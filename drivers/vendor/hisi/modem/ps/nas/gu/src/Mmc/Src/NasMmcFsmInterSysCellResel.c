/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcFsmInterSysCellResel.c
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2011��03��14��
  ����޸�   :
  ��������   : �������ѡʱ������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��03��14��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "Nasrrcinterface.h"
#include "MM_Share.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndMm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndMscc.h"
#include "NasMmcFsmInterSysCellResel.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcProcSuspend.h"
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
/* ɾ��ExtAppMmcInterface.h*/
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */
#include "NasMmcComFunc.h"
#include "NasUtranCtrlInterface.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_CELLRESEL_C
/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/


/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasSuspendInd_InterSysCellResel_Init
 ��������  : ��SUSPEND��INIT״̬,�յ�was��ϵͳ��ѡָʾ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:�յ�WAS����ϵͳ��ѡָʾ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2012��05��28��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysCellResel_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstGUSuspendMsg = VOS_NULL_PTR;

    pstGUSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM:3��ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstGUSuspendMsg->ucSuspendDestination )
    {
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasSuspendInd_InterSysCellResel_Init
 ��������  : ��SUSPEND��INIT״̬,�յ�Gas��ϵͳ��ѡָʾ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:�յ�GAS����ϵͳ��ѡָʾ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2012��06��01��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysCellResel_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstGUSuspendMsg = VOS_NULL_PTR;

    pstGUSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM:3��ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstGUSuspendMsg->ucSuspendDestination )
    {
        /* ֪ͨLTE��ЧPLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_InterSysCellResel_RSP״̬
             �յ�MMCGMM_Suspend_RSP��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMM_Suspend_RSP��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��14��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2012��11��17��
    ��    ��   : s00217060
    �޸�����   : DTS2012082007133:����д�ϣ����ҹ���ԭ�����ض��򣬸���ͬ�Ľ���㷢��SUSPEND_REL_REQ

  4.��    ��   : 2014��2��26��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:UT�޸�

  5.��    ��   : 2015��04��24��
    ��    ��   : j00174725
    �޸�����   : DSDS(������޸Ķ�ʱ������) DTS2015042702414

  6.��    ��   : 2015��05��30��
    ��    ��   : l00324781
    �޸�����   : CDMA Iteration 12: ���� CLģʽ�£�L2C��ѡ���ض����ܡ�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ������յ�GMM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCellResel( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP�����ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ����д�ϣ����ҹ���ԭ�����ض��򣬸���ͬ�Ľ���㷢��SUSPEND_REL_REQ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
        if ( MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            NAS_MMC_SndSuspendRelReq_InterSysCellResel(NAS_MML_GetCurrNetRatType());

            return VOS_TRUE;
        }
    }

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND );

    /* ƴƬ��CLģʽ�£�������ͬʱ����ʱ�� */
    if (VOS_TRUE == NAS_MMC_StartResumeTimer_InterSysCellResel())
    {
        return VOS_TRUE;
    }

    /* �����GU�ض���,��ʱ��ʱ��Ϊ90S;�����GL WL֮����ض���,��ʱ��ʱ��Ϊ200S */
    if ( MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

         return VOS_TRUE;
    }

    /* ��ȡ����Ŀ�ķ����������� */
#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendDestinationRatType(NAS_MMC_GetCurrEntryMsg()))
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, TI_NAS_MMC_INTER_SYS_GUL_REDIR_WAIT_AS_RESUME_IND_LEN);
    }
    else
#endif
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);
    }

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_InterSysCellResel_RSP״̬
             �յ�MMCMM_Suspend_RSP��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMM_Suspend_RSP��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��14��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2012��11��17��
    ��    ��   : s00217060
    �޸�����   : DTS2012082007133:����д�ϣ����ҹ���ԭ�����ض��򣬸���ͬ�Ľ���㷢��SUSPEND_REL_REQ
  4.��    ��   : 2015��04��24��
    ��    ��   : j00174725
    �޸�����   : DSDS(������޸Ķ�ʱ������) DTS2015042702414
  5.��    ��   : 2015��05��30��
    ��    ��   : l00324781
    �޸�����   : CDMA Iteration 12: ���� CLģʽ�£�L2C��ѡ���ض����ܡ�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ������յ�MM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCellResel( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ����д�ϣ����ҹ���ԭ�����ض��򣬸���ͬ�Ľ���㷢��SUSPEND_REL_REQ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
        if (MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            NAS_MMC_SndSuspendRelReq_InterSysCellResel(NAS_MML_GetCurrNetRatType());

            return VOS_TRUE;
        }
    }

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND );

    /* ƴƬ��CLģʽ�£�������ͬʱ����ʱ�� */
    if (VOS_TRUE == NAS_MMC_StartResumeTimer_InterSysCellResel())
    {
        return VOS_TRUE;
    }

    /* �����GU�ض���,��ʱ��ʱ��Ϊ90S;�����GL WL֮����ض���,��ʱ��ʱ��Ϊ200S */
    if ( MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

         return VOS_TRUE;
    }

    /* ��ȡ����Ŀ�ķ����������� */
#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendDestinationRatType(NAS_MMC_GetCurrEntryMsg()))
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, TI_NAS_MMC_INTER_SYS_GUL_REDIR_WAIT_AS_RESUME_IND_LEN);
    }
    else
#endif
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);
    }

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCellResel_WaitMmSuspendRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_InterSysCellResel_RSP״̬
              �յ�TI_NAS_MMC_WAIT_MM_Suspend_RSP_TIMER��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_MM_Suspend_RSP_TIMER��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��12��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCellResel_WaitMmSuspendRsp:ENTERED");

    /* �����㷢�͹���ʧ�� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmSuspendRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_InterSysCellResel_RSP״̬
             �յ�MMCMMC_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��ϱ�־ */
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_TRUE);

    /* ��������MM/GMM��SUSPEND_RSP���ٸ�����㷢RRMM_SUSPEND_REL_REQ */

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsResumeInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND״̬
              �յ�WAS:RRMM_RESUME_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_RESUME_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��12��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2011��12��1��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseIV �׶ε���

  4.��    ��   : 2012��9��11��
    ��    ��   : z40661
    �޸�����   : DTS2012090505066:��ϵͳ�����ź������ϱ�����ȷ
  5.��    ��   : 2012��10��22��
    ��    ��   : t00212959
    �޸�����   : DTS2012101907218:���Ʒ�����ϱ�ʱ������ȷ
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;


    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  ��ϵͳ������ģʽ�����С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_WCDMA);
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsResumeInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND״̬
              �յ�GAS:RRMM_RESUME_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_RESUME_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��12��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���

 3.��    ��   : 2012��9��11��
   ��    ��   : z40661
   �޸�����   : DTS2012090505066:��ϵͳ�����ź������ϱ�����ȷ
 4.��    ��   : 2012��10��22��
   ��    ��   : t00212959
   �޸�����   : DTS2012101907218:���Ʒ�����ϱ�ʱ������ȷ
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;


    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_GSM);
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcWaitAsResumeIndTimerOutInSuspendWaitAsResumeInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND״̬
              �յ�TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��12��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���

  3.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011120702166:MMC��λ���޸�λ��Ϣ,��MMLģ���װ��λ��Ϣ��
                  �Թ�MM����ã�������λ��
  4.��    ��   : 2014��2��18��
    ��    ��  :  w00242748
    �޸�����  :  DTS2014021803515:��λʱ��ȷ���յ��ĸ����뼼�����쳣��Ϣ���µġ�

  5.��    ��   : 2015��3��11��
    ��    ��   : wx270776
    �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCellResel_WaitAsResumeInd:ENTERED");

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_LMM_WAIT_RESUME_IND_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_TD_WAIT_RESUME_IND_EXPIRED);
    }

   return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitAsResumeInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND״̬
              �յ�MMCMMC_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
    VOS_UINT32                          ulIsSysChgToHrpd;

    ulIsSysChgToHrpd = NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg());
#endif

    /* ��¼��ϱ�־ */
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_TRUE);

    /* �����GU�ض���,��GU����㷢RRMM_SUSPEND_REL_REQ
       �����Lģ�ض���GU����LMM����LMM_SUSPEND_REL_REQ */
    if (( MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
      || (VOS_TRUE == ulIsSysChgToHrpd)
#endif
      )
    {
        /* ֹͣTI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF);

        /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

        NAS_MMC_SndSuspendRelReq_InterSysCellResel(NAS_MML_GetCurrNetRatType());
    }

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_InterSysCellResel_WaitAsResumeInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND״̬
             �յ�RRMM_REL_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��28��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��23��
    ��    ��   : l00130025
    �޸�����   : DTS2012031604090,�յ�WRR��Rel_indʱû������RAT�����»ָ�ResumeRsp����
  3.��    ��   : 2012��5��24��
    ��    ��   : l00171473
    �޸�����   : DTS2012051104124, relind�����޸�
  4.��    ��   : 2012��9��11��
    ��    ��   : z40661
    �޸�����   : DTS2012090505066:��ϵͳ�����ź������ϱ�����ȷ
  5.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : DTS2012082007133:�д�ϱ�־ʱ���˳�״̬������������Ϣ
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelInd = VOS_NULL_PTR;
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    pstRelInd = (RRMM_REL_IND_STRU*)pstMsg;


    /* �ͷ�ԭ��ΪUtran releaseʱ, ��Ҫ������ѡ����, �����ȴ�resume ind,
       ������Ϊ���̽���, ����WAS�ָ�, ����ͬWAS������resume ind */
    if (RRC_REL_CAUSE_UTRAN_RELEASE == pstRelInd->ulRelCause)
    {
        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ֹͣTI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);


    /* ����resume��Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* ���ǰ���д�ϱ�־���˳���ǰ״̬������������Ϣ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
        /* �ظ�InterSysCellReselִ�н�� */
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmResumeRsp_InterSysCellResel_WaitMmResumeRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬
              �յ�MMCGMM_RESUME_RSP��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCGMM_RESUME_RSP��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��12��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2011��12��12��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseIV �׶ε���:�����ȴ�WASϵͳ��Ϣʱ��
  4.��    ��   : 2012��6��1��
    ��    ��   : l00130025
    �޸�����   : DTS2012053003593:FACH̬����������W������������������ָܻ�
  5.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : DTS2012082007133:�д�ϱ�־ʱ���˳�״̬������������Ϣ
  6.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��cerssi��nmr
  7.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����  : L-C��������Ŀ��������ѡ��HRPD�Ĵ���
  8.��    ��   : 2015��05��30��
    ��    ��   : l00324781
    �޸�����   : CDMA Iteration 12: ���� CLģʽ�£�L2C��ѡ���ض����ܡ�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;
#if (FEATURE_ON == FEATURE_LTE)
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
    VOS_UINT32                          ulIsSysChgToHrpd;
#endif
    enSuspendCause                      = NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg());
#endif
    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    NAS_MMC_ClearResumeRspFlag_InterSysCellResel( NAS_MMC_GMM_RESUME_RSP_FLG );

    /* δ������GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣMMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    if(VOS_TRUE == NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel())
    {
        return VOS_TRUE;
    }

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ���ǰ���д�ϱ�־�����ҵ�ǰ���뼼������LTE���˳���ǰ״̬������������Ϣ
       �����ǰ���뼼����LTE,��Ҫ������LTE��ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
#if (FEATURE_ON == FEATURE_LTE)
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
        ulIsSysChgToHrpd = NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg());
#endif
        if ((NAS_MML_NET_RAT_TYPE_LTE != enCurNetType)
           || ((MMC_SUSPEND_CAUSE_CELLRESELECT == enSuspendCause)
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
          &&(VOS_FALSE == ulIsSysChgToHrpd)
#endif
          ))
#endif
        {
            /* �ظ�InterSysCellReselִ�н�� */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    /* ���ݲ�ͬ����������Ǩ�Ƶ���ͬ��״̬ */
    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:


            /* W��Cell Reselect ��ѡ���˵� W�£����ܽ���FACH̬�����������̣���Ҫ��ǰ�˳���ϵͳ��Ϣ�к���״̬������ */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                /* ����״̬���ɹ��Ľ�� */
                NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

                /* �˳���ǰ״̬��: */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;

            }
            else
            {
                /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND״̬ */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND);

                /* WAS�Ļ��������У��ϱ�ϵͳ��Ϣʱ��ϳ��������ȴ�ϵͳ��Ϣʱ�� */
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
                }
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvGmmResumeRsp_InterSysCellResel_WaitMmResumeRsp:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcMmResumeRspInSuspendWaitMmResumeRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬
              �յ�MMCMM_RESUME_RSP��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMM_RESUME_RSP��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��12��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2011��12��12��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseIV �׶ε���:�����ȴ�WASϵͳ��Ϣʱ��
  4.��    ��   : 2012��6��1��
    ��    ��   : l00130025
    �޸�����   : DTS2012053003593:FACH̬����������W������������������ָܻ�
  5.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : DTS2012082007133:�д�ϱ�־ʱ���˳�״̬������������Ϣ
  6.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����  : ֧��cerssi��nmr
  7.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����  : L-C��������Ŀ��������ѡ��HRPD�Ĵ���
  8.��    ��   : 2015��05��30��
    ��    ��   : l00324781
    �޸�����   : CDMA Iteration 12: ���� CLģʽ�£�L2C��ѡ���ض����ܡ�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;
