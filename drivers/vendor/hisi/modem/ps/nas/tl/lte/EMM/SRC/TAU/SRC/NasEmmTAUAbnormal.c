/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : EmmTAU.c
  Description   : EMM TAU REQUEST������ش�����Դ�ļ�
  Function List :
    01.   NAS_EMM_MsRegSsNormalMsgSysinfo
    02.   NAS_EMM_MsRegSsNormalMsgT3411Exp
    03.   NAS_EMM_MsRegSsNormalMsgT3412Exp
    04.   NAS_EMM_MsRegSsNormalMsgT3402Exp
    05.   NAS_EMM_MsRegSsNormalMsgMmIntraTAUReq
    06.   NAS_EMM_MsRegSsAtpUpdataMsgSysinfo
    07.   NAS_EMM_MsRegSsAtpUpdataMsgT3411Exp
    08.   NAS_EMM_MsRegSsAtpUpdataMsgT3402Exp
    09.   NAS_EMM_MsRegSsLimitSRMsgSysinfo
    10.   NAS_EMM_MsRegSsPLMNSearchMsgSysinfo
    11.   NAS_EMM_MsRegSsUpdataNeedMsgSysinfo
    12.   NAS_EMM_MsRegSsNocellMsgSysinfo
    13.   NAS_EMM_MsTAUInitSsWaitCNCnfMsgTAUAcp
    14.   NAS_EMM_MsTAUInitSsWaitCNCnfMsgTAURej
    15.   NAS_EMM_MsTAUInitSsWaitCNCnfMsgT3430Exp
    16.   NAS_EMM_MsTAUInitSsWaitCNCnfMsgSysinfo
    17.   NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd
    18.   NAS_EMM_MsTAUInitSsWaitCNCnfMsgRrcRelInd
    19.   NAS_EMM_MsTAUInitSsWaitMrrcRelMsgMrrcRelInd
    20.   NAS_EMM_MsSERInitSsWaitCNCnfMsgSysinfo
    21.   NAS_EMM_MsSERInitSsWaitCNCnfMsgT3411Exp
    22.   NAS_EMM_MsSERInitSsWaitCNCnfMsgT3412Exp
    23.   NAS_EMM_MsSERInitSsWaitCNCnfMsgT3402Exp
    24.   NAS_EMM_MsSERInitSsWaitCNCnfMsgMmIntraTAUReq

  History       :
    1.  Zhouyan 00125190  2008.09.17  �¹�����
    2.  leili       00132387    2009.06.25   BJ9001269 �յ�ϵͳ��Ϣ�����Ż�
*******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "NasEmmTauSerInclude.h"
#include "NasEmmAttDetInclude.h"
#if (FEATURE_LPP == FEATURE_ON)
#include "NasEmmSsMsgProc.h"
#include "EmmLppInterface.h"
#include "NasEmmLppMsgProc.h"
#include "NasEmmSerProc.h"
#endif


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMTAUABNORMAL_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMTAUABNORMAL_C
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

NAS_EMM_BAR_STRU                        g_stEmmRegStateBarInfo;

static NAS_EMM_GRANT_ACT_STRU g_astGrantActTable[] =
{
    {LRRC_LNAS_ACCESS_GRANT_MT,                                 0xfb},
    {LRRC_LNAS_ACCESS_GRANT_MO_CALL,                            0xfd},
    {LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL,                          0xfe},
    {LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MT,                     0xf9},
    {LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MT,                   0xfa},
    {LRRC_LNAS_ACCESS_GRANT_ALL,                                0xf0},
    {LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL,              0xfc},
    {LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MT,       0xf8},
    {LRRC_LNAS_ACCESS_GRANT_MO_CSFB,                            0xf7},
    {LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_CSFB,                0xf5},
    {LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB,              0xf6},
    {LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_SIGNAL_AND_MO_CSFB,  0xf4},
    {LRRC_LNAS_ACCESS_GRANT_MO_CSFB_AND_MT,                     0xf3},
    {LRRC_LNAS_ACCESS_GRANT_MO_CALL_AND_MO_CSFB_AND_MT,         0xf1},
    {LRRC_LNAS_ACCESS_GRANT_MO_SIGNAL_AND_MO_CSFB_AND_MT,       0xf2},

};

VOS_UINT32 ulGrantTypeNum = sizeof(g_astGrantActTable) / sizeof(NAS_EMM_GRANT_ACT_STRU);


/*******************************************************************************
  Module   :
  Function : NAS_EMM_CheckTinEnterRegNormal
  Input    :ulTARslt---------TAI is in TAI LIST??
  Output   :
  NOTE     :��TAUʧ��ʱ���ж��ܷ����REG+NORMAL_SERVICE ״̬
  Return   :
  History  :
    1.  wangchen 00209181        2012-04-16
    2.  leixiantiao 00258641     2015-06-24 DTS2015061001947������CS PAGING����
*******************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMM_CheckEnterRegNormal(VOS_VOID)
{
    VOS_UINT32                          ulRslt = NAS_EMM_FAIL;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType = MMC_LMM_TIN_INVALID;

    ulRslt = NAS_EMM_CheckMutiModeSupport();
    ulTinType = NAS_EMM_GetTinType();

    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_TIN=", ulTinType);
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_CheckEnterRegNormal_ENUM,LNAS_EMM_TIN_TYPE,
                                        ulTinType);
    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_UPDATE_STATE=",(NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat));
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_CheckEnterRegNormal_ENUM,LNAS_FUNCTION_LABEL1,
                                        (NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat));
    /* 24301Э��5.5.3.2.6���ж���ӦTAUʧ�ܵ�������:
        b)  Lower layer failure or release of the NAS signalling connection without "Extended wait time" received from lower layers before the TRACKING AREA UPDATE ACCEPT or TRACKING AREA UPDATE REJECT message is received
            The tracking area updating procedure shall be aborted, and the UE shall proceed as described below.
        c)  T3430 timeout
            The UE shall abort the procedure and proceed as described below. The NAS signalling connection shall be released locally.
        d)  TRACKING AREA UPDATE REJECT, other causes than those treated in subclause 5.5.3.2.5, and cases of EMM cause values  #22 and #25, if considered as abnormal cases according to subclause 5.5.3.2.5
            If the tracking area updating request is not for initiating a PDN connection for emergency bearer services, upon reception of the EMM causes #95, #96, #97, #99 and #111 the UE should set the tracking area updating attempt counter to 5.
            The UE shall proceed as described below.
        .....
        For the cases b, c and d, if the tracking area updating request is not for initiating a PDN connection for emergency bearer services, the tracking area updating attempt counter shall be incremented, unless it was already set to 5.
        If the tracking area updating attempt counter is less than 5, and the TAI of the current serving cell is included in the TAI list, and the EPS update status is equal to EU1 UPDATED and the TIN does not indicate "P-TMSI":
            the UE shall keep the EPS update status to EU1 UPDATED and enter state EMM-REGISTERED.NORMAL-SERVICE. The UE shall start timer T3411.
            If in addition the TRACKING AREA UPDATE REQUEST indicated "periodic updating", the timer T3411 may be stopped when the UE enters EMM-CONNECTED mode.
            If timer T3411 expires the tracking area updating procedure is triggered again
        Э���в�Ϊ��PS�������Ρ�DRX�ı����UE���������ı䷢���TAU�����⴦��,���TAU Other Cause Fail,EMM״̬��Ӧ��ת��REG+ATTEMP_TO_UPDATE̬ */

    /* TA��TAI LIST && EUֵΪEU1 && L��ģ���߶�ģ��TIN����P-TMSI���ɽ��� */
    if(   (NAS_EMM_SUCC == NAS_EMM_TAU_IsCurrentTAInTaList())
        && (EMM_US_UPDATED_EU1 == (NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat))
        && ((NAS_EMM_FAIL == ulRslt)
                || (    (NAS_EMM_SUCC == ulRslt)
                     && (MMC_LMM_TIN_P_TMSI != ulTinType))))
    {
#if(FEATURE_ON == FEATURE_CSG)
        if((NAS_EMM_YES == NAS_LMM_IsCsgCampOn())
            &&(NAS_EMM_FAIL == NAS_EMM_TAU_IsCsgIdInAllowedOrOperatorCsgList()))
        {
            return NAS_EMM_FAIL;
        }
#endif
        return NAS_EMM_SUCC;
    }
    return NAS_EMM_FAIL;

}

/*******************************************************************************
  Module   :
  Function : Nas_Emm_TAU_RcvT3440Exp
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  �¹�����
*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_RcvT3440Exp()
{

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "Nas_Emm_Tau_RcvT3440Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RcvT3440Exp_ENUM,LNAS_ENTRY);

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_NOT_BARRED);

    return;
}

/*******************************************************************************
  Module   :
  Function : Nas_Emm_TAU_RcvT3430Exp
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.17  �¹�����
    2.  lihong  00150010  2012.12.14  Modify:Emergency
*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_RcvT3430Exp()
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "Nas_Emm_Tau_RcvT3430Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RcvT3430Exp_ENUM,LNAS_ENTRY);

    NAS_EMM_TAU_ProcAbnormal();

    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_RcvT3430Exp:CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RcvT3430Exp_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqTauAbnormalCommProc(   NAS_EMM_MmcSendTauActionResultIndTimerExp,
                                                (VOS_VOID*)NAS_EMM_NULL_PTR,
                                                EMM_SS_DEREG_NORMAL_SERVICE);

        /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

        return;
    }

    /****����ͻ��־������Ӧ�Ĵ���********************/
    NAS_EMM_TAU_RelIndCollisionProc(NAS_EMM_MmcSendTauActionResultIndTimerExp,
                    (VOS_VOID*)NAS_EMM_NULL_PTR);



    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;

}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_ProcAbnormal
 Description     : ����TAU�쳣���ͽ��е��쳣����
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.sunjitan 00193151    2012-07-17  Draft Enact
    2.lihong 00150010      2012-12-18  Modify:Emergency
*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_ProcAbnormal(VOS_VOID)
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_ProcAbnormal is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ProcAbnormal_ENUM,LNAS_ENTRY);

    /* TAU���Դ���С��5 */
    if(NAS_EMM_TAU_ATTEMPT_CNT_MAX > NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        if(NAS_EMM_SUCC == NAS_EMM_CheckEnterRegNormal())
        {
            /*������ʱ��T3411*/
            NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3411);
            NAS_EMM_TranStatePsNormalServiceOrPsLimitService();
            /*ת��EMM״̬��MS_REG+EMM_SS_REG_NORMAL_SERVICE*/
            /*NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE, TI_NAS_EMM_PTL_T3411);*/

            return;
        }

        /* ���Դ���С��5���ǲ��ܽ���NORMAL SERVICE̬ */
        /*������ʱ��T3411*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3411);

        /*����EPS״̬ΪEU2*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

        if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
        {
            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }

        /*ת��EMM״̬��MS_REG+SS_NORMAL_SERVICE*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE, TI_NAS_EMM_STATE_NO_TIMER);

        return;
    }

    /* TAU���Դ�������5 */

    /* ������T3402ʱ���ж�PLMN �Ƿ��� EPLMN LIST�У�������ڣ�������ΪĬ��ֵ */
    if (VOS_TRUE== NAS_LMM_CheckModifyT3402DefaultValue())
    {
        /*T3402����ΪĬ��ֵ*/
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3402,NAS_LMM_TIMER_T3402_LEN);
        /* AT&T��������3402ʱ�������֪ͨMMC */
        if(NAS_LMM_TIMER_T3402_LEN != NAS_EMM_GetEmmInfoDamParaT3402Len())
        {
            NAS_EMM_GetEmmInfoDamParaT3402Len() = NAS_LMM_TIMER_T3402_LEN;
            NAS_EMM_SendMMCT3402LenNotify(NAS_LMM_TIMER_T3402_LEN);
        }
        /* T3402�������޸ģ���Ҫд���Ӧ��ȫ�ֱ��� */
        g_ulEmmT3402length  = NAS_LMM_TIMER_T3402_LEN;
    }


    /*������ʱ��T3402*/
    NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);

    /*����EPS״̬ΪEU2*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*����PS LOC��Ϣ*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }

    /*�����ǰTAUΪ�������ͣ��޸�TAU����ԭ��ֵ*/
    if (NAS_EMM_TAU_START_CAUSE_T3412EXP == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
    }

    /*ת��EMM״̬��MS_REG+SS_ATTEMPT_TO_UPDATE*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE, TI_NAS_EMM_STATE_NO_TIMER);

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_TAU_ProcCause161722TauAttemptCont
 Description     : TAU�ɹ���EPS ONLY��ԭ��ֵΪ16,17,22ʱ������
                   TAU�ɹ���TA UPDATED ONLY��ԭ��ֵΪ16,17,22ʱ��
                   ����TAU ATTEMPTIMG UPDATE COUNTERֵ���д���
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.leili 00132387      2011-7-12  Draft Enact
    2.lihong00150010      2012-12-19 Modify:Emergency

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_ProcCause161722TauAttemptCont(VOS_VOID )
{
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32                   ulLteUeMode;
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_ProcCause161722TauAttemptCont is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ProcCause161722TauAttemptCont_ENUM,LNAS_ENTRY);

    ulLteUeMode  = NAS_LMM_GetEmmInfoUeOperationMode();
    if (VOS_TRUE == NAS_EMM_IsEnterRegLimitService())
    {
        NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_MmcSendTauActionResultIndSucc();

        return;
    }

    if (NAS_EMM_TAU_ATTEMPT_CNT_MAX > NAS_EMM_TAU_GetEmmTAUAttemptCnt())
    {
        /*������ʱ��TI_NAS_EMM_PTL_T3411*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3411);


        /*�޸�״̬��������״̬REG��״̬ATTACH_WAIT_ESM_BEARER_CNF*/
        NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                        EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_MmcSendTauActionResultIndSucc();

    }
    else
    {
        if (NAS_LMM_UE_CS_PS_MODE_1 == ulLteUeMode)
        {
            NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_TRUE);
        }
        else if (NAS_LMM_UE_CS_PS_MODE_2 == ulLteUeMode)
        {
            NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);
        }
        else
        {
        }

        /*�޸�״̬��������״̬REG��״̬EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM*/
        NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                    EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                    TI_NAS_EMM_PTL_T3402);

        NAS_EMM_MmcSendTauActionResultIndSucc();

        /*NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);*/

        /* �����NAS_EMM_TAU_ProcCause161722TauAttemptCont�����ĳ�������IDLE����
           ��TAU������CS/PS1�ĳ������Զ��ȴ��������ͷ���·������LMM�����ͷ���· */
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_TAU_ProcCause161722TauAttemptCont
 Description     : attach�ɹ���EPS ONLY��ԭ��ֵΪ22ʱ������
                   TAU�ɹ���TA UPDATED ONLY��ԭ��ֵΪ22ʱ��
                   ����TAU ATTEMPTIMG UPDATE COUNTERֵ���д���(R11�汾)
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.chengmin 00285307      2015-06-03  Draft Enact for DTS2015052506967

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_ProcCause22TauAttemptContR11(VOS_VOID )
{
    NAS_EMM_ATTACH_LOG_INFO("NAS_EMM_TAU_ProcCause22TauAttemptContR11 is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ProcCause22TauAttemptContR11_ENUM,LNAS_ENTRY);

    if (VOS_TRUE == NAS_EMM_IsEnterRegLimitService())
    {
        NAS_EMM_AdStateConvert(         EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

        NAS_EMM_MmcSendTauActionResultIndSucc();

        return;
    }

    NAS_LMM_Start3402Timer(NAS_LMM_TIMER_161722Atmpt5CSPS1_FALSE);

    /*�޸�״̬��������״̬REG��״̬EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM*/
    NAS_EMM_AdStateConvert(     EMM_MS_REG,
                                    EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,
                                    TI_NAS_EMM_PTL_T3402);

    NAS_EMM_MmcSendTauActionResultIndSucc();

    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_TAU_ProcEnterForbTA
 Description     : TauInit.WtTauCnf״̬���յ�SYS_INFO����Я����ֹ��Ϣ����ֹTAU���̣�
                   �ͷ����Ӻ󣬴��� Collision��־
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-10-25  Draft Enact
    2.lihong 00150010           2011-09-29  Modify combined detach

*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_ProcEnterForbTA
(
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 ulForbInfo
)
{

    /* ����Collison��־���� ��ͬ����*/
    switch(NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        case    NAS_EMM_COLLISION_DETACH   :

                /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
                NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&ulForbInfo);

                /* �����IMSI DETACH���򱾵�CS��ȥע�ᣬ����REG+LIMIT_SERVICE;
                   ���򱾵�PS��ȥע�ᣬ����DEREG+LIMMIT_SERVICE */
                if (MMC_LMM_MO_DET_CS_ONLY != NAS_EMM_GLO_AD_GetDetTypeMo())
                {
                    NAS_EMM_TAU_LOG_NORM( "NAS_EMM_TAU_ProcEnterForbTA : Process EPS Detach or EPS/IMSI Detach.");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ProcEnterForbTA_ENUM,LNAS_FUNCTION_LABEL1);

                    /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
                    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                                EMM_SS_DEREG_LIMITED_SERVICE,
                                                TI_NAS_EMM_STATE_NO_TIMER);

                    NAS_EMM_TAU_CollisionDetachProc();

                    /* ����DETACH*/
                    NAS_LMM_DeregReleaseResource();
                }
                else
                {
                    NAS_EMM_TAU_LOG_NORM( "NAS_EMM_TAU_ProcEnterForbTA : Process Imsi Detach.");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ProcEnterForbTA_ENUM,LNAS_FUNCTION_LABEL2);

                    /* ����ע����ΪPS */
                    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

                    NAS_EMM_TAU_CollisionDetachProc();

                    /* IMSI DETACH���ͷ���Դ ,������ڸ�APP�ϱ����֮�󣬷���DETACH TYPE
                    �᲻��ȷ*/
                    NAS_LMM_ImsiDetachReleaseResource();
                }

                break;

        case    NAS_EMM_COLLISION_SERVICE    :

                /* ��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ�ŵ���ͻ�����д��� */
                NAS_EMM_TAU_CollisionServiceProc(NAS_EMM_MmcSendTauActionResultIndForbType,
                                (VOS_VOID*)&ulForbInfo,
                                NAS_EMM_TRANSFER_RAT_ALLOW);
                break;

        default :
                NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_ProcEnterForbTA : NO Collision.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_ProcEnterForbTA_ENUM,LNAS_FUNCTION_LABEL3);

                /*��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ*/
                NAS_EMM_MmcSendTauActionResultIndForbType((VOS_VOID*)&ulForbInfo);
                break;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_TAU_MsRegMsgRelInd
 Description     : �ȶ���ע��״̬�£��յ�RRC REL IND������ԭ�򣬿��ܴ���TAU
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410              2009-5-14  Draft Enact
    2.X00148705           2009-11-13 �޸ĺ��ع�
    3leixiantiao 00258641 2015-07-23 �ؼ���Ϣ�ϱ�
*****************************************************************************/
VOS_VOID    NAS_EMM_TAU_MsRegMsgRelInd( LRRC_LNAS_REL_CAUSE_ENUM_UINT32   enRelCause )
{
    NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32   enTauStartType = NAS_LMM_OM_TAU_START_TYPE_OTHERS;

    if(LRRC_LNAS_REL_CAUSE_LOAD_BALANCE_REQ         ==    enRelCause)
    {
        /*NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_RRC_REL_LOAD_BALANCE);*/
        NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
        NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE);
        enTauStartType  = NAS_LMM_OM_TAU_START_TYPE_LOAD_BALANCE;
    }
    else if(LRRC_LNAS_REL_CAUSE_CONN_FAIL           ==    enRelCause)
    {
        /* ����ϴ�TAU�ɹ������¸�ֵ
        */
        if(NAS_EMM_TRIGGER_TAU_RRC_REL_NO        ==  NAS_LMM_GetEmmInfoTriggerTauRrcRel())
        {
            /*NAS_EMM_TAU_SaveEmmTAUStartCause(     NAS_EMM_TAU_START_CAUSE_RRC_REL_CONN_FAILURE);*/
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE);
        }
        enTauStartType  = NAS_LMM_OM_TAU_START_TYPE_CONN_FAIL;
    }
    else
    {
        /* ����ԭ�򲻻ᵼ��TAU�������� */;
        NAS_EMM_TAU_LOG1_INFO("NAS_EMM_TAU_MsRegMsgRelInd: enRelCause = ", enRelCause);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_TAU_MsRegMsgRelInd_ENUM,LNAS_EMM_REL_CAUSE,enRelCause);

        return;
    }

    /* �ж��Ƿ��������Pending*/
    NAS_EMM_TAU_IsUplinkPending();
    /* �������TAU����ԭ�� */
    NAS_EMM_TAU_StartTAUREQ(enTauStartType);

    return;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsTAUInitSsWaitCNCnfMsgT3430Exp
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  �¹�����
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsTauInitSsWaitCNCnfMsgT3430Exp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               )
{
    VOS_UINT32                                  ulRslt              = NAS_EMM_FAIL;

    (VOS_VOID)ulMsgId;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_NORM("Nas_Emm_MsTauInitSsWaitCNCnfMsgT3430Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCNCnfMsgT3430Exp_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        /* ��ӡ�쳣 */
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitSsWaitCNCnfMsgT3430Exp_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*TAU ATTEMPT COUNT ++*/
    NAS_EMM_TAU_GetEmmTAUAttemptCnt()++;

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_EMM_SendMtcTAUEndType();
#endif

    /* ������:�ڸ�MMC����TAU���ǰ������TAU EXP���� */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_EXP);
    /*������Ϣ������*/
    NAS_EMM_TAU_RcvT3430Exp();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd
 Description     : ����RRC_REL_IND ��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.X00148705    2009-9-30  Draft Enact
    2.X00148705    2009-11-13 �޸ĺ��ع�
    3.Z00148421    2010-12-22 DTS2010111701490:CONN_FAIL�� LOAD_BALANCE_REQԭ��ֵ
                              ����������TAU���յ�SYS_INFO_IND�ٴ�����
    4.Z00148421    2011-02-15 DTS2011021401149
    5.Z00148421    2011-02-22 DTS2011022203339:����DETACH_COLLISION,�������ͷ�
                              ԭ��ֵ����ɱ���DETACH
    6.l00150010    2011-09-29 combined detach
    7.l00212067    2013-03-05 Load Balance��Conn Fail����ԭ��ֵ��������TAUʧ�ܴ���
    8.l00150010    2012-12-14 Modify:Emergency
*****************************************************************************/
VOS_VOID  NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd( VOS_UINT32 ulCause )
{

    NAS_EMM_TAU_LOG_INFO(                         "NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd_ENUM,LNAS_ENTRY);

    /*common process*/
    NAS_LMM_StopStateTimer(                        TI_NAS_EMM_STATE_TAU_T3430);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_EMM_SendMtcTAUEndType();
#endif

    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd:CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqTauAbnormalCommProc(   NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                                                (VOS_VOID*)NAS_EMM_NULL_PTR,
                                                EMM_SS_DEREG_NORMAL_SERVICE);

        NAS_EMM_CommProcConn2Ilde();

        return;
    }
    NAS_EMM_TAU_GetEmmTAUAttemptCnt()++;

    /*������DETACH_COLLISION��־������ݲ�ͬ�ͷ�ԭ��ֵ����*/
    switch(ulCause)
    {
        /* RRC����IDLE̬�����´���TAU*/
        case LRRC_LNAS_REL_CAUSE_NAS_DATA_ABSENT:
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd:DATA ABSENT.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd_ENUM,LNAS_FUNCTION_LABEL2);

            /*send INTRA_CONN2IDLE_REQ����������״̬*/
            NAS_EMM_CommProcConn2Ilde();

            /* �ж��Ƿ��������Pending*/
            NAS_EMM_TAU_IsUplinkPending();

            /* ����TAU*/
            /* �������TAU����ԭ�� */
            NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_OTHERS);
            return;
        case LRRC_LNAS_REL_CAUSE_L2GU_REDIRECT:
        case LRRC_LNAS_REL_CAUSE_CSFB_HIGH_PRIOR:
            /* CSFB������TAU���̳�ͻ,���յ��ͷ�ԭ��ֵΪ: L2GU_REDIRECT����CSFB_HIGH_PRIORʱ,����MMC�ϱ�CSFBʧ��,�����ض���2G,��ֹ������2G,�ҵ绰ʱ�޷�FR��LTE */
            if((NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
                &&(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
            {
                NAS_EMM_TAU_ProcAbnormal();
                /* ��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ */
                NAS_EMM_MmcSendTauActionResultIndFailWithPara((VOS_VOID*)NAS_EMM_NULL_PTR);
                /* �����ͻ��־ */
                NAS_EMM_TAU_SaveEmmCollisionCtrl( NAS_EMM_COLLISION_NONE);

                /* ���Active Flag */
                NAS_EMM_TAU_SaveEmmTauReqActiveCtrl(NAS_EMM_TAU_NO_BEARER_EST_REQ);

                /**����������ݵı�־��������**************/
                NAS_EMM_SerClearEsmDataBuf();
                NAS_EMM_CommProcConn2Ilde();
                return;
            }
            NAS_EMM_TAU_ProcAbnormal();

            /* ��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ�ڳ�ͻ�ڲ����� */
            NAS_EMM_TAU_RelIndCollisionProc(NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                               (VOS_VOID*)NAS_EMM_NULL_PTR);
            break;
        default:

            NAS_EMM_TAU_ProcAbnormal();

            /* ��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ�ڳ�ͻ�ڲ����� */
            NAS_EMM_TAU_RelIndCollisionProc(NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                               (VOS_VOID*)NAS_EMM_NULL_PTR);
            break;
    }

    /*send INTRA_CONN2IDLE_REQ����������״̬*/
    NAS_EMM_CommProcConn2Ilde();

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitSsWaitCnCnfMsgAuthRej
 Description     : TauInit.WtCnTauCnf״̬���յ�AUTH REJ��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2009-10-31  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_MsTauInitSsWaitCnCnfMsgAuthRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsTauInitSsWaitCnCnfMsgAuthRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCnCnfMsgAuthRej_ENUM,LNAS_ENTRY);

    /* ��Ȩ�ܾ��Ż����� */
    if (NAS_EMM_YES == NAS_EMM_IsNeedIgnoreHplmnAuthRej())
    {
        return  NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_MsTauInitSsWaitCnTauCnfProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);

    return NAS_LMM_MSG_HANDLED;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsTauInitSsWaitCnCnfMsgRrcRelInd
             ����RRC_REL_IND��Ϣ
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  �¹�����
    2.  X00148705         2009.09.30  �ع�
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsTauInitSsWaitCnCnfMsgRrcRelInd(
                                                  VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru)
{
    LRRC_LMM_REL_IND_STRU                 *pRrcRelInd     = (LRRC_LMM_REL_IND_STRU *)pMsgStru;
    VOS_UINT32                          ulCause;

    (VOS_VOID)ulMsgId;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsTauInitSsWaitCnCnfMsgRrcRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCnCnfMsgRrcRelInd_ENUM,LNAS_ENTRY);
    /* ������:�ڸ�MMC����TAU���ǰ������TAU REL FAIL���� */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_LRRC_REL);
    /*���ԭ��ֵ*/
    ulCause                                             =   pRrcRelInd->enRelCause;

    NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd(           ulCause);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsTauInitSsWaitCnCnfMsgDrbSetupInd
 Description     : �ڵȴ�TAU acp��Ϣ�������յ�Drb�����ɹ���Ϣ�Ĵ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2010-10-8  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_MsTauInitSsWaitCnCnfMsgDrbSetupInd(
                                                  VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru)
{
    (VOS_VOID)ulMsgId;
    (VOS_VOID)pMsgStru;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsTauInitSsWaitCnCnfMsgDrbSetupInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCnCnfMsgDrbSetupInd_ENUM,LNAS_ENTRY);

    /*TAU�����У��ڵȴ�������Ӧʱ���յ��ײ�Drb�����ɹ�����Ϣ��
      Ϊ�˱�������TAU������ɺ��ͷ���·����Ҫ������TAU������Ϊ��Я����active flag��TAU����*/
    NAS_EMM_TAU_SaveEmmTauReqActiveCtrl(NAS_EMM_TAU_WITH_BEARER_EST_REQ);
#if (FEATURE_LPP == FEATURE_ON)
    if (NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        if (NAS_EMM_SER_START_CAUSE_LPP_EST_REQ == NAS_EMM_SER_GetEmmSERStartCause())
        {
            NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_SUCC);
            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
        }

        if (NAS_EMM_SER_START_CAUSE_SS_EST_REQ == NAS_EMM_SER_GetEmmSERStartCause())
        {
            NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_SUCC,
                                    NAS_EMM_SER_GetSsOrLppOpid());

            NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
        }
    }
