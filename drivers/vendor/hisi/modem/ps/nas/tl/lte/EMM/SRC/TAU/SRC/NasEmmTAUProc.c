/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : NasEmmTAUProc.c
  Description   : EMM TAU REQUEST������ش�����Դ�ļ�
  Function List :
    01.   Nas_Emm_TAU_RcvSysinfo
    02.   Nas_Emm_TAU_RcvT3412Exp
    03.   Nas_Emm_TAU_RcvT3411Exp
    04.   Nas_Emm_TAU_RcvT3402Exp
    05.   Nas_Emm_TAU_RcvT3430Exp
    06.   Nas_Emm_TAU_RcvTAUAcp
    07.   Nas_Emm_TAU_RcvTAURej
    08.   Nas_Emm_TAU_RcvRrcRelInd
    09.   Nas_Emm_TAU_RcvMrrcRelInd
    10.   Nas_Emm_TAU_RcvAppMmStopReq
    11.   Nas_Emm_TAU_RcvTAURejCause**
    12.   Nas_Emm_TAU_RcvTAURejCauseOthers
    13.   Nas_Emm_TAU_AbnormalOver
    14.   Nas_Emm_TAU_TAUStart
    15.   Nas_Emm_TAU_ReleaseRRCConnect
    16.   Nas_Emm_TAU_GetSERRejCause
  History       :
    1.  Zhouyan 00125190  2008.09.09  �¹�����
    2.  hanlufeng 41410  2009-03-11  BA8D01164 ��NAS_EMM_INFO_GUTI  �޸�Ϊ
        SERר�õĽӿ�
    3.  leili       00132387    2009.06.25   BJ9001269 �յ�ϵͳ��Ϣ�����Ż�
*******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmTauSerInclude.h"
#include  "NasLmmPubMPrint.h"
#include "NasMmlCtx.h"
#include "NasEmmAttDetInclude.h"
#include "NasLmmCore.h"
#include "LRrcLNasInterface.h"
#include "NasEmmPubUResume.h"

#include "ImsaInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMTAUPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMTAUPROC_C
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
EMM_TAU_CTRL_STRU                g_stEmmTAUCtrlTbl;



/*******************************************************************************
  Module   :
  Function : NAS_EMM_TAU_Init
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  �¹�����
*******************************************************************************/
/*lint -e589*/
/*lint -e669*/
/*lint -e831*/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_EMM_TAU_Init(VOS_VOID)
{
    NAS_EMM_TAU_LOG_NORM("NAS_EMM_TAU_Init                   START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_Init_ENUM,LNAS_ENTRY);

    /* ��ʼ��TAUȫ�ֱ��� */
    NAS_LMM_MEM_SET_S(  &g_stEmmTAUCtrlTbl,
                        sizeof(g_stEmmTAUCtrlTbl),
                        0,
                        sizeof(g_stEmmTAUCtrlTbl));

    g_stEmmTAUCtrlTbl.enEmmTauType = NAS_EMM_CN_TAU_TYPE_TA_UPDATING;

    /* ��ʼ��BAR��Ϣ*/
    NAS_EMM_ClearBarResouce();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_ClearResouce
 Description     : UEȥע�ᣬ����TAU����������Դ
                   ����ʱ��������������TAU�����ʶ���������Ż����˴����������Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2010-9-8  Draft Enact
    2.zhengjunyan 00148421 2010-10-15 Mod:ͳһ��ģ����Դ�ͷ�

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_ClearResouce( VOS_VOID )
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_ClearResouce entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ClearResouce_ENUM,LNAS_ENTRY);

    /* ��ʼ��TAUȫ�ֱ��� */
    NAS_LMM_MEM_SET_S(&g_stEmmTAUCtrlTbl, sizeof(g_stEmmTAUCtrlTbl), 0, sizeof(g_stEmmTAUCtrlTbl));

    g_stEmmTAUCtrlTbl.enEmmTauType = NAS_EMM_CN_TAU_TYPE_TA_UPDATING;

    /* �ͷŻ����ESM��Ϣ*/
    NAS_EMM_SerClearEsmDataBuf();

    /* ��ս���Bar��Ϣ*/
    NAS_EMM_ClearBarResouce();

    /*ֹͣ��ض�ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);
    NAS_LMM_Stop3402Timer();
    NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_TAU_SuspendInitClearResouce
 Description     : UE��������TAU����������Դ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY       2012-02-24  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_SuspendInitClearResouce( VOS_VOID )
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_SuspendInitClearResouce entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SuspendInitClearResouce_ENUM,LNAS_ENTRY);

    /* ��ʼ��TAUȫ�ֱ��� */
    NAS_LMM_MEM_SET_S(&g_stEmmTAUCtrlTbl, sizeof(g_stEmmTAUCtrlTbl), 0, sizeof(g_stEmmTAUCtrlTbl));

    g_stEmmTAUCtrlTbl.enEmmTauType = MMC_LMM_TA_UPDATING;

    /* �ͷŻ����ESM��Ϣ*/
    NAS_EMM_SerClearEsmDataBuf();

    /* ��ս���Bar��Ϣ*/
    NAS_EMM_ClearBarResouce();

    /*ֹͣ��ض�ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    return;
}

VOS_VOID  NAS_EMM_FreeTauDyn( VOS_VOID )
{
    /*��Ҫʱ��Ӳ���*/

    return;
}


VOS_VOID    NAS_EMM_TAUSER_FSMTranState(
                                    NAS_EMM_MAIN_STATE_ENUM_UINT16  stMS,
                                    NAS_EMM_SUB_STATE_ENUM_UINT16   stSS,
                                    NAS_EMM_STATE_TI_ENUM_UINT16    stTI

)
{

    NAS_LMM_FSM_STATE_STRU              EmmStat;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAUSER_FSMTranState is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAUSER_FSMTranState_ENUM,LNAS_ENTRY);

    EmmStat.enFsmId                   = NAS_LMM_PARALLEL_FSM_EMM;
    EmmStat.enMainState               = stMS;
    EmmStat.enSubState                = stSS;
    EmmStat.enStaTId                  = stTI;
    NAS_LMM_StaTransProc(EmmStat);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TauUpdateGutiFromCnMsg
 Description     : �յ� TAU ACP��Ϣ������ GUTI
 Input           :
 Output          :
 Return          :
 History         :
    1.leili 00132387         2008-09-09  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_TauUpdateGutiFromCnMsg(
                                const NAS_EMM_CN_TAU_ACP_STRU     *pstTAUAcp)
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TauUpdateGutiFromCnMsg is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TauUpdateGutiFromCnMsg_ENUM,LNAS_ENTRY);

    if(NAS_EMM_BIT_SLCT == pstTAUAcp->ucBitOpGuti)
    {
        NAS_LMM_GetEmmInfoUeidAddr()->bitOpGuti = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(              NAS_LMM_GetEmmInfoUeidGutiAddr() ,
                                        sizeof(NAS_EMM_GUTI_STRU),
                                        &(pstTAUAcp->stGuti),
                                        sizeof(NAS_EMM_GUTI_STRU));

    }

    return;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_TaiListSet
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  �¹�����
    2.  X00148705         2009.06.29  ����bitOpTaiList�����á�
*******************************************************************************/
VOS_VOID NAS_EMM_TAUSER_TaiListSet( const NAS_EMM_TA_LIST_STRU *pstTALIST)
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAUSER_TaiListSet is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAUSER_TaiListSet_ENUM,LNAS_ENTRY);

    /* ����TAILIST��ȫ�ֱ��� */
    NAS_LMM_MEM_CPY_S(                          &(g_stEmmInfo.stNetInfo.stTaiList),
                                                sizeof(NAS_MM_TA_LIST_STRU),
                                                pstTALIST,
                                                sizeof(NAS_EMM_TA_LIST_STRU));
    g_stEmmInfo.stNetInfo.bitOpTaiList =        NAS_EMM_BIT_SLCT;

    return;
}


NasMmIntraMsgBlock *    NAS_EMM_TAUSER_GetSendIntraMsgBuffAddr(VOS_UINT32 ulBuffSize)
{
    NasMmIntraMsgBlock *                    pIntraMsg = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAUSER_GetSendIntraMsgBuffAddr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAUSER_GetSendIntraMsgBuffAddr_ENUM,LNAS_ENTRY);

    pIntraMsg = NAS_LMM_GetSendIntraMsgBuffAddr(ulBuffSize );

    return pIntraMsg;
}


VOS_VOID* NAS_EMM_TauRsltCommProc( VOS_VOID )
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* ����MMC�ڲ���Ϣ */
    pstRsltInd  = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_TAU_RESULT_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_TauRsltCommProc: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TauRsltCommProc_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_NULL_PTR;
    }

    NAS_LMM_MEM_SET_S(  pstRsltInd,
                        sizeof(LMM_MMC_TAU_RESULT_IND_STRU),
                        0,
                        sizeof(LMM_MMC_TAU_RESULT_IND_STRU));

    /* ����MMC��DOPRAͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER(       pstRsltInd,
                                        sizeof(LMM_MMC_TAU_RESULT_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /*���OPID*/


    /* �����ϢID */
    pstRsltInd->ulMsgId                 = ID_LMM_MMC_TAU_RESULT_IND;

    /* ע��/����״̬�ϱ������Ż�:TAU �����EUֵ */
    pstRsltInd->bitOpEpsUpdateStuts     = NAS_EMM_BIT_SLCT;
    pstRsltInd->enEmmUpStat             = NAS_EMM_UPDATE_STAE;

    return pstRsltInd;
}
/*******************************************************************************
  Module   : NAS_EMM_TauRstLeadSndAttachRst
  Function :
  Input    :
  Output   :
  NOTE     : ��
  Return   : ��
  History  :
    1.  z00179470  2011.12.15  �¹�����
*******************************************************************************/
VOS_VOID NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATTACH_RSLT_ENUM_UINT32 ulAttRst)
{
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        if( (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == NAS_EMM_GLO_GetAttReqType())
          ||(MMC_LMM_ATT_REQ_TYPE_CS_PS == NAS_EMM_GLO_GetAttReqType()))
        {
           NAS_EMM_AppSendAttRstInTau(ulAttRst);
        }
    }
    return;
}
/*******************************************************************************
  Module   : NAS_EMM_TauRstSuccLeadSndAttachRst
  Function :
  Input    :
  Output   :
  NOTE     : ��
  Return   : ��
  History  :
    1.  z00179470  2011.12.15  �¹�����
*******************************************************************************/
VOS_VOID NAS_EMM_TauRstSuccLeadSndAttachRst( VOS_VOID)
{
    /* �����ATTACH�����TAU����TAU�������ϱ�ATTACH */
    if (NAS_EMM_OK == NAS_EMM_CheckAppMsgPara(ID_MMC_LMM_ATTACH_REQ))
    {
        if( (MMC_LMM_ATT_REQ_TYPE_CS_ONLY == NAS_EMM_GLO_GetAttReqType())
          ||(MMC_LMM_ATT_REQ_TYPE_CS_PS == NAS_EMM_GLO_GetAttReqType()))
        {
            /* CS_PS��TAU�ɹ�,���ؽ��Ϊ�ɹ�*/
            if( (NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED == NAS_EMM_TAU_GetEpsUpdateRslt())
              ||(NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED_AND_ISR == NAS_EMM_TAU_GetEpsUpdateRslt()))
            {
                NAS_EMM_AppSendAttRstInTau(MMC_LMM_ATT_RSLT_SUCCESS);
            }
            /* ֻ��PS�ɹ������Ϊʧ�� */
            else
            {
                NAS_EMM_AppSendAttRstInTau(MMC_LMM_ATT_RSLT_FAILURE);
            }
        }
    }
    return;
}


MMC_LMM_TAU_TYPE_ENUM_UINT32  NAS_EMM_MmcTauReqTypeInTauRslt(VOS_VOID)
{
    NAS_EMM_CN_TAU_TYPE_ENUM_UINT32     ulCnTauType;

    ulCnTauType = NAS_EMM_TAU_GetTAUtype();
    if(ulCnTauType == NAS_EMM_CN_TAU_TYPE_TA_UPDATING)
    {
        return  MMC_LMM_TA_UPDATING;
    }
    if(ulCnTauType == NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING)
    {
        return  MMC_LMM_COMBINED_TA_LA_UPDATING;
    }
    if(ulCnTauType == NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI)
    {
        return  MMC_LMM_COMBINED_TA_LA_WITH_IMSI;
    }

    if( NAS_LMM_REG_DOMAIN_PS == NAS_EMM_TAU_GetPeriodTauRegDomain())
    {
        return  MMC_LMM_PS_PERIODIC_UPDATING;
    }
    else if(NAS_LMM_REG_DOMAIN_CS_PS == NAS_EMM_TAU_GetPeriodTauRegDomain())
    {
        return  MMC_LMM_CS_PS_PERIODIC_UPDATING;
    }
    else
    {

    }

    NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcPeriodTauReqType: RegState is WRONG !!");
    TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcTauReqTypeInTauRslt_ENUM,LNAS_ERROR);
    return  MMC_LMM_TAU_TYPE_BUTT;

}


/*****************************************************************************
 Function Name   : NAS_EMM_MmcSendTauActionResultIndSucc
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-4-7  Draft Enact
    2.yanglei 00307272    2015-7-15 ����TAU,��Я��ԭ��ֵ

*****************************************************************************/
VOS_VOID  NAS_EMM_MmcSendTauActionResultIndSucc(VOS_VOID)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndSucc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndSucc_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndSucc: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndSucc_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* �����Ϣ���� */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_SUCCESS;
    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();

    pstRsltInd->bitOpCnRst              = NAS_EMM_BIT_SLCT;
    pstRsltInd->ulCnRst                 = NAS_EMM_TAU_GetEpsUpdateRslt();


    /*���EPLMN*/
    pstRsltInd->bitOpEplmn              = NAS_EMM_BIT_SLCT;
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
    {
        NAS_EMM_TAU_LOG1_INFO("NAS_EMM_MmcSendTauActionResultIndSucc: EPMN NUM ==",
                            NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcSendTauActionResultIndSucc_ENUM,LNAS_EMM_PLMN,
                            NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        NAS_LMM_MEM_CPY_S(              &pstRsltInd->stEplmnList,
                                        sizeof(MMC_LMM_EPLMN_STRU),
                                        NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                                        sizeof(MMC_LMM_EPLMN_STRU));
    }

    /*���LAI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_TAU_GetOpLai())
    {
        pstRsltInd->bitOpLai            = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(              &pstRsltInd->stLai,
                                        sizeof(MMC_LMM_LAI_STRU),
                                        NAS_EMM_TAU_GetLaiAddr(),
                                        sizeof(MMC_LMM_LAI_STRU));
    }
    /*���TMSI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_TAU_GetOpMsId())
    {
        pstRsltInd->bitOpMsIdentity           = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(              pstRsltInd->stMsIdentity.aucMsIdentity,
                                        NAS_MAX_SIZE_MS_IDENTITY,
                                        NAS_EMM_TAU_GetMsIdAddr()->aucMsId,
                                        NAS_MAX_SIZE_MS_IDENTITY);
    }
    /*�����Ϣ����----EMM CAUSE��24301 5.5.3.2�½ڶ�������TAU�����������û��Ҫ��
    ��������TAU�ɹ�ʱҪ����ԭ��ֵ�����߼��ϣ�������TAUҲ��Ӧ��Я��ԭ��ֵ��Ϊ�˷�ֹ
    GUNAS��������TAU�ɹ�ʱ������ԭ��ֵ����Ӱ�쵽CS���ע��״̬��LMM��������TAU�ɹ�
    ʱ����ʹ������Я����ԭ��ֵ��LMMҲ������GUNAS*/
    if ((NAS_EMM_BIT_SLCT == NAS_EMM_TAU_GetOpCnCause())&&
        (pstRsltInd->ulReqType != MMC_LMM_CS_PS_PERIODIC_UPDATING)&&
        (pstRsltInd->ulReqType != MMC_LMM_PS_PERIODIC_UPDATING))
    {
        NAS_EMM_ATTACH_LOG_NORM("NAS_EMM_AppSendAttSucc:EMM CAUSE");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndSucc_ENUM,LNAS_CAUSE_NUMBER);
        pstRsltInd->bitOpCnCause        = NAS_EMM_BIT_SLCT;
        pstRsltInd->ucCnCause           = NAS_EMM_TAU_GetCnCause();
    }
    /* ���TAU ATTEMPT COUTER */
    if (NAS_EMM_NULL != NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        pstRsltInd->bitOpAtmpCnt        = NAS_EMM_BIT_SLCT;
        pstRsltInd->ulAttemptCount      = NAS_EMM_TAU_GetEmmTAUAttemptCnt();
    }
    /* ����LMM_MMC_TAU_RESULT_IND��Ϣ */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    NAS_EMM_TauRstSuccLeadSndAttachRst();
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly
 Description     : ������TAU,���ֵΪTA UPDATED ONLY��ԭ��ֵΪ�������߲���ʱ����
                   MMC����TAU RESULT IND��Ϣ
 Input           : pstRsvMsg--------------TAU ACCEPT��Ϣָ��
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-08-24    Draft Enact
    2.lihong 00150010     2011-11-18    Modify
    3.sunjitan 00193151   2012-05-31  Modify     ԭ��ֵ��Ϊ#2#16#17#18#22ʱ����MMC�ϱ�ԭ��ֵ
*****************************************************************************/
VOS_VOID  NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly
(
    const VOS_VOID                     *pvTauRslt
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;
    VOS_UINT32                      ulTaRslt;

    (VOS_VOID)pvTauRslt;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* ������: ����TAU OTHERS_FAIL���� */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /* �����Ϣ���� */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_CN_REJ;
    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();

    pstRsltInd->bitOpCnRst              = NAS_EMM_BIT_SLCT;
    pstRsltInd->ulCnRst                 = NAS_EMM_TAU_GetEpsUpdateRslt();

    /*���EPLMN*/
    pstRsltInd->bitOpEplmn              = NAS_EMM_BIT_SLCT;
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoNetInfoOpEplmnListAddr())
    {
        NAS_EMM_TAU_LOG1_INFO("NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly: EPMN NUM ==",
                            NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcSendTauActionResultIndRejTaUpdatedOnly_ENUM,LNAS_EMM_PLMN,
                            NAS_LMM_GetEmmInfoNetInfoEplmnListAddr()->ulPlmnNum);
        NAS_LMM_MEM_CPY_S(              &pstRsltInd->stEplmnList,
                                        sizeof(MMC_LMM_EPLMN_STRU),
                                        NAS_LMM_GetEmmInfoNetInfoEplmnListAddr(),
                                        sizeof(MMC_LMM_EPLMN_STRU));
    }

    /*���LAI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_TAU_GetOpLai())
    {
        pstRsltInd->bitOpLai            = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(              &pstRsltInd->stLai,
                                        sizeof(MMC_LMM_LAI_STRU),
                                        NAS_EMM_TAU_GetLaiAddr(),
                                        sizeof(MMC_LMM_LAI_STRU));
    }

    /*���TMSI*/
    if (NAS_EMM_BIT_SLCT == NAS_EMM_TAU_GetOpMsId())
    {
        pstRsltInd->bitOpMsIdentity           = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY_S(              pstRsltInd->stMsIdentity.aucMsIdentity,
                                        NAS_MAX_SIZE_MS_IDENTITY,
                                        NAS_EMM_TAU_GetMsIdAddr()->aucMsId,
                                        NAS_MAX_SIZE_MS_IDENTITY);
    }

    /* ԭ��ֵ��Ϊ#2#16#17#18#22ʱ����MMC�ϱ�ԭ��ֵ */
    /*�����Ϣ����----EMM CAUSE*/
    pstRsltInd->bitOpCnCause            = NAS_EMM_BIT_NO_SLCT;
    pstRsltInd->ucCnCause               = NAS_EMM_CAUSE_BUTT;

    /* ���TAU ATTEMPT COUTER */
    if (NAS_EMM_NULL != NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        pstRsltInd->bitOpAtmpCnt        = NAS_EMM_BIT_SLCT;
        pstRsltInd->ulAttemptCount      = NAS_EMM_TAU_GetEmmTAUAttemptCnt();

        /* ���TAU���Դ���С��5����Я��EPS update status��TAI�Ƿ���TAI LIST�б�ʶ */
        if (NAS_EMM_TAU_ATTEMPT_CNT_MAX > pstRsltInd->ulAttemptCount)
        {
            pstRsltInd->bitOpEpsUpdateStuts = NAS_EMM_BIT_SLCT;
            pstRsltInd->enEmmUpStat         = NAS_EMM_UPDATE_STAE;
            pstRsltInd->bitOpTaiInListFlag  = NAS_EMM_BIT_SLCT;

            ulTaRslt                        = NAS_EMM_TAU_IsCurrentTAInTaList();
            if (NAS_EMM_SUCC == ulTaRslt)
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_IN_TAI_LIST;
            }
            else
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_NOT_IN_TAI_LIST;
            }
        }
    }

    /* ����LMM_MMC_TAU_RESULT_IND��Ϣ */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* �����ATTACH�����TAU����TAU�������ϱ�ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}


VOS_VOID  NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara( VOS_VOID )
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* �����Ϣ���� */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_SUCCESS;
    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();


    /* ����LMM_MMC_TAU_RESULT_IND��Ϣ */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* �����ATTACH�����TAU����TAU�������ϱ�ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_IsTauRejCauseOthers
 Description     : �ж�TAU REJԭ��ֵ�Ƿ�Ϊ5.5.3.2.5�½�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-11-18  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsTauRejCauseOthers
(
    VOS_UINT8                           ucCnCause
)
{
    VOS_UINT32                          ulRslt = NAS_EMM_YES;

    switch(ucCnCause)
    {
        case    NAS_LMM_CAUSE_ILLEGAL_UE   :
        case    NAS_LMM_CAUSE_ILLEGAL_ME   :
        case    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW   :
        case    NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW:
        case    NAS_LMM_CAUSE_UE_ID_NOT_DERIVED    :
        case    NAS_LMM_CAUSE_IMPLICIT_DETACHED   :
        case    NAS_LMM_CAUSE_PLMN_NOT_ALLOW    :
        case    NAS_LMM_CAUSE_TA_NOT_ALLOW   :
        case    NAS_LMM_CAUSE_ROAM_NOT_ALLOW    :
        case    NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN    :
        case    NAS_LMM_CAUSE_NO_SUITABL_CELL   :
        case    NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG   :
        case    NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED:

                ulRslt = NAS_EMM_NO;
                break;
        default :

                ulRslt = NAS_EMM_YES;
                break;
    }

    return ulRslt;
}



VOS_VOID  NAS_EMM_MmcSendTauActionResultIndRej
(
    const VOS_VOID                     *pvTauRslt
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulTaRslt = NAS_EMM_FAIL;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         ucCnCause  = NAS_EMM_CAUSE_BUTT;

    (VOS_VOID)pvTauRslt;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndRej_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndRej: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndRej_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* ������: ����TAU OTHERS_FAIL���� */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    ucCnCause                             = NAS_EMM_TAU_GetEmmTauCnRejCause();
    /* �����Ϣ���� */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_CN_REJ;
    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();


    /*���ܾ�ԭ��ֵ*/
    pstRsltInd->bitOpCnCause            = NAS_EMM_BIT_SLCT;
    pstRsltInd->ucCnCause               = ucCnCause;

    if (NAS_EMM_NULL != NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        pstRsltInd->bitOpAtmpCnt        = NAS_EMM_BIT_SLCT;
        pstRsltInd->ulAttemptCount      = NAS_EMM_TAU_GetEmmTAUAttemptCnt();

        /* ���TAU REJԭ��ֵ��Ϊ5.5.3.2.5�½����У���TAU���Դ���С��5��
           ��Я��EPS update status��TAI�Ƿ���TAI LIST�б�ʶ */
        if ((NAS_EMM_YES == NAS_EMM_IsTauRejCauseOthers(ucCnCause))
            && (NAS_EMM_TAU_ATTEMPT_CNT_MAX > pstRsltInd->ulAttemptCount))
        {
            pstRsltInd->bitOpEpsUpdateStuts = NAS_EMM_BIT_SLCT;
            pstRsltInd->enEmmUpStat         = NAS_EMM_UPDATE_STAE;
            pstRsltInd->bitOpTaiInListFlag  = NAS_EMM_BIT_SLCT;

            ulTaRslt                        = NAS_EMM_TAU_IsCurrentTAInTaList();
            if (NAS_EMM_SUCC == ulTaRslt)
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_IN_TAI_LIST;
            }
            else
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_NOT_IN_TAI_LIST;
            }
        }
    }

    /* ����LMM_MMC_TAU_RESULT_IND��Ϣ */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* �����ATTACH�����TAU����TAU�������ϱ�ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}


VOS_VOID  NAS_EMM_MmcSendTauActionResultIndTimerExp
(
    const VOS_VOID                     *pvTauRslt
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulTaRslt = NAS_EMM_FAIL;

    (VOS_VOID)pvTauRslt;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndTimerExp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndTimerExp_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndTimerExp: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndTimerExp_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* ������: ����TAU OTHERS_FAIL���� */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /* �����Ϣ���� */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_TIMER_EXP;
    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();


    /*��䳢�Դ���*/
    pstRsltInd->bitOpAtmpCnt            = NAS_EMM_BIT_SLCT;
    pstRsltInd->ulAttemptCount          = NAS_EMM_TAU_GetEmmTAUAttemptCnt();

   /* ���TAU���Դ���С��5����Я��EPS update status��TAI�Ƿ���TAI LIST�б�ʶ */
    if (NAS_EMM_TAU_ATTEMPT_CNT_MAX > pstRsltInd->ulAttemptCount)
    {
        pstRsltInd->bitOpEpsUpdateStuts = NAS_EMM_BIT_SLCT;
        pstRsltInd->enEmmUpStat         = NAS_EMM_UPDATE_STAE;
        pstRsltInd->bitOpTaiInListFlag  = NAS_EMM_BIT_SLCT;

        ulTaRslt                        = NAS_EMM_TAU_IsCurrentTAInTaList();
        if (NAS_EMM_SUCC == ulTaRslt)
        {
            pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_IN_TAI_LIST;
        }
        else
        {
            pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_NOT_IN_TAI_LIST;
        }
    }

    /* ����LMM_MMC_TAU_RESULT_IND��Ϣ */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* �����ATTACH�����TAU����TAU�������ϱ�ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_MmcSendTauActionResultIndFailWithPara
 Description     : �ײ�ʧ�ܻ������ͷţ���MMC�ظ�LMM_MMC_TAU_RESULT_IND��Ϣ��
                    ���Ϊʧ�ܣ�Я�����Դ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-4-25     Draft Enact
    2.lihong 00150010     2011-11-18    Modify

*****************************************************************************/
VOS_VOID  NAS_EMM_MmcSendTauActionResultIndFailWithPara
(
    const VOS_VOID                     *pvTauRslt
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd  = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulTaRslt = NAS_EMM_FAIL;

    (VOS_VOID)pvTauRslt;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndFailWithPara is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndFailWithPara_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndFailWithPara: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndFailWithPara_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* ������: ����TAU OTHERS_FAIL���� */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /* �����Ϣ���� */
    pstRsltInd->ulTauRst                = MMC_LMM_TAU_RSLT_FAILURE;

    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();


    if (NAS_EMM_NULL != NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        pstRsltInd->bitOpAtmpCnt        = NAS_EMM_BIT_SLCT;
        pstRsltInd->ulAttemptCount      = NAS_EMM_TAU_GetEmmTAUAttemptCnt();

        /* ���TAU���Դ���С��5����Я��EPS update status��TAI�Ƿ���TAI LIST�б�ʶ */
        if (NAS_EMM_TAU_ATTEMPT_CNT_MAX > pstRsltInd->ulAttemptCount)
        {
            pstRsltInd->bitOpEpsUpdateStuts = NAS_EMM_BIT_SLCT;
            pstRsltInd->enEmmUpStat         = NAS_EMM_UPDATE_STAE;
            pstRsltInd->bitOpTaiInListFlag  = NAS_EMM_BIT_SLCT;

            ulTaRslt                        = NAS_EMM_TAU_IsCurrentTAInTaList();
            if (NAS_EMM_SUCC == ulTaRslt)
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_IN_TAI_LIST;
            }
            else
            {
                pstRsltInd->enTaiInListFlag = MMC_LMM_TAI_NOT_IN_TAI_LIST;
            }
        }
    }

    /* ����LMM_MMC_TAU_RESULT_IND��Ϣ */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* �����ATTACH�����TAU����TAU�������ϱ�ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}



VOS_VOID  NAS_EMM_MmcSendTauActionResultIndOthertype
(
    const VOS_VOID                     *pvTauRslt
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;
    MMC_LMM_TAU_RSLT_ENUM_UINT32     ulTauRslt;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndOthertype is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndOthertype_ENUM,LNAS_ENTRY);

    ulTauRslt = *(MMC_LMM_TAU_RSLT_ENUM_UINT32*)pvTauRslt;


    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndOthertype: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndOthertype_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* ������: ����TAU OTHERS_FAIL���� */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    /* �����Ϣ���� */
    if ((MMC_LMM_TAU_RSLT_ACCESS_BARED == ulTauRslt) ||
        (MMC_LMM_TAU_RSLT_AUTH_REJ == ulTauRslt) ||
        (MMC_LMM_TAU_RSLT_FAILURE == ulTauRslt)||
        (MMC_LMM_TAU_RSLT_T3402_RUNNING == ulTauRslt)||
        (MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE == ulTauRslt)||
        (MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE == ulTauRslt)||
        (MMC_LMM_TAU_RSLT_T3402_RUNNING == ulTauRslt)||
        (MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC == ulTauRslt))
    {
        NAS_EMM_TAU_LOG1_NORM("NAS_EMM_MmcSendTauActionResultIndOthertype:ulTauRslt =",
                            ulTauRslt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcSendTauActionResultIndOthertype_ENUM,LNAS_FUNCTION_LABEL1,
                            ulTauRslt);
        pstRsltInd->ulTauRst            = ulTauRslt;
    }
    else
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndOthertype:\
                                Input TAU Result Type is err !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndOthertype_ENUM,LNAS_ERROR);
    }

    pstRsltInd->ulReqType               = NAS_EMM_MmcTauReqTypeInTauRslt();


    /* ����LMM_MMC_TAU_RESULT_IND��Ϣ */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* �����ATTACH�����TAU����TAU�������ϱ�ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MmcSendTauActionResultIndForbType
 Description     : ��MMC�ϱ���ֹ��Ϣ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2012-1-10  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MmcSendTauActionResultIndForbType
(
    const VOS_VOID                     *pvForbInfo
)
{
    LMM_MMC_TAU_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 ulForbInfo;

    ulForbInfo = *(EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32*)pvForbInfo;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MmcSendTauActionResultIndForbType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendTauActionResultIndForbType_ENUM,LNAS_ENTRY);

    pstRsltInd = NAS_EMM_TauRsltCommProc();
    if (NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndForbType: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndForbType_ENUM,LNAS_NULL_PTR);
        return;
    }
    /* ������: ����TAU OTHERS_FAIL���� */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
    NAS_EMM_TAU_LOG1_NORM("NAS_EMM_MmcSendTauActionResultIndForbType:ulForbInfo =",
                            ulForbInfo);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcSendTauActionResultIndForbType_ENUM,LNAS_EMM_FORB_INFO,
                            ulForbInfo);

    /* �����Ϣ���� */
    if (EMMC_EMM_FORBIDDEN_PLMN == ulForbInfo)
    {
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FORBID_PLMN;
    }
    else if (EMMC_EMM_FORBIDDEN_PLMN_FOR_GPRS == ulForbInfo)
    {
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS;
    }
    else if (EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING == ulForbInfo)
    {
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING;
    }
    else if (EMMC_EMM_FORBIDDEN_TA_FOR_RPOS == ulForbInfo)
    {
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS;
    }
    else if(EMMC_EMM_NO_FORBIDDEN == ulForbInfo)
    {
        /* ϵͳ��Ϣδ���������ǵ��ô˺����ϱ������һ����ANY CELL��ϵͳ��Ϣ */
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FAILURE;
    }
    else
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_MmcSendTauActionResultIndForbType:\
                                Input TAU Result Type is err !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendTauActionResultIndForbType_ENUM,LNAS_ERROR);
        pstRsltInd->ulTauRst            = MMC_LMM_TAU_RSLT_FAILURE;
    }

    pstRsltInd->ulReqType               =  NAS_EMM_MmcTauReqTypeInTauRslt();


    /* ����LMM_MMC_TAU_RESULT_IND��Ϣ */
    NAS_LMM_SendLmmMmcMsg(                    pstRsltInd);

    /* �����ATTACH�����TAU����TAU�������ϱ�ATTACH */
    NAS_EMM_TauRstLeadSndAttachRst(MMC_LMM_ATT_RSLT_FAILURE);

    return;
}


