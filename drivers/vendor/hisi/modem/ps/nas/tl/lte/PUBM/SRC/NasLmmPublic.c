/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLmmPublic.c
  Description     : NAS��������ģ��
  History         :
  Function List   :
              NAS_LMM_AddPlmnInPlmnList
              NAS_LMM_AddTaInTaList
              NAS_LMM_ClearPlmnList
              NAS_LMM_DeletePlmnFromPlmnList
              NAS_LMM_DeleteTaFromTaList
              NAS_LMM_GetMccFromPlmn
              NAS_LMM_GetMccMncFromPlmn
              NAS_LMM_GetMncFromPlmn
              NAS_LMM_HplmnMatch
              NAS_LMM_PlmnCpy
              NAS_LMM_PlmnIDMatchPlmnList
              NAS_LMM_PlmnIsUndef
              NAS_LMM_PlmnListCpy
              NAS_LMM_PlmnMatch
              NAS_LMM_TacMatch
              NAS_LMM_TaCpy
              NAS_LMM_TaIncrease
              NAS_LMM_TaMatch
              NAS_LMM_TaMatchTaList
              NAS_LMM_UndefPlmn

     1.luojian 00107747      2008-10-9  Draft Enact
     2.zhengjunyan 00148421  2011-05-28 �ļ����� NasMmPublic.c�޸�Ϊ
                                        NasLmmPublic.c
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPublic.h"
#include    "NasLmmPubMOsa.h"
#include    "NasEmmPubUGlobal.h"
#include    "NasEmmAttDetInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBLIC_C
/*lint +e767*/

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


