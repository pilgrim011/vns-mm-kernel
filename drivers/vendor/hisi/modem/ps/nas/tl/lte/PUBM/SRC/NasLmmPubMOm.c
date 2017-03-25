/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLmmPubMOm.c
    Description :
    History     :
      1.  qilili00145085  2008-10-30  Draft Enact
      2.  hanlufeng 41410   2009-05-05  BJ9D00629   ͸��������������ñ���ȷ��
                                        ��������������棬����͸��������ִ��
      3.  zhengjunyan 00148421   2011-05-28 �ļ����� NasMmPubMOm.c�޸�Ϊ
                                           NasLmmPubMOm.c
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasLmmPubMInclude.h"
/*#include    "IpDhcpv4Server.h"*/
#include    "NasERabmIpFilter.h"
#include    "NasEmmSecuOm.h"
#include    "ImsaNvInterface.h"
#include    "SysNvId.h"

#include    "omringbuffer.h"
#include    "omnvinterface.h"
#if (VOS_WIN32 == VOS_OS_VER)
#include    "NasMmPubMTest.h"
#endif
#include    "NasEmmAttDetInclude.h"

#include    "TlPsDrv.h"

#include    "NasCommSndOm.h"

#include    "NasMmlCtx.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMOM_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMOM_C
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
NAS_EMM_DRX_CYCLE_LEN_CHANGE_ENUM_UINT32    g_ulDrxCycleLenChange
                                            = NAS_EMM_DRX_CYCLE_LEN_NOT_CHANGED;
/*
static APP_MM_REPORT_MODE_ENUM_UINT32      g_ulMmInfoRptFlag = APP_MM_RM_AUTO;
static APP_EMM_INFO_STRU                   g_stAppEmmInfo = {0};
*/

#if (FEATURE_ON == FEATURE_PTM)
LNAS_ERRLOG_GLO_INFO_STRU  stErrlogGloInfo;
/* LNASģ��Error Log�쳣����� */
LNAS_ERRLOG_ALM_LEVEL_STRU g_astLNasErrAlmLevelTb[] = {
    {LNAS_OM_ERRLOG_ALM_ID_ATTACH_FAIL,         LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_TAU_FAIL,            LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_DETACH_FAIL,         LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_NOR_SERVICE_FAIL,    LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_EXT_SERVICE_FAIL,    LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL,         LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_RAT_FAIL,            LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_CONN_FAIL,   LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_PDN_DISCONN_FAIL,LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_RES_MOD_FAIL,    LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_ESM_RES_ALLOC_FAIL,  LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_OVERFLOW_FAIL,       LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_LOCAL_DETACH_FAIL,   LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_AUTH_REJ,            LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {LNAS_OM_ERRLOG_ALM_ID_IMPROVE_PERFORMCE,   LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL},
};

LNAS_ERR_LOG_ALM_REPORT_TYPE_STRU   g_astLNasErrAlmUnsoliReportTypeTb[] = {
    {LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL,         EMM_ERR_LOG_ALARM_REPORT},
    {LNAS_OM_ERRLOG_ALM_ID_IMPROVE_PERFORMCE,   EMM_ERR_LOG_ALARM_REPORT},
};


NAS_LMM_CN_CAUSE_TRANS_STRU          g_astEmmErrlogCnCauseMap[] =
{
    /*------------casue-----------------------------------error id---------------------------*/
    {NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS,                 EMM_OM_ERRLOG_CN_CAUSE_IMSI_UNKNOWN_IN_HSS},
    {NAS_LMM_CAUSE_ILLEGAL_UE,                          EMM_OM_ERRLOG_CN_CAUSE_ILLEGAL_UE},
    {NAS_LMM_CAUSE_IMEI_NOT_ACCEPTED,                   EMM_OM_ERRLOG_CN_CAUSE_IMEI_NOT_ACCEPTED},
    {NAS_LMM_CAUSE_ILLEGAL_ME,                          EMM_OM_ERRLOG_CN_CAUSE_ILLEGAL_ME},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW,                  EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_NOT_ALLOW},
    {NAS_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW, EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW},
    {NAS_LMM_CAUSE_UE_ID_NOT_DERIVED,                   EMM_OM_ERRLOG_CN_CAUSE_UE_ID_NOT_DERIVED},
    {NAS_LMM_CAUSE_IMPLICIT_DETACHED,                   EMM_OM_ERRLOG_CN_CAUSE_IMPLICIT_DETACHED},
    {NAS_LMM_CAUSE_PLMN_NOT_ALLOW,                      EMM_OM_ERRLOG_CN_CAUSE_PLMN_NOT_ALLOW},
    {NAS_LMM_CAUSE_TA_NOT_ALLOW,                        EMM_OM_ERRLOG_CN_CAUSE_TA_NOT_ALLOW},
    {NAS_LMM_CAUSE_ROAM_NOT_ALLOW,                      EMM_OM_ERRLOG_CN_CAUSE_ROAM_NOT_ALLOW},
    {NAS_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,          EMM_OM_ERRLOG_CN_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN},
    {NAS_LMM_CAUSE_NO_SUITABL_CELL,                     EMM_OM_ERRLOG_CN_CAUSE_NO_SUITABL_CELL},
    {NAS_LMM_CAUSE_MSC_UNREACHABLE,                     EMM_OM_ERRLOG_CN_CAUSE_MSC_UNREACHABLE},
    {NAS_LMM_CAUSE_NETWORK_FAILURE,                     EMM_OM_ERRLOG_CN_CAUSE_NETWORK_FAILURE},
    {NAS_LMM_CAUSE_CS_NOT_AVAIL,                        EMM_OM_ERRLOG_CN_CAUSE_CS_NOT_AVAIL},
    {NAS_LMM_CAUSE_ESM_FAILURE,                         EMM_OM_ERRLOG_CN_CAUSE_ESM_FAILURE},
    {NAS_LMM_CAUSE_MAC_FAILURE,                         EMM_OM_ERRLOG_CN_CAUSE_MAC_FAILURE},
    {NAS_LMM_CAUSE_SYNCH_FAILURE,                       EMM_OM_ERRLOG_CN_CAUSE_SYNCH_FAILURE},
    {NAS_LMM_CAUSE_PROCEDURE_CONGESTION,                EMM_OM_ERRLOG_CN_CAUSE_PROCEDURE_CONGESTION},
    {NAS_LMM_CAUSE_UE_SECU_CAP_MISMATCH,                EMM_OM_ERRLOG_CN_CAUSE_UE_SECU_CAP_MISMATCH},
    {NAS_LMM_CAUSE_SECU_MODE_REJECTED_UNSPECIFIED,      EMM_OM_ERRLOG_CN_CAUSE_SECU_MODE_REJECTED_UNSPECIFIED},
    {NAS_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,         EMM_OM_ERRLOG_CN_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG},
    {NAS_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN, EMM_OM_ERRLOG_CN_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN},
    {NAS_LMM_CAUSE_CS_FALLBACK_CALL_EST_NOT_ALLOWED,    EMM_OM_ERRLOG_CN_CAUSE_CS_FALLBACK_CALL_EST_NOT_ALLOWED},
    {NAS_LMM_CAUSE_CS_DOMAIN_TMP_NOT_ALLOWED,           EMM_OM_ERRLOG_CN_CAUSE_CS_DOMAIN_TMP_NOT_ALLOWED},
    {NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,     EMM_OM_ERRLOG_CN_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED},
    {NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE,              EMM_OM_ERRLOG_CN_CAUSE_SERVER_NETWORK_FAILURE},
    {NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG,          EMM_OM_ERRLOG_CN_CAUSE_SEMANTICALLY_INCORRECT_MSG},
    {NAS_LMM_CAUSE_INVALID_MANDATORY_INF,               EMM_OM_ERRLOG_CN_CAUSE_INVALID_MANDATORY_INFORMATION},
    {NAS_LMM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED,          EMM_OM_ERRLOG_CN_CAUSE_MSG_TYPE_NON_EXIST_OR_IMPLEMENT},
    {NAS_LMM_CAUSE_MSG_TYPE_NOT_COMPATIBLE,             EMM_OM_ERRLOG_CN_CAUSE_MSG_TYPE_NOT_COMPATIBLE},
    {NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE,          EMM_OM_ERRLOG_CN_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENT},
    {NAS_LMM_CAUSE_CONDITIONAL_IE_ERROR,                EMM_OM_ERRLOG_CN_CAUSE_CONDITIONAL_IE_ERROR},
    {NAS_LMM_CAUSE_MSG_NOT_COMPATIBLE,                  EMM_OM_ERRLOG_CN_CAUSE_MSG_NOT_COMPATIBLE},
    {NAS_LMM_CAUSE_PROTOCOL_ERROR,                      EMM_OM_ERRLOG_CN_CAUSE_PROTOCOL_ERROR},
};

static VOS_UINT32   g_astEmmErrlogCnCauseNum
        = sizeof(g_astEmmErrlogCnCauseMap)/sizeof(NAS_LMM_CN_CAUSE_TRANS_STRU);
#endif


static NAS_EMM_PROTOCOL_STATE_MAP_STRU g_astProtocolStateMap[] =
{
    /* ��״̬ */
    { EMM_MS_NULL               ,     MM_SS_BUTT,      \
      APP_EMM_MS_NULL           ,     APP_EMM_SS_NULL                       },

    /* ȥע��״̬ */
    { EMM_MS_DEREG              ,     EMM_SS_DEREG_NORMAL_SERVICE,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_NORMAL_SERVICE       },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_LIMITED_SERVICE,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_LIMITED_SERVICE      },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_ATTEMPTING_TO_ATTACH,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_ATTEMPT_TO_ATTACH    },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_PLMN_SEARCH,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_PLMN_SEARCH          },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_NO_IMSI,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_NO_IMSI              },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_ATTACH_NEEDED,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_ATTACH_NEEDED        },

    { EMM_MS_DEREG              ,     EMM_SS_DEREG_NO_CELL_AVAILABLE,\
      APP_EMM_MS_DEREG          ,     APP_EMM_SS_DEREG_NO_CELL_AVAILABLE    },



    /* ע��״̬ */
    { EMM_MS_REG                ,     EMM_SS_REG_NORMAL_SERVICE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_NORMAL_SERVICE         },

    { EMM_MS_REG                ,     EMM_SS_REG_ATTEMPTING_TO_UPDATE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_ATTEMPTING_TO_UPDATE   },

    { EMM_MS_REG                ,     EMM_SS_REG_LIMITED_SERVICE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_LIMITED_SERVICE        },

    { EMM_MS_REG                ,     EMM_SS_REG_PLMN_SEARCH,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_PLMN_SEARCH            },

    { EMM_MS_REG                ,     EMM_SS_REG_WAIT_ACCESS_GRANT_IND,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_WAIT_ACCESS_GRANT_IND},

    { EMM_MS_REG                ,     EMM_SS_REG_NO_CELL_AVAILABLE,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_NO_CELL_AVAILABLE      },

    { EMM_MS_REG                ,     EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_ATTEMPT_TO_UPDATE_MM      },

    { EMM_MS_REG                ,     EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF,\
      APP_EMM_MS_REG            ,     APP_EMM_SS_REG_IMSI_DETACH_WAIT_CN_DETACH_CNF      },



    /* ע������� */
    { EMM_MS_REG_INIT           ,     MM_SS_BUTT,      \
      APP_EMM_MS_REG_INIT       ,     APP_EMM_SS_NULL                       },

    /* TAU������  */
    { EMM_MS_TAU_INIT           ,     MM_SS_BUTT,      \
      APP_EMM_MS_TAU_INIT       ,     APP_EMM_SS_NULL                       },

    /* SERVICE������ */
    { EMM_MS_SER_INIT           ,     MM_SS_BUTT,      \
      APP_EMM_MS_SER_INIT       ,     APP_EMM_SS_NULL                       },

    /* ȥע������� */
    { EMM_MS_DEREG_INIT         ,     MM_SS_BUTT,      \
      APP_EMM_MS_DEREG_INIT     ,     APP_EMM_SS_NULL                       }
};

static VOS_UINT32   g_ulProtocolStateMapNum
        = sizeof(g_astProtocolStateMap)/sizeof(NAS_EMM_PROTOCOL_STATE_MAP_STRU);

static  NAS_LMM_OM_ACT_STRU  g_astOmDataMap[] =
{
    /* APP_MM_MSG_TYPE_ENUM_UINT32      NAS_LMM_OM_ACTION_FUN */


    {ID_APP_MM_INQ_LTE_CS_REQ,         NAS_LMM_PubmDaInqLteCs},

    {ID_APP_MM_INQ_UE_MODE_REQ,         NAS_LMM_PubmDaInqUeMode},

    /* niuxiufan DT begin */
    {ID_APP_MM_INQ_LTE_GUTI_REQ,         NAS_LMM_PubmDaInqGuti},
    {ID_APP_MM_INQ_IMSI_REQ,             NAS_LMM_PubmDaInqImsi},
    {ID_APP_MM_INQ_EMM_STATE_REQ,        NAS_LMM_PubmDaInqEmmState},
    /* niuxiufan DT end */
};

static VOS_UINT32   g_astOmDataMapNum
        = sizeof(g_astOmDataMap)/sizeof(NAS_LMM_OM_ACT_STRU);


NAS_LMM_OM_MSG_ID_CHANGE_STRU g_stMmOmMsgIdStru[] =
{
    {0,NAS_EMM_CN_MT_ATTACH_ACP,    NAS_EMM_ATTACH_ACP,     EMM_OMT_KE_ATTACH_ACP},
    {0,NAS_EMM_CN_MT_ATTACH_REJ,    NAS_EMM_ATTACH_REJ,     EMM_OMT_KE_ATTACH_REJ},
    {0,NAS_EMM_CN_MT_DETACH_REQ_MT, NAS_EMM_DETACH_REQ_MT,  EMM_OMT_KE_DETACH_REQ_MT},
    {0,NAS_EMM_CN_MT_DETACH_ACP_MO, NAS_EMM_DETACH_ACP_MO,  EMM_OMT_KE_DETACH_ACP_MO},
    {0,NAS_EMM_CN_MT_TAU_ACP,       NAS_EMM_TAU_ACP,        EMM_OMT_KE_TAU_ACP},
    {0,NAS_EMM_CN_MT_TAU_REJ,       NAS_EMM_TAU_REJ,        EMM_OMT_KE_TAU_REJ},
    {0,NAS_EMM_CN_MT_SER_REJ,       NAS_EMM_SER_REJ,        EMM_OMT_KE_SER_REJ},
    {0,NAS_EMM_CN_MT_GUTI_CMD,      NAS_EMM_GUTI_CMD,       EMM_OMT_KE_GUTI_CMD},
    {0,NAS_EMM_CN_MT_AUTH_REQ,      NAS_EMM_AUTH_REQ,       EMM_OMT_KE_AUTH_REQ},
    {0,NAS_EMM_CN_MT_AUTH_RSP,      NAS_EMM_AUTH_RSP,       EMM_OMT_KE_AUTH_RSP},
    {0,NAS_EMM_CN_MT_AUTH_REJ,      NAS_EMM_AUTH_REJ,       EMM_OMT_KE_AUTH_REJ},
    {0,NAS_EMM_CN_MT_IDEN_REQ,      NAS_EMM_IDEN_REQ,       EMM_OMT_KE_IDEN_REQ},
    {0,NAS_EMM_CN_MT_SMC_CMD,       NAS_EMM_SECU_CMD,       EMM_OMT_KE_SECU_CMD},
    {0,NAS_EMM_CN_MT_SMC_CMP,       NAS_EMM_SECU_CMP,       EMM_OMT_KE_SECU_CMP},
    {0,NAS_EMM_CN_MT_EMM_STATUS,    NAS_EMM_STATUS,         EMM_OMT_KE_EMM_STATUS},
    {0,NAS_EMM_CN_MT_EMM_INFO,      NAS_EMM_INFO,           EMM_OMT_KE_EMM_INFO},
    {0,NAS_EMM_CN_MT_DOWNLINK_NAS_TRANSPORT, NAS_EMM_DOWNLINK_NAS_TRANSPORT, EMM_OMT_KE_EMM_DOWNLINK_NAS_TRANSPORT},
    {0,NAS_EMM_CN_CS_SER_NOTIFICATION, NAS_EMM_CS_SER_NOTIFICATION, EMM_OMT_KE_CS_SER_NOTIFICATION}
};
VOS_UINT32 g_ulSzieof_g_stMmOmMsgIdStru = sizeof(g_stMmOmMsgIdStru);

/*niuxiufan DT begin */
APP_MM_DT_REPORT_CTRL_STRU  gastNasDtRptCtrlTbl[NAS_DT_RPT_CTRL_MAX_ITEM_NUM] = {{0}};
VOS_UINT32                  g_ulNasEmmOmMsgHookFlag = 0;
/*niuxiufan DT end */

VOS_UINT32                  g_NasEmmOmInfoIndFlag = 0;

EMM_FTM_INFO_MANAGE_STRU             g_astEmmFtmInfoManage;
EMM_DATABASE_INFO_STRU               g_astEmmInfo;

APP_MM_DT_STRU                    g_stEmmDtInfo;
NAS_LMM_OM_ENTITY_STRU g_stEmmOmEntity;
NAS_LMM_ADD_ATTACH_COUNTER_TYPE_PROC_STRU g_stEmmAddAttachCounterProcTbl[] =
{
    {NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL,               NAS_LMM_AddAttachTotalCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_SUCC,                NAS_LMM_AddAttachSuccCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_BAR,                 NAS_LMM_AddAttachBarFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_NO_RF,               NAS_LMM_AddAttachNoRfFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL,            NAS_LMM_AddAttachEstFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EXP,                 NAS_LMM_AddAttachExpFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_CN_REJ,              NAS_LMM_AddAttachRejFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_LRRC_REL,            NAS_LMM_AddAttachRelFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_ESM_FAIL,            NAS_LMM_AddAttachEsmFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL,       NAS_LMM_AddAttachDataReqFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL,         NAS_LMM_AddAttachOtherFailCounter}
};
VOS_UINT32        g_stEmmAddAttachCounterProcTblLen = sizeof(g_stEmmAddAttachCounterProcTbl)
                                                    / sizeof(NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_STRU);
/* ������: TAU���������� */
NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_STRU g_stEmmAddTauCounterProcTbl[] =
{
    {NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL,               NAS_LMM_AddTauTotalCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_SUCC,                NAS_LMM_AddTauSuccCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_BAR,                 NAS_LMM_AddTauBarFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_NO_RF,               NAS_LMM_AddTauNoRfFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL,            NAS_LMM_AddTauEstFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EXP,                 NAS_LMM_AddTauExpFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_CN_REJ,              NAS_LMM_AddTauRejFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_LRRC_REL,            NAS_LMM_AddTauRelFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL,       NAS_LMM_AddTauDataReqFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL,         NAS_LMM_AddTauOtherFailCounter}
};
VOS_UINT32        g_stEmmAddTauCounterProcTblLen = sizeof(g_stEmmAddTauCounterProcTbl)
                                                    / sizeof(NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_STRU);
/* ������: Ser���������� */
NAS_LMM_ADD_SER_COUNTER_TYPE_PROC_STRU  g_stEmmAddSerCounterProcTbl[] =
{
    {NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL,               NAS_LMM_AddSerTotalCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_SUCC,                NAS_LMM_AddSerSuccCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_BAR,                 NAS_LMM_AddSerBarFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_NO_RF,               NAS_LMM_AddSerNoRfFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL,            NAS_LMM_AddSerOtherEstFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_EXP,                 NAS_LMM_AddSerExpFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_CN_REJ,              NAS_LMM_AddSerRejFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_LRRC_REL,            NAS_LMM_AddSerRelFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_DATA_CNF_FAIL,       NAS_LMM_AddSerDataReqFailCounter},
    {NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL,         NAS_LMM_AddSerOtherFailCounter}
};
VOS_UINT32  g_stEmmAddSerCounterProcTblLen = sizeof(g_stEmmAddSerCounterProcTbl)
                                                    / sizeof(NAS_LMM_ADD_SER_COUNTER_TYPE_PROC_STRU);

LNAS_EXC_LOG_INFO_STRU  g_stLNasResetInfo;
/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_LMM_OmFindFun
 Description     : ���Ҷ�Ӧ�Ĳ�������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-4-15  Draft Enact

*****************************************************************************/


NAS_LMM_OM_ACTION_FUN  NAS_LMM_OmFindFun( VOS_UINT32          ulMsgId)
{
    VOS_UINT32                          i;
    NAS_LMM_OM_ACTION_FUN                pActFun = NAS_LMM_NULL_PTR;

    /* ��g_astNvDataMap�в��Ҷ�Ӧ��NV TYPE*/
    for(i = 0; i < g_astOmDataMapNum; i++)
    {
        /* ��NV������ͬ,���ҵ���,���ص�ǰ��NV�����������˳�ѭ�� */
        if(ulMsgId == g_astOmDataMap[i].ulMsgId)
        {
            pActFun            = g_astOmDataMap[i].pfFun;
            break;
        }
    }

    return  pActFun;
}

/*****************************************************************************
 Function Name   : NAS_LMM_OmCommFindFun
 Description     : OMͨ�õĲ��Ҷ�Ӧ�Ĳ�������
 Input           : aucActMap        : ��������׵�ַ
                   ulMapElementNum  : ������ĳ�Ա����
                   ulMsgId          : ��Ϣ����
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.h41410      2009-4-15  Draft Enact

*****************************************************************************/
NAS_LMM_OM_ACTION_FUN  NAS_LMM_OmCommFindFun
(
    const NAS_LMM_OM_ACT_STRU           *aucActMap,
    VOS_UINT32                          ulMapElementNum,
    VOS_UINT32                          ulMsgId
)
{
    VOS_UINT32                          i;
    NAS_LMM_OM_ACTION_FUN                pActFun = NAS_LMM_NULL_PTR;

    /* ��aucActMap�в��Ҷ�Ӧ�� ulMsgId */
    for(i = 0; i < ulMapElementNum; i++)
    {
        /* ��ulMsgId������ͬ,���ҵ���,���ص�ǰ��ulMsgId�����������˳�ѭ�� */
        if(ulMsgId == aucActMap[i].ulMsgId)
        {
            pActFun = aucActMap[i].pfFun;
            break;
        }
    }

    return  pActFun;
}

/*****************************************************************************
 Function Name   : NAS_LMM_OmMaintain
 Description     : OM����ά����Ϣ�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.  qilili00145085  2008-10-30  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_OmMaintain( MsgBlock            *pMsg)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSrcMsgId;
    NAS_EMM_GENERAL_MSG_HEADER_STRU    *pstSrcMsg;
    NAS_LMM_OM_ACTION_FUN                pActFun = NAS_LMM_NULL_PTR;


    ulRet                               = NAS_LMM_MSG_DISCARD;
    pstSrcMsg                           = (NAS_EMM_GENERAL_MSG_HEADER_STRU*)pMsg;
    ulSrcMsgId                          = pstSrcMsg->ulMsgId;


    pActFun = NAS_LMM_OmFindFun(ulSrcMsgId);
    if (NAS_LMM_NULL_PTR != pActFun)
    {   /* �������ҵ��ˣ���������ִ��APP������ */
        (*pActFun)(pMsg);
        ulRet = NAS_LMM_MSG_HANDLED;
    }
    else
    {
        /* ����Ҳ�������������ʾ��ǰû�иô����� */
/*        NAS_LMM_PUBM_LOG_INFO("in NAS_LMM_OmFindFun, Action functin is NOT FOUND. ");*/

    }

    return  ulRet;

}
/*****************************************************************************
 Function Name   : NAS_EMM_OmInfoIndMsgProc
 Description     : �ϱ�EMM��Ϣ�Ŀ�����Ϣ����
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2013-06-21  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_EMM_OmInfoIndMsgProc( MsgBlock    *pMsg )
{
    OM_EMM_INFO_REPORT_REQ_STRU           *pMmOmInfoReqMsg;
    OM_EMM_INFO_REPORT_CNF_STRU           *pMmOmInfoCnfMsg;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_OmInfoIndMsgProc: enter !!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_OmInfoIndMsgProc_ENUM
,LNAS_ENTRY);

    pMmOmInfoReqMsg = (OM_EMM_INFO_REPORT_REQ_STRU *)pMsg;

    if (OM_EMM_INFO_REPORT_OPEN == pMmOmInfoReqMsg->enRptCtrl)
    {
        g_NasEmmOmInfoIndFlag = OM_EMM_REPORT_INFO_OPEN;
    }
    else
    {
        g_NasEmmOmInfoIndFlag = OM_EMM_REPORT_INFO_CLOSE;

    }
    /* �������ϱ���Ϣ��ȫ�ֱ������ */
    NAS_LMM_MEM_SET_S(&g_stEmmOmInfo, sizeof(OM_EMM_STATE_INFO_STRU), 0, sizeof(OM_EMM_STATE_INFO_STRU));

    /* Ϊ��Ϣ�����ַ */
    pMmOmInfoCnfMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(OM_EMM_INFO_REPORT_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pMmOmInfoCnfMsg)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_OmInfoIndMsgProc: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_OmInfoIndMsgProc_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_MSG_HANDLED;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET_S(  pMmOmInfoCnfMsg,
                        sizeof(OM_EMM_INFO_REPORT_CNF_STRU),
                        0,
                        sizeof(OM_EMM_INFO_REPORT_CNF_STRU));


    /* �����Ϣͷ */
    pMmOmInfoCnfMsg->ulSenderCpuId = pMmOmInfoReqMsg->ulReceiverCpuId;
    pMmOmInfoCnfMsg->ulSenderPid     = pMmOmInfoReqMsg->ulReceiverPid;
    pMmOmInfoCnfMsg->ulReceiverPid   = pMmOmInfoReqMsg->ulSenderPid;
    pMmOmInfoCnfMsg->ulReceiverCpuId  = pMmOmInfoReqMsg->ulSenderCpuId;
    pMmOmInfoCnfMsg->ulLength = EMM_MSG_LENTH_NO_HEADER(OM_EMM_INFO_REPORT_CNF_STRU);
    /* OM�ںϣ�����͸����ϢCNF��REQ�е�usOriginalId��usTerminalId�����Ӧ�����ܵߵ� */
    pMmOmInfoCnfMsg->usOriginalId    = pMmOmInfoReqMsg->usOriginalId;
    pMmOmInfoCnfMsg->usTerminalId    = pMmOmInfoReqMsg->usTerminalId;
    pMmOmInfoCnfMsg->ulTimeStamp     = pMmOmInfoReqMsg->ulTimeStamp;
    pMmOmInfoCnfMsg->ulSN            = pMmOmInfoReqMsg->ulSN;


    /*����OPID*/
    pMmOmInfoCnfMsg->ulOpId      = pMmOmInfoReqMsg->ulOpId;

    /*������Ϣ����*/
    pMmOmInfoCnfMsg->ulMsgId     = ID_OM_EMM_INFO_REPORT_CNF;

    pMmOmInfoCnfMsg->ulRslt      = APP_SUCCESS;

    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pMmOmInfoCnfMsg);

    /* xiongxianghui 253310 FOR PCLINT  begin 20130926*/
    return NAS_LMM_MSG_HANDLED;
    /* xiongxianghui 253310 FOR PCLINT  end  20130926*/
}
/*****************************************************************************
 Function Name   : NAS_LMM_CompareEmmInfo
 Description     : �ж�EMMģ��ά������Ҫ�ϱ���HSO����Ϣ�Ƿ����仯
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.wangchen 00209181     2013-06-21    Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LMM_CompareEmmInfo( VOS_VOID )
{
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;
    EMM_UPDATE_STATE_ENUM_UINT32    enEmmUpState;
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32                   ulLteUeMode;

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_CompareEmmInfo: enter !!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_CompareEmmInfo_ENUM,LNAS_ENTRY);

    ulLteUeMode  = NAS_LMM_GetEmmInfoUeOperationMode();
    /* ��EMM��ǰ״̬��ȡЭ��״̬ */
    NAS_LMM_PubmGetEmmState(&ulProtoclMainState,
                            &ulProtoclSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());
    /* ��ȡEUֵ */
    NAS_LMM_PubmGetEmmUpdateState(&enEmmUpState);

    if ((ulProtoclMainState != g_stEmmOmInfo.enMainState)
        || (ulProtoclSubState != g_stEmmOmInfo.enSubState))
    {
        g_stEmmOmInfo.enMainState = ulProtoclMainState;
        g_stEmmOmInfo.enSubState = ulProtoclSubState;
        ulRst = NAS_EMM_FAIL;
    }



    if (enEmmUpState != g_stEmmOmInfo.enEmmUpState)
    {
        g_stEmmOmInfo.enEmmUpState = enEmmUpState;
        ulRst = NAS_EMM_FAIL;
    }

    /* �Ƚ�GUTI��Ϣ */
    if (NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&g_stEmmOmInfo.stGuti,
                                                    NAS_LMM_GetEmmInfoUeidGutiAddr(),
                                                    sizeof(NAS_MM_GUTI_STRU)))
    {
        NAS_LMM_MEM_CPY_S(  &g_stEmmOmInfo.stGuti,
                            sizeof(OM_GUTI_STRU),
                            NAS_LMM_GetEmmInfoUeidGutiAddr(),
                            sizeof(NAS_MM_GUTI_STRU));
        ulRst = NAS_EMM_FAIL;
    }

    /* �Ƚϼ��ܺ������Ա����㷨 */
    if ((NAS_EMM_GetSecuEca() != g_stEmmOmInfo.enAlgSecurity)
        || (NAS_EMM_GetSecuEia() != g_stEmmOmInfo.enAlgIntegrity))
    {
        g_stEmmOmInfo.enAlgSecurity = NAS_EMM_GetSecuEca();
        g_stEmmOmInfo.enAlgIntegrity = NAS_EMM_GetSecuEia();
        ulRst = NAS_EMM_FAIL;
    }

    /* �Ƚ�UE����ģʽ */
    if (ulLteUeMode != g_stEmmOmInfo.enLteUeMode)
    {
        g_stEmmOmInfo.enLteUeMode = ulLteUeMode;
        ulRst = NAS_EMM_FAIL;
    }
    return ulRst;
}


