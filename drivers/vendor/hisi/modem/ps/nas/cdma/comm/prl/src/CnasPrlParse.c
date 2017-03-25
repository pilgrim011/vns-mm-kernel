/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasPrlParse.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��08����
  ��������   : NAS 1X&EVDO PRL��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��08��06��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"
#include "CnasPrlParse.h"
#include "CnasPrlMem.h"
#include "Crc.h"
#include "CnasPrlMntn.h"
#include "CnasCcb.h"
#include "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_PRL_PARSE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CNAS_PRL_BIT_TO_BYTE(pBuf, bOffSet, bLen)                                   \
        CNAS_PRL_ExtractBitStringToOctet(&pBuf[bOffSet/CNAS_PRL_BIT_LEN_8_BIT],     \
                                         (VOS_UINT8)bOffSet%CNAS_PRL_BIT_LEN_8_BIT, \
                                         bLen)

#define CNAS_PRL_BIT_TO_WORD(pBuf, bOffSet, bLen)                                   \
        CNAS_PRL_ExtractBitStringToWord(&pBuf[bOffSet/CNAS_PRL_BIT_LEN_8_BIT],      \
                                        (VOS_UINT8)bOffSet%CNAS_PRL_BIT_LEN_8_BIT,  \
                                        bLen)

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/
CNAS_PRL_INFO_STRU                      g_stCnasPrlInfo;    /* �洢PRL��Ϣȫ�ֱ��� */

CNAS_PARSE_ACQ_TYPE_REC_PROC_ENTITY     g_astCnasPrlProcParseAcqTypeRec[] =
{
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_CELLULAR_ANALOG                           , CNAS_PRL_ParseAcqRec_CellularAnalog},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_STANDARD_CHANNELS           , CNAS_PRL_ParseAcqRec_CellularCdmaStandard},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS             , CNAS_PRL_ParseAcqRec_CellularCdmaCustom},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_PREFERRED                   , CNAS_PRL_ParseAcqRec_CellularCdmaPrefered},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_BLOCKS                     , CNAS_PRL_ParseAcqRec_PcsCdmaUsingBlocks},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_CHANNELS                   , CNAS_PRL_ParseAcqRec_PcsCdmaUsingChannels},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_JTACS_CDMA_STANDARD_CHANNELS              , CNAS_PRL_ParseAcqRec_JtacsCdmaStandardChannels},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_JTACS_CDMA_CUSTOM_CHANNELS                , CNAS_PRL_ParseAcqRec_JtacsCdmaCustomChannels},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_2G_BAND_USING_CHANNELS                    , CNAS_PRL_ParseAcqRec_2gBandUsingChannels},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_1X_AND_IS95        , CNAS_PRL_ParseAcqRec_GenericCdma1X},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD               , CNAS_PRL_ParseAcqRec_GenericAcqRecordForHrpd},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_Reserved_FOR_OBSOLETE_IDENTIFICATION      , CNAS_PRL_ParseAcqRec_NotSupportRecType},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_COMMON_ACQ_TABLE_RECORD_FOR_UMB           , CNAS_PRL_ParseAcqRec_ComAcqTabRecordForUmb},
    {(VOS_UINT32)CNAS_PRL_ACQ_TYPE_COMMON_ACQ_RECORD_FOR_UMB                 , CNAS_PRL_ParseAcqRec_ComAcqRecordForUmb},
};

