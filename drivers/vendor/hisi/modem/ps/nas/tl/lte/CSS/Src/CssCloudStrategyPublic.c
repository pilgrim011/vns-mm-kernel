/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssCloudStrategyPublic.c
  Description     : CSS�ƶ�Ƶ��Ƶ�����Թ������ܵ�ʵ��
  History         :
     1.chengmin 00285307    2015-10-12  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "CssCloudStrategyPublic.h"
#include "NasMmlLib.h"
#include "CssProcAtMsg.h"
#include "MnClient.h"


#define    THIS_FILE_ID        PS_FILE_ID_CSSCLOUDSTRATEGYPUBLIC_C


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif


/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
VOS_UINT32 g_aulCssUSAMcc[]       = {0x00000103, 0x00010103, 0x00020103, 0x00030103, 0x00040103, 0x00050103, 0x00060103};
VOS_UINT32 g_aulCssUKMcc[]        = {0x00040302, 0x00050302};
VOS_UINT32 g_aulCssIndianMcc[]    = {0x00040004, 0x00050004, 0x00060004};
VOS_UINT32 g_aulCssJapanMcc[]     = {0x00000404, 0x00010404};
VOS_UINT32 g_aulCssSudanMcc[]     = {0x00040306, 0x00090506};

CSS_COUNTY_MCC_DESC_STRU g_astCountryMccList[] =
{
    {sizeof(g_aulCssUSAMcc)/sizeof(VOS_UINT32), g_aulCssUSAMcc},
    {sizeof(g_aulCssUKMcc)/sizeof(VOS_UINT32), g_aulCssUKMcc},
    {sizeof(g_aulCssIndianMcc)/sizeof(VOS_UINT32), g_aulCssIndianMcc},
    {sizeof(g_aulCssJapanMcc)/sizeof(VOS_UINT32), g_aulCssJapanMcc},
    {sizeof(g_aulCssSudanMcc)/sizeof(VOS_UINT32), g_aulCssSudanMcc},
};

#define  CSS_MCC_COUNTY_NUM (sizeof(g_astCountryMccList)/sizeof(CSS_COUNTY_MCC_DESC_STRU))



/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : CSS_ConvertSimPlmnToGuPlmn
 Description    : ��Sim�д洢PLMN�ĸ�ʽת��ΪGU�洢PLMN�ĸ�ʽ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertSimPlmnToGuPlmn
(
    VOS_UINT8                           aucPlmn[CSS_PLMN_ID_LEN],
    VOS_UINT32                         *pulMcc,
    VOS_UINT32                         *pulMnc

)
{
    VOS_UINT32                          ulTempData;

    ulTempData = CSS_OCTET_LOW_4_BITS & (aucPlmn[0]);
    *pulMcc = ulTempData;
    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucPlmn[0])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMcc |= ulTempData << CSS_OCTET_MOVE_8_BITS;
    ulTempData = CSS_OCTET_LOW_4_BITS & (aucPlmn[1]);
    *pulMcc |= ulTempData << CSS_OCTET_MOVE_16_BITS;

    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucPlmn[1])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMnc = ulTempData << CSS_OCTET_MOVE_16_BITS;
    ulTempData = CSS_OCTET_LOW_4_BITS & (aucPlmn[2]);
    *pulMnc |= ulTempData;
    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucPlmn[2])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMnc |= ulTempData << CSS_OCTET_MOVE_8_BITS;
}


/*****************************************************************************
 Function Name  : CSS_ConvertSimMccToGuMcc
 Description    : ��Sim�д洢MCC�ĸ�ʽת��ΪGU�洢MCC�ĸ�ʽ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertSimMccToGuMcc
(
    VOS_UINT8                           aucMcc[2],
    VOS_UINT32                         *pulMcc
)
{
    VOS_UINT32                          ulTempData;

    ulTempData = CSS_OCTET_LOW_4_BITS & (aucMcc[0]);
    *pulMcc = ulTempData;
    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucMcc[0])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMcc |= ulTempData << CSS_OCTET_MOVE_8_BITS;
    ulTempData = CSS_OCTET_LOW_4_BITS & (aucMcc[1]);
    *pulMcc |= ulTempData << CSS_OCTET_MOVE_16_BITS;
}

/*****************************************************************************
 Function Name  : CSS_ConvertSimMncToGuMnc
 Description    : ��Sim�д洢MNC�ĸ�ʽת��ΪGU�洢MNC�ĸ�ʽ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertSimMncToGuMnc
(
    VOS_UINT8                           aucMnc[2],
    VOS_UINT32                         *pulMnc
)
{
    VOS_UINT32                          ulTempData;

    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucMnc[0])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMnc = ulTempData << CSS_OCTET_MOVE_16_BITS;
    ulTempData = CSS_OCTET_LOW_4_BITS & (aucMnc[1]);
    *pulMnc |= ulTempData;
    ulTempData = (CSS_OCTET_HIGH_4_BITS & (aucMnc[1])) >> CSS_OCTET_MOVE_4_BITS;
    *pulMnc |= ulTempData << CSS_OCTET_MOVE_8_BITS;
}


/*****************************************************************************
 Function Name  : CSS_ConvertGuMccToSimMcc
 Description    : ��GU�洢MCC�ĸ�ʽת��ΪSim�д洢MCC�ĸ�ʽ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertGuMccToSimMcc
(
    VOS_UINT32                          ulMcc,
    VOS_UINT8                           aucMcc[2]
)
{
    aucMcc[0] = (((ulMcc >> CSS_OCTET_MOVE_8_BITS) & CSS_OCTET_LOW_4_BITS ) << CSS_OCTET_MOVE_4_BITS)
                | (ulMcc & CSS_OCTET_LOW_4_BITS);
    aucMcc[1] = (ulMcc >> CSS_OCTET_MOVE_16_BITS) & CSS_OCTET_LOW_4_BITS;
}


/*****************************************************************************
 Function Name  : CSS_ConvertGuMncToSimMnc
 Description    : ��GU�洢MNC�ĸ�ʽת��ΪSim�д洢MNC�ĸ�ʽ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertGuMncToSimMnc
(
    VOS_UINT32                          ulMnc,
    VOS_UINT8                           aucMnc[2]
)
{
    aucMnc[0] = ((ulMnc >> CSS_OCTET_MOVE_16_BITS) & CSS_OCTET_LOW_4_BITS) << CSS_OCTET_MOVE_4_BITS;
    aucMnc[1] = (((ulMnc >> CSS_OCTET_MOVE_8_BITS) & CSS_OCTET_LOW_4_BITS) << CSS_OCTET_MOVE_4_BITS)
                | (ulMnc & CSS_OCTET_LOW_4_BITS);
}


/*****************************************************************************
 Function Name  : CSS_ConvertMccDigitToSimMcc
 Description    : ��MCC1/MCC2/MCC3�ĸ�ʽת��ΪSim�д洢MCC�ĸ�ʽ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertMccDigitToSimMcc
(
    VOS_UINT8                           ucMccDigit1,
    VOS_UINT8                           ucMccDigit2,
    VOS_UINT8                           ucMccDigit3,
    VOS_UINT8                           aucMcc[2]
)
{
    aucMcc[0] = (((ucMccDigit2 & CSS_OCTET_LOW_4_BITS) << CSS_OCTET_MOVE_4_BITS) | (ucMccDigit1 & CSS_OCTET_LOW_4_BITS));
    aucMcc[1] = (ucMccDigit3 & CSS_OCTET_LOW_4_BITS);
}

/*****************************************************************************
 Function Name  : CSS_ConvertMncDigitToSimMnc
 Description    : ��MNC1/MNC2/MNC3�ĸ�ʽת��ΪSim�д洢MNC�ĸ�ʽ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ConvertMncDigitToSimMnc
(
    VOS_UINT8                           ucMncDigit1,
    VOS_UINT8                           ucMncDigit2,
    VOS_UINT8                           ucMncDigit3,
    VOS_UINT8                           aucMnc[2]
)
{
    aucMnc[0] = ((ucMncDigit3 & CSS_OCTET_LOW_4_BITS) << CSS_OCTET_MOVE_4_BITS);
    aucMnc[1] = (((ucMncDigit2 & CSS_OCTET_LOW_4_BITS) << CSS_OCTET_MOVE_4_BITS) | (ucMncDigit1 & CSS_OCTET_LOW_4_BITS));
}

/*****************************************************************************
 Function Name  : CSS_HasGetMccVersionFromAp
 Description    : �Ƿ���ƶ˻�ȡ���汾
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_HasGetMccVersionFromAp(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucVersion[MCC_INFO_VERSION_LEN];

    aucVersion[0] = '0';
    aucVersion[1] = '0';
    aucVersion[2] = '.';
    aucVersion[3] = '0';
    aucVersion[4] = '0';
    aucVersion[5] = '.';
    aucVersion[6] = '0';
    aucVersion[7] = '0';
    aucVersion[8] = '0';

    for (ulLoop = 0; ulLoop < MCC_INFO_VERSION_LEN; ++ulLoop)
    {
        if (g_stCloudContrl.aucVersion[ulLoop] != aucVersion[ulLoop])
        {
            return CSS_TRUE;
        }
    }
    return CSS_FALSE;
}

/*****************************************************************************
 Function Name  : CSS_GetLocalMccFreqVersion
 Description    : �ӱ��ػ�ȡԤ��Ƶ��İ汾�ţ���NAS��CHR�ϱ�ʱ����
 Input          : VOS_UINT8
 Output         : VOS_UINT8
 Return Value   : VOS_UINT32

 History        :
      1.qinxuying 00355475   2016-01-07  Draft Enact
*****************************************************************************/
CSS_RESULT_ENUM_UINT32 CSS_GetLocalMccFreqVersion(VOS_UINT8 aucVersion[CSS_MCC_VERSION_INFO_LEN])
{
    VOS_UINT32                          ulLoop = 0;
    
    if (CSS_NULL_PTR == aucVersion)
    {
        return CSS_RESULT_FAIL;
    }

    for (ulLoop = 0; ulLoop < CSS_MCC_VERSION_INFO_LEN; ++ulLoop)
    {
        aucVersion[ulLoop] = g_stCloudContrl.aucVersion[ulLoop];
        TLPS_PRINT2LAYER_INFO1(CSS_GetPreferMccFreqFromLocal_ENUM,LNAS_CSS_GetPrefMccVersionInfo,aucVersion[ulLoop]);
    }

    return CSS_RESULT_SUCC;
}

/*****************************************************************************
 Function Name  : CSS_InitMccVersion
 Description    : ��ʼ���汾��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_InitMccVersion(VOS_VOID)
{
    g_stCloudContrl.aucVersion[0] = '0';
    g_stCloudContrl.aucVersion[1] = '0';
    g_stCloudContrl.aucVersion[2] = '.';
    g_stCloudContrl.aucVersion[3] = '0';
    g_stCloudContrl.aucVersion[4] = '0';
    g_stCloudContrl.aucVersion[5] = '.';
    g_stCloudContrl.aucVersion[6] = '0';
    g_stCloudContrl.aucVersion[7] = '0';
    g_stCloudContrl.aucVersion[8] = '0';
}

/*****************************************************************************
 Function Name  : CSS_IsMccBelongToCountry
 Description    : �ж�ĳ��MCC�Ƿ�����ĳ��CSSԤ����Ķ�MCC����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccBelongToCountry
(
    VOS_UINT32                          ulMcc,
    CSS_COUNTY_MCC_DESC_STRU           *pstMccDesc
)
{
    VOS_UINT32                          i;
    for (i = 0; i < pstMccDesc->ulMccNum; ++i)
    {
        if (ulMcc == pstMccDesc->pulMccListAddr[i])
        {
            return CSS_TRUE;
        }
    }
    return CSS_FALSE;
}

/*****************************************************************************
 Function Name  : CSS_IsMccBelongToMultiCountry
 Description    : �ж�ĳ��MCC�Ƿ�����CSSԤ����Ķ�MCC����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccBelongToMultiCountry(VOS_UINT32 ulMcc)
{
    VOS_UINT32                          i;

    for (i = 0; i < CSS_MCC_COUNTY_NUM; ++i)
    {
        if (CSS_TRUE == CSS_IsMccBelongToCountry(ulMcc, &(g_astCountryMccList[i])))
        {
            return CSS_TRUE;
        }
    }
    return CSS_FALSE;
}


/*****************************************************************************
 Function Name  : CSS_IsTwoMccBelongToOneCountry
 Description    : �ж�����MCC�Ƿ�����ͬһ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsTwoMccBelongToOneCountry
(
    VOS_UINT32                          ulMcc1,
    VOS_UINT32                          ulMcc2
)
{
    VOS_UINT32                          i;

    for (i = 0; i < CSS_MCC_COUNTY_NUM; ++i)
    {
        if ((CSS_TRUE == CSS_IsMccBelongToCountry(ulMcc1, &(g_astCountryMccList[i])))
            && (CSS_TRUE == CSS_IsMccBelongToCountry(ulMcc2, &(g_astCountryMccList[i]))))
        {
            return CSS_TRUE;
        }
    }
    return CSS_FALSE;
}


/*****************************************************************************
 Function Name  : CSS_AddAllMccBelongToCountry
 Description    : ��ʼ���汾��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddAllMccBelongToCountry
(
    VOS_UINT32                         *pulOutNum,
    CSS_PLMN_ID_STRU                    astOutPlmn[CSS_MAX_PREF_PLMN_NUM],
    CSS_COUNTY_MCC_DESC_STRU           *pstMccDesc
)
{
    VOS_UINT32                          i;
    for (i = 0; i < pstMccDesc->ulMccNum; ++i)
    {
        if (*pulOutNum < CSS_MAX_PREF_PLMN_NUM)
        {
            astOutPlmn[*pulOutNum].ulMcc = pstMccDesc->pulMccListAddr[i];
            astOutPlmn[*pulOutNum].ulMnc = CSS_INVALID_MNC;
            (*pulOutNum) ++;
        }
    }
}



VOS_VOID CSS_GetAllMccBelongToOneCountry
(
    VOS_UINT32                                    ulInNum,
    CSS_PLMN_ID_STRU                              astInPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                   *pulOutNum,
    CSS_PLMN_ID_STRU                              astOutPlmn[CSS_MAX_PREF_PLMN_NUM]
)
{
    VOS_UINT32                          aulMcc[CSS_MAX_PREF_PLMN_NUM] = {0};/* �����ȡMCC�� */
    VOS_UINT32                          ulMccNum = 0;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          i;
    VOS_UINT8                           aucMccAdded[CSS_MCC_COUNTY_NUM] = {0};
    VOS_UINT32                          ulExist = CSS_FALSE;

    *pulOutNum = 0;

    /* ����ЩMNC��Ч��PLMN�ҳ�����������������
       MNC��Ч��PLMN�ҳ�����������ʱ������*/
    for (ulLoop = 0; ulLoop < ulInNum; ++ulLoop)
    {
        if (CSS_INVALID_MNC == astInPlmn[ulLoop].ulMnc)
        {
            aulMcc[ulMccNum++] = astInPlmn[ulLoop].ulMcc;
        }
        else
        {
            astOutPlmn[*pulOutNum].ulMcc = astInPlmn[ulLoop].ulMcc;
            astOutPlmn[*pulOutNum].ulMnc = astInPlmn[ulLoop].ulMnc;
            (*pulOutNum) ++;
        }
    }

    /* ����ʱ�������ҳ���MCC���б��������Ƿ�����һ����MCC���� */
    for (ulLoop = 0; ulLoop < ulMccNum; ++ulLoop)
    {
        ulExist = CSS_FALSE;
        for (i = 0; i < CSS_MCC_COUNTY_NUM; ++i)
        {
            if (CSS_TRUE == CSS_IsMccBelongToCountry(aulMcc[ulLoop], &(g_astCountryMccList[i])))
            {
                /* ����MCC���ڶ�MCC���ң����������MCC���ҵ�����MCCû�б�������������иù��ҵ�MCC���뵽�����
                   �������Ƿ�������Ϊtrue*/
                if (CSS_FALSE == aucMccAdded[i])
                {
                    CSS_AddAllMccBelongToCountry(pulOutNum, astOutPlmn, &(g_astCountryMccList[i]));
                    aucMccAdded[i] = CSS_TRUE;
                }
                ulExist = CSS_TRUE;
                break;
            }
        }
        /* ��mCC�������κ�һ����MCC���ң������������ */
        if (*pulOutNum < CSS_MAX_PREF_PLMN_NUM && CSS_FALSE == ulExist)
        {
            astOutPlmn[*pulOutNum].ulMcc = aulMcc[ulLoop];
            astOutPlmn[*pulOutNum].ulMnc = CSS_INVALID_MNC;
            (*pulOutNum) ++;
        }
    }
}




/*****************************************************************************
 Function Name  : CSS_isMncMatch
 Description    : MNC�Ƿ�һ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_isMncMatch(VOS_UINT8 aucMnc1[2], VOS_UINT8 aucMnc2[2])
{
    VOS_UINT32                          ulTmp1;
    VOS_UINT32                          ulTmp2;

    ulTmp1 = (CSS_OCTET_HIGH_4_BITS & (aucMnc1[0]));
    ulTmp2 = (CSS_OCTET_HIGH_4_BITS & (aucMnc2[0]));

    if (ulTmp1 == ulTmp2
        && aucMnc1[1] == aucMnc2[1])
    {
        return CSS_TRUE;
    }
    return CSS_FALSE;
}

/*****************************************************************************
 Function Name  : CSS_isMccMatch
 Description    : MCC�Ƿ�һ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_isMccMatch(VOS_UINT8 aucMcc1[2], VOS_UINT8 aucMcc2[2])
{
    VOS_UINT32                          ulTmp1;
    VOS_UINT32                          ulTmp2;

    ulTmp1 = (CSS_OCTET_LOW_4_BITS & (aucMcc1[1]));
    ulTmp2 = (CSS_OCTET_LOW_4_BITS & (aucMcc2[1]));

    if (ulTmp1 == ulTmp2
        && aucMcc1[0] == aucMcc2[0])
    {
        return CSS_TRUE;
    }
    return CSS_FALSE;
}

/*****************************************************************************
 Function Name  : CSS_IsRatSupportInFlag
 Description    : ��supportFlag���Ƿ�֧��ĳ��ʽ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-16  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsRatSupportInFlag(CSS_RAT_TYPE_ENUM_UINT8 ucRat, VOS_UINT8 ucSupportFlag)
{
    if (CSS_RAT_GSM == ucRat
        && (CSS_FALSE != (ucSupportFlag & CSS_GSM_SUPORT_OP)))
    {
        return CSS_TRUE;
    }

    if (CSS_RAT_UMTS_FDD == ucRat
        && (CSS_FALSE != (ucSupportFlag & CSS_WCDMA_SUPORT_OP)))
    {
        return CSS_TRUE;
    }

    if (CSS_RAT_LTE == ucRat
        && (CSS_FALSE != (ucSupportFlag & CSS_LTE_SUPORT_OP)))
    {
        return CSS_TRUE;
    }

    return CSS_FALSE;

}



VOS_VOID CSS_DeleteAllFreq(CSS_PUB_PREF_BAND_STRU *pBand)
{
    CSS_PUB_PREF_FREQ_STRU             *pFreqNode;
    CSS_PUB_PREF_FREQ_STRU             *pFreqNodeTmp;

    pFreqNode = pBand->pstFreqHead;
    /* ѭ��ɾ������FREQ�ڵ� */
    while (CSS_NULL_PTR != pFreqNode)
    {
        pFreqNodeTmp = pFreqNode->pstNext;

        /* �ͷŽڵ�ָ�� */
        CSS_FreeCloudPreferNode(pFreqNode);

        /* ָ����һ�ڵ� */
        pFreqNode = pFreqNodeTmp;
    }
    pBand->ucFreqNum = CSS_NULL;
}