#if (FEATURE_ON == FEATURE_LTE)
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
    VOS_UINT32                          ulIsSysChgToHrpd;
#endif
    enSuspendCause                      = NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg());
#endif
    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    NAS_MMC_ClearResumeRspFlag_InterSysCellResel( NAS_MMC_MM_RESUME_RSP_FLG );

    /* δ����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣMMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* �����ѡ��HRPD��֪ͨLMM�ָ����˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel())
    {
        return VOS_TRUE;
    }

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ���ǰ���д�ϱ�־���˳���ǰ״̬������������Ϣ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
#if   (FEATURE_ON == FEATURE_LTE)
#if   ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
        ulIsSysChgToHrpd = NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg());
#endif
        if ( (NAS_MML_NET_RAT_TYPE_LTE != enCurNetType)
          || ((MMC_SUSPEND_CAUSE_CELLRESELECT == enSuspendCause)
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
          &&(VOS_FALSE == ulIsSysChgToHrpd)
#endif
          ))
#endif
        {
            /* �ظ�InterSysCellReselִ�н�� */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* W��Cell Reselect ��ѡ���˵� W�£����ܽ���FACH̬�����������̣���Ҫ��ǰ�˳���ϵͳ��Ϣ�к���״̬������ */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                /* ����״̬���ɹ��Ľ�� */
                NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

                /* �˳���ǰ״̬��: */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;

            }
            else
            {
                /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND״̬ */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND);

                /* WAS�Ļ��������У��ϱ�ϵͳ��Ϣʱ��ϳ��������ȴ�ϵͳ��Ϣʱ�� */
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
                }
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmResumeRsp_InterSysCellResel_WaitMmResumeRsp:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcWaitMmResumeRspTimerOutInSuspendWaitMmResumeRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬
              �յ�TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��12��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2011��12��12��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseIV �׶ε���:�����ȴ�WASϵͳ��Ϣʱ��
  4.��    ��   : 2012��6��1��
    ��    ��   : l00130025
    �޸�����   : DTS2012053003593:FACH̬����������W������������������ָܻ�
  5.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : DTS2012082007133:�д�ϱ�־ʱ�����ҹ���ԭ������ѡ���˳�״̬������������Ϣ
  6.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��cerssi��nmr
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;
#if (FEATURE_ON == FEATURE_LTE)
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;

    enSuspendCause                      = NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg());
#endif
    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp:ENTERED");

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ���ǰ���д�ϱ�־�����ҹ���ԭ������ѡ���˳���ǰ״̬������������Ϣ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
#if   (FEATURE_ON == FEATURE_LTE)
        if ( (NAS_MML_NET_RAT_TYPE_LTE != enCurNetType)
          || (MMC_SUSPEND_CAUSE_CELLRESELECT == enSuspendCause) )
