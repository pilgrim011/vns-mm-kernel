/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdComFunc.c
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��7��14��
  ����޸�   :
  ��������   : XSDģ�鹫�ú�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��14��
    ��    ��   : h00246512
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsCommonDef.h"
#include  "CnasTimerMgmt.h"
#include  "CnasXsdComFunc.h"
#include  "CnasMntn.h"
#include  "CnasPrlApi.h"
#include  "CnasXsdCtx.h"
#include  "CnasXsdMntn.h"

#include "cas_1x_idlectrl_proc_nas_pif.h"
#include "xsd_mscc_pif.h"
#include "xsd_xreg_pif.h"
#include "CnasPrlParse.h"
#include "CnasXsdSndXreg.h"
#include "CnasXsdSndMscc.h"
#include "CnasXsdSysAcqStrategy.h"

#include  "CnasXsdSndInternalMsg.h"
#include  "CnasXsdFsmMain.h"
#include  "CnasXsdFsmMainTbl.h"

#include "CnasXsdSndCas.h"
#include "Nas_Mem.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_COM_FUNC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

CNAS_XSD_CHANNEL_SUPPORTED_IN_BANDCLASS_TBL_STRU            g_aucChannelSupportedInBandClassTbl[CNAS_PRL_BAND_CLASS_TYPE_MAX] =
{
    {CNAS_PRL_BAND_CLASS_TYPE_0,                            CNAS_XSD_IsUeSupportedChannel_BandClass_0},
    {CNAS_PRL_BAND_CLASS_TYPE_1,                            CNAS_XSD_IsUeSupportedChannel_BandClass_1},
    {CNAS_PRL_BAND_CLASS_TYPE_2,                            CNAS_XSD_IsUeSupportedChannel_BandClass_2},
    {CNAS_PRL_BAND_CLASS_TYPE_3,                            CNAS_XSD_IsUeSupportedChannel_BandClass_3},
    {CNAS_PRL_BAND_CLASS_TYPE_4,                            CNAS_XSD_IsUeSupportedChannel_BandClass_4},
    {CNAS_PRL_BAND_CLASS_TYPE_5,                            CNAS_XSD_IsUeSupportedChannel_BandClass_5},
    {CNAS_PRL_BAND_CLASS_TYPE_6,                            CNAS_XSD_IsUeSupportedChannel_BandClass_6},
    {CNAS_PRL_BAND_CLASS_TYPE_7,                            CNAS_XSD_IsUeSupportedChannel_BandClass_7},
    {CNAS_PRL_BAND_CLASS_TYPE_8,                            CNAS_XSD_IsUeSupportedChannel_BandClass_8},
    {CNAS_PRL_BAND_CLASS_TYPE_9,                            CNAS_XSD_IsUeSupportedChannel_BandClass_9},
    {CNAS_PRL_BAND_CLASS_TYPE_10,                           CNAS_XSD_IsUeSupportedChannel_BandClass_10},
    {CNAS_PRL_BAND_CLASS_TYPE_11,                           CNAS_XSD_IsUeSupportedChannel_BandClass_11},
    {CNAS_PRL_BAND_CLASS_TYPE_12,                           CNAS_XSD_IsUeSupportedChannel_BandClass_12},
    {CNAS_PRL_BAND_CLASS_TYPE_13,                           CNAS_XSD_IsUeSupportedChannel_BandClass_13},
    {CNAS_PRL_BAND_CLASS_TYPE_14,                           CNAS_XSD_IsUeSupportedChannel_BandClass_14},
    {CNAS_PRL_BAND_CLASS_TYPE_15,                           CNAS_XSD_IsUeSupportedChannel_BandClass_15}
};


