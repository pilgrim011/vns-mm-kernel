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
#include "LNasStkInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMTAUREJ_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMTAUREJ_C
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


NAS_LMM_TAU_REJ_CAUSE_PROC_STRU  gstEmmTauRejCauseProcTbl[]=
{
    {NAS_LMM_CAUSE_ILLEGAL_UE,                              NAS_EMM_TAU_TAUReqRejectCasue367},
    {NAS_LMM_CAUSE_ILLEGAL_ME,                              NAS_EMM_TAU_TAUReqRejectCasue367},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW,                      NAS_EMM_TAU_TAUReqRejectCasue367},
    {NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,     NAS_EMM_TAU_TAUReqRejectCasue8},
    {NAS_LMM_CAUSE_UE_ID_NOT_DERIVED,                       NAS_EMM_TAU_TAUReqRejectCasue9},
    {NAS_LMM_CAUSE_IMPLICIT_DETACHED,                       NAS_EMM_TAU_TAUReqRejectCasue10},
    {NAS_LMM_CAUSE_PLMN_NOT_ALLOW,                          NAS_EMM_TAU_TAUReqRejectCasue11},
    {NAS_LMM_CAUSE_TA_NOT_ALLOW,                            NAS_EMM_TAU_TAUReqRejectCasue12},
    {NAS_LMM_CAUSE_ROAM_NOT_ALLOW,                          NAS_EMM_TAU_TAUReqRejectCasue13},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,              NAS_EMM_TAU_TAUReqRejectCasue14},
    {NAS_LMM_CAUSE_NO_SUITABL_CELL,                         NAS_EMM_TAU_TAUReqRejectCasue15},
    {NAS_LMM_CAUSE_PROCEDURE_CONGESTION,                    NAS_EMM_TAU_TAUReqRejectCasue22},
#if(FEATURE_ON == FEATURE_CSG)
    {NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,             NAS_EMM_TAU_TAUReqRejectCasue25},
#endif
    {NAS_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,NAS_EMM_TAU_TAUReqRejectCasue35},
    {NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,         NAS_EMM_TAU_TAUReqRejectCasue40},
    {NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE,                  NAS_EMM_TAU_TAUReqRejectCasue42}
};
VOS_UINT32        gstEmmTauRejCauseProcTblLen = sizeof(gstEmmTauRejCauseProcTbl)
                                                / sizeof(NAS_LMM_TAU_REJ_CAUSE_PROC_STRU);


/*****************************************************************************
�ṹ����    :NAS_LMM_TAU_COLLISION_SER_RCV_CN_REJ_PROC_STRU
ʹ��˵��    :TAU���SER��ͻʱ�յ�����REJ��ͬԭ��ֵ�����
*****************************************************************************/
NAS_LMM_TAU_COLLISION_SER_RCV_CN_REJ_PROC_STRU  gstEmmTauCollisionSerRcvCnRejProcTbl[]=
{
    {NAS_LMM_CAUSE_ILLEGAL_UE,                                        NAS_EMM_TAU_TAUCollisionSerRejCasue3},
    {NAS_LMM_CAUSE_ILLEGAL_ME,                                        NAS_EMM_TAU_TAUCollisionSerRejCasue3},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_EMM_TAU_TAUCollisionSerRejCasue7},
    {NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_EMM_TAU_TAUCollisionSerRejCasue3},
    {NAS_LMM_CAUSE_UE_ID_NOT_DERIVED,                                 NAS_EMM_TAU_TAUCollisionSerRejCasue7},
    {NAS_LMM_CAUSE_IMPLICIT_DETACHED,                                 NAS_EMM_TAU_TAUCollisionSerRejCasue7},
    {NAS_LMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_EMM_TAU_TAUCollisionSerRejCasue7},
    {NAS_LMM_CAUSE_TA_NOT_ALLOW,                                      NAS_EMM_TAU_TAUCollisionSerRejCasue7},
    {NAS_LMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_EMM_TAU_TAUCollisionSerRejCasue7},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_EMM_TAU_TAUCollisionSerRejCasue7},
    {NAS_LMM_CAUSE_NO_SUITABL_CELL,                                   NAS_EMM_TAU_TAUCollisionSerRejCasue7},
    {NAS_LMM_CAUSE_PROCEDURE_CONGESTION,                              NAS_EMM_TAU_TAUCollisionSerRejCasue7},
#if(FEATURE_ON == FEATURE_CSG)
    {NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,                       NAS_EMM_TAU_TAUCollisionSerRejCasue7},
#endif
    {NAS_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,       NAS_EMM_NULL_PTR                    },
    {NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,                   NAS_EMM_TAU_TAUCollisionSerRejCasue7},
    {NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE,                            NAS_EMM_TAU_TAUCollisionSerRejCasue7}
};

VOS_UINT32 gstEmmTauCollisionSerRcvCnRejProcTblLen = sizeof(gstEmmTauCollisionSerRcvCnRejProcTbl)
                                        / sizeof(NAS_LMM_TAU_COLLISION_SER_RCV_CN_REJ_PROC_STRU);

/*****************************************************************************
�ṹ����    :NAS_LMM_TAU_COLLISION_DETACH_RCV_CN_REJ_PROC_STRU
ʹ��˵��    :TAU���DETACH��ͻʱ�յ�����REJ��ͬԭ��ֵ�����
*****************************************************************************/
NAS_LMM_TAU_COLLISION_DETACH_RCV_CN_REJ_PROC_STRU  gstEmmTauCollisionDetachRcvCnRejProcTbl[]=
{
    {NAS_LMM_CAUSE_ILLEGAL_UE,                                        NAS_EMM_TAU_TAUCollisionDetachRejCasue3 },
    {NAS_LMM_CAUSE_ILLEGAL_ME,                                        NAS_EMM_TAU_TAUCollisionDetachRejCasue3 },
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_EMM_TAU_TAUCollisionDetachRejCasue3 },
    {NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_EMM_TAU_TAUCollisionDetachRejCasue3 },
    {NAS_LMM_CAUSE_UE_ID_NOT_DERIVED,                                 NAS_EMM_TAU_TAUCollisionDetachRejCasue9 },
    {NAS_LMM_CAUSE_IMPLICIT_DETACHED,                                 NAS_EMM_TAU_TAUCollisionDetachRejCasue9 },
    {NAS_LMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_EMM_TAU_TAUCollisionDetachRejCasue3 },
    {NAS_LMM_CAUSE_TA_NOT_ALLOW,                                      NAS_EMM_TAU_TAUCollisionDetachRejCasue3 },
    {NAS_LMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_EMM_TAU_TAUCollisionDetachRejCasue13},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_EMM_TAU_TAUCollisionDetachRejCasue3 },
    {NAS_LMM_CAUSE_NO_SUITABL_CELL,                                   NAS_EMM_TAU_TAUCollisionDetachRejCasue13},
    {NAS_LMM_CAUSE_PROCEDURE_CONGESTION,                              NAS_EMM_TAU_TAUCollisionDetachRejCasue22},
#if(FEATURE_ON == FEATURE_CSG)
    {NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,                       NAS_EMM_TAU_TAUCollisionDetachRejCasue25},
#endif
    {NAS_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,       NAS_EMM_NULL_PTR                        },
    {NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,                   NAS_EMM_TAU_TAUCollisionDetachRejCasue9 },
    {NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE,                            NAS_EMM_TAU_TAUCollisionDetachRejCasue3 }
};

VOS_UINT32 gstEmmTauCollisionDetachRcvCnRejProcTblLen = sizeof(gstEmmTauCollisionDetachRcvCnRejProcTbl)
                                        / sizeof(NAS_LMM_TAU_COLLISION_DETACH_RCV_CN_REJ_PROC_STRU);

/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue367
Function : �յ�NAS_EMM_TAU_REJ_CAUSE367ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     : 1)set the EPS update status to EU3 ROAMING NOT ALLOWED
           2)delete any GUTI,
           3)last visited registered TAI, TAI list and KSI.
           4)consider the USIM as invalid for EPS services until switching off or the UICC containing the USIM is removed.
           5)delete the list of equivalent PLMNs
           6)enter the state EMM-DEREGISTERED.
Return   : VOS_UINT32
History  :
     1.  Zhouyan      00125190  2008.09.09  �¹�����
     2.  Zhengjunyan  00148421  2009.01.06  mod
     3.  lihong       00150010  2012.12.14  Modify:Emergency
     4.  sunjitan     00193151  2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue367
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "Nas_Emm_Tau_TAUReqRejectCasue367 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue3678_ENUM,LNAS_ENTRY);

    (VOS_VOID)pstTAURej;

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU3 ROAMING NOT ALLOWED�������õ�NVIM��*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*USIM��Ч��ֱ���ػ���ο�*/
    /*�ݲ�����*/

    /*ɾ��equivalent PLMNs��MMCģ�����*/
    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /*ת��EMM״̬��MS_DEREG+SS_DEREG_LIMITED_SERVICE*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                EMM_SS_DEREG_NO_IMSI,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /****����ͻ��־������Ӧ�Ĵ���********************************************/
    if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
    {
        /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
        NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
    }

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;
}