#endif
        {
            /* �ظ�InterSysCellReselִ�н�� */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:


            /* W��Cell Reselect ��ѡ���˵� W�£����ܽ���FACH̬�����������̣���Ҫ��ǰ�˳���ϵͳ��Ϣ�к���״̬������ */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                /* ����״̬���ɹ��Ľ�� */
                NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

                /* �˳���ǰ״̬��: */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;

            }
            else
            {
                /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND״̬ */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND);

                /* WAS�Ļ��������У��ϱ�ϵͳ��Ϣʱ��ϳ��������ȴ�ϵͳ��Ϣʱ�� */
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
                }
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmResumeRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬
              �յ�MMCMMC_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��ϱ�־ */
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF״̬
              �յ�WAS��SUSPEND_REL_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SUSPEND_REL_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ͣ�ȴ�WAS��SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  ��ϵͳ������ģʽ�����С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitWasSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF״̬
              �յ�WAS��RESUME_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_RESUME_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �Գ峡�����������㷢��RRMM_SUSPEND_REL_REQ,���յ�������RRMM_RESUME_IND
       �ȴ���RRMM_RESUME_IND,�������յ�RRMM_SUSPEND_REL_CNF���� */

    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* ͣ�ȴ�SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(enRatType);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != enRatType)
    {
        /*  ��ϵͳ������ģʽ�����С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF״̬
              �ȴ�WAS��SUSPEND_REL_CNF��Ϣ��ʱ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:�ȴ�RRMM_SUSPEND_REL_CNF��ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  ��ϵͳ������ģʽ�����С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmmRelInd_InterSysCellResel_WaitWasSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF״̬
              �յ�WAS��RRMM_REL_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrmmRelInd_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ͣ�ȴ�WAS��SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  ��ϵͳ������ģʽ�����С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF״̬
              �յ�WAS��SUSPEND_REL_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SUSPEND_REL_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ͣ�ȴ�GAS��SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitGasSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SUSPEND_REL_CNF״̬
              �յ�GAS��RESUME_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_RESUME_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �Գ峡�����������㷢��RRMM_SUSPEND_REL_REQ,���յ�������RRMM_RESUME_IND
       �ȴ���RRMM_RESUME_IND,�������յ�RRMM_SUSPEND_REL_CNF���� */

    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* ͣ�ȴ�SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(enRatType);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);


    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF״̬
              �ȴ�GAS��SUSPEND_REL_CNF��Ϣ��ʱ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:�ȴ�RRMM_SUSPEND_REL_CNF��ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}





/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitWasSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND״̬
              �յ�rrmm_sysinfo_ind��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstmsg:RRMM_SYS_INFO_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��16��
   ��    ��   : l00171473
   �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
 3.��    ��   : 2012��8��14��
   ��    ��   : t00212959
   �޸�����   : DCM�����������������,��ֹLTE����
 4.��    ��   : 2012��10��22��
   ��    ��   : t00212959
   �޸�����   : DTS2012101907218:���Ʒ�����ϱ�ʱ������ȷ
 4.��    ��   : 2012��12��11��
   ��    ��   : w00176964
   �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMMA
 5.��    ��   : 2013��4��10��
   ��    ��   : w00176964
   �޸�����   : DTS2013032507710:����NV����,��ѡ��GU��H3Gʱ�յ�GU��ϵͳ��Ϣ����,�Ƿ�����CS/PS�ķ���״̬
 6.��    ��   : 2013��9��14��
    ��    ��   : w00167002
    �޸�����   : DTS2013090908249:�����û�ָ������24003��CSע�ᱻ��15��MM��LIMIT
                 ״̬����ѡ��״̬���յ�ͬһС����SYSINFO��֪ͨMM��ǰû��FORB FLG,
                 ����MM����ѭ��ע�᣻
                 ��NAS_MMC_SndMmGsmSysInfoInd�����У�������û�ָ����������FORBFLG����Ϊnull��
                 �������ȥ����
                 ��ѡ��״̬��ʶ����Ƿ����û�ָ����������������ȷ��ulForbiddenFlg��־��

 7.��    ��   : 2014��1��18��
   ��    ��   : z00234330
   �޸�����   : dts2014011801513,������ϱ���ϵͳ��Ϣ�����п���û��Я��plmnid,
               �˴��жϲ�û���ж�plmnid�Ƿ���Ч
 8.��    ��   : 2014��4��28��
   ��    ��   : w00242748
   �޸�����   : DTS2014042808114:���H3G���γ�����L��ͬ����Ҫ����NV���ơ�
 9.��    ��   : 2014��5��4��
   ��    ��   : t00173447
   �޸�����   : DTS2014042105390,������������
 10.��    ��   : 2014��5��31��
    ��    ��   : y00245242
    �޸�����   : �޸ķ���״̬�ϱ�
 11.��    ��   : 2014��12��19��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI ����״̬�ϱ�������ϵͳ��Ϣ�ϱ�����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    VOS_UINT8                                               ucH3gCtrlFlg;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

    /* Added by t00212959 for DCM�����������������, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-15, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_WAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM�����������������, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-15, end */

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

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMMAģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* ��ϵͳ��ѡʱ����Ҫ���H3G���γ��������⴦������ǰ�����������HPLMN��
       �����״̬��Ҫ�ȸ���Ϊ���޷��� */
    ucH3gCtrlFlg = NAS_MML_GetH3gCtrlFlg();


    /* פ��С���仯ʱ���ϱ�ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    }

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /* ����״̬��ע��״̬�ϱ�����ϵͳ��Ϣ�ϱ����� */
    if ((VOS_TRUE != NAS_MML_ComparePlmnIdWithHplmn(&(stOldCampInfo.stLai.stPlmnId)))
     && (NAS_MML_NET_RAT_TYPE_WCDMA != enOldNtType)
     && (VOS_TRUE == ucH3gCtrlFlg))
    {
        /* С����ѡ���ڳɹ�ע��ǰ�����ϱ�limit service */
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */
    }


    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
    enParentFsmId     = NAS_MMC_GetParentFsmId();
    ulParentEventType = NAS_MMC_GetParentFsmEventType();

    if ( VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enParentFsmId,ulParentEventType) )
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM,������ǰϵͳ��Ϣ�� Forbidden ����Я����ȥ */
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

    }