/*****************************************************************************
 Function Name   : NAS_LMM_DtCompareGuti
 Description     : �ж�EMMģ��ά������Ҫ�ϱ���·���Guti��Ϣ�Ƿ����仯
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.l00195322     2014-05-07    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_DtCompareGuti(VOS_VOID)
{
    NAS_MM_GUTI_STRU                  *pstEmmCurGuti;
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    pstEmmCurGuti                       = NAS_LMM_GetEmmInfoUeidGutiAddr();

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&g_stEmmDtInfo.stGuti,pstEmmCurGuti,
                                                 sizeof(NAS_MM_GUTI_STRU)))
    {
       ulRst = NAS_EMM_FAIL;
    }

    return ulRst;

}

/*****************************************************************************
 Function Name   : NAS_LMM_DtCompareImsi
 Description     : �ж�EMMģ��ά������Ҫ�ϱ���·���Imsi��Ϣ�Ƿ����仯
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.l00195322     2014-05-07    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_DtCompareImsi(VOS_VOID)
{
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    NAS_OM_IMSI_INFO_STRU              stImsiInfo;
    VOS_UINT8                          ucIndex;

    NAS_LMM_MEM_SET_S(  &stImsiInfo,
                        sizeof(NAS_OM_IMSI_INFO_STRU),
                        0,
                        sizeof(NAS_OM_IMSI_INFO_STRU));

    /*�����ǰ�޿�,��OM�ظ���ѯIMSIΪ��*/
    if (NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
    {

        /* ��ȡIMSI */
        stImsiInfo.ucImsiLen = (VOS_UINT8)((g_stEmmInfo.stMmUeId.aucImsi[0])*2 - 1);

        /*���һ���ֽ����4λΪF,�����IMSIΪż���� */
        if (0xF0 == (g_stEmmInfo.stMmUeId.aucImsi[g_stEmmInfo.stMmUeId.aucImsi[0]] & 0xF0))
        {
            stImsiInfo.ucImsiLen -= 1;
        }

        for(ucIndex= 0; ucIndex< stImsiInfo.ucImsiLen; ucIndex++)
        {
            if (0 == (ucIndex+1)%2)
            {
                stImsiInfo.ucImsi[ucIndex] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(ucIndex+1)/2 + 1]);
            }
            else
            {
                stImsiInfo.ucImsi[ucIndex] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(ucIndex+1)/2 + 1] >> 4);
            }
        }
    }


    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&g_stEmmDtInfo.stImsi,&stImsiInfo,
                                                 sizeof(NAS_OM_IMSI_INFO_STRU)))
    {
       ulRst = NAS_EMM_FAIL;
    }

    return ulRst;

}

/*****************************************************************************
 Function Name   : NAS_LMM_DtCompareEmmState
 Description     : �ж�EMMģ��ά������Ҫ�ϱ���·���EmmState��Ϣ�Ƿ����仯
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.l00195322     2014-05-07    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_DtCompareEmmState(VOS_VOID)
{
    VOS_UINT32                          ulRst = NAS_EMM_SUCC;
    EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;
    VOS_UINT16                           usStaTId;           /* ��ʱ����Ϣ*/

    /* ��EMM��ǰ״̬��ȡЭ��״̬ */
    NAS_LMM_PubmGetEmmState(&ulProtoclMainState,
                            &ulProtoclSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());
    /* ��ȡ��ʱ����Ϣ */
    usStaTId = (VOS_UINT16)NAS_LMM_GetEmmCurTimer();

    if ((ulProtoclMainState != g_stEmmDtInfo.stEmmState.enMainState)
        || (ulProtoclSubState != g_stEmmDtInfo.stEmmState.enSubState)
        || (usStaTId != g_stEmmDtInfo.stEmmState.usStaTId))
    {
        ulRst = NAS_EMM_FAIL;
    }

    return ulRst;

}

/*****************************************************************************
 Function Name   : NAS_LMM_DtJudgeifNeedRpt
 Description     : �ж�EMMģ��ά������Ҫ�ϱ���·�����Ϣ�Ƿ����仯
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.l00195322     2014-05-07    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_DtJudgeifNeedRpt(VOS_VOID)
{

    /*�ж��Ƿ���Ҫ�ϱ�GUTI*/
    if (NAS_DT_RPT_START== NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus)
    {
        if(NAS_EMM_FAIL == NAS_LMM_DtCompareGuti())
        {
        #if (VOS_WIN32 != VOS_OS_VER)
           /*�ϱ�GUTI��Ϣ*/
           NAS_LMM_PubmIndGuti();
        #endif

        }
    }
     /*�ж��Ƿ���Ҫ�ϱ�IMSI*/
    if (NAS_DT_RPT_START== NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus)
    {
        if(NAS_EMM_FAIL == NAS_LMM_DtCompareImsi())
        {
        #if (VOS_WIN32 != VOS_OS_VER)
           /*�ϱ�Imsi��Ϣ*/
           NAS_LMM_PubmIndImsi();
        #endif

        }
    }

    /* �ж��Ƿ���Ҫ�ϱ�EMM״̬*/
    if(NAS_DT_RPT_START== NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus)
    {
        if(NAS_EMM_FAIL == NAS_LMM_DtCompareEmmState())
        {
        #if(VOS_WIN32 != VOS_OS_VER)
           /*�ϱ�EMM״̬*/
           NAS_LMM_PubmIndEmmState();
        #endif
        }
    }
    return;
}



VOS_VOID  NAS_LMM_SetAppParaValue
(
    NAS_LMM_APP_PARA_SET_RESLT_STRU      *pstParaInfo,
    const NAS_LMM_APP_PARA_SET_HEAD_STRU       *pstAppMsg
)
{
    pstParaInfo->ulOpId                 = pstAppMsg->ulOpId;

    /*����MID����*/
    pstParaInfo->usOriginalId = pstAppMsg->usOriginalId;
    pstParaInfo->usTerminalId = pstAppMsg->usTerminalId;
    pstParaInfo->ulTimeStamp  = pstAppMsg->ulTimeStamp;

    /*����SN����*/
    pstParaInfo->ulSN = pstAppMsg->ulSN;
    return;
}


VOS_VOID NAS_EMM_SendIntraTauReq
(
    APP_MM_MSG_TYPE_ENUM_UINT32         ulOmMmMsgType,
    NAS_LMM_INTRA_TAU_TYPE_ENUM_UINT32  enIntraTauType
)
{
    VOS_UINT32                          ulMsgLenthNoHeader;
    NAS_LMM_INTRA_TAU_REQ_STRU           *pEmmIntraTauReq;
/*    VOS_UINT32                          ulRst;*/

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SendIntraTauReq is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendIntraTauReq_ENUM
,LNAS_ENTRY);

     /* ����EMMҪ����OM����Ϣ����, ������VOSͷ */
    ulMsgLenthNoHeader = EMM_MSG_LENTH_NO_HEADER(NAS_LMM_INTRA_TAU_REQ_STRU);

    /* ����DOPRA��Ϣ */
    /*lint -e433 -e826*/
    pEmmIntraTauReq = (VOS_VOID *)NAS_LMM_GetSendIntraMsgBuffAddr(ulMsgLenthNoHeader);
    /*lint +e433 +e826*/

    if(NAS_LMM_NULL_PTR  == pEmmIntraTauReq)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SendIntraTauReq: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SendIntraTauReq_ENUM
,LNAS_NULL_PTR);
        return;
    }

    /* �����Ϣͷ */
    NAS_EMM_COMP_INTRA_MSG_HEADER(      pEmmIntraTauReq,
                                        ulMsgLenthNoHeader);


    /* ��д��ϢID */
    pEmmIntraTauReq->ulMsgId            = ID_NAS_LMM_INTRA_TAU_REQ;

    pEmmIntraTauReq->ulOmMsgType        = ulOmMmMsgType;

    pEmmIntraTauReq->enIntraTauType     = enIntraTauType;

    /* ������Ϣ */
    /*
    ulRst = NAS_LMM_SendIntraMsg(        pEmmIntraTauReq);
    if(NAS_EMM_SUCC != ulRst)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendIntraTauReq: SendIntraMsg ERR !!");
    }
    */
    NAS_EMM_SEND_INTRA_MSG(             pEmmIntraTauReq);

    return;

}



/*****************************************************************************
 Function Name  : IMSA_ReadImsaNvImsCapability()
 Description    : ��ȡIMS����������Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leili 00132387      2013-10-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_ReadImsaNvImsCapability( VOS_UINT8 *pucSmsOverIms, VOS_UINT8 *pucSrvcc)
{
    IMS_NV_IMS_CAP_STRU             stNvImsCapability;
    VOS_UINT32                      ulRslt;
    /*lint -e718*/
    /*lint -e732*/
    /*lint -e516*/
    ulRslt = LPs_NvimItem_Read(EN_NV_ID_IMS_CAPABILITY,&stNvImsCapability,\
                 sizeof(IMS_NV_IMS_CAP_STRU));
    /*lint +e516*/
    /*lint +e732*/
    /*lint +e718*/

    if(ulRslt == VOS_OK)
    {
        /*����NV��������*/
        *pucSmsOverIms = stNvImsCapability.ucSmsOnImsSupportFlag;
        *pucSrvcc = stNvImsCapability.ucSrvccOnImsSupportFlag;

    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("IMSA_ReadImsaNvImsCapability: read NV err!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ReadImsaNvImsCapability_ENUM
,LNAS_ERROR);

        /*���ó�ʼֵ*/
        *pucSmsOverIms = VOS_TRUE;
        *pucSrvcc = VOS_TRUE;
    }

}

/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqLteCs
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY        2012-02-17    Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqLteCs(MsgBlock *pMsg)
{
    APP_MM_INQ_LTE_CS_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_LTE_CS_CNF_STRU      *pstAppInqCnf;
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt;

    enAddUpdateRslt = NAS_EMM_GetAddUpdateRslt();

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqLteCs: enter");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_ENTRY);

    pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* Ϊ��Ϣ�����ַ */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_LTE_CS_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqLteCs: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_NULL_PTR);
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET_S(  pstAppInqCnf,
                        sizeof(APP_MM_INQ_LTE_CS_CNF_STRU),
                        0,
                        sizeof(APP_MM_INQ_LTE_CS_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_LTE_CS_CNF_STRU),
                                pstAppInqReq);

    /*����OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*������Ϣ����*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_LTE_CS_CNF;

    pstAppInqCnf->ulRslt      = APP_SUCCESS;

    if(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: REG domain  NAS_LMM_REG_DOMAIN_CS_PS!!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_FUNCTION_LABEL1);
        pstAppInqCnf->stLtecsInfo.ucSmsOverSGs = NAS_LMM_LTE_CS_SERVICE_SUPPORT;

        if(NAS_LMM_ADDITIONAL_UPDATE_BUTT == enAddUpdateRslt)
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: Addition Update Result not exist!!");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_FUNCTION_LABEL2);
            pstAppInqCnf->stLtecsInfo.ucCSFB = NAS_LMM_LTE_CS_SERVICE_SUPPORT;
        }
        else
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: Addition Update Resultsexist!!");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_FUNCTION_LABEL3);
            /*lint -e960*/
            if((NAS_LMM_ADDITIONAL_UPDATE_CSFB_NOT_PREFERED == enAddUpdateRslt) ||
                (NAS_LMM_ADDITIONAL_UPDATE_NO_INFO == enAddUpdateRslt))
            /*lint +e960*/
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PubmDaInqLteCs: Addition Update Result is NO_INFO or CSFB_NOT_PREFERED!!");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_PubmDaInqLteCs_ENUM,LNAS_FUNCTION_LABEL4);
                pstAppInqCnf->stLtecsInfo.ucCSFB = NAS_LMM_LTE_CS_SERVICE_SUPPORT;
            }
        }
    }
    NAS_LMM_ReadImsaNvImsCapability(&pstAppInqCnf->stLtecsInfo.ucSmsOverIMS,&pstAppInqCnf->stLtecsInfo.ucSrVcc);

    /* ������Ϣ */
    /*lint -e960*/
    NAS_LMM_SEND_MSG(pstAppInqCnf);
    /*lint +e960*/

    return;
}


/* niuxiufan DT begin */
/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqGuti
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.niuxiufan 00181501        2012-09-07    Draft Enact
    2.l00195322                 2014-4-23,  CNFֻ�ϱ��ɹ���ʧ�ܣ�IND�ϱ���Ϣ����

*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqGuti(MsgBlock *pMsg)
{
    APP_MM_INQ_LTE_GUTI_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_LTE_GUTI_CNF_STRU      *pstAppInqCnf;

    pstAppInqReq                       = (VOS_VOID *)pMsg;


    /* ���������ж��Ƿ�ֹͣGUTI�ϱ� */
    if (DT_CMD_STOP == pstAppInqReq->enCmd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: START");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqGuti_ENUM
,LNAS_FUNCTION_LABEL1);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus = NAS_DT_RPT_STOP;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqGuti_ENUM
,LNAS_FUNCTION_LABEL2);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enDtRptItem = NAS_DT_REPORT_TYPE_GUTI;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus = NAS_DT_RPT_START;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptType = APP_MM_RM_AUTO;
    }

    /* Ϊ��Ϣ�����ַ */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_LTE_GUTI_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqGuti_ENUM
,LNAS_NULL_PTR);
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET_S(  pstAppInqCnf,
                        sizeof(APP_MM_INQ_LTE_GUTI_CNF_STRU),
                        0,
                        sizeof(APP_MM_INQ_LTE_GUTI_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_CNF_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_LTE_GUTI_CNF_STRU),
                                pstAppInqReq);

    /*����OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*������Ϣ����*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_LTE_GUTI_CNF;

    pstAppInqCnf->ulRslt      = APP_SUCCESS;

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppInqCnf);
    }
#endif


    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppInqCnf);

    NAS_LMM_PubmIndGuti();

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqImsi
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.niuxiufan 00181501        2012-09-07    Draft Enact
    2.l00195322                 2014-4-23,  CNFֻ�ϱ��ɹ���ʧ�ܣ�IND�ϱ���Ϣ����
*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqImsi(MsgBlock *pMsg)
{
    APP_MM_INQ_IMSI_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_IMSI_CNF_STRU      *pstAppInqCnf;

    pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* ���������ж��Ƿ�ֹͣIMSI�ϱ� */
    /* chengmin 00285307 �޸����� begin */
    if (DT_CMD_STOP == pstAppInqReq->enCmd)
    /* chengmin 00285307 �޸����� end */
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqImsi: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqImsi_ENUM
,LNAS_FUNCTION_LABEL1);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus = NAS_DT_RPT_STOP;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqImsi: START");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqImsi_ENUM
,LNAS_FUNCTION_LABEL2);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enDtRptItem = NAS_DT_REPORT_TYPE_IMSI;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus = NAS_DT_RPT_START;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptType = APP_MM_RM_AUTO;
    }

    /* Ϊ��Ϣ�����ַ */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_IMSI_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqImsi: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqImsi_ENUM
,LNAS_NULL_PTR);
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET_S(  pstAppInqCnf,
                        sizeof(APP_MM_INQ_IMSI_CNF_STRU),
                        0,
                        sizeof(APP_MM_INQ_IMSI_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_CNF_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_IMSI_CNF_STRU),
                                pstAppInqReq);

    /*����OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*������Ϣ����*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_IMSI_CNF;
    pstAppInqCnf->ulRslt      = APP_SUCCESS;

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppInqCnf);
    }
#endif
    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppInqCnf);

    NAS_LMM_PubmIndImsi();

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqEmmState
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.niuxiufan 00181501        2012-09-07    Draft Enact
    2.l00195322                 2014-4-23,  CNFֻ�ϱ��ɹ���ʧ�ܣ�IND�ϱ���Ϣ����

*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqEmmState(MsgBlock *pMsg)
{
    APP_MM_INQ_EMM_STATE_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_EMM_STATE_CNF_STRU      *pstAppInqCnf;

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: enter");
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqEmmState_ENUM
,LNAS_FUNCTION_LABEL1);

    pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* ���������ж��Ƿ�ֹͣEMM State�ϱ� */
    if (DT_CMD_STOP == pstAppInqReq->enCmd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqEmmState_ENUM
,LNAS_FUNCTION_LABEL2);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus = NAS_DT_RPT_STOP;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: START");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqEmmState_ENUM
,LNAS_FUNCTION_LABEL3);
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enDtRptItem = NAS_DT_REPORT_TYPE_EMM_STATE;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus = NAS_DT_RPT_START;
        NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptType = APP_MM_RM_AUTO;
    }

    /* Ϊ��Ϣ�����ַ */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_EMM_STATE_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqEmmState: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqEmmState_ENUM
,LNAS_FUNCTION_LABEL4);
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET_S(  pstAppInqCnf,
                        sizeof(APP_MM_INQ_EMM_STATE_CNF_STRU),
                        0,
                        sizeof(APP_MM_INQ_EMM_STATE_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_CNF_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_EMM_STATE_CNF_STRU),
                                pstAppInqReq);

    /*����OPID*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;

    /*������Ϣ����*/
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_EMM_STATE_CNF;

    pstAppInqCnf->ulRslt      = APP_SUCCESS;

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppInqCnf);
    }
#endif

    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppInqCnf);

    NAS_LMM_PubmIndEmmState();

    return;
}

VOS_VOID  NAS_LMM_PubmIndGuti(VOS_VOID)
{
    APP_MM_INQ_LTE_GUTI_IND_STRU      *pstAppGutiInd;
    NAS_MM_GUTI_STRU                  *pstEmmCurGuti;

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndGuti: enter");
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndGuti_ENUM
,LNAS_ENTRY);

    /* ���������ж��Ƿ�ֹͣGUTI�ϱ� */
    if (NAS_DT_RPT_STOP == NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_GUTI)->enRptStatus)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndGuti: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndGuti_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }

    /* Ϊ��Ϣ�����ַ */
    pstAppGutiInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_LTE_GUTI_IND_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppGutiInd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqGuti: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndGuti_ENUM
,LNAS_FUNCTION_LABEL2);
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET_S(  pstAppGutiInd,
                        sizeof(APP_MM_INQ_LTE_GUTI_IND_STRU),
                        0,
                        sizeof(APP_MM_INQ_LTE_GUTI_IND_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_IND_MSG_HEADER( pstAppGutiInd,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_LTE_GUTI_IND_STRU));

    /*���APP��Ϣͷ*/
    EMM_COMP_OMT_APP_MSG_HEADER( pstAppGutiInd);

    /*������Ϣ����*/
    pstAppGutiInd->ulMsgId     = ID_APP_MM_INQ_LTE_GUTI_IND;
    pstAppGutiInd->ulOpId      = DIAG_CMD_EMM_APP_GUTI_INFO_IND;


    /* ��ȡGUTI */
    pstEmmCurGuti                       = NAS_LMM_GetEmmInfoUeidGutiAddr();
    NAS_LMM_MEM_CPY_S(  &pstAppGutiInd->stGuti,
                        sizeof(APP_GUTI_STRU),
                        pstEmmCurGuti,
                        sizeof(NAS_LMM_GUTI_STRU));

    /*����GUTI��Ϣ��ȫ�ֱ���*/
    NAS_LMM_MEM_CPY_S(  &g_stEmmDtInfo.stGuti,
                        sizeof(NAS_MM_GUTI_STRU),
                        pstEmmCurGuti,
                        sizeof(NAS_MM_GUTI_STRU));

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppGutiInd);
    }
#endif
    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppGutiInd);
    return;
}

VOS_VOID  NAS_LMM_PubmIndImsi(VOS_VOID)
{
    APP_MM_INQ_IMSI_IND_STRU      *pstAppImsiInd;
    NAS_OM_IMSI_INFO_STRU          stImsiInfo;
    VOS_UINT8                      i;

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndImsi: enter");
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndImsi_ENUM
,LNAS_ENTRY);


    /* ���������ж��Ƿ�ֹͣIMSI�ϱ� */
    if (NAS_DT_RPT_STOP == NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_IMSI)->enRptStatus)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndImsi: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndImsi_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }

    /* Ϊ��Ϣ�����ַ */
    pstAppImsiInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_IMSI_IND_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppImsiInd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndImsi: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndImsi_ENUM
,LNAS_FUNCTION_LABEL2);
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET_S(  pstAppImsiInd,
                        sizeof(APP_MM_INQ_IMSI_IND_STRU),
                        0,
                        sizeof(APP_MM_INQ_IMSI_IND_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_IND_MSG_HEADER( pstAppImsiInd,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_IMSI_IND_STRU));

    /*���APP��Ϣͷ*/
    EMM_COMP_OMT_APP_MSG_HEADER( pstAppImsiInd);

    /*������Ϣ����*/
    pstAppImsiInd->ulMsgId     = ID_APP_MM_INQ_IMSI_IND;
    pstAppImsiInd->ulOpId      = DIAG_CMD_EMM_APP_IMSI_INFO_IND;


    NAS_LMM_MEM_SET_S(  &stImsiInfo,
                        sizeof(NAS_OM_IMSI_INFO_STRU),
                        0,
                        sizeof(NAS_OM_IMSI_INFO_STRU));

    /*�����ǰ�޿�,��OM�ظ���ѯIMSIΪ��*/
    if (NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
    {

        /* ��ȡIMSI */
        stImsiInfo.ucImsiLen = (VOS_UINT8)((g_stEmmInfo.stMmUeId.aucImsi[0])*2 - 1);

        /*���һ���ֽ����4λΪF,�����IMSIΪż���� */
        if (0xF0 == (g_stEmmInfo.stMmUeId.aucImsi[g_stEmmInfo.stMmUeId.aucImsi[0]] & 0xF0))
        {
            stImsiInfo.ucImsiLen -= 1;
        }

        for(i = 0; i < stImsiInfo.ucImsiLen; i++)
        {
            if (0 == (i+1)%2)
            {
                stImsiInfo.ucImsi[i] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(i+1)/2 + 1]);
            }
            else
            {
                stImsiInfo.ucImsi[i] = 0x0F & (g_stEmmInfo.stMmUeId.aucImsi[(i+1)/2 + 1] >> 4);
            }
        }
    }

    NAS_LMM_MEM_CPY_S( &pstAppImsiInd->stImsi,
                        sizeof(NAS_OM_IMSI_INFO_STRU),
                        &stImsiInfo,
                        sizeof(NAS_OM_IMSI_INFO_STRU));

    /*����IMSI��Ϣ��ȫ�ֱ���*/
    NAS_LMM_MEM_CPY_S(  &g_stEmmDtInfo.stImsi,
                        sizeof(NAS_OM_IMSI_INFO_STRU),
                        &stImsiInfo,
                        sizeof(NAS_OM_IMSI_INFO_STRU));

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppImsiInd);
    }
#endif
    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppImsiInd);

    return;
}