/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue8
Function : �յ�NAS_EMM_SER_REJ_CAUSE8ԭ���Ĵ���
Input    : ��
Output   : ��
NOTE     :

Return   : VOS_UINT32
History  :
    1.  wangchen 00209181       2014-09-28  �¹�����
    2.  sunjitan 00193151       2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue8
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    MMC_LMM_TAU_TYPE_ENUM_UINT32        enEmmTauType;

    enEmmTauType = NAS_EMM_TAU_GetTAUtype();

    /* ����TAU������Ч���� */
    if ((NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING == enEmmTauType)
      ||(NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == enEmmTauType))
    {
        NAS_EMM_TAU_TAUReqRejectCasue367(ucTAUrejcause, pstTAURej);
        return;
    }

    /* ������TAU��R11������Ч����R10���°�other���� */
    if (NAS_RELEASE_R11)
    {
        NAS_EMM_TAU_TAUReqRejectCasue367(ucTAUrejcause, pstTAURej);
    }
    else
    {
        NAS_EMM_TAU_TAUReqRejectOtherCause(NAS_LMM_CAUSE_NULL, pstTAURej);
    }

    return;

}

/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue9
Function : �յ�NAS_EMM_SER_REJ_CAUSE9ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     :1)set the EPS update status to EU2 NOT UPDATED
          2)delete any GUTI, last visited registered TAI, TAI list and KSI.
          3)delete the list of equivalent PLMNs
          4)enter the state EMM-DEREGISTERED.
          5)automatically initiate the attach procedure.

Return   : VOS_UINT32
History  :
    1.  Zhouyan      00125190  2008.09.09  �¹�����
    2.  Zhengjunyan  00148421  2009.01.06  mod
    2.  lihong       00150010  2012.12.14  Modify:Emergency
    4.  wangchen     00209181  2014.9.03   Modify:T3440
    5.  sunjitan     00193151  2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue9
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    VOS_UINT32                          ulAttachFlag    = VOS_TRUE;
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg       = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("Nas_Emm_Tau_TAUReqRejectCasue9 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue9_ENUM,LNAS_ENTRY);

    (VOS_VOID)pstTAURej;

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*��������EU2 NOT UPDATED*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_NOT_UPDATED_EU2);

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*ɾ��equivalent PLMNs��MMCģ�����*/
    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /*ת��EMM״̬��MS_DEREG+SS_DEREG_NORMAL_SERVICE*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ����Ǵ��CSFB���̣����ں���Ҫ����ȥGU����ͣATTACH���� */
    if ((NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
      &&(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
    {
        ulAttachFlag = VOS_FALSE;
    }

    /****����ͻ��־������Ӧ�Ĵ���********************************************/
    if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
    {
        /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
        NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
    }

    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_RrcRelCause_TAUREJ9: CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue9_ENUM,LNAS_FUNCTION_LABEL4);

        /*����ESM��Ϣ*/
        /*lint -e960*/
        NAS_LMM_MEM_CPY_S(     (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                               sizeof(NAS_EMM_CN_MSGCON_STRU),
                               &(pstEsmMsg->stEsmMsg),
                               (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);
        /*lint +e960*/
        NAS_EMM_StartEmergencyAttach();
    }
    /*lint -e960*/
    else if(VOS_TRUE == ulAttachFlag)
    /*lint +e960*/
    {
        if (NAS_RELEASE_R11)
        {
            NAS_EMM_WaitNetworkRelInd();
            return;
        }
        else
        {
            /* ��ʱ����attach����, �˴�������ѹջ�� ֱ��������ʱ��ʱ����
               ����ʱ��ʱ����ʱ��, ֱ�ӷ���ATTACH����
            */
            NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_REATTACH_DELAY);
        }
    }
    else
    {
        /*lint -e960*/
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
        /*lint +e960*/
    }

    /* ���TAU����������Դ*/
    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_ClearAppMsgPara();

    return;

}

/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue10
Function : �յ�NAS_EMM_SER_REJ_CAUSE10ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     :  The UE shall delete the list of equivalent PLMNs
            and shall enter the state EMM-DEREGISTERED.NORMAL-SERVICE.
            The UE shall then perform a new attach procedure
Return   : VOS_UINT32
History  :
    1.  Zhouyan      00125190  2008.09.09  �¹�����
    2.  Zhengjunyan  00148421  2009.01.06  mod
    3.  Zhengjunyan  00148421  2010.11.08  Mod:TAU REJ #10���ͷŵ�ǰ����
    4.  lihong       00150010  2011-09-29  Mod:combined detach
    5.  lihong       00150010  2012.12.14  Modify:Emergency
    6.  sunjitan     00193151  2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
/*lint -e960*/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue10
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    VOS_UINT32                          ulAttachFlag    = VOS_TRUE;
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg       = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "Nas_Emm_Tau_TAUReqRejectCasue10 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue10_ENUM,LNAS_ENTRY);

    (VOS_VOID)pstTAURej;

    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /* ״̬Ǩ��Dereg.Normal_Service������INTRA_ATTACH_REQ��Ϣ*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ����DEREG̬����дͳһд��ȫ�����ģ����ձ�ˣ���TAU��#10�ܾ�������ȫ������д�� */
    NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);

    /* ����Ǵ��CSFB���̣����ں���Ҫ����ȥGU����ͣATTACH���� */
    if ((NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
      &&(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
    {
        ulAttachFlag = VOS_FALSE;
    }

    /****����ͻ��־������Ӧ�Ĵ���********************************************/
    if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
    {
        /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
        NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
    }

    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_RrcRelCause_TAUREJ9: CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue10_ENUM,LNAS_FUNCTION_LABEL3);

        /*����ESM��Ϣ*/
        /*lint -e960*/
        NAS_LMM_MEM_CPY_S(  (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pstEsmMsg->stEsmMsg),
                            (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);
        /*lint +e960*/

        NAS_EMM_StartEmergencyAttach();
    }
    else if(VOS_TRUE == ulAttachFlag)
    {
        if (NAS_RELEASE_R11)
        {
            NAS_EMM_WaitNetworkRelInd();
            return;
        }
        else
        {
            /* ��ʱ����attach����, �˴�������ѹջ�� ֱ��������ʱ��ʱ����
               ����ʱ��ʱ����ʱ��, ֱ�ӷ���ATTACH����
            */
            NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_REATTACH_DELAY);

        }
    }
    else
    {
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }

    /* ���TAU��APP��Դ*/
    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_ClearAppMsgPara();

    return;
}
/*lint +e960*/
/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue11
Function : �յ�NAS_EMM_SER_REJ_CAUSE11ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     : 1)set the EPS update status to EU3 ROAMING NOT ALLOWED (and shall store it according to subclause 5.1.3.3)
           2)delete any GUTI, last visited registered TAI, TAI list and KSI.
           3)reset the tracking area updating attempt counter
           4)delete the list of equivalent PLMNs
           5)enter the state EMM-DEREGISTERED.PLMN-SEARCH.
           6)store the PLMN identity in the "forbidden PLMN list".
           7)perform a PLMN selection according to 3GPP TS 23.122 [3].
Return   : VOS_UINT32
History  :
  1.  Zhouyan      00125190  2008.09.09  �¹�����
  2.  Zhengjunyan  00148421  2009.01.06  mod
  3.  lihong       00150010  2012.12.14  Modify:Emergency
  4.  sunjitan     00193151  2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
/*lint -e960*/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue11
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "Nas_Emm_Tau_TAUReqRejectCasue11 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue11_ENUM,LNAS_ENTRY);

    (VOS_VOID)pstTAURej;

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU3 ROAMING NOT ALLOWED�������õ�NVIM��*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*ɾ��equivalent PLMNs��MMCģ�����*/

    /*Reset the TAU attempt counter*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /*Ϊ�ϱ�����״̬,ת��EMM״̬��MS_DEREG+SS_DEREG_LIMITED_SERVICE*/
    /*���յ�MMC����ָ���ת��DEREG_PLMN_SEARCH̬*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /****����ͻ��־������Ӧ�Ĵ���********************************************/
    if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
    {
        /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
        NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
    }

    NAS_EMM_WaitNetworkRelInd();

    return;

}
/*lint +e960*/

/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue12
Function : �յ�NAS_EMM_SER_REJ_CAUSE11ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     :1)set the EPS update status to EU3 ROAMING NOT ALLOWED (and shall store it according to subclause 5.1.3.3)
          2)and shall delete any GUTI, last visited registered TAI, TAI list and KSI.
          3)reset the tracking area updating attempt counter
          4)enter the state EMM-DEREGISTERED.LIMITED-SERVICE.
          5)store the current TAI in the list of "forbidden tracking areas for regional provision of service".

