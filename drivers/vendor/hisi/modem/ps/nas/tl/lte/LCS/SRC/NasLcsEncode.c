/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLcsEncode.c
  Description     :
  History         :
     1.HANLUFENG 41410       2013-8-8   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "vos.h"
#include  "NasLcsPublic.h"
#include  "NasLcsEncode.h"
#include  "NasLcsDecode.h"


#define    THIS_FILE_ID            PS_FILE_ID_NASLCSENCODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSENCODE_C

#if (FEATURE_LPP == FEATURE_ON)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_LCS_EncodeRelComplete
 Description     : ����Release Complete�տ���Ϣ
 Input           : pucEncodeOutMsg              :���������
                   stEncodeInfo                 :��������Ҫ����Ϣ
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRelComplete
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT32                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                           ucTi     = pstEncodeInfo->ucTi;
    VOS_UINT16                          usTmpLen = 0;
    VOS_UINT8                           ucTag;

    *pusIeLen = 0;

    /* ����PD��TI */
    pucEncodeOutMsg[usSum]  = NAS_LCS_PROTOCOL_DISCRIMINATOR;
    pucEncodeOutMsg[usSum]  = pucEncodeOutMsg[usSum] | (VOS_UINT8)(ucTi << NAS_LCS_MOVEMENT_4_BITS);
    usSum++;

    /* ����Msg Type */
    pucEncodeOutMsg[usSum++] = NAS_LCS_CN_MSG_REL_CML;

    /* ����Fccility Ie */
    /* �ж��Ƿ�Я��Cause,��Я��Cause��˵��Rel Cmp��Ϣ��Я��Return Error����Retrun Rej */
    if (NAS_LCS_OP_TRUE == pstEncodeInfo->bitOpCause)
    {
        /* ȡCause�е�16λ�еĸ�8λ, ��ΪComponent Code */
        ucTag = (VOS_UINT8)((pstEncodeInfo->enCause & NAS_LCS_MSG_LOW_16_BIT) >> NAS_LCS_MOVEMENT_8_BITS);
        if (NAS_LCS_ERROR_CODE_TAG == ucTag)
        {
            enRslt = NAS_LCS_EncodeIeFacility(      pucEncodeOutMsg + usSum,
                                                    &usTmpLen,
                                                    pstEncodeInfo,
                                                    NAS_LCS_CN_MSG_REL_CML,
                                                    NAS_LCS_COMPONENT_RETURN_ERR_TAG);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
        }
        else
        {
            enRslt = NAS_LCS_EncodeIeFacility(      pucEncodeOutMsg + usSum,
                                                    &usTmpLen,
                                                    pstEncodeInfo,
                                                    NAS_LCS_CN_MSG_REL_CML,
                                                    NAS_LCS_COMPONENT_REJECT);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
        }
        usSum = usSum + usTmpLen;
    }
    /* �ж��Ƿ�ΪMT-LR RSP */
    else if (NAS_LCS_OP_TRUE == pstEncodeInfo->bitLocNtfRsp)
    {
        enRslt = NAS_LCS_EncodeIeFacility(  pucEncodeOutMsg + usSum,
                                            &usTmpLen,
                                            pstEncodeInfo,
                                            NAS_LCS_CN_MSG_REL_CML,
                                            NAS_LCS_COMPONENT_RETURN_RSLT_TAG);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return NAS_LCS_CAUSE_FAIL;
        }
        usSum = usSum + usTmpLen;
    }
    /* ��������,��Ϊ�������̽���, ��Я��Facility��Ԫ  */
    else
    {
        enRslt = NAS_LCS_CAUSE_SUCCESS;
    }

    *pusIeLen = usSum;
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeRegister
 Description     : ����register�տ���Ϣ
 Input           : pucEncodeOutMsg              :���������
                   stEncodeInfo                 :��������Ҫ����Ϣ
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRegister
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT32                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                           ucTi     = pstEncodeInfo->ucTi;
    VOS_UINT16                          usTmpLen = 0;

    *pusIeLen = 0;

    /* ����PD��TI */
    pucEncodeOutMsg[usSum]  = NAS_LCS_PROTOCOL_DISCRIMINATOR;
    pucEncodeOutMsg[usSum]  = pucEncodeOutMsg[usSum] | (VOS_UINT8)(ucTi << NAS_LCS_MOVEMENT_4_BITS);
    usSum++;

    /* ����Msg Type */
    pucEncodeOutMsg[usSum++] = NAS_LCS_CN_MSG_REGISTER;

    /* ����Facility Ie */
    enRslt = NAS_LCS_EncodeIeFacility(  pucEncodeOutMsg + usSum,
                                        &usTmpLen,
                                        pstEncodeInfo,
                                        NAS_LCS_CN_MSG_REGISTER,
                                        NAS_LCS_COMPONENT_INVOKE_TAG);

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeFacility
 Description     : ����FACILITY�տ���Ϣ
 Input           : pucEncodeOutMsg              :���������
                   stEncodeInfo                 :��������Ҫ����Ϣ
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT32                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                           ucTi     = pstEncodeInfo->ucTi;
    VOS_UINT16                          usTmpLen = 0;

    *pusIeLen = 0;

    /* ����PD��TI */
    pucEncodeOutMsg[usSum]  = NAS_LCS_PROTOCOL_DISCRIMINATOR;
    pucEncodeOutMsg[usSum]  = pucEncodeOutMsg[usSum] | (VOS_UINT8)(ucTi << NAS_LCS_MOVEMENT_4_BITS);
    usSum++;

    /* ����Msg Type */
    pucEncodeOutMsg[usSum++] = NAS_LCS_CN_MSG_FACILITY;

    /* ����Facility Ie */
    enRslt = NAS_LCS_EncodeIeFacility(  pucEncodeOutMsg + usSum,
                                        &usTmpLen,
                                        pstEncodeInfo,
                                        NAS_LCS_CN_MSG_FACILITY,
                                        NAS_LCS_COMPONENT_INVOKE_TAG);

    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeIeFacility
 Description     : ����տ���ԪFacility
 Input           : pucEncodeOutMsg              :���������
                   stEncodeInfo                 :��������Ҫ����Ϣ
                   enMsgType                    :�տ���Ϣ����
                   enComponent                  :Component����
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeIeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo,
    NAS_LCS_CN_MSG_TYPE_ENUM_UINT32     enMsgType,
    NAS_LCS_COMPONENT_ENUM_UINT8        enComponent
)
{
    VOS_UINT16                          usSum       = 0;
    VOS_UINT16                          usTmpLen    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT16                          usValueLen  = 0;
    VOS_UINT16                          usLenIndex  = 0;

    *pusIeLen = 0;

    /* ���ݿտ���Ϣ����, ������Ԫ���� */
    switch(enMsgType)
    {
        case NAS_LCS_CN_MSG_REL_CML:

            /* Rel Cmp��Facility��Ԫ�ṹΪTLV, ����IEI */
            pucEncodeOutMsg[usSum++] = NAS_LCS_MSG_FACILITY_IEI;

            /* ��������,��������Facility Value����д���� */
            usLenIndex = usSum;
            usSum++;
            enRslt = NAS_LCS_EncodeRelCmpIeFacility(    pucEncodeOutMsg + usSum,
                                                        &usTmpLen,
                                                        pstEncodeInfo,
                                                        enComponent);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
            usSum = usSum + usTmpLen;
            usValueLen = usTmpLen;
            break;

        case NAS_LCS_CN_MSG_REGISTER:

            /* REGISTER��Facility��Ԫ�ṹΪTLV,  ����IEI */
            pucEncodeOutMsg[usSum++] = NAS_LCS_MSG_FACILITY_IEI;

            /* ��������,��������Facility Value����д���� */
            usLenIndex = usSum;
            usSum++;
            enRslt = NAS_LCS_EncodeRegisterIeFacility(  pucEncodeOutMsg + usSum,
                                                        &usTmpLen,
                                                        pstEncodeInfo,
                                                        enComponent);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
            usSum = usSum + usTmpLen;
            usValueLen = usTmpLen;
            break;

        case NAS_LCS_CN_MSG_FACILITY:

            /* Facility��Facility��Ԫ�ṹΪLV, û��IEI */
            /* ��������,��������Facility Value����д���� */
            usLenIndex = usSum;
            usSum++;
            enRslt = NAS_LCS_EncodeRegisterIeFacility(  pucEncodeOutMsg + usSum,
                                                        &usTmpLen,
                                                        pstEncodeInfo,
                                                        enComponent);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
            usSum = usSum + usTmpLen;
            usValueLen = usTmpLen;
            break;

        default:
            TLPS_PRINT2LAYER_ERROR1(NAS_LCS_EncodeIeFacility_ENUM, LNAS_LCS_MsgTypeInvalid, enMsgType);
            return NAS_LCS_CAUSE_FAIL;
    }

    /* Component Len���Ϊ255 */
    if (NAS_LCS_MAX_COMPONENT_LENGTH < usValueLen)
    {
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_EncodeIeFacility_ENUM, LNAS_LCS_EnocdeLenFail, usValueLen);
        return NAS_LCS_CAUSE_FAIL;
    }

    /* ���LEHGTH */
    pucEncodeOutMsg[usLenIndex] = (VOS_UINT8)usValueLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeRegisterIeFacility
 Description     : ����Register�տ���ԪFacility
 Input           : pucEncodeOutMsg              :���������
                   stEncodeInfo                 :��������Ҫ����Ϣ
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRegisterIeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo,
    NAS_LCS_COMPONENT_ENUM_UINT8         enComponent
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    NAS_LCS_POS_PDUS_STRU               stPosPdus;
    NAS_LCS_LPP_MSG_RECORD_STRU         *pstLppMsgRecord = NAS_LCS_GetLppMolrRecord();

    *pusIeLen = 0;

    /* ����INVOKE ID */
    pucEncodeOutMsg[usSum++] = NAS_LCS_INVOKE_ID_TAG;
    pucEncodeOutMsg[usSum++] = 1;
    pucEncodeOutMsg[usSum++] = pstEncodeInfo->ucInvokeId;

    /* ����OPERATION CODE */
    pucEncodeOutMsg[usSum++] = NAS_LCS_OPERATION_CODE_TAG;
    pucEncodeOutMsg[usSum++] = 1;
    pucEncodeOutMsg[usSum++] = NAS_LCS_OPERATION_MO_LR;

    /* ����Parameters */
    if (NAS_LCS_START_SOURCE_LPP == pstEncodeInfo->enStartSource)
    {
        /* ��ǰLPP��������Ϣֻ��һ�� */
        stPosPdus.ucPduNum = 1;
        stPosPdus.astPosPdu[0].ucPduLen = (VOS_UINT8)pstLppMsgRecord->ulLppMsgSize;
        stPosPdus.astPosPdu[0].pucPdu   = pstLppMsgRecord->aucLppMsg;

        enRslt = NAS_LCS_EncodeAssDataMoLrReq(pucEncodeOutMsg + usSum, &usTmpLen, &stPosPdus);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return NAS_LCS_CAUSE_FAIL;
        }
    }
    else if(NAS_LCS_START_SOURCE_TAF == pstEncodeInfo->enStartSource)
    {
        enRslt = NAS_LCS_EncodeLocEstimateMoLrReq(pucEncodeOutMsg + usSum, &usTmpLen);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return NAS_LCS_CAUSE_FAIL;
        }
    }
    else
    {
        TLPS_PRINT2LAYER_ERROR1(    NAS_LCS_EncodeRegisterIeFacility_ENUM,
                                    LNAS_LCS_StartSourceInvalid,
                                    pstEncodeInfo->enStartSource);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;

    /* ����Component Tag��Length */
    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(enComponent, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeRelCmpIeFacility_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeAssDataMoLrReq
 Description     : ������������Ϣ��MoLr�����Paramesters
 Input           : pucEncodeOutMsg              :���������
                   stEncodeInfo                 :��������Ҫ����Ϣ
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeAssDataMoLrReq
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_POS_PDUS_STRU               *pstPosPdus
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;

    /* ������Ԫmo-lr */
    NAS_LCS_EncodeMolrType(pucEncodeOutMsg + usSum, &usTmpLen, NAS_LCS_MOLR_ASSISTANCE_DATA);
    usSum = usSum + usTmpLen;

    /* ������ԪmultiplePostioningProtocolPDUs */
    enRslt = NAS_LCS_EncodeMuliPosPDUS(pucEncodeOutMsg + usSum, &usTmpLen, pstPosPdus);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_FAIL;
    }
    usSum = usSum + usTmpLen;
    usTmpLen = usSum;

    /* ����mo-lr parameters TAG��LENGTH */
    enRslt = NAS_LCS_PackTL(NAS_LCS_SEQUENCE_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeAssDataMoLrReq_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeMuliPosPDUS
 Description     : ������ԪmutiplePositioningProtocolPDUs
 Input           : pucEncodeOutMsg              :���������
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeMuliPosPDUS
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_POS_PDUS_STRU               *pstPosPdus
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                           ucLoop;

    *pusIeLen = 0;

    /* ����PositioningProtocolPDU, */
    for (ucLoop = 0; ucLoop < pstPosPdus->ucPduNum; ucLoop++)
    {
        enRslt = NAS_LCS_EncodePosPDU(  pucEncodeOutMsg + usSum,
                                        &usTmpLen,
                                        &pstPosPdus->astPosPdu[ucLoop]);
        if (NAS_LCS_CAUSE_SUCCESS != enRslt)
        {
            return NAS_LCS_CAUSE_FAIL;
        }
        usSum = usSum + usTmpLen;
    }

    /* ����mutiplePositioningProtocolPDUs��TAG��LENGTH */
    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(NAS_LCS_MOLR_MULI_POS_PROTOC_PDUS_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeMuliPosPDUS_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLppMsg
 Description     : ������Ԫ����PositioningProtocolPDU
 Input           : pucEncodeOutMsg              :���������
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodePosPDU
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_POS_PDU_STRU                *pstPosPdu
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;

    /* ����Pdu���� */
    NAS_LCS_MEM_CPY_S(pucEncodeOutMsg, NAS_LCS_MAX_LPP_MSG_LEN, pstPosPdu->pucPdu, pstPosPdu->ucPduLen);

    usSum = pstPosPdu->ucPduLen;
    usTmpLen = usSum;

    /* ����TAG��LENGTH */
    enRslt = NAS_LCS_PackTL(NAS_LCS_OCTETSTRING_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeMuliPosPDUS_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLocEstimateMoLrReq
 Description     : ����LocationEstimate���͵�MoLr�����Paramesters
 Input           : pucEncodeOutMsg              :���������
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeLocEstimateMoLrReq
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen
)
{
    VOS_UINT16                          usSum       = 0;
    VOS_UINT16                          usTmpLen    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    LCS_MOLR_PARA_STRU                 *pstMolrPara = NAS_LCS_GetTafMolrRecord();

    *pusIeLen = 0;

    /* ������Ԫmo-lr type */
    NAS_LCS_EncodeMolrType(pucEncodeOutMsg + usSum, &usTmpLen, NAS_LCS_MOLR_LOCATION_ESTIMATE);
    usSum = usSum + usTmpLen;

    /* ������Ԫlocation method */
    NAS_LCS_EncodeLocationMethod(pucEncodeOutMsg + usSum, &usTmpLen, pstMolrPara->enMethod);
    usSum = usSum + usTmpLen;

    /* ����LCS QOS */
    NAS_LCS_EncodeLcsQos(pucEncodeOutMsg + usSum, &usTmpLen, pstMolrPara);
    usSum = usSum + usTmpLen;

    NAS_LCS_EncodeClentExtId(pucEncodeOutMsg + usSum, &usTmpLen, pstMolrPara);
    usSum = usSum + usTmpLen;

    /* ������ԪSupportGADShapes */
    NAS_LCS_EncodeSuppGADShapes(pucEncodeOutMsg + usSum, &usTmpLen, pstMolrPara);
    usSum = usSum + usTmpLen;

    /* ����mo-lr parameters TAG��LENGTH */
    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(NAS_LCS_SEQUENCE_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeLocEstimateMoLrReq_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeSuppGADShapes
 Description     : ����supportedGADShapes
 Input           : pucEncodeOutMsg              :���������
                   pstTafMsgRecord              :Taf�·���MoLr�������
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeSuppGADShapes
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_PARA_STRU                  *pstMolrPara
)
{
    VOS_UINT16                          usSum           = 0;
    LCS_SHAPE_REP_STRU                  *pstShapeRep;
    VOS_UINT8                           ucTmp           = 0;

    *pusIeLen = 0;

    /* ����Value,ת���ɿտڸ�ʽ */
    pstShapeRep = &pstMolrPara->u.stShapeRep;
    ucTmp = pstShapeRep->bitEllipPoint << NAS_LCS_MOVEMENT_7_BITS;
    ucTmp = ucTmp | (pstShapeRep->bitEllipPointUncertCircle << NAS_LCS_MOVEMENT_6_BITS);
    ucTmp = ucTmp | (pstShapeRep->bitEllipPointUncertEllip << NAS_LCS_MOVEMENT_5_BITS);
    ucTmp = ucTmp | (pstShapeRep->bitPolygon << NAS_LCS_MOVEMENT_4_BITS);
    ucTmp = ucTmp | (pstShapeRep->bitEllipPointAlt << NAS_LCS_MOVEMENT_3_BITS);
    ucTmp = ucTmp | (pstShapeRep->bitEllipPointAltUncertEllip << NAS_LCS_MOVEMENT_2_BITS);
    ucTmp = ucTmp | (pstShapeRep->bitEllipArc << NAS_LCS_MOVEMENT_1_BITS);

    /* ����TAG */
    pucEncodeOutMsg[usSum++] = NAS_LCS_SUPP_GAD_SHAPES_TAG;

    /* ����LEN */
    pucEncodeOutMsg[usSum++] = 2;

    /* ���뱣��λLEN */
    pucEncodeOutMsg[usSum++] = 1;

    /* ����VALUE */
    pucEncodeOutMsg[usSum++] = ucTmp;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeClentExtId
 Description     : ����lcsClientExternalId
 Input           : pucEncodeOutMsg              :���������
                   pstTafMsgRecord              :Taf�·���MoLr�������
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeClentExtId
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_PARA_STRU                  *pstMolrPara
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;
    if ((LCS_MOLR_METHOD_TRANSFER_TP_ADDR == pstMolrPara->enMethod)
        || (LCS_MOLR_METHOD_RETRIEVAL_TP_ADDR == pstMolrPara->enMethod))
    {
        if (0 < pstMolrPara->stTPAddr.ucLength)
        {
            usTmpLen = pstMolrPara->stTPAddr.ucLength;
            pucEncodeOutMsg[usSum++] = NAS_LCS_CLIENT_EXT_ID_ADDR_TAG;
            pucEncodeOutMsg[usSum++] = (VOS_UINT8)usTmpLen;
            NAS_LCS_MEM_CPY_S(  pucEncodeOutMsg + usSum,
                                         LCS_CLIENT_EXID_MAX_LEN,
                                         pstMolrPara->stTPAddr.aucValue,
                                         usTmpLen);

            usSum = usSum + usTmpLen;
        }
    }

    if (0 == usSum)
    {
        return NAS_LCS_CAUSE_SUCCESS;
    }

    usTmpLen = usSum;
    enRslt   = NAS_LCS_PackTL(NAS_LCS_CLIENT_EXT_ID_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeLocEstimateMoLrReq_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLcsQos
 Description     : ����lcs-qos
 Input           : pucEncodeOutMsg              :���������
                   pstTafMsgRecord              :Taf�·���MoLr�������
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeLcsQos
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_PARA_STRU                  *pstMolrPara
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;

    /* ����horizontal-accuracy */
    if (LCS_HOR_ACC_SET_PARAM == pstMolrPara->enHorAccSet)
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_QOS_HOR_ACC_TAG;
        pucEncodeOutMsg[usSum++] = 1;
        pucEncodeOutMsg[usSum++] = pstMolrPara->ucHorAcc;
    }

    /* ����verticalCoordinateRequest */
    if (LCS_VER_REQUESTED == pstMolrPara->enVerReq)
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_QOS_VER_REQ_TAG;
        pucEncodeOutMsg[usSum++] = 0;
    }

    /* ����vertical-accuracy */
    if ((LCS_VER_ACC_SET_PARAM == pstMolrPara->enVerAccSet) && (LCS_VER_REQUESTED == pstMolrPara->enVerReq))
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_QOS_VER_ACC_TAG;
        pucEncodeOutMsg[usSum++] = 1;
        pucEncodeOutMsg[usSum++] = pstMolrPara->ucVerAcc;
    }

    /* ����velocityRequest */
    if (LCS_VEL_NOT_REQUESTED != pstMolrPara->enVelReq)
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_QOS_VEL_REQ_TAG;
        pucEncodeOutMsg[usSum++] = 0;
    }

    /* ���볤��Ϊ0ʱ,˵��QosΪ��,��Я����ѡ��ԪQos */
    if (0 == usSum)
    {
        return NAS_LCS_CAUSE_SUCCESS;
    }
    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(NAS_LCS_MOLR_QOS_TAG, pucEncodeOutMsg, &usTmpLen);

    if(NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeLcsQos_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeMolrType
 Description     : ������ԪMo-lr type
 Input           : pucEncodeOutMsg              :���������
                   enMolrType                   :mo-lr type
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeMolrType
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_MOLR_TYPE_ENUM_UINT8         enMolrType
)
{
    VOS_UINT16                          usSum    = 0;

    *pusIeLen = 0;

    /* ����TLV */
    pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_TYPE_TAG;
    pucEncodeOutMsg[usSum++] = 1;
    pucEncodeOutMsg[usSum++] = enMolrType;

    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLocationMethod
 Description     : ������ԪLocation Method
 Input           : pucEncodeOutMsg              :���������
                   enMethod                     :At�·���Loc method
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LCS_EncodeLocationMethod
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    LCS_MOLR_METHOD_ENUM_UINT8           enMethod
)
{
    NAS_LCS_NW_MOLR_METHOD_ENUM_UINT8   enMoLrMethod;
    VOS_UINT16                          usSum = 0;

    *pusIeLen = 0;
    enMoLrMethod = NAS_LCS_MapLocationMethod(enMethod);

    /* �ж�ת�����Method�Ƿ���Ч */
    if (NAS_LCS_NW_MOLR_METHOD_BUTT == enMoLrMethod)
    {
        return;
    }
    pucEncodeOutMsg[usSum++] = NAS_LCS_MOLR_LOC_METHOD_TAG;
    pucEncodeOutMsg[usSum++] = 1;
    pucEncodeOutMsg[usSum++] = enMoLrMethod;
    *pusIeLen = usSum;
    return;
}

/*****************************************************************************
 Function Name   : NAS_LCS_MapLocationMethod
 Description     : ��TAF��Ϣ�е�Methodת��Ϊ�տ��е�LocationMethod
 Input           : enMethod                             :����ǰ��method
 Output          : NULL
 Return          : NAS_LCS_NW_MOLR_METHOD_ENUM_UINT8    :ת�����method

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_NW_MOLR_METHOD_ENUM_UINT8 NAS_LCS_MapLocationMethod(LCS_MOLR_METHOD_ENUM_UINT8  enMethod)
{
    NAS_LCS_NW_MOLR_METHOD_ENUM_UINT8 enMoLrMethod = NAS_LCS_NW_MOLR_METHOD_BUTT;

    /* ��AT������Я����methodת��Ϊ����methodö�� */
    switch(enMethod)
    {
        case LCS_MOLR_METHOD_AGPS:
            enMoLrMethod = NAS_LCS_NW_MOLR_METHOD_AGPS;
            break;

        case LCS_MOLR_METHOD_AGNSS:
            enMoLrMethod = NAS_LCS_NW_MOLR_METHOD_AGANSS;
            break;

        case LCS_MOLR_METHOD_AGPS_AGNSS:
            enMoLrMethod = NAS_LCS_NW_MOLR_METHOD_AGPS_GANSS;
            break;

        default:
            enMoLrMethod = NAS_LCS_NW_MOLR_METHOD_BUTT;
            break;
    }
    return enMoLrMethod;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLocNtyReslt
 Description     : ����Mtlr location notification Result�տ���Ϣ��Ԫ
 Input           : pucEncodeOutMsg              :���������
                   stEncodeInfo                 :��������Ҫ����Ϣ
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeLocNtyReslt
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;

    /* ����Operation Code */
    pucEncodeOutMsg[usSum++] = NAS_LCS_OPERATION_CODE_TAG;
    pucEncodeOutMsg[usSum++] = 1;
    pucEncodeOutMsg[usSum++] = NAS_LCS_OPERATION_LOC_NOTIFICATION;

    /* ����Parameters */
    enRslt = NAS_LCS_EncodeLocNtfRsp(pucEncodeOutMsg + usSum, &usTmpLen, pstEncodeInfo);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum    = usSum + usTmpLen;
    usTmpLen = usSum;

    /* �����ѡ��ԪSequence */
    enRslt   = NAS_LCS_PackTL(NAS_LCS_SEQUENCE_TAG , pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
       TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeLocNtyReslt_ENUM, LNAS_LCS_EncodeTLFail);
       return NAS_LCS_CAUSE_FAIL;
    }

    usSum     = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeRelCmpIeFacility
 Description     : ����Release Complete�տ���Ϣ��ԪFacility
 Input           : pucEncodeOutMsg              :���������
                   stEncodeInfo                 :��������Ҫ����Ϣ
                   enComponent                  :Component����
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeRelCmpIeFacility
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo,
    NAS_LCS_COMPONENT_ENUM_UINT8        enComponent
)
{
    VOS_UINT16                          usSum    = 0;
    VOS_UINT16                          usTmpLen = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;

    *pusIeLen = 0;

    /* ����Invoke Id */
    if (NAS_LCS_OP_TRUE == pstEncodeInfo->bitOpInvokeId)
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_INVOKE_ID_TAG;
        pucEncodeOutMsg[usSum++] = 1;
        pucEncodeOutMsg[usSum++] = pstEncodeInfo->ucInvokeId;
    }
    else
    {
        /* ֻ��Reject Component�ܲ�Я��Invoke Id, ����Component����Я��Invoke Id */
        if (NAS_LCS_COMPONENT_REJECT == enComponent)
        {
            /* Э��涨��и��INVOKE IDʱ, TAGʹ��NULL */
            pucEncodeOutMsg[usSum++] = NAS_LCS_NULL_TAG;
            pucEncodeOutMsg[usSum++] = 0;
        }
        else
        {
            TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeRelCmpIeFacility_ENUM, LNAS_LCS_MissInvokeId);
            return NAS_LCS_CAUSE_FAIL;
        }
    }

    /* ����Return Rslt Component */
    if (NAS_LCS_COMPONENT_RETURN_RSLT_TAG == enComponent)
    {
        /* ����Location Notification Rsp */
        if (NAS_LCS_OPERATION_LOC_NOTIFICATION == pstEncodeInfo->enOperType)
        {
            /* ����Parameters */
            enRslt = NAS_LCS_EncodeLocNtyReslt(pucEncodeOutMsg + usSum, &usTmpLen, pstEncodeInfo);
            if (NAS_LCS_CAUSE_SUCCESS != enRslt)
            {
                return NAS_LCS_CAUSE_FAIL;
            }
            usSum = usSum + usTmpLen;
        }
    }
    else if(NAS_LCS_COMPONENT_RETURN_ERR_TAG == enComponent)
    {
        /* ����Error Code */
        pucEncodeOutMsg[usSum++] = NAS_LCS_ERROR_CODE_TAG;
        pucEncodeOutMsg[usSum++] = 1;
        pucEncodeOutMsg[usSum++] = (VOS_UINT8)(pstEncodeInfo->enCause & NAS_LCS_MSG_LOW_8_BIT);
    }
    else if(NAS_LCS_COMPONENT_REJECT == enComponent)
    {
        /* ����Problem Code */
        pucEncodeOutMsg[usSum++] = (VOS_UINT8)((pstEncodeInfo->enCause & NAS_LCS_MSG_LOW_16_BIT) >> NAS_LCS_MOVEMENT_8_BITS);
        pucEncodeOutMsg[usSum++] = 1;
        pucEncodeOutMsg[usSum++] = (VOS_UINT8)(pstEncodeInfo->enCause & NAS_LCS_MSG_LOW_8_BIT);
    }
    else
    {
        return NAS_LCS_CAUSE_FAIL;
    }

    /* ����Component Tag��Length */
    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(enComponent, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeRelCmpIeFacility_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum = usSum + usTmpLen;
    *pusIeLen = usSum;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeRelCmpIeFacility
 Description     : ����LOCATION NOTIFICATION RESULT PARA
 Input           : pucEncodeOutMsg              :���������
                   stEncodeInfo                 :��������Ҫ����Ϣ
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeLocNtfRsp
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum    = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT16                          usTmpLen = 0;

    *pusIeLen = 0;

    if (NAS_LCS_OP_TRUE == pstEncodeInfo->bitLocNtfRsp)
    {
        enRslt = NAS_LCS_EncodeVerifyRsp(pucEncodeOutMsg + usSum, &usTmpLen, pstEncodeInfo);
        if (NAS_LCS_CAUSE_SUCCESS == enRslt)
        {
            usSum = usSum + usTmpLen;
        }
        else
        {
            return enRslt;
        }
    }

    usTmpLen = usSum;
    enRslt   = NAS_LCS_PackTL(NAS_LCS_SEQUENCE_TAG , pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
       TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeLocNtfRsp_ENUM, LNAS_LCS_EncodeTLFail);
       return NAS_LCS_CAUSE_FAIL;
    }

    usSum     = usSum + usTmpLen;
    *pusIeLen = usSum;
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeVerifyRsp
 Description     : ����LOCATION NOTIFICATION RESULT PARA�е���ԪverificationResponse
 Input           : pucEncodeOutMsg              :���������
                   stEncodeInfo                 :��������Ҫ����Ϣ
 Output          : pusIeLen                     :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32 NAS_LCS_EncodeVerifyRsp
(
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT16                          *pusIeLen,
    NAS_LCS_ENCODE_INFO_STRU            *pstEncodeInfo
)
{
    VOS_UINT16                          usSum       = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT16                          usTmpLen    = 0;

    *pusIeLen = 0;

    if (LCS_MTLRA_ALLOW == pstEncodeInfo->enLocNtfRsp)
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_VER_RSP_PERMISSON_GRANTED;
    }
    else
    {
        pucEncodeOutMsg[usSum++] = NAS_LCS_VER_RSP_PERMISSON_DENIED;
    }

    usTmpLen = usSum;
    enRslt = NAS_LCS_PackTL(NAS_LCS_VERIFICATION_RSP_TAG, pucEncodeOutMsg, &usTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_EncodeVerifyRsp_ENUM, LNAS_LCS_EncodeTLFail);
        return NAS_LCS_CAUSE_FAIL;
    }

    usSum     = usSum + usTmpLen;
    *pusIeLen = usSum;
    return enRslt;
}

/*****************************************************************************
 Function Name   : NAS_LCS_PackTL
 Description     : ����TAG��LEN
 Input           : pucEncodeOutMsg              :���������
                   stEncodeInfo                 :��������Ҫ����Ϣ
 Output          : pusCodeLen                   :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32  NAS_LCS_PackTL
(
    VOS_UINT8                           ucTag,
    VOS_UINT8                          *pucEncodeOutMsg,
    VOS_UINT16                         *pusCodeLen
)
{
    VOS_UINT8                           aucTmppool[5];
    VOS_UINT8                           ucHeaderLen     = 0;
    VOS_UINT16                          usSum           = 0;
    VOS_UINT16                          usValueLen      = *pusCodeLen;
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt;
    VOS_UINT8                           ucTmpLen        = 0;

    *pusCodeLen = 0;

    /* �����ǰ��û�н����κεĲ����ı���,��������Ϊ0 */
    if (0 == usValueLen)
    {
        pucEncodeOutMsg[usSum++] = ucTag;
        pucEncodeOutMsg[usSum++] = 0;
        *pusCodeLen = usSum;
        return NAS_LCS_CAUSE_SUCCESS;
    }

    aucTmppool[ucHeaderLen++] = ucTag;

    /* �Գ��Ƚ��б��� */
    enRslt = NAS_LCS_EncodeLength(usValueLen, aucTmppool + ucHeaderLen, &ucTmpLen);
    if (NAS_LCS_CAUSE_SUCCESS != enRslt)
    {
        TLPS_PRINT2LAYER_ERROR2(NAS_LCS_PackTL_ENUM, LNAS_LCS_EnocdeLenFail, ucTag, usValueLen);
        return NAS_LCS_CAUSE_FAIL;
    }

    ucHeaderLen = ucHeaderLen + ucTmpLen;

    /* �Ե�ǰ�ִ�������λ(ΪTLԤ�����ռ�)�Ϳ��� */
    (VOS_VOID)VOS_MemMove(pucEncodeOutMsg + ucHeaderLen, pucEncodeOutMsg, usValueLen);

    NAS_LCS_MEM_CPY_S(pucEncodeOutMsg, ucHeaderLen, aucTmppool, ucHeaderLen);

    /*��ǰ�Ѿ�������ִ�����*/
    *pusCodeLen = ucHeaderLen;
    return NAS_LCS_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_LCS_EncodeLength
 Description     : ����LEN
 Input           : pucEncodeOutMsg              :���������
                   usSrcLen                     :��Ԫ��LENֵ
 Output          : pusCodeLen                   :�ѱ��볤��
 Return          : NAS_LCS_CAUSE_ENUM_UINT32    :������

 History         :
    1.leixiantiao 00258641    2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_CAUSE_ENUM_UINT32  NAS_LCS_EncodeLength
