

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "CnasHsmFsmMain.h"
#include "CnasHsmCtx.h"
#include "CnasHsmSndInternalMsg.h"
#include "CnasHsmFsmTbl.h"
#include "CnasHsmSndTtf.h"
#include "CnasHsmComFunc.h"
#include "CnasHsmTimer.h"
#include "CnasHsmSndHsd.h"
#include "CnasHsmSndAs.h"
#include "CnasHsmDecode.h"
#include "CnasHsmEncode.h"
#include "CnasHsmProcNvim.h"
#include "CnasMntn.h"
#include "CnasHsmMntn.h"
#include "CnasTimerMgmt.h"
#include "CnasHsmFsmUatiRequest.h"
#include "CnasHsmSndHlu.h"
#include "hsm_hsd_pif.h"
#include "CnasHsmFsmSwitchOn.h"
#include "CnasHsmProcUsim.h"
#include "CnasHsmSndAps.h"
#include "hsm_aps_pif.h"
#include "ehsm_hsm_pif.h"
#include "CnasHsmSndRrm.h"
#include "CnasHsmSndEhsm.h"
#include "CnasCcb.h"
#include "CnasHsmKeepAlive.h"
#include "cttf_hrpd_fsps_ctrl_callback_pif.h"
#include "CnasHsmFsmSessionAct.h"

#include  "NasOmInterface.h"
#include "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 The Define Of The Gloabal Variable
*****************************************************************************/
/*****************************************************************************
 Variable Name       : g_astHsmSessionDeactReasonProcTbl
 Description         : Session deactive reason process table
                       �����ABORTԭ��ֵ������deactive����֮�����������Դ���
                       �ڻ��洦����֮����ݲ�ͬ���������Դ���
 1.DATE              : 2015-05-29
   AUTHOR            : y00174758
   Modification      : Create
*****************************************************************************/
CNAS_HSM_SESSION_DEACT_REASON_PROC_TBL_STRU g_astHsmSessionDeactReasonProcTbl[] =
{
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_NEG_FAIL,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpNegFail,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_AN_EXP,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpAnExp,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_FAIL,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpConnOpenFail,
    },

    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_EXPLICITLY_REJ,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpConnOpenDenyExplicitlyRej,
    },

    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpConnOpenDenyImplicitlyRej,
    },

    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_PERS_INVALID,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpPersInvalid,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_CFG_RSP_EXP,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpCfgRspExp,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_CFG_MSG_FAIL,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpCfgMsgFail,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_AN_GAUP_FAIL,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpAnGaupFail,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_IRAT_TO_LTE,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpIratToLte,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SCP_NO_RF,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpNoRf,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_NEG_FAIL,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_AN_EXP,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CONN_OPEN_FAIL,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_CONN_OPEN_DENY,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_PERS_INVALID,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CFG_RSP_EXP,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_CFG_MSG_FAIL,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_AN_GAUP_FAIL,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_IRAT_TO_LTE,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpNoRf,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_CAS_NEG_RSLT_IND_SCP_NO_RF,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonScpNoRf,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_NETWORK_LOST_IN_SESSION_ACT,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonNetworkLostInSessionAct,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_WAIT_SCP_CNF_EXP,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonWaitScpCnfExp,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_AMP_FAIL_UATI_REACH_MAX_CNT,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAmpFailUatiReachMaxCnt,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_AMP_FAIL_SYS_ACQ_SUBNET_CHANGE,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAmpFailSysAcqSubnetChange,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_AMP_FAIL_OTHER_SCENE,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAmpFailOtherScene,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_EHRPD_TO_HRPD,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonEhrpdToHrpd,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_HRPD_TO_EHRPD,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonHrpdToEhrpd,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_AN_CLOSE_SESSION_IN_VACANT,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_INTERNAL_SESSION_CLOSE_IN_CONN_MNMT,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_KEEP_ALIVE_EXP_OPEN,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonKeepAliveExpOpen,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_INTERNAL_SESSION_CLOSE_SLAVE,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonInternalSessionCloseSalve,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_AN_CLOSE_SESSION,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonSessionActAbortByAnCloseSession,
    },
    {   CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_OHM,
        {0, 0, 0},
        CNAS_HSM_ProcSessionRetryDeactReasonSessionActAbortByOhm,
    },
};


CNAS_HSM_UATI_FAIL_REASON_MAP_SESSION_DEACTVE_REASON_STRU g_astHsmUatiFailReasonMapSessionDeactReasonTbl[] =
{
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_REACH_MAX_CNT,
        CNAS_HSM_SESSION_DEACT_REASON_AMP_FAIL_UATI_REACH_MAX_CNT,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SUSPEND,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SUSPEND,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_POWER_SAVE,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_POWER_SAVE,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_POWER_OFF,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_POWER_OFF,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_NETWORK_LOST,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_NETWORK_LOST,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_AN_CLOSE_SESSION,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_AN_CLOSE_SESSION,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_EHRPD_NOT_AVAILABLE,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_EHRPD_NOT_AVAILABLE,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_PA_MODE_NTF,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_PA_MODE_NTF,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_KEEP_ALIVE_EXP,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_KEEP_ALIVE_EXP,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_NEG_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_NEG_FAIL,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_AN_EXP,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_AN_EXP,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CONN_OPEN_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CONN_OPEN_FAIL,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CONN_OPEN_DENY,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CONN_OPEN_DENY,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_PERS_INVALID,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_PERS_INVALID,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CFG_RSP_EXP,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_RSP_EXP,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CFG_MSG_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_MSG_FAIL,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_CFG_AN_GAUP_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_AN_GAUP_FAIL,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_IRAT_TO_LTE,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_IRAT_TO_LTE,
        {0, 0},
    },
    {   CNAS_HSM_UATI_REQUEST_FAIL_REASON_ABORT_BY_SCP_NO_RF,
        CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_NO_RF,
        {0, 0},
    },
};


CNAS_HSM_SESSION_ACT_FAIL_REASON_MAP_SESSION_DEACT_REASON_STRU g_astHsmSessionActFailReasonMapSessionDeactReasonTbl[] =
{
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_NEG_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_NEG_FAIL,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_AN_EXP,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_AN_EXP,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CONN_OPEN_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_FAIL,
        {0, 0},
    },

    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_IMPLICITLY_REJ,
        {0, 0},
    },

    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CONN_OPEN_DENY_EXPLICITLY_REJ,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CONN_OPEN_DENY_EXPLICITLY_REJ,
        {0, 0},
    },

    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_PERS_INVALID,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_PERS_INVALID,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CFG_RSP_EXP,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CFG_RSP_EXP,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CFG_MSG_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_CFG_MSG_FAIL,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_CFG_AN_GAUP_FAIL,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_AN_GAUP_FAIL,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_IRAT_TO_LTE,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_IRAT_TO_LTE,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_SCP_NO_RF,
        CNAS_HSM_SESSION_DEACT_REASON_SCP_NO_RF,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_WAIT_SCP_CNF_EXP,
        CNAS_HSM_SESSION_DEACT_REASON_WAIT_SCP_CNF_EXP,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_POWER_OFF,
        CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_POWER_OFF,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_POWER_SAVE,
        CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_POWER_SAVE,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_SUSPEND,
        CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_SUSPEND,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_NETWORK_LOST,
        CNAS_HSM_SESSION_DEACT_REASON_NETWORK_LOST_IN_SESSION_ACT,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_AN_CLOSE_SESSION,
        CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_AN_CLOSE_SESSION,
        {0, 0},
    },
    {   CNAS_HSM_SESSION_ACT_FAIL_REASON_ABORT_BY_OHM,
        CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_OHM,
        {0, 0},
    },
};


CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8 g_astHsmSessionDeactiveReasonAbortList[] =
{
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SUSPEND,                /* UATI is aborted by ID_HSD_HSM_SUSPEND_IND */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_POWER_SAVE,             /* UATI is aborted by ID_HSD_HSM_POWER_SAVE_REQ */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_POWER_OFF,              /* UATI is aborted by ID_HSD_HSM_POWEROFF_REQ */

    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_AN_CLOSE_SESSION,       /* UATI is aborted by AN send session close */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_EHRPD_NOT_AVAILABLE,    /* UATI is aborted by ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_PA_MODE_NTF,            /* UATI is aborted by ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF */

    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_KEEP_ALIVE_EXP,         /* UATI is aborted by keep alive timer expire */

    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_NEG_FAIL,           /* UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_FAILURE */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_AN_EXP,             /* UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_AN_EXPIRED */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CONN_OPEN_FAIL,     /* UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_CONN_OPEN_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CONN_OPEN_DENY,     /* UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_CONN_OPEN_DENY */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_PERS_INVALID,       /* UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_PERSONALITY_INVALID */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_RSP_EXP,        /* UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_CFG_RSP_EXPIRED */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_MSG_FAIL,       /* UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_CFG_MSG_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_CFG_AN_GAUP_FAIL,   /* UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_AN_GAUP_FAIL */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_IRAT_TO_LTE,        /* UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_IRAT_TO_LTE */
    CNAS_HSM_SESSION_DEACT_REASON_UATI_ABORT_BY_SCP_NO_RF,              /* UATI is aborted by ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND with reason RSLT_NO_RF */

    CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_SUSPEND,             /* Session active is aborted by ID_HSD_HSM_SUSPEND_IND */
    CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_POWER_SAVE,          /* Session active is aborted by ID_HSD_HSM_POWER_SAVE_REQ */
    CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_POWER_OFF,           /* Session active is aborted by ID_HSD_HSM_POWEROFF_REQ */
    CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_AN_CLOSE_SESSION,    /* Session active is aborted by AN send session close */

    CNAS_HSM_SESSION_DEACT_REASON_SESSION_DEACT_ABORT,                      /* Session deactive is aborted */
};


/*****************************************************************************
  3 Function Define
*****************************************************************************/

VOS_UINT32 CNAS_HSM_RcvHsdStartReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StartSwitchOnProcedure_L1Main();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_ProcPowerOffReq();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsmSwitchOnResultInd_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SndHsdStartCnf();

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_INACTIVE);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_HRPD_SESSION_NEG, VOS_RATMODE_HRPD);

    CNAS_HSM_ProcPowerOffReq();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_Setup(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_ProcPowerOffReq();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

    /* ����Session�������ʱ�� */
    CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                        CNAS_HSM_GetSessionActTimerLen());

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

    CNAS_HSM_EnterSetupStateProc_L1Main();

    CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsdSystemAcqInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_HSM_SYSTEM_ACQUIRED_IND_STRU   *pstHsdSysAcqInd = VOS_NULL_PTR;

    pstHsdSysAcqInd = (HSD_HSM_SYSTEM_ACQUIRED_IND_STRU *)pstMsg;

    /* Save the CDMA Sys time and current tick */
    CNAS_HSM_SaveSysTimeAndCurSysTick(pstHsdSysAcqInd->aulSystemTime);

    if (VOS_TRUE == CNAS_HSM_GetFirstSysAcqFlag())
    {
        /* HSM will start the session recovery flow if the last session must be recovered. Otherwise, HSM will generate the
            Initial session seed and will perform the enter Inactive state procedure. */
        CNAS_HSM_ProcMsgForFirstSysAcq_L1Main();

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* proc enter inactive state */
    CNAS_HSM_EnterInactiveStateProc_L1Main();


    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ߵ��ú����ĳ���: UATI��״̬�յ�ID_EHSM_HSM_EHRPD_NOT_AVAILABLE_IND֮�󻺴棬
       Deactive���֮��������Ϣ��ʱ����ߵ��˺���
       �ó��������ڣ�����������
     */

    /* �������������ŷ���UAT���� */
    if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT != CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetLatestSessionDeactReason(CNAS_HSM_SESSION_DEACT_REASON_EHRPD_TO_HRPD);

        /* ����Session�������ʱ�� */
        CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                            CNAS_HSM_GetSessionActTimerLen());

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdIratFromLteNtf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_HSM_GetFirstSysAcqFlag())
    {
        /* HSM will start the session recovery flow if the last session must be recovered. Otherwise, HSM will generate the
        Initial session seed and will perform the enter Inactive state procedure. */
        CNAS_HSM_ProcMsgForFirstSysAcq_L1Main();

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsmHrpdPaRatModeNtf_Inactive
Description     :   process ID_CNAS_HSM_HSM_HRPD_PA_RAT_MODE_NTF msg from cache queue
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED-------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED---the current event need to further process

Modify History  :
1)  Date           : 2015-06-11
    Author         : x00314862
    Modify content : Create
2)  Date           : 2015-08-15
    Author         : y00307564
    Modify content : DTS2015081302622�޸ĺ�����
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsmHrpdPaRatModeNtf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ߵ��ú����ĳ���: UATI��״̬�յ�ID_CAS_CNAS_HRPD_PA_RAT_MODE_NTF֮�󻺴棬
       Deactive���֮��������Ϣ��ʱ����ߵ��˺���
     */

    /* �������������ŷ���UAT���� */
    if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT != CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetLatestSessionDeactReason(CNAS_HSM_SESSION_DEACT_REASON_EHRPD_TO_HRPD);

        /* ����Session�������ʱ�� */
        CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                            CNAS_HSM_GetSessionActTimerLen());

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}




VOS_UINT32 CNAS_HSM_RcvRrmStatusInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRM_PS_STATUS_IND_STRU                                 *pstRrmStatusInd = VOS_NULL_PTR;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;
    pstRrmStatusInd = (RRM_PS_STATUS_IND_STRU *)pstMsg;
    enConvertedCasStatus     = CNAS_HSM_GetHrpdConvertedCasStatus();

    if ((RRM_PS_TASK_TYPE_HRPD_SESSION_NEG  == pstRrmStatusInd->enTaskType)
     && (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT != enConvertedCasStatus))
    {
        /* ����Session�������ʱ�� */
        CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                            CNAS_HSM_GetSessionActTimerLen());

        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SndHsdPowerSaveCnf();

    CNAS_HSM_SndEhsmSuspendInd();

    /* ����session���Բ��� */
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_EnterSlaveStateProc_L1Main();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����session���Բ��� */
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_EnterSlaveStateProc_L1Main();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����session���Բ��� */
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_EnterSlaveStateProc_L1Main();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}