Return   : VOS_UINT32
History  :
  1.  Zhouyan      00125190  2008.09.09  �¹�����
  2.  Zhengjunyan  00148421  2009.01.06  mod
  3.  lihong       00150010  2012.12.14  Modify:Emergency
  4.  sunjitan     00193151  2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
/*lint -e960*/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue12
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    NAS_MM_TA_STRU                      stTa;

    (VOS_VOID)pstTAURej;

    /* ��ȡ��ǰTA */
    NAS_EMM_GetCurrentTa(&stTa);

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "Nas_Emm_Tau_TAUReqRejectCasue12 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue12_ENUM,LNAS_ENTRY);

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU3 ROAMING NOT ALLOWED�������õ�NVIM��*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    if (NAS_RELEASE_R11)
    {
        /* ����ǹ������磬����TAU��������̬����ģ�����Ҫ��������Ϣ��ӵ������б��� */
        if (NAS_EMM_YES == NAS_EMM_IsNeedAddForbTa())
        {
            /*store the current TAI in the list of
                  "forbidden tracking areas for regional provision of service"*/
            NAS_EMM_AddForbTa(&stTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr());
        }
    }
    else
    {
        NAS_EMM_AddForbTa(&stTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr());
    }

    /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
    /*����TAU������*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /*ת��EMM״̬��MS_DEREG+SS_DEREG_LIMITED_SERVICE*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /****����ͻ��־������Ӧ�Ĵ���********************************************/
    if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
    {
        /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
        NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
    }

    NAS_EMM_WaitNetworkRelInd();
    return;

}
/*lint +e960*/
/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue13
Function : �յ�NAS_EMM_SER_REJ_CAUSE11ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     :1)set the EPS update status to EU3 ROAMING NOT ALLOWED (and shall store it according to subclause 5.1.3.3)
          2)delete the list of equivalent PLMNs.
          3)reset the tracking area updating attempt counter
          4)change to state EMM-REGISTERED.PLMN-SEARCH.
          5)store the current TAI in the list of "forbidden tracking areas for roaming"
          6)remove the current TAI from the stored TAI list if present.
          7)shall perform a PLMN selection according to 3GPP TS 23.122 [3].

Return   : VOS_UINT32
History  :
   1.  Zhouyan      00125190  2008.09.09  �¹�����
   2.  Zhengjunyan  00148421  2009.01.06  mod
   3.  lihong       00150010  2012.12.14  Modify:Emergency
   4.  sunjitan     00193151  2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
/*lint -e960*/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue13
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    NAS_MM_TA_STRU                      stCurrentTa;
    NAS_MM_TA_LIST_STRU                *pstTaiList;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("Nas_Emm_Tau_TAUReqRejectCasue13 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue13_ENUM,LNAS_ENTRY);

    (VOS_VOID)pstTAURej;

    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

    /*����EU3 ROAMING NOT ALLOWED�������õ�NVIM��*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);
    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*����PS LOC��Ϣ*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }
    /*����TAU������*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /*Remove current TA from TAI List*/
    NAS_EMM_GetCurrentTa(&stCurrentTa);

    /* ��Ҫ�ѵ�ǰTA����ʱ�б����޳� */
    NAS_LMM_UpdateGradualForbListWithTauRejCause13(&stCurrentTa);

    pstTaiList = NAS_LMM_GetEmmInfoNetInfoTaiListAddr();
    NAS_LMM_DeleteTaFromTaList(&stCurrentTa, pstTaiList, NAS_MM_MAX_TA_NUM);

    if (NAS_RELEASE_R11)
    {
        /* ����ǹ������磬����Ҫ��������Ϣ��ӵ������б��� */
        if (NAS_EMM_YES == NAS_EMM_IsNeedAddForbTa())
        {
            /*store the current TAI in the list of
                        "forbidden tracking areas for roaming"*/
            NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
            NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
        }
    }
    else
    {
        NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
    }

    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUReqRejectCasue13:CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue13_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqTauAbnormalCommProc(   NAS_EMM_MmcSendTauActionResultIndRej,
                                                (VOS_VOID*)NAS_EMM_NULL_PTR,
                                                EMM_SS_DEREG_LIMITED_SERVICE);
    }
    else
    {
        /*����EMM_ESM_STATUS_IND(ȥע��)*/
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_ATTACHED);

        /*Ϊ�ϱ�����״̬,ת��EMM״̬��MS_DEREG+SS_REG_LIMITED_SERVICE*/
        /*���յ�MMC����ָ���ת��REG_PLMN_SEARCH̬*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                    EMM_SS_REG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /****����ͻ��־������Ӧ�Ĵ���********************************************/
        if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
        {
            /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
            NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
        }

    }

    NAS_EMM_WaitNetworkRelInd();

    return;

}
/*lint +e960*/
/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue14
Function : �յ�NAS_EMM_SER_REJ_CAUSE11ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     : 1)set the EPS update status to EU3 ROAMING NOT ALLOWED (and shall store it according to subclause 5.1.3.3).
           2)delete any GUTI, last visited registered TAI, TAI list and KSI.
           3)enter the state EMM-DEREGISTERED.PLMN-SEARCH.
           4)store the PLMN identity in the "forbidden PLMNs for GPRS service" list.
           5)perform a PLMN selection according to 3GPP TS 23.122 [3].

Return   : VOS_UINT32
History  :
     1.  Zhouyan      00125190  2008.09.09  �¹�����
     2.  Zhengjunyan  00148421  2009.01.06  mod
     3.  lihong       00150010  2012.12.14  Modify:Emergency
     4.  sunjitan     00193151  2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
/*lint -e960*/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue14
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "Nas_Emm_Tau_TAUReqRejectCasue14 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue14_ENUM,LNAS_ENTRY);

    (VOS_VOID)pstTAURej;

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU3 ROAMING NOT ALLOWED�������õ�NVIM��*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*����TAU������*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);
    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /*Ϊ�ϱ�����״̬,ת��EMM״̬��MS_DEREG+SS_DEREG_LIMITED_SERVICE*/
    /*���յ�MMC����ָ���ת��DEREG_PLMN_SEARCH̬*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /****����ͻ��־������Ӧ�Ĵ���********************************************/
    if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
    {
        /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
        NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
    }

    NAS_EMM_WaitNetworkRelInd();

    return;

}
/*lint +e960*/
/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue15
Function : �յ�NAS_EMM_SER_REJ_CAUSE11ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     :1)set the EPS update status to EU3 ROAMING NOT ALLOWED (and shall store it according to subclause 5.1.3.3).
          2)reset the tracking area updating attempt counter
          3)enter the state EMM-REGISTERED.LIMITED-SERVICE.
          4)store the current TAI in the list of "forbidden tracking areas for roaming"
          5)remove the current TAI from the stored TAI list if present.
          6)search for a suitable cell in another tracking area or in another location area in the same PLMN according to 3GPP TS 36.304 [13].

Return   : VOS_UINT32
History  :
     1.  Zhouyan      00125190  2008.09.09  �¹�����
     2.  Zhengjunyan  00148421  2009.01.06  mod
     3.  lihong       00150010  2012.12.14  Modify:Emergency
     4.  sunjitan     00193151  2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
