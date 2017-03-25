/*******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdFsmSysAcq.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��07��28��
  ��������   : 1X SD SYSTEM ACQUIRE״̬���¼�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��28��
    ��    ��   : l60609
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasCcb.h"
#include  "CnasPrlApi.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "CnasXsdSndMscc.h"
#include  "CnasXsdSndCas.h"
#include  "CnasXsdFsmSysAcq.h"
#include  "CnasXsdFsmSysAcqTbl.h"
#include  "CnasXsdSysAcqStrategy.h"
#include  "CnasMntn.h"
#include  "CnasXsdMntn.h"
#include  "CnasTimerMgmt.h"
#include  "CnasXsdSndXreg.h"

#include "CnasXsdSndXcc.h"

#include "NasMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_SYS_ACQ_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
EXTERN VOS_UINT32                       g_CtrlCallRelScanList;

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Init
 ��������  : CNAS_XSD_SYS_ACQ_STA_INIT״̬�յ�ID_MMA_XSD_SYSTEM_ACQUIRE_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��30��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��05��
    ��    ��   : y00245242
    �޸�����   : ����OOC��������
  3.��    ��   : 2015��12��10��
    ��    ��   : l00324781
    �޸�����   : CL_MUTIMODE_OPTIMIZE�޸ģ����ӳ��� SWITCH_ON_INIT_SEARCH
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;
    MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU   *pstSysAcqReq = VOS_NULL_PTR;

    /* ���������Ϣ */
    CNAS_XSD_SaveCurEntryMsg(ulEventType, pstMsg);

    pstScanList = CNAS_XSD_GetScanChanListAddr();

    /* ����scan list */
    pstSysAcqReq = (MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU*)pstMsg;

    /* enSysAcqType����NORMAL����ʾ������פ�����󣬷������޿�������Xģ���ѣ�ֻΪ�˻�ȡ��ǰ�ֻ���λ����Ϣ
       ֻͬ�����ų���Ƶ�㣬������Ƶ��ͬ����ͬ����������ȴ�ϵͳ��Ϣ
    */
    if (MSCC_XSD_SYS_ACQ_TYPE_NORMAL == pstSysAcqReq->enSysAcqType)
    {
        CNAS_XSD_BuildScanChanList(CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR, pstScanList);
    }
    else
    {
        CNAS_XSD_BuildScanChanList(CNAS_XSD_SYS_ACQ_SCENE_POWER_ON_INIT_SEARCH, 0, VOS_NULL_PTR, pstScanList);
    }

    /* �����scan listΪ�� */
    if (0 == pstScanList->usTotalNum)
    {
        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE, CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON,VOS_FALSE);

        /* �˳����״̬�� */
        CNAS_XSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    /* ��״̬���������г�ʼ��available list */

    usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();

    usDstChanNum       = 0;

    /* ��ȡ�������ɨ���Ƶ���б� */
    CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);

    /* ��CAS����ID_CNAS_CAS_1X_SYSTEM_SYNC_REQ */
    CNAS_XSD_SndCasSysSyncReq(usDstChanNum, astDstChan);

    /* ��MSCC����ID_XSD_MSCC_SYSTEM_ACQUIRE_START_IND */
    CNAS_XSD_SndMsccSysAcqStartInd();

    /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF, usDstChanNum * TI_CNAS_XSD_WAIT_CAS_SYNC_ONE_FREQ_LEN + 5);

    CNAS_XSD_SetSystemCampOnFlag(VOS_FALSE);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXsdSysAcqReq_SysAcq_Init
 ��������  : CNAS_XSD_SYS_ACQ_STA_INIT״̬�յ�ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��5��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��5��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 6 Modified

  3.��    ��   : 2015��1��08��
    ��    ��   : y00245242
    �޸�����   : ����OOC��������

  4.��    ��   : 2015��7��20��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdSysAcqReq_SysAcq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU                  *pstIntSysAcqReq         = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList             = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                                              usCurScanListIndex;
    VOS_UINT16                                              usDstChanNum;

    /* ���������Ϣ */
    CNAS_XSD_SaveCurEntryMsg(ulEventType, pstMsg);

    pstIntSysAcqReq   = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU *)pstMsg;
    pstScanList       = CNAS_XSD_GetScanChanListAddr();

    CNAS_XSD_BuildScanChanList(pstIntSysAcqReq->enSysAcqScene, (VOS_UINT16)(pstIntSysAcqReq->ulFreqNum), &pstIntSysAcqReq->astFreq[0], pstScanList);

    /* �����scan listΪ�� */
    if (0 == pstScanList->usTotalNum)
    {
        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE, pstIntSysAcqReq->enSysAcqScene,CNAS_XSD_IsImmediateSysAcq_SysAcq());


        /* �˳����״̬�� */
        CNAS_XSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    /* ��״̬���������г�ʼ��available list */

    usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();
    usDstChanNum       = 0;

    /* ��ȡ�������ɨ���Ƶ���б� */
    CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);


    if (0 == usDstChanNum)
    {
        /* If Scan list is empty, quit the FSM with Fail Result */
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE, pstIntSysAcqReq->enSysAcqScene,CNAS_XSD_IsImmediateSysAcq_SysAcq());

        CNAS_XSD_QuitFsmSysAcq_SysAcq();
        return VOS_TRUE;
    }

    /* ��CAS����ID_CNAS_CAS_1X_SYSTEM_SYNC_REQ */
    CNAS_XSD_SndCasSysSyncReq(usDstChanNum, astDstChan);

    /* ��MSCC����ID_XSD_MSCC_SYSTEM_ACQUIRE_START_IND */
    CNAS_XSD_SndMsccSysAcqStartInd();

    /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF, usDstChanNum * TI_CNAS_XSD_WAIT_CAS_SYNC_ONE_FREQ_LEN + 5);

    CNAS_XSD_SetSystemCampOnFlag(VOS_FALSE);
    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF״̬�յ�ID_CAS_CNAS_1X_SYSTEM_SYNC_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��30��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasSysSyncCnf_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf = VOS_NULL_PTR;

    pstSyncCnf = (CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* ����ͬ��ȷ�Ͻ�� */
    switch (pstSyncCnf->enSyncRslt)
    {
        case CNAS_CAS_1X_RSLT_FAILURE:
        default:
            CNAS_XSD_ProcCasSyncCnfFail_SysAcq(pstSyncCnf);
            break;

        case CNAS_CAS_1X_RSLT_SUCCESS:
            CNAS_XSD_ProcCasSyncCnfSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_CAS_1X_RSLT_NO_RF:
            CNAS_XSD_ProcCasSyncCnfNoRf_SysAcq();
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF״̬��ID_CAS_CNAS_1X_SYS-
             TEM_SYNC_CNF��Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasSysSyncCnfExpired_SysAcq_WaitCasSysSyncCnf: timer out");

    /* ��CAS����ID_CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ��Ϣֹͣͬ�� */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf
 ��������  : �ȴ�CAS��ϵͳͬ���ظ�״̬�յ��ػ�����Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ջ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ջ��� */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    /* ����ػ����� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasSysSyncCnf
 ��������  : �ȴ�CAS��ϵͳͬ���ظ�״̬�յ��ػ�������ʱ���ĳ�ʱ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* ��CAS����ID_CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ��Ϣֹͣͬ�� */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasSysSyncCnf
 ��������  : �ȴ�CAS��ϵͳͬ���ظ�״̬�յ��յ�available��ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SetOocWaitSearchFlag(VOS_TRUE);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��������ȼ���Ϻ�֮ǰ��ϵĻ�����Ϣ */
    if (VOS_TRUE == CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ))
    {
        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);
    }

    /* ��ջ��� */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    /* Stop Sync Cnf protect timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* Save the Power Save Request in cache */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* Set Abort flag to true */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* Send Stop Sync Req to CAS */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* Set next State to Wait CAS Stop Sync Cnf and start the protect timer */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasOhmInd_SysAcq_WaitCasOhmInd
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬�յ�ID_CAS_CNAS_1X_OHM_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��9��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

  3.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasOhmInd_SysAcq_WaitCasOhmInd(
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

    /* �������availableϵͳ��ˢ��overheader�ϱ���Ƶ����Ϣ */
    if (VOS_FALSE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        /* ����overheader�ϱ���Ƶ�㵽CCB�� */
        CNAS_CCB_SetCdmaOhmFreq(&(stCurSysInfo.stFreq));
    }

    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo,
                                                 pstOhmInd->enServiceInfoIncl,
                                                 pstOhmInd->stServiceInfo.usMcc);

    if (VOS_TRUE == ulIsNegSys)
    {
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCasOhmInd_SysAcq_WaitCasOhmInd: The CAS Ind System is Neg!");
    }

    CNAS_XSD_ProcCasOhmInd(pstOhmInd, ulIsNegSys);

    if(VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                               CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_XSD_IsImmediateSysAcq_SysAcq());
    }
    else
    {
        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_SUCCESS, CNAS_XSD_GetCurSysAcqScene_SysAcq(), VOS_FALSE);
    }

    /* �˳����״̬�� */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasSysDeterminInd_SysAcq_WaitCasOhmInd
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬�յ�ID_CAS_CNAS_1X_SYSTEM_DETERMIN_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��13��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��25��
    ��    ��   : w00176964
    �޸�����   : CDMA Iteration 6 Modified:Add other SD reason
  3.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : DSDS NO RF����
  4.��    ��   : 2015��7��9��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
  5.��    ��   : 2015��9��11��
    ��    ��   : y00245242
    �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasSysDeterminInd_SysAcq_WaitCasOhmInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq           = VOS_NULL_PTR;

    pstSysDeterminInd = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    /* �д�ϱ����Ҫ�˳� */
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        /* ֹͣ������ʱ�� */
        CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

        CNAS_XSD_PerformAbortProcedure_SysAcq();

        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_XSD_GetNdssIndFlag())
    {
        CNAS_XSD_SetNdssIndFlag(VOS_FALSE);

        CNAS_XSD_SndXccNdssResultInd(XSD_XCC_NDSS_RESULT_FAILURE);
    }

    /* ��ȡ�ϴ�ͬ���ɹ���Ƶ�� */
    pstFreq = CNAS_XSD_GetLastSyncedFreq();

    /***********************************************************************************************
     * 1. ˢ��scan list���ϴ�ͬ���ɹ���Ƶ��Ϊ����������
     **********************************************************************************************/
    CNAS_XSD_UpdateChanStatusUponRcvCasDeterminInd_SysAcq(pstFreq);



    /***********************************************************************************************
     * 2. GEOϵͳ��¼�����б����ʱ��ˢ��GEOϵͳ��¼�����б��е�Ƶ��Ϊ����������
     **********************************************************************************************/
    if (VOS_NULL_PTR != CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo)
    {
        CNAS_XSD_UpdateGeoSysRecordStatusUponReceivedDeterminInd(pstFreq);
    }

    switch (pstSysDeterminInd->enSdReason)
    {
        case CAS_CNAS_1X_SD_SYS_LOST_IND:
        case CAS_CNAS_1X_SD_NEW_SYSTEM_IND:
        case CAS_CNAS_1X_SD_ABNORMAL_IND:
        case CAS_CNAS_1X_SD_LOCK_IND:
        case CAS_CNAS_1X_SD_UNLOCK_IND:
        case CAS_CNAS_1X_SD_RESCAN_IND:
        case CAS_CNAS_1X_SD_ACQUISITION_FAIL:
            CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

            CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

            CNAS_XSD_ContinueSysSync_SysAcq();
            break;

        case CAS_CNAS_1X_SD_PROTO_MISMATCH_IND:
            CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

            CNAS_XSD_ProcCasSystemDetermineIndWithProtoMisReason_SysAcq(ulEventType, pstMsg);
            break;

        /* ���ΪNO RF������ʧ�ܵĴ��� */
        case CAS_CNAS_1X_SD_NO_RF:
            CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

            CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

            /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
            CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE, CNAS_XSD_SYS_ACQ_SCENE_NO_RF, VOS_FALSE);

            /* �˳����״̬�� */
            CNAS_XSD_QuitFsmSysAcq_SysAcq();
            break;

        default:

            /* other reasons we think cas will continue send overhead message to us,so we still
               stay on the current state. */
            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCasSysDeterminInd_SysAcq_WaitCasOhmInd: unknown reason");
            break;
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬��ID_CAS_CNAS_1X_OHM_-
             IND��Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��17��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasOhmIndExpired_SysAcq_WaitCasOhmInd: timer out");

    /* ��ˢ��SCAN LISTƵ��״̬ */

    /* �д�ϱ����Ҫ�˳� */
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        CNAS_XSD_PerformAbortProcedure_SysAcq();

        return VOS_TRUE;
    }

    CNAS_XSD_ContinueSysSync_SysAcq();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasOhmInd
 ��������  : �ȴ�CAS��ϵͳ��Ϣ״̬�յ��ػ�����Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ջ���
  3.��    ��   : 2015��8��6��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstLastSyncedSys       = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU             st1xSysInfo;

    NAS_MEM_SET_S(&st1xSysInfo, sizeof(st1xSysInfo), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));
    pstLastSyncedSys                    = CNAS_XSD_GetLastSyncedSys();

    st1xSysInfo.usSid                   = pstLastSyncedSys->usSid;
    st1xSysInfo.usNid                   = pstLastSyncedSys->usNid;
    st1xSysInfo.stFreq                  = CNAS_XSD_GetHistorySyncedSysFreqList()->astFreq[0];

    /* ��ջ��� */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    /* ����ػ����� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����ǰϵͳ��Ч,������� */
    if (VOS_TRUE == CNAS_XSD_IsCurSysNotSuitableSys(&st1xSysInfo, VOS_FALSE, 0))
    {
        CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                               CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_XSD_IsImmediateSysAcq_SysAcq());

        /* �˳����״̬�� */
        CNAS_XSD_QuitFsmSysAcq_SysAcq();

        return VOS_TRUE;
    }

    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasOhmInd
 ��������  : �ȴ�CAS��ϵͳ��Ϣ״̬�յ��ػ�פ��������ʱ����ʱ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��10��11��
    ��    ��   : w00176964
    �޸�����   : DTS2015012608600:�ػ���ʱ����ʱ���ټ�����OHM��Ϣ,ֱ���˳�������
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    CNAS_XSD_PerformAbortProcedure_SysAcq();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasOhmInd
 ��������  : �ȴ�CAS��ϵͳ��Ϣ�����У��յ�available��ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SetOocWaitSearchFlag(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasOhmInd
Description     :   The function handles the power save request from MSCC in the wait OHM Ind State.

Input parameters:   ulEventType   - Event type of the message.
                    pstMsg        - POinter to the message.
Outout parameters:  None
Return Value    :   VOS_TRUE
Modify History:
    1)  Date    :   2014-01-31
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-05-28
        Author  :   w00176964
        Modify content :DTS2015052903319:power save�ڵ�OHM��Ϣʱ��Ҫ�ӳٴ��
*****************************************************************************/

VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstLastSyncedSys       = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU             st1xSysInfo;

    NAS_MEM_SET_S(&st1xSysInfo, sizeof(st1xSysInfo), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));
    pstLastSyncedSys                    = CNAS_XSD_GetLastSyncedSys();

    /* ��������ȼ���Ϻ�֮ǰ��ϵĻ�����Ϣ */
    if (VOS_TRUE == CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ))
    {
        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);
    }

    /* ��ջ��� */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    st1xSysInfo.usSid                   = pstLastSyncedSys->usSid;
    st1xSysInfo.usNid                   = pstLastSyncedSys->usNid;
    st1xSysInfo.stFreq                  = CNAS_XSD_GetHistorySyncedSysFreqList()->astFreq[0];

    /* �����������У���ϴ��� */
    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����ǰϵͳ��Ч���ӳٴ�� */
    if (VOS_TRUE != CNAS_XSD_IsCurSysNotSuitableSys(&st1xSysInfo, VOS_FALSE, 0))
    {
        /* ����״̬����ϱ�� */
        CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

        return VOS_TRUE;
    }

    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                           CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                           CNAS_XSD_IsImmediateSysAcq_SysAcq());

    /* �˳����״̬�� */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF״̬�յ�ID_CAS_CNAS_1X_STOP_SYSTEM_SYNC_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��05��
    ��    ��   : y00245242
    �޸�����   : ����OOC��������

  3.��    ��   : 2015��7��9��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasStopSysSyncCnf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ֹͣ������ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF);

    /***********************************************************************************************
     * 1. ����������
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        CNAS_XSD_PerformAbortProcedure_SysAcq();

        return VOS_TRUE;
    }

    /***********************************************************************************************
     * 2. ��������ͬ��
     **********************************************************************************************/
    CNAS_XSD_ContinueSysSync_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF״̬��ID_CAS_CNAS_1-
             X_STOP_SYSTEM_SYNC_CNF��Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��05��
    ��    ��   : y00245242
    �޸�����   : ����OOC��������

  3.��    ��   : 2015��7��9��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasStopSysSyncCnfExpired_SysAcq_WaitCasStopSysSyncCnf: timer out");

    /***********************************************************************************************
     * 1. ����������
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        CNAS_XSD_PerformAbortProcedure_SysAcq();

        return VOS_TRUE;
    }

    /***********************************************************************************************
     * 2. ��������ͬ��
     **********************************************************************************************/
    CNAS_XSD_ContinueSysSync_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf
 ��������  : �ȴ�CAS��ֹͣϵͳͬ���ظ�״̬�յ��ػ�����Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ջ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccPowerOffReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ջ��� */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    /* ����ػ����� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER, TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiPowerOffProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf
 ��������  : �ȴ�CAS��ֹͣϵͳͬ���ظ�״̬�յ��ػ�������ʱ����ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiPowerOffCampOnProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasStopSysSyncCnf
 ��������  : �ȴ�CAS��ֹͣϵͳͬ�������У��յ�available��ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiAvailableTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SetOocWaitSearchFlag(VOS_TRUE);

    return VOS_TRUE;
}



VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��������ȼ���Ϻ�֮ǰ��ϵĻ�����Ϣ */
    if (VOS_TRUE == CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ))
    {
        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);
    }

    /* ��ջ��� */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(CNAS_XSD_INIT_CTX_POWEROFF, &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    /* Save the Power Save Request in cache */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* Set Abort flag to true */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 FUNCTION NAME    : CNAS_XSD_PerformBestPreferedSystemSelectionAfterSyncSucc_SysAcq
 DESCRIPTION      : process system selection while the acquire mode is best prefered,in this case,we
                    have to find the best prefered system in PRL
 INPUT PARAMETER  : pstSyncCnf  -- ͬ��ȷ����Ϣ
 OUTPUT PARAMETER : none
 RETURN           : none
 CALLING FUNCTION :
 CALLED FUNCTION  :

 History modification:
  1.DATE         : 21/8/2014
    EDITOR       : y00245242
    MODIFICATION : create

  2.DATE         : 5/1/2015
    EDITOR       : w00176964
    MODIFICATION : CDMA 1X Iteration 6 Modifed:modified the function name

  3.��    ��   : 2015��1��12��
    ��    ��   : y00245242
    �޸�����   : ����OOC��������

  4.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformBestPreferedSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;

    /***********************************************************************************************
     * 1.����GEOϵͳ��¼�����б����ڵĳ���
     **********************************************************************************************/
    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        /* GEOϵͳ��¼�����б����ڵĴ��� */
        CNAS_XSD_PreformBestPreferedSystemSelectionAndNoGeoSysRecordSearchList_SysAcq(pstSyncCnf);

        return;
    }

    /***********************************************************************************************
     * 2.����GEOϵͳ��¼�����б���ڵĳ���
     **********************************************************************************************/
    CNAS_XSD_PreformBestPreferedSystemSelectionAndGeoSysRecordSearchListExist_SysAcq(pstSyncCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_PerformNormalCallRedialSystemSeletion_SysAcq
 ��������  : Do system selection on normal call redial scene

 �������  : pstCurSysInfo  -- the current system synchronized.
             pstGeoListInfo -- GEO list information of the synchronized system

 �������  : none

 �� �� ֵ  : VOS_TRUE  -- current system can be camped on
             VOS_FALSE -- current system is not suitable to camp on
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 27/11/2014
    ��    ��   : y00245242
    �޸�����   : create

  2.��    ��   : 31/12/2014
    ��    ��   : y00245242
    �޸�����   : add home SID/NID list

  3.��    ��   : 2015/7/2
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17

*****************************************************************************/
VOS_UINT32 CNAS_XSD_PerformNormalCallRedialSystemSeletion_SysAcq(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
)
{
    CNAS_PRL_SYS_PRI_TYPE_ENUM_UINT32                       enSysPref;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enRoamingInd;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stCurSysGeoListInfo;
    CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsNegSys;

    ulIsNegSys = VOS_FALSE;

    /* reference from chapter 4.7.2 in CDG 143:
       The MS shall only stay and try to place the call on systems that comply with one
       of the following criteria:

       1. Systems that are same or more preferred than the original system;

       2. Systems have a home roaming indicator;

       3. The MS is allowed to place the call on a system from a different GEO (i.e., jump a GEO)
          as long this system meets one of the above criteria.

          Note: The criteria 3 has been included in the aboving criteria 1.
    */

    pstOrigSysInfo = CNAS_XSD_GetCallOrignalSys();

    /* check if the current system is orignal system */
    if (VOS_TRUE == CNAS_PRL_Is1xSysMatched(pstOrigSysInfo, pstCurSysInfo))
    {
        return VOS_TRUE;
    }

    /* check��ǰϵͳ�Ƿ���homeϵͳ����������PRL */
    if (VOS_TRUE == CNAS_XSD_IsCurSysHomeSystemIndependenceOnPrl(pstCurSysInfo))
    {
        return VOS_TRUE;
    }

    /* check if the current system is negative system in PRL system table */
    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(pstCurSysInfo, VOS_FALSE, 0);

    if (VOS_TRUE == ulIsNegSys)
    {
        return VOS_FALSE;
    }

    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(pstOrigSysInfo, VOS_FALSE, 0);

    if (VOS_TRUE == ulIsNegSys)
    {
        return VOS_TRUE;
    }

    NAS_MEM_SET_S(&stCurSysGeoListInfo, sizeof(stCurSysGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stCurSysGeoListInfo);

    /* check if current system is home roaming indicator */
    if (VOS_TRUE == CNAS_PRL_IsCurrentSystemHomeRoamingIndicator(pstCurSysInfo,
                                                                 &stCurSysGeoListInfo,
                                                                 &enRoamingInd))
    {
        return VOS_TRUE;
    }

    /* compare the priority between current system and orignal system */
    enSysPref = CNAS_PRL_CompareSystemPreference(pstCurSysInfo, pstOrigSysInfo);

    if ((CNAS_PRL_SYS_PRI_HIGH == enSysPref)
     || (CNAS_PRL_SYS_PRI_SAME == enSysPref))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_PerformNotLessPrefSystemSelectionAfterSyncSucc_SysAcq
 ��������  : process system selection while the acquire mode is not less prefer,such as on
             normal call redial scene,in this case,we have to find a system whose pri is same
             or more prefered than the current system
 �������  : pstSyncCnf  -- ͬ��ȷ����Ϣ

 �������  : none

 �� �� ֵ  : none
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 27/11/2014
    ��    ��   : y00245242
    �޸�����   : create

  2.��    ��   : 2015��1��05��
    ��    ��   : y00245242
    �޸�����   : ����OOC��������

  3.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformNotLessPrefSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU                       *pstSyncCnf
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList = VOS_NULL_PTR;
    VOS_UINT16                                              usDstChanNum;
    VOS_UINT16                                              usCurScanListIndex;
    CNAS_PRL_1X_SYSTEM_STRU                                 stCurSysInfo;

    stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
    stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
    stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;

    /* check if orignal system is exist */
    if (VOS_FALSE == CNAS_XSD_GetCallOrigSysExistFlg())
    {
        /* if orignal system is not exist, here use procedure of switch on system selection */
        CNAS_XSD_PerformBestPreferedSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);

        return;
    }

    /* check the current system is fit to camp on */
    if (VOS_TRUE == CNAS_XSD_PerformNormalCallRedialSystemSeletion_SysAcq(&stCurSysInfo))
    {
        /* notify CAS to camp on the current system */
        CNAS_XSD_SndCas1xCampSyncedChannelNtf();

        /* transfer to CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND state, start timer */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);
    }
    else
    {
        /* contine to request CAS synchronize system */
        usDstChanNum       = 0;
        usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();
        pstScanList        = CNAS_XSD_GetScanChanListAddr();

        CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);

        if (0 == usDstChanNum)
        {
            /* No frequencies need to synchronize */
            CNAS_XSD_ProcScanListSyncComplete_SysAcq();
        }
        else
        {
            /* contine to synchronize the remained frequencies */
            CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_PerformSystemSelectionAfterSyncSucc_SysAcq
 ��������  : ����ͬ���ɹ����ϵͳѡ��

 �������  : pstCurSysInfo -- the synchronized system

 �������  : none

 �� �� ֵ  : none
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 27/11/2014
    ��    ��   : y00245242
    �޸�����   : create
  2.��    ��   : 25/12/2014
    ��    ��   : w00176964
    �޸�����   : CDMA Iteration 6 Modified:Add system acquire mode
  3.��    ��   : 2015��7��6��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
  4.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_PerformSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enScanScene;
    CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM_UINT8                 enSysAcqMode;
    VOS_UINT32                                              ulIsAnyCampOnFreq;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                         enCardStatus;

    enScanScene  = CNAS_XSD_GetCurSysAcqScene_SysAcq();
    enSysAcqMode = CNAS_XSD_GetSysAcqModeOfSpecialAcqScene(enScanScene);

    if (VOS_TRUE == g_CtrlCallRelScanList)
    {
        /* �����call release�������ҵ�ǰͬ���ɹ���Ƶ�㲻���κ�ϵͳ����פ����Ƶ�㣬��Best Prefer����
           ����ѡ��:
           ����Ŀǰcall release��������scan list�������һ�ι���(��call release�����µ�scan list����),
           ��������TCH״̬�µ�Ƶ���Լ�MRU0Ƶ���ϵ�ϵͳ����ֱ��פ����������Ƶ����Ҫ��BEST PREFERѡ�����
           �˴������⴦��
         */
        ulIsAnyCampOnFreq = CNAS_XSD_IsCallRelAnyCampOnFreq_SysAcq(&(pstSyncCnf->stFreq));

        if ((CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED == CNAS_XSD_GetCurSysAcqScene_SysAcq())
         && (VOS_FALSE                            == ulIsAnyCampOnFreq))
        {
            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_BEST_PREF;
        }
    }

    enCardStatus = CNAS_CCB_GetCsimCardStatus();

    if (CNAS_CCB_CARD_STATUS_ABSENT == enCardStatus)
    {
        enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_ANY;
    }

    CNAS_MNTN_LogCommonStatusInfo(UEPS_PID_XSD, (VOS_UINT8)enCardStatus);

    switch (enSysAcqMode)
    {
        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_NOT_LESS_PREF:

            CNAS_XSD_PerformNotLessPrefSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_ALLOWED:

            CNAS_XSD_PerformAllowedSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_BEST_PREF:

            CNAS_XSD_PerformBestPreferedSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_SPECIFIC:

            CNAS_XSD_PerformSpecificSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_ANY:

            CNAS_XSD_PerformAnySystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        case CNAS_XSD_SYSTEM_ACQUIRE_MODE_PREFERED:

            CNAS_XSD_PerformPreferedSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);
            break;

        default:

            CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_PerformSystemSelectionAfterSyncSucc_SysAcq: unsupported system acquire mode");
            break;
    }
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcCasSyncCnfSucc_SysAcq
 ��������  : �յ�CAS��ͬ���ظ��ɹ��Ĵ���
 �������  : pstSyncCnf----ͬ���ظ���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��21��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��1��05��
    ��    ��   : y00245242
    �޸�����   : ����OOC��������
  3.��    ��   : 2015��4��20��
    ��    ��   : w00242748
    �޸�����   : DTS2015041609529:����MRU0�����MRU0ͬ���ɹ�����û�취פ����
                 ����»ᵼ����ѭ��������
  4.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
  5.��    ��   : 2015��9��14��
    ��    ��   : y00245242
    �޸�����   : DTS2015090601618
  6.��    ��   : 2015��12��10��
    ��    ��   : l00324781
    �޸�����   : CL_MUTIMODE_OPTIMIZE�޸ģ�����SWITCH_ON_INIT_SEARCH��������
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSyncCnfSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    /***********************************************************************************************
     * 1. �����ǰRF availableΪFALSE��֪ͨ�ϲ�RF available
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_CCB_Get1XRfAvailFlg())
    {
        /* �ϱ�MSCC NO RF��Ϣ */
        CNAS_XSD_SndMsccRfAvailInd(VOS_TRUE);

        /* ���õ�ǰRF���ñ��Ϊ:RF���� */
        CNAS_CCB_Set1XRfAvailFlg(VOS_TRUE);
    }

    /***********************************************************************************************
     * 2. ����Ƶʱ���������avoidƵ��
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_XSD_GetFreqLockMode())
    {
        /* ����ϵͳͬ��ȷ����Ϣ����Ҫ������Ƶ�� */
        CNAS_XSD_ProcFreqAvoidedInCasSyncCnf(pstSyncCnf);
    }

    /***********************************************************************************************
     * 3. ֪ͨ�ϲ㵱ǰͬ����1Xϵͳ��SID��Ϣ
     **********************************************************************************************/
    if (pstSyncCnf->stSyncedSysId.usSid != CNAS_XSD_GetLastSyncedSys()->usSid)
    {
        /* �����ϴ�ͬ������ϵͳ */
        CNAS_XSD_UpdateLastSyncedSys((CNAS_PRL_1X_SYSTEM_ID_STRU *)&pstSyncCnf->stSyncedSysId);

        /* ֪ͨMSCC�µ�SID,NIDָʾ */
        CNAS_XSD_SndMsccSidNidInd(pstSyncCnf->stSyncedSysId.usSid, pstSyncCnf->stSyncedSysId.usNid);
    }

   /***********************************************************************************************
     * 4. ����ͬ����ϵͳ����ʷͬ����ϵͳ�б���
     **********************************************************************************************/
    CNAS_XSD_UpdateHistorySyncedSysFreqList((CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncCnf->stFreq));

    /***********************************************************************************************
     * 5. ˢ��ͬ���ɹ������µ�scan list��Ƶ��״̬
     **********************************************************************************************/
    CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfSucc_SysAcq(pstSyncCnf);

    /***********************************************************************************************
     * 6. ���и��ݳ�������ϵͳѡ��
     **********************************************************************************************/
    CNAS_XSD_PerformSystemSelectionAfterSyncSucc_SysAcq(pstSyncCnf);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcCasSyncCnfFail_SysAcq
 ��������  : �յ�CAS��ͬ���ظ�ʧ�ܵĴ���
 �������  : pstSyncCnf----ͬ���ظ���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��21��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��05��
    ��    ��   : y00245242
    �޸�����   : ����OOC��������

  3.��    ��   : 2015��4��20��
    ��    ��   : w00242748
    �޸�����   : DTS2015041609529:����MRU0�����MRU0ͬ���ɹ�����û�취פ����
                 ����»ᵼ����ѭ��������

  4.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

  5.��    ��   : 2015��9��14��
    ��    ��   : y00245242
    �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSyncCnfFail_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstEmcScanChanList   = VOS_NULL_PTR;

    pstEmcScanChanList                  = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

    /***********************************************************************************************
     * 1. �����ǰRF availableΪFALSE��֪ͨ�ϲ�RF available
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_CCB_Get1XRfAvailFlg())
    {
        /* �ϱ�MSCC NO RF��Ϣ */
        CNAS_XSD_SndMsccRfAvailInd(VOS_TRUE);

        /* ���õ�ǰRF���ñ��Ϊ:RF���� */
        CNAS_CCB_Set1XRfAvailFlg(VOS_TRUE);
    }

    /***********************************************************************************************
     * 2. ����Ƶʱ���������avoidƵ��
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_XSD_GetFreqLockMode())
    {
        /* ����ϵͳͬ��ȷ����Ϣ����Ҫ������Ƶ�� */
        CNAS_XSD_ProcFreqAvoidedInCasSyncCnf(pstSyncCnf);
    }

    /***********************************************************************************************
     * 3. ˢ��ͬ��ʧ�ܵ�Ƶ��scan list
     **********************************************************************************************/
    CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfFail_SysAcq(pstSyncCnf);

    /* ����������SD������ˢ�½�������Ƶ���б���������ظ���ͬ��ʧ�ܵ�Ƶ�� */
    if (VOS_NULL_PTR != pstEmcScanChanList->pstScanChanInfo)
    {
        if (VOS_TRUE == CNAS_XSD_IsEmcSDSysAcq_SysAcq(CNAS_XSD_GetCurSysAcqScene_SysAcq()))
        {
            (VOS_VOID)CNAS_XSD_UpdateSyncFailChanStatus(pstEmcScanChanList->usCurScanIndex,
                                                       (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                        pstSyncCnf->astSyncRsltList,
                                                        pstEmcScanChanList);
        }
    }

    /***********************************************************************************************
     * 4. ����GEOϵͳ��¼�����б�״̬
     **********************************************************************************************/
    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        /***********************************************************************************************
         * 4.1. ˢ��GEOϵͳ��¼�����б��е�Ƶ��Ϊ����������
         **********************************************************************************************/
        CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq((VOS_UINT16)(pstSyncCnf->ulSyncFailFreqNum),
                                                                       &pstSyncCnf->astSyncRsltList[0]);

        /*******************************************************************************************
         * 4.2. ����GEOϵͳ��¼�����б�����
         ******************************************************************************************/
        CNAS_XSD_ContinueGeoSysRecordSrch();

        return;
    }

    /***********************************************************************************************
     * 5. ����GEOϵͳ��¼����list�����ڵĴ�������
     **********************************************************************************************/
    CNAS_XSD_ProcSyncFailAndNoGeoSysRecorSearchList_SysAcq(pstSyncCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcCasSyncCnfNoRf_SysAcq
 ��������  : �յ�CAS��ͬ���ظ�ΪNO RF��������NO RF��������Ҫ֪ͨ�ϲ㵱ǰRF��
             ���ã����˳���ǰ״̬��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcCasSyncCnfNoRf_SysAcq(VOS_VOID)
{
    /***********************************************************************************************
     * ����NO RF������ֱ���˳���ǰ״̬��
     **********************************************************************************************/

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE, CNAS_XSD_SYS_ACQ_SCENE_NO_RF, VOS_FALSE);

    /* �˳����״̬�� */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcScanListSyncComplete_SysAcq
 ��������  : ����SCAN LIST�Ѿ�ȫ��ͬ�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��5��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 6 Modified

  3.��    ��   : 2015��7��4��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcScanListSyncComplete_SysAcq(VOS_VOID)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enScanScene;
    VOS_UINT16                                              usFreqNum;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreqList[CNAS_CAS_1X_MAX_FREQ_NUM];

    enScanScene   = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /***********************************************************************************************
     * 1. ��availableϵͳ����Ҫͬ��availableϵͳ
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_XSD_IsAcquireAvaialSysNeeded(enScanScene))
    {
        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                               CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                               CNAS_XSD_IsImmediateSysAcq_SysAcq());

        /* �˳����״̬�� */
        CNAS_XSD_QuitFsmSysAcq_SysAcq();

        return;
    }

    /***********************************************************************************************
     * 2. ͬ��availableϵͳ
     **********************************************************************************************/
    /* ���ñ�־: ��ǰ����Ƶ��������available system list */
    CNAS_XSD_SetAvailSysAcqListFlg_SysAcq(VOS_TRUE);

    /* ����ͬ������ͬ��availableϵͳ */
    NAS_MEM_SET_S(&astFreqList[0], sizeof(astFreqList), 0, sizeof(CNAS_CAS_1X_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

    CNAS_XSD_GetNextAvailSysAcqList_SysAcq(&usFreqNum, &astFreqList[0]);

    CNAS_XSD_ContinueSyncScanList_SysAcq(usFreqNum, &astFreqList[0]);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ContinueSyncScanList_SysAcq
 ��������  : SCAN LIST����ͬ��
 �������  : VOS_UINT16                          usDstChanNum
             CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_ContinueSyncScanList_SysAcq(
    VOS_UINT16                          usDstChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan
)
{
    CNAS_XSD_SndCasSysSyncReq(usDstChanNum, pstDstChan);

    /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF, usDstChanNum * TI_CNAS_XSD_WAIT_CAS_SYNC_ONE_FREQ_LEN + 5);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_PeformBestPreferedSystemSelectionUsingNewGeo_SysAcq
 ��������  : ����һ���µ�GEOs�������ŵ�ϵͳѡ��
 �������  : pstGeoListInfo -- ����������GEO list��Ϣ
             pstCurSysInfo  -- ��ǰ��ϵͳ��Ϣ
             ulIsNegSys     -- ��ǰϵͳ�Ƿ���negativeϵͳ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��12��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��05��
    ��    ��   : y00245242
    �޸�����   : ����OOC��������

  3.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_PeformBestPreferedSystemSelectionUsingNewGeo_SysAcq(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    VOS_UINT32                                              ulIsNegSys
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_CAS_1X_SYSTEM_IDENTITY_STRU                        stCurrSysId;
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU                         stSyncFailChan;
    CNAS_CAS_1X_FREQENCY_CHANNEL_STRU                       stFreq;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                                              usDstChanNum;

    /***********************************************************************************************
     * 1. ˢ��GEO�����б��б�������GEOΪ������
     **********************************************************************************************/
    CNAS_XSD_UpdateGeoListSrchStatus(pstGeoListInfo, VOS_TRUE);

    /***********************************************************************************************
     * 2. �����µ�GEO�����б�
     **********************************************************************************************/
    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    NAS_MEM_SET_S(pstGeoSysRecSrchList, sizeof(CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU), 0, sizeof(CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU));

    CNAS_XSD_ConstructGeoSysRecordSrchList(pstGeoListInfo, pstCurSysInfo, pstGeoSysRecSrchList);

    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        /* �ڴ����ʧ�ܣ�ֱ�ӷ��� */
        return;
    }

    CNAS_XSD_LogAcqSystemList(pstGeoSysRecSrchList);

    if (VOS_FALSE == ulIsNegSys)
    {
        stFreq.usBandClass = pstCurSysInfo->stFreq.enBandClass;
        stFreq.usChannel   = pstCurSysInfo->stFreq.usChannel;

        stCurrSysId.usNid  = pstCurSysInfo->usNid;
        stCurrSysId.usSid  = pstCurSysInfo->usSid;

        /* ˢ�µ�ǰͬ���ɹ���Ƶ��״̬��GEO��ϵͳ��¼�����б�����match��ϵͳƵ��ˢ��Ϊ�������ڣ�
         * ����ϵͳ��¼��Ƶ��ˢ��Ϊ���������� */
        CNAS_XSD_UpdateSyncSuccFreqStatusInGeoSysRecordSrchList_SysAcq(&stFreq,
                                                                       &stCurrSysId);
    }
    else
    {
        NAS_MEM_SET_S(&stSyncFailChan, sizeof(stSyncFailChan), 0, sizeof(CNAS_CAS_1X_SYNC_RSLT_INFO_STRU));

        stSyncFailChan.stFreq.usBandClass = pstCurSysInfo->stFreq.enBandClass;
        stSyncFailChan.stFreq.usChannel   = pstCurSysInfo->stFreq.usChannel;

        /* ��ǰϵͳ��negativeϵͳ��ˢ��GEO��ϵͳ��¼�����б��ж�Ӧ��Ƶ��Ϊ���������� */
        CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq(1, &stSyncFailChan);

        /* ����ϵͳ��negʱ����ˢ�¸�Ƶ��Ϊ�����ڣ������ˢ�µĻ�������ͬ����Ȼ��ͬ����Ƶ��
           ��ȡ��һ��ͬ��Ƶ��ʱ���߼�Ϊδͬ������ͬ������ */
        CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq(&pstCurSysInfo->stFreq,
                                                                       CNAS_XSD_GetScanChanListAddr());
    }

    /***********************************************************************************************
     * 3. �����ǰϵͳ����������ȼ�ϵͳ��֪ͨ�����פ��
     **********************************************************************************************/
    /* ����scan list���б��е�Ƶ��״̬��ˢ��GEOϵͳ��¼�����б��е�Ƶ��״̬���´��������� */
    CNAS_XSD_UpdateGeoSysRecordListInfoAccordingToScanChanList(pstGeoSysRecSrchList);

    if (VOS_TRUE == CNAS_XSD_IsCurrSysMostPref1xSysInGeoSysRecordSrchList(pstCurSysInfo, pstGeoSysRecSrchList))
    {
        /* ����ǰ֪ͨ�ϲ����״̬ */
        CNAS_XSD_ReportSrvAvailableInd_SysAcq(pstCurSysInfo);

        /* ����ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
        CNAS_XSD_SndCas1xCampSyncedChannelNtf();

        /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_OHM_IND */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

        /* ����������ʱ�� */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

        return;
    }

    /*******************************************************************************************
     * 4. ����GEOϵͳ��¼�����б�����
     ******************************************************************************************/
    usDstChanNum = 0;

    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    CNAS_XSD_GetNextSysSyncListFromGeoSysRecordSrchList(CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq(),
                                                        &usDstChanNum,
                                                        &astDstChan[0]);

    if (0 != usDstChanNum)
    {
        /* ����GEOϵͳ��¼Ƶ��ͬ������ */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, &astDstChan[0]);

        return;
    }

    /*******************************************************************************************
     * 5. ���GEO�����б�״̬�Լ��ͷ�GEOϵͳ��¼�����б��ڴ�
     ******************************************************************************************/
    /* �����GEO�����б�״̬ */
    CNAS_XSD_ClearGeoSrchListStatus();

    /* LOG GEO list����״̬��Ϣ */
    CNAS_XSD_LogGeoListSrchStatus(CNAS_XSD_GetGeoSrchListInfoAddr());

    /* �ͷ�GEOϵͳ��¼�����б���ڴ� */
    if (VOS_NULL_PTR != CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo);
        CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo = VOS_NULL_PTR;
    }

    /*******************************************************************************************
     * 6. ����scan listƵ���б�����
     ******************************************************************************************/
    usDstChanNum = 0;
    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    CNAS_XSD_GetNextScanChanList_SysAcq(CNAS_XSD_GetCurChannelScanIndex(),
                                        &usDstChanNum,
                                        astDstChan,
                                        CNAS_XSD_GetScanChanListAddr());

    if (0 != usDstChanNum)
    {
        /* scan listδȫ��ͬ���꣬������ͬ������ */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);

        return;
    }

    /*******************************************************************************************
     * 7. ����scan listͬ����ɵĺ�������
     ******************************************************************************************/
    /* scan list��ȫ��ͬ���� */
    CNAS_XSD_ProcScanListSyncComplete_SysAcq();
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ContinueSysSync_SysAcq
 ��������  : ����ϵͳ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��13��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��05��
    ��    ��   : y00245242
    �޸�����   : ����OOC��������

  2.��    ��   : 2015��7��4��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_VOID CNAS_XSD_ContinueSysSync_SysAcq(VOS_VOID)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList          = VOS_NULL_PTR;
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                                              usCurScanListIndex;
    VOS_UINT16                                              usDstChanNum;

    /***********************************************************************************************
     * 1. �����availableϵͳͬ��������availableϵͳͬ��
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        CNAS_XSD_ContinueAvailSysListSrch();

        return;
    }

    /***********************************************************************************************
     * 2. ����GEOϵͳ��¼�����б���ڵĳ���
     **********************************************************************************************/
    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        CNAS_XSD_ContinueGeoSysRecordSrch();

        return;
    }

    /***********************************************************************************************
     * 3. ����scan listƵ������
     **********************************************************************************************/
    usDstChanNum       = 0;
    pstScanList        = CNAS_XSD_GetScanChanListAddr();
    usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();

    CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);

    if (0 != usDstChanNum)
    {
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);

        return;
    }

    /***********************************************************************************************
     * 4. scan list������ɴ���
     **********************************************************************************************/
    CNAS_XSD_ProcScanListSyncComplete_SysAcq();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurSysAcqScene_SysAcq
 ��������  : ���ص�ǰϵͳ���񳡾�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��12��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��10��
    ��    ��   : l00324781
    �޸�����   : CL_MUTIMODE_OPTIMIZE �����³���SWITCH_ON_INIT_SEARCH
*****************************************************************************/
CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_XSD_GetCurSysAcqScene_SysAcq(VOS_VOID)
{
    CNAS_XSD_MSG_STRU                                      *pstEntryMsg  = VOS_NULL_PTR;
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU                  *pstIntSysAcqReq = VOS_NULL_PTR;
    MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU                       *pstSysAqcReq    = VOS_NULL_PTR;

    /* ��õ�ǰ����CNAS XSD�����Ϣ�Ļ�������ַ */
    pstEntryMsg                 = CNAS_XSD_GetCurrFsmEntryMsgAddr();

    if (CNAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_XSD_SYSTEM_ACQUIRE_REQ)
            == pstEntryMsg->ulEventType)
    {
        pstSysAqcReq = (MSCC_XSD_SYSTEM_ACQUIRE_REQ_STRU *)pstEntryMsg->aucMsgBuffer;

        if (MSCC_XSD_SYS_ACQ_TYPE_NORMAL == pstSysAqcReq->enSysAcqType)
        {
            return CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON;
        }
        else
        {
            return CNAS_XSD_SYS_ACQ_SCENE_POWER_ON_INIT_SEARCH;
        }
    }

    if (CNAS_BuildEventType(UEPS_PID_XSD, ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ)
            == pstEntryMsg->ulEventType)
    {
        pstIntSysAcqReq = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU *)pstEntryMsg->aucMsgBuffer;

        return pstIntSysAcqReq->enSysAcqScene;
    }

    return CNAS_XSD_SYS_ACQ_SCENE_BUTT;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsImmediateSysAcq_SysAcq
 ��������  : �жϵ�ǰ�Ƿ���Ҫ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��20��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsImmediateSysAcq_SysAcq(VOS_VOID)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene;

    enSysAcqScene = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* call release����scan list�����Ѿ��޸ģ�����һ�ι���(��call release�����µ�build scan list����)
     * ���ʧ��ʱ��������������
     */
    /* call release with redir�ĳ�����Ҫ������ */
    if (CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR == enSysAcqScene)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsEmergencySysAcq_SysAcq
 ��������  : �жϵ�ǰ�Ƿ�Ϊ�������е���������������7���������TRUE,�����������FALSE
             CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST ������Call Back����
             CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL           ����������
             CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED        ���������ͷŵ�����
             CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC
             CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC
             CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC
             CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC

 �������  : enSysAcqScene  ��ǰ����������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��1��
    ��    ��   : h00313353
    �޸�����   : DTS2015101200488

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsEmergencySysAcq_SysAcq(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    switch(enSysAcqScene)
    {
        case CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST:
        case CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL:
        case CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED:
            return VOS_TRUE;

        default:
            return CNAS_XSD_IsEmcSDSysAcq_SysAcq(enSysAcqScene);
    }
}
/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsEmcSDSysAcq_SysAcq
 ��������  : �жϵ�ǰ�Ƿ�Ϊ�������е���������������7���������TRUE,�����������FALSE
             CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC
             CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC
             CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC
             CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0_EMC
             CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM_EMC
             CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL_EMC
             CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC

 �������  : enSysAcqScene  ��ǰ����������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��09��
    ��    ��   : h00313353
    �޸�����   : DTS2015120205246

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsEmcSDSysAcq_SysAcq(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    switch(enSysAcqScene)
    {
        case CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetNextAvailSysAcqList_SysAcq
 ��������  : ��ȡ��һ����Ҫ������б�
 �������  : pstAcqSysInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 29/12/2014
    ��    ��   : w00176964
    �޸�����   : CDMA Iteration 6:Move the avail system list to the global variables

  3.��    ��   : 2015��7��4��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_GetNextAvailSysAcqList_SysAcq(
    VOS_UINT16                                             *pusFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqList
)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;
    VOS_UINT16                          i;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    *pusFreqNum = 0;

    for (i = pstAvailSysList->ucNextSrchIndex;
         i < CNAS_MIN(pstAvailSysList->ucAvailSysNum, CNAS_XSD_MAX_AVAILABLE_SYS_NUM);
         i++
         )
    {

        pstFreqList->enBandClass = pstAvailSysList->astAvailSystem[i].stFreq.enBandClass;
        pstFreqList->usChannel   = pstAvailSysList->astAvailSystem[i].stFreq.usChannel;

        pstFreqList++;
        (*pusFreqNum)++;

        if (*pusFreqNum == CNAS_CAS_1X_MAX_FREQ_NUM)
        {
            return;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq
 ��������  : ���²���ʧ�ܵ�ϵͳ״̬
 �������  : usSyncFailChanNum  ------------  ͬ��ʧ��Ƶ�����
             pstSyncFailChanList--------------ͬ��ʧ�ܵ�Ƶ���б�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��7��4��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq(
    VOS_UINT16                          usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU    *pstSyncFailChanList
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus;
    VOS_UINT16                                              i;

    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    enSysStatus   = CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST;

    for (i = 0; i < CNAS_MIN(usSyncFailChanNum, CNAS_CAS_1X_MAX_FREQ_NUM); i++)
    {
        /* ����ȡ�б���ָ��Ƶ��Ķ�Ӧ�б�ȫ��ˢ��Ϊ����������� */
        CNAS_XSD_UpdateSysFreqStatusByFreqChanInGeoSysRecordSrchList((CNAS_PRL_FREQENCY_CHANNEL_STRU *)&pstSyncFailChanList[i].stFreq,
                                                                     enSysStatus,
                                                                     pstGeoSysRecSrchList);
    }

    CNAS_XSD_LogAcqSystemList(pstGeoSysRecSrchList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateSyncSuccFreqStatusInGeoSysRecordSrchList_SysAcq
 ��������  : ����GEOϵͳ�����б���ͬ��ʧ�ܵ�Ƶ��״̬
 �������  : pstFreq        -- ͬ���ɹ���Ƶ��
             pstSyncedSysId -- ͬ����ϵͳ

 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��7��4��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateSyncSuccFreqStatusInGeoSysRecordSrchList_SysAcq(
    CNAS_CAS_1X_FREQENCY_CHANNEL_STRU                      *pstFreq,
    CNAS_CAS_1X_SYSTEM_IDENTITY_STRU                       *pstSyncedSysId
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU                                 stAcqSuccSys;
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus;
    VOS_UINT16                                              i;

    stAcqSuccSys.stFreq.enBandClass = pstFreq->usBandClass;
    stAcqSuccSys.stFreq.usChannel   = pstFreq->usChannel;
    stAcqSuccSys.usNid              = pstSyncedSysId->usNid;
    stAcqSuccSys.usSid              = pstSyncedSysId->usSid;

    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();
    enSysStatus   = CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST;

    CNAS_XSD_UpdateSysFreqStatusBySysInGeoSysRecordSrchList(&stAcqSuccSys, enSysStatus, pstGeoSysRecSrchList);

    /* ���ڷ���AS����ͬƵ�������SID+NID,Ӧ���ǲ���ʧ�ܵ�,���¶�Ӧ�Ĳ���ϵͳ״̬ */
    enSysStatus   = CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST;
    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++)
    {
        if ((stAcqSuccSys.stFreq.enBandClass == pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq.enBandClass)
         && (stAcqSuccSys.stFreq.usChannel   == pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq.usChannel))
        {
            /* ����ɹ���ϵͳ��ˢ��״̬ */
            if (VOS_FALSE == CNAS_PRL_Is1xSysIdMatched(stAcqSuccSys.usSid,
                                                       stAcqSuccSys.usNid,
                                                       pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.usSid,
                                                       pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.usNid))

            {
                pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus = enSysStatus;
            }
        }
    }

    CNAS_XSD_LogAcqSystemList(pstGeoSysRecSrchList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_QuitFsmSysAcq
 ��������  : �˳�SYSTEM ACQUIRED״̬��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��25��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��3��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 5 Modified
  3.��    ��   : 2015��7��9��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

  4.��    ��   : 2015��7��21��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_VOID CNAS_XSD_QuitFsmSysAcq_SysAcq(VOS_VOID)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstCallRedialScanChanList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList           = VOS_NULL_PTR;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene;

    enCurAcqScene                       = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* ���GEO����״̬ */
    CNAS_XSD_ClearGeoSrchListStatus();

    /* LOG GEO list����״̬��Ϣ */
    CNAS_XSD_LogGeoListSrchStatus(CNAS_XSD_GetGeoSrchListInfoAddr());

    pstScanChanList           = CNAS_XSD_GetScanChanListAddr();
    switch (enCurAcqScene)
    {
        case CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL:
            {
                /* for normal call redial scene, update the call redial channle list by the current
                   scan channle list */

                pstCallRedialScanChanList = CNAS_XSD_GetCallRedialScanChanListAddr();

                CNAS_XSD_UpdateScanChanList(pstCallRedialScanChanList, pstScanChanList);

                CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_CALL_REDIAL_SCAN_CHAN_LIST_IND,
                                            pstCallRedialScanChanList);
            }
            break;


        case CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL:
            {
                /* for emc call redial scene, update the call redial channle list by the current
                   scan channle list */
                pstCallRedialScanChanList = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

                CNAS_XSD_UpdateScanChanList(pstCallRedialScanChanList, pstScanChanList);

                CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_EMC_CALL_REDIAL_SCAN_CHAN_LIST_IND,
                                            pstCallRedialScanChanList);
            }
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR:
            {
                /* ����scan listƵ��״̬��ˢ��redirectionƵ��״̬ */
                CNAS_XSD_UpdateRedirectionFreqStatusAccordingToScanChanList(pstScanChanList);
            }
            break;

        default:
            break;
    }

    CNAS_XSD_QuitFsmL2();
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcFreqAvoidedInCasSyncCnf
 ��������  : ����CAS SYNC CNF��Ϣ����Ҫ������Ƶ��
 �������  : pstSyncCnf -- ϵͳͬ��ȷ����Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��20��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcFreqAvoidedInCasSyncCnf(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    VOS_UINT8                           i;
    CNAS_PRL_1X_SYSTEM_STRU             stSysInfo;
    VOS_UINT32                          ulIsNegSys;

    ulIsNegSys = VOS_FALSE;

    if (CNAS_CAS_1X_RSLT_SUCCESS == pstSyncCnf->enSyncRslt)
    {
        /* ����ɹ���Ƶ�� */
        stSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
        stSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;

        stSysInfo.usNid  = pstSyncCnf->stSyncedSysId.usNid;
        stSysInfo.usSid  = pstSyncCnf->stSyncedSysId.usSid;

        ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stSysInfo, VOS_FALSE, 0);

        /* �����negativeϵͳ�����Ƶ���avoid�б��� */
        if (VOS_TRUE == ulIsNegSys)
        {
            if (VOS_TRUE == CNAS_XSD_IsAddInAvoidList(CNAS_XSD_AVOID_SID_NID_IS_REJ_BY_PRL))
            {
                CNAS_XSD_UpdataAvoidListInfo(&(stSysInfo.stFreq), CNAS_XSD_AVOID_SID_NID_IS_REJ_BY_PRL);
            }
        }
    }


    for (i = 0; i < pstSyncCnf->ulSyncFailFreqNum; i++)
    {
        if (CNAS_CAS_1X_SYS_SRCH_SYNC_FAIL_PROTO_MISMATCH != pstSyncCnf->astSyncRsltList[i].enFailReason)
        {
            continue;
        }

        /* ����avoid�б�ǰ�����slice�Ƿ��Ѿ����� */
        stSysInfo.stFreq.enBandClass = pstSyncCnf->astSyncRsltList[i].stFreq.usBandClass;
        stSysInfo.stFreq.usChannel   = pstSyncCnf->astSyncRsltList[i].stFreq.usChannel;

        if (VOS_TRUE == CNAS_XSD_IsAddSyncFailFreqInAvoidList(&(stSysInfo.stFreq),
                                                              pstSyncCnf->astSyncRsltList[i].ulSlice,
                                                              CNAS_XSD_AVOID_P_REV_MISMATCH))
        {
            CNAS_XSD_UpdataAvoidListInfo(&(stSysInfo.stFreq), CNAS_XSD_AVOID_P_REV_MISMATCH);
        }

    }


    /*���avoid�б��д��ڽ��ñ�ǣ���ʾ���ڱ����õ�Ƶ�㣬������ʱ�� */
    if (VOS_TRUE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
    {
        /* ���avoid timerδ����������avoid timer��ʱ�� */
        if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_XSD,
                                                                      TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                      0))
        {
            CNAS_XSD_StartTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER,
                                TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
        }
    }

    CNAS_XSD_LogAvoidFreqList(CNAS_XSD_GetAvoidFreqListAddr());
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_PerformAbortProcedure_SysAcq
 ��������  : ִ��״̬���������
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_PerformAbortProcedure_SysAcq(VOS_VOID)
{
    CNAS_XSD_StopTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER);

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                           CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                           CNAS_XSD_IsImmediateSysAcq_SysAcq());

    /* �˳����״̬�� */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF״̬�յ�ID_MMA_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��20��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU            *pstCallRedialNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                       enCurScene;

    pstCallRedialNtfMsg = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*)pstMsg;

    enCurScene = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* ��������ȼ���Ϻ�֮ǰ��ϵĻ�����Ϣ */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF);

    /* ����ǰ���ڸ������ȼ��Ĵ�ϵĻ�����Ϣ�����Ա���Ϣ */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    CNAS_XSD_SetAbortFlg_SysAcq(VOS_FALSE);

    /* �ų�һЩ��Ҫ������Ϣ�ĳ��� */
    /* ���������� */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL       == pstCallRedialNtfMsg->enCallType)
    {
        if (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL           == enCurScene)
        {
            /* ��ǰ�Ѿ��ڽ��������ز���������Ϣ������������ */
            return VOS_TRUE;
        }
    }
    /* ��ͨ�������ݺ����� */
    else
    {
        if ((CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL      == enCurScene)
        ||  (CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON               == enCurScene))
        {
            /* ��ǰ�Ѿ��ں����ز���������Ϣ������������ */
            return VOS_TRUE;
        }
    }

    /* ����ǰ�����ڸ������ȼ��Ļ�����Ϣ�������µĴ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* ������������,����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* ��������ز�ָʾ��Ϣ */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ��CAS����ID_CNAS_CAS_1X_STOP_SYSTEM_SYNC_REQ��Ϣֹͣͬ�� */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasOhmInd
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬�յ�ID_MMA_XSD_CALL_REDIAL_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��20��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU           *pstCallRedialNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurScene;

    pstCallRedialNtfMsg = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*)pstMsg;

    enCurScene = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* ��������ȼ���Ϻ�����Ļ�����Ϣ */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF);

    /* ����ǰ���ڸ������ȼ��Ĵ�ϵĻ�����Ϣ�����Ա���Ϣ */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    CNAS_XSD_SetAbortFlg_SysAcq(VOS_FALSE);

    /* �ų�һЩ��Ҫ������Ϣ�ĳ��� */
    /* ���������� */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL       == pstCallRedialNtfMsg->enCallType)
    {
        if (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL           == enCurScene)
        {
            /* ��ǰ�Ѿ��ڽ��������ز���������Ϣ������������ */
            return VOS_TRUE;
        }
    }
    /* ��ͨ�������ݺ����� */
    else
    {
        if ((CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL      == enCurScene)
        ||  (CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON               == enCurScene))
        {
            /* ��ǰ�Ѿ��ں����ز���������Ϣ������������ */
            return VOS_TRUE;
        }
    }

    /* ����ǰ�����ڸ������ȼ��Ļ�����Ϣ�������µĴ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* ��������ز�ָʾ��Ϣ */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasStopSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF״̬�յ�ID_MMA_XSD_CALL_REDIAL_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��27��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU           *pstCallRedialNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurScene;

    pstCallRedialNtfMsg = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU*)pstMsg;

    enCurScene = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* ��������ȼ���Ϻ�����Ļ�����Ϣ */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF);

    /* ����ǰ���ڸ������ȼ��Ĵ�ϵĻ�����Ϣ�����Ա���Ϣ */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    CNAS_XSD_SetAbortFlg_SysAcq(VOS_FALSE);

    /* �ų�һЩ��Ҫ������Ϣ�ĳ��� */
    /* ���������� */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL       == pstCallRedialNtfMsg->enCallType)
    {
        if (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL           == enCurScene)
        {
            /* ��ǰ�Ѿ��ڽ��������ز���������Ϣ������������ */
            return VOS_TRUE;
        }
    }
    /* ��ͨ�������ݺ����� */
    else
    {
        if ((CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL      == enCurScene)
        ||  (CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON               == enCurScene))
        {
            /* ��ǰ�Ѿ��ں����ز���������Ϣ������������ */
            return VOS_TRUE;
        }
    }

    /* ����ǰ�����ڸ������ȼ��Ļ�����Ϣ�������µĴ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* ��������ز�ָʾ��Ϣ */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}



