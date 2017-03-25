/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcFsmInterSysOos.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2011��07��27��
  ����޸�   :
  ��������   : �������ѡʱ������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��07��27��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

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
#include "NasMmcFsmInterSysOos.h"
#include "NasMmcFsmInterSysOosTbl.h"
#include "NasMmcFsmInterSysOos.h"
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

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_OOS_C
/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasSuspendInd_InterSysOos_Init
 ��������  : ��intersysoos��INIT״̬,�յ�was��RRMM_SUSPEND_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SUSPEND_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��06��01��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysOos_Init(
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
    NAS_MMC_SetSuspendRspFlag_InterSysOos(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysOos(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmSuspendRsp_InterSysOos_WaitMmSuspendRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_InterSysOos_RSP״̬
              �յ�MMCGMM_Suspend_RSP��Ϣ�Ĵ���
 �������  :ulEventType:��Ϣ����
            pstmsg:MMCMM_Suspend_RSP��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��04��24��
    ��    ��   : j00174725
    �޸�����   : DSDS(������޸Ķ�ʱ������) DTS2015042702414
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysOos_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ������յ�GMM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysOos( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsOosResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmSuspendRsp_InterSysOos_WaitMmSuspendRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_InterSysOos_RSP״̬
              �յ�MMCMM_Suspend_RSP��Ϣ�Ĵ���
 �������  :ulEventType:��Ϣ����
            pstmsg:MMCMM_Suspend_RSP��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��04��24��
    ��    ��   : j00174725
    �޸�����   : DSDS(������޸Ķ�ʱ������) DTS2015042702414
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysOos_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ������յ�MM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysOos( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP�����ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsOosResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysOos_WaitMmSuspendRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_InterSysOos_RSP״̬
              �յ�TI_NAS_MMC_WAIT_MM_Suspend_RSP_TIMER��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_MM_Suspend_RSP_TIMER��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysOos_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysOos_WaitMmSuspendRsp:ENTERED");

    /* ������ظ�����ʧ�� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasResumeInd_InterSysOos_WaitAsResumeInd
 ��������  : MMC��NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND״̬
              �յ�WAS:RRMM_RESUME_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_RESUME_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��11��
    ��    ��   : z40661
    �޸�����   : DTS2012090505066:��ϵͳ�����ź������ϱ�����ȷ
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysOos_WaitAsResumeInd
 ��������  : MMC��NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND״̬
              �յ�TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_AS_RESUME_IND_TIMER��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011120702166:MMC��λ���޸�λ��Ϣ,��MMLģ���װ��λ��Ϣ��
                  �Թ�MM����ã�������λ��
  3.��    ��   : 2014��2��18��
    ��    ��  :  w00242748
    �޸�����  :  DTS2014021803515:��λʱ��ȷ���յ��ĸ����뼼�����쳣��Ϣ���µġ�

  4.��    ��   : 2015��3��11��
    ��    ��   : wx270776
    �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysOos_WaitAsResumeInd:ENTERED");

    /* ����om�ӿ�,�ϵ縴λ */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_GAS_WAIT_RESUME_IND_EXPIRED);
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
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitAsResumeInd
 ��������  : ��NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_INDʱ,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣTI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    /* ��ǰAS���� RRMM_SUSPEND_REL_REQ */
    if ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndAsSuspendRelReq(WUEPS_PID_WRR);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitAsResumeInd:could not support current rat!");

        return VOS_FALSE;
    }

    /* Ǩ��״̬���ȴ�SUSPEND_REL_CNF */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitAsResumeInd
 ��������  : ��NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_INDʱ,�յ�RRMM_REL_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��29��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��23��
    ��    ��   : l00130025
    �޸�����   : DTS2012031604090,�յ�WRR��Rel_indʱû������RAT�����»ָ�ResumeRsp����
  3.��    ��   : 2012��6��18��
    ��    ��   : l00171473
    �޸�����   : DTS2012051104124, �����ж�ԭ��ֵ���յ�rel ind����Ϊ���̽�����
                 ����WAS�ָ�������ͬWAS������resume ind
  4.��    ��   : 2012��6��20��
    ��    ��   : l00171473
    �޸�����   : DTS2012062002706, OOS״̬���յ�REL INDʱ��ֹͣ������ʱ��

  5.��    ��   : 2012��9��11��
    ��    ��   : z40661
    �޸�����   : DTS2012090505066:��ϵͳ�����ź������ϱ�����ȷ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �����ж�ԭ��ֵ */


    /* ֹͣTI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ����RESUME��Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_GMM_RESUME_RSP_FLG);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf
 ��������  : NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF״̬�´����յ�WAS���͵�suspend_rel_cnf��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:�յ�WAS���͵�suspend_rel_cnf��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��04��07��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:DTS2012040106098,����CoverageLost��service���ϱ�˳���Ը���MMA��״̬��DeepSleep
  3.��    ��   : 2013��07��23��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��:DTS2013071809030,�յ�����Ϣ��û�����̴���SYSCFG,����SYSCFG����ʱ��ϳ�
  4.��    ��   : 2014��5��31��
    ��    ��   : y00245242
    �޸�����   : �޸ķ���״̬�ϱ�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */
    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /* ���ݽӿ�Լ��,��WRR����RRMM_SUSPEND_REL_CNFʱ,�Ѿ�������IDLE,����WRR������MM/GMM���������ͷ�ָʾ,
       ����MMC��Ҫ����������ӱ�־ */
    NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf
 ��������  : NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF״̬�´����յ�WAS���͵�suspend_rel_cnf��ʱ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:�յ�WAS���͵�suspend_rel_cnf��ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��04��07��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:DTS2012040106098,����CoverageLost��service���ϱ�˳���Ը���MMA��״̬��DeepSleep
  3.��    ��   : 2014��5��31��
    ��    ��   : y00245242
    �޸�����   : �޸ķ���״̬�ϱ�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf:ENTERED");

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */
    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasResumeInd_InterSysOos_WaitWasSuspendRelCnf
 ��������  : MMC��NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF״̬
              �յ�WAS:RRMM_RESUME_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_RESUME_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��16��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �Գ峡���Ĵ����ո�����㷢��RRMM_SUSPEND_REL_REQ���յ�������RRMM_RESUME_IND
       �����յ�RRMM_RESUME_IND��Ϣ���������յ�RRMM_SUSPEND_REL_CNF���� */

    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmResumeRsp_InterSysOos_WaitMmResumeRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP״̬
              �յ�MMCGMM_RESUME_RSP��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCGMM_RESUME_RSP��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��15��
    ��    ��   : z00161729
    �޸�����   : DTS2013062406563:WAS����̬OOS,T305�����ڼ�ֻ���ڱ�ϵͳ���ѵ�Чplmn��
                 ����פ������ϵͳ�������磬Ҳ������ϵͳ�½��������������޷��ܿ�����������ע�ᣬnas����޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysOos_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_ClearResumeRspFlag_InterSysOos( NAS_MMC_GMM_RESUME_RSP_FLG );

    /* δ����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣMMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmResumeRsp_InterSysOos_WaitMmResumeRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP״̬
              �յ�MMCMM_RESUME_RSP��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMM_RESUME_RSP��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��cerssi��nmr
  3.��    ��   : 2013��7��15��
    ��    ��   : z00161729
    �޸�����   : DTS2013062406563:WAS����̬OOS,T305�����ڼ�ֻ���ڱ�ϵͳ���ѵ�Чplmn��
                 ����פ������ϵͳ�������磬Ҳ������ϵͳ�½��������������޷��ܿ�����������ע�ᣬnas����޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysOos_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_ClearResumeRspFlag_InterSysOos( NAS_MMC_MM_RESUME_RSP_FLG );

    /* δ����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣMMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysOos_WaitMmResumeRsp
 ��������  : MMC��NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP״̬
              �յ�TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_MM_RESUME_RSP_TIMER��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��15��
    ��    ��   : z00161729
    �޸�����   : DTS2013062406563:WAS����̬OOS,T305�����ڼ�ֻ���ڱ�ϵͳ���ѵ�Чplmn��
                 ����פ������ϵͳ�������磬Ҳ������ϵͳ�½��������������޷��ܿ�����������ע�ᣬnas����޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysOos_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysOos_WaitMmResumeRsp:ENTERED");

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/* oos״̬�������е�ϵͳ��Ϣ״̬��ɾ��g_astNasInterSysOosWaitWSysInfoIndActTbl��
   �յ�resume ind��Ϣ����״̬�� */

/* NAS_MMC_UpdateSearchedPlmnListInfo_Oos����list��bg������״̬������Ҫʹ������NasMmcCommFunc.c */

/* oos״̬�������е�ϵͳ��Ϣ״̬��ɾ��NAS_MMC_RcvWasSuspendInd_InterSysOos_WaitWasSysInfoInd/
   NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitWasSysInfoInd�յ�resume ind��Ϣ����״̬�� */


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitWasSysInfoInd
 ��������  : ��NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SYSINFO_INDʱ,�յ�RRMM_REL_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��05��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��18��
    ��    ��   : l00171473
    �޸�����   : DTS2012051104124, �����ж�ԭ��ֵ���յ�rel ind����Ϊ���̽�����
                 ����WAS�ָ�������ͬWAS������SUSPEND REL CNF.
  3.��    ��   : 2012��6��20��
    ��    ��   : l00171473
    �޸�����   : DTS2012062002706, OOS״̬���յ�REL INDʱ��ֹͣ������ʱ��
  4.��    ��   : 2014��5��31��
    ��    ��   : y00245242
    �޸�����   : �޸ķ���״̬�ϱ�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �����ж�ԭ��ֵ */


    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);
    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, begin */
    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-31, end */

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