VOS_UINT32    NAS_EMM_SendIntraAttachReq(VOS_VOID)
{
    NAS_LMM_INTRA_ATTACH_REQ_STRU        *pIntraAttachReqMsg = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_SendAttachReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendIntraAttachReq_ENUM,LNAS_ENTRY);

    /* ����DOPRA��Ϣ */
    pIntraAttachReqMsg = (VOS_VOID *)NAS_EMM_TAUSER_GetSendIntraMsgBuffAddr(
                                        sizeof(NAS_LMM_INTRA_ATTACH_REQ_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    if(NAS_EMM_NULL_PTR == pIntraAttachReqMsg)
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_SendAttachReq: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendIntraAttachReq_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /* ��дNAS_EMM_INTRA_ATTACH_REQ ��DOPRA��Ϣͷ */
    EMM_COMP_MM_MSG_HEADER(pIntraAttachReqMsg, sizeof(NAS_LMM_INTRA_ATTACH_REQ_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /* ��дNAS_EMM_INTRA_ATTACH_REQ ����ϢID��ʶ */
    pIntraAttachReqMsg->ulMsgId         = ID_NAS_LMM_INTRA_ATTACH_REQ;

    /* ������Ϣ(Send the msg of) NAS_EMM_INTRA_ATTACH_REQ */
    NAS_EMM_SEND_INTRA_MSG(             pIntraAttachReqMsg);

    return NAS_EMM_SUCC;

}


/*******************************************************************************
  Module   :
  Function : Nas_Emm_TAU_AbnormalOver
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190     2008.09.17  �¹�����
    2.  zhengjunyan 00148421 2010.07.30 ���:���TauStartCasue
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_AbnormalOver( )
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_AbnormalOver is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_AbnormalOver_ENUM,LNAS_ENTRY);

    /*ֹͣT3430��ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

    /*ֹͣT3440��ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    /* �������TAU��ԭ��ֵ*/
    NAS_EMM_TAU_SaveEmmTAUStartCause(   NAS_EMM_TAU_START_CAUSE_DEFAULT);

    /* ���Tau Attempt Counter*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    return;
}

/*******************************************************************************
      Module   :
      Function : NAS_EMM_NvimSetEPSUpdataStatus
      Input    :
      Output   :
      NOTE     :
      Return   :
      History  :
        1.  Zhouyan 00125190  2008.09.17  �¹�����
*******************************************************************************/
NAS_EMM_UPDATE_STATE_ENUM_UINT8 NAS_EMM_TAU_GetEmmEPSUPState()
{
    NAS_EMM_UPDATE_STATE_ENUM_UINT8   ucupdatastate;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_GetEmmEPSUPState is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_GetEmmEPSUPState_ENUM,LNAS_ENTRY);

    ucupdatastate = NAS_EMM_TAUSER_GetAuxFsmUpStat();

    return ucupdatastate;
}



/*******************************************************************************
  Module   :
  Function : NAS_EMM_TAU_SendEsmStatusInd
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  �¹�����

*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_ENUM_UINT32  stATTACHStatus)
{


    EMM_ESM_STATUS_IND_STRU                *pstsmstatusInd            = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG1_INFO( "NAS_EMM_TAU_SendEsmStatusInd is entered.", stATTACHStatus);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_TAU_SendEsmStatusInd_ENUM,LNAS_ENTRY,stATTACHStatus);

    /* ����DOPRA��Ϣ */
    pstsmstatusInd  = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_STATUS_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstsmstatusInd)
    {
        return;
    }

    /* ����RRC��DOPRAͷ */
    EMM_COMP_ESM_MSG_HEADER(pstsmstatusInd, sizeof(EMM_ESM_STATUS_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /* �����ϢID */
    pstsmstatusInd->ulMsgId = ID_EMM_ESM_STATUS_IND;

    /* �����Ϣ���� -- stATTACHStatus */
    pstsmstatusInd->enEMMStatus = stATTACHStatus;

    /*clear global:EpsContextStatusChange*/
    if(stATTACHStatus == EMM_ESM_ATTACH_STATUS_DETACHED)
    {
        NAS_EMM_GetEpsContextStatusChange() = NAS_EMM_EPS_BEARER_STATUS_NOCHANGE;
    }

    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstsmstatusInd);

    return;

}
/*****************************************************************************
 Function Name   : NAS_EMM_TAU_GetEpsUpdateType
 Description     : ����TAU REQ��Ϣʱ����ȡEps Update Type��ֵ
 Input           : ��
 Output          : ��
 Return          : MMC_LMM_TAU_TYPE_ENUM_UINT32

 History         :
    1.lihong00150010      2011-11-18    Draft Enact

*****************************************************************************/
NAS_EMM_CN_TAU_TYPE_ENUM_UINT32 NAS_EMM_TAU_GetEpsUpdateType
(
    NAS_EMM_TAU_START_CAUSE_ENUM_UINT8      enTauStartCause
)
{
    NAS_LMM_REG_DOMAIN_ENUM_UINT32          enRegDomain     = NAS_LMM_REG_DOMAIN_BUTT;


    /* ��ȡLģע���� */
    enRegDomain = NAS_LMM_GetEmmInfoRegDomain();

    if (NAS_EMM_TAU_START_CAUSE_T3412EXP == enTauStartCause)
    {
        /* ����������TAU��ע����
            ������MMC�ϱ����ʱ������PS_PERIOD_TAU����CS_PS_PERIOD_TAU */
        NAS_EMM_TAU_SavePeriodTauRegDomain(enRegDomain);
        return  NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING;
    }

    /* �ж��Ƿ�ΪCP/PS1����CS/PS2 */
    if (NAS_EMM_NO == NAS_EMM_IsCsPsUeMode())
    {
        return  NAS_EMM_CN_TAU_TYPE_TA_UPDATING;
    }

    /* �ж��Ƿ�ԭ��ֵ2�ܾ��� */
    if (NAS_EMM_REJ_YES == NAS_LMM_GetEmmInfoRejCause2Flag())
    {
        return  NAS_EMM_CN_TAU_TYPE_TA_UPDATING;
    }

    /* �ж��Ƿ�ԭ��ֵ18�ܾ��� */
    if (NAS_EMM_REJ_YES == NAS_EMMC_GetRejCause18Flag())
    {
        return  NAS_EMM_CN_TAU_TYPE_TA_UPDATING;
    }

    /* �ж�����DETACH�Ƿ�TAU��� */
    if (NAS_EMM_COM_DET_BLO_YES == NAS_EMM_TAU_GetEmmCombinedDetachBlockFlag())
    {
        return  NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING;
    }
    /* �ж��Ƿ�����CS��ע�� */
    if (NAS_EMM_AUTO_ATTACH_NOT_ALLOW == NAS_EMM_GetCsAttachAllowFlg())
    {
        return  NAS_EMM_CN_TAU_TYPE_TA_UPDATING;
    }

    if(NAS_LMM_REG_DOMAIN_PS == enRegDomain)
    {
        return  NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI;
    }
    else if(NAS_LMM_REG_DOMAIN_CS_PS == enRegDomain)
    {
        return  NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING;
    }
    else
    {
        /* ��ӡ�쳣 */
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_TAU_GetEpsUpdateType:enRegDomain = NAS_LMM_REG_DOMAIN_NULL");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAU_GetEpsUpdateType_ENUM,LNAS_FUNCTION_LABEL1);

        return  NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_CompCnTAUReqNasMsg
 Description     : Ϊ���PC-LINT�������Խ������⣬��������һ�����CN��Ϣ�ĺ���
 Input           : pulIndex     : �������룬Ҳ�����
 Output          : pucCnNasMsg  : ָ�� LRRC_LNAS_MSG_STRU.aucNasMsg
                   pulIndex     : Ҳ����� : ����˺����е������������������ַ�
                                 ��һ�����õ��ֽ�λ�ã�
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-2-1  Draft Enact  PCLINT�޸�
    2.zhengjunyan 00148421 2009-12-09  CR39:TAU REQ��Ԫ���
    3.zhengjunyan 00148421 2010-11-23  MOD:���ⵥDTS2010101502052,Service�ɹ���
                                       ����̬������TAUϣ��Я������״̬������ͬ����
                                       ����ɾ��Я������״̬IE���ж�����:IDLE��CONN
                                       ����TAU��Я������״̬��
*****************************************************************************/
VOS_VOID    NAS_EMM_TAU_CompCnTAUReqNasMsg
(
    VOS_UINT8      *pucCnNasMsg,
    VOS_UINT32     *pulIndex
)
{
    VOS_UINT32                          ulIndex             = 0;
    VOS_UINT32                          ulIeLength          = 0;
    VOS_UINT8                           ucKsi;
    NAS_EMM_CN_TAU_TYPE_ENUM_UINT32     enTauUpdateType     = NAS_EMM_CN_TAU_TYPE_BUTT;
    NAS_EMM_TAU_START_CAUSE_ENUM_UINT8  enTauStartCause     = NAS_EMM_TAU_START_CAUSE_BUTT;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG1_INFO("NAS_EMM_TAU_CompCnTAUReqNasMsg is entered.",*pulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_TAU_CompCnTAUReqNasMsg_ENUM,LNAS_ENTRY,*pulIndex);


    /* ��� Security header type  +  Protocol Discriminator */
    pucCnNasMsg[ulIndex++]              = EMM_TAU_REQ_MSG_PD_AND_SEC_TY;

    /* ��� TAU request message identity   */
    pucCnNasMsg[ulIndex++]              = NAS_EMM_CN_MT_TAU_REQ;

    /* ��ȡTAU�������� */
    enTauStartCause = NAS_EMM_TAU_GetEmmTAUStartCause();
    enTauUpdateType = NAS_EMM_TAU_GetEpsUpdateType(enTauStartCause);
    NAS_EMM_TAU_LOG1_NORM("Tau Type: ", enTauUpdateType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_TAU_CompCnTAUReqNasMsg_ENUM,LNAS_FUNCTION_LABEL1,enTauUpdateType);
    NAS_EMM_TAU_SaveTAUtype(enTauUpdateType);

    /* ��� EPS update type */
    pucCnNasMsg[ulIndex] = (VOS_UINT8)NAS_EMM_TAU_GetTAUtype();
    pucCnNasMsg[ulIndex] |= (NAS_EMM_TAU_GetEmmTauReqActiveCtrl()&0x1f)<<3;

    /* �����ԪNAS key set identifierASME */
    ucKsi = NAS_EMM_SecuGetKSIValue();
    pucCnNasMsg[ulIndex] |= (VOS_UINT8)(ucKsi << 4);
    ulIndex++;

    /*���OLD GUTI*/
    NAS_EMM_EncodeOldGuti(              &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���Non-current native NAS key set identifier*/
    NAS_EMM_EncodeNonCurrentNativeKSI(  &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���GPRS ciphering key sequence number*/
    NAS_EMM_EncodeGprsCkSn(             &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /* ���Old P-TMSI signature*/
    NAS_EMM_EncodePtmsiSignature(       &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���Additional GUTI*/
    NAS_EMM_EncodeAdditionalGuti(       &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���NonceUE*/
    NAS_EMM_EncodeNonceUE(              &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /* ���UE network capability*/
    if((EMM_TAU_AD_BIT_SLCT == NAS_EMM_TAU_UE_NET_CAP_BIT())
        && ( NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING != NAS_EMM_TAU_GetTAUtype()))
    {
        pucCnNasMsg[ulIndex++]          = NAS_EMM_TAU_REQ_UE_NET_CAP_IEI;

        /* UE NETWORK CAPABILITY �Ǳ�ѡIE, LV��3~14*/
        NAS_EMM_EncodeUeNetCapa(        &(pucCnNasMsg[ulIndex]),
                                        NAS_LMM_IE_FORMAT_LV,
                                        &ulIeLength);
        ulIndex += ulIeLength;

    }

    /* ���Last visited registered TAI */
    NAS_EMM_EncodeLRVTai(               &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /* ��� DRX parameter */
    NAS_EMM_EncodeDrxPara(              &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_TAU_REQ);
    ulIndex                             += ulIeLength;


    /*���UE radio capability information update needed*/
    NAS_EMM_EncodeURCUpdateNeed(        &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /* ���EPS bearer context status */
    NAS_EMM_EncodeEpsBearStatus(        &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;
    /* ��� MS network capability */
    NAS_EMM_EncodeMsNetworkCapability(  &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_TAU_REQ);
    ulIndex                             += ulIeLength;


    /* ���Old location area identification */
    NAS_EMM_EncodeLai(                  &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_TAU_REQ);
    ulIndex                             += ulIeLength;


    /*���TMSI STATUS*/
    NAS_EMM_EncodeTmsiStatus(           &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_TAU_REQ);
    ulIndex                             += ulIeLength;

    /*���Mobile station classmark 2*/
    NAS_EMM_EncodeMsClassMark2(         &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength,
                                        NAS_EMM_CN_MT_TAU_REQ);
    ulIndex                             += ulIeLength;

    /*���Mobile station classmark 3*/
    NAS_EMM_EncodeMsClassMark3(         &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���Supported Codecs*/
    NAS_EMM_EncodeSupportedCodecs(      &(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;

    /*���Additional update type*/
    if ((NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING  == NAS_EMM_TAU_GetTAUtype()) ||
        (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetTAUtype()))
    {
        NAS_EMM_EncodeAdditionUpdateType(   &(pucCnNasMsg[ulIndex]),
                                            &ulIeLength);
        ulIndex                             += ulIeLength;
    }

    /*���Voice domain preference and UE's usage setting*/
    NAS_EMM_EncodeVoiceDomainAndUsageSetting(&(pucCnNasMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;
    if (NAS_RELEASE_CTRL)
    {
        /* ���Old GUTI type */
        NAS_EMM_EncodeGutiType(             &(pucCnNasMsg[ulIndex]),
                                            &ulIeLength);
        ulIndex                            += ulIeLength;
    }

    if (NAS_RELEASE_R11)
    {
        if ((NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING  == NAS_EMM_TAU_GetTAUtype()) ||
            (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetTAUtype()))
        {
            /* ���TMSI based NRI container */
            NAS_EMM_EncodeTmsiBasedNriContainer(    &(pucCnNasMsg[ulIndex]),
                                                    &ulIeLength);
            ulIndex                             += ulIeLength;
        }
    }

    *pulIndex += ulIndex;

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EncodeOldGuti
 Description     : Old GUTI���뺯��
 Input           : None
 Output          : pMsg-------------IE����
                   pulIeLength------IE����
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeOldGuti
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          ulLen = NAS_EMM_NULL;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeOldGuti: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeOldGuti_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    if(NAS_EMM_SUCC == NAS_EMM_CheckMutiModeSupport())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:SUPPORT GU MODE ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL1);
        if (MMC_LMM_TIN_P_TMSI == ulTinType)
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:TIN IS P-TMSI ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL2);
            if (NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
            {
                NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:P-TMSI AND RAI VALID ");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL3);
                NAS_EMM_CompMappedGuti(&(pucReqMsg[ulIndex]),&ulLen);
                *pulIeLength                = ulLen;
            }
        }
        else if ((MMC_LMM_TIN_GUTI == ulTinType) ||
            (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:TIN IS GUTI or RAT RELATED TMSI");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL4);
            if (NAS_EMM_BIT_SLCT == NAS_EMM_TAUSER_OP_GUTI())
            {
                NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti: NATIVE GUTI VALID");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL5);
                NAS_EMM_CompNativeGuti(&(pucReqMsg[ulIndex]),&ulLen);
                *pulIeLength            = ulLen;
            }
        }
        else
        {
            NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeOldGuti: TIN INVALID");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL6);
        }
    }
    else
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:NOT SUPPORT GU MODE ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL7);
        if (NAS_EMM_BIT_SLCT == NAS_EMM_TAUSER_OP_GUTI())
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_EncodeOldGuti:NATIVE GUTI INVALID ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeOldGuti_ENUM,LNAS_FUNCTION_LABEL8);
            NAS_EMM_CompNativeGuti(&(pucReqMsg[ulIndex]),&ulLen);
            *pulIeLength                = ulLen;
        }
    }

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_IsPtmsiAndConn
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-6-24  Draft Enact
    2.sunjitan 00193151   2012-05-24 �޸����Ӵ���ISR����̬ʱ����������

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsConnChangeToLte( VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();
    if((MMC_LMM_TIN_P_TMSI == ulTinType)
        || (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
    {   /* �մ�GU���� */

        if( (NAS_LMM_SYS_CHNG_ORI_LRRC == NAS_EMM_GetResumeOri()) &&
            (NAS_LMM_SYS_CHNG_TYPE_HO   == NAS_EMM_GetResumeType())
           )
        {   /* HO,���� */

            return  NAS_EMM_YES;
        }
    }

    return  NAS_EMM_NO;
}


/*****************************************************************************
 Function Name   : NAS_EMM_IsPtmsiAndIdle
 Description     : Ԥ����Ϊ��CCO���ض���ʱ������ڵ�䲻���ڰ�ȫ�����ĵĴ��ݣ�
                   ���CCO���ض�����IDLE����������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-6-24  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_IsPtmsiAndIdle( VOS_VOID )
{
    if(MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
    {   /* �մ�GU���� */

        if( (NAS_LMM_SYS_CHNG_ORI_LRRC == NAS_EMM_GetResumeOri()) &&
            (   (NAS_LMM_SYS_CHNG_TYPE_RSL  == NAS_EMM_GetResumeType()) ||
                (NAS_LMM_SYS_CHNG_TYPE_CCO  == NAS_EMM_GetResumeType()) ||
                (NAS_LMM_SYS_CHNG_TYPE_REDIR== NAS_EMM_GetResumeType())
            ))
        {   /* ��ѡ/CCO/�ض��� ���� */

            return  NAS_EMM_YES;
        }
        else if(NAS_LMM_SYS_CHNG_ORI_MMC == NAS_EMM_GetResumeOri())
        {   /* MMC���������� */

            return  NAS_EMM_YES;
        }
        else
        {

        }
    }

    return  NAS_EMM_NO;
}



/*****************************************************************************
 Function Name   : NAS_EMM_EncodeNonCurrentNativeKSI
 Description     : Non-current native NAS key set identifier���뺯��
 Input           : None
 Output          : pMsg-------Non-current native NAS key set identifier IE ����
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact
    2.zhengjunyan 00148421 2011-06-02 ��SECUģ���ȡ non-current KSIasme,�����Ԫ
*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeNonCurrentNativeKSI
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{
    VOS_UINT8                          *pucReqMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();

    /* ��κϷ��Լ��*/
    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeNonCurrentNativeKSI: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeNonCurrentNativeKSI_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
   *pulIeLength                         = NAS_EMM_NULL;

    /* ��������� non-current native security context,��ֱ�ӷ��أ���������Ԫ*/
    if(NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE == NAS_EMM_SecuGetNonCurKSIasme())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_EncodeNonCurrentNativeKSI: no para.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeNonCurrentNativeKSI_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /* ���Ǵ�GU����������CONNECT ̬�����Ԥ�н�������Ϊ�ض���Ҳ������̬.
    8.2.29.2    Non-current native NAS key set identifier
    The UE shall include this IE if the UE has a valid non-current native EPS
    security context when the UE performs an A/Gb mode or Iu mode to S1 mode
    inter-system change in EMM-CONNECTED mode and the UE uses a mapped EPS
    security context to protect the TRACKING AREA UPDATE REQUEST message.
    */
    if(NAS_EMM_YES == NAS_EMM_IsConnChangeToLte())
    {
        NAS_EMM_TAU_LOG2_INFO("NAS_EMM_EncodeNonCurrentNativeKSI: TinType = , ResumeType = ",
                                ulTinType,
                                NAS_EMM_GetResumeType());
        /* coverity[unchecked_value] */
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeNonCurrentNativeKSI_ENUM,LNAS_EMM_TIN_TYPE,
                                ulTinType);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_EncodeNonCurrentNativeKSI_ENUM,LNAS_EMM_RESUME_TYPE,
                                NAS_EMM_GetResumeType());

        /* ���Non-current native NAS key set identifier IEI*/
        pucReqMsg[ulIndex]              = NAS_EMM_TAU_REQ_NON_CURRENT_NATIVE_KSI;

        /* ��� Non-current native NAS key set identifier�� TSC */
        pucReqMsg[ulIndex]              |= NAS_EMM_SecuGetNonCurKSIasme();
        ulIndex++;

        /* ��Ԫ����*/
        *pulIeLength = ulIndex;
    }

    /* non-current native security context���ڣ�������Ԫ*/

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeGprsCkSn
 Description     : GPRS ciphering key sequence number���뺯��
 Input           : None
 Output          : pMsg-------------GPRS ciphering key sequence number����

 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeGprsCkSn
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT8                           ucGprsCkSn = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeGprsCkSn: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeGprsCkSn_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;

    ucGprsCkSn = (VOS_UINT8)NAS_EMM_SecuGetUmtsKsi();

    /*
    8.2.29.3    GPRS ciphering key sequence number
    The UE shall include this IE if the UE performs an A/Gb mode or Iu mode
    to S1 mode inter-system change in EMM-IDLE mode and the TIN indicates "P-TMSI"
    */
    if (NAS_EMM_YES == NAS_EMM_IsPtmsiAndIdle() )
    {
        /*���GPRS ciphering key sequence number IEI*/
        pucReqMsg[ulIndex]              = NAS_EMM_TAU_REQ_GPRS_CK_SN;

        /* ��� GPRS ciphering key sequence number�� spare */
        pucReqMsg[ulIndex]              &= NAS_EMM_TAU_REQ_IE_SPARE;

        /* ���GPRS ciphering key sequence number��key sequence */
        pucReqMsg[ulIndex]              |= ucGprsCkSn;

        ulIndex ++;
        *pulIeLength                = ulIndex;

    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeNonceUe
 Description     : Nonce UE���뺯��
 Input           : None
 Output          : pMsg-------------Nonce UE����
                   pulIeLength------Nonce UE����
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-5-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeNonceUE
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{

    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeNonceUE: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeNonceUE_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;


    /*
    8.2.29.6    NonceUE
    This IE is included if the UE performs an A/Gb mode or Iu mode to S1 mode
    inter-system change in idle mode.
    */
    if (NAS_EMM_YES == NAS_EMM_IsPtmsiAndIdle() )
    {

        /*���NONCE UE IEI*/
        pucReqMsg[ulIndex++]                = NAS_EMM_TAU_REQ_Nonce_UE_IEI;

        /* ��� NONCE UE�� VALUE */
        NAS_LMM_MEM_CPY_S(                  &pucReqMsg[ulIndex],
                                            NAS_EMM_SECU_NONCE_UE_LEN,
                                            NAS_EMM_SecuGetNonceUE(),
                                            sizeof(VOS_UINT32));

        ulIndex                             += sizeof(VOS_UINT32);

        *pulIeLength                        = ulIndex;
    }

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_EncodeURCUpdateNeed
 Description     : UE radio capability information update needed���뺯��
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387      2011-5-12  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeURCUpdateNeed
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{

    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeURCUpdateNeed: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeURCUpdateNeed_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;


    /* �������TAUʱUE��GU���������ı��ʶ�Դ��ڣ���Ӧ���URC_UPDATE_NEED
       ����UE���������ϱ�������MME��UE�����������²�ѯ */
    if(NAS_LMM_UE_RADIO_CAP_GU_CHG == NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_LMM_SetEmmInfoFirstTauFlag(NAS_EMM_FIRST_TAU);
    }


    /*if (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())*/
    if (NAS_EMM_FIRST_TAU == NAS_LMM_GetEmmInfoFirstTauFlag())
    {
        /*���UE radio capability information update needed IEI*/
        pucReqMsg[ulIndex]            = NAS_EMM_TAU_REQ_RADIO_CAP_UPDATE_NEED_IEI;

        /* ��� UE radio capability information update needed IEI��spare*/
        pucReqMsg[ulIndex]              &= NAS_EMM_TAU_REQ_IE_SPARE;

        /* ���UE radio capability information update needed IEI��update needed */
        pucReqMsg[ulIndex]              |= NAS_EMM_URC_UPDATE_NEED;

        ulIndex ++;

        *pulIeLength                        = ulIndex;

    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EncodeEpsBearStatus
 Description     : EPS BEARER STATUS���뺯��
 Input           : None
 Output          : pMsg ------EPS BEARER STATUS����
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2012-3-1  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EncodeEpsBearStatus
(
    VOS_UINT8       *pMsg,
    VOS_UINT32      *pulIeLength
)
{
    VOS_UINT8                           *pucReqMsg;
    VOS_UINT32                          ulIndex = NAS_EMM_NULL;
    VOS_UINT32                          i;
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstEpsBearerCxt;
    VOS_UINT32                          ucEpsId;
    VOS_UINT8                           ucEsmEPS1           = 0;
    VOS_UINT8                           ucEsmEPS2           = 0;

    if((VOS_NULL_PTR == pMsg) ||
        (VOS_NULL_PTR == pulIeLength))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_EncodeEpsBearStatus: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_EncodeEpsBearStatus_ENUM,LNAS_NULL_PTR);
        return;
    }

    pucReqMsg                           = pMsg;
    *pulIeLength                        = NAS_EMM_NULL;
    pstEpsBearerCxt = NAS_EMM_GetPsBearerCtx();
    pucReqMsg[ulIndex++]          = NAS_EMM_TAU_REQ_EPS_STATUS_IEI;
    pucReqMsg[ulIndex++]          = NAS_EMM_CN_EPS_CONTEXT_LEN;

    /*lint -e701*/
    for(i = 0; i < EMM_ESM_MAX_EPS_BEARER_NUM; i++)
    {
        if (NAS_MML_PS_BEARER_STATE_ACTIVE == pstEpsBearerCxt[i].enPsBearerState)
        {
            ucEpsId = i + NAS_EMM_MIN_EPS_ID;
            if( NAS_EMM_EPS_BEARER_STATUS_NUM_SEVEN < ucEpsId)
            {
                ucEpsId             = ucEpsId - NAS_EMM_EPS_BEARER_STATUS_NUM_EIGNT;
                ucEsmEPS2 = ucEsmEPS2 | NAS_EMM_TAU_ESM_BEARER_LEFT_N(ucEpsId);
            }
            else
            {
                ucEsmEPS1 = ucEsmEPS1 | NAS_EMM_TAU_ESM_BEARER_LEFT_N(ucEpsId);
            }

        }
    }
    /*lint +e701*/

    pucReqMsg[ulIndex++]                = ucEsmEPS1;
    pucReqMsg[ulIndex++]                = ucEsmEPS2;
    *pulIeLength                        = ulIndex;


    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndOmLogActiveFlagInfo
 Description     : ����TAU REQ��Ϣ��Я��ACTIVE��ʶ�������ϱ�
 Input           :
 Output          : None
 Return          : None

 History         :
    1.wangchen 00209181 2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SndOmLogActiveFlagInfo
(
    VOS_VOID
)
{
    NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_LMM_OM_LOG_ACTIVE_FLAG_INFO;

    pstMsg->enEmmCollisionCtrl          = NAS_EMM_TAU_GetEmmCollisionCtrl();

    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        pstMsg->ucEsmEmcPdnReq              = VOS_TRUE;
    }

    pstMsg->ucCsAttachAllowFlag         = NAS_EMM_GetCsAttachAllowFlg();
    pstMsg->enTmoActiveFlag             = NAS_EMM_TAU_GetEmmTmoActiveFlagCtrl();
    #if (FEATURE_ON == FEATURE_IMS)
    /* �ӿ����޸� */
    pstMsg->ucImsProcedureOngoing       = (VOS_UINT8)IMSA_IsExitImsService();
    #endif
    if (EMM_ESM_UP_SINGNAL_PENDING == NAS_ESM_IsUpSingnalPending())
    {
        pstMsg->ucUpSignalPendingFlag   = VOS_TRUE;
    }

    if (EMM_ERABM_UP_DATA_PENDING == NAS_ERABM_IsDataPending())
    {
        pstMsg->ucDataPendingFlag       = VOS_TRUE;
    }
    pstMsg->enPtmsiActiveFlag           = NAS_EMM_TAU_GetEmmPtmsiActiveFlagCtrl();

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsVoiceDomainChangeSetActFlag
 Description     : �ж��Ƿ���VoiceDomain�޸Ĵ�����TAU�Ƿ�ҪЯ��Active Flag
 Input           :
 Output          : None
 Return          : NAS_EMM_YES:��Ҫ����, NAS_EMM_NO:����Ҫ����

 History         :
    1.leixiantiao 00258641 2016-05-17  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_IsVoiceDomainChangeSetActFlag()
{
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsVoiceDomainChangeSetActFlag_ENUM,LNAS_ENTRY);

    /* ����ǰTAU����ԭ��ΪDomain Change, �ҵ�ǰΪIDLE, ������ACT Flag, ��ֹTAU���֮������
       �ͷŵ���֮������ϱ���IMSȥע��/IMS�������ȥ����/������ؼ�����Ϣ���͵����������� */
    if (NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE == NAS_EMM_TAU_GetEmmTAUStartCause()
        && (NAS_EMM_CONN_IDLE == NAS_EMM_GetConnState()))
    {
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsVoiceDomainChangeSetActFlag_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}

/*******************************************************************************
  Module   :
  Function : Nas_Emm_TAU_SendMrrcDataReq_TAUReq
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  �¹�����
    2.  X00148705         2009.09.19  �޸�DRX Length:4-->3(byte)
    3.  z00148421         2009.07.21  CR187:ֻ��SER�����д�����TAU,Я��'active'
    4.  zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,���б����Ż�
    5.  lihong 00150010   2012-12-13  Modify:Emergency

*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_SendMrrcDataReq_TAUReq(NAS_EMM_MSG_TYPE_ENUM_UINT32 ulEmmMsgType)
{
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataReqMsg    = NAS_EMM_NULL_PTR;
    VOS_UINT32                          uldataReqMsgLenNoHeader;
    VOS_UINT32                          ulIndex             =0;


    /* ��ӡ����ú����� INFO_LEVEL */
    if(NAS_EMM_MSG_LOAD_BALANCING_TAU == ulEmmMsgType)
    {
        NAS_EMM_TAU_LOG_NORM( "NAS_EMM_TAU_SendMrrcDataReq_TAUReq is entered,TAUType:NAS_EMM_MSG_LOAD_BALANCING_TAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendMrrcDataReq_TAUReq_ENUM,LNAS_FUNCTION_LABEL1);
    }
    else
    {
        NAS_EMM_TAU_LOG_NORM( "NAS_EMM_TAU_SendMrrcDataReq_TAUReq is entered,TAUType:NAS_EMM_MSG_NOT_LOAD_BALANCING_TAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendMrrcDataReq_TAUReq_ENUM,LNAS_FUNCTION_LABEL2);
    }

    /* ����NAS_MSG_STRU��Ϣ���� */


    /* �������Ϣ��������DOPRA��Ϣ */
    pMrrcDataReqMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC( NAS_EMM_INTRA_MSG_MAX_SIZE);
    if(NAS_EMM_NULL_PTR == pMrrcDataReqMsg)
    {
        return;
    }
    /* �����������Pending���ߴ���COLLISION��־����Я��'ACTIVE'��־*/
    if((NAS_EMM_UPLINK_PENDING == NAS_EMM_TAU_GetEmmUplinkPending())
     || (NAS_EMM_COLLISION_NONE != NAS_EMM_TAU_GetEmmCollisionCtrl())
     || (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
     || (NAS_EMM_TMO_ACTIVE_FLAG_CTRL_VALID == NAS_EMM_TAU_GetEmmTmoActiveFlagCtrl())
     || (NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_VALID == NAS_EMM_TAU_GetEmmPtmsiActiveFlagCtrl())
     || (NAS_EMM_YES == NAS_EMM_IsVoiceDomainChangeSetActFlag()))
    {
        NAS_EMM_TAU_SaveEmmTauReqActiveCtrl(NAS_EMM_TAU_WITH_BEARER_EST_REQ);

        NAS_EMM_SndOmLogActiveFlagInfo();
    }
    else
    {
        NAS_EMM_TAU_SaveEmmTauReqActiveCtrl(NAS_EMM_TAU_NO_BEARER_EST_REQ);
    }

    /* ����MRRC_DATA_REQ �е� NAS_MSG_STRU,��CN��Ϣ(Compose the msg of): TAU_REQ */
    NAS_EMM_TAU_CompCnTAUReqNasMsg(pMrrcDataReqMsg->stNasMsg.aucNasMsg,&ulIndex);

    NAS_EMM_TAU_SaveEmmTauImsiDetachFlag(NAS_EMM_IMSI_DETACH_INVALID);

    uldataReqMsgLenNoHeader              = EMM_COUNT_DATA_REQ_LEN(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < uldataReqMsgLenNoHeader )
    {
        /* ��ӡ������Ϣ */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_TAU_CompCnTAUReqNasMsg, Size error ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendMrrcDataReq_TAUReq_ENUM,LNAS_ERROR);

        NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
        return ;
    }

    /* ��дMRRC_DATA_REQ ��DOPRA��Ϣͷ */
    EMM_COMP_MM_MSG_HEADER(pMrrcDataReqMsg, uldataReqMsgLenNoHeader);

    /* ��дMRRC_DATA_REQ ����ϢID��ʶ */
    pMrrcDataReqMsg->ulMsgId                 = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*��� TAU_REQ_EST_CAUSE*/
    /*��� TAU_REQ_EST_CAUSE*/
    if ((NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus())
        || (NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR == NAS_LMM_GetEmmInfoRegStatus())
        || (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause()))
    {
        pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL;
        pMrrcDataReqMsg->enCallType= LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL;
    }
    else
    {
        pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
        pMrrcDataReqMsg->enCallType= LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    }
    pMrrcDataReqMsg->enEmmMsgType = ulEmmMsgType;

    pMrrcDataReqMsg->enDataCnf               = LRRC_LMM_DATA_CNF_NEED;

    /* ��дMRRC_DATA_REQ ��NAS��Ϣ���ȱ�ʶ */
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize   = ulIndex;

    /*����TAU����ʱ������״̬*/
    NAS_EMM_TAU_SaveEmmTauStartConnSta(NAS_EMM_GetConnState());

    /* ���������TAU����֪ͨMM����MM LOCATION UPDATING PENDING״̬ */
    if ((NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING == NAS_EMM_TAU_GetTAUtype())
        || (NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetTAUtype()))
    {
        NAS_EMM_SendMmCombinedStartNotifyReq(MM_LMM_COMBINED_TAU);
    }

    /*NAS_EMM_TAU_SaveEmmT3412ExpCtrl(NAS_EMM_NO);*/

    /*�տ���Ϣ�ϱ�TAU REQ*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_TAU_REQ,(NAS_MSG_STRU *)&(pMrrcDataReqMsg->stNasMsg));

    /*�ؼ��¼��ϱ�TAU REQ*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_TAU_REQ);

    /* ������Ϣ(Send the msg of) MRRC_DATA_REQ(TAU_REQ) */
    NAS_EMM_SndUplinkNasMsg(             pMrrcDataReqMsg);



    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);

    return;

}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_TAU_SendEsmBearerStatusInd
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  �¹�����
*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_SendEsmBearerStatusInd(const NAS_EMM_CN_TAU_ACP_STRU   *pMsgStru )
{
    EMM_ESM_BEARER_STATUS_IND_STRU       *psmbearerstatusind  =  NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_SendEsmBearerStatusInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendEsmBearerStatusInd_ENUM,LNAS_ENTRY);

    /* ����DOPRA��Ϣ */
    psmbearerstatusind = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_BEARER_STATUS_IND_STRU));

    if(NAS_EMM_NULL_PTR == psmbearerstatusind)
    {
        return;
    }

    /* ��дDOPRA��Ϣͷ */
    EMM_COMP_ESM_MSG_HEADER(psmbearerstatusind, sizeof(EMM_ESM_BEARER_STATUS_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /* ��д��ϢID��ʶ */
    psmbearerstatusind->ulMsgId    = ID_EMM_ESM_BEARER_STATUS_IND;

    /* ��д��ǰ�Ѽ����EPSID����  */
    psmbearerstatusind->ulEpsIdNum = pMsgStru->stEPSBearerstatus.ulEpsIdNum;

    /* ��д �����Ѽ����EPS BID  */
    NAS_LMM_MEM_CPY_S(                  &(psmbearerstatusind->aulEsmEpsId[0]),
                                        EMM_ESM_MAX_EPS_BEARER_NUM*sizeof(VOS_UINT32),
                                        &(pMsgStru->stEPSBearerstatus.aulEsmEpsId[0]),
                                        EMM_ESM_MAX_EPS_BEARER_NUM*sizeof(VOS_UINT32));


    /* ������Ϣ*/
    NAS_LMM_SEND_MSG(psmbearerstatusind);

    return;


}


VOS_VOID    NAS_EMM_TAU_SendDetachReq()
{
    NAS_LMM_INTRA_DETACH_REQ_STRU             *pIntraDetachReqMsg = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_SendDetachReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendDetachReq_ENUM,LNAS_ENTRY);

    /* ����DOPRA��Ϣ */
    pIntraDetachReqMsg = (VOS_VOID *)NAS_EMM_TAUSER_GetSendIntraMsgBuffAddr(
                                        sizeof(NAS_LMM_INTRA_DETACH_REQ_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    if(NAS_EMM_NULL_PTR == pIntraDetachReqMsg)
    {
        NAS_EMM_TAU_LOG_ERR( "Nas_Emm_Sau_SendAttachReq: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAU_SendDetachReq_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* ��дNAS_EMM_INTRA_DETACH_REQ ��DOPRA��Ϣͷ */
    EMM_COMP_MM_MSG_HEADER(pIntraDetachReqMsg, sizeof(NAS_LMM_INTRA_DETACH_REQ_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /* ��дNAS_EMM_INTRA_DETACH_REQ ����ϢID��ʶ */
    pIntraDetachReqMsg->ulMsgId                 = ID_NAS_LMM_INTRA_DETACH_REQ;

    /* ������Ϣ(Send the msg of) NAS_EMM_INTRA_DETACH_REQ */
/*    NAS_EMM_TAUSER_SendIntraMsg(pIntraDetachReqMsg);*/
    NAS_EMM_SEND_INTRA_MSG(             pIntraDetachReqMsg);

    return;
}



/*****************************************************************************
 Function Name   : Nas_Emm_TAU_CompCnTAUCmpl
 Description     :
 Input           :
 Output          :
 Return          :

 History         :
    1.zhouyan 00125190       2008-09-08  Draft Enact
    2.zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,���б����Ż�

*****************************************************************************/
VOS_VOID    NAS_EMM_TAU_CompCnTAUCmpl(LRRC_LNAS_MSG_STRU  *pNasMsg,
                                                        VOS_UINT32 *pulIndex )
{
    VOS_UINT32                          ulIndex             = 0;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_CompCnTAUCmpl is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_CompCnTAUCmpl_ENUM,LNAS_ENTRY);

    /* ��ս����CN��Ϣ�Ŀռ� */
    /* NAS_LMM_MEM_SET(pNasMsg->aucNasMsg, 0, pNasMsg->ulNasMsgSize); */

    /* ��� Skip indicator  +  Protocol Discriminator */
    pNasMsg->aucNasMsg[ulIndex++]       = EMM_CN_MSG_PD_EMM;

    /* ��� TAU CMPL message identity   */
    pNasMsg->aucNasMsg[ulIndex++]       = NAS_EMM_CN_MT_TAU_CMP;

    *pulIndex = ulIndex;

    return;

}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_TAU_SendMrrcDataReqTauCmpl
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  �¹�����
    2.  zhuyiqiang 00138739    2009-08-11  MODIFY    BJ9D01672,���б����Ż�

*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_SendMrrcDataReqTauCmpl( )
{
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataReqMsg    = NAS_EMM_NULL_PTR;
    VOS_UINT32                          uldataReqMsgLenNoHeader;
    VOS_UINT32                          ulIndex             = 0;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_SendMrrcDataReqTauCmpl is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_SendMrrcDataReqTauCmpl_ENUM,LNAS_ENTRY);


    /* ������Ϣ���� */

    pMrrcDataReqMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC( NAS_EMM_INTRA_MSG_MAX_SIZE);
    if(NAS_EMM_NULL_PTR == pMrrcDataReqMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(pMrrcDataReqMsg, NAS_EMM_INTRA_MSG_MAX_SIZE, 0, NAS_EMM_INTRA_MSG_MAX_SIZE);

    /* ����MRRC_DATA_REQ �е� NAS_MSG_STRU,��CN��Ϣ(Compose the msg of): TAU_REQ */
    NAS_EMM_TAU_CompCnTAUCmpl(            &(pMrrcDataReqMsg->stNasMsg),&ulIndex);

    uldataReqMsgLenNoHeader              = EMM_COUNT_DATA_REQ_LEN(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < uldataReqMsgLenNoHeader )
    {
        /* ��ӡ������Ϣ */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_TAU_CompCnTAUCmpl, Size error ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAU_SendMrrcDataReqTauCmpl_ENUM,LNAS_ERROR);
        NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
        return ;
    }

    /* ��дMRRC_DATA_REQ ��DOPRA��Ϣͷ */
    EMM_COMP_MM_MSG_HEADER(pMrrcDataReqMsg, uldataReqMsgLenNoHeader);

    /* ��дMRRC_DATA_REQ ����ϢID��ʶ */
    pMrrcDataReqMsg->ulMsgId            = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*��� TAU_COMPL_EST_CAUSE*/
    pMrrcDataReqMsg->enEstCaue          = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pMrrcDataReqMsg->enCallType         = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pMrrcDataReqMsg->enEmmMsgType       = NAS_EMM_MSG_TAU_CMP;

    pMrrcDataReqMsg->enDataCnf          = LRRC_LMM_DATA_CNF_NEED;

    /* ��дMRRC_DATA_REQ ��NAS��Ϣ���ȱ�ʶ */
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize   = ulIndex;

    /*�տ���Ϣ�ϱ�TAU COMPLETE*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_TAU_CMP, (NAS_MSG_STRU *)&(pMrrcDataReqMsg->stNasMsg));

    /*�ؼ��¼��ϱ�TAU COMPLETE*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_TAU_CMP);

    NAS_EMM_SndUplinkNasMsg(             pMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
    return;

}




VOS_UINT32    NAS_EMM_TAU_CHKFSMStateMsgp(
                                    NAS_EMM_MAIN_STATE_ENUM_UINT16  stMS,
                                    NAS_EMM_SUB_STATE_ENUM_UINT16   stSS,
                                    VOS_VOID   *pMsgStru)
{
    (VOS_VOID)(pMsgStru);
    if(NAS_EMM_CHK_STAT_INVALID(stMS, stSS))
    {
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMState: STATE ERR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_TAU_CHKFSMStateMsgp_ENUM,LNAS_ERROR);
        return NAS_EMM_FAIL;
    }
    if ( NAS_EMM_NULL_PTR == pMsgStru )
    {
        /* ��ӡ�쳣 */
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKMsgp: pMsgStru is NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_TAU_CHKFSMStateMsgp_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }
    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_GetTauStartCause
 Description     : ��ȡ��ǰTAU������ԭ���Ժ�������ʽ�ṩ��TAU֮�������ģ
                   ��ʹ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-10-25  Draft Enact

*****************************************************************************/
NAS_EMM_TAU_START_CAUSE_ENUM_UINT8  NAS_EMM_TAU_GetTauStartCause(
                                        VOS_VOID)
{
    return NAS_EMM_TAU_GetEmmTAUStartCause();
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_GetImsiDetachFlag
 Description     : ��ȡIMSI DETACH FLAG��ʶ

 Input           : None
 Output          : None
 Return          : NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8

 History         :
    1.lihong 00150010      2012-03-13  Draft Enact

*****************************************************************************/
NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8  NAS_EMM_TAU_GetImsiDetachFlag( VOS_VOID )
{
    return NAS_EMM_TAU_GetEmmTauImsiDetachFlag();
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_SetImsiDetachFlag
 Description     : ����IMSI DETACH FLAG��ʶ

 Input           : None
 Output          : None
 Return          : NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8

 History         :
    1.lihong 00150010      2012-03-13  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_TAU_SetImsiDetachFlag
(
    NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8 enImsiDetachFlag
)
{
    NAS_EMM_TAU_SaveEmmTauImsiDetachFlag(enImsiDetachFlag);
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_IsUplinkPending
 Description     : ����ESM��RABM�ṩ��API���ж��Ƿ�����������������������
                   ���������������������������������ջ����ESM����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-2-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_IsUplinkPending( VOS_VOID )
{
    if((EMM_ESM_UP_SINGNAL_PENDING == NAS_ESM_IsUpSingnalPending())
        ||(EMM_ERABM_UP_DATA_PENDING == NAS_ERABM_IsDataPending())
#if (FEATURE_ON == FEATURE_IMS)
        /* �����IMSҵ���ҵ�ǰ������������̬ʱ������������PENDING�ı�ʶ��
        ����IMSͨ�������У���L���л�ʱ����������pending����Ϊtrue */
        /*��������̬����IMSҵ��ʱ��TAU REQ��Ϣ�в�Ӧ�ô�ACTIVE��ʶ*/
        /* �ӿ����޸� */
        ||((VOS_TRUE == IMSA_IsExitImsService())
        && (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState()))
#endif
        )
    {
        NAS_EMM_TAU_SetEmmUplinkPending(NAS_EMM_UPLINK_PENDING);
    }
    else
    {
        NAS_EMM_TAU_SetEmmUplinkPending(NAS_EMM_NO_UPLINK_PENDING);
    }

    return;
}

VOS_UINT32 NAS_EMM_TAU_CanTriggerComTauWithIMSI(VOS_VOID)
{
    if((NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
        && ( NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetEpsUpdateType(NAS_EMM_TAU_START_CAUSE_OTHERS))
        && (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus()))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


VOS_UINT32  NAS_EMM_TAU_RrcRelCauseTriggerTau(VOS_VOID)
{
    NAS_LMM_NETWORK_INFO_STRU           *pMmNetInfo = NAS_EMM_NULL_PTR;

    if(NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE == NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:load balance");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RrcRelCauseTriggerTau_ENUM,LNAS_FUNCTION_LABEL1);
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_RRC_REL_LOAD_BALANCE);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_LOAD_BALANCE);
        return NAS_EMM_YES;
    }
    else if(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE ==
                                        NAS_LMM_GetEmmInfoTriggerTauRrcRel())
    {
        /* �������CSFB DELAY��ʱ�����µ�֮ǰ��CSFBû�ܷ��𣬴�ʱ�����跢��TAU����SERVICE��
        ��Ҫ�ȷ�EXT SERVICE������һ������SERVICE�������Ͳ����ٷ���EXT SERVICE*/
        if((VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
            &&(NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl()))
        {
            /* ����UE����CSFB */
            NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE);

            /*������ʱ��3417*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /* ESR�տڷ���ǰ,֪ͨLRRC CSFB����INIT,LRRC��һ��ȫ�ֱ���,��ESR����ʱ�����ؽ�,ֱ�ӻ�LMM REL,����ȥGU */
            NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_INIT);

            /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

            /* ���֮ǰ��¼��SERVICE��ͻ */
            NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);

            return NAS_EMM_YES;
        }
        else
        {
            /* ����ɾ�������������PENDING,��ᷢ��SERVICE */
            NAS_EMM_TAU_IsUplinkPending();

            if(NAS_EMM_UPLINK_PENDING == NAS_EMM_TAU_GetEmmUplinkPending())
            {
                /*������������pendingʱ,����SR֮ǰ��Ҫ��MMC�ϱ�TAU�����ʹMMC֪ͨCDS�л���LTEģʽ */
                pMmNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();
                NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);
                NAS_EMM_SetTauTypeNoProcedure();
                /* ע��/����״̬�ϱ�����MMC�Ż���������EUֵ�ٸ�MMC�ظ�TAU��� */
                NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_UPDATED_EU1);
                NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
                if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
                {
                    /*����PS LOC��Ϣ*/
                    NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
                }
                NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:Init Ser.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RrcRelCauseTriggerTau_ENUM,LNAS_FUNCTION_LABEL2);
                NAS_EMM_SER_UplinkPending();
            }
            else
            {
                NAS_EMM_TAU_LOG_INFO("NAS_EMM_RrcRelCauseTriggerTau:RRC connection failure");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RrcRelCauseTriggerTau_ENUM,LNAS_FUNCTION_LABEL3);
                /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_RRC_REL_CONN_FAILURE );*/
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

                /* �������TAU����ԭ�� */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_CONN_FAIL);
            }

            return NAS_EMM_YES;
        }
    }
    else
    {

    }

    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc
 Description     : Reg.Limite_Service
                   Reg.Plmn_Search
                   Reg.No_Cell_Available
                   ״̬���յ�SYS_INFO_INDʱ����T3412��ʱ����ʱ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010  2011-08-31  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc( VOS_VOID )
{
    /* Э��24301 5.3.5�½���������REG+NO_AVAILABLE_CELL״̬�£�T3412��ʱ�����
       ISR���������T3423��ʱ��;���ISRû�м�����
       ��ǰ������ע��ɹ�����ص�REG+NORMAL_SERVICE̬�󣬷�������TAU��TAU����Ϊ
       combined TA/LA updating with IMSI attach�������������ע��ɹ�������������TAU
   */
    if (NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL ==  NAS_LMM_GetEmmInfoT3412ExpCtrl())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc:REG+NO_AVAILABE_CELL T3412exp.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc_ENUM,LNAS_FUNCTION_LABEL1);

        if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
        {
             /* ��ע�����ΪPS����Ϊ�˻ص�REG+NORMAL_SERVICE̬�����Ҫ��������TAU����
                TAU����Ӧ����Ϊcombined TA/LA updating with IMSI attach */
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
             /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
             NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }
        else
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_T3412EXP);
        }
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3412_EXP_HAPPENED);
        return NAS_LMM_MSG_HANDLED;
    }

    /* Э��24301 5.3.5�½�����������ڷ�REG+NO_AVAILABLE_CELL״̬�£�T3412��ʱ��
       �򵱻ص�REG+NORMAL_SERVICE̬��Ӧ���� Periodic TAU*/
    if(NAS_EMM_T3412_EXP_YES_OTHER_STATE ==  NAS_LMM_GetEmmInfoT3412ExpCtrl())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc:Other State T3412exp.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_TAU_SaveEmmTAUStartCause( NAS_EMM_TAU_START_CAUSE_T3412EXP);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_3412_EXP_HAPPENED);

        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_DISCARD;
}



/*****************************************************************************
 Function Name   : NAS_EMM_RegSomeStateStartTAUNeeded
 Description     :   �ж��Ƿ���Ҫ����TAU������Ҫ��ֱ�ӷ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151  2012-7-10  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_RegSomeStateStartTAUNeeded( VOS_VOID )
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_ENTRY);

    /* ����ڼ䷢����ESM�����޸ĳ���������*/
    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded:Bearer Status Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
        return NAS_EMM_YES;
    }

    /* ����ڼ䷢����UE_NET_CAP or DRX�ı䣬����TA-Updating TAU*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded:DrxOrNetCap Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED);
        return NAS_EMM_YES;
    }

    /*����ϵͳ��ʶ�����ж�*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoTriggerTauSysChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded: Sys Change flag");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL3);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_INTER_CHANGE);
        return NAS_EMM_YES;
    }

    /* �����ǰע����ΪPS���ҵ�ǰ����������CS���ע�ᣬ��������TAU */
    if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartTAUNeeded: with imsi attach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL4);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);
        return NAS_EMM_YES;
    }

    /* �жϽ��뼼���仯��ʶ������仯 */
    if (NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartTAUNeeded: UE radio capability is changed !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL5);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        return NAS_EMM_YES;
    }

    /*��RRC Relԭ������ж�*/
    if(NAS_EMM_YES == NAS_EMM_TAU_RrcRelCauseTriggerTau())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded:rrc rel cause");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_EMM_REL_CAUSE);
        return NAS_EMM_YES;
    }

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI"
       ��Ҫ������Lģ�¼���ISR��������Lģ��3412��3423��ʱ������ʱ�ĳ������˳������ܷ���������TAU */
    if (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartTAUNeeded: TIN is P-TMSI !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL6);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_PTMSI);
        return NAS_EMM_YES;
    }

    /* ����ʱ��T3412��ʱ */
    if (NAS_LMM_MSG_HANDLED == NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc())
    {
        return NAS_EMM_YES;
    }

    /* o)when the UE's usage setting or the voice domain preference for E-UTRAN change in the UE */
    if(NAS_EMM_YES == NAS_EMM_GetVoiceDomainChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartTAUNeeded: VOICE DOMAIN CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartTAUNeeded_ENUM,LNAS_FUNCTION_LABEL7);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE);
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;

}
/*****************************************************************************
 Function Name   : NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded
 Description     : ��ϵͳ�ص�L�ж��Ƿ���Ҫ����TAU������Ҫ��ֱ�ӷ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1. leixiantiao 00258641  2015-5-27  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded( VOS_VOID )
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_ENTRY);

    /* ����ڼ䷢����ESM�����޸ĳ���������*/
    if(NAS_EMM_EPS_BEARER_STATUS_CHANGEED == NAS_EMM_GetEpsContextStatusChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded:Bearer Status Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL1);
        /* ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_BEARER_STATUS_CHANGEED);
        return NAS_EMM_YES;
    }

    /* ����ڼ䷢����UE_NET_CAP or DRX�ı䣬����TA-Updating TAU*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoDrxNetCapChange())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded:DrxOrNetCap Change.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL2);
        /* ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_DRX_CHANGEED);
        return NAS_EMM_YES;
    }

    /*����ϵͳ��ʶ�����ж�*/
    if(NAS_EMM_YES == NAS_LMM_GetEmmInfoTriggerTauSysChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded: Sys Change flag");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL3);
        /* ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_INTER_CHANGE);
        return NAS_EMM_YES;
    }

    /* �����ǰע����ΪPS���ҵ�ǰ����������CS���ע�ᣬ��������TAU */
    if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded: with imsi attach");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL4);
        /* ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_ATTACH_NON_EPS);
        return NAS_EMM_YES;
    }

    /* �жϽ��뼼���仯��ʶ������仯 */
    if (NAS_LMM_UE_RADIO_CAP_NOT_CHG != NAS_LMM_GetEmmInfoUeRadioCapChgFlag())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded: UE radio capability is changed !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL5);
        /* ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_RADIO_CAP_CHANGE);
        return NAS_EMM_YES;
    }

    /*��RRC Relԭ������ж�*/
    if(NAS_EMM_YES == NAS_EMM_TAU_RrcRelCauseTriggerTau())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded:rrc rel cause");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_EMM_REL_CAUSE);
        return NAS_EMM_YES;
    }

    /* e)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI"
       ��Ҫ������Lģ�¼���ISR��������Lģ��3412��3423��ʱ������ʱ�ĳ������˳������ܷ���������TAU */
    if (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded: TIN is P-TMSI !");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL6);
        /* ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_PTMSI);
        return NAS_EMM_YES;
    }

    /* ����ʱ��T3412��ʱ */
    if (NAS_LMM_MSG_HANDLED == NAS_EMM_RegSomeStateMsgSysInfoT3412ExpProc())
    {
        return NAS_EMM_YES;
    }

    /* o)when the UE's usage setting or the voice domain preference for E-UTRAN change in the UE */
    if(NAS_EMM_YES == NAS_EMM_GetVoiceDomainChange() )
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded: VOICE DOMAIN CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded_ENUM,LNAS_FUNCTION_LABEL7);
        /* ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE, NAS_LMM_OM_TAU_START_TYPE_VOICE_DOMAIN_CHANGE);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;

}

/*****************************************************************************
 Function Name   : NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList
 Description     : Reg.Limite_Service
                   Reg.Plmn_Search
                   Reg.No_Cell_Available
                   ״̬���յ�SYS_INFO_IND��TAI����TAI LIST��
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong 00150010    2014-01-23  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList( VOS_VOID )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList_ENUM,LNAS_ENTRY);

    /* ��ȡ��ǰTA���ϴγ���ע���TA��Ϣ */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    /* TAû��&&�ж�ʱ��&&EUֵ����EU1���ȳ�ʱ; ������������TAU*/
    if( (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
        && (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
        && (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat()))
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList: wait timer expired.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_TAUSER_FSMTranState( EMM_MS_REG,
                                     EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                                     TI_NAS_EMM_STATE_NO_TIMER);

        /* �ж�ʱ��3402������, ���ϱ�TAU��� */
        if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
        {
            NAS_EMM_SetTauTypeNoProcedure();

            ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING;
            NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);


        }
        return;
    }

    /* ����TAU����������TAU Procedure */
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
    NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

    /* �������TAU����ԭ�� */
    NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
    return;
}
#if(FEATURE_ON == FEATURE_CSG)

