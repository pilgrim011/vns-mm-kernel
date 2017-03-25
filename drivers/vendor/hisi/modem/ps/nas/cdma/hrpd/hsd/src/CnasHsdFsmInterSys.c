/*******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdFsmInterSys.c
  �� �� ��   : ����
  ��    ��   : z00316370
  ��������   : 2015��06��03��
  ��������   : HRPD SD L2 INTER_SYS״̬���¼�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasHsdFsmInterSys.h"
#include  "CnasHsdFsmInterSysTbl.h"
#include  "CnasHsdCtx.h"
#include  "CnasHsdComFunc.h"
#include  "CnasPrlParse.h"
#include  "cas_hrpd_overheadmsg_nas_pif.h"
#include  "CnasHsdSndHsm.h"
#include  "CnasHsdSndMscc.h"
#include  "CnasHsdSndInternalMsg.h"
#include  "CnasHsdSysAcqStrategy.h"
#include  "CnasHsdSndCas.h"
#include  "CnasHsdAvoidStrategy.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_FSM_INTER_SYS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvHsdIratFromLteNtf_InterSys_Init
 ��������  : CNAS_HSD_INTER_SYS_STA_INIT״̬�յ�ID_CAS_CNAS_HRPD_IRAT_FROM_LTE_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvHsdIratFromLteNtf_InterSys_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���������Ϣ */
    CNAS_HSD_SaveCurEntryMsg(ulEventType, pstMsg);

    /* Ǩ�Ƶ� CNAS_HSD_INTER_SYS_STA_WAIT_OHM_IND״̬, ������������ʱ��TI_CNAS_HSD_IRAT_TO_HRPD_WAIT_CAS_OHM_IND */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_INTER_SYS_STA_WAIT_OHM_IND);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND, TI_CNAS_HSD_WAIT_CAS_OHM_IND_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasOverheadInd_InterSys_WaitCasInd
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_CAS_IND״̬�յ�ID_CNAS_HRDP_OVERHEAD_MSG_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasOhmInd_InterSys_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_HRPD_SYSTEM_STRU                              *pstHrpdSys;
    CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU                    *pstCasOhmMsg;

    /* ֹͣ������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND);

    pstCasOhmMsg = (CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU *)pstMsg;

    pstHrpdSys   = CNAS_HSD_GetCasOhmHrpdSysAddr();

    pstHrpdSys->stFreq.enBandClass = pstCasOhmMsg->usBandClass;
    pstHrpdSys->stFreq.usChannel   = pstCasOhmMsg->usFreq;
    pstHrpdSys->ucSubnetMask       = pstCasOhmMsg->ucSubNetMask;
    PS_MEM_CPY(pstHrpdSys->aucSubnet, pstCasOhmMsg->aucSectorId, CNAS_PRL_BYTES_IN_SUBNET);

    /* ��ϵͳ�л�ʧ�� */
    if (CNAS_HSD_ASSN_SUCC != CNAS_HSD_CheckHrpdSysAssnWith1X(pstHrpdSys))
    {
        CNAS_HSD_SndInterSysRslt(VOS_RATMODE_HRPD, VOS_FALSE, CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_BUTT);
    }
    else
    {
        /* avoidģ�鴦�� */
        CNAS_HSD_ProcAvoidEventInSubnetIdChange(pstHrpdSys);

        /* ����history list */
        CNAS_HSD_UpdateHistorySysList(pstHrpdSys);

        /* ����Hrpdפ����Ϣ */
        CNAS_HSD_UpdateHrpdSysInfo(pstHrpdSys);

        /* ��ע�������籣�浽MRU */
        CNAS_HSD_UpdateMru0(pstHrpdSys);

        /* HSD�յ�CAS��overhead��Ϣʱ��Ҫ��HSMת��overhead��Ϣ */
        CNAS_HSD_SndHsmOverheadMsgInd(pstCasOhmMsg);

        /* ��ϵͳ�л���HRPDʱ��Ҳ��Ҫ��MSCCת��ohm��Ϣ*/
        CNAS_HSD_SndMsccOverheadMsgInd(pstCasOhmMsg,pstHrpdSys);

        CNAS_HSD_SndInterSysRslt(VOS_RATMODE_HRPD, VOS_TRUE, CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_BUTT);
    }

    /* �˳����״̬�� */
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvTiWaitCasOhmIndExpired_InterSys_WaitCasOhmInd
 ��������  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬��TI_CNAS_HSD_WAIT_CAS_OHM_IND��Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiWaitCasOhmIndExpired_InterSys_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_HSD_SndInterSysRslt(VOS_RATMODE_HRPD, VOS_FALSE, CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_BUTT);

    /* �˳����״̬�� */
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccPowerSaveReq_InterSys_WaitCasOhmInd
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_CAS_IND״̬�յ�ID_MMA_HSD_POWER_SAVE_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerSaveReq_InterSys_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND);

    /* ����power save���� */
    CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

    /* �˳����״̬�� */
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitCasInd
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_CAS_IND״̬�յ�ID_MMA_HSD_POWER_OFF_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND);

    /* ��ջ��� */
    CNAS_HSD_InitCacheMsgQueue(&(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue), CNAS_HSD_INIT_CTX_POWEROFF);

    /* ����ػ����� */
    CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

    /* �˳����״̬�� */
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitCasOhmInd
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_CAS_IND״̬�յ�ID_MMA_HSD_DATA_CALL_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֮ǰ�Ѿ�֪ͨMSCC�з��� */
    CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasSuspendInd_InterSys_Init
 ��������  : CNAS_HSD_INTER_SYS_STA_INIT״̬�յ�ID_CAS_CNAS_HRPD_SUSPEND_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasSuspendInd_InterSys_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���������Ϣ */
    CNAS_HSD_SaveCurEntryMsg(ulEventType, pstMsg);

    /* Ǩ�Ƶ� CNAS_HSD_INTER_SYS_STA_WAIT_OHM_IND״̬, ������������ʱ��TI_CNAS_HSD_IRAT_TO_HRPD_WAIT_CAS_OHM_IND */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_INTER_SYS_STA_WAIT_IRAT_OR_RESUME_IND);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND, TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasIratToLte_InterSys_Init
 ��������  : CNAS_HSD_INTER_SYS_STA_INIT״̬�յ�ID_CAS_CNAS_HRPD_IRAT_TO_LTE_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasIratToLte_InterSys_WaitIratOrResume(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND);

    CNAS_HSD_SndHsmIratToLteInd();

    CNAS_HSD_SndMsccInterSysEndInd(VOS_RATMODE_LTE);

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_HSD_SndInterSysRslt(VOS_RATMODE_LTE, VOS_TRUE, CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_BUTT);

    /* �˳����״̬�� */
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasResumeInd_InterSys_Init
 ��������  : CNAS_HSD_INTER_SYS_STA_INIT״̬�յ�ID_CAS_CNAS_HRPD_RESUME_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasResumeInd_InterSys_WaitIratOrResume(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND);

    CNAS_HSD_SndHsmResumeInd();

    CNAS_HSD_SndMsccInterSysEndInd(VOS_RATMODE_HRPD);

    CNAS_HSD_SndCasResumeRsp();

    /* �ж��Ƿ��ڴ�������� */
    if (VOS_TRUE == CNAS_HSD_GetAbortFlg_InterSys())
    {
        /* �˳����״̬�� */
        CNAS_HSD_QuitFsmL2();

        return VOS_TRUE;
    }

    /* Ǩ�Ƶ� CNAS_HSD_INTER_SYS_STA_WAIT_OHM_IND״̬, ������������ʱ��TI_CNAS_HSD_IRAT_TO_HRPD_WAIT_CAS_OHM_IND */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_INTER_SYS_STA_WAIT_OHM_IND);

    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND, TI_CNAS_HSD_WAIT_CAS_OHM_IND_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvTiWaitIratOrResumeExpired_InterSys_WaitIratOrResume
 ��������  : CNAS_HSD_INTER_SYS_STA_INIT״̬����RESUME_IND/IRAT_TO_LTE_NTF��Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiWaitIratOrResumeExpired_InterSys_WaitIratOrResume(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���쳣���̲����ٹ����Ƿ��д�ϱ�־��ֱ�Ӹ�λ */

    /* ��ѡ��LTEʱ����û���յ�IRAT_TO_LTEҲû�յ�RESUME_IND,���쳣����µ��õ���λ */
    CNAS_REBOOT_INFO_STRU               stCnasRebootInfo;

    /* ��λ�ײ� */
    PS_MEM_SET(&stCnasRebootInfo, 0x0, sizeof(CNAS_REBOOT_INFO_STRU));
    stCnasRebootInfo.enRebootScene = CNAS_REBOOT_SCENE_TI_HSD_WAIT_CAS_SUSPEND_CNF_EXPIRED;
    stCnasRebootInfo.ulPid         = UEPS_PID_HSD;
    stCnasRebootInfo.ulFsmId       = CNAS_HSD_GetCurrFsmId();
    stCnasRebootInfo.ulFsmState    = CNAS_HSD_GetFsmTopState();

    /* ��λ��ֱ���˳� */
    CNAS_SoftReboot(stCnasRebootInfo);

    /* �˳����״̬��*/
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccPowerSaveReq_InterSys_WaitIratOrResume
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_IRAT_OR_RESUME_IND״̬�յ�ID_MMA_HSD_POWER_SAVE_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerSaveReq_InterSys_WaitIratOrResume(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_InterSys(VOS_TRUE, CNAS_HSD_ABORT_REASON_POWER_SAVE))
    {
        /* ֹͣ������ʱ�� */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND);

        /* ����POWER SAVE���� */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

        /* ֪ͨ�������ֹ�л����� */
        CNAS_HSD_SndCasSuspendRelReq();

        /* Ǩ�Ƶ� CNAS_HSD_INTER_SYS_STA_WAIT_OHM_IND״̬, ������������ʱ��TI_CNAS_HSD_IRAT_TO_HRPD_WAIT_CAS_OHM_IND */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_INTER_SYS_STA_WAIT_SUSPEND_REL_CNF);

        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF, TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitIratOrResume
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_IRAT_OR_RESUME_IND״̬�յ�ID_MMA_HSD_POWER_OFF_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitIratOrResume(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_InterSys(VOS_TRUE, CNAS_HSD_ABORT_REASON_POWER_OFF))
    {
        /* ֹͣ������ʱ�� */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND);

        /* ����POWER OFF���� */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);

        /* ֪ͨ�������ֹ�л����� */
        CNAS_HSD_SndCasSuspendRelReq();

        /* Ǩ�Ƶ� CNAS_HSD_INTER_SYS_STA_WAIT_OHM_IND״̬, ������������ʱ��TI_CNAS_HSD_IRAT_TO_HRPD_WAIT_CAS_OHM_IND */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_INTER_SYS_STA_WAIT_SUSPEND_REL_CNF);

        CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF, TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitIratOrResume
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_IRAT_OR_RESUME_IND״̬�յ�ID_MSCC_HSD_DATA_CALL_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitIratOrResume(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* HRPD�Ѿ������𣬲����ṩ�������� */
    CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasNetworkLost_InterSys_WaitCasOhmInd
 ��������  : CNAS_HSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬�յ�ID_CAS_CNAS_HRPD_NETWORK_LOST_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��18��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_InterSys_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstCasNetworkLostMsg;
    CNAS_HSD_REDIRECTION_STRU                              *pstRedirection;

    /* ֹͣ������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_OHM_IND);

    pstCasNetworkLostMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU*)pstMsg;

    pstRedirection = CNAS_HSD_GetRedirectionFreqAddr();

    if (CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT == pstCasNetworkLostMsg->enNetworkLostReason)
    {
        pstRedirection->ucChanNum = pstCasNetworkLostMsg->ucChanNum;

        if (0 != pstRedirection->ucChanNum)
        {
            PS_MEM_CPY(pstRedirection->aulChannel,
                       pstCasNetworkLostMsg->aulChannel,
                       sizeof(CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU) * pstCasNetworkLostMsg->ucChanNum);

            /* ��ӡ�յ���Ƶ����Ϣ */
            CNAS_HSD_LogRedirectionFreqList(pstRedirection);
        }
    }

    CNAS_HSD_SndInterSysRslt(VOS_RATMODE_HRPD,
                             VOS_FALSE,
                             pstCasNetworkLostMsg->enNetworkLostReason);

    /* �˳����״̬�� */
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasSuspendRelCnf_InterSys_WaitSuspendRelCnf
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_SUSPEND_REL_CNF״̬�յ�ID_CAS_CNAS_HRPD_SUSPEND_REL_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasSuspendRelCnf_InterSys_WaitSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF);

    CNAS_HSD_SndHsmResumeInd();

    CNAS_HSD_SndMsccInterSysEndInd(VOS_RATMODE_HRPD);

    /* �˳����״̬�� */
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasIratToLte_InterSys_WaitSuspendRelCnf
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_SUSPEND_REL_CNF״̬�յ�ID_CAS_CNAS_HRPD_IRAT_TO_LTE_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasIratToLte_InterSys_WaitSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF);

    CNAS_HSD_SndHsmIratToLteInd();

    CNAS_HSD_SndMsccInterSysEndInd(VOS_RATMODE_LTE);

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_HSD_SndInterSysRslt(VOS_RATMODE_LTE, VOS_TRUE, CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_BUTT);

    /* �˳����״̬�� */
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasResumeInd_InterSys_WaitSuspendRelCnf
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_SUSPEND_REL_CNF״̬�յ�ID_CAS_CNAS_HRPD_RESUME_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasResumeInd_InterSys_WaitSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SndHsmResumeInd();

    CNAS_HSD_SndCasResumeRsp();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasResumeInd_InterSys_WaitSuspendRelCnf
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_SUSPEND_REL_CNF״̬�յ�TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiWaitSuspendRelCnfExpired_InterSys_WaitSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SndHsmResumeInd();

    CNAS_HSD_SndMsccInterSysEndInd(VOS_RATMODE_HRPD);

    /* �˳����״̬�� */
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitSuspendRelCnf
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_SUSPEND_REL_CNF״̬�յ�ID_MSCC_HSD_POWER_OFF_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccPowerOffReq_InterSys_WaitSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_HSD_SetAbortFlg_InterSys(VOS_TRUE, CNAS_HSD_ABORT_REASON_POWER_OFF))
    {
        /* ��ջ��� */
        CNAS_HSD_InitCacheMsgQueue(&(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue), CNAS_HSD_INIT_CTX_POWEROFF);

        /* ����ػ����� */
        CNAS_HSD_SaveCacheMsg(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitSuspendRelCnf
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_SUSPEND_REL_CNF״̬�յ�ID_MSCC_HSD_DATA_CALL_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallReq_InterSys_WaitSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* HRPD�Ѿ������𣬲����ṩ�������� */
    CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasNetworkLost_InterSys_WaitIratOrResume
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_IRAT_OR_RESUME_IND״̬�յ�ID_CAS_CNAS_HRPD_NETWORK_LOST_IND��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��5��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_InterSys_WaitIratOrResume(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstCasNetworkLostMsg;
    CNAS_HSD_REDIRECTION_STRU                              *pstRedirection;

    pstCasNetworkLostMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU*)pstMsg;

    /* ֹͣ������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_IRAT_OR_RESUME_IND);

    pstRedirection = CNAS_HSD_GetRedirectionFreqAddr();

    if (CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT == pstCasNetworkLostMsg->enNetworkLostReason)
    {
        pstRedirection->ucChanNum = pstCasNetworkLostMsg->ucChanNum;

        if (0 != pstRedirection->ucChanNum)
        {
            PS_MEM_CPY(pstRedirection->aulChannel,
                       pstCasNetworkLostMsg->aulChannel,
                       sizeof(CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU) * pstCasNetworkLostMsg->ucChanNum);

            /* ��ӡ�յ���Ƶ����Ϣ */
            CNAS_HSD_LogRedirectionFreqList(pstRedirection);
        }
    }

    CNAS_HSD_SndHsmResumeInd();

    CNAS_HSD_SndMsccInterSysEndInd(VOS_RATMODE_HRPD);

    CNAS_HSD_SndInterSysRslt(VOS_RATMODE_HRPD,
                             VOS_FALSE,
                             pstCasNetworkLostMsg->enNetworkLostReason);

    /* �˳����״̬�� */
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasNetworkLost_InterSys_WaitSuspendRelCnf
 ��������  : CNAS_HSD_INTER_SYS_STA_WAIT_SUSPEND_REL_CNF״̬�յ�ID_MSCC_HSD_DATA_CALL_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��5��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLost_InterSys_WaitSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_CAS_SUSPEND_REL_CNF);

    CNAS_HSD_SndHsmResumeInd();

    CNAS_HSD_SndMsccInterSysEndInd(VOS_RATMODE_HRPD);

    /* �˳����״̬�� */
    CNAS_HSD_QuitFsmL2();

    return VOS_TRUE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