VOS_VOID CSS_DeleteAllBand(CSS_PUB_PREF_MNC_STRU *pMnc)
{
    CSS_PUB_PREF_BAND_STRU             *pBandNode;
    CSS_PUB_PREF_BAND_STRU             *pBandNodeTmp;

    pBandNode = pMnc->pstBandHead;
    /* ѭ��ɾ������BAND�ڵ� */
    while (CSS_NULL_PTR != pBandNode)
    {
        pBandNodeTmp = pBandNode->pstNext;

        /* ɾ����MNC�ڵ��µ�����FREQ�ڵ� */
        CSS_DeleteAllFreq(pBandNode);

        /* �ͷŽڵ�ָ�� */
        CSS_FreeCloudPreferNode(pBandNode);

        /* ָ����һ�ڵ� */
        pBandNode = pBandNodeTmp;
    }
    pMnc->ucBandNum = CSS_NULL;
}




VOS_VOID CSS_DeleteAllMnc(CSS_PUB_PREF_MCC_STRU *pMcc)
{
    CSS_PUB_PREF_MNC_STRU              *pMncNode;
    CSS_PUB_PREF_MNC_STRU              *pMncNodeTmp;

    pMncNode = pMcc->pstMncHead;
    /* ѭ��ɾ������MNC�ڵ� */
    while (CSS_NULL_PTR != pMncNode)
    {
        pMncNodeTmp = pMncNode->pstNext;

        /* ɾ����MNC�ڵ��µ�����BAND�ڵ� */
        CSS_DeleteAllBand(pMncNode);

        /* �ͷŽڵ�ָ�� */
        CSS_FreeCloudPreferNode(pMncNode);

        /* ָ����һ�ڵ� */
        pMncNode = pMncNodeTmp;
    }
    pMcc->ucMncNum = CSS_NULL;
}


VOS_VOID CSS_DeleteAllMcc(VOS_VOID)
{
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    CSS_PUB_PREF_MCC_STRU              *pMccNodeTmp;

    pMccNode = CSS_GetPrefMccHeadNode();
    /* ѭ��ɾ������MCC�ڵ� */
    while (CSS_NULL_PTR != pMccNode)
    {
        pMccNodeTmp = pMccNode->pstNext;

        /* ɾ����MCC�ڵ��µ�����MNC�ڵ� */
        CSS_DeleteAllMnc(pMccNode);

        /* �ͷŽڵ�ָ�� */
        CSS_FreeCloudPreferNode(pMccNode);
        pMccNode = CSS_NULL_PTR;

        /* ָ����һ�ڵ� */
        pMccNode = pMccNodeTmp;
    }

    CSS_GetPrefMccHeadNode() = CSS_NULL_PTR;
    CSS_GetPrefMccTailNode() = CSS_NULL_PTR;
    CSS_GetPrefMccNodeNum()  = 0;

}

/*****************************************************************************
 Function Name  : CSS_DeleteOneMcc
 Description    : ���ڴ���ɾ��ĳ��MCC
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_DeleteOneMcc(VOS_UINT8 aucMccId[2])
{
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    CSS_PUB_PREF_MCC_STRU              *pMccNodePrev = CSS_NULL_PTR;

    /* ֱ��ɾ����MCC�ڵ� */
    pMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pMccNode)
    {
        if (CSS_TRUE == CSS_isMccMatch(aucMccId, pMccNode->aucMccId))
        {
            CSS_DeleteAllMnc(pMccNode);

            if (CSS_NULL_PTR == pMccNodePrev)
            {
                CSS_GetPrefMccHeadNode() = pMccNode->pstNext;
            }
            else
            {
                pMccNodePrev->pstNext = pMccNode->pstNext;
            }

            if (CSS_GetPrefMccTailNode() == pMccNode)
            {
                CSS_GetPrefMccTailNode() = pMccNodePrev;
            }
            CSS_FreeCloudPreferNode(pMccNode);

            CSS_GetPrefMccNodeNum()--;
            return;
        }
        pMccNodePrev = pMccNode;
        pMccNode = pMccNode->pstNext;
    }
}

/*****************************************************************************
 Function Name  : CSS_IsMccExistInLocal
 Description    : �����Ƿ����ĳ��MCC
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccExistInLocal(VOS_UINT8 aucMccId[2])
{
    CSS_PUB_PREF_MCC_STRU              *pMccNode;

    /* ��ͷ��㿪ʼ���� */
    pMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pMccNode)
    {
        if (CSS_TRUE == CSS_isMccMatch(aucMccId, pMccNode->aucMccId))
        {
            return CSS_TRUE;
        }
        pMccNode = pMccNode->pstNext;
    }
    return CSS_FALSE;
}


/*****************************************************************************
 Function Name  : CSS_IsMccUpdatedAccordToUpdateStateTable
 Description    : ĳ��MCC�Ƿ��ڶ�̬�����Ѿ�������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccUpdatedAccordToUpdateStateTable(VOS_UINT8 aucMccId[2])
{
    VOS_UINT32                          ulLoop1;
    VOS_UINT32                          ulLoop2;
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCloudContrl;
    CSS_MCC_UPDATE_STRU                *pstUpdate;

    pstCloudContrl = CSS_GetCloudContrlAddr();

    /* ��������״̬���ҵ����ڸ��µ�PID */
    for (ulLoop1 = 0; ulLoop1 < CSS_MAX_PID_NUM; ++ulLoop1)
    {
        pstUpdate = &(pstCloudContrl->astMccUpdate[ulLoop1]);
        /* ������ڸ��� */
        if (CSS_TRUE == pstUpdate->ucIsUpdating)
        {
            for (ulLoop2 = 0; ulLoop2 < pstUpdate->usMccNum; ++ulLoop2)
            {
                if ((CSS_TRUE == CSS_isMccMatch(pstUpdate->astMcc[ulLoop2].aucMccId, aucMccId))
                    && (CSS_TRUE == pstUpdate->aucUpdated[ulLoop2]))
                {
                    return CSS_TRUE;
                }
            }

        }
    }
    return CSS_FALSE;
}


VOS_VOID CSS_StartApMccUpdateProcedure
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNum,
    VOS_UINT16                          usClientId
)
{
    CSS_MCC_UPDATE_STRU                *pstUpdate = CSS_NULL_PTR;

    pstUpdate = &(CSS_GetCloudContrlAddr()->stApMccUpdate);
    pstUpdate->ucIsUpdating = CSS_TRUE;
    pstUpdate->usMccNum = (VOS_UINT16)ulMccNum;

    CSS_MEM_CPY_S(  pstUpdate->astMcc,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM,
                    astMccID,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM);
    CSS_MEM_SET_S(  pstUpdate->aucUpdated,
                    CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM);

    /* ֹͣ��ʱ�� */
    CSS_StopTimer(&(pstUpdate->stTimer));

    /* ��AP����MCC�������� */
    CSS_SendAtQueryMccNotifyByMccList(astMccID, ulMccNum, usClientId);

    /* ������ʱ�� */
    pstUpdate->stTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstUpdate->stTimer.usName      = TI_CSS_WAIT_AP_UPDATE_MCC_SET_REQ;
    pstUpdate->stTimer.ulTimerLen  = TI_CSS_WAIT_MCC_SET_ONE_MCC_LEN*ulMccNum;
    CSS_StartTimer(&(pstUpdate->stTimer));
}


/*****************************************************************************
 Function Name   : CSS_StartMmcOrAsMccUpdateProcedure
 Description     : ����MMC��AS���MCC���¹���
 Input           : astMccID
                   ulMccNum
                   astMccToSend
                   ulMccNumToSend
                   ulPId
 Output          : VOS_VOID
 Return          : VOS_VOID
 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_StartMmcOrAsMccUpdateProcedure
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNum,
    CSS_MCC_ID_STRU                     astMccToSend[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNumToSend,
    VOS_UINT32                          ulPId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulLoop1;
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCloudContrl;
    CSS_MCC_UPDATE_STRU                *pstUpdate = CSS_NULL_PTR;
    VOS_UINT8                           ucIsExist;
    VOS_UINT32                          ulLoop2;
    VOS_UINT16                          usClientId;

    pstCloudContrl = CSS_GetCloudContrlAddr();

    /* ��������״̬���ҵ����ڸ��µ�PID */
    for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
    {
        /* ��������PID���ڸ��� */
        if ((CSS_TRUE == pstCloudContrl->astMccUpdate[ulLoop].ucIsUpdating)
            &&(pstCloudContrl->astMccUpdate[ulLoop].ulPid == ulPId))
        {
            pstUpdate = &(pstCloudContrl->astMccUpdate[ulLoop]);
            break;
        }
    }

    /* ���ڶ�̬����û���ҵ���ͬ��PID�ڸ��£�������һ�� */
    if (CSS_NULL_PTR == pstUpdate)
    {
        for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
        {
            if (CSS_FALSE == pstCloudContrl->astMccUpdate[ulLoop].ucIsUpdating)
            {
                pstUpdate = &(pstCloudContrl->astMccUpdate[ulLoop]);
                break;
            }
        }
    }

    /* ����̬���Ѿ����� */
    if (CSS_NULL_PTR == pstUpdate)
    {
        return;
    }

    /* ��ֵ����״̬ */

    CSS_MEM_SET_S(  pstUpdate->aucUpdated,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM);

    for (ulLoop1 = 0; ulLoop1 < ulMccNum; ++ulLoop1)
    {
        /* ��������״̬������MCC�ڶ�̬�����Ƿ��Ѿ����� */
        if (CSS_TRUE == CSS_IsMccUpdatedAccordToUpdateStateTable(astMccID[ulLoop1].aucMccId))
        {
            pstUpdate->aucUpdated[ulLoop1] = CSS_TRUE;
            continue;
        }

        /* �������toSend�б��Ҳ���� */
        ucIsExist = CSS_FALSE;
        for (ulLoop2 = 0; ulLoop2 < ulMccNumToSend; ++ulLoop2)
        {
            if (CSS_TRUE == CSS_isMccMatch(astMccID[ulLoop1].aucMccId, astMccToSend[ulLoop2].aucMccId))
            {
                ucIsExist = CSS_TRUE;
                break;
            }
        }
        if (CSS_FALSE == ucIsExist)
        {
            pstUpdate->aucUpdated[ulLoop1] = CSS_TRUE;
        }
    }

    pstUpdate->ucIsUpdating = CSS_TRUE;
    pstUpdate->ulPid = ulPId;
    pstUpdate->usMccNum = (VOS_UINT16)ulMccNum;

    CSS_MEM_CPY_S(  pstUpdate->astMcc,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM,
                    astMccID,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM);

    /* ֹͣ��ʱ�� */
    CSS_StopTimer(&(pstUpdate->stTimer));

    if (I1_UEPS_PID_GAS == ulPId || I1_WUEPS_PID_MMC == ulPId)
    {
        usClientId = AT_BROADCAST_CLIENT_ID_MODEM_1;
    }
    else
    {
        usClientId = AT_BROADCAST_CLIENT_ID_MODEM_0;
    }

    if (0 < ulMccNumToSend)
    {
        /* ��AP����MCC�������� */
        CSS_SendAtQueryMccNotifyByMccList(astMccToSend, ulMccNumToSend, usClientId);
    }

    /* ������ʱ�� */
    pstUpdate->stTimer.usPara = (VOS_UINT16)ulPId;
    pstUpdate->stTimer.ulTimerLen = TI_CSS_WAIT_MCC_SET_ONE_MCC_LEN * pstUpdate->usMccNum;
    CSS_StartTimer(&(pstUpdate->stTimer));
}


/*****************************************************************************
 Function Name  : CSS_EndApUpdateProcedure
 Description    : ��ֹAP�ĸ�������
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_EndApUpdateProcedure(VOS_VOID)
{
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCssCloudContrl;

    pstCssCloudContrl = CSS_GetCloudContrlAddr();

    /* ��ʼ������ */
    pstCssCloudContrl->stApMccUpdate.ulPid = 0;
    pstCssCloudContrl->stApMccUpdate.ucIsUpdating = CSS_FALSE;
    pstCssCloudContrl->stApMccUpdate.usMccNum = CSS_FALSE;

    CSS_MEM_SET_S(  pstCssCloudContrl->stApMccUpdate.astMcc,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM);
    CSS_MEM_SET_S(  pstCssCloudContrl->stApMccUpdate.aucUpdated,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM);

    /* ֹͣ��ʱ�� */
    CSS_StopTimer(&(pstCssCloudContrl->stApMccUpdate.stTimer));
}

/*****************************************************************************
 Function Name  : CSS_EndMmcOrAsUpdateProcedure
 Description    : ��ֹMMC��AS�ĸ�������
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_EndMmcOrAsUpdateProcedure(CSS_MCC_UPDATE_STRU *pstUpdate)
{
    /* ��ʼ������ */
    pstUpdate->ulPid = 0;
    pstUpdate->ucIsUpdating = CSS_FALSE;
    pstUpdate->usMccNum = CSS_FALSE;

    CSS_MEM_SET_S(  pstUpdate->astMcc,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_UPDATE_MCC_NUM);
    CSS_MEM_SET_S(  pstUpdate->aucUpdated,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM,
                    0,
                    sizeof(VOS_UINT8)*CSS_MAX_UPDATE_MCC_NUM);

    /* ֹͣ��ʱ�� */
    CSS_StopTimer(&(pstUpdate->stTimer));
}




VOS_VOID CSS_CloudContrlTimerInit(VOS_VOID)
{
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCssCloudContrl;
    VOS_UINT32                          ulLoop;
    CSS_MCC_UPDATE_STRU                *pstUpdate;

    pstCssCloudContrl = CSS_GetCloudContrlAddr();

    pstCssCloudContrl->stApMccUpdate.stTimer.phTimer     = VOS_NULL_PTR;
    pstCssCloudContrl->stApMccUpdate.stTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCssCloudContrl->stApMccUpdate.stTimer.usName      = TI_CSS_WAIT_AP_UPDATE_MCC_SET_REQ;
    pstCssCloudContrl->stApMccUpdate.stTimer.ulTimerLen  = TI_CSS_WAIT_MCC_SET_ONE_MCC_LEN;

    for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
    {
        pstUpdate = &(pstCssCloudContrl->astMccUpdate[ulLoop]);
        pstUpdate->stTimer.phTimer    = VOS_NULL_PTR;
        pstUpdate->stTimer.ucMode     = VOS_RELTIMER_NOLOOP;
        pstUpdate->stTimer.usName     = TI_CSS_WAIT_MMC_OR_AS_UPDATE_MCC_SET_REQ;
        pstUpdate->stTimer.ulTimerLen = TI_CSS_WAIT_MCC_SET_ONE_MCC_LEN;

    }
}


/*****************************************************************************
 Function Name   : CSS_ReadNvCloudStrategy
 Description     : ��ȡ��ͨ��ʹ��NV
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32  CSS_ReadNvCloudStrategy(VOS_VOID)
{
    VOS_UINT32                          ulDataLen = 0;
    VOS_UINT32                          ulRslt    = CSS_FAIL;
    CSS_NV_CLOUD_STRATEGY_STRU          stCloudStrategy = {0};
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCloudControl;

    pstCloudControl = CSS_GetCloudContrlAddr();

    /* ��NV */
    ulDataLen = sizeof(CSS_NV_CLOUD_STRATEGY_STRU);
    ulRslt = CSS_NV_Read(   EN_NV_ID_PS_CLOUD_FREQ_STRATEGY,
                            (VOS_VOID *)(&stCloudStrategy),
                            ulDataLen);

    if(CSS_RESULT_FAIL == ulRslt)
    {
        CSS_WARN_LOG("CSS_ReadNvCloudStrategy: read NV Fail.");
        TLPS_PRINT2LAYER_WARNING(CSS_ReadNvCloudStrategy_ENUM, LNAS_ReadNvFail);

        return CSS_FAIL;
    }

    pstCloudControl->ucCloudEnable    = stCloudStrategy.ucEnable;
    pstCloudControl->ucPrefFreqEnable = stCloudStrategy.ucCssPrefFreq;

    return CSS_SUCC;
}

/*****************************************************************************
 Function Name   : CSS_ReadNvCloudPrefArfcn
 Description     : ��ȡNV��Ԥ��Ƶ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    chengmin 00285307      2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID  CSS_ReadNvCloudPrefArfcn(VOS_VOID)
{
    VOS_UINT32                          ulDataLen = 0;
    VOS_UINT32                          ulRslt    = CSS_FAIL;
    CSS_NV_PREF_MCC_STRU               *pstNvPerfFreq;

    CSS_INFO_LOG("CSS_ReadNvCloudPrefArfcn: enter");
    TLPS_PRINT2LAYER_INFO(CSS_ReadNvCloudPrefArfcn_ENUM, LNAS_ENTRY);


    pstNvPerfFreq = (CSS_NV_PREF_MCC_STRU*)CSS_MEM_ALLOC(sizeof(CSS_NV_PREF_MCC_STRU));
    if (CSS_NULL_PTR == pstNvPerfFreq)
    {
        return;
    }
    ulDataLen = sizeof(CSS_NV_PREF_MCC_STRU);

    /* ��MCC1 */
    CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));

    ulRslt = CSS_NV_Read(   EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC1,
                            (VOS_VOID *)(pstNvPerfFreq),
                            ulDataLen);
    if(CSS_RESULT_SUCC == ulRslt)
    {
        CSS_INFO_LOG("CSS_ReadNvCloudPrefArfcn: read NV1 SUCC.");
        TLPS_PRINT2LAYER_INFO(CSS_ReadNvCloudPrefArfcn_ENUM, LNAS_FUNCTION_LABEL1);
        CSS_AddNvOneMcc(pstNvPerfFreq, 0);
    }

    CSS_PrintLocalPrefFreqInfo();

    /* ��MCC2 */
    CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));

    ulRslt = CSS_NV_Read(   EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC2,
                            (VOS_VOID *)(pstNvPerfFreq),
                            ulDataLen);
    if(CSS_RESULT_SUCC == ulRslt)
    {
        CSS_INFO_LOG("CSS_ReadNvCloudPrefArfcn: read NV2 SUCC.");
        TLPS_PRINT2LAYER_INFO(CSS_ReadNvCloudPrefArfcn_ENUM, LNAS_FUNCTION_LABEL2);
        CSS_AddNvOneMcc(pstNvPerfFreq, 1);
    }

    CSS_PrintLocalPrefFreqInfo();

    /* ��MCC3 */
    CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));

    ulRslt = CSS_NV_Read(   EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC3,
                            (VOS_VOID *)(pstNvPerfFreq),
                            ulDataLen);
    if(CSS_RESULT_SUCC == ulRslt)
    {
        CSS_INFO_LOG("CSS_ReadNvCloudPrefArfcn: read NV3 SUCC.");
        TLPS_PRINT2LAYER_INFO(CSS_ReadNvCloudPrefArfcn_ENUM, LNAS_FUNCTION_LABEL3);
        CSS_AddNvOneMcc(pstNvPerfFreq, 2);
    }

    CSS_PrintLocalPrefFreqInfo();

    CSS_MEM_FREE(pstNvPerfFreq);

    return;
}


/*****************************************************************************
 Function Name   : CSS_AddNvRatSupport
 Description     : ����ʽ��֧�ּ���freq�ڵ���
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddNvRatSupport(VOS_UINT8 *pucRatSupport, CSS_RAT_TYPE_ENUM_UINT8 ucRat)
{
    VOS_UINT8                           ucRatFlagTmp = *pucRatSupport;
    /* ��ʽ��֧�֣���Ѹ���ʽ���� */
    if (CSS_FALSE == CSS_IsRatSupportInFlag(ucRat, ucRatFlagTmp))
    {
        if (CSS_RAT_GSM == ucRat)
        {
            ucRatFlagTmp |= CSS_GSM_SUPORT_OP;
        }
        if (CSS_RAT_UMTS_FDD== ucRat)
        {
            ucRatFlagTmp |= CSS_WCDMA_SUPORT_OP;
        }
        if (CSS_RAT_LTE == ucRat)
        {
            ucRatFlagTmp |= CSS_LTE_SUPORT_OP;
        }
    }
    *pucRatSupport = ucRatFlagTmp;
}



/*****************************************************************************
 Function Name   : CSS_AddNvOneFreq
 Description     : ��NV��һ��Ԥ��Ƶ����뵽�ڴ���BAND�ṹ��
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddNvOneFreq(CSS_PUB_PREF_BAND_STRU *pstBand, CSS_NV_PREF_ARFCN_STRU *pNvFreq, CSS_RAT_TYPE_ENUM_UINT8 ucRat)
{
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNode;

    pstFreqNode = pstBand->pstFreqHead;
    /* ѭ������������Ƶ���Ƿ��Ѵ��� */
    while (CSS_NULL_PTR != pstFreqNode)
    {
        if ((pNvFreq->ulArfcnBegin == pstFreqNode->ulFreqBegin)
             && (pNvFreq->ulArfcnEnd == pstFreqNode->ulFreqEnd))
        {
            CSS_AddNvRatSupport(&(pstFreqNode->ucRatSupport), ucRat);
            return;
        }
        pstFreqNode = pstFreqNode->pstNext;
    }

    /* ���Ƶ��û�У���������ڵ���� */
    pstFreqNode = (CSS_PUB_PREF_FREQ_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_FREQ_STRU));
    if (CSS_NULL_PTR == pstFreqNode)
    {
        return;
    }

    CSS_MEM_SET_S(pstFreqNode, sizeof(CSS_PUB_PREF_FREQ_STRU), 0, sizeof(CSS_PUB_PREF_FREQ_STRU));

    /* ��ֵƵ�� */
    if (pNvFreq->ulArfcnBegin > pNvFreq->ulArfcnEnd)
    {
        pstFreqNode->ulFreqBegin  = pNvFreq->ulArfcnEnd;
        pstFreqNode->ulFreqEnd    = pNvFreq->ulArfcnBegin;
    }
    else
    {
        pstFreqNode->ulFreqBegin = pNvFreq->ulArfcnBegin;
        pstFreqNode->ulFreqEnd   = pNvFreq->ulArfcnEnd;
    }

    CSS_AddNvRatSupport(&(pstFreqNode->ucRatSupport), ucRat);

    /*��ĩβ��ӽڵ�*/
    if (CSS_NULL_PTR == pstBand->pstFreqHead)
    {
        pstBand->pstFreqHead          = pstFreqNode;
        pstBand->pstFreqTail          = pstFreqNode;
    }
    else
    {
        pstBand->pstFreqTail->pstNext = pstFreqNode;
        pstBand->pstFreqTail          = pstFreqNode;
    }
    pstBand->ucFreqNum++;
}


/*****************************************************************************
 Function Name   : CSS_AddNvOneBand
 Description     : ��NV��һ��BAND��Ԥ��Ƶ����뵽�ڴ���BAND�ṹ��
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddNvOneBand(CSS_PUB_PREF_MNC_STRU *pstMnc, CSS_NV_PREF_MNC_STRU *pNvMnc)
{
    CSS_PUB_PREF_BAND_STRU             *pstBandNode;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucFreqNumTmp;

    ucFreqNumTmp = (pNvMnc->ucArfcnNum < CSS_NV_MAX_PREF_ARFCN_NUM) ? pNvMnc->ucArfcnNum : CSS_NV_MAX_PREF_ARFCN_NUM;

    pstBandNode = pstMnc->pstBandHead;

    /* ѭ���������ҵ���BAND�Ľڵ�ָ�� */
    while (CSS_NULL_PTR != pstBandNode)
    {
        if (pstBandNode->ucBandInd == pNvMnc->ucBandInd)
        {
            /* ���freq����Ϊ0����Ҫ����ʽ֧�ּ���BAND�ڵ��� */
            if (0 == ucFreqNumTmp)
            {
                CSS_AddNvRatSupport(&(pstBandNode->ucRatSupport), (CSS_RAT_TYPE_ENUM_UINT8)(pNvMnc->bitRat));
            }
            /* ���ν���FREQ���� */
            for (ulLoop = 0; ulLoop < ucFreqNumTmp; ++ulLoop)
            {
                CSS_AddNvOneFreq(pstBandNode, &(pNvMnc->astArfcn[ulLoop]), pNvMnc->bitRat);
            }
            return;
        }
        pstBandNode = pstBandNode->pstNext;
    }

    /* ��û���ҵ���������һ��BAND�ڵ� */
    pstBandNode = (CSS_PUB_PREF_BAND_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_BAND_STRU));
    if (CSS_NULL_PTR == pstBandNode)
    {
        return;
    }

    CSS_MEM_SET_S(pstBandNode, sizeof(CSS_PUB_PREF_BAND_STRU), 0, sizeof(CSS_PUB_PREF_BAND_STRU));

    pstBandNode->ucBandInd = pNvMnc->ucBandInd;

    /*��ĩβ��ӽڵ�*/
    if (CSS_NULL_PTR == pstMnc->pstBandHead)
    {
        pstMnc->pstBandHead          = pstBandNode;
        pstMnc->pstBandTail          = pstBandNode;
    }
    else
    {
        pstMnc->pstBandTail->pstNext = pstBandNode;
        pstMnc->pstBandTail          = pstBandNode;
    }

    /* ���freq����Ϊ0����Ҫ����ʽ֧�ּ���BAND�ڵ��� */
    if (0 == ucFreqNumTmp)
    {
        CSS_AddNvRatSupport(&(pstBandNode->ucRatSupport), (CSS_RAT_TYPE_ENUM_UINT8)(pNvMnc->bitRat));
    }

    /* ���ν���FREQ���� */
    for (ulLoop = 0; ulLoop < ucFreqNumTmp; ++ulLoop)
    {
        CSS_AddNvOneFreq(pstBandNode, &(pNvMnc->astArfcn[ulLoop]), pNvMnc->bitRat);
    }
    pstMnc->ucBandNum++;
}

/*****************************************************************************
 Function Name   : CSS_AddNvOneMnc
 Description     : ��NV��һ��MNC��Ԥ��Ƶ����뵽�ڴ���MNC�ṹ��
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddNvOneMnc(CSS_PUB_PREF_MCC_STRU *pstMcc, CSS_NV_PREF_MNC_STRU *pstNvMnc)
{
    CSS_PUB_PREF_MNC_STRU              *pstMncNode;
    VOS_UINT8                           aucMnc[2] = {0};

    /* ��ȡMNC ID */
    CSS_ConvertMncDigitToSimMnc(pstNvMnc->bitMncDigit1, pstNvMnc->bitMncDigit2, pstNvMnc->bitMncDigit3, aucMnc);

    /* ѭ���������ҵ���MNC�Ľڵ�ָ�� */
    pstMncNode = pstMcc->pstMncHead;
    while (CSS_NULL_PTR != pstMncNode)
    {
        if (CSS_TRUE == CSS_isMncMatch(pstMncNode->aucMncId, aucMnc))
        {
            /* ��BAND���� */
            CSS_AddNvOneBand(pstMncNode, pstNvMnc);
            return;
        }
        pstMncNode = pstMncNode->pstNext;
    }

    /* ��û���ҵ���������һ��MNC�ڵ� */
    pstMncNode = (CSS_PUB_PREF_MNC_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_MNC_STRU));
    if (CSS_NULL_PTR == pstMncNode)
    {
        return;
    }

    CSS_MEM_SET_S(pstMncNode, sizeof(CSS_PUB_PREF_MNC_STRU), 0, sizeof(CSS_PUB_PREF_MNC_STRU));

    /* ��MNC�ڵ����ݸ�ֵ */
    pstMncNode->aucMncId[0] = aucMnc[0];
    pstMncNode->aucMncId[1] = aucMnc[1];

    /*��ĩβ��ӽڵ�*/
    if (CSS_NULL_PTR == pstMcc->pstMncHead)
    {
        pstMcc->pstMncHead          = pstMncNode;
        pstMcc->pstMncTail          = pstMncNode;
    }
    else
    {
        pstMcc->pstMncTail->pstNext = pstMncNode;
        pstMcc->pstMncTail          = pstMncNode;
    }
    /* ���ν�BAND���� */
    CSS_AddNvOneBand(pstMncNode, pstNvMnc);
    pstMcc->ucMncNum++;
}


/*****************************************************************************
 Function Name   : CSS_AddNvOneMcc
 Description     : ��NV��һ�����ҵ�Ԥ��Ƶ������ڴ���
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
/*lint -e429*/
VOS_VOID CSS_AddNvOneMcc(CSS_NV_PREF_MCC_STRU *pPrefMcc, VOS_UINT32 ulIndex)
{
    CSS_PUB_PREF_MCC_STRU              *pstMccNode;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucMcc[2] = {0};
    CSS_CLOUD_PUB_CONTROL_STRU         *pContrl = CSS_GetCloudContrlAddr();
    VOS_UINT16                          usMncNumTmp;


    /* ��ָ��Ϊ���򷵻� */
    if (CSS_NULL_PTR == pPrefMcc)
    {
        return;
    }

    /* MCC��Ч�򷵻� */
    if ((0x0F == pPrefMcc->bitMccDigit1)
        || (0 == pPrefMcc->bitMccDigit1 && 0 == pPrefMcc->bitMccDigit2))
    {
        return;
    }

    /* ��ȡMCC ID */
    CSS_ConvertMccDigitToSimMcc(pPrefMcc->bitMccDigit1, pPrefMcc->bitMccDigit2, pPrefMcc->bitMccDigit3, aucMcc);

    usMncNumTmp = (pPrefMcc->usMncNum < CSS_NV_MAX_PREF_MNC_NUM) ? pPrefMcc->usMncNum : CSS_NV_MAX_PREF_MNC_NUM;

    /* ��ȡ����MCC ID�������ڴ��� */
    pContrl->astNvMcc[ulIndex].aucMccId[0] = aucMcc[0];
    pContrl->astNvMcc[ulIndex].aucMccId[1] = aucMcc[1];

    /* ѭ���������ҵ���MCC�Ľڵ�ָ�� */
    pstMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pstMccNode)
    {
        if (CSS_TRUE == CSS_isMccMatch(pstMccNode->aucMccId, aucMcc))
        {
            /* ���ν���MNC���� */
            for (ulLoop = 0; ulLoop < usMncNumTmp; ++ulLoop)
            {
                CSS_AddNvOneMnc(pstMccNode, &(pPrefMcc->astMnc[ulLoop]));
            }
            return;
        }
        pstMccNode = pstMccNode->pstNext;
    }

    /* ��û���ҵ���������һ��MCC�ڵ� */
    pstMccNode = (CSS_PUB_PREF_MCC_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_MCC_STRU));
    if (CSS_NULL_PTR == pstMccNode)
    {
        return;
    }

    CSS_MEM_SET_S(pstMccNode, sizeof(CSS_PUB_PREF_MCC_STRU), 0, sizeof(CSS_PUB_PREF_MCC_STRU));

    /* ��MCC�ڵ����ݸ�ֵ */
    pstMccNode->aucMccId[0] = aucMcc[0];
    pstMccNode->aucMccId[1] = aucMcc[1];

    /*��ĩβ��ӽڵ�*/
    if (CSS_NULL_PTR == CSS_GetPrefMccHeadNode())
    {
        CSS_GetPrefMccHeadNode()          = pstMccNode;
        CSS_GetPrefMccTailNode()          = pstMccNode;
    }
    else
    {
        CSS_GetPrefMccTailNode()->pstNext = pstMccNode;
        CSS_GetPrefMccTailNode()          = pstMccNode;
    }

    /* ���ν���MNC���� */
    for (ulLoop = 0; ulLoop < usMncNumTmp; ++ulLoop)
    {
        CSS_AddNvOneMnc(pstMccNode, &(pPrefMcc->astMnc[ulLoop]));
    }
    CSS_GetPrefMccNodeNum() ++;
}
/*lint +e429*/


VOS_UINT32 CSS_UpdateOneMcc(CSS_MCC_UPDATE_STRU *pMccUpdate, VOS_UINT8 aucMcc[2])
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < pMccUpdate->usMccNum; ++ulLoop)
    {
        if (CSS_TRUE == CSS_isMccMatch(aucMcc, pMccUpdate->astMcc[ulLoop].aucMccId))
        {
            pMccUpdate->aucUpdated[ulLoop] = CSS_TRUE;
            return CSS_TRUE;
        }
    }

    return CSS_FALSE;
}


VOS_UINT32 CSS_IsAllMccUpdated(CSS_MCC_UPDATE_STRU *pMccUpdate)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < pMccUpdate->usMccNum; ++ulLoop)
    {
        if (CSS_FALSE == pMccUpdate->aucUpdated[ulLoop])
        {
            return CSS_FALSE;
        }
    }
    return CSS_TRUE;
}



VOS_UINT32 CSS_IsMmcOrAsUpdating(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    CSS_CLOUD_PUB_CONTROL_STRU         *pCloudContrl;

    pCloudContrl = CSS_GetCloudContrlAddr();

    for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
    {
        if (CSS_TRUE == pCloudContrl->astMccUpdate[ulLoop].ucIsUpdating)
        {
            return CSS_TRUE;
        }
    }
    return CSS_FALSE;
}



VOS_VOID CSS_GetMccListFromLocal
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_MEMORY_PERF_MCC_NUM],
    VOS_UINT32                         *pulMccNum
)
{
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    VOS_UINT32                          ulNum = 0;

    /* ��ͷ��㿪ʼ���� */
    pMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pMccNode && ulNum < CSS_MAX_MEMORY_PERF_MCC_NUM)
    {
        astMccID[ulNum].aucMccId[0] = pMccNode->aucMccId[0];
        astMccID[ulNum].aucMccId[1] = pMccNode->aucMccId[1];
        ulNum++;
        pMccNode = pMccNode->pstNext;
    }
    *pulMccNum = ulNum;
}


/*****************************************************************************
 Function Name   : CSS_GetMccListFromLocal
 Description     : �ж�ĳ��MCC���ƶ�Ԥ��Ƶ���Ƶ���Ƿ��Ѿ���ȡ��
                   ������ͨ�����ݿ��ܲ�ȫ����ʹ��ȡ��MCC��Ԥ��Ƶ���Ƶ�Σ�Ҳ�п���û��ĳЩPLMN ID��Ԥ��Ƶ��
 Input           : ulPlmnNum      :MCC ID����
                   astPlmn        :MCC ID�б�MNC��0xFF����ʾMNC��Ч
 Output          :
 Return          : VOS_TRUE       :ȫ���ѻ�ȡ
                   VOS_FALSE      :û��ȫ����ȡ

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccFreqExist
(
    VOS_UINT32                                    ulPlmnNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PLMN_ID_NUM]
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucMcc[2] = {0};

    /* �Ϸ��Լ�� */
    if (ulPlmnNum > CSS_MAX_PLMN_ID_NUM
        || CSS_NULL_PTR == astPlmn)
    {
        return VOS_FALSE;
    }

    /* �����ͨ�����Բ�ʹ�ã�ֱ�ӷ��سɹ� */
    if (CSS_FALSE == CSS_IsCloudStrategyEnable())
    {
        CSS_INFO_LOG("CSS_IsMccFreqExist: cloud strategy is not enabled");
        TLPS_PRINT2LAYER_INFO(CSS_IsMccFreqExist_ENUM, LNAS_FUNCTION_LABEL1);
        return VOS_TRUE;
    }

    /* ��������ƶ˻�ȡ��Ҳֱ�ӷ���RSP�ɹ� */
    if (CSS_FALSE == CSS_IsPrefFreqEnable())
    {
        CSS_INFO_LOG("CSS_IsMccFreqExist: cloud pref freq is not enabled");
        TLPS_PRINT2LAYER_INFO(CSS_IsMccFreqExist_ENUM, LNAS_FUNCTION_LABEL2);
        return VOS_TRUE;
    }

    /* ��������MCC�������Ƿ񱾵��Ƿ����и�MCC���� */
    for (ulLoop = 0; ulLoop < ulPlmnNum; ++ulLoop)
    {

        /* ת��MCC�洢��ʽ */
        CSS_ConvertGuMccToSimMcc(astPlmn[ulLoop].ulMcc, aucMcc);

        /* ���û�д��ƶ˸��¹����򷵻�FALSE */
        if (CSS_FALSE == CSS_IsMccUpdatedFromAp(aucMcc))
        {
            /* Log */
            TLPS_PRINT2LAYER_INFO2(CSS_IsMccFreqExist_ENUM, LNAS_FUNCTION_LABEL3, astPlmn[ulLoop].ulMcc, astPlmn[ulLoop].ulMnc);

            return VOS_FALSE;
        }
    }
    return VOS_TRUE;
}



VOS_VOID CSS_GetPrefFreqFromBandNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_BAND_STRU             *pBandNode,
    VOS_UINT32                         *pulOutNum,
    CSS_PREF_FREQ_INFO_STRU            *pstOut
)
{
    CSS_PUB_PREF_FREQ_STRU             *pFreqNode;
    VOS_UINT32                          ulNum = *pulOutNum;
    VOS_UINT8                           ucIsExist;
    VOS_UINT32                          i;

    pFreqNode = pBandNode->pstFreqHead;
    /* ѭ����������FREQ�����֧����ʽ��Ƶ����� */
    while (CSS_NULL_PTR != pFreqNode)
    {
        if ((CSS_RAT_GSM == enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_GSM_SUPORT_OP))
             || (CSS_RAT_UMTS_FDD== enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_WCDMA_SUPORT_OP))
             || (CSS_RAT_LTE == enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_LTE_SUPORT_OP)))
        {
            /* �Ѵ������� */
            if (ulNum >= CSS_MAX_PREF_FREQ_NUM)
            {
                *pulOutNum = ulNum;
                return;
            }

            /* �ж��ظ� */
            ucIsExist = CSS_FALSE;
            for (i = 0; i < ulNum; ++i)
            {
                if ((pBandNode->ucBandInd == pstOut->astFreq[i].enBand)
                    && (pFreqNode->ulFreqBegin == pstOut->astFreq[i].ulFreqBegin)
                    && (pFreqNode->ulFreqEnd == pstOut->astFreq[i].ulFreqEnd))
                {
                    ucIsExist = CSS_TRUE;
                    break;
                }
            }
            if (CSS_FALSE == ucIsExist)
            {
                pstOut->astFreq[ulNum].enBand       = pBandNode->ucBandInd;
                pstOut->astFreq[ulNum].ulFreqBegin  = pFreqNode->ulFreqBegin;
                pstOut->astFreq[ulNum].ulFreqEnd    = pFreqNode->ulFreqEnd;
                ulNum++;
            }
        }

        pFreqNode = pFreqNode->pstNext;
    }
    *pulOutNum = ulNum;
}



VOS_VOID CSS_GetPrefFreqFromMncNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_MNC_STRU              *pMncNode,
    VOS_UINT32                         *pulOutNum,
    CSS_PREF_FREQ_INFO_STRU            *pstOut
)
{
    CSS_PUB_PREF_BAND_STRU             *pBandNode;

    pBandNode = pMncNode->pstBandHead;
    /* ѭ����������BAND�����ν�Ƶ����� */
    while (CSS_NULL_PTR != pBandNode)
    {
        CSS_GetPrefFreqFromBandNode(enRat, pBandNode, pulOutNum, pstOut);

        pBandNode = pBandNode->pstNext;
    }
}




VOS_VOID CSS_GetPrefFreqFromMccNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PLMN_ID_STRU                   *pstPlmn,
    CSS_PUB_PREF_MCC_STRU              *pMccNode,
    CSS_PREF_FREQ_INFO_STRU            *pstOut
)
{
    CSS_PUB_PREF_MNC_STRU              *pMncNode;
    VOS_UINT32                          ulFreqNum = 0;
    NAS_MML_PLMN_ID_STRU                stBccPlmnId = {0};
    NAS_MML_PLMN_ID_STRU                stSimPlmnId = {0};


    CSS_ConvertSimMccToGuMcc(pMccNode->aucMccId, &(stBccPlmnId.ulMcc));
    stSimPlmnId.ulMcc = pstPlmn->ulMcc;
    stSimPlmnId.ulMnc = pstPlmn->ulMnc;

    pMncNode = pMccNode->pstMncHead;
    while (CSS_NULL_PTR != pMncNode)
    {
        /* ���MNC��Ч����ʾ��ȡ��MNC��Ԥ��Ƶ�� */
        if (CSS_INVALID_MNC != pstPlmn->ulMnc)
        {
            CSS_ConvertSimMncToGuMnc(pMncNode->aucMncId, &(stBccPlmnId.ulMnc));

            /* ���MNCƥ�� */
            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stBccPlmnId, &stSimPlmnId))
            {
                CSS_GetPrefFreqFromMncNode(enRat, pMncNode, &ulFreqNum, pstOut);
                break;
            }
        }
        else
        {
            CSS_GetPrefFreqFromMncNode(enRat, pMncNode, &ulFreqNum, pstOut);
        }
        pMncNode = pMncNode->pstNext;
    }

    /* ��ֵ���� */
    pstOut->ulFreqNum    = ulFreqNum;
}



CSS_RESULT_ENUM_UINT32 CSS_GetPreferFreqInfo
(
    CSS_RAT_TYPE_ENUM_UINT8                       enRat,
    VOS_UINT32                                    ulPlmnIdNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                   *pulOutPlmnNum,
    CSS_PREF_FREQ_INFO_STRU                       astPrefFreq[CSS_MAX_PREF_PLMN_NUM]
)
{
    VOS_UINT32                          ulLoop;
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    VOS_UINT8                           aucMcc[2] = {0};
    VOS_UINT32                          ulTmpNum;
    CSS_PLMN_ID_STRU                    astTmpPlmn[CSS_MAX_PREF_PLMN_NUM] = {{0}};

    TLPS_PRINT2LAYER_INFO1(CSS_GetPreferFreqInfo_ENUM, LNAS_ENTRY, enRat);

    /* �Ϸ��Լ�� */
    if (ulPlmnIdNum > CSS_MAX_PREF_PLMN_NUM
        || CSS_NULL_PTR == astPlmn
        || CSS_NULL_PTR == pulOutPlmnNum
        || CSS_NULL_PTR == astPrefFreq)
    {
        TLPS_PRINT2LAYER_INFO(CSS_GetPreferFreqInfo_ENUM, LNAS_NULL_PTR);
        return CSS_RESULT_FAIL;
    }

    /* �����ͨ�����Բ�ʹ�ã�ֱ�ӷ��ز���ʧ�� */
    if (CSS_FALSE == CSS_IsCloudStrategyEnable())
    {
        TLPS_PRINT2LAYER_INFO(CSS_GetPreferFreqInfo_ENUM, LNAS_FUNCTION_LABEL1);
        return CSS_RESULT_FAIL;
    }

    /* log ��ӡ */
    for (ulLoop = 0; ulLoop < ulPlmnIdNum; ++ulLoop)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPreferFreqInfo_ENUM, LNAS_FUNCTION_LABEL2, astPlmn[ulLoop].ulMcc, astPlmn[ulLoop].ulMnc);
    }

    /* ���ĳ��MCC���ڶ�MCC���ң��򽫸ù�������MCC���� */
    CSS_GetAllMccBelongToOneCountry(ulPlmnIdNum, astPlmn, &ulTmpNum, astTmpPlmn);
    *pulOutPlmnNum = ulTmpNum;

    /* log ��ӡ */
    for (ulLoop = 0; ulLoop < ulTmpNum; ++ulLoop)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPreferFreqInfo_ENUM, LNAS_FUNCTION_LABEL3, astTmpPlmn[ulLoop].ulMcc, astTmpPlmn[ulLoop].ulMnc);
    }

    for (ulLoop = 0; ulLoop < ulTmpNum; ++ulLoop)
    {
        /* �ȸ���������ֵ */
        astPrefFreq[ulLoop].ulFreqNum = 0;

        /* ȡ��MCC */
        CSS_ConvertGuMccToSimMcc(astTmpPlmn[ulLoop].ulMcc, aucMcc);

        /* ��ֵMCC */
        astPrefFreq[ulLoop].stPlmn.ulMcc = astTmpPlmn[ulLoop].ulMcc;
        astPrefFreq[ulLoop].stPlmn.ulMnc = astTmpPlmn[ulLoop].ulMnc;

        pMccNode = CSS_GetPrefMccHeadNode();
        while (CSS_NULL_PTR != pMccNode)
        {
            /* ��MCC IDƥ�䣬��MCC�µ�MNC���� */
            if (CSS_TRUE == CSS_isMccMatch(pMccNode->aucMccId, aucMcc))
            {
                CSS_GetPrefFreqFromMccNode(enRat, &(astTmpPlmn[ulLoop]), pMccNode, &(astPrefFreq[ulLoop]));
            }
            pMccNode = pMccNode->pstNext;
        }
    }

    /* ��Ϣ���� */
    for (ulLoop = 0; ulLoop < ulTmpNum; ++ulLoop)
    {
        CSS_SendOmGetOnePlmnPrefFreqRslt(enRat, ulPlmnIdNum, astPlmn, CSS_RESULT_SUCC, &(astPrefFreq[ulLoop]));
    }
    return CSS_RESULT_SUCC;
}



VOS_UINT32 CSS_IsBandNodeSupportRat
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_BAND_STRU             *pBandNode
)
{
    CSS_PUB_PREF_FREQ_STRU             *pFreqNode;

    /* ���ж�BANDָ���е���ʽ֧�� */
    if ((CSS_RAT_GSM == enRat && CSS_FALSE != (pBandNode->ucRatSupport & CSS_GSM_SUPORT_OP))
         || (CSS_RAT_UMTS_FDD== enRat && CSS_FALSE != (pBandNode->ucRatSupport & CSS_WCDMA_SUPORT_OP))
         || (CSS_RAT_LTE == enRat && CSS_FALSE != (pBandNode->ucRatSupport & CSS_LTE_SUPORT_OP)))
    {
        return CSS_TRUE;
    }

    /* ���FREQ������Ϊ0�������ÿ��FREQ�����ж��Ƿ�֧�� */
    pFreqNode = pBandNode->pstFreqHead;
    while (CSS_NULL_PTR != pFreqNode)
    {
        if ((CSS_RAT_GSM == enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_GSM_SUPORT_OP))
             || (CSS_RAT_UMTS_FDD== enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_WCDMA_SUPORT_OP))
             || (CSS_RAT_LTE == enRat && CSS_FALSE != (pFreqNode->ucRatSupport & CSS_LTE_SUPORT_OP)))
        {
            return CSS_TRUE;
        }

        pFreqNode = pFreqNode->pstNext;
    }
    return CSS_FALSE;
}




VOS_VOID CSS_GetPrefBandFromMncNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_MNC_STRU              *pMncNode,
    VOS_UINT32                         *pulOutNum,
    CSS_PREF_BAND_INFO_STRU            *pstOut
)
{
    CSS_PUB_PREF_BAND_STRU             *pBandNode;
    VOS_UINT32                          ulBandNum = *pulOutNum;
    VOS_UINT8                           ucIsExist;
    VOS_UINT32                          i;

    pBandNode = pMncNode->pstBandHead;
    while (CSS_NULL_PTR != pBandNode)
    {
        if (CSS_TRUE == CSS_IsBandNodeSupportRat(enRat, pBandNode))
        {
            /* �Ѵ������� */
            if (ulBandNum >= CSS_MAX_PREF_BAND_NUM)
            {
                *pulOutNum = ulBandNum;
                return;
            }
            /* �ж��ظ� */
            ucIsExist = CSS_FALSE;
            for (i = 0; i < ulBandNum; ++i)
            {
                if (pBandNode->ucBandInd == pstOut->ausBand[i])
                {
                    ucIsExist = CSS_TRUE;
                    break;
                }
            }
            if (CSS_FALSE == ucIsExist)
            {
                pstOut->ausBand[ulBandNum] = pBandNode->ucBandInd;
                ulBandNum++;
            }
        }

        pBandNode = pBandNode->pstNext;
    }
    *pulOutNum = ulBandNum;
}

/*****************************************************************************
 Function Name   : CSS_IsRatHasNoPrefBand
 Description     : �ж�ĳ����ʽ��PLMN���Ƿ�û���ƶ�BAND
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsRatHasNoPrefBand
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PUB_PREF_MNC_STRU              *pMncNode
)
{
    return CSS_IsRatSupportInFlag(enRat, pMncNode->ucNoPrefBandFlg);
}

/*****************************************************************************
 Function Name   : CSS_JudgeMultiMccCountryHasPrefBand
 Description     : �ж�ĳ����ʽ��PLMN���Ƿ�û���ƶ�BAND,������Ϊ0��MCCɾ������Ϊ0�����ݱ���
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_JudgeMultiMccCountryHasPrefBand
(
    VOS_UINT32                         *pulNum,
    CSS_PREF_BAND_INFO_STRU             astPrefBand[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                          aulResult[CSS_MAX_PREF_PLMN_NUM]
)
{
    VOS_UINT32                          i,j;
    VOS_UINT8                           ucIsMccHasData;
    VOS_UINT8                           ucDeleteFlag[CSS_MAX_PREF_PLMN_NUM] = {0};
    VOS_UINT32                          ulNumCopy;
    CSS_PREF_BAND_INFO_STRU             *pastPrefBandCopy;

    pastPrefBandCopy = CSS_MEM_ALLOC(sizeof(CSS_PREF_BAND_INFO_STRU)*CSS_MAX_PREF_PLMN_NUM);
    if (CSS_NULL_PTR == pastPrefBandCopy)
    {
        return CSS_FAIL;
    }

    /* ����ԭʼ���� */
    ulNumCopy = *pulNum;

    CSS_MEM_CPY_S(  pastPrefBandCopy,
                    sizeof(CSS_PREF_BAND_INFO_STRU)*CSS_MAX_PREF_PLMN_NUM,
                    astPrefBand,
                    sizeof(CSS_PREF_BAND_INFO_STRU)*CSS_MAX_PREF_PLMN_NUM);

    /* ԭʼ������գ���������¸�ֵ */
    *pulNum = 0;

    CSS_MEM_SET_S(  astPrefBand,
                    sizeof(CSS_PREF_BAND_INFO_STRU)*CSS_MAX_PREF_PLMN_NUM,
                    0,
                    sizeof(CSS_PREF_BAND_INFO_STRU)*CSS_MAX_PREF_PLMN_NUM);

    TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_ENTRY);

    /* �������е�MCC�����Ƚϣ������������ͬһ�����ң���������һ��MCCԤ��BAND����Ϊ0����һ����Ϊ0����Ϊ0��mCCɾ�������سɹ� */
    for (i = 0; i < ulNumCopy; ++i)
    {
        if (CSS_FAIL == aulResult[i])
        {
            TLPS_PRINT2LAYER_INFO1(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetPrefBandFromMccNodeFail,CSS_FAIL);
            /* ����ǻ���PLMN��ȡ��ֱ�ӷ���ʧ�� */
            if (CSS_INVALID_MNC != pastPrefBandCopy[i].stPlmn.ulMnc)
            {
                TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetPrefBandInfoFailAndPlmnWithInvalidMnc);
                CSS_MEM_FREE(pastPrefBandCopy);
                return CSS_FAIL;
            }

            /* �Ȱѵ�MCC��������� */
            if (CSS_FALSE == CSS_IsMccBelongToMultiCountry(pastPrefBandCopy[i].stPlmn.ulMcc))
            {
                TLPS_PRINT2LAYER_INFO1(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetPrefBandInfoFailAndMccNotBelongToMultiCountry,pastPrefBandCopy[i].stPlmn.ulMcc);
                CSS_MEM_FREE(pastPrefBandCopy);
                return CSS_FAIL;
            }


            /* �����MCC���ҵ�MCC */
            ucIsMccHasData = CSS_FALSE;
            for(j = 0; j < ulNumCopy; ++j)
            {
                /* ��������ͬһ���ң���������һ��MCC��Ԥ��BAND��Ϊ0 */
                if ((CSS_TRUE == CSS_IsTwoMccBelongToOneCountry(pastPrefBandCopy[i].stPlmn.ulMcc, pastPrefBandCopy[j].stPlmn.ulMcc))
                     && (CSS_SUCC == aulResult[j]))
                {
                    ucDeleteFlag[i] = CSS_TRUE;
                    ucIsMccHasData = CSS_TRUE;
                    TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_TwoMccBelongToOneCountry);
                    break;
                }
            }
            if (CSS_FALSE == ucIsMccHasData)
            {
                TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetNoPrefBandInfoFromOtherMccBelongToOneCountry);
                CSS_MEM_FREE(pastPrefBandCopy);
                return CSS_FAIL;
            }
        }
    }

    /* ��flag��Ϊ1��MCC�޳���������MCC�������б��� */
    for (i = 0; i < ulNumCopy; ++i)
    {
        if (CSS_TRUE != ucDeleteFlag[i])
        {
            CSS_MEM_CPY_S(  &(astPrefBand[*pulNum]),
                            sizeof(CSS_PREF_BAND_INFO_STRU),
                            &(pastPrefBandCopy[i]),
                            sizeof(CSS_PREF_BAND_INFO_STRU));

            (*pulNum)++;
            TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_SaveBandInfoForGetResult);
        }
    }

    /* �쳣���� */
    if (0 == *pulNum)
    {
        TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetPreferBandInfoFail);
        CSS_MEM_FREE(pastPrefBandCopy);
        return CSS_FAIL;
    }

    /* ������PLMN��MCC��û������ʱ��������Ϊ0�����سɹ� */
    ucIsMccHasData = CSS_FALSE;
    for (i = 0; i < *pulNum; ++i)
    {
        if (0 != astPrefBand[i].ulBandNum)
        {
            ucIsMccHasData = CSS_TRUE;
            break;
        }
    }
    if (CSS_FALSE == ucIsMccHasData)
    {
        *pulNum = 0;
    }
    TLPS_PRINT2LAYER_INFO(CSS_JudgeMultiMccCountryHasPrefBand_ENUM, LNAS_CSS_GetPreferBandInfoSucc);
    CSS_MEM_FREE(pastPrefBandCopy);
    return CSS_SUCC;
}


VOS_UINT32 CSS_GetPrefBandFromMccNode
(
    CSS_RAT_TYPE_ENUM_UINT8             enRat,
    CSS_PLMN_ID_STRU                   *pstPlmn,
    CSS_PUB_PREF_MCC_STRU              *pMccNode,
    CSS_PREF_BAND_INFO_STRU            *pstOut
)
{
    CSS_PUB_PREF_MNC_STRU              *pMncNode;
    VOS_UINT32                          ulBandNum = 0;
    VOS_UINT8                           ucExistPrefBand = CSS_FALSE;/* �Ƿ���һ��MNCû�б��ƶ���ȷָ��û��Ԥ��BAND */
    NAS_MML_PLMN_ID_STRU                stBccPlmnId = {0};
    NAS_MML_PLMN_ID_STRU                stSimPlmnId = {0};


    CSS_ConvertSimMccToGuMcc(pMccNode->aucMccId, &(stBccPlmnId.ulMcc));
    stSimPlmnId.ulMcc = pstPlmn->ulMcc;
    stSimPlmnId.ulMnc = pstPlmn->ulMnc;

    pMncNode = pMccNode->pstMncHead;
    if (CSS_NULL_PTR == pMncNode)
    {
        TLPS_PRINT2LAYER_INFO1(CSS_GetPrefBandFromMccNode_ENUM, LNAS_CSS_MncNodeNull, enRat);
        return CSS_FAIL;
    }

    while (CSS_NULL_PTR != pMncNode)
    {
        if (CSS_INVALID_MNC != pstPlmn->ulMnc)
        {
            CSS_ConvertSimMncToGuMnc(pMncNode->aucMncId, &(stBccPlmnId.ulMnc));

            /* ���MNCƥ�� */
            if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stBccPlmnId, &stSimPlmnId))
            {
                /* ����ƶ���ȷû��Ԥ��BAND����ֱ�ӷ��سɹ������Ҹ���Ϊ0 */
                if (CSS_TRUE == CSS_IsRatHasNoPrefBand(enRat, pMncNode))
                {
                    TLPS_PRINT2LAYER_INFO2(CSS_GetPrefBandFromMccNode_ENUM, LNAS_FUNCTION_LABEL1, pstPlmn->ulMcc, pstPlmn->ulMnc);
                    pstOut->ulBandNum    = 0;
                    return CSS_SUCC;
                }
                CSS_GetPrefBandFromMncNode(enRat, pMncNode, &ulBandNum, pstOut);
                break;
            }
        }
        else
        {
            /* ����ƶ���ȷû��Ԥ��BAND���򲻻�ȡ */
            if (CSS_TRUE == CSS_IsRatHasNoPrefBand(enRat, pMncNode))
            {
                TLPS_PRINT2LAYER_INFO2(CSS_GetPrefBandFromMccNode_ENUM, LNAS_FUNCTION_LABEL2, pstPlmn->ulMcc, pstPlmn->ulMnc);
            }
            else
            {
                CSS_GetPrefBandFromMncNode(enRat, pMncNode, &ulBandNum, pstOut);
                ucExistPrefBand = CSS_TRUE;
            }
        }
        pMncNode = pMncNode->pstNext;
    }

    /* ����MCC��ȡԤ��BANDʱ��������MNC����ȷû��Ԥ��BAND���򷵻سɹ�������Ϊ0 */
    if ((CSS_INVALID_MNC == pstPlmn->ulMnc) && (CSS_FALSE == ucExistPrefBand))
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPrefBandFromMccNode_ENUM, LNAS_FUNCTION_LABEL3, pstPlmn->ulMcc, pstPlmn->ulMnc);
        pstOut->ulBandNum    = 0;
        return CSS_SUCC;
    }

    pstOut->ulBandNum    = ulBandNum;
    if (0 == ulBandNum)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPrefBandFromMccNode_ENUM, LNAS_CSS_GetNoPrefBandWithPlmn, pstPlmn->ulMcc, pstPlmn->ulMnc);
        return CSS_FAIL;
    }
    TLPS_PRINT2LAYER_INFO2(CSS_GetPrefBandFromMccNode_ENUM, LNAS_CSS_GetPrefBandSuccWithPlmn, pstPlmn->ulMcc, pstPlmn->ulMnc);
    return CSS_SUCC;
}