VOS_VOID  NAS_LMM_PubmIndEmmState(VOS_VOID)
{
    APP_MM_INQ_EMM_STATE_IND_STRU      *pstAppEmmStateInd;
    NAS_OM_EMM_STATE_STRU               stEmmPtlState = {0};

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndEmmState: enter");
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndEmmState_ENUM
,LNAS_ENTRY);


    /* ���������ж��Ƿ�ֹͣEMM State�ϱ� */
    if (NAS_DT_RPT_STOP == NAS_EMM_GetNasDtRptCtrlItem(NAS_DT_REPORT_TYPE_EMM_STATE)->enRptStatus)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndEmmState: STOP");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndEmmState_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }


    /* Ϊ��Ϣ�����ַ */
    pstAppEmmStateInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_EMM_STATE_IND_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppEmmStateInd)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmIndEmmState: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmIndEmmState_ENUM
,LNAS_FUNCTION_LABEL2);
        return;
    }


    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET_S(  pstAppEmmStateInd,
                        sizeof(APP_MM_INQ_EMM_STATE_IND_STRU),
                        0,
                        sizeof(APP_MM_INQ_EMM_STATE_IND_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_DT_IND_MSG_HEADER( pstAppEmmStateInd,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_EMM_STATE_IND_STRU));

    /*���APP��Ϣͷ*/
    EMM_COMP_OMT_APP_MSG_HEADER( pstAppEmmStateInd);


    /*������Ϣ����*/
    pstAppEmmStateInd->ulMsgId     = ID_APP_MM_INQ_EMM_STATE_IND;
    pstAppEmmStateInd->ulOpId      = DIAG_CMD_EMM_APP_EMM_STATE_IND;

    /* ��ȡЭ��״̬��Ϣ */
    NAS_LMM_PubmGetEmmState(&(stEmmPtlState.enMainState),
                           &(stEmmPtlState.enSubState),
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());

    stEmmPtlState.usStaTId = (VOS_UINT16)NAS_LMM_GetEmmCurTimer();

    /* coverity[uninit_use_in_call] */
    NAS_LMM_MEM_CPY_S(  &pstAppEmmStateInd->stEmmState,
                        sizeof(NAS_OM_EMM_STATE_STRU),
                        &stEmmPtlState,
                        sizeof(NAS_OM_EMM_STATE_STRU));

    /*Э��״̬��Ϣ������ȫ�ֱ���*/
    /* coverity[uninit_use_in_call] */
    NAS_LMM_MEM_CPY_S(  &g_stEmmDtInfo.stEmmState,
                        sizeof(NAS_OM_EMM_STATE_STRU),
                        &stEmmPtlState,
                        sizeof(NAS_OM_EMM_STATE_STRU));

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEmmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAppEmmStateInd);
    }
#endif
    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppEmmStateInd);
    return;
}

/* niuxiufan DT end */



/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaInqUeMode
 Description     :
 Input           : MsgBlock    *pMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.FTY        2012-02-17    Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_PubmDaInqUeMode(MsgBlock *pMsg)
{
    APP_MM_INQ_UE_MODE_REQ_STRU      *pstAppInqReq;
    APP_MM_INQ_UE_MODE_CNF_STRU      *pstAppInqCnf;

    pstAppInqReq                       = (VOS_VOID *)pMsg;

    /* Ϊ��Ϣ�����ַ */
    pstAppInqCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(APP_MM_INQ_UE_MODE_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstAppInqCnf)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqUeMode: NAS_LMM_ALLOC_MSG alloc NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqUeMode_ENUM
,LNAS_ENTRY);
        return;
    }

    /*lint -e960*/

    /* �ṹ��ʼ�� */
    NAS_LMM_MEM_SET_S(  pstAppInqCnf,
                        sizeof(APP_MM_INQ_UE_MODE_CNF_STRU),
                        0,
                        sizeof(APP_MM_INQ_UE_MODE_CNF_STRU));

    /* �����Ϣͷ */
    EMM_COMP_APP_MSG_VOS_HEADER(pstAppInqCnf,
                                EMM_MSG_LENTH_NO_HEADER(APP_MM_INQ_UE_MODE_CNF_STRU),
                                pstAppInqReq);

    /*������Ϣ��*/
    pstAppInqCnf->ulOpId      = pstAppInqReq->ulOpId;
    pstAppInqCnf->ulMsgId     = ID_APP_MM_INQ_UE_MODE_CNF;
    pstAppInqCnf->ulRslt      = APP_SUCCESS;
    pstAppInqCnf->enCurrentUeMode = NAS_LMM_GetEmmInfoUeOperationMode();
    /*��ǰUE֧��CS\PS��PSģʽ����������Ϊ2*/
    pstAppInqCnf->ulSupportModeCnt = 2;
    if(EMM_SETTING_DATA_CENTRIC == NAS_LMM_GetEmmInfoUeCenter())
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqUeMode: UE Center is DATA_CENTRIC!!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqUeMode_ENUM
,LNAS_FUNCTION_LABEL1);
        pstAppInqCnf->aenSupportModeList[0] = NAS_LMM_UE_PS_MODE_2;
        pstAppInqCnf->aenSupportModeList[1] = NAS_LMM_UE_CS_PS_MODE_2;

    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_PubmDaInqUeMode: UE Center is VOICE_CENTRIC!!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_PubmDaInqUeMode_ENUM
,LNAS_FUNCTION_LABEL2);
        pstAppInqCnf->aenSupportModeList[0] = NAS_LMM_UE_PS_MODE_1;
        pstAppInqCnf->aenSupportModeList[1] = NAS_LMM_UE_CS_PS_MODE_1;
    }

    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstAppInqCnf);
    /*lint +e960*/

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PubmGetEmmState
 Description     : ��ȡЭ��״̬
 Input           : APP_EMM_MAIN_STATE_ENUM_UINT32      *pulProtoclMainState
                   APP_EMM_SUB_STATE_ENUM_UINT32       *pulProtoclSubState
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2009-3-20  Draft Enact
    2.lifuxin 00253982      2014-10-31 ���������ع�

*****************************************************************************/
VOS_VOID    NAS_LMM_PubmGetEmmState
(
    APP_EMM_MAIN_STATE_ENUM_UINT16      *pulProtoclMainState,
    APP_EMM_SUB_STATE_ENUM_UINT16       *pulProtoclSubState,
    NAS_LMM_MAIN_STATE_ENUM_UINT16      enMainState,
    NAS_LMM_SUB_STATE_ENUM_UINT16       enSubState
)
{
    APP_EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    APP_EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;
    VOS_UINT32                          ulLoop;

    NAS_LMM_FSM_STATE_STACK_STRU         *pstFsmStack;        /* ״̬��ջ��ַ */
    NAS_LMM_FSM_STATE_STRU               *pstFsmStackTop;     /* ָ��ջ��״̬ */


    /* ��ʼ��Э��״̬ */
    ulProtoclMainState                  = APP_EMM_MS_NULL;
    ulProtoclSubState                   = APP_EMM_SS_NULL;


    /* ���ӽ�������,�ͷŹ���,��Ȩ���� ��Ҫ��״̬ջ��ȡ״̬ */
    /*add by lifuxin for Lnas est&rel process re-construct*/
    if(EMM_MS_AUTH_INIT == enMainState)
    {
        /* ��ȡ״̬ջջ����ַ */
        pstFsmStack
            =  NAS_LMM_GetFsmStackAddr(NAS_LMM_PARALLEL_FSM_EMM);
        pstFsmStackTop
            = &((pstFsmStack->astFsmStack)[pstFsmStack->ucStackDepth - 1]);

        /* ��״̬ջ��ȡ״̬ */
        enMainState                     = pstFsmStackTop->enMainState;
        enSubState                      = pstFsmStackTop->enSubState;
    }

    /*��������� */
    if (EMM_MS_SUSPEND == enMainState)
    {
        enMainState = NAS_EMM_GetMsBefSuspend();
        enSubState = NAS_EMM_GetSsBefSuspend();
    }

    if (EMM_MS_RESUME == enMainState)
    {
        if (EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND == enSubState)
        {
            enMainState = NAS_EMM_GetMsBefResume();
            enSubState = NAS_EMM_GetSsBefResume();
        }
        else
        {
            if ((NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL == NAS_EMM_GetResumeType())
                || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO == NAS_EMM_GetResumeType())
                || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO == NAS_EMM_GetResumeType())
                || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR == NAS_EMM_GetResumeType()))
            {
                enMainState = NAS_EMM_GetMsBefSuspend();
                enSubState = NAS_EMM_GetSsBefSuspend();
            }
            else
            {
                enMainState = NAS_EMM_GetMsBefResume();
                enSubState = NAS_EMM_GetSsBefResume();
            }
        }
    }

    /* ����״̬ӳ����ȡЭ��״̬ */
    for (ulLoop = 0; ulLoop< g_ulProtocolStateMapNum; ulLoop++)
    {
        if ( (enMainState == g_astProtocolStateMap[ulLoop].enMainState)
            &&((enSubState == g_astProtocolStateMap[ulLoop].enSubState)
              || (MM_SS_BUTT == g_astProtocolStateMap[ulLoop].enSubState)) )
        {
            /*lint -e960*/
            ulProtoclMainState
                = g_astProtocolStateMap[ulLoop].ulProtoclMainState;
            ulProtoclSubState
                = g_astProtocolStateMap[ulLoop].ulProtoclSubState;
            break;
            /*lint +e960*/
        }
    }

    /* ��ֵ��� */
    *pulProtoclMainState                = ulProtoclMainState;
    *pulProtoclSubState                 = ulProtoclSubState;

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PubmGetEmmUpdateState
 Description     : ��ȡEMM����״̬
 Input           : APP_EMM_UPDATE_STATE_ENUM_UINT32    *pulEmmUpState
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2009-3-20  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_PubmGetEmmUpdateState
(
    APP_EMM_UPDATE_STATE_ENUM_UINT32    *pulEmmUpState
)
{
    *pulEmmUpState                      =  NAS_EMM_UPDATE_STAE;

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_PubmGetAreaInfo
 Description     : ��ȡGUTI,TA�б�,��ǰTA
 Input           : APP_GUTI_STRU                       *pstGuti
                   APP_TA_LIST_STRU                    *pstTaiList
                   APP_TA_STRU                         *pstLastTa
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2009-3-20  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_PubmGetAreaInfo
(
    APP_GUTI_STRU                       *pstGuti,
    APP_TA_LIST_STRU                    *pstTaiList,
    APP_TA_STRU                         *pstLastTa
)
{
    NAS_MM_GUTI_STRU                    *pstEmmCurGuti;
    NAS_MM_TA_LIST_STRU                 *pstEmmCurTaiList;
    NAS_MM_NETWORK_ID_STRU              *pstEmmCurNetId;

    /* ��ȡGUTI */
    pstEmmCurGuti                       = NAS_LMM_GetEmmInfoUeidGutiAddr();

    /*lint -e960*/

    NAS_LMM_MEM_CPY_S(  pstGuti,
                        sizeof(APP_GUTI_STRU),
                        pstEmmCurGuti,
                        sizeof(NAS_LMM_GUTI_STRU));

    /* ��ȡTAI�б� */
    pstEmmCurTaiList                    = NAS_LMM_GetEmmInfoNetInfoTaiListAddr();
    NAS_LMM_MEM_CPY_S(  pstTaiList,
                        sizeof(APP_TA_LIST_STRU),
                        pstEmmCurTaiList,
                        sizeof(NAS_MM_TA_LIST_STRU));

    /* ��ȡTA */
    pstEmmCurNetId                      = NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr();
    NAS_LMM_MEM_CPY_S(  &pstLastTa->stPlmnId,
                        sizeof(APP_PLMN_ID_STRU),
                        &pstEmmCurNetId->stPlmnId,
                        sizeof(NAS_MM_PLMN_ID_STRU));
    NAS_LMM_MEM_CPY_S(  &pstLastTa->stTac,
                        sizeof(APP_TAC_STRU),
                        &pstEmmCurNetId->stTac,
                        sizeof(NAS_MM_TAC_STRU));

    /*lint +e960*/

    return;

}


/*****************************************************************************
 Function Name   : NAS_LMM_PubmGetEmmInfo
 Description     : ��ȡ�ƶ�����Ϣ
 Input           : APP_EMM_INFO_STRU        *pstEmmInfoCnf
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian 00107747      2009-3-20  Draft Enact
    2.yangfan 00159566      2010-5-11  Modify

*****************************************************************************/
VOS_VOID    NAS_LMM_PubmGetEmmInfo
(
    APP_EMM_INFO_STRU                   *pstEmmInfoCnf
)
{
    /* ��ȡЭ��״̬��Ϣ */
    NAS_LMM_PubmGetEmmState(&(pstEmmInfoCnf->ulMainState),
                           &(pstEmmInfoCnf->ulSubState),
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());
    /* ��ȡEMM update״̬ */
    NAS_LMM_PubmGetEmmUpdateState(&(pstEmmInfoCnf->ulEmmUpState));

    /* ��ȡ GUTI,TaiList,Last Ta */
    NAS_LMM_PubmGetAreaInfo(&(pstEmmInfoCnf->stGuti),
                           &(pstEmmInfoCnf->stTaiList),
                           &(pstEmmInfoCnf->stLastTa));

}

/*****************************************************************************
 Function Name  : Nas_Emm_SendOmtKeyEvent
 Discription    : ��OMT���͹ؼ��¼�
 Input          :
 Output         : None
 Return         : None
 History:
      1.  qilili00145085  2008-10-30  Draft Enact
      2.  z00138739        2009-5-22  Modify, BJ9D00871
*****************************************************************************/
VOS_VOID    NAS_LMM_SendOmtKeyEvent(     PS_EMM_OMT_KEY_EVENT_TYPE_ENUM_UINT8
                                        ucEmmOmtKeyEvent  )
{
    /*z00282933, ��ģOM�ں���� - BEGIN*/
#if (VOS_WIN32 != VOS_OS_VER)
    DIAG_EVENT_IND_STRU stDiagEventInd;

#ifndef PS_ITT_PC_TEST
    NAS_LMM_MEM_SET_S(  &stDiagEventInd,
                        sizeof(DIAG_EVENT_IND_STRU),
                        0,
                        sizeof(DIAG_EVENT_IND_STRU));

    stDiagEventInd.ulModule = LPS_OM_ID(UE_MODULE_MM_ID, DIAG_LOG_TYPE_INFO);
    stDiagEventInd.ulPid = UE_MODULE_MM_ID;
    stDiagEventInd.ulEventId = (VOS_UINT32)(ucEmmOmtKeyEvent+OM_PS_KEY_EVENT_BASE_ID);

    /*lint -e778*/
    /*lint -e648*/
    if(ERR_MSP_SUCCESS != LDRV_DIAG_EVENTREPORT(&stDiagEventInd))
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_SendOmtKeyEvent: Send Msg Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_SendOmtKeyEvent_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }
    /*lint +e648*/
    /*lint +e778*/
#endif

#endif
    /*z00282933, ��ģOM�ں���� - END*/
}


/*****************************************************************************
 Function Name  : NAS_LMM_SendOmtAirMsg
 Discription    : ��OMT���Ϳտ���Ϣ
 Input          : ulDir,
                  ulAirMsgId
                  pstNasMsg
 Output         : None
 Return         : None
 History:
      1.  qilili00145085  2008-10-30  Draft Enact
      2.  z00138739        2009-5-22  Modify, BJ9D00871
*****************************************************************************/
VOS_VOID    NAS_LMM_SendOmtAirMsg(       NAS_LMM_OM_AIR_MSG_UP_DOWN_ENUM_UINT8  ucDir,
                                        NAS_LMM_OM_AIR_MSG_ID_ENUM_UINT8       ucAirMsgId,
                                        NAS_MSG_STRU                       *pstNasMsg)
{
#ifndef PS_ITT_PC_TEST
    /*z00282933, ��ģOM�ں���� - BEGIN*/
    DIAG_AIR_IND_STRU        stAirMsg;
    /*z00282933, ��ģOM�ں���� - END*/
    VOS_UINT8                   *pucTmpData = VOS_NULL_PTR;

    /*����տ���Ϣ�ռ�*/
    pucTmpData = (VOS_UINT8*)
                        NAS_LMM_MEM_ALLOC(pstNasMsg->ulNasMsgSize);

    if(VOS_NULL_PTR== pucTmpData)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SendOmtAirMsg: MEM_ALLOC ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendOmtAirMsg_ENUM
,LNAS_NULL_PTR);
        return;
    }

    /*lint -e960*/

    NAS_LMM_MEM_CPY_S( (pucTmpData),
                        (pstNasMsg->ulNasMsgSize),
                        (pstNasMsg->aucNasMsg),
                        (pstNasMsg->ulNasMsgSize));

    /*z00282933, ��ģOM�ں���� - BEGIN*/
    /*�տ���Ϣ��ֵ*/
    if(NAS_EMM_OMT_AIR_MSG_UP == ucDir)
    {
        stAirMsg.ulModule = DIAG_AIR_MSG_LOG_ID(PS_PID_MM, OS_MSG_UL);
        stAirMsg.ulPid = PS_PID_MM;
        stAirMsg.ulDirection = DIAG_SIDE_NET;
    }
    else
    {
        stAirMsg.ulModule = DIAG_AIR_MSG_LOG_ID(PS_PID_MM, OS_MSG_DL);
        stAirMsg.ulPid = PS_PID_MM;
        stAirMsg.ulDirection = DIAG_SIDE_UE;
    }
    stAirMsg.ulMsgId = (VOS_UINT32)(ucAirMsgId+ PS_MSG_ID_AIR_BASE);
    stAirMsg.ulLength = pstNasMsg->ulNasMsgSize;
    stAirMsg.pData = (void*)pucTmpData;

    /*�ϱ��տ���Ϣ*/
    if(ERR_MSP_SUCCESS != LDRV_DIAG_AIRMSGREPORT(&stAirMsg))
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_SendOmtAirMsg: Send Msg Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_SendOmtAirMsg_ENUM,LNAS_FAIL);
    }
    /*z00282933, ��ģOM�ں���� - END*/

    /*�ͷ��ڴ�ռ�*/
    NAS_LMM_MEM_FREE(pucTmpData);
    /*lint +e960*/

#endif
    (VOS_VOID)(pstNasMsg);
}


VOS_VOID   NAS_LMM_FindAirMsgId( VOS_UINT8 ucCnMsgType,
                                VOS_UINT8 *pucAirMsg,
                                VOS_UINT8 *pucKeyEvent)
{
    VOS_UINT8 i;
    VOS_UINT8 ucLen;
    ucLen = sizeof(g_stMmOmMsgIdStru)/(sizeof(NAS_LMM_OM_MSG_ID_CHANGE_STRU));
    for(i = 0;i < ucLen;i++)
    {
        /*lint -e960*/
        if (ucCnMsgType == g_stMmOmMsgIdStru[i].enCnMsgType)
        {
            *pucAirMsg   = g_stMmOmMsgIdStru[i].enAirMsg;
            *pucKeyEvent = g_stMmOmMsgIdStru[i].enKeyEvent;
            break;
        }
        /*lint +e960*/
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PubmDaSetCnf
 Description     : �����������APP��Ӧ���
 Input           : None
 Output          : None
 Return          : ulMsgId  : ��Ӧ��Ϣ������
                   ucRst    : ���ý��
                   pReqMsg  : ָ��APP������������REQ��Ϣ, ���ڻ�ȡAPPͷ�е�����

 History         :
    1.h41410      2009-4-14  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_PubmDaSendSetCnf( const NAS_LMM_APP_PARA_SET_RESLT_STRU *pstAppRslt )
{

    APP_MM_SET_CMD_CNF_STRU            *pstEmmSetCnf;

    NAS_LMM_PUBM_LOG3_NORM("NAS_LMM_PubmDaSetCnf:  ulMsgId =, ulRslt =, ulOpId = ",
                                        pstAppRslt->ulMsgId,
                                        pstAppRslt->ulRslt,
                                        pstAppRslt->ulOpId);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_PubmDaSendSetCnf_ENUM
,LNAS_FUNCTION_LABEL1,
                                        pstAppRslt->ulMsgId);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_PubmDaSendSetCnf_ENUM
,LNAS_FUNCTION_LABEL2,
                                        pstAppRslt->ulRslt,
                                        pstAppRslt->ulOpId);

    /* ����DOPRA��Ϣ */
    pstEmmSetCnf = (VOS_VOID *)NAS_LMM_ALLOC_MSG(
                                        sizeof(APP_MM_SET_CMD_CNF_STRU));
    if(NAS_LMM_NULL_PTR  == pstEmmSetCnf)
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_PubmDaSetCnf: alloc NULL_PTR !! ulMsgId = ",
                                        pstAppRslt->ulMsgId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_PubmDaSendSetCnf_ENUM
,LNAS_FUNCTION_LABEL3,
                                         pstAppRslt->ulMsgId);
        return;
    }

    /*lint -e960*/

    NAS_LMM_MEM_SET_S(  pstEmmSetCnf,
                        sizeof(APP_MM_SET_CMD_CNF_STRU),
                        0,
                        sizeof(APP_MM_SET_CMD_CNF_STRU));


    /* �����Ϣͷ */
    EMM_COMP_APP_MSG_VOS_HEADER( pstEmmSetCnf,
                                 EMM_MSG_LENTH_NO_HEADER(APP_MM_SET_CMD_CNF_STRU),
                                 pstAppRslt);

    /* ��д��Ϣ�� */
    pstEmmSetCnf->ulMsgId               = pstAppRslt->ulMsgId;
    pstEmmSetCnf->ulOpId                = pstAppRslt->ulOpId;
    pstEmmSetCnf->ulRslt                = pstAppRslt->ulRslt;

    /* ������Ϣ */
    NAS_LMM_SEND_MSG(pstEmmSetCnf);

    /*lint +e960*/

    return;

}

/*****************************************************************************
 Function Name   : NAS_LMM_CheckAppDrxParam
 Description     : ���APP�·���DRX�����Ƿ���Ч
 Input           :
 Output          :
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-25  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_CheckAppDrxParam( CONST APP_DRX_STRU *pstAppDrxParam )
{
    /*������ָ��*/
    if (VOS_NULL_PTR == pstAppDrxParam)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: Input NULL PTR.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckAppDrxParam_ENUM
,LNAS_NULL_PTR);
        return NAS_EMM_PARA_INVALID;
    }

    /*SPLIT on CCCH��Ч����֤*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxSplitOnCcchValid(pstAppDrxParam->ucSplitOnCcch))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: SplitOnCcch InValid.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckAppDrxParam_ENUM
,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_PARA_INVALID;
    }

    /*non_DRX Timer��Ч����֤*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxNonDrxTimerValid(pstAppDrxParam->ucNonDrxTimer))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: NonDrxTimer InValid.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckAppDrxParam_ENUM
,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_PARA_INVALID;
    }

    /*SPLIT PG CYCLE CODE��Ч����֤*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsDrxPgCycleCodeValid(pstAppDrxParam->ucSplitPgCode))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: SplitPgCycleCode InValid.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckAppDrxParam_ENUM
,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_PARA_INVALID;
    }

    /* DRX Valude for S1 Mode��Ч����֤*/
    if (NAS_EMM_PARA_INVALID == NAS_LMM_IsUeDrxCycleValid(pstAppDrxParam->ucPsDrxLen))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CheckAppDrxParam: UeSpecDrxCycle InValid.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_CheckAppDrxParam_ENUM
,LNAS_FUNCTION_LABEL4);
        return NAS_EMM_PARA_INVALID;
    }

    return NAS_EMM_PARA_VALID;

}

/*****************************************************************************
 Function Name   : NAS_LMM_IsDrxSplitOnCcchValid
 Description     : �ж�DRX������ucSplitOnCcch�Ƿ���Ч:
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-27  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_IsDrxSplitOnCcchValid( VOS_UINT8 ucSplitOnCcch )
{
    /*ucSplitOnCcchȡֵ:0 or 1*/
    if ((NAS_LMM_SPLIT_ON_CCCH_NOT_SUPPORT != ucSplitOnCcch)
      &&(NAS_LMM_SPLIT_ON_CCCH_SUPPORT != ucSplitOnCcch))
    {
        return NAS_EMM_PARA_INVALID;
    }
    return NAS_EMM_PARA_VALID;
}

/*****************************************************************************
 Function Name   : NAS_LMM_IsDrxNonDrxTimerValid
 Description     : �ж�DRX������ucNonDrxTimer�Ƿ���Ч
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-27  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_IsDrxNonDrxTimerValid( VOS_UINT8 ucNonDrxTimer )
{
    /*ucNonDrxTimerȡֵ��Χ:[0,7]*/
    if (NAS_LMM_MAX_NON_DRX_TIMER < ucNonDrxTimer)
    {
        return NAS_EMM_PARA_INVALID;
    }
    return NAS_EMM_PARA_VALID;
}

/*****************************************************************************
 Function Name   : NAS_LMM_IsDrxPgCycleCodeValid
 Description     : �ж�DRX������ucSplitPgCode�Ƿ���Ч
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-27  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_IsDrxPgCycleCodeValid( VOS_UINT8 ucSplitPgCode )
{
    /*ucSplitPgCodeȡֵ��Χ:[0,98]*/
    if (NAS_LMM_MAX_SPLIT_PG_CYCLE_CODE < ucSplitPgCode)
    {
        return NAS_EMM_PARA_INVALID;
    }
    return NAS_EMM_PARA_VALID;
}

/*****************************************************************************
 Function Name   : NAS_LMM_IsUeDrxCycleValid
 Description     : �ж�DRX������ucPsDrxLen�Ƿ���Ч
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-8-27  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_IsUeDrxCycleValid( VOS_UINT8 ucPsDrxLen )
{
    /*Drx Value for S1 Mode: 24008-930 10.5.5.6*/
    CONST VOS_UINT32 aulUeSpecDrxValue[NAS_LMM_UE_SPEC_DRX_VALUE_NUM] = {0,6,7,8,9};
    VOS_UINT32                          i;

    for(i = 0; i < NAS_LMM_UE_SPEC_DRX_VALUE_NUM; i++)
    {
        if(aulUeSpecDrxValue[i] == ucPsDrxLen)
        {
           return NAS_EMM_PARA_VALID;
        }
    }

    return NAS_EMM_PARA_INVALID;
}

/*PC REPLAY MODIFY BY LEILI DELETE*/

