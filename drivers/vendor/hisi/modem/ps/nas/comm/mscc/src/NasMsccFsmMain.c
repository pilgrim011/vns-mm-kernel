


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "NasMsccFsmMain.h"
#include "NasMsccFsmMainTbl.h"
#include "NasMsccCtx.h"
#include "NasMsccSndInternalMsg.h"
#include "NasMsccTimerMgmt.h"
#include "NasMsccSndMma.h"
#include "PsLogdef.h"
#include "NasMsccSndXsd.h"
#include "NasMsccSndHsd.h"
#include "NasMsccSndMmc.h"
#include "NasComm.h"
#include "NasMsccComFunc.h"
#include "NasMsccMlplMsplApi.h"
#include "NasMsccProcNvim.h"
#include "NasMsccFsmSysCfg.h"

#include "NasMsccSndRrm.h"
#include "NasUtranCtrlInterface.h"
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "NasDynLoadApi.h"
#include "NasDynLoad.h"
#endif

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_FSM_MAIN_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef DMT
    VOS_UINT32 g_ulDisableAutoSysAcq;
#endif
/*****************************************************************************
  3 ��������
*****************************************************************************/






VOS_UINT32 NAS_MSCC_RcvMmaStartReq_Main_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ReadNvim();

    /* Start the Switch ON FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_SWITCH_ON);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccStartCnf_Main_Null
Description     :   The function receives the Internal message from Switch On FSM. IF Start result is success,
                    Success result is sent to MSCC. If start result is not success, fail result is sent to MMA.

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2014-01-31
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-08-20
        Author  :   w00242748
        Modify content : ��̬������Ŀ
*****************************************************************************/

VOS_UINT32 NAS_MSCC_RcvMsccStartCnf_Main_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU                  *pstSwitchOnRslt;

    pstSwitchOnRslt                     = (NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU *)pstMsg;

    if (NAS_MSCC_SWITCH_ON_RESULT_SUCCESS == pstSwitchOnRslt->enRslt)
    {
        /* Send Switch On Cnf with Success result to MMA */
        NAS_MSCC_SndMmaSwitchOnRsltCnf(NAS_MSCC_PIF_START_RESULT_SUCC);

        /* Set next state to Deactive */
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_DEACTIVE);

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        /* �����ϱ���ǰ����CL mode����GUL mode */
        NAS_MSCC_SndRrmRatCombModeInd();
#endif

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        /* ��̬����ֻ����TDD/FDDͬʱ����ʱ�������壬�������֧�ֵĻ�����̬���ؾ�û������ */
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            NAS_MSCC_ProcDynamicLoadAfterStartCnf_Main();
        }
#endif

    }
    else
    {
        /* ����ʧ�ܺ�mma�����mscc���͹ػ�����, mscc��Ҫ�ڴ����mspl/mlpl����������ڴ� */
        NAS_MSCC_InitCtx(NAS_MSCC_INIT_CTX_POWEROFF);

        /* Send Switch On Cnf with Fail result to MMA */
        NAS_MSCC_SndMmaSwitchOnRsltCnf(NAS_MSCC_PIF_START_RESULT_FAIL);

        NAS_TRACE_HIGH("NAS_MSCC_RcvMsccStartCnf_Main_Null: Switch ON result Failed!");
    }

    return VOS_TRUE;

}



VOS_UINT32 NAS_MSCC_RcvMmaStartReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_NORMAL_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvMmaStartReq_Main_Deactive: Directly respond with START CNF msg");
    NAS_TRACE_HIGH("NAS_MSCC_RcvMmaStartReq_Main_Deactive: Directly respond with START CNF msg");
    /* Send Switch On Cnf with Success result to MMA */
    NAS_MSCC_SndMmaSwitchOnRsltCnf(NAS_MSCC_PIF_START_RESULT_SUCC);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvMmaPowerOffReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Start the Power Off FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_POWER_OFF);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmaSysAcquireReq_Main_Deactive
Description     :   The function receives the System Acquire request from MMA.
                    Send system acquire request all enabled modules.
                    Change the current state to NAS_MSCC_L1_STA_ACTIVE

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2014-01-31
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-04-08
        Author  :   m00312079
        Modify content :    add the logic for CL system acquire
    3)  ��    ��   : 2015��6��19��
        ��    ��   : s00217060
        �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
*****************************************************************************/

VOS_UINT32 NAS_MSCC_RcvMmaSysAcquireReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#ifdef DMT
    if (VOS_TRUE == g_ulDisableAutoSysAcq)
    {
        /* For ST testing purpose: Test sys cfg handling in DEACTIVE state */
        return VOS_TRUE;
    }
#endif

    NAS_MSCC_PerformSystemAcquireUponPowerOn_Main(pstMsg);

    return VOS_TRUE;
}




VOS_UINT32 NAS_MSCC_RcvMsccPowerOffCnf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU                      *pstPowerOffRslt;

    pstPowerOffRslt = (NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU *)pstMsg;

    NAS_MSCC_ProcPowerOffResult_Main(pstPowerOffRslt->enRslt);

    return VOS_TRUE;

}



VOS_UINT32 NAS_MSCC_RcvMmaPowerOffReq_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Start the Power OFF FSM  */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_POWER_OFF);

    return VOS_TRUE;

}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_UINT32 NAS_MSCC_RcvHsdSysAcqInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU                   *pstHsdSysAcqInd = VOS_NULL_PTR;
    VOS_UINT8                                               ucSimPsRegStatus;

    pstHsdSysAcqInd                     = (HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU *)pstMsg;






    /* only failure situation should be dealt with, success situcation will be
        left for session negotiation */
    if (NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC != pstHsdSysAcqInd->enRslt)
    {
        ucSimPsRegStatus = NAS_MSCC_GetSimPsRegStatus();

        NAS_MSCC_SndMmaHrpdServiceStatusInd(MSCC_MMA_HRPD_SERVICE_STATUS_NO_SERVICE,
                                            VOS_FALSE,
                                            VOS_FALSE,
                                            MSCC_MMA_SESSION_RELEASE_TYPE_BUTT);

        /* ��MMA�ϱ��޷��񣬺�MMA���ַ���״̬һ�£��˴�Ҳ�����޷��� */
        NAS_MSCC_SetCurrHrpdServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);

        if ((VOS_TRUE  == NAS_MSCC_IsNeedPerformCLSysAcq())
         && (VOS_TRUE  == ucSimPsRegStatus))
        {
            NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST));

            return VOS_TRUE;
        }
    }

    /* ��������ɹ���ʧ���ϱ�mma_sys_end_ind��������ϡ�NO_RF���ϱ� */
    /* �����֧��LTE,��ΪHRPD�����Ĳ�������;֪ͨ����ʼ��ϵͳģʽΪDO */
    if ((NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC == pstHsdSysAcqInd->enRslt)
      || (NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL == pstHsdSysAcqInd->enRslt))
    {
        if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
        {
            NAS_MSCC_SndMmaSystemAcquireEndInd(NAS_MSCC_GetSystemAcquireFinalResult(pstHsdSysAcqInd->enRslt),
                                               MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                               MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);
        }
        else
        {
            NAS_MSCC_SndMmaSystemAcquireEndInd(NAS_MSCC_GetSystemAcquireFinalResult(pstHsdSysAcqInd->enRslt),
                                               MSCC_MMA_ACQ_SYS_TYPE_DO,
                                               MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);
        }
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvInternalSysAcqReq_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_DO_LTE);

    /* ����L2 System Acquire״̬�� */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_SYS_ACQ);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmcRegRejPlmnSeleInd_Main_Active