/*****************************************************************************
 FUNCTION NAME    : CNAS_XSD_PerformAllowedSystemSelectionAfterSyncSucc_SysAcq
 DESCRIPTION      : perfrom system selection with acquire mode is allowed: need not to match the most prefered system in PRL
 INPUT PARAMETER  : pstSyncCnf  -- ͬ��ȷ����Ϣ
 OUTPUT PARAMETER : none
 RETURN           : none
 CALLING FUNCTION :
 CALLED FUNCTION  :

 History modification:
  1.DATE         : 21/8/2014
    EDITOR       : w00176964
    MODIFICATION : create
  2.��    ��   : 2015��7��2��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified
  3.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformAllowedSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;
    VOS_UINT32                          ulIsNegSys;

    stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
    stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
    stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;

    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo, VOS_FALSE, 0);

    /* first check the system is allowed or not */
    if (VOS_TRUE == ulIsNegSys)
    {
        usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();
        pstScanList        = CNAS_XSD_GetScanChanListAddr();

        usDstChanNum       = 0;
        NAS_MEM_SET_S(astDstChan, sizeof(astDstChan), 0x0, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);

        CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);

        /* scan list��ȫ��ͬ���� */
        if (0 == usDstChanNum)
        {
            CNAS_XSD_ProcScanListSyncComplete_SysAcq();
        }
        /* scan listδȫ��ͬ���꣬������ͬ������ */
        else
        {
            CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);
        }

        return;
    }

    /* ����ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
    CNAS_XSD_SndCas1xCampSyncedChannelNtf();

    /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_OHM_IND */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);
}

