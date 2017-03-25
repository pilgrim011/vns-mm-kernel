/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasUtranCtrlFsmSyscfg.c
  �� �� ��   : ����
  ��    ��   : w00167002
  ��������   : 2012��08��07��
  ����޸�   :
  ��������   : SYSCFG״̬������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��08��07��
    ��    ��   : w00167002
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "v_typdef.h"
#include "NasComm.h"
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmSyscfg.h"
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlFsmSyscfgTbl.h"
#include "NasUtranCtrlCommFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_SYSCFG_C


#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
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
  6 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_Init
 ��������  : �յ�WAS��SYSCFG���ûظ���Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:RRMM_SYS_CFG_CNF��Ϣ���׵�ַ
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
VOS_UINT32 NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* �յ�W��SYSCFG�ظ���֪ͨTDģSYSCFG���� */
    NAS_UTRANCTRL_SndGuAsSyscfgReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDģ��SYSCFG�ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_SYSCFG_STA_WAIT_TD_SYSCFG_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF_LEN);

    /* ���������״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_Init
 ��������  : �յ�Td��SYSCFG���ûظ���Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:RRMM_SYS_CFG_CNF��Ϣ���׵�ַ
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
VOS_UINT32 NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* �յ�TD��SYSCFG�ظ���֪ͨWģSYSCFG���� */
    NAS_UTRANCTRL_SndGuAsSyscfgReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�Wģ��SYSCFG�ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF_LEN);

    /* ���������״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitWasSysCfgCnf
 ��������  : �յ�WAS��SYSCFG���ûظ���Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:RRMM_SYS_CFG_CNF��Ϣ���׵�ַ
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
VOS_UINT32 NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRLֹͣ�ȴ�WAS�ظ���ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF);

    /* ����ģ��״̬���ص�main״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* �������MMC��SYSCFG״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvWasSuspendInd_SysCfg_WaitWasSysCfgCnf
 ��������  : �յ�WAS��SUSPEND��Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:RRMM_SUSPEND_IND��Ϣ���׵�ַ
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
VOS_UINT32 NAS_UTRANCTRL_RcvWasSuspendInd_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������ظ�����ʧ�� */
    NAS_UTRANCTRL_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitWasSysCfgCnf
 ��������  : ��TDģʱ���յ�w�����SYSCFG�ظ���Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_SYS_CFG_CNF��Ϣ�Ľṹ����ַ
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
VOS_UINT32  NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitWasSysCfgCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiWasSysCfgCnfExpired_SysCfg_WaitWasSysCfgCnf
 ��������  : �յ�WAS��SYSCFG���ûظ���ʱ��Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:RRMM_SUSPEND_IND��Ϣ���׵�ַ
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
VOS_UINT32 NAS_UTRANCTRL_RcvTiWasSysCfgCnfExpired_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstSysCfgCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    pstEntryMsg     = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    pstSysCfgCnfMsg = (RRMM_SYS_CFG_CNF_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasSysCfgCnfExpired_SysCfg_WaitWasSysCfgCnf: ENTERED");

    /* ��Ϊ��ǰSYSCFG����ʧ�� */
    pstSysCfgCnfMsg->ulResult = RRMM_SYS_CFG_RESULT_FAILURE;

    /* �������SYSCFG��Ϣ�ŵ���������� */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType, (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* ������Ҫ�滻�����Ϣ��ǣ�����MMCģ��ͻᴦ��SYSCFG����ʧ����Ϣ */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �ص�main״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitTdSysCfgCnf
 ��������  : �յ�Td��SYSCFG���ûظ���Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:RRMM_SYS_CFG_CNF��Ϣ���׵�ַ
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
VOS_UINT32 NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitTdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRLֹͣ�ȴ�WAS�ظ���ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF);

    /* ����ģ��״̬���ص�main״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* �����������״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTdSuspendInd_SysCfg_WaitTdSysCfgCnf
 ��������  : �յ�Td��SUSPEND��Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:RRMM_SUSPEND_IND��Ϣ���׵�ַ
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
VOS_UINT32 NAS_UTRANCTRL_RcvTdSuspendInd_SysCfg_WaitTdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������ظ�����ʧ�� */
    NAS_UTRANCTRL_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, TPS_PID_RRC);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitTdSysCfgCnf
 ��������  : ��Wģʱ���յ�TD�����SYSCFG�ظ���Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_SYS_CFG_CNF��Ϣ�Ľṹ����ַ
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
VOS_UINT32  NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitTdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitTdSysCfgCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_UTRANCTRL_RcvTiTdSysCfgCnfExpired_SysCfg_WaitTdSysCfgCnf
 ��������  : �յ�TD��SYSCFG���ûظ���ʱ��Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:TI_NAS_MMC_WAIT_TD_SYSCFG_CNF��Ϣ���׵�ַ
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
VOS_UINT32 NAS_UTRANCTRL_RcvTiTdSysCfgCnfExpired_SysCfg_WaitTdSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstSysCfgCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    pstEntryMsg     = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    pstSysCfgCnfMsg = (RRMM_SYS_CFG_CNF_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdSysCfgCnfExpired_SysCfg_WaitTdSysCfgCnf: ENTERED");

    /* ��Ϊ��ǰSYSCFG����ʧ�� */
    pstSysCfgCnfMsg->ulResult = RRMM_SYS_CFG_RESULT_FAILURE;

    /* ��SYSCFG����ʧ����Ϣ�ŵ���������� */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType, (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* ������Ҫ�滻�����Ϣ��ǣ�����MMCģ��ͻᴦ��SYSCFG����ʧ����Ϣ */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �ص�main״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}


#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
