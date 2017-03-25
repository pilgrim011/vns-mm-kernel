/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NASUTRANCTRLFSMPLMNSELECTION.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2012��7��12��
  ����޸�   :
  ��������   : ����״̬�������ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��8��4��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasComm.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasUtranCtrlFsmMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlProcNvim.h"
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlFsmPlmnSelectionTbl.h"
#include "NasMmlLib.h"
#include "NasMmcComFunc.h"

#include "NasMmcFsmPlmnSelection.h"

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "NasDynLoadApi.h"
#include "NasDynLoad.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_PLMN_SELECTION_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvWasPlmnSrchCnf_PlmnSelection_Init
 ��������  : ����״̬����ʼ��״̬�յ�WAS�����ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasPlmnSrchCnf_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* W������ʧ����Ҫ��TD�¼������� ����WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_Init
 ��������  : ����״̬����ʼ��״̬�յ�MMC����������WAS��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��5��18��
   ��    ��   : b00269685
   �޸�����   : ����ֹͣW�����Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF))
    {
        /* ͣ��ʱ�� */
        NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

        /* ��WAS����ֹͣ�������� */
        NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�wasֹͣ�����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

        return VOS_TRUE;
    }

    /* W������ʧ����Ҫ��TD�¼������� ����WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_PlmnSelection_Init
 ��������  : ����״̬����ʼ��״̬�յ�MMC����������tds��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* tds������ʧ����Ҫ��w�¼������� ����tds */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_Init
 ��������  : �յ�WAS��ָ�������ظ���ʱ��Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:�����ظ���ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��22��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:�����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��WAS����ֹͣ�������� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�ֹͣW������ȥTD������״̬ */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF_SEARCH_TD);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvWasRrMmRelInd_PlmnSelection_Init
 ��������  : ����ʱ�յ�WAS�Ľ���㸴λ��Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:�����ظ���ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��22��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:�����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvWasRrMmRelInd_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �������������Ϣ���浽״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* W������ʧ����Ҫ��TD�¼������� ����WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;

}



/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTdPlmnSrchCnf_PlmnSelection_Init
 ��������  : ����״̬����ʼ��״̬�յ�TD�����ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTdPlmnSrchCnf_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* TD������ʧ�ܸ���Я���������б�Ϊ�յ���������˳���ǰ��������,
       ������Ҫ����TD��W������ */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TD����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_Init
 ��������  : �յ�WAS��ָ�������ظ���ʱ��Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:�����ظ���ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��22��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:�����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��TD����ֹͣ�������� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�ֹͣTD������ȥW������״̬ */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF_SEARCH_W);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;

}