/*****************************************************************************
 FUNCTION NAME    : CNAS_XSD_PerformAnySystemSelectionAfterSyncSucc_SysAcq
 DESCRIPTION      : perfrom system selection with acq mode is any: could camp on any system while synced successfull expect
                    the user settings
 INPUT PARAMETER  : pstSyncCnf  -- ͬ��ȷ����Ϣ
 OUTPUT PARAMETER : none
 RETURN           : none
 CALLING FUNCTION :
 CALLED FUNCTION  :

 History modification:
  1.DATE         : 12/1/2015
    EDITOR       : w00176964
    MODIFICATION : create

  2.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

  3.��    ��   : 2015��7��20��
    ��    ��   : h00313353
    �޸�����   : ����17 ������

  4.��    ��   : 2015��11��30��
    ��    ��   : h00313353
    �޸�����   : DTS2015101200488
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformAnySystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_PRL_1X_SYSTEM_STRU            *pstEmcCallOrigSys   = VOS_NULL_PTR;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enCurSysAcqScene;
    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;

    enCurSysAcqScene    = CNAS_XSD_GetCurSysAcqScene_SysAcq();
    NAS_MEM_SET_S(&stCurSysInfo, sizeof(stCurSysInfo), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    if (CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST == enCurSysAcqScene)
    {
        pstEmcCallOrigSys   = CNAS_XSD_GetEmcCallOriginalSys();

        if ((pstEmcCallOrigSys->usSid != pstSyncCnf->stSyncedSysId.usSid)
         || (pstEmcCallOrigSys->usNid != pstSyncCnf->stSyncedSysId.usNid))
        {
            CNAS_INFO_LOG4(UEPS_PID_XSD,
                           "CNAS_XSD_PerformAnySystemSelectionAfterSyncSucc_SysAcq:CallBack System Lost Srch Not Match(Req/Rsp):",
                           pstEmcCallOrigSys->usSid,
                           pstEmcCallOrigSys->usNid,
                           pstSyncCnf->stSyncedSysId.usSid,
                           pstSyncCnf->stSyncedSysId.usNid);

            /* ͬ���ɹ���ϵͳ������Ҫ�󣬼���Scan Listͬ�� */
            CNAS_XSD_ContinueSysSync_SysAcq();

            return;
        }
    }

    /* �ǽ������ͽ�����CallBack����,��ϵͳΪNegativeϵͳ������ͬ��ScanListʣ��Ƶ�� */
    if (VOS_FALSE == CNAS_XSD_IsEmergencySysAcq_SysAcq(enCurSysAcqScene))
    {
        stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
        stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
        stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
        stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;

        if (VOS_TRUE == CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo,
                                                         VOS_FALSE,
                                                         0))
        {
            CNAS_XSD_ContinueSysSync_SysAcq();

            return;
        }
    }

    /* ����ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
    CNAS_XSD_SndCas1xCampSyncedChannelNtf();

    /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_OHM_IND */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

    return;
}

/*****************************************************************************
 FUNCTION NAME    : CNAS_XSD_PerformPreferedSystemSelectionAfterSyncSucc_SysAcq
 DESCRIPTION      : perfrom system selection with acq mode is prefered: in this case,
                    we have to find a perfered system in PRL
 INPUT PARAMETER  : pstSyncCnf  -- ͬ��ȷ����Ϣ
 OUTPUT PARAMETER : none
 RETURN           : none
 CALLING FUNCTION :
 CALLED FUNCTION  :

 History modification:
  1.DATE         : 12/1/2015
    EDITOR       : w00176964
    MODIFICATION : create
  2.��    ��   : 2015��4��20��
    ��    ��   : w00242748
    �޸�����   : DTS2015041609529:����MRU0�����MRU0ͬ���ɹ�����û�취פ����
                 ����»ᵼ����ѭ��������
  3.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformPreferedSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stGeoListInfo;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    VOS_UINT32                          ulIsNegSys;

    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;

    stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
    stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
    stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;


    ulIsNegSys = VOS_FALSE;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_PRL_Get1xSysGeoList(&stCurSysInfo, &stGeoListInfo);

    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo, VOS_FALSE, 0);

    /* negative system or not in PRL, could not select,should continue sync */
    if ((VOS_TRUE == ulIsNegSys)
     || (0        == stGeoListInfo.ucGeoNum))
    {
        usCurScanListIndex = CNAS_XSD_GetCurChannelScanIndex();
        pstScanList        = CNAS_XSD_GetScanChanListAddr();

        usDstChanNum       = 0;
        NAS_MEM_SET_S(astDstChan, sizeof(astDstChan), 0x0, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_CAS_1X_MAX_FREQ_NUM);
        CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex,
                                            &usDstChanNum,
                                            astDstChan,
                                            pstScanList);

        /* scan list��ȫ��ͬ���� */
        if (0 == usDstChanNum)
        {
            CNAS_XSD_ProcScanListSyncComplete_SysAcq();
        }
        /* scan listδȫ��ͬ���꣬������ͬ������ */
        else
        {
            CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);
        }

        return;
    }

    /* ����ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
    CNAS_XSD_SndCas1xCampSyncedChannelNtf();

    /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_OHM_IND */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);
}