#endif
    if(NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        /* ������: ����SER�ɹ����� */
        NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_SUCC);
        /* ������: ��¼Ser���̽���ʱ�� */
        NAS_EMM_SaveSerEndTimeStamp();
    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SetBarInfo
 Description     : ������Ӧ��BAR���̺�BAR����
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2010-8-23  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SetBarInfo(NAS_EMM_BAR_PROCEDURE_ENUM_UINT32 enBarProc,
                            LRRC_LNAS_EST_RESULT_ENUM_UINT32 enBarType)
{
    /*Coverity �澯���� 2013-9-26 Begin*/
    NAS_EMM_BAR_PROCEDURE_ENUM_UINT32 enBarProcOld;
    /*Coverity �澯���� 2013-9-26 End*/

    /*���Bar������:TAU or SER */
    if ((NAS_EMM_BAR_PROCEDURE_TAU != enBarProc)
      &&(NAS_EMM_BAR_PROCEDURE_SERVICE != enBarProc))
    {
        NAS_EMM_TAU_LOG_ERR("NAS_EMM_SetBarInfo:Input enBarProc Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SetBarInfo_ENUM,LNAS_ERROR);
        return;
    }

    /*Coverity �澯���� 2013-9-26 Begin*/
    enBarProcOld = NAS_EMM_TAU_GetRegBarProcedure();
    /*Coverity �澯���� 2013-9-26 End*/

    /*�����Ч:��¼Bar�����̺�����*/
    NAS_EMM_TAU_SetRegBarProcedure(enBarProc);

    switch (enBarType)
    {
        case LRRC_EST_ACCESS_BARRED_MO_SIGNAL:
            NAS_EMM_TAU_GetRegBarType() |= NAS_EMM_BIT_1;
            break;

        case LRRC_EST_ACCESS_BARRED_ALL:
            NAS_EMM_TAU_GetRegBarType() |= NAS_LMM_LOW_HALF_BYTE_F;
            break;

        case LRRC_EST_ACCESS_BARRED_MO_CALL:
            NAS_EMM_TAU_GetRegBarType() |= NAS_EMM_BIT_2;
            break;

        case LRRC_EST_ACCESS_BARRED_MO_CSFB:
            NAS_EMM_TAU_GetRegBarType() |= NAS_EMM_BIT_4;
            break;

        case LRRC_EST_ACCESS_BARRED_MO_CALL_AND_CSFB:
            NAS_EMM_TAU_GetRegBarType() |= 0x0a;
            break;

         case LRRC_EST_ACCESS_BARRED_MT_CALL:
            NAS_EMM_TAU_GetRegBarType() |= NAS_EMM_BIT_3;
            break;

        default:
            /*Coverity �澯���� 2013-9-26 Begin*/
            NAS_EMM_TAU_SetRegBarProcedure(enBarProcOld);
            NAS_EMM_TAU_LOG_ERR("NAS_EMM_SetBarInfo:Input enBarType Err.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SetBarInfo_ENUM,LNAS_FUNCTION_LABEL1);
            /*Coverity �澯���� 2013-9-26 End*/
            break;
    }
    return;
}
/* leixiantiao 00258641 �ع���������Ȧ���Ӷ� 2014-7-30 begin */
/*****************************************************************************
 Function Name   : NAS_EMM_IsBarTypeMoSingal
 Description     : ����bitλ�ж�BAR�����Ƿ�ΪMO SIGNAL
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leixiantiao  00258641      2014-7-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_IsBarTypeMoSingal(VOS_VOID)
{
    /*bit1 Ϊ1����ʶMO SIGNAL���ͱ�bar*/
    if(NAS_EMM_BIT_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_1))
    {
        return NAS_EMM_SUCC;
    }
    else
    {
        return NAS_EMM_FAIL;
    }

}
/*****************************************************************************
 Function Name   : NAS_EMM_IsBarTypeMoCall
 Description     : ����bitλ�ж�BAR�����Ƿ�ΪMO CALL
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leixiantiao  00258641      2014-7-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_IsBarTypeMoCall(VOS_VOID)
{
    /*bit2 Ϊ1����ʶMO CALL���ͱ�bar*/
    if(NAS_EMM_BIT_SLCT == ((NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_2)>> NAS_LMM_MOVEMENT_1_BITS))
    {
        return NAS_EMM_SUCC;
    }
    else
    {
        return NAS_EMM_FAIL;
    }

}
/*****************************************************************************
 Function Name   : NAS_EMM_IsBarTypeMt
 Description     : ����bitλ�ж�BAR�����Ƿ�ΪMT CALL
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leixiantiao  00258641      2014-7-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_IsBarTypeMt(VOS_VOID)
{
    /*bit3 Ϊ1����ʶMT CALL���ͱ�bar*/
    if(NAS_EMM_BIT_SLCT == ((NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_3)>>NAS_LMM_MOVEMENT_2_BITS))
    {
        return NAS_EMM_SUCC;
    }
    else
    {
        return NAS_EMM_FAIL;
    }

}
/*****************************************************************************
 Function Name   : NAS_EMM_IsBarTypeMoCsfb
 Description     : ����bitλ�ж�BAR�����Ƿ�ΪMO CSFB
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leixiantiao  00258641      2014-7-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_IsBarTypeMoCsfb(VOS_VOID)
{
    /*bit4 Ϊ1����ʶMO CSFB���ͱ�bar*/
    if(NAS_EMM_BIT_SLCT == ((NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_4)>>NAS_LMM_MOVEMENT_3_BITS))
    {
        return NAS_EMM_SUCC;
    }
    else
    {
        return NAS_EMM_FAIL;
    }

}
/*****************************************************************************
 Function Name   : NAS_EMM_IsBarTypeMoCallAndCsfb
 Description     : ����bitλ�ж�BAR�����Ƿ�ΪMO CALL& MO CSFB
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leixiantiao  00258641      2014-7-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_IsBarTypeMoCallAndCsfb(VOS_VOID)
{
    /*bit4&bit2 Ϊ1����ʶMO CALL& MO CSFB���ͱ�bar*/
    if((NAS_EMM_BIT_SLCT == ((NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_4)>>NAS_LMM_MOVEMENT_3_BITS))
        && (NAS_EMM_BIT_SLCT == ((NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_2)>>NAS_LMM_MOVEMENT_1_BITS)))
    {
        return NAS_EMM_SUCC;
    }
    else
    {
        return NAS_EMM_FAIL;
    }
}
/* leixiantiao 00258641 �ع���������Ȧ���Ӷ� 2014-7-30 end */

