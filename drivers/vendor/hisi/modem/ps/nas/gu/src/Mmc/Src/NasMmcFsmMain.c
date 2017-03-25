/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcFsmMain.c
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2011��5��9��
  ����޸�   :
  ��������   : ��״̬��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��04��01��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasMmcCtx.h"
#include "NasMmlLib.h"
#include "NasMmlCtx.h"
#include "NasMmlMsgProc.h"
#include "NasComm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcFsmMain.h"
#include "NasMmcMain.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcProcNvim.h"
#include "NasMmcProcUsim.h"
#include "NasMmcTimerMgmt.h"
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
/* ɾ��ExtAppMmcInterface.h*/
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */
#include "NasMmcComFunc.h"
#include "NasMmcSndOm.h"
#include "NasMmcFsmSyscfg.h"
#include "NasMmcPreProcAct.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcFsmMainTbl.h"
#include "NVIM_Interface.h"

#include "NasUtranCtrlInterface.h"
#include "NasMmlLib.h"

/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

#include "NasMmcProcSuspend.h"
#include "NasMmcSndCss.h"
/* added by wx270776 for OM�ں�, 2015-08-21, begin */
#include "OmApi.h"
/* added by wx270776 for OM�ں�, 2014-08-21, end */

#include "NasMmcFsmPlmnSelection.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSMMAIN_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/
/*****************************************************************************
  3 �궨��
*****************************************************************************/

extern VOS_VOID SLEEP_EnterLowPower(VOS_VOID);

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvStartReq_NULL
 ��������  : NULL״̬(���ϵ�ʱMMC PID��ʼ��ʱMMC������״̬����ػ���������״̬)
             �յ�ID_MSCC_MMC_START_REQ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_START_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvStartReq_NULL(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SWITCH_ON);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSwitchOnRslt_NULL
 ��������  : �յ�������������ɹ���Ǩ�Ƶ�NAS_MMC_L1_STA_INITIAL״̬
             ��ʧ�ܱ���NAS_MMC_L1_STA_NULL״̬����
 �������  : ulEventType:��Ϣ����
             pstMsg:������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��23��
    ��    ��   : wenlutao /w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011120702166:����ʧ�ܣ���������λ��ɾ����λ��Ϣ��
  3.��    ��   : 2015��5��4��
    ��    ��   : w00242748
    �޸�����   : CMDA����13���뿪��
  4.��    ��   : 2015��8��24��
    ��    ��   : m00312079
    �޸�����   : DTS2015082400829:CLģʽ�л���DEACT̬��GULģʽ�л���INITIAL̬
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvSwitchOnRslt_NULL(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SWITCHON_RLST_STRU                 *pstSwitchOnMsg;

    pstSwitchOnMsg                      = (NAS_MMC_SWITCHON_RLST_STRU *)pstMsg;

    /* �յ�������������ɹ�Ǩ�Ƶ�NAS_MMC_L1_STA_INITIAL״̬��
       ʧ�ܱ���NAS_MMC_L1_STA_NULL״̬
    */
    if (VOS_TRUE == pstSwitchOnMsg->ulResult)
    {
        if (VOS_TRUE == NAS_MML_IsGULModeConfigured())
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);
        }
        else
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvSwitchOnRslt_NULL:����ʧ��");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvPowerOffReq_NULL
 ��������  : �ڹػ�״̬�ܵ��ػ�����Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��30��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvPowerOffReq_NULL(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvPowerOffReq_NULL:rcv power off req in NULL state");

    /* �Ѿ�Ϊ�ػ�״̬��ֱ�ӻظ�MSCC�ɹ� */
    NAS_Mmc_SndMsccPowerOffCnf();

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvPowerOffReq_L1Main
 ��������  : �յ�ID_MSCC_MMC_POWER_OFF_REQ��Ϣ�Ĵ���
 �������  : ulEventType:�ػ���Ϣ����
             pstMsg: �ػ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK: ����������Ϣ�ɹ�
              VOS_ERR: ����������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��8��5��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ����

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvPowerOffReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_POWER_OFF);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvPowerOffRslt_L1Main
 ��������  : �ڿ���̬ʱ���յ�NAS_MM_LAYER_MMCMMC_POWER_OFF_RSLT��Ϣ�Ĵ���
 �������  : ulEventType:NAS_MM_LAYER_MMCMMC_POWER_OFF_RSLT��Ϣ����
             pstMsg: NAS_MM_LAYER_MMCMMC_POWER_OFF_RSLT��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��7��13��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseI�޸�
  3.��    ��   : 2015��4��7��
    ��    ��   : l00324781
    �޸�����   : Mmc Power Save�󣬲��ٽ���OOC״̬�����ǽ���Deactive״̬
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvPowerOffRslt_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_POWEROFF_RSLT_STRU      *pstPowerOffRslt;    /* �ػ��Ľ�� */
    NAS_MMC_CONTEXT_STRU               *pstMmcCtx = VOS_NULL_PTR;
    NAS_MML_CTX_STRU                   *pstMmlCtx = VOS_NULL_PTR;

    pstPowerOffRslt = (NAS_MMCMMC_POWEROFF_RSLT_STRU*)pstMsg;

    /* �ػ���� */
    /* Modified by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    if ( NAS_MMC_POWEROFF_RSLT_POWER_OFF == pstPowerOffRslt->enRslt )
    /* Modified by s00246516 for L-C��������Ŀ, 2014-01-28, End */
    {
        /* ��ʼ��MMLģ��CTX */
        pstMmlCtx   = NAS_MML_GetMmlCtx();
        NAS_MML_InitCtx(NAS_MML_INIT_CTX_POWEROFF, pstMmlCtx);


        /* ֧��TDʱ����NASUTRANCTRL�����Ľ��г�ʼ�� */
        NAS_UTRANCTRL_InitCtx(NAS_MML_INIT_CTX_POWEROFF);

        /* ��ʼ��MMCģ��CTX */
        pstMmcCtx   = NAS_MMC_GetMmcCtxAddr();
        NAS_MMC_InitCtx(NAS_MMC_INIT_CTX_POWEROFF, pstMmcCtx);

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_NULL);
    }
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    else if (NAS_MMC_POWEROFF_RSLT_POWER_SAVE == pstPowerOffRslt->enRslt)
    {
        NAS_MMC_StopAllTimer();

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);

        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_BUTT);

        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);
    }
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, end */
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvPowerOffRslt_L1Main:�ػ����ʧ��");
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSysCfgReq_L1Main
 ��������  : L1(onplmn/initial/ooc)״̬�����յ�SYSCFG����
 �������  : ulEventType:��Ϣ����
              pstMsg: ID_MSCC_MMC_SYS_CFG_SET_REQ��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��10��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��8��5��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ����

  3.��    ��   : 2011��8��26��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ����:��ʱ������洦���в���Ԥ�����е��߼�

  4.��    ��   : 2012��5��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012041002516: L��Ĭ�ϳ��ش�����������ʱ����W onlyʧ��

  5.��    ��   : 2012��11��7��
    ��    ��   : s00217060
    �޸�����   : DTS2012060507813: GU�´���PSҵ��ʱ��MMC��MM/GMM�����ͷ����������ͷź��·�SYSCFG
  6.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvSysCfgReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm = VOS_NULL_PTR;
    VOS_UINT32                          ulSyscfgNeedPlmnSrchRslt;
    VOS_UINT32                          ulCsServiceExist;

    pstSysCfgSetParm         = (MSCC_MMC_SYS_CFG_SET_REQ_STRU*)pstMsg;

    /* �жϵ�ǰSYSCFG�����Ƿ���Ҫ�������� */
    ulSyscfgNeedPlmnSrchRslt = NAS_MMC_IsPlmnSelectionNeeded_SysCfg(pstSysCfgSetParm);

    /* �жϵ�ǰ�Ƿ���CSҵ����� */
    ulCsServiceExist         = NAS_MML_GetCsServiceExistFlg();


    /* ���SYSCFG������Ҫ�����ҵ�ǰ��ҵ����ڻ����л����ҵ�����
     ��ô������SYSCFG���ã���MSCC����SYSCFG ����ʧ��*/

    /* GU�´���PSҵ��ʱ��MMC��MM/GMM�����ͷ����������ͷź󣬿��·�SYSCFG����L�Ĵ�����ͬ
       ����CSҵ��ʱ��MMC��MSCC�ϱ�SYSCFG���Ϊ��CSҵ����� */
    if (VOS_TRUE == ulSyscfgNeedPlmnSrchRslt)
    {
        if (VOS_TRUE == ulCsServiceExist)
        {
            NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_CS_SERV_EXIST);
            return VOS_TRUE;
        }
        else
        {

        }
    }

    /* ����SYSCFG��״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcSyscfgRsltDisableEnable_OnPlmn
 ��������  : ����SYSCFG������µ�disable/enable�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��26��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

  2.��    ��   : 2012��06��13��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1������Disable/Enable L,���������ֺ���
  3.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  4.��    ��   : 2013��01��23��
    ��    ��   : s00217060
    �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
  5.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
  6.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  7.��    ��   : 2015��2��26��
    ��    ��   : w00167002
    �޸�����   : DTS2015021604972:��SYSCFG�������MMA����ATTACH���̡�MMC�Ѿ��˳�
                 SYSCFG״̬����������������������ʱ�����PS��׼��ATTACH��������LTE.
                 ���޸�Ϊ��SYSCFG��,�����Ҫ���������б��Ƿ�ATTACH PS��Ҫ��ENABLE LTE��
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcSyscfgRsltDisableEnable_OnPlmn(
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSyscfgRsltMsg
)
{
    VOS_UINT32                                    ulDisablteRoamFlg;
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32        enDisablteReason;
    /* ����ģʽ�ı���ж��Ƿ���Ҫdisable LTE */
    ulDisablteRoamFlg = NAS_MML_GetDisableLteRoamFlg();

    if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_SysCfg(pstSyscfgRsltMsg))
    {
        /* �����ʱLTE�ڽ�ֹ���뼼���б����reason����ΪMMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST */
        if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MML_SetLteForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_DISABLE);
            enDisablteReason = MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST;
        }
        /* �����ʱ��SIM������reason����ΪMMC_LMM_DISABLE_LTE_REASON_SIM_CARD_SWITCH_ON */
        else if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
        {
            enDisablteReason = MMC_LMM_DISABLE_LTE_REASON_SIM_CARD_SWITCH_ON;
        }
        else if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {
            enDisablteReason = MMC_LMM_DISABLE_LTE_REASON_PS_DETACH;
        }
        else
        {
            enDisablteReason = MMC_LMM_DISABLE_LTE_REASON_PS_USIM_INVALID;
        }

        /* ��ǰ����ΪLTE������ʱ������disable LTE��Ϣ */
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        }
        else
        {
            /* ������ε��µ�disable�Ѿ�֪ͨ��GU�����,��ʱ����Ҫ���ظ�֪ͨ */
            if (VOS_FALSE == ulDisablteRoamFlg)
            {
                NAS_MMC_SndDisableLteNotify(enDisablteReason);

                /* ��¼disable lteʱפ����������Ϣ */
                NAS_MMC_SetDisabledLtePlmnId(NAS_MML_GetCurrCampPlmnId());
            }

            /* ����disable LTE������� */
            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);
        }
        NAS_MML_SetDisableLteReason(enDisablteReason);
    }
    /* �жϵ�ǰ�Ƿ���Ҫenable LTE */
    else if (VOS_TRUE == NAS_MMC_IsNeedEnableLte_SysCfg(pstSyscfgRsltMsg))
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
    else
    {

    }
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSysCfgRslt_TrigSrvStaPlmnSrch_OnPlmn
 ��������  : ����SYSCFG����У����ڷ���״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE ��ʾ�Ѿ�������
             VOS_FALSE ��ʾ��δ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��17��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��5��24��
   ��    ��   : w00242748
   �޸�����   : DTS2014052106103:֧�ֽ��뼼����0102���ó�010203�����������ȼ�����
                ��������������L�޸��ǣ���������LTEʱ��ϳ���15s�ڣ�AP���·�detach
                ���󣬵���ʱMSCC�ķ���״̬Ϊ�����������Ե���DETACHʧ�ܣ��Ӷ�AP��
                �������и�λ��
  3.��    ��   : 2014��7��14��
    ��    ��   : w00242748
    �޸�����   : DTS2014063003419:SYSCFG���������ȼ����뼼����������NV����
  4.��    ��   : 2014��10��23��
    ��    ��   : s00217060
    �޸�����   : DTS2014101707757:SYSCFG���������ȼ����뼼������ʱ��������״̬ʱ��
                 ͬʱ����ע��״̬���������״̬Ϊ���Ʒ���ע��״̬Ϊ��ע�ᣬ
                 AT+COPS?��ѯʱ����ѯ����PLMN
 5.��    ��   : 2015��8��6��
   ��    ��   : c00318887
   �޸�����   : DTS2015041401965��syscfg����ֻ�����ӽ��뼼�����������뼼�����ȼ����ڵ�ǰ���뼼���Ŵ�������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysCfgRslt_TrigSrvStaPlmnSrch_OnPlmn(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList
)
{
    VOS_UINT32                          ulFlg;
    VOS_UINT32                          ulSpecPlmnSearchFlg;
    VOS_UINT32                          ulCsServiceExistFlg;

    /* �жϵ�ǰ�Ƿ�����������״̬���������������� */
    ulFlg               = NAS_MMC_IsNormalServiceStatus();
    ulSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_FALSE  == ulFlg )
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == ulSpecPlmnSearchFlg))
    {

        /* �������CSҵ�� */
        if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
        {
            NAS_MMC_SetBufferedPlmnSearchInfo(VOS_TRUE, NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET);
            return VOS_TRUE;
        }

        /* Ǩ�Ƶ�Intial״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);


        /* ��ǰ����ģ��SYSCFG/SYSCFGEX����Ϊ��֧�֣����������������ǰģ */

        if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_GetCurrNetRatType()) )
        {
            /* SYSCFG��������Ҫ���й�����������õ�ǰ���뼼��ΪBUTT */
            NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

            /* ���ý�������״̬ */
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
        }

        if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
        {
            /* ���õ�ǰפ�������ϵͳģʽΪBUTT  */
            NAS_MML_SetCurrSysSubMode(NAS_MML_RRC_SYS_SUBMODE_BUTT);
        }

        /* ���첢�����ڲ�������Ϣ:����SYSCFG */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET, VOS_NULL_PTR, 0);
        return VOS_TRUE;
    }


    if ( VOS_TRUE == NAS_MML_GetSyscfgTriHighRatSrchFlg() )
    {
        ulCsServiceExistFlg = NAS_MML_GetCsServiceExistFlg();
        if ( (VOS_TRUE == NAS_MMC_IsRatPrioChangeTriggerPlmnSrch(pstPrePrioRatList, NAS_MML_GetMsPrioRatList()))
          && (VOS_FALSE == ulCsServiceExistFlg) )
        {
            if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus() )
            {
                /* SYSCFG���ú���Ҫ����������Ϊ���Ʒ���״̬���ϱ� */
                NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);
                NAS_MMC_SetPsServiceStatus(NAS_MMC_LIMITED_SERVICE);
                NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);
                NAS_MMC_UpdateRegStateSpecPlmnSearch();
            }

            /* Ǩ�Ƶ�Intial״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* ���첢�����ڲ�������Ϣ:����SYSCFG */
            NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET, VOS_NULL_PTR, 0);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcSyscfgRsltPlmnSrch_OnPlmn
 ��������  : ����SYSCFG������������Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��26��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��10��31��
   ��    ��   : t00212959
   �޸�����   : DTS2012103100827:syscfg ֮���µ���������������ʱ���ϱ�refresh
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 4.��    ��   : 2014��10��23��
   ��    ��   : s00217060
   �޸�����   : DTS2014101707757:SYSCFG���������ȼ����뼼������ʱ��������״̬ʱ��
                ͬʱ����ע��״̬���������״̬Ϊ���Ʒ���ע��״̬Ϊ��ע�ᣬ
                AT+COPS?��ѯʱ����ѯ����PLMN
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcSyscfgRsltPlmnSrch_OnPlmn(VOS_VOID)
{
    /* Ǩ�Ƶ�Intial״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);


    /* ��ǰ����ģ��SYSCFG/SYSCFGEX����Ϊ��֧�֣����������������ǰģ */


    if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_GetCurrNetRatType()) )
    {
        /* SYSCFG��������Ҫ���й�����������õ�ǰ���뼼��ΪBUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* ���ý�������״̬ */
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    }

    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        /* ���õ�ǰפ�������ϵͳģʽΪBUTT  */
        NAS_MML_SetCurrSysSubMode(NAS_MML_RRC_SYS_SUBMODE_BUTT);
    }


    if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus() )
    {
        /* SYSCFG���ú���Ҫ����������Ϊ���Ʒ���״̬���ϱ� */
        NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_SetPsServiceStatus(NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);
        NAS_MMC_UpdateRegStateSpecPlmnSearch();
}

    /* ���첢�����ڲ�������Ϣ:����SYSCFG */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET, VOS_NULL_PTR, 0);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSyscfgRsltCnf_L1Main
 ��������  : L1(onplmn/initial/ooc)״̬�����յ�SYSCFG����Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg: MMCMMC_SYSCFG_RSLT_CNF��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��22��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��8��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II ����:���Ӷ�SYSCFG����Ĵ���

 3.��    ��   : 2011��10��18��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II ����:��ǰ����ģ��SYSCFG/SYSCFGEX����Ϊ��֧�֣�
                ���������������ǰģ

  4.��    ��   : 2011��12��01��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:disable/enable ����
  5.��    ��   : 2012��3��17��
    ��    ��   : w00176964
    �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:����LTE�������ι��ܶ���
  6.��    ��   : 2012��4��25��
    ��    ��   : w00166186
    �޸�����   : DTS2012042305019 PS ONLYפ��LTE����£�SYSCFG����L->LU��������
                 ��ǰ����
  7.��    ��   : 2012��5��22��
    ��    ��   : L60609
    �޸�����   : DTS2012051707660:L��ģ����W��ģ��W��������������L��ģ��Lģע��ɹ���g_StatusContext.ucCurRaForSysInfo
                 δ����
  8.��    ��   : 2012��6��8��
    ��    ��   : z40661
    �޸�����   : DTS2012060503632: ����ģʽ����Ϊbuttʱ,�п�����Ҫ��������,��Ҫ��������ʶ���ϡ�
  9.��    ��   : 2012��6��21��
    ��    ��   : l00130025
    �޸�����   : DTS2012061908446: ��פ��״̬���ã�ϵͳ����ģʽ����Ҫ����ΪBUTT,�Դ���MMA Mode����
 10.��    ��   : 2012��6��26��
    ��    ��   : w00176964
    �޸�����   : DTS2012061908446: ��Ȧ���Ӷ�

  11.��    ��   : 2012��7��6��
    ��    ��   : z00161729
    �޸�����   : DTS2012062502088:hplmnΪ23002��פ��W��46002��UPLMNΪL��46002��syscfg���ò�֧��L,������hplmn��ʱ����
                 ����syscfg����֧��L,��˻���������hplmn��NAS���ᣬ�޸���������һ��
 12.��    ��   : 2012��08��26��
    ��    ��   : l65478
    �޸�����   : DTS2012081507333:�ڿ���ָ����������������SYSCFG,���ý�����û�з�������

  13.��    ��   : 2012��9��25��
    ��    ��   : z40661
    �޸�����   : DTS2012082006273,anycell����״̬�������ʱ������syscfg����
                 ����ʱ����Ч����δ��������

  14.��    ��   : 2013��6��25��
     ��    ��   : z00234330
     �޸�����   : DTS2013061808384,syscfgex״̬���˳�ʱ��δ�ж�ҵ��������
  15.��    ��   : 2014��2��10��
     ��    ��   : w00242748
     �޸�����   : DTS2014020700426:syscfg����ڲ��б��Ѻ󣬲�����������SVLTE��Ҫ
                  �����һ�TL������Ӧ������������һء�
  16.��    ��   : 2014��2��24��
     ��    ��   : w00176964
     �޸�����   : High_Rat_Hplmn_Search���Ե���:����High_Prio_rat_hplmn��ʱ������������
  17.��    ��   : 2014��4��16��
     ��    ��   : w00242748
     �޸�����   : DTS2014041704339:SYSCFG����0201��ע����W�ϣ�Ȼ��������030201��
                  ��Ҫ���������ȼ�������
  18.��    ��   : 2014��10��27��
     ��    ��   : b00269685
     �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
  19.��    ��   : 2015��08��06��
     ��    ��   : c00318887
     �޸�����   : DTS2015041401965��syscfg����ֻ�����ӽ��뼼�����������뼼�����ȼ����ڵ�ǰ���뼼���Ŵ�������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvSyscfgRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulUsimStausFlg;
    VOS_UINT32                          ulSpecPlmnSearchFlg;
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSysCfgMsg    = VOS_NULL_PTR;

    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucPsAttachAllow;
    VOS_UINT8                           ucSvlteSupportFlg;

    /* ת��ΪSysCfg�����Ϣ */
    pstSysCfgMsg        = (NAS_MMCMMC_SysCfg_RSLT_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_ProcSyscfgRsltDisableEnable_OnPlmn(pstSysCfgMsg);
#endif

    /* ����Deactive ��״̬ʱ������Ҫ���� */
    if(NAS_MMC_L1_STA_DEACT == NAS_MMC_GetFsmTopState())
    {
        return VOS_TRUE;
    }


    /* ��SysCfg�����Ҫ������ֱ��Ǩ�Ƶ�INITIAL״̬�������� */
    if ( VOS_TRUE == pstSysCfgMsg->ulNeedPlmnSrch )
    {
        NAS_MMC_ProcSyscfgRsltPlmnSrch_OnPlmn();

        return VOS_TRUE;
    }

    /* ��ǰ����Ч��ֱ�ӷ��أ�����Ҫ���� */
    ulUsimStausFlg = NAS_MML_IsUsimStausValid();
    ulSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();

    if ( ( VOS_FALSE == ulUsimStausFlg )
       && (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING != ulSpecPlmnSearchFlg))
    {
        return VOS_TRUE;
    }

    ucSvlteSupportFlg = NAS_MML_GetSvlteSupportFlag();

    ucCsAttachAllow =  NAS_MML_GetCsAttachAllowFlg();
    ucPsAttachAllow =  NAS_MML_GetPsAttachAllowFlg();
    if((NAS_MMC_L1_STA_ON_PLMN == NAS_MMC_GetFsmTopState())
    && (VOS_FALSE == ucSvlteSupportFlg)
    && (VOS_FALSE == ucCsAttachAllow)
    && (VOS_FALSE == ucPsAttachAllow)
    && (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING != ulSpecPlmnSearchFlg))
    {
        return VOS_TRUE;
    }

    if ( VOS_TRUE == NAS_MMC_RcvSysCfgRslt_TrigSrvStaPlmnSrch_OnPlmn(&pstSysCfgMsg->stPrePrioRatList) )
    {
        return VOS_TRUE;
    }

    /* syscfg���ò�������ʱ����Ҫ�ж��Ƿ���Ҫ����HPLMN��ʱ�� */
    if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
    {
        /* ������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());

        /* HPLMN TIMER�����¼��ϱ� */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* ��HPLMN������������Ϊ���״����� */
        NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
    {
        /* ������ʱ�� */
        if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
        {
            NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
            NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
        }
    }


    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvPlmnListReq_L1Main
 ��������  : L1״̬�����յ��б���������
 �������  : ulEventType:��Ϣ����
 �������  : pstMsg:��Ϣָ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��8��5��
   ��    ��   : w00176964
   �޸�����   : V7R1 PhaseII ����

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����LIST����״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListSearchReq_L1Main
 ��������  : L1״̬�����յ�CSG�б���������
 �������  : ulEventType:��Ϣ����
 �������  : pstMsg:��Ϣָ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
            VOS_FALSE:��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
1.��    ��   : 2015��9��6��
  ��    ��   : z00161729
  �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListSearchReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����LIST����״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_L1Main
 ��������  : ����TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH��Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�����������
             VOS_FALSE:��������δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��13��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����LIST����״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvPlmnSpecialReq_L1Main
 ��������  : L1״̬�����յ�ָ����������
 �������  : ulEventType:��Ϣ����
              pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��8��5��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ����
  3.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : ��������״̬��ʱ����Ϊ��ǰ������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvPlmnSpecialReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Ǩ�Ƶ�Initial״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* ��������״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcAvailablePlmnListRslt_L1Main
 ��������  : �յ�PLMNListRslt��available��ʱ���Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��1��
   ��    ��   : t00212959
   �޸�����   : �����ɺ���,NAS_MMC_RcvMmcPlmnListRsltCnf_L1Main��Ȧ���Ӷ�
 2.��    ��   : 2012��10��7��
   ��    ��   : s46746
   �޸�����   : for V7R1C50_At_Abort���ڲ��б����������У������û��б�������֮�����û��б�������
                ����û������Available��ʱ���ٴγ����ڲ��б�����
 3.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 4.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcAvailablePlmnListRslt_L1Main()
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    VOS_UINT32                                              ulPlmnLaType;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulCsPsMode1NeedPeriodSearchGU;

    ulCsPsMode1NeedPeriodSearchGU = NAS_MMC_IsCsPsMode1NeedPeriodSearchGU();
#endif
    enAdditionalAction            = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_L1Main(),
                                                            NAS_MMC_GetPsRegAdditionalAction_L1Main());
    ulPlmnLaType                  = NAS_MMC_GetCurrentLaiForbbidenType();

    /* ��ǰ��������ʱ��Available Timer������������ */
    if ((VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
#if (FEATURE_ON == FEATURE_LTE)
     && (VOS_FALSE == ulCsPsMode1NeedPeriodSearchGU)
#endif
        )
    {
        NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

        NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

        /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
        NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
        /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */
    }
    else
    {
        /* ��ǰ������������ҿ���Ч��פ��С���ǽ�ֹС�����ǽ������ޣ���Ҫ
           ����Available Timer�����ڲ��б����� */
        if ( (VOS_TRUE == NAS_MML_IsUsimStausValid())
          && (NAS_MML_PLMN_FORBID_NULL  == ulPlmnLaType)
          && (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED != enAdditionalAction) )
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue());

            /* ���� availble timer��ǰ�����Ĵ�����ncell�������� */
            /* �·�����ԭ������count++, ����count++��ӵ� , ���Ըĺ������Q. �º�����ֻ����timer type*/
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn
 ��������  : �жϵ��� availble timer��ǰ�����Ĵ�����ncell��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 2.��    ��   : 2014��2��7��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL����
 3.��    ��   : 2015��5��25��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
 4.��    ��   : 2015��10��30��
   ��    ��   : h00281185
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0�޸�
*****************************************************************************/
VOS_VOID  NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn(VOS_VOID)
{
    if (VOS_TRUE == NAS_MMC_IsNeedStartHistoryTimer())
    {

        NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_HISTORY);

        return;
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStartPrefBandTimer())
    {

        NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_PREFBAND);

        return;
    }

    /* ���� availble timer��ǰ�����Ĵ�����ncell�������� */
    if (VOS_TRUE == NAS_MMC_IsNeedStartNcellAvailableTimer())
    {

        NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NCELL);

        return;
    }


    NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcPlmnListRsltCnf_L1Main
 ��������  : L1״̬�����յ�LIST����״̬������Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��14��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��14��
    ��    ��   : z00161729
    �޸�����   : list����������¸����ȼ������б���Ҫ��������֧�ֵĽ��뼼��
  3.��    ��   : 2011��11��22��
    ��    ��   : s46746
    �޸�����   : ���ò�1��Addition actionʱӦ���ж���Ϣ��Addition action�Ƿ���Ч�����ⵥ��DTS2011112208047
  4.��    ��   : 2011��11��30��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:disable/enable ����
  5.��    ��   : 2012��4��16��
    ��    ��   : w00166186
    �޸�����   : DTS2012041208026,�б��ѹ�����ע��ɹ���û������HPLMN��ʱ��
  6.��    ��   : 2012��5��9��
    ��    ��   : t00212959
    �޸�����   : V7R1C50 GUL BG�޸ģ����ݽ����Ϣ��������
  7.��    ��   : 2012��5��24��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 GUL BG�޸�
  8.��    ��   : 2012��6��8��
    ��    ��   : s46746
    �޸�����   : for CS/PS mode 1���б�������ɺ������ж�LTE�Ƿ��Ѿ���Disable��δ֪ͨ�����
                  ��Ӧ������ѡ��״̬������ҪDisable L,����δ����LTEʱ���б��������
  8.��    ��   : 2012��10��7��
    ��    ��   : s46746
    �޸�����   : for V7R1C50_At_Abort���ڲ��б����������У������û��б�������֮�����û��б�������
                  ����û������Available��ʱ���ٴγ����ڲ��б�����
  9.��    ��   : 2012��11��1��
    ��    ��   : t00212959
    �޸�����   : DTS2012103007750���б����������У�������ϱ��쳣�ı���
 10.��    ��   : 2012��11��30��
    ��    ��   : w00176964
    �޸�����   : DTS2012112911167:��һ��С���Ϸ�������ע���б�RRC LISTrej���������
                 available��ʱ��
                  �����һ�TL������Ӧ������������һء�
 11.��    ��   : 2014��2��24��
    ��    ��   : w00176964
    �޸�����   : High_Rat_Hplmn_Search���Ե���:����High_Prio_rat_hplmn��ʱ������������
 12.��    ��   : 2013��4��4��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RFǨ�Ƶ�OOC״̬������Available��ʱ��
                 ��PLMN LISTʱ���յ�NO RF������FAIL����������NO RF��־��
 13.��    ��   : 2014��5��15��
    ��    ��   : w00167002
    �޸�����   : DTS2014051501018:DSDS��MODEM����绰����MODEM����ʧ������AVAILABLE
                 ��ʱ�����û������б��ѣ����б��ѹ����У�����������ʱ����ʱ���б���
                 ������MMCû����������������ʱ����
                 �޸�Ϊ:���б���NO RF�󣬶�����AVAILABLE��ʱ������AVAILABLE��ʱ��
                 ��ʱ�����������ǰ����#12����������ǰACCESS BAR��������
 14.��    ��   : 2014��7��9��
    ��    ��   : w00176964
    �޸�����   : DSDS III����:�յ�LIST NO RF�Ĵ���
 15.��    ��   : 2014��10��27��
    ��    ��   : b00269685
    �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcPlmnListRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_PLMN_LIST_RSLT_STRU                         *pstListRslt    = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8                      enAsCellCampOn;     /* ������Ƿ�Camp On */

    pstListRslt    = (NAS_MMCMMC_PLMN_LIST_RSLT_STRU*)pstMsg;
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    enAsCellCampOn = NAS_MMC_GetAsCellCampOn();

    /* list�������ΪNO RF FAIL���ҷ�פ��̬�Ĵ���,����OOC״̬ */
    if  ((NAS_MMC_AS_CELL_NOT_CAMP_ON  == enAsCellCampOn)
      && (NAS_MMC_PLMN_LIST_NO_RF_FAIL == pstListRslt->enRslt))
    {
        /* ������״̬���ϱ�����״̬��Ǩ�Ƶ�ooc������available��ʱ�� */
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */

        return VOS_TRUE;
    }

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
       /* ���¸����ȼ��б� */
       NAS_MMC_UpdatePlmnListInPlmnSelectionList(&(pstListRslt->astPlmnSearchInfo[i]),
                                                   NAS_MMC_GetHighPrioPlmnList(),
                                                   VOS_FALSE,
                                                   VOS_TRUE);

       /* ��ά�ɲ�,��ѡ���б���� */
       NAS_MMC_LogPlmnSelectionList(NAS_MMC_GetHighPrioPlmnList());
    }

    /* ���ݷ��ص�additionֵ�Ե�ǰ��addition���и��� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != pstListRslt->enCsRegAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(pstListRslt->enCsRegAdditionalAction);
    }

    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != pstListRslt->enPsRegAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(pstListRslt->enPsRegAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_ProcPlmnListTriggerPlmnSearch_L1Main(pstListRslt))
    {
        return VOS_TRUE;
    }

    /* ������ϱ�����ʱ�ı������б��Ѵ��ָ����ʱ����ֹ����㰴ָ���������ϱ�*/
    if ( NAS_MMC_SPEC_PLMN_SEARCH_STOP == NAS_MMC_GetSpecPlmnSearchState())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);
    }



    /* �������ע��ɹ�����Ҫ�ж��Ƿ���Ҫ����HPLMN��ʱ��,������פ��̬�𱳾��Ѷ�ʱ�� */
    if ( (VOS_TRUE                  == NAS_MMC_IsNeedStartHPlmnTimer())
      && (NAS_MMC_AS_CELL_CAMP_ON   == enAsCellCampOn) )
    {
        /* ������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());

        /* HPLMN TIMER�����¼��ϱ� */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* ��HPLMN������������Ϊ���״����� */
        NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
    {
        /* ������ʱ�� */
        if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
        {
            NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
            NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
        }
    }

    /* ֻ�д���˳�״̬��ʱ����Ҫ�ж��Ƿ���available ��ʱ����ֹͣ�Լ��ڲ�LIST�������� */
    if (NAS_MMC_PLMN_LIST_ABORTED == pstListRslt->enRslt)
    {
        /* ������ȡ��Ȧ���Ӷ� */
        NAS_MMC_ProcAvailablePlmnListRslt_L1Main();
    }

    if ( NAS_MMC_PLMN_LIST_NO_RF_FAIL == pstListRslt->enRslt )
    {
        /* �ж�LIST����ʧ��NO RF���ж��Ƿ���Ҫ����AVAILABLE��ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue());
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccSrvAcqReq_L1Main
 ��������  : �յ�MSCC��ID_MSCC_MMC_SRV_ACQ_REQ��������״̬��
 �������  : ulEventType:��Ϣ����
           : pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��23��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccSrvAcqReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_SRV_ACQ_REQ_STRU           *pstSrvAcqReq = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;

    pstSrvAcqReq = (MSCC_MMC_SRV_ACQ_REQ_STRU*)pstMsg;

    /* ����on plmnʱ�ѵ��������У�����anycell���� */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL == pstSrvAcqReq->enSrvType)
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH);

        /*ֹͣAvailable��ʱ��*/
        NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);
        return VOS_TRUE;
    }

    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH, VOS_NULL_PTR, 0);

    /*ֹͣAvailable��ʱ��*/
    NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

    return VOS_TRUE;
}