/*****************************************************************************
 FUNCTION NAME    : CNAS_XSD_PerformSpecificSystemSelectionAfterSyncSucc_SysAcq
 DESCRIPTION      : process system selection for which the SID/NID is known
 INPUT PARAMETER  : pstSyncCnf  -- ͬ��ȷ����Ϣ
 OUTPUT PARAMETER : none
 RETURN           : none
 CALLING FUNCTION :
 CALLED FUNCTION  :

 History modification:
  1.DATE         : 21/8/2014
    EDITOR       : y00245242
    MODIFICATION : create

  2.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_PerformSpecificSystemSelectionAfterSyncSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU  *pstFreqLockPara;
    VOS_UINT32                          ulRlst;

    /* ��ȡ��Ƶ��Ϣ */
    pstFreqLockPara = CNAS_XSD_GetFreqLockAddr();

    ulRlst = CNAS_PRL_Is1xSysIdMatched(pstSyncCnf->stSyncedSysId.usSid,
                                       pstSyncCnf->stSyncedSysId.usNid,
                                       pstFreqLockPara->usSid,
                                       pstFreqLockPara->usNid);

    if (VOS_TRUE == ulRlst)
    {
        CNAS_XSD_SndCas1xCampSyncedChannelNtf();

        /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_OHM_IND */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);
    }
    else
    {
        CNAS_XSD_ProcScanListSyncComplete_SysAcq();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcCasSystemDetermineIndWithProtoMisReason_SysAcq
 ��������  : process system determine indication message with protocol mismatch from CAS in system acquire state machine
 �������  : pstSysDeterminInd
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 29/12/2014
    ��    ��   : w00176964
    �޸�����   : Create

  2.��    ��   : 2015��7��17��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_UINT32 CNAS_XSD_ProcCasSystemDetermineIndWithProtoMisReason_SysAcq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd = VOS_NULL_PTR;

    pstSysDeterminInd   = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(CNAS_XSD_AVOID_P_REV_MISMATCH,
                                                  (CNAS_PRL_FREQENCY_CHANNEL_STRU *)(&(pstSysDeterminInd->stCurChannelInfo)));

    CNAS_XSD_SetRedirectionFlag(VOS_FALSE);

    /* continue sync */
    CNAS_XSD_ContinueSysSync_SysAcq();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetNextScanChanList_SysAcq
 ��������  : ��ȡ��һ��Ҫ������scan list
 �������  : usCurScanChanIndex----------��ǰɨ�赽��Ƶ������
             pstScanChanList------��ǰ��ɨ��Ƶ���б�
 �������  : pusDstChanNum-----------��ȡ����Ƶ�����
             pstDstChan--------------��ȡ����Ƶ���б�

 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��20��
    ��    ��   : w00242748
    �޸�����   : DTS2015041609529:����MRU0�����MRU0ͬ���ɹ�����û�취פ����
                 ����»ᵼ����ѭ��������
*****************************************************************************/
VOS_VOID CNAS_XSD_GetNextScanChanList_SysAcq(
    VOS_UINT16                          usCurScanChanIndex,
    VOS_UINT16                         *pusDstChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enCurAcqScene;
    VOS_UINT32                          ulIsAvoidListEnable;

    enCurAcqScene       = CNAS_XSD_GetCurSysAcqScene_SysAcq();
    ulIsAvoidListEnable = VOS_TRUE;

    if ((CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST == enCurAcqScene)
     || (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL           == enCurAcqScene)
     || (CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED        == enCurAcqScene))
    {
        ulIsAvoidListEnable = VOS_FALSE;
    }

    CNAS_XSD_GetNextScanChanList(usCurScanChanIndex,
                                 pusDstChanNum,
                                 pstDstChan,
                                 pstScanChanList,
                                 ulIsAvoidListEnable);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF״̬�յ�ID_MSCC_XSD_SRV_ACQ_REQ��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ǽ�����ʹ�õ�ǰ��������� */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL != ((MSCC_XSD_SRV_ACQ_REQ_STRU *)pstMsg)->enSrvType)
    {
        return VOS_TRUE;
    }

    /* ��������ȼ���ϵĻ�����Ϣ */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ);

    /* ����ǰ���ڸ������ȼ��Ĵ�ϵĻ�����Ϣ�����Ա���Ϣ */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    /* ���ҵ�������ǽ����������������������б� */
    CNAS_XSD_BuildEmcCallRedialScanChanList();

    /* ����ǰ�����ڸ������ȼ��Ļ�����Ϣ�������µĴ�� */
    /* ֹͣͬ����ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* ����ֹͣͬ������ */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* �����д������ҵ�񴥷�������� */
    CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* Ǩ״̬���ñ�����ʱ�� */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF״̬�յ�ID_MSCC_XSD_MO_CALL_END_NTF��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene;

    enAcqScene                          = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* �ǽ�������������� */
    if ((VOS_FALSE == CNAS_XSD_IsEmcSDSysAcq_SysAcq(enAcqScene))
     && (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL != enAcqScene))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* �����������У���ϴ��� */
    /* ֹͣͬ����ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_SYNC_CNF);

    /* ����ֹͣͬ������ */
    CNAS_XSD_SndCasStopSysSyncReq();

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* Ǩ״̬���ñ�����ʱ�� */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
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
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* Ǩ״̬���ñ�����ʱ�� */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
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
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* Ǩ״̬���ñ�����ʱ�� */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_SYNC_CNF״̬�յ�ID_MSCC_XSD_END_EMC_CALLBACK_REQ��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
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
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    /* Ǩ״̬���ñ�����ʱ�� */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF, TI_CNAS_XSD_WAIT_CAS_STOP_SYSTEM_SYNC_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasStopSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF״̬�յ�ID_MSCC_XSD_SRV_ACQ_REQ��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ǽ�����ʹ�õ�ǰ��������� */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL != ((MSCC_XSD_SRV_ACQ_REQ_STRU *)pstMsg)->enSrvType)
    {
        return VOS_TRUE;
    }

    /* ��������ȼ���ϵĻ�����Ϣ */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ);

    /* ����ǰ���ڸ������ȼ��Ĵ�ϵĻ�����Ϣ�����Ա���Ϣ */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    /* ���ҵ�������ǽ����������������������б� */
    CNAS_XSD_BuildEmcCallRedialScanChanList();

    /* ����ǰ�����ڸ������ȼ��Ļ�����Ϣ�������µĴ�� */
    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* �����д�����Ϣ�����ҵ�񴥷�������� */
    CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasStopSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF״̬�յ�ID_MSCC_XSD_MO_CALL_END_NTF��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene;

    enAcqScene                          = CNAS_XSD_GetCurSysAcqScene_SysAcq();

    /* �ǽ�������������� */
    if ((VOS_FALSE == CNAS_XSD_IsEmcSDSysAcq_SysAcq(enAcqScene))
     && (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL != enAcqScene))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* �����������У���ϴ��� */
    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasStopSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasStopSysSyncCnf
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_STOP_SYNC_CNF״̬�յ�ID_MSCC_XSD_END_EMC_CALLBACK_REQ��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasStopSysSyncCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasOhmInd
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬�յ�ID_MSCC_XSD_SRV_ACQ_REQ��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ǽ�����ʹ�õ�ǰ��������� */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL != ((MSCC_XSD_SRV_ACQ_REQ_STRU *)pstMsg)->enSrvType)
    {
        return VOS_TRUE;
    }

    /* ��������ȼ���ϵĻ�����Ϣ */
    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(VOS_PID_TIMER, TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_END_EMC_CALLBACK_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_MO_CALL_END_NTF);

    (VOS_VOID)CNAS_XSD_ClearCacheMsgByMsgName(UEPS_PID_MSCC, ID_MSCC_XSD_SRV_ACQ_REQ);

    /* ����ǰ���ڸ������ȼ��Ĵ�ϵĻ�����Ϣ�����Ա���Ϣ */
    if (0 != CNAS_XSD_GetCacheMsgNum())
    {
        return VOS_TRUE;
    }

    /* ���ҵ�������ǽ����������������������б� */
    CNAS_XSD_BuildEmcCallRedialScanChanList();

    /* ����ǰ�����ڸ������ȼ��Ļ�����Ϣ�������µĴ�� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* �����д�����Ϣ�����ҵ�񴥷�������� */
    CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasOhmInd
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬�յ�ID_MSCC_XSD_MO_CALL_END_NTF��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvMsccCallEndNtf_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstLastSyncedSys       = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU             st1xSysInfo;
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene;

    enAcqScene                          = CNAS_XSD_GetCurSysAcqScene_SysAcq();
    NAS_MEM_SET_S(&st1xSysInfo, sizeof(st1xSysInfo), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));
    pstLastSyncedSys                    = CNAS_XSD_GetLastSyncedSys();

    /* �ǽ�������������� */
    if ((VOS_FALSE == CNAS_XSD_IsEmcSDSysAcq_SysAcq(enAcqScene))
     && (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL != enAcqScene))

    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    st1xSysInfo.usSid                   = pstLastSyncedSys->usSid;
    st1xSysInfo.usNid                   = pstLastSyncedSys->usNid;
    st1xSysInfo.stFreq                  = CNAS_XSD_GetHistorySyncedSysFreqList()->astFreq[0];

    /* �����������У���ϴ��� */
    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����ǰϵͳ��Ч���ӳٴ�� */
    if (VOS_TRUE != CNAS_XSD_IsCurSysNotSuitableSys(&st1xSysInfo, VOS_FALSE, 0))
    {
        /* ����״̬����ϱ�� */
        CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

        return VOS_TRUE;
    }

    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND);

    CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ABORTED,
                           CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                           CNAS_XSD_IsImmediateSysAcq_SysAcq());

    /* �˳����״̬�� */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasOhmInd
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_NETWORK_SRCH_PROTECT_TIMER��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackNetWorkSrchTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasOhmInd
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬�յ�TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvTiEmcCallBackModeProtectTimerExpired_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* ����ҵ�񴥷��������� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasOhmInd
 ��������  : CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬�յ�ID_MSCC_XSD_END_EMC_CALLBACK_REQ��Ϣ�Ĵ���
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
VOS_UINT32 CNAS_XSD_RcvMsccEndEmcCallBackReq_SysAcq_WaitCasOhmInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == CNAS_XSD_GetAbortFlg_SysAcq())
    {
        return VOS_TRUE;
    }

    /* �����˳�CallBackģʽ���� */
    CNAS_XSD_SaveCacheMsg(ulEventType, pstMsg);

    /* ����״̬����ϱ�� */
    CNAS_XSD_SetAbortFlg_SysAcq(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateScanListChanStatusUponReceivedDeterminInd
 ��������  : �յ�determine ind��, ����determine indʧ�ܵ�Ƶ��
 �������  : usBeginScanListIndex -- ��ʼ����
             pstFreq              -- ��Ҫˢ�µ�Ƶ��
             pstScanChanList      -- �����б�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��7��9��
   ��    ��   : y00245242
   �޸�����   : iteration 17����

 2.��    ��   : 2015��09��09��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateScanListChanStatusUponReceivedDeterminInd(
    VOS_UINT16                                              usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT16                          usCurFreqIndex;

    usCurFreqIndex = usBeginScanListIndex;

    if (usCurFreqIndex > 0)
    {
        usCurFreqIndex--;
    }

    /* �������OOC�����µ�MRU0����Ƶ�㣬��scan list��ǰ������ʼ���ң�ֱ���ҵ���Ƶ��ˢ��Ϊͬ�������� */
    if (VOS_FALSE == CNAS_XSD_IsMru0FreqInOocScene(pstFreq))
    {
        CNAS_XSD_UpdateChanStatusInScanChanList(usCurFreqIndex,
                                                pstFreq,
                                                CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                pstScanChanList);

        return;
    }

    /* �����OOC�����µ�MRU0����Ƶ�㣬ֻ�ܴ�scan list��ʼλ��0����ǰ�������ң�������Ƶ�㲻Ҫˢ�� */
    CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                          usCurFreqIndex,
                                                          pstFreq,
                                                          pstScanChanList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateGeoSysRecordStatusUponReceivedDeterminInd
 ��������  : �յ�determine ind��, ����GEOϵͳ��¼����״̬
 �������  : pstFreq              -- ��Ҫˢ�µ�Ƶ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��7��9��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateGeoSysRecordStatusUponReceivedDeterminInd(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;

    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    /* TO DO: ����ԭ������Ƿ���Ҫ���֣����� */
    CNAS_XSD_UpdateSysFreqStatusByFreqChanInGeoSysRecordSrchList(pstFreq,
                                                                 CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                                 pstGeoSysRecSrchList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsCurGeoListSrchedInGeoListSrchInfo
 ��������  : check��ǰGEO list��GEO list������Ϣ�Ƿ��Ѿ�������
 �������  : pstGeoListInfo -- match��GEO list��Ϣ

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurGeoListSrchedInGeoListSrchInfo(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo
)
{
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoListSrchInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    pstGeoListSrchInfo = CNAS_XSD_GetGeoSrchListInfoAddr();

    for (i = 0; i< pstGeoListInfo->ucGeoNum; i++)
    {
        for (j = 0; j < pstGeoListSrchInfo->usGeoNum; j++)
        {
            if (pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex == pstGeoListSrchInfo->pstGeoSrchInfo[j].usGeoBeginIndex)
            {
                /* ֻҪ�����κ�һ��GEOδ������������Ϊδ������ */
                if (VOS_FALSE == pstGeoListSrchInfo->pstGeoSrchInfo[j].usGeoSrchStatus)
                {
                    return VOS_FALSE;
                }
            }
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetMostMatched1xGeoList
 ��������  : ��ȡ��match��GEO list
 �������  : pstCurSysInfo ----��ǰϵͳ��Ϣ

 �������  : pstMostMatchGeoListInfo ----��match��GEO list��Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��9��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_GetMostMatched1xGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMostMatchGeoListInfo
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;

    /* ��ȡ����ƥ���GEO list */
    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    /* ��GEO list����match��GEO list */
    CNAS_PRL_GetAllMostMatched1xGeoFrom1xGeoList(pstCurSysInfo, &stGeoListInfo, pstMostMatchGeoListInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ConstructGeoSysRecordSrchList
 ��������  : ����GEO�����б�
 �������  : pstGeoListInfo----GEO list��Ϣ
             pstCurSysInfo ----��ǰϵͳ��Ϣ

 �������  : pstSysAcqList ----�����list
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_ConstructGeoSysRecordSrchList(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord        = VOS_NULL_PTR;
    VOS_UINT16                          usMorePrefSysNum;
    VOS_UINT16                          usMaxSysRecNum;
    VOS_UINT16                          usSysRecNum;
    VOS_UINT32                          i;

    usSysRecNum        = 0;
    usMorePrefSysNum = 0;
    usMaxSysRecNum     = 0;

    /* ��������GEO�б��а�����ϵͳ��¼���� */
    for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        usMaxSysRecNum += pstGeoListInfo->astGeoInfoList[i].usGeoSysRecNum;
    }

    /* �����ڴ�ռ� */
    pstSysRecord = (CNAS_PRL_EXT_SYS_RECORD_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                usMaxSysRecNum * sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));

    if (VOS_NULL_PTR == pstSysRecord)
    {
        return;
    }

    CNAS_XSD_BuildCompsiteGeoFromMostMatchedGeoList(pstGeoListInfo,
                                                    &usSysRecNum,
                                                    pstSysRecord,
                                                    &usMorePrefSysNum);

    /* ����ϵͳ�����б� */
    CNAS_XSD_BuildGeoSysRecordSrchList(pstCurSysInfo,
                                       usSysRecNum,
                                       pstSysRecord,
                                       pstGeoSysRecSrchList,
                                       usMorePrefSysNum);

    /* ��¼����GEOϵͳ��¼�����б�������Щ���ٸ�GEO��ɼ����ǵ��׸����� */
    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {

        /* ��ǰ������������ΪGEOϵͳ��¼�����б����׸�ϵͳ��¼���� */
        pstGeoSysRecSrchList->usCurSrchLevel            = pstGeoSysRecSrchList->pstAcqSysInfo[0].usLevel;

        pstGeoSysRecSrchList->stCurSyncGeoInfo.usGeoNum = pstGeoListInfo->ucGeoNum;

        for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
        {
            pstGeoSysRecSrchList->stCurSyncGeoInfo.ausGeoFirstIndex[i] = pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex;
        }
    }

    /* ��Ҫ�ͷ�CNAS_PRL_BuildGeoSysRecList�й����system record */
    PS_MEM_FREE(UEPS_PID_XSD, pstSysRecord);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ContinueGeoSysRecordSrch
 ��������  : ����GEOϵͳ��¼�б��е�Ƶ������
 �������  : ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_ContinueGeoSysRecordSrch(VOS_VOID)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usDstChanNum;

    /*******************************************************************************************
     * 1. ����GEOϵͳ��¼Ƶ���б�����
     ******************************************************************************************/
    usDstChanNum = 0;

    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    CNAS_XSD_GetNextSysSyncListFromGeoSysRecordSrchList(CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq(),
                                                        &usDstChanNum,
                                                        &astDstChan[0]);

    if (0 != usDstChanNum)
    {
        /* ����GEOϵͳ��¼Ƶ��ͬ������ */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, &astDstChan[0]);

        return;
    }

    /*******************************************************************************************
     * 2. ���GEO�����б�״̬�Լ��ͷ�GEOϵͳ��¼�����б��ڴ�
     ******************************************************************************************/
    /* �����GEO�����б�״̬ */
    CNAS_XSD_ClearGeoSrchListStatus();

    /* �ͷ�GEOϵͳ��¼�����б���ڴ� */
    if (VOS_NULL_PTR != CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo);
        CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq()->pstAcqSysInfo = VOS_NULL_PTR;
    }

    /*******************************************************************************************
     * 3. ����scan listƵ���б�����
     ******************************************************************************************/
    pstScanList        = CNAS_XSD_GetScanChanListAddr();

    CNAS_XSD_GetNextScanChanList_SysAcq(CNAS_XSD_GetCurChannelScanIndex(),
                                        &usDstChanNum,
                                        astDstChan,
                                        pstScanList);

    if (0 != usDstChanNum)
    {
        /* scan listδȫ��ͬ���꣬������ͬ������ */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);

        return;
    }

    /*******************************************************************************************
     * 4. ����scan listͬ����ɵĺ�������
     ******************************************************************************************/
    /* scan list��ȫ��ͬ���� */
    CNAS_XSD_ProcScanListSyncComplete_SysAcq();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ContinueAvailSysListSrch
 ��������  : ����availableϵͳ�б�����
 �������  : ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_ContinueAvailSysListSrch(VOS_VOID)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usDstChanNum;

    usDstChanNum = 0;

    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    /***********************************************************************************************
     * 1. ����available listͬ��
     **********************************************************************************************/
    /* ��ȡ�´�ͬ��availableϵͳ */
    CNAS_XSD_GetNextAvailSysAcqList_SysAcq(&usDstChanNum, &astDstChan[0]);

    if (0 != usDstChanNum)
    {
        /* ����available system listƵ��ͬ�� */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, &astDstChan[0]);

        return;
    }

    /***********************************************************************************************
     * 2. available system list��û����Ҫͬ����Ƶ�㣬�˳�L2״̬��
     **********************************************************************************************/
    /* �˳�״̬��ʱ���available list */
    CNAS_XSD_InitAvailSysList(CNAS_XSD_INIT_CTX_STARTUP, CNAS_XSD_GetAvailSysFreqListAddr());

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_XSD_SndSysAcqRslt(CNAS_XSD_SYSTEM_ACQUIRED_RESULT_FAILURE,
                           CNAS_XSD_GetCurSysAcqScene_SysAcq(),
                           CNAS_XSD_IsImmediateSysAcq_SysAcq());

    /* �˳����״̬�� */
    CNAS_XSD_QuitFsmSysAcq_SysAcq();

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsCurrSysMostPref1xSysInGeoSysRecordSrchList
 ��������  : check��ǰϵͳ�Ƿ���GEOϵͳ��¼�����б��������ȵ�ϵͳ

             ע: �ڵ��øú���֮ǰ����Ҫcheckϵͳ�Ƿ���negativeϵͳ������negative
                 ϵͳ���ܻᱻѡ��!!!

 �������  : pstCurSysInfo        -- ͬ����ϵͳ��Ϣ
             pstGeoSysRecSrchList -- GEOϵͳ��¼�����б�

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ��ĿǰGEO�����ŵ�ϵͳ
             VOS_FALSE -- ����ĿǰGEO�����ŵ�ϵͳ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurrSysMostPref1xSysInGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                          i;

    /***********************************************************************************************
     * ע: �ú������治��Ҫ���ж��Ƿ���negativeϵͳ�ˣ���Ϊ�ڵ��øú���ǰ���Ѿ��ж���ϵͳ�Ƿ���
     *     negativeϵͳ��
     *     ���øú���ǰ��������ǰcheckϵͳ�Ƿ���negativeϵͳ������negativeϵͳ���ܻᱻѡ��!!!
     **********************************************************************************************/

#if 0
    /* ��ǰϵͳ��SID����SID�������У�����Ϊ�����ȵ�ϵͳ */
    if (VOS_FALSE == CNAS_XSD_IsSidInOperLockWhiteSidList(pstCurSysInfo->usSid))
    {
        return VOS_FALSE;
    }
#endif

    /* �����ǰͬ������ϵͳ�뵱ǰlevel�е�ϵͳƥ�䣬�����פ�� */
    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++ )
    {
        /* �����뵱ǰͬ����level��ͬ��ϵͳ */
        if (pstGeoSysRecSrchList->usCurSrchLevel != pstGeoSysRecSrchList->pstAcqSysInfo[i].usLevel)
        {
            continue;
        }

        /* ����ͬ�������ڵ�Ƶ�� */
        if (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST == pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus)
        {
            continue;
        }

        /* ������ǰƵ����ϵͳSID/NID��ƥ���ϵͳ */
        if (VOS_FALSE == CNAS_PRL_Is1xSysMatched(pstCurSysInfo,
                                                 &(pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys)))
        {
            continue;
        }

#if 0
        /* ��ǰϵͳ�����ȵ�ϵͳ */
        if (CNAS_PRL_PREF_NEG_SYS_PREF == pstGeoSysRecSrchList->pstAcqSysInfo[i].enPrefNegSys)
        {
            return VOS_TRUE;
        }

        /* �����negativeϵͳ������home SID/NID�б��У���Ȼ������һ��prefϵͳ���� */
        if (VOS_TRUE == CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo))
        {
            return VOS_TRUE;
        }
#endif

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsCurSysInGeoSysRecordSrchList
 ��������  : check��ǰϵͳ�Ƿ���GEOϵͳ��¼�����б���
 �������  : pstCurSysInfo -- ͬ����ϵͳ��Ϣ
             pstSysAcqList -- GEOϵͳ��¼�����б�

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ��ĿǰGEO�����ŵ�ϵͳ
             VOS_FALSE -- ����ĿǰGEO�����ŵ�ϵͳ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSysInGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                          i;

    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++ )
    {
        /* ������ǰƵ����ϵͳSID/NID��ƥ���ϵͳ */
        if (VOS_TRUE == CNAS_PRL_Is1xSysMatched(pstCurSysInfo,
                                                &(pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsCurSysGeoListSameAsCurSyncGeoInfo
 ��������  : check��ǰϵͳ�Ƿ���GEOϵͳ��¼�����б���
 �������  : pstGeoListInfo -- ��ǰϵͳͬ������GEO��Ϣ
             pstSysAcqList  -- GEOϵͳ��¼�����б�

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ��ĿǰGEO�����ŵ�ϵͳ
             VOS_FALSE -- ����ĿǰGEO�����ŵ�ϵͳ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSysGeoListSameAsCurSyncGeoInfo(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT32                          i;

    if (pstGeoListInfo->ucGeoNum != pstGeoSysRecSrchList->stCurSyncGeoInfo.usGeoNum)
    {
        return VOS_FALSE;
    }

    for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        if (pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex != pstGeoSysRecSrchList->stCurSyncGeoInfo.ausGeoFirstIndex[i])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_PreformBestPreferedSystemSelectionAndNoGeoSysRecordSearchList_SysAcq
 ��������  : ���������ȵ�ϵͳѡ����GEOϵͳ��¼�����б�����
 �������  : pstSyncCnf----ͬ���ظ���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_VOID CNAS_XSD_PreformBestPreferedSystemSelectionAndNoGeoSysRecordSearchList_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                                              usDstChanNum;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;
    VOS_UINT16                                              usCurScanListIndex;
    CNAS_PRL_1X_SYSTEM_STRU                                 stCurSysInfo;
    VOS_UINT32                                              ulIsNegSys;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList = VOS_NULL_PTR;

    /***********************************************************************************************
     * 1. ˢ��availableϵͳ�´�������������֪ͨ�����פ����ǰͬ������ϵͳ
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        usCurScanListIndex = CNAS_XSD_GetAvailSysFreqListNextSrchIndex();

        /* ����ʧ�ܵ�Ƶ������Լ���ǰ�ɹ���Ƶ����� */
        CNAS_XSD_SetAvailSysFeqListNextSrchIndex((VOS_UINT8)(usCurScanListIndex + pstSyncCnf->ulSyncFailFreqNum + 1));

        /* �����ϵͳ��SID�������У������ֱ��פ�� */
        if (VOS_TRUE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstSyncCnf->stSyncedSysId.usSid))
        {
            /* ����ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
            CNAS_XSD_SndCas1xCampSyncedChannelNtf();

            /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_OHM_IND */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

            /* ����������ʱ�� */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

            return;
        }

        /* ����availableϵͳ���� */
        CNAS_XSD_ContinueAvailSysListSrch();

        return;
    }

    /***********************************************************************************************
     * 2. ��ǰϵͳ��PRL���д���
     **********************************************************************************************/
    stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
    stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
    stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_XSD_GetMostMatched1xGeoList(&stCurSysInfo, &stGeoListInfo);

    if (0 != stGeoListInfo.ucGeoNum)
    {

        ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo, VOS_FALSE, 0);

        if (VOS_TRUE == ulIsNegSys)
        {
            CNAS_WARNING_LOG(UEPS_PID_XSD,
                             "CNAS_XSD_PreformBestPreferedSystemSelectionAndNoGeoSysRecordSearchList_SysAcq: Curr System is Neg!")
        }

        /* ʹ��һ���µ�GEO�������ŵ�ϵͳѡ�� */
        CNAS_XSD_PeformBestPreferedSystemSelectionUsingNewGeo_SysAcq(&stGeoListInfo,
                                                                     &stCurSysInfo,
                                                                     ulIsNegSys);

        return;
    }

    /***********************************************************************************************
     * 3. �����ǰϵͳ����PRL���У���ϵͳ��homeϵͳ���򲶻��ϵͳ
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_IsCurSysHomeSystemIndependenceOnPrl(&stCurSysInfo))
    {
        /* ����ǰ֪ͨ�ϲ����״̬ */
        CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

        /* ����ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
        CNAS_XSD_SndCas1xCampSyncedChannelNtf();

        /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_OHM_IND */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

        /* ����������ʱ�� */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

        return;
    }

    /***********************************************************************************************
     * 4. ͬ������ϵͳ��availableϵͳ�������scan list�ж�ӦƵ��״̬�ٴ�ˢΪ�����ڣ�������������ͬ��
     **********************************************************************************************/
    pstScanList = CNAS_XSD_GetScanChanListAddr();

    usCurScanListIndex = pstScanList->usCurScanIndex;

    CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq((CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncCnf->stFreq),
                                                                   pstScanList);

    /***********************************************************************************************
     * 5. �����ǰϵͳ��availableϵͳ���ϱ�������Ϣ��ͬʱˢ��available list
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_PRL_GetPrefOnlyFlg())
    {
        /* check��ǰavailableϵͳ�Ƿ��ڰ��������ڰ������У�����ӵ�availableϵͳ�У��ϱ�������� */
        if (VOS_TRUE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstSyncCnf->stSyncedSysId.usSid))
        {
             /* ֪ͨ����ɻ��ָʾ */
            CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

            /* ˢ��available list */
            CNAS_XSD_AddAvailSysFreqList(&(stCurSysInfo.stFreq));
        }
    }

    /***********************************************************************************************
     * 6. ����scan listƵ���б�����
     **********************************************************************************************/
    usDstChanNum       = 0;

    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    CNAS_XSD_GetNextScanChanList_SysAcq(usCurScanListIndex, &usDstChanNum, astDstChan, pstScanList);

    if (0 != usDstChanNum)
    {
        /* ����scan listͬ������ */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);

        return;
    }

    /*******************************************************************************************
     * 7. ����scan listͬ����ɵĺ�������
     ******************************************************************************************/
    CNAS_XSD_ProcScanListSyncComplete_SysAcq();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_PreformBestPreferedSystemSelectionAndGeoSysRecorSearchListExist_SysAcq
 ��������  : ���������ȵ�ϵͳѡ����GEOϵͳ��¼�����б����
 �������  : pstSyncCnf----ͬ���ظ���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

  2.��    ��   : 2015��9��11��
    ��    ��   : y00245242
    �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_PreformBestPreferedSystemSelectionAndGeoSysRecordSearchListExist_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;
    CNAS_PRL_1X_SYSTEM_STRU                                 stCurSysInfo;
    VOS_UINT32                                              ulIsNegSys;
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU                         stSyncFailChan;
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;

    /***********************************************************************************************
     * 1. ˢ��GEOϵͳ��¼�����б�
     *    ע: negativeϵͳ����Ҫˢ��scan list�е�Ƶ�㣬��Ϊnegativeϵͳ�Ѿ���֮ǰ�ӵ�avoid�б����ˣ�
     *        ����һ��ͬ������ʱ���ᱻ���˵�
     **********************************************************************************************/
    stCurSysInfo.stFreq.enBandClass = pstSyncCnf->stFreq.usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;
    stCurSysInfo.usNid              = pstSyncCnf->stSyncedSysId.usNid;
    stCurSysInfo.usSid              = pstSyncCnf->stSyncedSysId.usSid;

    ulIsNegSys = CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo, VOS_FALSE, 0);

    if (VOS_FALSE == ulIsNegSys)
    {
        /* ˢ�µ�ǰͬ���ɹ���Ƶ��״̬��GEO��ϵͳ��¼�����б�����match��ϵͳƵ��ˢ��Ϊ�������ڣ�����Ϊ���������� */
        CNAS_XSD_UpdateSyncSuccFreqStatusInGeoSysRecordSrchList_SysAcq(&(pstSyncCnf->stFreq),
                                                                       &(pstSyncCnf->stSyncedSysId));
    }
    else
    {
        stSyncFailChan.stFreq.usBandClass = pstSyncCnf->stFreq.usBandClass;
        stSyncFailChan.stFreq.usChannel   = pstSyncCnf->stFreq.usChannel;

        /* ��ǰϵͳ��negativeϵͳ��ˢ��״̬Ϊ���������� */
        CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq(1, &stSyncFailChan);

        /* ����ϵͳ��negʱ����ˢ�¸�Ƶ��Ϊ�����ڣ������ˢ�µĻ�������ͬ����Ȼ��ͬ����Ƶ��
           ��ȡ��һ��ͬ��Ƶ��ʱ���߼�Ϊδͬ������ͬ������ */
        CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq(&stCurSysInfo.stFreq,
                                                                       CNAS_XSD_GetScanChanListAddr());
    }

    /* ˢ�µ�ǰͬ��ʧ�ܵ�Ƶ�� */
    CNAS_XSD_UpdateSyncFailFreqStatusInGeoSysRecordSrchList_SysAcq((VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                                   &(pstSyncCnf->astSyncRsltList[0]));

    /***********************************************************************************************
     * 2. ��ǰϵͳ��PRL���д���
     **********************************************************************************************/
    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_XSD_GetMostMatched1xGeoList(&stCurSysInfo, &stGeoListInfo);

    if (0 != stGeoListInfo.ucGeoNum)
    {
        /***********************************************************************************************
         * 1.1. ��ǰϵͳ��GEOϵͳ�����б��д���
         **********************************************************************************************/
        pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

        if (VOS_TRUE == CNAS_XSD_IsCurSysInGeoSysRecordSrchList(&stCurSysInfo, pstGeoSysRecSrchList))
        {
            /***************************************************************************************
             * i ��ǰϵͳ����ֱ��פ������
             **************************************************************************************/
            /* ����scan list���б��е�Ƶ��״̬��ˢ��GEOϵͳ��¼�����б��е�Ƶ��״̬���´��������� */
            CNAS_XSD_UpdateGeoSysRecordListInfoAccordingToScanChanList(pstGeoSysRecSrchList);

            /* ��ǰϵͳ�Ǹ����ȼ�ϵͳ */
            if (VOS_TRUE == CNAS_XSD_IsCurrSysMostPref1xSysInGeoSysRecordSrchList(&stCurSysInfo, pstGeoSysRecSrchList))
            {
                /* ����ǰ֪ͨ�ϲ����״̬ */
                CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

                /* ����ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
                CNAS_XSD_SndCas1xCampSyncedChannelNtf();

                /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_OHM_IND */
                CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

                /* ����������ʱ�� */
                CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

                return;
            }

            /***************************************************************************************
             * ii ����GEOϵͳ��¼�����б�����
             **************************************************************************************/
            CNAS_XSD_ContinueGeoSysRecordSrch();
            return;
        }

        /*******************************************************************************************
         * 1.2 ��ǰͬ������ϵͳ��GEOϵͳ�����б��еĵ����ȼ�ϵͳ, ����GEOϵͳ��¼�����б�����
         *     ע: GEOϵͳ��¼�����б��ڹ���ʱ��������˵�ǰͬ����ϵͳ�Լ���GEO�б������ȼ��ߵ�ϵͳ��
                   �����ȼ�ϵͳ��û�зŵ�GEOϵͳ�����б��С�������жϵ�ǰϵͳ�Ƿ���GEOϵͳ��¼����
                   �б��еĵ����ȼ�ϵͳ��ԭ������:
                   1. ��ǰͬ������ϵͳ����GEOϵͳ��¼�����б��У���
                   2. ��ǰͬ������ϵͳ��PRL���е�GEO�뵱ǰ����ͬ����GEO��Ϣһ��
                   ������������������Ϊ��GEO�е����ȼ�ϵͳ�����򽫼�����ǰ��GEOϵͳ��¼�����б��и�
                   ����Ƶ��ͬ��
         *******************************************************************************************/
        if (VOS_TRUE == CNAS_XSD_IsCurSysGeoListSameAsCurSyncGeoInfo(&stGeoListInfo, pstGeoSysRecSrchList))
        {
            CNAS_XSD_ContinueGeoSysRecordSrch();

            return;
        }

        /*******************************************************************************************
         * 1.3 ��ǰϵͳ���µ�GEO�����Ѿ�������,��������:
         *     i)  �����negativeϵͳ����ǰ����GEO����������
         *     ii) ֱ��פ����ǰϵͳ
         *******************************************************************************************/
        /* ������Ǹ��µ�GEO�����µ�GEO�Ѿ���������ֱ��פ����ǰϵͳ�����������ѭ�� */
        if (VOS_TRUE == CNAS_XSD_IsCurGeoListSrchedInGeoListSrchInfo(&stGeoListInfo))
        {
            if (VOS_TRUE == ulIsNegSys)
            {
                CNAS_XSD_ContinueGeoSysRecordSrch();

                return;
            }

            /* ����ǰ֪ͨ�ϲ����״̬ */
            CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

            /* ����ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
            CNAS_XSD_SndCas1xCampSyncedChannelNtf();

            /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_OHM_IND */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

            /* ����������ʱ�� */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

            return;
        }

        /*******************************************************************************************
         * 1.4. ����δ���������µ�GEO���ͷ��ϵ�GEOϵͳ��¼�����б������µ�GEO����ϵͳѡ��
         ******************************************************************************************/
        /* �ͷŵ�ǰ��GEOϵͳ��¼�����б� */
        PS_MEM_FREE(UEPS_PID_XSD, pstGeoSysRecSrchList->pstAcqSysInfo);
        pstGeoSysRecSrchList->pstAcqSysInfo = VOS_NULL_PTR;

        /* ʹ��һ���µ�GEO�������ŵ�ϵͳѡ�� */
        CNAS_XSD_PeformBestPreferedSystemSelectionUsingNewGeo_SysAcq(&stGeoListInfo,
                                                                     &stCurSysInfo,
                                                                     ulIsNegSys);

        return;
    }

    /***********************************************************************************************
     * 3. �����ǰϵͳ����PRL���У���ϵͳ��homeϵͳ���򲶻��ϵͳ
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_IsCurSysHomeSystemIndependenceOnPrl(&stCurSysInfo))
    {
        /* ����ǰ֪ͨ�ϲ����״̬ */
        CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

        /* ����ID_CNAS_CAS_1X_CAMP_SYNCED_CHANNEL_NTF */
        CNAS_XSD_SndCas1xCampSyncedChannelNtf();

        /* Ǩ�Ƶ� CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND״̬, ������������ʱ��TI_CNAS_XSD_WAIT_CAS_OHM_IND */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_SYS_ACQ_STA_WAIT_CAS_OHM_IND);

        /* ����������ʱ�� */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_OHM_IND, TI_CNAS_XSD_WAIT_CAS_OHM_IND_LEN);

        return;
    }

    /***********************************************************************************************
     * 4. ͬ������ϵͳ��availableϵͳ�������scan list�ж�ӦƵ��״̬�ٴ�ˢΪ������
     **********************************************************************************************/
    CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq(&stCurSysInfo.stFreq,
                                                                   CNAS_XSD_GetScanChanListAddr());

    /***********************************************************************************************
     * 5. �����ǰϵͳ��availableϵͳ���ϱ�������Ϣ��ͬʱˢ��available list
     **********************************************************************************************/
    if (VOS_FALSE == CNAS_PRL_GetPrefOnlyFlg())
    {
        /* check��ǰavailableϵͳ�Ƿ��ڰ��������ڰ������У�����ӵ�availableϵͳ�У��ϱ�������� */
        if (VOS_TRUE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstSyncCnf->stSyncedSysId.usSid))
        {
            /* ����ǰ֪ͨ�ϲ����״̬ */
            CNAS_XSD_ReportSrvAvailableInd_SysAcq(&stCurSysInfo);

            /* ˢ��available list */
            CNAS_XSD_AddAvailSysFreqList(&(stCurSysInfo.stFreq));
        }
    }

    /***********************************************************************************************
     * 6. ����GEOϵͳ��¼�����б�����
     **********************************************************************************************/
    CNAS_XSD_ContinueGeoSysRecordSrch();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcSyncFailAndNoGeoSysRecorSearchList_SysAcq
 ��������  : �յ�CAS��ͬ���ظ�ʧ�ܣ�����GEOϵͳ��¼����list
 �������  : pstSyncCnf -- ϵͳͬ�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_ProcSyncFailAndNoGeoSysRecorSearchList_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      astDstChan[CNAS_CAS_1X_MAX_FREQ_NUM];
    VOS_UINT16                          usCurScanListIndex;
    VOS_UINT16                          usDstChanNum;

    /***********************************************************************************************
     * 1. ����availableϵͳƵ��ͬ��
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        /* ����availableϵͳ�´��������� */
        usCurScanListIndex = CNAS_XSD_GetAvailSysFreqListNextSrchIndex();

        CNAS_XSD_SetAvailSysFeqListNextSrchIndex((VOS_UINT8)(usCurScanListIndex + pstSyncCnf->ulSyncFailFreqNum));

        CNAS_XSD_ContinueAvailSysListSrch();

        return;
    }

    /*******************************************************************************************
     * 2. ����scan listͬ��
     ******************************************************************************************/
    usDstChanNum       = 0;

    NAS_MEM_SET_S(&astDstChan[0], sizeof(astDstChan), 0, sizeof(astDstChan));

    pstScanList = CNAS_XSD_GetScanChanListAddr();

    CNAS_XSD_GetNextScanChanList_SysAcq(CNAS_XSD_GetCurChannelScanIndex(),
                                        &usDstChanNum,
                                        astDstChan,
                                        pstScanList);

    if (0 != usDstChanNum)
    {
        /* scan listδȫ��ͬ���꣬������ͬ������ */
        CNAS_XSD_ContinueSyncScanList_SysAcq(usDstChanNum, astDstChan);

        return;
    }

    /*******************************************************************************************
     * 3. ����scan listͬ����ĺ�����������
     ******************************************************************************************/
    /* scan list��ȫ��ͬ���� */
    CNAS_XSD_ProcScanListSyncComplete_SysAcq();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReportSrvAvailableInd_SysAcq
 ��������  : �ϱ�����״̬���ָʾ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_ReportSrvAvailableInd_SysAcq(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo
)
{
    XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU                stSrvAvailableInd;
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enServiceStatus;
    CNAS_XSD_SERVICE_STATUS_ENUM_UINT32                     enXsdCurSrvStatus;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8                         enCardStatus;

    /* ��ǰ����״̬����normal service������Ҫ�ϱ�����״̬ */
    if (CNAS_XSD_SERVICE_STATUS_NORMAL_SERVICE == CNAS_XSD_GetCurSrvStatus())
    {
        return;
    }

    enCardStatus = CNAS_CCB_GetCsimCardStatus();

    if ( CNAS_CCB_CARD_STATUS_ABSENT == enCardStatus )
    {
        enXsdCurSrvStatus = CNAS_XSD_SERVICE_STATUS_LIMITED_SERVICE;
        enServiceStatus   = NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE;
    }
    else
    {
        enXsdCurSrvStatus = CNAS_XSD_SERVICE_STATUS_NORMAL_SERVICE;
        enServiceStatus   = NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE;
    }

    /* ���µ�ǰ�ķ���״̬Ϊnormal service */
    CNAS_XSD_SetCurSrvStatus(enXsdCurSrvStatus);

    NAS_MEM_SET_S(&stSrvAvailableInd, sizeof(stSrvAvailableInd), 0, sizeof(XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU));

    stSrvAvailableInd.usFreq          = pstCurSysInfo->stFreq.usChannel;
    stSrvAvailableInd.usBandClass     = pstCurSysInfo->stFreq.enBandClass;
    stSrvAvailableInd.usNid           = pstCurSysInfo->usNid;
    stSrvAvailableInd.usSid           = pstCurSysInfo->usSid;
    stSrvAvailableInd.enServiceStatus = enServiceStatus;
    stSrvAvailableInd.ucRoamingInd    = CNAS_XSD_GetCurrentSystemRoamingInd(pstCurSysInfo);

    CNAS_XSD_SndMsccSyncServiceAvailableInd(&stSrvAvailableInd);
    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsCallRelAnyCampOnFreq_SysAcq
 ��������  : �ϱ�����״̬���ָʾ
 �������  : pstFreq -- ��ǰͬ���ɹ���Ƶ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ���״�ͬ����Ƶ��
             VOS_FALSE -- ���״�ͬ����Ƶ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCallRelAnyCampOnFreq_SysAcq(
    CNAS_CAS_1X_FREQENCY_CHANNEL_STRU                      *pstFreq
)
{
    CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU                *pstCallRelAnyCampOnFreq = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstCallRelAnyCampOnFreq = CNAS_XSD_GetCallRelAnyCampOnFreqListAddr();

    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstCallRelAnyCampOnFreq->usChanNum, CNAS_XSD_CALL_REL_SYNC_MAX_FREQ_NUM); i++)
    {
        if ((pstFreq->usBandClass == pstCallRelAnyCampOnFreq->astFreq[i].enBandClass)
         && (pstFreq->usChannel   == pstCallRelAnyCampOnFreq->astFreq[i].usChannel))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateSyncSuccChanStatus_SysAcq
 ��������  : ����ɨ��ɹ���Ƶ��״̬
 �������  : VOS_UINT16                                     usBeginScanListIndex
             CNAS_PRL_FREQENCY_CHANNEL_STRU                *pstChannel
             CNAS_XSD_SCAN_CHANNEL_LIST_STRU               *pstScanChanList
             CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU        *pstGeoSysRecSrchList
 �������  : ��
 �� �� ֵ  : VOS_UINT16 -- ���ص�ǰͬ���ɹ���Ƶ����scan list�е�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��8��
    ��    ��   : y00245242
    �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateSyncSuccChanStatus_SysAcq(
    VOS_UINT16                                              usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstChannel,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                                              usCurFreqIndex;

    /***********************************************************************************************
       ͬ���ɹ���Ƶ�㴦��
       i�� �����GEOͬ���������OOC�����µ�MRU0����Ƶ�㣬��ˢ�£�������Ҫ��scan list��ǰ��������
           ˢ�¸�Ƶ�㣻

       ii���������GEOͬ�������scan list��ǰ�����������ˢ�¸�Ƶ��
     **********************************************************************************************/

    usCurFreqIndex = usBeginScanListIndex;

    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        if (VOS_TRUE == CNAS_XSD_IsMru0FreqInOocScene(pstChannel))
        {
            return usCurFreqIndex;
        }
    }

    usCurFreqIndex = CNAS_XSD_UpdateChanStatusInScanChanList(usBeginScanListIndex,
                                                             pstChannel,
                                                             CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST,
                                                             pstScanChanList);

    return usCurFreqIndex;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateSyncFailChanStatus_SysAcq
 ��������  : ����ɨ��ʧ�ܵ�Ƶ��״̬
 �������  : usBeginScanListIndex ------------��ʼ����Ƶ���index
             usSyncFailChanNum ---------------ͬ��ʧ�ܵ�Ƶ�����
             pstSyncFailChanList ------------ ͬ��ʧ�ܵ�Ƶ���б�
             pstScanChanList -----------------��ǰ��Ƶ��ɨ���б�
             pstGeoSysRecSrchList-------------GEO�����µ������б���Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT16 -- ���ص�ǰˢ�µ����һ��ʧ��Ƶ����scan list�е�����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��9��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateSyncFailChanStatus_SysAcq(
    VOS_UINT16                                              usBeginScanListIndex,
    VOS_UINT16                                              usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU                        *pstSyncFailChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                                              i;
    VOS_UINT16                                              usCurFreqIndex;
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru0SysId;
    VOS_UINT16                                              ulMru0FreqIndex;


    /***********************************************************************************************
       a. ͬ��ʧ�ܵ�Ƶ�㴦��
          i)  �����GEOͬ�����������MRU0����Ƶ�㣬����Ҫ��scan list��ǰ��������ˢ��ʧ�ܵ�Ƶ�㣻��
              ����Ҫ��scan listͷ������ǰ������������MRU0Ƶ��ˢ��Ϊͬ�������ڣ�ȷ��״̬һ���ԣ�
          ii���������GEOͬ������scan list��ǰ�����������ˢ��ʧ�ܵ�Ƶ�㣻
     **********************************************************************************************/

    usCurFreqIndex = usBeginScanListIndex;

    /* GEOͬ������ */
    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        ulMru0FreqIndex = CNAS_XSD_INVAILD_SCAN_LIST_FREQ_INDEX;

        /* �������OOC��������û��MRU0Ƶ����볡�� */
        if (VOS_FALSE == CNAS_XSD_IsOocSceneAndRepeatMru0FreqSrchExist(&stMru0SysId))
        {
            ulMru0FreqIndex = CNAS_XSD_INVAILD_SCAN_LIST_FREQ_INDEX;
        }
        else
        {
            /* checkͬ��������Ƿ���MRU0Ƶ����� */
            for (i = 0; i < usSyncFailChanNum; i++)
            {
                if ((stMru0SysId.stFreq.enBandClass == pstSyncFailChanList[i].stFreq.usBandClass)
                 && (stMru0SysId.stFreq.usChannel   == pstSyncFailChanList[i].stFreq.usChannel))
                {
                    ulMru0FreqIndex = i;

                    break;
                }
            }
        }

        if (0xFFFF == ulMru0FreqIndex)
        {
            /* ����OOC�����µ�MRU0Ƶ�㣬��scan list��ǰ�����������ˢ��ʧ�ܵ�Ƶ�㣻 */
            usCurFreqIndex = CNAS_XSD_UpdateSyncFailChanStatus(usBeginScanListIndex,
                                                               usSyncFailChanNum,
                                                               pstSyncFailChanList,
                                                               pstScanChanList);

            return usCurFreqIndex;
        }

        for (i = 0; i < usSyncFailChanNum; i++)
        {
            /* ����MRU0��Ƶ��, ��ˢ��MRU0Ƶ�� */
            if (i == ulMru0FreqIndex)
            {
                continue;
            }

            usCurFreqIndex =
                CNAS_XSD_UpdateChanStatusInScanChanList(usBeginScanListIndex,
                                                        (CNAS_PRL_FREQENCY_CHANNEL_STRU *)&pstSyncFailChanList[i].stFreq,
                                                        CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                        pstScanChanList);
        }

        /* ����MRU0��Ƶ�㣬��Ҫ��scan listͷ������ǰ������������MRU0Ƶ��ˢ��Ϊͬ�������ڣ�ȷ��״̬һ���ԣ� */
        CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                              usBeginScanListIndex,
                                                              &(stMru0SysId.stFreq),
                                                              pstScanChanList);

        return usCurFreqIndex;
    }

    /* ����ֻˢ��ͬ�����ڵĻ�δͬ����Ƶ��Ƶ��״̬Ϊͬ�������� */
    for (i = 0; i < usSyncFailChanNum; i++)
    {
        usCurFreqIndex =
            CNAS_XSD_UpdateNoSyncedOrSyncSuccScanChanInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                                    usBeginScanListIndex,
                                                                    (CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncFailChanList[i].stFreq),
                                                                    pstScanChanList);

    }

    return usCurFreqIndex;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfSucc_SysAcq
 ��������  : �յ�CASͬ���ɹ�ʱ������Ƶ��״̬
 �������  : pstSyncCnf -- ͬ���ɹ���ȷ����Ϣ

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��9��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfSucc_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList          = VOS_NULL_PTR;
    VOS_UINT16                                              usCurScanListIndex;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstEmcScanChanList   = VOS_NULL_PTR;

    pstEmcScanChanList                  = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

    /***********************************************************************************************
     * 1. �����availableϵͳͬ�����򲻶�scan list��������
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        return;
    }

    pstScanList          = CNAS_XSD_GetScanChanListAddr();

    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();

    /***********************************************************************************************
     * 2. ͬ��ʧ�ܵ�Ƶ�㴦��
     **********************************************************************************************/
    if (0 != pstSyncCnf->ulSyncFailFreqNum)
    {
        /* ����ͬ��ʧ�ܵ�Ƶ��ˢ�� */
        usCurScanListIndex = CNAS_XSD_UpdateSyncFailChanStatus_SysAcq(pstScanList->usCurScanIndex,
                                                                      (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                                      &pstSyncCnf->astSyncRsltList[0],
                                                                      pstScanList,
                                                                      pstGeoSysRecSrchList);

        /* GEO������ʱ�����µ�ǰscan list�����������ӿ�ͬ���ɹ�Ƶ���ˢ�� */
        if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
        {
            CNAS_XSD_SetCurChannelScanIndex(usCurScanListIndex + 1);
        }

        /* ����������SD������ˢ�½�������Ƶ���б���������ظ���ͬ��ʧ�ܵ�Ƶ�� */
        if (VOS_NULL_PTR != pstEmcScanChanList->pstScanChanInfo)
        {
            if (VOS_TRUE == CNAS_XSD_IsEmcSDSysAcq_SysAcq(CNAS_XSD_GetCurSysAcqScene_SysAcq()))
            {
                (VOS_VOID)CNAS_XSD_UpdateSyncFailChanStatus(pstEmcScanChanList->usCurScanIndex,
                                                           (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                            pstSyncCnf->astSyncRsltList,
                                                            pstEmcScanChanList);
            }
        }
    }

    /***********************************************************************************************
     * 3. ͬ���ɹ���Ƶ�㴦��
     **********************************************************************************************/
    usCurScanListIndex = CNAS_XSD_UpdateSyncSuccChanStatus_SysAcq(pstScanList->usCurScanIndex,
                                                                  (CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncCnf->stFreq),
                                                                  pstScanList,
                                                                  pstGeoSysRecSrchList);

    /***********************************************************************************************
     * 4. �������GEOͬ������ͬ���ɹ���Ƶ���ǲ����MRU0Ƶ�㣻���scan listͷ������ǰ��������ָ��scan
     *    list�б���ͬ���ɹ���MRU0��Ƶ������������������MRU0Ƶ��ˢ��Ϊͬ�����ڣ�ȷ��״̬һ���ԣ�
     **********************************************************************************************/
    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        /* �ٴθ����´�scan list�������� */
        CNAS_XSD_SetCurChannelScanIndex(usCurScanListIndex + 1);


        /* ����OOC�����£�����ֲ���MRU0Ƶ�㣬Ϊ��ȷ��֮ǰ������Ƶ���뱾���ѵ���Ƶ��״̬һ�£������
         * ֮ǰ��Ƶ��Ҳˢ��ͬ���ɹ�
         */
        if (VOS_TRUE == CNAS_XSD_IsMru0FreqInOocScene((CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncCnf->stFreq)))
        {
            CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST,
                                                                  usCurScanListIndex,
                                                                  (CNAS_PRL_FREQENCY_CHANNEL_STRU *)&(pstSyncCnf->stFreq),
                                                                  pstScanList);
        }

        /* log scan list����״̬ */
        CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_SCAN_CHAN_LIST_IND, pstScanList);

    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfFail_SysAcq
 ��������  : �յ�CASͬ��ʧ��ʱ������Ƶ��״̬
 �������  : pstSyncCnf -- ͬ��ʧ�ܵ�ȷ����Ϣ

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��9��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateChanStatusUponRcvCasSyncCnfFail_SysAcq(
    CAS_CNAS_1X_SYSTEM_SYNC_CNF_STRU   *pstSyncCnf
)
{
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList          = VOS_NULL_PTR;
    VOS_UINT16                                              usCurScanListIndex;

    /***********************************************************************************************
     * 1 �����availableϵͳͬ�����򲻶�scan list������������
     **********************************************************************************************/
    /* availableϵͳͬ�������� */
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        return;
    }

    pstScanList          = CNAS_XSD_GetScanChanListAddr();

    pstGeoSysRecSrchList = CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq();


    /***********************************************************************************************
     * 2 �����GEOͬ�����������MRU0����Ƶ�㣬����Ҫ��scan list��ǰ��������ˢ��ʧ�ܵ�Ƶ�㣻������Ҫ��
     *   scan listͷ������ǰ������������MRU0Ƶ��ˢ��Ϊͬ�������ڣ�ȷ��״̬һ���ԣ�
    **********************************************************************************************/
    usCurScanListIndex = CNAS_XSD_UpdateSyncFailChanStatus_SysAcq(pstScanList->usCurScanIndex,
                                                                  (VOS_UINT16)pstSyncCnf->ulSyncFailFreqNum,
                                                                  &pstSyncCnf->astSyncRsltList[0],
                                                                  pstScanList,
                                                                  pstGeoSysRecSrchList);


    /***********************************************************************************************
     * 3 �������GEOͬ��������Ҫ��scan list��ǰ��������ˢ��ʧ�ܵ�Ƶ�㣻
     **********************************************************************************************/
    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        CNAS_XSD_SetCurChannelScanIndex(usCurScanListIndex + 1);

        /* log scan list����״̬ */
        CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_SCAN_CHAN_LIST_IND, pstScanList);
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateChanStatusUponRcvCasDeterminInd_SysAcq
 ��������  : �յ�CAS determine indʱ������Ƶ��״̬
 �������  : pstDetermineInd -- determine ind��Ϣ

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��9��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
 2.��    ��   : 2015��10��8��
   ��    ��   : c00299063
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateChanStatusUponRcvCasDeterminInd_SysAcq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstTempFreq
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList = VOS_NULL_PTR;

    /***********************************************************************************************
     * 1 �����availableϵͳͬ�����򲻶�scan list������������
     **********************************************************************************************/
    /* availableϵͳͬ�������� */
    if (VOS_TRUE == CNAS_XSD_GetAvailSysAcqListFlg_SysAcq())
    {
        return;
    }

    pstScanList = CNAS_XSD_GetScanChanListAddr();

    /***********************************************************************************************
     * 2 �����ǰʧ�ܵ�Ƶ����MRU0��Ƶ�㣬����Ҫ��scan listͷ������ǰ������������MRU0Ƶ��ˢ��Ϊͬ������
     *   �ڣ������scan listͷ������ǰ���������ҵ�ʧ�ܵ�Ƶ�������ѭ����
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_IsMru0FreqInOocScene(pstTempFreq))
    {
        CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                              pstScanList->usCurScanIndex,
                                                              pstTempFreq,
                                                              pstScanList);
    }
    else
    {

        (VOS_VOID)CNAS_XSD_UpdateChanStatusInScanChanList(0,
                                                          pstTempFreq,
                                                          CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                          pstScanList);

    }

    /* log scan list����״̬ */
    CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_SCAN_CHAN_LIST_IND, pstScanList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq
 ��������  : ����available��negativeϵͳƵ��״̬
 �������  : pstChannel -- availableϵͳƵ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��9��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateAvailOrNegSystemChanStatusInScanChanList_SysAcq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanList = VOS_NULL_PTR;

    pstScanList = CNAS_XSD_GetScanChanListAddr();

    /***********************************************************************************************
     * i) �����OOC�����µ�MRU0����Ƶ�㣬ͬ������MRU0Ƶ����negativeϵͳ��availableϵͳ����scan list��
     * �������в����MRU0��ˢ��Ϊ�����ڣ�����
     * ii) ��scan list��ǰ��ʼ���ң�ˢ�¸�Ƶ��Ϊ����������
     **********************************************************************************************/
    if (VOS_TRUE == CNAS_XSD_IsMru0FreqInOocScene(pstFreq))
    {
        CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                              pstScanChanList->usTotalNum,
                                                              pstFreq,
                                                              pstScanChanList);
    }
    else
    {
        (VOS_VOID)CNAS_XSD_UpdateChanStatusInScanChanList(0,
                                                          pstFreq,
                                                          CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST,
                                                          pstScanList);
    }
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