Description     :   process ID_MMC_MSCC_REG_REJ_PLMN_SELE_IND message

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
    2)  Date    :   2016-01-18
        Author  :   w00176964
        Modify content :DTS2016011802320����
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcMmssLteUnavailableInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU                 *pstLteUnavailInd;
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;

    pstLteUnavailInd = (MMC_MSCC_MMSS_LTE_UNAVAILABLE_IND_STRU *)pstMsg;

    /* LTE���ڴ�ģ,������available��ʱ����ʱ��L,��������Ϣ */
    if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
    {
        return VOS_TRUE;
    }

    /* SYSCFG������detach����Ҫ������DO��SYSCFG������ɺ�ᴥ������ */
    if ((MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_BUTT               == pstLteUnavailInd->enReason)
     || (MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_RAT_OR_BAND_DETACH == pstLteUnavailInd->enReason))
    {
        return VOS_TRUE;
    }

    /* ��������������ֱ���˳� */
    if (VOS_FALSE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        return VOS_TRUE;
    }

    /* ע�ᱻ�ܿ���Ч��detach PS���NO RF����,��������������LTE */
    if ((VOS_FALSE                                             == NAS_MSCC_GetSimPsRegStatus())
     || (MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_USER_DETACH       == pstLteUnavailInd->enReason)
     || (MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_SRV_DOMAIN_DETACH == pstLteUnavailInd->enReason)
     || (MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_NO_RF             == pstLteUnavailInd->enReason))
    {
        enSysAcqScene = NAS_MSCC_SYS_ACQ_SCENE_LTE_NOT_AVAILABLE;
    }
    /* ע�ᱻ�ܻ�������,������������LTE��ģ������������,������һ��DO���ٳ���LTE */
    else
    {
        enSysAcqScene = NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST;
    }

    NAS_MSCC_SndInternalSysAcqReq(enSysAcqScene, NAS_MSCC_GetSysAcqLteSrchType_L1Main(enSysAcqScene));

    return VOS_TRUE;
}


VOS_VOID NAS_MSCC_ProcBsrFailureRslt_Main_Active(
    NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU    *pstBsrSearchRsltCnf
)
{
    VOS_UINT8                           uc3gppActiveFlg;

    if (NAS_MSCC_BSR_NEED_ACQ_SYS == pstBsrSearchRsltCnf->enIsNeedAcqSys)
    {
        uc3gppActiveFlg = NAS_MSCC_Get3gppActiveFlg();

        if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
        {
            /* BG�����л�LTEʱ���ע�ᱻ�ܿ���Ч,��Ҫͨ�����������е�HRPD��ȥ */
            if (VOS_TRUE == uc3gppActiveFlg)
            {
                NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST));

                return;
            }

            /* LTE��PSע�ᱻ�ܿ���Ч����HRPD��,������HSD��ѡ����ʱ������������;���ﲻ������ */
            if ((VOS_TRUE  == NAS_MSCC_GetSimPsRegStatus())
             && (VOS_FALSE == uc3gppActiveFlg))
            {
                NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST));

                return;
            }
        }
    }
    else
    {
        if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
        {
            /* ��ȻĿǰBSRʧ�ܳ���������������Retry Timer��ʶ, ��Ȼ�ȱ�����if��֧ */
            if (NAS_MSCC_BSR_NEED_START_RETRY_TIMER == pstBsrSearchRsltCnf->enIsNeedStartRetryTimer)
            {
                (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
                                             TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH_LEN);
            }
            else
            {
                NAS_MSCC_StartBsrTimer();
            }
        }
    }

    return;
}


VOS_UINT32 NAS_MSCC_RcvInternalBsrRsltCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU    *pstBsrSearchRsltCnf = VOS_NULL_PTR;

    pstBsrSearchRsltCnf = (NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU *)pstMsg;

    switch (pstBsrSearchRsltCnf->enRslt)
    {
        /* BSRפ���������ȼ���ʽ�ɹ� */
        case NAS_MSCC_BSR_RESULT_SUCCESS:
        case NAS_MSCC_BSR_RESULT_L2C:

            if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
            {
                NAS_MSCC_StartBsrTimer();
            }

            break;

        case NAS_MSCC_BSR_RESULT_FAILURE:

            NAS_MSCC_ProcBsrFailureRslt_Main_Active(pstBsrSearchRsltCnf);

            break;

        case NAS_MSCC_BSR_RESULT_ABORT:

            /* ��Ȼ��������Ҫ����BSR Retry Timer��ǣ��������������������BSR��ʱ��������������Retry��ʱ�� */
            if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
            {
                if (NAS_MSCC_BSR_NEED_START_RETRY_TIMER == pstBsrSearchRsltCnf->enIsNeedStartRetryTimer)
                {
                    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
                                                  TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH_LEN);
                }
                else
                {
                    NAS_MSCC_StartBsrTimer();
                }
            }

            break;

        default:

            NAS_WARNING_LOG(UEPS_PID_MSCC, "BSR FSM return result is except");

            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiBsrTimerExpired_Main_Active
