/******************************************************************************

                  ��Ȩ���� (C), 2014-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdAvoidStrategy.c
  �� �� ��   : ����
  ��    ��   : x00306642
  ��������   : 2015��01��15��
  ����޸�   :
  ��������   : CNAS��HSDģ��ϵͳ�����avoid list�Ĳ����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��01��15��
    ��    ��   : x00306642
    �޸�����   : Added for HRPD
******************************************************************************/


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsCommonDef.h"
#include "stdlib.h"
#include "CnasHsdSysAcqStrategy.h"
#include "CnasHsdMntn.h"
#include "CnasCcb.h"
#include "CnasPrlApi.h"
#include "CnasHsdAvoidStrategy.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_CNAS_HSD_AVOID_STRATEGY_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT��counterֵ�仯��avoid time */
VOS_UINT8                               g_aucAvoidSETTimeLen[CNAS_HSD_AVOID_SESSION_COUNTER_MAX] =
{
    0, 1, 2, 4, 8, 8, 8
};

/* CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE��counterֵ�仯��avoid time */
VOS_UINT8                               g_aucAvoidMAPFTimeLen[CNAS_HSD_AVOID_PROBE_COUNTER_MAX] =
{
    0, 1, 1, 2, 2, 2
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAvoidTimeLen_With_Counter
 ��������  : ��ȡavoid timerʱ��
 �������  : enAvoidReason -- avoidԭ��ֵ

 �������  : ��
 �� �� ֵ  : ulAvoidTime -- ��ȡ����avoid time
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetAvoidTimeLen_Without_Counter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    VOS_UINT32                          ulAvoidTimeLen;

    switch (enAvoidReason)
    {
        /* Э��CDG130��10.3.5:δ��ȷ���壬����ʹ��60sec */
        case CNAS_HSD_AVOID_PROTOCAL_MISMATCH:
            ulAvoidTimeLen = CNAS_HSD_AVOID_TIME_60_SEC;
            break;

        /* Э��CDG143��5.6.2:����30sec */
        case CNAS_HSD_AVOID_REDIRECTION:
            ulAvoidTimeLen = CNAS_HSD_AVOID_TIME_30_SEC;
            break;

        /* Э��CDG143��5.8.2:����10min */
        case CNAS_HSD_AVOID_SESSION_NEGOTIATION_FAILURE:
            ulAvoidTimeLen = 10 * CNAS_HSD_AVOID_TIME_60_SEC;
            break;

        /* Э��CDG143��5.7.1:����7min */
        case CNAS_HSD_AVOID_PERSISTENCE_TEST_FAILURE:
            ulAvoidTimeLen = 7 * CNAS_HSD_AVOID_TIME_60_SEC;
            break;

        /* Э��CDG143��5.7.4:����10min */
        case CNAS_HSD_AVOID_AUTHEN_OR_BILLING_FAILURE:
            ulAvoidTimeLen = 10 * CNAS_HSD_AVOID_TIME_60_SEC;
            break;

        /* Э��CDG143��5.5.2:����1min */
        case CNAS_HSD_AVOID_FAIL_CONTINUE_THREE_TIMES:
            ulAvoidTimeLen = CNAS_HSD_AVOID_TIME_60_SEC;
            break;

         case CNAS_HSD_AVOID_PREFER_CH_NOT_VALID:
            ulAvoidTimeLen = CNAS_HSD_AVOID_TIME_60_SEC;
            break;
        default:
            ulAvoidTimeLen = 0;
            break;
    }

    return ulAvoidTimeLen;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAvoidTimeLen_Without_Counter
 ��������  : ��ȡavoid timerʱ��
 �������  : enAvoidReason -- avoidԭ��ֵ

 �������  : ��
 �� �� ֵ  : ulAvoidTime -- ��ȡ����avoid time
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetAvoidTimeLen_With_Counter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    VOS_UINT32                          ulAvoidTimeLen;
    VOS_UINT8                           ucCounter;

    ucCounter = CNAS_HSD_GetCounterValue(enAvoidReason);

    switch (enAvoidReason)
    {
        /* Э��CDG143��5.8.1:����counter���ӣ�����ʱ��Ϊ1, 2, 4, 8, 8, 8, 16, 16(min)... */
        case CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT:
            if (ucCounter < CNAS_HSD_AVOID_SESSION_COUNTER_MAX)
            {
                ulAvoidTimeLen = g_aucAvoidSETTimeLen[ucCounter] * CNAS_HSD_AVOID_TIME_60_SEC;
            }
            else
            {
                ulAvoidTimeLen = 16 * CNAS_HSD_AVOID_TIME_60_SEC;
            }
            break;

        /* Э��CDG143��5.7.2b:����counter���ӣ�����ʱ��Ϊ2, 4, 8, 8, 8, 16, 16(min)... */
        case CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE:
            if (ucCounter < CNAS_HSD_AVOID_PROBE_COUNTER_MAX)
            {
                ulAvoidTimeLen = g_aucAvoidMAPFTimeLen[ucCounter] * CNAS_HSD_AVOID_TIME_60_SEC;
            }
            else
            {
                ulAvoidTimeLen = 4 * CNAS_HSD_AVOID_TIME_60_SEC;
            }
            break;

        /* Э��CDG143��5.7.5b:����������������1min */
        case CNAS_HSD_AVOID_BUSY_OR_GENERAL_FAILURE:
            if (ucCounter < CNAS_HSD_AVOID_BUSY_COUNTER_MAX)
            {
                ulAvoidTimeLen = 0;
            }
            else
            {
                ulAvoidTimeLen = 1 * CNAS_HSD_AVOID_TIME_60_SEC;
            }
            break;

        default:
            ulAvoidTimeLen = 0;
    }

    return ulAvoidTimeLen;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_IncreaseAvoidFreqUsedNum
 ��������  : ����avoid��ʹ����ĸ���
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_IncreaseAvoidFreqUsedNum(VOS_VOID)
{
    CNAS_HSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList;

    pstAvoidFreqList = CNAS_HSD_GetAvoidFreqListAddr();
    pstAvoidFreqList->ucAvoidItemUsedNum++;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_DecreaseAvoidFreqUsedNum
 ��������  : ��Сavoid��ʹ����ĸ���
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_DecreaseAvoidFreqUsedNum(VOS_VOID)
{
    CNAS_HSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList;

    pstAvoidFreqList = CNAS_HSD_GetAvoidFreqListAddr();
    pstAvoidFreqList->ucAvoidItemUsedNum--;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_UpdateCounter
 ��������  : ���Ӽ���������ֵ
 �������  : enAvoidReason -- ԭ��ֵ

 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_IncreaseCounter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason,
    UINT8                               ucMaxCounter
)
{
    VOS_UINT8                          *pucCounter;

    pucCounter = CNAS_HSD_GetAvoidFreqListAddr()->aucCounter;

    if (pucCounter[enAvoidReason] < ucMaxCounter)
    {
        pucCounter[enAvoidReason]++;
    }
    else
    {
        pucCounter[enAvoidReason] = ucMaxCounter;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_UpdateCounter
 ��������  : ��������ֵ����
 �������  : enAvoidReason -- ԭ��ֵ

 �������  :
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ClearCounter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    VOS_UINT8                          *pucCounter;

    if (enAvoidReason < CNAS_HSD_AVOID_REASON_MAX)
    {
        pucCounter                = CNAS_HSD_GetAvoidFreqListAddr()->aucCounter;
        pucCounter[enAvoidReason] = 0;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_DecreaseAvoidFreqUsedNum
 ��������  : ��ȡ��������ֵ
 �������  : enAvoidReason -- avoidԭ��ֵ

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_HSD_GetCounterValue(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    return (CNAS_HSD_GetAvoidFreqListAddr()->aucCounter[enAvoidReason]);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_CheckExpiredFreqFromAvoidList
 ��������  : ��鵽�ڵ�Ƶ�㣬�����Ƶ�㵽��, �򽫵��ڵ���Ŀ�ӱ���ɾ��
 �������  : ��

 �������  : ��

 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��01��06��
   ��    ��   : x00306642
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_CheckExpiredFreqFromAvoidList(VOS_VOID)
{
    VOS_UINT32                          ulCurSlice;
    VOS_UINT32                          ulRunSliceNum;
    VOS_UINT8                           ucIndex;
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;

    /* ��ȡ��ǰϵͳ��slice */
    ulCurSlice = CNAS_HSD_GetSystemSlice();

    /* ����avoid�б������е�Ƶ��ĵ���slice */
    for (ucIndex = 0; ucIndex < CNAS_HSD_MAX_AVOID_FREQ_NUM; ucIndex++)
    {
        pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(ucIndex);

        if (CNAS_HSD_AVOID_ITEM_UNUSED == pstAvoidFreqInfo->enUsedFlag)
        {
            continue;
        }

        if (ulCurSlice < pstAvoidFreqInfo->ulStartSlice)
        {
            /* ���Ƿ�ת���� */
            ulRunSliceNum = CNAS_HSD_MAX_SLICE_VALUE - pstAvoidFreqInfo->ulStartSlice + ulCurSlice + 1;
        }
        else
        {
            ulRunSliceNum = ulCurSlice - pstAvoidFreqInfo->ulStartSlice;
        }

        /* ����Ѿ����е�slice��Ŀ���ڵ��ڵ��ڵ�slice��Ŀ��Ҫ����item��avoid list��ɾ�� */
        if (ulRunSliceNum >= pstAvoidFreqInfo->ulExpiredSliceNum)
        {
            CNAS_HSD_DeleteItemFromAvoidList(ucIndex);
            CNAS_HSD_DecreaseAvoidFreqUsedNum();
        }
    }

    /* ���avoid listΪ�գ�ֹͣavoid��ʱ�� */
    if (0 == CNAS_HSD_GetAvoidFreqListUsedNum())
    {
        CNAS_HSD_StopTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER);
    }

    CNAS_HSD_LogAvoidFreqList(CNAS_HSD_GetAvoidFreqListAddr());

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_IsCurFreqAvoided
 ��������  : ��鵱ǰƵ���Ƿ���avoid�б��б���
 �������  : pstFreq -- ������Ƶ����Ϣ

 �������  : ��

 �� �� ֵ  : VOS_TRUE  -- ��ǰƵ�㱻��
             VOS_FALSE -- ��ǰƵ�㲻����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��01��07��
   ��    ��   : x00306642
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsCurFreqAvoided(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    VOS_UINT8                           ucIndex;
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;

    /* ����avoid�б������е�Ƶ�㣬�жϵ�ǰƵ���Ƿ���avoid�б��� */
    for (ucIndex = 0; ucIndex < CNAS_HSD_MAX_AVOID_FREQ_NUM; ucIndex++)
    {
        pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(ucIndex);

        if (CNAS_HSD_AVOID_ITEM_UNUSED == pstAvoidFreqInfo->enUsedFlag)
        {
            continue;
        }

        if (VOS_TRUE == CNAS_PRL_CmpFreqValue(&(pstAvoidFreqInfo->stAvoidFreq), pstFreq))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_DeleteItemFromAvoidList
 ��������  : ��avoid�б���ɾ��Ƶ����Ϣ
 �������  : ucIndex -- ��ɾ����item��index

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_DeleteItemFromAvoidList(
    VOS_UINT8                           ucIndex
)
{
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;

    pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(ucIndex);

    PS_MEM_SET(pstAvoidFreqInfo, 0, sizeof(CNAS_HSD_AVOID_FREQ_INFO_STRU));

    pstAvoidFreqInfo->enUsedFlag = CNAS_HSD_AVOID_ITEM_UNUSED;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAvoidItemFromAvoidList
 ��������  : ����index��avoid list�л�ȡָ����
 �������  : ucIndex -- avoidƵ����Ϣ����

 �������  : ��
 �� �� ֵ  : CNAS_HSD_AVOID_FREQ_INFO_STRU* -- ��ȡ����ָ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_AVOID_FREQ_INFO_STRU* CNAS_HSD_GetAvoidItemFromAvoidList(
    VOS_UINT8                           ucIndex
)
{
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;

    /* ����ָ��������avoidƵ����Ϣ */
    pstAvoidFreqInfo = &(CNAS_HSD_GetAvoidFreqListAddr()->astAvoidFreqInfo[ucIndex]);

    return pstAvoidFreqInfo;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetEmptyItemFormAvoidList
 ��������  : ��avoid list�в���һ��δʹ�õ���
 �������  :

 �������  : pstAvoidFreqInfo -- δʹ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_AVOID_FREQ_INFO_STRU* CNAS_HSD_GetEmptyItemFormAvoidList(VOS_VOID)
{
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulFlag;

    ulFlag = VOS_FALSE;

    for (ucIndex = 0; ucIndex < CNAS_HSD_MAX_AVOID_FREQ_NUM; ucIndex++)
    {
        pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(ucIndex);

        /* ����һ��δ��ʹ�õ��� */
        if (CNAS_HSD_AVOID_ITEM_UNUSED == pstAvoidFreqInfo->enUsedFlag)
        {
            ulFlag = VOS_TRUE;

            break;
        }
    }

    if (VOS_TRUE == ulFlag)
    {
        CNAS_HSD_IncreaseAvoidFreqUsedNum();

        return pstAvoidFreqInfo;
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_IsCurrFreqExistInAvoidList
 ��������  : �жϵ�ǰfreq��avoid list�Ƿ��Ѿ����ڣ����������������index
 �������  : pstFreq -- ��ǰfreq

 �������  : ucIndex -- �ҵ��Ķ�Ӧ��
 �� �� ֵ  : VOS_TRUE -- ��ǰfreq��avoid list��
             VOS_FALSE -- ��ǰfreq����avoid list��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsCurrFreqExistInAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    VOS_UINT8                          *ucIndex
)
{
    VOS_UINT8                           i;
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;

    /* ����avoid�б������е�Ƶ�㣬��ǰƵ����avoid�б���, ����VOS_TRUE */
    for (i = 0; i < CNAS_HSD_MAX_AVOID_FREQ_NUM; i++)
    {
        pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(i);

        if (CNAS_HSD_AVOID_ITEM_UNUSED == pstAvoidFreqInfo->enUsedFlag)
        {
            continue;
        }

        if (VOS_TRUE == CNAS_PRL_CmpFreqValue(&(pstAvoidFreqInfo->stAvoidFreq), pstFreq))
        {
            *ucIndex = i;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_AddAvoidInfoToAvoidFreqItem
 ��������  : ����ǰslice��avoid slice��ӵ���ǰfreq��avoid list�е���
 �������  : pstFreq -- ��Ҫavoid�����Ƶ��
             ulStartSlice -- ��ǰslice
             ulExpiredSliceNum -- avoid slice

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_AddAvoidInfoToAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    VOS_UINT32                          ulStartSlice,
    VOS_UINT32                          ulExpiredSliceNum
)
{
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;
    VOS_UINT8                           ucIndex;

    ucIndex = 0;

    /* �����ǰfreq�Ѿ�����avoid״̬���������avoid��Ϣ���³����µ�avoid��Ϣ��
       �����ҵ�һ���յļ�¼��д���µ�avoid��Ϣ */
    if (VOS_TRUE == CNAS_HSD_IsCurrFreqExistInAvoidList(pstFreq, &ucIndex))
    {
        pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(ucIndex);
    }
    else
    {
        pstAvoidFreqInfo = CNAS_HSD_GetEmptyItemFormAvoidList();
    }

    if (VOS_NULL_PTR == pstAvoidFreqInfo)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_AddAvoidInfoToAvoidList: get avoid item fail!");

        return;
    }

    pstAvoidFreqInfo->enUsedFlag                = CNAS_HSD_AVOID_ITEM_USED;
    pstAvoidFreqInfo->ulStartSlice              = ulStartSlice;
    pstAvoidFreqInfo->ulExpiredSliceNum         = ulExpiredSliceNum;
    pstAvoidFreqInfo->stAvoidFreq.enBandClass   = pstFreq->enBandClass;
    pstAvoidFreqInfo->stAvoidFreq.usChannel     = pstFreq->usChannel;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAvoidTimeLenInAccessRlstInd
 ��������  : ���¼�����
 �������  : enAcsFailReason -- ԭ��ֵ

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���
  1.��    ��   : 2015��06��06��
    ��    ��   : z00316370
    �޸�����   : ��Ϣ��CAS��ΪHSM���ͣ���Ӧ���޸�

*****************************************************************************/
VOS_VOID CNAS_HSD_IncreaseCounterInAccessRlstInd(
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enFailReason
)
{
    switch (enFailReason)
    {
        case HSM_HSD_HRPD_CONN_OPEN_RSLT_MAX_PROBE:
            CNAS_HSD_IncreaseCounter(CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE, CNAS_HSD_AVOID_PROBE_COUNTER_MAX);
            break;

        case HSM_HSD_HRPD_CONN_OPEN_RSLT_BS_BUSY_OR_GENERAL :
            CNAS_HSD_IncreaseCounter(CNAS_HSD_AVOID_BUSY_OR_GENERAL_FAILURE, CNAS_HSD_AVOID_BUSY_COUNTER_MAX);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAvoidTimeLenInAccessRlstInd
 ��������  : ��ȡavoid time
 �������  : enAcsFailReason -- ԭ��ֵ

 �������  : ��
 �� �� ֵ  : ulAvoidTime -- ��ȡ����avoid time
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���
  1.��    ��   : 2015��06��06��
    ��    ��   : z00316370
    �޸�����   : ��Ϣ��CAS��ΪHSM���ͣ���Ӧ���޸�
*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetAvoidTimeLenInAccessRlstInd(
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enFailReason
)
{
    VOS_UINT32                          ulAvoidTime;

    switch (enFailReason)
    {
        case HSM_HSD_HRPD_CONN_OPEN_RSLT_PERSIST_FAIL:
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_PERSISTENCE_TEST_FAILURE);
            break;

        case HSM_HSD_HRPD_CONN_OPEN_RSLT_MAX_PROBE:
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_With_Counter(CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE);
            break;

        case HSM_HSD_HRPD_CONN_OPEN_RSLT_AUTH_BILLING_FAIL:
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_AUTHEN_OR_BILLING_FAILURE);
            break;

        case HSM_HSD_HRPD_CONN_OPEN_RSLT_BS_BUSY_OR_GENERAL:
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_With_Counter(CNAS_HSD_AVOID_BUSY_OR_GENERAL_FAILURE);
            break;

        case HSM_HSD_HRPD_CONN_OPEN_RSLT_PREFER_CH_NOT_VALID:
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_PREFER_CH_NOT_VALID);
            break;

        default:
            ulAvoidTime = 0;
            break;
    }

    return ulAvoidTime;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetAvoidTimeLenInSessionNegRlstInd
 ��������  : ��ȡavoid time
 �������  : enNegResult -- session neg�Ľ��

 �������  :
 �� �� ֵ  : ulAvoidTime -- ��ȡ����avoid time
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_GetAvoidTimeLenInSessionNegRlstInd(
    HSM_HSD_SESSION_NEG_RSLT_ENUM_UINT8 enNegResult
)
{
    VOS_UINT32                          ulAvoidTime;

    if (HSM_HSD_SESSION_NEG_RSLT_TIMEOUT == enNegResult)
    {
        ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_With_Counter(CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT);
    }
    else if (HSM_HSD_SESSION_NEG_RSLT_FAIL == enNegResult)
    {
        ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_SESSION_NEGOTIATION_FAILURE);
    }
    else
    {
        ulAvoidTime = 0;
    }

    return ulAvoidTime;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcAvoidEventInAccessRlstInd
 ��������  : �յ�access rlst ind��Ϣ����avoid�¼�
 �������  : pstAccessRlstInd -- access rlst Ind��Ϣָ��
             pstFreq -- ��Ҫavoid��freq

 �������  : penReAcqFlag -- �Ƿ���Ҫ���������ı��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��06��06��
    ��    ��   : z00316370
    �޸�����   : 1����Ϣ��CAS��ΪHSM���ͣ���Ӧ���޸ģ�
                 2��ԭ�ȳɹ�����߼�����ProcAvoidEventInCasStatusInd��

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcAvoidEventInAccessRlstInd(
    HSM_HSD_CONN_OPEN_IND_STRU         *pstOpenInd,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_HSD_REACQ_FALG_ENUM_UINT32    *penReAcqFlag
)
{
    VOS_UINT32                          ulExpiredSliceNum;
    VOS_UINT32                          ulAvoidTime;

    ulExpiredSliceNum = 0;
    ulAvoidTime       = 0;

    if (HSM_HSD_HRPD_CONN_OPEN_RSLT_SUCC == pstOpenInd->enRslt)
    {
        /* access�ɹ������Э��5.7.5b�еļ����� */
        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_BUSY_OR_GENERAL_FAILURE);

        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_TCA_TIMEOUT);
    }
    else
    {
        if (HSM_HSD_HRPD_CONN_OPEN_RSLT_TCA_RTC_ACK_TIMEOUT == pstOpenInd->enRslt)
        {
            CNAS_HSD_ProcAvoidEventInTchAssignTimeoutInd(penReAcqFlag);

            return;
        }

        /*  CDG143 6.4 �ǻ��ģʽ�´˳�������Ҫavoid */
        if (HSM_HSD_HRPD_CONN_OPEN_RSLT_MAX_PROBE == pstOpenInd->enRslt)
        {
            if (VOS_FALSE == CNAS_HSD_IsNeedAvoidedInNonHbrid(CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE))
            {
                return;
            }
        }

        /* ���ݴ���ֵ����Э��CDG143����5.7.2b��5.7.5b�������ļ�����*/
        CNAS_HSD_IncreaseCounterInAccessRlstInd(pstOpenInd->enRslt);

        /* ��ȡavoid time */
        ulAvoidTime = CNAS_HSD_GetAvoidTimeLenInAccessRlstInd(pstOpenInd->enRslt);

        if (0 != ulAvoidTime)
        {
            ulExpiredSliceNum = ulAvoidTime * CNAS_HSD_GetSystemSliceNumOfOneSecond();

            CNAS_HSD_AddAvoidInfoToAvoidList(pstFreq,
                                             CNAS_HSD_GetSystemSlice(),
                                             ulExpiredSliceNum);

            /* ���avoid timerδ����������avoid timer��ʱ�� */
            if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSD,
                                                                          TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                          0))
            {
                CNAS_HSD_StartTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                    TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
            }

            *penReAcqFlag = CNAS_HSD_NEED_REACQ;
        }

    }

    CNAS_HSD_LogAvoidFreqList(CNAS_HSD_GetAvoidFreqListAddr());

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcCounterInTchAssignTimeoutInd
 ��������  : ����access rlst ind��Ϣ
 �������  : pstAccessRlstInd -- access rlst Ind��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcAvoidEventInTchAssignTimeoutInd(
    CNAS_HSD_REACQ_FALG_ENUM_UINT32    *penReAcqFlag
)
{
    VOS_UINT8                           ucCounter;

    /*  CDG143 6.4 �ǻ��ģʽ�´˳�������Ҫavoid */
    if (VOS_FALSE == CNAS_HSD_IsNeedAvoidedInNonHbrid(CNAS_HSD_AVOID_TCA_TIMEOUT))
    {
        return;
    }

    /* ����Э��CDG143��5.7.7��TCA TimeoutʱҪ���Ӽ������ļ��� */
    CNAS_HSD_IncreaseCounter(CNAS_HSD_AVOID_TCA_TIMEOUT, CNAS_HSD_AVOID_TCA_COUNTER_MAX);

    ucCounter = CNAS_HSD_GetCounterValue(CNAS_HSD_AVOID_TCA_TIMEOUT);

    /* ����Э��CDG143��5.7.7��TCA Timeout�������κ��������� */
    if (ucCounter >= CNAS_HSD_AVOID_TCA_COUNTER_MAX)
    {
        *penReAcqFlag = CNAS_HSD_NEED_REACQ;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcCounterInCasStatusInd
 ��������  : ����cas status ind��Ϣ
 �������  : pstAccessRlstInd -- access rlst Ind��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcAvoidEventInCasStatusInd(
    CNAS_HSD_AT_STATUS_ENUM_UINT32      enHsdATStatus
)
{
    /* ״̬����IDLE->TCH�л�ʱ����ʾһ��max access probes�ɹ���Ҫ����Э��CDG143��5.7.2�еļ����� */
    if ((CNAS_HSD_AT_STATUS_ENUM_IDLE == CNAS_HSD_GetATStatus())
     && (CNAS_HSD_AT_STATUS_ENUM_CONN  == enHsdATStatus))
    {
        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcFreqAvoidedInSessionNegRlstInd
 ��������  : ����session negotionation rlst ind��Ϣ
 �������  : pstAccessRlstInd -- access rlst Ind��Ϣָ��
             pstFreq -- ��Ҫavoid��freq

 �������  : penReAcqFlag -- �Ƿ���Ҫ���������ı��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcAvoidEventInSessionNegRlstInd(
    HSM_HSD_SESSION_NEG_RESULT_IND_STRU                    *pstSessionNegRlstInd,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_HSD_REACQ_FALG_ENUM_UINT32                        *penReAcqFlag
)
{
    VOS_UINT32                          ulExpiredSliceNum;
    VOS_UINT32                          ulAvoidTime;

    ulExpiredSliceNum = 0;
    ulAvoidTime       = 0;

    /* ����Э��CDG143��5.8,session neg�ɹ���Ҫ���5.8.1�еļ����� */
    if (HSM_HSD_SESSION_NEG_RSLT_SUCCESS == pstSessionNegRlstInd->enNegResult)
    {
        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT);
    }
    else
    {
        /* ����Э��CDG143��5.8,session neg timeout or failʱ��Ҫ���ε�ǰfreq��������������
           �����session neg timeout����Ҫ����5.8.1�������ļ����� */
        if (HSM_HSD_SESSION_NEG_RSLT_TIMEOUT == pstSessionNegRlstInd->enNegResult)
        {
            CNAS_HSD_IncreaseCounter(CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT, CNAS_HSD_AVOID_SESSION_COUNTER_MAX);
        }

        ulAvoidTime = CNAS_HSD_GetAvoidTimeLenInSessionNegRlstInd(pstSessionNegRlstInd->enNegResult);

        if (0 != ulAvoidTime)
        {
            ulExpiredSliceNum = ulAvoidTime * CNAS_HSD_GetSystemSliceNumOfOneSecond();

            CNAS_HSD_AddAvoidInfoToAvoidList(pstFreq,
                                             CNAS_HSD_GetSystemSlice(),
                                             ulExpiredSliceNum);

            /* ���avoid timerδ����������avoid timer��ʱ�� */
            if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSD,
                                                                          TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                          0))
            {
                CNAS_HSD_StartTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                    TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
            }

            *penReAcqFlag = CNAS_HSD_NEED_REACQ;
        }
    }

    CNAS_HSD_LogAvoidFreqList(CNAS_HSD_GetAvoidFreqListAddr());

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcRequiredFreqAvoidedInAccessRlstInd
 ��������  : ����access rlst ind��Ϣ
 �������  : pstAccessRlstInd -- access rlst Ind��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcAvoidEventInCasSysSyncCnf(
    CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf
)
{
    VOS_UINT32                          ulExpiredSliceNum;
    VOS_UINT32                          ulRunSliceNum;
    VOS_UINT32                          ulCurrSlice;
    VOS_UINT32                          ulAvoidTime;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreq;
    VOS_UINT8                           i;

    ulAvoidTime      = 0;
    ulCurrSlice      = CNAS_HSD_GetSystemSlice();

    /* Э��CDG130��10.3.5�涨�����freqͬ��ʧ�ܵ�ԭ����protocol mismatch���򽫸�freq��ӵ�avoid list�� */
    for (i = 0; i < pstSyncCnf->ulSyncFailFreqNum; i++)
    {
        if (CNAS_CAS_HRPD_SYS_SRCH_SYNC_FAIL_PROTO_MISMATCH == pstSyncCnf->astSyncRsltList[i].enFailReason)
        {
            ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_PROTOCAL_MISMATCH);
        }

        if (0 != ulAvoidTime)
        {
            /* �����ͬ��ʧ�ܵ�������������ʱ���Ѿ�������Ҫ���ε�ʱ�䣬�򲻽������β��� */
            ulExpiredSliceNum = ulAvoidTime * CNAS_HSD_GetSystemSliceNumOfOneSecond();

            ulRunSliceNum     = ulCurrSlice - pstSyncCnf->astSyncRsltList[i].ulSlice;
            ulRunSliceNum     = ulRunSliceNum % CNAS_HSD_MAX_SLICE_VALUE;

            if (ulRunSliceNum < ulExpiredSliceNum)
            {
                stFreq.enBandClass  = pstSyncCnf->astSyncRsltList[i].stFreq.usBandClass;
                stFreq.usChannel    = pstSyncCnf->astSyncRsltList[i].stFreq.usChannel;

                CNAS_HSD_AddAvoidInfoToAvoidList(&stFreq, ulCurrSlice, ulExpiredSliceNum);
            }

            ulAvoidTime = 0;
        }
    }

    if (0 != CNAS_HSD_GetAvoidFreqListUsedNum())
    {
        /* ���avoid timerδ����������avoid timer��ʱ�� */
        if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSD,
                                                                      TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                      0))
        {
            CNAS_HSD_StartTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
        }
    }

    CNAS_HSD_LogAvoidFreqList(CNAS_HSD_GetAvoidFreqListAddr());

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcAvoidEventInRedirection
 ��������  : redirectionʱ����avoid����¼�
 �������  : pstFreq -- ��Ҫ����avoid�����Ƶ��

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcAvoidEventInRedirection(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    VOS_UINT32                          ulExpiredSliceNum;
    VOS_UINT32                          ulAvoidTime;

    /* Э��CDG143��5.6.2�涨��redirectionʧ�ܺ���Ҫ��ԭ����freq����30sec */
    ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_REDIRECTION);

    if (0 != ulAvoidTime)
    {
        ulExpiredSliceNum = ulAvoidTime * CNAS_HSD_GetSystemSliceNumOfOneSecond();

        CNAS_HSD_AddAvoidInfoToAvoidList(pstFreq,
                                         CNAS_HSD_GetSystemSlice(),
                                         ulExpiredSliceNum);

        /* ���avoid timerδ����������avoid timer��ʱ�� */
        if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSD,
                                                                      TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                      0))
        {
            CNAS_HSD_StartTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
        }
    }

    CNAS_HSD_LogAvoidFreqList(CNAS_HSD_GetAvoidFreqListAddr());

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_PRL_IsSubnetIDChange
 ��������  : �ж�SubnetId�Ƿ�ı�
 �������  : pstCurrHrpdSys - �µ�Hrpdϵͳ
             pstLastHrpdSys - �ɵ�Hrpdϵͳ

 �������  : ��

 �� �� ֵ  :VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsSubnetIdChange(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstCurrHrpdSys,
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstLastHrpdSys
)
{
    VOS_UINT8                           ucCurrSubnetid;
    VOS_UINT8                           ucLastSubnetid;
    VOS_UINT8                           ucSubnetTempLen;
    VOS_UINT8                           ucSubnetBitTempLen;   /* ���Subneʣ��bit���� */

    if (pstCurrHrpdSys->ucSubnetMask != pstLastHrpdSys->ucSubnetMask)
    {
        return VOS_TRUE;
    }

    ucSubnetTempLen = (pstCurrHrpdSys->ucSubnetMask / CNAS_PRL_BIT_LEN_8_BIT);

    /* �ȱȽ����ֽ� */
    if (VOS_TRUE != CNAS_PRL_CmpSubnetValue(pstCurrHrpdSys->aucSubnet, pstLastHrpdSys->aucSubnet, ucSubnetTempLen))
    {
        return VOS_TRUE;
    }

    /* �ٱȽ�ʣ��bit */
    ucSubnetBitTempLen = (pstCurrHrpdSys->ucSubnetMask % CNAS_PRL_BIT_LEN_8_BIT);
    if (0 < ucSubnetBitTempLen)
    {
        ucCurrSubnetid = CNAS_PRL_ExtractBitStringToOctet(&(pstCurrHrpdSys->aucSubnet[ucSubnetTempLen]), 0, ucSubnetBitTempLen);
        ucLastSubnetid = CNAS_PRL_ExtractBitStringToOctet(&(pstLastHrpdSys->aucSubnet[ucSubnetTempLen]), 0, ucSubnetBitTempLen);

        if (ucCurrSubnetid != ucLastSubnetid)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcRequiredFreqAvoidedInAccessRlstInd
 ��������  : Subnet-Id changeʱ����avoid����¼�
 �������  : pstCurrSysId -- ��פ����hrpdϵͳ

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��07��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcAvoidEventInSubnetIdChange(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstCurrHrpdSys
)
{
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstLastHrpdSys;

    pstLastHrpdSys = &(CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0]);

    /* subnet-id changeʱ��Ҫ���Э��CDG143����5.7.7��5.8.1������������������ */
    if (VOS_TRUE == CNAS_HSD_IsSubnetIdChange(pstCurrHrpdSys, pstLastHrpdSys))
    {
        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_SESSION_NEGOTIATION_TIMEOUT);
        CNAS_HSD_ClearCounter(CNAS_HSD_AVOID_TCA_TIMEOUT);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcAvoidEventInNetwkLost
 ��������  : ��������������avoid����
 �������  : pstNetwkLostSysRec         ������¼��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_ProcAvoidEventInNetwkLostInd(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    VOS_UINT32                                              ulAvoidTime;
    VOS_UINT32                                              ulExpiredSliceNum;

    ulAvoidTime = CNAS_HSD_GetAvoidTimeLen_Without_Counter(CNAS_HSD_AVOID_FAIL_CONTINUE_THREE_TIMES);

    ulExpiredSliceNum = ulAvoidTime * CNAS_HSD_GetSystemSliceNumOfOneSecond();

    CNAS_HSD_AddAvoidInfoToAvoidList(pstFreq,
                                     CNAS_HSD_GetSystemSlice(),
                                     ulExpiredSliceNum);

    /* ���avoid timerδ����������avoid timer��ʱ�� */
    if (CNAS_TIMER_STATUS_RUNNING != CNAS_GetSpecifiedTimerStatus(UEPS_PID_HSD,
                                                                  TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                                                                  0))
    {
        CNAS_HSD_StartTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                            TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_IsNeedAvoided
 ��������  : �ж��Ƿ���Ҫavoid
 �������  : enAvoidReason         avoidԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_IsNeedAvoidedInNonHbrid(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
)
{
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32  enSysMode;

    enSysMode = CNAS_HSD_GetModeType();

    /* CDG143 6.4,�ǻ��ģʽ�£�һ�����ֳ�������Ҫ����avoid���� */
    if (((CNAS_HSD_AVOID_MAX_ACCESS_PROBES_FAILURE == enAvoidReason)
      || (CNAS_HSD_AVOID_TCA_TIMEOUT == enAvoidReason))
     && (CNAS_HSD_SYS_MODE_NONHYBRID == enSysMode))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


#endif

/*lint -restore*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



