/******************************************************************************

                  ��Ȩ���� (C), 2014-2020, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdSysAcqStrategy.h
  �� �� ��   : ����
  ��    ��   : wenlutao /00176964
  ��������   : 2014��08��05��
  ����޸�   :
  ��������   : CnasXsdSysAcqStrategy.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��08��05��
    ��    ��   : wenlutao /00176964
    �޸�����   : CDMA 1X IT&1 added

******************************************************************************/
#ifndef _CNAS_XSD_SYS_ACQ_STRATEGY_H_
#define _CNAS_XSD_SYS_ACQ_STRATEGY_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "CnasPrlApi.h"
#include  "CnasXsdCtx.h"
#include  "cas_1x_control_initialstate_nas_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CNAS_XSD_CHANNEL_REPEAT_INTERVAL     (5)


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
 �ṹ��    : NA
 �ṹ˵��  : ɨ��Ƶ���б��ʼ������ָ��
 1.��    ��   : 2014��8��05��
   ��    ��   : W00176964
   �޸�����   : ����
*****************************************************************************/
typedef VOS_VOID  (*pCNasXsdScanChanListBuildFunc)(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

/*****************************************************************************
 �ṹ��    : CNAS_XSD_SCAN_CHANNEL_LIST_BUILD_TBL_STRU
 �ṹ˵��  : ���治ͬ����������Ƶ��ɨ���б��캯��
 1.��    ��   : 2014��8��05��
   ��    ��   : w00176964
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene;           /* ϵͳ���񳡾� */
    pCNasXsdScanChanListBuildFunc       pfunScanChanListBuild;    /* ��Ӧ������ɨ��Ƶ���б��캯��ָ�� */
}CNAS_XSD_SCAN_CHANNEL_LIST_BUILD_TBL_STRU;

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
VOS_VOID CNAS_XSD_BuildScanChanList(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene,
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSyncSuccSysId,
    VOS_UINT16                                              usMatchedSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMatchedSysRecord,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList,
    VOS_UINT16                                              usMostMatchedIndex
);