Description     :   process the BSR Timer Expiry message

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - Pointer to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-07
        Author  :   t00323010
        Modify content :    Create for Iteration 10
    2)  Date    :   2015-06-11
        Author  :   W00176964
        Modify content : CDMA Iteration 12 Modified
    3)  Date    :   2015-12-15
        Author  :   W00176964
        Modify content : CL_MUTIMODE_OPTIMIZE����:BSR����ָ�����߼�ɾ��
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiBsrTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{


    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiPeriodTryingHighPrioNetworkSearchExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_ProcInterSysAcqSucc_Main
 ��������  : MAIN�ϴ����ڲ�ϵͳ����ɹ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��10��
    ��    ��   : w00176964
    �޸�����   : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcInterSysAcqSucc_Main(VOS_VOID)
{


    /* �ж��Ƿ���Ҫ������������BSR��ʱ�� */
    if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
    {
        if (VOS_TRUE == NAS_MSCC_IsNeedRestartBsrTimer())
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_BSR_TIMER);
            NAS_MSCC_StartBsrTimer();
        }
        else
        {
            if (NAS_MSCC_TIMER_STATUS_RUNING != NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_BSR_TIMER))
            {
                NAS_MSCC_StartBsrTimer();
            }
        }
    }


    NAS_MSCC_StopTimer(TI_NAS_MSCC_SCAN_TIMER);

    NAS_MSCC_Reset1xServiceClSysAcqRelatedInfo_L1Main();

    if (VOS_TRUE == NAS_MSCC_Get3gppCampOnFlag())
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE,
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_LTE_SUCC);
    }
    else
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE,
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_DO_SUCC);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_ProcInterSysAcqFail_Main
 ��������  : MAIN�ϴ����ڲ�ϵͳ����ʧ�ܽ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcInterSysAcqFail_Main(
    NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU                    *pstSysAcqRslt
)
{
    VOS_UINT8                           ucSearchLteFLag  = VOS_FALSE;
    VOS_UINT8                           ucSearchHrpdFLag = VOS_FALSE;

    ucSearchLteFLag  = pstSysAcqRslt->ucSearchLteFlag;
    ucSearchHrpdFLag = pstSysAcqRslt->ucSearchHrpdFlag;

    /* Lte��Hrpd����������������ʧ�ܵ��Ժ󣬲�֪ͨMMA sys acq end */
    if ((VOS_TRUE == ucSearchLteFLag)
     && (VOS_TRUE == ucSearchHrpdFLag))
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE,
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_FAIL);
    }

    /* LTEע�ᱻ�ܿ���Ч,��������available timer,ֱ������HRPD */
    if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);

        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        /* Set the Camp On flag to FALSE */
        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);

        return;
    }

    if (VOS_TRUE == NAS_MSCC_StartTimer(TI_NAS_MSCC_AVAILABLE_TIMER, NAS_MSCC_GetNextAvailableTimerLength_L1Main()))
    {
        if (VOS_TRUE == NAS_MSCC_Is1xNormalService())
        {
            NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main();
        }
        else
        {
            NAS_MSCC_AddCurOosAvailableTimerStartCount_L1Main();
        }
    }

    /* if both 1x and hrpd ,lte no service,start scan timer */
    if (NAS_MSCC_SERVICE_STATUS_NO_SERVICE == NAS_MSCC_GetCurr1xServiceStatus())
    {
        /* we start the timer only in CL mode */
        if (VOS_FALSE == NAS_MSCC_IsGULModeConfigured())
        {
            (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());
        }
    }

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_RcvInterSysAcqRsltCnf_Main_Active
Description     :   in active state process the system acquire result indication message

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-06-11
        Author  :   W00176964
        Modify content : CDMA Iteration 12 Modified
    3)  Date           : 2015-06-04
        Author         : w00176964
        Modify content : CDMA Iteration 15 Modified
    4)  Date           : 2015-08-25
        Author         : m00312079
        Modify content : DTS2015082004682:L2C��������MMA�ϱ��޷���
    5)  Date           : 2016-01-15
        Author         : j00354216
        Modify content : DTS2016011403391
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvInterSysAcqRsltCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU                    *pstSysAcqRslt = VOS_NULL_PTR;
    VOS_UINT8                                               ucSearchLteFLag  = VOS_FALSE;
    VOS_UINT8                                               ucSearchHrpdFLag = VOS_FALSE;

    pstSysAcqRslt = (NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU *)pstMsg;

    ucSearchLteFLag  = pstSysAcqRslt->ucSearchLteFlag;
    ucSearchHrpdFLag = pstSysAcqRslt->ucSearchHrpdFlag;

    if (NAS_MSCC_SYSTEM_ACQUIRED_RESULT_SUCCESS == pstSysAcqRslt->enRslt)
    {
        NAS_MSCC_ProcInterSysAcqSucc_Main();

        return VOS_TRUE;
    }

    if (NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE == pstSysAcqRslt->enRslt)
    {
        NAS_MSCC_ProcInterSysAcqFail_Main(pstSysAcqRslt);
    }

    if (NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ABORTED == pstSysAcqRslt->enRslt)
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_INTERRUPT,
                                           MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_FAIL);
    }

    if ( NAS_MSCC_SYSTEM_ACQUIRED_RESULT_L2C == pstSysAcqRslt->enRslt )
    {
        if ((VOS_TRUE == ucSearchLteFLag)
         && (VOS_TRUE == ucSearchHrpdFLag))
        {
            NAS_MSCC_SndMmaSystemAcquireEndInd(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE,
                                               MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                               MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_FAIL);
        }
    }
    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvTiSleepTimerExpired_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* here must be CL mode */
    NAS_MSCC_PerformSystemAcquireUponSleepTimerExpired_Main();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_ProcRfAvailableInd_Main_Deactive
 ��������  : MSCC��deactive״̬�£�����RF��Դ��������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��2��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_ProcRfAvailableInd_Main_Deactive()
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimCardStatus;
    VOS_UINT8                           ucSimPsRegStatus;

    VOS_UINT8                           ucAllowSrchLteFlg;

    ucAllowSrchLteFlg = NAS_MSCC_GetAllowSrchLteFlg();
    enUsimCardStatus    = NAS_MSCC_GetUsimCardStatus();
    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    /* �ػ�����NULL״̬��ֻ�н�SLEEPģʽʱ���Ż��DEACTIVE״̬ */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_NORMAL);

        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
    }

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));

        return;
    }

    /* current support lte, usim card status is avialable and sim ps reg status is true, start lte acquir */
    if ((VOS_TRUE                               == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
     && (NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT  == enUsimCardStatus)
     && (VOS_TRUE                               == ucSimPsRegStatus)
     && (VOS_TRUE                               == ucAllowSrchLteFlg))
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return;
}


