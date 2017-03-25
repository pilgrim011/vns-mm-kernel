/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasEmmcPublic.c
  Description     : EMMCģ��Ĺ�������
  History         :
     1.lining 00141619       2008-10-9   Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEmmcPublic.h"
#include  "NasEmmcSendMsg.h"
#include  "NasLmmPubMOm.h"
#include  "NasLmmPubMTimer.h"
/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMCPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMCPUBLIC_C
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
/* ȫ�ֱ���g_stEmmcGlobalCtrl�Ķ��� */
NAS_EMMC_GLOBAL_STRU                    g_stEmmcGlobalCtrl;

NAS_EMMC_GU_SYS_INFO_STRU               g_stEmmcGuSysInfo;


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_EMMC_FillRrcNasForbTaList
 Description     : ����NAS_RRC�ӿڽṹ����ֹTA�б�
 Input           : RRC_NAS_FORB_TA_LIST_STRU           *pstRrcNasForbTaList
 Output          : RRC_NAS_FORB_TA_LIST_STRU           *pstRrcNasForbTaList
 Return          : VOS_VOID
 History         :
     1.luojian 00107747      2008-10-10  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_FillRrcNasForbTaList
(
    LRRC_LNAS_FORB_TA_LIST_STRU           *pstRrcNasForbTaList
)
{
    VOS_UINT32                          i = 0;
    NAS_MM_TA_LIST_STRU                *pstForbTaListForRoaming = NAS_EMMC_NULL_PTR;

    /*get ForbTaListForRoaming and ForbTaListForRpos*/
    pstForbTaListForRoaming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);

    /* Fill ForbTaListForRoaming */
    /* ����Del Forb��ʱ���ж�, ����ʱ�����е�ʱ�Ű�Roaming�б����RRC, ��ֹ��ʱ������ֹͣ����֪ͨRRC��
        �����޶�ʱ����������TA�޷����, ����������ڸ�LRRC��������Ϣ���Forb�б�ʱ���� */
    if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_DEL_FORB_TA_PROID))
    {
        for ( i=0; i < pstForbTaListForRoaming->ulTaNum; i++)
        {
            pstRrcNasForbTaList->astForbTa[i].stTac.ucTac
                = pstForbTaListForRoaming->astTa[i].stTac.ucTac;
            pstRrcNasForbTaList->astForbTa[i].stTac.ucTacCont
                = pstForbTaListForRoaming->astTa[i].stTac.ucTacCnt;
            pstRrcNasForbTaList->astForbTa[i].stPlmnId.aucPlmnId[0]
                = pstForbTaListForRoaming->astTa[i].stPlmnId.aucPlmnId[0];
            pstRrcNasForbTaList->astForbTa[i].stPlmnId.aucPlmnId[1]
                = pstForbTaListForRoaming->astTa[i].stPlmnId.aucPlmnId[1];
            pstRrcNasForbTaList->astForbTa[i].stPlmnId.aucPlmnId[2]
                = pstForbTaListForRoaming->astTa[i].stPlmnId.aucPlmnId[2];
        }

        /*caculate forbidden TA num*/
        pstRrcNasForbTaList->ulTaNum  = pstForbTaListForRoaming->ulTaNum ;
    }
    else
    {
        if (0 < pstForbTaListForRoaming->ulTaNum)
        {
            NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_FillRrcNasForbTaList TI_NAS_EMM_STATE_DEL_FORB_TA_PROID Not Running");
        }
    }

    /* ����ʱ�б��гͷ���ʱ�������е�TA�����б��� */
    NAS_LMM_FillTempTaInRrcNasForbTaList(pstRrcNasForbTaList);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_FillUserSpecRrcNasForbTaList
 Description     : �û�ָ������ʱ����·���RRC�Ľ�ֹTA�б�
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-11-15  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_EMMC_FillUserSpecRrcNasForbTaList
(
    const NAS_MM_PLMN_ID_STRU  *pstPlmnId,
    NAS_MM_TA_LIST_STRU  *pstTaList
)
{

    NAS_MM_TA_LIST_STRU                *pstForbTaListForRoaming = NAS_EMMC_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU           *pstNetInfo = NAS_EMMC_NULL_PTR;
    VOS_UINT32                          i = 0;
    VOS_UINT32                          j = 0;

    if ((NAS_EMMC_NULL_PTR == pstPlmnId) ||
        (NAS_EMMC_NULL_PTR == pstTaList))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMMC_FillUserSpecRrcNasForbTaList: Input is Null");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_FillUserSpecRrcNasForbTaList_ENUM
,LNAS_NULL_PTR);
        return;
    }

    /*get ForbTaListForRoaming and ForbTaListForRpos*/
    pstForbTaListForRoaming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);
    pstNetInfo = (VOS_VOID*)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_NET_INFO);
    for (i = 0; i < pstForbTaListForRoaming->ulTaNum; i++)
    {
        if (NAS_LMM_MATCH_SUCCESS != NAS_LMM_PlmnMatch(pstPlmnId,&pstForbTaListForRoaming->astTa[i].stPlmnId))
        {
            NAS_LMM_MEM_CPY_S(  &pstTaList->astTa[j],
                                sizeof(NAS_MM_TA_STRU),
                                &pstForbTaListForRoaming->astTa[i],
                                sizeof(NAS_MM_TA_STRU));
            j++;

        }

    }
    pstTaList->ulTaNum = j;

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMMC_FillUserSpecRrcNasForbTaList:Rej15 TA NUM =, ",
                                   pstNetInfo->stForbTaForRej15.ulTaNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_FillUserSpecRrcNasForbTaList_ENUM