#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitWasSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND״̬
              �յ�RRMM_AREA_LOST_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstmsg:RRMM_AREA_LOST_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��04��07��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2012040106098,����CoverageLost��service���ϱ�˳���Ը���MMA��״̬��DeepSleep
 3.��    ��   : 2014��5��4��
   ��    ��   : t00173447
   �޸�����   : DTS2014042105390,������������
 4.��    ��   : 2014��04��4��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
 5.��    ��   : 2015��10��22��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND��Ϣ�ӿڱ��
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_WAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
	NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND״̬
              �յ�TI_NAS_MMC_WAIT_WAS_SYS_INFO��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstmsg:TI_NAS_MMC_WAIT_WAS_SYS_INFO��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��04��07��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2012040106098,����CoverageLost��service���ϱ�˳���Ը���MMA��״̬��DeepSleep
 3.��    ��   : 2014��04��4��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd:ENTERED");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_WAS_SYS_INFO_EXP);
    }
    else
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_TAS_SYS_INFO_EXP);
    }

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitWasSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND״̬
              �յ�MMCMMC_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*ֹͣ������ʱ�� TI_NAS_MMC_WAIT_WAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitGasSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND״̬
              �յ�GRRMM_SYS_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstmsg:GRRMM_SYS_INFO_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��16��
   ��    ��   : l00171473
   �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
 3.��    ��   : 2012��8��14��
   ��    ��   : t00212959
   �޸�����   : DCM�����������������,��ֹLTE����
 4.��    ��   : 2012��10��22��
   ��    ��   : t00212959
   �޸�����   : DTS2012101907218,���Ʒ�����ϱ�ʱ��
 5.��    ��   : 2012��12��11��
   ��    ��   : w00176964
   �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMMA
 6.��    ��   : 2013��4��10��
   ��    ��   : w00176964
   �޸�����   : DTS2013032507710:����NV����,��ѡ��GU��H3Gʱ�յ�GU��ϵͳ��Ϣ����,�Ƿ�����CS/PS�ķ���״̬
 7.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ

 8.��    ��   : 2014��5��4��
   ��    ��   : t00173447
   �޸�����   : DTS2014042105390,������������
 9.��    ��   : 2014��5��31��
   ��    ��   : y00245242
   �޸�����   : �޸ķ���״̬�ϱ�
10.��    ��   : 2014��12��19��
   ��    ��   : s00217060
   �޸�����   : Service_State_Optimize_PhaseI ����״̬�ϱ�������ϵͳ��Ϣ�ϱ�����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;
    VOS_UINT8                                               ucH3gCtrlFlg;

    /* Added by t00212959 for DCM�����������������, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-15, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_GAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM�����������������, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-15, end */

    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

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

    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* ��ϵͳ��ѡʱ,NV���ж���,���H3G���γ��������⴦������ǰ�����������HPLMN��
       �����״̬��Ҫ�ȸ���Ϊ���޷��� */
    ucH3gCtrlFlg = NAS_MML_GetH3gCtrlFlg();

    /* ����״̬�ϱ�������ϵͳ��Ϣ�ϱ����� */

    /* פ��С���仯ʱ���ϱ�ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    }

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMMAģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /* ����״̬��ע��״̬�ϱ�����ϵͳ��Ϣ�ϱ����� */
    if ((VOS_TRUE != NAS_MML_ComparePlmnIdWithHplmn(&(stOldCampInfo.stLai.stPlmnId)))
     && (NAS_MML_NET_RAT_TYPE_GSM != enOldNtType)
     && (VOS_TRUE == ucH3gCtrlFlg))
    {
        /* С����ѡ���ڳɹ�ע��ǰ�����ϱ�limit service */
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */
    }

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
    enParentFsmId     = NAS_MMC_GetParentFsmId();
    ulParentEventType = NAS_MMC_GetParentFsmEventType();


    if ( VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enParentFsmId,ulParentEventType) )
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM,������ǰϵͳ��Ϣ�� Forbidden ����Я����ȥ */
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

    }

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitGasSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND״̬
              �յ�RRMM_AREA_LOST_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstmsg:RRMM_AREA_LOST_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��04��07��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2012040106098,����CoverageLost��service���ϱ�˳���Ը���MMA��״̬��DeepSleep
 3.��    ��   : 2014��5��4��
   ��    ��   : t00173447
   �޸�����   : DTS2014042105390,������������
 4.��    ��   : 2014��04��4��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
 5.��    ��   : 2015��10��22��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND��Ϣ�ӿڱ��
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_AREA_LOST_IND_STRU                                *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];

    pstAreaLostInd = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_GAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
	NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    NAS_MMC_BuildPlmnListInfoFromGuAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitGasSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND״̬
              �յ�TI_NAS_MMC_WAIT_GAS_SYS_INFO��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstmsg:TI_NAS_MMC_WAIT_GAS_SYS_INFO��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��04��07��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2012040106098,����CoverageLost��service���ϱ�˳���Ը���MMA��״̬��DeepSleep
 3.��    ��   : 2014��04��4��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����״̬�ϱ���mmc
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd:ENTERED");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_GAS_SYS_INFO_EXP);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitGasSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND״̬
              �յ�MMCMMC_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*ֹͣ������ʱ�� TI_NAS_MMC_WAIT_GAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLSysInfoInd_InterSysCellResel_WaitLSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND״̬
              �յ�ID_LMM_MMC_SYS_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstmsg:ID_LMM_MMC_SYS_INFO_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��4��18��
   ��    ��   : l00130025
   �޸�����   : DTS2012040200480,����ά��EPSע��״̬,��Lģ��CEREG/CGREG��ѯ���ϱ�ʹ��
 3.��    ��   : 2012��4��28��
   ��    ��   : W00166186
   �޸�����   : DTS2012042602593,MMû�б��浱ǰפ����PLMN�����º����жϳ���
 4.��    ��   : 2012��11��20��
   ��    ��   : s00217060
   �޸�����   : DTS2012082007133:�յ�L��ϵͳ��Ϣ������Ϣʱ���ж��ǲ���L�ض���GUʧ�ܣ����˵�L
                ����ǣ����յ�LMM��suspend_rel_cnf�����˳�״̬������������Ϣ
 5.��    ��   : 2012��11��29��
   ��    ��   : w00176964
   �޸�����   : DTS2012042804167:֪ͨCBAģ�鵱ǰ����ģʽΪLTE
 6.��    ��   : 2012��12��20��
   ��    ��   : w00176964
   �޸�����   : DTS2012121906946:�յ�L��ϵͳ��Ϣת����LMM
 7.��    ��   : 2013��1��19��
    ��    ��   : t00212959
    �޸�����   : DTS2012122900189:EPSע��״̬��ȫ��L�ϱ�
 8.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    LMM_MMC_SYS_INFO_IND_STRU                              *pstLmmSysInfoMsg    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmPlmnId        = VOS_NULL_PTR;
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /*ֹͣ������ʱ�� TI_NAS_MMC_WAIT_LMM_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    PS_MEM_SET(&stPlmnId, 0x00, sizeof(NAS_MML_PLMN_ID_STRU));

    pstLmmSysInfoMsg = (LMM_MMC_SYS_INFO_IND_STRU*)pstMsg;

    pstLmmPlmnId = &(pstLmmSysInfoMsg->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]);

    NAS_MMC_ConvertLmmPlmnToGUNasFormat(pstLmmPlmnId, &stPlmnId);

    /* C2L �л���lte plmn������lte plmn ���ȼ� ���ڵ��� 1x ��Ҫ�� */
    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
         /*����״̬��ʧ�ܽ��*/
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
#endif

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);



    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /*�����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC*/
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }
    /* ת��GMMϵͳ��Ϣ,��rabmʹ�� */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    /* L�ض���GU�����ֹͣGURRC�ɹ��������ض���ʧ�ܻ��˵�Lʱ��
       ��Ϣ���͵�˳��Ϊ��LMM�ϱ�RESUME_IND,���ϱ�LMM_SYS_INFO_IND��AREA_LOST_IND
       ������ϱ�SUSPEND_REL_CNF,֮������˳�״̬������������Ϣ��
       ���Դ˴�Ǩ����LMM��SUSPEND_REL_CNF״̬ */
    if ( (VOS_TRUE == NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel())
      && (NAS_MML_NET_RAT_TYPE_LTE == enOldNtType) )
    {
        /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);

        return VOS_TRUE;
    }

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitLSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND״̬
              �յ�ID_LMM_MMC_AREA_LOST_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstmsg:ID_LMM_MMC_AREA_LOST_IND��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��04��07��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2012040106098,����CoverageLost��service���ϱ�˳���Ը���MMA��״̬��DeepSleep
 3.��    ��   : 2012��11��20��
   ��    ��   : s00217060
   �޸�����   : DTS2012082007133:�յ�L��ϵͳ��Ϣ������Ϣʱ���ж��ǲ���L�ض���GUʧ�ܣ����˵�L
               ����ǣ����յ�LMM��suspend_rel_cnf�����˳�״̬������������Ϣ
 4.��    ��   : 2014��5��5��
   ��    ��   : w00242748
   �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                ע��״̬���ϱ���
 5.��    ��   : 2015��10��22��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND��Ϣ�ӿڱ��
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU                             *pstAreaLostInd = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnListInfo[NAS_MML_MAX_RAT_NUM];
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

    pstAreaLostInd = (LMM_MMC_AREA_LOST_IND_STRU*)pstMsg;

    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_LMM_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ���·���״̬ */


    /* ��TAF���������� */
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    /* ֪ͨTAF��ǰ�ķ���״̬ */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* L�ض���GU�����ֹͣGURRC�ɹ��������ض���ʧ�ܻ��˵�Lʱ��
       ��Ϣ���͵�˳��Ϊ��LMM�ϱ�RESUME_IND,���ϱ�LMM_SYS_INFO_IND��AREA_LOST_IND
       ������ϱ�SUSPEND_REL_CNF,֮������˳�״̬������������Ϣ��
       ���Դ˴�Ǩ����LMM��SUSPEND_REL_CNF״̬ */
    if ( (VOS_TRUE == NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel())
      && (NAS_MML_NET_RAT_TYPE_LTE == enOldNtType) )
    {
        /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);

        return VOS_TRUE;
    }

    NAS_MMC_BuildPlmnListInfoFromLmmAreaLostInd(pstAreaLostInd, astPlmnListInfo);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, astPlmnListInfo);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLSysInfoExpired_InterSysCellResel_WaitLSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND״̬
              �յ�TI_NAS_MMC_WAIT_LMM_SYS_INFO��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstmsg:TI_NAS_MMC_WAIT_LMM_SYS_INFO��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��28��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��04��07��
   ��    ��   : l00130025
   �޸�����   : ���ⵥ��:DTS2012040106098,����CoverageLost��service���ϱ�˳���Ը���MMA��״̬��DeepSleep
 3.��    ��   : 2012��11��20��
   ��    ��   : s00217060
   �޸�����   : DTS2012082007133:�յ�L��ϵͳ��Ϣ������Ϣʱ���ж��ǲ���L�ض���GUʧ�ܣ����˵�L
              ����ǣ����յ�LMM��suspend_rel_cnf�����˳�״̬������������Ϣ
 4.��    ��   : 2014��5��5��
   ��    ��   : w00242748
   �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                ע��״̬���ϱ���
 5.��    ��   : 2015��11��16��
   ��    ��   : l00324781
   �޸�����   : DTS2015111004607: ɾ����䣺��ǰ�����������ΪBUTT
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLSysInfoExpired_InterSysCellResel_WaitLSysInfoInd:ENTERED");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ���·���״̬ */
    


    /* ��TAF���������� */
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* L�ض���GU�����ֹͣGURRC�ɹ��������ض���ʧ�ܻ��˵�Lʱ��
       ��Ϣ���͵�˳��Ϊ��LMM�ϱ�RESUME_IND,���ϱ�LMM_SYS_INFO_IND��AREA_LOST_IND
       ������ϱ�SUSPEND_REL_CNF,֮������˳�״̬������������Ϣ��
       ���Դ˴�Ǩ����LMM��SUSPEND_REL_CNF״̬ */
    if ( (VOS_TRUE == NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel())
      && (NAS_MML_NET_RAT_TYPE_LTE == enOldNtType) )
    {
        /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);

        return VOS_TRUE;
    }

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_LNAS_SYS_INFO_EXP);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendInd_InterSysCellResel_Init
 ��������  : ��SUSPEND��INIT״̬,�յ�LMM����ϵͳ��ѡָʾ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:�յ�LTE����ϵͳ��ѡָʾ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2015��11��05��
    ��    ��   : w00176964
    �޸�����   : DTS2015070910837:֪ͨMSCC CL��ϵͳ��ʼָʾ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysCellResel_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                 stSndSuspendMsg;
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg  = VOS_NULL_PTR;

    pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ת��L�Ĺ�����ϢΪGU��ʽ�� */
    NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stSndSuspendMsg);

    if (MMC_SUSPEND_DESTINATION_HRPD == stSndSuspendMsg.ucSuspendDestination)
    {
        /* ��mscc������ϵͳ��ʼָʾ */
        NAS_MMC_SndMsccInterSysStartInd(NAS_MMC_ConvertMmcInterSysCauseToMsccFormat(stSndSuspendMsg.ucSuspendCause),
                                        VOS_RATMODE_LTE,
                                        VOS_RATMODE_HRPD);
    }

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(&stSndSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(&stSndSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ��״̬Ǩ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsResumeInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND״̬
              �յ�ID_LMM_MMC_RESUME_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_RESUME_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��12��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���
  3.��    ��   : 2014��4��28��
    ��    ��   : w00242748
    �޸�����   : DTS2014042808114:���H3G���γ�����L��ͬ����Ҫ����NV���ơ�
  4.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���

  5.��    ��   : 2014��7��18��
    ��    ��   : w00167002
    �޸�����   : DTS2014071701762:��L->Cʧ�ܴ�L�ָ�ʱ��û��ֹͣCMMCA RESUME IND
                 �Ķ�ʱ����������ʱ����ʱ���¸�λ��
  5.��    ��   : 2015��8��22��
    ��    ��   : m00312079
    �޸�����   : DTS2015081908397:��L->Cʧ�ܴ�L�ָ�ʱ��ֹͣTI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF��ʱ��
  6.��    ��   : 2015��11��05��
    ��    ��   : w00176964
    �޸�����   : DTS2015070910837:֪ͨMSCC��ϵͳ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;


    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))

    /* ֹͣTI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF);
#endif

#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))
    if (VOS_TRUE == NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg()))
    {
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CMMCA_RESUME_IND);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        NAS_MMC_SndMsccInterSysEndInd(VOS_RATMODE_LTE);
#endif
    }
#endif

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_LTE);
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

    /* ����L��RESUME_IND��Ϣ������CS,PSresume�������ʱ���ջָ��ɹ�����RESUME��Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_NET_RAT_TYPE_LTE ,&stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF״̬
              �յ�LMM��SUSPEND_REL_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCLMM_SUSPEND_REL_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��3��14��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ����Ҫ֪ͨMM/GMM�ָ���Ϣ
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ͣ�ȴ�LMM��SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, End */

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitLmmSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_Lmm_SUSPEND_REL_CNF״̬
              �յ�LMM��RESUME_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_RESUME_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��4��28��
    ��    ��   : w00242748
    �޸�����   : DTS2014042808114:���H3G���γ�����L��ͬ����Ҫ����NV���ơ�
  3.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �Գ峡�����������㷢��RRMM_SUSPEND_REL_REQ,���յ�������RRMM_RESUME_IND
       �ȴ���RRMM_RESUME_IND,�������յ�RRMM_SUSPEND_REL_CNF���� */

    RRMM_RESUME_IND_ST                  stResumeIndMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* ��ȡ�ɵ��������� */

    /* ͣ�ȴ�SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(enRatType);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);


    /* ����L��RESUME_IND��Ϣ������CS,PSresume�������ʱ���ջָ��ɹ�����RESUME��Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_NET_RAT_TYPE_LTE ,&stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF״̬
              �ȴ�LMM��SUSPEND_REL_CNF��Ϣ��ʱ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:�ȴ�LMM_MMC_SUSPEND_REL_CNF��ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitLSysInfoInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND״̬
              �յ�MMCMMC_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*ֹͣ������ʱ�� TI_NAS_MMC_WAIT_LMM_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendInfoChangeNotify_InterSysCellResel_WaitAsResumeInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND״̬
              �յ�LMM���͵��滻�����Ϣ�Ľӿ�
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��26��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��31��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:����RAT�仯��MM
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmSuspendInfoChangeNotify_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU *pstSuspendInfoChangeNotifyMsg;
    NAS_MMC_ENTRY_MSG_STRU                  *pstEntryMsg;
    LMM_MMC_SUSPEND_IND_STRU                *pstSuspendIndMsg;

    pstSuspendInfoChangeNotifyMsg   = (LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU*)pstMsg;


    if ( LMM_MMC_SUSPEND_RAT_INFO_CHANGE != pstSuspendInfoChangeNotifyMsg->ulInfoType)
    {
        return VOS_TRUE;
    }

    pstEntryMsg     = NAS_MMC_GetCurrEntryMsg();

    pstSuspendIndMsg = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

    if ( LMM_MMC_RAT_CHANGE_G2W == pstSuspendInfoChangeNotifyMsg->ulRatChangeType )
    {
        pstSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2W;

        /*���ͱ仯��Ϣ��mm*/
        NAS_MMC_SndMmRatChangeInd(NAS_MML_NET_RAT_TYPE_WCDMA);
    }
    else if ( LMM_MMC_RAT_CHANGE_W2G == pstSuspendInfoChangeNotifyMsg->ulRatChangeType )
    {
        pstSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2G;

        /*���ͱ仯��Ϣ��mm*/
        NAS_MMC_SndMmRatChangeInd(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        ;
    }
    return VOS_TRUE;
}


