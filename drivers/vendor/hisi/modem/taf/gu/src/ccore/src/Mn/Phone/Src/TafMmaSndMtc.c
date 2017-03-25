/******************************************************************************

                  ��Ȩ���� (C), 2013-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaSndMtc.c
  �� �� ��   : ����
  ��    ��   : h00313353
  ��������   : 2015-11-03
  ����޸�   :
  ��������   : MMAģ�鷢�͵�MTC����Ϣ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015-11-03
    ��    ��   : h00313353
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "TafMmaSndMtc.h"
#include "TafMmaComFunc.h"
#include "TafSdcCtx.h"
#include "MmaAppLocal.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MMA_SND_MTC_C


/*****************************************************************************
   2 ȫ�ֱ�������ͺ�
****************************************************************************/

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndMtcPowerStateInd
 ��������  : TAF MMA ֪ͨMTC���ػ�״̬
 �������  : enStartState --���ػ�״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��12��
    ��    ��   : j00174725
    �޸�����  : V9R1 ���ſ�����Ŀ
*****************************************************************************/
VOS_VOID TAF_MMA_SndMtcPowerStateInd(MTC_MODEM_POWER_STATE_ENUM_UINT8 enPowerState)
{
    VOS_UINT16                          ulLenth;
    MMA_MTC_POWER_STATE_IND_STRU       *pstPowerState = VOS_NULL_PTR;

    ulLenth = sizeof(MMA_MTC_POWER_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstPowerState  = (MMA_MTC_POWER_STATE_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstPowerState)
    {
        MN_ERR_LOG("TAF_MMA_SndMtcPowerStateInd: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstPowerState + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstPowerState->stMsgHeader.ulReceiverPid      = UEPS_PID_MTC;
    pstPowerState->stMsgHeader.ulMsgName          = ID_MMA_MTC_POWER_STATE_IND;
    pstPowerState->enPowerState                   = enPowerState;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstPowerState))
    {
        MN_ERR_LOG("TAF_MMA_SndMtcPowerStateInd: Snd Msg Failed!");
    }

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndMtcRatModeInd
 ��������  : MMAģ��֪ͨMTCģ�鵱ǰϵͳ����ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��19��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
VOS_VOID TAF_MMA_SndMtcRatModeInd(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
)
{
    MMA_MTC_RAT_MODE_IND_STRU          *pstRatMode = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    pstRatMode = (MMA_MTC_RAT_MODE_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(MMA_MTC_RAT_MODE_IND_STRU));
    if( VOS_NULL_PTR == pstRatMode )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcRatModeInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRatMode + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_MTC_RAT_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstRatMode->stMsgHeader.ulReceiverPid   = UEPS_PID_MTC;
    pstRatMode->stMsgHeader.ulMsgName       = ID_MMA_MTC_RAT_MODE_IND;

    switch (enSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
            pstRatMode->enRatMode = MTC_RATMODE_GSM;
            break;
        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranMode)
            {
                pstRatMode->enRatMode = MTC_RATMODE_WCDMA;
            }
            else
            {
                pstRatMode->enRatMode = MTC_RATMODE_TDS;
            }
            break;
        case TAF_SDC_SYS_MODE_LTE:
            pstRatMode->enRatMode = MTC_RATMODE_LTE;
            break;

        default:
            pstRatMode->enRatMode = MTC_RATMODE_BUTT;
            break;
    }

    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstRatMode);
    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcRatModeInd: Send Msg Failed!");
    }

    return;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndMtcRegStatusInd
 ��������  : TAF MMA ֪ͨMTCע��״̬
 �������  : ucIsUsimValidFlag -- ���Ƿ���Ч
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��23��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088:svlte���Կ�������Ч����mtc�����ϱ�pstransfer:0