VOS_UINT32  NAS_EMM_RegSomeStateMsgSysInfoCsgIdNotInCsgList( VOS_VOID )
{
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;


    NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoCsgIdNotInCsgList is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCsgIdNotInCsgList_ENUM,LNAS_ENTRY);


    /* CSG ID���ϴγ��Ե�CSG ID��ͬ,��û��T3411��T3402 */
    if ((NAS_EMM_NO == NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId())
        ||(NAS_EMM_NO == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId)))
    {
        /* ����TAU����������TAU Procedure */
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);
        return NAS_EMM_YES;
    }


    return NAS_EMM_NO;
}
#endif

/*****************************************************************************
 Function Name   : NAS_EMM_RegSomeStateMsgSysInfoCommProc
 Description     : Reg.Limite_Service
                   Reg.Plmn_Search
                   Reg.No_Cell_Available
                   ״̬���յ�SYS_INFO_IND�Ĺ���������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151  2012-7-10  Draft Enact
    2.lihong 00150010    2012-12-18 Modify:Emergency
*****************************************************************************/
VOS_VOID  NAS_EMM_RegSomeStateMsgSysInfoCommProc( VOS_VOID )
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;
    NAS_MM_NETWORK_ID_STRU             *pstPresentNetInfo = NAS_EMM_NULL_PTR;
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;

    /* ��ȡ��ǰTA���ϴγ���ע���TA��Ϣ */
    pstPresentNetInfo                  = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegSomeStateMsgSysInfoCommProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCommProc_ENUM,LNAS_ENTRY);

