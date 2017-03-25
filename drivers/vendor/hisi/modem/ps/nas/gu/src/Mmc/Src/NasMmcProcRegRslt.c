/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcProcRegRslt.c
  �� �� ��   : ����
  ��    ��   : z40661
  ��������   : 2010��5��9��
  ����޸�   :
  ��������   : ע�ṫ��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��05��9��
    ��    ��   : z40661
    �޸�����   : �����ļ�
  2.��    ��   : 2011��7��22��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndLmm.h"
#include "NasMmSublayerDef.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndMscc.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcCtx.h"
#include "NVIM_Interface.h"
#include "NasMmcProcUsim.h"
#include "NasMmcProcNvim.h"
#include "NasMmcProcRegRslt.h"
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
/* ɾ��ExtAppMmcInterface.h*/
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */
#include "NasMmcComFunc.h"
#include "NasMmcSndOm.h"
#include "NVIM_Interface.h"

#include "NasUsimmApi.h"

#include "NasMmcPlmnSelectionStrategy.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_PROC_REG_RSLT_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/* ��NasMmcProcRegRslt.c�ļ��д���ע�������У���Ҫ��ͨ��CAUSE�����д���
   Ȼ�������ݴ���Ϣ������ע�����ǲ��걸�ģ�Ʃ����Ҫ֪��Attemp Counter��Ϣ��
   ���ڽ�����ע��������Ϣ�����ڱ��ص�ȫ�ֱ������棬�����ڴ���ע����ʱ��
   �ɻ�����е�ע������Ϣ�������������������õ��˼�������ţ�ע����������
   ����ļܹ��õ��ȶ�  */
NAS_MMC_REG_RSLT_CTX_STRU               gstRegRsltCtx;


/* CSע�ᱻ��ԭ��ֵ��Э�鴦��,�������Ϊ:Э������ȷ�涨��ԭ��ֵ���Լ���Щ�涨��ԭ��ֵ
   ��ӳ������Ķ�Ӧԭ��ֵ�����ڱ��н�����ʽ�Ĵ���; ���򽫽����쳣��֧���д��� */
NAS_MMC_REG_FAIL_PROC_ENTITY             gastMmcProcCsRegFailCause[] =
{
    {NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR,                      NAS_MMC_ProcCsRegFailCause2ImsiUnknownInHlr},
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS,                               NAS_MMC_ProcCsRegFailCause3IllegalMs},
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME,                               NAS_MMC_ProcCsRegFailCause6IllegalMe},
    {NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW,                           NAS_MMC_ProcCsRegFailCause11PlmnNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW,                             NAS_MMC_ProcCsRegFailCause12LaNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW,                           NAS_MMC_ProcCsRegFailCause13RoamNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL,                          NAS_MMC_ProcCsRegFailCause15NoSuitableCell},

    {NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE,                          NAS_MMC_ProcCsRegFailCause17NetWorkFailure},

    /* Upon reception of the cause codes # 95, # 96, # 97, # 99 and # 111 the MS should set the attempt counter to 4.*/
    {NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG,               NAS_MMC_ProcCsRegFailCause95SemanticallyIncorrectMsg},
    {NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF,                    NAS_MMC_ProcCsRegFailCause96InvalidMandatoryInf},
    {NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE,               NAS_MMC_ProcCsRegFailCause97MsgNonExistNotImplement},
    {NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED,               NAS_MMC_ProcCsRegFailCause99IeNonExistNotImplement},
    {NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR,                           NAS_MMC_ProcCsRegFailCause111ProtocolError},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcCsRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcCsRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT,                            NAS_MMC_ProcCsRegFailCause301TimerTimeOut},
    {NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL,                         NAS_MMC_ProcCsRegFailCause302RrConnEstFail},
    {NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL,                             NAS_MMC_ProcCsRegFailCause303RrConnFail},

    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcCsRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT,                NAS_MMC_ProcCsRegFailCause402MsCfgDomainNotSupport},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcCsRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcCsRegFailCause404ForbiddenLaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcCsRegFailCause405ForbiddenLaForRoam},
    {NAS_MML_REG_FAIL_CAUSE_SIM_INVALID,                              NAS_MMC_ProcCsRegFailCause407SimInvalid},
    {NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI,                               NAS_MMC_ProcCsRegFailCause408NetDetachImsi},
    {NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT,          NAS_MMC_ProcCsRegFailCause409ServingCellDomainNotSupport},

    {NAS_MML_REG_FAIL_CAUSE_DELAY_CS_IN_TRANS_LAU,                    NAS_MMC_ProcCsRegFailCause416DealyCsInTransLau},

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    {NAS_MML_REG_FAIL_CAUSE_ECALL_INACTIVE,                          NAS_MMC_ProcCsRegFailCause417ECallInactive},
#endif
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-30, end */

    {NAS_MML_REG_FAIL_CAUSE_T3212_RUNNING,                            NAS_MMC_ProcCsRegFailCause418T3212Running},

    {NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC,                    NAS_MMC_ProcCsRegFailCause419InterRatChangeSucc},
};

/* PSע�ᱻ��ԭ��ֵ��Э�鴦��,�������Ϊ:Э������ȷ�涨��ԭ��ֵ���Լ���Щ�涨��ԭ��ֵ
   ��ӳ������Ķ�Ӧԭ��ֵ�����ڱ��н�����ʽ�Ĵ���; ���򽫽����쳣��֧���д��� */
NAS_MMC_REG_FAIL_PROC_ENTITY             gastMmcProcPsRegFailCause[] =
{
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS,                               NAS_MMC_ProcPsRegFailCause3IllegalMs},
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME,                               NAS_MMC_ProcPsRegFailCause6IllegalMe},
    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW,                      NAS_MMC_ProcPsRegFailCause7GprsServNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW,    NAS_MMC_ProcPsRegFailCause8GprsAndNonGprsNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED,                        NAS_MMC_ProcPsRegFailCause9MsIdNotDerived},
    {NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED,                        NAS_MMC_ProcPsRegFailCause10ImplicitDetached},
    {NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW,                           NAS_MMC_ProcPsRegFailCause11PlmnNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW,                             NAS_MMC_ProcPsRegFailCause12LaNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW,                           NAS_MMC_ProcPsRegFailCause13RoamNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN,              NAS_MMC_ProcPsRegFailCause14GprsNotAllowInThisPlmn},
    {NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL,                          NAS_MMC_ProcPsRegFailCause15NoSuitableCell},
    {NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT,                       NAS_MMC_ProcPsRegFailCause40NoPdpContextActived},

    /* Upon reception of the cause codes # 95, # 96, # 97, # 99 and # 111 the MS should set the GPRS attach attempt counter to 5.*/
    {NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG,               NAS_MMC_ProcPsRegFailCause95SemanticallyIncorrectMsg},
    {NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF,                    NAS_MMC_ProcPsRegFailCause96InvalidMandatoryInf},
    {NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE,               NAS_MMC_ProcPsRegFailCause97MsgNonExistNotImplement},
    {NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED,               NAS_MMC_ProcPsRegFailCause99IeNonExistNotImplement},
    {NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR,                           NAS_MMC_ProcPsRegFailCause111ProtocolError},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcPsRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcPsRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT,                            NAS_MMC_ProcPsRegFailCause301TimerTimeOut},
    {NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL,                         NAS_MMC_ProcPsRegFailCause302RrConnEstFail},
    {NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL,                             NAS_MMC_ProcPsRegFailCause303RrConnFail},

    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcPsRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT,                NAS_MMC_ProcPsRegFailCause402MsCfgDomainNotSupport},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcPsRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcPsRegFailCause404ForbiddenLaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcPsRegFailCause405ForbiddenLaForRoam},

    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS,                  NAS_MMC_ProcPsRegFailCause406ForbiddenPlmnForGprs},
    {NAS_MML_REG_FAIL_CAUSE_SIM_INVALID,                              NAS_MMC_ProcPsRegFailCause407SimInvalid},
    {NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI,                               NAS_MMC_ProcPsRegFailCause408NetDetachImsi},
    {NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT,          NAS_MMC_ProcPsRegFailCause409ServingCellDomainNotSupport},
    {NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC,                    NAS_MMC_ProcPsRegFailCause419InterRatChangeSucc},
};
#if   (FEATURE_ON == FEATURE_LTE)

/* EPSע�ᱻ��ԭ��ֵ��Э�鴦��,�������Ϊ:Э������ȷ�涨��ԭ��ֵ���Լ���Щ�涨��ԭ��ֵ
   ��ӳ������Ķ�Ӧԭ��ֵ�����ڱ��н�����ʽ�Ĵ���; ���򽫽����쳣��֧���д��� */

/* Eps ����attach�����򱻾�ԭ��ֵ��Э�鴦�� */
NAS_MMC_COMBINED_EPS_REG_REJ_PROC_ENTITY             gastMmcProcCombinedAttachEpsRegFailCause[] =
{
    {NAS_EMM_CAUSE_ILLEGAL_UE,                                        NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs},
    {NAS_EMM_CAUSE_ILLEGAL_ME,                                        NAS_MMC_ProcCombinedEpsRegFailCause6IllegalMe},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_MMC_ProcCombinedEpsRegFailCause7EpsServNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_MMC_ProcCombinedEpsRegFailCause8GprsAndNonGprsNotAllow},
    {NAS_EMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_MMC_ProcCombinedEpsRegFailCause11PlmnNotAllow},
    {NAS_EMM_CAUSE_TA_NOT_ALLOW,                                      NAS_MMC_ProcCombinedEpsRegFailCause12TaNotAllow},
    {NAS_EMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_MMC_ProcCombinedEpsRegFailCause13RoamNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcCombinedEpsRegFailCause14GprsNotAllowInThisPlmn},
    {NAS_EMM_CAUSE_NO_SUITABL_CELL,                                   NAS_MMC_ProcCombinedEpsRegFailCause15NoSuitableCell},

    {NAS_EMM_CAUSE_ESM_FAILURE,                                       NAS_MMC_ProcCombinedEpsRegFailCause19EsmFailure},
    {NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,       NAS_MMC_ProcCombinedEpsRegFailCause35ReqServOptNotAuthorizedInThisPlmn},

    {NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE,                   NAS_MMC_ProcCombinedEpsRegFailCause42SevereNetworkFailure},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcCombinedEpsRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcCombinedEpsRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT,                            NAS_MMC_ProcCombinedEpsRegFailCause301TimerTimeOut},
    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcCombinedEpsRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcCombinedEpsRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcCombinedEpsRegFailCause404ForbiddenTaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcCombinedEpsRegFailCause405ForbiddenLaForRoam},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS,                  NAS_MMC_ProcCombinedEpsRegFailCause406ForbiddenPlmnForGprs},
    {NAS_MML_REG_FAIL_CAUSE_PS_ATTACH_NOT_ALLOW,                      NAS_MMC_ProcCombinedEpsRegFailCausePsAttachNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE,                         NAS_MMC_ProcCombinedEpsRegFailCauseEpsBearerEstFail},
    {NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE,                        NAS_MMC_ProcCombinedEpsRegFailCauseMoDetach},
    {NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE,                        NAS_MMC_ProcCombinedEpsRegFailCauseMtDetach},
    {NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL,                   NAS_MMC_ProcCombinedEpsRegFailCauseT3402Running},
};

/* Eps ����tau�����򱻾�ԭ��ֵ��Э�鴦�� */
NAS_MMC_COMBINED_EPS_REG_REJ_PROC_ENTITY             gastMmcProcCombinedTauEpsRegFailCause[] =
{
    {NAS_EMM_CAUSE_ILLEGAL_UE,                                        NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs},
    {NAS_EMM_CAUSE_ILLEGAL_ME,                                        NAS_MMC_ProcCombinedEpsRegFailCause6IllegalMe},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_MMC_ProcCombinedEpsRegFailCause7EpsServNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_MMC_ProcCombinedEpsRegFailCause8GprsAndNonGprsNotAllow},
    {NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW,                     NAS_MMC_ProcCombinedEpsRegFailCause9MsidCannotDerivedByNw},
    {NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED,                           NAS_MMC_ProcCombinedEpsRegFailCause10ImplicitlyDetached},
    {NAS_EMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_MMC_ProcCombinedEpsRegFailCause11PlmnNotAllow},
    {NAS_EMM_CAUSE_TA_NOT_ALLOW,                                      NAS_MMC_ProcCombinedEpsRegFailCause12TaNotAllow},
    {NAS_EMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_MMC_ProcCombinedEpsRegFailCause13RoamNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcCombinedEpsRegFailCause14GprsNotAllowInThisPlmn},
    {NAS_EMM_CAUSE_NO_SUITABL_CELL,                                   NAS_MMC_ProcCombinedEpsRegFailCause15NoSuitableCell},
    {NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,       NAS_MMC_ProcCombinedEpsRegFailCause35ReqServOptNotAuthorizedInThisPlmn},

    {NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,                   NAS_MMC_ProcCombinedEpsRegFailCause40NoEpsBearerActived},

    {NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE,                  NAS_MMC_ProcCombinedEpsRegFailCause42SevereNetworkFailure},


    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcCombinedEpsRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcCombinedEpsRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcCombinedEpsRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcCombinedEpsRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcCombinedEpsRegFailCause404ForbiddenTaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcCombinedEpsRegFailCause405ForbiddenLaForRoam},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS,                  NAS_MMC_ProcCombinedEpsRegFailCause406ForbiddenPlmnForGprs},

    {NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE,                         NAS_MMC_ProcCombinedEpsRegFailCauseEpsBearerEstFail},
    {NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE,                        NAS_MMC_ProcCombinedEpsRegFailCauseMoDetach},
    {NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE,                        NAS_MMC_ProcCombinedEpsRegFailCauseMtDetach},
    {NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL,                   NAS_MMC_ProcCombinedEpsRegFailCauseT3402Running},
};


/* Eps ����ע��Ps��ɹ���CS�򱻾�ԭ��ֵ��Э�鴦�� */
NAS_MMC_REG_FAIL_PROC_ENTITY                        gastMmcProcCombinedEpsRegOnlyEpsSuccCause[] =
{
    {NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS,                               NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause2ImsiUnknownInHss},
    {NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE,                          NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable},
    {NAS_EMM_CAUSE_NETWORKFAILURE,                                    NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause17NetworkFailure},
    {NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE,                           NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause18CsDomainNotAvailable},
    {NAS_EMM_CAUSE_CONGESTION,                                        NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause22Congestion},
};


/* Eps ע�ᱻ��ԭ��ֵ��Э�鴦�� */
NAS_MMC_REG_FAIL_PROC_ENTITY             gastMmcProcEpsAttachRegFailCause[] =
{
    {NAS_EMM_CAUSE_ILLEGAL_UE,                                        NAS_MMC_ProcEpsAttachRegFailCause3IllegalMs},
    {NAS_EMM_CAUSE_ILLEGAL_ME,                                        NAS_MMC_ProcEpsAttachRegFailCause6IllegalMe},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_MMC_ProcEpsAttachRegFailCause7EpsServNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_MMC_ProcEpsAttachRegFailCause8GprsAndNonGprsNotAllow},
    {NAS_EMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_MMC_ProcEpsAttachRegFailCause11PlmnNotAllow},
    {NAS_EMM_CAUSE_TA_NOT_ALLOW,                                      NAS_MMC_ProcEpsAttachRegFailCause12TaNotAllow},
    {NAS_EMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_MMC_ProcEpsAttachRegFailCause13RoamNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcEpsAttachRegFailCause14GprsNotAllowInThisPlmn},
    {NAS_EMM_CAUSE_NO_SUITABL_CELL,                                   NAS_MMC_ProcEpsAttachRegFailCause15NoSuitableCell},
    {NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,       NAS_MMC_ProcEpsAttachRegFailCause35ReqServOptNotAuthorizedInThisPlmn},

    {NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE,                   NAS_MMC_ProcEpsAttachRegFailCause42SevereNetworkFailure},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcEpsAttachRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcEpsAttachRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT,                            NAS_MMC_ProcEpsAttachRegFailCause301TimerTimeOut},
    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcEpsAttachRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcEpsAttachRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcEpsAttachRegFailCause404ForbiddenTaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcEpsAttachRegFailCause405ForbiddenLaForRoam},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS,                  NAS_MMC_ProcEpsAttachRegFailCause406ForbiddenPlmnForGprs},
    {NAS_MML_REG_FAIL_CAUSE_PS_ATTACH_NOT_ALLOW,                      NAS_MMC_ProcEpsAttachRegFailCausePsAttachNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE,                         NAS_MMC_ProcEpsAttachRegFailCauseEpsBearerEstFail},
    {NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE,                        NAS_MMC_ProcEpsAttachRegFailCauseMoDetach},
    {NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE,                        NAS_MMC_ProcEpsAttachRegFailCauseMtDetach},
    {NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL,                   NAS_MMC_ProcEpsAttachRegFailCauseT3402Running},
};




/* Eps TAU����ԭ��ֵ��Э�鴦�� */
NAS_MMC_REG_FAIL_PROC_ENTITY             gastMmcProcEpsTauRegFailCause[] =
{
    {NAS_EMM_CAUSE_ILLEGAL_UE,                                        NAS_MMC_ProcEpsTauRegFailCause3IllegalMs},
    {NAS_EMM_CAUSE_ILLEGAL_ME,                                        NAS_MMC_ProcEpsTauRegFailCause6IllegalMe},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_MMC_ProcEpsTauRegFailCause7EpsServNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_MMC_ProcEpsTauRegFailCause8GprsAndNonGprsNotAllow},

    {NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW,                     NAS_MMC_ProcEpsTauRegFailCause9MsIdCannotBeDerivedByNW},
    {NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED,                           NAS_MMC_ProcEpsTauRegFailCause10EpsImplicitlyDetached},

    {NAS_EMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_MMC_ProcEpsTauRegFailCause11PlmnNotAllow},
    {NAS_EMM_CAUSE_TA_NOT_ALLOW,                                      NAS_MMC_ProcEpsTauRegFailCause12TaNotAllow},
    {NAS_EMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_MMC_ProcEpsTauRegFailCause13RoamNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcEpsTauRegFailCause14GprsNotAllowInThisPlmn},
    {NAS_EMM_CAUSE_NO_SUITABL_CELL,                                   NAS_MMC_ProcEpsTauRegFailCause15NoSuitableCell},
    {NAS_EMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,                   NAS_MMC_ProcEpsTauRegFailCause40NoEpsBearerActived},
    {NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,       NAS_MMC_ProcEpsTauRegFailCause35ReqServOptNotAuthorizedInThisPlmn},

    {NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE,                   NAS_MMC_ProcEpsTauRegFailCause42SevereNetworkFailure},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                 NAS_MMC_ProcEpsTauRegFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                            NAS_MMC_ProcEpsTauRegFailCause257AccessBarrd},
    {NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT,                            NAS_MMC_ProcEpsTauRegFailCause301TimerTimeOut},
    {NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,                              NAS_MMC_ProcEpsTauRegFailCause401OtherCause},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN,                           NAS_MMC_ProcEpsTauRegFailCause403ForbiddenPlmn},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS,            NAS_MMC_ProcEpsTauRegFailCause404ForbiddenTaForRegPrvsSvs},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM,                    NAS_MMC_ProcEpsTauRegFailCause405ForbiddenLaForRoam},
    {NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS,                  NAS_MMC_ProcEpsTauRegFailCause406ForbiddenPlmnForGprs},
    {NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE,                        NAS_MMC_ProcEpsTauRegFailCauseMoDetach},
    {NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE,                        NAS_MMC_ProcEpsTauRegFailCauseMtDetach},
    {NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL,                   NAS_MMC_ProcEpsTauRegFailCauseT3402Running},
};



/* Eps ����detach����ԭ��ֵ��Э�鴦�� */
NAS_MMC_EPS_DETACH_CAUSE_PROC_ENTITY                gastMmcProcEpsDetachCause[] =
{
    {NAS_EMM_CAUSE_IMSI_UNKNOWN_IN_HSS,                               NAS_MMC_ProcEpsDetachCause2ImsiUnknowInHss},
    {NAS_EMM_CAUSE_ILLEGAL_UE,                                        NAS_MMC_ProcEpsDetachCause3IllegalMs},
    {NAS_EMM_CAUSE_ILLEGAL_ME,                                        NAS_MMC_ProcEpsDetachCause6IllegalMe},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW,                                NAS_MMC_ProcEpsDetachCause7EpsServNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,               NAS_MMC_ProcEpsDetachCause8GprsAndNonGprsNotAllow},
    {NAS_EMM_CAUSE_PLMN_NOT_ALLOW,                                    NAS_MMC_ProcEpsDetachCause11PlmnNotAllow},
    {NAS_EMM_CAUSE_TA_NOT_ALLOW,                                      NAS_MMC_ProcEpsDetachCause12TaNotAllow},
    {NAS_EMM_CAUSE_ROAM_NOT_ALLOW,                                    NAS_MMC_ProcEpsDetachCause13RoamNotAllow},
    {NAS_EMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcEpsDetachCause14GprsNotAllowInThisPlmn},
    {NAS_EMM_CAUSE_NO_SUITABL_CELL,                                   NAS_MMC_ProcEpsDetachCause15NoSuitableCell},
};

/* Eps SR����ԭ��ֵ��Э�鴦�� */
NAS_MMC_REG_FAIL_PROC_ENTITY            gastMmcProcEpsServiceRequestFailCause[] =
{
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS,                                         NAS_MMC_ProcEpsServiceRequestFailCause3IllegalMs},
    {NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME,                                         NAS_MMC_ProcEpsServiceRequestFailCause6IllegalMe},
    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW,                                NAS_MMC_ProcEpsServiceRequestFailCause7EpsServNotAllow},

    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW,              NAS_MMC_ProcEpsServiceRequestFailCause8GprsAndNonGprsNotAllow},

    {NAS_EMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW,                               NAS_MMC_ProcEpsServiceRequestFailCause9MsIdCannotBeDerivedByNW},
    {NAS_EMM_CAUSE_EPS_IMPLICITLY_DETACHED,                                     NAS_MMC_ProcEpsServiceRequestFailCause10EpsImplicitlyDetached},

    {NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW,                                     NAS_MMC_ProcEpsServiceRequestFailCause11PlmnNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW,                                       NAS_MMC_ProcEpsServiceRequestFailCause12TaNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW,                                     NAS_MMC_ProcEpsServiceRequestFailCause13RoamNotAllow},
    {NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN,                        NAS_MMC_ProcEpsServiceRequestFailCause14GprsNotAllowInThisPlmn},
    {NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL,                                    NAS_MMC_ProcEpsServiceRequestFailCause15NoSuitableCell},
    {NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,                 NAS_MMC_ProcEpsServiceRequestFailCause35ReqServOptNotAuthorizedInThisPlmn},

    {NAS_EMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE,                                     NAS_MMC_ProcEpsServiceRequestFailCause18CsDomainNotAvailable},
    {NAS_EMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,                                 NAS_MMC_ProcEpsServiceRequestFailCause25NotAuthorizedForThisCsg},
    {NAS_EMM_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE,                                NAS_MMC_ProcEpsServiceRequestFailCause39CsDomainTempNotAvailable},

    {NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT,                                 NAS_MMC_ProcEpsServiceRequestFailCause40NoEpsBearerActived},

    {NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE,                             NAS_MMC_ProcEpsServiceRequestFailCause42SevereNetworkFailure},

    {NAS_MML_REG_FAIL_CAUSE_AUTH_REJ,                                           NAS_MMC_ProcEpsServiceRequestFailCause256AuthRej},
    {NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED,                                      NAS_MMC_ProcEpsServiceRequestFailCause257AccessBarrd},
};


#endif

NAS_MMC_ADDITIONAL_ACTION_PRIORITY_PAIR gastAdditionalActionPrioArr[] =
{
    {NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL,                           0},
    {NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION,                         1},
    {NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN,      2},
    {NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION,                         3},
    {NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT,                       4},
    {NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON,                         5},
    {NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED,                          6},
    {NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION,                7},
    {NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON,                        8},
    {NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL,                  9},
    {NAS_MMC_ADDITIONAL_ACTION_BUTT,                                   10}
};

NAS_MMC_LMM_ATTACH_CL_REG_STATUS_PRIORITY_PAIR gastLmmAttaClRegStatPrio[] =
{
    {MMC_LMM_CL_REG_STATUS_ATTACH_NOT_SEND,                            1},
    {MMC_LMM_CL_REG_STATUS_ATTACH_SEND_WAIT_CN_RSP,                    2},
    {MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_REJ,                          3},
    {MMC_LMM_CL_REG_STATUS_ATTACH_RCV_CN_ACP,                          4},
    {MMC_LMM_CL_REG_STATUS_ATTACH_T3410_EXP,                           5},
    {MMC_LMM_CL_REG_STATUS_ATTACH_CMP_SEND,                            6},
    {MMC_LMM_CL_REG_STATUS_BUTT,                                       0}
};

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRegRsltCtxAddr
 ��������  : ���µ�ǰ��ע������Ϣ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_REG_RSLT_CTX_STRU:����ע�����ṹ����Ϣ�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��20��
    ��    ��   : w00167002
    �޸�����   : ��������
*****************************************************************************/
NAS_MMC_REG_RSLT_CTX_STRU* NAS_MMC_GetRegRsltCtxAddr(VOS_VOID)
{
    return &(gstRegRsltCtx);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveRegRsltCtx
 ��������  : ���µ�ǰ��ע������Ϣ���ͺ���Ϣָ��
 �������  : enRegRsltType:��ǰ��ע������Ϣ����
              pRegRsltCtx  :��ǰ��ע������Ϣָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��20��
    ��    ��   : w00167002
    �޸�����   : ��������
  2.��    ��   : 2012��3��5��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB����:����LMM �ϱ���service����ı���
  3.��    ��   : 2012��07��05��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1����¼EPS��AttemptCounter
  4.��    ��   : 2014��5��6��
    ��    ��   : z00161729
    �޸�����   : DTS2014050602850:l������ע��eps�ɹ���csע�ᱻ#18�ܾ���disable lte��gu������ע��ɹ�����ָ����l csע�ᱻ#18�ܾ������磬l����eps����ע��ɹ���mmcû��disable lte
*****************************************************************************/
VOS_VOID  NAS_MMC_SaveRegRsltCtx(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    VOS_VOID                           *pRegRsltIndMsg
)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    /* ���µ�ǰ��ע������Ϣ���� */
    pstRegRsltCtx->enRegRsltType = enRegRsltType;

    pstRegRsltCtx->ucIsLteRegTypeEpsOnly = VOS_FALSE;

    /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-11, begin */
    /* ���������̵�ע����������ʱ����������̱�־ */
    NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_SaveRegRsltCtx: Set ucLteUnrealRegProcFlg to FALSE");
    NAS_MMC_SetLteUnrealRegProcFlg(VOS_FALSE);
    /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-11, end */

    /* ������Ϣ������ */
    switch ( enRegRsltType )
    {
        case MM_MMC_CS_REG_RESULT_IND :
            pstRegRsltCtx->unRegRsltCtx.pstCsRegRsltInd = (MMMMC_CS_REG_RESULT_IND_STRU*)pRegRsltIndMsg;
            break;

        case GMM_MMC_PS_REG_RESULT_IND :
            pstRegRsltCtx->unRegRsltCtx.pstPsRegRsltInd = (GMMMMC_PS_REG_RESULT_IND_STRU*)pRegRsltIndMsg;
            break;

        case GMM_MMC_PS_SERVICE_RESULT_IND :
            pstRegRsltCtx->unRegRsltCtx.pstServiceRsltIndMsg = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pRegRsltIndMsg;
            break;

        case GMM_MMC_PS_NETWORK_DETACH_IND :
            pstRegRsltCtx->unRegRsltCtx.pstDetachIndMsg      = (MMCGMM_NETWORK_DETACH_IND_STRU*)pRegRsltIndMsg;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case LMM_MMC_ATTACH_IND :
            pstRegRsltCtx->unRegRsltCtx.pstLmmAttachIndMsg = (LMM_MMC_ATTACH_IND_STRU*)pRegRsltIndMsg;

            if (MMC_LMM_ATT_TYPE_EPS_ONLY == pstRegRsltCtx->unRegRsltCtx.pstLmmAttachIndMsg->ulReqType)
            {
                pstRegRsltCtx->ucIsLteRegTypeEpsOnly = VOS_TRUE;
            }

            NAS_MMC_SaveEpsAttachAttemptCounter((LMM_MMC_ATTACH_IND_STRU*)pRegRsltIndMsg);

            break;

        case LMM_MMC_TAU_RESULT_IND :
            pstRegRsltCtx->unRegRsltCtx.pstLmmTauIndMsg = (LMM_MMC_TAU_RESULT_IND_STRU*)pRegRsltIndMsg;

            if ((MMC_LMM_TA_UPDATING == pstRegRsltCtx->unRegRsltCtx.pstLmmTauIndMsg->ulReqType)
             || (MMC_LMM_PS_PERIODIC_UPDATING == pstRegRsltCtx->unRegRsltCtx.pstLmmTauIndMsg->ulReqType))
            {
                pstRegRsltCtx->ucIsLteRegTypeEpsOnly = VOS_TRUE;
            }

            NAS_MMC_SaveEpsTauAttemptCounter((LMM_MMC_TAU_RESULT_IND_STRU*)pRegRsltIndMsg);

            break;

        case LMM_MMC_DETACH_IND :
            pstRegRsltCtx->unRegRsltCtx.pstLmmDetachMsg = (LMM_MMC_DETACH_IND_STRU*)pRegRsltIndMsg;
            break;

        case LMM_MMC_SERVICE_RESULT_IND :
            pstRegRsltCtx->unRegRsltCtx.pstLmmServiceIndMsg = (LMM_MMC_SERVICE_RESULT_IND_STRU*)pRegRsltIndMsg;
            break;


#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveRegRsltCtx: UNEXPECTED MSG TYPE!");
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRegRsltType
 ��������  : ���µ�ǰ��ע������Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8:����ע������Ϣ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��20��
    ��    ��   : w00167002
    �޸�����   : ��������
*****************************************************************************/
NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8 NAS_MMC_GetRegRsltType(VOS_VOID)
{
    return gstRegRsltCtx.enRegRsltType;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-4, begin */

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-4, end */


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRegRsltAttemptCounter
 ��������  : ȡ��ע������Ϣ�е�AttemptCounter��ֵ
 �������  : enRegRsltType:��ǰ��ע������Ϣ����
 �������  : ��
 �� �� ֵ  : ����AttemptCounter��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��20��
    ��    ��   : w00167002
    �޸�����   : ��������
  2.��    ��   : 2012��07��05��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1����¼EPS��AttemptCounter
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetRegRsltAttemptCounter(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType
)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulAttempCounter;

    /* Attempt Counter ��ʼ��Ϊ0 */
    ulAttempCounter = 0;
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    switch ( enRegRsltType )
    {
        case MM_MMC_CS_REG_RESULT_IND :

            /* ��ȡCSע������Ϣ�е�Attempt Counter��ֵ */
            ulAttempCounter = pstRegRsltCtx->unRegRsltCtx.pstCsRegRsltInd->ulLuAttemptCnt;
            break;

        case GMM_MMC_PS_REG_RESULT_IND :

            /* ��ȡPSע������Ϣ�е�Attempt Counter��ֵ */
            ulAttempCounter = pstRegRsltCtx->unRegRsltCtx.pstPsRegRsltInd->ulRegCounter;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case LMM_MMC_ATTACH_IND :

            /* ��ȡlmm ATTACHע������Ϣ�е�Attempt Counter��ֵ */
            ulAttempCounter = pstRegRsltCtx->ucEpsAttemptCounter;

            break;

        case LMM_MMC_TAU_RESULT_IND :

            /* ��ȡlmm TAUע������Ϣ�е�Attempt Counter��ֵ */
            ulAttempCounter = pstRegRsltCtx->ucEpsAttemptCounter;

            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRegRsltAttemptCounter: UNEXPECTED MSG TYPE!");
            break;
    }

    return ulAttempCounter;
}

/* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-11, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLteUnrealRegProcFlg
 ��������  : ��ȡ��ǰ�Ƿ���LTE��δ�����⽻����ע�����̱�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�� VOS_FALSE:��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��11��
    ��    ��   : z00359541
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetLteUnrealRegProcFlg(VOS_VOID)
{
    NAS_NORMAL_LOG1(WUEPS_PID_MMC,"NAS_MMC_SetLteUnrealRegProcFlg: Get Flg", gstRegRsltCtx.ucLteUnrealRegProcFlg);
    return gstRegRsltCtx.ucLteUnrealRegProcFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetLteUnrealRegProcFlg
 ��������  : ���õ�ǰ�Ƿ���LTE��δ�����⽻����ע�����̱�־
 �������  : ucLteUnrealRegProcFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��11��
    ��    ��   : z00359541
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID NAS_MMC_SetLteUnrealRegProcFlg(
    VOS_UINT8                           ucLteUnrealRegProcFlg
)
{
    NAS_NORMAL_LOG1(WUEPS_PID_MMC,"NAS_MMC_SetLteUnrealRegProcFlg: Set to", ucLteUnrealRegProcFlg);
    gstRegRsltCtx.ucLteUnrealRegProcFlg = ucLteUnrealRegProcFlg;
}

/* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-11, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailImsiUnnownInHlr
 ��������  : Cs Cause2�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��10��15��
    ��    ��   : s00217060
    �޸�����   : for DTS2012082308686:Csע��ʧ��ԭ��ֵΪ2,3,6,256ʱ����Ҫ����Enable Lte
  3.��    ��   : 2013��01��23��
    ��    ��   : s00217060
    �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  4.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  5.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  6.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause2ImsiUnknownInHlr(VOS_VOID)
{
#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisablteRoamFlg;

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_CsRegFailCause2ImsiUnknownInHlr())
    {
        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause3IllegalMs
 ��������  : Cs Cause3�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause3IllegalMs(VOS_VOID)
{
    /* ��ԭ��ֵ2���д��� */
    return NAS_MMC_ProcCsRegFailCause2ImsiUnknownInHlr();
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause6IllegalMe
 ��������  : Cs Cause6�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause6IllegalMe(VOS_VOID)
{
    /* ��ԭ��ֵ2���д��� */
    return NAS_MMC_ProcCsRegFailCause2ImsiUnknownInHlr();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause11PlmnNotAllow
 ��������  : Cs Cause11�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  3.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ
  4.��    ��   : 2012��11��29��
    ��    ��   : W00176964
    �޸�����   : DTS2012112902395,BVT����,hplmn����#11�������Ҫ����ע��
  5.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2014��4��18��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:���ӷ���״̬�ϱ��Ĵ���
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause11PlmnNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucRejDomain;
    NAS_MML_MS_CFG_INFO_STRU           *pstMsCfg;
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId;

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* ��ӽ�ֹ������Ϣ,�и���ʱ����Usim�����ļ� */
    if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, end */

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if ( VOS_FALSE == NAS_MML_GetHplmnRegisterCtrlFlg())
    {
        /* ��E5�汾�������´���E5�汾Ҫ������HPLMN�Ϸ�������ע�� */

        if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
        {
            /* ����ע��������ע����Ϣ�� */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                          NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);

            pstMsCfg = NAS_MML_GetMsCfgInfo();

            if ((NAS_MML_MS_MODE_PS_CS == pstMsCfg->stMsSysCfgInfo.enMsMode))
            {
                NAS_MMC_GetHplmnRejDomainInfo(&ucRejDomain);

                if (NAS_MMC_REG_DOMAIN_PS_CS != ucRejDomain)
                {
                    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

                    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
                }
            }
        }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause12LaNotAllow
 ��������  : Cs Cause12�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2014��04��30��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:���·���״̬

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause12LaNotAllow(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8          enPsAdditionalAction;

    /*��ӽ�ֹ������Ϣ*/
    NAS_MML_AddForbRegLa(NAS_MML_GetCurrCampLai());

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE_REGION);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */

    /* ��ҵ��ʱ����Ҫ����һ������:����״̬�Ѹ���Ϊregistered��������ʱ��������RAT�µ�������� */
    if (VOS_TRUE == NAS_MMC_IsNeedLauRejTrigPlmnSearch(NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    enPsAdditionalAction = NAS_MMC_GetPsAdditionalAction();
    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL != enPsAdditionalAction)
     && (NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION != enPsAdditionalAction)
     && (NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN != enPsAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause13RoamNotAllow
 ��������  : Cs Cause13�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��29��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:NAS_MML_AddForbRoamLa�����������޸�
 3.��    ��   : 2014��04��30��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:���ӷ���״̬�ϱ�����

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause13RoamNotAllow(VOS_VOID)
{
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;

    /* ���û�ָ����������ȫ�ֱ����л�ȡFORBIDEN ROAMING LAS��Ϣ */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    /* ��ӽ�ֹ������Ϣ��ȫ�ֱ����Ľ�ֹ����LA������ȥ */
    NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                           &stForbRoamLaInfo );
    pstForbPlmnInfo->ucForbRoamLaNum = stForbRoamLaInfo.ucForbRoamLaNum;
    PS_MEM_CPY( pstForbPlmnInfo->astForbRomLaList,
                stForbRoamLaInfo.astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList));

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
    /* �ϱ���Ӧ��CS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause15NoSuitableCell
 ��������  : Cs Cause15�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��29��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:��ǰ��Ϊѡ��״̬��������ӽ�ֹ������Ϣ
                 ��ѡ��״̬���Ľ�ֹ����LA������ȥ
 3.��    ��   : 2014��4��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����CSPS����״̬
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause15NoSuitableCell(VOS_VOID)
{

    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;

    /* ���û�ָ����������ȫ�ֱ����л�ȡFORBIDEN ROAMING LAS��Ϣ */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    /* ��ӽ�ֹ������Ϣ��ȫ�ֱ����Ľ�ֹ����LA������ȥ */
    NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(), &stForbRoamLaInfo );
    pstForbPlmnInfo->ucForbRoamLaNum = stForbRoamLaInfo.ucForbRoamLaNum;
    PS_MEM_CPY( pstForbPlmnInfo->astForbRomLaList,
                stForbRoamLaInfo.astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList));


    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* ���·���״̬ */
    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, end */

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */

    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause17NetWorkFailure
 ��������  : Cs 17#ԭ��ֵ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��11��
   ��    ��   : w00166186
   �޸�����   : AT&T&DCM��Ŀ
 2.��    ��   : 2014��4��29��
   ��    ��   : s00261364
   �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
 3.��    ��   : 2014��5��21��
    ��    ��   : w00167002
    �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ
                �ֶ�ѡ��ʱ�򣬷���LIMIT CAMP ON,���ٷ���ѡ����

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause17NetWorkFailure(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enAction;
    VOS_UINT8                               ucRegFailMaxCnt;
    VOS_UINT32                              ulAttemptCnt;
    VOS_UINT8                               ulLaiSameFlg;
    NAS_MML_CAMP_PLMN_INFO_STRU            *pstCampInfo     = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                       *pstLastSuccLai  = VOS_NULL_PTR;

    pstCampInfo    = NAS_MML_GetCurrCampPlmnInfo();
    pstLastSuccLai = NAS_MML_GetCsLastSuccLai();

    enAction        = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    ucRegFailMaxCnt = NAS_MML_MAX_CS_REG_FAIL_CNT;

    /* ��roaming broker���Կ�������ʹ��ROAMING BROKER�����ʧ�ܸ�������������
       δ��ʱ��ʹ�õ�ֵΪNAS_MML_MAX_CS_REG_FAIL_CNT */
    if ( VOS_TRUE == NAS_MML_GetRoamBrokerActiveFlag() )
    {
        ucRegFailMaxCnt = NAS_MML_GetRoamBrokerRegisterFailCnt();
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(MM_MMC_CS_REG_RESULT_IND);

    /* ���ƿ��ش� */
    if (VOS_TRUE == NAS_MML_GetRegFailNetWorkFailureCustomFlag())
    {
        ulLaiSameFlg = NAS_MML_CompareLai(&(pstCampInfo->stLai), pstLastSuccLai);

        /* ��ǰפ����LAI�����ϴγɹ�פ����LAI��CS UPDATE״̬����U1������ATTEMPCNT�ﵽ���ֵ��Ҫ�������� */
        if ((NAS_MML_LOCATION_UPDATE_STATUS_UPDATED != NAS_MML_GetCsUpdateStatus())
         || (VOS_FALSE == ulLaiSameFlg)
         || (ulAttemptCnt >= ucRegFailMaxCnt))
        {
            /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */

            return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
    }

    if (ulAttemptCnt < ucRegFailMaxCnt)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailCause17AttemptCounterMaxTimes();
    }

    return enAction;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause95SemanticallyIncorrectMsg
 ��������  : Cs Cause95�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:�ܾ�ԭ��ֵ95�Ĵ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause95SemanticallyIncorrectMsg(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause96InvalidMandatoryInf
 ��������  : Cs Cause96�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:�ܾ�ԭ��ֵ96�Ĵ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause96InvalidMandatoryInf(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;

    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause97MsgNonExistNotImplement
 ��������  : Cs Cause97�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:�ܾ�ԭ��ֵ97�Ĵ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause97MsgNonExistNotImplement(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause99IeNonExistNotImplement
 ��������  : Cs Cause99�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:�ܾ�ԭ��ֵ99�Ĵ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause99IeNonExistNotImplement(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause111ProtocolError
 ��������  : Cs Cause111�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:�ܾ�ԭ��ֵ111�Ĵ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause111ProtocolError(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause256AuthRej
 ��������  : Cs Reg Auth rej�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  3.��    ��   : 2012��10��15��
    ��    ��   : s00217060
    �޸�����   : for DTS2012082308686:Csע��ʧ��ԭ��ֵΪ2,3,6,256ʱ����Ҫ����Enable Lte
  4.��    ��   : 2013��01��23��
    ��    ��   : s00217060
    �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  5.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  7.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause256AuthRej(VOS_VOID)
{
#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisablteRoamFlg;

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_CsRegFailCause256AuthRej())
    {
        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause257AccessBarrd
 ��������  : Cs AccessBarrd�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
 3.��    ��   : 2012��3��10��
   ��    ��   : w00166186
   �޸�����   : CSFB&PPAC&ETWS&ISR ����
 4.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 5.��    ��   : 2013��10��15��
   ��    ��   : s00190137
   �޸�����   : ���Կ��ش��ҷ�HPLMN/RPLMN�����ֹʱ��Ҫ����PLMN����
 6.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
  7.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause257AccessBarrd(VOS_VOID)
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8   enCsUpdateStatus;
    NAS_MML_CAMP_PLMN_INFO_STRU                *pstCampInfo     = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                           *pstLastSuccLai  = VOS_NULL_PTR;

    enCsUpdateStatus = NAS_MML_GetCsUpdateStatus();
    pstCampInfo      = NAS_MML_GetCurrCampPlmnInfo();
    pstLastSuccLai   = NAS_MML_GetCsLastSuccLai();

    /* ��ǰLAI���ϴ�ע��ɹ�LAI��ͬ���Ҹ���״̬ΪU1 */
    if ((VOS_TRUE == NAS_MML_CompareLai(&(pstCampInfo->stLai), pstLastSuccLai))
     && (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == enCsUpdateStatus)
     && (MM_STATUS_ATTACHED == (NAS_MMC_GetMmCtx())->ucCsAttachState))
    {
        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcCsRegFailCause257AccessBarrd: Update Reg state and Service state");
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NORMAL_SERVICE);
        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */
    }
    else
    {
        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    /*���Կ��ش��ҷ�HPLMN/RPLMN�����ֹʱ��Ҫ����PLMN����*/
    if (VOS_TRUE == NAS_MMC_IsAccBarPlmnSearch())
    {
        return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }
    else
    {
        return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause301TimerTimeOut
 ��������  : Cs Cause:NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT �Ĵ���
 �������  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ�����
 2.��    ��   : 2012��6��11��
   ��    ��   : w00166186
   �޸�����   : AT&T&DCM��Ŀ
 3.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 4.��    ��   : 2014��04��30��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause301TimerTimeOut(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;


    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_GetSingleDomainFailAction(NAS_MML_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);

        if (NAS_MMC_ADDITIONAL_ACTION_BUTT != enAction)
        {
            enPrioAdditionalAction = NAS_MMC_GetPsAdditionalAction();
            enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);

            /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

            if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
            {
                NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }
            else
            {
                NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            }
            /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */


            return enAction;
        }
        else
        {
            enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
        }
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause302RrConnEstFail
 ��������  : Cs Cause:NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL �Ĵ���
 �������  :
             VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ�����
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause302RrConnEstFail(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause303RrConnFail
 ��������  : Cs Cause:NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL�Ĵ���
 �������  : VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ�����
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause303RrConnFail(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause401OtherCause
 ��������  : Cs Other Cause�Ĵ���
 �������  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��29��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
                 1)  attemptCount < MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
                 2)  attemptCount >= MaxCountʱ���޶�������Ҫ�ȴ�����һ�����ע����,����NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION
                 3)  attemptCount >= MaxCountʱ���ж�MaxCount�Ķ��ƣ�Roaming Broker,cause<111���������������VDF�� Steer of  roaming��DT�Ķ������󣩣�
                     ����NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION

 2.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : DTS2011111603330:����ǰ��LAI�����ı䣬��ʹʧ�ܴ���δ�ﵽ
                ������,Ҳ����Ϊ���Ʒ���״̬��

 3.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS20111112105560:roamingbroker ���Կ����������ʧ�ܴ�������Ϊ1��
                �������쳣�ͷ�һ�ξͷ�����������ʵ��Ӧ����ע��ʧ��ԭ��ֵС��
                111ʱ���ŷ���������

 4.��    ��   : 2012��1��3��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                 NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSEʱ������NAS_MMC_ADDITIONAL_ACTION_BUTT
                 ,��ʾMMC����Ҫд�뵱ǰCS��ADDITIONAL ACTIONֵ��
 5.��    ��   : 2012��2��3��
   ��    ��   : w00167002
   �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                 ���ֺ���������һ���ԡ�
 6.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 7.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause401OtherCause(VOS_VOID)
{
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt >= NAS_MML_MAX_CS_REG_FAIL_CNT)
    {
        /* ��ȡCS��PS��additon action��ȡ�����ȼ����ж��Ƿ���Ҫ������
           �������Ҫ����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPsAdditionalAction   = NAS_MMC_GetPsAdditionalAction();
        enCsAdditionalAction   = NAS_MMC_GetCsAdditionalAction();

        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */
    }

    /* ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause402MsCfgDomainNotSupport
 ��������  : ������:Cs/only,��ǰ����CS only
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��1��13��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:��ǰ��ONPLMNʱ�����յ����ΪCS��֧�֣�
                  ����Ҫ�ж�1)PS���Ƿ���LIMIT_CAMP_ON 2)AVAILABLE��ʱ��δ����
                             3)PS��׼����ע��,��MMC��Ҫ��������
                  ��Ӧ��������:
                  ��ѡ��״̬���е�ǰפ��������һ���򱻾�12��һ����#14��
                  ��ON PLMN״̬����פ������ʱ�û���ע�ᱻ��#12����DETACH��
                  ����CS���ʱ��LIMITED_CAMP_ON���ʲ�������������ʵ����Ҫ��������.
  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�

  4.��    ��   : 2012��4��18��
    ��    ��   : z40661
    �޸�����   : DTS2012032204099,CCģʽ������CGģʽ��MMC����������
  5.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2013��11��30��
    ��    ��   : z00161729
    �޸�����   : DTS2013112809149:9230 nv�����ý�ֹ���뼼��Ϊw��g���ֶ�����ģʽפ��g��23002�ɹ���
                syscfg����w only��anycellפ��24005���ᷴ������w��anycell����
  8.��    ��   : 2014��04��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause402MsCfgDomainNotSupport(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;
    VOS_UINT8                                               ucPsAttachAllow;
    VOS_UINT32                                              ulRlst;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;


    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    enFsmId                = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);
    ucPsAttachAllow        = NAS_MML_GetPsAttachAllowFlg();

    /* ��ǰ��ONPLMN,PLMN_LISTʱ�����յ����ΪCS��֧�֣�����Ҫ�жϴ�ʱ�Ƿ���Ҫ����������
       1)PS����LIMIT_CAMP_ON 2)AVAILABLE��ʱ��δ���� 3)PS��׼����ע��,��MMC��Ҫ��������
    */
    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
        {
            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }

        pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();
        /* ��forbid plmn for gprs�б��� */
        ulRlst = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                              pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                              pstForbidPlmnInfo->astForbGprsPlmnList);
        if ( (VOS_TRUE                  == ucPsAttachAllow)
          && (VOS_TRUE                  == ulRlst)
          && (NAS_MMC_TIMER_STATUS_STOP == enAvailableTimerStatus) )
        {
            return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }
    }

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause
 ��������  : �ж�δ�����罻��ע��ʧ��ԭ��ֵ403-409/access bar�Ƿ���Ҫ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ����
             VOS_FALSE - ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��30��
    ��    ��   : z00161729
    �޸�����   : DTS2013112809149:9230 nv�����ý�ֹ���뼼��Ϊw��g���ֶ�����ģʽפ��g��23002�ɹ���
                 syscfg����w only��anycellפ��24005���ᷴ������w��anycell����
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause( VOS_VOID )
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                                              ulGsmOnlyFlg;
    VOS_UINT32                                              ulGsmForbFlg;
    VOS_UINT32                                              ulUserSpecPlmnForbPlmnFlag;

    ulGsmOnlyFlg                = NAS_MML_IsGsmOnlyMode(NAS_MML_GetMsPrioRatList());
    ulGsmForbFlg                = NAS_MML_GetGsmForbidFlg();
    pstUserSpecPlmn             = NAS_MMC_GetUserSpecPlmnId();

    /* 1.USIM����ֹGSM�����û�����GSM only������VOS_FALSE,�������� */
    if ((VOS_TRUE == ulGsmForbFlg)
     && (VOS_TRUE == ulGsmOnlyFlg) )
    {
        return VOS_FALSE;
    }

    /* 2.���UE���õ�������ʽ������ֹ���������� */
    if (VOS_TRUE == NAS_MML_IsAllMsRatInForbiddenList())
    {
        return VOS_FALSE;
    }

    /* 3.����Ч���������� */
    if ( VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_FALSE;
    }

    /* ��ǰΪ�ֶ�ģʽ���û�ָ���������ڽ�ֹ�����б��У��������� */
    ulUserSpecPlmnForbPlmnFlag    = NAS_MML_IsPlmnIdInForbidPlmnList( &(pstUserSpecPlmn->stPlmnId) );
    if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
       && (VOS_TRUE == ulUserSpecPlmnForbPlmnFlag))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCauseForbiddenPlmn
 ��������  : ������:Cs 11��ԭ��ֵ���ܻ�ǰ���ֶ�ָ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��12��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                  ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                  ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                  ���жϷŵ������Ӻ��������жϡ�
  3.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  4.��    ��   : 2013��11��30��
    ��    ��   : z00161729
    �޸�����   : DTS2013112809149:9230 nv�����ý�ֹ���뼼��Ϊw��g���ֶ�����ģʽפ��g��23002�ɹ���syscfg����w only��anycellפ��24005���ᷴ������w��anycell����
  5.��    ��   : 2014��04��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause403ForbiddenPlmn(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                                              ulUserSpecPlmnFlag;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnId        = VOS_NULL_PTR;

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    enFsmId = NAS_MMC_GetCurrFsmId();
    switch ( enFsmId )
    {
        case NAS_MMC_FSM_L1_MAIN :
        case NAS_MMC_FSM_PLMN_LIST :

            if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
            {
                return NAS_MMC_ADDITIONAL_ACTION_BUTT;
            }

            /* Ĭ�Ϸ���NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ */
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

            /* �����³�����Ҫ����:�ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,�ҵ�ǰPLMN����EPlmn�б��
               Available��ʱ��δ����������Ϊ��ǰplmn �Ѿ�ʧЧ�ˣ���Ҫ�������� */

            /* �ֶ�ģʽ�жϵ�ǰ�����Ƿ����û�ָ�������� */
            pstCurPlmnId       = NAS_MML_GetCurrCampPlmnId();
            pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
            ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId,
                                                        &(pstUserSpecPlmn->stPlmnId));

            /* �ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,�ҵ�ǰPLMN����EPlmn�б��
               ����Ϊ��ǰplmn �Ѿ�ʧЧ�ˣ�Available ��ʱ��δ��������Ҫ�������� */
            if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
              && (VOS_FALSE                          == ulUserSpecPlmnFlag)
              && (NAS_MMC_TIMER_STATUS_STOP          == enAvailableTimerStatus) )
            {
                enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            }

            break;

        /* ��Ҫ�������� */
        default:
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            break;
    }

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    /* ֻ������һ����Ҫ����ʱ���ű�״̬2��ȥ������Ҫ����ʱ��״̬0 */
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT == enAdditionalAction)
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    return enAdditionalAction;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause404ForbiddenLaForRegPrvsSvs
 ��������  : Cs Cause404:NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause404ForbiddenLaForRegPrvsSvs(VOS_VOID)
{
    /* ��ע�ᱻ��ԭ��#12�Ĵ���һ�� */
    return NAS_MMC_ProcCsRegFailCause12LaNotAllow();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause405ForbiddenLaForRoam
 ��������  : ������:Cs 13��15��ԭ��ֵ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��12��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��21��
    ��    ��   : w00167002
    �޸�����   : DTS2011102100710:ע�ᱻ��ԭ��ֵ#13��#15ʱ���������FORB ROAM
                  LA��Ϣ�б�����ӱ���ԭ��ֵ�Ĵ洢������������LAI�Ͼܾ���ԭ��
                 ֵ��MMC���յ�MM/GMM�ϱ��ܾ�ԭ��ֵ#13,#15�ļ�������Ϣʱ��MMC����
                 ��ͬ���������ԡ�
  3.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                     ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                     ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                     ���жϷŵ������Ӻ��������жϡ�
  4.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  5.��    ��   : 2014��04��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause405ForbiddenLaForRoam(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;                              /* �洢ע����CS�򱻾���Ϣ */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;                              /* �洢ע����PS�򱻾���Ϣ */

    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


    /* ��ǰ��ONPLMN����PLMN LIST״̬������ʱ��������פ��̬����δ��������ʵ��������������£�
       �����µ�ǰAdditionalActionֵ */
    enFsmId = NAS_MMC_GetCurrFsmId();
    if ( (NAS_MMC_FSM_L1_MAIN == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        /* ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ,MMC
           ��������ЧAdditionalActionֵ */
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }


    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    /* ��ǰ������ONPLMN����PLMN LIST״̬�����账��ܾ�ԭ��ֵ�����ز�ͬ���������� */

    /* ԭ��ֵ��ʼ��Ϊ#13,�������쳣������г�������� */
    enCsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );

    /* ��CS�����PS����һ�����ԭ��ֵΪ#13,����г�������� */
    if ( (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enPsCause))
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    /* �����վܾ�ԭ��ֵ#15���������Խ������� */
    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;


}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause407SimInvalid
 ��������  : ������:��ǰCS����Ч
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��5��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  3.��    ��   : 2012��3��1��
    ��    ��   : z40661
    �޸�����   : DTS2012022401628������л�������
  4.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
                  ���ֺ���������һ���ԡ�
  5.��    ��   : 2014��04��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause407SimInvalid(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* ���·���״̬ */
    NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    /* �����ڱ�ʾ�϶���ע�ᱻ�ܹ� */
    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }


    enFsmId = NAS_MMC_GetCurrFsmId();
    if ( (NAS_MMC_FSM_L1_MAIN == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        /* ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ,MMC
           ��������ЧAdditionalActionֵ */
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause408NetDetachImsi
 ��������  : Csע��ʧ��ԭ��:NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��01��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause408NetDetachImsi(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */

    /* ��ȡCSPS addition,�������Ҫ�������������CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    enPsAdditionalAction   = NAS_MMC_GetPsAdditionalAction();
    enCsAdditionalAction   = NAS_MMC_GetCsAdditionalAction();

    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    /* ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ,
       MMC��������ЧAdditionalActionֵ*/
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause409ServingCellDomainNotSupport
 ��������  : ������:��ǰС����֧��CS��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                  ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                  ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                  ���жϷŵ������Ӻ��������жϡ�
  3.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  4.��    ��   : 2013��1��31��
    ��    ��   : t00212959
    �޸�����   : DTS2013012909238:�ֶ�ģʽ�£���ģ��һ����ע�ᱻ#11�ܾ���һ����֧�֣���ѭ����ͣ�Ľ���anycell���������ܡ�

  5.��    ��   : 2013��4��1��
    ��    ��   : w00167002
    �޸�����   : DTS2013032701683:�޿�������ϵͳ��ϢָʾPS��֧�֣�MMC����ѭ������
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2013��11��30��
    ��    ��   : z00161729
    �޸�����   : DTS2013112809149:9230 nv�����ý�ֹ���뼼��Ϊw��g���ֶ�����ģʽפ��g��23002�ɹ���
                 syscfg����w only��anycellפ��24005���ᷴ������w��anycell����
  8.��    ��   : 2014��04��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
  9.��    ��   : 2015��11��24��
    ��    ��   : w00167002
    �޸�����   : DTS2015112405788:�ں������,�����ǰ����CS/PS���޷������ϱ���
                 MMA����MMA��Ҫ����CS/PS�ķ���״̬���Ÿ�stk�·�LOCATION STATUS NTF
                 ��Ϣ�����ղ�������Ϣ���򲻽���IMSI�л���
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause409ServingCellDomainNotSupport(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    /* ���·���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

    enFsmId                = NAS_MMC_GetCurrFsmId();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    /* ��ǰ��ONPLMNʱ�����յ����ΪCS��֧�֣�����Ҫ�жϴ�ʱ�Ƿ���Ҫ����������
       1)PS����LIMIT_CAMP_ON 2)AVAILABLE��ʱ��δ���� 3)PS��׼����ע��,��MMC��Ҫ��������
    */
    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
        {
            return NAS_MMC_ADDITIONAL_ACTION_BUTT;
        }

        if (NAS_MMC_TIMER_STATUS_RUNING               == enAvailableTimerStatus)
        {
            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }


        /* ��L1 MAINʱ�������ǰ���޿�����PS���ز���Ҫ���� */
        if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
        {
            /* ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ,MMC
                ��������ЧAdditionalActionֵ */
            return NAS_MMC_ADDITIONAL_ACTION_BUTT;
        }
    }


    enPrioAdditionalAction = NAS_MMC_GetPsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause416DealyCsInTransLau
 ��������  : Cs �쳣ԭ��ֵ�Ĵ���
 �������  :
             VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��1��17��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause416DealyCsInTransLau(VOS_VOID)
{
    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause418T3212Running
 ��������  : Eps T3402��ʱ���������еĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��4��
    ��    ��   : w00167002
    �޸�����   : DTS2014052603967:CS only����AС��ע��ʧ��17��Ǩ�Ƶ�BС������BС��
                �ǽ�ֹPLMNС����MMǨ�Ƶ�LIMIT service״̬������������AС�������
                ������LAU.
                ��LAUʧ��Ǩ�Ƶ�U2״̬ʱ���¼��ǰ��LAI��Ϣ���ڿ������û�����CS/CS_PS
                DETACHʱ���������·���LAUʱ���������LAI��Ϣ��
                �ں�����������С������U2״̬�������ǰ��LAI�ڼ�¼��LAI���棬��
                ������LAU.
  2.��    ��   : 2016��04��20��
    ��    ��   : j00174725
    �޸�����   : DTS2016041210543
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause418T3212Running(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;
    VOS_UINT8                                               ucSingleDomainSrchFlag;

    VOS_UINT32                                              ulCsRejSearch;

    ulCsRejSearch           = NAS_MML_GetCsRejSearchSupportFlg();

    enFsmId                = NAS_MMC_GetCurrFsmId();

    /* ���·���״̬ */
    NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);

    /* �жϵ�ǰ�����Ƿ�����SOR׼��, ����ֱ�ӷ���LAU */
    if ( (VOS_TRUE == NAS_MMC_IsSorTriggerAdditionalLau())
      && (VOS_TRUE == ulCsRejSearch))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcCsRegFailCause418T3212Running SOR LAU");
        /* ���additional lau��Ϣ */
        NAS_MML_InitSorAdditionalLauCtx();

        /* LIST�ѽ�����֪ͨMM���ʹ���SOR��LAU */
        NAS_MMC_SndMmLauReq(MMC_MM_LAU_REQ_REASON_SOR);

        return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }

    /* ȡ�õ�ǰ��CS/PS���ADDITIONAL ACTIONֵ */
    enCsAdditionalAction   = NAS_MMC_GetCsAdditionalAction();
    enPsAdditionalAction   = NAS_MMC_GetPsAdditionalAction();

    /* ��ѡ��״̬����Ҫ��ȡ��ǰ��CS���ADDITIONAL ACTIONֵ */
    if ( (NAS_MMC_FSM_PLMN_SELECTION == enFsmId)
      || (NAS_MMC_FSM_BG_PLMN_SEARCH == enFsmId) )
    {
        /* �����������Ʊ�ʶ */
        ucSingleDomainSrchFlag = NAS_MML_GetDtSingleDomainPlmnSearchFlag();

        /* ������ʧ�ܱ����Ƿ���������������VDF���ƴ򿪻�DT�����������ƴ�ʱ����������ʱ���ȴ�PS��ע���� */
        if ((VOS_TRUE == ulCsRejSearch)
         || (VOS_TRUE == ucSingleDomainSrchFlag))
        {
            enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }
    }

    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    return enCsAdditionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause419HoSucc
 ��������  : ע������̣��л�֮����ϵͳ��Ϣ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��13��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI:�л�������ϵͳ��Ϣ�Ĵ���
  2.��    ��   : 2015��7��13��
    ��    ��   : s00217060
    �޸�����   : DTS2015070907463:ԭ��ֵ��չ���������޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause419InterRatChangeSucc(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat               = NAS_MML_GetCurrNetRatType();
    pstCampPlmnInfo     = NAS_MML_GetCurrCampPlmnInfo();

    /* �����ǰ��ģ��פ����Ϣ��Ľ��뼼����ͬ��MMC�Ѿ��յ�������ϱ���ϵͳ��Ϣ�����ù���ϵͳ��Ϣ */
    /* pstCampPlmnInfo->enNetRatType���յ�RESUME_INDʱ���£�pstCampPlmnInfo->stLai.enCampPlmnNetRat���յ�ϵͳ��Ϣʱ���� */
    if (enRat != pstCampPlmnInfo->stLai.enCampPlmnNetRat)
    {
        /* ����CampPlmnInfo�е�Ratֵ */
        pstCampPlmnInfo->stLai.enCampPlmnNetRat     = enRat;

        /* ϵͳ��ģʽ��ȱʡֵ,�л��������϶�����ģ�ģ�enRat��������BUTT */
        if (NAS_MML_NET_RAT_TYPE_GSM == enRat)
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_EDGE;
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_WCDMA;
        }
        else
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_LTE;
        }

        /* ����ϵͳ��Ϣ */
        NAS_MMC_SndMsccSysInfo();
    }

    /* ֪ͨTAF��ǰ��ע��״̬ */
    NAS_MMC_ChangeCsRegState(NAS_MML_GetCsRegStatus());

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetCsServiceStatus());

    /* ����ֵ������¼��ȫ�ֱ������ݶ�ΪBUTT����Ӱ��ԭ�������� */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause421HoWaitSysinfoTimeout
 ��������  : ע������̣��л�֮����ϵͳ��Ϣ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2016��1��28��
    ��    ��   : w00167002
    �޸�����   : ��IMS�绰��SRVCC��G,û��ϵͳ��Ϣ�����·���TMSI����䣬���µ�ǰ��RAT
                 ΪGSM;���ж�RATû�иı䣬û�и�MSCC�ϱ�ϵͳ��Ϣ�����½���һֱ��ʾΪ
                 4G.
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause421HoWaitSysinfoTimeout(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat               = NAS_MML_GetCurrNetRatType();
    pstCampPlmnInfo     = NAS_MML_GetCurrCampPlmnInfo();

    /* ����CampPlmnInfo�е�Ratֵ */
    pstCampPlmnInfo->stLai.enCampPlmnNetRat     = enRat;

    /* ϵͳ��ģʽ��ȱʡֵ,�л��������϶�����ģ�ģ�enRat��������BUTT */
    if (NAS_MML_NET_RAT_TYPE_GSM == enRat)
    {
        pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_EDGE;
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
    {
        pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_WCDMA;
    }
    else
    {
        pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_LTE;
    }

    /* ����ϵͳ��Ϣ */
    NAS_MMC_SndMsccSysInfo();

    /* ֪ͨTAF��ǰ��ע��״̬ */
    NAS_MMC_ChangeCsRegState(NAS_MML_GetCsRegStatus());

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetCsServiceStatus());

    /* ����ֵ������¼��ȫ�ֱ������ݶ�ΪBUTT����Ӱ��ԭ�������� */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCauseAbnormalCause
 ��������  : Cs �쳣ԭ��ֵ�Ĵ���
 �������  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��1��17��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCauseAbnormalCause(
    VOS_UINT16                          usCause,
    VOS_UINT32                          ulAttemptCnt
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT8                                               ucRegFailMaxCnt;

    /* ��ʼ��CS��Attempt Counter����ע��ʧ�ܵ�������Ϊ4 */
    ucRegFailMaxCnt = NAS_MML_MAX_CS_REG_FAIL_CNT;

    /* ��roaming broker���Կ�������ʹ��ROAMING BROKER�����ʧ�ܸ�������������
       δ��ʱ��ʹ�õ�ֵΪNAS_MML_MAX_CS_REG_FAIL_CNT */
    if ( VOS_TRUE == NAS_MML_GetRoamBrokerActiveFlag() )
    {
        ucRegFailMaxCnt = NAS_MML_GetRoamBrokerRegisterFailCnt();
    }

    if (ulAttemptCnt < ucRegFailMaxCnt)
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes
 ��������  : Csע��ʧ���������Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
 4.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : CSע��ʧ�ܼ����ֹLA�б����Դ�ʱ���败��ָ��������
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT8                                               ucSingleDomainSrchFlag;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_REG_RSLT_CTX_STRU                               *pstRegRsltCtx              = VOS_NULL_PTR;

    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    /* ���·���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

    /* �����������Ʊ�ʶ */
    ucSingleDomainSrchFlag = NAS_MML_GetDtSingleDomainPlmnSearchFlag();

    /* ������ʧ�ܱ����Ƿ���������������VDF���ƴ򿪻�DT�����������ƴ�ʱ����������ʱ���ȴ�PS��ע���� */
    if ((VOS_TRUE == NAS_MML_GetCsRejSearchSupportFlg())
     || (VOS_TRUE == ucSingleDomainSrchFlag))
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    /* ��ҵ��ʱ��NV�����Ƿ���Ҫ������������ */
    else if ((VOS_TRUE == NAS_MMC_IsNeedLauRejTrigPlmnSearch(pstRegRsltCtx->unRegRsltCtx.pstCsRegRsltInd->enRegFailCause)))
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    /* CSע��ʧ�ܼ����ֹLA���Դ� */
    else if (VOS_TRUE == NAS_MMC_IsFailCauseInCustomizedForbLaCfgList(pstRegRsltCtx->unRegRsltCtx.pstCsRegRsltInd->enRegFailCause))
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    else
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    enPrioAdditionalAction = NAS_MMC_GetPsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


    return enAction;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause17AttemptCounterMaxTimes
 ��������  : Csע��ʧ���������Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   : 2014��5��21��
   ��    ��   : w00167002
   �޸�����   : DTS2014051602857����:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ
                �ֶ�ѡ��ʱ�򣬷���LIMIT CAMP ON,���ٷ���ѡ����
 4.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : CSע��ʧ�ܼ����ֹLA�б����Դ�ʱ���败��ָ��������
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause17AttemptCounterMaxTimes(VOS_VOID)
{
    NAS_MML_SOR_ADDITIONAL_LAU_STRU                        *pstAdditionalLau            = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCampInfo                 = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT8                                               ucSingleDomainSrchFlag;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    VOS_UINT8                                               ucRegFailMaxCnt;
    VOS_UINT32                                              ulAttemptCnt;

    ucRegFailMaxCnt = NAS_MML_MAX_CS_REG_FAIL_CNT;

    /* ��roaming broker���Կ�������ʹ��ROAMING BROKER�����ʧ�ܸ�������������
       δ��ʱ��ʹ�õ�ֵΪNAS_MML_MAX_CS_REG_FAIL_CNT */
    if ( VOS_TRUE == NAS_MML_GetRoamBrokerActiveFlag() )
    {
        ucRegFailMaxCnt = NAS_MML_GetRoamBrokerRegisterFailCnt();
    }

    ulAttemptCnt        = NAS_MMC_GetRegRsltAttemptCounter(MM_MMC_CS_REG_RESULT_IND);

    pstAdditionalLau    = NAS_MML_GetSorAdditionalLauCtx();
    pstCampInfo         = NAS_MML_GetCurrCampPlmnInfo();

    /* ���·���״̬ */
    NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �����������Ʊ�ʶ */
    ucSingleDomainSrchFlag = NAS_MML_GetDtSingleDomainPlmnSearchFlag();

    /* ������ʧ�ܱ����Ƿ���������������VDF���ƴ�ʱ����������ʱ���ȴ�PS��ע���� */
    if (VOS_TRUE == NAS_MML_GetCsRejSearchSupportFlg())
    {

        /* SOR�ֶ�ѡ��ģʽ��������פ�� */
        if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
        {
            enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }

        /* ���SOR���Զ��ƴ򿪣���ǰCOUNTER�ﵽ��������������additional LAU��Ϣ */
        else if ( ulAttemptCnt == ucRegFailMaxCnt )
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcCsRegFailCause17AttemptCounterMaxTimes: ulAttemptCnt == ucRegFailMaxCnt");
            pstAdditionalLau->ucAdditionalLauFlag = VOS_TRUE;
            PS_MEM_CPY(&(pstAdditionalLau->stLai), &(pstCampInfo->stLai), sizeof(NAS_MML_LAI_STRU));

            enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            if (VOS_TRUE == NAS_MMC_IsFailCauseInCustomizedForbLaCfgList(NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE))
            {
                enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            }
            else if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER))
            {
                enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
            }
            else
            {
                enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            }

        }
    }

    /* DT�����������ƴ�ʱ����������ʱ���ȴ�PS��ע���� */
    else if (VOS_TRUE == ucSingleDomainSrchFlag)
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    /* ��ҵ��ʱ��NV���ƴ򿪣���Ҫ������������ */
    else if (VOS_TRUE == NAS_MMC_IsNeedLauRejTrigPlmnSearch(NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE))
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    /* CSע��ʧ�ܼ����ֹLA���Դ���ʧ��ԭ��ֵ������ */
    else if (VOS_TRUE == NAS_MMC_IsFailCauseInCustomizedForbLaCfgList(NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE))
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    else
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    enPrioAdditionalAction = NAS_MMC_GetPsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    return enAction;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailAttemptCounterMaxTimes
 ��������  : Csע��ʧ���������Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��3��29��
   ��    ��   : z00161729
   �޸�����   : DTS2014032200128:g��cs only cs���ϱ��ķ���״̬Ϊ���Ʒ���ע��״̬�ϱ�Ϊפ��home���磬���½�����ʾ������������ʧ��
 3.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc

 4.��    ��   : 2014��10��22��
   ��    ��   : w00167002
   �޸�����   : DTS2014101305830:��PLMN�ı�ʱ�򣬸��·���״̬��
                ����˹�ⳡ����:��25002�����4G��ע��ɹ����ض���G�£�����RAU
                ʧ��(ps/cs cause:303),�������µķ���״̬���û����鲻�á��ڶ���RAU
                �ͳɹ��ˡ�
                ����״̬��ʾ�Ż��Ĺ��ܣ�SE�н���ϵͳ���Ż���Ʒ�������ǰֻ������ⳡ��
                ���м����Ż��޸ġ�
 5.��    ��   : 2014��11��28��
   ��    ��   : w00281933
   �޸�����   : ����״̬��ʾ�Ż�PhaseI

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailAttemptCounterLessThanMaxTimes(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnInfo        = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                                              ulInEplmnListFlag;
    VOS_UINT32                                              ulUserSpecPlmnFlag;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnId        = VOS_NULL_PTR;

    NAS_MML_REG_STATUS_ENUM_UINT8                           enCsRegStatus;

    enCsRegStatus = NAS_MML_GetCsRegStatus();

    /* Ĭ�����õ�ǰ�����ȴ�ע���� */
    enAction      = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;


    if(NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrCsService())
    {
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
        /* ���·���״̬ */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

        /* ���֮ǰע��ɹ�����Ҫ��ע��״̬����Ϊ0 */
        if ((NAS_MML_REG_REGISTERED_HOME_NETWORK == enCsRegStatus)
         || (NAS_MML_REG_REGISTERED_ROAM == enCsRegStatus))
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
    }

    /* �Զ�ģʽ����NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT */
    if ( NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode() )
    {
        return enAction;
    }

    /* �ֶ�ģʽ�жϵ�ǰ�����Ƿ����û�ָ�������� */
    pstCurPlmnId       = NAS_MML_GetCurrCampPlmnId();
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId,
                                                &(pstUserSpecPlmn->stPlmnId));

    /* �жϵ�ǰ�����Ƿ���EPlmn�б��� */
    pstEplmnInfo       = NAS_MML_GetEquPlmnList();

    ulInEplmnListFlag  = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstCurPlmnId,
                                              pstEplmnInfo->ucEquPlmnNum,
                                              pstEplmnInfo->astEquPlmnAddr);

    /* �ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,�ҵ�ǰPLMN����EPlmn�б��
       ����Ϊ��ǰplmn �Ѿ�ʧЧ�ˣ���Ҫ�������� */
    if ( (VOS_FALSE == ulUserSpecPlmnFlag)
      && (VOS_FALSE == ulInEplmnListFlag) )
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    return enAction;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause3IllegalMs
 ��������  : Ps Cause3�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : ����Чʱ��֪ͨAPS����
  3.��    ��   : 2012��10��15��
    ��    ��   : s00217060
    �޸�����   : for DTS2012082308686:Psע��ʧ��ԭ��ֵ#3,#6,#8,#256����Ҫ����Enable Lte
  4.��    ��   : 2013��01��23��
    ��    ��   : s00217060
    �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  5.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  7.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause3IllegalMs(VOS_VOID)
{
#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisablteRoamFlg;

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    /* ���·���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_PsRegFailCause3IllegalMs())
    {
        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause6IllegalMe
 ��������  : Ps Cause6�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause6IllegalMe(VOS_VOID)
{
    /* ��PsCause6 ���� */
    return NAS_MMC_ProcPsRegFailCause3IllegalMs();
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause7GprsServNotAllow
 ��������  : Ps Cause7�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��26��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase III����:����ע���޸�

 3.��    ��   : 2011��12��01��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase IV����:disable/enable ����

 4.��    ��   : 2011��12��20��
   ��    ��   : h44270
   �޸�����   : ����Чʱ��֪ͨAPS����
 5.��    ��   : 2012��3��17��
   ��    ��   : w00176964
   �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:����LTE�������ι��ܶ���
 6.��    ��   : 2012��07��02��
   ��    ��   : s46746
   �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
 7.��    ��   : 2012��7��27��
   ��    ��   : s00217060
   �޸�����   : for CS/PS mode 1,��Disable LTEԭ��ֵ
 8.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 9.��    ��   : 2014��4��29��
   ��    ��   : s00261364
   �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
 10.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause7GprsServNotAllow(VOS_VOID)
{
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    /* ���·���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if (FEATURE_ON == FEATURE_LTE)

    /* �ж��Ƿ���Ҫdisable LTE */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* ������ε��µ�disable�Ѿ�֪ͨ��GU�����,��ʱ����Ҫ���ظ�֪ͨ */
        if (VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
        {
            NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);

            /* ��¼disable lteʱפ����������Ϣ */
            NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }
#endif
    return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause8GprsAndNonGprsNotAllow
 ��������  : Ps Cause8�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : ����Чʱ��֪ͨAPS����
  3.��    ��   : 2012��10��15��
    ��    ��   : s00217060
    �޸�����   : for DTS2012082308686:Psע��ʧ��ԭ��ֵ#3,#6,#8,#256����Ҫ����Enable Lte
  4.��    ��   : 2013��01��23��
    ��    ��   : s00217060
    �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  5.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  7.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID)
{
#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisablteRoamFlg;

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    /* ���·���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_PsRegFailCause8GprsAndNonGprsNotAllow())
    {
        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause9MsIdNotDerived
 ��������  : ps Cause:9�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2013��07��16��
    ��    ��   : w00242748
    �޸�����   : �޸��ֶ�����������ѭ��
  4.��    ��   : 2014��04��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause9MsIdNotDerived(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  ucPlmnSelMode;

    /* �ֶ�ģʽ����Ҫattach������£�����Ҫɾ��EPlmn���Զ�ģʽ���߲���Ҫ
    ATTACH��ʱ����Ҫɾ��EPLMN���˴��޸Ĳ�����Э��淶���޸�Ϊ���û����顣
    �����ֶ�ģʽEPLMN��ɾ��ʱ����������ֶ�����RAU���ܴ�����ѭ����
    �˴��޸����NAS_GMM_DeleteEPlmnList����ֶ��������ܣ�������ѭ�����⡣*/
    ucPlmnSelMode = NAS_MMC_GetPlmnSelectionMode();

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == ucPlmnSelMode))
    {
        NAS_MML_SetEplmnValidFlg(VOS_TRUE);
    }

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ��ǰ��GMM�ϱ���NET WORK DETACH IND��Ϣ���򷵻�LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON�Ƚϣ�
           �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */

        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* ����ע�����ϱ���Attempt Counter�Ƿ�ﵽ�������ֱ���д��� */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause10ImplicitDetached
 ��������  : ps Cause:10�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2013��07��16��
    ��    ��   : w00242748
    �޸�����   : �޸��ֶ�����������ѭ��
  4.��    ��   : 2014��04��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause10ImplicitDetached(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  ucPlmnSelMode;

    /* �ֶ�ģʽ����Ҫattach������£�����Ҫɾ��EPlmn���Զ�ģʽ���߲���Ҫ
    ATTACH��ʱ����Ҫɾ��EPLMN���˴��޸Ĳ�����Э��淶���޸�Ϊ���û����顣
    �����ֶ�ģʽEPLMN��ɾ��ʱ����������ֶ�����RAU���ܴ�����ѭ����
    �˴��޸����NAS_GMM_DeleteEPlmnList����ֶ��������ܣ�������ѭ�����⡣*/
    ucPlmnSelMode = NAS_MMC_GetPlmnSelectionMode();

    if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
     && (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == ucPlmnSelMode))
    {
        NAS_MML_SetEplmnValidFlg(VOS_TRUE);
    }

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ��ǰ��GMM�ϱ���NET WORK DETACH IND��Ϣ���򷵻�LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON�Ƚϣ�
           �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* ����ע�����ϱ���Attempt Counter�Ƿ�ﵽ�������ֱ���д��� */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause11PlmnNotAllow
 ��������  : Ps Cause11�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  3.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ
  4.��    ��   : 2012��07��19��
    ��    ��   : l65478
    �޸�����   : DTS2012071805908,��HOME PLMNע��ʧ��#11����������,������EM����
  5.��    ��   : 2012��11��29��
    ��    ��   : W00176964
    �޸�����   : DTS2012112902395,BVT����,hplmn����#11�������Ҫ����ע��
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2014��04��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause11PlmnNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucRejDomain;
    NAS_MML_MS_CFG_INFO_STRU           *pstMsCfg;
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId;

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    pstMsCfg = NAS_MML_GetMsCfgInfo();

    /* ��ӽ�ֹ������Ϣ,�и���ʱ����Usim�����ļ� */
    if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    /* ���·���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

    /* פ���ڷ�HOME PLMN��ʱ��ע��ܾ�#11ʱ�������� */
    if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(pstCurPlmnId))
    {
        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                 NAS_MMC_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);

        /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if ( VOS_FALSE == NAS_MML_GetHplmnRegisterCtrlFlg())
    {
        /* ��E5�汾�������´���E5�汾Ҫ������HPLMN�Ϸ�������ע�� */
        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                 NAS_MMC_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW);


        if ((NAS_MML_MS_MODE_PS_CS == pstMsCfg->stMsSysCfgInfo.enMsMode))
        {
            NAS_MMC_GetHplmnRejDomainInfo(&ucRejDomain);

            if (NAS_MMC_REG_DOMAIN_PS_CS != ucRejDomain)
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

                return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
            }
        }

    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
    else
    {
        /* EM��������:1��PS ONLY��2����ǰ��W��3���������#11ʱ,
           ��Ҫ��HOME PLMN��������ע�� */
        if ((NAS_MML_NET_RAT_TYPE_WCDMA ==  NAS_MML_GetCurrNetRatType())
         && (NAS_MML_MS_MODE_PS_ONLY == pstMsCfg->stMsSysCfgInfo.enMsMode))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }
    }

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause12LaNotAllow
 ��������  : Ps Cause12�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2014��04��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause12LaNotAllow(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8          enCsAdditionalAction;

    /*��ӽ�ֹ������Ϣ*/
    NAS_MML_AddForbRegLa(NAS_MML_GetCurrCampLai());

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    /* ���·���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE_REGION);
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

    enCsAdditionalAction = NAS_MMC_GetCsAdditionalAction();
    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL != enCsAdditionalAction)
     && (NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION != enCsAdditionalAction)
     && (NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN != enCsAdditionalAction))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause13RoamNotAllow
 ��������  : Ps Cause13�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��29��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:NAS_MML_AddForbRoamLa�����������޸�
 3.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause13RoamNotAllow(VOS_VOID)
{
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;

    /* ���û�ָ����������ȫ�ֱ����л�ȡFORBIDEN ROAMING LAS��Ϣ */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    /* ��ӽ�ֹ������Ϣ��ȫ�ֱ����Ľ�ֹ����LA������ȥ */
    NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                           &stForbRoamLaInfo );
    pstForbPlmnInfo->ucForbRoamLaNum = stForbRoamLaInfo.ucForbRoamLaNum;
    PS_MEM_CPY( pstForbPlmnInfo->astForbRomLaList,
                stForbRoamLaInfo.astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList));

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    /* ���·���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause14GprsNotAllowInThisPlmn
 ��������  : Ps Cause8�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  3.��    ��   : 2012��6��20��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ
  4.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  5.��    ��   : 2014��04��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ��ӽ�ֹGPRS PLMN ��Ϣ */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */

    /* ����ж��Ƶ�#14�Ķ���������NV�ж��ƵĶ��� */
    enAction = NAS_MMC_GetSingleDomainFailAction(NAS_MML_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN);

    if (NAS_MMC_ADDITIONAL_ACTION_BUTT == enAction)
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    /* ��ȡCS addition,����enAction�Ƚϣ��������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */


    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause15NoSuitableCell
 ��������  : Ps Cause13�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��29��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:��ǰ��Ϊѡ��״̬��������ӽ�ֹ������Ϣ
                 ����ֹ����LA������ȥ
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 4.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause15NoSuitableCell(VOS_VOID)
{
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;

    /* ���û�ָ����������ȫ�ֱ����л�ȡFORBIDEN ROAMING LAS��Ϣ */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
    stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
    PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                pstForbPlmnInfo->astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList) );

    /* ��ӽ�ֹ������Ϣ��ȫ�ֱ����Ľ�ֹ����LA������ȥ */
    NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                           &stForbRoamLaInfo );
    pstForbPlmnInfo->ucForbRoamLaNum = stForbRoamLaInfo.ucForbRoamLaNum;
    PS_MEM_CPY( pstForbPlmnInfo->astForbRomLaList,
                stForbRoamLaInfo.astForbRomLaList,
                sizeof(pstForbPlmnInfo->astForbRomLaList));


    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_FORBID_LA_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN);

    /* ���·���״̬ */
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */

    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;

}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause40NoPdpContextActived
 ��������  : Ps Cause40�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause40NoPdpContextActived(VOS_VOID)
{
    return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause95SemanticallyIncorrectMsg
 ��������  : Ps Cause95�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:�ܾ�ԭ��ֵ95�Ĵ���
 2.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause95SemanticallyIncorrectMsg(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ��ǰ��GMM�ϱ���PS SERVICE REG RSLT IND��Ϣ���򷵻�NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND ==  enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* ��ǰ��GMM�ϱ���NET WORK DETACH IND��Ϣ���򷵻�LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND ==  enRegRsltType)
    {
        /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON�Ƚϣ�
           �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */

        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause96InvalidMandatoryInf
 ��������  : Ps Cause96�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:�ܾ�ԭ��ֵ96�Ĵ���
 2.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause96InvalidMandatoryInf(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ��ǰ��GMM�ϱ���PS SERVICE REG RSLT IND��Ϣ���򷵻�NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND ==  enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* ��ǰ��GMM�ϱ���NET WORK DETACH IND��Ϣ���򷵻�LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND ==  enRegRsltType)
    {
        /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON�Ƚϣ�
           �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause97MsgNonExistNotImplement
 ��������  : Ps Cause97�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:�ܾ�ԭ��ֵ97�Ĵ���
 2.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause97MsgNonExistNotImplement(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ��ǰ��GMM�ϱ���PS SERVICE REG RSLT IND��Ϣ���򷵻�NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND ==  enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* ��ǰ��GMM�ϱ���NET WORK DETACH IND��Ϣ���򷵻�LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND ==  enRegRsltType)
    {
        /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON�Ƚϣ�
           �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause99IeNonExistNotImplement
 ��������  : Ps Cause99�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:�ܾ�ԭ��ֵ99�Ĵ���
 2.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause99IeNonExistNotImplement(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ��ǰ��GMM�ϱ���PS SERVICE REG RSLT IND��Ϣ���򷵻�NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND ==  enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* ��ǰ��GMM�ϱ���NET WORK DETACH IND��Ϣ���򷵻�LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND ==  enRegRsltType)
    {
        /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON�Ƚϣ�
           �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause111ProtocolError
 ��������  : Ps Cause111�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:�ܾ�ԭ��ֵ111�Ĵ���
 2.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   : 2014��04��8��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause111ProtocolError(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ��ǰ��GMM�ϱ���PS SERVICE REG RSLT IND��Ϣ���򷵻�NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND == enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* ��ǰ��GMM�ϱ���NET WORK DETACH IND��Ϣ���򷵻�LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON�Ƚϣ�
           �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause256AuthRej
 ��������  : Ps Reg Auth rej�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  3.��    ��   : 2012��10��15��
    ��    ��   : s00217060
    �޸�����   : for DTS2012082308686:Psע��ʧ��ԭ��ֵΪ3,6,8,256ʱ����Ҫ����Enable Lte
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��01��23��
    ��    ��   : s00217060
    �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  8.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause256AuthRej(VOS_VOID)
{
#if   (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulDisablteRoamFlg;

    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();
#endif

    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
    /* ���·���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);

#if   (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_PsRegFailCause256AuthRej())
    {
        /* ������ڽ�ֹLTE�������ε��µ�disable LTE����δ�ص�����֮ǰ��ʱҲ��֪ͨenable LTE */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_FALSE == ulDisablteRoamFlg))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause257AccessBarrd
 ��������  : Ps AccessBarrd�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  3.��    ��   : 2012��3��10��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  4.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  5.��    ��   : 2013��10��15��
    ��    ��   : s00190137
    �޸�����   : ���Կ��ش��ҷ�HPLMN/RPLMN�����ֹʱ��Ҫ����PLMN����
  6.��    ��   : 2014��04��8��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
  7.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause257AccessBarrd(VOS_VOID)
{
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;

    enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

    /* �����ǰRAI���ϴγɹ�ע���RAI��ͬ��UPDATE״̬ΪU1������ע��Ϊ1��5��
       ����ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    if ((VOS_FALSE == NAS_MML_IsRaiChanged())
     && (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == enPsUpdateStatus)
     && (GMM_STATUS_ATTACHED == (NAS_MMC_GetGmmCtx())->ucAttachSta))
    {
        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcPsRegFailCause257AccessBarrd: Update Reg state and Service state");
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */
    }
    else
    {

        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    /*���Կ��ش��ҷ�HPLMN/RPLMN�����ֹʱ��Ҫ����PLMN����*/
    if (VOS_TRUE == NAS_MMC_IsAccBarPlmnSearch())
    {
        return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }
    else
    {
        return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause301TimerTimeOut
 ��������  : ps Cause:NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT �Ĵ���
 �������  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ�����
 2.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   : 2014��04��4��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause301TimerTimeOut(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ��ǰ��GMM�ϱ���PS SERVICE REG RSLT IND��Ϣ���򷵻�NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND == enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* ��ǰ��GMM�ϱ���NET WORK DETACH IND��Ϣ���򷵻�LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON�Ƚϣ�
           �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause302RrConnEstFail
 ��������  : Ps Cause:NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL �Ĵ���
 �������  :
             VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ�����
 2.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   : 2014��04��4��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause302RrConnEstFail(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ��ǰ��GMM�ϱ���PS SERVICE REG RSLT IND��Ϣ���򷵻�NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND == enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* ��ǰ��GMM�ϱ���NET WORK DETACH IND��Ϣ���򷵻�LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON�Ƚϣ�
           �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */



        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause303RrConnFail
 ��������  : Ps Cause:NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL�Ĵ���
 �������  : VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ�����
 2.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 3.��    ��   : 2014��04��4��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause303RrConnFail(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;

    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ��ǰ��GMM�ϱ���PS SERVICE REG RSLT IND��Ϣ���򷵻�NORMAL_CAMP_ON */
    if ( GMM_MMC_PS_SERVICE_RESULT_IND == enRegRsltType)
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* ��ǰ��GMM�ϱ���NET WORK DETACH IND��Ϣ���򷵻�LIMIT_CAMP_ON */
    if ( GMM_MMC_PS_NETWORK_DETACH_IND == enRegRsltType)
    {
        /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON�Ƚϣ�
           �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */


        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause401OtherCause
 ��������  : OtherCause�Ĵ���
 �������  : VOS_UINT16                          usCause,
              VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��29��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
                1)  attemptCount < MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
                2)  attemptCount >= MaxCountʱ���޶�������Ҫ�ȴ�����һ�����ע����,����NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION
                3)  attemptCount >= MaxCountʱ���е�����������ƣ�DT�Ķ������󣩣�����NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION

 2.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : DTS2011111603330:����ǰ��RAI�����ı䣬��ʹʧ�ܴ���δ�ﵽ
                ������,Ҳ����Ϊ���Ʒ���״̬��
 3.��    ��   : 2012��1��3��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSEʱ������NAS_MMC_ADDITIONAL_ACTION_BUTT,
                ��ʾMMC����Ҫд�뵱ǰCS��ADDITIONAL ACTIONֵ��
 4.��    ��   : 2012��2��3��
   ��    ��   : w00167002
   �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                 ���ֺ���������һ���ԡ�
 5.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬

 6.��    ��   : 2014��04��4��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause401OtherCause(VOS_VOID)
{
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt  = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* ��ȡCS��PS��additon action��ȡ�����ȼ����ж��Ƿ���Ҫ������
       �������Ҫ����������Ps counter�Ѿ��ﵽ���
       �����PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    if (ulAttemptCnt >= NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enPsAdditionalAction   = NAS_MMC_GetPsAdditionalAction();
        enCsAdditionalAction   = NAS_MMC_GetCsAdditionalAction();

        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

    }

    /* ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause402MsCfgDomainNotSupport
 ��������  : ������:Ps/only,��ǰ����PS only
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��1��13��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:��ǰ��ONPLMNʱ�����յ����ΪPS��֧�֣�
                  ����Ҫ�ж�1)CS���Ƿ���LIMIT_CAMP_ON 2)AVAILABLE��ʱ��δ����
                             3)CS��׼����ע��,��MMC��Ҫ��������
                  ��Ӧ��������:
                  ��ѡ��״̬���е�ǰפ��������һ���򱻾�12��һ����#14��
                  ��ON PLMN״̬����פ������ʱ�û���ע�ᱻ��#12����DETACH��
                  ����CS���ʱ��LIMITED_CAMP_ON���ʲ�������������ʵ����Ҫ��������.
  3.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2013��11��30��
    ��    ��   : z00161729
    �޸�����   : DTS2013112809149:9230 nv�����ý�ֹ���뼼��Ϊw��g���ֶ�����ģʽפ��g��23002�ɹ���
                 syscfg����w only��anycellפ��24005���ᷴ������w��anycell����

  7.��    ��   : 2014��04��4��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause402MsCfgDomainNotSupport(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    VOS_UINT8                                               ucCsAttachAllow;

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);


    /* ��ǰ��ONPLMNʱ�����յ����ΪPS��֧�֣�����Ҫ�ж��Ƿ���Ҫ����:
       1)CS���Ƿ���LIMIT_CAMP_ON 2)AVAILABLE��ʱ��δ���� 3)CS��׼����ע��,��MMC��Ҫ��������
    */
    enFsmId                = NAS_MMC_GetCurrFsmId();
    enCsAdditionalAction   = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);
    ucCsAttachAllow        = NAS_MML_GetCsAttachAllowFlg();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
        {
            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }

        if ( (VOS_TRUE                                  == ucCsAttachAllow)
          && (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enCsAdditionalAction)
          && (NAS_MMC_TIMER_STATUS_STOP                 == enAvailableTimerStatus) )
        {
            return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }
    }

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause403ForbiddenPlmn
 ��������  : Ps �ظ���ǰפ���ڽ�ֹ����ĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��12��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                ���жϷŵ������Ӻ��������жϡ�
  3.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��11��30��
    ��    ��   : z00161729
    �޸�����   : DTS2013112809149:9230 nv�����ý�ֹ���뼼��Ϊw��g���ֶ�����ģʽפ��
                 g��23002�ɹ���syscfg����w only��anycellפ��24005���ᷴ������w��anycell����

  6.��    ��   : 2014��04��4��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause403ForbiddenPlmn(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                                              ulUserSpecPlmnFlag;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnId        = VOS_NULL_PTR;

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    /* �ֶ�ģʽ�жϵ�ǰ�����Ƿ����û�ָ�������� */
    pstCurPlmnId       = NAS_MML_GetCurrCampPlmnId();
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId,
                                                &(pstUserSpecPlmn->stPlmnId));

    enFsmId = NAS_MMC_GetCurrFsmId();

    switch ( enFsmId )
    {
        case NAS_MMC_FSM_L1_MAIN :
        case NAS_MMC_FSM_PLMN_LIST :

            if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
            {
                return NAS_MMC_ADDITIONAL_ACTION_BUTT;
            }

            /* Ĭ�Ϸ���NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ */
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

            /* �����³�����Ҫ����:�ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,�ҵ�ǰPLMN����EPlmn�б��
               Available��ʱ��δ����������Ϊ��ǰplmn �Ѿ�ʧЧ�ˣ���Ҫ�������� */

            /* �ֶ�ģʽ�жϵ�ǰ�����Ƿ����û�ָ�������� */
            pstCurPlmnId       = NAS_MML_GetCurrCampPlmnId();
            pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
            ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId,
                                                        &(pstUserSpecPlmn->stPlmnId));

            enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

            /* �ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,�ҵ�ǰPLMN����EPlmn�б��
               ����Ϊ��ǰplmn �Ѿ�ʧЧ�ˣ�Available ��ʱ��δ��������Ҫ�������� */
            if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
              && (VOS_FALSE                          == ulUserSpecPlmnFlag)
              && (NAS_MMC_TIMER_STATUS_STOP          == enAvailableTimerStatus) )
            {
                enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            }
            break;

        /* ������Ҫ�������� */
        default:
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            break;
    }

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    /* ֻ������һ����Ҫ����ʱ���ű�״̬2��ȥ������Ҫ����ʱ��״̬0 */
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT == enAdditionalAction)
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    return enAdditionalAction;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause404ForbiddenLaForRegPrvsSvs
 ��������  : Ps Cause404:NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause404ForbiddenLaForRegPrvsSvs(VOS_VOID)
{
    /* ��ע�ᱻ��ԭ��#12�Ĵ���һ�� */
    return NAS_MMC_ProcPsRegFailCause12LaNotAllow();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause405ForbiddenLaForRoam
 ��������  : ������:Ps 13��15��ԭ��ֵ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��12��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��21��
    ��    ��   : w00167002
    �޸�����   : DTS2011102100710:ע�ᱻ��ԭ��ֵ#13��#15ʱ���������FORB ROAM
                  LA��Ϣ�б�����ӱ���ԭ��ֵ�Ĵ洢������������LAI�Ͼܾ���ԭ��
                 ֵ��MMC���յ�MM/GMM�ϱ��ܾ�ԭ��ֵ#13,#15�ļ�������Ϣʱ��MMC����
                 ��ͬ���������ԡ�
  3.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                ���жϷŵ������Ӻ��������жϡ�
  4.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��

  6.��    ��   : 2014��04��4��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause405ForbiddenLaForRoam(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;                              /* �洢ע����CS�򱻾���Ϣ */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;                              /* �洢ע����PS�򱻾���Ϣ */

    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


    /* ��ǰ��ONPLMN����PLMN LIST״̬������ʱ��������פ��̬����δ��������ʵ��������������£�
       �����µ�ǰAdditionalActionֵ */
    enFsmId = NAS_MMC_GetCurrFsmId();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        /* ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ,MMC
           ��������ЧAdditionalActionֵ */
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    /* ��ǰ������ONPLMN����PLMN LIST״̬�����账��ܾ�ԭ��ֵ�����ز�ͬ���������� */

    /* ԭ��ֵ��ʼ��Ϊ#13,�������쳣������г�������� */
    enCsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );

    /* ��CS�����PS����һ�����ԭ��ֵΪ#13,����г�������� */
    if ( (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enPsCause))
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    /* �����վܾ�ԭ��ֵ#15���������Խ������� */
    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;


}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause406ForbiddenPlmnForGprs
 ��������  : Ps Cause NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                ���жϷŵ������Ӻ��������жϡ�
  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬

  5.��    ��   : 2014��04��4��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
  6.��    ��   : 2015��1��14��
    ��    ��   : b00269685
    �޸�����   : ����ж��Ƶ�#14�Ķ���������NV�ж��ƵĶ���
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause406ForbiddenPlmnForGprs(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enFailAction;

    /* ��ӽ�ֹGPRS PLMN ��Ϣ */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    /* ����ж��Ƶ�#14�Ķ���������NV�ж��ƵĶ��� */
    enFailAction = NAS_MMC_GetSingleDomainFailAction(NAS_MML_REG_DOMAIN_PS,
                                                           NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN);
    enFsmId = NAS_MMC_GetCurrFsmId();

    switch ( enFsmId )
    {
        /* ��ǰ��ONPLMN,�����ĵ�ǰ��ADDITIONAL ACTION��ֵ */
        case NAS_MMC_FSM_L1_MAIN :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            break;

        /* ��ǰ��PLMN LIST,�����ĵ�ǰ��ADDITIONAL ACTION��ֵ*/
        case NAS_MMC_FSM_PLMN_LIST :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            break;

        /* ������Ҫ���п�ѡ������ */
        default:
            if (NAS_MMC_ADDITIONAL_ACTION_BUTT == enFailAction)
            {
                enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
            }
            else
            {
                enAdditionalAction = enFailAction;
            }
            break;
    }

    /* ��ȡCS addition,�������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAdditionalAction, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    return enAdditionalAction;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause407SimInvalid
 ��������  : ������:��ǰPS����Ч
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                ���жϷŵ������Ӻ��������жϡ�

  3.��    ��   : 2012��3��1��
    ��    ��   : z40661
    �޸�����   : DTS2012022401628������л�������
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause407SimInvalid(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    /* �����ڱ�ʾ�϶���ע�ᱻ�ܹ� */
    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    }
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }


    enFsmId = NAS_MMC_GetCurrFsmId();
    if ( (NAS_MMC_FSM_L1_MAIN == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        /* ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ,MMC
           ��������ЧAdditionalActionֵ */
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause408NetDetachImsi
 ��������  : Csע��ʧ��ԭ��:NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��01��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause408NetDetachImsi(VOS_VOID)
{
    /* ������ЧACTIONֵ:NAS_MMC_ADDITIONAL_ACTION_BUTT,�����ĵ�ǰ��ADDITIONAL ACTION��ֵ*/
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause409ServingCellDomainNotSupport
 ��������  : ������:��ǰС����֧��PS��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                ���жϷŵ������Ӻ��������жϡ�
  3.��    ��   : 2013��1��31��
    ��    ��   : t00212959
    �޸�����   : DTS2013012909238:�ֶ�ģʽ�£���ģ��һ����ע�ᱻ#11�ܾ���һ����֧�֣���ѭ����ͣ�Ľ���anycell���������ܡ�
  4.��    ��   : 2013��4��1��
    ��    ��   : w00167002
    �޸�����   : DTS2013032701683:�޿�������ϵͳ��ϢָʾPS��֧�֣�MMC����ѭ������
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2013��11��30��
    ��    ��   : z00161729
    �޸�����   : DTS2013112809149:9230 nv�����ý�ֹ���뼼��Ϊw��g���ֶ�����ģʽפ��g��23002�ɹ���
                 syscfg����w only��anycellפ��24005���ᷴ������w��anycell����
  8.��    ��   : 2014��04��4��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
  9.��    ��   : 2014��5��21��
    ��    ��   : w00167002
    �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ
                �ֶ�ѡ��ʱ�򣬷���LIMIT CAMP ON,���ٷ���ѡ����
  10.��    ��   : 2015��11��24��
     ��    ��   : w00167002
     �޸�����   : DTS2015112405788:�ں������,�����ǰ����CS/PS���޷������ϱ���
                  MMA����MMA��Ҫ����CS/PS�ķ���״̬���Ÿ�stk�·�LOCATION STATUS NTF
                  ��Ϣ�����ղ�������Ϣ���򲻽���IMSI�л���
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause409ServingCellDomainNotSupport(VOS_VOID)
{

    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    /* ���·���״̬ */
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, end */

    enFsmId                = NAS_MMC_GetCurrFsmId();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
        {
            return NAS_MMC_ADDITIONAL_ACTION_BUTT;
        }

        /* ��ǰAVAILABLE��ʱ�������У�����פ�� */
        if ( NAS_MMC_TIMER_STATUS_RUNING               == enAvailableTimerStatus )
        {
            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }


        /* ��L1 MAINʱ�������ǰ���޿�����PS���ز���Ҫ���� */
        if ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
        {
            /* ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ,MMC
                ��������ЧAdditionalActionֵ */
            return NAS_MMC_ADDITIONAL_ACTION_BUTT;
        }
    }



    enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    /* SOR���ֶ�ģʽ����ʱ�򣬷���LIMIT CAMP ON */
    if (VOS_TRUE == NAS_MML_GetCsRejSearchSupportFlg())
    {
        if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
        {
            enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }
    }

    /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION�Ƚϣ�
       �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();

    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);

    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause419HoSucc
 ��������  : ע������̣��л�֮����ϵͳ��Ϣ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��13��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI:�л�������ϵͳ��Ϣ�Ĵ���
  2.��    ��   : 2015��7��13��
    ��    ��   : s00217060
    �޸�����   : DTS2015070907463:ԭ��ֵ��չ���޸ĺ�����

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCause419InterRatChangeSucc(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    enRat               = NAS_MML_GetCurrNetRatType();
    pstCampPlmnInfo     = NAS_MML_GetCurrCampPlmnInfo();

    /* �����ǰ��ģ��פ����Ϣ��Ľ��뼼����ͬ��MMC�Ѿ��յ�������ϱ���ϵͳ��Ϣ�����ù���ϵͳ��Ϣ */
    /* pstCampPlmnInfo->enNetRatType���յ�RESUME_INDʱ���£�pstCampPlmnInfo->stLai.enCampPlmnNetRat���յ�ϵͳ��Ϣʱ���� */
    if (enRat != pstCampPlmnInfo->stLai.enCampPlmnNetRat)
    {
        /* ����CampPlmnInfo�е�Ratֵ */
        pstCampPlmnInfo->stLai.enCampPlmnNetRat     = enRat;

        /* ϵͳ��ģʽ��ȱʡֵ,�л��������϶�����ģ�ģ�enRat��������BUTT */
        if (NAS_MML_NET_RAT_TYPE_GSM == enRat)
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_EDGE;
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_WCDMA;
        }
        else
        {
            pstCampPlmnInfo->enSysSubMode   = NAS_MML_RRC_SYS_SUBMODE_LTE;
        }

        /* ����ϵͳ��Ϣ */
        NAS_MMC_SndMsccSysInfo();
    }

    /* ֪ͨTAF��ǰ��ע��״̬ */
    NAS_MMC_ChangePsRegState(NAS_MML_GetPsRegStatus());

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetPsServiceStatus());

    /* ����ֵ������¼��ȫ�ֱ������ݶ�ΪBUTT����Ӱ��ԭ�������� */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCauseAbnormalCause
 ��������  : Ps �쳣ԭ��ֵ�Ĵ���
 �������  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��1��17��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailCauseAbnormalCause(
    VOS_UINT16                          usCause,
    VOS_UINT32                          ulAttemptCnt
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;

    /* ע��ʧ��Attempt Counterδ�ﵽ������ */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes();
    }
    else
    {
        /* ע��ʧ��Attempt Counter�ﵽ�򳬹��������Ĵ��� */
        enAction = NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes();
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes
 ��������  : Psע��ʧ���������Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 3.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 4.��    ��   : 2014��04��4��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
 5.��    ��   : 2014��5��21��
   ��    ��   : w00167002
   �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ
                �ֶ�ѡ��ʱ�򣬷���LIMIT CAMP ON,���ٷ���ѡ����
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailAttemptCounterMaxTimes(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT8                                               ucSingleDomainSrchFlag;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enSelectionMode;

    enSelectionMode = NAS_MMC_GetPlmnSelectionMode();
    /* ���·���״̬ */
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, end */

    /* �����������Ʊ�ʶ */
    ucSingleDomainSrchFlag = NAS_MML_GetDtSingleDomainPlmnSearchFlag();


    enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    /* SOR���ֶ�ģʽ����ʱ�򣬷���LIMIT CAMP ON */
    if ( (VOS_TRUE == NAS_MML_GetCsRejSearchSupportFlg())
      && (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enSelectionMode) )
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }
    /* ������ʧ�ܱ����Ƿ���������������DT�����������ƴ�ʱ����; ����ʱ���ȴ�PS��ע���� */
    else if (VOS_TRUE == ucSingleDomainSrchFlag)
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
    else
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    /* ��ȡCS addition,����enAction�Ƚϣ�
       �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
    enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction, enPrioAdditionalAction);
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
    else
    {
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    }
    /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    return enAction;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes
 ��������  : Psע��ʧ��Attemptδ�ﵽ�������Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��3��29��
   ��    ��   : z00161729
   �޸�����   : DTS2014032200128:g��cs only cs���ϱ��ķ���״̬Ϊ���Ʒ���ע��״̬�ϱ�Ϊפ��home���磬���½�����ʾ������������ʧ��
 3.��    ��   : 2014��04��4��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
 4.��    ��   : 2014��10��22��
   ��    ��   : w00167002
   �޸�����   : DTS2014101305830:��PLMN�ı�ʱ�򣬸��·���״̬��
                ����˹�ⳡ����:��25002�����4G��ע��ɹ����ض���G�£�����RAU
                ʧ��(ps/cs cause:303),�������µķ���״̬���û����鲻�á��ڶ���RAU
                �ͳɹ��ˡ�
                ����״̬��ʾ�Ż��Ĺ��ܣ�SE�н���ϵͳ���Ż���Ʒ�������ǰֻ������ⳡ��
                ���м����Ż��޸ġ�
 5.��    ��   : 2014��11��27��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseI��Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFailAttemptCounterLessThanMaxTimes(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnInfo        = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                                              ulInEplmnListFlag;
    VOS_UINT32                                              ulUserSpecPlmnFlag;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnId        = VOS_NULL_PTR;


    NAS_MML_REG_STATUS_ENUM_UINT8       enPsRegStatus;

    enPsRegStatus = NAS_MML_GetPsRegStatus();

    /* Ĭ�����õ�ǰ�����ȴ�ע���� */
    enAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;





    if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrPsService())
    {
        /* ���·���״̬ */
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, end */

        /* ���ps֮ǰע��ɹ���λ�����ı䣬ע��δ�ﵽ����������Ҫ��ע��״̬����Ϊ0 */
        if ((NAS_MML_REG_REGISTERED_HOME_NETWORK == enPsRegStatus)
         || (NAS_MML_REG_REGISTERED_ROAM == enPsRegStatus))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
    }

    /* �Զ�ģʽʱ��ֱ�ӷ���NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT*/
    if ( NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode() )
    {
        return enAction;
    }

    /* �жϵ�ǰ�����Ƿ����û�ָ�������� */
    pstCurPlmnId       = NAS_MML_GetCurrCampPlmnId();
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId,
                                                &(pstUserSpecPlmn->stPlmnId));

    /* �жϵ�ǰ�����Ƿ���EPlmn�б��� */
    pstEplmnInfo       = NAS_MML_GetEquPlmnList();

    ulInEplmnListFlag  = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstCurPlmnId,
                                              pstEplmnInfo->ucEquPlmnNum,
                                              pstEplmnInfo->astEquPlmnAddr);

    /* �ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,�ҵ�ǰPLMN����EPlmn�б��
       ����Ϊ��ǰplmn �Ѿ�ʧЧ�ˣ���Ҫ�������� */
    if ( (VOS_FALSE == ulUserSpecPlmnFlag)
      && (VOS_FALSE == ulInEplmnListFlag) )
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    return enAction;
}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs
 ��������  : ����ע��Combined attach not accepted by the network����
             Combined TAU not accepted by the network��Eps Cause3�Ĵ���
 �������  : ��
 �������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
             penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��17��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV ����:ע��ԭ��ֵ�Ĵ���
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
  8.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 mmc�յ�COMBINED TAU REJ(#3/6/8),�ϱ�ע��״̬�ͷ���״̬
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* ����cs ps��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    /*mmc�յ�COMBINED TAU/ATTACH REJ(#3/6/8),�ϱ�ע��״̬�ͷ���״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS,NAS_MMC_LIMITED_SERVICE);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause6IllegalMe
 ��������  : ����ע��Combined attach not accepted by the network����
             Combined TAU not accepted by the network��Eps Cause6�Ĵ���
 �������  : ��
 �������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
             penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause6IllegalMe(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs(penPsRegAdditionalAction, penCsRegAdditionalAction);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause7EpsServNotAllow
  ��������  : ����ע��Combined attach not accepted by the network����
             Combined TAU not accepted by the network��Eps Cause7�Ĵ���
 �������  : ��
 �������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
             penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��30��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:disable/enable ����
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2012��07��02��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
  5.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  6.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����  : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  7.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  8.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                   mmc�յ�COMBINED TAU REJ(#7),�ϱ�ע��״̬�ͷ���״̬

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause7EpsServNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatOrder;

    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    pstRatOrder     = NAS_MML_GetMsPrioRatList();

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    /* ����ps��״̬Ϊ��Ч */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /*�����žͷ���������CS��ע��״̬�Ͳ��ϱ���*/

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* ���·���״̬ */
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-29, begin */
    /* �˴�����ɾ�����ɾ��֮��MMAģ����޷�֪����PS�����Ʒ�������ΪPS����Ч���µġ� */
    /* Modified by s00261364 for V3R360_eCall��Ŀ, 2014-4-29, end */
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    /*mmc�յ�COMBINED TAU REJ(#7),�ϱ�ע��״̬�ͷ���״̬,*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);

    /* �ж��Ƿ���Ҫdisable L */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* ��¼����disable LTE��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }

    /* �����L��ģ����ԭ��ֵ7����Ҫanycell����,��ģ�����Ҫ���� */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }
    else
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause8GprsAndNonGprsNotAllow
 ��������  : ����ע��Combined attach not accepted by the network����
             Combined TAU not accepted by the network��Eps Cause8�Ĵ���
 �������  : ��
 �������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
             penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause8GprsAndNonGprsNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_ProcCombinedEpsRegFailCause3IllegalMs(penPsRegAdditionalAction, penCsRegAdditionalAction);
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause9MsidCannotDerivedByNw
 ��������  : ����ע��Eps Cause9�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2015��11��19��
    ��    ��   : c00318887
    �޸�����   : DTS2015111701196,imsûע��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause9MsidCannotDerivedByNw(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause10ImplicitlyDetached
 ��������  : ����ע��Eps Cause10�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2015��11��19��
    ��    ��   : c00318887
    �޸�����   : DTS2015111701196,imsûע��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause10ImplicitlyDetached(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }
}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause11PlmnNotAllow
��������  : ����ע��Combined attach not accepted by the network����
            Combined TAU not accepted by the network��Eps Cause11�Ĵ���
�������  : ��
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2011��12��17��
  ��    ��   : w00176964
  �޸�����   : V7R1 PhaseIV ����:ע��ԭ��ֵ�Ĵ���
3.��    ��   : 2012��03��15��
  ��    ��   : l00130025
  �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
4.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
5.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
6.��    ��   : 2015��4��19��
  ��    ��   : z00161729
  �޸�����   : 24301 R11 CR������Ŀ�޸�
6.��    ��   : 2015��7��1��
  ��    ��   : c00318887
  �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause11PlmnNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId = VOS_NULL_PTR;

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* ��ӽ�ֹ������Ϣ,�и���ʱ����Usim�����ļ� */
    if (VOS_TRUE == NAS_MMC_IsNeedAddForbPlmn_TauRsltFailCause11PlmnNotAllow())
    {
        if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
        {
            NAS_MMC_SndUsimUpdateForbPlmnReq();
        }
    }

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause12TaNotAllow
��������  : ����ע��Combined attach not accepted by the network����
            Combined TAU not accepted by the network��Eps Cause12�Ĵ���
�������  : ��
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2011��12��17��
  ��    ��   : w00176964
  �޸�����   : V7R1 PhaseIV ����:ע��ԭ��ֵ�Ĵ���
3.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
4.��    ��   : 2013��05��08��
  ��    ��   : s46746
  �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
5.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
6.��    ��   : 2015��02��11��
  ��    ��   : l00305157
  �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 mmc�յ�COMBINED TAU REJ(#12),�ϱ�ע��״̬�ͷ���״̬
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause12TaNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /*mmc�յ�COMBINED TAU REJ(#12),�ϱ�ע��״̬�ͷ���״̬*/
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS,NAS_MMC_LIMITED_SERVICE_REGION);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }
}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause406ForbiddenPlmnForGprs
��������  : ����ע��Combined attach not accepted by the network����
            Combined TAU not accepted by the network��Eps Cause14�Ĵ���
�������  : ��
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2012��1��4��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���
                DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                ԭ��ֵ����δ��������ʵ��������������£�����Ҫ���п�ѡ��������
                �����ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON��
2.��    ��   : 2012��11��15��
  ��    ��   : w00176964
  �޸�����   : DTS2012111404729:causeΪ14��Ӧ�ø��·���״̬Ϊ����������Ʒ���,Ӧ�ø���Ϊ���Ʒ���
3.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
4.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
5.��    ��   : 2015��7��1��
  ��    ��   : c00318887
  �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause406ForbiddenPlmnForGprs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* ��ǰ��ONPLMN����PLMN LIST״̬������δ��������ʵ��������������£�
       ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ��MMC�����µ�ǰADDITIONAL ACTION��ֵ */
    enFsmId = NAS_MMC_GetCurrFsmId();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

        if (NAS_MMC_FSM_L1_MAIN == enFsmId)
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);
        }

        return ;
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    /* ��ǰ������ONPLMN����PLMN LIST״̬�����账��ܾ�ԭ��ֵ�����ؿ�ѡ���������� */
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause13RoamNotAllow
��������  : ����ע��Combined attach not accepted by the network����
            Combined TAU not accepted by the network��Eps Cause12�Ĵ���
�������  : ��
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2011��12��17��
  ��    ��   : w00176964
  �޸�����   : V7R1 PhaseIV ����:ע��ԭ��ֵ�Ĵ���
3.��    ��   : 2012��03��15��
  ��    ��   : l00130025
  �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
4.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
5.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
6.��    ��   : 2015��7��1��
  ��    ��   : c00318887
  �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause13RoamNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }
}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause14GprsNotAllowInThisPlmn
��������  : ����ע��Combined attach not accepted by the network����
            Combined TAU not accepted by the network��Eps Cause14�Ĵ���
�������  : ��
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��

���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2011��12��17��
  ��    ��   : w00176964
  �޸�����   : V7R1 PhaseIV ����:ע��ԭ��ֵ�Ĵ���
3.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
4.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ��s
5.��    ��   : 2015��1��5��
  ��    ��   : h00285180
  �޸�����   : LTE #14�ܾ��Ż�:DTS2015010401946
6.��    ��   : 2015��4��19��
  ��    ��   : z00161729
  �޸�����   : 24301 R11 CR������Ŀ�޸�
7.��    ��   : 2015��7��1��
  ��    ��   : c00318887
  �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
8.��    ��   : 2015��8��13��
  ��    ��   : l00289540
  �޸�����   : User_Exp_Improve

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause14GprsNotAllowInThisPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    VOS_UINT8                           ucAllowPsRegWhenEpsRejByCause14;

    ucAllowPsRegWhenEpsRejByCause14     = NAS_MML_GetEpsRejByCause14InVplmnAllowPsRegFlg();

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));
    /* ��ӽ�ֹGPRS PLMN ��Ϣ */
    if (VOS_TRUE == NAS_MMC_IsNeedAddForbGprsPlmn_TauRsltFailCause14GprsNotAllowInThisPlmn())
    {
        if ((VOS_TRUE   == NAS_MMC_IsRoam())
         && (VOS_TRUE   == ucAllowPsRegWhenEpsRejByCause14))
        {
            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                NAS_MML_MAX_TIME_SLICE,
                MMC_LMM_DISABLE_LTE_REASON_BUTT);
        }
        else
        {
            NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());
        }
    }

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /* 24301_CR1422R1_(Rel-11)_C1-121612 ��Ӧ24301 5.5.3.3.5��5.5.1.3.5�½�:
       A UE operating in CS/PS mode 1 of operation and supporting A/Gb or Iu mode
    may perform a PLMN selection according to 3GPP TS 23.122 [6].
       A UE operating in CS/PS mode 1 of operation and supporting S1 mode only,
    or operating in CS/PS mode 2 of operation shall delete the list of
    equivalent PLMNs and shall perform a PLMN selection according to 3GPP TS 23.122 [6].
    ��CR��Э��汾���� */
    if (VOS_TRUE == NAS_MMC_IsNeedDeleteEplmn_CombinedRegRsltFailCause14GprsNotAllowInThisPlmn())
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();
    }

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_LteRejCause14())
    {
        /* ��ҪDisable Lȫ�ֱ��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetLteRejCause14EnableLteTimerLen());

        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        return;
    }

    /* 24301_CR1499R3_(Rel-11)_C1-123437/ 24301_CR1520R1_(Rel-11)_C1-123939(rev
       of C1-123532)_24.301_Avoid to reselect E-UTRAN for #14/C1-141971�ܾ�ԭ��
       ֵ14ʱDISABLE LTE�Ĵ������,��Ӧ24301 5.5.1.3.5��5.5.3.2.5�½�����:
       #14: UE operating in CS/PS mode 1 of operation and supporting A/Gb mode or
            Iu mode may select GERAN or UTRAN radio access technology and proceed
            with the appropriate MM specific procedure according to the MM service state.
            In this case, the UE shall disable the E-UTRA capability (see subclause 4.5)
       ��CR��Э��汾���� */
    if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedAttRsltFailCause14GprsNotAllowInThisPlmn() )
    {
        /* ��ҪDisable Lȫ�ֱ��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

        PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
        stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                          NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                          MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);
        }

        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        return;
    }

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause15NoSuitableCell
��������  : ����ע��Combined attach not accepted by the network����
            Combined TAU not accepted by the network��Eps Cause15�Ĵ���
�������  : ��
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��

���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���

2.��    ��   : 2011��12��17��
  ��    ��   : w00176964
  �޸�����   : V7R1 PhaseIV ����:ע��ԭ��ֵ�Ĵ���
3.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
4.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
5.��    ��   : 2015��7��1��
  ��    ��   : c00318887
  �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause15NoSuitableCell(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
     /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
     NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
     NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
     NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;


    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause19EsmFailure
 ��������  : ����EPSע�ᱻ��ԭ��: NAS_EMM_CAUSE_ESM_FAILURE�Ĵ���
 �������  : ��
 �������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
              penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��6��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2012��06��07��
    ��    ��   : s00217060
    �޸�����   : #401�����Դ����ﵽ5�Σ���ҪDisable L
  5.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  6.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  7.��    ��   : 2013��6��3��
    ��    ��   : z00161729
    �޸�����   : SVLTE �޸�
  8.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
  9.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
  10.��    ��   : 2015��1��15��
     ��    ��   : z00161729
     �޸�����   : AT&T ֧��DAM�����޸�
  11.��    ��   : 2015��4��22��
     ��    ��   : z00161729
     �޸�����   : 24301 R11 CR������Ŀ�޸�
  11.��    ��   : 2015��7��1��
     ��    ��   : c00318887
     �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause19EsmFailure(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    VOS_UINT32                          ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ȡ��Attempt Counter��ֵ */
    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* cs ps���ע��ʧ��,��ǰ������ONPLMN����PLMN LIST״̬���������AttemptCounter
       �����ز�ͬ��ADDITIONAL ACTIONֵ */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* ����EPSע��ʧ��Attemptδ�ﵽ�������Ĵ���Ĵ��� */
        NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes(penPsRegAdditionalAction,
                                                                    penCsRegAdditionalAction);
    }
    else
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* ���·���״̬ */

        /* ֪ͨTAF��ǰ�ķ���״̬ */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegRsltFailMaxTimes() )
        {
            /* ��ҪDisable Lȫ�ֱ��� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, begin */
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, end */

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }

            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause35RequestedServiceOptionNotAuthorizedInThisPlmn
 ��������  : ����ע��Eps Cause35�Ĵ���
 �������  : VOS_VOID
 �������  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��6��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��24��
    ��    ��   : w00242748
    �޸�����   : DTS2013101106863:L�±���ԭ��ֵ#35��ֻ����R10����Э�����ϴ������#11
                 ԭ��ֵ������ͬ��������OTHER CAUSE������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause35ReqServOptNotAuthorizedInThisPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MML_MS_3GPP_REL_STRU                               *pstMs3GppRel = VOS_NULL_PTR;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    if ( NAS_MML_3GPP_REL_R9 >= pstMs3GppRel->enLteNasRelease )
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause(penPsRegAdditionalAction, penCsRegAdditionalAction);
    }
    else
    {
        NAS_MMC_ProcCombinedEpsRegFailCause11PlmnNotAllow(penPsRegAdditionalAction, penCsRegAdditionalAction);
    }

    return;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable
��������  : ����ע��Combined attach successful for EPS services only����
            Combined TAU successful for EPS services only��Eps Cause16�Ĵ���
�������  : ��
�������  : ��
�� �� ֵ  : �յ�ע������Э��Ҫ���cs���additional��������
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2012��5��24��
  ��    ��   : w00166186
  �޸�����   : DTS2012052203028,L�³����������������������ע��5�κ󣬵ȴ�ע������ʱ����ʱ��λ
3.��    ��   : 2012��06��02��
  ��    ��   : s00217060
  �޸�����   : CS/PS mode 1ʱ��Disable Lģ, ����ֵΪNAS_MMC_ADDITIONAL_PLMN_SELECTION
4.��    ��   : 2012��7��27��
  ��    ��   : s00217060
  �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
5.��    ��   : 2013��05��08��
  ��    ��   : s46746
  �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
6.��    ��   : 2013��6��3��
  ��    ��   : z00161729
  �޸�����   : SVLTE �޸�
7.��    ��   : 2013��12��10��
  ��    ��   : w00176964
  �޸�����   : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
8.��    ��   : 2014��3��29��
  ��    ��   : z00161729
  �޸�����   : DTS2014032200128:g��cs only cs���ϱ��ķ���״̬Ϊ���Ʒ���ע��״̬�ϱ�Ϊפ��home���磬���½�����ʾ������������ʧ��

9.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
10.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                ����EMM��COMBINED TAU/ATTACH(eps only,  cause!=#2/#18)�ɹ����ϱ�CS/PSע��״̬�ͷ���״̬
 11.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable(VOS_VOID)
 {
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;


    /* ȡ�õ�ǰ��ע��������  */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /*����EMM��COMBINED TAU/ATTACH(eps only,  cause!=#2/#18)�ɹ����ϱ�CS/PSע��״̬�ͷ���״̬*/
    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
    NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable: Update Reg state and Service state");
    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */


    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, begin */
    /*
    1)  attemptCount < MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
    2)  attemptCount >= MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION
    */

    /* ps��ע��ɹ���cs��ע��ʧ�� */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {

        /* ��GU����һ��,ͨ���жϷ���״̬�������Ƿ����ע��״̬�ͷ���״̬��*/
        if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrCsService())
        {
             /* ����ע��״̬Ϊ0 */
             NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
             NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
        }

        return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }
    else
    {
        /* ���·���״̬ */

        /* ֪ͨTAF��ǰ�ķ���״̬ */
        /*����EMM��COMBINED TAU(eps only,  cause!=#2/#18)�ɹ�,�Ҵﵽ���������ϱ�CS/PSע��״̬�ͷ���״̬*/
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

        return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, end */


}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause17NetworkFailure
��������  : ����ע��Combined attach successful for EPS services only����
            Combined TAU successful for EPS services only��Eps Cause17�Ĵ���
�������  : ��
�������  : ��
�� �� ֵ  : �յ�ע������Э��Ҫ���cs���additional��������
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
��    ��   : z00161729
�޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause17NetworkFailure(VOS_VOID)
{
    return NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable();
}


/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause22Congestion
��������  : ����ע��Combined attach successful for EPS services only����
            Combined TAU successful for EPS services only��Eps Cause22�Ĵ���
�������  : ��
�������  : ��
�� �� ֵ  : �յ�ע������Э��Ҫ���cs���additional��������
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause22Congestion(VOS_VOID)
{
    return NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause16MscNotReachable();
}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause18CsDomainNotAvailable
��������  : ����ע��Combined attach successful for EPS services only����
            Combined TAU successful for EPS services only��Eps Cause18�Ĵ���
�������  : ��
�������  : ��
�� �� ֵ  : �յ�ע������Э��Ҫ���cs���additional��������
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2012��06��07��
  ��    ��   : s00217060
  �޸�����   : CS/PS mode 1ʱ��Disable Lģ, ����ֵΪNAS_MMC_ADDITIONAL_PLMN_SELECTION
3.��    ��   : 2012��7��27��
  ��    ��   : s00217060
  �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
4.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
5.��    ��   : 2013��05��08��
  ��    ��   : s46746
  �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
6.��    ��   : 2013��12��10��
  ��    ��   : w00176964
  �޸�����   : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
7.��    ��   : 2015��02��11��
  ��    ��   : l00305157
  �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
               ����EMM��COMBINED TAU/ATTACH(eps only,  cause=#18)�ɹ����ϱ�CS/PSע��״̬�ͷ���״̬
  8.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause18CsDomainNotAvailable(VOS_VOID)
{
    /* ɾ��LTE�ϱ�����״̬��ע��״̬�Ľӿ�*/

    /* ֪ͨTAF��ǰ�ķ���״̬ */


    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, begin */
    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    /* ɾ��LTE�ϱ�����״̬��ע��״̬�Ľӿ�*/


    /*����EMM��COMBINED TAU/ATTACH(eps only,  cause=#18)�ɹ����ϱ�CS/PSע��״̬�ͷ���״̬*/
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
    NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause18CsDomainNotAvailable: Update Reg state and Service state");
    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, end */

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause2ImsiUnknownInHss
 ��������  : ����ע��Combined attach successful for EPS services only����
             Combined TAU successful for EPS services only��Eps Cause2�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : �յ�ע������Э��Ҫ���cs���additional��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  5.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
  6.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 ����EMM��COMBINED TAU/ATTACH(eps only,  cause=#2)�ɹ����ϱ�CS/PSע��״̬�ͷ���״̬
  7.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause2ImsiUnknownInHss(VOS_VOID)
{

    /* ɾ��LTE�ϱ�����״̬��ע��״̬�Ľӿ�*/


    /* ����cs��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);

    /* ɾ��LTE�ϱ�����״̬��ע��״̬�Ľӿ�*/

    /*����EMM��COMBINED TAU/ATTACH(eps only,  cause=#2)�ɹ����ϱ�CS/PSע��״̬�ͷ���״̬*/
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
    NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCause2ImsiUnknownInHss: Update Reg state and Service state");
    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

    return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause257AccessBarrd
��������  : Eps Cause access bar�Ĵ���
�������  : VOS_VOID
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2011��12��17��
  ��    ��   : w00176964
  �޸�����   : V7R1 PhaseIV ����:ע��ԭ��ֵ�Ĵ���
3.��    ��   : 2012��1��4��
  ��    ��   : w00167002
  �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                ���жϷŵ������Ӻ��������жϡ�
4.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
5.��    ��   : 2013��05��08��
  ��    ��   : s46746
  �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
6.��    ��   : 2013��10��15��
  ��    ��   : s00190137
  �޸�����   : ���Կ��ش��ҷ�HPLMN/RPLMN�����ֹʱ��Ҫ����PLMN����
7.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���

8.��    ��   : 2015��1��23��
  ��    ��   : w00167002
  �޸�����   : DTS2015020309124:via����L������ע��ʱ��L��ACCESS BAR������
                ѡ��������L�Լ�������ע�ᡣVIA�޷���ϣ�MODEM��������޸ġ�
                �޸�Ϊ��ע��״̬�յ�ACCESS BAR�󣬼����ȴ�L��ע������
9.��    ��   : 2015��02��11��
  ��    ��   : l00305157
  �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
               MMC�յ�LMM ATTACH����У�Я��ACCESS BAR������
                       ����״̬:CS���ϱ�NAS_MMC_NO_SERVICE��PS���ϱ�NAS_MMC_LIMITED_SERVICE, CS���PS��ע��״̬�ϱ�0��
               MMC�յ�LMM TAU����У�Я��ACCESS BAR������
                       CS���PS�����״̬,CS���PS��ע��״̬���ı�
 10.��    ��   : 2015��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2015112405788:�ں������,�����ǰ����CS/PS���޷������ϱ���
                MMA����MMA��Ҫ����CS/PS�ķ���״̬���Ÿ�stk�·�LOCATION STATUS NTF
                ��Ϣ�����ղ�������Ϣ���򲻽���IMSI�л���
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause257AccessBarrd(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;

    /* ��ȡ��ǰ��ע������Ϣ���� */
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    enFsmId         = NAS_MMC_GetCurrFsmId();

    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }


     /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /* ���·���״̬ */


    if (LMM_MMC_ATTACH_IND  == pstRegRsltCtx->enRegRsltType)
    {
        /*MMC�յ�LMM ATTACH����У�Я��ACCESS BAR������
        ����״̬:CS���ϱ�NAS_MMC_NO_SERVICE��PS���ϱ�NAS_MMC_LIMITED_SERVICE, CS���PS��ע��״̬�ϱ�0*/
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS,NAS_MMC_LIMITED_SERVICE);

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
    }
    else
    {
    }



    /*���Կ��ش��ҷ�HPLMN/RPLMN�����ֹʱ��Ҫ����PLMN����*/

    if (VOS_TRUE == NAS_MMC_IsAccBarPlmnSearch())
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }

        return;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    /* ��ǰCL������ʱ���ACCEESBARRED,������ȴ�ע���������������BAR,L����ע�ᣬVIA�޷���� */
    if ( (NAS_MMC_REG_CONTROL_BY_3GPP2_CBP  == NAS_MMC_GetRegCtrl())
      && (NAS_MMC_FSM_PLMN_SELECTION        == enFsmId) )
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

        return;
    }

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;

    return;


}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCauseAuthRej
��������  : Eps Cause auth rej�Ĵ���
�������  : VOS_VOID
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2011��12��17��
  ��    ��   : w00176964
  �޸�����   : V7R1 PhaseIV ����:ע��ԭ��ֵ�Ĵ���
3.��    ��   : 2012��03��15��
  ��    ��   : l00130025
  �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
4.��    ��   : 2012��09��15��
  ��    ��   : z00161729
  �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
5.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
6.��    ��   : 2013��05��08��
  ��    ��   : s46746
  �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
7.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
8.��    ��   : 2015��02��11��
  ��    ��   : l00305157
  �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
               ��COMBINEDTAU�����У�mmc�յ���Ȩ�ܾ�,�ϱ�ע��״̬�ͷ���״̬
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause256AuthRej(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* ����cs ps��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);

    /*��COMBINEDTAU�����У�mmc�յ���Ȩ�ܾ�,�ϱ�ע��״̬�ͷ���״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);


    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCause301TimerTimeOut
 ��������  : ps Cause:NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT �Ĵ���
 �������  :
             VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��18��
   ��    ��   : w00167002
   �޸�����   : �����ɺ�����
 2.��    ��   : 2012��03��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
 3.��    ��   : 2012��06��07��
   ��    ��   : s00217060
   �޸�����   : #301�����Դ����ﵽ5�Σ���ҪDisable L
 4.��    ��   : 2012��7��27��
   ��    ��   : s00217060
   �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
 5.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 6.��    ��   : 2013��6��3��
   ��    ��   : z00161729
   �޸�����   : SVLTE �޸�
 7.��    ��   : 2014��5��5��
   ��    ��   : w00242748
   �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                ע��״̬���ϱ���
 8.��    ��   : 2015��1��15��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
 9.��    ��   : 2015��4��22��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
 9.��    ��   : 2015��7��1��
   ��    ��   : c00318887
   �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause301TimerTimeOut(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    VOS_UINT32                          ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    /* ȡ�õ�ǰ��ע������Ϣ���� */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType );

    /* cs ps���ע��ʧ��,��ǰ������ONPLMN����PLMN LIST״̬���������AttemptCounter
       �����ز�ͬ��ADDITIONAL ACTIONֵ */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* EPS����ע��ʧ��Attempt Counterδ�ﵽ���ʧ�ܴ����Ĵ��� */
        NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes(penPsRegAdditionalAction,
                                                                    penCsRegAdditionalAction);
    }
    else
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* ���·���״̬ */

        /* ֪ͨTAF��ǰ�ķ���״̬ */

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegRsltFailMaxTimes() )
        {
            /* ��ҪDisable Lȫ�ֱ��� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, begin */
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, end */

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

            }

            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }
    return;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause403ForbiddenPlmn
��������  : Eps Cause forbidden plmn�Ĵ���
�������  : VOS_VOID
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��10��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���

2.��    ��   : 2011��12��17��
  ��    ��   : w00176964
  �޸�����   : V7R1 PhaseIV ����:ע��ԭ��ֵ�Ĵ���

3.��    ��   : 2012��1��4��
  ��    ��   : w00167002
  �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                ���жϷŵ������Ӻ��������жϡ�
4.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
5.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
6.��    ��   : 2015��7��1��
  ��    ��   : c00318887
  �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause403ForbiddenPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);

    /* ��ǰ��ONPLMN����PLMN LIST״̬�����򷵻ص�ΪNAS_MMC_ADDITIONAL_ACTION_BUTT */
    enFsmId = NAS_MMC_GetCurrFsmId();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

        if (NAS_MMC_FSM_L1_MAIN == enFsmId)
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);
        }

        return ;
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    /* ��ǰ������ONPLMN����PLMN LIST״̬��������������� */
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause404ForbiddenTaForRegPrvsSvs
��������  : ����ע��Combined attach not accepted by the network����
            Combined TAU not accepted by the network��Eps MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS �Ĵ���
�������  : ��
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :

1.��    ��   : 2012��2��4��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause404ForbiddenTaForRegPrvsSvs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* ������ע��ʧ��ԭ��ֵ#12�Ĵ���һ�� */
    NAS_MMC_ProcCombinedEpsRegFailCause12TaNotAllow(penPsRegAdditionalAction,
                                                    penCsRegAdditionalAction);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause405ForbiddenLaForRoam
 ��������  : ������:Ps 13��15��ԭ��ֵ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION :�ܾ�ԭ��ֵ#13����������
             NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN:�ܾ�ԭ��ֵ#15����������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
                 DTS2011102200381:L��ע�ᱻ��#12,LMM��MMC����TAU
                 �еĽ��ΪMMC_LMM_TAU_RSLT_FORBID_PLMNS��MMC�յ��˽�����ս�ֹ����
                 �������������������
                 MMC���ֵ�ǰ��#13����#15�������в�ͬ������������
 2.��    ��   : 2012��1��4��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                  ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                  ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                  ���жϷŵ������Ӻ��������жϡ�
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 4.��    ��   : 2014��5��5��
   ��    ��   : w00242748
   �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                ע��״̬���ϱ���
 5.��    ��   : 2015��7��1��
   ��    ��   : c00318887
   �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause405ForbiddenLaForRoam(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;                              /* �洢ע����CS�򱻾���Ϣ */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;                              /* �洢ע����PS�򱻾���Ϣ */

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);

    /* ��ǰ��ONPLMN����PLMN LIST״̬������δ��������ʵ��������������£�
       ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ��MMC�����µ�ǰADDITIONAL ACTION��ֵ */
    enFsmId = NAS_MMC_GetCurrFsmId();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

        if (NAS_MMC_FSM_L1_MAIN == enFsmId)
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);
        }

        return ;
    }

    /* ��ǰ������ONPLMN����PLMN LIST״̬�����账��ܾ�ԭ��ֵ�����ز�ͬ���������� */

    /* ԭ��ֵ��ʼ��Ϊ#13,�������쳣������#13���г�������� */
    enCsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    /* ��CS�����PS����һ�����ԭ��ֵΪ#13,����г�������� */
    if ( (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enPsCause))
    {
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        return ;
    }

    /* �����վܾ�ԭ��ֵ#15���������Խ������� */
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;

    return;
}
/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCausePsAttachNotAllow
��������  : Eps Cause ps attach not allow�Ĵ���
�������  : VOS_VOID
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��12��25��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
3.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
4.��    ��   : 2015��7��1��
  ��    ��   : c00318887
  �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCausePsAttachNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }
}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause40NoEpsBearerActived
��������  : Eps Cause 40�Ĵ���
�������  : VOS_VOID
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��1��8��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2012��03��15��
  ��    ��   : l00130025
  �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2015��11��19��
    ��    ��   : c00318887
    �޸�����   : DTS2015111701196,imsûע��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause40NoEpsBearerActived(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCauseEpsBearerEstFail
��������  : Eps Cause ESM���ؽ���ʧ�ܵĴ���
�������  : VOS_VOID
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��1��8��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
3.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
4.��    ��   : 2015��7��1��
  ��    ��   : c00318887
  �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseEpsBearerEstFail(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCauseMoDetach
��������  : Eps Cause Mo detach�Ĵ���
�������  : VOS_VOID
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��1��8��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2012��06��27��
  ��    ��   : s46746
  �޸�����   : For CS/PS mode 1������ע��������û�����Detach����
3.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
4.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
5.��    ��   : 2014��07��26��
  ��    ��   : s00217060
  �޸�����   : DTS2014051501744:TAU�������û�detach,LMM���MMC��MO_DETACH_FAILURE,
               MMC�յ���TAU����ᴥ������������ǰҪ�������ͷ����ӣ�����detach_req������ȥ
6.��    ��   : 2015��7��1��
  ��    ��   : c00318887
  �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseMoDetach(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

    /* attach/tau�������û�detach,LMM���MMC��MO_DETACH_FAILURE,
       MMC�յ���attach/tau����ᴥ������������ǰҪ�������ͷ����ӣ�����detach_req������ȥ
       ���Դ˴��޸�Ϊ����פ�� */
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;


    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCauseMtDetach
��������  : Eps Cause Mt detach�Ĵ���
�������  : VOS_VOID
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��1��8��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
3.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
4.��    ��   : 2015��7��1��
  ��    ��   : c00318887
  �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseMtDetach(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause42SevereNetworkFailure
 ��������  : ����ע��Eps Cause #42�Ĵ���
 �������  : VOS_VOID
 �������  : penPsRegAdditionalAction - ps��additional action
             penCsRegAdditionalAction - cs��additional action
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��19��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause42SevereNetworkFailure(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MML_3GPP_REL_ENUM_UINT8        enLteRelVersion;
    NAS_MML_PLMN_WITH_RAT_STRU         stPlmnWithRat;

    enLteRelVersion = NAS_MML_GetLte3gppRelVersion();
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* Э��汾С��R11��other cause���� */
    if ( NAS_MML_3GPP_REL_R11 > enLteRelVersion)
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause(penPsRegAdditionalAction, penCsRegAdditionalAction);
        return;
    }

    /* 24301_CR1473R2_(Rel-11)_C1-123386 MMC����ATTACH��TAU��SERVICE REQUEST�����б���ԭ��ֵ42�Ĵ���
    24301 5.5.1.3.5��5.5.3.3.5�½�����:
       The UE shall set the EPS update status to EU2 NOT UPDATED, and shall delete
    any GUTI, last visited registered TAI, eKSI, and list of equivalent PLMNs,
    and set the attach attempt counter to 5. The UE shall start an implementation
    specific timer, setting its value to 2 times the value of T as defined in 3GPP
    TS 23.122 [6]. While this timer is running, the UE shall not consider the
    PLMN + RAT combination that provided this reject cause, a candidate for PLMN
    selection. The UE then enters state EMM-DEREGISTERED.PLMN-SEARCH in order to
    perform a PLMN selection according to 3GPP TS 23.122 [6].
        If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
    set the GMM state to GMM-DEREGISTERED, GPRS update status to GU2 NOT UPDATED,
    and shall delete the P-TMSI, P-TMSI signature, RAI and GPRS ciphering key
    sequence number. ��CR��Э��汾���� */
    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

    /* ������#42����������ֹ���뼼�������б��У���ֹʱ��Ϊ2*T,�������� */
    NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                  NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice(),
                                                  MMC_LMM_DISABLE_LTE_REASON_BUTT);

    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCauseT3402Running
��������  : Eps Cause T3402��ʱ�������еĴ���
�������  : VOS_VOID
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��1��8��
  ��    ��   : z00161729
  �޸�����   : �����ɺ���
2.��    ��   : 2013��1��31��
  ��    ��   : t00212959
  �޸�����   : DTS2013012909238:anycell������3402�����У�����available��ʱ�����ַ�����������
3.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
4.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
5.��    ��   : 2015��7��1��
  ��    ��   : c00318887
  �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseT3402Running(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;

    enFsmId                = NAS_MMC_GetCurrFsmId();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);


    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    /* ��ǰ��ONPLMNʱ��AVAILABLE��ʱ��δ����,��MMC��Ҫ��������*/
    if ( NAS_MMC_FSM_L1_MAIN   == enFsmId)
    {
        if (NAS_MMC_TIMER_STATUS_RUNING == enAvailableTimerStatus)
        {
            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);

            return;
        }

        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    return;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc
��������  : Eps Cause T3402��ʱ����������PS normal service�Ĵ���
�������  : enRegRsltType - ��ǰ��ע������Ϣ����
            pstLmmTauIndMsg - LMM_MMC_TAU_RESULT_IND��Ϣָ��
�������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
            penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : c00318887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
    NAS_MMC_SetLteUnrealRegProcFlg(VOS_TRUE);
    NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc: Update Reg state and Service state");
    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause3IllegalMs
 ��������  : Eps Cause3�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����
  3.��    ��   : 2011��12��30��
    ��    ��   : l65478
    �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                 ���ݾ����ԭ��ֵ������

  4.��    ��   : 2012��2��15��
    ��    ��   : z40661
    �޸�����   : DTS2011121405203_PC���Է�������,֧��gUL��ģʱ,L�±�#3�ܾ�,��GU��ָ������
  5.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  6.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����  : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  7.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  8.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  9.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
 10.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
 11.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause3IllegalMs(VOS_VOID)
{

    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* �ȸ���ȫ�ֱ���,���ڷ�����Ϣʱȫ�ֱ���ʱ���µ� */
    /* ����cs ps��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);

    /*����PS��ע��״̬�����ϱ�����״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }


    /* modified by z40661 for DTS2011121405203_PC���Է�������, 2012-02-15, begin */
    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

    /* modified by l65478 for DTS2011121405203_PC���Է�������, 2012-02-15, end */

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause6IllegalMe
 ��������  : Eps Cause6�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause6IllegalMe(VOS_VOID)
{

    return NAS_MMC_ProcEpsAttachRegFailCause3IllegalMs();

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause7EpsServNotAllow
 ��������  : Eps Cause7�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����

  3.��    ��   : 2011��12��30��
    ��    ��   : l65478
    �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                 ���ݾ����ԭ��ֵ������
  4.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��

  5.��    ��   : 2012��4��4��
    ��    ��   : z40661
    �޸�����   : ���ⵥ��DTS2012032803448��PS oNLYʱ����Ҫ��Lģ�½���ANYCELL
                 ������
  6.��    ��   : 2012��7��4��
    ��    ��   : s46746
    �޸�����   : for V7R1 cS/PS mode 1, ԭ��ֵ#7ʱ����Ҫ����Disable LTEȫ�ֱ���
  7.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  8.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  9.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 10.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
 11.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
 12.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause7EpsServNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    pstRatOrder     = NAS_MML_GetMsPrioRatList();


    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* ����ps��״̬Ϊ��Ч */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);


    /*MMC���յ�LMMģ��ע����(EPS ONLY)��casue=#7, ����PS��ע��״̬�����ϱ�����״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);


    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    /* �ж��Ƿ���Ҫdisable L */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* ��¼����disable LTE��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    /* �����L��ģ����ԭ��ֵ7����Ҫanycell����,��ģ�����Ҫ���� */
    /* Lģ��PS ONLYʱҲ��Ҫ����anycell���� */
    enMsMode    =    NAS_MML_GetMsMode();
    if ( (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
      || (NAS_MML_MS_MODE_PS_ONLY == enMsMode))
    {
        return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }
    else
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause8GprsAndNonGprsNotAllow
 ��������  : Eps Cause8�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID)
{

    return NAS_MMC_ProcEpsAttachRegFailCause3IllegalMs();

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause11PlmnNotAllow
 ��������  : Eps Cause11�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��08��05��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
  5.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause11PlmnNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId;

    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* ��ӽ�ֹ������Ϣ,�и���ʱ����Usim�����ļ� */
    if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause12TaNotAllow
 ��������  : Eps Cause12�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  4.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause12TaNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /*MMC���յ�LMMģ��ע����(EPS ONLY)��casue=#12, ����PS��ע��״̬Ϊ0�����ϱ�����״̬2*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE_REGION);

    /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MMC_LIMITED_SERVICE_REGION */
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE_REGION);

    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause13RoamNotAllow
 ��������  : Eps Cause13�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
  5.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause13RoamNotAllow(VOS_VOID)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause14GprsNotAllowInThisPlmn
 ��������  : EPs Cause14�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
  4.��    ��   : 2015��1��5��
    ��    ��   : h00285180
    �޸�����   : LTE #14�ܾ��Ż�:DTS2015010401946
  5.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
  6.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
  7.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;
    VOS_UINT8                           ucEpsRejBy14AllowPsRegFlg;

    ucEpsRejBy14AllowPsRegFlg = NAS_MML_GetEpsRejByCause14InVplmnAllowPsRegFlg();

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    if ((VOS_TRUE   == NAS_MMC_IsRoam())
     && (VOS_TRUE   == ucEpsRejBy14AllowPsRegFlg))
    {
        PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
        stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

        NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
            NAS_MML_MAX_TIME_SLICE,
            MMC_LMM_DISABLE_LTE_REASON_BUTT);
    }
    else
    {
        /* ��ӽ�ֹGPRS PLMN ��Ϣ */
        NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());
    }
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /* 24301_CR1422R1_(Rel-11)_C1-121612 ��Ӧ24301 5.5.1.2.5�½�:
    #14(EPS services not allowed in this PLMN);
        The UE shall set the EPS update status to EU3 ROAMING NOT ALLOWED
        (and shall store it according to subclause 5.1.3.3) and shall delete any
        GUTI, last visited registered TAI and eKSI. Additionally, the UE shall
        delete the list of equivalent PLMNs and reset the attach attempt counter
        ��CR��Э��汾���� */
    if (NAS_MML_GetLte3gppRelVersion() >= NAS_MML_3GPP_REL_R11)
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();
    }

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_LteRejCause14())
    {
        /* ��ҪDisable Lȫ�ֱ��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetLteRejCause14EnableLteTimerLen());

        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause15NoSuitableCell
 ��������  : Eps Cause15�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause15NoSuitableCell(VOS_VOID)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause35RequestedServiceOptionNotAuthorizedInThisPlmn
 ��������  : Eps Cause35�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��03��06��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��24��
    ��    ��   : w00242748
    �޸�����   : DTS2013101106863:L�±���ԭ��ֵ#35��ֻ����R10����Э�����ϴ������#11
                 ԭ��ֵ������ͬ��������OTHER CAUSE������
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause35ReqServOptNotAuthorizedInThisPlmn(VOS_VOID)
{
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulAttemptCnt;

    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();
    pstMs3GppRel    = NAS_MML_GetMs3GppRel();

    if ( NAS_MML_3GPP_REL_R9 >= pstMs3GppRel->enLteNasRelease )
    {
        /* ȡ��Attempt Counter��ֵ */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(pstRegRsltCtx->enRegRsltType);
        return NAS_MMC_ProcEpsRegFailCauseAbnormalCause(NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN, ulAttemptCnt);
    }
    else
    {
        return NAS_MMC_ProcEpsAttachRegFailCause11PlmnNotAllow();
    }
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause256AuthRej
 ��������  : Eps Reg Auth rej�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  8.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
  9.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause256AuthRej(VOS_VOID)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* ����cs ps��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /*MMC���յ�LMMģ��ע����attach(EPS ONLY)����Ȩ���ܣ�����PS��ע��״̬�����ϱ�����״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause257AccessBarrd
 ��������  : Eps AccessBarrd�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  5.��    ��   : 2013��10��15��
    ��    ��   : s00190137
    �޸�����   : ���Կ��ش��ҷ�HPLMN/RPLMN�����ֹʱ��Ҫ����PLMN����

  6.��    ��   : 2015��1��23��
    ��    ��   : w00167002
    �޸�����   : DTS2015020309124:via����L������ע��ʱ��L��ACCESS BAR������
                ѡ��������L�Լ�������ע�ᡣVIA�޷���ϣ�MODEM��������޸ġ�
                �޸�Ϊ��ע��״̬�յ�ACCESS BAR�󣬼����ȴ�L��ע������
  7.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
               MMC�յ�LMM ATTACH����У�Я��ACCESS BAR������
                       ����״̬:CS���ϱ�NAS_MMC_NO_SERVICE��PS���ϱ�NAS_MMC_LIMITED_SERVICE, CS���PS��ע��״̬�ϱ�0��
               MMC�յ�LMM TAU����У�Я��ACCESS BAR������
                       CS���PS�����״̬,CS���PS��ע��״̬���ı�

  8.��    ��   : 2015��11��24��
    ��    ��   : w00167002
    �޸�����   : DTS2015112405788:�ں������,�����ǰ����CS/PS���޷������ϱ���
                 MMA����MMA��Ҫ����CS/PS�ķ���״̬���Ÿ�stk�·�LOCATION STATUS NTF
                 ��Ϣ�����ղ�������Ϣ���򲻽���IMSI�л���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause257AccessBarrd(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    enFsmId         = NAS_MMC_GetCurrFsmId();

    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS,NAS_MMC_LIMITED_SERVICE);
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);

    /*���Կ��ش��ҷ�HPLMN/RPLMN�����ֹʱ��Ҫ����PLMN����*/
    if (VOS_TRUE == NAS_MMC_IsAccBarPlmnSearch())
    {
        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }

        return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }


    /* ��ǰCL������ʱ���ACCEESBARRED,������ȴ�ע���������������BAR,L����ע�ᣬVIA�޷���� */
    if ( (NAS_MMC_REG_CONTROL_BY_3GPP2_CBP  == NAS_MMC_GetRegCtrl())
      && (NAS_MMC_FSM_PLMN_SELECTION        == enFsmId) )
    {
        return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }

    return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;

}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause301TimerTimeOut
 ��������  : Eps Reg Auth rej�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause301TimerTimeOut(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* ȡ�õ�ǰ��ע������Ϣ���� */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType );

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* AttemptCounterδ�ﵽ�������Ĵ��� */
        NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(&enAction);
    }
    else
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* ���·���״̬ */

        /* ֪ͨTAF��ǰ�ķ���״̬ */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return enAction;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause401OtherCause
 ��������  : Eps Reg Auth rej�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2012��06��07��
   ��    ��   : s00217060
   �޸�����   : For CS/PS mode 1������Attach,other cause,���ҳ���5�Σ�������ҪDisable L
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause401OtherCause(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* ȡ�õ�ǰ��ע������Ϣ���� */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType );

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* AttemptCounterδ�ﵽ�������Ĵ��� */
        NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(&enAction);
    }
    else
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* ���·���״̬ */

        /* ֪ͨTAF��ǰ�ķ���״̬ */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause403ForbiddenPlmn
 ��������  : Eps �ظ���ǰפ���ڽ�ֹ����ĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��12��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                  ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                  ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_BUTT��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause403ForbiddenPlmn(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    enFsmId = NAS_MMC_GetCurrFsmId();

    switch ( enFsmId )
    {
        /* ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ��
            MMC�����µ�ǰADDITIONAL ACTION��ֵ */
        case NAS_MMC_FSM_L1_MAIN :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);

            break;

        case NAS_MMC_FSM_PLMN_LIST :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }
            break;

        /* ������Ҫ�������� */
        default:
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            break;
    }

    return enAdditionalAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause404ForbiddenTaForRegPrvsSvs
 ��������  : Eps����ԭ��ֵ:MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS�ĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause404ForbiddenTaForRegPrvsSvs(VOS_VOID)
{
    /* ���ܾ�ԭ��ֵ#12�Ĵ�����һ�� */
    return NAS_MMC_ProcEpsAttachRegFailCause12TaNotAllow();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause405ForbiddenLaForRoam
 ��������  : ������:Ps 13��15��ԭ��ֵ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION :�ܾ�ԭ��ֵ#13����������
             NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN:�ܾ�ԭ��ֵ#15����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
                 DTS2011102200381:L��ע�ᱻ��#12,LMM��MMC����TAU
                 �еĽ��ΪMMC_LMM_TAU_RSLT_FORBID_PLMNS��MMC�յ��˽�����ս�ֹ����
                 �������������������
                 MMC���ֵ�ǰ��#13����#15�������в�ͬ������������
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause405ForbiddenLaForRoam(VOS_VOID)
{
    /* ��tau״̬�Ĵ���һ�� */
    return NAS_MMC_ProcEpsTauRegFailCause405ForbiddenLaForRoam();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause406ForbiddenPlmnForGprs
 ��������  : EPs Cause14�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                  ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                  ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                  ���жϷŵ������Ӻ��������жϡ�
   3.��    ��   : 2013��3��30��
     ��    ��   : l00167671
     �޸�����   : �����ϱ�AT�������������C��
   4.��    ��   : 2015��7��1��
     ��    ��   : c00318887
     �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause406ForbiddenPlmnForGprs(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    /* ��ӽ�ֹGPRS PLMN ��Ϣ */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    enFsmId = NAS_MMC_GetCurrFsmId();

    switch ( enFsmId )
    {
        /* ��ǰ��ONPLMN,����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalAction
            ֵ��MMC�����µ�ǰADDITIONAL ACTION��ֵ */
        case NAS_MMC_FSM_L1_MAIN :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);

            break;

        case NAS_MMC_FSM_PLMN_LIST :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            break;

        /* ������Ҫ���п�ѡ������ */
        default:
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            break;
    }

    return enAdditionalAction;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCausePsAttachNotAllow
 ��������  : Eps �ظ���ǰPS������ע��ĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��27��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCausePsAttachNotAllow(VOS_VOID)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }


    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCauseEpsBearerEstFail
 ��������  : Eps �ظ�EPS���ؽ���ʧ�ܵĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��08��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseEpsBearerEstFail(VOS_VOID)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }


    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}

 /*****************************************************************************
  �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCauseMoDetach
  ��������  : Eps Mo detach�ĺ�������
  �������  : VOS_VOID
  �������  : ��
  �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
  ���ú���  :
  ��������  :

  �޸���ʷ      :
   1.��    ��   : 2012��1��08��
     ��    ��   : z00161729
     �޸�����   : �����ɺ���
   2.��    ��   : 2013��3��30��
     ��    ��   : l00167671
     �޸�����   : �����ϱ�AT�������������C��
   3.��    ��   : 2014��07��26��
     ��    ��   : s00217060
     �޸�����   : DTS2014051501744:TAU�������û�detach,LMM���MMC��MO_DETACH_FAILURE,
                  MMC�յ���TAU����ᴥ������������ǰҪ�������ͷ����ӣ�����detach_req������ȥ
   4.��    ��   : 2015��7��1��
     ��    ��   : c00318887
     �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
 *****************************************************************************/
 NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseMoDetach(VOS_VOID)
 {
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }


    /* attach�������û�detach,LMM���MMC��MO_DETACH_FAILURE,
       MMC�յ���attach����ᴥ������������ǰҪ�������ͷ����ӣ�����detach_req������ȥ
       ���Դ˴��޸�Ϊ����פ�� */
    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
 }

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCauseMtDetach
 ��������  : Eps Mt detach�ĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��08��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseMtDetach(VOS_VOID)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause42SevereNetworkFailure
 ��������  : eps only attach����#42 severe network failure�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��19��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCause42SevereNetworkFailure(VOS_VOID)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulAttemptCnt;
    NAS_MML_3GPP_REL_ENUM_UINT8         enLteRelVersion;
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    enLteRelVersion = NAS_MML_GetLte3gppRelVersion();
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* Э��汾С��R11��other cause���� */
    if ( NAS_MML_3GPP_REL_R11 > enLteRelVersion )
    {
        /* ȡ��Attempt Counter��ֵ */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(pstRegRsltCtx->enRegRsltType);
        return NAS_MMC_ProcEpsRegFailCauseAbnormalCause(NAS_MML_REG_FAIL_CAUSE_SEVERE_NETWORK_FAILURE, ulAttemptCnt);
    }

    /* 24301_CR1473R2_(Rel-11)_C1-123386 MMC����ATTACH��TAU��SERVICE REQUEST�����б���ԭ��ֵ42�Ĵ���
      24301 5.5.1.2.5�½�����:
      The UE shall set the EPS update status to EU2 NOT UPDATED, and shall delete
    any GUTI, last visited registered TAI, eKSI, and list of equivalent PLMNs,
    and set the attach attempt counter to 5. The UE shall start an implementation
    specific timer setting its value to 2 times the value of T as defined in
    3GPP TS 23.122 [6]. While this timer is running, the UE shall not consider
    the PLMN + RAT combination that provided this reject cause a candidate
    for PLMN selection. The UE then enters state EMM-DEREGISTERED.PLMN-SEARCH
    in order to perform a PLMN selection according to 3GPP TS 23.122 [6].
      If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
    set the GMM state to GMM-DEREGISTERED, GPRS update status to GU2 NOT UPDATED,
    and shall delete the P-TMSI, P-TMSI signature, RAI and GPRS ciphering key
    sequence number. ��CR��Э��汾���� */
    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

    /* ������#42����������ֹ���뼼�������б��У���ֹʱ��Ϊ2*T,�������� */
    NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                   NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice(),
                                                   MMC_LMM_DISABLE_LTE_REASON_BUTT);

    NAS_MMC_DeleteEPlmnList();

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCauseT3402Running
 ��������  : Eps T3402��ʱ���������еĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��08��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��1��31��
    ��    ��   : t00212959
    �޸�����   : DTS2013012909238:anycell������3402�����У�����available��ʱ�����ַ�����������
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFailCauseT3402Running(VOS_VOID)
{

    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;

    enFsmId                = NAS_MMC_GetCurrFsmId();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    /* ��ǰ��ONPLMNʱ��AVAILABLE��ʱ��δ����,��MMC��Ҫ��������*/
    if ( NAS_MMC_FSM_L1_MAIN   == enFsmId)
    {
        if (NAS_MMC_TIMER_STATUS_RUNING == enAvailableTimerStatus)
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }

        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause3IllegalMs
 ��������  : Eps Cause3�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��30��
    ��    ��   : l65478
    �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                 ���ݾ����ԭ��ֵ������

  3.��    ��   : 2012��2��15��
    ��    ��   : z40661
    �޸�����   : DTS2011121405203_PC���Է�������,֧��gUL��ģʱ,L�±�#3�ܾ�,��GU��ָ������
  4.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  5.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  6.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  7.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  8.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  9.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause3IllegalMs(VOS_VOID)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* �ȸ���ȫ�ֱ���,���ڷ�����Ϣʱ��ȡ����ȫ�ֱ��������µ� */
    /* ����cs ps��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    /*����PS��ע��״̬�����ϱ�����״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    /* modified by z40661 for DTS2011121405203_PC���Է�������, 2012-02-15, begin */
    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
    /* modified by z40661 for DTS2011121405203_PC���Է�������, 2012-02-15, begin */

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause6IllegalMe
 ��������  : Eps Cause6�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause6IllegalMe(VOS_VOID)
{
    return NAS_MMC_ProcEpsTauRegFailCause3IllegalMs();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCauseCause7EpsServNotAllow
 ��������  : Eps Cause7�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��30��
    ��    ��   : l65478
    �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                 ���ݾ����ԭ��ֵ������
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��

  4.��    ��   : 2012��4��4��
    ��    ��   : z40661
    �޸�����   : ���ⵥ��DTS2012032803448��PS oNLYʱ����Ҫ��Lģ�½���ANYCELL������

  5.��    ��   : 2012��7��4��
    ��    ��   : s46746
    �޸�����   : for V7R1 cS/PS mode 1, ԭ��ֵ#7ʱ����Ҫ����Disable LTEȫ�ֱ���
  6.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  7.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  8.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  9.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
 10.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause7EpsServNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    pstRatOrder     = NAS_MML_GetMsPrioRatList();

    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* ����ps��״̬Ϊ��Ч */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
    /*MMC���յ�LMMģ��ע����(EPS ONLY)��casue=#7, ����PS��ע��״̬�����ϱ�����״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /* �ж��Ƿ���Ҫdisable L */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* ��¼����disable LTE��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,VOS_FALSE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    enMsMode    =    NAS_MML_GetMsMode();
    if ( (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
      || (NAS_MML_MS_MODE_PS_ONLY == enMsMode))
    {
        return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }
    else
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFailCause8GprsAndNonGprsNotAllow
 ��������  : Eps Cause8�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII �����ɺ���
                ���Ӷ�CASUE 8�Ĵ���
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID)
{
    return NAS_MMC_ProcEpsTauRegFailCause3IllegalMs();
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause9MsIdCannotBeDerivedByNW
 ��������  : Eps Cause9�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��11��19��
    ��    ��   : c00318887
    �޸�����   : DTS2015111701196,imsûע��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause9MsIdCannotBeDerivedByNW(VOS_VOID)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause10EpsImplicitlyDetached
 ��������  : Eps Cause9�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��11��19��
    ��    ��   : c00318887
    �޸�����   : DTS2015111701196,imsûע��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause10EpsImplicitlyDetached(VOS_VOID)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause11PlmnNotAllow
 ��������  : Eps Cause11�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��08��05��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause11PlmnNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId;

    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* ��ӽ�ֹ������Ϣ,�и���ʱ����Usim�����ļ� */
    if (VOS_TRUE == NAS_MMC_IsNeedAddForbPlmn_TauRsltFailCause11PlmnNotAllow())
    {
        if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
        {
            NAS_MMC_SndUsimUpdateForbPlmnReq();
        }
    }

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause12TaNotAllow
 ��������  : Eps Cause12�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  4.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause12TaNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    /* ���·���״̬ */

    /*MMC���յ�LMMģ��ע����(EPS ONLY)��casue=#12, ����PS��ע��״̬Ϊ0�����ϱ�����״̬2*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE_REGION);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MMC_LIMITED_SERVICE_REGION */
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE_REGION);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause13RoamNotAllow
 ��������  : Eps Cause13�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause13RoamNotAllow(VOS_VOID)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause14GprsNotAllowInThisPlmn
 ��������  : EPs Cause14�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2015��1��5��
    ��    ��   : h00285180
    �޸�����   : LTE #14�ܾ��Ż�:DTS2015010401946
  4.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
  5.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    NAS_MML_3GPP_REL_ENUM_UINT8         enLteRelVersion;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;
    VOS_UINT8                           ucEpsRejBy14AllowPsRegFlg;
    ucEpsRejBy14AllowPsRegFlg = NAS_MML_GetEpsRejByCause14InVplmnAllowPsRegFlg();
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    enLteRelVersion = NAS_MML_GetLte3gppRelVersion();

    if (VOS_TRUE == NAS_MMC_IsNeedAddForbGprsPlmn_TauRsltFailCause14GprsNotAllowInThisPlmn())
    {
        if ((VOS_TRUE   == NAS_MMC_IsRoam())
         && (VOS_TRUE   == ucEpsRejBy14AllowPsRegFlg))
        {
            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                NAS_MML_MAX_TIME_SLICE,
                MMC_LMM_DISABLE_LTE_REASON_BUTT);
        }
        else
        {
            /* ��ӽ�ֹGPRS PLMN ��Ϣ */
            NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());
        }
    }

    /* 24301_CR1422R1_(Rel-11)_C1-121612 ��Ӧ24301 5.5.3.2.5�½�:
     #14:
      If the EPS update type is "TA updating", or the EPS update type is
      "periodic updating" and the UE is in PS mode 1 or PS mode 2 of operation,
      the UE shall perform a PLMN selection according to 3GPP TS 23.122 [6]. In
      this case, the UE supporting S1 mode only shall delete the list of equivalent
      PLMNs before performing the procedure. ��CR��Э��汾����  */
    if ((VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
      && (enLteRelVersion >= NAS_MML_3GPP_REL_R11))
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();
    }
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_LteRejCause14())
    {
        /* ��ҪDisable Lȫ�ֱ��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetLteRejCause14EnableLteTimerLen());

        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause15NoSuitableCell
 ��������  : Eps Cause15�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause15NoSuitableCell(VOS_VOID)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause40NoEpsBearerActived
 ��������  : Eps Cause40�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��11��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV BBIT���Ե���
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2015��11��19��
    ��    ��   : c00318887
    �޸�����   : DTS2015111701196,imsûע��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause40NoEpsBearerActived(VOS_VOID)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause42SevereNetworkFailure
 ��������  : Eps tau Cause42�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause42SevereNetworkFailure(VOS_VOID)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulAttemptCnt;
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* Э��汾С��R11��other cause���� */
    if ( NAS_MML_3GPP_REL_R11 > NAS_MML_GetLte3gppRelVersion())
    {
        /* ȡ��Attempt Counter��ֵ */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(pstRegRsltCtx->enRegRsltType);
        return NAS_MMC_ProcEpsRegFailCauseAbnormalCause(NAS_EMM_CAUSE_SERVER_NETWORK_FAILURE, ulAttemptCnt);
    }

    /* 24301_CR1473R2_(Rel-11)_C1-123386 MMC����ATTACH��TAU��SERVICE REQUEST�����б���ԭ��ֵ42�Ĵ���
      24301 5.5.3.2.5�½�����:
       The UE shall set the EPS update status to EU2 NOT UPDATED, and shall delete
    any GUTI, last visited registered TAI, eKSI, and list of equivalent PLMNs,
    and set the attach attempt counter to 5. The UE shall start an implementation
    specific timer setting its value to 2 times the value of T as defined in
    3GPP TS 23.122 [6]. While this timer is running, the UE shall not consider
    the PLMN + RAT combination that provided this reject cause a candidate
    for PLMN selection. The UE then enters state EMM-DEREGISTERED.PLMN-SEARCH
    in order to perform a PLMN selection according to 3GPP TS 23.122 [6].
       If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
    set the GMM state to GMM-DEREGISTERED, GPRS update status to GU2 NOT UPDATED,
    and shall delete the P-TMSI, P-TMSI signature, RAI and GPRS ciphering key
    sequence number. ��CR��Э��汾���� */
    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

    /* ������#42����������ֹ���뼼�������б��У���ֹʱ��Ϊ2*T,�������� */
    NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                   NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice(),
                                                   MMC_LMM_DISABLE_LTE_REASON_BUTT);


    NAS_MMC_DeleteEPlmnList();

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause35RequestedServiceOptionNotAuthorizedInThisPlmn
 ��������  : Eps Cause35�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��6��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��24��
    ��    ��   : w00242748
    �޸�����   : DTS2013101106863:L�±���ԭ��ֵ#35��ֻ����R10����Э�����ϴ������#11
                 ԭ��ֵ������ͬ��������OTHER CAUSE������
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause35ReqServOptNotAuthorizedInThisPlmn(VOS_VOID)
{
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulAttemptCnt;

    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();
    pstMs3GppRel    = NAS_MML_GetMs3GppRel();

    if ( NAS_MML_3GPP_REL_R9 >= pstMs3GppRel->enLteNasRelease )
    {
        /* ȡ��Attempt Counter��ֵ */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(pstRegRsltCtx->enRegRsltType);
        return NAS_MMC_ProcEpsRegFailCauseAbnormalCause(NAS_EMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN, ulAttemptCnt);
    }
    else
    {
        return NAS_MMC_ProcEpsTauRegFailCause11PlmnNotAllow();
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause256AuthRej
 ��������  : Eps Reg Auth rej�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  7.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause256AuthRej(VOS_VOID)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* ����cs ps��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    /*MMC���յ�LMMģ��ע����(EPS ONLY)����Ȩ���ܣ�����PS��ע��״̬�����ϱ�����״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause257AccessBarrd
 ��������  : Eps AccessBarrd�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                  ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                  ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON���ֽ�
                  ���жϷŵ������Ӻ��������жϡ�
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  5.��    ��   : 2013��10��15��
    ��    ��   : s00190137
    �޸�����   : ���Կ��ش��ҷ�HPLMN/RPLMN�����ֹʱ��Ҫ����PLMN����
  6.��    ��   : 2015��1��23��
    ��    ��   : w00167002
    �޸�����   : DTS2015020309124:via����L������ע��ʱ��L��ACCESS BAR������
                ѡ��������L�Լ�������ע�ᡣVIA�޷���ϣ�MODEM��������޸ġ�
                �޸�Ϊ��ע��״̬�յ�ACCESS BAR�󣬼����ȴ�L��ע������
  7.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause257AccessBarrd(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;

    enFsmId         = NAS_MMC_GetCurrFsmId();

    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    }

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    /*���Կ��ش��ҷ�HPLMN/RPLMN�����ֹʱ��Ҫ����PLMN����*/
    if (VOS_TRUE == NAS_MMC_IsAccBarPlmnSearch())
    {
        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }

        return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    /* ��ǰCL������ʱ���ACCEESBARRED,������ȴ�ע���������������BAR,L����ע�ᣬVIA�޷���� */
    if ( (NAS_MMC_REG_CONTROL_BY_3GPP2_CBP  == NAS_MMC_GetRegCtrl())
      && (NAS_MMC_FSM_PLMN_SELECTION        == enFsmId) )
    {
        return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }

    return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause301TimerTimeOut
 ��������  : Eps Reg Timer Out�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause301TimerTimeOut(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* ȡ�õ�ǰ��ע������Ϣ���� */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType );

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* AttemptCounterδ�ﵽ�������Ĵ��� */
        NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(&enAction);
    }
    else
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* ���·���״̬ */

        /* ֪ͨTAF��ǰ�ķ���״̬ */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return enAction;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause401OtherCause
 ��������  : Eps Reg Auth rej�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause401OtherCause(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    VOS_UINT32                                              ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* ȡ�õ�ǰ��ע������Ϣ���� */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType );
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* AttemptCounterδ�ﵽ�������Ĵ��� */
        NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(&enAction);
    }
    else
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* ���·���״̬ */

        /* ֪ͨTAF��ǰ�ķ���״̬ */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return enAction;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause403ForbiddenPlmn
 ��������  : Eps �ظ���ǰפ���ڽ�ֹ����ĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��12��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause403ForbiddenPlmn(VOS_VOID)
{
    return NAS_MMC_ProcEpsAttachRegFailCause403ForbiddenPlmn();
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause404ForbiddenTaForRegPrvsSvs
 ��������  : Eps����ԭ��ֵ:MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS�ĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause404ForbiddenTaForRegPrvsSvs(VOS_VOID)
{
    /* ���ܾ�ԭ��ֵ#12�Ĵ�����һ�� */
    return NAS_MMC_ProcEpsTauRegFailCause12TaNotAllow();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause405ForbiddenLaForRoam
 ��������  : ������:Ps 13��15��ԭ��ֵ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION :�ܾ�ԭ��ֵ#13����������
             NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN:�ܾ�ԭ��ֵ#15����������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��29��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
                 DTS2011102200381:L��ע�ᱻ��#12,LMM��MMC����TAU
                 �еĽ��ΪMMC_LMM_TAU_RSLT_FORBID_PLMNS��MMC�յ��˽�����ս�ֹ����
                 �������������������
                 MMC���ֵ�ǰ��#13����#15�������в�ͬ������������
  2.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                  ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                  ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_BUTT��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause405ForbiddenLaForRoam(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;                              /* �洢ע����CS�򱻾���Ϣ */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;                              /* �洢ע����PS�򱻾���Ϣ */

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    /* ��ǰ��ONPLMN����PLMN LIST״̬�����򷵻ص�ΪNAS_MMC_ADDITIONAL_ACTION_BUTT */
    enFsmId = NAS_MMC_GetCurrFsmId();

    if ( (NAS_MMC_FSM_L1_MAIN   == enFsmId)
      || (NAS_MMC_FSM_PLMN_LIST == enFsmId) )
    {
        if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }

        if (NAS_MMC_FSM_L1_MAIN == enFsmId)
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);
        }

        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    /* ��ǰ������ONPLMN����PLMN LIST״̬�����账��ܾ�ԭ��ֵ�����ز�ͬ���������� */

    /* ԭ��ֵ��ʼ��Ϊ#13,�������쳣������#13���г�������� */
    enCsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );

    /* ��CS�����PS����һ�����ԭ��ֵΪ#13,����г�������� */
    if ( (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW == enPsCause))
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    /* �����վܾ�ԭ��ֵ#15���������Խ������� */
    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCause406ForbiddenPlmnForGprs
 ��������  : EPs Cause14�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                  ���������L1MAIN/PLMN LIST���жϵ�ǰԭ��ֵΪ��UE��������ע��
                  ԭ��ֵ�������ΪNAS_MMC_ADDITIONAL_ACTION_BUTT��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCause406ForbiddenPlmnForGprs(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    /* ��ӽ�ֹGPRS PLMN ��Ϣ */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

    enFsmId = NAS_MMC_GetCurrFsmId();

    switch ( enFsmId )
    {
        /* ����NAS_MMC_ADDITIONAL_ACTION_BUTT����ʾ��Ч��AdditionalActionֵ��
            MMC�����µ�ǰADDITIONAL ACTION��ֵ */
        case NAS_MMC_FSM_L1_MAIN :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);

            break;

        case NAS_MMC_FSM_PLMN_LIST :
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
            if (NAS_MML_REG_REGISTERED_HOME_NETWORK == NAS_MML_GetPsRegStatus())
            {
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            break;

        /* ������Ҫ���п�ѡ������ */
        default:
            enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

            break;
    }

    return enAdditionalAction;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCauseMoDetach
 ��������  : Eps Mo detach�ĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��08��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2014��07��26��
    ��    ��   : s00217060
    �޸�����   : DTS2014051501744:TAU�������û�detach,LMM���MMC��MO_DETACH_FAILURE,
                 MMC�յ���TAU����ᴥ������������ǰҪ�������ͷ����ӣ�����detach_req������ȥ
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCauseMoDetach(VOS_VOID)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    /* TAU�������û�detach,LMM���MMC��MO_DETACH_FAILURE,
       MMC�յ���TAU����ᴥ������������ǰҪ�������ͷ����ӣ�����detach_req������ȥ
       ���Դ˴��޸�Ϊ����פ�� */
    /* 3GPP 24301 Selection 5.5.3.2.6 Abnormal cases in the UE
    m)  Mobile originated detach required
        The tracking area updating procedure shall be aborted, and the UE initiated detach procedure shall be performed.
    */
    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCauseMtDetach
 ��������  : Eps mt detach�ĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��08��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCauseMtDetach(VOS_VOID)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFailCauseT3402Running
 ��������  : Eps T3402��ʱ���������еĺ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��08��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��1��31��
    ��    ��   : t00212959
    �޸�����   : DTS2013012909238:anycell������3402�����У�����available��ʱ�����ַ�����������
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��7��1��
    ��    ��   : c00318887
    �޸�����   : DTS2015061003127:L �·���״̬�ϱ���GU��һ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFailCauseT3402Running(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;

    enFsmId                = NAS_MMC_GetCurrFsmId();
    enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    /* ��ǰ��ONPLMNʱ��AVAILABLE��ʱ��δ����,��MMC��Ҫ��������*/
    if ( NAS_MMC_FSM_L1_MAIN   == enFsmId)
    {
        if (NAS_MMC_TIMER_STATUS_RUNING == enAvailableTimerStatus)
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }
    }
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}




/* ����detach EPS��causeֵ���� */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCause2ImsiUnknowInHss
 ��������  : Eps detach Cause2�Ĵ���
 �������  : VOS_VOID
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�
  3.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  7.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 mmc�յ�EPS����ȥע��(#2,NO_REATTACH),�ϱ�ע��״̬�ͷ���״̬
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause2ImsiUnknowInHss(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction
)
{

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* ����cs��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
    /*mmc�յ�EPS����ȥע��(#2,NO_REATTACH),�ϱ�ע��״̬�ͷ���״̬*/
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    *penCsRegAdditionalAction  = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    *penPsRegAdditionalAction  = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCause3IllegalMs
 ��������  : Eps detach Cause3�Ĵ���
 �������  : VOS_VOID
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�

  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�

  8.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                  mmc�յ�eps ����ȥע��(#3/6/8),�ϱ�ע��״̬�ͷ���״̬
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause3IllegalMs(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* ����cs ps��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    /*mmc�յ�eps ����ȥע��(#3/6/8),�ϱ�ע��״̬�ͷ���״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    if(VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    }

    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    *penPsAddition  = NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCause6IllegalMe
 ��������  : Eps detach Cause6�Ĵ���
 �������  : VOS_VOID
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�

*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause6IllegalMe(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    NAS_MMC_ProcEpsDetachCause3IllegalMs(penCsAddition, penPsAddition);
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCause7EpsServNotAllow
 ��������  : Eps detach Cause7�Ĵ���
 �������  : VOS_VOID
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�
  3.��    ��   : 2011��11��30��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:disable/enable ����
  4.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��

  5.��    ��   : 2012��4��4��
    ��    ��   : z40661
    �޸�����   : ���ⵥ��DTS2012032803448��PS oNLYʱ����Ҫ��Lģ�½���ANYCELL
               ������
  6.��    ��   : 2012��07��02��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
  7.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  8.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������

  9.��    ��   : 2012��9��25��
    ��    ��   : z40661
    �޸�����   : DTS2012082006273
 10.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 11.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
 12 ��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 mmc�յ�eps ����ȥע��(#7),�ϱ�ע��״̬�ͷ���״̬,
                 �ϱ�PS��ע��״̬Ϊ3��CS��PS�����Ʒ����������Ҫ���������ϱ�CS��ע��״̬Ϊ0����Ҫ�������ο���������״̬�ϱ�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause7EpsServNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                     *pstRatOrder;
    NAS_MML_MS_MODE_ENUM_UINT8                      enMsMode;

    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    pstRatOrder     = NAS_MML_GetMsPrioRatList();

    /* ���·���״̬ */

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* ����ps��״̬Ϊ��Ч */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    /* �ж��Ƿ���Ҫdisable L */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* ��¼����disable LTE��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }


    /*mmc�յ�eps ����ȥע��(#7),�ϱ�ע��״̬�ͷ���״̬,
       �ϱ�PS��ע��״̬Ϊ3��CS��PS�����Ʒ����������Ҫ���������ϱ�CS��ע��״̬Ϊ0����Ҫ�������ο���������״̬�ϱ�*/
     /*���ڽ����žͷ���������cs��ע��״̬�Ͳ��ϱ���*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);



    /* �����L��ģ����ԭ��ֵ7����Ҫanycell����,��ģ�����Ҫ���� */
    enMsMode    =    NAS_MML_GetMsMode();
    if ( (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
      || (NAS_MML_MS_MODE_PS_ONLY == enMsMode))
    {
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }
    else
    {
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCause8GprsAndNonGprsNotAllow
 ��������  : Eps detach Cause8�Ĵ���
 �������  : VOS_VOID
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�
  3.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����
  4.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  5.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  6.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  7.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  8.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  9.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                  mmc�յ�eps ����ȥע��(#3/6/8),�ϱ�ע��״̬�ͷ���״̬
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause8GprsAndNonGprsNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* ����cs ps��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    /*mmc�յ�eps����ȥע��(#3/6/8),�ϱ�ע��״̬�ͷ���״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    if(VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    }

    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    *penPsAddition  = NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCause11PlmnNotAllow
 ��������  : Eps detach Cause11�Ĵ���
 �������  : VOS_VOID
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�

*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause11PlmnNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    *penPsAddition  = NAS_MMC_ProcEpsAttachRegFailCause11PlmnNotAllow();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCause12TaNotAllow
 ��������  : Eps detach Cause12�Ĵ���
 �������  : VOS_VOID
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  5.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause12TaNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT8                           ucSimCsRegStatus;

    *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /*mmc�յ�eps ����ȥע��(#12),�ϱ�ע��״̬�ͷ���״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE_REGION);

    /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        /*mmc�յ�eps ����ȥע��(#12),�ϱ�ע��״̬�ͷ���״̬*/
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE_REGION);
    }

    *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCause13RoamNotAllow
 ��������  : Eps detach Cause14�Ĵ���
 �������  : VOS_VOID
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
    ��    ��   : l00305157
    �޸�����   : DTS2015061003127
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause13RoamNotAllow(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{

    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    *penPsAddition  = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCause14GprsNotAllowInThisPlmn
 ��������  : Eps detach Cause14�Ĵ���
 �������  : VOS_VOID
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�

  3.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����

  4.��    ��   : 2011��11��19��
    ��    ��   : L65478
    �޸�����   : DTS2012111402255:����detach cause #14û�з�������
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2015��1��5��
    ��    ��   : h00285180
    �޸�����   : LTE #14�ܾ��Ż�:DTS2015010401946
  7.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
  7.��    ��   : 2015��07��03��
    ��    ��   : l00305157
    �޸�����   : DTS2015061003127

*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause14GprsNotAllowInThisPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             stPlmnWithRat;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* ��ӽ�ֹGPRS PLMN ��Ϣ */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    if (VOS_TRUE == NAS_MMC_IsNeedDeleteEplmn_EpsDetachCause14GprsNotAllowInThisPlmn())
    {
        NAS_MMC_DeleteEPlmnList();
    }

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_LteRejCause14())
    {
        /* ��ҪDisable Lȫ�ֱ��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetLteRejCause14EnableLteTimerLen());

        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        return;
    }

    /* 24301_CR1499R3_(Rel-11)_C1-123437/ 24301_CR1520R1_(Rel-11)_C1-123939(rev
       of C1-123532)_24.301_Avoid to reselect E-UTRAN for #14/C1-141971�ܾ�ԭ��
       ֵ14ʱDISABLE LTE�Ĵ������,��Ӧ24301 5.5.2.3.2�½�����:
       #14: UE operating in CS/PS mode 1 of operation and supporting A/Gb mode or
            Iu mode may select GERAN or UTRAN radio access technology and proceed
            with the appropriate MM specific procedure according to the MM service state.
            In this case, the UE shall disable the E-UTRA capability (see subclause 4.5)*/
    if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_EpsDetachCause14GprsNotAllowInThisPlmn() )
    {
        /* ��ҪDisable Lȫ�ֱ��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

        PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
        stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                          NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                          MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14);
        }

        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
         return;
    }


    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    *penPsAddition  = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;


    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCause15NoSuitableCell
 ��������  : Eps detach Cause15�Ĵ���
 �������  : VOS_VOID
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��07��03��
    ��    ��   : l00305157
    �޸�����   : DTS2015061003127
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause15NoSuitableCell(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penCsAddition  = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    *penPsAddition  = NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCauseAbnormalCause
 ��������  : EPS detach OtherCause�Ĵ���
 �������  : ��
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��1��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�
  3.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:���ĺ�������
  4.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  5.��    ��   : 2012��07��03��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1��ѡ��״̬��������ע���EPS�ɹ���֮����յ�
                  detach������ԭ��ֵ��û����״̬��
  6.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCauseAbnormalCause(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause3IllegalMs
 ��������  : EpsServiceRequestFail Cause3�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��30��
    ��    ��   : l65478
    �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                 ���ݾ����ԭ��ֵ������

  3.��    ��   : 2012��2��15��
    ��    ��   : z40661
    �޸�����   : DTS2011121405203_PC���Է�������,֧��gUL��ģʱ,L�±�#3�ܾ�,��GU��ָ������
  4.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����  : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  8.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 ����LMM Service Reject����ϱ�(cause=#3)���ϱ�CS/PSע��״̬�ͷ���״̬
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause3IllegalMs(VOS_VOID)
{
    /* ���·���״̬ */

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* ����cs ps��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);



    /*����LMM Service Reject����ϱ�(cause=#3)���ϱ�CS/PSע��״̬�ͷ���״̬*/
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }


    /* modified by z40661 for DTS2011121405203_PC���Է�������, 2012-02-15, begin */
    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
    /* modified by z40661 for DTS2011121405203_PC���Է�������, 2012-02-15, end */

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause6IllegalMe
 ��������  : EpsServiceRequestFail Cause6�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause6IllegalMe(VOS_VOID)
{
    return NAS_MMC_ProcEpsServiceRequestFailCause3IllegalMs();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFailCauseCause7EpsServiceRequestFailServNotAllow
 ��������  : EpsServiceRequestFail Cause7�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��30��
    ��    ��   : l65478
    �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                 ���ݾ����ԭ��ֵ������

  3.��    ��   : 2011��12��16��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV����:����disable LTE�߼�

  4.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  5.��    ��   : 2012��07��02��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
  6.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  7.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����   : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ����
  8.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  9.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
 10.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 ����LMM Service Reject����ϱ�(cause=#7)���ϱ�CS/PSע��״̬�ͷ���״̬
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause7EpsServNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatOrder;

    pstRatOrder     = NAS_MML_GetMsPrioRatList();


    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* ����ps��״̬Ϊ��Ч */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
     /*����LMM Service Reject����ϱ�(cause=#7)���ϱ�ע��״̬�ͷ���״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);


    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */

    /* �ж��Ƿ���Ҫdisable L */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow())
    {
        /* ��¼����disable LTE��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
    {
        return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }
    else
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause9MsIdCannotBeDerivedByNW
 ��������  : EpsServiceRequestFail Cause9�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2015��11��19��
    ��    ��   : c00318887
    �޸�����   : DTS2015111701196,imsûע��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause9MsIdCannotBeDerivedByNW(VOS_VOID)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause10EpsServiceRequestFailImplicitlyDetached
 ��������  : EpsServiceRequestFail Cause9�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2015��11��19��
    ��    ��   : c00318887
    �޸�����   : DTS2015111701196,imsûע��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause10EpsImplicitlyDetached(VOS_VOID)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause11PlmnNotAllow
 ��������  : EpsServiceRequestFail Cause11�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��08��05��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2015��07��03��
    ��    ��   : l00305157
    �޸�����   : DTS2015061003127 �����ɺ���
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause11PlmnNotAllow(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId;

    pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

    /* ��ӽ�ֹ������Ϣ,�и���ʱ����Usim�����ļ� */
    if (VOS_TRUE == NAS_MML_AddForbPlmn(pstCurPlmnId))
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause12TaNotAllow
 ��������  : EpsServiceRequestFail Cause12�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  9.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 ����LMM Service Reject����ϱ�(cause=#12)���ϱ�CS/PSע��״̬�ͷ���״̬
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause12TaNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */



    /*����LMM Service Reject����ϱ�(cause=#12)���ϱ�CS/PSע��״̬�ͷ���״̬*/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE_REGION);
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (VOS_TRUE == ucSimCsRegStatus))
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE_REGION);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause13RoamNotAllow
 ��������  : EpsServiceRequestFail Cause13�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2015��07��03��
    ��    ��   : l00305157
    �޸�����   : DTS2015061003127
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause13RoamNotAllow(VOS_VOID)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause14GprsNotAllowInThisPlmn
 ��������  : EpsServiceRequestFail Cause14�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��22��
    ��    ��   : h00202780
    �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR����
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    /* ��ӽ�ֹGPRS PLMN ��Ϣ */
    NAS_MML_AddForbGprsPlmn(NAS_MML_GetCurrCampPlmnId());

    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause15NoSuitableCell
 ��������  : EpsServiceRequestFail Cause15�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2015��07��03��
    ��    ��   : l00305157
    �޸�����   : DTS2015061003127
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause15NoSuitableCell(VOS_VOID)
{
    /* ���·���״̬ */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes
��������  : ע�ᱻ��#16���������Ƿ���Ҫdisable lte
�������  : ��
�������  : ��
�� �� ֵ  : VOS_TRUE  - ��ҪDisable L
            VOS_FALSE - ����ҪDisable L
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��4��20��
  ��    ��   : z00161729
  �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes(VOS_VOID)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();

    /* ��ǰLTE��ģ,���ز���Ҫdisable lte */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* ����CS/PS mode 1��IMS VOICE���� */
    if ((VOS_TRUE                               == NAS_MML_GetImsVoiceAvailFlg())
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1  != enLUeMode))
    {
        return VOS_FALSE;
    }

    /* Э��汾С��R11,������Ҫdisable lte */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_TRUE;
    }

    if (NAS_MML_PERSISTENT_BEARER_STATE_NOT_EXIST == NAS_MML_GetPersistentBearerState())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes
��������  : ע�ᱻ��#17���������Ƿ���Ҫdisable lte
�������  : ��
�������  : ��
�� �� ֵ  : VOS_TRUE  - ��ҪDisable L
            VOS_FALSE - ����ҪDisable L
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��4��20��
  ��    ��   : z00161729
  �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes(VOS_VOID)
{
    return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause8GprsAndNonGprsNotAllow
 ��������  : Eps ServiceRequestFail Cause8�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause8GprsAndNonGprsNotAllow(VOS_VOID)
{
    /* Э��汾С��R11��other cause���� */
    if ( NAS_MML_3GPP_REL_R11 > NAS_MML_GetLte3gppRelVersion())
    {
        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
        }

       return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    /* 24301_CR1595R2_(Rel-11)_C1-124966 MMC������ͨ��������TAU�����Լ�SERVICE REQUEST���ܣ�
       ԭ��ֵΪ8�Ĵ���,��Ӧ24301 5.6.1.5�½�����:
       #8:The UE shall set the EPS update status to EU3 ROAMING NOT ALLOWED (and
          shall store it according to subclause 5.1.3.3) and shall delete any GUTI,
          last visited registered TAI, TAI list and eKSI. The UE shall consider
          the USIM as invalid for EPS services until switching off or the UICC
          containing the USIM is removed. The UE shall enter the state EMM-DEREGISTERED.
       ��CR��Э��汾���� */
    return NAS_MMC_ProcEpsServiceRequestFailCause3IllegalMs();
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause42SevereNetworkFailure
 ��������  : EpsServiceRequestFail Cause42�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
1.��    ��   : 2015��4��19��
  ��    ��   : z00161729
  �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause42SevereNetworkFailure(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* Э��汾С��R11��other cause���� */
    if ( NAS_MML_3GPP_REL_R11 > NAS_MML_GetLte3gppRelVersion())
    {
        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
        }

       return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }

    /* 24301_CR1473R2_(Rel-11)_C1-123386 MMC����ATTACH��TAU��SERVICE REQUEST�����б���ԭ��ֵ42�Ĵ���
      24301 5.6.1.5�½�����:
      The UE shall set the EPS update status to EU2 NOT UPDATED, and shall delete
    any GUTI, last visited registered TAI, eKSI, and list of equivalent PLMNs.
    The UE shall start an implementation specific timer, setting its value to 2
    times the value of T as defined in 3GPP TS 23.122 [6]. While this timer is
    running, the UE shall not consider the PLMN + RAT combination that provided
    this reject cause, a candidate for PLMN selection. The UE then enters state
    EMM-DEREGISTERED.PLMN-SEARCH in order to perform a PLMN selection according
    to 3GPP TS 23.122 [6].
       If A/Gb mode or Iu mode is supported by the UE, the UE shall in addition
    set the GMM state to GMM-DEREGISTERED, GPRS update status to GU2 NOT UPDATED,
    and shall delete the P-TMSI, P-TMSI signature, RAI and GPRS ciphering key sequence number.
    ��CR��Э��汾���� */
    PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
    stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

    /* ������#42����������ֹ���뼼�������б��У���ֹʱ��Ϊ2*T,�������� */
    NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                  NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice(),
                                                  MMC_LMM_DISABLE_LTE_REASON_BUTT);

    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause35RequestedServiceOptionNotAuthorizedInThisPlmn
 ��������  : EpsServiceRequestFail Cause35�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��03��06��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��24��
    ��    ��   : w00242748
    �޸�����   : DTS2013101106863:L�±���ԭ��ֵ#35��ֻ����R10����Э�����ϴ������#11
                 ԭ��ֵ������ͬ��������OTHER CAUSE������

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause35ReqServOptNotAuthorizedInThisPlmn(VOS_VOID)
{
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;

    pstMs3GppRel    = NAS_MML_GetMs3GppRel();

    if ( NAS_MML_3GPP_REL_R9 >= pstMs3GppRel->enLteNasRelease )
    {
        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
        }

       return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }
    else
    {
        return NAS_MMC_ProcEpsServiceRequestFailCause11PlmnNotAllow();
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause257AccessBarrd
 ��������  : EpsServiceRequestFail AccessBarrd�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  3.��    ��   : 2012��2��16��
    ��    ��   : h00202780
    �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR����
                   CSFB�����У��յ�LMM�ϱ���service���ܣ������¼��ֳ�����Ҫ��ѡ��GU�£����������ĳ��ԣ�
                ���뱻������NAS���������ܾ�
                Э��ԭ�ģ�3GPP 24.301,5.6.1.6�½�, Abnormal cases in the UE :

                1)Access barred because of access class barring or NAS signalling connection establishment rejected by the network
                    If the service request was initiated for CS fallback, the UE shall select GERAN or UTRAN radio access technology. The UE then proceeds with appropriate MM and CC specific procedures. The EMM sublayer shall not indicate the abort of the service request procedure to the MM sublayer��

                2)�ײ���·ʧ�ܣ�Lower layer failure before the service request procedure is completed (see subclause 5.6.1.4) or before SERVICE REJECT message is received����

                3)�յ�Service Reject��Ϣ������ԭ��ֵ��24.301��5.6.1.5�ж��� other
                    EMM cause values than those treated in subclause 5.6.1.5(ԭ��ֵΪ#3��
                    #6��#7��#9��#10��#11��#12��#13��#15��#18��#25��#39)
  7.��    ��   : 2012��06��13��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1���޸ķ�����������ֹ�Ĵ���

  8.��    ��   : 2012��7��25��
    ��    ��   : z00161729
    �޸�����   : DTS2012072506927:MMC�յ�LMM ��service result indָʾaccess barʱ
                 ��Ӧ���·���״̬Ϊ���Ʒ���Ӧ����L�ϱ���������״̬
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause257AccessBarrd(VOS_VOID)
{


    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);
    }

    /* service request�������ֹ���������ܽ���TAU�Ľ��� */
    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause256AuthRej
 ��������  : EpsServiceRequestFail Reg Auth rej�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��2��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע��ʧ��ԭ��ֵ�ĺ�������������ԭ��ֵ��
                  ���ֺ���������һ���ԡ�
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2012��09��15��
    ��    ��   : z00161729
    �޸�����  : DTS2012090708320��MMC�յ�L��ע������ps cs���Ƿ���Ч״̬��Ҫ���£�ԭ����gmm���´���ʱ������
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2014��4��29��
    ��    ��   : s00261364
    �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
  8.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 ����LMM Service Reject�����У���Ȩ���ܾ����ϱ�ע��״̬�ͷ���״̬
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause256AuthRej(VOS_VOID)
{
    /* ɾ��EPLMN */
    NAS_MMC_DeleteEPlmnList();

    /* ���·���״̬ */

    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, begin */
    /* ����cs ps��״̬Ϊ��Ч */
    NAS_MML_SetSimCsRegStatus(VOS_FALSE);
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    /* Modified by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-20, end */



    NAS_MMC_ChangePsRegState(NAS_MML_REG_REGISTERED_DENIED);
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);



    /*����LMM Service Reject�����У���Ȩ���ܾ����ϱ�ע��״̬�ͷ���״̬*/
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
    {
        NAS_MMC_ChangeCsRegState(NAS_MML_REG_REGISTERED_DENIED);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION);
    }

    return NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCauseCsDomainNotAvailable
 ��������  : CsDomainNotAvailable�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��16��
    ��    ��   : h00202780
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2015��4��18��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
  3.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 LMM Service Reject����ϱ�(cause=#18),
                 ���ϱ�CS��ע��״̬�ͷ���״̬��������TAU��ATTCH�������ڸ����յ��������������ϱ�
  5.��    ��   : 2015��9��6��
    ��    ��   : z00359541
    �޸�����   : DTS2015081407087: �ӿڵ�����ɾ��bitOpReqType��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause18CsDomainNotAvailable(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));

    /* LMM Service Reject����ϱ�(cause=#18)*/
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);


    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_ServiceReqFailCause18CsDomainNotAvailable())
    {
        /* ��ҪDisable Lȫ�ֱ��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        /* ��������������ʱ��ʱ������ͨ���в�ͬ��disable lteԭ��ֵҲ��ͬ */
        if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_EMERGENCY_CALL);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsfbEmgCallEnableLteTimerLen());
        }
        else
        {
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());
        }

        PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
        stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                          NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                          MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }

        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);

        return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCauseNotAuthorizedForThisCsg
 ��������  : NotAuthorizedForThisCsg�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��2��16��
    ��    ��   : h00202780
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause25NotAuthorizedForThisCsg(VOS_VOID)
{
    /* ���·���״̬ */
    NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_LIMITED_SERVICE);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCauseCsDomainTempNotAvailable
 ��������  : CsDomainTempNotAvailable�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��2��16��
    ��    ��   : h00202780
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��4��8��
    ��    ��   : B00269685
    �޸�����   : CSFBʧ��ԭ��ֵ#39������CS�����ע��״̬��������AP�����·���������
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause39CsDomainTempNotAvailable(VOS_VOID)
{

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
    }

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsServiceRequestFailCause40NoEpsBearerActived
 ��������  : EpsServiceRequestFail Cause40�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��11��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV BBIT����
  3.��    ��   : 2012��2��22��
    ��    ��   : h00202780
    �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR����
                CSFB�����У��յ�LMM�ϱ���service���ܣ������¼��ֳ�����Ҫ��ѡ��GU�£����������ĳ��ԣ�
                ���뱻������NAS���������ܾ�
                Э��ԭ�ģ�3GPP 24.301,5.6.1.6�½�, Abnormal cases in the UE :

                1)Access barred because of access class barring or NAS signalling connection establishment rejected by the network
                    If the service request was initiated for CS fallback, the UE shall select GERAN or UTRAN radio access technology. The UE then proceeds with appropriate MM and CC specific procedures. The EMM sublayer shall not indicate the abort of the service request procedure to the MM sublayer��

                2)�ײ���·ʧ�ܣ�Lower layer failure before the service request procedure is completed (see subclause 5.6.1.4) or before SERVICE REJECT message is received����

                3)�յ�Service Reject��Ϣ������ԭ��ֵ��24.301��5.6.1.5�ж��� other
                    EMM cause values than those treated in subclause 5.6.1.5(ԭ��ֵΪ#3��
                    #6��#7��#9��#10��#11��#12��#13��#15��#18��#25��#39)
  4.��    ��   : 2013��12��25��
    ��    ��   : f62575
    �޸�����   : DTS2013101106863:L�±���ԭ��ֵ#40��ֻ����R10����Э�����ϴ������#10
                 ԭ��ֵ������ͬ��������OTHER CAUSE������
  5.��    ��   : 2015��11��19��
    ��    ��   : c00318887
    �޸�����   : DTS2015111701196,imsûע��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsServiceRequestFailCause40NoEpsBearerActived(VOS_VOID)
{
    NAS_MML_MS_3GPP_REL_STRU           *pstMs3GppRel = VOS_NULL_PTR;

    pstMs3GppRel = NAS_MML_GetMs3GppRel();
    /* �汾ΪR10�汾���Ժ�汾����ǰԭ��ֵ��#40��ԭ��ֵת�����#10����Э��3GPP
    24.301 5.5.3.3.5 */
    if (NAS_MML_3GPP_REL_R9 >= pstMs3GppRel->enLteNasRelease)
    {
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON);
        }

        return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    }
    else
    {
        if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
        {
            return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
        }

        return NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }
}




#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailForbLaWithValidPeriod
 ��������  : Csע�ᱻ�ܽ�ֹLA��Чʱ���Ĵ���
 �������  : NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enRegFailCause,
              NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enAction
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��23��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCsRegFailForbLaWithValidPeriod(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enRegFailCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enAction
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg = VOS_NULL_PTR;
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_STRU         stForbLaWithValidPeriodCfgInfo;
    VOS_UINT32                                              ulAttempcnt;

    pstForbLaWithValidPeriodCfg                             = NAS_MML_GetForbLaWithValidPeriodCfg();
    stForbLaWithValidPeriodCfgInfo.usRegFailCause           = enRegFailCause;
    stForbLaWithValidPeriodCfgInfo.usForbLaValidPeriodLen   = NAS_MML_GetForbLaWithValidPeriodTimerLen(enRegFailCause, pstForbLaWithValidPeriodCfg);
    stForbLaWithValidPeriodCfgInfo.usPunishTimeLen          = NAS_MML_GetCustomizedForbLaPunishTimeLen(enRegFailCause, pstForbLaWithValidPeriodCfg);
    ulAttempcnt                                             = NAS_MMC_GetRegRsltAttemptCounter(MM_MMC_CS_REG_RESULT_IND);

    /* ע��ʧ��ԭ��ֵ���ٶ����б��У�����Ҫ���� */
    if (VOS_FALSE == NAS_MMC_IsFailCauseInCustomizedForbLaCfgList(enRegFailCause))
    {
        return;
    }

    /* ��ǰ�Ƿ���Ҫ���� */
    if (NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION == enAction)
    {
        /* �ܾ�ԭ��ֵΪ17��SOR���Դ��ҳ��Դ���������4�Σ�����Ҫ�����ֹLA�б� */
        if ( (VOS_TRUE                               == NAS_MML_GetCsRejSearchSupportFlg())
          && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enRegFailCause)
          && (NAS_MML_MAX_CS_REG_FAIL_CNT            == ulAttempcnt) )
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcCsRegFailForbLaWithValidPeriod(): SOR ON, Don't add to Customized Forb La since attempt cnt is 4");
            return;
        }

        if (VOS_TRUE == NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod(&stForbLaWithValidPeriodCfgInfo))
        {
            /* ������ʱ�� */
            NAS_MML_StartCustomizedForbLaTimer();
        }
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFail
 ��������  : Csע�ᱻ�ܵĴ���
 �������  : VOS_UINT16                          usCause,
              VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��29��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

 2.��    ��   : 2012��2��4��
   ��    ��   : w00167002
   �޸�����   : �޸ĺ������������ӱ���ע����ָ�뵽��ǰ�ļ���ȫ�ֱ����У�
                 �����ڴ���ע�����еĺ�����ʹ��ע������������Ϣ��
 3.��    ��   : 2013��8��15��
   ��    ��   : l00208543
   �޸�����   : ����ܾ�ԭ��ֵ�����ϱ�
 4.��    ��   : 2014��01��10��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;

    /* ����ע������Ϣ */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstCsRegRsltInd);

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */

    /* AT^REJINFO�����ϱ�����REJINFO�ϱ���MSCC ������ע���ʱ����ϱ� */
    if (VOS_FALSE == pstCsRegRsltInd->ucIsComBined)
    {
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_FALSE, pstCsRegRsltInd->enRegFailCause);
    }

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼CSע��ʧ���쳣log */
    NAS_MMC_CsRegErrRecord(pstCsRegRsltInd);
#endif

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_CS_REG_FAIL);

    ulTblSize = sizeof(gastMmcProcCsRegFailCause)/sizeof(gastMmcProcCsRegFailCause[0]);

    /*��CSע��ԭ���gastMmcProcCsRegFailCause�У����Ҷ�Ӧ�Ĵ�����*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (pstCsRegRsltInd->enRegFailCause == gastMmcProcCsRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcCsRegFailCause[i].pRegFailProcFunc;

            break;
        }

    }

    /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();

    }
    /*û���ҵ�ʱ������CS Other Cause����*/
    else
    {
        enAction = NAS_MMC_ProcCsRegFailCauseAbnormalCause(pstCsRegRsltInd->enRegFailCause,
                                                   pstCsRegRsltInd->ulLuAttemptCnt);
    }

    NAS_MMC_ProcCsRegFailForbLaWithValidPeriod(pstCsRegRsltInd->enRegFailCause, enAction);

    return enAction;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegFail
 ��������  : Psע�ᱻ�ܵĴ���
 �������  : VOS_UINT16                          usCause,
              VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��8��15��
    ��    ��   : l00208543
    �޸�����   : ����ܾ�ԭ��ֵ�����ϱ�
  3.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;

    /* ����ע������Ϣ */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstPsRegRsltInd);

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */

    /* AT^REJINFO�����ϱ�����REJINFO�ϱ���MSCC */
    if (GMM_MMC_REG_DOMAIN_PS_CS == pstPsRegRsltInd->enRsltDomain)
    {
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, pstPsRegRsltInd->enRegFailCause);
    }
    else
    {
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, pstPsRegRsltInd->enRegFailCause);
    }

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼PSע��ʧ���쳣log */
    NAS_MMC_PsRegErrRecord(pstPsRegRsltInd);
#endif

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_PS_REG_FAIL);

    ulTblSize = sizeof(gastMmcProcPsRegFailCause)/sizeof(gastMmcProcPsRegFailCause[0]);

    /*��PSע��ԭ���gastMmcProcPsRegFailCause�У����Ҷ�Ӧ�Ĵ�����*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (pstPsRegRsltInd->enRegFailCause == gastMmcProcPsRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcPsRegFailCause[i].pRegFailProcFunc;

            break;
        }
    }

    /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();

    }
    /*û���ҵ�ʱ������PS Other Cause����*/
    else
    {
        enAction = NAS_MMC_ProcPsRegFailCauseAbnormalCause(pstPsRegRsltInd->enRegFailCause,
                                                           pstPsRegRsltInd->ulRegCounter);
    }

    return enAction;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsServiceRegFail
 ��������  : Psҵ�񱻾ܵĴ���
 �������  : VOS_UINT16                          usCause,
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��5��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : �޸ĺ������������ӱ���ע����ָ�뵽��ǰ�ļ���ȫ�ֱ����У�
                 �����ڴ���ע�����еĺ�����ʹ��ע������������Ϣ��
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcPsServiceRegFail(
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;

    /* ����ע������Ϣ */
    NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_SERVICE_RESULT_IND, pstServiceRsltInd);

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼PSע��ʧ���쳣log */
    NAS_MMC_PsServiceRegErrRecord(pstServiceRsltInd);
#endif

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_PS_SERVICE_REG_FAIL);

    ulTblSize = sizeof(gastMmcProcPsRegFailCause)/sizeof(gastMmcProcPsRegFailCause[0]);

    /*��PSע��ԭ���gastMmcProcPsRegFailCause�У����Ҷ�Ӧ�Ĵ�����*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (pstServiceRsltInd->enRegFailCause == gastMmcProcPsRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcPsRegFailCause[i].pRegFailProcFunc;

            break;
        }

    }
    /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();

    }
    /*û���ҵ�ʱ������פ��*/
    else
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    return enAction;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcGmmNetworkDetachInd
 ��������  : ����GMM������DETACH��Ϣ
 �������  : pstDetachMsg GMM������detach��Ϣ
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��05��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  3.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬

  4.��    ��   : 2013��7��1��
    ��    ��   : w00167002
    �޸�����   : SVLTE STC:GMM����ע��ɹ������෢��imsi DETACH����ʱע��״̬Ϊ
                 NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH������״̬ΪNORMAL SERVICE ;
                 �޸�Ϊ�����ǰ��IMSI detach,�򲻴���
  5.��    ��   : 2014��04��4��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
  6.��    ��   : 2014��11��29��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseI��Ŀ�޸�

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcGmmNetworkDetachInd(
    MMCGMM_NETWORK_DETACH_IND_STRU     *pstDetachMsg
)
{

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-28, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-28, end */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPrioAdditionalAction;

    /* ����ע������Ϣ */
    NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_NETWORK_DETACH_IND, pstDetachMsg);

    enAction            = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
    ulTblSize           = sizeof(gastMmcProcPsRegFailCause)/sizeof(gastMmcProcPsRegFailCause[0]);

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-29, begin */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_GUT_NW_DETACH);

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-29, end */
    /* ��TAF����PS��ķ���״̬ */
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    NAS_MMC_SndMsccDetachInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstDetachMsg->ulDetachType,
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
                            pstDetachMsg->ulDetachCause);

    if (NAS_MMC_GMM_NT_DETACH_NOATTACH == pstDetachMsg->ulDetachType)
    {
        /*��Epsע��ԭ���gastMmcProcEpsRegFailCause�У����Ҷ�Ӧ�Ĵ�����*/
        for ( i = 0 ; i < ulTblSize; i++ )
        {
            if (pstDetachMsg->ulDetachCause == gastMmcProcPsRegFailCause[i].enRegCause)
            {
                pRegFailProcFunc = gastMmcProcPsRegFailCause[i].pRegFailProcFunc;

                break;
            }

        }

        /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
        if (VOS_NULL_PTR != pRegFailProcFunc)
        {
            enAction = pRegFailProcFunc();
        }
        else
        {
            /* ��ȡCS addition,����NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON�Ƚϣ�
               �������Ҫ�������������PSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
            enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
            enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON, enPrioAdditionalAction);
            if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
            {

                /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
                NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
                /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */
                NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            }

            enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
        }
    }

    else if ( NAS_MMC_GMM_NT_DETACH_IMSI == pstDetachMsg->ulDetachType )
    {
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    else
    {
        /*��ΪREATTACH���͵�ʱ�򣬲��ϱ�ע��״̬�ͷ���״̬��*/
        enAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }

    return enAction;

}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause
 ��������  : ����EPS OtherCause�Ĵ���
 �������  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
             penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
                 1)  attemptCount < MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
                 2)  attemptCount >= MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION

  2.��    ��   : 2012��1��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209/DTS2011122704039:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                1): ��UE��������ע���ԭ��ֵ(��ע�ᱻ��causeΪ260),��ʱ������
                    OnPlmn/PlmnList��,����Ҫ���п�ѡ�������򷵻�Ϊ
                    NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON

                2):�������³����Ŀ���:�ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,
                �ҵ�ǰPLMN����EPlmn�б������Ҫ���ؿ�ѡ���������ԡ�
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2012��06��02��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,����ע��ʧ�ܣ���ҪDisable L
  5.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  6.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  7.��    ��   : 2013��6��3��
    ��    ��   : z00161729
    �޸�����   : SVLTE �޸�
  8.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
  9.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
 10.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    VOS_UINT32                          ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    /* ȡ�õ�ǰ��ע������Ϣ���� */
    enRegRsltType = NAS_MMC_GetRegRsltType();

    /* ȡ��Attempt Counter��ֵ */
    ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* cs ps���ע��ʧ��,��ǰ������ONPLMN����PLMN LIST״̬���������AttemptCounter
       �����ز�ͬ��ADDITIONAL ACTIONֵ */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* ����EPSע��ʧ��Attemptδ�ﵽ�������Ĵ���Ĵ��� */
        NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes(penPsRegAdditionalAction,
                                                                    penCsRegAdditionalAction);
    }
    else
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* ���·���״̬ */

        /* ֪ͨTAF��ǰ�ķ���״̬ */

        if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegRsltFailMaxTimes() )
        {
            /* ��ҪDisable Lȫ�ֱ��� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, begin */
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, end */

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                              NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                              MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }

            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }

        /*��������ڲ��б�����ʱ��ҲҪ�ϱ�״̬���ο�NAS_MMC_RcvLmmMmcTauResultInd_OnPlmn()�е����������ڲ��б�����*/
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(*penCsRegAdditionalAction))
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }


        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailCause401OtherCause
 ��������  : ����EPS OtherCause�Ĵ���
 �������  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
             penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
                 1)  attemptCount < MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
                 2)  attemptCount >= MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION

  2.��    ��   : 2012��1��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209/DTS2011122704039:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
                1): ��UE��������ע���ԭ��ֵ(��ע�ᱻ��causeΪ260),��ʱ������
                    OnPlmn/PlmnList��,����Ҫ���п�ѡ�������򷵻�Ϊ
                    NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON

                2):�������³����Ŀ���:�ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,
                �ҵ�ǰPLMN����EPlmn�б������Ҫ���ؿ�ѡ���������ԡ�
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2012��06��07��
    ��    ��   : s00217060
    �޸�����   : #401�����Դ����ﵽ5�Σ���ҪDisable L
  5.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  6.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  7.��    ��   : 2013��6��3��
    ��    ��   : z00161729
    �޸�����   : SVLTE �޸�
  8.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
  9.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  10.��    ��   : 2015��4��22��
     ��    ��   : z00161729
     �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailCause401OtherCause(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    VOS_UINT32                          ulAttemptCnt;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    /* ȡ�õ�ǰ��ע������ */
    enRegRsltType = NAS_MMC_GetRegRsltType();
    ulAttemptCnt  = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);

    /* cs ps���ע��ʧ��,��ǰ������ONPLMN����PLMN LIST״̬���������AttemptCounter
       �����ز�ͬ��ADDITIONAL ACTIONֵ */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes(penPsRegAdditionalAction,
                                                                    penCsRegAdditionalAction);
    }
    else
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* ���·���״̬ */

        /* ֪ͨTAF��ǰ�ķ���״̬ */

        if ( VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegRsltFailMaxTimes() )
        {
            /* ��ҪDisable Lȫ�ֱ��� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, begin */
            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, end */

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

            PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
            stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

            if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                               NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                               MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
            }

            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
        }
        else
        {
            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        }
        /*��������ڲ��б�����ʱ��ҲҪ�ϱ�״̬���ο�NAS_MMC_RcvLmmMmcTauResultInd_OnPlmn()�е����������ڲ��б�����*/
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(*penCsRegAdditionalAction))
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes
 ��������  : ����EPSע��ʧ��Attemptδ�ﵽ�������Ĵ���Ĵ���
 �������  : ��
 �������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
              penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  8.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 mmc�յ�COMBINED ATU�REJ(#3/6/8),�ϱ�ע��״̬�ͷ���״̬
                 MMC���յ�LMMģ��ע����COMBINED TAU REJ(other casue),δ�ﵽ�������Ĵ��� ����PS��ע��״̬�����ϱ�����״̬
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegFailAttemptCouterLessThanMaxTimes(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo        = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                          ulInEplmnListFlag;
    VOS_UINT32                          ulUserSpecPlmnFlag;

    /* �жϵ�ǰ�����Ƿ����û�ָ�������� */
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(),
                                                &(pstUserSpecPlmn->stPlmnId));

    /* �жϵ�ǰ�����Ƿ���EPlmn�б��� */
    pstEplmnInfo       = NAS_MML_GetEquPlmnList();

    ulInEplmnListFlag  = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                              pstEplmnInfo->ucEquPlmnNum,
                                              pstEplmnInfo->astEquPlmnAddr);

    /* �ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,�ҵ�ǰPLMN����EPlmn�б��
       ����Ϊ��ǰplmn��NOT ALLOWED����Ҫ�������� */
    if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
      && (VOS_FALSE                          == ulUserSpecPlmnFlag)
      && (VOS_FALSE                          == ulInEplmnListFlag) )
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }

        return ;
    }

    /* ��GU����һ��,ͨ���жϷ���״̬�������Ƿ����ע��״̬�ͷ���״̬��*/
    if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrCsService())
    {
         NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
         NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS,NAS_MMC_LIMITED_SERVICE);
    }
    if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrPsService())
    {
         NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
         NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
    }
    /* ����mmc�����ȴ�ע���� */
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCauseAbnormalCause
 ��������  : ����EPS OtherCause�Ĵ���
 �������  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  5.��    ��   : 2014��01��11��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII ��Ŀ�޸�

  6.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                ����EMM��COMBINED TAU(eps only, other cause)�ɹ����ϱ�CS/PSע��״̬�ͷ���״̬
  7.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCauseAbnormalCause(
    VOS_UINT16                                               usCause,
    VOS_UINT32                                               ulAttemptCnt,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    *penCsRegAdditionalAction
)
{
    /*
    1)  attemptCount < MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
    2)  attemptCount >= MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION
    */

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-11, begin */
    /* ��������Э��,other causeҲ��ΪEPSע��ɹ�,��˸��·���״̬ */
    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
    NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCauseAbnormalCause: Update Reg state and Service state");
    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-11, end */

    /* ps��ע��ɹ���cs��ע��ʧ�� */
    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* ��GU����һ��,ͨ���жϷ���״̬�������Ƿ����ע��״̬�ͷ���״̬��*/
        if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrCsService())
        {
             /* ����ע��״̬Ϊ0 */
             NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
             NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);
        }
        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    }
    else
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* ���·���״̬ */

        /* ֪ͨTAF��ǰ�ķ���״̬ */

        NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        /*����EMM��COMBINED TAU/ATTACH(eps only,  other cause)�ɹ�,�Ҵﵽ���������ϱ�CS/PSע��״̬�ͷ���״̬*/
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

        *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

    }

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedAttachEpsRegFail
 ��������  : ����Eps attach���ܵĴ���
 �������  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : penPsRegAdditionalAction - �յ�ע��attach�����Э��Ҫ���ps���additional��������
             penCsRegAdditionalAction - �յ�ע��attach�����Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��13��
    ��    ��   : z00161729
    �޸�����   : DTS2011121302231:attach����#9/#10��Э��Ӧ�ð�other cause����
  3.��    ��   : 2011��1��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸�
  4.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
  5.��    ��   : 2013��8��15��
    ��    ��   : l00208543
    �޸�����   : ������ܾ�ԭ��ֵ�ϱ�
  6.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
  7.��    ��   : 2015��10��23��
    ��    ��   : l00289540
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedAttachEpsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulTblSize;
    NAS_MMC_PROC_COMBINED_EPS_REG_FAIL_FUNC_PTR             pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* ����ע������Ϣ */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstLmmAttachIndMsg);

    /* ������ע������Ϣ��ȡ�þܾ�ԭ��ֵ */
    NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause(pstLmmAttachIndMsg,
                                          &enPsRegRsltCause, &enCsRegRsltCause);

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, enPsRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_ATTACH_FAIL);

    ulTblSize = sizeof(gastMmcProcCombinedAttachEpsRegFailCause)/sizeof(gastMmcProcCombinedAttachEpsRegFailCause[0]);

    /* ������Epsע��ԭ���gastMmcProcCombinedAttachEpsRegFailCause�У����Ҷ�Ӧ�Ĵ����� */
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enPsRegRsltCause == gastMmcProcCombinedAttachEpsRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcCombinedAttachEpsRegFailCause[i].pCombinedEpsRegFailProcFunc;
            break;
        }

    }

    /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        pRegFailProcFunc(penPsRegAdditionalAction, penCsRegAdditionalAction);

    }
    /*û���ҵ�ʱ������PS Other Cause����*/
    else
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause(penPsRegAdditionalAction,
                                                         penCsRegAdditionalAction);
    }

    if (VOS_TRUE == NAS_MML_IsNetworkRegFailCause(enPsRegRsltCause))
    {
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, enPsRegRsltCause);
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, enPsRegRsltCause);

        /* ����DPLMN NPLMN�б� */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);
            NAS_MMC_LogDplmnNplmnList();
        }
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedTauEpsRegFail
 ��������  : ����Eps tau���ܵĴ���
 �������  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : penPsRegAdditionalAction - �յ�ע��tau�����Э��Ҫ���ps���additional��������
             penCsRegAdditionalAction - �յ�ע��tau�����Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��13��
    ��    ��   : z00161729
    �޸�����   : DTS2011121302231:attach����#9/#10��Э��Ӧ�ð�other cause����
  2.��    ��   : 2011��1��7��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸�
  3.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
  4.��    ��   : 2013��8��15��
    ��    ��   : l00208543
    �޸�����   : ������ܾ�ԭ��ֵ�ϱ�
  5.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
  6.��    ��   : 2014��11��3��
    ��    ��   : z00161729
    �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedTauEpsRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulTblSize;
    NAS_MMC_PROC_COMBINED_EPS_REG_FAIL_FUNC_PTR             pRegFailProcFunc = VOS_NULL_PTR;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* ����ע������Ϣ */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstLmmTauIndMsg);

    /* ������ע������Ϣ��ȡ�þܾ�ԭ��ֵ */
    NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(pstLmmTauIndMsg,
                                          &enPsRegRsltCause, &enCsRegRsltCause);

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, enPsRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_TAU_FAIL);

    ulTblSize = sizeof(gastMmcProcCombinedTauEpsRegFailCause)/sizeof(gastMmcProcCombinedTauEpsRegFailCause[0]);

    /* ������Epsע��ԭ���gastMmcProcCombinedTauEpsRegFailCause�У����Ҷ�Ӧ�Ĵ����� */
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enPsRegRsltCause == gastMmcProcCombinedTauEpsRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcCombinedTauEpsRegFailCause[i].pCombinedEpsRegFailProcFunc;
            break;
        }

    }

    /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        pRegFailProcFunc(penPsRegAdditionalAction, penCsRegAdditionalAction);

    }
    /*û���ҵ�ʱ������PS Other Cause����*/
    else
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseAbnormalCause(penPsRegAdditionalAction,
                                                         penCsRegAdditionalAction);
    }

    if (VOS_TRUE == NAS_MML_IsNetworkRegFailCause(enPsRegRsltCause))
    {
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, enPsRegRsltCause);
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, enPsRegRsltCause);

        /* ����DPLMN NPLMN�б� */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

            NAS_MMC_LogDplmnNplmnList();
        }
    }

    return;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCombinedEpsRegCsFail
 ��������  : ����Epsע��only eps�ɹ��Ĵ���
 �������  : VOS_UINT16                             usCause,
             VOS_UINT32                             ulAttemptCnt
 �������  : penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 phase IV�޸�
  3.��    ��   : 2014��11��3��
    ��    ��   : z00161729
    �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCombinedEpsRegOnlyEpsSucc(
    VOS_UINT16                                              usCause,
    VOS_UINT32                                              ulAttemptCnt,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR                          pRegFailProcFunc = VOS_NULL_PTR;

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_COMBINE_EPS_REG_ONLY_EPS_SUCC);

    ulTblSize = sizeof(gastMmcProcCombinedEpsRegOnlyEpsSuccCause)/sizeof(gastMmcProcCombinedEpsRegOnlyEpsSuccCause[0]);

    /* ������Epsע��ԭ���gastMmcProcCombinedEpsRegOnlyEpsSuccCause�У����Ҷ�Ӧ�Ĵ����� */
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (usCause == gastMmcProcCombinedEpsRegOnlyEpsSuccCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcCombinedEpsRegOnlyEpsSuccCause[i].pRegFailProcFunc;
            break;
        }

    }

    /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        *penCsRegAdditionalAction = pRegFailProcFunc();

    }
    /*û���ҵ�ʱ������PS Other Cause����*/
    else
    {
        NAS_MMC_ProcCombinedEpsRegOnlyEpsSuccCauseAbnormalCause(usCause, ulAttemptCnt,
                                                             penCsRegAdditionalAction);
    }

    NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);
    if (VOS_TRUE == NAS_MML_IsNetworkRegFailCause(usCause))
    {
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, usCause);

        /* ����DPLMN NPLMN�б� */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

            NAS_MMC_LogDplmnNplmnList();
        }
    }

    return;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsRegFailCauseAbnormalCause
 ��������  : EPS OtherCause�Ĵ���
 �������  : VOS_UINT16                          usCause,
              VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��5��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
                  1)  attemptCount < MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT
                  2)  attemptCount >= MaxCountʱ������NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION

  2.��    ��   : 2012��1��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������.
               1): ��UE��������ע���ԭ��ֵ(��ע�ᱻ��causeΪ260),��ʱ������
                   OnPlmn/PlmnList��,����Ҫ���п�ѡ�������򷵻�Ϊ
                   NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON

               2):�������³����Ŀ���:�ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,
               �ҵ�ǰPLMN����EPlmn�б������Ҫ���ؿ�ѡ���������ԡ�
  3.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsRegFailCauseAbnormalCause(
    VOS_UINT16                          usCause,
    VOS_UINT32                          ulAttemptCnt
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPrioAdditionalAction;

    if (ulAttemptCnt < NAS_MML_MAX_PS_REG_FAIL_CNT)
    {
        /* AttemptCounterδ�ﵽ�������Ĵ��� */
        NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(&enAction);
    }
    else
    {
        /* ɾ��EPLMN */
        NAS_MMC_DeleteEPlmnList();

        /* ���·���״̬ */

        /* ֪ͨTAF��ǰ�ķ���״̬ */

        enAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

        enPrioAdditionalAction = NAS_MMC_GetCsAdditionalAction();
        enPrioAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enAction,enPrioAdditionalAction);
        if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enPrioAdditionalAction))
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        else
        {
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_SEARCHING);
        }

        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

        if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
        {
            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_SPEC_PLMN_SELECTION);
        }
    }

    return enAction;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes
 ��������  : EPSע��ʧ��Attemptδ�ﵽ�������Ĵ���Ĵ���
 �������  : ��
 �������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsRegFailAttemptCouterLessThanMaxTimes(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo        = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                          ulInEplmnListFlag;
    VOS_UINT32                          ulUserSpecPlmnFlag;

    /* �жϵ�ǰ�����Ƿ����û�ָ�������� */
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(),
                                                &(pstUserSpecPlmn->stPlmnId));

    /* �жϵ�ǰ�����Ƿ���EPlmn�б��� */
    pstEplmnInfo       = NAS_MML_GetEquPlmnList();

    ulInEplmnListFlag  = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                              pstEplmnInfo->ucEquPlmnNum,
                                              pstEplmnInfo->astEquPlmnAddr);

    /* �ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,�ҵ�ǰPLMN����EPlmn�б��
       ����Ϊ��ǰplmn��NOT ALLOWED����Ҫ�������� */
    if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
      && (VOS_FALSE                          == ulUserSpecPlmnFlag)
      && (VOS_FALSE                          == ulInEplmnListFlag) )
    {
        *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
        return ;
    }
    /* ��GU����һ��,ͨ���жϷ���״̬�������Ƿ����ע��״̬�ͷ���״̬��*/
    if (NAS_MMC_NORMAL_SERVICE != NAS_MMC_GetCurrPsService())
    {
        /*MMC���յ�LMMģ��ע����(EPS ONLY),δ�ﵽ�������Ĵ��� ����PS��ע��״̬Ϊ0�����ϱ�����״̬2*/
        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
    }

    /* ����mmc�����ȴ�ע���� */
    *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsAttachRegFail
 ��������  : Epsע�ᱻ�ܵĴ���
 �������  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����
                  ����������NAS_MMC_ProcEpsRegFail����ΪNAS_MMC_ProcEpsAttachRegFail
                  ����ATTACH��ע��ԭ��ֵ����д���
  3.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  4.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
  5.��    ��   : 2013��8��15��
    ��    ��   : l00208543
    �޸�����   : ������ܾ�ԭ��ֵ�����ϱ�
  6.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsAttachRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    VOS_UINT32                                              ulAttemptCnt;

    /* ����ע������Ϣ */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstLmmAttachIndMsg);

    /* ��LMM��ע��ʧ��ԭ��ֵת��ΪMM��ʽ��ԭ��ֵ */
    NAS_MMC_ConverLmmAttachRsltToMMLCause(pstLmmAttachIndMsg, &enRegRsltCause);

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, enRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_REG_ATTACH_FAIL);

    ulTblSize = sizeof(gastMmcProcEpsAttachRegFailCause)/sizeof(gastMmcProcEpsAttachRegFailCause[0]);

    /*��Epsע��ԭ���gastMmcProcEpsRegFailCause�У����Ҷ�Ӧ�Ĵ�����*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enRegRsltCause == gastMmcProcEpsAttachRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcEpsAttachRegFailCause[i].pRegFailProcFunc;

            break;
        }

    }

    /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();

    }
    /*û���ҵ�ʱ������PS Other Cause����*/
    else
    {
        /* ȡ��Attempt Counter��ֵ */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);
        enAction = NAS_MMC_ProcEpsRegFailCauseAbnormalCause(enRegRsltCause, ulAttemptCnt);
    }


    if (VOS_TRUE == NAS_MML_IsNetworkRegFailCause(enRegRsltCause))
    {
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, enRegRsltCause);
    }
    return enAction;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsTauRegFail
 ��������  : Epsע�ᱻ�ܵĴ���
 �������  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : ��������
                  DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����
                  ����������NAS_MMC_ProcEpsRegFail����ΪNAS_MMC_ProcEpsTauRegFail
                  ����ATTACH��ע��ԭ��ֵ����д���
  2.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  3.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
  4.��    ��   : 2013��8��15��
    ��    ��   : l00208543
    �޸�����   : ������ܾ�ԭ��ֵ�����ϱ�
  5.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcEpsTauRegFail(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8    enRegRsltType,
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR                          pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAction;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    VOS_UINT32                                              ulAttemptCnt;

    /* ����ע������Ϣ */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstLmmTauIndMsg);
    NAS_MMC_ConverTauResultToMMLCause(pstLmmTauIndMsg, &enRegRsltCause);

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, enRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_REG_TAU_FAIL);

    ulTblSize = sizeof(gastMmcProcEpsTauRegFailCause)/sizeof(gastMmcProcEpsTauRegFailCause[0]);

    /*��Epsע��ԭ���gastMmcProcEpsRegFailCause�У����Ҷ�Ӧ�Ĵ�����*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enRegRsltCause == gastMmcProcEpsTauRegFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcEpsTauRegFailCause[i].pRegFailProcFunc;

            break;
        }

    }

    /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();

    }
    /*û���ҵ�ʱ������EPS Abnormal Cause����*/
    else
    {
        /* ȡ��Attempt Counter��ֵ */
        ulAttemptCnt = NAS_MMC_GetRegRsltAttemptCounter(enRegRsltType);
        enAction     = NAS_MMC_ProcEpsRegFailCauseAbnormalCause(enRegRsltCause, ulAttemptCnt);
    }

    if (VOS_TRUE == NAS_MML_IsNetworkRegFailCause(enRegRsltCause))
    {
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, enRegRsltCause);
    }

    return enAction;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEpsDetachCause
 ��������  : Eps detach���ܵĴ���
 �������  : enRegRsltType:ע��������
              pstDetachMsg: detach��Ϣ
 �������  : penCsAddition
             penPsAddition
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��4��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : ����ע��ST�޸�

  3.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEpsDetachCause(
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType,
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulTblSize;
    NAS_MMC_PROC_EPS_DETACH_CAUSE_FUNC_PTR                  pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;

    /* ����ע������Ϣ */
    NAS_MMC_SaveRegRsltCtx(enRegRsltType, pstDetachMsg);

    /* ����CAUSEֵ��OTHER CAUSE����һ�� */
    if ( VOS_FALSE == pstDetachMsg->bitOpCnCause )
    {
        enRegRsltCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    }
    else
    {
        NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstDetachMsg->ucCnCause,
                                                &enRegRsltCause);
    }

    ulTblSize           = sizeof(gastMmcProcEpsDetachCause)/sizeof(gastMmcProcEpsDetachCause[0]);

    /*��Epsע��ԭ���gastMmcProcEpsDetachCause�У����Ҷ�Ӧ�Ĵ�����*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enRegRsltCause == gastMmcProcEpsDetachCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcEpsDetachCause[i].pEpsDetachCauseProcFunc;

            break;
        }
    }

    /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        pRegFailProcFunc(penCsAddition, penPsAddition);
    }
    else
    {
        NAS_MMC_ProcEpsDetachCauseAbnormalCause(penCsAddition, penPsAddition);
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmDetachInd
 ��������  : ����LMM DETACH��Ϣ
 �������  : pstDetachMsg
 �������  : penCsAddition CS��ĺ�������
             penPsAddition PS��ĺ�������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��26��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע���޸�

  3.��    ��   : 2011��11��19��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע��ST�޸�

  4.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570:MMCδ����LMM��ATTACH/TAU/SERVICE/DETACH��EPLMN
                  ��Ϣ;֪ͨMM/GMM����Ϣδ����V7R1_PHASEIV�ĵ��ú���
  5.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ȥע���������Լ�ע����Ϣ���ݸ�����ȥע����
                  ��������չȥע���������Ĵ���������
  6.��    ��   : 2012��05��28��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  7.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�DTS2012090401249
  8.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  9.��    ��   : 2013��12��14��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ

 10.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                     mmc�յ�����ȥע��,����״̬��ע��״̬�Ĵ���
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmDetachInd(
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    MMC_LMM_MT_DETACH_TYPE_ENUM_UINT32                      enCnReqType;

    enCnReqType         = MMC_LMM_MT_DETACH_TYPE_BUTT;

   *penCsAddition       = NAS_MMC_ADDITIONAL_ACTION_BUTT;
   *penPsAddition       = NAS_MMC_ADDITIONAL_ACTION_BUTT;

   /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-17, begin */
   /* MMC_LMM_DETACH_LOCAL��Ԥ��������ɣ�����ɾ�� */
   /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-17, end */


    /* ������Ӧ��detach���OP��ر� */
    if ( VOS_TRUE == pstDetachMsg->bitOpCnReqType)
    {
        enCnReqType = pstDetachMsg->ulCnReqType;
    }

    /* ���ഥ����DETACH���̣�ͨ��DETACH������MMC_LMM_DETACH_MT֪ͨMMC��
    ��Я����Ӧ������DETACH�������ͺ�ԭ��ֵ */
    switch (enCnReqType)
    {
        case MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED:

            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_LTE_NW_DETACH);

            NAS_MMC_ProcEpsDetachCause(LMM_MMC_DETACH_IND, pstDetachMsg,
                                       penCsAddition, penPsAddition);

            /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, begin */
            /* �������PDN���ӱ�־,�ݲ���֪ͨEPLMN��Ϊ��״̬�յ�detach�����ʱ����Ҫ֪ͨEPLMN */
            NAS_MML_SetEmcPdpStatusFlg(VOS_FALSE);

            /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, end */


            /* ��GMM��MMת��ע������Ϣ */
            NAS_MMC_SndMmLmmMtDetachInd(pstDetachMsg);

            NAS_MMC_SndGmmLmmMtDetachInd(pstDetachMsg);

            break;

        case MMC_LMM_MT_DET_REATTACH_REQUIRED:

            *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT;

            NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);

            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_LTE_NW_DETACH);
            NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_LIMITED_SERVICE);

            /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, begin */
            /* �������PDN���ӱ�־,�ݲ���֪ͨEPLMN��Ϊ��״̬�յ�detach�����ʱ����Ҫ֪ͨEPLMN */
            NAS_MML_SetEmcPdpStatusFlg(VOS_FALSE);
            /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, end */

            /* ��GMM��MMת��ע������Ϣ */
            NAS_MMC_SndMmLmmMtDetachInd(pstDetachMsg);

            NAS_MMC_SndGmmLmmMtDetachInd(pstDetachMsg);

            break;
        case MMC_LMM_MT_DET_IMSI:

            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_LTE_NW_DETACH);

            /* ��MMת��ע������Ϣ */
            NAS_MMC_SndMmLmmMtDetachInd(pstDetachMsg);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

            /*mmc�յ�CS�������ȥע��,�ϱ�ע��״̬�ͷ���״̬*/
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmDetachInd:Unexpected detach cn req type!");
            break;
    }


    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmServiceRsltInd
 ��������  : ����LMM��service result IND��Ϣ
 �������  : pstSerRsltMsg LMM��service result ��Ϣ
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��26��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע���޸�
  3.��    ��   : 2011��11��30��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:disable/enable ����
  4.��    ��   : 2012��3��5��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB����:����LMM �ϱ���service����ı���
  5.��    ��   : 2013��01��11��
    ��    ��   : l00167671
    �޸�����   : DTS2013011107287,L�½�������SR����18��������ʧ�ܣ�һֱ���ܷ���
  6.��    ��   : 2015��1��6��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  7.��    ��   : 2015��4��22��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcLmmServiceRsltInd(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstSerRsltMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    NAS_MMC_PROC_REG_FAIL_FUNC_PTR      pRegFailProcFunc = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction;

    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;

    /* LMM��SERVICE���̽��ͨ����ԭ��֪ͨMMC���ṹ�е�bit������ʾ�����Ƿ���Ч��
     SERVICE���̳ɹ�������֪ͨMMC��
     SERVICE���̱�����ܾ���ͨ��SERVICE�����MMC_LMM_SERVICE_RSLT_FAILURE֪ͨMMC����Я����Ӧ��ԭ��ֵ��
     ���UE����EXTENDED SERVICE���̣���Я��SERVICE���͡�
     ע��SERIVE������ʱ��ʹ�� */

    /* ����LMM�ϱ���SERVICE�����Ϣ */
    NAS_MMC_SaveRegRsltCtx(LMM_MMC_SERVICE_RESULT_IND, pstSerRsltMsg);

    ulTblSize = sizeof(gastMmcProcEpsServiceRequestFailCause)/sizeof(gastMmcProcEpsServiceRequestFailCause[0]);
    NAS_MMC_ConverLmmServiceRsltToMMLCause(pstSerRsltMsg,&enRegRsltCause);

    /* ֪ͨMM/GMM */
    NAS_MMC_SndMmLmmSerResultnd(pstSerRsltMsg);
    NAS_MMC_SndGmmLmmSerResultnd(pstSerRsltMsg);

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_SERVICE_REQ_FAIL);

    /*��Epsע��ԭ���gastMmcProcEpsRegFailCause�У����Ҷ�Ӧ�Ĵ�����*/
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (enRegRsltCause == gastMmcProcEpsServiceRequestFailCause[i].enRegCause)
        {
            pRegFailProcFunc = gastMmcProcEpsServiceRequestFailCause[i].pRegFailProcFunc;

            break;
        }

    }

    /*�ҵ��󣬵��ö�Ӧ�Ĵ���,�����ض�Ӧ�ĺ�������ʱ*/
    if (VOS_NULL_PTR != pRegFailProcFunc)
    {
        enAction = pRegFailProcFunc();
    }
    else
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        enRegRsltCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    }

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_ServiceRsltFail(enRegRsltCause, pstSerRsltMsg->ucIsReachMaxTimes))
    {
        /* ��ҪDisable Lȫ�ֱ��� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER, NAS_MML_GetCsPsMode1EnableLteTimerLen());

        PS_MEM_CPY(&stPlmnWithRat.stPlmnId, NAS_MML_GetCurrCampPlmnId(), sizeof(stPlmnWithRat.stPlmnId));
        stPlmnWithRat.enRat = NAS_MML_GetCurrNetRatType();

        if (VOS_TRUE == NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
        {
            NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(&stPlmnWithRat,
                                                          NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(&stPlmnWithRat),
                                                          MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }

        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
    }

    if( VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist() )
    {
        enAction = NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION ;
    }

    return enAction;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc
 ��������  : Lmm combined tau EPS�ɹ�ע��,CSע��ʧ�ܵĴ�����
 �������  : pstLmmTauIndMsg  - LMM_MMC_TAU_RESULT_IND_STRU��Ϣ���׵�ַ
             enCsRegRsltCause - cs�򱻾�ԭ��ֵ
 �������  : penCsAddition    - CS��ĺ�������
             penPsAddition    - PS��ĺ�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��3��5��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB����:����ע�����ı���
  3.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:������ָ������ע��ɹ����������ע��ɹ�ʱ��Ҳ��Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
  4.��    ��   : 2013��8��15��
    ��    ��   : l00208543
    �޸�����   : �յ�����ľܾ�ԭ��ֵ����������ϱ�
  5.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
  6.��    ��   : 2015��4��18��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnInfo;

    NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    /* AT^REJINFO�����ϱ�����REJINFO�ϱ���MSCC */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_FALSE, enCsRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

    /* eps��ע��ɹ���cs��ע��ʧ�� */
    *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

    /* ע��ɹ�����ATTACH_IND��Ϣ�в���LAIʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ */
    NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, VOS_FALSE);

    /* ע��ɹ�ʱ�����GEO PLMN���´�������ʱ������ֱ����RPLMN */
    NAS_MMC_InitGeoPlmn();

    /* ����EPLMN,����ע��ɹ���EPS only�ɹ���������ܴ�EPLMN */
    if ( VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
    {
        ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
        pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

        /* ��LMM��PLMN ID��ʽת��ΪGU�ĸ�ʽ */
        NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));
        NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnInfo.astEquPlmnAddr);

        NAS_MMC_WriteEplmnNvim();
    }

    NAS_MMC_UpdateGURegRlstRPlmnIdInNV();

    NAS_MMC_ProcCombinedEpsRegOnlyEpsSucc(enCsRegRsltCause, pstLmmTauIndMsg->ulAttemptCount,
                                          penCsAddition);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltCsEpsSucc
 ��������  : Lmm combined tau EPS��cs�����ཻ���ɹ�ע�����Ĵ�����
 �������  : pstLmmTauIndMsg - LMM_MMC_TAU_RESULT_IND_STRU��Ϣ���׵�ַ
 �������  : penCsAddition CS��ĺ�������
             penPsAddition PS��ĺ�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��3��5��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB����:����ע�����ı���
  3.��    ��   : 2012��6��2��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,����TAU�ɹ�ʱ����ҪDisable L
  4.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
  5.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  6.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:������ָ������ע��ɹ����������ע��ɹ�ʱ��Ҳ��Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
  7.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  8.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  9.��    ��   : 2013��12��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
 10.��    ��   : 2014��7��14��
    ��    ��   : b00269685
    �޸�����   : ���������Ż���Ŀ�޸�
 11.��    ��   : 2015��3��23��
    ��    ��   : b00269685
    �޸�����   : �ȸ���EPLMN�ٸ���ע��״̬
 12.��    ��   : 2015��4��18��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
 13.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸ģ�
                 ����EMM��COMBINED TAU�ɹ�������PS��ע��״̬���ϱ�
 14.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltCsEpsSucc(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnInfo;

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

     *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
     *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

     /* ����ע��������ע����Ϣ�� */
     NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);
     NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_NULL);

    /* ����EPLMN,����ע��ɹ���EPS only�ɹ���������ܴ�EPLMN */
    if ( VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
    {
        ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
        pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

        /* ��LMM��PLMN ID��ʽת��ΪGU�ĸ�ʽ */
        NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));
        NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnInfo.astEquPlmnAddr);

        NAS_MMC_WriteEplmnNvim();
    }

    /* ����DPLMN NPLMN�б� */
    if (VOS_TRUE == NAS_MMC_IsRoam())
    {
        NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
        NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
        NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

        NAS_MMC_LogDplmnNplmnList();
    }

    /* ע��ɹ�ʱ�����GEO PLMN���´�������ʱ������ֱ����RPLMN */
    NAS_MMC_InitGeoPlmn();


     /* TAU�ɹ����Ҵ�LAIʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ */
     if (VOS_TRUE == pstLmmTauIndMsg->bitOpLai)
     {
         NAS_MMC_DelForbInfo_LmmAttRsltSucc(&(pstLmmTauIndMsg->stLai), VOS_FALSE);
     }
     else
     {
         /* TAU�ɹ����Ҳ���LAIʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ */
         NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, VOS_FALSE);
     }


    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
    NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltCsEpsSucc: Update Reg state and Service state");
    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);
    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, begin */
    *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, end */


    NAS_MMC_UpdateGURegRlstRPlmnIdInNV();

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedAttachInd_AttRsltCsEpsSucc
 ��������  : Lmm combined attach EPS��cs�����ཻ���ɹ�ע�����Ĵ�����
 �������  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : penCsAddition CS��ĺ�������
             penPsAddition PS��ĺ�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��3��5��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB����:����ע�����ı���
  3.��    ��   : 2012��6��1��
    ��    ��   : s00217060
    �޸�����   : ����:CS/PS mode 1����Attach�ɹ�ʱ����ҪDisable L
                  CsAdditionΪNAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
  4.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
  5.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  6.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:������ָ������ע��ɹ����������ע��ɹ�ʱ��Ҳ��Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
  7.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  8.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  9.��    ��   : 2013��12��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
  10.��    ��   : 2014��11��3��
     ��    ��   : z00161729
     �޸�����   : ��������������Ŀ�޸�
  11.��    ��   : 2015��3��23��
     ��    ��   : b00269685
     �޸�����   : ��дEPLMN�ٸ���ע��״̬
  12.��    ��   : 2015��4��18��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
 13.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 ����EMM��COMBINED ATTACH�ɹ�������PS��ע��״̬���ϱ�
 14.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltCsEpsSucc(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnInfo;

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

    *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;


    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-10, begin */

    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-10, end */

    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpLai)
    {
        /* ע��ɹ�����ATTACH_IND��Ϣ�д�LAIʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(&(pstLmmAttachIndMsg->stLai), NAS_MMC_IsEpsEmergencyAttachType(pstLmmAttachIndMsg->ulReqType));
    }
    else
    {
        /* ע��ɹ�����ATTACH_IND��Ϣ�в���LAIʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, NAS_MMC_IsEpsEmergencyAttachType(pstLmmAttachIndMsg->ulReqType));
    }

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, begin */
    *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, end */


    /* ����EPLMN������ע��ɹ���EPS only�ɹ���������ܴ�EPLMN */
    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
    {
        ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
        pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

        /* ��LMM��PLMN ID��ʽת��ΪGU�ĸ�ʽ */
        NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));
        NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnInfo.astEquPlmnAddr);

        NAS_MMC_WriteEplmnNvim();
    }

    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
    NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmCombinedAttachInd_AttRsltCsEpsSucc: Update Reg state and Service state");
    NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);
    /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */


    /* ����ע��������ע����Ϣ�� */
    NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);
    NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_NULL);

    /* ����DPLMN NPLMN�б� */
    if (VOS_TRUE == NAS_MMC_IsRoam())
    {
        NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
        NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_PS_CS, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
        NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

        NAS_MMC_LogDplmnNplmnList();
    }

    /* ע��ɹ�ʱ�����GEO PLMN���´�������ʱ������ֱ����RPLMN */
    NAS_MMC_InitGeoPlmn();

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */


    NAS_MMC_UpdateGURegRlstRPlmnIdInNV();
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc
 ��������  : Lmm combined attach EPS�ɹ�ע��,CSע��ʧ�ܵĴ�����
 �������  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
             enCsRegRsltCause -  cs�򱻾�ԭ��ֵ
 �������  : penCsAddition    - CS��ĺ�������
             penPsAddition    - PS��ĺ�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 phase IV�����ɺ���
  2.��    ��   : 2012��3��5��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB����:����ע�����ı���
  3.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:������ָ������ע��ɹ����������ע��ɹ�ʱ��Ҳ��Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
  4.��    ��   : 2013��8��15��
    ��    ��   : l00208543
    �޸�����   : �յ�����ľܾ�ԭ��ֵ����������ϱ�
  5.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
  6.��    ��   : 2015��4��18��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnInfo;

    NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    /* AT^REJINFO�����ϱ�����REJINFO�ϱ���MSCC */
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
    NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_FALSE, enCsRegRsltCause);
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

    /* EPS��ע��ɹ���cs��ע��ʧ�� */
    *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

    /* ע��ɹ�����ATTACH_IND��Ϣ�в���LAIʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ */
    NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, NAS_MMC_IsEpsEmergencyAttachType(pstLmmAttachIndMsg->ulReqType));

    /* ע��ɹ�ʱ�����GEO PLMN���´�������ʱ������ֱ����RPLMN */
    NAS_MMC_InitGeoPlmn();

    /* ����EPLMN������ע��ɹ���EPS only�ɹ���������ܴ�EPLMN */
    if ( VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
    {
        ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
        pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

        /* ��LMM��PLMN ID��ʽת��ΪGU�ĸ�ʽ */
        NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));
        NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnInfo.astEquPlmnAddr);

        NAS_MMC_WriteEplmnNvim();
    }

    NAS_MMC_UpdateGURegRlstRPlmnIdInNV();

    NAS_MMC_ProcCombinedEpsRegOnlyEpsSucc(enCsRegRsltCause, pstLmmAttachIndMsg->ulAttemptCount,
                                          penCsAddition);

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    return;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc
 ��������  : Lmm combined attach EPS��CS�ɹ�ע��Ĵ�����
 �������  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
             enCsRegRsltCause -  cs�򱻾�ԭ��ֵ
 �������  : penCsAddition    - CS��ĺ�������
             penPsAddition    - PS��ĺ�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
  3.��    ��   : 2012��6��8��
    ��    ��   : l00130025
    �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨAPS/CDS��Ϣ���޷�����
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
  7.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnRslt)
    {
        if (MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI == pstLmmAttachIndMsg->ulCnRslt)
        {
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltCsEpsSucc(pstLmmAttachIndMsg,
                          penCsAddition, penPsAddition);
        }
        else if (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == pstLmmAttachIndMsg->ulCnRslt)
        {
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(pstLmmAttachIndMsg,enCsRegRsltCause,
                          penCsAddition, penPsAddition);

        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc:Unexpected cn result!");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc: Unexpected Proc, ATTACH SUCC but bitOpCnRslt set to FALSE");
        /* ������ע��ɹ��ϱ��������񷵻� */
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc: Update Reg state and Service state");
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);
        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc
 ��������  : Lmm TAU result���ΪMMC_LMM_TAU_RSLT_SUCCESS�Ĵ�����
 �������  : ID_LMM_MMC_TAU_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��07��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
  3.��    ��   : 2012��6��8��
    ��    ��   : l00130025
    �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨAPS/CDS��Ϣ���޷�����
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  6.��    ��   : 2013��3��30��
    ��    ��   : w00176964
    �޸�����   : DTS2013030802929,������RAU��Ҫ֪ͨLMM
  7.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
  8.��    ��   : 2015��05��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
  9.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    if (VOS_TRUE == pstLmmTauIndMsg->bitOpCnRst)
    {
        /* CS+PS��������TAUʱ,�����Ƿ�Я��CS CAUSEֵ,����Ϊ����ע��ɹ� */
        if ((MMC_LMM_COMBINED_TA_LA_UPDATED == pstLmmTauIndMsg->ulCnRst)
         || (MMC_LMM_COMBINED_TA_LA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst)
         || (MMC_LMM_CS_PS_PERIODIC_UPDATING == pstLmmTauIndMsg->ulReqType))
        {
            /* �����ཻ��EPS��CS��ע��ɹ� */
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltCsEpsSucc(pstLmmTauIndMsg,
                          penCsAddition, penPsAddition);
        }
        else if ((MMC_LMM_TA_UPDATED == pstLmmTauIndMsg->ulCnRst)
              || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst))
        {
            /* �����ཻ��EPS�ɹ�CSʧ�ܣ���ԭ��ֵΪЭ��24301 5.5.3.3.4.3�½����� */
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc(pstLmmTauIndMsg,enCsRegRsltCause,
                          penCsAddition, penPsAddition);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc:Unexpected cn result!");
        }
    }
    else
    {
        /* ������ע��ɹ��ϱ��������񷵻� */
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-7, begin */
        /* LTE TAU�����̣��ñ�־λ */
        NAS_MMC_SetLteUnrealRegProcFlg(VOS_TRUE);
        NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc: Update Reg state and Service state");
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);
        /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-7, end */

         /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
         NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
         /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }

    if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());


    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedTauResult
 ��������  : Lmm TAU result�Ĵ�����
 �������  : pstLmmTauIndMsg          -  ID_LMM_MMC_TAU_RESULT_IND��Ϣ����
             enCsRegRsltCause - cs�򱻾�ԭ��ֵ
 �������  : penPsRegAdditionalAction - �յ�ע��tau�����Э��Ҫ���ps���additional��������
             penCsRegAdditionalAction - �յ�ע��tau�����Э��Ҫ���cs���additional��������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��07��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��7��
    ��    ��   : w00166186
    �޸�����   : DTS20120050302236:�ֶ�����ָ���������ڽ�ֹ�б��У�ע��ɹ���
                 û����LMM���͵�ЧPLMN
  3.��    ��   : 2012��5��10��
    ��    ��   : l65478
    �޸�����   : DTS2012050500988:CSע��ɹ�ʱ,����ɾ��forbid PLMN for GPRS��Ϣ
  4.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCombinedTauResult(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsRegAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsRegAdditionalAction
)
{
    switch (pstLmmTauIndMsg->ulTauRst)
{
    case MMC_LMM_TAU_RSLT_SUCCESS:
        NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc(pstLmmTauIndMsg,
                   enCsRegRsltCause, penCsRegAdditionalAction, penPsRegAdditionalAction);

        break;

    case MMC_LMM_TAU_RSLT_FAILURE:
        if (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt)
        {
            if (NAS_MMC_FSM_L1_MAIN == NAS_MMC_GetCurrFsmId())
            {
                /* LNAS��������ע�᳢������-��������ȴ��� */
                NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
            }

            *penPsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
            *penCsRegAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;


            /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
            NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
            /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
        }
        else
        {
            /* EPS��CSע���ʧ�� */
            NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          penPsRegAdditionalAction, penCsRegAdditionalAction);
        }
        break;

    case MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
    case MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
    case MMC_LMM_TAU_RSLT_T3402_RUNNING:
    case MMC_LMM_TAU_RSLT_TIMER_EXP:
    case MMC_LMM_TAU_RSLT_ACCESS_BARED:
    case MMC_LMM_TAU_RSLT_FORBID_PLMN:
    case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
    case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
    case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
    case MMC_LMM_TAU_RSLT_AUTH_REJ:
        /* EPS��CSע���ʧ�� */
        NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                      penPsRegAdditionalAction, penCsRegAdditionalAction);
        break;

    case MMC_LMM_TAU_RSLT_CN_REJ:
        if ((VOS_TRUE == pstLmmTauIndMsg->bitOpCnRst)
         && ((MMC_LMM_TA_UPDATED == pstLmmTauIndMsg->ulCnRst)
          || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst)))
        {
            /* ��TAU��������Ϊ���ϣ�������Ӧ��TAU�������ΪTA UPDATED��
               ��ԭ��ֵ��ΪЭ��24301 5.5.3.3.4.3�½����л���û��Я��ԭ��ֵ��
               ��LMMͨ��TAU�����MMC_LMM_TAU_RSLT_CN_REJ֪ͨMMC����Я����Ӧ
               ��TAU�������͡�������Ӧ��TAU������͡�ԭ��ֵ����Я�������ԭ
               ����tau attempt counterֵ */
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc(pstLmmTauIndMsg,enCsRegRsltCause,
                              penCsRegAdditionalAction, penPsRegAdditionalAction);

        }
        else
        {
            /* EPS��CSע���ʧ�� */
            NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          penPsRegAdditionalAction, penCsRegAdditionalAction);
        }
        break;

    case MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC:
        NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          penPsRegAdditionalAction, penCsRegAdditionalAction);
        break;

    default:

        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedTauResult:Unexpected tau result!");
        *penPsRegAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();
        *penCsRegAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
        break;
    }

    return;
}

#endif
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAdditionalActionPrioValue
 ��������  : ��ȡAdditonalAction��Ӧ�����ȼ�
 �������  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction,
             VOS_UINT8                          *pucPrioValue
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��22��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_GetAdditionalActionPrioValue(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAction,
    VOS_UINT8                           *pucPrioValue
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(gastAdditionalActionPrioArr)/sizeof(gastAdditionalActionPrioArr[0]);

    for  ( i = 0 ; i < ulTblSize ; i++ )
    {
        if (enAction == gastAdditionalActionPrioArr[i].enAdditionalAction)
        {
           *pucPrioValue = gastAdditionalActionPrioArr[i].ucPriority;
            return;
        }
    }

    /* δ���ҵ��򷵻�BUTT��������ȼ� */
    *pucPrioValue = gastAdditionalActionPrioArr[NAS_MMC_ADDITIONAL_ACTION_BUTT].ucPriority;

}
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPrioAddtionalAction
 ��������  : ��ȡ��ǰ���ȵ�AdditonalAction
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��22��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  NAS_MMC_GetPrioAddtionalAction(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAdditionalAction,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAdditionalAction
)
{
    VOS_UINT8                           ucCsPriority;
    VOS_UINT8                           ucPsPriority;


    NAS_MMC_GetAdditionalActionPrioValue(enCsAdditionalAction, &ucCsPriority);
    NAS_MMC_GetAdditionalActionPrioValue(enPsAdditionalAction, &ucPsPriority);

    /* ȨֵԽС�����ȼ�Խ�� */
    if (ucCsPriority < ucPsPriority)
    {
        return enCsAdditionalAction;
    }
    else
    {
        return enPsAdditionalAction;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsAdditionalActionTrigerPlmnSrch
 ��������  : AdditionalAction�Ƿ�ᴥ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ��������
             VOS_FALSE: ����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAdditionalActionTrigerPlmnSrch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction
)
{
    switch (enAdditionalAction)
    {
        case NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL:
        case NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION :
        case NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL :
        case NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN :
        case NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION:
            return VOS_TRUE;

        default:

            return VOS_FALSE;
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPsAdditionalAction
 ��������  : ��ȡPS��AdditionalAction
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8,PS��AdditionalAction
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsAdditionalAction(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;

    /* ��ȡ��ǰ״̬��ID������״̬�����ò�ͬ״̬���Ļ�ȡPS AdditionalAction���� */
    enFsmId                = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG1(WUEPS_PID_MMC, "NAS_MMC_GetPsAdditionalAction,ERROR:FsmId Error", enFsmId);

        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    if (NAS_MMC_FSM_L1_MAIN == enFsmId)
    {
        return NAS_MMC_GetPsRegAdditionalAction_L1Main();
    }
    else if (NAS_MMC_FSM_PLMN_LIST == enFsmId)
    {
        return NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    }
    else if (NAS_MMC_FSM_BG_PLMN_SEARCH == enFsmId)
    {
        return NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch();
    }
    else if (NAS_MMC_FSM_PLMN_SELECTION == enFsmId)
    {
        return NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();
    }
    else
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_GetPsAdditionalAction,WARNING:This Fsm not have Ps Additon", enFsmId);
    }

    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsAdditionalAction
 ��������  : ��ȡCS��AdditionalAction
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8,CS��AdditionalAction
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsAdditionalAction(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32                              enFsmId;

    /* ��ȡ��ǰ״̬��ID������״̬�����ò�ͬ״̬���Ļ�ȡCS AdditionalAction���� */
    enFsmId                = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enFsmId)
    {
        NAS_ERROR_LOG1(WUEPS_PID_MMC, "NAS_MMC_GetCsAdditionalAction,ERROR:FsmId Error", enFsmId);

        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    if (NAS_MMC_FSM_L1_MAIN == enFsmId)
    {
        return NAS_MMC_GetCsRegAdditionalAction_L1Main();
    }
    else if (NAS_MMC_FSM_PLMN_LIST == enFsmId)
    {
        return NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    }
    else if (NAS_MMC_FSM_BG_PLMN_SEARCH == enFsmId)
    {
        return NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch();
    }
    else if (NAS_MMC_FSM_PLMN_SELECTION == enFsmId)
    {
        return NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
    }
    else
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_GetCsAdditionalAction,WARNING:This Fsm not have Cs Additon", enFsmId);
    }

    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLmmAttaClRegStatPrioValue
 ��������  : ��ȡ��ǰ���ȵ�lmm attach cl ע��״̬
 �������  : MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachClReqStatus
             VOS_UINT8                          *pucPrioValue
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : wx270776
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetLmmAttaClRegStatPrioValue(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachClReqStatus
)
{

    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;
    VOS_UINT32                          ulPrioValue;

    ulPrioValue = gastLmmAttaClRegStatPrio[MMC_LMM_CL_REG_STATUS_BUTT].ucPriority;

    ulTblSize = sizeof(gastLmmAttaClRegStatPrio)/sizeof(gastLmmAttaClRegStatPrio[0]);

    for  ( i = 0 ; i < ulTblSize ; i++ )
    {
        if (enLmmAttachClReqStatus == gastLmmAttaClRegStatPrio[i].enLmmAttachClReqStatus)
        {
            ulPrioValue = gastLmmAttaClRegStatPrio[i].ucPriority;

            return ulPrioValue;
        }
    }

    return ulPrioValue;
}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLmmCauseToMmCause
 ��������  : ��MM��ע����ת��ΪEMM��ע����,������Ҫ��ȷ����EMM�Ƿ�������
              �ܾ���������ԭ��ܾ�
 �������  : enCnCause:MMע����
 �������  : penProtolCause:Э���й涨�Ľ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_ConvertLmmCauseToMmCause(
    NAS_LMM_CN_CAUSE_ENUM_UINT8          enLmmCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  *penMmCnCause
)
{
    *penMmCnCause = (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)enLmmCause;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause
 ��������  : ��LmmAttach������ע����ת��Ϊ��Ӧ��ps causeֵ��cs causeֵ
 �������  : pstLmmAttachIndMsg - ����attach��Ϣ����
 �������  : penPsRegRsltCause  - ps��ע��ԭ��ֵ
             penCsRegRsltCause  - cs��ע��ԭ��ֵ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 phase IV�޸�
  3.��    ��   : 2012��1��2��
    ��    ��   : w00167002
    �޸�����   : DTS2011102200381:L��ע�ᱻ��#12,LMM��MMC����ATTACH��TAU
                 �еĽ��ΪMMC_LMM_ATT_RSLT_FORBID��MMC�յ��˽�����ս�ֹ����
                 �������������������

*****************************************************************************/
VOS_VOID NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penPsRegRsltCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penCsRegRsltCause
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enPsCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enCsCause;
    MMC_LMM_ATTACH_CN_RSLT_ENUM_UINT32 ulAttachCnRslt;

    enPsCause      = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    enCsCause      = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    ulAttachCnRslt = MMC_LMM_ATT_CN_RSLT_BUTT;

    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnRslt)
    {
        ulAttachCnRslt = pstLmmAttachIndMsg->ulCnRslt;
    }

    switch (pstLmmAttachIndMsg->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:
            if (MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI == ulAttachCnRslt)
            {
                /* ����ע��cs ps���ע��ɹ� */
                enPsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                enCsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                break;
            }
            if (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == ulAttachCnRslt)
            {
                /* ����ע��ps��ע��ɹ���cs��ע��ʧ�� */
                enPsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmAttachIndMsg->ucCnCause, &enCsCause);
                break;
            }

            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause: attach ind cnRslt value is invalid");
            break;

        case MMC_LMM_ATT_RSLT_CN_REJ:
            if (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == ulAttachCnRslt)
            {
                enPsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnCause)
                {
                    NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmAttachIndMsg->ucCnCause, &enCsCause);
                }
                break;
            }

            if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnCause)
            {
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmAttachIndMsg->ucCnCause, &enPsCause);
                enCsCause = enPsCause;
            }
            break;

        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            break;

        case MMC_LMM_ATT_RSLT_TIMER_EXP :
            enPsCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            break;

        case MMC_LMM_ATT_RSLT_AUTH_REJ :
            enPsCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            break;

        case MMC_LMM_ATT_RSLT_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            break;

        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            break;

        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            break;

        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            break;

        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            break;
        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_PS_ATTACH_NOT_ALLOW;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_PS_ATTACH_NOT_ALLOW;
            break;

        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_T3402_RUNNING:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause: attach ind ulAttachRslt invalid");
            break;
    }

    *penPsRegRsltCause = enPsCause;
    *penCsRegRsltCause = enCsCause;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConverLmmCombinedTauRsltToMMLCause
 ��������  : ��Lmmtau������ע����ת��Ϊ��Ӧ��ps causeֵ��cs causeֵ
 �������  : pstLmmTauResultInd - ����tau��Ϣ����
 �������  : penPsRegRsltCause  - psע��ԭ��ֵ
             penCsRegRsltCause  - csע��ԭ��ֵ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 phase IV�޸�
 3.��    ��   : 2012��1��2��
   ��    ��   : w00167002
   �޸�����   : DTS2011102200381:L��ע�ᱻ��#12,LMM��MMC����ATTACH��TAU
                �еĽ��ΪMMC_LMM_ATT_RSLT_FORBID��MMC�յ��˽�����ս�ֹ����
                �������������������
 4.��    ��   : 2012��5��11��
   ��    ��   : w00166186
   �޸�����   : DTS2012051006163:�����ȼ���ָ����VPLMN��ϣ������ɹ�����AT����ʧ�ܡ�

*****************************************************************************/
VOS_VOID NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauResultInd,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penPsRegRsltCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penCsRegRsltCause
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;
    MMC_LMM_TAU_CN_RSLT_ENUM_UINT32     ulTauCnRst;

    enPsCause  = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    enCsCause  = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    ulTauCnRst = MMC_LMM_TAU_CN_RSLT_BUTT;

    if (VOS_TRUE == pstLmmTauResultInd->bitOpCnRst)
    {
        ulTauCnRst = pstLmmTauResultInd->ulCnRst;
    }

    switch (pstLmmTauResultInd->ulTauRst)
    {
        case MMC_LMM_TAU_RSLT_SUCCESS:

            enPsCause = NAS_MML_REG_FAIL_CAUSE_NULL;

            if ( (MMC_LMM_COMBINED_TA_LA_UPDATED == ulTauCnRst)
              || (MMC_LMM_COMBINED_TA_LA_UPDATED_ISR_ACTIVATED == ulTauCnRst))
            {
                /* ����ע��cs ps���ע��ɹ� */
                enCsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                break;
            }

            if (((MMC_LMM_TA_UPDATED == ulTauCnRst)
              || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == ulTauCnRst))
             && (VOS_TRUE == pstLmmTauResultInd->bitOpCnCause) )
            {
                /* ����ע��ps��ע��ɹ���cs��ע��ʧ�� */
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmTauResultInd->ucCnCause, &enCsCause);
                break;
            }

            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_ConverLmmCombinedTauRsltToMMLCause: tau cnRslt value is invalid");
            break;

        case MMC_LMM_TAU_RSLT_CN_REJ:
            if ((MMC_LMM_TA_UPDATED == ulTauCnRst)
             || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == ulTauCnRst))
            {
                enPsCause = NAS_MML_REG_FAIL_CAUSE_NULL;
                if (VOS_TRUE == pstLmmTauResultInd->bitOpCnCause)
                {
                    NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmTauResultInd->ucCnCause, &enCsCause);
                }
                break;
            }

            if (VOS_TRUE == pstLmmTauResultInd->bitOpCnCause)
            {
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmTauResultInd->ucCnCause, &enPsCause);
                enCsCause = enPsCause;
            }
            break;

        case MMC_LMM_TAU_RSLT_ACCESS_BARED:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            break;

        case MMC_LMM_TAU_RSLT_TIMER_EXP :
            enPsCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            break;

        case MMC_LMM_TAU_RSLT_AUTH_REJ :
            enPsCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            break;

        case MMC_LMM_TAU_RSLT_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            break;

        case MMC_LMM_TAU_RSLT_FORBID_PLMN:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            break;

        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            break;

        case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            break;

        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            break;
        case  MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            break;

        case  MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            break;

        case MMC_LMM_TAU_RSLT_T3402_RUNNING:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;
            break;

        case MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC:
            enPsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_ONLY_SUCC;
            enCsCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_ONLY_SUCC;
            break;

        default:
            break;
    }

    *penPsRegRsltCause = enPsCause;
    *penCsRegRsltCause = enCsCause;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConverLmmAttachRsltToMMLCause
 ��������  : ��LmmAttach�Ķ�Ӧ���ת��Ϊ��Ӧ��Causeֵ
 �������  : pstLmmAttachIndMsg
 �������  : penRegRsltCause
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��24��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  3.��    ��   : 2011��12��28��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�����µ�attach result
  4.��    ��   : 2011��12��29��
    ��    ��   : w00167002
    �޸�����   : DTS2011102200381:L��ע�ᱻ��#12,LMM��MMC����TAU
                 �еĽ��ΪMMC_LMM_TAU_RSLT_FORBID_PLMNS��MMC�յ��˽�����ս�ֹ����
                 �������������������
                  �޸�����:��Lģ�������ļ�����ֵת��ΪNAS�ڲ��ļ�����ֵ

  5.��    ��   : 2012��09��27��
    ��    ��   : z00161729
    �޸�����   : DTS2012090303562:����״̬����Lע�����յ�������Ϣ��ȡ��һ������ʧ����״̬�����ַ���Ƿ������������

*****************************************************************************/
VOS_VOID NAS_MMC_ConverLmmAttachRsltToMMLCause(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penRegRsltCause
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enCause;

    enCause  = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;

    switch (pstLmmAttachIndMsg->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:
            enCause = NAS_MML_REG_FAIL_CAUSE_NULL;
            break;

        case MMC_LMM_ATT_RSLT_CN_REJ:

            if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnCause)
            {
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmAttachIndMsg->ucCnCause,
                                                                &enCause);
            }

            break;

        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
            enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            break;

        case MMC_LMM_ATT_RSLT_TIMER_EXP :
            enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            break;

        case MMC_LMM_ATT_RSLT_AUTH_REJ :
            enCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            break;

        case MMC_LMM_ATT_RSLT_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            break;


        /* L�¼����̱���ԭ��ֵ#11���� */
        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            break;

        /* L�¼����̱���ԭ��ֵ#12���� */
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            break;

        /* L�¼����̱���ԭ��ֵ#14���� */
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            break;

        /* L�¼����̱���ԭ��ֵ#13 #15���� */
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            break;

        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
            enCause = NAS_MML_REG_FAIL_CAUSE_PS_ATTACH_NOT_ALLOW;
            break;

        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_ESM_BEAR_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            break;

        case MMC_LMM_ATT_RSLT_T3402_RUNNING:
            enCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;
            break;

        default:
            break;
    }

    *penRegRsltCause = enCause;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConverLmmServiceRsltToMMLCause
 ��������  : ��pstLmmSerRsltIndMsg�Ķ�Ӧ���ת��Ϊ��Ӧ��Causeֵ
 �������  : pstLmmSerRsltIndMsg
 �������  : penRegRsltCause
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��17��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV����:��ȡcauseֵ�ȼ��OP��
  3.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�

*****************************************************************************/
VOS_VOID NAS_MMC_ConverLmmServiceRsltToMMLCause(
    LMM_MMC_SERVICE_RESULT_IND_STRU    *pstLmmSerRsltIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penRegRsltCause
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 enCause;

    enCause  = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;

    switch (pstLmmSerRsltIndMsg->ulServiceRst)
    {
        case MMC_LMM_SERVICE_RSLT_CN_REJ:

            if ( VOS_TRUE == pstLmmSerRsltIndMsg->bitOpCnCause)
            {
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmSerRsltIndMsg->ucCnCause,
                                                                    &enCause);
            }

            break;

        case MMC_LMM_SERVICE_RSLT_ACCESS_BARED:
            enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            break;

        case MMC_LMM_SERVICE_RSLT_AUTH_REJ :
            enCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            break;

        case MMC_LMM_SERVICE_RSLT_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            break;

        case MMC_LMM_SERVICE_RSLT_TIMER_EXP:
            enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;

        default:
            break;
    }

    *penRegRsltCause = enCause;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConverTauResultToMMLCause
 ��������  : ��LmmAttach�Ķ�Ӧ���ת��Ϊ��Ӧ��Causeֵ
 �������  : pstLmmTauIndMsg
 �������  : penRegRsltCause
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��24��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  3.��    ��   : 2011��12��29��
    ��    ��   : w00167002
    �޸�����   : DTS2011102200381:L��ע�ᱻ��#12,LMM��MMC����TAU
                 �еĽ��ΪMMC_LMM_TAU_RSLT_FORBID_PLMNS��MMC�յ��˽�����ս�ֹ����
                 �������������������
                  �޸�����:��Lģ�������ļ�����ֵת��ΪNAS�ڲ��ļ�����ֵ
  4.��    ��   : 2012��7��9��
    ��    ��   : z00161729
    �޸�����  : GUL �������޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ConverTauResultToMMLCause(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penRegRsltCause
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;

    enCause  = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;

    switch (pstLmmTauIndMsg->ulTauRst)
    {
        case MMC_LMM_TAU_RSLT_SUCCESS:
            enCause = NAS_MML_REG_FAIL_CAUSE_NULL;
            break;

        case MMC_LMM_TAU_RSLT_CN_REJ:

            if (VOS_TRUE == pstLmmTauIndMsg->bitOpCnCause)
            {
                NAS_MMC_ConvertLmmCauseToMmCause((VOS_UINT8)pstLmmTauIndMsg->ucCnCause,
                                                                &enCause);
            }

            break;

        case MMC_LMM_TAU_RSLT_ACCESS_BARED:
            enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
            break;

        case MMC_LMM_TAU_RSLT_TIMER_EXP :
            enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;
            break;

        case MMC_LMM_TAU_RSLT_AUTH_REJ :
            enCause = NAS_MML_REG_FAIL_CAUSE_AUTH_REJ;
            break;

        case MMC_LMM_TAU_RSLT_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
            break;


        /* L�¼����̱���ԭ��ֵ#11���� */
        case MMC_LMM_TAU_RSLT_FORBID_PLMN:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
            break;

        /* L�¼����̱���ԭ��ֵ#12���� */
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
            break;

        /* L�¼����̱���ԭ��ֵ#14���� */
        case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
            break;

        /* L�¼����̱���ԭ��ֵ#13 #15���� */
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
            enCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
            break;


        case  MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_MO_DETACH_FAILURE;
            break;

        case  MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
            enCause = NAS_MML_REG_FAIL_CAUSE_MT_DETACH_FAILURE;
            break;

        case MMC_LMM_TAU_RSLT_T3402_RUNNING:
            enCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_FAIL;
            break;


        case MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC:
            enCause = NAS_MML_REG_FAIL_CAUSE_T3402_RUNNING_EPS_ONLY_SUCC;
            break;

        default:
            break;
    }

    *penRegRsltCause = enCause;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLmmAttachReqType
 ��������  : ����EPS OtherCause�Ĵ���
 �������  : VOS_UINT16                          usCause,
             VOS_UINT32                          ulAttemptCnt
 �������  : penPsRegAdditionalAction - �յ�ע������Э��Ҫ���ps���additional��������
             penCsRegAdditionalAction - �յ�ע������Э��Ҫ���cs���additional��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
MMC_LMM_ATTACH_TYPE_ENUM_UINT32 NAS_MMC_ConvertLmmAttachReqType(
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode
)
{
    if ((NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2 == enUeOperationMode)
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 == enUeOperationMode))
    {
        return MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI;
    }
    else if ((NAS_MML_LTE_UE_OPERATION_MODE_PS_2 == enUeOperationMode)
          || (NAS_MML_LTE_UE_OPERATION_MODE_PS_1 == enUeOperationMode))
    {
        return MMC_LMM_ATT_TYPE_EPS_ONLY;
    }
    else
    {
        return MMC_LMM_ATT_TYPE_BUTT;
    }

}



/*******************************************************************************
 �� �� ��  : NAS_MMC_ConvertGmmRegDomainToMmcDomain
 ��������  : ��GMM��ע����ת��ΪMMC�ĸ�ʽ
 �������  : enRegDomain GMM��ע����
 �������  : penMmcRegDomain MMC��ע����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��30��
   ��    ��   : l00130025
   �޸�����   : DTS2012032307791,����LMMע����,CombineRegʱ��Ҫ���ֽ����

*******************************************************************************/
VOS_VOID NAS_MMC_ConvertGmmRegDomainToMmcDomain(
    GMM_MMC_REG_DOMAIN_ENUM_UINT32      enRegDomain,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8      *penMmcRegDomain
)
{
    if (GMM_MMC_REG_DOMAIN_PS_CS == enRegDomain)
    {
        *penMmcRegDomain = NAS_MMC_REG_DOMAIN_PS_CS;
    }
    else
    {
        *penMmcRegDomain =  NAS_MMC_REG_DOMAIN_PS;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableL_CombinedAttRsltFailMaxTimes
 ��������  : ����ע��ʧ����ҪDisable L
 �������  : ��
 �������  : ��
 ����ֵ    : VOS_TRUE   ��ҪDisable L
              VOS_FALSE  ����ҪDisable L
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��02��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegRsltFailMaxTimes()
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    /* ����CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableL_CombinedAttRsltFailCause14GprsNotAllowInThisPlmn
 ��������  : �ж�����ע��ʧ��#14��ҪDisable L
 �������  : ��
 �������  : ��
 ����ֵ    : VOS_TRUE   ��ҪDisable L
             VOS_FALSE  ����ҪDisable L
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedAttRsltFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();

    /* Э��汾С��R11��disable lte */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_FALSE;
    }

    /* ����CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAddForbGprsPlmn_TauRsltFailCause14GprsNotAllowInThisPlmn
 ��������  : L��ע��ʧ�ܱ���#14�ж��Ƿ���Ҫ�����ֹgprs�����б�
 �������  : ��
 �������  : ��
 ����ֵ    : VOS_TRUE - ��Ҫ�����ֹgprs�����б�
             VOS_FALSE- ����Ҫ�����ֹgprs�����б�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddForbGprsPlmn_TauRsltFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    VOS_UINT8                           ucEpsSrvConnStatusFlag;
    NAS_MML_SUIT_PLMN_LIST_STRU        *pstSuitPlmnList = VOS_NULL_PTR;
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;

    ucEpsSrvConnStatusFlag = NAS_MML_GetEpsServiceConnStatusFlg();
    pstSuitPlmnList        = NAS_MML_GetSuitPlmnList();
    pstRegRsltCtx          = NAS_MMC_GetRegRsltCtxAddr();

    /* Э��汾С��R11��Ҫ����VOS_TRUE */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_TRUE;
    }

    /* 24301_CR1528R1_(Rel-11)_C1-124123�������磬����̬����TAU�����ܾ���MMC�����±���PLMN�б�
       ��Ӧ24301 5.5.3.1�½�����:
       In a shared network, if TRACKING AREA UPDATE REJECT is received as a response
    to a tracking area update procedure initiated in EMM-CONNECTED mode, the UE
    need not update forbidden lists.��CR��Э��汾���� */

    /* ����tau���� */
    if ((LMM_MMC_TAU_RESULT_IND == pstRegRsltCtx->enRegRsltType)
     && (pstSuitPlmnList->ucSuitPlmnNum > 1)
     && (VOS_TRUE == ucEpsSrvConnStatusFlag))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDeleteEplmn_CombinedRegRsltFailCause14GprsNotAllowInThisPlmn
 ��������  : L��ע��ʧ�ܱ���#14�ж��Ƿ���Ҫɾ����Чplmn
 �������  : ��
 �������  : ��
 ����ֵ    : VOS_TRUE - ��Ҫɾ��eplmn
             VOS_FALSE- ����Ҫɾ��eplmn
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDeleteEplmn_CombinedRegRsltFailCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode  = NAS_MML_GetLteUeOperationMode();

    /* Э��汾С��R11,����Ҫɾ��eplmn������VOS_FALSE */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_FALSE;
    }

    /* 24301_CR1422R1_(Rel-11)_C1-121612 ��Ӧ24301 5.5.3.3.5��5.5.1.3.5�½�:
         A UE operating in CS/PS mode 1 of operation and supporting A/Gb or Iu mode
      may perform a PLMN selection according to 3GPP TS 23.122 [6].
         A UE operating in CS/PS mode 1 of operation and supporting S1 mode only,
      or operating in CS/PS mode 2 of operation shall delete the list of
      equivalent PLMNs and shall perform a PLMN selection according to 3GPP TS 23.122 [6].
      ��CR��Э��汾���� */
    if (((VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
       && (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 == enLUeMode))
      || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2 == enLUeMode))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDeleteEplmn_EpsDetachCause14GprsNotAllowInThisPlmn
 ��������  : L������detach ind����#14�ж��Ƿ���Ҫɾ����Чplmn
 �������  : ��
 �������  : ��
 ����ֵ    : VOS_TRUE - ��Ҫɾ��eplmn
             VOS_FALSE- ����Ҫɾ��eplmn
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDeleteEplmn_EpsDetachCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    /* 24301_CR1422R1_(Rel-11)_C1-121612 ��Ӧ24301 5.5.2.3.2�½�:
         A UE operating in CS/PS mode 1 of operation and supporting A/Gb or Iu mode
      may perform a PLMN selection according to 3GPP TS 23.122 [6].
         A UE operating in CS/PS mode 1 of operation and supporting S1 mode only,
      or operating in CS/PS mode 2 of operation shall delete the list of
      equivalent PLMNs and shall perform a PLMN selection according to 3GPP TS 23.122 [6].
      ��CR��Э��汾���� */
    return NAS_MMC_IsNeedDeleteEplmn_CombinedRegRsltFailCause14GprsNotAllowInThisPlmn();

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAddForbPlmn_TauRsltFailCause11PlmnNotAllow
 ��������  : L��ע��ʧ�ܱ���#11�ж��Ƿ���Ҫ�����ֹ�����б�
 �������  : ��
 �������  : ��
 ����ֵ    : VOS_TRUE - ��Ҫ�����ֹ�����б�
             VOS_FALSE- ����Ҫ�����ֹ�����б�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddForbPlmn_TauRsltFailCause11PlmnNotAllow(VOS_VOID)
{
    VOS_UINT8                           ucEpsSrvConnStatusFlag;
    NAS_MML_SUIT_PLMN_LIST_STRU        *pstSuitPlmnList = VOS_NULL_PTR;

    ucEpsSrvConnStatusFlag = NAS_MML_GetEpsServiceConnStatusFlg();
    pstSuitPlmnList        = NAS_MML_GetSuitPlmnList();

    /* Э��汾С��R11��Ҫ����VOS_TRUE */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_TRUE;
    }

    /* 24301_CR1528R1_(Rel-11)_C1-124123�������磬����̬����TAU�����ܾ���MMC�����±���PLMN�б�
       ��Ӧ24301 5.5.3.1�½�����:
       In a shared network, if TRACKING AREA UPDATE REJECT is received as a response
    to a tracking area update procedure initiated in EMM-CONNECTED mode, the UE
    need not update forbidden lists. ��CR��Э��汾���� */
    /*pstSuitPlmnList->ucSuitPlmnNum��������1��ʾ���ڹ������� */
    if ((pstSuitPlmnList->ucSuitPlmnNum > 1)
     && (VOS_TRUE == ucEpsSrvConnStatusFlag))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableL_EpsDetachCause14GprsNotAllowInThisPlmn
 ��������  : �ж�����detach ind����#14�Ƿ���ҪDisable L
 �������  : ��
 �������  : ��
 ����ֵ    : VOS_TRUE   ��ҪDisable L
             VOS_FALSE  ����ҪDisable L
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_EpsDetachCause14GprsNotAllowInThisPlmn(VOS_VOID)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();

    /* Э��汾С��R11��disable lte */
    if (NAS_MML_GetLte3gppRelVersion() < NAS_MML_3GPP_REL_R11)
    {
        return VOS_FALSE;
    }

    /* ����CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableL_CombinedRegRsltSucc
 ��������  : �ж�����Attch������TAU�ɹ�ʱ�Ƿ���ҪDisable L
 �������  :
 �������  :
 �� �� ֵ  : VOS_TRUE  ��ҪDisable L
              VOS_FALSE ����ҪDisable L
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��1��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��19��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegRsltSucc()
{

    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(NAS_MML_GetAdditionUpdateRslt()))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_IsNeedDisableL_RegRsltAdditionUpdateRslt
��������  : cs ps mode1,ims not available,ע����additional update result IEָʾ
            "SMS only" or "CS Fallback not preferred" �Ƿ���Ҫdisable lte
�������  : enAdditionUpdateRslt - addition update result��Ϣ
�������  : ��
�� �� ֵ  : VOS_TRUE  - ��ҪDisable L
            VOS_FALSE - ����ҪDisable L
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��4��19��
  ��    ��   : z00161729
  �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdateRslt
)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    VOS_UINT8                                               ucAdditionUpdRsltSupportCsfbFlag;
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg;
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomain;

    enLUeMode                        = NAS_MML_GetLteUeOperationMode();
    ucAdditionUpdRsltSupportCsfbFlag = VOS_TRUE;
    enLteCsServiceCfg                = NAS_MML_GetLteCsServiceCfg();
    enVoiceDomain                    = NAS_MML_GetVoiceDomainPreference();

    /* ����CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MML_GetImsVoiceAvailFlg())
    {
        return VOS_FALSE;
    }

    if ((NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY == enAdditionUpdateRslt)
     || (NAS_MML_ADDITION_UPDATE_RSLT_CSFB_NOT_PREFERRED == enAdditionUpdateRslt))
    {
        ucAdditionUpdRsltSupportCsfbFlag = VOS_FALSE;
    }

    /* Additional Update Result IE��Ϣ��ָʾSMS Only��CSFB Not Preferred
      24301_CR1289R1_(Rel-11)_C1-115106 rev of c1-114768 domain selection
      clarification  CS PS MODE1��IMS voice not availableʱ��
      attach accept��tau accept��Ϣ��Я����Additional update result IEֵΪ
      SMS ONLY��CSFB NOT PREFERREDʱDISABLE LTE����������UE�Ƿ�������CSFB����
      ��Ӧ24301 5.5.1.3.4.2��5.5.3.3.4.2�½�,��CR����Э��汾���� */
    if ((VOS_FALSE == ucAdditionUpdRsltSupportCsfbFlag)
     && (NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
     && (enVoiceDomain != NAS_MML_IMS_PS_VOICE_ONLY))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes
��������  : ע�ᱻ��#22���������Ƿ���Ҫdisable lte
�������  : ��
�������  : ��
�� �� ֵ  : VOS_TRUE   - ��ҪDisable L
            VOS_FALSE - ����ҪDisable L
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��1��15��
  ��    ��   : z00161729
  �޸�����   : AT&T ֧��DAM�����޸�
2.��    ��   : 2015��4��20��
  ��    ��   : z00161729
  �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes(VOS_VOID)
{
    VOS_UINT32                                              ulIsPlmnInSupportDamPlmnInfo;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    NAS_MML_3GPP_REL_ENUM_UINT8                             enLteRelVersion;

    ulIsPlmnInSupportDamPlmnInfo = VOS_FALSE;
    enLUeMode                    = NAS_MML_GetLteUeOperationMode();
    enLteRelVersion              = NAS_MML_GetLte3gppRelVersion();

    /* ��ǰLTE��ģ,���ز���Ҫdisable lte */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* ����CS/PS mode 1��IMS VOICE���� */
    if ((VOS_TRUE                               == NAS_MML_GetImsVoiceAvailFlg())
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1  != enLUeMode))
    {
        return VOS_FALSE;
    }

    /* ATT�Ŀ����ע�ᱻ��#22����������������֧��DAM���������б�����disable lte��
       ��������disable lte;
       ��ATT�Ŀ�ע�ᱻ��#22�����������Э��汾С��R11��Ҫdisable lte��
       ����R11����disable lte*/
    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());

    if (VOS_FALSE == NAS_MML_IsImsiHplmnInDamImsiPlmnList())
    {
        /* 24301_CR1485R2_(Rel-11)_C1-123380 ��Ӧ24301 5.5.1.3.4.3��5.5.3.3.4.3�½�����:
           #22:The UE shall stop timer T3430 if still running. The tracking area updating
         attempt counter shall be set to 5. The UE shall start timer T3402, shall set
         the EPS update status to EU1 UPDATED, and shall enter state EMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM.
         ��CR��Э��汾���� */

        if (enLteRelVersion < NAS_MML_3GPP_REL_R11)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    if (VOS_TRUE == ulIsPlmnInSupportDamPlmnInfo)
    {
        return VOS_TRUE;
    }

    if (enLteRelVersion < NAS_MML_3GPP_REL_R11)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_IsNeedDisableL_CombinedAttRsltOnlyEpsSucc
��������  : ����ע��Combined attach successful for EPS services only����
            Combined TAU successful for EPS services only����ҪDisable L
�������  : enCsRegRsltCause
�������  :
�� �� ֵ  : VOS_TRUE   ��ҪDisable L
             VOS_FALSE ����ҪDisable L
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2012��06��02��
  ��    ��   : s00217060
  �޸�����   : �����ɺ���
2.��    ��   : 2015��1��5��
  ��    ��   : z00161729
  �޸�����   : AT&T ֧��DAM�����޸�
3.��    ��   : 2015��4��20��
  ��    ��   : z00161729
  �޸�����   : 24301 R11 CR������Ŀ�޸�
4.��    ��   : 2015��6��19��
  ��    ��   : z00161729
  �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_CombinedRegRsltOnlyEpsSucc(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause
)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    /* ����CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    {
        return VOS_FALSE;
    }


    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* enCsRegRsltCauseΪ#16,#17,#22,other cause && NAS_MMC_GetRegRsltAttemptCounter�ﵽ5�� */
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, begin */
    if ((NAS_MML_MAX_PS_REG_FAIL_CNT                == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
     && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != enCsRegRsltCause))
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, end */
    {
        /* 24301_CR1884R4_(Rel-11)_C1-140658-C1-140643-C1-140393-C1-140368-C1-140004-24301-b90-TA-IMSVoPS-EPS-only
          TAU ACCEPT��EPS ONLY�ɹ�������ԭ��ֵΪ16,17��CS/PS1��DIABLE LTE����������
          persistent EPS bearer�Ƿ���ڣ���Ӧ24301 5.5.3.3.4.3�½�:
      #16 and #17:a UE operating in CS/PS mode 1 of operation with "IMS voice not available"
          and with a persistent EPS bearer context shall wait until the radio bearer
          associated with the persistent EPS bearer context has been released. When
          the radio bearer associated with the persistent EPS bearer context has been
          released and the UE is registered for EPS services only, operating in CS/PS
          mode 1 of operation with "IMS voice not available", then the UE shall attempt
          to select GERAN or UTRAN radio access technology and proceed with appropriate
          MM or GMM specific procedures and disable the E-UTRA capability (see subclause 4.5).
          ��CR��Э��汾���� */
        if (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegRsltCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegRsltCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCsRegRsltCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes();
        }

        return VOS_TRUE;
    }

    /* ����ע��ʧ��ʱ,����ӵ�#18�б���,��other cause����,��Ҫ5��֮��Disable LTE,
       ��ԭ��ֵ�жϲ�׼ȷ,�������ڱ���1��֮���Disable LTE */
    /* ��#18�б��� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_IsNeedDisableL_ServiceReqFailCause18CsDomainNotAvailable
��������  : �յ�lmm��service result ind����ԭ��ֵ18�Ƿ���Ҫdisable lte
�������  : ��
�������  : ��
�� �� ֵ  : VOS_TRUE  - ��ҪDisable L
            VOS_FALSE - ����ҪDisable L
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��4��19��
  ��    ��   : z00161729
  �޸�����   : 24301 R11 CR������Ŀ�޸�
2.��    ��   : 2015��9��6��
  ��    ��   : z00359541
  �޸�����   : DTS2015081407087: �ӿڵ�����ɾ��bitOpReqType��
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_ServiceReqFailCause18CsDomainNotAvailable(VOS_VOID)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    NAS_MMC_REG_RSLT_CTX_STRU                              *pstRegRsltCtx = VOS_NULL_PTR;

    pstRegRsltCtx         = NAS_MMC_GetRegRsltCtxAddr();
    enLUeMode             = NAS_MML_GetLteUeOperationMode();

    /* 24301_CR1254R3_(Rel-11)_C1-115100 ESR����18ԭ��ֵ�Ĵ������
       The UE shall set the update status to U2 NOT UPDATED.If the UE is in CS/PS
       mode 1 of operation with "IMS voice not available" and the request was
       related to CS fallback, the UE shall attempt to select GERAN or UTRAN radio
       access technology rather than E-UTRAN for the selected PLMN or equivalent
       PLMN. The UE shall disable the E-UTRA capability (see subclause 4.5).
       If the UE is in the EMM-CONNECTED mode, the UE shall locally release the
       established NAS signalling connection and enter the EMM-IDLE mode before
       selecting GERAN or UTRAN radio access technology. ��CR����Э��汾���� */

    /* ����CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* service ����������Ч������csfb���̣�����VOS_FALSE */
    if ((VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
     && (LMM_MMC_SERVICE_RESULT_IND == pstRegRsltCtx->enRegRsltType))
    {
        return VOS_FALSE;
    }


    /* ���Կ���Э��disable lte���ǲ��Կ�Ϊ������û����飬�Ȳ�disable lte���绰����
    ��fast return��lte��lte��������ע�ᣬ����ٴα�#18�ܾ���disable lte�����LTEһ�λ��ᣬ
    �μ�DTS2015051901235���ⵥ����*/
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_IsNeedDisableL_ServiceRsltFail
��������  : �յ�lmm��service result ind��Ϣ�ж��Ƿ���Ҫdisable lte
�������  : enRegRsltCause    - ע�ᱻ��ԭ��ֵ
            ucIsReachMaxTimes - �Ƿ�ﵽ��������ʶ
�������  :
�� �� ֵ  : VOS_TRUE   ��ҪDisable L
            VOS_FALSE ����ҪDisable L
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��1��5��
  ��    ��   : z00161729
  �޸�����   : AT&T ֧��DAM�����޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_ServiceRsltFail(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegRsltCause,
    VOS_UINT8                           ucIsReachMaxTimes
)
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    enLUeMode             = NAS_MML_GetLteUeOperationMode();

    /* ����CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* DAM���Բ���Ч���򷵻�VOS_FALSE */
    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == ucIsReachMaxTimes)
    {
        return VOS_FALSE;
    }


    /* ʧ��ԭ��ֵΪ#22��������ʱ��Ҫdisable lte */
    if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enRegRsltCause)
    {
        return VOS_TRUE;
    }

    /* ʧ��ԭ��ֵ��Ϊ24.301 5.6.1.5�½ڶ����ԭ��ֵ��������ʱ��Ҫdisable lte */
    if (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE == enRegRsltCause)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc
 ��������  : ����EPS�ɹ�����PLMN��#18�б���ʱ����Ҫ Disable L
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ Disable L
              VOS_TRUE: ��Ҫ Disable L
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��06��02��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��01��10��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseIII��Ŀ
 3.��    ��   : 2015��6��19��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/

VOS_UINT32 NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc()
{
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    VOS_UINT8                                               ucSimCsRegStatus;

    enLUeMode        = NAS_MML_GetLteUeOperationMode();
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    /* CS������ע���CS����Ч */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     || (VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    /* ����CS/PS mode 1 */
    if (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode)
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    {
        return VOS_FALSE;
    }


    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* NAS_MMC_GetRegRsltAttemptCounter�ﵽ5��,��ʾ֮ǰ����ע���EPS�ɹ�,T3402δ��ʱ */
    if (NAS_MML_MAX_PS_REG_FAIL_CNT == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
    {
        return VOS_TRUE;
    }

    /* ��#18�б��� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCsPsMode1NeedPeriodSearchGU
 ��������  : �ж��Ƿ���Ҫ����������GU����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����������GU����
             VOS_FALSE:����Ҫ����������GU����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��20��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��01��10��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseIII��Ŀ
 3.��    ��   : 2015��1��14��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
 4.��    ��   : 2015��4��20��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
 5.��    ��   : 2015��6��19��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCsPsMode1NeedPeriodSearchGU(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatOrder = VOS_NULL_PTR;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdateRslt;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;

    enPsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;

    pstRatOrder          = NAS_MML_GetMsPrioRatList();
    enLUeMode            = NAS_MML_GetLteUeOperationMode();
    enAdditionUpdateRslt = NAS_MML_GetAdditionUpdateRslt();

    /* ��ǰLTE��ģ */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(pstRatOrder))
    {
        return VOS_FALSE;
    }

    /* ��ǰ���뼼��ΪGU */
    if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    /* ����CS/PS mode 1��IMS VOICE���� */
    if ((VOS_TRUE                               == NAS_MML_GetImsVoiceAvailFlg())
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1  != enLUeMode))
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    {
        return VOS_FALSE;
    }

    /* Additional Update Result IE��Ϣ��ָʾSMS Only��CSFB Not Preferred */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(enAdditionUpdateRslt))
    {
        return VOS_TRUE;
    }

    /* NAS_MMC_GetRegRsltAttemptCounterΪ5 */
    if (NAS_MML_MAX_PS_REG_FAIL_CNT == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
    {
        /* ��ȡ֮ǰע��ʧ�ܵ�ԭ��ֵ */
        NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                                NAS_MML_NET_RAT_TYPE_LTE,
                                               &enCsRegCause,
                                               &enPsRegCause);

        if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes();
        }


        /* 24301_CR1884R4_(Rel-11)_C1-140658-C1-140643-C1-140393-C1-140368-C1-140004-24301-b90-TA-IMSVoPS-EPS-only
          TAU ACCEPT��EPS ONLY�ɹ�������ԭ��ֵΪ16,17��CS/PS1��DIABLE LTE����������
          persistent EPS bearer�Ƿ���ڣ���Ӧ24301 5.5.3.3.4.3�½�:
             #16 and #17:a UE operating in CS/PS mode 1 of operation with "IMS voice not available"
          and with a persistent EPS bearer context shall wait until the radio bearer
          associated with the persistent EPS bearer context has been released. When
          the radio bearer associated with the persistent EPS bearer context has been
          released and the UE is registered for EPS services only, operating in CS/PS
          mode 1 of operation with "IMS voice not available", then the UE shall attempt
          to select GERAN or UTRAN radio access technology and proceed with appropriate
          MM or GMM specific procedures and disable the E-UTRA capability (see subclause 4.5).
          ��CR��Э��汾���� */
        if (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes();
        }

        return VOS_TRUE;
    }

    /* ��#18�б��� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow
 ��������  : PS(����EPS��GPRS/PS)��ԭ��ֵ#7�ܾ�(����Detach/Reg/Service)��
             �ж��Ƿ���Ҫdisable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ Disable L
              VOS_TRUE: ��Ҫ Disable L
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��07��02��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��12��
   ��    ��   : z00161729
   �޸�����   : DTS2012082702662��disable��enable lte�����жϵ�ǰsyscfg�Ƿ�֧��L
 3.��    ��   : 2012��12��28��
   ��    ��   : s46746
   �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_PsFailCause7PsServNotAllow(VOS_VOID)
{
    VOS_UINT8                                               ucSimCsRegStatus;

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    /* CS������ע���CS����Ч */
    if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
     || (VOS_FALSE == ucSimCsRegStatus))
    {
        return VOS_FALSE;
    }

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_FALSE;
    }

    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsEutranNotAllowedNeedDisableL
 ��������  : PS(����EPS��GPRS/PS)��ԭ��ֵ#7�ܾ�(����Detach/Reg/Service)��
             �ж��Ƿ���Ҫdisable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ Disable L
             VOS_TRUE: ��Ҫ Disable L
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��04��22��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsEutranNotAllowedNeedDisableL(VOS_VOID)
{

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if (VOS_TRUE == NAS_MML_IsLteCapabilityDisabled(NAS_MML_GetLteCapabilityStatus(), NAS_MML_GetDisableLteRoamFlg()))
    {
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedDisableL_LteRejCause14
 ��������  : LTE #14�ܾ����ж��Ƿ���Ҫdisable LTE
 �������  : ��
 �������  : ��
 ����ֵ    : VOS_TRUE   ��ҪDisable L
             VOS_FALSE  ����ҪDisable L
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��05��
    ��    ��   : h00285180
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedDisableL_LteRejCause14(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn;

    if (VOS_FALSE == NAS_MML_GetLteRejCause14Flg())
    {
        /* ����δ���� */
        return VOS_FALSE;
    }

    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();
    if (VOS_FALSE ==  NAS_MML_ComparePlmnIdWithHplmn(pstCurrPlmn))
    {
        /* VPLMN��ִ��#14�ܾ��Ż� */
        return VOS_FALSE;
    }

    /* LTE only */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_CsRegFailCause2ImsiUnknownInHlr
 ��������  : �ж�Csע��ʧ��#2ʱ���Ƿ���ҪEnable Lte
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ Enable Lte
              VOS_TRUE: ��Ҫ Enable Lte
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��10��15��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��USIM��ʱ������ҪEnable Lte;SIM��ʱ����Ҫ
 3.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_CsRegFailCause2ImsiUnknownInHlr(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)Csע��ʧ��ԭ��ֵ#2��#3��#6
    (3)PS����Ч��USIM�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ���֮ǰû��disable LTE,����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* PS����Ч��USIM��,��ҪEnable Lte */
    if ( (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
      || (NAS_MML_SIM_TYPE_USIM == enSimType) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_CsRegFailCause256AuthRej
 ��������  : �ж�Csע��ʧ��ʱ���Ƿ���ҪEnable Lte
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ Enable Lte
              VOS_TRUE: ��Ҫ Enable Lte
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��10��15��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��USIM��ʱ������ҪEnable Lte;SIM��ʱ����Ҫ
 3.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_CsRegFailCause256AuthRej(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)Csע��ʧ��ԭ��ֵ#256
    (3)PS����Ч��USIM�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰû��disable LTE,����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* PS����Ч��USIM��,��ҪEnable Lte */
    if ( (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
      || (NAS_MML_SIM_TYPE_USIM == enSimType) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_PsRegFailCause256AuthRej
 ��������  : �ж�Psע��ʧ��ʱ���Ƿ���ҪEnable Lte
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ Enable Lte
              VOS_TRUE: ��Ҫ Enable Lte
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��10��15��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 3.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_PsRegFailCause256AuthRej(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)Cs����Psע��ʧ��ԭ��ֵ#256 */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ��SIM��,����ҪEnable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* ���֮ǰ�Ѿ�disable LTE,��Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_PsRegFailCause3IllegalMs
 ��������  : �ж�Psע��ʧ��ʱ���Ƿ���ҪEnable Lte
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ Enable Lte
              VOS_TRUE: ��Ҫ Enable Lte
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��10��15��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 3.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
s*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_PsRegFailCause3IllegalMs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)Psע��ʧ��ԭ��ֵ#3 */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ��SIM��,����ҪEnable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* ���֮ǰ�Ѿ�disable LTE,��Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_PsRegFailCause8GprsAndNonGprsNotAllow
 ��������  : �ж�Psע��ʧ��ʱ���Ƿ���ҪEnable Lte
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ Enable Lte
              VOS_TRUE: ��Ҫ Enable Lte
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��10��15��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 3.��    ��   : 2013��2��28��
   ��    ��   : w00176964
   �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_PsRegFailCause8GprsAndNonGprsNotAllow(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)Psע��ʧ��ԭ��ֵ#8 */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ��SIM��,����ҪEnable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* ���֮ǰ�Ѿ�disable LTE,��Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_CmServiceRejectInd
 ��������  : �յ�CM_SERVICE_REJECT_INDָʾ��Ԥ����
 �������  : ulEventType:��Ϣ����
              pstMsg:CM_SERVICE_REJECT_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����Enable Lte
              VOS_FALSE:����Ҫ����Enable Lte
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��10��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��10��
    ��    ��   : s00217060
    �޸�����   : DTS2012102902559��USIM��ʱ������ҪEnable Lte;SIM��ʱ����Ҫ
  3.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
  4.��    ��   : 2013��2��28��
    ��    ��   : w00176964
    �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedEnableLte_CmServiceRejectInd(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCmServiceRejCause
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)Cm Service����ԭ��ֵ#6
    (3)PS����Ч��USIM�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰû��disable LTE,����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* ��SIM��,����ҪEnable Lte */
    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_FALSE;
    }


    /* Cm Service����ԭ��ֵ#6����Ҫenable LTE */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == enCmServiceRejCause)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_MmAbortInd
 ��������  : �ж��յ�MM_ABORT_IND��Ϣ�Ƿ���ҪEnable Lte
 �������  : ulEventType:��Ϣ����
              pstMsg:MM_ABORT_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����Enable Lte
              VOS_FALSE:����Ҫ����Enable Lte
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��10��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��10��
    ��    ��   : s00217060
    �޸�����   : DTS2012102902559��USIM��ʱ������ҪEnable Lte;SIM��ʱ����Ҫ
  3.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
  4.��    ��   : 2013��2��28��
    ��    ��   : w00176964
    �޸�����   : DTS2014030100833:����SIM��disable��enable lTE�߼�
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedEnableLte_MmAbortInd(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enAbortCause
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)Mm Abortԭ��ֵ#6
    (3)PS����Ч��USIM�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ���֮ǰδdisable LTE������Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* ��SIM��,����ҪEnable Lte */
    if (NAS_MML_SIM_TYPE_SIM == enSimType)
    {
        return VOS_FALSE;
    }


    /* Mm Abortԭ��ֵ#6����Ҫenable LTE */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == enAbortCause)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_EnableLteTimerExp
 ��������  : �ж��յ�TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER��Ϣ�Ƿ���ҪEnable Lte
 �������  : VOID
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����Enable Lte
             VOS_FALSE:����Ҫ����Enable Lte
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��12��15��
    ��    ��   : L65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��6��3��
    ��    ��   : z00161729
    �޸�����   : SVLTE �޸�
  3.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
  4.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
  5.��    ��   : 2015��01��5��
    ��    ��   : h00285180
    �޸�����   : LTE #14�ܾ��Ż�:DTS2015010401946

  6.��    ��   : 2015��4��18��
    ��    ��   : w00167002
    �޸�����   : DTS2015032709270:�ھܾ�15������DISABLE LTEʱ��Ҳ������ENABLE��ʱ����

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedEnableLte_EnableLteTimerExp(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason;

    enDisableLteReason = NAS_MML_GetDisableLteReason();

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)disable LTEԭ��ֵEM��VOICE NOT SUPPORT
    (3)PS����Ч��USIM�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    enSimType              = NAS_MML_GetSimType();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* ���֮ǰδdisable LTE������Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* PS����Ч����SIM��,����ҪEnable Lte */
    if ( (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
      && (NAS_MML_SIM_TYPE_SIM == enSimType) )
    {
        return VOS_FALSE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, begin */
    /* disable LTEԭ��ΪEMC��IMS VOICE�����û�LTE #14�ܾ��Ż�����Ҫenable LTE */
    if ((MMC_LMM_DISABLE_LTE_REASON_EMERGENCY_CALL          == enDisableLteReason)
     || (MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE == enDisableLteReason)
     || (MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14        == enDisableLteReason)
     || (MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW == enDisableLteReason))
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-18, end */
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveEpsAttachAttemptCounter
 ��������  : ����EPS Attach�����Ϣ�е�Attempt Counter
 �������  : pstEpsAttachIndMsg:Attach�����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��07��05��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SaveEpsAttachAttemptCounter(
    LMM_MMC_ATTACH_IND_STRU            *pstEpsAttachIndMsg
)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    /* ��LMMģ��ȷ�ϣ����Attach���ΪCN REJ��MT_DETACH_FAILURE��MO_DETACH_FAILURE
       ���߳ɹ���Я����Cn Rslt���������Ϣ��Я����ulAttemptCount���£��������
       ���������������������Ϣ��Я����ulAttemptCount���£����򲻸��� */
    if ((MMC_LMM_ATT_RSLT_CN_REJ == pstEpsAttachIndMsg->ulAttachRslt)
     || (MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE == pstEpsAttachIndMsg->ulAttachRslt)
     || (MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE == pstEpsAttachIndMsg->ulAttachRslt)
     || ((MMC_LMM_ATT_RSLT_SUCCESS == pstEpsAttachIndMsg->ulAttachRslt)
      && (VOS_TRUE == pstEpsAttachIndMsg->bitOpCnRslt)))
    {
        if (VOS_TRUE == pstEpsAttachIndMsg->bitOpAtmpCnt)
        {
            pstRegRsltCtx->ucEpsAttemptCounter = (VOS_UINT8)pstEpsAttachIndMsg->ulAttemptCount;
        }
        else
        {
            pstRegRsltCtx->ucEpsAttemptCounter = 0x0;
        }
    }
    else
    {
        if (VOS_TRUE == pstEpsAttachIndMsg->bitOpAtmpCnt)
        {
            pstRegRsltCtx->ucEpsAttemptCounter = (VOS_UINT8)pstEpsAttachIndMsg->ulAttemptCount;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveEpsTauAttemptCounter
 ��������  : ����EPS TAU�����Ϣ�е�Attempt Counter
 �������  : pstEpsTauIndMsg:TAU�����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��07��05��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SaveEpsTauAttemptCounter(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstEpsTauIndMsg
)
{
    NAS_MMC_REG_RSLT_CTX_STRU          *pstRegRsltCtx = VOS_NULL_PTR;
    pstRegRsltCtx   = NAS_MMC_GetRegRsltCtxAddr();

    /* ��LMMģ��ȷ�ϣ����TAU���ΪCN REJ��MT_DETACH_FAILURE��MO_DETACH_FAILURE
       ���߳ɹ���Я����Cn Rslt���������Ϣ��Я����ulAttemptCount���£��������
       ���������������������Ϣ��Я����ulAttemptCount���£����򲻸��� */
    if ((MMC_LMM_TAU_RSLT_CN_REJ == pstEpsTauIndMsg->ulTauRst)
     || (MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE == pstEpsTauIndMsg->ulTauRst)
     || (MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE == pstEpsTauIndMsg->ulTauRst)
     || ((MMC_LMM_TAU_RSLT_SUCCESS == pstEpsTauIndMsg->ulTauRst)
      && (VOS_TRUE == pstEpsTauIndMsg->bitOpCnRst)))
    {
        if (VOS_TRUE == pstEpsTauIndMsg->bitOpAtmpCnt)
        {
            pstRegRsltCtx->ucEpsAttemptCounter = (VOS_UINT8)pstEpsTauIndMsg->ulAttemptCount;
        }
        else
        {
            pstRegRsltCtx->ucEpsAttemptCounter = 0x0;
        }
    }
    else
    {
        if (VOS_TRUE == pstEpsTauIndMsg->bitOpAtmpCnt)
        {
            pstRegRsltCtx->ucEpsAttemptCounter = (VOS_UINT8)pstEpsTauIndMsg->ulAttemptCount;
        }
    }

    return;
}

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-13, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcEmcPdpRelease_DetachPs
 ��������  : ���ݽ���PDN����״̬����PS��DETACH
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��17��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ProcEmcPdpRelease_DetachPs( VOS_VOID )
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stSndEquPlmnInfo;
    VOS_UINT8                           ucEmcPdpStatusFlg;

    /* Э����������:
        1.if there is no PDN connection for emergency bearer services established,
        the UE shall remove from the list any PLMN code that is already in the list of "forbidden PLMNs"
        or in the list of "forbidden PLMNs for GPRS service".
        If there is a PDN connection for emergency bearer services established,
        the UE shall remove from the list of equivalent PLMNs any PLMN code present in the list of forbidden PLMNs
        or in the list of "forbidden PLMNs for GPRS service" when the PDN connection for emergency bearer services is released.

        2.if the attach procedure is not for emergency bearer services,
        the UE shall remove from the list any PLMN code that is already in the list of "forbidden PLMNs"
        or in the list of "forbidden PLMNs for GPRS service".

        3.The UE shall delete the stored list if the USIM is removed
        or when the UE attached for emergency bearer services enters the state EMM-DEREGISTERED.
    */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    ucEmcPdpStatusFlg   = NAS_MML_GetEmcPdpStatusFlg();

    /* ����PDN������ʱ������Ҫ��������PDN����ʱ�������־����LMM����EPLMN֪ͨ */
    if (VOS_TRUE == ucEmcPdpStatusFlg)
    {
        /* �������PDN���ӱ�־ */
        NAS_MML_SetEmcPdpStatusFlg(VOS_FALSE);


        /* ��������ʱ������Ҫ����EPLMN;������ʱ����LMM����EPLMN֪ͨ��ɾ��Forb Plmn */
        if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
        {
            pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
            PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
            NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
            NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);

            NAS_MMC_SndOmEquPlmn();
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSndEplmn_LmmDetachCnf
 ��������  : �ж��յ�LMM��DetachCnfʱ��Ҫ����Ҫ��LMM����EPLMN
 �������  : pstLmmDetachCnf:LMM��DetachCnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ���ͣ�VOS_FALSE:����Ҫ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��25��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSndEplmn_LmmDetachCnf(
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf
)
{
    VOS_UINT32                          ulRst;

    ulRst   = VOS_FALSE;

    /* ����������PS��CS+PS��detach��detach��Ϊfailureʱ��
        ����Ϊ����PDN�����ͷţ��������PDN���ӱ�ǣ�
        ͬʱ֪ͨLMM��ǰEPLMN�б���Ϣ��ɾ��forbidden plmn�б�
    */

    switch (pstLmmDetachCnf->ulReqType)
    {
        case MMC_LMM_MO_DET_PS_ONLY:
        case MMC_LMM_MO_DET_CS_PS:

            if ( (MMC_LMM_DETACH_RSLT_SUCCESS       == pstLmmDetachCnf->ulDetachRslt)
              || (MMC_LMM_DETACH_RSLT_ACCESS_BARED  == pstLmmDetachCnf->ulDetachRslt)
              || (MMC_LMM_DETACH_RSLT_AUTH_REJ      == pstLmmDetachCnf->ulDetachRslt) )
            {
                ulRst = VOS_TRUE;
            }

            break;

        default:

            ulRst   = VOS_FALSE;

            break;
    }

    return ulRst;
}

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-13, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLmmDetachIndTypeToMmcType
 ��������  : ��LMM detach indת����mmc�ڲ�����Ľṹ
 �������  : enCnReqType - lmm��ʽ��detach type
 �������  : penDetachType  - mmc��ʽ��detach type

 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��14��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ConvertLmmDetachIndTypeToMmcType(
    MMC_LMM_MT_DETACH_TYPE_ENUM_UINT32                      enCnReqType,
    NAS_MSCC_PIF_NETWORK_DETACH_TYPE_ENUM_UINT8                 *penDetachType
)
{
    switch ( enCnReqType )
    {
        case MMC_LMM_MT_DET_REATTACH_REQUIRED:
            *penDetachType = NAS_MSCC_PIF_NETWORK_DETACH_TYPE_REATTACH;
            break;

        case MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED:
            *penDetachType = NAS_MSCC_PIF_NETWORK_DETACH_TYPE_NOATTACH;
            break;

        case MMC_LMM_MT_DET_IMSI:
            *penDetachType = NAS_MSCC_PIF_NETWORK_DETACH_TYPE_IMSI;
            break;

        default:
            *penDetachType = NAS_MSCC_PIF_NETWORK_DETACH_TYPE_BUTT;
            break;
    }
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsFailCauseInCustomizedForbLaCfgList
 ��������  : CSע��ʧ��ʱ�Ƿ񴥷�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��23��
    ��    ��   : z00359541
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsFailCauseInCustomizedForbLaCfgList(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstForbLaWithValidPeriodCfg = NAS_MML_GetForbLaWithValidPeriodCfg();

    /* ���Կ�ʱ����Э��Ҫ�󣬲���Ҫ�������� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* ԭ��ֵ�Ƿ���NV���Ƶ�ԭ��ֵ�б��� */
    for (i = 0; i < pstForbLaWithValidPeriodCfg->ulSupportForbLaWithValidPeriodNum; i++)
    {
        if (enCause == pstForbLaWithValidPeriodCfg->astForbLaWithValidPeriodCfgList[i].usRegFailCause)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedLauRejTrigPlmnSearch
 ��������  : LAU��#12�ܾ�ʱ�Ƿ񴥷�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��23��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedLauRejTrigPlmnSearch(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause
)
{
    NAS_MML_LAU_REJ_TRIG_PLMN_SEARCH_STRU                  *pstLauRejCfg    = VOS_NULL_PTR;
    VOS_UINT8                                               ucCmSrvExistFlg;
    VOS_UINT8                                               ucIsCurCauseInNvCauseList;
    VOS_UINT32                                              i;

    pstLauRejCfg    = NAS_MML_GetLauRejTrigPlmnSearchCfg();
    ucCmSrvExistFlg = NAS_MML_GetCmServiceSetupFlg();
    ucIsCurCauseInNvCauseList   = VOS_FALSE;

    /* ���Կ�ʱ����Э��Ҫ�󣬲���Ҫ�������� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* ԭ��ֵ�Ƿ���NV���Ƶ�ԭ��ֵ�б��� */
    for (i=0; i < pstLauRejCfg->ucCmSrvTrigPlmnSearchCauseNum; i++)
    {
        if (enCause == pstLauRejCfg->aucCmSrvTrigPlmnSearchCause[i])
        {
            ucIsCurCauseInNvCauseList   = VOS_TRUE;
            break;
        }
    }

    /* ��ҵ��ʱ������NV�򿪣���Ҫ�������� */
    if ((VOS_TRUE == pstLauRejCfg->ucCmSrvExistTrigPlmnSearch)
     && (VOS_TRUE == ucCmSrvExistFlg)
     && (VOS_TRUE == ucIsCurCauseInNvCauseList))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ConverGmmActionTypeToMml
 ��������  : GMM��action ����ת��ΪMML��
 �������  : enGmmActionType:GMM��action type
 �������  : penProcType:MML�е�ע������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��1��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��30��
   ��    ��   : w00176964
   �޸�����   : DTS2013030802929,������RAU��Ҫ֪ͨLMM
*****************************************************************************/
VOS_VOID    NAS_MMC_ConverGmmActionTypeToMml(
    GMM_MMC_ACTION_TYPE_ENUM_U32        enGmmActionType,
    NAS_MML_PROC_TYPE_ENUM_U32         *penProcType
)
{
    switch (enGmmActionType)
    {
        case GMM_MMC_ACTION_RAU:

            *penProcType = NAS_MML_PROC_RAU;
            break;

        case GMM_MMC_ACTION_ATTACH:

            *penProcType = NAS_MML_PROC_ATTACH;
            break;

        case GMM_MMC_ACTION_COMBINED_RAU:

            *penProcType = NAS_MML_PROC_COMBINED_RAU;
            break;

        case GMM_MMC_ACTION_COMBINED_ATTACH:

            *penProcType = NAS_MML_PROC_COMBINED_ATTACH;
            break;

        case GMM_MMC_ACTION_PERIODC_RAU:

            *penProcType = NAS_MML_PROC_PERIODC_RAU;
            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ConverGmmActionTypeToMml: Invalid action type!");
            *penProcType = NAS_MML_PROC_BUTT;
            break;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSingleDomainFailAction
 ��������  : ��ȡ��Ӧע��ԭ��ֵ��Ӫ�̶��ƵĶ���
 �������  :
            enDomain,ע�����
            enFailCause,ʧ��ԭ��ֵ

 �������  : penAction:���ƵĶ���
 �� �� ֵ  : VOS_UINT32 VOS_TRUE:��ȡ�ɹ�  VOS_FALSE:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��11��
   ��    ��   : w00166186
   �޸�����   : AT&T&DCM�����ɺ���
2.��    ��   : 2014��8��19��
  ��    ��   : w00167002
  �޸�����   : DTS2014081905808:������PSע��ܾ�14ʱ������ǰ��HOME PLMN�ϣ������
               ����ѭ��ƹ�ң��޸�Ϊ����ACTION����:�����������ϴ���ѡ������HOME������
               ����Ч�����������̽��д���
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    NAS_MMC_GetSingleDomainFailAction(
    NAS_MML_REG_DOMAIN_ENUM_UINT8           enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enFailCause
)
{
    VOS_UINT8                                           i;
    NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_LIST_CTX_STRU*    pstSingleDomainFailActionCtx;

    pstSingleDomainFailActionCtx = NAS_MML_GetSingleDomainFailActionCtx();

    /* ����NVû�м��� */
    if (VOS_FALSE == pstSingleDomainFailActionCtx->ucActiveFlag)
    {
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }

    for (i = 0; i < pstSingleDomainFailActionCtx->ucCount; i++)
    {
        /* ��Ӧ��ע�����ע��ԭ��ֵ�ڶ����б��� */
        if ((enDomain == pstSingleDomainFailActionCtx->astSingleDomainFailActionList[i].enDomain)
         && (enFailCause == pstSingleDomainFailActionCtx->astSingleDomainFailActionList[i].enRegCause))
        {
            switch (pstSingleDomainFailActionCtx->astSingleDomainFailActionList[i].enAction)
            {
                case NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION:
                     return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;

                case NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON:
                     return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

                case NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION:
                     return NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;

                case NAS_MML_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON:
                     return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

                case NAS_MML_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION:

                     /* ��������������������������ԭ�����̴��� */
                     if ( VOS_TRUE == NAS_MMC_IsRoam() )
                     {
                         return NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION;
                     }

                     return NAS_MMC_ADDITIONAL_ACTION_BUTT;

                default:
                     return NAS_MMC_ADDITIONAL_ACTION_BUTT;
            }
        }
    }

    return NAS_MMC_ADDITIONAL_ACTION_BUTT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCurrPlmnInEplmnList
 ��������  : �жϵ�ǰפ����PLMN�Ƿ���EPLMN
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_TRUE:   ��EPLMN
             VOS_FALSE:  ����EPLMN

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : l00208543
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsCurrPlmnInEplmnList(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU               *pstCurplmn   =  VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList =  VOS_NULL_PTR;

    i            = 0;
    pstCurplmn   = NAS_MML_GetCurrCampPlmnId();
    pstEplmnList = NAS_MML_GetEquPlmnList();

    if ((VOS_FALSE == NAS_MML_GetEplmnValidFlg())
     || (0         == pstEplmnList->ucEquPlmnNum))
    {
        return VOS_FALSE;
    }

    for ( i = 0 ; i < pstEplmnList->ucEquPlmnNum; i++ )
    {
        if ( ( pstCurplmn->ulMcc == pstEplmnList->astEquPlmnAddr[i].ulMcc)
          && ( pstCurplmn->ulMnc == pstEplmnList->astEquPlmnAddr[i].ulMnc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsAccBarPlmnSearch
 ��������  : �����ֹ���Ƿ���Ҫ����OPTIONAL_PLMN_SELECTION
             ֻ�����Կ��ش򿪣���פ���������HPLMN/RPLMNʱ��Ҫ����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_TRUE:   ��Ҫplmn����
             VOS_FALSE:  ����Ҫplmn����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : s00190137
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
  3.��    ��   : 2013��11��30��
    ��    ��   : z00161729
    �޸�����   : DTS2013112809149:9230 nv�����ý�ֹ���뼼��Ϊw��g���ֶ�����ģʽפ��g��23002�ɹ���syscfg����w only��anycellפ��24005���ᷴ������w��anycell����
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAccBarPlmnSearch(VOS_VOID)
{
    VOS_UINT32                          ulIsRoam;
    VOS_UINT32                          ulIsAccBarPlmnSearchFlg;
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;
    NAS_MMC_TIMER_STATUS_ENUM_U8        enAvailableTimerStatus;
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    NAS_MML_PLMN_ID_STRU               *pstCurplmn =  VOS_NULL_PTR;

    /* ��ȡNV���Կ��� */
    ulIsAccBarPlmnSearchFlg = (VOS_UINT32)NAS_MML_GetSupportAccBarPlmnSearchFlg();

    /* ��ȡ����״̬ */
    ulIsRoam                = NAS_MMC_IsRoam();

    /* ��ȡ��ǰCamp������*/
    pstCurplmn              = NAS_MML_GetCurrCampPlmnId();

    /* ��ȡ��ǰ״̬��Id*/
    enFsmId                 = NAS_MMC_GetCurrFsmId();

    /* ��ѯMMC_AVAILABLE_TIMER��ʱ��״̬*/
    enAvailableTimerStatus  = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

    if (VOS_FALSE == NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAccBarPlmnSearch: NAS_MMC_IsNeedPlmnSearch_RegLocalFailCause return false.");
        return VOS_FALSE;
    }


    /* ���Ӳ��Կ����������Կ�ʱ���޸ģ�ֱ�ӷ��� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAccBarPlmnSearch(): The sim is Test card!");
        return VOS_FALSE;
    }

    NAS_NORMAL_LOG2(WUEPS_PID_MMC,
                    "NAS_MMC_IsAccBarPlmnSearch: ulIsAccBarPlmnSearchFlg, ulIsRoam",
                    ulIsAccBarPlmnSearchFlg,
                    ulIsRoam);

    /* ���Կ���δ�򿪻������״̬�������ֹ����Ҫ���� */
    if ((VOS_FALSE == ulIsAccBarPlmnSearchFlg)
     || (VOS_FALSE == ulIsRoam))
    {
        return VOS_FALSE;
    }

    NAS_NORMAL_LOG2(WUEPS_PID_MMC,
                    "NAS_MMC_IsAccBarPlmnSearch: enFsmId, enAvailableTimerStatus",
                    enFsmId,
                    enAvailableTimerStatus);

    /* ��L1״̬������available��ʱ��������ʱ������Ҫ�ٴ������� */
    if ((NAS_MMC_FSM_L1_MAIN == enFsmId)
     && (NAS_MMC_TIMER_STATUS_RUNING == enAvailableTimerStatus))
    {
        return VOS_FALSE;
    }

    /* ��ǰRplmn������ʱ����Ҫ���� */
    if (VOS_FALSE == NAS_MML_GetRPlmn(NAS_MML_GetLastRplmnRat(), &stRPlmnId))
    {
        return VOS_TRUE;
    }

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAccBarPlmnSearch: NAS_MML_GetRPlmn return false.");

    /* �����ǰ����ΪEPLMN����Ҫ���� */
    if (VOS_TRUE == NAS_MMC_IsCurrPlmnInEplmnList())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAccBarPlmnSearch: NAS_MMC_IsCurrPlmnInEplmnList return false.");

        return VOS_FALSE;
    }

    /* פ����ֹ����ΪRPLMN������Ҫ����*/
    /* ���ﻹ����Ҫ�ж�RPLMN����ֹRPLMN��ЧEPLMN�ĳ�����©�� */
    if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurplmn, &stRPlmnId))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAccBarPlmnSearch: NAS_MML_CompareBcchPlmnwithSimPlmn return false.");

        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegFailCause417ECallInactive
 ��������  : CS��causeΪecall inactive״̬�Ĵ���
 �������  :
             VOS_VOID
 �������  : ��
 �� �� ֵ  : NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��30��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_ProcCsRegFailCause417ECallInactive(VOS_VOID)
{
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_LIMITED_SERVICE);

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
}

#endif
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-30, end */

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