#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccPlmnSrchReq_L1Main
 ��������  : ���������INITIAL���յ�TAF������������������״̬��
 �������  : ulEventType:��Ϣ����
            : pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : luokaihui / 00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : ��������״̬��ʱ����Ϊ��ǰ������
  3.��    ��   : 2015��6��9��
    ��    ��   : w00176964
    �޸�����   : DTS2015052903319
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccPlmnSrchReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����Ч������ANY CELL״̬�� */
    if ( VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_ANYCELL_SEARCH);
    }
    else
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccAcqReq_L1Main
 ��������  : �յ�MSCC�Ļ�ȡ����������������״̬��
 �������  : ulEventType:��Ϣ����
           : pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccAcqReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU               *pstPlmnId = VOS_NULL_PTR;
    VOS_UINT32                          ulArfcn;

    /* ��������ظ���ȡ�ɹ� */
    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
        pstPlmnId = NAS_MML_GetCurrCampPlmnId();
        ulArfcn   = NAS_MML_GetCurrCampArfcn();

        /* �ظ���ȡ�ɹ� */
        NAS_MMC_SndMsccAcqCnf(NAS_MSCC_PIF_ACQ_RESULT_SUCCESS, pstPlmnId, ulArfcn);

        return VOS_TRUE;
    }

    /* ״̬Ǩ�Ƶ�initial */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* ����ѡ��״̬�����������ȡ */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);


    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccRegReq_L1Main
 ��������  : �յ�MSCC��ע������������������״̬��
 �������  : ulEventType:��Ϣ����
           : pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccRegReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32         enPlmnSearchScene;
    VOS_UINT32                                    ulArfcn;
    MSCC_MMC_REG_REQ_STRU                         *pstRegReq             = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                         *pstPlmnId             = VOS_NULL_PTR;

    pstRegReq = (MSCC_MMC_REG_REQ_STRU*)pstMsg;

    /* ��ǰ����Ѿ���ע��ɹ�����ע����������REG������Ϣ�е�Ҫ������Ҫ�������� */
    if (VOS_FALSE == NAS_MMC_IsRegReqTriggerPlmnSrch_L1Main(pstRegReq))
    {
        pstPlmnId = NAS_MML_GetCurrCampPlmnId();
        ulArfcn   = NAS_MML_GetCurrCampArfcn();
        NAS_MMC_SndMsccRegCnf(MMC_LMM_CL_REG_STATUS_BUTT, NAS_MSCC_PIF_REG_RESULT_SUCCESS, pstPlmnId, ulArfcn);
        return VOS_TRUE;
    }

    /* ����NCELL��Ϣ */
    if (VOS_TRUE == pstRegReq->bitOpCellInfo)
    {
        NAS_MMC_SaveRegReqNCellInfo(&(pstRegReq->stCellInfo));
    }

    enPlmnSearchScene = NAS_MMC_GetPlmnSearchSceneMsccRegReq(pstRegReq);

    /* ����ѡ��״̬�����������ȡ��ע�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    NAS_MMC_SndInterPlmnSearchReq(enPlmnSearchScene, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccPowerSaveReq_L1Main
 ��������  : �յ�MSCC��Power Save������������״̬��
 �������  : ulEventType:��Ϣ����
           : pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��7��
    ��    ��   : l00324781
    �޸�����   : Mmc Power Save�󣬲��ٽ���OOC״̬�����ǽ���Deactive״̬
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccPowerSaveReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ǰ���뼼��ΪBUTT����ʾ�Ѿ���PowerSave��ֱ�ӻظ� */
    if (NAS_MML_NET_RAT_TYPE_BUTT == NAS_MML_GetCurrNetRatType())
    {
        /* ״̬Ǩ�Ƶ�OOC״̬������ֹͣ��ʱ�� */

        /* MMC Recived Power Save, The fsm do not transport OOC, transport deactive state */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);

        NAS_MMC_StopAllTimer();

        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);

        /* �ظ��ɹ� */
        NAS_MMC_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

        return VOS_TRUE;
    }


    /* ��չPower Off״̬�����й������ */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_POWER_OFF);

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccGetGeoReq_L1Main
 ��������  : �յ�MSCC��GET GEO����������ȡ������Ϣ״̬��
 �������  : ulEventType:��Ϣ����
           : pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : w0167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccGetGeoReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����GET GEO���� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_GET_GEO);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvInterPlmnSrchReq_L1Main
 ��������  : INITIALʱ�յ��ڲ�������������������״̬��
 �������  : ulEventType:��Ϣ����
 �������  : pstMsg:��Ϣָ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : luokaihui / 00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : ��������״̬��ʱ����Ϊ��ǰ������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvInterPlmnSrchReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����Ч������ANY CELL״̬�� */
    if ( VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_ANYCELL_SEARCH);
    }
    else
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvInterAnyCellSrchReq_Initial
 ��������  : INITIALʱ�յ��ڲ���ANYCELL����������������״̬��
 �������  : ulEventType:��Ϣ����
 �������  : pstMsg:��Ϣָ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��5��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��25��
    ��    ��   : w00166186
    �޸�����   : DTS2011112308343,G��pdp����󣬶�����Wע��PS�ɹ���CS13�ܾ���PS��·���ͷ�
                 �����ͷź�û��������

  3.��    ��   : 2011��12��1��
    ��    ��   : w00167002
    �޸�����   : DTS2011112308343: �����ⵥDTS2011112308343�е��޸ķŵ��յ�ѡ��״̬��
                 �Ľ���н��д�����ע��ʧ�ܣ��ҵ�ǰ�н�������ҵ��������
                 ����������ʱ����
  4.��    ��   : 2012��6��6��
    ��    ��   : l00130025
    �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨCDS��Ϣ���޷�����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvInterAnyCellSrchReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_ANYCELL_SEARCH);


    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAnycellSearchRslt_Initial
 ��������  : INITIALʱ�յ��ڲ���Anycell����״̬���������
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��19��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��12��02��
   ��    ��   : w00167002
   �޸�����   : DTS2011112804719:��ANYCELL��ϵͳ��Ϣʱ���յ�ABORT��Ϣ���������Ѿ�
                ��פ��̬����Ǩ�Ƶ� ON PLMN״̬��
 3.��    ��   : 2012��6��6��
   ��    ��   : l00130025
   �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨCDS��Ϣ���޷�����
 4.��    ��   : 2012��6��25��
   ��    ��   : W00176964
   �޸�����   : DTS2012062501067:Anycellפ��������available��ʱ��δ������������
 5.��    ��   : 2012��10��23��
   ��    ��   : w00176964
   �޸�����   : DTS2012101205055:פ��G����̬�³�ʱ�䶪��,�����������ٴ�����L����
                ʧ�ܶ�����,NAS����С���ָ����������ָ�
 6.��    ��   : 2012��10��29��
   ��    ��   : w00176964
   �޸�����   : DTS201201003747:anycell����״̬������anycell����״̬���Ĵ�Ͻ��Ӧ����
                anycell_srch_abort
 7.��    ��   : 2012��11��7��
   ��    ��   : l00167671
   �޸�����   : DTS2012110607212: availble��ʱ����ʱ�������ɹ�,���ܽ��ж�ʱ������
 8.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559: SIM��������LTE onlyʱ,������Available��ʱ��,����������п�����Available��ʱ��
 9.��    ��   : 2012��12��31��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE,G��ģ��USIM��ֹGSM����ʱ��������Available��ʱ��,
                 ������һЩ�Ƿ���Ҫ��Available��ʱ�����жϷ�װ�ɺ���
 10.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
 11.��    ��   : 2014��4��24��
    ��    ��   : w00242748
    �޸�����   : DTS2014042405819:�޿�״̬�£�����������#5������ANYCELL�ѣ�������״̬��
                 ���·�RRMM_UE_OOC_STATUS_NOTIFY_IND���������粻���·�CM SERVICE REJ
 12.��    ��   : 2014��10��13��
    ��    ��   : w00167002
    �޸�����   : DTS2014102005694:G�£�CSע��ɹ���PS��δע��ɹ�ʱ����
               ����绰ҵ���ڵ绰ҵ����ʱ������MMû���ͷ����MMCû�з���ANY
               CELL������
               �ڷ���ANYCELLʱ��MM���������ӻ����ڣ�ֱ��REJ�ˣ�������ȷ�ϴ˴��ڲ�����
               �����Ǵ����߶��������ȥ�ã�û����ȷ���ⳡ��,�������˴���
13.��    ��   : 2014��11��4��
   ��    ��   : w00167002
   �޸�����   : DTS2014103102839:L�²���绰HO��Wʧ�ܻ��˵�L�������������������
                ��ANYCELL����L��GU����������ǰL��֧������̬������������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAnycellSearchRslt_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU      *pstAnycellRslt;

    pstAnycellRslt = (NAS_MMCMMC_ANYCELL_SEARCH_RSLT_STRU *)pstMsg;

    if (NAS_MMC_ANYCELL_SEARCH_REJECT == pstAnycellRslt->enResult)
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);


        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            /* ���� availble timer��ǰ�����Ĵ�����ncell�������� */
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */
        }

        return VOS_TRUE;
    }

    /* ��������������additional��ֵ */
    NAS_MMC_ClearAllRegAdditionalAction_L1Main();

    /* �����ɹ�,Ǩ�Ƶ�ON PLMN */
    if (NAS_MMC_ANYCELL_SEARCH_SUCC == pstAnycellRslt->enResult)
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);

        /* ��Ҫ����Available��ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsAnycellSrchSuccStartAvailableTimer_Initial())
        {
            if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
            {
                /* ���� availble timer��ǰ�����Ĵ�����ncell�������� */
                NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
                (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

            }
        }

        /* ����Ҫ����available ��ʱ���������ֻ����һ�ε����,����ע��״̬ */
        NAS_MMC_UpdateRegStateAnyCellSearchSucc();

    }
    else if (NAS_MMC_ANYCELL_SEARCH_FAIL == pstAnycellRslt->enResult)
    {
        /* ������ */
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */
    }
    else if (NAS_MMC_ANYCELL_SEARCH_ABORTED == pstAnycellRslt->enResult)
    {

        /* ����פ��̬��Ǩ�Ƶ�ON PLMN״̬ */
        if ( NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn() )
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);
        }

    }
    else
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcAnycellSearchRslt_Initial:ENTERED");
    }

    /* ֻ����פ��̬��֪ͨAPS��ǰ�Ľ��뼼��,��פ��̬��PDP�Ѿ����������
       ֪ͨAPS��ǰ���뼼��ΪW/Lʱ,APS����ȥ����SNDCP�������ص�G���޷��ָ�
       ���� */
    if (NAS_MMC_SPEC_PLMN_SEARCH_STOP == NAS_MMC_GetSpecPlmnSearchState())
    {
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());

    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcGetGeoRslt_Initial
 ��������  : �յ�GET_GEO����Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��23��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��9��
    ��    ��   : s00217060
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcGetGeoRslt_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_GET_GEO_RSLT_STRU       *pstGetGeoRslt   = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnIdWithRat;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList = VOS_NULL_PTR;

    pstGetGeoRslt   = (NAS_MMCMMC_GET_GEO_RSLT_STRU *)pstMsg;
    pstRatList      = NAS_MML_GetMsPrioRatList();

    PS_MEM_SET(&stPlmnIdWithRat, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    if (NAS_MMC_GET_GEO_SUCCESS == pstGetGeoRslt->enGetGeoRslt)
    {
        stPlmnIdWithRat.stPlmnId.ulMcc  = pstGetGeoRslt->stGetGeoPlmn.ulMcc;
        stPlmnIdWithRat.stPlmnId.ulMnc  = pstGetGeoRslt->stGetGeoPlmn.ulMnc;

        /* ֪ͨCSS��ǰMCC */
        NAS_MMC_SndCssCurrGeoInd(VOS_FALSE, 1, &(pstGetGeoRslt->stGetGeoPlmn));
    }
    else
    {
        stPlmnIdWithRat.stPlmnId.ulMcc  = NAS_MML_INVALID_MCC;
        stPlmnIdWithRat.stPlmnId.ulMnc  = NAS_MML_INVALID_MNC;
    }

    stPlmnIdWithRat.enRat = pstRatList->aucRatPrio[0];

    NAS_MMC_SetGeoPlmn(&stPlmnIdWithRat);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedStartAvailableTimer_PlmnSelectionRsltSucc
 ��������  : �������Ϊ�ɹ�ʱ�ж��Ƿ���Ҫ����available��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����
             VOS_FALSE:����Ҫ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2013��11��26��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedStartAvailableTimer_PlmnSelectionRsltSucc(VOS_VOID)
{
    VOS_UINT8                           ucCsAttachAllowFlg;
    VOS_UINT8                           ucPsAttachAllowFlg;
    VOS_UINT32                          ulIsUsimStatusValid;
    VOS_UINT8                           ucSvlteSupportFlg;
    VOS_UINT8                           ucLcEnableFlg;

    ucCsAttachAllowFlg  = NAS_MML_GetCsAttachAllowFlg();
    ucPsAttachAllowFlg  = NAS_MML_GetPsAttachAllowFlg();
    ulIsUsimStatusValid = NAS_MML_IsUsimStausValid();
    ucSvlteSupportFlg   = NAS_MML_GetSvlteSupportFlag();
    ucLcEnableFlg       = NAS_MML_GetLcEnableFlg();

    /* SVLTE��C+L��̬ʱ������ģʽ(PS Only)��Ҫ����Avaliable��ʱ�� */
    if ( (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
      && (VOS_FALSE == ucCsAttachAllowFlg)
      && (VOS_FALSE == ucPsAttachAllowFlg)
      && (VOS_TRUE == ulIsUsimStatusValid)
      && ((VOS_TRUE == ucSvlteSupportFlg)
       || (VOS_TRUE == ucLcEnableFlg)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcPlmnSelectionRsltSucc_Initial
 ��������  : INITIALʱ�յ��ڲ���ѡ��״̬�����Ϊ�ɹ��Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��20��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��10��27��
   ��    ��   : b00269685
   �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
 3.��    ��   : 2015��4��17��
   ��    ��   : w00176964
   �޸�����   : CDMA 1X Iteration 10 Modified:add lte coverage flg and notify mscc
 4.��    ��   : 2015��5��25��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0����

*****************************************************************************/
VOS_VOID NAS_MMC_RcvMmcPlmnSelectionRsltSucc_Initial(
    VOS_UINT8                           ucLteCoverFlg
)
{
    NAS_MML_BG_SEARCH_CFG_INFO_STRU    *pstBgSearchCfg       = VOS_NULL_PTR;

    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);

    pstBgSearchCfg       = NAS_MML_GetBgSearchCfg();

    /* �������ע��ɹ�����Ҫ�ж��Ƿ���Ҫ����HPLMN��ʱ�� */
    if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
    {
        /* ������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());


        /* HPLMN TIMER�����¼��ϱ� */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


        /* ��HPLMN������������Ϊ���״����� */
        NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
    }
    else
    {
        /* ���綨�ƣ���ǿ��Hplmn�������Դ�ʱ����������Ҫ����
           HPLMN��ʱ��,����������ʱ,��Ϊ�����״�����HPLMN��ʱ�� */
        if (VOS_TRUE == pstBgSearchCfg->ucEnhancedHplmnSrchFlg)
        {
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
        }
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
    {
        /* ������ʱ�� */
        if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
        {
            NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
            NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
        }
    }
    /* ��ǰ��������ʱ��Available Timer������������ */
    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
        NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

        NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

        /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
        NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
        /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

        /* ���ݲ�ͬ�ķ��ؽ������MSCC�ϱ�����ָ�������Ľ��������RaomingBroker�ϱ� */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NORMAL_SERVICE, ucLteCoverFlg);
    }
    else
    {
        /* ���ݲ�ͬ�ķ��ؽ������MSCC�ϱ�����ָ�������Ľ��������RaomingBroker�ϱ� */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE, ucLteCoverFlg);

        if (VOS_TRUE == NAS_MMC_IsNeedStartAvailableTimer_PlmnSelectionRsltSucc())
        {
            if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
            {
                /* ���� availble timer��ǰ�����Ĵ�����ncell�������� */
                NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
                (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */
            }
        }
    }
}
/* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

/* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcPlmnSelectionRsltFail_Initial
 ��������  : INITIALʱ�յ��ڲ���ѡ��״̬�����Ϊʧ�ܵĴ���
 �������  : pstPlmnSelectionRslt   --�������
             ucLteCoverFlg          --LTE ���Ǳ��
 �������  : ��
 �� �� ֵ  : ��:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��11��
   ��    ��   : c00318887
   �޸�����   : Ԥ��Ƶ�������Ż������ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_RcvMmcPlmnSelectionRsltFail_Initial(
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstPlmnSelectionRslt,
    VOS_UINT8                                               ucLteCoverFlg
)
{
    NAS_MML_CONN_STATUS_INFO_STRU                          *pstConnStatus        = VOS_NULL_PTR;

    pstConnStatus           = NAS_MML_GetConnStatus();

    /* CS���е�ǰ�н�������ҵ����� */
    if ( (VOS_TRUE == NAS_MML_GetCsEmergencyServiceFlg())
      && ((VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)) )
    {
        /* �������Ч����Available��ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);

        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            /* ���� availble timer��ǰ�����Ĵ�����ncell�������� */
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

        }

        /* ���ݲ�ͬ�ķ��ؽ������MSCC�ϱ�����ָ�������Ľ��������RaomingBroker�ϱ� */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE, ucLteCoverFlg);

        /* ֻ����פ��̬��֪ͨAPS��ǰ�Ľ��뼼��,��פ��̬��PDP�Ѿ����������
           ֪ͨAPS��ǰ���뼼��ΪW/Lʱ,APS����ȥ����SNDCP�������ص�G���޷��ָ�
           ���� */
        if (NAS_MMC_SPEC_PLMN_SEARCH_STOP == NAS_MMC_GetSpecPlmnSearchState())
        {
            NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                     NAS_MML_GetSimPsRegStatus());
        }

        return;
    }

    /* �����ǰ����NO RF����Ǩ�Ƶ�OOC״̬ */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_RF, ucLteCoverFlg);

        /* ������״̬���ϱ�����״̬��Ǩ�Ƶ�ooc������available��ʱ�� */
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */


        return;
    }

    /* ���κ����縲�� */
    if (0 == pstPlmnSelectionRslt->ulRatNum)
    {
        /* ������ */
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(pstPlmnSelectionRslt->ulPlmnSearchScene);
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */

        /* ���ݲ�ͬ�ķ��ؽ������MSCC�ϱ�����ָ�������Ľ��������RaomingBroker�ϱ� */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE, ucLteCoverFlg);

    }
    else
    {
        /* �����縲�ǵĴ��� */
        NAS_MMC_ProcOutOfService_L1Main(pstPlmnSelectionRslt);

        /* ���ݲ�ͬ�ķ��ؽ������MSCC�ϱ�����ָ�������Ľ��������RaomingBroker�ϱ� */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_LIMITED_SERVICE, ucLteCoverFlg);
    }

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
    return;
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */

}

/* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcPlmnSelectionRslt_Initial
 ��������  : INITIALʱ�յ��ڲ���ѡ��״̬���������
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��9��23��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase II �����ȼ���������

 3.��    ��   : 2011��10��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II-2 ����HPLMN TIMER���¼��ϱ�

 4.��    ��   : 2011��12��1��
   ��    ��   : w00167002
   �޸�����   : DTS2011112308343: ��ѡ��״̬���ظ����Ϊʧ�ܣ�����ǰ�н���
                 ����ҵ������������������ʱ����
 5.��    ��   : 2011��12��20��
   ��    ��   : h44270
   �޸�����   : �˳�Plmen selection״̬�������Ϊ�ɹ�ʱ�����͵�ǰ����������

 6.��    ��   : 2011��11��30��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase IV����:disable/enable ����

 7.��    ��   : 2012��9��20��
   ��    ��   : z40661
   �޸�����   : DTS2012082006273,δ֪ͨLģdisableʱ,���ý�Lģ������������

 8.��    ��   : 2012��10��23��
   ��    ��   : w00176964
   �޸�����   : DTS2012101205055:פ��G����̬�³�ʱ�䶪��,�����������ٴ�����L����
                ʧ�ܶ�����,NAS����С���ָ����������ָ�
 9.��    ��   : 2012��11��7��
   ��    ��   : l00167671
   �޸�����   : DTS2012110607212: availble��ʱ����ʱ�������ɹ�,���ܽ��ж�ʱ������
10.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
11.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
12.��    ��   : 2013��11��23��
   ��    ��   : z00161729
   �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
13.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
                �����һ�TL������Ӧ������������һء�
14.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search���Ե���:����High_Prio_rat_hplmn��ʱ������������
15.��    ��   : 2014��3��7��
   ��    ��   : f00261443
   �޸�����   : DTS2014022703617:����ʧ��ʱ�ж��Ƿ�������No Rf���£������No Rf�ϱ� ��������϶���������ʧ��
16.��    ��   : 2013��4��8��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:�����NO RFǨ�Ƶ�OOC
17.��    ��   : 2014��1��27��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
18.��    ��   : 2014��4��14��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����ʱ���·���״̬
19.��    ��   : 2015��4��17��
   ��    ��   : w00176964
   �޸�����   : CDMA 1X Iteration 10 Modified:add lte coverage flg and notify mscc
20.��    ��   : 2015��5��30��
   ��    ��   : l00324781
   �޸�����   : CDMA 1X Iteration 12: plmn�������ؽ��������hrpd��mmc��ǰ״̬��ΪDEACT
21.��    ��   : 2015��08��25��
   ��    ��   : m00312079
   �޸�����   : DTS2015082004682:�����������ԭ��ֵNAS_MSCC_PIF_PLMN_SELECTION_RESULT_L2C
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcPlmnSelectionRslt_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstPlmnSelectionRslt = VOS_NULL_PTR;

    VOS_UINT8                                               ucLteCoverFlg;

    pstPlmnSelectionRslt = (NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU *)pstMsg;

    ucLteCoverFlg = NAS_MMC_GetLteCoverageFlg_L1Main(pstPlmnSelectionRslt);

    NAS_MMC_SetRegRsltAdditionalAction_L1Main();

    /* ����ע��ɹ�,Ǩ�Ƶ�ON PLMN */
    if (NAS_MMC_PLMN_SELECTION_SUCC == pstPlmnSelectionRslt->enResult)
    {
        NAS_MMC_RcvMmcPlmnSelectionRsltSucc_Initial(ucLteCoverFlg);
    }
    else if (NAS_MMC_PLMN_SELECTION_FAIL == pstPlmnSelectionRslt->enResult)
    {
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
        NAS_MMC_RcvMmcPlmnSelectionRsltFail_Initial(pstPlmnSelectionRslt, ucLteCoverFlg);
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */
    }

    else if (NAS_MMC_PLMN_SELECTION_ABORTED == pstPlmnSelectionRslt->enResult)
    {
        /* ���ݲ�ͬ�ķ��ؽ������MSCC�ϱ�����ָ�������Ľ��������RaomingBroker�ϱ� */
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_INTERRUPT, ucLteCoverFlg);

        /* �����ǰפ�� Ӧ�ø���L1״̬ */
        if ( NAS_MMC_SPEC_PLMN_SEARCH_STOP == NAS_MMC_GetSpecPlmnSearchState())
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);
        }
    }
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */

#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
    else if (NAS_MMC_PLMN_SELECTION_INTER_SYS_HRPD == pstPlmnSelectionRslt->enResult)
    {

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_NO_SERVICE, ucLteCoverFlg);
#else
        NAS_MMC_SndMsccPlmnSelectionRsltInd(NAS_MSCC_PIF_PLMN_SELECTION_RESULT_L2C, ucLteCoverFlg);
#endif

        NAS_MMC_StopAllTimer();

        /* �޸� NAS_MMC_L1_STA_OOC--> NAS_MMC_L1_STA_DEACT�� ������ѡ��hrpd, lte������ģ
           mmc״̬Ǩ�Ƶ�NAS_MMC_L1_STA_DEACT  */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);

        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);

        return VOS_TRUE;
    }
#endif
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */
    else
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcPlmnSelectionRslt_Initial:ENTERED");
    }

    /* ֻ����פ��̬��֪ͨAPS��ǰ�Ľ��뼼��,��פ��̬��PDP�Ѿ����������
       ֪ͨAPS��ǰ���뼼��ΪW/Lʱ,APS����ȥ����SNDCP�������ص�G���޷��ָ�
       ���� */
    if (NAS_MMC_SPEC_PLMN_SEARCH_STOP == NAS_MMC_GetSpecPlmnSearchState())
    {
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCmServiceInd_Initial
 ��������  : INITIALʱ�յ�MMģ���������ָʾ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��15��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��8��5��
   ��    ��   : w00176964
   �޸�����   : V7R1 PhaseII ����
 3.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�,֧��L��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCmServiceInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_CM_SERVICE_IND_STRU          *pstServiceIndMsg;

    /* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList = VOS_NULL_PTR;

    pstPrioRatList      = NAS_MML_GetMsPrioRatList();

    /* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */

    pstServiceIndMsg    = (MMCMM_CM_SERVICE_IND_STRU*)pstMsg;

    if (MM_EMERGENCY_CALL_TRUE == pstServiceIndMsg->ulEmcFlg)
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
        /* ����ANYCELL����,������Ҫanycell�ѵĽ��뼼��ΪGU,����˳����syscfg���� */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        /* Modified by z00161729 for DCM�����������������, 2012-8-14, end */
    }

    return VOS_TRUE;
}


#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsfbAbortInd_Initial
 ��������  : INITIALʱ�յ�MMģ���������ָʾ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��7��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCsfbAbortInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        /* ���õ�ǰפ�������ϵͳģʽΪBUTT  */
        NAS_MML_SetCurrSysSubMode(NAS_MML_RRC_SYS_SUBMODE_BUTT);
    }

    /* ���첢�����ڲ�������Ϣ:����CSFB ABORT */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_ABORT, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsfbAbortInd_Initial
 ��������  : INITIALʱ�յ�MMģ��MMCMM_PLMN_SEARCH_IND�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��11��30��
    ��    ��   : s00217060
    �޸�����   : DTS2015102401241�޸ģ���ϵͳ��GUʧ�ܣ����˵�LTE�����̲���ϵ
                 ͳ��Ϣ����״̬��

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmPlmnSearchInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_PLMN_SEARCH_IND_STRU         *pstPlmnSearchInd;

    pstPlmnSearchInd = (MMCMM_PLMN_SEARCH_IND_STRU *)pstMsg;

    /* ��ҵ��ʱ���ض���ʧ�ܻ��˵�LTE�����̲���LTE��ϵͳ��Ϣ���˳���ϵͳ״̬����
       ��Ҫ��NAS_MMC_L1_STA_INITIAL����������Ϣ */
    if ( MM_MMC_PLMN_SEARCH_TYPE_CSFB_BACK_LTE == pstPlmnSearchInd->enPlmnSearchType )
    {
        return NAS_MMC_ProcCsfbRedirFailBackLte_L1Main(ulEventType, pstMsg);
    }

    /* CSFB�����г�����������ע�ᱻ�ܴ���������,�û��Ҷϵ绰�������� */
    if ( MM_MMC_PLMN_SEARCH_TYPE_CSFB_END == pstPlmnSearchInd->enPlmnSearchType )
    {
        if ( NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState() )
        {
            /* ���õ�ǰפ�������ϵͳģʽΪBUTT  */
            NAS_MML_SetCurrSysSubMode(NAS_MML_RRC_SYS_SUBMODE_BUTT);
        }

        /* ���첢�����ڲ�������Ϣ:����CSFB ABORT */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_END, VOS_NULL_PTR, 0);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcInterDplmnSetReq_Initial
 ��������  : INITIALʱ�յ�MSCCģ��ID_MSCC_MMC_DPLMN_SET_REQ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��10��21��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcInterDplmnSetReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���첢�����ڲ�������Ϣ:����NAS_MMC_PLMN_SEARCH_SCENE_DPLMN_SET */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_DPLMN_SET, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvAreaLostInd_Initial
 ��������  : On plmn������յ�������Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_AREA_LOST_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��4��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��4��4��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF Ǩ�Ƶ�OOC
  3.��    ��   : 2014��1��28��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���

  4.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
  5.��    ��   : 2014��5��31��
    ��    ��   : y00245242
    �޸�����   : �޸ķ���״̬�ϱ�

  6.��    ��   : 2015��3��9��
    ��    ��   : wx270776
    �޸�����   : DTS2015031107328, �޸�NO_SERVICE�ϱ�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvAreaLostInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRatType;

    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */

    /* ɾ��NV�еĲ�ͬ�������Plmn */
    NAS_MMC_DelDiffMccRplmnInNv_L1Main();

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* �����ǰΪNO RF�˳��������� */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ������״̬���ϱ�����״̬��Ǩ�Ƶ�ooc������available��ʱ�� */
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */
        return VOS_TRUE;
    }

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */

    enCurRatType = NAS_MML_GetCurrNetRatType();

    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRatType)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRatType) )
    {
        NAS_MMC_SndMmCoverageLostInd();

        NAS_MMC_SndGmmCoverageLostInd();
    }

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSuspendInd_Initial
 ��������  : ��INITIALʱ���յ�WAS/GAS/LMM SUSPEND IND ��Ϣ�Ĵ���
 �������  : ulEventType:��ϵͳ��ѡ��Ϣ����
              pstMsg: ��ϵͳ��ѡ��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSuspendInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֱ�ӻظ�ʧ�� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcInterPlmnListReq_OnPlmn
 ��������  : ON PLMN���յ��ڲ�LIST�����Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_INTER_PLMN_LIST_REQ��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��17��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II LIST����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcInterPlmnListReq_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    /* ����LIST����״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�WAS/GAS SUSPEND IND ��Ϣ�Ĵ���
 �������  : ulEventType:��ϵͳ��ѡ��Ϣ����
              pstMsg: ��ϵͳ��ѡ��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : ������ϵͳ״̬��ʱ����Ϊ��ǰ�����磬��ʱAPS����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmSuspendInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST             *pstSuspendMsg = VOS_NULL_PTR;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ��������ͬ��״̬�� */
    switch(pstSuspendMsg->ucSuspendCause)
    {
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            break;

        case MMC_SUSPEND_CAUSE_PLMNSEARCH:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_OOS);
            break;
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            break;

        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendInd_OnPlmn:ENTERED");
            break;
    }

    if ( (MMC_SUSPEND_CAUSE_BUTT != pstSuspendMsg->ucSuspendCause)
      && (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK != pstSuspendMsg->ucSuspendCause) )
    {
        NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                 NAS_MML_GetSimPsRegStatus());
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCmServiceInd_Ooc
 ��������  : OOCʱ�յ�MMģ�����ָʾ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��29��
   ��    ��   : z00161729
   �޸�����   : DSDSҵ���ز�ʱno rfδ������������ҵ��ʧ�ܣ�mm��no cell available
                ״̬no rfʱ��mmc����cm service ind��������
 2.��    ��   : 2015��10��08��
   ��    ��   : zwx247453
   �޸�����   : ���Coverity�澯
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCmServiceInd_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_CM_SERVICE_IND_STRU          *pstCmServiceInd = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;

    PS_MEM_SET(&stPrioRatList, 0x00, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    pstCmServiceInd = (MMCMM_CM_SERVICE_IND_STRU *)pstMsg;
    PS_MEM_CPY(&stPrioRatList, NAS_MML_GetMsPrioRatList(), sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */

    PS_MEM_SET(&stAnycellSrchRatList, 0, sizeof(stAnycellSrchRatList));

    if (MM_CS_SERV_NOT_EXIST == pstCmServiceInd->ulCsServFlg)
    {
        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* �������д���anycell����������ҵ�񴥷�rf enable �������� */
        if (MM_EMERGENCY_CALL_TRUE == pstCmServiceInd->ulEmcFlg)
        {
            /* ҵ���ط����������NO RF�����Ϣ���򴥷�����  */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
            /* ����ANYCELL����,������Ҫanycell�ѵĽ��뼼��ΪGU,����˳����syscfg���� */
            NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(&stPrioRatList, &stAnycellSrchRatList);
            /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */

            NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);

            /*ֹͣAvailable��ʱ��*/
            NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);
            return VOS_TRUE;
        }

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* ����������Ϣ */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE, VOS_NULL_PTR, 0);

        /*ֹͣAvailable��ʱ��*/
        NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);
    }
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-8, begin */
    else
    {
        /* �������д���anycell����������ҵ�񲻴������� */
        if (MM_EMERGENCY_CALL_TRUE == pstCmServiceInd->ulEmcFlg)
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            NAS_MML_SortSpecRatPrioHighest(NAS_MMC_GetLastCampedPlmnRat(), &stPrioRatList);

            /* ����ANYCELL����,������Ҫanycell�ѵĽ��뼼��ΪGU,����˳����syscfg���� */
            NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(&stPrioRatList, &stAnycellSrchRatList);

            NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);

            /*ֹͣAvailable��ʱ��*/
            NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

            return VOS_TRUE;
        }

    }

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-8, end */

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCmServiceInd_OnPlmn
 ��������  : ON PLMNʱ�յ�MMģ�����ָʾ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��10��18��
   ��    ��   : t00212959
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��12��
   ��    ��   : l65478
   �޸�����   : DTS2012111202844,�б����������б�LU��ֹ�����б�����ʧ��
 3.��    ��   : 2015��9��26��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCmServiceInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCsServFlg;

    ulCsServFlg = NAS_MML_GetCsServiceExistFlg();

    /* �յ�CSҵ��ʱ�������������û��б��Ѷ�ʱ���������У�ATû���ͷţ����ܼ�ʱ��Ӧ*/
    if ((NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST))
     && (VOS_TRUE == ulCsServFlg))
    {
        /* ֹͣTI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST */
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST);

        /* ��MSCC����REJ */
        NAS_Mmc_SndMsccPlmnListRej();
    }