VOS_UINT32 CNAS_HSM_RcvHsmSessionActiveResultInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU            *pstSessionActRsltInd;

    pstSessionActRsltInd  = (CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU *)pstMsg;

    /* this will only happen in session recovery flow */
    if (CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL == pstSessionActRsltInd->enRslt)
    {
        CNAS_HSM_EnterInactiveStateProc_L1Main();
    }
    else
    {
        CNAS_HSM_ProcSessionRecoverySucc_L1Main();

        /* ��ά�ɲ���Ϣ */
        CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SESSION_OPEN, UEPS_PID_HSM);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsmSessionCloseInd_Inactive
Description     :   Inactive״̬�����ڲ���Ϣ: ID_CNAS_HSM_HSM_SESSION_CLOSE_IND
                    ����״̬�յ����緢��SessionClose��Ϣ����Ԥ������Ȼظ�SessionClose��
                    Ȼ�󻺴����Ϣ���˳���ǰ��״̬������ʼHSM deacitve���̣�deactive���֮��
                    ��inactive״̬������ڲ���Ϣ
                    �������ڲ���Ϣ�ĳ���: 1) �����·�SessionClose
                                          2) �յ�ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND��Ϣ
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED------------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED--------the current event need to further process

Modify History  :
1)  Date           : 2015-06-11
    Author         : y00307564
    Modify content : Create
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU                    *pstMsgInd;
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;

    pstMsgInd = (CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU *)pstMsg;

    /* �ߵ��˺����ĳ���: ����״̬�յ��ڲ�CLOSE_IND��Ϣ֮�󻺴棬Deactive���֮�������ʱ����ߵ��˺���
     * �����ڲ�CLOSE_IND��Ϣ�ĳ���:
     * 1) Keep Alive��ʱ����ʱ
     * 2) �յ����緢��SessionClose
     * 3) �յ�ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND
     */

    /* �������UATI��Session act�������յ����緢��SessionClose�������������� */
    if ((CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_SETUP            == pstMsgInd->enScene)
     || (CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_OPEN_SESSION_ACT == pstMsgInd->enScene))

    {
        CNAS_HSM_ProcSessionRetryAfterSessionDeact_L1Main(
                                    CNAS_HSM_SESSION_DEACT_REASON_SESSION_ACT_ABORT_BY_AN_CLOSE_SESSION);
    }
    else if (CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_RCV_CAS_NEG_RSLD_IND == pstMsgInd->enScene)
    {
        enSessionDeactReason = CNAS_HSM_ConvertScpNegRsltIndFailReasonToSessionDeactReason(
                                                         pstMsgInd->stSessionNegRsltInfo.enResult);

        CNAS_HSM_ProcSessionRetryAfterSessionDeact_L1Main(enSessionDeactReason);
    }
    /* �����������������Բ�������ʼUAT����
     * ����Ȼ���ID_CNAS_HSM_HSM_SESSION_CLOSE_IND���ٻ���Power Off��Power Save��
     * ��ʱ����״̬��Null��Slave�������ߵ��������
     */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT != CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                            CNAS_HSM_GetSessionActTimerLen());

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
    else
    {
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsmSessionDeactiveResultInd_Setup(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU          *pstRsltIndMsg;

    pstRsltIndMsg = (CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU *)pstMsg;

    CNAS_HSM_CleanReviseTimerScene_SessionDeact();

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_INACTIVE);

    CNAS_HSM_EnterInactiveStateProc_L1Main();

    /* ���Session deactiveԭ��ֵ��ABORT���ȴ����棬���洦����֮�������� */
    if (VOS_TRUE == CNAS_HSM_IsSessionDeactReasonAbort(pstRsltIndMsg->enSessionDeactReason))
    {
        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_ProcSessionRetryAfterSessionDeact_L1Main(pstRsltIndMsg->enSessionDeactReason);

    CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SESSION_CLOSE, UEPS_PID_HSM);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvUatiRequestResultInd_Setup(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU              *pstUatiResult;
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;

    pstUatiResult = (CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU*)pstMsg;

    if (CNAS_HSM_UATI_REQUEST_RESULT_SUCC == pstUatiResult->enRslt)
    {
        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_OPEN);

        /* Session active reason is: Session Negotiation */
        CNAS_HSM_StartSessionActiveProcedure_L1Main(CNAS_HSM_SESSION_ACTIVE_REASON_NEG);
    }
    else
    {
        /* Reason type in paramter change to session close reason */

        enSessionDeactReason = CNAS_HSM_ConvertUaitFailReasonToSessionDeactReason(
                                                                    pstUatiResult->enFailReason);

        CNAS_HSM_StartSessionDeactiveProcedure_L1Main(enSessionDeactReason);

        CNAS_HSM_SetSessionNegOngoingFlag(VOS_FALSE);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdSystemAcqInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_HSM_SYSTEM_ACQUIRED_IND_STRU   *pstSysAcqInd = VOS_NULL_PTR;

    pstSysAcqInd = (HSD_HSM_SYSTEM_ACQUIRED_IND_STRU *)pstMsg;

    /* Save the CDMA Sys time and current tick */
    CNAS_HSM_SaveSysTimeAndCurSysTick(pstSysAcqInd->aulSystemTime);

    /*******************************************************************************
    �����޸ı���:
    CAS�ڷ����쳣ʱ����release all����CNAS��network_lost,��ʵ��ʱ�Ķ�����������������Ķ�����ֻ�ǵײ㷢�����쳣
    �ⳡ�ܳ���trace������CASĿǰ���쳣�����Ƚ�Ƶ����HSMģ�鰴��Э���ڶ������ٴ��ѵ��������ϵͳ��Ϣ�����˱仯��
    ��HSM��ȥ����session����Э�̣�������ֱ�ӵ����û�������3G������ʾ�޷����û�����ϲ

    �Ż�����:����ײ㷢�����쳣�������ٴ��ѵ����������ʱ��ϵͳ��Ϣ�����˱仯����HSM���ڸó����Ĵ�������IDHO���ƣ�
             ��ֻ����UATI������ȥ����session��

    �ӿ�Լ��:HSD��IDLE̬������յ�CASָʾ�ĵ���ԭ��ֵΪabnormal��HSD��������Ϊabnormal(�����)����������ֻ����һ��
             �����������abnormal��ԭ��ֵ����HSM���������HSD��δ�˳�abnormal����������״̬�����ٴ��յ�CAS�ĵ���ָʾ
             ������CAS�ĵ���ָʾԭ��ֵΪabnormal����������ͳһ��HSM��normal�����������
    ********************************************************************************/
    if (HSD_HSM_SYSTEM_ACQUIRE_TYPE_NORMAL == pstSysAcqInd->enSysAcqType )
    {
        CNAS_HSM_SetRcvOhmScene(CNAS_HSM_RCV_OHM_SCENE_FOLLOW_SYS_ACQ);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvEhsmEhrpdNotAvailableInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_StartSessionDeactiveProcedure_L1Main(CNAS_HSM_SESSION_DEACT_REASON_EHRPD_TO_HRPD);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCasPaRatModeNtf_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU                     *pstPaRatModeNtf;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enNegoSessionType;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;

    enNegoSessionType = CNAS_HSM_GetNegoSessionType();

    pstPaRatModeNtf = (CAS_CNAS_HRPD_PA_RAT_MODE_NTF_STRU *)pstMsg;

    /* convert the session type */
    enSessionType = CNAS_HSM_ConvertPaModeToHsmSessionType(pstPaRatModeNtf->enPaMode);

    if (CNAS_HSM_SESSION_TYPE_BUTT == enSessionType)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCasPaRatModeNtf_Open,receive the invalid session type--BUTT");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* Last session type is eHRPD and new negotiated session type is HRPD
       need fallback
     */
    if ((CNAS_HSM_SESSION_TYPE_EHRPD == enNegoSessionType)
     && (CNAS_HSM_SESSION_TYPE_HRPD == enSessionType))
    {
        /* start eHRPD fallback process*/
        CNAS_HSM_StartSessionDeactiveProcedure_L1Main(CNAS_HSM_SESSION_DEACT_REASON_EHRPD_TO_HRPD);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* store the negotiated session type */
    CNAS_HSM_SetNegoSessionType(enSessionType);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}





VOS_UINT32 CNAS_HSM_GetNoMonitorDistance_Open(
    VOS_INT32       lLongitude,
    VOS_INT32       lLatitude
)
{
    CNAS_HSM_LOC_INFO_STRU                                 *pstLocInfo;
    VOS_UINT32                                              usNoMonitorDistance;

    usNoMonitorDistance = 0;

    pstLocInfo = CNAS_HSM_GetLocInfoAddr();
    if ((CNAS_HSM_INVALIDE_LONGITUDE == pstLocInfo->lLongitude)
     || (CNAS_HSM_INVALIDE_LATITUDE  == pstLocInfo->lLatitude))
    {
        /* update the loc info*/
        pstLocInfo->lLatitude   = lLatitude;
        pstLocInfo->lLongitude  = lLongitude;
    }
    else
    {
        /* calcuate the NoMonitorDistance */
        usNoMonitorDistance = CNAS_HSM_CalcNoMonitorDistance(pstLocInfo->lLatitude,
                                                             pstLocInfo->lLongitude,
                                                             lLatitude,
                                                             lLongitude);

        /* update the loc info */
        pstLocInfo->lLatitude   = lLatitude;
        pstLocInfo->lLongitude  = lLongitude;
    }

    return usNoMonitorDistance;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_IsNeedStartDeactProcedure
Description     :   judge whether need start deact procedure or not when AT receives an InitializationState.NetworkAcquire
                    indication followed by an OverheadMessages.Updated indication
Input parameters:   VOS_VOID
Outout parameters:  None
Return Value    :   VOS_UINT8


Modify History  :
1)  Date           : 2015-06-06
    Author         : m00312079
    Modify content : Create

2.  ��    ��   : 2015��08��24��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_UINT8 CNAS_HSM_IsNeedStartDeactProcedure(VOS_VOID)
{
    CNAS_HSM_UATI_INFO_STRU                               *pstUatiInfo;
    CNAS_HSM_HRPD_SYS_INFO_STRU                           *pstHprdSysInfo;
    VOS_UINT8                                              ucQuotient;
    VOS_UINT8                                              ucRemainder;
    VOS_UINT8                                              ucLoop;
    VOS_UINT8                                              ucLeftMask;
    VOS_UINT8                                              ucReducedSubnetMaskOffset;
    CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU                     *pstAmpNegAttr;

    pstHprdSysInfo    = CNAS_HSM_GetHrpdSysInfoAddr();
    pstUatiInfo       = CNAS_HSM_GetUatiInfoAddr();

    pstAmpNegAttr = CNAS_HSM_GetHrpdAmpNegAttribAddr();
    /* get attribute value from Hsm ctx */
    ucReducedSubnetMaskOffset = (VOS_UINT8)pstAmpNegAttr->usReducedSubnetMaskOffset;

    /* C.S0024-A_v3.0 7.3.7.1.6.1:
       one of the following conditions is true:
       1: the UATISubnetMask is not equal to the SubnetMask of the sector in the active set;
       2: the result of bitwise logical AND of the UATI and ReducedSubnetMask is different from
          the result of bitwise logical AND of SectorID and ReducedMask(where SectorID and SubnetMask
          correspond to the sector in the active set) */
    if (pstHprdSysInfo->ucSubNetMask != pstUatiInfo->ucUATISubnetMask)
    {
        return VOS_TRUE;
    }

    if (pstHprdSysInfo->ucSubNetMask < ucReducedSubnetMaskOffset)
    {
        /* abnormal case */
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_IsReducedSubnetChanged: ucReducedSubnetMaskOffset > ucSubNetMask!");
        return VOS_TRUE;
    }

    ucQuotient  = (pstHprdSysInfo->ucSubNetMask - ucReducedSubnetMaskOffset) / CNAS_HSM_BIT_LEN_PER_BYTE;
    ucRemainder = (pstHprdSysInfo->ucSubNetMask - ucReducedSubnetMaskOffset) % CNAS_HSM_BIT_LEN_PER_BYTE;

    for (ucLoop = 0; ucLoop < ucQuotient; ucLoop++)
    {
        /* pstUatiInfo->aucCurUATI[ucLoop] & 0xFF is equal to  pstUatiInfo->aucCurUATI[ucLoop] */
        if ((pstUatiInfo->aucCurUATI[ucLoop])
         != (pstHprdSysInfo->aucSectorId[ucLoop]))
        {
            return VOS_TRUE;
        }
    }

    if (0 == ucRemainder)
    {
        return VOS_FALSE;
    }

    ucLeftMask = (VOS_UINT8)(((VOS_UINT32)1) << ucRemainder);
    ucLeftMask -= 1;
    ucLeftMask = (VOS_UINT8)(((VOS_UINT32)ucLeftMask) << (CNAS_HSM_BIT_LEN_PER_BYTE - ucRemainder));

    if ((pstUatiInfo->aucCurUATI[ucLoop] & ucLeftMask)
     != (pstHprdSysInfo->aucSectorId[ucLoop] & ucLeftMask))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID CNAS_HSM_HandleMonitorDistance_Open(
    VOS_UINT8                          *pucIsNeedStartDeactProc
)
{
    CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU                      *pstAmpNegAttr;
    VOS_UINT16                                              usMaxNoMonitorDistance;
    VOS_UINT32                                              usNoMonitorDistance;
    CNAS_HSM_HRPD_SYS_INFO_STRU                            *pstHrpdSysInfo;

    *pucIsNeedStartDeactProc = VOS_FALSE;

    /* read the gloable value */
    pstAmpNegAttr = CNAS_HSM_GetHrpdAmpNegAttribAddr();
    usMaxNoMonitorDistance = pstAmpNegAttr->usMaxNoMonitorDistance;

    if (usMaxNoMonitorDistance != 0)
    {
        /* get the hrpd sys info */
        pstHrpdSysInfo = CNAS_HSM_GetHrpdSysInfoAddr();

        usNoMonitorDistance = CNAS_HSM_GetNoMonitorDistance_Open(pstHrpdSysInfo->lLongitude, pstHrpdSysInfo->lLatitude);

        if (usNoMonitorDistance > usMaxNoMonitorDistance)
        {
             /* C.S0024-A_v3.0 7.3.7.1.6.1 The subnet associated with the UATI and the current subnet are defined to be different if
                 either of the following two conditions are satisfied:
                 1:the UATISubnetMask is not equal to the SubnetMask of the sector in the active set
                 2:the result of bitwise logical AND of the UATI and its subnet mask specified by
                   UATISubnetMask is different from the result of bitwise logical AND of SectorID and
                   its subnet mask specified by SubnetMask(where SectorID and SubnetMask correspond to
                   the sector in the active set) */
            *pucIsNeedStartDeactProc = CNAS_HSM_IsSubnetChanged();
        }
    }

}


/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsdOhmInd_Open
Description     :   open state process HSD overhead message
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED------------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED--------the current event need to further process


Modify History  :
1)  Date           : 2015-02-04
    Author         : m00312079
    Modify content : Create
2)  Date           : 2015-05-29
    Author         : m00312079
    Modify content : add process overhead message in open state
3)  Date           : 2015-06-02
    Author         : t00323010
    Modify content : Iteration 12: add quit Slave State first rcv OHM msg
4)  Date           : 2015-08-20
    Author         : t00323010
    Modify content : DTS2015081904804 clear coverity
