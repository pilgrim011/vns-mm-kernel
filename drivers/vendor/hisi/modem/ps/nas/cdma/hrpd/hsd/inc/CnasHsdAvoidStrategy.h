/******************************************************************************

                  ��Ȩ���� (C), 2014-2020, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdAvoidStrategy.h
  �� �� ��   : ����
  ��    ��   : x00306642
  ��������   : 2015��01��15��
  ����޸�   :
  ��������   : CnasHsdAvoidStrategy.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��01��15��
    ��    ��   : x00306642
    �޸�����   : Added for HRPD

******************************************************************************/
#ifndef _CNAS_HSD_AVOID_STRATEGY_H_
#define _CNAS_HSD_AVOID_STRATEGY_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "CnasHsdCtx.h"
#include  "CnasHsdComFunc.h"
#include  "hsm_hsd_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ����8��SESSION NEGOTIATION TIMEOUT��avoid time��ֵ����counterֵ�仯 */
#define CNAS_HSD_AVOID_SESSION_COUNTER_MAX      (7)

/* ����7��MAX ACCESS PROBES FAILURE��avoid time��ֵ����counterֵ�仯 */
#define CNAS_HSD_AVOID_PROBE_COUNTER_MAX        (6)

/* ��������BUSY_OR_GENERAL_FAILUREʱҪ�������� */
#define CNAS_HSD_AVOID_BUSY_COUNTER_MAX         (3)

/* ��������TCA timeoutʱҪ�������� */
#define CNAS_HSD_AVOID_TCA_COUNTER_MAX          (3)

/* avoid time�е�30sec��60sec */
#define CNAS_HSD_AVOID_TIME_30_SEC              (30)

#define CNAS_HSD_AVOID_TIME_60_SEC              (60)

#define CNAS_HSD_AVOID_NETWORK_LOST_MAX_CNT     (3)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

extern VOS_UINT32 CNAS_HSD_GetAvoidTimeLen_Without_Counter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);

extern VOS_UINT32 CNAS_HSD_GetAvoidTimeLen_With_Counter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);

extern VOS_VOID CNAS_HSD_IncreaseAvoidFreqUsedNum(VOS_VOID);

extern VOS_VOID CNAS_HSD_DecreaseAvoidFreqUsedNum(VOS_VOID);

extern VOS_VOID CNAS_HSD_IncreaseCounter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason,
    UINT8                               ucMaxCounter
);

extern VOS_VOID CNAS_HSD_ClearCounter(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);

extern VOS_UINT8 CNAS_HSD_GetCounterValue(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);

extern VOS_VOID CNAS_HSD_CheckExpiredFreqFromAvoidList(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_IsCurFreqAvoided(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

extern  VOS_VOID CNAS_HSD_DeleteItemFromAvoidList(
    VOS_UINT8                           ucIndex
);

extern CNAS_HSD_AVOID_FREQ_INFO_STRU* CNAS_HSD_GetAvoidItemFromAvoidList(
    VOS_UINT8                           ucIndex
);

extern CNAS_HSD_AVOID_FREQ_INFO_STRU* CNAS_HSD_GetEmptyItemFormAvoidList(VOS_VOID);

extern VOS_UINT32 CNAS_HSD_IsCurrFreqExistedInAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    VOS_UINT8                          *ucIndex
);

extern VOS_VOID CNAS_HSD_AddAvoidInfoToAvoidList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    VOS_UINT32                          ulStartSlice,
    VOS_UINT32                          ulExpiredSliceNum
);

extern VOS_VOID CNAS_HSD_IncreaseCounterInAccessRlstInd(
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enFailReason
);

extern VOS_UINT32 CNAS_HSD_GetAvoidTimeLenInAccessRlstInd(
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enFailReason
);

extern VOS_UINT32 CNAS_HSD_GetAvoidTimeLenInSessionNegRlstInd(
    HSM_HSD_SESSION_NEG_RSLT_ENUM_UINT8 enNegResult
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInAccessRlstInd(
    HSM_HSD_CONN_OPEN_IND_STRU         *pstOpenFailInd,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_HSD_REACQ_FALG_ENUM_UINT32    *penReAcqFlag
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInTchAssignTimeoutInd(
    CNAS_HSD_REACQ_FALG_ENUM_UINT32    *penReAcqFlag
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInCasStatusInd(
    CNAS_HSD_AT_STATUS_ENUM_UINT32      enHsdATStatus
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInSessionNegRlstInd(
    HSM_HSD_SESSION_NEG_RESULT_IND_STRU                    *pstSessionNegRlstInd,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_HSD_REACQ_FALG_ENUM_UINT32                        *penReAcqFlag
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInCasSysSyncCnf(
    CAS_CNAS_HRPD_SYSTEM_SYNC_CNF_STRU *pstSyncCnf
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInRedirection(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

extern VOS_UINT32 CNAS_HSD_IsSubnetIdChange(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstCurrHrpdSys,
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstLastHrpdSys
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInSubnetIdChange(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstCurrSysId
);

extern VOS_VOID CNAS_HSD_ProcAvoidEventInNetwkLostInd(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
);

extern VOS_UINT32 CNAS_HSD_IsNeedAvoidedInNonHbrid(
    CNAS_HSD_AVOID_REASON_ENUM_UINT8    enAvoidReason
);


#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CNasHsdAvoidStrategy.h */


