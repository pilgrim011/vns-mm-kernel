/******************************************************************************

                  ��Ȩ���� (C), 2014-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdSysAcqStrategy.c
  �� �� ��   : ����
  ��    ��   : wenlutao /00176964
  ��������   : 2014��08��05��
  ����޸�   :
  ��������   : CNAS ��״̬��ϵͳ��������������ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��08��05��
    ��    ��   : wenlutao /00176964
    �޸�����   : Added for CDMA 1X IT&1��
******************************************************************************/


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsCommonDef.h"
#include "stdlib.h"
#include "CnasXsdSysAcqStrategy.h"
#include "cas_1x_control_initialstate_nas_pif.h"
#include "CnasXsdMntn.h"
#include "CnasPrlApi.h"
#include "CnasCcb.h"
#include "CnasXsdComFunc.h"
#include "CnasXsdPreProcAct.h"
#include "NasMntn.h"
#include "CnasXsdFsmSysAcq.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_CNAS_XSD_SYS_ACQ_STRATEGY_C

/*lint -save -e958*/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/* ��������������Ӧ�������б��ʼ��������������״̬����ʼ��ʱʹ�� */
CNAS_XSD_SCAN_CHANNEL_LIST_BUILD_TBL_STRU                   g_astCnasXsdScanChanListBuildTbl[] =
{
    {CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON,                      CNAS_XSD_BuildScanChanList_SwitchOn},
    {CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST,                    CNAS_XSD_BuildScanChanList_SystemLost},
    {CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED,                  CNAS_XSD_BuildScanChanList_CallReleased},
    {CNAS_XSD_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED,        CNAS_XSD_BuildScanChanList_AvailableTimerExpired},

    {CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL,             CNAS_XSD_BuildScanChanList_CallRedial},

    {CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR,       CNAS_XSD_BuildScanChanList_CallReleasedWithRedir},
    {CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_FAIL,               CNAS_XSD_BuildScanChanList_RedirectionFail},
    {CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM, CNAS_XSD_BuildScanChanList_RedirectionWithInvalidGSRDM},

    {CNAS_XSD_SYS_ACQ_SCENE_RESCAN,                         CNAS_XSD_BuildScanChanList_Rescan},
    {CNAS_XSD_SYS_ACQ_SCENE_PROTO_MISMATCH,                 CNAS_XSD_BuildScanChanList_ProtoMismatch},
    {CNAS_XSD_SYS_ACQ_SCENE_ACCESS_DENINED,                 CNAS_XSD_BuildScanChanList_AccessDenied},
    {CNAS_XSD_SYS_ACQ_SCENE_ACCT_BLOCKED,                   CNAS_XSD_BuildScanChanList_AcctBlocked},
    {CNAS_XSD_SYS_ACQ_SCENE_NDSS_OFF,                       CNAS_XSD_BuildScanChanList_NdssOff},
    {CNAS_XSD_SYS_ACQ_SCENE_ERR,                            CNAS_XSD_BuildScanChanList_Error},
    {CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF,   CNAS_XSD_BuildScanChanList_RegisRejWithRedirAndRtf},
    {CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ,                      CNAS_XSD_BuildScanChanList_RegisRej},
    {CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF,      CNAS_XSD_BuildScanChanList_SysReselWithPrefPrl},
    {CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG,    CNAS_XSD_BuildScanChanList_SysReselNotInPrlOrNeg},
    {CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL,      CNAS_XSD_BuildScanChanList_MaxAccessFailureInPrl},
    {CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL,  CNAS_XSD_BuildScanChanList_MaxAccessFailureNotInPrl},
    {CNAS_XSD_SYS_ACQ_SCENE_ABNORMAL,                       CNAS_XSD_BuildScanChanList_Abnormal},

    {CNAS_XSD_SYS_ACQ_SCENE_CALL_MRU0,                      CNAS_XSD_BuildScanChanList_MRU0},

    {CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL,                 CNAS_XSD_BuildScanChanList_EMC},
    {CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST,       CNAS_XSD_BuildScanChanList_CALLBACK},
    {CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED,              CNAS_XSD_BuildScanChanList_EmcCallReleased},
    {CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0,          CNAS_XSD_BuildScanChanList_SystemLostSkipMru0},
    {CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC,   CNAS_XSD_BuildScanChanList_RegisRejWithRedirAndRtf},
    {CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC,      CNAS_XSD_BuildScanChanList_SysReselWithPrefPrl},
    {CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC,    CNAS_XSD_BuildScanChanList_SysReselNotInPrlOrNeg},
    {CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0_EMC,          CNAS_XSD_BuildScanChanList_SystemLostSkipMru0},
    {CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM_EMC, CNAS_XSD_BuildScanChanList_RedirectionWithInvalidGSRDM},
    {CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL_EMC,      CNAS_XSD_BuildScanChanList_MaxAccessFailureInPrl},
    {CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC,  CNAS_XSD_BuildScanChanList_MaxAccessFailureNotInPrl},

    {CNAS_XSD_SYS_ACQ_SCENE_POWER_ON_INIT_SEARCH,           CNAS_XSD_BuildScanChanList_PowerOnInitSearch},

    {CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASE_SYSTEM_LOST,           CNAS_XSD_BuildScanChanList_CallReleaseSystemLost},
};


/* �ñ�����ʱ����call release�����µ��б���, �����ᱻɾ�� */