/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 ��������  : �ȴ�WASֹͣ����ȥ��TD�ظ��������յ�ֹͣ�����ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��28��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    /* �յ���MMC���״̬����Ϣ����ص�SUSPEND״̬�˳�UTRANCTRLѡ������ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD WITH MMC ABORT");

        /* �����ǰ��MMC�Ĵ�ϣ���ǰ��Ҫ��������ǰģ�������� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�WAS����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

        /* ������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* �����ǰ�����ڴ�ϣ���ǰ��Ҫ��������ǰģ�������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 ��������  : �ȴ�WASֹͣ����ȥ��TD�ظ��������յ������ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��6��25��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg     = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD WITH MMC ABORT");

        /* �����ǰ��MMC�Ĵ�ϣ���ǰ��Ҫ��������ǰ���ڹ���״̬MMC�ظ���� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�WAS����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

        /* ������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* �����ȴ�ѡ��STOP CNF,������ǰ�����ظ� */
        return VOS_TRUE;
    }

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪFDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* �����ǰ�����ڴ�ϣ���ǰ��Ҫ��������ǰģ�������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 ��������  : �ȴ�WASֹͣ�����ظ��������յ�RRMM_REL_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��28��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2014��6��12��
   ��    ��   : w00167002
   �޸�����   : WAS�쳣�ҵ�ǰΪNO RF,�����MMC���д���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg  = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD: ENTERED");

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    /* �յ���MMC���״̬����Ϣ����ص�SUSPEND״̬�˳�UTRANCTRLѡ������ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD WITH MMC ABORT");

        /* �����ǰ��MMC�Ĵ�ϣ���ǰ��Ҫ��������ǰģ�������� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�WAS����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

        /* ������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }


    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪFDDģʽ */
    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ������ʧ����Ϣ����MMC���� */
        return VOS_FALSE;
    }

    /* W������ʧ����Ҫ��TD�¼������� ����WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 ��������  : �ȴ�WASֹͣ����ȥ��TD�ظ��������յ��û�������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��28��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 ��������  : �ȴ�WASֹͣ������TD״̬�յ����MMCѡ��״̬����Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���:��W������ʧ�ܣ���UTRANCTRLѡ��TD����ʱ���յ���һ�׶ζ�
                ʱ����ʱ����Ϣ���������ѡ��״̬������ǰMMC��W��STOP REQ���󣬶�����
                ��TD��STOP������������MMC����������Lte,����˫��ģ�쳣��λ. ����Ϣ���ѡ��״̬��ʱ��
                ��Ҫ���˳�UTRANCTRLѡ�����̣��ٴ��MMCѡ��״̬������ʱ���MMC�յ�
                ����ʧ����Ϣʱ���Ѿ��˳�ѡ��״̬�������ܽ�������״̬������ANYCELL
                ����״̬������ʱUTRAN�����ABORT��Ϣ�ɶ������ô���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ����MMC���״̬����� */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD
 ��������  : �ȴ�WASֹͣ�����ظ��������յ�ֹͣ�����ظ���ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��28��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD: ENTERED");

    /* �յ���MMC���״̬����Ϣ����ص�SUSPEND״̬�˳�UTRANCTRLѡ������ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD WITH MMC ABORT");

        /* �����ǰ��MMC�Ĵ�ϣ���ǰ��Ҫ��������ǰģ�������� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�WAS����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

        /* ������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ������ʧ����Ϣ����MMC���� */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�TD��,��WAS���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�was����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW
 ��������  : �ȴ�TDֹͣ����ȥ��TD�ظ��������յ�ֹͣ�����ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��28��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);


    /* �յ���MMC���״̬����Ϣ�����˳�UTRANCTRLѡ�����̣�֪ͨMMC�˳�ѡ������ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW WITH MMC ABORT");

        /* �����ǰ�����ڴ�ϣ���ǰ��Ҫ��������ǰģ�������� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* Ǩ��״̬���ȵ�TD����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

        /* ������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* ��Ϣ������� */
        return VOS_TRUE;
    }

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* �����ǰ�����ڴ�ϣ���ǰ��Ҫ��������ǰģ�������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TD����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW
 ��������  : �ȴ�TDֹͣ����ȥ��TD�ظ��������յ������ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��6��25��
   ��    ��   : b00269685
   �޸�����   : DSDS III�����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg     = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    pstSrchCnfMsg     = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW WITH MMC ABORT");

        /* ����ǰģ��֪ͨMMC�����Ϣ */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* Ǩ��״̬���ȵ�TD����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

        /* ������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* �����ȴ�ѡ��STOP CNF,������ǰ�����ظ� */
        return VOS_TRUE;
    }

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC�������õ�ǰΪTDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* �����ǰ�����ڴ�ϣ���ǰ��Ҫ��������ǰģ�������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TD����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW
 ��������  : �ȴ�TDֹͣ����ȥ��TD�ظ��������յ��û�������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��28��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW
 ��������  : �ȴ�TDֹͣ������W״̬�յ����MMCѡ��״̬����Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���:��W������ʧ�ܣ���UTRANCTRLѡ��TD����ʱ���յ���һ�׶ζ�
                ʱ����ʱ����Ϣ���������ѡ��״̬������ǰMMC��W��STOP REQ���󣬶�����
                ��TD��STOP������������MMC����������Lte,����˫��ģ�쳣��λ. ����Ϣ���ѡ��״̬��ʱ��
                ��Ҫ���˳�UTRANCTRLѡ�����̣��ٴ��MMCѡ��״̬����
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* �����յ�MMC���ѡ��״̬����Ϣ��� */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW
 ��������  : �ȴ�TDֹͣ�����ظ��������յ�ֹͣ�����ظ���ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��28��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;


    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW: ENTERED");


    /* �յ���MMC���״̬����Ϣ�����˳�UTRANCTRLѡ�����̣�֪ͨMMC�˳�ѡ������ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW WITH MMC ABORT");

        /* �����ǰ�����ڴ�ϣ���ǰ��Ҫ��������ǰģ�������� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* Ǩ��״̬���ȵ�TD����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

        /* ������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* ��Ϣ������� */
        return VOS_TRUE;
    }

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ������ʧ����Ϣ����MMC���� */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�w������,��TD���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TD����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf
 ��������  : �յ�suspend cnf��ʱ���Ƿ���Ҫ���������ظ���Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ
             VOS_TRUE:��Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��23��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf()
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (pstEntryMsg->ulEventType == NAS_UTRANCTRL_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_SKIP_SEARCH_W_IND))
    {
        return VOS_TRUE;
    }

    if (pstEntryMsg->ulEventType == NAS_UTRANCTRL_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_SKIP_SEARCH_TDS_IND))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnf
 ��������  : �ȴ�WAS����ظ�״̬�յ�WAS����ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��2��11��
   ��    ��   : w00167002
   �޸�����   : ��������W���.
                ע:SVLTE�����ߣ���W������NO RF����G�������ɹ�����פ���ɹ���
                �����ٷ�������ʱ������WAS,����G�ᶪ��������UTRANCTRL״̬��ʱ��
                ��NO RFʱ��ǰ��FDDģʽ�ģ����MMC�ٷ�������ʱ�򣬻��ȸ�WAS���ͣ�
                UTRAN����SKIP W��Ϣ����UTRANCTRL״̬������TDD.
 3.��    ��   : 2015��8��26��
   ��    ��   : w00242748
   �޸�����   : ��̬������Ŀ

 4.��    ��   : 2015��12��17��
   ��    ��   : w00167002
   �޸�����   : ��W������ʧ�ܣ���UTRANCTRLѡ��TD����ʱ���յ���һ�׶ζ�
                ʱ����ʱ����Ϣ���������ѡ��״̬������ǰMMCѡ��״̬����W��STOP REQ���󣬶�����
                ��TD��STOP������������MMC����������Lte,����˫��ģ�쳣��λ. ����Ϣ���ѡ��״̬��ʱ��
                ��Ҫ���˳�UTRANCTRLѡ�����̣��ٴ��MMCѡ��״̬������ʱMMC�յ�ѡ��״̬����MMC���͵�
                abort��Ϣ��ϣ�����˳�ѡ��״̬����
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* ���帴λ */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF);


    /* �յ���MMC���״̬����Ϣ�����˳�UTRANCTRLѡ�����̣�֪ͨMMC�˳�ѡ������ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnf WITH MMC ABORT");

        NAS_UTRANCTRL_BuildInterUtranCtrlPlmnSelectionAbortFinishIndMsg((NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ״̬����ϱ�ǲ����� */
    if (VOS_FALSE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, VOS_RATMODE_TDS);
        }