#endif

/* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
#if   (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCmmcaResumeInd_InterSysCellResel_WaitAsResumeInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND״̬
              �յ�CMMCA��RESUME_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_CMMCA_MMC_RESUME_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvCmmcaResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CMMCA_RESUME_IND);

    /* ��ѡ��CDMA�����õ�ǰ��3GPP�Ľ��뼼��ΪBUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* ��ѡ��CDMA�����õ�ǰδפ�� */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_HRPD);

    /* ��MM/GMM���͵�resume ind��Ϣ��ָʾ�ָ���ΪHRPD */
    stResumeIndMsg.ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucResumeOrigen   = MMC_RESUME_ORIGEN_HRPD;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitCmmcaResumeIndExpired_InterSysCellResel_WaitAsResumeInd
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND״̬
              �յ�TI_NAS_MMC_WAIT_CMMCA_RESUME_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_CMMCA_RESUME_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��3��11��
    ��    ��   : wx270776
    �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitCmmcaResumeIndExpired_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitCmmcaResumeIndExpired_InterSysCellResel_WaitAsResumeInd:ENTERED");

    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_CMMCA_RESUME_IND_EXPIRED);

    return VOS_TRUE;
}
#endif
/* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndSuspendRelReq_InterSysCellResel
 ��������  : ���ݲ�ͬ�Ľ��뼼������������LMM����SUSPEND_REL_REQ
 �������  : enRat
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��21��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

  1.��    ��   : 2014��3��13��
    ��    ��   : s00261364
    �޸�����   : ��ϵͳ��ѡ�������յ�detach req,֪ͨLTE suspendʱ,״̬Ǩ�ƴ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndSuspendRelReq_InterSysCellResel(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(VOS_TRUE);

    switch (enRat)
    {
       case NAS_MML_NET_RAT_TYPE_WCDMA :
            /* ��WRR����RRMM_SUSPEND_REL_REQ */
            NAS_MMC_SndAsSuspendRelReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WAS��SUSPEND_REL_CNF */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF);

            /* ����Ӧ�ı�����ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM :
            /* ��GAS����RRMM_SUSPEND_REL_REQ */
            NAS_MMC_SndAsSuspendRelReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS��SUSPEND_REL_CNF */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SUSPEND_REL_CNF);

            /* ����Ӧ�ı�����ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF_LEN);

            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE :
            /* ��LMM����RRMM_SUSPEND_REL_REQ */
            NAS_MMC_SndLmmSuspendRelReq();

            /* Modified by s00261364 for L-C��������Ŀ, 2014-3-13, begin */
            /* Ǩ��״̬���ȴ�LMM��SUSPEND_REL_CNF */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);

            /* ����Ӧ�ı�����ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);
            /* Modified by s00261364 for L-C��������Ŀ, 2014-3-13, end */

            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendRelReq_InterSysCellResel: Rat not support.");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel
 ��������  : ���ݲ�ͬ�Ľ��뼼������������LMM����SUSPEND_REL_REQ
 �������  : enRat
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��21��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��5��20��
    ��    ��   : z00161729
    �޸�����   : DTS201405090133:��lnas suspend rel req��gu resume ind��Ϣ�Գ�ʱmmcδ�����浼�º�����״̬��������������λ
