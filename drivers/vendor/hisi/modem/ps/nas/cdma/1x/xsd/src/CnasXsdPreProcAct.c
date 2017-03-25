/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdPreProcAct.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��07��03��
  ��������   : 1X SDԤ�����¼�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��03��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXsdPreProcAct.h"
#include  "CnasXsdSndXreg.h"
#include  "CnasXsdCtx.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdMntn.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "CnasXsdFsmMainTbl.h"
#include  "CnasXsdSysAcqStrategy.h"
#include  "CnasXsdSndCas.h"
#include  "CnasXsdSndMscc.h"
#include  "cas_1x_trchctrl_proc_nas_pif.h"
#include "CnasXsdProcNvim.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_PRE_PROC_ACT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvSliceReverseProtectTimerExpired_PreProc
 ��������  : �յ�avoid list timer��ʱ����ʱ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvSliceReverseProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCurSlice;
    VOS_UINT32                          ulRunSliceNum;
    VOS_UINT8                           i;
    CNAS_XSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo = VOS_NULL_PTR;

    /* ��ȡ��ǰϵͳ��slice */
    ulCurSlice = CNAS_XSD_GetSystemSlice();

    /* ����avoid�б������е�Ƶ��ĵ���slice */
    for (i = 0; i < CNAS_MIN(CNAS_XSD_GetAvoidFreqListNum(), CNAS_XSD_MAX_AVOID_FREQ_NUM); i++)
    {
        pstAvoidFreqInfo = CNAS_XSD_GetAvoidFreqFromAvoidList(i);

        if (VOS_NULL_PTR == pstAvoidFreqInfo)
        {
            continue;
        }

        if (VOS_FALSE == pstAvoidFreqInfo->ucAvoidFlag)
        {
            continue;
        }

        if (ulCurSlice < pstAvoidFreqInfo->ulStartSlice)
        {
            /* ���Ƿ�ת���� */
            ulRunSliceNum = CNAS_XSD_MAX_SLICE_VALUE - pstAvoidFreqInfo->ulStartSlice + ulCurSlice + 1;
        }
        else
        {
            ulRunSliceNum = ulCurSlice - pstAvoidFreqInfo->ulStartSlice;
        }

        /* ����Ѿ����е�slice��Ŀ���ڵ��ڵ��ڵ�slice��Ŀ����avoidƵ���б����޳���Ƶ�� */
        if (ulRunSliceNum >= pstAvoidFreqInfo->ulExpiredSliceNum)
        {
            CNAS_XSD_DeleteAvoidFlagFromAvoidList(i);
        }
    }

    /*���avoid�б��д��ڽ��ñ�ǣ���ʾ���ڱ����õ�Ƶ�㣬������ʱ�� */
    if (VOS_TRUE == CNAS_XSD_IsExistAvoidFlagInAvoidlist())
    {
        CNAS_XSD_StartTimer(TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER,
                            TI_CNAS_XSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
    }

    CNAS_XSD_LogAvoidFreqList(CNAS_XSD_GetAvoidFreqListAddr());

    return VOS_TRUE;
}