#endif

        /* ��TDRRC����ָ���������� */
        NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq(TPS_PID_RRC);

        /* Ǩ��״̬���ȵ�TDRRC�����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_SEARCH_CNF);

        /* ������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF_LEN);

        /* ��Ϣ������ɲ����������MMC״̬������ */
        return VOS_TRUE;
    }

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();



    /* �����ǰ�������ϢΪ��ʱ����ʱ,����MMC���͵��ڲ�SKIP ����W��Ϣ������Ҫ���������ظ�ʧ����Ϣ */
    if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {

        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* ȡ�����״̬�������ظ�ʧ����Ϣ��MMCģ�� */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �л���MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf
 ��������  : �ȴ�WAS����ظ�״̬�յ��û�������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasSuspendCnf
 ��������  : �ȴ�WAS����ظ�״̬�յ����MMCѡ��״̬����Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��16��
   ��    ��   : w00167002
   �޸�����   : ��W������ʧ�ܣ���UTRANCTRLѡ��TD����ʱ���յ���һ�׶ζ�
                ʱ����ʱ����Ϣ���������ѡ��״̬������ǰMMCѡ��״̬����W��STOP REQ���󣬶�����
                ��TD��STOP������������MMC����������Lte,����˫��ģ�쳣��λ. ����Ϣ���ѡ��״̬��ʱ��
                ��Ҫ���˳�UTRANCTRLѡ�����̣��ٴ��MMCѡ��״̬������ʱMMC�յ�ѡ��״̬����MMC���͵�
                abort��Ϣ��ϣ�����˳�ѡ��״̬����
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ���ѡ��״̬����Ϣ */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnf
 ��������  : �ȴ�WAS����ظ�״̬suspend CNF�����б�����ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnf: ENTERED");

    /* ��λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnf
 ��������  : �ȴ�TD����ظ�״̬�յ�TDRRC����ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��10��31��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
 3.��    ��   : 2015��8��26��
   ��    ��   : w00242748
   �޸�����   : ��̬������Ŀ
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();
    pstRrmmSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* ���帴λ */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF);


    /* �յ���MMC���״̬����Ϣ�����˳�UTRANCTRLѡ�����̣�֪ͨMMC�˳�ѡ������ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnf WITH MMC ABORT");

        NAS_UTRANCTRL_BuildInterUtranCtrlPlmnSelectionAbortFinishIndMsg((NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ״̬����ϱ�ǲ����� */
    if (VOS_FALSE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
        {
            (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, VOS_RATMODE_WCDMA);
        }
#endif
        /* ��WAS����ָ���������� */
        NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�WAS�����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF);

        /* ������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* �����ǰ�������ϢΪ��ʱ����ʱ������MMC���͵��ڲ�SKIP ����TDS��Ϣ,����Ҫ���������ظ�ʧ����Ϣ */
    if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* ȡ�����״̬�������ظ�ʧ����Ϣ��MMCģ�� */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �л���MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf
 ��������  : �ȴ�TD����ظ�״̬�յ��û�������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdSuspendCnf
 ��������  : �ȴ�TD����ظ�״̬�յ����MMCѡ��״̬����Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���:���յ�SUSPEND CNF�󣬸�MMC���ʹ��UTRANCTRL�����Ϣ��
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���ý��յ�MMC���״̬����Ϣ��־ */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnf
 ��������  : �ȴ�TD����ظ�״̬suspend CNF�����б�����ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnf: ENTERED");

    /* ��λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS�����ظ��������յ�WAS�����ظ��Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��1��20��
   ��    ��   : w00167002
   �޸�����   : SVLTE��������Ŀ:��W������ʧ��ΪNO RF����ʾ��ǰ������Դ�����ã�
                ����Ҫ����TD��ֱ�ӽ���MMC״̬�����д�����ǰ����FDDģʽ��
 3.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ��������ɹ� */
    if ((RRC_PLMN_SEARCH_RLT_SPEC           == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC   == pstSrchCnfMsg->ulSearchRlt))
    {
        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }


    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC�������õ�ǰΪFDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* ���������б�����й������� */
    if (MMCMMC_INTER_SKIP_SEARCH_TDS_IND != pstMsgHeader->ulMsgName)
    {
        NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                 NAS_UTRANCTRL_GetSpecTdMccList(),
                                                 &(pstSrchCnfMsg->PlmnIdList));

        /* �����й�����������utran����ģʽ */
        if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
        {
            NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
        }
        else if ((0 != pstSrchCnfMsg->PlmnIdList.ulHighPlmnNum)
              || (0 != pstSrchCnfMsg->PlmnIdList.ulLowPlmnNum))
        {
            /* δ�ѵ��й����粢��WЯ���ǿ��б�,���¹���ģʽΪFDD */
            NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);
        }
        else
        {
            /* WЯ�����б��޸Ĺ���ģʽ */
        }
    }

    /* ���ݵ�ǰ����ģʽΪTDD����Ҫ�ص�TD�� */
    if (NAS_UTRANCTRL_UTRAN_MODE_TDD   == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȴ���TDʱW�Ĺ���ظ�״̬ */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }

    /* ״̬���л���MAIN */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS�����ظ��������յ�inter abort plmn search req�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��13��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ����utran modeΪfdd��utranctrl ����״̬���˳�����Ϣ��mmc��������֪ͨ���������mmc���� */
    NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

    /* ֪ͨmmc MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF*/
    NAS_MMC_SndInterAbortUtranCtrlPlmnSearchCnfMsg();

    /* ״̬���л���MAIN */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    return VOS_TRUE;
}