#if (FEATURE_ON == FEATURE_CSG)
    if ((NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH))
     && (VOS_TRUE == ulCsServFlg))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH);

        /* ��MSCC����rej */
        NAS_MMC_SndMsccCsgListSearchRej();
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCmServiceInd_OnPlmn
 ��������  : ON PLMNʱ�յ�MMģ������ָʾ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��18��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��6��17��
   ��    ��   : w00176964
   �޸�����   : DTS2014061606181:���ֽ������г�����Ҫ����anycell����
 3.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve�޸�
 4.��    ��   : 2015��10��08��
   ��    ��   : zwx247453
   �޸�����   : ���Coverity�澯
 5.��    ��   : 2015��11��30��
   ��    ��   : s00217060
   �޸�����   : DTS2015102401241�޸ģ���ϵͳ��GUʧ�ܣ����˵�LTE��������Ϣ��
                 �˳�״̬��

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmPlmnSearchInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_PLMN_SEARCH_IND_STRU                             *pstPlmnSearchInd;

    pstPlmnSearchInd = (MMCMM_PLMN_SEARCH_IND_STRU *)pstMsg;

    /* ���MM��֪ͨLMM CSFB��L��ѡ��GUʧ�ܻ��˵�L��MMC��MM����L��resume ind
       ��MM��MMC���͵���������ΪCSFB���� */
    if ( MM_MMC_PLMN_SEARCH_TYPE_CSFB_BACK_LTE == pstPlmnSearchInd->enPlmnSearchType )
    {
        /* ��ȡ���� */
        return NAS_MMC_ProcCsfbRedirFailBackLte_L1Main(ulEventType, pstMsg);
    }

    if (MM_MMC_PLMN_SEARCH_TYPE_CSFB_END == pstPlmnSearchInd->enPlmnSearchType)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer_CsfbEnd())
        {
            /* ������ʱ����ʱ��Ϊ5s */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, 5*NAS_MML_ONE_THOUSAND_MILLISECOND);
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmRrConnInfoInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�MM���͵���������Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg: MMCMM_RR_CONN_INFO_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II����

  3.��    ��   : 2011��10��12��
    ��    ��   : zhoujun 40661
    �޸�����   : CTX��������Ҫ�����ı������ж��Ƿ���Ҫ����

  4.��    ��   : 2011��11��17��
    ��    ��   : w00167002
    �޸�����   : DTS2011111603447:���л���������Ĵ���
  5.��    ��   : 2012��5��24��
    ��    ��   : w00176964
    �޸�����   : GUL BG��Ŀ����:�������ָ������ʱ���ж����Ƿ��Ѿ�����������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrConnInfoInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    VOS_UINT32                          ulRrcConnExistFlag;

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* ��Ҫ��ע��ʧ�ܵ�����Ҫ������Ϊ���� */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* ���ע��ʧ�ܲ���Ҫ��������,���ж��Ƿ��л����������־ */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmSignalingStatusInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�GMM���͵���������Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg: MMCGMM_SIGNALING_STATUS_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II����

  3.��    ��   : 2011��10��12��
    ��    ��   : zhoujun 40661
    �޸�����   : CTX��������Ҫ�����ı������ж��Ƿ���Ҫ����

  4.��    ��   : 2011��11��17��
    ��    ��   : w00167002
    �޸�����   : DTS2011111603447:���л���������Ĵ���
  5.��    ��   : 2012��5��24��
    ��    ��   : w00176964
    �޸�����   : GUL BG��Ŀ����:�������ָ������ʱ���ж����Ƿ��Ѿ�����������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmSignalingStatusInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    VOS_UINT32                          ulRrcConnExistFlag;

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* ��Ҫ��ע��ʧ�ܵ�����Ҫ������Ϊ���� */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* ���ע��ʧ�ܲ���Ҫ��������,���ж��Ƿ��л����������־ */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmTbfRelInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�TBF�ͷ�����Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg: MMCGMM_TBF_REL_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II����

  3.��    ��   : 2011��10��12��
    ��    ��   : zhoujun 40661
    �޸�����   : CTX��������Ҫ�����ı������ж��Ƿ���Ҫ����

  4.��    ��   : 2011��11��17��
    ��    ��   : w00167002
    �޸�����   : DTS2011111603447:���л���������Ĵ���
  5.��    ��   : 2012��5��24��
    ��    ��   : w00176964
    �޸�����   : GUL BG��Ŀ����:�������ָ������ʱ���ж����Ƿ��Ѿ�����������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmTbfRelInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    VOS_UINT32                          ulRrcConnExistFlag;

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* ��Ҫ��ע��ʧ�ܵ�����Ҫ������Ϊ���� */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* ���ע��ʧ�ܲ���Ҫ��������,���ж��Ƿ��л����������־ */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();


    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmRrRelInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�MM�����ͷ�����Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg: MMCMM_RR_REL_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II����

 3.��    ��   : 2011��10��12��
   ��    ��   : zhoujun 40661
   �޸�����   : CTX��������Ҫ�����ı������ж��Ƿ���Ҫ����
 4.��    ��   : 2011��11��17��
    ��    ��   : w00167002
    �޸�����   : DTS2011111603447:���л���������Ĵ���
  5.��    ��   : 2012��5��24��
    ��    ��   : w00176964
    �޸�����   : GUL BG��Ŀ����:�������ָ������ʱ���ж����Ƿ��Ѿ�����������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrRelInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    VOS_UINT32                          ulRrcConnExistFlag;

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* ��Ҫ��ע��ʧ�ܵ�����Ҫ������Ϊ���� */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* ���ע��ʧ�ܲ���Ҫ��������,���ж��Ƿ��л����������־ */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();


    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelIndInMmcIdle
 ��������  : ON PLMNʱ�յ�AS���͵������ͷ�����
 �������  : ulEventType:��Ϣ����
             pstMsg: RRMM_REL_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II����

  3.��    ��   : 2011��10��12��
    ��    ��   : zhoujun 40661
    �޸�����   : CTX��������Ҫ�����ı������ж��Ƿ���Ҫ����

  4.��    ��   : 2011��11��17��
    ��    ��   : w00167002
    �޸�����   : DTS2011111603447:���л���������Ĵ���
  5.��    ��   : 2012��5��24��
    ��    ��   : w00176964
    �޸�����   : GUL BG��Ŀ����:�������ָ������ʱ���ж����Ƿ��Ѿ�����������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    VOS_UINT32                          ulRrcConnExistFlag;

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* ��Ҫ��ע��ʧ�ܵ�����Ҫ������Ϊ���� */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* ���ע��ʧ�ܲ���Ҫ��������,���ж��Ƿ��л����������־ */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCmServiceRejectInd_OnPlmn
 ��������  : ON PLMNʱ�յ�CSҵ���¿���Ч����Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg: MMCMM_CM_SERVICE_REJECT_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II����
 3.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
 4.��    ��   : 2014��4��24��
   ��    ��   : w00242748
   �޸�����   : DTS2014042405819:�޿�״̬�£�����������#5������ANYCELL�ѣ�������״̬��
                ���·�RRMM_UE_OOC_STATUS_NOTIFY_IND���������粻���·�CM SERVICE REJ
 5.��    ��   : 2014��4��29��
   ��    ��   : s00261364
   �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvCmServiceRejectInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    MMCMM_CM_SERVICE_REJECT_IND_STRU   *pstRcvMsg = VOS_NULL_PTR;
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;

    pstRcvMsg           = ( MMCMM_CM_SERVICE_REJECT_IND_STRU* )pstMsg;

#endif
    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */

#if (FEATURE_ON == FEATURE_LTE)
    /* ��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨ */
    stActionRslt.enProcType     = NAS_MML_PROC_CM_SER;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstRcvMsg->ulCause;
    stActionRslt.ulAttemptCount = 0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        if ( VOS_FALSE == NAS_MML_IsRrcConnExist() )
        {
            /* Ǩ�Ƶ�Initial״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* ���ݽ���еĽ��뼼��������Ϣ����anycell״̬��������������ǰ���뼼�� */
            NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        }
        else
        {
            NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvNetworkDetachInd_OnPlmn
 ��������  : On plmn������յ�GMMע�����Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCGMM_NETWORK_DETACH_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��28��
    ��    ��   : luokaihui / l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II����
  3.��    ��   : 2012��2��13��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  4.��    ��   : 2013��12��25��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
  5.��    ��   : 2015��6��6��
    ��    ��   : s00217060
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvNetworkDetachInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU                         *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    VOS_UINT32                                              ulRrcConnExistFlag;

    pstDetachMsg        = (MMCGMM_NETWORK_DETACH_IND_STRU *)pstMsg;

    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

#if   (FEATURE_ON == FEATURE_LTE)
    /* ��LMM����detach�����Ϣ */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
        (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    /* ����Ҫ����ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ����������ֹͣavailable��ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

            NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
            NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

        }

        return VOS_TRUE;
    }

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* �������� */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiAvailTimerExpired_HistorySearch_OnPlmn
 ��������  : available��ʱ����ʱ�����history�ѵĴ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_RcvTiAvailTimerExpired_HistorySearch_OnPlmn(VOS_VOID)
{
    /* ����Ϊ initail ״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* �����ڲ�������Ϣ */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH,
                                  VOS_NULL_PTR, 0);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiAvailTimerExpired_PrefBandSearch_OnPlmn
 ��������  : available��ʱ����ʱ�����PrefBand�ѵĴ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��09��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_RcvTiAvailTimerExpired_PrefBandSearch_OnPlmn(VOS_VOID)
{
    /* ����Ϊ initail ״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* �����ڲ�������Ϣ */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH,
                                  VOS_NULL_PTR, 0);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiAvailTimerExpired_NCellSearch_OnPlmn
 ��������  : ����NCELL�Ѵ���
 �������  : VOS_VOID
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��27��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL����
 3.��    ��   : 2014��2��25��
   ��    ��   : w00242748
   �޸�����   : DTS2014022110695������NCELL�����Ŀ����ԣ���ǰ����TD������ʱ��
                Ҳ��ȥ����LTE����֮��Ȼ������֮�����������ڲ��ڣ�����Ҫ����TD/LTE
*****************************************************************************/
VOS_VOID  NAS_MMC_RcvTiAvailTimerExpired_NcellSearch_OnPlmn(VOS_VOID)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pastSearchedPlmnListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList        = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulRatCnt;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn     = VOS_NULL_PTR;

    /* ��ȡ���ȼ��б� */
    pstRatPrioList     = NAS_MML_GetMsPrioRatList();

    /* ��ȡEHPLMN */
    pstEHPlmnInfo   = NAS_MML_GetSimEhplmnList();
    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

    /* �Զ�����ģʽ���hplmn���ֶ�����ģʽ����û�ָ������ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        stPlmnId.ulMcc = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc;
        stPlmnId.ulMnc = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc;
    }
    else
    {
        stPlmnId.ulMcc = pstUserSpecPlmn->stPlmnId.ulMcc;
        stPlmnId.ulMnc = pstUserSpecPlmn->stPlmnId.ulMnc;
    }

    pastSearchedPlmnListInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    /* �����ڴ�ʧ�� */
    if (VOS_NULL_PTR == pastSearchedPlmnListInfo)
    {
        return;
    }

    PS_MEM_SET(pastSearchedPlmnListInfo, 0, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        pastSearchedPlmnListInfo[ulRatCnt].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    NAS_MMC_InitSearchedPlmnListInfo(pastSearchedPlmnListInfo);

    /* ����T��L������Ƶ����Ϣ���������б�,�����������Ϊ0��Ҳ��Ҫ���������б� */
    for (ulRatCnt =0; ulRatCnt< pstRatPrioList->ucRatNum; ulRatCnt++)
    {
        /* ��ʼ���ϱ��Ľ��뼼���б� */
        pastSearchedPlmnListInfo[ulRatCnt].enRatType        = pstRatPrioList->aucRatPrio[ulRatCnt];
        pastSearchedPlmnListInfo[ulRatCnt].ulHighPlmnNum    = 0;
        pastSearchedPlmnListInfo[ulRatCnt].ulLowPlmnNum     = 0;

        if (NAS_MML_NET_RAT_TYPE_LTE == pastSearchedPlmnListInfo[ulRatCnt].enRatType)
        {
            pastSearchedPlmnListInfo[ulRatCnt].ulHighPlmnNum            = 1;
            pastSearchedPlmnListInfo[ulRatCnt].astHighPlmnList[0].ulMcc = stPlmnId.ulMcc;
            pastSearchedPlmnListInfo[ulRatCnt].astHighPlmnList[0].ulMnc = stPlmnId.ulMnc;
        }

        if (NAS_MML_NET_RAT_TYPE_WCDMA == pastSearchedPlmnListInfo[ulRatCnt].enRatType)
        {
            pastSearchedPlmnListInfo[ulRatCnt].ulHighPlmnNum    = 1;
            pastSearchedPlmnListInfo[ulRatCnt].astHighPlmnList[0].ulMcc = stPlmnId.ulMcc;
            pastSearchedPlmnListInfo[ulRatCnt].astHighPlmnList[0].ulMnc = stPlmnId.ulMnc;
        }
    }

    /* ��ʱ����ʱ������Ϊ initail ״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* ����������Ϣ */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH,
                                  pastSearchedPlmnListInfo, NAS_MML_MAX_RAT_NUM);

    PS_MEM_FREE(WUEPS_PID_MMC, pastSearchedPlmnListInfo);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiAvailTimerExpired_L1Main
 ��������  : ON PLMN��OOC��Available Timer ��ʱ����ʱ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_AVAILABLE_TIMER��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��27��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��9��20��
   ��    ��   : w00176964
   �޸�����   : V7R1 PhaseII �ڲ�LIST��������
 3.��    ��   : 2011��9��24��
   ��    ��   : w00166186
   �޸�����   : V7R1 PhaseII �ڲ�LIST��������
 4.��    ��   : 2011��12��20��
   ��    ��   : w00167002
   �޸�����   : DTS2011122001697: ��ǰ������������״̬��δ���й�������������
                �����ȼ�ָ������ʱ���߿���ָ����ʱ�����û�ָ���Ѵ�ϣ����û�
                ָ�����������ǰפ����������ͬ�������ȼ�����״̬���˳���
                �᲻�����û�ָ���ѡ�
 5.��    ��   : 2012��4��26��
   ��    ��   : w00176964
   �޸�����   : GUL BG��Ŀ����
 6.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 7.��    ��   : 2014��1��2��
  ��    ��   : z00234330
  �޸�����   : �����ǰʱGTLģʽ����gas�ϱ���������Ϣ����������Ϣ����ʱ��
             ����available timer����������������
 8.��    ��   : 2014��1��22��
   ��    ��   : w00167002
   �޸�����   : SVLTE��������Ŀ:����������ʱ����ʱʱ�򣬽���NO RF����������
 9.��    ��   : 2014��01��17��
   ��    ��   : l00198894
   �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
10.��    ��   : 2013��3��28��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:NO RFʱ��ʱ����ʱ������ʱ����������
11.��    ��   : 2013��4��4��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬����������
12.��    ��   : 2014��4��21��
   ��    ��   : w00167002
   �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF,������Ԥ������д���
13.��    ��   : 2015��5��25��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiAvailTimerExpired_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �Ƿ���Ҫ�������� */
    if (VOS_TRUE == NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main())
    {
        return NAS_MMC_ProcTiAvailableTimerExpiredTriggerPlmnSearch_L1Main();

    }

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmPsStatusInd_L1Main
 ��������  : ON PLMN/INITIAL/OOC���յ�RRM֪ͨ����Դ����֪ͨʱ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_RRM_PS_STATUS_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��22��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��29��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:NO RF�������RRM����ȥע�ᣬֻ����GU������LTE����������NO RF

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmPsStatusInd_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���յ�RRM����Դ����֪ͨʱ����Ҫ�жϵ�ǰ�Ƿ����NO RF��ǣ���������ڣ��򲻴������� */
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return VOS_TRUE;
    }

    /* �������NO RF�����Ϣ���򴥷�����  */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* ����������Ϣ */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE, VOS_NULL_PTR, 0);

    /*ֹͣAvailable��ʱ��*/
    NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmPsStatusInd_L1Main_Deactive
 ��������  : deactive���յ�RRM֪ͨ����Դ����֪ͨʱ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_RRM_PS_STATUS_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��28��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmPsStatusInd_L1Main_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return VOS_TRUE;
    }

    /* ��ǰ����NO RF ��MSCC͸����Ϣ,��������������MSCC�����Ƿ񴥷����� */
    NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

    /* ���õ�ǰRF���ñ��Ϊ:RF���� */
    NAS_MML_SetRfAvailFlg(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSysInfo_OnPlmn
 ��������  : On plmn������յ�W��ϵͳ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SYS_INFO_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��3��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��8��05��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IIȫ�ֱ�������
  3.��    ��   : 2012��6��16��
    ��    ��   : l00171473
    �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
  4.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
  5.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMMA
  6.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��

  7.��    ��   : 2014��1��18��
    ��    ��   : z00234330
    �޸�����   : dts2014011801513,������ϱ���ϵͳ��Ϣ�����п���û��Я��plmnid,
                 �˴��жϲ�û���ж�plmnid�Ƿ���Ч
  8.��    ��   : 2014��2��14��
    ��    ��   : z00161729
    �޸�����   : DTS2014021000537:sim��anycellפ��l��С��mmc�յ�ϵͳ��Ϣת��mmaʱӦ�ý���ֹ�����ʶ��ΪTRUE��
                 ���ϱ�pstransfer:1,������psǨ�Ƶ�modem0��l��ע�ᣬƹ��psǨ��

  9.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfo_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* פ��С���仯ʱ���ϱ�ϵͳ��Ϣ ,���ߴ�bar����bar */
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || ((VOS_TRUE == stOldPsRestrictInfo.ucRestrictRegister)
      && (VOS_FALSE == pstCurPsRestrictInfo->ucRestrictRegister)))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMSCCģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
    NAS_MMC_SndMmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(),VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGrrMmSysInfo_OnPlmn
 ��������  : On plmn������յ�G��ϵͳ��Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:GRRMM_SYS_INFO_IND��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��3��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��16��
    ��    ��   : l00171473
    �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
  3.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
  4.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMMA
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ

  7.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfo_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);

#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* פ��С���仯ʱ���ϱ�ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMSCCģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
    NAS_MMC_SndMmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_EnterOocStatus_OnPlmn
 ��������  : ����OOC��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��31��
    ��    ��   : z40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��11��9��
    ��    ��   : z40661
    �޸�����   : DRX Timer
  3.��    ��   : 2013��3��25��
    ��    ��   : z60575
    �޸�����   : DTS2013032501170���͹��ĺ���
  4.��    ��   : 2013��10��29��
    ��    ��   : z00234330
    �޸�����   : �͹��Ľӿں���  dts2013102911530
*****************************************************************************/
VOS_VOID  NAS_MMC_EnterOocStatus_OnPlmn( VOS_VOID )
{
    VOS_UINT32                          ulReceivePid;

#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndLmmUeOocStatusInd();
        /* ���������͹���ʱ����Ҫ��drx���� */
        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));

        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);
        return ;
    }
#endif

    if ( NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        ulReceivePid = UEPS_PID_GAS;
    }
    else if ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        ulReceivePid = WUEPS_PID_WRR;
    }
    else
    {
        return;
    }

    NAS_MMC_SndGuAsUeOocStatus(ulReceivePid);

    /* ���������͹���ʱ����Ҫ��drx���� */
    OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
    NAS_MMC_SndDrxTimerInfo(VOS_TRUE);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvAreaLostInd_OnPlmn
 ��������  : On plmn������յ�������Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_AREA_LOST_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��26��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II����
  3.��    ��   : 2012��04��07��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:DTS2012040106098,����CoverageLost��service���ϱ�˳���Ը���MMA��״̬��DeepSleep
  4.��    ��   : 2012��3��31��
    ��    ��   : z40661
    �޸�����   : V7R1�޸������͹���
  5.��    ��   : 2012��11��7��
    ��    ��   : l00167671
    �޸�����   : DTS2012110607212: availble��ʱ����ʱ�������ɹ�,���ܽ��ж�ʱ������
  6.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  7.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  8.��    ��   : 2013��7��15��
    ��    ��   : z00161729
    �޸�����   : DTS2013062406563:WAS����̬OOS,T305�����ڼ�ֻ���ڱ�ϵͳ���ѵ�Чplmn��
               ����פ������ϵͳ�������磬Ҳ������ϵͳ�½��������������޷��ܿ�����������ע�ᣬnas����޸�
  9.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
 10.��    ��   : 2013��4��4��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF Ǩ�Ƶ�OOC
 11.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
 12.��    ��   : 2014��5��31��
    ��    ��   : y00245242
    �޸�����   : �޸ķ���״̬�ϱ�
 13.��    ��   : 2015��3��9��
    ��    ��   : wx270776
    �޸�����   : DTS2015031107328, �޸�NO_SERVICE�ϱ�
 14.��    ��   : 2015��6��10��
    ��    ��   : w00242748
    �޸�����   : CDMA Iteration 15 modified
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvAreaLostInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stRatSrchList;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRatType;
    NAS_MMC_SEARCHED_TYPE_STRU          stNasSearchedType;

    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo = VOS_NULL_PTR;
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd = VOS_NULL_PTR;

    PS_MEM_SET(&stRatSrchList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));


    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;


    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */

    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

    /* ɾ��NV�еĲ�ͬ�������Plmn */
    NAS_MMC_DelDiffMccRplmnInNv_L1Main();

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* �����ǰΪNO RF�˳��������� */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ������״̬���ϱ�����״̬��Ǩ�Ƶ�ooc������available��ʱ�� */
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */




        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        return VOS_TRUE;
    }

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */

    /* ��TAF��������������, GU����MM/GMM/������ */
    enCurRatType = NAS_MML_GetCurrNetRatType();
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRatType)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRatType) )
    {
        NAS_MMC_SndMmCoverageLostInd();

        NAS_MMC_SndGmmCoverageLostInd();
    }

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);



    pstPlmnListInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                         sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    if (VOS_NULL_PTR == pstPlmnListInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvAreaLostInd_OnPlmn: ALLOC MEM FAIL!");
        return VOS_TRUE;

    }

    PS_MEM_SET(&stNasSearchedType, 0, sizeof(NAS_MMC_SEARCHED_TYPE_STRU));
    stNasSearchedType.ucHistorySearchedFlg  = pstAreaLostInd->stSearchedType.ucHistorySearchedFlg;
    stNasSearchedType.ucPrefBandSearchedFlg = pstAreaLostInd->stSearchedType.ucPrefBandSearchedFlg;
    stNasSearchedType.ucSpecSearchedFlg     = pstAreaLostInd->stSearchedType.ucSpecSearchedFlg;

    if (VOS_TRUE == NAS_MMC_IsNeedEnterOocStatusWhenAreaLost_OnPlmn(&stNasSearchedType))
    {
        NAS_MMC_EnterOocStatus_OnPlmn();

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_OOC);

        NAS_MMC_UpdateRegStateSpecPlmnSearch();

        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            /* ���� availble timer��ǰ�����Ĵ�����ncell�������� */
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */
        }
    }
    else
    {
        /*�յ�����ָʾ��Ǩ��״̬NAS_MMC_L1_STA_INITIAL,����������  */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        if (VOS_TRUE == NAS_MML_IsUsimStausValid())
        {
            NAS_MMC_InitSearchedPlmnListInfo(pstPlmnListInfo);

            /* ����area lost��Ϣ��������������ͺ͸ߵ�����plmn�����ڲ�ѡ����Ϣ */
            NAS_MMC_UpdateSearchedPlmnListInfo(&stNasSearchedType, &(pstAreaLostInd->PlmnIdList), pstPlmnListInfo);

            if(VOS_TRUE == NAS_MMC_IsInterNationalRoamingSearchRPLMN(NAS_MMC_GetLastCampedPlmnid()->ulMcc))
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG, pstPlmnListInfo, NAS_MML_MAX_RAT_NUM);
            }
            else
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST, pstPlmnListInfo, NAS_MML_MAX_RAT_NUM);
            }

        }
        else
        {
            /* ���춪������Ҫ�����Ľ��뼼���б� ��Anycell����ʱ����Ҫʹ��*/
            PS_MEM_CPY(&stRatSrchList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stRatSrchList);

            NAS_MMC_SndInterAnyCellSearchReq(&stRatSrchList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        }

    }

    /* �ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnListInfo);


    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcMmcSuspendRslt_OnPlmn
 ��������  : ��ON PLMNʱ���յ�MMCMMC_SUSPEND_RSLT_CNF��Ϣ�Ĵ���
 �������  : ulEventType:MMCMMC_SUSPEND_RSLT_CNF��Ϣ����
             pstMsg: MMCMMC_SUSPEND_RSLT_CNF��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2011��11��29��
    ��    ��   : w00166186
    �޸�����   : DTS2011101802330,OOS����������Ĵ���
  4.��    ��   : 2011��12��30��
    ��    ��   : l65478
    �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                 ���ݾ����ԭ��ֵ������
  5.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : �˳���ϵͳ״̬��ʱ��֪ͨAPS��ǰ��������
  6.��    ��   : 2013��9��17��
    ��    ��   : w00242748
    �޸�����   : DTS2013091404846 OOS�����У���������������OOS״̬��֮������Ӧ
                 �Ȳ�����Ҳ�����������
  7.��    ��   : 2013��4��8��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF Ǩ�Ƶ�OOC״̬
  8.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���

  9.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������

 10.��    ��   : 2015��5��30��
    ��    ��   : l00324781
    �޸�����   : CDMA 1X Iteration 12: ���ӹ��ܣ�CLģʽ�£�L2C�� lte��ѡ���ض���hrpd
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcMmcSuspendRslt_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRslt = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;

    /* Modified by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
    pstSuspendRslt  = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

/* ����((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))������ʽ��ԭ�е�CL��ͬ */
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE)))

    /* ��ѡ��HRPD��,MMC״̬Ǩ�Ƶ�DEACT */
    if ((NAS_MML_NET_RAT_TYPE_BUTT == NAS_MML_GetCurrNetRatType())
     && (NAS_MMC_SUSPEND_SUCCESS == pstSuspendRslt->enRslt))
    {
        NAS_MMC_StopAllTimer();

        /* �޸�:NAS_MMC_L1_STA_OOC--> NAS_MMC_L1_STA_DEACT
            ��ѡ��HRPD����ǰLTE���ڴ�ģ��MMC״̬Ӧ���е�DEACT */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);

        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);

        return VOS_TRUE;
    }
#endif

    pstPrioRatList   = NAS_MML_GetMsPrioRatList();
    PS_MEM_SET(&stAnycellSrchRatList, 0, sizeof(stAnycellSrchRatList));

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());
    /* Modified by s00246516 for L-C��������Ŀ, 2014-01-27, End */

#if (FEATURE_ON == FEATURE_LTE)

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    }

