


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include  "CnasCcb.h"
#include  "CnasPrlApi.h"
#include  "CnasXsdFsmSysAcq.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "CnasXsdSndMscc.h"
#include  "CnasXsdSndCas.h"
#include  "CnasXsdFsmRedir.h"
#include  "CnasXsdSysAcqStrategy.h"
#include  "CnasMntn.h"
#include  "CnasXsdMntn.h"
#include  "CnasTimerMgmt.h"
#include  "CnasXsdSndXreg.h"
#include  "CnasXsdFsmRedirTbl.h"
#include  "CnasXsdSndXcc.h"
#include  "CnasXsdCtx.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_REDIR_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
Function Name   :   CNAS_XSD_RcvXsdRedirInd_Redir_Init
Description     :   .

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2014-12-26
        Author  :   m00270891
        Modify content :    Create

    2.��    ��   : 2015��1��05��
      ��    ��   : y00245242
      �޸�����   : ����OOC��������
    3.��    ��   : 2015��4��20��
      ��    ��   : w00242748
      �޸�����   : DTS2015041609529:����MRU0�����MRU0ͬ���ɹ�����û�취פ����
                   ����»ᵼ����ѭ��������
    4.��    ��   : 2015��8��25��
      ��    ��   : w00176964
      �޸�����   : DTS2015082606848:�ض������̲ο���˴���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdRedirInd_Redir_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_REDIRECTION_IND_STRU                      *pstIntRedirInd  = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList     = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                                              usCurScanListIndex;
    VOS_UINT16                                              usDstChanNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstOrigSysChan = VOS_NULL_PTR;

    /* Save event information */
    CNAS_XSD_SaveCurEntryMsg(ulEventType, pstMsg);

    pstIntRedirInd    = (CNAS_XSD_XSD_REDIRECTION_IND_STRU *)pstMsg;
    pstScanList       = CNAS_XSD_GetScanChanListAddr_Redir();

    CNAS_XSD_BuildScanChanList_Redirection(&(pstIntRedirInd->stRedirectionInfo), pstScanList);

    /* Get the cur channel index*/
    usCurScanListIndex = pstScanList->usCurScanIndex;
    usDstChanNum       = 0;
    NAS_MEM_SET_S(astDstChan, sizeof(astDstChan), 0 , sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

    /* obtain the scan list */
    CNAS_XSD_GetNextScanChanList(usCurScanListIndex,
                                 &usDstChanNum,
                                 astDstChan,
                                 pstScanList,
                                 VOS_TRUE);

    if (0 == usDstChanNum)
    {
        /* return_if_fail is false, avoid the current freqency */
        if (VOS_FALSE == CNAS_XSD_GetRedirectionReturnIfFailFlag())
        {
            /* Get Original system band class and channel */
            pstOrigSysChan = (&((CNAS_XSD_GetRedirectionOrignalSys())->stFreq));

            CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_REDIRECTION_FAIL, pstOrigSysChan);
        }

        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_FAILURE);

        /* if scan list id empty quit the FSM*/
        CNAS_XSD_QuitFsmRedir_Redir();
        return VOS_TRUE;
    }

    /* notify CREG to delete zone_lists and sid_nid_lists */
    CNAS_XSD_SndXregRedirInd();

    CNAS_XSD_SetSystemCampOnFlag(VOS_FALSE);

    /* send sync request to CAS */
    CNAS_XSD_SndCasSysSyncReq(usDstChanNum, astDstChan);

    /* indiacte MSCC  */
    CNAS_XSD_SndMsccSysAcqStartInd();

    /* update the FSM state to CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF, usDstChanNum * TI_CNAS_XSD_WAIT_CAS_SYNC_ONE_FREQ_LEN + 5);

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvCasSysSyncCnf_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf = VOS_NULL_PTR;

    pstSyncCnf  = (CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU *)pstMsg;

    /* Stop the Wait Sync Cnf protection timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* Check the Sync Cnf Message and place any required frequency in the avoid list */
    CNAS_XSD_ProcFreqAvoidedInCasSyncCnf(pstSyncCnf);

    /* ���ΪNO RF������ʧ�ܵĴ��� */
    if (CNAS_CAS_1X_RSLT_NO_RF == pstSyncCnf->enSyncRslt)
    {
        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_NORF);

        /* �˳����״̬�� */
        CNAS_XSD_QuitFsmRedir_Redir();

        return VOS_TRUE;
    }

    if (CNAS_CAS_1X_RSLT_SUCCESS == pstSyncCnf->enSyncRslt)
    {
        CNAS_XSD_ProcCasSyncCnfSucc_Redir(pstSyncCnf);
    }
    else
    {
        CNAS_XSD_ProcCasSyncCnfFail_Redir(pstSyncCnf);
    }

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Clear the Cache buffer and save the MMA Power off request in the buffer. Start Camp-On Protect timer*/
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* Set Abort Flag to true */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    /* Send the Stop Sync Request to CAS*/
    CNAS_XSD_SndCasStopSysSyncReq();

    /* Set next state to CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF and start the
       TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF protect timer */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvTiWaitCasSysSyncCnfTimerExpired_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasSysSyncCnfExpired_Redir_WaitCasSysSyncCnf: timer out");

    /* Send ID_CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ to CAS to stop the current sync process*/
    CNAS_XSD_SndCasStopSysSyncReq();

    /* Set next state to CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF and start the
       TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF protect timer */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Stop Sync Cnf protect timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* Save the Power Save Request in cache */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* Set Abort flag to true */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    /* Send Stop Sync Req to CAS */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* Set next State to Wait CAS Stop Sync Cnf and start the protect timer */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasSysSyncCnf
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* ֹͣͬ����ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* ����ֹͣͬ������ */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    /* Ǩ״̬���ñ�����ʱ�� */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasSysSyncCnf
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF״̬�յ�ID_MSCC_XSD_END_EMC_CALLBACK_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* ֹͣͬ����ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* ����ֹͣͬ������ */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    /* Ǩ״̬���ñ�����ʱ�� */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasSysSyncCnfOrigSys
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF_RET_ORIG_SYS״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* ֹͣͬ����ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* ����ֹͣͬ������ */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    /* Ǩ״̬���ñ�����ʱ�� */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasSysSyncCnfOrigSys
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF_RET_ORIG_SYS״̬�յ�ID_MSCC_XSD_END_EMC_CALLBACK_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* ֹͣͬ����ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* ����ֹͣͬ������ */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    /* Ǩ״̬���ñ�����ʱ�� */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasOhmInd
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_IND״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasOhmInd
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_RET_ORIG_SYS_IND״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasOhmInd
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_RET_ORIG_SYS_IND״̬�յ�ID_MSCC_XSD_END_EMC_CALLBACK_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* �����˳�CallBackģʽ���� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasOhmInd
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_IND״̬�յ�ID_MSCC_XSD_END_EMC_CALLBACK_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* �����˳�CallBackģʽ���� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasStopSysSyncCnf
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasStopSysSyncCnf
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF״̬�յ�ID_MSCC_XSD_END_EMC_CALLBACK_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasStopSysSyncCnfOrigSys
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasStopSysSyncCnfOrigSys
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS״̬�յ�ID_MSCC_XSD_END_EMC_CALLBACK_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        return VOS_TRUE;
    }

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   CNAS_XSD_RcvCasStopSysSyncCnf_Redir_WaitCasStopSysSyncCnf
Description     :   Performs abort procedure if the abort flag is true. Otherwise continues Redirection flow by
                    getting the next Redirection scan list.