(
    VOS_UINT16                           usSrcLen,
    VOS_UINT8                           *pucEncodeOutMsg,
    VOS_UINT8                           *pucCodeLen
)
{
    VOS_UINT8                           ucSum = 0;

    *pucCodeLen = 0;

    /* ����ֻ���������ֱ��뷽ʽ������ȷ���ȵı��뷽ʽû�в��� */
    /* �������ȷ������ʽ�Ķ̸�ʽ�����봦�� */
    if (usSrcLen < NAS_LCS_INDEF_LENGTH_FLAG)
    {
        /* L��V��ֵ */
        pucEncodeOutMsg[ucSum++] = (VOS_UINT8)usSrcLen;
    }
    /* �������ȷ������ʽ�ĳ���ʽ,���봦�� */
    else
    {
        /* С�ڵ���255,������һ�ֽڱ�ʾ */
        if (usSrcLen <= NAS_LCS_MAX_COMPONENT_LENGTH)
        {
            /* L��V��ֵ */
            pucEncodeOutMsg[ucSum] = NAS_LCS_INDEF_LENGTH_FLAG + 1;
            ucSum++;
            pucEncodeOutMsg[ucSum] = (VOS_UINT8)usSrcLen;
            ucSum++;
            *pucCodeLen = ucSum;
        }
        else
        {
            TLPS_PRINT2LAYER_ERROR1(NAS_LCS_EncodeLength_ENUM, LNAS_LCS_EnocdeLenFail, usSrcLen);
            return NAS_LCS_CAUSE_FAIL;
        }
    }

    *pucCodeLen = ucSum;
    return NAS_LCS_CAUSE_SUCCESS;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