/*lint -e960*/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue15
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    NAS_MM_TA_STRU                      stCurrentTa;
    NAS_MM_TA_LIST_STRU                *pstTaiList;
    MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  stLteNoSubsPlmnList;

    VOS_UINT32                          ulIsNeedExecLteNotAllow = NAS_EMM_YES;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "Nas_Emm_Tau_TAUReqRejectCasue15 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue15_ENUM,LNAS_ENTRY);

    (VOS_VOID)pstTAURej;

    NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
    /*����EU3 ROAMING NOT ALLOWED*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);
    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        /*����PS LOC��Ϣ*/
        NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
    }
    /*����TAU������*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

    /*��15�ܾ�����ǰPLMNֻ��һ��*/
    stLteNoSubsPlmnList.ulPlmnNum = 1;
    /*������ǰPLMN*/
    NAS_LMM_MEM_CPY_S(&(stLteNoSubsPlmnList.astPlmnId[0]),
                     sizeof(MMC_LMM_PLMN_ID_STRU),
                     NAS_LMM_GetEmmInfoPresentPlmnAddr(),
                     sizeof(MMC_LMM_PLMN_ID_STRU));

    if((NAS_EMM_BIT_SLCT == NAS_EMM_TAU_GetEmmTauCnEmmExtRejCauseOp())
       &&(NAS_EMM_EUTRAN_NOT_ALLOWED == NAS_EMM_TAU_GetEmmTauCnEmmExtRejCause())
       &&(PS_FALSE == NAS_EMM_GetLteNoSubscribeNvConfigDiscardExtCauseFlag()))
    {
        /*��15ԭ��ֵ�ܾ����ҵ�ǰ����չԭ��ֵ��ָʾUSIMδ��LTE��������������LTEδ��������*/
        /*NAS_EMM_SetLteNoSubscribeExtCauseFlag(NAS_EMM_EUTRAN_NOT_ALLOWED);*/
        NAS_LMM_LteNoSubscribeWithExtCauseHandle(&stLteNoSubsPlmnList);

        /* Forb TA�б�ά�� */
        NAS_LMM_AddTaInForbListWithTauRejCauseVal15(NAS_EMM_YES, &ulIsNeedExecLteNotAllow);
    }
    else
    {
        /* Forb TA�б�ά��, ���ж��Ƿ�Ҫ��4Gδ�������� */
        NAS_LMM_AddTaInForbListWithTauRejCauseVal15(NAS_EMM_NO, &ulIsNeedExecLteNotAllow);

        /* �ж��Ƿ�Ҫ��4Gδ�������� */
        if (NAS_EMM_YES == ulIsNeedExecLteNotAllow)
        {
            /*��15ԭ��ֵ�ܾ�����û�д���չԭ��ֵ����LTEδ������������*/
            NAS_LMM_LteNoSubscribeWithOutExtCauseHandle(&stLteNoSubsPlmnList);
        }
    }


    /*Remove current TA from TAI List*/
    NAS_EMM_GetCurrentTa(&stCurrentTa);

    pstTaiList = NAS_LMM_GetEmmInfoNetInfoTaiListAddr();
    NAS_LMM_DeleteTaFromTaList(&stCurrentTa, pstTaiList, NAS_MM_MAX_TA_NUM);

    /* �Ƶ�4Gδ�����жϷ�֧��ά��Forb�б� */

    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUReqRejectCasue15:CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue15_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqTauAbnormalCommProc(   NAS_EMM_MmcSendTauActionResultIndRej,
                                                (VOS_VOID*)NAS_EMM_NULL_PTR,
                                                EMM_SS_DEREG_LIMITED_SERVICE);
    }
    else
    {
        /*����EMM_ESM_STATUS_IND(ȥע��)*/
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_ATTACHED);

        /*ת��EMM״̬��MS_REG+SS_REG_LIMITED_SERVICE*/
        NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                    EMM_SS_REG_LIMITED_SERVICE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /****����ͻ��־������Ӧ�Ĵ���********************************************/
        if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
        {
            /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
            NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
        }

    }

    NAS_EMM_WaitNetworkRelInd();

    return;
}
/*lint +e960*/


/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue22
Function : �յ�NAS_EMM_SER_REJ_CAUSE22ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     :1)set the EPS update status to EU2 NOT UPDATED. (and shall store it according to subclause 5.1.3.3).
          2)reset the tracking area updating attempt counter
          3)enter the state EMM-REGISTERED.ATTEMPTING-TO-UPDATE.
          4)The UE shall stop timer T3346 if it is running.
          5)If the TRACKING AREA UPDATE REJECT message is integrity protected,
            the UE shall start timer with the value provided in the T3346 value IE
          6)If the TRACKING AREA UPDATE REJECT message is not integrity protected,
            the UE shall start timer T3346 with a random value from the default range specified in 3GPP TS 24.008

Return   : VOS_UINT32
History  :
     1.  wangchen 00209181  2015-02-10  �¹�����
     2.  sunjitan 00193151  2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue22
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_TAUReqRejectCasue22 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue22_ENUM,LNAS_ENTRY);

    if (NAS_EMM_BIT_SLCT == pstTAURej->ucBitOpT3346)
    {

        /*����EU2*/
        NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat = EMM_US_NOT_UPDATED_EU2;

        /*����TAU������*/
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

        /* ֹͣT3346��ʱ�� */
        NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3346);

        /* ����T3346��ʱ�� */
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3346);

        /* EMMע��״̬û�з����仯������ҪͬʱESMע��״̬ */
        /*����EMM_ESM_STATUS_IND(ȥע��)*/
        //NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_ATTACHED);


        NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                    EMM_SS_REG_ATTEMPTING_TO_UPDATE,
                                    TI_NAS_EMM_STATE_NO_TIMER);

        /****����ͻ��־������Ӧ�Ĵ���********************************************/
        if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
        {
            /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
            NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
        }

        /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    }
    else
    {
        NAS_EMM_TAU_TAUReqRejectOtherCause(ucTAUrejcause, pstTAURej);
    }

    return;
}


#if(FEATURE_ON == FEATURE_CSG)
/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue25
Function : �յ�NAS_EMM_SER_REJ_CAUSE25ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     :

Return   : VOS_UINT32
History  :
     1.  yanglei 00307272  2015-09-25  �¹�����

*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue25
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    /* ��ӡ����ú��� */
    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_TAUReqRejectCasue25 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue25_ENUM,LNAS_ENTRY);

    if(NAS_EMM_NO == NAS_LMM_IsCsgCampOn())
    {
        NAS_EMM_TAU_TAUReqRejectOtherCause(ucTAUrejcause, pstTAURej);
    }
    else
    {

        (VOS_VOID)pstTAURej;


        /*����EU3 ROAMING NOT ALLOWED�������õ�NVIM��*/
        NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_ZERO);

        /* tau����Ϊ����tau,����ps�򣬺�������tauΪ����tau */
        if((NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING == NAS_EMM_TAU_GetTAUtype())
            ||(NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI== NAS_EMM_TAU_GetTAUtype()))
        {
            NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);
        }

         /*ɾ��equivalent PLMNs��MMCģ�����*/
        if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
        {
            NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUReqRejectCasu25:CAUSE_ESM_EMC_PDN_REQ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue25_ENUM,LNAS_FUNCTION_LABEL1);

            NAS_EMM_EmcPndReqTauAbnormalCommProc(   NAS_EMM_MmcSendTauActionResultIndRej,
                                                    (VOS_VOID*)NAS_EMM_NULL_PTR,
                                                    EMM_SS_DEREG_LIMITED_SERVICE);
        }
        else
        {
            /*����EMM_ESM_STATUS_IND(ȥע��)*/
            NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_ATTACHED);

            /*Ϊ�ϱ�����״̬,ת��EMM״̬��MS_DEREG+SS_REG_LIMITED_SERVICE*/
            /*���յ�MMC����ָ���ת��REG_PLMN_SEARCH̬*/
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);

            /****����ͻ��־������Ӧ�Ĵ���********************************************/
            if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
            {
                /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
                NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
            }

        }

        /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    return;
}
#endif

/* leixiantiao 00258641 �ع����뽵��Ȧ���Ӷ� 2014-7-30 begin */
/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue35
Function : �յ�NAS_EMM_SER_REJ_CAUSE35ԭ���Ĵ���
Input    : NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause
Output   : ��

Return   : None
History  :
     1.  leixiantiao      00258641  2014-07-30
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue35
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

)

{
    /* �ж��Ƿ��nas r10���� */
    if (NAS_RELEASE_CTRL)
    {
        NAS_EMM_TAU_TAUReqRejectCasue11(ucTAUrejcause, pstTAURej);
    }
    else
    {
        NAS_EMM_TAU_TAUReqRejectOtherCause(ucTAUrejcause, pstTAURej);
    }
    return;
}
/* leixiantiao 00258641 �ع����뽵��Ȧ���Ӷ� 2014-7-30 end */

/*lint -e960*/

VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue40
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    VOS_UINT32                          ulAttachFlag    = VOS_TRUE;
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg       = NAS_EMM_NULL_PTR;

    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_TAU_TAUReqRejectCasue40 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue40_ENUM,LNAS_ENTRY);

    (VOS_VOID)pstTAURej;

    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /*ת��EMM״̬��MS_REG+SS_REG_LIMITED_SERVICE*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG, EMM_SS_DEREG_NORMAL_SERVICE, TI_NAS_EMM_STATE_NO_TIMER);

    /* ����Ǵ��CSFB���̣����ں���Ҫ����ȥGU����ͣATTACH���� */
    if ((NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
      &&(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure()))
    {
        ulAttachFlag = VOS_FALSE;
    }

    /****����ͻ��־������Ӧ�Ĵ���********************************************/
    if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
    {
        /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
        NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
    }

    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();
    if ((NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
        && (NAS_EMM_NULL_PTR != pstEsmMsg))
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_RrcRelCause_TAUREJ9: CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue40_ENUM,LNAS_FUNCTION_LABEL4);

        /*����ESM��Ϣ*/
        /*lint -e960*/
        NAS_LMM_MEM_CPY_S(  (VOS_VOID*)NAS_EMM_GLO_AD_GetEsmMsgAddr(),
                            sizeof(NAS_EMM_CN_MSGCON_STRU),
                            &(pstEsmMsg->stEsmMsg),
                            (pstEsmMsg->stEsmMsg.ulEsmMsgSize)+4);
        /*lint +e960*/
        NAS_EMM_StartEmergencyAttach();
    }
    else if(VOS_TRUE == ulAttachFlag)
    {
        if (NAS_RELEASE_R11)
        {
            NAS_EMM_WaitNetworkRelInd();
            return;
        }
        else
        {
            /* ��ʱ����attach����, �˴�������ѹջ�� ֱ��������ʱ��ʱ����
               ����ʱ��ʱ����ʱ��, ֱ�ӷ���ATTACH����
            */
            NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_REATTACH_DELAY);
        }
    }
    else
    {
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }

    /* ���TAU����������Դ*/
    NAS_EMM_TAU_ClearResouce();
    NAS_EMM_ClearAppMsgPara();

    return;
}
/*lint +e960*/


