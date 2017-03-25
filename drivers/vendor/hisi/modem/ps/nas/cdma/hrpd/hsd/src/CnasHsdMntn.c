/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdMntn.c
  �� �� ��   : ����
  ��    ��   : d00212987
  ��������   : 2014��12��16��
  ��������   : CNAS�Ŀ�ά�ɲ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��16��
    ��    ��   : d00212987
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasMntn.h"
#include "CnasHsdMntn.h"
#include "PsLib.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e545 -e413 */
/*****************************************************************************
 �� �� ��  : CNAS_HSD_LogScanFreqList
 ��������  : ��Ƶ��ɨ���б�����SDT LOG��
 �������  : pstScanFreqList - ������Scan list
             enMsgLogType    - Scan list��������

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��16��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_LogScanFreqList(
    CNAS_HSD_HRPD_SCAN_FREQ_LIST_STRU           *pstScanFreqList,
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32           enMsgLogType
)
{
    VOS_UINT32                                   i;
    CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                          (sizeof(CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogScanFreqList:Alloc Memory Failed");

        return;
    }
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_SCAN_FREQ_LIST_IND;

    pstMsg->enMsgLogType                = enMsgLogType;
    pstMsg->usTotalItemNum              = pstScanFreqList->usAvailFreqNum;
    pstMsg->usCurScanIndex              = pstScanFreqList->usCurrIndex;
    pstMsg->ucLowPrioLevel              = pstScanFreqList->ucLowPrioLevel;

    for (i = 0; i < pstScanFreqList->usAvailFreqNum; i++)
    {
        if (i >= CNAS_HSD_MAX_LOG_FREQ_NUM_IN_SCAN_LIST)
        {
            break;
        }

        pstMsg->astScanFreqList[i] = pstScanFreqList->pstScanFreqItem[i];
    }

    pstMsg->stMsgHeader.ulLength        = PS_OFFSET_OF(CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU, astScanFreqList)
                                          - VOS_MSG_HEAD_LENGTH
                                          + (pstMsg->usTotalItemNum * sizeof(CNAS_HSD_HRPD_SCAN_FREQ_ITEM_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_SCAN_FREQ_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_LogSysRecList
 ��������  : ��ϵͳ�����б�����SDT LOG��
 �������  : pstSysRecList - SYS RECORD �б�
             enMsgLogType  - SYS RECORD��������

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��16��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_LogSysRecList(
    CNAS_HSD_HRPD_SYS_LIST_STRU                  *pstSysRecList,
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32            enMsgLogType
)
{
    VOS_UINT32                                    i;
    CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                          (sizeof(CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogSysRecList:Alloc Memory Failed");

        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_HRPD_SYS_LIST_IND;

    pstMsg->enMsgLogType                = enMsgLogType;

    pstMsg->usSysNum   = pstSysRecList->usHrpdSysNum;

    for (i = 0; i < pstSysRecList->usHrpdSysNum; i++)
    {
        if (i >= CNAS_HSD_MAX_LOG_HRPD_SYS_NUM)
        {
            break;
        }

        pstMsg->astSysRecList[i] = pstSysRecList->pstHrpdSysItem[i];
    }

    pstMsg->stMsgHeader.ulLength        = PS_OFFSET_OF(CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU, astSysRecList)
                                          - VOS_MSG_HEAD_LENGTH
                                          + (pstMsg->usSysNum* sizeof(CNAS_HSD_HRPD_SYS_REC_ITEM_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_HRPD_SYS_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_LogMruList
 ��������  : ��MRU�б�����SDT LOG��
 �������  : pstMruList   - ������MRU�б�
             enMruLogType - MRU �б���³���

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��16��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_LogMruList(
    CNAS_HSD_HRPD_MRU_LIST_STRU                  *pstMruList,
    CNAS_HSD_MNTN_MRU_LOG_TYPE_ENUM_UINT8         enMruLogType
)
{
    VOS_UINT32                                    i;
    CNAS_HSD_LOG_MRU_LIST_MSG_STRU               *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_MRU_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                          (sizeof(CNAS_HSD_LOG_MRU_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogMruList:Alloc Memory Failed");

        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_MRU_LIST_IND;

    pstMsg->enMruLogType                = enMruLogType;

    pstMsg->ucSysNum    = pstMruList->ucCurrMruNum;

    for (i = 0; i < CNAS_MIN(pstMruList->ucCurrMruNum, CNAS_HSD_MAX_MRU_SYS_NUM); i++)
    {
        pstMsg->astSystem[i] = pstMruList->astHrpdSys[i];
    }

    pstMsg->stMsgHeader.ulLength        = PS_OFFSET_OF(CNAS_HSD_LOG_MRU_LIST_MSG_STRU, astSystem)
                                          - VOS_MSG_HEAD_LENGTH
                                          + (pstMsg->ucSysNum * sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_MRU_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_LogOocScheduleInfo
 ��������  : ��OOC timer������Ϣ������SDT LOG��
 �������  : pstOocTimerScheduleInfo
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��13��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_LogOocScheduleInfo(
    CNAS_NVIM_HRPD_OOC_TIMER_SCHEDULE_INFO_STRU            *pstOocTimerScheduleInfo
)
{
    VOS_UINT8                                               i;
    CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU          *pstMsg               = VOS_NULL_PTR;
    pstMsg = (CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                          sizeof(CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogOocScheduleInfo:Alloc Memory Failed");

        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_OOC_TIMER_SCHEDULE_IND;
    pstMsg->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucMru0SearchTimerLen        = pstOocTimerScheduleInfo->ucMru0SearchTimerLen;
    pstMsg->ucPhaseNum                  = pstOocTimerScheduleInfo->ucPhaseNum;

    for (i = 0; i < pstOocTimerScheduleInfo->ucPhaseNum; i++)
    {
        pstMsg->astOocTimerInfo[i].usTimes    = pstOocTimerScheduleInfo->astOocTimerInfo[i].usTimes;
        pstMsg->astOocTimerInfo[i].usTimerLen = pstOocTimerScheduleInfo->astOocTimerInfo[i].usTimerLen;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_LogOocCtxInfo
 ��������  : log OOC��������Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : Z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_LogOocCtxInfo(
    CNAS_HSD_OOC_CTX_INFO_STRU         *pstOocCtxInfo
)
{
    CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                                                                sizeof(CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogOocCtxInfo: Alloc Memory Failed!");

        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU));

    /* ������Ϣͷ��Ϣ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_OOC_CTX_INFO_IND;
    pstMsg->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ������ */
    pstMsg->ucWaitSearchFlag            = pstOocCtxInfo->ucWaitSearchFlag;
    pstMsg->ucCurrentPhase              = pstOocCtxInfo->ucCurrentPhase;
    pstMsg->usCurrentTimes              = pstOocCtxInfo->usCurrentTimes;
    pstMsg->ucSceneSetFlag              = pstOocCtxInfo->ucSceneSetFlag;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_OOC_CTX_INFO_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_LogAvoidFreqList
 ��������  : ��avoid Ƶ���б�����SDT LOG��
 �������  : pstAvoidFreqList
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_LogAvoidFreqList(
    CNAS_HSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList
)
{
    VOS_UINT8                                               i;
    CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                                                                   sizeof(CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogAvoidFreqList: Alloc Memory Failed!");

        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_AVOID_FREQ_LIST_IND;
    pstMsg->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucAvoidItemUsedNum          = pstAvoidFreqList->ucAvoidItemUsedNum;

    for (i  = 0; i < CNAS_HSD_AVOID_REASON_MAX; i++)
    {
        pstMsg->aucCounter[i]           = pstAvoidFreqList->aucCounter[i];
    }

    for (i = 0; i < CNAS_HSD_MAX_AVOID_FREQ_NUM; i++)
    {
        pstMsg->astAvoidFreqInfo[i].enUsedFlag        = pstAvoidFreqList->astAvoidFreqInfo[i].enUsedFlag;
        pstMsg->astAvoidFreqInfo[i].stAvoidFreq       = pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq;
        pstMsg->astAvoidFreqInfo[i].ulStartSlice      = pstAvoidFreqList->astAvoidFreqInfo[i].ulStartSlice;
        pstMsg->astAvoidFreqInfo[i].ulExpiredSliceNum = pstAvoidFreqList->astAvoidFreqInfo[i].ulExpiredSliceNum;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_AVOID_FREQ_LIST_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_LogRedirectionFreqList
 ��������  : ���յ����ض���Ƶ�㷨��LOG������
 �������  : pstRedirection   - �յ����ض����б�Ƶ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��20��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_LogRedirectionFreqList(
    CNAS_HSD_REDIRECTION_STRU           *pstRedirection
)
{
    CNAS_HSD_LOG_REDIRCT_MSG_STRU      *pstMsg;

    pstMsg = (CNAS_HSD_LOG_REDIRCT_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                          (sizeof(CNAS_HSD_LOG_REDIRCT_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogRedirectionFreqList:Alloc Memory Failed");

        return;
    }

    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_HSD;
    pstMsg->ulReceiverPid           = UEPS_PID_HSD;
    pstMsg->enMsgId                 = ID_CNAS_HSD_MNTN_LOG_REDIRECT_FREQ_LIST_IND;

    pstMsg->enNetworkLostReason     = CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT;

    pstMsg->ucChanNum               = pstRedirection->ucChanNum;

    PS_MEM_CPY( pstMsg->aulChannel,
                pstRedirection->aulChannel,
                (sizeof(CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU) * pstMsg->ucChanNum) );

    pstMsg->ulLength        = PS_OFFSET_OF(CNAS_HSD_LOG_REDIRCT_MSG_STRU, aulChannel)
                                           - VOS_MSG_HEAD_LENGTH
                                           + (pstMsg->ucChanNum * sizeof(CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_REDIRCT_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_LogOperLockWhiteSidList
 ��������  : ��ȡOPER LOCK WHITE SID�б�
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��1��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_LogOperLockSysWhiteList(
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstMsg
)
{
    CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU             *pstOperLockSysWhiteList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstOperLockSysWhiteList = (CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                                                                sizeof(CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU));
    if (VOS_NULL_PTR == pstOperLockSysWhiteList)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogOperLockSysWhiteList: Alloc Memory Failed!");

        return;
    }

    PS_MEM_SET(pstOperLockSysWhiteList, 0, sizeof(CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU));

    /* ������Ϣͷ��Ϣ */
    pstOperLockSysWhiteList->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstOperLockSysWhiteList->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstOperLockSysWhiteList->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstOperLockSysWhiteList->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstOperLockSysWhiteList->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_OPER_LOCK_WHITE_SID_LIST_IND;
    pstOperLockSysWhiteList->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ������ */
    pstOperLockSysWhiteList->ucEnable      = pstMsg->ucEnable;

    pstOperLockSysWhiteList->usWhiteSysNum = CNAS_MIN(pstMsg->usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM);

    for (i = 0; i < pstOperLockSysWhiteList->usWhiteSysNum;i++)
    {
        pstOperLockSysWhiteList->astSysInfo[i].usStartSid = pstMsg->astSysInfo[i].usStartSid;
        pstOperLockSysWhiteList->astSysInfo[i].usEndSid   = pstMsg->astSysInfo[i].usEndSid;
        pstOperLockSysWhiteList->astSysInfo[i].ulMcc      = pstMsg->astSysInfo[i].ulMcc;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU), (VOS_VOID *)pstOperLockSysWhiteList);

    PS_MEM_FREE(UEPS_PID_HSD, pstOperLockSysWhiteList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_LogCTCCCustomizeFreqList
 ��������  : ��ȡ�й������Զ���Ƶ���б�
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��1��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_LogCTCCCustomizeFreqList(
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstMsg
)
{
    CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU             *pstCustFreqList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstCustFreqList = (CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                                                                sizeof(CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU));
    if (VOS_NULL_PTR == pstCustFreqList)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogCTCCCustomizeFreqList: Alloc Memory Failed!");

        return;
    }

    PS_MEM_SET(pstCustFreqList, 0, sizeof(CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU));

    /* ������Ϣͷ��Ϣ */
    pstCustFreqList->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCustFreqList->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstCustFreqList->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstCustFreqList->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCustFreqList->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_CTCC_CUSTOMIZE_FREQ_LIST_IND;
    pstCustFreqList->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ������ */
    pstCustFreqList->ucEnableFlg = pstMsg->ucEnableFlg;
    pstCustFreqList->usFreqNum   = CNAS_MIN(pstMsg->usFreqNum, CNAS_CCB_MAX_FREQ_NUM);

    for (i = 0; i < pstCustFreqList->usFreqNum;i++)
    {
        pstCustFreqList->astFreqList[i].usChannel   = pstMsg->astFreqList[i].usChannel;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU), (VOS_VOID *)pstCustFreqList);

    PS_MEM_FREE(UEPS_PID_HSD, pstCustFreqList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogPrlSourceType
 ��������  : ��avoid Ƶ���б�����SDT LOG��
 �������  : enPrlSrcType -- PRLԴ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��18��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_LogPrlSourceType(
    CNAS_HSD_PRL_SOURCE_TYPE_ENUM_UINT8 enPrlSrcType
)
{
    CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD,
                                                                   sizeof(CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_LogPrlSourceType: Alloc Memory Failed!");

        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulMsgName       = ID_CNAS_HSD_MNTN_LOG_PRL_SOURCE_TYPE_IND;
    pstMsg->stMsgHeader.ulLength        = sizeof(CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enPrlSrcType                = enPrlSrcType;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_HSD, sizeof(CNAS_HSD_LOG_PRL_SOURCE_TYPE_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_HSD, pstMsg);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