/*****************************************************************************
 Function Name   : NAS_EMM_JudgeBarType
 Description     : �ж��Ƿ���ĳ�����͵�bar
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2010-8-25  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_JudgeBarType( NAS_EMM_BAR_TYPE_ENUM_UINT32 enBarType )
{
    VOS_UINT32 ulRslt;
    /* leixiantiao 00258641 �ع���������Ȧ���Ӷ� 2014-7-30 begin */
    if( NAS_EMM_BAR_TYPE_MO_SIGNAL == enBarType)
    {
        ulRslt = NAS_EMM_IsBarTypeMoSingal();
    }
    else if(NAS_EMM_BAR_TYPE_MO_CALL == enBarType)
    {
        ulRslt = NAS_EMM_IsBarTypeMoCall();
    }
    else if(NAS_EMM_BAR_TYPE_MT == enBarType)
    {
        ulRslt = NAS_EMM_IsBarTypeMt();
    }
    else if(NAS_EMM_BAR_TYPE_MO_CSFB == enBarType)
    {
        ulRslt = NAS_EMM_IsBarTypeMoCsfb();
    }
    else if(NAS_EMM_BAR_TYPE_MO_CALL_AND_CSFB == enBarType)
    {
        ulRslt = NAS_EMM_IsBarTypeMoCallAndCsfb();
    }
    else
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_JudgeBarType: Bar type is err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_JudgeBarType_ENUM,LNAS_ERROR);
        ulRslt = NAS_EMM_FAIL;
    }
    return ulRslt;
    /* leixiantiao 00258641 �ع���������Ȧ���Ӷ� 2014-7-30 end */
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetBarType
 Description     : ��ȡ��ǰ�ı�bar����:MO-SIGNAL��MO-CALL��BARRED_ALL
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leili  00132387      2010-8-23  Draft Enact

*****************************************************************************/
/*VOS_UINT32  NAS_EMM_GetBarType (VOS_VOID )
{
    NAS_EMM_BAR_TYPE_ENUM_UINT32 enBarType = NAS_EMM_BAR_TYPE_BUTT;

    if ((NAS_EMM_BIT_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_1))
        && (NAS_EMM_BIT_NO_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_2)>>NAS_LMM_MOVEMENT_1_BITS)
        && (NAS_EMM_BIT_NO_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_3)>>NAS_LMM_MOVEMENT_2_BITS))
    {
        enBarType = NAS_EMM_BAR_TYPE_MO_SIGNAL;
    }
    else if ((NAS_EMM_BIT_NO_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_1))
             &&(NAS_EMM_BIT_SLCT == ((NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_2)>> NAS_LMM_MOVEMENT_1_BITS))
             && (NAS_EMM_BIT_NO_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_3)>>NAS_LMM_MOVEMENT_2_BITS))

    {
        enBarType = NAS_EMM_BAR_TYPE_MO_CALL;
    }
    else if ((NAS_EMM_BIT_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_1))
            && (NAS_EMM_BIT_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_2)>>NAS_LMM_MOVEMENT_1_BITS)
            && (NAS_EMM_BIT_SLCT ==(NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_3)>>NAS_LMM_MOVEMENT_2_BITS))
    {
        enBarType = NAS_EMM_BAR_TYPE_ALL;
    }
    else if ((NAS_EMM_BIT_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_1))
            && (NAS_EMM_BIT_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_2)>>NAS_LMM_MOVEMENT_1_BITS)
            && (NAS_EMM_BIT_NO_SLCT ==(NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_3)>>NAS_LMM_MOVEMENT_2_BITS))
    {
        enBarType = NAS_EMM_BAR_TYPE_MO;
    }
    else if ((NAS_EMM_BIT_NO_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_1))
            && (NAS_EMM_BIT_NO_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_2)>>NAS_LMM_MOVEMENT_1_BITS)
            && (NAS_EMM_BIT_SLCT ==(NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_3)>>NAS_LMM_MOVEMENT_2_BITS))
    {
        enBarType = NAS_EMM_BAR_TYPE_MT;
    }
    else if ((NAS_EMM_BIT_NO_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_1))
            && (NAS_EMM_BIT_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_2)>>NAS_LMM_MOVEMENT_1_BITS)
            && (NAS_EMM_BIT_SLCT ==(NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_3)>>NAS_LMM_MOVEMENT_2_BITS))
    {
        enBarType = NAS_EMM_BAR_TYPE_MO_CALL_AND_MT;
    }
    else if ((NAS_EMM_BIT_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_1))
            && (NAS_EMM_BIT_NO_SLCT == (NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_2)>>NAS_LMM_MOVEMENT_1_BITS)
            && (NAS_EMM_BIT_SLCT ==(NAS_EMM_TAU_GetRegBarType() & NAS_EMM_BIT_3)>>NAS_LMM_MOVEMENT_2_BITS))
    {
        enBarType = NAS_EMM_BAR_TYPE_MO_SIGNAL_AND_MT;
    }
    else
    {
        ;
    }

    return enBarType;
}*/

/*****************************************************************************
 Function Name   : NAS_EMM_ClearBarType
 Description     : ���ݲ�ͬ�Ľ�bar���������Ӧ�ı�ʶλ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leili  00132387      2010-8-23  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClearBarType( LRRC_LNAS_ACCESS_GRANT_ENUM_UINT32 enBarType)
{
    VOS_UINT32                          i = 0;

    for(i = 0; i < ulGrantTypeNum; i++)
    {
        if (enBarType == g_astGrantActTable[i].enGrantType)
        {
            NAS_EMM_TAU_GetRegBarType() &= g_astGrantActTable[i].ucGrantValue;

            break;
        }
    }

}






VOS_VOID  NAS_EMM_ClearBarResouce(VOS_VOID)
{
    NAS_LMM_MEM_SET_S(  NAS_EMM_TAU_GetRegBarInfoAddr(),
                        sizeof(NAS_EMM_BAR_STRU),
                        0,
                        sizeof(NAS_EMM_BAR_STRU));

    return;
}


VOS_UINT32  NAS_EMM_GetBarProcedure(VOS_VOID )
{
    NAS_EMM_BAR_PROCEDURE_ENUM_UINT32   ulBarProc;

    ulBarProc = NAS_EMM_TAU_GetRegBarProcedure();

    return ulBarProc;
}


/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  �¹�����
    2.  Z00148421         2010-12-22  DTS2010111701490:��ӽ���ʧ��ԭ��ֵCELL_SEATCHING�Ĵ���
    3.  l00150010         2012-12-14  Modify:Emergency
*******************************************************************************/

VOS_UINT32 NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru)
{

    VOS_UINT32                          ulRslt                  = NAS_EMM_FAIL;
    NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU *pMrrcConnectFailRelInd  = NAS_EMM_NULL_PTR;
    MMC_LMM_TAU_RSLT_ENUM_UINT32        enTauRslt               = MMC_LMM_TAU_RSLT_ACCESS_BARED;
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg               = NAS_EMM_NULL_PTR;

    (VOS_VOID)ulMsgId;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd_ENUM,LNAS_ENTRY);

    /*check the input params and current states*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN( "NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd_ENUM,LNAS_ERROR);
        return NAS_LMM_MSG_DISCARD;
    }

    /*get the msg INTRA_REL_IND*/
    pMrrcConnectFailRelInd = (NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU *)pMsgStru;

    /*commom process*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_EMM_SendMtcTAUEndType();
#endif

    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd:CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd_ENUM,LNAS_FUNCTION_LABEL1);

        if ((LRRC_EST_ACCESS_BARRED_MO_SIGNAL == pMrrcConnectFailRelInd->enEstResult)
            || (LRRC_EST_ACCESS_BARRED_ALL == pMrrcConnectFailRelInd->enEstResult))
        {
            /* ������:�ڸ�MMC����TAU���ǰ������TAU Bar���� */
            NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_BAR);
            NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&enTauRslt);
        }
        else if (LRRC_EST_CELL_SEARCHING == pMrrcConnectFailRelInd->enEstResult)
        {
            /* ������:�ڸ�MMC����TAU���ǰ������TAU EST FAIL���� */
            NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL);
            enTauRslt = MMC_LMM_TAU_RSLT_FAILURE;
            NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&enTauRslt);
        }
        else
        {
            /* ������:�ڸ�MMC����TAU���ǰ������TAU EST FAIL���� */
            NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL);
            NAS_EMM_MmcSendTauActionResultIndFailWithPara((VOS_VOID*)NAS_EMM_NULL_PTR);
        }

        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

        /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
        NAS_LMM_DeregReleaseResource();

        /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
        NAS_EMM_MmcSendDetIndLocal( MMC_LMM_L_LOCAL_DETACH_OTHERS);

        NAS_EMM_CommProcConn2Ilde();

        if (LRRC_EST_CELL_SEARCHING == pMrrcConnectFailRelInd->enEstResult)
        {
            /* ��¼ATTACH����ԭ��ֵ */
            NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

            NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                        EMM_SS_DEREG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);
        }
        else
        {
            /*����ESM��Ϣ*/
            NAS_LMM_MEM_CPY_S(      (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                                    sizeof(NAS_EMM_CN_MSGCON_STRU),
                                    &(pstEsmMsg->stEsmMsg),
                                    (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);

            NAS_EMM_StartEmergencyAttach();
        }

        return NAS_LMM_MSG_HANDLED;
    }
    switch (pMrrcConnectFailRelInd->enEstResult)
    {
        case LRRC_EST_ACCESS_BARRED_MO_SIGNAL:
        case LRRC_EST_ACCESS_BARRED_ALL:
            /* ������:�ڸ�MMC����TAU���ǰ������TAU Bar���� */
            NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_BAR);
            /*����bar���̺�����*/
            NAS_EMM_SetBarInfo(NAS_EMM_BAR_PROCEDURE_TAU,pMrrcConnectFailRelInd->enEstResult);

            /*ת��EMM״̬��MS_REG+SS_WAIT_ACCESS_GRANT_IND*/
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                        EMM_SS_REG_WAIT_ACCESS_GRANT_IND,
                                        TI_NAS_EMM_STATE_NO_TIMER);

            NAS_EMM_TAU_RelIndCollisionProc(NAS_EMM_MmcSendTauActionResultIndOthertype,
                               (VOS_VOID*)&enTauRslt);
            break;

        /* ����ʧ�ܣ�RRC���ڽ���С��������Ǩ�Ƶ�Reg.Plmn_Search*/
        /*
        case LRRC_EST_CELL_SEARCHING:
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                        EMM_SS_REG_PLMN_SEARCH,
                                        TI_NAS_EMM_STATE_NO_TIMER);

            NAS_EMM_TAU_RelIndCollisionProc((NAS_LMM_SEND_TAU_RESULT_ACT_FUN)NAS_EMM_NULL_PTR,
                                 (VOS_VOID*)NAS_EMM_NULL_PTR);
            break;
        */

        default:
            /* ������:�ڸ�MMC����TAU���ǰ������TAU EST FAIL���� */
            NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL);
            NAS_EMM_TAU_GetEmmTAUAttemptCnt()++;

            NAS_EMM_TAU_ProcAbnormal();

            /* ��MMC����LMM_MMC_TAU_RESULT_IND��Ϣ�ڳ�ͻ�ڲ����� */
            NAS_EMM_TAU_RelIndCollisionProc(NAS_EMM_MmcSendTauActionResultIndFailWithPara,
                                 (VOS_VOID*)NAS_EMM_NULL_PTR);
            break;

    }

    /*send INTRA_CONN2IDLE_REQ����������״̬*/
    NAS_EMM_CommProcConn2Ilde();

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SndTauCompleteFailProc
 Description     : TAU CMP����ʧ��ʱ�Ĵ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen  00209181   2013-03-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SndTauCompleteFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataMsg = VOS_NULL_PTR;

    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;

    *pulIsDelBuff = VOS_TRUE;

    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(pstRrcMmDataCnf->ulOpId);

    if (NAS_EMM_NULL_PTR == pEmmMrrcMgmtData)
    {
        return NAS_EMM_FAIL;
    }

    /* ������Ϣ�ڴ�*/
    /* �տ���Ϣ�����ڴ�ֱ������1024�ֽڶ�����ʵ�ʳ���, ���:�������ڴ�Ϊʵ�ʳ���,
        �ڼ��ܼӱ�����, ���ϰ�ȫͷ����, �ڴ�Խ��6���ֽ����� */
    pMrrcDataMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)(VOS_VOID*)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    if(VOS_NULL_PTR == pMrrcDataMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SndTauCompleteFailProc: Mem Alloc Fail");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndTauCompleteFailProc_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*�������Ҫ�ش�TAU CMP��Ϣ�������TAU���̱���*/
    #if (FEATURE_ON == FEATURE_DSDS)
    if((LRRC_LMM_SEND_RSLT_FAILURE_TXN != pstRrcMmDataCnf->enSendRslt)
        && (LRRC_LMM_SEND_RSLT_FAILURE_RLF != pstRrcMmDataCnf->enSendRslt))
    {
        /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
        NAS_EMM_TAU_SendRrcDsdsEndNotify();
    }
    #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    if((LRRC_LMM_SEND_RSLT_FAILURE_TXN != pstRrcMmDataCnf->enSendRslt)
        && (LRRC_LMM_SEND_RSLT_FAILURE_RLF != pstRrcMmDataCnf->enSendRslt))
    {
        NAS_EMM_SendMtcTAUEndType();
    }