*****************************************************************************/
VOS_VOID TAF_MMA_SndMtcRegStatusInd(VOS_UINT8 ucIsUsimValidFlag)
{
    VOS_UINT16                          ulLenth;
    MMA_MTC_REG_STATUS_IND_STRU        *pstMsg = VOS_NULL_PTR;

    ulLenth = sizeof(MMA_MTC_REG_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstMsg  = (MMA_MTC_REG_STATUS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_MMA_SndMtcRegStatusInd: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MTC;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MTC_REG_STATUS_IND;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MTC_REG_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ucIsUsimValidFlg             = ucIsUsimValidFlag;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstMsg))
    {
        MN_ERR_LOG("TAF_MMA_SndMtcRegStatusInd: Snd Msg Failed!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndMtcRatCfgInd
 ��������  : MMAģ��֪ͨMTCģ�鵱ǰSysCfg���õĽ���ģʽ
 �������  : TAF_MMA_RAT_ORDER_STRU SysCfg���õĽ�����ʽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID TAF_MMA_SndMtcRatCfgInd(
    TAF_MMA_RAT_ORDER_STRU             *pstNewRatOrder
)
{
    MMA_MTC_RAT_CFG_IND_STRU           *pstRatCfgMsg = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstRatCfgMsg = (MMA_MTC_RAT_CFG_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(MMA_MTC_RAT_CFG_IND_STRU));

    i                                   = 0;

    if (VOS_NULL_PTR == pstRatCfgMsg)
    {
        MN_ERR_LOG("TAF_MMA_SndMtcRatModeInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRatCfgMsg + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_MTC_RAT_CFG_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstRatCfgMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_MTC;
    pstRatCfgMsg->stMsgHeader.ulMsgName       = (VOS_UINT32)ID_MMA_MTC_RAT_CFG_IND;
    pstRatCfgMsg->ucRatOrderNum               = MMA_MIN(pstNewRatOrder->ucRatOrderNum, MTC_MMA_MAX_GUL_RAT_NUM);

    for (i = 0; i < pstRatCfgMsg->ucRatOrderNum; i++)
    {
        pstRatCfgMsg->aenRatOrder[i]    = TAF_MMA_ConvertRatTypeToMtc(pstNewRatOrder->aenRatOrder[i]);
    }

    (VOS_VOID)PS_SEND_MSG(WUEPS_PID_MMA, pstRatCfgMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndMtcImsaStateInd
 ��������  : TAF MMA ֪ͨMTC IMSA�Ŀ��ػ�״̬
 �������  : enPowerState --���ػ�״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : l00198894
    �޸�����   : VOLTE Randk1������Ŀ
*****************************************************************************/
VOS_VOID TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_STATE_ENUM_UINT8 enPowerState)
{
    VOS_UINT16                          ulLenth;
    MMA_MTC_IMSA_STATE_IND_STRU        *pstImsaState = VOS_NULL_PTR;

    ulLenth = sizeof(MMA_MTC_IMSA_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstImsaState  = (MMA_MTC_IMSA_STATE_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstImsaState)
    {
        MN_ERR_LOG("TAF_MMA_SndMtcImsaStateInd: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstImsaState + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstImsaState->stMsgHeader.ulReceiverPid      = UEPS_PID_MTC;
    pstImsaState->stMsgHeader.ulMsgName          = ID_MMA_MTC_IMSA_STATE_IND;
    pstImsaState->enPowerState                   = enPowerState;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstImsaState))
    {
        MN_ERR_LOG("TAF_MMA_SndMtcImsaStateInd: Snd Msg Failed!");
    }

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndMtcCurrCampPlmnInfoInd
 ��������  : MMAģ��֪ͨMTCģ�鵱ǰϵͳ����ģʽ
 �������  : enSysMode   - ϵͳģʽ
             enUtranMode - utranģʽ
             ucForbiddenPlmnFlag - �����Ƿ��ֹ��ʶ
             ucPsAttachAllowFlag - ps�Ƿ�����ע���ʶ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��22��
    ��    ��   : z00161729
    �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
  2.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ

*****************************************************************************/
VOS_VOID TAF_MMA_SndMtcCurrCampPlmnInfoInd(
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU                   *pstPlmnInfo
)
{
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU                   *pstCurrCampPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulResult;

    pstCurrCampPlmnInfo = (MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                              WUEPS_PID_MMA,
                                              sizeof(MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU));

    if( VOS_NULL_PTR == pstCurrCampPlmnInfo )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcCurrCampPlmnInfoInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCurrCampPlmnInfo + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstCurrCampPlmnInfo->stMsgHeader.ulReceiverPid   = UEPS_PID_MTC;
    pstCurrCampPlmnInfo->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstCurrCampPlmnInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCurrCampPlmnInfo->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCurrCampPlmnInfo->stMsgHeader.ulMsgName       = ID_MMA_MTC_CURR_CAMP_PLMN_INFO_IND;
    pstCurrCampPlmnInfo->enRatMode                   = pstPlmnInfo->enRatMode;
    pstCurrCampPlmnInfo->ucIsForbiddenPlmnFlag       = pstPlmnInfo->ucIsForbiddenPlmnFlag;
    pstCurrCampPlmnInfo->ucPsAttachAllowFlag         = pstPlmnInfo->ucPsAttachAllowFlag;
    pstCurrCampPlmnInfo->stPlmnId.ulMcc              = pstPlmnInfo->stPlmnId.ulMcc;
    pstCurrCampPlmnInfo->stPlmnId.ulMnc              = pstPlmnInfo->stPlmnId.ulMnc;
    pstCurrCampPlmnInfo->ucPsSupportFlg              = pstPlmnInfo->ucPsSupportFlg;

    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstCurrCampPlmnInfo);

    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcCurrCampPlmnInfoInd: Send Msg Failed!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndMtcSysInfo
 ��������  : ֪ͨmtcϵͳ��Ϣ�����Ϣ
 �������  : ucIsFobbiddenPlmnFlag      -- ��ǰPLMN�Ƿ�Ϊ��ֹPLMN
             ucPsSupportFlg             -- ��ǰ�����Ƿ�֧��PS��
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��26��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ

*****************************************************************************/
VOS_VOID TAF_MMA_SndMtcSysInfo(
    VOS_UINT8                           ucIsFobbiddenPlmnFlag,
    VOS_UINT8                           ucPsSupportFlg
)
{
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU   stSndMtcPlmnInfo;
    TAF_SDC_PLMN_ID_STRU                  *pstCurrCampPlmnId = VOS_NULL_PTR;

    pstCurrCampPlmnId = TAF_SDC_GetCurrCampPlmnId();

    /* ��MTCģ���ϱ���ǰ����ģʽ */
    TAF_MMA_SndMtcRatModeInd(TAF_SDC_GetSysMode(), NAS_UTRANCTRL_GetCurrUtranMode());

    /* ֪ͨmtc ��ǰפ��������뼼�����Ƿ��ֹ��Ϣ */
    PS_MEM_SET(&stSndMtcPlmnInfo, 0, sizeof(stSndMtcPlmnInfo));
    TAF_MMA_ConvertRatModeToMtc(TAF_SDC_GetSysMode(), NAS_UTRANCTRL_GetCurrUtranMode(),
                                &stSndMtcPlmnInfo.enRatMode);

    stSndMtcPlmnInfo.ucIsForbiddenPlmnFlag  = ucIsFobbiddenPlmnFlag;
    stSndMtcPlmnInfo.ucPsAttachAllowFlag    = TAF_SDC_GetPsAttachAllowFlg();
    stSndMtcPlmnInfo.stPlmnId.ulMcc         = pstCurrCampPlmnId->ulMcc;
    stSndMtcPlmnInfo.stPlmnId.ulMnc         = pstCurrCampPlmnId->ulMnc;
    stSndMtcPlmnInfo.ucPsSupportFlg         = ucPsSupportFlg;
    TAF_MMA_SndMtcCurrCampPlmnInfoInd(&stSndMtcPlmnInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndMtcEplmnInfoInd
 ��������  : ֪ͨmtc eplmn�����Ϣ
 �������  : pstEplmnInfoIndMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��25��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����

*****************************************************************************/
VOS_VOID TAF_MMA_SndMtcEplmnInfoInd(
    MSCC_MMA_EPLMN_INFO_IND_STRU        *pstEplmnInfoIndMsg
)
{
    MMA_MTC_EPLMN_INFO_IND_STRU        *pstMmaSndMtcEplmnInfoInd = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    pstMmaSndMtcEplmnInfoInd = (MMA_MTC_EPLMN_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                              WUEPS_PID_MMA,
                                              sizeof(MMA_MTC_EPLMN_INFO_IND_STRU));

    if( VOS_NULL_PTR == pstMmaSndMtcEplmnInfoInd )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcEplmnInfoInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMmaSndMtcEplmnInfoInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_MTC_EPLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMmaSndMtcEplmnInfoInd->stMsgHeader.ulReceiverPid   = UEPS_PID_MTC;
    pstMmaSndMtcEplmnInfoInd->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMmaSndMtcEplmnInfoInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmaSndMtcEplmnInfoInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmaSndMtcEplmnInfoInd->stMsgHeader.ulMsgName       = ID_MMA_MTC_EPLMN_INFO_IND;

    pstMmaSndMtcEplmnInfoInd->stEplmnInfo.ucEquPlmnNum    = pstEplmnInfoIndMsg->stEplmnInfo.ucEquPlmnNum;
    PS_MEM_CPY(pstMmaSndMtcEplmnInfoInd->stEplmnInfo.astEquPlmnAddr, pstEplmnInfoIndMsg->stEplmnInfo.astEquPlmnAddr,
               sizeof(pstMmaSndMtcEplmnInfoInd->stEplmnInfo.astEquPlmnAddr));

    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstMmaSndMtcEplmnInfoInd);

    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcEplmnInfoInd: Send Msg Failed!");
    }

    return;
}


#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndMtcImsVoiceCapInd
 ��������  : MMA��MTC����IMS VOICE CAP֪ͨ
 �������  : ucAvail---IMS VOICE�Ƿ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : w00316404
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MMA_SndMtcImsVoiceCapInd(
    VOS_UINT8                           ucAvail
)
{
    MMA_MTC_IMS_VOICE_CAP_IND_STRU     *pstMsg      = VOS_NULL_PTR;
    VOS_UINT16                          ulLenth;

    ulLenth = sizeof(MMA_MTC_IMS_VOICE_CAP_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڴ�  */
    pstMsg  = (MMA_MTC_IMS_VOICE_CAP_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMtcImsVoiceCapInd: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    pstMsg->stMsgHeader.ulReceiverPid           = UEPS_PID_MTC;
    pstMsg->stMsgHeader.ulMsgName               = ID_MMA_MTC_IMS_VOICE_CAP_IND;
    pstMsg->enImsVoiceCap                       = (MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8)ucAvail;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstMsg))
    {
        MN_ERR_LOG("TAF_MMA_SndMtcImsVoiceCapInd: Snd Msg Failed!");
    }

    return;
}
#endif



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif



