/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdMain.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��06��27��
  ��������   : 1X SD(system determination)�����ʼ����������ں�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��27��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasCcb.h"
#include "CnasXsdCtx.h"
#include "PsCommonDef.h"
#include "CnasMntn.h"
#include "CnasXsdFsmMainTbl.h"
#include "CnasXsdFsmSwitchOnTbl.h"
#include "CnasXsdFsmPowerOffTbl.h"
#include "CnasXsdFsmSysAcqTbl.h"
#include "CnasPrlApi.h"
#include "CnasXsdMntn.h"
#include "CnasXsdProcNvim.h"
#include "CnasXsdFsmRedirTbl.h"
#include "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_CTX_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* XSD CTX,���ڱ���MMC״̬��,������ */
CNAS_XSD_CTX_STRU                       g_stCnasXsdCtx;

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitCurrFsmCtx
 ��������  : ��ʼ����ǰ״̬��������
 �������  : ��
 �������  : pstCurrFsmCtx -- ��ǰ״̬����������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��7��17��
   ��    ��   : y00245242
   �޸�����   : iteration 17����

*****************************************************************************/
VOS_VOID CNAS_XSD_InitCurrFsmCtx(
    CNAS_XSD_FSM_CTX_STRU              *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   CNAS_XSD_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   CNAS_XSD_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   CNAS_XSD_L1_STA_NULL;
    pstCurrFsmCtx->enParentFsmId            =   CNAS_XSD_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;

    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;
    NAS_MEM_SET_S(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer,
                  sizeof(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer),
                  0x00,
                  CNAS_XSD_MAX_MSG_BUFFER_LEN);

    NAS_MEM_SET_S(&(pstCurrFsmCtx->unFsmCtx),
                  sizeof(pstCurrFsmCtx->unFsmCtx),
                  0x00,
                  sizeof(CNAS_XSD_FSM_EXTRA_CTX_UNION));
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitFsmStackCtx
 ��������  : ��ʼ��״̬��ջ������
 �������  : ��
 �������  : pstFsmStack -- ״̬��ջ��Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitFsmStackCtx(
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for (i = 0 ; i < CNAS_XSD_MAX_FSM_STACK_DEPTH ; i++)
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = CNAS_XSD_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = CNAS_XSD_L1_STA_BUTT;
    }
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitCacheMsgQueue
 ��������  : ��ʼ���������Ϣ����
 �������  : ��
 �������  : pstCacheMsgQueue -- �������Ϣ������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��09��07��
   ��    ��   : w00176964
   �޸�����   : CNAS�ڴ�ü�����
*****************************************************************************/
VOS_VOID CNAS_XSD_InitCacheMsgQueue(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue
)
{
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-7, begin */
    VOS_UINT32                          i;

    if (CNAS_XSD_INIT_CTX_STARTUP == enInitType)
    {
        pstCacheMsgQueue->ucCacheMsgNum = 0;

        for (i = 0; i < CNAS_XSD_MAX_CACHE_MSG_QUEUE_NUM; i++)
        {
            pstCacheMsgQueue->pastCacheMsg[i] = VOS_NULL_PTR;
        }
    }
    else
    {
        /* �ػ�ʱ����δִ����Ļ�����Ҫ���,�����ڴ�й© */
        for (i = 0; i < (VOS_UINT32)pstCacheMsgQueue->ucCacheMsgNum; i++)
        {
            if (VOS_NULL_PTR != pstCacheMsgQueue->pastCacheMsg[i])
            {
                PS_MEM_FREE(UEPS_PID_XSD, pstCacheMsgQueue->pastCacheMsg[i]);
                pstCacheMsgQueue->pastCacheMsg[i] = VOS_NULL_PTR;
            }
        }

        pstCacheMsgQueue->ucCacheMsgNum = 0;
    }

    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-7, end */
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitScanChanList
 ��������  : ��ʼ��Ƶ��ɨ���б�
 �������  : enInitType----��ʼ������
 �������  : pstScanChanList -- Ƶ��ɨ���б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��14��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitScanChanList(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU    *pstScanChanList
)
{
    if (CNAS_XSD_INIT_CTX_STARTUP == enInitType)
    {
        pstScanChanList->usCurScanIndex     = 0;
        pstScanChanList->usTotalNum         = 0;
        pstScanChanList->pstScanChanInfo    = VOS_NULL_PTR;

        return;
    }

    if (CNAS_XSD_INIT_CTX_POWEROFF == enInitType)
    {
        if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
        {
            PS_MEM_FREE(UEPS_PID_XSD, pstScanChanList->pstScanChanInfo);
            pstScanChanList->pstScanChanInfo = VOS_NULL_PTR;
        }

        pstScanChanList->usCurScanIndex = 0;
        pstScanChanList->usTotalNum  = 0;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitCurCampedSysInfo
 ��������  : ��ʼ����ǰפ����ϵͳ��Ϣ
 �������  : CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSysInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��10��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_VOID CNAS_XSD_InitCurCampedSysInfo(
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSysInfo
)
{
    NAS_MEM_SET_S(pstCurCampedSysInfo, sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU), 0, sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU));

    pstCurCampedSysInfo->ucRoamingInd = VOS_FALSE;
    pstCurCampedSysInfo->enSysType    = CNAS_XSD_SYS_TYPE_BUTT;
    pstCurCampedSysInfo->enSrvStatus  = CNAS_XSD_SERVICE_STATUS_NO_SERVICE;

    CNAS_CCB_SetCur1XSrvStatus(CNAS_CCB_SERVICE_STATUS_NO_SERVICE);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitCallRedialCtrlInfo
 ��������  : ��ʼ�������ز��Ŀ�����Ϣ
 �������  : CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU  pstCallRedialInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��2��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitCallRedialCtrlInfo(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallRedialInfo
)
{
    if (CNAS_XSD_INIT_CTX_POWEROFF == enInitType)
    {
        if (VOS_NULL_PTR != pstCallRedialInfo->stCallRedialChanScanList.pstScanChanInfo)
        {
            PS_MEM_FREE(UEPS_PID_XSD, pstCallRedialInfo->stCallRedialChanScanList.pstScanChanInfo);
        }
    }

    NAS_MEM_SET_S(pstCallRedialInfo, sizeof(CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU), 0, sizeof(CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU));

    pstCallRedialInfo->ucCallExistFlg                           = CNAS_XSD_CALL_EXIST_NULL_FLAG;
    pstCallRedialInfo->stCallRedialChanScanList.pstScanChanInfo = VOS_NULL_PTR;

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitCallRedialCtrlInfo
 ��������  : ��ʼ�����������ز��Ŀ�����Ϣ
 �������  : CNAS_XSD_EMC_CALL_CTRL_INFO_STRU  pstEmcCallInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��04��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitEmcCallCtrlInfo(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_EMC_CALL_CTRL_INFO_STRU    *pstEmcCallInfo
)
{
    if (CNAS_XSD_INIT_CTX_POWEROFF == enInitType)
    {
        if (VOS_NULL_PTR != pstEmcCallInfo->stEmcCallRedialChanScanList.pstScanChanInfo)
        {
            PS_MEM_FREE(UEPS_PID_XSD, pstEmcCallInfo->stEmcCallRedialChanScanList.pstScanChanInfo);
        }
    }

    NAS_MEM_SET_S(pstEmcCallInfo, sizeof(CNAS_XSD_EMC_CALL_CTRL_INFO_STRU), 0x00, sizeof(CNAS_XSD_EMC_CALL_CTRL_INFO_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitAvailSysList
 ��������  : Init available system list
 �������  : CNAS_XSD_AVAILABLE_LIST_STRU  pstAvailList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��9��
    ��    ��   : y00245242
    �޸�����   : iteration 17����
*****************************************************************************/
VOS_VOID CNAS_XSD_InitAvailSysList(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_AVAILABLE_LIST_STRU        *pstAvailList
)
{
    NAS_MEM_SET_S(pstAvailList,
                  sizeof(CNAS_XSD_AVAILABLE_LIST_STRU),
                  0,
                  sizeof(CNAS_XSD_AVAILABLE_LIST_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitRedirectionInfo
 ��������  : clear redirection info
 �������  : CNAS_XSD_REDIRECTION_INFO_STRU  pstRedirInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitRedirectionInfo(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8    enInitType,
    CNAS_XSD_REDIRECTION_INFO_STRU      *pstRedirInfo
)
{
    pstRedirInfo->ucRedirection   = VOS_FALSE;
    pstRedirInfo->ucReturnIfFail  = VOS_FALSE;
    pstRedirInfo->ucChanNum       = 0;

    pstRedirInfo->stOriginalSystem.usSid = CNAS_PRL_WILDCARD_SID;
    pstRedirInfo->stOriginalSystem.usNid = CNAS_PRL_WILDCARD_NID;
    pstRedirInfo->usExpectSid            = CNAS_PRL_WILDCARD_SID;
    pstRedirInfo->usExpectNid            = CNAS_PRL_WILDCARD_NID;
    pstRedirInfo->ucIsEmcRedir           = VOS_FALSE;

    NAS_MEM_SET_S(&(pstRedirInfo->astChanInfo[0]),
                  sizeof(pstRedirInfo->astChanInfo),
                  0x0,
                  sizeof(CNAS_XSD_SCAN_CHANNEL_INFO_STRU) * CNAS_XSD_MAX_REDIR_CHANNEL_NUM);

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitSystemAcquireCtrl
 ��������  : ��ʼ��1Xϵͳ��ȡ������Ϣ
 �������  : enInitType------��ʼ������
 �������  : pstSysAcqCtrl -- ϵͳ��ȡ������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��08��14��
   ��    ��   : w00176964
   �޸�����   : ���ӳ�ʼ������
 3.��    ��   : 2015��1��3��
   ��    ��   : y00245242
   �޸�����   : HOME SID/NID list ����
*****************************************************************************/
VOS_VOID CNAS_XSD_InitSystemAcquireCtrl(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType,
    CNAS_XSD_SYSTEM_ACQUIRE_CTRL_STRU  *pstSysAcqCtrl
)
{
    /* Deleted by w00176964 for CNAS�ڴ�ü�, 2015-9-6, begin */

    /* Deleted by w00176964 for CNAS�ڴ�ü�, 2015-9-6, end */

    NAS_MEM_SET_S(&(pstSysAcqCtrl->stAvoidFreqList), sizeof(pstSysAcqCtrl->stAvoidFreqList), 0, sizeof(CNAS_XSD_AVOID_FREQ_LIST_STRU));

    NAS_MEM_SET_S(&(pstSysAcqCtrl->stMruList), sizeof(pstSysAcqCtrl->stMruList), 0, sizeof(CNAS_XSD_MRU_LIST_STRU));

    NAS_MEM_SET_S(&(pstSysAcqCtrl->stCallList), sizeof(pstSysAcqCtrl->stCallList), 0, sizeof(CNAS_XSD_CALL_REDIAL_SYS_LIST_STRU));

    NAS_MEM_SET_S(&(pstSysAcqCtrl->unUeSupportedBand.ulBand), sizeof(pstSysAcqCtrl->unUeSupportedBand.ulBand), 0x0, sizeof(VOS_UINT32));
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_0 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_1 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_2 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_3 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_4 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_5 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_6 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_7 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_8 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_9 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_10 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_11 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_12 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_13 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_14 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_15 = VOS_TRUE;
    pstSysAcqCtrl->unUeSupportedBand.stBitBand.BandCDMA_16 = VOS_TRUE;

    CNAS_XSD_InitScanChanList(enInitType, &(pstSysAcqCtrl->stChanScanList));


    CNAS_XSD_InitCurCampedSysInfo(&(pstSysAcqCtrl->stCurCampedSysInfo));

    CNAS_XSD_InitCallRedialCtrlInfo(enInitType, &pstSysAcqCtrl->stCallRedialInfo);

    CNAS_XSD_InitRedirectionInfo(enInitType, &pstSysAcqCtrl->stRedirInfo);

    CNAS_XSD_InitOocScheduleInfo(&(pstSysAcqCtrl->stOocScheduleInfo));

    CNAS_XSD_InitEmcCallCtrlInfo(enInitType, &(pstSysAcqCtrl->stEmcCallInfo));

    NAS_MEM_SET_S(&(pstSysAcqCtrl->stCdma1XCustomPrefChan),
                  sizeof(pstSysAcqCtrl->stCdma1XCustomPrefChan),
                  0,
                  sizeof(CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU));

    CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);

    CNAS_XSD_InitHistorySyncedSysFreqList(&(pstSysAcqCtrl->stHisSyncedSysFreqList));

    CNAS_XSD_InitGeoSrchListInfo(&(pstSysAcqCtrl->stGeoListSrchInfo));
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitFsmCtx_L1Main
 ��������  : ��ʼ��L1״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitFsmCtx_L1Main(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* ��鵱ǰ״̬���Ƿ���L1״̬�� */
    if (CNAS_XSD_FSM_L1_MAIN != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmCtx_L1Main:ENTERED");

        return;
    }

    pstXsdCtx->stCurFsm.unFsmCtx.stL1MainCtx.ulCurAvailableTimerCount = 0;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitFsmCtx_SwitchOn
 ��������  : ��ʼ������״̬��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitFsmCtx_SwitchOn(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* ��鵱ǰ״̬���Ƿ�ʱ����״̬�� */
    if (CNAS_XSD_FSM_SWITCH_ON != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmCtx_SwitchOn:ENTERED");

        return;
    }

    pstXsdCtx->stCurFsm.unFsmCtx.stSwitchOnCtx.ulXsdReadCardFileFlg = CNAS_XSD_READ_CARD_FILE_FLG_NULL;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitFsmCtx_PowerOff
 ��������  : ��ʼ���ػ�״̬��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��20��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitFsmCtx_PowerOff(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* ��鵱ǰ״̬���Ƿ�Ϊ�ػ�״̬�� */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmCtx_PowerOff:ENTERED");

        return;
    }

    pstXsdCtx->stCurFsm.unFsmCtx.stPowerOffCtx.ucCampOnNeedFlg      = VOS_FALSE;
    pstXsdCtx->stCurFsm.unFsmCtx.stPowerOffCtx.ucBufCallRelIndFlg   = VOS_FALSE;

    NAS_MEM_SET_S(&(pstXsdCtx->stCurFsm.unFsmCtx.stPowerOffCtx.stBuffCallRelFreq),
                  sizeof(pstXsdCtx->stCurFsm.unFsmCtx.stPowerOffCtx.stBuffCallRelFreq),
                  0x0,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitFsmCtx_SysAcq
 ��������  : ��ʼ��SYSTEM ACQUIRE״̬����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��8��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��25��
    ��    ��   : w00176964
    �޸�����   : CDMA Iteration 6:Move the avail system list to the global variables

  3.��    ��   : 2015��7��6��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_VOID CNAS_XSD_InitFsmCtx_SysAcq(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* ��鵱ǰ״̬���Ƿ�ʱSYSTEM ACQUIRE״̬�� */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmCtx_SysAcq:ENTERED");

        return;
    }

    /* �˳�L2����״̬��ǰ��ȷ���ڴ��ͷ� */
    if (VOS_NULL_PTR != pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.stGeoSysSrchList.pstAcqSysInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.stGeoSysSrchList.pstAcqSysInfo);
    }

    NAS_MEM_SET_S(&(pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx),
                  sizeof(pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx),
                  0,
                  sizeof(CNAS_XSD_FSM_SYS_ACQ_CTX_STRU));

    return;
}



VOS_VOID CNAS_XSD_InitFsmCtx_Redirection(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* Checking for current state machine is redirection or not */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* abnormal event */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmCtx_Redirection:ENTERED");

        return;
    }

    pstXsdCtx->stCurFsm.unFsmCtx.stRedirCtx.ucAbortFlag                      = VOS_FALSE;
    pstXsdCtx->stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.usTotalNum      = 0;
    pstXsdCtx->stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.usCurScanIndex  = 0;
    pstXsdCtx->stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.pstScanChanInfo = VOS_NULL_PTR;

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitCtx
 ��������  : XSD ������ȫ�ֱ�����ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��10��15��
   ��    ��   : c00299063
   �޸�����   : CNAS XSD�����ڲ���Ϣ���г�ʼ��
*****************************************************************************/
VOS_VOID CNAS_XSD_InitCtx(
    CNAS_XSD_INIT_CTX_TYPE_ENUM_UINT8   enInitType
)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    /* ��ǰ��������ԭ��ֵ����������չ */

    /* ��ǰ��״̬�������ʼ�� */
    CNAS_XSD_InitCurrFsmCtx(&(pstXsdCtx->stCurFsm));

    /* ״̬��ջ�����ʼ�� */
    CNAS_XSD_InitFsmStackCtx(&(pstXsdCtx->stFsmStack));

    /* CNAS XSD������Ϣ���г�ʼ�� */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, begin */
    CNAS_XSD_InitCacheMsgQueue(enInitType, &(pstXsdCtx->stCacheMsgQueue));
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-18, end */

    /* CNAS XSD�����ڲ���Ϣ���г�ʼ�� */
    CNAS_XSD_InitInternalBuffer(&(CNAS_XSD_GetXsdCtxAddr()->stIntMsgQueue));

    /* CNAS XSDϵͳ��ȡ���Ƴ�ʼ�� */
    CNAS_XSD_InitSystemAcquireCtrl(enInitType, &(pstXsdCtx->stSysAcqCtrl));

    CNAS_XSD_InitCFreqLockValue();

    CNAS_XSD_InitTestConfig(&(pstXsdCtx->stTestConfig));

    CNAS_XSD_InitSysAcqNvimCfg(&(pstXsdCtx->stSysAcqNvimCfg));
    CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_NORMAL_ACCESS);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_LoadSubFsm
 ��������  : ����L2״̬������Ϣ
 �������  : enFsmId - L2״̬��ID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��12��25��
   ��    ��   : w00176964
   �޸�����   : CDMA IX Iteration 6 Modified:Add redirection state machine

*****************************************************************************/
VOS_VOID  CNAS_XSD_LoadSubFsm(
    CNAS_XSD_FSM_ID_ENUM_UINT32         enFsmId,
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm
)
{
    switch (enFsmId)
    {
        case CNAS_XSD_FSM_SWITCH_ON :
            pstCurFsm->ulState                  = CNAS_XSD_SWITCH_ON_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_XSD_GetSwitchOnFsmDescAddr();
            break;

        case CNAS_XSD_FSM_POWER_OFF :
            pstCurFsm->ulState                  = CNAS_XSD_POWER_OFF_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_XSD_GetPowerOffFsmDescAddr();
            break;

        case CNAS_XSD_FSM_SYS_ACQ:
            pstCurFsm->ulState                  = CNAS_XSD_SYS_ACQ_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_XSD_GetSysAcqFsmDescAddr();
            break;

        case CNAS_XSD_FSM_REDIRECTION:
            pstCurFsm->ulState                  = CNAS_XSD_REDIR_STA_INIT;
            pstCurFsm->pstFsmDesc               = CNAS_XSD_GetRedirFsmDescAddr();
            break;

        default:
            CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_LoadSubFsm:Invalid Fsm Id");
            return;
    }

    /*ִ�г�ʼ��L2״̬���ĺ���*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_PushFsm
 ��������  : ��״̬������ѹջ
 �������  : pstFsmStack -- ״̬��ջ
             pstNewFsm   -- ��Ҫѹ���״̬��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_PushFsm(
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack,
    CNAS_XSD_FSM_CTX_STRU              *pstNewFsm
)
{
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;

    /* ���ָ���� */
    if ((VOS_NULL_PTR == pstFsmStack)
     || (VOS_NULL_PTR == pstNewFsm))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD,
                       "CNAS_XSD_PushFsm: pstFsmStack or pstNewFsm is null pointer!");

        return;
    }

    /* ջ��ȼ�� */
    if (pstFsmStack->usStackDepth >= CNAS_XSD_MAX_FSM_STACK_DEPTH)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XSD,
                       "CNAS_XSD_PushFsm: Fsm Stack Depth = %d Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    /* push��ǰ״̬����������ջ */
    pstCurFsm = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    NAS_MEM_CPY_S(pstCurFsm, sizeof(CNAS_XSD_FSM_CTX_STRU), pstNewFsm, sizeof(CNAS_XSD_FSM_CTX_STRU));

    /* ջ������� */
    pstFsmStack->usStackDepth++;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_PopFsm
 ��������  : ��״̬�����г�ջ
 �������  : ��
             ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_PopFsm(VOS_VOID)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* ���ݲ���״̬��ջ������״̬����ȡ��ǰ״̬��������ַ  */
    pstFsmStack = CNAS_XSD_GetFsmStackAddr();
    pstCurFsm   = CNAS_XSD_GetCurFsmAddr();

    /* ���ջ�ռ��Ƿ�Ϊ�� */
    if (0 == pstFsmStack->usStackDepth)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_PopFsm: FSM Stack is empty");

        return;
    }

    /* ״̬��ջ��ȼ��� */
    pstFsmStack->usStackDepth--;

    /* ���õ�ǰ״̬�� */
    NAS_MEM_CPY_S(pstCurFsm,
                  sizeof(CNAS_XSD_FSM_CTX_STRU),
                  &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]),
                  sizeof(CNAS_XSD_FSM_CTX_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitFsmL2
 ��������  : XSD����һ��L2��״̬�����������̵�ͬʱ����״̬�Լ�������ʱ��
              �ú��������ѹջ����,�������Ҫ����Э��ջѹջ, ���뱣֤�˳�ǰ����
 �������  : enFsmId -- L2״̬��ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��07��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��01��17��
   ��    ��   : y00307564
   �޸�����   : ��TQE

*****************************************************************************/
VOS_VOID CNAS_XSD_InitFsmL2(
    CNAS_XSD_FSM_ID_ENUM_UINT32         enFsmId
)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;
    CNAS_XSD_FSM_ID_ENUM_UINT32         enParentFsmId;
    VOS_UINT32                          ulParentEventType;
    CNAS_XSD_FSM_ID_ENUM_UINT32         enCurrFsmId;

    enCurrFsmId = CNAS_XSD_GetCurrFsmId();
    if (CNAS_XSD_BUTT == enCurrFsmId)
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmL2: CNAS_XSD_GetCurrFsmId return Butt");
    }

    /* ��ӡѹջǰ��״̬����״̬ID */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XSD, enCurrFsmId, CNAS_XSD_GetFsmTopState(), 0);

    /* ��¼ѹջǰ��״̬�����������Ϣ���� */
    enParentFsmId     = CNAS_XSD_GetCurrFsmId();
    ulParentEventType = CNAS_XSD_GetCurFsmAddr()->stEntryMsg.ulEventType;

    /* ����ǰ״̬��ѹջ���� */
    pstFsmStack = CNAS_XSD_GetFsmStackAddr();
    pstCurFsm   = CNAS_XSD_GetCurFsmAddr();
    CNAS_XSD_PushFsm(pstFsmStack, pstCurFsm);

    /* ���õ�ǰ״̬�� */
    pstCurFsm->enFsmId = enFsmId;

    /* ����L2״̬�� */
    CNAS_XSD_LoadSubFsm(enFsmId, pstCurFsm);

    /* ��¼�ϲ�״̬�����������Ϣ���� */
    pstCurFsm->enParentFsmId     = enParentFsmId;
    pstCurFsm->ulParentEventType = ulParentEventType;

    enCurrFsmId = CNAS_XSD_GetCurrFsmId();
    if (CNAS_XSD_BUTT == enCurrFsmId)
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_InitFsmL2: CNAS_XSD_GetCurrFsmId return Butt");
    }

    /* ��ӡѹջǰ��״̬����״̬ID */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XSD, enCurrFsmId, CNAS_XSD_GetFsmTopState(), 0);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_QuitFsmL2
 ��������  : ����L2״̬��������������̣�״̬������״̬ջ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��07��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��01��17��
   ��    ��   : y00307564
   �޸�����   : ��TQE

*****************************************************************************/
VOS_VOID CNAS_XSD_QuitFsmL2(VOS_VOID)
{
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    CNAS_XSD_FSM_ID_ENUM_UINT32         enCurrFsmId;

    pstCurFsm = CNAS_XSD_GetCurFsmAddr();

    /* QUITʱ��յ�ǰL2״̬����CTX */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    enCurrFsmId = CNAS_XSD_GetCurrFsmId();
    if (CNAS_XSD_BUTT == enCurrFsmId)
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_QuitFsmL2: CNAS_XSD_GetCurrFsmId return Butt");
    }

    /*  ��ӡ��ǰ��״̬��ID�Լ�״̬ */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XSD, enCurrFsmId, CNAS_XSD_GetFsmTopState(), 0);

    /* ״̬����ջ���� */
    CNAS_XSD_PopFsm();

    enCurrFsmId = CNAS_XSD_GetCurrFsmId();
    if (CNAS_XSD_BUTT == enCurrFsmId)
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_QuitFsmL2: CNAS_XSD_GetCurrFsmId return Butt");
    }

    /*  ��ӡ��ǰ��״̬��ID�Լ�״̬ */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XSD, enCurrFsmId, CNAS_XSD_GetFsmTopState(), 0);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetXsdCtxAddr
 ��������  : ��ȡ��ǰXSD��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰXSD��CTX��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_CTX_STRU* CNAS_XSD_GetXsdCtxAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetFsmStackAddr
 ��������  : ��ȡ��ǰ״̬��ջ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬��ջ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_FSM_STACK_STRU* CNAS_XSD_GetFsmStackAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stFsmStack);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurFsmAddr
 ��������  : ��ȡ��ǰ״̬����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_FSM_CTX_STRU* CNAS_XSD_GetCurFsmAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stCurFsm);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetFsmTopState
 ��������  : ��ȡ״̬�������״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬���Ķ���״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetFsmTopState(VOS_VOID)
{
    return (CNAS_XSD_GetCurFsmAddr()->ulState);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurFsmDesc
 ��������  : ��ȡ��ǰ״̬����ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU* CNAS_XSD_GetCurFsmDesc(VOS_VOID)
{
    return (CNAS_XSD_GetCurFsmAddr()->pstFsmDesc);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetFsmStackDepth
 ��������  : ��ȡ��ǰЭ��ջ��ջ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetFsmStackDepth(VOS_VOID)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XSD_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetFsmStackPopFlg
 ��������  : ����״̬��ջpop��־
 �������  : ucStackPopFlg -- ջpop��־
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XSD_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg = ucStackPopFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetFsmStackPopFlg
 ��������  : ��ȡ״̬��ջpop��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ջpop��־
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetFsmStackPopFlg(VOS_VOID)
{
    CNAS_XSD_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = CNAS_XSD_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCacheMsgAddr
 ��������  : ��ȡ��ǰ�Ļ�����Ϣ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS XSD������Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_CACHE_MSG_QUEUE_STRU* CNAS_XSD_GetCacheMsgAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stCacheMsgQueue);
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAvoidScheduInfoAddr
 ��������  : ��ȡAvoidScheduInfo��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_XSD_AVOID_SCHEDULE_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��11��12��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_AVOID_SCHEDULE_INFO_STRU* CNAS_XSD_GetAvoidScheduInfoAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stAvoidScheduInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAvoidFreqIndexOfAvoidlist
 ��������  : ��avoid�б��л�ȡƵ������
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
VOS_UINT8 CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstAvoidFreq,
    VOS_UINT8                          *pucIndex
)
{
    VOS_UINT8                           i;
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;

    *pucIndex         = 0;
    pstAvoidFreqList  = CNAS_XSD_GetAvoidFreqListAddr();

    for (i = 0; i < CNAS_MIN(pstAvoidFreqList->ucAvoidFreqNum, CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        if ((pstAvoidFreq->enBandClass == pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq.enBandClass)
         && (pstAvoidFreq->usChannel   == pstAvoidFreqList->astAvoidFreqInfo[i].stAvoidFreq.usChannel))
        {
            *pucIndex = i;
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : CNAS_XSD_SaveCacheMsgInMsgQueue
 ��������  : ��������Ϣ����Ļ����ڴ����
 �������  : ulEventType -- ��ϢID+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��09��07��
   ��    ��   : w00176964
   �޸�����   : CNAS�ڴ�ü�����

*****************************************************************************/
VOS_VOID CNAS_XSD_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue  = CNAS_XSD_GetCacheMsgAddr();

    if (CNAS_XSD_MAX_CACHE_MSG_QUEUE_NUM <= pstMsgQueue->ucCacheMsgNum)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_SaveCacheMsgInMsgQueue:No Empty buffer");

        return;
    }

    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-7, begin */
    pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum]
            = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XSD, pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum])
    {
        return;
    }

    NAS_MEM_CPY_S(pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum],
                  pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH,
                  pstMsgHeader,
                  pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-7, end */

    pstMsgQueue->ucCacheMsgNum++;

    CNAS_XSD_LogBufferQueueMsg(VOS_FALSE);

    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_XSD_SaveCacheMsgInMsgQueue: Cache Num = %d", pstMsgQueue->ucCacheMsgNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SaveCacheMsg
 ��������  : ���浱ǰ��Ҫ����Ļ���
 �������  : ulEventType -- ��ϢID+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ����ɹ�
             VOS_FALSE -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XSD_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��cache����Ϣ���ȼ�� */
    if ((CNAS_XSD_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) <= pstMsgHeader->ulLength)
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_SaveCacheMsg:Len too Long");
        return VOS_FALSE;
    }

    /* ����Ϣ�����ڻ����ڴ���� */
    CNAS_XSD_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearCacheMsg
 ��������  : ���ָ���Ļ�����Ϣ
 �������  : ulCurrIndex -- ���ָ��index����Ϣ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��09��07��
   ��    ��   : w00176964
   �޸�����   : CNAS�ڴ�ü�����
*****************************************************************************/
VOS_VOID CNAS_XSD_ClearCacheMsg(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XSD_CACHE_MSG_QUEUE_STRU       *pstMsgQueue = VOS_NULL_PTR;

    if (CNAS_XSD_MAX_CACHE_MSG_QUEUE_NUM <= ucIndex)
    {
        return;
    }

    pstMsgQueue = CNAS_XSD_GetCacheMsgAddr();

    if (0 < pstMsgQueue->ucCacheMsgNum)
    {
        pstMsgQueue->ucCacheMsgNum--;

        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-7, begin */
        if (VOS_NULL_PTR != pstMsgQueue->pastCacheMsg[ucIndex])
        {
            PS_MEM_FREE(UEPS_PID_XSD, pstMsgQueue->pastCacheMsg[ucIndex]);

            pstMsgQueue->pastCacheMsg[ucIndex] = VOS_NULL_PTR;
        }

        if (ucIndex < (CNAS_XSD_MAX_CACHE_MSG_QUEUE_NUM - 1))
        {
            /* �������Ϣ�����������һ������Ҫ�Ѻ��������е���Ϣǰ�� */
            NAS_MEM_MOVE_S(&(pstMsgQueue->pastCacheMsg[ucIndex]),
                            (pstMsgQueue->ucCacheMsgNum - ucIndex) * sizeof(VOS_UINT8 *),
                           &(pstMsgQueue->pastCacheMsg[ucIndex + 1]),
                            (pstMsgQueue->ucCacheMsgNum - ucIndex) * sizeof(VOS_UINT8 *));
        }

        pstMsgQueue->pastCacheMsg[pstMsgQueue->ucCacheMsgNum] = VOS_NULL_PTR;
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-7, end */
    }

    CNAS_XSD_LogBufferQueueMsg(VOS_FALSE);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearCacheMsgByMsgName
 ��������  : ����MsgNameƥ�������Ӧ�Ļ�����Ϣ
 �������  : VOS_UINT32                          ulSndPid  ��ϢPID
             VOS_UINT16                          usMsgName ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32:
             VOS_TRUE  : �ҵ���Ӧ��Ϣ������������
             VOS_FALSE : δ�ҵ���Ӧ��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��20��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��09��07��
   ��    ��   : w00176964
   �޸�����   : CNAS�ڴ�ü�����
*****************************************************************************/
VOS_UINT32 CNAS_XSD_ClearCacheMsgByMsgName(
    VOS_UINT32                          ulSndPid,
    VOS_UINT16                          usMsgName
)
{
    VOS_UINT32                          ulCurCacheMsgNum;
    /* Added by w00176964 for CNAS�ڴ�ü�, 2015-9-7, begin */
    VOS_UINT32                          ulCacheMsgEventType;
    MSG_HEADER_STRU                    *pstCacheMsg;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Added by w00176964 for CNAS�ڴ�ü�, 2015-9-7, end */
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          i;

    ulCurCacheMsgNum                    = CNAS_XSD_GetCacheMsgNum();
    ulEventType                         = CNAS_BuildEventType(ulSndPid, usMsgName);

    for (i = 0; i < ulCurCacheMsgNum; i++)
    {
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-7, begin */
        pstCacheMsg         = (MSG_HEADER_STRU *)CNAS_XSD_GetCacheMsgAddr()->pastCacheMsg[i];

        if (VOS_NULL_PTR == pstCacheMsg)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsg->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsg;

            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsg->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsg->ulSenderPid, pstCacheMsg->ulMsgName);
        }

        if (ulEventType == ulCacheMsgEventType)
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-7, end */
        {
            CNAS_XSD_ClearCacheMsg((VOS_UINT8)i);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetNextCachedMsg
 ��������  : ��ȡ��ǰ��Ҫ����Ļ���
 �������  : ��
 �������  : pstEntryMSg -- ��ǰ��Ҫ�������Ϣ��ַ

 �� �� ֵ  : VOS_TRUE  -- ��ȡ�ɹ�
             VOS_FALSE -- ��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��09��07��
   ��    ��   : w00176964
   �޸�����   : CNAS�ڴ�ü�����

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetNextCachedMsg(
    CNAS_XSD_MSG_STRU                  *pstEntryMsg
)
{
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;
    /* Added by w00176964 for CNAS�ڴ�ü�, 2015-9-7, begin */
    MSG_HEADER_STRU                    *pstCacheMsgHdr = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Added by w00176964 for CNAS�ڴ�ü�, 2015-9-7, end */

    pstMsgQueue = CNAS_XSD_GetCacheMsgAddr();

    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        CNAS_INFO_LOG(UEPS_PID_XSD, "CNAS_XSD_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    /* ���������ȳ�ԭ��,Ĭ��ȡ��1���������� */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-7, begin */
    pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[0]);

    if (VOS_NULL_PTR == pstCacheMsgHdr)
    {
        return VOS_FALSE;
    }

    if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
    {
        pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

        pstEntryMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
    }
    else
    {
        pstEntryMsg->ulEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
    }

    NAS_MEM_CPY_S(&pstEntryMsg->aucMsgBuffer[0],
                  sizeof(pstEntryMsg->aucMsgBuffer),
                  pstCacheMsgHdr,
                  pstCacheMsgHdr->ulLength + VOS_MSG_HEAD_LENGTH);
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-7, end */

    /* ���indexΪ0��cache��Ϣ */
    CNAS_XSD_ClearCacheMsg(0);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCacheMsgNum
 ��������  : ��ȡ��ǰ�������Ϣ����
 �������  : ��
 �������  :
 �� �� ֵ  : ��ǰ���ڵĻ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetCacheMsgNum(VOS_VOID)
{
    CNAS_XSD_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = CNAS_XSD_GetCacheMsgAddr();

    return pstMsgQueue->ucCacheMsgNum;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetCurrFsmState
 ��������  : ���õ�ǰ��ҪǨ�Ƶ�״̬
 �������  : ulCurrState:��ǰǨ�Ƶ�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��11��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  CNAS_XSD_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
)
{
    CNAS_XSD_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* ��ȡ��ǰ��״̬��Ϣ */
    pstCurFsm                   = CNAS_XSD_GetCurFsmAddr();

    /* ���õ�ǰ״̬ */
    pstCurFsm->ulState          = ulCurrState;

    /*  ��ӡ��ǰ�ĵ�ǰ״̬��ID�Լ�״̬ */
    CNAS_MNTN_LogFsmInfo(UEPS_PID_XSD, pstCurFsm->enFsmId, ulCurrState, 0);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurrFsmEntryMsgAddr
 ��������  : ��ȡ��ǰ״̬�������Ϣ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������Ϣ�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��12��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_MSG_STRU* CNAS_XSD_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stCurFsm.stEntryMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SaveCurEntryMsg
 ��������  : ���浱ǰ״̬���������Ϣ
 �������  : ulEventType            :�����Ϣ����
              pstMsg             :�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ  :
   1.��    ��   : 2014��7��11��
     ��    ��   : h00246512
     �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_MSG_STRU                  *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ��õ�ǰ����CNAS XSD�����Ϣ�Ļ�������ַ */
    pstEntryMsg                 = CNAS_XSD_GetCurrFsmEntryMsgAddr();

    ulLen                       = pstMsg->ulLength + VOS_MSG_HEAD_LENGTH;

    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-16, begin */
    if (ulLen > CNAS_XSD_MAX_MSG_BUFFER_LEN)
    {
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SaveCurEntryMsg:beyond the Size!");

        ulLen = CNAS_XSD_MAX_MSG_BUFFER_LEN;
    }
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-16, end */

    /* ����ǰ����������Ϣ������Context��Ӧ�Ļ����� */
    NAS_MEM_CPY_S( pstEntryMsg->aucMsgBuffer, sizeof(pstEntryMsg->aucMsgBuffer), pstMsg, ulLen );

    /* ��дContext�еĲ��� */
    pstEntryMsg->ulEventType    = ulEventType;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurrFsmId
 ��������  : ��ȡ��ǰ״̬����ID
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��11��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���


*****************************************************************************/
CNAS_XSD_FSM_ID_ENUM_UINT32 CNAS_XSD_GetCurrFsmId(VOS_VOID)
{
    return (g_stCnasXsdCtx.stCurFsm.enFsmId);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn
 ��������  : ���������л�ȡ��ȡ���ļ��ظ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ȡ���ļ��ظ����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��7��11��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_READ_CARD_FILES_CNF_ENUM_UINT32 CNAS_XSD_GetWaitCardFilesCnfFlg_SwitchOn(VOS_VOID)
{
    /* �����ǰ״̬������switch on */
    if (CNAS_XSD_FSM_SWITCH_ON != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulXsdReadCardFileFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn
 ��������  : �������������ö�ȡ���ļ��ظ����
 �������  : ���ÿ��ļ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��7��11��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (CNAS_XSD_FSM_SWITCH_ON != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulXsdReadCardFileFlg |= enReadCardFileCnfFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCampOnNeedFlg_PowerOff
 ��������  : ��ȡ�ػ��������Ƿ���Ҫפ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ػ��������Ƿ���Ҫפ�����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��10��19��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetCampOnNeedFlg_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "sCNAS_XSD_GetCampOnNeedFlg_PowerOff: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucCampOnNeedFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetCampOnNeedFlg_PowerOff
 ��������  : ���ùػ��������Ƿ���Ҫפ�����
 �������  : פ�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��10��20s��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetCampOnNeedFlg_PowerOff(
    VOS_UINT8                           ucCampOnNeedFlg
)
{
    /* �����ǰ״̬������power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetCampOnNeedFlg_PowerOff: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucCampOnNeedFlg = ucCampOnNeedFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetBufCallRelIndFlg_PowerOff
 ��������  : ��ȡ�ػ������л���ĺ����ͷ�ָʾ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ػ������л���ĺ����ͷ�ָʾ���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��10��19��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetBufCallRelIndFlg_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetBufCallRelFlg_PowerOff: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucBufCallRelIndFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetBufCallRelIndFlg_PowerOff
 ��������  : ���ùػ������л���ĺ����ͷ�ָʾ���
 �������  : �����ͷ�ָʾ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��10��20s��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetBufCallRelIndFlg_PowerOff(
    VOS_UINT8                           ucBufCallRelIndFlg
)
{
    /* �����ǰ״̬������power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetBufCallRelIndFlg_PowerOff: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.ucBufCallRelIndFlg = ucBufCallRelIndFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetBufCallRelFreqInfo_PowerOff
 ��������  : ��ȡ�ػ������л���ĺ����ͷ�ָʾ��Ƶ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ػ������л���ĺ����ͷ�ָʾ��Ƶ����Ϣ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��10��19��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_XSD_GetBufCallRelFreqInfo_PowerOff(VOS_VOID)
{
    /* �����ǰ״̬������power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetBufCallRelFreqInfo_PowerOff: Wrong state ENTERED");
    }

    return &(g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.stBuffCallRelFreq);
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_SaveBufCallRelFreqInfo_PowerOff
 ��������  : ����ػ������л���ĺ����ͷ�ָʾ��Ƶ����Ϣ
 �������  : �����ͷ�ָʾ��Ƶ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��10��19��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SaveBufCallRelFreqInfo_PowerOff(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    /* �����ǰ״̬������power off */
    if (CNAS_XSD_FSM_POWER_OFF != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetBufCallRelFreqInfo_PowerOff: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.stBuffCallRelFreq.enBandClass = pstFreq->enBandClass;
    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stPowerOffCtx.stBuffCallRelFreq.usChannel   = pstFreq->usChannel;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetTestConfig
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
CNAS_XSD_TEST_CONFIG_STRU* CNAS_XSD_GetTestConfig(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stTestConfig);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_Get1xSysAcqNvimConfig
 ��������  : ��ȡstSysAcqNvimCfg�׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����stSysAcqNvimCfg�׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU* CNAS_XSD_Get1xSysAcqNvimConfig(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqNvimCfg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAcqPrefSysflg
 ��������  : �Ƿ�GEO�У�����ƥ���prefϵͳ���Ͱ�prefϵͳ����ı��
 �������  :
 �������  :
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��5��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_NEG_PREF_SYS_CMP_TYPE_ENUM_UINT8 CNAS_XSD_GetNegPrefSysCmpType()
{
    return (CNAS_XSD_Get1xSysAcqNvimConfig()->stNegPrefSysCmpCtrl.enNegPrefSysCmpType);
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn
 ��������  : ���������������ȡ���ļ��ظ����
 �������  : ���ļ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��7��11��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn(
    CNAS_XSD_READ_CARD_FILES_CNF_ENUM_UINT32                enReadCardFileCnfFlg
)
{
    /* �����ǰ״̬������switch on */
    if (CNAS_XSD_FSM_SWITCH_ON != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_ClearWaitCardFilesCnfFlg_SwitchOn: Wrong state ENTERED");
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSwitchOnCtx.ulXsdReadCardFileFlg &= ~enReadCardFileCnfFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetMruList
 ��������  : ��ȡMRU table�׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����MRU table�׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��06��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_MRU_LIST_STRU* CNAS_XSD_GetMruList(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stMruList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetMruListNum
 ��������  : ��ȡMRU table��ϵͳ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����MRU table��ϵͳ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetMruListNum(VOS_VOID)
{
    return (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stMruList.ucSysNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetMru0SysId
 ��������  : ��ȡMRU0��Ӧ��ϵͳID
 �������  : ��
 �������  : pstMru0SysId------MRU0��Ӧ��ϵͳID
 �� �� ֵ  : ��ȡ�ɹ�:VOS_TRUE
             ��ȡʧ��:VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��08��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetMru0SysId(
    CNAS_PRL_1X_SYSTEM_STRU         *pstMru0SysId
)
{
    CNAS_XSD_MRU_LIST_STRU             *pstMruList = VOS_NULL_PTR;

    pstMruList = CNAS_XSD_GetMruList();

    if (0 < CNAS_XSD_GetMruListNum())
    {
        pstMru0SysId->stFreq    = pstMruList->astSystem[0].stFreq;
        pstMru0SysId->usNid     = pstMruList->astSystem[0].usNid;
        pstMru0SysId->usSid     = pstMruList->astSystem[0].usSid;

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetMru1SysId
 ��������  : ��ȡMRU1��Ӧ��ϵͳID
 �������  : ��
 �������  : pstMru0SysId------MRU1��Ӧ��ϵͳID
 �� �� ֵ  : ��ȡ�ɹ�:VOS_TRUE
             ��ȡʧ��:VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��21��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_GetMru1SysId(
    CNAS_PRL_1X_SYSTEM_STRU         *pstMru1SysId
)
{
    CNAS_XSD_MRU_LIST_STRU             *pstMruList = VOS_NULL_PTR;

    pstMruList = CNAS_XSD_GetMruList();

    if (1 < CNAS_XSD_GetMruListNum())
    {
        pstMru1SysId->stFreq    = pstMruList->astSystem[1].stFreq;
        pstMru1SysId->usNid     = pstMruList->astSystem[1].usNid;
        pstMru1SysId->usSid     = pstMruList->astSystem[1].usSid;

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateMru0
 ��������  : ����MRU0��¼��������Ϣ
 �������  : pstCurNetwork -- ��ǰפ����

 �������  : ��

 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��08��06��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateMru0(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
)
{
    VOS_UINT32                          i;
    CNAS_XSD_MRU_LIST_STRU             *pstMruList;
    VOS_UINT32                          ulIsSysInMru;

    ulIsSysInMru    = VOS_FALSE;
    pstMruList      = CNAS_XSD_GetMruList();

    /* ����MRU�У��Ƿ����ظ���ϵͳ */
    for (i = 0; i < pstMruList->ucSysNum; i++)
    {
        /* ������ظ��ģ���ɾ���ظ��� */
        if ((pstCurSysId->usSid == pstMruList->astSystem[i].usSid)
         && (pstCurSysId->usNid == pstMruList->astSystem[i].usNid)
         && (pstCurSysId->stFreq.enBandClass == pstMruList->astSystem[i].stFreq.enBandClass)
         && (pstCurSysId->stFreq.usChannel == pstMruList->astSystem[i].stFreq.usChannel))
        {
            /* �����ǰϵͳ����MRU0λ�ã�ֱ�ӷ��أ�����Ҫ�κβ��� */
            if (0 == i)
            {
                return;
            }

            ulIsSysInMru = VOS_TRUE;
            pstMruList->ucSysNum--;

            NAS_MEM_MOVE_S(&pstMruList->astSystem[1],
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU) * (CNAS_XSD_MAX_MRU_SYS_NUM - 1),
                           pstMruList->astSystem,
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU)*(i));

            break;
        }
    }

    /* �����ǰ����MRU�У�ֱ�ӿճ�MRU[0]���� */
    if (VOS_FALSE == ulIsSysInMru)
    {
        if (CNAS_XSD_MAX_MRU_SYS_NUM == pstMruList->ucSysNum)
        {
            NAS_MEM_MOVE_S(&pstMruList->astSystem[1],
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU) * (CNAS_XSD_MAX_MRU_SYS_NUM - 1),
                           pstMruList->astSystem,
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU)*(CNAS_XSD_MAX_MRU_SYS_NUM-1));
            pstMruList->ucSysNum--;
        }
        else
        {
            NAS_MEM_MOVE_S(&pstMruList->astSystem[1],
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU) * (CNAS_XSD_MAX_MRU_SYS_NUM - 1),
                           pstMruList->astSystem,
                           sizeof(CNAS_PRL_1X_SYSTEM_STRU)*pstMruList->ucSysNum);
        }
    }

    /* ��ֵ��MRU[0]�� */
    pstMruList->astSystem[0] = *pstCurSysId;
    pstMruList->ucSysNum++;

    CNAS_XSD_WriteMruNvim(pstMruList);

    CNAS_XSD_LogMruList(pstMruList);

}


VOS_UINT32 CNAS_XSD_GetUeSupportedBandClass(VOS_VOID)
{
    return (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.unUeSupportedBand.ulBand);
}


VOS_VOID CNAS_XSD_SetUeSupportedBandClass(
    VOS_UINT32                          ulUeSupportedBand
)
{
    (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.unUeSupportedBand.ulBand) = ulUeSupportedBand;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetScanChanListAddr
 ��������  : ��ȡƵ��ɨ���б�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰƵ��ɨ���б�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��8��6��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/

CNAS_XSD_SCAN_CHANNEL_LIST_STRU* CNAS_XSD_GetScanChanListAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetScanChannelNum
 ��������  : ��ȡ��ǰƵ��ɨ���б���Ƶ���ܸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰƵ��ɨ���б���Ƶ���ܸ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��8��6��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetScanChannelNum(VOS_VOID)
{
    return (g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList.usTotalNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurChannelScanIndex
 ��������  : ��ȡ��ǰƵ��ɨ���б��е�ǰɨ�赽���б�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰƵ��ɨ���б��е�ǰɨ�赽���б�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��8��6��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetCurChannelScanIndex(VOS_VOID)
{
    return (g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList.usCurScanIndex);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetCurChannelScanIndex
 ��������  : ���õ�ǰƵ��ɨ���б��е�ǰɨ�赽���б�����
 �������  : usCurScanIndex------��ǰƵ��ɨ���б��е�ǰɨ�赽���б�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��8��6��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetCurChannelScanIndex(
    VOS_UINT16                          usCurScanIndex
)
{
    g_stCnasXsdCtx.stSysAcqCtrl.stChanScanList.usCurScanIndex = usCurScanIndex;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAvailSysFreqListAddr
 ��������  : ��ȡavailable system list��ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_XSD_AVAILABLE_LIST_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��25��
    ��    ��   : w00176964
    �޸�����   : CDMA Iteration 6:Move the avail system list to the global variables
  3.��    ��   : 2015��7��9��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
CNAS_XSD_AVAILABLE_LIST_STRU* CNAS_XSD_GetAvailSysFreqListAddr(VOS_VOID)
{
    /* �����ǰ״̬������CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAvailSysFreqListAddr: Wrong state ENTERED");
    }

    return &(CNAS_XSD_GetXsdCtxAddr()->stCurFsm.unFsmCtx.stSysAcqCtx.stAvailSysList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_AddAvailSysFreqList
 ��������  : ����available systemƵ��
 �������  : CNAS_PRL_1X_SYSTEM_STRU            *pstAvailSys
 �������  : ��
 �� �� ֵ  : VOS_VOID
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
VOS_VOID CNAS_XSD_AddAvailSysFreqList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    /* �ж��Ƿ��Ѿ����� */
    for (i = 0; i < (VOS_UINT32)CNAS_MIN(pstAvailSysList->ucAvailSysNum, CNAS_XSD_MAX_AVAILABLE_SYS_NUM); i++)
    {
        if (0 == PS_MEM_CMP(&(pstAvailSysList->astAvailSystem[i].stFreq),
                            pstFreq,
                            sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)))
        {
            NAS_MEM_MOVE_S(&(pstAvailSysList->astAvailSystem[1]),
                           sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * (CNAS_XSD_MAX_AVAILABLE_SYS_NUM - 1),
                           &(pstAvailSysList->astAvailSystem[0]),
                           sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * i);

            NAS_MEM_CPY_S(&(pstAvailSysList->astAvailSystem[0].stFreq),
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU),
                          pstFreq,
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));

            return;
        }
    }

    /* ���м�¼���ƣ����µ�available system������index 0��λ�� */
    if (pstAvailSysList->ucAvailSysNum < CNAS_XSD_MAX_AVAILABLE_SYS_NUM)
    {
        NAS_MEM_MOVE_S(&(pstAvailSysList->astAvailSystem[1]),
                       sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * (CNAS_XSD_MAX_AVAILABLE_SYS_NUM - 1),
                       &(pstAvailSysList->astAvailSystem[0]),
                       sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * pstAvailSysList->ucAvailSysNum);

        pstAvailSysList->ucAvailSysNum++;
    }
    else
    {
        NAS_MEM_MOVE_S(&(pstAvailSysList->astAvailSystem[1]),
                       sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * (CNAS_XSD_MAX_AVAILABLE_SYS_NUM - 1),
                       &(pstAvailSysList->astAvailSystem[0]),
                       sizeof(CNAS_XSD_AVAIL_SYSTEM_INFO_STRU) * (CNAS_XSD_MAX_AVAILABLE_SYS_NUM - 1));
    }

    NAS_MEM_CPY_S(&(pstAvailSysList->astAvailSystem[0].stFreq),
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU),
                  pstFreq,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));

    CNAS_XSD_LogAvailSystemList(pstAvailSysList);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetAvailSysFeqListNextSrchIndex
 ��������  : ����available system list���´���������
 �������  : ucNextSrchIndex------�´��б����������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��6��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetAvailSysFeqListNextSrchIndex(
    VOS_UINT8                           ucNextSrchIndex
)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    pstAvailSysList->ucNextSrchIndex = ucNextSrchIndex;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAvailSysFreqListNextSrchIndex
 ��������  : ��ȡavailable system list���´���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8 -- �����´�availableϵͳ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��6��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetAvailSysFreqListNextSrchIndex(VOS_VOID)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    return pstAvailSysList->ucNextSrchIndex;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAvailSysFreqNum
 ��������  : ��ȡavailable system�ĸ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��13��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��25��
    ��    ��   : w00176964
    �޸�����   : CDMA Iteration 6:Move the avail system list to the global variables

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetAvailSysFreqNum(VOS_VOID)
{
    CNAS_XSD_AVAILABLE_LIST_STRU       *pstAvailSysList = VOS_NULL_PTR;

    pstAvailSysList = CNAS_XSD_GetAvailSysFreqListAddr();

    return pstAvailSysList->ucAvailSysNum;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetAvailSysAcqListFlg_SysAcq
 ��������  : ���õ�ǰ��ȡ�б��Ƿ�Ϊavailable system list
 �������  : VOS_UINT8                           ucFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetAvailSysAcqListFlg_SysAcq(
    VOS_UINT8                           ucFlg
)
{
    /* �����ǰ״̬������CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAvailSysAcqListFlg_SysAcq: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucIsAvailSysAcqList = ucFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAvailSysAcqListFlg_SysAcq
 ��������  : ��ȡ��ǰ��ȡ�б��Ƿ�Ϊavailable system list
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��14��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetAvailSysAcqListFlg_SysAcq(VOS_VOID)
{
    /* �����ǰ״̬������CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAvailSysAcqListFlg_SysAcq: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucIsAvailSysAcqList;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetAbortFlg_SysAcq
 ��������  : ���õ�ǰ״̬����ϱ��
 �������  : VOS_UINT8                           ucFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��15��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetAbortFlg_SysAcq(
    VOS_UINT8                           ucFlg
)
{
    /* �����ǰ״̬������CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetAbortFlg_SysAcq: Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg = ucFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAbortFlg_SysAcq
 ��������  : ��ȡ��ǰ״̬����ϱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��15��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetAbortFlg_SysAcq(VOS_VOID)
{
    /* �����ǰ״̬������CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAbortFlg_SysAcq: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg;
}



VOS_VOID CNAS_XSD_SetAbortFlag_Redir(
    VOS_UINT8                                ucAbortFlag
)
{

    /* Checking for current state machine is redirection or not */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* abnormal event */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetAbortFlag_Redir:Wrong state ENTERED");

        return;
    }

    g_stCnasXsdCtx.stCurFsm.unFsmCtx.stRedirCtx.ucAbortFlag = ucAbortFlag;

    return;
}


VOS_UINT8 CNAS_XSD_GetAbortFlag_Redir(VOS_VOID)
{

    /* Checking for current state machine is redirection or not */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* abnormal event */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAbortFlag_Redir:Wrong state ENTERED");
    }

    return (g_stCnasXsdCtx.stCurFsm.unFsmCtx.stRedirCtx.ucAbortFlag);
}


CNAS_XSD_SCAN_CHANNEL_LIST_STRU *CNAS_XSD_GetScanChanListAddr_Redir(VOS_VOID)
{
    /* Checking for current state machine is redirection or not */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* abnormal event */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetScanChanListAddr_Redir:Wrong state ENTERED");

    }

    return (&(g_stCnasXsdCtx.stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList));
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurChannelScanIndex_Redir
 ��������  : ��ȡ�ض����У���ǰscan list������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��29��
    ��    ��   : w00242748
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetCurChannelScanIndex_Redir(VOS_VOID)
{
    /* �����ǰ״̬������CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetCurChannelScanIndex_Redir: Wrong state ENTERED");
    }

    return (CNAS_XSD_GetXsdCtxAddr()->stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.usCurScanIndex);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetCurChannelScanIndex_Redir
 ��������  : �����ض����У���ǰscan list������
 �������  : VOS_UINT16
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��29��
    ��    ��   : w00242748
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_VOID CNAS_XSD_SetCurChannelScanIndex_Redir(VOS_UINT16 usIndex)
{
    /* �����ǰ״̬������CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_SetCurChannelScanIndex_Redir: Wrong state ENTERED");

        return;
    }

    CNAS_XSD_GetXsdCtxAddr()->stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.usCurScanIndex = usIndex;
}



VOS_UINT16 CNAS_XSD_GetScanChannelNum_Redir(VOS_VOID)
{
    /* Checking for current state machine is redirection or not */
    if (CNAS_XSD_FSM_REDIRECTION != CNAS_XSD_GetCurrFsmId())
    {
        /* abnormal event */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetScanChannelNum_Redir:Wrong state ENTERED");

    }

    return (g_stCnasXsdCtx.stCurFsm.unFsmCtx.stRedirCtx.stRedireScanList.usTotalNum);
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetCallFlg
 ��������  : ���ú��б��
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_SCAN_CHANNEL_LIST_STRU* CNAS_XSD_GetCallRedialScanChanListAddr(VOS_VOID)
{
    return  (&(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.stCallRedialChanScanList));
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetEmcCallRedialScanChanListAddr
 ��������  : ��ȡ�����������ز������б��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_XSD_SCAN_CHANNEL_LIST_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��07��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_SCAN_CHANNEL_LIST_STRU *CNAS_XSD_GetEmcCallRedialScanChanListAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stEmcCallRedialChanScanList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetCallExistFlg
 ��������  : ���ú��д��ڱ��
 �������  : VOS_UINT8                           ucCallExistFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetCallExistFlg(
    VOS_UINT8                           ucCallExistFlg
)
{
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallStartSysInfo = VOS_NULL_PTR;

    pstCallStartSysInfo = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo);

    pstCallStartSysInfo->ucCallExistFlg |= ucCallExistFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearEmcCallRedialScanChanList
 ��������  : ��������������ز�����Ƶ���б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��07��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ClearEmcCallRedialScanChanList( VOS_VOID )
{
    CNAS_XSD_SCAN_CHANNEL_LIST_STRU                        *pstScanChanList = VOS_NULL_PTR;

    pstScanChanList = CNAS_XSD_GetEmcCallRedialScanChanListAddr();

    if (VOS_NULL_PTR != pstScanChanList->pstScanChanInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstScanChanList->pstScanChanInfo);
    }

    NAS_MEM_SET_S(pstScanChanList, sizeof(CNAS_XSD_SCAN_CHANNEL_LIST_STRU), 0x00, sizeof(CNAS_XSD_SCAN_CHANNEL_LIST_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearCallExistFlg
 ��������  : ������д��ڱ��
 �������  : VOS_UINT8                           ucCallExistFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearCallExistFlg(
    VOS_UINT8                           ucCallExistFlg
)
{
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallStartSysInfo = VOS_NULL_PTR;

    pstCallStartSysInfo = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo);

    pstCallStartSysInfo->ucCallExistFlg &= ~(ucCallExistFlg);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCallExistFlg
 ��������  : ��ȡ���д��ڱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���д��ڱ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetCallExistFlg(VOS_VOID)
{
    CNAS_XSD_CALL_REDIAL_CTRL_INFO_STRU *pstCallStartSysInfo = VOS_NULL_PTR;

    pstCallStartSysInfo = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo);

    return (pstCallStartSysInfo->ucCallExistFlg);
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetCallOrigSysExistFlg
 ��������  : ���ú��з���ϵͳ���ڱ��
 �������  : VOS_UINT8                           ucFlg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetCallOrigSysExistFlg(
    VOS_UINT8                           ucFlg
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.ucOrigSysExistFlg = ucFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCallOrigSysExistFlg
 ��������  : ��ȡ���з���ϵͳ���ڱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetCallOrigSysExistFlg(VOS_VOID)
{
    return (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.ucOrigSysExistFlg);

}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_SaveCallOrignalSys
 ��������  : ���浱ǰ���з����ϵͳ
 �������  : CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SaveCallOrignalSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.stCallOrignalSys = *pstCurSysId;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCallOrignalSys
 ��������  : ��ȡ��ǰ���з����ϵͳ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_PRL_1X_SYSTEM_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_1X_SYSTEM_STRU *CNAS_XSD_GetCallOrignalSys(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCallRedialInfo.stCallOrignalSys);

}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_SaveEmcCallOrignalSys
 ��������  : ��������������ɹ�ʱ��ϵͳ
 �������  : CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SaveEmcCallOriginalSys(
    CNAS_PRL_1X_SYSTEM_STRU            *pstCurSysId
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stCallOrignalSys = *pstCurSysId;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetEmcCallOrignalSys
 ��������  : ��ȡ��ǰ�������н����ɹ�ʱ��ϵͳ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_PRL_1X_SYSTEM_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��07��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_1X_SYSTEM_STRU *CNAS_XSD_GetEmcCallOriginalSys(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stCallOrignalSys);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearEmcCallOrignalSys
 ��������  : �����ǰ�������н����ɹ�ʱ��ϵͳ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_PRL_1X_SYSTEM_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��07��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearEmcCallOriginalSys( VOS_VOID )
{
    NAS_MEM_SET_S(CNAS_XSD_GetEmcCallOriginalSys(), sizeof(CNAS_PRL_1X_SYSTEM_STRU), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_IsEmcCallOrignalSysExist
 ��������  : �жϵ�ǰ���������з���ϵͳ�Ƿ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��07��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_IsEmcCallOriginalSysExist( VOS_VOID )
{
    CNAS_PRL_1X_SYSTEM_STRU                         stNullSystem;

    NAS_MEM_SET_S(&stNullSystem, sizeof(stNullSystem), 0x00, sizeof(CNAS_PRL_1X_SYSTEM_STRU));

    if (0 == PS_MEM_CMP(&stNullSystem,
                         CNAS_XSD_GetEmcCallOriginalSys(),
                         sizeof(CNAS_PRL_1X_SYSTEM_STRU)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq
 ��������  : ��ȡָ�������Ĳ���ϵͳ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : SYS ACQ״̬����������ϵͳ�����б��׵�ַ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��8��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_GEO_SYS_RECORD_SRCH_LIST_STRU* CNAS_XSD_GetGeoSysRecSrchListAddr_SysAcq(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    return &(pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.stGeoSysSrchList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurSysAcqListNum_SysAcq
 ��������  : ��ȡ��ǰϵͳ�����б�ĸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰϵͳ�����б������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2014��8��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_XSD_GetCurSysAcqListNum_SysAcq(VOS_VOID)
{
    /* �����ǰ״̬������CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetCurSysAcqListIndex_SysAcq: Wrong state ENTERED");
    }

    return g_stCnasXsdCtx.stCurFsm.unFsmCtx.stSysAcqCtx.stGeoSysSrchList.usTotalNum;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurCampedSysInfo
 ��������  : ��ȡ��ǰפ��ϵͳ��Ϣ��ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAX_XSD_CAMPED_SYS_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAX_XSD_CAMPED_SYS_INFO_STRU* CNAS_XSD_GetCurCampedSysInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCurCampedSysInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateCurCampedSysInfo
 ��������  : ���µ�ǰפ��ϵͳ��Ϣ
 �������  : CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSysInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateCurCampedSysInfo(
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCurCampedSysInfo
)
{
    NAS_MEM_CPY_S(CNAS_XSD_GetCurCampedSysInfo(), sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU), pstCurCampedSysInfo, sizeof(CNAX_XSD_CAMPED_SYS_INFO_STRU));

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCurSrvStatus
 ��������  : ��ȡ��ǰ����״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_XSD_SERVICE_STATUS_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_SERVICE_STATUS_ENUM_UINT32 CNAS_XSD_GetCurSrvStatus(VOS_VOID)
{
    CNAX_XSD_CAMPED_SYS_INFO_STRU                          *pstCurCampedSysInfo = VOS_NULL_PTR;

    pstCurCampedSysInfo = CNAS_XSD_GetCurCampedSysInfo();

    return pstCurCampedSysInfo->enSrvStatus;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetCurSrvStatus
 ��������  : ���õ�ǰ����״̬
 �������  : enSrvStatus -- ����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetCurSrvStatus(
    CNAS_XSD_SERVICE_STATUS_ENUM_UINT32                     enSrvStatus
)
{
    CNAX_XSD_CAMPED_SYS_INFO_STRU                          *pstCurCampedSysInfo = VOS_NULL_PTR;

    pstCurCampedSysInfo = CNAS_XSD_GetCurCampedSysInfo();

    pstCurCampedSysInfo->enSrvStatus = enSrvStatus;

    /* ͬ����״̬���õ�CCBȫ�ֱ���������ģ���ѯ */
    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_XSD_SetCurSrvStatus:Cur SrvStatus Set To:", (VOS_UINT32)pstCurCampedSysInfo->enSrvStatus);

    CNAS_CCB_SetCur1XSrvStatus((CNAS_CCB_SERVICE_STATUS_ENUM_UINT32)enSrvStatus);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetIntMsgQueueAddr
 ��������  : ��ȡ�ڲ���Ϣ�����׵�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_XSD_INT_MSG_QUEUE_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��15��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_XSD_INT_MSG_QUEUE_STRU* CNAS_XSD_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stIntMsgQueue);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitInternalBuffer
 ��������  : ��ʼ��XSD�ڲ���Ϣ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��15��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_InitInternalBuffer(
    CNAS_XSD_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
)
{
    VOS_UINT8                           i;

    for (i = 0; i < CNAS_XSD_MAX_INT_MSG_QUEUE_NUM; i++)
    {
        pstIntMsgQueue->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstIntMsgQueue->ucIntMsgNum = 0;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_PutMsgInIntMsgQueue
 ��������  : ����Ϣ�ŵ��ڲ���Ϣ������
 �������  : pSndMsg:�����͵���Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��15��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  CNAS_XSD_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
)
{
    VOS_UINT8                           ucIntMsgNum;

    /* ����ڲ���Ϣ���У��Ƿ��л���������� */
    if (CNAS_XSD_MAX_INT_MSG_QUEUE_NUM <= CNAS_XSD_GetIntMsgNum())
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstMsg);

        CNAS_ERROR_LOG( UEPS_PID_XSD, "CNAS_XSD_SndSwitchOnRlst: msg queue is full!" );

        return;
    }

    ucIntMsgNum = CNAS_XSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    /* ���浱ǰ��Ϣ */
    CNAS_XSD_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = pstMsg;

    CNAS_XSD_GetIntMsgQueueAddr()->ucIntMsgNum = (ucIntMsgNum + 1);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetNextIntMsg
 ��������  : ��ȡ�ڲ���Ϣ�����е���һ�����õ��ڲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ڲ���Ϣ���е�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��15��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 *CNAS_XSD_GetNextIntMsg(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = CNAS_XSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* ��ȡ��һ���������Ϣ��Ϣ */
        pstIntMsg = CNAS_XSD_GetIntMsgQueueAddr()->pastIntMsg[0];

        /* �ڲ���Ϣ��Ŀ����һ�� */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* ǰ���ڲ���Ϣ */
            NAS_MEM_MOVE_S(&(CNAS_XSD_GetIntMsgQueueAddr()->pastIntMsg[0]),
                           CNAS_XSD_MAX_INT_MSG_QUEUE_NUM * sizeof(VOS_UINT8 *),
                           &(CNAS_XSD_GetIntMsgQueueAddr()->pastIntMsg[1]),
                           ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* ����Ϣ������β������Ϣ��Ϊ��ָ�� */
        CNAS_XSD_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        CNAS_XSD_GetIntMsgQueueAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetIntMsgNum
 ��������  : ��ȡ��ǰXSD�ڲ���Ϣ����
 �������  : ��
 �������  :
 �� �� ֵ  : ��ǰ���ڵ��ڲ���Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��0423
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = CNAS_XSD_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}




/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAvoidFreqListAddr
 ��������  : ��ȡavoid Ƶ���б��ַ
 �������  : ��

 �������  : ��
 �� �� ֵ  : CNAS_XSD_AVOID_FREQ_LIST_STRU* -- avoidƵ���б��׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_AVOID_FREQ_LIST_STRU* CNAS_XSD_GetAvoidFreqListAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stSysAcqCtrl.stAvoidFreqList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAvoidFreqListNum
 ��������  : ��ȡavoid Ƶ���б���Ŀ
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_UINT8 -- avoid�б���Ŀ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetAvoidFreqListNum(VOS_VOID)
{
    return (CNAS_XSD_GetAvoidFreqListAddr()->ucAvoidFreqNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_DeleteAvoidFreqFromAvoidList
 ��������  : ��avoid�б���ɾ��Ƶ����Ϣ
 �������  : ucIndex -- ��ɾ����Ƶ����Ϣ����

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_DeleteAvoidFlagFromAvoidList(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;

    if (ucIndex < CNAS_XSD_MAX_AVOID_FREQ_NUM)
    {
        pstAvoidFreqList = CNAS_XSD_GetAvoidFreqListAddr();

        pstAvoidFreqList->astAvoidFreqInfo[ucIndex].ucAvoidFlag = VOS_FALSE;


    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetAvoidFreqFromAvoidList
 ��������  : ��avoid list�л�ȡ����Ƶ����Ϣ
 �������  : ucIndex -- avoidƵ����Ϣ����

 �������  : ��
 �� �� ֵ  : CNAS_XSD_AVOID_FREQ_STRU* -- avoidƵ���б�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_AVOID_FREQ_INFO_STRU *CNAS_XSD_GetAvoidFreqFromAvoidList(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo = VOS_NULL_PTR;

    if (ucIndex < CNAS_XSD_MAX_AVOID_FREQ_NUM)
    {
        /* ����ָ��������avoidƵ����Ϣ */
        pstAvoidFreqInfo = &(CNAS_XSD_GetAvoidFreqListAddr()->astAvoidFreqInfo[ucIndex]);

        return pstAvoidFreqInfo;
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetSystemCampOnFlag
 ��������  : set system camp on flag
 �������  : ucCampOnFlg -- camp on flag
 �������  : none
 �� �� ֵ  : none
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 3/12/2012
    ��    ��   : y00245242
    �޸�����   : create

*****************************************************************************/
VOS_VOID CNAS_XSD_SetSystemCampOnFlag(
    VOS_UINT8                           ucCampOnFlg
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCurCampedSysInfo.ucCampOnFlag = ucCampOnFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetSystemCampOnFlag
 ��������  : get system camp on flag
 �������  : ucCampOnFlg -- camp on flag
 �������  : none
 �� �� ֵ  : none
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 3/12/2012
    ��    ��   : y00245242
    �޸�����   : create

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetSystemCampOnFlag(VOS_VOID)
{
    return (CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCurCampedSysInfo.ucCampOnFlag);
}




CNAS_XSD_REDIRECTION_INFO_STRU *CNAS_XSD_GetRedirectionInfoAddr(VOS_VOID)
{
    return (&(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stRedirInfo));
}


VOS_UINT8 CNAS_XSD_GetRedirectionFlag(VOS_VOID)
{
    return (CNAS_XSD_GetRedirectionInfoAddr()->ucRedirection);
}


VOS_VOID CNAS_XSD_SetRedirectionFlag(
    VOS_UINT8               ucRedirection
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;

    pstRedirInfo                = CNAS_XSD_GetRedirectionInfoAddr();
    pstRedirInfo->ucRedirection = ucRedirection;

    return;
}

/*****************************************************************************
Function Name   :   CNAS_XSD_SetEmcRedirectionFlg
Description     :   �����ض�����������:�����������ó�TRUE,��������ó�FALSE
                    1.��ǰ�յ�������Startδ�յ�������End
                    2.��ǰ���ڽ������غ�ģʽ��

Input parameters:   None
Outout parameters:  None
Return Value    :   VOS_VOID

Modify History:
    1)  Date    :   2015-12-09
        Author  :   h00313353
        Modify content :    Create
*****************************************************************************/
VOS_VOID CNAS_XSD_SetEmcRedirectionFlg(
    VOS_VOID
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulIsEmcCallOriginalSysExist;

    pstRedirInfo                        = CNAS_XSD_GetRedirectionInfoAddr();
    ulIsEmcCallOriginalSysExist         = CNAS_XSD_IsEmcCallOriginalSysExist();

    if ((VOS_NULL_PTR != CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
     || (VOS_TRUE     == ulIsEmcCallOriginalSysExist))
    {
        pstRedirInfo->ucIsEmcRedir  = VOS_TRUE;

        return;
    }

    pstRedirInfo->ucIsEmcRedir  = VOS_FALSE;

    return;
}


VOS_UINT8 CNAS_XSD_GetRedirectionReturnIfFailFlag(VOS_VOID)
{
    return (CNAS_XSD_GetRedirectionInfoAddr()->ucReturnIfFail);
}


VOS_VOID CNAS_XSD_SaveRedirectionOrignalSys(
    CNAS_PRL_1X_SYSTEM_STRU         *pstOriginalSystem
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;

    pstRedirInfo                   = CNAS_XSD_GetRedirectionInfoAddr();

    pstRedirInfo->stOriginalSystem = *pstOriginalSystem;

    return;
}


CNAS_PRL_1X_SYSTEM_STRU *CNAS_XSD_GetRedirectionOrignalSys(VOS_VOID)
{
    return (&(CNAS_XSD_GetRedirectionInfoAddr()->stOriginalSystem));
}


CNAS_XSD_SCAN_CHANNEL_INFO_STRU *CNAS_XSD_GetRedirectionChanList(VOS_VOID)
{
    return (CNAS_XSD_GetRedirectionInfoAddr()->astChanInfo);
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetFreqLockAddr
 ��������  : ��ȡstFreqLockPara��ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU* CNAS_XSD_GetFreqLockAddr(VOS_VOID)
{
    return &(g_stCnasXsdCtx.stSysAcqCtrl.stFreqLockPara);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetFreqLockMode
 ��������  : ��ȡ��ǰ��Ƶģʽ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ucFreqLockMode
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetFreqLockMode(VOS_VOID)
{
    return (g_stCnasXsdCtx.stSysAcqCtrl.stFreqLockPara.ucFreqLockMode);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitCFreqLockValue
 ��������  : ��ʼ��stFreqLockPara
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitCFreqLockValue(VOS_VOID)
{
    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU  *pstCnasXsdCFreqLockValue;

    pstCnasXsdCFreqLockValue = CNAS_XSD_GetFreqLockAddr();

    NAS_MEM_SET_S(pstCnasXsdCFreqLockValue, sizeof(CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU), 0x00, sizeof(CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU));

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitTestConfig
 ��������  : ��ʼ��TestConfig
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��3��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitTestConfig(
    CNAS_XSD_TEST_CONFIG_STRU          *pstTestConfig
)
{
    NAS_MEM_SET_S(pstTestConfig, sizeof(CNAS_XSD_TEST_CONFIG_STRU), 0x00, sizeof(CNAS_XSD_TEST_CONFIG_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitSysAcqNvimCfg
 ��������  : ��ʼ��SysAcqNvimCfg
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��3��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitSysAcqNvimCfg(
    CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU                         *pstSysAcqNvimCfg
)
{
    NAS_MEM_SET_S(pstSysAcqNvimCfg, sizeof(CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU), 0x00, sizeof(CNAS_XSD_SYS_ACQ_NVIM_CFG_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetOocScheduleInfo
 ��������  : ��ȡOOC�µ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����OOC������Ϣ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_OOC_SCHEDULE_INFO_STRU *CNAS_XSD_GetOocScheduleInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitOocScheduleInfo
 ��������  : ��ʼ��OOC�µ�����Ϣ
 �������  : enInitType -- ��ʼ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitOocScheduleInfo(
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
)
{
    NAS_MEM_SET_S(pstOocScheduleInfo, sizeof(CNAS_XSD_OOC_SCHEDULE_INFO_STRU), 0, sizeof(CNAS_XSD_OOC_SCHEDULE_INFO_STRU));

    pstOocScheduleInfo->stConfigInfo.ucPhaseNum                      = 0;
    pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimerLen   = 5;
    pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimes      = 5;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitOocCtxInfo
 ��������  : ��ʼ��OOC��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitOocCtxInfo(VOS_VOID)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;

    pstOocScheduleInfo = CNAS_XSD_GetOocScheduleInfo();

    NAS_MEM_SET_S(&pstOocScheduleInfo->stOocCtxInfo, sizeof(pstOocScheduleInfo->stOocCtxInfo), 0, sizeof(CNAS_XSD_OOC_CTX_INFO_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetOocWaitSearchFlag
 ��������  : ��ȡOOC�ȴ�������־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetOocWaitSearchFlag(VOS_VOID)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_XSD_GetOocScheduleInfo();

    return (pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetOocWaitSearchFlag
 ��������  : ����OOC�ȴ�������־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��04��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetOocWaitSearchFlag(VOS_UINT8 ucWaitSearchFlag)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocSchedule = VOS_NULL_PTR;

    pstOocSchedule = CNAS_XSD_GetOocScheduleInfo();

    pstOocSchedule->stOocCtxInfo.ucWaitSearchFlag = ucWaitSearchFlag;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetNdssIndFlag
 ��������  : ����NDSS IND ָʾ
 �������  : ucNdssInd -- NDSS offָʾflag
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��05��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetNdssIndFlag(
    VOS_UINT8                           ucNdssInd
)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;

    pstRedirInfo            = CNAS_XSD_GetRedirectionInfoAddr();
    pstRedirInfo->ucNdssInd = ucNdssInd;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetNdssIndFlag
 ��������  : ��ȡNDSS IND ָʾ
 �������  : ucNdssInd -- NDSS offָʾflag
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��05��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetNdssIndFlag(VOS_VOID)
{
    CNAS_XSD_REDIRECTION_INFO_STRU     *pstRedirInfo = VOS_NULL_PTR;

    pstRedirInfo            = CNAS_XSD_GetRedirectionInfoAddr();

    return (pstRedirInfo->ucNdssInd);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetOocScheduleConfigInfo
 ��������  : ��ȡOOC�µ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����OOC����������Ϣ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��08��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_OOC_CONFIG_INFO_STRU *CNAS_XSD_GetOocScheduleConfigInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stOocScheduleInfo.stConfigInfo);
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetSrvAcqFlg
 ��������  : ��ȡ��ǰ�Ƿ���ҵ�񴥷������ı�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8 : ucSrvAcqFlg
             VOS_TRUE  : ����ҵ�񴥷���������
             VOS_FALSE : ������ҵ�񴥷���������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��05��21��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetSrvAcqFlg(VOS_VOID)
{
    return CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.ucSrvAcqFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetSrvAcqFlg
 ��������  : ���õ�ǰ�Ƿ���ҵ�񴥷���������ʶ
 �������  : VOS_UINT8 : ucSrvAcqFlg
             VOS_TRUE  : ����ҵ�񴥷���������
             VOS_FALSE : ������ҵ�񴥷���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��21��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetSrvAcqFlg(
    VOS_UINT8                           ucSrvAcqFlg
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.ucSrvAcqFlg  = ucSrvAcqFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetEmcState
 ��������  : ��ȡ��ǰ���������̵�״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_XSD_EMC_STATE_ENUM_UINT8 : enEmcState
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��02��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_EMC_STATE_ENUM_UINT8 CNAS_XSD_GetEmcState(VOS_VOID)
{
    return CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.enEmcState;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetEmcCallBackSrchCounter
 ��������  : ��ȡ��ǰ���������̵ļ�����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��02��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetEmcCallBackSrchCounter(VOS_VOID)
{
    return CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.ucCallBackSrchCounter;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetEmcCallBackSrchCounter
 ��������  : ���õ�ǰ���������̵�״̬
 �������  : CNAS_XSD_EMC_STATE_ENUM_UINT8 : enEmcState
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��02��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetEmcCallBackSrchCounter(
    VOS_UINT8                           ucEmcCallBackCounter
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.ucCallBackSrchCounter = ucEmcCallBackCounter;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetEmcCallBackCandidateFreqInfo
 ��������  : ��ȡ��ǰ�������غ���Ƶ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2016��01��28��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU* CNAS_XSD_GetEmcCallBackCandidateFreqInfo(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stEmcCallBackCfInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearEmcCallBackCandidateFreq
 ��������  : �����ǰ�������غ�ģʽ��Ƶ����Ƶ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��01��28��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearEmcCallBackCandidateFreq(
    VOS_VOID
)
{
    PS_MEM_SET(CNAS_XSD_GetEmcCallBackCandidateFreqInfo(), 0x00, sizeof(CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetEmcCallBackCandidateFreq
 ��������  : ���õ�ǰ�������غ�ģʽ��Ƶ����Ƶ��
 �������  : usCfFreqNum:Ƶ����
             pstCfInfo:  Ƶ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2016��01��28��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetEmcCallBackCandidateFreq(
    VOS_UINT16                          usCfFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstCfInfo
)
{
    VOS_UINT32                          i;
    CNAS_XSD_EMC_CALLBACK_CANDIDATE_FREQ_INFO_STRU         *pstEmcCallBackCfInfo    = VOS_NULL_PTR;

    pstEmcCallBackCfInfo    = CNAS_XSD_GetEmcCallBackCandidateFreqInfo();

    CNAS_XSD_ClearEmcCallBackCandidateFreq();

    pstEmcCallBackCfInfo->usCfChannelNum = CNAS_MIN(usCfFreqNum, CNAS_XSD_MAX_CANDIDATE_FREQ_NUM);

    for (i = 0; i < pstEmcCallBackCfInfo->usCfChannelNum; i++)
    {
        pstEmcCallBackCfInfo->astChannelList[i].enBandClass = pstCfInfo[i].enBandClass;
        pstEmcCallBackCfInfo->astChannelList[i].usChannel   = pstCfInfo[i].usChannel;

        CNAS_INFO_LOG3(UEPS_PID_XSD, "CNAS_XSD_SetEmcCallBackCandidateFreq: Index,Band,Chan", i, (VOS_UINT32)pstCfInfo[i].enBandClass, (VOS_UINT32)pstCfInfo[i].usChannel);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetEmcState
 ��������  : ���õ�ǰ���������̵�״̬
 �������  : CNAS_XSD_EMC_STATE_ENUM_UINT8 : enEmcState
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��02��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_SetEmcState(
    CNAS_XSD_EMC_STATE_ENUM_UINT8       enEmcState
)
{
    CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.enEmcState = enEmcState;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCallBackCfg
 ��������  : ��ȡNv�ж��ڽ�����CallBackģʽ���������
 �������  : CNAS_XSD_EMC_STATE_ENUM_UINT8 : enEmcState
 �������  : ��
 �� �� ֵ  : CNAS_XSD_CALLBACK_CFG_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��02��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_CALLBACK_CFG_STRU *CNAS_XSD_GetCallBackCfg( VOS_VOID )
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stCallBackCfg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitGeoSrchListInfo
 ��������  : ��ʼ��GEO list������Ϣ
 �������  : pstGeoListSrchInfo -- ָ��GEO list������Ϣ��ַ

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��03��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitGeoSrchListInfo(
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU   *pstGeoListSrchInfo
)
{
    NAS_MEM_SET_S(pstGeoListSrchInfo, sizeof(CNAS_XSD_GEO_LIST_SRCH_INFO_STRU), 0, sizeof(CNAS_XSD_GEO_LIST_SRCH_INFO_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetGeoSrchListInfoAddr
 ��������  : ��ȡ��ǰGEO����list��Ϣ��ַ
 �������  : pstGeoListSrchInfo -- ָ��GEO list������Ϣ��ַ

 �������  : CNAS_XSD_GEO_LIST_SRCH_INFO_STRU* -- ����GEO�����б���Ϣ��ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��03��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_GEO_LIST_SRCH_INFO_STRU *CNAS_XSD_GetGeoSrchListInfoAddr(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stGeoListSrchInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ClearGeoSrchListStatus
 ��������  : ���GEO�����б�״̬
 �������  : ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��07��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_ClearGeoSrchListStatus(VOS_VOID)
{
    VOS_UINT16                              i;
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU       *pstGeoListSrchInfo = VOS_NULL_PTR;

    pstGeoListSrchInfo = CNAS_XSD_GetGeoSrchListInfoAddr();

    if (VOS_NULL_PTR == pstGeoListSrchInfo->pstGeoSrchInfo)
    {
        return;
    }

    for (i = 0; i < pstGeoListSrchInfo->usGeoNum; i++)
    {
        pstGeoListSrchInfo->pstGeoSrchInfo[i].usGeoSrchStatus = VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_FreeBufferOfGeoSrchList
 ��������  : �ͷ�GEO�����б�ռ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_FreeBufferOfGeoSrchList(VOS_VOID)
{
    CNAS_XSD_GEO_LIST_SRCH_INFO_STRU       *pstGeoListSrchInfo = VOS_NULL_PTR;

    pstGeoListSrchInfo = CNAS_XSD_GetGeoSrchListInfoAddr();

    if (VOS_NULL_PTR != pstGeoListSrchInfo->pstGeoSrchInfo)
    {
        PS_MEM_FREE(UEPS_PID_XSD, pstGeoListSrchInfo->pstGeoSrchInfo);

        pstGeoListSrchInfo->pstGeoSrchInfo = VOS_NULL_PTR;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_InitHistorySyncedSysFreqList
 ��������  : ��ʼ����ʷͬ������ϵͳƵ���б�
 �������  : pstHisSyncedSysFreqList -- ��ʷͬ������ϵͳƵ���б�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_InitHistorySyncedSysFreqList(
    CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU             *pstHisSyncedSysFreqList
)
{
    pstHisSyncedSysFreqList->ulCurNum   = 0;
    pstHisSyncedSysFreqList->ulTotalNum = 0;
    NAS_MEM_SET_S(&(pstHisSyncedSysFreqList->astFreq[0]),
                  sizeof(pstHisSyncedSysFreqList->astFreq),
                  0,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetHistorySyncedSysFreqList
 ��������  : ��ȡͬ������ϵͳ��¼�б��ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU* CNAS_XSD_GetHistorySyncedSysFreqList(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stHisSyncedSysFreqList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateHistorySyncedSysFreqList
 ��������  : ���¿���֮��ͬ����ϵͳ��Ƶ���б�
 �������  : pstFreq -- ͬ������Ƶ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  1.��    ��   : 2015��9��10��
    ��    ��   : y00245242
    �޸�����   : DTS2015090206027
*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateHistorySyncedSysFreqList(
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
)
{
    CNAS_XSD_HISTORY_SYNCED_SYS_FREQ_LIST_STRU             *pstHisSyncedSysList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstHisSyncedSysList = CNAS_XSD_GetHistorySyncedSysFreqList();

    /* �����Ƿ������б��� */
    for (i = 0; i < CNAS_MIN(pstHisSyncedSysList->ulCurNum, CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM); i++)
    {
        if (0 == PS_MEM_CMP(pstFreq,
                            &(pstHisSyncedSysList->astFreq[i]),
                            sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU)))
        {
            NAS_MEM_MOVE_S(&(pstHisSyncedSysList->astFreq[1]),
                           sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM - 1),
                           &(pstHisSyncedSysList->astFreq[0]),
                           sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * i);

            NAS_MEM_CPY_S(&(pstHisSyncedSysList->astFreq[0]),
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU),
                          pstFreq,
                          sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));
            return;
        }
    }

    /* ���м�¼���ƣ����µ�system������index 0��λ�� */
    if (pstHisSyncedSysList->ulCurNum < CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM)
    {
        NAS_MEM_MOVE_S(&(pstHisSyncedSysList->astFreq[1]),
                       sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM - 1),
                       &(pstHisSyncedSysList->astFreq[0]),
                       sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * pstHisSyncedSysList->ulCurNum);

        pstHisSyncedSysList->ulCurNum++;
    }
    else
    {
        NAS_MEM_MOVE_S(&(pstHisSyncedSysList->astFreq[1]),
                       sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM - 1),
                       &(pstHisSyncedSysList->astFreq[0]),
                       sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * (CNAS_XSD_1X_SYNC_SUCC_FREQ_MAX_NUM - 1));
    }

    NAS_MEM_CPY_S(&(pstHisSyncedSysList->astFreq[0]),
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU),
                  pstFreq,
                  sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetLastSyncedSys
 ��������  : ��ȡ�ϴ�ͬ������ϵͳ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_PRL_1X_SYSTEM_ID_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_1X_SYSTEM_ID_STRU* CNAS_XSD_GetLastSyncedSys(VOS_VOID)
{
    CNAS_XSD_CTX_STRU                  *pstXsdCtx = VOS_NULL_PTR;

    pstXsdCtx = CNAS_XSD_GetXsdCtxAddr();

    return &(pstXsdCtx->stCurFsm.unFsmCtx.stSysAcqCtx.stLastSyncedSys);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetLastSyncedFreq
 ��������  : ��ȡ�ϴ�ͬ���ɹ���Ƶ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_PRL_FREQENCY_CHANNEL_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��8��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_XSD_GetLastSyncedFreq(VOS_VOID)
{
    return &(CNAS_XSD_GetHistorySyncedSysFreqList()->astFreq[0]);
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_UpdateLastSyncedSys
 ��������  : �����ϴ�ͬ������ϵͳ
 �������  : pstLastSyncedSys -- ��ǰͬ������ϵͳ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XSD_UpdateLastSyncedSys(
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstCurSyncedSys
)
{
    CNAS_PRL_1X_SYSTEM_ID_STRU         *pstLastSyncedSys = VOS_NULL_PTR;

    pstLastSyncedSys = CNAS_XSD_GetLastSyncedSys();

    pstLastSyncedSys->usNid = pstCurSyncedSys->usNid;
    pstLastSyncedSys->usSid = pstCurSyncedSys->usSid;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCallRelAnyCampOnFreqListAddr
 ��������  : ��ȡcall release�����£��κ�ϵͳֱ��פ��Ƶ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��9��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
CNAS_XSD_CALL_REL_ANY_CAMP_ON_FREQ_STRU* CNAS_XSD_GetCallRelAnyCampOnFreqListAddr(VOS_VOID)
{
    /* �����ǰ״̬������CNAS_XSD_FSM_SYS_ACQ */
    if (CNAS_XSD_FSM_SYS_ACQ != CNAS_XSD_GetCurrFsmId())
    {
        /* �쳣�¼� */
        CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_GetAvailSysFreqListAddr: Wrong state ENTERED");
    }

    return &(CNAS_XSD_GetXsdCtxAddr()->stCurFsm.unFsmCtx.stSysAcqCtx.stCallRelFirstSyncFreq);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetCdma1XCustomPrefChannels
 ��������  : ��ȡ���ų���1XƵ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU* CNAS_XSD_GetCdma1XCustomPrefChannels(VOS_VOID)
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCdma1XCustomPrefChan);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetNoCardModeCfgFlg
 ��������  : ��avoidƵ���б���ɾ�����õ�Ƶ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XSD_GetNoCardModeCfgFlg()
{
    return (CNAS_XSD_GetTestConfig()->ucNoCardModeCfgFlg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SetNoCardModeCfgFlg
 ��������  : �����޿�ģʽ���
 �������  : VOS_UINT8                           ucNoCardModeCfgFlg
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_SetNoCardModeCfgFlg(
    VOS_UINT8                           ucNoCardModeCfgFlg
)
{
    CNAS_XSD_GetTestConfig()->ucNoCardModeCfgFlg = ucNoCardModeCfgFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_GetEmcRedialSysAcqCfgInfo
 ��������  : ��ȡ�������ز�����������Ϣ
 �������  : ��
 �������  : CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU*
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��26��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU* CNAS_XSD_GetEmcRedialSysAcqCfgInfo()
{
    return &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stEmcCallInfo.stEmcRedialSysAcqCfg);

}


/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