/*****************************************************************************
 Function Name   : NAS_LMM_OmInfoIndProc
 Description     : EMMģ�鴦��OM��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.xiongxianghui 00253310     2013-10-31    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_OmInfoIndProc(VOS_VOID)
{
    VOS_UINT32 ulFtmRst = NAS_EMM_FAIL;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_OmInfoIndProc!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_OmInfoIndProc_ENUM
,LNAS_ENTRY);

    if(NAS_EMM_FTM_ACTION_FLAG_OPEN == NAS_EMM_GetFtmInfoActionFlag())
    {
        ulFtmRst = NAS_LMM_CompareEmmDatabaseInfo();
    }

    NAS_LMM_UpdateEmmDatabaseInfo();

    if(NAS_EMM_SUCC == ulFtmRst)
    {
        NAS_LMM_SendOmFtmMsg();
    }
}


/*****************************************************************************
 Function Name   : NAS_LMM_FtmInfoInit
 Description     : ��ʼ������ģʽ��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.xiongxianghui 00253310     2013-10-31    Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_FtmInfoInit( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_FtmInfoInit!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_FtmInfoInit_ENUM
,LNAS_ENTRY);

    /*lint -e960*/

    NAS_LMM_MEM_SET_S(  NAS_EMM_GetFtmInfoManageAddr(),
                        sizeof(EMM_FTM_INFO_MANAGE_STRU),
                        0,
                        sizeof(EMM_FTM_INFO_MANAGE_STRU));

    NAS_LMM_MEM_SET_S(  NAS_EMM_GetEmmInfoAddr(),
                        sizeof(EMM_DATABASE_INFO_STRU),
                        0,
                        sizeof(EMM_DATABASE_INFO_STRU));

    /*lint +e960*/

    NAS_EMM_GetFtmInfoActionFlag() = NAS_EMM_FTM_ACTION_FLAG_CLOSE;

    return;
}


/*****************************************************************************
 Function Name   : NAS_LMM_CompareEmmDatabaseInfo
 Description     : �ж�EMMģ���ϱ���OM����Ϣ�Ƿ����仯
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.xiongxianghui 00253310     2013-10-31    Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_CompareEmmDatabaseInfo( VOS_VOID )
{
    NAS_LMM_TIMER_CTRL_STRU             *pstPtlTimer;
    APP_EMM_MAIN_STATE_ENUM_UINT16      ulProtoclMainState;
    APP_EMM_SUB_STATE_ENUM_UINT16       ulProtoclSubState;


    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_CompareEmmDatabaseInfo!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_CompareEmmDatabaseInfo_ENUM
,LNAS_ENTRY);

    /* ��EMM��ǰ״̬��ȡЭ��״̬ */
    NAS_LMM_PubmGetEmmState(&ulProtoclMainState,
                            &ulProtoclSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());

    if((ulProtoclMainState != NAS_EMM_GetEmmInfoAddr()->enMainState)
        || (ulProtoclSubState != NAS_EMM_GetEmmInfoAddr()->enSubState))
    {
        return NAS_EMM_SUCC;
    }

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&NAS_EMM_GetEmmInfoAddr()->stGuti,
                                                    NAS_LMM_GetEmmInfoUeidGutiAddr(),
                                                    sizeof(NAS_MM_GUTI_STRU)))
    {
        return NAS_EMM_SUCC;
    }

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&NAS_EMM_GetEmmInfoAddr()->stPlmnId,
                                                    NAS_LMM_GetEmmInfoLastRegPlmnAddr(),
                                                    sizeof(NAS_MM_PLMN_ID_STRU)))
    {
        return NAS_EMM_SUCC;
    }

    if((NAS_EMM_GetEmmInfoAddr()->enEmmCnRejCause) != NAS_EMM_GetFtmInfoCnRej())
    {
        return NAS_EMM_SUCC;
    }

    if(NAS_LMM_MEM_CMP_EQUAL != NAS_LMM_MEM_CMP(&NAS_EMM_GetEmmInfoAddr()->stTac,
                                                    NAS_LMM_GetEmmInfoLastRegTacAddr(),
                                                    sizeof(NAS_MM_TAC_STRU)))
    {
        return NAS_EMM_SUCC;
    }

    /*lint -e506 -e944 -e636 */
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(TI_NAS_EMM_PTL_T3412);
    /*lint +e506 +e944 +e636 */
    if(NAS_EMM_GetEmmInfoAddr()->ulTimerLen3412 != pstPtlTimer->ulTimerLen)
    {
        return NAS_EMM_SUCC;
    }

    return NAS_EMM_FAIL;
}


/*****************************************************************************
 Function Name   : NAS_LMM_UpdateEmmDatabaseInfo
 Description     : EMMģ����»�����Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.xiongxianghui 00253310     2013-10-31    Draft Enact
*****************************************************************************/
 VOS_VOID NAS_LMM_UpdateEmmDatabaseInfo(VOS_VOID)
 {
    NAS_LMM_TIMER_CTRL_STRU             *pstPtlTimer;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_UpdateEmmDatabaseInfo!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_UpdateEmmDatabaseInfo_ENUM
,LNAS_ENTRY);

    /* ����EMM״̬ */
    NAS_LMM_PubmGetEmmState(&NAS_EMM_GetEmmInfoAddr()->enMainState,
                            &NAS_EMM_GetEmmInfoAddr()->enSubState,
                            NAS_LMM_GetEmmCurFsmMS(),
                            NAS_LMM_GetEmmCurFsmSS());

    /*lint -e960*/

    /* ����GUTI��Ϣ */
    NAS_LMM_MEM_CPY_S(  &NAS_EMM_GetEmmInfoAddr()->stGuti,
                        sizeof(NAS_MM_GUTI_STRU),
                        NAS_LMM_GetEmmInfoUeidGutiAddr(),
                        sizeof(NAS_MM_GUTI_STRU));

    /* ����PlmnId��Ϣ */
    NAS_LMM_MEM_CPY_S(  &NAS_EMM_GetEmmInfoAddr()->stPlmnId,
                        sizeof(NAS_MM_PLMN_ID_STRU),
                        NAS_LMM_GetEmmInfoLastRegPlmnAddr(),
                        sizeof(NAS_MM_PLMN_ID_STRU));

    /* ����TAC��Ϣ */
    NAS_LMM_MEM_CPY_S(  &NAS_EMM_GetEmmInfoAddr()->stTac,
                        sizeof(NAS_MM_TAC_STRU),
                        NAS_LMM_GetEmmInfoLastRegTacAddr(),
                        sizeof(NAS_MM_TAC_STRU));

    /*lint +e960*/


    /* ����CN�ܾ�ԭ�� */
    NAS_EMM_GetEmmInfoAddr()->enEmmCnRejCause = NAS_EMM_GetFtmInfoCnRej();

    /* ����TimerLen3412 */
    /*lint -e506 -e944 -e636 */
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(TI_NAS_EMM_PTL_T3412);
    /*lint +e506 +e944 +e636 */
    NAS_EMM_GetEmmInfoAddr()->ulTimerLen3412 = pstPtlTimer->ulTimerLen;

    return;
 }

 /*****************************************************************************
  Function Name   : NAS_LMM_RevOmFtmCtrlMsg
  Description     : �յ�OM����ģʽ������Ϣ
  Input           : 1.MsgBlock   *pMsgStru
  Output          : None
  Return          : VOS_UINT32

  History         :
     1. lifuxin 00253982 2013-10-31 �½�

 *****************************************************************************/
 VOS_UINT32   NAS_LMM_RevOmFtmCtrlMsg(MsgBlock   *pMsgStru)
 {
     OM_FTM_CTRL_IND_STRU  *pstOmFtmCtlInfo;

     NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmFtmCtrlMsg!");
     TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmFtmCtrlMsg_ENUM
,LNAS_ENTRY);

     if (VOS_NULL_PTR == pMsgStru)
     {
         NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmFtmCtrlMsg, input point is null!");
         TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmFtmCtrlMsg_ENUM
,LNAS_NULL_PTR);

         return NAS_LMM_MSG_DISCARD;
     }

     pstOmFtmCtlInfo = (OM_FTM_CTRL_IND_STRU *)(VOS_VOID *)pMsgStru;

     if(1 == pstOmFtmCtlInfo->ucActionFlag)
     {
        /*���ù���ģʽ�ϱ����ܴ�*/
         NAS_EMM_SetFtmOmManageFtmActionFlag(NAS_EMM_FTM_ACTION_FLAG_OPEN);

        /*�ϱ���ǰ��Ϣ */
         NAS_LMM_SendOmFtmMsg();
     }
     else
     {
         /*�رչ���ģʽ�ϱ���*/
          NAS_EMM_SetFtmOmManageFtmActionFlag(NAS_EMM_FTM_ACTION_FLAG_CLOSE);
     }

     return NAS_LMM_MSG_HANDLED;

 }

 /*****************************************************************************
  Function Name   : NAS_LMM_SendOmFtmMsg
  Description     : ����״̬�仯��Ϣ��OM
  Input           : None
  Output          : None
  Return          : None

  History         :
     1.lifuxin 00253982      2013-10-31  �½�

 *****************************************************************************/
 VOS_VOID     NAS_LMM_SendOmFtmMsg(VOS_VOID)
 {
     LNAS_OM_FTM_REPROT_IND_STRU *pFtmMsg;

     NAS_LMM_PUBM_LOG1_INFO("LMM_OM_SendOmFtmMsg: ActionFlag = ", NAS_EMM_GetFtmInfoActionFlag());
     TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendOmFtmMsg_ENUM
,LNAS_FUNCTION_LABEL1,NAS_EMM_GetFtmInfoActionFlag());

     /* ������ģʽ�رգ��򲻷��� */
     if(NAS_EMM_FTM_ACTION_FLAG_OPEN != NAS_EMM_GetFtmInfoActionFlag())
     {
         return;
     }

     /*������Ϣ�ڴ�*/
     pFtmMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(LNAS_OM_FTM_REPROT_IND_STRU));

     /*�ж�����������ʧ���˳�*/
     if (VOS_NULL_PTR == pFtmMsg)
     {
         return;
     }

     /*����ID_EMM_ESM_PDN_CON_IND��Ϣ*/
     /*�����Ϣͷ*/

     /*lint -e960*/
     NAS_LMM_COMP_OM_MSG_HEADER(         pFtmMsg,
                                         (sizeof(LNAS_OM_FTM_REPROT_IND_STRU)-
                                         NAS_EMM_LEN_VOS_MSG_HEADER));
     /*lint +e960*/

     /*�����ϢID*/
     pFtmMsg->ulMsgName                  = ID_OM_FTM_REPROT_IND;

     /*�����Ϣ����*/
     pFtmMsg->ulMsgType                  = OM_ERR_LOG_MSG_FTM_REPORT;
     pFtmMsg->ulMsgSN                    = NAS_EMM_GetFtmInfoMsgSN();
     NAS_EMM_GetFtmInfoMsgSN()++;
     pFtmMsg->ulRptlen                   = sizeof(LNAS_OM_FTM_REPROT_CONTENT_STRU);

     pFtmMsg->stLnasFtmContent.ulMsgModuleID  = OM_ERR_LOG_MOUDLE_ID_LMM;
     pFtmMsg->stLnasFtmContent.usModemId      = 0;
     pFtmMsg->stLnasFtmContent.usProjectID    = 0;
     pFtmMsg->stLnasFtmContent.ulLength       = sizeof(LNAS_LMM_FTM_INFO_STRU);

    /*���ܾ�ԭ��*/
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.ucEmmCnRejCause =
         g_astEmmFtmInfoManage.enEmmCnRejCause;

    /*���PlmnID*/
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stPlmnId.aucPlmnId[0] =
         g_astEmmInfo.stPlmnId.aucPlmnId[0];
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stPlmnId.aucPlmnId[1] =
         g_astEmmInfo.stPlmnId.aucPlmnId[1];
     pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stPlmnId.aucPlmnId[2] =
         g_astEmmInfo.stPlmnId.aucPlmnId[2];

    /*���Guti*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMmeCode.ucMmeCode =
        g_astEmmInfo.stGuti.stMmeCode.ucMmeCode;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMmeGroupId.ucGroupId =
        g_astEmmInfo.stGuti.stMmeGroupId.ucGroupId;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMmeGroupId.ucGroupIdCnt =
        g_astEmmInfo.stGuti.stMmeGroupId.ucGroupIdCnt;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsi =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsi;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsiCnt1 =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsiCnt1;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsiCnt2 =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsiCnt2;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stMTmsi.ucMTmsiCnt3 =
        g_astEmmInfo.stGuti.stMTmsi.ucMTmsiCnt3;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stPlmnId.aucPlmnId[0] =
        g_astEmmInfo.stGuti.stPlmnId.aucPlmnId[0];
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stPlmnId.aucPlmnId[1] =
        g_astEmmInfo.stGuti.stPlmnId.aucPlmnId[1];
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stGuti.stPlmnId.aucPlmnId[2] =
        g_astEmmInfo.stGuti.stPlmnId.aucPlmnId[2];

    /*���Timer3412*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.ulTimerLen3412 =
        g_astEmmInfo.ulTimerLen3412;

    /*���Tac*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stTac.ucTac =
        g_astEmmInfo.stTac.ucTac;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stTac.ucTacCnt =
        g_astEmmInfo.stTac.ucTacCnt;

    /*���mainstate, substate*/
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stEmmState.ulLmmMainState =
        g_astEmmInfo.enMainState;
    pFtmMsg->stLnasFtmContent.u.stLmmFtmInfo.stEmmState.ulLmmSubState =
        g_astEmmInfo.enSubState;


     /*��OMģ�鷢��״̬�仯��Ϣ*/
     /*lint -e960*/
     NAS_LMM_SEND_MSG( pFtmMsg);
     /*lint +e960*/

     return;

 }

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 Function Name   : NAS_LMM_GetPositionInfo
 Description     : ��ȡλ����Ϣ
 Input           : pMsg
 Output          : None
 Return          : None
 History         :
    1.yanglei 00307272     2015-09-29 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_GetPositionInfo(LNAS_OM_ERRLOG_POSITION_INFO_STRU *pstPositionInfo)
{


    NAS_MM_NETWORK_ID_STRU             *pstPresentNetInfo = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_GetPositionInfo Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_GetPositionInfo_ENUM,LNAS_ENTRY);

    pstPresentNetInfo                  = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();

    if(NAS_EMM_NULL_PTR == pstPositionInfo)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_GetPositionInfo PRT NULL.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_GetPositionInfo_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_FAIL;
    }

    NAS_LMM_MEM_CPY_S(                  &pstPositionInfo->stPlmnId,
                                        sizeof(LNAS_OM_ERRLOG_PLMN_ID_STRU),
                                        &pstPresentNetInfo->stPlmnId,
                                        sizeof(LNAS_OM_ERRLOG_PLMN_ID_STRU));

    NAS_LMM_MEM_CPY_S(                  &pstPositionInfo->stTac,
                                        sizeof(LNAS_OM_ERRLOG_TAC_STRU),
                                        &pstPresentNetInfo->stTac,
                                        sizeof(LNAS_OM_ERRLOG_TAC_STRU));

    pstPositionInfo->ulCellId         = pstPresentNetInfo->ulCellId;

    pstPositionInfo->ulArfcn          = pstPresentNetInfo->ulArfcn;

    pstPositionInfo->aulLteBand[0]    = pstPresentNetInfo->aulLteBand[0];

    pstPositionInfo->aulLteBand[1]    = pstPresentNetInfo->aulLteBand[1];
    return NAS_LMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMsgEsmSaveErrlogInd
 Description     : ����ESM����EMM��ESM ERRLOG��Ϣ������buffer
 Input           : pMsg
 Output          : None
 Return          : None
 History         :
    1.lifuxin 00253982     2014-12-31 Draft Enact
*****************************************************************************/
/*lint -e826*/
VOS_UINT32 NAS_LMM_PreProcMsgEsmSaveErrlogInd(MsgBlock *     pMsg)
{
    EMM_ESM_SAVE_ERRLOG_IND_STRU        *pstSaveEsmErrMsg = VOS_NULL;
    VOS_VOID                            *pstEsmErrlogRslt = VOS_NULL;
    VOS_UINT32                          ulLength = 0;
    VOS_UINT32                          ulResult = 0;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMsgEsmSaveErrlogInd Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMsgEsmSaveErrlogInd_ENUM
,LNAS_ENTRY);

    /*ȡ��buffer�е�ESM errlog����*/
    pstSaveEsmErrMsg = (EMM_ESM_SAVE_ERRLOG_IND_STRU*)pMsg;
    pstEsmErrlogRslt = (VOS_VOID*)pstSaveEsmErrMsg->stEmmEsmErrlog.aucEsmMsg;
    ulLength = pstSaveEsmErrMsg->stEmmEsmErrlog.ulEsmMsgSize;

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)pstEsmErrlogRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_LMM_PreProcMsgEsmSaveErrlogInd: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_LMM_PreProcMsgEsmSaveErrlogInd_ENUM
,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return NAS_LMM_MSG_HANDLED;
}
/*lint +e826*/
/*****************************************************************************
Function Name   : NAS_LMM_RevNvCtrl
Description     : nv����ģ��
Input           : None
Output          : None
Return          : VOS_UINT32

History         :

1.lifuxin       00253982     2014-12-29    Errlog �ع�
*****************************************************************************/
VOS_VOID NAS_LMM_RevNvCtrl(VOS_VOID)
{
    VOS_UINT32                              ulRslt;
    NV_ID_ERR_LOG_CTRL_INFO_STRU            stOMErrLogCtrlInfo;
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevNvCtrl!!!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_RevNvCtrl_ENUM
,LNAS_ENTRY);

    NAS_LMM_MEM_SET_S(  &stOMErrLogCtrlInfo,
                        sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU),
                        0x00,
                        sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));

    ulRslt = LPs_NvimItem_Read(en_NV_Item_ErrLogCtrlInfo, &stOMErrLogCtrlInfo, sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU) );
    if(PS_SUCC != ulRslt)
    {
        return;
    }

    /* ����ERRLOG���Ʊ�ʶ, 0��ʾ�ر�errlog�� 1��ʾ����errlog*/
    if ((VOS_FALSE == stOMErrLogCtrlInfo.ucAlmStatus)
     || (VOS_TRUE  == stOMErrLogCtrlInfo.ucAlmStatus))
    {
        NAS_EMM_SetErrlogCtrlInfoCtrlFlag(stOMErrLogCtrlInfo.ucAlmStatus);
    }

    /*�����·���errlog�ȼ�ȥ�����Ƿ�洢log��Ϣ*/
    if ((stOMErrLogCtrlInfo.ucAlmLevel >= LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (stOMErrLogCtrlInfo.ucAlmLevel <= LNAS_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        NAS_EMM_SetErrlogCtrlInfoALMLevel(stOMErrLogCtrlInfo.ucAlmLevel);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_RevOmErrlogCtrlMsg
 Description     : EMMģ���յ�OM����Errlog������Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.xiongxianghui 00253310     2013-11-07    Draft Enact
    2.lifuxin       00253982     2014-12-29    Errlog �ع�
 *****************************************************************************/
VOS_UINT32 NAS_LMM_RevOmErrlogCtrlMsg(MsgBlock   *pMsgStru)
{
    OM_ERROR_LOG_CTRL_IND_STRU  *pstOmErrlogCtlInfo;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmErrlogCtrlMsg!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmErrlogCtrlMsg_ENUM
,LNAS_ENTRY);

    if (VOS_NULL_PTR == pMsgStru)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmErrlogCtrlMsg, input point is null!");
       TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmErrlogCtrlMsg_ENUM
,LNAS_NULL_PTR);

        return NAS_LMM_MSG_DISCARD;
    }

    pstOmErrlogCtlInfo = (OM_ERROR_LOG_CTRL_IND_STRU *)(VOS_VOID *)pMsgStru;

    /* ����ERRLOG���Ʊ�ʶ, 0��ʾ�ر�errlog�� 1��ʾ����errlog*/
    if ((VOS_FALSE == pstOmErrlogCtlInfo->ucAlmStatus)
     || (VOS_TRUE  == pstOmErrlogCtlInfo->ucAlmStatus))
    {
        NAS_EMM_SetErrlogCtrlInfoCtrlFlag(pstOmErrlogCtlInfo->ucAlmStatus);
    }

    /*�����·���errlog�ȼ�ȥ�����Ƿ�洢log��Ϣ*/
    if ((pstOmErrlogCtlInfo->ucAlmLevel >= LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (pstOmErrlogCtlInfo->ucAlmLevel <= LNAS_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        NAS_EMM_SetErrlogCtrlInfoALMLevel(pstOmErrlogCtlInfo->ucAlmLevel);
    }

    return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
Function Name   : NAS_EMM_GetErrLogRingBufUseBytes
Description     : ��ȡ����buffer�Ѿ�ʹ�����ݵ��ֽ���
Input           : None
Output          : None
Return          : VOS_UINT32 �ֽ���

History         :
 1. lifuxin 00253982 2013-11-07 �½�
*****************************************************************************/

VOS_UINT32 NAS_EMM_GetErrLogRingBufUseBytes(VOS_VOID)
{
    return (VOS_UINT32)OM_RingBufferNBytes(NAS_EMM_GetErrlogBufferInfoRingBuffer());
}

/*****************************************************************************
Function Name   : NAS_EMM_GetErrLogRingBufContent
Description     : ��ȡ����buffer�Ѿ�ʹ�����ݵ�����
Input           : None
Output          : None
Return          : VOS_UINT32 ��ȡʵ���ֽ���������

History         :
 1. lifuxin 00253982 2013-12-29 �½�
*****************************************************************************/
 VOS_UINT32 NAS_EMM_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    return (VOS_UINT32)OM_RingBufferGet(NAS_EMM_GetErrlogBufferInfoRingBuffer(), pbuffer, (VOS_INT)ulbytes);
}

/*****************************************************************************
Function Name   : NAS_EMM_CleanErrLogRingBuf
Description     : ��ջ���buffer
Input           : None
Output          : None
Return          : NONE

History         :
 1. lifuxin 00253982 2013-12-29 �½�
*****************************************************************************/
VOS_VOID NAS_EMM_CleanErrLogRingBuf(VOS_VOID)
{
    OM_RingBufferFlush(NAS_EMM_GetErrlogBufferInfoRingBuffer());

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_GetErrLogAlmLevel
 Description     : ����ALM IDȥ��ȡ��Ӧ�ĸ澯�ȼ�
 Input           : enAlmId
 Output          : None
 Return          : VOS_UINT16 ���ض�Ӧ��log�ȼ�

 History         :
    1. lifuxin 00253982 2014-12-29 �½�
*****************************************************************************/
VOS_UINT16 NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16 enAlmId)
{
     VOS_UINT16                          usTableLen;
     VOS_UINT16                          usStep;

     /* ��ȡTab���� */
     usTableLen = sizeof(g_astLNasErrAlmLevelTb)/sizeof(g_astLNasErrAlmLevelTb[0]);

     /* ����ض�ӦAlm ID��log�ȼ� */
     for (usStep = 0; usStep < usTableLen; usStep++)
     {
         if (g_astLNasErrAlmLevelTb[usStep].enAlmID == enAlmId)
         {
             return g_astLNasErrAlmLevelTb[usStep].usLogLevel;
         }
     }

 /* δ�鵽������δ����ȼ� */
 return LNAS_ERR_LOG_CTRL_LEVEL_NULL;
}

/*****************************************************************************
 �� �� ��  : NAS_EMM_GetErrLogUnsoliReportType
 ��������  : ��ȡERR LOG�����ϱ�����
 �������  : LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16 enAlmId
 �������  : ��
 �� �� ֵ  : EMM_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��5��
    ��    ��   : wangchen 00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
EMM_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_UINT16 NAS_EMM_GetErrLogUnsoliReportType(LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16 enAlmId)
{
    VOS_UINT16                          usTableLen;
    VOS_UINT16                          usStep;

    /* ��ȡTab���� */
    usTableLen = sizeof(g_astLNasErrAlmUnsoliReportTypeTb)/sizeof(g_astLNasErrAlmUnsoliReportTypeTb[0]);

    /* ����ض�ӦAlm ID��log�ȼ� */
    for (usStep = 0; usStep < usTableLen; usStep++)
    {
        if (g_astLNasErrAlmUnsoliReportTypeTb[usStep].enAlmID == enAlmId)
        {
            return g_astLNasErrAlmUnsoliReportTypeTb[usStep].enReportType;
        }
    }

    /* δ�鵽������δ����ȼ� */
    return EMM_ERR_LOG_REPORT_TYPE_BUTT;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SndAcpuOmErrLogReportCnf
 Description     : OMģ������errlog��ͨ���ú����ϱ�
 Input           : pbuffer����������, ulBufUseLen���ݵ���Ч����
 Output          : None
 Return          : None

 History         :
    1. lifuxin 00253982 2014-12-29 �½�
*****************************************************************************/
VOS_VOID NAS_EMM_SndAcpuOmErrLogReportCnf(
 VOS_CHAR                           *pbuffer,
 VOS_UINT32                          ulBufUseLen
)
{
     LNAS_OM_ERR_LOG_REPORT_CNF_STRU     *pstReqErrlogCnf = VOS_NULL_PTR;
     VOS_UINT32                          ulMsgLen;

     /* �ϱ�����Ϣ�ܳ��� */
     ulMsgLen  = sizeof(LNAS_OM_ERR_LOG_REPORT_CNF_STRU) - 4 + ulBufUseLen;

     /* ��Ϣ�ռ����� */
     pstReqErrlogCnf = (VOS_VOID*)NAS_LMM_ALLOC_MSG(ulMsgLen);
     if (VOS_NULL_PTR == pstReqErrlogCnf)
     {
         NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SndAcpuOmErrLogReportCnf, Alloc mem error!");
         TLPS_PRINT2LAYER_INFO(NAS_EMM_SndAcpuOmErrLogReportCnf_ENUM
,LNAS_NULL_PTR);
         return;
     }

     pstReqErrlogCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
     pstReqErrlogCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
     pstReqErrlogCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
     pstReqErrlogCnf->ulSenderPid      = PS_PID_MM;
     pstReqErrlogCnf->ulMsgName        = ID_LNAS_OM_ERR_LOG_REPORT_CNF;
     pstReqErrlogCnf->ulMsgType        = OM_ERR_LOG_MSG_ERR_REPORT;
     pstReqErrlogCnf->ulMsgSN          = 0;
     pstReqErrlogCnf->ulRptlen         = ulBufUseLen;

     if (VOS_NULL_PTR != pbuffer)
     {
         NAS_LMM_MEM_CPY_S(pstReqErrlogCnf->aucContent, ulBufUseLen, pbuffer, ulBufUseLen);
     }

     NAS_LMM_SEND_MSG(pstReqErrlogCnf);

     return;
}

/*****************************************************************************
Function Name   : NAS_LMM_RevOmReadErrlogReq
Description     : LMM�յ���ȡerrlog��Ϣ����
Input           : 1.MsgBlock   *pMsgStru
Output          : None
Return          : VOS_UINT32

History         :
 1. lifuxin 00253982 2013-11-07 �½�
 2. lifuxin 00253982 2014-12-29 errlog �ع�
*****************************************************************************/
VOS_UINT32   NAS_LMM_RevOmReadErrlogReq(MsgBlock   *pMsgStru)
{
    VOS_CHAR                                       *pbuffer   = VOS_NULL_PTR;
    VOS_UINT32                                     ulBufUseLen;
    VOS_UINT32                                     ulRealLen;
    VOS_UINT32                                     ulTotalLen;
    LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU        stLnasErrLogOverflowEvent;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmReadErrlogReq!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmReadErrlogReq_ENUM
,LNAS_ENTRY);

    if (VOS_NULL_PTR == pMsgStru)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_RevOmReadErrlogReq, input point is null!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_RevOmReadErrlogReq_ENUM
,LNAS_NULL_PTR);

        return NAS_LMM_MSG_DISCARD;
    }

    /* RING BUFFER���ݳ��� */
    ulBufUseLen = NAS_EMM_GetErrLogRingBufUseBytes();

    ulTotalLen = ulBufUseLen + sizeof(LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU);

    pbuffer = (VOS_CHAR *)NAS_LMM_MEM_ALLOC(ulTotalLen);
    if (VOS_NULL_PTR == pbuffer)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        NAS_EMM_SndAcpuOmErrLogReportCnf(VOS_NULL_PTR, 0);
        return VOS_TRUE;
    }

    NAS_LMM_MEM_SET_S(pbuffer, ulTotalLen, 0, ulTotalLen);

    /* ��ȡRING BUFFER������ */
    ulRealLen = NAS_EMM_GetErrLogRingBufContent(pbuffer, ulBufUseLen);
    if (ulRealLen != ulBufUseLen)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        NAS_EMM_SndAcpuOmErrLogReportCnf(VOS_NULL_PTR, 0);
        NAS_LMM_MEM_FREE(pbuffer);
        return VOS_TRUE;
    }

    /* �����������������Ϣ׷����RingBuf���� */
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stLnasErrLogOverflowEvent.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_OVERFLOW_FAIL,
                                      NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_OVERFLOW_FAIL),
                                      VOS_GetSlice(),
                                      (sizeof(LNAS_ERR_INFO_OVERFLOW_COUNT_EVENT_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stLnasErrLogOverflowEvent.ulOverflowCount = NAS_EMM_GetErrlogBufferInfoOverflowCnt();

    NAS_LMM_MEM_CPY_S(  pbuffer + ulBufUseLen,
                        ulTotalLen - ulBufUseLen,
                        &stLnasErrLogOverflowEvent,
                        sizeof(stLnasErrLogOverflowEvent));

    /* ��ȡ���˺���Ҫ��RINGBUFFER��� */
    NAS_EMM_CleanErrLogRingBuf();

    /* ����������� */
    NAS_EMM_SetErrlogBufferInfoOverflowCnt(0);

    /* ����ID_OM_ERR_LOG_REPORT_CNF��Ϣ��ACPU OM */
    NAS_EMM_SndAcpuOmErrLogReportCnf(pbuffer, ulTotalLen);

    NAS_LMM_MEM_FREE(pbuffer);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
Function Name   : NAS_EMM_IsErrLogNeedRecord
Description     : �жϵ�ǰ���������Ƿ���Ҫ��¼
Input           : ��Ӧ��log��¼�ȼ�
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-29 errlog �½�
*****************************************************************************/
VOS_UINT32 NAS_EMM_IsErrLogNeedRecord(VOS_UINT16 usLevel)
{
     /* Log���عرգ�����Ҫ�ϱ� */
     if (0 == NAS_EMM_GetErrlogCtrlInfoCtrlFlag())
     {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsErrLogNeedRecord1");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsErrLogNeedRecord_ENUM
,LNAS_FUNCTION_LABEL1);
        return VOS_FALSE;
     }

     /* ģ��log����usLevel�����û����õ�log�ϱ������usLevel��Ч������Ҫ�ϱ� */
     if ((NAS_EMM_GetErrlogCtrlInfoALMLevel() < usLevel)
      || (LNAS_ERR_LOG_CTRL_LEVEL_NULL == usLevel))
     {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsErrLogNeedRecord2");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsErrLogNeedRecord_ENUM
,LNAS_FUNCTION_LABEL2);
        return VOS_FALSE;
     }

     return VOS_TRUE;
}