CSS_RESULT_ENUM_UINT32 CSS_GetPreferBandInfo
(
    CSS_RAT_TYPE_ENUM_UINT8                       enRat,
    VOS_UINT32                                    ulPlmnIdNum,
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM],
    VOS_UINT32                                   *pulOutPlmnNum,
    CSS_PREF_BAND_INFO_STRU                       astPrefBand[CSS_MAX_PREF_PLMN_NUM]
)
{
    VOS_UINT32                          ulLoop;
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    VOS_UINT8                           aucMcc[2] = {0};
    VOS_UINT32                          ulTmpNum;
    CSS_PLMN_ID_STRU                    astTmpPlmn[CSS_MAX_PREF_PLMN_NUM] = {{0}};
    VOS_UINT8                           ucTmpNodeNum = 0;
    VOS_UINT32                          aulResult[CSS_MAX_PREF_PLMN_NUM] = {0};

    TLPS_PRINT2LAYER_INFO1(CSS_GetPreferBandInfo_ENUM, LNAS_ENTRY, enRat);

    /* �Ϸ��Լ�� */
    if (ulPlmnIdNum > CSS_MAX_PREF_PLMN_NUM
        || CSS_NULL_PTR == astPlmn
        || CSS_NULL_PTR == pulOutPlmnNum
        || CSS_NULL_PTR == astPrefBand)
    {
        TLPS_PRINT2LAYER_INFO(CSS_GetPreferBandInfo_ENUM, LNAS_NULL_PTR);
        return CSS_RESULT_FAIL;
    }

    /* �����ͨ�����Բ�ʹ�ã�ֱ�ӷ��ز���ʧ�� */
    if (CSS_FALSE == CSS_IsCloudStrategyEnable())
    {
        TLPS_PRINT2LAYER_INFO(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL1);
        return CSS_RESULT_FAIL;
    }

    /* log ��ӡ */
    for (ulLoop = 0; ulLoop < ulPlmnIdNum; ++ulLoop)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL2, astPlmn[ulLoop].ulMcc, astPlmn[ulLoop].ulMnc);
    }

    /* ���ĳ��MCC���ڶ�MCC���ң��򽫸ù�������MCC���� */
    CSS_GetAllMccBelongToOneCountry(ulPlmnIdNum, astPlmn, &ulTmpNum, astTmpPlmn);
    *pulOutPlmnNum = ulTmpNum;

    /* log ��ӡ */
    for (ulLoop = 0; ulLoop < ulTmpNum; ++ulLoop)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL3, astTmpPlmn[ulLoop].ulMcc, astTmpPlmn[ulLoop].ulMnc);
    }

    for (ulLoop = 0; ulLoop < ulTmpNum; ++ulLoop)
    {
        /* Ĭ��ֵΪFAIL */
        aulResult[ulLoop] = CSS_FAIL;

        /* �ȸ���������ֵ */
        astPrefBand[ulLoop].ulBandNum = 0;

        ucTmpNodeNum = 0;

        /* ȡ��MCC */
        CSS_ConvertGuMccToSimMcc(astTmpPlmn[ulLoop].ulMcc, aucMcc);

        /* ��ֵMCC */
        astPrefBand[ulLoop].stPlmn.ulMcc = astTmpPlmn[ulLoop].ulMcc;
        astPrefBand[ulLoop].stPlmn.ulMnc = astTmpPlmn[ulLoop].ulMnc;

        /* ���ұ����ڴ�����нڵ� */
        pMccNode = CSS_GetPrefMccHeadNode();
        /* �����ϣ��������ýӿ�ǰ�϶��Ѿ�����ȡ�ƶ������˴�ʱMCC����������Ϊ0���������Ϊ0�������쳣�ˡ�
           ���ڷ��տ��ǣ�Ӧ�÷���ʧ���ý�������ȫBAND��*/
        if (CSS_NULL_PTR == pMccNode)
        {
            TLPS_PRINT2LAYER_INFO1(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL4, ulLoop);
            return CSS_RESULT_FAIL;
        }
        while (CSS_NULL_PTR != pMccNode)
        {
            if (CSS_TRUE == CSS_isMccMatch(pMccNode->aucMccId, aucMcc))
            {
                /* ��������������� */
                aulResult[ulLoop] = CSS_GetPrefBandFromMccNode(enRat, &(astTmpPlmn[ulLoop]), pMccNode, &(astPrefBand[ulLoop]));
                TLPS_PRINT2LAYER_INFO2(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL5, ulLoop, aulResult[ulLoop]);
                TLPS_PRINT2LAYER_INFO1(CSS_GetPreferBandInfo_ENUM, LNAS_FUNCTION_LABEL5, ucTmpNodeNum);
                break;
            }
            pMccNode = pMccNode->pstNext;
            ucTmpNodeNum ++;
        }
    }

    if (CSS_FAIL == CSS_JudgeMultiMccCountryHasPrefBand(pulOutPlmnNum, astPrefBand, aulResult))
    {
        /* add */
        TLPS_PRINT2LAYER_INFO(CSS_GetPreferBandInfo_ENUM, LNAS_CSS_GetPreferBandInfoFail);
        /* add */
        CSS_SendOmGetPrefBandRslt(enRat,ulPlmnIdNum,astPlmn,aulResult,CSS_RESULT_FAIL,*pulOutPlmnNum, astPrefBand);
        return CSS_RESULT_FAIL;
    }

    CSS_SendOmGetPrefBandRslt(enRat,ulPlmnIdNum,astPlmn,aulResult,CSS_RESULT_SUCC,*pulOutPlmnNum, astPrefBand);

    return CSS_RESULT_SUCC;
}

/*****************************************************************************
 Function Name   : CSS_CheckMccIsValid
 Description     : �ж�MCC�Ƿ���Ч
 Input           :
 Output          : VOS_TRUE --��Ч
                   VOS_FALSE--��Ч
 Return          :

 History         :
    1.qinxuying 00355475 2016-02-17  Draft Enact
*****************************************************************************/
VOS_UINT32    CSS_CheckMccIsValid
(
    VOS_UINT8                           aucMcc[2]
)
{
    VOS_UINT8                          ucMccDigit1 = 0;
    VOS_UINT8                          ucMccDigit2 = 0;
    VOS_UINT8                          ucMccDigit3 = 0;

    ucMccDigit1 = aucMcc[0] & CSS_OCTET_LOW_4_BITS;
    ucMccDigit2 = (aucMcc[0] & CSS_OCTET_HIGH_4_BITS) >> CSS_OCTET_MOVE_4_BITS;
    ucMccDigit3 = aucMcc[1] & CSS_OCTET_LOW_4_BITS;

    if ((ucMccDigit1 <= CSS_DEC_DIGIT_9) &&
        (ucMccDigit2 <= CSS_DEC_DIGIT_9) &&
        (ucMccDigit3 <= CSS_DEC_DIGIT_9))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function Name   : CSS_GetMccFromPlmnArr
 Description     : ��PLMN�������ҳ�MCC
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_GetMccFromPlmnArr
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                         *pulMccNum,
    const CSS_PLMN_ID_STRU              astPlmnId[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulPlmnNum
)
{
    VOS_UINT32                          ulLoop1,ulLoop2;
    VOS_UINT32                          ulMccNum = 0;
    VOS_UINT32                          ulIsExist = CSS_FALSE;
    VOS_UINT32                          ulIsValid = CSS_FALSE;
    VOS_UINT8                           aucMcc[2] = {0};

    CSS_MEM_SET_S(astMccID, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM, 0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    /* ��������PLMN ID������������ */
    for (ulLoop1 = 0; ulLoop1 < ulPlmnNum; ++ulLoop1)
    {
        ulIsExist = CSS_FALSE;

        CSS_ConvertGuMccToSimMcc(astPlmnId[ulLoop1].ulMcc, aucMcc);

        ulIsValid = CSS_CheckMccIsValid(aucMcc);
        if ( VOS_TRUE != ulIsValid )
        {
            continue;
        }

        /* �鿴�������Ƿ��Ѿ����� */
        for (ulLoop2 = 0; ulLoop2 < ulMccNum; ++ulLoop2)
        {
            if (CSS_TRUE == CSS_isMccMatch(aucMcc, astMccID[ulLoop2].aucMccId))
            {
                ulIsExist = CSS_TRUE;
                break;
            }
        }
        /* ����������� */
        if (CSS_FALSE == ulIsExist)
        {
            astMccID[ulMccNum].aucMccId[0] = aucMcc[0];
            astMccID[ulMccNum].aucMccId[1] = aucMcc[1];
            ulMccNum++;
        }
    }
    *pulMccNum = ulMccNum;
}

/*****************************************************************************
 Function Name   : CSS_IsMccUpdatedFromAp
 Description     : �鿴ĳmCC�Ƿ���ƶ˸��¹�
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccUpdatedFromAp(VOS_UINT8 aucMcc[2])
{
    VOS_UINT32                          i,j;
    VOS_UINT32                          ulTmpMcc;
    VOS_UINT8                           aucTmpMcc[2] = {0};

    if (CSS_TRUE == CSS_IsMccExistInLocal(aucMcc))
    {
        return CSS_TRUE;
    }

    /* sim����ʽת��ΪGU�ĸ�ʽ */
    CSS_ConvertSimMccToGuMcc(aucMcc, &ulTmpMcc);

    for (i = 0; i < CSS_MCC_COUNTY_NUM; ++i)
    {
        if (CSS_TRUE == CSS_IsMccBelongToCountry(ulTmpMcc, &(g_astCountryMccList[i])))
        {
            for (j = 0; j < g_astCountryMccList[i].ulMccNum; ++j)
            {
                /* gu��ʽת��Ϊsim����ʽ  */
                CSS_ConvertGuMccToSimMcc(g_astCountryMccList[i].pulMccListAddr[j], aucTmpMcc);

                if (CSS_TRUE == CSS_IsMccExistInLocal(aucTmpMcc))
                {
                    return CSS_TRUE;
                }
            }
        }

    }
    return CSS_FALSE;
}



VOS_VOID CSS_DeleteSameMccAccordToLocal
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                         *pulMccNum
)
{
    CSS_MCC_ID_STRU                     astMccIDCopy[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                          ulNumCopy;
    VOS_UINT8                           ucExistFlag[CSS_MAX_PLMN_ID_NUM] = {0};
    VOS_UINT32                          ulLoop;

    CSS_MEM_SET_S(astMccIDCopy, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM, 0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    /* �Ƚ�ԭʼMCC�б���һ�ݿ��� */
    CSS_MEM_CPY_S(astMccIDCopy, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                            astMccID, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);
    ulNumCopy = *pulMccNum;

    /* ��ԭʼ��MCC�б���������������Ҫ��ʼ��ֵ */
    CSS_MEM_SET_S(astMccID, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM, 0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);
    *pulMccNum = 0;

    /* �Կ�������ѭ�����������ұ����Ƿ���ڸ�MCC��Ԥ��Ƶ�� */
    for (ulLoop = 0; ulLoop < ulNumCopy; ++ulLoop)
    {
        if (CSS_TRUE == CSS_IsMccUpdatedFromAp(astMccIDCopy[ulLoop].aucMccId))
        {
            /* �����Ѹ��¹���MCC��Ԥ��Ƶ�㣬�򽫴��޳���FLAG��ΪTRUE */
            ucExistFlag[ulLoop] = CSS_TRUE;
        }
    }

    /* ��������MCC��FALG��ΪTRUE���޳��������뵽ԭʼMCC�б��� */
    for (ulLoop = 0; ulLoop < ulNumCopy; ++ulLoop)
    {
        if (CSS_FALSE == ucExistFlag[ulLoop])
        {
            astMccID[*pulMccNum].aucMccId[0] = astMccIDCopy[ulLoop].aucMccId[0];
            astMccID[*pulMccNum].aucMccId[1] = astMccIDCopy[ulLoop].aucMccId[1];
            (*pulMccNum) += 1;
        }
    }
}

/*****************************************************************************
 Function Name   : CSS_IsMccUpdatingInUpdateStateTable
 Description     : ���MCC���ڵȴ��ƶ��·���ɾ��
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccUpdatingInUpdateStateTable
(
    VOS_UINT8                           aucMccID[2]
)
{
    VOS_UINT32                          ulLoop2;
    VOS_UINT32                          ulLoop3;
    CSS_MCC_UPDATE_STRU                *pstUpdate;
    CSS_CLOUD_PUB_CONTROL_STRU         *pCloudContrl = CSS_GetCloudContrlAddr();

    /* ��ÿ��MMC��AS״̬����� */
    for (ulLoop2 = 0; ulLoop2 < CSS_MAX_PID_NUM; ++ulLoop2)
    {
        pstUpdate = &(pCloudContrl->astMccUpdate[ulLoop2]);
        /* ��״̬�����ڸ���״̬�� */
        if (CSS_TRUE == pstUpdate->ucIsUpdating)
        {
            /* ������״̬���ÿ��MCC�����Ƿ��뿽���е�MCCһ�� */
            for (ulLoop3 = 0; ulLoop3 < pstUpdate->usMccNum; ++ulLoop3)
            {
                if (CSS_TRUE == CSS_isMccMatch(aucMccID, pstUpdate->astMcc[ulLoop3].aucMccId))
                {
                    return CSS_TRUE;
                }
            }
        }
    }

    /* ��AP�ĸ������ڽ����� */
    if (CSS_TRUE == pCloudContrl->stApMccUpdate.ucIsUpdating)
    {
        /* ������״̬���ÿ��MCC�����Ƿ��뿽���е�MCCһ�� */
        for (ulLoop2 = 0; ulLoop2 < pCloudContrl->stApMccUpdate.usMccNum; ++ulLoop2)
        {
            if (CSS_TRUE == CSS_isMccMatch(aucMccID, pCloudContrl->stApMccUpdate.astMcc[ulLoop2].aucMccId))
            {
                return CSS_TRUE;
            }
        }
    }
    return CSS_FALSE;
}


/*****************************************************************************
 Function Name   : CSS_DeleteMccAlreadySndToAp
 Description     : ���MCC���ڵȴ��ƶ��·���ɾ��
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_DeleteMccAlreadySndToAp
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                         *pulMccNum
)
{
    VOS_UINT32                          ulLoop1;
    CSS_MCC_ID_STRU                     astMccIDCopy[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                          ulNumCopy;
    VOS_UINT8                           ucExistFlag[CSS_MAX_PLMN_ID_NUM] = {0};

    CSS_MEM_SET_S(astMccIDCopy, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM, 0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    /* �Ƚ�ԭʼMCC�б���һ�ݿ��� */
    CSS_MEM_CPY_S(astMccIDCopy, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                                astMccID, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);
    ulNumCopy = *pulMccNum;
    /* ��ԭʼ��MCC�б���������������Ҫ��ʼ��ֵ */
    CSS_MEM_SET_S(astMccID, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                                0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);
    *pulMccNum = 0;

    /* �Կ����е�ÿ��MCC�жϣ������Ƿ��MCC���ڸ��¹����� */
    for (ulLoop1 = 0; ulLoop1 < ulNumCopy; ++ulLoop1)
    {
        if (CSS_TRUE == CSS_IsMccUpdatingInUpdateStateTable(astMccIDCopy[ulLoop1].aucMccId))
        {
            /* �����ڸ��£��򽫴��޳���FLAG��ΪTRUE */
            ucExistFlag[ulLoop1] = CSS_TRUE;
        }

    }

    /* ��������MCC��FALG��ΪTRUE���޳��������뵽ԭʼMCC�б��� */
    for (ulLoop1 = 0; ulLoop1 < ulNumCopy; ++ulLoop1)
    {
        if (CSS_FALSE == ucExistFlag[ulLoop1])
        {
            astMccID[*pulMccNum].aucMccId[0] = astMccIDCopy[ulLoop1].aucMccId[0];
            astMccID[*pulMccNum].aucMccId[1] = astMccIDCopy[ulLoop1].aucMccId[1];
            (*pulMccNum) += 1;
        }
    }

}





/*****************************************************************************
 Function Name   : CSS_DeleteLocalMccFromMccArray
 Description     : ���ݴ��������ɾ�����ص���ЩMCC
 Input           :
 Output          :
 Return          :

 History         :
    1.chengmin 00285307 2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_DeleteLocalMccFromMccArray
(
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM],
    VOS_UINT32                          ulMccNum
)
{
    CSS_PUB_PREF_MCC_STRU              *pstMccNode;
    CSS_PUB_PREF_MCC_STRU              *pstMccNodePre;
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulMccNum; ++ulLoop)
    {
        /* ѭ���ҵ��ڴ��и�MCC�Ľڵ� */
        pstMccNode = CSS_GetPrefMccHeadNode();
        pstMccNodePre = CSS_NULL_PTR;
        while (CSS_NULL_PTR != pstMccNode)
        {
            if (CSS_TRUE == CSS_isMccMatch(pstMccNode->aucMccId, astMccID[ulLoop].aucMccId))
            {
                CSS_DeleteAllMnc(pstMccNode);

                if (CSS_NULL_PTR == pstMccNodePre)
                {
                    CSS_GetPrefMccHeadNode() = pstMccNode->pstNext;
                }
                else
                {
                    pstMccNodePre->pstNext = pstMccNode->pstNext;
                }

                if (CSS_GetPrefMccTailNode() == pstMccNode)
                {
                    CSS_GetPrefMccTailNode() = pstMccNodePre;
                }
                CSS_FreeCloudPreferNode(pstMccNode);
                CSS_GetPrefMccNodeNum() --;
                pstMccNode = CSS_NULL_PTR;
                break;
            }
            pstMccNodePre = pstMccNode;
            pstMccNode = pstMccNode->pstNext;
        }
    }


}


/*****************************************************************************
 Function Name  : CSS_ReadFreqFromAtMsg
 Description    : �������ж�ȡƵ������
 Input          : pstBand : BAND�ڵ�
                  pAddr   : �����׵�ַ
                  pulSum  : ��ַƫ����
 Output         : pstBand : BAND�ڵ�
                  pulSum  : ��ַƫ����
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ReadFreqFromAtMsg(CSS_PUB_PREF_BAND_STRU *pstBand, VOS_UINT8 *pAddr, VOS_UINT32 *pulSum, VOS_UINT32 ulRemainLen)
{
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNode;
    VOS_UINT8                           ucSupportFlag;
    VOS_UINT32                          ulFreqBegin;
    VOS_UINT32                          ulFreqEnd;
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT32                          ulFreqTmp;

    if (ulRemainLen < CSS_SIZEOF_AT_FREQ_RANGE_STRU)
    {
        return CSS_FAIL;
    }

    /* ��ȡ��ʽ֧��flag */
    ucSupportFlag = pAddr[ulSumTmp];
    ulSumTmp += 1;

    /* ��ȡ����Ƶ�� */
    ulFreqEnd = (((VOS_UINT32)pAddr[ulSumTmp+3]) << 24)
                | (((VOS_UINT32)pAddr[ulSumTmp+2]) << 16)
                | (((VOS_UINT32)pAddr[ulSumTmp+1]) << 8)
                | ((VOS_UINT32)pAddr[ulSumTmp]);
    ulSumTmp += 4;

    /* ��ȡ��ʼƵ�� */
    ulFreqBegin = (((VOS_UINT32)pAddr[ulSumTmp+3]) << 24)
                  | (((VOS_UINT32)pAddr[ulSumTmp+2]) << 16)
                  | (((VOS_UINT32)pAddr[ulSumTmp+1]) << 8)
                  | ((VOS_UINT32)pAddr[ulSumTmp]);
    ulSumTmp += 4;

    /* ������end��begin���˵��������ߵ�һ�� */
    if (ulFreqEnd < ulFreqBegin)
    {
        ulFreqTmp = ulFreqEnd;
        ulFreqEnd = ulFreqBegin;
        ulFreqBegin = ulFreqTmp;
    }

    /* ��������Ƶ��ڵ�ָ�룬���Ҹ�Ƶ���Ƿ���� */
    pstFreqNode = pstBand->pstFreqHead;
    while (CSS_NULL_PTR != pstFreqNode)
    {
        /* ���Ƶ���Ѵ��ڣ�����ʽ֧��������� */
        if ((ulFreqBegin == pstFreqNode->ulFreqBegin)
             && (ulFreqEnd == pstFreqNode->ulFreqEnd))
        {
            pstFreqNode->ucRatSupport |= ucSupportFlag;
            *pulSum += ulSumTmp;
            return CSS_SUCC;
        }
        pstFreqNode = pstFreqNode->pstNext;
    }

    /* ����Ƶ��û�д�����������ڵ� */
    pstFreqNode = (CSS_PUB_PREF_FREQ_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_FREQ_STRU));
    if (CSS_NULL_PTR == pstFreqNode)
    {
        return CSS_CAUSE_NULL_PTR;
    }
    CSS_MEM_SET_S(pstFreqNode, sizeof(CSS_PUB_PREF_FREQ_STRU), 0, sizeof(CSS_PUB_PREF_FREQ_STRU));

    pstFreqNode->ulFreqBegin = ulFreqBegin;
    pstFreqNode->ulFreqEnd   = ulFreqEnd;
    pstFreqNode->ucRatSupport = ucSupportFlag;

    /*��ĩβ��ӽڵ�*/
    if (CSS_NULL_PTR == pstBand->pstFreqHead)
    {
        pstBand->pstFreqHead          = pstFreqNode;
        pstBand->pstFreqTail          = pstFreqNode;
    }
    else
    {
        pstBand->pstFreqTail->pstNext = pstFreqNode;
        pstBand->pstFreqTail          = pstFreqNode;
    }

    /* ������1 */
    pstBand->ucFreqNum ++;

    *pulSum += ulSumTmp;
    return CSS_SUCC;
}