#if(FEATURE_ON == FEATURE_CSG)
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        if(NAS_EMM_YES == NAS_EMM_RegSomeStateMsgSysInfoCsgIdNotInCsgList())
        {
            return;
        }
    }
#endif

    /* �����ǰTA����TAI LIST */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        NAS_EMM_RegSomeStateMsgSysInfoTaiNotInTaiList();

        return ;
    }

    /* TA��TAI LIST && EUֵ��ΪEU1 */
    if (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoCommProc: TA is in TAI LIST, not EU1.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL1);

        /* �ϴγ��Է���ע���TAU��TA����TAI LIST�����ü�������TAU */
        if (NAS_EMM_NO == NAS_LMM_IsLastAttemptRegTaInTaiList())
        {
            NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

            /* �������TAU����ԭ�� */
            NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_LAST_ATTEMPT_TA_NOT_IN_TAI_LIST);
            return;
        }

        /*�ж�ʱ�� && ��ǰTA���ϴγ��Է���ע���TA��Ч���ȳ�ʱ*/
        if (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoCommProc: Equivalent TA, wait timer expired.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL2);
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

            /* �ж�ʱ����3402������, ���ϱ�TAU��� */
            if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

            }
            return;
        }

        /* û�ж�ʱ�� && ��ǰTA���ϴγ��Է���ע���TA��Ч������TAU�������ó��Դ��� */
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
        return;
    }

    /* TA��TAI LIST && EUֵΪEU1*/
    /* ����ж�ʱ�������жϸ�ת��NORMAL SEVICE����UPDATE MM̬���ȳ�ʱ */
    if ((NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
        && (VOS_TRUE != NAS_EMM_IsEnterRegLimitService()))
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoCommProc: Check enter Nor-service or Upt-MM state.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL3);

        if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        {
            /* ��״̬ת����MS_REG + EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM״̬ */
            NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                           EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                           TI_NAS_EMM_STATE_NO_TIMER);

            /* �ж�ʱ����3402������, ���ϱ�TAU��� */
            if (TI_NAS_EMM_PTL_T3402 == enPtlTimerId)
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
                return;
            }
        }
        else
        {
            /* ��״̬ת����MS_REG + SS_REG_NORMAL_SERVICE״̬ */
            NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                           EMM_SS_REG_NORMAL_SERVICE,
                                           TI_NAS_EMM_STATE_NO_TIMER);
        }

        NAS_EMM_SetTauTypeNoProcedure();

        /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();

        return ;
    }

    /* TA��TAI LIST && EUֵΪEU1*/
    /* ���û�ж�ʱ�� */
    /* ������㷢��TAU��������ֱ�ӷ��𣬷���תNORMAL SERVICE */
    if (NAS_EMM_NO == NAS_EMM_RegSomeStateStartTAUNeeded())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegSomeStateMsgSysInfoCommProc: TAU not needed, return Nor-service.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegSomeStateMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL4);

        /* TA��TAI List�У����� L.V.R TAI*/
        NAS_EMM_SetLVRTai(pstPresentNetInfo);
        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

        /* ת��EMM״̬��MS_REG+SS_NORMAL_SEARVICE*/
        /*NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);*/
        NAS_EMM_SetTauTypeNoProcedure();

        /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoWaitTimerExp3411or3402Running
 Description     : �յ�ϵͳ��Ϣʱʶ���Ҫ�ȴ�T3402��ʱ�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010    2014-01-23  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_RegStateMmcOriResumeSysInfoWaitTimerExp3411or3402Running