#endif

    /* suspend ��ϵͳ��ѡ��� */
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_OnPlmn:SUSPEND COMPLETE");

    /* ����״̬���˳���� ������Ӧ�Ĵ��� */
    if ( (NAS_MMC_SUSPEND_FAIL == pstSuspendRslt->enRslt)
      && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST == pstSuspendRslt->enFailCause))
    {

        /* �����ǰ����NO RF����Ǩ�Ƶ�OOC״̬ */
        if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
        {
            /* ������״̬���ϱ�����״̬��Ǩ�Ƶ�ooc������available��ʱ�� */
            /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
            NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
            /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */

            return VOS_TRUE;
        }

        /* Ǩ��״̬��INITIAL ״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        if (MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendRslt->enSuspendCause)
        {
            /* ����������Ϣ */
            NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_INTER_SYS_OOS, &(pstSuspendRslt->astPlmnSearchInfo[0]), NAS_MML_MAX_RAT_NUM);
        }
        else
        {
            /* ����������Ϣ */
            if(VOS_TRUE == NAS_MMC_IsInterNationalRoamingSearchRPLMN(NAS_MMC_GetLastCampedPlmnid()->ulMcc))
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG, &(pstSuspendRslt->astPlmnSearchInfo[0]), NAS_MML_MAX_RAT_NUM);
            }
            else
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST, &(pstSuspendRslt->astPlmnSearchInfo[0]), NAS_MML_MAX_RAT_NUM);
            }

        }
    }

    if ( (VOS_TRUE == NAS_MML_IsExistBufferedEmgCall())
      && (NAS_MMC_SUSPEND_ABORTED == pstSuspendRslt->enRslt))
    {
        /* Ǩ�Ƶ�Intial״̬  */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* ���ڽ������д���ANYCELL����,������Ҫanycell�ѵĽ��뼼��ΪGU,����˳����syscfg���� */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvUserSpecPlmnSearch_OnPlmn
 ��������  : ON PLMN״̬���յ��û�ָ��������Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��01��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��8��26��
   ��    ��   : w00176964
   �޸�����   : V7R1 PhaseII ����:��ʱ������洦���в���Ԥ�����е��߼�

 3.��    ��   : 2011��12��20��
   ��    ��   : w00167002
   �޸�����   : DTS2011122001697:��ON PLMN״̬����ǰָ���ѵ�������ǰפ��������
                 ��ͬ����ǰ������������״̬�Ҳ������������У��Ų������û�ָ������
                 �����ڸ����ȼ�ָ������ʱ���߿���ָ����ʱ�����û�ָ���Ѵ�ϣ�
                 ���û�ָ�����������ǰפ����������ͬ�������ȼ�����״̬���˳���
                 �᲻�����û�ָ���ѡ�

 4.��    ��   : 2011��12��20��
   ��    ��   : h44270
   �޸�����   : ��������״̬��ʱ����Ϊ��ǰ������
 5.��    ��   : 2012��6��6��
   ��    ��   : l00130025
   �޸�����   : DTS2012060604313:������ע��ɹ����û�����Ը������ָ������ʱ��Ҫ��������ע��
 6.��    ��   : 2013��3��14��
   ��    ��   : W00176964
   �޸�����   : DTS2013031400138, ��Ʒ��������:PSҵ�����ʱ����ָ������
 7.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvUserSpecPlmnSearch_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU      *pstUserSelReqMsg  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstUserSpecPlmnId = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;
    VOS_UINT32                          ulCsServiceStatusFlg;
    VOS_UINT32                          ulRslt;

    VOS_UINT32                          ulSpecPlmnSearchFlg;

    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;

    /* ָ���û�ָ��������Ϣ�е�PlmnId */
    pstUserSpecPlmnId   = (NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId);

    /* �ж��û�ָ��������͵�ǰפ���������Ƿ���ͬ */
    ulRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(),
                                               pstUserSpecPlmnId);
    enCurrRatType = NAS_MML_GetCurrNetRatType();

    if ( (VOS_TRUE == ulRslt)
     && (pstUserSelReqMsg->enAccessMode == enCurrRatType) )
    {

        /* ��ǰ������������״̬��δ���й������������ڸ����ȼ�ָ������ʱ
           ���߿���ָ����ʱ�����û�ָ���Ѵ�ϣ����û�ָ�����������ǰפ����
           ������ͬ�������ȼ�����״̬���˳��󣬻᲻�����û�ָ���� */
        ulSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();

        if ( (VOS_FALSE == NAS_MMC_NeedTrigPlmnSrch_UserSpecCurrentPlmn())
          && (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING != ulSpecPlmnSearchFlg) )
        {

            /* �����ֶ��������� */
            NAS_MMC_UpdateUserSpecPlmnSearchInfo_PreProc(pstUserSpecPlmnId,
                                                              pstUserSelReqMsg->enAccessMode);

            /* ���õ�ǰע��״̬Ϊ�ɹ� */
            NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

            /* ��MSCC�����û�ָ�������ɹ� */
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
            return VOS_TRUE;
        }
    }

    ulCsServiceStatusFlg = NAS_MML_GetCsServiceExistFlg();

    if (VOS_TRUE == ulCsServiceStatusFlg)
    {
        /* ��MSCC�����û�ָ������ʧ�� */
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
        return VOS_TRUE;
    }

    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvUserReselReq_L1Main
 ��������  : ON PLMN,Initial״̬���յ��û��Զ���ѡ����Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��15��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II����
 3.��    ��   : 2012��5��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton����֧��
 4.��    ��   : 2013��4��7��
   ��    ��   : z00161729
   �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���

 5.��    ��   : 2013��6��4��
   ��    ��   : z00161729
   �޸�����   : SVLTE ��usim�ӿڵ����޸�
 6.��    ��   : 2014��2��12��
   ��    ��   : w00242748
   �޸�����   : DTS2014021003925:en_NV_Item_User_Auto_Resel_Switch��NV��ʱ��CS��
                ��������PS��DEREGISTER LIMIT SERVICE״̬���·�AT+COPS=0����������
                ���������У�����δ���·���״̬�����������������У��·�AT+COPS?��ѯ
                �����Ϊ�������񡣵������������У�MMC�ѽ�CS/PSע��״̬���ó�δע��
                ��Ҫ������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvUserReselReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    /* ��ǰΪ�Զ�ѡ��ģʽ */
    if ( NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ��¼�������� */


        if (VOS_TRUE == NAS_MML_GetUserAutoReselActiveFlg())
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_USER_AUTO_RESEL;
        }
        else
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED;
        }

    }
    else
    {
        /* ����ѡ��ģʽ */
        NAS_MMC_SetPlmnSelectionMode(NAS_MMC_PLMN_SELECTION_MODE_AUTO);

        /* ����ǰ��ѡģʽд��NVIM�� */
        NAS_MMC_WritePlmnSelectionModeNvim();

        /* ģʽ�ı����STK����¼�,MMC�ڵ���ǰ�ж��£�SVLTE��̬�£����û��CS���������Ͳ�����*/
        if (VOS_TRUE == NAS_MMC_IsNeedSndStkSearchModeChgEvt())
        {
            NAS_MMC_SndStkSearchModeChgEvt(NAS_MMC_PLMN_SELECTION_MODE_AUTO);
        }

        /* ��¼�������� */

        if (VOS_TRUE == NAS_MML_GetUserAutoReselActiveFlg())
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_USER_AUTO_RESEL;
        }
        else
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_MANUAL_CHANGE_AUTO_MODE;
        }

    }

    /* ��ҵ��ʱ�������� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    NAS_MMC_SndInterPlmnSearchReq(enPlmnSearchScene,VOS_NULL_PTR, 0);

    if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus() )
    {
        NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_SetPsServiceStatus(NAS_MMC_LIMITED_SERVICE);

        NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);
        NAS_MMC_UpdateRegStateSpecPlmnSearch();
    }

    /* �������óɹ� */
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
    NAS_MMC_SndMsccPlmnReselCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvPsRegResultInd_OnPlmn
 ��������  : ON PLMNʱ�յ�PS��ע��������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg: GMMMMC_PS_REG_RESULT_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��   : 2011��7��19��
   ��    ��   : h44270
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II����

 3.��    ��   : 2011��9��20��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II �ڲ�LIST��������

 4.��    ��   : 2011��9��25��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase II �����ȼ���������

 5.��    ��   : 2011��10��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II-2 ����HPLMN TIMER���¼��ϱ�

 6.��    ��   : 2011��11��20��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2111111507462,�����̣�������ע��ɹ���ʱ�����ֹͣ��AvailTimer

 7.��    ��   : 2013��10��17��
   ��    ��   : l65478
   �޸�����   : DTS2013102103487:DT����:�ڵ���ʧ��ʱҲ��Ҫ��������
 8.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
                  �����һ�TL������Ӧ������������һء�
 9.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search���Ե���:����High_Prio_rat_hplmn��ʱ������������
10.��    ��   : 2014��10��27��
   ��    ��   : b00269685
   �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
11.��    ��   : 2015��6��6��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvPsRegResultInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcConnExistFlag;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* ON PLMN�����������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ���ON PLMN���յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    NAS_MMC_ProcPsRegRslt_L1Main(pstPsRegRslt);

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    /* ����Ҫ����ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ON PLMNʱ�յ�PS��ע��������������������Ҫ�ж��Ƿ���Ҫ����HPLMN��ʱ�� */
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* ������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());


            /* HPLMN TIMER�����¼��ϱ� */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


            /* ��HPLMN������������Ϊ���״����� */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);

        }

        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
        {
            /* ������ʱ�� */
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }


        /* ����ע��ʧ��ԭ��ֵΪother cause��Ҫ�����������Դ�ʱ,��CS��ע��ʧ��ʱ����ֹͣ��ʱ�� */
        /* ����������ֹͣavailable��ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsPsNormalService())
        {
            if (VOS_FALSE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS))
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

            }
        }


        return VOS_TRUE;
    }

    /* �ж��Ƿ���Խ����ڲ�LIST���� */
    if ( VOS_TRUE == NAS_MMC_IsGURegFailTriggerInterPlmnList_L1Main())
    {
        NAS_MMC_SndInterPlmnListReq();

        /* ��������������additional��ֵ */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* ����������ͬʱ���CS/PS��ע�᳢�Դ��� */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();

        return VOS_TRUE;
    }

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* �������� */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCsRegResultInd_OnPlmn
 ��������  : ON PLMNʱ�յ�CS��ע��������Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg: MMMMC_CS_REG_RESULT_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��   : 2011��7��19��
   ��    ��   : h44270
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II����

 3.��    ��   : 2011��9��20��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II �ڲ�LIST��������

 4.��    ��   : 2011��10��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II-2 ����HPLMN TIMER���¼��ϱ�

 5.��    ��   : 2011��11��20��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2111111507462,�����̣�������ע��ɹ���ʱ�����ֹͣ��AvailTimer
 6.��    ��   : 2013��10��17��
   ��    ��   : l65478
   �޸�����   : DTS2013102103487:DT����:�ڵ���ʧ��ʱҲ��Ҫ��������
 7.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
                  �����һ�TL������Ӧ������������һء�
 8.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search���Ե���:����High_Prio_rat_hplmn��ʱ������������
 9.��    ��   : 2014��10��27��
   ��    ��   : b00269685
   �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
10.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvCsRegResultInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcConnExistFlag;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* ON PLMN�����������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ���ON PLMN���յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    NAS_MMC_ProcCsRegRslt_L1Main(pstCsRegRslt);

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    /* ����Ҫ����ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ON PLMNʱ�յ�CS��ע��������������������Ҫ�ж��Ƿ���Ҫ����HPLMN��ʱ�� */
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* ������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());


            /* HPLMN TIMER�����¼��ϱ� */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


            /* ��HPLMN������������Ϊ���״����� */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
        }

        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
        {
            /* ������ʱ�� */
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }


        /* ����������ֹͣavailable��ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsCsNormalService())
        {
            /* ����ע��ʧ��ԭ��ֵΪnetwork fail��Ҫ�����������Դ�ʱ,��CS��ע��ʧ��ʱ����ֹͣ��ʱ�� */
            if (VOS_FALSE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS))
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

            }
        }

        return VOS_TRUE;
    }

    /* �ж��Ƿ���Խ����ڲ�LIST���� */
    if ( VOS_TRUE == NAS_MMC_IsGURegFailTriggerInterPlmnList_L1Main())
    {
        NAS_MMC_SndInterPlmnListReq();

        /* ��������������additional��ֵ */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* ����������ͬʱ���CS/PS��ע�᳢�Դ��� */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();

        return VOS_TRUE;
    }

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* �������� */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmAbortInd_OnPlmn
 ��������  : On Plmn�������յ�MM Abort��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��7��12��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmAbortInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stGuActionRslt;
#endif

    pstMmAbortInd = (MMMMC_ABORT_IND_STRU*)pstMsg;

    /* ���ԭ��ֵ��Ϊ#6���Ҳ�Ϊ#17��ֱ�ӷ��� */
    if ((NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME != pstMmAbortInd->enAbortCause)
     && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstMmAbortInd->enAbortCause))
    {
        return VOS_TRUE;
    }

    /* ���ԭ��ֵ#6������CS AdditionΪAnycellפ�� */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstMmAbortInd->enAbortCause)
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* ��LMM����ID_MMC_LMM_ACTION_RESULT_REQ */
    /* ����ActionRslt��Ϣ�����ΪCN_Rej,������Ϊ����NAS_MML_PROC_MM_ABORT����
       ����ͽ������CS��ԭ��ֵΪAbort����ԭ��ֵ */
    stGuActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stGuActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stGuActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stGuActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stGuActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stGuActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stGuActionRslt);
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmServiceRequestResultInd_OnPlmn
 ��������  : ON PLMNʱ�յ�PS��SR�������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg: GMMMMC_SERVICE_REQUEST_RESULT_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��   : 2011��8��11��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 3.��    ��   : 2015��6��6��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmServiceRequestResultInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstSrRsltInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulRrcConnExistFlag;

    pstSrRsltInd = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    /* ����SR�Ľ����Ϣ */
    NAS_MMC_ProcGmmServiceRequestResultInd_L1Main(pstSrRsltInd);

    /* ����Ҫ����ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ����������ֹͣavailable��ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

            NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
            NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

        }

        return VOS_TRUE;
    }

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* �������� */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCustomizedForbLaTimerExpired_OnPlmn
 ��������  : ����CUSTOMIZED_FORBLA_TIMER��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��ǰ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�����������
             VOS_FALSE:��������δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��12��
   ��    ��   : z00359541
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCustomizedForbLaTimerExpired_OnPlmn(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg
)
{
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod    = VOS_NULL_PTR;
    VOS_UINT32                                              ulTriggerPlmnSearchFlg;

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvCustomizedForbLaTimerExpired_OnPlmn");

    pstForbLaWithValidPeriod            = NAS_MML_GetForbLaWithValidPeriodList();
    ulTriggerPlmnSearchFlg              = NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa();

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvCustomizedForbLaTimerExpired_OnPlmn: Manual PLMN Sel Mode");
        (VOS_VOID)NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList(pstForbLaWithValidPeriod);

        /* ������ʱ�� */
        NAS_MML_StartCustomizedForbLaTimer();

        return VOS_TRUE;
    }

    /* ���ƽ�ֹLA�б��б仯 */
    if (VOS_TRUE == NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList(pstForbLaWithValidPeriod))
    {
        /* �ж�ɾ��LAI���Ƿ���Ҫ�������� */
        if ((VOS_TRUE == NAS_MML_IsCurrGURatMode())
         && (VOS_TRUE == ulTriggerPlmnSearchFlg))
        {

            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvCustomizedForbLaTimerExpired_OnPlmn: Snd Inter PLMN Search Req");
            /* �����ڲ�������ϢΪ��ʱ����ʱ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* ����������Ϣ */
            NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED, VOS_NULL_PTR, 0);
        }
        else
        {
            /* ֪ͨ����㣬CUSTOMIZED FORB LA�����仯 */
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    /* ������ʱ�� */
    NAS_MML_StartCustomizedForbLaTimer();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvForbLaTimerExpired_OnPlmn
 ��������  : ����MMC_FORBLA_TIMER��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��ǰ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��11��29��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvForbLaTimerExpired_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo   = VOS_NULL_PTR;
    VOS_UINT32                          ulLaiValidFlg;
    VOS_UINT32                          ulRlstLaiInForbidRegLaiList;
    ulLaiValidFlg       = VOS_TRUE;

    /* ��ȡFPLMN��Ϣ*/
    pstForbidPlmnInfo   = NAS_MML_GetForbidPlmnInfo();

    /* ��ȡ��ǰפ��PLMN��Ϣ */
    pstCampPlmnInfo     = NAS_MML_GetCurrCampPlmnInfo();

    ulRlstLaiInForbidRegLaiList = NAS_MML_IsLaiInDestLaiList(&(pstCampPlmnInfo->stLai),
        pstForbidPlmnInfo->ucForbRegLaNum, pstForbidPlmnInfo->astForbRegLaList);

    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        pstForbidPlmnInfo->ucForbRegLaNum    = 0;
        pstForbidPlmnInfo->ucForbRoamLaNum   = 0;
        return VOS_TRUE;
    }

    /* פ��PLMN�ڽ�ֹFPLMN�б��� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(&(pstCampPlmnInfo->stLai.stPlmnId)))
    {
        ulLaiValidFlg =  VOS_FALSE;
    }

    /* פ����LAI�ڽ�ֹLAI�б��� */
    if ((VOS_TRUE == NAS_MML_IsLaiInDestLaiList(&(pstCampPlmnInfo->stLai),
            pstForbidPlmnInfo->ucForbRoamLaNum, pstForbidPlmnInfo->astForbRomLaList)) ||
        (VOS_TRUE == ulRlstLaiInForbidRegLaiList))
    {
        ulLaiValidFlg =  VOS_FALSE;
    }

    pstForbidPlmnInfo->ucForbRegLaNum    = 0;
    pstForbidPlmnInfo->ucForbRoamLaNum   = 0;

    switch ( NAS_MML_GetCurrNetRatType())
    {
#if (FEATURE_ON == FEATURE_LTE)
    case NAS_MML_NET_RAT_TYPE_LTE:
        /* Lģ��Ҫ��ForbTAI����Ŀǰ��L��� */
        return VOS_TRUE;
#endif
    case NAS_MML_NET_RAT_TYPE_WCDMA:
    case NAS_MML_NET_RAT_TYPE_GSM:

        break;

    default:
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvForbLaTimerExpired_L1Main:Net RAT ERROR! ");
        return VOS_TRUE;
    }

    /* ��ǰλ�ô���Forb LA��ʱ��ɾ������Ҫ������������һ��ע�� */
    if ( VOS_FALSE == ulLaiValidFlg )
    {
        /* �����ڲ�������ϢΪ��ʱ����ʱ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* ����������Ϣ */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED, VOS_NULL_PTR, 0);
    }
    else
    {
        /* ֪ͨ����㣬��ǰForbLa��Ч */
        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
    }

    return VOS_TRUE;

}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmDetachCnf_L1Main
 ��������  : MMC�յ�LMM DETACH CNF�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ԥ�������
             VOS_FALSE:����Ԥ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��19��
   ��    ��   : ��ë/00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��8��11��
   ��    ��   : W00167002
   �޸�����   : �޸�Ϊ����detach����
 3.��    ��   : 2011��10��26��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase III����:����ע���޸�
 4.��    ��   : 2012��5��15��
   ��    ��   : w00176964
   �޸�����   : GUL BG��Ŀ����
 5.��    ��   : 2014��4��24��
   ��    ��   : w00242748
   �޸�����   : DTS2014042405819:�޿�״̬�£�����������#5������ANYCELL�ѣ�������״̬��
                ���·�RRMM_UE_OOC_STATUS_NOTIFY_IND���������粻���·�CM SERVICE REJ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmDetachCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_CNF_STRU            *pstLmmDetachCnf     = VOS_NULL_PTR;

    pstLmmDetachCnf = (LMM_MMC_DETACH_CNF_STRU*)pstMsg;

    switch (pstLmmDetachCnf->ulDetachRslt)
    {
        case MMC_LMM_DETACH_RSLT_AUTH_REJ:

            /* �������ӵ�ʱ���Ѿ����봦�����꣬��״̬���󲻻������Ӵ��� */
            /* Ǩ�Ƶ�Initial״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* ���ݽ���еĽ��뼼��������Ϣ����anycell״̬��������������ǰ���뼼�� */
            NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);

            break;

        case MMC_LMM_DETACH_RSLT_ACCESS_BARED:
        case MMC_LMM_DETACH_RSLT_FAILURE:
        case MMC_LMM_DETACH_RSLT_SUCCESS:

            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* �����ڲ����� */
            NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE, VOS_NULL_PTR, 0);

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmDetachCnf_L1Main:Unexpected detach result!");

            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLSysInfoInd_OnPlmn
 ��������  : �ڿ���̬ʱ���յ�ID_LMM_MMC_SYS_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType:ID_LMM_MMC_SYS_INFO_IND��Ϣ����
             pstMsg: ID_LMM_MMC_SYS_INFO_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II����
  3.��    ��   : 2011��10��20��
    ��    ��   : w00167002
    �޸�����   : V7R1 Phase II ST: ɾ������NAS_MMC_SetPsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_BUTT);
  4.��    ��   : 2011��11��2��
    ��    ��   : w00167002
    �޸�����   : V7R1 Phase II ST: ɾ������NAS_MMC_SetCsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION);
                 �޸�ԭ��:��Lģ�¸����ȼ�����ע�ᱻ��ԭ��ֵ6�����¿���Ч��
                 ��Ҫ����ANYCELL������ANYCELL�������ܵ�Lģ��ϵͳ��Ϣ��CS������Ϊ
                 NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION���յ�MM������
                 ������ָʾ��Ϣ�������������ANYCELL������
  5.��    ��   : 2012��4��18��
    ��    ��   : l00130025
    �޸�����   : DTS2012040200480,����ά��EPSע��״̬,��Lģ��CEREG/CGREG��ѯ���ϱ�ʹ��
  6.��    ��   : 2012��4��28��
    ��    ��   : W00166186
    �޸�����   : DTS2012042602593,MMû�б��浱ǰפ����PLMN�����º����жϳ���
  7.��    ��   : 2012��11��29��
    ��    ��   : w00176964
    �޸�����   : DTS2012042804167:֪ͨCBAģ�鵱ǰ����ģʽΪLTE
  8.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  9.��    ��   : 2012��12��20��
    ��    ��   : w00176964
    �޸�����   : DTS2012121906946:�յ�L��ϵͳ��Ϣת����LMM
 10.��    ��   : 2013��1��19��
    ��    ��   : t00212959
    �޸�����   : DTS2012122900189:EPSע��״̬��ȫ��L�ϱ�
 11.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);



    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */
    /*�����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC*/
    /* פ��С���仯ʱ*/
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }


    /* ת��GMMϵͳ��Ϣ,��rabmʹ�� */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAreaLostInd_OnPlmn
 ��������  : ON PLMN״̬�յ�LMM��ID_LMM_MMC_AREA_LOST_IND�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��15��
    ��    ��   : w00176964
    �޸�����   : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SEARCHED_TYPE_STRU                              stNasSearchedType;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stRatSrchList;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo = VOS_NULL_PTR;
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd  = VOS_NULL_PTR;
    RRC_PLMN_ID_LIST_STRU                                  *pstGuPlmnIdList = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList  = VOS_NULL_PTR;

    pstAreaLostInd  = (LMM_MMC_AREA_LOST_IND_STRU*)pstMsg;
    pstPrioRatList  = NAS_MML_GetMsPrioRatList();
    pstGuPlmnIdList = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmAreaLostInd_OnPlmn:ERROR: Memory Alloc Error");
        return VOS_TRUE;
    }

    /* RSSI��ʼ�� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* פ����Ϣ��פ��״̬���� */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);

    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

    /* ɾ��NV�еĲ�ͬ�������Plmn */
    NAS_MMC_DelDiffMccRplmnInNv_L1Main();

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* �����ǰΪNO RF�˳��������� */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ������״̬���ϱ�����״̬��Ǩ�Ƶ�ooc������available��ʱ�� */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);

        /* CLģʽ��L��ģע��ʧ��������DO */
        if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
        {
            NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_NO_RF);
        }

        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

        return VOS_TRUE;
    }

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);



    pstPlmnListInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                         sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    if (VOS_NULL_PTR == pstPlmnListInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmAreaLostInd_OnPlmn: ALLOC MEM FAIL!");

        PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

        return VOS_TRUE;

    }



    PS_MEM_SET(&stNasSearchedType, 0, sizeof(NAS_MMC_SEARCHED_TYPE_STRU));
    stNasSearchedType.ucHistorySearchedFlg  = pstAreaLostInd->stSearchedType.ucHistorySearchedFlg;
    stNasSearchedType.ucPrefBandSearchedFlg = pstAreaLostInd->stSearchedType.ucPrefBandSearchedFlg;
    stNasSearchedType.ucSpecSearchedFlg     = pstAreaLostInd->stSearchedType.ucSpecSearchedFlg;

    /* ����AS/LRRC��������������ж��Ƿ�Ҫ��������OOC״̬ */
    if (VOS_TRUE == NAS_MMC_IsNeedEnterOocStatusWhenAreaLost_OnPlmn(&stNasSearchedType))
    {
        NAS_MMC_EnterOocStatus_OnPlmn();

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_OOC);

        NAS_MMC_UpdateRegStateSpecPlmnSearch();

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        /* CLģʽ��L��ģע��ʧ��������DO */
        if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
        {
            NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_AREA_LOST);

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnListInfo);

            PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

            return VOS_TRUE;
        }
#endif

        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            /* ���� availble timer��ǰ�����Ĵ�����ncell�������� */
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
        }
    }
    else
    {
        /*�յ�����ָʾ��Ǩ��״̬NAS_MMC_L1_STA_INITIAL,����������  */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        if (VOS_TRUE == NAS_MML_IsUsimStausValid())
        {
            NAS_MMC_InitSearchedPlmnListInfo(pstPlmnListInfo);

            /* ��������Ϣ��Я����������Ϣת��Ϊ�ڲ���Ϣ��������Ϣ */
            NAS_MMC_ConvertLmmPlmnIdListToGUFormat(&(pstAreaLostInd->stPlmnIdList),
                                                   pstGuPlmnIdList);

            /* ����area lost��Ϣ��������������ͺ͸ߵ�����plmn�����ڲ�ѡ����Ϣ */
            NAS_MMC_UpdateSearchedPlmnListInfo(&stNasSearchedType, pstGuPlmnIdList, pstPlmnListInfo);

            /* LMM����������ת����NAS���������� */
            if(VOS_TRUE == NAS_MMC_IsInterNationalRoamingSearchRPLMN(NAS_MMC_GetLastCampedPlmnid()->ulMcc))
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG, pstPlmnListInfo, NAS_MML_MAX_RAT_NUM);
            }
            else
            {
                NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST, pstPlmnListInfo, NAS_MML_MAX_RAT_NUM);
            }
        }
        else
        {
            /* ���춪������Ҫ�����Ľ��뼼���б� ��Anycell����ʱ����Ҫʹ��*/
            PS_MEM_SET(&stRatSrchList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
            PS_MEM_CPY(&stRatSrchList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stRatSrchList);

            NAS_MMC_SndInterAnyCellSearchReq(&stRatSrchList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        }

    }

    /* �ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnListInfo);

    PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcStatusInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�ID_LMM_MMC_STATUS_IND��Ϣ�Ĵ���
 �������  : ulEventType:ID_LMM_MMC_STATUS_IND��Ϣ����
             pstMsg: ID_LMM_MMC_STATUS_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II����
  3.��    ��   : 2011��12��8��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:���������Ĵ���
  4.��    ��   : 2012��5��24��
    ��    ��   : w00176964
    �޸�����   : GUL BG��Ŀ����:�������ָ������ʱ���ж����Ƿ��Ѿ�����������
  5.��    ��   : 2015��9��16��
    ��    ��   : y00346957
    �޸�����   : DTS2015070910885 ���ӵ�ǰפ����plmn�Ƿ������ѵ��ж�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn        = VOS_NULL_PTR;

    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();
#endif

    pstLmmStatusIndMsg  = ( LMM_MMC_STATUS_IND_STRU* )pstMsg;

    /* ����LMM������״̬ */
    switch (pstLmmStatusIndMsg->ulConnState)
    {
        case MMC_LMM_CONN_ESTING:
        case MMC_LMM_CONNECTED_SIG:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
            break;

        case MMC_LMM_CONNECTED_DATA:
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);
            break;

        case MMC_LMM_CONN_IDLE:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        default:
            break;
    }

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    if ( VOS_TRUE == NAS_MML_IsRrcConnExist() )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* ��Ҫ��ע��ʧ�ܵ�����Ҫ������Ϊ���� */
    if ( VOS_TRUE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        return NAS_MMC_PerformPlmnSearch_L1Main();
    }

    /* ���ע��ʧ�ܲ���Ҫ��������,���ж��Ƿ��л����������־ */
    NAS_MMC_PerformBufferedPlmnSearch_L1Main();
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_MMC_IsCampLteNormalService())
    {
        if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(pstCurrPlmn))
        {
            NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_OnPlmn:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                                 pstCurrPlmn->ulMcc, pstCurrPlmn->ulMnc);

            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* �����ڲ��������� */
            NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST, VOS_NULL, 0);

            return VOS_TRUE;
        }
    }
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcAttachInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�ID_LMM_MMC_ATTACH_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg: ID_LMM_MMC_ATTACH_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II����

 3.��    ��   : 2011��10��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II-2 ����HPLMN TIMER���¼��ϱ�

 4.��    ��   : 2011��11��20��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2111111507462,�����̣�������ע��ɹ���ʱ�����ֹͣ��AvailTimer
 5.��    ��   : 2011��10��25��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase III����ע�����
 6.��    ��   : 2012��1��8��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����
 7.��    ��   : 2012��4��26��
   ��    ��   : w00176964
   �޸�����   : GUL BG��Ŀ����
 8.��    ��   : 2012��11��22��
   ��    ��   : t00212959
   �޸�����   : DTS2012112006974
 9.��    ��   : 2012��12��26��
   ��    ��   : l00171473
   �޸�����   : DTS2012122502264, �����Ҫ����������GU��������ֹͣAVAILABLE��ʱ��
 10.��    ��   : 2013��12��25��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
                  �����һ�TL������Ӧ������������һء�
 11.��    ��   : 2014��2��24��
    ��    ��   : w00176964
    �޸�����   : High_Rat_Hplmn_Search���Ե���:����High_Prio_rat_hplmn��ʱ������������
 12.��    ��   : 2014��10��27��
   ��    ��   : b00269685
   �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
 13.��    ��   : 2015��5��26��
    ��    ��   : w00167002
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcAttachInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulRrcConnExistFlag;
    NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8                 enClRegAddition;

    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode;

    enUeOperationMode   =  NAS_MML_GetLteUeOperationMode();
    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* LMM������δ�ظ�search cnfʱ�յ��û�detach ps����󣬺���������ע���mmc�ظ�attach result
       ΪMMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW���������������MMC_LMM_ATT_TYPE_BUTT��
       MMC��Ҫ���ݵ�ǰue operation mode�������������¸�ֵ */
    if ((MMC_LMM_ATT_TYPE_BUTT == pstLmmAttachIndMsg->ulReqType)
     && (MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW == pstLmmAttachIndMsg->ulAttachRslt))
    {
        pstLmmAttachIndMsg->ulReqType = NAS_MMC_ConvertLmmAttachReqType(enUeOperationMode);
    }

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_OnPlmn(pstLmmAttachIndMsg);

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    enClRegAddition = NAS_MMC_GetCLRegAdditionalAction_L1Main();

    /* CLģʽ��,���CL��reg additionΪanycell����������פ��,��Ҫ֪ͨ
       MSCC��ʱLTE������,����HRPD */
    if ((VOS_FALSE                                       == NAS_MML_IsGULModeConfigured())
     && ((NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION == enClRegAddition)
      || (NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON   == enClRegAddition)))
    {
        NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_REG_FAILURE);
    }

    /* ����Ҫ����ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ON PLMNʱ�յ�ע��������������������Ҫ�ж��Ƿ���Ҫ����HPLMN��ʱ�� */
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* ������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());


            /* HPLMN TIMER�����¼��ϱ� */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


            /* ��HPLMN������������Ϊ���״����� */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);

        }

        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
        {
            /* ������ʱ�� */
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }


        /* ����������ֹͣavailable��ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsPsNormalService())
        {

            /* ����Ҫ����������GU����, ��ֹͣavailable��ʱ�� */
            if ( VOS_FALSE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU() )
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

            }
        }


        return VOS_TRUE;
    }



    /* �����ڲ��б������ж� */
    if ( VOS_TRUE == NAS_MMC_IsLRegFailTriggerInterPlmnList_L1Main())
    {
        NAS_MMC_SndInterPlmnListReq();

        /* ��������������additional��ֵ */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* ����������ͬʱ���CS/PS��ע�᳢�Դ��� */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();

        return VOS_TRUE;
    }

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* �������� */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcTauResultInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�ID_LMM_MMC_TAU_RESULT_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg: ID_LMM_MMC_TAU_RESULT_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II����

 3.��    ��   : 2011��10��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II-2 ����HPLMN TIMER���¼��ϱ�

 4.��    ��   : 2011��11��20��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2111111507462,�����̣�������ע��ɹ���ʱ�����ֹͣ��AvailTimer
 5.��    ��   : 2011��10��26��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase III����:����ע���޸�
 6.��    ��   : 2012��4��26��
   ��    ��   : w00176964
   �޸�����   : GUL BG��Ŀ����
 7.��    ��   : 2012��11��22��
   ��    ��   : t00212959
   �޸�����   : DTS2012112006974
 8.��    ��   : 2012��12��26��
   ��    ��   : l00171473
   �޸�����   : DTS2012122502264, �����Ҫ����������GU��������ֹͣAVAILABLE��ʱ��
 9.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
                  �����һ�TL������Ӧ������������һء�
10.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search���Ե���:����High_Prio_rat_hplmn��ʱ������������
11.��    ��   : 2014��10��27��
   ��    ��   : b00269685
   �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
