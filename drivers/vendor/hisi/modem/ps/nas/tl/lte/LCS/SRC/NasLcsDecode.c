

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "NasLcsDecode.h"
#include    "NasCommPrint.h"
#include    "NasLcsPublic.h"
#include    "NasLcsOm.h"
#include    "PsCommonDef.h"
#include    "PsLogdef.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASLCSDECODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSDECODE_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/* CN��Ϣ���������Ľṹ�壬��Ϣ̫�������ʺ��������ľֲ����� */
NAS_LCS_CN_MSG_STRU                     g_stLcsCnDecodeMsgStru;

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCnMsg
 Description     : LCS�տ���Ϣ������ں���
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulDecodeMsgLen              :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCnMsg
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    NAS_LCS_CN_MSG_TYPE_ENUM_UINT32     enCnMsgType;
    VOS_UINT8                          *pucTemMsg        = pucMsg;
    VOS_UINT32                          ulTmpLen;
    VOS_UINT32                          ulUndecodeMsgLen = *pulLen;
    VOS_UINT32                          ulSum            = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enResult         = NAS_LCS_CAUSE_SUCCESS;

    *pulLen = 0;

    NAS_LCS_MEM_SET_S(pstCnMsgStru, sizeof(NAS_LCS_CN_MSG_STRU), 0, sizeof(NAS_LCS_CN_MSG_STRU));

    /* ���տڳ����Ƿ�Ϸ� */
    if (NAS_LCS_MSG_MIN_LEN > ulUndecodeMsgLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_MSG_LEN,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeMsgLen,
                                    NAS_LCS_MSG_MIN_LEN);

        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeCnMsg UndecodeMsgLen Invalid ", ulUndecodeMsgLen);
        return NAS_LCS_CAUSE_FAIL;
    }

    /* ��ȡ����transaction identifier */
    pstCnMsgStru->ucTi = pucTemMsg[ulSum++] >> NAS_LCS_MOVEMENT_4_BITS;

    /* ��ȡMessage type */
    enCnMsgType = pucMsg[ulSum++] & NAS_LCS_MSG_LOW_6_BIT;

    /* ����Message type */
    pstCnMsgStru->enCnMsgType = enCnMsgType;

    /* ����ʣ��δ�������� */
    ulUndecodeMsgLen = ulUndecodeMsgLen - ulSum;
    ulTmpLen      = ulUndecodeMsgLen;

    /* ������Ϣ���ͽ��н��� */
    switch(enCnMsgType)
    {
        case NAS_LCS_CN_MSG_REL_CML:
            enResult = NAS_LCS_DecodeRelCmpl(pucMsg + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        case NAS_LCS_CN_MSG_FACILITY:
            enResult = NAS_LCS_DecodeFacility(pucMsg + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        case NAS_LCS_CN_MSG_REGISTER:
            enResult = NAS_LCS_DecodeRegister(pucMsg + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        default:
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_MSG_TYPE,
                                        NAS_LCS_MSG_TYPE_INVALID,
                                        enCnMsgType,
                                        NAS_LCS_NULL_PTR);

            NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeCnMsg Msg Type Invalid ", enCnMsgType);
            enResult = NAS_LCS_CAUSE_MSG_TYPE_ERR_OR_NOT_IMPLEMENT;
            break;
    }

    if (NAS_LCS_CAUSE_SUCCESS != enResult)
    {
        return enResult;
    }

    /* ��ȡ�ѽ�����Ϣ���� */
    ulSum       = ulSum + ulTmpLen;
    *pulLen     = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRegister
 Description     : ����Register�տ�����
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRegister
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                          *pucTemMsg        = pucMsg;
    VOS_UINT32                          ulUndecodeMsgLen = *pulLen;
    VOS_UINT32                          ulSum            = 0;
    VOS_UINT32                          ulTmpLen         = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt           = NAS_LCS_CAUSE_SUCCESS;

    *pulLen = 0;

    /* ���ʣ��δ������������ */
    if(NAS_LCS_IE_FACILITY_MIN_LEN > ulUndecodeMsgLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_MSG_LEN,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeMsgLen,
                                    NAS_LCS_IE_FACILITY_MIN_LEN);

        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeRegister UndecodeMsgLen Invalid ", ulUndecodeMsgLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ������ѡ��ԪFACILITY����ʽʱTLV */
    if (NAS_LCS_MSG_FACILITY_IEI == pucTemMsg[ulSum])
    {
        /* ��ѡ��Ԫ����Facility IEI, ����IEI */
        ulSum++;

        ulUndecodeMsgLen = ulUndecodeMsgLen - 1;

        ulTmpLen = ulUndecodeMsgLen;
        enRslt = NAS_LCS_DecodeIeFacility(pucTemMsg + ulSum, &ulTmpLen, pstCnMsgStru);

        /* �ж�FACILITY��Ԫ����������� */
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            NAS_LCS_INFO_LOG(" NAS_LCS_DecodeRegister Facility IE Decode Fail ");
            return enRslt;
        }

        ulSum = ulSum + ulTmpLen;
    }
    else
    {
        /* ȱ�ٱ�ѡ��ԪFacility, ����ʧ�� */
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_FACILITY,
                                    NAS_LCS_MISS_MANDATORY_IE,
                                    pucTemMsg[ulSum],
                                    NAS_LCS_MSG_FACILITY_IEI);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeRegister Miss Facility IE ", pucTemMsg[ulSum]);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeFacility
 Description     : ����Facility�տ���Ϣ
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeFacility
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                          *pucTemMsg        = pucMsg;
    VOS_UINT32                          ulUndecodeMsgLen = *pulLen;
    VOS_UINT32                          ulSum            = 0;
    VOS_UINT32                          ulTmpLen         = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt           = NAS_LCS_CAUSE_SUCCESS;

    *pulLen = 0;

    /* ���ʣ��δ������������ */
    if(NAS_LCS_IE_FACILITY_MIN_LEN > ulUndecodeMsgLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_MSG_LEN,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeMsgLen,
                                    NAS_LCS_IE_FACILITY_MIN_LEN);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeFacility UndecodeMsgLen Invalid ", ulUndecodeMsgLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ������ѡ��ԪFACILITY����ʽ��LV */

    ulTmpLen = ulUndecodeMsgLen;

    /* �ж�FACILITY��Ԫ����������� */
    enRslt = NAS_LCS_DecodeIeFacility(pucTemMsg + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeFacility Facility Ie Decode Fail ", enRslt);
        return enRslt;
    }
    ulSum = ulSum + ulTmpLen;


    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRelCmpl
 Description     : ����Rel Complete�տ���Ϣ
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRelCmpl
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                          *pucTemMsg       = pucMsg;
    VOS_UINT32                          ulUndecodeMsgLen = *pulLen;
    VOS_UINT32                          ulSum            = 0;
    VOS_UINT32                          ulTmpLen;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pulLen = 0;

    /* �ж��Ƿ���ڿ�ѡ��Ԫ */
    if (0 == ulUndecodeMsgLen)
    {
        return NAS_LCS_CAUSE_SUCCESS;
    }

    /* ������ѡ��ԪCause */
    if (NAS_LCS_MSG_CAUSE_IEI == pucTemMsg[ulSum])
    {
        /* ��ȡʣ���������� */
        ulTmpLen = ulUndecodeMsgLen;
        enRslt = NAS_LCS_DecodeCause(pucTemMsg + ulSum, &ulTmpLen, pstCnMsgStru);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* ��ѡ��Ԫ����ʧ�ܷ��سɹ�, ����ʣ������ */
            ulSum   = ulSum + ulUndecodeMsgLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ����CAUSE */
        ulSum = ulSum + ulTmpLen;

        /* ����ʣ���������� */
        ulUndecodeMsgLen = ulUndecodeMsgLen - ulTmpLen;
    }

    /* ������ѡ��ԪFACILITY */
    if ((NAS_LCS_IE_FACILITY_MIN_LEN <= ulUndecodeMsgLen)&&(NAS_LCS_MSG_FACILITY_IEI == pucTemMsg[ulSum]))
    {
        /* ��ѡ��Ԫ����Facility IEI, ����IEI */
        ulSum++;

        ulUndecodeMsgLen = ulUndecodeMsgLen - 1;

        /* ��ȡʣ���������� */
        ulTmpLen = ulUndecodeMsgLen;
        enRslt = NAS_LCS_DecodeIeFacility(pucTemMsg + ulSum, &ulTmpLen, pstCnMsgStru);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* ��ѡ��Ԫ����ʧ�ܷ��سɹ�, ����ʣ������ */
            ulSum   = ulSum + ulUndecodeMsgLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ����Facility */
        ulSum = ulSum + ulTmpLen;

        /* ����ʣ���������� */
        ulUndecodeMsgLen = ulUndecodeMsgLen - ulTmpLen;
    }

    ulSum = ulSum + ulUndecodeMsgLen;

    /* ��ȡ�����ѳ��� */
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeIeFacility
 Description     : ����Facility��Ԫ
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeIeFacility
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulUndecodeMsgLen = *pulLen;
    VOS_UINT8                          *pucTemMsg        = pucMsg;
    VOS_UINT32                          ulSum            = 0;
    VOS_UINT8                           ulValueLen       = 0;
    VOS_UINT32                          ulTmpLen         = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt           = NAS_LCS_CAUSE_SUCCESS;

    /* ��ȡFacility Len */
    ulValueLen = pucTemMsg[ulSum++];

    /* ��ȡʣ����������  */
    ulUndecodeMsgLen = ulUndecodeMsgLen - ulSum;

    /* ��鳤���Ƿ�Ϸ� */
    if ((0 == ulValueLen) || (ulUndecodeMsgLen < ulValueLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_FACILITY,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen,
                                    ulUndecodeMsgLen);
        NAS_LCS_INFO_LOG2(" NAS_LCS_DecodeIeFacility ValueLen Invalid ", ulValueLen, ulUndecodeMsgLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ʣ��������������Ԫʵ�ʳ���Ϊ׼ */
    ulUndecodeMsgLen = ulValueLen;
    ulTmpLen         = ulUndecodeMsgLen;

    /* ����Component */
    enRslt = NAS_LCS_DecodeComponent(pucTemMsg + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /* ����IE */
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeIeFacility Component decode fail ", enRslt);
        return enRslt;
    }

    ulSum   = ulSum + ulTmpLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCause
 Description     : ����CASUE��Ԫ
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : puLen                        :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCause
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *puLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulSum            = 0;
    VOS_UINT32                          ulLen            = 0;
    VOS_UINT32                          ulUndecodeMsgLen = *puLen;
    VOS_UINT8                          *pucMsgTem        = pucMsg;
    VOS_UINT32                          ulIeLen;

    *puLen = 0;

    /* ���ʣ����Ϣ���� */
    if (NAS_LCS_CAUSE_IE_MIN_LEN > ulUndecodeMsgLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CAUSE,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeMsgLen,
                                    NAS_LCS_CAUSE_IE_MIN_LEN);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeCause UndecodeLen Invalid ", ulUndecodeMsgLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����IEI */
    ulSum++;

    /* ��ȡIE���� */
    ulLen     = pucMsgTem[ulSum++];

    /* ��������IE����ΪTL���ȼ���Value���� */
    ulIeLen   = ulSum + ulLen;

    /* �����Ϣ����,ʣ������������ڵ�������IE���� */
    if (ulIeLen > ulUndecodeMsgLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CAUSE,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeMsgLen,
                                    ulIeLen);
        NAS_LCS_INFO_LOG2(" NAS_LCS_DecodeCause UndecodeLen Invalid ", ulUndecodeMsgLen, ulIeLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* IE Cause�ݲ�ʹ�� */
    /* ��������IE */
    *puLen = ulIeLen;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeComponent
 Description     : ����component
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeComponent
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT8                           ucComponentType;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTem       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;

    /* ��ȡ����Component type */
    ucComponentType = pucMsgTem[ulSum];
    pstCnMsgStru->ucComponentType = ucComponentType;

    /* ��ȡʣ���������� */
    ulTmpLen = ulUndecodeLen;

    /* ����component type���ͣ�������Ӧ���룬����:INVOKE, return result, return error, reject */
    switch (ucComponentType)
    {
        case NAS_LCS_COMPONENT_INVOKE_TAG:
            enRslt = NAS_LCS_DecodeInvoke(pucMsgTem + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        case NAS_LCS_COMPONENT_RETURN_RSLT_TAG:
            enRslt = NAS_LCS_DecodeRtrnRslt(pucMsgTem + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        case NAS_LCS_COMPONENT_RETURN_ERR_TAG:
            enRslt = NAS_LCS_DecodeRtrnErr(pucMsgTem + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        case NAS_LCS_COMPONENT_REJECT:
            enRslt = NAS_LCS_DecodeReject(pucMsgTem + ulSum, &ulTmpLen, pstCnMsgStru);
            break;

        default:
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_COMPONENT,
                                        NAS_LCS_CMPONENT_INVALID,
                                        ucComponentType, 0);
            NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeComponent unknow ComponentType ", ucComponentType);
            return NAS_LCS_CAUSE_UNRECOGNIZED_COMPONENT;
    }

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* ����Component */
    ulSum         = ulSum + ulTmpLen;
    ulUndecodeLen = ulUndecodeLen -ulTmpLen;

    /* ����δ��������ʣ�೤�� */
    ulSum         = ulSum + ulUndecodeLen;
    *pulLen       = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRtrnRslt
 Description     : ����Retrun Result Component��ӦPara
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRtrnRslt
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                           ucOperationCode;
    VOS_UINT32                          enRslt              = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum               = 0;
    VOS_UINT8                          *pucMsgTmp           = pucSrc;
    VOS_UINT32                          ulUndecodeLen       = *pulLen;
    VOS_UINT32                          ulTmpLen            = 0;
    VOS_UINT32                          ulValueLen          = 0;
    NAS_LCS_TAG_STRU                    stTagStru;

    *pulLen  = 0;

    /* ��ȡcomponent����, TLV��ʽ */
    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_RTN_RSLT,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_DecodeRtrnRslt Len Decode Fail ");
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����Len */
    ulSum              = ulSum + ulTmpLen;

    /* ��ȡʣ���������,��ʵ����Ԫ��LENΪ׼ */
    ulUndecodeLen      = ulValueLen;
    ulTmpLen           = ulUndecodeLen;

    /* ����INVOKE ID */
    enRslt  = NAS_LCS_DecodeInvokeId(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_INVOKE, NAS_LCS_MISS_MANDATORY_IE, 0, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_DecodeRtrnRslt Invoke Id Decode Fail ");

        /*ȱ��Invoke Id,������Ϣ�������*/
        return enRslt;
    }

    /* ����INVOKE ID */
    ulSum         = ulSum + ulTmpLen;

    /* ����ʣ��������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* ������ѡ��ԪSequence */
    if ((0 < ulUndecodeLen) && (NAS_LCS_SEQUENCE_TAG == pucMsgTmp[ulSum]))
    {
        ulTmpLen = ulUndecodeLen;

        /* ����Len */
        enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);

        /* ��ѡ��Ԫ����ʧ��, �������� */
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            ulSum     = ulSum + ulUndecodeLen;
            *pulLen   = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ����Sequence */
        ulSum         = ulSum + ulTmpLen;

        /* ����ʣ�೤�� */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;
    }

    /* ������ѡ��ԪOperation Code��Parameters */
    if ((0 < ulUndecodeLen) && (NAS_LCS_OPERATION_CODE_TAG == pucMsgTmp[ulSum]))
    {
        /* ����Operation Code */
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeOperationCode(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru, &ucOperationCode);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ����Opertion Code */
        ulSum = ulSum + ulTmpLen;

        /* ����ʣ�೤�� */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* ���ݲ����룬�����component����������Ӧ�Ľ��봦�� */
        if (0 < ulUndecodeLen)
        {
            ulTmpLen = ulUndecodeLen;
            switch(ucOperationCode)
            {
                /* ����Mo-lr Result */
                case NAS_LCS_OPERATION_MO_LR:
                    enRslt = NAS_LCS_DecodeMoLrResult(  pucMsgTmp + ulSum,
                                                        &ulTmpLen,
                                                        &pstCnMsgStru->stMolrResult);
                    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                    {
                        pstCnMsgStru->bitOpMolrResult = pstCnMsgStru->stMolrResult.bitOpDecipherKeys \
                                                        | pstCnMsgStru->stMolrResult.bitOpHGmlcAddr \
                                                        | pstCnMsgStru->stMolrResult.bitOpLocationEstimate \
                                                        | pstCnMsgStru->stMolrResult.bitOpReferNumber \
                                                        | pstCnMsgStru->stMolrResult.bitOpRepPlmnList \
                                                        | pstCnMsgStru->stMolrResult.bitOpShortCircuit \
                                                        | pstCnMsgStru->stMolrResult.bitOpVelocityEstimate;
                    }

                    /* ����Parameters */
                    ulSum         = ulSum + ulTmpLen;
                    ulUndecodeLen = ulUndecodeLen - ulTmpLen;
                    break;

                default:
                    /* ����ʣ��ʣ�೤�� */
                    ulSum   = ulSum + ulUndecodeLen;
                    *pulLen = ulSum;
                    NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_OPERA,
                                                NAS_LCS_UNKNOWN_OPER,
                                                ucOperationCode, 0);
                    NAS_LCS_INFO_LOG(" NAS_LCS_DecodeRtrnRslt Invoke Id Decode Fail ");
                    return NAS_LCS_CAUSE_SUCCESS;
            }
        }
    }

    /* ����ʣ��δ������������ */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstLocEstimate
 Description     : ����Mo LR����ظ�����ԪLocEstimate Value
 Input           : pucSrc                       :����
                   ulLen                        :��ԪLENֵ
                   pstMolrRst                   :������ṹ
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstLocEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulTmpLen                = 0;
    VOS_UINT32                          ulSum = 0;

    /* ��ֹ�������Ƚ�����־������Ԫ���� */
    if (NAS_LCS_OP_TRUE == pstMolrRst->bitOpLocationEstimate)
    {
        return;
    }

    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeLocEstimate( pucSrcTmp + ulSum,
                                        &ulTmpLen,
                                        &pstMolrRst->stLocationEstimate);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        pstMolrRst->bitOpLocationEstimate = NAS_LCS_OP_TRUE;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstDecipherKey
 Description     : ����Mo LR����ظ�����ԪDecipherKey
 Input           : pucSrc                       :����
                   ulLen                        :��ԪLENֵ
                   pstMolrRst                   :������ṹ
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstDecipherKey
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulSum = 0;

    if (NAS_LCS_DECIPHER_KEYS_LEN == ulUndecodeLen)
    {
        NAS_LCS_MEM_CPY_S(  pstMolrRst->aucDecipherKeys,
                            NAS_LCS_DECIPHER_KEYS_LEN,
                            pucSrcTmp + ulSum,
                            NAS_LCS_DECIPHER_KEYS_LEN);

        pstMolrRst->bitOpDecipherKeys = NAS_LCS_OP_TRUE;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstAddLocEstimate
 Description     : ����Mo LR����ظ�����ԪAddLocEstimate
 Input           : pucSrc                       :����
                   ulLen                        :��ԪLENֵ
                   pstMolrRst                   :������ṹ
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstAddLocEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulTmpLen                = 0;
    VOS_UINT32                          ulSum = 0;

    ulTmpLen = ulUndecodeLen;

    if (NAS_LCS_OP_TRUE == pstMolrRst->bitOpLocationEstimate)
    {
        return;
    }

    enRslt = NAS_LCS_DecodeAddLocEstimate(  pucSrcTmp + ulSum,
                                            &ulTmpLen,
                                            &pstMolrRst->stLocationEstimate);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        pstMolrRst->bitOpLocationEstimate = NAS_LCS_OP_TRUE;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstVelEstimate
 Description     : ����Mo LR����ظ�����ԪVelEstimate
 Input           : pucSrc                       :����
                   ulLen                        :��ԪLENֵ
                   pstMolrRst                   :������ṹ
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstVelEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulTmpLen                = 0;
    VOS_UINT32                          ulSum = 0;

    ulTmpLen = ulUndecodeLen;

    enRslt = NAS_LCS_DecodeVelEstimate( pucSrcTmp + ulSum,
                                        &ulTmpLen,
                                        &pstMolrRst->stVelocityEstimate);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        pstMolrRst->bitOpVelocityEstimate = NAS_LCS_OP_TRUE;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstHGmlcAddr
 Description     : ����Mo LR����ظ�����ԪHGmlcAddr
 Input           : pucSrc                       :����
                   ulLen                        :��ԪLENֵ
                   pstMolrRst                   :������ṹ
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstHGmlcAddr
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulTmpLen                = 0;
    VOS_UINT32                          ulSum = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeHGmlcAddr(   pucSrcTmp + ulSum,
                                        &ulTmpLen,
                                        &pstMolrRst->stHGmlcAddr);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        pstMolrRst->bitOpHGmlcAddr = NAS_LCS_OP_TRUE;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstShortCircuit
 Description     : ����Mo LR����ظ�����ԪShortCircuit
 Input           : pucSrc                       :����
                   ulLen                        :��ԪLENֵ
                   pstMolrRst                   :������ṹ
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstShortCircuit
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    VOS_UINT32                          ulUndecodeLen           = ulLen;

    if (0 == ulUndecodeLen)
    {
        pstMolrRst->bitOpShortCircuit = NAS_LCS_OP_TRUE;
    }
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMolrRstReportPlmnList
 Description     : ����Mo LR����ظ�����ԪReportPlmnList
 Input           : pucSrc                       :����
                   ulLen                        :��ԪLENֵ
                   pstMolrRst                   :������ṹ
 Output          : NONE
 Return          : NONE

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeMolrRstReportPlmnList
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = ulLen;
    VOS_UINT32                          ulTmpLen                = 0;
    VOS_UINT32                          ulSum = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeReportPlmnList(  pucSrcTmp + ulSum,
                                            &ulTmpLen,
                                            &pstMolrRst->stRepPlmnList);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        if (0 != pstMolrRst->stRepPlmnList.stPlmnList.ucPlmnNum)
        {
            pstMolrRst->bitOpRepPlmnList = NAS_LCS_OP_TRUE;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeMoLrResult
 Description     : ����Mo LR���ඨλ����ظ�
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeMoLrResult
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_MOLR_RESULT_STRU            *pstMolrRst
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;
    VOS_UINT32                          ulLoop                  = 0;

    *pulLen = 0;

    /* ����TAG��LEN */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /* ����ʣ������ */
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_PARA,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_DecodeMoLrResult TL decode fail ");
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��LEN */
    ulSum = ulSum + ulTmpLen;

    /* ��ȡʣ�೤��,��ʵ����Ԫ��LENΪ׼ */
    ulUndecodeLen = ulValueLen;

    /* ������ѡ��Ԫ, ���ѭ����ѡ��Ԫ���� */
    while((0 != ulUndecodeLen) && (ulLoop < NAS_LCS_MOLR_RESLT_OP_IE_MAX_NUM))
    {
        ulTmpLen = ulUndecodeLen;

        /* ����TAG��LEN */
        enRslt = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* ��ѡ��ԪTL����ʧ��, ��������Ԫʣ���������� */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ����TAG��LEN */
        ulSum = ulSum + ulTmpLen;

        /* ����ʣ���������� */
        ulUndecodeLen = ulUndecodeLen -ulTmpLen;

        /* ��ȡ�ÿ�ѡ��ԪValue���� */
        ulTmpLen = ulValueLen;

        /* ����TAGֵ������ѡ��Ԫ */
        switch(stTagStru.ulNumber)
        {
            /* ����LocationEstimate */
            case 0:
                NAS_LCS_DecodeMolrRstLocEstimate(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* ����decipheringKeys */
            case 1:
                NAS_LCS_DecodeMolrRstDecipherKey(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* ����add-Locationestimate */
            case 2:
                NAS_LCS_DecodeMolrRstAddLocEstimate(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* ����velocityEstimate */
            case 3:
                NAS_LCS_DecodeMolrRstVelEstimate( pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* ����referenceNumber */
            case 4:
                pstMolrRst->bitOpReferNumber = NAS_LCS_OP_TRUE;
                pstMolrRst->ucReferNumber = pucSrcTmp[ulSum];
                break;

            /* ����h-gmlc-address */
            case 5:
                NAS_LCS_DecodeMolrRstHGmlcAddr(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* ����mo-lrShortCircuit */
            case 6:
                NAS_LCS_DecodeMolrRstShortCircuit(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

            /* ����reportingPLMNList */
            case 7:
                NAS_LCS_DecodeMolrRstReportPlmnList(pucSrcTmp + ulSum, ulTmpLen, pstMolrRst);
                break;

             default:
                ulSum   = ulSum + ulUndecodeLen;
                *pulLen = ulSum;
                NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_PARA,
                                            NAS_LCS_UNKNOWN_OP_IE,
                                            stTagStru.ulNumber, 0);
                NAS_LCS_INFO_LOG(" NAS_LCS_DecodeMoLrResult TL decode fail ");
                return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ������ѡ��ԪValue���� */
        ulSum         = ulSum + ulValueLen;
        ulUndecodeLen = ulUndecodeLen - ulValueLen;

        /* ѭ������������1 */
        ulLoop++;
    }

    ulSum = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLatitude
 Description     : ����γ��
 Input           : pucSrc                       :����
 Output          : penLatitudeSign              :�ϱ�γ��ʶ
                   pulDegreeLatitude            :γ��
 Return          : None

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeLatitude
(
    VOS_UINT8                          *pucSrc,
    LOC_COM_LATITUDE_SIGN_ENUM_UINT8   *penLatitudeSign,
    VOS_UINT32                         *pulDegreeLatitude
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* ��ֵ�ϱ�γö�� */
    if (0 == (pucMsgTmp[ulSum] & NAS_LCS_MSG_8_BIT))
    {
        *penLatitudeSign = LOC_COM_LATITUDE_SIGN_NORTH;
    }
    else
    {
        *penLatitudeSign = LOC_COM_LATITUDE_SIGN_SOUTH;
    }

    /* ��ֵγ�� */
    *pulDegreeLatitude  =   (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT) << NAS_LCS_MOVEMENT_16_BITS;
    *pulDegreeLatitude  |=  (pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS);
    *pulDegreeLatitude  |=  pucMsgTmp[ulSum++];
}

/*lint -e713*/
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLongitude
 Description     : ��������
 Input           : pucSrc                       :����
                   pulDegreeLongitude           :����
 Return          : None

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeLongitude
(
    VOS_UINT8                          *pucSrc,
    VOS_INT32                          *plDegreeLongitude
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* ��ֵ���� */
    *plDegreeLongitude  = 0;
    *plDegreeLongitude  =  (pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_16_BITS);
    *plDegreeLongitude  |= (pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS);
    *plDegreeLongitude  |=  pucMsgTmp[ulSum++];

    /* ����տڴ����24�����Ǹ���������Ҫ����8���ز���Ϊ"0xff" */
    if (*plDegreeLongitude >= 0x800000)
    {
        *plDegreeLongitude |= 0xff000000;
    }
}
/*lint +e713*/

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeAltitude
 Description     : ����γ��
 Input           : pucSrc                       :����
 Output          : penAltitudeDirection         :����ȱ�ʶ
                   pusAltitude                  :�߶Ȼ������
 Return          : None

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_DecodeAltitude
(
    VOS_UINT8                          *pucSrc,
    LOC_COM_LATITUDE_DIR_ENUM_UINT8    *penAltitudeDirection,
    VOS_UINT16                         *pusAltitude
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* ��ֵ����ȱ�ʶ */
    if (0 == (pucMsgTmp[ulSum] & NAS_LCS_MSG_8_BIT))
    {
        *penAltitudeDirection = LOC_COM_LATITUDE_DIR_HEITHT;
    }
    else
    {
        *penAltitudeDirection = LOC_COM_LATITUDE_DIR_DEPTH;
    }

    /* ��ֵ�߶Ȼ������ */
    *pusAltitude  =   (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT) << NAS_LCS_MOVEMENT_8_BITS;
    *pusAltitude  |=  pucMsgTmp[ulSum++];
}


/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPoint
 Description     : ����λ����ϢPOINT��ʽ
 Input           : pucSrc                       :����
                   ulLen                        :Value����
 Output          : pstLocationEstimate          :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPoint
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* ���Ȳ���ȷ��ֱ�ӷ���ʧ�� */
    if (ulLen < 7)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_POINT, NAS_LCS_LEN_INVAILID, ulLen, 7);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPoint Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOID_POINT_CHOSEN;

    /* ����shap type */
    ulSum++;

    /* ����γ�� */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPoint.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidPoint.ulDegreeLatitude);
    ulSum += 3;

    /* ���뾭�� */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPoint.lDegreesLongitude);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPointWithCircle
 Description     : ����λ����ϢPOINT WITH UNCERTAINTITY CIRCLE��ʽ
 Input           : pucSrc                       :����
                   ulLen                        :Value����
 Output          : pstLocationEstimate          :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPointWithCircle
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* ���Ȳ���ȷ��ֱ�ӷ���ʧ�� */
    if (ulLen < 8)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_CIRCLE, NAS_LCS_LEN_INVAILID, ulLen, 8);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPointWithCircle Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_CHOSEN;

    /* ����shap type */
    ulSum++;

    /* ����γ�� */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyCircle.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyCircle.ulDegreesLatitude);
    ulSum += 3;

    /* ���뾭�� */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyCircle.lDegreeLongitude);
    ulSum += 3;

    /* ���벻ȷ���� */
    pstLocationEstimate->u.stEllipsoidPointWithUncertaintyCircle.ulUncretainty
                                = (pucMsgTmp[ulSum] & NAS_LCS_MSG_LOW_7_BIT);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPointWithEllipse
 Description     : ����λ����ϢPOINT WITH UNCERTAINTITY ELLIPSE��ʽ
 Input           : pucSrc                       :����
                   ulLen                        :Value����
 Output          : pstLocationEstimate          :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPointWithEllipse
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* ���Ȳ���ȷ��ֱ�ӷ���ʧ�� */
    if (ulLen < 11)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_ELLIPSE, NAS_LCS_LEN_INVAILID, ulLen, 11);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPointWithEllipse Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_CHOSEN;

    /* ����shap type */
    ulSum++;

    /* ����γ�� */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.ulDegreesLatitude);
    ulSum += 3;

    /* ���뾭�� */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.lDegreesLongitude);
    ulSum += 3;

    /* ����SEMI MAJOR */
    pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.ucUncertaintySemiMajor
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* ����SEMI MINOR */
    pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.ucUncertaintySemiMinor
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* ����ORIENTATION OF MAJOR AXIS */
    pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.ucOrientationMajorAxis
                                = pucMsgTmp[ulSum++];

    /* ����CONFIDENCE */
    pstLocationEstimate->u.stEllipsoidPointWithUncertaintyEllipse.ucConfidence
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPointWithAlititudeAndEllipsoid
 Description     : ����λ����ϢPOINT WITH ALTITUDE AND UNCERTAINTITY ELLIPSOID��ʽ
 Input           : pucSrc                       :����
                   ulLen                        :Value����
 Output          : pstLocationEstimate          :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPointWithAlititudeAndEllipsoid
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* ���Ȳ���ȷ��ֱ�ӷ���ʧ�� */
    if (ulLen < 14)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_ALIT_ELLI, NAS_LCS_LEN_INVAILID, ulLen, 14);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPointWithAlititudeAndEllipsoid Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_CHOSEN;

    /* ����shap type */
    ulSum++;

    /* ����γ�� */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ulDegreesLatitude);
    ulSum += 3;

    /* ���뾭�� */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.lDegreesLongtitude);
    ulSum += 3;

    /* ����߶� */
    NAS_LCS_DecodeAltitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.enAltitudeDirection,
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.usAltitude);
    ulSum += 2;

    /* ����SEMI MAJOR */
    pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ucUncertaintySemiMajor
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* ����SEMI MINOR */
    pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ucUncertaintySemiMinor
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* ����ORIENTATION OF MAJOR AXIS */
    pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ucOrientationMajorAxis
                                = pucMsgTmp[ulSum++];

    /* ���벻ȷ���� */
    pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ucUncertaintyAltitude
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* ����CONFIDENCE */
    pstLocationEstimate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid.ucConfidence
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocArc
 Description     : ����λ����ϢARC��ʽ
 Input           : pucSrc                       :����
                   ulLen                        :Value����
 Output          : pstLocationEstimate          :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocArc
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* ���Ȳ���ȷ��ֱ�ӷ���ʧ�� */
    if (ulLen < 13)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_ARC, NAS_LCS_LEN_INVAILID, ulLen, 13);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocArc Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOIDARC_CHOSEN;

    /* ����shap type */
    ulSum++;

    /* ����γ�� */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidArc.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidArc.ulDegreesLatitude);
    ulSum += 3;

    /* ���뾭�� */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidArc.lDegreesLongtitude);
    ulSum += 3;

    /* ����INNER RADIUS */
    pstLocationEstimate->u.stEllipsoidArc.ulInnerRadius = (pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS);
    pstLocationEstimate->u.stEllipsoidArc.ulInnerRadius |= pucMsgTmp[ulSum++];

    /* ����UNCERTAINTY RADIUS */
    pstLocationEstimate->u.stEllipsoidArc.ucUncertaintyRadius = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    /* ����OFFSET ANGLE */
    pstLocationEstimate->u.stEllipsoidArc.ucOffsetAngle = pucMsgTmp[ulSum++];

    /* ����INCLUEDED ANGLE */
    pstLocationEstimate->u.stEllipsoidArc.ucIncludedAngle = pucMsgTmp[ulSum++];

    /* ����CONFIDENCE */
    pstLocationEstimate->u.stEllipsoidArc.ucConfidence
                                = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_LOW_7_BIT);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPointWithAltitude
 Description     : ����λ����ϢPOINT WITH ALTITUDE��ʽ
 Input           : pucSrc                       :����
                   ulLen                        :Value����
 Output          : pstLocationEstimate          :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPointWithAltitude
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;

    /* ���Ȳ���ȷ��ֱ�ӷ���ʧ�� */
    if (ulLen < 9)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_ALT, NAS_LCS_LEN_INVAILID, ulLen, 9);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPointWithAltitude Len Invalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_ELLIPSOID_POINT_WITH_ALTITUDE_CHOSEN;

    /* ����shap type */
    ulSum++;

    /* ����γ�� */
    NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitude.enLatitudeSign,
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitude.ulDegreesLatitude);
    ulSum += 3;

    /* ���뾭�� */
    NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitude.lDegreesLatitude);
    ulSum += 3;

    /* ����߶� */
    NAS_LCS_DecodeAltitude(     &pucMsgTmp[ulSum],
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitude.enAltitudeDirection,
                                &pstLocationEstimate->u.stEllipsoidPointWithAltitude.usAltitude);

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocPolygon
 Description     : ����λ����ϢPOLYGON��ʽ
 Input           : pucSrc                       :����
                   ulLen                        :Value����
 Output          : pstLocationEstimate          :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocPolygon
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;
    VOS_UINT8                           ucPointsNum     = 0;
    VOS_UINT32                          i               = 0;


    /* ȡ������� */
    ucPointsNum = (pucMsgTmp[ulSum] & NAS_LCS_MSG_LOW_BIT);

    if (0 == ucPointsNum)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_POLYGON, NAS_LCS_POINT_NUM_INVALID, ucPointsNum, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocPolygon Point Num Null ", ucPointsNum);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ���Ȳ���ȷ��ֱ�ӷ���ʧ�� */
    if (ulLen < (VOS_UINT32)((6 * ucPointsNum) + 1))
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LOC_POLYGON, NAS_LCS_LEN_INVAILID, ulLen, ((6 * ucPointsNum) + 1));
        NAS_LCS_INFO_LOG2(" NAS_LCS_DecodeLocPolygon Len Invalid ", ulLen, ((6 * ucPointsNum) + 1));
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstLocationEstimate,
                        sizeof(LOC_COM_COORDINATE_STRU),
                        0,
                        sizeof(LOC_COM_COORDINATE_STRU));

    pstLocationEstimate->ulChoice = LOC_COM_POLYGON_CHOSEN;

    /* ����shap type */
    ulSum++;

    pstLocationEstimate->u.stPolygon.ulPolygonCnt = ucPointsNum;
    for (i = 0; i < ucPointsNum; i++)
    {
        /* ����γ�� */
        NAS_LCS_DecodeLatitude(     &pucMsgTmp[ulSum],
                                    &pstLocationEstimate->u.stPolygon.astPolygonArray[i].enLatitudeSign,
                                    &pstLocationEstimate->u.stPolygon.astPolygonArray[i].ulDegreesLatitude);
        ulSum += 3;

        /* ���뾭�� */
        NAS_LCS_DecodeLongitude(    &pucMsgTmp[ulSum],
                                    &pstLocationEstimate->u.stPolygon.astPolygonArray[i].lDegreesLatitude);
        ulSum += 3;
    }

    return NAS_LCS_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocEstimate
 Description     : ������ԪlocationEstimate
 Input           : pucSrc                       :����
                   pulLen                       :Value����
 Output          : pulLen                       :�ѽ�������
                   pstLocationEstimate          :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT8                           ucShapeType     = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt          = NAS_LCS_CAUSE_SUCCESS;

    *pulLen = 0;

    /* �жϳ����Ƿ���1-20֮�� */
    if ((0 == ulUndecodeLen) || (NAS_LCS_LOC_ESTIMATE_MAX_LEN < ulUndecodeLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_LOC_ESTIMATE,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeLen,
                                    NAS_LCS_LOC_ESTIMATE_MAX_LEN);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocEstimate Undecode Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ȡ��SHAPE���� */
    ucShapeType = (pucMsgTmp[ulSum] & NAS_LCS_MSG_HIGH_BIT) >> NAS_LCS_MOVEMENT_4_BITS;

    switch (ucShapeType)
    {
        case NAS_LCS_LOC_SHAP_ELLIPSOID_POINT:
            enRslt = NAS_LCS_DecodeLocPoint(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        case NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE:
            enRslt = NAS_LCS_DecodeLocPointWithCircle(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        case NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE:
            enRslt = NAS_LCS_DecodeLocPointWithEllipse(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        case NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID:
            enRslt = NAS_LCS_DecodeLocPointWithAlititudeAndEllipsoid(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        case NAS_LCS_LOC_SHAP_ELLIPSOIDARC:
            enRslt = NAS_LCS_DecodeLocArc(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        default :
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_LOC_ESTIMATE,
                                        NAS_LCS_UNKNOWN_SHAPE_TYPE,
                                        ucShapeType,
                                        0);
            NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeLocEstimate Unknown Shape Type ", ucShapeType);
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* ����IE */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_LCS_DecodeAddLocEstimate
 Description     : ������ԪAdditionallocationEstimate
 Input           : pucSrc                       :����
                   pulLen                       :Value����
 Output          : pulLen                       :�ѽ�������
                   pstLocationEstimate          :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-13  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeAddLocEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    LOC_COM_COORDINATE_STRU             *pstLocationEstimate
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT8                           ucShapeType     = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pulLen = 0;

    /* �ж�Len�Ƿ���1-91֮�� */
    if ((0 == ulUndecodeLen) || (NAS_LCS_ADD_LOC_ESTIMATE_MAX_LEN < ulUndecodeLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_ADD_LOC_EST,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeLen,
                                    NAS_LCS_ADD_LOC_ESTIMATE_MAX_LEN);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeAddLocEstimate Undecode Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ȡ��SHAPE���� */
    ucShapeType = (pucMsgTmp[ulSum] & NAS_LCS_MSG_HIGH_BIT) >> NAS_LCS_MOVEMENT_4_BITS;

    switch (ucShapeType)
    {
        case NAS_LCS_LOC_SHAP_POLYGON:
            enRslt = NAS_LCS_DecodeLocPolygon(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        case NAS_LCS_LOC_SHAP_ELLIPSOID_POINT_WITH_ALTITUDE:
            enRslt = NAS_LCS_DecodeLocPointWithAltitude(pucMsgTmp, ulUndecodeLen, pstLocationEstimate);
            break;

        default :
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_ADD_LOC_EST,
                                        NAS_LCS_UNKNOWN_SHAPE_TYPE,
                                        ucShapeType, 0);
            NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeAddLocEstimate Unknown Shape Type ", ucShapeType);
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeHorizontalVelocity
 Description     : �����ٶ���ϢHORIZAONTAL VELOCITY��ʽ
 Input           : pucSrc                       :����
                   ulLen                        :Value����
 Output          : pstVelEstimate               :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-14  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeHorizontalVelocity
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_VELOCITY_STRU               *pstVelEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;

    /* ���Ȳ���ȷ��ֱ�ӷ���ʧ�� */
    if (ulLen < 4)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_HOR_VEL, NAS_LCS_LEN_INVAILID, ulLen, 4);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeHorizontalVelocity Len Ivalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstVelEstimate,
                        sizeof(LOC_COM_VELOCITY_STRU),
                        0,
                        sizeof(LOC_COM_VELOCITY_STRU));

    pstVelEstimate->ulChoice = LOC_COM_HORIZONTAL_VELCOCTIY_CHOSEN;

    /* ����BEARING */
    pstVelEstimate->u.stHorizontalVelocity.usBearing
                        = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_1_BIT) << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalVelocity.usBearing |= pucMsgTmp[ulSum++];

    /* ����horizontal speed */
    pstVelEstimate->u.stHorizontalVelocity.usHorizontalSpeed
                        = pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalVelocity.usHorizontalSpeed
                        |= pucMsgTmp[ulSum++];

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeHorizontalAndVerticalVelocity
 Description     : �����ٶ���ϢHORIZAONTAL AND VERTICAL VELOCITY��ʽ
 Input           : pucSrc                       :����
                   ulLen                        :Value����
 Output          : pstVelEstimate               :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-14  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeHorizontalAndVerticalVelocity
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_VELOCITY_STRU               *pstVelEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;

    /* ���Ȳ���ȷ��ֱ�ӷ���ʧ�� */
    if (ulLen < 5)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_HOR_VER_VEL,
                                    NAS_LCS_LEN_INVAILID,
                                    ulLen, 5);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeHorizontalAndVerticalVelocity Len Ivalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstVelEstimate,
                        sizeof(LOC_COM_VELOCITY_STRU),
                        0,
                        sizeof(LOC_COM_VELOCITY_STRU));

    pstVelEstimate->ulChoice = LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_CHOSEN;

    /* ���봹ֱ���� */
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.enVerticalDirection
                        = (pucMsgTmp[ulSum] & NAS_LCS_MSG_2_BIT) >> NAS_LCS_MOVEMENT_1_BITS;

    /* ����BEARING */
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.usBearing
                        = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_1_BIT) << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.usBearing |= pucMsgTmp[ulSum++];

    /* ����horizontal speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.usHorizontalSpeed
                        = pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.usHorizontalSpeed
                        |= pucMsgTmp[ulSum++];

    /* ����Vertical Speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocity.ulVerticalSpeed = pucMsgTmp[ulSum++];

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeHorizontalVelocityWithUncertainty
 Description     : �����ٶ���ϢHORIZAONTAL VELOCITY WITH UNCERTAINTY��ʽ
 Input           : pucSrc                       :����
                   ulLen                        :Value����
 Output          : pstVelEstimate               :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-14  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeHorizontalVelocityWithUncertainty
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_VELOCITY_STRU               *pstVelEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;

    /* ���Ȳ���ȷ��ֱ�ӷ���ʧ�� */
    if (ulLen < 5)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_HOR_VER_UNCERT, NAS_LCS_LEN_INVAILID, ulLen, 5);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeHorizontalVelocityWithUncertainty Len Ivalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstVelEstimate,
                        sizeof(LOC_COM_VELOCITY_STRU),
                        0,
                        sizeof(LOC_COM_VELOCITY_STRU));

    pstVelEstimate->ulChoice = LOC_COM_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_CHOSEN;

    /* ����BEARING */
    pstVelEstimate->u.stHorizontalVelocityWithUncertainty.usBearing
                        = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_1_BIT) << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalVelocityWithUncertainty.usBearing |= pucMsgTmp[ulSum++];

    /* ����horizontal speed */
    pstVelEstimate->u.stHorizontalVelocityWithUncertainty.usHorizontalSpeed
                        = pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalVelocityWithUncertainty.usHorizontalSpeed
                        |= pucMsgTmp[ulSum++];

    /* ����Uncertainty Speed */
    pstVelEstimate->u.stHorizontalVelocityWithUncertainty.ulUncertaintySpeed = pucMsgTmp[ulSum++];

    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeHorizontalAndVerticalVelocityWithUncertainty
 Description     : �����ٶ���ϢHORIZAONTAL AND VERTICAL VELOCITY WITH UNCERTAINTY��ʽ
 Input           : pucSrc                       :����
                   ulLen                        :Value����
 Output          : pstVelEstimate               :������ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.lihong 00150010    2015-10-14  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeHorizontalAndVerticalVelocityWithUncertainty
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                           ulLen,
    LOC_COM_VELOCITY_STRU               *pstVelEstimate
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;

    /* ���Ȳ���ȷ��ֱ�ӷ���ʧ�� */
    if (ulLen < 7)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_HOR_VER_VEL_UNCERT,
                                    NAS_LCS_LEN_INVAILID,
                                    ulLen, 7);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeHorizontalAndVerticalVelocityWithUncertainty Len Ivalid ", ulLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_SET_S(  pstVelEstimate,
                        sizeof(LOC_COM_VELOCITY_STRU),
                        0,
                        sizeof(LOC_COM_VELOCITY_STRU));

    pstVelEstimate->ulChoice = LOC_COM_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_CHOSEN;

    /* ���봹ֱ���� */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.enVerticalDirection
                        = (pucMsgTmp[ulSum] & NAS_LCS_MSG_2_BIT) >> NAS_LCS_MOVEMENT_1_BITS;

    /* ����BEARING */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.usBearing
                        = (pucMsgTmp[ulSum++] & NAS_LCS_MSG_1_BIT) << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.usBearing |= pucMsgTmp[ulSum++];

    /* ����horizontal speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.usHorizontalSpeed
                        = pucMsgTmp[ulSum++] << NAS_LCS_MOVEMENT_8_BITS;
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.usHorizontalSpeed
                        |= pucMsgTmp[ulSum++];

    /* ����Vertical Speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.ucVerticalSpeed = pucMsgTmp[ulSum++];

    /* ����Horizonal Uncertainty Speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.ucHorizontalUncertaintySpeed = pucMsgTmp[ulSum++];

    /* ����Vertical Uncertainty Speed */
    pstVelEstimate->u.stHorizontalWithVerticalVelocityAndUncertainty.ucVerticalUncertaintySpeed = pucMsgTmp[ulSum++];

    return NAS_LCS_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_LCS_DecodeVelEstimate
 Description     : ������ԪvelocityEstimate
 Input           : pucSrc                       :����
                   pstRepPlmnList               :������ṹ
                   pulLen                       :ʣ���������
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeVelEstimate
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    LOC_COM_VELOCITY_STRU               *pstVelEstimate
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT8                           ucVelocityType  = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    if ((NAS_LCS_VEL_ESTIMATE_MIN_LEN > ulUndecodeLen)
        || (NAS_LCS_VEL_ESTIMATE_MAX_LEN < ulUndecodeLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_VEL_ESTIMATE,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeVelEstimate Len Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ȡ���ٶ����� */
    ucVelocityType = (pucMsgTmp[ulSum] & NAS_LCS_MSG_HIGH_BIT) >> NAS_LCS_MOVEMENT_4_BITS;

    switch (ucVelocityType)
    {
        case NAS_LCS_VELOCITY_TYPE_HORIZONTAL_VELOCITY:
            enRslt = NAS_LCS_DecodeHorizontalVelocity(pucMsgTmp, ulUndecodeLen, pstVelEstimate);
            break;

        case NAS_LCS_VELOCITY_TYPE_HORIZONTAL_WITH_VERTICAL_VELOCITY:
            enRslt = NAS_LCS_DecodeHorizontalAndVerticalVelocity(pucMsgTmp, ulUndecodeLen, pstVelEstimate);
            break;

        case NAS_LCS_VELOCITY_TYPE_HORIZONTAL_VELOCITY_WITH_UNCERTAINTY:
            enRslt = NAS_LCS_DecodeHorizontalVelocityWithUncertainty(pucMsgTmp, ulUndecodeLen, pstVelEstimate);
            break;

        case NAS_LCS_VELOCITY_TYPE_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY:
            enRslt = NAS_LCS_DecodeHorizontalAndVerticalVelocityWithUncertainty(pucMsgTmp, ulUndecodeLen, pstVelEstimate);
            break;

        default :
            NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_VEL_ESTIMATE, NAS_LCS_UNKNOWN_VEL_TYPE, ucVelocityType, 0);
            NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeVelEstimate Unknown VelocityType ", ucVelocityType);
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeHGmlcAddr
 Description     : ������Ԫh-gmlc-address
 Input           : pucSrc                       :����
                   pstRepPlmnList               :������ṹ
                   pulLen                       :ʣ���������
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeHGmlcAddr
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_HGMLC_ADDR_STRU             *pstHGmlcAddr
)
{
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    *pulLen = 0;

    /* �ж�Len�Ƿ���5-17֮�� */
    if ((NAS_LCS_HGMALC_ADD_MIN_LEN > ulUndecodeLen)
        || (NAS_LCS_HGMALC_ADD_MAX_LEN < ulUndecodeLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_HGMLC_ADDR,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeHGmlcAddr Len Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ����Hgmlc */
    NAS_LCS_MEM_CPY_S(  pstHGmlcAddr->aucHGmlcAddr,
                        NAS_LCS_HGMALC_ADD_MAX_LEN,
                        pucMsgTmp,
                        ulUndecodeLen);

    pstHGmlcAddr->ucLen = (VOS_UINT8)ulUndecodeLen;

    *pulLen = ulUndecodeLen;
    return NAS_LCS_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeReportPlmnList
 Description     : ������ԪreportingPLMNList
 Input           : pucSrc                       :����
                   pstRepPlmnList               :������ṹ
                   pulLen                       :ʣ���������
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeReportPlmnList
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_REPORT_PLMN_LIST_STRU       *pstRepPlmnList
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulValueLen      = 0;

    ulTmpLen = ulUndecodeLen;

    /* ������ѡ��Ԫplmn-ListPrioritized */
    /* ����TAG��LEN */
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        ulSum   = ulSum + ulUndecodeLen;
        *pulLen = ulSum;
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_REP_PLMN_LIST,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeReportPlmnList Len Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    if (0 == stTagStru.ulNumber)
    {
        /* ����TAG��LEN */
        ulSum         = ulSum + ulTmpLen;

        /* ����ʣ���������� */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* �жϳ����Ƿ�Ϸ� */
        if (0 == ulValueLen)
        {
            pstRepPlmnList->bitOpPlmnPriority = NAS_LCS_OP_TRUE;
        }

        /* ����Value���� */
        ulSum         = ulSum + ulValueLen;
        ulUndecodeLen = ulUndecodeLen - ulValueLen;
    }

    /* ��ȡʣ���������� */
    ulTmpLen = ulUndecodeLen;

    /* ������ѡ��Ԫplmn-list */
    enRslt   = NAS_LCS_DecodePlmnList(pucMsgTmp + ulSum, &ulTmpLen, &pstRepPlmnList->stPlmnList);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* ����plmn-list */
    ulSum = ulSum + ulTmpLen;
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return enRslt;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodePlmnList
 Description     : ������Ԫplmn-list
 Input           : pucSrc                       :����
                   pstPlmnList                  :������ṹ
                   pulLen                       :ʣ���������
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodePlmnList
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_PLMN_LIST_STRU              *pstPlmnList
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulValueLen      = 0;
    VOS_UINT8                           ucIndex         = 0;

    *pulLen = 0;

    /* ����TAG��LEN */
    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_REP_PLMN_LIST,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeReportPlmnList Len Ivalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��LEN */
    ulSum         = ulSum + ulTmpLen;

    /* ��ȡʵ��IEʣ���������� */
    ulUndecodeLen = ulValueLen;

    /* �ж�TAG�Ƿ���ȷ */
    if (1 != stTagStru.ulNumber)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_REP_PLMN_LIST,
                                    NAS_LCS_MISS_MANDATORY_IE,
                                    stTagStru.ulNumber, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeReportPlmnList decode Plmn-list fail ", ulUndecodeLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ѭ������PLMN��Ϣ */
    while(0 != ulUndecodeLen)
    {
        /* ����������Sequence TL */
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_PLMN_LIST,
                                        NAS_LCS_LEN_DECODE_FAIL,
                                        ulUndecodeLen,
                                        0);
            return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
        }

        /* ����TAG��LEN */
        ulSum = ulSum + ulTmpLen;

        /* ����ʣ���������� */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /*��ȡ����ԪValue����*/
        ulTmpLen = ulValueLen;

        /* ����PLMN */
        ucIndex = pstPlmnList->ucPlmnNum;
        enRslt = NAS_LCS_DecodePlmn(    pucMsgTmp + ulSum,
                                        &ulTmpLen,
                                        &pstPlmnList->astPlmn[ucIndex]);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            *pulLen = ulSum + ulUndecodeLen;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* PLMN������1 */
        pstPlmnList->ucPlmnNum++;

        /* ����Value���� */
        ulSum = ulSum + ulValueLen;

        /* ����ʣ���������� */
        ulUndecodeLen = ulUndecodeLen - ulValueLen;

        /* ���֧��Я��20��PLMN��Ϣ */
        if (NAS_LCS_REP_PLMN_MAX_NUM <= pstPlmnList->ucPlmnNum)
        {
            /* ����ʣ��δ������������ */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }
    }

    /* ����ʣ��δ������������ */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodePlmn
 Description     : ������Ԫplmn
 Input           : pucSrc                       :����
                   pstPlmn                      :������ṹ
                   pulLen                       :ʣ���������
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodePlmn
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_PLMN_STRU                   *pstPlmn
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulValueLen      = 0;
    VOS_UINT32                          ulLoop          = 0;

    *pulLen = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_PLMN, NAS_LCS_UNDECODE_LEN_INVAlID,
                                    0, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodePlmn Undecode Len Invalid ", ulUndecodeLen);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��LEN */
    ulSum = ulSum + ulTmpLen;

    /* ����ʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* ������ѡ��Ԫplmn-id */
    if ((0 == stTagStru.ulNumber) && (3 == ulValueLen))
    {
        pstPlmn->stPlmnId.aucPlmnId[0] = pucMsgTmp[ulSum];
        ulSum++;
        pstPlmn->stPlmnId.aucPlmnId[1] = pucMsgTmp[ulSum];
        ulSum++;
        pstPlmn->stPlmnId.aucPlmnId[2] = pucMsgTmp[ulSum];
        ulSum++;
        ulUndecodeLen = ulUndecodeLen - ulValueLen;
    }
    else
    {
        ulSum = ulSum + ulUndecodeLen;
        *pulLen = ulSum;
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_PLMN, NAS_LCS_MISS_PLMN_ID, 0, 0);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodePlmn Miss Plmn Id ", stTagStru.ulNumber);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ������ѡ��Ԫ */
    while ((0 < ulUndecodeLen) && (ulLoop < NAS_LCS_PLMN_OP_IE_MAX_NUM))
    {
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ����TAG��LEN */
        ulSum = ulSum + ulTmpLen;

        /* ����ʣ���������� */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* ����TAGֵ������ѡ��Ԫ */
        switch(stTagStru.ulNumber)
        {
            /* ����ran-Technology */
            case 1:
                pstPlmn->enRanTech = pucMsgTmp[ulSum];
                pstPlmn->bitOpRanTech = NAS_LCS_OP_TRUE;
                break;

            /* ����ran-PerodicLocationSupport */
            case 2:
                if (0 == ulValueLen)
                {
                    pstPlmn->bitOpRanPerLocSupp = NAS_LCS_OP_TRUE;
                }
                break;

            default:
                /* ����ʣ������ */
                ulSum = ulSum + ulUndecodeLen;
                *pulLen = ulSum;
                return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ��ѡ��Ԫ����Value����, ���ÿ��ǽ������ */
        ulSum         = ulSum + ulValueLen;
        ulUndecodeLen = ulUndecodeLen - ulValueLen;

        /* ѭ��������1, ���ѭ������Ϊ��ѡ��Ԫ���� */
        ulLoop++;
    }

    /* ����ʣ��δ�������� */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeErrorCode
 Description     : ����Error code
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulDecodeMsgLen              :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeErrorCode
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    VOS_UINT32                          ulValueLen      = 0;
    NAS_LCS_TAG_STRU                    stTagStru;

    /* �ж�ERROR CODE TAG�Ƿ���ȷ */
    if ((0 == ulUndecodeLen) || (NAS_LCS_ERROR_CODE_TAG != pucMsgTmp[ulSum]))
    {
        *pulLen = ulUndecodeLen;
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_ERROR_CODE,
                                    NAS_LCS_TAG_ERROR,
                                    pucMsgTmp[ulSum],
                                    NAS_LCS_ERROR_CODE_TAG);
        NAS_LCS_INFO_LOG1(" NAS_LCS_DecodeRtrnErr Error code Tag Invalid ", pucMsgTmp[ulSum]);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ��ȡError Code����, TLV��ʽ */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        *pulLen = ulUndecodeLen;
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_ERROR_CODE,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��Len */
    ulSum = ulSum + ulTmpLen;

    /* TAG��ERROR CODE��ϳ�����ԭ��ֵ */
    pstCnMsgStru->enNwCause = (NAS_LCS_ERROR_CODE_TAG << NAS_LCS_MOVEMENT_8_BITS) + pucMsgTmp[ulSum];
    pstCnMsgStru->bitOpNwCause = NAS_LCS_OP_TRUE;

    /* ����Value */
    ulSum = ulSum + ulValueLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRtrnErr
 Description     : ����Retrun Error Component
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulDecodeMsgLen              :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRtrnErr
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    VOS_UINT32                          ulValueLen      = 0;
    NAS_LCS_TAG_STRU                    stTagStru;

    *pulLen = 0;

    /*��ȡcomponent����, TLV��ʽ��ͬʱָ����λ��V��ȷ������λ��*/
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��Len */
    ulSum         = ulSum + ulTmpLen;

    /* ��ȡʣ�����Ԫ��������, ����Ԫ��Я����LΪ׼ */
    ulUndecodeLen = ulValueLen;
    ulTmpLen      = ulUndecodeLen;

    /* ����INVOKE ID */
    enRslt  = NAS_LCS_DecodeInvokeId(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /*ȱ��Invoke Id,������Ϣ�������*/
        return enRslt;
    }

    /* ����INVOKE ID */
    ulSum = ulSum + ulTmpLen;

    /* ����ʣ����Ԫ���� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* ����Error Code */
    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeErrorCode(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /*ȱ��Error Code,������Ϣ�������*/
        return enRslt;
    }

    /* ����Error Code */
    ulSum = ulSum + ulTmpLen;

    /* ������Ԫʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* ����ʣ��δ�������� */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodePromblemCode
 Description     : ����Promblem Code
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodePromblemCode
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    VOS_UINT32                          ulValueLen      = 0;
    NAS_LCS_PROBLEM_TAG_ENUM_UINT8      enProblemTag;
    NAS_LCS_TAG_STRU                    stTagStru;

    /* ����Problem Code */
    /* ���Problem TAGֵ�Ƿ�Ϸ� */
    if ((0 == ulUndecodeLen) || (NAS_LCS_CAUSE_SUCCESS != NAS_LCS_CheckProblemTagVaild(pucMsgTmp[ulSum])))
    {
        /* ����ʣ������ */
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_PROBLEM_CODE,
                                    NAS_LCS_TAG_ERROR,
                                    pucMsgTmp[ulSum], 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ��ȡProblemTag */
    enProblemTag = pucMsgTmp[ulSum];

    ulTmpLen     = ulUndecodeLen;

    /* ��ȡProblem Code����, TLV��ʽ */
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /* ����ʣ������ */
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_PROBLEM_CODE, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��Len */
    ulSum = ulSum + ulTmpLen;

    /* TAG��ERROR CODE��ϳ�����ԭ��ֵ */
    pstCnMsgStru->enNwCause = (enProblemTag << NAS_LCS_MOVEMENT_8_BITS) + pucMsgTmp[ulSum];
    pstCnMsgStru->bitOpNwCause = NAS_LCS_OP_TRUE;

    /* ����Problem IE Value */
    ulSum   = ulSum + ulValueLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeReject
 Description     : ����Rej Component
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeReject
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    VOS_UINT32                          ulValueLen      = 0;
    NAS_LCS_TAG_STRU                    stTagStru;

    ulTmpLen = ulUndecodeLen;

    *pulLen = 0;

    /*��ȡcomponent����, TLV��ʽ��ͬʱָ����λ��V��ȷ������λ��*/
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_COMPONENT, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_DecodeReject Len decode Fail ");
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��Len */
    ulSum         = ulSum + ulTmpLen;

    /* ��ȡComponent IEʣ����������*/
    ulUndecodeLen = ulValueLen;
    ulTmpLen      = ulUndecodeLen;

    /* ������ѡ��ԪINVOKE ID */
    enRslt  = NAS_LCS_DecodeInvokeId(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /*ȱ��Invoke Id,������Ϣ�������*/
        return enRslt;
    }

    /* ����INVOKE ID */
    ulSum         = ulSum + ulTmpLen;

    /* ����ʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* ������ѡProblem Code */
    enRslt = NAS_LCS_DecodePromblemCode(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* ����Problem Code */
    ulSum         = ulSum + ulTmpLen;

    /* ����ʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* ����ʣ������ */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeInvoke
 Description     : ����Invoke Component
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeInvoke
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                           ucOperationCode;
    VOS_UINT32                          enRslt          = NAS_LCS_CAUSE_SUCCESS;
    VOS_UINT32                          ulValueLen         = 0;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_TAG_STRU                    stTagStru;

    *pulLen = 0;

    ulTmpLen = ulUndecodeLen;

    /* ��ȡcomponent����, TLV��ʽ */
    enRslt = NAS_LCS_DecodeTL(pucMsgTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_COMPONENT, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��Len */
    ulSum         = ulSum + ulTmpLen;

    /* ��ȡʣ����������, ��Component��Ԫ��LΪ׼ */
    ulUndecodeLen = ulValueLen;
    ulTmpLen      = ulUndecodeLen;

    /* ����INVOKE ID */
    enRslt  = NAS_LCS_DecodeInvokeId(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        /* ȱ��Invoke Id,������Ϣ������� */
        return enRslt;
    }

    /* ����INVOKE ID */
    ulSum = ulSum + ulTmpLen;

    /* ����ʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* ����LINKED ID */
    enRslt = NAS_LCS_DecodeLinkedId(pucMsgTmp + ulSum, &ulTmpLen, pstCnMsgStru);
    if (NAS_LCS_CAUSE_SUCCESS == enRslt)
    {
        /* ����LINKED ID */
        ulSum = ulSum + ulTmpLen;
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;
        pstCnMsgStru->bitOpLinkedId = NAS_LCS_OP_TRUE;
    }

    /* ����Operation Code */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeOperationCode(   pucMsgTmp + ulSum,
                                            &ulTmpLen,
                                            pstCnMsgStru,
                                            &ucOperationCode);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����Opertion Code */
    ulSum         = ulSum + ulTmpLen;

    /* ��ȡʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /*���ݲ����룬�����component����������Ӧ�Ľ��봦��*/
    if (0 < ulUndecodeLen)
    {
        ulTmpLen      = ulUndecodeLen;
        switch(ucOperationCode)
        {
            /* ����Loc Notification Parameters */
            case NAS_LCS_OPERATION_LOC_NOTIFICATION:
                enRslt = NAS_LCS_DecodeLocNotification( pucMsgTmp + ulSum,
                                                        &ulTmpLen,
                                                        &pstCnMsgStru->stLocNotication);
                if (NAS_LCS_CAUSE_SUCCESS != enRslt)
                {
                    return enRslt;
                }

                pstCnMsgStru->bitOpLocNotification = NAS_LCS_OP_TRUE;
                break;

            /* ��ǰLCS��֧��Operation, �׳���ά�ɲ�, �����ظ�Rel Cmp */
            default:
                ulSum   = ulSum + ulUndecodeLen;
                *pulLen = ulSum;
                NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_COMPONENT,
                                            NAS_LCS_OPERA_INVALID,
                                            ucOperationCode, 0);
                return NAS_LCS_CAUSE_SUCCESS;
        }

        ulSum = ulSum + ulTmpLen;
    }

    *pulLen = ulSum;
    return enRslt;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeInvokeId
 Description     : ����Invoke Id
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulDecodeMsgLen              :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeInvokeId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    /* ���ʣ���������Ⱥ�TAG�Ƿ���ȷ */
    if ((3 <= ulUndecodeLen) && (NAS_LCS_INVOKE_ID_TAG == pucMsgTmp[ulSum]))
    {
        /* ����TAG */
        ulSum++;

        /* ����Len */
        ulSum++;

        /* ����Invoke id */
        pstCnMsgStru->ucInvokeId = pucMsgTmp[ulSum++];
        pstCnMsgStru->bitOpInvokeId = NAS_LCS_OP_TRUE;
    }
    else
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_INVOKE,
                                    NAS_LCS_MISS_INVOKE_ID,
                                    pucMsgTmp[ulSum],
                                    NAS_LCS_INVOKE_ID_TAG);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLinkedId
 Description     : ����Linked Id
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLinkedId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    *pulLen = 0;

    if ((3 <= ulUndecodeLen) && (NAS_LCS_LINKED_ID_TAG == pucMsgTmp[ulSum]))
    {
        /* ����Tag */
        ulSum++;

        /* ����Len */
        ulSum++;

        /* ����Linked Id */
        pstCnMsgStru->bitOpLinkedId = NAS_LCS_OP_TRUE;
        pstCnMsgStru->ucLinkedId    = pucMsgTmp[ulSum];

        /* ����Linked Id */
        ulSum++;
    }
    else
    {
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeOperationCode
 Description     : ����Operation Code
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulDecodeMsgLen              :�ѽ�������
                   pucOperationCode             :Operation Code
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeOperationCode
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CN_MSG_STRU                 *pstCnMsgStru,
    VOS_UINT8                           *pucOperationCode
)
{
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT8                          *pucMsgTmp       = pucSrc;
    VOS_UINT8                           ucOperationCode;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    *pulLen = 0;

    /* ���ʣ�������Ƿ����OPeration Code IE���� */
    if (3 > ulUndecodeLen)
    {
        /*ȱ��operation code��������Ϣ�������*/
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    if (NAS_LCS_OPERATION_CODE_TAG == pucMsgTmp[ulSum])
    {
        /* ����Operation Code Tag */
        ulSum++;

        /* ����Len */
        ulSum++;

        /*��ȡ������*/
        ucOperationCode = pucMsgTmp[ulSum++];

        /*������Operation�Ƿ�ǰLCS֧��, ����֧���׳���ά�ɲ�, ����㴦��ظ�Rel Cmp*/
        if (NAS_LCS_CAUSE_SUCCESS != NAS_LCS_CheckOperationCode(ucOperationCode))
        {
            NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_OPERA_CODE,
                                        NAS_LCS_OPERA_INVALID,
                                        ucOperationCode, 0);

        }

        /* ��¼operationcode */
        pstCnMsgStru->bitOperationCode = NAS_LCS_OP_TRUE;
        pstCnMsgStru->ucOperationCode  = ucOperationCode;
        *pucOperationCode              = ucOperationCode;
    }
    else
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_OPERA_CODE,
                                    NAS_LCS_TAG_ERROR,
                                    pucMsgTmp[ulSum],
                                    NAS_LCS_OPERATION_CODE_TAG);

        /*ȱ��operation code��������Ϣ�������*/
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocNotification
 Description     : ����Operation Lcs-LocationNotification ��Ӧpara
 Input           : pucSrc                       :����
                   pstCnMsgStru                 :������ṹ
 Output          : pulDecodeMsgLen              :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocNotification
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_LOC_NOTFICATION_STRU        *pstLocNtfStru
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen = 0;
    ulTmpLen = ulUndecodeLen;

    /* ����TAG��LEN */
    enRslt = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_NTF, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��LEN */
    ulSum = ulSum + ulTmpLen;

    /* ��ȡʣ�೤��,��ʵ����Ԫ��LENΪ׼ */
    ulUndecodeLen = ulValueLen;
    ulTmpLen      = ulUndecodeLen;

    /* ����notificationType */
    enRslt = NAS_LCS_DecodeNotificationType(    pucSrcTmp + ulSum,
                                                &ulTmpLen,
                                                &pstLocNtfStru->enNtfType);

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* ����notificationType */
    ulSum = ulSum + ulTmpLen;

    /* ����ʣ�೤�� */
    ulUndecodeLen   = ulUndecodeLen - ulTmpLen;
    ulTmpLen        = ulUndecodeLen;

    /* ����locationtype */
    enRslt = NAS_LCS_DecodeLocationType(    pucSrcTmp + ulSum,
                                            &ulTmpLen,
                                            &pstLocNtfStru->stLocationType);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* ����notificationType */
    ulSum = ulSum + ulTmpLen;

    /* ����ʣ��Value���� */
    ulUndecodeLen  = ulUndecodeLen - ulTmpLen;
    ulTmpLen       = ulUndecodeLen;

    /* ����Notifcation�еĿ�ѡ��Ԫ */
    (VOS_VOID)NAS_LCS_DecodeNotificationOpIe(pucSrcTmp + ulSum, &ulTmpLen, pstLocNtfStru);

    /* ����ʣ�೤�� */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeNotificationOpIe
 Description     : ����Loc Notification��ѡ��Ԫ
 Input           : pucSrc                       :����
                   pstLocNtfStru                :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeNotificationOpIe
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_LOC_NOTFICATION_STRU        *pstLocNtfStru
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;
    VOS_UINT32                          ulLoop                  = 0;

    *pulLen = 0;

    while ((0 != ulUndecodeLen) && (ulLoop < NAS_LCS_LOC_NTF_OP_IE_MAX_NUM))
    {
        ulTmpLen = ulUndecodeLen;

        /* ����TAG��LEN */
        enRslt = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if ((NAS_LCS_CAUSE_SUCCESS != enRslt))
        {
            /* ��ѡ��ԪTL����ʧ��, ֱ�ӷ���, ����ʣ�೤�� */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ����TAG��LEN */
        ulSum         = ulSum + ulTmpLen;

        /* ����ʣ���������� */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* ��ȡ��ԪValue���� */
        ulTmpLen      = ulValueLen;

        switch (stTagStru.ulNumber)
        {
            case 2:
                enRslt = NAS_LCS_DecodeCilentExtId( pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstLocNtfStru->stClientExternalId);
                if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                {
                    /* �ÿ�ѡ��Ԫ�����ӿ�ѡ��Ԫ��� */
                    pstLocNtfStru->bitOpClientExternalId = pstLocNtfStru->stClientExternalId.bitOpExternalAddr;
                }
                break;

            case 3:
                enRslt = NAS_LCS_DecodeClientName(  pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstLocNtfStru->stClientName);
                if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                {
                    /* ����Ԫ������Ԫ���б�ѡ��Ԫ, ����ɹ�, Bitλ���� */
                    pstLocNtfStru->bitOpClientName = NAS_LCS_OP_TRUE;
                }
                break;

            case 4:
                enRslt = NAS_LCS_DecodeRequestorID( pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstLocNtfStru->stRequestorId);
                if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                {
                    pstLocNtfStru->bitOpRequestorId = NAS_LCS_OP_TRUE;
                }
                break;

            case 5:
                enRslt = NAS_LCS_DecodeCodeWord(    pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstLocNtfStru->stCodeWord);
                if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                {
                    pstLocNtfStru->bitOpCodeWord = NAS_LCS_OP_TRUE;
                }
                break;

            case 6:
                enRslt = NAS_LCS_DecodeServiceTypeId(   pucSrcTmp + ulSum,
                                                        &ulTmpLen,
                                                        &pstLocNtfStru->ucServiceTypeId);
                if (NAS_LCS_CAUSE_SUCCESS == enRslt)
                {
                    pstLocNtfStru->bitOpServiceTypeId = NAS_LCS_OP_TRUE;
                }
                break;

            default:
                ulSum   = ulSum + ulUndecodeLen;
                *pulLen = ulSum;
                return NAS_LCS_CAUSE_SUCCESS;
        }

        ulSum          = ulSum + ulValueLen;
        ulUndecodeLen  = ulUndecodeLen - ulValueLen;

        /* ѭ�����������ۼ� */
        ulLoop++;
    }

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeNotificationOpIe
 Description     : ����Requestor ID��Ԫ�еı�ѡ��ԪDataCodingScheme
 Input           : pucSrc                       :����
                   pstRequestorId               :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeReqIdDataCodingScheme
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_REQUESTOR_ID_STRU           *pstRequestorId
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_REQUESTOR_ID,
                                    NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��LEN */
    ulSum         = ulSum + ulTmpLen;

    /* ��ȡ����Ԫʣ���������� */
    ulUndecodeLen = ulValueLen;

    /* ����dataCodingScheme */
    if (0 == stTagStru.ulNumber)
    {
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeDataCodingScheme(    pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstRequestorId->ucDataCodeScheme);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return enRslt;
        }

        /* ����dataCodingScheme */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;
        ulSum         = ulSum + ulTmpLen;
    }
    else
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_DATA_CODE_SHM,
                                    NAS_LCS_TAG_ERROR,
                                    stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ������IEʣ������ */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRequestorID
 Description     : ����Requestor ID��Ԫ
 Input           : pucSrc                       :����
                   pstRequestorId               :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRequestorID
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_REQUESTOR_ID_STRU           *pstRequestorId
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen = 0;

    /* ������ѡdataCodingScheme */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeReqIdDataCodingScheme(pucSrcTmp + ulSum, &ulTmpLen, pstRequestorId);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* ����dataCodingScheme */
    ulSum         = ulSum + ulTmpLen;

    /* ��ȡ��IEʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* ����RequestorIDString */
    ulTmpLen      = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeRequestorIDString(pucSrcTmp + ulSum, &ulTmpLen, &pstRequestorId->stReqString);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* ����RequestorIDString */
    ulSum         = ulSum + ulTmpLen;

    /* ��ȡ��IEʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* �ж��Ƿ��п�ѡ��Ԫ */
    if (0 < ulUndecodeLen)
    {
        ulTmpLen = ulUndecodeLen;
        enRslt   = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* ��ѡ��Ԫ����ʣ�೤�� */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ����TAG��LEN */
        ulSum         = ulSum + ulTmpLen;

        /* ����ʣ���������� */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* ��ȡ��ѡ��ԪValue���� */
        ulTmpLen      = ulValueLen;

        /* ������ѡ��Ԫlcs-FormatIndicator */
        if (2 == stTagStru.ulNumber)
        {
            ulTmpLen = ulValueLen;
            enRslt = NAS_LCS_DecodeFormatIndicator( pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstRequestorId->enLcsFormat);
            if (NAS_LCS_CAUSE_SUCCESS == enRslt)
            {
                pstRequestorId->bitOpLcsFormat = NAS_LCS_OP_TRUE;
            }
        }
        /* ������ѡ��ԪValue���� */
        ulSum           = ulSum + ulValueLen;

        /* ����ʣ���������� */
        ulUndecodeLen   = ulUndecodeLen - ulValueLen;
    }

    /* ��������Ԫʣ��δ�������� */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeRequestorIDString
 Description     : ����RequestorIDString��Ԫ
 Input           : pucSrc                       :����
                   pstReqString                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeRequestorIDString
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_REQUESTOR_ID_STRING_STRU    *pstReqString
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    *pulLen = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_REQ_ID_STRING,
                                    NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TL */
    ulSum = ulSum + ulTmpLen;

    /* ��ȡ����Ԫʣ���������� */
    ulUndecodeLen = ulValueLen;

    /* �ж�TAG�Ƿ���ȷ */
    if (1 != stTagStru.ulNumber)
    {
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ��鳤���Ƿ�Ϸ� */
    if ((NAS_LCS_REQUESTOR_ID_STRING_MAX_LEN < ulValueLen) || (0 == ulValueLen))
    {
        ulSum  = ulUndecodeLen;
        *pulLen = ulSum;
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_REQ_ID_STRING,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen,
                                    ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ���� */
    pstReqString->ucLen = (VOS_UINT8)ulValueLen;

    NAS_LCS_MEM_CPY_S(  pstReqString->aucReqIdString,
                        NAS_LCS_REQUESTOR_ID_STRING_MAX_LEN,
                        (pucSrcTmp + ulSum),
                        ulValueLen);

    /* ����Value */
    ulSum = ulSum + ulValueLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCodeWordDataCodingScheme
 Description     : ����lcs Code Word��Ԫ�еı�ѡ��ԪDataCodingScheme
 Input           : pucSrc                       :����
                   pstCodeWord                  :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCodeWordDataCodingScheme
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CODE_WORD_STRU              *pstCodeWord
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen  = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_CODE_WORD, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��LEN */
    ulSum           = ulSum + ulTmpLen;

    /* ��ȡ��Ԫʣ���������� */
    ulUndecodeLen   = ulValueLen;

    /* ����dataCodingScheme */
    if (0 == stTagStru.ulNumber)
    {
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeDataCodingScheme(    (pucSrcTmp + ulSum),
                                                    &ulTmpLen,
                                                    &pstCodeWord->ucDataCodeScheme);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return enRslt;
        }

        /* ����dataCodingScheme */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;
        ulSum         = ulSum + ulTmpLen;
    }
    else
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_DATA_CODE_SHM,
                                    NAS_LCS_TAG_ERROR,
                                    stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ��������Ԫʣ���������� */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCodeWord
 Description     : ����lcs Code Word��Ԫ
 Input           : pucSrc                       :����
                   pstCodeWord                  :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCodeWord
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CODE_WORD_STRU              *pstCodeWord
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulSum                   = 0;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen = 0;

    /* ������ѡ��ԪdataCodingScheme */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeCodeWordDataCodingScheme(pucSrcTmp + ulSum, &ulTmpLen, pstCodeWord);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* ����dataCodingScheme */
    ulSum = ulSum + ulTmpLen;

    /* �������Ԫʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* ������ѡ��ԪCode Word String */
    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeCodeWordString(pucSrcTmp + ulSum, &ulTmpLen, &pstCodeWord->stCodeWord);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* ����CodeWordString */
    ulSum = ulSum + ulTmpLen;

    /* �������Ԫʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* ����ʣ��δ�������� */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCodeWordString
 Description     : ����lcs Code Word String��Ԫ
 Input           : pucSrc                       :����
                   pstCodeWord                  :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCodeWordString
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CODE_WORD_STRING_STRU       *pstCodeWord
)
{
    VOS_UINT32                          ulTmpLen                = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen              = 0;
    VOS_UINT32                          ulSum                   = 0;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_CODE_WORD_STRING,
                                    NAS_LCS_LEN_DECODE_FAIL,
                                    0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TL */
    ulSum = ulSum + ulTmpLen;

    /* �ж�TAG�Ƿ���ȷ */
    if (1 != stTagStru.ulNumber)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_CODE_WORD_STRING,
                                    NAS_LCS_TAG_ERROR,
                                    stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* �жϳ����Ƿ�Ϸ� */
    if ((NAS_LCS_CODE_WORD_STRING_MAX_LEN < ulValueLen) || (0 == ulValueLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_CODE_WORD_STRING,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen,
                                    ulUndecodeLen);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ����Code Word */
    pstCodeWord->ucLen = (VOS_UINT8)ulValueLen;

    NAS_LCS_MEM_CPY_S(  pstCodeWord->aucCodeWord,
                        NAS_LCS_CODE_WORD_STRING_MAX_LEN,
                        (pucSrcTmp + ulSum),
                        ulValueLen);

    /* ����Code Word */
    ulSum = ulSum + ulValueLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeServiceTypeId
 Description     : ����Service Type Id��Ԫ
 Input           : pucSrc                       :����
                   pucServiceTypeId             :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeServiceTypeId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucServiceTypeId
)
{
    VOS_UINT32                          ulSum                   = 0;
    VOS_UINT8                          *pucSrcTmp               = pucSrc;
    VOS_UINT32                          ulUndecodeLen           = *pulLen;

    *pulLen = 0;

    /* ���LEN */
    if (1 != ulUndecodeLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_SER_TYPE_ID,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen, 0);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    *pucServiceTypeId = pucSrcTmp[ulSum];

    /* �ж�ServiceTypeId�Ƿ�С��127 */
    if (NAS_LCS_MAX_SERVICE_TYPE_ID < *pucServiceTypeId)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_SER_TYPE_ID,
                                    NAS_LCS_VALUE_IVALID,
                                    *pucServiceTypeId,
                                    NAS_LCS_MAX_SERVICE_TYPE_ID);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    ulSum++;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeCilentExtId
 Description     : ����CilentExternalId��Ԫ
 Input           : pucSrc                       :����
                   pstClientExternalId          :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeCilentExtId
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_EXTERNAL_ID_STRU     *pstClientExternalId
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;
    VOS_UINT32                          ulLoop          = 0;

    /* �ж��Ƿ��п�ѡ��Ԫ */
    if (0 == ulUndecodeLen)
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    /* ������ѡ��Ԫ */
    while ((0 != ulUndecodeLen) && (ulLoop < NAS_LCS_CLIENT_EXT_ID_OP_MAX_NUM))
    {
        ulTmpLen = ulUndecodeLen;
        enRslt   = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* ��ѡ��ԪTL����ʧ������ʣ���������� */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_EXT_CLIENT_ID, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ����TAG��LEN */
        ulSum              = ulSum + ulTmpLen;

        /* ����ʣ���������� */
        ulUndecodeLen      = ulUndecodeLen - ulTmpLen;

        /* ��ȡ��ѡ��ԪValue Len */
        ulTmpLen           = ulValueLen;
        switch (stTagStru.ulNumber)
        {
            /* ����externalAddress */
            case 0:
                (VOS_VOID)NAS_LCS_DecodeExternalAddr(   pucSrcTmp + ulSum,
                                                        &ulTmpLen,
                                                        pstClientExternalId);
                break;

            /* ����externsionContainer */
            case 1:
                (VOS_VOID)NAS_LCS_DecodeExtensionContainer( pucSrcTmp + ulSum,
                                                            &ulTmpLen,
                                                            pstClientExternalId);
                break;

            default:
                ulSum              = ulSum + ulUndecodeLen;
                *pulLen            = ulSum;
                NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_EXT_CLIENT_ID,
                                            NAS_LCS_TAG_ERROR,
                                            stTagStru.ulNumber, 0);
                return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ������ѡ��ԪValue����, ���ÿ��ǿ�ѡ��Ԫ */
        ulSum         = ulSum + ulValueLen;

        /*�������Ԫʣ����������*/
        ulUndecodeLen = ulUndecodeLen - ulValueLen;

        /* ���������ۼ�, ѭ���������ܴ��ڿ�ѡ��Ԫ���� */
        ulLoop++;
    }

    /* ��������Ԫʣ��δ������������ */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeExternalAddr
 Description     : ����CilentExternal Address��Ԫ
 Input           : pucSrc                       :����
                   pstClientExternalId          :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeExternalAddr
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_EXTERNAL_ID_STRU     *pstClientExternalId
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    /* �жϳ����Ƿ���1-20֮�� */
    if ((0 == ulUndecodeLen) || (LCS_CLIENT_EXID_MAX_LEN < ulUndecodeLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_EXT_ADDR,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen,
                                    0);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    NAS_LCS_MEM_CPY_S(  pstClientExternalId->stExternalAddr.aucAddr,
                                 LCS_CLIENT_EXID_MAX_LEN,
                                 pucSrcTmp,
                                 ulUndecodeLen);

    pstClientExternalId->bitOpExternalAddr = NAS_LCS_OP_TRUE;
    pstClientExternalId->stExternalAddr.ucLen = (VOS_UINT8)ulUndecodeLen;
    *pulLen = ulUndecodeLen;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeExtensionContainer
 Description     : ����Extension Container��Ԫ
 Input           : pucSrc                       :����
                   pstClientExternalId          :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeExtensionContainer
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_EXTERNAL_ID_STRU     *pstClientExternalId
)
{
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    *pulLen  = ulUndecodeLen;

    /* �ݲ����� */
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeDataCodingScheme
 Description     : ����Data Coding Scheme��Ԫ
 Input           : pucSrc                       :����
                   pucDataCodeScheme            :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeDataCodingScheme
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucDataCodeScheme
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    /* �жϳ����Ƿ�Ϸ� */
    if ( NAS_LCS_DATA_CODING_SCHEME_LEN != ulUndecodeLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_LOC_DATA_CODE_SHM,
                                    NAS_LCS_LEN_INVAILID,
                                    ulUndecodeLen,
                                    NAS_LCS_DATA_CODING_SCHEME_LEN);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ����DataCodeScheme */
    *pucDataCodeScheme = pucSrcTmp[ulSum++];

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeClientNameDataCodingScheme
 Description     : ����Clent Name��Ԫ�б�ѡ��ԪData Coding Scheme��Ԫ
 Input           : pucSrc                       :����
                   pucDataCodeScheme            :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeClientNameDataCodingScheme
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_NAME_STRU            *pstClientName
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    ulTmpLen    = ulUndecodeLen;
    enRslt      = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_CLIENT_NAME, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����Tag��Len */
    ulSum         = ulSum + ulTmpLen;
    ulUndecodeLen = ulValueLen;

    /* �ж�TAG�Ƿ���ȷ */
    if (0 == stTagStru.ulNumber)
    {
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeDataCodingScheme((pucSrcTmp + ulSum), &ulTmpLen, &pstClientName->ucDataCodeScheme);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
        }

        /* ����ʣ�೤�� */
        ulSum         = ulSum + ulTmpLen;
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;
    }
    else
    {
        ulSum   = ulSum + ulUndecodeLen;
        *pulLen = ulSum;
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CLIENT_NAME,
                                    NAS_LCS_MISS_DATA_CODE_SCH,
                                    stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeClientName
 Description     : ����Client Name��Ԫ
 Input           : pucSrc                       :����
                   pstClientName                :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeClientName
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_NAME_STRU            *pstClientName
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    /* ������ѡ��ԪDataCodingScheme */
    ulTmpLen = ulUndecodeLen;
    enRslt   = NAS_LCS_DecodeClientNameDataCodingScheme(pucSrcTmp + ulSum, &ulTmpLen, pstClientName);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    ulSum         = ulSum + ulTmpLen;
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeClientNameString(pucSrcTmp + ulSum, &ulTmpLen, pstClientName);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    ulSum         = ulSum + ulTmpLen;
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* �ж��Ƿ��п�ѡ��Ԫ */
    if (0 < ulUndecodeLen)
    {
        ulTmpLen = ulUndecodeLen;
        enRslt = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            /* ����ʣ�೤�� */
            ulSum   = ulSum + ulUndecodeLen;
            *pulLen = ulSum;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* ����TAG��LEN */
        ulSum         = ulSum + ulTmpLen;

        /* ����ʣ���������� */
        ulUndecodeLen = ulUndecodeLen - ulTmpLen;

        /* ������ѡ��ԪLcs-FormatIndeicator */
        ulTmpLen = ulValueLen;
        if (3 == stTagStru.ulNumber)
        {
            enRslt = NAS_LCS_DecodeFormatIndicator( pucSrcTmp + ulSum,
                                                    &ulTmpLen,
                                                    &pstClientName->enLcsFormat);
            if (NAS_LCS_CAUSE_SUCCESS == enRslt)
            {
                pstClientName->bitOpLcsFormat = NAS_LCS_OP_TRUE;
            }
        }

        /* ������ѡ��ԪValue���� */
        ulSum           = ulSum + ulValueLen;

        /* ����ʣ���������� */
        ulUndecodeLen   = ulUndecodeLen - ulValueLen;
    }

    /* ��������Ԫʣ���������� */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeFormatIndicator
 Description     : ����Format Indicator��Ԫ
 Input           : pucSrc                       :����
                   penLcsFormat                 :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeFormatIndicator
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_FORMAT_INDICATOR_ENUM_UINT8 *penLcsFormat
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    /* �жϿ�ѡ��Ԫ�����Ƿ�Ϸ� */
    if (1 != ulUndecodeLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_FORMAT_IND, NAS_LCS_LEN_INVAILID, ulUndecodeLen, 1);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ����LcsFormat */
    *penLcsFormat = pucSrcTmp[ulSum++];

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeClientNameString
 Description     : ����Client Name String��Ԫ
 Input           : pucSrc                       :����
                   pstClientName                :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeClientNameString
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_CLIENT_NAME_STRU            *pstClientName
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen        = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    ulTmpLen = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucSrcTmp, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CLIENT_NAME,
                                    NAS_LCS_LEN_DECODE_FAIL,
                                    0,
                                    0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* �ж�TAG�Ƿ���ȷ */
    if (2 != stTagStru.ulNumber)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CLIENT_NAME,
                                    NAS_LCS_TAG_ERROR,
                                    stTagStru.ulNumber,
                                    2);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TL */
    ulSum = ulSum + ulTmpLen;

    if ((0 == ulValueLen) || (LCS_CLIENT_NAME_MAX_LEN < ulValueLen))
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_CLIENT_NAME,
                                    NAS_LCS_LEN_INVAILID,
                                    ulValueLen,
                                    LCS_CLIENT_EXID_MAX_LEN);
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ���� */
    pstClientName->stNameString.ucLen = (VOS_UINT8)ulValueLen;

    NAS_LCS_MEM_CPY_S(    pstClientName->stNameString.aucNameString,
                          LCS_CLIENT_NAME_MAX_LEN,
                          (pucSrcTmp + ulSum),
                          ulValueLen);

    /* ����Value */
    ulSum = ulSum + ulValueLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeNotificationType
 Description     : ����Notication Type
 Input           : pucSrc                       :����
                   pucNtfType                   :���������
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeNotificationType
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucNtfType
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen       = 0;

    ulTmpLen    = ulUndecodeLen;
    enRslt      = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if(NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_NTF_TYPE, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ���TAG */
    if (0 != stTagStru.ulNumber)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_NTF_TYPE, NAS_LCS_TAG_ERROR, stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����Tag��Len */
    ulSum           = ulSum + ulTmpLen;

    /* ����Notication Type */
    *pucNtfType     = pucSrcTmp[ulSum];

    /* ��������IE */
    *pulLen = ulSum + ulValueLen;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocEstimateType
 Description     : ����locationEstimateType
 Input           : pucSrc                       :����
                   pstLocNtfStru                :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocEstimateType
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_LOCATION_TYPE_STRU          *pstLocationType
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    /* ������ѡlocationEstimateType */
    ulTmpLen    = ulUndecodeLen;
    enRslt      = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_EST_TYPE, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    /* ����TAG��LEN */
    ulSum         = ulSum + ulTmpLen;

    /* ����ʣ���������� */
    ulUndecodeLen = ulValueLen;

    /* �ж�TAG��LEN�Ƿ���Ч */
    if ((0 == stTagStru.ulNumber) && (1 == ulValueLen))
    {
        pstLocationType->enLocType = pucSrcTmp[ulSum++];
        ulUndecodeLen = ulUndecodeLen - 1;
    }
    else
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_EST_TYPE, NAS_LCS_LEN_INVAILID, ulValueLen, 1);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLocationType
 Description     : ����Location Type
 Input           : pucSrc                       :����
                   pstLocNtfStru                :������ṹ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeLocationType
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    NAS_LCS_LOCATION_TYPE_STRU          *pstLocationType
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulTmpLen;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulValueLen      = 0;

    ulTmpLen    = ulUndecodeLen;
    enRslt      = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if(NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_TYPE, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }

    if (1 != stTagStru.ulNumber)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_LOC_EST_TYPE, NAS_LCS_TAG_ERROR, stTagStru.ulNumber, 0);
        return NAS_LCS_CAUSE_MISTYPED_PARAMETER;
    }
    /* ����TAG��LEN */
    ulSum         = ulSum + ulTmpLen;

    /* ��ȡ����Ԫδ��������, ��IE��LENΪ׼ */
    ulUndecodeLen = ulValueLen;
    ulTmpLen      = ulUndecodeLen;

    /* ������ѡlocationEstimateType */
    enRslt      = NAS_LCS_DecodeLocEstimateType(pucSrcTmp + ulSum, &ulTmpLen, pstLocationType);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return enRslt;
    }

    /* ����locationEstimateType */
    ulSum         = ulSum + ulTmpLen;

    /* ����ʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* �ж��Ƿ���ڿ�ѡ��Ԫ */
    if (0 < ulUndecodeLen)
    {
        ulTmpLen = ulUndecodeLen;

        /* ����deferredLocationEventType */
        enRslt      = NAS_LCS_DecodeTL(pucSrcTmp + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
        if ((NAS_LCS_CAUSE_SUCCESS == enRslt)&& (1 == stTagStru.ulNumber))
        {
            /* ����TAG��LEN */
            ulSum = ulSum + ulTmpLen;

            /* ����ʣ���������� */
            ulUndecodeLen = ulUndecodeLen - ulTmpLen;

            /* ��ȡdeferredLocationEventType��Ԫ���� */
            ulTmpLen = ulValueLen;
            enRslt = NAS_LCS_DecodeDeferLocEventType(   pucSrcTmp + ulSum,
                                                        &ulTmpLen,
                                                        &pstLocationType->ucDeferLocEventType);
            if (NAS_LCS_CAUSE_SUCCESS == enRslt)
            {
                pstLocationType->bitOpDeferLocEventType = NAS_LCS_OP_TRUE;
            }

            /* ����deferredLocationEventType Value */
            ulSum = ulSum + ulValueLen;

            /* ����ʣ���������� */
            ulUndecodeLen = ulUndecodeLen - ulValueLen;
        }
    }

    /* ��������IE */
    ulSum   = ulSum + ulUndecodeLen;
    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeDeferLocEventType
 Description     : ��������ö��
 Input           : pucSrc                       :����
                   pucDest                      :���������
                   ucTagMode                    :TAGģʽ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeDeferLocEventType
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulLen,
    VOS_UINT8                           *pucDeferLocEventType
)
{
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT32                          ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;
    VOS_UINT8                           ucValue;
    VOS_UINT8                           ucFillBitNum    = 0;
    VOS_UINT8                           ucTmpLen;

    /* ��鳤�� */
    if (NAS_LCS_BIT_STRING_MIN_LEN > ulUndecodeLen)
    {
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ����ԪΪbitString�����ʽ, V�е�һ���ֽ�Ϊ���bit���� */
    /* ��ȡ���BIT���� */
    ucFillBitNum = pucSrcTmp[ulSum++];

    /* ��ȡ��ʵSting�ֽ��� */
    ucTmpLen     = (VOS_UINT8)ulUndecodeLen - 1;

    /* ��ȡDeferLocEventType, ��ǰֻ��һ���ֽ� */
    if (1 == ucTmpLen)
    {
        /* ������Ϊ1ʱ, �������Bit��, ��ȡ��Ч���� */
        switch(ucFillBitNum)
        {
            case 0:
                ucValue = pucSrcTmp[ulSum];
                break;

            case 1:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_7_BIT;
                break;

            case 2:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_6_BIT;
                break;

            case 3:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_5_BIT;
                break;

            case 4:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_4_BIT;
                break;

            case 5:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_3_BIT;
                break;

            case 6:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_2_BIT;
                break;

            case 7:
                ucValue = pucSrcTmp[ulSum] & NAS_LCS_MSG_HIGH_1_BIT;
                break;

            default:
                ucValue = 0;
                break;
        }
    }
    else
    {
        /* ��ǰֻ��һ���ֽ�, ���Ը��ֽڶ�Ϊ��Ч���� */
        ucValue = pucSrcTmp[ulSum];
    }

    /* ����������Ԫ */
    *pulLen = ulUndecodeLen;
    *pucDeferLocEventType = ucValue;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeTL
 Description     : ����TAG��Len
 Input           : pucSrc                       :����
 Output          : pulLen                       :�ѽ�������
                   pulIeLen                     :IE LEN
                   pstTagStru                   :������TAG�ṹ
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeTL
(
    VOS_UINT8                           *pucSrc,
    NAS_LCS_TAG_STRU                    *pstTagStru,
    VOS_UINT32                          *pulValueLen,
    VOS_UINT32                          *pulLen
)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT32                          ulUndecodeLen = *pulLen;
    VOS_UINT8                          *pucSrTmp      = pucSrc;
    VOS_UINT32                          ulSum         = 0;
    VOS_UINT32                          ulTmpLen      = 0;
    VOS_UINT32                          ulValueLen    = 0;

    *pulValueLen    = 0;
    *pulLen         = 0;

    /* ��ʼ�� */
    NAS_LCS_MEM_SET_S(  pstTagStru,
                        sizeof(NAS_LCS_TAG_STRU),
                        0,
                        sizeof(NAS_LCS_TAG_STRU));

    if (0 == ulUndecodeLen)
    {
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ��ȡʣ���������� */
    ulTmpLen        = ulUndecodeLen;

    /* �Ա�ǩ���н��룬����TLV�е�T��L,ȷ������λ�� */
    enRslt = NAS_LCS_DecodeTag(pucSrTmp + ulSum, pstTagStru, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_TAG, NAS_LCS_TAG_DECODE_FAIL, 0, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_TAG_DECODE_FAIL TAG decode fail ");
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ����TAG */
    ulSum           = ulSum + ulTmpLen;

    /* ��ȡʣ���������� */
    ulUndecodeLen   = ulUndecodeLen - ulTmpLen;
    ulTmpLen        = ulUndecodeLen;

    /* ����LEN */
    enRslt          = NAS_LCS_DecodeLength(pucSrTmp + ulSum, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        NAS_LCS_SndOmDecodeDbgInfo(NAS_LCS_CN_MSG_IE_LENGTH, NAS_LCS_LEN_DECODE_FAIL, 0, 0);
        NAS_LCS_INFO_LOG(" NAS_LCS_TAG_DECODE_FAIL LENGTH decode fail ");
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    /* ����L */
    ulSum         = ulSum + ulTmpLen;

    /* ��ȡʣ���������� */
    ulUndecodeLen = ulUndecodeLen - ulTmpLen;

    /* ���ʣ�����������Ƿ�С��Value���� */
    if (ulUndecodeLen < ulValueLen)
    {
        NAS_LCS_SndOmDecodeDbgInfo( NAS_LCS_CN_MSG_IE_LENGTH,
                                    NAS_LCS_UNDECODE_LEN_INVAlID,
                                    ulUndecodeLen,
                                    ulValueLen);
        NAS_LCS_INFO_LOG(" NAS_LCS_TAG_DECODE_FAIL unDecode Len Invalid ");
        return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }

    *pulLen       = ulSum;
    *pulValueLen  = ulValueLen;
    return NAS_LCS_CAUSE_SUCCESS;
}
/*****************************************************************************
 Function Name   : NAS_LCS_DecodeTag
 Description     : ��������ö��
 Input           : pucSrc                       :����
                   pucDest                      :���������
                   ucTagMode                    :TAGģʽ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeTag
(
    VOS_UINT8                           *pucSrc,
    NAS_LCS_TAG_STRU                    *pstTagStru,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT8                           ucCounter       = 0;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT8                           ulSum           = 0;
    VOS_UINT32                          ulUndecodeLen   = *pulLen;

    *pulLen = 0;

    /*��ȡ��ǩ���ͺͽṹ*/
    pstTagStru->ucClass = pucSrcTmp[ulSum] >> NAS_LCS_MOVEMENT_6_BITS;
    pstTagStru->ucStructed = (VOS_UINT8)(pucSrcTmp[ulSum] & 0x20);

    /*��ȡ��ǩֵ*/
    ucTmp = (VOS_UINT8)(pucSrcTmp[ulSum++] & NAS_LCS_MSG_LOW_5_BIT);

    /*���ֽڸ�ʽ*/
    if (ucTmp != NAS_LCS_MULTI_BYTE_TAG_FLAG)
    {
        pstTagStru->ulNumber = ucTmp;
        *pulLen = ulSum;
        return NAS_LCS_CAUSE_SUCCESS;
    }

    /* ���ֽڸ�ʽʱ,��ȡ��ǩֵ,���λΪ1ʱ,��ʾ�к����ֽ� */
    /* �Ѻ����ֽڵĵ�һ���ֽڵ����һ���ֽڵĵ�7λ����һλ���������Ǳ�ǩ��ֵ */
    pstTagStru->ulNumber = 0;
    do
    {
        /* �ж������Ƿ�������� */
        if (ulUndecodeLen <= ulSum)
        {
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
        }

        ucCounter++;

        /*����ѭ��������VOS_UINT32�͵ĳ������*/
        if (ucCounter > sizeof(VOS_UINT32))
        {
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
        }

        ucTmp = pucSrcTmp[ulSum++];
        pstTagStru->ulNumber = (VOS_INT32)(((VOS_UINT32)pstTagStru->ulNumber << NAS_LCS_MOVEMENT_7_BITS) + (ucTmp & NAS_LCS_MSG_LOW_7_BIT));
    }while(ucTmp >= NAS_LCS_MULTI_BYTE_TAG_CON_OCT_MIN_VALUE);

    *pulLen = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeLength
 Description     : ����LEN
 Input           : pucSrc                       :����
                   pucDest                      :���������
                   ucTagMode                    :TAGģʽ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32  NAS_LCS_DecodeLength
(
    VOS_UINT8                           *pucSrc,
    VOS_UINT32                          *pulValueLen,
    VOS_UINT32                          *pulLen
)
{
    VOS_UINT8                           ucTmpLen      = 0;
    VOS_UINT8                          *pucTmpMsg     = pucSrc;
    VOS_UINT32                          ulSum         = 0;
    VOS_UINT32                          ulUndecodeLen = *pulLen;

    *pulValueLen = 0;

    if ((0 == ulUndecodeLen)||(NAS_LCS_MAX_COMPONENT_LENGTH < ulUndecodeLen))
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    /* �������� */
    ucTmpLen = pucTmpMsg[ulSum++];

    /* ����Ƕ̸�ʽģʽ����ȷ���ȣ����㳤�� */
    if (ucTmpLen < NAS_LCS_INDEF_LENGTH_FLAG)
    {
        *pulValueLen = ucTmpLen;
        *pulLen      = ulSum;
        return NAS_LCS_CAUSE_SUCCESS;
    }

    ulUndecodeLen = ulUndecodeLen - ulSum;

    /* �Ƕ̸�ʽ */
    switch (ucTmpLen)
    {
        case NAS_LCS_INDEF_LENGTH_FLAG:

            /* �������ȵļ��㴦�� */
            /* ������LCS��para���ܳ����ǿ�֪�ģ����Բ�Ӧ�ó���ֱ�Ӵ������ݶ���������������ݵĳ��� */
            ucTmpLen = (VOS_UINT8)ulUndecodeLen;
            if (NAS_LCS_CAUSE_SUCCESS != NAS_LCS_DecodeIndefLen(pucTmpMsg + ulSum, &ucTmpLen))
            {
                return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
            }

            *pulValueLen = ucTmpLen;
            break;

        case (NAS_LCS_INDEF_LENGTH_FLAG + 1):

            /* ����ʽ�����ֽ� */
            *pulValueLen = pucTmpMsg[ulSum++];
            break;

        default:
            /*
            ����129�����������Facility Ie���Ȳ��ᳬ��һ���ֽڣ���ʹ�ö��ֽڱ�ʾʱ�����ᳬ��һ���ֽ�
            ���������������
            */
            return NAS_LCS_CAUSE_UNEXPECT_DATA_VALUE;
    }
    *pulLen     = ulSum;
    return NAS_LCS_CAUSE_SUCCESS;

}

/*****************************************************************************
 Function Name   : NAS_LCS_DecodeIndefLen
 Description     : ��������LEN
 Input           : pucSrc                       :����
                   pucDest                      :���������
                   ucTagMode                    :TAGģʽ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_DecodeIndefLen(VOS_UINT8 *pucSrc, VOS_UINT8 *pucLen)
{
    VOS_UINT8                           aucEndFlag[]    = {0,0};
    VOS_UINT8                           ucEndFlagLength;
    VOS_UINT32                          ulLoop = 0;
    VOS_UINT8                           ucLength        = 0;
    VOS_UINT8                           ucLengthBytes;
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucSrcTmp       = pucSrc;
    VOS_UINT8                           ucUndoceLen     = *pucLen;

    /* ��ȡ���������� */
    ucEndFlagLength = sizeof(aucEndFlag);

    /* ��ʣ����������С�ڽ���������, ����ʧ�� */
    if (ucEndFlagLength > ucUndoceLen)
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    ulLoop          = 0;

    /* ѭ����������, ��ֹ����IE�л����ڲ�������IE */
    while (ulLoop < ucUndoceLen)
    {
        if (0 == PS_MEM_CMP(pucSrcTmp + ulLoop, aucEndFlag, ucEndFlagLength))
        {
            /* ʵ����������, ���������� */
            *pucLen      = (VOS_UINT8)ulLoop + ucEndFlagLength;
            return NAS_LCS_CAUSE_SUCCESS;
        }

        /* TAG */
        ulLoop++;

        /* LENGTH */
        ucLength    = pucSrcTmp[ulLoop];
        ulLoop++;

        /* ��������ʽ:Length���ڰ�λ��̶�����Ϊ0x80��Value���������������0x00��β��*/
        if (NAS_LCS_INDEF_LENGTH_FLAG == ucLength)
        {
            ucLength = ucUndoceLen - (VOS_UINT8)ulLoop;
            ulRet = NAS_LCS_DecodeIndefLen(pucSrcTmp + ulLoop, &ucLength);
            if (NAS_LCS_CAUSE_SUCCESS != ulRet)
            {
                return ulRet;
            }
            ulLoop  += ucLength;
        }
        else
        {
            if (NAS_LCS_INDEF_LENGTH_FLAG == (ucLength & NAS_LCS_INDEF_LENGTH_FLAG))
            {
                /* ������ʽ����ʽ: ��һ����λ��ĵ���λָ������L��ռ�õİ�λ�������������λ���ʾV�ĳ��� */
                /* SS��֧�ֳ���Ϊ1�ֽڵĳ��� */
                ucLengthBytes = ucLength & NAS_LCS_MSG_LOW_7_BIT;
                if ((ucLengthBytes > sizeof(VOS_UINT8)) || (ulLoop >= ucUndoceLen))
                {
                    return NAS_LCS_CAUSE_FAIL;
                }

                /* LENGTH */
                ucLength    = pucSrcTmp[ulLoop];
                ulLoop++;

                ulLoop  += ucLength;
            }
            else
            {
                /* ������ʽ�̸�ʽ */
                ulLoop  += ucLength;
            }
        }
    }
    return NAS_LCS_CAUSE_FAIL;
}

/*****************************************************************************
 Function Name   : NAS_LCS_CheckOperationCode
 Description     : ��������LEN
 Input           : pucSrc                       :����
                   pucDest                      :���������
                   ucTagMode                    :TAGģʽ
 Output          : pulLen                       :�ѽ�������
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :�������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_CheckOperationCode(NAS_LCS_OPERATION_TYPE_UINT32 enOperationCode)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    /* ���OperationCode */
    switch(enOperationCode)
    {
        case NAS_LCS_OPERATION_MO_LR:
        case NAS_LCS_OPERATION_LOC_NOTIFICATION:
            enRslt = NAS_LCS_CAUSE_SUCCESS;
            break;

        default:
            enRslt = NAS_LCS_CAUSE_FAIL;
            break;
    }
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_CheckProblemTagVaild
 Description     : �ж�Problem Code�Ƿ�Ϸ�
 Input           : enProblemTag :Problem Tag
 Output          : None
 Return          : 0:�Ϸ�, 1:�Ƿ�

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_CheckProblemTagVaild(NAS_LCS_PROBLEM_TAG_ENUM_UINT8 enProblemTag)
{
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    /* ���ProblemTag */
    switch (enProblemTag)
    {
        case NAS_LCS_PROBLEM_GENERAL_TAG:
        case NAS_LCS_PROBLEM_INVOKE_TAG:
        case NAS_LCS_PROBLEM_RTN_RSLT_TAG:
        case NAS_LCS_PROBLEM_RTN_ERR_TAG:

            enRslt = NAS_LCS_CAUSE_SUCCESS;
            break;

         default:
            enRslt = NAS_LCS_CAUSE_FAIL;
            break;
    }
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_GetRegisterOperaCode
 Description     : ��ȡRegister�տڵ���ϢOperation Code
 Input           : pucFacilityIe                  : FacilityIe����
                   ulLen                          : ��������
 Output          : None
 Return          : NAS_LCS_OPERATION_TYPE_UINT32  : Operation Code

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_OPERATION_TYPE_UINT32 NAS_LCS_GetRegisterOperaCode
(
    VOS_UINT8                          *pucFacilityIe,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulUndecodeLen = ulLen;
    NAS_LCS_OPERATION_TYPE_UINT32       enOperaCode   = NAS_LCS_OPERATION_NULL;
    VOS_UINT8                          *pucMsgTem     = pucFacilityIe;
    VOS_UINT32                          ulSum         = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    NAS_LCS_TAG_STRU                    stTagStru;
    VOS_UINT32                          ulValueLen    = 0;
    VOS_UINT32                          ulTmpLen      = 0;

    /* �ж�ʣ�����������Ƿ�����Register�տ�Facility Ie��С���� */
    if (NAS_LCS_REG_IE_FACILITY_MIN_LEN > ulUndecodeLen)
    {
        return NAS_LCS_OPERATION_NULL;
    }

    /* �ж�IEI�Ƿ���ȷ */
    if (NAS_LCS_MSG_FACILITY_IEI != pucMsgTem[ulSum])
    {
        return NAS_LCS_OPERATION_NULL;
    }

    /* ����Facility IEI��Len */
    ulSum         = ulSum + 2;
    ulUndecodeLen = ulUndecodeLen - 2;

    /* �ж�Component type�Ƿ�ΪInvoke */
    if (NAS_LCS_COMPONENT_INVOKE_TAG != pucMsgTem[ulSum])
    {
        return NAS_LCS_OPERATION_NULL;
    }

    /* ����Component type Tag��Length */
    ulTmpLen      = ulUndecodeLen;
    enRslt = NAS_LCS_DecodeTL(pucMsgTem + ulSum, &stTagStru, &ulValueLen, &ulTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_OPERATION_NULL;
    }

    /* ����Component type Tag��Length */
    ulSum         = ulSum + ulTmpLen;
    ulUndecodeLen = ulValueLen;

    /* ����Invoke Id */
    if ((NAS_LCS_INVOKE_ID_TAG == pucMsgTem[ulSum])&&(3 <= ulUndecodeLen))
    {
        ulSum         = ulSum + 3;
        ulUndecodeLen = ulUndecodeLen - 3;
    }
    else
    {
        return NAS_LCS_OPERATION_NULL;
    }

    /* �ж��Ƿ����Linked Id */
    if (NAS_LCS_LINKED_ID_TAG == pucMsgTem[ulSum])
    {
        if (3 <= ulUndecodeLen)
        {
            ulSum         = ulSum + 3;
            ulUndecodeLen = ulUndecodeLen - 3;
        }
        else
        {
            return NAS_LCS_OPERATION_NULL;
        }
    }

    /* ��ȡOperation Code */
    if ((NAS_LCS_OPERATION_CODE_TAG == pucMsgTem[ulSum])&&(3 <= ulUndecodeLen))
    {
        ulSum = ulSum + 2;
        enOperaCode = pucMsgTem[ulSum];
    }
    else
    {
        return NAS_LCS_OPERATION_NULL;
    }
    return enOperaCode;
}

#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