5)  Date           : 2015-09-18
    Author         : m00312079
    Modify content : DTS2015091705555:Ϊ��ͨ��RF��CCF2.2.2.8������ֻҪsubnet�����仯������UATI��������
6)  Date           : 2015-09-23
    Author         : t00323010
    Modify content : HSM MNTN(DTS2015092201636): log session operate ctrl info
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsdOhmInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_RCV_OHM_SCENE_ENUM_UINT8                       enRcvOhmScene;
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enCurrSessionRelType;
    VOS_UINT8                                               ucIsNeedStartDeactProc;
    CNAS_HSM_UATI_INFO_STRU                                *pstUatiInfo;
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enCurrSessionType;

    enCurrSessionType   = CNAS_HSM_GetNegoSessionType();
    pstUatiInfo         = CNAS_HSM_GetUatiInfoAddr();

    CNAS_HSM_LogSessionOperateCtrlInfo();

    if (CNAS_HSM_SESSION_TYPE_BUTT != enCurrSessionType)
    {
        /* current session type is HRPD,while on LTE system have register succ,when back to HRPD should
           deactive current HRPD type session, and renegotiate EHRPD type session */
        if (VOS_TRUE == CNAS_HSM_IsNeedReNegEhrpdSession(enCurrSessionType))
        {
            CNAS_HSM_SetRegLteSuccFlag(VOS_FALSE);

            CNAS_HSM_StartSessionDeactiveProcedure_L1Main(CNAS_HSM_SESSION_DEACT_REASON_HRPD_TO_EHRPD);

            return CNAS_HSM_FSM_EVENT_HANDLED;
        }
    }

    CNAS_HSM_SetRegLteSuccFlag(VOS_FALSE);

    ucIsNeedStartDeactProc = VOS_FALSE;

    CNAS_HSM_HandleMonitorDistance_Open(&ucIsNeedStartDeactProc);

    if (VOS_TRUE == ucIsNeedStartDeactProc)
    {
        CNAS_HSM_StartSessionDeactiveProcedure_L1Main(CNAS_HSM_SESSION_DEACT_REASON_AMP_FAIL_OTHER_SCENE);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    enRcvOhmScene = CNAS_HSM_GetRcvOhmScene();

    /* clear the rcv ohm scene */
    CNAS_HSM_SetRcvOhmScene(CNAS_HSM_RCV_OHM_SCENE_FOLLOW_OHM);

    if (CNAS_HSM_RCV_OHM_SCENE_FOLLOW_SYS_ACQ == enRcvOhmScene)
    {
        /*************************************************************************************
         C.S0024-A_v3.0 7.3.7.1.6.1:
             one of the following conditions is true:
             1: the UATISubnetMask is not equal to the SubnetMask of the sector in the active set;
             2: the result of bitwise logical AND of the UATI and ReducedSubnetMask is different from
                the result of bitwise logical AND of SectorID and ReducedMask(where SectorID and SubnetMask
                correspond to the sector in the active set)
         **************************************************************************************/

        ucIsNeedStartDeactProc = CNAS_HSM_IsNeedStartDeactProcedure();

        if (VOS_TRUE == ucIsNeedStartDeactProc)
        {
            /* Save current to prev uait for session restore, then deactive HSM then start session restore */
            NAS_MEM_CPY_S(CNAS_HSM_GetSessionCtrlInfoAddr()->aucPrevUatiForSessionRestore,
                          CNAS_HSM_UATI_OCTET_LENGTH,
                          pstUatiInfo->aucCurUATI,
                          CNAS_HSM_UATI_OCTET_LENGTH);

            CNAS_HSM_StartSessionDeactiveProcedure_L1Main(CNAS_HSM_SESSION_DEACT_REASON_AMP_FAIL_SYS_ACQ_SUBNET_CHANGE);

            return CNAS_HSM_FSM_EVENT_HANDLED;
        }
    }
    else
    {
        /*****************************************************************************************
          C.S0024-A V3.0 7.3.7.1.6.1:
          If the access terminal receives a RouteUpdate.IdleHO indication or a ConnectedState.ConnectionClosed,
          and then it receives an OverheadMessages.Updated indication,
          access terminal shall send a UATIRequest, if both of the following two conditions are true
          1: the subnet associated with UATI and the current subnet are different;
          2: supportSecondaryColorCodes is set to 0x00 or UATIColorCode is different from all of the
             secondaryColorCode values provided as public data by the Overhead Messages protocol
          ��ȫ����Э�鴦��CCF����C.S0038 2.2.2.8����Failed����RF�Զ�������(DTS2015091705555)Ҳ����ͨ����
          ������CNAS_HSM_GetStartUatiReqAfterSectorIdChgFlg()����TRUE(NV�ɿ�)����CNAS���ձ�˴���
          ���ж�CNAS_HSM_RCV_OHM_SCENE_FOLLOW_CONN_CLOSE �� CNAS_HSM_RCV_OHM_SCENE_FOLLOW_IDLE_HO����������
          *****************************************************************************************/

        if ((VOS_TRUE == CNAS_HSM_GetStartUatiReqAfterSectorIdChgFlg())
         || (CNAS_HSM_RCV_OHM_SCENE_FOLLOW_IDLE_HO    == enRcvOhmScene)
         || (CNAS_HSM_RCV_OHM_SCENE_FOLLOW_CONN_CLOSE == enRcvOhmScene))
        {
            if (VOS_TRUE == CNAS_HSM_IsNeedSndUatiReq())
            {
                 /* according to 3gpp2 C.S0024 , AMP should set current UATI to Old uati
                   and process uati request procedure */
                 NAS_MEM_CPY_S(pstUatiInfo->aucOldUATI,
                               sizeof(pstUatiInfo->aucOldUATI),
                               pstUatiInfo->aucCurUATI,
                               sizeof(pstUatiInfo->aucCurUATI));

                 CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
            }
        }
    }

    enCurrSessionRelType = CNAS_HSM_GetCurrSessionRelType();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SUCCESS,
                                       VOS_FALSE,/* old session */
                                       enCurrSessionRelType);

    /* �������̸��ǵķ���̫���ұȽϸ��ӣ����ܻ��м��޸�session type,
       ������Ȼ������ʼʱ��ȡ��session type���˴���Ȼ���»�ȡһ�� */
    enCurrSessionType   = CNAS_HSM_GetNegoSessionType();

    if (CNAS_HSM_SESSION_TYPE_BUTT == enCurrSessionType)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvHsdOhmInd_Open: Curr Session Type is BUTT!");
    }

    CNAS_HSM_SndEhsmSessionInfoInd(enCurrSessionType);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_ProcAmpMsg_Open
Description     :   Process the AMP message in Open
Input parameters:   CTTF_CNAS_HRPD_SNP_DATA_IND_STRU    *pstSnpDataInd
Outout parameters:  None
Return Value    :   VOS_UINT8;

Modify History  :
1)  Date           : 2015-02-04
    Author         : m00312079
    Modify content : Create
2)  Date           : 2015-05-31
    Author         : m00312079
    Modify content : process UATI assignment in open state
3)  Date           : 2015-06-08
    Author         : y00346957
    Modify content : UATI assign�ɹ���״̬�л���uati comp wait snp data cnf
4)  Date           : 2015-06-18
    Author         : t00323010
    Modify content : Iteration 12: add session begin ntf send
*****************************************************************************/
VOS_UINT32 CNAS_HSM_ProcAmpMsg_Open(
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd
)
{
    VOS_UINT8                               ucMsgType;
    CNAS_HSM_UATI_ASSIGN_MSG_STRU           stUatiAssignMsg;
    CNAS_HSM_DECODE_ERROR_TYPE_ENUM_UINT32  ulDecodeRslt;
    VOS_UINT8                               ucIsUatiAssignValidAndFresh;

    ucMsgType = CNAS_HSM_AMP_MESSAGE_TYPE_BUTT;

    ulDecodeRslt = CNAS_HSM_DecodeMsgType(pstSnpDataInd->enProtocolType,
                                          pstSnpDataInd->stMsgData.aucMsgData,
                                          &ucMsgType);

    if ((CNAS_HSM_DECODE_SUCCESS           != ulDecodeRslt)
     || (CNAS_HSM_AMP_MSG_TYPE_UATI_ASSIGN != ucMsgType))
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCttfSnpDataInd_UatiReq_WaitUatiAssign: Decode msg type fail or ucMsgType not as expected");

        return CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }

    NAS_MEM_SET_S(&stUatiAssignMsg, sizeof(stUatiAssignMsg), 0, sizeof(stUatiAssignMsg));

    ulDecodeRslt = CNAS_HSM_DecodeUATIAssignment(pstSnpDataInd->stMsgData.aucMsgData,
                                                 pstSnpDataInd->stMsgData.usMsgBitLen,
                                                 (VOS_VOID *)&stUatiAssignMsg);
    CNAS_MNTN_LogOmAirMsg(CNAS_HRPD_OM_AIR_MSG_DOWN,
                          NAS_OTA_MSG_HSM_AMP_MSG_TYPE_UATI_ASSIGN,
                          UEPS_PID_HSM,
                          (VOS_UINT32)pstSnpDataInd->stMsgData.usMsgBitLen,
                          pstSnpDataInd->stMsgData.aucMsgData);
    if (CNAS_HSM_DECODE_SUCCESS != ulDecodeRslt)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvCttfSnpDataInd_UatiReq_WaitUatiAssign: Decode msg content fail");

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* check the uati assign valid&fresh */
    ucIsUatiAssignValidAndFresh = CNAS_HSM_IsUatiAssignValidAndFresh(&stUatiAssignMsg);

    if (VOS_FALSE == ucIsUatiAssignValidAndFresh)
    {
        /* just discard the message */
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_HandleUatiAssignMsg(&stUatiAssignMsg);

    CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AN);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvCttfSnpDataInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CTTF_CNAS_HRPD_SNP_DATA_IND_STRU                       *pstSnpDataInd;
    CTTF_HRPD_PROTOCOL_TYPE_ENUM_UINT16                     enProtocolType;
    CNAS_HSM_EVENT_HANDLED_STATUES_ENUM_UINT32              enRlst;

    pstSnpDataInd = (CTTF_CNAS_HRPD_SNP_DATA_IND_STRU*)pstMsg;

    enProtocolType = pstSnpDataInd->enProtocolType;

    if (CTTF_HRPD_SNP_ADDRESS_MANAGEMENT_PROTOCOL == enProtocolType)
    {
        enRlst = CNAS_HSM_ProcAmpMsg_Open(pstSnpDataInd);
    }
    else
    {
        enRlst = CNAS_HSM_FSM_EVENT_NOT_HANDLED;
    }

    return enRlst;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvHsmSessionActiveResultInd_Open
Description     :   open state process HSM session active result indication message
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED------------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED--------the current event need to further process

Modify History  :
1)  Date           : 2015-02-04
    Author         : m00312079
    Modify content : Create
2)  Date           : 2015-05-30
    Author         : y00174758
    Modify content : Add handle of different scp reason
3)  Date           : 2015-06-02
    Author         : y00346957
    Modify content : set session neg flag
4)  Date           : 2015-06-03
    Author         : a00295761
    Modify content : Register traffic flow monitor callback function
5)  Date           : 2015-08-20
    Author         : t00323010
    Modify content : DTS2015081904804 clear coverity