/*****************************************************************************
 Function Name   :  NAS_LMM_CnCauseProc
 Description     :  ���ڲ�����ܾ�ԭ��ת����Lnas error log��Ӧ��ö��ֵ
 Input           :  ucCauseCode ��ʾ����ܾ�ԭ��

 Output          :  ���һ��Lnas error log��ö�ٱ���
 Return          :

 History         :
    1.lifuxin 00253982         2013-11-07  �����ļ�
    2.lifuxin 00253982         2014-12-29  errlog�ع�

*****************************************************************************/
EMM_OM_ERRLOG_CN_CAUSE_ENUM_UINT16  NAS_LMM_CnCauseProc(NAS_EMM_CN_CAUSE_ENUM_UINT8 ucCnCause)
{
    EMM_OM_ERRLOG_CN_CAUSE_ENUM_UINT16   ulErrId = 0;
    VOS_UINT32 i;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_CnCauseProc!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_CnCauseProc_ENUM
,LNAS_ENTRY);

    for(i = 0; i < g_astEmmErrlogCnCauseNum; i++)
    {
        if(ucCnCause == g_astEmmErrlogCnCauseMap[i].ulCauseId)
        {
            ulErrId = g_astEmmErrlogCnCauseMap[i].ulErrorlogID;
            break;
        }
    }
    if(g_astEmmErrlogCnCauseNum == i)
    {
        ulErrId = EMM_OM_ERRLOG_CN_CAUSE_OTHERS;
    }

    return ulErrId;
}

/*****************************************************************************
Function Name   : NAS_EMM_PutErrLogRingBuf
Description     : ��errlog��Ϣд�뵽����buffer
Input           : д������ݣ��Ѿ���Ӧ�ĳ���
Output          : None
Return          : ʵ��д��ĳ���

History         :
 1. lifuxin 00253982 2014-12-30 errlog �½�
*****************************************************************************/
VOS_UINT32 NAS_EMM_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    VOS_UINT32                          ulCount;
    OM_RING_ID                          pLnasRingBuffer;

    pLnasRingBuffer = NAS_EMM_GetErrlogBufferInfoRingBuffer();
    if (VOS_NULL_PTR == pLnasRingBuffer)
    {
        return 0;
    }

    /* ���д���RING BUFFER������д�� */
    if (ulbytes > LNAS_RING_BUFFER_SIZE)
    {
        return 0;
    }

    /* ��ȡRING BUFFERʣ��ռ��С */
    ulFreeSize = (VOS_UINT32)OM_RingBufferFreeBytes(pLnasRingBuffer);

    ulCount = NAS_EMM_GetErrlogBufferInfoOverflowCnt();
    /* ���ʣ��ռ䲻��д��Ĵ�С�������RING BUFFER */
    if (ulFreeSize < ulbytes)
    {
        ulCount++;
        NAS_EMM_SetErrlogBufferInfoOverflowCnt(ulCount);

        OM_RingBufferFlush(pLnasRingBuffer);
    }

    /* д��RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pLnasRingBuffer, pbuffer, (VOS_INT)ulbytes);
}



/*****************************************************************************
 Function Name   :  NAS_LMM_EstCnfFailRsltProc
 Description     :  ��LRRC�Ľ���ԭ��ֵת��ERRLOG��ԭ��ֵ
 Input           :

 Output          :
 Return          :

 History         :
    1.lifuxin 00253982         2015-02-10  �º���
*****************************************************************************/
EMM_OM_ERRLOG_EST_RESULT_ENUM_UINT32  NAS_LMM_EstCnfFailRsltProc(LRRC_LNAS_EST_RESULT_ENUM_UINT32 ulLrrcEstCnfRslt)
{
    EMM_OM_ERRLOG_EST_RESULT_ENUM_UINT32   ulErrlogEstRslt = 0;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_EstCnfFailRsltProc!");

    switch(ulLrrcEstCnfRslt)
    {
        case LRRC_EST_DELING:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_DELING;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_CALL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CALL;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_SIGNAL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_SIGNAL;
            break;
        case LRRC_EST_ACCESS_BARRED_ALL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_ALL;
            break;
        case LRRC_EST_EST_CONN_FAIL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_EST_CONN_FAIL;
            break;
        case LRRC_EST_CELL_SEARCHING:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_CELL_SEARCHING;
            break;
        case LRRC_EST_ACCESS_BARRED_MT_CALL:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MT_CALL;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_CSFB:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CSFB;
            break;
        case LRRC_EST_ACCESS_BARRED_MO_CALL_AND_CSFB:
            ulErrlogEstRslt = EMM_OM_ERRLOG_EST_ACCESS_BARRED_MO_CALL_AND_CSFB;
            break;
        default:
             ulErrlogEstRslt = EMM_OM_ERRLOG_EST_RESULT_BUTT;
            break;
    }

    return ulErrlogEstRslt;
}

/*****************************************************************************
 Function Name   :  NAS_LMM_DataCnfFailRsltProc
 Description     :  ��LRRC��ֱ��ԭ��ֵת��ERRLOG��ԭ��ֵ
 Input           :

 Output          :
 Return          :

 History         :
    1.lifuxin 00253982         2015-02-10  �º���
*****************************************************************************/
EMM_OM_ERRLOG_SEND_RSLT_ENUM_UINT32  NAS_LMM_DataCnfFailRsltProc(LRRC_LMM_SEND_RSLT_ENUM_UINT32 ulLrrcDataCnfRslt)
{
    EMM_OM_ERRLOG_SEND_RSLT_ENUM_UINT32   ulErrlogDataCnfRslt = 0;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_DataCnfFailRsltProc!");

    switch(ulLrrcDataCnfRslt)
    {
        case LRRC_LMM_SEND_RSLT_FAILURE_HO:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_HO;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_CONN_REL:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_CONN_REL;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_CTRL_NOT_CONN:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_CTRL_NOT_CONN;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_TXN:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_TXN;
            break;
        case LRRC_LMM_SEND_RSLT_FAILURE_RLF:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_FAILURE_RLF;
            break;
        default:
            ulErrlogDataCnfRslt = EMM_OM_ERRLOG_SEND_RSLT_BUTT;
            break;
    }

    return ulErrlogDataCnfRslt;
}
/*****************************************************************************
Function Name   : NAS_LMM_AttachErrRecord
Description     : attach���̼�¼������Ϣ
Input           : attach fail�Լ���Ӧ�Ĵ�������
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-29 errlog �½�
*****************************************************************************/
VOS_VOID NAS_EMM_AttachErrRecord(
         VOS_VOID*                         pstAttachFail,
         EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType)
{
    EMM_ERR_INFO_ATTACH_RESULT_EVENT_STRU                   stAttachRslt;
    NAS_EMM_CN_ATTACH_ACP_STRU                              *pstCnAttachEpsOnly = VOS_NULL_PTR;
    LRRC_LMM_EST_CNF_STRU                                   *pstEstCnfMsg = VOS_NULL_PTR;
    LRRC_LMM_DATA_CNF_STRU                                  *pRrcDataCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_AttachErrRecord!!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AttachErrRecord_ENUM
,LNAS_ENTRY);
    if(VOS_NULL_PTR == pstAttachFail)
    {
        return;
    }

    /*����attach��ͬ��fail���;�������Ľṹ����*/
    switch(enErrType)
    {
        case EMM_OM_ERRLOG_TYPE_CN_REJ:
            break;
        case EMM_OM_ERRLOG_TYPE_EPS_ONLY:
            pstCnAttachEpsOnly = (NAS_EMM_CN_ATTACH_ACP_STRU*)(VOS_VOID*)pstAttachFail;
            break;
        case EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL:
            pstEstCnfMsg = (LRRC_LMM_EST_CNF_STRU*)(VOS_VOID*)pstAttachFail;
            break;
        case EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL:
            pRrcDataCnf = (LRRC_LMM_DATA_CNF_STRU*)(VOS_VOID*)pstAttachFail;
            break;
        case EMM_OM_ERRLOG_TYPE_TIMEOUT:
        case EMM_OM_ERRLOG_TYPE_LRRC_REL:
            break;
        default:
            NAS_LMM_PUBM_LOG_ERR("NAS_EMM_AttachErrRecord: Err Type");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_AttachErrRecord_ENUM
,LNAS_ERROR);
            return;
    }

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ATTACH_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_ATTACH_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stAttachRslt, ulLength, 0x00, ulLength);

    /*���attach fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stAttachRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_ATTACH_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));
    stAttachRslt.enErrType = enErrType;

    /*lint -e613*/
    /*������attach rej�����attach fail�쳣��ص���Ϣ��Ŀǰ���ܾ�ԭ��ֵ���Լ�attach����*/
    if(EMM_OM_ERRLOG_TYPE_CN_REJ == stAttachRslt.enErrType)
    {
        stAttachRslt.stAttachCnRej.enCnRejCause = NAS_LMM_CnCauseProc(NAS_EMM_GLO_AD_GetAttRejCau());
        stAttachRslt.stAttachCnRej.enOriginalRejectCause =
                           NAS_LMM_CnCauseProc(NAS_MML_GetOriginalRejectCause(NAS_EMM_GLO_AD_GetAttRejCau()));
        stAttachRslt.stAttachCnRej.enReqType = (VOS_UINT16)NAS_EMM_GLO_GetCnAttReqType();
    }
    else if(EMM_OM_ERRLOG_TYPE_EPS_ONLY == stAttachRslt.enErrType)
    {
        if (NAS_EMM_BIT_SLCT == pstCnAttachEpsOnly->ucBitOpEmmCau)
        {
            stAttachRslt.stAttachCnRej.enCnRejCause = NAS_LMM_CnCauseProc(pstCnAttachEpsOnly->ucEMMCause); /* [false alarm]:���뱣֤������ʿ�ָ�� */
            /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, begin
            attach accept�е�ԭ�򲻻ᱻ�滻 */
            stAttachRslt.stAttachCnRej.enOriginalRejectCause = NAS_LMM_CnCauseProc(pstCnAttachEpsOnly->ucEMMCause);
        }
        else
        {
            stAttachRslt.stAttachCnRej.enCnRejCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
            stAttachRslt.stAttachCnRej.enOriginalRejectCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
        }
        stAttachRslt.stAttachCnRej.enReqType = (VOS_UINT16)NAS_EMM_GLO_GetCnAttReqType();
    }
    else if(EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL == stAttachRslt.enErrType)
    {
        stAttachRslt.enEstCnfRslt = NAS_LMM_EstCnfFailRsltProc(pstEstCnfMsg->enResult);/* [false alarm]:���뱣֤������ʿ�ָ�� */
    }
    else if(EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL == stAttachRslt.enErrType)
    {
        stAttachRslt.enDataCnfRslt = NAS_LMM_DataCnfFailRsltProc(pRrcDataCnf->enSendRslt);/* [false alarm]:���뱣֤������ʿ�ָ�� */
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_AttachErrRecord: No item to Save!");
    }
    /*lint +e613*/
    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stAttachRslt.stPositionInfo));

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stAttachRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_AttachErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_AttachErrRecord_ENUM
,LNAS_FUNCTION_LABEL1,
                                        ulLength, ulResult);
    }

    return;
}

 /*****************************************************************************
 Function Name   :  NAS_LMM_TauTypeTrans
 Description     :  ����TAU�����뷢��OM��TAU����ӳ��
 Input           :

 Output          :
 Return          :

 History         :
   1.lifuxin 00253982         2014-12-30  �½�
*****************************************************************************/
EMM_ERR_LOG_TAU_TYPE_ENUM_UINT16  NAS_LMM_TauTypeTrans(NAS_EMM_CN_TAU_TYPE_ENUM_UINT32 ulTauType)
{
    EMM_ERR_LOG_TAU_TYPE_ENUM_UINT16   ulErrTauType = 0;

    switch(ulTauType)
    {
        case NAS_EMM_CN_TAU_TYPE_TA_UPDATING:
            ulErrTauType = EMM_ERR_LOG_TA_UPDATING;
            break;

        case NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING:
            ulErrTauType = EMM_ERR_LOG_COMBINED_TA_LA_UPDATING;
            break;

        case NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI:
            ulErrTauType = EMM_ERR_LOG_COMBINED_TA_LA_WITH_IMSI;
            break;

        case NAS_EMM_CN_TAU_TYPE_PERIODIC_UPDATING:
            if(NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
            {
                ulErrTauType = EMM_ERR_LOG_PS_PERIODIC_UPDATING;
            }
            else if(NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
            {
                ulErrTauType = EMM_ERR_LOG_CS_PS_PERIODIC_UPDATING;
            }
            else
            {

            }
            break;

        default:
            break;
    }

    return ulErrTauType;
}


/*****************************************************************************
Function Name   : NAS_LMM_TAUErrRecord
Description     : TAU���̼�¼������Ϣ
Input           : TAU fail�Լ���Ӧ�Ĵ�������
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog �½�
*****************************************************************************/
VOS_VOID NAS_EMM_TAUErrRecord(
         VOS_VOID*                         pstTAUFail,
         EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType)
{
    EMM_ERR_INFO_TAU_RESULT_EVENT_STRU                      stTAURslt;
    NAS_EMM_CN_TAU_ACP_STRU                                 *pstCnTAUEpsOnly = VOS_NULL_PTR;
    LRRC_LMM_EST_CNF_STRU                                   *pstEstCnfMsg = VOS_NULL_PTR;
    LRRC_LMM_DATA_CNF_STRU                                  *pRrcDataCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_TAUErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_TAUErrRecord_ENUM
,LNAS_ENTRY);
    if(VOS_NULL_PTR == pstTAUFail)
    {
        return;
    }

    /*����attach��ͬ��fail���;�������Ľṹ����*/
    switch(enErrType)
    {
        case EMM_OM_ERRLOG_TYPE_CN_REJ:
            break;
        case EMM_OM_ERRLOG_TYPE_EPS_ONLY:
            pstCnTAUEpsOnly = (NAS_EMM_CN_TAU_ACP_STRU*)(VOS_VOID*)pstTAUFail;
            break;
        case EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL:
            pstEstCnfMsg = (LRRC_LMM_EST_CNF_STRU*)(VOS_VOID*)pstTAUFail;
            break;
        case EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL:
            pRrcDataCnf = (LRRC_LMM_DATA_CNF_STRU*)(VOS_VOID*)pstTAUFail;
            break;
        case EMM_OM_ERRLOG_TYPE_TIMEOUT:
        case EMM_OM_ERRLOG_TYPE_LRRC_REL:
            break;
        default:
            NAS_LMM_PUBM_LOG_ERR("NAS_EMM_TAUErrRecord: Err Type");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_TAUErrRecord_ENUM
,LNAS_ERROR);
            return;
    }

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_TAU_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_TAU_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stTAURslt, ulLength, 0x00, ulLength);

    /*���TAU fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stTAURslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_TAU_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));
    stTAURslt.enErrType = enErrType;

    /*lint -e613*/
    /*������TAU rej�����TAU fail�쳣��ص���Ϣ��Ŀǰ���ܾ�ԭ��ֵ���Լ�TAU����*/
    if(EMM_OM_ERRLOG_TYPE_CN_REJ == stTAURslt.enErrType)
    {
        stTAURslt.stTauCnRej.enCnRejCause = NAS_LMM_CnCauseProc(NAS_EMM_TAU_GetEmmTauCnRejCause());
        stTAURslt.stTauCnRej.enOriginalRejectCause =
                              NAS_LMM_CnCauseProc(NAS_MML_GetOriginalRejectCause(NAS_EMM_TAU_GetEmmTauCnRejCause()));
        stTAURslt.stTauCnRej.enReqType = NAS_LMM_TauTypeTrans(NAS_EMM_TAU_GetTAUtype());
    }
    else if(EMM_OM_ERRLOG_TYPE_EPS_ONLY == stTAURslt.enErrType)
    {
        if (NAS_EMM_BIT_SLCT == pstCnTAUEpsOnly->ucBitOpEmmCau)
        {
            stTAURslt.stTauCnRej.enCnRejCause = NAS_LMM_CnCauseProc(pstCnTAUEpsOnly->ucEMMCause);/* [false alarm]:���뱣֤������ʿ�ָ�� */
            /* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, begin
            tau accept�е�cause�������滻������ԭʼ�ܾ�ԭ��ֵ�������ԭ��һ�� */
            stTAURslt.stTauCnRej.enOriginalRejectCause = NAS_LMM_CnCauseProc(pstCnTAUEpsOnly->ucEMMCause);
        }
        else
        {
            stTAURslt.stTauCnRej.enCnRejCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
            stTAURslt.stTauCnRej.enOriginalRejectCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
        }
        stTAURslt.stTauCnRej.enReqType = NAS_LMM_TauTypeTrans(NAS_EMM_TAU_GetTAUtype());
    }
    else if(EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL == stTAURslt.enErrType)
    {
        stTAURslt.enEstCnfRslt = NAS_LMM_EstCnfFailRsltProc(pstEstCnfMsg->enResult);/* [false alarm]:���뱣֤������ʿ�ָ�� */
    }
    else if(EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL == stTAURslt.enErrType)
    {
        stTAURslt.enDataCnfRslt = NAS_LMM_DataCnfFailRsltProc(pRrcDataCnf->enSendRslt);/* [false alarm]:���뱣֤������ʿ�ָ�� */
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_TAUErrRecord: No item to Save!");
    }
    /*lint +e613*/

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stTAURslt.stPositionInfo));
    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stTAURslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_TAUErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_TAUErrRecord_ENUM
,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return;
}


/*****************************************************************************
Function Name   : NAS_EMM_DetachErrRecord
Description     : Detach���̼�¼������Ϣ,Ŀǰֻ���������detach�ĳ���
Input           : �����detach�Ľṹ
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog �½�
*****************************************************************************/
VOS_VOID NAS_EMM_DetachErrRecord(
        NAS_EMM_CN_DETACH_REQ_MT_STRU       *pstCnDetach)
{
    EMM_ERR_INFO_MT_DETACH_RESULT_EVENT_STRU                stDetachRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_DetachErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DetachErrRecord_ENUM
,LNAS_ENTRY);
    if(VOS_NULL_PTR == pstCnDetach)
    {
       return;
    }

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_DETACH_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_MT_DETACH_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stDetachRslt, ulLength, 0x00, ulLength);

    /*���Cn Detach fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stDetachRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_DETACH_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*���Cn Detach����ϱ���*/
    /*���������ԭ��ֵ����ֱ����䣬�������ԭ��ֵ�������ó�NULL*/
    if(NAS_EMM_BIT_SLCT == NAS_EMM_GLO_AD_OP_GetDetEmmCau())
    {
        stDetachRslt.enCnDetCause = NAS_LMM_CnCauseProc(NAS_EMM_GLO_AD_GetDetEmmCau());
        stDetachRslt.enOriginalRejectCause = NAS_LMM_CnCauseProc(NAS_MML_GetOriginalRejectCause(NAS_EMM_GLO_AD_GetDetEmmCau()));
    }
    else
    {
        stDetachRslt.enCnDetCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
        stDetachRslt.enOriginalRejectCause = EMM_OM_ERRLOG_CN_CAUSE_NULL;
    }
    stDetachRslt.enCnDetReqType = pstCnDetach->ucDetType;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stDetachRslt.stPositionInfo));
    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stDetachRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_DetachErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_DetachErrRecord_ENUM
,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_NorServiceErrRecord
Description     : Normal Service ��������쳣�ϱ�
Input           :
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog �½�
*****************************************************************************/
VOS_VOID NAS_EMM_NorServiceErrRecord(
            VOS_VOID*                         pstNorServiceFail,
            EMM_OM_ERRLOG_TYPE_ENUM_UINT16    enErrType)

{
    EMM_ERR_INFO_NOR_SERVICE_RESULT_EVENT_STRU              stNorServerRslt;
    NAS_EMM_CN_SER_REJ_STRU                                 *pstCnSerRej = VOS_NULL_PTR;
    LRRC_LMM_EST_CNF_STRU                                   *pstEstCnfMsg = VOS_NULL_PTR;
    LRRC_LMM_DATA_CNF_STRU                                  *pRrcDataCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_NorServiceErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_NorServiceErrRecord_ENUM
,LNAS_ENTRY);
    if(VOS_NULL_PTR == pstNorServiceFail)
    {
        return;
    }

    /*����service��ͬ��fail���;�������Ľṹ����*/
    switch(enErrType)
    {
        case EMM_OM_ERRLOG_TYPE_CN_REJ:
            pstCnSerRej = (NAS_EMM_CN_SER_REJ_STRU*)(VOS_VOID*)pstNorServiceFail;
            break;
        case EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL:
            pstEstCnfMsg = (LRRC_LMM_EST_CNF_STRU*)(VOS_VOID*)pstNorServiceFail;
            break;
        case EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL:
            pRrcDataCnf = (LRRC_LMM_DATA_CNF_STRU*)(VOS_VOID*)pstNorServiceFail;
            break;
        case EMM_OM_ERRLOG_TYPE_TIMEOUT:
        case EMM_OM_ERRLOG_TYPE_LRRC_REL:
            break;
        default:
            NAS_LMM_PUBM_LOG_ERR("NAS_EMM_NorServiceErrRecord: Err Type");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_NorServiceErrRecord_ENUM
,LNAS_ERROR);
            return;
    }

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_NOR_SERVICE_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_NOR_SERVICE_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stNorServerRslt, ulLength, 0x00, ulLength);

    /*���Service�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stNorServerRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_NOR_SERVICE_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stNorServerRslt.enErrType = enErrType;

    /*lint -e613*/
    if(EMM_OM_ERRLOG_TYPE_CN_REJ == stNorServerRslt.enErrType)
    {
        stNorServerRslt.stNorServiceCnRej.enCnRejCause =
                                        NAS_LMM_CnCauseProc(pstCnSerRej->ucEMMCause);/* [false alarm]:���뱣֤������ʿ�ָ�� */
        stNorServerRslt.stNorServiceCnRej.enOriginalRejectCause  =
                                        NAS_LMM_CnCauseProc(NAS_MML_GetOriginalRejectCause(pstCnSerRej->ucEMMCause));
    }
    else if(EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL == stNorServerRslt.enErrType)
    {
        stNorServerRslt.enEstCnfRslt = NAS_LMM_EstCnfFailRsltProc(pstEstCnfMsg->enResult);/* [false alarm]:���뱣֤������ʿ�ָ�� */
    }
    else if(EMM_OM_ERRLOG_TYPE_DATA_CNF_FAIL == stNorServerRslt.enErrType)
    {
        stNorServerRslt.enDataCnfRslt = NAS_LMM_DataCnfFailRsltProc(pRrcDataCnf->enSendRslt);/* [false alarm]:���뱣֤������ʿ�ָ�� */
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_NorServiceErrRecord: No item need to Save!");
    }
    /*lint +e613*/

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stNorServerRslt.stPositionInfo));

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stNorServerRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_NorServiceErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_NorServiceErrRecord_ENUM
,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_ExtServiceErrRecord
Description     : Service ��������쳣�ϱ�
Input           :
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog �½�
*****************************************************************************/
VOS_VOID NAS_EMM_ExtServiceErrRecord(
        NAS_EMM_CN_CAUSE_ENUM_UINT8                 enCnRejCause,
        EMM_OM_LMM_CSFB_FAIL_CAUSE_ENUM_UINT8       enCsfbFailCause)
{
    EMM_ERR_INFO_EXT_SERVICE_RESULT_EVENT_STRU              stExtServerRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_ExtServiceErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ExtServiceErrRecord_ENUM
,LNAS_ENTRY);

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_EXT_SERVICE_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_EXT_SERVICE_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stExtServerRslt, ulLength, 0x00, ulLength);

    /*���Service�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stExtServerRslt.stHeader,
                                    VOS_GetModemIDFromPid(PS_PID_MM),
                                    LNAS_OM_ERRLOG_ALM_ID_EXT_SERVICE_FAIL,
                                    usLevel,
                                    VOS_GetSlice(),
                                    (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stExtServerRslt.enCsfbFailCause = enCsfbFailCause;
    stExtServerRslt.enCnRejCause = NAS_LMM_CnCauseProc(enCnRejCause);
    stExtServerRslt.enOriginalRejectCause =
                     NAS_LMM_CnCauseProc(NAS_MML_GetOriginalRejectCause(enCnRejCause));

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stExtServerRslt.stPositionInfo));

    /*
     ���쳣��Ϣд��Buffer��
     ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
    */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stExtServerRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_ExtServiceErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_ExtServiceErrRecord_ENUM
,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_DetachErrRecord
Description     : PS IMSI PAGING���̵��¶����ϱ�errlog��Ϣ
Input           : IMSI PAGING�ṹ
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog �½�
 2. wangchen 00209181 2015-08-04 Modify:CHR
*****************************************************************************/
VOS_VOID NAS_EMM_PagingErrRecord
(
    EMM_OM_ERRLOG_PAGING_ENUM_UINT16  enPagingType,
    EMM_OM_LMM_PAGING_FAIL_CAUSE_ENUM_UINT8 enPagingFailCause
)
{
    EMM_ERR_INFO_PAGING_RESULT_EVENT_STRU                   stPagingRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;


    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PagingErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PagingErrRecord_ENUM
,LNAS_ENTRY);

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);


    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_PAGING_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stPagingRslt, ulLength, 0x00, ulLength);

    /*���PS IMSI PAGING fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stPagingRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*���IMSI PAGING����ϱ���*/
    stPagingRslt.enPagingProcess = enPagingType;

    stPagingRslt.enPagingFailCause  = enPagingFailCause;

    stPagingRslt.enMainState            = NAS_LMM_GetEmmCurFsmMS();
    stPagingRslt.enSubState             = NAS_LMM_GetEmmCurFsmSS();

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stPagingRslt.stPositionInfo));

    /* ��pagingֱ�Ӷ���ʱ�����������ϱ� */
    if (EMM_OM_LMM_PAGING_FAIL_CAUSE_ABNORMAL_STATUS == enPagingFailCause)
    {
        NAS_EMM_SndAcpuOmFaultErrLogInd(&stPagingRslt, ulLength, LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL);
    }
    else
    {
        /*
           ���쳣��Ϣд��Buffer��
           ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
         */
        ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stPagingRslt, ulLength);
        if (ulResult != ulLength)
        {
            NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_PagingErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
            TLPS_PRINT2LAYER_ERROR2(NAS_EMM_PagingErrRecord_ENUM ,LNAS_FUNCTION_LABEL1, ulLength, ulResult);
        }
    }
    return;
}
/*****************************************************************************
Function Name   : NAS_EMM_ImprovePerformceeErrReport
Description     : �û�����������Ŀ�����ϱ�
Input           : IMSI PAGING�ṹ
Output          : None
Return          : None

History         :
 1. wangchen 00209181 2015-08-05 Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_ImprovePerformceeErrReport
(
    EMM_OM_ERRLOG_IMPROVEMENT_TYPE_ENUM_UINT16  enImproveType
)
{
    EMM_ERR_INFO_IMPROVEMENT_EVENT_STRU                     stImproveEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_ImprovePerformceeErrReport!!");

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_IMPROVE_PERFORMCE);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_IMPROVEMENT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stImproveEvent, ulLength, 0x00, ulLength);

    /*������������ĳ���ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stImproveEvent.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_IMPROVE_PERFORMCE,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* �����Ŀ�������������� */
    stImproveEvent.enImproveType    = enImproveType;

    /* �����¼������ϱ���OM */
    NAS_EMM_SndAcpuOmFaultErrLogInd(&stImproveEvent, ulLength, LNAS_OM_ERRLOG_ALM_ID_IMPROVE_PERFORMCE);

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_RatErrRecord
Description     : RAT���̵��¶����ϱ�errlog��Ϣ
Input           : ���¶�������ϵͳ����
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2014-12-30 errlog �½�
*****************************************************************************/
VOS_VOID NAS_EMM_RatErrRecord(
            EMM_OM_ERRLOG_RAT_ENUM_UINT16           enRatType)
{
    EMM_ERR_INFO_RAT_RESULT_EVENT_STRU                      stRatRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_RatErrRecord!!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_RatErrRecord_ENUM
,LNAS_ENTRY);

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_PAGING_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_RAT_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stRatRslt, ulLength, 0x00, ulLength);

    /*���rat�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stRatRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_RAT_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*���RAT����ϱ���*/
    stRatRslt.enRatProcess = enRatType;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stRatRslt.stPositionInfo));

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stRatRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_RatErrRecord: Push buffer error. ulLength =, ulResult = ", ulLength, ulResult);
        TLPS_PRINT2LAYER_ERROR2(NAS_EMM_RatErrRecord_ENUM,LNAS_FUNCTION_LABEL1,ulLength, ulResult);
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_LocalDetachErrRecord
Description     : Local detach������errlog�洢
Input           : local detach������
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2015-02-10 errlog �½�
*****************************************************************************/
VOS_VOID NAS_EMM_LocalDetachErrRecord(
        EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16       enLocalDetType)
{
    EMM_ERR_INFO_LOCAL_DETACH_RESULT_EVENT_STRU             stLocalDetRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_LocalDetachErrRecord!!");

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_LOCAL_DETACH_FAIL);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_LOCAL_DETACH_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stLocalDetRslt, ulLength, 0x00, ulLength);

    /*���Cn Detach fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stLocalDetRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_LOCAL_DETACH_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*���Cn Detach����ϱ���*/
    stLocalDetRslt.enLocalDetType = enLocalDetType;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stLocalDetRslt.stPositionInfo));
    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stLocalDetRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_LocalDetachErrRecord: Push buffer error.");
    }

    return;
}

/*****************************************************************************
Function Name   : NAS_EMM_AuthCnFailErrRecord
Description     : Auth Fail������errlog�洢
Input           :
Output          : None
Return          : None

History         :
 1. lifuxin 00253982 2015-02-10 errlog �½�
*****************************************************************************/
VOS_VOID NAS_EMM_AuthCnFailErrRecord(
        EMM_OM_ERRLOG_AUTH_FAIL_ENUM_UINT16       enErrAuthFail)
{
    EMM_ERR_INFO_AUTH_FAIL_RESULT_EVENT_STRU                stAuthCnFailRslt;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_AuthCnFailErrRecord!!");

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_AUTH_REJ);
    ulIsLogRecord = NAS_EMM_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(EMM_ERR_INFO_AUTH_FAIL_RESULT_EVENT_STRU);

    NAS_LMM_MEM_SET_S(&stAuthCnFailRslt, ulLength, 0x00, ulLength);

    /*���Cn Detach fail�쳣����ͷ*/
    NAS_EMM_COMM_BULID_ERRLOG_HEADER_INFO(&stAuthCnFailRslt.stHeader,
                                      VOS_GetModemIDFromPid(PS_PID_MM),
                                      LNAS_OM_ERRLOG_ALM_ID_AUTH_REJ,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /*���Cn Detach����ϱ���*/
    stAuthCnFailRslt.enAuthFail = enErrAuthFail;

    (VOS_VOID)NAS_LMM_GetPositionInfo(&(stAuthCnFailRslt.stPositionInfo));

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_EMM_PutErrLogRingBuf((VOS_CHAR *)&stAuthCnFailRslt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_AuthCnFailErrRecord: Push buffer error.");
    }

    return;
}
/*****************************************************************************
Function Name   : NAS_EMM_SndAcpuOmFaultErrLogInd
Description     : CHR��Ϣ�����ϱ�
Input           :
Output          : None
Return          : None

History         :
 1. wangchen 00209181   2015-08-05  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SndAcpuOmFaultErrLogInd(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulDataLen,
    LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16   usAlmId
)
{
    OM_FAULT_ERR_LOG_IND_STRU                              *pstFaultRptInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLen;
    VOS_UINT32                                              ulContentAddr;
    EMM_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_UINT16              enReportType;

    /* ������Ϣ�ṹ�ڴ� */
    /*lint -e961*/
    ulMsgLen     = sizeof(OM_FAULT_ERR_LOG_IND_STRU) - 4 + ulDataLen;
    /*lint +e961*/
    pstFaultRptInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(ulMsgLen);
    if (VOS_NULL_PTR == pstFaultRptInd)
    {
        return;
    }

    /* ������Ϣ�ṹ�� */
    pstFaultRptInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFaultRptInd->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstFaultRptInd->ulReceiverPid     = MSP_PID_DIAG_APP_AGENT;
    pstFaultRptInd->ulSenderPid       = PS_PID_MM;
    pstFaultRptInd->ulMsgName         = ID_OM_FAULT_ERR_LOG_IND;

    enReportType = NAS_EMM_GetErrLogUnsoliReportType(usAlmId);

    if (EMM_ERR_LOG_FAULT_REPORT == enReportType)
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_FAULT_REPORT;
    }
    else if (EMM_ERR_LOG_ALARM_REPORT == enReportType)
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_ALARM_REPORT;
    }
    else
    {
        pstFaultRptInd->ulMsgType     = OM_ERR_LOG_MSG_TYPE_BUTT;
    }

    pstFaultRptInd->ulMsgSN           = 0;
    pstFaultRptInd->ulRptlen          = ulDataLen;

    ulContentAddr                     = (VOS_UINT32)pstFaultRptInd->aucContent;

    NAS_LMM_MEM_CPY_S((VOS_UINT8 *)ulContentAddr, ulDataLen, pData, ulDataLen);

    /* ������Ϣ��ACPU OMģ�� */
    NAS_LMM_SEND_MSG(pstFaultRptInd);

    return;
}
#endif