VOS_UINT32                              g_CtrlCallRelScanList = VOS_TRUE;

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RemoveSpecialFreqFromScanList
 ��������  : �������б���ɾ��ָ��Ƶ��
 �������  : pstSpecialFreq  ---------- ָ��Ƶ��
             pstScanChanList ---------- ͬ���б�
 �������  : pstScanChanList ---------- ͬ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��12��21��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_RemoveSpecialFreqFromScanList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstSpecialFreq,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          usIndex;

    if ( (VOS_NULL_PTR == pstSpecialFreq)
      || (VOS_NULL_PTR == pstScanChanList) )
    {
        return;
    }

    for ( usIndex = 0; usIndex < pstScanChanList->usTotalNum; usIndex++ )
    {
        if ((pstSpecialFreq->enBandClass == pstScanChanList->pstScanChanInfo[usIndex].stFreqChan.enBandClass)
         && (pstSpecialFreq->usChannel   == pstScanChanList->pstScanChanInfo[usIndex].stFreqChan.usChannel))
        {
            if (usIndex != pstScanChanList->usTotalNum - 1)
            {
                NAS_MEM_MOVE_S(&(pstScanChanList->pstScanChanInfo[usIndex]),
                                (pstScanChanList->usTotalNum - usIndex) * sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU),
                               &(pstScanChanList->pstScanChanInfo[usIndex+1]),
                                (pstScanChanList->usTotalNum - usIndex - 1) * sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));
            }

            pstScanChanList->usTotalNum--;

            return;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList
 ��������  : ϵͳ����״̬������ʱ,Ƶ��ɨ����ʼ��
 �������  : enSysAcqScene ------------   ���񳡾�
             usPreSrchChanNum ------------��ǰ��Ҫ����������Ƶ�����,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
             pstPreSrchChanArray ----------��ǰ��Ҫ����������Ƶ������ͷָ��,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
 �������  : pstScanChanListInfo -----------����õ�ɨ��Ƶ���б�ָ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��08��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32 enSysAcqScene,
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    VOS_UINT32                          i;
    pCNasXsdScanChanListBuildFunc       pfunScanChanListBuild;
    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU  *pstCnasXsdCFreqLockValue;

    pstCnasXsdCFreqLockValue = CNAS_XSD_GetFreqLockAddr();

    pfunScanChanListBuild = VOS_NULL_PTR;

    if (VOS_TRUE == CNAS_XSD_GetTestConfig()->ucIsMod1xAvailTimerLen)
    {        
        CNAS_XSD_GetCdma1XCustomPrefChannels()->ucEnableFlg = VOS_FALSE;
    }

    /* ��������Ƶ */
    if (VOS_TRUE == pstCnasXsdCFreqLockValue->ucFreqLockMode)
    {
        CNAS_XSD_AllocMemoryForScanChanList_FreqLock(pstScanChanList);
        if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
        {
            CNAS_XSD_BuildScanChanList_FreqLock(pstScanChanList);
            CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_CFREQLOCK_SCAN_CHAN_LIST_IND, pstScanChanList);
        }

        return;
    }

    /* ���ݳ�����g_astCnasXsdScanChanListBuildTbl���������б��캯�� */
    for (i = 0; i < (sizeof(g_astCnasXsdScanChanListBuildTbl)/sizeof(CNAS_XSD_SCAN_CHANNEL_LIST_BUILD_TBL_STRU)); i++)
    {
        if (enSysAcqScene == g_astCnasXsdScanChanListBuildTbl[i].enSysAcqScene)
        {
            pfunScanChanListBuild = g_astCnasXsdScanChanListBuildTbl[i].pfunScanChanListBuild;
            break;
        }
    }

    /* ����scan list�Ƚϴ�,��Ҫ�ȷ����ڴ�,���ػ�ʱ�ͷ��ڴ� */
    /* ������������*/
    CNAS_XSD_AllocMemoryForScanChanList(pstScanChanList, enSysAcqScene);


    /* ���ҳɹ�ʱ���ó�ʼ���������й��� */
    if ((VOS_NULL_PTR != pfunScanChanListBuild)
     && (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo))
    {
        pfunScanChanListBuild(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

        CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_SCAN_CHAN_LIST_IND, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildGeoSysRecordSrchList
 ��������  : Ƶ��ͬ�����,��Ҫ����ϵͳʱ,�����б�Ĺ���
 �������  : usMatchedSysRecNum--------------ͬ���ɹ���ϵͳID:�����ͷŵȳ�����ֱ��ʹ��ͬ���ɹ���SID+NID�����б�
             pusMatchedSysRecNum-----------ϵͳGEO�б���ƥ���ϵͳ���¼�ܸ���,�����ƥ���,������дΪ0
             pstMatchedSysRecord ----------ϵͳGEO�б���ƥ���ϵͳ���¼ָ��,��GEO�������Ѿ��������ڴ�
 �������  : pstSysAcqList ---------------����õĲ���ϵͳ�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��08��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��7��9��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSyncSuccSysId,
    VOS_UINT16                                              usMatchedSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMatchedSysRecord,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList,
    VOS_UINT16                                              usMostMatchedIndex
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          j;
    VOS_UINT16                          usAcqIndex;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stAcqRecFreqInfo;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec = VOS_NULL_PTR;
    VOS_UINT16                          usLevel;
    VOS_UINT16                          usTotalNum;

    /* �ڴ����ʱ��������GEO�и����ȼ���ϵͳƵ��+��ǰͬ������ϵͳƵ�� */
    CNAS_XSD_AllocMemoryForGeoSysRecordSrchList(usMostMatchedIndex,
                                                pstMatchedSysRecord,
                                                pstGeoSysRecSrchList);

    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        return;
    }

    /* ��ȡGEO����match��level */
    usLevel = (pstMatchedSysRecord + usMostMatchedIndex)->usPriLvl;

    for (i = 0; i < usMatchedSysRecNum; i++)
    {
        if (VOS_FALSE == pstMatchedSysRecord[i].ucSysRecValid)
        {
            continue;
        }

        usAcqIndex = pstMatchedSysRecord[i].usAcqIndex;

        /* ��ȡPRL�л�ȡ��ָ�� */
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(usAcqIndex);

        /* ��ָ����б��� */
        if (VOS_NULL_PTR == pstPrlAcqRec)
        {
            continue;
        }

        /*******************************************************************************************
         * ֻȡ�����ȼ���ϵͳ�Լ���ǰͬ������ϵͳ
         * ע: ��������ǰ�ж�level�����������ǰϵͳ����GEO��level����߼���ģ�������֮ǰ��Ȼ��ͬ��
         *     ���ϵͳ���ᱻ�ӽ�ȥ
         ******************************************************************************************/
        if (usLevel == pstMatchedSysRecord[i].usPriLvl)
        {
            usTotalNum = pstGeoSysRecSrchList->usTotalNum;

            /* ����Ĭ�ϸ��µ�ǰϵͳΪ����ϵͳ��ͬ��״̬Ϊδͬ���󣬺��������ǰϵͳΪnegativeϵͳ����ˢ��Ϊͬ�������ڣ�
               ����ᱻˢ��Ϊͬ������ */
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].enPrefNegSys                = CNAS_PRL_PREF_NEG_SYS_PREF;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].enSysStatus                 = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].stAcqSys.stFreq.enBandClass = pstSyncSuccSysId->stFreq.enBandClass;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].stAcqSys.stFreq.usChannel   = pstSyncSuccSysId->stFreq.usChannel;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].stAcqSys.usNid              = pstSyncSuccSysId->usNid;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].stAcqSys.usSid              = pstSyncSuccSysId->usSid;
            pstGeoSysRecSrchList->pstAcqSysInfo[usTotalNum].usLevel                     = usLevel;

            pstGeoSysRecSrchList->usTotalNum++;

            return;
        }

        /*******************************************************************************************
         * ֻͳ��IS_95��ϵͳ�Լ�MCC/MNC��������ΪSID��SID/NID��ϵͳ
         ******************************************************************************************/
        /*  */
        if ((CNAS_PRL_SYS_RECORD_TYPE_1X_IS95           == pstMatchedSysRecord[i].enRecordType)
        || ((CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED     == pstMatchedSysRecord[i].enRecordType)
         && ((CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID     == pstMatchedSysRecord[i].u.stMccMncId.enMccMncSubType)
          || (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID == pstMatchedSysRecord[i].u.stMccMncId.enMccMncSubType))))
        {
            NAS_MEM_SET_S(&stAcqRecFreqInfo, sizeof(stAcqRecFreqInfo), 0x0, sizeof(CNAS_PRL_ACQ_REC_FREQ_INFO_STRU));
            CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stAcqRecFreqInfo);

            for (j = 0; j < CNAS_MIN(stAcqRecFreqInfo.ulNum, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); j++)
            {
                CNAS_XSD_AddSysRecordIntoSysList(&(stAcqRecFreqInfo.astFreqInfo[j]), &(pstMatchedSysRecord[i]), pstGeoSysRecSrchList);
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_SwitchOn
 ��������  : ����ɨ��Ƶ���б���
 �������  : usPreSrchChanNum ------------ ��ǰ��Ҫ����������Ƶ�����,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
             pstPreSrchChanArray---------- ��ǰ��Ҫ����������Ƶ������ͷָ��,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_SwitchOn(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    /* �б����: (MRU + ���ų���Ƶ�� + PRL Acquire table)
         Reference to
         CDG130:
         5.2.3.1  Normal Scan List
         such as the deletion of:
           Duplicate entries
           Channels caused by suitable identification in the preferences (see section 5.1.1)
           Channels that can be specifically identified as negative systems

         CDG143:
         4.1 Power-up
         4.1.1 This requirement does not exclude multiple acquisition attempts on channels, like MRU[0], before completing a pass through the MRU and PRL
    */
    /* �Ƚ�MRU�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    CNAS_XSD_AddMruListInScanChanList(pstScanChanList);

    /* �����ų���1X Ƶ����뵽pstScanChanListInfo�� */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    /* Ȼ��PRL�л�ȡ���Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);

    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildChanScanList_SystemLost
 ��������  : ����������ɨ��Ƶ���б���
 �������  : usPreSrchChanNum ------------ ��ǰ��Ҫ����������Ƶ�����,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
             pstPreSrchChanArray---------- ��ǰ��Ҫ����������Ƶ������ͷָ��,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
  �޸���ʷ     :
 2.��    ��   : 2015��1��5��
   ��    ��   : c00299063
   �޸�����   : ��װԭ�����������ظ���������
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_SystemLost(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{

    CNAS_XSD_OOC_SCAN_STRATEGY_ENUM_UINT8                   enOocScanStrategy;
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocScheduleInfo = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstOrigFreq        = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru0SysId;

    pstOocScheduleInfo = CNAS_XSD_GetOocScheduleInfo();

    /*�������ظ�Ƶ�����������Ƶ���б� */
    CNAS_XSD_BuildNormalSystemLostScanChanlist(pstScanChanList);

    enOocScanStrategy = pstOocScheduleInfo->stConfigInfo.enOocScanStrategy;

    NAS_MEM_SET_S(&stMru0SysId, sizeof(stMru0SysId), 0, sizeof(stMru0SysId));

    if (VOS_FALSE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        return;
    }

    pstOrigFreq       = &(stMru0SysId.stFreq);

    switch (enOocScanStrategy)
    {
        case CNAS_XSD_OOC_SCAN_REACQ_0_1_2_3_4S:
            CNAS_XSD_AddOrigChanToScanChanlist_REACQ_0_1_2_3_4s(pstScanChanList, pstOrigFreq);
            break;

        case CNAS_XSD_OOC_SCAN_PING_5:
            CNAS_XSD_AddOrigChanToScanChanlist_PING_5(pstScanChanList, pstOrigFreq);
            break;

        case CNAS_XSD_OOC_SCAN_2_7:
            CNAS_XSD_AddOrigChanToScanChanlist_2_7(pstScanChanList, pstOrigFreq);
            break;

        case CNAS_XSD_OOC_SCAN_NORMAL:

            break;
        default:

            break;

    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_AvailableTimerExpired
 ��������  : ѡ����ʱ����ʱ������ɨ��Ƶ���б��ʼ��
 �������  : usPreSrchChanNum ------------ ��ǰ��Ҫ����������Ƶ�����,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
             pstPreSrchChanArray---------- ��ǰ��Ҫ����������Ƶ������ͷָ��,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��11��28��
   ��    ��   : c00299063
   �޸�����   : ��¼��ǰ��������
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_AvailableTimerExpired(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    /* Ŀǰ����,�ó�����system lost���������б��߼�һ�� */
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_CallReleased
 ��������  : �����ͷų�����ɨ��Ƶ���б���
 �������  : usPreSrchChanNum ------------ ��ǰ��Ҫ����������Ƶ�����,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
             pstPreSrchChanArray---------- ��ǰ��Ҫ����������Ƶ������ͷָ��,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��7��9��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
 3.��    ��   : 2015��12��21��
   ��    ��   : w00242748
   �޸�����   : DTS2015121511023:call release�������Դ���ȼ������

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_CallReleased(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU                *pstCallRelAnyCampOnFreq = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stTmpScanChanInfo;
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru0SysId;
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru1SysId;
    VOS_UINT16                                              i;

    /***********************************************************************************************
     * cdg143 4.6:
     * If MS fails to acquire the last channel being used in Traffic state, it shall try to acquire
     * the channel that is listed in MRU[0].
     * If MS fails to acquire MRU[0], it shall perform system lost algorithm based on MRU[0].
     * ����cdg143��Э�飬call releaseƵ�㹹�찴��"�����ͷ�ʱ��Ƶ��+MRU0", ��������Ƶ�㲶��ʧ�ܣ���
     * ����system lost��������MRU[0]���죬�������scan list�б�����һ�ι������, �б����¹���:
     * ��ʷƵ�� + MRU[0] + GEO LIST(ORDER BY MRU LIST) + MRU LIST + ���ų���Ƶ�� + PRL ACQ RECORD LIST
     **********************************************************************************************/

    /***********************************************************************************************
     * 1. ��Ӻ����ͷ�ʱ��Ƶ��
     **********************************************************************************************/
    /* �Ƚ�pstPreSrchChanArray�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    for (i = 0; i < usPreSrchChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /***********************************************************************************************
     * 2. ���MRU[0]Ƶ��
     **********************************************************************************************/
    /* �ٽ�MRU[0]�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan   = stMru0SysId.stFreq;
        stTmpScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    if (VOS_TRUE == g_CtrlCallRelScanList)
    {
        /***********************************************************************************************
         * 3. ����call release�״���Ҫͬ����Ƶ��
         **********************************************************************************************/
        pstCallRelAnyCampOnFreq = CNAS_XSD_GetCallRelAnyCampOnFreqListAddr();
        pstCallRelAnyCampOnFreq->usChanNum = pstScanChanList->usTotalNum;
        for (i = 0; i < CNAS_MIN(pstCallRelAnyCampOnFreq->usChanNum, CNAS_XSD_CALL_REL_SYNC_MAX_FREQ_NUM); i++)
        {
            pstCallRelAnyCampOnFreq->astFreq[i].enBandClass = pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass;
            pstCallRelAnyCampOnFreq->astFreq[i].usChannel   = pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel;
        }
    }

    if (VOS_TRUE == CNAS_XSD_GetMru1SysId(&stMru1SysId))
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan   = stMru1SysId.stFreq;
        stTmpScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_EmcCallReleased
 ��������  : ���������ͷų�����ɨ��Ƶ���б���
 �������  : usPreSrchChanNum ------------ ��ǰ��Ҫ����������Ƶ�����,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
             pstPreSrchChanArray---------- ��ǰ��Ҫ����������Ƶ������ͷָ��,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��7��9��
   ��    ��   : h00313353
   �޸�����   : iteration 17����

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_EmcCallReleased(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stTmpScanChanInfo;
    VOS_UINT16                                              i;

    /***********************************************************************************************
     * 1. ��Ӻ����ͷ�ʱ��Ƶ��
     **********************************************************************************************/
    /* �Ƚ�pstPreSrchChanArray�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    for (i = 0; i < usPreSrchChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_SystemLostSkipMru0
 ��������  : ͬ�������������б�ֻ�ǽ�MRU0��scanList�����
 �������  : usPreSrchChanNum ------------ ��ǰ��Ҫ����������Ƶ�����,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
             pstPreSrchChanArray---------- ��ǰ��Ҫ����������Ƶ������ͷָ��,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��26��
   ��    ��   : m00312079
   �޸�����   : DTS2015070400587:ͬ�������������б�ֻ�ǽ�MRU0��scanList�����

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_SystemLostSkipMru0(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    VOS_UINT32                              ulLoop;

    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum,
                                          pstPreSrchChanArray,
                                          pstScanChanList);

    if (pstScanChanList->usTotalNum > 1)
    {
        /* ��MRU0ɾ�� */
        for (ulLoop = 0; ulLoop < (VOS_UINT32)pstScanChanList->usTotalNum - 1; ulLoop++)
        {
            NAS_MEM_MOVE_S(&pstScanChanList->pstScanChanInfo[ulLoop],
                           sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU),
                           &pstScanChanList->pstScanChanInfo[ulLoop + 1],
                           sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));
        }

        NAS_MEM_SET_S(&pstScanChanList->pstScanChanInfo[ulLoop],
                      sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU),
                      0x00,
                      sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        pstScanChanList->usTotalNum--;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_PowerOnInitSearch
 ��������  : �ϵ翪������һ���޿�����������Xģ���ѣ�ֻΪ�˻�ȡXģλ����Ϣ��ֻ������ų���Ƶ��
 �������  : usPreSrchChanNum ------------ ��ǰ��Ҫ����������Ƶ�����,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
             pstPreSrchChanArray---------- ��ǰ��Ҫ����������Ƶ������ͷָ��,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��12��10��
   ��    ��   : l00324781
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_PowerOnInitSearch(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    /* �����ų���1X Ƶ����뵽pstScanChanListInfo�� */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex    = 0;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_OrderScanListByMruList
 ��������  : scan list is ordered according MRU list,
 �������  : pstScanChanList -- scan list
             pstMruList      -- MRU list
 �������  : none
 �� �� ֵ  : none
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2/12/2014
   ��    ��   : y00245242
   �޸�����   : create
*****************************************************************************/
VOS_VOID CNAS_XSD_OrderScanListByMruList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList,
    CNAS_XSD_MRU_LIST_STRU             *pstMruList
)
{
    VOS_UINT8                           i;
    VOS_UINT16                          j;

    for (i = CNAS_MIN(pstMruList->ucSysNum, CNAS_XSD_MAX_MRU_SYS_NUM); i > 0; i--)
    {
        for (j = 0; j < pstScanChanList->usTotalNum; j++)
        {
            /* �ҵ�Ƶ���򽫶�Ӧ��Ƶ��ɾ��,���ҵ�Ƶ����뵽����ͷ�� */
            if ((pstMruList->astSystem[i-1].stFreq.enBandClass == pstScanChanList->pstScanChanInfo[j].stFreqChan.enBandClass)
             && (pstMruList->astSystem[i-1].stFreq.usChannel   == pstScanChanList->pstScanChanInfo[j].stFreqChan.usChannel))
            {
                if (0 != j)
                {
                    NAS_MEM_MOVE_S(&(pstScanChanList->pstScanChanInfo[1]),
                                   sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * (pstScanChanList->usTotalNum - 1),
                                   &(pstScanChanList->pstScanChanInfo[0]),
                                   sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * j);
                }

                pstScanChanList->pstScanChanInfo[0].stFreqChan = pstMruList->astSystem[i-1].stFreq;

                break;
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetLastIndexOfSameOrMorePreferredThanSpecifiedSystemInGeo
 ��������  : get the last index of system that is same or more preferred than the
             specified system in GEO.

 �������  : pstGeoListInfo -- orignal system GEO information

 �������  : pstScanChanList -- return silent normal call scan list

 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2/12/2014
   ��    ��   : y00245242
   �޸�����   : create
 2.��    ��   : 1/17/2015
   ��    ��   : y00307564
   �޸�����   : ��TQE
 3.��    ��   : 4/17/2015
   ��    ��   : c00299063
   �޸�����   : DTS2015032505314
*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetSystemIndexOfSameOrMorePreferredThanSpecifiedSystemInGeo(
    VOS_UINT16                                              usSysMatchedIndex,
    CNAS_PRL_MATCHED_GEO_INFO_STRU                         *pstMatchedGeoInfo
)
{
    VOS_UINT16                          usGeoEndIndex;
    VOS_UINT16                          i;

    /* get end index in GEO */
    usGeoEndIndex = pstMatchedGeoInfo->usGeoFirstSysRecIndex + pstMatchedGeoInfo->usGeoSysRecNum - 1;

    for (i = usSysMatchedIndex; i <= usGeoEndIndex; i++)
    {
        if (VOS_NULL_PTR == CNAS_PRL_GetSpecifiedPrlSysRecord(i))
        {
            continue;
        }

        if (CNAS_PRL_RELATIVE_PRI_MORE == CNAS_PRL_GetSpecifiedPrlSysRecord(i)->enPriInd)
        {
            return i;
        }
    }

    return usGeoEndIndex;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildCallRedialScanChanListUponOrigSystemInGeo
 ��������  : construct scan list when orignal system is in GEO.
 �������  : pstGeoListInfo -- orignal system GEO information

 �������  : pstScanChanList -- return silent normal call scan list

 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2/12/2014
   ��    ��   : y00245242
   �޸�����   : create
 2.��    ��   : 1/17/2015
   ��    ��   : y00307564
   �޸�����   : ��TQE
 3.��    ��   : 17/1/2015
   ��    ��   : y00245242
   �޸�����   : home SID/NID list����
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildCallRedialScanChanListUponOrigSystemInGeo(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstOrigSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT16                                              usIndex;
    VOS_UINT8                                               i;
    VOS_UINT16                                              j;
    CNAS_PRL_SID_NID_MATCH_LVL_ENUM_UINT16                  enMatchLvl;
    VOS_UINT16                                              usSameOrHighIndex;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstAcqRecord = VOS_NULL_PTR;
    VOS_UINT16                                              usGeoEndIndex;
    VOS_UINT8                                               ucIsHomeSidNid;
    CNAS_PRL_1X_SYSTEM_STRU                                 stCurSysInfo;

    /* reference from section 4.7.3 in cdg143:
    If the original system is listed in the PRL system table, only channels that
    are associated with system table entries that are within the current GEO and
    comply with one of the following criteria shall be placed into the list:

    - System table entries that are same or more preferred than the original system

    - System table entries that have a home roaming indicator (as defined in Req. 2.6.2).
    */

    for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        enMatchLvl = CNAS_PRL_Get1xSysMatchSysRecordIndexInGeo(pstOrigSysInfo,
                                                               &(pstGeoListInfo->astGeoInfoList[i]),
                                                               &usIndex);

        /* Actually, it should not happen. Or somewhere is error! */
        if (CNAS_PRL_SID_NID_MATCH_LVL_NOT_MATCH == enMatchLvl)
        {
            continue;
        }

        /* add freqs in scan list that System table entries are same or more preferred than the original system */
        usSameOrHighIndex = CNAS_XSD_GetSystemIndexOfSameOrMorePreferredThanSpecifiedSystemInGeo(usIndex,
                                                                                                 &(pstGeoListInfo->astGeoInfoList[i]));
        for (j = pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex; j <= usSameOrHighIndex; j++)
        {
            pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(j);

            if (VOS_NULL_PTR == pstSysRecord)
            {
                continue;
            }

            NAS_MEM_SET_S(&stCurSysInfo, sizeof(stCurSysInfo), 0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

            stCurSysInfo.usNid = pstSysRecord->u.st1xAndIs95Id.usNid;
            stCurSysInfo.usSid = pstSysRecord->u.st1xAndIs95Id.usSid;

            ucIsHomeSidNid = CNAS_PRL_IsCurrentSystemInHomeSidNidList(&stCurSysInfo);

            if ((CNAS_PRL_PREF_NEG_SYS_PREF == pstSysRecord->enPrefNegSys)
            ||  (VOS_TRUE                   == ucIsHomeSidNid))
            {
                pstAcqRecord = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);
                if (VOS_NULL_PTR == pstAcqRecord)
                {
                    continue;
                }

                CNAS_XSD_AddSpecPrlAcqRecInScanChanList(pstAcqRecord, pstScanChanList);
            }
        }

        /* Add freqs in scan list that System table entries have a home roaming indicator */
        usGeoEndIndex = pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex + pstGeoListInfo->astGeoInfoList[i].usGeoSysRecNum - 1;
        for (j = usSameOrHighIndex + 1; j <= usGeoEndIndex; j++)
        {
            pstSysRecord = CNAS_PRL_GetSpecifiedPrlSysRecord(j);

            if (VOS_NULL_PTR == pstSysRecord)
            {
                continue;
            }

            /* home roaming indicator */
            if (CNAS_PRL_SYS_ROAMING_STATUS_OFF == pstSysRecord->enRoamingInd)
            {
                pstAcqRecord = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord->usAcqIndex);
                if (VOS_NULL_PTR == pstAcqRecord)
                {
                    continue;
                }

                CNAS_XSD_AddSpecPrlAcqRecInScanChanList(pstAcqRecord, pstScanChanList);
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildCallRedialScanChanList
 ��������  : ���п�ʼʱ��������ز�����Ƶ���б�
 �������  : pstOrigSysInfo---------------���з����ϵͳ,���δפ��,ָ��Ϊ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��18��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildCallRedialScanChanList(
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampSysInfo
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU                                 stOrigSysInfo;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stGeoListInfo;

    pstScanChanList = CNAS_XSD_GetCallRedialScanChanListAddr();

    CNAS_XSD_AllocMemoryForScanChanList(pstScanChanList, CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL);

    if (VOS_NULL_PTR == pstScanChanList->pstScanChanInfo)
    {
        return;
    }

    /* check current camp on system exist or not */
    if (VOS_TRUE == pstCurCampSysInfo->ucCampOnFlag)
    {
        NAS_MEM_SET_S(&stOrigSysInfo, sizeof(stOrigSysInfo), 0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

        NAS_MEM_CPY_S(&stOrigSysInfo, sizeof(stOrigSysInfo), &(pstCurCampSysInfo->stSystem), sizeof(CNAS_PRL_1X_SYSTEM_STRU));

        NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

        CNAS_XSD_GetMostMatched1xGeoList(&stOrigSysInfo, &stGeoListInfo);

        /* check whether or not orignal system is in PRL */
        if (0 != stGeoListInfo.ucGeoNum)
        {
            CNAS_XSD_BuildCallRedialScanChanListUponOrigSystemInGeo(&stOrigSysInfo,
                                                                    &stGeoListInfo,
                                                                    pstScanChanList);
        }
        /* orignal system is not in GEO */
        else
        {
            /* �����ų���1X Ƶ����뵽pstScanChanListInfo�� */
            CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

            /* reference from section 4.7.3 in cdg143:
            - If the original system is not listed in the PRL system table, all channels from
              the PRL acquisition table shall be placed into the list.
            */
            CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);
        }

        /* reference from section 4.7.3 in cdg143:
        - The list should be ordered according to the MRU, then system table entries in the current GEO.

        - The channel over which origination failed shall be placed last in the channels list.
        */

        /* The list should be ordered according to the MRU */
        CNAS_XSD_OrderScanListByMruList(pstScanChanList, CNAS_XSD_GetMruList());

        /* place the failed freq last in the channels list */
        CNAS_XSD_MoveFreqChantoEndOfChanList(&stOrigSysInfo, pstScanChanList);
    }
    else
    {
        /* �Ƚ�MRU�е�Ƶ����Ϣ���ӵ�pstScanChanList�� */
        CNAS_XSD_AddMruListInScanChanList(pstScanChanList);

        /* �����ų���1X Ƶ����뵽pstScanChanListInfo�� */
        CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

        /* Ȼ��PRL�л�ȡ���Ƶ����Ϣ���ӵ�pstScanChanList�� */
        CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);
    }

    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex = 0;

    CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_CALL_REDIAL_SCAN_CHAN_LIST_IND, pstScanChanList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildEmcCallRedialScanChanList
 ��������  : ���п�ʼʱ������������ز�����Ƶ���б�
 �������  : pstOrigSysInfo---------------���з����ϵͳ,���δפ��,ָ��Ϊ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildEmcCallRedialScanChanList( VOS_VOID )
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList = VOS_NULL_PTR;

    pstScanChanList = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

    CNAS_XSD_AllocMemoryForScanChanList(pstScanChanList, CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL);

    if (VOS_NULL_PTR == pstScanChanList->pstScanChanInfo)
    {
        return;
    }

    /* ����ͬ���ɹ����Ƶ�� */
    CNAS_XSD_AddHistorySyncedSuccFreqListInScanChanlist(pstScanChanList);

    /* ��MRU�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    CNAS_XSD_AddMruListInScanChanList(pstScanChanList);

    /* �����ų���1X Ƶ����뵽pstScanChanListInfo�� */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    /* ��PRL�л�ȡ���Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);

    /* ����ǰ֧�ֵ�PrefƵ����Ϣ���ӵ�pstScanChanListInfo�� */
    CNAS_XSD_AddUePreferredListInScanChanList(pstScanChanList);

    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddOrigChanToScanChanlist_REACQ_0_1_2_3_4s
 ��������  : �ظ���������REACQ_0_1_2_3_4s
 �������  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
             CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��5��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_AddOrigChanToScanChanlist_REACQ_0_1_2_3_4s(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
)
{
    VOS_UINT16                                              i;
    VOS_UINT16                                              usTotalChanNum;
    VOS_UINT16                                              usOrigChanInsertCount;
    VOS_UINT16                                              usChanIntervalCount;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstScanChanInfo    = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstSrcScanChanInfo = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stPreCampChanInfo;
    VOS_UINT16                                              usSrcTotalChanNum;

    usSrcTotalChanNum  = pstScanChanList->usTotalNum;
    pstScanChanInfo    = pstScanChanList->pstScanChanInfo;

    /*��ǰפ��Ƶ����Ϣ */
    NAS_MEM_SET_S(&stPreCampChanInfo, sizeof(stPreCampChanInfo), 0, sizeof(stPreCampChanInfo));
    stPreCampChanInfo.stFreqChan.enBandClass = pstPreCampFreq->enBandClass;
    stPreCampChanInfo.stFreqChan.usChannel   = pstPreCampFreq->usChannel;
    stPreCampChanInfo.enChanStatus           = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    /*����ռ䱣��ԭƵ����Ϣ */
    pstSrcScanChanInfo = PS_MEM_ALLOC(UEPS_PID_XSD, (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    if (VOS_NULL_PTR == pstSrcScanChanInfo)
    {
        return;
    }

    NAS_MEM_SET_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  0,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    NAS_MEM_CPY_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  pstScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    /*��дƵ���б�*/

    usTotalChanNum        = 0;
    usChanIntervalCount   = 0;
    usOrigChanInsertCount = 0;

    /*��Ƶ���б�ͷ��������ǰפ��Ƶ�� */
    *pstScanChanInfo      = stPreCampChanInfo;

    /*Ƶ��������1 */
    usTotalChanNum++;

    /*Ƶ�����������㣬���������1 */
    usOrigChanInsertCount++;

    /*ԭƵ���б�ĵ�һ��ҲΪ��ǰפ��Ƶ�㣬Ŀǰ�Ĵ������� */
    for (i = 1; i < usSrcTotalChanNum; i++)
    {
        if (usChanIntervalCount == usOrigChanInsertCount)
        {
            /*������������Ѿ�����Ĵ�����������ǰפ��Ƶ�� */
            *(pstScanChanInfo + usTotalChanNum)  = stPreCampChanInfo;

            /*Ƶ�����������㣬���������1 */
            usChanIntervalCount = 0;
            usOrigChanInsertCount++;

            /*Ƶ��������1 */
            usTotalChanNum++;
        }

        /*������������Ƶ�� */
        *(pstScanChanInfo + usTotalChanNum)  = *(pstSrcScanChanInfo + i);

        /*���������1 */
        usChanIntervalCount++;

        /*Ƶ��������1 */
        usTotalChanNum++;

    }

    PS_MEM_FREE(UEPS_PID_XSD, pstSrcScanChanInfo);

    pstScanChanList->usTotalNum = usTotalChanNum;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddOrigChanToScanChanlist_PING_5
 ��������  : �ظ���������PING_5
 �������  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
             CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��5��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_AddOrigChanToScanChanlist_PING_5(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
)
{
    VOS_UINT16                                              i;
    VOS_UINT16                                              usTotalChanNum;
    VOS_UINT16                                              usChanIntervalCount;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstScanChanInfo    = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstSrcScanChanInfo = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stPreCampChanInfo;
    VOS_UINT16                                              usSrcTotalChanNum;

    usSrcTotalChanNum  = pstScanChanList->usTotalNum;
    pstScanChanInfo    = pstScanChanList->pstScanChanInfo;

    /*��ǰפ��Ƶ����Ϣ */
    NAS_MEM_SET_S(&stPreCampChanInfo, sizeof(stPreCampChanInfo), 0, sizeof(stPreCampChanInfo));
    stPreCampChanInfo.stFreqChan.enBandClass = pstPreCampFreq->enBandClass;
    stPreCampChanInfo.stFreqChan.usChannel   = pstPreCampFreq->usChannel;
    stPreCampChanInfo.enChanStatus           = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    /*����ռ䱣��ԭƵ����Ϣ */
    pstSrcScanChanInfo = PS_MEM_ALLOC(UEPS_PID_XSD, (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    if (VOS_NULL_PTR == pstSrcScanChanInfo)
    {
        return;
    }

    NAS_MEM_SET_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  0,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    NAS_MEM_CPY_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  pstScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    /*��дƵ���б�*/

    usTotalChanNum      = 0;
    usChanIntervalCount = 0;

    /*��Ƶ���б�ͷ��������ǰפ��Ƶ�� */
    *pstScanChanInfo      = stPreCampChanInfo;

    usTotalChanNum++;

    /*ԭƵ���б�ĵ�һ��ҲΪ��ǰפ��Ƶ�㣬Ŀǰ�Ĵ������� */
    for (i = 1; i < usSrcTotalChanNum; i++)
    {
        if (CNAS_XSD_CHANNEL_REPEAT_INTERVAL == usChanIntervalCount)
        {
            /*������ǰפ��Ƶ�� */
            *(pstScanChanInfo + usTotalChanNum)  = stPreCampChanInfo;

            /*Ƶ������������*/
            usChanIntervalCount = 0;

            /*Ƶ��������1 */
            usTotalChanNum++;
        }

        /*������������Ƶ�� */
        *(pstScanChanInfo + usTotalChanNum)  = *(pstSrcScanChanInfo + i);

        /*���������1 */
        usChanIntervalCount++;

        /*Ƶ��������1 */
        usTotalChanNum++;

    }

    PS_MEM_FREE(UEPS_PID_XSD, pstSrcScanChanInfo);

    pstScanChanList->usTotalNum = usTotalChanNum;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddOrigChanToScanChanlist_PING_5
 ��������  : �ظ���������2_7
 �������  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
             CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��5��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_AddOrigChanToScanChanlist_2_7(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstPreCampFreq
)
{
    VOS_UINT16                                              i;
    VOS_UINT16                                              usTotalChanNum;
    VOS_UINT16                                              usChanIntervalCount;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstScanChanInfo    = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                        *pstSrcScanChanInfo = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stPreCampChanInfo;
    VOS_UINT16                                              usSrcTotalChanNum;

    usSrcTotalChanNum  = pstScanChanList->usTotalNum;
    pstScanChanInfo    = pstScanChanList->pstScanChanInfo;

    /*��ǰפ��Ƶ����Ϣ */
    NAS_MEM_SET_S(&stPreCampChanInfo, sizeof(stPreCampChanInfo), 0, sizeof(stPreCampChanInfo));
    stPreCampChanInfo.stFreqChan.enBandClass = pstPreCampFreq->enBandClass;
    stPreCampChanInfo.stFreqChan.usChannel   = pstPreCampFreq->usChannel;
    stPreCampChanInfo.enChanStatus           = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    /*����ռ䱣��ԭƵ����Ϣ */
    pstSrcScanChanInfo = PS_MEM_ALLOC(UEPS_PID_XSD, (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    if (VOS_NULL_PTR == pstSrcScanChanInfo)
    {
        return;
    }

    NAS_MEM_SET_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  0,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    NAS_MEM_CPY_S(pstSrcScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum),
                  pstScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usSrcTotalChanNum));

    /*��дƵ���б�*/

    usTotalChanNum      = 0;
    usChanIntervalCount = 0;

    /*��Ƶ���б�ͷ��������ǰפ��Ƶ��2�� */
    *pstScanChanInfo      = stPreCampChanInfo;

    usTotalChanNum++;

    *(pstScanChanInfo + usTotalChanNum)  = stPreCampChanInfo;

    usTotalChanNum++;

    /*ԭƵ���б�ĵ�һ��ҲΪ��ǰפ��Ƶ�㣬Ŀǰ�Ĵ������� */
    for (i = 1; i < usSrcTotalChanNum; i++)
    {
        if (CNAS_XSD_CHANNEL_REPEAT_INTERVAL == usChanIntervalCount)
        {
            /*������ǰפ��Ƶ�㣬2�� */
            *(pstScanChanInfo + usTotalChanNum)  = stPreCampChanInfo;

            /*Ƶ��������1 */
            usTotalChanNum++;

            *(pstScanChanInfo + usTotalChanNum)  = stPreCampChanInfo;

            /*Ƶ��������1 */
            usTotalChanNum++;

            /*Ƶ������������*/
            usChanIntervalCount = 0;
        }

        /*������������Ƶ�� */
        *(pstScanChanInfo + usTotalChanNum)  = *(pstSrcScanChanInfo + i);

        /*���������1 */
        usChanIntervalCount++;

        /*Ƶ��������1 */
        usTotalChanNum++;

    }

    PS_MEM_FREE(UEPS_PID_XSD, pstSrcScanChanInfo);

    pstScanChanList->usTotalNum = usTotalChanNum;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildCallRedialScanChanList
 ��������  : ϵͳ����������������Ƶ���б�
 �������  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��18��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildNormalSystemLostScanChanlist(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru0SysId;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stScanChanInfo;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                     stMatchedGeoList;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstGeoChanList  = VOS_NULL_PTR;
    VOS_UINT16                                              usGeoChanNum;
    VOS_UINT32                                              ulRet;
    VOS_UINT16                                              usMaxGeoChanNum;

    CNAS_XSD_AllocMemoryForScanChanList(pstScanChanList, CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST);

    if (VOS_NULL_PTR == pstScanChanList->pstScanChanInfo)
    {
        return;
    }

    /* �б����:MRU[0] + GEO LIST(ORDER BY MRU LIST) + MRU LIST + ���ų���Ƶ�� + PRL ACQ RECORD LIST */

    NAS_MEM_SET_S(&stMatchedGeoList, sizeof(stMatchedGeoList), 0x0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    /* �Ƚ�MRU[0]�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan   = stMru0SysId.stFreq;
        stScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);

        /* ��PRLϵͳ���в���MRU[0]��SID NID���ڵ�GEO LIST */
        CNAS_PRL_Get1xSysGeoList(&stMru0SysId, &stMatchedGeoList);
    }

    if (0 < stMatchedGeoList.ucGeoNum)
    {
        /* calculate the max size of the geo list channel and then alloc memory */
        usMaxGeoChanNum = CNAS_PRL_CalcMatchedGeoListTotalFreqNum(&stMru0SysId, &stMatchedGeoList);

        pstGeoChanList = (CNAS_PRL_FREQENCY_CHANNEL_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * usMaxGeoChanNum);

        if (VOS_NULL_PTR == pstGeoChanList)
        {
            return;
        }

        /* ��GEO�б���ÿ����¼��Ƶ�������Ƶ���б� */
        usGeoChanNum = 0;
        ulRet        = CNAS_XSD_PraseChannelInMatchedGeoList(&stMru0SysId, &stMatchedGeoList, usMaxGeoChanNum, &usGeoChanNum, pstGeoChanList);

        /* �����ɹ� */
        if (VOS_TRUE == ulRet)
        {
            /* �����ҵ���GEO�ж�Ӧ��Ƶ���б���MRU��˳��������� */
            CNAS_XSD_SortChanListByMruList(usGeoChanNum,pstGeoChanList,CNAS_XSD_GetMruList());

            /* ������õ�Ƶ���б�����pstScanChanListInfo�� */
            CNAS_XSD_AddFreqChanListInScanChanList(usGeoChanNum, pstGeoChanList,pstScanChanList);
        }

        PS_MEM_FREE(UEPS_PID_XSD, pstGeoChanList);
    }

    /* �Ƚ���MRU[0]֮��������MRU�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    CNAS_XSD_AddMruListExcludeMru0InScanChanList(pstScanChanList);

    /* �����ų���1X Ƶ����뵽pstScanChanListInfo�� */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    /* Ȼ��PRL�л�ȡ���Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);


    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;

}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearCallRedialScanChanList
 ��������  : ���п�ʼʱ��������ز�����Ƶ���б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��18��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ClearCallRedialScanChanList(VOS_VOID)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList = VOS_NULL_PTR;

    pstScanChanList = CNAS_XSD_GetCallRedialScanChanListAddr();

    if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstScanChanList->pstScanChanInfo);

        pstScanChanList->pstScanChanInfo = VOS_NULL_PTR;
    }

    pstScanChanList->usTotalNum     = 0;
    pstScanChanList->usCurScanIndex = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateScanChanList
 ��������  : ����Ƶ��ɨ���б�
 �������  : pstSrcScanChanList------------����ǰ��Ƶ��ɨ���б�
 �������  : pstDestScanChanList-----------���º��Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��5��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstDestScanChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstSrcScanChanList
)
{
    VOS_UINT16                          i;

    if ((VOS_NULL_PTR == pstSrcScanChanList->pstScanChanInfo)
     || (VOS_NULL_PTR == pstDestScanChanList->pstScanChanInfo))
    {
        return;
    }

    for (i = 0; i < pstSrcScanChanList->usTotalNum; i++)
    {
        pstDestScanChanList->usTotalNum     = pstSrcScanChanList->usTotalNum;
        pstDestScanChanList->usCurScanIndex = pstSrcScanChanList->usCurScanIndex;

        NAS_MEM_CPY_S(&(pstDestScanChanList->pstScanChanInfo[i]),
                      sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU),
                      &(pstSrcScanChanList->pstScanChanInfo[i]),
                      sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_CallRedial
 ��������  : ����ɨ��Ƶ���б���
 �������  : usPreSrchChanNum ------------ ��ǰ��Ҫ����������Ƶ�����,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
             pstPreSrchChanArray---------- ��ǰ��Ҫ����������Ƶ������ͷָ��,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��18��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_CallRedial(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstCallRedialScanChanList = VOS_NULL_PTR;
    VOS_UINT16                          i;

    pstCallRedialScanChanList = CNAS_XSD_GetCallRedialScanChanListAddr();

    CNAS_XSD_UpdateScanChanList(pstScanChanList, pstCallRedialScanChanList);

    /* if the call redial channel list has been synced finished,we should reset
       the index and the channle status. */
    if (pstScanChanList->usCurScanIndex >= pstScanChanList->usTotalNum - 1)
    {
        for (i = 0; i < pstScanChanList->usTotalNum; i++)
        {
            pstScanChanList->pstScanChanInfo[i].enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
        }

        pstScanChanList->usCurScanIndex = 0;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateChanStatusInScanChanList
 ��������  : ����ָ��Ƶ����ɨ��Ƶ���б��е�Ƶ������״̬
 �������  : usBeginScanListIndex --------------- ��ʼ��index
             pstChannel--------------- ָ��Ƶ��
             enChanStatus--------------------Ƶ��״̬
             pstScanChanList -----------------��ǰ��Ƶ��ɨ���б�
 �������  : pstScanChanList-------------------��ǰ��Ƶ��ɨ���б�
 �� �� ֵ  : VOS_UINT16 -- ���ص�ǰˢ�µ�Ƶ����scan list�е�����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��9��8��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateChanStatusInScanChanList(
    VOS_UINT16                                              usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstChannel,
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enChanStatus,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT16                          i;

    for (i = usBeginScanListIndex; i < pstScanChanList->usTotalNum; i++)
    {
        if ((pstChannel->enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass)
         && (pstChannel->usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel))
        {
            pstScanChanList->pstScanChanInfo[i].enChanStatus = enChanStatus;

            return i;
        }
    }

    /* ���û���ҵ�����Ȼ���ص�ǰ������ */
    return usBeginScanListIndex;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateSysFreqStatusBySysInGeoSysRecordSrchList
 ��������  : ����ָ��ϵͳ�ڲ���ϵͳ�б��е�״̬
 �������  : pstSysInfo--------------- ָ��ϵͳ
             enSysStatus----------------ϵͳ״̬
             pstSysAcqList ---------------ϵͳ�����б�
 �������  : pstSysAcqList------------------ϵͳ�����б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��16��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateSysFreqStatusBySysInGeoSysRecordSrchList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                          i;

    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++)
    {
        if (VOS_TRUE == CNAS_PRL_Is1xSysMatched(pstSysInfo, &(pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys)))
        {
            /* ���ظ�ˢ�²������ϵͳ״̬ */
            if (CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED == pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus)
            {
                pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus = enSysStatus;
                break;
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateSysFreqStatusByFreqChanInGeoSysRecordSrchList
 ��������  : ����ָ����Ƶ����ϵͳ�����б��в��Ҷ�Ӧ��ϵͳ�б�����״̬
 �������  : pstFreqChan--------------- ָ��Ƶ��
             enSysStatus----------------ϵͳ״̬
             pstSysAcqList ---------------ϵͳ�����б�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��28��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��7��27��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/

VOS_VOID CNAS_XSD_UpdateSysFreqStatusByFreqChanInGeoSysRecordSrchList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstSysAcqList
)
{
    VOS_UINT16                          i;

    for (i = 0; i < pstSysAcqList->usTotalNum; i++)
    {
        if ((pstFreqChan->enBandClass == pstSysAcqList->pstAcqSysInfo[i].stAcqSys.stFreq.enBandClass)
         && (pstFreqChan->usChannel   == pstSysAcqList->pstAcqSysInfo[i].stAcqSys.stFreq.usChannel))
        {
             /* ˢ��Ƶ��״̬ */
            pstSysAcqList->pstAcqSysInfo[i].enSysStatus = enSysStatus;
        }
    }


    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RemoveExpiredFreqFromAvoidList
 ��������  : ��鵽�ڵ�Ƶ�㣬�����Ƶ�㵽�ڣ���avoid�б����޳���Ƶ��
 �������  : ��

 �������  : ��

 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_RemoveExpiredFreqFromAvoidList(VOS_VOID)
{
    VOS_UINT32                                              ulCurSlice;
    VOS_UINT32                                              ulRunSliceNum;
    VOS_UINT8                                               i;
    CNAS_XSD_AVOID_FREQ_INFO_STRU                          *pstAvoidFreqInfo = VOS_NULL_PTR;


    /* ��ȡ��ǰϵͳ��slice */
    ulCurSlice = CNAS_XSD_GetSystemSlice();

    /* ����avoid�б������е�Ƶ��ĵ���slice */
    for (i = 0; i < CNAS_MIN(CNAS_XSD_GetAvoidFreqListNum(), CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        pstAvoidFreqInfo = CNAS_XSD_GetAvoidFreqFromAvoidList(i);

        if (VOS_NULL_PTR == pstAvoidFreqInfo)
        {
            /* ��ָ�뱣�� */
            continue;
        }

        if (VOS_FALSE == pstAvoidFreqInfo->ucAvoidFlag)
        {
            continue;
        }

        if (ulCurSlice < pstAvoidFreqInfo->ulStartSlice)
        {
            /* ���Ƿ�ת���� */
            ulRunSliceNum = CNAS_XSD_MAX_SLICE_VALUE- pstAvoidFreqInfo->ulStartSlice + ulCurSlice + 1;
        }
        else
        {
            ulRunSliceNum = ulCurSlice - pstAvoidFreqInfo->ulStartSlice;
        }

        /* ����Ѿ����е�slice��Ŀ���ڵ��ڵ��ڵ�slice��Ŀ����avoidƵ���б����޳���Ƶ�� */
        if (ulRunSliceNum >= pstAvoidFreqInfo->ulExpiredSliceNum)
        {
            CNAS_XSD_DeleteAvoidFlagFromAvoidList(i);

            /* ���ڽ����Ƶ�㣬����ˢ��scan listƵ��Ϊδ������ȷ�������������� */
            (VOS_VOID)CNAS_XSD_UpdateChanStatusInScanChanList(0,
                                                              &(pstAvoidFreqInfo->stAvoidFreq),
                                                              CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED,
                                                              CNAS_XSD_GetScanChanListAddr());


        }
    }

    /*���avoid�б��в����ڽ��ñ�ǣ���ʾû�б����õ�Ƶ�㣬ֹͣ��ʱ�� */
    if (VOS_FALSE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
    {
        CNAS_XSD_StopTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER);
    }

    CNAS_XSD_LogAvoidFreqList(CNAS_XSD_GetAvoidFreqListAddr());
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsCurFreqAvoided
 ��������  : ��鵱ǰƵ���Ƿ���avoid�б��б���
 �������  : pstFreqChan -- Ƶ����Ϣָ��

 �������  : ��

 �� �� ֵ  : VOS_TRUE  -- ��ǰƵ�㱻��
             VOS_FALSE -- ��ǰƵ�㲻����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsCurFreqAvoided(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqChan
)
{
    VOS_UINT8                           i;
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;

    /* ����avoid�б������е�Ƶ�㣬��ǰƵ����avoid�б���, ����VOS_TRUE */
    pstAvoidFreqList = CNAS_XSD_GetAvoidFreqListAddr();

    for (i = 0; i < CNAS_MIN(pstAvoidFreqList->ucAvoidFreqNum, CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        if (VOS_FALSE == pstAvoidFreqList->astAvoidFreqInfo[i].ucAvoidFlag)
        {
            continue;
        }

        if ((pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq.enBandClass == pstFreqChan->enBandClass)
         && (pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq.usChannel   == pstFreqChan->usChannel))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetNextScanChanList
 ��������  : ��ȡ�¸�δɨ�����Ƶ���б�
 �������  : ucInsertMru0Freq  ----------����MRU0Ƶ��
             usCurScanChanIndex----------��ǰɨ�赽��Ƶ������
             pstScanChanList------��ǰ��ɨ��Ƶ���б�
 �������  : pusDstChanNum-----------��ȡ����Ƶ�����
             pstDstChan--------------��ȡ����Ƶ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��05��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��1��05��
   ��    ��   : y00245242
   �޸�����   : ����OOC��������

 3.��    ��   : 2015��7��21��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_GetNextScanChanList(
    VOS_UINT16                          usCurScanChanIndex,
    VOS_UINT16                         *pusDstChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstDstChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList,
    VOS_UINT32                          ulIsAvoidListEnable
)
{
    VOS_UINT16                          usChanScanNum;
    VOS_UINT16                          i;
    VOS_UINT16                          j;

    /* ��ǰ��δɨ���Ƶ���ܸ��� */
    usChanScanNum   = pstScanChanList->usTotalNum - usCurScanChanIndex;

    *pusDstChanNum = 0;

    /* scan list����Ϊ0��ֱ���˳� */
    if (0 == usChanScanNum)
    {
        return;
    }

    /* ���avoid�б��е��ڵ�Ƶ�㣬�ӱ����޳� */
    CNAS_XSD_RemoveExpiredFreqFromAvoidList();

    /* ���һ��ȡ32��Ƶ�㷢��AS����ͬ�� */
    if (CNAS_CAS_1X_MAX_FREQ_NUM <= usChanScanNum)
    {
        usChanScanNum = CNAS_CAS_1X_MAX_FREQ_NUM;
    }

    j = 0;

    for (i = usCurScanChanIndex; i < pstScanChanList->usTotalNum; i++)
    {
        /* ͬ�����ڵ�Ƶ���Ҳ�������� */
        if ((CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED    == pstScanChanList->pstScanChanInfo[i].enChanStatus)
         || (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST == pstScanChanList->pstScanChanInfo[i].enChanStatus))
        {
            /* �����ǰƵ����avoid�б��У�������һ����� */
            if ((VOS_TRUE   == CNAS_XSD_IsCurFreqAvoided(&pstScanChanList->pstScanChanInfo[i].stFreqChan))
             && (VOS_TRUE   == ulIsAvoidListEnable))
            {
                /* ���洦��ԭ��:
                 *  ��Ƶ��ɨ���б���ȡδͬ�����ҷ�avoid��Ƶ�㣬����avoid��Ƶ�㴦������:
                 *  1) ���pstDstChan�е�Ƶ�����Ϊ0��������ȡδͬ�����ҷ�avoid��Ƶ�㣻
                 *  2) ���pstDstChan�е�Ƶ�������Ϊ0������ѭ����
                 *  ԭ��: ��ΪASͬ��һ��Ƶ��ʱ��ʱ����ܻ�ܳ�������һ��Ƶ��ͬ��ʱ���ܿ��ܱ�����
                 *        ��Ƶ���Ѿ����������avoidƵ������������ᡣ
                 */
                if (0 == j)
                {
                    /* ���pstDstChan��Ƶ�����Ϊ0��������һ��Ƶ���� */
                    continue;
                }
                else
                {
                    /* ���pstDstChan��Ƶ�������Ϊ0������ѭ���� */
                    break;
                }
            }

            pstDstChan[j].enBandClass = pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass;
            pstDstChan[j].usChannel   = pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel;

            j++;

            if (j >= usChanScanNum)
            {
                break;
            }
        }
    }

    (*pusDstChanNum) = j;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsSpecifiedFreqSrchedInGeoSysRecordSrchList
 ��������  : GEOϵͳ��¼�����б��Ƿ�������
 �������  : pstFreq       -- ָ����Ƶ��
             pstAcqSysInfo -- �����ϵͳ��Ϣ
 �������  :

 �� �� ֵ  : VOS_TRUE  -- �Ѿ�������
             VOS_FALSE -- δ������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��7��6��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
VOS_UINT8 CNAS_XSD_IsSpecifiedFreqSrchedInGeoSysRecordSrchList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU  *pstAcqSysInfo
)
{
    /* δ�������ϵͳ�ҷ�NEG��ϵͳ,��ͬƵ���������� */
    if ((pstFreq->enBandClass                    == pstAcqSysInfo->stAcqSys.stFreq.enBandClass)
     && (pstFreq->usChannel                      == pstAcqSysInfo->stAcqSys.stFreq.usChannel)
     && ((CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED    == pstAcqSysInfo->enSysStatus)
      || (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST == pstAcqSysInfo->enSysStatus)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetNextSysSyncListFromGeoSysRecordSrchList
 ��������  : ��ȡ�¸�δ�������ϵͳ�б�
 �������  : pstSysAcqList  -- ��ǰ��ϵͳ�����б�
 �������  : pusScanChanNum -- �����´�ͬ��������Ƶ����Ŀ
             pstScanList    -- ��ȡ���·�����AS��scan list
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��7��4��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_GetNextSysSyncListFromGeoSysRecordSrchList(
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList,
    VOS_UINT16                                             *pusScanChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstScanList
)
{
    VOS_UINT16                                              i;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stTmpChannel;

    *pusScanChanNum = 0;

    /* ���avoid�б��е��ڵ�Ƶ�� */
    CNAS_XSD_RemoveExpiredFreqFromAvoidList();

    CNAS_XSD_UpdateGeoSysRecordListInfoAccordingToScanChanList(pstGeoSysRecSrchList);

    for (i = 0; ((i < pstGeoSysRecSrchList->usTotalNum) && (*pusScanChanNum < CNAS_CAS_1X_MAX_FREQ_NUM)); i++)
    {
        stTmpChannel = pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq;

        /*******************************************************************************************
         *  1. �����ǰlevel�Ѿ�ȫ��ȡ�ֹ꣬ͣ��scan list�б�ע: �����ǰlevel��Ƶ��û����Ҫ�����ģ�
         *     ������һ��levelϵͳ��¼��������
         ******************************************************************************************/
        if (pstGeoSysRecSrchList->usCurSrchLevel != pstGeoSysRecSrchList->pstAcqSysInfo[i].usLevel)
        {
            if (0 != *pusScanChanNum)
            {
                /* ��ͬlevel���ȼ���ϵͳ�Ѿ�ȫ��ȡ�� */
                return;
            }
            else
            {
                /* ��ǰGEO��û����Ҫ������Ƶ�㣬ȡGEO����һ��level��ϵͳ��Ƶ��ȥ���� */
                pstGeoSysRecSrchList->usCurSrchLevel = pstGeoSysRecSrchList->pstAcqSysInfo[i].usLevel;
            }
        }

        /*******************************************************************************************
         *  2. ��鵱ǰƵ���Ƿ񱻽������������������Ƶ��
         ******************************************************************************************/
        if (VOS_TRUE == CNAS_XSD_IsCurFreqAvoided(&stTmpChannel))
        {
            continue;
        }

        /*******************************************************************************************
         *  3. ��ǰƵ����scan list�У�ͬ�������ڵģ�������
         ******************************************************************************************/
        if (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST == CNAS_XSD_GetScanChanStatusInScanChanList(&stTmpChannel,
                                                                                                  CNAS_XSD_GetScanChanListAddr()))
        {
            continue;
        }

        /*******************************************************************************************
         *  4. �������͸�AS��ͬ��list���Ѿ����ڵ�Ƶ��
         ******************************************************************************************/
        if (VOS_TRUE == CNAS_XSD_IsChannelInSndCasSyncList(&stTmpChannel, pstScanList, *pusScanChanNum))
        {
            continue;
        }

        /*******************************************************************************************
         *  5. �����������������ڵ�ϵͳ
         ******************************************************************************************/
        if (VOS_FALSE == CNAS_XSD_IsSpecifiedFreqSrchedInGeoSysRecordSrchList(&stTmpChannel,
                                                                              &pstGeoSysRecSrchList->pstAcqSysInfo[i]))
        {
            continue;
        }

        /*******************************************************************************************
         *  6. ���scan list�б�
         ******************************************************************************************/
        pstScanList[*pusScanChanNum].enBandClass = pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq.enBandClass;
        pstScanList[*pusScanChanNum].usChannel   = pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq.usChannel;

        (*pusScanChanNum)++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_PraseChannelInMatchedGeoList
 ��������  : ����ƥ���GEO�б��������Ӧ��Ƶ��
 �������  : pstMatchedGeoList------ƥ���GEO�б�
             usMaxGeoChanNum--------����GEOƵ�����
 �������  : pusGeoChanNum-------����GEO���Ƶ�����
             pstGeoChanList------����GEO���Ƶ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��5��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 3/1/2015
   ��    ��   : w00176964
   �޸�����   : place the alloc memory logic outside of this function
 3.��    ��   : 2015��08��27��
   ��    ��   : t00323010
   �޸�����   : DTS2015081904804 clear pc-lint warning
*****************************************************************************/
VOS_UINT32 CNAS_XSD_PraseChannelInMatchedGeoList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstMatchedGeoList,
    VOS_UINT16                                              usMaxGeoChanNum,
    VOS_UINT16                                             *pusGeoChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstGeoChanList
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          j;
    VOS_UINT16                          usIndex;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec  = VOS_NULL_PTR;
    CNAS_PRL_EXT_SYS_RECORD_STRU       *pstSysRecord  = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stAcqRecFreqInfo;
    VOS_UINT16                          usSysRecNum;
    VOS_UINT16                          usTotalSysRecNum;

    usSysRecNum         = 0;
    usTotalSysRecNum    = 0;

    /* ����PCLINT 429�澯 */
    pstGeoChanList = pstGeoChanList;

    /* ���㵱ǰ���ܵ����ϵͳ��¼�� */
    for (i = 0; i < (VOS_UINT8)CNAS_MIN(pstMatchedGeoList->ucGeoNum, CNAS_PRL_MAX_MATCHING_GEO_NUM); i++)
    {
        usTotalSysRecNum += pstMatchedGeoList->astGeoInfoList[i].usGeoSysRecNum;
    }

    pstSysRecord = PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU) * usTotalSysRecNum);

    /* ����ǿ�ָ�룬ֱ�ӷ��� */
    if (VOS_NULL_PTR == pstSysRecord)
    {
        return VOS_FALSE;
    }

    CNAS_PRL_BuildGeoSysRecList(pstSysInfo, pstMatchedGeoList, VOS_TRUE, &usSysRecNum, pstSysRecord);

    *pusGeoChanNum = 0;
    usIndex        = 0;

    for (i = 0; i < usSysRecNum; i++)
    {
        /* ��ȡPRL�л�ȡ��ָ�� */
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstSysRecord[i].usAcqIndex);

        /* ��ָ����б��� */
        if (VOS_NULL_PTR == pstPrlAcqRec)
        {
            continue;
        }

        /* �����жϣ�HRPDƵ�㲻��� */
        if (CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD == pstPrlAcqRec->enAcqType)
        {
            continue;
        }

        CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stAcqRecFreqInfo);

        for (j = 0; (j < CNAS_MIN(stAcqRecFreqInfo.ulNum, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM)) && (*pusGeoChanNum < usMaxGeoChanNum); j++)
        {
            if (VOS_FALSE == CNAS_XSD_IsChannelInChannelList(&(stAcqRecFreqInfo.astFreqInfo[j]), *pusGeoChanNum, pstGeoChanList))
            {
                pstGeoChanList[usIndex++] = stAcqRecFreqInfo.astFreqInfo[j];

                (*pusGeoChanNum)++;
            }
        }
    }

    /* �ͷ��ڴ�pstSysRecord */
    PS_MEM_FREE(UEPS_PID_XSD, pstSysRecord);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_SortChanListByMruList
 ��������  : ����MRU�б����֪��Ƶ���б��������
 �������  : usChanNum------ԭʼ��Ƶ���б����
             pstChanList----ԭʼ��Ƶ���б�
             pstMruList----MRU�б�
 �������  : usChanNum------�ź����Ƶ���б����
             pstChanList----�ź����Ƶ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��85��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
/*lint -e429*/
VOS_VOID CNAS_XSD_SortChanListByMruList(
    VOS_UINT16                          usChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChanList,
    CNAS_XSD_MRU_LIST_STRU             *pstMruList
)
{
    VOS_UINT8                           i;
    VOS_UINT16                          j;

    for (i = CNAS_MIN(pstMruList->ucSysNum, CNAS_XSD_MAX_MRU_SYS_NUM); i > 0; i--)
    {
        for (j = 0; j < usChanNum; j++)
        {
            /* �ҵ�Ƶ���򽫶�Ӧ��Ƶ��ɾ��,���ҵ�Ƶ����뵽����ͷ�� */
            if ((pstMruList->astSystem[i-1].stFreq.enBandClass == pstChanList[j].enBandClass)
             && (pstMruList->astSystem[i-1].stFreq.usChannel   == pstChanList[j].usChannel))
            {
                if (0 != j)
                {
                    NAS_MEM_MOVE_S(&(pstChanList[1]),
                                   sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (usChanNum - 1),
                                   &(pstChanList[0]),
                                   sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * j);
                }

                pstChanList[0] = pstMruList->astSystem[i-1].stFreq;
                break;
            }
        }
    }

    return;
}
/*lint +e429*/

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetScanChanStatusInScanChanList
 ��������  : �ж�ָ����Ƶ����ɨ��Ƶ���б��е�ɨ��״̬
 �������  : pstFreq-------------ָ����Ƶ��
             pstScanChanList-------Ƶ��ɨ���б�
 �������  : ��
 �� �� ֵ  : Ƶ��ɨ��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��21��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/

CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8 CNAS_XSD_GetScanChanStatusInScanChanList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                              i;
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8    enChanSta;

    enChanSta       = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    for (i = 0; i < pstScanChanList->usTotalNum; i++)
    {
        if ((pstFreq->enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass)
         && (pstFreq->usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel))
        {
            enChanSta       = pstScanChanList->pstScanChanInfo[i].enChanStatus;

            break;
        }
    }

    return enChanSta;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddFreqChanListInScanChanList
 ��������  : ��Ƶ��ɨ���б�������Ƶ��ɨ���б�
 �������  : usChanNum---------Ƶ���б����
             pstChanList------Ƶ���б�
 �������  : pstScanChanList-------------����PRL�л�ȡ��¼�б���Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -e429*/
VOS_VOID CNAS_XSD_AddFreqChanListInScanChanList(
    VOS_UINT16                          usChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stScanChanInfo;

    for (i = 0; i < usChanNum; i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan    = pstChanList[i];
        stScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}
/*lint +e429*/


/*****************************************************************************
 �� �� ��  : NAS_MMC_AddMruListInScanChanList
 ��������  : ��Ƶ��ɨ���б�������MRU�б�
 �������  : ��
 �������  : pstScanChanList-------------����MRU�б���Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_AddMruListInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    CNAS_XSD_MRU_LIST_STRU             *pstMruList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stScanChanInfo;

    pstMruList = CNAS_XSD_GetMruList();

    for (i = 0; i < CNAS_MIN(pstMruList->ucSysNum, CNAS_XSD_MAX_MRU_SYS_NUM); i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan   = pstMruList->astSystem[i].stFreq;
        stScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddUePreferredListInScanChanList
 ��������  : ��Ƶ��ɨ���б�������Band0��Band10��PreferredƵ��
 �������  : ��
 �������  : pstScanChanList
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��9��23��
   ��    ��   : y00245242
   �޸�����   : DTS2015091901326
*****************************************************************************/
VOS_VOID CNAS_XSD_AddUePreferredListInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT32                                              i;
    CNAS_PRL_BANDCLASS0_SUBCLASS_CHAN_STRU  const          *pstBand0Tab     = VOS_NULL_PTR;
    CNAS_PRL_BANDCLASS10_SUBCLASS_CHAN_STRU const          *pstBand10Tab    = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stScanChanInfo;
    VOS_UINT32                                              ulBand0TabSize;
    VOS_UINT32                                              ulBand10TabSize;
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan = VOS_NULL_PTR;

    ulBand0TabSize  = CNAS_PRL_GetBand0PrefChanTabSize();
    ulBand10TabSize = CNAS_PRL_GetBand10PrefChanTabSize();
    pstBand0Tab     = CNAS_PRL_GetBand0PrefChanTab();
    pstBand10Tab    = CNAS_PRL_GetBand10PrefChanTab();

    /* ���BC0��SUBCLASS����0��Ƶ�� */
    pstCdmaStandardChan = CNAS_CCB_GetCdmaStandardChannels();

    stScanChanInfo.stFreqChan.enBandClass   = CNAS_PRL_BAND_CLASS_TYPE_0;
    stScanChanInfo.enChanStatus             = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    stScanChanInfo.stFreqChan.usChannel     = pstCdmaStandardChan->usPrimaryA;
    CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);

    stScanChanInfo.stFreqChan.usChannel     = pstCdmaStandardChan->usPrimaryB;
    CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);

    stScanChanInfo.stFreqChan.usChannel     = pstCdmaStandardChan->usSecondaryA;
    CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);

    stScanChanInfo.stFreqChan.usChannel     = pstCdmaStandardChan->usSecondaryB;
    CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);

    for (i = 0; i < ulBand0TabSize; i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan.usChannel     = pstBand0Tab[i].usChan;
        stScanChanInfo.stFreqChan.enBandClass   = CNAS_PRL_BAND_CLASS_TYPE_0;
        stScanChanInfo.enChanStatus             = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    for (i = 0; i < ulBand10TabSize; i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan.usChannel     = pstBand10Tab[i].usChan;
        stScanChanInfo.stFreqChan.enBandClass   = CNAS_PRL_BAND_CLASS_TYPE_10;
        stScanChanInfo.enChanStatus             = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddSyncedSuccFreqListinScanChanlist
 ��������  : ��Ƶ��ɨ���б������ӿ�����ͬ���ɹ�����Ƶ��
 �������  : ��
 �������  : pstScanChanList
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_AddHistorySyncedSuccFreqListInScanChanlist(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stScanChanInfo;
    CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU             *pstSyncedSuccFreqList   = VOS_NULL_PTR;

    pstSyncedSuccFreqList               = CNAS_XSD_GetHistorySyncedSysFreqList();

    for (i = 0; i < CNAS_MIN(pstSyncedSuccFreqList->ulCurNum, CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM); i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan.usChannel     = pstSyncedSuccFreqList->astFreq[i].usChannel;
        stScanChanInfo.stFreqChan.enBandClass   = pstSyncedSuccFreqList->astFreq[i].enBandClass;
        stScanChanInfo.enChanStatus             = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddCdma1XPrefChannelsInScanChanlist
 ��������  : ��Ƶ��ɨ���б�������CDMA 1X ��ѡƵ��
 �������  : ��
 �������  : pstScanChanList
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU                         stScanChanInfo;
    CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU             *pstCdma1XCustomPrefChan    = VOS_NULL_PTR;

    pstCdma1XCustomPrefChan                                 = CNAS_XSD_GetCdma1XCustomPrefChannels();

    if (VOS_FALSE == pstCdma1XCustomPrefChan->ucEnableFlg)
    {
        return;
    }

    for (i = 0; i < pstCdma1XCustomPrefChan->usFreqNum; i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan.usChannel     = pstCdma1XCustomPrefChan->astFreqList[i].usChannel;
        stScanChanInfo.stFreqChan.enBandClass   = pstCdma1XCustomPrefChan->astFreqList[i].enBandClass;
        stScanChanInfo.enChanStatus             = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddMruListExcludeMru0InScanChanList
 ��������  : ��Ƶ��ɨ���б������ӳ�MRU0�����MRU�б�
 �������  : ��
 �������  : pstScanChanList-------------����MRU0�����MRU�б���Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_AddMruListExcludeMru0InScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    CNAS_XSD_MRU_LIST_STRU             *pstMruList = VOS_NULL_PTR;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stScanChanInfo;

    pstMruList = CNAS_XSD_GetMruList();

    for (i = 1; i < CNAS_MIN(pstMruList->ucSysNum, CNAS_XSD_MAX_MRU_SYS_NUM); i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan   = pstMruList->astSystem[i].stFreq;
        stScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddSpecPrlAcqRecInScanChanList
 ��������  : ��Ƶ��ɨ���б�������PRL��ָ����ȡ��¼Ƶ����Ϣ
 �������  : pstPrlAcqRec---------------ָ����PRL�е�ϵͳ���¼
 �������  : pstScanChanList-------------����PRL�л�ȡ��¼�б���Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_AddSpecPrlAcqRecInScanChanList(
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stAcqRecFreqInfo;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stScanChanInfo;

    /* �����жϣ�HRPDƵ�㲻��� */
    if (CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD == pstPrlAcqRec->enAcqType)
    {
        return;
    }

    CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stAcqRecFreqInfo);

    for (i = 0; i < CNAS_MIN(stAcqRecFreqInfo.ulNum, CNAS_PRL_ACQ_RECORD_MAX_CHANNEL_NUM); i++)
    {
        NAS_MEM_SET_S(&stScanChanInfo, sizeof(stScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stScanChanInfo.stFreqChan.enBandClass = stAcqRecFreqInfo.astFreqInfo[i].enBandClass;
        stScanChanInfo.stFreqChan.usChannel   = stAcqRecFreqInfo.astFreqInfo[i].usChannel;
        stScanChanInfo.enChanStatus           = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stScanChanInfo, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddPrlAcqRecListInScanChanList
 ��������  : ��Ƶ��ɨ���б�������PRL�еĻ�ȡ��¼�б�
 �������  : ��
 �������  : pstScanChanList-------------����PRL�л�ȡ��¼�б���Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_AddPrlAcqRecListInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    CNAS_PRL_ACQ_RECORD_INFO_STRU      *pstAcqRecInfo = VOS_NULL_PTR;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec  = VOS_NULL_PTR;

    pstAcqRecInfo = CNAS_PRL_GetPrlAcqInfoAddr();

    for (i = 0; i < CNAS_MIN(pstAcqRecInfo->usAcqRecordNum, CNAS_PRL_ACQ_RECORD_MAX_NUM); i++)
    {
        /* ��ȡPRL�л�ȡ��ָ�� */
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(i);

        /* ��ָ����б��� */
        if ((VOS_NULL_PTR == pstPrlAcqRec)
         || (VOS_FALSE    == pstPrlAcqRec->ucAcqValid))
        {
            continue;
        }

        CNAS_XSD_AddSpecPrlAcqRecInScanChanList(pstPrlAcqRec, pstScanChanList);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AppendFreqChanInScanChanList
 ��������  : ��Ƶ��ɨ���б��м���ָ��Ƶ��
 �������  : pstScanChanInfo-----ָ����ɨ��Ƶ����Ϣ
 �������  : pstScanChanList----------Ƶ��ɨ���б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��12��26��
   ��    ��   : w00176964
   �޸�����   : CDMA 1X Iteration Modifed:Remove the band class that are not supported BY MS
*****************************************************************************/
VOS_VOID CNAS_XSD_AppendFreqChanInScanChanList(
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU    *pstScanChanInfo,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usIndex;
    /* could not add the band class or channel which is not supported by UE */
    if (VOS_FALSE == CNAS_XSD_IsUeSupportedFreq(pstScanChanInfo->stFreqChan))
    {
        return;
    }

    /* the totoal num is larger than the max channel list size, should not add chan to the list */
    if (pstScanChanList->usTotalNum >= pstScanChanList->usMaxScanChanSize)
    {
        return;
    }

    for (i = 0; i < pstScanChanList->usTotalNum; i++)
    {
        /* ������ظ�Ƶ�� */
        if ((pstScanChanInfo->stFreqChan.enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass)
         && (pstScanChanInfo->stFreqChan.usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel))
        {
            return;
        }
    }

    usIndex = pstScanChanList->usTotalNum;

    NAS_MEM_SET_S(&(pstScanChanList->pstScanChanInfo[usIndex]), sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

    pstScanChanList->pstScanChanInfo[usIndex].stFreqChan   = pstScanChanInfo->stFreqChan;
    pstScanChanList->pstScanChanInfo[usIndex].enChanStatus = pstScanChanInfo->enChanStatus;
    pstScanChanList->usTotalNum++;

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsChannelInSndCasSyncList
 ��������  : check��ǰ���͸�CAS�е�Ƶ���б����Ƿ�����Ҫͬ����Ƶ��
 �������  : pstFreqChan -- ��Ҫͬ����Ƶ��
             pstScanList -- ���͸�AS��ͬ���б�
             usScanNum   -- ��ǰͬ���б�����Ŀ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��ǰƵ��������
             VOS_FALSE:��ǰƵ�㲻������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��7��4��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsChannelInSndCasSyncList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstScanList,
    VOS_UINT16                                              usScanNum
)
{
    VOS_UINT16                          i;

    /* ��ֹ����ظ�Ƶ���ϵͳ */
    for (i = 0; i < CNAS_MIN(usScanNum, CNAS_CAS_1X_MAX_FREQ_NUM); i++)
    {
        if ((pstScanList[i].enBandClass == pstFreqChan->enBandClass)
         && (pstScanList[i].usChannel   == pstFreqChan->usChannel))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AppendAcqSysInfoInAcqSysList
 ��������  : �򲶻�ϵͳ�б������Ӳ���ϵͳ��Ϣ
 �������  : pstAcqSysInfo-----ָ���Ĳ���ϵͳ��Ϣ
 �������  : pstScanChanList----------����ϵͳ�б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��7��6��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_AppendAcqSysInfoInAcqSysList(
    CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU                      *pstAcqSysInfo,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usIndex;

    if (VOS_FALSE == CNAS_XSD_IsUeSupportedFreq(pstAcqSysInfo->stAcqSys.stFreq))
    {
        return;
    }

    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++)
    {
        /* ������ظ�ϵͳ */
        if (VOS_TRUE == CNAS_PRL_Is1xSysMatched(&(pstAcqSysInfo->stAcqSys), &(pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys)))
        {
            return;
        }
    }

    /* the totoal num is larger than the max acq sys list size, should not add sys to the list */
    if (pstGeoSysRecSrchList->usTotalNum >= pstGeoSysRecSrchList->usMaxAcqSysSize)
    {
        return;
    }

    usIndex = pstGeoSysRecSrchList->usTotalNum;

    NAS_MEM_SET_S(&(pstGeoSysRecSrchList->pstAcqSysInfo[usIndex]), sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU), 0x0, sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU));

    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].stAcqSys.stFreq = pstAcqSysInfo->stAcqSys.stFreq;
    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].stAcqSys.usNid  = pstAcqSysInfo->stAcqSys.usNid;
    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].stAcqSys.usSid  = pstAcqSysInfo->stAcqSys.usSid;
    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].enPrefNegSys    = pstAcqSysInfo->enPrefNegSys;
    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].enSysStatus     = pstAcqSysInfo->enSysStatus;
    pstGeoSysRecSrchList->pstAcqSysInfo[usIndex].usLevel         = pstAcqSysInfo->usLevel;

    pstGeoSysRecSrchList->usTotalNum++;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddSysRecordIntoSysList
 ��������  : �򲶻�ϵͳ�б������Ӳ���ϵͳ��Ϣ
 �������  : pstFreq             -----Ƶ����Ϣ
             pstSysRecord        -----ϵͳ��¼
 �������  : pstGeoSysRecSrchList-----GEOϵͳ��¼�����б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��7��6��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_AddSysRecordIntoSysList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstSysRecord,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU   stTmpAcqSysInfo;
    VOS_UINT32                          k;

    if (CNAS_PRL_SYS_RECORD_TYPE_1X_IS95 == pstSysRecord->enRecordType)
    {
        NAS_MEM_SET_S(&stTmpAcqSysInfo, sizeof(stTmpAcqSysInfo), 0x0, sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU));

        stTmpAcqSysInfo.stAcqSys.stFreq = *pstFreq;
        stTmpAcqSysInfo.stAcqSys.usNid  = pstSysRecord->u.st1xAndIs95Id.usNid;
        stTmpAcqSysInfo.stAcqSys.usSid  = pstSysRecord->u.st1xAndIs95Id.usSid;
        stTmpAcqSysInfo.enSysStatus     = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
        stTmpAcqSysInfo.enPrefNegSys    = pstSysRecord->enPrefNegSys;
        stTmpAcqSysInfo.usLevel         = pstSysRecord->usPriLvl;

        CNAS_XSD_AppendAcqSysInfoInAcqSysList(&stTmpAcqSysInfo, pstGeoSysRecSrchList);
    }

    if ( (CNAS_PRL_SYS_RECORD_TYPE_MCC_MNC_BASED == pstSysRecord->enRecordType)
      && ( (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID     == pstSysRecord->u.stMccMncId.enMccMncSubType)
        || (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID_NID == pstSysRecord->u.stMccMncId.enMccMncSubType) ) )
    {
        for (k = 0; k < pstSysRecord->u.stMccMncId.u.stSidNid.ucSidNidNum;k++)
        {
            NAS_MEM_SET_S(&stTmpAcqSysInfo, sizeof(stTmpAcqSysInfo), 0x0, sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU));

            stTmpAcqSysInfo.stAcqSys.stFreq = *pstFreq;

            if (CNAS_PRL_MCC_MNC_SUBTYPE_MULTIPLE_SID == pstSysRecord->u.stMccMncId.enMccMncSubType)
            {
                stTmpAcqSysInfo.stAcqSys.usNid  = CNAS_PRL_WILDCARD_NID;
            }
            else
            {
                stTmpAcqSysInfo.stAcqSys.usNid  = pstSysRecord->u.stMccMncId.u.stSidNid.asNid[k];
            }

            stTmpAcqSysInfo.stAcqSys.usSid  = pstSysRecord->u.stMccMncId.u.stSidNid.asSid[k];
            stTmpAcqSysInfo.enSysStatus     = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
            stTmpAcqSysInfo.enPrefNegSys    = pstSysRecord->enPrefNegSys;
            stTmpAcqSysInfo.usLevel         = pstSysRecord->usPriLvl;

            CNAS_XSD_AppendAcqSysInfoInAcqSysList(&stTmpAcqSysInfo, pstGeoSysRecSrchList);
        }

    }

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsChannelInChannelList
 ��������  : �ж�ָ��Ƶ���Ƿ���Ƶ���б�ֹŻ�ܹ�
 �������  : pstChannel-----ָ����ɨ��Ƶ����Ϣ
             usChanListNum---Ƶ���б����
             pstChanList----------Ƶ��ɨ���б��ű�
 �������  : ��
 �� �� ֵ  : VOS_UINT32 VOS_TRUE :��Ƶ���б���
                        VOS_FALSE:����Ƶ���б�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��18��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
/*lint -e429*/
VOS_UINT32 CNAS_XSD_IsChannelInChannelList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChannel,
    VOS_UINT16                          usChanListNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChanList
)
{
    VOS_UINT16                          i;

    for (i = 0; i < usChanListNum; i++)
    {
        /* ������ظ�Ƶ�� */
        if ((pstChannel->enBandClass == pstChanList[i].enBandClass)
         && (pstChannel->usChannel   == pstChanList[i].usChannel))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*lint +e429*/

/*****************************************************************************
 �� �� ��  : CNAS_XSD_MoveFreqChantoEndOfChanList
 ��������  : The channel over which origination failed shall be placed last in
             the channels list.

 �������  : pstSysInfo      -- system information
             pstScanChanList -- scan list
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��21��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_MoveFreqChantoEndOfChanList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT16                          i;

    for (i = 0; i < pstScanChanList->usTotalNum; i++)
    {
        if ((pstSysInfo->stFreq.usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel)
         && (pstSysInfo->stFreq.enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass))
        {
            /* if last freq is failed freq  */
            if (i == pstScanChanList->usTotalNum - 1)
            {
                return;
            }

            /* if fail freq is not last in scan list */
            if (i != pstScanChanList->usTotalNum - 1)
            {
                NAS_MEM_MOVE_S(&pstScanChanList->pstScanChanInfo[i],
                               (pstScanChanList->usTotalNum - i) * sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU),
                               &pstScanChanList->pstScanChanInfo[i+1],
                               (pstScanChanList->usTotalNum - i - 1) * sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

                pstScanChanList->pstScanChanInfo[pstScanChanList->usTotalNum - 1].stFreqChan = pstSysInfo->stFreq;

                return;
            }
        }
    }

    /* the fail req is not found */
    pstScanChanList->pstScanChanInfo[pstScanChanList->usTotalNum].stFreqChan = pstSysInfo->stFreq;

    pstScanChanList->pstScanChanInfo[pstScanChanList->usTotalNum].enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    pstScanChanList->usTotalNum++;

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_CalculateSystemLostMaxScanChanListSize
 ��������  : ���㶪���������ظ���������ʱ����Ƶ����
 �������  : VOS_UINT16                         *pstMaxScanListSize
 �������  : VOS_UINT16                         *pstMaxScanListSize
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

  1.��    ��   : 2015��1��5��
    ��    ��   : c00299063
    �޸�����   : �½�

*****************************************************************************/
VOS_VOID CNAS_XSD_CalculateSystemLostMaxScanChanListSize(
    VOS_UINT16                         *pusMaxScanListSize
)
{
    VOS_UINT16                                              usMaxScanListSize;
    CNAS_XSD_OOC_SCAN_STRATEGY_ENUM_UINT8                   enOocScanStrategy;
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocScheduleInfo = VOS_NULL_PTR;

    usMaxScanListSize         = *pusMaxScanListSize;
    pstOocScheduleInfo        = CNAS_XSD_GetOocScheduleInfo();
    enOocScanStrategy         = pstOocScheduleInfo->stConfigInfo.enOocScanStrategy;

    switch (enOocScanStrategy)
    {
        case CNAS_XSD_OOC_SCAN_REACQ_0_1_2_3_4S:
            usMaxScanListSize *= 2;
            break;

        case CNAS_XSD_OOC_SCAN_PING_5:
            usMaxScanListSize  = (VOS_UINT16)((usMaxScanListSize / 5) * 6 + 1 + usMaxScanListSize % 5);
            break;

        case CNAS_XSD_OOC_SCAN_2_7:
            usMaxScanListSize  = (VOS_UINT16)((usMaxScanListSize / 5) * 7 + 2 + usMaxScanListSize % 5);
            break;

        case CNAS_XSD_OOC_SCAN_NORMAL:
        default:
            break;

    }

    *pusMaxScanListSize      = usMaxScanListSize;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AllocMemoryForScanChanList
 ��������  : Ϊɨ��Ƶ���б�����ڴ�
 �������  : ��
 �������  : pstScanChanList-----Ƶ��ɨ���б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��21��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
 �޸���ʷ      :
  2.��    ��   : 2015��1��5��
    ��    ��   : c00299063
    �޸�����   : ������Σ���������

  3.��    ��   : 2015��7��20��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_VOID CNAS_XSD_AllocMemoryForScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList,
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
)
{
    VOS_UINT16                          usMaxScanListSize;

    /* �����������,���ͷ�֮ǰ�����SCAN LIST���ڴ� */
    if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstScanChanList->pstScanChanInfo);

        pstScanChanList->pstScanChanInfo = VOS_NULL_PTR;
    }

    /* ����MRU+PRL ACQ���еļ�¼,������µ�Ƶ����� */
    usMaxScanListSize = CNAS_PRL_CalcPrlAcqRecTotalFreqNum();

    if (0 != CNAS_XSD_GetMruListNum())
    {
        usMaxScanListSize += CNAS_XSD_MAX_MRU_SYS_NUM;
    }

    /* ���Ͻ����ų���1X Ƶ������ */
    if (VOS_TRUE == CNAS_XSD_GetCdma1XCustomPrefChannels()->ucEnableFlg)
    {
        usMaxScanListSize += CNAS_XSD_GetCdma1XCustomPrefChannels()->usFreqNum;
    }

    if (CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST == enSysAcqScene)
    {
        /* ���㶪���������ظ���������ʱ����Ƶ���� */
        CNAS_XSD_CalculateSystemLostMaxScanChanListSize(&usMaxScanListSize);
    }

    /* ���Ͻ�����ͬ���ɹ���Ƶ������ */
    if (CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL == enSysAcqScene)
    {
        /* ���뵱ǰͬ���ɹ���Ƶ������ */
        usMaxScanListSize += (VOS_UINT16)CNAS_XSD_GetHistorySyncedSysFreqList()->ulCurNum;

        /* ����Band0��Band10 Pref��Ƶ������ */
        usMaxScanListSize += CNAS_XSD_BAND0_BAND10_PREFERRED_SYSTEM_NUM;
    }

    /* PRL������ʱ,�����ض������ѡ����,ASЯ��Ƶ��������Ϊ40,��ʱ���б��� */
    if (usMaxScanListSize < CNAS_XSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM)
    {
        usMaxScanListSize = CNAS_XSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM;
    }

    /* ����scan list�Ƚϴ�,��Ҫ�ȷ����ڴ�,���ػ�ʱ�ͷ��ڴ� */
    pstScanChanList->pstScanChanInfo = (CNAS_XSD_SCAN_CHANNEL_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usMaxScanListSize);

    if (VOS_NULL_PTR == pstScanChanList->pstScanChanInfo)
    {
        return;
    }

    pstScanChanList->usCurScanIndex  = 0;
    pstScanChanList->usTotalNum      = 0;

    NAS_MEM_SET_S(pstScanChanList->pstScanChanInfo, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usMaxScanListSize, 0x0, (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * usMaxScanListSize));

    pstScanChanList->usMaxScanChanSize = usMaxScanListSize;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_AllocMemoryForGeoSysRecordSrchList
 ��������  : Ϊ����ϵͳ�б�����ڴ�
 �������  : usMatchedSysRecNum----------ѡ�е�GEO�б��е�ϵͳ��¼����
             pstMatchedSysRecord---------ѡ�е�GEO�б��е�ϵͳ��¼
 �������  : pstAcqSysList---------------����ϵͳ�б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��21��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��20��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_AllocMemoryForGeoSysRecordSrchList(
    VOS_UINT16                                              usMatchedSysRecNum,
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstMatchedSysRecord,
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT16                          usMaxAcqSysIdNum;

    /* �����������,���ͷ�֮ǰ�����acq sys LIST���ڴ� */
    if (VOS_NULL_PTR != pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstGeoSysRecSrchList->pstAcqSysInfo);

        pstGeoSysRecSrchList->pstAcqSysInfo = VOS_NULL_PTR;
    }

    /* ����ƥ���GEO�б������Ƶ����� */
    usMaxAcqSysIdNum = CNAS_XSD_CalcPrlSysRecListTotalFreqNum(usMatchedSysRecNum, pstMatchedSysRecord);

    /* Ϊ��ǰͬ������ϵͳƵ��Ԥ��һ���ռ� */
    usMaxAcqSysIdNum++;

    /* ���ݸ��������ڴ� */
    pstGeoSysRecSrchList->pstAcqSysInfo = (CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU)*(usMaxAcqSysIdNum));

    /* �����ڴ�ʧ�� */
    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        return;
    }

    pstGeoSysRecSrchList->usTotalNum     = 0;
    NAS_MEM_SET_S(pstGeoSysRecSrchList->pstAcqSysInfo, sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU) * (usMaxAcqSysIdNum), 0x0, sizeof(CNAS_XSD_ACQUIRE_SYSTEM_INFO_STRU) * usMaxAcqSysIdNum);

    pstGeoSysRecSrchList->usMaxAcqSysSize = usMaxAcqSysIdNum;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AllocMemoryForScanChanList_FreqLock
 ��������  : Ϊɨ��Ƶ���б�����ڴ�
 �������  : ��
 �������  : pstScanChanList-----Ƶ��ɨ���б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_AllocMemoryForScanChanList_FreqLock(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    /* �����������,���ͷ�֮ǰ�����SCAN LIST���ڴ� */
    if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstScanChanList->pstScanChanInfo);

        pstScanChanList->pstScanChanInfo = VOS_NULL_PTR;
    }

    /* ��ƵʱƵ��ֻ��1�� */
    pstScanChanList->pstScanChanInfo = (CNAS_XSD_SCAN_CHANNEL_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) );

    if (VOS_NULL_PTR == pstScanChanList->pstScanChanInfo)
    {
        return;
    }

    pstScanChanList->usCurScanIndex  = 0;
    pstScanChanList->usTotalNum      = 0;

    NAS_MEM_SET_S(pstScanChanList->pstScanChanInfo, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_CallReleasedWithRedir
 ��������  : build scan channel list with SD ind with release while redirection flag is true
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create

 2.��    ��   : 2015��7��20��
   ��    ��   : y00245242
   �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_CallReleasedWithRedir(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;
    VOS_UINT16                          i;

    /* �б����:��ʷƵ�� + MRU[0] */

    /* �Ƚ�pstPreSrchChanArray�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    for (i = 0; i < usPreSrchChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /* �ٽ�MRU[0]�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan   = stMru0SysId.stFreq;
        stTmpScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_RedirectionFail
 ��������  : build scan channel list while redirection failed
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_RedirectionFail(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    /* according to CDG143, the list is compose of:GEO(ordered by mru) + MRU + ���ų���Ƶ�� + PRL */
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stMatchedGeoList;
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstGeoChanList = VOS_NULL_PTR;
    VOS_UINT16                          usGeoChanNum;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usMaxGeoChanNum;

    NAS_MEM_SET_S(&stMatchedGeoList, sizeof(stMatchedGeoList), 0x0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    /* �Ƚ�MRU[0]�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        /* ��PRLϵͳ���в���MRU[0]��SID NID���ڵ�GEO LIST */
        CNAS_PRL_Get1xSysGeoList(&stMru0SysId, &stMatchedGeoList);
    }

    if (0 < stMatchedGeoList.ucGeoNum)
    {
        /* calculate the max size of the geo list channel and then alloc memory */
        usMaxGeoChanNum = CNAS_PRL_CalcMatchedGeoListTotalFreqNum(&stMru0SysId, &stMatchedGeoList);

        pstGeoChanList = (CNAS_PRL_FREQENCY_CHANNEL_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * usMaxGeoChanNum);

        if (VOS_NULL_PTR == pstGeoChanList)
        {
            return;
        }

        /* ��GEO�б���ÿ����¼��Ƶ�������Ƶ���б� */
        usGeoChanNum = 0;
        ulRet = CNAS_XSD_PraseChannelInMatchedGeoList(&stMru0SysId, &stMatchedGeoList, usMaxGeoChanNum, &usGeoChanNum, pstGeoChanList);

        /* �����ɹ� */
        if (VOS_TRUE == ulRet)
        {
            /* �����ҵ���GEO�ж�Ӧ��Ƶ���б���MRU��˳��������� */
            CNAS_XSD_SortChanListByMruList(usGeoChanNum,pstGeoChanList,CNAS_XSD_GetMruList());

            /* ������õ�Ƶ���б�����pstScanChanListInfo�� */
            CNAS_XSD_AddFreqChanListInScanChanList(usGeoChanNum, pstGeoChanList, pstScanChanList);
        }

        PS_MEM_FREE(UEPS_PID_XSD, pstGeoChanList);
    }

    /* �Ƚ���MRU[0]֮��������MRU�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    CNAS_XSD_AddMruListExcludeMru0InScanChanList(pstScanChanList);

    /* �����ų���1X Ƶ����뵽pstScanChanListInfo�� */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    /* Ȼ��PRL�л�ȡ���Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);

    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_RedirectionWithInvalidGSRDM
 ��������  : build scan channel list while redirection failed
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_RedirectionWithInvalidGSRDM(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    /* according to CDG143, the list is compose of:GEO(ordered by mur) + MRU + PRL */

    CNAS_XSD_BuildScanChanList_RedirectionFail(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_Rescan
 ��������  : build scan channel list with SD ind with reason reason
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_Rescan(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_ProtoMismatch
 ��������  : build scan channel list with SD ind with protocol mismatch reason
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_ProtoMismatch(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_AccessDenied
 ��������  : build scan channel list with SD ind with access denied reason
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_AccessDenied(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_AcctBlocked
 ��������  : build scan channel list with SD ind with acct blocked reason
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_AcctBlocked(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_NdssOff
 ��������  : build scan channel list with SD ind with ndss off reason
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_NdssOff(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    /* NDSS OFF scan list���տ����������� */
    CNAS_XSD_BuildScanChanList_SwitchOn(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_Error
 ��������  : build scan channel list with SD ind with error ind reason
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_Error(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_RegisRej
 ��������  : build scan channel list with SD ind with register reject ind reason
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_RegisRej(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_RegisRejWithRedirAndRtf
 ��������  : build scan channel list with SD ind with register reject ind reason while rediection flag is true and return_if_fail is true
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_RegisRejWithRedirAndRtf(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;

    /* add the redirection orignal system only */

    NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

    stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[0];
    stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);

    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_SysReselWithPrefPrl
 ��������  : build scan channel list with SD ind with system reselection ind reason while the current system is in PRL and is prefered system
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_SysReselWithPrefPrl(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    /* the scan list is built like this:reslection list(delete the frequency not in PRL) + idle geo list */
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;
    VOS_UINT16                          i;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usGeoChanNum;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stMatchedGeoList;
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstGeoChanList = VOS_NULL_PTR;
    VOS_UINT16                          usMaxGeoChanNum;

    NAS_MEM_SET_S(&stMatchedGeoList, sizeof(stMatchedGeoList), 0x0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    /* first add reslection list */
    for (i = 0; i < usPreSrchChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* if the channel is not in PRL acquistion table,we should not add to the scan list */
        if (VOS_TRUE == CNAS_XSD_IsChannelInPrlAcqTbl(&stTmpScanChanInfo.stFreqChan))
        {
            CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
        }
    }

    /* Second add idle geo list */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        /* ��PRLϵͳ���в���MRU[0]��SID NID���ڵ�GEO LIST */
        CNAS_PRL_Get1xSysGeoList(&stMru0SysId, &stMatchedGeoList);
    }

    if (0 < stMatchedGeoList.ucGeoNum)
    {
        /* calculate the max size of the geo list channel and then alloc memory */
        usMaxGeoChanNum = CNAS_PRL_CalcMatchedGeoListTotalFreqNum(&stMru0SysId, &stMatchedGeoList);

        pstGeoChanList = (CNAS_PRL_FREQENCY_CHANNEL_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * usMaxGeoChanNum);

        if (VOS_NULL_PTR == pstGeoChanList)
        {
            return;
        }

        /* prase the channle list from the GEO list */
        usGeoChanNum = 0;
        ulRet = CNAS_XSD_PraseChannelInMatchedGeoList(&stMru0SysId, &stMatchedGeoList, usMaxGeoChanNum, &usGeoChanNum, pstGeoChanList);

        /* prase success */
        if (VOS_TRUE == ulRet)
        {
            CNAS_XSD_AddFreqChanListInScanChanList(usGeoChanNum, pstGeoChanList, pstScanChanList);
        }

        PS_MEM_FREE(UEPS_PID_XSD, pstGeoChanList);
    }

    /* initial the index */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_SysReselNotInPrlOrNeg
 ��������  : build scan channel list with SD ind with system reselection ind reason while the current system is not in PRL or negative in PRL
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_SysReselNotInPrlOrNeg(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    /* the scan list is built like this:reslection list(delete the frequency not in PRL) */
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;
    VOS_UINT16                          i;

    for (i = 0; i < usPreSrchChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* if the channel is not in PRL acquistion table,we should not add to the scan list */
        if (VOS_TRUE == CNAS_XSD_IsChannelInPrlAcqTbl(&stTmpScanChanInfo.stFreqChan))
        {
            CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_MaxAccessFailureInPrl
 ��������  : build scan channel list with SD ind with max access failure reason while the current system is in PRL
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create

 2.��    ��   : 2015��3��21��
   ��    ��   : c00299063
   �޸�����   : DTS2015031106822

 3.��    ��   : 27/1/2016
   ��    ��   : w00176964
   �޸�����   : DTS2015120204031:SDָʾmax access failure,balong��ԭʼƵ��ʱ��Ƚ���
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_MaxAccessFailureInPrl(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{

    /* the scan list is built like this:IDLE GEO LIST + MRU + ���ų���Ƶ�� + PRL(MRU0 should be placed to the end)*/
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stMatchedGeoList;
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstGeoChanList = VOS_NULL_PTR;
    VOS_UINT16                          usGeoChanNum;
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usMaxGeoChanNum;
    CNAS_PRL_1X_SYSTEM_STRU             stTmpSysId;

    PS_MEM_SET(&stTmpSysId, 0x0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    NAS_MEM_SET_S(&stMatchedGeoList, sizeof(stMatchedGeoList), 0x0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    /* �Ƚ�MRU[0]�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        /* ��PRLϵͳ���в���MRU[0]��SID NID���ڵ�GEO LIST */
        CNAS_PRL_Get1xSysGeoList(&stMru0SysId, &stMatchedGeoList);
    }

    if (0 < stMatchedGeoList.ucGeoNum)
    {
        /* calculate the max size of the geo list channel and then alloc memory */
        usMaxGeoChanNum = CNAS_PRL_CalcMatchedGeoListTotalFreqNum(&stMru0SysId, &stMatchedGeoList);

        pstGeoChanList = (CNAS_PRL_FREQENCY_CHANNEL_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * usMaxGeoChanNum);
        if (VOS_NULL_PTR == pstGeoChanList)
        {
            return;
        }

        /* ��GEO�б���ÿ����¼��Ƶ�������Ƶ���б� */
        usGeoChanNum = 0;
        ulRet        = CNAS_XSD_PraseChannelInMatchedGeoList(&stMru0SysId, &stMatchedGeoList, usMaxGeoChanNum, &usGeoChanNum, pstGeoChanList);

        /* �����ɹ� */
        if (VOS_TRUE == ulRet)
        {
            CNAS_XSD_AddFreqChanListInScanChanList(usGeoChanNum, pstGeoChanList, pstScanChanList);

            /* ��MRU�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
            CNAS_XSD_AddMruListInScanChanList(pstScanChanList);

            /* �����ų���1X Ƶ����뵽pstScanChanListInfo�� */
            CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

            /* Ȼ��PRL�л�ȡ���Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
            CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);

            /* place the mru0 freq last in the channels list */
            CNAS_XSD_MoveFreqChantoEndOfChanList(&stMru0SysId, pstScanChanList);

            if (VOS_NULL_PTR != pstPreSrchChanArray)
            {
                stTmpSysId.stFreq = pstPreSrchChanArray[0];

                /* ��SDЯ����MAPƵ������б������ */
                CNAS_XSD_MoveFreqChantoEndOfChanList(&stTmpSysId, pstScanChanList);
            }
        }

        PS_MEM_FREE(UEPS_PID_XSD, pstGeoChanList);
    }

    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_MaxAccessFailureNotInPrl
 ��������  : build scan channel list with SD ind with max access failure reason while the current system is not in PRL
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create

 2.��    ��   : 27/1/2016
   ��    ��   : w00176964
   �޸�����   : DTS2015120204031:SDָʾmax access failure,balong��ԭʼƵ��ʱ��Ƚ���
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_MaxAccessFailureNotInPrl(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    VOS_UINT16                          usAcqChanNum;
    VOS_UINT16                          i;
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAcqChanList = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;
    CNAS_PRL_1X_SYSTEM_STRU             stTmpSysId;

    PS_MEM_SET(&stTmpSysId, 0x0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    /* the scan list is built like this: ���ų���Ƶ�� + prl acquisition table(ordered by mru) + del mru0 from list + mru0 */
    /* �����ų���1X Ƶ����뵽pstScanChanListInfo�� */
    CNAS_XSD_AddCdma1XCustomPrefChannelsInScanChanlist(pstScanChanList);

    CNAS_XSD_AddPrlAcqRecListInScanChanList(pstScanChanList);

    pstAcqChanList = (CNAS_PRL_FREQENCY_CHANNEL_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * pstScanChanList->usTotalNum);

    if (VOS_NULL_PTR == pstAcqChanList)
    {
        return;
    }

    usAcqChanNum = pstScanChanList->usTotalNum;
    for (i = 0; i < pstScanChanList->usTotalNum; i++)
    {
        pstAcqChanList[i] = pstScanChanList->pstScanChanInfo[i].stFreqChan;
    }

    /* clear the scan channel list */
    pstScanChanList->usTotalNum     = 0;
    pstScanChanList->usCurScanIndex = 0;

    CNAS_XSD_SortChanListByMruList(usAcqChanNum, pstAcqChanList, CNAS_XSD_GetMruList());

    CNAS_XSD_AddFreqChanListInScanChanList(usAcqChanNum, pstAcqChanList,pstScanChanList);

    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        /* place the mru0 freq last in the channels list */
        CNAS_XSD_MoveFreqChantoEndOfChanList(&stMru0SysId, pstScanChanList);
    }

    if (VOS_NULL_PTR != pstPreSrchChanArray)
    {
        stTmpSysId.stFreq = pstPreSrchChanArray[0];

        /* ��SDЯ����MAPƵ������б������ */
        CNAS_XSD_MoveFreqChantoEndOfChanList(&stTmpSysId, pstScanChanList);
    }

    PS_MEM_FREE(UEPS_PID_XSD, pstAcqChanList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_Abnormal
 ��������  : build scan channel list with SD ind with abnormal ind reason
 �������  : usPreSrchChanNum ------------ Number of the channels which are synced at first
             pstPreSrchChanArray---------- The channels which are synced at first,we have to add the list to the scan chanel list while building
 �������  : pstScanChanList---------------The scan channel list which has been built
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : Create
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_Abnormal(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_BuildScanChanList_SystemLost(usPreSrchChanNum, pstPreSrchChanArray, pstScanChanList);

    return;
}



CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM_UINT8 CNAS_XSD_GetSysAcqModeOfSpecialAcqScene(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enScanScene
)
{
    CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM_UINT8                 enSysAcqMode;

    enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_BEST_PREF;

    if (VOS_TRUE == CNAS_XSD_GetFreqLockMode())
    {
        return CNAS_XSD_SYSTEM_ACQUIRE_MODE_SPECIFIC;
    }

    switch (enScanScene)
    {
        case CNAS_XSD_SYS_ACQ_SCENE_NDSS_OFF:
        case CNAS_XSD_SYS_ACQ_SCENE_RESCAN:
        case CNAS_XSD_SYS_ACQ_SCENE_PROTO_MISMATCH:
        case CNAS_XSD_SYS_ACQ_SCENE_ACCESS_DENINED:
        case CNAS_XSD_SYS_ACQ_SCENE_ACCT_BLOCKED:
        case CNAS_XSD_SYS_ACQ_SCENE_ERR:
        case CNAS_XSD_SYS_ACQ_SCENE_SWITCH_ON:
        case CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST:
        case CNAS_XSD_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED:
        case CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ:
        case CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_FAIL:
        case CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM:
        case CNAS_XSD_SYS_ACQ_SCENE_ABNORMAL:
        case CNAS_XSD_SYS_ACQ_SCENE_CALL_MRU0:
            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_BEST_PREF;
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL:
        case CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF:

            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_ALLOWED;
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF:
        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL:

            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_PREFERED;
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG:
        case CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED_WITH_REDIR:
        case CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED:
        case CNAS_XSD_SYS_ACQ_SCENE_EMERGENCY_CALL:
        case CNAS_XSD_SYS_ACQ_SCENE_EMC_CALLBACK_SYSTEM_LOST:
        case CNAS_XSD_SYS_ACQ_SCENE_EMC_CALL_RELEASED:
        case CNAS_XSD_SYS_ACQ_SCENE_REGIS_REJ_WITH_REDIR_AND_RTF_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_IN_PRL_AND_PREF_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYS_RESEL_NOT_IN_PRL_OR_NEG_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST_SKIP_MRU0_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_REDIRECTION_WITH_INVALID_GSRDM_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_NOT_IN_PRL_EMC:
        case CNAS_XSD_SYS_ACQ_SCENE_POWER_ON_INIT_SEARCH:

            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_ANY;
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_NORMAL_CALL_REDIAL:

            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_NOT_LESS_PREF;
            break;

        case CNAS_XSD_SYS_ACQ_SCENE_CFREQ_LOCK:

            enSysAcqMode = CNAS_XSD_SYSTEM_ACQUIRE_MODE_SPECIFIC;
            break;

        default:
            break;
    }

    return enSysAcqMode;
}


/*****************************************************************************
Function Name   :   CNAS_XSD_BuildScanChanList_Redirection
Description     :   Build the channel scan list with SD ind reason is redirecton
Input parameters:   pstRedirectionInfo
                    pstScanList

Output parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2014-12-26
        Author  :   m00270891
        Modify content :    Create
    2)  Date    :   2015-6-09
        Author  :   W00176964
        Modify content : DTS2015053003202:�ض������ASЯ���������ظ�Ƶ��
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_Redirection(
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirectionInfo,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanList
)
{
    VOS_UINT8                           i;
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;

    /* Allocate memory for the scan list */
    pstScanList->pstScanChanInfo = (CNAS_XSD_SCAN_CHANNEL_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                                                   (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * pstRedirectionInfo->ucChanNum));

    if (VOS_NULL_PTR == pstScanList->pstScanChanInfo)
    {
        return;
    }

    pstScanList->usTotalNum         = 0;
    pstScanList->usCurScanIndex     = 0;
    pstScanList->usMaxScanChanSize  = pstRedirectionInfo->ucChanNum;

    NAS_MEM_SET_S(pstScanList->pstScanChanInfo,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * pstRedirectionInfo->ucChanNum),
                  0,
                  (sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * pstRedirectionInfo->ucChanNum));

    for (i = 0; i < pstRedirectionInfo->ucChanNum; i++)
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstRedirectionInfo->astChanInfo[i].stFreqChan;
        stTmpScanChanInfo.enChanStatus  = pstRedirectionInfo->astChanInfo[i].enChanStatus;

        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanList);
    }

    pstScanList->usCurScanIndex = pstRedirectionInfo->usCurScanIndex;

    CNAS_XSD_LogScanChannelList(ID_CNAS_XSD_MNTN_LOG_REDIR_SCAN_CHAN_LIST_IND, pstScanList);
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_FreqLock
 ��������  : ����ɨ���б�
 �������  : ��
 �������  : pstScanChanList-----Ƶ��ɨ���б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_FreqLock(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU  *pstCnasXsdCFreqLockValue;

    pstCnasXsdCFreqLockValue = CNAS_XSD_GetFreqLockAddr();

    pstScanChanList->usCurScanIndex                         = 0;
    pstScanChanList->usTotalNum                             = 1;

    pstScanChanList->pstScanChanInfo->stFreqChan.enBandClass = pstCnasXsdCFreqLockValue->usCdmaBandClass;
    pstScanChanList->pstScanChanInfo->stFreqChan.usChannel   = pstCnasXsdCFreqLockValue->usCdmaFreq;
    pstScanChanList->pstScanChanInfo->enChanStatus           = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    return;
}
/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsChannelInPrlAcqTbl
 ��������  : �ж�ָ��Ƶ���Ƿ���PRL��
 �������  : pstChannel-----ָ����ɨ��Ƶ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32 VOS_TRUE :��PRL��
                        VOS_FALSE:����PRL��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsChannelInPrlAcqTbl(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChannel
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usAcqRecNum;
    CNAS_PRL_ACQ_RECORD_STRU           *pstPrlAcqRec = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU     stAcqRecFreqInfo;

    usAcqRecNum = CNAS_PRL_GetPrlAcqRecordNum();

    for (i = 0; i < usAcqRecNum; i++)
    {
        pstPrlAcqRec = CNAS_PRL_GetSpecifiedPrlAcqRecord(i);

        /* ��ָ����б�����ֱ������ */
        if (VOS_NULL_PTR == pstPrlAcqRec)
        {
            continue;
        }

        /* �����жϣ�HRPDƵ�㲻��� */
        if (CNAS_PRL_ACQ_TYPE_GENERIC_ACQ_RECORD_FOR_HRPD == pstPrlAcqRec->enAcqType)
        {
            continue;
        }

        /* �������Ч��Acq Rec�� ֱ������ */
        if (VOS_FALSE == pstPrlAcqRec->ucAcqValid)
        {
            continue;
        }

        CNAS_PRL_GetPrlAcqRecFreqListInfo(pstPrlAcqRec, &stAcqRecFreqInfo);

        if (VOS_TRUE == CNAS_XSD_IsChannelInChannelList(pstChannel, (VOS_UINT16)stAcqRecFreqInfo.ulNum, &(stAcqRecFreqInfo.astFreqInfo[0])))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsAvailableSys
 ��������  : �ж���ǰϵͳ�Ƿ�Ϊavailable system
 �������  : pstCurSys-----��ǰϵͳ
 �������  : ��
 �� �� ֵ  : VOS_UINT32 VOS_TRUE :��available system
                        VOS_FALSE:����available system
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsAvailableSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSys
)
{
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU stGeoListInfo;

    if (VOS_FALSE == CNAS_XSD_IsUeSupportedFreq(pstCurSys->stFreq))
    {
        return VOS_FALSE;
    }


    NAS_MEM_SET_S(&stGeoListInfo, sizeof(stGeoListInfo), 0, sizeof(CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU));

    CNAS_PRL_Get1xSysGeoList(pstCurSys, &stGeoListInfo);

    /* SID and NID is not In PRL */
    if ((VOS_FALSE == CNAS_PRL_GetPrefOnlyFlg())
     && (0         == stGeoListInfo.ucGeoNum))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsAcquireAvaialSysNeeded
 ��������  : �ж��Ƿ���Ҫ����available system
 �������  : pstCurSys-----��ǰϵͳ
 �������  : ��
 �� �� ֵ  : VOS_UINT32 VOS_TRUE :��available system
                        VOS_FALSE:����available system
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsAcquireAvaialSysNeeded(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enScanScene
)
{
    VOS_UINT8                                               ucAvailSysNum;
    VOS_UINT8                                               ucPrefOnlyFlg;
    CNAS_XSD_SYSTEM_ACQUIRE_MODE_ENUM_UINT8                 enSysAcqMode;

    ucAvailSysNum = CNAS_XSD_GetAvailSysFreqNum();
    ucPrefOnlyFlg = CNAS_PRL_GetPrefOnlyFlg();

    enSysAcqMode = CNAS_XSD_GetSysAcqModeOfSpecialAcqScene(enScanScene);

    /* PERF_ONLY is false and available system exist,for the following acq scene,
       we have to select the avaialble system to provide service */
    if ((VOS_FALSE                                        == ucPrefOnlyFlg)
     && (0                                                != ucAvailSysNum)
     && ((CNAS_XSD_SYSTEM_ACQUIRE_MODE_BEST_PREF           == enSysAcqMode)
      || (CNAS_XSD_SYSTEM_ACQUIRE_MODE_NOT_LESS_PREF       == enSysAcqMode)
      || ((CNAS_XSD_SYSTEM_ACQUIRE_MODE_PREFERED           == enSysAcqMode)
       && (CNAS_XSD_SYS_ACQ_SCENE_MAX_ACCESS_FAILURE_IN_PRL == enScanScene))))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_MRU0
 ��������  : MRU0Ƶ������scan list����
 �������  : usPreSrchChanNum ------------ ��ǰ��Ҫ����������Ƶ�����,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
             pstPreSrchChanArray---------- ��ǰ��Ҫ����������Ƶ������ͷָ��,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��1��5��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_MRU0(
    VOS_UINT16                         usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU    *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU   *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;

    /* �ٽ�MRU[0]�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan   = stMru0SysId.stFreq;
        stTmpScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        /* ��ӵ�Ƶ��ɨ���б� */
        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }


    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_EMC
 ��������  : ������Ƶ������scan list����
 �������  : VOS_UINT16                          usPreSrchChanNum
             CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_EMC(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstEmcCallRedialScanChanList = VOS_NULL_PTR;
    VOS_UINT16                          i;

    pstEmcCallRedialScanChanList = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

    CNAS_XSD_UpdateScanChanList(pstScanChanList, pstEmcCallRedialScanChanList);

    /* if the call redial channel list has been synced finished,we should reset
       the index and the channle status. */
    if (pstScanChanList->usCurScanIndex >= pstScanChanList->usTotalNum - 1)
    {
        for (i = 0; i < pstScanChanList->usTotalNum; i++)
        {
            pstScanChanList->pstScanChanInfo[i].enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;
        }

        pstScanChanList->usCurScanIndex = 0;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_CALLBACK
 ��������  : ������Ƶ������scan list����
 �������  : VOS_UINT16                          usPreSrchChanNum
             CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

 2.��    ��   : 2016��1��27��
   ��    ��   : h00313353
   �޸�����   : DTS2015091603440
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_CALLBACK(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_XSD_SCAN_CHANNEL_INFO_STRU     stTmpScanChanInfo;
    CNAS_PRL_1X_SYSTEM_STRU            *pstCallBackSysId    = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /***********************************************************************************************
     * 1. ��ӽ������н�����ϵͳƵ��
     **********************************************************************************************/

    pstCallBackSysId                    = CNAS_XSD_GetEmcCallOriginalSys();
    NAS_MEM_SET_S(&stTmpScanChanInfo, sizeof(stTmpScanChanInfo), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

    stTmpScanChanInfo.stFreqChan   = pstCallBackSysId->stFreq;
    stTmpScanChanInfo.enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

    /* ��ӵ�Ƶ��ɨ���б� */
    CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);

    /***********************************************************************************************
     * 2. �����Ƶ������Ƶ��
     **********************************************************************************************/
    /* �Ƚ�pstPreSrchChanArray�е�Ƶ����Ϣ���ӵ�pstScanChanListInfo�� */
    for (i = 0; i < usPreSrchChanNum; i++)
    {
        PS_MEM_SET(&stTmpScanChanInfo, 0x0, sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU));

        stTmpScanChanInfo.stFreqChan    = pstPreSrchChanArray[i];
        stTmpScanChanInfo.enChanStatus  = CNAS_XSD_SCAN_CHAN_STATUS_NO_SYNCED;

        CNAS_XSD_AppendFreqChanInScanChanList(&stTmpScanChanInfo, pstScanChanList);
    }

    /* ��ʼ����ǰ��Ҫ������Ƶ������Ϊ0 */
    pstScanChanList->usCurScanIndex    = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateSyncSuccChanStatus
 ��������  : ����ɨ��ɹ���Ƶ��״̬
 �������  : VOS_UINT16                          usBeginScanListIndex
             CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChannel
             CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
 �������  : ��
 �� �� ֵ  : VOS_UINT16 -- ���ص�ǰˢ�µ�Ƶ����scan list�е�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��9��8��
    ��    ��   : y00245242
    �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateSyncSuccChanStatus(
    VOS_UINT16                          usBeginScanListIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstChannel,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    return CNAS_XSD_UpdateChanStatusInScanChanList(usBeginScanListIndex,
                                                   pstChannel,
                                                   CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_EXIST,
                                                   pstScanChanList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateSyncFailChanStatus
 ��������  : ����ɨ��ʧ�ܵ�Ƶ��״̬
 �������  : usBeginScanListIndex ------------ ��ʼ����Ƶ���index
             usSyncFailChanNum ------------------ͬ��ʧ�ܵ�Ƶ�����
             pstSyncFailChanList ------------ ͬ��ʧ�ܵ�Ƶ���б�
             pstScanChanList -----------------��ǰ��Ƶ��ɨ���б�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��8��14��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��7��9��
   ��    ��   : y00245242
   �޸�����   : iteration 17����

 3.��    ��   : 2015��9��8��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateSyncFailChanStatus(
    VOS_UINT16                          usBeginScanListIndex,
    VOS_UINT16                          usSyncFailChanNum,
    CNAS_CAS_1X_SYNC_RSLT_INFO_STRU    *pstSyncFailChanList,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stTmpChan;
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enChanStatus;
    VOS_UINT16                                              i;
    VOS_UINT16                                              usCurFreqIndex;

    usCurFreqIndex = usBeginScanListIndex;

    for (i = 0; i < usSyncFailChanNum; i++)
    {
        stTmpChan.enBandClass = pstSyncFailChanList[i].stFreq.usBandClass;
        stTmpChan.usChannel   = pstSyncFailChanList[i].stFreq.usChannel;

        enChanStatus = CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST;

        usCurFreqIndex = CNAS_XSD_UpdateChanStatusInScanChanList(usBeginScanListIndex,
                                                                 &stTmpChan,
                                                                 enChanStatus,
                                                                 pstScanChanList);
    }

    /* �������һ��ˢ�µ�Ƶ����scan list�е����� */
    return usCurFreqIndex;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateGeoListSrchStatus
 ��������  : ����GEO list����״̬
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
VOS_VOID CNAS_XSD_UpdateGeoListSrchStatus(
    CNAS_PRL_MATCHED_GEO_LIST_INFO_STRU                    *pstGeoListInfo,
    VOS_UINT16                                              usGeoSrchStatus
)
{
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoListSrchInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    pstGeoListSrchInfo = CNAS_XSD_GetGeoSrchListInfoAddr();

    if (VOS_NULL_PTR == pstGeoListSrchInfo->pstGeoSrchInfo)
    {
        NAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_UpdateGeoListSrchStatus: GEO LIST search information is NULL!");
        return;
    }

    /* ��GEO�����б��в��ҵ�ǰGEO�������ö�Ӧ��GEO״̬Ϊ������ */
    for (i = 0; i < pstGeoListInfo->ucGeoNum; i++)
    {
        for (j = 0; j < pstGeoListSrchInfo->usGeoNum; j++)
        {
            if (pstGeoListInfo->astGeoInfoList[i].usGeoFirstSysRecIndex == pstGeoListSrchInfo->pstGeoSrchInfo[j].usGeoBeginIndex)
            {
                pstGeoListSrchInfo->pstGeoSrchInfo[j].usGeoSrchStatus = usGeoSrchStatus;

                break;
            }
        }
    }

    /* log GEO list����״̬ */
    CNAS_XSD_LogGeoListSrchStatus(pstGeoListSrchInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateGeoSysRecordListInfoAccordingToScanChanList
 ��������  : ����scan chan list����GEOϵͳ��¼����
 �������  : pstGeoSysRecSrchList -- GEOϵͳ��¼�����б�

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateGeoSysRecordListInfoAccordingToScanChanList(
    CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU                 *pstGeoSysRecSrchList
)
{
    VOS_UINT32                                              i;
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enSysStatus;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstGeoSysRecSrchList->pstAcqSysInfo)
    {
        return;
    }

    for (i = 0; i < pstGeoSysRecSrchList->usTotalNum; i++)
    {
        if (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST == pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus)
        {
            continue;
        }

        pstFreq = &pstGeoSysRecSrchList->pstAcqSysInfo[i].stAcqSys.stFreq;

        /* check��ǰGEOϵͳ��¼�����б��е�Ƶ����scan list�е�״̬ */
        enSysStatus = CNAS_XSD_GetScanChanStatusInScanChanList(pstFreq, CNAS_XSD_GetScanChanListAddr());

        if (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST != enSysStatus)
        {
            /* ˢ�µ�ǰ����level */
            pstGeoSysRecSrchList->usCurSrchLevel = pstGeoSysRecSrchList->pstAcqSysInfo[i].usLevel;

            return;
        }

        /* ���򣬸���ϵͳ��¼�����б��е�״̬Ϊͬ�������� */
        pstGeoSysRecSrchList->pstAcqSysInfo[i].enSysStatus = CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST;

        if ((pstGeoSysRecSrchList->usTotalNum - 1) != i)
        {
            /* ����GEO�е�ǰ����levelΪ��һ��ϵͳ��¼��level */
            pstGeoSysRecSrchList->usCurSrchLevel = pstGeoSysRecSrchList->pstAcqSysInfo[i+1].usLevel;
        }
        else
        {
            /* ����GEO�е�ǰ����levelΪ��ǰ��level */
            pstGeoSysRecSrchList->usCurSrchLevel = pstGeoSysRecSrchList->pstAcqSysInfo[i].usLevel;
        }
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateRedirectionFreqStatusAccordingToScanChanList
 ��������  : ����scan chan list�����ض���Ƶ��״̬
 �������  : pstScanChanList -- scan chan list��ַ

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateRedirectionFreqStatusAccordingToScanChanList(
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU                         *pstRedirInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;

    /* ����ض����־�����ڵĻ�������Ҫˢ���ض���Ƶ��״̬ */
    if (VOS_FALSE == CNAS_XSD_GetRedirectionFlag())
    {
        return;
    }

    pstRedirInfo = CNAS_XSD_GetRedirectionInfoAddr();

    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstScanChanList->usTotalNum, CNAS_XSD_CALL_REL_SYNC_MAX_FREQ_NUM); i++)
    {
        for (j = 0; j < pstRedirInfo->ucChanNum; j++)
        {
            if ((pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass == pstRedirInfo->astChanInfo[j].stFreqChan.enBandClass)
             && (pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel   == pstRedirInfo->astChanInfo[j].stFreqChan.usChannel))
            {
                pstRedirInfo->astChanInfo[j].enChanStatus = pstScanChanList->pstScanChanInfo[i].enChanStatus;
            }
        }
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsOocSceneAndRepeatMru0FreqSrchExist
 ��������  : check��ǰ�Ƿ���OOC�������ظ�MRU0Ƶ����������
 �������  : pstMru0SysId -- MRU0Ƶ����Ϣ

 �������  : ��

 �� �� ֵ  : VOS_TRUE  -- ��ǰ��OOC������MRU0Ƶ�����
             VOS_FALSE -- ����OOC������MRU0Ƶ�����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��07��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_UINT32  CNAS_XSD_IsOocSceneAndRepeatMru0FreqSrchExist(
    CNAS_PRL_1X_SYSTEM_STRU            *pstMru0SysId
)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;

    pstOocScheduleInfo = CNAS_XSD_GetOocScheduleInfo();

    /* �������OOC������ֱ�ӷ���FALSE */
    if (CNAS_XSD_SYS_ACQ_SCENE_SYSTEM_LOST != CNAS_XSD_GetCurSysAcqScene_SysAcq())
    {
        return VOS_FALSE;
    }

    /* �����ǰû������MRU0�ظ�Ƶ�������ԣ��򷵻�FAALSE */
    if ((CNAS_XSD_OOC_SCAN_NORMAL == pstOocScheduleInfo->stConfigInfo.enOocScanStrategy)
     || (CNAS_XSD_OOC_SCAN_BUTT   == pstOocScheduleInfo->stConfigInfo.enOocScanStrategy))
    {
        return VOS_FALSE;
    }

    /* �����MRU0Ƶ�㣬����VOS_FALSE */
    if (VOS_FALSE == CNAS_XSD_GetMru0SysId(pstMru0SysId))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsMru0FreqInOocScene
 ��������  : ��鵱ǰƵ���Ƿ���MRU0Ƶ��
 �������  : pstFreqChan -- Ƶ����Ϣָ��

 �������  : ��

 �� �� ֵ  : VOS_TRUE  -- ��MRU0Ƶ��
             VOS_FALSE -- ����MRU0Ƶ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��07��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsMru0FreqInOocScene(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqChan
)
{
    CNAS_PRL_1X_SYSTEM_STRU             stMru0SysId;

    if (VOS_FALSE == CNAS_XSD_IsOocSceneAndRepeatMru0FreqSrchExist(&stMru0SysId))
    {
        return VOS_FALSE;
    }

    if ((stMru0SysId.stFreq.enBandClass == pstFreqChan->enBandClass)
     && (stMru0SysId.stFreq.usChannel   == pstFreqChan->usChannel))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList
 ��������  : ����scan list�дӿ�ʼ����ǰ����ָ����Ƶ��״̬
 �������  : enChanStatus       -- Ƶ��״̬
             usCurScanChanIndex -- ��ǰƵ������
             pstFreqChan        -- Ƶ����Ϣ��ַ
             pstScanChanList    -- scan chan list��Ϣ��ַ

 �������  : ��

 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��07��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateFreqStatusBeforeCurIndexInScanChanList(
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enChanStatus,
    VOS_UINT16                                              usCurScanChanIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT32                          i;

    for (i = 0; i < usCurScanChanIndex; i++)
    {
        if ((pstFreqChan->enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass)
         && (pstFreqChan->usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel))
        {
            pstScanChanList->pstScanChanInfo[i].enChanStatus = enChanStatus;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateNoSyncedOrSyncSuccScanChanInScanChanList
 ��������  : ����scan list��δͬ���Ļ�ͬ���ɹ���Ƶ��״̬
 �������  : enChanStatus       -- Ƶ��״̬
             usCurScanChanIndex -- ��ǰƵ������
             pstFreqChan        -- Ƶ����Ϣ��ַ
             pstScanChanList    -- scan chan list��Ϣ��ַ

 �������  : ��

 �� �� ֵ  : VOS_UINT16 -- ��ǰˢ�µ�Ƶ������

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��07��
   ��    ��   : y00245242
   �޸�����   : DTS2015090601618
*****************************************************************************/
VOS_UINT16 CNAS_XSD_UpdateNoSyncedOrSyncSuccScanChanInScanChanList(
    CNAS_XSD_SCAN_CHAN_STATUS_ENUM_UINT8                    enChanStatus,
    VOS_UINT16                                              usCurScanIndex,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreqChan,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList
)
{
    VOS_UINT16                          i;

    for (i = usCurScanIndex; i < pstScanChanList->usTotalNum; i++)
    {
        /* ����Ƶ��״̬Ϊ���������ڵ�Ƶ��״̬ */
        if (CNAS_XSD_SCAN_CHAN_STATUS_SYNCED_NO_EXIST == pstScanChanList->pstScanChanInfo[i].enChanStatus)
        {
            continue;
        }

        if ((pstFreqChan->enBandClass == pstScanChanList->pstScanChanInfo[i].stFreqChan.enBandClass)
         && (pstFreqChan->usChannel   == pstScanChanList->pstScanChanInfo[i].stFreqChan.usChannel))
        {
            pstScanChanList->pstScanChanInfo[i].enChanStatus = enChanStatus;

            return i;
        }
    }

    /* ���û���ҵ������ص�ǰ�������� */

    return usCurScanIndex;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildEmcRedialMruList
 ��������  : ��¼��ǰMRU LIST�����ڽ��������ز�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��26��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildEmcRedialMruList()
{
    CNAS_XSD_MRU_LIST_STRU                                 *pstMruList            = VOS_NULL_PTR;
    CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU                   *pstEmcRedialSysAcqCfg = VOS_NULL_PTR;

    pstMruList            = CNAS_XSD_GetMruList();
    pstEmcRedialSysAcqCfg = CNAS_XSD_GetEmcRedialSysAcqCfgInfo();

    NAS_MEM_CPY_S(&(pstEmcRedialSysAcqCfg->stEmcRedialMruList),
                  sizeof(pstEmcRedialSysAcqCfg->stEmcRedialMruList),
                  pstMruList,
                  sizeof(CNAS_XSD_MRU_LIST_STRU));

    return;

}
/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearEmcRedialSysAcqCount
 ��������  : ��ս������ز���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��26��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ClearEmcRedialSysAcqCfgInfo()
{
    CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU                   *pstEmcRedialSysAcqCfg = VOS_NULL_PTR;

    pstEmcRedialSysAcqCfg = CNAS_XSD_GetEmcRedialSysAcqCfgInfo();

    pstEmcRedialSysAcqCfg->ucRedialCount     = 0;

    NAS_MEM_SET_S(&(pstEmcRedialSysAcqCfg->stLastCampedSys), sizeof(pstEmcRedialSysAcqCfg->stLastCampedSys), 0, sizeof(CNAS_PRL_1X_SYSTEM_STRU));
    NAS_MEM_SET_S(&(pstEmcRedialSysAcqCfg->stEmcRedialMruList), sizeof(pstEmcRedialSysAcqCfg->stEmcRedialMruList), 0, sizeof(CNAS_XSD_MRU_LIST_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurSysIndexOfEmcRedialMruList
 ��������  : ���浱ǰϵͳ��mru�б��е�����
 �������  : CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo
 �������  : VOS_UINT8                                              *pucindex
 �� �� ֵ  : VOS_TRUE      ��ȡ�����ɹ�
             VOS_FALSE     ��ȡ����ʧ�ܣ�ϵͳ����MruList����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��26��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetCurSysIndexOfEmcRedialMruList(
    CNAS_PRL_1X_SYSTEM_STRU                                *pstSysInfo,
    VOS_UINT32                                             *pulIndex
)
{
    CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU                   *pstEmcRedialSysAcqCfg = VOS_NULL_PTR;
    VOS_UINT32                                              i;

   *pulIndex = 0;

    pstEmcRedialSysAcqCfg = CNAS_XSD_GetEmcRedialSysAcqCfgInfo();

    for (i = 0; i < pstEmcRedialSysAcqCfg->stEmcRedialMruList.ucSysNum; i++)
    {
        if ((pstSysInfo->usSid              == pstEmcRedialSysAcqCfg->stEmcRedialMruList.astSystem[i].usSid)
         && (pstSysInfo->usNid              == pstEmcRedialSysAcqCfg->stEmcRedialMruList.astSystem[i].usNid)
         && (pstSysInfo->stFreq.enBandClass == pstEmcRedialSysAcqCfg->stEmcRedialMruList.astSystem[i].stFreq.enBandClass)
         && (pstSysInfo->stFreq.usChannel   == pstEmcRedialSysAcqCfg->stEmcRedialMruList.astSystem[i].stFreq.usChannel))
        {
           *pulIndex = i;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_BuildScanChanList_CallReleaseSystemLost
 ��������  : ����������ɨ��Ƶ���б���
 �������  : usPreSrchChanNum ------------ ��ǰ��Ҫ����������Ƶ�����,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
             pstPreSrchChanArray---------- ��ǰ��Ҫ����������Ƶ������ͷָ��,����ʱ��Ҫ���ӵ�ɨ��Ƶ���б���
 �������  : pstScanChanList---------------����õ�Ƶ��ɨ���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��12��21��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_BuildScanChanList_CallReleaseSystemLost(
    VOS_UINT16                          usPreSrchChanNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstPreSrchChanArray,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru0SysId;
    CNAS_PRL_1X_SYSTEM_STRU                                 stMru1SysId;

    /*�������ظ�Ƶ�����������Ƶ���б� */
    CNAS_XSD_BuildNormalSystemLostScanChanlist(pstScanChanList);

    if (VOS_TRUE == CNAS_XSD_GetMru0SysId(&stMru0SysId))
    {
        CNAS_XSD_RemoveSpecialFreqFromScanList(&(stMru0SysId.stFreq), pstScanChanList);
    }

    if (VOS_TRUE == CNAS_XSD_GetMru1SysId(&stMru1SysId))
    {
        CNAS_XSD_RemoveSpecialFreqFromScanList(&(stMru1SysId.stFreq), pstScanChanList);
    }

    return;
}


#endif

/*lint -restore*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