VOS_UINT32 NAS_MSCC_RcvMmcMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ProcRfAvailableInd_Main_Deactive();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ProcRfAvailableInd_Main_Deactive();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvXsdMsccRfAvailableInd_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_ProcRfAvailableInd_Main_Deactive();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaSrvAcqReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimCardStatus;
    VOS_UINT8                           ucSimPsRegStatus;
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq = VOS_NULL_PTR;
    VOS_UINT8                           ucAllowSrchLteFlg;

    ucAllowSrchLteFlg = NAS_MSCC_GetAllowSrchLteFlg();

    pstSrvAcqReq = (MMA_MSCC_SRV_ACQ_REQ_STRU *)pstMsg;

    enUsimCardStatus    = NAS_MSCC_GetUsimCardStatus();
    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    /* �ػ�����NULL״̬��ֻ�н�SLEEPģʽʱ���Ż��DEACTIVE״̬ */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);

        NAS_MSCC_SndXsdSrvAcqReq(pstSrvAcqReq);
    }

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));

        return VOS_TRUE;
    }

    /* current support lte, usim card status is avialable and sim ps reg status is true, start lte acquir */
    if ((VOS_TRUE                               == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
     && (NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT  == enUsimCardStatus)
     && (VOS_TRUE                               == ucSimPsRegStatus)
     && (VOS_TRUE                               == ucAllowSrchLteFlg))
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return VOS_TRUE;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaCdmaMoCallStartNtf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                     ucSimPsRegStatus;

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_MO_TRIGGER, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_MO_TRIGGER));

        return VOS_TRUE;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return VOS_TRUE;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}



/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiAvailableTimerExpired_Main_Active
Description     :   proc for TI_NAS_MSCC_AVAILABLE_TIMER message
Input parameters:   ulEventType
                    pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2014-4-7
        Author  :   w00176964
        Modify content :Create
    2)  Date    :   2015-12-11
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiAvailableTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo();
    NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo();

    if (VOS_TRUE == NAS_MSCC_ProcTiAvailableTimerExpiredOosSrch_L1Main())
    {
        NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo();
        NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo();

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MSCC_ProcTiAvailableTimerExpiredLteHistorySrchWith1xSrvExist_L1Main())
    {
        NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo();
        NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo();

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MSCC_ProcTiAvailableTimerExpiredLteFullBandSrchWith1xSrvExist_L1Main())
    {
        NAS_MSCC_MNTN_LogFsmL1MainCtxRelatedInfo();
        NAS_MSCC_MNTN_LogClSystemAcquireStrategyRelatedInfo();

        return VOS_TRUE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvTiScanTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enHrpdSrvst;

    /* maybe here is the buffered scan timer expied message,should judge the service
       status, if one of the system is normal service, hould ignore this message */

    enHrpdSrvst = NAS_MSCC_GetCurrHrpdServiceStatus();

    if ((NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == NAS_MSCC_GetCurr3gppPsServiceStatus())
     || (NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == enHrpdSrvst))
    {
        /* discard this message */
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MSCC_Get1xSysAcqMoCallFlag())
    {
        (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());
        return VOS_TRUE;
    }

    /* Start the Power Off FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_POWER_OFF);

    return VOS_TRUE;
}


VOS_VOID NAS_MSCC_PerformSystemAcquireUponSleepTimerExpired_Main(VOS_VOID)
{
    VOS_UINT8                           ucSimPsRegStatus;

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_NORMAL);

        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
    }

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));

        return;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvHsdInterSysStartInd_Main_Active
 ��������  : mscc�յ���ϢHSD_MSCC_INTERSYS_START_IND,�������Ϣ
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2015��11��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdInterSysStartInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_CL_INTERSYS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmcInterSysStartInd_Main_Active
 ��������  : mscc�յ���ϢMMC_MSCC_INTERSYS_START_IND,�������Ϣ
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2015��11��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcInterSysStartInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_CL_INTERSYS);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMsccCLInterSysRsltCnf_Main_Active
 ��������  : mscc�յ���ϢID_NAS_MSCC_MSCC_CL_INTERSYS_RSLT_CNF,�������Ϣ
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2015��11��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccCLInterSysRsltCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvMmaCdmaMoCallSusccessNtf_Main_Active
 ��������  : mscc�յ���ϢID_MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF,�������Ϣ
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2015��11��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaCdmaMoCallSusccessNtf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Start the Power OFF FSM  */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_POWER_OFF);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_RcvXsdEmcCallBackInd_Main_Active
 ��������  : mscc�յ���ϢID_XSD_MSCC_EMC_CALLBACK_IND,�������Ϣ
 �������  : pstMsg      - ��Ϣ����
             ulEventType - ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣ����δ���

 �޸���ʷ      :
 1.��    ��   : 2016��1��6��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdEmcCallBackInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucSimPsRegStatus;

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    NAS_MSCC_SetEmcCallExistFlag(VOS_FALSE);

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));

        return VOS_TRUE;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return VOS_TRUE;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_ProcTiAvailableTimerExpiredOosSrch_L1Main(VOS_VOID)
{
    NAS_NORMAL_LOG(UEPS_PID_MSCC, "NAS_MSCC_ProcTiAvailableTimerExpiredOosSrch_L1Main entered.");

    if (VOS_FALSE == NAS_MSCC_Is1xNormalService())
    {
        /* 1x���ܴ��з���䵽�޷���,��Ҫ���1x�з���ʱ�����Ϣ */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);

        NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

        NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

        NAS_MSCC_ResetCur1xServiceSysAcqPhaseNum();

        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED, NAS_MSCC_PIF_PLMN_SEARCH_SPEC);

        return VOS_TRUE;
    }

    /* ��OOS����,���ö�ʱ���������� */
    NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main();

    return VOS_FALSE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ProcTiAvailableTimerExpiredLteFullBandSrchWith1xSrvExist_L1Main
Description     :   proc for TI_NAS_MSCC_AVAILABLE_TIMER message
Input parameters:   VOS_VOID
Output parameters:  None
Return Value    :   VOS_UINT32
Modify History:
    1)  Date    :   2015-12-11
        Author  :   w00176964
        Modify content :Create
    2)  Date    :   2016-1-16
        Author  :   w00176964
        Modify content :DTS2016011505664:����LTE��ȫƵ������֮ǰ����NV�޶�������LTE��ʷƵ������
*****************************************************************************/
VOS_UINT32 NAS_MSCC_ProcTiAvailableTimerExpiredLteFullBandSrchWith1xSrvExist_L1Main(VOS_VOID)
{
    VOS_UINT8                           ucFullBandSrchCount;
    VOS_UINT8                           ucFullBandSrchNum;

    NAS_NORMAL_LOG(UEPS_PID_MSCC, "NAS_MSCC_ProcTiAvailableTimerExpiredLteFullBandSrchWith1xSrvExist_L1Main entered.");

    if (VOS_TRUE == NAS_MSCC_IsNeedPerfromLteFullBandSrchWith1xServiceExist_L1Main())
    {
        NAS_MSCC_AddCur1xServiceLteFullBandSrchCount_L1Main();

        if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
        {
            ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteFullBandSrchNum;
        }
        else
        {
            ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteFullBandSrchNum;
        }

        ucFullBandSrchCount = NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main();

        /* ��ǰ�������׶�,����Ҫ�����¸��׶��� */
        if ((NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_MAX != NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
         && (ucFullBandSrchCount == ucFullBandSrchNum))
        {
            NAS_MSCC_AddCur1xServiceSysAcqPhaseNum();

            NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

            NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

            NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);
        }

        /* �Ƿ���Ҫ���õ�ǰ�׶� */
        if ((NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_MAX == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
         && (ucFullBandSrchCount == ucFullBandSrchNum))
        {
            NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

            NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();
        }

        /* ��Ҫ����ȫƵ�ѵ�ʱ��,��Ҫ�����ʷ�ѵĴ���,��֤����NV�޶���������ʷ�Ѻ��ٽ���һ��ȫƵ�� */
        NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED, NAS_MSCC_PIF_PLMN_SEARCH_SPEC);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_ProcTiAvailableTimerExpiredLteHistorySrchWith1xSrvExist_L1Main(VOS_VOID)
{
    VOS_UINT8                           ucHistorySrchCount;
    VOS_UINT8                           ucHistorySrchNum;
    VOS_UINT8                           ucFullBandSrchNum;

    NAS_NORMAL_LOG(UEPS_PID_MSCC, "NAS_MSCC_ProcTiAvailableTimerExpiredLteHistorySrchWith1xSrvExist_L1Main entered.");

    if (VOS_TRUE == NAS_MSCC_IsNeedPerfromLteHistorySrchWith1xServiceExist_L1Main())
    {
        NAS_MSCC_AddCur1xServiceLteHistorySrchCount_L1Main();

        if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
        {
            ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteHistorySrchNum;

            ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteFullBandSrchNum;
        }
        else
        {
            ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteHistorySrchNum;

            ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteFullBandSrchNum;
        }

        ucHistorySrchCount  = NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main();

        /* ��ǰ�������׶�,����Ҫ�����¸��׶��� */
        if ((NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_MAX != NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
         && (ucHistorySrchCount == ucHistorySrchNum)
         && (0                  == ucFullBandSrchNum))
        {
            NAS_MSCC_AddCur1xServiceSysAcqPhaseNum();

            NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

            NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

            NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);
        }

        /* �Ƿ���Ҫ���õ�ǰ�׶� */
        if ((NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_MAX == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
         && (ucHistorySrchCount == ucHistorySrchNum)
         && (0                  == ucFullBandSrchNum))
        {
            NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

            NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();
        }

        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED, NAS_MSCC_PIF_PLMN_SEARCH_HISTORY);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MSCC_RcvTi1xSrvClSysAcqPhaseOneTotalTimerExpired_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_NORMAL_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTi1xSrvClSysAcqPhaseOneTotalTimerExpired_Main_Active entered.");

    /* ע��:������̶��ں������,�˴��Ǵ�Ϻ�ص�L1 MAIN�Ĳ��� */

    /* ��ʽֹͣ�µ�ǰ�ܽ׶�ʱ����ʱ��,��Ϊ����ʱ�ȳ�ʱ�󱻻���,
       �ڴ����涨ʱ����ʱ֮ǰ������ */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);

    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE != NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTi1xSrvClSysAcqPhaseOneTotalTimerExpired_Main_Active:Not In Phase One.");

        return VOS_TRUE;
    }

    /* ���õ�ǰ�׶ε�һЩ����,�����¸��׶����� */
    NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();
    NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_MAX != NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
    {
        NAS_MSCC_AddCur1xServiceSysAcqPhaseNum();
    }

    /* �����ǰavailable���������У���������ʱ���ȴ��䳬ʱ������������ */
    if (NAS_MSCC_TIMER_STATUS_RUNING == NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_AVAILABLE_TIMER))
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

        /* ����һ����ʱ��ʱ��,��ʱ���л����¸��׶� */
        (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_AVAILABLE_TIMER, TI_NAS_MSCC_DEFAULT_AVAILABLE_TIMER_SKIP_LEN);
    }

    return VOS_TRUE;
}


/* ϵͳ����lte����������ӳ��� */
NAS_MSCC_SYS_ACQ_SCENE_MAP_LTE_SRCH_TYPE_STRU g_astSysAcqSceneMapLteSrchTypeTbl[]=
{
    {NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
    {NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
    {NAS_MSCC_SYS_ACQ_SCENE_LTE_NOT_AVAILABLE, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
    {NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
    {NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
    {NAS_MSCC_SYS_ACQ_SCENE_SYS_CFG_SET, NAS_MSCC_PIF_PLMN_SEARCH_SPEC},
};


/*****************************************************************************
Function Name   :   NAS_MSCC_GetSysAcqLteSrchType_L1Main
Description     :   ��ȡϵͳ����Lteʱ����������
Input parameters:   enSysAcqScene--���񳡾�
Output parameters:  VOS_VOID
Return Value    :   NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32

Modify History:
    1)  Date    :   2015-12-30
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/

NAS_MSCC_PIF_PLMN_SEARCH_TYPE_ENUM_UINT32 NAS_MSCC_GetSysAcqLteSrchType_L1Main(
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
)
{
    VOS_UINT32                          i;

    /* ���ڱ�������Ƿ���ӳ���ϵ,���û�и��ݵ�ǰLTE�����������Լ�1x�Ƿ��з�������ж� */
    for (i = 0; i < (sizeof(g_astSysAcqSceneMapLteSrchTypeTbl)/sizeof(NAS_MSCC_SYS_ACQ_SCENE_MAP_LTE_SRCH_TYPE_STRU)); i++)
    {
        if (enSysAcqScene == g_astSysAcqSceneMapLteSrchTypeTbl[i].enSysAcqScene)
        {
            return g_astSysAcqSceneMapLteSrchTypeTbl[i].enLteSrchType;
        }
    }

    if (VOS_TRUE == NAS_MSCC_Is1xNormalService())
    {
        if (VOS_TRUE == NAS_MSCC_IsNeedPerfromLteHistorySrchWith1xServiceExist_L1Main())
        {
            return NAS_MSCC_PIF_PLMN_SEARCH_HISTORY;
        }
    }

    return NAS_MSCC_PIF_PLMN_SEARCH_SPEC;
}


#endif


VOS_VOID NAS_MSCC_PerformSystemAcquireUponPowerOn_Main(
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU                       *pstMmaSysAcqReq = VOS_NULL_PTR;

    pstMmaSysAcqReq = (MMA_MSCC_SYSTEM_ACQUIRE_REQ_STRU *)pstMsg;

    /* ���³���λ����Ϣ */
    NAS_MSCC_UpdateGulNoCardInitSearchLocInfo(pstMmaSysAcqReq->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMcc,
                                              pstMmaSysAcqReq->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMnc);

    NAS_MSCC_Update1xNoCardInitSearchLocInfo(pstMmaSysAcqReq->stCdmaInitLocInfo.lSid,
                                             pstMmaSysAcqReq->stCdmaInitLocInfo.lNid);

    NAS_MSCC_Update1xNoCardInitSearchLocMcc(pstMmaSysAcqReq->stCdmaInitLocInfo.ulMcc);


    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_POWER_UP,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     &(pstMmaSysAcqReq->stInitAcqPlmnInfo),
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        /* Set the Current FSM state to Active */
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

        return;
    }

    /* ���洦��CLģʽ�µ�ϵͳ�������� */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_NORMAL);

        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
    }

    if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON));

        return;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_POWER_UP,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     &(pstMmaSysAcqReq->stInitAcqPlmnInfo),
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        /* hrpd and lte could not both perform system acquire,here return */
        return;
    }

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        /* Send HSD system acquire request if CDMA EVDO is supported */
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_POWER_UP,
                                 0,
                                 VOS_NULL_PTR);

        /* Set the Camp On flag to FALSE */
        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }
#endif

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_PerformSystemAcquireUponSysCfg_Main
Description     :   ��SYS CFG�����£�����ϵͳ����
Input parameters:   VOS_VOID
Output parameters:  VOS_VOID
Return Value    :   VOS_VOID
Modify History:
    1)  Date    :   2015-5-29
        Author  :   y00245242
        Modify content :Create
*****************************************************************************/
VOS_VOID NAS_MSCC_PerformSystemAcquireUponSysCfg_Main(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          uc3gppNormalSrvFlg;
    VOS_UINT32                          ucHrpdNormalSrvFlg;
    VOS_UINT8                           ucSimPsRegStatus;
#endif

    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
         if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
         {
             NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                          NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                          VOS_NULL_PTR,
                                          VOS_NULL_PTR);

             NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

             NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);
         }

         return;
    }

    /* ���洦��CLģʽ�µ�ϵͳ�������� */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    if (VOS_TRUE == NAS_MSCC_IsNeedStartScanTimerUponSyscfg())
    {
        (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());
    }

    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
    {
        if (VOS_FALSE == NAS_MSCC_Get1xActiveFlg())
        {
            NAS_MSCC_SndXsdSysAcqReq(MSCC_XSD_SYS_ACQ_TYPE_NORMAL);

            NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set1xActiveFlg(VOS_TRUE);
        }
    }

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    uc3gppNormalSrvFlg  = NAS_MSCC_Is3gppNormalService();
    ucHrpdNormalSrvFlg  = NAS_MSCC_IsHrpdNormalService();

    /* ���3GPP��HRPD�Ѿ���normal service��פ����������ȼ�,����Ҫ����;ֱ�ӷ��� */
    if ((VOS_TRUE  == NAS_MSCC_IsCampOnHighestPrioritySystem())
     && ((VOS_TRUE == uc3gppNormalSrvFlg)
      || (VOS_TRUE == ucHrpdNormalSrvFlg)))
    {
        return;
    }

    /* ����CL����������PS����Ч,��CL�������� */
    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SYS_CFG_SET, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SYS_CFG_SET));

        return;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
        {
            NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                         NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                         VOS_NULL_PTR,
                                         VOS_NULL_PTR);

            NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);
        }

        return;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        if (VOS_FALSE == NAS_MSCC_GetHrpdActiveFlg())
        {
            NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                     0,
                                     VOS_NULL_PTR);

            NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

            NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
        }
    }
#endif

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 NAS_MSCC_RcvHsdRfAvailableInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* HSD��DEACTIVE״̬�յ�RF AVAILABLE IND��˵��֮ǰHSD����RF��Դ
       ����Ԥ�������жϣ������ǰģ����֧�֣��򲻽�״̬�����������Ͻ��ú���
       һ����CLģʽ��
       ������CLģʽ����������:(1)SYSCFG���ò�֧��CL;(2)SYSCFG֧��CL����������CL������ */
    if (VOS_FALSE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        /* (1)HRPD��֧�ֺ�SYSCFG�����÷�֧;
           (2)��֧��CLģʽ������1X��HRPDʧ�ܣ�TI_NAS_MSCC_SCAN_TIMER��ʱ����ʱ��HSD����DEACTVE״̬
           (3)֧��CLģʽ��������HRPD+LTE�������ģʽ */
        if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
        {
            /* Send HSD system acquire request if CDMA EVDO is supported */
            NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                     0,
                                     VOS_NULL_PTR);

            /* Set the Camp On flag to FALSE */
            NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

            NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
        }

        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
    {
        /* ͣAVAILABLE��ʱ�� */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

        /* ��HRPD��Դ���õĳ������� */
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE));
    }
    else
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE));
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmcRfAvailableInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucHrpdActiveFlg;
    VOS_UINT8                           ucAllowSrchLteFlg;

    ucAllowSrchLteFlg = NAS_MSCC_GetAllowSrchLteFlg();
    ucHrpdActiveFlg = NAS_MSCC_GetHrpdActiveFlg();

    /* MMC��DEACTIVE״̬�յ�RF AVAILABLE IND��˵��֮ǰMMC����RF��Դ
       ����Ԥ�������жϣ������ǰģ����֧�֣��򲻽�״̬�����������Ͻ��ú���
       һ����CLģʽ */
    if (VOS_FALSE == NAS_MSCC_IsNeedPerformCLSysAcq())
    {
        /* (1)LTE��֧�ֺ�SYSCFG�����÷�֧;
           (2)��֧��CLģʽ������1X��LTEʧ�ܣ�TI_NAS_MSCC_SCAN_TIMER��ʱ����ʱ��MMC����DEACTVE״̬
           (3)֧��CLģʽ��������HRPD+LTE�������ģʽ */
        if ( (VOS_TRUE  == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
          && (VOS_FALSE == ucHrpdActiveFlg)
          && (VOS_TRUE  == ucAllowSrchLteFlg))
        {
            NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                         NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                         VOS_NULL_PTR,
                                         VOS_NULL_PTR);

            NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);
        }

        return VOS_TRUE;
    }

    /* ���HRPD��ǰHRPDδ������Ļ�������HRPD���ģʽ���� */
    if (VOS_FALSE == NAS_MSCC_GetHrpdActiveFlg())
    {
        /* ͣAVAILABLE��ʱ�� */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

        /* ��lte��Դ���ó�ʱ������������CL  */
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_RF_AVAILABLE, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_LTE_RF_AVAILABLE));
    }

    return VOS_TRUE;
}