(
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId
)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt;

    NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp: Check enter Nor-service or Upt-MM state.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoWaitTimerExp3411or3402Running_ENUM,LNAS_FUNCTION_LABEL1);

    if (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
    {
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        /* ��״̬ת����MS_REG + EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM״̬ */
        NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                       EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                                       TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        if (VOS_TRUE == NAS_EMM_IsEnterRegLimitService())
        {
            return NAS_EMM_FAIL;
        }
        if (NAS_EMM_YES == NAS_EMM_TAU_CanTriggerComTauWithIMSI())
        {
            /* ��״̬ת����MS_REG + EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM״̬ */
            NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                           EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                           TI_NAS_EMM_STATE_NO_TIMER);

            /* �ж�ʱ����3402������, ���ϱ�TAU��� */
            if (TI_NAS_EMM_PTL_T3402 == enPtlTimerId)
            {
                TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoWaitTimerExp3411or3402Running_ENUM,LNAS_FUNCTION_LABEL2);

                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
                return NAS_EMM_SUCC;
            }
        }
        else
        {
            /* ��״̬ת����MS_REG + SS_REG_NORMAL_SERVICE״̬ */
            NAS_EMM_TAUSER_FSMTranState(   EMM_MS_REG,
                                           EMM_SS_REG_NORMAL_SERVICE,
                                           TI_NAS_EMM_STATE_NO_TIMER);
        }
    }

    NAS_EMM_SetTauTypeNoProcedure();

    /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
    NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp
 Description     : �յ�ϵͳ��Ϣʱʶ���Ҫ�ȴ�T3402��ʱ�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen          2012-10-31  Draft Enact
    2.lihong00150010    2012-12-18  Modify:Emergency
*****************************************************************************/
VOS_UINT32  NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp( VOS_VOID )
{
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    /* ��ȡ��ǰTA���ϴγ���ע���TA��Ϣ */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    if (NAS_RELEASE_R11)
    {
        NAS_EMM_IsG2LGmmSuspendAndIsrAct();
    }
#if(FEATURE_ON == FEATURE_CSG)
    if(NAS_EMM_YES ==NAS_EMM_RegStateMmcOriResumeSysInfoIsCsgIdNotInListTauNeed())
    {
        return NAS_EMM_FAIL;
    }
#endif

    /* �����ǰTA����TAI LIST */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        /* TAû��&&�ж�ʱ��&&EUֵ����EU1���ȳ�ʱ; ������������TAU*/
        if( (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
            && (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
            && (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat()))
        {
            NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp: TA is not in TAI LIST, wait timer expired.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_TAUSER_FSMTranState( EMM_MS_REG,
                                         EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                                         TI_NAS_EMM_STATE_NO_TIMER);

            /* �ж�ʱ��3402������, ���ϱ�TAU��� */
            if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);


            }
            return NAS_EMM_SUCC;
        }
        return NAS_EMM_FAIL;

    }

    if (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp: TA is in TAI LIST, not EU1.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp_ENUM,LNAS_FUNCTION_LABEL2);

        /*�ж�ʱ�� && ��ǰTA���ϴγ��Է���ע���TA��Ч���ȳ�ʱ*/
        if ((NAS_EMM_YES == NAS_LMM_IsLastAttemptRegTaInTaiList())
            && (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId)))
        {
                NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp: Equivalent TA, wait timer expired.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoRecogniseWaitTimerExp_ENUM,LNAS_FUNCTION_LABEL3);
                NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                            EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                                            TI_NAS_EMM_STATE_NO_TIMER);

            /* �ж�ʱ��3402������, ���ϱ�TAU��� */
            if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

            }
            return NAS_EMM_SUCC;
        }
        return NAS_EMM_FAIL;
    }
    /* TA��TAI LIST && EUֵΪEU1*/

    /* ����ж�ʱ�������жϸ�ת��NORMAL SEVICE����UPDATE MM̬���ȳ�ʱ */
    if (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
    {
        return NAS_EMM_RegStateMmcOriResumeSysInfoWaitTimerExp3411or3402Running(enPtlTimerId);
    }

    return NAS_EMM_FAIL;
}
/* leixiantiao 00258641 �ع���������Ȧ���Ӷ� 2014-7-30 begin */
/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc
 Description     : ע��̬���յ�ϵͳ��Ϣ,����Ҫ��T3411����T3402��ʱ����TIN����Ϊ
                    P-TMSI�Ĺ�������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641     2014-7-30  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_RegStateMmcOriResumeSysInfoWithTmsiProc(VOS_VOID)
{
    if ((NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL == NAS_LMM_GetEmmInfoT3412ExpCtrl())
        && (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:combined succ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoWithTmsiProc_ENUM,LNAS_FUNCTION_LABEL1);

        /* ��ע�����ΪPS����Ϊ�˻ص�REG+NORMAL_SERVICE̬�����Ҫ��������TAU����
            TAU����Ӧ����Ϊcombined TA/LA updating with IMSI attach */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    }
    /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
    /* ��ϵͳTAU������ϵͳTAU��װ���� */
    NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_PTMSI);
    return;
}
/* leixiantiao 00258641 �ع���������Ȧ���Ӷ� 2014-7-30 end */
/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoWithNotEu1Proc
 Description     : ע��̬���յ�ϵͳ��Ϣ,����Ҫ��T3411����T3402��ʱ����EUֵ��ΪEUI�Ĺ�������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181 2014-09-26  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_RegStateMmcOriResumeSysInfoWithNotEu1Proc(VOS_VOID)
{
    NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc: TA is in TAI LIST, not EU1.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoWithNotEu1Proc_ENUM,LNAS_FUNCTION_LABEL1);

    /* �ϴγ��Է���ע���TAU��TA����TAI LIST�����ü�������TAU */
    if (NAS_EMM_NO == NAS_LMM_IsLastAttemptRegTaInTaiList())
    {
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        /* ������: ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
        return;
    }

    /* û�ж�ʱ�� && ��ǰTA���ϴγ��Է���ע���TA��Ч������TAU�������ó��Դ��� */
    /* ������: ��ϵͳTAU������ϵͳTAU��װ���� */
    NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_EU1);
    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc
 Description     : ע��̬���յ�ϵͳ��Ϣ,����Ҫ��T3411����T3402��ʱ�Ĺ�������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen          2012-10-31  Draft Enact
    2.lihong00150010    2012-12-18  Modify:Emergency
*****************************************************************************/
VOS_VOID  NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc( VOS_VOID )
{
    NAS_MM_NETWORK_ID_STRU             *pstPresentNetInfo = NAS_EMM_NULL_PTR;
    GMM_LMM_GPRS_MM_STATE_ENUM_UINT32   enGprsMmState   = GMM_LMM_GPRS_MM_STATE_BUTT;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();
    pstPresentNetInfo                 = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc is entered.");

    if (NAS_EMM_YES == NAS_EMM_IsPtmsiTauActiveFlagSatified())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc: PTMSI, save active flag ctrl.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM, LNAS_EMM_PTMSI_SET_ACT_FLAG);
        NAS_EMM_TAU_SaveEmmPtmsiActiveFlagCtrl(NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_VALID);
    }

    /*c)when the UE enters EMM-REGISTERED.NORMAL-SERVICE and the UE's TIN indicates "P-TMSI"*/
    if (MMC_LMM_TIN_P_TMSI == ulTinType)
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:TIN is p-tmsi");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_FUNCTION_LABEL1);

        /* leixiantiao 00258641 ����Ȧ���Ӷ� 2014-7-30 begin */
        NAS_EMM_RegStateMmcOriResumeSysInfoWithTmsiProc();
        /* leixiantiao 00258641 ����Ȧ���Ӷ� 2014-7-30 end */
        return;
    }

    /* d)when the UE performs an intersystem change from A/Gb or Iu mode to S1 mode,
     and the UE previously either performed a location area update procedure
     or a combined routing area update procedure in A/Gb or Iu mode,
     in order to re-establish the SGs association. In this case the EPS update
     type IE shall be set to "combined TA/LA updating with IMSI attach"; */
    if (NAS_EMM_YES == NAS_EMM_IsLauOrComRauOrSrvccHappenedWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:FIRST TAU");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_FUNCTION_LABEL2);

        /*����TAU����*/
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
        /* ������: ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_LAU_COMRAU);

        return;
    }

    if (NAS_EMM_YES == NAS_EMM_IsEmcCsfbHappenedAndLaiChangWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:EMC CSFB,LAI CHANG ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_EMM_EMC_CSFB_LAI_CHG);
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    }

    /* ��ȡGģ����״̬ */
    enGprsMmState = NAS_LMM_GetEmmInfoGConnState();

    /* l)when the UE reselects an E-UTRAN cell while it was in GPRS READY state or PMM-CONNECTED mode; */
    /* For case l, if the TIN indicates "RAT-related TMSI", the UE shall set the TIN to "P-TMSI" before
    initiating the tracking area updating procedure.*/
    if (GMM_LMM_GPRS_MM_STATE_READY  == enGprsMmState)
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:GPRS READY init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_EMM_GPRS_READY_TAU);
        NAS_EMM_SetTinToPtmsiWhenIsrAct();
        /* ������: ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GPRS_READY_OR_PMM_CONNECT);
        return ;
    }

    /* ����TAU */
    /* For case c, if the TIN indicates "RAT-related TMSI" and the EPS services were not resumed before
    returning to S1 mode, the UE shall set the TIN to "P-TMSI" before initiating
    the combined tracking area updating procedure*/

    if (NAS_EMM_YES == NAS_EMM_IsG2LAndGmmSuspendWithCsPsUeMode())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc:EPS service suspended init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_EMM_EPS_SERV_SUSP_TAU);
        NAS_EMM_SetTinToPtmsiWhenIsrAct();
        /* ������: ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_GSM_PS_SUSPEND);
        return ;
    }

    /*q)When the UE performs an intersystem change from A/Gb mode to S1 mode and the TIN indicates "RAT-related TMSI",
    but the UE is required to perform tracking area updating for IMS voice termination as specified in 3GPP TS 24.008 [13],
    annex P.4*/
    if (NAS_EMM_YES == NAS_EMM_RegStateMmcOriResumeSysInfoIsIsrActP4TAUNeed())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:ISR act and P.4 init tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_EMM_ISR_ACT_P4_TAU);
        /* ������: ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_P4);
        return;
    }
#if(FEATURE_ON == FEATURE_CSG)
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_ProcSysWhenRsmGu2LRegRedirect:CSG not in CSG list tau");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_FUNCTION_LABEL3);

        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);

        return;
    }
#endif

    /* �����ǰTA����TAI LIST */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        /* ����TAU����������TAU Procedure */
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        /* ������: ��ϵͳTAU������ϵͳTAU��װ���� */
        NAS_EMM_TAU_StartTauForInterRat(NAS_EMM_TAU_START_CAUSE_OTHERS, NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        return;

    }

    /* TA��TAI LIST && EUֵ��ΪEU1 */
    if (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat())
    {
        NAS_EMM_RegStateMmcOriResumeSysInfoWithNotEu1Proc();
        return;
    }


    /* TA��TAI LIST && EUֵΪEU1*/
    /* ���û�ж�ʱ�� */
    /* ������㷢��TAU��������ֱ�ӷ��𣬷���תNORMAL SERVICE */
    /* ������: ��ϵͳTAU������ϵͳTAU��װ���� */
    if (NAS_EMM_NO == NAS_EMM_RegSomeStateStartIntrerRatTAUNeeded())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc: TAU not needed, return Nor-service.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegStateMmcOriResumeSysInfoNeednotWaitTimerExpProc_ENUM,LNAS_FUNCTION_LABEL3);

        /* TA��TAI List�У����� L.V.R TAI*/
        NAS_EMM_SetLVRTai(pstPresentNetInfo);
        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        NAS_EMM_TranStateRegNormalServiceOrRegLimitService();

        /* ת��EMM״̬��MS_REG+SS_NORMAL_SEARVICE*/
        /*NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);*/

        NAS_EMM_SetTauTypeNoProcedure();

        NAS_EMM_ProcHoWaitSysInfoBufferMsg();

        /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();

        NAS_EMM_TAU_ClearActiveFlagProc();

        return;
    }
    /* �޸ĺ������� */
    (VOS_VOID)NAS_EMM_ClrWaitSysInfoBufferMsg();

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc
 Description     : REG+NORMAL_SERVICE״̬����UPDATE_MM״̬���յ�ϵͳ��Ϣ���ж��Ƿ���TAU�Ĵ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

  History             :
     1.wangchen 00209181    2012-08-24  Draft Enact
     2.lihong 00150010      2012-12-18  Modify:Emergency
     3.leixiantiao 00258641 2015-07-02  fix DTS2015062301014
*****************************************************************************/
VOS_VOID  NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc( EMMC_EMM_CHANGE_INFO_ENUM_UINT32    ulChangeInfo )
{
    NAS_MM_NETWORK_ID_STRU             *pstPresentNetInfo = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;
    VOS_UINT32                          ulRslt = NAS_EMM_FAIL;
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    /* ��ȡ��ǰTA��Ϣ */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstPresentNetInfo                  = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc_ENUM,LNAS_ENTRY);
#if(FEATURE_ON == FEATURE_CSG)
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        /* ����TAU����������TAU Procedure */
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        ulRslt = NAS_EMM_ClrWaitSysInfoBufferMsg();
        if (NAS_EMM_SUCC == ulRslt)
        {
            NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);

        return;
    }
#endif
    /* �����ǰTA����TAI LIST */
    if (NAS_EMM_FAIL == NAS_EMM_TAU_IsCurrentTAInTaList())
    {
        /* ����TAU����������TAU Procedure */
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        /* �޸ĺ������� */
        ulRslt = NAS_EMM_ClrWaitSysInfoBufferMsg();
        if (NAS_EMM_SUCC == ulRslt)
        {
            NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        return;

    }
     /* TA��TAI LIST */
    /* ����ж�ʱ�����ȳ�ʱ */
    if ((NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
        && (VOS_TRUE != NAS_EMM_IsEnterRegLimitService()))
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc: Check enter Nor-service or Upt-MM state.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_ProcHoWaitSysInfoBufferMsg();
        /* С����Ϣ����,MMA������������������Ϣ,��Ҫ�յ�TAU IND�Ż����,Ϊ��ܸ�����,
           LMM����һ�������κβ���TAU IND��Ϣ�ϱ���MMC */
        /* ��UE�յ�MMC������ϵͳ��Ϣ֮����Ҫ����attach��tau���̣�����ԭ�����̴�������T3411��T3402��run����ô��MMC�ϱ�TAU����ļ���Ϣ */
        /* �ж�ʱ����3402������, ���ϱ�TAU��� */
        if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
        {
            NAS_EMM_SetTauTypeNoProcedure();

            ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC;

            NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
        }
        /* �ж�ʱ����3411������, ���ϱ�TAU��� */
        if ( TI_NAS_EMM_PTL_T3411 == enPtlTimerId )
        {
            NAS_EMM_SetTauTypeNoProcedure();

            ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
            NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
        }
        return ;
    }

    /* TA��TAI LIST && û�ж�ʱ��  */
    /* ������㷢��TAU��������ֱ�ӷ��𣬷���״̬����(UPDATE MM̬һ���ж�ʱ��) */
    if (NAS_EMM_NO == NAS_EMM_RegSomeStateStartTAUNeeded())
    {
        NAS_EMM_TAU_LOG_NORM("NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc: TAU not needed, return Nor-service.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_RegNormalServiceOrUpdateMMMsgSysInfoCommProc_ENUM,LNAS_FUNCTION_LABEL2);

        /* TA��TAI List�У����� L.V.R TAI*/
        NAS_EMM_SetLVRTai(pstPresentNetInfo);

        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        if (VOS_TRUE == NAS_EMM_IsEnterRegLimitService())
        {
            NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                            EMM_SS_REG_LIMITED_SERVICE,
                                            TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            NAS_EMM_ProcConnRelWaitSysInfoBufferMsg();
            NAS_EMM_ProcHoWaitSysInfoBufferMsg();
        }

        /* �����������ĳ�����LMM��REG+NormalServiceOrUpdateMM״̬�յ�MMC������ϵͳ��Ϣ���ж�����ʱ�Ƿ�����Ӧtimer��Ҫ�ȴ���
        ����timer����ô���۵�ǰ��TA,CELL,PLMN�Ƿ�仯��LMM���MMC�ϱ�һ��TAU����Ϊ�յ�ind. */
        /* ������Ϣ����,MMA������������������Ϣ,��Ҫ�յ�TAU IND�Ż����,Ϊ��ܸ�����,
        LMM����һ�������κβ���TAU IND��Ϣ�ϱ���MMC */
        NAS_EMM_SetTauTypeNoProcedure();

        /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
        return;
    }
    /* �޸ĺ������� */
    (VOS_VOID)NAS_EMM_ClrWaitSysInfoBufferMsg();

    return;

}
/*****************************************************************************
 Function Name   : NAS_EMM_TAU_StartTauForInterRat
 Description     : ��ϵͳ�任������TAU
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-4-30  Draft Enact
    2.wangchen 00209181         2013-10-24 Modify
    3.leixiantiao 00258641      2015-07-23 ������������ϱ�TAU����ԭ��
*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_StartTauForInterRat( NAS_EMM_TAU_START_CAUSE_ENUM_UINT8 ucTauStartCause,
                                                        NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 enTauStartType)
{
    if (NAS_LMM_SYS_CHNG_TYPE_HO != NAS_EMM_GetResumeType())
    {
        /* ��ȡGU��UMTS��ȫ�����ģ�����LTE�İ�ȫ�����������ð�ȫ״̬*/
        NAS_EMM_SecuResumeIdle();
    }
    /* ������: ����ϵͳ��־���ñ�־��DISABLE LTE��DEREG��TAU SUCC�ɹ�ʱ��� */
    NAS_EMM_SetOmInterTauFlag(NAS_EMM_YES);
    /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_SYSINFO);*/
    NAS_EMM_TAU_SaveEmmTAUStartCause(ucTauStartCause);
    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_YES);

    NAS_EMM_TAU_StartTAUREQ(enTauStartType);
    return;
}