/*****************************************************************************
  4 ��������
*****************************************************************************/
/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : CNAS_PRL_IsAcqRecTabValid
 ��������  : �����¼���Ƿ���Ч
 �������  : pstAcqRecInfo -- ������¼��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ��Ч
             VOS_FALSE -- ��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_IsAcqRecTabValid(
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstAcqRecInfo
)
{
    VOS_UINT32                          i;

    for (i = 0; i < pstAcqRecInfo->usAcqRecordNum; i++)
    {
        if ((VOS_NULL_PTR != pstAcqRecInfo->pastPrlAcqRecord[i])
        &&  (VOS_TRUE     == pstAcqRecInfo->pastPrlAcqRecord[i]->ucAcqValid))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_IsSysRecTabValid
 ��������  : ϵͳ��¼���Ƿ���Ч
 �������  : pstSysRecInfo -- ϵͳ���¼��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ��Ч
             VOS_FALSE -- ��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_IsSysRecTabValid(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstSysRecInfo
)
{
    VOS_UINT32                          i;

    for (i = 0; i < pstSysRecInfo->usSysRecordNum; i++)
    {
        if ((VOS_NULL_PTR != pstSysRecInfo->pstSysRecord)
        &&  (VOS_TRUE     == pstSysRecInfo->pstSysRecord[i].ucSysRecValid))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetPrlInfoAddr
 ��������  : ��ȡ��ǰPRL��Ϣ�׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����PRL��Ϣ�׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_INFO_STRU* CNAS_PRL_GetPrlInfoAddr(VOS_VOID)
{
    return &(g_stCnasPrlInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_CheckPrlCrcChecksum
 ��������  : ��֤CRCУ���
 �������  : pPrl -- prlԭʼ���ݵ�ַ
 �������  : ��
 �� �� ֵ  : CNAS_PRL_PARSE_SUCCESS  �� CRCУ��ɹ�
             CNAS_PRL_PARSE_CRC_FAIL �� CRCУ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��06��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_CheckPrlCrcChecksum(
    VOS_UINT8                          *pPrl
)
{
    VOS_UINT16                          usCrcCalLength;
    VOS_UINT16                          usPrlListCrc;
    VOS_UINT16                          usPrlListSize;
    VOS_UINT16                          usCalcCrc;
    VOS_UINT8                          *pBuff = VOS_NULL_PTR;

    pBuff        = pPrl;

    /* ��ȡPRL list size */
    usPrlListSize = CNAS_PRL_ExtractBitStringToWord(pBuff, 0, CNAS_PRL_BIT_LEN_16_BIT);

    /* See 3.5.5.1 Preferred Roaming List CRC Calculation in C.S0016-D:
       The 16-bit preferred roaming list CRC field PR_LIST_CRC is calculated on all bits of the
       Preferred Roaming List/Extended Preferred Roaming List excluding the bits of the PR_LIST_CRC
       field itself. The generator polynomial for this CRC is g(x) = x16 + x12 + x5 + x0 */
    usCrcCalLength = usPrlListSize - sizeof(VOS_UINT16);

    /* PR_LIST_SIZE - Preferred roaming list size.
       This field is set to the total size, in octets, of the preferred roaming list, including
       the PR_LIST_SIZE and PR_LIST_CRC fields. */
    usPrlListCrc = CNAS_PRL_BIT_TO_WORD(pBuff, (usCrcCalLength * CNAS_PRL_BIT_LEN_8_BIT), CNAS_PRL_BIT_LEN_16_BIT);

    /* ����CRC, length��Ҫת����bit�� */
    usCalcCrc = CRC_CalculateCRC16(pBuff, usCrcCalLength * CNAS_PRL_BIT_LEN_8_BIT);

    if (usPrlListCrc == usCalcCrc)
    {
        return CNAS_PRL_PARSE_SUCCESS;
    }

    return CNAS_PRL_PARSE_CRC_FAIL;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_ExtractBitStringToOctet
 ��������  : �ɸ������ֽ����Ŀ�ʼ��ַ���Լ���Ӧ��bitƫ��������Ӧ���ݽṹ��bit���ȣ������ݵĸ�ֵ
 �������  : pucSrcAddr  -- ��Ӧ��bit�ֽ����ĵ�ַ
             usOffsetPos -- һ���ֽ��е�ƫ��λ��
             usBitLen    -- ��Ҫ��ֵ��bit����
 �������  : ��
 �� �� ֵ  : ת������ֽ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��5��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -e701*/
VOS_UINT8  CNAS_PRL_ExtractBitStringToOctet(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucBitLen
)
{
    VOS_UINT8                          *pucBuffOffset = VOS_NULL_PTR;
    VOS_INT16                           iRemainBitLen;
    VOS_UINT8                           ucExtractByte;
    VOS_UINT8                           ucRemainLen;

    pucBuffOffset = pucSrcAddr;

    iRemainBitLen = (VOS_INT16)(CNAS_PRL_BIT_LEN_8_BIT - (ucOffsetPos + ucBitLen));

    /* ���һ���ֽ�����usOffsetPos��ʣ��bit�ĳ��ȴ��ڵ���usOffsetPos����ֱ���ڸ��ֽ��н���ȡֵ */
    /* ���һ���ֽ�����usOffsetPos��ʣ��bit�ĳ���С��usOffsetPos,����Ҫ����һ���ֽ��н���ȡֵ*/
    if ( iRemainBitLen >= 0 )
    {
        ucExtractByte =  (VOS_UINT8)(((VOS_UINT8)((*pucBuffOffset) << ucOffsetPos)) >> (ucOffsetPos + iRemainBitLen));
    }
    else
    {
        /* ����ʣ��λ */
        ucRemainLen = (VOS_UINT8)(ucBitLen - (CNAS_PRL_BIT_LEN_8_BIT - ucOffsetPos));

        ucExtractByte = (VOS_UINT8)(((*pucBuffOffset) & (0xFF >> ucOffsetPos)) << ucRemainLen);

        pucBuffOffset++;

        /* ���ֽ�ʣ��bit���� */
        ucExtractByte |= (VOS_UINT8)(((*pucBuffOffset) & 0xFF) >> (CNAS_PRL_BIT_LEN_8_BIT - ucRemainLen));
    }

    return ucExtractByte;

}
/*lint +e701*/


/*****************************************************************************
 �� �� ��  : CNAS_PRL_ExtractBitStringToWord
 ��������  : �ɸ������ֽ����Ŀ�ʼ��ַ���Լ���Ӧ��bitƫ��������Ӧ���ݽṹ��bit���ȣ������ݵĸ�ֵ
 �������  : pucSrcAddr  -- ��Ӧ��bit�ֽ����ĵ�ַ
             usOffsetPos -- ��ǰ�ֽڵ�bitƫ��λ��
             usBitLen    -- ��Ҫ��ֵ��bit����
 �������  : ��
 �� �� ֵ  : ת�����˫�ֽ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��5��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -e701*/
VOS_UINT16 CNAS_PRL_ExtractBitStringToWord(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucBitLen
)
{
    VOS_UINT8                          *pucTmpSrc = VOS_NULL_PTR;
    VOS_UINT16                          usExtractWord;
    VOS_UINT16                          usRemainBitLen;

    pucTmpSrc = pucSrcAddr;

    if (ucBitLen > CNAS_PRL_BIT_LEN_16_BIT)
    {
        ucBitLen = CNAS_PRL_BIT_LEN_16_BIT;
    }

    if (ucBitLen <= CNAS_PRL_BIT_LEN_8_BIT)
    {
        /* ����bit lengthС�ڵ���8bit�Ĵ��� */
        usExtractWord = (VOS_UINT16)CNAS_PRL_ExtractBitStringToOctet(pucTmpSrc,
                                                                     ucOffsetPos,
                                                                     ucBitLen);

        return usExtractWord;
    }

    /* �����ȥ��ǰ�ֽ���Чbit��ʣ��bit���� */
    usRemainBitLen = (VOS_UINT16)(ucBitLen - (CNAS_PRL_BIT_LEN_8_BIT - ucOffsetPos));

    /* ��ȡ�׸��ֽ����ݲ��֣����Ƶ���Ӧ�ĸ�λ, �ճ�ʣ��bitλ */
    usExtractWord  = (VOS_UINT16)(((*pucTmpSrc) & (0xFF >> ucOffsetPos)) << usRemainBitLen);

    /* ָ����һ���ֽ� */
    pucTmpSrc++;

    /* ���ʣ�೤�� */
    if (usRemainBitLen > CNAS_PRL_BIT_LEN_8_BIT)
    {
        /* ����ʣ��δȡ���bit */
        usRemainBitLen -= CNAS_PRL_BIT_LEN_8_BIT;

        /* ���ƣ��ճ�ʣ��bitλ */
        usExtractWord |= (VOS_UINT16)((VOS_UINT8)(*pucTmpSrc) << usRemainBitLen);
    }
    else
    {
        /* ���ֽ�ʣ��bit���� */
        usExtractWord |= (VOS_UINT16)(((*pucTmpSrc) & 0xFF) >> (CNAS_PRL_BIT_LEN_8_BIT - usRemainBitLen));

        /* bit�Ѿ�ȡ�꣬��0 */
        usRemainBitLen = 0;
    }

    if (usRemainBitLen > 0)
    {
        pucTmpSrc++;

        /* ���ֽ�ʣ��bit���� */
        usExtractWord |= (VOS_UINT16)(((*pucTmpSrc) & 0xFF) >> (CNAS_PRL_BIT_LEN_8_BIT - usRemainBitLen));
    }

    /* ����ת�����ֽڵĴ��� */
    return usExtractWord;
}
/*lint +e701*/


/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_CellularCdmaStandard
 ��������  : ����һ��acquisition record��¼,Acquisition Record Type����Ϊ
             Cellular CDMA (Standard Channels)
 �������  : pucSrc - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ��
 �������  : pastPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����
 �� �� ֵ  : VOS_TRUE  -- �����ɹ�
             VOS_FALSE -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularCdmaStandard(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulSize;
    VOS_UINT32                          ulCurBitOffset;

    VOS_UINT32                          ulAcqRecordLength;
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev;

    ulAcqRecordLength  = 0;
    enSsprPRev         = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev;

    /*
    PRL��ʽ:
    Type-specific Record    Length (bits)
    A_B                           2
    PRI_SEC                       2

    EPRL��ʽ:
    Type-specific Record          Length (bits)
    LENGTH                        8
    A_B                           2
    PRI_SEC                       2
    RESERVED                      4
    */

    /* �����ڴ� */
    ulSize       = sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_CellularCdmaStandard: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* ���õ�ǰ�ֽ��е�bitƫ�� */
    ulCurBitOffset = ulOffsetPos;

    /* ���õ�ǰ����ָ�� */
    pucPrlBuff = pucSrc;

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_STANDARD_CHANNELS;

    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        /* ��ȡ�����¼����*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        /* ����length�� */
        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /* ���� A_B field */
    pstAcqRecord->u.stCellularStandardSys.enSysSelType =
        (CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8)CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_2_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT;

    /* ���� PRI_SEC field */
    pstAcqRecord->u.stCellularStandardSys.enChanSelType =
        (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_ENUM_UINT8)CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_2_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT;


    /* ��Acq_valid */
    if ((CNAS_PRL_SYS_SEL_TYPE_RESERVED           == pstAcqRecord->u.stCellularStandardSys.enSysSelType)
     || (CNAS_PRL_STANDARD_CHAN_SEL_TYPE_RESERVED == pstAcqRecord->u.stCellularStandardSys.enChanSelType))
    {
        CNAS_ERROR_LOG2(UEPS_PID_XSD,
                        "CNAS_PRL_ParseAcqRec_CellularCdmaStandard: illegal parameter, enSysSelType = %d, enChanSelType = %d",
                        pstAcqRecord->u.stCellularStandardSys.enSysSelType,
                        pstAcqRecord->u.stCellularStandardSys.enChanSelType);

        pstAcqRecord->ucAcqValid = VOS_FALSE;
    }
    else
    {
        pstAcqRecord->ucAcqValid = VOS_TRUE;
    }


    /* ���ر���¼�е�bitƫ�� */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        *pulCurOffsetPos = ulCurBitOffset;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_CellularCdmaCustom
 ��������  : ����һ��acquisition record��¼,,Acquisition Record Type����Ϊ
             Cellular CDMA (Custom Channels)
 �������  : pucSrc - �����bit��
             usOffsetPos - ��Ӧ��һ���ֽ��е�ƫ��λ��
 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����
 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularCdmaCustom(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulSize;
    VOS_UINT8                           ucNumChans;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           i;

    VOS_UINT32                          ulAcqRecordLength;
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev;

    ulAcqRecordLength  = 0;
    enSsprPRev         = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev;

    /*
    PRL��ʽ:
    Type-specific Record    Length (bits)
    NUM_CHANS               5
    NUM_CHANS occurrences of the following field:
    CHAN                   11

    EPRL��ʽ:
    Type-specific Record    Length (bits)
    LENGTH                  8
    NUM_CHANS               5
    NUM_CHANS occurrences of the following field:
    CHAN                    11
    RESERVED                0 to 7
    */

    /* ���õ�ǰ����ָ�� */
    pucPrlBuff  = pucSrc;

    /* ���õ�ǰ�ֽ��е�bitƫ�� */
    ulCurBitOffset = ulOffsetPos;



    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        /* ��ȡ�����¼����*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        /* ����length�� */
        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /* ����NUM_CHANS */
    ucNumChans = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT;

    /* �����ڴ� */
    ulSize       = ucNumChans * sizeof(VOS_UINT16) + sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_CellularCdmaCustom: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS;

    /* ����NUM_CHANS����forѭ��������CHAN */
    pstAcqRecord->u.stCelluarCustomSys.ucNumOfChans = ucNumChans;

    /* ���� CHAN field */
    for (i = 0; i < ucNumChans; i++)
    {
        pstAcqRecord->u.stCelluarCustomSys.ausChan[i] =
            CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_11_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_11_BIT;
    }

    /* ��Acq_valid */
    pstAcqRecord->ucAcqValid = VOS_TRUE;

    /* ���ر���¼�е�bitƫ�� */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        *pulCurOffsetPos = ulCurBitOffset;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_CellularCdmaPrefered
 ��������  : ����һ��acquisition record��¼,,Acquisition Record Type����Ϊ
             Cellular CDMA Preferred
 �������  : pucSrc - �����bit��
             ulOffsetPos - ��Ӧ��һ���ֽ��е�ƫ��λ��
 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����
 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularCdmaPrefered(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulSize;
    VOS_UINT32                          ulCurBitOffset;

    VOS_UINT32                          ulAcqRecordLength;
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev;

    ulAcqRecordLength  = 0;
    enSsprPRev         = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev;

    /*
    PRL��ʽ:
    Type-specific Record        Length (bits)
    A_B                         2

    EPRL��ʽ:
    Type-specific Record        Length (bits)
    LENGTH                      8
    A_B                         2
    RESERVED                    6
    */

    /* �����ڴ� */
    ulSize       = sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_CellularCdmaPrefered: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* ���õ�ǰ����ָ�� */
    pucPrlBuff     = pucSrc;

    /* ���õ�ǰ�ֽ��е�bitƫ�� */
    ulCurBitOffset = ulOffsetPos;

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_PREFERRED;

    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        /* ��ȡ�����¼����*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        /* ����length�� */
        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /*���� A_B field*/
    pstAcqRecord->u.stCellularPreSys.enSysSelType =
        (CNAS_PRL_SYS_SEL_TYPE_ENUM_UINT8)CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_2_BIT);

    ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT;

    /* ��Acq_valid */
    if (CNAS_PRL_SYS_SEL_TYPE_RESERVED == pstAcqRecord->u.stCellularPreSys.enSysSelType)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XSD,
                        "CNAS_PRL_ParseAcqRec_CellularCdmaPrefered: illegal parameter enSysSelType = %d",
                        pstAcqRecord->u.stCellularStandardSys.enSysSelType);

        pstAcqRecord->ucAcqValid = VOS_FALSE;
    }
    else
    {
        pstAcqRecord->ucAcqValid = VOS_TRUE;
    }

    /* ���ر���¼�е�bitƫ�� */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        *pulCurOffsetPos = ulCurBitOffset;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_PcsCdmaUsingBlocks
 ��������  : ����һ��acquisition record��¼,,Acquisition Record Type����Ϊ
             PCS CDMA (Using Blocks)

 �������  : pucSrc - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ��

 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����

 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_PcsCdmaUsingBlocks(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    C.S0016-D
    3.5.5.2.2.5 PCS CDMA System Acquisition (Using Blocks) Record

    Type-specific Record        Length (bits)
    NUM_BLOCKS                  3
    NUM_BLOCKS occurrences of the following field:
    BLOCK                       3
    RESERVED                    0 to 7
    */

    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulSize;
    VOS_UINT8                           ucNumBlock;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           i;

    VOS_UINT32                          ulAcqRecordLength;
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev;

    ulAcqRecordLength  = 0;
    enSsprPRev         = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev;

    /* ���õ�ǰ����ָ�� */
    pucPrlBuff     = pucSrc;

    /* ���õ�ǰ�ֽ��е�bitƫ�� */
    ulCurBitOffset = ulOffsetPos;

    /* ���� LENGTH field */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        /* ��ȡ�����¼����*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /* ���� NUM_BLOCKS field */
    ucNumBlock      = CNAS_PRL_BIT_TO_BYTE(pucSrc, ulCurBitOffset, CNAS_PRL_BIT_LEN_3_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_3_BIT;

    /* �����ڴ� */
    ulSize          = ucNumBlock * sizeof(VOS_UINT8) + sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord    = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_PcsCdmaUsingBlocks: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_BLOCKS;

    /* ����NUM_BLOCKS����forѭ��������BLOCK */
    pstAcqRecord->u.stPcsBlocksSys.ucNumOfBlocks  = ucNumBlock;

    /* ���� CHAN field */
    for (i = 0; i < ucNumBlock; i++)
    {
        pstAcqRecord->u.stPcsBlocksSys.aenBlock[i] =
            CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_3_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_3_BIT;
    }

    /* ��Acq_valid */
    if (0 == pstAcqRecord->u.stPcsBlocksSys.ucNumOfBlocks)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_PcsCdmaUsingBlocks: ucNumOfBlocks = 0");

        pstAcqRecord->ucAcqValid = VOS_FALSE;
    }
    else
    {
        /* ��Acq_valid */
        pstAcqRecord->ucAcqValid = VOS_TRUE;
    }

    /* ���ص�ǰbitƫ�� */
    *pulCurOffsetPos = ulCurBitOffset;

    /* ���ر���¼�е�bitƫ�� */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        *pulCurOffsetPos = ulCurBitOffset;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_PcsCdmaUsingChannels
 ��������  : ����һ��acquisition record��¼,,Acquisition Record Type����Ϊ
             PCS CDMA (Using Channels)

 �������  : pucSrc - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ��

 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����

 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_PcsCdmaUsingChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    C.S0016-D
    3.5.5.2.2.6 PCS CDMA System Acquisition (Using Channels) Record

    Type-specific Record        Length (bits)
    NUM_CHANS                   5
    NUM_CHANS occurrences of the following field:
    CHAN                        11
    RESERVED                    0 to 7
    */

    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulSize;
    VOS_UINT8                           ucNumChan;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           i;

    VOS_UINT32                          ulAcqRecordLength;
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enSsprPRev;

    ulAcqRecordLength  = 0;
    enSsprPRev         = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev;

    pucPrlBuff      = pucSrc;

    ulCurBitOffset  = ulOffsetPos;

    /* ���� LENGTH field */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        /* ��ȡ�����¼����*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset  += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /* ���� NUM_BLOCKS field */
    ucNumChan       = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT;

    /* �����ڴ� */
    ulSize          = ucNumChan * sizeof(VOS_UINT16) + sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord    = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_PcsCdmaUsingChannels: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_PCS_CDMA_USING_CHANNELS;

    /* ����NUM_BLOCKS����forѭ��������BLOCK */
    pstAcqRecord->u.stPcsChannelsSys.ucNumOfChans   = ucNumChan;

    /* ���� CHAN field */
    for (i = 0; i < ucNumChan; i++)
    {
        pstAcqRecord->u.stPcsChannelsSys.ausChan[i] =
            CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_11_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_11_BIT;
    }

    /* ��Acq_valid */
    pstAcqRecord->ucAcqValid = VOS_TRUE;

    /* ���ر���¼�е�bitƫ�� */
    if (CNAS_PRL_SSPR_P_REV_3 == enSsprPRev)
    {
        *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        *pulCurOffsetPos = ulCurBitOffset;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_GenericCdma1X
 ��������  : ����һ��acquisition record��¼,,Acquisition Record Type����Ϊ
             Generic Acquisition Record for cdma2000 1x and IS-95

 �������  : pucSrc - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ

 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����

 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_GenericCdma1X(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    EPRL��ʽ(��record������EPRL):
    Type-specific Record            Length (bits)
    LENGTH/2 occurrences of the following two fields:
    BAND_CLASS                      5
    CHANNEL_NUMBER                  11
    */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLen;
    VOS_UINT16                          usSize;
    VOS_UINT8                           i;

    /* ���õ�ǰ�ֽ��е�bitƫ�� */
    ulCurBitOffset = ulOffsetPos;

    /* ���õ�ǰ����ָ�� */
    pucPrlBuff     = pucSrc;

    ucLen = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;

    /* ����record�ڴ�ռ�, �����ڴ� */
    usSize = ((ucLen/2) * sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)) + sizeof(CNAS_PRL_ACQ_RECORD_STRU);

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(usSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_GenericCdma1X: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType = CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_1X_AND_IS95;

    pstAcqRecord->u.st1xAndIs95Sys.ucNumOfChans = ucLen/2;

    for (i = 0; i < (ucLen/2); i++)
    {
        /* ���� BAND_CLASS field */
        pstAcqRecord->u.st1xAndIs95Sys.astFreq[i].enBandClass =
            (CNAS_PRL_BAND_CLASS_ENUM_UINT16)CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);
        ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT;

        /* ���� CHANNEL_NUMBER */
        pstAcqRecord->u.st1xAndIs95Sys.astFreq[i].usChannel =
            CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_11_BIT);
        ulCurBitOffset += CNAS_PRL_BIT_LEN_11_BIT;
    }

    pstAcqRecord->ucAcqValid = VOS_TRUE;

    *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ucLen * CNAS_PRL_BIT_LEN_8_BIT;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_CellularAnalog
 ��������  : ����һ��acquisition record��¼,Acquisition Record Type����Ϊcellular
             analog record type
 �������  : pucSrc - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ��

 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����

 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_CellularAnalog(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
      PRL��ʽ:
      A_B                               2

      EPRL��ʽ:
      Type-specific Record            Length (bits)
      LENGTH                            8
      A_B                               2
      RESERVED                          6
    */

    /* cellular analog���Ͳ�֧�֣���������Ȼ��ҪΪ������ռ䲢�����record bitƫ�� */
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;

    VOS_UINT32                          ulAcqRecordLength;
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;

    pucPrlBuff         = pucSrc;
    ulAcqRecordLength  = 0;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_CellularAnalog: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    ulCurBitOffset = ulOffsetPos;

    /* �����record bitƫ�� */
    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        /* ��ȡ�����¼����*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset += (CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT);
    }
    else
    {
        ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT;
    }

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_CELLULAR_ANALOG;

    /* �øü�¼Ϊ��Ч */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_JtacsCdmaStandardChannels
 ��������  : ����һ��acquisition record��¼,Acquisition Record Type����JTACS
             CDMA standard channels
 �������  : pucSrc - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ��

 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����

 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_JtacsCdmaStandardChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
      PRL��ʽ:
      A_B                               2
      PRI_SEC                           2

      EPRL��ʽ:
      Type-specific Record            Length (bits)
      LENGTH                            8
      A_B                               2
      PRI_SEC                           2
      RESERVED                          4
    */

    /* JTACS CDMA standard channels���Ͳ�֧�֣���������Ȼ��ҪΪ������ռ䲢�����record bitƫ�� */
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;

    VOS_UINT32                          ulAcqRecordLength;
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;

    pucPrlBuff         = pucSrc;
    ulAcqRecordLength  = 0;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_JtacsCdmaStandardChannels: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    ulCurBitOffset = ulOffsetPos;

    /* �����record bitƫ�� */
    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        /* ��ȡ�����¼����*/
        ulAcqRecordLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset += (CNAS_PRL_BIT_LEN_8_BIT + ulAcqRecordLength * CNAS_PRL_BIT_LEN_8_BIT);

    }
    else
    {
        ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT * 2;
    }

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_JTACS_CDMA_STANDARD_CHANNELS;

    /* �øü�¼Ϊ��Ч */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;


}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_JtacsCdmaCustomChannels
 ��������  : ����һ��acquisition record��¼,Acquisition Record Type����JTACS
             CDMA custom channels
 �������  : pucSrc - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ��

 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����

 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_JtacsCdmaCustomChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
     PRL��ʽ:
     NUM_CHANS                          5
     NUM_CHANS occurrences of the following field:
     CHAN                               11

     EPRL��ʽ:
     LENGTH                             8
     Type-specific Record            Length (bits)
     NUM_CHANS                          5
     NUM_CHANS occurrences of the following field:
     CHAN                               11
     RESERVED                           0 to 7
     */

    /* JTACS CDMA Custom channels���Ͳ�֧�֣���������Ȼ��ҪΪ������ռ䲢�����record bitƫ�� */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucNumChans;
    VOS_UINT8                           ucLength;

    pucPrlBuff      = pucSrc;

    ulCurBitOffset  = ulOffsetPos;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_JtacsCdmaCustomChannels: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        ucLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT + (ucLength * CNAS_PRL_BIT_LEN_8_BIT);
    }
    else
    {
        /* ��ȡPRL��ʽ��NUM_CHANS��Ŀ */
        ucNumChans = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT + (ucNumChans * CNAS_PRL_BIT_LEN_11_BIT);
    }

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_JTACS_CDMA_CUSTOM_CHANNELS;

    /* �øü�¼Ϊ��Ч */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_2gBandUsingChannels
 ��������  : ����һ��acquisition record��¼,Acquisition Record Type����2G BAND
             USING CHANNELS
 �������  : pucSrc - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ��

 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����

 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_2gBandUsingChannels(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
     PRL��ʽ:
     NUM_CHANS                          5
     NUM_CHANS occurrences of the following field:
     CHAN                               11

     EPRL��ʽ:
     LENGTH                             8
     NUM_CHANS                          5
     NUM_CHANS occurrences of the following field:
     CHAN                               11
     RESERVED                           0 to 7
     */

    /* JTACS CDMA Custom channels���Ͳ�֧�֣������Ϊ������ռ䲢�������������� */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucNumChans;
    VOS_UINT8                           ucLength;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_2gBandUsingChannels: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    pucPrlBuff      = pucSrc;

    ulCurBitOffset  = ulOffsetPos;

    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        ucLength = CNAS_PRL_BIT_TO_BYTE(pucSrc, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT + (ucLength * CNAS_PRL_BIT_LEN_8_BIT);
    }
    else
    {
        /* ��ȡPRL��ʽ��NUM_CHANS��Ŀ */
        ucNumChans = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT + (ucNumChans * CNAS_PRL_BIT_LEN_11_BIT);
    }

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_2G_BAND_USING_CHANNELS;

    /* �øü�¼Ϊ��Ч */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_GenericAcqRecordForHrpd
 ��������  : ����һ��acquisition record��¼,Acquisition Record Type����Generic
             acquisition record for HRPD

 �������  : pucSrc - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ��

 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����

 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��6��
    ��    ��   : d00212987
    �޸�����   : EVDO HSD Phase0

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_GenericAcqRecordForHrpd(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
     EPRL��ʽ:
     LENGTH                             8
     Type-specific                      8*LENGTH
     --------------------------------------------------------------------
     LENGTH                             8
     LENGTH/2                           occurrences of the following two fields:
     BAND_CLASS                         5
     CHANNEL_NUMBER                     11
     */

    /* Generic acquisition record for HRPD����ֻ֧��EPRL */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLength;
    VOS_UINT32                          ulSize;
    VOS_UINT8                           i;

    pucPrlBuff      = pucSrc;

    ulCurBitOffset  = ulOffsetPos;

    /* ���� LENGTH field */
    if (CNAS_PRL_SSPR_P_REV_3 != CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        /* ��֧��PRL */
        return VOS_FALSE;
    }

    ucLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

    /* ����Hrpd��������ռ�ڴ� �ṹ���С + Freq ���ִ��� */
    ulSize       = sizeof(CNAS_PRL_ACQ_RECORD_STRU) + ((ucLength / 2) * sizeof(VOS_UINT32));

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_GenericAcqRecordForHrpd: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD;

    pstAcqRecord->u.stHrpdSys.ucNumOfChans = (ucLength/2);
    ulCurBitOffset  += CNAS_PRL_BIT_LEN_8_BIT;

    /* ���� CHAN field */
    for (i = 0; i < pstAcqRecord->u.stHrpdSys.ucNumOfChans; i++)
    {
        /* Ƶ�� */
        pstAcqRecord->u.stHrpdSys.astFreq[i].enBandClass =
            CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT;

        /* Ƶ�� */
        pstAcqRecord->u.stHrpdSys.astFreq[i].usChannel   =
            CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_11_BIT);

        ulCurBitOffset += CNAS_PRL_BIT_LEN_11_BIT;
    }

    /* ��Acq_valid */
    pstAcqRecord->ucAcqValid = VOS_TRUE;

    *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT + ucLength * CNAS_PRL_BIT_LEN_8_BIT;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_ComAcqTabRecordForUmb
 ��������  : ����һ��acquisition record��¼,Acquisition Record Type����Common
             Acquisition Table Record for UMB

 �������  : pucSrc - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ��

 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����
 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_ComAcqTabRecordForUmb(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
       EPRL��ʽ:
       LENGTH                           8
       Type-specific                    8*LENGTH
       --------------------------------------------------------------------
       LENGTH                           8
       LENGTH/2                         occurrences of the following fields:
       UMB_ACQ_PROFILE                  6
       FFT_SIZE                         4
       CYCLIC_PREFIX_LENGTH             3
       NUM_GUARD_SUBCARRIERS            7
       RESERVED                         0 to 7
    */

    /* Common Acquisition Table Record for UMB���Ͳ�֧�֣������Ϊ������ռ䲢�����record bitƫ�� */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLength;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_ComAcqTabRecordForUmb: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    pucPrlBuff       = pucSrc;

    ulCurBitOffset   = ulOffsetPos;

    ucLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

    ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT + (ucLength * CNAS_PRL_BIT_LEN_8_BIT);

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_COMMON_ACQ_TABLE_RECORD_FOR_UMB;

    /* �øü�¼Ϊ��Ч */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_ComAcqRecordForUmb
 ��������  : ����һ��acquisition record��¼,Acquisition Record Type����Common
             Acquisition Record for UMB

 �������  : pucSrc - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ��

 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����

 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_ComAcqRecordForUmb(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
       EPRL��ʽ:
       LENGTH                           8
       Type-specific                    8*LENGTH
       --------------------------------------------------------------------
       NUM_UMB_BLOCKS                   6
       NUM_UMB_BLOCKS                   occurrences of the following fields:
       BAND_CLASS                       8
       CHANNEL_NUMBER                   16
       UMB_ACQ_TABLE_PROFILE            6
       RESERVED                         0 to 7
    */

    /* Common Acquisition Record for UMB���Ͳ�֧�֣������Ϊ������ռ䲢�����record bitƫ�� */
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLength;

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_ComAcqRecordForUmb: mem alloc fail");

        return VOS_FALSE;
    }

    *pstPrlAcqRecord = pstAcqRecord;

    pucPrlBuff       = pucSrc;

    ulCurBitOffset   = ulOffsetPos;

    ucLength = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);

    ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT + (ucLength * CNAS_PRL_BIT_LEN_8_BIT);

    /* ���ò����¼���� */
    pstAcqRecord->enAcqType  = CNAS_PRL_ACQ_TYPE_COMMON_ACQ_RECORD_FOR_UMB;

    /* �øü�¼Ϊ��Ч */
    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseAcqRec_NotSupportRecType
 ��������  : ����һ��acquisition record��¼,Acquisition Record Type���Ͳ�֧��

 �������  : pucSrc         - �����bit��
             usOffsetPos    - ��Ӧ��һ���ֽ��е�ƫ��λ��

 �������  : pstPrlAcqRecord - ����Ĳ����¼���ݽṹ
             pulCurOffSetPos - ���ر���¼�е�bitƫ����

 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��8��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseAcqRec_NotSupportRecType(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    VOS_UINT8                          *pucPrlBuff   = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLen;

    /* ����REV1�����ڲ�ͬ���ͣ����ݳ���û����ȷ���壬�������ֱ�ӷ���ʧ�� */
    if (CNAS_PRL_SSPR_P_REV_1 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_NotSupportRecType: record type is unknown!");

        *pstPrlAcqRecord = VOS_NULL_PTR;

        return VOS_FALSE;
    }

    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_NotSupportRecType: record type is unknown!");

    pstAcqRecord = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(sizeof(CNAS_PRL_ACQ_RECORD_STRU));

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseAcqRec_JtacsCdmaStandardChannels: mem alloc fail");

        *pstPrlAcqRecord = VOS_NULL_PTR;

        return VOS_FALSE;
    }

    /*
      EPRL��ʽ:
      LENGTH                           8
      Type-specific                    8*LENGTH
    */

    *pstPrlAcqRecord = pstAcqRecord;

    /* ���õ�ǰ�ֽ��е�bitƫ�� */
    ulCurBitOffset           = ulOffsetPos;

    /* ���õ�ǰ����ָ�� */
    pucPrlBuff               = pucSrc;

    /* ��ȡ��֧�ֵĲ������͵����ݳ��� */
    ucLen                    = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
    ulCurBitOffset          += CNAS_PRL_BIT_LEN_8_BIT + ucLen * CNAS_PRL_BIT_LEN_8_BIT;


    pstAcqRecord->ucAcqValid = VOS_FALSE;

    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseExAcqRecTbl
 ��������  : ��ÿһ�������¼������
 �������  : enAcqType - �����¼����
             pucSrc    - �����ԭʼ����
 �������  : pstPrlAcqRecord - ����������ݽṹ
 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��8��14��
    ��    ��   : y00245242
    �޸�����   : DTS2015030604458
*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseExAcqRecTbl(
    CNAS_PRL_ACQ_TYPE_ENUM_UINT8        enAcqType,
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_ACQ_RECORD_STRU          **pstPrlAcqRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    VOS_UINT32                                    i;
    VOS_UINT32                                    ulRslt;
    CNAS_PRL_PARSE_ACQ_TYPE_REC_PROC_FUNC_PTR     pParseAcqTypeRecProcFunc = VOS_NULL_PTR;

    ulRslt = VOS_FALSE;

    /* ���ݳ�����gastCnasProcParseAcqTypeRec���������б��ʼ������ */
    for (i = 0; i < (sizeof(g_astCnasPrlProcParseAcqTypeRec)/sizeof(CNAS_PARSE_ACQ_TYPE_REC_PROC_ENTITY)); i++)
    {
        if (enAcqType == g_astCnasPrlProcParseAcqTypeRec[i].enAcqType)
        {
            pParseAcqTypeRecProcFunc = g_astCnasPrlProcParseAcqTypeRec[i].pParseAcqTypeRecProcFunc;
            break;
        }
    }

    /* ���ҳɹ�ʱ���ó�ʼ���������г�ʼ�� */
    if (VOS_NULL_PTR != pParseAcqTypeRecProcFunc)
    {
        ulRslt = pParseAcqTypeRecProcFunc(pucSrc, ulOffsetPos, pstPrlAcqRecord, pulCurOffsetPos);
    }
    else
    {
        /* �Բ�֧�ֵ����������� */
        ulRslt = CNAS_PRL_ParseAcqRec_NotSupportRecType(pucSrc, ulOffsetPos, pstPrlAcqRecord, pulCurOffsetPos);
    }

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_AddCTCCCustomizeFreqListIntoAcqRec
 ��������  : ���й������Զ���Ƶ����뵽�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_VOID CNAS_PRL_AddCTCCCustomizeFreqListIntoAcqRec(VOS_VOID)
{
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstCustFreqList = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_INFO_STRU                          *pstAcqRecInfo = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT32                                              ulSize;
    VOS_UINT16                                              i;

    pstCustFreqList                =  CNAS_CCB_GetCTCCCustomizeFreqList();

    pstAcqRecInfo                  = &(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo);
    pstAcqRecInfo->usAcqRecordNum++;

    /* �����ڴ� */
    ulSize                             = (pstCustFreqList->usFreqNum) * sizeof(VOS_UINT16) + sizeof(CNAS_PRL_ACQ_RECORD_STRU);
    pstAcqRecord                       = (CNAS_PRL_ACQ_RECORD_STRU *)CNAS_PRL_Malloc(ulSize);

    if (VOS_NULL_PTR == pstAcqRecord)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_AddCTCCCustomizeFreqListIntoAcqRec: mem alloc fail");

        return;
    }

    pstAcqRecInfo->pastPrlAcqRecord[pstAcqRecInfo->usAcqRecordNum - 1] = pstAcqRecord;

    pstAcqRecord->enAcqType            = CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS;
    pstAcqRecord->ucAcqValid           = VOS_TRUE;
    pstAcqRecord->u.stCelluarCustomSys.ucNumOfChans = (VOS_UINT8)(pstCustFreqList->usFreqNum);

    for (i = 0;i < pstCustFreqList->usFreqNum;i++)
    {
        pstAcqRecord->u.stCelluarCustomSys.ausChan[i] = pstCustFreqList->astFreqList[i].usChannel;
    }
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParsePrlAcqRec
 ��������  : ����һ��acquisition record��¼
 �������  : pucSrc:ԭʼbit����
             pstPrlAcqRecord:�������acquisition record
 �������  : pulBitOffset:�������bitƫ����
 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��7��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified
*****************************************************************************/
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlAcqRec(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    VOS_UINT32                         *pulCurOffSetPos
)
{
    VOS_UINT8                                              *pucPrlBuff    = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_INFO_STRU                          *pstAcqRecInfo = VOS_NULL_PTR;
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstCustFreqList = VOS_NULL_PTR;
    CNAS_PRL_ACQ_TYPE_ENUM_UINT8                            enAcqType;
    VOS_UINT8                                               ucBitLen;
    VOS_UINT32                                              ulCurBitOffset;
    VOS_UINT32                                              ulAcqBitOffset;
    VOS_UINT32                                              i;

    pstCustFreqList =  CNAS_CCB_GetCTCCCustomizeFreqList();

    /* ��ȡ��Ϣͷ�н�������ACQ_NUMS */
    pstAcqRecInfo                  = &(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo);
    pstAcqRecInfo->usAcqRecordNum  = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.usNumAcqRecs;


    /*
    ����CNAS_PRL_SSPR_P_REV_1���ο�C.S0016 3.5.5.2.1.1
    Acquisition Record  Field Length (bits)
    ACQ_TYPE            4

    ����CNAS_PRL_SSPR_P_REV_3���ο�C.S0016 3.5.5.2.2
    Type-specific     Record Length (bits)
    ACQ_TYPE          8
    ���ߵĳ����ǲ�һ����
    */
    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        ucBitLen = CNAS_PRL_BIT_LEN_8_BIT;
    }
    else
    {
        ucBitLen = CNAS_PRL_BIT_LEN_4_BIT;
    }

    pucPrlBuff     = pucSrc;
    ulCurBitOffset = ulOffsetPos;

    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstAcqRecInfo->usAcqRecordNum,CNAS_PRL_ACQ_RECORD_MAX_NUM); i++)
    {
        /* ����ACQ_TYPE */
        enAcqType       = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, ucBitLen);
        ulCurBitOffset += ucBitLen;

        ulAcqBitOffset  = 0;

        /* ����enAcqType����g_astCnasPrlProcParseAcqTypeRec�����н��� */
        if (VOS_TRUE != CNAS_PRL_ParseExAcqRecTbl(enAcqType,
                                                  pucPrlBuff,
                                                  ulCurBitOffset,
                                                  &(pstAcqRecInfo->pastPrlAcqRecord[i]),
                                                  &ulAcqBitOffset))
        {
            return CNAS_PRL_PARSE_ACQ_RECORD_FAIL;
        }

        ulCurBitOffset = ulAcqBitOffset;
    }

    /* �������ϵͳ��¼����Ч������ΪPRL����Ч */
    if (VOS_FALSE == CNAS_PRL_IsAcqRecTabValid(pstAcqRecInfo))
    {
        return CNAS_PRL_PARSE_ACQ_RECORD_FAIL;
    }

    if ( (CNAS_PRL_SSPR_P_REV_1 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
      && (VOS_TRUE == pstCustFreqList->ucEnableFlg) )
    {
        CNAS_PRL_AddCTCCCustomizeFreqListIntoAcqRec();
    }

    /* ���������¼��Ϣ */
    CNAS_PRL_LogAcqRecInfo(pstAcqRecInfo);

    /* ���ػ�ȡ���¼��ƫ�� */
    *pulCurOffSetPos    = ulCurBitOffset;

    return CNAS_PRL_PARSE_SUCCESS;

}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseSysIdRec_1X
 ��������  : ����Type-specific system ID record��¼
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_ParseSysIdRec_1X(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_SYS_TYPE_1X_IS95_ID_STRU  *pst1xAndIs95Id,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    Table 3.5.5.3.2-2 Type-specific system ID record
    System ID Record Field          Length (bits)
    RESERVED                        1
    NID_INCL                        2
    SID                             15
    NID                             0 or 16
    */
    VOS_UINT8                          *pucPrBuff    = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;

    /* ��ʼ������ */
    pucPrBuff      = pucSrc;
    ulCurBitOffset = ulOffsetPos;

    /* ����RESERVED */
    ulCurBitOffset += CNAS_PRL_BIT_LEN_1_BIT;

    /* ����NID_INCL */
    pst1xAndIs95Id->enNidIncl = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_2_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_2_BIT;

    /* ����SID */
    pst1xAndIs95Id->usSid = CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_15_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_15_BIT;

    /* ����NID */
    if (CNAS_PRL_NID_INCL == pst1xAndIs95Id->enNidIncl)
    {
        pst1xAndIs95Id->usNid = CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_16_BIT);
        ulCurBitOffset += CNAS_PRL_BIT_LEN_16_BIT;
    }
    else if (CNAS_PRL_NID_NOT_INCL_WILD_CARD == pst1xAndIs95Id->enNidIncl)
    {
        pst1xAndIs95Id->usNid           = CNAS_PRL_WILDCARD_NID;
    }
    else if (CNAS_PRL_NID_NOT_INCL_PLUBLIC_SYSTEM == pst1xAndIs95Id->enNidIncl)
    {
        pst1xAndIs95Id->usNid           = 0;
    }
    else
    {
        /* NID included is reserved */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseSysIdRec_1X:  enNidIncl is illegal!");

        pst1xAndIs95Id->usNid = CNAS_PRL_WILDCARD_NID;
    }

    /* ��¼������¼��ƫ��ֵ */
    *pulCurOffsetPos = ulCurBitOffset;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseSubnetComm
 ��������  : ����Type-specific system ID record��¼
 �������  : pucSrc       : EPRL ����
             ulOffsetPos  : SubnetCom��Ա�ͷ������
             pstIs586Id   : Subnet��ַ

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��3��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_ParseSubnetComm(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_SYS_TYPE_HRPD_ID_STRU     *pstIs586Id
)
{
    VOS_UINT8                          *pucPrBuff       = VOS_NULL_PTR;
    VOS_UINT8                          *pucSubnetCom    = VOS_NULL_PTR;
    VOS_UINT32                          ulSubnetComOffset;

    /*
    Table 3.5.5.3.2.1-1 Common Subnet Record
    System ID Record Field      Length (bits)
    RESERVED                    4
    SUBNET_COMMON_LENGTH        4
    SUBNET_COMMON               8  *    SUBNET_COMMON_LENGTH
    */

    pucPrBuff = pucSrc;

    /* ��ȡSubnetComm�ڴ�����������ʼλ�� */
    ulSubnetComOffset = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.ulComSubnetBitOffset +
                        ulOffsetPos;

    pucSubnetCom                = pucPrBuff + ulSubnetComOffset;

    pstIs586Id->ucSubnetCommLen = pucSubnetCom[0] & 0x0F;

    NAS_MEM_CPY_S(pstIs586Id->aucSubnet,
                  CNAS_PRL_BYTES_IN_SUBNET,
                  pucSubnetCom + sizeof(VOS_UINT8),
                  pstIs586Id->ucSubnetCommLen);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseSysIdRec_Is856
 ��������  : ����Type-specific system ID record��¼
 �������  : pucSrc          - EPRL ����
             ulOffsetPos     - EPRL ������ǰλ��
             pstIs856Id      - �����������ŵ�ַ

 �������  : pulCurOffsetPos - �������bit��������

 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��3��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_ParseSysIdRec_Is856(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_SYS_TYPE_HRPD_ID_STRU     *pstIs856Id,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    Table 3.5.5.3.2-2 Type-specific system ID record
    System ID Record Field          Length (bits)

    RESERVED                        3
    SUBNET_COMMON_INCLUDED          1
    SUBNET_LSB_LENGTH               7
    SUBNET_LSB                      SUBNET_LSB_LENGTH
    SUBNET_COMMON_OFFSET            0 or 12
    */

    VOS_UINT8                          *pucPrBuff               = VOS_NULL_PTR;
    VOS_UINT8                           ucSubnetLsbLen          = 0;
    VOS_UINT8                           ucMinSubnetLsbLen       = 0;
    VOS_UINT32                          ulSubCommOffset         = 0; /* 0 or 12 */
    VOS_UINT32                          ulSubCommOffsetToTable  = 0;
    VOS_UINT32                          ulCurBitOffset;

    /* ��ʼ������ */
    pucPrBuff      = pucSrc;
    ulCurBitOffset = ulOffsetPos;

    /* ����RESERVED */
    ulCurBitOffset += CNAS_PRL_BIT_LEN_3_BIT;

    /* ����COMM_INCL */
    pstIs856Id->ucSubnetCommInc = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_1_BIT;

    /* ����LSB_LEN */
    pstIs856Id->ucSubnetLsbLen = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_7_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_7_BIT;

    /* Subnet��� |--SubnetComm--+--SubnetLsb--|*/
    if (VOS_TRUE == pstIs856Id->ucSubnetCommInc)
    {
        /* ����SubnetComm */
        /* ����SUBNET_COMMON,����SUBNET_COMMON_OFFSET */
        ulSubCommOffsetToTable = CNAS_PRL_BIT_TO_WORD(pucPrBuff,
                                                      (ulCurBitOffset + pstIs856Id->ucSubnetLsbLen),
                                                      CNAS_PRL_BIT_LEN_12_BIT);
        /* ����SUBNET_COMMON */
        CNAS_PRL_ParseSubnetComm(pucPrBuff, ulSubCommOffsetToTable, pstIs856Id);

        ulSubCommOffset = CNAS_PRL_BIT_LEN_12_BIT;
    }
    else
    {
        ulSubCommOffset             = 0;
        pstIs856Id->ucSubnetCommLen = 0;
    }

    ucSubnetLsbLen = ((pstIs856Id->ucSubnetLsbLen + CNAS_PRL_BIT_LEN_7_BIT) / CNAS_PRL_BIT_LEN_8_BIT);

    /* ����SubnetLsb */
    ucMinSubnetLsbLen = CNAS_MIN(ucSubnetLsbLen, (sizeof(pstIs856Id->aucSubnet) - pstIs856Id->ucSubnetCommLen));
    NAS_MEM_CPY_S(&(pstIs856Id->aucSubnet[pstIs856Id->ucSubnetCommLen]),
                  CNAS_PRL_BYTES_IN_SUBNET - pstIs856Id->ucSubnetCommLen,
                  &pucPrBuff[ulCurBitOffset / CNAS_PRL_BIT_LEN_8_BIT], /* PRL��������ǡ����8bit���� */
                  (VOS_UINT32)ucMinSubnetLsbLen);

    pstIs856Id->ucSubnetBitLen = pstIs856Id->ucSubnetCommLen + pstIs856Id->ucSubnetLsbLen;

    ulCurBitOffset  += pstIs856Id->ucSubnetLsbLen;

    ulCurBitOffset  += ulSubCommOffset;

    /* ��¼������¼��ƫ��ֵ */
    *pulCurOffsetPos = ulCurBitOffset;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseSysIdRec_Mcc
 ��������  : ����Type-specific system ID record��¼
 �������  : pucSrc          - EPRL ����
             ulOffsetPos     - EPRL ������ǰλ��
             pstMccMncIdId   - �����������ŵ�ַ

 �������  : pulCurOffsetPos - �������bit��������
 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��3��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseSysIdRec_Mcc(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_SYS_TYPE_MCC_MNC_ID_STRU  *pstMccMncIdId,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    Table 3.5.5.3.2.2-1 Type-specific system ID record  18
    System ID Record Field          Length (bits)
    SYS_RECORD_SUBTYPE              3
    Subtype dependent field         Variable

    ----------------------------------------------------
    Table 3.5.5.3.2.2-3 Subtype Dependent record for Subtype ��000��  7
    Field Name                      Length (bits)
    MCC                             12
    MNC                             12
    ----------------------------------------------------
    Table 3.5.5.3.2.2-4 Subtype Dependent record for Subtype ��001��  16
    Field Name                      Length (bits)
    RESERVED                        4
    NUM_SID                         4
    NUM_SID occurrences of the following field
    RESERVED                        1
    SID                             15
    ----------------------------------------------------
    Table 3.5.5.3.2.2-5 Subtype Dependent record for Subtype ��010��
    Field Name                      Length (bits)
    RESERVED                        4
    NUM_SID_NID                     4
    NUM_SID_NID occurrences of the following two fields
    RESERVED                        1
    SID                             15
    NID                             16
    ----------------------------------------------------
    */
    VOS_UINT8                          *pucPrBuff    = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT32                          ulSubnet_len;
    VOS_UINT32                          i;

    /* ��ʼ������ */
    pucPrBuff      = pucSrc;
    ulCurBitOffset = ulOffsetPos;

    /* SYS_RECORD_SUBTYPE */
    pstMccMncIdId->enMccMncSubType = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_3_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_3_BIT;

    /* ����MCC */
    pstMccMncIdId->usMcc= CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_12_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_12_BIT;

    /* ����MNC */
    pstMccMncIdId->usMnc= CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_12_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_12_BIT;

    switch(pstMccMncIdId->enMccMncSubType)
    {
        case CNAS_PRL_MCC_MNC_SUBTYPE_ONLY:
            break;

        case CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID:
        case CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID:

            /* RESERVED 4 */
            ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

            pstMccMncIdId->u.stSidNid.ucSidNidNum = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_4_BIT);
            ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

            for (i=0; i<pstMccMncIdId->u.stSidNid.ucSidNidNum; i++)
            {
                /* RESERVED 1 */
                ulCurBitOffset += CNAS_PRL_BIT_LEN_1_BIT;

                pstMccMncIdId->u.stSidNid.asSid[i] = CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_15_BIT);
                ulCurBitOffset += CNAS_PRL_BIT_LEN_15_BIT;

                if(CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID == pstMccMncIdId->enMccMncSubType)
                {
                    pstMccMncIdId->u.stSidNid.asNid[i] = CNAS_PRL_WILDCARD_NID;
                }
                else
                {
                    pstMccMncIdId->u.stSidNid.asNid[i] = CNAS_PRL_BIT_TO_WORD(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_16_BIT);
                    ulCurBitOffset += CNAS_PRL_BIT_LEN_16_BIT;
                }

            }
            break;
        /*
        ----------------------------------------------------
        Table 3.5.5.3.2.2-6 Subtype Dependent record for Subtype ��011��  14
        Field Name                  Length (bits)
        RESERVED                    4
        NUM_SUBNET_ID               4
        NUM_SUBNET_ID occurrences of the following three fields:
        SUBNET_LENGTH               8
        SUBNET_ID                   SUBNET_LENGTH
        RESERVED                    0 to 7
        ----------------------------------------------------
        */
        case CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SUBNET_ID:

            pstMccMncIdId->u.pstSubnetId = (CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU*)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                                           sizeof(CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU));

            if (VOS_NULL_PTR == pstMccMncIdId->u.pstSubnetId)
            {
                return VOS_FALSE;
            }

            NAS_MEM_SET_S(pstMccMncIdId->u.pstSubnetId, sizeof(CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU), 0, sizeof(CNAS_PRL_SYS_TYPE_SUBNET_ID_STRU));

            /* RESERVED 4 */
            ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

            pstMccMncIdId->u.pstSubnetId->ucSubnetNum = CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_4_BIT);
            ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

            for (i=0; i<pstMccMncIdId->u.pstSubnetId->ucSubnetNum; i++)
            {
                pstMccMncIdId->u.pstSubnetId->aucSubnetLen[i]= CNAS_PRL_BIT_TO_BYTE(pucPrBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
                ulCurBitOffset += CNAS_PRL_BIT_LEN_8_BIT;

                ulSubnet_len = CNAS_MIN( ((pstMccMncIdId->u.pstSubnetId->aucSubnetLen[i] + CNAS_PRL_BIT_LEN_7_BIT)/CNAS_PRL_BIT_LEN_8_BIT),
                                        CNAS_PRL_MCC_MNC_SUBNET_MAX_LEN);

                NAS_MEM_CPY_S(pstMccMncIdId->u.pstSubnetId->aucSubnetID[i],
                              (CNAS_PRL_MCC_MNC_SUBNET_MAX_NUM - i ) * CNAS_PRL_MCC_MNC_SUBNET_MAX_LEN,
                              &pucPrBuff[ulCurBitOffset / CNAS_PRL_BIT_LEN_8_BIT],
                              ulSubnet_len);

                ulCurBitOffset += pstMccMncIdId->u.pstSubnetId->aucSubnetLen[i];
            }

            ulCurBitOffset = ((ulCurBitOffset + CNAS_PRL_BIT_LEN_7_BIT) / CNAS_PRL_BIT_LEN_8_BIT) * CNAS_PRL_BIT_LEN_8_BIT;
            break;

        default:
        /* �ü�¼����δ֪ */
        //pstPrlSysRecord->ucSysRecValid = VOS_FALSE;
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "CNAS_PRL_ParseSysIdRec_1XMcc: system record = %d is unknown  ",
                        pstMccMncIdId->enMccMncSubType);
        return VOS_FALSE;
    }

    /* ��¼������¼��ƫ��ֵ */
    *pulCurOffsetPos = ulCurBitOffset;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseSysRec_REV3
 ��������  : ����һ��system record��¼
 �������  : pucSrc:ԭʼbit����
             pstPrlAcqRecord:�������system record
 �������  : pulBitOffset:�������bitƫ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17

*****************************************************************************/
VOS_VOID CNAS_PRL_ParseSysRec_REV3(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstPrlSysRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    System Record Field         Length (bits)
    SYS_RECORD_LENGTH           5
    SYS_RECORD_TYPE             4
    PREF_NEG                    1
    GEO                         1
    PRI                         1
    ACQ_INDEX                   9
    Type-specific system ID record variable
    ROAM_IND                    0 or 8
    ASSOCIATION_INC             1
    ASSOCIATION_TAG             0 or 8
    PN_ASSOCIATION              0 or 1
    DATA_ASSOCIATION            0 or 1
    RESERVED                    0 to 7
    */

    VOS_UINT8                          *pucPrlBuff = VOS_NULL_PTR;
    VOS_UINT32                          ulSysRecBitOffset;
    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucLength;

    /* ��ʼ������ */
    ulSysRecBitOffset = 0;
    pucPrlBuff        = pucSrc;
    ulCurBitOffset    = ulOffsetPos;

    /* ����SYS_RECORD_LENGTH,����Ҫ���� */
    ucLength        = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_5_BIT);
    ulCurBitOffset += CNAS_PRL_BIT_LEN_5_BIT;

    /* ���ظ�SYS_RECORD��ƫ���� */
    *pulCurOffsetPos = ulOffsetPos + CNAS_PRL_BIT_LEN_8_BIT * ucLength;

    /* ����SYS_RECORD_TYPE */
    pstPrlSysRecord->enRecordType = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_4_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_4_BIT;

    /* ����PREF_NEG */
    pstPrlSysRecord->enPrefNegSys = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_1_BIT;

    /* ����GEO */
    pstPrlSysRecord->enGeoInd     = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_1_BIT;

    /* ����PRI */
    pstPrlSysRecord->enPriInd     = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_1_BIT;

    /* ����ACQ_INDEX */
    pstPrlSysRecord->usAcqIndex   = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_9_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_9_BIT;

    /* ����SYS_RECORD_TYPE������ͬ�Ľ��� */
    switch(pstPrlSysRecord->enRecordType)
    {
        case CNAS_PRL_SYS_RECORD_TYPE_1X_IS95:
            CNAS_PRL_ParseSysIdRec_1X(pucPrlBuff,
                                      ulCurBitOffset,
                                      &(pstPrlSysRecord->u.st1xAndIs95Id),
                                      &ulSysRecBitOffset);
            pstPrlSysRecord->ucSysRecValid = VOS_TRUE;
            break;

        case CNAS_PRL_SYS_RECORD_TYPE_HRPD:
            CNAS_PRL_ParseSysIdRec_Is856(pucPrlBuff,
                                         ulCurBitOffset,
                                         &(pstPrlSysRecord->u.stIs856Id),
                                         &ulSysRecBitOffset);
            pstPrlSysRecord->ucSysRecValid = VOS_TRUE;

            break;

        case CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED:
            if (VOS_TRUE == CNAS_PRL_ParseSysIdRec_Mcc(pucPrlBuff,
                                                        ulCurBitOffset,
                                                        &(pstPrlSysRecord->u.stMccMncId),
                                                        &ulSysRecBitOffset))
            {
                pstPrlSysRecord->ucSysRecValid = VOS_TRUE;
            }
            else
            {
                pstPrlSysRecord->ucSysRecValid = VOS_FALSE;
            }

            break;

        default:
        /* �ü�¼����δ֪ */
        pstPrlSysRecord->ucSysRecValid = VOS_FALSE;
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "CNAS_PRL_ParseSysRec_REV3: system record = %d is unknown  ",
                        pstPrlSysRecord->enRecordType);
        return;
    }

    ulCurBitOffset = ulSysRecBitOffset;

    /* �����Ƿ���Negative */
    if (CNAS_PRL_PREF_NEG_SYS_PREF == pstPrlSysRecord->enPrefNegSys)
    {
        pstPrlSysRecord->enRoamingInd   = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ulCurBitOffset                 += CNAS_PRL_BIT_LEN_8_BIT;
    }

    /* ����ASSOCIATION_INC */
    pstPrlSysRecord->ucAssociationIncl  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);

    if (VOS_TRUE == pstPrlSysRecord->ucAssociationIncl)
    {

        ulCurBitOffset                     += CNAS_PRL_BIT_LEN_1_BIT;

        /* ����ASSOCIATION_TAG */
        pstPrlSysRecord->ucAssociationTag   = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ulCurBitOffset                     += CNAS_PRL_BIT_LEN_8_BIT;

        /* ����PN_ASSOCIATION */
        pstPrlSysRecord->ucPnAssociation    = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
        ulCurBitOffset                     += CNAS_PRL_BIT_LEN_1_BIT;

        /* ����DATA_ASSOCIATION */
        pstPrlSysRecord->ucDataAssociation  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseSysRec_REV1
 ��������  : ����һ��PRL system record��¼
 �������  : pucSrc:ԭʼbit����
             pstPrlAcqRecord:�������system record
 �������  : pulBitOffset:�������bitƫ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��10��
    ��    ��   : c00294324
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_ParseSysRec_REV1(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstPrlSysRecord,
    VOS_UINT32                         *pulCurOffsetPos
)
{
    /*
    System Record Field         Length (bits)
    SID                         15
    NID_INCL                    2
    NID                         0 or 16
    PREF_NEG                    1
    GEO                         1
    PRI                         0 or 1
    ACQ_INDEX                   9
    ROAM_IND                    0 or 8
    */

    VOS_UINT8                          *pucPrlBuff = VOS_NULL_PTR;
    VOS_UINT32                          ulCurBitOffset;

    /* ��ʼ������ */
    pucPrlBuff        = pucSrc;
    ulCurBitOffset    = ulOffsetPos;

    /* ����SID */
    pstPrlSysRecord->u.st1xAndIs95Id.usSid  = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_15_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_15_BIT;

    /* ����NID_INCL */
    pstPrlSysRecord->u.st1xAndIs95Id.enNidIncl = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_2_BIT);
    ulCurBitOffset               += CNAS_PRL_BIT_LEN_2_BIT;

    /* ����NID */
    if (CNAS_PRL_NID_INCL ==  pstPrlSysRecord->u.st1xAndIs95Id.enNidIncl)
    {
        pstPrlSysRecord->u.st1xAndIs95Id.usNid = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_16_BIT);
        ulCurBitOffset += CNAS_PRL_BIT_LEN_16_BIT;
    }
    else if (CNAS_PRL_NID_NOT_INCL_WILD_CARD == pstPrlSysRecord->u.st1xAndIs95Id.enNidIncl)
    {
        pstPrlSysRecord->u.st1xAndIs95Id.usNid           = CNAS_PRL_WILDCARD_NID;
    }
    else if (CNAS_PRL_NID_NOT_INCL_PLUBLIC_SYSTEM == pstPrlSysRecord->u.st1xAndIs95Id.enNidIncl)
    {
        pstPrlSysRecord->u.st1xAndIs95Id.usNid           = 0;
    }
    else
    {
        /* NID included is reserved */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_PRL_ParseSysRec_REV1:  enNidIncl is illegal!");

        pstPrlSysRecord->u.st1xAndIs95Id.usNid = CNAS_PRL_WILDCARD_NID;
    }

    /* ����PREF_NEG */
    pstPrlSysRecord->enPrefNegSys       =   CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset                     +=   CNAS_PRL_BIT_LEN_1_BIT;

    /* ����GEO */
    pstPrlSysRecord->enGeoInd           =   CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
    ulCurBitOffset                     +=   CNAS_PRL_BIT_LEN_1_BIT;

    /* ����PRI */
    if (CNAS_PRL_PREF_NEG_SYS_PREF == pstPrlSysRecord->enPrefNegSys)
    {
        pstPrlSysRecord->enPriInd       =   CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
        ulCurBitOffset                 +=   CNAS_PRL_BIT_LEN_1_BIT;
    }

    /* ����ACQ_INDEX */
    pstPrlSysRecord->usAcqIndex         =   CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_9_BIT);
    ulCurBitOffset                     +=   CNAS_PRL_BIT_LEN_9_BIT;

    /* ����ROAM_IND */
    if (CNAS_PRL_PREF_NEG_SYS_PREF == pstPrlSysRecord->enPrefNegSys)
    {
        pstPrlSysRecord->enRoamingInd   = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ulCurBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ulCurBitOffset                 +=   CNAS_PRL_BIT_LEN_8_BIT;
    }

    pstPrlSysRecord->enRecordType       =   CNAS_PRL_SYS_RECORD_TYPE_1X_IS95;
    pstPrlSysRecord->ucSysRecValid      =   VOS_TRUE;
    *pulCurOffsetPos                    =   ulCurBitOffset;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParsePrlSysRec
 ��������  : ����һ��system record��¼
 �������  : pucSrc:ԭʼbit����
             pstPrlAcqRecord:�������system record
 �������  : pulBitOffset:�������bitƫ����
 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��7��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified

*****************************************************************************/
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlSysRec(
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulOffsetPos,
    VOS_UINT32                         *pulCurOffSetPos
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU                          *pstSysRecInfo   = VOS_NULL_PTR;
    VOS_UINT8                                              *pucBuffOffset   = VOS_NULL_PTR;
    VOS_UINT32                                              ulSysRecBitOffset;
    VOS_UINT32                                              ulCurBitOffset;
    VOS_UINT32                                              ulSize;
    VOS_UINT32                                              i;
    VOS_UINT16                                              usPriLvlSeed;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstLastSysRec = VOS_NULL_PTR;
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstCustFreqList = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_INFO_STRU                          *pstAcqRecInfo = VOS_NULL_PTR;

    usPriLvlSeed                        = 0;
    pstCustFreqList                     =  CNAS_CCB_GetCTCCCustomizeFreqList();

    pstAcqRecInfo                       = &(CNAS_PRL_GetPrlInfoAddr()->stPrlAcqInfo);

    /* ��ʼ������ */
    pucBuffOffset                       = pucSrc;
    ulCurBitOffset                      = ulOffsetPos;

    /* ��ȡ��Ϣͷ�н�������ACQ_NUMS */
    pstSysRecInfo                       = &(CNAS_PRL_GetPrlInfoAddr()->stPrlSysInfo);
    pstSysRecInfo->usSysRecordNum       = CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.usNumSysRecs;

    /* �����ڴ棬������һ���ڴ棬ΪCNAS_PRL_SSPR_P_REV_1�汾Ԥ��һ����¼�Ŀռ� */
    ulSize                          = sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU) * (pstSysRecInfo->usSysRecordNum + 1);
    pstSysRecInfo->pstSysRecord     = (CNAS_PRL_EXT_SYS_RECORD_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, ulSize);

    if (VOS_NULL_PTR == pstSysRecInfo->pstSysRecord)
    {
        return CNAS_PRL_PARSE_SYS_RECORD_FAIL;
    }

    /* ��ʼ���ڴ�ռ� */
    NAS_MEM_SET_S(pstSysRecInfo->pstSysRecord, ulSize, 0, ulSize);

    /* ��ǰ��ֻʵ��EPRL�Ľ��� */
    if (CNAS_PRL_SSPR_P_REV_3 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        /* ����ÿһ��ϵͳ��¼ */
        for (i = 0;  i < pstSysRecInfo->usSysRecordNum; i++)
        {
            ulSysRecBitOffset           = 0;

            CNAS_PRL_ParseSysRec_REV3(pucBuffOffset,
                                      ulCurBitOffset,
                                      pstSysRecInfo->pstSysRecord + i,
                                      &ulSysRecBitOffset);

            /* ƫ��BIT������ָ�� */
            ulCurBitOffset = ulSysRecBitOffset;

            (pstSysRecInfo->pstSysRecord + i)->usPriLvl = usPriLvlSeed;

            if (CNAS_PRL_RELATIVE_PRI_MORE == (pstSysRecInfo->pstSysRecord + i)->enPriInd)
            {
                usPriLvlSeed++;
            }
        }
    }

    /* ����PRL�Ľ��� */
    if (CNAS_PRL_SSPR_P_REV_1 == CNAS_PRL_GetPrlInfoAddr()->stPrlHeader.enSsprPRev)
    {
        /* ����ÿһ��ϵͳ��¼ */
        for (i = 0;  i < pstSysRecInfo->usSysRecordNum; i++)
        {
            ulSysRecBitOffset           = 0;

            CNAS_PRL_ParseSysRec_REV1(pucBuffOffset,
                                      ulCurBitOffset,
                                      pstSysRecInfo->pstSysRecord + i,
                                      &ulSysRecBitOffset);

            /* ƫ��BIT������ָ�� */
            ulCurBitOffset = ulSysRecBitOffset;

            (pstSysRecInfo->pstSysRecord + i)->usPriLvl = usPriLvlSeed;

            if (CNAS_PRL_RELATIVE_PRI_MORE == (pstSysRecInfo->pstSysRecord + i)->enPriInd)
            {
                usPriLvlSeed++;
            }
        }

        if (VOS_TRUE == pstCustFreqList->ucEnableFlg)
        {
            pstLastSysRec = pstSysRecInfo->pstSysRecord + pstSysRecInfo->usSysRecordNum;

            NAS_MEM_SET_S(pstLastSysRec, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU), 0x00, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
            pstLastSysRec->enRecordType  = CNAS_PRL_SYS_RECORD_TYPE_HRPD;
            pstLastSysRec->enPrefNegSys  = CNAS_PRL_PREF_NEG_SYS_PREF;
            pstLastSysRec->enGeoInd      = CNAS_PRL_GEO_REGION_IND_NEW;
            pstLastSysRec->enPriInd      = CNAS_PRL_RELATIVE_PRI_MORE;
            pstLastSysRec->usAcqIndex    = pstAcqRecInfo->usAcqRecordNum - 1;
            pstLastSysRec->ucSysRecValid = VOS_TRUE;
            pstLastSysRec->usPriLvl      = usPriLvlSeed;
            /* ����ָʾ��ǣ������ȷ�ϣ��ñ���䲻ʹ�� */
            pstLastSysRec->enRoamingInd  = CNAS_PRL_SYS_ROAMING_STATUS_OFF;

            pstSysRecInfo->usSysRecordNum++;
        }
    }

    /* ���ϵͳ�������м�¼��Ч���򷵻�ϵͳ��¼ʧ�� */
    if (VOS_FALSE == CNAS_PRL_IsSysRecTabValid(pstSysRecInfo))
    {
        return CNAS_PRL_PARSE_SYS_RECORD_FAIL;
    }

    /* ���ϵͳ���¼��Ϣ */
    CNAS_PRL_LogSysRecInfo(pstSysRecInfo);

    *pulCurOffSetPos  = ulCurBitOffset;

    return CNAS_PRL_PARSE_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParsePrlHeader
 ��������  : ����PRL���е���Ϣ
 �������  : pucSrc -- PRL����ԭʼ�����׵�ַ
             enPrlRev -- PRL�汾��Ϊ����ʹ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlHeader(
    VOS_UINT8                          *pucSrc,
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enPrlRev
)
{
    CNAS_PRL_HEADER_INFO_STRU          *pstPrlHeaderInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucPrlBuff       = VOS_NULL_PTR;
    VOS_UINT16                          usPrlListSize;
    VOS_UINT8                           ucBitOffset;

    /* ����PRL��ͷ������ǰֻ����ERPL */
    /* EPRL��PRL�ĸ�ʽ�������죬������Э�鶨��ĸ�ʽC.S0016 3.5.5
    Preferred Roaming List Field                Length (bits)
    PR_LIST_SIZE                                16
    PR_LIST_ID                                  16
    PREF_ONLY                                   1
    DEF_ROAM_IND                                8
    NUM_ACQ_RECS                                9
    NUM_SYS_RECS                                14
    ACQ_TABLE                                   variable
    SYS_TABLE                                   variable
    RESERVED                                    0 to 7
    PR_LIST_CRC                                 16

    Extended Preferred Roaming List Field       Length (bits)
    PR_LIST_SIZE                                16
    PR_LIST_ID                                  16
    CUR_SSPR_P_REV                              8
    PREF_ONLY                                   1
    DEF_ROAM_IND                                8
    NUM_ACQ_RECS                                9
    NUM_COMMON_SUBNET_RECS                      9
    NUM_SYS_RECS                                14
    RESERVED                                    7
    EXT_ACQ_TABLE                               variable
    COMMON_SUBNET_TABLE                         variable
    EXT_SYS_TABLE                               variable
    RESERVED                                    As needed
    PR_LIST_CRC                                 16
    */

    ucBitOffset     = 0;
    pucPrlBuff      = pucSrc;

    /* ����PR_LIST_SIZE */
    usPrlListSize = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_16_BIT);
    ucBitOffset  += CNAS_PRL_BIT_LEN_16_BIT;

    /* ��PR_LIST_SIZE���������, ��ȥPR_LIST_SIZE��PR_LIST_CRC������Ҫ����0*/
    if (usPrlListSize <= (sizeof(VOS_UINT16) + sizeof(VOS_UINT16)))
    {
        return CNAS_PRL_PARSE_INVALID_LIST_SIZE;
    }

    /* ͷ��Ϣ��usPrListSize��ȥPR_LIST_SIZE��PR_LIST_CRC���� */
    pstPrlHeaderInfo                = &(CNAS_PRL_GetPrlInfoAddr()->stPrlHeader);
    pstPrlHeaderInfo->usPrListSize  = usPrlListSize;

    /* ����PR_LIST_ID */
    pstPrlHeaderInfo->usPrListId = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_16_BIT);
    ucBitOffset += CNAS_PRL_BIT_LEN_16_BIT;

    if (CNAS_PRL_SSPR_P_REV_1 == enPrlRev)
    {
        pstPrlHeaderInfo->enSsprPRev = CNAS_PRL_SSPR_P_REV_1;

        /* PRLͷ���� */
        /* ����PREF_ONLY */
        pstPrlHeaderInfo->ucPreferOnly  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_1_BIT;

        /* ����DEF_ROAM_IND */
        pstPrlHeaderInfo->enDefRoamInd  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_8_BIT;

        /* ����NUM_ACQ_RECS */
        pstPrlHeaderInfo->usNumAcqRecs  = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_9_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_9_BIT;

        if (0 == pstPrlHeaderInfo->usNumAcqRecs)
        {
            return CNAS_PRL_PARSE_ACQ_RECORD_FAIL;
        }

        /* ����NUM_SYS_RECS */
        pstPrlHeaderInfo->usNumSysRecs = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_14_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_14_BIT;

        if (0 == pstPrlHeaderInfo->usNumSysRecs)
        {
            return CNAS_PRL_PARSE_SYS_RECORD_FAIL;
        }
    }
    else
    {
        /* ����CUR_SSPR_P_REV */
        pstPrlHeaderInfo->enSsprPRev = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_8_BIT;

        if (CNAS_PRL_SSPR_P_REV_3 != pstPrlHeaderInfo->enSsprPRev)
        {
            return CNAS_PRL_PARSE_VERSION_MISMATCH;
        }

        /* ����PREF_ONLY */
        pstPrlHeaderInfo->ucPreferOnly  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_1_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_1_BIT;

        /* ����DEF_ROAM_IND */
        pstPrlHeaderInfo->enDefRoamInd  = CNAS_PRL_BIT_TO_BYTE(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_8_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_8_BIT;

        /* ����NUM_ACQ_RECS */
        pstPrlHeaderInfo->usNumAcqRecs  = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_9_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_9_BIT;

        if (0 == pstPrlHeaderInfo->usNumAcqRecs)
        {
            return CNAS_PRL_PARSE_ACQ_RECORD_FAIL;
        }

        /* ����NUM_COMMON_SUBNET_RECS */
        pstPrlHeaderInfo->usNumSubnetRecs   = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_9_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_9_BIT;

        /* ����NUM_SYS_RECS */
        pstPrlHeaderInfo->usNumSysRecs = CNAS_PRL_BIT_TO_WORD(pucPrlBuff, ucBitOffset, CNAS_PRL_BIT_LEN_14_BIT);
        ucBitOffset += CNAS_PRL_BIT_LEN_14_BIT;

        if (0 == pstPrlHeaderInfo->usNumSysRecs)
        {
            return CNAS_PRL_PARSE_SYS_RECORD_FAIL;
        }

        /* ����RESERVED�ֶΣ�ƫ��ָ��EXT_ACQ_TABLE, ˢ�µ�ͷ����Ϣ */
        ucBitOffset += CNAS_PRL_BIT_LEN_7_BIT;
    }

    /* ���ò������PRL�е�bitƫ�� */
    pstPrlHeaderInfo->usAcqTabBitOffset = ucBitOffset;

    /* ��ӡPRL header��Ϣ */
    CNAS_PRL_LogHeaderInfo(pstPrlHeaderInfo);

    return CNAS_PRL_PARSE_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParsePrlCalcCommSubnetSize
 ��������  : ����COMMON_SUBNET_TABLEռ�մ�С
 �������  : pucSrc        -- ��ǰrecord�׵�ַ
             ucOffsetPos   -- ��ǰrecord���ֽ��е�bitƫ��
             usNumSubnetRecs- ��ǰSub net����

 �������  : pulBitOffset ���� ���ص�ǰ��¼��bitƫ��

 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��6��
    ��    ��   : d00212987
    �޸�����   : EVDO HSD Phase0

*****************************************************************************/
VOS_VOID CNAS_PRL_ParsePrlCalcComSubnetBits(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usNumSubnetRecs,
    VOS_UINT32                          ulOffsetPos,
    VOS_UINT32                         *pulBitOffset
)
{
    /* ��ǰ��������ʵ�ʽ�����ֻ����Ӧ��bitƫ�� */
    /*
    System ID Record Field      Length (bits)
    RESERVED                    4
    SUBNET_COMMON_LENGTH        4
    SUBNET_COMMON               8 * SUBNET_COMMON_LENGTH
    */

    VOS_UINT32                          ulCurBitOffset;
    VOS_UINT8                           ucSubnetComLen;
    VOS_UINT16                          i;

    /* ��ǰ�����������ƫ��λ�� */
    ulCurBitOffset  = ulOffsetPos;

    for (i=0; i<usNumSubnetRecs; i++)
    {
        /* ͳ��4bitƫ���� */
        ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

        /* ����SUBNET_COMMON_LENGTH */
        ucSubnetComLen = CNAS_PRL_BIT_TO_BYTE(pucSrc, ulCurBitOffset, CNAS_PRL_BIT_LEN_4_BIT);
        ulCurBitOffset += CNAS_PRL_BIT_LEN_4_BIT;

        /* �����record�ܵ�bitƫ�� */
        ulCurBitOffset += ucSubnetComLen * CNAS_PRL_BIT_LEN_8_BIT;
    }

    *pulBitOffset = ulCurBitOffset;

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParsePrlInfo
 ��������  : ����PRL���е���Ϣ
 �������  : pucSrc   -- PRLԭʼ����
             usSrcLen -- ԭʼ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_PARSE_CAUSE_ENUM_UINT32 CNAS_PRL_ParsePrlInfo(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    CNAS_PRL_SSPR_P_REV_ENUM_UINT8      enPrlRev
)
{
    CNAS_PRL_HEADER_INFO_STRU          *pstPrlHeaderInfo = VOS_NULL_PTR;
    VOS_UINT8                          *pucPrlBuff       = VOS_NULL_PTR;
    VOS_UINT32                          ulPrlBitOffset;
    VOS_UINT32                          ulCurBitOffset;
    CNAS_PRL_PARSE_CAUSE_ENUM_UINT32    enCause;

    pucPrlBuff = pucSrc;

    enCause = CNAS_PRL_CheckPrlCrcChecksum(pucPrlBuff);
    if (CNAS_PRL_PARSE_SUCCESS != enCause)
    {
        /* CRCУ��ʧ�� */
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "check CRC is failure! cause = %d", enCause);
        return enCause;
    }

    /* �Ƚ���PRL��ͷ������ǰֻ����ERPL */
    enCause = CNAS_PRL_ParsePrlHeader(pucPrlBuff, enPrlRev);
    if (CNAS_PRL_PARSE_SUCCESS != enCause)
    {
        /* CRCУ��ʧ�� */
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "ParseHeader is failure! cause = %d", enCause);

        return enCause;
    }
    pstPrlHeaderInfo = &(CNAS_PRL_GetPrlInfoAddr()->stPrlHeader);
    ulCurBitOffset   = pstPrlHeaderInfo->usAcqTabBitOffset;

    /* ����acquisition�� */
    ulPrlBitOffset = 0;
    enCause = CNAS_PRL_ParsePrlAcqRec(pucPrlBuff, ulCurBitOffset, &ulPrlBitOffset);
    if (CNAS_PRL_PARSE_SUCCESS != enCause)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "parse acquisiton record table is failure! cause = %d", enCause);

        return enCause;
    }

    ulCurBitOffset = ulPrlBitOffset;

    pstPrlHeaderInfo->ulComSubnetBitOffset = ulCurBitOffset; /* ��¼Comm Sub Net bitƫ����ʼλ�� */
    /* ����SUBNET_COMM�� */
    if (CNAS_PRL_SSPR_P_REV_3 == enPrlRev)
    {
        CNAS_PRL_ParsePrlCalcComSubnetBits(pucPrlBuff,
                                           pstPrlHeaderInfo->usNumSubnetRecs,
                                           ulCurBitOffset,
                                           &ulPrlBitOffset);

        ulCurBitOffset = ulPrlBitOffset;
    }

    /* ����system record�� */
    ulPrlBitOffset = 0;
    enCause        = CNAS_PRL_ParsePrlSysRec(pucPrlBuff, ulCurBitOffset, &ulPrlBitOffset);
    if (CNAS_PRL_PARSE_SUCCESS != enCause)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XSD, "parse system tableis failure! cause = %d", enCause);

        return  enCause;
    }

    /* �����ɹ�������PRL��Ч */
    CNAS_PRL_GetPrlInfoAddr()->ulIsPrlValid = VOS_TRUE;

    return CNAS_PRL_PARSE_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_IsConcatenatedPrlProbable
 ��������  : ����PRL�Ƿ��ǿ��ܣ�����ǣ�����TRUE������ΪFALSE

 �������  : pucSrc             -- PRLԭʼ����
             usSrcLen           -- ԭʼ���ݳ���
             usFirstPrlListSize -- �׸�PRL����

 �������  : ��
 �� �� ֵ  : VOS_TRUE  ���������д���PRL
             VOS_FALSE --  �������д���PRL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_IsConcatenatedPrlProbable(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    VOS_UINT16                          usFirstPrlListSize
)
{
    VOS_UINT8                          *pucPrlBuff = VOS_NULL_PTR;
    VOS_UINT16                          usSecondPrlListSize;

    if ((usFirstPrlListSize + CNAS_PRL_PRL_LIST_SIZE_BYTE_LEN) < usSrcLen)
    {
        /* �����������׸�PRL������Ƿ��д���PRL���� */
        pucPrlBuff = (pucSrc + usFirstPrlListSize);

        /* ��ȡ�ڶ�������PRL_LIST_SIZE  */
        usSecondPrlListSize = CNAS_PRL_ExtractBitStringToWord(pucPrlBuff, 0, CNAS_PRL_BIT_LEN_16_BIT);

        if ((usFirstPrlListSize + usSecondPrlListSize) <= usSrcLen)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParsePrlBitStream
 ��������  : ����PRL���е���Ϣ, Ĭ��ʹ�ð汾1�����������������ʧ�ܣ������ð汾
             2��������
             ����Ǵ���PRL��

 �������  : pucSrc   -- PRLԭʼ����
             usSrcLen -- ԭʼ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParsePrlBitStream(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen
)
{
    CNAS_PRL_PARSE_CAUSE_ENUM_UINT32    enCause;
    VOS_UINT16                          usFirstPrlListSize;
    VOS_UINT8                          *pucPrlBuff = VOS_NULL_PTR;

    /* ��ȡ�������׸���PRL_LIST_SIZE  */
     usFirstPrlListSize = CNAS_PRL_ExtractBitStringToWord(pucSrc, 0, CNAS_PRL_BIT_LEN_16_BIT);

    if (usFirstPrlListSize > usSrcLen)
    {
        /* PRL���ݳ����뷵�ص��ļ����Ȳ�ƥ�� */
        CNAS_ERROR_LOG1(UEPS_PID_XSD,
                        "PRL PRL_LIST_SIZE is mismatch usSrcLen: usFirstPrlListSize = " ,
                        usFirstPrlListSize);

        return VOS_FALSE;
    }

    if (VOS_TRUE == CNAS_PRL_IsConcatenatedPrlProbable(pucSrc, usSrcLen, usFirstPrlListSize))
    {
        pucPrlBuff = (pucSrc + usFirstPrlListSize);

        /* ����ʹ��EPRL��ʽ�����ڶ���PRL���� */
        enCause = CNAS_PRL_ParsePrlInfo(pucPrlBuff, usSrcLen, CNAS_PRL_SSPR_P_REV_3);

        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* �����ɹ������� */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on 2nd PRL");

            return VOS_TRUE;
        }

        /* ����ʹ��EPRL��ʽ������һ��PRL���� */
        enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_3);
        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* �����ɹ������� */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on 1st PRL");

            return VOS_TRUE;
        }

        /* ʹ��PRL��ʽ�����ڶ�PRL���� */
        enCause = CNAS_PRL_ParsePrlInfo(pucPrlBuff, usSrcLen, CNAS_PRL_SSPR_P_REV_1);

        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* �����ɹ������� */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on 2nd PRL");

            return VOS_TRUE;
        }

        /* ʹ��PRL��ʽ������һPRL���� */
        enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_1);

        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* �����ɹ������� */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on 1nd PRL");

            return VOS_TRUE;
        }
    }
    else
    {

        /* ʹ��PRL��ʽ����PRL���� */
        enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_1);

        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* �����ɹ������� */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on PRL");

            return VOS_TRUE;
        }

        /* ʹ��EPRL��ʽ����PRL���� */
        enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_3);

        if (CNAS_PRL_PARSE_SUCCESS == enCause)
        {
            /* �����ɹ������� */
            CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on PRL");

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_ParseEprlBitStream
 ��������  : ����PRL���е���Ϣ, Ĭ��ʹ�ð汾3�����������������ʧ�ܣ������ð汾
             1��������

 �������  : pucSrc   -- PRLԭʼ����
             usSrcLen -- ԭʼ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_TRUE�������ɹ��� VOS_FALSE������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_PRL_ParseEprlBitStream(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen
)
{
    CNAS_PRL_PARSE_CAUSE_ENUM_UINT32    enCause;
    VOS_UINT16                          usPrlListSize;

    /* ��ȡ�������׸���PRL_LIST_SIZE  */
     usPrlListSize = CNAS_PRL_ExtractBitStringToWord(pucSrc, 0, CNAS_PRL_BIT_LEN_16_BIT);

    if (usPrlListSize > usSrcLen)
    {
        /* PRL���ݳ����뷵�ص��ļ����Ȳ�ƥ�� */
        CNAS_ERROR_LOG1(UEPS_PID_XSD,
                        "PRL PRL_LIST_SIZE is mismatch usSrcLen: usPrlListSize = " ,
                        usPrlListSize);

        return VOS_FALSE;
    }

    enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_3);

    if (CNAS_PRL_PARSE_SUCCESS == enCause)
    {
        CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on EPRL");

        return VOS_TRUE;
    }

    /* ������PRL��ʽ�������� */
    enCause = CNAS_PRL_ParsePrlInfo(pucSrc, usSrcLen, CNAS_PRL_SSPR_P_REV_1);

    if (CNAS_PRL_PARSE_SUCCESS == enCause)
    {
        CNAS_NORMAL_LOG(UEPS_PID_XSD, "CNAS_PRL_ProcPrlInfo: working on EPRL");

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



