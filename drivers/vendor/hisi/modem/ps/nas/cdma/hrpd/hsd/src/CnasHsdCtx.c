/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdCtx.c
  �� �� ��   : ����
  ��    ��   : g00256031
  ��������   : 2014��12��15��
  ��������   : HRPD SD(system determination)״̬����������ȫ�ֱ�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��15��
    ��    ��   : g00256031
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasCcb.h"
#include "CnasHsdCtx.h"
#include "PsCommonDef.h"
#include "CnasMntn.h"
#include "CnasHsdFsmMainTbl.h"
#include "CnasHsdFsmSwitchOnTbl.h"
#include "CnasHsdFsmPowerOffTbl.h"
#include "CnasHsdFsmPowerSaveTbl.h"
#include "CnasHsdFsmSysAcqTbl.h"
#include "CnasPrlApi.h"
#include "CnasHsdMntn.h"
#include "CnasHsdProcNvim.h"
#include "CnasHsdFsmPowerSaveTbl.h"

#include "hsd_mscc_pif.h"
#include "CnasHsdFsmInterSysTbl.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* HSD CTX,���ڱ���HSD״̬��,������ */
CNAS_HSD_CTX_STRU                       g_stCnasHsdCtx;
VOS_UINT16                              g_ausCachePriorityList[] =
{
    ID_MSCC_HSD_POWER_OFF_REQ,
    ID_MSCC_HSD_POWER_SAVE_REQ,
    ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ
};