12.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcTauResultInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;
    VOS_UINT32                          ulRrcConnExistFlag;
    NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8                 enClRegAddition;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_OnPlmn(pstLmmTauIndMsg);

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    enClRegAddition = NAS_MMC_GetCLRegAdditionalAction_L1Main();

    /* CLģʽ��,���CL��reg additionΪanycell����������פ��,��Ҫ֪ͨ
       MSCC��ʱLTE������,����HRPD */
    if ((VOS_FALSE                                       == NAS_MML_IsGULModeConfigured())
     && ((NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION == enClRegAddition)
      || (NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON   == enClRegAddition)))
    {
        NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_REG_FAILURE);
    }

    /* ����Ҫ����ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ON PLMNʱ�յ�ע��������������������Ҫ�ж��Ƿ���Ҫ����HPLMN��ʱ�� */
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* ������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());


            /* HPLMN TIMER�����¼��ϱ� */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


            /* ��HPLMN������������Ϊ���״����� */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);

        }

        if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
        {
            /* ������ʱ�� */
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, NAS_MMC_GetHighPrioRatHplmnTimerLen()))
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }


        /* ����������ֹͣavailable��ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsPsNormalService())
        {

            /* ����Ҫ����������GU����, ��ֹͣavailable��ʱ�� */
            if ( VOS_FALSE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU() )
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

            }
        }


        return VOS_TRUE;
    }



    /* �����ڲ��б������ж� */
    if ( VOS_TRUE == NAS_MMC_IsLRegFailTriggerInterPlmnList_L1Main())
    {
        NAS_MMC_SndInterPlmnListReq();

        /* ��������������additional��ֵ */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* ����������ͬʱ���CS/PS��ע�᳢�Դ��� */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();

        return VOS_TRUE;
    }

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* �������� */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcDetachInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�ID_LMM_MMC_DETACH_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ�׵�ַ
             pstMsg: ID_LMM_MMC_DETACH_IND�׵�ַ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II����

 3.��    ��   : 2011��10��26��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase III����:����ע���޸�
 4.��    ��   : 2012��12��26��
   ��    ��   : l00171473
   �޸�����   : DTS2012122502264, �����Ҫ����������GU��������ֹͣAVAILABLE��ʱ��
 5.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 6.��    ��   : 2015��6��6��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulRrcConnExistFlag;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8                 enClRegAddition;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* ����DETACH��Ϣ��������һ������ */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();
    }

    /*����EPS����һ���Ķ�������*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enPsAdditionalAction);
    }

    /*����CS����һ���Ķ�������*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(enCsAdditionalAction);
    }

    enClRegAddition = NAS_MMC_GetCLRegAdditionalAction_L1Main();

    /* CLģʽ��,���CL��reg additionΪanycell����������פ��,��Ҫ֪ͨ
       MSCC��ʱLTE������,����HRPD */
    if ((VOS_FALSE                                       == NAS_MML_IsGULModeConfigured())
     && ((NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION == enClRegAddition)
      || (NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON   == enClRegAddition)))
    {
        NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_MT_DETACH);
    }

    /* ����Ҫ����ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ����������ֹͣavailable��ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {

            /* ����Ҫ����������GU����, ��ֹͣavailable��ʱ�� */
            if ( VOS_FALSE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU() )
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

            }
        }


        return VOS_TRUE;
    }



    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* �������� */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcServiceRsltInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ�Ĵ���
             LMM��SERVICE���̽��ͨ����ԭ��֪ͨMMC���ṹ�е�bit������ʾ�����Ƿ���Ч��
             SERVICE���̳ɹ�������֪ͨMMC��
             SERVICE���̱�����ܾ���ͨ��SERVICE�����MMC_LMM_SERVICE_RSLT_FAILURE֪ͨMMC����Я����Ӧ��ԭ��ֵ��
             ���UE����EXTENDED SERVICE���̣���Я��SERVICE���͡�
             ע��SERIVE������ʱ��ʹ��
 �������  : ulEventType:��Ϣ����
             pstMsg: ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��1��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase II����
 3.��    ��   : 2012��2��13��
   ��    ��   : w00167002
   �޸�����   : DTS2011122704039:additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
 4.��    ��   : 2012��06��01��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 5.��    ��   : 2012��8��21��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�DTS2012090401249
 6.��    ��   : 2012��12��26��
   ��    ��   : l00171473
   �޸�����   : DTS2012122502264, �����Ҫ����������GU��������ֹͣAVAILABLE��ʱ��
 7.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 8.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU                        *pstSerRsltMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulRrcConnExistFlag;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_CL_ADDITIONAL_ACTION_ENUM_UINT8                 enClRegAddition;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstSerRsltMsg     = (LMM_MMC_SERVICE_RESULT_IND_STRU*)pstMsg;

    /* ����LMM��service result���������һ�������� */
    enAdditionalAction = NAS_MMC_ProcLmmServiceRsltInd(pstSerRsltMsg);

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo     = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();
    }

    enClRegAddition = NAS_MMC_GetCLRegAdditionalAction_L1Main();

    /* CLģʽ��,���CL��reg additionΪanycell����������פ��,��Ҫ֪ͨ
       MSCC��ʱLTE������,����HRPD */
    if ((VOS_FALSE                                       == NAS_MML_IsGULModeConfigured())
     && ((NAS_MMC_CL_ADDITIONAL_ACTION_ANYCELL_SELECTION == enClRegAddition)
      || (NAS_MMC_CL_ADDITIONAL_ACTION_LIMITED_CAMP_ON   == enClRegAddition)))
    {
        NAS_MMC_SndMsccMmssLteUnAvailableInd(MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_SERVICE_FAILURE);
    }

    /* ����Ҫ����ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MMC_IsPlmnSearchNeeded_L1Main())
    {
        /* ����������ֹͣavailable��ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {

            /* ����Ҫ����������GU����, ��ֹͣavailable��ʱ�� */
            if ( VOS_FALSE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU() )
            {
                NAS_MMC_ResetOosPlmnSearchTimerCount_OnPlmn();

                NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
                NAS_MMC_StopTimer(TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER);
                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

            }
        }


        return VOS_TRUE;
    }



    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
       /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
       return VOS_TRUE;
    }

    /* �������� */
    (VOS_VOID)NAS_MMC_PerformPlmnSearch_L1Main();

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcSuspendInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�ID_LMM_MMC_SUSPEND_IND��Ϣ�Ĵ���
 �������  : ulEventType:LMM ��ϵͳ��ѡ��Ϣ����
             pstMsg: LMM��ϵͳ��ѡ��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : ������ϵͳ״̬��ʱ����Ϊ��ǰ�����磬��ʱAPS����

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcSuspendInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg  = VOS_NULL_PTR;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ��������ͬ��״̬�� */
    switch(pstLSuspendMsg->ulSysChngType)
    {
        case MMC_LMM_SUS_TYPE_RSL:
        case MMC_LMM_SUS_TYPE_REDIR:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            break;

        case MMC_LMM_SUS_TYPE_HO:
            /* Added by s00261364 for L-C��������Ŀ, 2014-3-12, begin */
            /*��ȫ�ֱ�������ģʽ�жϣ������ΪC+L������ģʽ��������ע������*/
            if (MMC_LMM_SYS_CHNG_DIR_L2C == pstLSuspendMsg->ulSysChngDir)
            {
                /* C+Lģʽ��֧����ϵͳ�л����ظ�LMM����ʧ�� */
                NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
                return VOS_TRUE;
            }
            /* Added by s00261364 for L-C��������Ŀ, 2014-3-12, end */

            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            break;

        case MMC_LMM_SUS_TYPE_CCO:
            /* Added by s00261364 for L-C��������Ŀ, 2014-3-12, begin */
            /*��ȫ�ֱ�������ģʽ�жϣ������ΪC+L������ģʽ��������ע������*/
            if (MMC_LMM_SYS_CHNG_DIR_L2C == pstLSuspendMsg->ulSysChngDir)
            {
                /* C+Lģʽ��֧����ϵͳ�л����ظ�LMM����ʧ�� */
                NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
                return VOS_TRUE;
            }
            /* Added by s00261364 for L-C��������Ŀ, 2014-3-12, end */

            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcSuspendInd_OnPlmn:Unexpected Suspend Type!");
            break;
    }

    if ( (MMC_LMM_SUS_TYPE_BUTT != pstLSuspendMsg->ulSysChngType)
      && (MMC_LMM_SUS_TYPE_CCO_REVERSE != pstLSuspendMsg->ulSysChngType) )
    {
        NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                 NAS_MML_GetSimPsRegStatus());
    }

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAttachCnf_L1Main
 ��������  : ��һ״̬���յ�Attach_Cnf��Ϣʱ����Ҫ�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��4��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��5��
    ��    ��   : s00217060
    �޸�����   : DTS2012082703201:�޸ĺ�������

  3.��    ��   : 2013��11��15��
    ��    ��   : w00167002
    �޸�����   : L-->LWGʱ����Ҫ������������ֹ���뼼��Lʱ���û�����ΪLWG��MMA
                 �Ȼ�DETACH CS/PS.��SYSCFG������ɺ����CSPS��ATTACH,���յ�LMM��
                 ATTACH CNFʱ��
  4.��    ��   : 2014��4��24��
    ��    ��   : w00242748
    �޸�����   : DTS2014042405819:�޿�״̬�£�����������#5������ANYCELL�ѣ�������״̬��
                 ���·�RRMM_UE_OOC_STATUS_NOTIFY_IND���������粻���·�CM SERVICE REJ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        if ( VOS_FALSE == NAS_MML_IsRrcConnExist() )
        {
            /* ��Ҫ�������� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            /* ����Ч����anycell���� */
            NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        }
        else
        {
            NAS_MMC_SetPsRegAdditionalAction_L1Main(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);
        }

        return VOS_TRUE;
    }

    /* ��Ҫ�������� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* DISABLE lte�������� */
    if ( NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus() )
    {
        /* ����Ч�����ڲ�ָ������ */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE, VOS_NULL_PTR, 0);

        return VOS_TRUE;
    }

    /* ����Ч�����ڲ�ָ������ */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED, VOS_NULL_PTR, 0);


    return VOS_TRUE;
}


/* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmServiceResultInd_Initial
 ��������  : INITIALʱ�յ�LMMģ��ID_LMM_MMC_SERVICE_RESULT_IND��������ָʾ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��8��14��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��9��6��
   ��    ��   : z00359541
   �޸�����   : DTS2015081407087: �ӿڵ�����ɾ��bitOpReqType��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmServiceResultInd_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList;

    pstPrioRatList       = NAS_MML_GetMsPrioRatList();

    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        /* ����ANYCELL����,������Ҫanycell�ѵĽ��뼼��ΪGU,����˳����syscfg���� */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }

    return VOS_TRUE;
}

/* Modified by z00161729 for DCM�����������������, 2012-8-14, end */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCLAssociatedInfoNtf_OnPlmn
 ��������  : פ��ʱ�յ�MSCCMģ��ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��17��
   ��    ��   : y00346957
   �޸�����   : DTS2015070910885 ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCLAssociatedInfoNtf_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     NAS_MML_PLMN_ID_STRU               *pstCurrPlmn        = VOS_NULL_PTR;

    pstCurrPlmn = NAS_MML_GetCurrCampPlmnId();

    if (VOS_TRUE != NAS_MMC_IsCampLteNormalService())
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(pstCurrPlmn))
    {
        return VOS_TRUE;
    }

    NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvMsccCLAssociatedInfoNtf_OnPlmn:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                                 pstCurrPlmn->ulMcc, pstCurrPlmn->ulMnc);

    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* ���������ͷ����� */
        NAS_MMC_SndLmmRelReq();
    }
    else
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* �����ڲ��������� */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST, VOS_NULL, 0);
    }

    return VOS_TRUE;
}
#endif
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiHplmnTimerExpired_OnPlmn
 ��������  : On plmn������յ�HPLMN��ʱ����ʱ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:HPLMN��ʱ����ʱ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
 3.��    ��   : 2012��4��27��
   ��    ��   : w00176964
   �޸�����   : GUL BG��������:״̬����һ
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiHplmnTimerExpired_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstHighPrioPlmnSearchList = VOS_NULL_PTR;

    /* ��ȡ�����ȼ������б���Ϣ */
    pstHighPrioPlmnSearchList = NAS_MMC_GetHighPrioPlmnList();

    /* ��ʼ�������ȼ������б� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstHighPrioPlmnSearchList);

    /* ����BG����״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_BG_PLMN_SEARCH);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiTryingHighPrioPlmnSearchExpired_OnPlmn
 ��������  : On plmn������յ������Գ��Ը����ȼ�������ʱ����ʱ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:HPLMN��ʱ����ʱ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��4��27��
   ��    ��   : w00176964
   �޸�����   : GUL BG��������:״̬����һ
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiTryingHighPrioPlmnSearchExpired_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    /* ����BG����״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_BG_PLMN_SEARCH);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiHighPrioRatHplmnSrchTimerExpired_OnPlmn
 ��������  : On plmn������յ�TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER��ʱ����ʱ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:HPLMN��ʱ����ʱ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiHighPrioRatHplmnSrchTimerExpired_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *pstHighPrioPlmnSearchList = VOS_NULL_PTR;

    /* ��ȡ�����ȼ������б���Ϣ */
    pstHighPrioPlmnSearchList = NAS_MMC_GetHighPrioPlmnList();

    /* ��ʼ�������ȼ������б� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_RAT_HPLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstHighPrioPlmnSearchList);

    /* ����BG����״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_BG_PLMN_SEARCH);

    return VOS_TRUE;
}



/**************************L1 Main��������**************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildCoverageRatPrioList_L1Main
 ��������  : ����������Ľṹ�У����쵱ǰ������������Ƚ��뼼���б�;
             ���н��뼼��������ʱ��ʹ�� SYSCFG�趨�Ľ��뼼�����Ե�ǰģΪ������
 �������  : pstPlmnSelectionRslt-�������
 �������  : pstRatPrioList-���ȼ��б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��13��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��30��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:disable LTE��ANYCELLʱ��ѡ��LTE������

  3.��    ��   : 2012��9��20��
    ��    ��   : z40661
    �޸�����   : DTS2012082006273,δ֪ͨLģdisableʱ,���ý�Lģ������������

  4.��    ��   : 2012��11��05��
    ��    ��   : w00176964
    �޸�����   : DTS2011082405001:������������е����縲�����Ͷ�RAT���б��������
  5.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : PCINT����
*****************************************************************************/
VOS_VOID NAS_MMC_BuildCoverageRatPrioList_L1Main(
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstPlmnSelectionRslt,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList
)
{
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstRatSearchInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIdx;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucFoundLteRat;
#endif
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8                        enFirstCovType;
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8                        enSecondCovType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enTmpRat;
    VOS_UINT32                                              j;

    ulIdx               =  0;
    pstRatSearchInfo    =  pstPlmnSelectionRslt->astSearchRatInfo;
#if (FEATURE_ON == FEATURE_LTE)
    ucFoundLteRat       = VOS_FALSE;
#endif

    /* ����������ṹ�У���ȡ��ǰ������������Ƚ��뼼���б� */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )
    {
        if (VOS_TRUE == NAS_MML_IsNetRatSupported(pstRatSearchInfo[i].enRatType))
        {
#if (FEATURE_ON == FEATURE_LTE)

            /* ��ȡLTE������״̬ */
            enLteCapabilityStatus   = NAS_MML_GetLteCapabilityStatus();


            /* ���뼼��ΪLTE�ҵ�ǰLTE״̬Ϊdisableʱ����ѡ��LTE������ */
            if (((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  == enLteCapabilityStatus)
              || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS  == enLteCapabilityStatus))
             && (NAS_MML_NET_RAT_TYPE_LTE   == pstRatSearchInfo[i].enRatType))
            {
                if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  == enLteCapabilityStatus)
                {
                    ucFoundLteRat = VOS_TRUE;
                }
                continue;
            }
#endif
            /* Modified by z00234330 for PCLINT����, 2014-06-16, begin */
            if (VOS_FALSE == pstRatSearchInfo[i].ucSearchAllBand)
            {
                pstRatPrioList->aucRatPrio[ulIdx] = pstRatSearchInfo[i].enRatType;
                ulIdx++;
            }
            else if ((NAS_MMC_COVERAGE_TYPE_HIGH == pstRatSearchInfo[i].enCoverageType)
                  || (NAS_MMC_COVERAGE_TYPE_LOW  == pstRatSearchInfo[i].enCoverageType))
            {
                pstRatPrioList->aucRatPrio[ulIdx] = pstRatSearchInfo[i].enRatType;
                ulIdx++;
            }
            else
            {

            }
            /* Modified by z00234330 for PCLINT����, 2014-06-16, end */
        }
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* Modified by z00234330 for PCLINT����, 2014-06-16, begin */
    if (VOS_TRUE == ucFoundLteRat)
    {
        pstRatPrioList->aucRatPrio[ulIdx] = NAS_MML_NET_RAT_TYPE_LTE;
        ulIdx++;
    }
    /* Modified by z00234330 for PCLINT����, 2014-06-16, end */
#endif

    /* ���н��뼼��������ʱ��ʹ�� SYSCFG�趨�Ľ��뼼�� */
    pstRatPrioList->ucRatNum = (VOS_UINT8)ulIdx;

    /* ��ǰ���뼼��֧��ʱ���Ե�ǰ���뼼�������� */
    NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), pstRatPrioList);

    /* ����ÿ�ֽ��뼼���ĸ�����������,�������͸ߵ�����ǰ�� */
    for (i = 0; i < pstRatPrioList->ucRatNum; i++)
    {
        for (j = i+1; j < pstRatPrioList->ucRatNum; j++)
        {
            enFirstCovType = NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(pstRatSearchInfo, pstRatPrioList->aucRatPrio[i]);
            enSecondCovType = NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(pstRatSearchInfo, pstRatPrioList->aucRatPrio[j]);

            /* �������͸ߵ����ȼ���,����ǰ��,���Ƚ���anycell���� */
            if ((enFirstCovType     < enSecondCovType)
             && (enFirstCovType     != NAS_MMC_COVERAGE_TYPE_BUTT)
             && (enSecondCovType    != NAS_MMC_COVERAGE_TYPE_BUTT))
            {
                enTmpRat                            = pstRatPrioList->aucRatPrio[i];
                pstRatPrioList->aucRatPrio[i]       = pstRatPrioList->aucRatPrio[j];
                pstRatPrioList->aucRatPrio[j]       = enTmpRat;
            }
        }
    }
}

/* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main
 ��������  : ����ANYCELL����,������Ҫanycell�ѵĽ��뼼��ΪGU,����˳����syscfg����
 �������  : pstSyscfgRatPrioList - syscfg���õĽ��뼼�����ȼ�
 �������  : pstRatPrioList       - ���ȼ��б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��14��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSyscfgRatPrioList,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucRatNum;
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;

    ucRatNum = 0;

    for (i = 0; i < pstSyscfgRatPrioList->ucRatNum; i++)
    {
        if (pstSyscfgRatPrioList->aucRatPrio[i] != NAS_MML_NET_RAT_TYPE_LTE)
        {
            stAnycellSrchRatList.aucRatPrio[ucRatNum] = pstSyscfgRatPrioList->aucRatPrio[i];
            ucRatNum++;
        }
    }

    stAnycellSrchRatList.ucRatNum = ucRatNum;
   *pstRatPrioList                = stAnycellSrchRatList;

}

/* Modified by z00161729 for DCM�����������������, 2012-8-14, end */


/*****************************************************************************
 �� �� ��  : NAS_MMC_DelDiffMccRplmnInNv_L1Main
 ��������  : ��NV�е�RPLMN�͵�ǰ��RPLMN�����벻ͬʱ��ɾ��NV�е�RPLMN
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_DelDiffMccRplmnInNv_L1Main(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList;
    NAS_MML_PLMN_ID_STRU               *pstNVRplmn;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo     = NAS_MML_GetRplmnCfg();

    /* ˫ģ����£������ǰפ����������Ч������NV�е�RPLMN�͵�ǰ�����������
       ��ͬ��ɾ��NV�е�RPLMN */
    pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&(pstCampPlmnInfo->stLai.stPlmnId)))
    {
        return;
    }

    /* �Ե�ǰ֧�ֵ����н��뼼��������������� */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);

    for ( i = 0 ; i < pstPrioRatList->ucRatNum; i++ )
    {
        switch (pstPrioRatList->aucRatPrio[i] )
        {
            case NAS_MML_NET_RAT_TYPE_GSM:
                pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);
                break;

            case NAS_MML_NET_RAT_TYPE_WCDMA:
                pstNVRplmn = &(pstRplmnCfgInfo->stWRplmnInNV);
                break;

            default:
                continue;
        }
        /* ��ǰ */
        if (pstNVRplmn->ulMcc != pstCampPlmnInfo->stLai.stPlmnId.ulMcc)
        {
            pstNVRplmn->ulMcc = NAS_MML_INVALID_MCC;
            pstNVRplmn->ulMnc = NAS_MML_INVALID_MNC;
        }

    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnSearchNeeded_L1Main
 ��������  : ����CS/PS��additional��ȷ��״̬���Ƿ���Ҫ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ����
             VOS_FALSE: ����Ҫ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnSearchNeeded_L1Main(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enPsAdditionalAction;

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();

    enAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* �ж��Ƿ���Ҫ����������Ҫ����ֱ�ӷ��� */
    if ( VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsLRegFailTriggerInterPlmnList_L1Main
 ��������  : L��ע��ʧ���Ƿ񴥷��ڲ��б�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ҫ�����ڲ��б�����
             VOS_FALSE: ����Ҫ�����ڲ��б�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��11��
    ��    ��   : w00176964
    �޸�����   : DTS2014030508059:GTLģʽ�ڲ�LIST����ת��Ϊָ����������
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsLRegFailTriggerInterPlmnList_L1Main(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    VOS_UINT8                                               ucInterPlmnListFlg;

    ucInterPlmnListFlg  = VOS_FALSE;

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();

    /* Added by s00261364 for L-C��������Ŀ, 2014-3-7, begin */
    if (NAS_MMC_REG_CONTROL_BY_3GPP_MMC != NAS_MMC_GetRegCtrl())
    {
        return VOS_FALSE;
    }
    /* Added by s00261364 for L-C��������Ŀ, 2014-3-7, end */

    /* �����ֻ�ģʽ�ж��Ƿ���Ҫ�ڲ�LIST���� */
    switch (NAS_MML_GetMsMode())
    {
        case NAS_MML_MS_MODE_PS_ONLY:

            /* PS ONLYʱע��ﵽ�����������ڲ�LIST���� */
            if ((NAS_MML_MAX_PS_REG_FAIL_CNT <= NAS_MMC_GetPsRegAttemptCount_L1Main())
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enPsAdditionalAction))
            {
                ucInterPlmnListFlg =  VOS_TRUE;
            }

            break;

        case NAS_MML_MS_MODE_PS_CS:

            /* LTE��CS+PSʱ������CS���Դ���,����ֻ�ж�PS����*/
            if ((NAS_MML_MAX_PS_REG_FAIL_CNT <= NAS_MMC_GetPsRegAttemptCount_L1Main())
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enCsAdditionalAction)
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enPsAdditionalAction))
            {
                ucInterPlmnListFlg =  VOS_TRUE;
            }

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsLRegFailTrigerInterPlmnList_L1Main:Unexpected MS mode!");

            break;
    }

    /* ����tds��֧�ֱ�����,֧��TD��GTLģʽ�������ڲ�list����Ϊ����ʱ��̫����ֱ����ָ������ */
    if (VOS_TRUE == ucInterPlmnListFlg)
    {
        if (VOS_TRUE == NAS_MMC_IsNetRatSupportedTdscdma())
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsGURegFailTriggerIntraPlmnList_L1Main
 ��������  : GU��ע��ʧ���Ƿ񴥷��ڲ��б�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ҫ�����ڲ��б�����
             VOS_FALSE: ����Ҫ�����ڲ��б�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��11��
    ��    ��   : w00176964
    �޸�����   : DTS2014030508059:GTLģʽ�ڲ�LIST����ת��Ϊָ����������
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsGURegFailTriggerInterPlmnList_L1Main(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    VOS_UINT32                                              ulCsRegCount;
    VOS_UINT32                                              ulPsRegCount;
    VOS_UINT8                                               ucInterPlmnListFlg;

    ucInterPlmnListFlg  = VOS_FALSE;

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();

    /* ��ȡCS/PS��ע�᳢�Դ��� */
    ulCsRegCount = NAS_MMC_GetCsRegAttemptCount_L1Main();
    ulPsRegCount = NAS_MMC_GetPsRegAttemptCount_L1Main();

    /* �����ֻ�ģʽ�ж��Ƿ���Ҫ�ڲ�LIST���� */
    switch (NAS_MML_GetMsMode())
    {
        case NAS_MML_MS_MODE_CS_ONLY:

            /* CS ONLYʱע��ﵽ�����������ڲ�LIST���� */
            if ((NAS_MML_GetRoamBrokerRegisterFailCnt() <= ulCsRegCount)
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enCsAdditionalAction))
            {
                ucInterPlmnListFlg =  VOS_TRUE;
            }

            break;

        case NAS_MML_MS_MODE_PS_ONLY:

            /* PS ONLYʱע��ﵽ�����������ڲ�LIST���� */
            if ((NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enPsAdditionalAction)
             && (NAS_MML_MAX_PS_REG_FAIL_CNT <= ulPsRegCount))
            {
                ucInterPlmnListFlg =  VOS_TRUE;
            }

            break;

        case NAS_MML_MS_MODE_PS_CS:

            /* CS+PSʱ���CS/PSע��ͬʱ�ﵽ�����������ڲ�LIST���� */
            if ((NAS_MML_GetRoamBrokerRegisterFailCnt() <= ulCsRegCount)
             && (NAS_MML_MAX_PS_REG_FAIL_CNT <= ulPsRegCount)
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enCsAdditionalAction)
             && (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enPsAdditionalAction))
            {
                ucInterPlmnListFlg =  VOS_TRUE;
            }

            break;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_IsGuRegFailTrigerInterPlmnList_L1Main:Unexpected MS mode!");

            break;
    }

    /* ����tds��֧�ֱ�����,֧��TD��GTLģʽ�������ڲ�list����Ϊ����ʱ��̫����ֱ����ָ������ */
    if (VOS_TRUE == ucInterPlmnListFlg)
    {
        if (VOS_TRUE == NAS_MMC_IsNetRatSupportedTdscdma())
        {
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main
 ��������  : availtimer ��ʱ�Ƿ񴥷�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ҫ��������
             VOS_FALSE: ����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��1��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��1��16��
    ��    ��   : t00212959
    �޸�����   : DTS2013011501766:OnPlmnʱ����Ч����Ҫ����
  3.��    ��   : 2013��10��17��
    ��    ��   : l65478
    �޸�����   : DTS2013102103487:DT����:�ڵ���ʧ��ʱҲ��Ҫ��������
  4.��    ��   : 2014��5��15��
    ��    ��   : w00167002
    �޸�����   : DTS2014051501018:DSDS��MODEM����绰����MODEM����ʧ������AVAILABLE
                 ��ʱ�����û������б��ѣ����б��ѹ����У�����������ʱ����ʱ���б���
                 ������MMCû����������������ʱ����
                 �޸�Ϊ:���б���NO RF�󣬶�����AVAILABLE��ʱ������AVAILABLE��ʱ��
                 ��ʱ�����������ǰ����#12����������ǰACCESS BAR��������
  5.��    ��   : 2016��3��3��
    ��    ��   : z00301431
    �޸�����   : DTS2016030400205:AREA LOST��������pref band���ѵ�һ��available plmn��
                 ϵͳ��Ϣָʾaccess barred������������פ����С����available��ʱ����ʱ
                 ��Ҳ�������������ʹ��NV 9228���ƣ�����򿪸�NV�����������
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main(VOS_VOID)
{
    VOS_UINT32                          ulUsimStatusValid;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enPrioAdditionalAction;

    ulUsimStatusValid   = NAS_MML_IsUsimStausValid();

    /* ȡ��CS/PS��additionֵ */
    enCsAdditionalAction    = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction    = NAS_MMC_GetPsRegAdditionalAction_L1Main();
    enPrioAdditionalAction  = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);


    /* OnPLmn����Ч����Ҫ���� */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* OnPLmn����Ч����Ҫ���� */
        if ( VOS_FALSE == ulUsimStatusValid )
        {
            /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, begin */
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main:ulUsimStatusValid IS FALSE AND CAMP ON! ");
            /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, end */
            return VOS_FALSE;
        }


        /* �����ǰפ�����类#12�ܾ�����Ҫ���� */
        if (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enPrioAdditionalAction)
        {
            /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, begin */
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main: #12.");
            /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, end */

            return VOS_FALSE;
        }

        /* �����ǰפ�����紦��ACCESS BAR������Ҫ���� */
        if (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enPrioAdditionalAction)
        {
            /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, begin */
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main: ACCESS BAR.");
            /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, end */

            if (VOS_TRUE != NAS_MMC_IsAccBarPlmnSearch())
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main: NAS_MMC_IsAccBarPlmnSearch return false.");
                return VOS_FALSE;
            }
        }

    }



    /* ��ǰ���ڷ���������״̬�������� */
    if (VOS_FALSE == NAS_MMC_IsNormalServiceStatus())
    {
        /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main: NORMAL SERVICE IS FALSE.");
        /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, end */
        return VOS_TRUE;
    }

    /* ��ǰNASΪδפ��״̬ */
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main: PLMN SEARCH RUNNING.");
        /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, end */
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MMC_IsCsPsMode1NeedPeriodSearchGU())
    {
        /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main: NAS_MMC_IsCsPsMode1NeedPeriodSearchGU true.");
        /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, end */

        return VOS_TRUE;
    }
#endif

    if (VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS))
    {
        return VOS_TRUE;
    }

    /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, begin */
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main:RETURN FALSE END.");
    /* Added by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, end */

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsAvailTimerExpiredTriggerInterPlmnList_L1Main
 ��������  : availtimer ��ʱ�Ƿ񴥷��ڲ��б�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ҫ�����ڲ��б�����
             VOS_FALSE: ����Ҫ�����ڲ��б�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��7��2��
    ��    ��   : z00161729
    �޸�����   : DTS2012063000279:L�ڲ�list��forbidden tai�ж�������Ҫ��GU����һ��
  3.��    ��   : 2012��7��19��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1��LTE��PS����Ч��Ҫ����ָ������
  4.��    ��   : 2013��10��17��
    ��    ��   : l65478
    �޸�����   : DTS2013102207188:DT����:��PS����ʧ��#14ʱҲ��Ҫ��������
  5.��    ��   : 2014��1��26��
    ��    ��   : z00161729
    �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL������
  6.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAvailTimerExpiredTriggerInterPlmnList_L1Main(VOS_VOID)
{
    VOS_UINT32                          ulUsimStatusValid;
    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8  enCampStatus;
    VOS_UINT32                          ulForbidFlag;

    VOS_UINT32                          ulForbidType;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucSimPsRegStatus;
#endif

    /* Ĭ�ϲ��ڽ�ֹ�б��� */
    ulForbidFlag        = VOS_FALSE;

    ulUsimStatusValid   = NAS_MML_IsUsimStausValid();

#if (FEATURE_ON == FEATURE_LTE)

    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    /* LTE��ģ�����PS����Ч��ʱ��Ҳ��Ϊ��ʱ����Ч */
    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     && (VOS_FALSE == ucSimPsRegStatus))
    {
        ulUsimStatusValid = VOS_FALSE;
    }
#endif

    /* �ж�available timer��ʱ�Ƿ񴥷��ڲ��б�������
       ����tds��֧�ֱ����ѣ�GTLģʽ�������ڲ�list����Ϊ����ʱ��̫����ֱ����ָ������ */
    if (VOS_TRUE == NAS_MMC_IsNetRatSupportedTdscdma())
    {
        return VOS_FALSE;
    }

    /* Added by s00246516 for L-C��������Ŀ, 2014-03-04, Begin */
    if (NAS_MMC_REG_CONTROL_BY_3GPP_MMC != NAS_MMC_GetRegCtrl())
    {
        return VOS_FALSE;
    }
    /* Added by s00246516 for L-C��������Ŀ, 2014-03-04, End */

    /* �Ƿ����㴥���ڲ�LIST����������:��ǰ����Ч,��Ϊפ��״̬���Ҳ��ڽ�ֹ������Ϣ�� */
    enCampStatus = NAS_MMC_GetAsCellCampOn();

    /* ��ȡ��ǰ��LA(GU��)��TA(L��)�Ƿ��ڽ�ֹ�б��� */
    ulForbidType = NAS_MMC_GetCurrentLaiForbbidenType();
    if (NAS_MML_PLMN_FORBID_NULL != ulForbidType)
    {
        if ((NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION == NAS_MMC_GetSingleDomainFailAction(NAS_MML_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN))
         && (NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS == ulForbidType))
        {
            ulForbidFlag = VOS_FALSE;
        }
        else
        {
            ulForbidFlag = VOS_TRUE;
        }
    }

    /* ��ǰפ��̬,����Ч,���ڽ�ֹLA/TA�б����������ڲ��б����� */
    if ((VOS_TRUE  == ulUsimStatusValid)
     && (VOS_FALSE == ulForbidFlag)
     && (NAS_MMC_AS_CELL_CAMP_ON == enCampStatus))
    {

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PerformPlmnSearch_L1Main
 ��������  : ����CS/PS��additional�����������Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ����
             VOS_FALSE: ����Ҫ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��5��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIII:����ע�����
 3.��    ��   : 2011��11��17��
   ��    ��   : w00167002
   �޸�����   : L1Main�����������������������

 4.��    ��   : 2011��11��30��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase IV����:disable LTE��Ҫ������GU�ĵ���
 4.��    ��   : 2012��2��16��
    ��    ��   : h00202780
    �޸�����   : CSFB&PPAC&ETWS&ISR CSFBʧ����Ҫ������GU�ĳ������������޸�
 5.��    ��   : 2012��3��27��
   ��    ��   : w00166186
   �޸�����   : CSFB&PPAC&ETWS&ISR ���� ENERGENCY CALL
 6.��    ��   : 2012��4��17��
   ��    ��   : z00161729
   �޸�����   : DTS2012041400766
 7.��    ��   : 2012��8��14��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�,֧��L��������
 8.��    ��   : 2013��10��17��
   ��    ��   : l65478
   �޸�����   : DTS2013102103487:DT����:�ڵ���ʧ��ʱҲ��Ҫ��������
 9.��    ��   : 2013��3��11��
   ��    ��   : w00176964
   �޸�����   : DTS2014030508059:GTLģʽ�ڲ�LIST����ת��Ϊָ����������
*****************************************************************************/
VOS_UINT32 NAS_MMC_PerformPlmnSearch_L1Main(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    VOS_UINT32                                              ulSingleDomainPlmnListFlg;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurrentRat;
    NAS_MMC_REG_RSLT_TYPE_ENUM_UINT8                        enRegRsltType;

    /* Modified by z00161729 for DCM�����������������, 2012-8-13, begin */
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enCsfbServiceStatus;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;

    enCsfbServiceStatus  = NAS_MML_GetCsfbServiceStatus();
    pstPrioRatList       = NAS_MML_GetMsPrioRatList();

    /* ��ȡ��ǰLTE�����Ƿ���� */
    enCurrentRat   = NAS_MML_GetCurrNetRatType();

    /* ��ȡ��ǰ��ע�������� */
    enRegRsltType  = NAS_MMC_GetRegRsltType();
    /* Modified by z00161729 for DCM�����������������, 2012-8-13, end */
#endif

    /* �µ�����:����ע��ʧ�ܷ����������Դ�ʱ,���ע��ʧ��ԭ��ֵ��#17,��Ҫ�������� */
    ulSingleDomainPlmnListFlg = NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS);
    ulSingleDomainPlmnListFlg |= NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS);

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();

    enAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);


    /* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
    /* �����csfb �������У���Ҫanycell���� */