/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue42
Function : �յ�NAS_EMM_SER_REJ_CAUSE42ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     :

Return   : VOS_UINT32
History  :
    1.  wangchen 00209181   2014-09-01  �¹�����
    2.  sunjitan 00193151   2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue42Release11
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("Nas_Emm_Tau_TAUReqRejectCasue42 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectCasue42Release11_ENUM,LNAS_ENTRY);

    (VOS_VOID)pstTAURej;

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*��������EU2 NOT UPDATED*/
    NAS_LMM_GetMmAuxFsmAddr()->ucEmmUpStat = EMM_US_NOT_UPDATED_EU2;

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_NOT_DELETE_RPLMN);

    /*ɾ��equivalent PLMNs��MMCģ�����*/
    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }

    /*TAU���Դ�������Ϊ���*/
    NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_MAX);

    /*ת��EMM״̬��MS_DEREG+SS_DEREG_LIMITED_SERVICE*/
    /* ���յ�����ָʾ���ٽ�״̬ת��DEREG_PLMN_SERCH */
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                EMM_SS_DEREG_LIMITED_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /****����ͻ��־������Ӧ�Ĵ���********************************************/
    if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
    {
        /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
        NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
    }

    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;

}
/*******************************************************************************
Module   : NAS_EMM_TAU_TAUReqRejectCasue42
Function : �յ�NAS_EMM_SER_REJ_CAUSE42ԭ���Ĵ���
Input    : VOS_VOID *pMsg     ԭ���׵�ַ
Output   : ��
NOTE     :

Return   : VOS_UINT32
History  :
    1.  wangchen 00209181   2014-09-01  �¹�����
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUReqRejectCasue42
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej

)
{
    if (NAS_RELEASE_R11)
    {
        NAS_EMM_TAU_TAUReqRejectCasue42Release11(ucTAUrejcause, pstTAURej);
    }
    else
    {
        NAS_EMM_TAU_TAUReqRejectOtherCause(ucTAUrejcause, pstTAURej);
    }
}


/* s00193151 begin for ����Ӧ����ܾ�ԭ��ֵ */
/*******************************************************************************
  Module   : NAS_EMM_TAU_TAUReqRejectOtherCause
  Function : �յ�RRC_MM_REL_INDԭ���Ĵ���
  Input    : VOS_VOID *pMsg     ԭ���׵�ַ
  Output   : ��
  NOTE     : 1)set the tracking area updating attempt counter to 5
             2)stop any ongoing transmission of user data
             3)Timer T3430 shall be stopped if still running.
             4)start timer T3402
             5)set the update status to EU2 NOT UPDATED
             6)delete the list of equivalent PLMNs
             7)change to state EMM-REGISTERED.ATTEMPTING-TO-UPDATE
               or optionally to EMM-REGISTERED.PLMN-SEARCH in order to perform a PLMN selection according to 3GPP TS 23.122 [3].
  Return   : VOS_UINT32
  History  :
    1.  Zhouyan   00125190  2008.09.09  �¹�����
    2.  lihong    00150010  2012.12.14  Modify:Emergency
    3.  sunjitan  00193151  2015-08-04  Modify for MT_CSFB_IMPROVED_PHASEII
*******************************************************************************/
/*lint -e960*/
VOS_VOID NAS_EMM_TAU_TAUReqRejectOtherCause
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU      *pstTAURej
)
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO( "Nas_Emm_Tau_TAUReqRejectCasueOthers is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectOtherCause_ENUM,LNAS_ENTRY);

    (VOS_VOID)pstTAURej;

    if( (NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG == ucTAUrejcause)||
        (NAS_LMM_CAUSE_INVALID_MANDATORY_INF == ucTAUrejcause)||
        (NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE == ucTAUrejcause)||
        (NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED == ucTAUrejcause)||
        (NAS_LMM_CAUSE_PROTOCOL_ERROR == ucTAUrejcause)||
        (VOS_TRUE == NAS_LMM_GetRoamingRejectNoRetryFlg(ucTAUrejcause)))/* ��Ʒ����������������DTS2014073107501 */
    {
        NAS_EMM_TAU_SaveEmmTAUAttemptCnt(NAS_EMM_TAU_ATTEMPT_CNT_MAX);
    }
    else
    {
        NAS_EMM_TAU_GetEmmTAUAttemptCnt()++;
    }

    NAS_EMM_TAU_ProcAbnormal();

    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUReqRejectOtherCause:CAUSE_ESM_EMC_PDN_REQ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUReqRejectOtherCause_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_EMM_EmcPndReqTauAbnormalCommProc(   NAS_EMM_MmcSendTauActionResultIndRej,
                                                (VOS_VOID*)NAS_EMM_NULL_PTR,
                                                EMM_SS_DEREG_NORMAL_SERVICE);
    }
    else
    {
        /****����ͻ��־������Ӧ�Ĵ���********************************************/
        if (NAS_EMM_COLLISION_NONE == NAS_EMM_TAU_RcvTauRejCollisionProc(ucTAUrejcause))
        {
            /* ��������ڳ�ͻ��ֻ�ϱ�TAU����������ڳ�ͻ�����л��ϱ�TAU��� */
            NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
        }
    }

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);

    return;

}

/*******************************************************************************
  Module   :
  Function : Nas_Emm_TAU_RcvTAURej
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.Zhouyan 00125190  2008.09.17  �¹�����
    2.zhengjunyan 00148421   2011-12-23  DTS2011122103346:CSG������δʵ�֣��յ�
                                     REJ #25����CSG��������default�����֧
    3.wangchen 00209181 2014-09-03  Modify:#8����ͬ#367
*******************************************************************************/
VOS_VOID    NAS_EMM_TAU_RcvTAURej
(
    const NAS_EMM_CN_CAUSE_ENUM_UINT8   ucTAUrejcause,
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej
)
{
    VOS_UINT32                          ulIndex = 0;
    NAS_LMM_TAU_REJ_CAUSE_PROC_FUN          pfRejCauseProcFun;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_INFO("Nas_Emm_Tau_RcvTAURej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RcvTAURej_ENUM,LNAS_ENTRY);

    /* ֹͣ��ʱ��3430*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_TAU_T3430);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_EMM_SendMtcTAUEndType();
#endif

    for (ulIndex = 0; ulIndex < gstEmmTauRejCauseProcTblLen; ulIndex++)
    {
        if (ucTAUrejcause == gstEmmTauRejCauseProcTbl[ulIndex].enRejCauseVal)
        {
            pfRejCauseProcFun = gstEmmTauRejCauseProcTbl[ulIndex].pfRejCauseProcFun;

            /* �д����� */
            if (VOS_NULL_PTR != pfRejCauseProcFun)
            {
                (pfRejCauseProcFun)(ucTAUrejcause, pstTAURej);
            }
            return;
        }
    }

    /*����ԭ��ֵ����*/
    NAS_EMM_TAU_TAUReqRejectOtherCause(ucTAUrejcause, pstTAURej);
    return;
}
/* s00193151 end for ����Ӧ����ܾ�ԭ��ֵ */
/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsTauInitSsWaitCNCnfMsgTAURej
  Input    :
  Output   :
  NOTE     :
  Return   :
  History  :
    1.  Zhouyan 00125190  2008.09.10  �¹�����
*******************************************************************************/
VOS_UINT32 NAS_EMM_MsTauInitSsWaitCNCnfMsgTAURej(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               )
{
    VOS_UINT32                          ulRslt      = NAS_EMM_FAIL;
    NAS_EMM_CN_TAU_REJ_STRU            *pstTAURej   = NAS_EMM_NULL_PTR;
    LNAS_STK_UPDATE_TYPE_ENUM_UINT8     uTauType = LNAS_STK_UPDATE_TYPE_BUTT;
    VOS_UINT32                          ulTimerLen = NAS_EMM_NULL;

    (VOS_VOID)ulMsgId;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_TAU_LOG_NORM( "Nas_Emm_MsTauInitSsWaitCNCnfMsgTAURej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCNCnfMsgTAURej_ENUM,LNAS_ENTRY);

    /* ��������ָ��������, ״̬ƥ����,����ƥ��,�˳�*/
    ulRslt = NAS_EMM_TAU_CHKFSMStateMsgp(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF,pMsgStru);
    if ( NAS_EMM_SUCC != ulRslt )
    {
        NAS_EMM_TAU_LOG_WARN("NAS_EMM_TAUSER_CHKFSMStateMsgp ERROR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsTauInitSsWaitCNCnfMsgTAURej_ENUM,LNAS_ERROR);
        return ulRslt;
    }
    /* ������:�ڸ�MMC����TAU���ǰ������TAU CN REJ���� */
    NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_CN_REJ);
    /*ֹͣT3416��ɾ��RAND,RES*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();

    /*������Ϣ������*/
    pstTAURej = (NAS_EMM_CN_TAU_REJ_STRU*) pMsgStru;
    /*����TAU�ܾ�ԭ��*/
    NAS_EMM_TAU_GetEmmTauCnRejCause() =  pstTAURej->ucEMMCause;
    if(NAS_EMM_BIT_SLCT == pstTAURej->ucBitOpExtCause)
    {
        NAS_EMM_TAU_GetEmmTauCnEmmExtRejCauseOp() = NAS_EMM_BIT_SLCT;
        NAS_EMM_TAU_GetEmmTauCnEmmExtRejCause() = pstTAURej->ucEmmExtCause;
    }


    /* ����T3346��ʱ��ʱ�� */
    if (NAS_EMM_BIT_SLCT == pstTAURej->ucBitOpT3346)
    {
        /* �˴��޸Ľ����GCF 9.2.3.1.20a�����޸ģ���δ�����ƣ�����Ŀǰ������TAU REJ�������Ա���
        �ĳ��� */
        ulTimerLen = NAS_EMM_TimerValTransfer(pstTAURej->stT3346.ucUnit,
                                               pstTAURej->stT3346.ucTimerVal);
        NAS_LMM_ModifyPtlTimer(TI_NAS_EMM_PTL_T3346,ulTimerLen);
    }

    /* s00193151 begin for ����Ӧ����ܾ�ԭ��ֵ */
    /* ���ݵ�ǰ���������Ƿ���Ҫ�޸�ԭ��ֵ */
    NAS_LMM_AdaptRegRejCau(&NAS_EMM_TAU_GetEmmTauCnRejCause());
    /* s00193151 end for ����Ӧ����ܾ�ԭ��ֵ */

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_TAUErrRecord(pMsgStru, EMM_OM_ERRLOG_TYPE_CN_REJ);
    #endif

    switch(NAS_EMM_TAU_GetTAUtype())
    {
        case NAS_EMM_CN_TAU_TYPE_TA_UPDATING:
                uTauType = LNAS_STK_UPDATE_TYPE_TA_UPDATEING;
                break;

        case NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING:
                uTauType = LNAS_STK_UPDATE_TYPE_COMBINED_TALA_UPDATING ;
                break;

        case NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI:
                uTauType = LNAS_STK_UPDATE_TYPE_COMBINED_TALA_UPDATING_WITH_IMSI_ATTACH;
                break;

        case NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING:
                uTauType = LNAS_STK_UPDATE_TYPE_PERIODIC_UPDATING;
                break;

        default:
                NAS_EMM_TAU_LOG_ERR("NAS_EMM_SendRejEventToSTK: TAU Type error!");
                TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsTauInitSsWaitCNCnfMsgTAURej_ENUM,LNAS_FUNCTION_LABEL1);
                break;
    }

    /* s00193151 begin for ����Ӧ����ܾ�ԭ��ֵ */
    /*��TAU rejʱ����rej�¼����͸�STK*/
    NAS_EMM_SendRejEventToSTK(NAS_EMM_TAU_GetEmmTauCnRejCause(), uTauType);

    NAS_EMM_TAU_RcvTAURej(NAS_EMM_TAU_GetEmmTauCnRejCause(), pstTAURej);
    /* s00193151 end for ����Ӧ����ܾ�ԭ��ֵ */

    return NAS_LMM_MSG_HANDLED;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_MsTauInitSsWaitCnTauCnfProcMsgAuthRej
  NOTE     : ��״̬:TauInit ��״̬:WtCnTauCnf �յ� INTRA_AUTH_REJ
             ��Ϊ����Ч����
  Input    :
  Output   :
  Return   :
  History  :
    1.zhengjunyan 00148421    2009-5-19  Draft Enact
    2.X00148705               2009-09-30 �ع�
*******************************************************************************/
VOS_VOID NAS_EMM_MsTauInitSsWaitCnTauCnfProcMsgAuthRej(
                                                   VOS_UINT32  ulCause)
{
    MMC_LMM_TAU_RSLT_ENUM_UINT32        enTauRslt = MMC_LMM_TAU_RSLT_AUTH_REJ;

    (VOS_VOID)ulCause;

    NAS_EMM_TAU_LOG_INFO( "NAS_EMM_MsTauInitSsWaitCnTauCnfProcMsgAuthRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCnTauCnfProcMsgAuthRej_ENUM,LNAS_ENTRY);

    /*ֹͣ��ʱ��*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_STATE_TAU_T3430);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    NAS_EMM_TAU_SendRrcDsdsEndNotify();
    #endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_EMM_SendMtcTAUEndType();
#endif

    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();

    /* ɾ��GUTI����Զ�����EPS_LOC,������Ҫ������STATUS */
    /*����EU3 ROAMING NOT ALLOWED�������õ�NVIM��*/
    NAS_EMM_TAUSER_SaveAuxFsmUpStat(EMM_US_ROAMING_NOT_ALLOWED_EU3);

    /*ɾ��GUTI,KSIasme,TAI list,GUTI*/
    NAS_EMM_ClearRegInfo(NAS_EMM_DELETE_RPLMN);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_INVALID);

    /*USIM��Ч��ֱ���ػ���ο�*/
    /*�ݲ�����*/

    /*ɾ��equivalent PLMNs��MMCģ�����*/
    if (NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ == NAS_EMM_TAU_GetEmmTAUStartCause())
    {
        /* ��¼ATTACH����ԭ��ֵ */
        NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);
    }
    else
    {
        NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_DETACHED);
    }
    /*ת��EMM״̬��MS_DEREG+SS_DEREG_LIMITED_SERVICE*/
    NAS_EMM_TAUSER_FSMTranState(EMM_MS_DEREG,
                                EMM_SS_DEREG_NO_IMSI,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* �ϱ�TAU����ڳ�ͻ������ִ�� */
    /****����ͻ��־������Ӧ�Ĵ���********************************************/
    switch(NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        case    NAS_EMM_COLLISION_DETACH   :

                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&enTauRslt);
                NAS_EMM_TAU_CollisionDetachProc();
                break;

        case    NAS_EMM_COLLISION_SERVICE    :

                NAS_EMM_TAU_CollisionServiceProc(NAS_EMM_MmcSendTauActionResultIndOthertype,
                                (VOS_VOID*)&enTauRslt,
                                NAS_EMM_TRANSFER_RAT_NOT_ALLOW);
                break;

        default :

                NAS_EMM_TAU_LOG_INFO( "NAS_EMM_MsTauInitSsWaitCnTauCnfProcMsgAuthRej : NO Emm Collision.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_MsTauInitSsWaitCnTauCnfProcMsgAuthRej_ENUM,LNAS_FUNCTION_LABEL1);
                NAS_EMM_MmcSendTauActionResultIndOthertype((VOS_VOID*)&enTauRslt);
                break;
    }

    /*��LRRC����LRRC_LMM_NAS_INFO_CHANGE_REQЯ��USIM��״̬*/
    NAS_EMM_SendUsimStatusToRrc(LRRC_LNAS_USIM_PRESENT_INVALID);

    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    return;
}



/*****************************************************************************
 Function Name   : NAS_EMM_TAU_RcvTauRejCollisionProc
 Description     : TAU������������յ�CN REJʱ��Գ�ͻ�Ĵ���
 Input           : NAS_EMM_CN_CAUSE_ENUM_UINT8    TAU����ԭ��ֵ
 Output          : None
 Return          : NAS_EMM_COLLISION_ENUM_UINT8   ��ͻ����

 History         :
    1.  sunjitan 00193151    2015-08-04    Draft Enact
*****************************************************************************/
NAS_EMM_COLLISION_ENUM_UINT8 NAS_EMM_TAU_RcvTauRejCollisionProc
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_RcvTauRejCollisionProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RcvTauRejCollisionProc_ENUM, LNAS_ENTRY);

    /* �����DETACH��ͻ */
    if (NAS_EMM_COLLISION_DETACH == NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_RcvTauRejCollisionProc: NAS_EMM_COLLISION_DETACH.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RcvTauRejCollisionProc_ENUM, LNAS_FUNCTION_LABEL1);

        NAS_EMM_TAU_CollisionDetachRcvCnRejProc(enTauRejcause);
        return NAS_EMM_COLLISION_DETACH;
    }

    /* SERVICE��ͻ�Ĵ��� */
    if (NAS_EMM_COLLISION_SERVICE == NAS_EMM_TAU_GetEmmCollisionCtrl())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_RcvTauRejCollisionProc: NAS_EMM_COLLISION_SERVICE.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_RcvTauRejCollisionProc_ENUM, LNAS_FUNCTION_LABEL2);

        NAS_EMM_TAU_CollisionServiceRcvCnRejProc(enTauRejcause);
        return NAS_EMM_COLLISION_SERVICE;
    }

    /* �޳�ͻ���������⴦�� */
    return NAS_EMM_COLLISION_NONE;

}