*****************************************************************************/
VOS_VOID NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
       case NAS_MML_NET_RAT_TYPE_WCDMA :

            /* ͣWAS�ı�����ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM :

            /* ͣGAS�ı�����ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF);

            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE :
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel: Rat not support.");
            break;
    }

    return;
}


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))


VOS_UINT32 NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ֹͣTI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF);

    /* ��ѡ���ض���CDMA�����õ�ǰ��3GPP�Ľ��뼼��ΪBUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* ��ѡ���ض���CDMA�����õ�ǰδפ�� */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_HRPD);

    /* ��MM/GMM���͵�resume ind��Ϣ��ָʾ�ָ���ΪHRPD */
    stResumeIndMsg.ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucResumeOrigen   = MMC_RESUME_ORIGEN_HRPD;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvTiWaitMsccInterSysHrpdNtfExpired_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMsccInterSysHrpdNtfExpired_InterSysCellResel_WaitAsResumeInd:ENTERED");

    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_EXPIRED);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF״̬
              �յ�MSCC����ϵͳ�任��HRPD��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_INTERSYS_HRPD_NTF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��5��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �Գ峡�����������㷢��MMC_LMM_SUSPEND_REL_REQ,���յ�MSCC����ϵͳ�任��HRPD��ָʾ,
       ��ʱLTE��Ϊ��ģ,��suspend relȷ�ϻظ�,����HRPD�󵱳�HRPD�Ļָ����̴��� */

    RRMM_RESUME_IND_ST                  stResumeIndMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* ͣ�ȴ�SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(enRatType);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* ��ѡ���ض���CDMA�����õ�ǰδפ�� */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_HRPD);

    /* ��MM/GMM���͵�resume ind��Ϣ��ָʾ�ָ���ΪHRPD */
    stResumeIndMsg.ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucResumeOrigen   = MMC_RESUME_ORIGEN_HRPD;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


#endif

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
Function Name   :   NAS_MMC_RcvLmmResumeInd_InterSysCellResel_Init
Description     :   CL mode,HRPD Reselct LTE, MMC Recive LMM_MMC_RESUME_IND��wait LMM_MMC_SYSINFO_INF_IND
Input parameters:   ulEventType: the Event type
                :   pstMsg     : the LMM_MMC_RESUME_IND message
Outout parameters:  None
Return Value    :
Modify History:
    1)  Date    :   2015-06-06
        Author  :   l00324781
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��LMM������Ӧ��Ϣ */
    NAS_MMC_SndLmmResumeNotify();

    /* ��״̬Ǩ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

    return VOS_TRUE;
}
#endif


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


