/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdProcNvim.c
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��07��08��
  ��������   : XSD����NV�Ķ�ȡ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��08��
    ��    ��   : h00246512
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXsdProcNvim.h"
#include  "CnasXsdCtx.h"
#include  "NVIM_Interface.h"
#include  "CnasMntn.h"
#include  "CnasXsdMntn.h"
#include  "NasNvInterface.h"
#include  "msp_diag_comm.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_PROC_NVIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadMruNvim
 ��������  : ��NV�л�ȡMRU������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��8��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadMruNvim(VOS_VOID)
{
    CNAS_XSD_MRU_LIST_STRU             *pstMruList = VOS_NULL_PTR;
    CNAS_NVIM_1X_MRU_LIST_STRU          stNvMruList;
    VOS_UINT16                          i;

    pstMruList      = CNAS_XSD_GetMruList();

    NAS_MEM_SET_S(&stNvMruList, sizeof(stNvMruList), 0x0, sizeof(CNAS_NVIM_1X_MRU_LIST_STRU));

    if (NV_OK != NV_Read(en_NV_Item_1X_MRU_LIST,
                         &stNvMruList, sizeof(CNAS_NVIM_1X_MRU_LIST_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadMruNvim:Read Nvim Failed");
        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_1X_MRU_LIST,
                            sizeof(CNAS_NVIM_1X_MRU_LIST_STRU),
                            UEPS_PID_XSD,
                            (VOS_UINT8 *)&stNvMruList);

    pstMruList->ucSysNum = stNvMruList.ucSysNum;

    for (i = 0; i < stNvMruList.ucSysNum; i++)
    {
        pstMruList->astSystem[i].stFreq.enBandClass = stNvMruList.astSystem[i].usBandClass;
        pstMruList->astSystem[i].stFreq.usChannel   = stNvMruList.astSystem[i].usChannel;
        pstMruList->astSystem[i].usNid              = stNvMruList.astSystem[i].usNid;
        pstMruList->astSystem[i].usSid              = stNvMruList.astSystem[i].usSid;
    }

    CNAS_XSD_LogMruList(pstMruList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_WriteMruNvim
 ��������  : ��MRU������д��NV��
 �������  : pstMruList----------д��MRU���б�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��25��
   ��    ��   : w00176964
   �޸�����   : 1X BUILD2 BBIT���������޸�
*****************************************************************************/
VOS_VOID CNAS_XSD_WriteMruNvim(
    CNAS_XSD_MRU_LIST_STRU             *pstMruList
)
{
    CNAS_NVIM_1X_MRU_LIST_STRU          stNvMruList;
    VOS_UINT16                          i;

    NAS_MEM_SET_S(&stNvMruList, sizeof(stNvMruList), 0x0, sizeof(CNAS_NVIM_1X_MRU_LIST_STRU));

    stNvMruList.ucSysNum = pstMruList->ucSysNum;

    for (i = 0; i < pstMruList->ucSysNum; i++)
    {
        stNvMruList.astSystem[i].usBandClass        = pstMruList->astSystem[i].stFreq.enBandClass;
        stNvMruList.astSystem[i].usChannel          = pstMruList->astSystem[i].stFreq.usChannel;
        stNvMruList.astSystem[i].usNid              = pstMruList->astSystem[i].usNid;
        stNvMruList.astSystem[i].usSid              = pstMruList->astSystem[i].usSid;
    }

    if (NV_OK != NV_Write(en_NV_Item_1X_MRU_LIST,
                         &stNvMruList, sizeof(CNAS_NVIM_1X_MRU_LIST_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_WriteMruNvim:Write Nvim Failed");
        return;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadPrlNvim
 ��������  : ��NV�л�ȡPRL������, ������PRL����

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��11��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadPrlNvim(VOS_VOID)
{
    CNAS_NVIM_1X_EVDO_PRL_LIST_STRU                        *pPrlData = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;

    /* ��ȡPRLǰ��ΪPRL����������ʱ�ڴ�ռ� */
    pPrlData = (CNAS_NVIM_1X_EVDO_PRL_LIST_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD, sizeof(CNAS_NVIM_1X_EVDO_PRL_LIST_STRU));

    if (VOS_NULL_PTR != pPrlData)
    {
        NAS_MEM_SET_S(pPrlData, sizeof(CNAS_NVIM_1X_EVDO_PRL_LIST_STRU), 0, sizeof(CNAS_NVIM_1X_EVDO_PRL_LIST_STRU));

        if (NV_OK != NV_Read(en_NV_Item_PRL_LIST, pPrlData, sizeof(CNAS_NVIM_1X_EVDO_PRL_LIST_STRU)))
        {
            CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadPrlNvim: Read Nvim Failed");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(UEPS_PID_XSD, pPrlData);

            return;
        }

        /* Ĭ�ϳ�����EPRL��ʽ����PRL���� */
        ulRslt = CNAS_PRL_ProcPrlInfo(&(pPrlData->ucPrlData[0]), sizeof(CNAS_NVIM_1X_EVDO_PRL_LIST_STRU), CNAS_PRL_SSPR_P_REV_3);

        if (VOS_TRUE == ulRslt)
        {
            CNAS_XSD_LogPrlSourceType(CNAS_XSD_PRL_TYPE_NVRAM);
        }
        else
        {
            CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadPrlNvim: parse Nvim PRL Failed");
        }

        /* �ͷ��ڴ� */
        PS_MEM_FREE(UEPS_PID_XSD, pPrlData);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadChanRepeatScanScheduleConfigNvim
 ��������  : ��NV�л�ȡ�ظ��������Ժ�
             �Ƿ���ǰפ��Ƶ������Ƶ���б��ײ��ı��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��4��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��1��8��
   ��    ��   : h00313353
   �޸�����   : �ϲ���ȡ������Ϣ��Ƶ���б��ײ��Ĳ����Ǻ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadChanRepeatScanScheduleConfigNvim(VOS_VOID)
{
    CNAS_XSD_OOC_CONFIG_INFO_STRU                          *pstConfigInfo = VOS_NULL_PTR;
    CNAS_NVIM_OOC_REPEAT_SCAN_STRATEGY_INFO_STRU            stScanSchedule;

    pstConfigInfo       = CNAS_XSD_GetOocScheduleConfigInfo();

    NAS_MEM_SET_S(&stScanSchedule,
                  sizeof(stScanSchedule),
                  0,
                  sizeof(CNAS_NVIM_OOC_REPEAT_SCAN_STRATEGY_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_1X_CHAN_REPEAT_SCAN_STRATEGY,
                         &stScanSchedule, sizeof(CNAS_NVIM_OOC_REPEAT_SCAN_STRATEGY_INFO_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadChanRepeatScanScheduleNvim:Read Nvim Failed");
        return;
    }
    CNAS_MNTN_LogReadNVInfo(en_NV_Item_1X_CHAN_REPEAT_SCAN_STRATEGY,
                            sizeof(CNAS_NVIM_OOC_REPEAT_SCAN_STRATEGY_INFO_STRU),
                            UEPS_PID_XSD,
                            (VOS_UINT8 *)&stScanSchedule);
    pstConfigInfo->enOocScanStrategy        = stScanSchedule.enChanRepeatScanStrategy;
    pstConfigInfo->ucInsertOrigChanFlg      = stScanSchedule.ucInsertOrigChanFlg;

    return;
}


VOS_VOID CNAS_XSD_ReadBandClassNvim(VOS_VOID)
{
#if 0
    VOS_UINT32                          ulNvimBand;

    NAS_MEM_SET_S(&ulNvimBand, 0x0, sizeof(VOS_UINT32));

    if (NV_OK != NV_Read(en_NV_Item_1X_BANDCLASS_LIST,
                         &ulNvimBand, sizeof(VOS_UINT32)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadBandClassNvim:Read Nvim Failed");
        return;
    }

    CNAS_XSD_SetUeSupportedBandClass(ulNvimBand);

    CNAS_XSD_LogUeSupportedBandClass(ulNvimBand);
#endif
    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadHomeSidNidNvim
 ��������  : ��NV�л�ȡHOME_SID_NID������

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��31��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadHomeSidNidNvim(VOS_VOID)
{
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU                     *pstHomeSidNidList = VOS_NULL_PTR;
    CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU                     stNvHomeSidNidList;
    VOS_UINT16                                              i;

    pstHomeSidNidList       = CNAS_CCB_GetHomeSidNidList();

    NAS_MEM_SET_S(&stNvHomeSidNidList, sizeof(stNvHomeSidNidList), 0x0, sizeof(CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU));

    if (NV_OK != NV_Read(en_NV_Item_1X_HOME_SID_NID_LIST,
                        &stNvHomeSidNidList, sizeof(CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU)))
    {
        /* NVIM�ȶ��������ȡʧ�ܣ���ʼ���ñ��� */
        NAS_MEM_SET_S(pstHomeSidNidList, sizeof(CNAS_CCB_1X_HOME_SID_NID_LIST_STRU), 0, sizeof(CNAS_CCB_1X_HOME_SID_NID_LIST_STRU));

        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadHomeSidNidNvim:Read Nvim Failed");
        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_1X_HOME_SID_NID_LIST,
                            sizeof(CNAS_NVIM_1X_HOME_SID_NID_LIST_STRU),
                            UEPS_PID_XSD,
                            (VOS_UINT8 *)&stNvHomeSidNidList);

    pstHomeSidNidList->ucSysNum = (VOS_UINT8)CNAS_MIN(stNvHomeSidNidList.ucSysNum, CNAS_NVIM_MAX_1X_HOME_SID_NID_NUM);

    for(i = 0; i < pstHomeSidNidList->ucSysNum; i++)
    {
        pstHomeSidNidList->astHomeSidNid[i].usSid   = stNvHomeSidNidList.astHomeSidNid[i].usSid;
        pstHomeSidNidList->astHomeSidNid[i].usNid   = stNvHomeSidNidList.astHomeSidNid[i].usNid;
        pstHomeSidNidList->astHomeSidNid[i].usBand  = stNvHomeSidNidList.astHomeSidNid[i].usBand;
    }

    CNAS_XSD_LogHomeSidNidList(pstHomeSidNidList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadSearchIntervalNvim
 ��������  : ��NV�л�ȡɨ������ص�����

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��31��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadSearchIntervalNvim(VOS_VOID)
{
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                   *pstOocScheduleInfo = VOS_NULL_PTR;
    CNAS_NVIM_OOC_TIMER_SCHEDULE_INFO_STRU             stNvTimerScheduleInfo;
    VOS_UINT16                                         i;

    pstOocScheduleInfo       = CNAS_XSD_GetOocScheduleInfo();

    NAS_MEM_SET_S(&stNvTimerScheduleInfo,
                  sizeof(stNvTimerScheduleInfo),
                  0,
                  sizeof(CNAS_NVIM_OOC_TIMER_SCHEDULE_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_1X_OOC_TIMER_SCHEDULE_INFO,
                        &stNvTimerScheduleInfo, sizeof(CNAS_NVIM_OOC_TIMER_SCHEDULE_INFO_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadSearchIntervalNvim:Read Nvim Failed");
        pstOocScheduleInfo->stConfigInfo.ucPhaseNum                      = 0;
        pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimerLen   = 5;
        pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[0].usTimes      = 5;
        /* OOC��ʱ�����ʱ�� */
        pstOocScheduleInfo->stConfigInfo.uc1xOocDoTchPhase1TimerLen      = 10;
        pstOocScheduleInfo->stConfigInfo.uc1xOocDoTchPhase2TimerLen      = 20;

        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_1X_OOC_TIMER_SCHEDULE_INFO,
                            sizeof(CNAS_NVIM_OOC_TIMER_SCHEDULE_INFO_STRU),
                            UEPS_PID_XSD,
                            (VOS_UINT8 *)&stNvTimerScheduleInfo);

    stNvTimerScheduleInfo.ucPhaseNum                      = (VOS_UINT8)CNAS_MIN(CNAS_XSD_MAX_OOC_SCHEDULE_PHASE_NUM, stNvTimerScheduleInfo.ucPhaseNum);
    pstOocScheduleInfo->stConfigInfo.ucPhaseNum           = stNvTimerScheduleInfo.ucPhaseNum;
    pstOocScheduleInfo->stConfigInfo.ucMru0SearchTimerLen = stNvTimerScheduleInfo.ucMru0SearchTimerLen;
    /* OOC��ʱ�����ʱ�� */
    pstOocScheduleInfo->stConfigInfo.uc1xOocDoTchPhase1TimerLen        = stNvTimerScheduleInfo.uc1xOocDoTchPhase1TimerLen;
    pstOocScheduleInfo->stConfigInfo.uc1xOocDoTchPhase2TimerLen        = stNvTimerScheduleInfo.uc1xOocDoTchPhase2TimerLen;

    for(i = 0; i < pstOocScheduleInfo->stConfigInfo.ucPhaseNum; i++)
    {
        pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[i].usTimes    = stNvTimerScheduleInfo.astOocTimerInfo[i].usTimes;
        pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[i].usTimerLen = stNvTimerScheduleInfo.astOocTimerInfo[i].usTimerLen;
    }

    CNAS_XSD_LogOocScheduleInfo(&stNvTimerScheduleInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadTestConfigNvim
 ��������  : ��NV�л�ȡTestConfig������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��11��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadTestConfigNvim(VOS_VOID)
{
    CNAS_XSD_TEST_CONFIG_STRU          *pstTestConfig = VOS_NULL_PTR;
    CNAS_NVIM_TEST_CONFIG_STRU          stTestConfig;

    pstTestConfig      = CNAS_XSD_GetTestConfig();

    NAS_MEM_SET_S(&stTestConfig, sizeof(stTestConfig), 0x0, sizeof(stTestConfig));

    if (NV_OK != NV_Read(en_NV_Item_TEST_CONFIG,
                         &stTestConfig, sizeof(stTestConfig)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadTestConfigNvim:Read Nvim Failed");

        pstTestConfig->ucReadNvPrlDirectly    = VOS_FALSE;
        pstTestConfig->ucReadDefaultPrl       = VOS_FALSE;
        pstTestConfig->ucIsMod1xAvailTimerLen = VOS_FALSE;

        return;
    }

    CNAS_MNTN_LogReadNVInfo(en_NV_Item_TEST_CONFIG,
                            sizeof(CNAS_NVIM_TEST_CONFIG_STRU),
                            UEPS_PID_XSD,
                            (VOS_UINT8 *)&stTestConfig);

    pstTestConfig->ucReadNvPrlDirectly    = stTestConfig.ucReadNvPrlDirectly;
    pstTestConfig->ucReadDefaultPrl       = stTestConfig.ucReadDefaultPrl;
    pstTestConfig->ucIsMod1xAvailTimerLen = stTestConfig.ucIsMod1xAvailTimerLen;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadAddAvoidListCfgNvim
 ��������  : ��NV�л�ȡ�������avoidƵ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��4��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadAddAvoidListCfgNvim(VOS_VOID)
{
    CNAS_XSD_ADD_AVOID_LIST_CFG_STRU                       *pstAddAvoidListCfg = VOS_NULL_PTR;
    CNAS_NVIM_1X_ADD_AVOID_LIST_CFG_STRU                    stAddAvoidListCfg;

    pstAddAvoidListCfg      = &(CNAS_XSD_Get1xSysAcqNvimConfig()->stAddAvoidListCfg);

    NAS_MEM_SET_S(&stAddAvoidListCfg, sizeof(stAddAvoidListCfg), 0x0, sizeof(stAddAvoidListCfg));

    if (NV_OK != NV_Read(en_NV_Item_1X_ADD_AVOID_LIST_CFG,
                         &stAddAvoidListCfg, sizeof(stAddAvoidListCfg)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadAddAvoidFreqCfgNvim:Read Nvim Failed");

        pstAddAvoidListCfg->ucIsNegSysAdd = VOS_FALSE;
        return;
    }

    pstAddAvoidListCfg->ucIsNegSysAdd = stAddAvoidListCfg.ucIsNegSysAdd;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadNegSysCtrlCfgNvim
 ��������  : ��NV�л�ȡnegative system���жϲ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��5��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadNegPrefSysCmpCtrlNvim(VOS_VOID)
{
    CNAS_XSD_NEG_PREF_SYS_CMP_CTRL_STRU                   *pstNegPrefSysCmpCtrl = VOS_NULL_PTR;
    CNAS_NVIM_1X_NEG_PREF_SYS_CMP_CTRL_STRU                stNegPrefSysCmpCtrl;

    pstNegPrefSysCmpCtrl      = &(CNAS_XSD_Get1xSysAcqNvimConfig()->stNegPrefSysCmpCtrl);

    NAS_MEM_SET_S(&stNegPrefSysCmpCtrl, sizeof(stNegPrefSysCmpCtrl), 0x0, sizeof(stNegPrefSysCmpCtrl));

    if (NV_OK != NV_Read(en_NV_Item_1X_NEG_PREF_SYS_CMP_CTRL,
                         &stNegPrefSysCmpCtrl, sizeof(stNegPrefSysCmpCtrl)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadNegPrefSysCmpCtrlNvim:Read Nvim Failed");

        pstNegPrefSysCmpCtrl->enNegPrefSysCmpType = CNAS_XSD_NEG_PREF_SYS_CMP_BAND_CHAN_AMBIGUOUS_MATCH;
        return;
    }

    pstNegPrefSysCmpCtrl->enNegPrefSysCmpType = stNegPrefSysCmpCtrl.enNegPrefSysCmpType;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadCallBackCfgNvim
 ��������  : ��NV�л�ȡ������CallBackģʽ������ò��洢
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��2��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadCallBackCfgNvim( VOS_VOID )
{
    CNAS_XSD_CALLBACK_CFG_STRU         *pstCallBackCfg = VOS_NULL_PTR;
    CNAS_NVIM_1X_CALLBACK_CFG_STRU      stNvCallBackCfg;

    pstCallBackCfg                      = CNAS_XSD_GetCallBackCfg();

    NAS_MEM_SET_S(&stNvCallBackCfg, sizeof(stNvCallBackCfg), 0x00, sizeof(CNAS_NVIM_1X_CALLBACK_CFG_STRU));

    if (NV_OK != NV_Read(en_Nv_Item_EMC_CALLBACK_CFG,
                         &stNvCallBackCfg, sizeof(CNAS_NVIM_1X_CALLBACK_CFG_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadCallBackCfgNvim:Read Nvim Failed");

        /* ��ȡʧ�� Ĭ�Ϲر�CallBack */
        pstCallBackCfg->ulCallBackEnableFlg     = VOS_FALSE;
        pstCallBackCfg->ulCallBackModeTimerLen  = 0;

        return;
    }

    pstCallBackCfg->ulCallBackEnableFlg     = stNvCallBackCfg.ulCallBackEnableFlg;
    pstCallBackCfg->ulCallBackModeTimerLen  = stNvCallBackCfg.ulCallBackModeTimerLen * 1000;

    CNAS_XSD_LogCallBackConfig(pstCallBackCfg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadHomeSidNidPriCfgNvim
 ��������  : ��ȡHOME SID/NID���ȼ����õ�NV
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��3��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadHomeSidNidDependOnCfgNvim(VOS_VOID)
{
    CNAS_NVIM_HOME_SID_NID_DEPEND_ON_PRL_CFG_STRU           stHomeSidNidDependOnPrlCfg;

    NAS_MEM_SET_S(&stHomeSidNidDependOnPrlCfg, sizeof(stHomeSidNidDependOnPrlCfg), 0x0, sizeof(stHomeSidNidDependOnPrlCfg));

    if (NV_OK != NV_Read(en_NV_Item_HOME_SID_NID_DEPEND_ON_PRL_CFG,
                         &stHomeSidNidDependOnPrlCfg, sizeof(stHomeSidNidDependOnPrlCfg)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadHomeSidNidDependOnCfgNvim:Read Nvim Failed");
        return;
    }

    CNAS_CCB_SetHomeSidNidDependOnPrlFlg(stHomeSidNidDependOnPrlCfg.ucHomeSidNidDependOnPrlFlg);

    CNAS_XSD_LogHomeSidNidDependOnPrlFlg(stHomeSidNidDependOnPrlCfg.ucHomeSidNidDependOnPrlFlg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadOperLockWhiteSidInfoNvim
 ��������  : ��ȡ��������SID��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��3��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadOperLockSysWhiteListInfoNvim(VOS_VOID)
{
    CNAS_NVIM_OPER_LOCK_SYS_WHITE_LIST_STRU                 stOperLockSysWhiteList;
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstOperLockSysWhiteList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstOperLockSysWhiteList = CNAS_CCB_GetOperLockSysWhiteList();

    NAS_MEM_SET_S(&stOperLockSysWhiteList, sizeof(stOperLockSysWhiteList), 0x0, sizeof(stOperLockSysWhiteList));
    NAS_MEM_SET_S(pstOperLockSysWhiteList, sizeof(CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU), 0x0, sizeof(CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU));

    if (NV_OK != NV_Read(en_NV_Item_OPER_LOCK_SYS_WHITE_LIST_INFO,
                         &stOperLockSysWhiteList, sizeof(stOperLockSysWhiteList)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadOperLockSysWhiteListInfoNvim:Read Nvim Failed");
        return;
    }

    pstOperLockSysWhiteList->ucEnable      = stOperLockSysWhiteList.ucEnable;
    pstOperLockSysWhiteList->usWhiteSysNum = CNAS_MIN(stOperLockSysWhiteList.usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM);

    for (i = 0; i < pstOperLockSysWhiteList->usWhiteSysNum;i++ )
    {
        pstOperLockSysWhiteList->astSysInfo[i].usStartSid = stOperLockSysWhiteList.astSysInfo[i].usStartSid;
        pstOperLockSysWhiteList->astSysInfo[i].usEndSid   = stOperLockSysWhiteList.astSysInfo[i].usEndSid;
        pstOperLockSysWhiteList->astSysInfo[i].ulMcc      = stOperLockSysWhiteList.astSysInfo[i].ulMcc;
    }

    CNAS_XSD_LogOperLockSysWhiteList(pstOperLockSysWhiteList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadCTCCCustomizeFreqNvim
 ��������  : ��ȡ�й������Զ���Ƶ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��3��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadCTCCCustomizeFreqNvim(VOS_VOID)
{
    CNAS_NVIM_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 stCustFreqList;
    CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU                 *pstCustFreqList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstCustFreqList = CNAS_CCB_GetCTCCCustomizeFreqList();

    NAS_MEM_SET_S(&stCustFreqList, sizeof(stCustFreqList), 0x0, sizeof(stCustFreqList));
    NAS_MEM_SET_S(pstCustFreqList, sizeof(CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU), 0x0, sizeof(CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU));

    if (NV_OK != NV_Read(en_NV_Item_CTCC_CUSTOMIZE_FREQ_INFO,
                         &stCustFreqList, sizeof(stCustFreqList)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadCTCCCustomizeFreqNvim:Read Nvim Failed");
        return;
    }

    pstCustFreqList->ucEnableFlg = stCustFreqList.ucEnableFlg;
    pstCustFreqList->usFreqNum   = CNAS_MIN(stCustFreqList.usFreqNum, CNAS_CCB_MAX_FREQ_NUM);

    for (i = 0; i < pstCustFreqList->usFreqNum;i++ )
    {
        pstCustFreqList->astFreqList[i].usChannel   = stCustFreqList.astFreqList[i].usChannel;
    }

    CNAS_XSD_LogCTCCCustomizeFreqList(pstCustFreqList);
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_WriteOperLockWhiteSidInfoNvim
 ��������  : д���������SID��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE:д��ɹ�
             VOS_FALSE:д��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��3��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_WriteOperLockWhiteSidListInfoNvim(
    MSCC_XSD_OPER_LOCK_SYS_WHITE_STRU  *pstOPerLockWhiteSid
)
{
    CNAS_NVIM_OPER_LOCK_SYS_WHITE_LIST_STRU                 stOperLockSysWhiteListNvim;

    NAS_MEM_CPY_S(&stOperLockSysWhiteListNvim, sizeof(stOperLockSysWhiteListNvim), pstOPerLockWhiteSid, sizeof(CNAS_NVIM_OPER_LOCK_SYS_WHITE_LIST_STRU));

    if (NV_OK != NV_Write(en_NV_Item_OPER_LOCK_SYS_WHITE_LIST_INFO,
                         &stOperLockSysWhiteListNvim, sizeof(CNAS_NVIM_OPER_LOCK_SYS_WHITE_LIST_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_WriteOperLockWhiteSidInfoNvim:Write Nvim Failed");

        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadCdmaStandardChannelsNvim
 ��������  : ��NV�ж�ȡcdma��׼Ƶ��

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��14��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadCdmaStandardChannelsNvim(VOS_VOID)
{
    CNAS_NVIM_CDMA_STANDARD_CHANNELS_STRU                  stNvimCdmaStandardChan;
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan = VOS_NULL_PTR;

    pstCdmaStandardChan       = CNAS_CCB_GetCdmaStandardChannels();

    NAS_MEM_SET_S(&stNvimCdmaStandardChan, sizeof(stNvimCdmaStandardChan), 0x0, sizeof(CNAS_NVIM_CDMA_STANDARD_CHANNELS_STRU));

    if (NV_OK != NV_Read(en_NV_Item_CDMA_STANDARD_CHANNLES_INFO,
                         &stNvimCdmaStandardChan,
                         sizeof(CNAS_NVIM_CDMA_STANDARD_CHANNELS_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadCdmaStandardChannelsNvim: Read Nvim Failed");
    }
    else
    {
        pstCdmaStandardChan->usPrimaryA   = stNvimCdmaStandardChan.usPrimaryA;

        pstCdmaStandardChan->usPrimaryB   = stNvimCdmaStandardChan.usPrimaryB;

        pstCdmaStandardChan->usSecondaryA = stNvimCdmaStandardChan.usSecondaryA;

        pstCdmaStandardChan->usSecondaryB = stNvimCdmaStandardChan.usSecondaryB;
    }

    CNAS_XSD_LogCdmaStandardChannels(pstCdmaStandardChan);
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_Read1xSupportBandClassMaskNvim
 ��������  : ��NV�л�ȡ1x֧�ֵ�Band Class
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��8��4��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_Read1xSupportBandClassMaskNvim(VOS_VOID)
 {
    VOS_UINT32                                            *pul1xSupportBandClassMask = VOS_NULL_PTR;
    CNAS_NVIM_1X_SUPPORT_BANDCLASS_MASK_STRU               st1xSupportBandClassMask;

    pul1xSupportBandClassMask = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.unUeSupportedBand.ulBand);

    NAS_MEM_SET_S(&st1xSupportBandClassMask, sizeof(st1xSupportBandClassMask), 0x0, sizeof(st1xSupportBandClassMask));

    if (NV_OK != NV_Read(en_NV_Item_CDMA_SUPPORT_BANDCLASS_MASK,
                         &st1xSupportBandClassMask, sizeof(st1xSupportBandClassMask)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_Read1xSupportBandClassMaskNvim:Read Nvim Failed");

        return;
    }

    *pul1xSupportBandClassMask = st1xSupportBandClassMask.ulSupportBandclassMask;

}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadCdma1XPrefChannelsNvim
 ��������  : ��NV�ж�ȡcdma 1x��ѡƵ��

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��14��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadCdma1XCustomPrefChannelsNvim( VOS_VOID )
{
    CNAS_NVIM_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU             stNvimCdma1XCustomPrefChan;
    CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU             *pstCdma1XCustomPrefChan    = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstCdma1XCustomPrefChan       = CNAS_XSD_GetCdma1XCustomPrefChannels();

    NAS_MEM_SET_S(&stNvimCdma1XCustomPrefChan, sizeof(stNvimCdma1XCustomPrefChan), 0x0, sizeof(CNAS_NVIM_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU));
    NAS_MEM_SET_S(pstCdma1XCustomPrefChan, sizeof(CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU), 0x00, sizeof(CNAS_XSD_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU));

    if (NV_OK != NV_Read(en_NV_Item_CDMA_1X_CUSTOM_PREF_CHANNELS_INFO,
                         &stNvimCdma1XCustomPrefChan,
                         sizeof(CNAS_NVIM_CDMA_1X_CUSTOM_PREF_CHANNELS_STRU)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadCdma1XCustomPrefChannelsNvim: Read Nvim Failed");

        return;
    }

    pstCdma1XCustomPrefChan->ucEnableFlg  = stNvimCdma1XCustomPrefChan.ucEnableFlg;
    pstCdma1XCustomPrefChan->usFreqNum    = stNvimCdma1XCustomPrefChan.usFreqNum;

    for (i = 0; i < stNvimCdma1XCustomPrefChan.usFreqNum; i++)
    {
        pstCdma1XCustomPrefChan->astFreqList[i].usChannel = stNvimCdma1XCustomPrefChan.astFreqList[i].usChannel;
    }

#ifdef DMT
    pstCdma1XCustomPrefChan->ucEnableFlg  = VOS_FALSE;
#endif

    CNAS_XSD_LogCdma1XCustomPrefChannels(pstCdma1XCustomPrefChan);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadNoCardModeCfgNvim
 ��������  : ��NV�ж�ȡ�޿�ģʽ����

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��8��27��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_ReadNoCardModeCfgNvim(VOS_VOID)
{
    CNAS_NVIM_NO_CARD_MODE_CFG_STRU     stNoCardModeCfg;

    NAS_MEM_SET_S(&stNoCardModeCfg, sizeof(stNoCardModeCfg), 0x0, sizeof(stNoCardModeCfg));

    if (NV_OK != NV_Read(en_NV_Item_NO_CARD_MODE_CFG,
                         &stNoCardModeCfg, sizeof(stNoCardModeCfg)))
    {
        CNAS_XSD_SetNoCardModeCfgFlg(VOS_FALSE);

        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadNoCardModeCfgNvim: Read Nvim Failed");

        return;
    }

    CNAS_XSD_SetNoCardModeCfgFlg((VOS_UINT8)stNoCardModeCfg.ulEnableFlag);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_ReadEmcRedialSysAcqCfgNvim
 ��������  : ��ȡ���������ز�����

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
VOS_VOID CNAS_XSD_ReadEmcRedialSysAcqCfgNvim(VOS_VOID)
{
    VOS_UINT32                                              i;
    CNAS_XSD_EMC_REDIAL_SYS_ACQ_CFG_STRU                   *pstEmcRedialSysAcqCfg   = VOS_NULL_PTR;

    pstEmcRedialSysAcqCfg = CNAS_XSD_GetEmcRedialSysAcqCfgInfo();

    if (NV_OK != NV_Read(en_NV_Item_EMC_REDIAL_SYS_ACQ_CFG,
                         pstEmcRedialSysAcqCfg->aucRedialTimes, sizeof(pstEmcRedialSysAcqCfg->aucRedialTimes)))
    {
        pstEmcRedialSysAcqCfg->aucRedialTimes[0] = 4;
        pstEmcRedialSysAcqCfg->aucRedialTimes[1] = 3;

        for (i = 2; i < CNAS_XSD_MAX_MRU_SYS_NUM; i++)
        {
            pstEmcRedialSysAcqCfg->aucRedialTimes[i] = 2;
        }

        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_ReadEmcRedialSysAcqCfgNvim: Read Nvim Failed");

    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_Read1xAvoidScheduleInfoNvim
 ��������  : avoid ������Ϣ

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
VOS_VOID CNAS_XSD_Read1xAvoidScheduleInfoNvim(VOS_VOID)
{
    CNAS_NVIM_1X_AVOID_SCHEDULE_INFO_STRU                  stAvoidScheduleInfo;
    CNAS_XSD_AVOID_SCHEDULE_INFO_STRU                     *pstAvoidScheduleInfo  = VOS_NULL_PTR;
    VOS_UINT32                                             i;
    VOS_UINT32                                             j;

    NAS_MEM_SET_S(&stAvoidScheduleInfo, sizeof(stAvoidScheduleInfo), 0x0, sizeof(stAvoidScheduleInfo));

    pstAvoidScheduleInfo = CNAS_XSD_GetAvoidScheduInfoAddr();

    if (NV_OK != NV_Read(en_NV_Item_1X_AVOID_SCHEDULE_INFO,
                         &stAvoidScheduleInfo, sizeof(stAvoidScheduleInfo)))
    {
        for(i = 0; i < CNAS_XSD_AVOID_REASON_MAX; i++)
        {
            if ((CNAS_XSD_AVOID_REG_REJECTED                   == i)
             || (CNAS_XSD_AVOID_REDIRECTION_FAIL               == i)
             || (CNAS_XSD_AVOID_REDIRECTION_WITH_INVALID_GSRDM == i))
            {
                for(j = 0; j < CNAS_XSD_AVOID_MAX_PHASE_NUM; j++)
                {
                    pstAvoidScheduleInfo->aucAvoidTimerLen[i][j] = 30;
                }
            }
            else
            {
                for(j = 0; j < CNAS_XSD_AVOID_MAX_PHASE_NUM; j++)
                {
                    pstAvoidScheduleInfo->aucAvoidTimerLen[i][j] = 60;
                }
            }
        }

        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_Read1xAvoidScheduleInfoNvim: Read Nvim Failed");

        return;

    }

    for(i = 0; i < CNAS_XSD_AVOID_REASON_MAX; i++)
    {
        for (j = 0; j < CNAS_XSD_AVOID_MAX_PHASE_NUM; j++)
        {
            pstAvoidScheduleInfo->aucAvoidTimerLen[i][j] = stAvoidScheduleInfo.astAvoidPhaseNum[i].aucAvoidTimerLen[j];
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_Read1xPowerOffCampOnCtrlFlgNvim
 ��������  : ��ȡ�ػ�ע����Ʊ��

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��21��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XSD_Read1xPowerOffCampOnCtrlFlgNvim(VOS_VOID)
{
    CNAS_NVIM_1X_POWER_OFF_CAMP_ON_CTRL_STRU                st1xPowerOffCampOnCtrl;

    NAS_MEM_SET_S(&st1xPowerOffCampOnCtrl, sizeof(st1xPowerOffCampOnCtrl), 0, sizeof(st1xPowerOffCampOnCtrl));

    if (NV_OK != NV_Read(en_NV_Item_1X_POWER_OFF_CAMP_ON_CTRL,
                         &st1xPowerOffCampOnCtrl, sizeof(st1xPowerOffCampOnCtrl)))
    {
        CNAS_CCB_SetPowerOffCampOnCtrlFlg(VOS_FALSE);

        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_XSD_Read1xPowerOffCampOnCtrlFlgNvim: Read Nvim Failed");

        return;

    }

    CNAS_CCB_SetPowerOffCampOnCtrlFlg(st1xPowerOffCampOnCtrl.ucPowerOffCampOnCtrlFlg);

    return;
}



/*lint -restore*/


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