,LNAS_FUNCTION_LABEL1,
                                   pstNetInfo->stForbTaForRej15.ulTaNum);

    for(i = 0; i < pstNetInfo->stForbTaForRej15.ulTaNum; i++ )
    {

       NAS_LMM_AddTaInTaList(   &pstNetInfo->stForbTaForRej15.astTa[i],
                                pstTaList,
                                NAS_LMM_MAX_FORBTA_NUM);
    }

    NAS_LMM_FillUserSpecRrcNasForbTaListWithTempTa(pstPlmnId, pstTaList);

    NAS_EMM_PUBU_LOG1_NORM("NAS_EMMC_FillUserSpecRrcNasForbTaList:RRC FORB TA NUM =, ",
                                       pstTaList->ulTaNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_FillUserSpecRrcNasForbTaList_ENUM
,LNAS_FUNCTION_LABEL2,
                                   pstTaList->ulTaNum);
    return;
}



/*****************************************************************************
 Function Name   : NAS_EMMC_GetCurrentTa
 Description     : ��ȡ��ǰTAs
 Input           : NAS_MM_TA_STRU pstTa
 Output          : None
 Return          : VOS_VOID

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_GetCurrentTa( NAS_MM_TA_STRU *pstTa )
{
    NAS_MM_NETWORK_ID_STRU              *pstAreaInfo;

    if (NAS_EMMC_NULL_PTR == pstTa)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_GetCurrentTa:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_GetCurrentTa_ENUM
,LNAS_NULL_PTR);
        return;
    }
    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    NAS_LMM_PlmnCpy(&(pstTa->stPlmnId), &pstAreaInfo->stPlmnId);

    pstTa->stTac.ucTac                  = pstAreaInfo->stTac.ucTac;

    pstTa->stTac.ucTacCnt               = pstAreaInfo->stTac.ucTacCnt;

    return;
}



VOS_VOID  NAS_EMMC_GetForbPlmnInfo
(
    NAS_MM_PLMN_LIST_STRU               *pstFPlmn,
    NAS_MM_PLMN_LIST_STRU               *pstFPlmnForGprs
)
{
    MMC_LMM_PUB_INFO_STRU               stFPlmnInfo;
    MMC_LMM_PUB_INFO_STRU               stFPlmnForGprsInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulErrInd;

    if ((NAS_EMMC_NULL_PTR == pstFPlmn) ||
        (NAS_EMMC_NULL_PTR == pstFPlmnForGprs))
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_GetForbPlmnInfo:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_GetForbPlmnInfo_ENUM
,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET_S(&stFPlmnInfo,sizeof(MMC_LMM_PUB_INFO_STRU),0,sizeof(MMC_LMM_PUB_INFO_STRU));
    NAS_LMM_MEM_SET_S(&stFPlmnForGprsInfo,sizeof(MMC_LMM_PUB_INFO_STRU),0,sizeof(MMC_LMM_PUB_INFO_STRU));

    /*��ȡ��ֹPLMN*/
    ulErrInd = NAS_EMM_GetGulPubInfo(MMC_LMM_FPLMN,&stFPlmnInfo);

    if (MMC_LMM_SUCC != ulErrInd)
    {
        NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_GetCurrentForbInfo: FPLMN Invalid");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_GetForbPlmnInfo_ENUM
,LNAS_FUNCTION_LABEL1);
    }

    /*��ȡ��ֹPLMN for GPRS*/
    ulErrInd = NAS_EMM_GetGulPubInfo(MMC_LMM_FPLMN_FOR_GPRS,&stFPlmnForGprsInfo);

    if (MMC_LMM_SUCC != ulErrInd)
    {
        NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_GetCurrentForbInfo: FPLMN FOR GRPS Invalid");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_GetForbPlmnInfo_ENUM
,LNAS_FUNCTION_LABEL2);
    }
    NAS_LMM_PlmnListCpy(pstFPlmn, (NAS_MM_PLMN_LIST_STRU *)&(stFPlmnInfo.u.stForbiddenPlmnList));
    NAS_LMM_PlmnListCpy(pstFPlmnForGprs, (NAS_MM_PLMN_LIST_STRU *)&(stFPlmnForGprsInfo.u.stForbiddenPlmnListForGPRS));

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMMC_GetCurrentForbInfo
 Description     : ��ȡ��ǰ�����ֹ��Ϣ
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2008-10-16  Draft Enact
    2.leili   00132387      2011-02-25  Modify EMMC����

*****************************************************************************/
VOS_VOID NAS_EMMC_GetCurrentForbInfo
(
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  *pulForbdInfo
)
{
    NAS_MM_NETWORK_ID_STRU              *pstAreaInfo;
    NAS_MM_PLMN_LIST_STRU               stForbPlmn;
    NAS_MM_PLMN_LIST_STRU               stForbPlmnForGprs;
    NAS_MMC_TA_LIST_STRU                *pstForbTaForRoming;
    NAS_MMC_TA_LIST_STRU                *pstForbTaForRegional;
    NAS_MMC_TA_STRU                     stTa;

    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbdInfo;

    if (NAS_EMMC_NULL_PTR == pulForbdInfo)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_GetCurrentForbInfo:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_GetCurrentForbInfo_ENUM
,LNAS_NULL_PTR);
        return;
    }

    ulForbdInfo                         = EMMC_EMM_NO_FORBIDDEN;
    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    NAS_LMM_MEM_SET_S(&stForbPlmn,sizeof(NAS_MM_PLMN_LIST_STRU),0,sizeof(NAS_MM_PLMN_LIST_STRU));
    NAS_LMM_MEM_SET_S(&stForbPlmnForGprs,sizeof(NAS_MM_PLMN_LIST_STRU),0,sizeof(NAS_MM_PLMN_LIST_STRU));

    NAS_EMMC_GetForbPlmnInfo(&stForbPlmn,&stForbPlmnForGprs);

    pstForbTaForRoming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);
    pstForbTaForRegional = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS);

    NAS_EMMC_GetCurrentTa(&stTa);

    if (NAS_LMM_MATCH_SUCCESS ==
           NAS_LMM_PlmnIDMatchPlmnList(&pstAreaInfo->stPlmnId, &stForbPlmn))
    {
        ulForbdInfo                     = EMMC_EMM_FORBIDDEN_PLMN;
    }
    else if (NAS_LMM_MATCH_SUCCESS ==
            NAS_LMM_PlmnIDMatchPlmnList(&pstAreaInfo->stPlmnId,&stForbPlmnForGprs))
    {
        ulForbdInfo                     = EMMC_EMM_FORBIDDEN_PLMN_FOR_GPRS;
    }
    else if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(&stTa, pstForbTaForRoming))
    {
        ulForbdInfo                     = EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING;
    }
    else if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(&stTa, pstForbTaForRegional))
    {
        ulForbdInfo                     = EMMC_EMM_FORBIDDEN_TA_FOR_RPOS;
    }
    else if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTempTaListWithForbTimerRunning(&stTa))
    {
        /* ��TA��Gradul Forb��ʱ�б���, �ҳͷ���ʱ��������, �򱻽� */
        ulForbdInfo                     = EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING;
    }
    else
    {
    }

    *pulForbdInfo                       = ulForbdInfo;

    return;


}