6)  Date           : 2015-09-18
    Author         : m00312079
    Modify content : DTS2015091604029: sessionЭ�̳ɹ��󣬽�session seedд��nv
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvHsmSessionActiveResultInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU            *pstSessionActRsltInd;
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;

    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enCurrSessionType;

    CNAS_HSM_SetSessionNegOngoingFlag(VOS_FALSE);

    pstSessionActRsltInd  = (CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU *)pstMsg;

    if (CNAS_HSM_SESSION_ACTIVE_RESULT_SUCC == pstSessionActRsltInd->enRslt)
    {
        CNAS_HSM_SetSessionStatus(CNAS_HSM_SESSION_STATUS_OPEN);

        /* ��ά�ɲ���Ϣ */
        CNAS_HSM_UpdateHrpdAtiInfo();
        CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SESSION_OPEN, UEPS_PID_HSM);

        CNAS_HSM_WriteHrpdSessionInfoNvim();

        CNAS_HSM_WriteHrpdSessionInfoExNvim();
        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SUCCESS,
                                           VOS_TRUE,
                                           CNAS_HSM_GetCurrSessionRelType());

        /* Initialize the variable which records the system tick when AT receives forward traffic chan data */
        CNAS_HSM_SetSysTickFwdTrafficChan(CNAS_HSM_GetSysTick());

        /* HSM will register the callback function that will update the Sys tick at which forward traffic chan data
        is received */
        CTTF_HRPD_FSPS_RegTrafficFlowMonitor(CNAS_HSM_ProcTrafficFlowOnForwardChannel);

        /* HSM will process the keep alive timer */
        CNAS_HSM_ProcKeepAliveTimer(CNAS_HSM_KEEP_ALIVE_SCENE_SESSION_ACTIVATED);

        enCurrSessionType   = CNAS_HSM_GetNegoSessionType();

        if (CNAS_HSM_SESSION_TYPE_BUTT == enCurrSessionType)
        {
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvHsmSessionActiveResultInd_Open: Curr Session Type is BUTT!");
        }

        /* SessionЭ�̳ɹ�֮���HLU�� SESSION_CHANGED_IND ��Ϣ */
        CNAS_HSM_SndHluSessionChangedInd(enCurrSessionType);

        /* ����session���Բ��� */
        CNAS_HSM_ResetSessionRetryParameters();
    }
    else
    {
        /* trigger session deactive procedure */
        enSessionDeactReason = CNAS_HSM_ConvertSessionActFailReasonToSessionDeactReason(
                                                              pstSessionActRsltInd->enFailReason);

        CNAS_HSM_StartSessionDeactiveProcedure_L1Main(enSessionDeactReason);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsmSessionDeactiveResultInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU          *pstRsltIndMsg;

    CNAS_HSM_SESSION_CLOSE_INFO_STRU                       *pstSessionCloseInfo;

    pstRsltIndMsg = (CNAS_HSM_HSM_SESSION_DEACTIVE_RESULT_IND_STRU *)pstMsg;

    CNAS_HSM_CleanReviseTimerScene_SessionDeact();

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_INACTIVE);

    CNAS_HSM_EnterInactiveStateProc_L1Main();

    /* Stop the Keep Alive timer and save the Session Keep Alive Info */
    CNAS_HSM_ProcKeepAliveTimer(CNAS_HSM_KEEP_ALIVE_SCENE_SESSION_DEACTIVATED);

    pstSessionCloseInfo = CNAS_HSM_GetSessionCloseInfoCtxAddr();

    /* ����AN��Ȩ������ܾ��������Σ���Avoid��ǰƵ��10���� */
    if (pstSessionCloseInfo->ucCount >= CNAS_HSM_AN_AUTH_MAX_REJECT_CNT)
    {
        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);

        NAS_MEM_SET_S(pstSessionCloseInfo,
                      sizeof(CNAS_HSM_SESSION_CLOSE_INFO_STRU),
                      0x00,
                      sizeof(CNAS_HSM_SESSION_CLOSE_INFO_STRU));

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* ���Session deactiveԭ��ֵ��ABORT���ȴ����棬���洦����֮�������� */
    if (VOS_TRUE == CNAS_HSM_IsSessionDeactReasonAbort(pstRsltIndMsg->enSessionDeactReason))
    {
        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_ProcSessionRetryAfterSessionDeact_L1Main(pstRsltIndMsg->enSessionDeactReason);

    CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SESSION_CLOSE, UEPS_PID_HSM);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvUatiRequestResultInd_Open
Description     :   open state process uati request result indication message
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED------------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED--------the current event need to further process


Modify History  :
1)  Date           : 2015-02-07
    Author         : y00174758
    Modify content : Create
2)  Date           : 2015-05-31
    Author         : m00312079
    Modify content : add process uati assignment in open state
3)  Date           : 2015-06-02
    Author         : y00346957
    Modify content : set session neg flag
4)  Date           : 2015-11-27
    Author         : m00312079
    Modify content : DTS2015111102189:����C.S0024Э��Ҫ��UATI reqֻ������AC�Ϸ��ͣ�CNAS����ӱ���
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvUatiRequestResultInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU              *pstUatiResult;
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enCurrSessionRelType;

    pstUatiResult = (CNAS_HSM_HSM_UATI_REQUEST_RESULT_IND_STRU*)pstMsg;

    switch (pstUatiResult->enRslt)
    {
        case CNAS_HSM_UATI_REQUEST_RESULT_FAIL :

            enSessionDeactReason = CNAS_HSM_ConvertUaitFailReasonToSessionDeactReason(pstUatiResult->enFailReason);
            CNAS_HSM_StartSessionDeactiveProcedure_L1Main(enSessionDeactReason);
            CNAS_HSM_SetSessionNegOngoingFlag(VOS_FALSE);

            break;
        case CNAS_HSM_UATI_REQUEST_RESULT_SUCC :
            enCurrSessionRelType = CNAS_HSM_GetCurrSessionRelType();

            CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SUCCESS,
                                               VOS_FALSE,               /* old session */
                                               enCurrSessionRelType);

            CNAS_HSM_WriteHrpdSessionInfoNvim();

            break;
        case CNAS_HSM_UATI_REQUEST_RESULT_CANCEL :

            /* ĿǰCANCELԭ��ֵֻ��һ������:����UATI reqʱ���ֵ�ǰ����TCH�ŵ�����ʱ�˳�״̬��������ָ��UATI assignment */
            break;
        default:
            CNAS_WARNING_LOG(UEPS_PID_HSM, "CNAS_HSM_RcvUatiRequestResultInd_Open: unknown enRslt ");

            break;
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvCasHrpdPageInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (CNAS_HSM_HRPD_CONN_STATUS_OPEN != CNAS_HSM_GetConnStatus())
    {
        CNAS_HSM_StartConnMnmtProcedure_L1Main(CNAS_HSM_CONN_MNMT_TRIGGER_BY_PAGE_IND);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (CNAS_HSM_HRPD_CONN_STATUS_OPEN == CNAS_HSM_GetConnStatus())
    {
        CNAS_HSM_StartConnMnmtProcedure_L1Main(CNAS_HSM_CONN_MNMT_TRIGGER_BY_POWER_SAVE);
    }
    else
    {
        CNAS_HSM_SndHsdPowerSaveCnf();

        CNAS_HSM_SndEhsmSuspendInd();

        /* ����session���Բ��� */
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_EnterSlaveStateProc_L1Main();
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdSuspendInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����session���Բ��� */
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_EnterSlaveStateProc_L1Main();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdHrpdPilotSearchFailNtf_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����session���Բ��� */
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_EnterSlaveStateProc_L1Main();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}

/*****************************************************************************
Function Name   :   CNAS_HSM_RcvApsOrigReq_Open
Description     :   process the Aps orig req in open state
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   CNAS_HSM_FSM_EVENT_HANDLED------------the current event is processed finished
                    CNAS_HSM_FSM_EVENT_NOT_HANDLED--------the current event need to further process

Modify History  :
1)  Date           : 2015-05-31
    Author         : m00312079
    Modify content : Create

  2.��    ��   : 2015��10��22��
    ��    ��   : Y00213812
    �޸�����   : ɾ��ΪDTS2015081101470���׮
*****************************************************************************/
VOS_UINT32 CNAS_HSM_RcvApsOrigReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_HSM_ORIG_REQ_STRU                                  *pstCallOrigMsg;

    pstCallOrigMsg = (APS_HSM_ORIG_REQ_STRU *)pstMsg;

    if (CNAS_HSM_HRPD_CONN_STATUS_OPEN == CNAS_HSM_GetConnStatus())
    {
        /* Save CallId send by APS. */
        CNAS_HSM_SaveHsmCallId(pstCallOrigMsg->ucCallId);
        CNAS_HSM_SndApsOrigCnf(pstCallOrigMsg->ucCallId, HSM_APS_CAUSE_SUCCESS);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    /* Save CallId send by APS. */
    CNAS_HSM_SaveHsmCallId(pstCallOrigMsg->ucCallId);

    CNAS_HSM_StartConnMnmtProcedure_L1Main(CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_OPEN_CONN);
    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvApsDiscReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_HSM_DISC_REQ_STRU                                  *pstApsDiscReq;
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus;

    enConnStatus = CNAS_HSM_GetConnStatus();

    if (CNAS_HSM_HRPD_CONN_STATUS_OPEN != enConnStatus)
    {
        pstApsDiscReq    =  (APS_HSM_DISC_REQ_STRU *)pstMsg;

        CNAS_HSM_SndApsDiscCnf(pstApsDiscReq->ucCallId, HSM_APS_CAUSE_SUCCESS);

        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_StartConnMnmtProcedure_L1Main(CNAS_HSM_CONN_MNMT_TRIGGER_BY_APS_CLOSE_CONN);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvEhsmConnEstReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus;

    enConnStatus = CNAS_HSM_GetConnStatus();

    if (CNAS_HSM_HRPD_CONN_STATUS_OPEN == enConnStatus)
    {
        CNAS_HSM_SndEhsmConnEstCnf(EHSM_HSM_RSLT_SUCCESS);
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_StartConnMnmtProcedure_L1Main(CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_OPEN_CONN);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvEhsmDiscReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus;

    enConnStatus = CNAS_HSM_GetConnStatus();

    if (CNAS_HSM_HRPD_CONN_STATUS_OPEN != enConnStatus)
    {
        CNAS_HSM_SndEhsmDiscCnf();
        return CNAS_HSM_FSM_EVENT_HANDLED;
    }

    CNAS_HSM_StartConnMnmtProcedure_L1Main(CNAS_HSM_CONN_MNMT_TRIGGER_BY_EHSM_CLOSE_CONN);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    CNAS_HSM_ProcPowerOffReq();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}





VOS_UINT32 CNAS_HSM_RcvHsmConnMnmtResultInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU                 *pstConnMnmtRsltInd;

    pstConnMnmtRsltInd  = (CNAS_HSM_HSM_CONN_MNMT_RESULT_IND_STRU *)pstMsg;

    /* �����power save���������ӶϿ����̣�Ǩ״̬��Slave */
    if (CNAS_HSM_CONN_MNMT_TRIGGER_BY_POWER_SAVE == pstConnMnmtRsltInd->enTriggerScene)
    {
        /* ����session���Բ��� */
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_EnterSlaveStateProc_L1Main();
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}




VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_Open(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU                    *pstMsgInd;
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason;

    /* �ߵ��˺����ĳ����ʹ���:
     * 1) Open״̬Keep Alive��ʱ����ʱ: Sessionȥ����������Բ�������ʼUATI����
     * 2) Open״̬�յ����緢��SessionClose: Sessionȥ����������Բ�������ʼUATI����
     * 3) Open״̬�յ�ID_CAS_CNAS_HRPD_SESSION_NEG_RSLT_IND: Sessionȥ�����ʼ�������̺�UATI����
     */

    pstMsgInd = (CNAS_HSM_HSM_SESSION_CLOSE_IND_STRU *)pstMsg;

    switch (pstMsgInd->enScene)
    {
        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_KEEP_ALIVE_EXP_OPEN:

            enSessionDeactReason = CNAS_HSM_SESSION_DEACT_REASON_KEEP_ALIVE_EXP_OPEN;

            break;

        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_AN_CLOSE_IN_OPEN_NOT_SESSION_ACT:

            enSessionDeactReason = CNAS_HSM_SESSION_DEACT_REASON_AN_CLOSE_SESSION_IN_VACANT;

            break;

        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_RCV_CAS_NEG_RSLD_IND:

            enSessionDeactReason = CNAS_HSM_ConvertScpNegRsltIndFailReasonToSessionDeactReason(
                                                         pstMsgInd->stSessionNegRsltInfo.enResult);

            if (PS_TRUE == pstMsgInd->stSessionNegRsltInfo.enProtocolTypeVaildFlag)
            {
                CNAS_HSM_SetScpActFailProcType(pstMsgInd->stSessionNegRsltInfo.usProtocolType);
                CNAS_HSM_SetScpActFailProcSubtype(pstMsgInd->stSessionNegRsltInfo.usProtocolSubType);
            }

            break;

        case CNAS_HSM_INTERNAL_SESSION_CLOSE_IND_SCENE_IN_CONN_MNMT_SENT_SESSION_CLOSE:

            enSessionDeactReason = CNAS_HSM_SESSION_DEACT_REASON_INTERNAL_SESSION_CLOSE_IN_CONN_MNMT;

            break;

        default:

            return CNAS_HSM_FSM_EVENT_HANDLED;

    }

    CNAS_HSM_StartSessionDeactiveProcedure_L1Main(enSessionDeactReason);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}




VOS_VOID CNAS_HSM_EnterInactiveStateProc_L1Main(VOS_VOID)
{
    /* 3GPP2 C.S0024-A_v3.0:7.3.7.1.4.1
      Upon entering the Inactive State, the access terminal shall perform the following:
      1)Set OldUATI to NULL.
      2)Clear the ReceiveATIList
      3)Add the following entry to the ReceiveATIList:
        <ATIType = ��00��, ATI = NULL>.
        Set TransmitATI to <ATIType = NULL, ATI = NULL>.
      4)Set UATI to NULL.
      5)Set UATIColorCode to NULL.
      6)Set UATISubnetMask to NULL.
      7)Set SessionSeed to the 32-bit pseudo-random number generated using output of the
        pseudo random number generator specified in 14.5
      8)Disable the Address timers.
      9)Set (xo, yo) to (NULL, NULL).
    */
    VOS_UINT32                          ulSessionSeed;
    CNAS_HSM_SESSION_CTRL_STRU         *pstSessionCtrlInfo;
    CNAS_HSM_ATI_LIST_INFO_STRU        *pstReceiveAtiListInfo;
    CNAS_HSM_ATI_RECORD_STRU           *pstTransmitAtiInfo;
    CNAS_HSM_LOC_INFO_STRU             *pstLocInfo;
    VOS_UINT8                           i;

    CNAS_HSM_SetRcvOhmScene(CNAS_HSM_RCV_OHM_SCENE_FOLLOW_OHM);

    pstSessionCtrlInfo = CNAS_HSM_GetSessionCtrlInfoAddr();

    /* init UATI info */
    CNAS_HSM_InitUATIInfo(&pstSessionCtrlInfo->stUATIInfo);

    /* init transmit ATI */
    pstTransmitAtiInfo   = CNAS_HSM_GetTransmitATIAddr();
    CNAS_HSM_InitATIRecord(pstTransmitAtiInfo);

    /* init receive ATI list */
    pstReceiveAtiListInfo = CNAS_HSM_GetReceivedATIListAddr();

    CNAS_HSM_InitATIList(pstReceiveAtiListInfo);

    /* add one entry to the receive ATI list */
    pstReceiveAtiListInfo->ulATIRecordNum = 1;
    pstReceiveAtiListInfo->astATIEntry[0].enATIType = CNAS_HSM_ATI_TYPE_BATI;

    for (i = 0; i < CNAS_HSM_ATI_VALUE_LENGTH; i++)
    {
        pstReceiveAtiListInfo->astATIEntry[0].aucATIValue[i] = CNAS_HSM_INVALID_ATI_VALUE;
    }

    CNAS_HSM_StopTimer(TI_CNAS_HSM_ADDRESS_TIMER);

    ulSessionSeed = CNAS_HSM_GetSessionSeed();
    ulSessionSeed = CNAS_HSM_GenerateCurrentSessionSeed(ulSessionSeed);

    CNAS_HSM_SetSessionSeed(ulSessionSeed);

    //��ά�ɲ���Ϣ
    CNAS_HSM_UpdateHrpdAtiInfo();

    /* init the location information */
    pstLocInfo = CNAS_HSM_GetLocInfoAddr();

    pstLocInfo->lLatitude  = CNAS_HSM_INVALIDE_LATITUDE;
    pstLocInfo->lLongitude = CNAS_HSM_INVALIDE_LONGITUDE;

    /* deregister the callback function */
    CTTF_HRPD_FSPS_DeregTrafficFlowMonitor();

    CNAS_HSM_SndCasHrpdSessionSeedNtf(ulSessionSeed);

    CNAS_HSM_SndMacTransmitAtiNotify(pstTransmitAtiInfo);

    CNAS_HSM_SndMacReceiveAtiNotify(pstReceiveAtiListInfo);
}


VOS_VOID CNAS_HSM_EnterSetupStateProc_L1Main(VOS_VOID)
{
    /* 3GPP2 C.S0024-A_v3.0:7.3.7.1.5.1 Access Terminal Requirements
      Upon entering the Setup State the access terminal shall perform the following:
      Set the TransmitATI to
      <ATIType = ��11��, ATI = SessionSeed>,
      Add the following entry to the ReceiveATIList list
      <ATIType = ��11��, ATI = SessionSeed>.
      Shall send a UATIRequest message.
    */
    CNAS_HSM_ATI_RECORD_STRU           *pstPubTransATI;
    CNAS_HSM_ATI_LIST_INFO_STRU        *pstPubRcvATIList;
    VOS_UINT32                          ulSessionSeed;
    CNAS_HSM_ATI_RECORD_STRU           *pstRcvATI;

    ulSessionSeed = CNAS_HSM_GetSessionSeed();

    /* Update TransmitAIT and send to MAC */
    pstPubTransATI                 = CNAS_HSM_GetTransmitATIAddr();
    pstPubTransATI->enATIType      = CNAS_HSM_ATI_TYPE_RATI;

    /* aucATIValue[0] = ulSessionSeed[31:24], aucATIValue[1] = ulSessionSeed[23:16]
     * aucATIValue[2] = ulSessionSeed[15:8], aucATIValue[3] = ulSessionSeed[7:0]
     */
    pstPubTransATI->aucATIValue[0] = (VOS_UINT8)((ulSessionSeed & 0xFF000000) >> 24);
    pstPubTransATI->aucATIValue[1] = (VOS_UINT8)((ulSessionSeed & 0x00FF0000) >> 16);
    pstPubTransATI->aucATIValue[2] = (VOS_UINT8)((ulSessionSeed & 0x0000FF00) >> 8);
    pstPubTransATI->aucATIValue[3] = (VOS_UINT8)(ulSessionSeed & 0x000000FF);

    CNAS_HSM_SndMacTransmitAtiNotify(pstPubTransATI);

    /* Update ReceiveATIList and send to MAC */
    pstPubRcvATIList    = CNAS_HSM_GetReceivedATIListAddr();

    /* In inactive state, ATIType = '00' is the first record, so add RATI as the second record */
    if (pstPubRcvATIList->ulATIRecordNum < CNAS_HSM_MAX_UATI_REC_NUM)
    {
        pstRcvATI = &(pstPubRcvATIList->astATIEntry[pstPubRcvATIList->ulATIRecordNum]);

        pstPubRcvATIList->ulATIRecordNum += 1;
    }
    else
    {
        pstRcvATI = &(pstPubRcvATIList->astATIEntry[CNAS_HSM_MAX_UATI_REC_NUM -1]);
    }

    pstRcvATI->enATIType  = CNAS_HSM_ATI_TYPE_RATI;

    /* aucATIValue[0] = ulSessionSeed[31:24], aucATIValue[1] = ulSessionSeed[23:16]
     * aucATIValue[2] = ulSessionSeed[15:8], aucATIValue[3] = ulSessionSeed[7:0]
     */
    pstRcvATI->aucATIValue[0] = (VOS_UINT8)((ulSessionSeed & 0xFF000000) >> 24);
    pstRcvATI->aucATIValue[1] = (VOS_UINT8)((ulSessionSeed & 0x00FF0000) >> 16);
    pstRcvATI->aucATIValue[2] = (VOS_UINT8)((ulSessionSeed & 0x0000FF00) >> 8);
    pstRcvATI->aucATIValue[3] = (VOS_UINT8)(ulSessionSeed & 0x000000FF);

    CNAS_HSM_SndMacReceiveAtiNotify(pstPubRcvATIList);
}


VOS_VOID CNAS_HSM_StartUATIRequestProcedure_L1Main(
    CNAS_HSM_UATI_REQ_TRIGGER_ENUM_UINT8                    enTriggerReason
)
{
    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF, 0))
    {
        CNAS_HSM_ResetUatiCompleteRetryTimes();

        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);
    }

    CNAS_HSM_SndCasHrpdSessionBeginNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);

    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_UATI_REQUEST_INIT);

    CNAS_HSM_SndInternalUATIReq(enTriggerReason);
}