#endif


VOS_UINT32 NAS_MSCC_RcvMmcPlmnSelectionRsltInd_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU                  *pstMmcSysAcqCnf = VOS_NULL_PTR;
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enMmaSysAcqRlst;

    pstMmcSysAcqCnf                     = (MMC_MSCC_PLMN_SELECTION_RLST_IND_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_RF == pstMmcSysAcqCnf->enResult)
    {
        if (VOS_FALSE == NAS_MSCC_IsGULModeConfigured())
        {
            /* check the current mode(only CL mode) and find the prior system in mspl*/
            if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
            {
                NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_NOT_AVAILABLE, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_LTE_NOT_AVAILABLE));
            }


            return VOS_TRUE;
        }
    }
#endif

    enMmaSysAcqRlst = NAS_MSCC_ConvertMmcPlmnSelRsltToMmaSysAcqRlst(pstMmcSysAcqCnf->enResult);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE == pstMmcSysAcqCnf->enResult)
     || (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE      == pstMmcSysAcqCnf->enResult))
    {
        /* check the current mode(only CL mode) and find the prior system in mspl*/
        if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
        {
            NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST));

            return VOS_TRUE;
        }
    }
#endif

    /* GULģʽ����ԭ���߼�֪ͨMMA��������,ģʽΪ3GPP */
    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(enMmaSysAcqRlst,
                                           MSCC_MMA_ACQ_SYS_TYPE_3GPP,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);

        return VOS_TRUE;
    }

    /* ��ϡ�NO_RF��L2C�Ҳ���Ҫ����������²��ϱ�����������ϱ�mma_sys_end_ind��� */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE == enMmaSysAcqRlst)
     || (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE == enMmaSysAcqRlst)
     || (NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE == enMmaSysAcqRlst))
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(enMmaSysAcqRlst,
                                          MSCC_MMA_ACQ_SYS_TYPE_DO_LTE,
                                          MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);
    }
#endif

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvMsccPowerOffCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU                      *pstPowerOffRslt;

    pstPowerOffRslt = (NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU *)pstMsg;

    NAS_MSCC_ProcPowerOffResult_Main(pstPowerOffRslt->enRslt);

    return VOS_TRUE;
}


MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32 NAS_MSCC_GetSystemAcquireFinalResult(
    NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32                enAcqRslt
)
{

    if(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC == enAcqRslt)
    {
        return MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE;
    }
    else
    {
        return MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE;
    }

}




VOS_UINT32 NAS_MSCC_RcvMmaSysCfgReq_Main_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the entry message */
    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* Start the System config FSM */
    NAS_MSCC_InitFsmL2(NAS_MSCC_FSM_SYSTEM_CONFIG);

    return VOS_TRUE;
}

/* ɾ���˺��� */


VOS_UINT32 NAS_MSCC_RcvMsccSysCfgCnf_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SYS_CFG_SET_REQ_STRU                          *pstSysCfgReq = VOS_NULL_PTR;
    NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU                    *pstSysCfgCnf = VOS_NULL_PTR;
    #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
    VOS_UINT8                                               ucIsCLmodeLast;
    VOS_UINT8                                               ucIsCLmodeCurr;
    #endif

    pstSysCfgCnf = (NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU *)pstMsg;

    pstSysCfgReq  = (MMA_MSCC_SYS_CFG_SET_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();

    if (NAS_MSCC_SYS_CFG_RESULT_SUCCESS == pstSysCfgCnf->enRslt)
    {
        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        ucIsCLmodeLast = NAS_MSCC_IsCLCombinedModeWithRatPrio(NAS_MSCC_GetRatPrioList());
        ucIsCLmodeCurr = NAS_MSCC_IsCLCombinedModeWithRatPrio(&(pstSysCfgReq->stRatPrioList));
        #endif

        /* set the user rat priority */
        NAS_MSCC_SavePrioRatList(&pstSysCfgReq->stRatPrioList);

        /*send the system config success result to MMA */
        NAS_MSCC_SndMmaSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS);

        /* Send the system acquire if Sleep timer is running */
        if (NAS_MSCC_TIMER_STATUS_RUNING == NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_SLEEP_TIMER))
        {
            /* �ڷ���ϵͳ�����ֹͣsleep timer��ʱ�� */
            NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

            NAS_MSCC_PerformSystemAcquireUponSysCfg_Main();

            /* Set the Current FSM state to Active */
            NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);
        }

        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        /* ǰ��CL��GUL֮���б��ʱ���ϱ� */
        if (ucIsCLmodeLast != ucIsCLmodeCurr)
        {
            NAS_MSCC_SndRrmRatCombModeInd();
        }
        #endif
        return VOS_TRUE;
    }

    NAS_MSCC_SndMmaSysCfgCnf(pstSysCfgCnf->enRslt);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMsccSysCfgCnf_Main_Active
Description     :   The function is used to Handle System config Confirm internal message from MSCC in L1 Main active state.

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2014-04-10
        Author  :   m00270891
        Modify content :    Create

    2)  Date    :   2015-05-29
        Author  :   y00245242
        Modify content : DTS2015052903319

    3)  Date    :   2015-12-11
        Author  :   w00176964
        Modify content : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccSysCfgCnf_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SYS_CFG_SET_REQ_STRU                          *pstSysCfgReq  = VOS_NULL_PTR;
    NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU                    *pstSysCfgCnf = VOS_NULL_PTR;
    #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
    VOS_UINT8                                               ucIsCLmodeLast;
    VOS_UINT8                                               ucIsCLmodeCurr;
    #endif

    pstSysCfgCnf = (NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU *)pstMsg;

    pstSysCfgReq  = (MMA_MSCC_SYS_CFG_SET_REQ_STRU *)NAS_MSCC_GetCurrFsmEntryMsgBufferAddr();


    if (NAS_MSCC_SYS_CFG_RESULT_SUCCESS == pstSysCfgCnf->enRslt)
    {
        /* ֹͣ��صĶ�ʱ�� */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_TRUE == NAS_MSCC_IsHrpdAndLteBothSupported())
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_BSR_TIMER);
            NAS_MSCC_Reset1xServiceClSysAcqRelatedInfo_L1Main();

            NAS_MSCC_StopTimer(TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH);
        }

        NAS_MSCC_StopTimer(TI_NAS_MSCC_SCAN_TIMER);