Input parameters:   ulEventType  - The event type of the Stop Sync Cnf message from CAS.
                    pstMsg       - pointer to Stop Sync Cnf message from CAS.
Outout parameters:  None
Return Value    :   VOS_TRUE

Modify History:
    1)  Date    :   2014-12-26
        Author  :   a00295761
        Modify content :    Create

    2.��    ��   : 2015��1��05��
      ��    ��   : y00245242
      �޸�����   : ����OOC��������
    3.��    ��   : 2015��4��20��
      ��    ��   : w00242748
      �޸�����   : DTS2015041609529:����MRU0�����MRU0ͬ���ɹ�����û�취פ����
                   ����»ᵼ����ѭ��������
*****************************************************************************/

VOS_UINT32 CNAS_XSD_RcvCasStopSysSyncCnf_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;

    /* Stop the Wait Stop Sync Cnf Protect timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF);

    /* Perform Abort procedure for Redirection FSM if Abort Flag is true */
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        CNAS_XSD_PerformAbortProcedure_Redir();

        return VOS_TRUE;
    }

    /* If abort flag is false, continue to Sync the next set of channels from Redirection scan list. */
    usDstChanNum       = 0;
    NAS_MEM_SET_S(astDstChan, sizeof(astDstChan), 0 , sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

    pstScanList        = CNAS_XSD_GetScanChanListAddr_Redir();
    usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex_Redir();

    CNAS_XSD_GetNextScanChanList(usCurScanListIndex,
                                 &usDstChanNum,
                                 astDstChan,
                                 pstScanList,
                                 VOS_TRUE);

    /* If Redirection scan list is empty, check the RETURN_IF_FAIL flag  */
    if (0 == usDstChanNum)
    {
        CNAS_XSD_ProcRedirScanListSyncComplete_Redir();
    }
    /* Continue to sync the channels from the redirection scan list. */
    else
    {
        CNAS_XSD_ContinueSyncRedirScanList_Redir(usDstChanNum, astDstChan);
    }

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Clear the Cache message buffer */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    /* Save the Power off request in the Buffer */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Set Abort Flag to True */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_Redir_WaitCasStopSysSyncCnf
Description     :   Abort the Redirection FSM if the Abort flag is true.
                    Otherwise continue Redirection flow by getting the next Redirection scan list.
Input parameters:   ulEventType  - The event type of the Wait Cas Stop Sync Timer expired message
                    pstMsg       - pointer to Wait Cas Stop Sync Timer expired message structure.
Outout parameters:  None
Return Value    :   VOS_TRUE

Modify History:
    1)  Date    :   2014-12-26
        Author  :   a00295761
        Modify content :    Create

    2.��    ��   : 2015��1��05��
      ��    ��   : y00245242
      �޸�����   : ����OOC��������
    3.��    ��   : 2015��4��20��
      ��    ��   : w00242748
      �޸�����   : DTS2015041609529:����MRU0�����MRU0ͬ���ɹ�����û�취פ����
                   ����»ᵼ����ѭ��������
*****************************************************************************/

VOS_UINT32 CNAS_XSD_RcvTiWaitCasStopSysSyncCnfTimerExpired_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;

    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_Redir_WaitCasStopSysSyncCnf: timer out");

    /* Perform Redirection Abort procedure if Abort flag is true */
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        CNAS_XSD_PerformAbortProcedure_Redir();

        return VOS_TRUE;
    }

    usDstChanNum       = 0;
    NAS_MEM_SET_S(astDstChan, sizeof(astDstChan), 0 , sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

    pstScanList        = CNAS_XSD_GetScanChanListAddr_Redir();
    usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex_Redir();

    /* Continue the Redirection Flow by getting the next Redirection scan list */
    CNAS_XSD_GetNextScanChanList(usCurScanListIndex,
                                 &usDstChanNum,
                                 astDstChan,
                                 pstScanList,
                                 VOS_TRUE);

    /* If scan list is complete check the RETURN_IF_FAIL value */
    if (0 == usDstChanNum)
    {
        CNAS_XSD_ProcRedirScanListSyncComplete_Redir();
    }
    /* Send Sync Request to CAS */
    else
    {
        CNAS_XSD_ContinueSyncRedirScanList_Redir(usDstChanNum, astDstChan);
    }

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the Power Save Request in cache */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* Set Abort flag to true */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;

}


/*****************************************************************************
Function Name   :   CNAS_XSD_RcvCasOhmInd_Redir_WaitCasOhmInd
Description     :   Process the OHM Indication message received from CAS.
                    Send Notification to XREG And MMA, about the current camped system details.
                    Quit Redirection FSM with Success result.
Input parameters:   ulEventType  - The event type of the OHM Indication message
                    pstMsg       - pointer to OHM Indication message structure.
Outout parameters:  None
Return Value    :   VOS_TRUE

Modify History:
    1)  Date    :   2014-12-26
        Author  :   a00295761
        Modify content :    Create

    2.��    ��   : 2015��7��17��
      ��    ��   : y00245242
      �޸�����   : iteration 17����

    3.��    ��   : 2015��08��20��
      ��    ��   : t00323010
      �޸�����   : DTS2015081904804 clear coverity
*****************************************************************************/

VOS_UINT32 CNAS_XSD_RcvCasOhmInd_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;
    VOS_UINT32                          ulIsNegSys;
    CAS_CNAS_1X_OHM_IND_STRU           *pstOhmInd = VOS_NULL_PTR;

    pstOhmInd = (CAS_CNAS_1X_OHM_IND_STRU *)pstMsg;

    /* Stop the Timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    stCurSysInfo.stFreq.enBandClass = pstOhmInd->usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstOhmInd->usFreq;
    stCurSysInfo.usSid              = pstOhmInd->usSid;
    stCurSysInfo.usNid              = pstOhmInd->usNid;

    ulIsNegSys = CNAS_XSD_Is1xSysNegative(&stCurSysInfo,
                                           pstOhmInd->enServiceInfoIncl,
                                           pstOhmInd->stServiceInfo.usMcc);

    /* Process the CAS OHM message to send Info to XREG and MMA */
    CNAS_XSD_ProcCasOhmInd(pstOhmInd, ulIsNegSys);

    if(VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        /* Quit the FSM with Abort result */
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_ABORTED);
    }
    else
    {
        /* Quit the FSM with Success result */
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_SUCCESS);
    }

    CNAS_XSD_QuitFsmRedir_Redir();

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* clear the Cache message buffer and save the power off request message */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasOhmInd
Description     :   Sets the Redirection FSM abort flag to True.
Input parameters:   ulEventType  - The event type of the power off camp on protect timer expired message
                    pstMsg       - pointer to power off camp on protect timer expired message structure.
Outout parameters:  None
Return Value    :   VOS_TRUE

Modify History:
    1)  Date    :   2014-12-26
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-3-7
        Author  :   w00176964
        Modify content : DTS2015012608600:�ػ���ʱ����ʱ���ټ�����OHM��Ϣ,ֱ���˳�������
*****************************************************************************/

VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Set Redirection abort flag to TRUE */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    CNAS_XSD_PerformAbortProcedure_Redir();

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   CNAS_XSD_RcvTiWaitCasOhmIndExpired_Redir_WaitCasOhmInd
Description     :   If Abort flag is true, the Redirection FSM is quit.
                    Else the next scan Redirection scan list is synced.
Input parameters:   ulEventType  - The event type of the power off camp on protect timer expired message
                    pstMsg       - pointer to power off camp on protect timer expired message structure.
Outout parameters:  None
Return Value    :   VOS_TRUE

Modify History:
    1)  Date    :   2014-12-26
        Author  :   a00295761
        Modify content :    Create

    2.��    ��   : 2015��1��05��
      ��    ��   : y00245242
      �޸�����   : ����OOC��������
    3.��    ��   : 2015��4��20��
      ��    ��   : w00242748
      �޸�����   : DTS2015041609529:����MRU0�����MRU0ͬ���ɹ�����û�취פ����
                   ����»ᵼ����ѭ��������
*****************************************************************************/

VOS_UINT32 CNAS_XSD_RcvTiWaitCasOhmIndExpired_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;

    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasOhmIndExpired_Redir_WaitCasOhmInd: timer out");

    /* If abort flag is true, the redirection FSM Is Aborted */
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        CNAS_XSD_PerformAbortProcedure_Redir();

        return VOS_TRUE;
    }

    /* Abort flag is false. Get the next Redirection scan list */

    usDstChanNum       = 0;
    NAS_MEM_SET_S(astDstChan, sizeof(astDstChan), 0 , sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

    pstScanList        = CNAS_XSD_GetScanChanListAddr_Redir();
    usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex_Redir();

    /* Continue the Redirection Flow by getting the next Redirection scan list */
    CNAS_XSD_GetNextScanChanList(usCurScanListIndex,
                                 &usDstChanNum,
                                 astDstChan,
                                 pstScanList,
                                 VOS_TRUE);

    /* If scan list is complete check the RETURN_IF_FAIL value */
    if (0 == usDstChanNum)
    {
        CNAS_XSD_ProcRedirScanListSyncComplete_Redir();
    }
    /* Send Sync Request to CAS */
    else
    {
        CNAS_XSD_ContinueSyncRedirScanList_Redir(usDstChanNum, astDstChan);
    }

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   CNAS_XSD_RcvCasSysDeterminInd_Redir_WaitCasOhmInd
Description     :   If Abort flag is true, the Redirection FSM is quit.
                    Else process the System determine Ind message from CAS.
Input parameters:   ulEventType  - The event type of the power off camp on protect timer expired message
                    pstMsg       - pointer to power off camp on protect timer expired message structure.
Outout parameters:  None
Return Value    :   VOS_TRUE

Modify History:
    1)  Date    :   2014-12-26
        Author  :   a00295761
        Modify content :    Create

    2.��    ��   : 2015��1��4��
      ��    ��   : y00245242
      �޸�����   : ����NDSS ORIG����

  3.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : DSDS Determine Ind No RF�Ĵ���
*****************************************************************************/

VOS_UINT32 CNAS_XSD_RcvCasSysDeterminInd_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq           = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList       = VOS_NULL_PTR;

    pstSysDeterminInd = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
     /* Stop The Wait OHM Message Protect timer */
        CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

        CNAS_XSD_PerformAbortProcedure_Redir();

        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_XSD_GetNdssIndFlag())
    {
        CNAS_XSD_SetNdssIndFlag(VOS_FALSE);

        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_FAILURE);
    }

    pstScanList                 = CNAS_XSD_GetScanChanListAddr_Redir();

    /* ��ȡ�ϴ�ͬ���ɹ���Ƶ�� */
    pstFreq = CNAS_XSD_GetLastSyncedFreq();

    CNAS_XSD_UpdateScanListChanStatusUponReceivedDeterminInd(CNAS_XSD_GetCurChannelScanIndex_Redir(),
                                                             pstFreq,
                                                             pstScanList);

    /* log scan list����״̬ */
    CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_SCAN_CHAN_LIST_IND, pstScanList);

    /* ���ΪNO RF������ʧ�ܵĴ��� */
    if (CAS_CNAS_1X_SD_NO_RF == pstSysDeterminInd->enSdReason)
    {
        /* Stop The Wait OHM Message Protect timer */
        CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_NORF);

        /* �˳����״̬�� */
        CNAS_XSD_QuitFsmRedir_Redir();

        return VOS_TRUE;
    }

    /* Process the different System determine indication reasons */
    switch (pstSysDeterminInd->enSdReason)
    {
        case CAS_CNAS_1X_SD_SYS_LOST_IND:
        case CAS_CNAS_1X_SD_NEW_SYSTEM_IND:
        case CAS_CNAS_1X_SD_ABNORMAL_IND:
        case CAS_CNAS_1X_SD_LOCK_IND:
        case CAS_CNAS_1X_SD_UNLOCK_IND:
        case CAS_CNAS_1X_SD_ACQUISITION_FAIL:

            /* Stop The Wait OHM Message Protect timer */
            CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

            CNAS_XSD_ContinueRedir_Redir();
            break;

       case CAS_CNAS_1X_SD_PROTO_MISMATCH_IND:

            CNAS_XSD_ProcCasSystemDetermineIndWithProtoMisReason_Redir(ulEventType, pstMsg);
            break;

        default:

            /* other reasons we think cas will continue send overhead message to us,so we still
               stay on the current state. */
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCasSysDeterminInd_Redir_WaitCasOhmInd: unknown reason");
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasOhmInd
Description     :   The function handles the Power Save Request in the Wait OHM Ind state.
Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   VOS_TRUE
Modify History:
    1)  Date    :   2015-04-04
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-05-28
        Author  :   w00176964
        Modify content :DTS2015052903319:power save�ڵ�OHM��Ϣʱ��Ҫ�ӳٴ��
*****************************************************************************/

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the Power Save Request in cache */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;

}

/*****************************************************************************
Function Name   :   CNAS_XSD_RcvCasSysSyncCnf_Redir_WaitCasSysSyncCnfOrigSys
Description     :   1) Receives sync conf result from CAS is SUCCESS or FAILURE
                    2) If SUCESS: Compares the synced system is original syste or not.
                                If SID ans NID are matched, sends campon request with synced sys to CAS, start timer.
                                If not matched send internal message and quit FSM
                    3) If FAILURE: Quit FSM

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2014-12-25
        Author  :   k902809
        Modify content :    Create
  2.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : DSDS SyncCnf NO RF�Ĵ���

  3.��    ��   : 2015��7��20��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasSysSyncCnf_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usRcvSid;
    VOS_UINT16                          usRcvNid;
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf      = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU            *pstRedirOrigSys = VOS_NULL_PTR;
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo        = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstEmcScanChanList  = VOS_NULL_PTR;

    pstEmcScanChanList                  = CNAS_XSD_GetEmcCallRedialScanChanListAddr();
    pstRedirInfo                        = CNAS_XSD_GetRedirectionInfoAddr();

    pstSyncCnf                  = (CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU *)pstMsg;

    /*Stop the protect timer*/
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* ���ΪNO RF������ʧ�ܵĴ��� */
    if (CNAS_CAS_1X_RSLT_NO_RF == pstSyncCnf->enSyncRslt)
    {
        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_NORF);

        /* �˳����״̬�� */
        CNAS_XSD_QuitFsmRedir_Redir();

        return VOS_TRUE;
    }

    /* �����������ض���ˢ��ͬ��ʧ�ܵ�Ƶ����Ϣ */
    if (VOS_TRUE == pstRedirInfo->ucIsEmcRedir)
    {
        if (VOS_NULL_PTR != pstEmcScanChanList->pstScanChanInfo)
        {
            (VOS_VOID)CNAS_XSD_UpdateSyncFailChanStatus(pstEmcScanChanList->usCurScanIndex,
                                                       (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                        pstSyncCnf->astSyncRsltList,
                                                        pstEmcScanChanList);
        }
    }

    /*Compare the sync result is success or not*/
    if (CNAS_CAS_1X_RSLT_SUCCESS == pstSyncCnf->enSyncRslt)
    {
        pstRedirOrigSys = CNAS_XSD_GetRedirectionOrignalSys();
        usRcvSid = pstSyncCnf->stSyncedSysId.usSid;
        usRcvNid = pstSyncCnf->stSyncedSysId.usNid;

        /* ���µ���ʷͬ���ɹ��б� */
        CNAS_XSD_UpdateHistorySyncedSysFreqList(&(pstRedirOrigSys->stFreq));

        /*Compare the synced system is original system*/
        if ((VOS_TRUE == CNAS_PRL_Is1xSysIdMatched(pstRedirOrigSys->usSid, pstRedirOrigSys->usNid,usRcvSid, usRcvNid))
         || (VOS_TRUE == pstRedirInfo->ucIsEmcRedir))
        {
            /*Notify CAS to camp on synced system*/
            CNAS_XSD_SndCas1xCampSyncedChannelNtf();

            /* transfer to CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND state, start timer */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_RET_ORIG_SYS_IND);
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);
            return VOS_TRUE;
        }
    }

    /*Sending Result*/
    CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_FAILURE);

    /* Quit Redirection FSM */
    CNAS_XSD_QuitFsmRedir_Redir();

    return VOS_TRUE;
}



VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Clearing the message queue */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    /* Saving Power off event in message queue */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* Start POWER OFF CAMP ON PROTECT timer */
    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*Stop TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF timer*/
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /*Set ABORT flag = 1 in redirection*/
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    /*Send Stop sync request to CAS*/
    CNAS_XSD_SndCasStopSysSyncReq();

    /*Set net state to CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS*/
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS);

    /*Start TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF protect timer*/
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32  CNAS_XSD_RcvTiWaitCasSysSyncCnfTimerExpired_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasSysSyncCnfTimerExpired_Redir_WaitCasSysSyncCnfOrigSys: Timer out");

    /* Send Stop sync request to CAS*/
    CNAS_XSD_SndCasStopSysSyncReq();

    /* Cahnge the next state to CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS);

    /*Start timer TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF*/
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Stop Sync Cnf protect timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* Save the Power Save Request in cache */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* Set Abort flag to true */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    /* Send Stop Sync Req to CAS */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* Set next State to Wait CAS Stop Sync Cnf and start the protect timer */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;

}




VOS_UINT32 CNAS_XSD_RcvCasStopSysSyncCnf_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*Stop Sys Sync stop protect timer*/
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF);

    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        /* send internal message with ABORT*/
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_ABORTED);
    }
    else
    {
        /* send internal message */
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_FAILURE);
    }

    CNAS_XSD_QuitFsmRedir_Redir();

    return VOS_TRUE;
}


VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;

}


VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectExpired_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        /* send internal message with ABORT*/
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_ABORTED);
    }
    else
    {
        /* send internal message */
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_FAILURE);
    }

    CNAS_XSD_QuitFsmRedir_Redir();

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the Power Save Request in cache */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* Set Abort flag to true */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;

}