/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitCurrFsmCtx
 ��������  : ��ʼ����ǰ״̬��������
 �������  : ��
 �������  : pstCurrFsmCtx -- ��ǰ״̬����������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitCurrFsmCtx(
    CNAS_HSD_FSM_CTX_STRU              *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   CNAS_HSD_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   CNAS_HSD_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   CNAS_HSD_L1_STA_NULL;
    pstCurrFsmCtx->enParentFsmId            =   CNAS_HSD_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;

    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;
    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer,
               0x00,
               CNAS_HSD_MAX_MSG_BUFFER_LEN);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitFsmStackCtx
 ��������  : ��ʼ��״̬��ջ������
 �������  : ��
 �������  : pstFsmStack -- ״̬��ջ��Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitFsmStackCtx(
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for (i = 0 ; i < CNAS_HSD_MAX_FSM_STACK_DEPTH ; i++)
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = CNAS_HSD_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = CNAS_HSD_L1_STA_BUTT;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitCacheMsgQueue
 ��������  : ��ʼ���������Ϣ����
 �������  : ��
 �������  : pstCacheMsgQueue -- �������Ϣ������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��09��18��
   ��    ��   : d00212987
   �޸�����   : CNAS�ڴ�ü�

*****************************************************************************/
VOS_VOID CNAS_HSD_InitCacheMsgQueue(
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue,
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType
)
{
    /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, begin */
    VOS_UINT32                          i;

    pstCacheMsgQueue->ucCacheMsgNum = 0;

    for (i = 0; i < CNAS_HSD_MAX_CACHE_MSG_QUEUE_NUM; i++)
    {
        /* ����ʱֱ�Ӱѱ����ÿգ�����ʱ���ֹ�ڴ�й¶����Ҫ�ͷ��ڴ� */
        if (CNAS_HSD_INIT_CTX_STARTUP == enInitType)
        {
            pstCacheMsgQueue->pastCacheMsg[i] = VOS_NULL_PTR;
        }
        else
        {
            if (VOS_NULL_PTR != pstCacheMsgQueue->pastCacheMsg[i])
            {
                PS_MEM_FREE(UEPS_PID_HSD, pstCacheMsgQueue->pastCacheMsg[i]);
            }
        }
    }
    /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, end */

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitSysRecList
 ��������  : ��ʼ������HRPDϵͳ��
 �������  : enInitType----��ʼ������
 �������  : pstSysRecList -- ϵͳ���б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitSysRecList(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSD_HRPD_SYS_LIST_STRU        *pstSysRecList
)
{
    pstSysRecList->usHrpdSysNum     = 0;

    if (CNAS_HSD_INIT_CTX_STARTUP == enInitType)
    {
        pstSysRecList->pstHrpdSysItem   = VOS_NULL_PTR;

        return;
    }

    if (VOS_NULL_PTR != pstSysRecList->pstHrpdSysItem)
    {
        PS_MEM_FREE(UEPS_PID_HSD, pstSysRecList->pstHrpdSysItem);
        pstSysRecList->pstHrpdSysItem = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitScanChanList
 ��������  : ��ʼ��Ƶ��ɨ���б�
 �������  : enInitType----��ʼ������
 �������  : pstScanChanList -- Ƶ��ɨ���б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitScanChanList(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstScanChanList
)
{
    pstScanChanList->usTotalFreqNum     = 0;
    pstScanChanList->usAvailFreqNum     = 0;
    pstScanChanList->usCurrIndex        = 0;
    pstScanChanList->ucLowPrioLevel     = CNAS_PRL_PRIO_LEVEL_1;

    if (CNAS_HSD_INIT_CTX_STARTUP == enInitType)
    {
        pstScanChanList->pstScanFreqItem    = VOS_NULL_PTR;

        return;
    }

    if (VOS_NULL_PTR != pstScanChanList->pstScanFreqItem)
    {
        PS_MEM_FREE(UEPS_PID_HSD, pstScanChanList->pstScanFreqItem);
        pstScanChanList->pstScanFreqItem = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitSystemAcquireCtrl
 ��������  : ��ʼ��HRPDϵͳ��ȡ������Ϣ
 �������  : enInitType------��ʼ������
 �������  : pstSysAcqCtrl -- ϵͳ��ȡ������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_InitSystemAcquireCtrl(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_HSD_SYSTEM_ACQUIRE_CTRL_STRU  *pstSysAcqCtrl
)
{
    pstSysAcqCtrl->enModeType           = CNAS_HSD_SYS_MODE_BUTT;

    pstSysAcqCtrl->st1xSysInfo.enStatus   = CNAS_HSD_1X_SYSTEM_UNAVAILABLE;
    pstSysAcqCtrl->stHrpdSysInfo.enStatus = CNAS_HSD_HRPD_SYSTEM_UNAVAILABLE;

    PS_MEM_SET(&(pstSysAcqCtrl->st1xSysInfo.st1xSys), 0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    PS_MEM_SET(&(pstSysAcqCtrl->stMruList), 0, sizeof(CNAS_HSD_HRPD_MRU_LIST_STRU));

    PS_MEM_SET(&(pstSysAcqCtrl->stAvoidFreqList), 0, sizeof(CNAS_HSD_AVOID_FREQ_LIST_STRU));

    PS_MEM_SET(&(pstSysAcqCtrl->stHistorySysList), 0, sizeof(CNAS_HSD_HISTORY_SYS_LIST_STRU));

    CNAS_HSD_InitSysRecList(enInitType, &(pstSysAcqCtrl->stSysRecList));

    CNAS_HSD_InitScanChanList(enInitType, &(pstSysAcqCtrl->stScanFreqList));

    CNAS_HSD_InitOocScheduleInfo(&(pstSysAcqCtrl->stOocScheduleInfo));

    PS_MEM_SET(&(pstSysAcqCtrl->stHighPriority), 0, sizeof(CNAS_HSD_HIGHPRIORITY_STRU));
    PS_MEM_SET(&(pstSysAcqCtrl->stCasOhmHrpdSys), 0, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));
    PS_MEM_SET(&(pstSysAcqCtrl->stNetwkLostSysRec), 0, sizeof(CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU));

    /* ��Ƶ���� */
    CNAS_HSD_InitCFreqLockValue();

    PS_MEM_SET(&(pstSysAcqCtrl->stSyncFreq), 0, sizeof(CNAS_CAS_HRPD_FREQENCY_CHANNEL_STRU));

    CNAS_HSD_InitMatchedHrpdSysIndexList();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitSystemAcquireCtrl
 ��������  : ��ʼ��HRPDϵͳ��ȡ������Ϣ
 �������  : enInitType------��ʼ������
 �������  : pstSysAcqCtrl -- ϵͳ��ȡ������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_InitSystemAssistInfo(
    CNAS_HSD_SYSTEM_ASSIST_INFO_STRU   *pstSysAssistInfo
)
{
    pstSysAssistInfo->enNoRfScene        = CNAS_HSD_SYS_ACQ_SCENE_BUTT;
    pstSysAssistInfo->enATStatus         = CNAS_HSD_AT_STATUS_ENUM_NONE;
    pstSysAssistInfo->enSessionNegStatus = CNAS_HSD_NOT_IN_SESSION_NEG;
    pstSysAssistInfo->ucHrpdRfAvailFlg   = VOS_TRUE;
    pstSysAssistInfo->ucMru0RelateFlg    = VOS_FALSE;
    pstSysAssistInfo->ulUeSupportedBand  = 0xFFFF;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitFsmCtx_L1Main
 ��������  : ��ʼ��L1״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitFsmCtx_L1Main(VOS_VOID)
{
    CNAS_HSD_CTX_STRU                  *pstHsdCtx = VOS_NULL_PTR;

    pstHsdCtx = CNAS_HSD_GetHsdCtxAddr();

    /* ��鵱ǰ״̬���Ƿ���L1״̬�� */
    if (CNAS_HSD_FSM_L1_MAIN != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmCtx_L1Main:ENTERED");

        return;
    }

    pstHsdCtx->stCurFsm.unFsmCtx.stL1MainCtx.ulCurAvailableTimerCount = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitFsmCtx_SwitchOn
 ��������  : ��ʼ������״̬��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitFsmCtx_SwitchOn(VOS_VOID)
{
    CNAS_HSD_CTX_STRU                  *pstHsdCtx = VOS_NULL_PTR;

    pstHsdCtx = CNAS_HSD_GetHsdCtxAddr();

    /* ��鵱ǰ״̬���Ƿ�ʱ����״̬�� */
    if (CNAS_HSD_FSM_SWITCH_ON != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmCtx_SwitchOn:ENTERED");

        return;
    }

    pstHsdCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.ulHsdReadCardFileFlg = CNAS_HSD_READ_CARD_FILE_FLG_NULL;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitFsmCtx_SysAcq
 ��������  : ��ʼ��SYSTEM ACQUIRE״̬����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��15��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitFsmCtx_SysAcq(VOS_VOID)
{
    CNAS_HSD_CTX_STRU                  *pstHsdCtx = VOS_NULL_PTR;

    pstHsdCtx = CNAS_HSD_GetHsdCtxAddr();

    /* ��鵱ǰ״̬���Ƿ�ʱSYSTEM ACQUIRE״̬�� */
    if (CNAS_HSD_FSM_SYS_ACQ != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmCtx_SysAcq:ENTERED");

        return;
    }

    pstHsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg     = VOS_FALSE;
    pstHsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.enAbortReason  = CNAS_HSD_ABORT_REASON_BUTT;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitCtx
 ��������  : HSD ������ȫ�ֱ�����ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��09��18��
   ��    ��   : d00212987
   �޸�����   : CNAS�ڴ�ü�
*****************************************************************************/
VOS_VOID CNAS_HSD_InitCtx(
    CNAS_HSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType
)
{
    CNAS_HSD_CTX_STRU                  *pstHsdCtx = VOS_NULL_PTR;

    pstHsdCtx = CNAS_HSD_GetHsdCtxAddr();

    /* ��ǰ��������ԭ��ֵ����������չ */

    /* ��ǰ��״̬�������ʼ�� */
    CNAS_HSD_InitCurrFsmCtx(&(pstHsdCtx->stCurFsm));

    /* ״̬��ջ�����ʼ�� */
    CNAS_HSD_InitFsmStackCtx(&(pstHsdCtx->stFsmStack));

    /* CNAS HSD������Ϣ���г�ʼ�� */
    CNAS_HSD_InitCacheMsgQueue(&(pstHsdCtx->stCacheMsgQueue), enInitType);

    /* CNAS HSD�����ڲ���Ϣ���г�ʼ�� */
    CNAS_HSD_InitInternalBuffer(&(pstHsdCtx->stIntMsgQueue));

    /* CNAS HSDϵͳ��ȡ���Ƴ�ʼ�� */
    CNAS_HSD_InitSystemAcquireCtrl(enInitType, &(pstHsdCtx->stSysAcqCtrl));

    /* CNAS HSD������Ϣ */
    CNAS_HSD_InitSystemAssistInfo(&(pstHsdCtx->stSysAssistInfo));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_LoadSubFsm
 ��������  : ����L2״̬������Ϣ
 �������  : enFsmId - L2״̬��ID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_HSD_LoadSubFsm(
    CNAS_HSD_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm
)
{
    switch (enFsmId)
    {
        case CNAS_HSD_FSM_SWITCH_ON :
            pstCurFsm->ulState                  = CNAS_HSD_SWITCH_ON_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_HSD_GetSwitchOnFsmDescAddr();
            break;

        case CNAS_HSD_FSM_POWER_OFF :
            pstCurFsm->ulState                  = CNAS_HSD_POWER_OFF_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_HSD_GetPowerOffFsmDescAddr();
            break;

        case CNAS_HSD_FSM_SYS_ACQ:
            pstCurFsm->ulState                  = CNAS_HSD_SYS_ACQ_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_HSD_GetSysAcqFsmDescAddr();
            break;

        case CNAS_HSD_FSM_POWER_SAVE:
            pstCurFsm->ulState                  = CNAS_HSD_POWER_SAVE_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_HSD_GetPowerSaveFsmDescAddr();
            break;

        case CNAS_HSD_FSM_INTER_SYS:
            pstCurFsm->ulState                  = CNAS_HSD_INTER_SYS_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_HSD_GetInterSysFsmDescAddr();
            break;

        default:
            CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LoadSubFsm:Invalid Fsm Id");
            return;
    }

    /*ִ�г�ʼ��L2״̬���ĺ���*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_PushFsm
 ��������  : ��״̬������ѹջ
 �������  : pstFsmStack -- ״̬��ջ
             pstNewFsm   -- ��Ҫѹ���״̬��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_PushFsm(
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack,
    CNAS_HSD_FSM_CTX_STRU              *pstNewFsm
)
{
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;

    /* ���ָ���� */
    if ((VOS_NULL_PTR == pstFsmStack)
     || (VOS_NULL_PTR == pstNewFsm))
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD,
                       "CNAS_HSD_PushFsm: pstFsmStack or pstNewFsm is null pointer!");

        return;
    }

    /* ջ��ȼ�� */
    if (pstFsmStack->usStackDepth >= CNAS_HSD_MAX_FSM_STACK_DEPTH)
    {
        CNAS_ERROR_LOG1(UEPS_PID_HSD,
                       "CNAS_HSD_PushFsm: Fsm Stack Depth = %d Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    /* push��ǰ״̬����������ջ */
    pstCurFsm = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(CNAS_HSD_FSM_CTX_STRU));

    /* ջ������� */
    pstFsmStack->usStackDepth++;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_PopFsm
 ��������  : ��״̬�����г�ջ
 �������  : ��
             ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_PopFsm(VOS_VOID)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* ���ݲ���״̬��ջ������״̬����ȡ��ǰ״̬��������ַ  */
    pstFsmStack = CNAS_HSD_GetFsmStackAddr();
    pstCurFsm   = CNAS_HSD_GetCurFsmAddr();

    /* ���ջ�ռ��Ƿ�Ϊ�� */
    if (0 == pstFsmStack->usStackDepth)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_PopFsm: FSM Stack is empty");

        return;
    }

    /* ״̬��ջ��ȼ��� */
    pstFsmStack->usStackDepth--;

    /* ���õ�ǰ״̬�� */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]),
              sizeof(CNAS_HSD_FSM_CTX_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitFsmL2
 ��������  : HSD����һ��L2��״̬�����������̵�ͬʱ����״̬�Լ�������ʱ��
              �ú��������ѹջ����,�������Ҫ����Э��ջѹջ, ���뱣֤�˳�ǰ����
 �������  : enFsmId -- L2״̬��ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��07��13��
   ��    ��   : z00316370
   �޸�����   : ��TQE
*****************************************************************************/
VOS_VOID CNAS_HSD_InitFsmL2(
    CNAS_HSD_FSM_ID_ENUM_UINT32         enFsmId
)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;
    CNAS_HSD_FSM_ID_ENUM_UINT32         enParentFsmId;
    VOS_UINT32                          ulParentEventType;
    CNAS_HSD_FSM_ID_ENUM_UINT32         enCurrFsmId;

    enCurrFsmId = CNAS_HSD_GetCurrFsmId();
    if (CNAS_HSD_BUTT == enCurrFsmId)
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmL2: CNAS_HSD_GetCurrFsmId return Butt");
    }

    /* ��ӡѹջǰ��״̬����״̬ID */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_HSD, enCurrFsmId, CNAS_HSD_GetFsmTopState(), 0);

    /* ��¼ѹջǰ��״̬�����������Ϣ���� */
    enParentFsmId     = CNAS_HSD_GetCurrFsmId();
    ulParentEventType = CNAS_HSD_GetCurFsmAddr()->stEntryMsg.ulEventType;

    /* ����ǰ״̬��ѹջ���� */
    pstFsmStack = CNAS_HSD_GetFsmStackAddr();
    pstCurFsm   = CNAS_HSD_GetCurFsmAddr();
    CNAS_HSD_PushFsm(pstFsmStack, pstCurFsm);

    /* ���õ�ǰ״̬�� */
    pstCurFsm->enFsmId = enFsmId;

    /* ����L2״̬�� */
    CNAS_HSD_LoadSubFsm(enFsmId, pstCurFsm);

    /* ��¼�ϲ�״̬�����������Ϣ���� */
    pstCurFsm->enParentFsmId     = enParentFsmId;
    pstCurFsm->ulParentEventType = ulParentEventType;

    /* ��ӡѹջǰ��״̬����״̬ID */
    enCurrFsmId = CNAS_HSD_GetCurrFsmId();
    if (CNAS_HSD_BUTT == enCurrFsmId)
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmL2: CNAS_HSD_GetCurrFsmId return Butt");
    }

    CNAS_MNTN_LogFsmInfo(UEPS_PID_HSD, enCurrFsmId, CNAS_HSD_GetFsmTopState(), 0);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_QuitFsmL2
 ��������  : ����L2״̬��������������̣�״̬������״̬ջ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��07��13��
   ��    ��   : z00316370
   �޸�����   : ��TQE

*****************************************************************************/
VOS_VOID CNAS_HSD_QuitFsmL2(VOS_VOID)
{
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;
    CNAS_HSD_FSM_ID_ENUM_UINT32         enCurrFsmId;

    pstCurFsm = CNAS_HSD_GetCurFsmAddr();

    /* QUITʱ��յ�ǰL2״̬����CTX */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    enCurrFsmId = CNAS_HSD_GetCurrFsmId();
    if (CNAS_HSD_BUTT == enCurrFsmId)
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_QuitFsmL2: CNAS_HSD_GetCurrFsmId return Butt");
    }

    /*  ��ӡ��ǰ��״̬��ID�Լ�״̬ */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_HSD, enCurrFsmId, CNAS_HSD_GetFsmTopState(), 0);

    /* ״̬����ջ���� */
    CNAS_HSD_PopFsm();

    enCurrFsmId = CNAS_HSD_GetCurrFsmId();
    if (CNAS_HSD_BUTT == enCurrFsmId)
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_QuitFsmL2: CNAS_HSD_GetCurrFsmId return Butt");
    }

    /*  ��ӡ��ǰ��״̬��ID�Լ�״̬ */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_HSD, enCurrFsmId, CNAS_HSD_GetFsmTopState(), 0);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetHsdCtxAddr
 ��������  : ��ȡ��ǰHSD��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰHSD��CTX��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_CTX_STRU* CNAS_HSD_GetHsdCtxAddr(VOS_VOID)
{
    return &(g_stCnasHsdCtx);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetFsmStackAddr
 ��������  : ��ȡ��ǰ״̬��ջ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬��ջ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_FSM_STACK_STRU* CNAS_HSD_GetFsmStackAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stFsmStack);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetCurFsmAddr
 ��������  : ��ȡ��ǰ״̬����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_FSM_CTX_STRU* CNAS_HSD_GetCurFsmAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stCurFsm);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetFsmTopState
 ��������  : ��ȡ״̬�������״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬���Ķ���״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetFsmTopState(VOS_VOID)
{
    return (CNAS_HSD_GetCurFsmAddr()->ulState);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetCurFsmDesc
 ��������  : ��ȡ��ǰ״̬����ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_HSD_GetCurFsmDesc(VOS_VOID)
{
    return (CNAS_HSD_GetCurFsmAddr()->pstFsmDesc);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetFsmStackDepth
 ��������  : ��ȡ��ǰЭ��ջ��ջ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetFsmStackDepth(VOS_VOID)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_HSD_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetFsmStackPopFlg
 ��������  : ����״̬��ջpop��־
 �������  : ucStackPopFlg -- ջpop��־
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_HSD_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg = ucStackPopFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetFsmStackPopFlg
 ��������  : ��ȡ״̬��ջpop��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ջpop��־
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetFsmStackPopFlg(VOS_VOID)
{
    CNAS_HSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_HSD_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetCacheMsgAddr
 ��������  : ��ȡ��ǰ�Ļ�����Ϣ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS HSD������Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_CACHE_MSG_QUEUE_STRU* CNAS_HSD_GetCacheMsgAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stCacheMsgQueue);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SaveCacheMsgInMsgQueue
 ��������  : ��������Ϣ����Ļ����ڴ����
 �������  : ulEventType -- ��ϢID+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��09��18��
   ��    ��   : d00212987
   �޸�����   : CNAS�ڴ�ü�
*****************************************************************************/
VOS_VOID CNAS_HSD_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, begin */
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulMsgLen;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue  = CNAS_HSD_GetCacheMsgAddr();

    ulOffset     = pstMsgQueue->ucCacheMsgNum;

    if (CNAS_HSD_MAX_CACHE_MSG_QUEUE_NUM <= ulOffset)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SaveCacheMsgInMsgQueue:No Empty buffer");

        return;
    }

    ulMsgLen = (pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    /* �ڴ������ڲ� */
    pstMsgQueue->pastCacheMsg[ulOffset] = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_HSD, ulMsgLen);

    if (VOS_NULL_PTR == pstMsgQueue->pastCacheMsg[ulOffset])
    {
        return;
    }

    PS_MEM_CPY((pstMsgQueue->pastCacheMsg[ulOffset]),
               pstMsg,
               ulMsgLen);
    /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, end */

    pstMsgQueue->ucCacheMsgNum++;

    CNAS_INFO_LOG1(UEPS_PID_HSD, "CNAS_HSD_SaveCacheMsgInMsgQueue: Cache Num = %d", pstMsgQueue->ucCacheMsgNum);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SaveCacheMsg
 ��������  : ���浱ǰ��Ҫ����Ļ���
 �������  : ulEventType -- ��ϢID+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ����ɹ�
             VOS_FALSE -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_HSD_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��cache����Ϣ���ȼ�� */
    if ((CNAS_HSD_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) <= pstMsgHeader->ulLength)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SaveCacheMsg:Len too Long");
        return VOS_FALSE;
    }

    /* ����Ϣ�����ڻ����ڴ���� */
    CNAS_HSD_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    CNAS_HSD_SortCacheMsgInMsgQueue();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_ClearCacheMsg
 ��������  : ���ָ���Ļ�����Ϣ
 �������  : ulCurrIndex -- ���ָ��index����Ϣ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��09��18��
   ��    ��   : d00212987
   �޸�����   : CNAS�ڴ�ü�
*****************************************************************************/
VOS_VOID CNAS_HSD_ClearCacheMsg(
    VOS_UINT8                           ucIndex
)
{
    CNAS_HSD_CACHE_MSG_QUEUE_STRU       *pstMsgQueue = VOS_NULL_PTR;

    if (CNAS_HSD_MAX_CACHE_MSG_QUEUE_NUM <= ucIndex)
    {
        return;
    }

    pstMsgQueue = CNAS_HSD_GetCacheMsgAddr();

    if (0 < pstMsgQueue->ucCacheMsgNum)
    {
        pstMsgQueue->ucCacheMsgNum--;
        /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, begin */
        if (VOS_NULL_PTR != pstMsgQueue->pastCacheMsg[ucIndex])
        {
            PS_MEM_FREE(UEPS_PID_HSD, pstMsgQueue->pastCacheMsg[ucIndex]);

            pstMsgQueue->pastCacheMsg[ucIndex] = VOS_NULL_PTR;
        }

        if (ucIndex < (CNAS_HSD_MAX_CACHE_MSG_QUEUE_NUM - 1))
        {
            /* �������Ϣ�����������һ������Ҫ�Ѻ��������е���Ϣǰ�� */
            PS_MEM_MOVE(&(pstMsgQueue->pastCacheMsg[ucIndex]),
                        &(pstMsgQueue->pastCacheMsg[ucIndex + 1]),
                        (pstMsgQueue->ucCacheMsgNum - ucIndex) * sizeof(VOS_UINT32));
        }

       pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum] = VOS_NULL_PTR;
       /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, end */
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetNextCachedMsg
 ��������  : ��ȡ��ǰ��Ҫ����Ļ���
 �������  : ��
 �������  : pstEntryMSg -- ��ǰ��Ҫ�������Ϣ��ַ

 �� �� ֵ  : VOS_TRUE  -- ��ȡ�ɹ�
             VOS_FALSE -- ��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��09��18��
   ��    ��   : d00212987
   �޸�����   : CNAS�ڴ�ü�
*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetNextCachedMsg(
    CNAS_HSD_MSG_STRU                  *pstEntryMsg
)
{
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;
    /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, begin */
    MSG_HEADER_STRU                    *pstCacheMsgHdr = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstTimerMsg;
    VOS_UINT32                          ulMsgLen;

    pstMsgQueue = CNAS_HSD_GetCacheMsgAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        CNAS_INFO_LOG(UEPS_PID_HSD, "CNAS_HSD_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[0]);

    if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
    {
        pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

        pstEntryMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
    }
    else
    {
        pstEntryMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
    }

    /* ���������ȳ�ԭ��,Ĭ��ȡ��1���������� */
    ulMsgLen = (pstCacheMsgHdr->ulLength + VOS_MSG_HEAD_LENGTH);

    if (CNAS_HSD_MAX_MSG_BUFFER_LEN < ulMsgLen)
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetNextCachedMsg: beyond msg size ");

        ulMsgLen = CNAS_HSD_MAX_MSG_BUFFER_LEN;
    }

    PS_MEM_CPY(&pstEntryMsg->aucMsgBuffer[0],
               pstMsgQueue->pastCacheMsg[0],
               ulMsgLen);
    /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, end */

    /* ���indexΪ0��cache��Ϣ */
    CNAS_HSD_ClearCacheMsg(0);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetCacheMsgNum
 ��������  : ��ȡ��ǰ�������Ϣ����
 �������  : ��
 �������  :
 �� �� ֵ  : ��ǰ���ڵĻ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetCacheMsgNum(VOS_VOID)
{
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue;

    pstMsgQueue = CNAS_HSD_GetCacheMsgAddr();

    return pstMsgQueue->ucCacheMsgNum;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetCurrFsmState
 ��������  : ���õ�ǰ��ҪǨ�Ƶ�״̬
 �������  : ulCurrState:��ǰǨ�Ƶ�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��15��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  CNAS_HSD_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
)
{
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm;

    /* ��ȡ��ǰ��״̬��Ϣ */
    pstCurFsm                   = CNAS_HSD_GetCurFsmAddr();

    /* ���õ�ǰ״̬ */
    pstCurFsm->ulState          = ulCurrState;

    /*  ��ӡ��ǰ�ĵ�ǰ״̬��ID�Լ�״̬ */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_HSD, pstCurFsm->enFsmId, ulCurrState, 0);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetCurrFsmEntryMsgAddr
 ��������  : ��ȡ��ǰ״̬�������Ϣ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������Ϣ�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_MSG_STRU* CNAS_HSD_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(g_stCnasHsdCtx.stCurFsm.stEntryMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SaveCurEntryMsg
 ��������  : ���浱ǰ״̬���������Ϣ
 �������  : ulEventType            :�����Ϣ����
              pstMsg             :�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ  :
 1.��    ��   : 2014��12��15��
     ��    ��   : g00256031
     �޸�����   : �����ɺ���

 2.��    ��   : 2015��09��18��
   ��    ��   : d00212987
   �޸�����   : CNAS�ڴ�ü�
*****************************************************************************/
VOS_VOID CNAS_HSD_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_MSG_STRU                  *pstEntryMsg;
    VOS_UINT32                          ulLen;

    /* ��õ�ǰ����CNAS HSD�����Ϣ�Ļ�������ַ */
    pstEntryMsg                 = CNAS_HSD_GetCurrFsmEntryMsgAddr();

    ulLen                       = pstMsg->ulLength + VOS_MSG_HEAD_LENGTH;

    /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, begin */
    if (CNAS_HSD_MAX_MSG_BUFFER_LEN < ulLen)
    {
        CNAS_ERROR_LOG( UEPS_PID_HSD, "CNAS_HSD_SaveCurEntryMsg: msg size big than 1600!" );
        ulLen = CNAS_HSD_MAX_MSG_BUFFER_LEN;
    }

    /* ����ǰ����������Ϣ������Context��Ӧ�Ļ����� */
    PS_MEM_CPY(&pstEntryMsg->aucMsgBuffer[0], pstMsg, ulLen );
    /* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, end */

    /* ��дContext�еĲ��� */
    pstEntryMsg->ulEventType    = ulEventType;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetCurrFsmId
 ��������  : ��ȡ��ǰ״̬����ID
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���


*****************************************************************************/
CNAS_HSD_FSM_ID_ENUM_UINT32 CNAS_HSD_GetCurrFsmId(VOS_VOID)
{
    return (g_stCnasHsdCtx.stCurFsm.enFsmId);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetIntMsgQueueAddr
 ��������  : ��ȡ�ڲ���Ϣ�����׵�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_HSD_INT_MSG_QUEUE_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_HSD_INT_MSG_QUEUE_STRU* CNAS_HSD_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stIntMsgQueue);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitInternalBuffer
 ��������  : ��ʼ��HSD�ڲ���Ϣ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_InitInternalBuffer(
    CNAS_HSD_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
)
{
    VOS_UINT8                           i;

    for (i = 0; i < CNAS_HSD_MAX_INT_MSG_QUEUE_NUM; i++)
    {
        pstIntMsgQueue->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstIntMsgQueue->ucIntMsgNum = 0;

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_PutMsgInIntMsgQueue
 ��������  : ����Ϣ�ŵ��ڲ���Ϣ������
 �������  : pSndMsg:�����͵���Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��13��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  CNAS_HSD_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = CNAS_HSD_GetIntMsgNum();

    /* ����ڲ���Ϣ���У��Ƿ��л���������� */
    if (CNAS_HSD_MAX_INT_MSG_QUEUE_NUM <= ucIntMsgNum)
    {
        PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

        CNAS_ERROR_LOG( UEPS_PID_HSD, "CNAS_HSD_PutMsgInIntMsgQueue: msg queue is full!" );

        return;
    }

    /* ���浱ǰ��Ϣ */
    CNAS_HSD_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = pstMsg;

    CNAS_HSD_GetIntMsgQueueAddr()->ucIntMsgNum = (ucIntMsgNum + 1);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetNextIntMsg
 ��������  : ��ȡ�ڲ���Ϣ�����е���һ�����õ��ڲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ڲ���Ϣ���е�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 *CNAS_HSD_GetNextIntMsg(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = CNAS_HSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* ��ȡ��һ���������Ϣ��Ϣ */
        pstIntMsg = CNAS_HSD_GetIntMsgQueueAddr()->pastIntMsg[0];

        /* �ڲ���Ϣ��Ŀ����һ�� */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* ǰ���ڲ���Ϣ */
            PS_MEM_MOVE(&(CNAS_HSD_GetIntMsgQueueAddr()->pastIntMsg[0]),
                        &(CNAS_HSD_GetIntMsgQueueAddr()->pastIntMsg[1]),
                        ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* ����Ϣ������β������Ϣ��Ϊ��ָ�� */
        CNAS_HSD_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        CNAS_HSD_GetIntMsgQueueAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetIntMsgNum
 ��������  : ��ȡ��ǰHSD�ڲ���Ϣ����
 �������  : ��
 �������  :
 �� �� ֵ  : ��ǰ���ڵ��ڲ���Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = CNAS_HSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn
 ��������  : ���������л�ȡ��ȡ���ļ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ȡ���ļ��ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��12��15��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_READ_CARD_FILES_CNF_ENUM_UINT32 CNAS_HSD_GetWaitCardFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* �����ǰ״̬������switch on */
    if (CNAS_HSD_FSM_SWITCH_ON != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");
    }

    return g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulHsdReadCardFileFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn
 ��������  : �������������ö�ȡ���ļ��ظ����
 �������  : ���ÿ��ļ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��12��15��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn(
    CNAS_HSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (CNAS_HSD_FSM_SWITCH_ON != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_SetWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");
    }

    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulHsdReadCardFileFlg |= enReadCardFileCnfFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn
 ��������  : ���������������ȡ���ļ��ظ����
 �������  : ���ļ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��12��15��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn(
    CNAS_HSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (CNAS_HSD_FSM_SWITCH_ON != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_ClearWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");
    }

    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulHsdReadCardFileFlg &= ~enReadCardFileCnfFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetModeType
 ��������  : ��ǰģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32 CNAS_HSD_GetModeType(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.enModeType;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetSysModeType
 ��������  : ���õ�ǰ����ģʽ:��ϻ�ǻ��
 �������  : enModeType:����ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : h00300778
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetSysModeType(CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32 enModeType)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.enModeType = enModeType;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_Get1xSystemInfo
 ��������  : ���õ�ǰƵ��ɨ���б��е�ǰɨ�赽���б�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_HSD_1X_SYSTEM_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��8��6��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_1X_SYSTEM_INFO_STRU* CNAS_HSD_Get1xSystemInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.st1xSysInfo);
}
/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetScanListMatched1xSystemInfo
 ��������  : ��ȡ����ʱ��1Xϵͳ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_HSD_1X_SYSTEM_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��26��
   ��    ��   : c00299064
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_1X_SYSTEM_INFO_STRU* CNAS_HSD_GetScanListMatched1xSystemInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdMatched1xSysInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetMruList
 ��������  : �õ�MRU
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_HSD_HRPD_MRU_LIST_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��10��
   ��    ��   : C00299064
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_HRPD_MRU_LIST_STRU* CNAS_HSD_GetMruList(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stMruList);
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_UpdateMru0
 ��������  : ����MRU0
 �������  : pstCurSysId - EVDOϵͳ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��10��
   ��    ��   : C00299064
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_UpdateMru0(CNAS_PRL_HRPD_SYSTEM_STRU *pstCurSysId)
{
    VOS_UINT8                           i;
    CNAS_HSD_HRPD_MRU_LIST_STRU        *pstMruList;
    VOS_UINT32                          ulIsSysInMru = VOS_FALSE;
    CNAS_PRL_HRPD_SYSTEM_STRU           stMruItem;

    pstMruList       = CNAS_HSD_GetMruList();

    PS_MEM_SET(&stMruItem, 0, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));
    stMruItem.stFreq = pstCurSysId->stFreq;

    /* MRU��ֻ��SubnetID�еĸ�6�ֽ� */
    PS_MEM_CPY(stMruItem.aucSubnet, pstCurSysId->aucSubnet + (CNAS_PRL_BYTES_IN_SUBNET - CNAS_HSD_CHECK_BYTES_SUBNET_ID),
               CNAS_HSD_CHECK_BYTES_SUBNET_ID);

    /* ���������ظ� */
    for (i = 0; i < pstMruList->ucCurrMruNum; i++)
    {
        /* ����ظ�������ȥ�ز��� */
        if (VOS_TRUE == CNAS_PRL_CmpFreqValue(&(pstMruList->astHrpdSys[i].stFreq), &(stMruItem.stFreq)))
        {
            if (VOS_TRUE == CNAS_PRL_CmpSubnetValue(pstMruList->astHrpdSys[i].aucSubnet,
                                                    stMruItem.aucSubnet, CNAS_HSD_CHECK_BYTES_SUBNET_ID))
            {
                ulIsSysInMru = VOS_TRUE;

                if (0 != i)
                {
                    PS_MEM_MOVE(&pstMruList->astHrpdSys[1], pstMruList->astHrpdSys, (i)*(sizeof(CNAS_PRL_HRPD_SYSTEM_STRU)));
                }

                break;
            }
        }
    }

    /* �������MRU�У�ֱ����MRU0���������� */
    if (VOS_FALSE == ulIsSysInMru)
    {
        PS_MEM_MOVE(&pstMruList->astHrpdSys[1], pstMruList->astHrpdSys,
                    sizeof(CNAS_PRL_HRPD_SYSTEM_STRU)*(CNAS_HSD_MAX_MRU_SYS_NUM - 1));

        if (pstMruList->ucCurrMruNum < CNAS_HSD_MAX_MRU_SYS_NUM)
        {
            pstMruList->ucCurrMruNum++;
        }
    }

    /* ��ֵMRU[0] */
    PS_MEM_CPY(pstMruList->astHrpdSys, &stMruItem, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    CNAS_HSD_WriteMruNvim(pstMruList);

    CNAS_HSD_LogMruList(pstMruList, ID_CNAS_HSD_MNTN_MRU_LOG_TYPE_STAY_SUCC);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetMruListNum
 ��������  : ��ȡMRU table��ϵͳ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����MRU table��ϵͳ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��16��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetMruListNum(VOS_VOID)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enHrpdMode;
    VOS_UINT8                           ucMruNum = 0;

    enHrpdMode = CNAS_HSD_GetModeType();

    /* ��ȡMRU�������� */
    /* �������Ϊ0����0  ���HYBRID �Ҳ�Ϊ0 ����1 �����nonhybrid ֱ��ʹ��ԭ����ֵ */
    if ((0 == CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stMruList.ucCurrMruNum)
     || (CNAS_HSD_SYS_MODE_NONHYBRID == enHrpdMode))
    {
        ucMruNum    = CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stMruList.ucCurrMruNum;
    }
    else
    {
        ucMruNum    = 1;
    }

    return ucMruNum;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetMru0SysId
 ��������  : ��ȡMRU0��Ӧ��ϵͳID
 �������  : ��
 �������  : pstMru0SysId------MRU0��Ӧ��ϵͳID
 �� �� ֵ  : ��ȡ�ɹ�:VOS_TRUE
             ��ȡʧ��:VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��16��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetMru0SysId(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstMru0SysId
)
{
    CNAS_HSD_HRPD_MRU_LIST_STRU        *pstMruList = VOS_NULL_PTR;

    pstMruList = CNAS_HSD_GetMruList();

    if (0 < CNAS_HSD_GetMruListNum())
    {
        pstMru0SysId->stFreq    = pstMruList->astHrpdSys[0].stFreq;
        PS_MEM_CPY(pstMru0SysId->aucSubnet, pstMruList->astHrpdSys[0].aucSubnet, CNAS_PRL_BYTES_IN_SUBNET);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetSysRecListAddr
 ��������  : ��ȡϵͳƵ���б�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰϵͳƵ���б�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��16��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/

CNAS_HSD_HRPD_SYS_LIST_STRU* CNAS_HSD_GetSysRecListAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stSysRecList);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetSysRecItemNum
 ��������  : ��ȡϵͳƵ���б��ܸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ȡϵͳƵ���б��ܸ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��16��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetSysRecItemNum(VOS_VOID)
{
    return (CNAS_HSD_GetSysRecListAddr()->usHrpdSysNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetSysRecListIndex
 ��������  : ���õ�ǰϵͳ�б����
 �������  : usHrpdSysNum-----ϵͳ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��6��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetSysRecListIndex(
    VOS_UINT16                          usHrpdSysNum
)
{
    CNAS_HSD_GetSysRecListAddr()->usHrpdSysNum = usHrpdSysNum;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetScanFreqListAddr
 ��������  : ��ȡƵ��ɨ���б�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰƵ��ɨ���б�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��12��
   ��    ��   : c00299064
   �޸�����   : �����ɺ���

*****************************************************************************/

CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU* CNAS_HSD_GetScanFreqListAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stScanFreqList);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetScanFreqNum
 ��������  : ��ȡ��ǰƵ��ɨ���б���Ƶ���ܸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰƵ��ɨ���б���Ƶ���ܸ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��16��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetScanFreqNum(VOS_VOID)
{
    return (CNAS_HSD_GetScanFreqListAddr()->usAvailFreqNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetCurScanFreqIndex
 ��������  : ��ȡ��ǰƵ��ɨ���б��е�ǰɨ�赽���б�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰƵ��ɨ���б��е�ǰɨ�赽���б�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��16��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetCurScanFreqIndex(VOS_VOID)
{
    return (CNAS_HSD_GetScanFreqListAddr()->usCurrIndex);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetScanListAvailFreqNum
 ��������  : ��Scan List�л�ȡʣ�����Ƶ����
 �������  : NA

 �������  : NA

 �� �� ֵ  : VOS_UINT16 /��Scan List�л�ȡʣ�����Ƶ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��8��
    ��    ��   : d00212987
    �޸�����   : EVDO HSD Phase0

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetScanListAvailFreqNum(VOS_VOID)
{
    VOS_UINT16                          usAvailFreqNum = 0;
    VOS_UINT16                          usCurrIndex    = 0;

    /* �ܵĿ���Ƶ����� */
    usAvailFreqNum = CNAS_HSD_GetScanFreqNum();

    /* ��ǰ���� */
    usCurrIndex    = CNAS_HSD_GetCurScanFreqIndex();

    return (usAvailFreqNum - usCurrIndex);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetCurScanFreqIndex
 ��������  : ���õ�ǰƵ��ɨ���б��е�ǰɨ�赽���б�����
 �������  : usCurScanIndex------��ǰƵ��ɨ���б��е�ǰɨ�赽���б�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��16��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetCurScanFreqIndex(
    VOS_UINT16                          usCurScanIndex
)
{
    CNAS_HSD_GetScanFreqListAddr()->usCurrIndex = usCurScanIndex;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetScanFreqByIndex
 ��������  : ͨ��������ò���Ƶ��
 �������  : usFreqIndex------�б�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��16��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_HSD_GetScanFreqByIndex(
    VOS_UINT16                          usFreqIndex
)
{
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU  *pstFreqList;

    if (usFreqIndex >= CNAS_HSD_GetScanFreqNum())
    {
        return VOS_NULL_PTR;
    }

    pstFreqList = CNAS_HSD_GetScanFreqListAddr();

    return &(pstFreqList->pstScanFreqItem[usFreqIndex].stFreq);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetRedirectionFreqAddr
 ��������  : ��ȡ�ض���Ƶ���б�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ�ض����б�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��6��
   ��    ��   : d00212987
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_REDIRECTION_STRU* CNAS_HSD_GetRedirectionFreqAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stRedirection);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetRedirectionFreqNum
 ��������  : ��ȡ�ض���Ƶ���б�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ�ض����б�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��6��
   ��    ��   : d00212987
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetRedirectionFreqNum(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stRedirection.ucChanNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetOocScheduleConfigInfo
 ��������  : ��ȡOOC�µ���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����OOC����������Ϣ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��08��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_OOC_CONFIG_INFO_STRU *CNAS_HSD_GetOocScheduleConfigInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo.stConfigInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetOocScheduleInfo
 ��������  : ��ȡOOC�µ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����OOC������Ϣ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��13��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_OOC_SCHEDULE_INFO_STRU *CNAS_HSD_GetOocScheduleInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitOocScheduleInfo
 ��������  : ��ʼ��OOC�µ�����Ϣ
 �������  : pstOocScheduleInfo -- ��ʼ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��13��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitOocScheduleInfo(
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
)
{
    PS_MEM_SET(pstOocScheduleInfo, 0, sizeof(CNAS_HSD_OOC_SCHEDULE_INFO_STRU));

    pstOocScheduleInfo->stConfigInfo.ucPhaseNum                      = 1;
    pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimerLen   = 5;
    pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimes      = 5;

    return;

}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitOocCtxInfo
 ��������  : ��ʼ��OOC��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��13��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitOocCtxInfo(VOS_VOID)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enSysMode;

    pstOocScheduleInfo = CNAS_HSD_GetOocScheduleInfo();

    PS_MEM_SET(&pstOocScheduleInfo->stOocCtxInfo, 0, sizeof(CNAS_HSD_OOC_CTX_INFO_STRU));

    enSysMode          = CNAS_HSD_GetModeType();

    if (CNAS_HSD_SYS_MODE_HYBRID == enSysMode)
    {
        /* ���ģʽ�µ�һ��OOC����ʱ������Ϊ0 */
        pstOocScheduleInfo->stOocCtxInfo.ucCurrentPhase = 1;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetOocWaitSearchFlag
 ��������  : ��ȡOOC�ȴ�������־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��14��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetOocWaitSearchFlag(VOS_VOID)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_HSD_GetOocScheduleInfo();

    return (pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetOocWaitSearchFlag
 ��������  : ����OOC�ȴ�������־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��14��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetOocWaitSearchFlag(VOS_UINT8 ucWaitSearchFlag)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_HSD_GetOocScheduleInfo();

    pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag = ucWaitSearchFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAvoidFreqListAddr
 ��������  : ��ȡavoidƵ���б��ַ
 �������  : ��

 �������  : ��
 �� �� ֵ  : CNAS_HSD_AVOID_FREQ_LIST_STRU* -- avoidƵ���б��׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��06��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_AVOID_FREQ_LIST_STRU* CNAS_HSD_GetAvoidFreqListAddr(VOS_VOID)
{
    return &(g_stCnasHsdCtx.stSysAcqCtrl.stAvoidFreqList);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAvoidFreqListUsedNum
 ��������  : ��ȡavoidƵ���б���Ŀ
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_UINT8 -- avoid�б���Ŀ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��06��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetAvoidFreqListUsedNum(VOS_VOID)
{
    return (CNAS_HSD_GetAvoidFreqListAddr()->ucAvoidItemUsedNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetCasSessionNegStatus
 ��������  : ��ȡSession negotiation״̬
 �������  : ��

 �������  : ��
 �� �� ֵ  : CNAS_HSD_CAS_SESSION_NEG_STATUS_ENUM_UINT32 -- ״̬ö��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_SESSION_NEG_STATUS_ENUM_UINT32 CNAS_HSD_GetSessionNegStatus(VOS_VOID)
{
     return (CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enSessionNegStatus);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SaveCasSessionNegStatus
 ��������  : ����Session negotionation״̬
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SaveSessionNegStatus(
    CNAS_HSD_SESSION_NEG_STATUS_ENUM_UINT32                 enSessionNegStatus
)
{
     CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enSessionNegStatus = enSessionNegStatus;

     return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetATStatus
 ��������  : ��ȡCas״̬
 �������  : ��

 �������  : ��
 �� �� ֵ  : CNAS_HSD_CAS_STATUS_ENUM_UINT32 -- ״̬ö��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_AT_STATUS_ENUM_UINT32 CNAS_HSD_GetATStatus(VOS_VOID)
{
     return (CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enATStatus);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SaveATStatus
 ��������  : ����Cas״̬
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SaveATStatus(
    CNAS_HSD_AT_STATUS_ENUM_UINT32     enATStatus
)
{
     CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enATStatus = enATStatus;

     return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetHistorySysList
 ��������  : ��ȡ��ʷפ����Hrpd��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_HSD_HISTORY_SYS_LIST_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��12��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_HISTORY_SYS_LIST_STRU* CNAS_HSD_GetHistorySysList(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHistorySysList);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_UpdateHistorySysList
 ��������  : ������ʷפ����Hrpd��Ϣ
 �������  : pstCurrSystem - ��ǰפ����ϵͳ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��12��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_UpdateHistorySysList(CNAS_PRL_HRPD_SYSTEM_STRU *pstCurrSystem)
{
    CNAS_HSD_HISTORY_SYS_LIST_STRU                         *pstHistorySysList;

    pstHistorySysList = CNAS_HSD_GetHistorySysList();

    if (pstHistorySysList->ulTotalNum < CNAS_HSD_HRPD_ACQED_SUCC_SYS_MAX_NUM)
    {
        PS_MEM_MOVE(&(pstHistorySysList->stCampedHrpdSysInfo[1]),
                    &(pstHistorySysList->stCampedHrpdSysInfo[0]),
                    sizeof(CNAS_PRL_HRPD_SYSTEM_STRU) * pstHistorySysList->ulTotalNum);

        pstHistorySysList->ulTotalNum++;
    }
    else
    {
        PS_MEM_MOVE(&(pstHistorySysList->stCampedHrpdSysInfo[1]),
                    &(pstHistorySysList->stCampedHrpdSysInfo[0]),
                    sizeof(CNAS_PRL_HRPD_SYSTEM_STRU) * (CNAS_HSD_HRPD_ACQED_SUCC_SYS_MAX_NUM - 1));
    }

    PS_MEM_CPY(&(pstHistorySysList->stCampedHrpdSysInfo[0]),
               pstCurrSystem,
               sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetHrpdSysStatus
 ��������  : ��ȡ��ǰHrpd������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32 Hrpd����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��12��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32 CNAS_HSD_GetHrpdSysStatus(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdSysInfo.enStatus;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetHrpdSysStatus
 ��������  : ���õ�ǰHrpd������Ϣ
 �������  : enStatus:Hrpd����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��12��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetHrpdSysStatus(CNAS_HSD_HRPD_SYSTEM_STATUS_ENUM_UINT32 enStatus)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdSysInfo.enStatus = enStatus;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetCampedHrpdSystemInfo
 ��������  : ��ȡ��ǰפ����Hrpd��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_PRL_HRPD_SYSTEM_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��12��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_HRPD_SYSTEM_STRU* CNAS_HSD_GetCampedHrpdSystemInfo(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHrpdSysInfo.stCampedHrpdSysInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_UpdateHrpdSysInfo
 ��������  : ���µ�ǰפ����Hrpd��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��12��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_UpdateHrpdSysInfo(CNAS_PRL_HRPD_SYSTEM_STRU *pstSystem)
{
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem;

    /* ���õ�ǰHrpdϵͳ���� */
    CNAS_HSD_SetHrpdSysStatus(CNAS_HSD_HRPD_SYSTEM_AVAILABLE);

    pstHrpdSystem = CNAS_HSD_GetCampedHrpdSystemInfo();

    PS_MEM_CPY(pstHrpdSystem, pstSystem, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ClearHrpdSysInfo
 ��������  : �����ǰפ����Hrpd��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��12��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ClearHrpdSysInfo(VOS_VOID)
{
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSystem;

    /* ���õ�ǰHrpdϵͳ��פ�� */
    CNAS_HSD_SetHrpdSysStatus(CNAS_HSD_HRPD_SYSTEM_UNAVAILABLE);

    pstHrpdSystem = CNAS_HSD_GetCampedHrpdSystemInfo();

    PS_MEM_SET(pstHrpdSystem, 0, sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetNoRfScene
 ��������  : ����NoRf����
 �������  : CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 enNoRfScene
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��12��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 enNoRfScene)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRfScene = enNoRfScene;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetNoRfScene
 ��������  : ���NoRf����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��12��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetNoRfScene(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRfScene;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetNoRf1XUeStatus
 ��������  : ���NoRf����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_CCB_1X_CAS_STATE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��03��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 CNAS_HSD_GetNoRf1XUeStatus(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRf1XUeStatus;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetNoRf1XUeStatus
 ��������  : ���NoRf����
 �������  : CNAS_CCB_1X_CAS_STATE_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��03��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetNoRf1XUeStatus(CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 enStatus)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.enNoRf1XUeStatus = enStatus;
    return ;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetAbortFlg_SysAcq
 ��������  : ���õ�ǰ״̬����ϱ�Ǻʹ�ϳ���
 �������  : VOS_UINT8                           ucFlg
 �������  : ��
 �� �� ֵ  : ����ǰ��ϳ������ȼ����ߣ���֮ǰ����Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8   CNAS_HSD_SetAbortFlg_SysAcq(
    VOS_UINT8                           ucFlg,
    CNAS_HSD_ABORT_REASON_ENUM_UINT8    enAbortReason
)
{
    /* �����ǰ״̬������CNAS_HSD_FSM_SYS_ACQ */
    if (CNAS_HSD_FSM_SYS_ACQ != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_SetAbortFlg_SysAcq: Current state is incorrect.");

        return VOS_FALSE;
    }

    if (enAbortReason >= CNAS_HSD_GetAbortReason_SysAcq())
    {
        return VOS_FALSE;
    }

    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg     = ucFlg;
    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.enAbortReason  = enAbortReason;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAbortFlg_SysAcq
 ��������  : ��ȡ��ǰ״̬����ϱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��21��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetAbortFlg_SysAcq(VOS_VOID)
{
    /* �����ǰ״̬������CNAS_HSD_FSM_SYS_ACQ */
    if (CNAS_HSD_FSM_SYS_ACQ != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetAbortFlg_SysAcq: Current state is incorrect.");
    }

    return g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAbortReason_SysAcq
 ��������  : ��ȡ��ǰ״̬����ϳ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_HSD_ABORT_REASON_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_ABORT_REASON_ENUM_UINT8 CNAS_HSD_GetAbortReason_SysAcq(VOS_VOID)
{
    /* �����ǰ״̬������CNAS_HSD_FSM_SYS_ACQ */
    if (CNAS_HSD_FSM_SYS_ACQ != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetAbortFlg_SysAcq: Current state is incorrect.");
    }

    return g_stCnasHsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.enAbortReason;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetHighPriorityFreqAddr
 ��������  : ��ȡ�����ȼ�Ƶ���б�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ�ض����б�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��07��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_HIGHPRIORITY_STRU* CNAS_HSD_GetHighPriorityFreqAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHighPriority);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetHighPriorityFreqNum
 ��������  : ��ȡ�����ȼ�Ƶ���б�ĸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ�����ȼ�Ƶ���б�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��07��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetHighPriorityFreqNum(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stHighPriority.ucFreqNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitHighPriorityFreq
 ��������  : ��ʼ�������ȼ�Ƶ���б�
 �������  : ��ǰ�����ȼ�Ƶ���б�ĵ�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��07��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitHighPriorityFreq(CNAS_HSD_HIGHPRIORITY_STRU* pstHighFreq)
{
    PS_MEM_SET(pstHighFreq, 0, sizeof(CNAS_HSD_HIGHPRIORITY_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetCasOhmHrpdSysAddr
 ��������  : ��ȡ�տ��ϱ�Ƶ��ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ�տ��ϱ�Ƶ��ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��27��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_HRPD_SYSTEM_STRU* CNAS_HSD_GetCasOhmHrpdSysAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stCasOhmHrpdSys);
}

/* add by d00212987 for CNAS�ڴ�ü�, 2015-09-18, begin */
/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetEventType
 ��������  : ͨ��������Ϣ��ȡEventType
 �������  : pstMsgQueue        -- ������Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��10��
   ��    ��   : d00212987
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetEventType(
    VOS_UINT8                          *pucCacheMsg
)
{
    VOS_UINT32                          ulEventType;
    MSG_HEADER_STRU                    *pstCacheMsgHdr = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstTimerMsg;

    pstCacheMsgHdr = (MSG_HEADER_STRU *)pucCacheMsg;

    if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
    {
        pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

        ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
    }
    else
    {
        ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
    }

    return ulEventType;
}
/* add by d00212987 for CNAS�ڴ�ü�, 2015-09-18, end */

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SortCacheMsgInMsgQueue
 ��������  : �Ի�����Ϣ����Ļ����ڴ�ؽ����������ȼ��ߵ���Ϣ���ȴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��29��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��09��18��
   ��    ��   : d00212987
   �޸�����   : CNAS�ڴ�ü�
*****************************************************************************/
VOS_VOID CNAS_HSD_SortCacheMsgInMsgQueue(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT8                           ucPri1;
    VOS_UINT8                           ucPri2;
/* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, begin */	
    VOS_UINT8                          *pstCacheMsg;
    CNAS_HSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue   = VOS_NULL_PTR;

    pstMsgQueue  = CNAS_HSD_GetCacheMsgAddr();

    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        ucPri1 =  CNAS_HSD_GetCacheMsgPriority(CNAS_HSD_GetEventType(pstMsgQueue->pastCacheMsg[i]));

        for (j = i + 1; j < pstMsgQueue->ucCacheMsgNum; j++)
        {
            ucPri2 =  CNAS_HSD_GetCacheMsgPriority(CNAS_HSD_GetEventType(pstMsgQueue->pastCacheMsg[j]));

            /* ����λ�� */
            if (ucPri1 > ucPri2)
            {
                pstCacheMsg = pstMsgQueue->pastCacheMsg[i];

                pstMsgQueue->pastCacheMsg[i] = pstMsgQueue->pastCacheMsg[j];

                pstMsgQueue->pastCacheMsg[j] = pstCacheMsg;
#if 0
                PS_MEM_CPY(pstCacheMsg->aucMsgBuffer,
                           &(pstMsgQueue->pastCacheMsg[i]),
                           sizeof(CNAS_HSD_MSG_STRU));

                PS_MEM_CPY(&pstMsgQueue->pastCacheMsg[i],
                           &pstMsgQueue->pastCacheMsg[j],
                           sizeof(CNAS_HSD_MSG_STRU));

                PS_MEM_CPY(&pstMsgQueue->pastCacheMsg[j],
                           pstCacheMsg->aucMsgBuffer,
                           sizeof(CNAS_HSD_MSG_STRU));
#endif
            }
        }
    }
/* Modified by d00212987 for CNAS�ڴ�ü�, 2015-09-18, end */

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetCacheMsgPriority
 ��������  : ��ȡ��ǰ�¼���Ϣ�����ȼ�
 �������  : ulEventType        -- �¼�����
 �������  : ��
 �� �� ֵ  : ��������Ϣ��Ӧ�����ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��29��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetCacheMsgPriority(
    VOS_UINT32                          ulEventType
)
{
    VOS_UINT8                           i;
    VOS_UINT16                          usMsgName;

    usMsgName = (VOS_UINT16)(ulEventType & 0xFFFF);

    for (i = 0; i < sizeof(g_ausCachePriorityList)/sizeof(VOS_UINT16); i++)
    {
        if (usMsgName == g_ausCachePriorityList[i])
        {
            break;
        }
    }

    return i;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitFsmCtx_InterSys
 ��������  : ��ʼ��INTER SYS״̬����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitFsmCtx_InterSys(VOS_VOID)
{
    CNAS_HSD_CTX_STRU                  *pstHsdCtx = VOS_NULL_PTR;

    pstHsdCtx = CNAS_HSD_GetHsdCtxAddr();

    /* ��鵱ǰ״̬���Ƿ�ʱCNAS_HSD_FSM_INTER_SYS״̬�� */
    if (CNAS_HSD_FSM_INTER_SYS != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_InitFsmCtx_InterSys:ENTERED");

        return;
    }

    pstHsdCtx->stCurFsm.unFsmCtx.stInterSysCtx.ucAbortFlg     = VOS_FALSE;
    pstHsdCtx->stCurFsm.unFsmCtx.stInterSysCtx.enAbortReason  = CNAS_HSD_ABORT_REASON_BUTT;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetAbortFlg_InterSys
 ��������  : ���õ�ǰ״̬����ϱ�Ǻʹ�ϳ���
 �������  : VOS_UINT8                           ucFlg
 �������  : ��
 �� �� ֵ  : ����ǰ��ϳ������ȼ����ߣ���֮ǰ����Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8   CNAS_HSD_SetAbortFlg_InterSys(
    VOS_UINT8                           ucFlg,
    CNAS_HSD_ABORT_REASON_ENUM_UINT8    enAbortReason
)
{
    /* �����ǰ״̬������CNAS_HSD_FSM_INTER_SYS */
    if (CNAS_HSD_FSM_INTER_SYS != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_SetAbortFlg_InterSys: Current state is incorrect.");

        return VOS_FALSE;
    }

    if (enAbortReason >= CNAS_HSD_GetAbortReason_InterSys())
    {
        return VOS_FALSE;
    }

    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stInterSysCtx.ucAbortFlg     = ucFlg;
    g_stCnasHsdCtx.stCurFsm.unFsmCtx.stInterSysCtx.enAbortReason  = enAbortReason;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAbortFlg_InterSys
 ��������  : ��ȡ��ǰ״̬����ϱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetAbortFlg_InterSys(VOS_VOID)
{
    /* �����ǰ״̬������CNAS_HSD_FSM_INTER_SYS */
    if (CNAS_HSD_FSM_INTER_SYS != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetAbortFlg_InterSys: Current state is incorrect.");
    }

    return g_stCnasHsdCtx.stCurFsm.unFsmCtx.stInterSysCtx.ucAbortFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAbortReason_InterSys
 ��������  : ��ȡ��ǰ״̬����ϳ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_HSD_ABORT_REASON_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_ABORT_REASON_ENUM_UINT8 CNAS_HSD_GetAbortReason_InterSys(VOS_VOID)
{
    /* �����ǰ״̬������CNAS_HSD_FSM_INTER_SYS */
    if (CNAS_HSD_FSM_INTER_SYS != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetAbortReason_InterSys: Current state is incorrect.");
    }

    return g_stCnasHsdCtx.stCurFsm.unFsmCtx.stInterSysCtx.enAbortReason;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetNetwkLostSysRec
 ��������  : ��ȡ������¼��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU* CNAS_HSD_GetNetwkLostSysRec(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stNetwkLostSysRec);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetFreqLockAddr
 ��������  : ��ȡstFreqLockPara��ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU* CNAS_HSD_GetFreqLockAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stFreqLockPara);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetFreqLockMode
 ��������  : ��ȡ��ǰ��Ƶģʽ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ucFreqLockMode
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetFreqLockMode(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stFreqLockPara.ucFreqLockMode);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetHrpdRfAvailFlg
 ��������  : ��ȡ��ǰXģ��Ƶ��Դ���ñ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
             VOS_TRUE   : ����
             VOS_FALSE  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetHrpdRfAvailFlg(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucHrpdRfAvailFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetHrpdRfAvailFlg
 ��������  : ���õ�ǰXģ��Ƶ��Դ���ñ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
             VOS_TRUE   : ����
             VOS_FALSE  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetHrpdRfAvailFlg(VOS_UINT8 ucHrpdRfAvailFlg)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucHrpdRfAvailFlg = ucHrpdRfAvailFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetMru0RelateFlg
 ��������  : ��ȡMru0��ر�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
             VOS_TRUE   : ����
             VOS_FALSE  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetMru0RelateFlg(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucMru0RelateFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetMru0RelateFlg
 ��������  : ����Mru0��ر�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
             VOS_TRUE   : ����
             VOS_FALSE  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetMru0RelateFlg(VOS_UINT8 ucMru0RelateFlg)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucMru0RelateFlg = ucMru0RelateFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitCFreqLockValue
 ��������  : ��ʼ��stFreqLockPara
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitCFreqLockValue(VOS_VOID)
{
    CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU  *pstCnasHsdCFreqLockValue;

    pstCnasHsdCFreqLockValue = CNAS_HSD_GetFreqLockAddr();

    PS_MEM_SET(pstCnasHsdCFreqLockValue, 0x00, sizeof(CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetUeSupportedBandClass
 ��������  : ��ȡ֧�ֵ�band
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetUeSupportedBandClass(VOS_VOID)
{
    return (CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ulUeSupportedBand);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetTestConfig
 ��������  : ��ȡstTestConfig�׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����stTestConfig�׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��11��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_HSD_TEST_CONFIG_STRU* CNAS_HSD_GetTestConfig(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stTestConfig);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetSysCfgFlag
 ��������  : ����SysCfg��Ϣ��û�����
 �������  : VOS_TRUE : �Ѿ����͸�CAS��CAS��û�лظ�
             VOS_FALSE: SysCfg�Ѿ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetSysCfgFlag(VOS_UINT8 ucIsSysCfg)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucSysCfgFlg = ucIsSysCfg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetSysCfgFlag
 ��������  : ���SysCfg���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_TRUE : �Ѿ����͸�CAS��CAS��û�лظ�
             VOS_FALSE: SysCfg�Ѿ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetSysCfgFlag(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucSysCfgFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetMatchedHrpdSysIndexListAddr
 ��������  : ��ȡƥ��ϵͳ������ֵ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ƥ��ϵͳ������ֵ�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��30��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/

CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU* CNAS_HSD_GetMatchedHrpdSysIndexListAddr(VOS_VOID)
{
    return &(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stMatchedHrpdSysIndexList);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitMatchedHrpdSysIndexAddr
 ��������  : ��ʼ��ƥ��ϵͳ������ֵ�б�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��30��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_InitMatchedHrpdSysIndexList(VOS_VOID)
{
    CNAS_HSD_MATCHED_HRPD_SYS_INDEX_LIST_STRU              *pstMatchedHrpdSysIndex;

    pstMatchedHrpdSysIndex              = CNAS_HSD_GetMatchedHrpdSysIndexListAddr();
    pstMatchedHrpdSysIndex->usIndexNum  = 0;

    PS_MEM_SET(pstMatchedHrpdSysIndex->ausMatchedHrpdSysIndexList, 0, CNAS_PRL_MAX_MATCHED_HRPD_SYSTEM_NUM * (sizeof(VOS_UINT16)));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetAbortFlg_SysAcq
 ��������  : �жϸô���Ƿ��Ѵ���
 �������  : CNAS_HSD_ABORT_REASON_ENUM_UINT8    enAbortReason
 �������  : ��
 �� �� ֵ  : VOS_TRUE   --�Ѵ���
             VOS_FALSE  --������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��7��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8   CNAS_HSD_IsCurAbortFlgSet_SysAcq(
    CNAS_HSD_ABORT_REASON_ENUM_UINT8    enAbortReason
)
{
    /* �����ǰ״̬������CNAS_HSD_FSM_SYS_ACQ */
    if (CNAS_HSD_FSM_SYS_ACQ != CNAS_HSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_IsCurAbortFlgSet_SysAcq: Current state is incorrect.");

        return VOS_FALSE;
    }

    if (enAbortReason == CNAS_HSD_GetAbortReason_SysAcq())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetAbnormalLostFlag
 ��������  : ����IDLE̬�յ�CAS��abnormal lost��־
 �������  : VOS_TRUE : IDLE̬�յ�AbnormalLost
             VOS_FALSE: δ��IDLE̬�յ�AbnormalLost
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��01��27��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetAbnormalLostFlag(VOS_UINT8 ucIsAbnormalLost)
{
    CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucIsAbnormalLostFLg = ucIsAbnormalLost;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAbnormalLostFlag
 ��������  : ���IDLE̬�յ�CAS��abnormal lost��־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_TRUE : IDLE̬�յ�AbnormalLost
             VOS_FALSE: δ��IDLE̬�յ�AbnormalLost
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetAbnormalLostFlag(VOS_VOID)
{
    return CNAS_HSD_GetHsdCtxAddr()->stSysAssistInfo.ucIsAbnormalLostFLg;
}

/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