/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : ��Wģʱ���յ�TD����������ظ���Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_PLMN_SEARCH_CNF��Ϣ�Ľṹ����ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:�����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS�����ظ��������յ�RRMM_REL_IND�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2014��6��12��
   ��    ��   : w00167002
   �޸�����   : WAS�쳣��NO RF,ֱ�ӽ�MMC״̬�����д���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnSearchCnf: ENTERED");

    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);


    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪFDDģʽ */
    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ǰδ�ѵ��й�������,����Ϊ��Ȼ��TD��,ģʽ���ֲ��� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȴ���TDʱW�Ĺ���ظ�״̬ */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS�����ظ�״̬�յ��û�������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��WAS����ֹͣ�������� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS����ظ�״̬�յ����MMCѡ��״̬����Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���:��W������ʧ�ܣ���UTRANCTRLѡ��TD����ʱ���յ���һ�׶ζ�
                ʱ����ʱ����Ϣ���������ѡ��״̬������ǰMMC��W��STOP REQ���󣬶�����
                ��TD��STOP������������MMC����������Lte,����˫��ģ�쳣��λ. ����Ϣ���ѡ��״̬��ʱ��
                ��Ҫ���˳�UTRANCTRLѡ�����̣��ٴ��MMCѡ��״̬����
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnSearchCnf WITH MMC ABORT");

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ����״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���ô�� */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* ��WAS����ֹͣ�������� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS�����ظ������еȴ�WAS�����ظ���ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf: ENTERED");

    /* ֹͣWAS���� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WASֹͣ�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS�����ظ������еȴ�WAS�����ظ���ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��18��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ͣ��ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ֹͣWAS���� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WASֹͣ�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf
 ��������  : �ȴ�TD�����ظ��������յ�TDRRC�����ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��6��12��
   ��    ��   : w00167002
   �޸�����   : DSDS III:��NO RF���MMC����
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);

    /* ���ָ�������ɹ���history�ѳɹ� */
    if ((RRC_PLMN_SEARCH_RLT_SPEC           == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC   == pstSrchCnfMsg->ulSearchRlt))
    {
        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }


    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪTDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* ���������б�����й������� */
    NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                             NAS_UTRANCTRL_GetSpecTdMccList(),
                                             &(pstSrchCnfMsg->PlmnIdList));

    /* �����й�����������utran����ģʽ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
    }

    /* ���ݵ�ǰ����ģʽΪFDD����Ҫ�ص�W�� */
    if (NAS_UTRANCTRL_UTRAN_MODE_FDD   == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        /* ����TD */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* Ǩ��״̬���ȴ���WʱTD�Ĺ���ظ�״̬ */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }

    /* ״̬���л���MAIN */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvWasPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf
 ��������  : ��TDģʱ���յ�WAS����������ظ���Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_PLMN_SEARCH_CNF��Ϣ�Ľṹ����ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:�����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_UTRANCTRL_RcvWasPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf
 ��������  : �ȴ�td�����ظ�״̬�յ��û�������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��TDRRC����ֹͣ�������� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDRRCֹͣ�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnSearchCnf
 ��������  : �ȴ�TDRRC�����ظ�״̬�յ����MMCѡ��״̬����Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���:��W������ʧ�ܣ���UTRANCTRLѡ��TD����ʱ���յ���һ�׶ζ�
                ʱ����ʱ����Ϣ���������ѡ��״̬������ǰMMC��W��STOP REQ���󣬶�����
                ��TD��STOP������������MMC����������Lte,����˫��ģ�쳣��λ. ����Ϣ���ѡ��״̬��ʱ��
                ��Ҫ���˳�UTRANCTRLѡ�����̣��ٴ��MMCѡ��״̬������ʱ���MMC�յ�
                ����ʧ����Ϣʱ���Ѿ��˳�ѡ��״̬�������ܽ�������״̬������ANYCELL
                ����״̬������ʱUTRAN�����ABORT��Ϣ�ɶ������ô���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnSearchCnf WITH MMC ABORT");

    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);

    /* ���ü�¼��ϱ�־ */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* ��TDRRC����ֹͣ�������� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDRRCֹͣ�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_WaitTdPlmnSearchCnf
 ��������  : �ȴ�TD�����ظ������г�ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_WaitTdPlmnSearchCnf: ENTERED");

    /* ֹͣTDRRC���� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDRRCֹͣ�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �ȴ�WASֹͣ�����ظ��������յ�ֹͣ�����ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnf WITH MMC ABORT");

        /* ��ʱǨ�Ƶ�����״̬��MMC�ظ���Ͻ�� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�was����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        return VOS_TRUE;
    }

    if ((VOS_FALSE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
     && (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_TDS_IND == pstMsgHeader->ulMsgName))
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    if ((WUEPS_PID_MMC == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName))
    {
        /* ��ʱ��Ҫ�ص�TD��,��WAS���͹������� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�was����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }


    /* ��ʱ��Ҫ�ص�TD��,��WAS���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�was����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �ȴ�WASֹͣ�����ظ��������յ������ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��6��25��
   ��    ��   : b00269685
   �޸�����   : DSDS III�����ɺ���
 2.��    ��   : 2014��12��8��
   ��    ��   : b00269685
   �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf WITH MMC ABORT");

        /* ��ʱǨ�Ƶ�����״̬��MMC�ظ���Ͻ�� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�was����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪFDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    if ((VOS_FALSE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
     && (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_TDS_IND == pstMsgHeader->ulMsgName))
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�TD��,��WAS���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�was����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �ȴ�WASֹͣ�����ظ��������յ�plmn search info ind�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��23��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : ��Wģʱ���յ�TD����������ظ���Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_PLMN_SEARCH_CNF��Ϣ�Ľṹ����ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:�����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �ȴ�WASֹͣ�����ظ��������յ��û�������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �ȴ�WASֹͣ�����ظ�״̬�յ����MMCѡ��״̬����Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���:��W������ʧ�ܣ���UTRANCTRLѡ��TD����ʱ���յ���һ�׶ζ�
                ʱ����ʱ����Ϣ���������ѡ��״̬������ǰMMC��W��STOP REQ���󣬶�����
                ��TD��STOP������������MMC����������Lte,����˫��ģ�쳣��λ. ����Ϣ���ѡ��״̬��ʱ��
                ��Ҫ���˳�UTRANCTRLѡ�����̣��ٴ��MMCѡ��״̬����
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ���ѡ��״̬����Ϣ */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �ȴ�WASֹͣ�����ظ��������յ�ֹͣ�����ظ���ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf: ENTERED");

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf WITH MMC ABORT");

        /* ��ʱǨ�Ƶ�����״̬��MMC�ظ���Ͻ�� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�was����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        return VOS_TRUE;
    }

    if ((VOS_FALSE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
     && (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_TDS_IND == pstMsgHeader->ulMsgName))
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�TD��,��WAS���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�was����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf
 ��������  : �ȴ�WASֹͣ�����ظ��������յ�ֹͣ�����ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��2��11��
    ��    ��   : w00167002
    �޸�����   : ��������W���.
                 ע:SVLTE�����ߣ���W������NO RF����G�������ɹ�����פ���ɹ���
                 �����ٷ�������ʱ������WAS,����G�ᶪ��������UTRANCTRL״̬��ʱ��
                 ��NO RFʱ��ǰ��FDDģʽ�ģ����MMC�ٷ�������ʱ�򣬻��ȸ�WAS���ͣ�
                 UTRAN����SKIP W��Ϣ����UTRANCTRL״̬������TDD.
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;


    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);


    /* �յ���MMC���״̬����Ϣ����ص�SUSPEND״̬�˳�UTRANCTRLѡ������ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf WITH MMC ABORT");

        /* ��ʱ��Ҫ�ص�W��,��TDRRC���͹������� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* Ǩ��״̬���ȵ�TDRRC����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }

    /* �й������Ǵ������˳���ǰ״̬�� */
    if ( (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
      || ( (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
        && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName) ) )
    {

        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�W��,��TDRRC���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDRRC����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnf
 ��������  : �ȴ�WASֹͣ�����ظ��������յ������ظ���Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��6��25��
   ��    ��   : b00269685
   �޸�����   : DSDS III�����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;


    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);

    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnf WITH MMC ABORT");

        /* ��ʱ��Ҫ�ص�W��,��TDRRC���͹������� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* Ǩ��״̬���ȵ�TDRRC����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        return VOS_TRUE;
    }

    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪTDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* �й������Ǵ������˳���ǰ״̬�� */
    if ( (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
      || ( (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
        && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName) ) )
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�W��,��TDRRC���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDRRC����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvWasPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf
 ��������  : ��TDģʱ���յ�WAS����������ظ���Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_PLMN_SEARCH_CNF��Ϣ�Ľṹ����ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��7��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:�����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_UTRANCTRL_RcvWasPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf
 ��������  : �ȴ�TDֹͣ�����ظ��������յ��û�������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnf
 ��������  : �ȴ�TDֹͣ�����ظ�״̬�յ����MMCѡ��״̬����Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��16��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���:��W������ʧ�ܣ���UTRANCTRLѡ��TD����ʱ���յ���һ�׶ζ�
                ʱ����ʱ����Ϣ���������ѡ��״̬������ǰMMC��W��STOP REQ���󣬶�����
                ��TD��STOP������������MMC����������Lte,����˫��ģ�쳣��λ. ����Ϣ���ѡ��״̬��ʱ��
                ��Ҫ���˳�UTRANCTRLѡ�����̣��ٴ��MMCѡ��״̬����
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvMmcAbortFsmReqMsg_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* �����յ�MMC���ѡ��״̬����Ϣ��� */
    NAS_UTRANCTRL_SetRcvMmcAbortFsmReqMsgFlg_PlmnSelection(VOS_TRUE);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf
 ��������  : �ȴ�WASֹͣ�����ظ��������յ�ֹͣ�����ظ���ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��2��11��
   ��    ��   : w00167002
   �޸�����   : ��������W���.
                ע:SVLTE�����ߣ���W������NO RF����G�������ɹ�����פ���ɹ���
                �����ٷ�������ʱ������WAS,����G�ᶪ��������UTRANCTRL״̬��ʱ��
                ��NO RFʱ��ǰ��FDDģʽ�ģ����MMC�ٷ�������ʱ�򣬻��ȸ�WAS���ͣ�
                UTRAN����SKIP W��Ϣ����UTRANCTRL״̬������TDD.
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;


    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf: ENTERED");


    /* �յ���MMC���״̬����Ϣ����ص�SUSPEND״̬�˳�UTRANCTRLѡ������ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf WITH MMC ABORT");

        /* ��ʱ��Ҫ�ص�W��,��TDRRC���͹������� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* Ǩ��״̬���ȵ�TDRRC����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }

    /* �й������Ǵ������˳���ǰ״̬�� */
    if ( (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
      || ( (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
        && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName) ) )
    {

        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�W��,��TDRRC���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDRRC����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnfBackTD
 ��������  : �ȴ���TD����W�������յ�WAS����ظ��Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��12��17��
   ��    ��   : w00167002
   �޸�����   : ��W������ʧ�ܣ���UTRANCTRLѡ��TD����ʱ���յ���һ�׶ζ�
                ʱ����ʱ����Ϣ���������ѡ��״̬������ǰMMCѡ��״̬����W��STOP REQ���󣬶�����
                ��TD��STOP������������MMC����������Lte,����˫��ģ�쳣��λ. ����Ϣ���ѡ��״̬��ʱ��
                ��Ҫ���˳�UTRANCTRLѡ�����̣��ٴ��MMCѡ��״̬������ʱMMC�յ�ѡ��״̬����MMC���͵�
                abort��Ϣ��ϣ�����˳�ѡ��״̬����
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnfBackTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
#endif

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();
    pstRrmmSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* ���帴λ */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF);

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();


    /* �յ���MMC���״̬����Ϣ�����˳�UTRANCTRLѡ�����̣�֪ͨMMC�˳�ѡ������ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_UTRANCTRL_BuildInterUtranCtrlPlmnSelectionAbortFinishIndMsg((NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }

    /* �����ǰ�������ϢΪ��ʱ����ʱ������Ҫ���������ظ�ʧ����Ϣ */
    else if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* ȡ�����״̬�������ظ�ʧ����Ϣ��MMCģ�� */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �л���MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    /* �����TDS/W������Ļ���������Ҫִ�дμ��ز������Է�ֹ���³�������:
       ����֪ͨ�����FDD������FDD��������ʧ�ܣ�����TDD��������TDD������ʧ�ܣ�
       ��ʱ��Ҫ��FDD�����ڼ��ص��ڴ��У��Է�ֹGSM����LTEפ��������FDD���л�����
       ��FDD�����ڴ��ж���λ
    */
    if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
    {
        enUtranMode = NAS_UTRANCTRL_GetPreUtranMode();
        enRatMode   = NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(enUtranMode);

        (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);
    }
#endif

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnfBackTD
 ��������  : �ȴ���TD����W�������յ�WAS����ظ���ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnfBackTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnfBackTD: ENTERED");

    /* ��λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnfBackW
 ��������  : �ȴ���TD����W�������յ�WAS����ظ���ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnfBackW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
#endif

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();
    pstRrmmSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* ���帴λ */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF);

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();


    if (VOS_TRUE == NAS_UTRANCTRL_GetRcvMmcAbortFsmReqMsgFlg_PlmnSelection())
    {
        NAS_UTRANCTRL_BuildInterUtranCtrlPlmnSelectionAbortFinishIndMsg((NAS_MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    /* �����ǰ�������ϢΪ��ʱ����ʱ������Ҫ���������ظ�ʧ����Ϣ */
    else if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* ȡ�����״̬�������ظ�ʧ����Ϣ��MMCģ�� */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �л���MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
    /* �����TDS/W������Ļ���������Ҫִ�дμ��ز������Է�ֹ���³�������:
       ����֪ͨ�����FDD������FDD��������ʧ�ܣ�����TDD��������TDD������ʧ�ܣ�
       ��ʱ��Ҫ��FDD�����ڼ��ص��ڴ��У��Է�ֹGSM����LTEפ��������FDD���л�����
       ��FDD�����ڴ��ж���λ
    */
    if (VOS_TRUE == NAS_DYNLOAD_GetEnableDynloadTWFlg())
    {
        enUtranMode = NAS_UTRANCTRL_GetPreUtranMode();
        enRatMode   = NAS_UTRANCTRL_GetRatModeBasedOnUtranMode(enUtranMode);

        (VOS_VOID)NAS_DYNLOAD_LoadAS(NAS_DYNLOAD_LOAD_RATCOMB_TYPE_T_W, enRatMode);
    }
#endif

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection
 ��������  : �յ�csg list abort����Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��11��3��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvCsgListAbortReq_PlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �������csg list�������棬�����csg list�������� */
    NAS_UTRANCTRL_ClearCacheMsg(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ));

    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnfBackW
 ��������  : �ȴ���TD����W�������յ�WAS����ظ���ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��8��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnfBackW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnfBackW: ENTERED");

    /* ��λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
