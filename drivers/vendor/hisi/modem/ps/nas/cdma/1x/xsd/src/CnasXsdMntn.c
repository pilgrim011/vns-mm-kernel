/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdMntn.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2014��08��18��
  ��������   : CNAS�Ŀ�ά�ɲ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��08��18��
    ��    ��   : w00176964
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasMntn.h"
#include "CnasXsdMntn.h"
#include "NasNvInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogScanChannelList
 ��������  : ��Ƶ��ɨ���б�����SDT LOG��
 �������  : ulMsgName----��Ϣ��
             pstScanChanList--Ƶ��ɨ���б�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��10��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 5 Modified

*****************************************************************************/
VOS_VOID CNAS_XSD_LogScanChannelList(
    VOS_UINT32                          ulMsgName,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU                 *pstMsg               = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          (sizeof(CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogScanChannelList:Alloc Memory Failed");

        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ulMsgName;

    pstMsg->usChanNum       = pstScanChanList->usTotalNum;
    pstMsg->usCurScanIndex  = pstScanChanList->usCurScanIndex;

    for (i = 0; i < pstScanChanList->usTotalNum; i++)
    {
        if (i >= CNAS_XSD_MAX_LOG_CHANNEL_NUM_IN_SCAN_LIST)
        {
            break;
        }

        pstMsg->astScanChanList[i] = pstScanChanList->pstScanChanInfo[i];
    }

    pstMsg->ulLength        = sizeof(pstMsg->enMsgId)
                              + sizeof(pstMsg->usChanNum)
                              + sizeof(pstMsg->usCurScanIndex)
                              + (pstMsg->usChanNum * sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_SCAN_CHNNEL_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogAcqSystemList
 ��������  : ��ϵͳ�����б�����SDT LOG��
 �������  : pstAcqSysList
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogAcqSystemList(
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU                  *pstMsg               = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          (sizeof(CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogAcqSystemList:Alloc Memory Failed");

        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_ACQ_SYS_LIST_IND;

    pstMsg->usSysNum   = pstGeoSysRecSrchList->usTotalNum;

    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++)
    {
        if (i >= CNAS_XSD_MAX_LOG_SYSTEM_NUM_IN_ACQ_LIST)
        {
            break;
        }

        pstMsg->astAcqSysList[i] = pstGeoSysRecSrchList->pstAcqSysInfo[i];
    }

    pstMsg->ulLength        = sizeof(pstMsg->enMsgId)
                              + sizeof(pstMsg->usSysNum)
                              + sizeof(pstMsg->aucRsv[0])*2
                              + (pstMsg->usSysNum* sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_ACQ_SYSTEM_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogAvailSystemList
 ��������  : ��availϵͳ�б�����SDT LOG��
 �������  : pstAvailSysList
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��9��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_VOID CNAS_XSD_LogAvailSystemList(
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU                *pstMsg               = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          (sizeof(CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogAvailSystemList:Alloc Memory Failed");

        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_AVAIL_SYS_LIST_IND;

    pstMsg->ucAvailSysNum = pstAvailSysList->ucAvailSysNum;

    pstMsg->ucNextSrchIndex = pstAvailSysList->ucNextSrchIndex;

    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstAvailSysList->ucAvailSysNum, CNAS_XSD_MAX_AVAILABLE_SYS_NUM); i++)
    {
        pstMsg->astAvailSystem[i] = pstAvailSysList->astAvailSystem[i];
    }

    pstMsg->ulLength = sizeof(pstMsg->enMsgId)
                       + sizeof(pstMsg->ucAvailSysNum)
                       + sizeof(pstMsg->ucNextSrchIndex)
                       + sizeof(pstMsg->aucRsved[0])*2
                       + (pstMsg->ucAvailSysNum* sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_AVAIL_SYSTEM_LIST_MSG_STRU),(VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogMruList
 ��������  : ��MRU�б�����SDT LOG��
 �������  : pstMruList
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogMruList(
    CNAS_XSD_MRU_LIST_STRU             *pstMruList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_LOG_MRU_LIST_MSG_STRU                         *pstMsg               = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_MRU_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          (sizeof(CNAS_XSD_LOG_MRU_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogMruList:Alloc Memory Failed");

        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_MRU_LIST_IND;

    pstMsg->ucSysNum    = pstMruList->ucSysNum;

    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstMruList->ucSysNum, CNAS_XSD_MAX_MRU_SYS_NUM); i++)
    {
        pstMsg->astSystem[i] = pstMruList->astSystem[i];
    }

    pstMsg->ulLength        = sizeof(pstMsg->enMsgId)
                              + sizeof(pstMsg->ucSysNum)
                              + sizeof(pstMsg->aucReserve[0])*3
                              + (pstMsg->ucSysNum* sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_MRU_LIST_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}


VOS_VOID CNAS_XSD_LogUeSupportedBandClass(
    VOS_UINT32                          ulBandClass
)
{
    CNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU                   *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          (sizeof(CNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogUeSupportedBandClass:Alloc Memory Failed");

        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_BANDClASS_LIST_IND;

    pstMsg->ulLength        = sizeof(pstMsg->enMsgId) + sizeof(VOS_UINT32);

    pstMsg->ulBandClass = ulBandClass;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_BANDCLASS_LIST_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogHomeSidNidList
 ��������  : ��HOME_SID_NID�б�����SDT LOG��
 �������  : pstHomeSidNidList
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogHomeSidNidList(
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU          *pstHomeSidNidList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU                 *pstMsg               = VOS_NULL_PTR;
    pstMsg = (CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                     sizeof(CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogHomeSidNidList:Alloc Memory Failed");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU), 0, sizeof(CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_HOME_SID_NID_LIST_IND;
    pstMsg->ucSysNum        = CNAS_MIN(pstHomeSidNidList->ucSysNum, CNAS_CCB_MAX_HOME_SID_NID_LIST);

    for (i = 0; i < pstMsg->ucSysNum; i++)
    {
        NAS_MEM_CPY_S(&pstMsg->astHomeSidNid[i],
                      sizeof(CNAS_CCB_1X_HOME_SID_NID_STRU),
                      &pstHomeSidNidList->astHomeSidNid[i],
                      sizeof(CNAS_CCB_1X_HOME_SID_NID_STRU));
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_HOME_SID_NID_LIST_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogOocScheduleInfo
 ��������  : ��OOC timer������Ϣ������SDT LOG��
 �������  : pstOocTimerScheduleInfo
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogOocScheduleInfo(
    CNAS_NVIM_OOC_TIMER_SCHEDULE_INFO_STRU                 *pstOocTimerScheduleInfo
)
{
    VOS_UINT8                                               i;
    CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU          *pstMsg               = VOS_NULL_PTR;
    pstMsg = (CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                          sizeof(CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogOocScheduleInfo:Alloc Memory Failed");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU), 0, sizeof(CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_OOC_TIMER_SCHEDULE_IND;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucMru0SearchTimerLen        = pstOocTimerScheduleInfo->ucMru0SearchTimerLen;
    pstMsg->ucPhaseNum                  = pstOocTimerScheduleInfo->ucPhaseNum;
    pstMsg->uc1xOocDoTchPhase1TimerLen  = pstOocTimerScheduleInfo->uc1xOocDoTchPhase1TimerLen;
    pstMsg->uc1xOocDoTchPhase2TimerLen  = pstOocTimerScheduleInfo->uc1xOocDoTchPhase2TimerLen;

    for (i = 0; i < pstOocTimerScheduleInfo->ucPhaseNum; i++)
    {
        pstMsg->astOocTimerInfo[i].usTimes    = pstOocTimerScheduleInfo->astOocTimerInfo[i].usTimes;
        pstMsg->astOocTimerInfo[i].usTimerLen = pstOocTimerScheduleInfo->astOocTimerInfo[i].usTimerLen;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_OOC_TIMER_SCHEDULE_INFO_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogAvoidFreqList
 ��������  : ��avoid Ƶ���б�����SDT LOG��
 �������  : pstAvoidFreqList
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogAvoidFreqList(
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList
)
{
    VOS_UINT8                                               i;
    VOS_UINT8                                               j;
    CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                   sizeof(CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogAvoidFreqList: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU), 0, sizeof(CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_AVOID_FREQ_LIST_IND;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ucAvoidFreqNum              = pstAvoidFreqList->ucAvoidFreqNum;

    for (i = 0; i < CNAS_MIN(pstAvoidFreqList->ucAvoidFreqNum, CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        pstMsg->astAvoidFreqInfo[i].ucAvoidFlag       = pstAvoidFreqList->astAvoidFreqInfo[i].ucAvoidFlag;
        pstMsg->astAvoidFreqInfo[i].stAvoidFreq       = pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq;
        pstMsg->astAvoidFreqInfo[i].ulStartSlice      = pstAvoidFreqList->astAvoidFreqInfo[i].ulStartSlice;
        pstMsg->astAvoidFreqInfo[i].ulExpiredSliceNum = pstAvoidFreqList->astAvoidFreqInfo[i].ulExpiredSliceNum;

        for (j = 0; j < CNAS_XSD_AVOID_REASON_MAX; j++)
        {
            pstMsg->astAvoidFreqInfo[i].aucAvoidTimes[j] = pstAvoidFreqList->astAvoidFreqInfo[i].aucAvoidTimes[j];
        }

    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_AVOID_FREQ_LIST_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

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
  1.��    ��   : 2014��10��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogPrlSourceType(
    CNAS_XSD_PRL_SOURCE_TYPE_ENUM_UINT8 enPrlSrcType
)
{
    CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                   sizeof(CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogPrlSourceType: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU), 0, sizeof(CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU));

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_PRL_SOURCE_TYPE_IND;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->enPrlSrcType                = enPrlSrcType;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_PRL_SOURCE_TYPE_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogBufferQueueMsg
 ��������  : �����������Ϣ
 �������  : ulFullFlg:�����Ƿ��Ѿ����ı�־λ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��5��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_XSD_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
)
{
    CNAS_XSD_LOG_BUffER_MSG_INFO_STRU  *pstBufferMsg = VOS_NULL_PTR;
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue  = VOS_NULL_PTR;

    pstBufferMsg = (CNAS_XSD_LOG_BUffER_MSG_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_XSD,
                             sizeof(CNAS_XSD_LOG_BUffER_MSG_INFO_STRU));

    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogBufferQueueMsg: Alloc Memory Failed!");
        return;
    }

    NAS_MEM_SET_S(pstBufferMsg, sizeof(CNAS_XSD_LOG_BUffER_MSG_INFO_STRU), 0, sizeof(CNAS_XSD_LOG_BUffER_MSG_INFO_STRU));

    pstMsgQueue                               = CNAS_XSD_GetCacheMsgAddr();
    pstBufferMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->ulSenderPid     = UEPS_PID_XSD;
    pstBufferMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstBufferMsg->ulLength        = sizeof(CNAS_XSD_LOG_BUffER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->enMsgId       = ID_CNAS_XSD_MNTN_LOG_BUFFER_MSG_INFO_IND;
    pstBufferMsg->ulFullFlg                   = ulFullFlg;
    NAS_MEM_CPY_S(&(pstBufferMsg->stMsgQueue), sizeof(pstBufferMsg->stMsgQueue), pstMsgQueue, sizeof(pstBufferMsg->stMsgQueue));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstBufferMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogOocCtxInfo
 ��������  : log OOC��������Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��22��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogOocCtxInfo(
    CNAS_XSD_OOC_CTX_INFO_STRU         *pstOocCtxInfo
)
{
    CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogOocCtxInfo: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU), 0, sizeof(CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU));

    /* ������Ϣͷ��Ϣ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_OOC_CTX_INFO_IND;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ������ */
    pstMsg->ucAttemptTimesInDoTraffic   = pstOocCtxInfo->ucAttemptTimesInDoTraffic;
    pstMsg->ucCurrentPhase              = pstOocCtxInfo->ucCurrentPhase;
    pstMsg->ucDoTrafficFlag             = pstOocCtxInfo->ucDoTrafficFlag;
    pstMsg->ucFirstFourAcqArrivedFlag   = pstOocCtxInfo->ucFirstFourAcqArrivedFlag;
    pstMsg->ucSceneSetFlag              = pstOocCtxInfo->ucSceneSetFlag;
    pstMsg->ucWaitSearchFlag            = pstOocCtxInfo->ucWaitSearchFlag;
    pstMsg->usCurrentTimes              = pstOocCtxInfo->usCurrentTimes;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_OOC_CTX_INFO_MSG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogHomeSidNidMostPriFlg
 ��������  : ��ȡhome sid/nid�Ƿ�������ѡ�ı��
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogHomeSidNidDependOnPrlFlg(
    VOS_UINT8                           ucFlg
)
{
    CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogHomeSidNidMostPriCfg: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU), 0, sizeof(CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU));

    /* ������Ϣͷ��Ϣ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_HOME_SID_NID_PRI_FLG;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ������ */
    pstMsg->ucHomeSidNidMostPriFlg      = ucFlg;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_HOME_SID_NID_MOST_PRI_FLG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogOperLockWhiteSidList
 ��������  : ��ȡOPER LOCK WHITE SID�б�
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogOperLockSysWhiteList(
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstMsg
)
{
    CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU             *pstOperLockSysWhiteList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstOperLockSysWhiteList = (CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU));
    if (VOS_NULL_PTR == pstOperLockSysWhiteList)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogOperLockSysWhiteList: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstOperLockSysWhiteList, sizeof(CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU), 0, sizeof(CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU));

    /* ������Ϣͷ��Ϣ */
    pstOperLockSysWhiteList->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstOperLockSysWhiteList->ulSenderPid     = UEPS_PID_XSD;
    pstOperLockSysWhiteList->ulReceiverPid   = UEPS_PID_XSD;
    pstOperLockSysWhiteList->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstOperLockSysWhiteList->enMsgId         = ID_CNAS_XSD_MNTN_LOG_OPER_LOCK_WHITE_SID_LIST_IND;
    pstOperLockSysWhiteList->ulLength        = sizeof(CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ������ */
    pstOperLockSysWhiteList->ucEnable      = pstMsg->ucEnable;

    pstOperLockSysWhiteList->usWhiteSysNum = CNAS_MIN(pstMsg->usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM);

    for (i = 0; i < pstOperLockSysWhiteList->usWhiteSysNum;i++)
    {
        pstOperLockSysWhiteList->astSysInfo[i].usStartSid = pstMsg->astSysInfo[i].usStartSid;
        pstOperLockSysWhiteList->astSysInfo[i].usEndSid   = pstMsg->astSysInfo[i].usEndSid;
        pstOperLockSysWhiteList->astSysInfo[i].ulMcc      = pstMsg->astSysInfo[i].ulMcc;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_OPER_LOCK_SYS_WHITE_LIST_STRU), (VOS_VOID *)pstOperLockSysWhiteList);

    PS_MEM_FREE(UEPS_PID_XSD, pstOperLockSysWhiteList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogCTCCCustomizeFreqList
 ��������  : ��ȡ�й������Զ���Ƶ���б�
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogCTCCCustomizeFreqList(
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstMsg
)
{
    CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU             *pstCustFreqList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstCustFreqList = (CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU));
    if (VOS_NULL_PTR == pstCustFreqList)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LogCTCCCustomizeFreqList: Alloc Memory Failed!");

        return;
    }

    NAS_MEM_SET_S(pstCustFreqList, sizeof(CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU), 0, sizeof(CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU));

    /* ������Ϣͷ��Ϣ */
    pstCustFreqList->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCustFreqList->ulSenderPid     = UEPS_PID_XSD;
    pstCustFreqList->ulReceiverPid   = UEPS_PID_XSD;
    pstCustFreqList->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCustFreqList->enMsgId         = ID_CNAS_XSD_MNTN_LOG_CTCC_CUSTOMIZE_FREQ_LIST_IND;
    pstCustFreqList->ulLength        = sizeof(CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ������ */
    pstCustFreqList->ucEnableFlg = pstMsg->ucEnableFlg;
    pstCustFreqList->usFreqNum   = CNAS_MIN(pstMsg->usFreqNum, CNAS_CCB_MAX_FREQ_NUM);

    for (i = 0; i < pstCustFreqList->usFreqNum;i++)
    {
        pstCustFreqList->astFreqList[i].usChannel   = pstMsg->astFreqList[i].usChannel;
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_CTCC_CUSTOMIZE_FREQ_LIST_STRU), (VOS_VOID *)pstCustFreqList);

    PS_MEM_FREE(UEPS_PID_XSD, pstCustFreqList);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogGeoSrchStatusList
 ��������  : GEO����״̬list
 �������  : pstGeoSrchStatus -- GEO����״̬�б���Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogGeoListSrchStatus(
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU    *pstGeoSrchStatus
)
{
    CNAS_XSD_LOG_GEO_LIST_SRCH_STATUS_STRU                 *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLen;
    VOS_UINT16                                              usGeoNum;

    usGeoNum = (VOS_UINT16)CNAS_MIN(pstGeoSrchStatus->usGeoNum, CNAS_XSD_MAX_LOG_SYSTEM_NUM_IN_ACQ_LIST);

    ulMsgLen = sizeof(MSG_HEADER_STRU) + sizeof(VOS_UINT16) + sizeof(VOS_UINT16) +\
               sizeof(CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU) * usGeoNum;

    pstMsg = (CNAS_XSD_LOG_GEO_LIST_SRCH_STATUS_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, ulMsgLen, 0, ulMsgLen);

    /* ������Ϣͷ��Ϣ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_GEO_LIST_SRCH_STATUS_IND;
    pstMsg->ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;

    pstMsg->usGeoNum                    = usGeoNum;

    if (0 != usGeoNum)
    {
        NAS_MEM_CPY_S(&pstMsg->astGeoSrchInfo[0],
                      sizeof(CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU) * pstMsg->usGeoNum,
                      pstGeoSrchStatus->pstGeoSrchInfo,
                      sizeof(CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU) * pstMsg->usGeoNum);
    }

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, ulMsgLen, (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU
 ��������  : LOG CDMA��׼Ƶ��
 �������  : pstCdmaStandardChan -- CDMA��׼Ƶ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogCdmaStandardChannels(
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan
)
{
    CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU               *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                      sizeof(CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU), 0, sizeof(CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU));

    /* ������Ϣͷ��Ϣ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_XSD;
    pstMsg->ulReceiverPid   = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->enMsgId         = ID_CNAS_XSD_MNTN_LOG_CDMA_STANDARD_CHANNELS_IND;
    pstMsg->ulLength        = sizeof(CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stCdmaStandardChan.usPrimaryA   = pstCdmaStandardChan->usPrimaryA;

    pstMsg->stCdmaStandardChan.usPrimaryB   = pstCdmaStandardChan->usPrimaryB;

    pstMsg->stCdmaStandardChan.usSecondaryA = pstCdmaStandardChan->usSecondaryA;

    pstMsg->stCdmaStandardChan.usSecondaryB = pstCdmaStandardChan->usSecondaryB;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_CDMA_STANDARD_CHANNELS_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogCallBackConfig
 ��������  : LOG CallBackģʽNv����
 �������  : pstCdmaStandardChan -- CDMA��׼Ƶ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogCallBackConfig(
    CNAS_XSD_CALLBACK_CFG_STRU                             *pstCallBackCfg
)
{
    CNAS_XSD_LOG_CALLBACK_CFG_STRU                          *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_CALLBACK_CFG_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_LOG_CALLBACK_CFG_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_CALLBACK_CFG_STRU), 0, sizeof(CNAS_XSD_LOG_CALLBACK_CFG_STRU));

    /* ������Ϣͷ��Ϣ */
    pstMsg->ulReceiverCpuId                         = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                             = UEPS_PID_XSD;
    pstMsg->ulReceiverPid                           = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId                           = VOS_LOCAL_CPUID;
    pstMsg->enMsgId                                 = ID_CNAS_XSD_MNTN_LOG_CALLBACK_CFG_IND;
    pstMsg->ulLength                                = sizeof(CNAS_XSD_LOG_CALLBACK_CFG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stCallBackCfg.ulCallBackEnableFlg       = pstCallBackCfg->ulCallBackEnableFlg;
    pstMsg->stCallBackCfg.ulCallBackModeTimerLen    = pstCallBackCfg->ulCallBackModeTimerLen;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_CALLBACK_CFG_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogCallBackStatusInd
 ��������  : LOG CallBackģʽNv����
 �������  : pstCdmaStandardChan -- CDMA��׼Ƶ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogCallBackStatusInd(
    CNAS_XSD_MNTN_MSG_ID_ENUM_UINT32                        enMsgId
)
{
    CNAS_XSD_LOG_CALLBACK_STATUS_STRU                        *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_CALLBACK_STATUS_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                               sizeof(CNAS_XSD_LOG_CALLBACK_STATUS_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_CALLBACK_STATUS_STRU), 0, sizeof(CNAS_XSD_LOG_CALLBACK_STATUS_STRU));

    /* ������Ϣͷ��Ϣ */
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->enMsgId                     = enMsgId;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_LOG_CALLBACK_STATUS_STRU) - VOS_MSG_HEAD_LENGTH;

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_CALLBACK_STATUS_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_LogCdma1XPrefChannels
 ��������  : LOG Cdma 1X��ѡƵ����Ϣ
 �������  : pstCdma1XPrefChannels -- CDMA 1X ��ѡƵ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_LogCdma1XCustomPrefChannels(
    CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU             *pstCdma1XPrefChannels
)
{
    CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_MEM_SET_S(pstMsg, sizeof(CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU), 0x00, sizeof(CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU));

    /* ������Ϣͷ��Ϣ */
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->enMsgId                     = ID_CNAS_XSD_MNTN_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_IND;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU) - VOS_MSG_HEAD_LENGTH;
    NAS_MEM_CPY_S(&(pstMsg->stCdma1XPrefChannels),
                  sizeof(pstMsg->stCdma1XPrefChannels),
                  pstCdma1XPrefChannels,
                  sizeof(CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU));

    CNAS_MNTN_TraceIntMsg(UEPS_PID_XSD, sizeof(CNAS_XSD_LOG_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU), (VOS_VOID *)pstMsg);

    PS_MEM_FREE(UEPS_PID_XSD, pstMsg);
}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