#endif

    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
            /*  ��Ҫ����Ӧ�Ļ�����Ϣ��ulHoWaitSysInfoFlag����Ϊtrue */
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_TRUE;
            *pulIsDelBuff = VOS_FALSE;

            break;

        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            pMrrcDataMsg->enDataCnf = LRRC_LMM_DATA_CNF_NEED;

            pMrrcDataMsg->enEmmMsgType = NAS_EMM_MSG_TAU_CMP;
            pMrrcDataMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
            pMrrcDataMsg->ulEsmMmOpId = pEmmMrrcMgmtData->ulEsmMmOpId;

            pMrrcDataMsg->stNasMsg.ulNasMsgSize = pEmmMrrcMgmtData->ulNasMsgLength;

            NAS_LMM_MEM_CPY_S(  pMrrcDataMsg->stNasMsg.aucNasMsg,
                                pEmmMrrcMgmtData->ulNasMsgLength,
                                pEmmMrrcMgmtData->aucNasMsgContent,
                                pEmmMrrcMgmtData->ulNasMsgLength);

            NAS_EMM_SndUplinkNasMsg(pMrrcDataMsg);


            break;

        case LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL:
        case LRRC_LMM_SEND_RSLT_FAILURE_CTRL_NOT_CONN:
            NAS_LMM_Stop3402Timer();
            NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3411);
            /* ������:����TAU COMM����DATA REQ����ʧ�ܴ��� */
            NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);
            NAS_EMM_TAU_SaveEmmTAUStartCause(NAS_EMM_TAU_START_CAUSE_OTHERS);
            NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE);
            break;

        default:
            break;
    }

    /*�ͷ��������ڴ� */
    NAS_LMM_MEM_FREE(pMrrcDataMsg);
    return NAS_EMM_SUCC;
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_EMM_SndTauReqFailProc
 Description     : TAU REQ����ʧ��ʱ�Ĵ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen  00209181   2013-03-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_SndTauReqFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff)
{
    LRRC_LMM_DATA_CNF_STRU              *pstRrcMmDataCnf = VOS_NULL_PTR;
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;

    enMainState                         = NAS_LMM_GetEmmCurFsmMS();

    *pulIsDelBuff = VOS_TRUE;

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (EMM_MS_TAU_INIT != enMainState)
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_SndTauReqFailProc: STATE ERR!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndTauReqFailProc_ENUM,LNAS_ERROR);
        return  NAS_EMM_SUCC;
    }

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_EMM_SendMtcTAUEndType();
#endif

    /* ������:�ڸ�MMC����TAU���ǰ������TAU DATA REQ Snd Fail���� */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL);
    pstRrcMmDataCnf = (LRRC_LMM_DATA_CNF_STRU*) pMsg;

    switch (pstRrcMmDataCnf->enSendRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
        /* NORF������ط�������ɶ�ʱ���ڲ����ط���������˸ó�����ֱ�Ӷ������ȴ�tau��ʱ����ʱ */
            /*����EPS״̬ΪEU2*/
            NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

            if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
            {
                /*����PS LOC��Ϣ*/
                NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
            }
            /*ֹͣT3430��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

            /*ֹͣT3440��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /* �������TAU����ԭ�� */
            NAS_EMM_TAU_StartTAUREQ(NAS_LMM_OM_TAU_START_TYPE_SND_MSG_FAIL);
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL:

            /*����EPS״̬ΪEU2*/
            NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

            if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
            {
                /*����PS LOC��Ϣ*/
                NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
            }

            /*����TAU_REQ����ʧ��ԭ����LRRC�ͷű�ʶ*/
            NAS_LMM_SetTauReqSndFailFlag(PS_TRUE);
            break;

        default:
            break;
        }

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SndTauCmpSuccProc
 Description     : TAU CMP���ͳɹ�ʱ�Ĵ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : 1.wangchen 00209181  2012-11-01  Draft Enact
                   2.sunjitan 00193151  2014-09-06  Mod: DTS2014090904779 ���GU��ѡ��L��SMC CMP���Ͳ��ɹ����µĺ����쳣
*****************************************************************************/
VOS_UINT32 NAS_EMM_SndTauCmpSuccProc(VOS_VOID* pMsg)
{

    (VOS_VOID)pMsg;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SndTauCmpSuccProc: entern");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndTauCmpSuccProc_ENUM,LNAS_ENTRY);
    NAS_EMM_TAU_SaveEmmTauCompleteFlag(NAS_EMM_TAU_COMPLETE_INVALID);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_EMM_SendMtcTAUEndType();
#endif

    /* s00193151 add DTS2014090904779 2014-09-06:
       SMC�ɹ�֮�󲻻�����ɾ��NEW MAPPED��ȫ�����ģ�Ϊ�������쳣����TAUʱ�����ּ���NEW MAPPED,
       ����TAU�ɹ�֮�����ɾ��������Ӱ�쵽�������� */
    NAS_EMM_ClearNewMappedSecuCntxt();
    /* ������:����TAU�ɹ����� */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_SUCC);
    /* ������: �����ϵͳTAU��־���ñ�־����ϵͳTAUʱ���� */
    NAS_EMM_SetOmInterTauFlag(NAS_EMM_NO);
    return NAS_EMM_SUCC;
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