#if (FEATURE_ON == FEATURE_LTE)
    if ((NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == enCsfbServiceStatus)
     && (LMM_MMC_SERVICE_RESULT_IND == enRegRsltType))
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* ����ANYCELL����,������Ҫanycell�ѵĽ��뼼��ΪGU,����˳����syscfg���� */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);

        /* ��������������additional��ֵ */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* ����������������������� */
        NAS_MMC_SetBufferedPlmnSearchInfo(VOS_FALSE, NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        return VOS_TRUE;
    }

    /* ��ǰ������L������ע�ᱻ��#7���µģ���Ҫ����L��GU������ */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS  == NAS_MML_GetLteCapabilityStatus())
     && (NAS_MML_NET_RAT_TYPE_LTE == enCurrentRat))
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* ����������Ϣ */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE, VOS_NULL_PTR, 0);

        /* ��������������additional��ֵ */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();


        /* ����������������������� */
        NAS_MMC_SetBufferedPlmnSearchInfo(VOS_FALSE, NAS_MMC_PLMN_SEARCH_SCENE_BUTT);

        return VOS_TRUE;
    }

#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-14, end */

    /* ����tds��֧�ֱ�����,֧��TD��GTLģʽ�������ڲ�list����Ϊ����ʱ��̫����ֱ����ָ������ */
    if ((VOS_TRUE == NAS_MMC_IsNetRatSupportedTdscdma())
     && (VOS_TRUE == ulSingleDomainPlmnListFlg))
    {
        ulSingleDomainPlmnListFlg =  VOS_FALSE;
    }

    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL == enAdditionalAction))
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }
    else if (NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN == enAdditionalAction)
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* ����������Ϣ */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_CURRENT_PLMN_SEARCH,VOS_NULL_PTR, 0);
    }
    /* CSFB�����У�L��service������Ҫ���� */
#if (FEATURE_ON == FEATURE_LTE)
    else if ( (VOS_TRUE                   == NAS_MML_IsCsfbServiceStatusExist())
           && (LMM_MMC_SERVICE_RESULT_IND == enRegRsltType) )
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ, VOS_NULL_PTR, 0);

    }
#endif
    else if (VOS_TRUE == ulSingleDomainPlmnListFlg)
    {
        NAS_MMC_SndInterPlmnListReq();

        /* ����������ͬʱ���CS/PS��ע�᳢�Դ��� */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();
    }
    else
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        /* ����������Ϣ */
        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_PLMN_SEARCH, VOS_NULL_PTR, 0);
    }

    /* ��������������additional��ֵ */
    NAS_MMC_ClearAllRegAdditionalAction_L1Main();


    /* ����������������������� */
    NAS_MMC_SetBufferedPlmnSearchInfo(VOS_FALSE, NAS_MMC_PLMN_SEARCH_SCENE_BUTT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PerformBufferedPlmnSearch_L1Main
 ��������  : �������ָ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��06��07��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1���������Availabe Timer��ʱ����Ҫ�����ڲ��б��Ѻ�ָ������
  3.��    ��   : 2013��1��11��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII ��Ŀ�޸�:����IMS�����û����disable LTE�������ڲ�������������
  4.��    ��   : 2014��2��19��
    ��    ��   : s00217060
    �޸�����   : coverity����
*****************************************************************************/
VOS_VOID NAS_MMC_PerformBufferedPlmnSearch_L1Main(VOS_VOID)
{
    VOS_UINT32                          ulSpecPlmnSearchFlg;
    VOS_UINT32                          ulIsNeedPlmnSearch;
    VOS_UINT32                          ulIsNeedInterPlmnList;
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-11, begin */
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32   enPlmnSearchScene;
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-11, end */

    /* ���ע��ʧ�ܲ���Ҫ��������,���ж��Ƿ��л����������־ */
    if (VOS_FALSE == NAS_MMC_GetBufferedPlmnSearchFlg())
    {
        return;
    }

    ulIsNeedPlmnSearch    = NAS_MMC_IsAvailTimerExpiredTriggerPlmnSearch_L1Main();
    ulIsNeedInterPlmnList = NAS_MMC_IsAvailTimerExpiredTriggerInterPlmnList_L1Main();
    ulSpecPlmnSearchFlg   = NAS_MMC_GetSpecPlmnSearchState();
    /* Modified by s00217060 for coverity����, 2014-02-19, begin */
    enPlmnSearchScene = NAS_MMC_GetBufferedPlmnSearchScene();

    if ((NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED == enPlmnSearchScene)
     && (VOS_TRUE == ulIsNeedPlmnSearch)
     && (VOS_TRUE == ulIsNeedInterPlmnList))
    {
        NAS_MMC_SndInterPlmnListReq();

        /* ��������������additional��ֵ */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* ����������ͬʱ���CS/PS��ע�᳢�Դ��� */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();
    }
    else
    {
        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-11, begin */

        /* ��ǰ�������������ָ������״̬��disable LTEʱ�Ŵ������ָ������ */
        if ((VOS_FALSE                              == NAS_MMC_IsNormalServiceStatus())
         || (NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE  == enPlmnSearchScene)
         || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING       == ulSpecPlmnSearchFlg))
        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-11, end */
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

            NAS_MMC_SndInterPlmnSearchReq(enPlmnSearchScene, VOS_NULL_PTR, 0);
        }
    }
    /* Modified by s00217060 for coverity����, 2014-02-19, end */

    /* ��ջ����������־ */
    NAS_MMC_SetBufferedPlmnSearchInfo(VOS_FALSE, NAS_MMC_PLMN_SEARCH_SCENE_BUTT);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcGmmServiceRequestResultInd_L1Main
 ��������  : ��GMM��GMMMMC_SERVICE_REQUEST_RESULT_IND��Ϣ�Ĵ���
 �������  : pstServiceRsltInd GMMMMC_SERVICE_REQUEST_RESULT_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
  3.��    ��   : 2012��2��13��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                  �򲻸��µ�ǰ��additional action
  4.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
*****************************************************************************/
VOS_VOID NAS_MMC_ProcGmmServiceRequestResultInd_L1Main(
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    enAdditionalAction      = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    /* ����Service Reqest Result ��������ͬ���� */
    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstServiceRsltInd->enActionResult)
    {
        /* ����PS��AdditionalAction */
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

#if (FEATURE_ON == FEATURE_LTE)
        /* ��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨ ����LMM����Service requestResult�����Ϣ����*/
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcPsServiceRegFail(pstServiceRsltInd);

#if (FEATURE_ON == FEATURE_LTE)
        /* ��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨ����LMM����Service requestResult�����Ϣ���� */
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = pstServiceRsltInd->enRegFailCause;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif
    }

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegRslt_L1Main
 ��������  : ��Psע�����Ĵ���
 �������  : pstPsRegRsltInd PSע������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��21��
   ��    ��   : w00167002
   �޸�����   : DTS2011111806904:�ֶ�ģʽ����ϵͳ��ѡ,��EPLMN��ע�ᱻ��ԭ��ֵ
                 #17������EPLMN��������յ�ϵͳ��Ϣ��MMCת����MM/GMM��ϵͳ
                 ��Ϣʱ���FORB PLMN��־������T3211��ʱ�󣬲�����ע�ᡣ
                 �޸ķ���������������£�������������û�ָ����PLMN��

 3.��    ��   : 2011��11��28��
   ��    ��   : w00167002
   �޸�����   : DTS2011112406707:����ǰΪ�������ҵ�ǰ��AdditionalAction��Ϊ
                ��ʼ��Чֵ���򲻸��µ�ǰ��AdditionalAction��ֵ����������ǰΪ
                �����̻�ǰΪ��������AdditionalActionΪ��ʼ��Чֵ�������
                ��ǰ��AdditionalAction��ֵ.
                �޸�ԭ��:��ROAMING BROKERʱ������1��ʧ��,ע��ʧ��1�κ�
                MMC��Ҫ����������MMC����Ҫ��������Ľ��(����ѡ��״̬��)��
                ���յ�ϵͳ��Ϣ��ʱ�򣬼����̻����MMC��AdditionalAction��ֵ,
                ����ROMING BROKER����ʧЧ��

  4.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ

 5.��    ��   : 2011��12��17��
   ��    ��   : w00166186
   �޸�����   : dts2011120603107����һ����������С����ѡ��һ����֧��GPRS��С������ͣ����LAU

 6.��    ��   : 2012��1��3��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������
                ͳһ����ע��ADDITIONAL ACTION��ֵ�������û��Զ����ԭ��ֵ(>=256)����
                ������ע����������ǰ֧��Lģ����ע��ԭ��ֵС��260ʱ֪ͨLMM��ǰ��ע����.
                ���������̣�MMC����Ҫ֪��MM/GMM�ϱ����Ƿ���������̡�

  7.��    ��   : 2012��1��6��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:ɾ��DTS2011111806904�ڴ˺������������޸ģ�
                 ���˸Ķ������ݵ���������OTHER CAUSE�ĺ����С�
  8.��    ��   : 2012��3��1��
    ��    ��   : w00176964
    �޸�����   : DTS2012022407450:����GMM������RAU/ATTACH���ͣ�MMCת����LMM
  9.��    ��   : 2012��03��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012032307791,����LMMע����,CombineRegʱ��Ҫ���ֽ����
 10.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
 11.��    ��   : 2012��6��8��
    ��    ��   : l00130025
    �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨAPS/CDS��Ϣ���޷�����
 12.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
 13.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
 14.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 15.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
 16.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
 17.��    ��   : 2014��04��9��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:���ӷ���״̬�ϱ�����
 18.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID NAS_MMC_ProcPsRegRslt_L1Main(
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
)
{
    NAS_MML_LAI_STRU                                       *pstLai         = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, end */

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
    NAS_MML_PROC_TYPE_ENUM_U32                              enProcType;

    /* ת�����͸�L��proctype */
    enProcType = NAS_MML_PROC_BUTT;

    NAS_MMC_ConverGmmActionTypeToMml(pstPsRegRsltInd->enGmmActionType, &enProcType);


    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enReqDomain, &stActionRslt.enReqDomain);

    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enRsltDomain, &stActionRslt.enRstDomain);



#endif
    pstLai              = NAS_MML_GetCurrCampLai();

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-10, end */

    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstPsRegRsltInd->enActionResult)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-10, begin */
        /* ����ע������Ϣ */
        NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_REG_RESULT_IND, pstPsRegRsltInd);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-10, end */

        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_NULL);

        NAS_MMC_ClearHplmnRejDomainInfo(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS);

        if (VOS_TRUE == NAS_MML_GetKeepCsForbInfoCfg())
        {
            /* ֻɾ��Forb GPRS PLMN��Ϣ��CS���FORB��Ϣ��Ȼ���� */
            NAS_MML_DelForbGprsPlmn(&(pstLai->stPlmnId));
        }
        else
        {
            /* ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ */
            NAS_MMC_DelForbInfo_GuRegRsltSucc(NAS_MMC_REG_DOMAIN_PS);
        }


        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());


        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

#if   (FEATURE_ON == FEATURE_LTE)
        /* ��ǰSYSCFG��L����ʱ����Ҫ��LMM֪ͨ */
        /* �����̲�֪ͨ��LMM */
        if ( VOS_TRUE == NAS_MML_IsRegFailCauseNotifyLmm(pstPsRegRsltInd->enRegFailCause) )
        {
            stActionRslt.enProcType     = enProcType;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
            stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
            stActionRslt.ulAttemptCount = 0;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, pstPsRegRsltInd->enRegFailCause);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcPsRegFail(GMM_MMC_PS_REG_RESULT_IND,
                                                   pstPsRegRsltInd);

        /* С�� NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE�ľܾ�ԭ����������ʵ�ʽ����õ���ֵ����Ҫ֪ͨLMM */
        if ( VOS_TRUE == NAS_MML_IsNetworkRegFailCause(pstPsRegRsltInd->enRegFailCause) )
        {
            /* ֻ�ڸ�������ʵ����������ʱ��Ÿ���ע����Ϣ�� */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS, pstPsRegRsltInd->enRegFailCause);
        }

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(pstPsRegRsltInd->enRegFailCause);

#if   (FEATURE_ON == FEATURE_LTE)

        /* С�� NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE�ľܾ�ԭ����UE���Է���ע���ԭ��ֵ����Ҫ֪ͨLMM */
        if ( VOS_TRUE == NAS_MML_IsRegFailCauseNotifyLmm(pstPsRegRsltInd->enRegFailCause) )
        {
            stActionRslt.enProcType     = enProcType;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
            stActionRslt.enCnCause      = pstPsRegRsltInd->enRegFailCause;
            stActionRslt.ulAttemptCount = pstPsRegRsltInd->ulRegCounter;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif

    }

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    NAS_MMC_SetPsRegAttemptCount_L1Main(pstPsRegRsltInd->ulRegCounter);

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegRslt_L1Main
 ��������  : ��Csע�����Ĵ���
 �������  : pstCsRegRsltInd CSע������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��21��
   ��    ��   : w00167002
   �޸�����   : DTS2011111806904:�ֶ�ģʽ����ϵͳ��ѡ,��EPLMN��ע�ᱻ��ԭ��ֵ
                 #17������EPLMN��������յ�ϵͳ��Ϣ��MMCת����MM/GMM��ϵͳ
                 ��Ϣʱ���FORB PLMN��־������T3211��ʱ�󣬲�����ע�ᡣ
                 �޸ķ���������������£�������������û�ָ����PLMN��

 3.��    ��   : 2011��11��28��
   ��    ��   : w00167002
   �޸�����   : DTS2011112406707:����ǰΪ�������ҵ�ǰ��AdditionalAction��Ϊ
                ��ʼ��Чֵ���򲻸��µ�ǰ��AdditionalAction��ֵ����������ǰΪ
                �����̻�ǰΪ��������AdditionalActionΪ��ʼ��Чֵ�������
                ��ǰ��AdditionalAction��ֵ.
                �޸�ԭ��:��ROAMING BROKERʱ������1��ʧ��,ע��ʧ��1�κ�
                MMC��Ҫ����������MMC����Ҫ��������Ľ��(����ѡ��״̬��)��
                ���յ�ϵͳ��Ϣ��ʱ�򣬼����̻����MMC��AdditionalAction��ֵ,
                ����ROMING BROKER����ʧЧ��
  4.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ

  5.��    ��   : 2012��1��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������
                  ͳһ����ע��ADDITIONAL ACTION��ֵ�������û��Զ����ԭ��ֵ(>=256)����
                  ������ע����������ǰ֧��Lģ����ע��ԭ��ֵС��260ʱ֪ͨLMM.

  6.��    ��   : 2012��1��6��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:ɾ��DTS2011111806904�ڴ˺������������޸ģ�
                 ���˸Ķ������ݵ���������OTHER CAUSE�ĺ����С�
  7.��    ��   : 2012��1��20��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:��ע��ʧ�ܵ���Ϣ֪ͨ������ע����������
                  �ܽ��и��õ���չ.
  8.��    ��   : 2012��3��1��
    ��    ��   : w00176964
    �޸�����   : DTS2012022407450:����ATTACHʱ,MM����֪ͨLMM��ʱCS��ע������������TAU�����Ͳ���ȷ
  9.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
 10.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
 11.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
 12.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 13.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
 14.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
 15.��    ��   : 2014��04��9��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:���ӷ���״̬�ϱ�����
 16.��    ��   : 2014��11��3��
    ��    ��   : z00161729
    �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCsRegRslt_L1Main(
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    if (MM_MMC_LU_RESULT_SUCCESS == pstCsRegRsltInd->enLuResult)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /* ����DPLMN NPLMN�б� */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum,pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

            NAS_MMC_LogDplmnNplmnList();
        }
        /* ��Hplmn��Rej Lai��Ϣ����� */
        NAS_MMC_ClearHplmnRejDomainInfo(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS);

        /* ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_GuRegRsltSucc(NAS_MMC_REG_DOMAIN_CS);

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_UpdateCsRegStateCsRegSucc();

        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-3, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NORMAL_SERVICE);
        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-3, end */


#if   (FEATURE_ON == FEATURE_LTE)

        /* ����ע��ʱ��֪ͨLMM��ʱLU�Ľ�� */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRsltInd->enRegFailCause))
         && (VOS_FALSE == pstCsRegRsltInd->ucIsComBined))
        {
            /* ��ǰSYSCFG��L����ʱ����Ҫ��LMM֪ͨ */
            stActionRslt.enProcType     = NAS_MML_PROC_LAU;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
            stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
            stActionRslt.ulAttemptCount = 0;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }


#endif

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_TRUE, pstCsRegRsltInd->enRegFailCause);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcCsRegFail(MM_MMC_CS_REG_RESULT_IND,
                                                   pstCsRegRsltInd);

        if ( VOS_TRUE == NAS_MML_IsNetworkRegFailCause(pstCsRegRsltInd->enRegFailCause) )
        {
            /* ֻ�ڸ�������ʵ����������ʱ��Ÿ���ע����Ϣ�� */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, pstCsRegRsltInd->enRegFailCause);

            /* ����DPLMN NPLMN�б� */
            if (VOS_TRUE == NAS_MMC_IsRoam())
            {
                NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum,pstDPlmnNPlmnCfgInfo->astNPlmnList);
                NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
                NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);

                NAS_MMC_LogDplmnNplmnList();
            }

        }

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(pstCsRegRsltInd->enRegFailCause);

#if   (FEATURE_ON == FEATURE_LTE)

        /* С�� NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE�ľܾ�ԭ����UE���Է���ע���ԭ��ֵ����Ҫ֪ͨLMM */
        /* ����ע��ʱ��֪ͨLMM��ʱLU�Ľ�� */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRsltInd->enRegFailCause))
         && (VOS_FALSE == pstCsRegRsltInd->ucIsComBined))
        {
            /* ��ǰSYSCFG��L����ʱ����Ҫ��LMM֪ͨ */
            stActionRslt.enProcType     = NAS_MML_PROC_LAU;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
            stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enCnCause      = pstCsRegRsltInd->enRegFailCause;
            stActionRslt.ulAttemptCount = pstCsRegRsltInd->ulLuAttemptCnt;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif

    }

    /* AdditionalAction��Ч������CS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    /* ����CSע��ĳ��Դ��� */
    NAS_MMC_SetCsRegAttemptCount_L1Main(pstCsRegRsltInd->ulLuAttemptCnt);

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_AdjustOtherCauseAdditionalAction_OnPlmn
 ��������  : OnPlmnע��ʧ��ʱ����ԭ��ֵOTHER CAUSE��ADDITIONAL����
 �������  : penAdditionalAction: ע��ԭ��ֵӳ���ADDITIONAL ACTION
 �������  : penAdditionalAction: �������ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,
             �ҵ�ǰPLMN����EPlmn�б���ҵ�ǰ��AdditionalֵΪWAIT_REG_ATTEMPT��
             ����Ҫ��������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��21��
   ��    ��   : w00167002
   �޸�����   : DTS2011111806904:�ֶ�ģʽ����ϵͳ��ѡ,��EPLMN��ע�ᱻ��ԭ��ֵ
                 #17�ȣ�����EPLMN��������յ�ϵͳ��Ϣ��MMCת����MM/GMM��ϵͳ
                 ��Ϣʱ���FORB PLMN��־������T3211��ʱ��MM������ע�ᡣ
                 �޸ķ���������������£���EPLMN��ע��ʧ��(ԭ��ֵΪOTHER CAUSE)
                 �����������û�ָ����PLMN�������ڵ�ǰ�����ϼ�������ע�ᡣ
 2.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
               ����ΪNAS_MML_IsBcchPlmnIdInDestSimPlmnList,������ȷ�ж�
               ��������ͣ���������ȽϿ��ܻ����
*****************************************************************************/
VOS_VOID NAS_MMC_AdjustOtherCauseAdditionalAction_OnPlmn(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penAdditionalAction
)
{
    NAS_MML_LAI_STRU                   *pstCurrentLai       = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo        = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn     = VOS_NULL_PTR;
    VOS_UINT32                          ulInEplmnListFlag;
    VOS_UINT32                          ulUserSpecPlmnFlag;

    pstCurrentLai      = NAS_MML_GetCurrCampLai();

    /* �жϵ�ǰ�����Ƿ����û�ָ�������� */
    pstUserSpecPlmn    = NAS_MMC_GetUserSpecPlmnId();
    ulUserSpecPlmnFlag = NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCurrentLai->stPlmnId),
                                                &(pstUserSpecPlmn->stPlmnId));

    /* �жϵ�ǰ�����Ƿ���EPlmn�б��� */
    pstEplmnInfo       = NAS_MML_GetEquPlmnList();

    ulInEplmnListFlag  = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstCurrentLai->stPlmnId),
                                              pstEplmnInfo->ucEquPlmnNum,
                                              pstEplmnInfo->astEquPlmnAddr);

    /* �ֶ�ģʽ�£���ǰPlmn�����û�ָ����PLMN,�ҵ�ǰPLMN����EPlmn�б��
       �ҵ�ǰ���AdditionalֵΪWAIT_REG_ATTEMPT������Ҫ�������� */
    if ( (NAS_MMC_PLMN_SELECTION_MODE_MANUAL         == NAS_MMC_GetPlmnSelectionMode())
      && (VOS_FALSE                                  == ulUserSpecPlmnFlag)
      && (VOS_FALSE                                  == ulInEplmnListFlag)
      && (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == *penAdditionalAction) )
    {
        *penAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION;
    }

    return;
}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmEpsOnlyAttachInd_OnPlmn
 ��������  : Lmm attach����Ĵ�����
 �������  : pstLmmAttachIndMsg L��ATTACH��Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  3.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���

  4.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����
                  ����������NAS_MMC_ProcEpsRegFail����ΪNAS_MMC_ProcEpsAttachRegFail
                  ����ATTACH��ע��ԭ��ֵ����д���
  5.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  6.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
                  additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  7.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : GUL_BG��Ŀ����
  8.��    ��   : 2012��06��01��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  9.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
  9.��    ��   : 2012��6��8��
    ��    ��   : l00130025
    �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨAPS/CDS��Ϣ���޷�����
 10.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
  11.��    ��   : 2012��8��21��
     ��    ��   : z00161729
     �޸�����   : DCM������������������޸�DTS2012090401249

  12.��    ��   : 2012��09��12��
     ��    ��   : z00161729
     �޸�����  : DTS2012082904888��cs ps mode1��on plmn��plmn list��bg plmn search״̬����eps onlyע��ɹ�δ����NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc�ж��Ƿ���Ҫdisable lte
  13.��    ��   : 2012��12��6��
     ��    ��   : s00217060
     �޸�����   : DTS2012120410842:ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ
  14.��    ��   : 2013��3��30��
     ��    ��   : l00167671
     �޸�����   : �����ϱ�AT�������������C��
  15.��    ��   : 2013��05��08��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  16.��    ��   : 2013��12��10��
     ��    ��   : w00176964
     �޸�����   : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
  17.��    ��   : 2014��5��6��
     ��    ��   : z00161729
     �޸�����   : DTS2014050602850:l������ע��eps�ɹ���csע�ᱻ#18�ܾ���disable lte��gu������ע��ɹ�����ָ����l csע�ᱻ#18�ܾ������磬l����eps����ע��ɹ���mmcû��disable lte
  18.��    ��   : 2014��5��5��
     ��    ��   : w00242748
     �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                  ע��״̬���ϱ���
  19.��    ��   : 2015��4��18��
     ��    ��   : z00161729
     �޸�����   : 24301 R11 CR������Ŀ�޸�
  20.��    ��   : 2015��02��11��
     ��    ��   : l00305157
     �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע����ATTACH (EPS ONLY)�ɹ����ϱ�ע��״̬
  21.��    ��   : 2015��06��09��
     ��    ��   : l00305157
     �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע�������ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmEpsOnlyAttachInd_OnPlmn(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */
    VOS_UINT8                                               ucSimCsRegStatus;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverLmmAttachRsltToMMLCause(pstLmmAttachIndMsg,&enRegRsltCause);

    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt)
    {
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);

        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */
        /* ����EPLMN */
        if ( VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

            /* LMM PLMN ID��ʽת��ΪMMC��PLMN ID�ĸ�ʽ  */
            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));

            /* ��EPLMN��Ϣ�������ڴ��� */
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, (stLEplmnInfo.astEquPlmnAddr));

            NAS_MMC_WriteEplmnNvim();
        }

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

        /* EPS����ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, NAS_MMC_IsEpsEmergencyAttachType(pstLmmAttachIndMsg->ulReqType));

        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */


        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */
        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();


        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());


        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }
    else if ((MMC_LMM_ATT_RSLT_FAILURE == pstLmmAttachIndMsg->ulAttachRslt)
          && (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt))
    {
        /* LNAS��������ע�᳢������-��������ȴ��� */
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);

        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

        NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS,NAS_MMC_LIMITED_SERVICE);
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }
    else
    {
        enAdditionalAction= NAS_MMC_ProcEpsAttachRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enRegRsltCause);
    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    /* ����PS��ע�᳢�Դ��� */
    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpAtmpCnt)
    {
        NAS_MMC_SetPsRegAttemptCount_L1Main(pstLmmAttachIndMsg->ulAttemptCount);
    }

    return ;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmAttachInd_OnPlmn
 ��������  : Lmm attach����Ĵ�����
 �������  : pstLmmAttachIndMsg L��ATTACH��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmAttachInd_OnPlmn(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    switch (pstLmmAttachIndMsg->ulReqType)
    {
        case MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI:

            /* ����lmm������attach��� */
            NAS_MMC_ProcLmmCombinedAttachInd_OnPlmn(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_ONLY:

            /* ����lmm�ķ�����attach��EPS onlyע��Ľ�� */
            NAS_MMC_ProcLmmEpsOnlyAttachInd_OnPlmn(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_EMERGENCY:

            /* �ݲ�֧��δʵ�� */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_OnPlmn:Unsupported attach req type!");
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_OnPlmn:Unexpected attach req type!");
            break;

    }
    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmEpsOnlyTauResultInd_OnPlmn
 ��������  : Lmm TAU����Ĵ�����
 �������  : pstLmmTauIndMsg L��TAU��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��28��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  3.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  4.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����
                  ����������NAS_MMC_ProcEpsRegFail����ΪNAS_MMC_ProcEpsTauRegFail
                  ����TAU��ע��ԭ��ֵ����д���
  5.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  6.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
                  additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  7.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : GUL_BG��Ŀ����
  8.��    ��   : 2012��06��01��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  9.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
 10.��    ��   : 2012��6��8��
    ��    ��   : l00130025
    �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨAPS/CDS��Ϣ���޷�����
 11.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
 12.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�DTS2012090401249
 13.��    ��   : 2012��09��12��
    ��    ��   : z00161729
    �޸�����   : DTS2012082904888��cs ps mode1��on plmn��plmn list��bg plmn search״̬����eps onlyע��ɹ�δ����NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc�ж��Ƿ���Ҫdisable lte
 14.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ
 15.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 16.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 17.��    ��   : 2013��12��10��
     ��    ��  : w00176964
     �޸�����  : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
 18.��    ��   : 2014��5��6��
    ��    ��   : z00161729
    �޸�����   : DTS2014050602850:l������ע��eps�ɹ���csע�ᱻ#18�ܾ���disable lte��gu������ע��ɹ�����ָ����l csע�ᱻ#18�ܾ������磬l����eps����ע��ɹ���mmcû��disable lte
 19.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
 20.��    ��   : 2014��5��14��
    ��    ��   : w00242748
    �޸�����   : DTS2014051206381:ö��ֵʹ�ò���
 21.��    ��   : 2015��4��18��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
 22.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע����(EPS ONLY)�ɹ����ϱ�ע��״̬
 23.��    ��   : 2015��06��09��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע�������ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�
 24.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmEpsOnlyTauResultInd_OnPlmn(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */
    VOS_UINT8                                               ucSimCsRegStatus;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                enCsRegAdditionalAction;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverTauResultToMMLCause(pstLmmTauIndMsg, &enRegRsltCause);

    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_NORMAL_CAMP_ON);

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */
        /* ����EPLMN */
        if ( VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, stLEplmnInfo.astEquPlmnAddr);

            /* ��EPLMN��Ϣ�������ڴ��� */
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, (stLEplmnInfo.astEquPlmnAddr));

            NAS_MMC_WriteEplmnNvim();
        }

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

        /* EPS����ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, VOS_FALSE);

        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */

        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();


        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());


        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }
    else if ((MMC_LMM_TAU_RSLT_FAILURE == pstLmmTauIndMsg->ulTauRst)
          && (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt))
    {
        /* LNAS��������ע�᳢������-��������ȴ��� */
        NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);

        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }
    else if (MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC == pstLmmTauIndMsg->ulTauRst)
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          &enAdditionalAction, &enCsRegAdditionalAction);
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcEpsTauRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enRegRsltCause);
    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    /* ����PS��ע�᳢�Դ��� */
    if (VOS_TRUE == pstLmmTauIndMsg->bitOpAtmpCnt)
    {
        NAS_MMC_SetPsRegAttemptCount_L1Main(pstLmmTauIndMsg->ulAttemptCount);
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmTauResultInd_OnPlmn
 ��������  : Lmm TAU����Ĵ�����
 �������  : pstLmmTauIndMsg L��TAU��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��28��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸�������tau����
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmTauResultInd_OnPlmn(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    switch (pstLmmTauIndMsg->ulReqType)
    {
        case MMC_LMM_COMBINED_TA_LA_UPDATING:
        case MMC_LMM_COMBINED_TA_LA_WITH_IMSI:
        case MMC_LMM_CS_PS_PERIODIC_UPDATING:

            /* ����lmm������tau��� */
            NAS_MMC_ProcLmmCombinedTauResultInd_OnPlmn(pstLmmTauIndMsg);
            break;

        case MMC_LMM_TA_UPDATING:
        case MMC_LMM_PS_PERIODIC_UPDATING:

            /* ����lmm�ķ�����tau��EPS onlyע��Ľ�� */
            NAS_MMC_ProcLmmEpsOnlyTauResultInd_OnPlmn(pstLmmTauIndMsg);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmTauResultInd_OnPlmn:Unexpected tau req type!");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedAttachInd_OnPlmn
 ��������  : Lmm combined attach����Ĵ�����
 �������  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��8��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV ����
  3.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  4.��    ��   : 2011��12��13��
    ��    ��   : z00161729
    �޸�����   : DTS2011121302231:attach����#9/#10��Э��Ӧ�ð�other cause����
  5.��    ��   : 2011��12��20��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:����ע��ɹ���Ҫ����NAS_MMC_SetUserSpecPlmnRegisterStatusΪVOS_TRUE
  6.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
                  additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  7.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : GUL_BG��Ŀ����
  8.��    ��   : 2012��06��01��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  9.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
  10.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�DTS2012090401249
 11.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 12.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
 *****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_OnPlmn(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));


    enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause(pstLmmAttachIndMsg,&enPsRegRsltCause, &enCsRegRsltCause);

    switch (pstLmmAttachIndMsg->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc(pstLmmAttachIndMsg,
                       enCsRegRsltCause, &enCsAdditionalAction, &enPsAdditionalAction);

            break;

        case MMC_LMM_ATT_RSLT_FAILURE:
            if (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt)
            {
                enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
                enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

                /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
                NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
                /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

                /* LNAS��������ע�᳢������-��������ȴ��� */
                NAS_MMC_SetCLRegAdditionalAction_L1Main(NAS_MMC_CL_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT);
            }
            else
            {
                /* EPS/CS ��ע��ʧ�� */
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND,
                                                     pstLmmAttachIndMsg,
                                                     &enPsAdditionalAction,
                                                     &enCsAdditionalAction);
            }
            break;

        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_T3402_RUNNING:
        case MMC_LMM_ATT_RSLT_TIMER_EXP:
        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_ATT_RSLT_AUTH_REJ:
        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
            /* EPS/CS ��ע��ʧ�� */
            NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND,
                                                pstLmmAttachIndMsg,
                                                &enPsAdditionalAction,
                                                &enCsAdditionalAction);
            break;

        case MMC_LMM_ATT_RSLT_CN_REJ:
            if ((VOS_TRUE == pstLmmAttachIndMsg->bitOpCnRslt)
             && (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == pstLmmAttachIndMsg->ulCnRslt))
            {
                /* ��ATTACH��������Ϊ���ϣ�������Ӧ��ATTACH�������ΪEPS ONLY��
                   ��ԭ��ֵ��ΪЭ��24301 5.5.1.3.4.3�½����л���û��Я��ԭ��ֵ��
                   ��LMMͨ��ATTACH�����MMC_LMM_ATT_RSLT_CN_REJ֪ͨMMC��
                   ��Я����Ӧ��ATTACH�������͡�������Ӧ��ATTCH������͡�ԭ��ֵ��
                   ��Я�������ԭ����attach attempt counterֵ */
                NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(pstLmmAttachIndMsg,enCsRegRsltCause,
                                  &enCsAdditionalAction, &enPsAdditionalAction);
            }
            else
            {
                /* EPS/CS ��ע��ʧ�� */
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND,
                                                     pstLmmAttachIndMsg,
                                                     &enPsAdditionalAction,
                                                     &enCsAdditionalAction);

            }
            break;

        default:
            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_OnPlmn:Unexpected attach result!");
            enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();
            enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
            break;
    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enPsAdditionalAction);
    }

    /* AdditionalAction��Ч������CS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }


    /* ����PS��ע�᳢�Դ��� */
    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpAtmpCnt)
    {
        NAS_MMC_SetPsRegAttemptCount_L1Main(pstLmmAttachIndMsg->ulAttemptCount);
    }

    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);
    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedTauResultInd_OnPlmn
 ��������  : Lmm ����TAU����Ĵ�����
 �������  : pstLmmTauIndMsg L��TAU��Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��8��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV ����
  3.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  4.��    ��   : 2011��12��13��
    ��    ��   : z00161729
    �޸�����   : DTS2011121302231:attach����#9/#10��Э��Ӧ�ð�other cause����
  5.��    ��   : 2011��12��20��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:����ע��ɹ���Ҫ����NAS_MMC_SetUserSpecPlmnRegisterStatusΪVOS_TRUE
  6.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
                  additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  7.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : GUL_BG��Ŀ����
  8.��    ��   : 2012��06��01��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  9.��    ��   : 2012��6��7��
    ��    ��   : z00161729
    �޸�����   : GUL_BG��Ŀ������Ȧ���Ӷ�
 10.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
  11.��    ��   : 2012��8��21��
     ��    ��   : z00161729
     �޸�����   : DCM������������������޸�DTS2012090401249
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_OnPlmn(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(pstLmmTauIndMsg, &enPsRegRsltCause, &enCsRegRsltCause);

    NAS_MMC_ProcLmmCombinedTauResult(pstLmmTauIndMsg, enCsRegRsltCause,
                                    &enPsAdditionalAction, &enCsAdditionalAction);

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_L1Main(enPsAdditionalAction);
    }

    /* AdditionalAction��Ч������CS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_L1Main(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }


    /* ����PS��ע�᳢�Դ��� */
    if (VOS_TRUE == pstLmmTauIndMsg->bitOpAtmpCnt)
    {
        NAS_MMC_SetPsRegAttemptCount_L1Main(pstLmmTauIndMsg->ulAttemptCount);
    }

    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);
    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCoverageLost_L1Main
 ��������  : ������������Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��08��09��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ
 3.��    ��   : 2012��04��07��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2012040106098,����CoverageLost��service���ϱ�˳���Ը���MMA��״̬��DeepSleep
 4.��    ��   : 2012��4��9��
   ��    ��   : l00130025
   �޸�����   : DTS2012033006643,����������Syscfg��������ʧ��ʱ���ϱ�RSSIΪ��Ч
 5.��    ��   : 2012��3��31��
   ��    ��   : z40661
   �޸�����   : V7R1֧�������͹���
 6.��    ��   : 2012��9��14��
   ��    ��   : t00212959
   �޸�����   : DTS2012082808241,����OOC״̬��Ӧ�ý�פ����־������б��ѳɹ���������0������ʱ��available��ʱ������������
 7.��    ��   : 2012��11��7��
   ��    ��   : l00167671
   �޸�����   : DTS2012110607212: availble��ʱ����ʱ�������ɹ�,���ܽ��ж�ʱ������
 8.��    ��   : 2012��11��21��
   ��    ��   : z00161729
   �޸�����   : ֧��cerssi��nmr