/*****************************************************************************
Function Name   :   CNAS_XSD_RcvCasOhmInd_Redir_WaitCasOhmIndRetOrigSysInd
Description     :   1) Stop Wait OHM protect timer
                    2) Process OHM message
                    3) Send ind to XREG
                    4) Send ind to MMA
                    5) Send result to XSD with success
                    6) Quit FSM

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2014-12-26
        Author  :   k902809
        Modify content :    Create

    2.��    ��   : 2015��7��17��
      ��    ��   : y00245242
      �޸�����   : iteration 17����
    3.��    ��   : 2015��08��20��
      ��    ��   : t00323010
      �޸�����   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasOhmInd_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;
    VOS_UINT32                          ulIsNegSys;
    CAS_CNAS_1X_OHM_IND_STRU           *pstOhmInd = VOS_NULL_PTR;

    pstOhmInd = (CAS_CNAS_1X_OHM_IND_STRU *)pstMsg;

    /* Stop the Wait OHM Indication Protect timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    /* Process OHM message
    Send ind to XREG
    Send ind to MMA*/
    stCurSysInfo.stFreq.enBandClass = pstOhmInd->usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstOhmInd->usFreq;

    stCurSysInfo.usSid              = pstOhmInd->usSid;
    stCurSysInfo.usNid              = pstOhmInd->usNid;

    ulIsNegSys = CNAS_XSD_Is1xSysNegative(&stCurSysInfo,
                                           pstOhmInd->enServiceInfoIncl,
                                           pstOhmInd->stServiceInfo.usMcc);

    CNAS_XSD_ProcCasOhmInd(pstOhmInd, ulIsNegSys);

    if(VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        /* Quit the FSM with Abort result */
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_ABORTED);
    }
    else
    {
        /* Quit the FSM with Success result */
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_SUCCESS);
    }

    CNAS_XSD_QuitFsmRedir_Redir();

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* clear the Cache message buffer and save the power off request message */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   CNAS_XSD_RcvTiPowerOffCampOnProtectExpired_Redir_WaitCasOhmIndRetOrigSysInd
Description     :   1) Set Abort flag to 1

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2014-12-26
        Author  :   k902809
        Modify content :    Create
    2)  Date    :   2015-3-7
        Author  :   w00176964
        Modify content : DTS2015012608600:�ػ���ʱ����ʱ���ټ�����OHM��Ϣ,ֱ���˳�������
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectExpired_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Set Redirection abort flag to TRUE */
    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    CNAS_XSD_PerformAbortProcedure_Redir();

    return VOS_TRUE;
}


VOS_UINT32 CNAS_XSD_RcvTiWaitCasOhmIndExpired_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        /* send internal message with ABORT*/
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_ABORTED);
    }
    else
    {
        /* send internal message */
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_FAILURE);
    }

    /*Quiting FSM*/
    CNAS_XSD_QuitFsmRedir_Redir();

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   CNAS_XSD_RcvCasSysDeterminInd_Redir_WaitCasOhmIndRetOrigSysInd
Description     :   1) Check the SD message id
                    1) Check the FLAG and invalid message
                        Quit FSM
                    2) Else :
                        Search for redir message inside message queue and clear
                        Save to message queue and return

Input parameters:   ulEventType, *pstMsg
Output parameters:  None
Return Value    :   VOS_UINT32

Modify History:
    1)  Date    :   2014-12-26
        Author  :   k902809
        Modify content :    Create
  2.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : DSDS Determin Ind NO RF�Ĵ���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasSysDeterminInd_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd = VOS_NULL_PTR;

    pstSysDeterminInd = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    /* if ABORT FLAG is true, Quit the FSM with Abort result */
    if (VOS_TRUE == CNAS_XSD_GetAbortFlag_Redir())
    {
        CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

        CNAS_XSD_PerformAbortProcedure_Redir();

        return VOS_TRUE;
    }

    /* ���ΪNO RF������ʧ�ܵĴ��� */
    if (CAS_CNAS_1X_SD_NO_RF == pstSysDeterminInd->enSdReason)
    {
        /* Stop the Wait OHM Indication Protect timer */
        CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_NORF);

        /* �˳����״̬�� */
        CNAS_XSD_QuitFsmRedir_Redir();

        return VOS_TRUE;
    }

    switch (pstSysDeterminInd->enSdReason)
    {
        case CAS_CNAS_1X_SD_SYS_LOST_IND:
        case CAS_CNAS_1X_SD_NEW_SYSTEM_IND:
        case CAS_CNAS_1X_SD_ABNORMAL_IND:
        case CAS_CNAS_1X_SD_LOCK_IND:
        case CAS_CNAS_1X_SD_UNLOCK_IND:

            /* Stop the Wait OHM Indication Protect timer */
            CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

            CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_FAILURE);
            CNAS_XSD_QuitFsmRedir_Redir();
            break;

        case CAS_CNAS_1X_SD_PROTO_MISMATCH_IND:

            CNAS_XSD_ProcCasSystemDetermineIndWithProtoMisReason_Redir(ulEventType, pstMsg);
            break;

        default:

            /* other reasons we think cas will continue send overhead message to us,so we still
               stay on the current state. */
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCasSysDeterminInd_Redir_WaitCasOhmIndRetOrigSysInd: unknown reason");
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasOhmIndRetOrigSysInd
Description     :   The function handles the Power Save Request in the Wait OHM Ind Ret Orig Sys state.
Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   VOS_TRUE
Modify History:
    1)  Date    :   2015-04-04
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-05-28
        Author  :   w00176964
        Modify content :DTS2015052903319:power save�ڵ�OHM��Ϣʱ��Ҫ�ӳٴ��
*****************************************************************************/

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the Power Save Request in cache */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_XSD_SetAbortFlag_Redir(VOS_TRUE);

    return VOS_TRUE;

}


/*****************************************************************************
Function Name   :   CNAS_XSD_ProcCasSyncCnfSucc_Redir
Description     :   1. Updates the sync status Redirection scan list
                    2. Compares the expected SID, NID with synced SID, NID.
                    3. Sends Camp on notify to CAS if the comparison is success.
                    4. Gets next Redirection scan list if the comparison is failure.
Input parameters:   pstSyncCnf - The Sync result details of Redirection scan list sent by CAS.
Outout parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2014-12-25
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-07-13
        Author  :   m00312079
        Modify content :    DTS2015063003186 add returnCause logicals
     3.��    ��   : 2015��7��20��
       ��    ��   : h00313353
       �޸�����   : ����17 ������
*****************************************************************************/