/* Added session active reason input parameter and added session Active reason input paramter to snd intrnl msg func */
VOS_VOID CNAS_HSM_StartSessionActiveProcedure_L1Main(
    CNAS_HSM_SESSION_ACTIVE_REASON_ENUM_UINT8               enSessionActiveReason
)
{
    CNAS_HSM_SetRegLteSuccFlag(VOS_FALSE);
    CNAS_HSM_SetScpActiveFlag(VOS_TRUE);

    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_SESSION_ACT_INIT);
    CNAS_HSM_SndInternalSessionActiveReq(enSessionActiveReason);
}

/*****************************************************************************
Function Name   :  CNAS_HSM_StartSessionDeactiveProcedure_L1Main
Description     :  HSM start session deactive procedure
Input parameters:  enReason -- session deactive reasons
Outout parameters: VOS_VOID
Return Value    :  VOS_VOID

Modify History  :
1)  Date           : 2015-02-07
    Author         : w00176964
    Modify content : Create
2)  Date           : 2015-05-30
    Author         : y00174758
    Modify content : Change session deacitve reason to session close reason
3)  Date           : 2015-10-19
    Author         : m00312079
    Modify content : DTS2015101606193,session��Чʱ����keep alive��nv��Ϣ��ȫ�ֱ������(NVID=2029)
4)  Date           : 2015-01-05
    Author         : w00351686
    Modify content : DTS2015110200394 del UatiComplete SubState modify
*****************************************************************************/
/* Change session deacitve reason to session close reason */
VOS_VOID CNAS_HSM_StartSessionDeactiveProcedure_L1Main(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
)
{
    CNAS_HSM_SESSION_KEEP_ALIVE_INFO_STRU                  *pstSessionKeepAliveInfo;

    CNAS_HSM_SESSION_TYPE_ENUM_UINT8                        enSessionType;
    VOS_UINT8                                               ucCallId;
    CNAS_HSM_HRPD_CONN_STATUS_ENUM_UINT8                    enConnStatus;

    /* ����session deactive����ʱ����֪ͨaps/ehsm����ָʾ�� */
    enSessionType = CNAS_HSM_GetNegoSessionType();
    enConnStatus  = CNAS_HSM_GetConnStatus();

    if (CNAS_HSM_HRPD_CONN_STATUS_OPEN == enConnStatus)
    {
        if (CNAS_HSM_SESSION_TYPE_HRPD == enSessionType)
        {
            ucCallId = CNAS_HSM_GetHsmCallId();

            if (ucCallId != CNAS_HSM_CALL_ID_INVALID)
            {
                CNAS_HSM_SndApsDiscInd(ucCallId, HSM_APS_CAUSE_SESSION_NOT_EXIST);
            }

            CNAS_HSM_SaveHsmCallId(CNAS_HSM_CALL_ID_INVALID);
        }
        else if (CNAS_HSM_SESSION_TYPE_EHRPD == enSessionType)
        {
            CNAS_HSM_SndEhsmDiscInd();
        }
        else
        {
            /* ��session��֪ͨAPS/EHSM */
        }
    }

    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_SESSION_DEACT_INIT);
    CNAS_HSM_SetSessionStatus(CNAS_HSM_SESSION_STATUS_CLOSE);

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM, TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF, 0))
    {
        CNAS_HSM_ResetUatiCompleteRetryTimes();

        CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_COMPLETE_WAIT_SNP_DATA_CNF);

        CNAS_HSM_SndCasHrpdSessionEndNtf(CNAS_CAS_HRPD_SESSION_TYPE_UATI);
    }

    /* ��ά�ɲ���Ϣ */
    CNAS_HSM_UpdateHrpdAtiInfo();

    CNAS_HSM_ClearNegoSessionType();

    CNAS_HSM_WriteHrpdSessionInfoNvim();

    pstSessionKeepAliveInfo = CNAS_HSM_GetSessionKeepAliveInfoAddr();

    NAS_MEM_SET_S(pstSessionKeepAliveInfo,
                  sizeof(CNAS_HSM_SESSION_KEEP_ALIVE_INFO_STRU),
                  0x00,
                  sizeof(CNAS_HSM_SESSION_KEEP_ALIVE_INFO_STRU));

    CNAS_HSM_SetKeepAliveInfoValidFlag(VOS_FALSE);
    CNAS_HSM_SetTsmpClose(CNAS_HSM_DEFAULT_TSMP_CLOSE_LEN);
    CNAS_HSM_SetTsmpCloseRemainTime(CNAS_HSM_DEFAULT_TSMP_CLOSE_REMAIN_LEN);

    CNAS_HSM_WriteSessionKeepAliveInfoNvim(pstSessionKeepAliveInfo);

    CNAS_HSM_WriteHrpdAccessAuthInfoNvim();
    CNAS_HSM_SndInternalSessionDeactiveReq(enSessionDeactReason);
}


VOS_VOID CNAS_HSM_StartSwitchOnProcedure_L1Main(VOS_VOID)
{
    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_SWITCH_ON_INIT);

    CNAS_HSM_SndInternalSwitchOnReq();
}


VOS_VOID CNAS_HSM_EnterSlaveStateProc_L1Main(VOS_VOID)
{
    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SLAVE);
}


VOS_UINT32 CNAS_HSM_RcvHsdSystemAcqInd_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  enCurSessionStatus;
    VOS_UINT8                           ucIsFirstSysAcq;
    HSD_HSM_SYSTEM_ACQUIRED_IND_STRU   *pstHsdSysAcqInd = VOS_NULL_PTR;

    enCurSessionStatus  = CNAS_HSM_GetSessionStatus();
    ucIsFirstSysAcq     = CNAS_HSM_GetFirstSysAcqFlag();
    pstHsdSysAcqInd     = (HSD_HSM_SYSTEM_ACQUIRED_IND_STRU *)pstMsg;

    CNAS_HSM_LogQuitSlaveStateInfo(enCurSessionStatus, ucIsFirstSysAcq);

    /* Save the CDMA Sys time and current tick */
    CNAS_HSM_SaveSysTimeAndCurSysTick(pstHsdSysAcqInd->aulSystemTime);

    if (CNAS_HSM_SESSION_STATUS_OPEN == enCurSessionStatus)
    {
        CNAS_HSM_SetRcvOhmScene(CNAS_HSM_RCV_OHM_SCENE_FOLLOW_SYS_ACQ);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_OPEN);
    }
    else
    {
        if (VOS_TRUE == ucIsFirstSysAcq)
        {
            /* HSM will start the session recovery flow if the last session must be recovered. Otherwise, HSM will generate the
            Initial session seed and will perform the enter Inactive state procedure. */
            CNAS_HSM_ProcMsgForFirstSysAcq_L1Main();

            return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_INACTIVE);

        CNAS_HSM_EnterInactiveStateProc_L1Main();
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdResumeInd_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (CNAS_HSM_SESSION_STATUS_OPEN == CNAS_HSM_GetSessionStatus())
    {
        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_OPEN);
    }
    else
    {
        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_INACTIVE);

        CNAS_HSM_EnterInactiveStateProc_L1Main();
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdIratFromLteNtf_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SESSION_STATUS_ENUM_UINT8  enCurSessionStatus;
    VOS_UINT8                           ucIsFirstSysAcq;

    enCurSessionStatus  = CNAS_HSM_GetSessionStatus();
    ucIsFirstSysAcq     = CNAS_HSM_GetFirstSysAcqFlag();

    CNAS_HSM_LogQuitSlaveStateInfo(enCurSessionStatus, ucIsFirstSysAcq);

    if (CNAS_HSM_SESSION_STATUS_OPEN == enCurSessionStatus)
    {
        CNAS_HSM_SetRcvOhmScene(CNAS_HSM_RCV_OHM_SCENE_FOLLOW_SYS_ACQ);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_OPEN);
    }
    else
    {
        if (VOS_TRUE == ucIsFirstSysAcq)
        {
            /* HSM will start the session recovery flow if the last session must be recovered. Otherwise, HSM will generate the
            Initial session seed and will perform the enter Inactive state procedure. */
            CNAS_HSM_ProcMsgForFirstSysAcq_L1Main();

            return CNAS_HSM_FSM_EVENT_HANDLED;
        }

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_INACTIVE);

        CNAS_HSM_EnterInactiveStateProc_L1Main();
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerOffReq_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_HRPD_SESSION_NEG, VOS_RATMODE_HRPD);

    CNAS_HSM_ProcPowerOffReq();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}