/*****************************************************************************
 Function Name   : NAS_EMM_TAU_CollisionServiceRcvCnRejProc
 Description     : TAU���SERVICE�յ�CN REJ�Ĵ���
 Input           : NAS_EMM_CN_CAUSE_ENUM_UINT8    TAU����ԭ��ֵ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.  sunjitan 00193151    2015-08-04    Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_CollisionServiceRcvCnRejProc
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    VOS_UINT32                                     i;
    NAS_LMM_TAU_COLLISION_SER_RCV_CN_REJ_PROC_FUN  pfProcFun;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_CollisionServiceRcvCnRejProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_CollisionServiceRcvCnRejProc_ENUM, LNAS_ENTRY);

    for (i = 0; i < gstEmmTauCollisionSerRcvCnRejProcTblLen; i++)
    {
        if (enTauRejcause == gstEmmTauCollisionSerRcvCnRejProcTbl[i].enRejCauseVal)
        {
            pfProcFun = gstEmmTauCollisionSerRcvCnRejProcTbl[i].pfProcFun;

            /* �д�����ִ�� */
            if (VOS_NULL_PTR != pfProcFun)
            {
                (pfProcFun)(enTauRejcause);
            }

            /* �޴������޶���ֱ�ӷ��� */
            return;
        }
    }

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_CollisionServiceRcvCnRejProc: other cause.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_CollisionServiceRcvCnRejProc_ENUM, LNAS_FUNCTION_LABEL1);

    /*����ԭ��ֵ����*/
    NAS_EMM_TAU_TAUCollisionSerRejCasueOther(enTauRejcause);

    return;
}

/*******************************************************************************
Module   : NAS_EMM_TAU_TAUCollisionSerRejCasue368
Function : TAU���SER�յ�CN REJ#3#6#8ԭ���Ĵ���
Input    : NAS_EMM_CN_CAUSE_ENUM_UINT8            TAU�ܾ�ԭ��ֵ
Output   : VOS_VOID
Return   : VOS_VOID
History  :
    1.  sunjitan 00193151    2015-08-04    Draft Enact
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUCollisionSerRejCasue3
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    (VOS_VOID)enTauRejcause;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionSerRejCasue3 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionSerRejCasue3_ENUM, LNAS_ENTRY);

    /* ESR�����з���TAU����, TAUʧ�ܵ���CSFB����ʧ��, ֪ͨLRRC CSFB������ֹ,
    LRRC�յ�����Ϣ��, ���ȴ������ͷŶ�ʱ������ʱ, ֹͣ��ʱ�� */
    if(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);
    }

    switch(NAS_EMM_SER_GetEmmSERStartCause())
    {
        case    NAS_EMM_SER_START_CAUSE_SMS_EST_REQ:

                NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionSerRejCasue3: SMS EST REQ.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionSerRejCasue3_ENUM, LNAS_FUNCTION_LABEL1);

                /* �ϱ�TAU��� */
                NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
                NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
                NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);

                /* ֪ͨRABM ���SERVICE ʧ�� */
                NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
                break;

        case    NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ:
        case    NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ:

                NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionSerRejCasue3: MO/MT CSFB.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionSerRejCasue3_ENUM, LNAS_FUNCTION_LABEL2);

                NAS_EMM_SetCsfbProcedureFlag(PS_FALSE);
                NAS_EMM_MmSendCsfbSerEndInd(MM_LMM_CSFB_SERVICE_RSLT_TAU_COLLISION_RSLT_ABNORMAL, NAS_LMM_CAUSE_NULL);

                /* �ϱ�TAU���, ˳��һ��Ҫ�ڸ�MM����ֹ֮�� */
                NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
                break;

        case    NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ:

                NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionSerRejCasue3: EMERGENCY CSFB.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionSerRejCasue3_ENUM, LNAS_FUNCTION_LABEL3);

                /* �ϱ�TAU���, ˳��һ��Ҫ�ڸ�MMC��SER���֮ǰ*/
                NAS_EMM_MmcSendTauActionResultIndRej(VOS_NULL_PTR);

                /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
                NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

                break;

        default:
                /* �ϱ�TAU��� */
                NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);

                /* ֪ͨRABM ���SERVICE ʧ�� */
                NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
                break;
    }

    /* �����ͻ��־ */
    NAS_EMM_TAU_SaveEmmCollisionCtrl( NAS_EMM_COLLISION_NONE);

    NAS_EMM_TAU_ClearActiveFlagProc();

    /**����������ݵı�־��������**************/
    NAS_EMM_SerClearEsmDataBuf();

    return;

}

/*******************************************************************************
Module   : NAS_EMM_TAU_TAUCollisionSerRejCasue7
Function : TAU���SER�յ�CN REJ#7ԭ���Ĵ���
Input    : NAS_EMM_CN_CAUSE_ENUM_UINT8            TAU�ܾ�ԭ��ֵ
Output   : VOS_VOID
Return   : VOS_VOID
History  :
    1.  sunjitan 00193151    2015-08-04    Draft Enact
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUCollisionSerRejCasue7
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    (VOS_VOID)enTauRejcause;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionSerRejCasue7 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionSerRejCasue7_ENUM, LNAS_ENTRY);

    /* ESR�����з���TAU����, TAUʧ�ܵ���CSFB����ʧ��, ֪ͨLRRC CSFB������ֹ,
    LRRC�յ�����Ϣ��, ���ȴ������ͷŶ�ʱ������ʱ, ֹͣ��ʱ�� */
    if(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);
    }

    switch(NAS_EMM_SER_GetEmmSERStartCause())
    {
        case    NAS_EMM_SER_START_CAUSE_SMS_EST_REQ:

                NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionSerRejCasue7: SMS EST REQ.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionSerRejCasue7_ENUM, LNAS_FUNCTION_LABEL1);

                /* �ϱ�TAU��� */
                NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);
                NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
                NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);

                /* ֪ͨRABM ���SERVICE ʧ�� */
                NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
                break;

        case    NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ:
        case    NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ:
        case    NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ:

                NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionSerRejCasue7: MO/MT/EMERGENCY CSFB.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionSerRejCasue7_ENUM, LNAS_FUNCTION_LABEL2);

                /* �ϱ�TAU���, ˳��һ��Ҫ�ڸ�MMC��SER���֮ǰ*/
                NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);

                /*��MMC����LMM_MMC_SERVICE_RESULT_IND��Ϣ*/
                NAS_EMM_MmcSendSerResultIndOtherType(MMC_LMM_SERVICE_RSLT_FAILURE);

                break;

        default:
                /* �ϱ�TAU��� */
                NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);

                /* ֪ͨRABM ���SERVICE ʧ�� */
                NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
                break;
    }

    /* �����ͻ��־ */
    NAS_EMM_TAU_SaveEmmCollisionCtrl(NAS_EMM_COLLISION_NONE);

    NAS_EMM_TAU_ClearActiveFlagProc();

    /**����������ݵı�־��������**************/
    NAS_EMM_SerClearEsmDataBuf();

    return;

}

/*******************************************************************************
Module   : NAS_EMM_TAU_TAUCollisionSerRejCasueOther
Function : TAU���SER�յ�CN REJ#otherԭ���Ĵ���
Input    : NAS_EMM_CN_CAUSE_ENUM_UINT8            TAU�ܾ�ԭ��ֵ
Output   : VOS_VOID
Return   : VOS_VOID
History  :
    1.  sunjitan 00193151    2015-08-04    Draft Enact
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUCollisionSerRejCasueOther
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    NAS_EMM_TAU_TAUCollisionSerRejCasue7(enTauRejcause);
    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_TAU_CollisionDetachRcvCnRejProc
 Description     : TAU���DETACH�յ�CN REJ�Ĵ���
 Input           : NAS_EMM_CN_CAUSE_ENUM_UINT8    TAU����ԭ��ֵ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.  sunjitan 00193151    2015-08-04    Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_TAU_CollisionDetachRcvCnRejProc
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    VOS_UINT32                                     i;
    NAS_LMM_TAU_COLLISION_SER_RCV_CN_REJ_PROC_FUN  pfProcFun;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_CollisionDetachRcvCnRejProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_CollisionDetachRcvCnRejProc_ENUM, LNAS_ENTRY);

    for (i = 0; i < gstEmmTauCollisionDetachRcvCnRejProcTblLen; i++)
    {
        if (enTauRejcause == gstEmmTauCollisionDetachRcvCnRejProcTbl[i].enRejCauseVal)
        {
            pfProcFun = gstEmmTauCollisionDetachRcvCnRejProcTbl[i].pfProcFun;

            /* �д�����ִ�� */
            if (VOS_NULL_PTR != pfProcFun)
            {
                (pfProcFun)(enTauRejcause);
            }

            /* �޴������޶���ֱ�ӷ��� */
            return;
        }
    }

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_CollisionDetachRcvCnRejProc: other cause.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_CollisionDetachRcvCnRejProc_ENUM, LNAS_FUNCTION_LABEL1);

    /*����ԭ��ֵ����*/
    NAS_EMM_TAU_TAUCollisionDetachRejCasueOther(enTauRejcause);

    return;
}