9.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
10.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
11.��    ��   : 2013��4��4��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:����NO RF ��ر�������
12.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
13.��    ��   : 2014��6��4��
   ��    ��   : b00269685
   �޸�����   : NAS_MMC_SndMsccRssiInd()�޸�
14.��    ��   : 2014��7��3��
   ��    ��   : z00161729
   �޸�����   : DSDS III����
15.��    ��   : 2015��5��25��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
16.��    ��   : 2015��9��10��
   ��    ��   : c00318887
   �޸�����   : Ԥ��Ƶ�������Ż��޸�
17.��    ��   : 2015��11��14��
   ��    ��   : l00289540
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
*****************************************************************************/
/* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
VOS_VOID    NAS_MMC_ProcCoverageLost_L1Main(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32          ulPlmnSearchScene
)
/* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCellInfo = VOS_NULL_PTR;


    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN   unMeasReportType;

    pstCampCellInfo         = NAS_MML_GetCampCellInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    enRatType = NAS_MML_GetCurrNetRatType();

    PS_MEM_SET(((VOS_UINT8*)&unMeasReportType), 0, sizeof(MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN));
    unMeasReportType.ucMeasReportType |= NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV;

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                 NAS_MML_GetSimPsRegStatus());

    }

    if (((NAS_MML_NET_RAT_TYPE_GSM == enRatType)
      && (NAS_MML_RSSI_UNVALID != pstCampCellInfo->astRssiInfo[0].sRssiValue))
     || ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
      && (NAS_MML_UTRA_RSCP_UNVALID != pstCampCellInfo->astRssiInfo[0].sRscpValue)))
    {
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
        NAS_MMC_SndMsccRssiInd(&unMeasReportType);
    }

    /* �Ѿ�������ӦΪ��פ��̬�������б���û�д�����������Ķ�����available��ʱ�����CCO״̬�����б�������*/
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */


    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */
    /* ֪ͨMM ��������ʧ */
    NAS_MMC_SndMmCoverageLostInd();

    /* ֪ͨGMM ��������ʧ */
    NAS_MMC_SndGmmCoverageLostInd();

    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH != ulPlmnSearchScene)
    {
        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
        /* �ϱ���Ӧ��CS/PS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
        NAS_MMC_UpdateRegStateSpecPlmnSearch();
        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */
    }
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_EnterOocStatus_OnPlmn();

    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_OOC);



    /* ����NO RFʧ��ʱ������������������ʱ������������COUNTER */
    if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()))
    {
        NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

        if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
        {
            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */
        }
    }


}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcOutOfService_L1Main
 ��������  : ���������縲�ǵĴ���
 �������  : ulCampFlg:��ǰ�Ƿ�פ�� VOS_TRUE  - פ��
                                    VOS_FALSE - ��פ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��08��09��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��10��
   ��    ��   : L00171473
   �޸�����   : DTS2012082204471, TQE����
 3.��    ��   : 2012��07��14��
   ��    ��   : l65478
   �޸�����   : DTS2012071303294�����ӽ���ʧ��ʱû�����CS���ӱ�־

  4.��    ��   : 2012��9��25��
    ��    ��   : z40661
    �޸�����   : DTS2012082006273
 5.��    ��   : 2012��11��7��
   ��    ��   : l00167671
   �޸�����   : DTS2012110607212: availble��ʱ����ʱ�������ɹ�,���ܽ��ж�ʱ������
 6.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 7.��    ��   : 2013��4��4��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:����NO RF ��ر�������

 8.��    ��   : 2015��1��23��
   ��    ��   : w00167002
   �޸�����   : CL_ACCESSBAR_STUB:via����L������ע��ʱ��L��ACCESS BAR������
                ѡ��������L�Լ�������ע�ᡣVIA�޷���ϣ�MODEM��������޸ġ�
                �޸�Ϊ��ע��״̬�յ�ACCESS BAR�󣬼����ȴ�L��ע������

*****************************************************************************/
VOS_VOID    NAS_MMC_ProcOutOfService_L1Main(
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstPlmnSelectionRslt
)
{
    VOS_UINT32                          ulPlmnLaType;
    NAS_MML_PLMN_RAT_PRIO_STRU          stAnycellSrchRatList;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulRecampFlg;
#endif

    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8  enCampOnFlg;

    VOS_UINT8                           ucRfAvailFlg;

    NAS_MMC_REG_CONTROL_ENUM_UINT8      enRegCtrl;

    enRegCtrl  = NAS_MMC_GetRegCtrl();

    ucRfAvailFlg    = NAS_MML_GetRfAvailFlg();

    enCampOnFlg  = NAS_MMC_GetAsCellCampOn();

    PS_MEM_SET(&stAnycellSrchRatList, 0x00, sizeof(stAnycellSrchRatList));


    /* ��ȡ��ǰ��LA�Ƿ��ڽ�ֹ�б��� */
    ulPlmnLaType = NAS_MMC_GetCurrentLaiForbbidenType();

    /* ��ǰ����Ч,��Ϊפ��״̬���Ҳ��ڽ�ֹ������Ϣ�� */
#if (FEATURE_ON == FEATURE_LTE)
    ulRecampFlg = VOS_FALSE;
    ulRecampFlg = NAS_MMC_IsReCampLteLimitedService();
#endif

    if ( (VOS_TRUE == NAS_MML_IsUsimStausValid())
       &&(NAS_MML_PLMN_FORBID_NULL  == ulPlmnLaType)
       &&(VOS_TRUE                  == pstPlmnSelectionRslt->ulCampFlg)
       &&(NAS_MMC_AS_CELL_CAMP_ON   == enCampOnFlg)
       &&(NAS_MMC_REG_CONTROL_BY_3GPP2_CBP != enRegCtrl))
    {
#if   (FEATURE_ON == FEATURE_LTE)
        /* ��Ҫdisalbe lte,ͬʱ��פ����LTE���� */
        if ( (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus())
          && ( VOS_FALSE == ulRecampFlg ))
        {
            /* ����������� ����ANYCELL������RAT�������� */
            NAS_MMC_BuildCoverageRatPrioList_L1Main(pstPlmnSelectionRslt, &stAnycellSrchRatList);

            /* ���ݽ���еĽ��뼼��������Ϣ����anycell״̬��������������ǰ���뼼�� */
            NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        }
        else
#endif
        {
            /* �������Ч����Available��ʱ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);



            /* ����ʧ��ΪNO RF��������COUNTER,��ֹ���������ٶȼ��� */
            if ( (VOS_TRUE  == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()))
               && (VOS_TRUE == ucRfAvailFlg) )
            {
                /* ���� availble timer��ǰ�����Ĵ�����ncell�������� */
                NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
                (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
                /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */

            }
        }
    }
    else
    {
        /* ����������� ����ANYCELL������RAT�������� */
        NAS_MMC_BuildCoverageRatPrioList_L1Main(pstPlmnSelectionRslt, &stAnycellSrchRatList);

        /* ���ݽ���еĽ��뼼��������Ϣ����anycell״̬��������������ǰ���뼼�� */
        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPlmnListTriggerPlmnSearch_L1Main
 ��������  : L1״̬�����յ�LIST����״̬�����,������Ҫ����ʱ�Ĵ���
 �������  : pstListRslt:List����״̬�����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
              VOS_FALSE:����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��13��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
  3.��    ��   : 2012��8��21��
    ��    ��   : w00176964
    �޸�����   : DTS2012111404729:����פ����ACC BARС���������û�LIST����
                 ֻ�ѵ���ǰ�����,�������������ڲ�LIST����
  4.��    ��   : 2012��12��07��
    ��    ��   : w00176964
    �޸�����   : DTS2012120401487:L��detach CS/PS���û�LIST��������Ӧ�ò�����
  5.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2014��5��31��
    ��    ��   : y00245242
    �޸�����   : �޸ķ���״̬�ϱ�
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcPlmnListTriggerPlmnSearch_L1Main(
    NAS_MMCMMC_PLMN_LIST_RSLT_STRU     *pstListRslt
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    /* Modified by z00161729 for DCM�����������������, 2012-8-22, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    /* Modified by z00161729 for DCM�����������������, 2012-8-22, end */

    /* �ж��Ƿ���Ҫ��������,����Ҫ��ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MMC_IsPlmnListTriggerPlmnSrch_L1Main(pstListRslt))
    {
        return VOS_FALSE;
    }

    /* �յ�����ָʾ��Ǩ��״̬NAS_MMC_L1_STA_INITIAL */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

   /* L��idle̬detach,�յ�L detach cnf������disable���������Ʒ�����Ϣ�����û�list����,
      L��list�����ɹ��˳���Ҫ����,���û�list������������,��Ҫ��ջ����������־ */
    NAS_MMC_SetBufferedPlmnSearchInfo(VOS_FALSE, NAS_MMC_PLMN_SEARCH_SCENE_BUTT);

#if (FEATURE_ON == FEATURE_LTE)
    /* ���disable LTE��LIST�����ص�L�£���ʱ����������Ҫ�������� */
    if (NAS_MMC_PLMN_LIST_SEARCH_SCENE_DISABLE_LTE == pstListRslt->enPlmnListSearchScene)
    {
        /* ����������Ϣ */
        enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE;
    }
    else
#endif
    {
        /* �����û��б�������Ϣ */
        enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST;
    }

    /* Modified by z00161729 for DCM�����������������, 2012-8-22, begin */
    if (VOS_FALSE == NAS_MMC_IsNeedAnycell_OnPlmn())
    {
        /* ��פ��ʱ����Ϊ�޷���״̬���ϱ� */
        if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
        {
            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */
        }

        /* ���첢�����ڲ�������Ϣ */
        NAS_MMC_SndInterPlmnSearchReq(enPlmnSearchScene, &(pstListRslt->astPlmnSearchInfo[0]), NAS_MML_MAX_RAT_NUM);
        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_IsExistBufferedEmgCall())
    {
        /* ����Ϊ���Ʒ���״̬���ϱ� */
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */

        /* ע�ᱻ�ܵ��¿���Ч����Anycell���� */
        NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }
    else
    {
        /* ���ڽ������д���ANYCELL����,������Ҫanycell�ѵĽ��뼼��ΪGU,����˳����syscfg���� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }
    /* Modified by z00161729 for DCM�����������������, 2012-8-22, end */

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcTiAvailableTimerExpiredTriggerPlmnSearch_L1Main
 ��������  : available��ʱ����ʱ֮����Ҫ�����Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiAvailableTimerExpiredTriggerPlmnSearch_L1Main(VOS_VOID)
{
    NAS_MML_PLMN_ID_STRU                                   *pstCampPlmnId    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstOtherPlmnId   = VOS_NULL_PTR;

    VOS_UINT8                                               ucRrcLteNcellExistFlg;
    VOS_UINT8                                               ucRrcUtranNcellExistFlg;
    VOS_UINT8                                               ucIsCampSamePlmn;
    VOS_UINT8                                               ucSvlteSupportFlg;
    VOS_UINT8                                               ucLcEnableFlg;
    NAS_MMC_OOS_PHASE_ENUM_UINT8                            enOosPhaseNum;


    pstOtherPlmnId              = NAS_MMC_GetOtherModemPlmnId();
    pstCampPlmnId               = NAS_MML_GetCurrCampPlmnId();
    ucRrcLteNcellExistFlg       = NAS_MML_GetRrcLteNcellExistFlg();
    ucRrcUtranNcellExistFlg     = NAS_MML_GetRrcUtranNcellExistFlg();
    ucSvlteSupportFlg           = NAS_MML_GetSvlteSupportFlag();
    ucLcEnableFlg               = NAS_MML_GetLcEnableFlg();

    ucIsCampSamePlmn            = VOS_FALSE;


    if ( ( pstOtherPlmnId->ulMcc == pstCampPlmnId->ulMcc)
      && ( pstOtherPlmnId->ulMnc == pstCampPlmnId->ulMnc)  )
    {
        ucIsCampSamePlmn = VOS_TRUE;
    }
    /* ��ά�ɲ� */
    NAS_MMC_LogOosPlmnSearchStrategyRelatedInfo();
    NAS_MMC_LogFsmL1MainCtxRelatedInfo(NAS_MMC_GetL1MainCtx_L1Main());

    /* available��ʱ����ʱ����history�ѵĴ��� */
    if (VOS_TRUE == NAS_MMC_ProcTiAvailableTimerExpired_HistorySearch_L1Main())
    {
        return VOS_TRUE;
    }

    /* available��ʱ����ʱ����Pref-Band�ѵĴ��� */
    if (VOS_TRUE == NAS_MMC_ProcTiAvailableTimerExpired_PrefBandSearch_L1Main())
    {
        return VOS_TRUE;
    }

    /* available��ʱ����ʱ����ncell�ѵĴ��� */
    if (VOS_TRUE == NAS_MMC_ProcTiAvailableTimerExpired_NcellSearch_L1Main())
    {
        return VOS_TRUE;
    }
    enOosPhaseNum               = NAS_MMC_GetOosPhaseNum();

    /* SVLTE��C+L��̬ʱ������ģʽ(PS Only)��Ҫ����Avaliable��ʱ�� */
    if ( (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
      && ( (VOS_TRUE == ucSvlteSupportFlg)
        || (VOS_TRUE == ucLcEnableFlg) )
      && (NAS_MMC_OOS_PHASE_ONE == enOosPhaseNum)
      && (VOS_TRUE == ucIsCampSamePlmn )
      && ((VOS_TRUE == ucRrcLteNcellExistFlg)
       || (VOS_TRUE == ucRrcUtranNcellExistFlg)) )
    {
        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */
        }
        return VOS_FALSE;
    }


    /* available��ʱ����ʱ������ͨ�б��ѻ���ָͨ���ѵĴ��� */
    if (VOS_TRUE == NAS_MMC_ProcTiAvailableTimerExpired_NormalSearch_L1Main())
    {
        return VOS_TRUE;
    }

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcTiAvailableTimerExpired_HistorySearch_L1Main
 ��������  : available��ʱ����ʱ����history�ѵĴ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiAvailableTimerExpired_HistorySearch_L1Main(VOS_VOID)
{


    /* Modified by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, begin */

    /* ��Ҫhistory�� */
    if (VOS_FALSE == NAS_MMC_IsNeedHistorySearch_L1Main())
    {
        NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());

        /* ����Ҫhistory�ѵ�ʱ�򣬼�������������Ҫncell�ѻ���ͨ���������� */
        NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn();

        return VOS_FALSE;
    }

    NAS_MMC_AddCurHistorySearchTimerCount_OnPlmn();

    NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());

    if(VOS_TRUE == NAS_MMC_IsNeedGoToNextPhaseByHistory())
    {
        NAS_MMC_AddOosPhaseNum();
        NAS_MMC_ResetCurHistorySearchTimerCount_OnPlmn();
    }

    /* ��������һ�׶��ܿض�ʱ��ʱ��normal availuable ��ʱ����������ʱ���ԭ������Ϊ��ֹ���ܼ�ʱ��Ӧ��
       normal availuable��historyʱ����������ʱִ��LIST �� */

    if (VOS_TRUE == NAS_MMC_IsAvailTimerExpiredTriggerInterPlmnList_L1Main())
    {
        /* �����ǰ��һ�׶��ܿض�ʱ���������У����ڵڶ��׶�������Ϊ���͹��ģ����÷�LIST����������������ʱ�� */
        if (NAS_MMC_OOS_PHASE_ONE != NAS_MMC_GetCurrOosSearchPhaseNum())
        {
            if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextSearchSleepTimerLen()))
            {
                NAS_MMC_SetAvailableTimerType_OnPlmn(NAS_MMC_AVAILABLE_TIMER_TYPE_HISTORY);
            }

            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcTiAvailableTimerExpired_HistorySearch_L1Main: PHASE ONE TIMER IS NOT RUN,GO ON HISTORY TIMER.");

            return VOS_TRUE;
        }

        NAS_MMC_SndInterPlmnListReq();

        /* ��������������additional��ֵ */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* ����������ͬʱ���CS/PS��ע�᳢�Դ��� */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();
    }
    else
    {
        NAS_MMC_RcvTiAvailTimerExpired_HistorySearch_OnPlmn();
    }

    return VOS_TRUE;

    /* Modified by w00167002 for Ԥ��Ƶ�������Ż���Ŀ, 2015-9-15, end */

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcTiAvailableTimerExpired_PrefBandSearch_L1Main
 ��������  : available��ʱ����ʱ����PrefBand�ѵĴ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��9��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiAvailableTimerExpired_PrefBandSearch_L1Main(VOS_VOID)
{


    /* ��ҪPrefBand�� */
    if (VOS_FALSE == NAS_MMC_IsNeedPrefBandSearch_L1Main())
    {
        NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());

        /* ����ҪPrefBand�ѵ�ʱ�򣬼�������������Ҫncell�ѻ���ͨ���������� */
        NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn();

        return VOS_FALSE;
    }

    NAS_MMC_AddCurPrefBandSearchTimerCount_OnPlmn();

    NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());

    if(VOS_TRUE == NAS_MMC_IsNeedGoToNextPhaseByPrefBand())
    {
        NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());
        NAS_MMC_AddOosPhaseNum();
        NAS_MMC_ResetCurPrefBandSearchTimerCount_OnPlmn();
    }

    NAS_MMC_RcvTiAvailTimerExpired_PrefBandSearch_OnPlmn();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcTiAvailableTimerExpired_NcellSearch_L1Main
 ��������  : available��ʱ����ʱ����ncell�ѵĴ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiAvailableTimerExpired_NcellSearch_L1Main(VOS_VOID)
{
    /* ����ncell����������ֱ�ӽ���ncell�������� */
    if (VOS_TRUE == NAS_MMC_IsNeedNcellSearch())
    {
        /*
           ��������:
           ��Ncell���Դ�ʱ,
           ��Ҫ��� OOS�е����� "FullBandNum >= 1, PrefBandNum = 0, HistoryNum = 0"
        */
        NAS_MMC_AddCurNcellSearchTimerCount_OnPlmn();
        /* ����NCELL�� */
        NAS_MMC_RcvTiAvailTimerExpired_NcellSearch_OnPlmn();

        return VOS_TRUE;
    }


    /* ����Ҫncell�ѵ�ʱ�򣬼�������������Ҫ��ͨ���������� */
    NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn();

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcTiAvailableTimerExpired_NormalSearch_L1Main
 ��������  : available��ʱ����ʱ������ͨ�б��ѻ���ָͨ���ѵĴ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcTiAvailableTimerExpired_NormalSearch_L1Main(VOS_VOID)
{


    NAS_MMC_AddCurNormalAvailableTimerCount_L1Main();

    NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());

    if(VOS_TRUE == NAS_MMC_IsNeedGoToNextPhaseByFullBand())
    {
        NAS_MMC_SetCurrOosSearchPhaseNum(NAS_MMC_GetOosPhaseNum());
        NAS_MMC_AddOosPhaseNum();
        NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main();
    }

    /* �ж�available timer��ʱ�Ƿ񴥷��ڲ��б����� */
    if (VOS_TRUE == NAS_MMC_IsAvailTimerExpiredTriggerInterPlmnList_L1Main())
    {
        NAS_MMC_SndInterPlmnListReq();

        /* ��������������additional��ֵ */
        NAS_MMC_ClearAllRegAdditionalAction_L1Main();

        /* ����������ͬʱ���CS/PS��ע�᳢�Դ��� */
        NAS_MMC_ClearAllRegAttemptCount_L1Main();

        return VOS_TRUE;
    }

    /* ��ʱ����ʱ������Ϊ initail ״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* ����������Ϣ */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED,VOS_NULL_PTR, 0);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetRegRsltAdditionalAction_L1Main
 ��������  : ����������ע����������CS��PS��AdditionalAction
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��27��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��1��13��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:���յ�ע����ʱ����CS/PS���AdditionalAction
                 ֵ�ֱ��װ���л�ȡ�������Ժ���չ�Ϳɶ��ԡ�
*****************************************************************************/
VOS_VOID NAS_MMC_SetRegRsltAdditionalAction_L1Main( VOS_VOID )
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                        enPsAdditionalAction;

    /* ��״̬���˵�L1 MAINʱ��ȡ��CS/PS��additionֵ */
    enCsAdditionalAction = NAS_MMC_GenerateRegRsltCsDomainAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GenerateRegRsltPsDomainAdditionalAction_L1Main();

    /* ����CS/PS��additionֵ */
    NAS_MMC_SetCsRegAdditionalAction_L1Main(enCsAdditionalAction);
    NAS_MMC_SetPsRegAdditionalAction_L1Main(enPsAdditionalAction);


}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvForbLaTimerExpired_OnPlmn
 ��������  : ����TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�����������
             VOS_FALSE:��������δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��9��13��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����LIST����״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_OnPlmn
 ��������  : ����TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�����������
             VOS_FALSE:��������δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��9��13��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����LIST����״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_LIST);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvBgPlmnSearchRsltCnfFail_OnPlmn
 ��������  : ����MMCMMC_BG_PLMN_SEARCH_RSLT_CNF��Ϣ��BG�������Ϊ
             NAS_MMC_BG_PLMN_SEARCH_FAIL�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:     MMCMMC_BG_PLMN_SEARCH_RSLT_CNF��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��04��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��21��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 4.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����

 5.��    ��   : 2014��5��4��
   ��    ��   : t00173447
   �޸�����   : DTS2014042105390,������������
 6.��    ��   : 2014��4��29��
   ��    ��   : s00261364
   �޸�����   : ecall��Ŀ�޸ķ���״̬�ϱ�
*****************************************************************************/
VOS_VOID  NAS_MMC_RcvBgPlmnSearchRsltCnfFail_OnPlmn(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32    enBgPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pstIntraPlmnSrchInfo
)
{
    VOS_UINT32                                              ulCsServiceExist;
    VOS_UINT32                                              ulPsServiceExist;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    /* Modified by z00161729 for DCM�����������������, 2012-8-22, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulEmgCallFlg;

    pstPrioRatList   = NAS_MML_GetMsPrioRatList();
    ulCsServiceExist = NAS_MML_GetCsServiceExistFlg();
    ulPsServiceExist = NAS_MML_GetPsServiceExistFlg();
    ulEmgCallFlg     = NAS_MML_GetCsEmergencyServiceFlg();

    /* �����ǰ����ҵ�����ӣ�����AVAILABLE������ʱ��,����������Ҫ����anycell�� */
    if (((VOS_TRUE == ulCsServiceExist)
      && (VOS_FALSE == ulEmgCallFlg))
     || (VOS_TRUE == ulPsServiceExist))
    {
        if ( VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue()) )
        {
            /* ���� availble timer��ǰ�����Ĵ�����ncell�������� */
            NAS_MMC_SetAvailableTimerTypebySearchType_OnPlmn();

            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, begin */
            (VOS_VOID)NAS_MMC_StartPlmnSearchPhaseOneTotalTimer();
            /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-1, end */
        }

        return;
    }

    /* Modified by z00161729 for DCM�����������������, 2012-8-22, end */

    /* Ǩ�Ƶ�Intial״̬  */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* ����BG����״̬����������������ת��Ϊ�ڲ�������Ϣ�е��������� */
    if ( NAS_MMC_BG_PLMN_SEARCH_SCENE_AREA_LOST ==  enBgPlmnSearchScene)
    {
        if(VOS_TRUE == NAS_MMC_IsInterNationalRoamingSearchRPLMN(NAS_MMC_GetLastCampedPlmnid()->ulMcc))
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG;
        }
        else
        {
            enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST;
        }
    }
    else
    {
        enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE;
    }

    /* Modified by z00161729 for DCM�����������������, 2012-8-22, begin */
    if (VOS_FALSE == NAS_MMC_IsNeedAnycell_OnPlmn())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_HIGH_PRO_PLMN_SRCH_BACK_TO_ORIG_PLMN_FAIL);

        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */

        /* ���첢�����ڲ�������Ϣ:����ͬ���� */
        NAS_MMC_SndInterPlmnSearchReq(enPlmnSearchScene, pstIntraPlmnSrchInfo, 1);
        return;
    }

    if (VOS_FALSE == NAS_MML_IsExistBufferedEmgCall())
    {
        /* ����Ϊ�޷���״̬���ϱ� */
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */

        /* ע�ᱻ�ܵ��¿���Ч����Anycell���� */
        NAS_MMC_SndInterAnyCellSearchReq(VOS_NULL_PTR, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }
    else
    {
        /* ���ڽ������д���ANYCELL����,������Ҫanycell�ѵĽ��뼼��ΪGU,����˳����syscfg���� */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
    }
    /* Modified by z00161729 for DCM�����������������, 2012-8-22, end */

    return;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvBgPlmnSearchRsltCnf_OnPlmn
 ��������  : ����MMCMMC_BG_PLMN_SEARCH_RSLT_CNF��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:     MMCMMC_BG_PLMN_SEARCH_RSLT_CNF��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�����������
             VOS_FALSE:��������δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��9��18��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��22��
   ��    ��   : w00167002
   �޸�����   : V7R1 Phase II-2 ����HPLMN TIMER���¼��ϱ�

 3.��    ��   : 2011��12��3��
   ��    ��   : w00167002
   �޸�����   : DTS2011120300667:�ڱ�����ʱ�������н�����ҵ��ͬʱע����
                ��Ҫ�����������ڵ������ͷų�ʱʱ����Ҫ����AVAILABLE ��ʱ����
                �ȴ˶�ʱ����ʱ�󣬷���������
 4.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
 5.��    ��   : 2011��12��20��
   ��    ��   : h44270
   �޸�����   : �˳�BG����״̬��ʱ��֪ͨAPS��ǰ��������
 6.��    ��   : 2012��5��8��
   ��    ��   : z00161729
   �޸�����   : GUL BG��������:����disable LTE����
 7.��    ��   : 2012��5��25��
   ��    ��   : w00176964
   �޸�����   : GUL BG��������:BG�����˳�ʱ����L1��additionalֵ
 8.��    ��   : 2012��6��11��
   ��    ��   : l60609
   �޸�����   : AT&T&DCM��BG��δ��ɺ�ʱ����0��������10s�����Գ��Զ�ʱ��

 9.��    ��   : 2012��9��3��
   ��    ��   : z40661
   �޸�����   : DTS2012081801644,SIM����HPLMN����Ϊ0ʱ,�����������������Դ�ʱδ���������Զ�ʱ��
 10.��    ��   : 2012��8��29��
    ��    ��   : w00176964
    �޸�����   : ��UTRANģʽΪFDDʱ��ʱ����0����֧��ActingHplmn��������10s�����Գ��Զ�ʱ��
 11.��    ��   : 2013��1��17��
    ��    ��   : s00217060
    �޸�����   : for DSDA GUNAS C CORE:ֻ����UtranModeΪTDDʱ���Ų���HPLMN��ʱ��
 12.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 13.��    ��   : 2013��12��20��
    ��    ��   : w00167002
    �޸�����   : DTS2013112917981:guNASɾ����TDģʽ�²��ܽ���bg�ѵ�����
                  �����һ�TL������Ӧ������������һء�
 14.��    ��   : 2014��2��24��
    ��    ��   : w00176964
    �޸�����   : High_Rat_Hplmn_Search���Ե���:����High_Prio_rat_hplmn��ʱ������������
 15.��    ��   : 2013��4��4��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ������ʱ����Ǩ�Ƶ�ooc
 16.��    ��   : 2014��3��21��
   ��    ��   : z00161729
   �޸�����   : DTS2014032105704:����TDS����˲���һ�ԭС��psǨ��modem1���ٻ�Ǩmodem0
 17.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
 18.��    ��   : 2014��10��25��
    ��    ��   : b00269685
    �޸�����   : ����high rat TD count�Ĵ���
 19.��    ��   : 2015��5��30��
    ��    ��   : l00324781
    �޸�����   : CDMA 1X Iteration 12: lte��BG��hrpd���ɹ���ue��Ҫפ����hrpd��lte���ڴ�ģ��
                                        mmc״̬��Ϊhrpd
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvBgPlmnSearchRsltCnf_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU                    *pstBgPlmnSearchRsltCnfMsg = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchList = VOS_NULL_PTR;

    VOS_UINT8                                               ucCsAttachAllowFlag;
    VOS_UINT8                                               ucPsAttachAllowFlag;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enAvailableTimerStatus;


    VOS_UINT32                                              ulSpecPlmnSearchFlg;

    /* ��ǰ������������״̬��δ���й���������������Ϣ������������ */
    ulSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();


    /* ת��ΪBG�ѽ����Ϣ */
    pstBgPlmnSearchRsltCnfMsg = (NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU *)pstMsg;

    /* ��ȡ�����ȼ������б���Ϣ */
    pstHighPrioPlmnSearchList = NAS_MMC_GetHighPrioPlmnList();

    /* ��ά�ɲ�,��ѡ���б���� */
    NAS_MMC_LogPlmnSelectionList(pstHighPrioPlmnSearchList);

    /* �����ǰ����NO RF����Ǩ�Ƶ�OOC״̬ */
    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ������״̬���ϱ�����״̬��Ǩ�Ƶ�ooc������available��ʱ�� */
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, begin */
        NAS_MMC_ProcCoverageLost_L1Main(NAS_MMC_PLMN_SEARCH_SCENE_BUTT);
        /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-10, end */

        return VOS_TRUE;
    }
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    if (NAS_MMC_BG_PLMN_SEARCH_INTER_SYS_HRPD == pstBgPlmnSearchRsltCnfMsg->enRslt)
    {
        NAS_MMC_StopAllTimer();

        /* NAS_MMC_L1_STA_OOC-->NAS_MMC_L1_STA_DEACT, BG�ѳɹ���UE��פ����hRPD�ϣ�
            ��ʱlte���ڴ�ģ��mmc״̬Ǩ��DEACT
        */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_DEACT);

        OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMC));
        NAS_MMC_SndDrxTimerInfo(VOS_TRUE);

        return VOS_TRUE;
    }
