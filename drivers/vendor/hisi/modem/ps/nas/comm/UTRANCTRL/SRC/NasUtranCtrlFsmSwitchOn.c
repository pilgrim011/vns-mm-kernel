/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasUtranCtrlFsmSwitchOn.c
  �� �� ��   : ����
  ��    ��   : w00167002
  ��������   : 2012��08��9��
  ����޸�   :
  ��������   : UTRANCTRLģ�鿪��״̬����Ϣ�Ĵ�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��08��9��
    ��    ��   : w00167002
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasComm.h"
#include "PsTypeDef.h"
#include "NasUtranCtrlFsmSwitchOn.h"
#include "NasUtranCtrlFsmSwitchOnTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlCommFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_SWITCHON_C

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_Init
 ��������  : ����״̬����������
 �������  : ulEventType:��Ϣ����
             pstMsg:TAFUtranCtrl_START_REQ��Ϣ���׵�ַ
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
VOS_UINT32 NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* �յ�W�¿����ظ���֪ͨTDģ���� */
    NAS_UTRANCTRL_SndGuAsStartReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDģ�Ŀ����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_TD_START_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_START_CNF, TI_NAS_UTRANCTRL_WAIT_TD_START_CNF_LEN);

    /* ���������״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_Init
 ��������  : ����״̬����������
 �������  : ulEventType:��Ϣ����
             pstMsg:TAFUtranCtrl_START_REQ��Ϣ���׵�ַ
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
VOS_UINT32 NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* �յ�TD�¿����ظ���֪ͨWģ�鿪�� */
    NAS_UTRANCTRL_SndGuAsStartReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�Wģ�Ŀ����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_WAS_START_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF_LEN);

    /* ���������״̬������ */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitWasStartCnf
 ��������  : Wģ����㿪���ظ���Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_START_CNF��Ϣ�Ľṹ����ַ
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
VOS_UINT32  NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRLֹͣ�ȴ�WAS�ظ���ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF);

    /* ����ģ��״̬���ص�main״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* �����������״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitWasStartCnf
 ��������  : ��Wģʱ���յ�TD����㿪���ظ���Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_START_CNF��Ϣ�Ľṹ����ַ
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
VOS_UINT32  NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitWasStartCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf
 ��������  : Wģ����㿪���ظ���ʱ��Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_START_CNF��Ϣ�Ľṹ����ַ
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
VOS_UINT32  NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                *pstRrMmStartCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    pstEntryMsg        = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    pstRrMmStartCnfMsg = (RRMM_START_CNF_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf: ENTERED");

    /* ��Ϊ��ǰ����ʧ�� */
    pstRrMmStartCnfMsg->ulResult = MMC_START_FAILURE;

    /* ����ǰ����ʧ����Ϣ�ŵ���������� */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType, (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* ������Ҫ�滻�����Ϣ��ǣ�����MMCģ��ͻᴦ�����ظ�ʧ����Ϣ */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* UTRANCTRL״̬���ص�MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣδ�����������MMC�������� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitTdStartCnf
 ��������  : Tdģ����㿪���ظ���Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_START_CNF��Ϣ�Ľṹ����ַ
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
VOS_UINT32  NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitTdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRLֹͣ�ȴ�TD�ظ���ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_START_CNF);

    /* ����ģ��״̬���ص�main״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* �����������״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitTdStartCnf
 ��������  : ��TDģʱ���յ�W����㿪���ظ���Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_START_CNF��Ϣ�Ľṹ����ַ
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
VOS_UINT32  NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitTdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitTdStartCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_SwitchOn_WaitTdStartCnf
 ��������  : Tdģ����㿪���ظ���ʱ��Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_START_CNF��Ϣ�Ľṹ����ַ
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
VOS_UINT32  NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_SwitchOn_WaitTdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                *pstRrMmStartCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    pstEntryMsg        = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    pstRrMmStartCnfMsg = (RRMM_START_CNF_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_SwitchOn_WaitTdStartCnf: ENTERED");

    /* ��Ϊ��ǰ����ʧ�� */
    pstRrMmStartCnfMsg->ulResult = MMC_START_FAILURE;

    /* ����ǰ����ʧ����Ϣ�ŵ���������� */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType, (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* ������Ҫ�滻�����Ϣ��ǣ�����MMCģ��ͻᴦ�����ظ�ʧ����Ϣ */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* UTRANCTRL״̬���ص�main״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣδ�����������MMC�������� */
    return VOS_FALSE;
}

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