#ifdef DMT
/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXsdTestCfgREQ_PreProc
 ��������  : �յ�����������Ϣ������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdTestCfgREQ_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_TEST_CFG_REQ_STRU     *pstCfgReq = VOS_NULL_PTR;

    pstCfgReq = (CNAS_XSD_XSD_TEST_CFG_REQ_STRU *)pstMsg;

    g_ulCurSlice = pstCfgReq->ulCurSlice;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXsdMofiyPrlAcqRecordReq_PreProc
 ��������  : �յ��޸�PRL�����¼��Ϣ��������Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��17��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdMofiyPrlAcqRecordReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ_STRU            *pstModifyReq   = VOS_NULL_PTR;
    VOS_UINT16                                              i;
    CNAS_PRL_ACQ_RECORD_STRU                               *pstRecordInfo = VOS_NULL_PTR;

    pstModifyReq = (CNAS_XSD_XSD_MODIFY_PRL_ACQ_RECORD_REQ_STRU *)pstMsg;

    for (i = 0; i < pstModifyReq->usRecNum; i++)
    {
        pstRecordInfo = CNAS_PRL_GetSpecifiedPrlAcqRecord(pstModifyReq->astAcqRecord[i].usAcqRecordIndex);

        if ((VOS_NULL_PTR != pstRecordInfo)
         && (VOS_TRUE     == pstRecordInfo->ucAcqValid))
        {
            switch (pstRecordInfo->enAcqType)
            {
                case CNAS_PRL_ACQ_TYPE_CELLULAR_CDMA_CUSTOM_CHANNELS:
                    {
                        if (pstModifyReq->astAcqRecord[i].stAcqRecordInfo.u.stCelluarCustomSys.ucNumOfChans <= pstRecordInfo->u.stCelluarCustomSys.ucNumOfChans)
                        {
                            pstRecordInfo->u.stCelluarCustomSys.ucNumOfChans = \
                                pstModifyReq->astAcqRecord[i].stAcqRecordInfo.u.stCelluarCustomSys.ucNumOfChans;

                            NAS_MEM_CPY_S(&(pstRecordInfo->u.stCelluarCustomSys.ausChan[0]),
                                          sizeof(VOS_UINT16)*pstRecordInfo->u.stCelluarCustomSys.ucNumOfChans,
                                          &(pstModifyReq->astAcqRecord[i].stAcqRecordInfo.u.stCelluarCustomSys.ausChan[0]),
                                          sizeof(VOS_UINT16)*pstRecordInfo->u.stCelluarCustomSys.ucNumOfChans);
                        }
                    }
                    break;

                default:

                    break;

            }
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXsdMofiyPrlSysRecordReq_PreProc
 ��������  : �յ��޸�PRLϵͳ���¼������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��25��
    ��    ��   : y00245242
    �޸�����   : iteration 17����

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdMofiyPrlSysRecordReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ_STRU            *pstModifyReq  = VOS_NULL_PTR;
    VOS_UINT16                                              i;
    CNAS_PRL_EXT_SYS_RECORD_STRU                           *pstRecordInfo = VOS_NULL_PTR;
    VOS_UINT16                                              usPriLvl;

    pstModifyReq = (CNAS_XSD_XSD_MODIFY_PRL_SYS_RECORD_REQ_STRU *)pstMsg;

    for (i = 0; i < pstModifyReq->usRecNum; i++)
    {
        pstRecordInfo = CNAS_PRL_GetSpecifiedPrlSysRecord(pstModifyReq->astSysRecord[i].usSysRecordIndex);

        if (VOS_NULL_PTR != pstRecordInfo)
        {
            NAS_MEM_CPY_S(pstRecordInfo,
                          sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU),
                          &(pstModifyReq->astSysRecord[i].stSysRecordInfo),
                          sizeof(CNAS_PRL_EXT_SYS_RECORD_STRU));
        }
    }

    usPriLvl = 0;
    /* �����Ҫ����ˢ��һ��PRL���е�level���������GEOϵͳ��¼����ʱ���� */
    for (i = 0; i <CNAS_PRL_GetPrlHeaderInfoAddr()->usNumSysRecs; i++)
    {
        CNAS_PRL_GetPrlSysInfoAddr()->pstSysRecord[i].usPriLvl = usPriLvl;

        if (CNAS_PRL_RELATIVE_PRI_MORE == CNAS_PRL_GetPrlSysInfoAddr()->pstSysRecord[i].enPriInd)
        {
            usPriLvl++;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXsdMofiyPrlHeadInfoReq_PreProc
 ��������  : �յ��޸�PRLͷ��Ϣ��������Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdMofiyPrlHeadInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU             *pstModifyReq   = VOS_NULL_PTR;
    CNAS_PRL_HEADER_INFO_STRU                              *pstPrlHeadInfo = VOS_NULL_PTR;

    pstModifyReq = (CNAS_XSD_XSD_MODIFY_PRL_HEAD_INFO_REQ_STRU *)pstMsg;

    pstPrlHeadInfo = CNAS_PRL_GetPrlHeaderInfoAddr();

    pstPrlHeadInfo->ucPreferOnly = pstModifyReq->ucPreferOnly;
    pstPrlHeadInfo->enDefRoamInd = pstModifyReq->enDefRoamInd;

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXsdMofiyOocScanIntervalReq_PreProc
 ��������  : �յ��޸�PRLͷ��Ϣ��������Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��17��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXsdMofiyOocScanIntervalReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL_REQ_STRU         *pstModifyReq        = VOS_NULL_PTR;
    CNAS_XSD_OOC_SCHEDULE_INFO_STRU                        *pstOocScheduleInfo  = VOS_NULL_PTR;

    pstModifyReq        = (CNAS_XSD_XSD_MODIFY_OOC_SCAN_INTERVAL_REQ_STRU *)pstMsg;

    pstOocScheduleInfo  = CNAS_XSD_GetOocScheduleInfo();

    pstOocScheduleInfo->stOocCtxInfo.ucDoTrafficFlag      = pstModifyReq->ucDoTrafficFlag;

    NAS_MEM_CPY_S(&(pstOocScheduleInfo->stConfigInfo),
                  sizeof(pstOocScheduleInfo->stConfigInfo),
                  &(pstModifyReq->stOocCfgInfo),
                  sizeof(CNAS_XSD_OOC_CONFIG_INFO_STRU));

    return VOS_TRUE;
}


#endif

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccMoCallStartNtf_PreProc
 ��������  : �յ�mma�����п�ʼ��Ϣ�Ĵ���ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��24��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccMoCallStartNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_1X_SYSTEM_STRU                *pstOrignalSys      = VOS_NULL_PTR;
    MSCC_XSD_MO_CALL_START_NTF_STRU        *pstCallStartNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8     enCallExistFlg;

    pstCallStartNtfMsg =  (MSCC_XSD_MO_CALL_START_NTF_STRU*)pstMsg;

    enCallExistFlg = CNAS_XSD_TransferMsccCallTypeToXsdFormat(pstCallStartNtfMsg->enCallType);

    /* �쳣���� */
    if (CNAS_XSD_CALL_EXIST_NULL_FLAG == enCallExistFlg)
    {
        return VOS_TRUE;
    }

    if (CNAS_XSD_EMC_VOICE_CALL_EXIST_FLAG == enCallExistFlg)
    {
        /* ����Session���� */
        CNAS_XSD_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_CS_CALL);

        /* ���������� */
        CNAS_XSD_BuildEmcCallRedialScanChanList();

        /* ��¼��ǰMRU LIST�����ڽ��������ز�����*/
        CNAS_XSD_BuildEmcRedialMruList();

        return VOS_TRUE;
    }

    /* �½������ز�����Ƶ���б� */
    if (CNAS_XSD_CALL_EXIST_NULL_FLAG == CNAS_XSD_GetCallExistFlg())
    {
        CNAS_XSD_BuildCallRedialScanChanList(CNAS_XSD_GetCurCampedSysInfo());
    }

    CNAS_XSD_SetCallExistFlg(enCallExistFlg);

    if (VOS_TRUE == CNAS_XSD_GetSystemCampOnFlag())
    {
        /* �����פ��״̬,���浱ǰפ��ϵͳ */
        pstOrignalSys = &(CNAS_XSD_GetXsdCtxAddr()->stSysAcqCtrl.stCurCampedSysInfo.stSystem);

        CNAS_XSD_SaveCallOrignalSys(pstOrignalSys);

        CNAS_XSD_SetCallOrigSysExistFlg(VOS_TRUE);
    }
    else
    {
        /* ��¼��Ǻ��п�ʼʱ��פ��ϵͳ */
        CNAS_XSD_SetCallOrigSysExistFlg(VOS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccMoCallEndNtf_PreProc
 ��������  : �յ�MMA�����н�����Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��20��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccMoCallEndNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_1X_MO_CALL_END_NTF_STRU           *pstCallEndNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8         enCallExistFlg;
    CNAS_XSD_FSM_CTX_STRU                      *pstCurFsm        = VOS_NULL_PTR;

    pstCallEndNtfMsg = (MSCC_XSD_1X_MO_CALL_END_NTF_STRU*)pstMsg;

    enCallExistFlg = CNAS_XSD_TransferMsccCallTypeToXsdFormat(pstCallEndNtfMsg->enCallType);
    pstCurFsm                                   = CNAS_XSD_GetCurFsmAddr();

    if ((CNAS_XSD_NORMAL_VOICE_CALL_EXIST_FLAG == enCallExistFlg)
     || (CNAS_XSD_NORMAL_DATA_CALL_EXIST_FLAG  == enCallExistFlg))
    {
        /* ������б�� */
        CNAS_XSD_ClearCallExistFlg(enCallExistFlg);

        if (CNAS_XSD_CALL_EXIST_NULL_FLAG == CNAS_XSD_GetCallExistFlg())
        {
            /* ��պ����ز�����Ƶ���б� */
            CNAS_XSD_ClearCallRedialScanChanList();
        }

        return VOS_TRUE;
    }

    if (CNAS_XSD_EMC_VOICE_CALL_EXIST_FLAG == enCallExistFlg)
    {
        /* ��ս������ز�����������Ϣ*/
        CNAS_XSD_ClearEmcRedialSysAcqCfgInfo();

        /* ������δ��ͨ�յ�Call End */
        if (VOS_NULL_PTR != CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
        {
            /* �ͷ���Դ���� */
            CNAS_XSD_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_CS_CALL);

            /* ��ս�����������Ƶ��ɨ���б� */
            CNAS_XSD_ClearEmcCallRedialScanChanList();

            return VOS_FALSE;
        }

        /* ��ǰ���ڲ�1״̬����INITIAL̬��˵���ǻ�����Ϣ�Ĵ�������״̬�������� */
        if ((CNAS_XSD_FSM_L1_MAIN       == pstCurFsm->enFsmId)
         && (CNAS_XSD_L1_STA_INITIAL    == pstCurFsm->ulState))
        {
            return VOS_FALSE;
        }

        /* �ͷ���Դ���� */
        CNAS_XSD_SndCasEndSessionNotify(CNAS_CAS_1X_SESSION_TYPE_CS_CALL);

        /* NV���óɲ�֧��CALL BACK */
        if (VOS_FALSE == CNAS_XSD_GetCallBackCfg()->ulCallBackEnableFlg)
        {
            return VOS_TRUE;
        }

        /* ����CallBackģʽ */
        CNAS_XSD_SetEmcState(CNAS_XSD_EMC_STATE_CALLBACK);

        /* �ϱ�����CALLBACKģʽNTF */
        CNAS_XSD_SndMsccEmcCallBackInd(NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENABLE);

        /* ����CALLBACK������ʱ�� */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_EMC_CALLBACK_MODE_PROTECT_TIMER, CNAS_XSD_GetCallBackCfg()->ulCallBackModeTimerLen);

        CNAS_XSD_LogCallBackStatusInd(ID_CNAS_XSD_MNTN_LOG_ENTER_CALLBACK_IND);

        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccMoCallSuccessNtf_PreProc
 ��������  : �յ�MMA�����гɹ�����Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��24��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccMoCallSuccessNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU  *pstCallSuccessNtfMsg = VOS_NULL_PTR;
    CNAS_XSD_CALL_EXIST_FLAG_ENUM_UINT8 enCallExistFlg;

    pstCallSuccessNtfMsg = (MSCC_XSD_MO_CALL_SUCCESS_NTF_STRU*)pstMsg;

    enCallExistFlg = CNAS_XSD_TransferMsccCallTypeToXsdFormat(pstCallSuccessNtfMsg->enCallType);

    /* �쳣���� */
    if (CNAS_XSD_CALL_EXIST_NULL_FLAG == enCallExistFlg)
    {
        return VOS_TRUE;
    }

    if (CNAS_XSD_EMC_VOICE_CALL_EXIST_FLAG == enCallExistFlg)
    {
        /* ��ս������ز�������Ƶ���б� */
        CNAS_XSD_ClearEmcCallRedialScanChanList();

        /* ���潨���ɹ���ϵͳ */
        CNAS_XSD_SaveEmcCallOriginalSys(&(CNAS_XSD_GetCurCampedSysInfo()->stSystem));

        return VOS_TRUE;
    }

    /* ��ͨ���������ݺ�:������б�� */
    CNAS_XSD_ClearCallExistFlg(enCallExistFlg);

    if (CNAS_XSD_CALL_EXIST_NULL_FLAG == CNAS_XSD_GetCallExistFlg())
    {
        /* ��պ����ز�����Ƶ���б� */
        CNAS_XSD_ClearCallRedialScanChanList();

        /* ��ս������ز�����������Ϣ*/
        CNAS_XSD_ClearEmcRedialSysAcqCfgInfo();
    }

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCFreqLockSetNtf_PreProc
 ��������  : �յ�MMA��������Ƶ����Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCFreqLockSetNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CFREQ_LOCK_NTF_STRU       *pstCFreqLockNtf         = VOS_NULL_PTR;
    CNAS_XSD_CFREQ_LOCK_SET_PARA_STRU  *pstCFreqLockSetPara     = VOS_NULL_PTR;
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstXsdCampedSysInfo     = VOS_NULL_PTR;

    pstCFreqLockNtf = (MSCC_XSD_CFREQ_LOCK_NTF_STRU *)pstMsg;

    /* ���͸�CAS */
    if (VOS_TRUE != CNAS_XSD_SndCasCFreqLockNtf(pstCFreqLockNtf))
    {
        return VOS_TRUE;
    }

    pstCFreqLockSetPara                  = CNAS_XSD_GetFreqLockAddr();

    pstCFreqLockSetPara->ucFreqLockMode  = pstCFreqLockNtf->enFreqLockMode;
    pstCFreqLockSetPara->usCdmaBandClass = pstCFreqLockNtf->usCdmaBandClass;
    pstCFreqLockSetPara->usSid           = pstCFreqLockNtf->usSid;
    pstCFreqLockSetPara->usNid           = pstCFreqLockNtf->usNid;
    pstCFreqLockSetPara->usCdmaFreq      = pstCFreqLockNtf->usCdmaFreq;
    pstCFreqLockSetPara->usCdmaPn        = pstCFreqLockNtf->usCdmaPn;

    /* ��ǰsysCfg��֧��1x����ִ������ */
    if (VOS_FALSE == pstCFreqLockNtf->ulIsSupport1x)
    {
        return VOS_TRUE;
    }

    pstXsdCampedSysInfo = CNAS_XSD_GetCurCampedSysInfo();

    if (NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENABLE == pstCFreqLockNtf->enFreqLockMode)
    {
        /* ��ǰפ��ϵͳ�Ĳ����뼴����Ƶ������ͬʱ������������ */
        if ((VOS_TRUE == pstXsdCampedSysInfo->ucCampOnFlag)
         && (pstXsdCampedSysInfo->stSystem.stFreq.usChannel   == pstCFreqLockSetPara->usCdmaFreq)
         && (pstXsdCampedSysInfo->stSystem.stFreq.enBandClass == pstCFreqLockSetPara->usCdmaBandClass))
        {
            if (VOS_TRUE == CNAS_PRL_Is1xSysIdMatched(pstXsdCampedSysInfo->stSystem.usSid, pstXsdCampedSysInfo->stSystem.usNid,
                                                      pstCFreqLockSetPara->usSid, pstCFreqLockSetPara->usNid))
            {
                return VOS_TRUE;
            }
        }

        /* IDLE״̬�´������� */
        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_CFREQ_LOCK, 0, VOS_NULL_PTR);
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCdmaCsqSetReq_PreProc
 ��������  : ����CdmaCsq�����ò�����CAS
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��25��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCdmaCsqSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CDMACSQ_SET_REQ_STRU         *pstCdmaCsqReq = VOS_NULL_PTR;

    pstCdmaCsqReq = (MSCC_XSD_CDMACSQ_SET_REQ_STRU *)pstMsg;

    /* ���͸�CAS */
    if (VOS_TRUE != CNAS_XSD_SndCasCdmaCsqSetReq(pstCdmaCsqReq->stCdmaCsq.ucRssiRptThreshold,
                                                 pstCdmaCsqReq->stCdmaCsq.ucEcIoRptThreshold,
                                                 pstCdmaCsqReq->stCdmaCsq.ucTimeInterval))
    {
        CNAS_XSD_SndCdmaCsqSetCnf(NAS_MSCC_PIF_CDMACSQ_SET_RESULT_FAIL);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasCdmaCsqSetCnf_PreProc
 ��������  : XSD��CAS�յ�CdmaCsq�����ý��
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasCdmaCsqSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SET_SIGNAL_QUALITY_CNF_STRU                *pstCdmaCsqCnf = VOS_NULL_PTR;

    pstCdmaCsqCnf = (CAS_CNAS_1X_SET_SIGNAL_QUALITY_CNF_STRU *)pstMsg;

    if (CAS_CNAS_1X_SIGNAL_QUALITY_CNF_RSLT_SUCCESS == pstCdmaCsqCnf->enRslt)
    {
        CNAS_XSD_SndCdmaCsqSetCnf(NAS_MSCC_PIF_CDMACSQ_SET_RESULT_SUCC);
    }
    else
    {
        CNAS_XSD_SndCdmaCsqSetCnf(NAS_MSCC_PIF_CDMACSQ_SET_RESULT_FAIL);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasCdmaCsqInd_PreProc
 ��������  : CAS�����ϱ�CdmaCsq
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��27��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��16��
    ��    ��   : m00312079
    �޸�����   : DTS2015101505057:���ec/Io���ϱ�����

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasCdmaCsqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SIGNAL_QUALITY_IND_STRU  *pstCdmaCsqInd = VOS_NULL_PTR;

    pstCdmaCsqInd = (CAS_CNAS_1X_SIGNAL_QUALITY_IND_STRU  *)pstMsg;

    CNAS_XSD_SndCdmaCsqInd(pstCdmaCsqInd->sCdmaRssi, pstCdmaCsqInd->sCdmaEcIo);

    return VOS_TRUE;

}
#if 0
/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasNegativeSystemQuery_PreProc
 ��������  : �յ�CAS��ѯϵͳ�Ƿ���negativeϵͳ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasNegativeSystemQueryInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_NEGATIVE_SYSTEM_QUERY_IND_STRU             *pstQueryInd     = VOS_NULL_PTR;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stNegativeFreqList;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stSrcFreqInfo;
    CNAS_PRL_ACQ_REC_FREQ_INFO_STRU                         stDstFreqInfo;
    CNAS_PRL_1X_SYSTEM_ID_STRU                              stSysId;
    VOS_UINT32                                              i;

    pstQueryInd = (CAS_CNAS_1X_NEGATIVE_SYSTEM_QUERY_IND_STRU *)pstMsg;

    NAS_MEM_SET_S(&stNegativeFreqList, 0x0, sizeof(stNegativeFreqList));
    NAS_MEM_SET_S(&stSysId, 0x0, sizeof(stSysId));
    NAS_MEM_SET_S(&stSrcFreqInfo, 0x0, sizeof(stSrcFreqInfo));
    NAS_MEM_SET_S(&stDstFreqInfo, 0x0, sizeof(stDstFreqInfo));

    stSysId.usSid = pstQueryInd->stCurrSysId.usSid;
    stSysId.usNid = pstQueryInd->stCurrSysId.usNid;

    for (i = 0; i < pstQueryInd->ulFreqNum; i++)
    {
        stSrcFreqInfo.astFreqInfo[i].enBandClass = pstQueryInd->astFreqList[i].usBandClass;
        stSrcFreqInfo.astFreqInfo[i].usChannel   = pstQueryInd->astFreqList[i].usChannel;
    }
    stSrcFreqInfo.ulNum = pstQueryInd->ulFreqNum;

    /* ���ﲻ��band����֧�ּ�飬��CAS������ */

    /* filter out negative freqs */
    CNAS_XSD_RemoveNegativeFreqs(&stSysId, &stSrcFreqInfo, &stDstFreqInfo);

    for (i = 0; i < stSrcFreqInfo.ulNum; i++)
    {
        if (VOS_FALSE == CNAS_XSD_IsChannelInChannelList(&stSrcFreqInfo.astFreqInfo[i],
                                                          (VOS_UINT16)stDstFreqInfo.ulNum,
                                                          &(stDstFreqInfo.astFreqInfo[0])))
        {
            stNegativeFreqList.astFreqInfo[stNegativeFreqList.ulNum] = stSrcFreqInfo.astFreqInfo[i];

            (stNegativeFreqList.ulNum)++;
        }
    }

    CNAS_XSD_SndCasNegativeSystemQueryRsp(&pstQueryInd->stCurrSysId, &stNegativeFreqList);

    return VOS_TRUE;
}
#endif
/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCas1xSyncTimeInd_PreProc
 ��������  : �յ�CAS�ϱ�1X��ϵͳʱ��
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��4��
    ��    ��   : L00256032
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCas1xSyncTimeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYNC_TIME_IND_STRU      *pstSyncTimeInd = VOS_NULL_PTR;
    NAS_MSCC_PIF_1X_SYS_TIME_STRU        st1xSysTime;

    pstSyncTimeInd = (CAS_CNAS_1X_SYNC_TIME_IND_STRU *)pstMsg;

    NAS_MEM_CPY_S(st1xSysTime.aucSysTime,
                  sizeof(st1xSysTime.aucSysTime),
                  pstSyncTimeInd->stSysTime.aucSysTime,
                  sizeof(pstSyncTimeInd->stSysTime.aucSysTime));
    st1xSysTime.ucLpSec = pstSyncTimeInd->stSysTime.ucLpSec;
    st1xSysTime.cLtmOff = pstSyncTimeInd->stSysTime.cLtmOff;
    st1xSysTime.ucDaylt = pstSyncTimeInd->stSysTime.ucDaylt;

    CNAS_XSD_SndMscc1xSysTimeInd(&st1xSysTime);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccSysCfgReq_PreProc
 ��������  : ͸��ϵͳ������Ϣ��CAS
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSysCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_SYS_CFG_REQ_STRU          *pstSysReq = VOS_NULL_PTR;

    pstSysReq = (MSCC_XSD_SYS_CFG_REQ_STRU *)pstMsg;

    /* ���͸�CAS */
    CNAS_XSD_SndCasSysCfgReq(pstSysReq);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCas1xSysCfgCnf_PreProc
 ��������  : ͸��ϵͳ������ϢCnf��Mscc
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCas1xSysCfgCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYS_CFG_CNF_STRU       *pstSysCnf = VOS_NULL_PTR;

    pstSysCnf = (CAS_CNAS_1X_SYS_CFG_CNF_STRU *)pstMsg;

    /* ���͸�CAS */
    CNAS_XSD_SndMsccSysCfgCnf(pstSysCnf);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccHandsetInfoQry_PreProc
 ��������  : �յ�MSCC���ֻ���Ϣ��ѯ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccHandsetInfoQry_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_HANDSET_INFO_QRY_STRU     *pstInfoMsg = VOS_NULL_PTR;

    pstInfoMsg = (MSCC_XSD_HANDSET_INFO_QRY_STRU *)pstMsg;

    CNAS_HandsetInfoQry_Proc((VOS_UINT32)pstInfoMsg->ulInfoType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCas1xEnterRelSubStateReasonInd_PreProc
 ��������  : �յ�CAS����release substate��ԭ��ֵָʾ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��13��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCas1xEnterRelSubStateReasonInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_IND_STRU     *pst1xEnterRelSubStateResonInd;

    pst1xEnterRelSubStateResonInd = (CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_IND_STRU *)pstMsg;

    /*  Ref to C.S0005-A_v6.0 2.6.4.4,following release subState should set the returnCause to 0x00(NORMAL_ACCESS)
        1.mobile station enters the Release Substate with a mobile station release indication;
        2.mobile station enters the Release Substate with a service inactive indication;
        3.mobile station enters the Release Substate with a base station release indication;
        4.mobile station enters the Release Substate with a base station extended release indication;
        5.mobile station enters the Release Substate with a base station extended release with mini message indication;
    */

    switch (pst1xEnterRelSubStateResonInd->enReason)
    {
        case CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_MS_RELEASE_INDICATION :
        case CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_SERVICE_INACTIVE_INDICATION :
        case CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_BS_RELEASE_INDICATION :
        case CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_BS_EXTEND_RELEASE_INDICATION :
        case CAS_CNAS_1X_ENTER_RELEASE_SUBSTATE_REASON_BS_EXTEND_RELEASE_WITH_MINI_INDICATION :
             CNAS_CCB_Set1xReturnCause(CNAS_CCB_1X_RETURN_CAUSE_NORMAL_ACCESS);
             break;

        default:
             CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvCas1xEnterRelSubStateReasonInd_PreProc: unknown release substate reason!");
             break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvRrmStatusInd_PreProc
 ��������  : �յ�RRM NO RF״ָ̬ʾ��ʱ�򣬽���RRMģ����¼�ȥע��
 �������  : ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_FALSE : ��������
             VOS_TRUE  : ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvRrmStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��RRM����ȥע����Ϣ */
    CNAS_XSD_DeRegisterRrmResourceNtf(RRM_PS_TASK_TYPE_1X_NETWORK_SEARCH);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccSrvAcqReq_PreProc
 ��������  : �յ�MSCCҵ�񴥷�������Ԥ����
 �������  : ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_FALSE : ��������
             VOS_TRUE  : ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��20��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccSrvAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Srv Acq��ϴ��� */
    CNAS_XSD_SetSrvAcqFlg(VOS_TRUE);

    /* �����Ϣ���ν���Ԥ����ֱ�ӽ���״̬������ */
    if (VOS_NULL_PTR != CNAS_XSD_GetEmcCallRedialScanChanListAddr()->pstScanChanInfo)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == CNAS_XSD_GetSystemCampOnFlag())
    {
        CNAS_XSD_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS);

        CNAS_XSD_SetSrvAcqFlg(VOS_FALSE);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccBeginSessionNotify_PreProc
 ��������  : �յ�MSCC��Դ��������Ĵ���:��CAS������Դ��������
 �������  : ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_FALSE : ��������
             VOS_TRUE  : ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccBeginSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType;

    enSessionType = CNAS_XSD_ConvertSrvTypeToSessionType(((MSCC_XSD_BEGIN_SESSION_NOTIFY_STRU *)pstMsg)->enSrvType);

    /* ��CAS������Դ�������� */
    CNAS_XSD_SndCasBeginSessionNotify(enSessionType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccEndSessionNotify_PreProc
 ��������  : �յ�MSCC��Դ��������Ĵ���:��CAS������Դ�ͷ�����
 �������  : ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_FALSE : ��������
             VOS_TRUE  : ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType;

    enSessionType = CNAS_XSD_ConvertSrvTypeToSessionType(((MSCC_XSD_END_SESSION_NOTIFY_STRU *)pstMsg)->enSrvType);

    /* ��CAS������Դ�ͷ����� */
    CNAS_XSD_SndCasEndSessionNotify(enSessionType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_PreProc
 ��������  : �յ�MSCC�����ز���Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_FALSE : ��������
             VOS_TRUE  : ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCallRedialSystemAcquireNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU           *pstCallRedialSysAcqNtf = VOS_NULL_PTR;

    pstCallRedialSysAcqNtf                                  = (MSCC_XSD_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU *)pstMsg;

    if ((NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_EMC_VOICE_CALL      == pstCallRedialSysAcqNtf->enCallType)
     || (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_VOICE_CALL   == pstCallRedialSysAcqNtf->enCallType))
    {
        return VOS_FALSE;
    }

    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_1X_NORMAL_DATA_CALL     == pstCallRedialSysAcqNtf->enCallType)
    {
        /* CallBack�����в�������ͨ���ݺ����ز� */
        if (CNAS_XSD_EMC_STATE_CALLBACK                     == CNAS_XSD_GetEmcState())
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* ������Ϣ������״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccEndCallBackNtf_PreProc
 ��������  : �յ�MSCC�˳�CallBackģʽָʾ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_FALSE : ��������
             VOS_TRUE  : ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccEndCallBackNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����ǰ������CALLBACKģʽ�����쳣���� */
    if (CNAS_XSD_EMC_STATE_CALLBACK != CNAS_XSD_GetEmcState())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiCallBackModeTimerExpired_PreProc
 ��������  : �յ�CallBack Nv��ʱ������Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_FALSE : ��������
             VOS_TRUE  : ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiCallBackModeTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����ǰ������CALLBACKģʽ�����쳣���� */
    if (CNAS_XSD_EMC_STATE_CALLBACK != CNAS_XSD_GetEmcState())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiCallBackSrchTimerExpired_PreProc
 ��������  : �յ�CallBack 15s������ʱ������Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_FALSE : ��������
             VOS_TRUE  : ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiCallBackSrchTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����ǰ������CALLBACKģʽ�����쳣���� */
    if (CNAS_XSD_EMC_STATE_CALLBACK != CNAS_XSD_GetEmcState())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccCSidListReq_PreProc
 ��������  : �յ�MSCC Sid��������������Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE  : ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvMsccCSidListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_SET_CSIDLIST_REQ_STRU                         *pstOperLockSysWhite     = VOS_NULL_PTR;
    CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU                 *pstOperLockSysWhiteList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstOperLockSysWhite                 = (MSCC_XSD_SET_CSIDLIST_REQ_STRU *)pstMsg;

    /* NVд��ɹ� */
    if (VOS_TRUE == CNAS_XSD_WriteOperLockWhiteSidListInfoNvim((MSCC_XSD_OPER_LOCK_SYS_WHITE_STRU *)(&pstOperLockSysWhite->stSidWhiteList)))
    {
        /* �洢��ȫ�ֱ��� */
        pstOperLockSysWhiteList                = CNAS_CCB_GetOperLockSysWhiteList();
        pstOperLockSysWhiteList->ucEnable      = pstOperLockSysWhite->stSidWhiteList.ucEnable;
        pstOperLockSysWhiteList->usWhiteSysNum = CNAS_MIN(pstOperLockSysWhite->stSidWhiteList.usWhiteSysNum, CNAS_CCB_MAX_WHITE_LOCK_SYS_NUM);

        for (i = 0; i < pstOperLockSysWhiteList->usWhiteSysNum;i++ )
        {
            pstOperLockSysWhiteList->astSysInfo[i].usStartSid = pstOperLockSysWhite->stSidWhiteList.astSysInfo[i].usStartSid;
            pstOperLockSysWhiteList->astSysInfo[i].usEndSid   = pstOperLockSysWhite->stSidWhiteList.astSysInfo[i].usEndSid;
            pstOperLockSysWhiteList->astSysInfo[i].ulMcc      = pstOperLockSysWhite->stSidWhiteList.astSysInfo[i].ulMcc;
        }

        CNAS_XSD_LogOperLockSysWhiteList(pstOperLockSysWhiteList);

        /* �ϱ�MSCC���óɹ� */
        CNAS_XSD_SndMsccSetCSidListCnf(VOS_TRUE);

        return VOS_TRUE;
    }

    /* �ϱ�MSCC����ʧ�� */
    CNAS_XSD_SndMsccSetCSidListCnf(VOS_FALSE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCASStateInd_PreProc
 ��������  : �յ�cas state ind�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE  : ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��11��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasStateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_CAS_STATE_IND_STRU     *pstStateInd;

    pstStateInd = (CAS_CNAS_1X_CAS_STATE_IND_STRU*)pstMsg;

    /* ����tch̬�����avoidƵ����Ϣ*/
    if (CAS_CNAS_1X_CAS_TCH_STATE == pstStateInd->enCasState)
    {
        CNAS_XSD_ClearAccessSuccessFreqFormAvoidList();
    }

    /* UE ״̬���ͽoXREG*/
    CNAS_XSD_SndXregUeStateInd(pstStateInd->enCasState,
                               pstStateInd->enCasSubState);

    /* UE ״̬���ͽoMSCC*/
    CNAS_XSD_SndMsccUeStatusInd(pstStateInd->enCasState,
                                pstStateInd->enCasSubState);
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasAvailableCampQueryReq_PreProc
 ��������  : �յ�CAS��ѯ��ǰϵͳ�ܷ�פ���Ĳ�ѯ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��28��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasAvailableCampQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_AVAILABLE_CAMP_QUERY_REQ_STRU              *pstQueryReq = VOS_NULL_PTR;
    CNAS_PRL_1X_SYSTEM_STRU                                 stCurSysInfo;
    PS_BOOL_ENUM_UINT8                                      enIsCurSysCanCamp;

    pstQueryReq = (CAS_CNAS_1X_AVAILABLE_CAMP_QUERY_REQ_STRU*)pstMsg;

    NAS_MEM_SET_S(&stCurSysInfo, sizeof(stCurSysInfo), 0x00, sizeof(stCurSysInfo));
    stCurSysInfo.stFreq.enBandClass = (CNAS_PRL_BAND_CLASS_ENUM_UINT16)pstQueryReq->usBandClass;
    stCurSysInfo.stFreq.usChannel   = pstQueryReq->usFreq;
    stCurSysInfo.usSid              = pstQueryReq->usSid;
    stCurSysInfo.usNid              = pstQueryReq->usNid;

    /* �ú�������VOS_TRUE����ʾ������פ�� */
    if (VOS_TRUE == CNAS_XSD_IsCurSysNotSuitableSys(&stCurSysInfo, VOS_FALSE, 0))
    {
        /* �ӿڶ���0��ʾ����פ��������ֵ��ʾ����פ�������ڲ��ӿ������෴ */
        enIsCurSysCanCamp = PS_FALSE;
    }
    else
    {
        enIsCurSysCanCamp = PS_TRUE;
    }

    CNAS_XSD_SndCasAvailableCampQueryCnf(pstQueryReq->usOpId, enIsCurSysCanCamp);

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXregRegSuccessInd_PreProc
 ��������  : �յ�RegSuccessInd�Ĵ���, ���avoidƵ����Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE  : ����ɹ�
  1.��    ��   : 2015��12��5��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXregRegSuccessInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAX_XSD_CAMPED_SYS_INFO_STRU      *pstCampedSysInfo = VOS_NULL_PTR;
    CNAS_XSD_AVOID_FREQ_LIST_STRU      *pstAvoidFreqList = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAvoidFreqList    = CNAS_XSD_GetAvoidFreqListAddr();

    ucIndex             = 0;

    pstCampedSysInfo = CNAS_XSD_GetCurCampedSysInfo();

    if (VOS_TRUE == CNAS_XSD_GetAvoidFreqIndexOfAvoidlist(&(pstCampedSysInfo->stSystem.stFreq), &ucIndex))
    {

        CNAS_XSD_ClearAvoidCountFromAvoidList(ucIndex, CNAS_XSD_AVOID_REG_REJECTED);

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

    return VOS_TRUE;
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