#endif
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */
    NAS_MMC_StartHighPrioPlmnSearchTimer_BgSearch_OnPlmn(pstBgPlmnSearchRsltCnfMsg);

    if (VOS_TRUE == NAS_MMC_IsCampOnHighestPrioRatHplmn())
    {
        NAS_MMC_InitTdHighRatSearchCount();
    }

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    /* ���״̬���˳����Ϊ NAS_MMC_BG_PLMN_SEARCH_SUCC��
       ����û����һ�������������ȼ�������פ���ڸ����ȼ������vplmn�ϵ�������������� */
    if (NAS_MMC_BG_PLMN_SEARCH_SUCC == pstBgPlmnSearchRsltCnfMsg->enRslt)
    {
        /* ����AdditionalAction��ֵ */
        NAS_MMC_SetRegRsltAdditionalAction_L1Main();

        ucCsAttachAllowFlag    = NAS_MML_GetCsAttachAllowFlg();
        ucPsAttachAllowFlag    = NAS_MML_GetPsAttachAllowFlg();
        enAvailableTimerStatus = NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER);

        if((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
        && (VOS_FALSE == ucCsAttachAllowFlag)
        && (VOS_FALSE == ucPsAttachAllowFlag)
        && (NAS_MMC_TIMER_STATUS_RUNING != enAvailableTimerStatus))
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, NAS_MMC_GetNextAvailableTimerValue());
        }

        return VOS_TRUE;
    }

    /* ���״̬���˳����ΪNAS_MMC_BG_PLMN_SEARCH_ABORTED,
       �������ⲿ��Ϣ��ϣ�����������������vplmnʧ�ܺͳɹ� */
    if (NAS_MMC_BG_PLMN_SEARCH_ABORTED == pstBgPlmnSearchRsltCnfMsg->enRslt)
    {
        /* ���ⲿ����˳�״̬�������ʼ�������ȼ��б� */
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                      VOS_NULL_PTR,
                                      pstHighPrioPlmnSearchList);

        /* ��ǰMMC������״̬,���MMC�ķ���״̬Ϊ��������,�ȸ����·���״̬ */
        if ((VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
         && (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == ulSpecPlmnSearchFlg))
        {
            /* ����Ϊ�޷���״̬���ϱ� */
            NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
            NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);
            NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE);
        }

        /* abort�˳��п�����Ҫ����,����AdditionalAction��ֵ */
        NAS_MMC_SetRegRsltAdditionalAction_L1Main();

        return VOS_TRUE;
    }

    /* ��״̬���˳����ΪNAS_MMC_BG_PLMN_SEARCH_FAIL�������¼������:
       1������һ�������ȼ������һ�VPLMNʧ�ܣ� 2��ע�ᱻ�ܵ��¿���Ч��
       3���������abort���������abort�����ʼ�������ȼ��б�4���ȴ�ϵͳ��Ϣ��ʱ��
       5���ȴ�����������ظ��͵ȴ�ֹͣ�����ظ�״̬�յ�W��RRMM_REL_IND_STRU����ԭ��ֵΪRRC_REL_CAUSE_OTHER_REASON */
    if ((NAS_MMC_BG_PLMN_SEARCH_FAIL == pstBgPlmnSearchRsltCnfMsg->enRslt)
     && (VOS_TRUE == pstBgPlmnSearchRsltCnfMsg->ulNeedPlmnSearch))
    {
        NAS_MMC_RcvBgPlmnSearchRsltCnfFail_OnPlmn(pstBgPlmnSearchRsltCnfMsg->enBgPlmnSearchScene,
                                                 &pstBgPlmnSearchRsltCnfMsg->stSearchedPlmnListInfo);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GenerateRegRsltCsDomainAdditionalAction_L1Main
 ��������  : ��L1 MAIN״̬�յ�ѡ��״̬����ע����ʱ����ȡ����CS���AdditionalAction
 �������  : ��
 �������  : ��
 �� �� ֵ  :
              NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON:����������״̬
              NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL:����Ч
              NAS_MMC_ADDITIONAL_ACTION_BUTT
              NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION:ע�ᱻ��ԭ��#12
              NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED:��������
              NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON:��ON PLMN״̬����פ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��21��
    ��    ��   : w00167002
    �޸�����   : ��������
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GenerateRegRsltCsDomainAdditionalAction_L1Main( VOS_VOID )
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsCause;          /* �洢ע����CS�򱻾���Ϣ */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsCause;          /* �洢ע����PS�򱻾���Ϣ */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_MS_MODE_ENUM_UINT8                              enMsMode;

    /* ��ȡLTE�µ�UEģʽ */
    enMsMode = NAS_MML_GetMsMode();
#endif

    enCsCause = NAS_MML_REG_FAIL_CAUSE_BUTT;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_BUTT;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );

    /* ����CS�ķ���״̬����CS��additionֵ */
    if ( VOS_TRUE == NAS_MMC_IsCsNormalService() )
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* CS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }

    /* ע��ʧ��ԭ��ֵ#12�Ĵ��� */
    if ( NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == enCsCause )
    {
        return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
    }

    /* ��������ACCESS BAR �Ĵ��� */
    if ( NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED == enCsCause )
    {
        return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* Lģ��PS onlyʱ��CS���AdditionֵΪBUTT */
    if ( (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
      && (NAS_MML_MS_MODE_PS_ONLY  == enMsMode) )
    {
        return NAS_MMC_ADDITIONAL_ACTION_BUTT;
    }
#endif

    /* �������յ�ע����ʱ���õ�ǰΪ����פ�� */
    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GenerateRegRsltPsDomainAdditionalAction_L1Main
 ��������  : ��L1 MAIN״̬�յ�ѡ��״̬����ע����ʱ����ȡ����PS���AdditionalAction
 �������  : ��
 �������  : ��
 �� �� ֵ  :
              NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON:����������״̬
              NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL:����Ч
              NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION:ע�ᱻ��ԭ��#12
              NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED:��������
              NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON:��ON PLMN״̬����פ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��21��
    ��    ��   : w00167002
    �޸�����   : ��������
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GenerateRegRsltPsDomainAdditionalAction_L1Main( VOS_VOID )
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;                              /* �洢ע����CS�򱻾���Ϣ */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;                              /* �洢ע����PS�򱻾���Ϣ */

    enCsCause = NAS_MML_REG_FAIL_CAUSE_BUTT;
    enPsCause = NAS_MML_REG_FAIL_CAUSE_BUTT;

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );
    /* PS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL;
    }

    /* ע��ʧ��ԭ��ֵ#12�Ĵ��� */
    if ( NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW == enPsCause )
    {
        return NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION;
    }

    /* ��������ACCESS BAR �Ĵ��� */
    if ( NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED == enPsCause )
    {
        return NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED;
    }

     /* ����PS�ķ���״̬����PS��additionֵ */
    if (VOS_TRUE == NAS_MMC_IsPsNormalService())
    {
        return NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
    }

    /* �������յ�ע����ʱ���õ�ǰΪ����פ�� */
    return NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnterOocStatusWhenAreaLost_OnPlmn
 ��������  : �жϽ�����ϱ�����֮���Ƿ���Ҫ��������OOC״̬
 �������  : NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enSearchedType
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedEnterOocStatusWhenAreaLost_OnPlmn(
    NAS_MMC_SEARCHED_TYPE_STRU                             *pstSearchedType
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList  = VOS_NULL_PTR;

    pstPrioRatList  = NAS_MML_GetMsPrioRatList();

    /* ��ģʱ������Ҫ��������OOC״̬ */
    if (1 != pstPrioRatList->ucRatNum)
    {
        return VOS_FALSE;
    }

    /* û����Ϣʱ��Ĭ��û���ѹ���������OOC״̬ */
    if (VOS_NULL_PTR == pstSearchedType)
    {
        return VOS_FALSE;
    }

    /* ��ģʱ�������ǰģʽ���ѽ��й�spec������pref band���������Խ���OOC״̬ */
    if ((VOS_TRUE == pstSearchedType->ucPrefBandSearchedFlg)
     || (VOS_TRUE == pstSearchedType->ucSpecSearchedFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Modified by z00161729 for DCM�����������������, 2012-8-22, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAnycell_OnPlmn
 ��������  : �ж��Ƿ���Ҫ����anycell����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ����anycell����
             VOS_FALSE - �������anycell����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAnycell_OnPlmn( VOS_VOID )
{
    /* ����Ч��Ҫ����anycell�� */
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_TRUE;
    }

    /* ������ڻ���Ľ�����ҵ����Ҫanycell���� */
    if (VOS_TRUE == NAS_MML_IsExistBufferedEmgCall())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Modified by z00161729 for DCM�����������������, 2012-8-22, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnListTriggerPlmnSrch_L1Main
 ��������  : �ж�PLMN LIST�Ƿ񴥷�����
 �������  : pstListRslt-PLMN LIST�˳����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ��������
             VOS_FALSE - �����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��7��
    ��    ��   : w0176964
    �޸�����   : ��������
  2.��    ��   : 2012��8��21��
    ��    ��   : w00176964
    �޸�����   : DTS2012111404729:����פ����ACC BARС���������û�LIST����
                 ֻ�ѵ���ǰ�����,�������������ڲ�LIST����
  3.��    ��   : 2012��12��07��
    ��    ��   : w00176964
    �޸�����   : DTS2012120401487:L��detach CS/PS���û�LIST��������Ӧ�ò�����
  4.��    ��   : 2013��11��25��
    ��    ��   : z00161729
    �޸�����    : SVLTE�Ż�G-TL ps�л������޸�
  5.��    ��   : 2014��1��17��
    ��    ��   : w00242748
    �޸�����   : DTS2014011516578:UE��ǰפ��С��ACCESS BAR�󣬽����б��ѣ�UE�ٴ�
                 ����������ACCESS BAR����²�Ӧ����������enPsAdditionalAction��д��
                 enCsAdditionalAction��
  6.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnListTriggerPlmnSrch_L1Main(
    NAS_MMCMMC_PLMN_LIST_RSLT_STRU     *pstListRslt
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    VOS_UINT32                                              ucSpecPlmnSearchFlg;
    VOS_UINT8                                               ucPsAttachAllow;

    VOS_UINT8                                   ucIsSvlteSupportFlg;
    VOS_UINT8                                   ucLcEnableFlg;

    ucIsSvlteSupportFlg  = NAS_MML_GetSvlteSupportFlag();
    ucLcEnableFlg        = NAS_MML_GetLcEnableFlg();

    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_L1Main();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_L1Main();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    ucSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();

    ucPsAttachAllow = NAS_MML_GetPsAttachAllowFlg();

    /* פ��̬ʱ,��ǰΪacc bar��12�ܾ���CS/PS��detachʱ����Ҫ�ٴη������� */
    if ((NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
     && (NAS_MMC_SPEC_PLMN_SEARCH_STOP == ucSpecPlmnSearchFlg))
    {
        /* �ڷ�SVLTE��C+L��̬ʱ��CS/PS���������ٴη������� */
        if ( (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
          && (VOS_FALSE == ucIsSvlteSupportFlg)
          && (VOS_FALSE == ucLcEnableFlg)
          && (VOS_FALSE == ucPsAttachAllow) )
        {
            return VOS_FALSE;
        }

        if ((NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enCsAdditionalAction)
         || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enPsAdditionalAction))
        {
            return VOS_FALSE;
        }

        if ((NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enCsAdditionalAction)
         || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enPsAdditionalAction))
        {
            return VOS_FALSE;
        }
    }

    /* ���LIST�����˳�����������Ҫ��������
       ���LIST����������ע�ᱻ�ܵ��¿���Ч,�˳��󲻻�Я��������־,
       ��Ҫ����additionֵ����һ���ж� */
#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus())
    {
        return VOS_TRUE;
    }
#endif

    if (VOS_TRUE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == pstListRslt->ucNeedPlmnSearch)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsAnycellSrchSuccStartAvailableTimer_Initial
 ��������  : �ж�Anycell�����ɹ�ʱ�Ƿ���Ҫ����Available��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ����Available��ʱ��
             VOS_FALSE - ��������Available��ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��27��
    ��    ��   : s00217060
    �޸�����   : ��������
  2.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAnycellSrchSuccStartAvailableTimer_Initial( VOS_VOID )
{
    VOS_UINT32                                ulLteOnlyFlg;
    VOS_UINT32                                ulGsmOnlyFlg;
    VOS_UINT32                                ulGsmForbFlg;
    NAS_MML_SIM_TYPE_ENUM_UINT8               enSimType;

    ulLteOnlyFlg   = NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList());
    ulGsmOnlyFlg   = NAS_MML_IsGsmOnlyMode(NAS_MML_GetMsPrioRatList());
    ulGsmForbFlg   = NAS_MML_GetGsmForbidFlg();
    enSimType      = NAS_MML_GetSimType();

    /* ���UE���õ�������ʽ������ֹ��������Available Timer��ʱ��*/
    if (VOS_TRUE == NAS_MML_IsAllMsRatInForbiddenList())
    {
        return VOS_FALSE;
    }


    /* �������������е��κ�һ��ʱ������Ҫ����Available��ʱ��
       1)����Ч
       2) ����Ч����������SIM��������LTE only
       3) ����Ч��USIM����ֹGSM�����û�����GSM only */

    if ( VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        return VOS_FALSE;
    }

    /* SIM��������LTE onlyʱ,������Available��ʱ�� */
    if ( (NAS_MML_SIM_TYPE_SIM == enSimType)
      && (VOS_TRUE == ulLteOnlyFlg) )
    {
        return VOS_FALSE;
    }

    /* USIM����ֹGSM�����û�����GSM only,������Available��ʱ�� */
    if ( (VOS_TRUE == ulGsmForbFlg)
      && (VOS_TRUE == ulGsmOnlyFlg) )
    {
        return VOS_FALSE;
    }

    /* ����������п�����Available��ʱ�� */
    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmmLimitServiceCampInd_OnPlmn
 ��������  : ����RRMM_LIMIT_SERVICE_CAMP_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:     MMCMMC_BG_PLMN_SEARCH_RSLT_CNF��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��06��24��
   ��    ��   : l65478
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��21��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                *pastIntraPlmnSrchInfo = VOS_NULL_PTR;
    RRMM_LIMIT_SERVICE_CAMP_IND_STRU                    *pstRrmmLimitCampOnMsg;
    VOS_UINT32                                           ulRatCnt;

    pstRrmmLimitCampOnMsg = (RRMM_LIMIT_SERVICE_CAMP_IND_STRU *)pstMsg;

    pastIntraPlmnSrchInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                             sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);
    /* �����ڴ�ʧ�� */
    if (VOS_NULL_PTR == pastIntraPlmnSrchInfo)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(pastIntraPlmnSrchInfo, 0, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

    for (ulRatCnt = 0; ulRatCnt < NAS_MML_MAX_RAT_NUM; ulRatCnt++)
    {
        pastIntraPlmnSrchInfo[ulRatCnt].enRatType = NAS_MML_NET_RAT_TYPE_BUTT;
    }

    NAS_MMC_InitSearchedPlmnListInfo(pastIntraPlmnSrchInfo);

    /* ת��W�µ������ʽ */
    NAS_MMC_UpdateSearchedPlmnListInfo(VOS_NULL_PTR, &(pstRrmmLimitCampOnMsg->stPlmnIdList), pastIntraPlmnSrchInfo);

    /* ɾ���б��н�ֹ��PLMN */
    NAS_MMC_DelForbPlmnFromAsSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* �ֶ�����ģʽ��ɾ�����û�ָ����PLMN */
    NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* ��ά�ɲ���Ϣ���� */
    NAS_MMC_LogAsPlmnList(pastIntraPlmnSrchInfo);

    if (VOS_TRUE == NAS_MMC_IsExistAvailPlmnInSearchedPlmnList(pastIntraPlmnSrchInfo))
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_INTER_SYS_OOS, pastIntraPlmnSrchInfo, NAS_MML_MAX_RAT_NUM);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);

    return VOS_TRUE;
}

/* NAS_MMC_DelForbPlmnFromAsSrchedPlmnList��NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList
   ��������NasMmcCommFunc.c�� */



#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccNcellInfoNotify_OnPlmn
 ��������  : ����ID_MSCC_MMC_NCELL_INFO_NOTIFY��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:     ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 2.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccNcellInfoNotify_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_AVAILABLE_TIMER))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_AVAILABLE_TIMER);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_AVAILABLE_TIMER, TI_NAS_MMC_NCELL_PLMN_SEARCH_AVAILABLE_TIMER_LEN);
    }
    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSingleDomainRegFailNeedPlmnSrchCause
 ��������  : �ж��ڵ���ע��ʧ��ʱ�Ƿ���Ҫ��������
 �������  : VOS_VOID
 �������  : VOS_TRUE : ��Ҫ��������
             VOS_FALSE: ����Ҫ��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��06��24��
   ��    ��   : l65478
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��10��17��
   ��    ��   : l65478
   �޸�����   : DTS2013102207188:DT����:��PS����ʧ��#14ʱҲ��Ҫ��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsSingleDomainRegFailNeedPlmnSrchCause(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    switch (enCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE:
    case NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG:
    case NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF:
    case NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE:
    case NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED:
    case NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR:
    case NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT:
    case NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL:
    case NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL:
    case NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE:
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
        return VOS_TRUE;
    default:
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch
 ��������  : �ж��ڵ���ע��ʧ��ʱ�Ƿ���Ҫ��������
 �������  : VOS_VOID
 �������  : VOS_TRUE : ��Ҫ��������
             VOS_FALSE: ����Ҫ��������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��06��24��
   ��    ��   : l65478
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��10��17��
   ��    ��   : l65478
   �޸�����   : DTS2013102207188:DT����:��PS����ʧ��#14ʱҲ��Ҫ��������

 3.��    ��   : 2014��5��21��
   ��    ��   : w00167002
   �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enRegFailDomain
)
{
    VOS_UINT8                           ucSingleDomainSrchFlag;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause;
    NAS_MMC_SERVICE_ENUM_UINT8          enCsService;
    NAS_MMC_SERVICE_ENUM_UINT8          enPsService;

    ucSingleDomainSrchFlag    = NAS_MML_GetDtSingleDomainPlmnSearchFlag();


    /* ԭ��ֵ��ʼ��ΪBUT,Ĭ�ϲ����� */
    enCsCause   = NAS_MML_REG_FAIL_CAUSE_BUTT;
    enPsCause   = NAS_MML_REG_FAIL_CAUSE_BUTT;

    enCsService = NAS_MMC_GetCsServiceStatus();
    enPsService = NAS_MMC_GetPsServiceStatus();

    NAS_MMC_GetDomainRegStatusInRegInfoList( NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             &enCsCause,
                                             &enPsCause );


    /* SOR���ƴ�ʱ��CSע��ʧ��#17����Ҫ����LIST���� */
    if ((VOS_TRUE                               == NAS_MML_GetCsRejSearchSupportFlg())
     && (NAS_MSCC_PIF_SRVDOMAIN_CS                   == enRegFailDomain)
     && (NAS_MMC_LIMITED_SERVICE                == enCsService)
     && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsCause))
    {
        return VOS_TRUE;
    }

    /* �����ܴ�,�����Ʒ���,ԭ��ֵ������ܾ�OTHER CAUSE,��Ҫ���� */
    if ((VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrchCause(enCsCause))
     && (NAS_MSCC_PIF_SRVDOMAIN_CS    == enRegFailDomain)
     && (NAS_MMC_LIMITED_SERVICE == enCsService)
     && (VOS_TRUE                == ucSingleDomainSrchFlag))
    {
        return VOS_TRUE;
    }

    if ((VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrchCause(enPsCause))
     && (NAS_MSCC_PIF_SRVDOMAIN_PS    == enRegFailDomain)
     && (NAS_MMC_LIMITED_SERVICE == enPsService)
     && (VOS_TRUE                == ucSingleDomainSrchFlag))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-10, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsVoiceCapInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�ID_MSCC_MMC_IMS_VOICE_CAP_IND��Ϣ�Ĵ���
 �������  : ulEventType:ID_MSCC_MMC_IMS_VOICE_CAP_IND��Ϣ����
             pstMsg: ID_MSCC_MMC_IMS_VOICE_CAP_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)

    /* ����ON PLMN�ĳ���������ҪDisable Lģ�� */

    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* �����ڲ����� */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE, VOS_NULL_PTR, 0);

#endif

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-10, end */


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsSwitchStateInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�ID_MSCC_MMC_IMS_SWITCH_STATE_IND��Ϣ�Ĵ���
 �������  : ulEventType:ID_MSCC_MMC_IMS_SWITCH_STATE_IND��Ϣ����
             pstMsg: ID_MSCC_MMC_IMS_SWITCH_STATE_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsSwitchStateInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����ѡ��״̬�����������ȡ��ע�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* enable lte����Ҫ���������������ڲ�������Ϣ */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccVoiceDomainChangeInd_OnPlmn
 ��������  : ��ON PLMNʱ���յ�ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType:ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND��Ϣ����
             pstMsg: ID_MSCC_MMC_VOICE_DOMAIN_CHANGE_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ����������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccVoiceDomainChangeInd_OnPlmn(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����ѡ��״̬�����������ȡ��ע�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* enable lte����Ҫ���������������ڲ�������Ϣ */
    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_StartHighPrioRatHplmnTimer_BgSearch_OnPlmn
 ��������  : ����BG����״̬���˳���������������ȼ�������ض�ʱ���Ĵ���
 �������  : pstBgPlmnSearchRsltCnfMsg:BG���˳������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : �½�����
 2.��    ��   : 2014��4��10��
   ��    ��   : w00242748
   �޸�����   : DTS2014040905679:���뼼��˳��030201����ǰפ����GSM�ϣ�
                �����ȼ����뼼��HPLMN����Lʧ�ܣ�����W�ɹ����ɹ�ע����ٴ�
                ���������ȼ����뼼��HPLMNʱ����ʱ��ʱ������ȷ��
13.��    ��   : 2014��10��27��
   ��    ��   : b00269685
   �޸�����   : ����High_Prio_rat_hplmn TD Count�Ĵ���
*****************************************************************************/
VOS_VOID  NAS_MMC_StartHighPrioPlmnSearchTimer_BgSearch_OnPlmn(
    NAS_MMCMMC_BG_PLMN_SEARCH_RSLT_STRU                    *pstBgPlmnSearchRsltCnfMsg
)
{
    VOS_UINT32                          ulHplmnTimerLen;
    VOS_UINT8                           ucActingHplmnSupportFlg;

    if (VOS_TRUE == NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer())
    {
        if (VOS_TRUE == pstBgPlmnSearchRsltCnfMsg->ulSearchCompleted)
        {
           ulHplmnTimerLen = NAS_MMC_GetHighPrioRatHplmnTimerLen();
        }
        else
        {
           ulHplmnTimerLen = NAS_MMC_GetHighPrioRatHplmnTimerRetryLen();
        }

        if (VOS_TRUE == NAS_MMC_StartTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER, ulHplmnTimerLen))
        {
            if (VOS_TRUE == pstBgPlmnSearchRsltCnfMsg->ulSearchCompleted)
            {
                NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
                NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount();
            }
        }

        /* ��RAT��BG������ʱ����Ҫ����ʱ,Hplmn��10S�����Գ���BG������ʱ���ɲ��Զ� */
        return;
    }

    if (VOS_TRUE == pstBgPlmnSearchRsltCnfMsg->ulSearchCompleted)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedStartHPlmnTimer())
        {
            /* ������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());

            /* HPLMN TIMER�����¼��ϱ� */
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            /* ��HPLMN������������Ϊ���״����� */
            NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
        }
    }
    else
    {
        /* ��UTRANģʽΪFDDʱ��ʱ����0����֧��ActingHplmn��������10s�����Գ��Զ�ʱ�� */
        ucActingHplmnSupportFlg = NAS_MML_GetActingHplmnSupportFlg();

        /* פ����HPLMNʱ,Hplmn��10S�����Գ���BG������ʱ���ɲ��Զ� */
        if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(NAS_MML_GetCurrCampPlmnId()))
        {
            return;
        }

        if ((0 != NAS_MMC_GetHplmnTimerLen())
         || (VOS_TRUE == ucActingHplmnSupportFlg))
        {
            /* FDD���������ڸ����ȼ����Զ�ʱ�� */
            if ( NAS_UTRANCTRL_UTRAN_MODE_TDD != NAS_UTRANCTRL_GetCurrUtranMode() )
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH, TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH_LEN);
            }
            /* TDD���������������ȼ��Ѷ�ʱ�� */
            else
            {
                /* ������ʱ�� */
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_HPLMN_TIMER, NAS_MMC_GetHplmnTimerLen());

                /* HPLMN TIMER�����¼��ϱ� */
                NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_START,
                                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

                /* ��HPLMN������������Ϊ���״����� */
                NAS_MMC_SetFirstStartHPlmnTimerFlg(VOS_FALSE);
            }
        }
    }

    return;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-02-13, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsRegReqTriggerPlmnSrch_L1Main
 ��������  : �ж�MSCC��REG REQ�Ƿ񴥷�����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ��������
             VOS_FALSE - �����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��13��
    ��    ��   : s00246516
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsRegReqTriggerPlmnSrch_L1Main(
    MSCC_MMC_REG_REQ_STRU                         *pstRegReq
)
{
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8        enRegPlmnPrioClass;

    /* ������������Ҫ�������� */
    if (VOS_FALSE == NAS_MMC_IsNormalServiceStatus())
    {
        return VOS_TRUE;
    }

    enRegPlmnPrioClass = NAS_MMC_GetPlmnPrioClass(NAS_MML_GetCurrCampPlmnId());

    /* ��ǰ����Ϊ����Ҫ����������Ҫ�������� */
    if (VOS_TRUE == pstRegReq->bitOpPrioClass)
    {
        if (VOS_TRUE == NAS_MMC_ComParePlmnPrioClass(enRegPlmnPrioClass, pstRegReq->enPrioClass))
        {
            return VOS_FALSE;
        }
    }
    else if (VOS_TRUE == pstRegReq->bitOpCellInfo)
    {
        if (VOS_TRUE == NAS_MMC_IsSuccRegInSpecCellInfo(&(pstRegReq->stCellInfo)))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        /* ��������REG������û��ָ����Ҫע���������������������쳣���������������� */
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-02-13, End */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccPlmnSrchReq_Ooc
 ��������  : OOC״̬�յ�MSCC��PLMN��������Ĵ���
 �������  : ulEventType:��Ϣ����
            : pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��2��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccPlmnSrchReq_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    /* ����Ч������ANY CELL״̬�� */
    if ( VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_ANYCELL_SEARCH);
    }
    else
    {
        NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_PLMN_SELECTION);
    }

    NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                             NAS_MML_GetSimPsRegStatus());

    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccPlmnSrchReq_Deact
 ��������  : Deactive״̬�յ�MSCC��PLMN��������Ĵ���,����ʽ��OCC״̬����ͬ��
            ֱ�ӵ���NAS_MMC_RcvMsccPlmnSrchReq_Ooc
 �������  : ulEventType:��Ϣ����
            : pstMsg:��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4����
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccPlmnSrchReq_Deact(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvMsccPlmnSrchReq_Ooc(ulEventType, pstMsg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLteCoverageFlg_L1Main
 ��������  : �������������ȡLTE�ĸ��Ǳ��
 �������  : pstPlmnSelectionRslt ---- �������
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��17��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8  NAS_MMC_GetLteCoverageFlg_L1Main(
    NAS_MMCMMC_PLMN_SELECTION_RSLT_STRU                    *pstPlmnSelectionRslt
)
{
    VOS_UINT8                           ucRatIndex;

    for (ucRatIndex = 0; ucRatIndex < NAS_MML_MAX_RAT_NUM; ucRatIndex++)
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == pstPlmnSelectionRslt->astSearchRatInfo[ucRatIndex].enRatType)
        {
            if (NAS_MMC_COVERAGE_TYPE_NONE == pstPlmnSelectionRslt->astSearchRatInfo[ucRatIndex].enCoverageType)
            {
                return VOS_FALSE;
            }
            else
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedHistorySearch_L1Main
 ��������  : �Ƿ���Ҫ����history����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8  NAS_MMC_IsNeedHistorySearch_L1Main(VOS_VOID)
{

    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCurHistoryCount = 0;
    VOS_UINT8                                               ucTotalHistoryCount = 0;


    pstPhaseOneOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo         = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulCurHistoryCount                           = NAS_MMC_GetCurHistorySearchTimerCount_OnPlmn();


    /* ��ʱ�����Ͳ���history���ͣ�����Ҫhistory�� */
    if (NAS_MMC_AVAILABLE_TIMER_TYPE_HISTORY != NAS_MMC_GetAvailableTimerType_OnPlmn())
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* ��һ�׶� */
        ucTotalHistoryCount = pstPhaseOneOosPlmnSearchPatternInfo->ucHistoryNum;
    }
    else
    {
         /* �ڶ��׶� */
        ucTotalHistoryCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucHistoryNum;
    }

    /* �趨��ʷ�Ѵ���Ϊ0������Ҫ��ʷ�� */
    if (0 == ucTotalHistoryCount)
    {
        return VOS_FALSE;
    }

    /* ��ǰ��ʷ�������� < �趨��ʷ�Ѵ�������Ҫhistory�� */
    if (ulCurHistoryCount < ucTotalHistoryCount)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;


}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedPrefBandSearch_L1Main
 ��������  : �Ƿ���Ҫ����PrefBand����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : h00281185
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8  NAS_MMC_IsNeedPrefBandSearch_L1Main(VOS_VOID)
{
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseOneOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_OOS_PLMN_SEARCH_PATTERN_INFO_STRU              *pstPhaseTwoOosPlmnSearchPatternInfo  = VOS_NULL_PTR;
    NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8                 enAvailableType;
    VOS_UINT32                                              ulCurPrefBandCount;
    VOS_UINT8                                               ucTotalPrefBandCount = 0;


    pstPhaseOneOosPlmnSearchPatternInfo          = NAS_MMC_GetPhaseOneOosPlmnSearchPatternInfo();
    pstPhaseTwoOosPlmnSearchPatternInfo          = NAS_MMC_GetPhaseTwoOosPlmnSearchPatternInfo();
    ulCurPrefBandCount                           = NAS_MMC_GetCurPrefBandSearchTimerCount_OnPlmn();
    enAvailableType                              = NAS_MMC_GetAvailableTimerType_OnPlmn();


    /* ��ʱ�����Ͳ���history����Ҳ����PrefBand���ͣ�����ҪPrefBand�� */
    if ((NAS_MMC_AVAILABLE_TIMER_TYPE_HISTORY   != enAvailableType)
     && (NAS_MMC_AVAILABLE_TIMER_TYPE_PREFBAND  != enAvailableType))
    {
        return VOS_FALSE;
    }

    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        /* ��һ�׶� */
        ucTotalPrefBandCount = pstPhaseOneOosPlmnSearchPatternInfo->ucPrefBandNum;
    }
    else
    {
         /* �ڶ��׶� */
        ucTotalPrefBandCount = pstPhaseTwoOosPlmnSearchPatternInfo->ucPrefBandNum;
    }

    /* PrefBand�Ѵ����趨Ϊ0������ҪPrefBand�� */
    if (0 == ucTotalPrefBandCount)
    {
        return VOS_FALSE;
    }

    /* ��ǰPrefBand�������� < �趨PrefBand�Ѵ�������ҪPrefBand�� */
    if (ulCurPrefBandCount < ucTotalPrefBandCount)
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;

}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmResumeInd_Deact
 ��������  : ����LMM��ϢlMM_MMC_RESUME_IND
 �������  : ulEventType  VOS_UINT32
           : pstMsg         struct MsgCB *
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��2��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmResumeInd_Deact(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_ON_PLMN);

    /* ������ǰ����: ��ϵͳ�л�LTE-->HRPD,ʧ�ܣ����˵�LTE, �յ�RESUME_IND��Ϣ�Ĵ�������
        ʵ�ֹ�����ͬ���յ�RESUME_IND��Ϣ������״̬������ʱ�����ȴ�LMM_MMC_SYS_INFO_IND��Ϣ
    */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsfbRedirFailBackLte_L1Main
 ��������  : �յ�MMCMM_PLMN_SEARCH_IND�����˵�LTE�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcCsfbRedirFailBackLte_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                              stAnycellSrchRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList;

    /* ������ʱ��anycell�� */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        pstPrioRatList       = NAS_MML_GetMsPrioRatList();

        /* ����ANYCELL����,������Ҫanycell�ѵĽ��뼼��ΪGU,����˳����syscfg���� */
        NAS_MMC_BuildCoverageRatPrioListEmgCall_L1Main(pstPrioRatList, &stAnycellSrchRatList);

        NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

        NAS_MMC_SndInterAnyCellSearchReq(&stAnycellSrchRatList, NAS_MMC_ANYCELL_SEARCH_SCENE_BUTT);
        return VOS_TRUE;
    }

    /* �ǽ�����ʱ��CSFB_SERVIEC_REJ���͵��ڲ����� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_L1_STA_INITIAL);

    NAS_MMC_SndInterPlmnSearchReq(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ, VOS_NULL_PTR, 0);

    return VOS_TRUE;
}
#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