#endif
        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        ucIsCLmodeLast = NAS_MSCC_IsCLCombinedModeWithRatPrio(NAS_MSCC_GetRatPrioList());
        ucIsCLmodeCurr = NAS_MSCC_IsCLCombinedModeWithRatPrio(&(pstSysCfgReq->stRatPrioList));
        #endif

        /* Note: firstly, set user rat priority. And then process system acquire. */
        NAS_MSCC_SavePrioRatList(&pstSysCfgReq->stRatPrioList);

        /*send the system config success result to MMA */
        NAS_MSCC_SndMmaSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS);

        NAS_MSCC_PerformSystemAcquireUponSysCfg_Main();

        #if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
        /* ǰ��CL��GUL֮���б��ʱ���ϱ� */
        if (ucIsCLmodeLast != ucIsCLmodeCurr)
        {
            NAS_MSCC_SndRrmRatCombModeInd();
        }
        #endif
        return VOS_TRUE;
    }

    NAS_MSCC_SndMmaSysCfgCnf(pstSysCfgCnf->enRslt);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ProcPowerOffResult_Main
Description     :   proc power off result ind
Input parameters:   VOS_VOID
Output parameters:  VOS_VOID
Return Value    :   VOS_VOID
Modify History:
    1)  Date    :   2014-4-7
        Author  :   w00176964
        Modify content :Create
    2)  Date    :   2015-8-26
        Author  :   w00242748
        Modify content :Create
      3.��    ��   : 2016��1��6��
        ��    ��   : w00242748
        �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                     �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcPowerOffResult_Main(
    NAS_MSCC_POWEROFF_RSLT_ENUM_UINT32  enRslt
)
{
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    VOS_RATMODE_ENUM_UINT32             enRatType;
#endif

    if (NAS_MSCC_POWEROFF_RSLT_POWER_SAVE_HRPD_LTE == enRslt)
    {
        NAS_MSCC_StopAllTimer();

        NAS_MSCC_Reset1xServiceClSysAcqRelatedInfo_L1Main();

        return;
    }

    if (NAS_MSCC_POWEROFF_RSLT_POWER_OFF == enRslt)
    {
        NAS_MSCC_StopAllTimer();

        /* Send the Power off result cnf to MMA */
        NAS_MSCC_SndMmaPowerOffRsltCnf();

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            enRatType = NAS_DYNLOAD_GetCurRatInCached(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W);

            (VOS_VOID)NAS_DYNLOAD_UnloadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatType);
        }
#endif

        /* Reset the Context For MSCC */
        NAS_MSCC_InitCtx(NAS_MSCC_INIT_CTX_POWEROFF);

        /* set next state to NULL */
        NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_NULL);

        return;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* stop all timer */
    NAS_MSCC_StopAllTimer();

    NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main();

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_DEACTIVE);

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_SLEEP_TIMER, NAS_MSCC_GetSleepTimerLength());
#endif

    return;
}

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
/*****************************************************************************
 �� �� ��  : NAS_MSCC_ProcDynamicLoadAfterStartCnf_Main
 ��������  : �ڿ�����ɺ󣬴���̬���صĴ���
 �������  : ucImsVoiceAvail           -IMS voice�Ƿ����
             ucIsExistPersistentBearer -persistent eps bearer�Ƿ���ڱ�ʶ
 �������  : ��
 �� �� ֵ  : ��
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��4��25��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MSCC_ProcDynamicLoadAfterStartCnf_Main(VOS_VOID)
{
    VOS_RATMODE_ENUM_UINT32                                 enRatMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enUtranMode;

    enRatMode = VOS_RATMODE_BUTT;

    if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
    {
        enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
        enRatMode   = NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(enUtranMode);

        (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);
    }

    return;
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Deactive
Description     :   ��deactive״̬�£��յ�MMA���û�PLMN������Ϣ
Input parameters:   ulEventType -- �¼�����
                    pstMsg      -- ��Ϣ
Output parameters:  VOS_VOID
Return Value    :   VOS_TRUE  -- ��Ϣ������ϣ�
                    VOS_FALSE -- ��Ϣ��Ҫ��һ������
Modify History:
    1)  Date    :   2015-12-30
        Author  :   y00245242
        Modify content :Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                     ucSimPsRegStatus;

    ucSimPsRegStatus    = NAS_MSCC_GetSimPsRegStatus();

    NAS_MSCC_StopTimer(TI_NAS_MSCC_SLEEP_TIMER);

    NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());

    NAS_MSCC_SetCurrFsmState(NAS_MSCC_L1_STA_ACTIVE);

    if ((VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
     && (VOS_TRUE == ucSimPsRegStatus))
    {
        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));

        return VOS_TRUE;
    }

    /* judge if need acqurie lte first, start lte acquire */
    if (VOS_TRUE == NAS_MSCC_IsNeedAcqLteFrist())
    {
        NAS_MSCC_SndMmcPlmnSearchReq(NAS_MSCC_PIF_ACQ_REASON_OTHER,
                                     NAS_MSCC_PIF_PLMN_SEARCH_SPEC,
                                     VOS_NULL_PTR,
                                     VOS_NULL_PTR);

        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

        return VOS_TRUE;
    }

    /* Send HSD system acquire request if CDMA EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndHsdSysAcqReq(MSCC_HSD_ACQUIRE_REASON_OTHER,
                                 0,
                                 VOS_NULL_PTR);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Active
Description     :   ��active״̬�£��յ�MMA���û�PLMN������Ϣ
Input parameters:   ulEventType -- �¼�����
                    pstMsg      -- ��Ϣ
Output parameters:  VOS_VOID
Return Value    :   VOS_TRUE  -- ��Ϣ������ϣ�
                    VOS_FALSE -- ��Ϣ��Ҫ��һ������
Modify History:
    1)  Date    :   2015-12-30
        Author  :   y00245242
        Modify content :Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPlmnUserReselReq_Main_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���available��ʱ�������У�����DO&L���޷�����Ҫ�������� */
    if (NAS_MSCC_TIMER_STATUS_RUNING == NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_AVAILABLE_TIMER))
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

        NAS_MSCC_SndInternalSysAcqReq(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED, NAS_MSCC_GetSysAcqLteSrchType_L1Main(NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED));
    }

    return VOS_TRUE;
}
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