VOS_UINT32 CNAS_HSM_RcvHsdPowerSaveReq_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_SndHsdPowerSaveCnf();

    CNAS_HSM_SndEhsmSuspendInd();

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT32 CNAS_HSM_RcvHsmSessionActiveResultInd_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU            *pstSessionActRsltInd;

    pstSessionActRsltInd  = (CNAS_HSM_HSM_SESSION_ACTIVE_RESULT_IND_STRU *)pstMsg;

    /* this will only happen in session recovery flow */
    if (CNAS_HSM_SESSION_ACTIVE_RESULT_FAIL == pstSessionActRsltInd->enRslt)
    {
        /* proc enter inactive state */
        CNAS_HSM_EnterInactiveStateProc_L1Main();

        /* HSM will set next state to Inactive state and will wait for the Overhead message */
        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_INACTIVE);
    }
    else
    {
        CNAS_HSM_ProcSessionRecoverySucc_L1Main();

        /* ��ά�ɲ���Ϣ */
        CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SESSION_OPEN, UEPS_PID_HSM);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}




VOS_UINT32 CNAS_HSM_RcvHsmSessionDeactiveResultInd_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSM_CleanReviseTimerScene_SessionDeact();

    /* Stop the Keep Alive timer */
    CNAS_HSM_ProcKeepAliveTimer(CNAS_HSM_KEEP_ALIVE_SCENE_SESSION_DEACTIVATED);

    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SESSION_CLOSE, UEPS_PID_HSM);

    return CNAS_HSM_FSM_EVENT_HANDLED;
}




VOS_UINT32 CNAS_HSM_RcvHsmSessionCloseInd_Slave(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ߵ���������ĳ���:
     * 1) Save״̬��Keep Alive��ʱ
     * 2) ������״̬���У��յ�AN��SessionClose/ID_CNAS_HSM_HSM_SESSION_CLOSE_IND/Keep Alive��ʱ��
          Deactive�������յ�Power Save/Suspend����ʱ������deactive��session״̬Ϊclose
     * 3) ����״̬���У��յ�AN��SessionClose/ID_CNAS_HSM_HSM_SESSION_CLOSE_IND/Keep Alive��ʱ��
     *    Ȼ��������״̬�����յ�Power Save/Suspend����ʱδ����deactive��session״̬Ϊopen����Ҫ��deactive
     */
    if (CNAS_HSM_SESSION_STATUS_OPEN == CNAS_HSM_GetSessionStatus())
    {
        CNAS_HSM_StartSessionDeactiveProcedure_L1Main(
                                CNAS_HSM_SESSION_DEACT_REASON_INTERNAL_SESSION_CLOSE_SLAVE);
    }

    return CNAS_HSM_FSM_EVENT_HANDLED;
}



VOS_UINT8 CNAS_HSM_IsNeedReNegEhrpdSession(
    CNAS_HSM_SESSION_TYPE_ENUM_UINT8    enCurrSessionType
)
{
    VOS_UINT8                           ucRegLteSuccFlg;
    VOS_UINT8                           ucNeedReNegEhrpdSession;

    ucRegLteSuccFlg         = CNAS_HSM_GetRegLteSuccFlag();
    ucNeedReNegEhrpdSession = VOS_FALSE;

    if ((VOS_TRUE == CNAS_HSM_IsCurrentCapSupportEhrpd())
     && (VOS_TRUE == ucRegLteSuccFlg)
     && (CNAS_HSM_SESSION_TYPE_HRPD == enCurrSessionType))
    {
        ucNeedReNegEhrpdSession = VOS_TRUE;
    }

    return ucNeedReNegEhrpdSession;
}


VOS_UINT8 CNAS_HSM_IsNeedSndUatiReq(VOS_VOID)
{
    VOS_UINT8                                               ucIsSubnetChanged;
    CNAS_HSM_HRPD_SYS_INFO_STRU                            *pstHprdSysInfo;
    CNAS_HSM_UATI_INFO_STRU                                *pstUatiInfo;
    VOS_UINT16                                              usSupportSecondaryColorCodes;
    VOS_UINT8                                               ucLoop;
    CNAS_HSM_HRPD_AMP_NEG_ATTRIB_STRU                      *pstAmpNegAttr;

    /* C.S0024-A V3.0 7.3.7.1.6.1:
        access terminal shall send a UATIRequest, if both of the following two conditions are true
     1: the subnet associated with UATI and the current subnet are different;
     2: supportSecondaryColorCodes is set to 0x00 or UATIColorCode is different from all of the
        secondaryColorCode values provided as public data by the Overhead Messages protocol */

    /* condition 1: */
    ucIsSubnetChanged = CNAS_HSM_IsSubnetChanged();

    if (VOS_FALSE == ucIsSubnetChanged)
    {
        return VOS_FALSE;
    }

    /* condition 2: */
    pstAmpNegAttr = CNAS_HSM_GetHrpdAmpNegAttribAddr();

    usSupportSecondaryColorCodes = pstAmpNegAttr->usSupportSecondaryColorCodes;

    pstHprdSysInfo    = CNAS_HSM_GetHrpdSysInfoAddr();
    pstUatiInfo       = CNAS_HSM_GetUatiInfoAddr();

    if (0x00 == usSupportSecondaryColorCodes)
    {
        return VOS_TRUE;
    }

    if (0x00 == pstHprdSysInfo->ucSecondaryColorCodeCount)
    {
        return VOS_TRUE;
    }

    for (ucLoop = 0; ucLoop < pstHprdSysInfo->ucSecondaryColorCodeCount; ucLoop++)
    {
        if (pstUatiInfo->ucUATIColorCode == pstHprdSysInfo->aucSecondaryColorCode[ucLoop])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}

/*****************************************************************************
Function Name   :  CNAS_HSM_IsSubnetChanged
Description     :  HSM check whether the subnet changed or not
Input parameters:  VOS_VOID
Outout parameters: VOS_VOID
Return Value    :  VOS_UINT8

Modify History  :
1)  Date           : 2015-05-31
    Author         : m00312079
    Modify content : Create

2.  ��    ��   : 2015��08��24��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_UINT8 CNAS_HSM_IsSubnetChanged(VOS_VOID)
{
    CNAS_HSM_UATI_INFO_STRU            *pstUatiInfo;
    CNAS_HSM_HRPD_SYS_INFO_STRU        *pstHprdSysInfo;
    VOS_UINT8                           ucQuotient;
    VOS_UINT8                           ucRemainder;
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLeftMask;

    pstHprdSysInfo    = CNAS_HSM_GetHrpdSysInfoAddr();
    pstUatiInfo       = CNAS_HSM_GetUatiInfoAddr();

    /* C.S0024-A_v3.0 7.3.7.1.6.1 The subnet associated with the UATI and the current subnet are defined to be different if
        either of the following two conditions are satisfied:
        1:the UATISubnetMask is not equal to the SubnetMask of the sector in the active set
        2:the result of bitwise logical AND of the UATI and its subnet mask specified by
          UATISubnetMask is different from the result of bitwise logical AND of SectorID and
          its subnet mask specified by SubnetMask(where SectorID and SubnetMask correspond to
          the sector in the active set) */

    /* Condition 1: */
    if (pstHprdSysInfo->ucSubNetMask != pstUatiInfo->ucUATISubnetMask)
    {
        return VOS_TRUE;
    }

    /* Condition 2: */
    ucQuotient  = (pstHprdSysInfo->ucSubNetMask) / CNAS_HSM_BIT_LEN_PER_BYTE;
    ucRemainder = (pstHprdSysInfo->ucSubNetMask) % CNAS_HSM_BIT_LEN_PER_BYTE;

    for (ucLoop = 0; ucLoop < ucQuotient; ucLoop++)
    {
        /* pstUatiInfo->aucCurUATI[ucLoop] & 0xFF is equal to pstUatiInfo->aucCurUATI[ucLoop] */
        if ((pstUatiInfo->aucCurUATI[ucLoop])
         != (pstHprdSysInfo->aucSectorId[ucLoop]))
        {
            return VOS_TRUE;
        }
    }

    if (0 == ucRemainder)
    {
        return VOS_FALSE;
    }

    ucLeftMask = (VOS_UINT8)(((VOS_UINT32)1) << ucRemainder);
    ucLeftMask -= 1;
    ucLeftMask = (VOS_UINT8)(((VOS_UINT32)ucLeftMask) << (CNAS_HSM_BIT_LEN_PER_BYTE - ucRemainder));

    if ((pstUatiInfo->aucCurUATI[ucLoop] & ucLeftMask)
     != (pstHprdSysInfo->aucSectorId[ucLoop] & ucLeftMask))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
Function Name   :   CNAS_HSM_IsCardChanged
Description     :   Check card changed
Input parameters:   None
Outout parameters:  None
Return Value    :   None

Modify History  :
1)  Date           : 2015-06-08
    Author         : y00307564
    Modify content : Create
2)  Date           : 2015-10-12
    Author         : y00307564
    Modify content : DTS2015082403731�޸ģ������ж�ESN_MEID_ME��ppp an��Ȩ�û����ж��߼�
*****************************************************************************/
VOS_UINT8  CNAS_HSM_IsCardChanged(VOS_VOID)
{
    VOS_UINT8                                              *pucCardIccId         = VOS_NULL_PTR;
    VOS_UINT8                                              *pucLastIccId         = VOS_NULL_PTR;
    CNAS_HSM_HARDWARE_ID_INFO_STRU                         *pstCardHwid          = VOS_NULL_PTR;
    CNAS_HSM_HARDWARE_ID_INFO_STRU                         *pstLastHwid          = VOS_NULL_PTR;
    CNAS_HSM_CARD_STATUS_CHANGE_INFO_STRU                  *pstCardStatusChgInfo = VOS_NULL_PTR;
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstSrcAccessAuthInfo = VOS_NULL_PTR;
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstDstAccessAuthInfo = VOS_NULL_PTR;
    CNAS_HSM_STORE_ESN_MEID_RSLT_STRU                      *pstStoreEsnMeidRslt  = VOS_NULL_PTR;
    CNAS_CCB_ESNMEIDME_INFO_STRU                           *pstEsnMeidMeInfo     = VOS_NULL_PTR;
    VOS_UINT8                                               ucIccidChangedFlg;
    VOS_UINT8                                               ucHwIdChangedFlg;

    pucCardIccId         = CNAS_CCB_GetCardIccIdAddr();
    pucLastIccId         = CNAS_HSM_GetLastIccIdAddr();

    pstCardHwid          = CNAS_HSM_GetHardwareIdInfo();
    pstLastHwid          = CNAS_HSM_GetLastSessionHwidCtxAddr();

    pstSrcAccessAuthInfo = CNAS_CCB_GetHrpdAccesAuthInfoAddr();
    pstDstAccessAuthInfo = CNAS_HSM_GetLastHrpdAccessAuthInfoCtxAddr();
    pstStoreEsnMeidRslt  = CNAS_HSM_GetStoreEsnMeidRsltAddr();
    pstEsnMeidMeInfo     = CNAS_CCB_GetEsnMeidMeInfoAddr();

    ucIccidChangedFlg    = CNAS_HSM_IsIccidChanged(pucCardIccId, pucLastIccId);
    ucHwIdChangedFlg     = CNAS_HSM_IsHardwareIdChanged(pstCardHwid, pstLastHwid);
    pstCardStatusChgInfo = CNAS_HSM_GetCardStatusChangeInfoAddr();

    /* �������ICCID����hardwareid�ı䣬ֱ���˳���Ϊ���� */
    if ((VOS_TRUE == ucIccidChangedFlg)
     || (VOS_TRUE == ucHwIdChangedFlg))
    {
        return VOS_TRUE;
    }

    /* ��iccid��hardwareidδ�ı䣬�������³�����Ҫ�����ж�:
    *  1����1���ն�A�п�������session��ػ���Ȼ�󽫿�1�����ն�B���ٿ������Ҽ���session��ػ���
    *     �ٽ���1�����ն�A������----��Ҫ�����ж�ESN_MEID_ME
    *
    *  2����2��ǰ���ն�A��ʹ�ù���session����ɣ���1���ն�A�п�������session��ػ���
    *     Ȼ���ն��еĿ�1���ɿ�2�ٿ���----��Ҫ�����ж�NAI(hrpd ppp�����Ȩ�û���)*/

    /* �����жϴ��ڵĳ�����
    *  A���������ػ���������session����ɹ��������ػ��µ翪����������

    *  B���Ȳ�ο�A:ʹ�ÿ�A������session����ɹ����γ�A���ٲ��A����

    *  C��������ο�A��B: ʹ�ÿ�A������session����ɹ���ػ��µ磬�γ�A���ٲ���B����

    *  D���Ȳ�ο�A��B��ʹ�ÿ�A������session����ɹ����γ�A���ٲ���B

    *  E������ģʽ */
    if ((VOS_FALSE == pstCardStatusChgInfo->ucIsPreCardPresent) && (VOS_TRUE == pstCardStatusChgInfo->ucIsCurCardPresent))
    {
        /* �ж�ESN_MEID_ME�Ƿ�ı� */
        if (VOS_TRUE == CNAS_HSM_IsEsnMeidMeChanged(pstStoreEsnMeidRslt, pstEsnMeidMeInfo, pstLastHwid))
        {
            return VOS_TRUE;
        }

        /* �ж�PPP AN��Ȩ�����û����Ƿ�ı� */
        if (VOS_TRUE == CNAS_HSM_IsHrpdAccessAuthUserChanged(pstSrcAccessAuthInfo, pstDstAccessAuthInfo))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID CNAS_HSM_ProcSessionRetryAfterSessionDeact_L1Main(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
)
{
    VOS_UINT32                                              ulReasonCnt;
    VOS_UINT32                                              ulLoop;
    pCnasHsmSessionDeactReasonHdlrFunc                      pfuncHdlr = VOS_NULL_PTR;
    VOS_UINT8                                               ucIsSessionActTimerRun;
    CNAS_HSM_SESSION_DEACT_INFO_STRU                        stSeessionDeactInfo;

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        ucIsSessionActTimerRun = VOS_TRUE;
    }
    else
    {
        ucIsSessionActTimerRun = VOS_FALSE;
    }

    NAS_MEM_SET_S(&stSeessionDeactInfo, sizeof(stSeessionDeactInfo), 0, sizeof(CNAS_HSM_SESSION_DEACT_INFO_STRU));

    stSeessionDeactInfo.enSessionDeactReason          = enSessionDeactReason;
    stSeessionDeactInfo.ucSessionActTriedCntConnFail  = CNAS_HSM_GetSessionActTriedCntConnFail();
    stSeessionDeactInfo.ucSessionActTriedCntOtherFail = CNAS_HSM_GetSessionActTriedCntOtherFail();
    stSeessionDeactInfo.ucIsSessionActTimerRun        = ucIsSessionActTimerRun;
    stSeessionDeactInfo.ucSessionActMaxCntConnFail    = CNAS_HSM_GetSessionActMaxCntConnFail();
    stSeessionDeactInfo.ucSessionActMaxCntOtherFail   = CNAS_HSM_GetSessionActMaxCntOtherFail();
    stSeessionDeactInfo.ulSessionActTimerLen          = CNAS_HSM_GetSessionActTimerLen();
    stSeessionDeactInfo.enConvertedCasStatus          = CNAS_HSM_GetHrpdConvertedCasStatus();
    stSeessionDeactInfo.enCurrMainState               = CNAS_HSM_GetCurrMainState();

    CNAS_HSM_LogSessionDeactInfo(&stSeessionDeactInfo);

    /* �����Last session deactive reason���ڸ�ԭ��ֵ�������и�����Ҫ���� */
    CNAS_HSM_SetLatestSessionDeactReason(CNAS_HSM_SESSION_DEACT_REASON_BUTT);

    ulReasonCnt = sizeof(g_astHsmSessionDeactReasonProcTbl) /
                        sizeof(CNAS_HSM_SESSION_DEACT_REASON_PROC_TBL_STRU);

    for (ulLoop = 0; ulLoop < ulReasonCnt; ulLoop++)
    {
        if (enSessionDeactReason == g_astHsmSessionDeactReasonProcTbl[ulLoop].enSessionDeactReason)
        {
            pfuncHdlr = g_astHsmSessionDeactReasonProcTbl[ulLoop].pfuncSessionDeactReasonHdlr;

            break;
        }
    }

    if (VOS_NULL_PTR != pfuncHdlr)
    {
        pfuncHdlr();
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpNegFail(VOS_VOID)
{
    CNAS_HSM_IncreaseSessionActTriedCntOtherFail();

    CNAS_HSM_ResetSessionActTriedCntConnFail();

    /* ������Դ����ﵽ���������������� */
    if (CNAS_HSM_GetSessionActTriedCntOtherFail() >= CNAS_HSM_GetSessionActMaxCntOtherFail())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* �����ʱ����ʱ���������� */
    else if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: ����Ǵ�ģ״̬��ֹͣ���� */
    else if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: �������������ֹͣ���� */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��ʼ���� */
    else
    {
        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpAnExp(VOS_VOID)
{
    /* ������Զ�ʱ����ʱ���������� */
    if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: ����Ǵ�ģ״̬��ֹͣ���� */
    else if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: �������������ֹͣ���� */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��ʼ���� */
    else
    {
        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpConnOpenFail(VOS_VOID)
{
    CNAS_HSM_IncreaseSessionActTriedCntConnFail();

    /* ������Դ����ﵽ���������������� */
    if (CNAS_HSM_GetSessionActTriedCntConnFail() >= CNAS_HSM_GetSessionActMaxCntConnFail())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_TIMEOUT,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* �����ʱ����ʱ���������� */
    else if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_TIMEOUT,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: ����Ǵ�ģ״̬��ֹͣ���� */
    else if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: �������������ֹͣ���� */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��ʼ���� */
    else
    {
        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpConnOpenDenyImplicitlyRej(VOS_VOID)
{
    HSM_HSD_SESSION_NEG_RSLT_ENUM_UINT8                     enSessionNegRlt;

    enSessionNegRlt = HSM_HSD_SESSION_NEG_RSLT_TIMEOUT;

    /***************************************************************************************************************
        �����Э�̣��ִ��һ�½���:
        1:�����յ�5����ͬ��denyԭ��ֵ(general),����CDG143 5.8���е��������ò���ʽ�Ĺ�ܷ�ʽ��
        2:�����յ�5����ͬ��denyԭ��ֵ(NW busy),����CDG143 5.8���е��������ò���ʽ�Ĺ�ܷ�ʽ��
        3:�����յ�5����ͬ��denyԭ��ֵ(Preferred channel not available),����CDG143 5.8���е��������ò���ʽ�Ĺ�ܷ�ʽ��
        4:�����յ�5����ͬ��denyԭ��ֵ(authentication billing),����CDG143 5.8���е��������10���ӣ�
        5:Ϊ�˱���deny��ԭ��ֵ�������(����general��authentication)����������ѭ������ʹ���ܼ�ʱ�������Ƶ�㣬BalongĿǰ��
          ���������5������һ�ε�denyԭ��ֵΪauthentication billing��ֱ�ӹ��10���ӡ�
    ******************************************************************************************************************/

    if (VOS_TRUE == CNAS_HSM_GetExplicitlyConnDenyFlg())
    {
        enSessionNegRlt = HSM_HSD_SESSION_NEG_RSLT_FAIL;
    }

    CNAS_HSM_IncreaseSessionActTriedCntConnFail();

    /* ������Դ����ﵽ���������������� */
    if (CNAS_HSM_GetSessionActTriedCntConnFail() >= CNAS_HSM_GetSessionActMaxCntConnFail())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(enSessionNegRlt,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* �����ʱ����ʱ���������� */
    else if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(enSessionNegRlt,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: ����Ǵ�ģ״̬��ֹͣ���� */
    else if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: �������������ֹͣ���� */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��ʼ���� */
    else
    {
        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpConnOpenDenyExplicitlyRej(VOS_VOID)
{
    CNAS_HSM_IncreaseSessionActTriedCntConnFail();

    CNAS_HSM_SetExplicitlyConnDenyFlg(VOS_TRUE);

    /* ������Դ����ﵽ���������������� */
    if (CNAS_HSM_GetSessionActTriedCntConnFail() >= CNAS_HSM_GetSessionActMaxCntConnFail())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* �����ʱ����ʱ���������� */
    else if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: ����Ǵ�ģ״̬��ֹͣ���� */
    else if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: �������������ֹͣ���� */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��ʼ���� */
    else
    {
        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpPersInvalid(VOS_VOID)
{
    CNAS_HSM_IncreaseSessionActTriedCntOtherFail();

    CNAS_HSM_ResetSessionActTriedCntConnFail();

    /* ������Դ����ﵽ���������������� */
    if (CNAS_HSM_GetSessionActTriedCntOtherFail() >= CNAS_HSM_GetSessionActMaxCntOtherFail())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* �����ʱ����ʱ���������� */
    else if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: ����Ǵ�ģ״̬��ֹͣ���� */
    else if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: �������������ֹͣ���� */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��ʼ���� */
    else
    {
        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpCfgRspExp(VOS_VOID)
{
    /* �����ʱ����ʱ���������� */
    if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: ����Ǵ�ģ״̬��ֹͣ���� */
    else if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: �������������ֹͣ���� */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��ʼ���� */
    else
    {
        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpCfgMsgFail(VOS_VOID)
{
    /* �����ʱ����ʱ���������� */
    if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: ����Ǵ�ģ״̬��ֹͣ���� */
    else if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: �������������ֹͣ���� */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��ʼ���� */
    else
    {
        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpAnGaupFail(VOS_VOID)
{
    CNAS_HSM_IncreaseSessionActTriedCntOtherFail();

    CNAS_HSM_ResetSessionActTriedCntConnFail();

    /* ������Դ����ﵽ���������������� */
    if (CNAS_HSM_GetSessionActTriedCntOtherFail() >= CNAS_HSM_GetSessionActMaxCntOtherFail())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* �����ʱ����ʱ���������� */
    else if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: ����Ǵ�ģ״̬��ֹͣ���� */
    else if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: �������������ֹͣ���� */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��ʼ���� */
    else
    {
        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpIratToLte(VOS_VOID)
{
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                       VOS_FALSE,
                                       CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonScpNoRf(VOS_VOID)
{
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                       VOS_FALSE,
                                       CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonNetworkLostInSessionAct(VOS_VOID)
{
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                       VOS_FALSE,
                                       CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonWaitScpCnfExp(VOS_VOID)
{
    CNAS_HSM_IncreaseSessionActTriedCntOtherFail();

    CNAS_HSM_ResetSessionActTriedCntConnFail();

    /* ������Դ����ﵽ���������������� */
    if (CNAS_HSM_GetSessionActTriedCntOtherFail() >= CNAS_HSM_GetSessionActMaxCntOtherFail())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* �����ʱ����ʱ���������� */
    else if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: ����Ǵ�ģ״̬��ֹͣ���� */
    else if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: �������������ֹͣ���� */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��ʼ���� */
    else
    {
        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonSessionActAbortByAnCloseSession(VOS_VOID)
{
    CNAS_HSM_IncreaseSessionActTriedCntOtherFail();

    CNAS_HSM_ResetSessionActTriedCntConnFail();

    /* ������Դ����ﵽ���������������� */
    if (CNAS_HSM_GetSessionActTriedCntOtherFail() >= CNAS_HSM_GetSessionActMaxCntOtherFail())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* �����ʱ����ʱ���������� */
    else if (CNAS_TIMER_STATUS_STOP == CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSM,
                                            TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER, 0))
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: ����Ǵ�ģ״̬��ֹͣ���� */
    else if (CNAS_HSM_L1_STA_SLAVE == CNAS_HSM_GetCurrMainState())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��������: �������������ֹͣ���� */
    else if (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == CNAS_HSM_GetHrpdConvertedCasStatus())
    {
        CNAS_HSM_ResetSessionRetryParameters();

        CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                           VOS_FALSE,
                                           CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
    }
    /* ��ʼ���� */
    else
    {
        CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

        CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

        CNAS_HSM_EnterSetupStateProc_L1Main();

        CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
    }
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonAmpFailUatiReachMaxCnt(VOS_VOID)
{
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_FAIL,
                                       VOS_FALSE,
                                       CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonAmpFailSysAcqSubnetChange(VOS_VOID)
{
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;

    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                       VOS_FALSE,
                                       CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);

    enMainState          = CNAS_HSM_GetCurrMainState();

    enConvertedCasStatus = CNAS_HSM_GetHrpdConvertedCasStatus();

    /* ��������: ����Ǵ�ģ״̬�����������������sessionЭ�� */
    if ((CNAS_HSM_L1_STA_SLAVE              == enMainState)
     || (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enConvertedCasStatus))
    {
        return;
    }

    /* ����sessionЭ�� */
    /* ����session deaciveԭ��ֵ��
     * ע��:����CNAS_HSM_RcvInterSessionActiveReq_SessionAct_Init()��ʹ�ã����������ط�ʹ��
     */
    CNAS_HSM_SetLatestSessionDeactReason(
                          CNAS_HSM_SESSION_DEACT_REASON_AMP_FAIL_SYS_ACQ_SUBNET_CHANGE);

    CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                        CNAS_HSM_GetSessionActTimerLen());

    CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

    CNAS_HSM_EnterSetupStateProc_L1Main();

    CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonAmpFailOtherScene(VOS_VOID)
{
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;

    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                       VOS_FALSE,
                                       CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);

    enMainState          = CNAS_HSM_GetCurrMainState();

    enConvertedCasStatus = CNAS_HSM_GetHrpdConvertedCasStatus();

    /* ��������: ����Ǵ�ģ״̬�����������������sessionЭ�� */
    if ((CNAS_HSM_L1_STA_SLAVE              == enMainState)
     || (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enConvertedCasStatus))
    {
        return;
    }

    /* ����sessionЭ�� */
    CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                        CNAS_HSM_GetSessionActTimerLen());

    CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

    CNAS_HSM_EnterSetupStateProc_L1Main();

    CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonAnCloseSessionInVacant(VOS_VOID)
{
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;

    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                       VOS_FALSE,
                                       CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);

    enMainState          = CNAS_HSM_GetCurrMainState();

    enConvertedCasStatus = CNAS_HSM_GetHrpdConvertedCasStatus();

    /* ��������: ����Ǵ�ģ״̬�����������������sessionЭ�� */
    if ((CNAS_HSM_L1_STA_SLAVE              == enMainState)
     || (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enConvertedCasStatus))
    {
        return;
    }

    /* ����sessionЭ�� */
    CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                        CNAS_HSM_GetSessionActTimerLen());

    CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

    CNAS_HSM_EnterSetupStateProc_L1Main();

    CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonKeepAliveExpOpen(VOS_VOID)
{
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;

    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                       VOS_FALSE,
                                       CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);

    enMainState          = CNAS_HSM_GetCurrMainState();

    enConvertedCasStatus = CNAS_HSM_GetHrpdConvertedCasStatus();

    /* ��������: ����Ǵ�ģ״̬�����������������sessionЭ�� */
    if ((CNAS_HSM_L1_STA_SLAVE              == enMainState)
     || (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enConvertedCasStatus))
    {
        return;
    }

    /* ����sessionЭ�� */
    CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                        CNAS_HSM_GetSessionActTimerLen());

    CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

    CNAS_HSM_EnterSetupStateProc_L1Main();

    CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonInternalSessionCloseSalve(VOS_VOID)
{
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                       VOS_FALSE,
                                       CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonEhrpdToHrpd(VOS_VOID)
{
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;
    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                       VOS_FALSE,
                                       CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);

    enMainState          = CNAS_HSM_GetCurrMainState();

    enConvertedCasStatus = CNAS_HSM_GetHrpdConvertedCasStatus();

    /* ��������: ����Ǵ�ģ״̬�����������������sessionЭ�� */
    if ((CNAS_HSM_L1_STA_SLAVE              == enMainState)
     || (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enConvertedCasStatus))
    {
        return;
    }

    /* ����sessionЭ�� */
    /* ����session deaciveԭ��ֵ
     * ע��:����CNAS_HSM_RcvInterSessionActiveReq_SessionAct_Init()��ʹ�ã����������ط�ʹ��
     */
    CNAS_HSM_SetLatestSessionDeactReason(CNAS_HSM_SESSION_DEACT_REASON_EHRPD_TO_HRPD);

    CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                        CNAS_HSM_GetSessionActTimerLen());

    CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

    CNAS_HSM_EnterSetupStateProc_L1Main();

    CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonHrpdToEhrpd(VOS_VOID)
{
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;

    CNAS_HSM_ResetSessionRetryParameters();

    CNAS_HSM_SndHsdSessionNegResultInd(HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE,
                                       VOS_FALSE,
                                       CNAS_HSM_SESSION_RELEASE_TYPE_BUTT);

    enMainState          = CNAS_HSM_GetCurrMainState();

    enConvertedCasStatus = CNAS_HSM_GetHrpdConvertedCasStatus();

    /* ��������: ����Ǵ�ģ״̬�����������������sessionЭ�� */
    if ((CNAS_HSM_L1_STA_SLAVE              == enMainState)
     || (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enConvertedCasStatus))
    {
        return;
    }

    /* ����sessionЭ�� */
    CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                        CNAS_HSM_GetSessionActTimerLen());

    CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

    CNAS_HSM_EnterSetupStateProc_L1Main();

    CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
}


VOS_VOID CNAS_HSM_ProcSessionRetryDeactReasonSessionActAbortByOhm(VOS_VOID)
{
    CNAS_HSM_L1_STA_ENUM_UINT32                             enMainState;
    CNAS_HSM_HRPD_CAS_STATUS_ENUM_UINT16                    enConvertedCasStatus;

    CNAS_HSM_ResetSessionRetryParameters();

    enMainState          = CNAS_HSM_GetCurrMainState();

    enConvertedCasStatus = CNAS_HSM_GetHrpdConvertedCasStatus();

    /* ��������: ����Ǵ�ģ״̬�����������������sessionЭ�� */
    if ((CNAS_HSM_L1_STA_SLAVE              == enMainState)
     || (CNAS_HSM_HRPD_CAS_STATUS_ENUM_INIT == enConvertedCasStatus))
    {
        return;
    }

    /* ����sessionЭ�� */
    CNAS_HSM_StartTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER,
                        CNAS_HSM_GetSessionActTimerLen());

    CNAS_HSM_SetSessionNegOngoingFlag(VOS_TRUE);

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_SETUP);

    CNAS_HSM_EnterSetupStateProc_L1Main();

    CNAS_HSM_StartUATIRequestProcedure_L1Main(CNAS_HSM_UATI_REQ_TRIGGER_BY_AT);
}


VOS_VOID CNAS_HSM_ResetSessionRetryParameters(VOS_VOID)
{
    CNAS_HSM_ResetSessionActTriedCntConnFail();
    CNAS_HSM_ResetSessionActTriedCntOtherFail();

    CNAS_HSM_SetExplicitlyConnDenyFlg(VOS_FALSE);

    CNAS_HSM_StopTimer(TI_CNAS_HSM_UATI_AND_SESSION_ACT_PROTECT_TIMER);

    CNAS_HSM_SetLatestSessionDeactReason(CNAS_HSM_SESSION_DEACT_REASON_BUTT);

    CNAS_HSM_SetReqSessionTypeForRetry(CNAS_HSM_SESSION_TYPE_BUTT);
}


CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8
CNAS_HSM_ConvertUaitFailReasonToSessionDeactReason(
    CNAS_HSM_UATI_REQUEST_FAIL_REASON_ENUM_UINT8            enUatiFailReason
)
{
    VOS_UINT32                                              ulReasonCnt;
    VOS_UINT32                                              ulLoop;

    ulReasonCnt = sizeof(g_astHsmUatiFailReasonMapSessionDeactReasonTbl) /
                            sizeof(CNAS_HSM_UATI_FAIL_REASON_MAP_SESSION_DEACTVE_REASON_STRU);

    for (ulLoop = 0; ulLoop < ulReasonCnt; ulLoop++)
    {
        if (g_astHsmUatiFailReasonMapSessionDeactReasonTbl[ulLoop].enUatiFailReason
                                                                         == enUatiFailReason)
        {
            return g_astHsmUatiFailReasonMapSessionDeactReasonTbl[ulLoop].enSessionDeactReason;
        }
    }

    return CNAS_HSM_SESSION_DEACT_REASON_BUTT;
}


CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8
CNAS_HSM_ConvertSessionActFailReasonToSessionDeactReason(
    CNAS_HSM_SESSION_ACT_FAIL_REASON_ENUM_UINT8             enSessionActFailReason
)
{
    VOS_UINT32                                              ulReasonCnt;
    VOS_UINT32                                              ulLoop;

    ulReasonCnt = sizeof(g_astHsmSessionActFailReasonMapSessionDeactReasonTbl) /
                            sizeof(CNAS_HSM_SESSION_ACT_FAIL_REASON_MAP_SESSION_DEACT_REASON_STRU);

    for (ulLoop = 0; ulLoop < ulReasonCnt; ulLoop++)
    {
        if (g_astHsmSessionActFailReasonMapSessionDeactReasonTbl[ulLoop].enSessionActFailReason
                                                                         == enSessionActFailReason)
        {
            return g_astHsmSessionActFailReasonMapSessionDeactReasonTbl[ulLoop].enSessionDeactReason;
        }
    }

    return CNAS_HSM_SESSION_DEACT_REASON_BUTT;
}


VOS_UINT8 CNAS_HSM_IsSessionDeactReasonAbort(
    CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8                enSessionDeactReason
)
{
    VOS_UINT32                                              ulReasonCnt;
    VOS_UINT32                                              ulLoop;

    ulReasonCnt = sizeof(g_astHsmSessionDeactiveReasonAbortList) /
                            sizeof(CNAS_HSM_SESSION_DEACT_REASON_ENUM_UINT8);

    for (ulLoop = 0; ulLoop < ulReasonCnt; ulLoop++)
    {
        if (g_astHsmSessionDeactiveReasonAbortList[ulLoop] == enSessionDeactReason)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID CNAS_HSM_StartConnMnmtProcedure_L1Main(
    CNAS_HSM_CONN_MNMT_TRIGGER_ENUM_UINT8           enTriggerScene
)
{
    CNAS_HSM_SetCurrSubState(CNAS_HSM_SS_CONN_MNMT_INIT);

    CNAS_HSM_SndInternalConnMnmtReq(enTriggerScene);
}




VOS_VOID CNAS_HSM_ProcMsgForFirstSysAcq_L1Main(VOS_VOID)
{
    VOS_UINT32                          ulSessionSeed;
    VOS_UINT32                         *pulLastReceivedSysTime = VOS_NULL_PTR;
    VOS_UINT32                         *pulLastPowerOffSysTime = VOS_NULL_PTR;
    VOS_UINT8                           ucNeedSessionRecovery;

    /* Set the First Sys acq flag to FALSE */
    CNAS_HSM_SetFirstSysAcqFlag(VOS_FALSE);

    /* Save the Sys_time at the time of last power off */
    pulLastPowerOffSysTime = CNAS_HSM_GetLastPowerOffSysTime();

    /* Get the latest CDMA Sys time received in Sys acq ind or Sys time ind message*/
    pulLastReceivedSysTime = CNAS_HSM_GetLastReceivedSysTime();

    ucNeedSessionRecovery = CNAS_HSM_IsNeedSessionRecovery(pulLastReceivedSysTime, pulLastPowerOffSysTime);

    if (VOS_TRUE == ucNeedSessionRecovery)
    {
        /* Here, the CNAS_HSM_GetTsmpClose() returns the TsmpClose that was stored in the NV. */
        if (0 != CNAS_HSM_GetTsmpClose())
        {
            /* HSM will calculate the Time remaining for TsmpCLose to expire, and save to global variable. HSM
               will subtract the time interval since last power Off */
            CNAS_HSM_CalcTsmpCloseRemainTimeAfterFirstSysAcq(pulLastReceivedSysTime, pulLastPowerOffSysTime);
        }

        /* recover flow,simliar as open state receive acquire ind message,so set this value */
        CNAS_HSM_SetRcvOhmScene(CNAS_HSM_RCV_OHM_SCENE_FOLLOW_SYS_ACQ);

        /* Send Session Recover request to CAS.  Start the Session active procedure */
        CNAS_HSM_StartSessionActiveProcedure_L1Main(CNAS_HSM_SESSION_ACTIVE_REASON_RECOVERY);

        return;
    }

    /* If it is the first sys acq and session need not be recovered, Generate the initial session seed and
    update the session seed in the global variable. */
    ulSessionSeed = CNAS_HSM_GenerateInitSessionSeed();
    CNAS_HSM_SetSessionSeed(ulSessionSeed);

    //��ά�ɲ���Ϣ
    CNAS_HSM_UpdateHrpdAtiInfo();

    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_INACTIVE);

    /* Perform The enter Inactive state procedure  */
    CNAS_HSM_EnterInactiveStateProc_L1Main();

    return ;
}

/*****************************************************************************
Function Name   :  CNAS_HSM_ProcSessionRecoverySucc_L1Main
Description     :  The function is used to proc session recovery succ in inactive or slave state.
Input parameters:  VOS_VOID
Outout parameters: VOS_VOID
Return Value    :  VOS_VOID


Modify History  :
1)  Date           : 2015-06-25
    Author         : w00176964
    Modify content : Create
2)  Date           : 2015-09-18
    Author         : m00312079
    Modify content : DTS2015091604029:���ָ����session seed�·���CAS
*****************************************************************************/

VOS_VOID CNAS_HSM_ProcSessionRecoverySucc_L1Main(VOS_VOID)
{
    CNAS_HSM_ATI_RECORD_STRU           *pstPubTransATI;
    CNAS_HSM_ATI_LIST_INFO_STRU        *pstPubRcvATIList;
    CNAS_HSM_UATI_INFO_STRU            *pstCurUatiInfo;
    VOS_UINT32                          ulSessionSeed;
    VOS_UINT8                           i;

    CNAS_HSM_SetSessionStatus(CNAS_HSM_SESSION_STATUS_OPEN);

    /* ��ά�ɲ���Ϣ */
    CNAS_HSM_UpdateHrpdAtiInfo();

    /* HSM will enter the Open state if the PowerSave Flag and Suspend flags are FALSE */
    CNAS_HSM_SetCurrMainState(CNAS_HSM_L1_STA_OPEN);

    /* Initialize the variable which records the system tick when AT receives forward traffic chan data */
    CNAS_HSM_SetSysTickFwdTrafficChan(CNAS_HSM_GetSysTick());

    /* HSM will register the callback function that will update the Sys tick at which forward traffic chan data
    is received */
    CTTF_HRPD_FSPS_RegTrafficFlowMonitor(CNAS_HSM_ProcTrafficFlowOnForwardChannel);

    /*  HSM will start the Keep Alive TImer */
    CNAS_HSM_ProcKeepAliveTimer(CNAS_HSM_KEEP_ALIVE_SCENE_SESSION_RECOVERED);

    /* send session seed */
    ulSessionSeed = CNAS_HSM_GetSessionSeed();


    CNAS_HSM_SndCasHrpdSessionSeedNtf(ulSessionSeed);

    /* send transmit ati */
    pstPubTransATI   = CNAS_HSM_GetTransmitATIAddr();

    pstPubTransATI->enATIType = CNAS_HSM_ATI_TYPE_UATI;

    pstCurUatiInfo = CNAS_HSM_GetUatiInfoAddr();

    pstPubTransATI->aucATIValue[0] = pstCurUatiInfo->ucUATIColorCode;

    NAS_MEM_CPY_S(&(pstPubTransATI->aucATIValue[1]),
                  sizeof(pstPubTransATI->aucATIValue) - 1,
                  pstCurUatiInfo->aucCurUATI + CNAS_HSM_UATI104_OCTET_LENGTH,
                  CNAS_HSM_UATI024_OCTET_LENGTH);

    CNAS_HSM_SndMacTransmitAtiNotify(pstPubTransATI);

    /* send receive ati list */
    pstPubRcvATIList = CNAS_HSM_GetReceivedATIListAddr();

    CNAS_HSM_InitATIList(pstPubRcvATIList);

    /* add one entry to the receive ATI list */
    pstPubRcvATIList->ulATIRecordNum = 2;
    pstPubRcvATIList->astATIEntry[0].enATIType = CNAS_HSM_ATI_TYPE_BATI;

    for (i = 0; i < CNAS_HSM_ATI_VALUE_LENGTH; i++)
    {
        pstPubRcvATIList->astATIEntry[0].aucATIValue[i] = CNAS_HSM_INVALID_ATI_VALUE;
    }

    pstPubRcvATIList->astATIEntry[1].enATIType  = CNAS_HSM_ATI_TYPE_UATI;

    pstPubRcvATIList->astATIEntry[1].aucATIValue[0] = pstCurUatiInfo->ucUATIColorCode;

    NAS_MEM_CPY_S(&(pstPubRcvATIList->astATIEntry[1].aucATIValue[1]),
                  sizeof(pstPubRcvATIList->astATIEntry[1].aucATIValue) - 1,
                  pstCurUatiInfo->aucCurUATI + CNAS_HSM_UATI104_OCTET_LENGTH,
                  CNAS_HSM_UATI024_OCTET_LENGTH);

    CNAS_HSM_SndMacReceiveAtiNotify(pstPubRcvATIList);

    return ;
}



#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