/*******************************************************************************
Module   : NAS_EMM_TAU_TAUCollisionDetachRejCasue368
Function : TAU���Detach�յ�CN REJ#3#6#8ԭ���Ĵ���
Input    : NAS_EMM_CN_CAUSE_ENUM_UINT8            TAU�ܾ�ԭ��ֵ
Output   : VOS_VOID
Return   : VOS_VOID
History  :
    1.  sunjitan 00193151    2015-08-04    Draft Enact
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUCollisionDetachRejCasue3
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    (VOS_VOID)enTauRejcause;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionDetachRejCasue3 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionDetachRejCasue3_ENUM, LNAS_ENTRY);

    /* �ϱ�TAU��� */
    NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);

    NAS_EMM_TAU_CollisionDetachProc();

    if (MMC_LMM_MO_DET_CS_ONLY != NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionDetachRejCasue3: PS/CS_PS DETACH.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionDetachRejCasue3_ENUM, LNAS_FUNCTION_LABEL1);

        /* ����DETACH*/
        NAS_LMM_DeregReleaseResource();
    }
    else
    {
        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();
    }

    return;

}

/*******************************************************************************
Module   : NAS_EMM_TAU_TAUCollisionDetachRejCasue9
Function : TAU���Detach�յ�CN REJ#9ԭ���Ĵ���
Input    : NAS_EMM_CN_CAUSE_ENUM_UINT8            TAU�ܾ�ԭ��ֵ
Output   : VOS_VOID
Return   : VOS_VOID
History  :
    1.  sunjitan 00193151    2015-08-04    Draft Enact
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUCollisionDetachRejCasue9
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    (VOS_VOID)enTauRejcause;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionDetachRejCasue9 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionDetachRejCasue9_ENUM, LNAS_ENTRY);

    /* �ϱ�TAU��� */
    NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);

    NAS_EMM_TAU_CollisionDetachProc();

    if (MMC_LMM_MO_DET_CS_ONLY != NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionDetachRejCasue9: PS/CS_PS DETACH.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionDetachRejCasue9_ENUM, LNAS_FUNCTION_LABEL1);

       /* ����DETACH*/
       NAS_LMM_DeregReleaseResource();
       NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    else
    {
       /* IMSI DETACH���ͷ���Դ */
       NAS_LMM_ImsiDetachReleaseResource();
    }

    return;

}

/*******************************************************************************
Module   : NAS_EMM_TAU_TAUCollisionDetachRejCasue13
Function : TAU���Detach�յ�CN REJ#13ԭ���Ĵ���
Input    : NAS_EMM_CN_CAUSE_ENUM_UINT8            TAU�ܾ�ԭ��ֵ
Output   : VOS_VOID
Return   : VOS_VOID
History  :
    1.  sunjitan 00193151    2015-08-04    Draft Enact
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUCollisionDetachRejCasue13
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    (VOS_VOID)enTauRejcause;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionDetachRejCasue13 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionDetachRejCasue13_ENUM, LNAS_ENTRY);

    /* �ϱ�TAU��� */
    NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);

    if (MMC_LMM_MO_DET_CS_ONLY != NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionDetachRejCasue13: PS/CS_PS DETACH.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionDetachRejCasue13_ENUM, LNAS_FUNCTION_LABEL1);

        /*�޸�״̬��������״̬DEREG��״̬DEREG_LIMITED_SERVICE*/
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_LIMITED_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);
        NAS_EMM_TAU_CollisionDetachProc();

        /* ����DETACH*/
        NAS_LMM_DeregReleaseResource();
    }
    else
    {
        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        NAS_EMM_TAU_CollisionDetachProc();

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();
    }

    return;

}

/*******************************************************************************
Module   : NAS_EMM_TAU_TAUCollisionDetachRejCasue22
Function : TAU���Detach�յ�CN REJ#22ԭ���Ĵ���
Input    : NAS_EMM_CN_CAUSE_ENUM_UINT8            TAU�ܾ�ԭ��ֵ
Output   : VOS_VOID
Return   : VOS_VOID
History  :
    1.  sunjitan 00193151    2015-08-04    Draft Enact
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUCollisionDetachRejCasue22
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    (VOS_VOID)enTauRejcause;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionDetachRejCasue22 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionDetachRejCasue22_ENUM, LNAS_ENTRY);

    /* �ϱ�TAU��� */
    NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);

    if (MMC_LMM_MO_DET_CS_ONLY != NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionDetachRejCasue22: PS/CS_PS DETACH.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionDetachRejCasue22_ENUM, LNAS_FUNCTION_LABEL1);

        /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /*���TAU���ȫ�ֱ�����֪ͨESM��APPȥע��*/
        NAS_EMM_TAU_CollisionDetachProc();

        /*����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
        NAS_LMM_DeregReleaseResource();
    }
    else
    {
        /* �����IMSI DETACH���ͣ��򱾵�CS��ȥע�ᣬ��������TAU�������յ�RRC��·�ͷ� */

        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        /*���TAU���ȫ�ֱ�����֪ͨESM��APPȥע��*/
        NAS_EMM_TAU_CollisionDetachProc();

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();
    }

    return;

}
#if(FEATURE_ON == FEATURE_CSG)
/*******************************************************************************
Module   : NAS_EMM_TAU_TAUCollisionDetachRejCasue25
Function : TAU���Detach�յ�CN REJ#25ԭ���Ĵ���
Input    : NAS_EMM_CN_CAUSE_ENUM_UINT8            TAU�ܾ�ԭ��ֵ
Output   : VOS_VOID
Return   : VOS_VOID
History  :
    1.  yanglei 00193151    2015-10-22    Draft Enact
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUCollisionDetachRejCasue25
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    (VOS_VOID)enTauRejcause;

    NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionDetachRejCasue25 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionDetachRejCasue25_ENUM, LNAS_ENTRY);

    /* �ϱ�TAU��� */
    NAS_EMM_MmcSendTauActionResultIndRej((VOS_VOID*)NAS_EMM_NULL_PTR);

    if (MMC_LMM_MO_DET_CS_ONLY != NAS_EMM_GLO_AD_GetDetTypeMo())
    {
        NAS_EMM_TAU_LOG_INFO("NAS_EMM_TAU_TAUCollisionDetachRejCasue25: PS/CS_PS DETACH.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_TAU_TAUCollisionDetachRejCasue25_ENUM, LNAS_FUNCTION_LABEL1);

        /*�޸�״̬��������״̬DEREG��״̬DEREG_NORMAL_SERVICE*/
        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                               EMM_SS_DEREG_NORMAL_SERVICE,
                               TI_NAS_EMM_STATE_NO_TIMER);

        /*���TAU���ȫ�ֱ�����֪ͨESM��APPȥע��*/
        NAS_EMM_TAU_CollisionDetachProc();

        /*����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
        NAS_LMM_DeregReleaseResource();
    }
    else
    {
        /* �����IMSI DETACH���ͣ��򱾵�CS��ȥע�ᣬ��������TAU�������յ�RRC��·�ͷ� */

        /* ����ע����ΪPS */
        NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_PS);

        /*���TAU���ȫ�ֱ�����֪ͨESM��APPȥע��*/
        NAS_EMM_TAU_CollisionDetachProc();

        /* IMSI DETACH���ͷ���Դ */
        NAS_LMM_ImsiDetachReleaseResource();
    }

    return;

}
#endif
/*******************************************************************************
Module   : NAS_EMM_TAU_TAUCollisionDetachRejCasueOther
Function : TAU���Detach�յ�CN REJ#otherԭ���Ĵ���
Input    : NAS_EMM_CN_CAUSE_ENUM_UINT8            TAU�ܾ�ԭ��ֵ
Output   : VOS_VOID
Return   : VOS_VOID
History  :
    1.  sunjitan 00193151    2015-08-04    Draft Enact
*******************************************************************************/
VOS_VOID NAS_EMM_TAU_TAUCollisionDetachRejCasueOther
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enTauRejcause
)
{
    NAS_EMM_TAU_TAUCollisionDetachRejCasue22(enTauRejcause);
    return;
}




/*lint +e960*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