/*****************************************************************************
 Function Name   : NAS_LMM_IsCellStatusNormal
 Description     : �ж�С��״̬�Ƿ�ΪNORMAL
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010      2014-01-23  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_LMM_IsCellStatusNormal
(
    MMC_LMM_PLMN_ID_STRU               *pstPlmn,
    const   NAS_MM_TA_STRU             *pstTa
)
{
    const NAS_MM_TA_LIST_STRU          *pstForbTaListForRoaming = VOS_NULL_PTR;
    const NAS_MM_TA_LIST_STRU          *pstForbTaListForRpos = VOS_NULL_PTR;
    MMC_LMM_PLMN_CTRL_ENUM_UINT32       ulPlmnCtrl;
    NAS_MML_SIM_TYPE_ENUM_UINT8         ucSimType;
    ucSimType = NAS_EMM_GetSimType();

    pstForbTaListForRoaming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);
    pstForbTaListForRpos = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS);
    ulPlmnCtrl = Nas_PlmnIdIsForbid(pstPlmn);
    if ((NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
        &&(NAS_LMM_SIM_VALID == NAS_LMM_GetPsSimValidity())
        &&(NAS_MML_SIM_TYPE_USIM == ucSimType)
        &&(MMC_LMM_PLMN_ALLOW_REG == ulPlmnCtrl)
        &&(NAS_LMM_MATCH_FAIL == NAS_LMM_TaMatchTaList(pstTa, pstForbTaListForRoaming))
        &&(NAS_LMM_MATCH_FAIL == NAS_LMM_TaMatchTaList(pstTa, pstForbTaListForRpos))
        &&(NAS_LMM_MATCH_FAIL == NAS_LMM_TaMatchTempTaListWithForbTimerRunning(pstTa)))
    {
        return VOS_TRUE;
    }
    NAS_LMM_SndOmAnyCellJudgingInfo(ucSimType, ulPlmnCtrl, pstTa);
    return VOS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_ProcessMmcLteSysInfoInd
 Description     : RRCϵͳ��Ϣ�ϱ�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2008-10-16  Draft Enact
    2.Date         : 2009/5/7
      Author       : lining 00141619
      Modification : ���ⵥBA8D01630
                     �޸���MMC��RRCϵͳ��Ϣ�Ĵ���
    3.Date         : 2009/5/20
      Author       : lining 00141619
      Modification : ���ⵥBN8D00126
                     �����˵�����PLMN LIST��ʼ��
    4.Date         : 2009/7/22
      Author       : zhengjunyan 00148421
      Modification : 24301_CR97
                     �Ƚ�ϵͳ��Ϣ�뵱ǰ������Ϣ����ȡ��Ϣ�仯�����
    5.Date         : 2011/02/25
      Author       : leili 00132387
      Modification : EMMC����
    6.Date         : 2012/12/17
      Author       : lihong00150010
      Modification : Emergency
    7.Date         : 2012/12/22
      Author       : lihong 00150010
      Modification : DTS2012121306127��ϵͳ��Ϣ���Ʊ��
*****************************************************************************/
VOS_VOID  NAS_EMMC_ProcessMmcLteSysInfoInd
(
    const MMC_LMM_SYS_INFO_STRU        *pstLteInfoIndMsg,
    EMMC_EMM_CHANGE_INFO_ENUM_UINT32   *pulChangeInfo,
    EMMC_EMM_CELL_STATUS_ENUM_UINT32   *penCellStatus,
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 *penForbdInfo
)
{
    EMMC_EMM_CHANGE_INFO_ENUM_UINT32    ulChangeInfo = EMMC_EMM_NO_CHANGE;
    NAS_MM_NETWORK_ID_STRU             *pstAreaInfo;
    NAS_LMM_NETWORK_INFO_STRU           *pstNetInfo;
    NAS_MM_TA_STRU                      stTa;
    EMMC_EMM_CELL_STATUS_ENUM_UINT32    enCellStatus = EMMC_EMM_CELL_STATUS_NORMAL;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 enForbdInfo = EMMC_EMM_NO_FORBIDDEN;

    NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoInd_ENUM
,LNAS_ENTRY);

    pstNetInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_NET_INFO);

    pstNetInfo->bitOpPresentNetId = NAS_EMMC_BIT_SLCT;

    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);


    /*�Ƚ�ϵͳ��Ϣ��UEά���ĵ�ǰ������Ϣ,��ȡ��Ϣ�������*/
    if(NAS_LMM_MATCH_FAIL ==
            NAS_LMM_PlmnMatch(&(pstAreaInfo->stPlmnId),
                (NAS_MM_PLMN_ID_STRU *)pstLteInfoIndMsg->stSpecPlmnIdList.astSuitPlmnList))
    {
        ulChangeInfo                    = EMMC_EMM_CHANGE_PLMN;
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoInd: MMC_EMM_CHANGE_PLMN");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoInd_ENUM
,LNAS_FUNCTION_LABEL1);

        NAS_EMMC_SendEsmPlmnChangeInd();
    }
    else if(NAS_LMM_MATCH_FAIL ==
                NAS_LMM_TacMatch(&(pstAreaInfo->stTac),
                    (NAS_MM_TAC_STRU *)&(pstLteInfoIndMsg->stTac)))
    {
        ulChangeInfo                    = EMMC_EMM_CHANGE_TA;
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoInd: MMC_EMM_CHANGE_TA");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoInd_ENUM,LNAS_FUNCTION_LABEL2);
    }
    else if (pstAreaInfo->ulCellId != pstLteInfoIndMsg->ulCellId)
    {
        ulChangeInfo                    = EMMC_EMM_CHANGE_CELL;
    }
    else
    {
        ulChangeInfo                    = EMMC_EMM_NO_CHANGE;
    }


    NAS_LMM_PlmnCpy(&pstAreaInfo->stPlmnId,
            (NAS_MM_PLMN_ID_STRU *)&pstLteInfoIndMsg->stSpecPlmnIdList.astSuitPlmnList[0]);


    pstAreaInfo->stTac.ucTac            = pstLteInfoIndMsg->stTac.ucTac;
    pstAreaInfo->stTac.ucTacCnt         = pstLteInfoIndMsg->stTac.ucTacCnt;

    pstAreaInfo->ulCellId               = pstLteInfoIndMsg->ulCellId;
    /* ����Forbidden Plmn&Ta ��Ϣ */
    NAS_EMMC_SndOmLogForbiddenInfo();
    /* ��ȡ��ֹ��Ϣ */
    if (NAS_EMMC_USER_SPEC_PLMN_YES == NAS_EMMC_GetUserSpecPlmnFlag())
    {
       enForbdInfo =  EMMC_EMM_NO_FORBIDDEN;
    }
    else
    {
        NAS_EMMC_GetCurrentForbInfo(&enForbdInfo);
    }

    pstAreaInfo->ulForbiddenInfo = enForbdInfo;