VOS_VOID CNAS_XSD_ProcCasSyncCnfSucc_Redir(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstRedirScanList = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU                                 stCurSysInfo;
    VOS_UINT16                                              usCurScanListIndex;
    VOS_UINT16                                              usExpectedSid;
    VOS_UINT16                                              usExpectedNid;
    CNAS_XSD_REDIRECTION_INFO_STRU                         *pstRedirInfoStru = VOS_NULL_PTR;
    VOS_UINT16                                              usDstChanNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT32                                              ulIsNegSys;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstEmcScanChanList  = VOS_NULL_PTR;

    pstEmcScanChanList                  = CNAS_XSD_GetEmcCallRedialScanChanListAddr();
    pstRedirInfoStru                    = CNAS_XSD_GetRedirectionInfoAddr();

    ulIsNegSys = VOS_FALSE;


    /* Save the current synced system SID, NID, band class and channel */
    stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;
    stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
    stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;

    usCurScanListIndex      = CNAS_XSD_GetCurChannelScanIndex_Redir();
    pstRedirScanList        = CNAS_XSD_GetScanChanListAddr_Redir();

    /* Update the Redirection scan list state */
    CNAS_XSD_UpdateSyncSuccChanStatus((VOS_UINT8)usCurScanListIndex,
                                       &stCurSysInfo.stFreq,
                                       pstRedirScanList);

    CNAS_XSD_UpdateSyncFailChanStatus(usCurScanListIndex,
                                      (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                      pstSyncCnf->astSyncRsltList,
                                      pstRedirScanList);

    /* �����������ض���ˢ��ͬ��ʧ�ܵ�Ƶ����Ϣ */
    if (VOS_TRUE == pstRedirInfoStru->ucIsEmcRedir)
    {
        if (VOS_NULL_PTR != pstEmcScanChanList->pstScanChanInfo)
        {
            (VOS_VOID)CNAS_XSD_UpdateSyncFailChanStatus(pstEmcScanChanList->usCurScanIndex,
                                                       (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                        pstSyncCnf->astSyncRsltList,
                                                        pstEmcScanChanList);
        }
    }

    CNAS_XSD_SetCurChannelScanIndex_Redir(usCurScanListIndex + (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum + 1);

    /* ���µ���ʷͬ���ɹ��б� */
    CNAS_XSD_UpdateHistorySyncedSysFreqList(&stCurSysInfo.stFreq);

    CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_REDIR_SCAN_CHAN_LIST_IND, pstRedirScanList);

    /* Get expected SID and NID from Redirection Info Structure */

    usExpectedSid    = pstRedirInfoStru->usExpectSid;
    usExpectedNid    = pstRedirInfoStru->usExpectNid;

    if (VOS_TRUE == pstRedirInfoStru->ucIsEmcRedir)
    {
        if (VOS_TRUE == CNAS_PRL_Is1xSysIdMatched(stCurSysInfo.usSid, stCurSysInfo.usNid, usExpectedSid, usExpectedNid))
        {
            /* �������ض���ͬ���ɹ���ֱ��פ�� */
            CNAS_XSD_SndCas1xCampSyncedChannelNtf();

            /* Set next state to wait OHM indication and start Wait OHM indication Timer */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_IND);
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

            return;
        }
    }

    ulIsNegSys = CNAS_XSD_Is1xSysNegative(&stCurSysInfo, VOS_FALSE, 0);

    /* Check if synced system is listed in PRL as negative or not */
    if (VOS_TRUE == ulIsNegSys)
    {
        /* ����ϵͳ��negʱ����ˢ�¸�Ƶ��Ϊ�����ڣ������ˢ�µĻ�������ͬ����Ȼ��ͬ����Ƶ��
           ��ȡ��һ��ͬ��Ƶ��ʱ���߼�Ϊδͬ������ͬ������ */
        (VOS_VOID)CNAS_XSD_UpdateChanStatusInScanChanList(usCurScanListIndex,
                                                          &stCurSysInfo.stFreq,
                                                          CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                          pstRedirScanList);

        /* If synced system is listed as negative in the PRL, Continue to sync Redirection scan list */
        CNAS_XSD_ContinueRedir_Redir();
        return;
    }

    /* available list��ϵͳ����״̬��ʹ�ã�����ɾ��availableϵͳ��� */

    /* Compare synced SID, NID with the expected SID, NID */
    /* Send Camp on Notify to CAS only if the Synced SID, NID is equal to Expected SID, NID
       and the matched system is not Negative in PRL (CDG 143 4.5.6) */
    if ((VOS_TRUE  == CNAS_PRL_Is1xSysIdMatched(stCurSysInfo.usSid, stCurSysInfo.usNid, usExpectedSid, usExpectedNid)))
    {
        /* Expected SID, NID is equal to Synced SID, NID and System is not negative. send Camp On Notify to CAS */
        CNAS_XSD_SndCas1xCampSyncedChannelNtf();

        /* Set next state to wait OHM indication and start Wait OHM indication Timer */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_IND);
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);
        return;
    }

    /* ����ϵͳ��ƥ��ʱ����ˢ�¸�Ƶ��Ϊ�����ڣ������ˢ�µĻ�������ͬ����Ȼ��ͬ����Ƶ��
       ��ȡ��һ��ͬ��Ƶ��ʱ���߼�Ϊδͬ������ͬ������ */
    (VOS_VOID)CNAS_XSD_UpdateChanStatusInScanChanList(usCurScanListIndex,
                                                      &stCurSysInfo.stFreq,
                                                      CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                      pstRedirScanList);

    usDstChanNum       = 0;
    NAS_MEM_SET_S(astDstChan, sizeof(astDstChan), 0 , sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

    CNAS_XSD_GetNextScanChanList(usCurScanListIndex, &usDstChanNum, astDstChan, pstRedirScanList, VOS_TRUE);

    /* If Redirection scan list is empty, check the RETURN_IF_FAIL flag  */
    if (0 == usDstChanNum)
    {
        if ((stCurSysInfo.usNid != usExpectedNid)
         && (stCurSysInfo.usNid != CNAS_PRL_WILDCARD_NID))
        {
            CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_WRONG_NID);
        }

        if ((stCurSysInfo.usSid != usExpectedSid)
         && (stCurSysInfo.usSid != CNAS_PRL_WILDCARD_SID))
        {
            CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_WRONG_SID);
        }

        CNAS_XSD_ProcRedirScanListSyncComplete_Redir();
    }
    /* Continue to sync the channels from the redirection scan list. */
    else
    {
        CNAS_XSD_ContinueSyncRedirScanList_Redir(usDstChanNum, astDstChan);
    }
    return;
}