/*****************************************************************************
 Function Name  : CSS_ReadBandRatSuppotFromAtMsg
 Description    : �������ж�ȡBAND ��ratSupport����
 Input          : pstMnc  : MNC�ڵ�
                  pAddr   : �����׵�ַ
                  pulSum  : ��ַƫ����
 Output         : pstMnc  : MNC�ڵ�
                  pulSum  : ��ַƫ����
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ReadBandRatSuppotFromAtMsg(VOS_UINT8 *pucBandRatFlag, VOS_UINT8 *pAddr, VOS_UINT32 *pulSum, VOS_UINT32 ulRemainLen)
{
    VOS_UINT8                           ucFreqRangeNum;
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT8                           ucFlagTmp = 0;

    /* ���ʣ�µĳ��Ȳ����Խ������򷵻�ʧ�� */
    if (ulRemainLen - ulSumTmp < 1)
    {
        return CSS_FAIL;
    }

    /* ��ȡԤ��Ƶ�θ��� */
    ucFreqRangeNum = pAddr[ulSumTmp];
    ulSumTmp += 1;

    /* ���ʣ�µĳ��Ȳ����Խ������򷵻�ʧ�� */
    if (ulRemainLen - ulSumTmp < (ucFreqRangeNum*CSS_SIZEOF_AT_FREQ_RANGE_STRU))
    {
        return CSS_FAIL;
    }

    /* ���������Ϊ0��˵����Ԥ��BAND */
    if (0 < ucFreqRangeNum)
    {
        ucFlagTmp = pAddr[ulSumTmp];
    }

    ulSumTmp += (ucFreqRangeNum*CSS_SIZEOF_AT_FREQ_RANGE_STRU);

    (*pulSum) += ulSumTmp;
    *pucBandRatFlag = ucFlagTmp;
    return CSS_SUCC;
}

/*****************************************************************************
 Function Name  : CSS_ReadNoPrefBandFlgFromAtMsg
 Description    : �������ж�ȡBAND ��ratSupport����
 Input          : pstMnc  : MNC�ڵ�
                  pAddr   : �����׵�ַ
                  pulSum  : ��ַƫ����
 Output         : pstMnc  : MNC�ڵ�
                  pulSum  : ��ַƫ����
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ReadNoPrefBandFlgFromAtMsg(CSS_PUB_PREF_MNC_STRU *pstMnc, VOS_UINT8 *pAddr, VOS_UINT32 *pulSum, VOS_UINT32 ulRemainLen)
{
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT8                           ucFreqRangeNum;
    VOS_UINT8                           ucSupportFlag;

    /* ���ʣ�µĳ��Ȳ����Խ������򷵻�ʧ�� */
    if (ulRemainLen - ulSumTmp < 1)
    {
        return CSS_FAIL;
    }

    /* ��ȡԤ��Ƶ�θ��� */
    ucFreqRangeNum = pAddr[ulSumTmp];
    ulSumTmp += 1;

    if (0 == ucFreqRangeNum)
    {
        return CSS_FAIL;
    }

    if (ulRemainLen - ulSumTmp < 1)
    {
        return CSS_FAIL;
    }

    ucSupportFlag = pAddr[ulSumTmp];
    ulSumTmp += (ucFreqRangeNum*CSS_SIZEOF_AT_FREQ_RANGE_STRU);

    pstMnc->ucNoPrefBandFlg |= ucSupportFlag;

    (*pulSum) += ulSumTmp;

    return CSS_SUCC;
}




/*****************************************************************************
 Function Name  : CSS_AddBandFromAtMsg
 Description    : �������ж�ȡBAND����
 Input          : pstMnc  : MNC�ڵ�
                  pAddr   : �����׵�ַ
                  pulSum  : ��ַƫ����
 Output         : pstMnc  : MNC�ڵ�
                  pulSum  : ��ַƫ����
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ReadBandFromAtMsg(CSS_PUB_PREF_MNC_STRU *pstMnc, VOS_UINT8 *pAddr, VOS_UINT32 *pulSum, VOS_UINT32 ulRemainLen)
{
    CSS_PUB_PREF_BAND_STRU             *pstBandNode;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucBandInd;
    VOS_UINT8                           ucFreqNum;
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT8                           ucBandRatFlag = 0;
    VOS_UINT32                          ulRslt;

    pstBandNode = pstMnc->pstBandHead;

    if (ulRemainLen - ulSumTmp < 2)
    {
        return CSS_FAIL;
    }

    /* ��ȡBANDֵ */
    ucBandInd = pAddr[ulSumTmp];
    ulSumTmp += 1;

    /* ���BANDINDΪ0�����ʾ�ƶ���ȷ��PLMN��GSM/WCDMA/LTEû������Ҫ����GSM/WCDMA/LTE���� */
    if (CSS_NO_NETWORK_BAND_IND == ucBandInd)
    {
        if (CSS_SUCC != CSS_ReadNoPrefBandFlgFromAtMsg(pstMnc, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp))
        {
            return CSS_FAIL;
        }
    }
    else
    {
        /* ��ȡԤ��Ƶ�� */
        if (CSS_SUCC != CSS_ReadBandRatSuppotFromAtMsg(&ucBandRatFlag, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp))
        {
            return CSS_FAIL;
        }
    }

    if (ulRemainLen - ulSumTmp < 1)
    {
        return CSS_FAIL;
    }

    /* ��ȡԤ��Ƶ����� */
    ucFreqNum = pAddr[ulSumTmp];
    ulSumTmp += 1;

    /* ��������BAND�ڵ㣬�����Ƿ��BAND�Ѿ����� */
    while (CSS_NULL_PTR != pstBandNode)
    {
        if (pstBandNode->ucBandInd == ucBandInd)
        {
            /* ��BAND��ʽ֧�ּ��� */
            pstBandNode->ucRatSupport |= ucBandRatFlag;

            /* ������FREQ���� */
            for (ulLoop = 0; ulLoop < ucFreqNum; ++ulLoop)
            {
                /* һ������ʧ�ܣ�ԭ��ֻ�п����ǳ��Ȳ��Ի����ڴ�����ʧ�ܡ�
                  ���Ȳ�������Ϊ�����������ǲ����ŵģ��ڴ�����ʧ������ϵͳ����������ڴ�������ࡣ
                  ����ʧ����ֱ���˳� */
                ulRslt = CSS_ReadFreqFromAtMsg(pstBandNode, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp);
                if (CSS_SUCC != ulRslt)
                {
                    return ulRslt;
                }
            }
            *pulSum += ulSumTmp;
            return CSS_SUCC;
        }
        pstBandNode = pstBandNode->pstNext;
    }

    /* ���ڴ���û���ҵ���ͬ��BAND����������BAND */
    pstBandNode = (CSS_PUB_PREF_BAND_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_BAND_STRU));
    if (CSS_NULL_PTR == pstBandNode)
    {
        return CSS_CAUSE_NULL_PTR;
    }
    CSS_MEM_SET_S(pstBandNode, sizeof(CSS_PUB_PREF_BAND_STRU), 0, sizeof(CSS_PUB_PREF_BAND_STRU));

    pstBandNode->ucBandInd = ucBandInd;
    pstBandNode->ucRatSupport |= ucBandRatFlag;

    /*��ĩβ��ӽڵ�*/
    if (CSS_NULL_PTR == pstMnc->pstBandHead)
    {
        pstMnc->pstBandHead          = pstBandNode;
        pstMnc->pstBandTail          = pstBandNode;
    }
    else
    {
        pstMnc->pstBandTail->pstNext = pstBandNode;
        pstMnc->pstBandTail          = pstBandNode;
    }

    /* ������1 */
    pstMnc->ucBandNum ++;

    /* ������FREQ���� */
    for (ulLoop = 0; ulLoop < ucFreqNum; ++ulLoop)
    {
        /* һ������ʧ�ܣ�ԭ��ֻ�п����ǳ��Ȳ��Ի����ڴ�����ʧ�ܡ�
           ���Ȳ�������Ϊ�����������ǲ����ŵģ��ڴ�����ʧ������ϵͳ����������ڴ�������ࡣ
           ����ʧ����ֱ���˳�*/
        ulRslt = CSS_ReadFreqFromAtMsg(pstBandNode, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp);
        if (CSS_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    *pulSum += ulSumTmp;
    return CSS_SUCC;
}


/*****************************************************************************
 Function Name  : CSS_ReadMncFromAtMsg
 Description    : �������ж�ȡMNC����
 Input          : pstMcc  : MCC�ڵ�
                  pAddr   : �����׵�ַ
                  pulSum  : ��ַƫ����
 Output         : pstMcc  : MCC�ڵ�
                  pulSum  : ��ַƫ����
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ReadMncFromAtMsg(CSS_PUB_PREF_MCC_STRU *pstMcc, VOS_UINT8 *pAddr, VOS_UINT32 *pulSum, VOS_UINT32 ulRemainLen)
{
    CSS_PUB_PREF_MNC_STRU              *pstMncNode;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucMnc[2] = {0};
    VOS_UINT8                           ucBandNum;
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT32                          ulRslt;

    pstMncNode = pstMcc->pstMncHead;

    if (ulRemainLen < 3)
    {
        return CSS_FAIL;
    }

    /* ��ȡMNCid */
    aucMnc[0] = pAddr[ulSumTmp];
    aucMnc[1] = pAddr[ulSumTmp+1];
    ulSumTmp += 2;

    /* ��ȡBAND���� */
    ucBandNum = pAddr[ulSumTmp];
    ulSumTmp += 1;

    /* ���BAND����Ϊ0������Ϊ��MNC�����ݣ����� */
    if (0 == ucBandNum)
    {
        return CSS_FAIL;
    }

    /* ��������MNC�ڵ㣬�����Ƿ��MNC�Ѿ����� */
    while (CSS_NULL_PTR != pstMncNode)
    {
        if (CSS_TRUE == CSS_isMncMatch(pstMncNode->aucMncId, aucMnc))
        {
            for (ulLoop = 0; ulLoop < ucBandNum; ++ulLoop)
            {
                /* �Ѹ���BAND���� */
                ulRslt = CSS_ReadBandFromAtMsg(pstMncNode, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp);
                if (CSS_SUCC != ulRslt)
                {
                    return ulRslt;
                }
            }
            *pulSum += ulSumTmp;
            return CSS_SUCC;
        }
        pstMncNode = pstMncNode->pstNext;
    }

    /* ��û���ҵ�MNC�ڵ㣬������ */
    pstMncNode = (CSS_PUB_PREF_MNC_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_MNC_STRU));
    if (CSS_NULL_PTR == pstMncNode)
    {
        return CSS_CAUSE_NULL_PTR;
    }
    CSS_MEM_SET_S(pstMncNode, sizeof(CSS_PUB_PREF_MNC_STRU), 0, sizeof(CSS_PUB_PREF_MNC_STRU));
    pstMncNode->aucMncId[0] = aucMnc[0];
    pstMncNode->aucMncId[1] = aucMnc[1];

    /*��ĩβ��ӽڵ�*/
    if (CSS_NULL_PTR == pstMcc->pstMncHead)
    {
        pstMcc->pstMncHead          = pstMncNode;
        pstMcc->pstMncTail          = pstMncNode;
    }
    else
    {
        pstMcc->pstMncTail->pstNext = pstMncNode;
        pstMcc->pstMncTail          = pstMncNode;
    }

    /* ������1 */
    pstMcc->ucMncNum ++;

    /* �Ѹ���BAND���� */
    for (ulLoop = 0; ulLoop < ucBandNum; ++ulLoop)
    {
        ulRslt = CSS_ReadBandFromAtMsg(pstMncNode, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp);
        if (CSS_SUCC != ulRslt)
        {
            return ulRslt;
        }
    }

    *pulSum += ulSumTmp;
    return CSS_SUCC;
}


/*****************************************************************************
 Function Name  : CSS_ReadMccFromAtMsg
 Description    : �������ж�ȡMCC����
 Input          : pAddr         : �����׵�ַ
                  ulRemainLen   : ʣ���ֽ���
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
/*lint -e429*/
VOS_UINT32 CSS_ReadMccFromAtMsg(VOS_UINT8 *pAddr, VOS_UINT32 ulRemainLen)
{
    CSS_PUB_PREF_MCC_STRU              *pstMccNode;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucMcc[2] = {0};
    VOS_UINT8                           ucMncNum;
    VOS_UINT32                          ulSumTmp = 0;
    VOS_UINT32                          ulRslt;

    if (CSS_NULL_PTR == pAddr)
    {
        return CSS_CAUSE_NULL_PTR;
    }

    /* �����ڵ㣬�������������е���Ϣ */
    pstMccNode = (CSS_PUB_PREF_MCC_STRU*)CSS_AllocCloudPreferNodeAndClearFullMemory(sizeof(CSS_PUB_PREF_MCC_STRU));

    /* �����ڴ�ʧ�ܣ�ֱ�ӷ��� */
    if (CSS_NULL_PTR == pstMccNode)
    {
        return CSS_CAUSE_NULL_PTR;
    }

    /* �ڴ��ʼ�� */
    CSS_MEM_SET_S(pstMccNode, sizeof(CSS_PUB_PREF_MCC_STRU), 0, sizeof(CSS_PUB_PREF_MCC_STRU));


    /* ��ȡMCCid */
    aucMcc[0] = pAddr[ulSumTmp];
    aucMcc[1] = pAddr[ulSumTmp+1];
    ulSumTmp += 2;

    /* ���ʣ�µĳ��Ȳ��������򷵻�ʧ�� */
    if (ulRemainLen - ulSumTmp < 1)
    {
        /* �ͷ�MCC�ڵ��ڴ� */
        CSS_FreeCloudPreferNode(pstMccNode);

        return CSS_FAIL;
    }

    /* ��ȡMNC���� */
    ucMncNum  = pAddr[ulSumTmp];
    ulSumTmp += 1;

    pstMccNode->aucMccId[0] = aucMcc[0];
    pstMccNode->aucMccId[1] = aucMcc[1];

    /* ѭ��ȡ������MNC������һ��ȡ��ʧ�ܣ��򷵻�ʧ�� */
    for (ulLoop = 0; ulLoop < ucMncNum; ++ulLoop)
    {
        ulRslt = CSS_ReadMncFromAtMsg(pstMccNode, &(pAddr[ulSumTmp]), &ulSumTmp, ulRemainLen-ulSumTmp);
        if (CSS_SUCC != ulRslt)
        {
            /* ��ȡMNCʧ�ܣ���Ϊ�������������ţ�ɾ�����ж������� */
            CSS_DeleteAllMnc(pstMccNode);

            /* �ͷ�MCC�ڵ��ڴ� */
            CSS_FreeCloudPreferNode(pstMccNode);
            return ulRslt;
        }
    }

    /* ��MCC�ڵ��ȡ������ */
    CSS_AddMccNodeToLocal(pstMccNode);

    return CSS_SUCC;
}
/*lint +e429*/

/*****************************************************************************
 Function Name  : CSS_AddFreqNodeToLocal
 Description    : ��һ��FREQ�ڵ���뵽����ĳ��BAND�ڵ��£�����ԭ��:
                  �����ֱ���BAND�ڵ����Ѿ�������ͬ��Ƶ����ֵ���������ʽ֧��flag���ͷ�
                  �����ָ����ڴ�;
                  �����ֱ���BAND�ڵ���û����ͬ��Ƶ����ֵ����ֱ�ӽ�����BAND�е�FREQβ�ڵ�ָ��
                  ָ�����FREQָ�룬���������ڴ档
 Input          : pstFreqIn     : �����FREQ�ڵ�
 Output         : pstBandNode   : ��Ҫ����FREQ�ڵ�ı���BAND�ڵ�
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddFreqNodeToLocal(CSS_PUB_PREF_BAND_STRU *pstBandNode, CSS_PUB_PREF_FREQ_STRU *pstFreqIn)
{
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNode;
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNodeTmp;

    /* ѭ���������ҵ�FREQ�Ľڵ�ָ�� */
    pstFreqNode = pstBandNode->pstFreqHead;
    while (CSS_NULL_PTR != pstFreqNode)
    {
        /* ���ҵ���ͬ��Ƶ�㣬�������ʽ֧��flag�����ͷŴ����ָ���ڴ� */
        if (pstFreqNode->ulFreqBegin == pstFreqIn->ulFreqBegin
            && pstFreqNode->ulFreqEnd == pstFreqIn->ulFreqEnd)
        {
            pstFreqNode->ucRatSupport |= pstFreqIn->ucRatSupport;
            CSS_FreeCloudPreferNode(pstFreqIn);
            return;
        }
        pstFreqNode = pstFreqNode->pstNext;
    }

    /* ����ڵ�����Ѵ����ֵ����ȥ��ͷ���ģ�������1 */
    if (pstBandNode->ucFreqNum >= CSS_MAX_MEMORY_PERF_FREQ_NUM)
    {
        if (CSS_NULL_PTR != pstBandNode->pstFreqHead)
        {
            pstFreqNodeTmp = pstBandNode->pstFreqHead;

            /* ���µ�ͷβ�ڵ㸳ֵ */
            pstBandNode->pstFreqHead = pstFreqNodeTmp->pstNext;
            if (pstBandNode->pstFreqTail == pstFreqNodeTmp)
            {
                pstBandNode->pstFreqTail = CSS_NULL_PTR;
            }

            /* ɾ��ͷ��� */
            CSS_FreeCloudPreferNode(pstFreqNodeTmp);

            /* ������1 */
            pstBandNode->ucFreqNum --;
        }
    }

    /* ��û���ҵ���ͬ��Ƶ�㣬�򽫸ýڵ���ӵ�ĩβ */
    if (CSS_NULL_PTR == pstBandNode->pstFreqHead)
    {
        pstBandNode->pstFreqHead          = pstFreqIn;
        pstBandNode->pstFreqTail          = pstFreqIn;
    }
    else
    {
        if (CSS_NULL_PTR != pstBandNode->pstFreqTail)
        {
            pstBandNode->pstFreqTail->pstNext = pstFreqIn;
        }
        pstBandNode->pstFreqTail          = pstFreqIn;
    }
    pstFreqIn->pstNext = CSS_NULL_PTR;
    pstBandNode->ucFreqNum ++;
}