/* s00193151 mod for GU NAS LAU ֹͣT3212��ʱ�������� begin */
    pstAreaInfo->ulCellStatus = pstLteInfoIndMsg->enCellStatusInd;
    enCellStatus              = pstLteInfoIndMsg->enCellStatusInd;

    NAS_LMM_MEM_CPY_S(  pstAreaInfo->aulLteBand,
                        sizeof(LTE_BAND_STRU),
                        pstLteInfoIndMsg->stLteBand.aulLteBand,
                        sizeof(LTE_BAND_STRU));

    /*update the bitOp for AreaInfo*/
    pstAreaInfo->bitOpCellId            = NAS_EMMC_BIT_SLCT;
    pstAreaInfo->bitOpPlmnId            = NAS_EMMC_BIT_SLCT;
    pstAreaInfo->bitOpTac               = NAS_EMMC_BIT_SLCT;
    pstAreaInfo->bitOpLteBand           = NAS_EMMC_BIT_SLCT;

    /* ��ǰTA���ھܾ�ԭ��12��TA�ڣ���¼��ǣ����ڷ���״̬�ϱ� */
    NAS_EMM_GetCurrentTa(&stTa);
    /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
/* s00193151 mod for GU NAS LAU ֹͣT3212��ʱ�������� end */

    *pulChangeInfo                      = ulChangeInfo;
    *penForbdInfo                       = enForbdInfo;
    *penCellStatus                      = enCellStatus;

    pstAreaInfo->ulArfcn                 = pstLteInfoIndMsg->ulArfcn;
#if (FEATURE_ON == FEATURE_CSG)
    pstAreaInfo->ucCellType             = pstLteInfoIndMsg->enCellType;
    pstAreaInfo->ulCsgId                = pstLteInfoIndMsg->ulCsgId;
#endif
}

/*****************************************************************************
 Function Name   : NAS_EMMC_DeleteForbTa
 Description     : ɾ��һ����ֹTA
 Input           : NAS_MM_PLMN_ID_STRU stPlmnId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.luojian 00107747      2008-10-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_DeleteForbTa
(
    const NAS_MM_TA_STRU               *pstTa,
    NAS_MM_TA_LIST_STRU                *pstTaList
)
{
    NAS_LMM_DeleteTaFromTaList(pstTa, pstTaList, NAS_EMMC_MAX_FORBTA_NUM);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMMC_UpdateForbTaList
 Description     : TAI List�����仯�������µ�TAI Listˢ��ForbTa for Roaming
                   ��ForbTA for RPOS�б����ForbTA for Roaming�����仯������Ϣ
                   ֪ͨRRC��
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-8-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMMC_UpdateForbTaList( VOS_VOID )
{
    NAS_MM_TA_LIST_STRU                         *pstCurTaiList           = VOS_NULL_PTR;
    NAS_MM_TA_LIST_STRU                         *pstForbTaListForRoaming = VOS_NULL_PTR;
    NAS_MM_TA_LIST_STRU                         *pstForbTaListForRpos    = VOS_NULL_PTR;
    VOS_UINT32                                  ulPriForbTaNum           = 0;
    VOS_UINT32                                  i                        = 0;
    NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 enUpdateResult           = NAS_EMM_GRADUAL_FORB_TA_LIST_NOT_CHANGED;
    /* ����ǽ���ע������л��߽���ע�ᣬ����Ҫ��TAI LIST�е�TA�ӱ���TA�б�
       ��ɾ�� */
    if ((NAS_LMM_REG_STATUS_EMC_REGING  == NAS_LMM_GetEmmInfoRegStatus())
        || (NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus()))
    {
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_UpdateForbTaList:EMC REGED OR EMC REGING!");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_UpdateForbTaList_ENUM
,LNAS_FUNCTION_LABEL1);
        return ;
    }

    /*��ȡ��ǰ��TAI List,ForTA for Roaming,ForbTA for RPOS*/
    pstCurTaiList = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_TA_LIST);
    pstForbTaListForRoaming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);
    pstForbTaListForRpos = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS);

    /* ������ʱForb�б� */
    enUpdateResult = NAS_LMM_UpdateGradualForbTempTaList();

    /*���� ForbTA for Roaming,����仯֪ͨRRC*/
    if(0 != pstForbTaListForRoaming->ulTaNum)
    {
        ulPriForbTaNum = pstForbTaListForRoaming->ulTaNum;
        for(i = 0; i < pstCurTaiList->ulTaNum; ++i)
        {
            if(NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(&(pstCurTaiList->astTa[i]),
                                                              pstForbTaListForRoaming))
            {
                NAS_EMMC_DeleteForbTa(&(pstCurTaiList->astTa[i]),pstForbTaListForRoaming);
            }
        }
        /* Roam ForbTA����Temp Forb���������仯, ֪ͨRRC */
        if((ulPriForbTaNum != pstForbTaListForRoaming->ulTaNum)
            || (NAS_EMM_GRADUAL_FORB_TA_LIST_CHANGED == enUpdateResult))
        {
            NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);

        }
    }
    else
    {
        /* Roam ForbTA����û�仯, ������ʱ�б�����б仯, Ҳ��Ҫ֪ͨRRC */
        if(NAS_EMM_GRADUAL_FORB_TA_LIST_CHANGED == enUpdateResult)
        {
            NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
        }
    }

    /*���� ForbTA for RPOS,����仯֪ͨRRC*/
    if(0 != pstForbTaListForRpos->ulTaNum)
    {
        for(i = 0; i < pstCurTaiList->ulTaNum; ++i)
        {
            if(NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(&(pstCurTaiList->astTa[i]),
                                                              pstForbTaListForRpos))
            {
                NAS_EMMC_DeleteForbTa(&(pstCurTaiList->astTa[i]),pstForbTaListForRpos);
            }
        }
    }
    /* ��FORB TA LISTΪ��ʱ,ֹͣForb��ʱ�� */
    if((NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_DEL_FORB_TA_PROID))
        &&(0 == pstForbTaListForRoaming->ulTaNum)
        &&(0 == pstForbTaListForRpos->ulTaNum))
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_DEL_FORB_TA_PROID);
    }
    NAS_LMM_EMMC_LOG1_INFO("NAS_EMMC_UpdateForbTaList:ForbTA for RPOS NUM: New :",
                           pstForbTaListForRpos->ulTaNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_UpdateForbTaList_ENUM
,LNAS_FUNCTION_LABEL2,
                           pstForbTaListForRpos->ulTaNum);

    return;
}