VOS_VOID CNAS_XSD_BuildScanChanList_SwitchOn(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_SystemLost(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_AvailableTimerExpired(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_CallReleased(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_EmcCallReleased(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_SystemLostSkipMru0(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_PowerOnInitSearch(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
);

VOS_VOID CNAS_XSD_OrderScanListByMruList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList,
    CNAS_XSD_MRU_LIST_STRU             *pstMruList
);

VOS_UINT16 CNAS_XSD_GetSystemIndexOfSameOrMorePreferredThanSpecifiedSystemInGeo(
    VOS_UINT16                                              usSysMatchedIndex,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMatchedGeoInfo
);

VOS_VOID CNAS_XSD_BuildCallRedialScanChanListUponOrigSystemInGeo(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_CallRedial(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_MoveFreqChantoEndOfChanList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSys,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildCallRedialScanChanList(
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampSysInfo
);

VOS_VOID CNAS_XSD_BuildEmcCallRedialScanChanList( VOS_VOID );

VOS_VOID CNAS_XSD_ClearCallRedialScanChanList(VOS_VOID);

VOS_VOID CNAS_XSD_UpdateScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstDestScanChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstSrcScanChanList
);


VOS_UINT16 CNAS_XSD_UpdateChanStatusInScanChanList(
    VOS_UINT16                                              usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstChannel,
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enChanStatus,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
);

VOS_VOID CNAS_XSD_UpdateSysFreqStatusBySysInGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_VOID CNAS_XSD_RemoveExpiredFreqFromAvoidList(VOS_VOID);

VOS_UINT8 CNAS_XSD_IsCurFreqAvoided(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqChan
);

VOS_UINT32  CNAS_XSD_IsOocSceneAndRepeatMru0FreqSrchExist(
    CNAS_PRL_1X_SYSTEM_STRU         *pstMru0SysId
);

VOS_UINT32 CNAS_XSD_IsMru0FreqInOocScene(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqChan
);

VOS_VOID CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enChanStatus,
    VOS_UINT16                                              usCurScanChanIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
);

VOS_UINT16 CNAS_XSD_UpdateNoSyncedOrSyncSuccScanChanInScanChanList(
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enChanStatus,
    VOS_UINT16                                              usCurScanIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
);

VOS_VOID CNAS_XSD_GetNextScanChanList(
    VOS_UINT16                          usCurScanChanIndex,
    VOS_UINT16                         *pusDstChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList,
    VOS_UINT32                          ulIsAvoidListEnable
);

VOS_VOID CNAS_XSD_SortChanListByMruList(
    VOS_UINT16                          usChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChanList,
    CNAS_XSD_MRU_LIST_STRU             *pstMruList
);

VOS_UINT32 CNAS_XSD_PraseChannelInMatchedGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMatchedGeoList,
    VOS_UINT16                                              usMaxGeoChanNum,
    VOS_UINT16                                             *pusGeoChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstGeoChanList
);


CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8 CNAS_XSD_GetScanChanStatusInScanChanList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_AddMruListInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_AddUePreferredListInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_AddHistorySyncedSuccFreqListInScanChanlist(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_AddMruListExcludeMru0InScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_AddSpecPrlAcqRecInScanChanList(
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_AddPrlAcqRecListInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_AppendFreqChanInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU    *pstScanChanInfo,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_AddFreqChanListInScanChanList(
    VOS_UINT16                          usChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_UINT32 CNAS_XSD_IsChannelInChannelList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChannel,
    VOS_UINT16                          usChanListNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChanList
);

VOS_UINT32 CNAS_XSD_IsChannelInLatestSndCasAcqSysInfo(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_XSD_LATEST_SND_CAS_ACQ_SYSTEM_INFO                *pstLastSndCasSysInfo
);

VOS_VOID CNAS_XSD_AppendAcqSysInfoInAcqSysList(
    CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU                      *pstAcqSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_VOID CNAS_XSD_AddSysRecordIntoSysList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstSysAcqList
);

VOS_VOID CNAS_XSD_GetNextSysSyncListFromGeoSysRecordSrchList(
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList,
    VOS_UINT16                                             *pusScanChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstScanList
);

VOS_VOID CNAS_XSD_UpdateSysFreqStatusByFreqChanInGeoSysRecordSrchList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_VOID CNAS_XSD_AllocMemoryForScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);

VOS_VOID CNAS_XSD_AllocMemoryForGeoSysRecordSrchList(
    VOS_UINT16                                              usMatchedSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMatchedSysRecord,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_VOID CNAS_XSD_BuildScanChanList_RedirectionFail(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_RedirectionWithInvalidGSRDM(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_Rescan(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_ProtoMismatch(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);


VOS_VOID CNAS_XSD_BuildScanChanList_AccessDenied(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_AcctBlocked(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_NdssOff(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_Error(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);


VOS_VOID CNAS_XSD_BuildScanChanList_RegisRej(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_RegisRejWithRedirAndRtf(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_SysReselWithPrefPrl(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_SysReselNotInPrlOrNeg(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);


VOS_VOID CNAS_XSD_BuildScanChanList_MaxAccessFailureInPrl(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_MaxAccessFailureNotInPrl(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_CallReleasedWithRedir(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_Abnormal(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM_UINT8 CNAS_XSD_GetSysAcqModeOfSpecialAcqScene(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enScanScene
);

VOS_UINT32 CNAS_XSD_IsChannelInPrlAcqTbl(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChannel
);

VOS_UINT32 CNAS_XSD_IsAvailableSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSys
);

VOS_UINT32 CNAS_XSD_IsAcquireAvaialSysNeeded(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enScanScene
);

VOS_VOID CNAS_XSD_BuildScanChanList_Redirection(
    CNAS_XSD_REDIRECTION_INFO_STRU              *pstRedirectionInfo,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU             *pstScanList
);

VOS_VOID CNAS_XSD_AllocMemoryForScanChanList_FreqLock(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
);
VOS_VOID CNAS_XSD_BuildScanChanList_FreqLock(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_MRU0(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_EMC(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildScanChanList_CALLBACK(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildNormalSystemLostScanChanlist(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
);

VOS_VOID CNAS_XSD_AddOrigChanToScanChanlist_REACQ_0_1_2_3_4s(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                        *pstPreCampFreq
);

VOS_VOID CNAS_XSD_AddOrigChanToScanChanlist_PING_5(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                        *pstPreCampFreq
);

VOS_VOID CNAS_XSD_AddOrigChanToScanChanlist_2_7(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                        *pstPreCampFreq
);

VOS_UINT32 CNAS_XSD_IsChannelInSndCasSyncList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstScanList,
    VOS_UINT16                                              usScanNum
);

VOS_UINT16 CNAS_XSD_UpdateSyncSuccChanStatus(
    VOS_UINT16                          usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChannel,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_UINT16 CNAS_XSD_UpdateSyncFailChanStatus(
    VOS_UINT16                          usBeginScanListIndex,
    VOS_UINT16                          usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU    *pstSyncFailChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
);

VOS_VOID CNAS_XSD_UpdateGeoListSrchStatus(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    VOS_UINT16                                              usGeoSrchStatus
);

VOS_VOID CNAS_XSD_UpdateGeoSysRecordListInfoAccordingToScanChanList(
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
);

VOS_VOID CNAS_XSD_UpdateRedirectionFreqStatusAccordingToScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
);

VOS_VOID CNAS_XSD_BuildEmcRedialMruList(VOS_VOID);

VOS_VOID CNAS_XSD_ClearEmcRedialSysAcqCfgInfo(VOS_VOID);

VOS_UINT8 CNAS_XSD_GetCurSysIndexOfEmcRedialMruList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    VOS_UINT32                                             *pulIndex
);

VOS_VOID CNAS_XSD_BuildScanChanList_CallReleaseSystemLost(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
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

#endif /* end of CNasXsdSysAcqStrategy.h */