/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_LMM_GetMccFromPlmn
 Description     : ��PLMN��ȡMCC
 Input           :
                   NAS_MM_PLMN_ID_STRU                 *pstPlmnId,
 Output          :
                   VOS_UINT8                           *pucMcc1,
                   VOS_UINT8                           *pucMcc2,
                   VOS_UINT8                           *pucMcc3,
 Return          : ������

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_GetMccFromPlmn
(
    const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
    VOS_UINT8                           *pucMcc1,
    VOS_UINT8                           *pucMcc2,
    VOS_UINT8                           *pucMcc3
)
{
    if ( (VOS_NULL_PTR == pucMcc1)
        ||(VOS_NULL_PTR == pucMcc2)
        ||(VOS_NULL_PTR == pucMcc3)
        ||(VOS_NULL_PTR == pstPlmnId))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetMccFromPlmn: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetMccFromPlmn_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* PLMNδ���壬�򷵻�F */
    if (VOS_TRUE == NAS_LMM_PlmnIsUndef(pstPlmnId))
    {
        *pucMcc1                         = NAS_LMM_HEX_DIGIT_F;
        *pucMcc2                         = NAS_LMM_HEX_DIGIT_F;
        *pucMcc3                         = NAS_LMM_HEX_DIGIT_F;
    }
    else
    {
        /* ȡ��ÿһλMCC */
        *pucMcc1 =  pstPlmnId->aucPlmnId[0] & NAS_LMM_HIGH_HALF_BYTE_MASK;
        *pucMcc2 = (pstPlmnId->aucPlmnId[0] & NAS_LMM_LOW_HALF_BYTE_MASK)
                   >> NAS_LMM_RIGHT_SHIFT_HALF_BYTE;
        *pucMcc3 =  pstPlmnId->aucPlmnId[1] & NAS_LMM_HIGH_HALF_BYTE_MASK;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_GetMncFromPlmn
 Description     : ��PLMN��ȡMNC
 Input           :
                   NAS_MM_PLMN_ID_STRU                 *pstPlmnId,
 Output          :
                   VOS_UINT8                           *pucMnc1,
                   VOS_UINT8                           *pucMnc2,
                   VOS_UINT8                           *pucMnc3,
 Return          : ������

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_GetMncFromPlmn
(
    const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
    VOS_UINT8                           *pucMnc1,
    VOS_UINT8                           *pucMnc2,
    VOS_UINT8                           *pucMnc3
)
{
    if ( (VOS_NULL_PTR == pucMnc1)
        ||(VOS_NULL_PTR == pucMnc2)
        ||(VOS_NULL_PTR == pucMnc3)
        ||(VOS_NULL_PTR == pstPlmnId))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetMncFromPlmn: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetMncFromPlmn_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* PLMNδ���壬�򷵻�F */
    if (VOS_TRUE == NAS_LMM_PlmnIsUndef(pstPlmnId))
    {
        *pucMnc1                         = NAS_LMM_HEX_DIGIT_F;
        *pucMnc2                         = NAS_LMM_HEX_DIGIT_F;
        *pucMnc3                         = NAS_LMM_HEX_DIGIT_F;
    }
    else
    {
        /* ȡ��ÿһλMNC */
        *pucMnc1 =  pstPlmnId->aucPlmnId[2] & NAS_LMM_HIGH_HALF_BYTE_MASK;
        *pucMnc2 = (pstPlmnId->aucPlmnId[2] & NAS_LMM_LOW_HALF_BYTE_MASK)
                   >> NAS_LMM_RIGHT_SHIFT_HALF_BYTE;
        *pucMnc3 = (pstPlmnId->aucPlmnId[1] & NAS_LMM_LOW_HALF_BYTE_MASK)
                   >> NAS_LMM_RIGHT_SHIFT_HALF_BYTE;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_GetMccMncFromPlmn
 Description     : ��PLMN��ȡMCC,MNC,����10���������
 Input           :
                   NAS_MM_PLMN_ID_STRU                 *pstPlmnId,
 Output          :
                   VOS_UINT32                          *pulMCC,
                   VOS_UINT32                          *pulMNC
 Return          : ������

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_GetMccMncFromPlmn
(
    const NAS_MM_PLMN_ID_STRU           *pstPlmnId,
    VOS_UINT32                          *pulMCC,
    VOS_UINT32                          *pulMNC
)
{
    VOS_UINT8                           ucMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit3 = NAS_LMM_NULL;

    if ( (VOS_NULL_PTR == pulMCC)
       ||(VOS_NULL_PTR == pulMNC)
       ||(VOS_NULL_PTR == pstPlmnId))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetMccMncFromPlmn: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetMccMncFromPlmn_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* PLMNδ���壬�򷵻�0 */
    if (VOS_TRUE == NAS_LMM_PlmnIsUndef(pstPlmnId))
    {
        *pulMCC                         = 0;
        *pulMNC                         = 0;
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetMccMncFromPlmn: PLMN is not defined.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetMccMncFromPlmn_ENUM,LNAS_FUNCTION_LABEL1);

        return;
    }

    /* ��ȡMCCÿһλ */
    NAS_LMM_GetMccFromPlmn(pstPlmnId,&ucMccDigit1,&ucMccDigit2,&ucMccDigit3);

    /* ��ȡMNCÿһλ */
    NAS_LMM_GetMncFromPlmn(pstPlmnId,&ucMncDigit1,&ucMncDigit2,&ucMncDigit3);

    *pulMCC = (100*ucMccDigit1) + (10*ucMccDigit2) + ucMccDigit3;

    /* MNC3:F,ֻȡMNC1,MNC2*/
    if ( NAS_LMM_HEX_DIGIT_F == ucMncDigit3 )
    {
        *pulMNC = (10*ucMncDigit1) + ucMncDigit2;
    }
    else
    {
        *pulMNC = (100*ucMncDigit1) + (10*ucMncDigit2) + ucMncDigit3;
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_ExactlyPlmnMatch
 Description     : ��������:����������MNC����Ϊ2��3ʱPLMN�ıȽ�
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-8-25  Draft Enact

*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32  NAS_LMM_ExactlyPlmnMatch
(
    const NAS_MM_PLMN_ID_STRU          *pstLocalPlmn,
    const NAS_MM_PLMN_ID_STRU          *pstBcchPlmn
)
{
    VOS_UINT32                          ulMatchResult = NAS_LMM_MATCH_FAIL;
    VOS_UINT32                          ulSimMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulSimMnc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMnc = NAS_LMM_NULL;

    /* SIM MCC MNC Digits */
    VOS_UINT8                           ucSimMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit3 = NAS_LMM_NULL;

    /* BCCH MCC MNC Digits */
    VOS_UINT8                           ucBcchMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit3 = NAS_LMM_NULL;

    if ( (VOS_NULL_PTR == pstLocalPlmn)
        ||(VOS_NULL_PTR ==pstBcchPlmn))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    /* ��ÿһλMCC,MNC��ȡ���� */
    NAS_LMM_GetMccFromPlmn(pstLocalPlmn,&ucSimMccDigit1,&ucSimMccDigit2,&ucSimMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstLocalPlmn,&ucSimMncDigit1,&ucSimMncDigit2,&ucSimMncDigit3);

    NAS_LMM_GetMccFromPlmn(pstBcchPlmn,&ucBcchMccDigit1,&ucBcchMccDigit2,&ucBcchMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstBcchPlmn,&ucBcchMncDigit1,&ucBcchMncDigit2,&ucBcchMncDigit3);

    NAS_LMM_GetMccMncFromPlmn(pstLocalPlmn, &ulSimMcc, &ulSimMnc);

    NAS_LMM_GetMccMncFromPlmn(pstBcchPlmn, &ulBcchMcc, &ulBcchMnc);

    /* �ж�SIM-MCC��BCCH-MCC�Ƿ���� */
    if ( ulSimMcc != ulBcchMcc  )
    {
        return NAS_LMM_MATCH_FAIL;
    }
    if (ulSimMnc == ulBcchMnc)
    {
        return NAS_LMM_MATCH_SUCCESS;
    }

    if ((310 <= ulBcchMcc) && (316 >= ulBcchMcc))
    {
        if (((0x0f == ucBcchMncDigit3)&&(0x0 == ucSimMncDigit3))
           ||((0x0f == ucSimMncDigit3)&&(0x0 == ucBcchMncDigit3)))
        {
           ulMatchResult = (ucSimMncDigit1 == ucBcchMncDigit1)
                        && (ucSimMncDigit2 == ucBcchMncDigit2);
        }
    }

    return ulMatchResult;
}
/*****************************************************************************
 Function Name   : NAS_LMM_GetPlmnExactlyComparaFlg
 Description     : ��ȡMML�б����Mnc��ȷ�Ƚϱ��ExactlyCompareFlg
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-8-25  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_LMM_GetPlmnExactlyComparaFlg( VOS_VOID )
{
    NAS_LMM_PUBM_LOG1_NORM("NAS_LMM_GetPlmnExactlyComparaFlg:NAS_MML_GetPlmnExactlyComparaFlg() =",
                        NAS_MML_GetPlmnExactlyComparaFlg());
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_GetPlmnExactlyComparaFlg_ENUM,LNAS_FUNCTION_LABEL1,
                        NAS_MML_GetPlmnExactlyComparaFlg());
    #ifndef __PS_WIN32_RECUR__

    if (VOS_TRUE == NAS_MML_GetPlmnExactlyComparaFlg())
    {
        NAS_LMM_LogPlmnexactlyCmpFlag(VOS_TRUE);
        return NAS_LMM_SUCC;
    }
    NAS_LMM_LogPlmnexactlyCmpFlag(VOS_FALSE);
    return NAS_LMM_FAIL;
    #else
    if (VOS_TRUE == Stub_NAS_MML_GetPlmnExactlyComparaFlg())
    {
        return NAS_LMM_SUCC;
    }
    return NAS_LMM_FAIL;

    #endif
}
/*****************************************************************************
 Function Name   : NAS_LMM_PlmnMatch
 Description     : PLMN�Ƚ�
 Input           : NAS_MM_PLMN_ID_STRU *pstLocalPlmn
                   NAS_MM_PLMN_ID_STRU *pstBcchPlmn
 Output          : ����룬��NAS_MATCH_RESULT_ENUM_UINT32����
 Return          : VOS_VOID
 History         :
     1.luojian 00107747      2008-10-8  Draft Enact

     2.leili   00132387      2011-12-15   Modify

        1) Э����ֻ��˵�����������µ�Bcch-Mnc��3����ΪFʱ��Sim-Mnc�����Ӧ0��balong
        ����IOTʱ����Ҫ��Bcch-Mnc��3����Ϊ0ʱ��Sim-Mnc�����ӦF,���Ҹ�ͨ�ܹ�ͨ����
        ��ſ�Ƚ�������

        2) Э��23.122 Annex.A ��ֻ��˵��Hplmn��Ҫʵ��PCS 1900Э�飬��Balong������Plmn
        �������˱����������жϣ�����ͨ����IOT���ԣ�����V7R1Ҳ�մ��޸�
*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnMatch
(
    const NAS_MM_PLMN_ID_STRU          *pstLocalPlmn,
    const NAS_MM_PLMN_ID_STRU          *pstBcchPlmn
)
{
    VOS_UINT32                          ulMatchResult = NAS_LMM_MATCH_FAIL;
    VOS_UINT32                          ulSimMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulSimMnc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMnc = NAS_LMM_NULL;

    /* SIM MCC MNC Digits */
    VOS_UINT8                           ucSimMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit3 = NAS_LMM_NULL;

    /* BCCH MCC MNC Digits */
    VOS_UINT8                           ucBcchMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit3 = NAS_LMM_NULL;

    if ( (VOS_NULL_PTR == pstLocalPlmn)
        ||(VOS_NULL_PTR ==pstBcchPlmn))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    if (NAS_LMM_SUCC == NAS_LMM_GetPlmnExactlyComparaFlg())
    {
        ulMatchResult = NAS_LMM_ExactlyPlmnMatch(pstLocalPlmn,pstBcchPlmn);

        return ulMatchResult;
    }

    /* ��ÿһλMCC,MNC��ȡ���� */
    NAS_LMM_GetMccFromPlmn(pstLocalPlmn,&ucSimMccDigit1,&ucSimMccDigit2,&ucSimMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstLocalPlmn,&ucSimMncDigit1,&ucSimMncDigit2,&ucSimMncDigit3);

    NAS_LMM_GetMccFromPlmn(pstBcchPlmn,&ucBcchMccDigit1,&ucBcchMccDigit2,&ucBcchMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstBcchPlmn,&ucBcchMncDigit1,&ucBcchMncDigit2,&ucBcchMncDigit3);

    NAS_LMM_GetMccMncFromPlmn(pstLocalPlmn, &ulSimMcc, &ulSimMnc);

    NAS_LMM_GetMccMncFromPlmn(pstBcchPlmn, &ulBcchMcc, &ulBcchMnc);

    /* �ж�SIM-MCC��BCCH-MCC�Ƿ���� */
    if ( ulSimMcc != ulBcchMcc  )
    {
        return NAS_LMM_MATCH_FAIL;
    }

    /* ����������Ļ����� */
    if ((310 > ulBcchMcc) || (316 < ulBcchMcc))
    {
        /* MNC����Ϊ2����� */
        if (0x0f == ucBcchMncDigit3)
        {
            /* 6.�ж�SIM-MNC��BCCH-MNCǰ���������Ƿ�ƥ�� */
            ulMatchResult = (ucSimMncDigit1 == ucBcchMncDigit1)
                            && (ucSimMncDigit2 == ucBcchMncDigit2);
        }
        else /* MNC����Ϊ3����� */
        {
            /* �ж�SIM-MNC��BCCH-MNC���������Ƿ�ƥ�� */
            ulMatchResult = (ulSimMnc == ulBcchMnc);
        }
    }
    else /* ����������MCC��ΧΪ310~316 */
    {
        /* ���BCCH-MNC&SIM-MNC�ĵ��������ֱ���0��F,������PCS1900Ҫ�� */
        if (((0x0f == ucBcchMncDigit3)&&(0x0 == ucSimMncDigit3))
           ||((0x0f == ucSimMncDigit3)&&(0x0 == ucBcchMncDigit3)))
        {
            /* �ж�SIM-MNC��BCCH-MNCǰ���������Ƿ�ƥ�� */
            ulMatchResult = (ucSimMncDigit1 == ucBcchMncDigit1)
                            && (ucSimMncDigit2 == ucBcchMncDigit2);
        }
        else
        {
            /* �ж�SIM-MNC��BCCH-MNC���������Ƿ�ƥ�� */
            ulMatchResult = (ulSimMnc == ulBcchMnc);
        }
    }

    return ulMatchResult;
}
/*****************************************************************************
 Function Name   : NAS_LMM_HplmnMatch
 Description     : HPLMN�Ƚ�,�ο�23.122 Annex A
 Input           :
                     NAS_MM_PLMN_ID_STRU                 *pstHplmn,
                     NAS_MM_PLMN_ID_STRU                 *pstBcchPlmn
 Output          : ����룬��NAS_MATCH_RESULT_ENUM_UINT32����
 Return          : VOS_VOID
 History         :
     1.luojian 00107747      2008-10-8  Draft Enact
     2.leili   00132387      2011-12-15   Modify

        1) Э����ֻ��˵�����������µ�Bcch-Mnc��3����ΪFʱ��Sim-Mnc�����Ӧ0��balong
        ����IOTʱ����Ҫ��Bcch-Mnc��3����Ϊ0ʱ��Sim-Mnc�����ӦF,���Ҹ�ͨ�ܹ�ͨ����
        ��ſ�Ƚ�������
*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_HplmnMatch
(
    const   NAS_MM_PLMN_ID_STRU        *pstHplmn,
    const   NAS_MM_PLMN_ID_STRU        *pstBcchPlmn
)
{
    VOS_UINT32                          ulMatchResult = NAS_LMM_MATCH_FAIL;
    VOS_UINT32                          ulSimMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMcc = NAS_LMM_NULL;
    VOS_UINT32                          ulSimMnc = NAS_LMM_NULL;
    VOS_UINT32                          ulBcchMnc = NAS_LMM_NULL;
    /* SIM MCC MNC Digits */
    VOS_UINT8                           ucSimMccDigit1;
    VOS_UINT8                           ucSimMccDigit2;
    VOS_UINT8                           ucSimMccDigit3;
    VOS_UINT8                           ucSimMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucSimMncDigit3 = NAS_LMM_NULL;

    /* BCCH MCC MNC Digits */
    VOS_UINT8                           ucBcchMccDigit1;
    VOS_UINT8                           ucBcchMccDigit2 ;
    VOS_UINT8                           ucBcchMccDigit3;
    VOS_UINT8                           ucBcchMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucBcchMncDigit3 = NAS_LMM_NULL;

    if ( (VOS_NULL_PTR == pstHplmn)
        ||(VOS_NULL_PTR ==pstBcchPlmn))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    if (NAS_LMM_SUCC == NAS_LMM_GetPlmnExactlyComparaFlg())
    {
        ulMatchResult = NAS_LMM_ExactlyPlmnMatch(pstHplmn,pstBcchPlmn);

        return ulMatchResult;
    }

    /* ��ÿһλMCC,MNC��ȡ���� */
    NAS_LMM_GetMccFromPlmn(pstHplmn,&ucSimMccDigit1,&ucSimMccDigit2,&ucSimMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstHplmn,&ucSimMncDigit1,&ucSimMncDigit2,&ucSimMncDigit3);

    NAS_LMM_GetMccFromPlmn(pstBcchPlmn,&ucBcchMccDigit1,&ucBcchMccDigit2,&ucBcchMccDigit3);

    NAS_LMM_GetMncFromPlmn(pstBcchPlmn,&ucBcchMncDigit1,&ucBcchMncDigit2,&ucBcchMncDigit3);


    NAS_LMM_GetMccMncFromPlmn(pstHplmn, &ulSimMcc, &ulSimMnc);

    NAS_LMM_GetMccMncFromPlmn(pstBcchPlmn,&ulBcchMcc, &ulBcchMnc);

   /* �ж�SIM-MCC��BCCH-MCC�Ƿ���� */
    if ( ulSimMcc != ulBcchMcc  )
    {
        return NAS_LMM_MATCH_FAIL;
    }

    /* ����������Ļ����� */
    if ((310 > ulBcchMcc) || (316 < ulBcchMcc))
    {
        /* MNC����Ϊ2����� */
        if (0x0f == ucBcchMncDigit3)
        {
            /* 6.�ж�SIM-MNC��BCCH-MNCǰ���������Ƿ�ƥ�� */
            ulMatchResult = (ucSimMncDigit1 == ucBcchMncDigit1)
                            && (ucSimMncDigit2 == ucBcchMncDigit2);
        }
        else /* MNC����Ϊ3����� */
        {
            /* �ж�SIM-MNC��BCCH-MNC���������Ƿ�ƥ�� */
            ulMatchResult = (ulSimMnc == ulBcchMnc);
        }
    }
    else /* ����������MCC��ΧΪ310~316 */
    {
        /* ���BCCH-MNC&SIM-MNC�ĵ��������ֱ���0��F,������PCS1900Ҫ�� */
        if (((0x0f == ucBcchMncDigit3)&&(0x0 == ucSimMncDigit3))
           ||((0x0f == ucSimMncDigit3)&&(0x0 == ucBcchMncDigit3)))
        {
            /* �ж�SIM-MNC��BCCH-MNCǰ���������Ƿ�ƥ�� */
            ulMatchResult = (ucSimMncDigit1 == ucBcchMncDigit1)
                            && (ucSimMncDigit2 == ucBcchMncDigit2);
        }
        else
        {
            /* �ж�SIM-MNC��BCCH-MNC���������Ƿ�ƥ�� */
            ulMatchResult = (ulSimMnc == ulBcchMnc);
        }
    }

    return ulMatchResult;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PlmnIDMatchPlmnList
 Description     : �ж�PLMN ID�Ƿ���PLMN�б���
 Input           : VOS_VOID
 Output          : ����룬��NAS_MATCH_RESULT_ENUM_UINT32����
 Return          : VOS_VOID
 History         :
     1.luojian 00107747      2008-10-9  Draft Enact

*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnIDMatchPlmnList
(
    const NAS_MM_PLMN_ID_STRU          *pstPlmnId,
    const NAS_MM_PLMN_LIST_STRU        *pstPlmnList
)
{
    VOS_UINT8                           i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult;

    if ( (VOS_NULL_PTR == pstPlmnId)
       ||(VOS_NULL_PTR == pstPlmnList))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    for (i=0; i<pstPlmnList->ulPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_LMM_PlmnMatch(pstPlmnId, &pstPlmnList->astPlmnId[i]))
        {
            ulMatchResult = NAS_LMM_MATCH_SUCCESS;
            /* �����һ��ƥ��ɹ�����������ѭ�� */
            break;
        }
    }
    return ulMatchResult;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PlmnIDMatchHplmnList
 Description     : �ж�PLMN ID�Ƿ���HPLMN�б���
 Input           : VOS_VOID
 Output          : ����룬��NAS_MATCH_RESULT_ENUM_UINT32����
 Return          : VOS_VOID
 History         :
     1.leili 00132387       2011-06-07      Draft Enact

*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_PlmnIDMatchHplmnList
(
    const NAS_MM_PLMN_ID_STRU          *pstPlmnId,
    const NAS_MM_PLMN_LIST_STRU        *pstPlmnList
)
{
    VOS_UINT8                           i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult;

    if ( (VOS_NULL_PTR == pstPlmnId)
       ||(VOS_NULL_PTR == pstPlmnList))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    for (i=0; i<pstPlmnList->ulPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_LMM_HplmnMatch(&pstPlmnList->astPlmnId[i],pstPlmnId))
        {
            ulMatchResult = NAS_LMM_MATCH_SUCCESS;
            /* �����һ��ƥ��ɹ�����������ѭ�� */
            break;
        }
    }
    return ulMatchResult;
}


/*****************************************************************************
 Function Name   : NAS_LMM_TaCpy
 Description     : TA��ֵ����
 Input           :NAS_MM_TA_STRU                      *pstDestTa
                  NAS_MM_TA_STRU                      *pstOrgTa
 Output          : None
 Return          : VOS_VOID

 History         :
    1.luojian 00107747      2009-3-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_TaCpy
(
    NAS_MM_TA_STRU                      *pstDestTa,
    const   NAS_MM_TA_STRU              *pstOrgTa
)
{
    if ( (VOS_NULL_PTR == pstDestTa)
       ||(VOS_NULL_PTR == pstOrgTa))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_TaCpy: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_TaCpy_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstDestTa->stTac.ucTac              = pstOrgTa->stTac.ucTac;
    pstDestTa->stTac.ucTacCnt           = pstOrgTa->stTac.ucTacCnt;

    NAS_LMM_PlmnCpy(&(pstDestTa->stPlmnId), &(pstOrgTa->stPlmnId));

    return;
}



/*****************************************************************************
 Function Name   : NAS_LMM_PlmnCpy
 Description     : PLMN��ֵ����
 Input           :NAS_MM_PLMN_ID_STRU *pstDestPlmn
                  NAS_MM_PLMN_ID_STRU *pstOrgPlmn
 Output          : None
 Return          : ����룬��NAS_LMM_ERROR_CODE_ENUM_UINT32����
 History         :
     1.luojian 00107747      2008-10-8  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_PlmnCpy
(
    NAS_MM_PLMN_ID_STRU                *pstDestPlmn,
    const   NAS_MM_PLMN_ID_STRU        *pstOrgPlmn
)
{
    if ( (VOS_NULL_PTR == pstDestPlmn)
       ||(VOS_NULL_PTR == pstOrgPlmn))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PlmnCpy: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PlmnCpy_ENUM,LNAS_NULL_PTR);
        return;
    }
    pstDestPlmn->aucPlmnId[0] = pstOrgPlmn->aucPlmnId[0];
    pstDestPlmn->aucPlmnId[1] = pstOrgPlmn->aucPlmnId[1];
    pstDestPlmn->aucPlmnId[2] = pstOrgPlmn->aucPlmnId[2];
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PlmnListCpy
 Description     : PLMN list��ֵ����
 Input           :
                  NAS_MM_PLMN_LIST_STRU               *pstDestPlmnList,
                  NAS_MM_PLMN_LIST_STRU               *pstOrgPlmnList,
 Output          : None
 Return          : ����룬��NAS_LMM_ERROR_CODE_ENUM_UINT32����
 History         :
     1.luojian 00107747      2008-10-8  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_PlmnListCpy
(
    NAS_MM_PLMN_LIST_STRU               *pstDestPlmnList,
    const   NAS_MM_PLMN_LIST_STRU       *pstOrgPlmnList
)
{
    VOS_UINT8                           i;

    if ( (VOS_NULL_PTR == pstDestPlmnList)
       ||(VOS_NULL_PTR == pstOrgPlmnList))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PlmnListCpy: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PlmnListCpy_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstDestPlmnList->ulPlmnNum    = pstOrgPlmnList->ulPlmnNum;

    for (i=0; i<pstOrgPlmnList->ulPlmnNum; i++)
    {
        NAS_LMM_PlmnCpy(&pstDestPlmnList->astPlmnId[i],
                    &pstOrgPlmnList->astPlmnId[i]);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_TaIncrease
 Description     : TA����1
 Input           : NAS_MM_TAC_STRU                     *pstTac
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2008-12-18  Draft Enact

*****************************************************************************/
NAS_LMM_ERROR_CODE_ENUM_UINT32 NAS_LMM_TaIncrease
(
    NAS_MM_TAC_STRU                     *pstTac
)
{
    VOS_UINT16                          usTac;

    if (VOS_NULL_PTR == pstTac)
    {
        return NAS_LMM_ERR_CODE_PTR_NULL;
    }

    usTac = (pstTac->ucTac<<8) | (pstTac->ucTacCnt);

    usTac++;

    pstTac->ucTac = (usTac>>8) & 0xFF;

    pstTac->ucTacCnt = usTac & 0xFF;

    return NAS_LMM_SUCC;

}

/*****************************************************************************
 Function Name   : NAS_LMM_TacMatch
 Description     : �ж�TAC�Ƿ���ͬ
 Input           :
                   NAS_MM_TAC_STRU                    *pstTac1,
                   NAS_MM_TAC_STRU                    *pstTac2
 Output          :
 Return          : ����룬��NAS_MATCH_RESULT_ENUM_UINT32����
 History         :
     1.luojian 00107747      2008-10-11  Draft Enact

*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TacMatch
(
    const   NAS_MM_TAC_STRU            *pstTac1,
    const   NAS_MM_TAC_STRU            *pstTac2
)
{
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult;

    if ( (VOS_NULL_PTR == pstTac1)
       ||(VOS_NULL_PTR == pstTac2))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    if ( (pstTac1->ucTac == pstTac2->ucTac)
       &&(pstTac1->ucTacCnt == pstTac2->ucTacCnt))
    {
        ulMatchResult                   = NAS_LMM_MATCH_SUCCESS;
    }
    return ulMatchResult;
}


/*****************************************************************************
 Function Name   : NAS_LMM_TaMatch
 Description     : �ж�TA�Ƿ���ͬ
 Input           : VOS_VOID
 Output          : ����룬��NAS_MATCH_RESULT_ENUM_UINT32����
 Return          : VOS_VOID
 History         :
     1.luojian 00107747      2008-10-11  Draft Enact

*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatch
(
    const   NAS_MM_TA_STRU             *pstTa1,
    const   NAS_MM_TA_STRU             *pstTa2
)
{
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult;

    if ( (VOS_NULL_PTR == pstTa1)
       ||(VOS_NULL_PTR == pstTa2))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    if ( NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnMatch(&pstTa1->stPlmnId, &pstTa2->stPlmnId))
    {
        if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TacMatch(&pstTa1->stTac,&pstTa2->stTac) )
        {
            ulMatchResult               = NAS_LMM_MATCH_SUCCESS;
        }
    }

    return ulMatchResult;
}



/*****************************************************************************
 Function Name   : NAS_LMM_TaMatchTaList
 Description     : �ж�TA�Ƿ���TA LIST�б���
 Input           : VOS_VOID
 Output          :
                  NAS_MM_TA_STRU                      *pstTa,
                  NAS_MM_TA_LIST_STRU                 *pstTaList

 Return          : ����룬��NAS_MATCH_RESULT_ENUM_UINT32����
 History         :
     1.luojian 00107747      2008-10-11  Draft Enact

*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatchTaList
(
    const   NAS_MM_TA_STRU             *pstTa,
    const   NAS_MM_TA_LIST_STRU        *pstTaList
)
{
    VOS_UINT8                           i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32     ulMatchResult;
    NAS_MM_TA_STRU                      stTaInTalist;

    if ( (VOS_NULL_PTR == pstTa)
       ||(VOS_NULL_PTR == pstTaList))
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    NAS_LMM_PUBM_LOG3_INFO("DST_PLMNID: ",  pstTa->stPlmnId.aucPlmnId[0],
                                            pstTa->stPlmnId.aucPlmnId[1],
                                            pstTa->stPlmnId.aucPlmnId[2]);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL1,
                                            pstTa->stPlmnId.aucPlmnId[0]);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL2,
                                            pstTa->stPlmnId.aucPlmnId[1],
                                            pstTa->stPlmnId.aucPlmnId[2]);

    NAS_LMM_PUBM_LOG2_INFO("DST_TAC: ",     pstTa->stTac.ucTac,
                                            pstTa->stTac.ucTacCnt);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL3,
                                            pstTa->stTac.ucTac,
                                            pstTa->stTac.ucTacCnt);

    /* ƥ��TA�б� */
    for (i=0; i<pstTaList->ulTaNum; i++)
    {
        NAS_LMM_TaCpy(&stTaInTalist, &(pstTaList->astTa[i]));

        NAS_LMM_PUBM_LOG3_INFO("LIST_PLMNID: ", stTaInTalist.stPlmnId.aucPlmnId[0],
                                                stTaInTalist.stPlmnId.aucPlmnId[1],
                                                stTaInTalist.stPlmnId.aucPlmnId[2]);
        TLPS_PRINT2LAYER_INFO1(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL4,
                                                stTaInTalist.stPlmnId.aucPlmnId[0]);
        TLPS_PRINT2LAYER_INFO2(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL5,
                                                stTaInTalist.stPlmnId.aucPlmnId[1],
                                                stTaInTalist.stPlmnId.aucPlmnId[2]);

        NAS_LMM_PUBM_LOG2_INFO("LIST_TAC: ",    stTaInTalist.stTac.ucTac,
                                                stTaInTalist.stTac.ucTacCnt);
        TLPS_PRINT2LAYER_INFO2(NAS_LMM_TaMatchTaList_ENUM,LNAS_FUNCTION_LABEL6,
                                                stTaInTalist.stTac.ucTac,
                                                stTaInTalist.stTac.ucTacCnt);

        if ( VOS_TRUE == NAS_LMM_TaMatch(pstTa, &stTaInTalist))
        {
            ulMatchResult           = NAS_LMM_MATCH_SUCCESS;

            /* �����һ��ƥ��ɹ�����������ѭ�� */
            break;
        }
    }
    return ulMatchResult;

}


/*****************************************************************************
 Function Name   : NAS_LMM_AddTaInTaList
 Description     : ���һ��TA��TA�б���
 Input           :
                   NAS_MM_TA_STRU                      *pstTa,
                   NAS_MM_TA_LIST_STRU                 *pstTaList,
                   VOS_UINT32                          ulListNumMax
 Output          :
                   NAS_MM_TA_LIST_STRU                 *pstTaList,
                   VOS_UINT32                          ulListNumMax
 Return          : VOS_VOID

 History         : ����룬��NAS_LMM_ERROR_CODE_ENUM_UINT32����
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_AddTaInTaList
(
    const   NAS_MM_TA_STRU              *pstTa,
    NAS_MM_TA_LIST_STRU                 *pstTaList,
    VOS_UINT32                          ulListNumMax
)
{
    VOS_UINT32                          i;

    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(pstTa, pstTaList))
    {
         NAS_LMM_PUBM_LOG_NORM("NAS_LMM_AddTaInTaList: TA is already in TaiList. ");
         TLPS_PRINT2LAYER_INFO(NAS_LMM_AddTaInTaList_ENUM,LNAS_ENTRY);
         return;
    }

    /* �б��в����ڵ�ǰҪ���뱻���б��TA*/
    /* TA����û�е����ֱ�ӽ�TA�ӵ�ĩβ */
    if (ulListNumMax > pstTaList->ulTaNum)
    {
        NAS_LMM_TaCpy(&pstTaList->astTa[pstTaList->ulTaNum],pstTa);
        pstTaList->ulTaNum++;
    }
    /* TA��������󣬽�TA�ӵ�ĩβ������TA��ǰ�ƶ�����һ��TA�Ƴ� */
    else
    {
        pstTaList->ulTaNum             = ulListNumMax;

        for (i=0; i<(ulListNumMax -1) ; i++)
        {
            NAS_LMM_TaCpy(&(pstTaList->astTa[i]),
                         &(pstTaList->astTa[i+1]));
        }

        NAS_LMM_TaCpy(&(pstTaList->astTa[i]),
                     pstTa);
    }
    return;

}


/*****************************************************************************
 Function Name   : NAS_LMM_DeleteTaFromTaList
 Description     : ��TA LIST��ɾ��TA
 Input           :
                   NAS_MM_TA_STRU                      *pstTa,
                   NAS_MM_TA_LIST_STRU                 *pstTaList,
                   VOS_UINT32                          ulListNumMax
 Output          :
                   NAS_MM_TA_LIST_STRU                 *pstTaList,
 Return          : ����룬��NAS_LMM_ERROR_CODE_ENUM_UINT32����

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_DeleteTaFromTaList
(
    const   NAS_MM_TA_STRU              *pstTa,
    NAS_MM_TA_LIST_STRU                 *pstTaList,
    VOS_UINT32                          ulListNumMax
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulFound;

    ulFound                             = VOS_FALSE;

    for (i=0; i<pstTaList->ulTaNum; i++)
    {
        if (VOS_FALSE == ulFound)
        {
            if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch( pstTa, &pstTaList->astTa[i]))
            {
                ulFound = VOS_TRUE;
            }
        }
        if ( (VOS_TRUE == ulFound) && (i < (ulListNumMax-1)) )
        {
            NAS_LMM_TaCpy(&(pstTaList->astTa[i]),
                         &(pstTaList->astTa[i+1]));
        }
    }

    /* ��ɾ����TA���б���,�б��������һ�� */
    if (VOS_TRUE == ulFound)
    {
        pstTaList->ulTaNum--;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_AddPlmnInPlmnList
 Description     : ���һ��PLMN��PLMNs�б���,���PLMN�б�����,��һ��PLMN�����Ƴ�
 Input           :
                   NAS_MM_PLMN_ID_STRU                 stPlmnId,
                   NAS_MM_PLMN_LIST_STRU               *pstPlmnList,
                   VOS_UINT32                          ulListNumMax
 Output          :
                   NAS_MM_PLMN_LIST_STRU               *pstPlmnList,

 Return          : ����룬��NAS_LMM_ERROR_CODE_ENUM_UINT32����

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_AddPlmnInPlmnList
(
    const   NAS_MM_PLMN_ID_STRU         *pstPlmnId,
    NAS_MM_PLMN_LIST_STRU               *pstPlmnList,
    VOS_UINT32                          ulListNumMax
)
{
    VOS_UINT32                          i;

    /* ����ָ��ǿռ�� */
    if ( (VOS_NULL_PTR == pstPlmnId)
        ||(VOS_NULL_PTR == pstPlmnList))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_AddPlmnInPlmnList: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_AddPlmnInPlmnList_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* ����ӵ�PLMN�����б��в���� */
    if (NAS_LMM_MATCH_FAIL == NAS_LMM_PlmnIDMatchPlmnList(pstPlmnId, pstPlmnList))
    {
        /* �б�δ����ֱ����ӵ���� */
        if (ulListNumMax > pstPlmnList->ulPlmnNum)
        {
            NAS_LMM_PlmnCpy(&pstPlmnList->astPlmnId[pstPlmnList->ulPlmnNum],
                        pstPlmnId);
            pstPlmnList->ulPlmnNum++;
        }
        /* �б���������һ��FPLMN�Ƴ�,����ӵ�PLMN�ӵ���� */
        else
        {
            pstPlmnList->ulPlmnNum  = ulListNumMax;

            for (i=0; i<(ulListNumMax -1) ; i++)
            {
                NAS_LMM_PlmnCpy(&(pstPlmnList->astPlmnId[i]),
                               &(pstPlmnList->astPlmnId[i+1]));
            }
            NAS_LMM_PlmnCpy(&pstPlmnList->astPlmnId[i],pstPlmnId);
        }
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_DeletePlmnFromPlmnList
 Description     : ��PLMN�б���ɾ��PLMN
 Input           :
                   NAS_MM_PLMN_ID_STRU                 *pstPlmnId,
                   NAS_MM_PLMN_LIST_STRU               *pstPlmnList,
                   VOS_UINT32                          ulListNumMax
 Output          :
                   NAS_MM_PLMN_LIST_STRU               *pstPlmnList,

 Return          : VOS_VOID

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_DeletePlmnFromPlmnList
(
    const   NAS_MM_PLMN_ID_STRU         *pstPlmnId,
    NAS_MM_PLMN_LIST_STRU               *pstPlmnList,
    VOS_UINT32                          ulListNumMax
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulFound;

    /* ����ָ��ǿռ�� */
    if ( (VOS_NULL_PTR == pstPlmnId)
       ||(VOS_NULL_PTR == pstPlmnList))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_DeletePlmnFromPlmnList: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DeletePlmnFromPlmnList_ENUM,LNAS_NULL_PTR);
        return;
    }

    if (pstPlmnList->ulPlmnNum > ulListNumMax)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_DeletePlmnFromPlmnList:List num or ulListNumMax is err!!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_DeletePlmnFromPlmnList_ENUM,LNAS_ERROR);
        return;
    }

    /* ��ɾ����PLMN���б��в�ɾ�� */
    ulFound                             = VOS_FALSE;
    for (i=0; i<pstPlmnList->ulPlmnNum; i++)
    {
        if (VOS_FALSE == ulFound)
        {
            if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnMatch( pstPlmnId, &pstPlmnList->astPlmnId[i]))
            {
                ulFound = VOS_TRUE;
            }
        }
        if ( (VOS_TRUE == ulFound) && (i < (ulListNumMax-1)) )
        {
            NAS_LMM_PlmnCpy(&(pstPlmnList->astPlmnId[i]),
                           &(pstPlmnList->astPlmnId[i+1]));
        }
    }

    /* ��ɾ����PLMN�ڵ�ǰ�б���,�б��������һ�� */
    if (VOS_TRUE == ulFound)
    {
        pstPlmnList->ulPlmnNum--;
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PlmnIsUndef
 Description     : �ж�PLMN�Ƿ�û�ж���
 Input           : NAS_MM_PLMN_ID_STRU *pstPlmnId
 Output          : VOS_VOID
 Return          : VOS_TRUE--û�ж���,PLMN��Ч;
                   VOS_FALSE--����,PLMN��Ч;
 History         :
     1.luojian 00107747      2008-10-11  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_PlmnIsUndef(const NAS_MM_PLMN_ID_STRU *pstPlmnId)
{
    if (VOS_NULL_PTR == pstPlmnId)
    {
        return VOS_TRUE;
    }

    /* ����ָ��ǿռ�� */
    if ( (0xff == pstPlmnId->aucPlmnId[0])
       &&(0xff == pstPlmnId->aucPlmnId[1])
       &&(0xff == pstPlmnId->aucPlmnId[2])
       )
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 Function Name   : NAS_LMM_TacIsInvalid
 Description     : �ж�TAC�Ƿ���Ч
 Input           : NAS_MM_PLMN_ID_STRU *pstPlmnId
 Output          : VOS_VOID
 Return          : VOS_TRUE--û�ж���,TAC��Ч;
                   VOS_FALSE--����TAC��Ч;
 History         :
     1.leili 00132387      2012-5-9  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_TacIsInvalid(const NAS_MM_TAC_STRU *pstTac)
{
    /* ����ָ��ǿռ�� */
    if (VOS_NULL_PTR == pstTac)
    {
        return VOS_TRUE;
    }

    if ((0xff == pstTac->ucTac)
       &&(0xfe == pstTac->ucTacCnt))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


/*****************************************************************************
 Function Name   : NAS_LMM_PlmnIsUndef
 Description     : �ж�PLMN�Ƿ�û�ж���
 Input           : NAS_MM_PLMN_ID_STRU *pstPlmnId
 Output          : VOS_VOID
 Return          : VOS_TRUE--û�ж���,PLMN��Ч;
                   VOS_FALSE--����,PLMN��Ч;
 History         :
     1.luojian 00107747      2008-10-11  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_PlmnIsUnexist(const NAS_MM_PLMN_ID_STRU *pstPlmnId)
{
    if (VOS_NULL_PTR == pstPlmnId)
    {
        return VOS_TRUE;
    }

    /* ����ָ��ǿռ�� */
    if ( (0x00== pstPlmnId->aucPlmnId[0])
       &&(0x00 == pstPlmnId->aucPlmnId[1])
       &&(0x00 == pstPlmnId->aucPlmnId[2])
       )
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


/*****************************************************************************
 Function Name   : NAS_LMM_UndefPlmn
 Description     : ����PLMN��Ч
 Input           : NAS_MM_PLMN_ID_STRU *pstPlmnId
 Output          : NAS_MM_PLMN_ID_STRU *pstPlmnId
 Return          : VOS_VOID
 History         :
     1.luojian 00107747      2008-10-11  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_UndefPlmn
(
    NAS_MM_PLMN_ID_STRU                 *pstPlmnId
)
{
    /* ����ָ��ǿռ�� */
    if (VOS_NULL_PTR == pstPlmnId)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_UndefPlmn: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UndefPlmn_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstPlmnId->aucPlmnId[0]             = 0xff;
    pstPlmnId->aucPlmnId[1]             = 0xff;
    pstPlmnId->aucPlmnId[2]             = 0xff;

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_UndefTac
 Description     : ����PLMN��Ч
 Input           : NAS_MM_TAC_STRU *pstPlmnId
 Output          : NAS_MM_TAC_STRU *pstPlmnId
 Return          : VOS_VOID
 History         :
     1.leili 00132387      2012-5-8  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_UndefTac
(
    NAS_MM_TAC_STRU                 *pstTac
)
{
    /* ����ָ��ǿռ�� */
    if (VOS_NULL_PTR == pstTac)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_UndefTac: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UndefTac_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstTac->ucTac                       = 0xff;
    pstTac->ucTacCnt                    = 0xfe;

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_UndefTac
 Description     : �ж�TAC�Ƿ�û�ж���
 Input           : NAS_MM_TAC_STRU *pstTac
 Output          : VOS_VOID
 Return          : VOS_TRUE--û�ж���,TAC��Ч;
                   VOS_FALSE--����,TAC��Ч;
 History         :
     1.leili 00132387      2012-5-15  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_LMM_TacIsUnexist
(
    const NAS_MM_TAC_STRU                 *pstTac
)
{
    if (VOS_NULL_PTR == pstTac)
    {
        return VOS_TRUE;
    }

    /* ����ָ��ǿռ�� */
    if((0x00 == pstTac->ucTac) &&
        (0x00 == pstTac->ucTacCnt))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 Function Name   : NAS_LMM_CheckPlmnIsInvalid
 Description     : �ж�PLMN��MCC��MNC�Ƿ���Ч
 Input           : NAS_MM_PLMN_ID_STRU                 *pstPlmnId
 Output          : VOS_VOID
 Return          : VOS_TRUE--��Ч;
                   VOS_FALSE--��Ч;
 History         :
     1.leili 00132387      2012-5-15  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_LMM_CheckPlmnIsInvalid
(
    const NAS_MM_PLMN_ID_STRU                 *pstPlmnId
)
{
    VOS_UINT8                           ucMccDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucMccDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucMccDigit3 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit1 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit2 = NAS_LMM_NULL;
    VOS_UINT8                           ucMncDigit3 = NAS_LMM_NULL;
    VOS_UINT32                          ulMccMatchRslt;
    VOS_UINT32                          ulMncMatchRslt;

    if (VOS_NULL_PTR == pstPlmnId)
    {
        return VOS_TRUE;
    }

    /* ȡ��MCC */
    NAS_LMM_GetMccFromPlmn(pstPlmnId,&ucMccDigit1,&ucMccDigit2,&ucMccDigit3);

    /* ȡ��MNC */
    NAS_LMM_GetMncFromPlmn(pstPlmnId,&ucMncDigit1,&ucMncDigit2,&ucMncDigit3);

    ulMccMatchRslt = NAS_LMM_CheckMccIsValid(ucMccDigit1,ucMccDigit2,ucMccDigit3);

    ulMncMatchRslt = NAS_LMM_CheckMncIsValid(ucMncDigit1,ucMncDigit2,ucMncDigit3);

    if ((VOS_FALSE == ulMccMatchRslt) ||
        (VOS_FALSE == ulMncMatchRslt))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 Function Name   : NAS_LMM_CheckMccIsValid
 Description     : �ж�MCCֵ�Ƿ���Ч
 Input           :  VOS_UINT8   ucMcc1
                    VOS_UINT8   ucMcc2
                    VOS_UINT8   ucMcc3
 Output          : VOS_VOID
 Return          : VOS_TRUE--��Ч;
                   VOS_FALSE--��Ч;
 History         :
     1.leili 00132387      2012-5-15  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_LMM_CheckMccIsValid
(
    VOS_UINT8   ucMcc1,
    VOS_UINT8   ucMcc2,
    VOS_UINT8   ucMcc3
)
{
    VOS_UINT32                          ulRslt = VOS_FALSE;

    if ((ucMcc1 <= NAS_LMM_DEC_DIGIT_9) &&
        (ucMcc2 <= NAS_LMM_DEC_DIGIT_9) &&
        (ucMcc3 <= NAS_LMM_DEC_DIGIT_9))
    {
        ulRslt = VOS_TRUE;
    }

    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_LMM_CheckMncIsValid
 Description     : �ж�MCCֵ�Ƿ���Ч
 Input           :  VOS_UINT8   ucMnc1
                    VOS_UINT8   ucMnc2
                    VOS_UINT8   ucMnc3
 Output          : VOS_VOID
 Return          : VOS_TRUE--��Ч;
                   VOS_FALSE--��Ч;
 History         :
     1.leili 00132387      2012-5-15  Draft Enact

*****************************************************************************/
VOS_UINT32    NAS_LMM_CheckMncIsValid
(
    VOS_UINT8   ucMnc1,
    VOS_UINT8   ucMnc2,
    VOS_UINT8   ucMnc3
)
{
    VOS_UINT32                          ulRslt = VOS_FALSE;

    if ((ucMnc1 <= NAS_LMM_DEC_DIGIT_9) &&
        (ucMnc2 <= NAS_LMM_DEC_DIGIT_9) &&
        ((ucMnc3 <= NAS_LMM_DEC_DIGIT_9) || (ucMnc3 == NAS_LMM_HEX_DIGIT_F)))
    {
        ulRslt = VOS_TRUE;
    }

    return ulRslt;
}




/*****************************************************************************
 Function Name   : NAS_LMM_ClearPlmnList
 Description     : ���PLMN�б�
 Input           : NAS_MM_PLMN_LIST_STRU  *pstPlmnList
 Output          : NAS_MM_PLMN_LIST_STRU  *pstPlmnList
 Return          : VOS_VOID
 History         :
     1.luojian 00107747      2008-10-13  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_ClearPlmnList(NAS_MM_PLMN_LIST_STRU  *pstPlmnList)
{

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ClearPlmnList: is entered !!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ClearPlmnList_ENUM,LNAS_ENTRY);

     /* ����ָ��ǿռ�� */
    if (VOS_NULL_PTR == pstPlmnList)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_ClearPlmnList: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_ClearPlmnList_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstPlmnList->ulPlmnNum            = 0;

    NAS_LMM_MEM_SET_S(  pstPlmnList->astPlmnId,
                        NAS_MM_MAX_PLMN_NUM * sizeof(NAS_MM_PLMN_ID_STRU),
                        0,
                        NAS_MM_MAX_PLMN_NUM * sizeof(NAS_MM_PLMN_ID_STRU));

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_ClearTaList
 Description     : ���PLMN�б�
 Input           : NAS_MM_TA_LIST_STRU  *pstTaList
 Output          : NAS_MM_TA_LIST_STRU  *pstTaList
 Return          : VOS_VOID
 History         :
     1.leili 00132387      2009-05-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_ClearTaList(NAS_MM_FORB_TA_LIST_STRU  *pstTaList)
{

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ClearTaList: is entered !!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ClearTaList_ENUM,LNAS_ENTRY);

     /* ����ָ��ǿռ�� */
    if (VOS_NULL_PTR == pstTaList)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_ClearTaList: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_ClearTaList_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(pstTaList,sizeof(NAS_MM_FORB_TA_LIST_STRU),0,sizeof(NAS_MM_FORB_TA_LIST_STRU));

    return;
}


VOS_UINT32  NAS_LMM_CheckWhetherAllBytesAreFF(  const VOS_UINT8 *pucSimRecord,
                                                            const VOS_UINT32 ulIndex,
                                                            const VOS_UINT32 ulLen )
{
    VOS_UINT32                          i;

    if ((VOS_NULL_PTR == pucSimRecord) || (VOS_NULL == ulLen))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckWhetherAllBytesAreFF: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckWhetherAllBytesAreFF_ENUM,LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    for (i = 0; i< ulLen; i++)
    {
        if ( NAS_LMM_HEX_DIGIT_FF != pucSimRecord[ulIndex + i])
        {
            /* ������ڲ�Ϊ0xFF,����ʧ�� */
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 Function Name   : NAS_LMM_CheckWhetherAnyByteIsFF
 Description     : �鿴Sim�������Ƿ����0xFF
                   ��������򷵻�VOS_TRUE�����򷵻�VOS_FALSE
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00159566      2010-7-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_CheckWhetherAnyByteIsFF(   const VOS_UINT8 *pucSimRecord,
                                                            const VOS_UINT32 ulIndex,
                                                            const VOS_UINT32 ulLen)
{
    VOS_UINT32                          i;

    if ((VOS_NULL_PTR == pucSimRecord) || (VOS_NULL == ulLen))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckWhetherAnyByteIsFF: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckWhetherAnyByteIsFF_ENUM,LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    for (i = 0; i < ulLen; i++)
    {
        if ( NAS_LMM_HEX_DIGIT_FF == pucSimRecord[ulIndex + i])
        {
            return VOS_TRUE;
        }
    }

    /*���������0xff,����VOS_FALSE*/
    return VOS_FALSE;

}


VOS_VOID NAS_LMM_SetArrayAllBytesFF( VOS_UINT8 *pucArray,
                                              const VOS_UINT32 ulLen )
{
    VOS_UINT32                          i;

    if ((VOS_NULL_PTR == pucArray) || (VOS_NULL == ulLen))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckWhetherAnyByteIsFF: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SetArrayAllBytesFF_ENUM,LNAS_NULL_PTR);
        return ;
    }

    for (i = 0; i < ulLen; i++)
    {
        pucArray[i] = NAS_LMM_HEX_DIGIT_FF;
    }

    return;
}



VOS_UINT32  NAS_LMM_CheckSimRecordHeadValid( const VOS_UINT8 *pucSimRecord,
                                                          const VOS_UINT32 ulIndex,
                                                          const VOS_UINT32 ulLen )
{
    VOS_UINT32                        ulRslt;

    ulRslt =  NAS_LMM_CheckWhetherAnyByteIsFF( pucSimRecord, ulIndex, ulLen);

    if (VOS_FALSE == ulRslt)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}



VOS_UINT32  NAS_LMM_CheckSecuAlgValid( VOS_UINT8 ucSecuAlg)
{
    VOS_UINT8                    ucEncAlg;
    VOS_UINT8                    ucIntAlg;

    ucEncAlg = (ucSecuAlg & NAS_EMM_HIGH_HALF_BYTE_F) >> NAS_EMM_MOVEMENT_4_BITS;
    ucIntAlg = ucSecuAlg & NAS_EMM_LOW_HALF_BYTE_F;

    if ( (NAS_LMM_NVIM_ALG_VALID_IE < ucEncAlg)||(NAS_LMM_NVIM_ALG_VALID_IE < ucIntAlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}


VOS_UINT32  NAS_LMM_CheckModifyT3402DefaultValue( VOS_VOID)
{
    NAS_MM_PLMN_ID_STRU                *pstPresentPlmnId = NAS_EMM_NULL_PTR;

    pstPresentPlmnId = NAS_LMM_GetEmmInfoPresentPlmnAddr();

    if ((NAS_EMM_AD_BIT_SLCT == NAS_LMM_GetEmmInfoOpLastRegPlmn())
        && (NAS_LMM_MATCH_FAIL == NAS_LMM_PlmnMatch(pstPresentPlmnId, NAS_LMM_GetEmmInfoLastRegPlmnAddr())))
    {
        if ((NAS_EMM_AD_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
            && (NAS_LMM_MATCH_FAIL == NAS_LMM_PlmnIDMatchPlmnList(pstPresentPlmnId, NAS_LMM_GetEmmInfoNetInfoEplmnListAddr())))
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;

}

/*****************************************************************************
 Function Name   : NAS_LMM_UndefPlmn
 Description     : ����csgid��Ч
 Input           :
 Output          :
 Return          : VOS_VOID
 History         :
     1.yanglei 00307272      2015-10-20  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_UndefCsgId
(
    VOS_UINT32             *pulCsgId
)
{
    /* ����ָ��ǿռ�� */
    if (VOS_NULL_PTR == pulCsgId)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_UndefCsgId: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UndefCsgId_ENUM,LNAS_NULL_PTR);
        return;
    }

    *pulCsgId = 0xffffffff;

    return;
}
#if(FEATURE_ON == FEATURE_CSG)

/*****************************************************************************
 Function Name   : NAS_LMM_IsCsgCampOn
 Description     : �ж��Ƿ�CSGפ��
 Input           : VOS_VOID
 Output          :
 Return          :
 History         :
     1.yanglei 00307272      2015-10-21  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_IsCsgCampOn( VOS_VOID )
{
    NAS_MM_CELL_TYPE_ENUM_UINT8         ucCellType;

    ucCellType = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()->ucCellType;


    if((NAS_MM_CELL_TYPE_CSG == ucCellType)
        ||(NAS_MM_CELL_TYPE_HYBRID == ucCellType))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsCsgCampOn:CSG Camp On.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_IsCsgCampOn_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_YES;
    }
    else
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsCsgCampOn:CSG Not Camp On.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_IsCsgCampOn_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_NO;
    }
}

/*****************************************************************************
 Function Name   : NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList
 Description     : �ж�CSGID�Ƿ���CSG LIST�б���
 Input           : VOS_VOID
 Output          :

 Return          : ����룬��NAS_LMM_MATCH_RESULT_ENUM_UINT32����
 History         :
     1.yanglei 00307272      2015-09-24  Draft Enact

*****************************************************************************/
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList
(
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU  *pstAllowedCsgList,
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU  *pstOperatorCsgList
)
{
    VOS_UINT8                           i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32    ulMatchResult;
    NAS_MM_PLMN_ID_STRU                *pstPlmnId;
    NAS_MM_PLMN_ID_STRU                 stPlmnIdInList;
    VOS_UINT32                          ulCsgId;

    /* �ж��Ƿ�ָ��� */
    if ((VOS_NULL_PTR == pstAllowedCsgList)
       ||(VOS_NULL_PTR == pstOperatorCsgList))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList: ERR--input NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MATCH_PTR_NULL;
    }

    ulCsgId                             = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()->ulCsgId;
    pstPlmnId                           = NAS_EMM_GLO_AD_GetPresPlmnIdAddr();
    ulMatchResult                       = NAS_LMM_MATCH_FAIL;

    NAS_LMM_PUBM_LOG1_INFO("DTS_CSGID: ",  ulCsgId);
    TLPS_PRINT2LAYER_INFO1( NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList_ENUM,
                            LNAS_FUNCTION_LABEL1,
                            ulCsgId);

    /* ƥ��CSG�б� */
    for (i=0; i<pstAllowedCsgList->ulPlmnWithCsgIdListNum; i++)
    {

        NAS_LMM_PUBM_LOG1_INFO("LIST_CSGID: ", pstAllowedCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId);

        TLPS_PRINT2LAYER_INFO1( NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList_ENUM,
                                LNAS_FUNCTION_LABEL2,
                                pstAllowedCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId);

        /* ת��PLMN��ʽ */
        NAS_LMM_ConvertGuPlmnToLteFormat(   &pstAllowedCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.stPlmnId,
                                            &stPlmnIdInList);

        if (( ulCsgId == pstAllowedCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId)
            &&(pstPlmnId->aucPlmnId[0] == stPlmnIdInList.aucPlmnId[0])
            &&(pstPlmnId->aucPlmnId[1] == stPlmnIdInList.aucPlmnId[1])
            &&(pstPlmnId->aucPlmnId[2] == stPlmnIdInList.aucPlmnId[2]))
        {
            ulMatchResult               = NAS_LMM_MATCH_SUCCESS;

            /* �����һ��ƥ��ɹ�����������ѭ�� */
            return ulMatchResult;
        }
    }
    for (i=0; i<pstOperatorCsgList->ulPlmnWithCsgIdListNum; i++)
    {

        NAS_LMM_PUBM_LOG1_INFO("LIST_CSGID: ", pstOperatorCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId);

        TLPS_PRINT2LAYER_INFO1( NAS_LMM_CsgIdMatchAllowedOrOperatorCsgList_ENUM,
                                LNAS_FUNCTION_LABEL3,
                                pstOperatorCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId);
        /* ת��PLMN��ʽ */
        NAS_LMM_ConvertGuPlmnToLteFormat(   &pstOperatorCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.stPlmnId,
                                            &stPlmnIdInList);

        if (( ulCsgId == pstOperatorCsgList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.ulCsgId)
            &&(pstPlmnId->aucPlmnId[0] == stPlmnIdInList.aucPlmnId[0])
            &&(pstPlmnId->aucPlmnId[1] == stPlmnIdInList.aucPlmnId[1])
            &&(pstPlmnId->aucPlmnId[2] == stPlmnIdInList.aucPlmnId[2]))
        {
            ulMatchResult           = NAS_LMM_MATCH_SUCCESS;

            /* �����һ��ƥ��ɹ�����������ѭ�� */
            break;
        }
    }
    return ulMatchResult;

}

/*****************************************************************************
 Function Name   : NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId
 Description     : �ж�CSG ID�Ƿ���ϴγ��Ե���ͬ
 Input           : VOS_VOID
 Output          :
 Return          : ����룬NAS_EMM_SUCC or NAS_EMM_FAIL
 History         :
     1.yanglei 00307272      2015-10-21  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId( VOS_VOID )
{
    VOS_UINT32                          ulCurCsgId;
    NAS_MM_CSG_INFO_STRU               *pstLastAttmpRegCsgInfo;
    NAS_MM_PLMN_ID_STRU                *pstPlmnId;
    NAS_MM_PLMN_ID_STRU                *pstLastAttmpPlmnId;


    ulCurCsgId                          = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()->ulCsgId;
    pstLastAttmpRegCsgInfo              = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegCsgInfoAddr();
    pstPlmnId                           = NAS_LMM_GetEmmInfoPresentPlmnAddr();
    pstLastAttmpPlmnId                  = NAS_LMM_GetEmmInfoLastAttmpRegPlmnAddr();

    /* �ɺ�С����CSGС����CSG ID����LIST��ֱ�ӷ���TAU */
    if(NAS_MM_CELL_TYPE_MACRO == pstLastAttmpRegCsgInfo->ucCellType)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId: Last camp on macro.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_NO;
    }

    if((ulCurCsgId == pstLastAttmpRegCsgInfo->ulCsgId)
        &&(pstPlmnId->aucPlmnId[0] == pstLastAttmpPlmnId->aucPlmnId[0])
        &&(pstPlmnId->aucPlmnId[1] == pstLastAttmpPlmnId->aucPlmnId[1])
        &&(pstPlmnId->aucPlmnId[2] == pstLastAttmpPlmnId->aucPlmnId[2]))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId: equal last attempt register CSG ID.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_YES;
    }
    else
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId: not equal last attempt register CSG ID.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_NO;
    }
}
#endif
/*****************************************************************************
 Function Name   : NAS_LMM_ConvertGuPlmnToLteFormat
 Description     : ��GU PLMN��ʽת��LNAS�ĸ�ʽ
 Input           : VOS_VOID
 Output          :

 Return          :
 History         :
     1.yanglei 00307272      2015-10-28  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_ConvertGuPlmnToLteFormat
(
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn,
    NAS_MM_PLMN_ID_STRU                *pstLNasPlmn
)
{
    pstLNasPlmn->aucPlmnId[0]
      = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMcc);
    pstLNasPlmn->aucPlmnId[0]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMcc) >> 4);

    pstLNasPlmn->aucPlmnId[1]
     = (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMcc) >> 16);

    pstLNasPlmn->aucPlmnId[1]
     |= (VOS_UINT8)((0x000F0000 & pstGUNasPlmn->ulMnc) >> 12);

    pstLNasPlmn->aucPlmnId[2]
     = (VOS_UINT8)(0x0000000F & pstGUNasPlmn->ulMnc);
    pstLNasPlmn->aucPlmnId[2]
     |= (VOS_UINT8)((0x00000F00 & pstGUNasPlmn->ulMnc) >> 4);

    return;

}


/*****************************************************************************
 Function Name   : LMM_Get3402TimerLen
 Description     : �ṩ���ⲿ�ӿڻ�ȡ3402��ʱ��ʱ��
 Input           : VOS_VOID
 Output          : VOS_VOID

 Return          : VOS_UINT32              3402��ʱ��ʱ��
 History         :
     1.leixiantiao 00258641      2015-12-10  Draft Enact

*****************************************************************************/
VOS_UINT32  LMM_Get3402TimerLen(VOS_VOID)
{
    return NAS_EMM_GetEmmInfoDamParaT3402Len();
}

/*****************************************************************************
 Function Name   : NAS_LMM_PUBM_SecuMemCpy
 Description     : ��ȫmemcpy
 Input           : VOS_VOID* pDst, VOS_UINT32 ulMaxBuffer, const VOS_VOID* pSrc,
                   VOS_UINT32  ulLength, VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID
 Output          : None
 Return          : VOS_INT32

 History         :
    1.z00297373    2015-12-28  Draft Enact
*****************************************************************************/
VOS_INT32 NAS_LMM_PUBM_SecuMemCpy
(
    VOS_VOID            * pDst,
    VOS_UINT32          ulMaxBuffer,
    const VOS_VOID      * pSrc,
    VOS_UINT32          ulLength,
    VOS_UINT32          ulLineNO,
    VOS_UINT32          ulFileID
)
{
    /*���Դ��ַ��Ŀ�ĵ�ַ�ص��������TLPS_MEM_MOVE_S������ȫ����ʧ�� */
    if(((pSrc > pDst) && ((VOS_UINT8 *)pSrc <= ((VOS_UINT8 *)pDst + ulMaxBuffer)))
        ||((pDst> pSrc) && ((VOS_UINT8 *)pDst <= ((VOS_UINT8 *)pSrc + ulLength)))
        || (pSrc == pDst))
    {
        return TLPS_MEM_MOVE_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
    else
    {
        return TLPS_MEM_CPY_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
}


/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