VOS_VOID  NAS_EMMC_DeleteCurrentAreaCellId( VOS_VOID )
{
    NAS_MM_NETWORK_ID_STRU              *pstAreaInfo;

    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    /* С������Чȡֵ��ΧΪ0~504 ,��С��ID����Ϊ��Ч */
    pstAreaInfo->ulCellId               = NAS_EMMC_INVALID_CELLID;
}


/*****************************************************************************
 Function Name   : NAS_EMMC_ProcessRrcAreaLostInd
 Description     : С������������ʧ�ϱ�����
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2008-10-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_ProcessRrcAreaLostInd(VOS_VOID)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_ProcessRrcAreaLostInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessRrcAreaLostInd_ENUM
,LNAS_ENTRY);

    /*�ϱ���������ʧ�ؼ��¼�*/
    NAS_LMM_SendOmtKeyEvent(MM_KEY_EVENT_COVERAGE_LOST);

    /* ɾ����ǰС�� */
    NAS_EMMC_DeleteCurrentAreaCellId();

    return;
}


VOS_VOID NAS_EMMC_ProcessRrcNotCampOnInd(VOS_VOID)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_ProcessRrcNotCampOnInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessRrcNotCampOnInd_ENUM
,LNAS_ENTRY);

    /* ����Not Camp On��ʶ */
    NAS_EMMC_SetNotCampOnFlag(VOS_TRUE);

    /*�ϱ���������ʧ�ؼ��¼�*/
    /* NAS_LMM_SendOmtKeyEvent(MM_KEY_EVENT_COVERAGE_LOST); */

    /* ɾ����ǰС�� */
    /* NAS_EMMC_DeleteCurrentAreaCellId(); */

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_IsBgListSearch
 Description     : �ж��Ƿ���б���LIST��
 Input           : ulSearchType   �����·�����������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuhua 00212067      2013-02-02  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMMC_IsBgListSearch(MMC_LMM_PLMN_SRCH_TYPE_ENUM_UINT32 ulSearchType)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_IsBgListSearch is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_IsBgListSearch_ENUM
,LNAS_ENTRY);

    /**
     * ֻ�е�:
     *   - �·���������ΪLIST�ѣ���
     *   - ��״̬��ΪNO_CELL��    ��
     *   - û���յ���Not Camp On��Ϣ
     * ʱ������������Ǳ���LIST��
     */
    if ((MMC_LMM_PLMN_SRCH_LIST == ulSearchType) &&
        (EMM_SS_DEREG_NO_CELL_AVAILABLE != NAS_LMM_GetEmmCurFsmSS()) &&
        (EMM_SS_REG_NO_CELL_AVAILABLE   != NAS_LMM_GetEmmCurFsmSS()) &&
        (VOS_FALSE == NAS_EMMC_GetNotCampOnFlag()))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