/*****************************************************************************
 Function Name  : CSS_AddBandNodeToLocal
 Description    : ��һ��BAND�ڵ���뵽����ĳ��MNC�ڵ��£�����ԭ��:
                  �����ֱ���MNC�ڵ����Ѿ�������ͬ��BAND��ֵ������������BANDָ�룬
                  ���ν�����BANDָ���е�FREQ���뵽����BAND�ڵ���;
                  �����ֱ���MNC�ڵ���û����ͬ��BAND��ֵ����ֱ�ӱ����е�BANDβ�ڵ�ָ��
                  ָ�����BANDָ�룬���������ڴ档
 Input          : pstBandIn     : �����BAND�ڵ�
 Output         : pstMncNode    : ��Ҫ����BAND�ڵ�ı���MNC�ڵ�
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddBandNodeToLocal(CSS_PUB_PREF_MNC_STRU *pstMncNode, CSS_PUB_PREF_BAND_STRU *pstBandIn)
{
    CSS_PUB_PREF_BAND_STRU             *pstBandNode;
    CSS_PUB_PREF_BAND_STRU             *pstBandNodeTmp;
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNode;
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNodeTmp;

    /* ѭ���������ҵ���BAND�Ľڵ�ָ�� */
    pstBandNode = pstMncNode->pstBandHead;
    while (CSS_NULL_PTR != pstBandNode)
    {
        /* �ҵ���ͬ��BAND */
        if (pstBandNode->ucBandInd == pstBandIn->ucBandInd)
        {
            /* ��BAND ��ʽ֧�ּ��� */
            pstBandNode->ucRatSupport |= pstBandIn->ucRatSupport;

            /* ���ν�����BANDָ���е�FREQ���뵽����BAND�ڵ��У����ͷŴ����BANDָ���ڴ� */
            pstFreqNode = pstBandIn->pstFreqHead;
            while (CSS_NULL_PTR != pstFreqNode)
            {
                pstFreqNodeTmp = pstFreqNode->pstNext;
                CSS_AddFreqNodeToLocal(pstBandNode, pstFreqNode);
                pstFreqNode = pstFreqNodeTmp;
            }
            CSS_FreeCloudPreferNode(pstBandIn);
            return;
        }
        pstBandNode = pstBandNode->pstNext;
    }

    /* ����ڵ�����Ѵ����ֵ����ȥ��ͷ���ģ�������1 */
    if (pstMncNode->ucBandNum >= CSS_MAX_MEMORY_PERF_BAND_NUM)
    {
        if (CSS_NULL_PTR != pstMncNode->pstBandHead)
        {
            pstBandNodeTmp = pstMncNode->pstBandHead;

            /* ���µ�ͷβ�ڵ㸳ֵ */
            pstMncNode->pstBandHead = pstBandNodeTmp->pstNext;
            if (pstMncNode->pstBandTail == pstBandNodeTmp)
            {
                pstMncNode->pstBandTail = CSS_NULL_PTR;
            }

            /* ɾ��ͷ��� */
            CSS_DeleteAllFreq(pstBandNodeTmp);
            CSS_FreeCloudPreferNode(pstBandNodeTmp);

            /* ������1 */
            pstMncNode->ucBandNum --;
        }
    }

    /* ��û���ҵ���ͬ��BAND���򽫸ýڵ���ӵ�ĩβ */
    if (CSS_NULL_PTR == pstMncNode->pstBandHead)
    {
        pstMncNode->pstBandHead          = pstBandIn;
        pstMncNode->pstBandTail          = pstBandIn;
    }
    else
    {
        if (CSS_NULL_PTR != pstMncNode->pstBandTail)
        {
            pstMncNode->pstBandTail->pstNext = pstBandIn;
        }
        pstMncNode->pstBandTail          = pstBandIn;
    }
    pstBandIn->pstNext = CSS_NULL_PTR;
    pstMncNode->ucBandNum ++;
}


/*****************************************************************************
 Function Name  : CSS_AddMncNodeToLocal
 Description    : ��һ��MNC�ڵ���뵽����ĳ��MCC�ڵ��£�����ԭ��:
                  �����ֱ���MCC�ڵ����Ѿ�������ͬ��MNC��ֵ������������MNCָ�룬
                  ���ν�����MNCָ���е�BAND���뵽����MNC�ڵ���;
                  �����ֱ���MCC�ڵ���û����ͬ��MNC��ֵ����ֱ�ӱ����е�MNCβ�ڵ�ָ��
                  ָ�����MNCָ�룬���������ڴ档
 Input          : pstMncIn      : �����MNC�ڵ�
 Output         : pstMccNode    : ��Ҫ����MNC�ڵ�ı���MCC�ڵ�
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddMncNodeToLocal(CSS_PUB_PREF_MCC_STRU *pstMccNode, CSS_PUB_PREF_MNC_STRU *pstMncIn)
{
    CSS_PUB_PREF_MNC_STRU              *pstMncNode;
    CSS_PUB_PREF_MNC_STRU              *pstMncNodeTmp;
    CSS_PUB_PREF_BAND_STRU             *pstBandNode;
    CSS_PUB_PREF_BAND_STRU             *pstBandNodeTmp;

    /* ѭ���������ҵ���MNC�Ľڵ�ָ�� */
    pstMncNode = pstMccNode->pstMncHead;
    while (CSS_NULL_PTR != pstMncNode)
    {
        /* �ҵ���ͬ��MNC */
        if (CSS_TRUE == CSS_isMncMatch(pstMncNode->aucMncId, pstMncIn->aucMncId))
        {
            /* ���ν�����MNCָ���е�BAND���뵽����MNC�ڵ��У����ͷŴ����MNCָ���ڴ� */
            pstBandNode = pstMncIn->pstBandHead;
            while (CSS_NULL_PTR != pstBandNode)
            {
                pstBandNodeTmp = pstBandNode->pstNext;
                CSS_AddBandNodeToLocal(pstMncNode, pstBandNode);
                pstBandNode = pstBandNodeTmp;
            }
            CSS_FreeCloudPreferNode(pstMncIn);
            return;
        }
        pstMncNode = pstMncNode->pstNext;
    }

    /* ����ڵ�����Ѵ����ֵ����ȥ��ͷ���ģ�������1 */
    if (pstMccNode->ucMncNum >= CSS_MAX_MEMORY_PERF_MNC_NUM)
    {
        if (CSS_NULL_PTR != pstMccNode->pstMncHead)
        {
            pstMncNodeTmp = pstMccNode->pstMncHead;

            /* ���µ�ͷβ�ڵ㸳ֵ */
            pstMccNode->pstMncHead = pstMncNodeTmp->pstNext;
            if (pstMccNode->pstMncTail == pstMncNodeTmp)
            {
                pstMccNode->pstMncTail = CSS_NULL_PTR;
            }

            /* ɾ��ͷ��� */
            CSS_DeleteAllBand(pstMncNodeTmp);
            CSS_FreeCloudPreferNode(pstMncNodeTmp);

            /* ������1 */
            pstMccNode->ucMncNum --;
        }
    }

    /* ��û���ҵ���ͬ��MNC���򽫸ýڵ���ӵ�ĩβ */
    if (CSS_NULL_PTR == pstMccNode->pstMncHead)
    {
        pstMccNode->pstMncHead          = pstMncIn;
        pstMccNode->pstMncTail          = pstMncIn;
    }
    else
    {
        if (CSS_NULL_PTR != pstMccNode->pstMncTail)
        {
            pstMccNode->pstMncTail->pstNext = pstMncIn;
        }
        pstMccNode->pstMncTail          = pstMncIn;
    }
    pstMncIn->pstNext = CSS_NULL_PTR;
    pstMccNode->ucMncNum++;
}


/*****************************************************************************
 Function Name  : CSS_AddMccNodeToLocal
 Description    : ��һ��MCC�ڵ���뵽���أ�����ԭ��:
                  �����ֱ����Ѿ�������ͬ��MCC������������MCCָ�룬
                  ���ν�����MCCָ���е�MNC���뵽����MCC�ڵ���;
                  �����ֱ���û����ͬ��MCC����ֱ�ӱ����е�MCCβ�ڵ�ָ��
                  ָ�����MCCָ�룬���������ڴ档
 Input          : pstMccIn      : �����MCC�ڵ�
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AddMccNodeToLocal(CSS_PUB_PREF_MCC_STRU *pstMccIn)
{
    CSS_PUB_PREF_MCC_STRU              *pstMccNode;
    CSS_PUB_PREF_MNC_STRU              *pstMncNode;
    CSS_PUB_PREF_MCC_STRU              *pstMccNodeTmp;
    CSS_PUB_PREF_MNC_STRU              *pstMncNodeTmp;

    /* ѭ���������ҵ���MCC�Ľڵ�ָ�� */
    pstMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pstMccNode)
    {
        /* �ҵ���ͬ��MCC */
        if (CSS_TRUE == CSS_isMccMatch(pstMccNode->aucMccId, pstMccIn->aucMccId))
        {
            /* ���ν�����MCCָ���е�MNC���뵽����MCC�ڵ��У����ͷŴ����MCCָ���ڴ� */
            pstMncNode = pstMccIn->pstMncHead;
            while (CSS_NULL_PTR != pstMncNode)
            {
                pstMncNodeTmp  = pstMncNode->pstNext;
                CSS_AddMncNodeToLocal(pstMccNode, pstMncNode);
                pstMncNode = pstMncNodeTmp;
            }
            CSS_FreeCloudPreferNode(pstMccIn);
            return;
        }
        pstMccNode = pstMccNode->pstNext;
    }

    /* ����ڵ�����Ѵ����ֵ����ȥ��ͷ���ģ�������1 */
    if (CSS_GetPrefMccNodeNum() >= CSS_MAX_MEMORY_PERF_MCC_NUM)
    {
        if (CSS_NULL_PTR != CSS_GetPrefMccHeadNode())
        {
            pstMccNodeTmp = CSS_GetPrefMccHeadNode();

            /* ���µ�ͷβ�ڵ㸳ֵ */
            CSS_GetPrefMccHeadNode() = pstMccNodeTmp->pstNext;
            if (CSS_GetPrefMccTailNode() == pstMccNodeTmp)
            {
                CSS_GetPrefMccTailNode() = CSS_NULL_PTR;
            }

            /* ɾ��ͷ��� */
            CSS_DeleteAllMnc(pstMccNodeTmp);
            CSS_FreeCloudPreferNode(pstMccNodeTmp);

            /* ������1 */
            CSS_GetPrefMccNodeNum() --;
        }
    }

    /* ���ýڵ���ӵ�ĩβ��������1 */
    if (CSS_NULL_PTR == CSS_GetPrefMccHeadNode())
    {
        CSS_GetPrefMccHeadNode()          = pstMccIn;
        CSS_GetPrefMccTailNode()          = pstMccIn;
    }
    else
    {
        if (CSS_NULL_PTR != CSS_GetPrefMccTailNode())
        {
            CSS_GetPrefMccTailNode()->pstNext = pstMccIn;
        }
        CSS_GetPrefMccTailNode()          = pstMccIn;
    }
    CSS_GetPrefMccNodeNum() ++;
}


/*****************************************************************************
 Function Name  : CSS_UpdateRatFreqToNv
 Description    : ������ĳ��ʽ֧�ֵ�FREQ�ڵ�д��NV��
 Input          : aucMncId      : �����MNC ID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateRatFreqToNv
(
    VOS_UINT8 aucMncId[2],
    VOS_UINT8 ucBand,
    CSS_RAT_TYPE_ENUM_UINT8 ucRat,
    CSS_PUB_PREF_FREQ_STRU *pstFreqNode,
    CSS_NV_PREF_MCC_STRU *pstNvMcc
)
{
    CSS_NV_PREF_MNC_STRU               *pNvMnc = CSS_NULL_PTR;
    CSS_NV_PREF_ARFCN_STRU             *pNvFreq = CSS_NULL_PTR;
    VOS_UINT8                           aucNvMnc[2] = {0};
    VOS_UINT8                           ucNvRat;

    /* ������и���С�ڵ��������� */
    if (pstNvMcc->usMncNum <= CSS_NV_MAX_PREF_MNC_NUM)
    {
        /* ȡ�ѱ������ݵ����һ��MNC�ṹ */
        pNvMnc = &(pstNvMcc->astMnc[pstNvMcc->usMncNum-1]);

        /* ��ȡMNC id */
        CSS_ConvertMncDigitToSimMnc(pNvMnc->bitMncDigit1, pNvMnc->bitMncDigit2, pNvMnc->bitMncDigit3, aucNvMnc);

        /* ȡ��NV�ڵ����ʽ */
        ucNvRat = pNvMnc->bitRat;

        /* ���MNC�ṹ�еĸ���û������MNC��BAND����ʽ��Ҫ�����MNC��ͬ�������FREQ */
        if ((pNvMnc->ucArfcnNum < CSS_NV_MAX_PREF_ARFCN_NUM)
            &&(CSS_TRUE == CSS_isMncMatch(aucNvMnc, aucMncId))
            &&(ucBand == pNvMnc->ucBandInd)
            &&(ucNvRat == ucRat))
        {
            pNvFreq = &(pNvMnc->astArfcn[pNvMnc->ucArfcnNum]);
            pNvFreq->ulArfcnBegin = pstFreqNode->ulFreqBegin;
            pNvFreq->ulArfcnEnd   = pstFreqNode->ulFreqEnd;
            pNvMnc->ucArfcnNum ++;
        }
        /* ��������һ��MNC�ṹ���������ڸ�MNC�ĵ�һ��FREQ�ṹ�� */
        else
        {
            if (pstNvMcc->usMncNum < CSS_NV_MAX_PREF_MNC_NUM)
            {
                /* ������ز��� */
                pNvMnc = &(pstNvMcc->astMnc[pstNvMcc->usMncNum]);
                pNvMnc->bitMncDigit1 = (aucMncId[1] & CSS_OCTET_LOW_4_BITS);
                pNvMnc->bitMncDigit2 = ((aucMncId[1] & CSS_OCTET_HIGH_4_BITS) >> CSS_OCTET_MOVE_4_BITS);
                pNvMnc->bitMncDigit3 = ((aucMncId[0] & CSS_OCTET_HIGH_4_BITS) >> CSS_OCTET_MOVE_4_BITS);
                pNvMnc->bitRat = ucRat;
                pNvMnc->ucBandInd = ucBand;
                pstNvMcc->usMncNum ++;

                pNvFreq = &(pNvMnc->astArfcn[0]);
                pNvFreq->ulArfcnBegin = pstFreqNode->ulFreqBegin;
                pNvFreq->ulArfcnEnd   = pstFreqNode->ulFreqEnd;
                pNvMnc->ucArfcnNum = 1;
            }
        }
    }
}


/*****************************************************************************
 Function Name  : CSS_UpdateRatFreqToNv
 Description    : ������ĳ��ʽ֧�ֵ�BAND�ڵ�д��NV������BAND��û��Ԥ��Ƶ������
 Input          : aucMncId      : �����MNC ID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateRatBandToNv
(
    VOS_UINT8 aucMncId[2],
    CSS_RAT_TYPE_ENUM_UINT8 ucRat,
    CSS_PUB_PREF_BAND_STRU *pstBandNode,
    CSS_NV_PREF_MCC_STRU *pstNvMcc
)
{
    CSS_NV_PREF_MNC_STRU               *pNvMnc = CSS_NULL_PTR;

    if (pstNvMcc->usMncNum < CSS_NV_MAX_PREF_MNC_NUM)
    {
        pNvMnc = &(pstNvMcc->astMnc[pstNvMcc->usMncNum]);
        pNvMnc->bitMncDigit1 = (aucMncId[1] & CSS_OCTET_LOW_4_BITS);
        pNvMnc->bitMncDigit2 = ((aucMncId[1] & CSS_OCTET_HIGH_4_BITS) >> CSS_OCTET_MOVE_4_BITS);
        pNvMnc->bitMncDigit3 = ((aucMncId[0] & CSS_OCTET_HIGH_4_BITS) >> CSS_OCTET_MOVE_4_BITS);
        pNvMnc->bitRat = ucRat;
        pNvMnc->ucBandInd = pstBandNode->ucBandInd;
        pstNvMcc->usMncNum ++;
    }
}


/*****************************************************************************
 Function Name  : CSS_UpdateFreqToNv
 Description    : ������ĳ��BAND�µ�����FREQ�ڵ�д��NV��
 Input          : aucMncId      : �����MNC ID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateFreqToNv
(
    VOS_UINT8 aucMncId[2],
    CSS_PUB_PREF_BAND_STRU *pstBandNode,
    CSS_NV_PREF_MCC_STRU *pstNvMcc
)
{
    CSS_PUB_PREF_FREQ_STRU             *pstFreqNode;

    /* ���FREQ��Ϊ�㣬Ҳ��Ҫ��BAND���� */
    if (0 == pstBandNode->ucFreqNum)
    {
        /* ���֧��GSM�����GSM���� */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_GSM, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_GSM, pstBandNode, pstNvMcc);
        }
        /* ���֧��WCDMA�����WCDMA���� */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_UMTS_FDD, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_UMTS_FDD, pstBandNode, pstNvMcc);
        }
        /* ���֧��LTE�����LTE���� */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_LTE, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_LTE, pstBandNode, pstNvMcc);
        }

        return;
    }

    /* ���BAND�ж����ratSupport */
    if (0 != pstBandNode->ucRatSupport)
    {
        /* ���֧��GSM�����GSM���� */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_GSM, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_GSM, pstBandNode, pstNvMcc);
        }
        /* ���֧��WCDMA�����WCDMA���� */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_UMTS_FDD, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_UMTS_FDD, pstBandNode, pstNvMcc);
        }
        /* ���֧��LTE�����LTE���� */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_LTE, pstBandNode->ucRatSupport))
        {
            CSS_UpdateRatBandToNv(aucMncId, CSS_RAT_LTE, pstBandNode, pstNvMcc);
        }
    }

    /* ѭ���������ҵ�FREQ�Ľڵ�ָ�� */
    pstFreqNode = pstBandNode->pstFreqHead;
    while (CSS_NULL_PTR != pstFreqNode)
    {
        /* ���֧��GSM�����GSM���� */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_GSM, pstFreqNode->ucRatSupport))
        {
            CSS_UpdateRatFreqToNv(aucMncId, pstBandNode->ucBandInd, CSS_RAT_GSM, pstFreqNode, pstNvMcc);
        }
        /* ���֧��WCDMA�����WCDMA���� */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_UMTS_FDD, pstFreqNode->ucRatSupport))
        {
            CSS_UpdateRatFreqToNv(aucMncId, pstBandNode->ucBandInd, CSS_RAT_UMTS_FDD, pstFreqNode, pstNvMcc);
        }
        /* ���֧��LTE�����LTE���� */
        if (CSS_TRUE == CSS_IsRatSupportInFlag(CSS_RAT_LTE, pstFreqNode->ucRatSupport))
        {
            CSS_UpdateRatFreqToNv(aucMncId, pstBandNode->ucBandInd, CSS_RAT_LTE, pstFreqNode, pstNvMcc);
        }
        pstFreqNode = pstFreqNode->pstNext;
    }
}