/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgSrvccNofify
 Description     : �յ�ID_MM_LMM_SRVCC_NOFIFY��Ϣ����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leili 00132387    2014-12-18  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMsgSrvccNofify(MsgBlock *    pMsg )
{
    MM_LMM_SRVCC_STATUS_NOTIFY_STRU            *pstSrvccNotify;

    pstSrvccNotify = (VOS_VOID*)pMsg;

    if (MM_LMM_SRVCC_STATUS_SUCC == pstSrvccNotify->enSrvccStatus)
    {
        NAS_LMM_SetEmmInfoSrvccFlag(NAS_EMM_SRVCC_HAPPENED);

    }
    else
    {
        NAS_LMM_SetEmmInfoSrvccFlag(NAS_EMM_SRVCC_NOT_HAPPENED);
    }
    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_EmcPndReqTauAbnormalCommProc
 Description     : ����PDN���ӽ��������TAU�쳣��������
 Input           : pfTauRslt----------------TAU����ϱ�����ָ��
                   pvPara-------------------TAU����ϱ����������
                   ucSs---------------------��״̬
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-12-31  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_EmcPndReqTauAbnormalCommProc
(
    NAS_LMM_SEND_TAU_RESULT_ACT_FUN     pfTauRslt,
    const VOS_VOID                     *pvPara,
    NAS_EMM_SUB_STATE_ENUM_UINT16       ucSs
)
{
    /* �ϱ�TAU��� */
    NAS_EMM_TAU_SEND_MMC_RESULT_IND(pfTauRslt, pvPara);

    NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_MmcSendDetIndLocal( MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif
    /* ��¼ATTACH����ԭ��ֵ */
    NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                ucSs,
                                TI_NAS_EMM_STATE_NO_TIMER);
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_ClearActiveFlagProc
 Description     : TAU���Active flag����ش���
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2015-03-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_ClearActiveFlagProc(VOS_VOID)
{
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_ClearActiveFlagProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ClearActiveFlagProc_ENUM,LNAS_ENTRY);

    /* TMO�����������active flag��ʶ��� */
    NAS_EMM_TAU_SaveEmmTmoActiveFlagCtrl(NAS_EMM_TMO_ACTIVE_FLAG_CTRL_INVALID);

    /* ������ǰFLAG��״̬ */
    NAS_LMM_SndOmSetTmoActiveFlag(NAS_EMM_TMO_ACTIVE_FLAG_CTRL_INVALID);

    /* TAU��active flag��ʶ��� */
    NAS_EMM_TAU_SaveEmmTauReqActiveCtrl(NAS_EMM_TAU_NO_BEARER_EST_REQ);

    NAS_EMM_TAU_SaveEmmPtmsiActiveFlagCtrl(NAS_EMM_PTMSI_ACTIVE_FLAG_CTRL_INVALID);
    return;
}
#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 Function Name   : NAS_EMM_TAU_SendRrcDsdsBeginNotify
 Description     : TAU���̱���������ҵ��֪ͨ��ʼ��Ϣ��LRRCģ��
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.c00134407      2014-7-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_SendRrcDsdsBeginNotify(VOS_VOID)
{
    LRRC_LNAS_SESSION_TYPE_ENUM_UINT8  enSessionType;
    NAS_EMM_DSDS_TAU_TYPE_ENUM_UINT32  enTauType;

     /*���쳣���ܽ���NORMAL̬������Ϊ��ǰTAU����ΪLOW-TAU������ΪHIGH-TAU*/
    /* if(NAS_EMM_SUCC == NAS_EMM_CheckEnterRegNormal())
    {
        enSessionType = LRRC_LNAS_SESSION_TYPE_PS_LOW_TAU;
    }
    else
    {
        enSessionType = LRRC_LNAS_SESSION_TYPE_PS_HIGH_TAU;
    }*/
    /* Low���ȼ���TAU���ټ����������쳣ʱ�����ܻᵼ����Դû���ͷţ���HIGH���ͣ�
       ��ʹTAU����û�������������´�TAUʱ��������ͬ��Դ��TAU�ɹ���,���ͷ���Դ���ȡ��LOW���� */
    enSessionType = LRRC_LNAS_SESSION_TYPE_PS_HIGH_TAU;

    enTauType = (NAS_EMM_DSDS_TAU_TYPE_ENUM_UINT32)enSessionType;

    /*���浱ǰTAU������*/
    NAS_EMM_SetDsdsTauType(enTauType);

    /*��װ������ҵ��֪ͨ��ʼ��Ϣ��LRRCģ��*/
    NAS_LMM_SendRrcDsdsBeginNotify(enSessionType);

     return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_SendRrcDsdsEndNotify
 Description     : TAU���̱���������ҵ��֪ͨ������Ϣ��LRRCģ��
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.c00134407      2014-7-9  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_SendRrcDsdsEndNotify(VOS_VOID)
{
     LRRC_LNAS_SESSION_TYPE_ENUM_UINT8  enSessionType;

     /*��ȡ��ǰTAU������*/
     enSessionType = (LRRC_LNAS_SESSION_TYPE_ENUM_UINT8)NAS_EMM_GetDsdsTauType();

     /*��װ������ҵ��֪ͨ������Ϣ��LRRCģ��*/
     NAS_LMM_SendRrcDsdsEndNotify(enSessionType);

     return;
}
#endif
#if(FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 Function Name   : NAS_EMM_IsCsgIdChangeTauStart
 Description     : �Ƿ���CSG ID CHANGE ���µ�TAU
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsTauInitSsWaitCNCnfIsCsgIdChangeTauStart(VOS_VOID)
{

    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList())
        &&(NAS_EMM_NO == NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId()))
    {
        /*����EPS״̬ΪEU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        /*ֹͣT3430��ʱ��*/
        NAS_LMM_StopStateTimer(              TI_NAS_EMM_STATE_TAU_T3430);

#if (FEATURE_ON == FEATURE_DSDS)
        /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
        NAS_EMM_TAU_SendRrcDsdsEndNotify();
#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        NAS_EMM_SendMtcTAUEndType();
#endif

        /* TauAttemptCount����*/
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

        if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ != NAS_EMM_TAU_GetEmmTAUStartCause())
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }

        /* ���´���TAU*/
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_CSG_ID_CHANGE);

        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsAtpUpdataIsCsgIdNotInListTauStart
 Description     : �Ƿ���CSG ID NOT IN LIST ���µ�TAU
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsRegSsAtpUpdataIsCsgIdNotInListTauStart
(
    VOS_VOID
)
{
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId    = NAS_LMM_PTL_TI_BUTT;
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        if (NAS_LMM_TIMER_RUNNING != NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3346))
        {
            /* CSG ID���ϴγ��Ե�CSG ID��ͬ,��û��T3411��T3402 */
            if ((NAS_EMM_NO == NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId())
                || (NAS_EMM_NO == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId)))
            {

                /* ����TAU���� */
                NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
                NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

                /*����TAU Procedure*/
                /* �������TAU����ԭ�� */
                NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);

                return NAS_EMM_YES;

            }
        }

    }
    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsDeRegInitSsWaitCNDetachCnfIsCsgIdNotInListTauStart
 Description     : �Ƿ���CSG ID NOT IN LIST ���µ�TAU
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsDeRegInitSsWaitCNDetachCnfIsCsgIdNotInListTauStart(VOS_VOID)
{

    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsDeRegInitSsWaitCNDetachCnfIsCsgIdNotInListTauStart:CSGID not in CSG List.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsDeRegInitSsWaitCNDetachCnfIsCsgIdNotInListTauStart_ENUM,LNAS_FUNCTION_LABEL1);

        /* �������̳�ͻ��־λDETACH */
        NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_DETACH);

        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

        /* �����DETACH����ΪEPS/IMSI������������DETACH��TAU��ϱ�ʶ������
        �����TAU����Ϊ����TAU */
        if (MMC_LMM_MO_DET_CS_PS == NAS_EMM_GetDetachType())
        {
            /* ��������DETACH��TAU��ϱ�ʶ���������������TAU������ȻΪ����TAU */
            NAS_EMM_TAU_SetEmmCombinedDetachBlockFlag(NAS_EMM_COM_DET_BLO_YES);
        }

        /* ����DETACH�ĺ���������DETACH����*/
        NAS_EMM_DetachToTAU();

        /* ����TAU Procedure
        ע:MO_DETACH�����д���TAU����ΪDETACH_COLLISION��־����ȻЯ��ACTVIE,
        ���ж���������*/
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_CSG_LIST);

        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoIsCsgIdNotInListTauNeed
 Description     : �Ƿ���CSG ID NOT IN LIST ���µ�TAU
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_RegStateMmcOriResumeSysInfoIsCsgIdNotInListTauNeed
(
    VOS_VOID
)
{
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId     = NAS_LMM_PTL_TI_BUTT;
    if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
        &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
    {
        /* CSG ID���ϴγ��Ե�CSG ID��ͬ,��û��T3411��T3402,ֱ�ӷ���TAU */
        if ((NAS_EMM_NO == NAS_LMM_IsCurCsgIdEqualLastAttmpRegCsgId())
           || (NAS_EMM_NO == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId)))
        {
            return NAS_EMM_YES;
        }
    }
    return NAS_EMM_NO;
}
#endif
/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitSsWaitCNCnfSysChangeOrNotProc
 Description     : ϵͳ��Ϣ�ı����Ĵ���
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MsTauInitSsWaitCNCnfSysChangeOrNotProc
(
    EMMC_EMM_CHANGE_INFO_ENUM_UINT32 ulChangeInfo
)
{

    VOS_UINT32                          ulTaRslt    = NAS_EMM_FAIL;
    NAS_LMM_NETWORK_INFO_STRU          *pMmNetInfo = NAS_EMM_NULL_PTR;

    /* ��ȡEMMά����������Ϣ*/
    pMmNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();

    /* ���TA�����仯�����ͷ����ӣ������´���TAU*/
    if ((EMMC_EMM_CHANGE_PLMN == ulChangeInfo)
      ||(EMMC_EMM_CHANGE_TA == ulChangeInfo))
    {
        /*����EPS״̬ΪEU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);
        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }
        /*ֹͣT3430��ʱ��*/
        NAS_LMM_StopStateTimer(              TI_NAS_EMM_STATE_TAU_T3430);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
        NAS_EMM_TAU_SendRrcDsdsEndNotify();
        #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        NAS_EMM_SendMtcTAUEndType();
#endif

        /* TauAttemptCount����*/
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
        /* ���TA����TAI List�У��޸�TAU����ԭ�򣬴���TA-Updating TAU,
           ���TA��TAI List�У���������TAU����ԭ�򲻱�*/
        ulTaRslt = NAS_EMM_TAU_IsCurrentTAInTaList();
        if ((NAS_EMM_FAIL == ulTaRslt)
            && (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ != NAS_EMM_TAU_GetEmmTAUStartCause()))
        {
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        }
        /* ���´���TAU*/
        /* �������TAU����ԭ�� */
        NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_PLMN_TA_CHANGE);
    }
    else
    {
        /*����L.V.R TAI*/
        NAS_EMM_SetLVRTai(&pMmNetInfo->stPresentNetId);

        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_MsRegSsAtpUpdataIsTaNotListProc
 Description     : TA����TAI LIST�Ĵ���
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_MsRegSsAtpUpdataTaIsNotListProc
(
    VOS_VOID
)
{
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    MMC_LMM_TAU_RSLT_ENUM_UINT32        ulTauRslt = MMC_LMM_TAU_RSLT_BUTT;

    NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

    /* ��ȡ��ǰTA���ϴγ���ע���TA��Ϣ */
    NAS_EMM_GetCurrentTa(&stCurTa);
    pstLastAttmpRegTa                   = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    if (NAS_LMM_TIMER_RUNNING != NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3346))
    {
        /* ���ϴγ���ע���TA��ͬ && �ж�ʱ�� && EUֵ��ΪEU1 ���ȳ�ʱ;  ������������TAU */
        if(    (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstLastAttmpRegTa, &stCurTa))
            && (NAS_EMM_YES == NAS_EMM_IsT3411orT3402Running(&enPtlTimerId))
            && (EMM_US_UPDATED_EU1 != NAS_EMM_TAUSER_GetAuxFsmUpStat()) )
        {
            /* ��֮ǰ�й���RRC_REL���µ�TAU_REQ����ʧ�ܵ��������ô��ʱӦ����TAU */
            if(PS_TRUE == NAS_LMM_GetTauReqSndFailFlag())
            {
                 TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsRegSsAtpUpdataMsgSysinfo_ENUM,LNAS_LEAVE);
                 /* �������TAU����ԭ�� */
                 NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_SND_MSG_FAIL);

                 return;
            }

            /* ������Ϣ����,MMA������������������Ϣ,��Ҫ�յ�TAU IND�Ż����,Ϊ��ܸ�����,
               LMM����һ�������κβ���TAU IND��Ϣ�ϱ���MMC */
            /* ��UE�յ�MMC������ϵͳ��Ϣ֮����Ҫ����attach��tau���̣�����ԭ�����̴�������T3346��run������T3411��T3402��run����ô��MMC�ϱ�TAU����ļ���Ϣ */
            /* �ж�ʱ����3402������, ���ϱ�TAU��� */
            if ( TI_NAS_EMM_PTL_T3402 == enPtlTimerId )
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_T3402_RUNNING;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);

            }
            /* �ж�ʱ����3411������, ���ϱ�TAU��� */
            if ( TI_NAS_EMM_PTL_T3411 == enPtlTimerId )
            {
                NAS_EMM_SetTauTypeNoProcedure();

                ulTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&ulTauRslt);
            }
            return;
        }
        else
        {
            /* ����TAU���� */
            NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);

            /*����TAU Procedure*/
            /* �������TAU����ԭ�� */
            NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_NOT_IN_TAI_LIST);
        }
    }
    else
    {
        /* ��UE�յ�MMC������ϵͳ��Ϣ֮����Ҫ����attach��tau���̣�����ԭ�����̴�������T3346��run����ô��MMC�ϱ�TAU����ļ���Ϣ */
        /* С����Ϣ����,MMA������������������Ϣ,��Ҫ�յ�TAU IND�Ż����,Ϊ��ܸ�����,
        LMM����һ�������κβ���TAU IND��Ϣ�ϱ���MMC */
        NAS_EMM_SetTauTypeNoProcedure();

        /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
        NAS_EMM_MmcSendTauActionResultIndSuccWithoutPara();
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_RegStateMmcOriResumeSysInfoIsIsrActP4TAUNeed
 Description     : �ж��Ƿ���Ҫ����ISR_ACT_P4_TAU
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-11-3  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_RegStateMmcOriResumeSysInfoIsIsrActP4TAUNeed(VOS_VOID)
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();

    if ((NAS_LMM_RSM_SYS_CHNG_DIR_G2L == NAS_EMM_GetResumeDir())
           && (NAS_EMM_YES == NAS_EMM_IsAnnexP4ConditionSatisfied())
           && (MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType))
    {
        return NAS_EMM_YES;
    }
    return NAS_EMM_NO;
}
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 Function Name   : NAS_EMM_SendMtcTAUEndType
 Description     :
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-01-05  Draft Enact

*****************************************************************************/
MTC_SESSION_TYPE_ENUM_UINT8  NAS_EMM_GetTAUMtcSessionType
(
    VOS_VOID
)
{
    MTC_SESSION_TYPE_ENUM_UINT8         enMtcSessionType = MTC_SESSION_TYPE_BUTT;

    if (NAS_EMM_CN_TAU_TYPE_TA_UPDATING == NAS_EMM_TAU_GetTAUtype())
    {
        enMtcSessionType = MTC_SESSION_TYPE_TAU_ONLY_EPS;
    }
    else if(NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING == NAS_EMM_TAU_GetTAUtype())
    {
        enMtcSessionType = MTC_SESSION_TYPE_TAU_PERIODIC;
    }
    else
    {
        enMtcSessionType = MTC_SESSION_TYPE_TAU_COMBINED;
    }

    return  enMtcSessionType;

}

/*****************************************************************************
 Function Name   : NAS_EMM_SendMtcTAUEndType
 Description     :
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yanglei    2015-01-05  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SendMtcTAUEndType
(
    VOS_VOID
)
{
    TAF_CTRL_STRU                       stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8         enMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_MEM_SET(&stCtrl, 0x00, sizeof(TAF_CTRL_STRU));

    enMtcSessionType = NAS_EMM_GetTAUMtcSessionType();

    stCtrl.ulModuleId = PS_PID_MM;
    MTC_SetEndSessionInfo(&stCtrl,enMtcSessionType);
    return;
}
#endif


/*lint +e961*/
/*lint +e960*/
/*lint +e831*/
/*lint +e669*/
/*lint +e589*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