/*****************************************************************************
 Function Name   : NAS_LMM_ExportEmmInfoExcLog
 Description     : ��λʱ����Nas��Ϣ
 Input           : pulExcLogAddr ���ݱ����ַ
 Output          : pulLeftSpace ʣ��ռ䳤��
 Return          : Nasʹ�õĿռ��С

 History         :
    1.x00183216     2013-9-17  Draft Enact
    2.leixiantiao 00258641 2014-12-26
*****************************************************************************/
VOS_UINT32 NAS_LMM_ExportEmmInfoExcLog(VOS_UINT32* pulExcLogAddr, VOS_UINT32 *pulLeftSpace)
{
    VOS_UINT32                     *pulSaveAddr = pulExcLogAddr;
    VOS_UINT32                      ulSaveSize = 0;
    VOS_UINT32                      ulstNasInfoSize = 0;
    LNAS_EXC_LOG_STRU               stNasInfo;
    VOS_UINT32                      ulLoop;

    if((0 == *pulLeftSpace)||(NAS_EMM_NULL_PTR == pulExcLogAddr))
    {
        return ulSaveSize;
    }
    NAS_LMM_MEM_SET_S(&stNasInfo, sizeof(LNAS_EXC_LOG_STRU), 0, sizeof(LNAS_EXC_LOG_STRU));
    /* �����Ҫ��������Ϣ */
    for(ulLoop = 0; ulLoop < NAS_LMM_PARALLEL_FSM_BUTT; ulLoop++)
    {
        stNasInfo.astCurFsm[ulLoop].enFsmId = NAS_LMM_GetCurFsmAddr(ulLoop)->enFsmId;
        stNasInfo.astCurFsm[ulLoop].enMainState = NAS_LMM_GetCurFsmAddr(ulLoop)->enMainState;
        stNasInfo.astCurFsm[ulLoop].enStaTId = NAS_LMM_GetCurFsmAddr(ulLoop)->enStaTId;
        stNasInfo.astCurFsm[ulLoop].enSubState = NAS_LMM_GetCurFsmAddr(ulLoop)->enSubState;
    }
    stNasInfo.ucRrcConnState = NAS_EMM_GetConnState();
    stNasInfo.ulCurLteState = NAS_EMM_GetCurLteState();
    /*��ȡ��������*/
    ulstNasInfoSize = sizeof(LNAS_EXC_LOG_STRU);
    /* ����EMM״̬���Ͱ�ȫ״̬�� */
    if(ulstNasInfoSize < *pulLeftSpace)
    {
        NAS_LMM_MEM_CPY_S((VOS_VOID *)pulSaveAddr, *pulLeftSpace, &stNasInfo,ulstNasInfoSize);
        ulSaveSize = ulstNasInfoSize;
        *pulLeftSpace -= ulstNasInfoSize;
    }
    else
    {
        NAS_LMM_MEM_CPY_S((VOS_VOID *)pulSaveAddr, *pulLeftSpace, &stNasInfo, *pulLeftSpace);
        ulSaveSize = *pulLeftSpace;
        *pulLeftSpace = 0;
    }
    return ulSaveSize;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmDamPara
 Description     : ��DAM��ز��������OM
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmDamPara(VOS_VOID)
{
    NAS_EMM_OM_DAM_PARA_LOG_STRU            *pstMsg = VOS_NULL_PTR;
    NAS_MM_NETWORK_ID_STRU                  *pstAreaInfo;
    NAS_MM_DAM_PLMN_LIST_STRU               *pstDamPlmnList;
    NAS_DAM_IMSI_PLMN_LIST                  *pstImsiPlmnList;

    pstDamPlmnList  = NAS_EMM_GetEmmInfoDamParaPlmnListAddr();
    pstImsiPlmnList = NAS_EMM_GetEmmInfoDamParaImsiPlmnListAddr();
    pstAreaInfo    = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    pstMsg = (NAS_EMM_OM_DAM_PARA_LOG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_DAM_PARA_LOG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SndOmDamPara: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndOmDamPara_ENUM
,LNAS_NULL_PTR);
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_DAM_PARA_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_DAM_PARA_LOG;

    /* CService���ֵ�͵�ǰ���� */
    pstMsg->ulCServiceMax               = NAS_EMM_GetEmmInfoDamParaCserviceMax();
    pstMsg->ulCService                  = NAS_EMM_GetEmmInfoDamParaCserviceCnt();

    /* ��ǰפ����PLMN ID��DAM PLMN LIST */
    NAS_LMM_MEM_SET_S(  &pstMsg->stCampPlmnId,
                        sizeof(NAS_MM_PLMN_ID_STRU),
                        0,
                        sizeof(NAS_MM_PLMN_ID_STRU));

    if(NAS_EMM_BIT_SLCT == pstAreaInfo->bitOpPlmnId)
    {
        NAS_LMM_MEM_CPY_S(  &pstMsg->stCampPlmnId,
                            sizeof(NAS_MM_PLMN_ID_STRU),
                            &pstAreaInfo->stPlmnId,
                            sizeof(NAS_MM_PLMN_ID_STRU));
    }

    NAS_LMM_MEM_CPY_S(  &pstMsg->stImsiPlmnList,
                        sizeof(NAS_DAM_IMSI_PLMN_LIST),
                        pstImsiPlmnList,
                        sizeof(NAS_DAM_IMSI_PLMN_LIST));

    NAS_LMM_MEM_CPY_S(  &pstMsg->stDamPlmnList,
                        sizeof(NAS_MM_DAM_PLMN_LIST_STRU),
                        pstDamPlmnList,
                        sizeof(NAS_MM_DAM_PLMN_LIST_STRU));

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmLmmCommConfigPara
 Description     : ��LMM�������󹫹����������OM
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmCommConfigPara
(
    LNAS_LMM_NV_COMM_CONFIG_PARA_STRU   *pstNvCommPara
)
{
    NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_COMM_CONFIG_PARA_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_COMM_CONFIG_PARA_LOG;

    NAS_LMM_MEM_CPY_S(  &pstMsg->stNvCommPara,
                        sizeof(LNAS_LMM_NV_COMM_CONFIG_PARA_STRU),
                        pstNvCommPara,
                        sizeof(LNAS_LMM_NV_COMM_CONFIG_PARA_STRU));

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmRej19Cnt
 Description     : ��LMM���ܾ�#19����ؼ��������OM
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    sunjitan 00193151      2015-01-04  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmRej19Cnt(VOS_VOID)
{
    NAS_EMM_OM_REJ19_CNT_LOG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_EMM_OM_REJ19_CNT_LOG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_REJ19_CNT_LOG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_REJ19_CNT_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_REJ19_CNT_LOG;

    /* ��䵱ǰ�ﵽ�ĳ��Դ��� */
    pstMsg->ulRej19AtmptCnt = NAS_EMM_GLO_AD_GetAttRej19AtmpCnt();

    /* ���NV�����õ�����Դ�����ʶ */
    pstMsg->ulRej19AtmptCntFlag = NAS_EMM_GetEmmInfoRej19AtmptCntFlag();

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmSetTmoActiveFlag
 Description     : ����TMO��active flag��ʶʱ���ϱ�OM��Ϣ��HIDS
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    sunjitan 00193151      2015-03-15  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmSetTmoActiveFlag(VOS_UINT32 ulTmoActiveFlagStatus)
{
    NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_SET_TMO_ACTIVE_FLAG_LOG;

    /* ��д��ʶ״̬ */
    pstMsg->ulTmoActiveFlagStatus       = ulTmoActiveFlagStatus;

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}
/*****************************************************************************
 Function Name   :NAS_LMM_SndDebugInfoInd
 Description     : EMM��ά�ɲ⣬������ǰ״̬
 Input           :
 Output          : None
 Return          :

 History         :
    1.leixiantiao     2014-10-17  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_SndDebugInfoInd(VOS_UINT32 ulFileName, VOS_UINT32 ulLineNo, VOS_UINT16 ucPara1, VOS_UINT16 ucPara2, VOS_UINT16 ucPara3, VOS_UINT16 ucPara4)
{
    NAS_EMM_DBG_INFO_IND_STRU            stMsg = {0};
    NAS_LMM_FSM_STATE_STRU               *pstEmmCurState  = NAS_LMM_GetEmmCurFsmAddr();
    NAS_LMM_FSM_STATE_STRU               *pstSecuCurState = NAS_LMM_GetSecuFsmAddr();

    stMsg.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stMsg.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid         = PS_PID_MM;
    stMsg.ulReceiverPid       = PS_PID_MM;
    stMsg.ulLength            = sizeof(NAS_EMM_DBG_INFO_IND_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    stMsg.ulMsgId             = ID_NAS_EMM_OM_DEBUG_INFO_LOG;
    stMsg.ulFileName          = ulFileName;
    stMsg.ulLineNo            = ulLineNo;
    stMsg.enEmmMainState      = pstEmmCurState->enMainState ;
    stMsg.enEmmSubState       = pstEmmCurState->enSubState;
    stMsg.enSecuMainState     = pstSecuCurState->enMainState ;
    stMsg.enSecuSubState      = pstSecuCurState->enSubState;
    stMsg.ucPara1             = ucPara1;
    stMsg.ucPara2             = ucPara2;
    stMsg.ucPara3             = ucPara3;
    stMsg.ucPara4             = ucPara4;

    #if (VOS_WIN32 != VOS_OS_VER)
        (VOS_VOID)LTE_MsgHook((VOS_VOID*)&stMsg);
    #endif

        return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauTotalCounter
 Description     : ����TAU�������
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachTotalCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttTolTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauSuccCounter
 Description     : ����TAU�ɹ�����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachSuccCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttSuccTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauBarFailCounter
 Description     : ����TAU��bar����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachBarFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttBarFailTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauNoRfFailCounter
 Description     : ����TAU NoRf����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachNoRfFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttNoRfFailTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauEstFailCounter
 Description     : ����TAU EST Fail����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachEstFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttEstFailTimes()++;
    return NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   : NAS_LMM_AddTauExpFailCounter
 Description     : ����TAU��ʱ����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachExpFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttExpFailTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauRejFailCounter
 Description     : ����TAU���ܴ���
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachRejFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttRejFailTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauRelFailCounter
 Description     : ����TAU Rel����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachRelFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttRelFailTimes()++;
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauEsmFailCounter
 Description     : ����TAU ESM Fail����:ESM����ʧ��
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachEsmFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttEsmFailTimes()++;
    return NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   : NAS_LMM_AddTauDataReqFailCounter
 Description     : ����TAU��Comm��������ֱ������ʧ�ܴ���
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddAttachDataReqFailCounter(VOS_VOID)
{
    NAS_EMM_GetOmSuccRationAttDataReqFailTimes()++;
    return NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :Attach fail Other Cause����ͳ��
 Input           :None
 Return          :VOS_UINT32 �����Ƿ�����

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddAttachOtherFailCounter(VOS_VOID)
{
    VOS_UINT16 usTimes = 0;

    /* ���㵱ǰ��¼Attach�ɹ���ʧ�ܴ����ܺ� */
    usTimes = NAS_EMM_GetOmSuccRationAttBarFailTimes()
                + NAS_EMM_GetOmSuccRationAttNoRfFailTimes()
                + NAS_EMM_GetOmSuccRationAttEstFailTimes()
                + NAS_EMM_GetOmSuccRationAttExpFailTimes()
                + NAS_EMM_GetOmSuccRationAttRejFailTimes()
                + NAS_EMM_GetOmSuccRationAttEsmFailTimes()
                + NAS_EMM_GetOmSuccRationAttDataReqFailTimes()
                + NAS_EMM_GetOmSuccRationAttOtherFailTimes()
                + NAS_EMM_GetOmSuccRationAttRelFailTimes()
                + NAS_EMM_GetOmSuccRationAttSuccTimes();

     /* ��Attach��������Ƿ�ȵ�ǰAttach�ɹ���ʧ�ܴ����ܺͣ�˵����ǰ��Attach Other Fail */
     if(NAS_EMM_GetOmSuccRationAttTolTimes() > usTimes)
     {
        NAS_EMM_GetOmSuccRationAttOtherFailTimes() += (NAS_EMM_GetOmSuccRationAttTolTimes() - usTimes);
        return NAS_EMM_YES;
     }
     return NAS_EMM_NO;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :Attach�ɹ��ʱ��ؼ���ά��
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_AddAttachCounter(NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16  enCounterType)
{
    VOS_UINT32                                  ulRslt = NAS_EMM_NO;
    VOS_UINT32                                  ulIndex = 0;
    NAS_LMM_ADD_ATTACH_COUNTER_TYPE_PROC_FUN    pfAddAttachCounterProcFun = VOS_NULL_PTR;
    for(ulIndex = 0; ulIndex < g_stEmmAddAttachCounterProcTblLen; ulIndex++)
    {
        if(enCounterType == g_stEmmAddAttachCounterProcTbl[ulIndex].enCounterType)
        {
            pfAddAttachCounterProcFun = g_stEmmAddAttachCounterProcTbl[ulIndex].pfAddAttachCounterProcFun;
            break;
        }
    }
    if(VOS_NULL_PTR != pfAddAttachCounterProcFun)
    {
        ulRslt = (pfAddAttachCounterProcFun)();
    }
    if((NAS_EMM_YES == NAS_EMM_GetOmSwitchSuccRatioFlag())
        &&(NAS_EMM_YES == ulRslt)
        &&(NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL != enCounterType))
    {
        NAS_LMM_SndOmAttSuccRatioInfo();
    }
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :��¼ATTACH����Startʱ���
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachStartTimeStamp(VOS_VOID)
{
    NAS_LMM_OM_ATTACH_DELAY_INFO_STRU *pstAttachDelayInfo;
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    /* ��¼ATTACH���̷���ʱ��ǰ��ձ���ʱ������ */
    pstAttachDelayInfo = NAS_EMM_GetOmAttachDelayInfoAddr();
    NAS_LMM_MEM_SET_S(  pstAttachDelayInfo,
                        sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_STRU));
    NAS_EMM_GetOmAttachDelayInfoStartTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :��¼ATTACH REQ Sndʱ���
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachReqSndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmAttachDelayInfoReqSndTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :��¼ATTACH EST SUCCʱ���
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachEstSuccTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);
    NAS_EMM_GetOmAttachDelayInfoOpEstSucc() = NAS_EMM_BIT_SLCT;
    NAS_EMM_GetOmAttachDelayInfoEstSuccTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :��¼�յ�ATTACH ACPʱ���
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachAcpTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmAttachDelayInfoulAcceptTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :��¼ATTACH Cmp ����ʱ���
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachCmpSndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmAttachDelayInfoCmpSndTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   :NAS_LMM_AddAttachOtherFailCounter
 Description     :��¼ATTACH�������ʱ���
 Input           :None
 Return          :NONE

 History         :
    1.leixiantiao 00258641      2015-05-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SaveAttachEndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmAttachDelayInfoEndTime() = stCurrTime.ul32KTStampLowBit;
    /* ��ʱ����Ϣ�ϱ����ش����ϱ� */
    if(NAS_EMM_YES == NAS_EMM_GetOmSwitchDelayFlag())
    {
        NAS_LMM_SndOmAttachDelayInfo();
    }
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauTotalCounter
 Description     : ����TAU�������
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauTotalCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauTolalTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauTolalTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauSuccCounter
 Description     : ����TAU�ɹ�����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauSuccCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauSuccTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauSuccTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauBarFailCounter
 Description     : ����TAU��bar����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauBarFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauBarFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauBarFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauNoRfFailCounter
 Description     : ����TAU NoRf����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauNoRfFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauNoRfFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauNoRfFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauEstFailCounter
 Description     : ����TAU EST Fail����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauEstFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauEstFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauEstFailTimes()++;
    }
    return NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   : NAS_LMM_AddTauExpFailCounter
 Description     : ����TAU��ʱ����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauExpFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauExpFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauExpFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauRejFailCounter
 Description     : ����TAU���ܴ���
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauRejFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauRejFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauRejFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauRelFailCounter
 Description     : ����TAU Rel����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauRelFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauRelFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauRelFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauDataReqFailCounter
 Description     : ����TAU��Comm��������ֱ������ʧ�ܴ���
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauDataReqFailCounter(VOS_VOID)
{
    VOS_UINT8 ucFlag = NAS_EMM_NO;
    ucFlag = NAS_EMM_GetOmInterTauFlag();
    if(NAS_EMM_YES == ucFlag)
    {
        NAS_EMM_GetInterTauDatReqFailTimes()++;
    }
    else
    {
        NAS_EMM_GetIntraTauDatReqFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauOtherFailCounter
 Description     : ����TAU����ԭ��ʧ�ܴ���
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_UINT32 NAS_LMM_AddTauOtherFailCounter(VOS_VOID)
{
    VOS_UINT16 usInterTimes = 0;
    VOS_UINT16 usIntraTimes = 0;
    VOS_UINT32 ulRslt = NAS_EMM_NO;
    /* ���㵱ǰ��¼Inter Tau�ɹ���ʧ�ܴ����ܺ� */
    usInterTimes = NAS_EMM_GetInterTauSuccTimes()
                    + NAS_EMM_GetInterTauBarFailTimes()
                    + NAS_EMM_GetInterTauNoRfFailTimes()
                    + NAS_EMM_GetInterTauEstFailTimes()
                    + NAS_EMM_GetInterTauExpFailTimes()
                    + NAS_EMM_GetInterTauRejFailTimes()
                    + NAS_EMM_GetInterTauRelFailTimes()
                    + NAS_EMM_GetInterTauDatReqFailTimes()
                    + NAS_EMM_GetInterTauOtherFailTimes();

     /* ��Attach��������Ƿ�ȵ�ǰAttach�ɹ���ʧ�ܴ����ܺͣ�˵����ǰ��Attach Other Fail */
     if(NAS_EMM_GetInterTauTolalTimes() > usInterTimes)
     {
        NAS_EMM_GetInterTauOtherFailTimes() += (NAS_EMM_GetInterTauTolalTimes() - usInterTimes);
        ulRslt = NAS_EMM_YES;
     }

     /* ���㵱ǰ��¼Intra Tau�ɹ���ʧ�ܴ����ܺ� */
    usIntraTimes = NAS_EMM_GetIntraTauSuccTimes()
                    + NAS_EMM_GetIntraTauBarFailTimes()
                    + NAS_EMM_GetIntraTauNoRfFailTimes()
                    + NAS_EMM_GetIntraTauEstFailTimes()
                    + NAS_EMM_GetIntraTauExpFailTimes()
                    + NAS_EMM_GetIntraTauRejFailTimes()
                    + NAS_EMM_GetIntraTauRelFailTimes()
                    + NAS_EMM_GetIntraTauDatReqFailTimes()
                    + NAS_EMM_GetIntraTauOtherFailTimes();

     /* ��Attach��������Ƿ�ȵ�ǰAttach�ɹ���ʧ�ܴ����ܺͣ�˵����ǰ��Attach Other Fail */
     if(NAS_EMM_GetIntraTauTolalTimes() > usIntraTimes)
     {
        NAS_EMM_GetIntraTauOtherFailTimes() += (NAS_EMM_GetIntraTauTolalTimes() - usIntraTimes);
        ulRslt = NAS_EMM_YES;
     }
    return ulRslt;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddTauCounter
 Description     : ����TAU�����ݱ��ش洢����
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/

VOS_VOID NAS_LMM_AddTauCounter(NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16   enCounterType)
{
    VOS_UINT32                              ulRslt = NAS_EMM_NO;
    VOS_UINT32                              ulIndex = 0;
    NAS_LMM_ADD_TAU_COUNTER_TYPE_PROC_FUN   pfAddTauCounterProcFun = VOS_NULL_PTR;
    for(ulIndex = 0; ulIndex < g_stEmmAddTauCounterProcTblLen; ulIndex++)
    {
        if(enCounterType == g_stEmmAddTauCounterProcTbl[ulIndex].enCounterType)
        {
            pfAddTauCounterProcFun = g_stEmmAddTauCounterProcTbl[ulIndex].pfAddTauCounterProcFun;
            break;
        }
    }
    if(VOS_NULL_PTR != pfAddTauCounterProcFun)
    {
        ulRslt = (pfAddTauCounterProcFun)();
    }
    NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_AddTauCounter ulRslt = ", ulRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_AddTauCounter_ENUM
,LNAS_FUNCTION_LABEL1,ulRslt);
    if((NAS_EMM_YES == NAS_EMM_GetOmSwitchSuccRatioFlag())
        &&(NAS_EMM_YES == ulRslt)
        &&(NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL != enCounterType))
    {
        NAS_LMM_SndOmTauSuccRatioInfo();
    }
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerTotalCounter
 Description     : ����Ser�������
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerTotalCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerTolalTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerTolalTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerSuccCounter
 Description     : ����Ser�ɹ�����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerSuccCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerSuccTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerSuccTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerBarFailCounter
 Description     : ����Ser��bar����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerBarFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerBarFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerBarFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerNoRfFailCounter
 Description     : ����Ser NoRf����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerNoRfFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerNoRfFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerNoRfFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerEstFailCounter
 Description     : ����Ser EST Fail����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerOtherEstFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerEstFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerEstFailTimes()++;
    }
    return NAS_EMM_YES;
}

/*****************************************************************************
 Function Name   : NAS_LMM_AddSerExpFailCounter
 Description     : ����Ser��ʱ����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerExpFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerExpFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerExpFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerRejFailCounter
 Description     : ����Ser���ܴ���
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerRejFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerRejFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerRejFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerRelFailCounter
 Description     : ����Ser Rel����
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerRelFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerRelFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerRelFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerDataReqFailCounter
 Description     : ����Ser��Comm��������ֱ������ʧ�ܴ���
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerDataReqFailCounter(VOS_VOID)
{
    VOS_UINT8 ucMtSerFlag;
    ucMtSerFlag = NAS_EMM_GetOmMtSerFlag();
    if(NAS_EMM_YES == ucMtSerFlag)
    {
        NAS_EMM_GetMtSerDataReqFailTimes()++;
    }
    else
    {
        NAS_EMM_GetMoSerDataReqFailTimes()++;
    }
    return NAS_EMM_YES;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerOtherFailCounter
 Description     : ����Ser����ԭ��ʧ�ܴ���
 Input           :
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_AddSerOtherFailCounter(VOS_VOID)
{
    VOS_UINT16 usMtSerTimes = 0;
    VOS_UINT16 usMoSerTimes = 0;
    VOS_UINT32 ulRslt = NAS_EMM_NO;
    /* ���㵱ǰ��¼MT Tau�ɹ���ʧ�ܴ����ܺ� */
    usMtSerTimes = NAS_EMM_GetMtSerSuccTimes()
                    + NAS_EMM_GetMtSerBarFailTimes()
                    + NAS_EMM_GetMtSerNoRfFailTimes()
                    + NAS_EMM_GetMtSerEstFailTimes()
                    + NAS_EMM_GetMtSerExpFailTimes()
                    + NAS_EMM_GetMtSerRejFailTimes()
                    + NAS_EMM_GetMtSerRelFailTimes()
                    + NAS_EMM_GetMtSerDataReqFailTimes()
                    + NAS_EMM_GetMtSerOtherFailTimes();

     /* ��Attach��������Ƿ�ȵ�ǰAttach�ɹ���ʧ�ܴ����ܺͣ�˵����ǰ��Attach Other Fail */
     if(NAS_EMM_GetMtSerTolalTimes() > usMtSerTimes)
     {
        NAS_EMM_GetMtSerOtherFailTimes() += (NAS_EMM_GetMtSerTolalTimes() - usMtSerTimes);
        ulRslt = NAS_EMM_YES;
     }

     /* ���㵱ǰ��¼Intra Tau�ɹ���ʧ�ܴ����ܺ� */
    usMoSerTimes = NAS_EMM_GetMoSerSuccTimes()
                    + NAS_EMM_GetMoSerBarFailTimes()
                    + NAS_EMM_GetMoSerNoRfFailTimes()
                    + NAS_EMM_GetMoSerEstFailTimes()
                    + NAS_EMM_GetMoSerExpFailTimes()
                    + NAS_EMM_GetMoSerRejFailTimes()
                    + NAS_EMM_GetMoSerRelFailTimes()
                    + NAS_EMM_GetMoSerDataReqFailTimes()
                    + NAS_EMM_GetMoSerOtherFailTimes();

     /* ��Attach��������Ƿ�ȵ�ǰAttach�ɹ���ʧ�ܴ����ܺͣ�˵����ǰ��Attach Other Fail */
     if(NAS_EMM_GetMoSerTolalTimes() > usMoSerTimes)
     {
        NAS_EMM_GetMoSerOtherFailTimes() += (NAS_EMM_GetMoSerTolalTimes() - usMoSerTimes);
        ulRslt = NAS_EMM_YES;
     }
    return ulRslt;
}
/*****************************************************************************
 Function Name   : NAS_LMM_AddSerCounter
 Description     : ����Ser�����ݱ��ش洢����
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_ENUM_UINT16   enCounterType)
{
    VOS_UINT32                              ulRslt = NAS_EMM_NO;
    VOS_UINT32                              ulIndex = 0;
    NAS_LMM_ADD_SER_COUNTER_TYPE_PROC_FUN   pfAddSerCounterProcFun = VOS_NULL_PTR;
    if(VOS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
    {
        return;
    }
    for(ulIndex = 0; ulIndex < g_stEmmAddSerCounterProcTblLen; ulIndex++)
    {
        if(enCounterType == g_stEmmAddSerCounterProcTbl[ulIndex].enCounterType)
        {
            pfAddSerCounterProcFun = g_stEmmAddSerCounterProcTbl[ulIndex].pfAddSerCounterProcFun;
            break;
        }
    }
    if(VOS_NULL_PTR != pfAddSerCounterProcFun)
    {
        ulRslt = (pfAddSerCounterProcFun)();
    }
    if((NAS_EMM_YES == NAS_EMM_GetOmSwitchSuccRatioFlag())
        &&(NAS_EMM_YES == ulRslt)
        &&(NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL != enCounterType))
    {
        NAS_LMM_SndOmSerSuccRatioInfo();
    }
}
/*****************************************************************************
 Function Name   : NAS_LMM_UpdateSerEstFailCounter
 Description     : ����EST FAIL ԭ��ֵ���м���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_UpdateSerEstFailCounter(LRRC_LNAS_EST_RESULT_ENUM_UINT32   enEstResult)
{
    if((LRRC_EST_ACCESS_BARRED_MO_CALL == enEstResult)
        ||(LRRC_EST_ACCESS_BARRED_ALL == enEstResult)
        ||(LRRC_EST_ACCESS_BARRED_ALL == enEstResult)
        ||(LRRC_EST_ACCESS_BARRED_MT_CALL == enEstResult)
        ||(LRRC_EST_ACCESS_BARRED_MO_CALL_AND_CSFB == enEstResult))
     {
        NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_BAR);
     }
     else
     {
        NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_EST_FAIL);
     }
}
/*****************************************************************************
 Function Name   : NAS_LMM_UpdateSerOtherFailCounter
 Description     : ���ݵ�ǰ����״̬����Ser OTHER FAIL��������������״̬ת��ʱ����
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_UpdateSerOtherFailCounter(VOS_VOID)
{
    if((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        ||(NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
        ||(NAS_EMM_CONN_IDLE == NAS_EMM_GetConnState()))
     {
        NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_OTHERS_FAIL);
     }
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveMtSerStartTimeStamp
 Description     : ��¼Mt Ser��������ʱ���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMtSerStartTimeStamp(VOS_VOID)
{
    NAS_LMM_OM_MT_SERVICE_DELAY_INFO_STRU *pstSerDelayInfo;
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    pstSerDelayInfo = NAS_EMM_GetOmMtSerDelayInfoAddr();
    NAS_LMM_MEM_SET_S(  pstSerDelayInfo,
                        sizeof(NAS_LMM_OM_MT_SERVICE_DELAY_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_MT_SERVICE_DELAY_INFO_STRU));
    NAS_EMM_GetOmMtSerStartTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMtSerReqSndTimeStamp
 Description     : ��¼Mt Ser Req Sndʱ���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMtSerReqSndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMtSerReqSndTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMtSerEstSuccTimeStamp
 Description     : ��¼Mt Ser Est Succʱ���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMtSerEstSuccTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMtSerEstSuccTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMtSerEndTimeStamp
 Description     : ��¼Mt Ser���̽���ʱ���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMtSerEndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMtSerEndTime() = stCurrTime.ul32KTStampLowBit;
    /* ��ʱ����Ϣ�ϱ����ش����ϱ� */
    if(NAS_EMM_YES == NAS_EMM_GetOmSwitchDelayFlag())
    {
        NAS_LMM_SndOmServiceDelayInfo(NAS_EMM_YES);
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMoSerStartTimeStamp
 Description     : ��¼Mo Ser��������ʱ���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMoSerStartTimeStamp(VOS_VOID)
{
    NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU *pstSerDelayInfo;
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    pstSerDelayInfo = NAS_EMM_GetOmMoSerDelayInfoAddr();
    NAS_LMM_MEM_SET_S(  pstSerDelayInfo,
                        sizeof(NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU));
    NAS_EMM_GetOmMoSerStartTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMoSerReqSndTimeStamp
 Description     : ��¼Mo Ser Req Sndʱ���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMoSerReqSndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMoSerReqSndTime() = stCurrTime.ul32KTStampLowBit;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveMoSerEstSuccTimeStamp
 Description     : ��¼Mo Ser Est Succʱ���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMoSerEstSuccTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMoSerEstSuccTime() = stCurrTime.ul32KTStampLowBit;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveMoSerEndTimeStamp
 Description     : ��¼Mo Ser�������ʱ���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveMoSerEndTimeStamp(VOS_VOID)
{
    LPS_32K_TIMESTAMP                      stCurrTime;
    NAS_LMM_MEM_SET_S(&stCurrTime, sizeof(LPS_32K_TIMESTAMP), 0, sizeof(LPS_32K_TIMESTAMP));
    /* ��ȡ��ǰʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&stCurrTime.ul32KTStampHighBit, &stCurrTime.ul32KTStampLowBit);

    NAS_EMM_GetOmMoSerEndTime() = stCurrTime.ul32KTStampLowBit;
    /* ��ʱ����Ϣ�ϱ����ش����ϱ� */
    if(NAS_EMM_YES == NAS_EMM_GetOmSwitchDelayFlag())
    {
        NAS_LMM_SndOmServiceDelayInfo(NAS_EMM_NO);
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveSerReqSndTimeStamp
 Description     : ��¼Ser Req Sndʱ���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveSerReqSndTimeStamp()
{
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        if((NAS_EMM_SER_START_CAUSE_RABM_REEST == NAS_EMM_SER_GetEmmSERStartCause())
            ||(NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC == NAS_EMM_SER_GetEmmSERStartCause()))
        {
            NAS_EMM_SaveMoSerReqSndTimeStamp();
        }
        else if(NAS_EMM_SER_START_CAUSE_RRC_PAGING == NAS_EMM_SER_GetEmmSERStartCause())
        {
            NAS_EMM_SaveMtSerReqSndTimeStamp();
        }
        else
        {
        }
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveSerEstSuccTimeStamp
 Description     : ��¼Ser EST SUCCʱ���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveSerEstSuccTimeStamp(VOS_VOID)
{
    if((NAS_EMM_SER_START_CAUSE_RABM_REEST == NAS_EMM_SER_GetEmmSERStartCause())
        ||(NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC == NAS_EMM_SER_GetEmmSERStartCause()))
    {
        NAS_EMM_SaveMoSerEstSuccTimeStamp();
    }
    else if(NAS_EMM_SER_START_CAUSE_RRC_PAGING == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_SaveMtSerEstSuccTimeStamp();
    }
    else
    {
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveSerEndTimeStamp
 Description     : ��¼Ser���̽���ʱ���
 Input           :
 Output          : None
 Return          : NONE

 History         :
    1.leixiantiao 00258641      2015-5-22  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveSerEndTimeStamp(VOS_VOID)
{
    if((NAS_EMM_SER_START_CAUSE_RABM_REEST == NAS_EMM_SER_GetEmmSERStartCause())
        ||(NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC == NAS_EMM_SER_GetEmmSERStartCause()))
    {
        NAS_EMM_SaveMoSerEndTimeStamp();
    }
    else if(NAS_EMM_SER_START_CAUSE_RRC_PAGING == NAS_EMM_SER_GetEmmSERStartCause())
    {
        NAS_EMM_SaveMtSerEndTimeStamp();
    }
    else
    {
    }
}

/*****************************************************************************
 Function Name   : NAS_LMM_CalcDelayLen
 Description     : ������ʱ����ʱ�Ӻ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LMM_CalcDelayLen(VOS_UINT32 ulTimeStampBegin, VOS_UINT32 ulTimeStampEnd)
{
    VOS_UINT32 ulLen;
    if(ulTimeStampEnd > ulTimeStampBegin)
    {
        ulLen = ulTimeStampEnd - ulTimeStampBegin;
    }
    else
    {
        /* ���ַ�ת����� */
        ulLen = (NAS_EMM_UINT32_MAX - ulTimeStampBegin) + ulTimeStampEnd;
    }
    return ulLen;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmAttSuccRatioInfo
 Description     : ������attach�ɹ����ϱ�
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmAttSuccRatioInfo(VOS_VOID)
{
    NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU),
                        0,
                        sizeof(NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU));
    pstMsg->stTlKpiHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulSenderPid     = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulReceiverPid   = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulLength        = sizeof(NAS_LMM_OM_ATTACH_SUCC_RATIO_INFO_MSG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstMsg->stTlKpiHdr.enType          = TL_KPI_TYPE_EST;
    pstMsg->stTlKpiHdr.ulMsgName       = ID_NAS_EMM_OM_ATTACH_SUCC_RATIO_INFO;

    NAS_LMM_MEM_CPY_S(  &pstMsg->stNasLmmOmAttSuccRatioInfo,
                        sizeof(NAS_LMM_OM_SUCC_RATIO_ATTTACH_STRU),
                        NAS_EMM_GetOmSuccRationAttInfoAddr(),
                        sizeof(NAS_LMM_OM_SUCC_RATIO_ATTTACH_STRU));

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmTauSuccRatioInfo
 Description     : ������tau�ɹ����ϱ�
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmTauSuccRatioInfo(VOS_VOID)
{
    NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU),
                        0,
                        sizeof(NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU));
    pstMsg->stTlKpiHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulSenderPid     = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulReceiverPid   = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulLength        = sizeof(NAS_LMM_OM_TAU_SUCC_RATIO_INFO_MSG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstMsg->stTlKpiHdr.enType          = TL_KPI_TYPE_EST;
    pstMsg->stTlKpiHdr.ulMsgName       = ID_NAS_EMM_OM_TAU_SUCC_RATIO_INFO;

    NAS_LMM_MEM_CPY_S(  &pstMsg->stNasLmmOmTauSuccRatioInfo,
                        sizeof(NAS_LMM_OM_SUCC_RATIO_TAU_STRU),
                        NAS_EMM_GetOmSuccRationTauInfoAddr(),
                        sizeof(NAS_LMM_OM_SUCC_RATIO_TAU_STRU));

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;

}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmSerSuccRatioInfo
 Description     : ������service�ɹ����ϱ�
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmSerSuccRatioInfo(VOS_VOID)
{
    NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU    *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU),
                        0,
                        sizeof(NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU));
    pstMsg->stTlKpiHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiHdr.ulSenderPid     = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulReceiverPid   = PS_PID_MM;
    pstMsg->stTlKpiHdr.ulLength        = sizeof(NAS_LMM_OM_SER_SUCC_RATIO_INFO_MSG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstMsg->stTlKpiHdr.enType          = TL_KPI_TYPE_EST;
    pstMsg->stTlKpiHdr.ulMsgName       = ID_NAS_EMM_OM_SERVICE_SUCC_RATIO_INFO;

    /* ��д��ʶ״̬ */
    NAS_LMM_MEM_CPY_S(  &pstMsg->stNasLmmOmSerSuccRatioInfo,
                        sizeof(NAS_LMM_OM_SUCC_RATIO_SER_STRU),
                        NAS_EMM_GetOmSuccRationSerInfoAddr(),
                        sizeof(NAS_LMM_OM_SUCC_RATIO_SER_STRU));

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmAttachDelayInfo
 Description     : ������attachʱ���ϱ�
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmAttachDelayInfo(VOS_VOID)
{
    NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                               ulTimeDelayLen;
    pstMsg = (NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU),
                        0,
                        sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU));
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulSenderPid     = PS_PID_MM;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulReceiverPid   = PS_PID_MM;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulLength        = sizeof(NAS_LMM_OM_ATTACH_DELAY_INFO_MSG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.enType          = TL_KPI_TYPE_DELAY;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulMsgName       = ID_NAS_EMM_OM_ATTACH_DELAY_INFO;

    /* ������ʱ�� */
    ulTimeDelayLen = NAS_LMM_CalcDelayLen(NAS_EMM_GetOmAttachDelayInfoStartTime(), NAS_EMM_GetOmAttachDelayInfoEndTime());

    pstMsg->stTlKpiDelayHdr.ulDelay = ulTimeDelayLen;
    pstMsg->stTlKpiDelayHdr.ulStartTime = NAS_EMM_GetOmAttachDelayInfoStartTime();
    pstMsg->stTlKpiDelayHdr.ulEnd = NAS_EMM_GetOmAttachDelayInfoEndTime();

    /* ��������ʱ����Ϣ */
    pstMsg->bitOpEstSucc        = NAS_EMM_GetOmAttachDelayInfoOpEstSucc();
    pstMsg->ulAttachReqSnd      = NAS_EMM_GetOmAttachDelayInfoReqSndTime();
    pstMsg->ulAttachAccept      = NAS_EMM_GetOmAttachDelayInfoulAcceptTime();
    pstMsg->ulEstSucc           = NAS_EMM_GetOmAttachDelayInfoEstSuccTime();
    pstMsg->ulAttachCompleteSnd = NAS_EMM_GetOmAttachDelayInfoCmpSndTime();
    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmServiceDelayInfo
 Description     : ������serviceʱ���ϱ�
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641      2015-06-3  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmServiceDelayInfo(VOS_UINT32 ulIsMtService)
{
    NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU    *pstMsg = VOS_NULL_PTR;
    NAS_LMM_OM_MO_SERVICE_DELAY_INFO_STRU     *pstNasServiceDelayInfo = VOS_NULL_PTR;
    VOS_UINT32                                 ulTimeDelayLen = 0;
    pstMsg = (NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU));
    if(VOS_NULL_PTR == pstMsg)
    {
        return;
    }
    NAS_LMM_MEM_SET_S(  pstMsg,
                        sizeof(NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU),
                        0,
                        sizeof(NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU));
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulSenderPid     = PS_PID_MM;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulReceiverPid   = PS_PID_MM;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulLength        = sizeof(NAS_LMM_OM_SERVICE_DELAY_INFO_MSG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.enType          = TL_KPI_TYPE_DELAY;
    pstMsg->stTlKpiDelayHdr.stKpiHdr.ulMsgName       = ID_NAS_EMM_OM_SERVICE_DELAY_INFO;
    pstMsg->ulIsMtServiceFlag                        = ulIsMtService;
    /* �ж����Ƿ���Mt Ser */
    if(NAS_EMM_YES == ulIsMtService)
    {
        pstNasServiceDelayInfo = NAS_EMM_GetOmMtSerDelayInfoAddr();
    }
    else
    {
        pstNasServiceDelayInfo = NAS_EMM_GetOmMoSerDelayInfoAddr();
    }
    /* ������ʱ�� */
    ulTimeDelayLen = NAS_LMM_CalcDelayLen(pstNasServiceDelayInfo->ulStart, pstNasServiceDelayInfo->ulEnd);

    pstMsg->stTlKpiDelayHdr.ulDelay = ulTimeDelayLen;
    pstMsg->stTlKpiDelayHdr.ulStartTime = pstNasServiceDelayInfo->ulStart;
    pstMsg->stTlKpiDelayHdr.ulEnd = pstNasServiceDelayInfo->ulEnd;

    pstMsg->ulServiceReqSnd = pstNasServiceDelayInfo->ulServiceReqSnd;
    pstMsg->ulEstSucc       = pstNasServiceDelayInfo->ulEstSucc;
    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmTauStartTypeInfo
 Description     : �ϱ�TAU����ԭ��
 Input           : enTauStartType: TAU����ԭ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    leixiantiao 00258641   2015-07-25  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LMM_SndOmTauStartTypeInfo(NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 enTauStartType)
{
    NAS_LMM_OM_LOG_TAU_START_TYPE_INFO_STRU stTauStartTypeInfo;

    NAS_LMM_MEM_SET_S(  &stTauStartTypeInfo,
                        sizeof(NAS_LMM_OM_LOG_TAU_START_TYPE_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_TAU_START_TYPE_INFO_STRU));
    stTauStartTypeInfo.stMsgHeader.ulSenderCpuId         = VOS_LOCAL_CPUID;
    stTauStartTypeInfo.stMsgHeader.ulSenderPid           = PS_PID_MM;
    stTauStartTypeInfo.stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    stTauStartTypeInfo.stMsgHeader.ulReceiverPid         = PS_PID_MM;
    stTauStartTypeInfo.stMsgHeader.ulLength              = sizeof(NAS_LMM_OM_LOG_TAU_START_TYPE_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    stTauStartTypeInfo.stMsgHeader.ulMsgName             = ID_NAS_LMM_OM_LOG_TAU_START_TYPE_INFO;

    stTauStartTypeInfo.enTauStartType                    = enTauStartType;
    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)&stTauStartTypeInfo);
}


#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 Function Name   :LNAS_InitErrLogGloInfo
 Description     : ��ʼ��Errlogȫ����Ϣ
 Input           :
 Output          : None
 Return          :

 History         :
    1.lifuxin  00253982    2014-12-27  Draft Enact
*****************************************************************************/
/*lint -e593*/
VOS_VOID  LNAS_InitErrLogGloInfo(LNAS_ERRLOG_GLO_INFO_STRU *pstErrlogGloInfo)
{
    VOS_CHAR                               *pbuffer;
    OM_RING_ID                              pRingbuffer;

    pstErrlogGloInfo->stCtrlInfo.ucErrLogCtrlFlag         = VOS_FALSE;
    pstErrlogGloInfo->stCtrlInfo.usAlmLevel               = LNAS_ERR_LOG_CTRL_LEVEL_CRITICAL;

    /* ����cache�Ķ�̬�ڴ� , ���ȼ�1����Ϊ����дָ��֮����д��ʱ�����һ���ֽ� */
    pbuffer = (char *)NAS_LMM_MEM_ALLOC(LNAS_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pbuffer)
    {
         pstErrlogGloInfo->stBuffInfo.pstRingBuffer = VOS_NULL_PTR;
         return;
    }

    /* ����OM�Ľӿڣ�������Ķ�̬�ڴ洴��ΪRING BUFFER */
    pRingbuffer = OM_RingBufferCreateEx(pbuffer, LNAS_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pRingbuffer)
    {
        NAS_LMM_MEM_FREE(pbuffer);
    }

    /* ����ringbufferָ�� */
    pstErrlogGloInfo->stBuffInfo.pstRingBuffer = pRingbuffer;

    pstErrlogGloInfo->stBuffInfo.ulOverflowCnt = 0;

    NAS_LMM_RevNvCtrl();

    return;
}
/*lint +e593*/
#endif
/*****************************************************************************
 Function Name   : NAS_EMM_SaveRecvMsgList
 Description     : ��¼LMM�յ�����Ϣ����,���50��
 Input           : pMsg:��Ϣ
 Output          : None
 Return          : None

 History         :
    1.leixiantiao  00258641    2015-07-17  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SaveRecvMsgList(VOS_VOID *pMsg)
{
    PS_MSG_HEADER_STRU         *pMsgHeader    = (PS_MSG_HEADER_STRU *)pMsg;
    LNAS_EXC_MSG_MNTN_STRU     *pstMsgMntn    = VOS_NULL_PTR;
    LNAS_EXC_MSG_ELEMENT_STRU  *pstMsgElement = VOS_NULL_PTR;
    pstMsgMntn = &g_stLNasResetInfo.stLNasMsgList;
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }
    /* ѭ��������Ϣ��ָ��ȫ�ֱ��� */
    if(pstMsgMntn->ulNextIndex >= LNAS_EXC_MAX_SAVE_MSG_NUM)
    {
        pstMsgMntn->ulNextIndex = 0;
    }
    pstMsgElement = &(pstMsgMntn ->astMsgList[pstMsgMntn->ulNextIndex]);
    /* ����ʱ����Լ���ϢID����Ϣ */
    pstMsgElement->ulTimeStamp      = VOS_GetSlice();
    pstMsgElement->ulCompPid        = TLPS_EXC_BUILD_MSG_PID(pMsgHeader->ulSenderPid,
                                                                pMsgHeader->ulReceiverPid);
    pstMsgElement->ulMsgId          = pMsgHeader->ulMsgName;
    pstMsgElement->enCurrMainState  = NAS_LMM_GetEmmCurFsmMS();
    pstMsgElement->enCurrSubState   = NAS_LMM_GetEmmCurFsmSS();

    /*Ŀǰ��ʱ��������Ϣ���ౣ��4���ֽ�,��4���ֽڻ�����OPid������̬������ģʽ�ķ��� */
    pstMsgElement->ulPrivate = *((VOS_UINT32*)pMsg + TLPS_EXC_MSG_PRIVATE_OFFSET);

    /* �ȱ����������1,����Indexǰһ����¼�Ǹ�λǰ���һ����¼ */
    pstMsgMntn->ulNextIndex++;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SaveEmmPreState
 Description     : ��¼LMM ת״̬֮ǰ״̬,���ڸ�λʱȷ��LMM�Ǵ��ĸ�״̬��ת����
                   ǰ״̬
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.leixiantiao  00258641    2015-07-17  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SavePreEmmState(VOS_VOID)
{
    LNAS_EXC_PRE_STATE_STRU             *pstLNasPreState = VOS_NULL_PTR;
    pstLNasPreState = &g_stLNasResetInfo.stLNasPreState;

    pstLNasPreState->enPreMainState = NAS_LMM_GetEmmCurFsmMS();
    pstLNasPreState->enPreSubState  = NAS_LMM_GetEmmCurFsmSS();
    pstLNasPreState->ulTimeStamp    = VOS_GetSlice();
}
/*****************************************************************************
 Function Name  : NAS_EMM_ExportMsgInfoExcLog
 Discription    : ��NAS��Ϣ���е���λ�ļ���
 Input          : pulExcLogAddr:Ŀ���ַ
 Output         : pulLeftSize  :TLPS��ά�ɲ��ڴ�ʣ�೤��
 Return         : VOS_UINT32   :�洢LMM��Ϣ����ʹ�õĳ���

 History:
      1.leixiantiao  00258641    2015-07-17  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_ExportMsgInfoExcLog(VOS_UINT8* pulExcLogAddr, VOS_UINT32 *pulLeftSize)
{
    VOS_UINT32                  ulLoop        = 0;
    VOS_UINT8                   *pulSaveAddr   = pulExcLogAddr;
    VOS_UINT32                  ulSaveSize    = 0;
    VOS_UINT32                  ulMsgStruSize = sizeof(LNAS_EXC_MSG_ELEMENT_STRU);
    VOS_UINT32                  ulMsgNum      = 0;
    LNAS_EXC_MSG_MNTN_STRU     *pstMsgMntn    = VOS_NULL_PTR;

    pstMsgMntn = &g_stLNasResetInfo.stLNasMsgList;

    /* ��ȡ��λǰ���һ����Ϣ���� */
    if(0 == pstMsgMntn->ulNextIndex)
    {
        ulLoop = LNAS_EXC_MAX_SAVE_MSG_NUM - 1;
    }
    else
    {
        ulLoop = pstMsgMntn->ulNextIndex - 1;
    }

    /* ѭ�����浽rdr�ڴ��� */
    for( ; ulMsgNum < LNAS_EXC_MAX_SAVE_MSG_NUM; ulMsgNum++ )
    {
        /* ���ָ�TLPS�ĸ�λ��ά�ɲ�ʣ���ڴ�С��һ����Ϣ�����ڴ�ʱ�˳� */
        if(*pulLeftSize < ulMsgStruSize)
        {
            return ulSaveSize;
        }

        /* �������� */
        *pulLeftSize -= ulMsgStruSize;
        ulSaveSize += ulMsgStruSize;

        NAS_LMM_MEM_CPY_S(  pulSaveAddr,
                            ulMsgStruSize,
                            &(pstMsgMntn->astMsgList[ulLoop]),
                            ulMsgStruSize);

        pulSaveAddr += ulMsgStruSize;

        /* ����ѭ�� */
        if(0 == ulLoop)
        {
            ulLoop = LNAS_EXC_MAX_SAVE_MSG_NUM;
        }
        ulLoop--;
    }
    return ulSaveSize;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmSerStartTypeInfo
 Description     : �ϱ�SERVICE����ԭ��
 Input           : NAS_LMM_OM_SER_START_TYPE_ENUM_UINT32 enSerStartType
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    yanglei 00307272      2015-08-13  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_ENUM_UINT32 enSerStartType)
{
    NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU                 *pstSerStartTypeInfo;
    pstSerStartTypeInfo = (NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU));
    if (VOS_NULL_PTR == pstSerStartTypeInfo)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstSerStartTypeInfo,
                        sizeof(NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU));
    pstSerStartTypeInfo->stMsgHeader.ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstSerStartTypeInfo->stMsgHeader.ulSenderPid            = PS_PID_MM;
    pstSerStartTypeInfo->stMsgHeader.ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstSerStartTypeInfo->stMsgHeader.ulReceiverPid          = PS_PID_MM;
    pstSerStartTypeInfo->stMsgHeader.ulLength               = sizeof(NAS_LMM_OM_LOG_SER_START_TYPE_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstSerStartTypeInfo->stMsgHeader.ulMsgName              = ID_NAS_LMM_OM_LOG_SER_START_TYPE_INFO;
    pstSerStartTypeInfo->enSerStartType                     = enSerStartType;


    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstSerStartTypeInfo);
    NAS_LMM_MEM_FREE(pstSerStartTypeInfo);
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmAnyCellJudgingInfo
 Description     : ��ʶ��ΪANY CELLС��ʱ�ϱ�
 Input           : NAS_MML_SIM_TYPE_ENUM_UINT8         enSimType,
                   MMC_LMM_PLMN_CTRL_ENUM_UINT32       ulPlmnCtrl,
                   NAS_MM_TA_STRU                     *pstTa
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    yanglei 00307272      2015-08-13  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmAnyCellJudgingInfo
(
    NAS_MML_SIM_TYPE_ENUM_UINT8         enSimType,
    MMC_LMM_PLMN_CTRL_ENUM_UINT32       ulPlmnCtrl,
    const   NAS_MM_TA_STRU             *pstTa
)
{
    NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU               *pstAnyCellJudgingInfo = VOS_NULL_PTR;
    NAS_MM_TA_LIST_STRU                                     *pstForbTaListForRoaming = VOS_NULL_PTR;
    NAS_MM_TA_LIST_STRU                                     *pstForbTaListForRpos = VOS_NULL_PTR;

    pstForbTaListForRoaming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);
    pstForbTaListForRpos = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS);

    pstAnyCellJudgingInfo = (NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU));
    if (VOS_NULL_PTR == pstAnyCellJudgingInfo)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstAnyCellJudgingInfo,
                        sizeof(NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU));
    pstAnyCellJudgingInfo->stMsgHeader.ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstAnyCellJudgingInfo->stMsgHeader.ulSenderPid          = PS_PID_MM;
    pstAnyCellJudgingInfo->stMsgHeader.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstAnyCellJudgingInfo->stMsgHeader.ulReceiverPid        = PS_PID_MM;
    pstAnyCellJudgingInfo->stMsgHeader.ulLength             = sizeof(NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstAnyCellJudgingInfo->stMsgHeader.ulMsgName            = ID_NAS_LMM_OM_LOG_ANY_CELL_JUDGING_INFO;
    pstAnyCellJudgingInfo->ulSimStat                        = NAS_LMM_GetSimState();
    pstAnyCellJudgingInfo->enPsSimValidity                  = NAS_LMM_GetPsSimValidity();
    pstAnyCellJudgingInfo->enSimType                        = enSimType;
    pstAnyCellJudgingInfo->enPlmnForb                       = ulPlmnCtrl;
    NAS_LMM_MEM_CPY_S(  &pstAnyCellJudgingInfo->stForbTaForRoam,
                        sizeof(NAS_MM_FORB_TA_LIST_STRU),
                        pstForbTaListForRoaming,
                        sizeof(NAS_MM_FORB_TA_LIST_STRU));
    NAS_LMM_MEM_CPY_S(  &pstAnyCellJudgingInfo->stForbTaForRpos,
                        sizeof(NAS_MM_FORB_TA_LIST_STRU),
                        pstForbTaListForRpos,
                        sizeof(NAS_MM_FORB_TA_LIST_STRU));
    NAS_LMM_MEM_CPY_S(  &pstAnyCellJudgingInfo->stTa,
                        sizeof(NAS_MM_TA_STRU),
                        pstTa,
                        sizeof(NAS_MM_TA_STRU));

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstAnyCellJudgingInfo);
    NAS_LMM_MEM_FREE(pstAnyCellJudgingInfo);
    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_GetImsiInfo
 Description     : ��ȡimsi info
 Input           :
 Output          : NAS_OM_IMSI_INFO_STRU *stImsiInfo
 Return          : VOS_UINT32

 History         :
    1.yanglei 00307272        2015-08-18    Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_GetImsiInfo(NAS_OM_IMSI_INFO_STRU *pstImsiInfo)
{
    VOS_UINT8                           i;
    NAS_LMM_UEID_STRU                  *pstMmUeId;

    pstMmUeId                           = NAS_LMM_GetEmmInfoUeidAddr();
    NAS_LMM_MEM_SET_S(  pstImsiInfo,
                        sizeof(NAS_OM_IMSI_INFO_STRU),
                        0,
                        sizeof(NAS_OM_IMSI_INFO_STRU));

    /*�����ǰ�޿�,��OM�ظ���ѯIMSIΪ��*/
    if (NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
    {
        /* ��ȡIMSI */
        /* usim������PS:I CANT STAND IT ANYMORE */
        if((pstMmUeId->aucImsi[0] > NAS_LMM_NVIM_IMSI_FILE_LEN - 1)
            ||(pstMmUeId->aucImsi[0] == 0))
        {
            pstImsiInfo->ucImsiLen = 0x0F;
            if (0xF0 == (pstMmUeId->aucImsi[8] & 0xF0))
            {
                pstImsiInfo->ucImsiLen -= 1;
            }
        }
        else
        {
            pstImsiInfo->ucImsiLen = (VOS_UINT8)((pstMmUeId->aucImsi[0])*2 - 1);

            /*���һ���ֽ����4λΪF,�����IMSIΪż���� */
            if (0xF0 == (pstMmUeId->aucImsi[pstMmUeId->aucImsi[0]] & 0xF0))
            {
                pstImsiInfo->ucImsiLen -= 1;
            }

        }
        for(i = 0; i < pstImsiInfo->ucImsiLen; i++)
        {
            if (0 == (i+1)%2)
            {
                pstImsiInfo->ucImsi[i] = 0x0F & (pstMmUeId->aucImsi[(i+1)/2 + 1]);
            }
            else
            {
                pstImsiInfo->ucImsi[i] = 0x0F & (pstMmUeId->aucImsi[(i+1)/2 + 1] >> 4);
            }
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmStaticUeIdInfo
 Description     : �ϱ���̬UE ID��Ϣ
 Input           :
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    yanglei 00307272      2015-08-18  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmStaticUeIdInfo(VOS_VOID)
{
    NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU                   *pstStaticUeIdInfo = VOS_NULL_PTR;
    VOS_UINT32                                              *pulImsiMncLen;
    NAS_LMM_UEID_STRU                                       *pstMmUeId;

    pstMmUeId                           = NAS_LMM_GetEmmInfoUeidAddr();
    pulImsiMncLen                       = NAS_LMM_GetEmmInfoUeidImsiMncLenAddr();
    pstStaticUeIdInfo                   = (NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU *)NAS_LMM_MEM_ALLOC \
                                                (sizeof(NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU));
    if (VOS_NULL_PTR == pstStaticUeIdInfo)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstStaticUeIdInfo,
                        sizeof(NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU));
    pstStaticUeIdInfo->stMsgHeader.ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstStaticUeIdInfo->stMsgHeader.ulSenderPid          = PS_PID_MM;
    pstStaticUeIdInfo->stMsgHeader.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstStaticUeIdInfo->stMsgHeader.ulReceiverPid        = PS_PID_MM;
    pstStaticUeIdInfo->stMsgHeader.ulLength             = sizeof(NAS_LMM_OM_LOG_STATIC_UE_ID_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstStaticUeIdInfo->stMsgHeader.ulMsgName            = ID_NAS_LMM_OM_LOG_STATIC_UE_ID_INFO;
    pstStaticUeIdInfo->stMmUeid.bitOpImei               = pstMmUeId->bitOpImei;
    pstStaticUeIdInfo->stMmUeid.bitOpImeisv             = pstMmUeId->bitOpImeisv;
    NAS_LMM_MEM_CPY_S(  pstStaticUeIdInfo->stMmUeid.aucImei,
                        NAS_MM_MAX_UEID_BUF_SIZE,
                        NAS_LMM_GetEmmInfoUeidImeiAddr(),
                        sizeof(VOS_UINT8)*NAS_MM_MAX_UEID_BUF_SIZE);
    NAS_LMM_MEM_CPY_S(  pstStaticUeIdInfo->stMmUeid.aucImeisv,
                        NAS_MM_MAX_UEID_BUF_SIZE,
                        NAS_LMM_GetEmmInfoUeidImeisvAddr(),
                        sizeof(VOS_UINT8)*NAS_MM_MAX_UEID_BUF_SIZE);
    NAS_LMM_GetImsiInfo(&pstStaticUeIdInfo->stMmUeid.stImsiInfo);
    pstStaticUeIdInfo->stMmUeid.ulImsiMncLen            = *pulImsiMncLen;

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstStaticUeIdInfo);
    NAS_LMM_MEM_FREE(pstStaticUeIdInfo);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmConnstateInfo
 Description     : �ϱ�����״̬
 Input           : NAS_EMM_RRC_CONN_STATE_ENUM_UINT8   ucConnstate
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    yanglei 00307272      2015-08-18  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmConnstateInfo(NAS_EMM_RRC_CONN_STATE_ENUM_UINT8   ucConnstate)
{
    NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU                   *pstConnStateInfo = VOS_NULL_PTR;

    pstConnStateInfo = (NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU));
    if (VOS_NULL_PTR == pstConnStateInfo)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstConnStateInfo,
                        sizeof(NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU));
    pstConnStateInfo->stMsgHeader.ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstConnStateInfo->stMsgHeader.ulSenderPid          = PS_PID_MM;
    pstConnStateInfo->stMsgHeader.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstConnStateInfo->stMsgHeader.ulReceiverPid        = PS_PID_MM;
    pstConnStateInfo->stMsgHeader.ulLength             = sizeof(NAS_LMM_OM_LOG_CONN_STATE_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstConnStateInfo->stMsgHeader.ulMsgName            = ID_NAS_LMM_OM_LOG_CONN_STATE_INFO;
    pstConnStateInfo->ucPreConnState                   = NAS_EMM_GetConnState();
    pstConnStateInfo->ucCurConnState                   = ucConnstate;

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstConnStateInfo);
    NAS_LMM_MEM_FREE(pstConnStateInfo);
    return;
}




/*****************************************************************************
 Function Name   : NAS_EMM_SndOmGradualForbParaLog
 Description     : Gradual Forb������ά�ɲ�
 Input           : stNvGradualForbPara: ��NV�ж�����������Ϣ
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SndOmGradualForbParaLog(LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU  stNvGradualForbPara)
{
    NAS_EMM_OM_GRADUAL_FORB_PARA_LOG_STRU    stOmGradualForbPara;

    /* ��Ϣ�ṹ��ʼ�� */
    NAS_LMM_MEM_SET_S(  &stOmGradualForbPara,
                        sizeof(NAS_EMM_OM_GRADUAL_FORB_PARA_LOG_STRU),
                        0,
                        sizeof(NAS_EMM_OM_GRADUAL_FORB_PARA_LOG_STRU));
    /* ��д��Ϣͷ */
    stOmGradualForbPara.stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stOmGradualForbPara.stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stOmGradualForbPara.stMsgHeader.ulSenderPid     = PS_PID_MM;
    stOmGradualForbPara.stMsgHeader.ulReceiverPid   = PS_PID_MM;
    stOmGradualForbPara.stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_GRADUAL_FORB_PARA_LOG_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    stOmGradualForbPara.stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_GRADUAL_FORB_PARA_LOG;

    /* ��ά�ɲ���Ϣ���ݸ�ֵ */
    NAS_LMM_MEM_CPY_S(  &stOmGradualForbPara.stNvGradualForbPara,
                        sizeof(LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU),
                        &stNvGradualForbPara,
                        sizeof(LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU));

    stOmGradualForbPara.ucGradualForbFlag            = g_ucLmmGradualForbFlag;
    stOmGradualForbPara.ulGradualForbTimerFirstLen   = g_ulGradualForbTimerFirstLen;
    stOmGradualForbPara.ulGradualForbTimerSecondLen  = g_ulGradualForbTimerSecondLen;
    stOmGradualForbPara.ulGradualForbTimerAgingLen   = g_ulGradualForbAgingTimerLen;

    /* ������ά�ɲ���Ϣ */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)&stOmGradualForbPara);
}
/*****************************************************************************
 Function Name   : NAS_EMM_SndOmGradualForbTaInfo
 Description     : Gradual Forb TA�Լ�TA LIST��ά�ɲ�
 Input           : stOperaTa  :����TA
                   enOperaType:��������
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-07-31  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SndOmGradualForbTaInfo(NAS_MM_TA_STRU *pstOperaTa,
                                                        NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_ENUM_UINT8 enOperaType)
{
    NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU        *pstOmGradualForbTaInfo = VOS_NULL_PTR;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST      *pstTaList             = VOS_NULL_PTR;
    VOS_UINT32                                   i;

    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();

    pstOmGradualForbTaInfo = NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU));
    if(VOS_NULL_PTR == pstOmGradualForbTaInfo)
    {
        return;
    }
    /* ��ʼ����Ϣ */
    NAS_LMM_MEM_SET_S(  pstOmGradualForbTaInfo,
                        sizeof(NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU),
                        0,
                        sizeof(NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU));

    /* �����Ϣͷ */
    pstOmGradualForbTaInfo->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstOmGradualForbTaInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstOmGradualForbTaInfo->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstOmGradualForbTaInfo->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstOmGradualForbTaInfo->stMsgHeader.ulLength        = sizeof(NAS_EMM_OM_GRADUAL_FORB_TA_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstOmGradualForbTaInfo->stMsgHeader.ulMsgName       = ID_NAS_EMM_OM_GRADUAL_FORB_TA_INFO;

    /* �����Ϣ���� */
    pstOmGradualForbTaInfo->enOperationType             = enOperaType;
    NAS_LMM_MEM_CPY_S(&pstOmGradualForbTaInfo->stOperaTa, sizeof(NAS_MM_TA_STRU), pstOperaTa, sizeof(NAS_MM_TA_STRU));
    for(i = 0; i < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; i++)
    {
        NAS_LMM_MEM_CPY_S(  &pstOmGradualForbTaInfo->stGradualForbTaList.astGradualForbTa[i],
                            sizeof(NAS_LMM_GRADUAL_FORB_TA),
                            &pstTaList->astGradualForbTa[i],
                            sizeof(NAS_LMM_GRADUAL_FORB_TA));
    }
    pstOmGradualForbTaInfo->stGradualForbTaList.ulTaNum = pstTaList->ulTaNum;

    /* ������ά�ɲ���Ϣ */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstOmGradualForbTaInfo);

    NAS_LMM_MEM_FREE(pstOmGradualForbTaInfo);
}


/*****************************************************************************
 Function Name   : NAS_LMM_SndOmRegDomainInfo
 Description     : ����ע����ʱ, �ϱ���ά�ɲ���Ϣ
 Input           : enRegDomainCur  :��ǰע����
                   enRegDomainDst  :Ŀ��ע����
 Output          : None
 Return          : None
 History         :
    1.leixiantiao 00258641      2015-08-28  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_SndOmRegDomainInfo(NAS_LMM_REG_DOMAIN_ENUM_UINT32  enRegDomainCur,
                                                        NAS_LMM_REG_DOMAIN_ENUM_UINT32   enRegDomainDst)
{
    NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU     *pstRegDomainInfo;
    NAS_EMMC_GLOBAL_STRU                    *pstEmmcInfo;

    /* ��ȡRej18PLMN�б� */
    pstEmmcInfo = NAS_EMMC_GetEmmcInfoAddr();

    pstRegDomainInfo = NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU));
    if(VOS_NULL_PTR == pstRegDomainInfo)
    {
        return;
    }
    /* ��ʼ����Ϣ */
    NAS_LMM_MEM_SET_S(  pstRegDomainInfo,
                        sizeof(NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU),
                        0,
                        sizeof(NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU));

    /* �����Ϣͷ */
    pstRegDomainInfo->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstRegDomainInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstRegDomainInfo->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstRegDomainInfo->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstRegDomainInfo->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_REG_DOMAIN_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstRegDomainInfo->stMsgHeader.ulMsgName       = ID_NAS_LMM_OM_LOG_SET_REG_DOMAIN;

    /* �����Ϣ */
    pstRegDomainInfo->enRegDomainCur       = enRegDomainCur;
    pstRegDomainInfo->enRegDomainDst       = enRegDomainDst;
    pstRegDomainInfo->ucCsRej18Cause18Flg  = (VOS_UINT8)NAS_EMMC_GetRejCause18Flag();
    pstRegDomainInfo->ucCsRejCause2Flag    = (VOS_UINT8)NAS_LMM_GetEmmInfoRejCause2Flag();

    /* �˴�ֱ�ӵ���MML�ӿ�, ��ֹ�����ظ��ϱ���ά�ɲ���Ϣ */
    pstRegDomainInfo->ucCsAttachAllowFlg = NAS_MML_GetCsAttachAllowFlg();
    pstRegDomainInfo->ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();

    NAS_LMM_MEM_CPY_S(  &pstRegDomainInfo->stRej18PlmnList,
                        sizeof(NAS_MM_PLMN_LIST_STRU),
                        &pstEmmcInfo->stRej18PlmnList,
                        sizeof(NAS_MM_PLMN_LIST_STRU));

    /* ������ά�ɲ���Ϣ */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstRegDomainInfo);

    /* �ͷ��ڴ� */
    NAS_LMM_MEM_FREE(pstRegDomainInfo);
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmImsiRefreshStatus
 Description     : �ϱ�imsiˢ��״̬
 Input           : VOS_UINT8   ucImsiRefreshStatusFlag
 Output          : None
 Return          : VOS_VOID

 History         :
    1.    yanglei 00307272      2015-11-18  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmImsiRefreshStatus(VOS_UINT8   ucImsiRefreshStatusFlag)
{
    NAS_EMM_IMSI_REFRESH_STATUS_STRU                   *pstImsiRefreshStatusInfo = VOS_NULL_PTR;

    pstImsiRefreshStatusInfo = (NAS_EMM_IMSI_REFRESH_STATUS_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_IMSI_REFRESH_STATUS_STRU));
    if (VOS_NULL_PTR == pstImsiRefreshStatusInfo)
    {
        return;
    }

    NAS_LMM_MEM_SET_S(  pstImsiRefreshStatusInfo,
                        sizeof(NAS_EMM_IMSI_REFRESH_STATUS_STRU),
                        0,
                        sizeof(NAS_EMM_IMSI_REFRESH_STATUS_STRU));

    pstImsiRefreshStatusInfo->stMsgHeader.ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstImsiRefreshStatusInfo->stMsgHeader.ulSenderPid          = PS_PID_MM;
    pstImsiRefreshStatusInfo->stMsgHeader.ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstImsiRefreshStatusInfo->stMsgHeader.ulReceiverPid        = PS_PID_MM;
    pstImsiRefreshStatusInfo->stMsgHeader.ulLength             = sizeof(NAS_EMM_IMSI_REFRESH_STATUS_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;
    pstImsiRefreshStatusInfo->stMsgHeader.ulMsgName            = LNAS_OM_LOG_IMSI_REFRESH_STATUS_IND;
    pstImsiRefreshStatusInfo->ucImsiRefreshStatusFlag          = ucImsiRefreshStatusFlag;

    /* ���巢�ͣ�PC�����׮�޲������ᷢ����Ϣ������Ӱ��PC ST */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstImsiRefreshStatusInfo);
    NAS_LMM_MEM_FREE(pstImsiRefreshStatusInfo);
    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of ��ϵͳ+ģ��+�ļ���.c */
