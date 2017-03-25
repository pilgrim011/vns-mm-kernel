/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LnasLppEncode.c
  Description     :
  History         :
     1.WANGENSHENG 324863       2015-5-5   Draft Enact

******************************************************************************/



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/



#include "NasLppAirMsg.h"
#include "NasLppEncodeDecodePublic.h"
#include "NasLppDecode.h"
#include "NasCommPrint.h"


#define     NAS_LPP_DecodeWARNING

#define    THIS_FILE_ID            PS_FILE_ID_NASLPPDECODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPDECODE_C

#if (FEATURE_LPP == FEATURE_ON)

VOS_UINT32      NAS_LPP_UT_PRINTF(VOS_UINT32    ulBitPos,   VOS_UINT32  ulBitValue,VOS_UINT32 ulBitLen)
{
    vos_printf("\n\tthe BitPos is %d,the DecodeValue is %d,theCurrentLen is %d\n",ulBitPos,ulBitValue,ulBitLen);
    return 1;
}
/*****************************************************************************
Function Name   :NAS_LPP_DecodeNormalSmallInt
Description     :����ͨ��С�ķǸ�����
Input           : ��Ϣ������
Output          : None
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32     NAS_LPP_DecodeNormalSmallInt
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT32                         *pulSaveData)
{
    VOS_UINT32                          ulReturnRslt    = 0;
    VOS_UINT32                          ulReturnValue   = 0;

    ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /* L >63�����ֻ���벻��������,����Ҫ����֮������ݣ������������ */
    if (ulReturnRslt != 0)
    {

        /*���ͨ�õ�С�ķǸ����������һ��bitΪ1�������˸�bit��ʾL-1ռ�����ֽڣ�Ȼ���ȡL-1��ֵ*/
        ulReturnValue = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
        if (ulReturnValue == 1)
        {
            NAS_LPP_ASN_FAIL_Message(   NAS_LPP_NORMAL_VALUE,
                                        NAS_LPP_NORMAL_VALUE_LARGE_WARNING,
                                       *pulCurrentBitPos, __LINE__,0);
           *pulSaveData = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                        pulCurrentBitPos, 8);
        }
        else if (ulReturnValue == 2)
        {
            NAS_LPP_ASN_FAIL_Message(   NAS_LPP_NORMAL_VALUE,
                                        NAS_LPP_NORMAL_VALUE_LARGE_WARNING,
                                       *pulCurrentBitPos,
                                        __LINE__,0);
           *pulSaveData = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                        pulCurrentBitPos, 16);
        }
        else
        {
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_EXT_IE_LEN_ERROR;
        }

        return NAS_LPP_DECODE_SUCC;
    }
    else
    {
        ulReturnValue = NAS_LPP_GetDataFromBitStream(   pucDecodeBitStream,
                                                        pulCurrentBitPos, 6);
       *pulSaveData = (VOS_UINT8)ulReturnValue;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeExtObject
Description     :�����������ܴ��ڵ���չ���Э��汾û�У�ֱ������
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeExtObject
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos
)
{
    VOS_UINT32                          ulReturnRslt;
    VOS_UINT32                          ulExtObjectCnt = 0;
    VOS_UINT32                          ulCount = 0;
    VOS_UINT32                          ulReturnValue = 0;

    /*�ж��Ƿ������ȷ*/
    ulReturnRslt = NAS_LPP_DecodeNormalSmallInt(pucDecodeBitStream, pulCurrentBitPos,
                                               &ulExtObjectCnt);
    if (NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        return ulReturnRslt;
    }

    /*ASN��չ���L-1����Ҫ�ӻ���*/
    ulExtObjectCnt += 1;

    /*���汾Э��û����չ���ȡ�����е���չ���־λ�����Ϊ0��������Ҫ�����ļ����� 1 */
    for (ulCount = ulExtObjectCnt;ulCount != 0;ulCount--)
    {
        ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
        if (NAS_LPP_NO_SLCT == ulReturnRslt)
        {
            ulExtObjectCnt--;
        }
    }

    /*ѭ���������ڵ���չ��*/
    /*��չ�����ݲ���OPEN���뷽ʽ��ÿһ���һ��L+VȻ�����L �� V��L+VС��128���ֽ�ʱ����Ҫһ���ֽڼ���
    **����ʾL+V���ȵ�ֵ����128���ֽڣ���Ҫ����������һ��bit����Ϊ1����14��bit��ʾ���ȣ����������Ȼ����14��bit
    **�ܱ�ʾ�ķ�Χ���ٽ���һ��bit����Ϊ1��ĿǰmyeyeҲ������һ��bitΪ1�������������������:
    **|---------------------------------------------------------------------------------------------|
    **|���ȷ�Χ      |bitֵ��ʾ                                 |��ע˵��                           |
    **|---------------------------------------------------------------------------------------------|
    **|0~127         |0 X X X X X X X                           |X��ʾ��Ӧ������ֵ  (1 + 7)         |
    **|---------------------------------------------------------------------------------------------|
    **|128~2^14-1    |1 0   XX XXXX XXXX XXXX                   |��һ��bit1��������һ��0(2 + 14)    |
    **|---------------------------------------------------------------------------------------------|
    **|��Լ2^14      |1 1 0 X XXXX XXXX XXXX XXXX XXXX          |��һ�����myeye�Ѿ�֧�ֲ�����      |
    **|---------------------------------------------------------------------------------------------|
    ***/
    for (ulCount = 0; ulCount < ulExtObjectCnt; ulCount++)
    {
        ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

        /*�������128�ֽڣ���Ҫ���������Ƚ������⴦��*/
        if (ulReturnRslt == 1)
        {
            /*���1����һλ��0�����������������ȣ������1������֧�ַ�Χ�ڣ��϶��ǽ������*/
            ulReturnValue = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
            if ( ulReturnValue == 1 )
            {
                return  NAS_LPP_DECODE_MSG_VALUE_ERROR_EXT_IE_LEN_ERROR;
            }
            else
            {
                ulReturnValue = NAS_LPP_GetDataFromBitStream(   pucDecodeBitStream,
                                                                pulCurrentBitPos, 14);
               *pulCurrentBitPos += (ulReturnValue * 8);
            }
        }
        else
        {
            ulReturnValue = NAS_LPP_GetDataFromBitStream(   pucDecodeBitStream,
                                                            pulCurrentBitPos, 7);
           *pulCurrentBitPos += (ulReturnValue * 8);
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeExtEnumerated
Description     :�������չö��
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeExtEnumerated
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT8                           ucLen,
    VOS_UINT8                          *pEnumeratedValue
)
{
    VOS_UINT32                          ulReturnRslt = 0;
    VOS_UINT32                          ulReturnValue = 0;

    /*ö����չ���־λ*/
    ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    /*���Ϊ1����ͨ�õ�С�ķǸ�����������룬�����ó�BUTT*/
    if (0 != ulReturnRslt )
    {
        ulReturnRslt = NAS_LPP_DecodeNormalSmallInt(pucDecodeBitStream, pulCurrentBitPos,
                                                    &ulReturnValue);
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return ulReturnRslt;
        }
       *pEnumeratedValue = NAS_LPP_EXT_ENUMERATED_BUTT;
    }
    else
    {
        /*���Ϊ0�������ʵ�ʵ�ö��ֵ*/
       *pEnumeratedValue = (VOS_UINT8)NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                    pulCurrentBitPos, ucLen);
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEpduBody
Description     :����LPP_EPDU_BODY_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
EPDU-Body ::= OCTET STRING

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEpduBody
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_EPDU_BODY_STRU                 *pstEpduBody
)
{
    VOS_UINT32                          ulReturnRslt = 0;
    VOS_UINT32                          ulEpduBodyCount = 0;

    /* ��Ŀ���� */
    ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /* ������ȳ���128����Ҫ�������ֽڱ�ʾ���� */
    if (ulReturnRslt == 1)
    {
        ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 15);
        if (ulReturnRslt > 256)
        {
            NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_EPDUBODY_ERROR,
                                        NAS_LPP_OCTET_LEN_OUT_OF_RANGE,
                                       *pulCurrentBitPos,
                                      __LINE__, 0);
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
        }
        else
        {
            pstEpduBody->ulBodyLen = ulReturnRslt;
        }
    }
    else
    {
        pstEpduBody->ulBodyLen = NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                pulCurrentBitPos, 7);
    }

    for (ulEpduBodyCount = 0;ulEpduBodyCount < pstEpduBody->ulBodyLen;ulEpduBodyCount++)
    {
        ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                    pulCurrentBitPos, 8);
        pstEpduBody->aucBodyData[ulEpduBodyCount] = (VOS_UINT8)ulReturnRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEpduIdentifier
Description     :����LPP_EPDU_IDENTIFIER_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
EPDU-ID ::= INTEGER (1..256)

EPDU-Name ::= VisibleString (SIZE (1..32))

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
 VOS_UINT32  NAS_LPP_DecodeEpduIdentifier
 (
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_EPDU_IDENTIFIER_STRU           *pstEpduIdentifier)
{
    VOS_UINT32                          ulReturnRslt        = 0;
    VOS_UINT32                          ulEpduNameCount     = 0;
    VOS_UINT32                          ulReturnValue       = 0;

    /*��ȡ��չ��־λ*/
    pstEpduIdentifier->bitOpEpduIdentifierExt = NAS_LPP_GetDataFromBitStream(   pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);

    /*OPTIONAL��־λ*/
    pstEpduIdentifier->bitOpEpduName = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                    pulCurrentBitPos, 1);


    /*����integerֵ*/
    ulReturnValue = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
    ulReturnValue += 1;
    pstEpduIdentifier->ulEpduId = ulReturnValue;

    /*����optional��*/
    if (pstEpduIdentifier->bitOpEpduName == NAS_LPP_SLCT)
    {
        ulReturnValue = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 5);
        ulReturnValue += 1;
        pstEpduIdentifier->ulEpduNameLength = ulReturnValue;

        for (ulEpduNameCount = 0; ulEpduNameCount < pstEpduIdentifier->ulEpduNameLength; ulEpduNameCount++)
        {
            ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7);
            pstEpduIdentifier->acEpduName[ulEpduNameCount] = (VOS_UINT8)ulReturnRslt;
        }
    }


    /*������չ��*/
    if(NAS_LPP_NO_SLCT == pstEpduIdentifier->bitOpEpduIdentifierExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*����չ����ֱ���������ɣ��ж��Ƿ������ȷ*/
    ulReturnRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(ulReturnRslt != NAS_LPP_DECODE_SUCC)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_EPDUIDENTIFIER_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulReturnRslt;
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEpdu
Description     :����LPP_EPDU_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
EPDU ::= SEQUENCE {
        ePDU-Identifier         EPDU-Identifier,
        ePDU-Body               EPDU-Body
    }
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEpdu
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_EPDU_STRU                      *pstEpdu
)
{
    VOS_UINT32                          ulReturnRslt = 0;


    ulReturnRslt = NAS_LPP_DecodeEpduIdentifier(pucDecodeBitStream, pulCurrentBitPos,
                                              &(pstEpdu->stEpduIdentifier));
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        return  ulReturnRslt;
    }

    ulReturnRslt = NAS_LPP_DecodeEpduBody(pucDecodeBitStream, pulCurrentBitPos,
                                        &(pstEpdu->stEpduBody));
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        return  ulReturnRslt;
    }

    return  NAS_LPP_DECODE_SUCC;
}
/*****************************************************************************
Function Name   :NAS_LPP_DecodeEpduSequence
Description     :����LPP_EPDU_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEpduSequence
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_EPDU_SEQUENCE_STRU             *pstEpduSequence
)
{
    VOS_UINT32                          ulReturnResult          = 0;
    VOS_UINT32                          ulSequenceNum           = 0;
    VOS_UINT32                          ulCount                 = 0;

    /* ����Sequence of��Ŀ L - 1 */
    ulSequenceNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 4);
    ulSequenceNum = ulSequenceNum + 1;

    pstEpduSequence->ulEpduNum = ulSequenceNum;

    /* ѭ�����ý���EPDU���� */
    for(ulCount = 0;ulCount < ulSequenceNum;ulCount++)
    {
        ulReturnResult = NAS_LPP_DecodeEpdu(pucDecodeBitStream, pulCurrentBitPos,
                                          &(pstEpduSequence->astEpduArray[ulCount]));
        if(NAS_LPP_DECODE_SUCC != ulReturnResult)
        {
            return ulReturnResult;
        }
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeReqCapEpdu
Description     :����LPP_EPDU_REQ_CAP_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
                EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU
Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeReqCapEpdu
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_EPDU_REQ_CAP_STRU              *pstReqCapEpdu)
{
    VOS_UINT32                          ulReturnRslt = 0;

    /*����SEQUENCE OF*/
    ulReturnRslt = NAS_LPP_DecodeEpduSequence(  pucDecodeBitStream, pulCurrentBitPos,
                                               (LPP_EPDU_SEQUENCE_STRU *)pstReqCapEpdu);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        return ulReturnRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeReqCapEcid
Description     :����LPP_ECID_REQ_CAP_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
        Э��Ϊ��
Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeReqCapEcid(
                                                    VOS_UINT8                       *pucDecodeBitStream,
                                                    VOS_UINT32                      *pulCurrentBitPos,
                                                    LPP_ECID_REQ_CAP_STRU           *pstReqCapEcid)
{
    VOS_UINT32  ulReturnRslt = 0;

    /*������չ��־λ*/
    ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstReqCapEcid->bitOpEcidReqCapExt = ulReturnRslt;

    /*������չ��*/
    if(NAS_LPP_NO_SLCT == pstReqCapEcid->bitOpEcidReqCapExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    /*����չ����ֱ���������ɣ��ж��Ƿ������ȷ*/
    ulReturnRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_REQCAPOTDOA_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulReturnRslt;
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeReqCapOTDOA
Description     :����LPP_OTDOA_REQ_CAP_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
    Э��Ϊ��
Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32

History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeReqCapOTDOA
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_OTDOA_REQ_CAP_STRU             *pstReqCapOTDOA
)
{
    VOS_UINT32                          ulReturnRslt    = 0;

    /*������չ��־λ*/
    pstReqCapOTDOA->bitOpOtdoaReqCapExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 1);

    /*������չ��*/
    if(NAS_LPP_NO_SLCT == pstReqCapOTDOA->bitOpOtdoaReqCapExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    /*����չ����ֱ���������ɣ��ж��Ƿ������ȷ*/
    ulReturnRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(ulReturnRslt != NAS_LPP_DECODE_SUCC)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_REQCAPOTDOA_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos,
                               __LINE__,0);
        return ulReturnRslt;
    }

    return  NAS_LPP_DECODE_SUCC;
}
/*****************************************************************************
Function Name   :NAS_LPP_DecodeAGNSS
Description     :����LPP_AGNSS_REQ_CAP_STRU�ṹ��
Input           : ��Ϣ������
Output          : None
ASN             :
A-GNSS-RequestCapabilities ::= SEQUENCE {
        gnss-SupportListReq             BOOLEAN,
        assistanceDataSupportListReq    BOOLEAN,
        locationVelocityTypesReq        BOOLEAN,
        ...
    }

Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeReqCapAGNSS
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_AGNSS_REQ_CAP_STRU             *pstReqCapAGNSS
)
{
    VOS_UINT32                          ulReturnRslt = 0;

    /*��չ���־λ*/
    pstReqCapAGNSS->bitOpAGNSSReqCapExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 1);

    /*����ṹ������*/
    ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    if(1 == ulReturnRslt)
    {
        pstReqCapAGNSS->bGnssSupportListReq = NAS_LPP_TRUE;
    }
    else
    {
        pstReqCapAGNSS->bGnssSupportListReq = NAS_LPP_FALSE;
    }

    ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    if(1 == ulReturnRslt)
    {
        pstReqCapAGNSS->bAssistanceDataSupportListReq = NAS_LPP_TRUE;
    }
    else
    {
        pstReqCapAGNSS->bAssistanceDataSupportListReq = NAS_LPP_FALSE;
    }

    ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    if(1 == ulReturnRslt)
    {
        pstReqCapAGNSS->blocationVelocityTypesReq = NAS_LPP_TRUE;
    }
    else
    {
        pstReqCapAGNSS->blocationVelocityTypesReq = NAS_LPP_FALSE;
    }

    /*������չ��*/
    if(NAS_LPP_NO_SLCT == pstReqCapAGNSS->bitOpAGNSSReqCapExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    /*����չ����ֱ���������ɣ��ж��Ƿ������ȷ*/
    ulReturnRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_REQCAPAGNSS_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return  ulReturnRslt;
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeReqCapCommonIEs
Description     :����commonIEsRequestCapabilities
Input           : ��Ϣ������
Output          : None
ASN             :
       Э��Ϊ��
Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeReqCapCommonIEs
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_COMMON_IES_REQ_CAP_STRU        *pstReqCapCommonIEs
)
{
    VOS_UINT32                          ulReturnRslt = 0;

    /*������չ��־λ*/
    ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    if(NAS_LPP_SLCT == ulReturnRslt)
    {
        pstReqCapCommonIEs->bitOpCommonIEsReqCapabilitiesExt = 1;
    }

    /*������չ��*/
    if(NAS_LPP_NO_SLCT == pstReqCapCommonIEs->bitOpCommonIEsReqCapabilitiesExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    /*����չ����ֱ���������ɣ��ж��Ƿ������ȷ*/
    ulReturnRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(ulReturnRslt != NAS_LPP_DECODE_SUCC)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_REQCAPCOMMONIES_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulReturnRslt;
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeReqCapR9IEs
Description     :����RequestCapabilities-r9-IEs
Input           : ��Ϣ������
Output          : None
ASN             :

    RequestCapabilities-r9-IEs ::= SEQUENCE {
        commonIEsRequestCapabilities        CommonIEsRequestCapabilities        OPTIONAL,   -- Need ON
        a-gnss-RequestCapabilities          A-GNSS-RequestCapabilities          OPTIONAL,   -- Need ON
        otdoa-RequestCapabilities           OTDOA-RequestCapabilities           OPTIONAL,   -- Need ON
        ecid-RequestCapabilities            ECID-RequestCapabilities            OPTIONAL,   -- Need ON
        epdu-RequestCapabilities            EPDU-Sequence                       OPTIONAL,   -- Need ON
        ...
    }


Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32

History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeReqCapR9IEs
(
    VOS_UINT8                              *pucDecodeBitStream,
    VOS_UINT32                             *pulCurrentBitPos,
    LPP_REQUEST_CAPABILITIES_R9_IES_STRU   *pstReqCapabilities
)
{
    VOS_UINT32                              ulReturnRslt = 0;

    /*��ȡext��OPTIONAL��־λ*/
    pstReqCapabilities->bitOpLPPReqCapaabilitiesExt = NAS_LPP_GetDataFromBitStream(
                                                                                    pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 1);
    pstReqCapabilities->bitOpCommonIEsRequestCapabilities = NAS_LPP_GetDataFromBitStream(
                                                                                        pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 1);
    pstReqCapabilities->bitOpAGNSSRequestCapabilities = NAS_LPP_GetDataFromBitStream(
                                                                                    pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 1);
    pstReqCapabilities->bitOpOTDOARequestCapabilities = NAS_LPP_GetDataFromBitStream(
                                                                                    pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 1);
    pstReqCapabilities->bitOpECIDRequestCapabilities = NAS_LPP_GetDataFromBitStream(
                                                                                    pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 1);
    pstReqCapabilities->bitOpEPDUSequence = NAS_LPP_GetDataFromBitStream(
                                                                        pucDecodeBitStream,
                                                                        pulCurrentBitPos, 1);

    /*����CommonIEsRequestCapabilities*/
    if(NAS_LPP_SLCT == pstReqCapabilities->bitOpCommonIEsRequestCapabilities)
    {
        ulReturnRslt = NAS_LPP_DecodeReqCapCommonIEs(   pucDecodeBitStream,
                                                        pulCurrentBitPos,
                                                      &(pstReqCapabilities->stCommonIEsRequestCapabilities));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }
    }
    /*����A-GNSS-RequestCapabilities*/
    if(NAS_LPP_SLCT == pstReqCapabilities->bitOpAGNSSRequestCapabilities)
    {
        ulReturnRslt = NAS_LPP_DecodeReqCapAGNSS(   pucDecodeBitStream,
                                                    pulCurrentBitPos,
                                                  &(pstReqCapabilities->stAGNSSRequestCapabilities));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }
    }

    /*���� OTDOA-RequestCapabilities*/
    if(NAS_LPP_SLCT == pstReqCapabilities->bitOpOTDOARequestCapabilities)
    {
        ulReturnRslt = NAS_LPP_DecodeReqCapOTDOA(   pucDecodeBitStream,
                                                    pulCurrentBitPos,
                                                  &(pstReqCapabilities->stOTDOARequestCapabilities));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }
    }

    /*����ECID-RequestCapabilities*/
    if(NAS_LPP_SLCT == pstReqCapabilities->bitOpECIDRequestCapabilities)
    {
        ulReturnRslt = NAS_LPP_DecodeReqCapEcid(    pucDecodeBitStream,
                                                    pulCurrentBitPos,
                                                  &(pstReqCapabilities->stECIDRequestCapabilities));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }
    }

    /*����EPDU-Sequence*/
    if(NAS_LPP_SLCT == pstReqCapabilities->bitOpEPDUSequence)
    {
        ulReturnRslt = NAS_LPP_DecodeReqCapEpdu(    pucDecodeBitStream,
                                                    pulCurrentBitPos,
                                                  &(pstReqCapabilities->stEPDURequestCapabilities));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }
    }

    /*������չ�����ݣ���ǰ�汾û�У�ֱ����������*/
    if(NAS_LPP_NO_SLCT == pstReqCapabilities->bitOpLPPReqCapaabilitiesExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*����չ����ֱ���������ɣ��ж��Ƿ������ȷ*/
    ulReturnRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(ulReturnRslt != NAS_LPP_DECODE_SUCC)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_REQCAPR9IES_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulReturnRslt;
    }

    return  NAS_LPP_DECODE_SUCC;
}
/*****************************************************************************
Function Name   :NAS_LPP_DecodeExtReqCap
Description     :����RequestCapabilities��criticalExtensions
Input           : ��Ϣ������
Output          : None
asn             :
c1                      CHOICE {
                requestCapabilities-r9      RequestCapabilities-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },

Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32

History         :
  1.WANGENSHENG 00324863           2015-05-7  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeExtReqCap
(
    VOS_UINT8                                      *pucDecodeBitStream,
    VOS_UINT32                                     *pulCurrentBitPos,
    LPP_CRITI_EXT_REQUEST_CAPABILITIES_STRU        *pstReqCapabilities
)
{
    VOS_UINT32                                      ulReturnRslt = 0;


    /*����ѡ��������*/
    pstReqCapabilities->ulChoice = NAS_LPP_GetDataFromBitStream(
                                                                pucDecodeBitStream,
                                                                pulCurrentBitPos, 2);

    /*������Ϣ��*/
    switch(pstReqCapabilities->ulChoice)
    {
        case LPP_C1_CRITI_EXT_REQUEST_CAPABILITIES_R9_CHOSEN:
            ulReturnRslt =NAS_LPP_DecodeReqCapR9IEs(pucDecodeBitStream,
                                                    pulCurrentBitPos,
                                                  &(pstReqCapabilities->u.stRequestCapabilitiesR9));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return  ulReturnRslt;
            }
            break;

        default:
            break;
    }

    return      NAS_LPP_DECODE_SUCC;
}


/*****************************************************************************
Function Name   :NAS_LPP_DecodeReqCap
Description     :����RequestCapabilities
Input           : ��Ϣ������
Output          : None
ASN             :
RequestCapabilities ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                requestCapabilities-r9      RequestCapabilities-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }

Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeReqCap
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_MESSAGE_REQUEST_CAPABILITIES_STRU   *pstReqCapabilities
)
{
    VOS_UINT32                               ulReturnRslt = 0;

    /*����choice��*/
    pstReqCapabilities->ulChoice = NAS_LPP_GetDataFromBitStream(
                                                                pucDecodeBitStream,
                                                                pulCurrentBitPos,
                                                                1);

    /*���������Ԫ*/
    switch(pstReqCapabilities->ulChoice)
    {
        case LPP_C1_CRITI_EXT_REQUEST_CAPABILITIES_CHOSEN:
            ulReturnRslt = NAS_LPP_DecodeExtReqCap( pucDecodeBitStream,
                                                    pulCurrentBitPos,
                                                  &(pstReqCapabilities->u.stC1));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return  ulReturnRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeErrorCause
Description     :����errorCause
Input           : ��Ϣ������
Output          : None
ASN             :
    errorCause  ENUMERATED {
    undefined,
    lppMessageHeaderError,
    lppMessageBodyError,
    epduError,
    incorrectDataValue,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeErrorCause
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT8                           ucLen,
    LPP_COMMON_IES_ERROR_ENUM_UINT8    *penCommonIEsError
)
{
    VOS_UINT32                          ulRslt      = 0;

    ulRslt = NAS_LPP_DecodeExtEnumerated(   pucDecodeBitStream, pulCurrentBitPos,
                                            ucLen, penCommonIEsError);
    if ( NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_ERRORCAUSE_ERROR,
                                    NAS_LPP_NORMAL_VALUE_LARGE_ERROR,
                                   *pulCurrentBitPos, __LINE__, 0);
        return  ulRslt;
    }

    if ((NAS_LPP_EXT_ENUMERATED_BUTT == *penCommonIEsError) || (*penCommonIEsError > 4))
    {
       *penCommonIEsError = LPP_COMMON_IES_ERROR_BUTT;
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_ERRORCAUSE_ERROR,
                                    NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                   *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCommonIEsError
Description     :����CommonIEsError
Input           : ��Ϣ������
Output          : None
ASN             :
CommonIEsError ::= SEQUENCE {
        errorCause  ENUMERATED {
        undefined,
        lppMessageHeaderError,
        lppMessageBodyError,
        epduError,
        incorrectDataValue,
        ...
    }
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCommonIEsError
(
    VOS_UINT8                       *pucDecodeBitStream,
    VOS_UINT32                      *pulCurrentBitPos,
    LPP_COMMON_IES_ERROR_STRU       *pstCommonIEsError
)
{
    VOS_UINT32  ulRslt = 0;

    /*����ö��ErrorCause*/
    ulRslt = NAS_LPP_DecodeErrorCause(pucDecodeBitStream, pulCurrentBitPos, 3,
                                    &(pstCommonIEsError->enCommonIesErrorCasue));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEpduSequenceError
Description     :����EPDU-Sequence
Input           : ��Ϣ������
Output          : None
ASN             :
EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

maxEPDU INTEGER ::= 16
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEpduSequenceError
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_EPDU_SEQUENCE_STRU             *pstEpduSequnce
)
{
    VOS_UINT32                          ulRslt = 0;

    /*����SEQUENCE OF*/
    ulRslt = NAS_LPP_DecodeEpduSequence(pucDecodeBitStream, pulCurrentBitPos, pstEpduSequnce);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEpduError
Description     :����EPDU-Sequence
Input           : ��Ϣ������
Output          : None
ASN             :
EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

maxEPDU INTEGER ::= 16
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEpduError
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_EPDU_SEQUENCE_STRU             *pstEpduSequnce
)
{
    VOS_UINT32                          ulRslt              = 0;
    VOS_UINT32                          ulEpduByteLen       = 0;
    VOS_UINT32                          ulPadLen            = 0;
    VOS_UINT32                          ulEpduBodyStartLen  = 0;
    VOS_UINT32                          ulEpduBodyEndLen    = 0;

    /*����L+V*/
    ulEpduBodyEndLen = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,  pulCurrentBitPos, 1);
    if(ulEpduBodyEndLen == 1)
    {
        ulEpduByteLen = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos,  15);
        if(ulEpduByteLen > 256)
        {
            NAS_LPP_ASN_FAIL_Message(   NAS_LPP_EPDUERROR_ERROR,
                                        NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                       *pulCurrentBitPos,
                                      __LINE__, 0);
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;

        }
    }
    else
    {
        ulEpduByteLen = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream, pulCurrentBitPos, 7);
    }
    ulEpduBodyStartLen  = *pulCurrentBitPos;
    /*������Ϣʵ��*/
    ulRslt = NAS_LPP_DecodeEpduSequenceError(   pucDecodeBitStream,pulCurrentBitPos,
                                                pstEpduSequnce);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    ulEpduBodyEndLen = *pulCurrentBitPos;

    /*�����bit*/
    ulPadLen = (ulEpduByteLen * 8) - (ulEpduBodyEndLen - ulEpduBodyStartLen);
    if(0 != ulPadLen)
    {
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, (VOS_UINT8)ulPadLen);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeErrorIEsR9
Description     :����Error-r9-IEs
Input           : ��Ϣ������
Output          : None
ASN             :
Error-r9-IEs ::= SEQUENCE {
    commonIEsError  CommonIEsError  OPTIONAL,-- Need ON
    ...,
    epdu-Error      EPDU-Sequence   OPTIONAL -- Need ON
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeErrorIEsR9
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_ERROR_R9_STRU                  *pstErrorR9
)
{
    VOS_UINT32                          ulRslt                  = 0;
    VOS_UINT32                          ulExtIeNum              = 0;
    VOS_UINT32                          ulLoop                  = 0;
    VOS_UINT32                          ulExtIeInvalidOption    = 0;
    VOS_UINT32                          ulExtIeInValidNum       = 0;

    /*������չ��*/
    pstErrorR9->bitOpErrorR9IEsExt = NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                    pulCurrentBitPos, 1);

    /*����option*/
    pstErrorR9->bitOpCommonIesError = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                    pulCurrentBitPos, 1);

    /*����commonIEsError*/
    if(NAS_LPP_SLCT == pstErrorR9->bitOpCommonIesError)
    {
        ulRslt = NAS_LPP_DecodeCommonIEsError(pucDecodeBitStream,pulCurrentBitPos,
                                            &(pstErrorR9->stCommonIesError));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*������չ��epdu-Error*/
    /*û��ѡ����չ��*/
    if(NAS_LPP_NO_SLCT == pstErrorR9->bitOpErrorR9IEsExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*ѡ����չ��*/
    /*������չ��ļ���L-1*/
    ulRslt = NAS_LPP_DecodeNormalSmallInt(pucDecodeBitStream, pulCurrentBitPos, &ulExtIeNum);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    /*�����������չ��ļ�����1����ʾ�����������İ汾����չ��ļ���*/
    ulExtIeNum += 1;

    /*�����Э��汾һ����չ���option*/
    pstErrorR9->bitOpEpduError = NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                pulCurrentBitPos, 1);

    /*�����Э��汾��һ����չ���option*/
    for(ulLoop = 0; ulLoop < ulExtIeNum - 1; ulLoop++)
    {
        ulExtIeInvalidOption = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                            pulCurrentBitPos, 1);
        if(NAS_LPP_SLCT == ulExtIeInvalidOption)
        {
            ulExtIeInValidNum++;
        }
    }

    /*������չ��ľ����ֵ*/
    /*����Э��汾һ�µ���Ԫ*/
    if(NAS_LPP_SLCT == pstErrorR9->bitOpEpduError)
    {
        ulRslt = NAS_LPP_DecodeEpduError(pucDecodeBitStream, pulCurrentBitPos,
                                       &(pstErrorR9->stEpduError));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }
    /*�����ǰ��չ��ļ�����UE�汾����չ��ļ�����ȣ���˵��Э��汾һ�£��������*/
    if(1 == ulExtIeNum)
    {
        return NAS_LPP_DECODE_SUCC;
    }
    else
    {
        /*Э��汾�ȱ��ظߣ�����Ҫ����ѭ������ʣ�µ�IE��*/
        ulRslt = NAS_LPP_DecodeExtIeWithPartValid(  pucDecodeBitStream, pulCurrentBitPos,
                                                    ulExtIeInValidNum);
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_ERRORIESR9_ERROR,
                                        NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                       *pulCurrentBitPos,
                                      __LINE__,0);
            return ulRslt;
        }

        return NAS_LPP_DECODE_SUCC;
    }
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeError
Description     :����ErrorMessage
Input           : ��Ϣ������
Output          : None
ASN             :
Error ::= CHOICE {
    error-r9                    Error-r9-IEs,
    criticalExtensionsFuture    SEQUENCE {}
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeError
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_MESSAGE_ERROR_STRU             *pstMessageError
)
{
    VOS_UINT32                          ulRslt = 0;

    /*����choice��*/
    pstMessageError->ulChoice = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                             pulCurrentBitPos, 1);

    switch(pstMessageError->ulChoice)
    {
        case LPP_ERROR_R9_IES_CHOSEN:
            ulRslt = NAS_LPP_DecodeErrorIEsR9(pucDecodeBitStream,pulCurrentBitPos,
                                            &(pstMessageError->u.stErrorR9));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return  ulRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeErrorCause
Description     :����errorCause
Input           : ��Ϣ������
Output          : None
ASN             :
    errorCause  ENUMERATED {
    undefined,
    lppMessageHeaderError,
    lppMessageBodyError,
    epduError,
    incorrectDataValue,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeAbortCause
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT8                           ucLen,
    LPP_COMMON_IES_ABORT_ENUM_UINT8    *penCommIEsAbort
)
{
    VOS_UINT32                          ulRslt = 0;

    ulRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                        ucLen, penCommIEsAbort);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ABORTCAUSE_ERROR, NAS_LPP_NORMAL_VALUE_LARGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  ulRslt;
    }
    if((NAS_LPP_EXT_ENUMERATED_BUTT == *penCommIEsAbort)||(*penCommIEsAbort > 4))
    {
        *penCommIEsAbort = LPP_COMMON_IES_ABORT_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ABORTCAUSE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCommonIEsAbort
Description     :����criticalExtensions
Input           : ��Ϣ������
Output          : None
ASN             :
CommonIEsAbort ::= SEQUENCE {
        abortCause  ENUMERATED {
        undefined,
        stopPeriodicReporting,
        targetDeviceAbort,
        networkAbort,
        ...
    }
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCommonIEsAbort
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_COMMON_IES_ABORT_STRU          *pstCommonIEsAbort
)
{
    VOS_UINT32  ulRslt = 0;

    /*����ö��ErrorCause*/
    ulRslt = NAS_LPP_DecodeAbortCause(pucDecodeBitStream, pulCurrentBitPos, 2,
                                    &(pstCommonIEsAbort->enCommonIesAbortCasue));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEpduSequencAbort
Description     :����EPDU-Sequence
Input           : ��Ϣ������
Output          : None
ASN             :
EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

maxEPDU INTEGER ::= 16
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEpduSequencAbort
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_EPDU_SEQUENCE_STRU             *pstEpduSequnce
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*����SEQUENCE OF*/
    ulRslt = NAS_LPP_DecodeEpduSequence(pucDecodeBitStream, pulCurrentBitPos, pstEpduSequnce);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEpduAbort
Description     :����epdu-Abort
Input           : ��Ϣ������
Output          : None
ASN             :
Abort-r9-IEs ::= SEQUENCE {
        ommonIEsAbort   CommonIEsAbort  OPTIONAL,	-- Need ON
        ...,
        epdu-Abort      EPDU-Sequence   OPTIONAL	-- Need ON
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEpduAbort
(
    VOS_UINT8                           *pucDecodeBitStream,
    VOS_UINT32                          *pulCurrentBitPos,
    LPP_EPDU_SEQUENCE_STRU              *pstEpduSequence
)
{
    VOS_UINT32                          ulRslt              = 0;
    VOS_UINT32                          ulEpduByteLen       = 0;
    VOS_UINT32                          ulPadLen            = 0;
    VOS_UINT32                          ulEpduBodyStartLen  = 0;
    VOS_UINT32                          ulEpduBodyEndLen    = 0;

    /*����L+V*/

    ulEpduBodyEndLen = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,  pulCurrentBitPos, 1);
    if(ulEpduBodyEndLen == 1)
    {
        ulEpduByteLen = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos,  15);
        if(ulEpduByteLen > 256)
        {
            NAS_LPP_ASN_FAIL_Message(   NAS_LPP_EPDUERROR_ERROR,
                                        NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                       *pulCurrentBitPos,
                                      __LINE__, 0);
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;

        }
    }
    else
    {
        ulEpduByteLen = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream, pulCurrentBitPos, 7);
    }
    ulEpduBodyStartLen = *pulCurrentBitPos;

    /*������Ϣʵ��*/
    ulRslt = NAS_LPP_DecodeEpduSequencAbort(pucDecodeBitStream,pulCurrentBitPos, pstEpduSequence);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    ulEpduBodyEndLen = *pulCurrentBitPos;

    /*�����bit*/
    ulPadLen = (ulEpduByteLen * 8) - (ulEpduBodyEndLen - ulEpduBodyStartLen);
    if(0 != ulPadLen)
    {
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, (VOS_UINT8)ulPadLen);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCritExtAbortR9
Description     :����criticalExtensions
Input           : ��Ϣ������
Output          : None
ASN             :
Abort-r9-IEs ::= SEQUENCE {
        ommonIEsAbort   CommonIEsAbort  OPTIONAL,	-- Need ON
        ...,
        epdu-Abort      EPDU-Sequence   OPTIONAL	-- Need ON
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCritExtAbortR9
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_ABORT_R9_IES_STRU              *pstAbortR9IEs)
{
    VOS_UINT32                          ulRslt                  = 0;
    VOS_UINT32                          ulExtIeNum              = 0;
    VOS_UINT32                          ulLoop                  = 0;
    VOS_UINT32                          ulExtIeInvalidOption    = 0;
    VOS_UINT32                          ulExtIeInValidNum       = 0;

    /*������չ��*/
    pstAbortR9IEs->bitOpAbortR9IEsExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                     pulCurrentBitPos, 1);

    /*����option*/
    pstAbortR9IEs->bitOpCommonIesAbort = NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                        pulCurrentBitPos, 1);

    /*����commonIEsAbort*/
    if(NAS_LPP_SLCT == pstAbortR9IEs->bitOpCommonIesAbort)
    {
        ulRslt = NAS_LPP_DecodeCommonIEsAbort(pucDecodeBitStream,pulCurrentBitPos,
                                            &(pstAbortR9IEs->stCommonIesAbort));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*������չ��epdu-Error*/
    /*û��ѡ����չ��*/
    if(NAS_LPP_NO_SLCT == pstAbortR9IEs->bitOpAbortR9IEsExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*ѡ����չ��*/
    /*������չ��ļ���L-1*/
    ulRslt = NAS_LPP_DecodeNormalSmallInt(pucDecodeBitStream, pulCurrentBitPos, &ulExtIeNum);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    /*�����������չ��ļ�����1����ʾ�����������İ汾����չ��ļ���*/
    ulExtIeNum += 1;

    /*�����Э��汾һ����չ���option*/
    pstAbortR9IEs->bitOpEpduAbort = NAS_LPP_GetDataFromBitStream(   pucDecodeBitStream,
                                                                    pulCurrentBitPos, 1);

    /*�����Э��汾��һ����չ���option*/
    for(ulLoop = 0; ulLoop < ulExtIeNum - 1; ulLoop++)
    {
        ulExtIeInvalidOption = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
        if(NAS_LPP_SLCT == ulExtIeInvalidOption)
        {
            ulExtIeInValidNum++;
        }
    }

    /*������չ��ľ����ֵ*/
    /*����Э��汾һ�µ���Ԫ*/
    if(NAS_LPP_SLCT == pstAbortR9IEs->bitOpEpduAbort)
    {
        ulRslt = NAS_LPP_DecodeEpduAbort(pucDecodeBitStream, pulCurrentBitPos,
                                       &(pstAbortR9IEs->stEpduAbort));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*�����ǰ��չ��ļ�����UE�汾����չ��ļ�����ȣ���˵��Э��汾һ�£��������*/
    if(1 == ulExtIeNum)
    {
        return NAS_LPP_DECODE_SUCC;
    }
    else
    {
        /*Э��汾�ȱ��ظߣ�����Ҫ����ѭ������ʣ�µ�IE��*/
        ulRslt = NAS_LPP_DecodeExtIeWithPartValid(  pucDecodeBitStream, pulCurrentBitPos,
                                                    ulExtIeInValidNum);
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_CRITEXTABORTR9_ERROR,
                                        NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                       *pulCurrentBitPos,
                                      __LINE__,0);
            return ulRslt;
        }

        return NAS_LPP_DECODE_SUCC;
    }
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCritExtAbort
Description     :����criticalExtensions
Input           : ��Ϣ������
Output          : None
ASN             :
Abort ::= SEQUENCE {
        criticalExtensions      CHOICE {
        c1                  CHOICE {
        abort-r9        Abort-r9-IEs,
        spare3 NULL, spare2 NULL, spare1 NULL
        },
        criticalExtensionsFuture    SEQUENCE {}
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCritExtAbort
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_C1_EXT_ABORT_STRU              *pstCritExtAbortC1)
{
    VOS_UINT32                          ulRslt              = 0;

    /*����choice��*/
    pstCritExtAbortC1->ulChoice = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                pulCurrentBitPos, 2);

    switch(pstCritExtAbortC1->ulChoice)
    {
        case LPP_C1_CRITI_EXT_ABORT_R9_CHOSEN:
            ulRslt = NAS_LPP_DecodeCritExtAbortR9(pucDecodeBitStream,pulCurrentBitPos,
                                                &(pstCritExtAbortC1->u.stAbortR9));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return  ulRslt;
            }
            break;
        default:
            break;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeError
Description     :����ErrorMessage
Input           : ��Ϣ������
Output          : None
ASN             :
Abort ::= SEQUENCE {
        criticalExtensions      CHOICE {
        c1                  CHOICE {
        abort-r9        Abort-r9-IEs,
        spare3 NULL, spare2 NULL, spare1 NULL
        },
        criticalExtensionsFuture    SEQUENCE {}
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeAbortMsg
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_CRIT_EXT_ABORT_STRU            *pstCritExtAbort
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*����choice��*/
    pstCritExtAbort->ulChoice = NAS_LPP_GetDataFromBitStream(   pucDecodeBitStream,
                                                                pulCurrentBitPos, 1);

    switch(pstCritExtAbort->ulChoice)
    {
        case LPP_CRITI_EXT_ABORT_CHOSEN:
            ulRslt = NAS_LPP_DecodeCritExtAbort(pucDecodeBitStream,pulCurrentBitPos,
                                              &(pstCritExtAbort->u.stAbortExtC1));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return  ulRslt;
            }
            break;
        default:
            break;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeError
Description     :����ErrorMessage
Input           : ��Ϣ������
Output          : None
ASN             :
Abort ::= SEQUENCE {
        criticalExtensions      CHOICE {
        c1                  CHOICE {
        abort-r9        Abort-r9-IEs,
        spare3 NULL, spare2 NULL, spare1 NULL
        },
        criticalExtensionsFuture    SEQUENCE {}
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeAbort
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_MESSAGE_ABORT_STRU             *pstMessageAbort)
{
    VOS_UINT32                          ulRslt              = 0;

    ulRslt = NAS_LPP_DecodeAbortMsg(pucDecodeBitStream, pulCurrentBitPos,
                                  &(pstMessageAbort->stC1));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCommonIesReqLocationInfo
Description     :����CommonIEsRequestLocationInformation
Input           : ��Ϣ������
Output          : None
ASN             :
    LocationInformationType ::= ENUMERATED {
        locationEstimateRequired,
        locationMeasurementsRequired,
        locationEstimatePreferred,
        locationMeasurementsPreferred,
        ...
    }
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeLocationInfoType
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT8                           ucLen,
    LPP_LOCATION_INFO_TYPE_ENUM_UINT8  *penLppLocationInfoType
)
{
    VOS_UINT32                          ulRslt = 0;

    ulRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                        ucLen, penLppLocationInfoType);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_LOCATIONINFOTYPE_ERROR,
                                 NAS_LPP_NORMAL_VALUE_LARGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  ulRslt;
    }
    if(NAS_LPP_EXT_ENUMERATED_BUTT == *penLppLocationInfoType)
    {
        *penLppLocationInfoType = LPP_LOCATION_INFO_TYPE_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_LOCATIONINFOTYPE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }
    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeLocationTriggeredReporting
Description     :����CommonIEsRequestLocationInformation
Input           : ��Ϣ������
Output          : None
ASN             :
    TriggeredReportingCriteria ::=      SEQUENCE {
        cellChange                          BOOLEAN,
        reportingDuration                   ReportingDuration,
        ...
    }
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeLocationTriggeredReporting
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_TRIGGER_REPORT_CRITERIA_STRU   *pstTriggerReport
)
{
    VOS_UINT32                          ulRslt = 0;

    /*������չ��*/
    pstTriggerReport->bitOpTriggerReportCriteriaExt =NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);

    /*����cellChange*/
    pstTriggerReport->bCellChange = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                 pulCurrentBitPos, 1);

    /*����reportDuration*/
    pstTriggerReport->ulReportDuration = NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                        pulCurrentBitPos, 8);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstTriggerReport->bitOpTriggerReportCriteriaExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_LOCATIONTRIGGEREDREPORTING_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeReportingAmount
Description     :����enReportAmount
Input           : ��Ϣ������
Output          : None
ASN             :

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeReportingAmount
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_REPORT_AMOUNT_ENUM_UINT32      *penReportAmount
)
{
    *penReportAmount = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 3);

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeReportingAmount
Description     :����enReportAmount
Input           : ��Ϣ������
Output          : None
ASN             :

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeReportingInterval
(
    VOS_UINT8                       *pucDecodeBitStream,
    VOS_UINT32                      *pulCurrentBitPos,
    LPP_REPORT_INTERVAL_ENUM_UINT32   *penReportInteraval
)
{
    *penReportInteraval = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 4);
    if(*penReportInteraval > 9)
    {

        NAS_LPP_ASN_FAIL_Message(NAS_LPP_REPORTINGINTERVAL_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeLocationPeriodicalReporting
Description     :����TriggeredReportingCriteria
Input           : ��Ϣ������
Output          : None
ASN             :
    PeriodicalReportingCriteria ::=     SEQUENCE {
        reportingAmount                     ENUMERATED {
                                                ra1, ra2, ra4, ra8, ra16, ra32,
                                                ra64, ra-Infinity
                                            } DEFAULT ra-Infinity,
        reportingInterval                   ENUMERATED {
                                                noPeriodicalReporting, ri0-25,
                                                ri0-5, ri1, ri2, ri4, ri8, ri16, ri32, ri64
                                            }
    }
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeLocationPeriodicalReporting
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_PERIODICAL_REPORT_STRU         *pstPeriodicalReport
)
{
    VOS_UINT32                          ulRslt          = 0;
    VOS_UINT32                          ulDefaultBit    = 0;

    /*����ReportAmount*/
    /*ReportAmount��һ��default��б�־λ�������־λΪ1��˵�����������ݣ������Ϊ1����������������ȱʡֵ*/
    ulDefaultBit = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,  pulCurrentBitPos, 1);
    if(ulDefaultBit == 1)
    {
        ulRslt = NAS_LPP_DecodeReportingAmount(pucDecodeBitStream, pulCurrentBitPos,
                                             &(pstPeriodicalReport->enReportAmount));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }
    else
    {
        pstPeriodicalReport->enReportAmount = LPP_REPORT_AMOUNT_RA_INFINITY;
    }

    /*����ReportInterval*/
    ulRslt = NAS_LPP_DecodeReportingInterval(pucDecodeBitStream, pulCurrentBitPos,
                                           &(pstPeriodicalReport->enReportInterval));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeLocationAdditonInfo
Description     :����AdditionalInformation
Input           : ��Ϣ������
Output          : None
ASN             :
    AdditionalInformation ::= ENUMERATED {
        onlyReturnInformationRequested,
        mayReturnAditionalInformation,
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeLocationAdditonInfo
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT8                           ucLen,
    LPP_ADDITON_REPORT_ENUM_UNIT8      *enLppAdditonType
)
{
    VOS_UINT32                          ulRslt              = 0;

    ulRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                        ucLen, enLppAdditonType);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_LOCATIONADDITONINFO_ERROR,
                                 NAS_LPP_NORMAL_VALUE_LARGE_ERROR,
                                 *pulCurrentBitPos, __LINE__, 0);
        return  ulRslt;
    }
    if(NAS_LPP_EXT_ENUMERATED_BUTT == *enLppAdditonType)
    {
        *enLppAdditonType = LPP_ADDITON_REPORT_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_LOCATIONADDITONINFO_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeHoriazontalAccuracy
Description     :����HorizontalAccuracy
Input           : ��Ϣ������
Output          : None
ASN             :
    HorizontalAccuracy ::= SEQUENCE {
        accuracy        INTEGER(0..127),
        confidence      INTEGER(0..100),
        ...
    }
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeHoriazontalAccuracy
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_HORIZONTAL_ACCURACY_STRU       *pstHorizontalAccuracy
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��*/
    pstHorizontalAccuracy->bitOpHorizontalAccuracyExt =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����accuracy*/
    pstHorizontalAccuracy->ucAccuracy =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7);

    /*����confidence*/
    pstHorizontalAccuracy->ucConfidence =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7);
    if(pstHorizontalAccuracy->ucConfidence > 100)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_HORIAZONTALACCURACY_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstHorizontalAccuracy->bitOpHorizontalAccuracyExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_HORIAZONTALACCURACY_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeVerticalAccuracy
Description     :����VerticalAccuracy
Input           : ��Ϣ������
Output          : None
ASN             :
    VerticalAccuracy ::= SEQUENCE {
        accuracy        INTEGER(0..127),
        confidence      INTEGER(0..100),
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeVerticalAccuracy
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_VERTICAL_ACCURACY_STRU         *pstVerticalAccuracy
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��*/
    pstVerticalAccuracy->bitOpVerticalAccuracyExt =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����accuracy*/
    pstVerticalAccuracy->ucAccuracy =
            (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7);

    /*����confidence*/
    pstVerticalAccuracy->ucConfidence =
            (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7);
    if(pstVerticalAccuracy->ucConfidence > 100)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_VERTICALACCURACY_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstVerticalAccuracy->bitOpVerticalAccuracyExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_VERTICALACCURACY_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeVerticalAccuracy
Description     :����VerticalAccuracy
Input           : ��Ϣ������
Output          : None
ASN             :
    VerticalAccuracy ::= SEQUENCE {
        accuracy        INTEGER(0..127),
        confidence      INTEGER(0..100),
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeResponseTime
(
    VOS_UINT8                       *pucDecodeBitStream,
    VOS_UINT32                      *pulCurrentBitPos,
    LPP_RESPONSE_TIME_STRU          *pstResponseTime)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��*/
    pstResponseTime->bitOpResponseTimeExt =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����responseTime*/
    pstResponseTime->ucTime =
            (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7) + 1;


    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstResponseTime->bitOpResponseTimeExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_RESPONSETIME_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}



/*****************************************************************************
Function Name   :NAS_LPP_DecodeLocationQos
Description     :����QoS
Input           : ��Ϣ������
Output          : None
ASN             :
    QoS ::= SEQUENCE {
        horizontalAccuracy          HorizontalAccuracy      OPTIONAL,   -- Need ON
        verticalCoordinateRequest   BOOLEAN,
        verticalAccuracy            VerticalAccuracy        OPTIONAL,   -- Need ON
        responseTime                ResponseTime            OPTIONAL,   -- Need ON
        velocityRequest             BOOLEAN,
        ...
    }
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeLocationQos
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_QOS_STRU                       *pstLppQos
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��*/
    pstLppQos->bitOpQoSExt =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*�����ѡ��*/
    pstLppQos->bitOpHoriazontalAccuracy =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstLppQos->bitOpVerticalAccuracy =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstLppQos->bitOpResponseTime =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����HorizontalAccuracy*/
    if(NAS_LPP_SLCT == pstLppQos->bitOpHoriazontalAccuracy)
    {
        ulRslt = NAS_LPP_DecodeHoriazontalAccuracy(pucDecodeBitStream, pulCurrentBitPos,
                                                 &(pstLppQos->stHorizontalAccuracy));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����verticalCoordinateRequest*/
    pstLppQos->bVerticalCoordinateRequest =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����verticalAccuracy*/
    if(NAS_LPP_SLCT == pstLppQos->bitOpVerticalAccuracy)
    {
        ulRslt = NAS_LPP_DecodeVerticalAccuracy(pucDecodeBitStream, pulCurrentBitPos,
                                              &(pstLppQos->stVerticalAccuracy));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����responseTime*/
    if(NAS_LPP_SLCT == pstLppQos->bitOpResponseTime)
    {
        ulRslt = NAS_LPP_DecodeResponseTime(pucDecodeBitStream, pulCurrentBitPos,
                                          &(pstLppQos->stResponseTime));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����velocityRequest*/
    pstLppQos->bVelocityReq = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstLppQos->bitOpQoSExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_LOCATIONQOS_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeLocationEnvironment
Description     :����Environment
Input           : ��Ϣ������
Output          : None
ASN             :
    Environment ::= ENUMERATED {
        badArea,
        notBadArea,
        mixedArea,
        ...
    }
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeLocationEnvironment
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT8                           ucLen,
    LPP_ENVIRONMENT_ENUM_UINT8         *penEnvironment
)
{
    VOS_UINT32      ulRslt = 0;

    ulRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos, ucLen, penEnvironment);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_LOCATIONENVIRONMENT_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  ulRslt;
    }
    if((NAS_LPP_EXT_ENUMERATED_BUTT == *penEnvironment)||(*penEnvironment > 2))
    {
        *penEnvironment = LPP_ENVIRONMENT_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_LOCATIONENVIRONMENT_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeLocationCoordinateType
Description     :����LocationCoordinateTypes
Input           : ��Ϣ������
Output          : None
ASN             :
    LocationCoordinateTypes ::= SEQUENCE {
        ellipsoidPoint                                          BOOLEAN,
        ellipsoidPointWithUncertaintyCircle                     BOOLEAN,
        ellipsoidPointWithUncertaintyEllipse                    BOOLEAN,
        polygon                                                 BOOLEAN,
        ellipsoidPointWithAltitude                              BOOLEAN,
        ellipsoidPointWithAltitudeAndUncertaintyEllipsoid       BOOLEAN,
        ellipsoidArc                                            BOOLEAN,
        ...
    }
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeLocationCoordinateType
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_LOCATION_COORDINATE_TYPE_STRU  *pstLocationCoordianteType
)
{
    VOS_UINT32                          ulRslt              = 0;

    pstLocationCoordianteType->bitOpExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*������Ϣʵ��*/
    pstLocationCoordianteType->bEllipsoidPoint =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstLocationCoordianteType->bEllipsoidPointWithUncertaintyCircle =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstLocationCoordianteType->bEllipsoidPointWithUncertaintyEllipse =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstLocationCoordianteType->bPolygon =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstLocationCoordianteType->bEllipsoidPointWithAltitude =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstLocationCoordianteType->bEllipsoidPointWithAltitudeAndUncertaintyEllipsoid =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstLocationCoordianteType->bEllipsoidArc =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstLocationCoordianteType->bitOpExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_LOCATIONCOORDINATETYPE_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeLocationVelocityTypes
Description     :����VelocityTypes
Input           : ��Ϣ������
Output          : None
ASN             :
    VelocityTypes ::= SEQUENCE {
        horizontalVelocity                                      BOOLEAN,
        horizontalWithVerticalVelocity                          BOOLEAN,
        horizontalVelocityWithUncertainty                       BOOLEAN,
        horizontalWithVerticalVelocityAndUncertainty            BOOLEAN,
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeLocationVelocityTypes
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_VELOCITY_TYPE_STRU             *pstVelocityType
)
{
    VOS_UINT32      ulRslt = 0;

    /*������չ��*/
    pstVelocityType->bitOpExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*������Ϣʵ��*/
    pstVelocityType->bHorizontalVelocity =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstVelocityType->bHorizontalWithVerticalVelocity =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstVelocityType->bHorizontalVelocityWithUncertainty =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstVelocityType->bHorizontalWithVerticalVelocityAndUncertainty =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstVelocityType->bitOpExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_LOCATIONVELOCITYTYPES_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCommonIesReqLocationInfo
Description     :����CommonIEsRequestLocationInformation
Input           : ��Ϣ������
Output          : None
ASN             :
    CommonIEsRequestLocationInformation ::= SEQUENCE {
        locationInformationType     LocationInformationType,
        triggeredReporting          TriggeredReportingCriteria  OPTIONAL,   -- Cond ECID
        periodicalReporting         PeriodicalReportingCriteria OPTIONAL,   -- Need ON
        additionalInformation       AdditionalInformation       OPTIONAL,   -- Need ON
        qos                         QoS                         OPTIONAL,   -- Need ON
        environment                 Environment                 OPTIONAL,   -- Need ON
        locationCoordinateTypes     LocationCoordinateTypes     OPTIONAL,   -- Need ON
        velocityTypes               VelocityTypes               OPTIONAL,   -- Need ON
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCommonIesReqLocationInfo
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_COMMON_IES_REQ_LOCATION_INFO_STRU                  *pstCommonIesReqLocInfo
)
{
    VOS_UINT32                                              ulRslt          = 0;

    /*������չ��*/
    pstCommonIesReqLocInfo->bitOpCommonIEsReqLocationInfoExt =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*�����ѡ��*/
    pstCommonIesReqLocInfo->bitOpTriggeredReportCriteria =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstCommonIesReqLocInfo->bitOpPeriodicalReportCriteria =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstCommonIesReqLocInfo->bitOPAddtionInfo =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstCommonIesReqLocInfo->bitOpQos =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstCommonIesReqLocInfo->bitOpEnvironment =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstCommonIesReqLocInfo->bitOpLocationCoordinateType =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstCommonIesReqLocInfo->bitOPVelocityTypes =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����locationInformationType*/
    ulRslt = NAS_LPP_DecodeLocationInfoType(pucDecodeBitStream, pulCurrentBitPos, 2,
                                          &(pstCommonIesReqLocInfo->enLocationInformationType));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    if(NAS_LPP_EXT_ENUMERATED_BUTT == pstCommonIesReqLocInfo->enLocationInformationType)
    {
        pstCommonIesReqLocInfo->enLocationInformationType = LPP_LOCATION_INFO_TYPE_BUTT;
    }

    /*����triggeredReporting*/
    if(NAS_LPP_SLCT == pstCommonIesReqLocInfo->bitOpTriggeredReportCriteria)
    {
        ulRslt = NAS_LPP_DecodeLocationTriggeredReporting(pucDecodeBitStream, pulCurrentBitPos,
                                                        &(pstCommonIesReqLocInfo->stTriggerReportCriteria));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����periodicalReporting*/
    if(NAS_LPP_SLCT == pstCommonIesReqLocInfo->bitOpPeriodicalReportCriteria)
    {
        ulRslt = NAS_LPP_DecodeLocationPeriodicalReporting(pucDecodeBitStream, pulCurrentBitPos,
                                                         &(pstCommonIesReqLocInfo->stPeriodReport));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����additionalInformation*/
    if(NAS_LPP_SLCT == pstCommonIesReqLocInfo->bitOPAddtionInfo)
    {
        ulRslt = NAS_LPP_DecodeLocationAdditonInfo(pucDecodeBitStream, pulCurrentBitPos, 1,
                                                 &(pstCommonIesReqLocInfo->enAdditonInfo));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����qos*/
    if(NAS_LPP_SLCT == pstCommonIesReqLocInfo->bitOpQos)
    {
        ulRslt = NAS_LPP_DecodeLocationQos(pucDecodeBitStream, pulCurrentBitPos,
                                         &(pstCommonIesReqLocInfo->stQos));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����environment*/
    if(NAS_LPP_SLCT == pstCommonIesReqLocInfo->bitOpEnvironment)
    {
        ulRslt = NAS_LPP_DecodeLocationEnvironment(pucDecodeBitStream, pulCurrentBitPos, 2,
                                                 &(pstCommonIesReqLocInfo->enEnvironment));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����locationCoordinateTypes*/
    if(NAS_LPP_SLCT == pstCommonIesReqLocInfo->bitOpLocationCoordinateType)
    {
        ulRslt = NAS_LPP_DecodeLocationCoordinateType(pucDecodeBitStream, pulCurrentBitPos,
                                                    &(pstCommonIesReqLocInfo->stLocationCoordinateType));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����velocityTypes*/
    if(NAS_LPP_SLCT == pstCommonIesReqLocInfo->bitOPVelocityTypes)
    {
        ulRslt = NAS_LPP_DecodeLocationVelocityTypes(pucDecodeBitStream, pulCurrentBitPos,
                                                   &(pstCommonIesReqLocInfo->stVeloctytype));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstCommonIesReqLocInfo->bitOpCommonIEsReqLocationInfoExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_COMMONIESREQLOCATIONINFO_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssMethods
Description     :����GNSS-ID-Bitmap
Input           : ��Ϣ������
Output          : None
ASN             :
    GNSS-ID-Bitmap ::= SEQUENCE {
        gnss-ids            BIT STRING {    gps         (0),
                                            sbas        (1),
                                            qzss        (2),
                                            galileo     (3),
                                            glonass     (4)  } (SIZE (1..16)),
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssMethods
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ID_BITMAP_STRU            *pstGnssIdBitMap
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��*/
    pstGnssIdBitMap->bitOpGNSSIDBitmapExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����gnss-ids*/
    pstGnssIdBitMap->usGnssIdsCnt =
        (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 4) + 1;
    pstGnssIdBitMap->usGNSSIDs =
        (VOS_UINT16) NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos,
                                                 (VOS_UINT8)(pstGnssIdBitMap->usGnssIdsCnt));

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssIdBitMap->bitOpGNSSIDBitmapExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_GNSSMETHODS_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssPositioningInstructions
Description     :����GNSS-PositioningInstructions
Input           : ��Ϣ������
Output          : None
ASN             :
    GNSS-PositioningInstructions ::= SEQUENCE {
        gnss-Methods                GNSS-ID-Bitmap,
        fineTimeAssistanceMeasReq   BOOLEAN,
        adrMeasReq                  BOOLEAN,
        multiFreqMeasReq            BOOLEAN,
        assistanceAvailability      BOOLEAN,
        ...
    }
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssPositioningInstructions
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_POSITION_INSTRUCTION_STRU *pstGnssPostionInstruction
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��*/
    pstGnssPostionInstruction->bitOpGNSSPositionInstructionExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����gnss-Methods*/
    ulRslt = NAS_LPP_DecodeGnssMethods(pucDecodeBitStream, pulCurrentBitPos,
                                     &(pstGnssPostionInstruction->stGNSSMethods));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����bool*/
    pstGnssPostionInstruction->bFineTimeAssistanceMeasReq =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstGnssPostionInstruction->bAdrMeasReq =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstGnssPostionInstruction->bMultiFreqMeasReq =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstGnssPostionInstruction->bAssistanceAvailability =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssPostionInstruction->bitOpGNSSPositionInstructionExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_GNSSPOSITIONINGINSTRUCT_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeAgnssReqLocationInfo
Description     :����A-GNSS-RequestLocationInformatio
Input           : ��Ϣ������
Output          : None
ASN             :
    A-GNSS-RequestLocationInformation ::= SEQUENCE {
        gnss-PositioningInstructions        GNSS-PositioningInstructions,
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeAgnssReqLocationInfo
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_AGNSS_REQ_LOCATION_INFO_STRU   *pstAgnssReqLocInfo
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��*/
    pstAgnssReqLocInfo->bitOpAGNSSReqLocationInfoExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����PositioningInstructions*/
    ulRslt = NAS_LPP_DecodeGnssPositioningInstructions(pucDecodeBitStream, pulCurrentBitPos,
                                                     &(pstAgnssReqLocInfo->stGNSSPositonINsturction));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstAgnssReqLocInfo->bitOpAGNSSReqLocationInfoExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_AGNSSREQLOCATIONINFO_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeOtdoaReqLocationInfo
Description     :����OTDOA-RequestLocationInformation
Input           : ��Ϣ������
Output          : None
ASN             :
    OTDOA-RequestLocationInformation ::= SEQUENCE {
        assistanceAvailability      BOOLEAN,
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeOtdoaReqLocationInfo
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_OTDOA_REQ_LOCATION_INFO_STRU   *pstOtdoaReqLocInfo
)
{
    VOS_UINT32      ulRslt = 0;

    /*������չ��*/
    pstOtdoaReqLocInfo->bitOpOtdoaReqLocationInfoExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*������Ϣʵ��*/
    pstOtdoaReqLocInfo->bAssistanceAvailability =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstOtdoaReqLocInfo->bitOpOtdoaReqLocationInfoExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_OTDOAREQLOCATIONINFO_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEcellIdReqLocationInfo
Description     :����ECID-RequestLocationInformation
Input           : ��Ϣ������
Output          : None
ASN             :
    ECID-RequestLocationInformation ::= SEQUENCE {
        requestedMeasurements       BIT STRING {    rsrpReq     (0),
                                                    rsrqReq     (1),
                                                    ueRxTxReq   (2) } (SIZE(1..8)),
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEcellIdReqLocationInfo
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_ECID_REQ_LOCATION_INFO_STRU    *pstEcellIdReqLocInfo
)
{
    VOS_UINT32                          ulRslt          = 0;

    /*������չ��*/
    pstEcellIdReqLocInfo->bitOpEcidRequestLocationInformationExt =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����reqMeasurements*/
    pstEcellIdReqLocInfo->stRequestedMeasurements.ucRequestedMeasCnt =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 3) + 1;

    pstEcellIdReqLocInfo->stRequestedMeasurements.ucRequestedMeas =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos,
                                                pstEcellIdReqLocInfo->stRequestedMeasurements.ucRequestedMeasCnt);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstEcellIdReqLocInfo->bitOpEcidRequestLocationInformationExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_ECELLIDREQLOCATIONINFO_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEpduReqLocationInfo
Description     :���� EPDU-Sequence
Input           : ��Ϣ������
Output          : None
ASN             :
    EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

    maxEPDU INTEGER ::= 16

    EPDU ::= SEQUENCE {
        ePDU-Identifier         EPDU-Identifier,
        ePDU-Body               EPDU-Body
    }

    EPDU-Identifier ::= SEQUENCE {
        ePDU-ID                 EPDU-ID,
        ePDU-Name               EPDU-Name       OPTIONAL,
        ...
    }

    EPDU-ID ::= INTEGER (1..256)

    EPDU-Name ::= VisibleString (SIZE (1..32))

    EPDU-Body ::= OCTET STRING


Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEpduReqLocationInfo
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_EPDU_REQ_LOCATION_INFO_STRU    *pstEpduReqLocInfo
)
{
    VOS_UINT32                          ulRslt              = 0;
    /*����SEQUENCE OF*/
    ulRslt = NAS_LPP_DecodeEpduSequence(pucDecodeBitStream, pulCurrentBitPos,
                                       (LPP_EPDU_SEQUENCE_STRU*)pstEpduReqLocInfo);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeReqLocationInfo
Description     :����RequestLocationInformation
Input           : ��Ϣ������
Output          : None
ASN             :
    RequestLocationInformation-r9-IEs ::= SEQUENCE {
        commonIEsRequestLocationInformation
                                        CommonIEsRequestLocationInformation     OPTIONAL,   -- Need ON
        a-gnss-RequestLocationInformation   A-GNSS-RequestLocationInformation   OPTIONAL,   -- Need ON
        otdoa-RequestLocationInformation    OTDOA-RequestLocationInformation    OPTIONAL,   -- Need ON
        ecid-RequestLocationInformation     ECID-RequestLocationInformation     OPTIONAL,   -- Need ON
        epdu-RequestLocationInformation     EPDU-Sequence                       OPTIONAL,   -- Need ON
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeReqLocInfoR9IEs
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_REQ_LOCATION_INFO_R9_IES_STRU  *pstReqLocInfoR9
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չλ*/
    pstReqLocInfoR9->bitOpLPPReqLocationInfoExt =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*�����ѡ��*/
    pstReqLocInfoR9->bitOpCommonIEsReqLocationInfo =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstReqLocInfoR9->bitOpAGNSSReqLocationInfo =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstReqLocInfoR9->bitOpOtdoaReqLocationInfo  =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstReqLocInfoR9->bitOpEcidReqLocationInfo =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    pstReqLocInfoR9->bitOpEpduSequence =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����commonIEsRequestLocationInformation*/
    if(NAS_LPP_SLCT == pstReqLocInfoR9->bitOpCommonIEsReqLocationInfo)
    {
        ulRslt = NAS_LPP_DecodeCommonIesReqLocationInfo(pucDecodeBitStream, pulCurrentBitPos,
                                                      &(pstReqLocInfoR9->stCommonIEsReqLocationInfo));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����a-gnss-RequestLocationInformation*/
    if(NAS_LPP_SLCT == pstReqLocInfoR9->bitOpAGNSSReqLocationInfo)
    {
        ulRslt = NAS_LPP_DecodeAgnssReqLocationInfo(pucDecodeBitStream, pulCurrentBitPos,
                                                  &(pstReqLocInfoR9->stAGNSSReqLocationInfo));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����otdoa-RequestLocationInformation*/
    if(NAS_LPP_SLCT == pstReqLocInfoR9->bitOpOtdoaReqLocationInfo)
    {
        ulRslt = NAS_LPP_DecodeOtdoaReqLocationInfo(pucDecodeBitStream, pulCurrentBitPos,
                                                  &(pstReqLocInfoR9->stOtdoaReqLocationInfo));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����ecid-RequestLocationInformation*/
    if(NAS_LPP_SLCT == pstReqLocInfoR9->bitOpEcidReqLocationInfo)
    {
        ulRslt = NAS_LPP_DecodeEcellIdReqLocationInfo(pucDecodeBitStream, pulCurrentBitPos,
                                                    &(pstReqLocInfoR9->stEcidReqLocationInfo));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����epdu-RequestLocationInformation*/
    if(NAS_LPP_SLCT == pstReqLocInfoR9->bitOpEpduSequence)
    {
        ulRslt = NAS_LPP_DecodeEpduReqLocationInfo(pucDecodeBitStream, pulCurrentBitPos,
                                                 &(pstReqLocInfoR9->stEpduReqLocationInfo));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstReqLocInfoR9->bitOpLPPReqLocationInfoExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_REQLOCINFOR9IES_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeReqLocationInfo
Description     :����RequestLocationInformation
Input           : ��Ϣ������
Output          : None
ASN             :
    c1                      CHOICE {
        requestLocationInformation-r9   RequestLocationInformation-r9-IEs,
        spare3 NULL, spare2 NULL, spare1 NULL
    },
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeExtReqLocationInfo
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_CRITI_EXT_REQ_LOCATION_INFO_STRU                   *pstReqLocationInfo
)
{
    VOS_UINT32                                              ulReturnRslt    = 0;


    /*����ѡ��������*/
    ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 2);
    pstReqLocationInfo->ulChoice = ulReturnRslt;

    switch(ulReturnRslt)
    {
        case LPP_C1_CRITI_EXT_REQ_LOCATION_INFO_R9_CHOSEN:
            ulReturnRslt =NAS_LPP_DecodeReqLocInfoR9IEs(pucDecodeBitStream, pulCurrentBitPos,
                                                      &(pstReqLocationInfo->u.stReqLocationInfoR9));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return  ulReturnRslt;
            }
            break;

        default:
            break;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeReqLocationInfo
Description     :����RequestLocationInformation
Input           : ��Ϣ������
Output          : None
ASN             :
    RequestLocationInformation ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                requestLocationInformation-r9   RequestLocationInformation-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-06-02  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeReqLocationInfo
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_MESSAGE_REQUEST_LOCATION_INFO_STRU                 *pstReqLocationInfo
)
{
    VOS_UINT32                                              ulReturnRslt    = 0;

    /*����choice��*/
    pstReqLocationInfo->ulChoice = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                pulCurrentBitPos, 1);

    switch(pstReqLocationInfo->ulChoice)
    {
        case LPP_C1_CRITI_EXT_REQ_LOCATION_INFO_CHOSEN:
            ulReturnRslt = NAS_LPP_DecodeExtReqLocationInfo(pucDecodeBitStream,pulCurrentBitPos,
                                                          &(pstReqLocationInfo->u.stC1));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return  ulReturnRslt;
            }
            break;
        default:
            break;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeProAssistDataEPDU
Description     :����LPP_EPDU_PROVIDE_ASSIST_DATA_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeProAssistDataEPDU
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_EPDU_PROVIDE_ASSIST_DATA_STRU       *pstProAssistData
)
{
    VOS_UINT32                               ulRslt = 0;

    /*����SEQUENCE OF*/
    ulRslt = NAS_LPP_DecodeEpduSequence(pucDecodeBitStream, pulCurrentBitPos,
                                       (LPP_EPDU_SEQUENCE_STRU*)pstProAssistData);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCellGlobalId
Description     :����LPP_ECGI_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
ECGI ::= SEQUENCE {
    mcc             SEQUENCE (SIZE (3))     OF INTEGER (0..9),
    mnc             SEQUENCE (SIZE (2..3))  OF INTEGER (0..9),
    cellidentity    BIT STRING (SIZE (28))
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCellGlobalId
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_ECGI_STRU                           *pstCellGloballId
)
{
    VOS_UINT32  ulRslt = 0;

    /*����plmn-identity*/
    ulRslt = NAS_LPP_DecodePlmnIdentity(pucDecodeBitStream, pulCurrentBitPos,
                                        &(pstCellGloballId->stPlmnIdentity));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����Cellidentity*/
    pstCellGloballId->ulCellIdentity = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                    pulCurrentBitPos, 28);

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEarfcnRef
Description     :����LPP_ARFCN_VALUE_EUTRA_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
ARFCN-ValueEUTRA ::= INTEGER (0..maxEARFCN)
maxEARFCN   INTEGER ::= 65535   -- Maximum value of EUTRA carrier frequency

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_DecodeEarfcnRef(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_ARFCN_VALUE_EUTRA_STRU              *pstArfcnValueEutra)
{
    /*����arfcn-valueeutra*/
    pstArfcnValueEutra->ulArfcnValueEUTRA = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                        pulCurrentBitPos, 16);

}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeAntennaPortConfig
Description     :����LPP_ANTENNA_PORT_CONFIG_ENUM_UINT8
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeAntennaPortConfig
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT8                           ucLen,
    LPP_ANTENNA_PORT_CONFIG_ENUM_UINT8 *penAntenaPortConfig
)
{
    VOS_UINT32      ulRslt = 0;

    ulRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                        ucLen, penAntenaPortConfig);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ANTENNAPORTCONFIG_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  ulRslt;
    }
    if(NAS_LPP_EXT_ENUMERATED_BUTT == *penAntenaPortConfig)
    {
        *penAntenaPortConfig = LPP_ANTENNA_PORT_CONFIG_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ANTENNAPORTCONFIG_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCpLength
Description     :����LPP_CP_LENGTH_ENUM_UINT8
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCpLength
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    VOS_UINT8                               ucLen,
    LPP_CP_LENGTH_ENUM_UINT8                *penCpLength
)
{
    VOS_UINT32      ulRslt = 0;

    ulRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                        ucLen, penCpLength);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_CPLENGTH_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                 *pulCurrentBitPos, __LINE__, 0);
        return  ulRslt;
    }
    if(NAS_LPP_EXT_ENUMERATED_BUTT == *penCpLength)
    {
        *penCpLength = LPP_CP_LENGTH_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_CPLENGTH_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                 *pulCurrentBitPos, __LINE__, 0);
    }
    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodePrsBandWidth
Description     :����NAS_LPP_DecodePrsBandWidth
Input           : ��Ϣ������
Output          : None
ASN             :
prs-Bandwidth           ENUMERATED { n6, n15, n25, n50, n75, n100, ... },

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodePrsBandWidth
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT8                           ucLen,
    LPP_PRS_BAND_WITH_ENUM_UINT8       *penPrsBandwidth
)
{
    VOS_UINT32                          ulRslt              = 0;

    ulRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                         ucLen, penPrsBandwidth);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRSBANDWIDTH_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                    *pulCurrentBitPos, __LINE__, 0);
        return  ulRslt;
    }
    if((NAS_LPP_EXT_ENUMERATED_BUTT == *penPrsBandwidth)||(*penPrsBandwidth > 5))
    {
        *penPrsBandwidth = LPP_PRS_BAND_WITH_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRSBANDWIDTH_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeNumDlFrames
Description     :����LPP_NUMDL_FRAMES_ENUM_UINT8
Input           : ��Ϣ������
Output          : None
ASN             :
numDL-Frames            ENUMERATED {sf-1, sf-2, sf-4, sf-6, ...},

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeNumDlFrames
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    VOS_UINT8                               ucLen,
    LPP_NUMDL_FRAMES_ENUM_UINT8            *penFreames
)
{
    VOS_UINT32      ulRslt = 0;

    ulRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                        ucLen, penFreames);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_NUMDIFRAMES_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  ulRslt;
    }
    if(NAS_LPP_EXT_ENUMERATED_BUTT == *penFreames)
    {
        *penFreames = LPP_NUMDL_FRAMES_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_NUMDIFRAMES_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeExtChoice
Description     :�������չchoice��
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982         2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeExtChoice
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT8                           ucLen,
    VOS_UINT32                         *pExtChoiceValue
)
{
    VOS_UINT32                          ulRslt              = 0;
    VOS_UINT32                          ulReturnValue       = 0;

    ulReturnValue = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    /*���Ϊ1����ͨ�õ�С�ķǸ�����������룬�����ó�LPP_DECODE_EXT_CHOICE_INVALID_VALUE*/
    if(0 != ulReturnValue)
    {
        ulRslt = NAS_LPP_DecodeNormalSmallInt(pucDecodeBitStream, pulCurrentBitPos, &ulReturnValue);
        if (NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
        *pExtChoiceValue = LPP_DECODE_EXT_CHOICE_INVALID_VALUE;

    }
    else
    {
        *pExtChoiceValue = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, ucLen);
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeExtChoiceClockMoel
Description     :�������չchoice��
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982         2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeExtChoiceMutingInfo(
                                    VOS_UINT8                       *pucDecodeBitStream,
                                    VOS_UINT32                      *pulCurrentBitPos,
                                    VOS_UINT8                       ucLen,
                                    VOS_UINT32                      *pExtChoiceValue)
{
    VOS_UINT32      ulRslt = 0;

    ulRslt = NAS_LPP_DecodeExtChoice(pucDecodeBitStream, pulCurrentBitPos, ucLen, pExtChoiceValue);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    if(LPP_DECODE_EXT_CHOICE_INVALID_VALUE == *pExtChoiceValue)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_MUTINGINFO_ERROR, NAS_LPP_CHOICE_EXT_OBJECT_ERROR, *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeNumDlFrames
Description     :����LPP_NUMDL_FRAMES_ENUM_UINT8
Input           : ��Ϣ������
Output          : None
ASN             :
prs-MutingInfo-r9       CHOICE {
    po2-r9                  BIT STRING (SIZE(2)),
    po4-r9                  BIT STRING (SIZE(4)),
    po8-r9                  BIT STRING (SIZE(8)),
    po16-r9                 BIT STRING (SIZE(16)),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodePrsMutingInfoR9(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_PRS_MUTING_INFO_R9_STRU             *pstMutingInfoR9)
{
    VOS_UINT32      ulMutingInfoLen = 0;
    VOS_UINT32      ulRslt = 0;

    /*������չ���L+V*/
    ulMutingInfoLen = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

    /*����V*/
    /*����choice��*/
    ulRslt= NAS_LPP_DecodeExtChoiceMutingInfo(pucDecodeBitStream, pulCurrentBitPos, 2, &(pstMutingInfoR9->ulChoice));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*�ж�L+V�ĺϷ���*/
    switch(pstMutingInfoR9->ulChoice)
    {
        case LPP_PRS_MUTING_INFO_PO2_R9_CHOSEN:
        case LPP_PRS_MUTING_INFO_PO4_R9_CHOSEN:
             if(ulMutingInfoLen != 1)
             {
                NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRSMUTINGINFOR9_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos, __LINE__, 0);
                 return NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_LV_VALUE_MISMATCH;
             }
             break;

        case LPP_PRS_MUTING_INFO_PO8_R9_CHOSEN:
            if(ulMutingInfoLen != 2)
            {
                NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRSMUTINGINFOR9_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos, __LINE__, 0);
                return NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_LV_VALUE_MISMATCH;
            }
            break;

        default:
            if(ulMutingInfoLen != 3)
            {
                NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRSMUTINGINFOR9_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos, __LINE__, 0);
                return NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_LV_VALUE_MISMATCH;
            }
            break;
    }

    /*��������ֵ��*/
    switch(pstMutingInfoR9->ulChoice)
    {
        case LPP_PRS_MUTING_INFO_PO2_R9_CHOSEN:
             pstMutingInfoR9->u.usPo2R9 = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 2);
             /*��������Ĳ���, ����1���ֽ��ܹ�ռ����5��bit�����Ի���Ҫ��������3��bit*/
             *pulCurrentBitPos += 3;
             break;

        case LPP_PRS_MUTING_INFO_PO4_R9_CHOSEN:
             pstMutingInfoR9->u.usPo4R9 = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 4);
             /*��������Ĳ���, ����1���ֽ��ܹ�ռ����7��bit�����Ի���Ҫ��������1��bit*/
             *pulCurrentBitPos += 1;
             break;

        case LPP_PRS_MUTING_INFO_PO8_R9_CHOSEN:
             pstMutingInfoR9->u.usPo8R9 = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
             /*��������Ĳ���, ����2���ֽ��ܹ�ռ����11��bit�����Ի���Ҫ��������5��bit*/
             *pulCurrentBitPos += 5;
             break;

        default:
             pstMutingInfoR9->u.usPo16R9 = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16);
             /*��������Ĳ���, ����3���ֽ��ܹ�ռ����19��bit�����Ի���Ҫ��������5��bit*/
             *pulCurrentBitPos += 5;
             break;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodePrsInfo
Description     :����LPP_PRS_INFO_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
PRS-Info ::= SEQUENCE {
    prs-Bandwidth           ENUMERATED { n6, n15, n25, n50, n75, n100, ... },
    prs-ConfigurationIndex  INTEGER (0..4095),
    numDL-Frames            ENUMERATED {sf-1, sf-2, sf-4, sf-6, ...},
    ...,
    prs-MutingInfo-r9       CHOICE {
        po2-r9                  BIT STRING (SIZE(2)),
        po4-r9                  BIT STRING (SIZE(4)),
        po8-r9                  BIT STRING (SIZE(8)),
        po16-r9                 BIT STRING (SIZE(16)),
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodePrsInfo(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_PRS_INFO_STRU                       *pstPrsInfo)
{
    VOS_UINT32      ulRslt = 0;
    VOS_UINT32      ulExtIeNum = 0;
    VOS_UINT32      ulLoop = 0;
    VOS_UINT32      ulExtIeOptionEarfcnV9a0 = 0;
    VOS_UINT32      ulExtIeInValidNum = 0;
    VOS_UINT32      ulExtIeInvalidOption = 0;

    /*������չ��*/
    pstPrsInfo->bitOpPrsInfoExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                pulCurrentBitPos, 1);

    /*����prs-bandwidth*/
    ulRslt = NAS_LPP_DecodePrsBandWidth(pucDecodeBitStream, pulCurrentBitPos, 3,
                                                            &(pstPrsInfo->enPrsBandWith));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����prs-configindex*/
    pstPrsInfo->ulPrsConfigIndex = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                pulCurrentBitPos, 12);

    /*����numDL-Frames*/
    ulRslt = NAS_LPP_DecodeNumDlFrames(pucDecodeBitStream, pulCurrentBitPos, 2,
                                       &(pstPrsInfo->enNumDlFrames));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*û��ѡ����չ��*/
    if(NAS_LPP_NO_SLCT == pstPrsInfo->bitOpPrsInfoExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*ѡ����չ��*/
    /*������չ��ļ���L-1*/
    ulRslt = NAS_LPP_DecodeNormalSmallInt(pucDecodeBitStream, pulCurrentBitPos,
                                            &ulExtIeNum);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    /*�����������չ��ļ�����1����ʾ�����������İ汾����չ��ļ���*/
    ulExtIeNum += 1;

    /*�����Э��汾һ����չ���option*/
    ulExtIeOptionEarfcnV9a0 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                            pulCurrentBitPos, 1);
    pstPrsInfo->bitOpPrsMutingInfoR9 = ulExtIeOptionEarfcnV9a0;

    /*�����Э��汾��һ����չ���option*/
    for(ulLoop = 0; ulLoop < ulExtIeNum - 1; ulLoop++)
    {
        ulExtIeInvalidOption = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                            pulCurrentBitPos, 1);
        if(NAS_LPP_SLCT == ulExtIeInvalidOption)
        {
            ulExtIeInValidNum++;
        }
    }

    /*������չ��ľ����ֵ*/
    /*����Э��汾һ�µ���Ԫ*/
    if(NAS_LPP_SLCT == pstPrsInfo->bitOpPrsMutingInfoR9)
    {
        ulRslt = NAS_LPP_DecodePrsMutingInfoR9(pucDecodeBitStream, pulCurrentBitPos,
                                                &(pstPrsInfo->stPrsMutingInfoR9));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*�����ǰ��չ��ļ�����UE�汾����չ��ļ�����ȣ���˵��Э��汾һ�£��������*/
    if(1 == ulExtIeNum)
    {
        return NAS_LPP_DECODE_SUCC;
    }
    else
    {
        /*Э��汾�ȱ��ظߣ�����Ҫ����ѭ������ʣ�µ�IE��*/
        ulRslt = NAS_LPP_DecodeExtIeWithPartValid(pucDecodeBitStream, pulCurrentBitPos, ulExtIeInValidNum);
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_PRSINFO_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                    *pulCurrentBitPos, __LINE__,0);
            return ulRslt;
        }

        return NAS_LPP_DECODE_SUCC;
    }
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeOtdoaRefCellInfo
Description     :����LPP_OTDOA_REF_CELL_INFO_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
OTDOA-ReferenceCellInfo ::= SEQUENCE {
    physCellId                  INTEGER (0..503),
    cellGlobalId                ECGI                        OPTIONAL,       -- Need ON
    earfcnRef                   ARFCN-ValueEUTRA            OPTIONAL,       -- Cond NotSameAsServ0
    antennaPortConfig           ENUMERATED {ports1-or-2, ports4, ... }
                                                            OPTIONAL,       -- Cond NotSameAsServ1
    cpLength                    ENUMERATED { normal, extended, ... },
    prsInfo                     PRS-Info                    OPTIONAL,       -- Cond PRS
    ...,
    [[ earfcnRef-v9a0           ARFCN-ValueEUTRA-v9a0       OPTIONAL        -- Cond NotSameAsServ2
    ]]
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeOtdoaRefCellInfo
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_OTDOA_REF_CELL_INFO_STRU            *pstOtdoaRefCellInfo
)
{
    VOS_UINT32      ulRslt = 0;
    VOS_UINT32      ulExtIeNum = 0;
    VOS_UINT32      ulLoop = 0;
    VOS_UINT32      ulExtIeOptionEarfcnV9a0 = 0;
    VOS_UINT32      ulExtIeInValidNum = 0;
    VOS_UINT32      ulExtIeInvalidOption = 0;

    /*������չ��*/
    pstOtdoaRefCellInfo->bitOpOtdoaRefCellInfoExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����option*/
    pstOtdoaRefCellInfo->bitOpCellGlobalId = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstOtdoaRefCellInfo->bitOpEarFcnRef = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstOtdoaRefCellInfo->bitOpAntennaPortConfig = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstOtdoaRefCellInfo->bitOpPrsInfo = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����physcellid*/
    pstOtdoaRefCellInfo->usPhyCellId = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 9);
    if(pstOtdoaRefCellInfo->usPhyCellId > 503)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_OTDOAREFCELLINFO_ERROR,
                                    NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pulCurrentBitPos,
                                    __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����ECGI*/
    if(NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpCellGlobalId)
    {
        ulRslt = NAS_LPP_DecodeCellGlobalId(    pucDecodeBitStream, pulCurrentBitPos,
                                                &(pstOtdoaRefCellInfo->stCellGlobalId));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����earfcnRef*/
    if(NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpEarFcnRef)
    {
        NAS_LPP_DecodeEarfcnRef(   pucDecodeBitStream, pulCurrentBitPos,
                                            &(pstOtdoaRefCellInfo->stEarfcnRef));

    }

    /*����portconfig*/
    if(NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpAntennaPortConfig)
    {
        ulRslt = NAS_LPP_DecodeAntennaPortConfig(pucDecodeBitStream, pulCurrentBitPos,
                                                 1, &(pstOtdoaRefCellInfo->enAntennaPortConfig));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }
    /*����cpLength*/
    ulRslt = NAS_LPP_DecodeCpLength(pucDecodeBitStream, pulCurrentBitPos, 1,
                                    &(pstOtdoaRefCellInfo->enCpLength));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����prsInfo*/
    if(NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpPrsInfo)
    {
        ulRslt = NAS_LPP_DecodePrsInfo(pucDecodeBitStream, pulCurrentBitPos,
                                        &(pstOtdoaRefCellInfo->stPrsInfo));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*û��ѡ����չ��*/
    if(NAS_LPP_NO_SLCT == pstOtdoaRefCellInfo->bitOpOtdoaRefCellInfoExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*ѡ����չ��*/
    /*������չ��ļ���L-1*/
    ulRslt = NAS_LPP_DecodeNormalSmallInt(pucDecodeBitStream, pulCurrentBitPos,
                                           &ulExtIeNum);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    /*�����������չ��ļ�����1����ʾ�����������İ汾����չ��ļ���*/
    ulExtIeNum += 1;

    /*�����Э��汾һ����չ���option*/
    ulExtIeOptionEarfcnV9a0 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                            pulCurrentBitPos, 1);
    pstOtdoaRefCellInfo->bitOpEarfcnRefV9a0 = ulExtIeOptionEarfcnV9a0;

    /*�����Э��汾��һ����չ���option*/
    for(ulLoop = 0; ulLoop < ulExtIeNum - 1; ulLoop++)
    {
        ulExtIeInvalidOption = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                            pulCurrentBitPos, 1);
        if(NAS_LPP_SLCT == ulExtIeInvalidOption)
        {
            ulExtIeInValidNum++;
        }
    }

    /*������չ��ľ����ֵ*/
    /*����Э��汾һ�µ���Ԫ*/
    if(NAS_LPP_SLCT == pstOtdoaRefCellInfo->bitOpEarfcnRefV9a0)
    {
        ulRslt = NAS_LPP_DecodeArfcnEutranV9a0(pucDecodeBitStream, pulCurrentBitPos,
                                                &(pstOtdoaRefCellInfo->stEarfcnRefV9a0));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*�����ǰ��չ��ļ�����UE�汾����չ��ļ�����ȣ���˵��Э��汾һ�£��������*/
    if(1 == ulExtIeNum)
    {
        return NAS_LPP_DECODE_SUCC;
    }
    else
    {
        /*Э��汾�ȱ��ظߣ�����Ҫ����ѭ������ʣ�µ�IE��*/
        ulRslt = NAS_LPP_DecodeExtIeWithPartValid(pucDecodeBitStream, pulCurrentBitPos,
                                                  ulExtIeInValidNum);
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_OTDOAREFCELLINFO_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                     *pulCurrentBitPos, __LINE__,0);
            return ulRslt;
        }

        return NAS_LPP_DECODE_SUCC;
    }
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeOtdoaNeighbourCellInfoElement
Description     :����LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
OTDOA-NeighbourCellInfoElement ::= SEQUENCE {
    physCellId                          INTEGER (0..503),
    cellGlobalId                        ECGI                OPTIONAL,       -- Need ON
    earfcn                              ARFCN-ValueEUTRA    OPTIONAL,       -- Cond NotSameAsRef0
    cpLength                            ENUMERATED {normal, extended, ...}
                                                            OPTIONAL,       -- Cond NotSameAsRef1
    prsInfo                             PRS-Info            OPTIONAL,       -- Cond NotSameAsRef2
    antennaPortConfig                   ENUMERATED {ports-1-or-2, ports-4, ...}
                                                            OPTIONAL,       -- Cond NotsameAsRef3
    slotNumberOffset                    INTEGER (0..19)     OPTIONAL,       -- Cond NotSameAsRef4
    prs-SubframeOffset                  INTEGER (0..1279)   OPTIONAL,       -- Cond InterFreq
    expectedRSTD                        INTEGER (0..16383),
    expectedRSTD-Uncertainty            INTEGER (0..1023),
    ...,
    [[ earfcn-v9a0          ARFCN-ValueEUTRA-v9a0           OPTIONAL        -- Cond NotSameAsRef5
    ]]
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeOtdoaNeighbourCellInfoElement
(
    VOS_UINT8                                   *pucDecodeBitStream,
    VOS_UINT32                                  *pulCurrentBitPos,
    LPP_OTDOA_NEIGHBOUR_CELL_INFO_ELEMENT_STRU  *pstOtdoaNeighBourFreqElement
)
{
    VOS_UINT32      ulRslt                  = 0;
    VOS_UINT32      ulExtIeNum              = 0;
    VOS_UINT32      ulLoop                  = 0;
    VOS_UINT32      ulExtIeOptionEarfcnV9a0 = 0;
    VOS_UINT32      ulExtIeInValidNum       = 0;
    VOS_UINT32      ulExtIeInvalidOption    = 0;

    /*������չ��*/
    pstOtdoaNeighBourFreqElement->bitOpNeighbourCellInfoElementExt = NAS_LPP_GetDataFromBitStream(
                                                                                                pucDecodeBitStream,
                                                                                                pulCurrentBitPos, 1);

    /*����option*/
    pstOtdoaNeighBourFreqElement->bitOpCellGlobalId = NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstOtdoaNeighBourFreqElement->bitOpEarfcn = NAS_LPP_GetDataFromBitStream(
                                                                            pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);
    pstOtdoaNeighBourFreqElement->bitOpCpLength = NAS_LPP_GetDataFromBitStream(
                                                                            pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);
    pstOtdoaNeighBourFreqElement->bitOpPrsInfo = NAS_LPP_GetDataFromBitStream(
                                                                            pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);
    pstOtdoaNeighBourFreqElement->bitOpAntennaPortconfig = NAS_LPP_GetDataFromBitStream(
                                                                            pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);
    pstOtdoaNeighBourFreqElement->bitOpSlotNumberOffset = NAS_LPP_GetDataFromBitStream(
                                                                            pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);
    pstOtdoaNeighBourFreqElement->bitOpPrsSubFrameOffset = NAS_LPP_GetDataFromBitStream(
                                                                            pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);

    /*����physcellid*/
    pstOtdoaNeighBourFreqElement->ulPhysCellId = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(
                                                                                        pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 9);
    if(pstOtdoaNeighBourFreqElement->ulPhysCellId > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_OTDOANEIGHBOURCELLINFOELEMENT_ERROR,
                                NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pulCurrentBitPos, __LINE__,
                                pstOtdoaNeighBourFreqElement->ulPhysCellId);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����ECGI*/
    if(NAS_LPP_SLCT == pstOtdoaNeighBourFreqElement->bitOpCellGlobalId)
    {
        ulRslt = NAS_LPP_DecodeCellGlobalId(pucDecodeBitStream, pulCurrentBitPos,
                                            &(pstOtdoaNeighBourFreqElement->stCellGlobalId));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����earfcnRef*/
    if(NAS_LPP_SLCT == pstOtdoaNeighBourFreqElement->bitOpEarfcn)
    {
        NAS_LPP_DecodeEarfcnRef(pucDecodeBitStream, pulCurrentBitPos,
                                       &(pstOtdoaNeighBourFreqElement->stEarfcn));

    }

    /*����cpLength*/
    if(NAS_LPP_SLCT == pstOtdoaNeighBourFreqElement->bitOpCpLength)
    {
        ulRslt = NAS_LPP_DecodeCpLength(pucDecodeBitStream, pulCurrentBitPos, 1,
                                        &(pstOtdoaNeighBourFreqElement->enCpLength));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����prsInfo*/
    if(NAS_LPP_SLCT == pstOtdoaNeighBourFreqElement->bitOpPrsInfo)
    {
        ulRslt = NAS_LPP_DecodePrsInfo(pucDecodeBitStream, pulCurrentBitPos,
                                      &(pstOtdoaNeighBourFreqElement->stPrsInfo));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����portconfig*/
    if(NAS_LPP_SLCT == pstOtdoaNeighBourFreqElement->bitOpAntennaPortconfig)
    {
        ulRslt = NAS_LPP_DecodeAntennaPortConfig(pucDecodeBitStream, pulCurrentBitPos,
                                                1, &(pstOtdoaNeighBourFreqElement->enAntennaPortConfig));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����slotOffset*/
    if(NAS_LPP_SLCT == pstOtdoaNeighBourFreqElement->bitOpSlotNumberOffset)
    {
        pstOtdoaNeighBourFreqElement->usSlotNumberOffset = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(
                                                                                                    pucDecodeBitStream,
                                                                                                    pulCurrentBitPos, 5);
        if(pstOtdoaNeighBourFreqElement->usSlotNumberOffset > 19)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_OTDOANEIGHBOURCELLINFOELEMENT_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pulCurrentBitPos,
                                     __LINE__, 0);
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
    }

    /*����subframeoffset*/
    if(NAS_LPP_SLCT == pstOtdoaNeighBourFreqElement->bitOpPrsSubFrameOffset)
    {
        pstOtdoaNeighBourFreqElement->usPrsSubframeOffset = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(
                                                                                                    pucDecodeBitStream,
                                                                                                    pulCurrentBitPos, 11);
    }

    /*����rstd*/
    pstOtdoaNeighBourFreqElement->usExpectedRSTD = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(
                                                                                            pucDecodeBitStream,
                                                                                            pulCurrentBitPos, 14);

    /*����rstd-uncertainty*/
    pstOtdoaNeighBourFreqElement->usExpectedRSTDUncertainty = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(
                                                                                                    pucDecodeBitStream,
                                                                                                    pulCurrentBitPos, 10);


    /*û��ѡ����չ��*/
    if(NAS_LPP_NO_SLCT == pstOtdoaNeighBourFreqElement->bitOpNeighbourCellInfoElementExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*ѡ����չ��*/
    /*������չ��ļ���L-1*/
    ulRslt = NAS_LPP_DecodeNormalSmallInt(pucDecodeBitStream, pulCurrentBitPos, &ulExtIeNum);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    /*�����������չ��ļ�����1����ʾ�����������İ汾����չ��ļ���*/
    ulExtIeNum += 1;

    /*�����Э��汾һ����չ���option*/
    ulExtIeOptionEarfcnV9a0 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstOtdoaNeighBourFreqElement->bitOpEarfcnV9a0 = ulExtIeOptionEarfcnV9a0;

    /*�����Э��汾��һ����չ���option*/
    for(ulLoop = 0; ulLoop < ulExtIeNum - 1; ulLoop++)
    {
        ulExtIeInvalidOption = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
        if(NAS_LPP_SLCT == ulExtIeInvalidOption)
        {
            ulExtIeInValidNum++;
        }
    }

    /*������չ��ľ����ֵ*/
    /*����Э��汾һ�µ���Ԫ*/
    if(NAS_LPP_SLCT == pstOtdoaNeighBourFreqElement->bitOpEarfcnV9a0)
    {
        ulRslt = NAS_LPP_DecodeArfcnEutranV9a0(pucDecodeBitStream, pulCurrentBitPos,
                                                &(pstOtdoaNeighBourFreqElement->stEarfcnv9a0));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*�����ǰ��չ��ļ�����UE�汾����չ��ļ�����ȣ���˵��Э��汾һ�£��������*/
    if(1 == ulExtIeNum)
    {
        return NAS_LPP_DECODE_SUCC;
    }
    else
    {
        /*Э��汾�ȱ��ظߣ�����Ҫ����ѭ������ʣ�µ�IE��*/
        ulRslt = NAS_LPP_DecodeExtIeWithPartValid(pucDecodeBitStream, pulCurrentBitPos,
                                                    ulExtIeInValidNum);
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_OTDOANEIGHBOURCELLINFOELEMENT_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos,
                                    __LINE__,0);
            return ulRslt;
        }

        return NAS_LPP_DECODE_SUCC;
    }
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeNeighbourCellInfoList
Description     :����LPP_OTDOA_NEIGHBOUR_FREQ_INFO_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
OTDOA-NeighbourFreqInfo ::= SEQUENCE (SIZE (1..24)) OF OTDOA-NeighbourCellInfoElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeOtdoaNeighbourCellInfoList
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_OTDOA_NEIGHBOUR_FREQ_INFO_STRU      *pstOtdoaNeighBourFreqInfo
)
{
    VOS_UINT32      ulRslt              = 0;
    VOS_UINT32      ulNeiFreqInfoNum    = 0;
    VOS_UINT32      ulLoop              = 0;

    /*�������ֵ*/
    ulNeiFreqInfoNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 5);
    ulNeiFreqInfoNum += 1;
    if((ulNeiFreqInfoNum < 1) || (ulNeiFreqInfoNum > 24))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOANEIGHBOURCELLINFOLIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                 *pulCurrentBitPos, __LINE__, 0);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    pstOtdoaNeighBourFreqInfo->ulOtdoaNeighbourFreqInfoCnt = ulNeiFreqInfoNum;

    for(ulLoop = 0; ulLoop < pstOtdoaNeighBourFreqInfo->ulOtdoaNeighbourFreqInfoCnt ; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeOtdoaNeighbourCellInfoElement(pucDecodeBitStream, pulCurrentBitPos,
                                                            &(pstOtdoaNeighBourFreqInfo->astOtdoaNeighbourFreqInfoArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeOtdoaNeighbourCellInfo
Description     :����LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
OTDOA-NeighbourCellInfoList ::= SEQUENCE (SIZE (1..maxFreqLayers)) OF OTDOA-NeighbourFreqInfo

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeOtdoaNeighbourCellInfo
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_OTDOA_NEIGHOUR_CELL_INFO_STRU       *pstOtdoaNeiCellInfo
)
{
    VOS_UINT32      ulRslt                  = 0;
    VOS_UINT32      ulLoop                  = 0;
    VOS_UINT32      ulNeighbourCellInfoNum  = 0;

    /*�������ֵ*/
    ulNeighbourCellInfoNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 2);
    ulNeighbourCellInfoNum += 1;
    if((ulNeighbourCellInfoNum < 1) || (ulNeighbourCellInfoNum > 3))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOANEIGHBOURCELLINFO_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                 *pulCurrentBitPos, __LINE__, 0);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    pstOtdoaNeiCellInfo->ulOtdoaNeighbourCellInfoListCnt = ulNeighbourCellInfoNum;

    for(ulLoop = 0; ulLoop < pstOtdoaNeiCellInfo->ulOtdoaNeighbourCellInfoListCnt ; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeOtdoaNeighbourCellInfoList(pucDecodeBitStream, pulCurrentBitPos,
                                                          &(pstOtdoaNeiCellInfo->astOtdoaNeighourFreqInfoArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssLocationServerErrorCause
Description     :����LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT8
Input           : ��Ϣ������
Output          : None
ASN             :
cause       ENUMERATED  {   undefined,
                            assistanceDataNotSupportedByServer,
                            assistanceDataSupportedButCurrentlyNotAvailableByServer,
                            ...
                        },

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin          2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32      NAS_LPP_DecodeOtdoaLocationServerErrorCause
(
    VOS_UINT8                       *pucDecodeBitStream,
    VOS_UINT32                      *pulCurrentBitPos,
    VOS_UINT8                       ucLen,
    LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT8   *penLocSerErrorCause
)
{
    VOS_UINT32      ulReturnRslt = 0;

    ulReturnRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                                ucLen, penLocSerErrorCause);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOALOCATIONSERVERERRORCAUSE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                    *pulCurrentBitPos, __LINE__, 0);
        return  ulReturnRslt;
    }
    if((NAS_LPP_EXT_ENUMERATED_BUTT == *penLocSerErrorCause)||(*penLocSerErrorCause > 2))
    {
        *penLocSerErrorCause = LPP_OTDOA_LOCATION_SERVER_ERROR_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOALOCATIONSERVERERRORCAUSE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssErrorLocationServer
Description     :����LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
OTDOA-LocationServerErrorCauses ::= SEQUENCE {
    cause       ENUMERATED  {   undefined,
                                assistanceDataNotSupportedByServer,
                                assistanceDataSupportedButCurrentlyNotAvailableByServer,
                                ...
                            },
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982          2015-05-25  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeOtdoaErrorLocationServer(
            VOS_UINT8                               *pucDecodeBitStream,
            VOS_UINT32                              *pulCurrentBitPos,
            LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_STRU    *pstOtdoaLocationServerError)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��*/
    pstOtdoaLocationServerError->bitOpOtdoaLocationServerErrorCauseExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����ö��Cause*/
    ulRslt = NAS_LPP_DecodeOtdoaLocationServerErrorCause(pucDecodeBitStream, pulCurrentBitPos, 2, &(pstOtdoaLocationServerError->enOtdoaLocationServerErrorCause));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstOtdoaLocationServerError->bitOpOtdoaLocationServerErrorCauseExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_OTDOAERRORLOCATIONSERVER_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssTargetDeviceErrorCause
Description     :����LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT8
Input           : ��Ϣ������
Output          : None
ASN             :
cause       ENUMERATED {    undefined,
                            assistance-data-missing,
                            unableToMeasureReferenceCell,
                            unableToMeasureAnyNeighbourCell,
                            attemptedButUnableToMeasureSomeNeighbourCells,
                            ...
                        },

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin          2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32    NAS_LPP_DecodeOtdoaTargetDeviceErrorCause
(
    VOS_UINT8                           *pucDecodeBitStream,
    VOS_UINT32                          *pulCurrentBitPos,
    VOS_UINT8                            ucLen,
    LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT8   *penTarDeviceErrorCause)
{
    VOS_UINT32      ulReturnRslt    = 0;

    ulReturnRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                                ucLen, penTarDeviceErrorCause);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOATARGETDEVICEERRORCAUSE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  ulReturnRslt;
    }
    if((NAS_LPP_EXT_ENUMERATED_BUTT == *penTarDeviceErrorCause)||(*penTarDeviceErrorCause > 4))
    {
        *penTarDeviceErrorCause = LPP_OTDOA_LOCATION_SERVER_ERROR_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOATARGETDEVICEERRORCAUSE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssErrorLocationServer
Description     :����LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
OTDOA-TargetDeviceErrorCauses ::= SEQUENCE {
    cause       ENUMERATED {    undefined,
                                assistance-data-missing,
                                unableToMeasureReferenceCell,
                                unableToMeasureAnyNeighbourCell,
                                attemptedButUnableToMeasureSomeNeighbourCells,
                                ...
                            },
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982          2015-05-25  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeOtdoaTargetDevice(
            VOS_UINT8                               *pucDecodeBitStream,
            VOS_UINT32                              *pulCurrentBitPos,
            LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_STRU *pstOtdoaTargetDeviceError)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��*/
    pstOtdoaTargetDeviceError->bitOpOtdoaTargetDeviceErrorCauseExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����ö��Cause*/
    ulRslt = NAS_LPP_DecodeOtdoaTargetDeviceErrorCause(pucDecodeBitStream, pulCurrentBitPos, 3, (LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT8 *)(&(pstOtdoaTargetDeviceError->enOtoaTargetDeviceErrorCause)));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstOtdoaTargetDeviceError->bitOpOtdoaTargetDeviceErrorCauseExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_OTDOATARGETDEVICE_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeOtdoaError
Description     :����LPP_OTDOA_ERROR_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
OTDOA-Error ::= CHOICE {
    locationServerErrorCauses       OTDOA-LocationServerErrorCauses,
    targetDeviceErrorCauses         OTDOA-TargetDeviceErrorCauses,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeOtdoaError(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_OTDOA_ERROR_STRU                    *pstOtdoaError)
{
    VOS_UINT32          ulRslt = 0;

     /*�������չ��choic�����С�ķǸ�������������*/
     ulRslt = NAS_LPP_DecodeExtChoice(pucDecodeBitStream, pulCurrentBitPos, 1, &(pstOtdoaError->ulChoice));
     if(NAS_LPP_DECODE_SUCC != ulRslt)
     {
         return ulRslt;
     }
     if(LPP_DECODE_EXT_CHOICE_INVALID_VALUE == pstOtdoaError->ulChoice)
     {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOAERROR_ERROR, NAS_LPP_CHOICE_EXT_OBJECT_ERROR, *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_CHOICE_ERROR;
     }
     switch(pstOtdoaError->ulChoice)
     {
         case LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_CHOSEN:
             ulRslt = NAS_LPP_DecodeOtdoaErrorLocationServer(pucDecodeBitStream, pulCurrentBitPos, &(pstOtdoaError->u.stLocationServerErrorCauses));
             if(NAS_LPP_DECODE_SUCC != ulRslt)
             {
                 return ulRslt;
             }
             break;

         default:
             ulRslt = NAS_LPP_DecodeOtdoaTargetDevice(pucDecodeBitStream, pulCurrentBitPos, &(pstOtdoaError->u.stTargetDeviceErrorCauses));
             if(NAS_LPP_DECODE_SUCC != ulRslt)
             {
                 return ulRslt;
             }
             break;
     }
     return NAS_LPP_DECODE_SUCC;

}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeProAssistDataOTDOA
Description     :����LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
OTDOA-ProvideAssistanceData ::= SEQUENCE {
        otdoa-ReferenceCellInfo         OTDOA-ReferenceCellInfo             OPTIONAL,   -- Need ON
        otdoa-NeighbourCellInfo         OTDOA-NeighbourCellInfoList         OPTIONAL,   -- Need ON
        otdoa-Error                     OTDOA-Error                         OPTIONAL,   -- Need ON
        ...
    }

Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32

History         :
  1.lifuxin 00253982          2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeProAssistDataOTDOA
(
    VOS_UINT8                              *pucDecodeBitStream,
    VOS_UINT32                             *pulCurrentBitPos,
    LPP_OTDOA_PROVIDE_ASSIST_DATA_STRU     *pstProAssistDataOTDOA
)
{
    VOS_UINT32                              ulRslt = 0;

    /*������չ��*/
    pstProAssistDataOTDOA->bitOpOtdoaProvideAssistanceDataExt = NAS_LPP_GetDataFromBitStream(
                                                                                            pucDecodeBitStream,
                                                                                            pulCurrentBitPos, 1);

    /*����option*/
    pstProAssistDataOTDOA->bitOpOtdoaReferenceCellInfo = NAS_LPP_GetDataFromBitStream(
                                                                                    pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 1);
    pstProAssistDataOTDOA->bitOpOtdoaNeighbourCellInfo = NAS_LPP_GetDataFromBitStream(
                                                                                    pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 1);
    pstProAssistDataOTDOA->bitOpOtdoaError = NAS_LPP_GetDataFromBitStream(
                                                                            pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);

    /*����refCellInfo*/
    if(NAS_LPP_DECODE_SUCC != pstProAssistDataOTDOA->bitOpOtdoaReferenceCellInfo)
    {
        ulRslt = NAS_LPP_DecodeOtdoaRefCellInfo(pucDecodeBitStream, pulCurrentBitPos,
                                                &(pstProAssistDataOTDOA->stOtdoaRefCellInfo));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����NeighbourCellInfo*/
    if(NAS_LPP_DECODE_SUCC != pstProAssistDataOTDOA->bitOpOtdoaNeighbourCellInfo)
    {
        ulRslt = NAS_LPP_DecodeOtdoaNeighbourCellInfo(  pucDecodeBitStream, pulCurrentBitPos,
                                                        &(pstProAssistDataOTDOA->stOtdoaNeighbourCellInfo));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����NeighbourCellInfo*/
    if(NAS_LPP_DECODE_SUCC != pstProAssistDataOTDOA->bitOpOtdoaError)
    {
        ulRslt = NAS_LPP_DecodeOtdoaError(  pucDecodeBitStream, pulCurrentBitPos,
                                            &(pstProAssistDataOTDOA->stOtdoaError));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*��չ����*/
    if(NAS_LPP_NO_SLCT == pstProAssistDataOTDOA->bitOpOtdoaProvideAssistanceDataExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_PROASSISTDATAOTDOA_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                    *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssLocationServerErrorCause
Description     :����LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT8
Input           : ��Ϣ������
Output          : None
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin          2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32      NAS_LPP_DecodeGnssLocationServerErrorCause
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    VOS_UINT8                                               ucLen,
    LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_ENUM_UINT8        *penLocSerErrorCause
)
{
    VOS_UINT32                                              ulReturnRslt    = 0;

    ulReturnRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                                ucLen, penLocSerErrorCause);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSLOCATIONSERVERERRORCAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  ulReturnRslt;
    }
    if((NAS_LPP_EXT_ENUMERATED_BUTT == *penLocSerErrorCause)||(*penLocSerErrorCause > 2))
    {
        *penLocSerErrorCause = LPP_GNSS_LOCATION_SERVER_ERROR_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSLOCATIONSERVERERRORCAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssErrorLocationServer
Description     :����LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU
Input           : ��Ϣ������
Output          : None
ASN             :

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982          2015-05-25  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssErrorLocationServer
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU              *pstGNSSLocationServerError
)
{
    VOS_UINT32                                              ulRslt          = 0;

    /*������չ��*/
    pstGNSSLocationServerError->bitOpGNSSLocationServerErrorCauseExt = NAS_LPP_GetDataFromBitStream(
                                                                                                    pucDecodeBitStream,
                                                                                                    pulCurrentBitPos, 1);

    /*����ö��Cause*/
    ulRslt = NAS_LPP_DecodeGnssLocationServerErrorCause(pucDecodeBitStream, pulCurrentBitPos,
                                                        2, &(pstGNSSLocationServerError->enGNSSLocationServerCause));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGNSSLocationServerError->bitOpGNSSLocationServerErrorCauseExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSERRORLOCATIONSERVER_ERROR,
                                NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos,
                                __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssTargetDeviceErrorCause
Description     :����LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT8
Input           : ��Ϣ������
Output          : None
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin          2015-05-26  Draft Enact
*****************************************************************************/
VOS_UINT32      NAS_LPP_DecodeGnssTargetDeviceErrorCause
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    VOS_UINT8                                               ucLen,
    LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_CAUSE_ENUM_UINT8 *penTarDeviceErrorCause
)
{
    VOS_UINT32                                              ulReturnRslt = 0;

    ulReturnRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                                ucLen, penTarDeviceErrorCause);
    if(ulReturnRslt != NAS_LPP_DECODE_SUCC)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSTARGETDEVICEERRORCAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pulCurrentBitPos,
                                 __LINE__, 0);
        return      ulReturnRslt;
    }
    if(NAS_LPP_EXT_ENUMERATED_BUTT == *penTarDeviceErrorCause)
    {
        *penTarDeviceErrorCause = LPP_GNSS_LOCATION_TARGET_DEVICE_ERROR_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSTARGETDEVICEERRORCAUSE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssErrorLocationServer
Description     :����LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-TargetDeviceErrorCauses ::= SEQUENCE {
    cause       ENUMERATED {    undefined,
                                thereWereNotEnoughSatellitesReceived,
                                assistanceDataMissing,
                                notAllRequestedMeasurementsPossible,
                                ...
                            },
    fineTimeAssistanceMeasurementsNotPossible       NULL        OPTIONAL,
    adrMeasurementsNotPossible                      NULL        OPTIONAL,
    multiFrequencyMeasurementsNotPossible           NULL        OPTIONAL,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982          2015-05-25  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssTargetDevice
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_GNSS_TARGET_DEVICE_ERROR_CAUSE_STRU                *pstGNSSTargetDeviceError
)
{
    VOS_UINT32                                              ulRslt          = 0;

    /*������չ��*/
    pstGNSSTargetDeviceError->bitOpGNSSTargetDevErrCauseExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����option*/
    pstGNSSTargetDeviceError->bitOpFineTimeAssistMeasNotPossible =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstGNSSTargetDeviceError->bitOpAdrMeasNotPossibleExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstGNSSTargetDeviceError->bitOpMultiFreqMeasNotPossibleExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����ö��Cause*/
    ulRslt = NAS_LPP_DecodeGnssTargetDeviceErrorCause(pucDecodeBitStream, pulCurrentBitPos, 2,
                                                    &(pstGNSSTargetDeviceError->enGNSSTargetDeviceErrorCause));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGNSSTargetDeviceError->bitOpGNSSTargetDevErrCauseExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSTARGETDEVICE_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGNSSError
Description     :����LPP_GNSS_ERROR_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
A-GNSS-Error ::= CHOICE {
    locationServerErrorCauses       GNSS-LocationServerErrorCauses,
    targetDeviceErrorCauses         GNSS-TargetDeviceErrorCauses,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982          2015-05-25  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGNSSError
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ERROR_STRU                *pstGNSSError
)
{
    VOS_UINT32                          ulRslt              = 0;

     /*�������չ��choic�����С�ķǸ�������������*/
     ulRslt = NAS_LPP_DecodeExtChoice(pucDecodeBitStream, pulCurrentBitPos, 1, &(pstGNSSError->ulChoice));
     if(NAS_LPP_DECODE_SUCC != ulRslt)
     {
         return ulRslt;
     }
     if(LPP_DECODE_EXT_CHOICE_INVALID_VALUE == pstGNSSError->ulChoice)
     {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSERROR_ERROR,
                                 NAS_LPP_CHOICE_EXT_OBJECT_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_CHOICE_ERROR;
     }

     switch(pstGNSSError->ulChoice)
     {
         case LPP_LOCATION_SERVER_ERROR_CAUSE_CHOSEN:
             ulRslt = NAS_LPP_DecodeGnssErrorLocationServer(pucDecodeBitStream, pulCurrentBitPos,
                                                          &(pstGNSSError->u.stLocationServerErrorCauses));
             if(NAS_LPP_DECODE_SUCC != ulRslt)
             {
                 return ulRslt;
             }
             break;

         default:
             ulRslt = NAS_LPP_DecodeGnssTargetDevice(pucDecodeBitStream, pulCurrentBitPos,
                                                   &(pstGNSSError->u.stTargetDeviceErrorCauses));
             if(NAS_LPP_DECODE_SUCC != ulRslt)
             {
                 return ulRslt;
             }
             break;
     }

     return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssIdWithExtNoChoice
Description     :����LPP_GNSS_ID_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssIdWithExtNoChoice
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT8                           ucLen,
    LPP_GNSS_ID_ENUM_UINT8             *penGnssId
)
{
    VOS_UINT32      ulRslt = 0;

    ulRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                        ucLen, penGnssId);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSIDWITHEXTNOCHOICE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return      ulRslt;
    }
    if((NAS_LPP_EXT_ENUMERATED_BUTT == *penGnssId)||(*penGnssId > 4))
    {
        *penGnssId = LPP_GNSS_ID_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSIDWITHEXTNOCHOICE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                 *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssId
Description     :����LPP_GNSS_ID_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-ID ::= SEQUENCE {
    gnss-id             ENUMERATED{ gps, sbas, qzss, galileo, glonass, ...},
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssId
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ID_STRU                   *pstGnssId
)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��*/
    pstGnssId->bitOpGNSSIDExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����ö����*/
    /*��չö����Ľ���*/
    ulRslt = NAS_LPP_DecodeGnssIdWithExtNoChoice(pucDecodeBitStream, pulCurrentBitPos, 3, &(pstGnssId->enGnssId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return  ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssId->bitOpGNSSIDExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSID_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssIdWithExtNoChoice
Description     :����LPP_GNSS_ID_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeSabsIdWithExtNoChoice
(
    VOS_UINT8                       *pucDecodeBitStream,
    VOS_UINT32                      *pulCurrentBitPos,
    VOS_UINT8                       ucLen,
    LPP_SBAS_ID_ENUM_UINT8          *penSbasId
)
{
    VOS_UINT32      ulRslt = 0;

    ulRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                         ucLen, penSbasId);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SABSIDWITHEXTNOCHOICE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return      ulRslt;
    }
    if(NAS_LPP_EXT_ENUMERATED_BUTT == *penSbasId)
    {
        *penSbasId = LPP_SBAS_ID_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SABSIDWITHEXTNOCHOICE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeSbasId
Description     :����LPP_SBAS_ID_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
SBAS-ID ::= SEQUENCE {
    sbas-id             ENUMERATED { waas, egnos, msas, gagan, ...},
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeSbasId
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_SBAS_ID_STRU                   *pstSbasId
)
{
    VOS_UINT32                          ulRslt = 0;

    /*������չ��*/
    pstSbasId->bitOpSBASIDExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����ö����*/
    /*��չö����Ľ���*/
    ulRslt = NAS_LPP_DecodeSabsIdWithExtNoChoice(pucDecodeBitStream, pulCurrentBitPos, 2, &(pstSbasId->enLppSbasId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return  ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstSbasId->bitOpSBASIDExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_SBASID_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}


/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssTimeModelReqElement
Description     :����LPP_GNSS_TIME_MODEL_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-TimeModelElement ::= SEQUENCE {
    gnss-TimeModelRefTime       INTEGER (0..65535),
    tA0                         INTEGER (-67108864..67108863),
    tA1                         INTEGER (-4096..4095)                   OPTIONAL,   -- Need ON
    tA2                         INTEGER (-64..63)                       OPTIONAL,   -- Need ON
    gnss-TO-ID                  INTEGER (1..15),
    weekNumber                  INTEGER (0..8191)                       OPTIONAL,   -- Need ON
    deltaT                      INTEGER (-128..127)                     OPTIONAL,   -- Need ON
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssTimeModelReqElement
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_TIME_MODEL_ELEMENT_STRU   *pstGnssTimeModelListElement)
{
    VOS_UINT32                          ulRslt      = 0;

    /*������չ��*/
    pstGnssTimeModelListElement->bitOpGNSSTimeModelElementExt = NAS_LPP_GetDataFromBitStream(
                                                                                            pucDecodeBitStream,
                                                                                            pulCurrentBitPos, 1);

    /*����option*/
    pstGnssTimeModelListElement->bitOpTA1 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                         pulCurrentBitPos, 1);
    pstGnssTimeModelListElement->bitOpTA2 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                         pulCurrentBitPos, 1);
    pstGnssTimeModelListElement->bitOpWeekNumber = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstGnssTimeModelListElement->bitOpDeltaT = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);

    /*����gnss-TimeModelRefTime*/
    pstGnssTimeModelListElement->ulGNSSTimeModelRefTime = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                       pulCurrentBitPos, 16);

    /*����TA0*/
    pstGnssTimeModelListElement->lTA0 = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 27) - 67108864;

    /*����TA1*/
    if(NAS_LPP_SLCT == pstGnssTimeModelListElement->bitOpTA1)
    {
        pstGnssTimeModelListElement->sTA1 = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 13) - 4096;
    }

    /*����TA2*/
    if(NAS_LPP_SLCT == pstGnssTimeModelListElement->bitOpTA2)
    {
        pstGnssTimeModelListElement->cTA2 = (VOS_INT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 7) - 64;
    }

    /*����gnsstoId*/
    pstGnssTimeModelListElement->ucGNSSToId = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                      pulCurrentBitPos, 4) + 1;

    /*����weekNum*/
    if(NAS_LPP_SLCT == pstGnssTimeModelListElement->bitOpWeekNumber)
    {
        pstGnssTimeModelListElement->usWeekNumber = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                             pulCurrentBitPos, 13);
    }

    /*����DeltaT*/
    if(NAS_LPP_SLCT == pstGnssTimeModelListElement->bitOpDeltaT)
    {
        pstGnssTimeModelListElement->sDeltaT = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                       pulCurrentBitPos, 8) - 128;
    }


    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssTimeModelListElement->bitOpGNSSTimeModelElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSTIMEMODELREQELEMENT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssTimeModel
Description     :����LPP_GNSS_TIME_MODEL_LIST_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-TimeModelList ::= SEQUENCE (SIZE (1..15)) OF GNSS-TimeModelElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssTimeModel
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_TIME_MODEL_LIST_STRU      *pstGnssTimeModelList
)
{
    VOS_UINT32                          ulRslt                      = 0;
    VOS_UINT32                          ulGnssTimeModelListNum      = 0;
    VOS_UINT32                          ulLoop                      = 0;

    /*����ulGnssTimeModelListNum*/
    ulGnssTimeModelListNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 4);
    ulGnssTimeModelListNum += 1;
    if((ulGnssTimeModelListNum < 1) || (ulGnssTimeModelListNum > 15))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSTIMEMODEL_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__, 0);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    pstGnssTimeModelList->ulGNSSTimeModelListCnt = ulGnssTimeModelListNum;

    /*����ʵ�ʵ���Ϣ��*/
    for(ulLoop = 0; ulLoop < pstGnssTimeModelList->ulGNSSTimeModelListCnt; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeGnssTimeModelReqElement(pucDecodeBitStream, pulCurrentBitPos,
                                                     &(pstGnssTimeModelList->astGNSSTimeModelListArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssSignalID
Description     :����LPP_GNSS_SIGNAL_ID_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-SignalID   ::= SEQUENCE {
    gnss-SignalID       INTEGER (0 .. 7),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssSignalID
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_SIGNAL_ID_STRU            *pstGnssSignalId
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��ʶλ*/
    pstGnssSignalId->bitGNSSSignalIDExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 1);

    /*������չsignalId*/
    pstGnssSignalId->ucGNSSSignalId = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 3);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssSignalId->bitGNSSSignalIDExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSSIGNALID_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeSvId
Description     :����LPP_SV_ID_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
SV-ID ::= SEQUENCE {
    satellite-id        INTEGER(0..63),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeSvId(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_SV_ID_STRU                          *pstSvId
)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��ʶλ*/
    pstSvId->bitOpSVIDExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����svid*/
    pstSvId->ucSatelliteId = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 6);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstSvId->bitOpSVIDExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_SVID_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeDgnssSatListElement
Description     :����LPP_DGNSS_CORRECT_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
DGNSS-CorrectionsElement ::= SEQUENCE {
    svID                SV-ID,
    iod                 BIT STRING (SIZE(11)),
    udre                INTEGER (0..3),
    pseudoRangeCor      INTEGER (-2047..2047),
    rangeRateCor        INTEGER (-127..127),
    udreGrowthRate      INTEGER (0..7)          OPTIONAL,   -- Need ON
    udreValidityTime    INTEGER (0..7)          OPTIONAL,   -- Need ON
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeDgnssSatListElement(
            VOS_UINT8                               *pucDecodeBitStream,
            VOS_UINT32                              *pulCurrentBitPos,
            LPP_DGNSS_CORRECT_ELEMENT_STRU          *pstDgnssCorrectElement)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��*/
    pstDgnssCorrectElement->bitOpDGNSSCorrectElementExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����option*/
    pstDgnssCorrectElement->bitOpUdreGrowthRate = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstDgnssCorrectElement->bitOpUdreValidityTime = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����svid*/
    ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos, &(pstDgnssCorrectElement->stSvId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����iod*/
    pstDgnssCorrectElement->usIod = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos,11);

    /*����udre*/
    pstDgnssCorrectElement->usUdre = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 2);

    /*����Cor*/
    pstDgnssCorrectElement->sPseudoRangeCor = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 12) - 2047;

    /*����RateCor*/
    pstDgnssCorrectElement->cRangeRateCor = (VOS_INT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8) - 127;

    /*����GreowthRate*/
    if(NAS_LPP_SLCT == pstDgnssCorrectElement->bitOpUdreGrowthRate)
    {
        pstDgnssCorrectElement->ucUdreGrowthRate = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 3);
    }

    /*����ValidTime*/
    if(NAS_LPP_SLCT == pstDgnssCorrectElement->bitOpUdreValidityTime)
    {
        pstDgnssCorrectElement->ucudreValidityTime = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 3);
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstDgnssCorrectElement->bitOpDGNSSCorrectElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_DGNSATLISTELEMENT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;

}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeDgnssSatList
Description     :����LPP_DGNSS_SAT_LIST_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
DGNSS-SatList ::= SEQUENCE (SIZE (1..64)) OF DGNSS-CorrectionsElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeDgnssSatList(
            VOS_UINT8                               *pucDecodeBitStream,
            VOS_UINT32                              *pulCurrentBitPos,
            LPP_DGNSS_SAT_LIST_STRU                 *pstDgnssSatList)
{
    VOS_UINT32      ulRslt = 0;
    VOS_UINT32      ulDgnssSatListNum = 0;
    VOS_UINT32      ulLoop = 0;

    /*�������ֵ*/
    ulDgnssSatListNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 6);
    ulDgnssSatListNum += 1;
    pstDgnssSatList->ulDGNSSSatListcnt = ulDgnssSatListNum;
    if (LPP_MAX_DGNSS_CORRECT_ELEMENT_LEN < ulDgnssSatListNum)
    {
        NAS_LPP_ASN_FAIL_Message( NAS_LPP_DECODE_DGNSSSATLIST_ERROR,
                                  NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                 *pulCurrentBitPos,
                                  __LINE__,
                                  ulDgnssSatListNum);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    for(ulLoop = 0; ulLoop < pstDgnssSatList->ulDGNSSSatListcnt ; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeDgnssSatListElement(pucDecodeBitStream, pulCurrentBitPos, &(pstDgnssSatList->astDGNSSCorrectElementArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeDgnssSgnTypeListElement
Description     :����LPP_DGNSS_SGN_TYPE_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
DGNSS-SgnTypeElement ::= SEQUENCE {
    gnss-SignalID        GNSS-SignalID,
    gnss-StatusHealth    INTEGER (0..7),
    dgnss-SatList        DGNSS-SatList,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeDgnssSgnTypeListElement
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_DGNSS_SGN_TYPE_ELEMENT_STRU    *pstDgnssSgnTypeElement
)
{
    VOS_UINT32                          ulRslt = 0;

    /*������չ��*/
    pstDgnssSgnTypeElement->bitOpDGNSSSignalTypeElementExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����signalID*/
    ulRslt = NAS_LPP_DecodeGnssSignalID(pucDecodeBitStream, pulCurrentBitPos,
                                      &(pstDgnssSgnTypeElement->stGNSSSignalId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����StatusHealth*/
    pstDgnssSgnTypeElement->ucGNSSStatusHealth = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 3);

    /*���� dgnss-SatList*/
    ulRslt = NAS_LPP_DecodeDgnssSatList(pucDecodeBitStream, pulCurrentBitPos,
                                      (LPP_DGNSS_SAT_LIST_STRU*)&(pstDgnssSgnTypeElement->stDGNSSSatList));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstDgnssSgnTypeElement->bitOpDGNSSSignalTypeElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_DGNSSSGNTYPELISTELEMENT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeDgnssSgnTypeList
Description     :����LPP_DGNSS_SGN_TYPE_LIST_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
DGNSS-SgnTypeList ::= SEQUENCE (SIZE (1..3)) OF DGNSS-SgnTypeElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeDgnssSgnTypeList
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_DGNSS_SGN_TYPE_LIST_STRU       *pstDgnssSgnTypeList
)
{
    VOS_UINT32                          ulRslt                      = 0;
    VOS_UINT32                          ulDgnssSgnTypeListNum       = 0;
    VOS_UINT32                          ulLoop                      = 0;

    /*�������ֵ*/
    ulDgnssSgnTypeListNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 2);
    ulDgnssSgnTypeListNum += 1;
    if((ulDgnssSgnTypeListNum < 1) || (ulDgnssSgnTypeListNum > 3))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DGNSSSGNTYPELIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__, 0);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    pstDgnssSgnTypeList->ulDGNSSSgnTypeListCnt = ulDgnssSgnTypeListNum;

    for(ulLoop = 0; ulLoop < pstDgnssSgnTypeList->ulDGNSSSgnTypeListCnt ; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeDgnssSgnTypeListElement(pucDecodeBitStream, pulCurrentBitPos,
                                                     &(pstDgnssSgnTypeList->astDGNSSSgnTypeListArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssdiffCorrection
Description     :����LPP_GNSS_DIFF_CORRECT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-DifferentialCorrections ::= SEQUENCE {
    dgnss-RefTime       INTEGER (0..3599),
    dgnss-SgnTypeList   DGNSS-SgnTypeList,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssdiffCorrection
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_DIFF_CORRECT_STRU         *pstGnssDiffCorrect
)
{
    VOS_UINT32                          ulRslt = 0;

    /*������չ��*/
    pstGnssDiffCorrect->bitOpGNSSDiffCorrectExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                               pulCurrentBitPos, 1);

    /*����refTime*/
    pstGnssDiffCorrect->usDGNSSRefTime = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                  pulCurrentBitPos, 12);
    if(pstGnssDiffCorrect->usDGNSSRefTime > 3599)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_DGNSSREFTIME_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__, pstGnssDiffCorrect->usDGNSSRefTime);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����sgnTypeList*/
    ulRslt = NAS_LPP_DecodeDgnssSgnTypeList(pucDecodeBitStream, pulCurrentBitPos,
                                          &(pstGnssDiffCorrect->stDGNSSSgnTypeList));


    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssDiffCorrect->bitOpGNSSDiffCorrectExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSDIFFCORRECTION_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeExtChoiceClockMoel
Description     :�������չchoice��
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982         2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeExtChoiceClockMoel
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    VOS_UINT8                           ucLen,
    VOS_UINT32                         *pExtChoiceValue
)
{
    VOS_UINT32                          ulRslt              = 0;

    ulRslt = NAS_LPP_DecodeExtChoice(pucDecodeBitStream, pulCurrentBitPos, ucLen,
                                     pExtChoiceValue);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    if(LPP_DECODE_EXT_CHOICE_INVALID_VALUE == *pExtChoiceValue)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_CLOCKMODEL_ERROR,
                                 NAS_LPP_CHOICE_EXT_OBJECT_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeStandardClockModellListElement
Description     :����LPP_STANDARD_CLOCK_MODEL_LIST_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
StandardClockModelElement ::= SEQUENCE {
    stanClockToc    INTEGER (0..16383),
    stanClockAF2    INTEGER (-2048..2047),
    stanClockAF1    INTEGER (-131072..131071),
    stanClockAF0    INTEGER (-134217728..134217727),
    stanClockTgd    INTEGER (-512..511)                 OPTIONAL,   -- Need ON
    stanModelID     INTEGER (0..1)                      OPTIONAL,   -- Need ON
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeStandardClockModellListElement
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_STANDARD_CLOCK_MODEL_LIST_ELEMENT_STRU             *pstStandardClockModelElement
)
{
    VOS_UINT32                                              ulRslt = 0;

    /*������չ��*/
    pstStandardClockModelElement->bitOpStandClockModelListElementExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����option*/
    pstStandardClockModelElement->bitOpStanClockTgd =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstStandardClockModelElement->bitOpStanModelId =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����Toc*/
    pstStandardClockModelElement->usStanClockToc =
        (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 14);

    /*����AF2*/
    pstStandardClockModelElement->sStanClockAF2 =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 12) - 2048;

    /*����AF1s*/
    pstStandardClockModelElement->lStanClockAF1 =
        (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 18) - 131072;

    /*����AF1s*/
    pstStandardClockModelElement->lStanClockAF0 =
        (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 28) - 134217728;

    /*����TDG*/
    if(NAS_LPP_SLCT == pstStandardClockModelElement->bitOpStanClockTgd)
    {
        pstStandardClockModelElement->sStanClockTgd =
            (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 10) - 512;
    }

    /*����TDG*/
    if(NAS_LPP_SLCT == pstStandardClockModelElement->bitOpStanModelId)
    {
        pstStandardClockModelElement->usStanModelID =
            (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstStandardClockModelElement->bitOpStandClockModelListElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_STANDARDCLOCKMODELLISTELEMENT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeStandardClockModeList
Description     :����LPP_STANDARD_CLOCK_MODEL_LIST_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
StandardClockModelList ::= SEQUENCE (SIZE(1..2)) OF StandardClockModelElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeStandardClockModeList
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_STANDARD_CLOCK_MODEL_LIST_STRU *pstStandardClockModelList)
{
    VOS_UINT32                          ulRslt                      = 0;
    VOS_UINT32                          ulStandardClockModelNum     = 0;
    VOS_UINT32                          ulLoop                      = 0;

    /*�������ֵ*/
    ulStandardClockModelNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    ulStandardClockModelNum += 1;
    pstStandardClockModelList->ulStandardClockModelListCnt = ulStandardClockModelNum;

    for(ulLoop = 0; ulLoop < pstStandardClockModelList->ulStandardClockModelListCnt ; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeStandardClockModellListElement(pucDecodeBitStream, pulCurrentBitPos,
                                                            &(pstStandardClockModelList->astStandardClockModelListArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeNavClockModel
Description     :����LPP_NAV_CLOCK_MODEL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
NAV-ClockModel ::= SEQUENCE {
navToc          INTEGER (0..37799),
navaf2          INTEGER (-128..127),
navaf1          INTEGER (-32768..32767),
navaf0          INTEGER (-2097152..2097151),
navTgd          INTEGER (-128..127),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeNavClockModel
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_NAV_CLOCK_MODEL_STRU                *pstNavClockModelList
)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��*/
    pstNavClockModelList->bitOpNavClockModelExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                               pulCurrentBitPos, 1);

    /*����toc*/
    pstNavClockModelList->usNavToc = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 16);
    if(pstNavClockModelList->usNavToc > 37799)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_NAVCLOCKMODEL_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__,
                                 pstNavClockModelList->usNavToc);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����af2*/
    pstNavClockModelList->cNavaf2 = (VOS_INT8)((VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                       pulCurrentBitPos, 8) - 128);

    /*����af1*/
    pstNavClockModelList->lNavaf1 = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                            pulCurrentBitPos, 16) - 32768;

    /*����af0*/
    pstNavClockModelList->lNavaf0 = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                            pulCurrentBitPos, 22) - 2097152;

    /*����tgd*/
    pstNavClockModelList->cNavTgd = (VOS_INT8)((VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                       pulCurrentBitPos, 8) - 128);


    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstNavClockModelList->bitOpNavClockModelExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_NAVCLOCKMODEL_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCnavClockModel
Description     :����LPP_CNAV_CLOCK_MODEL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
CNAV-ClockModel ::= SEQUENCE {
    cnavToc         INTEGER (0..2015),
    cnavTop         INTEGER (0..2015),
    cnavURA0        INTEGER (-16..15),
    cnavURA1        INTEGER (0..7),
    cnavURA2        INTEGER (0..7),
    cnavAf2         INTEGER (-512..511),
    cnavAf1         INTEGER (-524288..524287),
    cnavAf0         INTEGER (-33554432..33554431),
    cnavTgd         INTEGER (-4096..4095),
    cnavISCl1cp     INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
    cnavISCl1cd     INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
    cnavISCl1ca     INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
    cnavISCl2c      INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
    cnavISCl5i5     INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
    cnavISCl5q5     INTEGER (-4096..4095)           OPTIONAL,   -- Need ON
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCnavClockModel
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_CNAV_CLOCK_MODEL_STRU          *pstCnavClockModelList)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��*/
    pstCnavClockModelList->bitOpCnavClockModelExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����option*/
    pstCnavClockModelList->bitOpCnavISCl1cp = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                           pulCurrentBitPos, 1);
    pstCnavClockModelList->bitOpCnavISCl1cd = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                           pulCurrentBitPos, 1);
    pstCnavClockModelList->bitOpCnavISCl1ca = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                           pulCurrentBitPos, 1);
    pstCnavClockModelList->bitOpCnavISCl2c = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 1);
    pstCnavClockModelList->bitOpCnavISCl5i5 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                           pulCurrentBitPos, 1);
    pstCnavClockModelList->bitOpCnavISCl5q5 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                           pulCurrentBitPos, 1);

    /*����toc*/
    pstCnavClockModelList->usCnavToc = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 11);
    if(pstCnavClockModelList->usCnavToc > 2015)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_CNAVCLOCKMODEL_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����top*/
    pstCnavClockModelList->uscnavTop = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 11);
    if(pstCnavClockModelList->uscnavTop > 2015)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_CNAVCLOCKMODEL_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����Ra0*/
    pstCnavClockModelList->cCnavUra0 = (VOS_INT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 5) - 16;

    /*����ra1*/
    pstCnavClockModelList->ucCnavUra1 = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 3);

    /*����ra2*/
    pstCnavClockModelList->ucCnavUra2 = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 3);

    /*����af2*/
    pstCnavClockModelList->lCnavAf2 = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 10) - 512;

    /*����af1*/
    pstCnavClockModelList->lCnavAf1 = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 20) - 524288;

    /*����af0*/
    pstCnavClockModelList->lCnavAf0 = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 26) - 33554432;

    /*����TGD*/
    pstCnavClockModelList->sCnavTgd = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 13) - 4096;

    /*����cp*/
    if(NAS_LPP_SLCT == pstCnavClockModelList->bitOpCnavISCl1cp)
    {
        pstCnavClockModelList->sCnavISCl1cp = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                      pulCurrentBitPos, 13) - 4096;
    }

    /*����cd*/
    if(NAS_LPP_SLCT == pstCnavClockModelList->bitOpCnavISCl1cd)
    {
        pstCnavClockModelList->sCnavISCl1cd = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                      pulCurrentBitPos, 13) - 4096;
    }

    /*����ca*/
    if(NAS_LPP_SLCT == pstCnavClockModelList->bitOpCnavISCl1ca)
    {
        pstCnavClockModelList->sCnavISCl1ca = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                      pulCurrentBitPos, 13) - 4096;
    }

    /*����2c*/
    if(NAS_LPP_SLCT == pstCnavClockModelList->bitOpCnavISCl2c)
    {
        pstCnavClockModelList->sCnavISCl2c = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                     pulCurrentBitPos, 13) - 4096;
    }

    /*����5i5*/
    if(NAS_LPP_SLCT == pstCnavClockModelList->bitOpCnavISCl5i5)
    {
        pstCnavClockModelList->sCnavISCl5i5 = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                      pulCurrentBitPos, 13) - 4096;
    }

    /*����5q5*/
    if(NAS_LPP_SLCT == pstCnavClockModelList->bitOpCnavISCl5q5)
    {
        pstCnavClockModelList->sCnavISCl5q5 = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                      pulCurrentBitPos, 13) - 4096;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstCnavClockModelList->bitOpCnavClockModelExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_CNAVCLOCKMODEL_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGlonassClockModel
Description     :����LPP_GLONASS_CLOCK_MODEL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GLONASS-ClockModel ::= SEQUENCE {
    gloTau          INTEGER (-2097152..2097151),
    gloGamma        INTEGER (-1024..1023),
    gloDeltaTau     INTEGER (-16..15)               OPTIONAL,   -- Need ON
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGlonassClockModel
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GLONASS_CLOCK_MODEL_STRU       *pstGlonassClockModelList)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��*/
    pstGlonassClockModelList->bitOpGLONASSClockModelExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����option*/
    pstGlonassClockModelList->bitOpGloDeltaTau = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 1);

    /*����tau*/
    pstGlonassClockModelList->lGloTau = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 22) - 2097152;

    /*����gamma*/
    pstGlonassClockModelList->sGloGamma = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                  pulCurrentBitPos, 11) - 1024;

    /*����5q5*/
    if(NAS_LPP_SLCT == pstGlonassClockModelList->bitOpGloDeltaTau)
    {
        pstGlonassClockModelList->sGloDeltatau =
            (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 5) - 16;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGlonassClockModelList->bitOpGLONASSClockModelExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GLONASSCLOCKMODEL_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeSbasClockModel
Description     :����LPP_SBAS_CLOCK_MODEL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
SBAS-ClockModel ::= SEQUENCE {
    sbasTo          INTEGER (0..5399),
    sbasAgfo        INTEGER (-2048..2047),
    sbasAgf1        INTEGER (-128..127),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeSbasClockModel
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_SBAS_CLOCK_MODEL_STRU          *pstSbasClockModelList
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��*/
    pstSbasClockModelList->bitOpSBASClockModelExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����to*/
    pstSbasClockModelList->usSbasTo = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                               pulCurrentBitPos, 13);
    if(pstSbasClockModelList->usSbasTo > 5399)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_SBASCLOCKMODEL_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����agfo*/
    pstSbasClockModelList->sSbasAgfo = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                               pulCurrentBitPos, 12) - 2048;

    /*����agf1*/
    pstSbasClockModelList->sSbasAgf1 = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                               pulCurrentBitPos, 8) - 128;


    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstSbasClockModelList->bitOpSBASClockModelExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_SBASCLOCKMODEL_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssClockModel
Description     :����LPP_GNSS_CLOCK_MODEL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-ClockModel ::= CHOICE {
    standardClockModelList  StandardClockModelList,         -- Model-1
    nav-ClockModel          NAV-ClockModel,                 -- Model-2
    cnav-ClockModel         CNAV-ClockModel,                -- Model-3
    glonass-ClockModel      GLONASS-ClockModel,             -- Model-4
    sbas-ClockModel         SBAS-ClockModel,                -- Model-5
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssClockModel
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_CLOCK_MODEL_STRU          *pstGnssClockModel)
{
    VOS_UINT32                          ulRslt              = 0;

    /*����choice*/
    ulRslt= NAS_LPP_DecodeExtChoiceClockMoel(pucDecodeBitStream, pulCurrentBitPos, 3,
                                           &(pstGnssClockModel->ulChoice));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������Ϣ��*/
    switch(pstGnssClockModel->ulChoice)
    {
        case LPP_STANDARD_CLOCK_MODEL_LIST_CHOSEN:
            ulRslt = NAS_LPP_DecodeStandardClockModeList(pucDecodeBitStream, pulCurrentBitPos,
                                                       &(pstGnssClockModel->u.stStandardClockModelList));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_NAV_CLOCK_MODEL_CHOSEN:
            ulRslt = NAS_LPP_DecodeNavClockModel(pucDecodeBitStream, pulCurrentBitPos,
                                               &(pstGnssClockModel->u.stNavClockModel));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_CNAV_CLOCK_MODEL_CHOSEN:
            ulRslt = NAS_LPP_DecodeCnavClockModel(pucDecodeBitStream, pulCurrentBitPos,
                                                &(pstGnssClockModel->u.stCnavClockModel));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_GLONASS_CLOCK_MODEL_CHOSEN:
            ulRslt = NAS_LPP_DecodeGlonassClockModel(pucDecodeBitStream, pulCurrentBitPos,
                                                   &(pstGnssClockModel->u.stGlonassClockModel));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        default:
            ulRslt = NAS_LPP_DecodeSbasClockModel(pucDecodeBitStream, pulCurrentBitPos,
                                                &(pstGnssClockModel->u.stSbasClockModel));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeKeplerSet
Description     :����LPP_NAV_MODEL_KEPLERIAN_SET_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
NavModelKeplerianSet ::= SEQUENCE {
    keplerToe        INTEGER (0 .. 16383),
    keplerW          INTEGER (-2147483648..2147483647),
    keplerDeltaN     INTEGER (-32768..32767),
    keplerM0         INTEGER (-2147483648..2147483647),
    keplerOmegaDot   INTEGER (-8388608.. 8388607),
    keplerE          INTEGER (0..4294967295),
    keplerIDot       INTEGER (-8192..8191),
    keplerAPowerHalf INTEGER (0.. 4294967295),
    keplerI0         INTEGER (-2147483648..2147483647),
    keplerOmega0     INTEGER (-2147483648..2147483647),
    keplerCrs        INTEGER (-32768..32767),
    keplerCis        INTEGER (-32768..32767),
    keplerCus        INTEGER (-32768..32767),
    keplerCrc        INTEGER (-32768..32767),
    keplerCic        INTEGER (-32768..32767),
    keplerCuc        INTEGER (-32768..32767),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeKeplerSet
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_NAV_MODEL_KEPLERIAN_SET_STRU   *pstNavModelKeplerSet
)
{
    VOS_UINT32                          ulRslt = 0;
    VOS_INT64                           llTempValue = 2147483648UL;

    /*������չ��*/
    pstNavModelKeplerSet->bitOpNavModelKeplerianSetExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                      pulCurrentBitPos, 1);

    /*����toe*/
    pstNavModelKeplerSet->ulKeplerToe = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                     pulCurrentBitPos, 14);

    /*����w*/
    pstNavModelKeplerSet->lKeplerW = (VOS_INT32)((VOS_INT64)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 32) - llTempValue);

    /*����N*/
    pstNavModelKeplerSet->lKeplerDeltaN = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 16) - 32768;

    /*����MO*/
    pstNavModelKeplerSet->lKeplerM0 = (VOS_INT32)((VOS_INT64)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                         pulCurrentBitPos, 32) - llTempValue);

    /*����dot*/
    pstNavModelKeplerSet->lKeplerOmegaDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 24) - 8388608;

    /*����E*/
    pstNavModelKeplerSet->ulKeplerE = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                   pulCurrentBitPos, 32);

    /*����idot*/
    pstNavModelKeplerSet->lKeplerIDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 14) - 8192;

    /*����Harlf*/
    pstNavModelKeplerSet->ulKeplerAPowerHalf = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                            pulCurrentBitPos, 32);

    /*����IO*/
    pstNavModelKeplerSet->lKeplerI0 = (VOS_INT32)((VOS_INT64)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                          pulCurrentBitPos, 32) - llTempValue);

    /*����omega0*/
    pstNavModelKeplerSet->lKeplerOmega0 = (VOS_INT32)((VOS_INT64)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                              pulCurrentBitPos, 32) - llTempValue);

    /*����crs*/
    pstNavModelKeplerSet->sKeplerCrs = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                           pulCurrentBitPos, 16) - 32768);

    /*����cis*/
    pstNavModelKeplerSet->sKeplerCis = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                           pulCurrentBitPos, 16) - 32768);

    /*����CUS*/
    pstNavModelKeplerSet->sKeplerCus = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                           pulCurrentBitPos, 16) - 32768);

    /*����crc*/
    pstNavModelKeplerSet->sKeplerCrc = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                           pulCurrentBitPos, 16) - 32768);

    /*����cic*/
    pstNavModelKeplerSet->sKeplerCic = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                           pulCurrentBitPos, 16) - 32768);

    /*����cuc*/
    pstNavModelKeplerSet->sKeplerCuc = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                           pulCurrentBitPos, 16) - 32768);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstNavModelKeplerSet->bitOpNavModelKeplerianSetExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_KEPLERSET_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEphemSf1Rsvd
Description     :����LPP_EPHEM_SF1_RSVD_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
ephemSF1Rsvd    SEQUENCE {
    reserved1       INTEGER (0..8388607),   -- 23-bit field
    reserved2       INTEGER (0..16777215),  -- 24-bit field
    reserved3       INTEGER (0..16777215),  -- 24-bit field
    reserved4       INTEGER (0..65535)      -- 16-bit field
},

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEphemSf1Rsvd
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_EPHEM_SF1_RSVD_STRU            *pstEphenSf1Rsvd
)
{
    /*����rsv1*/
    pstEphenSf1Rsvd->ulReserved1 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                pulCurrentBitPos, 23);

    /*����rsv2*/
    pstEphenSf1Rsvd->ulReserved2 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                pulCurrentBitPos, 24);

    /*����rsv3*/
    pstEphenSf1Rsvd->ulReserved3 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                pulCurrentBitPos, 24);

    /*����rsv4*/
    pstEphenSf1Rsvd->ulReserved4 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                pulCurrentBitPos, 16);

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeAddNavParam
Description     :����LPP_ADD_NAV_PARAM_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
addNAVparam     SEQUENCE {
     ephemCodeOnL2   INTEGER (0..3),
     ephemL2Pflag    INTEGER (0..1),
     ephemSF1Rsvd    SEQUENCE {
         reserved1       INTEGER (0..8388607),   -- 23-bit field
         reserved2       INTEGER (0..16777215),  -- 24-bit field
         reserved3       INTEGER (0..16777215),  -- 24-bit field
         reserved4       INTEGER (0..65535)      -- 16-bit field
     },
     ephemAODA       INTEGER (0..31)
 }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeAddNavParam
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_ADD_NAV_PARAM_STRU             *pstAddNavParam)
{
    VOS_UINT32                          ulRslt = 0;

    /*����onl2*/
    pstAddNavParam->ucEphemCodeOnL2 = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 2);

    /*����l2pflag*/
    pstAddNavParam->ucEphemL2Pflag = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                             pulCurrentBitPos, 1);

    /*����sfRsv*/
    ulRslt = NAS_LPP_DecodeEphemSf1Rsvd(pucDecodeBitStream, pulCurrentBitPos,
                                      &(pstAddNavParam->stEphemSF1Rsvd));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����ADDA*/
    pstAddNavParam->ulEphemAODA = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 5);

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeNavKeplerSet
Description     :����LPP_NAV_MODEL_NAV_KEPLERIAN_SET_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
NavModelNAV-KeplerianSet ::= SEQUENCE {
    navURA          INTEGER (0..15),
    navFitFlag      INTEGER (0..1),
    navToe          INTEGER (0..37799),
    navOmega        INTEGER (-2147483648..2147483647),
    navDeltaN       INTEGER (-32768..32767),
    navM0           INTEGER (-2147483648..2147483647),
    navOmegaADot    INTEGER (-8388608..8388607),
    navE            INTEGER (0..4294967295),
    navIDot         INTEGER (-8192..8191),
    navAPowerHalf   INTEGER (0..4294967295),
    navI0           INTEGER (-2147483648..2147483647),
    navOmegaA0      INTEGER (-2147483648..2147483647),
    navCrs          INTEGER (-32768..32767),
    navCis          INTEGER (-32768..32767),
    navCus          INTEGER (-32768..32767),
    navCrc          INTEGER (-32768..32767),
    navCic          INTEGER (-32768..32767),
    navCuc          INTEGER (-32768..32767),
    addNAVparam     SEQUENCE {
        ephemCodeOnL2   INTEGER (0..3),
        ephemL2Pflag    INTEGER (0..1),
        ephemSF1Rsvd    SEQUENCE {
            reserved1       INTEGER (0..8388607),   -- 23-bit field
            reserved2       INTEGER (0..16777215),  -- 24-bit field
            reserved3       INTEGER (0..16777215),  -- 24-bit field
            reserved4       INTEGER (0..65535)      -- 16-bit field
        },
        ephemAODA       INTEGER (0..31)
    }   OPTIONAL,   -- Need ON
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeNavKeplerSet
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_NAV_MODEL_NAV_KEPLERIAN_SET_STRU                   *pstNavKeplerSet)
{
    VOS_UINT32                                              ulRslt = 0;
    VOS_INT64                                               llTempValue = 2147483648UL;

    /*������չ��*/
    pstNavKeplerSet->bitOpNavClockNavKeplerianSetExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 1);

    /*����option*/
    pstNavKeplerSet->bitOpAddNavParam = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                     pulCurrentBitPos, 1);

    /*����URA*/
    pstNavKeplerSet->ucNavUra = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                        pulCurrentBitPos, 4);

    /*����FITFLAG*/
    pstNavKeplerSet->ucNavFitFlag = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);

    /*����TOE*/
    pstNavKeplerSet->usNavToe = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                         pulCurrentBitPos, 16);

    /*����omega*/
    pstNavKeplerSet->lNavOmega = (VOS_INT32)((VOS_INT64)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                     pulCurrentBitPos, 32) - llTempValue);

    /*����N*/
    pstNavKeplerSet->lNavDeltaN = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 16) - 32768;

    /*����M0*/
    pstNavKeplerSet->lNavMo = (VOS_INT32)((VOS_INT64)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                  pulCurrentBitPos, 32) - llTempValue);

    /*����DOT*/
    pstNavKeplerSet->lNavOmegaADot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                             pulCurrentBitPos, 24) - 8388608;

    /*����E*/
    pstNavKeplerSet->ulNavE = (VOS_UINT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 32);

    /*����IDOT*/
    pstNavKeplerSet->lNavIDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                        pulCurrentBitPos, 14) - 8192;

    /*����HALF*/
    pstNavKeplerSet->ulNavAPowerHalf = (VOS_UINT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 32);

    /*����IO*/
    pstNavKeplerSet->lNavI0 = (VOS_INT32)((VOS_INT64)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                  pulCurrentBitPos, 32) - llTempValue);

    /*����omega0*/
    pstNavKeplerSet->lNavOmegaA0 = (VOS_INT32)((VOS_INT64)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                       pulCurrentBitPos, 32) - llTempValue);

    /*����crs*/
    pstNavKeplerSet->sNavCrs = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                   pulCurrentBitPos, 16) - 32768);

    /*����cis*/
    pstNavKeplerSet->sNavCis = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                   pulCurrentBitPos, 16) - 32768);

    /*����CUS*/
    pstNavKeplerSet->sNavCus = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                   pulCurrentBitPos, 16) - 32768);

    /*����crc*/
    pstNavKeplerSet->sNavCrc = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                   pulCurrentBitPos, 16) - 32768);

    /*����cic*/
    pstNavKeplerSet->sNavCic = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                   pulCurrentBitPos, 16) - 32768);

    /*����cuc*/
    pstNavKeplerSet->sNavCuc = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                   pulCurrentBitPos, 16) - 32768);

    if(NAS_LPP_SLCT == pstNavKeplerSet->bitOpAddNavParam)
    {
        ulRslt = NAS_LPP_DecodeAddNavParam(pucDecodeBitStream, pulCurrentBitPos,
                                         &(pstNavKeplerSet->stAddNavParam));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstNavKeplerSet->bitOpNavClockNavKeplerianSetExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_NAVKEPLERSET_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos,
                               __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCnavKeplerSet
Description     :����LPP_NAV_MODEL_CNAV_KEPLERIAN_SET_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
NavModelCNAV-KeplerianSet ::= SEQUENCE {
    cnavTop             INTEGER (0..2015),
    cnavURAindex        INTEGER (-16..15),
    cnavDeltaA          INTEGER (-33554432..33554431),
    cnavAdot            INTEGER (-16777216..16777215),
    cnavDeltaNo         INTEGER (-65536..65535),
    cnavDeltaNoDot      INTEGER (-4194304..4194303),
    cnavMo              INTEGER (-4294967296..4294967295),
    cnavE               INTEGER (0..8589934591),
    cnavOmega           INTEGER (-4294967296..4294967295),
    cnavOMEGA0          INTEGER (-4294967296..4294967295),
    cnavDeltaOmegaDot   INTEGER (-65536..65535),
    cnavIo              INTEGER (-4294967296..4294967295),
    cnavIoDot           INTEGER (-16384..16383),
    cnavCis             INTEGER (-32768..32767),
    cnavCic             INTEGER (-32768..32767),
    cnavCrs             INTEGER (-8388608..8388607),
    cnavCrc             INTEGER (-8388608..8388607),
    cnavCus             INTEGER (-1048576..1048575),
    cnavCuc             INTEGER (-1048576..1048575),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCnavKeplerSet
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_NAV_MODEL_CNAV_KEPLERIAN_SET_STRU                  *pstCnavKerplerSet
)
{
    VOS_UINT32                                              ulRslt          = 0;

    /*������չ��*/
    pstCnavKerplerSet->bitOpNAVModelCnavKeplerianSetExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����top*/
    pstCnavKerplerSet->usCnavTop = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                            pulCurrentBitPos, 11);
    if(pstCnavKerplerSet->usCnavTop > 2015)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_CNAVKEPLERSET_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos,
                               __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����aindex*/
    pstCnavKerplerSet->sCnavURAindex = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                               pulCurrentBitPos, 5) - 16;

    /*����deltaA*/
    pstCnavKerplerSet->lCnavDeltaA = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                             pulCurrentBitPos, 26) - 33554432;

    /*����adot*/
    pstCnavKerplerSet->lCnavAdot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                           pulCurrentBitPos, 25) - 16777216;

    /*����no*/
    pstCnavKerplerSet->lCnavDeltaNo = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 17) - 65536;

    /*����nodot*/
    pstCnavKerplerSet->lCnavDeltaNoDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                 pulCurrentBitPos, 23) - 4194304;

    /*����M0*/
    ulRslt= NAS_LPP_GetLongDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 33,
                                            (VOS_UINT64 *) &(pstCnavKerplerSet->llCnavMo));
    pstCnavKerplerSet->llCnavMo -= 4294967296;

    /*����E*/
    ulRslt= NAS_LPP_GetLongDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 33,
                                           &(pstCnavKerplerSet->ullCnavE));


    /*����omega*/
    ulRslt= NAS_LPP_GetLongDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 33,
                                            (VOS_UINT64 *)&(pstCnavKerplerSet->llCnavOmega));

    pstCnavKerplerSet->llCnavOmega -= 4294967296;

    /*����omega0*/
    ulRslt= NAS_LPP_GetLongDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 33,
                                            (VOS_UINT64 *)&(pstCnavKerplerSet->llCnavOMEGA0));

    pstCnavKerplerSet->llCnavOMEGA0 -= 4294967296;

    /*����dot*/
    pstCnavKerplerSet->lCnavDeltaOmegaDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 17) - 65536;

    /*����IO*/
    ulRslt= NAS_LPP_GetLongDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 33,
                                            (VOS_UINT64 *)&(pstCnavKerplerSet->llCnavIo));

    pstCnavKerplerSet->llCnavIo -= 4294967296;

    /*����iddot*/
    pstCnavKerplerSet->lCnavIoDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                            pulCurrentBitPos, 15) - 16384;

    /*����cis*/
    pstCnavKerplerSet->sCnavCis = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                      pulCurrentBitPos, 16) - 32768);

    /*����cic*/
    pstCnavKerplerSet->sCnavCic = (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                      pulCurrentBitPos, 16) - 32768);

    /*����cRs*/
    pstCnavKerplerSet->lCnavCrs = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 24) - 8388608;

    /*����cRc*/
    pstCnavKerplerSet->lCnavCrc = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 24) - 8388608;

    /*����cus*/
    pstCnavKerplerSet->lCnavCus = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 21) - 1048576;

    /*����cuc*/
    pstCnavKerplerSet->lCnavCuc = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 21) - 1048576;

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstCnavKerplerSet->bitOpNAVModelCnavKeplerianSetExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_CNAVKEPLERSET_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGlonassEcef
Description     :����LPP_NAV_MODEL_GLONASS_ECEF_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
NavModel-GLONASS-ECEF ::= SEQUENCE {
    gloEn               INTEGER (0..31),
    gloP1               BIT STRING (SIZE(2)),
    gloP2               BOOLEAN,
    gloM                INTEGER (0..3),
    gloX                INTEGER (-67108864..67108863),
    gloXdot             INTEGER (-8388608..8388607),
    gloXdotdot          INTEGER (-16..15),
    gloY                INTEGER (-67108864..67108863),
    gloYdot             INTEGER (-8388608..8388607),
    gloYdotdot          INTEGER (-16..15),
    gloZ                INTEGER (-67108864..67108863),
    gloZdot             INTEGER (-8388608..8388607),
    gloZdotdot          INTEGER (-16..15),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGlonassEcef
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_NAV_MODEL_GLONASS_ECEF_STRU    *pstGlonassEcef)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��*/
    pstGlonassEcef->bitOpNavModelGLONASSECEFExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����EN*/
    pstGlonassEcef->ucGloEn = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                      pulCurrentBitPos, 5);

    /*����P1*/
    pstGlonassEcef->ucGloP1 = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                      pulCurrentBitPos, 2);

    /*����P2*/
    pstGlonassEcef->bGloP2 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                          pulCurrentBitPos, 1);

    /*����M*/
    pstGlonassEcef->ulGloM = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                     pulCurrentBitPos, 2);

    /*����X*/
    pstGlonassEcef->lGloX = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                    pulCurrentBitPos, 27) - 67108864;

    /*����xdot*/
    pstGlonassEcef->lGloXdot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 24) - 8388608;

    /*����xdotdot*/
    pstGlonassEcef->lGloXdotdot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 5) - 16;

    /*����Y*/
    pstGlonassEcef->lGloY = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                    pulCurrentBitPos, 27) - 67108864;

    /*����Ydot*/
    pstGlonassEcef->lGloYdot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 24) - 8388608;

    /*����Ydotdot*/
    pstGlonassEcef->lGloYdotdot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 5) - 16;

    /*����Z*/
    pstGlonassEcef->lGloZ = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                    pulCurrentBitPos, 27) - 67108864;

    /*����Zdot*/
    pstGlonassEcef->lGloZdot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 24) - 8388608;

    /*����Zdotdot*/
    pstGlonassEcef->lGloZdotdot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 5) - 16;

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGlonassEcef->bitOpNavModelGLONASSECEFExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GLONASSECEF_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGlonassEcef
Description     :����LPP_NAV_MODEL_GLONASS_ECEF_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
NavModel-SBAS-ECEF ::= SEQUENCE {
    sbasTo              INTEGER (0..5399)                   OPTIONAL,   -- Cond ClockModel
    sbasAccuracy        BIT STRING (SIZE(4)),
    sbasXg              INTEGER (-536870912..536870911),
    sbasYg              INTEGER (-536870912..536870911),
    sbasZg              INTEGER (-16777216..16777215),
    sbasXgDot           INTEGER (-65536..65535),
    sbasYgDot           INTEGER (-65536..65535),
    sbasZgDot           INTEGER (-131072..131071),
    sbasXgDotDot        INTEGER (-512..511),
    sbagYgDotDot        INTEGER (-512..511),
    sbasZgDotDot        INTEGER (-512..511),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeSbasEcef
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_NAV_MODEL_SBAS_STRU            *pstSbassEcef)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��*/
    pstSbassEcef->bitOpNavModelSBASExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                      pulCurrentBitPos, 1);

    /*����option*/
    pstSbassEcef->bitOpSbasTo = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                             pulCurrentBitPos, 1);

    /*����sbasto*/
    if(NAS_LPP_SLCT == pstSbassEcef->bitOpSbasTo)
    {
        pstSbassEcef->sSbasTo = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                         pulCurrentBitPos, 13);
        if(pstSbassEcef->sSbasTo > 5399)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_SBASECEF_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pulCurrentBitPos, __LINE__, 0);
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
    }

    /*����Accuracy*/
    pstSbassEcef->sSbasAccuracy = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                           pulCurrentBitPos, 4);

    /*����X*/
    pstSbassEcef->lSbasXg = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                    pulCurrentBitPos, 30) - 536870912;

    /*����Y*/
    pstSbassEcef->lSbasYg = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                    pulCurrentBitPos, 30) - 536870912;

    /*����Z*/
    pstSbassEcef->lSbasZg = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                    pulCurrentBitPos, 25) - 16777216;

    /*����XDOT*/
    pstSbassEcef->lSbasXgDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 17) - 65536;

    /*����YDOT*/
    pstSbassEcef->lSbasYgDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 17) - 65536;

    /*����ZDOT*/
    pstSbassEcef->lSbasZgDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 18) - 131072;

    /*����xdotdot*/
    pstSbassEcef->lSbasXgDotDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 10) - 512;

    /*����ydotdot*/
    pstSbassEcef->lSbasYgDotDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 10) - 512;

    /*����Zdotdot*/
    pstSbassEcef->lSbasZgDotDot = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 10) - 512;


    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstSbassEcef->bitOpNavModelSBASExt )
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_SBASECEF_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;

}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssOrbitModel
Description     :����LPP_GNSS_ORBIT_MODEL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-OrbitModel ::= CHOICE {
    keplerianSet            NavModelKeplerianSet,           -- Model-1
    nav-KeplerianSet        NavModelNAV-KeplerianSet,       -- Model-2
    cnav-KeplerianSet       NavModelCNAV-KeplerianSet,      -- Model-3
    glonass-ECEF            NavModel-GLONASS-ECEF,          -- Model-4
    sbas-ECEF               NavModel-SBAS-ECEF,             -- Model-5
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssOrbitModel
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ORBIT_MODEL_STRU          *pstGnssOrbitModel)
{
    VOS_UINT32                          ulRslt          = 0;

    /*����choice*/
    ulRslt= NAS_LPP_DecodeExtChoiceClockMoel(pucDecodeBitStream, pulCurrentBitPos, 3,
                                           &(pstGnssOrbitModel->ulChoice));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������Ϣ��*/
    switch(pstGnssOrbitModel->ulChoice)
    {
        case LPP_NAV_MODEL_KEPLERIAN_SET_CHOSEN:
            ulRslt = NAS_LPP_DecodeKeplerSet(pucDecodeBitStream, pulCurrentBitPos,
                                           &(pstGnssOrbitModel->u.stkeplerianSet));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_NAV_MODEL_NAV_KEPLERIAN_SET_CHOSEN:
            ulRslt = NAS_LPP_DecodeNavKeplerSet(pucDecodeBitStream, pulCurrentBitPos,
                                              &(pstGnssOrbitModel->u.stNavKeplerianSet));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_NAV_MODEL_CNAV_KEPLERIAN_SET_CHOSEN:
            ulRslt = NAS_LPP_DecodeCnavKeplerSet(pucDecodeBitStream, pulCurrentBitPos,
                                                &(pstGnssOrbitModel->u.stCnavKeplerianSet));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_NAV_MODEL_GLONASS_ECEF_CHOSEN:
            ulRslt = NAS_LPP_DecodeGlonassEcef(pucDecodeBitStream, pulCurrentBitPos,
                                             &(pstGnssOrbitModel->u.stGlonassEcef));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_NAV_MODEL_SBAS_CHOSEN:
            ulRslt = NAS_LPP_DecodeSbasEcef(pucDecodeBitStream, pulCurrentBitPos,
                                          &(pstGnssOrbitModel->u.stSbasEcef));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_DECODE_SUCC;

}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssNavModelListElement
Description     :����LPP_GNSS_NAV_MODEL_SATELLITE_LIST_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-NavModelSatelliteElement ::= SEQUENCE {
    svID                SV-ID,
    svHealth            BIT STRING (SIZE(8)),
    iod                 BIT STRING (SIZE(11)),
    gnss-ClockModel     GNSS-ClockModel,
    gnss-OrbitModel     GNSS-OrbitModel,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssNavModelListElement
(
    VOS_UINT8                                           *pucDecodeBitStream,
    VOS_UINT32                                          *pulCurrentBitPos,
    LPP_GNSS_NAV_MODEL_SATELLITE_LIST_ELEMENT_STRU      *pstGnssNavModelSatListElement)
{
    VOS_UINT32                                           ulRslt = 0;

    /*������չ��*/
    pstGnssNavModelSatListElement->bitOpGNSSNavModelSatelliteListElementExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����svid*/
    ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos,
                              &(pstGnssNavModelSatListElement->stSvId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����SvHealth*/
    pstGnssNavModelSatListElement->usSvHealth = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                         pulCurrentBitPos, 8);

    /*����iod*/
    pstGnssNavModelSatListElement->usIod = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 11);

    /*����ClockModel*/
    ulRslt = NAS_LPP_DecodeGnssClockModel(pucDecodeBitStream, pulCurrentBitPos,
                                        &(pstGnssNavModelSatListElement->stGNSSClockModel));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����ClockModel*/
    ulRslt = NAS_LPP_DecodeGnssOrbitModel(pucDecodeBitStream, pulCurrentBitPos,
                                        &(pstGnssNavModelSatListElement->stGNSSOrbitModel));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssNavModelSatListElement->bitOpGNSSNavModelSatelliteListElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSNAVMODELLISTELEMENT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;

}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssSatLiteList
Description     :����LPP_GNSS_NAVIGATION_MODEL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-NavModelSatelliteList ::= SEQUENCE (SIZE(1..64)) OF GNSS-NavModelSatelliteElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssSatLiteList
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_GNSS_NAV_MODEL_SATELLITE_LIST_STRU                 *pstGnssNavModelSatList)
{
    VOS_UINT32                                              ulRslt = 0;
    VOS_UINT32                                              ulGnssNavModelSatNum = 0;
    VOS_UINT32                                              ulLoop = 0;

    /*�������ֵ*/
    ulGnssNavModelSatNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 6);
    ulGnssNavModelSatNum += 1;
    pstGnssNavModelSatList->ulGNSSNavModelSatelliteListCnt = ulGnssNavModelSatNum;
    if (LPP_MAX_NAV_MODEL_SAT_ELEMENT_LEN < ulGnssNavModelSatNum)
    {
        NAS_LPP_ASN_FAIL_Message( NAS_LPP_DECODE_GNSSSATLITELIST_ERROR,
                                  NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                 *pulCurrentBitPos,
                                  __LINE__,
                                  ulGnssNavModelSatNum);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    for(ulLoop = 0; ulLoop < pstGnssNavModelSatList->ulGNSSNavModelSatelliteListCnt ; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeGnssNavModelListElement(pucDecodeBitStream, pulCurrentBitPos,
                                                     &(pstGnssNavModelSatList->astGNSSNavModelSatelliteListArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssNavigationModel
Description     :����LPP_GNSS_NAVIGATION_MODEL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-NavigationModel ::= SEQUENCE {
    nonBroadcastIndFlag     INTEGER (0..1),
    gnss-SatelliteList      GNSS-NavModelSatelliteList,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssNavigationModel
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_NAVIGATION_MODEL_STRU     *pstGnssNavigationModel
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��*/
    pstGnssNavigationModel->bitOpGNSSNavigationModelExt = NAS_LPP_GetDataFromBitStream(
                                                                                        pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 1);

    /*����IndFlag*/
    pstGnssNavigationModel->ucNonBroadcastIndFlag = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                            pulCurrentBitPos, 1);

    /*����satliteList*/
    ulRslt = NAS_LPP_DecodeGnssSatLiteList(pucDecodeBitStream, pulCurrentBitPos,
                                          (LPP_GNSS_NAV_MODEL_SATELLITE_LIST_STRU*)&(pstGnssNavigationModel->stGNSSSatelliteList));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssNavigationModel->bitOpGNSSNavigationModelExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSNAVIGATIONMODEL_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssBadSignallListElement
Description     :����LPP_GNSS_BAD_SIGNAL_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-SignalIDs  ::= SEQUENCE {
    gnss-SignalIDs      BIT STRING (SIZE(8)),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssSignalIDS
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_SIGNAL_IDS_STRU           *pstGnssSingalIds
)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��ʶλ*/
    pstGnssSingalIds->bitOpGNSSSignalIDsExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                           pulCurrentBitPos, 1);

    /*������չsignalIds*/
    pstGnssSingalIds->ucGNSSSignalIds = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 8);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssSingalIds->bitOpGNSSSignalIDsExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSSIGNALIDS_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssBadSignallListElement
Description     :����LPP_GNSS_BAD_SIGNAL_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
BadSignalElement ::= SEQUENCE {
    badSVID             SV-ID,
    badSignalID         GNSS-SignalIDs  OPTIONAL,   -- Need OP
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssBadSignallListElement
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_GNSS_BAD_SIGNAL_ELEMENT_STRU        *pstGnssBadSignalElement)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��ʶλ*/
    pstGnssBadSignalElement->bitOpBadSignalElementExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����option*/
    pstGnssBadSignalElement->bitOpGNSSSignalIds = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                               pulCurrentBitPos, 1);

    /*����svid*/
    ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos,
                              &(pstGnssBadSignalElement->stBadSvid));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����badSignalID*/
    if(NAS_LPP_SLCT == pstGnssBadSignalElement->bitOpGNSSSignalIds)
    {
        ulRslt = NAS_LPP_DecodeGnssSignalIDS(pucDecodeBitStream, pulCurrentBitPos,
                                           &(pstGnssBadSignalElement->stBadSignalId));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssBadSignalElement->bitOpBadSignalElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSBADSIGNALLISTELEMENT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;

}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssBadSignalList
Description     :����LPP_GNSS_BAD_SIGNAL_LIST_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-BadSignalList ::= SEQUENCE (SIZE(1..64)) OF BadSignalElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssBadSignalList
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_GNSS_BAD_SIGNAL_LIST_STRU           *pstGnssBadSignalList
)
{
    VOS_UINT32      ulRslt = 0;
    VOS_UINT32      ulGnssBadSignalListNum = 0;
    VOS_UINT32      ulLoop = 0;

    /*�������ֵ*/
    ulGnssBadSignalListNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 6);
    ulGnssBadSignalListNum += 1;
    pstGnssBadSignalList->ulGNSSBadSignalListCnt = ulGnssBadSignalListNum;
    if (LPP_MAX_BAD_SIGNAL_ELEMENT_LEN < ulGnssBadSignalListNum)
    {
        NAS_LPP_ASN_FAIL_Message( NAS_LPP_DECODE_GNSSBADSIGNALLIST_ERROR,
                                  NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                 *pulCurrentBitPos,
                                  __LINE__,
                                  ulGnssBadSignalListNum);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    for(ulLoop = 0; ulLoop < pstGnssBadSignalList->ulGNSSBadSignalListCnt; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeGnssBadSignallListElement(pucDecodeBitStream, pulCurrentBitPos,
                                                       &(pstGnssBadSignalList->stGNSSBadSignalListArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssRealTimeIntegrity
Description     :����LPP_GNSS_REALTIME_INTERGRITY_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-RealTimeIntegrity ::= SEQUENCE {
    gnss-BadSignalList  GNSS-BadSignalList,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssRealTimeIntegrity
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_REALTIME_INTERGRITY_STRU  *pstGnssRealIntergarity
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��ʶλ*/
    pstGnssRealIntergarity->bitOpGNSSRealtimeIntergrityExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����signalList*/
    ulRslt = NAS_LPP_DecodeGnssBadSignalList(pucDecodeBitStream, pulCurrentBitPos,
                                           (LPP_GNSS_BAD_SIGNAL_LIST_STRU*)&(pstGnssRealIntergarity->stGNSSBadSignalList));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssRealIntergarity->bitOpGNSSRealtimeIntergrityExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSREALTIMEINTEGRITY_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssBadBitsSgnListElement
Description     :����LPP_GNSS_DATA_BITS_SGN_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-DataBitsSgnElement ::= SEQUENCE {
    gnss-SignalType         GNSS-SignalID,
    gnss-DataBits           BIT STRING (SIZE (1..1024)),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssBadBitsSgnListElement
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_GNSS_DATA_BITS_SGN_ELEMENT_STRU     *pstGnssDataBitsSgnElement
)
{
    VOS_UINT32                               ulRslt         = 0;
    VOS_UINT32                               ulLoop         = 0;
    VOS_UINT32                               ulAlignFlag    = 1;
    VOS_UINT32                               ulDataByte     = 0;

    /*������չ��ʶλ*/
    pstGnssDataBitsSgnElement->bitOpGNSSDataBitsSgnElementExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����signal Type*/
    ulRslt = NAS_LPP_DecodeGnssSignalID(pucDecodeBitStream, pulCurrentBitPos,
                                      &(pstGnssDataBitsSgnElement->stGNSSSignalType));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����gnss-Databits*/
    pstGnssDataBitsSgnElement->ulGnssDataBitsNum =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 10) + 1;
    ulDataByte = (pstGnssDataBitsSgnElement->ulGnssDataBitsNum)/8;
    do
    {
        /*��������������Ӧ��bit string������1--8֮����ֱ��ȡ���������ֵ�����*/
        if((pstGnssDataBitsSgnElement->ulGnssDataBitsNum < 8) && (pstGnssDataBitsSgnElement->ulGnssDataBitsNum > 1))
        {
            pstGnssDataBitsSgnElement->aucGNSSDataBitsArray[ulLoop] =
                (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos,
                                                       (VOS_UINT8)(pstGnssDataBitsSgnElement->ulGnssDataBitsNum));
            break;
        }

        /*�ܳ��ȳ���8������*/
        /*AlignFlag��ʾ��ǰbit string�Ƿ���8bit����ģ���������䣬�����Ƚ�Ƕ���Ĳ��֣������ٽ�8����������byte
          ע��:���ڷǶ���ĳ��������統ǰ��Ҫ��9��bit��ulDataByte��Ϊѭ��������������Ҫ���Σ������������
          ѭ������Ҫ��1
        */
        if(((pstGnssDataBitsSgnElement->ulGnssDataBitsNum) % 8 != 0) && (1 == ulAlignFlag))
        {
            pstGnssDataBitsSgnElement->aucGNSSDataBitsArray[ulLoop] =
                (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos,
                                                       (VOS_UINT8)((pstGnssDataBitsSgnElement->ulGnssDataBitsNum) % 8));
            ulAlignFlag = 0;
            ulDataByte++;
            ulLoop++;
        }
        else
        {
            /*ʣ�µĶ���8����������ֱ��ȡ����*/
            pstGnssDataBitsSgnElement->aucGNSSDataBitsArray[ulLoop] =
                (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
            ulLoop++;
        }
    }
    while(ulLoop < ulDataByte);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssDataBitsSgnElement->bitOpGNSSDataBitsSgnElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSBADBITSSGNLISTELEMENT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;

}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeDataBitsSgnList
Description     :����LPP_GNSS_DATA_BITS_SGN_LIST_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-DataBitsSgnList ::= SEQUENCE (SIZE(1..8)) OF GNSS-DataBitsSgnElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeDataBitsSgnList
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_DATA_BITS_SGN_LIST_STRU   *pstGnssDataBitsSgnList
)
{
    VOS_UINT32                          ulRslt                  = 0;
    VOS_UINT32                          ulGnssBadBitSgnListNum  = 0;
    VOS_UINT32                          ulLoop                  = 0;

    /*�������ֵ*/
    ulGnssBadBitSgnListNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 3);
    ulGnssBadBitSgnListNum += 1;
    pstGnssDataBitsSgnList->ulGNSSDataBitsSgnListCnt = ulGnssBadBitSgnListNum;

    for(ulLoop = 0; ulLoop < pstGnssDataBitsSgnList->ulGNSSDataBitsSgnListCnt; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeGnssBadBitsSgnListElement(pucDecodeBitStream, pulCurrentBitPos,
                                                       &(pstGnssDataBitsSgnList->astGNSSDataBitsSgnElementArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssBadBitsSatListElement
Description     :����LPP_GNSS_DATA_BITS_SAT_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-DataBitsSatElement ::= SEQUENCE {
    svID                    SV-ID,
    gnss-DataBitsSgnList    GNSS-DataBitsSgnList,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssBadBitsSatListElement
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_GNSS_DATA_BITS_SAT_ELEMENT_STRU                    *pstGnssDataBitsSatElment
)
{
    VOS_UINT32                                              ulRslt = 0;

    /*������չ��ʶλ*/
    pstGnssDataBitsSatElment->bitOpGNSSDataBitsSatElementExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����svid*/
    ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos, &(pstGnssDataBitsSatElment->stSvId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����GNSS-databitsSgnList*/
    ulRslt = NAS_LPP_DecodeDataBitsSgnList(pucDecodeBitStream, pulCurrentBitPos,
                                         &(pstGnssDataBitsSatElment->stGNSSDataBitsSgnList));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT ==  pstGnssDataBitsSatElment->bitOpGNSSDataBitsSatElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSBADBITSSATLISTELEMENT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssDataBitAssit
Description     :����LPP_GNSS_DATA_BIT_ASSIST_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-DataBitsSatList ::= SEQUENCE (SIZE(1..64))OF GNSS-DataBitsSatElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeDataBitsSatList
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_DATA_BITS_SATLIST_STRU    *pstGnssDataBitAssitList
)
{
    VOS_UINT32                          ulRslt               = 0;
    VOS_UINT32                          ulGnssDataBitListNum = 0;
    VOS_UINT32                          ulLoop               = 0;

    /*�������ֵ*/
    ulGnssDataBitListNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 6);
    ulGnssDataBitListNum += 1;
    pstGnssDataBitAssitList->ulGNSSDataBitsSatListCnt = ulGnssDataBitListNum;
    if (LPP_MAX_GNSS_DATA_BITS_SAT_ELEMENT_LEN < ulGnssDataBitListNum)
    {
        NAS_LPP_ASN_FAIL_Message( NAS_LPP_DECODE_DATABITSSATLIST_ERROR,
                                  NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                 *pulCurrentBitPos,
                                  __LINE__,
                                  ulGnssDataBitListNum);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    for(ulLoop = 0; ulLoop < pstGnssDataBitAssitList->ulGNSSDataBitsSatListCnt; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeGnssBadBitsSatListElement(pucDecodeBitStream, pulCurrentBitPos,
                                                       &(pstGnssDataBitAssitList->astGNSSDataBitsSatListArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssDataBitAssit
Description     :����LPP_GNSS_DATA_BIT_ASSIST_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-DataBitAssistance ::= SEQUENCE {
    gnss-TOD                INTEGER (0..3599),
    gnss-TODfrac            INTEGER (0..999)        OPTIONAL,   -- Need ON
    gnss-DataBitsSatList    GNSS-DataBitsSatList,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeDataBitsAssit
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_DATA_BIT_ASSIST_STRU      *pstGnssDataBitAssit
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��ʶλ*/
    pstGnssDataBitAssit->bitOpGNSSDataBitAssistExt =
                NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����option*/
    pstGnssDataBitAssit->bitOpGNSSTodFrac = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                         pulCurrentBitPos, 1);

    /*����gnss-tod*/
    pstGnssDataBitAssit->usGNSSTod = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 12);
    if(pstGnssDataBitAssit->usGNSSTod > 3599)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_DATABITSASSIT_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__,
                                 pstGnssDataBitAssit->usGNSSTod);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����gnss-tod-Frac*/
    if(NAS_LPP_SLCT == pstGnssDataBitAssit->bitOpGNSSTodFrac)
    {
        pstGnssDataBitAssit->usGNSSTodFrac =
            (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 10);
        if(pstGnssDataBitAssit->usGNSSTodFrac > 999)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_DATABITSASSIT_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pulCurrentBitPos, __LINE__,
                                     pstGnssDataBitAssit->usGNSSTodFrac);
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
    }

    /*����GNSS-databitsatlist*/
    ulRslt = NAS_LPP_DecodeDataBitsSatList(pucDecodeBitStream, pulCurrentBitPos,
                                         &(pstGnssDataBitAssit->stGNSSDataBitsSatlist));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssDataBitAssit->bitOpGNSSDataBitAssistExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_DATABITSASSIT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssAcquisitAssitListElement
Description     :����LPP_GNSS_ACQUISIT_ASSIST_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeDopplerUncertExtR10
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    VOS_UINT8                               ucLen,
    LPP_DOPPLER_EXTR10_ENUM_UINT8           *penDopplerExt10
)
{
    VOS_UINT32      ulReturnRslt = 0;

    ulReturnRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                                ucLen, penDopplerExt10);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DOPPLERUNCERTEXTR10_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return      ulReturnRslt;
    }
    if((NAS_LPP_EXT_ENUMERATED_BUTT == *penDopplerExt10)||(*penDopplerExt10 > 4))
    {
        *penDopplerExt10 = LPP_DOPPLER_EXTR10_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DOPPLERUNCERTEXTR10_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}


/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssAcquisitAssitListElement
Description     :����LPP_GNSS_ACQUISIT_ASSIST_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-AcquisitionAssistElement  ::= SEQUENCE {
    svID                        SV-ID,
    doppler0                    INTEGER (-2048..2047),
    doppler1                    INTEGER (0..63),
    dopplerUncertainty          INTEGER (0..4),
    codePhase                   INTEGER (0..1022),
    intCodePhase                INTEGER (0..127),
    codePhaseSearchWindow       INTEGER (0..31),
    azimuth                     INTEGER (0..511),
    elevation                   INTEGER (0..127),
    ...,
    codePhase1023               BOOLEAN             OPTIONAL,   -- Need OP
    dopplerUncertaintyExt-r10   ENUMERATED {    d60,
                                                d80,
                                                d100,
                                                d120,
                                                noInformation, ... }    OPTIONAL    -- Need ON
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssAcquisitAssitListElement
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_GNSS_ACQUISIT_ASSIST_ELEMENT_STRU                  *pstGnssAcqusitAssitElement
)
{
    VOS_UINT32                                              ulRslt                  = 0;
    VOS_UINT32                                              ulExtIeNum              = 0;
    VOS_UINT32                                              ulLoop                  = 0;
    VOS_UINT32                                              ulExtIeInValidNum       = 0;
    VOS_UINT32                                              ulExtIeInvalidOption    = 0;
    VOS_UINT32                                              ulLVLen                 = 0;

    /*������չ��ʶλ*/
    pstGnssAcqusitAssitElement->bitOpGNSSAcquisitAssistElementExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����svid*/
    ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos, &(pstGnssAcqusitAssitElement->stSvId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����doppler0*/
    pstGnssAcqusitAssitElement->sDoppler0 =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 12) - 2048;

    /*����doppler0*/
    pstGnssAcqusitAssitElement->ucDoppler1 =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 6);

    /*����uncertainty*/
    pstGnssAcqusitAssitElement->ucDopplerUncertainty =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 3);
    if(pstGnssAcqusitAssitElement->ucDopplerUncertainty > 4)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSACQUISITIONASSITLISTELEMENT_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__,
                                 pstGnssAcqusitAssitElement->ucDopplerUncertainty);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����codePhase*/
    pstGnssAcqusitAssitElement->usCodePhase =
        (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 10);
    if(pstGnssAcqusitAssitElement->usCodePhase > 1022)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSACQUISITIONASSITLISTELEMENT_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__,
                                 pstGnssAcqusitAssitElement->usCodePhase);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����intcodephase*/
    pstGnssAcqusitAssitElement->ucIntCodePhase =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7);

    /*����SearchWindow*/
    pstGnssAcqusitAssitElement->ucCodePhaseSearchWindow =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 5);

    /*����azimuth*/
    pstGnssAcqusitAssitElement->ucAzimuth =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 9);

    /*����elevation*/
    pstGnssAcqusitAssitElement->ucElevation =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7);


    /*û��ѡ����չ��*/
    if(NAS_LPP_NO_SLCT == pstGnssAcqusitAssitElement->bitOpGNSSAcquisitAssistElementExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*ѡ����չ��*/
    /*������չ��ļ���L-1*/
    ulRslt = NAS_LPP_DecodeNormalSmallInt(pucDecodeBitStream, pulCurrentBitPos, &ulExtIeNum);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    /*�����������չ��ļ�����1����ʾ�����������İ汾����չ��ļ���*/
    ulExtIeNum += 1;

    /*�����Э��汾һ����չ���option*/
    pstGnssAcqusitAssitElement->bitOpCodePhase1023 =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstGnssAcqusitAssitElement->bitOpDopplerUncertaintyExtR10 =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*�����Э��汾��һ����չ���option*/
    for(ulLoop = 0; ulLoop < ulExtIeNum - 2; ulLoop++)
    {
        ulExtIeInvalidOption = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
        if(NAS_LPP_SLCT == ulExtIeInvalidOption)
        {
            ulExtIeInValidNum++;
        }
    }

    /*������չ��ľ����ֵ*/
    /*����Э��汾һ�µ���Ԫ*/
    if(NAS_LPP_SLCT == pstGnssAcqusitAssitElement->bitOpCodePhase1023)
    {
        /*����L+V*/
        ulLVLen = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
        pstGnssAcqusitAssitElement->bCodePhase1023 =
            NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
        /*�������bit*/
        *pulCurrentBitPos += ulLVLen*8 - 1;
    }

    if(NAS_LPP_SLCT == pstGnssAcqusitAssitElement->bitOpDopplerUncertaintyExtR10)
    {
        /*����L+V*/
        ulLVLen = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
        ulRslt = NAS_LPP_DecodeDopplerUncertExtR10(pucDecodeBitStream, pulCurrentBitPos, 3,
                                                 &(pstGnssAcqusitAssitElement->enDopplerUncertaintyExtR10));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return  ulRslt;
        }
        /*�������bit*/
        /*ע������������λΪʲôҪ����4bit������3bit��? ��Ϊ����չ��ö�ٶ���һ����չλ*/
        *pulCurrentBitPos += ulLVLen*8 - 4;
    }

    /*�����ǰ��չ��ļ�����UE�汾����չ��ļ�����ȣ���˵��Э��汾һ�£��������*/
    if(2 == ulExtIeNum)
    {
        return NAS_LPP_DECODE_SUCC;
    }
    else
    {
        /*Э��汾�ȱ��ظߣ�����Ҫ����ѭ������ʣ�µ�IE��*/
        ulRslt = NAS_LPP_DecodeExtIeWithPartValid(pucDecodeBitStream, pulCurrentBitPos, ulExtIeInValidNum);
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSACQUISITIONASSITLISTELEMENT_ERROR,
                                     NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                    *pulCurrentBitPos, __LINE__,0);
            return ulRslt;
        }

        return NAS_LPP_DECODE_SUCC;
    }


}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssAcquisitonAssitList
Description     :����LPP_GNSS_ACQUISIT_ASSIST_LIST_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-AcquisitionAssistList ::= SEQUENCE (SIZE(1..64)) OF GNSS-AcquisitionAssistElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssAcquisitonAssitList
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ACQUISIT_ASSIST_LIST_STRU *pstGnssAcqusitAssitList
)
{
    VOS_UINT32                          ulRslt                      = 0;
    VOS_UINT32                          ulGnssAcquisitAssitListNum  = 0;
    VOS_UINT32                          ulLoop                      = 0;

    /*�������ֵ*/
    ulGnssAcquisitAssitListNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                              pulCurrentBitPos, 6);
    ulGnssAcquisitAssitListNum += 1;
    pstGnssAcqusitAssitList->ulGNSSAcquisitAssitListCnt = ulGnssAcquisitAssitListNum;
    if (LPP_MAX_GNSS_ACQUSITON_ASSIST_ELMENT_LEN < ulGnssAcquisitAssitListNum)
    {
        NAS_LPP_ASN_FAIL_Message( NAS_LPP_DECODE_GNSSACQUISITONASSITLIST_ERROR,
                                  NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                 *pulCurrentBitPos,
                                  __LINE__,
                                  ulGnssAcquisitAssitListNum);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    for(ulLoop = 0; ulLoop < pstGnssAcqusitAssitList->ulGNSSAcquisitAssitListCnt; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeGnssAcquisitAssitListElement(pucDecodeBitStream, pulCurrentBitPos,
                                                          &(pstGnssAcqusitAssitList->astGNSSAcquisitAssistListArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssAcquisitionAssit
Description     :����LPP_GNSS_ACQUISIT_ASSIST_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-AcquisitionAssistance ::= SEQUENCE {
    gnss-SignalID               GNSS-SignalID,
    gnss-AcquisitionAssistList  GNSS-AcquisitionAssistList,
    ...,
    confidence-r10              INTEGER (0..100)    OPTIONAL    -- Need ON
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssAcquisitionAssit
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ACQUISIT_ASSIST_STRU      *pstGnssAcqusitAssit
)
{
    VOS_UINT32                          ulRslt               = 0;
    VOS_UINT32                          ulExtIeNum           = 0;
    VOS_UINT32                          ulLoop               = 0;
    VOS_UINT32                          ulExtIeInValidNum    = 0;
    VOS_UINT32                          ulExtIeInvalidOption = 0;
    VOS_UINT32                          ulLVLen              = 0;

    /*������չ��ʶλ*/
    pstGnssAcqusitAssit->bitOpGNSSAcquisitAssistExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����signalID*/
    ulRslt = NAS_LPP_DecodeGnssSignalID(pucDecodeBitStream, pulCurrentBitPos,
                                      &(pstGnssAcqusitAssit->stGNSSSignalId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����acuisitonAssitList*/
    ulRslt = NAS_LPP_DecodeGnssAcquisitonAssitList(pucDecodeBitStream, pulCurrentBitPos,
                                                 (LPP_GNSS_ACQUISIT_ASSIST_LIST_STRU*)&(pstGnssAcqusitAssit->stGNSSAcquisitAssistList));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*û��ѡ����չ��*/
    if(NAS_LPP_NO_SLCT ==  pstGnssAcqusitAssit->bitOpGNSSAcquisitAssistExt )
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*ѡ����չ��*/
    /*������չ��ļ���L-1*/
    ulRslt = NAS_LPP_DecodeNormalSmallInt(pucDecodeBitStream, pulCurrentBitPos, &ulExtIeNum);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    /*�����������չ��ļ�����1����ʾ�����������İ汾����չ��ļ���*/
    ulExtIeNum += 1;

    /*�����Э��汾һ����չ���option*/
    pstGnssAcqusitAssit->bitOpConfidenceR10 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*�����Э��汾��һ����չ���option*/
    for(ulLoop = 0; ulLoop < ulExtIeNum - 1; ulLoop++)
    {
        ulExtIeInvalidOption = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
        if(NAS_LPP_SLCT == ulExtIeInvalidOption)
        {
            ulExtIeInValidNum++;
        }
    }

    /*������չ��ľ����ֵ*/
    /*����Э��汾һ�µ���Ԫ*/
    if(NAS_LPP_SLCT == pstGnssAcqusitAssit->bitOpConfidenceR10)
    {
        /*����L+V*/
        ulLVLen = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
        pstGnssAcqusitAssit->ulConfidenceR10 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7);
        if(pstGnssAcqusitAssit->ulConfidenceR10 > 100)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSACQUISITIONASSIT_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pulCurrentBitPos, __LINE__,
                                     pstGnssAcqusitAssit->ulConfidenceR10);
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        /*��������bitλ*/
        *pulCurrentBitPos += ulLVLen*8 - 7;
    }

    /*�����ǰ��չ��ļ�����UE�汾����չ��ļ�����ȣ���˵��Э��汾һ�£��������*/
    if(1 == ulExtIeNum)
    {
        return NAS_LPP_DECODE_SUCC;
    }
    else
    {
        /*Э��汾�ȱ��ظߣ�����Ҫ����ѭ������ʣ�µ�IE��*/
        ulRslt = NAS_LPP_DecodeExtIeWithPartValid(pucDecodeBitStream, pulCurrentBitPos, ulExtIeInValidNum);
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSACQUISITIONASSIT_ERROR,
                                     NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                    *pulCurrentBitPos, __LINE__,0);
            return ulRslt;
        }

        return NAS_LPP_DECODE_SUCC;
    }

}


/*****************************************************************************
Function Name   :NAS_LPP_DecodeKeplerianAlmanacSet
Description     :����LPP_ALMANAC_KEPLERIAN_SET_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
AlmanacKeplerianSet ::= SEQUENCE {
    svID                    SV-ID,
    kepAlmanacE             INTEGER (0..2047),
    kepAlmanacDeltaI        INTEGER (-1024..1023),
    kepAlmanacOmegaDot      INTEGER (-1024..1023),
    kepSVHealth             INTEGER (0..15),
    kepAlmanacAPowerHalf    INTEGER (-65536..65535),
    kepAlmanacOmega0        INTEGER (-32768..32767),
    kepAlmanacW             INTEGER (-32768..32767),
    kepAlmanacM0            INTEGER (-32768..32767),
    kepAlmanacAF0           INTEGER (-8192..8191),
    kepAlmanacAF1           INTEGER (-1024..1023),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeKeplerianAlmanacSet
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_ALMANAC_KEPLERIAN_SET_STRU     *pstAlmanacKeplerSet
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��ʶλ*/
    pstAlmanacKeplerSet->bitOpAlmanacKeplerianSetExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����svid*/
    ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos, &(pstAlmanacKeplerSet->stSvId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����CE*/
   pstAlmanacKeplerSet->usKepAlmanacE = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                 pulCurrentBitPos, 11);

   /*����TAI*/
   pstAlmanacKeplerSet->sKepAlmanacDeltaI = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 11) - 1024;

   /*����dot*/
   pstAlmanacKeplerSet->sKepAlmanacOmegaDot = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                      pulCurrentBitPos, 11) - 1024;

   /*����health*/
   pstAlmanacKeplerSet->usKepSVHealth = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 4);

   /*����powerHalf*/
   pstAlmanacKeplerSet->ulKepAlmanacAPowerHalf = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                         pulCurrentBitPos, 17) - 65536;

   /*����omega0*/
   pstAlmanacKeplerSet->sKepAlmanacOmega0 =
    (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16) - 32768);

   /*����W*/
   pstAlmanacKeplerSet->sKepAlmanacW =
    (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16) - 32768);

   /*����M0*/
   pstAlmanacKeplerSet->sKepAlmanacM0 =
    (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16) - 32768);

   /*����AF0*/
   pstAlmanacKeplerSet->sKepAlmanacAF0 =
    (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 14) - 8192;

   /*����AF1*/
   pstAlmanacKeplerSet->sKepAlmanacAF1 =
    (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 11) - 1024;

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT ==  pstAlmanacKeplerSet->bitOpAlmanacKeplerianSetExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_KEPLERIANALMANACSET_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos,
                               __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeKeplerianNAVAlmanac
Description     :����LPP_ALMANAC_NAV_KEPLERIAN_SET_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
AlmanacNAV-KeplerianSet ::= SEQUENCE {
    svID                    SV-ID,
    navAlmE                 INTEGER (0..65535),
    navAlmDeltaI            INTEGER (-32768..32767),
    navAlmOMEGADOT          INTEGER (-32768..32767),
    navAlmSVHealth          INTEGER (0..255),
    navAlmSqrtA             INTEGER (0..16777215),
    navAlmOMEGAo            INTEGER (-8388608..8388607),
    navAlmOmega             INTEGER (-8388608..8388607),
    navAlmMo                INTEGER (-8388608..8388607),
    navAlmaf0               INTEGER (-1024..1023),
    navAlmaf1               INTEGER (-1024..1023),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeKeplerianNAVAlmanac
(
    VOS_UINT8                           *pucDecodeBitStream,
    VOS_UINT32                          *pulCurrentBitPos,
    LPP_ALMANAC_NAV_KEPLERIAN_SET_STRU  *pstAlmanacNavKeplerSet
)
{
     VOS_UINT32                          ulRslt             = 0;

     /*������չ��ʶλ*/
     pstAlmanacNavKeplerSet->bitOpAlmanacNAVKeplerianSetExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

     /*����svid*/
     ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos, &(pstAlmanacNavKeplerSet->stSvId));
     if(NAS_LPP_DECODE_SUCC != ulRslt)
     {
         return ulRslt;
     }

     /*����alme*/
     pstAlmanacNavKeplerSet->usNavAlmE =
        (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16);

     /*����DeltaI*/
     pstAlmanacNavKeplerSet->sNavAlmDeltaI =
        (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16) - 32768);

     /*����dot*/
     pstAlmanacNavKeplerSet->sNavAlmOMEGADOT =
        (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16) - 32768);

     /*����svHealth*/
     pstAlmanacNavKeplerSet->usNavAlmSVHealth =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

     /*����sqrta*/
     pstAlmanacNavKeplerSet->ulNavAlmSqrtA =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 24);

     /*����omegao*/
     pstAlmanacNavKeplerSet->lNavAlmOMEGAo =
        (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 24) - 8388608;

     /*����omega*/
     pstAlmanacNavKeplerSet->lNavAlmOmega =
        (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 24) - 8388608;

     /*����m0*/
     pstAlmanacNavKeplerSet->lNavAlmMo =
        (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 24) - 8388608;

     /*����af0*/
     pstAlmanacNavKeplerSet->sNavAlmaf0 =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 11) - 1024;

     /*����af1*/
     pstAlmanacNavKeplerSet->sNavAlmaf1 =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 11) - 1024;

     /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
     if(NAS_LPP_NO_SLCT ==  pstAlmanacNavKeplerSet->bitOpAlmanacNAVKeplerianSetExt)
     {
         return  NAS_LPP_DECODE_SUCC;
     }

     ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
     if(NAS_LPP_DECODE_SUCC != ulRslt)
     {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_KEPLERIANNAVALMANAC_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos,
                               __LINE__,0);
         return ulRslt;
     }

     return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeKeplerianReducedAlmanac
Description     :����LPP_ALMANAC_REDUCED_KEPLERIAN_SET_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
AlmanacReducedKeplerianSet ::= SEQUENCE {
    svID                    SV-ID,
    redAlmDeltaA            INTEGER (-128..127),
    redAlmOmega0            INTEGER (-64..63),
    redAlmPhi0              INTEGER (-64..63),
    redAlmL1Health          BOOLEAN,
    redAlmL2Health          BOOLEAN,
    redAlmL5Health          BOOLEAN,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeKeplerianReducedAlmanac
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_ALMANAC_REDUCED_KEPLERIAN_SET_STRU  *pstAlmanacReduceKeplerSet
)
{
    VOS_UINT32                               ulRslt               = 0;

    /*������չ��ʶλ*/
    pstAlmanacReduceKeplerSet->bitOpAlmanacReducedKeplerianSetExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����svid*/
    ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos, &(pstAlmanacReduceKeplerSet->stSvId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����deltaA*/
    pstAlmanacReduceKeplerSet->cRedAlmDeltaA =
        (VOS_INT8)((VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8) - 128);

    /*����omega0*/
    pstAlmanacReduceKeplerSet->cRedAlmOmega0 =
        (VOS_INT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7) - 64;

    /*����phi0*/
    pstAlmanacReduceKeplerSet->cRedAlmPhi0 =
        (VOS_INT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7) - 64;

    /*����L1*/
    pstAlmanacReduceKeplerSet->bRedAlmL1Health = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 1);

    /*����L2*/
    pstAlmanacReduceKeplerSet->bRedAlmL2Health = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 1);

    /*����L5*/
    pstAlmanacReduceKeplerSet->bRedAlmL5Health = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 1);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT ==  pstAlmanacReduceKeplerSet->bitOpAlmanacReducedKeplerianSetExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_KEPLERIANREDUCEDALMANAC_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos,
                               __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeKeplerianMidiAlmanac
Description     :����LPP_ALMANAC_MIDI_ALMANAC_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
AlmanacMidiAlmanacSet ::= SEQUENCE {
    svID                    SV-ID,
    midiAlmE                INTEGER (0..2047),
    midiAlmDeltaI           INTEGER (-1024..1023),
    midiAlmOmegaDot         INTEGER (-1024..1023),
    midiAlmSqrtA            INTEGER (0..131071),
    midiAlmOmega0           INTEGER (-32768..32767),
    midiAlmOmega            INTEGER (-32768..32767),
    midiAlmMo               INTEGER (-32768..32767),
    midiAlmaf0              INTEGER (-1024..1023),
    midiAlmaf1              INTEGER (-512..511),
    midiAlmL1Health         BOOLEAN,
    midiAlmL2Health         BOOLEAN,
    midiAlmL5Health         BOOLEAN,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeKeplerianMidiAlmanac
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_ALMANAC_MIDI_ALMANAC_STRU      *pstAlmanacMidiSet
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��ʶλ*/
    pstAlmanacMidiSet->bitOpAlmanacMidiAlmanacSetExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����svid*/
    ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos, &(pstAlmanacMidiSet->stSvId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����mE*/
    pstAlmanacMidiSet->usMidiAlmE = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                             pulCurrentBitPos, 11);

    /*����deltai*/
    pstAlmanacMidiSet->sMidiAlmDelatI = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 11) - 1024;

    /*����dot*/
    pstAlmanacMidiSet->sMidiAlmOmegaDot =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 11) - 1024;

    /*����sprta*/
    pstAlmanacMidiSet->ulMidiAlmSqrtA = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                     pulCurrentBitPos, 17);

    /*����omega0*/
    pstAlmanacMidiSet->sMidiAlmOmega0 =
        (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16) - 32768);

    /*����omega*/
    pstAlmanacMidiSet->sMidiAlmOmega =
        (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16) - 32768);

    /*����M0*/
    pstAlmanacMidiSet->sMidiAlmMo =
        (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16) - 32768);

    /*����AF0*/
    pstAlmanacMidiSet->sMidiAlmaf0 =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 11) - 1024;

    /*����AF1*/
    pstAlmanacMidiSet->sMidiAlmaf1 =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 10) - 512;

    /*����L1*/
    pstAlmanacMidiSet->bMidiAlmL1Health = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 1);

    /*����L2*/
    pstAlmanacMidiSet->bmidiAlmL2Health = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 1);

    /*����L5*/
    pstAlmanacMidiSet->bMidiAlmL5Health = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 1);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT ==  pstAlmanacMidiSet->bitOpAlmanacMidiAlmanacSetExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_KEPLERIANMIDIALMANAC_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos,
                               __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeKeplerianGLONASS
Description     :����LPP_ALMANAC_GLONASS_ALMANAC_SET_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
AlmanacGLONASS-AlmanacSet ::= SEQUENCE {
    gloAlm-NA               INTEGER (1..1461),
    gloAlmnA                INTEGER (1..24),
    gloAlmHA                INTEGER (0..31),
    gloAlmLambdaA           INTEGER (-1048576..1048575),
    gloAlmtlambdaA          INTEGER (0..2097151),
    gloAlmDeltaIa           INTEGER (-131072..131071),
    gloAlmDeltaTA           INTEGER (-2097152..2097151),
    gloAlmDeltaTdotA        INTEGER (-64..63),
    gloAlmEpsilonA          INTEGER (0..32767),
    gloAlmOmegaA            INTEGER (-32768..32767),
    gloAlmTauA              INTEGER (-512..511),
    gloAlmCA                INTEGER (0..1),
    gloAlmMA                BIT STRING (SIZE(2))            OPTIONAL,   -- Need ON
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeKeplerianGLONASS
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_ALMANAC_GLONASS_ALMANAC_SET_STRU                   *pstAlmanacGlonassSet
)
{
    VOS_UINT32                                              ulRslt = 0;

    /*������չ��ʶλ*/
    pstAlmanacGlonassSet->bitOpAlmanacGLONASSAlmanacSetExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����option*/
    pstAlmanacGlonassSet->bitOpGloAlmMa = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 1);

    /*����NA*/
    pstAlmanacGlonassSet->usGloAlmNa =
        (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 11) + 1;
    if(pstAlmanacGlonassSet->usGloAlmNa > 1461)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_KEPLERIANGLONASS_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos,
                               __LINE__,
                                 pstAlmanacGlonassSet->usGloAlmNa);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����na*/
    pstAlmanacGlonassSet->ucGloAlmNa1 =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 5) + 1;
    if(pstAlmanacGlonassSet->ucGloAlmNa1 > 24)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_KEPLERIANGLONASS_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos,
                               __LINE__,
                                 pstAlmanacGlonassSet->ucGloAlmNa1);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����HA*/
    pstAlmanacGlonassSet->ucGloAlmHa =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 5);

    /*����bdaA*/
    pstAlmanacGlonassSet->lGloAlmLambdaA =
        (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 21) - 1048576;

    /*����bdaA*/
    pstAlmanacGlonassSet->ulGloAlmtlambdaA =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 21);

    /*����IA*/
    pstAlmanacGlonassSet->lGloAlmDeltaIa =
        (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 18) - 131072;

    /*����TA*/
    pstAlmanacGlonassSet->lGloAlmDeltaTA =
        (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 22) - 2097152;

    /*����dotA*/
    pstAlmanacGlonassSet->sGloAlmDeltaTdotA =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7) - 64;

    /*����nA*/
    pstAlmanacGlonassSet->usGloAlmEpsilonA =
        (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 15);

    /*����omegaA*/
    pstAlmanacGlonassSet->sGloAlmOmegaA =
        (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16) - 32768);

    /*����tauA*/
    pstAlmanacGlonassSet->sGloAlmTauA =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 10) - 512;

    /*����CA*/
    pstAlmanacGlonassSet->ucGloAlmCA =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����MA*/
    if(NAS_LPP_SLCT == pstAlmanacGlonassSet->bitOpGloAlmMa)
    {
        pstAlmanacGlonassSet->ucGloAlmMA =
            (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 2);
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstAlmanacGlonassSet->bitOpAlmanacGLONASSAlmanacSetExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_KEPLERIANGLONASS_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodestEcefSbasAlmanac
Description     :����LPP_ALMANAC_ECEF_SBAS_ALMANAC_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
AlmanacECEF-SBAS-AlmanacSet ::= SEQUENCE {
    sbasAlmDataID           INTEGER (0..3),
    svID                    SV-ID,
    sbasAlmHealth           BIT STRING (SIZE(8)),
    sbasAlmXg               INTEGER (-16384..16383),
    sbasAlmYg               INTEGER (-16384..16383),
    sbasAlmZg               INTEGER (-256..255),
    sbasAlmXgdot            INTEGER (-4..3),
    sbasAlmYgDot            INTEGER (-4..3),
    sbasAlmZgDot            INTEGER (-8..7),
    sbasAlmTo               INTEGER (0..2047),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEcefSbasAlmanac
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_ALMANAC_ECEF_SBAS_ALMANAC_STRU *pstAlmanacEcfeSbas
)
{
    VOS_UINT32                          ulRslt          = 0;

    /*������չ��ʶλ*/
    pstAlmanacEcfeSbas->bitOpAlmanacECEFSBASAlmanacSetExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����dataID*/
    pstAlmanacEcfeSbas->ulSbasAlmDataID = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 2);

    /*����svid*/
    ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos, &(pstAlmanacEcfeSbas->stSvId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����almHealth*/
    pstAlmanacEcfeSbas->ucSbasAlmHealth =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

    /*����X*/
    pstAlmanacEcfeSbas->sSbasAlmXg =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 15) - 16384;

    /*����Y*/
    pstAlmanacEcfeSbas->sSbasAlmYg =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 15) - 16384;

    /*����Z*/
    pstAlmanacEcfeSbas->cSbasAlmZg =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 9) - 256;

    /*����xdot*/
    pstAlmanacEcfeSbas->cSbasAlmXgdot =
        (VOS_INT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 3) - 4;

    /*����ydot*/
    pstAlmanacEcfeSbas->cSbasAlmYgdot =
        (VOS_INT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 3) - 4;

    /*����zdot*/
    pstAlmanacEcfeSbas->cSbasAlmZgdot =
        (VOS_INT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 4) - 8;

    /*����AlmTo*/
    pstAlmanacEcfeSbas->usSbasAlmTo =
        (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 11);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstAlmanacEcfeSbas->bitOpAlmanacECEFSBASAlmanacSetExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_ECEFSBASALMANAC_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssAlmanacListElement
Description     :����LPP_GNSS_ALMANAC_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-AlmanacElement ::= CHOICE {
    keplerianAlmanacSet     AlmanacKeplerianSet,        -- Model-1
    keplerianNAV-Almanac    AlmanacNAV-KeplerianSet,    -- Model-2
    keplerianReducedAlmanac AlmanacReducedKeplerianSet, -- Model-3
    keplerianMidiAlmanac    AlmanacMidiAlmanacSet,      -- Model-4
    keplerianGLONASS        AlmanacGLONASS-AlmanacSet,  -- Model-5
    ecef-SBAS-Almanac       AlmanacECEF-SBAS-AlmanacSet,-- Model-6
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssAlmanacListElement
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ALMANAC_ELEMENT_STRU      *pstGnssAlmanacElement
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*�������չ��choic�����С�ķǸ�������������*/
    ulRslt = NAS_LPP_DecodeExtChoice(pucDecodeBitStream, pulCurrentBitPos, 3, &(pstGnssAlmanacElement->ulChoice));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    if(LPP_DECODE_EXT_CHOICE_INVALID_VALUE == pstGnssAlmanacElement->ulChoice)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSALMANACLISTELEMENT_ERROR,
                                 NAS_LPP_CHOICE_EXT_OBJECT_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    switch(pstGnssAlmanacElement->ulChoice)
    {
        case LPP_ALMANAC_KEPLERIAN_SET_CHOSEN:
            ulRslt = NAS_LPP_DecodeKeplerianAlmanacSet(pucDecodeBitStream, pulCurrentBitPos,
                                                     &(pstGnssAlmanacElement->u.stKeplerianAlmanacSet));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_ALMANAC_NAV_KEPLERIAN_SET_CHOSEN:
            ulRslt = NAS_LPP_DecodeKeplerianNAVAlmanac(pucDecodeBitStream, pulCurrentBitPos,
                                                     &(pstGnssAlmanacElement->u.stKeplerianNAVAlmanac));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_ALMANAC_REDUCED_KEPLERIAN_SET_CHOSEN:
            ulRslt = NAS_LPP_DecodeKeplerianReducedAlmanac(pucDecodeBitStream, pulCurrentBitPos,
                                                         &(pstGnssAlmanacElement->u.stKeplerianReducedAlmanac));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_ALMANAC_MIDI_ALMANAC_CHOSEN:
            ulRslt = NAS_LPP_DecodeKeplerianMidiAlmanac(pucDecodeBitStream, pulCurrentBitPos,
                                                      &(pstGnssAlmanacElement->u.stKeplerianMidiAlmanac));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_ALMANAC_GLONASS_ALMANAC_SET_CHOSEN:
            ulRslt = NAS_LPP_DecodeKeplerianGLONASS(pucDecodeBitStream, pulCurrentBitPos,
                                                  &(pstGnssAlmanacElement->u.stKeplerianGLONASS));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_ALMANAC_ECEF_SBAS_ALMANAC_CHOSEN:
            ulRslt = NAS_LPP_DecodeEcefSbasAlmanac(pucDecodeBitStream, pulCurrentBitPos,
                                                 &(pstGnssAlmanacElement->u.stEcefSbasAlmanac));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        default:
            return NAS_LPP_DECODE_SUCC;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssAlmanacList
Description     :����LPP_GNSS_ALMANAC_LIST_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-AlmanacList ::= SEQUENCE (SIZE(1..64)) OF GNSS-AlmanacElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssAlmanacList
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ALMANAC_LIST_STRU         *pstGnssAlmanaclist
)
{
    VOS_UINT32                          ulRslt               = 0;
    VOS_UINT32                          ulGnssAlmanacListNum = 0;
    VOS_UINT32                          ulLoop               = 0;

    /*�������ֵ*/
    ulGnssAlmanacListNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 6);
    ulGnssAlmanacListNum += 1;
    pstGnssAlmanaclist->ulGNSSAlmanacListCnt = ulGnssAlmanacListNum;
    if (LPP_MAX_GNSS_ALMANAC_ELMENT_LEN < ulGnssAlmanacListNum)
    {
        NAS_LPP_ASN_FAIL_Message( NAS_LPP_DECODE_GNSSALMANACLIST_ERROR,
                                  NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                 *pulCurrentBitPos,
                                  __LINE__,
                                  ulGnssAlmanacListNum);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    for(ulLoop = 0; ulLoop < pstGnssAlmanaclist->ulGNSSAlmanacListCnt; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeGnssAlmanacListElement(pucDecodeBitStream, pulCurrentBitPos,
                                                    &(pstGnssAlmanaclist->astGNSSAlmanacListArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssAlmanac
Description     :����LPP_GNSS_ALMANAC_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-Almanac ::= SEQUENCE {
    weekNumber                  INTEGER (0..255)    OPTIONAL,   -- Need ON
    toa                         INTEGER (0..255)    OPTIONAL,   -- Need ON
    ioda                        INTEGER (0..3)      OPTIONAL,   -- Need ON
    completeAlmanacProvided     BOOLEAN,
    gnss-AlmanacList            GNSS-AlmanacList,


Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssAlmanac
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ALMANAC_STRU              *pstGnssAlmanac
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��ʶλ*/
    pstGnssAlmanac->bitOpGNSSAlmanacExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 1);

    /*����option*/
    pstGnssAlmanac->bitOpWeekNumber = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstGnssAlmanac->bitOpToa = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstGnssAlmanac->bitOpIoda = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����weekNumber*/
    if(NAS_LPP_SLCT == pstGnssAlmanac->bitOpWeekNumber)
    {
        pstGnssAlmanac->ucWeekNumber = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                               pulCurrentBitPos, 8);
    }

    /*����toa*/
    if(NAS_LPP_SLCT == pstGnssAlmanac->bitOpToa)
    {
        pstGnssAlmanac->ucToa = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                        pulCurrentBitPos, 8);
    }

    /*����ioa*/
    if(NAS_LPP_SLCT == pstGnssAlmanac->bitOpIoda)
    {
        pstGnssAlmanac->ucIoda = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                         pulCurrentBitPos, 2);
    }

    /*����AlmanacProvide*/
    pstGnssAlmanac->bCompleteAlmanacProvided = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);

    /*����AlmanacList*/
    ulRslt = NAS_LPP_DecodeGnssAlmanacList(pucDecodeBitStream, pulCurrentBitPos,
                                         (LPP_GNSS_ALMANAC_LIST_STRU*)&(pstGnssAlmanac->stGNSSAlmanacList));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssAlmanac->bitOpGNSSAlmanacExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSALMANAC_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos,
                               __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeUtcModel1
Description     :����LPP_UTC_MODEL_SET1_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
UTC-ModelSet1 ::= SEQUENCE {
    gnss-Utc-A1         INTEGER (-8388608..8388607),
    gnss-Utc-A0         INTEGER (-2147483648..2147483647),
    gnss-Utc-Tot        INTEGER (0..255),
    gnss-Utc-WNt        INTEGER (0..255),
    gnss-Utc-DeltaTls   INTEGER (-128..127),
    gnss-Utc-WNlsf      INTEGER (0..255),
    gnss-Utc-DN         INTEGER (-128..127),
    gnss-Utc-DeltaTlsf  INTEGER (-128..127),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeUtcModel1
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_UTC_MODEL_SET1_STRU            *pstUtcModelSet1
)
{
    VOS_UINT32                          ulRslt              = 0;
    VOS_INT64                           llTempValue         = 2147483648UL;

    /*������չ��ʶλ*/
    pstUtcModelSet1->bitOpUTCModelSet1Ext =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����utcA1*/
    pstUtcModelSet1->lGNSSUtcA1 =
        (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 24) - 8388608;

    /*����utcA0*/
    pstUtcModelSet1->lGNSSUtcA0 =
        (VOS_INT32)((VOS_INT64)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 32) - llTempValue);

    /*����tot*/
    pstUtcModelSet1->ucGNSSUtcTot =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

    /*����wnt*/
    pstUtcModelSet1->ucGNSSUtcWnt =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

    /*����deltatls*/
    pstUtcModelSet1->cGNSSUtcDeltaTls =
        (VOS_INT8)((VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8) - 128);

    /*����nlsf*/
    pstUtcModelSet1->ucGNSSUtcWnlsf =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

    /*����dn*/
    pstUtcModelSet1->cGNSSUtcDn =
        (VOS_INT8)((VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8) - 128);

    /*����deltatlf*/
    pstUtcModelSet1->cGNSSUtcDeltaTlsf =
        (VOS_INT8)((VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8) - 128);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT ==  pstUtcModelSet1->bitOpUTCModelSet1Ext)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_UTCMODEL1_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeUtcModel2
Description     :����LPP_UTC_MODEL_SET2_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
UTC-ModelSet2 ::= SEQUENCE {
    utcA0               INTEGER (-32768..32767),
    utcA1               INTEGER (-4096..4095),
    utcA2               INTEGER (-64..63),
    utcDeltaTls         INTEGER (-128..127),
    utcTot              INTEGER (0..65535),
    utcWNot             INTEGER (0..8191),
    utcWNlsf            INTEGER (0..255),
    utcDN               BIT STRING (SIZE(4)),
    utcDeltaTlsf        INTEGER (-128..127),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeUtcModel2
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_UTC_MODEL_SET2_STRU            *pstUtcModelSet2
)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��ʶλ*/
    pstUtcModelSet2->bitOpUTCModelSet2Ext =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����utcA1*/
    pstUtcModelSet2->sUtcA0 =
        (VOS_INT16)((VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16) - 32768);

    /*����utcA0*/
    pstUtcModelSet2->sUtcA1 =
        (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 13) - 4096;

    /*����tot*/
    pstUtcModelSet2->cUtcA2 =
        (VOS_INT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7) - 64;

    /*����wnt*/
    pstUtcModelSet2->cUtcDeltaTls =
        (VOS_INT8)((VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8) - 128);

    /*����deltatls*/
    pstUtcModelSet2->usUtcTot =
        (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16);

    /*����nlsf*/
    pstUtcModelSet2->usUtcWnot =
        (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 13);

    /*����dn*/
    pstUtcModelSet2->ucUtcWnlsf =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

    /*����deltatlf*/
    pstUtcModelSet2->ucUtcDn =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 4);

    /*����deltatlf*/
    pstUtcModelSet2->cUtcDeltaTlsf =
        (VOS_INT8)((VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8)- 128);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT ==  pstUtcModelSet2->bitOpUTCModelSet2Ext)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_UTCMODEL2_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeUtcModel3
Description     :����LPP_UTC_MODEL_SET3_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
UTC-ModelSet3 ::= SEQUENCE {
    nA                  INTEGER (1..1461),
    tauC                INTEGER (-2147483648..2147483647),
    b1                  INTEGER (-1024..1023)                   OPTIONAL,   -- Cond GLONASS-M
    b2                  INTEGER (-512..511)                     OPTIONAL,   -- Cond GLONASS-M
    kp                  BIT STRING (SIZE(2))                    OPTIONAL,   -- Cond GLONASS-M
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeUtcModel3
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_UTC_MODEL_SET3_STRU            *pstUtcModelSet3
)
{
    VOS_UINT32                          ulRslt              = 0;
    VOS_INT64                           llTempValue         = 2147483648UL;

    /*������չ��ʶλ*/
    pstUtcModelSet3->bitOpUTCModelSet3Ext = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                         pulCurrentBitPos, 1);

    /*����option*/
    pstUtcModelSet3->bitOpB1 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstUtcModelSet3->bitOpB2 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstUtcModelSet3->bitOpKp = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);


    /*����NA*/
    pstUtcModelSet3->ulNa = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 11) + 1;
    if(pstUtcModelSet3->ulNa > 1461)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_UTCMODEL3_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����tauC*/
    pstUtcModelSet3->lTauC =
        (VOS_INT32)((VOS_INT64)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 32) - llTempValue);

    /*����b1*/
    if(NAS_LPP_SLCT == pstUtcModelSet3->bitOpB1)
    {
        pstUtcModelSet3->sB1 =
            (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 11) - 1024;
    }

    /*����b2*/
    if(NAS_LPP_SLCT == pstUtcModelSet3->bitOpB2)
    {
        pstUtcModelSet3->sB2 = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 10) - 512;
    }

    /*����KP*/
    if(NAS_LPP_SLCT == pstUtcModelSet3->bitOpKp)
    {
        pstUtcModelSet3->ulKp = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                             pulCurrentBitPos, 2);
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstUtcModelSet3->bitOpUTCModelSet3Ext)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_UTCMODEL3_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeUtcModel4
Description     :����LPP_UTC_MODEL_SET4_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
UTC-ModelSet4 ::= SEQUENCE {
    utcA1wnt            INTEGER (-8388608..8388607),
    utcA0wnt            INTEGER (-2147483648..2147483647),
    utcTot              INTEGER (0..255),
    utcWNt              INTEGER (0..255),
    utcDeltaTls         INTEGER (-128..127),
    utcWNlsf            INTEGER (0..255),
    utcDN               INTEGER (-128..127),
    utcDeltaTlsf        INTEGER (-128..127),
    utcStandardID       INTEGER (0..7),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeUtcModel4
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_UTC_MODEL_SET4_STRU            *pstUtcModelSet4
)
{
    VOS_UINT32                          ulRslt              = 0;
    VOS_INT64                           llTempValue         = 2147483648UL;

    /*������չ��ʶλ*/
    pstUtcModelSet4->bitOpUTCModelSet4Ext =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����wnt1*/
    pstUtcModelSet4->lUtcA1wnt =
        (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 24) - 8388608;

    /*����wnt0*/
    pstUtcModelSet4->lUtcA0wnt =
        (VOS_INT32)((VOS_INT64)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 32) - llTempValue);

    /*����tot*/
    pstUtcModelSet4->ucUtcTot =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

    /*����wnt*/
    pstUtcModelSet4->ucUtcWnt =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

    /*����deltatls*/
    pstUtcModelSet4->cUtcDeltaTls =
        (VOS_INT8)((VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8) - 128);

    /*����wnlsf*/
    pstUtcModelSet4->ucUtcWnlsf =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

    /*����dn*/
    pstUtcModelSet4->cUtcDn =
        (VOS_INT8)((VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8) - 128);

    /*����deltatlsf*/
    pstUtcModelSet4->cUtcDeltaTlsf =
        (VOS_INT8)((VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8) - 128);

    /*����standardid*/
    pstUtcModelSet4->ucUtcStandardId =
        (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 3);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstUtcModelSet4->bitOpUTCModelSet4Ext)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_UTCMODEL4_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssUtcModel
Description     :����LPP_GNSS_UTC_MODEL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-UTC-Model ::= CHOICE {
    utcModel1           UTC-ModelSet1,  -- Model-1
    utcModel2           UTC-ModelSet2,  -- Model-2
    utcModel3           UTC-ModelSet3,  -- Model-3
    utcModel4           UTC-ModelSet4,  -- Model-4
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssUtcModel
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_UTC_MODEL_STRU            *pstGnssUtcModel
)
{
    VOS_UINT32                          ulRslt              = 0;

     /*�������չ��choic�����С�ķǸ�������������*/
     ulRslt = NAS_LPP_DecodeExtChoice(pucDecodeBitStream, pulCurrentBitPos, 2,
                                    &(pstGnssUtcModel->ulChoice));
     if(NAS_LPP_DECODE_SUCC != ulRslt)
     {
         return ulRslt;
     }
     if(LPP_DECODE_EXT_CHOICE_INVALID_VALUE == pstGnssUtcModel->ulChoice)
     {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSUTCMODEL_ERROR,
                                 NAS_LPP_CHOICE_EXT_OBJECT_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_CHOICE_ERROR;
     }

     switch(pstGnssUtcModel->ulChoice)
     {
         case LPP_UTC_MODEL1_CHOSEN:
             ulRslt = NAS_LPP_DecodeUtcModel1(pucDecodeBitStream, pulCurrentBitPos,
                                            &(pstGnssUtcModel->u.stUtcModel1));
             if(NAS_LPP_DECODE_SUCC != ulRslt)
             {
                 return ulRslt;
             }
             break;

         case LPP_UTC_MODEL2_CHOSEN:
             ulRslt = NAS_LPP_DecodeUtcModel2(pucDecodeBitStream, pulCurrentBitPos,
                                            &(pstGnssUtcModel->u.stUtcModel2));
             if(NAS_LPP_DECODE_SUCC != ulRslt)
             {
                 return ulRslt;
             }
             break;

         case LPP_UTC_MODEL3_CHOSEN:
             ulRslt = NAS_LPP_DecodeUtcModel3(pucDecodeBitStream, pulCurrentBitPos,
                                            &(pstGnssUtcModel->u.stUtcModel3));
             if(NAS_LPP_DECODE_SUCC != ulRslt)
             {
                 return ulRslt;
             }
             break;

         default:
             ulRslt = NAS_LPP_DecodeUtcModel4(pucDecodeBitStream, pulCurrentBitPos,
                                            &(pstGnssUtcModel->u.stUtcModel4));
             if(NAS_LPP_DECODE_SUCC != ulRslt)
             {
                 return ulRslt;
             }
             break;
     }

     return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssIdGpsElement
Description     :����LPP_GNSS_ID_GPS_SAT_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-ID-GPS-SatElement ::= SEQUENCE {
    svID                SV-ID,
    signalsAvailable    GNSS-SignalIDs,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssIdGpsElement
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ID_GPS_SAT_ELEMENT_STRU   *pstGnssIdGpsElement
)
{
    VOS_UINT32                          ulRslt              = 0;

    /*������չ��ʶλ*/
    pstGnssIdGpsElement->bitOpGNSSIDGPSSatElementExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����svid*/
    ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos,
                              &(pstGnssIdGpsElement->stSvId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����gnss-signalids*/
    ulRslt = NAS_LPP_DecodeGnssSignalIDS(pucDecodeBitStream, pulCurrentBitPos,
                                       &(pstGnssIdGpsElement->stSignalAvailable));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssIdGpsElement->bitOpGNSSIDGPSSatElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSIDGPSELEMENT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssIdGps
Description     :����LPP_GNSS_ID_GPS_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-ID-GPS ::= SEQUENCE    (SIZE(1..64)) OF GNSS-ID-GPS-SatElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssIdGps
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ID_GPS_STRU               *pstGnssIdGps
)
{
    VOS_UINT32                          ulRslt              = 0;
    VOS_UINT32                          ulGnssIdGpsNum      = 0;
    VOS_UINT32                          ulLoop              = 0;

    /*�������ֵ*/
    ulGnssIdGpsNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 6);
    ulGnssIdGpsNum += 1;
    pstGnssIdGps->ulGNSSIdGpsCnt = ulGnssIdGpsNum;
    if (LPP_MAX_GNSS_ID_GPS_SAT_ELEMENT_LEN < ulGnssIdGpsNum)
    {
        NAS_LPP_ASN_FAIL_Message( NAS_LPP_DECODE_GNSSIDGPS_ERROR,
                                  NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                 *pulCurrentBitPos,
                                  __LINE__,
                                  ulGnssIdGpsNum);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    for(ulLoop = 0; ulLoop < pstGnssIdGps->ulGNSSIdGpsCnt; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeGnssIdGpsElement(pucDecodeBitStream, pulCurrentBitPos,
                                              &(pstGnssIdGps->astGNSSIdGpsArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssIdGlonass
Description     :����LPP_GNSS_ID_GLONASS_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-ID-GLONASS-SatElement ::= SEQUENCE {
    svID                SV-ID,
    signalsAvailable    GNSS-SignalIDs,
    channelNumber       INTEGER (-7..13)        OPTIONAL,       -- Cond FDMA
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssIdGlonassElement
(
    VOS_UINT8                                              *pucDecodeBitStream,
    VOS_UINT32                                             *pulCurrentBitPos,
    LPP_GNSS_ID_GLONASS_SAT_ELEMENT_STRU                   *pstGnssGlonassElement
)
{
    VOS_UINT32                                              ulRslt          = 0;

    /*������չ��ʶλ*/
    pstGnssGlonassElement->bitOpGNSSIDGLONASSSatElementExt =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����option*/
    pstGnssGlonassElement->bitOpChannelNumber =
        NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����svid*/
    ulRslt = NAS_LPP_DecodeSvId(pucDecodeBitStream, pulCurrentBitPos, &(pstGnssGlonassElement->stSvId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����gnss-signalids*/
    ulRslt = NAS_LPP_DecodeGnssSignalIDS(pucDecodeBitStream, pulCurrentBitPos,
                                       &(pstGnssGlonassElement->stSignalsAvailable));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    if(NAS_LPP_SLCT == pstGnssGlonassElement->bitOpChannelNumber)
    {
        pstGnssGlonassElement->lChannelNumber =
            (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 5) - 7;
        if((pstGnssGlonassElement->lChannelNumber > 13)||(pstGnssGlonassElement->lChannelNumber < -7))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSIDGLONASSELEMENT_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pulCurrentBitPos, __LINE__, 0);
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGnssGlonassElement->bitOpGNSSIDGLONASSSatElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSIDGLONASSELEMENT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssIdGlonass
Description     :����LPP_GNSS_ID_GLONASS_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-ID-GLONASS ::= SEQUENCE (SIZE(1..64)) OF GNSS-ID-GLONASS-SatElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssIdGlonass
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_ID_GLONASS_STRU           *pstGnssGlonass
)
{
    VOS_UINT32                          ulRslt              = 0;
    VOS_UINT32                          ulGnssIdGlonassNum  = 0;
    VOS_UINT32                          ulLoop              = 0;

    /*�������ֵ*/
    ulGnssIdGlonassNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 6);
    ulGnssIdGlonassNum += 1;
    pstGnssGlonass->ulGNSSIdGlonassCnt = ulGnssIdGlonassNum;
    if (LPP_MAX_GNSS_ID_GLONASS_SAT_ELEMENT_LEN < ulGnssIdGlonassNum)
    {
        NAS_LPP_ASN_FAIL_Message( NAS_LPP_DECODE_GNSSIDGLONASS_ERROR,
                                  NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                 *pulCurrentBitPos,
                                  __LINE__,
                                  ulGnssIdGlonassNum);
        return NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    for(ulLoop = 0; ulLoop < pstGnssGlonass->ulGNSSIdGlonassCnt; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeGnssIdGlonassElement(pucDecodeBitStream, pulCurrentBitPos,
                                                  &(pstGnssGlonass->astGNSSIdGlonassArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssAuxiliaryInfo
Description     :����LPP_GNSS_AUX_INFO_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-AuxiliaryInformation ::= CHOICE {
    gnss-ID-GPS     GNSS-ID-GPS,
    gnss-ID-GLONASS GNSS-ID-GLONASS,
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssAuxiliaryInfo
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_AUX_INFO_STRU             *pstGnssAuxInfo
)
{
    VOS_UINT32                          ulRslt              = 0;

     /*�������չ��choic�����С�ķǸ�������������*/
     ulRslt = NAS_LPP_DecodeExtChoice(pucDecodeBitStream, pulCurrentBitPos, 1, &(pstGnssAuxInfo->ulChoice));
     if(NAS_LPP_DECODE_SUCC != ulRslt)
     {
         return ulRslt;
     }
     if(LPP_DECODE_EXT_CHOICE_INVALID_VALUE == pstGnssAuxInfo->ulChoice)
     {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSAUXILIARYINFO_ERROR,
                                 NAS_LPP_CHOICE_EXT_OBJECT_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_CHOICE_ERROR;
     }
     switch(pstGnssAuxInfo->ulChoice)
     {
         case LPP_GNSS_ID_GPS_CHOSEN:
             ulRslt = NAS_LPP_DecodeGnssIdGps(pucDecodeBitStream, pulCurrentBitPos,
                                            (LPP_GNSS_ID_GPS_STRU*)&(pstGnssAuxInfo->u.stGNSSIdGps));
             if(NAS_LPP_DECODE_SUCC != ulRslt)
             {
                 return ulRslt;
             }
             break;

         default:
             ulRslt = NAS_LPP_DecodeGnssIdGlonass(pucDecodeBitStream, pulCurrentBitPos,
                                                (LPP_GNSS_ID_GLONASS_STRU*)&(pstGnssAuxInfo->u.stGNSSIdGlonass));
             if(NAS_LPP_DECODE_SUCC != ulRslt)
             {
                 return ulRslt;
             }
             break;
     }

     return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGnssGenericAssitDataElement
Description     :����LPP_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-GenericAssistDataElement ::= SEQUENCE {
    gnss-ID                         GNSS-ID,
    sbas-ID                         SBAS-ID                         OPTIONAL, -- Cond GNSS-ID-SBAS
    gnss-TimeModels                 GNSS-TimeModelList              OPTIONAL,   -- Need ON
    gnss-DifferentialCorrections    GNSS-DifferentialCorrections    OPTIONAL,   -- Need ON
    gnss-NavigationModel            GNSS-NavigationModel            OPTIONAL,   -- Need ON
    gnss-RealTimeIntegrity          GNSS-RealTimeIntegrity          OPTIONAL,   -- Need ON
    gnss-DataBitAssistance          GNSS-DataBitAssistance          OPTIONAL,   -- Need ON
    gnss-AcquisitionAssistance      GNSS-AcquisitionAssistance      OPTIONAL,   -- Need ON
    gnss-Almanac                    GNSS-Almanac                    OPTIONAL,   -- Need ON
    gnss-UTC-Model                  GNSS-UTC-Model                  OPTIONAL,   -- Need ON
    gnss-AuxiliaryInformation       GNSS-AuxiliaryInformation       OPTIONAL,   -- Need ON
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGnssGenericAssitDataElement
(
    VOS_UINT8                                   *pucDecodeBitStream,
    VOS_UINT32                                  *pulCurrentBitPos,
    LPP_GNSS_GENERIC_ASSIST_DATA_ELEMENT_STRU   *pstGenericAssitDataElement)
{
    VOS_UINT32                                   ulRslt = 0;

    /*������չ��*/
    pstGenericAssitDataElement->bitOpGNSSGenericAssistDataElementExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����option��*/
    pstGenericAssitDataElement->bitOpSbasId = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);
    pstGenericAssitDataElement->bitOpGNSSTimeModelIs = NAS_LPP_GetDataFromBitStream(
                                                                            pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);
    pstGenericAssitDataElement->bitOpGNSSDiffCorrection = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 1);
    pstGenericAssitDataElement->bitOpGNSSNavigationModel = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 1);
    pstGenericAssitDataElement->bitOpGNSSRealTimeIntegrity = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                          pulCurrentBitPos, 1);
    pstGenericAssitDataElement->bitOpGNSSDataBitAssit = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 1);
    pstGenericAssitDataElement->bitOpGNSSAcqAssit = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstGenericAssitDataElement->bitOpGNSSAlmanac = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstGenericAssitDataElement->bitOpGNSSUtcModel = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstGenericAssitDataElement->bitOpGNSSAuxInfo = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);

    /*����GNSS-ID*/
    ulRslt = NAS_LPP_DecodeGnssId(pucDecodeBitStream, pulCurrentBitPos,
                                &(pstGenericAssitDataElement->stGNSSId));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����SBAS-ID*/
    if(NAS_LPP_SLCT == pstGenericAssitDataElement->bitOpSbasId)
    {
        ulRslt = NAS_LPP_DecodeSbasId(pucDecodeBitStream, pulCurrentBitPos,
                                    &(pstGenericAssitDataElement->stSbasId));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����timeModelReq*/
    if(NAS_LPP_SLCT == pstGenericAssitDataElement->bitOpGNSSTimeModelIs)
    {
        ulRslt = NAS_LPP_DecodeGnssTimeModel(pucDecodeBitStream, pulCurrentBitPos,
                                           &(pstGenericAssitDataElement->stGNSSTimeModels));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����diffCorrectionsReq*/
    if(NAS_LPP_SLCT == pstGenericAssitDataElement->bitOpGNSSDiffCorrection)
    {
        ulRslt = NAS_LPP_DecodeGnssdiffCorrection(pucDecodeBitStream, pulCurrentBitPos,
                                                &(pstGenericAssitDataElement->stGNSSDiffCorrect));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����NavigationModelReq*/
    if(NAS_LPP_SLCT == pstGenericAssitDataElement->bitOpGNSSNavigationModel)
    {
        ulRslt = NAS_LPP_DecodeGnssNavigationModel(pucDecodeBitStream, pulCurrentBitPos,
                                                 &(pstGenericAssitDataElement->stGNSSNavigationModel));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����GNSSRealTimeIntergrity*/
    if(NAS_LPP_SLCT == pstGenericAssitDataElement->bitOpGNSSRealTimeIntegrity)
    {
        ulRslt = NAS_LPP_DecodeGnssRealTimeIntegrity(pucDecodeBitStream, pulCurrentBitPos,
                                                   &(pstGenericAssitDataElement->stGNSSRealTimeIntergrity));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����databitAssitReq*/
    if(NAS_LPP_SLCT == pstGenericAssitDataElement->bitOpGNSSDataBitAssit)
    {
        ulRslt = NAS_LPP_DecodeDataBitsAssit(pucDecodeBitStream, pulCurrentBitPos,
                                           &(pstGenericAssitDataElement->stGNSSDataBitAssistance));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����AcquisuitonAssitReq*/
    if(NAS_LPP_SLCT == pstGenericAssitDataElement->bitOpGNSSAcqAssit)
    {
        ulRslt = NAS_LPP_DecodeGnssAcquisitionAssit(pucDecodeBitStream, pulCurrentBitPos,
                                                  &(pstGenericAssitDataElement->stGNSSAcquisitAssit));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����AlmanancReq*/
    if(NAS_LPP_SLCT == pstGenericAssitDataElement->bitOpGNSSAlmanac)
    {
        ulRslt = NAS_LPP_DecodeGnssAlmanac(pucDecodeBitStream, pulCurrentBitPos,
                                         &(pstGenericAssitDataElement->stGNSSAlmanac));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����UtcModelReq*/
    if(NAS_LPP_SLCT == pstGenericAssitDataElement->bitOpGNSSUtcModel)
    {
        ulRslt = NAS_LPP_DecodeGnssUtcModel(pucDecodeBitStream, pulCurrentBitPos,
                                          &(pstGenericAssitDataElement->stGNSSUtcModel));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����AuxiliaryInfo*/
    if(NAS_LPP_SLCT == pstGenericAssitDataElement->bitOpGNSSAuxInfo)
    {
        ulRslt = NAS_LPP_DecodeGnssAuxiliaryInfo(pucDecodeBitStream, pulCurrentBitPos,
                                               &(pstGenericAssitDataElement->stGNSSAuxInfo));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGenericAssitDataElement->bitOpGNSSGenericAssistDataElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSGENERICASSISTDATAELEMENT_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGNSSGenAssistData
Description     :����LPP_GNSS_GENERIC_ASSIST_DATA_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-GenericAssistData ::= SEQUENCE (SIZE (1..16)) OF GNSS-GenericAssistDataElement

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGNSSGenAssistData
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_GENERIC_ASSIST_DATA_STRU  *pstGNSSGenAssistData
)
{
    VOS_UINT32                          ulRslt                      = 0;
    VOS_UINT32                          ulGnssGenericAssitDataNum   = 0;
    VOS_UINT32                          ulLoop                      = 0;
    /*�������ֵ*/
    ulGnssGenericAssitDataNum = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 4);
    ulGnssGenericAssitDataNum += 1;
    if (LPP_MAX_GNSS_GENERIC_ASSIST_DATA_ELEMENT_LEN < ulGnssGenericAssitDataNum)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSGENASSISTDATA_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__, ulGnssGenericAssitDataNum);
        return  NAS_LPP_DECODE_FAIL;
    }
    pstGNSSGenAssistData->ulGNSSGenericAssitDataCnt = ulGnssGenericAssitDataNum;
    for(ulLoop = 0; ulLoop < pstGNSSGenAssistData->ulGNSSGenericAssitDataCnt ; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeGnssGenericAssitDataElement(pucDecodeBitStream,
                                                           pulCurrentBitPos,
                                                         &(pstGNSSGenAssistData->astGNSSGenericAssistDataArray[ulLoop]));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}
/*****************************************************************************
Function Name   :NAS_LPP_DecodeGNSSEarthParam
Description     :����LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-EarthOrientationParameters ::= SEQUENCE {
        teop                INTEGER (0..65535),
        pmX                 INTEGER (-1048576..1048575),
        pmXdot              INTEGER (-16384..16383),
        pmY                 INTEGER (-1048576..1048575),
        pmYdot              INTEGER (-16384..16383),
        deltaUT1            INTEGER (-1073741824..1073741823),
        deltaUT1dot         INTEGER (-262144..262143),
        ...
    }


Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGNSSEarthParam
(
    VOS_UINT8                                   *pucDecodeBitStream,
    VOS_UINT32                                  *pulCurrentBitPos,
    LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_STRU  *pstGNSSEarthParam
)
{
    VOS_UINT32      ulRslt = 0;
    VOS_INT32       lValue = 0;

    /*������չ��*/
    pstGNSSEarthParam->bitOpGNSSEarthOrientationParameterExt = NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);

    /*����teop*/
    pstGNSSEarthParam->ulTeop = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16);

    /*����pmx*/
    lValue = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 21);
    pstGNSSEarthParam->lPmx = lValue - 1048576;

    /*����pmXdot*/
    lValue = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 15);
    pstGNSSEarthParam->lPmXdot = lValue - 16384;

    /*����pmY*/
    lValue = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 21);
    pstGNSSEarthParam->lPmY = lValue - 1048576;

    /*����pmYdot*/
    lValue = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 15);
    pstGNSSEarthParam->lPmYdot = lValue - 16384;

    /*����deltaUt1*/
    lValue = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 31);
    pstGNSSEarthParam->lDeltaUt1= lValue - 1073741824;

    /*����deltaUt1Dot*/
    lValue = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 19);
    pstGNSSEarthParam->lDeltaUt1Dot = lValue - 262144;

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
     if(NAS_LPP_NO_SLCT == pstGNSSEarthParam->bitOpGNSSEarthOrientationParameterExt)
     {
         return  NAS_LPP_DECODE_SUCC;
     }

     ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
     if(NAS_LPP_DECODE_SUCC != ulRslt)
     {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSEARTHPARAM_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
         return ulRslt;
     }

     return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeKlobucharModel
Description     :����LPP_GNSS_IONOSPHERIC_MODEL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
KlobucharModelParameter ::= SEQUENCE {
    dataID          BIT STRING (SIZE (2)),
    alfa0           INTEGER (-128..127),
    alfa1           INTEGER (-128..127),
    alfa2           INTEGER (-128..127),
    alfa3           INTEGER (-128..127),
    beta0           INTEGER (-128..127),
    beta1           INTEGER (-128..127),
    beta2           INTEGER (-128..127),
    beta3           INTEGER (-128..127),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeKlobucharModel
(
    VOS_UINT8                              *pucDecodeBitStream,
    VOS_UINT32                             *pulCurrentBitPos,
    LPP_KLOBUCHAR_MODEL_PARAMTER_STRU      *pstKlobucharModel
)
{
    VOS_UINT32                              ulRslt = 0;
    VOS_INT16                               cValue = 0;

    /*������չ��*/
    pstKlobucharModel->bitOpKlobucharModelParamterExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                     pulCurrentBitPos, 1);

    /*����dataId*/
    pstKlobucharModel->ucDataId = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                            pulCurrentBitPos, 2);

    /*����alfa0*/
    cValue = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
    pstKlobucharModel->cAlfa0 = (VOS_INT8)(cValue - 128);

    /*����alfa1*/
    cValue = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
    pstKlobucharModel->cAlfa1 = (VOS_INT8)(cValue - 128);

    /*����alfa2*/
    cValue = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
    pstKlobucharModel->cAlfa2 = (VOS_INT8)(cValue - 128);

    /*����alfa3*/
    cValue = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
    pstKlobucharModel->cAlfa3 = (VOS_INT8)(cValue - 128);

    /*����beta0*/
    cValue = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
    pstKlobucharModel->cbeta0 = (VOS_INT8)(cValue - 128);

    /*����beta1*/
    cValue = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
    pstKlobucharModel->cbeta1 = (VOS_INT8)(cValue - 128);

    /*����beta1*/
    cValue = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
    pstKlobucharModel->cbeta2 = (VOS_INT8)(cValue - 128);

    /*����beta1*/
    cValue = (VOS_INT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);
    pstKlobucharModel->cbeta3 = (VOS_INT8)(cValue - 128);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
     if(NAS_LPP_NO_SLCT == pstKlobucharModel->bitOpKlobucharModelParamterExt)
     {
         return  NAS_LPP_DECODE_SUCC;
     }

     ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
     if(NAS_LPP_DECODE_SUCC != ulRslt)
     {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_KLOBUCHARMODEL_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos, __LINE__,0);
         return ulRslt;
     }

     return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeNeQuickModel
Description     :����LPP_NEQUICK_MODEL_PARAMETER_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
NeQuickModelParameter ::= SEQUENCE {
    ai0             INTEGER (0..4095),
    ai1             INTEGER (0..4095),
    ai2             INTEGER (0..4095),
    ionoStormFlag1  INTEGER (0..1)      OPTIONAL,   -- Need OP
    ionoStormFlag2  INTEGER (0..1)      OPTIONAL,   -- Need OP
    ionoStormFlag3  INTEGER (0..1)      OPTIONAL,   -- Need OP
    ionoStormFlag4  INTEGER (0..1)      OPTIONAL,   -- Need OP
    ionoStormFlag5  INTEGER (0..1)      OPTIONAL,   -- Need OP
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeNeQuickModel
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_NEQUICK_MODEL_PARAMETER_STRU        *pstNeQuickMOdel
)
{
    VOS_UINT32                               ulRslt = 0;

    /*������չ��*/
    pstNeQuickMOdel->bitOpNequickModelParameterExt = NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 1);

    /*�����ѡ��*/
    pstNeQuickMOdel->bitOpIonoStormFlag1 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                        pulCurrentBitPos, 1);
    pstNeQuickMOdel->bitOpIonoStormFlag2 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                        pulCurrentBitPos, 1);
    pstNeQuickMOdel->bitOpIonoStormFlag3 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                        pulCurrentBitPos, 1);
    pstNeQuickMOdel->bitOpIonoStormFlag4 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                        pulCurrentBitPos, 1);
    pstNeQuickMOdel->bitOpIonoStormFlag5 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                        pulCurrentBitPos, 1);

    /*����ai0*/
    pstNeQuickMOdel->usAi0 = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                        pulCurrentBitPos, 12);

    /*����ai1*/
    pstNeQuickMOdel->usAi1 = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                        pulCurrentBitPos, 12);

    /*����ai2*/
    pstNeQuickMOdel->usAi2 = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                        pulCurrentBitPos, 12);

    /*����InoStormFlag1*/
    if(NAS_LPP_SLCT == pstNeQuickMOdel->bitOpIonoStormFlag1)
    {
        pstNeQuickMOdel->ucInoStormFlag1 = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    }

    /*����InoStormFlag2*/
    if(NAS_LPP_SLCT == pstNeQuickMOdel->bitOpIonoStormFlag2)
    {
        pstNeQuickMOdel->ucInoStormFlag2 = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    }

    /*����InoStormFlag3*/
    if(NAS_LPP_SLCT == pstNeQuickMOdel->bitOpIonoStormFlag3)
    {
        pstNeQuickMOdel->ucInoStormFlag3 = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    }

    /*����InoStormFlag4*/
    if(NAS_LPP_SLCT == pstNeQuickMOdel->bitOpIonoStormFlag4)
    {
        pstNeQuickMOdel->ucInoStormFlag4 = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    }

    /*����InoStormFlag5*/
    if(NAS_LPP_SLCT == pstNeQuickMOdel->bitOpIonoStormFlag5)
    {
        pstNeQuickMOdel->ucInoStormFlag5 = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstNeQuickMOdel->bitOpNequickModelParameterExt)
    {
     return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_NEQUICKMODEL_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return      ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}


/*****************************************************************************
Function Name   :NAS_LPP_DecodeGNSSIonoModel
Description     :����LPP_GNSS_IONOSPHERIC_MODEL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-IonosphericModel ::= SEQUENCE {
        klobucharModel          KlobucharModelParameter     OPTIONAL,   -- Need ON
        neQuickModel            NeQuickModelParameter       OPTIONAL,   -- Need ON
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGNSSIonoModel
(
    VOS_UINT8                           *pucDecodeBitStream,
    VOS_UINT32                          *pulCurrentBitPos,
    LPP_GNSS_IONOSPHERIC_MODEL_STRU     *pstGNSSIonoModel)
{
    VOS_UINT32                           ulRslt = 0;

    /*������չ��*/
    pstGNSSIonoModel->bitOpGNSSIonosphericModelExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                  pulCurrentBitPos, 1);

    /*�����ѡ��*/
    pstGNSSIonoModel->bitOpklobucharModel = NAS_LPP_GetDataFromBitStream(   pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);
    pstGNSSIonoModel->bitOpneQuickModel = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                        pulCurrentBitPos, 1);

    /*����klobucharModel*/
    if(NAS_LPP_SLCT == pstGNSSIonoModel->bitOpklobucharModel)
    {
        ulRslt = NAS_LPP_DecodeKlobucharModel(pucDecodeBitStream, pulCurrentBitPos,
                                            &(pstGNSSIonoModel->stKlobucharModel));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����neQuickModel*/
    if(NAS_LPP_SLCT == pstGNSSIonoModel->bitOpneQuickModel)
    {
        ulRslt = NAS_LPP_DecodeNeQuickModel(pucDecodeBitStream, pulCurrentBitPos,
                                          &(pstGNSSIonoModel->stNeQuickModel));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return      ulRslt;
        }
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGNSSIonoModel->bitOpGNSSIonosphericModelExt)
    {
     return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSIONOMODEL_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return      ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEllipsoidPointWithAltiAndUncertEllipsoid
Description     :����pstEllipAltitude
Input           : ��Ϣ������
Output          : None
ASN             :
EllipsoidPointWithAltitudeAndUncertaintyEllipsoid ::= SEQUENCE {
    latitudeSign                ENUMERATED {north, south},
    degreesLatitude             INTEGER (0..8388607),           -- 23 bit field
    degreesLongitude            INTEGER (-8388608..8388607),    -- 24 bit field
    altitudeDirection           ENUMERATED {height, depth},
    altitude                    INTEGER (0..32767),             -- 15 bit field
    uncertaintySemiMajor        INTEGER (0..127),
    uncertaintySemiMinor        INTEGER (0..127),
    orientationMajorAxis        INTEGER (0..179),
    uncertaintyAltitude         INTEGER (0..127),
    confidence                  INTEGER (0..100)
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEllipsoidPointWithAltiAndUncertEllipsoid
(
    VOS_UINT8                                                  *pucDecodeBitStream,
    VOS_UINT32                                                 *pulCurrentBitPos,
    LPP_ELLIP_POINT_WITH_ALTITUDE_UNCERTAIN_ELLIPSOID_STRU     *pstEllipAltitude)
{
    VOS_INT32                                                   lDegreeeLongitude = 0;

    /*����latitudeSgn*/
    pstEllipAltitude->enLatitudeSign = (VOS_UINT8)NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);

    /*����degreeLatitude*/
    pstEllipAltitude->ulDegreeLatitude = NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                        pulCurrentBitPos, 23);


    /*����degreeLongitude*/
    lDegreeeLongitude = (VOS_INT32)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                pulCurrentBitPos, 24);
    pstEllipAltitude->lDegreeeLongitude = lDegreeeLongitude - 8388608;

    /*����degreeLongitude*/
    pstEllipAltitude->enAltitudeDirection = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                    pulCurrentBitPos, 1);

    /*����altitude*/
    pstEllipAltitude->usAltitude = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                            pulCurrentBitPos, 15);

    /*����uncertaintySemiMajor*/
    pstEllipAltitude->ucUncertaintySemiMajor =  (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 7);

    /*����uncertaintysemiMinor*/
    pstEllipAltitude->ucUncertaintySemiMinor = (VOS_UINT8)NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 7);

    /*����orientationMajorAxis*/
    pstEllipAltitude->ucOrientationMajorAxis = (VOS_UINT8)NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 8);
    if(pstEllipAltitude->ucOrientationMajorAxis > 179)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_ELLIPSOIDPOINTWITHALTIANDUNCERTELLIPSOID_ERROR,
                                    NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pulCurrentBitPos,
                                  __LINE__, pstEllipAltitude->ucOrientationMajorAxis);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����unCertaintyAltitude*/
    pstEllipAltitude->ucUncertaintyAltitude = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream, pulCurrentBitPos, 7);

    /*����confidence*/
    pstEllipAltitude->ucConfidence = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                            pulCurrentBitPos, 7);

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGNSSRefLocation
Description     :����LPP_GNSS_REFERENCE_LOCATION_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-ReferenceLocation ::= SEQUENCE {
            threeDlocation          EllipsoidPointWithAltitudeAndUncertaintyEllipsoid,
            ...
    }


Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGNSSRefLocation
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_REFERENCE_LOCATION_STRU   *pGNSSRefLocation)
{
    VOS_UINT32                          ulRslt = 0;

    /*������չ��*/
    pGNSSRefLocation->bitOpNGSSReferenceLocationExt = NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);

    /*����EllipsoidPointWithAltitudeAndUncertaintyEllipsoid*/
    ulRslt = NAS_LPP_DecodeEllipsoidPointWithAltiAndUncertEllipsoid(pucDecodeBitStream,
                                                                    pulCurrentBitPos,
                                                                  &(pGNSSRefLocation->stThreeDlocation));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pGNSSRefLocation->bitOpNGSSReferenceLocationExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_GNSSREFLOCATION_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeArfcnEutranV9a0
Description     :����pstEutra
Input           : ��Ϣ������
Output          : None
ASN             :
ARFCN-ValueEUTRA-v9a0 ::=INTEGER (maxEARFCN-Plus1..maxEARFCN2)
maxEARFCN-Plus1 INTEGER ::= 65536   -- Lowest value extended EARFCN range
maxEARFCN2 INTEGER ::= 262143   -- Highest value extended EARFCN range

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeArfcnEutranV9a0(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_ARFCN_VALUE_EUTRA_V9A0_STRU         *pstArfcnValueV9a0)
{
    VOS_UINT32      ulExtEarfcnLen = 0;
    VOS_UINT32      ulExtEarfcnV9a0 = 0;
    VOS_UINT32      ulArfcnEutraV9A0Op = 0;

    /*������չ���L+V*/
    ulExtEarfcnLen = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

    /*��ȡOPTIONAL���־λ*/
    ulArfcnEutraV9A0Op = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,  pulCurrentBitPos, 1);
    if(NAS_LPP_NO_SLCT == ulArfcnEutraV9A0Op)
    {
        *pulCurrentBitPos += (ulExtEarfcnLen * 8 - 1);
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ARFCNEUTRANV9A0_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_BODY_ERROR_HAVE_EXT_IE_BUT_DONOT_TAKE;
    }
    pstArfcnValueV9a0->bitOpARFCNValueEutraV9A0 = ulArfcnEutraV9A0Op;
    if(ulExtEarfcnLen != 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ARFCNEUTRANV9A0_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                 *pulCurrentBitPos, __LINE__, 0);
        return NAS_LPP_DECODE_MSG_BODY_ERROR_OPTION_IE_LV_VALUE_MISMATCH;
    }

    /*����V*/
    ulExtEarfcnV9a0 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 18);
    pstArfcnValueV9a0->ulArfcnValueEUTRAv9a0 = ulExtEarfcnV9a0 + 65536;

    /*��������Ĳ���, ����3���ֽ��ܹ�ռ����19��bit�����Ի���Ҫ��������5��bit*/
    *pulCurrentBitPos += 5;

    return NAS_LPP_DECODE_SUCC;
}


/*****************************************************************************
Function Name   :NAS_LPP_DecodeEutra
Description     :��������Э��汾�ȱ���Э��汾�ߵĲ���
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeExtIeWithPartValid(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        VOS_UINT32                              ulInvalidExtIeLen)
{
    VOS_UINT32  ulLoop = 0;
    VOS_UINT32  ulLAndVvalue = 0;

    for(ulLoop = 0; ulLoop < ulInvalidExtIeLen; ulLoop++)
    {
        ulLAndVvalue = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
        /*�������128�ֽڣ���Ҫ���������Ƚ������⴦��*/
        if(ulLAndVvalue == 1)
        {
            /*���1����һλ��0�����������������ȣ������1������֧�ַ�Χ�ڣ��϶��ǽ������*/
            ulLAndVvalue = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
            if(ulLAndVvalue == 1)
            {
                return  NAS_LPP_DECODE_MSG_VALUE_ERROR_EXT_IE_LEN_ERROR;
            }
            else
            {
                ulLAndVvalue = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                             pulCurrentBitPos, 14);
                *pulCurrentBitPos += ulLAndVvalue * 8;
            }
        }
        else
        {
            ulLAndVvalue = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                         pulCurrentBitPos, 7);
            *pulCurrentBitPos += ulLAndVvalue * 8;
        }
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodePlmnIdentity
Description     :����pstPlmnInetity
Input           : ��Ϣ������
Output          : None
ASN             :
plmn-Identity       SEQUENCE {
                        mcc     SEQUENCE (SIZE (3))     OF INTEGER (0..9),
                        mnc     SEQUENCE (SIZE (2..3))  OF INTEGER (0..9)
                    },

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodePlmnIdentity
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_PLMN_IDENTITY_STRU                  *pstPlmnInetity
)
{
    VOS_UINT32      ulLoop = 0;
    VOS_UINT32      ulMncLen = 0;

    /*����mcc*/
    for(ulLoop = 0; ulLoop < 3; ulLoop++)
    {
        pstPlmnInetity->aucMcc[ulLoop] = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 4);
        if(pstPlmnInetity->aucMcc[ulLoop] > 9)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_PLMNIDENTITY_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pulCurrentBitPos, __LINE__, pstPlmnInetity->aucMcc[ulLoop]);
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
    }

    /*����mnc*/
    /*����mnc�ĳ���*/
    ulMncLen = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstPlmnInetity->ucMncNum = (VOS_UINT8)(ulMncLen + 2);

    /*����mnc��ʵ��ֵ��*/
    for(ulLoop = 0; ulLoop < pstPlmnInetity->ucMncNum; ulLoop++)
    {
        pstPlmnInetity->aucMnc[ulLoop] = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 4);
        if(pstPlmnInetity->aucMnc[ulLoop] > 9)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_PLMNIDENTITY_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                     *pulCurrentBitPos, __LINE__, pstPlmnInetity->aucMnc[ulLoop]);
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCellIdentity
Description     :����pstCellIndentity
Input           : ��Ϣ������
Output          : None
ASN             :
cellIdentity        CHOICE {
    eutra   BIT STRING (SIZE (28)),
    utra    BIT STRING (SIZE (32))
},

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCellIdentity
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_CELL_IDENTITY_STRU                  *pstCellIndentity
)
{
    /*����choice��*/
    pstCellIndentity->ulChoice = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                             pulCurrentBitPos, 1);

    /*�������ֵ��*/
    switch(pstCellIndentity->ulChoice)
    {
        case LPP_EUTRA_CHOSEN:
            pstCellIndentity->u.ulEutra = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                      pulCurrentBitPos, 28);
            break;

        default:
            pstCellIndentity->u.ulUtra = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                      pulCurrentBitPos, 32);
            break;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCellEutranAndUtra
Description     :����pstCellGloEutra
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCellEutranAndUtra
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_CELL_GLO_EUTRA_UTRA_STRU            *pstCellGloEutra
)
{
    VOS_UINT32      ulRslt = 0;
    VOS_UINT32      ulExtIe = 0;

    /*������չ��ʶλ*/
    ulExtIe = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstCellGloEutra->bitOpCellGloEUTRAUTRAExt = ulExtIe;

    /*����plmn-identity*/
    ulRslt = NAS_LPP_DecodePlmnIdentity(pucDecodeBitStream, pulCurrentBitPos,
                                        &(pstCellGloEutra->stPlmnIdentity));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����CellIdentity*/
    ulRslt = NAS_LPP_DecodeCellIdentity(pucDecodeBitStream, pulCurrentBitPos,
                                        &(pstCellGloEutra->stCellIdentity));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstCellGloEutra->bitOpCellGloEUTRAUTRAExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_CELLEUTRANANDUTRA_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeARFCNValueEutra
Description     :����pstCellGloEutra
Input           : ��Ϣ������
Output          : None
ASN             :
ARFCN-ValueEUTRA ::= INTEGER (0..maxEARFCN)
maxEARFCN   INTEGER ::= 65535   -- Maximum value of EUTRA carrier frequency

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeARFCNValueEutra
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_ARFCN_VALUE_EUTRA_STRU              *pstArcnValueEutra
)
{
    /*����ArfcnValueEutra*/
    pstArcnValueEutra->ulArfcnValueEUTRA = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                        pulCurrentBitPos, 16);

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeEutra
Description     :����pstEutra
Input           : ��Ϣ������
Output          : None
ASN             :
eUTRA       SEQUENCE {
            physCellId          INTEGER (0..503),
            cellGlobalIdEUTRA   CellGlobalIdEUTRA-AndUTRA   OPTIONAL,   -- Need ON
            earfcn              ARFCN-ValueEUTRA,
            ...,
            [[ earfcn-v9a0      ARFCN-ValueEUTRA-v9a0 OPTIONAL  -- Cond EARFCN-max
            ]]  FIXME LIFUXIN
            },

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeEutra
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_EUTRA_STRU                          *pstEutra
)
{
    VOS_UINT32      ulRslt                  = 0;
    VOS_UINT32      ulExtIe                 = 0;
    VOS_UINT32      ulOptionCellGloEutra    = 0;
    VOS_UINT32      ulExtIeNum              = 0;
    VOS_UINT16      usPhysCellId            = 0;
    VOS_UINT32      ulLoop                  = 0;
    VOS_UINT32      ulExtIeOptionEarfcnV9a0 = 0;
    VOS_UINT32      ulExtIeInValidNum       = 0;
    VOS_UINT32      ulExtIeInvalidOption    = 0;

    /*������չ��ʶλ*/
    ulExtIe = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstEutra->bitOpEutraExt = ulExtIe;

    /*�����ѡ��*/
    ulOptionCellGloEutra = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                        pulCurrentBitPos, 1);
    pstEutra->bitOpCellGEutraAndUtra = ulOptionCellGloEutra;

    /*����physCellId*/
    usPhysCellId = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                            pulCurrentBitPos, 9);
    if(usPhysCellId > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_EUTRA_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__, 0);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    pstEutra->usPhysCellId = usPhysCellId;

    /*����cellGlobalIdEUTRA*/
    if(NAS_LPP_SLCT == pstEutra->bitOpCellGEutraAndUtra)
    {
        ulRslt = NAS_LPP_DecodeCellEutranAndUtra(pucDecodeBitStream, pulCurrentBitPos,
                                                 &(pstEutra->stCellGlobalIdEUTRA));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����earfcn*/
    ulRslt = NAS_LPP_DecodeARFCNValueEutra(pucDecodeBitStream, pulCurrentBitPos,
                                            &(pstEutra->stEarfcn));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*û��ѡ����չ��*/
    if(NAS_LPP_NO_SLCT == pstEutra->bitOpEutraExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*ѡ����չ��*/
    /*������չ��ļ���L-1*/
    ulRslt = NAS_LPP_DecodeNormalSmallInt(pucDecodeBitStream, pulCurrentBitPos,
                                          &ulExtIeNum);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    /*�����������չ��ļ�����1����ʾ�����������İ汾����չ��ļ���*/
    ulExtIeNum += 1;

    /*�����Э��汾һ����չ���option*/
    ulExtIeOptionEarfcnV9a0 = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                           pulCurrentBitPos, 1);
    pstEutra->bitOpArfcnEutraV9a0 = ulExtIeOptionEarfcnV9a0;

    /*�����Э��汾��һ����չ���option*/
    for(ulLoop = 0; ulLoop < ulExtIeNum - 1; ulLoop++)
    {
        ulExtIeInvalidOption = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
        if(NAS_LPP_SLCT == ulExtIeInvalidOption)
        {
            ulExtIeInValidNum++;
        }
    }

    /*������չ��ľ����ֵ*/
    /*����Э��汾һ�µ���Ԫ*/
    if(NAS_LPP_SLCT == pstEutra->bitOpArfcnEutraV9a0)
    {
        ulRslt = NAS_LPP_DecodeArfcnEutranV9a0(pucDecodeBitStream, pulCurrentBitPos, &(pstEutra->stEarfcnV9a0));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*�����ǰ��չ��ļ�����UE�汾����չ��ļ�����ȣ���˵��Э��汾һ�£��������*/
    if(1 == ulExtIeNum)
    {
        return NAS_LPP_DECODE_SUCC;
    }
    else
    {
        /*Э��汾�ȱ��ظߣ�����Ҫ����ѭ������ʣ�µ�IE��*/
        ulRslt = NAS_LPP_DecodeExtIeWithPartValid(pucDecodeBitStream, pulCurrentBitPos,
                                                  ulExtIeInValidNum);
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_EUTRA_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                    *pulCurrentBitPos, __LINE__,0);
            return ulRslt;
        }

        return NAS_LPP_DECODE_SUCC;
    }

}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeFdd
Description     :����pstFdd
Input           : ��Ϣ������
Output          : None
ASN             :

fdd         SEQUENCE {
                                                    primary-CPICH-Info  INTEGER (0..511),
                                                    ...
                                                  },

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeFdd(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_FDD_STRU                            *pstFdd)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��*/
    pstFdd->bitOpFddExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����Primary-cpich*/
    pstFdd->ulPrimaryCpichInfo = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 9);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstFdd->bitOpFddExt )
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_FDD_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeTdd
Description     :����pstTdd
Input           : ��Ϣ������
Output          : None
ASN             :
tdd         SEQUENCE {
                                                    cellParameters      INTEGER (0..127),
                                                    ...
                                                    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeTdd(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_TDD_STRU                            *pstTdd)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��*/
    pstTdd->bitOpTddExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����Primary-cpich*/
    pstTdd->ulCellParameters = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstTdd->bitOpTddExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_TDD_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeMode
Description     :����pstMode
Input           : ��Ϣ������
Output          : None
ASN             :
mode    CHOICE {
                fdd     SEQUENCE {
                        primary-CPICH-Info  INTEGER (0..511),
                        ...
                        },
                tdd     SEQUENCE {
                        cellParameters      INTEGER (0..127),
                        ...
                        }
                },

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeMode(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_MODE_SELECT_STRU                    *pstMode)
{
    VOS_UINT32  ulRslt = NAS_LPP_DECODE_SUCC;

    /*����choice��*/
    pstMode->ulChoice = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    switch(pstMode->ulChoice)
    {
        case LPP_FDD_CHOSEN:
            ulRslt = NAS_LPP_DecodeFdd(pucDecodeBitStream, pulCurrentBitPos, &(pstMode->u.stFdd));
            break;

        default:
            ulRslt = NAS_LPP_DecodeTdd(pucDecodeBitStream, pulCurrentBitPos, &(pstMode->u.stTdd));
            break;
    }

    return ulRslt;
}
/*****************************************************************************
Function Name   :NAS_LPP_DecodeARFCNValueUtra
Description     :����pstCellGloEutra
Input           : ��Ϣ������
Output          : None
ASN             :
ARFCN-ValueUTRA ::= INTEGER(0..16383)

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeARFCNValueUtra(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_ARFCN_VALUE_UTRA_STRU               *pstArcnValueUtra)
{
    /*����ArfcnValueEutra*/
    pstArcnValueUtra->ulArfcnValueUTRA = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 14);

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeUtra
Description     :����pstUtra
Input           : ��Ϣ������
Output          : None
ASN             :
uTRA        SEQUENCE {
mode    CHOICE {
                fdd     SEQUENCE {
                        primary-CPICH-Info  INTEGER (0..511),
                        ...
                        },
                tdd     SEQUENCE {
                        cellParameters      INTEGER (0..127),
                        ...
                        }
                },
cellGlobalIdUTRA    CellGlobalIdEUTRA-AndUTRA   OPTIONAL,   -- Need ON
uarfcn              ARFCN-ValueUTRA,
...

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/

VOS_UINT32  NAS_LPP_DecodeUtra(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_UTRA_STRU                           *pstUtra)
{
    VOS_UINT32  ulRslt = 0;


    /*������չ���־λ*/
    pstUtra->bitOpUtraExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*�����ѡ���־λ*/
    pstUtra->bitOpCellGloEutraAndUtra = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����mode*/
    ulRslt = NAS_LPP_DecodeMode(pucDecodeBitStream, pulCurrentBitPos, &(pstUtra->stMode));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����cellGlobalIdEUTRA*/
    if(NAS_LPP_SLCT == pstUtra->bitOpCellGloEutraAndUtra)
    {
        ulRslt = NAS_LPP_DecodeCellEutranAndUtra(pucDecodeBitStream, pulCurrentBitPos, &(pstUtra->stCellGlobalIdUTRA));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*����uarfcn*/
    ulRslt = NAS_LPP_DecodeARFCNValueUtra(pucDecodeBitStream, pulCurrentBitPos, &(pstUtra->stUarfcn));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstUtra->bitOpUtraExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_UTRA_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos, __LINE__,0);
        return  ulRslt;
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeCellGlobalGeran
Description     :����pstCellGloGeran
Input           : ��Ϣ������
Output          : None
ASN             :
CellGlobalIdGERAN ::= SEQUENCE {
    plmn-Identity       SEQUENCE {
                            mcc     SEQUENCE (SIZE (3))     OF INTEGER (0..9),
                            mnc     SEQUENCE (SIZE (2..3))  OF INTEGER (0..9)
                            },
    locationAreaCode        BIT STRING (SIZE (16)),
    cellIdentity            BIT STRING (SIZE (16)),
    ...
}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCellGlobalGeran(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_CELL_GLO_ID_GERAN_STRU              *pstCellGloGeran)
{
    VOS_UINT32  ulRslt = 0;

    /*������չλ*/
    pstCellGloGeran->bitOpCellGLOBALIdGERANExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����plmn-identity*/
    ulRslt = NAS_LPP_DecodePlmnIdentity(pucDecodeBitStream, pulCurrentBitPos, &(pstCellGloGeran->stPlmnIdentity));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����locationAreaCode*/
    pstCellGloGeran->usLocationAreaCode = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16);

    /*����CellIdentity*/
    pstCellGloGeran->usCellIdentity = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 16);

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstCellGloGeran->bitOpCellGLOBALIdGERANExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_CELLGLOBALGERAN_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGsm
Description     :����pstUtra
Input           : ��Ϣ������
Output          : None
ASN             :
 gSM         SEQUENCE {
         bcchCarrier         INTEGER (0..1023),
         bsic                INTEGER (0..63),
         cellGlobalIdGERAN   CellGlobalIdGERAN           OPTIONAL,   -- Need ON
         ...
         },
...

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGsm(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_GSM_STRU                            *pstGsm)
{
    VOS_UINT32  ulRslt = 0;

    /*������չ��*/
    pstGsm->bitOpGsmExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*������չλ*/
    pstGsm->bitOpCellGlobalIdGeran = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*����bcchCarrier*/
    pstGsm->usBcchCarrier = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 10);

    /*����basic*/
    pstGsm->usBsis = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 6);

    if(NAS_LPP_SLCT == pstGsm->bitOpCellGlobalIdGeran)
    {
        ulRslt = NAS_LPP_DecodeCellGlobalGeran(pucDecodeBitStream, pulCurrentBitPos, &(pstGsm->stCellGlobalIdGeran));
        if(NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGsm->bitOpGsmExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GSM_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}


/*****************************************************************************
Function Name   :NAS_LPP_DecodeCellId
Description     :����pCellId
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeCellId(
                        VOS_UINT8                               *pucDecodeBitStream,
                        VOS_UINT32                              *pulCurrentBitPos,
                        LPP_CELL_ID_STRU                        *pstCellId)
{
    VOS_UINT32          ulRslt = 0;

    /*�������չ��choic�����С�ķǸ�������������*/
    ulRslt = NAS_LPP_DecodeExtChoice(pucDecodeBitStream, pulCurrentBitPos, 2, &(pstCellId->ulChoice));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }
    if(LPP_DECODE_EXT_CHOICE_INVALID_VALUE == pstCellId->ulChoice)
    {
    NAS_LPP_ASN_FAIL_Message(NAS_LPP_CELLID_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE, *pulCurrentBitPos, __LINE__, 0);
    return  NAS_LPP_DECODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }

    switch(pstCellId->ulChoice)
    {
        case LPP_CELL_ID_EUTRA_CHOSEN:
            ulRslt = NAS_LPP_DecodeEutra(pucDecodeBitStream, pulCurrentBitPos, &(pstCellId->u.stEUtra));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_CELL_ID_UTRA_CHOSEN:
            ulRslt = NAS_LPP_DecodeUtra(pucDecodeBitStream, pulCurrentBitPos, &(pstCellId->u.stUtra));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        case LPP_CELL_ID_GSM_CHOSEN:
            ulRslt = NAS_LPP_DecodeGsm(pucDecodeBitStream, pulCurrentBitPos, &(pstCellId->u.stGsm));
            if(NAS_LPP_DECODE_SUCC != ulRslt)
            {
                return ulRslt;
            }
            break;

        default:
            return NAS_LPP_DECODE_SUCC;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeNetTime
Description     :����pNetWorkTime
Input           : ��Ϣ������
Output          : None
ASN             :
NetworkTime ::= SEQUENCE {
    secondsFromFrameStructureStart              INTEGER(0..12533),
    fractionalSecondsFromFrameStructureStart    INTEGER(0..3999999),
    frameDrift                                  INTEGER (-64..63)   OPTIONAL,   -- Cond GNSSsynch
    cellid .......

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeNetTime
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_NET_WORK_TIME_STRU             *pstNetWorkTime)
{
    VOS_UINT32                          ulRslt                                      = 0;
    VOS_UINT32                          ulOptionFrameDrift                          = 0;
    VOS_UINT32                          ulSecondsFromFrameStructureStart            = 0;
    VOS_UINT32                          ulFractionalSecondsFromFrameStructureStart  = 0;

    /*������չ��ʶλ*/
    pstNetWorkTime->bitOpNetworkTimeExt = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                        pulCurrentBitPos, 1);

    /*�����ѡ��*/
    ulOptionFrameDrift = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstNetWorkTime->bitOpFrameDrift = ulOptionFrameDrift;

    /*����secondsFromFrameStructureStart*/
    ulSecondsFromFrameStructureStart = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                    pulCurrentBitPos, 14);
    pstNetWorkTime->ulSecondsFromFrameStructureStart = ulSecondsFromFrameStructureStart;
    if(pstNetWorkTime->ulSecondsFromFrameStructureStart > 12533)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_NETTIME_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__,
                                 pstNetWorkTime->ulSecondsFromFrameStructureStart);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����fractionalSecondsFromFrameStructureStart*/
    ulFractionalSecondsFromFrameStructureStart = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 22);
    pstNetWorkTime->ulFractionalSecondsFromFrameStructureStart = ulFractionalSecondsFromFrameStructureStart;
    if(pstNetWorkTime->ulFractionalSecondsFromFrameStructureStart > 3999999)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_NETTIME_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__,
                                 pstNetWorkTime->ulFractionalSecondsFromFrameStructureStart);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*����frameDrift*/
    if(NAS_LPP_SLCT == pstNetWorkTime->bitOpFrameDrift)
    {
        pstNetWorkTime->cFrameDrift  = (VOS_INT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 7) - 64;
    }

    /*����CellId*/
    ulRslt = NAS_LPP_DecodeCellId(pucDecodeBitStream, pulCurrentBitPos, &(pstNetWorkTime->stCellID));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*������չ��*/
    if(NAS_LPP_NO_SLCT == pstNetWorkTime->bitOpNetworkTimeExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_NETTIME_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGNSSRefTimeForCell
Description     :����LPP_GNSS_REFERENCE_TIME_FOR_CELL_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-ReferenceTimeForOneCell  ::= SEQUENCE {
        networkTime                 NetworkTime,
        referenceTimeUnc            INTEGER (0..127),
        bsAlign                     ENUMERATED {true}   OPTIONAL,
        ...
    }


Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGNSSRefTimeForCell
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_GNSS_REFERENCE_TIME_FOR_CELL_STRU   *pstGNSSSysTime)
{
    VOS_UINT32                               ulRslt = 0;
    VOS_UINT32                               ulExtIe = 0;
    VOS_UINT32                               ulOptionBsalign = 0;
    VOS_UINT8                                ucReferenceTimeUnc = 0;

    /*������չ��ʶλ*/
    ulExtIe = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstGNSSSysTime->bitOpGNSSReferenceTimeForCellExt = ulExtIe;

    /*�����ѡ��*/
    ulOptionBsalign = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstGNSSSysTime->bitOpBsAlign = ulOptionBsalign;

    /*����networkTime*/
    ulRslt = NAS_LPP_DecodeNetTime(pucDecodeBitStream, pulCurrentBitPos,
                                 &(pstGNSSSysTime->stNetWorkTime));
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        return ulRslt;
    }

    /*����referenceTimeUnc*/
    ucReferenceTimeUnc = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(   pucDecodeBitStream,
                                                                    pulCurrentBitPos, 7);
    pstGNSSSysTime->ucReferenceTimeUnc = ucReferenceTimeUnc;

    /*����bsAlign*/
    if(NAS_LPP_SLCT == pstGNSSSysTime->bitOpBsAlign)
    {
        /*�м�ע�⣬        bsAlign                     ENUMERATED {true}   OPTIONAL,
          ����������ö��ֵ�������ʱ���ǲ�ռ��bitλ�ģ� ֱ�Ӹ�ֵ���ɣ�ǰ����ֻҪѡ�У�
          ��˵��һ���и�ֵ
        */
        pstGNSSSysTime->enBsAlign = LPP_BSALIGN_TRUE;
    }

    /*������չ��*/
    if(NAS_LPP_NO_SLCT == pstGNSSSysTime->bitOpGNSSReferenceTimeForCellExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSREFTIMEFORCELL_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return ulRslt;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   : NAS_LPP_DecodeGPSTowAssitElement
Description     :����pGPSTOWAssistElement
Input           : ��Ϣ������
Output          : None
ASN             :
    GPS-TOW-AssistElement ::= SEQUENCE {
        satelliteID     INTEGER (1..64),
        tlmWord         INTEGER (0..16383),
        antiSpoof       INTEGER (0..1),
        alert           INTEGER (0..1),
        tlmRsvdBits     INTEGER (0..3),
        ...
    }

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.lifuxin 00253982           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGPSTowAssitElement
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GPS_TOW_ASSIST_ELEMENT_STRU    *pstGPSTOWAssistElement
)
{
    VOS_UINT32                          ulRslt = 0;
    VOS_UINT32                          ulExtIe = 0;
    VOS_UINT8                           ucSatelliteId = 0;
    VOS_UINT16                          usTlmWord = 0;
    VOS_UINT8                           ucAntiSpoof = 0;
    VOS_UINT8                           ucAlert = 0;
    VOS_UINT8                           ucTlmRsvdBits = 0;

    /*ע��:���ڲ�Ӱ��BITλ����������ASN��������жϣ��ŵ�������ȥ*/

    /*������չ��ʶλ*/
    ulExtIe = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    pstGPSTOWAssistElement->bitOpGPSTowAssistElementExt = ulExtIe;

    /*����satelliteID*/
    ucSatelliteId = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                            pulCurrentBitPos, 6);
    pstGPSTOWAssistElement->ucSatalliteID = ucSatelliteId + 1;

    /*����tlmWord*/
    usTlmWord = (VOS_UINT16)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                         pulCurrentBitPos, 14);
    pstGPSTOWAssistElement->usTlmWord = usTlmWord;

    /*����antiSpoof*/
    ucAntiSpoof = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                            pulCurrentBitPos, 1);
    pstGPSTOWAssistElement->ucAntiSpoof = ucAntiSpoof;

    /*����alert*/
    ucAlert = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                        pulCurrentBitPos, 1);
    pstGPSTOWAssistElement->ucAlert = ucAlert;

    /*����tlmRsvdBits*/
    ucTlmRsvdBits = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                            pulCurrentBitPos, 2);
    pstGPSTOWAssistElement->ucTlmRsvdBits = ucTlmRsvdBits;

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGPSTOWAssistElement->bitOpGPSTowAssistElementExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_GPSTOWASSISELEMENT_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos, __LINE__,0);
        return  ulRslt;
    }
    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :
Description     :����
Input           : ��Ϣ������
Output          : None
ASN             :
    GPS-TOW-Assist ::= SEQUENCE (SIZE(1..64)) OF GPS-TOW-AssistElement
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGPSTOWAssist
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GPS_TOW_ASSIST_STRU            *pGPSTOWAssist)
{
    VOS_UINT32                          ulRslt              = 0;
    VOS_UINT32                          ulLoop              = 0;
    VOS_UINT32                          ulGpsTowAssistLen   = 0;

    /*����ṹ�������ļ���ֵ*/
    ulGpsTowAssistLen = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 6);
    ulGpsTowAssistLen += 1;
    pGPSTOWAssist->ulGpsTowAssistCnt = ulGpsTowAssistLen;

    /*�������Ľṹ*/
    for (ulLoop = 0; ulLoop < ulGpsTowAssistLen; ulLoop++)
    {
        ulRslt = NAS_LPP_DecodeGPSTowAssitElement(pucDecodeBitStream, pulCurrentBitPos,
                                                &(pGPSTOWAssist->astGpsTowAssistArray[ulLoop]));
        if (NAS_LPP_DECODE_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGNSSTimeIDStr
Description     :����
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGNSSTimeIDStr
(
    VOS_UINT8                       *pucDecodeBitStream,
    VOS_UINT32                      *pulCurrentBitPos,
    VOS_UINT8                       ucLen,
    LPP_GNSS_ID_STRU                *pstGnssId
)

{
    VOS_UINT32      ulReturnRslt = 0;

    pstGnssId->bitOpGNSSIDExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                            pulCurrentBitPos, 1);

    ulReturnRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                                ucLen, &(pstGnssId->enGnssId));
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSTIMEIDSTR_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return      ulReturnRslt;
    }
    if(NAS_LPP_EXT_ENUMERATED_BUTT == pstGnssId->enGnssId)
    {
        pstGnssId->enGnssId = LPP_GNSS_ID_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSTIMEIDSTR_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__,0);
    }


    if(NAS_LPP_NO_SLCT == pstGnssId->bitOpGNSSIDExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }
    ulReturnRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream,  pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSTIMEIDSTR_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return  ulReturnRslt;
    }
    return ulReturnRslt;
}

/*****************************************************************************
Function Name   :
Description     :����
Input           : ��Ϣ������
Output          : None

gnss-id             ENUMERATED{ gps, sbas, qzss, galileo, glonass, ...}

Return          : �ɹ�����NAS_LPP_DECODE_SUCC
                  ʧ�ܷ���NAS_LPP_DecodeFAIL
History         :
  1.WANGENSHENG 00324863           2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGNSSTimeID
(
    VOS_UINT8                       *pucDecodeBitStream,
    VOS_UINT32                      *pulCurrentBitPos,
    VOS_UINT8                       ucLen,
    LPP_GNSS_ID_ENUM_UINT8          *pIntiator
)

{
    VOS_UINT32      ulReturnRslt = 0;

    ulReturnRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos,
                                                ucLen, pIntiator);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSTIMEID_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                 *pulCurrentBitPos, __LINE__, 0);
        return      ulReturnRslt;
    }
    if((NAS_LPP_EXT_ENUMERATED_BUTT == *pIntiator)||(*pIntiator > 4))
    {
        *pIntiator = LPP_GNSS_ID_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSTIMEID_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                    *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGNSSSysTime
Description     :����LPP_GNSS_SYSTEM_TIME_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-SystemTime ::= SEQUENCE {
        gnss-TimeID                     GNSS-ID,
        gnss-DayNumber                  INTEGER (0..32767),
        gnss-TimeOfDay                  INTEGER (0..86399),
        gnss-TimeOfDayFrac-msec         INTEGER (0..999)        OPTIONAL,   -- Need ON
        notificationOfLeapSecond        BIT STRING (SIZE(2))    OPTIONAL,   -- Cond gnss-TimeID-glonass
        gps-TOW-Assist                  GPS-TOW-Assist          OPTIONAL,   -- Cond gnss-TimeID-gps
        ...
    }


Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863        2015-05-12  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGNSSSysTime
(
    VOS_UINT8                           *pucDecodeBitStream,
    VOS_UINT32                          *pulCurrentBitPos,
    LPP_GNSS_SYSTEM_TIME_STRU           *pstGNSSSysTime)
{
    VOS_UINT32                           ulReturnRslt = 0;

    /*������չλ��optional��־λ*/
    pstGNSSSysTime->bitOpGNSSSystemTimeExt = NAS_LPP_GetDataFromBitStream(      pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstGNSSSysTime->bitOpGNSSTimeOfDayFracMsec = NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstGNSSSysTime->bitOpGNSSNotifOfLeapSecond = NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstGNSSSysTime->bitOpGNSSGpsTowAssit = NAS_LPP_GetDataFromBitStream(        pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);

    /*����ṹ������*/
    ulReturnRslt = NAS_LPP_DecodeGNSSTimeIDStr(pucDecodeBitStream, pulCurrentBitPos, 3, &(pstGNSSSysTime->stGNSSTimeID));
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        return  ulReturnRslt;
    }

    pstGNSSSysTime->ulGNSSDayNumber = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                   pulCurrentBitPos, 15);

    pstGNSSSysTime->ulGNSSTimeOfDay = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                   pulCurrentBitPos, 17);
    if(pstGNSSSysTime->ulGNSSTimeOfDay > 86399)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSSYSTIME_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pulCurrentBitPos, __LINE__,pstGNSSSysTime->ulGNSSTimeOfDay);
        return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    if(NAS_LPP_SLCT == pstGNSSSysTime->bitOpGNSSTimeOfDayFracMsec)
    {
        pstGNSSSysTime->ulGNSSTimeOfDayFracMsec = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                                pulCurrentBitPos, 10);
        if(pstGNSSSysTime->ulGNSSTimeOfDayFracMsec > 999)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSSYSTIME_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pulCurrentBitPos, __LINE__, pstGNSSSysTime->ulGNSSTimeOfDayFracMsec);
            return  NAS_LPP_DECODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
    }

    if(NAS_LPP_SLCT == pstGNSSSysTime->bitOpGNSSNotifOfLeapSecond)
    {
        pstGNSSSysTime->ucGNSSNotifOfLeapSecond = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                                          pulCurrentBitPos, 2);
    }

    if(NAS_LPP_SLCT == pstGNSSSysTime->bitOpGNSSGpsTowAssit)
    {
        ulReturnRslt = NAS_LPP_DecodeGPSTOWAssist(pucDecodeBitStream, pulCurrentBitPos,
                                                &(pstGNSSSysTime->stGpsTowAssist));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }
    }

    /*������չ��*/
    if(pstGNSSSysTime->bitOpGNSSSystemTimeExt == NAS_LPP_NO_SLCT)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulReturnRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSSYSTIME_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return  ulReturnRslt;
    }

    return  ulReturnRslt;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGNSSRefTime
Description     :����LPP_GNSS_REFERENCE_TIME_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-ReferenceTime ::= SEQUENCE  {
        gnss-SystemTime             GNSS-SystemTime,
        referenceTimeUnc            INTEGER (0..127)                    OPTIONAL,   -- Cond noFTA
        gnss-ReferenceTimeForCells  SEQUENCE (SIZE (1..16)) OF
                                        GNSS-ReferenceTimeForOneCell    OPTIONAL,   -- Need ON
        ...
    }

Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.wangensheng  w00324863          2015-05-12  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGNSSRefTime
(
    VOS_UINT8                              *pucDecodeBitStream,
    VOS_UINT32                             *pulCurrentBitPos,
    LPP_GNSS_REFERENCE_TIME_STRU           *pstGNSSRefTime
)
{
    VOS_UINT32                              ulReturnRslt    = 0;
    VOS_UINT32                              ulCount         = 0;

    /*������չ���־λ��OPTIONAL��־λ*/
    pstGNSSRefTime->bitOpGNSSReferenceTimeExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                             pulCurrentBitPos, 1);
    pstGNSSRefTime->bitOpGNSSRefTimeUnc = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                       pulCurrentBitPos, 1);
    pstGNSSRefTime->bitOpGNSSRefTimeForCell = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                           pulCurrentBitPos, 1);

    /*����gnss-SystemTime*/
    ulReturnRslt = NAS_LPP_DecodeGNSSSysTime(pucDecodeBitStream, pulCurrentBitPos,
                                           &(pstGNSSRefTime->stGNSSSystemTime));
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        return  ulReturnRslt;
    }

    /*����referenceTimeUnc*/
    if(NAS_LPP_SLCT == pstGNSSRefTime->bitOpGNSSRefTimeUnc)
    {
        ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 7);
        pstGNSSRefTime->ucRefTimeUnc = (VOS_UINT8)ulReturnRslt;
    }
    /*����gnss-referencetimeforonecell*/
    if(NAS_LPP_SLCT == pstGNSSRefTime->bitOpGNSSRefTimeForCell)
    {
        ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 4);
        ulReturnRslt++;
        pstGNSSRefTime->ulGNSSReferenceTimeForCellsCnt = ulReturnRslt;
        for(ulCount = 0; ulCount < pstGNSSRefTime->ulGNSSReferenceTimeForCellsCnt;ulCount++)
        {
            ulReturnRslt = NAS_LPP_DecodeGNSSRefTimeForCell(pucDecodeBitStream,
                                                            pulCurrentBitPos,
                                                          &(pstGNSSRefTime->astGNSSReferenceTimeForCells[ulCount]));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return  ulReturnRslt;
            }

        }
    }

    /*������չ�δѡ�еĴӼ����м�ȥ��ѡ�е�������L+V*/
    if(NAS_LPP_NO_SLCT == pstGNSSRefTime->bitOpGNSSReferenceTimeExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulReturnRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSREFTIME_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return  ulReturnRslt;
    }

    return  ulReturnRslt;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeGNSSComAssistData
Description     :����LPP_GNSS_COMMON_ASSIST_DATA_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
GNSS-CommonAssistData ::= SEQUENCE {
        gnss-ReferenceTime              GNSS-ReferenceTime                  OPTIONAL,   -- Need ON
        gnss-ReferenceLocation          GNSS-ReferenceLocation              OPTIONAL,   -- Need ON
        gnss-IonosphericModel           GNSS-IonosphericModel               OPTIONAL,   -- Need ON
        gnss-EarthOrientationParameters GNSS-EarthOrientationParameters     OPTIONAL,   -- Need ON
        ...
    }

Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.wangensheng  w00324863            2015-05-12  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeGNSSComAssistData
(
    VOS_UINT8                          *pucDecodeBitStream,
    VOS_UINT32                         *pulCurrentBitPos,
    LPP_GNSS_COMMON_ASSIST_DATA_STRU   *pstGNSSComAssistData
)
{
    VOS_UINT32                          ulReturnRslt = 0;

    /*����option�Լ���չ��־λ*/
    pstGNSSComAssistData->bitOpGNSSCommonAssistDataExt = NAS_LPP_GetDataFromBitStream(
                                                                                        pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 1);
    pstGNSSComAssistData->bitOpGNSSRefTime = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                          pulCurrentBitPos, 1);
    pstGNSSComAssistData->bitOpGNSSRefLocation = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                              pulCurrentBitPos, 1);
    pstGNSSComAssistData->bitOpGNSSIonoModel = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);
    pstGNSSComAssistData->bitOpGNSSEarthOriPara = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                               pulCurrentBitPos, 1);

    /*����ṹ������*/
    if(NAS_LPP_SLCT == pstGNSSComAssistData->bitOpGNSSRefTime)
    {
        ulReturnRslt = NAS_LPP_DecodeGNSSRefTime(pucDecodeBitStream, pulCurrentBitPos,
                                               &(pstGNSSComAssistData->stGNSSReferenceTime));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }

    }

    if(NAS_LPP_SLCT == pstGNSSComAssistData->bitOpGNSSRefLocation)
    {
        ulReturnRslt = NAS_LPP_DecodeGNSSRefLocation(pucDecodeBitStream, pulCurrentBitPos,
                                                   &(pstGNSSComAssistData->stGNSSReferenceLocation));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }

    }

    if(NAS_LPP_SLCT == pstGNSSComAssistData->bitOpGNSSIonoModel)
    {
        ulReturnRslt = NAS_LPP_DecodeGNSSIonoModel(pucDecodeBitStream, pulCurrentBitPos,
                                                 &(pstGNSSComAssistData->stIonosphericModel));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }

    }

    if(NAS_LPP_SLCT == pstGNSSComAssistData->bitOpGNSSEarthOriPara)
    {
        ulReturnRslt = NAS_LPP_DecodeGNSSEarthParam(pucDecodeBitStream, pulCurrentBitPos,
                                                  &(pstGNSSComAssistData->stEarthOrientationParameters));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }

    }

    /*������չ�δ��ѡ�еļ�����һ��ѡ�е�����L+V*/
    if(NAS_LPP_NO_SLCT == pstGNSSComAssistData->bitOpGNSSCommonAssistDataExt)
    {
        return  NAS_LPP_DECODE_SUCC;
    }

    ulReturnRslt = NAS_LPP_DecodeExtObject( pucDecodeBitStream,  pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_GNSSCOMMONASSISTDATA_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                *pulCurrentBitPos, __LINE__,0);
        return  ulReturnRslt;
    }

    return ulReturnRslt;
}
/*****************************************************************************
Function Name   :NAS_LPP_DecodeProAssistDataAGNSS
Description     :����LPP_AGNSS_PROVIDE_ASSIST_DATA_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
A-GNSS-ProvideAssistanceData ::= SEQUENCE {
        gnss-CommonAssistData           GNSS-CommonAssistData               OPTIONAL,   -- Need ON
        gnss-GenericAssistData          GNSS-GenericAssistData              OPTIONAL,   -- Need ON
        gnss-Error                      A-GNSS-Error                        OPTIONAL,   -- Need ON
        ...
    }

Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.wangensheng  w00324863            2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeProAssistDataAGNSS
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_AGNSS_PROVIDE_ASSIST_DATA_STRU      *pstProAssistDataAGNSS
)
{
    VOS_UINT32                               ulReturnRslt = 0;

    /*������չλ��OPTIONAL��־λ*/
    pstProAssistDataAGNSS->bitOpAGnssProvideAssistDataExt = NAS_LPP_GetDataFromBitStream(
                                                                                        pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 1);
    pstProAssistDataAGNSS->bitOpGNSSCommonAssitData = NAS_LPP_GetDataFromBitStream(
                                                                                        pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 1);
    pstProAssistDataAGNSS->bitOpGNSSGenericAssitData = NAS_LPP_GetDataFromBitStream(
                                                                                        pucDecodeBitStream,
                                                                                        pulCurrentBitPos, 1);
    pstProAssistDataAGNSS->bitOpGNSSError = NAS_LPP_GetDataFromBitStream(
                                                                         pucDecodeBitStream,
                                                                         pulCurrentBitPos, 1);

    /*�����ṹ������*/
    if(NAS_LPP_SLCT == pstProAssistDataAGNSS->bitOpGNSSCommonAssitData)
    {
        ulReturnRslt = NAS_LPP_DecodeGNSSComAssistData( pucDecodeBitStream,
                                                        pulCurrentBitPos,
                                                      &(pstProAssistDataAGNSS->stGNSSCommonAssistData));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }
    }

    if(NAS_LPP_SLCT == pstProAssistDataAGNSS->bitOpGNSSGenericAssitData)
    {
        ulReturnRslt = NAS_LPP_DecodeGNSSGenAssistData( pucDecodeBitStream,
                                                        pulCurrentBitPos,
                                                      &(pstProAssistDataAGNSS->stGNSSGenericAssitData));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }

    }

    if(NAS_LPP_SLCT == pstProAssistDataAGNSS->bitOpGNSSError)
    {
        ulReturnRslt = NAS_LPP_DecodeGNSSError( pucDecodeBitStream,
                                                pulCurrentBitPos,
                                              &(pstProAssistDataAGNSS->stGNSSError));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }

    }

    /*���ݸ߰汾����չ��,���û����չ���򷵻�*/
    if(NAS_LPP_NO_SLCT == pstProAssistDataAGNSS->bitOpAGnssProvideAssistDataExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*����չ����ֱ���������ɣ��ж��Ƿ������ȷ*/
    ulReturnRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_PROASSISTAGNSS_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos,
                                    __LINE__,0);
        return  ulReturnRslt;
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeProAssistDataComIEs
Description     :����LPP_COMMON_IES_PROVIDE_ASSIST_DATA_STRU
Input           : ��Ϣ������
Output          : None
ASN             :

Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeProAssistDataComIEs(
                                                    VOS_UINT8                               *pucDecodeBitStream,
                                                    VOS_UINT32                              *pulCurrentBitPos,
                                                    LPP_COMMON_IES_PROVIDE_ASSIST_DATA_STRU *pstProAssComIEs)
{
    VOS_UINT32      ulReturnRslt = 0;

    /*������չ��־λ*/
    ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);
    if(NAS_LPP_SLCT == ulReturnRslt)
    {
        pstProAssComIEs->bitOpCommonIEsProvideAssistDataExt = 1;
    }

    /*���ݸ߰汾����չ��,���û����չ���򷵻�*/
    if(NAS_LPP_NO_SLCT == pstProAssComIEs->bitOpCommonIEsProvideAssistDataExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*����չ����ֱ���������ɣ��ж��Ƿ������ȷ*/
    ulReturnRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR,
                                 NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos,
                                 __LINE__,0);
        return  ulReturnRslt;
    }

    return  NAS_LPP_DECODE_SUCC;
}


/*****************************************************************************
Function Name   :NAS_LPP_DecodeProAssistDataR9IEs
Description     :����LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
ProvideAssistanceData-r9-IEs ::= SEQUENCE {
    commonIEsProvideAssistanceData      CommonIEsProvideAssistanceData      OPTIONAL,   -- Need ON
    a-gnss-ProvideAssistanceData        A-GNSS-ProvideAssistanceData        OPTIONAL,   -- Need ON
    otdoa-ProvideAssistanceData         OTDOA-ProvideAssistanceData         OPTIONAL,   -- Need ON
    epdu-Provide-Assistance-Data        EPDU-Sequence                       OPTIONAL,   -- Need ON
    ...
}

Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
    VOS_UINT32  NAS_LPP_DecodeProAssistDataR9IEs
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_PROVIDE_ASSIST_DATA_R9_IES_STRU     *pstProvdeAssistData
)
{
    VOS_UINT32                               ulReturnRslt = 0;

    /*��ȡext��OPTIONAL��־λ*/
    pstProvdeAssistData->bitOpLPPProvideAssistDataExt = NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstProvdeAssistData->bitOpCommonIEsProvideAssitData = NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstProvdeAssistData->bitOpAGNSSProvideAssistData = NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstProvdeAssistData->bitOpOTDOAProvideAssistData = NAS_LPP_GetDataFromBitStream(
                                                                                pucDecodeBitStream,
                                                                                pulCurrentBitPos, 1);
    pstProvdeAssistData->bitOpEPDUSequence = NAS_LPP_GetDataFromBitStream(  pucDecodeBitStream,
                                                                            pulCurrentBitPos, 1);

    /*�����ṹ������*/
    if(NAS_LPP_SLCT == pstProvdeAssistData->bitOpCommonIEsProvideAssitData)
    {
        ulReturnRslt = NAS_LPP_DecodeProAssistDataComIEs(   pucDecodeBitStream,
                                                            pulCurrentBitPos,
                                                          &(pstProvdeAssistData->stCommonIEsProvideAssistanceData));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }
    }

    if(NAS_LPP_SLCT == pstProvdeAssistData->bitOpAGNSSProvideAssistData)
    {
        ulReturnRslt = NAS_LPP_DecodeProAssistDataAGNSS(    pucDecodeBitStream,
                                                            pulCurrentBitPos,
                                                          &(pstProvdeAssistData->stAGNSSProvideAssistanceData));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }

    }

    if(NAS_LPP_SLCT == pstProvdeAssistData->bitOpOTDOAProvideAssistData)
    {
        ulReturnRslt = NAS_LPP_DecodeProAssistDataOTDOA(    pucDecodeBitStream,
                                                            pulCurrentBitPos,
                                                          &(pstProvdeAssistData->stOTDOAProvideAssistanceData));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }

    }

    if(NAS_LPP_SLCT == pstProvdeAssistData->bitOpEPDUSequence)
    {
        ulReturnRslt = NAS_LPP_DecodeProAssistDataEPDU( pucDecodeBitStream,
                                                        pulCurrentBitPos,
                                                      &(pstProvdeAssistData->stEPDUProvideAssistanceData));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }

    }

     /*���ݸ߰汾����չ��,���û����չ���򷵻�*/
    if(NAS_LPP_NO_SLCT == pstProvdeAssistData->bitOpLPPProvideAssistDataExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*����չ����ֱ���������ɣ��ж��Ƿ������ȷ*/
    ulReturnRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_PROASSISTDATAR9IES_ERROR,
                                    NAS_LPP_EXT_OBJECT_BIT_ERROR,
                                   *pulCurrentBitPos,
                                  __LINE__,0);
        return  ulReturnRslt;
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeExtProvideAssistData
Description     :����LPP_CRITI_EXT_PROVIDE_ASSIST_DATA_STRU
Input           : ��Ϣ������
Output          : None
ASN             :
Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-8  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeExtProvideAssistData
(
    VOS_UINT8                               *pucDecodeBitStream,
    VOS_UINT32                              *pulCurrentBitPos,
    LPP_CRITI_EXT_PROVIDE_ASSIST_DATA_STRU  *pstProvdeAssistData
)
{
    VOS_UINT32                               ulReturnRslt       = 0;

    /*ѡ�����ֵ*/
    pstProvdeAssistData->ulChoice = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                  pulCurrentBitPos, 2);

    /*���ѡ����Ϣ�����*/
    switch(pstProvdeAssistData->ulChoice)
    {
        case LPP_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_R9_CHOSEN:
            ulReturnRslt =NAS_LPP_DecodeProAssistDataR9IEs( pucDecodeBitStream,
                                                            pulCurrentBitPos,
                                                          &(pstProvdeAssistData->u.stProvideAssitDataR9));
            if(NAS_LPP_ENCODE_SUCC != ulReturnRslt)
            {
                return ulReturnRslt;
            }
            break;

        default :
            break;
    }

    return      NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeProvideAssist
Description     :����ProvideAssistanceData
Input           : ��Ϣ������
Output          : None
ASN             :
ProvideAssisData ::= SEQUENCE {
        criticalExtensions      CHOICE {
            c1                      CHOICE {
                ProvideAssisData-r9      ProvideAssisData-r9-IEs,
                spare3 NULL, spare2 NULL, spare1 NULL
            },
            criticalExtensionsFuture    SEQUENCE {}
        }
    }

   ProvideAssisData-r9-IEs ::= SEQUENCE {
        commonIEsProvideAssisData        CommonIEsProvideAssisData              OPTIONAL,
        a-gnss-ProvideAssisData         A-GNSS-ProvideAssisData                 OPTIONAL,
        otdoa-ProvideAssisData          OTDOA-ProvideAssisData                  OPTIONAL,
        epdu-ProvideAssisData            EPDU-Sequence                          OPTIONAL,
        ...
    }

Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeProvideAssist
(
    VOS_UINT8                              *pucDecodeBitStream,
    VOS_UINT32                             *pulCurrentBitPos,
    LPP_MESSAGE_PROVIDE_ASSIST_DATA_STRU   *pstProvideAssistData
)
{
    VOS_UINT32                              ulReturnRslt = 0;

    /*choice���ѡ�����ֵ*/
    pstProvideAssistData->ulChoice  = NAS_LPP_GetDataFromBitStream( pucDecodeBitStream,
                                                                    pulCurrentBitPos, 1);

    /*������Ϣ��*/
    switch(pstProvideAssistData->ulChoice )
    {
        case LPP_C1_CRITI_EXT_PROVIDE_ASSIST_DATA_CHOSEN:
            ulReturnRslt = NAS_LPP_DecodeExtProvideAssistData(  pucDecodeBitStream,
                                                                pulCurrentBitPos,
                                                              &(pstProvideAssistData->u.stC1));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return ulReturnRslt;
            }
            break;

        default :
            break;
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeSupportMessageBody
Description     :����MessageBody�е�������
Input           : ��Ϣ������
Asn             :
c1                      CHOICE {
    requestCapabilities         RequestCapabilities,
    provideCapabilities         ProvideCapabilities,
    requestAssistanceData       RequestAssistanceData,
    provideAssistanceData       ProvideAssistanceData,
    requestLocationInformation  RequestLocationInformation,
    provideLocationInformation  ProvideLocationInformation,
    abort                       Abort,
    error                       Error,
    spare7 NULL, spare6 NULL, spare5 NULL, spare4 NULL,
    spare3 NULL, spare2 NULL, spare1 NULL, spare0 NULL
},

Output          : None
Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32      NAS_LPP_DecodeSupportMessageBody
(
    VOS_UINT8                       *pucDecodeBitStream,
    VOS_UINT32                      *pulCurrentBitPos,
    LPP_SUPPORT_MESSAGE_BODY_STRU   *pstSupportMessageBody
)
{
    VOS_UINT32  ulReturnRslt = 0;

    pstSupportMessageBody->ulChoice = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                                   pulCurrentBitPos, 4);

    /*����ѡ��ֵ��������Ӧ�Ľ���*/
    switch(pstSupportMessageBody->ulChoice)
    {
        case    LPP_SUPPORT_MESSAGE_BODY_REQUEST_CAPABILITIES_CHOSEN:
            ulReturnRslt = NAS_LPP_DecodeReqCap(pucDecodeBitStream,
                                                pulCurrentBitPos,
                                              &(pstSupportMessageBody->u.stRequestCapabilities));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return ulReturnRslt;
            }
            break;

        case    LPP_SUPPORT_MESSAGE_BODY_PROVIDE_ASSISTANCE_DATA_CHOSEN:
            ulReturnRslt = NAS_LPP_DecodeProvideAssist( pucDecodeBitStream,
                                                        pulCurrentBitPos,
                                                      &(pstSupportMessageBody->u.stProvideAssistanceData));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return ulReturnRslt;
            }
            break;

        case    LPP_SUPPORT_MESSAGE_BODY_REQUEST_LOCATION_INFO_CHOSEN:
            ulReturnRslt = NAS_LPP_DecodeReqLocationInfo(   pucDecodeBitStream,
                                                            pulCurrentBitPos,
                                                          &(pstSupportMessageBody->u.stRequestLocationInformation));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return ulReturnRslt;
            }
            break;

        case    LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN:
            ulReturnRslt = NAS_LPP_DecodeAbort( pucDecodeBitStream,
                                                pulCurrentBitPos,
                                              &(pstSupportMessageBody->u.stAbort));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return ulReturnRslt;
            }
            break;

        case    LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN:
            ulReturnRslt = NAS_LPP_DecodeError( pucDecodeBitStream,
                                                pulCurrentBitPos,
                                              &(pstSupportMessageBody->u.stError));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return ulReturnRslt;
            }
            break;

        default :
            break;
    }

    return      NAS_LPP_DECODE_SUCC;
}
/*****************************************************************************
Function Name   :NAS_LPP_DecodeIntiator
Description     :����LPP_INITIATOR_TYPE_ENUM_UINT8
Input           :  pucDecodeBitStream   ��Ҫ�����������Ϣ����
                   pulCurrentBitPos     ��ʼ�����bitλ
                   pstTransactionID     ����֮����Ϣ���buffer
Asn             :
    Initiator ::= ENUMERATED {
        locationServer,
        targetDevice,
        ...
    }
Output          : None
Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-18  Draft Enact
*****************************************************************************/
VOS_UINT32      NAS_LPP_DecodeIntiator
(
    VOS_UINT8                       *pucDecodeBitStream,
    VOS_UINT32                      *pulCurrentBitPos,
    VOS_UINT8                       ucLen,
    LPP_INITIATOR_TYPE_ENUM_UINT8   *pIntiator
)
{
    VOS_UINT32      ulReturnRslt = 0;

    ulReturnRslt = NAS_LPP_DecodeExtEnumerated(pucDecodeBitStream, pulCurrentBitPos, ucLen, pIntiator);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_INTIATOR_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pulCurrentBitPos, __LINE__, 0);
        return      ulReturnRslt;
    }
    if(NAS_LPP_EXT_ENUMERATED_BUTT == *pIntiator)
    {
        *pIntiator = LPP_INITIATOR_TYPE_BUTT;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_INTIATOR_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_WARNING,
                                *pulCurrentBitPos, __LINE__, 0);
    }

    return NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeTransactionID
Description     :����TRANSACTIONID
Input           :  pucDecodeBitStream   ��Ҫ�����������Ϣ����
                   pulCurrentBitPos     ��ʼ�����bitλ
                   pstTransactionID     ����֮����Ϣ���buffer
ASN             :

    LPP-TransactionID ::= SEQUENCE {
        initiator               Initiator,
        transactionNumber       TransactionNumber,
        ...

    }
Output          : None
Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32      NAS_LPP_DecodeTransactionID(
                                                VOS_UINT8       *pucDecodeBitStream,
                                                VOS_UINT32      *pulCurrentBitPos,
                                                LPP_TRANSACTION_ID_STRU *pstTransactionID)
{
    VOS_UINT32      ulReturnRslt = 0;

    /*��ȡ��չ��־λ*/
    pstTransactionID->bitOpTransactionIDExt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos,1);

    /*��չö����Ľ���*/
    ulReturnRslt = NAS_LPP_DecodeIntiator(pucDecodeBitStream, pulCurrentBitPos, 1, &(pstTransactionID->enInitiator));
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        return  ulReturnRslt;
    }

    /*����TransactionNumber*/
    pstTransactionID->ucTransactionNumber  = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

    /*���ݸ߰汾����չ��,���û����չ���򷵻�*/
    if(NAS_LPP_NO_SLCT == pstTransactionID->bitOpTransactionIDExt)
    {
        return NAS_LPP_DECODE_SUCC;
    }

    /*����չ����ֱ���������ɣ��ж��Ƿ������ȷ*/
    ulReturnRslt = NAS_LPP_DecodeExtObject(pucDecodeBitStream, pulCurrentBitPos);
    if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_DECODE_TRANSACTIONID_ERROR, NAS_LPP_EXT_OBJECT_BIT_ERROR, *pulCurrentBitPos, __LINE__,0);
        return  ulReturnRslt;
    }
    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   : NAS_LPP_DecodeSequenceNumber
Description     : ����SequenceNumber
Input           :  pucDecodeBitStream   ��Ҫ�����������Ϣ����
                   pulCurrentBitPos     ��ʼ�����bitλ
                   pSequenceNumber     ����֮����Ϣ���buffer
Output          : None
asn             :SequenceNumber ::= INTEGER (0..255)
Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-5  Draft Enact
*****************************************************************************/
VOS_VOID      NAS_LPP_DecodeSequenceNumber(
                                                VOS_UINT8       *pucDecodeBitStream,
                                                VOS_UINT32      *pulCurrentBitPos,
                                                LPP_SEQUENCE_NUMBER_STRU *pstSequenceNumber)
{
    pstSequenceNumber->ucSequenceNumber = (VOS_UINT8)NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 8);

}

/*****************************************************************************

Function Name   :NAS_LPP_DecodeAcknowledgement
Description     :����Acknowledgement�ṹ��
Input           :  pucDecodeBitStream   ��Ҫ�����������Ϣ����
                   pulCurrentBitPos     ��ʼ�����bitλ
                   pstAcknowledgement   ����֮����Ϣ���buffer
Output          : None
ASN             :
        Acknowledgement ::= SEQUENCE {
        ackRequested    BOOLEAN,
        ackIndicator    SequenceNumber      OPTIONAL
Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32      NAS_LPP_DecodeAcknowledgement
(
    VOS_UINT8                           *pucDecodeBitStream,
    VOS_UINT32                          *pulCurrentBitPos,
    LPP_ACKNOWLEDGEMENT_STRU            *pstAcknowledgement
)
{
    VOS_UINT32      ulReturnRslt = 0;

    /*��ȡOPTIONAL��־λ*/
    pstAcknowledgement->bitOpAckIndicator = NAS_LPP_GetDataFromBitStream(
                                        pucDecodeBitStream, pulCurrentBitPos, 1);

    /*��ȡ�ṹ��������*/
    /*��ȡbool����ֵ*/
    ulReturnRslt = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream,
                                                        pulCurrentBitPos, 1);
    if(1 == ulReturnRslt)
    {
        pstAcknowledgement->bAckRequested = NAS_LPP_TRUE;
    }
    else
    {
        pstAcknowledgement->bAckRequested = NAS_LPP_FALSE;
    }

    /*����ackIndicator*/
    if(NAS_LPP_SLCT == pstAcknowledgement->bitOpAckIndicator)
    {
        NAS_LPP_DecodeSequenceNumber(pucDecodeBitStream, pulCurrentBitPos, &(pstAcknowledgement->stAckIndicator));
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
Function Name   :NAS_LPP_DecodeMessageBody
Description     : ����LPP��Ϣ��
Input           :  pucDecodeBitStream   ��Ҫ�����������Ϣ����
                   pulCurrentBitPos     ��ʼ�����bitλ
                   pstAcknowledgement   ����֮����Ϣ���buffer
asn             :
LPP-MessageBody ::= CHOICE {
                    CHOICE {
        requestCapabilities         RequestCapabilities,
        provideCapabilities         ProvideCapabilities,
        requestAssistanceData       RequestAssistanceData,
        provideAssistanceData       ProvideAssistanceData,
        requestLocationInformation  RequestLocationInformation,
        provideLocationInformation  ProvideLocationInformation,
        abort                       Abort,
        error                       Error,
        spare7 NULL, spare6 NULL, spare5 NULL, spare4 NULL,
        spare3 NULL, spare2 NULL, spare1 NULL, spare0 NULL
        ,
        messageClassExtension	SEQUENCE {}
}

Output          : None
Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
History         :
  1.WANGENSHENG 00324863           2015-05-5  Draft Enact
*****************************************************************************/
VOS_UINT32      NAS_LPP_DecodeMessageBody(
                                                VOS_UINT8       *pucDecodeBitStream,
                                                VOS_UINT32      *pulCurrentBitPos,
                                                LPP_MESSAGE_BODY_STRU *pstMessageBody)
{
    VOS_UINT32  ulReturnRslt = 0;

    /*choice�ṹ�壬���������ȡһ��bit*/
     pstMessageBody->ulChoice = NAS_LPP_GetDataFromBitStream(pucDecodeBitStream, pulCurrentBitPos, 1);

    /*���ѡ����Ϣ�壬�����*/
    switch(pstMessageBody->ulChoice)
    {
        case LPP_C1_MESSAGE_BODY_CHOSEN:
            ulReturnRslt = NAS_LPP_DecodeSupportMessageBody(pucDecodeBitStream,
                                                            pulCurrentBitPos,
                                                          &(pstMessageBody->u.stC1));
            if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
            {
                return ulReturnRslt;
            }
            break;

        default:
            break;
    }

    return  NAS_LPP_DECODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_DecodeMessage
 Description     : LPP������Ϣ������ں���
 Input           : pucDecodeInMsg  ��Ҫ�����������Ϣ����
                   pByteLen       �����������Ϣ��byte num
                   pstLppMsg     ����֮����Ϣ���buffer
 ASN             :

 LPP-Message ::= SEQUENCE {
     transactionID           LPP-TransactionID   OPTIONAL,   -- Need ON
     endTransaction          BOOLEAN,
     sequenceNumber          SequenceNumber      OPTIONAL,   -- Need ON
     acknowledgement         Acknowledgement     OPTIONAL,   -- Need ON
     lpp-MessageBody         LPP-MessageBody     OPTIONAL    -- Need ON
 }

 Output          :
 Return          : VOS_UINT32:NAS_LPP_CAUSE_DECODE_CAUSE_ENUM_UINT32
 History         :
    1.wangensheng    00324863   2015-05-05  Draft   Enact
*****************************************************************************/
VOS_UINT32  NAS_LPP_DecodeMessage
(
    VOS_UINT8                          *pucDecodeInMsg,
    VOS_UINT32                          ulByteLen,
    LPP_MESSAGE_STRU                   *pstLppMsg
)
{
    VOS_UINT32  ulCurrentBitPos =   0;
    VOS_UINT32  ulReturnRslt    =   0;
    VOS_UINT32  ultempByteNum   =   0;
    VOS_UINT32  ulReturnValue   =   0;

    if((NAS_LPP_NULL_PTR == pstLppMsg)
        || (NAS_LPP_NULL_PTR == pucDecodeInMsg))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_MESSAGE_ERROR, NAS_LPP_EMPTY_POINT, 0, __LINE__, 0);
        return NAS_LPP_DECODE_NULL_PTR;
    }

    /*�����ѡ��*/
    pstLppMsg->bitOpLppTransactionId = NAS_LPP_GetDataFromBitStream(pucDecodeInMsg,
                                                                   &ulCurrentBitPos, 1);
    pstLppMsg->bitOpSequenceNumber   = NAS_LPP_GetDataFromBitStream(pucDecodeInMsg,
                                                                   &ulCurrentBitPos, 1);
    pstLppMsg->bitOpAcknowledgement  = NAS_LPP_GetDataFromBitStream(pucDecodeInMsg,
                                                                   &ulCurrentBitPos, 1);
    pstLppMsg->bitOpLppMessageBody   = NAS_LPP_GetDataFromBitStream(pucDecodeInMsg,
                                                                   &ulCurrentBitPos, 1);

    /*����transaction ID*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpLppTransactionId)
    {
        ulReturnRslt = NAS_LPP_DecodeTransactionID(pucDecodeInMsg, &ulCurrentBitPos,
                                                 &(pstLppMsg->stTransactionId));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }
    }

    /*�����ѡ��EndTransaction*/
    ulReturnValue = NAS_LPP_GetDataFromBitStream(pucDecodeInMsg, &ulCurrentBitPos, 1);
    if(1 == ulReturnValue)
    {
        pstLppMsg->bEndTransaction = NAS_LPP_TRUE;
    }
    else
    {
        pstLppMsg->bEndTransaction = NAS_LPP_FALSE;
    }

    /*����sequenceNumber*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpSequenceNumber)
    {
        NAS_LPP_DecodeSequenceNumber(pucDecodeInMsg, &ulCurrentBitPos,
                                   &(pstLppMsg->stSequenceNumber));
    }

    /*����acknowledgement*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpAcknowledgement)
    {
        ulReturnRslt = NAS_LPP_DecodeAcknowledgement(pucDecodeInMsg, &ulCurrentBitPos,
                                                   &(pstLppMsg->stAcknowledgement));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }

    }

    /*����lppMessageBody*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpLppMessageBody)
    {
        ulReturnRslt = NAS_LPP_DecodeMessageBody(pucDecodeInMsg, &ulCurrentBitPos,
                                               &(pstLppMsg->stLppMessageBody));
        if(NAS_LPP_DECODE_SUCC != ulReturnRslt)
        {
            return  ulReturnRslt;
        }
    }

    /*���������������ֽڣ���Ҫ���ֽ��� +1*/
    if((ulCurrentBitPos&0x07) != 0)
    {
        ultempByteNum = (ulCurrentBitPos >> 3) + 1;
    }
    else
    {
        ultempByteNum = (ulCurrentBitPos >> 3);
    }

    if(ultempByteNum != ulByteLen)
    {
        NAS_LPP_ASN_FAIL_Message(   NAS_LPP_DECODE_MESSAGE_ERROR,
                                    NAS_LPP_BIT_STRING_LEN_ERROR,
                                    ulCurrentBitPos, __LINE__, 0);
        return NAS_LPP_DECODE_MSG_BODY_ERROR_TOTOAL_LEN_MISMATCH;
    }

    return NAS_LPP_DECODE_SUCC;
}
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