/*****************************************************************************
 Function Name  : CSS_UpdateBandToNv
 Description    : ������ĳ��MNC�µ�����BANDд��NV��
 Input          : pstMccIn      : �����MCC�ڵ�
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateBandToNv(CSS_PUB_PREF_MNC_STRU *pstMncNode, CSS_NV_PREF_MCC_STRU *pstNvMcc)
{
    CSS_PUB_PREF_BAND_STRU             *pstBandNode;

    /* ѭ���������ҵ���BAND�Ľڵ�ָ�� */
    pstBandNode = pstMncNode->pstBandHead;
    while (CSS_NULL_PTR != pstBandNode)
    {
        CSS_UpdateFreqToNv(pstMncNode->aucMncId, pstBandNode, pstNvMcc);
        pstBandNode = pstBandNode->pstNext;
    }
}

/*****************************************************************************
 Function Name  : CSS_UpdateMncToNv
 Description    : ������ĳ��MCC�µ�����MNCд��NV��
 Input          : pstMccIn      : �����MCC�ڵ�
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_UpdateMncToNv(CSS_PUB_PREF_MCC_STRU *pstMccNode, CSS_NV_PREF_MCC_STRU *pstNvMcc)
{
    CSS_PUB_PREF_MNC_STRU              *pstMncNode;

    /* ѭ���������ҵ���MNC�Ľڵ�ָ�� */
    pstMncNode = pstMccNode->pstMncHead;
    while (CSS_NULL_PTR != pstMncNode)
    {
        CSS_UpdateBandToNv(pstMncNode, pstNvMcc);
        pstMncNode = pstMncNode->pstNext;
    }

    pstNvMcc->bitMccDigit1 = (pstMccNode->aucMccId[0] & CSS_OCTET_LOW_4_BITS);
    pstNvMcc->bitMccDigit2 = ((pstMccNode->aucMccId[0] & CSS_OCTET_HIGH_4_BITS) >> CSS_OCTET_MOVE_4_BITS);
    pstNvMcc->bitMccDigit3 = (pstMccNode->aucMccId[1] & CSS_OCTET_LOW_4_BITS);
}

/*****************************************************************************
 Function Name  : CSS_UpdateMccToNv
 Description    : ������ĳ��MCCд��NV��
 Input          : pstMccIn      : �����MCC�ڵ�
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_UpdateMccToNv(VOS_UINT8 aucMccId[2], CSS_NV_PREF_MCC_STRU *pstNvMcc)
{
    CSS_PUB_PREF_MCC_STRU              *pstMccNode;

    /* ѭ���������ҵ���MCC�Ľڵ�ָ�� */
    pstMccNode = CSS_GetPrefMccHeadNode();
    while (CSS_NULL_PTR != pstMccNode)
    {
        /* �ҵ���ͬ��MCC */
        if (CSS_TRUE == CSS_isMccMatch(pstMccNode->aucMccId, aucMccId))
        {
            CSS_UpdateMncToNv(pstMccNode, pstNvMcc);
            return CSS_SUCC;
        }
        pstMccNode = pstMccNode->pstNext;
    }
    return CSS_FAIL;
}

/*****************************************************************************
 Function Name  : CSS_WriteNvMccPrefFreq
 Description    : �������Ѵ洢��MCC д��NV��
 Input          : pstMccIn      : �����MCC�ڵ�
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_WriteNvMccPrefFreq(VOS_VOID)
{
    VOS_UINT32                          ulDataLen = 0;
    CSS_NV_PREF_MCC_STRU               *pstNvPerfFreq;
    CSS_CLOUD_PUB_CONTROL_STRU         *pstCloudControl;
    VOS_UINT32                          ulResult;

    pstCloudControl = CSS_GetCloudContrlAddr();
    ulDataLen = sizeof(CSS_NV_PREF_MCC_STRU);

    CSS_INFO_LOG("CSS_WriteNvMccPrefFreq: enter");
    TLPS_PRINT2LAYER_INFO(CSS_WriteNvMccPrefFreq_ENUM, LNAS_ENTRY);

    /* �����ͨ�����Բ�ʹ�ã�ֱ�ӷ��� */
    if (CSS_FALSE == CSS_IsCloudStrategyEnable())
    {
        CSS_INFO_LOG("CSS_WriteNvMccPrefFreq: cloud strategy is not enabled");
        TLPS_PRINT2LAYER_INFO(CSS_WriteNvMccPrefFreq_ENUM, LNAS_FUNCTION_LABEL1);
        return;
    }

    /* ��������ƶ˻�ȡ��Ҳֱ�ӷ��� */
    if (CSS_FALSE == CSS_IsPrefFreqEnable())
    {
        CSS_INFO_LOG("CSS_WriteNvMccPrefFreq: cloud pref freq is not enabled");
        TLPS_PRINT2LAYER_INFO(CSS_WriteNvMccPrefFreq_ENUM, LNAS_FUNCTION_LABEL2);
        return;
    }

    pstNvPerfFreq = (CSS_NV_PREF_MCC_STRU*)CSS_MEM_ALLOC(sizeof(CSS_NV_PREF_MCC_STRU));
    if (CSS_NULL_PTR == pstNvPerfFreq)
    {
        return;
    }

    CSS_PrintLocalPrefFreqInfo();

    /* Ϊ0���ʾ���ڳ�ʼ��״̬��û��MCC����Ϊ0�Ÿ���MCC */
    /* MCC1 */
    if (0 != pstCloudControl->astNvMcc[0].aucMccId[0])
    {
        TLPS_PRINT2LAYER_INFO2( CSS_WriteNvMccPrefFreq_ENUM,
                                LNAS_FUNCTION_LABEL3,
                                pstCloudControl->astNvMcc[0].aucMccId[0],
                                pstCloudControl->astNvMcc[0].aucMccId[1]);

        CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));
        if (CSS_SUCC == CSS_UpdateMccToNv(pstCloudControl->astNvMcc[0].aucMccId, pstNvPerfFreq))
        {
            ulResult = CSS_NV_Write(EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC1,
                                    (VOS_VOID *)(pstNvPerfFreq),
                                    ulDataLen);
            if (VOS_OK != ulResult)
            {
                TLPS_PRINT2LAYER_INFO1(CSS_WriteNvMccPrefFreq_ENUM,LNAS_FUNCTION_LABEL3,ulResult);
            }
        }

    }

    /* MCC2 */
    if (0 != pstCloudControl->astNvMcc[1].aucMccId[0])
    {
        TLPS_PRINT2LAYER_INFO2( CSS_WriteNvMccPrefFreq_ENUM,
                                LNAS_FUNCTION_LABEL4,
                                pstCloudControl->astNvMcc[1].aucMccId[0],
                                pstCloudControl->astNvMcc[1].aucMccId[1]);

        CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));
        if (CSS_SUCC == CSS_UpdateMccToNv(pstCloudControl->astNvMcc[1].aucMccId, pstNvPerfFreq))
        {
            ulResult = CSS_NV_Write(EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC2,
                                    (VOS_VOID *)(pstNvPerfFreq),
                                    ulDataLen);
            if (VOS_OK != ulResult)
            {
                TLPS_PRINT2LAYER_INFO1(CSS_WriteNvMccPrefFreq_ENUM,LNAS_FUNCTION_LABEL4,ulResult);
            }
        }
    }

    /* MCC3 */
    if (0 != pstCloudControl->astNvMcc[2].aucMccId[0])
    {
        TLPS_PRINT2LAYER_INFO2( CSS_WriteNvMccPrefFreq_ENUM,
                                LNAS_FUNCTION_LABEL5,
                                pstCloudControl->astNvMcc[2].aucMccId[0],
                                pstCloudControl->astNvMcc[2].aucMccId[1]);

        CSS_MEM_SET_S(pstNvPerfFreq, sizeof(CSS_NV_PREF_MCC_STRU), 0, sizeof(CSS_NV_PREF_MCC_STRU));
        if (CSS_SUCC == CSS_UpdateMccToNv(pstCloudControl->astNvMcc[2].aucMccId, pstNvPerfFreq))
        {
            ulResult = CSS_NV_Write(EN_NV_ID_PS_CLOUD_PREFER_FREQ_MCC3,
                                    (VOS_VOID *)(pstNvPerfFreq),
                                    ulDataLen);
            if (VOS_OK != ulResult)
            {
                TLPS_PRINT2LAYER_INFO1(CSS_WriteNvMccPrefFreq_ENUM,LNAS_FUNCTION_LABEL5,ulResult);
            }
        }
    }

    CSS_MEM_FREE(pstNvPerfFreq);
}


/*****************************************************************************
 Function Name  : CSS_ConvertAscToHex
 Description    : ��ASC��ת����16����
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ConvertAscToHex(VOS_UINT8 *pucDest, VOS_UINT8 ucSrc)
{
    if (CSS_NULL_PTR == pucDest)
    {
        return CSS_FAIL;
    }

    /* 0-9 */
    if((ucSrc >= 0x30)&&(ucSrc <=0x39))
    {
        *pucDest = ucSrc - 0x30;
    }
    /* A-F */
    else if((ucSrc >= 0x41)&&(ucSrc <=0x46))
    {
        *pucDest = ucSrc - 0x41 + 10;
    }
    /* a-f */
    else if((ucSrc >= 0x61)&&(ucSrc <=0x66))
    {
        *pucDest = ucSrc - 0x61 + 10;
    }
    else
    {
        return CSS_FAIL;
    }
    return CSS_SUCC;
}


/*****************************************************************************
 Function Name  : CSS_ConvertStrToHex
 Description    : ���ַ���ת����16����
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_ConvertStrToHex(VOS_UINT8 *pucHex, const VOS_UINT8 *pucStr, VOS_UINT32 ulStrLen)
{
    VOS_UINT8                           ucConvertHex;
    VOS_UINT8                           ucTmpHex = 0;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulHexNum = 0;

    if ((CSS_NULL_PTR == pucHex)
        ||(CSS_NULL_PTR == pucStr)
        ||(0 == ulStrLen))
    {
        return CSS_FAIL;
    }

    if (0 != ulStrLen % 2)
    {
        return CSS_FAIL;
    }

    CSS_MEM_SET_S(pucHex, ulStrLen/2, 0, ulStrLen/2);

    for (ulLoop = 0; ulLoop < ulStrLen; ++ulLoop)
    {
        if(CSS_FAIL == CSS_ConvertAscToHex(&ucConvertHex, pucStr[ulLoop]))
        {
            return CSS_FAIL;
        }

        if(0 == ulLoop % 2)
        {
            ucTmpHex = (VOS_UINT8)(ucConvertHex << CSS_OCTET_MOVE_4_BITS);
        }
        else
        {
            ucTmpHex |= ucConvertHex;
            pucHex[ulHexNum++] = ucTmpHex;
        }
    }
    return CSS_SUCC;
}

/*****************************************************************************
 Function Name  : CSS_IsMccNeedToDelete
 Description    : �ж�ĳ��MCC�Ƿ���Ҫɾ��(�����Ƿ����ڸ���)
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_UINT32 CSS_IsMccNeedToDelete(VOS_UINT8 aucMccId[2])
{
    VOS_UINT8                           ucIsBelongToMutiMccCountry;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTmpMcc;
    VOS_UINT8                           aucTmpMcc[2];
    VOS_UINT32                          ulCountryIdx = 0;

    CSS_ConvertSimMccToGuMcc(aucMccId, &ulTmpMcc);
    ucIsBelongToMutiMccCountry = CSS_FALSE;

    /* �ж������MCC�Ƿ����ڶ�MCC���� */
    for (i = 0; i < CSS_MCC_COUNTY_NUM; ++i)
    {
        if (CSS_TRUE == CSS_IsMccBelongToCountry(ulTmpMcc, &(g_astCountryMccList[i])))
        {
            ucIsBelongToMutiMccCountry = CSS_TRUE;
            ulCountryIdx = i;
            break;
        }
    }

    /* ��������ڶ�MCC���� */
    if (CSS_FALSE == ucIsBelongToMutiMccCountry)
    {
        /* ����ڸ����б��� */
        if (CSS_TRUE == CSS_IsMccUpdatingInUpdateStateTable(aucMccId))
        {
            return CSS_FALSE;
        }
    }
    else
    {
        /* ������ڶ�MCC���ң����жϸù��ҵ�ÿ��MCC�Ƿ��ڸ����б��� */
        for (i = 0; i < g_astCountryMccList[ulCountryIdx].ulMccNum; ++i)
        {
            CSS_ConvertGuMccToSimMcc(g_astCountryMccList[ulCountryIdx].pulMccListAddr[i], aucTmpMcc);
            if (CSS_TRUE == CSS_IsMccUpdatingInUpdateStateTable(aucTmpMcc))
            {
                return CSS_FALSE;
            }
        }
    }

    return CSS_TRUE;
}


/*****************************************************************************
 Function Name  : CSS_DeleteLocalMccNotUpdating
 Description    : �����ر����MCC�����в��������ڸ��µ�MCC����ɾ����ֻ�����ڴ�����������²Ż���ô˺����������������µ�MCC��
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_DeleteLocalMccNotUpdating(VOS_VOID)
{
    CSS_PUB_PREF_MCC_STRU              *pMccNode;
    VOS_UINT8                           ucMccNum = 0;
    CSS_MCC_ID_STRU                     astMccId[CSS_MAX_MEMORY_PERF_MCC_NUM];
    VOS_UINT8                           ucLoopNum = 0;
    VOS_UINT8                           i;

    CSS_MEM_SET_S(astMccId, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_MEMORY_PERF_MCC_NUM, 0, sizeof(CSS_MCC_ID_STRU)*CSS_MAX_MEMORY_PERF_MCC_NUM);

    /* �ҵ�������Ҫɾ����MCC�ڵ��MCC ID */
    pMccNode = CSS_GetPrefMccHeadNode();
    while ((CSS_NULL_PTR != pMccNode) && (ucLoopNum < CSS_GetPrefMccNodeNum()))
    {
        if ((CSS_TRUE == CSS_IsMccNeedToDelete(pMccNode->aucMccId))
             && (ucMccNum < CSS_MAX_MEMORY_PERF_MCC_NUM))
        {
            astMccId[ucMccNum].aucMccId[0] = pMccNode->aucMccId[0];
            astMccId[ucMccNum].aucMccId[1] = pMccNode->aucMccId[1];
            ucMccNum ++;

            TLPS_PRINT2LAYER_INFO2(CSS_DeleteLocalMccNotUpdating_ENUM, LNAS_FUNCTION_LABEL1, pMccNode->aucMccId[0], pMccNode->aucMccId[1]);
        }
        pMccNode = pMccNode->pstNext;
        ucLoopNum ++;
    }

    /* ����MCC ID������MCC ɾ�� */
    for (i = 0; i < ucMccNum; ++i)
    {
        CSS_DeleteOneMcc(astMccId[i].aucMccId);
    }

}



VOS_VOID * CSS_AllocCloudPreferNodeAndClearFullMemory(VOS_UINT32 ulLen)
{
    #if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)
    VOS_UINT32                          ulUsedLen = CSS_GetCloudMemUsedLen();
    VOS_UINT32                          ulOneBlockLen;

    /* ��Ҫ����Ľڵ㳤�ȴ���BLOCKʵ�����ݳ���ʱ��˵�������쳣�� */
    if (ulLen > CSS_CLOUD_BLOCK_DATA_LEN)
    {
        TLPS_PRINT2LAYER_ERROR(CSS_AllocCloudPreferNodeAndClearFullMemory_ENUM, LNAS_CSS_ALLOC_SIZE_LARGER_THAN_BLOCK);
        return CSS_NULL_PTR;
    }

    /* һ��С��Ĵ�С */
    ulOneBlockLen = sizeof(CSS_MEM_BLOCK_STRU);

    /* ��ʣ�µ��ڴ��Ѳ���ʹ�ã���ɾ���ϵ�MCC���� */
    if ((ulUsedLen + ulOneBlockLen) > CSS_CLOUD_MEM_TOTAL_LEN)
    {
        TLPS_PRINT2LAYER_INFO(CSS_AllocCloudPreferNodeAndClearFullMemory_ENUM, LNAS_CSS_CLOUD_MEM_IS_FULL);
        CSS_DeleteLocalMccNotUpdating();
    }

    return CSS_AllocCloudPreferNode();

    #else

    return CSS_MEM_ALLOC(ulLen);

    #endif
}


#if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)

VOS_VOID * CSS_AllocCloudPreferNode(VOS_VOID)
{
    CSS_MEM_BLOCK_STRU                 *pstBlock;
    VOS_UINT32                          ulOneBlockLen;
    VOS_UINT32                          ulTmpLen = 0;
    VOS_UINT32                          ulTotalNum = 0;
    VOS_UINT32                          ulLoop;

    /* һ��BLOCK�Ĵ�С */
    ulOneBlockLen = sizeof(CSS_MEM_BLOCK_STRU);

    /* �ܵ�BLOCK���� */
    ulTotalNum = CSS_CLOUD_MEM_TOTAL_LEN / ulOneBlockLen;

    /* ��������BLOCK���ҵ�û��ʹ�õ�BLOCK */
    for (ulLoop = 0; ulLoop < ulTotalNum; ++ulLoop)
    {
        /* ȡ�׵�ַ�ĵ�ǰƫ����Ϊ��ǰBLOCK���׵�ַ */
        pstBlock = (CSS_MEM_BLOCK_STRU*)((VOS_UINT8*)CSS_GetCloudMemAddr()+ulTmpLen);

        /* ����ǰBLOCKû�б�ʹ�� */
        if (CSS_FALSE == pstBlock->stMemHead.ucUsedFlag)
        {
            pstBlock->stMemHead.ucUsedFlag = CSS_TRUE;
            CSS_GetCloudMemUsedLen() += ulOneBlockLen;
            TLPS_PRINT2LAYER_INFO1(CSS_AllocCloudPreferNode_ENUM, LNAS_CSS_USE_CLOUD_MEM_BLOCK_INDEX, ulLoop);
            return &(pstBlock->aucData[0]);
        }

        ulTmpLen += ulOneBlockLen;
    }

    TLPS_PRINT2LAYER_INFO(CSS_AllocCloudPreferNode_ENUM, LNAS_CSS_ALLOC_RETURN_NULL_PTR);
    return CSS_NULL_PTR;
}
#endif



VOS_VOID CSS_FreeCloudPreferNode(VOS_VOID *pAddr)
{
    #if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)
    CSS_MEM_BLOCK_STRU                 *pstBlock;
    VOS_UINT32                          ulOneBlockLen;
    VOS_UINT32                          ulBlockHeadLen;

    /* �Ϸ����ж� */
    if (CSS_NULL_PTR == pAddr)
    {
        return;
    }

    /* һ��С��Ĵ�С */
    ulOneBlockLen = sizeof(CSS_MEM_BLOCK_STRU);

    /* һ��С���ͷ�ṹ��С */
    ulBlockHeadLen = sizeof(CSS_MEM_BLOCK_HEAD_STRU);

    pstBlock = (CSS_MEM_BLOCK_STRU*)((VOS_UINT8*)pAddr-ulBlockHeadLen);

    /* ���ڴ��ѱ�ʹ�ã������ʹ�ñ�ǣ���ʹ�ô�С��Ӧ���� */
    if (CSS_TRUE == pstBlock->stMemHead.ucUsedFlag)
    {
        pstBlock->stMemHead.ucUsedFlag = CSS_FALSE;
        CSS_GetCloudMemUsedLen() -= ulOneBlockLen;
    }

    #else

    CSS_MEM_FREE(pAddr);

    #endif
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of CssCloudStrategyPublic.c */