/*****************************************************************************
Function Name   :   CNAS_XSD_ProcCasSyncCnfFail_Redir
Description     :   Gets next redirection scan list and continues to sync.
                    If the redirection scan list is empty, the RETURN_IF_FAIL value is judged
                    to determine the next state.
Input parameters:   pstSyncCnf - pointer to Sync Cnf structure
Outout parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2014-12-25
        Author  :   a00295761
        Modify content :    Create

    2.��    ��   : 2015��1��05��
      ��    ��   : y00245242
      �޸�����   : ����OOC��������
    3.��    ��   : 2015��4��20��
      ��    ��   : w00242748
      �޸�����   : DTS2015041609529:����MRU0�����MRU0ͬ���ɹ�����û�취פ����
                   ����»ᵼ����ѭ��������
    4.��    ��   : 2015��07��13��
      ��    ��   : m00312079
      �޸�����   : DTS2015063003186 ���ά��returnCause���߼�
*****************************************************************************/

VOS_VOID CNAS_XSD_ProcCasSyncCnfFail_Redir(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstEmcScanChanList  = VOS_NULL_PTR;

    pstEmcScanChanList                  = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

    pstScanList                 = CNAS_XSD_GetScanChanListAddr_Redir();
    usCurScanListIndex          = CNAS_XSD_GetCurChannelScanIndex_Redir();

    /* Update the redirection scan list status for failed frequencies */
    CNAS_XSD_UpdateSyncFailChanStatus(usCurScanListIndex,
                                      (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                      pstSyncCnf->astSyncRsltList,
                                      pstScanList);

    /* �����������ض���ˢ��ͬ��ʧ�ܵ�Ƶ����Ϣ */
    if (VOS_TRUE == CNAS_XSD_GetRedirectionInfoAddr()->ucIsEmcRedir)
    {
        if (VOS_NULL_PTR != pstEmcScanChanList->pstScanChanInfo)
        {
            (VOS_VOID)CNAS_XSD_UpdateSyncFailChanStatus(pstEmcScanChanList->usCurScanIndex,
                                                       (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                        pstSyncCnf->astSyncRsltList,
                                                        pstEmcScanChanList);
        }
    }

    CNAS_XSD_SetCurChannelScanIndex_Redir(usCurScanListIndex + (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum);

    CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_REDIR_SCAN_CHAN_LIST_IND, pstScanList);


    usDstChanNum       = 0;
    NAS_MEM_SET_S(astDstChan, sizeof(astDstChan), 0 , sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

    CNAS_XSD_GetNextScanChanList(usCurScanListIndex,
                                 &usDstChanNum,
                                 astDstChan,
                                 pstScanList,
                                 VOS_TRUE);

    /* If the scan list is empty  */
    if (0 == usDstChanNum)
    {
        CNAS_XSD_UpdateReturnCauseValue((VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                         pstSyncCnf->astSyncRsltList);
        CNAS_XSD_ProcRedirScanListSyncComplete_Redir();
    }
    /* if the scan list is not empty, send Sync Request to CAS */
    else
    {
        CNAS_XSD_ContinueSyncRedirScanList_Redir(usDstChanNum, astDstChan);
    }

    return;
}




VOS_VOID CNAS_XSD_ContinueSyncRedirScanList_Redir(
    VOS_UINT16                          usDstChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan
)
{
    CNAS_XSD_SndCasSysSyncReq(usDstChanNum, pstDstChan);

    /* Set next state to CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF and start the protect timer  */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF, usDstChanNum * TI_CNAS_XSD_WAIT_CAS_SYNC_ONE_FREQ_LEN + 5);

    return;
}




VOS_VOID CNAS_XSD_ProcRedirScanListSyncComplete_Redir(VOS_VOID)
{
    VOS_UINT16                          usDstChanNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstOrigSysChan = VOS_NULL_PTR;

    /* Get Original system band class and channel */
    pstOrigSysChan = (&((CNAS_XSD_GetRedirectionOrignalSys())->stFreq));

    /* If Return_If_Fail value is true, attempt to Sync Original System */
    if (VOS_TRUE == CNAS_XSD_GetRedirectionReturnIfFailFlag())
    {
        /* Disable the Redirection global Flag */
        CNAS_XSD_SetRedirectionFlag(VOS_FALSE);
        usDstChanNum = 1;
        CNAS_XSD_SndCasSysSyncReq(usDstChanNum, pstOrigSysChan);

        /* Set next state to CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF and start the protect timer  */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF_RET_ORIG_SYS);
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF, usDstChanNum * TI_CNAS_XSD_WAIT_CAS_SYNC_ONE_FREQ_LEN + 5);
        return;
    }

    /* Disable the Redirection global Flag */
    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_REDIRECTION_FAIL, pstOrigSysChan);

    /* Send failure result and quit the redirection FSM */
    CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_FAILURE);
    CNAS_XSD_QuitFsmRedir_Redir();

    return;
}




VOS_VOID CNAS_XSD_PerformAbortProcedure_Redir(VOS_VOID)
{
    /* Stop the power off protect timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER);

    /* Send Internal Abort Result and quit the Redirection FSM */
    CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_ABORTED);

    CNAS_XSD_QuitFsmRedir_Redir();

    return;
}


VOS_UINT32 CNAS_XSD_ProcCasSystemDetermineIndWithProtoMisReason_Redir(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd;

    pstSysDeterminInd   = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    /* Stop the Wait OHM Indication Protect timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_P_REV_MISMATCH, (CNAS_PRL_FREQENCY_CHANNEL_STRU *)(&(pstSysDeterminInd->stCurChannelInfo)));

    if (CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_IND == CNAS_XSD_GetFsmTopState())
    {
        /* continue sync */
        CNAS_XSD_ContinueRedir_Redir();
    }
    else
    {
        CNAS_XSD_SndRedirRslt(CNAS_XSD_REDIRECTION_RESULT_FAILURE);
        CNAS_XSD_QuitFsmRedir_Redir();
    }

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   CNAS_XSD_ContinueRedir_Redir
Description     :   Continues the Redirection flow by getting the next Redirection scan list
Input parameters:   None
Output parameters:  None
Return Value    :   VOS_TRUE

Modify History:
    1)  Date    :   2014-12-29
        Author  :   a00295761
        Modify content :    Create

    2.��    ��   : 2015��1��05��
      ��    ��   : y00245242
      �޸�����   : ����OOC��������
    3.��    ��   : 2015��4��20��
      ��    ��   : w00242748
      �޸�����   : DTS2015041609529:����MRU0�����MRU0ͬ���ɹ�����û�취פ����
                   ����»ᵼ����ѭ��������
*****************************************************************************/

VOS_VOID CNAS_XSD_ContinueRedir_Redir(VOS_VOID)
{
    VOS_UINT16                                              usCurScanListIndex;
    VOS_UINT16                                              usDstChanNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList = VOS_NULL_PTR;

    usDstChanNum       = 0;
    NAS_MEM_SET_S(astDstChan, sizeof(astDstChan), 0 , sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

    pstScanList        = CNAS_XSD_GetScanChanListAddr_Redir();
    usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex_Redir();

    CNAS_XSD_GetNextScanChanList(usCurScanListIndex,
                                 &usDstChanNum,
                                 astDstChan,
                                 pstScanList,
                                 VOS_TRUE);

    /* If Redirection scan list is empty, check the RETURN_IF_FAIL flag  */
    if (0 == usDstChanNum)
    {
        CNAS_XSD_ProcRedirScanListSyncComplete_Redir();
    }
    /* Continue to sync the channels from the redirection scan list. */
    else
    {
        CNAS_XSD_ContinueSyncRedirScanList_Redir(usDstChanNum, astDstChan);
    }
}



VOS_VOID CNAS_XSD_QuitFsmRedir_Redir(VOS_VOID)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList = VOS_NULL_PTR;
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo    = VOS_NULL_PTR;
    VOS_UINT16                          i;

    pstScanChanList          = CNAS_XSD_GetScanChanListAddr_Redir();
    pstRedirInfo             = CNAS_XSD_GetRedirectionInfoAddr();

    if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
    {
        for (i = 0; i < pstScanChanList->usTotalNum; i++)
        {
            pstRedirInfo->astChanInfo[i].enChanStatus           = pstScanChanList->pstScanChanInfo[i].enChanStatus;
            pstRedirInfo->astChanInfo[i].stFreqChan.enBandClass = pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass;
            pstRedirInfo->astChanInfo[i].stFreqChan.usChannel   = pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel;
        }

        pstRedirInfo->usCurScanIndex  = pstScanChanList->usCurScanIndex;

        /* Deallocate the memory for redirection scan list */
        PS_MEM_FREE(UEPS_PID_XSD, pstScanChanList->pstScanChanInfo);
        pstScanChanList->pstScanChanInfo = VOS_NULL_PTR;
    }

    pstScanChanList->usTotalNum     = 0;
    pstScanChanList->usCurScanIndex = 0;

    /* Quit the FSM */
    CNAS_XSD_QuitFsmL2();
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasSysSyncCnf
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF״̬�յ�ID_MSCC_XSD_MO_CALL_END_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo    = VOS_NULL_PTR;

    pstRedirInfo                            = CNAS_XSD_GetRedirectionInfoAddr();
    pstRedirInfo->ucIsEmcRedir              = VOS_FALSE;

    /* ���ԭϵͳ��ֹפ����Negϵͳ */
    pstRedirInfo->stOriginalSystem.usSid    = CNAS_PRL_WILDCARD_SID;
    pstRedirInfo->stOriginalSystem.usNid    = CNAS_PRL_WILDCARD_NID;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasSysSyncCnfOrigSys
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_SYNC_CNF_RET_ORIG_SYS״̬�յ�ID_MSCC_XSD_MO_CALL_END_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo    = VOS_NULL_PTR;

    pstRedirInfo                            = CNAS_XSD_GetRedirectionInfoAddr();
    pstRedirInfo->ucIsEmcRedir              = VOS_FALSE;

    /* ���ԭϵͳ��ֹפ����Negϵͳ */
    pstRedirInfo->stOriginalSystem.usSid    = CNAS_PRL_WILDCARD_SID;
    pstRedirInfo->stOriginalSystem.usNid    = CNAS_PRL_WILDCARD_NID;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasOhmInd
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_IND״̬�յ�ID_MSCC_XSD_MO_CALL_END_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo    = VOS_NULL_PTR;

    pstRedirInfo                            = CNAS_XSD_GetRedirectionInfoAddr();
    pstRedirInfo->ucIsEmcRedir              = VOS_FALSE;

    /* ���ԭϵͳ��ֹפ����Negϵͳ */
    pstRedirInfo->stOriginalSystem.usSid    = CNAS_PRL_WILDCARD_SID;
    pstRedirInfo->stOriginalSystem.usNid    = CNAS_PRL_WILDCARD_NID;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasOhmIndRetOrigSysInd
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_OHM_RET_ORIG_SYS_IND״̬�յ�ID_MSCC_XSD_MO_CALL_END_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasOhmIndRetOrigSysInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo    = VOS_NULL_PTR;

    pstRedirInfo                            = CNAS_XSD_GetRedirectionInfoAddr();
    pstRedirInfo->ucIsEmcRedir              = VOS_FALSE;

    /* ���ԭϵͳ��ֹפ����Negϵͳ */
    pstRedirInfo->stOriginalSystem.usSid    = CNAS_PRL_WILDCARD_SID;
    pstRedirInfo->stOriginalSystem.usNid    = CNAS_PRL_WILDCARD_NID;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasStopSysSyncCnf
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF״̬�յ�ID_MSCC_XSD_MO_CALL_END_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo    = VOS_NULL_PTR;

    pstRedirInfo                            = CNAS_XSD_GetRedirectionInfoAddr();
    pstRedirInfo->ucIsEmcRedir              = VOS_FALSE;

    /* ���ԭϵͳ��ֹפ����Negϵͳ */
    pstRedirInfo->stOriginalSystem.usSid    = CNAS_PRL_WILDCARD_SID;
    pstRedirInfo->stOriginalSystem.usNid    = CNAS_PRL_WILDCARD_NID;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasStopSysSyncCnfOrigSys
 ��������  : CNAS_XSD_REDIR_STA_WAIT_CAS_STOP_SYNC_CNF_RET_ORIG_SYS״̬�յ�ID_MSCC_XSD_MO_CALL_END_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_Redir_WaitCasStopSysSyncCnfOrigSys(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo    = VOS_NULL_PTR;

    pstRedirInfo                            = CNAS_XSD_GetRedirectionInfoAddr();
    pstRedirInfo->ucIsEmcRedir              = VOS_FALSE;

    /* ���ԭϵͳ��ֹפ����Negϵͳ */
    pstRedirInfo->stOriginalSystem.usSid    = CNAS_PRL_WILDCARD_SID;
    pstRedirInfo->stOriginalSystem.usNid    = CNAS_PRL_WILDCARD_NID;

    return VOS_TRUE;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