/*****************************************************************************
 Function Name   : NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID
 Description     : RRCϵͳ��Ϣ�ϱ�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.z00179470            2011-08-01   Draft Enact
    2.lihong 00150010      2012-12-22   Modify:DTS2012121306127��ϵͳ��Ϣ���Ʊ��

*****************************************************************************/
VOS_VOID  NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID
(
    const MMC_LMM_SYS_INFO_STRU          *pstLteInfoIndMsg,
    VOS_UINT32                           *pulChangeInfo
)
{
    VOS_UINT32                          ulChangeInfo = NAS_EMMC_NULL;
    NAS_MM_NETWORK_ID_STRU             *pstAreaInfo;
    NAS_LMM_NETWORK_INFO_STRU          *pstNetInfo;

    NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID_ENUM
,LNAS_ENTRY);

    pstNetInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_NET_INFO);

    pstNetInfo->bitOpPresentNetId = NAS_EMMC_BIT_SLCT;

    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);


    /*�Ƚ�ϵͳ��Ϣ��UEά���ĵ�ǰ������Ϣ,��ȡ��Ϣ�������*/
    if(NAS_LMM_MATCH_FAIL ==
            NAS_LMM_PlmnMatch(&(pstAreaInfo->stPlmnId),
                (NAS_MM_PLMN_ID_STRU *)pstLteInfoIndMsg->stSpecPlmnIdList.astSuitPlmnList))
    {
        ulChangeInfo = ulChangeInfo | NAS_EMMC_BIT_SLCT;
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID: MMC_EMM_CHANGE_PLMN");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID_ENUM
,LNAS_FUNCTION_LABEL1);
    }
    if(NAS_LMM_MATCH_FAIL ==
                NAS_LMM_TacMatch(&(pstAreaInfo->stTac),
                    (NAS_MM_TAC_STRU *)&(pstLteInfoIndMsg->stTac)))
    {
        ulChangeInfo = ulChangeInfo | (NAS_EMMC_BIT_SLCT << 1);
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID: MMC_EMM_CHANGE_TA");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID_ENUM
,LNAS_FUNCTION_LABEL2);
    }
    if (pstAreaInfo->ulCellId != pstLteInfoIndMsg->ulCellId)
    {
        ulChangeInfo  = ulChangeInfo | (NAS_EMMC_BIT_SLCT << 2);
        NAS_LMM_EMMC_LOG_INFO("NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID: MMC_EMM_CHANGE_CELLID");
        TLPS_PRINT2LAYER_INFO(NAS_EMMC_ProcessMmcLteSysInfoIndTaOrCellID_ENUM
,LNAS_FUNCTION_LABEL3);
    }

    *pulChangeInfo                      = ulChangeInfo;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_GetUserSpecPlmnFlag
 Description     : ��ȡ�û�ָ��������ʶ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-11-15  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMMC_GetUserSpecPlmnFlag(VOS_VOID)
{
    NAS_EMMC_GLOBAL_STRU               *pstEmmcInfo;
    NAS_EMMC_USER_SPEC_PLMN_FLAG_UINT32  ulUserFlag;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    ulUserFlag = pstEmmcInfo->enUserSpecPlmnFlag;

    return ulUserFlag;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_SetUserSpecPlmnFlag
 Description     : �����û�ָ��������ʶ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-11-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMMC_SetUserSpecPlmnFlag(NAS_EMMC_USER_SPEC_PLMN_FLAG_UINT32  ulUserFlag)
{
    NAS_EMMC_GLOBAL_STRU               *pstEmmcInfo;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    pstEmmcInfo->enUserSpecPlmnFlag = ulUserFlag;

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_AddPlmnInRej18PlmnList
 Description     : �ѵ�ǰPLMN���뵽�ܾ�#18��PLMN�б���
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-12-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMMC_AddPlmnInRej18PlmnList(const NAS_MM_PLMN_ID_STRU *pstPlmnId)
{
    NAS_EMMC_GLOBAL_STRU                *pstEmmcInfo;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    NAS_LMM_AddPlmnInPlmnList(  pstPlmnId,
                                &pstEmmcInfo->stRej18PlmnList,
                                NAS_MM_MAX_PLMN_NUM);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_PlmnMatchRej18PlmnList
 Description     : �ж������PLMN�Ƿ��ھܾ�#18PLMN�б���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-12-16  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMMC_PlmnMatchRej18PlmnList
(
    NAS_MM_PLMN_ID_STRU *pstPlmnId
)
{
    NAS_EMM_REJ_FLAG_ENUM_UINT32        ulRslt = NAS_EMM_REJ_NO;
    NAS_EMMC_GLOBAL_STRU                *pstEmmcInfo;

    (void)pstPlmnId;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    ulRslt = NAS_LMM_PlmnIDMatchPlmnList(pstPlmnId,&pstEmmcInfo->stRej18PlmnList);

    if (NAS_LMM_MATCH_SUCCESS == ulRslt)
    {
        ulRslt = NAS_EMM_REJ_YES;
    }

    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_SetRejCause18Flag
 Description     : ���õ�ǰPLMN�ھܾ�#18PLMN�б��еı�ʶ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-12-19  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_SetRejCause18Flag
(
    NAS_EMM_REJ_FLAG_ENUM_UINT32 ulRej18Flag
)
{
    NAS_EMMC_GLOBAL_STRU                *pstEmmcInfo;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    pstEmmcInfo->ulRej18Flag = ulRej18Flag;

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMMC_GetRejCause18Flag
 Description     : ��ȡ��ǰPLMN�ھܾ�#18�б��еı�ʶ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-12-19  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMMC_GetRejCause18Flag(VOS_VOID)
{
    NAS_EMMC_GLOBAL_STRU                *pstEmmcInfo;
    NAS_EMM_REJ_FLAG_ENUM_UINT32        ulRej18Flag;

    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    ulRej18Flag =  pstEmmcInfo->ulRej18Flag;

    NAS_LMM_EMMC_LOG1_INFO("NAS_EMMC_GetRejCause18Flag: ulRej18Flag = ",
                             ulRej18Flag);
    TLPS_PRINT2LAYER_INFO1(NAS_EMMC_GetRejCause18Flag_ENUM
,LNAS_FUNCTION_LABEL1,
                             ulRej18Flag);
    return ulRej18Flag;
}
/*****************************************************************************
 Function Name   : NAS_EMMC_SndOmLogForbPlmnInfo
 Description     : ��������PLMN��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-03-18  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMMC_SndOmLogForbiddenInfo(VOS_VOID)
{
    NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU            *pstMsg = VOS_NULL_PTR;
    NAS_MM_PLMN_LIST_STRU                          stForbPlmn;
    NAS_MM_PLMN_LIST_STRU                          stForbPlmnForGprs;
    NAS_EMMC_GLOBAL_STRU                           *pstEmmcInfo;
    NAS_MM_FORB_TA_LIST_STRU                       *pstForbTaForRoming;
    NAS_MM_FORB_TA_LIST_STRU                       *pstForbTaForRegional;
    NAS_MM_FORB_TA_LIST_STRU                       *pstForbTaForRej15;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST         *pstGradualForbTaList;

    pstGradualForbTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();
    pstForbTaForRoming   = NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr();
    pstForbTaForRegional = NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr();
    pstForbTaForRej15    = NAS_LMM_GetEmmInfoNetInfoForbTaForRej15Addr();
    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    pstMsg = (NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_SndOmLogForbPlmnInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMMC_SndOmLogForbiddenInfo_ENUM
,LNAS_NULL_PTR);
        return;
    }


    NAS_LMM_MEM_SET_S(pstMsg, sizeof(NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU), 0, sizeof(NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU));
    NAS_LMM_MEM_SET_S(&stForbPlmn,sizeof(NAS_MM_PLMN_LIST_STRU),0,sizeof(NAS_MM_PLMN_LIST_STRU));
    NAS_LMM_MEM_SET_S(&stForbPlmnForGprs,sizeof(NAS_MM_PLMN_LIST_STRU),0,sizeof(NAS_MM_PLMN_LIST_STRU));

    NAS_EMMC_GetForbPlmnInfo(&stForbPlmn,&stForbPlmnForGprs);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMMC_OM_LOG_FORBIDDEN_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = ID_NAS_LMM_OM_LOG_FORBIDDEN_INFO;
    /* ���ݸ�ֵ */
    pstMsg->enUserSpecPlmnFlag = pstEmmcInfo->enUserSpecPlmnFlag;
    NAS_LMM_MEM_CPY_S(&pstMsg->stForbPlmn, sizeof(NAS_MM_PLMN_LIST_STRU), &stForbPlmn, sizeof(NAS_MM_PLMN_LIST_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stForbPlmnForGprs, sizeof(NAS_MM_PLMN_LIST_STRU), &stForbPlmnForGprs, sizeof(NAS_MM_PLMN_LIST_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stForbTaForRoam, sizeof(NAS_MM_FORB_TA_LIST_STRU), pstForbTaForRoming, sizeof(NAS_MM_FORB_TA_LIST_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stForbTaForRpos, sizeof(NAS_MM_FORB_TA_LIST_STRU), pstForbTaForRegional, sizeof(NAS_MM_FORB_TA_LIST_STRU));
    NAS_LMM_MEM_CPY_S(&pstMsg->stForbTaForRej15, sizeof(NAS_MM_FORB_TA_LIST_STRU), pstForbTaForRej15, sizeof(NAS_MM_FORB_TA_LIST_STRU));
    NAS_LMM_MEM_CPY_S(  &pstMsg->stGradualForbTaList,
                        sizeof(NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST),
                        pstGradualForbTaList,
                        sizeof(NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*lint +e961*/
/*lint +e960*/
#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 Function Name   : NAS_EMMC_IsBgCsgListSearch
 Description     : �ж��Ƿ���б���Csg LIST��
 Input           : none
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yanglei 00307272      2015-10-28  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMMC_IsBgCsgListSearch(VOS_VOID)
{
    NAS_LMM_EMMC_LOG_NORM("NAS_EMMC_IsBgCsgListSearch is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMMC_IsBgCsgListSearch_ENUM,LNAS_ENTRY);

    /**
     * ֻ�е�:
     *   - �·���������ΪLIST�ѣ���
     *   - ��״̬��ΪNO_CELL��    ��
     *   - û���յ���Not Camp On��Ϣ
     * ʱ������������Ǳ���LIST��
     */
    if ((EMM_SS_DEREG_NO_CELL_AVAILABLE != NAS_LMM_GetEmmCurFsmSS()) &&
        (EMM_SS_REG_NO_CELL_AVAILABLE   != NAS_LMM_GetEmmCurFsmSS()) &&
        (VOS_FALSE == NAS_EMMC_GetNotCampOnFlag()))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