#ifdef DMT
VOS_UINT32                              g_ulCurSlice = 0;
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_StartTimer
 ��������  : XSDģ���װ��������ʱ������
 �������  : CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId,
             VOS_UINT32                          ulTimerLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_StartTimer(
    CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    CNAS_TIMER_INFO_STRU                stTimerInfo;

    if (0 == ulTimerLen)
    {
        CNAS_WARNING_LOG1(UEPS_PID_XSD, "CNAS_XSD_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return ;
    }

    /* ��ǰXSD�Ķ�ʱ����ulParam��ʱ�ò�����ȡֵΪ0��ulTimerPrecision����
       VOS_TIMER_NO_PRECISION�����������Ҫ����TimerId������ͬ�趨ʱ����
       ������صķ�װ���� */
    NAS_MEM_SET_S(&stTimerInfo, sizeof(stTimerInfo), 0, sizeof(CNAS_TIMER_INFO_STRU));
    stTimerInfo.ulTimerId               = enTimerId;
    stTimerInfo.ulTimerLen              = ulTimerLen;
    stTimerInfo.ulParam                 = 0;
    stTimerInfo.ulTimerPrecision        = VOS_TIMER_PRECISION_0;

    CNAS_StartTimer(UEPS_PID_XSD, &stTimerInfo);


}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_StopTimer
 ��������  : XSDģ���װ��ֹͣ��ʱ������
 �������  : CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_StopTimer(
    CNAS_XSD_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    /* XSDģ�鲻ҪulParam������ڵ���CNAS_StopTimer��ʱ��ulParamֵΪ0*/
    CNAS_StopTimer(UEPS_PID_XSD, enTimerId, 0);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAvoidTimerLen
 ��������  : ��ȡavoid timerʱ��
 �������  : enReason -- avoidԭ��ֵ
             VOS_UINT8                           ucAvoidTimes
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��11��12��
    ��    ��   : c00299063
    �޸�����   : avoid timerʱ���ɱ�
*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetAvoidTimerLen(
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enReason,
    VOS_UINT16                          usAvoidTimes
)
{

    CNAS_XSD_AVOID_SCHEDULE_INFO_STRU  *pstAvoidScheduleInfo = VOS_NULL_PTR;

    if (enReason < CNAS_XSD_AVOID_REASON_MAX)
    {
        pstAvoidScheduleInfo = CNAS_XSD_GetAvoidScheduInfoAddr();

        if (usAvoidTimes < CNAS_XSD_AVOID_MAX_PHASE_NUM)
        {
           return pstAvoidScheduleInfo->aucAvoidTimerLen[enReason][usAvoidTimes];
        }

        /*���������洢��ʱ��ʱ���������󳤶ȣ�ȡ���������һ������*/
        return pstAvoidScheduleInfo->aucAvoidTimerLen[enReason][CNAS_XSD_AVOID_MAX_PHASE_NUM - 1];


    }

    return 0;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdataAvoidListInfo
 ��������  : ���Ƶ����Ϣ��avoidƵ���б�
 �������  : pstFreq        -- avoidƵ��
             ulExpiredSlice -- ����slice

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
 �޸���ʷ      :
  2.��    ��   : 2015��11��12��
    ��    ��   : c00299063
    �޸�����   : ���Ӽ�¼����avoidƵ��Ĵ���
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdataAvoidListInfo(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;
    CNAS_XSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucAvoidTimes;
    VOS_UINT16                          usTimerLen;

    ucAvoidTimes = CNAS_XSD_GetAvoidTimesOfAvoidFreq(pstFreq, enAvoidReason);

    /* ��ȡ��ʱ��ʱ�� */
    usTimerLen  = CNAS_XSD_GetAvoidTimerLen(enAvoidReason, ucAvoidTimes);

    if (0 == usTimerLen)
    {
        return;
    }

    pstAvoidFreqList = CNAS_XSD_GetAvoidFreqListAddr();

    ucIndex = 0;

    if (VOS_TRUE == CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(pstFreq, &ucIndex))
    {
        pstAvoidFreqInfo = &(pstAvoidFreqList->astAvoidFreqInfo[ucIndex]);
    }
    else
    {
        if (pstAvoidFreqList->ucAvoidFreqNum < CNAS_XSD_MAX_AVOID_FREQ_NUM)
        {
            pstAvoidFreqInfo = &(pstAvoidFreqList->astAvoidFreqInfo[pstAvoidFreqList->ucAvoidFreqNum]);

            pstAvoidFreqList->ucAvoidFreqNum++;
        }
    }

    if (VOS_NULL_PTR == pstAvoidFreqInfo)
    {
        return;
    }

    /* ����Ƶ���뵽��slice��avoidƵ���б� */
    pstAvoidFreqInfo->stAvoidFreq.enBandClass = pstFreq->enBandClass;
    pstAvoidFreqInfo->stAvoidFreq.usChannel   = pstFreq->usChannel;
    pstAvoidFreqInfo->ulStartSlice            = CNAS_XSD_GetSystemSlice();
    pstAvoidFreqInfo->ulExpiredSliceNum       = CNAS_XSD_GetSystemSliceNumOfOneSecond() * usTimerLen;
    pstAvoidFreqInfo->ucAvoidFlag             = VOS_TRUE;


    if (pstAvoidFreqInfo->aucAvoidTimes[enAvoidReason] < CNAS_XSD_AVOID_MAX_PHASE_NUM)
    {
        pstAvoidFreqInfo->aucAvoidTimes[enAvoidReason]++;
    }

    return;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_DeleteAcqSuccFreqOfAvoidList
 ��������  : ��avoid�б���ɾ��Ƶ����Ϣ
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��16��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_DeleteAcqSuccFreqOfAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
)
{

    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstLastSyncedFreq = VOS_NULL_PTR;

    pstLastSyncedFreq = CNAS_XSD_GetLastSyncedFreq();

    CNAS_XSD_DeleteUsableFreqFormAvoidList(pstFreq);

    /*���ϵͳ��Ϣ���ϴ�ͬ���ɹ���Ƶ�㲻��ͬ��hash�����л����� */
    if ((pstLastSyncedFreq->enBandClass != pstFreq->enBandClass)
     || (pstLastSyncedFreq->usChannel   != pstFreq->usChannel))
    {
        CNAS_XSD_DeleteUsableFreqFormAvoidList(pstLastSyncedFreq);
    }

    return;

}


/*****************************************************************************
 �� �� ��  : IsExistAvoidFlagInAvoidlist
 ��������  : avoid list ���Ƿ��е�Ƶ�㻹δ���
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��16��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsExistAvoidFlagInAvoidlist()
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    for (i = 0; i < CNAS_MIN(pstAvoidFreqList->ucAvoidFreqNum, CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        if (VOS_TRUE == pstAvoidFreqList->astAvoidFreqInfo[i].ucAvoidFlag)
        {
           return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearAccessSuccessFreqFormAvoidList
 ��������  : ��avoid�б���ɾ��Ƶ����Ϣ
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��16��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ClearAccessSuccessFreqFormAvoidList()
{
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCampedSysInfo = VOS_NULL_PTR;
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    ucIndex             = 0;

    pstCampedSysInfo = CNAS_XSD_GetCurCampedSysInfo();

    if (VOS_TRUE == CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(&(pstCampedSysInfo->stSystem.stFreq), &ucIndex))
    {
        /*���avoid�б��в����ڽ��ñ�ǣ���ʾû�б����õ�Ƶ�㣬ֹͣ��ʱ�� */

        CNAS_XSD_ClearAvoidFreqInfoOfAvoidList(ucIndex);

        if (VOS_FALSE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
        {
            CNAS_XSD_StopTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER);
        }

        CNAS_XSD_LogAvoidFreqList(pstAvoidFreqList);
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_DeleteAvoidFreqInfoOfAvoidList
 ��������  : ��avoid�б���ɾ��Ƶ����Ϣ
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��16��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearAvoidFreqInfoOfAvoidList(
    VOS_UINT8                           ucAvoidListIndex
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList    = VOS_NULL_PTR;

    pstAvoidFreqList = CNAS_XSD_GetAvoidFreqListAddr();

    if ((CNAS_XSD_MAX_AVOID_FREQ_NUM - 1) == ucAvoidListIndex)
    {
        NAS_MEM_SET_S(&(pstAvoidFreqList->astAvoidFreqInfo[ucAvoidListIndex]),
                      sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU),
                      0,
                      sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU));
    }
    else if (ucAvoidListIndex < (CNAS_XSD_MAX_AVOID_FREQ_NUM - 1))
    {
        if ((pstAvoidFreqList->ucAvoidFreqNum - 1) > ucAvoidListIndex)
        {
            NAS_MEM_MOVE_S(&(pstAvoidFreqList->astAvoidFreqInfo[ucAvoidListIndex]),
                            (pstAvoidFreqList->ucAvoidFreqNum - ucAvoidListIndex) * sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU),
                           &(pstAvoidFreqList->astAvoidFreqInfo[ucAvoidListIndex + 1]),
                            (pstAvoidFreqList->ucAvoidFreqNum - ucAvoidListIndex - 1) * sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU));
        }

        NAS_MEM_SET_S(&(pstAvoidFreqList->astAvoidFreqInfo[pstAvoidFreqList->ucAvoidFreqNum - 1]),
                      sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU),
                      0,
                      sizeof(CNAS_XSD_AVOID_FREQ_INFO_STRU));
    }
    else
    {
        return;
    }

    pstAvoidFreqList->ucAvoidFreqNum--;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsAddSyncFailFreqInAvoidList
 ��������  : ���Ƶ��ͬ��ʧ�ܵ�ʱ�̵�����avoid�б��ʱ���Ѿ������˽����ʱ�䣬�򲻼���
 �������  :     CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstSyncFailFreq,
                 VOS_UINT32                          ulSyncFailSlice,
                 CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsAddSyncFailFreqInAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstSyncFailFreq,
    VOS_UINT32                          ulSyncFailSlice,
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    VOS_UINT32                          ulExpiredSliceNum;
    VOS_UINT16                          usTimerLen;
    VOS_UINT32                          ulCurrSlice;
    VOS_UINT32                          ulRunSliceNum;
    VOS_UINT8                           ucAvoidTimes;

    ucAvoidTimes = CNAS_XSD_GetAvoidTimesOfAvoidFreq(pstSyncFailFreq, enAvoidReason);

    usTimerLen  = CNAS_XSD_GetAvoidTimerLen(enAvoidReason, ucAvoidTimes);

    if (0 != usTimerLen)
    {
        /* ������Ҫ���ٸ�slice���� */
        ulExpiredSliceNum = usTimerLen * CNAS_XSD_GetSystemSliceNumOfOneSecond();

        ulCurrSlice       = CNAS_XSD_GetSystemSlice();

        ulRunSliceNum     = (ulCurrSlice - ulSyncFailSlice);

        ulRunSliceNum     = ulRunSliceNum % CNAS_XSD_MAX_SLICE_VALUE;

        if (ulRunSliceNum < ulExpiredSliceNum)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAvoidTimesOfAvoidFreq
 ��������  : ��ȡƵ���б���ֹ�Ĵ���
 �������  : CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAvoidFreq,
             CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetAvoidTimesOfAvoidFreq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAvoidFreq,
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCount;

    ucIndex          = 0;

    pstAvoidFreqList = CNAS_XSD_GetAvoidFreqListAddr();

    if (VOS_TRUE == CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(pstAvoidFreq, &ucIndex))
    {
        ucCount = pstAvoidFreqList->astAvoidFreqInfo[ucIndex].aucAvoidTimes[enAvoidReason];

        return ucCount;
    }

    return 0;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearAvoidCountFromAvoidList
 ��������  : ���avoid������avoid�б���
 �������  : VOS_UINT8                           ucAvoidListIndex,
             CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ClearAvoidCountFromAvoidList(
    VOS_UINT8                           ucAvoidListIndex,
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList    = VOS_NULL_PTR;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    pstAvoidFreqList->astAvoidFreqInfo[ucAvoidListIndex].aucAvoidTimes[enAvoidReason] = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsClearFreqInfoOfAvoidList
 ��������  : ���avoid������avoid�б���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsClearFreqInfoOfAvoidList(
    VOS_UINT8                           ucAvoidListIndex
)
{
    VOS_UINT32                          i;
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList    = VOS_NULL_PTR;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    for (i = 0; i < CNAS_XSD_AVOID_REASON_MAX; i++)
    {
        if (0 != pstAvoidFreqList->astAvoidFreqInfo[ucAvoidListIndex].aucAvoidTimes[i])
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason
 ��������  : process required avoid frequency according to avoid reason
 �������  : enAvoidReason----avoid reason
             pstAvoidFreq ----avoid frequency
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��26��
    ��    ��   : w00176964
    �޸�����   : CDMA Iteration 6 Modified

*****************************************************************************/
VOS_VOID CNAS_XSD_ProcRequiredAvoidedFreqByAvoidReason(
    CNAS_XSD_AVOID_REASON_ENUM_UINT8    enAvoidReason,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAvoidFreq
)
{
    CNAS_XSD_UpdataAvoidListInfo(pstAvoidFreq, enAvoidReason);

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
 �� �� ��  : CNAS_XSD_GetSystemSlice
 ��������  : ��ȡϵͳslice
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetSystemSlice(VOS_VOID)
{
#ifdef DMT
    return g_ulCurSlice;
#else
    return VOS_GetSlice();
#endif

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetSystemSliceNumOfEverySecond
 ��������  : ��ȡ1��slice�ĸ���
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetSystemSliceNumOfOneSecond(VOS_VOID)
{
    return VOS_GetSliceUnit();
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_TransferMsccCallTypeToXsdFormat
 ��������  : �յ�����������Ϣ������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��2��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8 CNAS_XSD_TransferMsccCallTypeToXsdFormat(
    NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8          enMsccCallType
)
{
    CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8 enCallExistFlg;

    switch (enMsccCallType)
    {
        case NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL:
            enCallExistFlg = CNAS_XSD_EMC_VOICE_CALL_EXIST_FLAG;
            break;

        case NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_VOICE_CALL:
            enCallExistFlg = CNAS_XSD_NORMAL_VOICE_CALL_EXIST_FLAG;
            break;

        case NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL:
            enCallExistFlg = CNAS_XSD_NORMAL_DATA_CALL_EXIST_FLAG;
            break;

        default:
            enCallExistFlg = CNAS_XSD_CALL_EXIST_NULL_FLAG;
            break;
    }

   return enCallExistFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedFreq
 ��������  : check the band class and chenne are supported by UE or not
 �������  : CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreqChan
 �������  : NONE
 �� �� ֵ  : VOS_TRUE----UE support
             VOS_FALSE---UE could not support
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 26/12/2014
    ��    ��   : w00176964
    �޸�����   : Create
  1.��    ��   : 19/1/2015
    ��    ��   : y00307564
    �޸�����   : ��PCLINT
  3.��    ��   : 3/8/2015
    ��    ��   : c00299063
    �޸�����   : ����Ƶ�����
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedFreq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreqChan
)
{
    VOS_UINT32                          ulSupportedBand;
    VOS_UINT32                          i;
    pCNasXsdBandSupportChanBuildFunc    pfunBandSupportChanBuild = VOS_NULL_PTR;

    ulSupportedBand = CNAS_XSD_GetUeSupportedBandClass();

    if (0 == (ulSupportedBand & ((VOS_UINT32)1 << stFreqChan.enBandClass)))
    {
        return VOS_FALSE;
    }

    for (i = 0; i < (sizeof(g_aucChannelSupportedInBandClassTbl)/sizeof(CNAS_XSD_CHANNEL_SUPPORTED_IN_BANDCLASS_TBL_STRU)); i++)
    {
        if ((VOS_UINT32)stFreqChan.enBandClass == g_aucChannelSupportedInBandClassTbl[i].ulBandClass)
        {
            pfunBandSupportChanBuild = g_aucChannelSupportedInBandClassTbl[i].pfunBandSupportChanBuild;
            break;
        }
    }

    if (VOS_NULL_PTR == pfunBandSupportChanBuild)
    {
        return VOS_FALSE;
    }
    else
    {
        return pfunBandSupportChanBuild(stFreqChan.usChannel);
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_0
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_0(
    VOS_UINT16                          usChannel
)
{
    if (((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_799))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_991) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1323)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_1
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_1(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1199)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_2
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_2(
    VOS_UINT16                          usChannel
)
{
    if ((usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1000)
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1329) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_2047)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_3
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_3(
    VOS_UINT16                          usChannel
)
{
    if (((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_799))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_801) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1039))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1041) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1199))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1201) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1600)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_4
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_4(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_599)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_5
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_5(
    VOS_UINT16                          usChannel
)
{
    if (((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_400))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_539) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_871))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1039) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1473))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1536) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1715))
     || ((usChannel >= CNAS_PRL_CDMA_CHANNEL_RANGE_1792) && (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_2016)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_6
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_6(
    VOS_UINT16                          usChannel
)
{
    return CNAS_XSD_IsUeSupportedChannel_BandClass_1(usChannel);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_7
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_7(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_359)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_8
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_8(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1499)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_9
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_9(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_699)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_10
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_10(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_919)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_11
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_11(
    VOS_UINT16                          usChannel
)
{
    return CNAS_XSD_IsUeSupportedChannel_BandClass_5(usChannel);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_12
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_12(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_239)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_13
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_13(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1399)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_14
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_14(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_1299)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsUeSupportedChannel_BandClass_15
 ��������  : �жϸ�Ƶ���Ƿ����ƶ��ն���֧�ֵĴ����б���
 �������  : VOS_UINT16                          usChannel
 �������  : ��

 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsUeSupportedChannel_BandClass_15(
    VOS_UINT16                          usChannel
)
{
    if (usChannel <= CNAS_PRL_CDMA_CHANNEL_RANGE_899)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_SaveRedirectionInfo
 ��������  : Save the redirection info from CAS
 �������  : pstCasRedirInfo-----the redirection info from CAS
 �������  : NONE
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 26/12/2014
    ��    ��   : w00176964
    �޸�����   : Create

*****************************************************************************/
VOS_VOID CNAS_XSD_SaveRedirectionInfo(
    CNAS_CAS_1X_REDIRECTION_INFO_STRU  *pstCasRedirInfo
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstXsdRedirInfo = VOS_NULL_PTR;
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSys = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_ID_STRU          stSysId;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stSrcFreqInfo;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stDstFreqInfo;
    VOS_UINT8                           i;

    pstXsdRedirInfo     = CNAS_XSD_GetRedirectionInfoAddr();

    NAS_MEM_SET_S(&stSysId, sizeof(stSysId), 0x0, sizeof(stSysId));
    NAS_MEM_SET_S(&stSrcFreqInfo, sizeof(stSrcFreqInfo), 0x0, sizeof(stSrcFreqInfo));
    NAS_MEM_SET_S(&stDstFreqInfo, sizeof(stDstFreqInfo), 0x0, sizeof(stDstFreqInfo));

    stSysId.usSid = pstCasRedirInfo->usExpectedSid;
    stSysId.usNid = pstCasRedirInfo->usExpectedNid;

    for (i = 0; i < pstCasRedirInfo->ucChannelNum; i++)
    {
        stSrcFreqInfo.astFreqInfo[i].enBandClass = pstCasRedirInfo->usBandClass;
        stSrcFreqInfo.astFreqInfo[i].usChannel   = pstCasRedirInfo->ausChannelList[i];
    }
    stSrcFreqInfo.ulNum = pstCasRedirInfo->ucChannelNum;

    /* filter out negative freqs */
    CNAS_XSD_RemoveNegativeFreqs(&stSysId, &stSrcFreqInfo, &stDstFreqInfo);



    pstXsdRedirInfo->ucReturnIfFail = pstCasRedirInfo->ucReturnIfFail;
    pstXsdRedirInfo->usExpectSid    = pstCasRedirInfo->usExpectedSid;
    pstXsdRedirInfo->usExpectNid    = pstCasRedirInfo->usExpectedNid;
    pstXsdRedirInfo->ucChanNum      = pstCasRedirInfo->ucChannelNum;

    pstCurCampedSys     = CNAS_XSD_GetCurCampedSysInfo();

    CNAS_XSD_SaveRedirectionOrignalSys(&pstCurCampedSys->stSystem);

    for (i = 0; i < stDstFreqInfo.ulNum; i++)
    {
        pstXsdRedirInfo->astChanInfo[i].stFreqChan      = stDstFreqInfo.astFreqInfo[i];
        pstXsdRedirInfo->astChanInfo[i].enChanStatus    = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
    }

    pstXsdRedirInfo->ucChanNum = (VOS_UINT8)stDstFreqInfo.ulNum;

    pstXsdRedirInfo->usCurScanIndex = 0;

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_TransformMccToBcd
 ��������  : ת��ʮ���Ƶ�MCCΪBCD��ʽ
 �������  : VOS_UINT16                          usMcc
 �������  : ��
 �� �� ֵ  : VOS_UINT32

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_TransformMccToBcd(
    VOS_UINT16                          usMcc
)
{
    /*ת��ԭ��:��λ��ʮλ�Ͱ�λ��ÿһλ��1�������λֵ��9����1Ϊ10����ȡ��λ0    ���ת��ΪBCD��*/
    /*359--> 460 -->0x00000604            */
    VOS_UINT32                          ulBcdMcc;

    if (usMcc > CNAS_XSD_MAX_MCC)
    {
        /*��Чֵ */
        ulBcdMcc = 0xffffffff;
    }
    else
    {
        ulBcdMcc  = 0;

        do
        {
            ulBcdMcc  = (ulBcdMcc << 8)|((usMcc % 10 + 1) % 10);
            usMcc    /= 10;
        }
        while(0 != usMcc);
    }

    return ulBcdMcc;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_TransformImsiToBcd
 ��������  : ת��ʮ���Ƶ�ImsiΪBCD��ʽ
 �������  : VOS_UINT8                           ucImsi
 �������  : ��
 �� �� ֵ  : VOS_UINT16

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16 CNAS_XSD_TransformImsiToBcd(
    VOS_UINT8                           ucImsi
)
{
    /*ת��ԭ��:��λ��ʮλ��ÿһλ��1�������λֵ��9����1Ϊ10����ȡ��λ0    ���ת��ΪBCD��*/
    /*92--> 03 -->0x3000            */
    VOS_UINT16                          usBcdImsi;

    if (ucImsi > CNAS_XSD_MAX_IMSI11_12)
    {
        usBcdImsi = 0xffff;
    }
    else
    {
        usBcdImsi  = 0;

        do
        {
            usBcdImsi  = (VOS_UINT16)((usBcdImsi << 8)|((ucImsi % 10 + 1) % 10));
            ucImsi    /= 10;
        }
        while(0 != ucImsi);
    }

    return usBcdImsi;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_DeleteUsableFreqFormAvoidList
 ��������  : ��avoidƵ���б���ɾ�����õ�Ƶ��
 �������  : CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq
 �������  : ��
 �� �� ֵ  : VOS_VOID

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��27��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_DeleteUsableFreqFormAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList    = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    ucIndex             = 0;

    if (VOS_TRUE == CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(pstFreq, &ucIndex))
    {

        /*ɾ�����������µļ���avoid�б���ۼӼ��� */
        CNAS_XSD_ClearAvoidCountFromAvoidList(ucIndex, CNAS_XSD_AVOID_P_REV_MISMATCH);
        CNAS_XSD_ClearAvoidCountFromAvoidList(ucIndex, CNAS_XSD_AVOID_SID_NID_IS_REJ_BY_PRL);
        CNAS_XSD_ClearAvoidCountFromAvoidList(ucIndex, CNAS_XSD_AVOID_REDIRECTION_FAIL);
        CNAS_XSD_ClearAvoidCountFromAvoidList(ucIndex, CNAS_XSD_AVOID_REDIRECTION_WITH_INVALID_GSRDM);

        if (VOS_TRUE == CNAS_XSD_IsClearFreqInfoOfAvoidList(ucIndex))
        {

            CNAS_XSD_ClearAvoidFreqInfoOfAvoidList(ucIndex);

            /*���avoid�б��в����ڽ��ñ�ǣ���ʾû�б����õ�Ƶ�㣬ֹͣ��ʱ�� */
            if (VOS_FALSE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
            {
                CNAS_XSD_StopTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER);
            }
        }

        CNAS_XSD_LogAvoidFreqList(pstAvoidFreqList);
    }
}


/*****************************************************************************
Function Name   :   CNAS_XSD_ProcCasOhmInd
Description     :   Process the OHM Indication message received from CAS.
                    Send Notification to XREG And MMA, about the current camped system details.
Input parameters:
                    pstMsg       - pointer to OHM Indication message structure.
Outout parameters:  None
Return Value    :   VOS_TRUE

Modify History:
    1)  Date    :   2014-12-27
        Author  :   a00295761
        Modify content :    Create

    2)��    ��   : 2015��1��3��
      ��    ��   : y00245242
      �޸�����   : home SID/NID���ܿ���

    3).��    ��   : 2015��7��9��
      ��    ��   : y00245242
      �޸�����   : iteration 17����
   4).��    ��   :  2015��12��15��
      ��    ��   :  l00324781
      �޸�����   :  CL_MUTIMODE_OPTIMIZE �޸�
*****************************************************************************/

VOS_VOID CNAS_XSD_ProcCasOhmInd(
    CAS_CNAS_1X_OHM_IND_STRU           *pstMsg,
    VOS_UINT32                          ulIsNegSys
)
{
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU   stSysInfo;
    XSD_XREG_SYS_INFO_STRU              stXsdXregSysInfo;
    CNAS_PRL_1X_SYSTEM_STRU             stCurSysInfo;
    VOS_UINT32                          ulIsAvailSys;
    XSD_XREG_SERVICE_STATUS_ENUM_UINT32 enXsdXregSrvSta;
    CNAX_XSD_CAMPED_SYS_INFO_STRU       stCurCampedSysInfo;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8 enRoamingInd;
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCardStatus;
    VOS_UINT8                           ucNoCardModeCfgFlg;

    NAS_MEM_SET_S(&stSysInfo, sizeof(stSysInfo), 0, sizeof(NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU));
    NAS_MEM_SET_S(&stXsdXregSysInfo, sizeof(stXsdXregSysInfo), 0, sizeof(XSD_XREG_SYS_INFO_STRU));
    NAS_MEM_SET_S(&stCurCampedSysInfo, sizeof(stCurCampedSysInfo), 0, sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU));

    stCurSysInfo.usSid              = pstMsg->usSid;
    stCurSysInfo.usNid              = pstMsg->usNid;
    stCurSysInfo.stFreq.enBandClass = pstMsg->usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstMsg->usFreq;

    CNAS_CCB_Set1xSysInfo(pstMsg->usSid,
                          pstMsg->usNid,
                          pstMsg->usBandClass,
                          pstMsg->usFreq);

    NAS_MEM_CPY_S(&(stCurCampedSysInfo.stSystem), sizeof(stCurCampedSysInfo.stSystem), &stCurSysInfo, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    stCurCampedSysInfo.enSysType = CNAS_XSD_SYS_TYPE_PREFERRED;

    ulIsAvailSys = CNAS_XSD_IsCurSystemInAvailSysList(&stCurSysInfo);

    CNAS_XSD_BuildXregSysInfoInd(pstMsg, &stXsdXregSysInfo);

    CNAS_XSD_BuildMsccSysInfoInd(pstMsg, &stSysInfo);

    enCardStatus       = CNAS_CCB_GetCsimCardStatus();
    ucNoCardModeCfgFlg = CNAS_XSD_GetNoCardModeCfgFlg();

    if ((VOS_TRUE                     == ulIsNegSys)
     || ((CNAS_CCB_CARD_STATUS_ABSENT == enCardStatus)
      && (VOS_FALSE                   == ucNoCardModeCfgFlg)))
    {
        enXsdXregSrvSta                 = XSD_XREG_SERVICE_STATUS_LIMITED_SERVICE;
        stSysInfo.enServiceStatus       = NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE;
        stCurCampedSysInfo.enSysType    = CNAS_XSD_SYS_TYPE_NEGATIVE;
        stCurCampedSysInfo.enSrvStatus  = CNAS_XSD_SERVICE_STATUS_LIMITED_SERVICE;
        CNAS_CCB_SetCur1XSrvStatus(CNAS_CCB_SERVICE_STATUS_LIMITED_SERVICE);
    }
    else
    {
        enXsdXregSrvSta                 = XSD_XREG_SERVICE_STATUS_NORMAL_SERVICE;
        stSysInfo.enServiceStatus       = NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE;

        enRoamingInd = CNAS_XSD_GetCurrentSystemRoamingInd(&stCurSysInfo);
        stSysInfo.ucRoamingInd          = enRoamingInd;
        stCurCampedSysInfo.ucRoamingInd = enRoamingInd;
        stCurCampedSysInfo.enSrvStatus  = CNAS_XSD_SERVICE_STATUS_NORMAL_SERVICE;
        CNAS_CCB_SetCur1XSrvStatus(CNAS_CCB_SERVICE_STATUS_NORMAL_SERVICE);
    }

    if (VOS_TRUE == ulIsAvailSys)
    {
        stCurCampedSysInfo.enSysType    = CNAS_XSD_SYS_TYPE_AVAILABLE;
    }

    if (VOS_TRUE == pstMsg->enServiceInfoIncl)
    {
        stCurCampedSysInfo.ulMcc                  = CNAS_XSD_TransformMccToBcd(pstMsg->stServiceInfo.usMcc);
        stCurCampedSysInfo.usImsi11_12            = CNAS_XSD_TransformImsiToBcd(pstMsg->stServiceInfo.ucImsi11_12);
        stSysInfo.stServiceInfo.ulMcc             = CNAS_XSD_TransformMccToBcd(pstMsg->stServiceInfo.usMcc);
        stSysInfo.stServiceInfo.usImsi11_12       = CNAS_XSD_TransformImsiToBcd(pstMsg->stServiceInfo.ucImsi11_12);

        CNAS_CCB_SetConcurrentSupportedFlag(pstMsg->stServiceInfo.ucConcurrentSupported);
    }

    stSysInfo.en1xPriClass = CNAS_XSD_GetCurrentSystemPriClass(&stCurCampedSysInfo.stSystem, MSCC_XSD_SYS_TYPE_CDMA2000_1X);
    stSysInfo.enAIPriClass = CNAS_XSD_GetCurrentSystemPriClass(&stCurCampedSysInfo.stSystem, MSCC_XSD_SYS_TYPE_CDMA2000_AI);

    stCurCampedSysInfo.ucCampOnFlag = VOS_TRUE;

    /* ��XREGģ��ת��ID_XSD_XREG_SYS_INFO_IND��Ϣ */
    CNAS_XSD_SndXregSysInfoInd(enXsdXregSrvSta, &stXsdXregSysInfo);

    /* ��MSCC����System srv Info��Ϣ */
    CNAS_XSD_SndMsccSysSrvInfoInd(&stSysInfo);

    CNAS_XSD_SndMsccSidNidInd(stCurSysInfo.usSid, stCurSysInfo.usNid);

    CNAS_XSD_UpdateCurCampedSysInfo(&stCurCampedSysInfo);

    /* ����Э��ʹ�ð汾 */
    CNAS_CCB_SetPRevInUse(pstMsg->ucPRevInUse);

    /* �������negativeϵͳ�������MRU�Լ��汾�� */
    if (VOS_FALSE == ulIsNegSys)
    {
        /* ����Ƿ�negativeϵͳ������MRU[0] */
        CNAS_XSD_UpdateMru0(&stCurSysInfo);

        CNAS_XSD_DeleteAcqSuccFreqOfAvoidList(&(stCurSysInfo.stFreq));
    }

    /* ˢ�½�������ʼϵͳ */
    if (VOS_TRUE == CNAS_XSD_IsEmcCallOriginalSysExist())
    {
        CNAS_XSD_SaveEmcCallOriginalSys(&stCurSysInfo);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateReturnCauseValue
 ��������  : ����returnCause
 �������  : usSyncFailChanNum ------------------ͬ��ʧ�ܵ�Ƶ�����
             pstSyncFailChanList ------------ ͬ��ʧ�ܵ�Ƶ���б�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��13��
   ��    ��   : m00312079
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateReturnCauseValue(
    VOS_UINT16                          usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU    *pstSyncFailChanList
)
{
    CNAS_CAS_1X_SYS_SRCH_FAIL_REASON_ENUM_UINT16            enFailReason;
    VOS_UINT16                                              i;

    for (i = 0; i < usSyncFailChanNum; i++)
    {
        enFailReason          = pstSyncFailChanList[i].enFailReason;

        if (CNAS_CAS_1X_SYS_SRCH_SYNC_FAIL_FREQ_SRCH_FAIL == enFailReason)
        {
            CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_SYSTEM_NOT_ACQ);
        }
        else if (CNAS_CAS_1X_SYS_SRCH_SYNC_FAIL_PROTO_MISMATCH == enFailReason)
        {
            CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_PROTOCOL_MISMATCH);
        }
        else
        {
            /* Do noting */
        }
    }

    return;

}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurrentSystemRoamingInd
 ��������  : ��ȡ��ǰϵͳ������ָʾֵ
 �������  : CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
 �������  : ��
 �� �� ֵ  : CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8 -- ����ָʾֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��2��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified

*****************************************************************************/
CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8 CNAS_XSD_GetCurrentSystemRoamingInd(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;
    CNAS_PRL_SYS_ROAMING_IND_ENUM_UINT8                     enRoamingInd;
    VOS_UINT8                                               ucHomeSidNidFlg;

    ucHomeSidNidFlg = CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo);

    if ( (VOS_FALSE == CNAS_CCB_GetHomeSidNidDependOnPrlFlg())
      && (VOS_TRUE == ucHomeSidNidFlg) )
    {
        return (VOS_UINT8)CNAS_PRL_SYS_ROAMING_STATUS_OFF;
    }

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));
    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    if (0 == stGeoListInfo.ucGeoNum)
    {
        /* ��GEO������һ��availableϵͳ������PRLͷ��Ϣ�е�����ָʾ */
        return CNAS_PRL_GetPrlHeaderInfoAddr()->enDefRoamInd;
    }

    enRoamingInd = CNAS_PRL_GetRoamingIndInMatchedGeolist(pstCurSysInfo, &stGeoListInfo);

    if (VOS_TRUE == ucHomeSidNidFlg)
    {
        enRoamingInd = (VOS_UINT8)CNAS_PRL_SYS_ROAMING_STATUS_OFF;
    }

    return enRoamingInd;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RemoveNegativeFreqs
 ��������  : ���ݵ�ǰ�����ϵͳ�Լ�Ƶ���б�,����negative��Ƶ��
 �������  : pstSysId -- �����ϵͳID
             pstSrcFreqInfo----ԭʼ��Ƶ����Ϣ
 �������  : pstDstFreqInfo----����negative���Ƶ����Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��15��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��7��2��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 modified

*****************************************************************************/
VOS_VOID CNAS_XSD_RemoveNegativeFreqs(
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstSysId,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU    *pstSrcFreqInfo,
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU    *pstDstFreqInfo
)
{
    CNAS_PRL_1X_SYSTEM_STRU             stSysInfo;
    VOS_UINT32                          i;
    VOS_UINT32                          ulIsNegSys;

    NAS_MEM_SET_S(&stSysInfo, sizeof(stSysInfo), 0x0, sizeof(stSysInfo));
    stSysInfo.usSid = pstSysId->usSid;
    stSysInfo.usNid = pstSysId->usNid;

    /* SID+NIDΪͨ�����ǰϵͳ��home sid/nid list������Ҫ����negativeƵ�� */
    if ((CNAS_PRL_WILDCARD_SID == pstSysId->usSid)
     && (CNAS_PRL_WILDCARD_NID == pstSysId->usNid))
    {
        NAS_MEM_CPY_S(pstDstFreqInfo, sizeof(CNAS_PRL_ACQ_REC_FREQ_INFO_STRU), pstSrcFreqInfo, sizeof(CNAS_PRL_ACQ_REC_FREQ_INFO_STRU));

        return;
    }

    for (i = 0; i < pstSrcFreqInfo->ulNum; i++)
    {
        stSysInfo.stFreq = pstSrcFreqInfo->astFreqInfo[i];
        stSysInfo.usSid  = pstSysId->usSid;
        stSysInfo.usNid  = pstSysId->usNid;

        ulIsNegSys = CNAS_XSD_Is1xSysNegative(&stSysInfo, VOS_FALSE, 0);

        if ((VOS_TRUE  == CNAS_XSD_GetRedirectionInfoAddr()->ucIsEmcRedir)
         || (VOS_FALSE == ulIsNegSys))
        {
            pstDstFreqInfo->astFreqInfo[pstDstFreqInfo->ulNum] = pstSrcFreqInfo->astFreqInfo[i];

            (pstDstFreqInfo->ulNum)++;
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2k1xSysType
 ��������  : �鿴��ǰ��1xϵͳ��GEO�е�ƥ�����ȼ�,��ǰsys typeΪcdma2K_1X
 �������  : pstCurSysInfo -- ��ǰ�ѵ���ϵͳ��Ϣ
             ����CDMA2000_1x��sys type,pri class��1xϵͳ���ڵ����ȼ�,��
             1Xϵͳ��¼֮�����HRPD��ϵͳ,��1Xϵͳ��������ȼ�Ϊ׼;
             ����CDMA2000_AI��sys type,pri class��1xϵͳ���ڵľ������ȼ�,��
             1Xϵͳ��¼֮����ָ������ȼ���HRPD��ϵͳ,1Xϵͳ�����ȼ�ҲҪ�ݼ�;
 �������  : penMatchPrio        -----ƥ������ȼ�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��8��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2k1xSysType(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_MATCH_PRIO_LVL_ENUM_UINT8                  *penMatchPrio
)
{
    VOS_UINT16                                              i;
    VOS_UINT8                                               ucSysPrioLvl;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;
    VOS_UINT16                                              ucMostMatchIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;

    *penMatchPrio   = CNAS_PRL_1X_MATCH_PRIO_LEVLE_NULL;
    ucSysPrioLvl    = 0;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));
    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    if (0 == stGeoListInfo.ucGeoNum)
    {
        return;
    }

    /* ��GEO list���ҳ���ƥ���GEO */
    pstMostMatchGeoInfo = CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(pstCurSysInfo, &stGeoListInfo);

    /* ����ƥ���GEO�л�ȡPRL������ƥ���ϵͳ��¼���� */
    enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstCurSysInfo, pstMostMatchGeoInfo, &ucMostMatchIndex);

    /* ��ƥ�� */
    if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enSysMatchLvl)
    {
        return;
    }

    /* ������ȼ���¼ֱ�ӷ��� */
    if (ucMostMatchIndex == pstMostMatchGeoInfo->usGeoFirstSysRecIndex)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_0;

        return;
    }

    for (i = (pstMostMatchGeoInfo->usGeoFirstSysRecIndex); i <= ucMostMatchIndex; i++)
    {
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(i);

        if ((VOS_NULL_PTR   == pstSysRecord)
         || (VOS_FALSE      == pstSysRecord->ucSysRecValid))
         {
            continue;
        }

        if (CNAS_PRL_RELATIVE_PRI_MORE == pstSysRecord->enPriInd)
        {
            ucSysPrioLvl++;

            /* ����more���ȼ���ϵͳ��¼,PRIO����,�����ǰ��Ϊmore�Ļ�HRPD��ϵͳ,���ȼ��ݼ�һ�� */
            if ((i                              == ucMostMatchIndex)
             || (CNAS_PRL_SYS_RECORD_TYPE_HRPD  == pstSysRecord->enRecordType))
            {
                ucSysPrioLvl--;
            }
        }
    }

    if (0 == ucSysPrioLvl)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_0;
    }
    else if (1 == ucSysPrioLvl)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_1;
    }
    else
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_OTHER;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2kAISysType
 ��������  : �鿴��ǰ��1xϵͳ��GEO�е�ƥ�����ȼ�,��ǰsys typeΪCDMA2K_ai
 �������  : pstCurSysInfo -- ��ǰ�ѵ���ϵͳ��Ϣ
             ����CDMA2000_1x��sys type,pri class��1xϵͳ���ڵ����ȼ�,��
             1Xϵͳ��¼֮�����HRPD��ϵͳ,��1Xϵͳ��������ȼ�Ϊ׼;
             ����CDMA2000_AI��sys type,pri class��1xϵͳ���ڵľ������ȼ�,��
             1Xϵͳ��¼֮����ָ������ȼ���HRPD��ϵͳ,1Xϵͳ�����ȼ�ҲҪ�ݼ�;
 �������  : penMatchPrio        -----ƥ������ȼ�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��8��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2kAISysType(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstCurSysInfo,
    CNAS_PRL_1X_MATCH_PRIO_LVL_ENUM_UINT8                  *penMatchPrio
)
{
    VOS_UINT16                                              i;
    VOS_UINT8                                               ucSysPrioLvl;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;
    VOS_UINT16                                              usMostMatchIndex;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enSysMatchLvl;
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMostMatchGeoInfo = VOS_NULL_PTR;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;

    *penMatchPrio   = CNAS_PRL_1X_MATCH_PRIO_LEVLE_NULL;
    ucSysPrioLvl    = 0;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));
    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    if (0 == stGeoListInfo.ucGeoNum)
    {
        return;
    }

    /* ��GEO list���ҳ���ƥ���GEO */
    pstMostMatchGeoInfo = CNAS_PRL_GetMostMatched1xGeoFrom1xGeoList(pstCurSysInfo, &stGeoListInfo);

    /* ����ƥ���GEO�л�ȡPRL������ƥ���ϵͳ��¼���� */
    enSysMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstCurSysInfo, pstMostMatchGeoInfo, &usMostMatchIndex);

    /* ��ƥ�� */
    if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enSysMatchLvl)
    {
        return;
    }

    /* ������ȼ���¼ֱ�ӷ��� */
    if (usMostMatchIndex == pstMostMatchGeoInfo->usGeoFirstSysRecIndex)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_0;

        return;
    }

    for (i = (pstMostMatchGeoInfo->usGeoFirstSysRecIndex); i <= usMostMatchIndex; i++)
    {
        pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(i);

        if ((VOS_NULL_PTR   == pstSysRecord)
         || (VOS_FALSE      == pstSysRecord->ucSysRecValid))
        {
            continue;
        }

        if (CNAS_PRL_RELATIVE_PRI_MORE == pstSysRecord->enPriInd)
        {
            ucSysPrioLvl++;

            /* ����more���ȼ���ϵͳ��¼,PRIO����,�����ǰ��Ϊmore��ϵͳ,���ȼ��ݼ�һ�� */
            if (i == usMostMatchIndex)
            {
                ucSysPrioLvl--;
            }
        }
    }

    if (0 == ucSysPrioLvl)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_0;
    }
    else if (1 == ucSysPrioLvl)
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_1;
    }
    else
    {
        *penMatchPrio = CNAS_PRL_1X_MATCH_PRIO_LEVLE_OTHER;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurrentSystemPriClass
 ��������  : ��ȡ��ǰϵͳ��PRI CLASS
 �������  : enSysType
 �������  : ��
 �� �� ֵ  : NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8 -- PRI CLASS
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 7/4/2015
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8 CNAS_XSD_GetCurrentSystemPriClass(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    MSCC_XSD_SYS_TYPE_ENUM_UINT8        enSysType
)
{
    NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8                           enPriClass;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                         stGeoListInfo;
    CNAS_PRL_1X_MATCH_PRIO_LVL_ENUM_UINT8                       enMatchPrio;

    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    enMatchPrio   = CNAS_PRL_1X_MATCH_PRIO_LEVLE_NULL;

    if (MSCC_XSD_SYS_TYPE_CDMA2000_AI == enSysType)
    {
        CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2kAISysType(pstCurSysInfo, &enMatchPrio);
    }
    else
    {
        CNAS_PRL_GetCur1xSysMatchPrioInGeoWithCdma2k1xSysType(pstCurSysInfo, &enMatchPrio);
    }

    if (CNAS_PRL_1X_MATCH_PRIO_LEVLE_0 == enMatchPrio)
    {
        enPriClass = NAS_MSCC_PIF_PRI_CLASS_HOME;
    }
    else if (CNAS_PRL_1X_MATCH_PRIO_LEVLE_1 == enMatchPrio)
    {
        enPriClass = NAS_MSCC_PIF_PRI_CLASS_PREF;
    }
    else
    {
        enPriClass = NAS_MSCC_PIF_PRI_CLASS_ANY;
    }

    return enPriClass;
}




VOS_VOID CNAS_XSD_StopAllTimerExceptSpecifiedTimerId(
    VOS_UINT32                          ulTimerId
)
{
    CNAS_TIMER_CTX_STRU                *pstTimerCtx = VOS_NULL_PTR;
    VOS_UINT8                           i;
    CNAS_MNTN_TIMER_INFO_STRU           stMntnTimerInfo;

    pstTimerCtx = CNAS_GetTimerCtxAddr();

    for (i = 0; i < CNAS_MAX_TIMER_RUNNING_NUM; i++)
    {
        if ((CNAS_TIMER_STATUS_RUNNING   == pstTimerCtx->enTimerStatus)
         && (UEPS_PID_XSD                == pstTimerCtx->ulPid)
         && (ulTimerId                   != pstTimerCtx->ulTimerId))
        {
            /* ����ʱ���ľ��Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
            if (VOS_NULL_PTR != pstTimerCtx->pTimerHandle)
            {
                /* ��ǰtimer�������У���ֹͣ�� */
                if (VOS_OK != VOS_StopRelTimer(&(pstTimerCtx->pTimerHandle)))
                {
                    /* ֹͣ��ʱ��ʧ�ܣ���ӡ������Ϣ */
                    CNAS_ERROR_LOG1(UEPS_PID_XSD, "CNAS_StopTimer: start timer is failure!", pstTimerCtx->ulTimerId);

                    pstTimerCtx++;

                    continue;
                }

                /* ���timerֹͣ��Ϣ */
                stMntnTimerInfo.ulParam    = pstTimerCtx->ulParam;
                stMntnTimerInfo.ulTimerId  = pstTimerCtx->ulTimerId;
                stMntnTimerInfo.ulTimerLen = 0;
                stMntnTimerInfo.enTimerAct = CNAS_MNTN_TIMER_ACTION_STOP;
                CNAS_MNTN_TraceTimerMsg(UEPS_PID_XSD, &stMntnTimerInfo);
            }

            /* ���timer���е�CTX��Ϣ */
            pstTimerCtx->pTimerHandle  = VOS_NULL_PTR;
            pstTimerCtx->ulParam       = 0;
            pstTimerCtx->enTimerStatus = CNAS_TIMER_STATUS_STOP;
            pstTimerCtx->ulTimerId     = 0;
            pstTimerCtx->ulPid         = 0;
        }

        pstTimerCtx++;
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsAddNegSysInAvoidList
 ��������  : ��ȡ�Ƿ����neg sys��avoidƵ���б�
 �������  :

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��5��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsAddInAvoidList(
    CNAS_XSD_AVOID_REASON_ENUM_UINT8                        enReason
)
{
    switch(enReason)
    {
        case CNAS_XSD_AVOID_SID_NID_IS_REJ_BY_PRL:
            return (CNAS_XSD_Get1xSysAcqNvimConfig()->stAddAvoidListCfg.ucIsNegSysAdd);

        default:
            return VOS_FALSE;
    }

}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RegisterRrmResourceNtf
 ��������  : ������RRM����ע����Ϣ��RF�ָ�����
 �������  : RRM_PS_TASK_TYPE_ENUM_UINT16
             enRrmTaskType : ע�����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_RegisterRrmResourceNtf(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
    /* ����ע����Ϣ */
    CNAS_XSD_SndRrmRegisterInd(enRrmTaskType);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_DeRegisterRrmResourceNtf
 ��������  : ������RRM����ȥע����Ϣ��ȡ��RF�ָ�����
 �������  : RRM_PS_TASK_TYPE_ENUM_UINT16
             enRrmTaskType : ע�����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_DeRegisterRrmResourceNtf(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
)
{
    /* ����ȥע����Ϣ */
    CNAS_XSD_SndRrmDeRegisterInd(enRrmTaskType);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_ConvertSrvTypeToSessionType
 ��������  : ����������ת������Ӧ��Session����
 �������  : ҵ������
 �������  : ��
 �� �� ֵ  : ��Ӧ��Session����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : w00242748ʱ
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16 CNAS_XSD_ConvertSrvTypeToSessionType(
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType
)
{
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType;

    enSessionType = NAS_MSCC_PIF_SRV_TYPE_BUTT;

    switch (enSrvType)
    {
        case NAS_MSCC_PIF_SRV_TYPE_CS_MO_NORMAL_CALL :
        case NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL :
            enSessionType = CNAS_CAS_1X_SESSION_TYPE_CS_CALL;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_PS_CONVERSAT_CALL :
        case NAS_MSCC_PIF_SRV_TYPE_PS_STREAM_CALL :
        case NAS_MSCC_PIF_SRV_TYPE_PS_INTERACT_CALL :
        case NAS_MSCC_PIF_SRV_TYPE_PS_BACKGROUND_CALL :
        case NAS_MSCC_PIF_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL :
            enSessionType = CNAS_CAS_1X_SESSION_TYPE_PS_CALL;
            break;

        case NAS_MSCC_PIF_SRV_TYPE_CS_MO_SMS :
            enSessionType = CNAS_CAS_1X_SESSION_TYPE_SMS;
            break;

        default:
            enSessionType = NAS_MSCC_PIF_SRV_TYPE_BUTT;
            break;
    }

    return enSessionType;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsSidInOperLockWhiteSidList
 ��������  : �ж�SID�Ƿ��ڰ�������
 �������  : usSid
 �������  : ��
 �� �� ֵ  : VOS_TRUE   ��ʾ�ڰ�������
             VOS_FALSE  ��ʾ���ڰ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsSidInOperLockSysWhiteList(
    VOS_UINT16                          usSid
)
{
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstOperLockSysWhiteList = VOS_NULL_PTR;
    CNAS_CCB_SYS_INFO_STRU                                 *pstSysInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulWhiteSysNum;

    pstOperLockSysWhiteList = CNAS_CCB_GetOperLockSysWhiteList();

    /* �����������disable��Ĭ��ϵͳ�ڰ������� */
    if (VOS_FALSE == pstOperLockSysWhiteList->ucEnable)
    {
        return VOS_TRUE;
    }

    ulWhiteSysNum = (VOS_UINT32)CNAS_MIN(pstOperLockSysWhiteList->usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM);

    for (i = 0; i < ulWhiteSysNum; i++)
    {
        pstSysInfo = &(pstOperLockSysWhiteList->astSysInfo[i]);

        if ( (pstSysInfo->usStartSid <= usSid)
          && (usSid <= pstSysInfo->usEndSid) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsMccInOperLockWhiteSidList
 ��������  : �ж�MCC�Ƿ��ڰ�������
 �������  : usSid
 �������  : ��
 �� �� ֵ  : VOS_TRUE   ��ʾ�ڰ�������
             VOS_FALSE  ��ʾ���ڰ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsMccInOperLockSysWhiteList(
    VOS_UINT32                          ulMcc
)
{
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstOperLockSysWhiteList = VOS_NULL_PTR;
    CNAS_CCB_SYS_INFO_STRU                                 *pstSysInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstOperLockSysWhiteList = CNAS_CCB_GetOperLockSysWhiteList();

    /* �����������disable��Ĭ��ϵͳ�ڰ������� */
    if (VOS_FALSE == pstOperLockSysWhiteList->ucEnable)
    {
        return VOS_TRUE;
    }

    for (i = 0; i < CNAS_MIN(pstOperLockSysWhiteList->usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM); i++)
    {
        pstSysInfo = &(pstOperLockSysWhiteList->astSysInfo[i]);

        if ( pstSysInfo->ulMcc == ulMcc )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsCurSysInSysWhiteList
 ��������  : �жϵ�ǰϵͳ�Ƿ���ϵͳ��������
 �������  : pstCurSysInfo -- ��ǰϵͳ��Ϣ
             ulMccValidFlg -- �Ƿ���Ҫcheck MCC
             usMcc         -- MCC
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��ʾ�ڰ�������
             VOS_FALSE --  ��ʾ���ڰ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��1��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSysInSysWhiteList
(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    VOS_UINT32                          ulMccValidFlg,
    VOS_UINT16                          usMcc
)
{
    /* �����ǰϵͳSID��SID�������У�����Ϊϵͳ�ڰ������� */
    if (VOS_TRUE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstCurSysInfo->usSid))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == ulMccValidFlg)
    {
        /* ���MCC�ڰ������У�����Ϊ��һ���ʺ�פ����ϵͳ */
        if (VOS_TRUE == CNAS_XSD_IsMccInOperLockSysWhiteList(CNAS_XSD_TransformMccToBcd(usMcc)))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RefreshPriLvlInSysRecord
 ��������  : ˢ��ϵͳ���е����ȼ��ȼ�
 �������  : usTmpSysRecNum - ϵͳ���¼����
             pstSysRecord - ϵͳ���¼
             usDistance - ��Ҫ���ӵ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_ReducePriLvlInSysRecordList(
    VOS_UINT16                          usTmpSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord,
    VOS_UINT16                          usReducePriLvl
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstTmpSysRecord = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstTmpSysRecord = pstSysRecord;

    for (i = 0; i < (VOS_UINT32)usTmpSysRecNum; i++)
    {
        pstTmpSysRecord->usPriLvl += usReducePriLvl;

        pstTmpSysRecord++;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildSysRecordListBasedOnGeo
 ��������  : ����GEO����Ϣ������ϵͳ��¼��(�������豣֤��
             pstSysRecord������ڴ�����Ǹ�GEO�У�ϵͳ��¼��ĸ���)
 �������  : pstMatchedGeo - GEO��Ϣ
 �������  : pstSysRecord - ϵͳ��¼��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildSysRecordListBasedOnGeo(
    CNAS_PRL_MATCHED_GEO_INFO_STRU     *pstMatchedGeo,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo         = VOS_NULL_PTR;
    VOS_UINT16                          usGeoFirstSysRecIndex;
    VOS_UINT16                          usSysRecNum;

    pstPrlSysInfo         = CNAS_PRL_GetPrlSysInfoAddr();
    usSysRecNum           = pstMatchedGeo->usGeoSysRecNum;
    usGeoFirstSysRecIndex = pstMatchedGeo->usGeoFirstSysRecIndex;

    NAS_MEM_CPY_S(pstSysRecord, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*usSysRecNum, pstPrlSysInfo->pstSysRecord + usGeoFirstSysRecIndex, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*usSysRecNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddGeoIntoCompsiteGeo
 ��������  : ��ĳ��GEO���뵽ƴ�ӵ�GEO�У�ƴ��GEO��ϵͳ��¼�������Լ���Ӧ��ϵͳ��¼��ʾ
            (�ڴ��ڸú��������룬���ͷ��ɵ������ͷ�)
 �������  : pstMatchedGeo - ��Ҫƴ�ӵ�GEO
 �������  : pusSysRecNum - ϵͳ��¼����
             ppstSysRecord - ϵͳ��¼�б�
             pusPriLvl - ƴ�Ӻ���ƥ��ϵͳ��Ӧ�����ȼ��ȼ�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��26��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_UINT32 CNAS_XSD_AddGeoIntoCompsiteGeo(
    CNAS_PRL_MATCHED_GEO_INFO_STRU     *pstMatchedGeo,
    VOS_UINT16                         *pusSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecordList,
    VOS_UINT16                         *pusPriLvl
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstNewSysRecordList = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstCurSysRecordList = VOS_NULL_PTR;
    VOS_UINT16                          usNewSysRecNum;
    VOS_UINT16                          usMostMatchedIndex;
    VOS_UINT16                          usNewSysRecPriLvl;
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT32                          k;

    usMostMatchedIndex    = pstMatchedGeo->usMostMatchedIndex;
    usNewSysRecPriLvl     = (CNAS_PRL_GetPrlSysInfoAddr()->pstSysRecord + usMostMatchedIndex)->usPriLvl;
    usNewSysRecNum        = pstMatchedGeo->usGeoSysRecNum;

    /* ��GEO�б��е�ϵͳ��¼����廯����ÿ����¼���б���ʽ��ʾ */
    pstNewSysRecordList   = (CNAS_PRL_EXT_SYS_RECORD_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*usNewSysRecNum);
    if (VOS_NULL_PTR == pstNewSysRecordList)
    {
        return VOS_FALSE;
    }

    CNAS_XSD_BuildSysRecordListBasedOnGeo(pstMatchedGeo, pstNewSysRecordList);

    /* ����ƴ�ӳɵ�GEO�б���һ�� */
    pstCurSysRecordList   = (CNAS_PRL_EXT_SYS_RECORD_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*(*pusSysRecNum));
    if (VOS_NULL_PTR == pstCurSysRecordList)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstNewSysRecordList);
        return VOS_FALSE;
    }

    NAS_MEM_CPY_S(pstCurSysRecordList,
                  sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*(*pusSysRecNum),
                  pstSysRecordList,
                  sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU)*(*pusSysRecNum));

    if (usNewSysRecPriLvl > *pusPriLvl)
    {
        CNAS_XSD_ReducePriLvlInSysRecordList(*pusSysRecNum, pstCurSysRecordList, usNewSysRecPriLvl - *pusPriLvl);

        *pusPriLvl = usNewSysRecPriLvl;
    }
    else
    {
        CNAS_XSD_ReducePriLvlInSysRecordList(usNewSysRecNum, pstNewSysRecordList, *pusPriLvl - usNewSysRecPriLvl);
    }

    /* �ϲ�����GEO�б� */
    for (i = 0, j = 0, k = 0; (i < (VOS_UINT32)*pusSysRecNum) && (j < (VOS_UINT32)usNewSysRecNum); )
    {
        /* �ж���GEO��ϵͳ���ȼ��뵱ǰ��ƴ��GEO��ϵͳ�����ȼ����бȽϣ������ȼ���ֵ��С�����˳������ */
        if ( (pstCurSysRecordList+i)->usPriLvl > (pstNewSysRecordList+j)->usPriLvl )
        {
            NAS_MEM_CPY_S((pstSysRecordList + k), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU), (pstNewSysRecordList + j), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
            k++;
            j++;
        }
        else
        {
            NAS_MEM_CPY_S((pstSysRecordList + k), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU), (pstCurSysRecordList + i), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
            k++;
            i++;
        }
    }

    /* ���б���ʣ��δ�����ϵͳ��¼�������� */
    while (i != (VOS_UINT32)*pusSysRecNum)
    {
        NAS_MEM_CPY_S((pstSysRecordList + k), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU), (pstCurSysRecordList + i), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
        k++;
        i++;
    }

    while (j != (VOS_UINT32)usNewSysRecNum)
    {
        NAS_MEM_CPY_S((pstSysRecordList + k), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU), (pstNewSysRecordList + j), sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
        k++;
        j++;
    }

    PS_MEM_FREE(UEPS_PID_XSD, pstNewSysRecordList);
    PS_MEM_FREE(UEPS_PID_XSD, pstCurSysRecordList);



    *pusSysRecNum   = *pusSysRecNum + usNewSysRecNum;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildCompsiteGeoFromMostMatchedGeoList
 ��������  : ��������ƥ���GEOƴ�ӣ�(�ڴ��ڸú��������룬���ͷ��ɵ������ͷ�)
 �������  : pstMatchedGeoList - ��Ҫƴ�ӵ�GEO�ļ���
 �������  : pusSysRecNum - ϵͳ��¼����
             ppstSysRecord - ϵͳ��¼�б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildCompsiteGeoFromMostMatchedGeoList(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMatchedGeoList,
    VOS_UINT16                                             *pusSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecordList,
    VOS_UINT16                                             *pusMorePrefSysNum
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          j;
    VOS_UINT16                          usPriLvl;

    if (0 == pstMatchedGeoList->ucGeoNum)
    {
        return;
    }

    usPriLvl = 0;

    *pusSysRecNum        = pstMatchedGeoList->astGeoInfoList[0].usGeoSysRecNum;

    usPriLvl             = (CNAS_PRL_GetPrlSysInfoAddr()->pstSysRecord + pstMatchedGeoList->astGeoInfoList[0].usMostMatchedIndex)->usPriLvl;

    CNAS_XSD_BuildSysRecordListBasedOnGeo(&(pstMatchedGeoList->astGeoInfoList[0]), pstSysRecordList);

    for (i = 1; i < pstMatchedGeoList->ucGeoNum;i++)
    {
        CNAS_XSD_AddGeoIntoCompsiteGeo(&(pstMatchedGeoList->astGeoInfoList[i]), pusSysRecNum, pstSysRecordList, &usPriLvl);
    }

    for (j = 0; j < *pusSysRecNum; j++)
    {
        if ((pstSysRecordList + j)->usPriLvl < usPriLvl)
        {
            (*pusMorePrefSysNum)++;
        }
        else
        {
            break;
        }
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildGeoListBasedOnSysRecord
 ��������  : ����ϵͳ��¼��Ϣ��ȡ��Ӧ��GEO
 �������  : pstPrlSysInfo - PRL����ϵͳ���¼
 �������  : pstGeoList - GEO�б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildGeoListBasedOnSysRecord(
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo,
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoList
)
{
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord = VOS_NULL_PTR;
    VOS_UINT16                          i;
    VOS_UINT16                          j;
    VOS_UINT16                          usGeoNum;

    /* �ú��������ڲ����ã������߱�֤pstPrlSysInfo��ΪVOS_NULL_PTR */
    pstSysRecord   = pstPrlSysInfo->pstSysRecord;
    usGeoNum       = 0;

    /* ͳ��GEO�ĸ�����Ϊ�˺��������ڴ� */
    for (i = 0; i < pstPrlSysInfo->usSysRecordNum;i++)
    {
        if ( (CNAS_PRL_GEO_REGION_IND_NEW == (pstSysRecord+i)->enGeoInd)
          || (0 == i) )
        {
            usGeoNum++;
        }
    }

    pstGeoList->usGeoNum       = usGeoNum;
    pstGeoList->pstGeoSrchInfo = (CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_XSD_GEO_SRCH_STATUS_INFO_STRU)*usGeoNum);

    if (VOS_NULL_PTR == pstGeoList->pstGeoSrchInfo)
    {
        pstGeoList->usGeoNum       = 0;
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_BuildGeoListBasedOnSysRecord: mem alloc fail");

        return;
    }

    /* ���Ѿ�������ڴ��У����GEO���׵�ַ */
    for (i = 0, j = 0; i < pstPrlSysInfo->usSysRecordNum;i++)
    {
        if ( (CNAS_PRL_GEO_REGION_IND_NEW == (pstSysRecord+i)->enGeoInd)
          || (0 == i) )
        {
            pstGeoList->pstGeoSrchInfo[j].usGeoBeginIndex = i;
            pstGeoList->pstGeoSrchInfo[j].usGeoSrchStatus = VOS_FALSE;
            j++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetGeoListFromPrlSysRecordInfo
 ��������  : ����ϵͳ��¼��Ϣ��ȡ��Ӧ��GEO
 �������  : ��
 �������  : pstGeoList - GEO�б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_GetGeoListFromPrlSysRecordInfo(
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoList
)
{
    CNAS_PRL_SYS_RECORD_INFO_STRU      *pstPrlSysInfo   = VOS_NULL_PTR;

    pstPrlSysInfo         = CNAS_PRL_GetPrlSysInfoAddr();

    CNAS_XSD_BuildGeoListBasedOnSysRecord(pstPrlSysInfo, pstGeoList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_CalcPrlSysRecListTotalFreqNum
 ��������  : ����PRLϵͳ��¼�б���ܵ�Ƶ�������(MCC-MNC��¼�Ļ����÷ֳɶ�����¼����)
 �������  : usSysRecNum-----------ϵͳ��¼�ܸ���
             pstSysRecord----------ϵͳ��¼�б�
 �������  : ��

 �� �� ֵ  : ��ȡ�����ܵ�Ƶ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_XSD_CalcPrlSysRecListTotalFreqNum(
    VOS_UINT16                          usSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usTotalNum;
    VOS_UINT16                          usAcqIndex;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stFreqInfo;
    VOS_UINT8                           ucSidNum;

    usTotalNum  = 0;
    usAcqIndex  = 0;
    ucSidNum    = 0;

    /* ��ǰ�����Ƶ��������ظ���Ŀǰ���������������ظ�����ʱ��Ϊ����ظ��������ر�Ķ� */
    for (i = 0; i < usSysRecNum; i++)
    {

        if (VOS_FALSE == pstSysRecord[i].ucSysRecValid)
        {
            continue;
        }

        if (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 == pstSysRecord[i].enRecordType)
        {
            usAcqIndex = pstSysRecord[i].usAcqIndex;
            pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(usAcqIndex);

            /* ��ָ����б��� */
            if (VOS_NULL_PTR == pstPrlAcqRec)
            {
                continue;
            }

            CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stFreqInfo);

            usTotalNum += (VOS_UINT16)stFreqInfo.ulNum;
        }

        if (CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord[i].enRecordType)
        {
            usAcqIndex = pstSysRecord[i].usAcqIndex;
            pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(usAcqIndex);

            /* ��ָ����б��� */
            if (VOS_NULL_PTR == pstPrlAcqRec)
            {
                continue;
            }

            CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stFreqInfo);

            if ( (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID     == pstSysRecord[i].u.stMccMncId.enMccMncSubType)
              || (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID == pstSysRecord[i].u.stMccMncId.enMccMncSubType) )
            {
                ucSidNum    = pstSysRecord[i].u.stMccMncId.u.stSidNid.ucSidNidNum;
                usTotalNum += (VOS_UINT16)(stFreqInfo.ulNum * ucSidNum);
            }
        }
    }

    return usTotalNum;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsCurSysHomeSystemIndependenceOnPrl
 ��������  : check��ǰ����PRL���е�ϵͳ�Ƿ���home SID/NIDϵͳ
 �������  : pstCurSysInfo -- ��ǰϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   ��ʾ��homeϵͳ
             VOS_FALSE  ��ʾ����homeϵͳ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSysHomeSystemIndependenceOnPrl(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo
)
{
    /* �����PRL���е�ϵͳ���ܵ���homeϵͳ */
    if (VOS_TRUE == CNAS_CCB_GetHomeSidNidDependOnPrlFlg())
    {
        return VOS_FALSE;
    }

    /* ���ϵͳ����home SID/NID list�У�����Ϊ�Ƿ�homeϵͳ */
    if (VOS_FALSE == CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo))
    {
        return VOS_FALSE;
    }

    /* �����ǰhome SID���ڰ������У�����Ϊ����home SID/NIDϵͳ */
    if (VOS_FALSE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstCurSysInfo->usSid))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsCurSystemInAvailSysList
 ��������  : �ж�һ��system�Ƿ���available system list��
 �������  : CNAS_PRL_1X_SYSTEM_STRU            *pstCurSys
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��25��
    ��    ��   : w00176964
    �޸�����   : CDMA Iteration 6:Move the avail system list to the global variables
  3.��    ��   : 2015��7��17��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSystemInAvailSysList(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSys
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;
    VOS_UINT32                                              ulHomeSidNidFlg;

    /* ��ȡ����ƥ���GEO list */
    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_PRL_Get1xSysGeoList(pstCurSys, &stGeoListInfo);

    /* PRL�����ҵ���Ӧ��GEO������Ϊ�Ƿ�availϵͳ */
    if (0 != stGeoListInfo.ucGeoNum)
    {
        return VOS_FALSE;
    }

    /* ��ǰϵͳ���ڰ������У�����Ϊ��NEGϵͳ��Ҳ����availϵͳ */
    if (VOS_FALSE == CNAS_XSD_IsSidInOperLockSysWhiteList(pstCurSys->usSid))
    {
        return VOS_FALSE;
    }

    ulHomeSidNidFlg = CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSys);

    /* ���home sid/nid������PRL������home sid/nidϵͳ�Ļ�������Ϊ�Ƿ�availϵͳ */
    if ( (VOS_FALSE == CNAS_CCB_GetHomeSidNidDependOnPrlFlg())
      && (VOS_TRUE == ulHomeSidNidFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_QuitCallBackMode
 ��������  : �������˳�CallBackģʽ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_QuitCallBackMode( VOS_VOID )
{
    /* �ϱ��˳�CALLBACKģʽNTF */
    CNAS_XSD_SndMsccEmcCallBackInd(NAS_MSCC_PIF_EMC_CALLBACK_MODE_DISABLE);

    /* ��ս����������ɹ���ϵͳ */
    CNAS_XSD_ClearEmcCallOriginalSys();

    /* �����Ƶ����Ƶ����Ϣ */
    CNAS_XSD_ClearEmcCallBackCandidateFreq();

    /* ���CALLBACK״̬ */
    CNAS_XSD_SetEmcState(CNAS_XSD_EMC_STATE_NULL);

    CNAS_XSD_LogCallBackStatusInd(ID_CNAS_XSD_MNTN_LOG_QUIT_CALLBACK_IND);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsCurSysNotSuitableSys
 ��������  : �жϵ�ǰϵͳ�Ƿ���פ��
 �������  : pstCurSysInfo -- ��ǰϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   ��ʾ��not suitableϵͳ������Ϊ��negϵͳ
             VOS_FALSE  ��ʾ��suitableϵͳ������negativeϵͳ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsCurSysNotSuitableSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    VOS_UINT32                          ulMccValidFlg,
    VOS_UINT16                          usMcc
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stGeoListInfo;
    VOS_UINT32                          ulIsNegSys;

    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    if (0 == stGeoListInfo.ucGeoNum)
    {
        if (VOS_FALSE == CNAS_PRL_GetPrefOnlyFlg())
        {
            /* ���prefer onlyΪFALSE����Ҫ�������� */
            return (!CNAS_XSD_IsCurSysInSysWhiteList(pstCurSysInfo, ulMccValidFlg, usMcc));
        }

        /* ���prefer onlyΪTRUE����home SID/NIDϵͳ��Ҫ����PRL������PRL����ϵͳ���ǲ��ʺ�פ����ϵͳ */
        if (VOS_TRUE == CNAS_CCB_GetHomeSidNidDependOnPrlFlg())
        {
            return VOS_TRUE;
        }

        /* ���prefer onlyΪTRUE����home SID/NIDϵͳ������PRL������Ҫ����home SID/NID��� */
    }
    else
    {
        /* home sid/nid������ָʾ��ʶ������enable����disable�����Ὣ��ϵͳָʾ�ɷ�NEG */
        ulIsNegSys = CNAS_PRL_Is1xSysNegativeInPrl(pstCurSysInfo, &stGeoListInfo);

        /* �������negativeϵͳ��check��ǰϵͳ�Ƿ��ڰ������� */
        if (VOS_FALSE == ulIsNegSys)
        {
            return (!CNAS_XSD_IsCurSysInSysWhiteList(pstCurSysInfo, ulMccValidFlg, usMcc));
        }

        /* �����negativeϵͳ������Ҫ����home SID/NID��� */
    }

    /* ���ϵͳ���ڰ������У�����Ϊ��ϵͳ���ʺ�פ�� */
    if (VOS_FALSE == CNAS_XSD_IsCurSysInSysWhiteList(pstCurSysInfo, ulMccValidFlg, usMcc))
    {
        return VOS_TRUE;
    }

    /* �����ǰϵͳ����home SID/NID list�У�����Ϊ��ϵͳ���ʺ�פ�� */
    if (VOS_FALSE == CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_Is1xSysAllowedCampOn
 ��������  : �жϵ�ǰϵͳ�Ƿ���negϵͳ
 �������  : pstCurSysInfo -- ��ǰϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE   ��ʾ��negϵͳ
             VOS_FALSE  ��ʾ����negϵͳ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_Is1xSysNegative(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysInfo,
    VOS_UINT32                          ulMccValidFlg,
    VOS_UINT16                          usMcc
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stGeoListInfo;
    VOS_UINT32                          ulIsNegSys;
    VOS_UINT8                           ucHomeSidNidFlg;

    CNAS_PRL_Get1xSysGeoList(pstCurSysInfo, &stGeoListInfo);

    if (0 == stGeoListInfo.ucGeoNum)
    {
        ulIsNegSys = VOS_FALSE;
    }
    else
    {
        /* home sid/nid������ָʾ��ʶ������enable����disable�����Ὣ��ϵͳָʾ�ɷ�NEG */
        ulIsNegSys      = CNAS_PRL_Is1xSysNegativeInPrl(pstCurSysInfo, &stGeoListInfo);
        ucHomeSidNidFlg = CNAS_PRL_IsCurrentSystemInHomeSidNidList(pstCurSysInfo);

        ulIsNegSys = (VOS_UINT32)((VOS_TRUE == ucHomeSidNidFlg) ? VOS_FALSE : ulIsNegSys);
    }

    if (VOS_FALSE == ulIsNegSys)
    {
        /* ������ڰ������У�����Ϊ��negativeϵͳ */
        if (VOS_FALSE == CNAS_XSD_IsCurSysInSysWhiteList(pstCurSysInfo, ulMccValidFlg, usMcc))
        {
            ulIsNegSys = VOS_TRUE;
        }
    }

    return ulIsNegSys;
}



/*lint -restore */


#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

