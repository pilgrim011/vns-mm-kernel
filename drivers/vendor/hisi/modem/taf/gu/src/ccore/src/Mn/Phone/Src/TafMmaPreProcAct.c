/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaPreProcAct.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��7��9��
  ����޸�   :
  ��������   :Ԥ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��9��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "NasComm.h"
#include "NasCommDef.h"
#include "TafMmaCtx.h"
#include "TafSdcCtx.h"
#include "MmaAppLocal.h"
#include "Taf_Status.h"
#include "NasUsimmApi.h"
#include "msp_nvim.h"
#include "TafApsProcNvim.h"
#include "TafMmaFsmPhoneModeTbl.h"
#include "TafMmaPreProcAct.h"
#include "TafLog.h"
#include "TafSdcLib.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaSndTaf.h"
#include "TafMmaSndXsms.h"
#include "TafMmaNetworkNameTbl.h"
#include "MmaAppLocal.h"
/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-24, begin */
#if (FEATURE_ON == FEATURE_IMS)
#include "MmaMsccInterface.h"
#endif
/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-24, end */

/* Added by w00167002 for L-C��������Ŀ, 2014-2-14, begin */
#include "TafMmaSndApp.h"
#include "TafMmaProcNvim.h"
#include "TafMmaMntn.h"
#include "TafMmaFsmPhoneMode.h"
/* Added by w00167002 for L-C��������Ŀ, 2014-2-14, end */
#include "MmaUphyInterface.h"
#include "TafMmaFsmPhoneMode.h"

/* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-17, begin */
#include "TafMmaProcUsim.h"
/* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-17, end */

/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
#include "TafMtcApi.h"
#endif
/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */
#include "NasComm.h"
#include "TafMmaProcUsim.h"
#include "TafMmaSndMscc.h"

#include "TafStdlib.h"

#include "TafMmaComFunc.h"
#include "Taf_Status.h"

#include "TafMmaMain.h"
#include "NasMmlCtx.h"

#include "TafMmaComFunc.h"

#include "TafMmaSndStk.h"

#include "hsm_mma_pif.h"
#include "TafMmaSndOm.h"
#include "xcc_mma_pif.h"

#include "TafMmaSndMtc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_PREPROC_ACT_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern MMA_ME_PERSONALISATION_STATUS_STRU       g_stMmaMePersonalisationStatus;
extern VOS_UINT8                                g_ucMmaOmConnectFlg ;
extern MMA_TIMER_ST                             g_stPhPhResetTimer;
extern STATUS_CONTEXT_STRU                      g_StatusContext;
extern VOS_UINT32                               g_ucUsimHotOutFlag;
extern NAS_MMA_NEW_ADD_GLABAL_VARIABLE_FOR_PC_REPLAY_ST g_MmaNewValue;
extern VOS_UINT8                               g_aucMmaImei[TAF_PH_IMEI_LEN-1];
extern TAF_MMA_GLOBAL_VALUE_ST                 gstMmaValue;
extern MMA_TI_TABLE                            gastMmaTiTab[MMA_MAX_TI];
extern MMA_INTERNAL_TIMER_ST                   gstMmaInternalTimer;
extern MMA_TIMER_ST                            g_MmaSimTimer[TAF_SIM_TIMER_NUM];
extern MMA_TIMER_ST                                     g_stNetScanProtectTimer;
extern MMA_TIMER_ST                                     g_stAbortNetScanProtectTimer;


/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#ifdef __PS_WIN32_RECUR__
/*****************************************************************************
 �� �� ��  : NAS_MMA_SndOutsideContextData
 ��������  : �ָ�MMAȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��01��04��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��4��1��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mscc�ӿڵ���
*****************************************************************************/
VOS_UINT32 NAS_MMA_RestoreContextData(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMA_SDT_MSG_ST                      *pRcvMsgCB;
    NAS_MMA_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_MMA_SDT_MSG_ST *)pstMsg;

    if (EVT_NAS_MMA_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY == pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        /* Deleted by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-12, begin */

        /* Deleted by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-12, end */
        g_MmaNewValue.ucSimType = pstOutsideCtx->ucSimType;

        /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-1, begin */
        TAF_SDC_SetSimImsi(pstOutsideCtx->pc_g_aucMmaImsi);
        /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-1, end */

        PS_MEM_CPY(g_aucMmaImei, pstOutsideCtx->pc_g_aucMmaImei, TAF_PH_IMEI_LEN-1);

        /* Deleted by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-12, begin */

        /* Deleted by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-12, end */
        PS_MEM_CPY(&g_StatusContext, &pstOutsideCtx->pc_g_StatusContext, sizeof(STATUS_CONTEXT_STRU));
        PS_MEM_CPY(&gstMmaValue, &pstOutsideCtx->pc_gstMmaValue, sizeof(TAF_MMA_GLOBAL_VALUE_ST));
        gstMmaValue.pg_StatusContext = &g_StatusContext;

        PS_MEM_CPY(&g_stMmaMePersonalisationStatus, &pstOutsideCtx->pc_g_stMmaMePersonalisationStatus, sizeof(MMA_ME_PERSONALISATION_STATUS_STRU));
        PS_MEM_CPY(gastMmaTiTab, pstOutsideCtx->pc_gastMmaTiTab, MMA_MAX_TI*sizeof(MMA_TI_TABLE));

        PS_MEM_CPY(&gstMmaInternalTimer, &pstOutsideCtx->pc_gstMmaInternalTimer, sizeof(MMA_INTERNAL_TIMER_ST));
        /* Deleted by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-11, begin */

        /* Deleted by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-11, end */
        PS_MEM_CPY(g_MmaSimTimer, pstOutsideCtx->pc_g_MmaSimTimer, TAF_SIM_TIMER_NUM*sizeof(MMA_TIMER_ST));

        MMA_INFOLOG("MMA: NAS_MMA_RestoreContextData - data is restored.");
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMA_RestoreFixedContextData
 ��������  : �ָ�MMAȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��05��11��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2009��08��22��
    ��    ��   : ŷ���� 00132663
    �޸�����   : AT2D13878, ��PC�طŹ��̡��ط���Ϣ�ָ�NV������ǰ��ȫ�ֱ����ڿ���ʱ�Ѿ���ȡNV�ֵ�ˣ�
                 �˺��յ�������Ϣ�����������¶�ȡ������MMAȫ�ֱ���δ���¡�
  3.��    ��   : 2011��6��28��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : ���ⵥ��: DTS2011040204531,ɾ��en_NV_Item_Ps_Delay_Flag
  4.��    ��   : 2013��4��1��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mscc�ӿڵ���
  5.��    ��   : 2013��05��17��
    ��    ��   : m00217266
    �޸�����   : nv����
*****************************************************************************/
VOS_UINT32 NAS_MMA_RestoreFixedContextData(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMA_FIXED_CONTEXT_MSG_ST       *pRcvMsgCB;
    NAS_MMA_FIXED_PART_CONTEXT_ST      *pstOutsideCtx;
    VOS_UINT32                          ulVersion;
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;
    MN_MMA_LAST_SETTED_SYSCFG_SET_STRU *pstLastSyscfgSet = VOS_NULL_PTR;

    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU               stQuickStartFlg;

    stQuickStartFlg.ulQuickStartSta = MMA_QUICK_START_DISABLE;

    pstLastSyscfgSet = MN_MMA_GetLastSyscfgSetAddr();

    pRcvMsgCB        = (NAS_MMA_FIXED_CONTEXT_MSG_ST *)pstMsg;

    if (EVT_NAS_MMA_FIXED_PART_CONTEXT == pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stFixedOutsideCtx;

        ulVersion = pstOutsideCtx->ulVersion;
        switch (ulVersion)
        {
            case 1:      /* restore new para here, no break. */
                gstMmaBandCapa = pstOutsideCtx->gstMmaBandCapa;
            case 0:
                /* ȫ�ֱ����ָ� */

                /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-1, begin */
                TAF_SDC_SetSimImsi(pstOutsideCtx->aucMmaImsi);
                /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-1, end */

                g_MmaNewValue.ucSimType = pstOutsideCtx->aucSimType;

                pstLastSyscfgSet->stUserSetBand.uUserSetGuBand.ulPrefBand = pstOutsideCtx->ulPrefBand;
                pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand = pstOutsideCtx->Band;
                gstMmaValue.ulQuickStartFlg = pstOutsideCtx->ulQuickStartFlg;
                /* Deleted by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-12, begin */

                /* Deleted by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-12, end */
                gstMmaValue.stEfustServiceCfg = pstOutsideCtx->stEfustServiceCfg;

                PS_MEM_CPY(g_MmaNewValue.aucImeiBcd, pstOutsideCtx->aucImeiBcd, TAF_PH_IMEI_LEN+1);

                gstMmaValue.stSetMsClass.MsClassType = pstOutsideCtx->MsClassType;
                pstLastSyscfgSet->enRoam = pstOutsideCtx->enRoam;
                gstMmaValue.ucRoamFeatureStatus = pstOutsideCtx->ucRoamFeatureStatus;

                gstMmaValue.stMeInfo = pstOutsideCtx->stMeInfo;

                g_MmaNewValue.stSimLockPlmnInfo = pstOutsideCtx->stSimLockPlmnInfo;
                g_MmaNewValue.stCardLockStatus = pstOutsideCtx->stCardLockStatus;
                g_MmaNewValue.stSimLockMaxTimes = pstOutsideCtx->stSimLockMaxTimes;

                PS_MEM_CPY(g_MmaNewValue.aucPwd, pstOutsideCtx->aucPwd, TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX+1);
                g_MmaNewValue.usSimMePersonalisationActFlag = pstOutsideCtx->usSimMePersonalisationActFlag;
                PS_MEM_CPY(g_MmaNewValue.aucSimPersonalisationStr, pstOutsideCtx->aucSimPersonalisationStr, TAF_MAX_IMSI_LEN+1);


                /* NV��Ļָ� */
                MMA_WriteValue2Nvim(en_NV_Item_User_Set_Freqbands, &pstOutsideCtx->ulPrefBand, sizeof(VOS_UINT32));
                MMA_WriteValue2Nvim(en_NV_Item_Support_Freqbands, &pstOutsideCtx->Band, sizeof(MMA_UE_SUPPORT_FREQ_BAND_STRU));

                stQuickStartFlg.ulQuickStartSta = pstOutsideCtx->ulQuickStartFlg;
                MMA_WriteValue2Nvim(en_NV_Item_FollowOn_OpenSpeed_Flag, &(stQuickStartFlg.ulQuickStartSta), sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU));

                MMA_WriteValue2Nvim(en_NV_Item_RF_Auto_Test_Flag, &pstOutsideCtx->usRfAutoTestFlg, sizeof(VOS_UINT16));
                MMA_WriteValue2Nvim(en_NV_Item_EFust_Service_Cfg, &pstOutsideCtx->stEfustServiceCfg, sizeof(MMA_EFUST_SERVICE_CFG_STRU));

                MMA_WriteValue2Nvim(en_NV_Item_IMEI, pstOutsideCtx->aucImeiBcd, TAF_PH_IMEI_LEN);


                MMA_WriteValue2Nvim(en_NV_Item_MMA_MsClass, &pstOutsideCtx->MsClassType, sizeof(TAF_PH_MS_CLASS_TYPE));
                stRoamFeature.ucRoamFeatureFlg = pstOutsideCtx->ucRoamFeatureStatus;
                stRoamFeature.ucRoamCapability = pstOutsideCtx->enRoam;
                MMA_WriteValue2Nvim(en_NV_Item_Roam_Capa, &stRoamFeature, 2);

                MMA_WriteValue2Nvim(en_NV_Item_FMRID, &pstOutsideCtx->stMeInfo.FmrId, TAF_MAX_MFR_ID_LEN);
                MMA_WriteValue2Nvim(en_NV_Item_ProductName, &pstOutsideCtx->stMeInfo.ProductName, TAF_PH_PRODUCT_NAME_LEN);
                /* MMA_WriteValue2Nvim(en_NV_Item_ModelId, &pstOutsideCtx->stMeInfo.ModelId, TAF_MAX_MODEL_ID_LEN); */

                MMA_WriteValue2Nvim(en_NV_Item_CustomizeSimLockPlmnInfo, &pstOutsideCtx->stSimLockPlmnInfo, sizeof(TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU));
                MMA_WriteValue2Nvim(en_NV_Item_CardlockStatus, &pstOutsideCtx->stCardLockStatus, sizeof(TAF_CUSTOM_CARDLOCK_STATUS_STRU));
                MMA_WriteValue2Nvim(en_NV_Item_CustomizeSimLockMaxTimes, &pstOutsideCtx->stSimLockMaxTimes, sizeof(TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU));

                MMA_WriteValue2Nvim(en_NV_Item_Sim_Personalisation_Pwd, pstOutsideCtx->aucPwd, TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);
                MMA_WriteValue2Nvim(en_NV_Item_Me_Personalisation_Active_Flag, &pstOutsideCtx->usSimMePersonalisationActFlag, 2);
                MMA_WriteValue2Nvim(en_NV_Item_Sim_Personalisation_Imsi_Str, pstOutsideCtx->aucSimPersonalisationStr, pstOutsideCtx->aucSimPersonalisationStr[0]+1);

                break;
            default:
                break;
        }

        MMA_INFOLOG("MMA: NAS_MMA_RestoreFixedContextData - data is restored.");
    }
    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetMiniMode_PreProc
 ��������  : ����miniģʽ
 �������  : usClientId--��ǰ���������client ID
             ucOpId--��ǰ���������OP ID
             ucSetMode-��ǰ���õ�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TURE--�Ѿ���������������
             VOS_FALSE--δ���������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����

*****************************************************************************/
VOS_UINT32 TAF_MMA_SetMiniMode_PreProc(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucSetMode
)
{
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));

    stPhMode.CmdType    = TAF_PH_CMD_SET;
    stPhMode.PhMode     = ucSetMode;

    /* ��ǰ��ΪFULLģʽ,������ֱ�ӻظ��ɹ� */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
#if (FEATURE_ON == FEATURE_LTE)
        (VOS_VOID)NVM_Flush();
#endif
        (VOS_VOID)NV_Flush();

        TAF_SDC_SetCurPhoneMode(ucSetMode);

        /* �ϱ�TAF_PH_EVT_OPER_MODE_CNF�¼� */
        MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetRfOffMode_PreProc
 ��������  : ����rf offģʽ
 �������  : usClientId--��ǰ���������client ID
             ucOpId--��ǰ���������OP ID
             ucSetMode-��ǰ���õ�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TURE--�Ѿ���������������
             VOS_FALSE--δ���������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����
*****************************************************************************/
VOS_UINT32 TAF_MMA_SetRfOffMode_PreProc(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucSetMode
)
{
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));

    stPhMode.CmdType    = TAF_PH_CMD_SET;
    stPhMode.PhMode     = ucSetMode;

    /* ��ǰģʽ��ΪFULLģʽ��ֱ���ϱ��ɹ� */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        TAF_SDC_SetCurPhoneMode(ucSetMode);

        /* �ϱ�TAF_PH_EVT_OPER_MODE_CNF�¼� */
        MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_SetFtMode_PreProc
 ��������  : ����FTģʽ
 �������  : usClientId--��ǰ���������client ID
             ucOpId--��ǰ���������OP ID
             ucSetMode-��ǰ���õ�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TURE--�Ѿ���������������
             VOS_FALSE--δ���������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����
*****************************************************************************/
VOS_UINT32 TAF_MMA_SetFtMode_PreProc(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucSetMode
)
{
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));

    stPhMode.CmdType    = TAF_PH_CMD_SET;
    stPhMode.PhMode     = ucSetMode;

    /* ��ǰģʽ��ΪFULLģʽ��ֱ���ϱ��ɹ� */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        TAF_SDC_SetCurPhoneMode(ucSetMode);

        /* �ϱ�TAF_PH_EVT_OPER_MODE_CNF�¼� */
        MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_SetVdfMiniMode_PreProc
 ��������  : ����vdf miniģʽ
 �������  : usClientId--��ǰ���������client ID
             ucOpId--��ǰ���������OP ID
             ucSetMode-��ǰ���õ�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TURE--�Ѿ���������������
             VOS_FALSE--δ���������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����

*****************************************************************************/
VOS_UINT32 TAF_MMA_SetVdfMiniMode_PreProc(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucSetMode
)
{
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));

    stPhMode.CmdType    = TAF_PH_CMD_SET;
    stPhMode.PhMode     = ucSetMode;

    /* ��ǰģʽ��ΪFULLģʽ��ֱ���ϱ��ɹ� */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        TAF_SDC_SetCurPhoneMode(ucSetMode);

        /* �ϱ�TAF_PH_EVT_OPER_MODE_CNF�¼� */
        MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_SetLowPowerMode_PreProc
 ��������  : ����lower powerģʽ
 �������  : usClientId--��ǰ���������client ID
             ucOpId--��ǰ���������OP ID
             ucSetMode-��ǰ���õ�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TURE--�Ѿ���������������
             VOS_FALSE--δ���������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����
*****************************************************************************/
VOS_UINT32 TAF_MMA_SetLowPowerMode_PreProc(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucSetMode
)
{
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));

    stPhMode.CmdType    = TAF_PH_CMD_SET;
    stPhMode.PhMode     = ucSetMode;

    /* ��ǰģʽ��ΪFULLģʽ��ֱ���ϱ��ɹ� */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        TAF_SDC_SetCurPhoneMode(ucSetMode);

        /* �ϱ�TAF_PH_EVT_OPER_MODE_CNF�¼� */
        MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_SetResetMode_PreProc
 ��������  : ����resetģʽ
 �������  : usClientId--��ǰ���������client ID
             ucOpId--��ǰ���������OP ID
             ucSetMode-��ǰ���õ�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TURE--�Ѿ���������������
             VOS_FALSE--δ���������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����
*****************************************************************************/
VOS_UINT32 TAF_MMA_SetResetMode_PreProc(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucSetMode
)
{
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));

    stPhMode.CmdType    = TAF_PH_CMD_SET;
    stPhMode.PhMode     = ucSetMode;

    /* �ϱ�TAF_PH_EVT_OPER_MODE_CNF�¼� */
    MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_NO_ERROR);

    /* �����ӳٶ�ʱ����AT�ָ�OK����������*/
    g_stPhPhResetTimer.ulTimerId = TI_MN_PH_RESET;

    ulRet = NAS_StartRelTimer( &g_stPhPhResetTimer.MmaHTimer,
                               WUEPS_PID_MMA,
                               TI_MN_PH_RESET_LENGTH,
                               TAF_MMA,
                               TI_MN_PH_RESET,
                               VOS_RELTIMER_NOLOOP );

    if (VOS_OK !=  ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SetRestMode:start TI_MN_PH_RESET failed!");
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_SetFullMode_PreProc
 ��������  : ����fullģʽ
 �������  : usClientId--��ǰ���������client ID
             ucOpId--��ǰ���������OP ID
             ucSetMode-��ǰ���õ�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TURE--�Ѿ���������������
             VOS_FALSE--δ���������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��7��7��
    ��    ��   : z00234330
    �޸�����   : coverity����
*****************************************************************************/
VOS_UINT32 TAF_MMA_SetFullMode_PreProc(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucSetMode
)
{
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));

    /* ��ǰ�Ѿ���������ģʽ��ֱ���ϱ��ɹ� */
    if (ucSetMode == TAF_SDC_GetCurPhoneMode())
    {
        stPhMode.CmdType    = TAF_PH_CMD_SET;
        stPhMode.PhMode     = ucSetMode;

        /* �ϱ�TAF_PH_EVT_OPER_MODE_CNF�¼� */
        MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

#if (VOS_WIN32 == VOS_OS_VER)

    if (VOS_TRUE == g_ucMmaOmConnectFlg)
    {
        NAS_MMA_SndNVData();
    }
#endif

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetPowerOffMode_PreProc
 ��������  : ����power offģʽ
 �������  : usClientId--��ǰ���������client ID
             ucOpId--��ǰ���������OP ID
             ucSetMode-��ǰ���õ�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_TURE--�Ѿ���������������
             VOS_FALSE--δ���������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��9��27��
    ��    ��   : w00167002
    �޸�����   : DTS2013092100149:ɾ��C��TASKDELAY������V9�͹���ʱ���ᵼ��
                  TASKDELAY��δ�����ѣ�����AT��Ϣû�лظ���
  3.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����
*****************************************************************************/
VOS_UINT32 TAF_MMA_SetPowerOffMode_PreProc(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucSetMode
)
{
    TAF_PH_OP_MODE_CNF_STRU                                 stPhMode;
    VOS_UINT16                                              usAppCfgSupportType;
#if (FEATURE_ON == FEATURE_POWER_ON_OFF)
    VOS_UINT32                          ulRslt;
#endif

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));

    usAppCfgSupportType     = TAF_SDC_GetAppCfgSupportType();
    stPhMode.CmdType        = TAF_PH_CMD_SET;
    stPhMode.PhMode         = ucSetMode;

    /* DTS2012051402688: Gģ�����������Ϣ�󲦺�����, ʱ��С��10����, ��������ʱ��Ҫ��������Ϣд��NV */
    TAF_APS_SaveDsFlowInfoToNv();

    if (SYSTEM_APP_WEBUI == usAppCfgSupportType)
    {
#if (FEATURE_ON == FEATURE_POWER_ON_OFF)
        if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
        {
            /* �ϱ�TAF_PH_EVT_OPER_MODE_CNF�¼� */
            MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_NO_ERROR);





            /* ��TASKDELAY�޸�Ϊ������ʱ�����б��� */
            ulRslt = NAS_StartRelTimer(&g_stPowerDownDelayTimer.MmaHTimer,
                                  WUEPS_PID_MMA,
                                  TI_TAF_MMA_DELAY_POWER_DOWN_TIMER_LEN,
                                  TAF_MMA,
                                  TI_TAF_MMA_DELAY_POWER_DOWN,
                                  VOS_RELTIMER_NOLOOP );

            if ( VOS_OK !=  ulRslt)
            {
                MMA_WARNINGLOG("MN_PH_Switch2OffFunc():ERROR:Start TI_TAF_MMA_DELAY_POWER_DOWN Timer Error!");
                mdrv_sysboot_poweroff();
            }



            return VOS_TRUE;
        }

        return VOS_FALSE;
#endif
    }

    if (SYSTEM_APP_ANDROID == usAppCfgSupportType)
    {
        if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
        {
            /* ���ϱ��¼�ǰ�ȵ���COMM�ӿ�Flush NV */
#if (FEATURE_ON == FEATURE_LTE)
            (VOS_VOID)NVM_Flush();
#endif
            (VOS_VOID)NV_Flush();

            /* ����ģʽ��ʹ��AT+CFUN=8Ҳ��Ҫȥ����USIM�� */
            (VOS_VOID)NAS_USIMMAPI_DeactiveCardReq(WUEPS_PID_MMA);

            MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_NO_ERROR);

            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    /* Ŀǰ����WEBUI��ANDROID��������̨�����·�AT+CFUN=8 */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsPhoneModeSetAllowed_PreProc
 ��������  : �Ƿ����������ֻ�ģʽ
 �������  : usClientId       -��ǰ��clientID
             ucPhMode         -��ǰ���õ��ֻ�ģʽ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:�����������ֻ�ģʽ
             VOS_TRUE: ���������ֻ�ģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��19��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��2��14��
   ��    ��   : w00167002
   �޸�����   : L-C��������Ŀ:������������
*****************************************************************************/

/* Modified by w00167002 for L-C��������Ŀ, 2014-2-15, begin */
VOS_UINT32 TAF_MMA_IsPhoneModeSetAllowed_PreProc(
    VOS_UINT16                          usClientId,
    TAF_PH_MODE                         ucPhMode
)
{
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-18, begin */
    TAF_SDC_RAT_PRIO_STRU              *pstRatPrio      = VOS_NULL_PTR;
    VOS_UINT8                           ucCurPhmode;

    /* ģʽ�����Ƿ�����ı� VOS_TRUE :��������, VOS_FALSE:�������� */
    VOS_UINT32                          aulOperModeSetTable[TAF_PH_MODE_NUM_MAX][TAF_PH_MODE_NUM_MAX] =
    {
        /* operate mode: MINI--0,FULL--1,TXOFF--2,RXOFF--3,RFOFF--4,FT--5,RESET--6,LOW--7
                         POWEROFF--8,LOWPOWER--9 */
        /*->0*/     /*->1*/     /*->2*/     /*->3*/     /*->4*/     /*->5*/     /*->6*/     /*->7*/     /* ->8 */   /* ->9 */
/*0->*/ {VOS_TRUE,  VOS_TRUE,   VOS_FALSE,  VOS_FALSE,  VOS_TRUE,   VOS_TRUE,   VOS_FALSE,  VOS_TRUE,   VOS_TRUE,   VOS_TRUE},
/*1->*/ {VOS_TRUE,  VOS_TRUE,   VOS_FALSE,  VOS_FALSE,  VOS_TRUE,   VOS_TRUE,   VOS_FALSE,  VOS_TRUE,   VOS_TRUE,   VOS_TRUE},
/*2->*/ {VOS_FALSE, VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE},
/*3->*/ {VOS_FALSE, VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE},
/*4->*/ {VOS_FALSE, VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_TRUE,   VOS_FALSE,  VOS_TRUE,   VOS_FALSE,  VOS_TRUE,   VOS_FALSE},
/*5->*/ {VOS_TRUE,  VOS_TRUE,   VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_TRUE,   VOS_FALSE,  VOS_TRUE,   VOS_TRUE,   VOS_TRUE},
/*6->*/ {VOS_FALSE, VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE,  VOS_FALSE},
/*7->*/ {VOS_TRUE,  VOS_TRUE,   VOS_FALSE,  VOS_FALSE,  VOS_TRUE,   VOS_TRUE,   VOS_FALSE,  VOS_TRUE,   VOS_TRUE,   VOS_TRUE},
/*8->*/ {VOS_TRUE,  VOS_TRUE,   VOS_FALSE,  VOS_FALSE,  VOS_TRUE,   VOS_TRUE,   VOS_FALSE,  VOS_TRUE,   VOS_TRUE,   VOS_TRUE},
/*9->*/ {VOS_TRUE,  VOS_TRUE,   VOS_FALSE,  VOS_FALSE,  VOS_TRUE,   VOS_TRUE,   VOS_FALSE,  VOS_TRUE,   VOS_TRUE,   VOS_TRUE}
    };

    pstRatPrio                          = TAF_SDC_GetMsPrioRatList();
    ucCurPhmode                         = TAF_SDC_GetCurPhoneMode();

    /* ���в�׼�����ã���ֱ�ӻظ�ʧ�� */
    if (VOS_FALSE                       == aulOperModeSetTable[ucCurPhmode][ucPhMode] )
    {
        return VOS_FALSE;
    }


    /* �쳣����:���CLģʽ���ҵ�ǰ��AT����ģʽ�����ϱ�����ʧ�� */
    if ((VOS_TRUE                       == TAF_SDC_IsConfigCLInterWorkCOutside())
     && (usClientId                     < AT_CLIENT_ID_BUTT))
    {
        return VOS_FALSE;
    }

    /* �쳣����:�������CLģʽ���ҵ�ǰ��CMMCA����ģʽ�����ϱ�CMMCAʧ�� */
    if ((VOS_FALSE                      == TAF_SDC_IsConfigCLInterWorkCOutside())
     && (CMMCA_CLIENT_ID                == usClientId))
    {
        return VOS_FALSE;
    }


    /* ��CMMCA���п���ʱ�������ǰ����L ONLY MODE,��ֱ�ӻظ�CMMCAʧ�� */
    if ( (VOS_TRUE                      != TAF_SDC_IsLteOnlyMode(pstRatPrio))
      && (CMMCA_CLIENT_ID               == usClientId) )
    {
        return VOS_FALSE;
    }

    /* ���Խ���ģʽ���� */
    return VOS_TRUE;

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-18, end */
}
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-15, end */

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcOmPhoneModeSetReq_PreProc
 ��������  : ����ģʽ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��2��21��
    ��    ��   : w00167002
    �޸�����   : ��Ȧ���Ӷȣ�TAF_MMA_ProcPhoneModeSetReq_PreProc��������
  3.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����
*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcOmPhoneModeSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucOldMode;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg       = VOS_NULL_PTR;
    TAF_PH_OP_MODE_STRU                *pstPhModeSet    = VOS_NULL_PTR;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));

    pstRcvMsg       = (MN_APP_REQ_MSG_STRU *)pstMsg;
    pstPhModeSet    = (TAF_PH_OP_MODE_STRU*)pstRcvMsg->aucContent;

    usClientId      = pstRcvMsg->clientId;
    ucOpId          = pstRcvMsg->opId;
    ulRet           = VOS_TRUE;
    ucOldMode       = TAF_SDC_GetCurPhoneMode();

    /* ģʽ����״̬����������ֱ�ӽ�������� */
    if (TAF_MMA_FSM_PHONE_MODE == TAF_MMA_GetCurrFsmId())
    {
        return VOS_FALSE;
    }

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-15, begin */

    /* �жϵ�ǰ�Ƿ��������ģʽ���� */
    if (VOS_FALSE == TAF_MMA_IsPhoneModeSetAllowed_PreProc(usClientId, pstPhModeSet->PhMode))
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-15, end */
    {
        stPhMode.CmdType    = TAF_PH_CMD_SET;
        stPhMode.PhMode     = TAF_SDC_GetCurPhoneMode();

        MMA_PhModeReport(usClientId,  ucOpId, stPhMode, TAF_ERR_ERROR);

        return VOS_TRUE;
    }

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-21, begin */

    /* ���ݲ�ͬ��ģʽ�������ô��� */
    ulRet =TAF_MMA_ProcPhoneModeSet_PreProc(pstPhModeSet->PhMode, usClientId, ucOpId);
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-21, end */

    if (ucOldMode != pstPhModeSet->PhMode)
    {
        /* �뿪FTģʽ��Ҫ����˯�� */
        if (TAF_PH_MODE_FT == ucOldMode)
        {
            TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_FTM);
            if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
            {
                (VOS_VOID)vos_printf("\n*TAF_MMA_ProcOmPhoneModeSetReq_PreProc:PWRCTRL_SLEEP_FTM,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK\n");
            }
        }

        /* ����FTģʽ��Ҫ��ֹ˯�� */
        if (TAF_PH_MODE_FT == pstPhModeSet->PhMode)
        {
            TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_FTM);
            if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
            {
                (VOS_VOID)vos_printf("\n*TAF_MMA_ProcOmPhoneModeSetReq_PreProc:PWRCTRL_SLEEP_FTM,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK\n");
            }
        }
    }

    return ulRet;
}


/* Added by w00167002 for L-C��������Ŀ, 2014-2-15, begin */



/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcPhoneModeSet_PreProc
 ��������  : ����TAFģʽ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��02��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���:TAF_MMA_ProcTafPhoneModeSetReq_PreProc��Ȧ���Ӷ�
  2.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����
*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcPhoneModeSet_PreProc(
    TAF_PH_MODE                         ucCurrPhMode,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));

    ulRet = VOS_TRUE;

    /* ���ݲ�ͬ��ģʽ�������ô��� */
    switch (ucCurrPhMode)
    {
        case TAF_PH_MODE_MINI:

            ulRet = TAF_MMA_SetMiniMode_PreProc(usClientId, ucOpId, ucCurrPhMode);
            break;

        case TAF_PH_MODE_RFOFF:

            ulRet = TAF_MMA_SetRfOffMode_PreProc(usClientId, ucOpId, ucCurrPhMode);
            break;

        case TAF_PH_MODE_FT:

            ulRet = TAF_MMA_SetFtMode_PreProc(usClientId, ucOpId, ucCurrPhMode);
            break;

        case TAF_PH_MODE_VDFMINI:

            ulRet = TAF_MMA_SetVdfMiniMode_PreProc(usClientId, ucOpId, ucCurrPhMode);
            break;

        case TAF_PH_MODE_LOWPOWER:

            ulRet = TAF_MMA_SetLowPowerMode_PreProc(usClientId, ucOpId, ucCurrPhMode);
            break;

        case TAF_PH_MODE_FULL:

            ulRet = TAF_MMA_SetFullMode_PreProc(usClientId, ucOpId, ucCurrPhMode);
            break;

        case TAF_PH_MODE_RESET:

            ulRet = TAF_MMA_SetResetMode_PreProc(usClientId, ucOpId, ucCurrPhMode);
            break;

        case TAF_PH_MODE_POWEROFF:

            ulRet = TAF_MMA_SetPowerOffMode_PreProc(usClientId, ucOpId, ucCurrPhMode);
            break;

        default:

            /* warning ��ӡ */
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcPhoneModeSet_PreProc:invalid mode!");

            stPhMode.CmdType = TAF_PH_CMD_SET;
            stPhMode.PhMode = TAF_SDC_GetCurPhoneMode();
            MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_ERROR);

            break;
    }

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcTafPhoneModeSetReq_PreProc
 ��������  : ����TAFģʽ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��02��15��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���:��������TAF/CMMCA�·��Ŀ��ػ�����
  2.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����
  3.��    ��   : 2015��12��11��
    ��    ��   : w00242748
    �޸�����   : DTS2015103000174:֧�����ض�ȡƽ̨������Ϊ���䶯̬��Cģ
*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcTafPhoneModeSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucOldMode;
    TAF_PH_MODE                         ucCurrPhMode;
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstRcvMsg       = VOS_NULL_PTR;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));

    pstRcvMsg       = (TAF_MMA_PHONE_MODE_SET_REQ_STRU *)pstMsg;

    usClientId      = pstRcvMsg->stCtrl.usClientId;
    ucOpId          = pstRcvMsg->stCtrl.ucOpId;
    ulRet           = VOS_TRUE;
    ucOldMode       = TAF_SDC_GetCurPhoneMode();
    ucCurrPhMode    = pstRcvMsg->stPhoneModePara.PhMode;

    /* ������ȡNV */
    if (TAF_PH_MODE_FULL == pstRcvMsg->stPhoneModePara.PhMode)
    {
        TAF_MMA_ReadLcCtrlNvim();

        TAF_MMA_ReadPlatformRatCap();
        /* ɾ����ӡ����ֹ�ڿ���ʱ���ͷ�CPU����˯�ߣ����������쳣 */
    }

    /* ģʽ����״̬����������ֱ�ӽ�������� */
    if (TAF_MMA_FSM_PHONE_MODE == TAF_MMA_GetCurrFsmId())
    {
        return VOS_FALSE;
    }

    /* �жϵ�ǰ�Ƿ��������ģʽ���� */
    if (VOS_FALSE == TAF_MMA_IsPhoneModeSetAllowed_PreProc(usClientId, ucCurrPhMode))
    {
        stPhMode.CmdType = TAF_PH_CMD_SET;
        stPhMode.PhMode = TAF_SDC_GetCurPhoneMode();
        MMA_PhModeReport(usClientId, ucOpId, stPhMode, TAF_ERR_ERROR);

        return VOS_TRUE;
    }

    /* ��CMMCA���п���ʱ�������ǰ���ֶ�ģʽ�����޸�Ϊ�Զ�����ģʽ */
    if ( (NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO    != TAF_MMA_GetPlmnSelectionMode())
      && (CMMCA_CLIENT_ID               == usClientId) )
    {
        /* CLģʽʱ������ֶ�ģʽ��������Ϊ�Զ�����ģʽ�������쳣��������ֹAPPû�����õ�ǰΪ�Զ�����ģʽ */
        TAF_MMA_WritePlmnSelectionModeNvim(NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO);
        TAF_MMA_SetPlmnSelectionMode(TAF_PH_PLMN_SEL_MODE_AUTO);
    }

    /* ���ݲ�ͬ��ģʽ�������ô��� */
    ulRet = TAF_MMA_ProcPhoneModeSet_PreProc(ucCurrPhMode, usClientId, ucOpId);

    if (ucOldMode != ucCurrPhMode)
    {
        /* �뿪FTģʽ��Ҫ����˯�� */
        if (TAF_PH_MODE_FT == ucOldMode)
        {

            if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
            {
                (VOS_VOID)vos_printf("\n*TAF_MMA_ProcTafPhoneModeSetReq_PreProc:PWRCTRL_SLEEP_FTM,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK\n");
            }

            TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_FTM);
        }

        /* ����FTģʽ��Ҫ��ֹ˯�� */
        if (TAF_PH_MODE_FT == ucCurrPhMode)
        {
            TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_FTM);
            if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
            {
                (VOS_VOID)vos_printf("\n*TAF_MMA_ProcTafPhoneModeSetReq_PreProc:PWRCTRL_SLEEP_FTM,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK\n");
            }
        }
    }

    return ulRet;
}

/* Added by w00167002 for L-C��������Ŀ, 2014-2-15, end */


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvOmPhoneModeSetReq_PreProc
 ��������  : �յ�OM��ģʽ���úͲ�ѯ��Ϣ��Ԥ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvOmPhoneModeSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstRcvMsg       = VOS_NULL_PTR;
    TAF_PH_OP_MODE_STRU                *pstPhModeSet    = VOS_NULL_PTR;
    TAF_PH_OP_MODE_CNF_STRU             stPhModeCnf;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stPhModeCnf, 0x00, sizeof(stPhModeCnf));

    pstRcvMsg       = (MN_APP_REQ_MSG_STRU *)pstMsg;
    pstPhModeSet    = (TAF_PH_OP_MODE_STRU *)pstRcvMsg->aucContent;

    /* �����������ͷַ����� */
    switch (pstPhModeSet->CmdType)
    {
        case TAF_PH_CMD_SET:            /* ������ַ����� */

            ulRet = TAF_MMA_ProcOmPhoneModeSetReq_PreProc(ulEventType, pstMsg);

            break;

        case TAF_PH_CMD_QUERY:          /* ��ѯ��ַ����� */

            /* �ϱ��¼�����������д */
            stPhModeCnf.CmdType = TAF_PH_CMD_QUERY;

            /* �ϱ��¼����ǰģʽ������д */
            stPhModeCnf.PhMode = TAF_SDC_GetCurPhoneMode();

            /* �ϱ�TAF_PH_EVT_OPER_MODE_CNF�¼� */
            MMA_PhModeReport(pstRcvMsg->clientId, pstRcvMsg->opId, stPhModeCnf, TAF_ERR_NO_ERROR);

            ulRet = VOS_TRUE;
            break;

        default:

            /* ������ַ����� */
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvOmPhoneModeSetReq_PreProc:invalid para!");

            stPhModeCnf.CmdType    = pstPhModeSet->CmdType;
            stPhModeCnf.PhMode     = TAF_SDC_GetCurPhoneMode();
            MMA_PhModeReport(pstRcvMsg->clientId, pstRcvMsg->opId, stPhModeCnf, TAF_ERR_PARA_ERROR);
            ulRet = VOS_TRUE;
            break;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvUphyInitStatus_PreProc
 ��������  : �յ�������ϱ���ʼ��״ָ̬ʾ��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��21��
   ��    ��   : y00176023
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��5��23��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvUphyInitStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    UPHY_MMA_INIT_STATUS_IND_STRU      *pstRcvMsg = VOS_NULL;

    /* ��ǰ״̬����ʶ */
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId;

    pstRcvMsg                           = (UPHY_MMA_INIT_STATUS_IND_STRU*)pstMsg;
    enFsmId                             = TAF_MMA_GetCurrFsmId();

    NAS_TRACE_HIGH("UPHY Init Status:%d", (VOS_INT32)(pstRcvMsg->enInitStatus));

    if (VOS_TRUE == TAF_MMA_GetTestRoamFlag())
    {
        return VOS_TRUE;
    }

    /* ��¼������ʼ��״̬ */
    if (MMA_UPHY_INIT_STATUS_BUTT > pstRcvMsg->enInitStatus)
    {
        TAF_MMA_SetPhyInitStatus(pstRcvMsg->enInitStatus);
    }

    /* ����������,�ȴ���ʼ�����״ָ̬ʾ״̬ʱֱ�ӽ�״̬���������Ϣ */
    if ((TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT == TAF_MMA_FSM_GetFsmTopState())
     && (TAF_MMA_FSM_PHONE_MODE                           == enFsmId))

    {
        return VOS_FALSE;
    }

    /* ��ά�ɲ� */
    if (MMA_UPHY_INIT_STATUS_FAIL == pstRcvMsg->enInitStatus)
    {
        NAS_TRACE_HIGH("MMA UPHY INIT FAIL!!!!!!!!");

        /* �ϱ���ǰ���Ƿ���CLģʽ */
        TAF_MMA_SndRatModInd_PhoneMode();

        /* ���״̬����TAF_MMA_FSM_PHONE_MODE���¼ʧ��״̬�����Ϳ���ʧ�ܸ�AT */
        TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_PHY_FAIL);
    }

    return VOS_TRUE;
}

/* Added by w00167002 for L-C��������Ŀ, 2014-2-19, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvQryPhoneModeReq_PreProc
 ��������  : �յ�ģʽ��ѯ��Ϣ��Ԥ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : w00167002
    �޸�����   : �½�����
  2.��    ��   : 2014��07��07��
    ��    ��   : z00234330
    �޸�����   : coverity����
  3.����       :2015�� 03��23��
    ��    ��   : y00322978
    �޸�����   : TAF_MMA_RcvQryPhoneModeReq_PreProc �ع�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvQryPhoneModeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
   TAF_MMA_PHONE_MODE_QRY_REQ_STRU     *pstRcvMsg;
   TAF_MMA_PHONE_MODE_QRY_CNF_STRU     *pstPhoneModeQryCnf;

    pstRcvMsg          = (TAF_MMA_PHONE_MODE_QRY_REQ_STRU *)pstMsg;
    pstPhoneModeQryCnf = (TAF_MMA_PHONE_MODE_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                         sizeof(TAF_MMA_PHONE_MODE_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstPhoneModeQryCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvPhoneModeQry_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstPhoneModeQryCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_PHONE_MODE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstPhoneModeQryCnf->ulReceiverPid          = pstRcvMsg->stCtrl.ulModuleId;
    pstPhoneModeQryCnf->ulMsgName              = ID_TAF_MMA_PHONE_MODE_QRY_CNF;

    PS_MEM_CPY(&pstPhoneModeQryCnf->stCtrl, &pstRcvMsg->stCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstPhoneModeQryCnf->ucPhMode               = TAF_SDC_GetCurPhoneMode();
    pstPhoneModeQryCnf->ucCmdType              = TAF_PH_CMD_QUERY;
    pstPhoneModeQryCnf->enErrorCause           = TAF_ERR_NO_ERROR;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPhoneModeQryCnf);

    return VOS_TRUE;
}

/* Added by w00167002 for L-C��������Ŀ, 2014-2-19, end */


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetUsimImsi
 ��������  : �����ڲ���״ָ̬ʾ��Ϣ��������Ϣ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��02��17��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_GetUsimImsi(
    USIMM_CARD_STATUS_STRU             *pstUsimStatus,
    VOS_UINT8                          *pucImsi
)
{
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    if (USIMM_CARD_SERVIC_AVAILABLE == pstUsimStatus->enCardService)
    {
        ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(pucImsi);
        if (USIMM_API_SUCCESS != ulGetCardImsiRslt)
        {
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvPihUsimStatusInd_PreProc:GetImSiFailed!");

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼��ȡ��IMSI�쳣log */
            TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, pucImsi);
#endif
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsCsimImsimChanged
 ��������  : ��ȡCsim��Imsim�ļ������Ϣ���ж�Imsim�Ƿ����ı�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��6��
    ��    ��   : h00313353
    �޸�����   : 1X ��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsCsimImsimChanged(
    USIMM_CARD_STATUS_STRU             *pstCsimStatus,
    VOS_UINT8                          *pucImsi
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT8                           aucIMSIM[NAS_MAX_IMSIM_DATA_LEN];
    VOS_UINT8                          *pstSdcCsimImsi = VOS_NULL_PTR;

    PS_MEM_SET(aucIMSIM, 0x00, sizeof(aucIMSIM));
    pstSdcCsimImsi                      = TAF_SDC_GetCsimImsi();

    if (USIMM_CARD_SERVIC_AVAILABLE != pstCsimStatus->enCardService)
    {
        return VOS_FALSE;
    }

    /* ���ö�ȡCsimImsim��ͬ���ӿ� */
    if (USIMM_API_SUCCESS != USIMM_GetCdmaIMSIM(aucIMSIM))
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_GetCsimImsim:GetImSim Failed!");

        return VOS_FALSE;
    }

    TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_GetCsimImsim:GetImSim Succ!");

    (VOS_VOID)TAF_SDC_ConvertCImsiBcdCode(aucIMSIM, pucImsi);
    TAF_NORMAL_LOG1(WUEPS_PID_MMA, "Sdc ImsimLen:", pucImsi[0]);
    if ((TAF_SDC_MAX_IMSI_LEN - 1) <= pucImsi[0])
    {
        TAF_NORMAL_LOG4(WUEPS_PID_MMA, "Sdc Imsim:", pucImsi[1], pucImsi[2], pucImsi[3], pucImsi[4]);
        TAF_NORMAL_LOG4(WUEPS_PID_MMA, "Sdc Imsim:", pucImsi[5], pucImsi[6], pucImsi[7], pucImsi[8]);
    }

     /* CSIM IMSI�ı䣬���´洢��SDC�е�ȫ�ֱ��� */
    if (0 != PS_MEM_CMP(pstSdcCsimImsi, pucImsi, TAF_SDC_MAX_IMSI_LEN))
    {
        PS_MEM_CPY(pstSdcCsimImsi, pucImsi, TAF_SDC_MAX_IMSI_LEN);

        TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_GetCsimImsim: Imsim Changed!");

        return VOS_TRUE;
    }

    TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_GetCsimImsim: Imsim Not Changed!");
#endif

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvPihUsimStatusInd_PreProc
 ��������  : �յ�PIHģ���ϱ��Ŀ�״ָ̬ʾ��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��10��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��10��22��
   ��    ��   : z00161729
   �޸�����   : DTS2013101600135:pin�뿪��simlock�������Ƚ�pin�ٽ�simlock mmaû�д������¹ػ�����
 3.��    ��   : 2014��04��28��
   ��    ��   : s00246516
   �޸�����   : ˫IMSI�л�ʱ,MMA���ʲ������ػ��Ϳ�������
 4.��    ��   : 2015��2��15��
   ��    ��   : c00318887
   �޸�����   : AT&T phaseII:���IMSI����Ҵ���CSҵ����������ʱ���ȴ�CSҵ�������ػ�
 5.��    ��   : 2015��5��23��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
 6.��    ��   : 2015��7��6��
   ��    ��   : s00217060
   �޸�����   : DTS2015070606276:syscfg�����жԿ�״̬�仯�Ĵ�������װ����
 7.��    ��   : 2015��12��29��
   ��    ��   : z00359541
   �޸�����   : DTS2015120305849:�յ���״̬��Ϣ��ʼ��EONS���ļ������Ϣ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_CARDSTATUS_IND_STRU          *pstUsimMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulUsimStaChg;
    VOS_UINT32                          ulImsiChg;
    VOS_UINT8                           aucIMSI[NAS_MAX_IMSI_LENGTH];
    /* ��ȡCSIM��IMSIM�ļ� */
    VOS_UINT8                           aucIMSIM[NAS_MAX_IMSI_LENGTH];

    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    TAF_CTRL_STRU                       stCtrl;
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enMtcUsimCardState;
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enMtcCsimCardState;
#endif
    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */
/* Added by w00167002 for L-C��������Ŀ, 2014-2-20, begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32           enCardType;                   /* ������:SIM��USIM��ROM-SIM  */
    TAF_MMA_CARD_STATUS_ENUM_UINT8                enCardStatus;
#endif
    VOS_UINT32                                    ulIsCsimImsiChanged;

    ulIsCsimImsiChanged                           = VOS_FALSE;

    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
    /* ��ʼ�� */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    PS_MEM_SET(&stCtrl, 0x0,sizeof(stCtrl));
    enMtcUsimCardState  = TAF_MTC_USIMM_CARD_SERVIC_ABSENT;
    enMtcCsimCardState  = TAF_MTC_USIMM_CARD_SERVIC_ABSENT;
#endif
    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */
    pstUsimMsg      = (USIMM_CARDSTATUS_IND_STRU *)pstMsg;

    if (VOS_TRUE == TAF_MMA_GetTestRoamFlag())
    {
        return VOS_TRUE;
    }

    /* ��ȡUSIM IMSI��Ϣ */
    PS_MEM_SET(aucIMSI, 0x00, NAS_MAX_IMSI_LENGTH);
    TAF_MMA_GetUsimImsi(&(pstUsimMsg->stUsimSimInfo), aucIMSI);
    PS_MEM_SET(aucIMSIM, 0x00, NAS_MAX_IMSI_LENGTH);
    ulIsCsimImsiChanged = TAF_MMA_IsCsimImsimChanged(&(pstUsimMsg->stCsimUimInfo), aucIMSIM);

    /* ������Ϣ AT_MMA_USIM_STATUS_IND ��AT */
    TAF_MMA_SndATUsimmStatusInd(pstUsimMsg, aucIMSI);

/* Added by w00167002 for L-C��������Ŀ, 2014-2-20, begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    TAF_MMA_ConvertCardType(pstUsimMsg->stUsimSimInfo.enCardType, &enCardType);
    TAF_MMA_ConvertCardStatus(pstUsimMsg->stUsimSimInfo.enCardService, &enCardStatus);
    TAF_MMA_SndSimStatusInd(enCardType, enCardStatus);
#endif
/* Added by w00167002 for L-C��������Ŀ, 2014-2-20, end */

    /* �ֱ𱣴�Usim��Csim������ */
    TAF_SDC_SaveUsimCardType(pstUsimMsg->stUsimSimInfo.enCardType);
    TAF_SDC_SaveCsimCardType(pstUsimMsg->stCsimUimInfo.enCardType);


    NAS_TRACE_HIGH("MMA Rcv PIH Usim Status Ind, USIM CardType: %d,USIM CardService: %d, FSM ID: %d, FSM STATE = %d",
                    pstUsimMsg->stUsimSimInfo.enCardType,
                    pstUsimMsg->stUsimSimInfo.enCardService,
                    TAF_MMA_GetCurrFsmId(),
                    TAF_MMA_FSM_GetFsmTopState());

    /* ���յ�SIM�ϱ��Ŀ�״̬ʱ��֪ͨSMSģ�鵱ǰ�Ŀ�״̬ */
    MN_PH_SndMsgUsimStatus(pstUsimMsg->stUsimSimInfo.enCardService);

    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ��дCTLͷ */
    TAF_API_CTRL_HEADER(&stCtrl, WUEPS_PID_MMA, 0, 0);

    /* ת��MTC��״̬ */
    (VOS_VOID)MMA_MTC_ConvertCardStatus(pstUsimMsg->stUsimSimInfo.enCardService, &enMtcUsimCardState);
    (VOS_VOID)MMA_MTC_ConvertCardStatus(pstUsimMsg->stCsimUimInfo.enCardService, &enMtcCsimCardState);

    /* ������Ϣ��MTCģ�� */
    MTC_SetModemUsimmState(&stCtrl, enMtcUsimCardState, enMtcCsimCardState);
#endif
    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */

    /* �жϿ�״̬��USIM IMSI�Ƿ�ı� */
    ulUsimStaChg    = TAF_MMA_IsCardStatusChanged(pstUsimMsg);
    ulImsiChg       = TAF_MMA_IsImsiChanged(&(pstUsimMsg->stUsimSimInfo), aucIMSI);

    if (VOS_TRUE == ulImsiChg)
    {
        TAF_SDC_SetSimImsi(aucIMSI);
        TAF_SDC_SetLastSimImsi(aucIMSI);
    }



#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* CLģʽ��ˢ��Csim��Ӧ����������״̬ */
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* �ȴ���ȡCsim Imsi�ظ����ٴ���������� */
        if (TAF_SDC_USIM_STATUS_VALID == TAF_SDC_GetCsimStatus())
        {
            if ((VOS_TRUE == ulUsimStaChg)
             || (VOS_TRUE == ulIsCsimImsiChanged))
            {
                g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_IS_UNLOCK;
            }

            /* ���CSIM�Ƿ����� */
            (VOS_VOID)MMA_CheckCsimMePersonalisationStatus();
        }
    }
    else
#endif
    {
        if (USIMM_CARD_SERVIC_AVAILABLE == (pstUsimMsg->stUsimSimInfo.enCardService))
        {
#if (VOS_WIN32 == VOS_OS_VER)
            /* PC���̳�������������룬��״̬�ı����½�����������У�� */
            g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_IS_UNLOCK;
#endif
            /* ͻ��˹�����޸�:��SIM��״̬�����ı�,����IMSI�����ı�ʱ,��Ҫ����У������״̬.
               ��ΪУ�麯��ֻ����MMA_SIM_IS_UNLOCK״̬�Ż�����У��,�������³�ʼ���˱��� */
            if ((VOS_TRUE == ulUsimStaChg)
             || (VOS_TRUE == ulImsiChg))
            {
                g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_IS_UNLOCK;
            }

            /* ����Ƿ����� */
            (VOS_VOID)MMA_CheckMePersonalisationStatus();
        }
    }

    /* �ֱ𱣴�Usim��Csim��״̬ */
    TAF_SDC_SaveUsimCardStatus(pstUsimMsg->stUsimSimInfo.enCardService);
    TAF_SDC_SaveCsimCardStatus(pstUsimMsg->stCsimUimInfo.enCardService);
    /* ���¿���IMSI��SDC�е�IMSI״̬�Լ��������У���,���ϱ���״ָ̬ʾ��AT */
    TAF_MMA_SndAtIccStatusInd_PreProc(ulUsimStaChg);

    /* ��״̬�Լ�IMSI��δ�ı��򷵻� */
    if ((VOS_FALSE == ulUsimStaChg)
     && (VOS_FALSE == ulImsiChg)
     && (VOS_FALSE == ulIsCsimImsiChanged))
    {
        NAS_TRACE_HIGH("*TAF_MMA_RcvPihUsimStatusInd_PrePro:UsimStaChg = VOS_FALSE, ulImsiChg = VOS_FALSE\n");

        return VOS_TRUE;
    }

    /* ��ʼ��EONS���ļ����ȫ�ֱ��� */
    NAS_TRACE_HIGH("*TAF_MMA_RcvPihUsimStatusInd_PrePro: Initialize EONS related SIM File Info\n");
    TAF_SDC_InitEonsRelatedSimFileInfo();

    /* ����п����Ͷ��ļ����� */
    TAF_MMA_ReadUsimInfo_PreProc();

    /* �������������������ӣ���ͬ״̬�������ִ�����switch��֧��� */
    /* ����״̬��ID����switch��֧�Ĵ��� */
    return TAF_MMA_ProcUsimStatusIndByCurFsmId(ulUsimStaChg, ulImsiChg);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaInterUsimStatusChangeInd_PreProc
 ��������  : �յ�MMA���ڲ���״ָ̬ʾ��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��10��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaInterUsimStatusChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           aucImsi[TAF_SDC_MAX_IMSI_LEN];
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT8                           aucIMSIM[NAS_MAX_IMSIM_DATA_LEN];
    VOS_UINT8                          *pucOldImsi  = VOS_NULL_PTR;

    PS_MEM_SET(aucIMSIM, 0x00, sizeof(aucIMSIM));
    pucOldImsi  = TAF_SDC_GetCsimImsi();
#endif

    if (TAF_SDC_USIM_STATUS_VALID == TAF_SDC_GetUsimStatus())
    {
        if (USIMM_API_SUCCESS == USIMM_GetCardIMSI(aucImsi))
        {
            TAF_SDC_SetSimImsi(aucImsi);
            TAF_SDC_SetLastSimImsi(aucImsi);
        }
    }

    /* ��Imsim�����ı� �洢Csim Imsi */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_SDC_USIM_STATUS_VALID == TAF_SDC_GetCsimStatus())
    {
        PS_MEM_SET(aucImsi, 0x00, sizeof(aucImsi));

        if (USIMM_API_SUCCESS == USIMM_GetCdmaIMSIM(aucIMSIM))
        {
            (VOS_VOID)TAF_SDC_ConvertCImsiBcdCode(aucIMSIM, aucImsi);

            if (0 != PS_MEM_CMP(pucOldImsi, aucImsi, TAF_SDC_MAX_IMSI_LEN))
            {
                PS_MEM_CPY(pucOldImsi, aucImsi, TAF_SDC_MAX_IMSI_LEN);
            }
        }
    }
#endif

    /* �����ǰΪNULL״̬����Ҫ���� */
    if (STA_FSM_NULL == g_StatusContext.ulFsmState)
    {
        return VOS_TRUE;
    }

    /* ����phone mode״̬�� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaSimLockStatusChangeInd_PreProc
 ��������  : �յ�MMA������������״ָ̬ʾ��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��4��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaSimLockStatusChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ǰ��available״̬��������Ϣ */
    if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetSimStatus())
    {
        return VOS_TRUE;
    }

    /* �ϱ�һ�ο�״̬ */
    TAF_MMA_SndAtIccStatusInd_PreProc(VOS_TRUE);

    /* ����������,�����ڲ���״̬�ı�ָʾ��Ϣ���� */
    if (TAF_MMA_FSM_MAIN != TAF_MMA_GetCurrFsmId())
    {
        TAF_MMA_SndInterUsimChangeInd();

        return VOS_TRUE;
    }

    /* �����ǰΪNULL״̬����Ҫ���� */
    if (STA_FSM_NULL == g_StatusContext.ulFsmState)
    {
        return VOS_TRUE;
    }

    /* ����phone mode״̬�� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaQrySyscfgReq_PreProc
 ��������  : �յ�AT��SYSCFG��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��10��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2014��2��13��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:����SYSCFG�����ò�ѯ�ӿ�

  3.��    ��   : 2015��3��26��
    ��    ��   : y00322978
    �޸�����   : �ӿں����ع�����������MMA�� syscfg qry��Ϣ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaQrySyscfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SYSCFG_QRY_REQ_STRU        *pstRcvMsg = VOS_NULL_PTR;
    TAF_MMA_SYSCFG_QRY_CNF_STRU        *pstSyscfgQryCnf;
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;
    VOS_UINT32                          ulLength;

    NAS_MMA_NVIM_ACCESS_MODE_STRU       stAccessMode;
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    TAF_PH_MS_CLASS_TYPE                ucMsClassResult;

    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *pstLastSyscfgSet = VOS_NULL_PTR;

    pstRcvMsg   = (TAF_MMA_SYSCFG_QRY_REQ_STRU *)pstMsg;

    ulLength        = 0;

    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();

    pstSyscfgQryCnf = (TAF_MMA_SYSCFG_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                           WUEPS_PID_MMA,
                                           sizeof(TAF_MMA_SYSCFG_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstSyscfgQryCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvMmaSyscfgQry_PreProc:ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }


    /* ��ʼ���¼��ϱ� */
    PS_MEM_SET( (VOS_INT8 *)pstSyscfgQryCnf + VOS_MSG_HEAD_LENGTH, 0X00,
            (VOS_SIZE_T)(sizeof(TAF_MMA_SYSCFG_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ��ȡ��ǰ�Ľ���ģʽ���ȼ�������ػ�����NV:en_NV_Item_RAT_PRIO_LIST�ж�ȡ */
    if (STA_FSM_NULL == g_StatusContext.ulFsmState)
    {
        TAF_MMA_ReadNvimRatPrioList(&(pstLastSyscfgSet->stRatPrioList));
        PS_MEM_CPY(&(gstMmaValue.pg_StatusContext->stRatPrioList),
                   &(pstLastSyscfgSet->stRatPrioList), sizeof(TAF_MMA_RAT_ORDER_STRU));

        (VOS_VOID)NV_GetLength(en_NV_Item_MMA_AccessMode, &ulLength);

        if (NV_OK != NV_Read(en_NV_Item_MMA_AccessMode ,
                 &stAccessMode,
                 ulLength))

        {
            (stAccessMode.aucAccessMode)[1] = TAF_PLMN_PRIO_AUTO;
        }
        pstLastSyscfgSet->enPrioRat = (stAccessMode.aucAccessMode)[1] ;
    }

    pstSyscfgQryCnf->stSysCfg.stRatOrder = pstLastSyscfgSet->stRatPrioList;

    /* ��ȡ��ǰ�û����õ�GUƵ����Ϣ */
    pstSyscfgQryCnf->stSysCfg.stGuBand = pstLastSyscfgSet->stUserSetBand.stOrigUserSetGuBand;

    /* ��ȡ��ǰ�û����õ�������Ϣ */
    pstSyscfgQryCnf->stSysCfg.enRoam = pstLastSyscfgSet->enRoam;

    /* ��ȡ��ǰ�û����õĽ������ȼ� */
    pstSyscfgQryCnf->stSysCfg.enUserPrio = pstLastSyscfgSet->enPrioRat;

    if (STA_FSM_NULL == g_StatusContext.ulFsmState)
    {

        PS_MEM_SET(&stRoamFeature, 0x00, sizeof(stRoamFeature));

        (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Capa, &ulLength);
        if (NV_OK == NV_Read(en_NV_Item_Roam_Capa,
                             &stRoamFeature,
                             ulLength))
        {
            pstSyscfgQryCnf->stSysCfg.enRoam = stRoamFeature.ucRoamCapability;
            MMA_INFOLOG1("TAF_MMA_RcvMmaSyscfgQry_PreProc: usRoamCapa", stRoamFeature.ucRoamCapability);
        }
        else
        {
            MMA_WARNINGLOG("TAF_MMA_RcvMmaSyscfgQry_PreProc:WARNING:Read from NVIM en_NV_Item_Roam_Capa Fail");
            pstSyscfgQryCnf->stSysCfg.enRoam = TAF_MMA_ROAM_NATIONAL_ON_INTERNATIONAL_OFF;
        }
    }

    /* ��ȡ��ǰ�û����õķ�������Ϣ */
    pstSyscfgQryCnf->stSysCfg.enSrvDomain = pstLastSyscfgSet->enSrvDomain;

    if (STA_FSM_NULL == g_StatusContext.ulFsmState)
    {

        PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));


        /* ��ȷ�ڹػ�״̬��ȡ��������Ϣ */
        (VOS_VOID)NV_GetLength(en_NV_Item_MMA_MsClass, &ulLength);
        if (NV_OK != NV_Read(en_NV_Item_MMA_MsClass ,
                             &stMsClass,
                             ulLength))
        {
            MMA_WARNINGLOG("MMA_PhSysCfgQuery():WARNING:Read from NVIM MSClass Fail");
            ucMsClassResult = TAF_PH_MS_CLASS_A;
        }
        else
        {
            ucMsClassResult = stMsClass.ucMsClass;
        }

        MMA_ChangeClass2Srv(&pstSyscfgQryCnf->stSysCfg.enSrvDomain, ucMsClassResult);
    }

    /* ��ȡ��ǰ��Ʒ֧�ֵ��û����õ�LTEƵ����Ϣ */
#if (FEATURE_ON == FEATURE_LTE)
    MN_MMA_GetSupportedUserLteBand(&pstSyscfgQryCnf->stSysCfg.stLBand);
#endif

    /* ����ʧ�ܻ��ѯ�¼��ϱ����ÿͻ��� */
    PS_MEM_CPY(&pstSyscfgQryCnf->stCtrl, &pstRcvMsg->stCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSyscfgQryCnf->ulReceiverPid            = WUEPS_PID_AT;
    pstSyscfgQryCnf->ulMsgName                = ID_TAF_MMA_SYSCFG_QRY_CNF;
    pstSyscfgQryCnf->enErrorCause             = TAF_ERR_NO_ERROR;

    PS_SEND_MSG(WUEPS_PID_MMA, pstSyscfgQryCnf);


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAtEonsUcs2Req_PreProc
 ��������  : �յ�AT^EONSUCS2Ԥ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��12��
    ��    ��   : c00318887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAtEonsUcs2Req_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_EONS_UCS2_REQ_STRU         *pstRcvMsg = VOS_NULL_PTR;
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU    stEonsUcs2PlmnName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucCtxIndex;

    pstRcvMsg = (TAF_MMA_EONS_UCS2_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stEonsUcs2PlmnName, 0x00, sizeof(TAF_MMA_EONS_UCS2_PLMN_NAME_STRU));

    usClientId      = pstRcvMsg->stCtrl.usClientId;
    ucOpId          = pstRcvMsg->stCtrl.ucOpId;

    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_EONS_UCS2_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_EONS_UCS2_REQ))
    {
        TAF_MMA_SndEonsUcs2Rsp(&(pstRcvMsg->stCtrl),
                                TAF_MMA_APP_OPER_RESULT_FAILURE,
                                TAF_ERR_ERROR,
                                &stEonsUcs2PlmnName);

        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndEonsUcs2Rsp(&(pstRcvMsg->stCtrl),
                                TAF_MMA_APP_OPER_RESULT_FAILURE,
                                TAF_ERR_ERROR,
                                &stEonsUcs2PlmnName);

        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstRcvMsg->stCtrl,
                       TAF_MMA_OPER_EONS_UCS2_REQ, ucCtxIndex);



    TAF_MMA_QryEonsUcs2(usClientId,ucOpId);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAtParaReadReq_PreProc
 ��������  : �յ�AT�Ĳ�����ѯ�����Ԥ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��13��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAtParaReadReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstRcvMsg = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    TAF_PARA_TYPE                       ucParaType;

    pstRcvMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    ucParaType  = pstRcvMsg->aucContent[0];
    usClientId  = pstRcvMsg->clientId;
    ucOpId      = pstRcvMsg->opId;

    /* MMA������ѯ���� */
    if ((ucParaType >= TAF_PH_MS_CLASS_PARA )
     && (ucParaType <= (TAF_PH_PRODUCT_NAME_PARA + 1)))
    {
        MMA_QueryProc(usClientId, ucOpId, &ucParaType);

        return VOS_TRUE;
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsNetworkCapInfoChanged
 ��������  : �ж�SDC�еĴ洢������������Ϣ�Ƿ����ı�
 �������  : pstNewNwCapInfo---�յ���������ָʾ��Ϣ���º�SDC�е�����������Ϣ

 �������  : ��
 �� �� ֵ  : VOS_TRUE, ����������Ϣ�����ı�
             VOS_FALSE,����������Ϣ�������ı�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��10��10��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNetworkCapInfoChanged(
    TAF_SDC_NETWORK_CAP_INFO_STRU       *pstNewNwCapInfo
)
{
    TAF_SDC_NETWORK_CAP_INFO_STRU       *pstOldNwCapInfo = VOS_NULL_PTR;

    /* �Ȼ�ȡLTE������������Ϣ */
    pstOldNwCapInfo = TAF_SDC_GetLteNwCapInfo();

    /* �¾������Ƿ��б仯 */
    if ((pstOldNwCapInfo->enLteCsCap   != pstNewNwCapInfo->enLteCsCap)
     || (pstOldNwCapInfo->enNwEmcBsCap != pstNewNwCapInfo->enNwEmcBsCap)
     || (pstOldNwCapInfo->enNwImsVoCap != pstNewNwCapInfo->enNwImsVoCap))
    {
        return VOS_TRUE;
    }

    /* �ٻ�ȡGU������������Ϣ */
    pstOldNwCapInfo = TAF_SDC_GetGuNwCapInfo();

    /* �¾������Ƿ��б仯 */
    if ((pstOldNwCapInfo->enLteCsCap   != pstNewNwCapInfo->enLteCsCap)
     || (pstOldNwCapInfo->enNwEmcBsCap != pstNewNwCapInfo->enNwEmcBsCap)
     || (pstOldNwCapInfo->enNwImsVoCap != pstNewNwCapInfo->enNwImsVoCap))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccNetworkCapabilityInfoInd_PreProc
 ��������  : ��������MSCC��LTE ���������������ϱ���������Ϣ����ת����IMSA
 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��13��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��09��18��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseII��Ŀ�����������ı�ʱ֪ͨSPM
 3.��    ��   : 2013��10��10��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseII��Ŀ�����������ı�ʱ֪ͨIMSA
 4.��    ��   : 2015��01��28��
   ��    ��   : y00245242
   �޸�����   : iteration 9����������IMSA�ӿڵ�MSCCģ��
 5.��    ��   : 2015��2��16��
   ��    ��   : s00217060
   �޸�����   : VOLTE SWITCH
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccNetworkCapabilityInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU               *pstRcvMsg       = VOS_NULL_PTR;
    TAF_SDC_NETWORK_CAP_INFO_STRU                           stNewNwCapInfo;
    VOS_UINT32                                              ulNwCapInfoChanged;

    pstRcvMsg = (MSCC_MMA_NETWORK_CAPABILITY_INFO_IND_STRU *)pstMsg;

    stNewNwCapInfo.enNwEmcBsCap = (TAF_SDC_NW_EMC_BS_CAP_ENUM_UINT8)pstRcvMsg->enNwEmcBsCap;
    stNewNwCapInfo.enNwImsVoCap = (TAF_SDC_NW_IMS_VOICE_CAP_ENUM_UINT8)pstRcvMsg->enNwImsVoCap;

    switch (pstRcvMsg->enLteCsCap)
    {
        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_NO_ADDITION_INFO:
            stNewNwCapInfo.enLteCsCap = TAF_SDC_LTE_CS_CAPBILITY_NO_ADDITION_INFO;
            break;

        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_CSFB_NOT_PREFER:
            stNewNwCapInfo.enLteCsCap = TAF_SDC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER;
            break;

        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_SMS_ONLY:
            stNewNwCapInfo.enLteCsCap = TAF_SDC_LTE_CS_CAPBILITY_SMS_ONLY;
            break;

        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_NOT_SUPPORTED:
            stNewNwCapInfo.enLteCsCap = TAF_SDC_LTE_CS_CAPBILITY_NOT_SUPPORTED;
            break;

        default:
            stNewNwCapInfo.enLteCsCap = TAF_SDC_LTE_CS_CAPBILITY_BUTT;
            break;
    }

    /* �жϵ�ǰ������������GU��L����������Ƿ����˸ı� */
    ulNwCapInfoChanged = TAF_MMA_IsNetworkCapInfoChanged(&stNewNwCapInfo);

    if (VOS_TRUE == ulNwCapInfoChanged)
    {
        /* update infomaton to the corresponding global variable according to RAT */
        TAF_MMA_SetNetworkCapabilityInfo(TAF_SDC_GetSysMode(), &stNewNwCapInfo);
    }

#if (FEATURE_IMS == FEATURE_ON)
    if (VOS_TRUE == TAF_SDC_GetImsSupportFlag())
    {
        /* ֪ͨSPM�����������������SPM���������Ϣ����Ϣ�в�����ǰ��������������SPMȡSDCȫ�ֱ����е� */
        TAF_MMA_SndSpmNetworkCapabilityChangeNotify();

        }
#endif


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UsimRefreshIndMsgProc
 ��������  : MMA���տ�����ָʾ��Ϣ�Ĵ���
 �������  : USIMM_STKREFRESH_IND_STRU* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : z00161729
    �޸�����   : SVLTE ��usim�ӿڵ����޸�
  2.��    ��   : 2012��07��15��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseI��Ŀ�޸�:�޸ĺ��������ͷ���ֵ�Լ�������
  3.��    ��   : 2015��02��06��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
  4.��    ��   : 2015��2��15��
    ��    ��   : c00318887
    �޸�����   : AT&T phaseII:���������ļ�ʱ����AT^FILECHANGE�ϱ����ȴ�CSҵ�������ػ��Ĵ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPihUsimRefreshIndMsgProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
   /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-24, begin */
    USIMM_STKREFRESH_IND_STRU          *pUsimRefreshIndMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucRefreshAllFileRestartFlag;
    VOS_UINT8                          *pucOldImsi;
    VOS_UINT8                           aucNewImsi[TAF_SDC_MAX_IMSI_LEN];
    VOS_UINT8                           ucIsImsiChanged;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT8                           aucIMSIM[NAS_MAX_IMSIM_DATA_LEN];

    PS_MEM_SET(aucIMSIM, 0x00, sizeof(aucIMSIM));
#endif

    pUsimRefreshIndMsg = (USIMM_STKREFRESH_IND_STRU *)pstMsg;

    ucIsImsiChanged = VOS_FALSE;
    pucOldImsi      = TAF_SDC_GetLastSimImsi();
    if (USIMM_API_SUCCESS == USIMM_GetCardIMSI(aucNewImsi))
    {
        if (0 != VOS_MemCmp(pucOldImsi, aucNewImsi, TAF_SDC_MAX_IMSI_LEN))
        {
            ucIsImsiChanged = VOS_TRUE;
        }
    }

    /* ĿǰPIH�ϱ��ļ�ˢ��ָʾ��Ϣ��, USIM�����ϱ���״ָ̬ʾ��MMA
       �����˴��߼���USIMɾ����,MMA��Ҫ���¶�ȡIMSI�Ƚ��Ƿ����ı�
       ,�����йػ��Ϳ������� */
    if (USIMM_REFRESH_ALL_FILE == pUsimRefreshIndMsg->enRefreshType)
    {

        /* ���Կ�������������gcf 27.22.4.7.1.4��ʧ�� */
        ucRefreshAllFileRestartFlag = TAF_SDC_GetRefreshAllFileRestartFlag();

#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_FALSE == TAF_MMA_ProcPihUsimRefreshIndEfUstFileChanged_PreProc())
        {
            TAF_MMA_SndInterUsimChangeInd();

            return VOS_TRUE;
        }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_FALSE == ucIsImsiChanged)
        {
            pucOldImsi      = TAF_SDC_GetCsimImsi();
            PS_MEM_SET(aucNewImsi, 0x00, sizeof(aucNewImsi));
            if (USIMM_API_SUCCESS == USIMM_GetCdmaIMSIM(aucIMSIM))
            {
                (VOS_VOID)TAF_SDC_ConvertCImsiBcdCode(aucIMSIM, aucNewImsi);

                if (0 != PS_MEM_CMP(pucOldImsi, aucNewImsi, TAF_SDC_MAX_IMSI_LEN))
                {
                    PS_MEM_CPY(pucOldImsi, aucNewImsi, TAF_SDC_MAX_IMSI_LEN);

                    ucIsImsiChanged = VOS_TRUE;

#ifdef DMT
                    ucIsImsiChanged = VOS_FALSE;
#endif
                }
            }
        }
#endif

        if (((VOS_TRUE  == NAS_USIMMAPI_IsTestCard())
         || (VOS_FALSE == ucRefreshAllFileRestartFlag))
         && (VOS_FALSE == ucIsImsiChanged))
        {
            TAF_MMA_ReadUsimInfo_PreProc();

            return VOS_TRUE;
        }

        if (VOS_TRUE == TAF_SDC_GetCsEccExistFlg())
        {
            /* ����CSҵ����������ʱ���ȴ�CSҵ�������ػ� */
            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN, TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN_LEN);
            return VOS_TRUE;
        }

        /* ����main�����ػ����� */
        return VOS_FALSE;
    }

    if (USIMM_REFRESH_FILE_LIST == pUsimRefreshIndMsg->enRefreshType)
    {
        /* refresh ��Ϣָʾ�ض��ļ�������� */
        TAF_MMA_UsimRefreshIndFileListChangedMsgProc(pUsimRefreshIndMsg);

        return VOS_TRUE;
    }

    if (USIMM_REFRESH_3G_SESSION_RESET == pUsimRefreshIndMsg->enRefreshType)
    {
       return TAF_MMA_ProcPihUsimRefreshInd3gSessionReset_PreProc();
    }

    return VOS_TRUE;
   /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-24, end */
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcPihUsimRefreshInd3gSessionReset_PreProc
 ��������  : MMA�����ļ�ˢ��ָʾ:3G SESSION RESET
 �������  : ��
 �������  : ��
 �� �� ֵ  : vos_true
             vos_false
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��8��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��2��15��
   ��    ��   : c00318887
   �޸�����   : AT&T phaseII:����CSҵ����������ʱ���ȴ�CSҵ�������ػ�
3.��    ��   : 2015��4��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 TAF_MMA_ProcPihUsimRefreshInd3gSessionReset_PreProc(VOS_VOID)
{
    TAF_MMA_ReadUsimInfo_PreProc();

    /* ��ǰ״̬������main״̬��,�����ڲ���״̬�ı�ָʾ��Ϣ���� */
    if (TAF_MMA_FSM_MAIN != TAF_MMA_GetCurrFsmId())
    {
        TAF_MMA_SndInterUsimChangeInd();

        return VOS_TRUE;
    }

    /* �ǿ����������յ���״̬�������ػ����� */
    if (STA_FSM_NULL == g_StatusContext.ulFsmState)
    {
       return VOS_TRUE;
    }


    if (VOS_TRUE == TAF_SDC_GetCsEccExistFlg())
    {
        /* ����CS ҵ����������ʱ���ȴ�CSҵ�������ػ� */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN, TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN_LEN);
        return VOS_TRUE;
    }

    /* �Ѿ����������main�����ػ����� */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_ReadUsimInfo_PreProc
 ��������  : ������ȡUSIM���ļ������Ϣ
 �������  : ucIsNeedReadImsim:�Ƿ���Ҫ��ȡCSIM��IMSIM�ļ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��18��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��4��1��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ�޸�:����ecall��ؿ��ļ���ȡ
 3.��    ��   : 2015��2��9��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��EONS�����޸�
 4.��    ��   : 2015��12��28��
   ��    ��   : h00313353
   �޸�����   : 1X ��������
*****************************************************************************/

VOS_VOID TAF_MMA_ReadUsimInfo_PreProc(
    VOS_VOID
)
{
    VOS_UINT8                           ucIsNeedStartTimer;

    ucIsNeedStartTimer                  = VOS_FALSE;

    if (TAF_SDC_USIM_STATUS_VALID == TAF_SDC_GetUsimStatus())
    {
        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        /*  ����ecallģʽ��Ϣ */
        TAF_MMA_UpdateCallMode();
#endif
        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-4, end */

        /* ��ȡSPN�ļ� */
        TAF_MMA_ReadSpnFile();

        TAF_MMA_ReadSimCphsOperNameFile();

        /* ����ѡ��˵�����ʹ�ܣ�������Ҫ��6F15�ļ� */
        TAF_MMA_ReadCustomerServiceProfileFile_SwitchOn();

        /* ���뼼��ƽ�����ʹ�ܣ�������4F36�ļ� */
        TAF_MMA_ReadRatModeFile();

        TAF_MMA_ReadOplFile();
        TAF_MMA_ReadPnnFile();
        TAF_MMA_ReadSpdiFile();

        ucIsNeedStartTimer  = VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_SDC_USIM_STATUS_VALID == TAF_SDC_GetCsimStatus())
    {
        /*�����ļ�RUIMID*/
        TAF_MMA_ReadRuimidFile();
        ucIsNeedStartTimer  = VOS_TRUE;
    }
#endif

    if (VOS_TRUE == ucIsNeedStartTimer)
    {
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_READ_SIM_FILES, TI_TAF_MMA_WAIT_READ_SIM_FILES_LEN);
    }

    return;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_SndAtIccStatusInd_PreProc
 ��������  : Ԥ��������AT����usim status ind��Ϣ
 �������  :  VOS_UINT32            ulUsimStaChg--��״̬�Ƿ�ı�

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��18��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��4��1��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:���ĳ�ʼ��״̬����
 3.��    ��   : 2015��11��2��
   ��    ��   : l00289540
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
*****************************************************************************/

VOS_VOID TAF_MMA_SndAtIccStatusInd_PreProc(
    VOS_UINT32                          ulUsimStaChg
)
{
    VOS_UINT8                           ucSimStatus;
    VOS_UINT8                           ucSimLockStatus;
    TAF_MMA_FSM_ID_ENUM_UINT32          enCurrFsmId;
    VOS_UINT32                          ulFsmTopState;

    enCurrFsmId = TAF_MMA_GetCurrFsmId();

    ulFsmTopState = TAF_MMA_FSM_GetFsmTopState();

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        ucSimStatus     = MMA_GetCsimStatus(ulUsimStaChg);

        /* ��ȡ����״̬ */
        if (MMA_SIM_IS_LOCK == MMA_GetCsimMeLockStatus())
        {
            ucSimLockStatus                 = VOS_TRUE;
        }
        else
        {
            ucSimLockStatus                 = VOS_FALSE;
        }
    }
    else
#endif
    {
        ucSimStatus = MMA_GetUsimStatus(ulUsimStaChg);

        /* ��ȡ����״̬ */
        if (MMA_SIM_IS_LOCK == MMA_GetMeLockStatus())
        {
            ucSimLockStatus                 = VOS_TRUE;
        }
        else
        {
            ucSimLockStatus                 = VOS_FALSE;
        }
    }

    /* �Ȳ���ڼ䲻�ϱ�SIMST��AP */
   if ((TAF_PH_MODE_FULL == TAF_SDC_GetCurPhoneMode())
    && (VOS_TRUE         == g_ucUsimHotOutFlag))
   {
       g_ucUsimHotOutFlag = VOS_FALSE;

       return;
   }

   /* ����RIL�߼�,�ϵ��һ�������յ�����Э��ջ������ɵ�����(PSINIT)
      �ϵ�ʱ�ϱ��Ŀ�״̬�ӳٵ�Э��ջ��ʼ�����֮���ϱ���ȥ */
   if ((TAF_MMA_FSM_PHONE_MODE == enCurrFsmId)
    && (TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT == ulFsmTopState))
   {
       return;
   }

   TAF_MMA_SndAtIccStatusInd(ucSimStatus, ucSimLockStatus);

   /* ��״̬�����仯���˴���Ϊ�ǿ��Ȳ�ε��µģ����ø���Dplmn�ĳ���Ϊ IMSI_CHANGE */
   TAF_MMA_SetDplmnUpdateScene(TAF_MMA_AP_PRESET_DPLMN_SCENE_IMSI_CHANGE);

   return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcUsimStatusIndInPhoneModeProc_PreProc
 ��������  : ���ػ������д���״ָ̬ʾ
 �������  : pstUsimMsg-��״̬�ı�ָʾ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��ǰԤ�������,����Ҫ�����������
             VOS_FALSE:��ǰԤ����δ���,��Ҫ���������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��18��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��4��1��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:���ĳ�ʼ��״̬����
 3.��    ��   : 2015��4��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 TAF_MMA_ProcUsimStatusIndInPhoneModeProc_PreProc(
    VOS_UINT32                          ulUsimStaChg,
    VOS_UINT32                          ulImsiChg
)
{
    VOS_UINT32                          ulFsmTopState;

    ulFsmTopState                       = TAF_MMA_FSM_GetFsmTopState();

    /* ���������У����״̬����������״̬����ֱ�ӽ�״̬������״̬�ϱ� */
    if (VOS_TRUE == TAF_MMA_IsNeedProcUsimStatusIndInFsmPhoneMode(ulFsmTopState))
    {
        /* ֱ�ӽ�״̬������״̬�ϱ� */
        return VOS_FALSE;
    }

    /* ��״̬��IMSI�����ı������¶�ȡ���ļ������濨״̬�ı���Ϣ */
    TAF_MMA_SndInterUsimChangeInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcUsimStatusIndInFsmMain_PreProc
 ��������  : main״̬�����յ���״̬�仯�Ĵ���
 �������  : VOS_UINT32                          ulUsimStaChg
             VOS_UINT32                          ulImsiChg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��6��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcUsimStatusIndInFsmMain_PreProc(
    VOS_UINT32                          ulUsimStaChg,
    VOS_UINT32                          ulImsiChg
)
{
    TAF_PH_FPLMN_OPERATE_STRU           stFplmnOperate;

    if (VOS_TRUE == MN_MMA_GetRoamingBrokerFlg())
    {
        stFplmnOperate.ulCmdType = TAF_PH_FPLMN_DEL_ALL;
        TAF_MMA_SndMsccCFPlmnSetReq(&stFplmnOperate);
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF, TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF_LEN);
    }

    /* �ǿ����������յ���״̬�������ػ����� */
    if (STA_FSM_NULL == g_StatusContext.ulFsmState)
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == TAF_SDC_GetCsEccExistFlg())
    {
        /* ���IMSI����Ҵ���CS ҵ����������ʱ���ȴ�CSҵ�������ػ� */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN, TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN_LEN);
        return VOS_TRUE;
    }

    /* �Ѿ����������main�����ػ����� */
    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcUsimStatusIndInFsmSyscfg_PreProc
 ��������  : syscfg״̬�����յ���״̬�仯��Ԥ����
 �������  : VOS_UINT32                          ulUsimStaChg
             VOS_UINT32                          ulImsiChg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��6��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcUsimStatusIndInFsmSyscfg_PreProc(
    VOS_UINT32                          ulUsimStaChg,
    VOS_UINT32                          ulImsiChg
)
{
    /* �����ڲ��Ŀ�״̬�ı�ָʾ��Ϣ */
    TAF_MMA_SndInterUsimChangeInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcUsimStatusIndInFsmImsSwitch_PreProc
 ��������  : ims switch״̬�����յ���״̬�仯��Ԥ����
 �������  : VOS_UINT32                          ulUsimStaChg
             VOS_UINT32                          ulImsiChg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��6��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcUsimStatusIndInFsmImsSwitch_PreProc(
    VOS_UINT32                          ulUsimStaChg,
    VOS_UINT32                          ulImsiChg
)
{
    /* �����ڲ��Ŀ�״̬�ı�ָʾ��Ϣ */
    TAF_MMA_SndInterUsimChangeInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcUsimStatusIndByCurFsmId
 ��������  : ���ݵ�ǰ״̬��Id����״ָ̬ʾ
 �������  : ulUsimmStaChg:USIMM��״̬�Ƿ����ı�
             ulImsiChg    :����IMSI�Ƿ����ı�
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE:  ����Ҫ����״̬������
             VOS_FALSE: ��Ҫ����״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��28��
    ��    ��   : h00313353
    �޸�����   : 1X ��������

*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcUsimStatusIndByCurFsmId(
    VOS_UINT32                          ulUsimmStaChg,
    VOS_UINT32                          ulImsiChg
)
{
    /* ��״̬�仯�ڲ�ͬ��״̬��ʱ��Ԥ���� */
    switch(TAF_MMA_GetCurrFsmId())
    {
        case TAF_MMA_FSM_PHONE_MODE:

            return TAF_MMA_ProcUsimStatusIndInPhoneModeProc_PreProc(ulUsimmStaChg, ulImsiChg);

        case TAF_MMA_FSM_SYS_CFG:

            return TAF_MMA_ProcUsimStatusIndInFsmSyscfg_PreProc(ulUsimmStaChg, ulImsiChg);

        case TAF_MMA_FSM_IMS_SWITCH:

            return TAF_MMA_ProcUsimStatusIndInFsmImsSwitch_PreProc(ulUsimmStaChg, ulImsiChg);

        default:

            return TAF_MMA_ProcUsimStatusIndInFsmMain_PreProc(ulUsimmStaChg, ulImsiChg);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccCampOnInd_PreProc
 ��������  : ��������MSCC��פ��ָʾ��Ϣ
 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��19��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��6��16��
   ��    ��   : w00167002
   �޸�����   : DSDS III����
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCampOnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_CAMP_ON_IND_STRU_STRU      *pstCampOnInd = VOS_NULL_PTR;

    pstCampOnInd = (MSCC_MMA_CAMP_ON_IND_STRU_STRU*)pstMsg;

    /* MMA�ڴ�����Ƶ����ռ��״̬��ֱ�Ӷ���������Ϣ����ˢ��MMA�ı�����
       ���ϱ�����ʱ���AT�в�ѯ��������Ƶ��Դ����ʱ��״̬*/
#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        return VOS_TRUE;
    }
#endif

    if (VOS_TRUE == pstCampOnInd->ucCampOnFlg)
    {
        TAF_SDC_SetCampOnFlag(VOS_TRUE);
    }
    else
    {
        TAF_SDC_SetCampOnFlag(VOS_FALSE);
    }

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccAreaLostNoRfStatusInd_PreProc
 ��������  : ��������MSCC��פ��ָʾ��Ϣ
 �������  : ulEventType  ����ϢID��task ID����
             pstMsg       ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��13��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccRfAvailableInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_RF_AVAILABLE_IND_STRU      *pstRfAvail = VOS_NULL_PTR;

    pstRfAvail = (MSCC_MMA_RF_AVAILABLE_IND_STRU*)pstMsg;

    if (NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_3GPP == pstRfAvail->enRatType)
    {
        TAF_SDC_Set3GppRfAvailFlag(pstRfAvail->ucRfAvailFlg);

        /* ����ӳٶ�ʱ���������У�������ʱ�� */
        if ((TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS))
         && (VOS_TRUE == pstRfAvail->ucRfAvailFlg))
        {
            /* ������ʱ�� */
            TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS);

            TAF_MMA_StartTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS, (TAF_MMA_GetDelayReportServiceStatusCfgTimerLen()));

            return VOS_TRUE;
        }
    }

    if (NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_1X == pstRfAvail->enRatType)
    {
        TAF_SDC_Set1xRfAvailFlag(pstRfAvail->ucRfAvailFlg);
    }

    if (NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_HRPD == pstRfAvail->enRatType)
    {
        TAF_SDC_SetHrpdRfAvailFlag(pstRfAvail->ucRfAvailFlg);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertSdcRatToAppRatType
 ��������  : ��SDC��RAT TYPEת����APP��RAT TYPE
 �������  : NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8 enMsccRatType
 �������  : TAF_MMA_RAT_TYPE_ENUM_UINT8
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��15��
    ��    ��   : l00208543
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
*****************************************************************************/
TAF_MMA_RAT_TYPE_ENUM_UINT8 TAF_MMA_ConvertSdcRatToAppRatType(
                        TAF_SDC_SYS_MODE_ENUM_UINT8 enSdcRatType
                        )
{
    switch (enSdcRatType)
    {
        case TAF_SDC_SYS_MODE_GSM:
             return TAF_MMA_RAT_GSM;

        case TAF_SDC_SYS_MODE_WCDMA:
             return TAF_MMA_RAT_WCDMA;

        case TAF_SDC_SYS_MODE_LTE:
             return TAF_MMA_RAT_LTE;

        default:
            MMA_WARNINGLOG("TAF_MMA_ConvertSdcRatToAppRatType():WORNING:The input is invalid.");
            return TAF_MMA_RAT_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertMsccDomainToMmaDomainType
 ��������  : ��MSCC��DOMAIN TYPEת����MMA��DOMAIN TYPE
 �������  : NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32      enMsccDomainType
 �������  : TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��15��
    ��    ��   : l00208543
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��9��
    ��    ��   : h00313353
    �޸�����   : SysCfg SrvDomain�궨��toö��
*****************************************************************************/
TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8 TAF_MMA_ConvertMsccDomainToMmaDomainType(
                        NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32      enMsccDomainType
)
{
    switch (enMsccDomainType)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_NO_DOMAIN:
        case NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING:
             return TAF_MMA_SERVICE_DOMAIN_NULL;

        case NAS_MSCC_PIF_SRVDOMAIN_CS:
             return TAF_MMA_SERVICE_DOMAIN_CS;

        case NAS_MSCC_PIF_SRVDOMAIN_PS:
             return TAF_MMA_SERVICE_DOMAIN_PS;

        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
             return TAF_MMA_SERVICE_DOMAIN_CS_PS;

        case NAS_MSCC_PIF_SRVDOMAIN_NO_CHANGE:
             return TAF_MMA_SERVICE_DOMAIN_NOCHANGE;
        default:
            MMA_WARNINGLOG("TAF_MMA_ConvertMsccDomainToMmaDomainType():WORNING:The input is invalid.");
            return TAF_MMA_SERVICE_DOMAIN_NULL;
    }
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndRegRejInfoInd
 ��������  : �յ�MSCC��ָ�����ע�����Ĵ���
 �������  : pstRejInfoInd--MSCC�ϱ���ע������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��13��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��4��1��
    ��    ��   : z00161729
    �޸�����   : DTS2014040300125:service ���ܺ�����detach ind������Ҫ�ϱ�^rejinfo
*****************************************************************************/
VOS_VOID TAF_MMA_SndRegRejInfoInd(
    MSCC_MMA_REG_RESULT_IND_STRU        *pstRejInfoInd
)
{
    /* ��MSCC����������ת��ΪTAF���������ͣ������ϱ� */
    TAF_PH_REG_REJ_INFO_STRU            stTafRejInfo;

    /* ����ϱ��¼� */
    stTafRejInfo.enRat        = TAF_MMA_ConvertSdcRatToAppRatType(pstRejInfoInd->stCampPostion.enNetRatType);
    stTafRejInfo.stPlmnId.Mcc = pstRejInfoInd->stCampPostion.stPlmnId.ulMcc;
    stTafRejInfo.stPlmnId.Mnc = pstRejInfoInd->stCampPostion.stPlmnId.ulMnc;

    stTafRejInfo.enSrvDomain  = TAF_MMA_ConvertMsccDomainToMmaDomainType(pstRejInfoInd->enCnDomainId);
    stTafRejInfo.ulRejCause   = pstRejInfoInd->enRejCause;

    /* �ܾ�����Ϊע�ᱻ�� */
    stTafRejInfo.ucRejType    = NAS_MSCC_PIF_REJ_TYPE_REG;

    stTafRejInfo.aucReserved[0]       = 0;
    stTafRejInfo.ucOriginalRejCause   = pstRejInfoInd->ucOriginalRejCause;
    stTafRejInfo.ulCellId             = pstRejInfoInd->stCampPostion.ulCellId;
    stTafRejInfo.ucRac                = pstRejInfoInd->stCampPostion.ucRac;
    stTafRejInfo.usLac                = pstRejInfoInd->stCampPostion.usLac;

    /* ��PLMN IDתΪBCD��ʽ */
    MMA_PlmnId2Bcd(&stTafRejInfo.stPlmnId);

    if (VOS_TRUE == TAF_MMA_IsRegRejChangeNeedRpt())
    {
        TAF_MMA_SndRegRejInd(&stTafRejInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccRegResultInd_PreProc
 ��������  : �յ�MSCC��ָ�����ע�����Ĵ���
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��15��
    ��    ��   : l00208543
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��13��
    ��    ��   : W00176964
    �޸�����   : Volte_PhaseIII ��Ŀ�޸�
  3.��    ��   : 2014��12��13��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI ֪ͨIMSA����״̬�޸�
  4.��    ��   : 2015��1��28��
    ��    ��   : y00245242
    �޸�����   : iteration 9��������IMSA�ӿڵ�MSCCģ��
  5.��    ��   : 2015��6��9��
    ��    ��   : n00269697
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ϊ�˾�����ʹ����Ч�ĵ���λ����Ϣ��
                 ע��ɹ�����Ҫ���¹������ʱ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccRegResultInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_REG_RESULT_IND_STRU        *pstRegResultInd   = VOS_NULL_PTR;
    TAF_SDC_PLMN_ID_STRU                *pstCurrPlmnId = VOS_NULL_PTR;

    pstRegResultInd     = (MSCC_MMA_REG_RESULT_IND_STRU *)pstMsg;
    pstCurrPlmnId       = TAF_SDC_GetCurrCampPlmnId();

    /* ������״̬֪ͨ��MMC�ȱ�REG_RESULT_IND���ٱ�SERVCIE_STATUS_IND����ʱ֪ͨIMSA�ķ���״̬��׼ȷ */

    /* Ϊ�˾�����ʹ����Ч�ĵ���λ����Ϣ��ע��ɹ�����Ҫ���¹������ʱ��� */
    if (VOS_TRUE == pstRegResultInd->ucRegRslt)
    {
        /* �޸ĺ����� */
        TAF_MMA_UpdateGeoPlmnIdInfo(pstCurrPlmnId);
    }

    /* ע��ʧ��ʱ����Ҫ�ϱ��ܾ�ԭ��ֵ */
    if ((VOS_FALSE == pstRegResultInd->ucRegRslt)
     && (VOS_TRUE  == pstRegResultInd->ucReportCauseCtrl))
    {
        TAF_MMA_SndRegRejInfoInd(pstRegResultInd);
    }


    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccImsVoiceCapInd_PreProc
 ��������  : �յ�IMSA��IMS voice cap��Ϣ��Ԥ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��13��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��01��28��
    ��    ��   : y00245242
    �޸�����   : iteration 9������ IMSA�ӿ����Ƶ�MSCCģ��
  3.��    ��   : 2015��06��17��
    ��    ��   : w00316404
    �޸�����   : NEXT B26 Project,֪ͨMTC��ǰIMS VOICE�Ƿ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccImsVoiceCapInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_IMS_VOICE_CAP_IND_STRU *pstImsVoiceCap = VOS_NULL_PTR;

    pstImsVoiceCap = (MSCC_MMA_IMS_VOICE_CAP_IND_STRU *)pstMsg;


    /* ֪ͨSPM��ǰIMS VOICE�Ƿ���� */
    TAF_MMA_SndSpmImsVoiceCapInd(pstImsVoiceCap->ucAvail);

    /* ֪ͨMTC��ǰIMS VOICE�Ƿ���� */
    TAF_MMA_SndMtcImsVoiceCapInd(pstImsVoiceCap->ucAvail);

    return VOS_TRUE;
}

/* ɾ����ʱ�������߼� */
#endif
/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccUsimAuthFailInd_PreProc
 ��������  : �յ�MSCC��������USIM��Ȩʧ��ԭ��ֵ��Ϣ���д���
 �������  : MSCC_MMA_USIM_AUTH_FAIL_IND_STRU *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��15��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��4��1��
    ��    ��   : z00161729
    �޸�����   : DTS2014040300125:service ���ܺ�����detach ind������Ҫ�ϱ�^rejinfo
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccUsimAuthFailInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��MMC����������ת��ΪTAF���������ͣ������ϱ� */
    TAF_PH_REG_REJ_INFO_STRU            stTafRejInfo;
    MSCC_MMA_USIM_AUTH_FAIL_IND_STRU    *pstAuthFailInd  = VOS_NULL_PTR;

    pstAuthFailInd            = (MSCC_MMA_USIM_AUTH_FAIL_IND_STRU *)pstMsg;

    /* ����ϱ��¼� */
    stTafRejInfo.enRat        = TAF_MMA_ConvertSdcRatToAppRatType(pstAuthFailInd->stCampPostion.enNetRatType);
    stTafRejInfo.stPlmnId.Mcc = pstAuthFailInd->stCampPostion.stPlmnId.ulMcc;
    stTafRejInfo.stPlmnId.Mnc = pstAuthFailInd->stCampPostion.stPlmnId.ulMnc;
    stTafRejInfo.enSrvDomain  = TAF_MMA_ConvertMsccDomainToMmaDomainType(pstAuthFailInd->enCnDomainId);

    /* Ϊ�˺�����ܾ�ԭ��ֵ���֣�usim��Ȩʧ��ԭ��ֵ����һ��ƫ��λ */
    stTafRejInfo.ulRejCause   = pstAuthFailInd->enRejCause + (1 << 16);

    stTafRejInfo.ucRejType   = NAS_MSCC_PIF_REJ_TYPE_USIM_AUTH;

    stTafRejInfo.aucReserved[0]       = 0;
    stTafRejInfo.ucOriginalRejCause   = (VOS_UINT8)NAS_MML_REG_FAIL_CAUSE_NULL;
    stTafRejInfo.ulCellId             = pstAuthFailInd->stCampPostion.ulCellId;
    stTafRejInfo.ucRac                = pstAuthFailInd->stCampPostion.ucRac;
    stTafRejInfo.usLac                = pstAuthFailInd->stCampPostion.usLac;

    /* ��PLMN IDתΪBCD��ʽ */
    MMA_PlmnId2Bcd(&stTafRejInfo.stPlmnId);

    if (VOS_TRUE == TAF_MMA_IsRegRejChangeNeedRpt())
    {
        TAF_MMA_SndRegRejInd(&stTafRejInfo);
    }


    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccCsServiceConnStatusInd_PreProc
 ��������  : �յ�MSCC�ϱ���csҵ����������״ָ̬ʾ��Ϣ
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��04��
    ��    ��   : z00161729
    �޸�����   : DTS2014022800234:����mm�յ�paging������csҵ���������Ӵ��ڣ�
                 ����ѯ^usersrvstateʱ������csҵ��syscfgex����ʧ�ܻظ�����csҵ�񣬲�һ��
  2.��    ��   : 2014��06��27��
    ��    ��   : s00217060
    �޸�����   : K3V3 ��ģ����������:CS�������״̬֪ͨMTC
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCsServiceConnStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU                *pstCsServiceConnStatusInd = VOS_NULL_PTR;
    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    TAF_MTC_SRV_CONN_STATE_INFO_STRU                        stMmaMtcConnStInfo;
    TAF_CTRL_STRU                                           stCtrl;
#endif
    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */

    /* ��ʼ�� */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    PS_MEM_SET(&stCtrl, 0x0,sizeof(stCtrl));
    PS_MEM_SET(&stMmaMtcConnStInfo, 0x0,sizeof(stMmaMtcConnStInfo));
#endif

    pstCsServiceConnStatusInd = (MSCC_MMA_CS_SERVICE_CONN_STATUS_IND_STRU *)pstMsg;

    TAF_SDC_SetCsServiceConnStatusFlag(pstCsServiceConnStatusInd->ucCsServiceConnStatusFlag);

    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    stMmaMtcConnStInfo.bitOpCsSrv           = VOS_TRUE;
    stMmaMtcConnStInfo.enCsSrvConnState     = pstCsServiceConnStatusInd->ucCsServiceConnStatusFlag;

    /* ��дCTLͷ */
    TAF_API_CTRL_HEADER(&stCtrl, WUEPS_PID_MMA, 0, 0);

    /* ������״̬����MTC */
    MTC_SetModemServiceConnState(&stCtrl, &stMmaMtcConnStInfo);
#endif
    /* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */
#if (FEATURE_ON == FEATURE_BASTET)
    if(VOS_TRUE == TAF_SDC_GetBastetSupportFlag())
    {
        TAF_MMA_SndBastetCsServiceInd(pstCsServiceConnStatusInd->ucCsServiceConnStatusFlag);
    }
#endif
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccServRejInd_PreProc
 ��������  : �յ�MSCC�������ķ��񱻾�ԭ��ֵ��Ϣ���д���
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : z00161729
    �޸�����   : DTS2014040300125:service ���ܺ�����detach ind����û���ϱ�^rejinfo

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccServRejInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_SERV_REJ_IND_STRU         *pstServRejInd = VOS_NULL_PTR;
    TAF_PH_REG_REJ_INFO_STRU            stTafServRejInfo;

    pstServRejInd = (MSCC_MMA_SERV_REJ_IND_STRU *) pstMsg;
    PS_MEM_SET(&stTafServRejInfo, 0, sizeof(stTafServRejInfo));

    /* ����ϱ��¼� */
    stTafServRejInfo.enRat        = TAF_MMA_ConvertSdcRatToAppRatType(pstServRejInd->stCampPostion.enNetRatType);
    stTafServRejInfo.stPlmnId.Mcc = pstServRejInd->stCampPostion.stPlmnId.ulMcc;
    stTafServRejInfo.stPlmnId.Mnc = pstServRejInd->stCampPostion.stPlmnId.ulMnc;

    stTafServRejInfo.enSrvDomain  = TAF_MMA_ConvertMsccDomainToMmaDomainType(pstServRejInd->enCnDomainId);

    stTafServRejInfo.ulRejCause   = pstServRejInd->usRejCause;
    stTafServRejInfo.ucRejType    = NAS_MSCC_PIF_REJ_TYPE_SERV_REQ;

    /* ��PLMN IDתΪBCD��ʽ */
    MMA_PlmnId2Bcd(&stTafServRejInfo.stPlmnId);

    stTafServRejInfo.aucReserved[0]       = 0;
    stTafServRejInfo.ucOriginalRejCause   = pstServRejInd->ucOriginalRejCause;
    stTafServRejInfo.ulCellId             = pstServRejInd->stCampPostion.ulCellId;
    stTafServRejInfo.ucRac                = pstServRejInd->stCampPostion.ucRac;
    stTafServRejInfo.usLac                = pstServRejInd->stCampPostion.usLac;

    if (VOS_TRUE == TAF_MMA_IsRegRejChangeNeedRpt())
    {
        TAF_MMA_SndRegRejInd(&stTafServRejInfo);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccAttachCnf_PreProc
 ��������  : �յ�MSCC��������attach cnf���д���
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��30��
    ��    ��   : z00161729
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccAttachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_ATTACH_CNF_STRU            *pstAttachCnf = VOS_NULL_PTR;

    pstAttachCnf = (MSCC_MMA_ATTACH_CNF_STRU*)pstMsg;

    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstAttachCnf->enCnDomainId)
    {
        TAF_SDC_SetCsAttachAllowFlg(VOS_TRUE);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstAttachCnf->enCnDomainId)
    {
        TAF_SDC_SetPsAttachAllowFlg(VOS_TRUE);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == pstAttachCnf->enCnDomainId)
    {
        TAF_SDC_SetCsAttachAllowFlg(VOS_TRUE);
        TAF_SDC_SetPsAttachAllowFlg(VOS_TRUE);
    }
    else
    {
    }

    /* ��״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccDplmnSetCnf_PreProc
 ��������  : MMA�յ�MSCC���͵� ID_MSCC_MMA_DPLMN_SET_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��11��2��
    ��    ��   : l00289540
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccDplmnSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg

)
{
    TAF_MMA_DPLMN_SET_CNF_STRU         *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (TAF_MMA_DPLMN_SET_CNF_STRU *)pstMsg;

    /* MMA��AT����ID_TAF_MMA_DPLMN_SET_CNF��Ϣ */
    TAF_MMA_SndDplmnSetCnf(pstRcvMsg->ulRslt, pstRcvMsg->stCtrl);

    TAF_MMA_SetDplmnUpdateScene(TAF_MMA_AP_PRESET_DPLMN_SCENE_DPLMN_UPDATE);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccDetachInd_PreProc
 ��������  : �յ�MSCC��������detach ind����ԭ��ֵ��Ϣ���д���
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : z00161729
    �޸�����   : DTS2014040300125:service ���ܺ�����detach ind����û���ϱ�^rejinfo

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccDetachInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_DETACH_IND_STRU            *pstDetachInd = VOS_NULL_PTR;
    TAF_PH_REG_REJ_INFO_STRU            stTafServRejInfo;

    pstDetachInd = (MSCC_MMA_DETACH_IND_STRU *) pstMsg;
    PS_MEM_SET(&stTafServRejInfo, 0, sizeof(stTafServRejInfo));

    if (NAS_MSCC_PIF_NETWORK_DETACH_TYPE_NOATTACH == pstDetachInd->enNetworkDetachType)
    {
        /* ����ϱ��¼� */
        stTafServRejInfo.enRat        = TAF_MMA_ConvertSdcRatToAppRatType(pstDetachInd->stCampPostion.enNetRatType);
        stTafServRejInfo.stPlmnId.Mcc = pstDetachInd->stCampPostion.stPlmnId.ulMcc;
        stTafServRejInfo.stPlmnId.Mnc = pstDetachInd->stCampPostion.stPlmnId.ulMnc;

        stTafServRejInfo.enSrvDomain  = TAF_MMA_ConvertMsccDomainToMmaDomainType(pstDetachInd->enCnDomainId);

        stTafServRejInfo.ulRejCause   = pstDetachInd->ulDetachCause;
        stTafServRejInfo.ucRejType    = NAS_MSCC_PIF_REJ_TYPE_NETWORK_DETACH_IND;

        /* ��PLMN IDתΪBCD��ʽ */
        MMA_PlmnId2Bcd(&stTafServRejInfo.stPlmnId);

        stTafServRejInfo.aucReserved[0]       = 0;
        stTafServRejInfo.ucOriginalRejCause   = pstDetachInd->ucOriginalDetachCause;
        stTafServRejInfo.ulCellId             = pstDetachInd->stCampPostion.ulCellId;
        stTafServRejInfo.ucRac                = pstDetachInd->stCampPostion.ucRac;
        stTafServRejInfo.usLac                = pstDetachInd->stCampPostion.usLac;

        if (VOS_TRUE == TAF_MMA_IsRegRejChangeNeedRpt())
        {
            TAF_MMA_SndRegRejInd(&stTafServRejInfo);
        }
    }

    /* ��״̬������ */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertMsccCauseToMmaFormat
 ��������  : ��MSCC��ʽ��CAUSEֵת����MMA��ʽ��
 �������  : MSCC_MMA_NET_SCAN_CAUSE_ENUM_UINT8   enMsccCause
 �������  : TAF_MMA_NET_SCAN_CAUSE_ENUM_UINT8  *pstMmaCause
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ConvertMsccCauseToTafFormat(
    NAS_MSCC_PIF_NET_SCAN_CAUSE_ENUM_UINT8   enMsccCause,
    TAF_MMA_NET_SCAN_CAUSE_ENUM_UINT8  *pstMmaCause
)
{
    switch ( enMsccCause )
    {
        case NAS_MSCC_PIF_NET_SCAN_CAUSE_SIGNAL_EXIST :
            *pstMmaCause = TAF_MMA_NET_SCAN_CAUSE_SIGNAL_EXIST;
            break;

        case NAS_MSCC_PIF_NET_SCAN_CAUSE_STATE_NOT_ALLOWED :
            *pstMmaCause = TAF_MMA_NET_SCAN_CAUSE_STATE_NOT_ALLOWED;
            break;

        case NAS_MSCC_PIF_NET_SCAN_CAUSE_FREQ_LOCK :
           *pstMmaCause = TAF_MMA_NET_SCAN_CAUSE_FREQ_LOCK;
            break;

        case NAS_MSCC_PIF_NET_SCAN_CAUSE_PARA_ERROR :
            *pstMmaCause = TAF_MMA_NET_SCAN_CAUSE_PARA_ERROR;
            break;

        case NAS_MSCC_PIF_NET_SCAN_CAUSE_CONFLICT :
            *pstMmaCause = TAF_MMA_NET_SCAN_CAUSE_CONFLICT;
            break;

        case NAS_MSCC_PIF_NET_SCAN_CAUSE_SERVICE_EXIST :
            *pstMmaCause = TAF_MMA_NET_SCAN_CAUSE_SERVICE_EXIST;
            break;

        case NAS_MSCC_PIF_NET_SCAN_CAUSE_NOT_CAMPED :
            *pstMmaCause = TAF_MMA_NET_SCAN_CAUSE_NOT_CAMPED;
            break;

        case NAS_MSCC_PIF_NET_SCAN_CAUSE_RAT_TYPE_ERROR :
            *pstMmaCause = TAF_MMA_NET_SCAN_CAUSE_RAT_TYPE_ERROR;
            break;

        default:
            *pstMmaCause = TAF_MMA_NET_SCAN_CAUSE_BUTT;
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertMsccBandToTafFormat
 ��������  : ��MSCCƵ��ת����Taf��ʽ
 �������  : NAS_MML_MS_BAND_INFO_STRU          *pstMsccBand
 �������  : TAF_USER_SET_PREF_BAND64           *pstUserBand
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ConvertMsccBandToTafFormat(
    NAS_MSCC_PIF_UE_SUPPORT_FREQ_BAND_STRU     *pstMsccBand,
    TAF_USER_SET_PREF_BAND64                   *pstUserBand
)
{
    TAF_MMA_USER_PREF_BAND_STRU        *pstUserBitBand      = VOS_NULL_PTR;
    GSM_BAND_STRU                      *pstGsmBitBand       = VOS_NULL_PTR;
    WCDMA_BAND_STRU                    *pstWcdmaBitBand     = VOS_NULL_PTR;
    TAF_MMA_USER_BAND_SET_UN            uUserSetBand;

    PS_MEM_SET(&uUserSetBand, 0x00, sizeof(TAF_MMA_USER_BAND_SET_UN));

    /* uUserSetBand���յ���MSCC��ʽƵ�α����32λ */
    pstUserBitBand                        = &(uUserSetBand.BitBand);
    pstGsmBitBand                         = &(pstMsccBand->unGsmBand.stBitBand);
    pstWcdmaBitBand                       = &(pstMsccBand->unWcdmaBand.stBitBand);

    pstUserBitBand->BandGsm850            = pstGsmBitBand->BandGsm850;
    pstUserBitBand->BandGsmDcs1800        = pstGsmBitBand->BandGsm1800;
    pstUserBitBand->BandGsmEgsm900        = pstGsmBitBand->BandGsmE900;
    pstUserBitBand->BandGsmPcs1900        = pstGsmBitBand->BandGsm1900;
    pstUserBitBand->BandGsmPgsm900        = pstGsmBitBand->BandGsmP900;
    pstUserBitBand->BandGsmRgsm900        = pstGsmBitBand->BandGsmR900;

    pstUserBitBand->BandWcdma_I_Imt2k1    = pstWcdmaBitBand->BandWCDMA_I_2100;
    pstUserBitBand->BandWcdma_II_PCS_1900 = pstWcdmaBitBand->BandWCDMA_II_1900;
    pstUserBitBand->BandWcdma_III_1800    = pstWcdmaBitBand->BandWCDMA_III_1800;
    pstUserBitBand->BandWcdma_IV_1700     = pstWcdmaBitBand->BandWCDMA_IV_1700;
    pstUserBitBand->BandWcdma_V_850       = pstWcdmaBitBand->BandWCDMA_V_850;
    pstUserBitBand->BandWcdma_VI_800      = pstWcdmaBitBand->BandWCDMA_VI_800;
    pstUserBitBand->BandWcdma_VII_2600    = pstWcdmaBitBand->BandWCDMA_VII_2600;
    pstUserBitBand->BandWcdma_VIII_900    = pstWcdmaBitBand->BandWCDMA_VIII_900;
    pstUserBitBand->BandWcdma_IX_1700     = pstWcdmaBitBand->BandWCDMA_IX_J1700;
    pstUserBitBand->BandWCDMA_XIX_850     = pstWcdmaBitBand->BandWCDMA_XIX_850;
    pstUserBitBand->BandWcdma_XI_1500     = pstWcdmaBitBand->BandWCDMA_XI_1500;

    /* ��uUserSetBandת���ɵ�32λ�͸�32λ�ṹ */
    pstUserBand->ulBandHigh = uUserSetBand.ulPrefBand & TAF_PH_BAND_NEED_CHANGE_TO_64BIT;
    pstUserBand->ulBandLow  = uUserSetBand.ulPrefBand & (~TAF_PH_BAND_NEED_CHANGE_TO_64BIT);

    return;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertMsccNetScanCnfToMmaFormat
 ��������  : �յ�MSCC�ظ���NETSCAN����ת���ɸ�AT�ϱ���ʽ
 �������  : MSCC_MMA_NET_SCAN_CNF_STRU *pMsg
 �������  : TAF_MMA_NET_SCAN_CNF_STRU *pstNetScanCnf
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��10��15��
    ��    ��   : w00167002
    �޸�����   : �ɼ��̹淶�޸�
  3.��    ��   : 2015��03��25��
    ��    ��   : K00902809
    �޸�����   : changed according to new structure.
*****************************************************************************/
VOS_VOID TAF_MMA_ConvertMsccNetScanCnfToMmaFormat(
    MSCC_MMA_NET_SCAN_CNF_STRU          *pstMsg,
    TAF_MMA_NET_SCAN_CNF_STRU          *pstNetScanCnf
)
{
    VOS_UINT32                          i;

    /* �����Ϣͷ */
    pstNetScanCnf->ulMsgName                = ID_TAF_MMA_NET_SCAN_CNF;
    pstNetScanCnf->usClientId               = gstMmaValue.stNetScan.usClientId;
    pstNetScanCnf->ucOpId                   = gstMmaValue.stNetScan.ucOpId;

    pstNetScanCnf->enResult    = pstMsg->enResult;
    pstNetScanCnf->ucFreqNum   = pstMsg->ucFreqNum;

    TAF_MMA_ConvertMsccCauseToTafFormat(pstMsg->enCause, &pstNetScanCnf->enCause);

    if ( TAF_MMA_NET_SCAN_MAX_FREQ_NUM < pstNetScanCnf->ucFreqNum )
    {
        pstNetScanCnf->ucFreqNum = TAF_MMA_NET_SCAN_MAX_FREQ_NUM;
    }

    for ( i = 0; i < pstNetScanCnf->ucFreqNum; i++ )
    {
        pstNetScanCnf->astNetScanInfo[i].usArfcn        = pstMsg->astNetScanInfo[i].usArfcn;
        pstNetScanCnf->astNetScanInfo[i].usC1           = pstMsg->astNetScanInfo[i].usC1;
        pstNetScanCnf->astNetScanInfo[i].usC2           = pstMsg->astNetScanInfo[i].usC2;
        pstNetScanCnf->astNetScanInfo[i].usLac          = pstMsg->astNetScanInfo[i].usLac;
        pstNetScanCnf->astNetScanInfo[i].ulMcc          = pstMsg->astNetScanInfo[i].ulMcc;
        pstNetScanCnf->astNetScanInfo[i].ulMnc          = pstMsg->astNetScanInfo[i].ulMnc;
        pstNetScanCnf->astNetScanInfo[i].usBsic         = pstMsg->astNetScanInfo[i].usBsic;
        pstNetScanCnf->astNetScanInfo[i].sRxlev         = pstMsg->astNetScanInfo[i].sRxlev;
        pstNetScanCnf->astNetScanInfo[i].sRssi          = pstMsg->astNetScanInfo[i].sRssi;
        pstNetScanCnf->astNetScanInfo[i].ulCellId       = pstMsg->astNetScanInfo[i].ulCellId;

        TAF_MMA_ConvertMsccBandToTafFormat(&pstMsg->astNetScanInfo[i].stBand,
                                          &pstNetScanCnf->astNetScanInfo[i].stBand);
    }


    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccNetScanCnf_PreProc
 ��������  : �յ�MSCC��������netscan�ظ�
 �������  : MSCC_MMA_NET_SCAN_CNF_STRU *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��03��25��
    ��    ��   : K00902809
    �޸�����   : Including TAF_MMA_SendAtNetScanCnf instead of MN_PH_SendMsg
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccNetScanCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    MSCC_MMA_NET_SCAN_CNF_STRU          *pstMsccNetScanCnf = VOS_NULL_PTR;

    pstMsccNetScanCnf = (MSCC_MMA_NET_SCAN_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

    TAF_MMA_ConvertMsccNetScanCnfToMmaFormat(pstMsccNetScanCnf, &stNetScanCnf);

    if ( MMA_TIMER_RUN == g_stNetScanProtectTimer.ucTimerStatus )
    {
        TAF_MMA_StopNetScanProtectTimer();

        /* ���õ绰�����ϱ����� */
        TAF_MMA_SndNetScanCnf(&stNetScanCnf);
    }
    else if ( MMA_TIMER_RUN == g_stAbortNetScanProtectTimer.ucTimerStatus )
    {
        TAF_MMA_StopAbortNetScanProtectTimer();

        /* ���õ绰�����ϱ����� */
        TAF_MMA_SndNetScanCnf(&stNetScanCnf);
    }
    else
    {
        /* NETSCAN�ı�����ʱ���������У�����Ϊ���쳣�ظ� */
        MMA_WARNINGLOG("TAF_MMA_RcvMsccNetScanCnf: RCV UNEXPECTED NETSCAN CNF MSG!\r\n");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertMsccAbortNetScanCnfToMmaFormat
 ��������  : MMA�յ�MSCC��NETSCAN�ظ�����װ�ɷ��͸�AT����Ϣ��ʽ
 �������  : pstMsg    �յ�MSCC�Ļظ���Ϣ
 �������  : pstNetScanCnf ��ATģ�鷢�͵�����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��03��25��
    ��    ��   : K00902809
    �޸�����   : changed according to new structure.
*****************************************************************************/
VOS_VOID TAF_MMA_ConvertMsccAbortNetScanCnfToMmaFormat(
    MSCC_MMA_ABORT_NET_SCAN_CNF_STRU    *pstMsg,
    TAF_MMA_NET_SCAN_CNF_STRU           *pstNetScanCnf
)
{
    VOS_UINT32                          i;

    pstNetScanCnf->ulMsgName                = ID_TAF_MMA_NET_SCAN_CNF;
    pstNetScanCnf->usClientId               = gstMmaValue.stNetScan.usClientId;
    pstNetScanCnf->ucOpId                   = gstMmaValue.stNetScan.ucOpId;

    pstNetScanCnf->enResult             = TAF_MMA_NET_SCAN_RESULT_SUCCESS;
    pstNetScanCnf->enCause              = TAF_MMA_NET_SCAN_CAUSE_BUTT;
    pstNetScanCnf->ucFreqNum            = pstMsg->ucFreqNum;

    if ( TAF_MMA_NET_SCAN_MAX_FREQ_NUM < pstNetScanCnf->ucFreqNum )
    {
        pstNetScanCnf->ucFreqNum = TAF_MMA_NET_SCAN_MAX_FREQ_NUM;
    }

    for ( i = 0; i < pstNetScanCnf->ucFreqNum; i++ )
    {
        pstNetScanCnf->astNetScanInfo[i].usArfcn        = pstMsg->astNetScanInfo[i].usArfcn;
        pstNetScanCnf->astNetScanInfo[i].usC1           = pstMsg->astNetScanInfo[i].usC1;
        pstNetScanCnf->astNetScanInfo[i].usC2           = pstMsg->astNetScanInfo[i].usC2;
        pstNetScanCnf->astNetScanInfo[i].usLac          = pstMsg->astNetScanInfo[i].usLac;
        pstNetScanCnf->astNetScanInfo[i].ulMcc          = pstMsg->astNetScanInfo[i].ulMcc;
        pstNetScanCnf->astNetScanInfo[i].ulMnc          = pstMsg->astNetScanInfo[i].ulMnc;
        pstNetScanCnf->astNetScanInfo[i].usBsic         = pstMsg->astNetScanInfo[i].usBsic;
        pstNetScanCnf->astNetScanInfo[i].sRxlev         = pstMsg->astNetScanInfo[i].sRxlev;
        pstNetScanCnf->astNetScanInfo[i].sRssi          = pstMsg->astNetScanInfo[i].sRssi;
        pstNetScanCnf->astNetScanInfo[i].ulCellId       = pstMsg->astNetScanInfo[i].ulCellId;

        TAF_MMA_ConvertMsccBandToTafFormat(&pstMsg->astNetScanInfo[i].stBand,
                                          &pstNetScanCnf->astNetScanInfo[i].stBand);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccAbortNetScanCnf_PreProc
 ��������  : �յ�MSCC�������Ĵ��netscan�ظ�
 �������  : MSCC_MMA_NET_SCAN_CNF_STRU *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��03��25��
    ��    ��   : K00902809
    �޸�����   : Including TAF_MMA_SendAtNetScanCnf instead of MN_PH_SendMsg
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccAbortNetScanCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_NET_SCAN_CNF_STRU           stNetScanCnf;
    MSCC_MMA_ABORT_NET_SCAN_CNF_STRU    *pstMsccAbortNetScanCnf = VOS_NULL_PTR;

    pstMsccAbortNetScanCnf = (MSCC_MMA_ABORT_NET_SCAN_CNF_STRU *)pstMsg;

    if ( MMA_TIMER_RUN != g_stAbortNetScanProtectTimer.ucTimerStatus )
    {
        MMA_WARNINGLOG("TAF_MMA_RcvMsccAbortNetScanCnf:abort timer not run!!!\r\n");

        return VOS_TRUE;
    }

    PS_MEM_SET(&stNetScanCnf, 0x00, sizeof(stNetScanCnf));

    /* ��װ��ATģ��ظ���CNF�ṹ */
    TAF_MMA_ConvertMsccAbortNetScanCnfToMmaFormat(pstMsccAbortNetScanCnf, &stNetScanCnf);

    /* ֹͣNETSCAN�ı�����ʱ�� */
    TAF_MMA_StopAbortNetScanProtectTimer();

    /* ���õ绰�����ϱ����� */
    TAF_MMA_SndNetScanCnf(&stNetScanCnf);

    return VOS_TRUE;
}


#if (FEATURE_MULTI_MODEM == FEATURE_ON)

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMtcNcellInfoInd_PreProc
 ��������  : ��������mtc��ID_MTC_MMA_NCELL_INFO_IND��Ϣ
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMtcNcellInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת����mscc */
    TAF_MMA_SndMsccNcellInfoInd(pstMsg);
    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMtcPsTransferInd_PreProc
 ��������  : ��������mtc��ID_MTC_MMA_PS_TRANSFER_IND��Ϣ
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��6��
    ��    ��   : z00161729
    �޸�����   : DTS2014010202583:SVLTE�Ż�G-TL ps�л������޸�

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMtcPsTransferInd_PreProc(
     VOS_UINT32                         ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת����mmc */
    TAF_MMA_SndMsccPsTransferNotify(pstMsg);
    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMtcOtherModemInfoNotify_PreProc
 ��������  : ��������mtc��ID_MTC_MMA_OTHER_MODEM_INFO_NOTIFY��Ϣ
 �������  : ulEventType---�¼�����
             pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��22��
    ��    ��   : z00161729
    �޸�����   : SVLTE�Ż�G-TL ps�л������޸�

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMtcOtherModemInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת����mscc */
    TAF_MMA_SndMsccOtherModemInfoNotify(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMtcOtherModemDplmnNplmnInfoNotify_PreProc
 ��������  : ��������mtc��other modem dplmn nplmn info notify��Ϣ
 �������  : ulEventType---�¼�����
             pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��3��
    ��    ��   : z00161729
    �޸�����   : ��������������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMtcOtherModemDplmnNplmnInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ת����mmc */
    TAF_MMA_SndMsccOtherModemDplmnNplmnInfoNotify(pstMsg);

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccEplmnInfoInd_PreProc
 ��������  : �յ�MSCC ��Чplmn��Ϣ
 �������  : pstEplmnInfoIndMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��25��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����

  2.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccEplmnInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    MSCC_MMA_EPLMN_INFO_IND_STRU        *pstEplmnInfoIndMsg  = VOS_NULL_PTR;

    pstEplmnInfoIndMsg   = (MSCC_MMA_EPLMN_INFO_IND_STRU *)pstMsg;

    TAF_MMA_SndMtcEplmnInfoInd(pstEplmnInfoIndMsg);

#endif
    return VOS_TRUE;
}




/* Added by s00261364 for L-C��������Ŀ, 2014-1-26, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaAcqReq_PreProc
 ��������  : �յ�CMMCAģ���acq req��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��14��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ACQ_REQ_STRU               *pstMmaAcqReqMsg    = VOS_NULL_PTR;
    MSCC_MMA_ACQ_CNF_STRU               stSndMsg;
    VOS_UINT8                           ucCtxIndex;
    VOS_UINT32                          ulRet;

    pstMmaAcqReqMsg = (TAF_MMA_ACQ_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stSndMsg, 0, sizeof(MSCC_MMA_ACQ_CNF_STRU));

    /* ����ǹػ�״̬�����������ڿ��ػ�����ظ��ܾ� */
    if ((TAF_MMA_FSM_PHONE_MODE == TAF_MMA_GetCurrFsmId())
     || (STA_FSM_NULL           == g_StatusContext.ulFsmState)
     || (STA_FSM_STOP           == g_StatusContext.ulFsmState))
    {
        TAF_MMA_SndAcqBestNetworkCnf(&(pstMmaAcqReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_REJECT,
                          &stSndMsg);
        return VOS_TRUE;
    }


    /* �������CLģʽ������CMMCA��Ϣ�����ϱ�CMMCA�ܾ� */
    if ((VOS_FALSE              == TAF_SDC_IsConfigCLInterWorkCOutside())
     && (CMMCA_CLIENT_ID        == pstMmaAcqReqMsg->stCtrl.usClientId))
    {
        TAF_MMA_SndAcqBestNetworkCnf(&(pstMmaAcqReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_REJECT,
                          &stSndMsg);
        return VOS_TRUE;
    }


    /* �������Ч��ֱ�ӻ�ʧ�� */
    if (VOS_FALSE == TAF_SDC_IsUsimStausValid())
    {
        TAF_MMA_SndAcqBestNetworkCnf(&(pstMmaAcqReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          &stSndMsg);
        return VOS_TRUE;
    }

    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_ACQ_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_ACQ_REQ))
    {
        TAF_MMA_SndAcqBestNetworkCnf(&(pstMmaAcqReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          &stSndMsg);
        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndAcqBestNetworkCnf(&(pstMmaAcqReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          &stSndMsg);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstMmaAcqReqMsg->stCtrl,
                       TAF_MMA_OPER_ACQ_REQ, ucCtxIndex);

    /* ��MSCC��acq req��Ϣ */
    ulRet = TAF_MMA_SndMsccAcqReq(&(pstMmaAcqReqMsg->stAcqPara));
    if (VOS_OK != ulRet)
    {
        TAF_MMA_ClearOperCtx(ucCtxIndex);
        return VOS_TRUE;
    }


    /* ����������ʱ��TI_TAF_MMA_WAIT_MSCC_ACQ_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_ACQ_CNF, TI_TAF_MMA_WAIT_MSCC_ACQ_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertAttachDomainToAttachType
 ��������  : ��TAF_PH_SERVICE_DOMAINת��ΪMMAģ���Attach type
 �������  : TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8              ucAttachDomain
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��9��
    ��    ��   : h00313353
    �޸�����   : SysCfg SrvDomainתö��
*****************************************************************************/
TAF_MMA_ATTACH_TYPE_ENUM_UINT8 TAF_MMA_ConvertAttachDomainToAttachType(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8                       enAttachDomain
)
{
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8      enAttachType;

    switch ( enAttachDomain )
    {
        case TAF_MMA_SERVICE_DOMAIN_CS:
            enAttachType = TAF_MMA_ATTACH_TYPE_IMSI;
            break;

        case TAF_MMA_SERVICE_DOMAIN_PS:
            enAttachType = TAF_MMA_ATTACH_TYPE_GPRS;
            break;

        case TAF_MMA_SERVICE_DOMAIN_CS_PS:
        case TAF_MMA_SERVICE_DOMAIN_ANY:
            enAttachType = TAF_MMA_ATTACH_TYPE_GPRS_IMSI;
            break;

        case TAF_MMA_SERVICE_DOMAIN_NOCHANGE:
        default:
            enAttachType = TAF_MMA_ATTACH_TYPE_GPRS;
            break;
    }

    return enAttachType;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccRegReq_PreProc
 ��������  : �յ�CMSCCAģ���reg req��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��14��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaRegReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_REG_REQ_STRU               *pstMmaRegReqMsg = VOS_NULL_PTR;
    MSCC_MMA_REG_CNF_STRU               stSndMsg;
    VOS_UINT8                           ucCtxIndex;
    VOS_UINT32                          ulRet;
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType;
    VOS_UINT8                                               ucOpID;

    pstMmaRegReqMsg = (TAF_MMA_REG_REQ_STRU*)pstMsg;
    PS_MEM_SET(&stSndMsg, 0, sizeof(MSCC_MMA_REG_CNF_STRU));

    /* ����ǹػ�״̬�����������ڿ��ػ�����ظ��ܾ� */
    if ((TAF_MMA_FSM_PHONE_MODE == TAF_MMA_GetCurrFsmId())
     || (STA_FSM_NULL           == g_StatusContext.ulFsmState)
     || (STA_FSM_STOP           == g_StatusContext.ulFsmState))
    {
        TAF_MMA_SndRegCnf(&(pstMmaRegReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_REJECT,
                          &stSndMsg);
        return VOS_TRUE;
    }


    /* �������CLģʽ������CMMCA��Ϣ�����ϱ�CMMCA�ܾ� */
    if ((VOS_FALSE              == TAF_SDC_IsConfigCLInterWorkCOutside())
     && (CMMCA_CLIENT_ID        == pstMmaRegReqMsg->stCtrl.usClientId))
    {
        TAF_MMA_SndRegCnf(&(pstMmaRegReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_REJECT,
                          &stSndMsg);
        return VOS_TRUE;
    }


    /* �������Ч��ֱ�ӻ�ʧ�� */
    if (VOS_FALSE == TAF_SDC_IsUsimStausValid())
    {
        TAF_MMA_SndRegCnf(&(pstMmaRegReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          &stSndMsg);
        return VOS_TRUE;
    }

    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_REG_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_REG_REQ))
    {
        TAF_MMA_SndRegCnf(&(pstMmaRegReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          &stSndMsg);
        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ��  */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndRegCnf(&(pstMmaRegReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          &stSndMsg);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstMmaRegReqMsg->stCtrl,
                       TAF_MMA_OPER_REG_REQ, ucCtxIndex);

    /* ��MSCC��reg req��Ϣ */
    ulRet = TAF_MMA_SndMsccRegReq(&(pstMmaRegReqMsg->stRegPara));
    if (VOS_OK != ulRet)
    {
        TAF_MMA_ClearOperCtx(ucCtxIndex);
        return VOS_TRUE;
    }

    if (TAF_MMA_SERVICE_DOMAIN_NULL == pstMmaRegReqMsg->stRegPara.enAttachDomain)
    {
        TAF_MMA_SndRegCnf(&(pstMmaRegReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          &stSndMsg);

        return VOS_TRUE;
    }

    enAttachType = TAF_MMA_ConvertAttachDomainToAttachType(pstMmaRegReqMsg->stRegPara.enAttachDomain);

    ucOpID = TAF_MMA_GetAttachOpId();

    (VOS_VOID)TAF_MMA_SndMsccAttachReq(ucOpID,
                                       (NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32)enAttachType,
                                       pstMmaRegReqMsg->stRegPara.enEpsAttachReason);

    TAF_MMA_SetAttachAllowFlg(enAttachType);

    /* ����������ʱ��TI_TAF_MMA_WAIT_MSCC_REG_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_REG_CNF, TI_TAF_MMA_WAIT_MSCC_REG_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaPowerSaveReq_PreProc
 ��������  : �յ�CMMCAģ���power save req��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��14��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaPowerSaveReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_POWER_SAVE_REQ_STRU        *pstMmaPowerSaveReqMsg  = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;
    VOS_UINT32                          ulRet;

    pstMmaPowerSaveReqMsg  = (TAF_MMA_POWER_SAVE_REQ_STRU*)pstMsg;

    /* ����ǿ��ػ������У�ֱ�ӻظ��ܾ� */
    if (TAF_MMA_FSM_PHONE_MODE == TAF_MMA_GetCurrFsmId())
    {
        TAF_MMA_SndPowerSaveCnf(&(pstMmaPowerSaveReqMsg->stCtrl),
                                TAF_MMA_APP_OPER_RESULT_REJECT);
        return VOS_TRUE;
    }


    /* �������CLģʽ������CMMCA��Ϣ�����ϱ�CMMCA�ܾ� */
    if ((VOS_FALSE             == TAF_SDC_IsConfigCLInterWorkCOutside())
     && (CMMCA_CLIENT_ID       == pstMmaPowerSaveReqMsg->stCtrl.usClientId))
    {
        TAF_MMA_SndPowerSaveCnf(&(pstMmaPowerSaveReqMsg->stCtrl),
                                TAF_MMA_APP_OPER_RESULT_REJECT);
        return VOS_TRUE;
    }


    /* ����Ѿ��ػ���ֱ�ӻظ��ɹ� */
    if ((STA_FSM_NULL    == g_StatusContext.ulFsmState)
     || (STA_FSM_STOP    == g_StatusContext.ulFsmState))
    {
        TAF_MMA_SndPowerSaveCnf(&(pstMmaPowerSaveReqMsg->stCtrl),
                                TAF_MMA_APP_OPER_RESULT_SUCCESS);
        return VOS_TRUE;
    }

    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_POWER_SAVE_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_POWER_SAVE_REQ))
    {
        TAF_MMA_SndPowerSaveCnf(&(pstMmaPowerSaveReqMsg->stCtrl),
                                TAF_MMA_APP_OPER_RESULT_FAILURE);
        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ��  */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPowerSaveCnf(&(pstMmaPowerSaveReqMsg->stCtrl),
                                TAF_MMA_APP_OPER_RESULT_FAILURE);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstMmaPowerSaveReqMsg->stCtrl,
                       TAF_MMA_OPER_POWER_SAVE_REQ, ucCtxIndex);

    /* ��MSCC��power save req��Ϣ */
    ulRet = TAF_MMA_SndMsccPowerSaveReq(&(pstMmaPowerSaveReqMsg->stPowerSavePara));
    if (VOS_OK != ulRet)
    {
        TAF_MMA_ClearOperCtx(ucCtxIndex);

        return VOS_TRUE;
    }

    /* ����������ʱ��TI_TAF_MMA_WAIT_MSCC_POWER_SAVE_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_POWER_SAVE_CNF,
                       TI_TAF_MMA_WAIT_MSCC_POWER_SAVE_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccAcqCnf_PreProc
 ��������  : �յ�MSCCģ���acq cnf��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��14��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_ACQ_CNF_STRU               *pstMsccMmaAcqCnf = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;

    pstMsccMmaAcqCnf = (MSCC_MMA_ACQ_CNF_STRU *)pstMsg;
    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();
    enRslt          = TAF_MMA_APP_OPER_RESULT_SUCCESS;

    if (NAS_MSCC_PIF_ACQ_RESULT_SUCCESS != pstMsccMmaAcqCnf->enAcqRslt)
    {
        enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
    }

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_ACQ_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_ACQ_REQ, &ucCtxIndex))
    {
        /*  �ظ�MMA_ACQ_CNF */
        TAF_MMA_SndAcqBestNetworkCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                          enRslt,
                          pstMsccMmaAcqCnf);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_ACQ_CNF);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccAcqInd_PreProc
 ��������  : �յ�MSCCģ���acq ind��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��14��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccAcqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_ACQ_IND_STRU               *pstMsccMmaAcqInd = VOS_NULL_PTR;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;

    pstMsccMmaAcqInd = (MSCC_MMA_ACQ_IND_STRU *)pstMsg;
    enRslt          = TAF_MMA_APP_OPER_RESULT_SUCCESS;

    if (NAS_MSCC_PIF_ACQ_RESULT_SUCCESS != pstMsccMmaAcqInd->enAcqRslt)
    {
        enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
    }

    /* �ظ�MMA_ACQ_IND */
    TAF_MMA_SndAcqInd(enRslt, pstMsccMmaAcqInd);

    return VOS_TRUE;
}
#endif




/*****************************************************************************
 �� �� ��  : TAF_MMA_SndEndSessionNotifyAccordingSrvType
 ��������  : ����ҵ�����ͷ���end session�ͷ���Դ��
             ���ڶ�ҵ�񲢷�����Ҫ���Ͷ���end session���
 �������  : pstSrvType - ҵ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��30��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndEndSessionNotifyAccordingSrvType(
    TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION                 *pstSrvType
)
{
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU                       stMsccRatList;
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU                           *pstMmaRatListAddr = VOS_NULL_PTR;
    VOS_UINT32                                               i;

    pstMmaRatListAddr = TAF_MMA_GetSrvAcqRatListAddr();

    stMsccRatList.ucRatNum = pstMmaRatListAddr->ucRatNum;

    for (i = 0; i < PS_MIN(pstMmaRatListAddr->ucRatNum, TAF_MMA_SRV_ACQ_RAT_NUM_MAX); i++)
    {
        stMsccRatList.aenRatType[i] = pstMmaRatListAddr->aenRatType[i];
    }

    /* ����֮ǰ�ļ�¼��ҵ�����ͷ���end session�ͷ���Դ,
          ���ڶ�ҵ�񲢷���Ҫ������end session��Ϣ���  */
    if (VOS_TRUE == pstSrvType->stTrigPlmnSearchSrvType.usCsMoNormalCall)
    {
        TAF_MMA_SndMsccEndSessionNotify(NAS_MSCC_PIF_SRV_TYPE_CS_MO_NORMAL_CALL, &stMsccRatList);
        pstSrvType->stTrigPlmnSearchSrvType.usCsMoNormalCall = VOS_FALSE;
    }

    if (VOS_TRUE == pstSrvType->stTrigPlmnSearchSrvType.usCsMoEmgCall)
    {
        TAF_MMA_SndMsccEndSessionNotify(NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL, &stMsccRatList);
        pstSrvType->stTrigPlmnSearchSrvType.usCsMoEmgCall = VOS_FALSE;
    }

    if (VOS_TRUE == pstSrvType->stTrigPlmnSearchSrvType.usCsMoSs)
    {
        TAF_MMA_SndMsccEndSessionNotify(NAS_MSCC_PIF_SRV_TYPE_CS_MO_SS, &stMsccRatList);
        pstSrvType->stTrigPlmnSearchSrvType.usCsMoSs = VOS_FALSE;
    }

    if (VOS_TRUE == pstSrvType->stTrigPlmnSearchSrvType.usCsMoSms)
    {
        TAF_MMA_SndMsccEndSessionNotify(NAS_MSCC_PIF_SRV_TYPE_CS_MO_SMS, &stMsccRatList);
        pstSrvType->stTrigPlmnSearchSrvType.usCsMoSms = VOS_FALSE;
    }

    if (VOS_TRUE == pstSrvType->stTrigPlmnSearchSrvType.usPsBackGroundCall)
    {
        TAF_MMA_SndMsccEndSessionNotify(NAS_MSCC_PIF_SRV_TYPE_PS_BACKGROUND_CALL, &stMsccRatList);
        pstSrvType->stTrigPlmnSearchSrvType.usPsBackGroundCall = VOS_FALSE;
    }

    if (VOS_TRUE == pstSrvType->stTrigPlmnSearchSrvType.usPsConversatCall)
    {
        TAF_MMA_SndMsccEndSessionNotify(NAS_MSCC_PIF_SRV_TYPE_PS_CONVERSAT_CALL, &stMsccRatList);
        pstSrvType->stTrigPlmnSearchSrvType.usPsConversatCall = VOS_FALSE;
    }

    if (VOS_TRUE == pstSrvType->stTrigPlmnSearchSrvType.usPsInteractCall)
    {
        TAF_MMA_SndMsccEndSessionNotify(NAS_MSCC_PIF_SRV_TYPE_PS_INTERACT_CALL, &stMsccRatList);
        pstSrvType->stTrigPlmnSearchSrvType.usPsInteractCall = VOS_FALSE;
    }

    if (VOS_TRUE == pstSrvType->stTrigPlmnSearchSrvType.usPsStreamCall)
    {
        TAF_MMA_SndMsccEndSessionNotify(NAS_MSCC_PIF_SRV_TYPE_PS_STREAM_CALL, &stMsccRatList);
        pstSrvType->stTrigPlmnSearchSrvType.usPsStreamCall = VOS_FALSE;
    }

    if (VOS_TRUE == pstSrvType->stTrigPlmnSearchSrvType.usPsSubscribTrafficCall)
    {
        TAF_MMA_SndMsccEndSessionNotify(NAS_MSCC_PIF_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, &stMsccRatList);
        pstSrvType->stTrigPlmnSearchSrvType.usPsSubscribTrafficCall = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertSrvTypeToMscc
 ��������  : ��spm��mma�ӿ�ҵ������ת��Ϊmma��mscc�ӿ�ҵ������
 �������  : enMmaSrvType     - TAF MMA�ӿ�ҵ������
 �������  : pucMsccSrvType    - MMA MSCC�ӿ�ҵ������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ConvertSrvTypeToMscc(
    TAF_MMA_SRV_TYPE_ENUM_UINT8              enMmaSrvType,
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8        *pucMsccSrvType
)
{
    switch (enMmaSrvType)
    {
        case TAF_MMA_SRV_TYPE_CS_MO_NORMAL_CALL:
            *pucMsccSrvType = NAS_MSCC_PIF_SRV_TYPE_CS_MO_NORMAL_CALL;
            break;

        case TAF_MMA_SRV_TYPE_CS_MO_SS:
            *pucMsccSrvType = NAS_MSCC_PIF_SRV_TYPE_CS_MO_SS;
            break;

        case TAF_MMA_SRV_TYPE_CS_MO_SMS:
            *pucMsccSrvType = NAS_MSCC_PIF_SRV_TYPE_CS_MO_SMS;
            break;

        case TAF_MMA_SRV_TYPE_CS_MO_EMERGENCY_CALL:
            *pucMsccSrvType = NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL;
            break;

        case TAF_MMA_SRV_TYPE_PS_CONVERSAT_CALL:
            *pucMsccSrvType = NAS_MSCC_PIF_SRV_TYPE_PS_CONVERSAT_CALL;
            break;

        case TAF_MMA_SRV_TYPE_PS_STREAM_CALL:
            *pucMsccSrvType = NAS_MSCC_PIF_SRV_TYPE_PS_STREAM_CALL;
            break;

        case TAF_MMA_SRV_TYPE_PS_INTERACT_CALL:
            *pucMsccSrvType = NAS_MSCC_PIF_SRV_TYPE_PS_INTERACT_CALL;
            break;

        case TAF_MMA_SRV_TYPE_PS_BACKGROUND_CALL:
            *pucMsccSrvType = NAS_MSCC_PIF_SRV_TYPE_PS_BACKGROUND_CALL;
            break;

        case TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL:
            *pucMsccSrvType = NAS_MSCC_PIF_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL;
            break;

        default:
            *pucMsccSrvType = NAS_MSCC_PIF_SRV_TYPE_BUTT;
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_UpdateTrigPlmnSearchSrvType
 ��������  : ����ҵ�񴥷�����ʱҵ������
 �������  : enSrvType - ҵ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��21��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_SDC_UpdateTrigPlmnSearchSrvType(
    TAF_MMA_SRV_TYPE_ENUM_UINT8         enSrvType
)
{
    TAF_SDC_TRIG_PLMN_SEARCH_SRV_TYPE_UNION                 *pstTrigPlmnSrcSrvType = VOS_NULL_PTR;

    pstTrigPlmnSrcSrvType = TAF_SDC_GetTrigPlmnSearchSrvType();

    switch (enSrvType)
    {
        case TAF_MMA_SRV_TYPE_CS_MO_NORMAL_CALL:
            pstTrigPlmnSrcSrvType->stTrigPlmnSearchSrvType.usCsMoNormalCall = VOS_TRUE;
            break;

        case TAF_MMA_SRV_TYPE_CS_MO_EMERGENCY_CALL:
            pstTrigPlmnSrcSrvType->stTrigPlmnSearchSrvType.usCsMoEmgCall = VOS_TRUE;
            break;

        case TAF_MMA_SRV_TYPE_CS_MO_SS:
            pstTrigPlmnSrcSrvType->stTrigPlmnSearchSrvType.usCsMoSs = VOS_TRUE;
            break;

        case TAF_MMA_SRV_TYPE_CS_MO_SMS:
            pstTrigPlmnSrcSrvType->stTrigPlmnSearchSrvType.usCsMoSms = VOS_TRUE;
            break;

        case TAF_MMA_SRV_TYPE_PS_CONVERSAT_CALL:
            pstTrigPlmnSrcSrvType->stTrigPlmnSearchSrvType.usPsConversatCall = VOS_TRUE;
            break;

        case TAF_MMA_SRV_TYPE_PS_STREAM_CALL:
            pstTrigPlmnSrcSrvType->stTrigPlmnSearchSrvType.usPsStreamCall = VOS_TRUE;
            break;

        case TAF_MMA_SRV_TYPE_PS_INTERACT_CALL:
            pstTrigPlmnSrcSrvType->stTrigPlmnSearchSrvType.usPsInteractCall = VOS_TRUE;
            break;

        case TAF_MMA_SRV_TYPE_PS_BACKGROUND_CALL:
            pstTrigPlmnSrcSrvType->stTrigPlmnSearchSrvType.usPsBackGroundCall = VOS_TRUE;
            break;

        case TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL:
            pstTrigPlmnSrcSrvType->stTrigPlmnSearchSrvType.usPsSubscribTrafficCall = VOS_TRUE;
            break;

        default:
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafSrvAcqReq_PreProc
 ��������  : �յ�TAF SPMģ���srv acq req��Ϣ
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��21��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafSrvAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SRV_ACQ_REQ_STRU                               *pstTafSrvAcqReq = VOS_NULL_PTR;
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8                        enMmaMsccSrvType;
    TAF_MMA_TIMER_STATUS_ENUM_UINT8                         enWaitSrvAcqCnfTimerStatus;
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU                      stMsccRatList;
    VOS_UINT32                                              i;

    PS_MEM_SET(&stMsccRatList, 0, sizeof(NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU));

    pstTafSrvAcqReq            = (TAF_MMA_SRV_ACQ_REQ_STRU *)pstMsg;
    enWaitSrvAcqCnfTimerStatus = TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF);

    if (TAF_MMA_SRV_TYPE_BUTT == pstTafSrvAcqReq->enSrvType)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTafSrvAcqReq_PreProc:invalid para!");
        return VOS_TRUE;
    }

    /* �������ҵ�񴥷�������mma����¼������begin session���� */
    TAF_SDC_UpdateTrigPlmnSearchSrvType(pstTafSrvAcqReq->enSrvType);

    TAF_MMA_ConvertSrvTypeToMscc(pstTafSrvAcqReq->enSrvType, &enMmaMsccSrvType);

    /* �������ҵ�񴥷�������mma����¼������begin session���󣬲���Ҫ��mscc�ٷ�srv req���� */
    if (TAF_MMA_TIMER_STATUS_RUNING == enWaitSrvAcqCnfTimerStatus)
    {
        return VOS_TRUE;
    }

    stMsccRatList.ucRatNum = pstTafSrvAcqReq->stRatList.ucRatNum;

    for (i = 0; i < PS_MIN(pstTafSrvAcqReq->stRatList.ucRatNum, TAF_MMA_SRV_ACQ_RAT_NUM_MAX); i++)
    {
        stMsccRatList.aenRatType[i] = pstTafSrvAcqReq->stRatList.aenRatType[i];
    }

    TAF_MMA_SndMsccBeginSessionNotify(enMmaMsccSrvType, &stMsccRatList);

    /* ֪ͨmsccҵ�����ʹ������� */
    TAF_MMA_SndMsccSrvAcqReq(enMmaMsccSrvType, &stMsccRatList);

    TAF_MMA_UpdateSrvAcqRatList(&(pstTafSrvAcqReq->stRatList));


    /* ����������ʱ�� */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF, TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccSrvAcqCnf_PreProc
 ��������  : �յ�mscc��srv acq cnf��Ϣ
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��21��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccSrvAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_SRV_ACQ_CNF_STRU           *pstSrvAcqCnf = VOS_NULL_PTR;

    pstSrvAcqCnf = (MSCC_MMA_SRV_ACQ_CNF_STRU *)pstMsg;

    if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF))
    {
        /* ֹͣ������ʱ�� */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF);

        /* ����֮ǰ�ļ�¼��ҵ�����ͷ���end session�ͷ���Դ,
           ���ڶ�ҵ�񲢷���Ҫ������end session��Ϣ���  */
        TAF_MMA_SndEndSessionNotifyAccordingSrvType(TAF_SDC_GetTrigPlmnSearchSrvType());

        /* ��������SRV ACQ RAT LIST */
        TAF_MMA_ClearSrvAcqRatList();

        TAF_MMA_SndSrvAcqCnf(pstSrvAcqCnf->enResult);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccSrvAcqCnfExpired_PreProc
 ��������  : ��mscc�ظ�srv acq cnf��Ϣ��ʱ�Ĵ���
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��21��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccSrvAcqCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����֮ǰ�ļ�¼��ҵ�����ͷ���end session�ͷ���Դ,
       ���ڶ�ҵ�񲢷���Ҫ������end session��Ϣ���  */
    TAF_MMA_SndEndSessionNotifyAccordingSrvType(TAF_SDC_GetTrigPlmnSearchSrvType());

    /* ��������SRV ACQ RAT LIST */
    TAF_MMA_ClearSrvAcqRatList();

    /* ��spm�ظ� ID_TAF_MMA_SRV_ACQ_CNF����ʧ����Ϣ */
    TAF_MMA_SndSrvAcqCnf(TAF_MMA_SRV_ACQ_RESULT_FAIL);
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAtPlmnList_PreProc
 ��������  : �յ�AT��at+cops=?�б����������Ԥ����
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ҫ��һ������
             VOS_FALSE:��Ҫ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��21��
    ��    ��   : z00161729
    �޸�����   : ��������
  2.��    ��   : 2014��7��24��
    ��    ��   : b00269685
    �޸�����   : coverify����
  3.��    ��   : 2015��4��22��
    ��    ��   : b00269685
    �޸�����   : �б����ϱ�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAtPlmnList_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enWaitSrvAcqCnfTimerStatus;
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_REQ_STRU         *pstRcvMsg          = VOS_NULL_PTR;

    pstRcvMsg = (TAF_MMA_PLMN_LIST_REQ_STRU *)pstMsg;

    pstPlmnListCnfPara = (TAF_MMA_PLMN_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));
    if (NULL == pstPlmnListCnfPara)
    {
        return VOS_TRUE;
    }

    PS_MEM_SET(pstPlmnListCnfPara, 0x0, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    enWaitSrvAcqCnfTimerStatus = TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF);

    /* �����ǰno rf״̬�Ҵ���ҵ�񴥷���������ֱ�ӻظ�ʧ�� */
    if (TAF_MMA_TIMER_STATUS_RUNING == enWaitSrvAcqCnfTimerStatus)
    {
        /* ֱ�ӻظ�plmn listʧ�� */
        pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
        pstPlmnListCnfPara->enPhoneError = TAF_ERR_NO_RF;
        TAF_MMA_SndPlmnListCnf(&(pstRcvMsg->stCtrl), pstPlmnListCnfPara);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);
#endif

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsSysCfgAllowedInCallExist
 ��������  : �����ǰ���ں��г����£��յ�AT��syscfg������
 �������  : pstReqRatOrder -- �û������RAT order
 �������  : pulErrCode     -- �����������
 �� �� ֵ  : VOS_TRUE:����Ҫ��һ������
             VOS_FALSE:��Ҫ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��15��
    ��    ��   : y00245242
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsSysCfgAllowedInCallExist(
    TAF_MMA_RAT_ORDER_STRU             *pstReqRatOrder,
    TAF_ERROR_CODE_ENUM_UINT32         *pulErrCode
)
{
    VOS_UINT8                                               ucImsCallFlag;
    VOS_UINT8                                               ucCsCallFlag;
    TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8                        enRatChangeType;
    TAF_MMA_RAT_ORDER_STRU                                 *pstLastRatOder  = VOS_NULL_PTR;

    *pulErrCode = TAF_ERR_NO_ERROR;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /***********************************************************************************************
     * �ڽ������غ�ģʽ�ܾ�sys cfg����
     **********************************************************************************************/
    if (VOS_TRUE == TAF_SDC_Get1xSysInfo()->ucIsEmcCallExistFlg)
    {
        *pulErrCode = TAF_ERR_ERROR;

        return VOS_FALSE;
    }
#endif

    /***********************************************************************************************
     * �����ǰ��CL<-->GULģʽ֮���ת������, ����������SYS CFG
     **********************************************************************************************/
    pstLastRatOder = &(TAF_MMA_GetLastSyscfgSetAddr()->stRatPrioList);

    enRatChangeType = TAF_MMA_GetRatModeChangeType(pstReqRatOrder, pstLastRatOder);

    if ((TAF_MMA_RAT_MODE_CL_TO_GUL == enRatChangeType)
     || (TAF_MMA_RAT_MODE_GUL_TO_CL == enRatChangeType))
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        /***********************************************************************************************
         * ��ǰ���ں��У��Ҳ����޷���״̬���ܾ�SYS CFG����
         **********************************************************************************************/
        if (VOS_TRUE == TAF_SDC_GetCsCallExistFlg())
        {
            if (TAF_SDC_REPORT_SRVSTA_NO_SERVICE != TAF_SDC_GetServiceStatus())
            {
               *pulErrCode = TAF_ERR_ERROR;

                return VOS_FALSE;
            }
        }
#endif

#if (FEATURE_ON == FEATURE_DSDS)
        /* ���ҵ�񴥷�������ʱ�������У�ֹͣ�ö�ʱ������֪ͨTAFҵ�񴥷�����ʧ�ܣ��ͷŵ�ǰ��ҵ�� */
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF))
        {
            TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF);

            /* ����֮ǰ�ļ�¼��ҵ�����ͷ���end session�ͷ���Դ,
               ���ڶ�ҵ�񲢷���Ҫ������end session��Ϣ���  */
            TAF_MMA_SndEndSessionNotifyAccordingSrvType(TAF_SDC_GetTrigPlmnSearchSrvType());

            /* ��������SRV ACQ RAT LIST */
            TAF_MMA_ClearSrvAcqRatList();

            TAF_MMA_SndSrvAcqCnf(TAF_MMA_SRV_ACQ_RESULT_FAIL);
        }
#endif

        return VOS_TRUE;
    }

    /***********************************************************************************************
     * �����ǰ��GUL<-->GUL��CL<-->CLģʽ֮����л�, ���ҵ�񴥷�����״̬�������У���ܾ�SYS CFG
     **********************************************************************************************/
#if (FEATURE_ON == FEATURE_DSDS)
    /* �����ǰno rf״̬�Ҵ���ҵ�񴥷���������ֱ�ӻظ�ʧ�� */
    if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF))
    {
        *pulErrCode = TAF_ERR_NO_RF;

        return VOS_FALSE;
    }
#endif

    /***********************************************************************************************
     * �����ǰ��CL<-->CLģʽ֮����л�, �к��д��ڣ���ܾ�����
     **********************************************************************************************/
    ucImsCallFlag = TAF_SDC_GetImsCallExistFlg();
    ucCsCallFlag  = TAF_SDC_GetCsCallExistFlg();

    if (((VOS_TRUE == ucCsCallFlag) && (TAF_MMA_RAT_MODE_CL_TO_CL == enRatChangeType))
      || (VOS_TRUE == ucImsCallFlag))
    {
        *pulErrCode = TAF_ERR_SYSCFG_CS_SERV_EXIST;

        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvSysCfgSetReq_PreProc
 ��������  : �յ�AT��syscfg�����Ԥ����
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ҫ��һ������
             VOS_FALSE:��Ҫ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��21��
    ��    ��   : z00161729
    �޸�����   : ��������
  2.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                 �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSysCfgSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SYS_CFG_REQ_STRU           *pstSysCfgReq = VOS_NULL_PTR;
    TAF_ERROR_CODE_ENUM_UINT32          ulErrCode;


    pstSysCfgReq               = (TAF_MMA_SYS_CFG_REQ_STRU *)pstMsg;

    /* ����״̬����Ҫ���ж�ͨ�� */
    if ((STA_FSM_NULL != g_StatusContext.ulFsmState)
     && (STA_FSM_STOP != g_StatusContext.ulFsmState))
    {
        /* C+Lģʽ����ʱ��AT������SYSCFG���ã���ظ�ʧ��,���б���  */
        if ((VOS_TRUE        == TAF_MMA_IsPowerOnCLInterWork())
         && (CMMCA_CLIENT_ID != pstSysCfgReq->stCtrl.usClientId))
        {
            TAF_MMA_SndSysCfgSetCnf(&pstSysCfgReq->stCtrl, TAF_ERR_ERROR);

            return VOS_TRUE;
        }

        /* ����C+Lģʽ����ʱ��CMMCA������SYSCFG���ã���ظ�ʧ��,���б���  */
        if ((VOS_FALSE       == TAF_MMA_IsPowerOnCLInterWork())
         && (CMMCA_CLIENT_ID == pstSysCfgReq->stCtrl.usClientId))
        {
            TAF_MMA_SndSysCfgSetCnf(&pstSysCfgReq->stCtrl, TAF_ERR_ERROR);

            return VOS_TRUE;
        }
    }

    /* �ж��û����õĲ����Ƿ���Ч */
    if (VOS_FALSE == TAF_MMA_IsUserSettedSysCfgParaValid(&(pstSysCfgReq->stSysCfgPara)))
    {
        TAF_MMA_SndSysCfgSetCnf(&pstSysCfgReq->stCtrl, TAF_ERR_PARA_ERROR);

        return VOS_TRUE;
    }

    if (VOS_FALSE == TAF_MMA_IsSysCfgAllowedInCallExist(&(pstSysCfgReq->stSysCfgPara.stRatOrder), &ulErrCode))
    {
        TAF_MMA_SndSysCfgSetCnf(&pstSysCfgReq->stCtrl, ulErrCode);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccRegCnf_PreProc
 ��������  : �յ�MSCCģ���reg cnf��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��14��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccRegCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_REG_CNF_STRU               *pstMsccMmaRegCnf = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;

    pstMsccMmaRegCnf = (MSCC_MMA_REG_CNF_STRU *)pstMsg;
    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    switch (pstMsccMmaRegCnf->enRegRslt)
    {
        case NAS_MSCC_PIF_REG_RESULT_SUCCESS:
            enRslt = TAF_MMA_APP_OPER_RESULT_SUCCESS;
            break;

        case NAS_MSCC_PIF_REG_RESULT_ACQ_FAILURE:
            enRslt = TAF_MMA_APP_OPER_RESULT_ACQUIRED_FAIL;
            break;

        case NAS_MSCC_PIF_REG_RESULT_REG_FAILURE:
            enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
            break;

        default:
            enRslt = TAF_MMA_APP_OPER_RESULT_ACQUIRED_FAIL;
            break;
    }

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_REG_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_REG_REQ, &ucCtxIndex))
    {

        /*  �ظ�MMA_REG_CNF */
        TAF_MMA_SndRegCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                          enRslt,
                          pstMsccMmaRegCnf);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_REG_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccPowerSaveCnf_PreProc
 ��������  : �յ�MSCCģ���power save cnf��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��14��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ


*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccPowerSaveCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    TAF_MMA_CTRL_STRU                   stCtrlInfo;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_ACQ_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE != TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_POWER_SAVE_REQ, &ucCtxIndex))
    {
        MMA_WARNINGLOG("TAF_MMA_RcvMsccPowerSaveCnf_PreProc:NOT FIND TAF_MMA_OPER_POWER_SAVE_REQ!");

        TAF_MMA_BuildMmaCtrlInfo(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stCtrlInfo);
        TAF_MMA_SndPowerSaveCnf(&stCtrlInfo,
                                TAF_MMA_APP_OPER_RESULT_SUCCESS);

        return VOS_TRUE;
    }

    /* �ظ�MMA_POWER_SAVE_CNF */
    TAF_MMA_SndPowerSaveCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                            TAF_MMA_APP_OPER_RESULT_SUCCESS);

    TAF_MMA_ClearOperCtx(ucCtxIndex);

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_POWER_SAVE_CNF);

    return VOS_TRUE;
}

/* Added by s00261364 for L-C��������Ŀ, 2014-1-26, end */

/* Added by b00269685 for L-C��������Ŀ, 2014-3-4, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccAcqCnfExpired_PreProc
 ��������  : �ȴ�MSCCģ���acq cnf��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��4��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccAcqCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    MSCC_MMA_ACQ_CNF_STRU                stSndMsg;
    VOS_UINT8                           ucCtxIndex;

    PS_MEM_SET(&stSndMsg, 0, sizeof(MSCC_MMA_ACQ_CNF_STRU));
    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    stSndMsg.stPlmnId.ulMcc = MMA_INVALID_MCC;
    stSndMsg.stPlmnId.ulMnc = MMA_INVALID_MNC;

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_ACQ_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_ACQ_REQ, &ucCtxIndex))
    {
        /*  �ظ�MMA_ACQ_CNF */
        TAF_MMA_SndAcqBestNetworkCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          &stSndMsg);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccRegCnfExpired_PreProc
 ��������  : �ȴ�MSCCģ���reg cnf��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��4��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccRegCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    MSCC_MMA_REG_CNF_STRU                stSndMsg;
    VOS_UINT8                           ucCtxIndex;

    PS_MEM_SET(&stSndMsg, 0, sizeof(MSCC_MMA_REG_CNF_STRU));
    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    stSndMsg.stPlmnId.ulMcc = MMA_INVALID_MCC;
    stSndMsg.stPlmnId.ulMnc = MMA_INVALID_MNC;

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_REG_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_REG_REQ, &ucCtxIndex))
    {
        /*  �ظ�MMA_REG_CNF */
        TAF_MMA_SndRegCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                          TAF_MMA_APP_OPER_RESULT_ACQUIRED_FAIL,
                          &stSndMsg);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccPowerSaveExpired_PreProc
 ��������  : �ȴ�MSCCģ���powersave cnf��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��4��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccPowerSaveExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_POWER_SAVE_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_POWER_SAVE_REQ, &ucCtxIndex))
    {
        /*  �ظ�MMA_POWER_SAVE_CNF */
        TAF_MMA_SndPowerSaveCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE);

        TAF_MMA_ClearOperCtx(ucCtxIndex);

    }

    return VOS_TRUE;

}
/* Added by b00269685 for L-C��������Ŀ, 2014-3-4, end */

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvDelayReportServiceStatusExpired_PreProc
 ��������  : TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2015��02��11��
  ��    ��   : l00305157
  �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDelayReportServiceStatusExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enCsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enPsRegStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;

    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enAppCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enAppPsServiceStatus;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enRptSrvSta;

    /* �����no rf��־����ֱ�Ӳ����� */
#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        /*NO RF �ؿ���ʱ��*/
        TAF_MMA_StartTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS, (TAF_MMA_GetDelayReportServiceStatusCfgTimerLen()));

        return VOS_TRUE;
    }
#endif

    /*��ȡ����״̬*/
    enRptSrvSta                      = TAF_SDC_GetServiceStatus();

    enCsRegStatus                       = TAF_SDC_GetCsRegStatus();
    enPsRegStatus                       = TAF_SDC_GetPsRegStatus();
    enCsServiceStatus                   = TAF_SDC_GetCsServiceStatus();
    enPsServiceStatus                   = TAF_SDC_GetPsServiceStatus();

    enAppCsServiceStatus                = TAF_SDC_GetAppCsServiceStatus();
    enAppPsServiceStatus                = TAF_SDC_GetAppPsServiceStatus();

    /* ����״̬�ı�,�ϱ�����״̬*/
    if ((enCsServiceStatus    != enAppCsServiceStatus)
     || (enPsServiceStatus    != enAppPsServiceStatus))
    {
        TAF_MMA_ProcServiceStatusReport(enRptSrvSta, TAF_SDC_GetAppServiceStatus());
    }

    /* ע��״̬�ı�,�ϱ�ע��״̬*/
    TAF_MMA_ReportRegStatus(enCsRegStatus, NAS_MSCC_PIF_SRVDOMAIN_CS);

    TAF_MMA_ReportRegStatus(enPsRegStatus, NAS_MSCC_PIF_SRVDOMAIN_PS);

    /* ���ڲ��ķ���״̬��ע��״̬���µ�APPNetworkInfo�� */
    TAF_MMA_UpdateAppNetworkInfo();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvDelayReportCLNoServiceExpired_PreProc
 ��������  : TI_TAF_MMA_DELAY_RPT_CL_NO_SERVICE��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ    :

  1.��    ��   : 2016��1��7��
    ��    ��   : h00313353
    �޸�����   : DTS2016010508602
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDelayReportCLNoServiceExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8          enSubMode;
    TAF_SDC_SYS_MODE_ENUM_UINT8             enOldSysMode;
    pTafSdcSysmodServiceRegStaUpdateFunc    pFuncTafSdcSysmodServiceRegStaUpdate;
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32   enNetworkExist;
    MMA_TAF_CL_STATUS_ENUM_UINT32           enDelayType;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8          enOldSubMode;

    enOldSubMode                            = TAF_SDC_GetSysSubMode();
#endif
    enSysMode                               = TAF_SDC_SYS_MODE_BUTT;
    enSubMode                               = TAF_SDC_SYS_SUBMODE_BUTT;
    enNetworkExist                          = TAF_SDC_NETWORK_BUT;
    enOldSysMode                            = TAF_SDC_GetSysMode();
    pFuncTafSdcSysmodServiceRegStaUpdate    = VOS_NULL_PTR;
    enDelayType                             = MMA_TAF_CL_STATUS_DO_LTE_NO_SERVICE;

    /* ����״̬��ʱ��ά�ɲ� */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

    if (TAF_MMA_DELAY_CL_REPORT_TYPE_DO == TAF_MMA_GetCLNoServiceDelayRptInfo()->enDelayType)
    {
        enDelayType = MMA_TAF_CL_STATUS_DO_NO_SERVICE;
    }

    TAF_MMA_GetCLNoServiceDelayRptInfo()->enDelayType   = TAF_MMA_DELAY_CL_REPORT_TYPE_BUTT;

    if ((TAF_SDC_SYS_MODE_LTE == enOldSysMode)
     || (TAF_SDC_SYS_MODE_SVLTE == enOldSysMode))
    {
        enNetworkExist = TAF_SDC_LTE_NETWORK_NOT_EXIST;
    }
    else
    {
        enNetworkExist = TAF_SDC_HRPD_NETWORK_NOT_EXIST;
    }

    TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(enNetworkExist, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);
    Mma_ModeChgReport(enSysMode, enSubMode);

    TAF_SDC_SetSysMode(enSysMode);
    TAF_SDC_SetSysSubMode(enSubMode);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* LTE���� */
        if (TAF_SDC_LTE_NETWORK_NOT_EXIST == enNetworkExist)
        {
            TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeLte(enNetworkExist);

            TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());
        }

        /* EHRPD���� */
        if (TAF_SDC_HRPD_NETWORK_NOT_EXIST == enNetworkExist)
        {
            if (TAF_SDC_SYS_SUBMODE_EHRPD == enOldSubMode)
            {
                TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeHrpd(enNetworkExist);

                TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());
            }
        }
    }
#endif

    TAF_MMA_SndTafCLServiceStatusInd(enDelayType, VOS_FALSE);

    /* ����״̬��ʱ��ά�ɲ� */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvDelayReportDONoServiceExpired_PreProc
 ��������  : TI_TAF_MMA_DELAY_RPT_DO_NO_SERVICE��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ    :

  1.��    ��   : 2016��1��7��
    ��    ��   : h00313353
    �޸�����   : DTS2016010508602
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDelayReportDONoServiceExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8          enSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc    pFuncTafSdcSysmodServiceRegStaUpdate;
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32   enNetworkExist;
    MMA_TAF_CL_STATUS_ENUM_UINT32           enDelayType;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8          enOldSubMode;

    enOldSubMode                            = TAF_SDC_GetSysSubMode();
#endif
    enSysMode                               = TAF_SDC_SYS_MODE_BUTT;
    enSubMode                               = TAF_SDC_SYS_SUBMODE_BUTT;
    enNetworkExist                          = TAF_SDC_NETWORK_BUT;
    pFuncTafSdcSysmodServiceRegStaUpdate    = VOS_NULL_PTR;
    enDelayType                             = MMA_TAF_CL_STATUS_DO_LTE_NO_SERVICE;

    /* ����״̬��ʱ��ά�ɲ� */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

    if (TAF_MMA_DELAY_CL_REPORT_TYPE_DO == TAF_MMA_GetCLNoServiceDelayRptInfo()->enDelayType)
    {
        enDelayType = MMA_TAF_CL_STATUS_DO_NO_SERVICE;
    }

    TAF_MMA_GetCLNoServiceDelayRptInfo()->enDelayType   = TAF_MMA_DELAY_CL_REPORT_TYPE_BUTT;

    enNetworkExist = TAF_SDC_HRPD_NETWORK_NOT_EXIST;

    TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(enNetworkExist, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);
    Mma_ModeChgReport(enSysMode, enSubMode);

    TAF_SDC_SetSysMode(enSysMode);
    TAF_SDC_SetSysSubMode(enSubMode);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        if (TAF_SDC_SYS_SUBMODE_EHRPD == enOldSubMode)
        {
            TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeHrpd(enNetworkExist);

            TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());
        }
    }
#endif

    TAF_MMA_SndTafCLServiceStatusInd(enDelayType, VOS_FALSE);

    /* ����״̬��ʱ��ά�ɲ� */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);

    return VOS_TRUE;
}

/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcPihUsimRefreshIndEfUstFileChanged_PreProc
 ��������  : Ԥ�����ļ�ˢ��ָʾEFUST�ļ����ָʾ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ҫ��һ������
             VOS_FALSE:��Ҫ��״̬������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 TAF_MMA_ProcPihUsimRefreshIndEfUstFileChanged_PreProc(VOS_VOID)
{
    TAF_SDC_CALL_MODE_ENUM_UINT8        enOldCallMode;
    TAF_SDC_CALL_MODE_ENUM_UINT8        enNewCallMode;

    /* �ػ�ģʽ�������ļ���� */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
       return VOS_TRUE;
    }

    /* �ж�ecallģʽ�Ƿ����ı� */
    enOldCallMode = TAF_SDC_GetCurCallMode();

    /*  ����ecallģʽ��Ϣ */
    TAF_MMA_UpdateCallMode();

    enNewCallMode = TAF_SDC_GetCurCallMode();

    /* ����ecall onlyģʽ */
    if ((enOldCallMode       != enNewCallMode)
     && ((TAF_SDC_ECALL_ONLY == enOldCallMode)
      || (TAF_SDC_ECALL_ONLY == enNewCallMode)))
    {
        /* ��ǰ״̬������main״̬,�����ڲ���״̬�ı�ָʾ��Ϣ���� */
        if (TAF_MMA_FSM_MAIN != TAF_MMA_GetCurrFsmId())
        {
            TAF_MMA_SndInterUsimChangeInd();

            return VOS_TRUE;
        }

        /* �Ѿ����������main�����ػ����� */
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#endif
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-22, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : TAF_MMA_MapMsccServiceStatus
 ��������  : CDMA����״̬ת��ΪTAF�����״̬
 �������  : XSD_MMA_SERVICE_STATUS_ENUM_UINT8   enServiceStatus
 �������  : ��
 �� �� ֵ  : TAF_SDC_SERVICE_STATUS_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��20��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_MMA_MapMsccServiceStatus(
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32     enServiceStatus
)
{
    if (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == enServiceStatus)
    {
        return TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE;
    }
    else if ( NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == enServiceStatus)
    {
        return TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE;
    }
    else if ( NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION == enServiceStatus)
    {
        return TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION;
    }
    else if ( NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI == enServiceStatus)
    {
        return TAF_SDC_SERVICE_STATUS_NO_IMSI;
    }
    else if ( NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE == enServiceStatus)
    {
        return TAF_SDC_SERVICE_STATUS_NO_CHANGE;
    }
    else if ( NAS_MSCC_PIF_SERVICE_STATUS_DEEP_SLEEP == enServiceStatus)
    {
        return TAF_SDC_SERVICE_STATUS_DEEP_SLEEP;
    }
    else
    {
        return TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    }


}


TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32 TAF_MMA_Map1xSrvStaToCdmaNetworkExistance(
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32                 enSrvSta
)
{
    if ((NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == enSrvSta)
     || (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == enSrvSta))
    {
        return TAF_SDC_1X_NETWORK_EXIST;
    }
    else
    {
        return TAF_SDC_1X_NETWORK_NOT_EXIST;
    }
}







/*****************************************************************************
 �� �� ��  : TAF_MMA_CovertSubMode_1xLost
 ��������  : 1x�޷���ʱ����ȡ��ǰ��submode��
 �������  : TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enPreSubMode
 �������  : ��
 �� �� ֵ  : TAF_SDC_SYS_SUBMODE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : m00312079
    �޸�����   : �½�
*****************************************************************************/
TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_MMA_CovertSubMode_1xLost(
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enPreSubMode
)
{
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enCurrSubMode;

    switch (enPreSubMode)
    {
        case TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A:

            enCurrSubMode = TAF_SDC_SYS_SUBMODE_EVDO_REL_A;
            break;

        case TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0:

            enCurrSubMode = TAF_SDC_SYS_SUBMODE_EVDO_REL_0;
            break;
        default:

            enCurrSubMode = TAF_SDC_GetSysSubMode();
            break;
    }

    return enCurrSubMode;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CovertSubMode_1xExist
 ��������  : 1x�з���ʱ����ȡ��ǰ��submode��
 �������  : TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enPreSubMode
 �������  : ��
 �� �� ֵ  : TAF_SDC_SYS_SUBMODE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : m00312079
    �޸�����   : �½�
*****************************************************************************/
TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_MMA_CovertSubMode_1xExist(
     TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enPreSubMode

)
{
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enCurrSubMode;

    switch (enPreSubMode)
    {
        case TAF_SDC_SYS_SUBMODE_EVDO_REL_A:

            enCurrSubMode = TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A;
            break;

        case TAF_SDC_SYS_SUBMODE_EVDO_REL_0:

            enCurrSubMode = TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0;
            break;
        default:

            enCurrSubMode = TAF_SDC_GetSysSubMode();
            break;
    }

    return enCurrSubMode;

}



/*****************************************************************************
 �� �� ��  : TAF_MMA_BuildStk1xSystemInfo
 ��������  : �����STK��1X system info
 �������  : NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU  *pstMscc1xSysSrvInfo
 �������  : MMA_STK_1X_SYS_INFO_STRU           *pstStk1xSysInfo
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_BuildStk1xSystemInfo(
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU  *pstMscc1xSysSrvInfo,
    MMA_STK_1X_SYS_INFO_STRU           *pstStk1xSysInfo
)
{
    TAF_SDC_1X_SYS_INFO_STRU           *pSdc1xSysInfo = VOS_NULL_PTR;

    pSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    if (PS_TRUE == pstMscc1xSysSrvInfo->enServiceInfoIncl)
    {
        pstStk1xSysInfo->ulMcc           = TAF_STD_TransformBcdMccToDeciDigit(pstMscc1xSysSrvInfo->stServiceInfo.ulMcc);
        pstStk1xSysInfo->usImsi11_12     = TAF_STD_TransformBcdImsi1112ToDeciDigit(pstMscc1xSysSrvInfo->stServiceInfo.usImsi11_12);
    }
    else
    {
        pstStk1xSysInfo->ulMcc           = TAF_STD_TransformBcdMccToDeciDigit(pSdc1xSysInfo->stServiceInfo.ulMcc);
        pstStk1xSysInfo->usImsi11_12     = TAF_STD_TransformBcdImsi1112ToDeciDigit(pSdc1xSysInfo->stServiceInfo.usImsi11_12);
    }

    pstStk1xSysInfo->usSid           = pstMscc1xSysSrvInfo->usSid;
    pstStk1xSysInfo->usNid           = pstMscc1xSysSrvInfo->usNid;

    if (PS_TRUE == pstMscc1xSysSrvInfo->enBaseStationInfoIncl)
    {
        pstStk1xSysInfo->usBaseId        = pstMscc1xSysSrvInfo->stBaseStationInfo.usBaseId;
        pstStk1xSysInfo->lBaseLatitude   = pstMscc1xSysSrvInfo->stBaseStationInfo.lBaseLatitude;
        pstStk1xSysInfo->lBaseLongtitude = pstMscc1xSysSrvInfo->stBaseStationInfo.lBaseLongitude;
    }
    else
    {
        pstStk1xSysInfo->usBaseId        = pSdc1xSysInfo->stBaseStationInfo.usBaseId;
        pstStk1xSysInfo->lBaseLatitude   = pSdc1xSysInfo->stBaseStationInfo.lBaseLatitude;
        pstStk1xSysInfo->lBaseLongtitude = pSdc1xSysInfo->stBaseStationInfo.lBaseLongitude;
    }
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_BuildStkSrvStatus
 ��������  : �����STK�ķ���״̬
 �������  : NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32     enServiceStatus
             NAS_STK_SERVICE_STATUS_INFO_STRU           *pstServiceStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_BuildStkSrvStatus(
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32     enServiceStatus,
    NAS_STK_SERVICE_STATUS_INFO_STRU           *pstServiceStatus
)
{
    switch(enServiceStatus)
    {
        case NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE:
            pstServiceStatus->enCsServiceStatus = NAS_STK_SERVICE_STATUS_NORMAL_SERVICE;
            break;

        case NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE:
            pstServiceStatus->enCsServiceStatus = NAS_STK_SERVICE_STATUS_LIMITED_SERVICE;
            break;

        case NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE:
            pstServiceStatus->enCsServiceStatus = NAS_STK_SERVICE_STATUS_NO_SERVICE;
            break;

        default:
            pstServiceStatus->enCsServiceStatus = NAS_STK_SERVICE_STATUS_NO_SERVICE;
            break;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsStk1xSystemInfoChanged
 ��������  : �ж�STK��Ҫ��service info�Ƿ��иı�
 �������  : TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enCurServiceStatus
             NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU               *pstMscc1xSysSrvInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��8��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsStk1xSystemInfoChanged(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCurServiceStatus,
    NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU  *pstMscc1xSysSrvInfo
)
{
    TAF_SDC_1X_SYS_INFO_STRU           *pSdc1xSysInfo = VOS_NULL_PTR;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enLastCsServiceStatus;

    pSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    enLastCsServiceStatus = TAF_SDC_GetCsServiceStatus();

    /* �жϷ���״̬ */
    if (enLastCsServiceStatus != enCurServiceStatus)
    {
        return VOS_TRUE;
    }

    if (PS_TRUE == pstMscc1xSysSrvInfo->enServiceInfoIncl)
    {
        if (pSdc1xSysInfo->stServiceInfo.ulMcc != pstMscc1xSysSrvInfo->stServiceInfo.ulMcc)
        {
            return VOS_TRUE;
        }

        if (pSdc1xSysInfo->stServiceInfo.usImsi11_12 != pstMscc1xSysSrvInfo->stServiceInfo.usImsi11_12)
        {
            return VOS_TRUE;
        }
    }

    if (pSdc1xSysInfo->lSid != (0x00000000 | pstMscc1xSysSrvInfo->usSid))
    {
        return VOS_TRUE;
    }

    if (pSdc1xSysInfo->lNid != (0x00000000 | pstMscc1xSysSrvInfo->usNid))
    {
        return VOS_TRUE;
    }


    if (PS_TRUE == pstMscc1xSysSrvInfo->enBaseStationInfoIncl)
    {
        if (pSdc1xSysInfo->stBaseStationInfo.usBaseId != pstMscc1xSysSrvInfo->stBaseStationInfo.usBaseId)
        {
            return VOS_TRUE;
        }

        if (pSdc1xSysInfo->stBaseStationInfo.lBaseLatitude != pstMscc1xSysSrvInfo->stBaseStationInfo.lBaseLatitude)
        {
            return VOS_TRUE;
        }

        if (pSdc1xSysInfo->stBaseStationInfo.lBaseLongitude != pstMscc1xSysSrvInfo->stBaseStationInfo.lBaseLongitude)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_Rcv1xMsccSystemServiceInfoInd_PreProc
 ��������  : �����յ���XSD�����ϱ���ϵͳ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : g00261581
    �޸�����   : CDMA 1X Iteration 5 ��������
  2.��    ��   : 2015��06��03��
    ��    ��   : m00312079
    �޸�����   : ����EVDO�汾�Ŵ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMscc1xSystemServiceInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pstSysSrvInfoInd = VOS_NULL_PTR;
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enCdmaNetworkExist;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enServiceStatus;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode;

    MMA_STK_1X_SYS_INFO_STRU                                stSysInfo;
    NAS_STK_SERVICE_STATUS_INFO_STRU                        stServiceStatus;

    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate;

    NAS_MSCC_PIF_PLMN_ID_STRU                               stPlmnId;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8                        enOldRptSrvStatus;

    VOS_INT32                                               lSidTmp;
    enOldRptSrvStatus                    = TAF_SDC_REPORT_SRVSTA_BUTT;
    pFuncTafSdcSysmodServiceRegStaUpdate = VOS_NULL_PTR;
    enSysMode                            = TAF_SDC_SYS_MODE_BUTT;
    enSubMode                            = TAF_SDC_SYS_SUBMODE_BUTT;

    /* ����״̬��ʱ��ά�ɲ� */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

    PS_MEM_SET(&stPlmnId, 0x00, sizeof(NAS_MSCC_PIF_PLMN_ID_STRU));

    PS_MEM_SET(&stSysInfo, 0, sizeof(MMA_STK_1X_SYS_INFO_STRU));
    PS_MEM_SET(&stServiceStatus, 0, sizeof(NAS_STK_SERVICE_STATUS_INFO_STRU));

    pstSysSrvInfoInd = (MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND_STRU *)pstMsg;

    /* �����no rf��־����ֱ�Ӳ����� */
    if (VOS_FALSE == TAF_SDC_Get1xRfAvailFlag())
    {
        return VOS_TRUE;
    }

    enCdmaNetworkExist = TAF_MMA_Map1xSrvStaToCdmaNetworkExistance(pstSysSrvInfoInd->stSysSrvInfo.enServiceStatus);

    /* Cdma have limited service and normal service, so it should be concerned*/
    enServiceStatus = TAF_MMA_MapMsccServiceStatus(pstSysSrvInfoInd->stSysSrvInfo.enServiceStatus);

    /* to calc the sysmode and submode */
    TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(enCdmaNetworkExist, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

    if (TAF_SDC_1X_NETWORK_EXIST  == enCdmaNetworkExist)
    {



        TAF_MMA_SndApsEpdszidInfoInd(pstSysSrvInfoInd->stSysSrvInfo.usSid,
                                     pstSysSrvInfoInd->stSysSrvInfo.usNid,
                                     pstSysSrvInfoInd->stSysSrvInfo.ucPzid);

        if (TAF_SDC_SYS_MODE_HYBRID == enSysMode)
        {
            enSubMode = TAF_SDC_GetSysSubMode();

            enSubMode = TAF_MMA_CovertSubMode_1xExist(enSubMode);
        }


        /* ^MODE�����ϱ����� */
        Mma_ModeChgReport(enSysMode, enSubMode);

        /* ֪ͨAPS��ǰ�ķ���״̬,ֻҪ��1X���Ӿ���Ϊ������1X���Խ��� */
        TAF_MMA_SndTaf1XServiceStatusInd(VOS_TRUE);


        /* ֪ͨXSMS��ǰ�ķ���״̬*/

        TAF_MMA_SndXsmsServiceStatusInd(enSysMode, VOS_FALSE);

        if (VOS_TRUE == TAF_MMA_IsStk1xSystemInfoChanged(enServiceStatus, &(pstSysSrvInfoInd->stSysSrvInfo)))
        {
            TAF_MMA_BuildStk1xSystemInfo(&(pstSysSrvInfoInd->stSysSrvInfo), &stSysInfo);
            TAF_MMA_BuildStkSrvStatus(pstSysSrvInfoInd->stSysSrvInfo.enServiceStatus, &stServiceStatus);
            TAF_MMA_SndStk1xServiceInfoInd(&stSysInfo, &stServiceStatus);
        }

        /* ����MMAά����Mode/SubMode, SysMode�������ڷ���״̬ˢ�� */
        TAF_SDC_SetSysMode(enSysMode);

        /* TO Do:���������ǰSubMode��DO,����Ҫ����SubMode */
        TAF_SDC_SetSysSubMode(enSubMode);

        /* Normal serviceʱ������ϵͳ��Ϣ */
        TAF_SDC_Set1xSysInfo((NAS_MSCC_PIF_1X_SYS_SRV_INFO_STRU*)(&(pstSysSrvInfoInd->stSysSrvInfo)));

        /* �����ϵķ���״̬ */
        enOldRptSrvStatus = TAF_SDC_GetServiceStatus();

        /* ���·���״̬����״̬ */
        TAF_MMA_Update1xServiceStatusAndDomain(enServiceStatus, enSysMode);

        /* �ϱ�CREG */
        if (TAF_SDC_SYS_ROAMING_STATUS_OFF == pstSysSrvInfoInd->stSysSrvInfo.ucRoamingInd)
        {
            TAF_MMA_Report1xCregStatus(TAF_SDC_REG_REGISTERED_HOME_NETWORK);
        }
        else
        {
            TAF_MMA_Report1xCregStatus(TAF_SDC_REG_REGISTERED_ROAM);
        }

    }

    if (TAF_SDC_1X_NETWORK_NOT_EXIST == enCdmaNetworkExist)
    {

        if (TAF_SDC_SYS_MODE_EVDO == enSysMode)
        {
            enSubMode = TAF_SDC_GetSysSubMode();

            enSubMode = TAF_MMA_CovertSubMode_1xLost(enSubMode);
        }

        /* ^MODE�����ϱ����� */
        Mma_ModeChgReport(enSysMode, enSubMode);


        /* ���з����޷�����ϱ� */
        if (TAF_SDC_SERVICE_STATUS_NO_SERVICE != TAF_SDC_GetCsServiceStatus())
        {
            TAF_MMA_BuildStkSrvStatus(NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE, &stServiceStatus);
            TAF_MMA_SndStk1xServiceInfoInd(&stSysInfo, &stServiceStatus);
        }

        TAF_SDC_SetSysMode(enSysMode);
        TAF_SDC_SetSysSubMode(enSubMode);

        /* �����ϵķ���״̬ */
        enOldRptSrvStatus = TAF_SDC_GetServiceStatus();

        /* ���·���״̬����״̬ */
        TAF_MMA_Update1xServiceStatusAndDomain(enServiceStatus, enSysMode);

        /* �ϱ�CREG */
        TAF_MMA_Report1xCregStatus(TAF_SDC_REG_NOT_REGISTERED_SEARCHING);
    }


    /* ����״̬�и��²Ž��뺯������ */
    if (enOldRptSrvStatus != TAF_SDC_GetServiceStatus())
    {
        TAF_MMA_Report1xServiceState();
    }

    /* sid�Ƿ��ϱ��Ĵ��� SID������ʱ�ϱ�����*/
    lSidTmp = (0x00000000 | pstSysSrvInfoInd->stSysSrvInfo.usSid);
    TAF_MMA_Report1xSidInClMode(lSidTmp);

    if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
    {
        /* ���CS�����AT�����Ƿ���Ҫ�ϱ� */
        TAF_MMA_DelayReportCsReferCmdInClMode();

        /* ��stNetworkInfo����stAppNwInfo,��CS����� */
        TAF_MMA_UpdateAppCsSrvInfoInClMode();
    }

    /* ��ά�ɲ� */
    TAF_MMA_SndOmCdmaStatusInfoReportInd();

    /* ����������Ϣ�������ϱ� */
    if (PS_TRUE == pstSysSrvInfoInd->stSysSrvInfo.enServiceInfoIncl)
    {
        stPlmnId.ulMcc  = pstSysSrvInfoInd->stSysSrvInfo.stServiceInfo.ulMcc;
        /*mncֻ��2λ����λ��0x0f */
        stPlmnId.ulMnc  = ((VOS_UINT32)pstSysSrvInfoInd->stSysSrvInfo.stServiceInfo.usMnc) | 0x0f0000;

        TAF_MMA_PlmnIdReport((TAF_PLMN_ID_STRU *)&stPlmnId);
    }

    TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode1x(enCdmaNetworkExist);

    TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());

    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccSyncServiceAvailInd_PreProc
 ��������  : �����յ���MSCC�����ϱ���ϵͳ���������Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��31��
    ��    ��   : w00242748
    �޸�����   : CDMA 1X Iteration 17 ��������
  2.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccSyncServiceAvailInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU                   *pstSyncSrvAvailInd = VOS_NULL_PTR;
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enCdmaNetworkExist;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enServiceStatus;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode;
    MMA_STK_1X_SYS_INFO_STRU                                stSysInfo;
    NAS_STK_SERVICE_STATUS_INFO_STRU                        stServiceStatus;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate;
    TAF_SDC_1X_SYS_INFO_STRU                               *pstSdc1xSysInfo = VOS_NULL_PTR;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8                        enOldRptSrvStatus;
    VOS_INT32                                               lSidTmp;

    /* ����״̬��ʱ��ά�ɲ� */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

    pFuncTafSdcSysmodServiceRegStaUpdate = VOS_NULL_PTR;
    enSysMode                            = TAF_SDC_SYS_MODE_BUTT;
    enSubMode                            = TAF_SDC_SYS_SUBMODE_BUTT;

    PS_MEM_SET(&stSysInfo, 0, sizeof(MMA_STK_1X_SYS_INFO_STRU));
    PS_MEM_SET(&stServiceStatus, 0, sizeof(NAS_STK_SERVICE_STATUS_INFO_STRU));

    pstSyncSrvAvailInd = (MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU *)pstMsg;

    /* �����no rf��־����ֱ�Ӳ����� */
    if (VOS_FALSE == TAF_SDC_Get1xRfAvailFlag())
    {
        return VOS_TRUE;
    }

    enCdmaNetworkExist = TAF_MMA_Map1xSrvStaToCdmaNetworkExistance(pstSyncSrvAvailInd->enServiceStatus);

    /* Cdma have limited service and normal service, so it should be concerned*/
    enServiceStatus = TAF_MMA_MapMsccServiceStatus(pstSyncSrvAvailInd->enServiceStatus);

    /* to calc the sysmode and submode */
    TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(enCdmaNetworkExist, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

    if (TAF_SDC_SYS_MODE_HYBRID == enSysMode)
    {
        enSubMode = TAF_SDC_GetSysSubMode();

        enSubMode = TAF_MMA_CovertSubMode_1xExist(enSubMode);
    }


    /* ^MODE�����ϱ����� */
    Mma_ModeChgReport(enSysMode, enSubMode);

    /* ����MMAά����Mode/SubMode */
    TAF_SDC_SetSysMode(enSysMode);

    /* TO Do:���������ǰSubMode��DO,����Ҫ����SubMode */
    TAF_SDC_SetSysSubMode(enSubMode);

    /* �����ϵķ���״̬ */
    enOldRptSrvStatus = TAF_SDC_GetServiceStatus();

    /* ���·���״̬����״̬ */
    TAF_MMA_Update1xServiceStatusAndDomain(enServiceStatus, enSysMode);

    /* �ϱ�CREG */
    if (TAF_SDC_SYS_ROAMING_STATUS_OFF == pstSyncSrvAvailInd->ucRoamingInd)
    {
        TAF_MMA_Report1xCregStatus(TAF_SDC_REG_REGISTERED_HOME_NETWORK);
    }
    else
    {
        TAF_MMA_Report1xCregStatus(TAF_SDC_REG_REGISTERED_ROAM);
    }

    /* Normal serviceʱ������ϵͳ��Ϣ */
    pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    pstSdc1xSysInfo->usBandClass      = pstSyncSrvAvailInd->usBandClass;
    pstSdc1xSysInfo->usFreq           = pstSyncSrvAvailInd->usFreq;
    pstSdc1xSysInfo->lSid             = (0x00000000 | pstSyncSrvAvailInd->usSid);
    pstSdc1xSysInfo->lNid             = (0x00000000 | pstSyncSrvAvailInd->usNid);
    pstSdc1xSysInfo->ucRoamingInd     = pstSyncSrvAvailInd->ucRoamingInd;

    /* ����״̬�и��£��Ž��뺯������ */
    if (enOldRptSrvStatus != TAF_SDC_GetServiceStatus())
    {
        TAF_MMA_Report1xServiceState();
    }

    /* sid�Ƿ��ϱ��Ĵ��� SID������ʱ�ϱ�����*/
    lSidTmp = (0x00000000 | pstSyncSrvAvailInd->usSid);
    TAF_MMA_Report1xSidInClMode(lSidTmp);

    if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
    {
        /* ���CS�����AT�����Ƿ���Ҫ�ϱ� */
        TAF_MMA_DelayReportCsReferCmdInClMode();

        /* ��stNetworkInfo����stAppNwInfo,��CS����� */
        TAF_MMA_UpdateAppCsSrvInfoInClMode();
    }

    TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode1x(TAF_SDC_1X_NETWORK_EXIST);

    TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());

    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);

    /* ��ά�ɲ� */
    TAF_MMA_SndOmCdmaStatusInfoReportInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafCdmaMoCallStartNtf_PreProc
 ��������  : �յ�ID_TAF_MMA_CDMA_MO_CALL_START_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��21��
    ��    ��   : h00313353
    �޸�����   : ����17 ������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafCdmaMoCallStartNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CDMA_MO_CALL_START_NTF_STRU *pstCallStartNtf = VOS_NULL_PTR;
    TAF_SDC_1X_SYS_INFO_STRU            *pstSdc1xSysInfo = VOS_NULL_PTR;

    pstCallStartNtf = (TAF_MMA_CDMA_MO_CALL_START_NTF_STRU *)pstMsg;
    pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    /* ֪ͨXSD */
    TAF_MMA_SndMsccCdmaMoCallStartNtf(pstCallStartNtf->enCallType);

    /* CallBack״̬�������ݺ������˳�CallBack���� */
    if ((VOS_TRUE == pstSdc1xSysInfo->ulIsInEmcCallBack)
     && (TAF_MMA_1X_NORMAL_DATA_CALL != pstCallStartNtf->enCallType))
    {
        TAF_MMA_SndMsccQuitCallBackNtf();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafCdmaMoCallEndNtf_PreProc
 ��������  : �յ�ID_TAF_MMA_CDMA_MO_CALL_END_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafCdmaMoCallEndNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CDMA_MO_CALL_END_NTF_STRU *pstCallEndNtf = VOS_NULL_PTR;

    pstCallEndNtf = (TAF_MMA_CDMA_MO_CALL_END_NTF_STRU *)pstMsg;

    /* ֪ͨXSD */
    TAF_MMA_SndMsccCdmaMoCallEndNtf(pstCallEndNtf->enCallType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafCdmaMoCallSuccessNtf_PreProc
 ��������  : �յ�ID_TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafCdmaMoCallSuccessNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU   *pstCallSuccNtf = VOS_NULL_PTR;

    pstCallSuccNtf = (TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF_STRU *)pstMsg;

    /* ֪ͨXSD */
    TAF_MMA_SndMsccCdmaMoCallSuccessNtf(pstCallSuccNtf->enCallType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafCdmaCallRedialSystemAcquireNtf
 ��������  : �յ�ID_TAF_MMA_CMDA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafCdmaCallRedialSystemAcquireNtf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU       *pstCallRedialNtf = VOS_NULL_PTR;

    pstCallRedialNtf = (TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF_STRU *)pstMsg;

    /* ֪ͨXSD */
    TAF_MMA_SndMsccCdmaMoCallRedialSysAcqNtf(pstCallRedialNtf->enCallType, pstCallRedialNtf->ulCause);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAtQueryCLocInfo_PreProc
 ��������  : MMAԤ�����д���at����^CLOCINFO
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��4��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��03��25��
    ��    ��   : K00902809
    �޸�����   : Changed the structure from TAF_MMA_CLOCINFO_QUERY_REQ_STRU to TAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU
  3.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAtQueryCLocInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU  *pstAppReqMsg = VOS_NULL_PTR;
    TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU  *pstCLocInfoQryCnf = VOS_NULL_PTR;
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    VOS_UINT32                          ulMccTmp;
    VOS_UINT16                          usMncTmp;
    pstAppReqMsg      = (TAF_MMA_CDMA_LOCINFO_QRY_REQ_STRU *)pstMsg;

    pstCLocInfoQryCnf = (TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                          sizeof(TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstCLocInfoQryCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvAtQueryCLocInfo_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCLocInfoQryCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CDMA_LOCINFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    pstSdc1xSysInfo = TAF_SDC_GetApp1xSysInfo();

    /* ��д��Ϣͷ����Ϣ */
    pstCLocInfoQryCnf->ulReceiverPid          = pstAppReqMsg->stCtrl.ulModuleId;
    pstCLocInfoQryCnf->ulMsgName              = ID_TAF_MMA_CDMA_LOCINFO_QRY_CNF;
    PS_MEM_CPY(&pstCLocInfoQryCnf->stCtrl, &pstAppReqMsg->stCtrl, sizeof(TAF_MMA_CTRL_STRU));

    enSysMode     = TAF_SDC_GetAppSysMode();
    /* aP�����յ�^mode srvst reg plmn ���ϱ�����ʱ��������cdma������£����·�ClocInfo��ѯ��
        Ϊ�˺��ϱ���Ϣ����һ�£�LocInfo�ϱ�AppNetWorkInfo�е���Ϣ */
    if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode)
     || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
    {
        pstCLocInfoQryCnf->ulRslt         = VOS_OK;
        if (PS_TRUE == pstSdc1xSysInfo->enBaseStationInfoIncl)
        {
            pstCLocInfoQryCnf->stClocinfoPara.ulBaseId              = pstSdc1xSysInfo->stBaseStationInfo.usBaseId;
            pstCLocInfoQryCnf->stClocinfoPara.lBaseLatitude         = pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude;
            pstCLocInfoQryCnf->stClocinfoPara.lBaseLongitude        = pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude;
        }
        else
        {
            pstCLocInfoQryCnf->stClocinfoPara.ulBaseId              = TAF_MMA_INVALID_BASE_ID;
            pstCLocInfoQryCnf->stClocinfoPara.lBaseLatitude         = TAF_MMA_INVALID_BASE_LATITUDE;
            pstCLocInfoQryCnf->stClocinfoPara.lBaseLongitude        = TAF_MMA_INVALID_BASE_LONGITUDE;
        }
        pstCLocInfoQryCnf->stClocinfoPara.lSid                  = pstSdc1xSysInfo->lSid;
        pstCLocInfoQryCnf->stClocinfoPara.lNid                  = pstSdc1xSysInfo->lNid;
        if (PS_TRUE == pstSdc1xSysInfo->enServiceInfoIncl)
        {
            ulMccTmp = pstSdc1xSysInfo->stServiceInfo.ulMcc;
            usMncTmp = pstSdc1xSysInfo->stServiceInfo.usImsi11_12;
        }
        else
        {
            ulMccTmp = MMA_INVALID_MCC;
            usMncTmp = (VOS_UINT16)MMA_INVALID_MNC;
        }

        pstCLocInfoQryCnf->stClocinfoPara.ulMcc           = (VOS_UINT32)TAF_STD_TransformBcdMccToDeciDigit(ulMccTmp);
        pstCLocInfoQryCnf->stClocinfoPara.ulMnc           = (VOS_UINT32)TAF_STD_TransformBcdMncToDeciDigit(usMncTmp);

        pstCLocInfoQryCnf->stClocinfoPara.usPrevInUse     = pstSdc1xSysInfo->ucPrevInUse;
    }
    else
    {
        pstCLocInfoQryCnf->ulRslt          = VOS_ERR;
    }

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCLocInfoQryCnf);

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvSetCFreqLock_PreProc
 ��������  : MMAԤ�����д���^CFREQLOCK��������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                 �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSetCFreqLock_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CFREQ_LOCK_SET_REQ_STRU    *pstCFreqLockSetReq     = VOS_NULL_PTR;
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstTafMmaCFreqLockPara = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo = VOS_NULL_PTR;

    pstCFreqLockSetReq = (TAF_MMA_CFREQ_LOCK_SET_REQ_STRU *)pstMsg;

    /*  ��ȡȫ�ֱ�����ֵ */
    pstTafMmaCFreqLockPara = TAF_MMA_GetCFreqLockSetPara();

    pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    /* CallBack״̬����������Ƶ */
    if (VOS_TRUE == pstSdc1xSysInfo->ucIsEmcCallExistFlg)
    {
        TAF_MMA_SndCFreqLockSetCnf(pstCFreqLockSetReq, VOS_FALSE);

        return VOS_TRUE;
    }

    /*  ������ò����仯��дNV��NTF XSD/HSD */
    if (0 != PS_MEM_CMP(pstTafMmaCFreqLockPara,
                        &pstCFreqLockSetReq->stCFreqLockPara,
                        sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU)))
    {
        #ifndef DMT
        /* wirte CFREQLOCK informations into NV */
        ulRslt = NV_Write(en_NV_Item_CFreqLock_CFG,
                          &pstCFreqLockSetReq->stCFreqLockPara,
                          sizeof(TAF_NVIM_CFREQ_LOCK_CFG_STRU));

        if (NV_OK != ulRslt)
        {
            TAF_MMA_SndCFreqLockSetCnf(pstCFreqLockSetReq, VOS_FALSE);
            return VOS_TRUE;
        }
        #endif
        /* ����MMA�������Ƶȫ�ֱ��� */
        PS_MEM_CPY(pstTafMmaCFreqLockPara,
                   &pstCFreqLockSetReq->stCFreqLockPara,
                   sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU));

        /* ����MMA_XSD_CFREQLOCK_SET_NTF */
        TAF_MMA_SndMsccCFreqLockNtf(pstTafMmaCFreqLockPara);

        /* TODO:����MMA_HSD_CFREQLOCK_SET_NTF */

    }
    /* ����TAF_MMA_CFREQ_LOCK_SET_CNF */
    TAF_MMA_SndCFreqLockSetCnf(pstCFreqLockSetReq, VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvQueryCFreqLock_PreProc
 ��������  : MMAԤ�����д���^CFREQLOCK��ѯ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvQueryCFreqLock_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CFREQ_LOCK_QUERY_REQ_STRU  *pstAppReqMsg            = VOS_NULL_PTR;
    TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU  *pstCFreqLockQryCnf      = VOS_NULL_PTR;
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstTafMmaCFreqLockPara  = VOS_NULL_PTR;


    pstAppReqMsg     = (TAF_MMA_CFREQ_LOCK_QUERY_REQ_STRU *)pstMsg;

    pstCFreqLockQryCnf = (TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                       sizeof(TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU));
    if (VOS_NULL_PTR == pstCFreqLockQryCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvAtQueryCFreqLock_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCFreqLockQryCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CFREQ_LOCK_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstCFreqLockQryCnf->ulReceiverPid          = pstAppReqMsg->stCtrl.ulModuleId;
    pstCFreqLockQryCnf->ulMsgName              = ID_TAF_MMA_CDMA_FREQ_LOCK_QRY_CNF;

    PS_MEM_CPY(&pstCFreqLockQryCnf->stCtrl, &pstAppReqMsg->stCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstTafMmaCFreqLockPara = TAF_MMA_GetCFreqLockSetPara();
    PS_MEM_CPY(&pstCFreqLockQryCnf->stCFreqLockPara,
                pstTafMmaCFreqLockPara,
                sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU));

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCFreqLockQryCnf);

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcCdmaCsqSetReq_PreProc
 ��������  : ����TAF�ź�ǿ���ϱ���������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��25��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��16��
    ��    ��   : m00312079
    �޸�����   : DTS2015101505057:���ec/Io���ϱ�����
  3.��    ��   : 2016��1��7��
    ��    ��   : t00323010
    �޸�����   : DTS2016010711329:����ƽ̨�Ƿ�֧��1x�߼��ж�
*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcCdmaCsqSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CDMACSQ_SET_REQ_STRU       *pstMmaCdmaCsqReqMsg = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx       = VOS_NULL_PTR;
    NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU  stCdmaCsqSetPara;
    VOS_UINT8                           ucCtxIndex;

    pstMmaCdmaCsqReqMsg  = (TAF_MMA_CDMACSQ_SET_REQ_STRU *)pstMsg;

    /* ���ƽ̨������֧��1x, ���·�����, ֱ�ӷ���ʧ�� */
    if (VOS_FALSE == TAF_SDC_IsPlatformSupport1x())
    {
        TAF_MMA_SndCdmaCsqSetCnf(&(pstMmaCdmaCsqReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE);

        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndCdmaCsqSetCnf(&(pstMmaCdmaCsqReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstMmaCdmaCsqReqMsg->stCtrl,
                       TAF_MMA_OPER_CDMACSQ_SET_REQ, ucCtxIndex);

    /*�����Ϣ*/
    PS_MEM_SET(&stCdmaCsqSetPara, 0, sizeof(NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU));
    stCdmaCsqSetPara.ucTimeInterval     = pstMmaCdmaCsqReqMsg->stCdmaCsqPara.ucTimeInterval;
    stCdmaCsqSetPara.ucRssiRptThreshold = pstMmaCdmaCsqReqMsg->stCdmaCsqPara.ucRssiRptThreshold;
    stCdmaCsqSetPara.ucEcIoRptThreshold = pstMmaCdmaCsqReqMsg->stCdmaCsqPara.ucEcIoRptThreshold;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();
    pstMmaOperCtx[ucCtxIndex].pPara = (TAF_MMA_CDMACSQ_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_CDMACSQ_PARA_STRU));

    if (VOS_NULL_PTR == pstMmaOperCtx[ucCtxIndex].pPara)
    {
        TAF_MMA_SndCdmaCsqSetCnf(&(pstMmaCdmaCsqReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
        return VOS_TRUE;
    }

    if (VOS_TRUE != TAF_MMA_SndMsccCdmaCsqSetReq(stCdmaCsqSetPara))
    {
        TAF_MMA_SndCdmaCsqSetCnf(&(pstMmaCdmaCsqReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE);

        PS_MEM_FREE(WUEPS_PID_MMA, pstMmaOperCtx[ucCtxIndex].pPara);
        pstMmaOperCtx[ucCtxIndex].pPara = VOS_NULL_PTR;

        TAF_MMA_ClearOperCtx(ucCtxIndex);

        return VOS_TRUE;
    }

    PS_MEM_CPY(pstMmaOperCtx[ucCtxIndex].pPara, &pstMmaCdmaCsqReqMsg->stCdmaCsqPara, sizeof(TAF_MMA_CDMACSQ_PARA_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccCdmaCsqSetCnf_PreProc
 ��������  : ����XSD�ź�ǿ���ϱ����õĴ�����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��16��
    ��    ��   : m00312079
    �޸�����   : DTS2015101505057:���ec/Io���ϱ�����
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCdmaCsqSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_CDMACSQ_SET_CNF_STRU        *pstCdmaCsqCnf             = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU                *pstMmaOperCtx             = VOS_NULL_PTR;
    TAF_MMA_CDMACSQ_PARA_STRU            *pstMmaCdmaCsqPara         = VOS_NULL_PTR;
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU     *pstSdc1xSigQualityInfo    = VOS_NULL_PTR;
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU     *pstSdcApp1xSigQualityInfo = VOS_NULL_PTR;
    VOS_UINT8                             ucCtxIndex;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32   enRslt;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();
    enRslt          = TAF_MMA_APP_OPER_RESULT_SUCCESS;

    pstCdmaCsqCnf   = (MSCC_MMA_CDMACSQ_SET_CNF_STRU *)pstMsg;

    if ( NAS_MSCC_PIF_CDMACSQ_SET_RESULT_SUCC != pstCdmaCsqCnf->enRslt )
    {
        enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
    }

    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CDMACSQ_SET_REQ, &ucCtxIndex))
    {
        /* ����CDMACSQ�����ûظ� */
        TAF_MMA_SndCdmaCsqSetCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                                enRslt);

        if (TAF_MMA_APP_OPER_RESULT_SUCCESS == enRslt)
        {

            pstMmaCdmaCsqPara  = (TAF_MMA_CDMACSQ_PARA_STRU *)pstMmaOperCtx[ucCtxIndex].pPara;
            /*����SDC��ȫ�ֱ���*/
            pstSdc1xSigQualityInfo                         = TAF_SDC_Get1xSigQualityInfo();

            pstSdc1xSigQualityInfo->enMode                 = pstMmaCdmaCsqPara->enMode;
            pstSdc1xSigQualityInfo->ucTimeInterval         = pstMmaCdmaCsqPara->ucTimeInterval;
            pstSdc1xSigQualityInfo->ucRssiRptThreshold     = pstMmaCdmaCsqPara->ucRssiRptThreshold;
            pstSdc1xSigQualityInfo->ucEcIoRptThreshold     = pstMmaCdmaCsqPara->ucEcIoRptThreshold;

            /* CDMACSQ����ʱ���ź���Ϣ��enMode,ucTimeInterval,ucRssiRptThreshold,ucEcIoRptThreshold��
                  �ź������Ŀ��Ʋ��������漰�ӳ��ϱ������Դ˴���Ҫͬ������app�е���4������ */
            pstSdcApp1xSigQualityInfo                      = TAF_SDC_GetApp1xSigQualityInfo();

            pstSdcApp1xSigQualityInfo->enMode              = pstMmaCdmaCsqPara->enMode;
            pstSdcApp1xSigQualityInfo->ucTimeInterval      = pstMmaCdmaCsqPara->ucTimeInterval;
            pstSdcApp1xSigQualityInfo->ucRssiRptThreshold  = pstMmaCdmaCsqPara->ucRssiRptThreshold;
            pstSdcApp1xSigQualityInfo->ucEcIoRptThreshold  = pstMmaCdmaCsqPara->ucEcIoRptThreshold;
        }

        /* ���CTX������  */
        TAF_MMA_ClearOperCtx(ucCtxIndex);
        PS_MEM_FREE(WUEPS_PID_MMA, pstMmaCdmaCsqPara);
    }
    else
    {
        MMA_ERRORLOG("TAF_MMA_RcvMsccCdmaCsqSetCnf_PreProc:ERROR");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvCdmaCsqQryReq_PreProc
 ��������  : ��ѯ�ź�ǿ��
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�

  2.��    ��   : 2015��10��16��
    ��    ��   : m00312079
    �޸�����   : DTS2015101505057:���ec/Io���ϱ�����
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvCdmaCsqQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CDMACSQ_QUERY_CNF_STRU       *pstCdmaCsqQryCnf       = VOS_NULL_PTR;
    TAF_MMA_CDMACSQ_QRY_REQ_STRU         *pstRcvMsg              = VOS_NULL_PTR;
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU     *pstSdc1xSigQualityInfo = VOS_NULL_PTR;



    pstRcvMsg = (TAF_MMA_CDMACSQ_QRY_REQ_STRU *)pstMsg;

    pstCdmaCsqQryCnf = (TAF_MMA_CDMACSQ_QUERY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                       sizeof(TAF_MMA_CDMACSQ_QUERY_CNF_STRU));
    if (VOS_NULL_PTR == pstCdmaCsqQryCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvAtCdmaCsqQryReq_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCdmaCsqQryCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CDMACSQ_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstCdmaCsqQryCnf->ulReceiverPid          = pstRcvMsg->stCtrl.ulModuleId;
    pstCdmaCsqQryCnf->ulMsgName              = ID_TAF_MMA_CDMACSQ_QRY_CNF;

    PS_MEM_CPY(&pstCdmaCsqQryCnf->stCtrl, &pstRcvMsg->stCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstSdc1xSigQualityInfo                              = TAF_SDC_GetApp1xSigQualityInfo();

    pstCdmaCsqQryCnf->enMode                            = pstSdc1xSigQualityInfo->enMode;
    pstCdmaCsqQryCnf->ucTimeInterval                    = pstSdc1xSigQualityInfo->ucTimeInterval;

    pstCdmaCsqQryCnf->ucRssiRptThreshold                = pstSdc1xSigQualityInfo->ucRssiRptThreshold;
    pstCdmaCsqQryCnf->ucEcIoRptThreshold                = pstSdc1xSigQualityInfo->ucEcIoRptThreshold;
    pstCdmaCsqQryCnf->stSigQualityInfo.sCdmaRssi        = pstSdc1xSigQualityInfo->sCdmaRssi;
    pstCdmaCsqQryCnf->stSigQualityInfo.sCdmaEcIo        = pstSdc1xSigQualityInfo->sCdmaEcIo;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCdmaCsqQryCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccCdmaCsqInd_PreProc
 ��������  : �����ϱ��ź�ǿ��
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�

 2.��    ��   : 2015��10��16��
   ��    ��   : m00312079
   �޸�����   : DTS2015101505057:���ec/Io���ϱ�����
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCdmaCsqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_CDMACSQ_IND_STRU            *pstCdmaCsqInd             = VOS_NULL_PTR;
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU     *pstSdc1xSigQualityInfo    = VOS_NULL_PTR;
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU     *pstAppSdc1xSigQualityInfo = VOS_NULL_PTR;
    TAF_MMA_CDMA_CSQ_MODE_ENUM_UINT8      enMode;

    pstCdmaCsqInd = (MSCC_MMA_CDMACSQ_IND_STRU *)pstMsg;

    /* �����no rf��־����ֱ�Ӳ����� */
    if (VOS_FALSE == TAF_SDC_Get1xRfAvailFlag())
    {
        return VOS_TRUE;
    }

    /* ����ȫ�ֱ��� */
    pstSdc1xSigQualityInfo                 = TAF_SDC_Get1xSigQualityInfo();
    pstSdc1xSigQualityInfo->sCdmaRssi      = pstCdmaCsqInd->sCdmaRssi;
    pstSdc1xSigQualityInfo->sCdmaEcIo      = pstCdmaCsqInd->sCdmaEcIo;

    enMode = pstSdc1xSigQualityInfo->enMode;

    if (TAF_MMA_CDMA_CSQ_MODE_ENABLE == enMode)
    {
        /* ����CDMACSQ�����ûظ� */

        /* �ӳ��ϱ���ʱ��������ʱ���ݲ��ϱ������ӳ��ϱ���ʱ��ֹͣ��ʱ��ʱ�򣬻�����������,������app����Ϣ */
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            pstSdc1xSigQualityInfo->cDelayRptFLag = VOS_TRUE;

            /* AT������ʱ�ϱ������� */
            TAF_MMA_LogDelayReportInfo(TAF_MMA_LOG_DELAY_RPT_CDMACSQ);
        }
        else
        {
            /* ͬ������APP�е��ź���Ϣ */
            pstAppSdc1xSigQualityInfo              = TAF_SDC_GetApp1xSigQualityInfo();
            pstAppSdc1xSigQualityInfo->sCdmaRssi   = pstCdmaCsqInd->sCdmaRssi;
            pstAppSdc1xSigQualityInfo->sCdmaEcIo   = pstCdmaCsqInd->sCdmaEcIo;

            TAF_MMA_SndCdmaCsqInd(pstCdmaCsqInd->sCdmaRssi,pstCdmaCsqInd->sCdmaEcIo);
        }
    }
    else
    {
        /* û�������ź����������ϱ����ܵĴ��� */

        /* �ӳ��ϱ���ʱ��ֹͣʱ����Ҫ����app�е��ź���Ϣ���������ӳ��ϱ���ʱ��ֹͣ��ʱ��ʱ�򣬻����app����Ϣ */
        if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            pstAppSdc1xSigQualityInfo              = TAF_SDC_GetApp1xSigQualityInfo();
            pstAppSdc1xSigQualityInfo->sCdmaRssi   = pstCdmaCsqInd->sCdmaRssi;
            pstAppSdc1xSigQualityInfo->sCdmaEcIo   = pstCdmaCsqInd->sCdmaEcIo;
        }
    }

    return VOS_TRUE;
}



TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32 TAF_MMA_MapHrpdSrvStaToCdmaNetworkExistance(
    MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32                enSrvSta
)
{
    if (MSCC_MMA_HRPD_SERVICE_STATUS_NORMAL_SERVICE == enSrvSta)
    {
        return TAF_SDC_HRPD_NETWORK_EXIST;
    }
    else
    {
        return TAF_SDC_HRPD_NETWORK_NOT_EXIST;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CovertSubMode_EvdoExist
 ��������  : EVDO�з���ʱ����ȡ��ǰ��submode��
 �������  : TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enPreSubMode
 �������  : ��
 �� �� ֵ  : TAF_SDC_SYS_SUBMODE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : m00312079
    �޸�����   : �½�
*****************************************************************************/
TAF_SDC_SYS_SUBMODE_ENUM_UINT8 TAF_MMA_CovertSubMode_EvdoExist(
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode,
    MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32          enCurrSessionRelType
)
{
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enCurrSubMode;

    if (TAF_SDC_SYS_MODE_EVDO == enSysMode)
    {
        switch (enCurrSessionRelType)
        {
            case MSCC_MMA_SESSION_RELEASE_TYPE_A:
                enCurrSubMode = TAF_SDC_SYS_SUBMODE_EVDO_REL_A;
                break;

            default:
                enCurrSubMode = TAF_SDC_SYS_SUBMODE_EVDO_REL_0;
                break;
        }
    }
    else/* hybrid mode */
    {
        switch (enCurrSessionRelType)
        {
            case MSCC_MMA_SESSION_RELEASE_TYPE_A:
                enCurrSubMode = TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A;
                break;

            default:
                enCurrSubMode = TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0;
                break;
        }
    }

    return enCurrSubMode;

}
/*****************************************************************************
Function Name   :   TAF_MMA_RcvMsccHrpdServiceStatusInd_PreProc
Description     :   Receive and process the MSCC hrpd service status ind
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   VOS_TRUE------------the current event is processed finished


Modify History  :
1)  Date           : 2015-02-04
    Author         : w00208541
    Modify content : Create
2)  Date           : 2015-06-02
    Author         : m00312079
    Modify content : Add session release type
3)  Date           : 2015-06-03
    Author         : l00324781
    Modify content : MMA_TAF_SERVICE_STATUS��Ϣ���
4)  Date           : 2015-06-11
    Author         : w00242748
    Modify content : CDMA Iteration 15 modified
5)  Date           : 2015-08-22
    Author         : y00307564
    Modify content : DTS2015081005519modified
6)  Date           : 2015-09-30
    Author         : j00354216
    Modify content : CDMA Iteration 18 modified
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccHrpdServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU                  *pstHrpdSrvStaInd = VOS_NULL_PTR;
    MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32                enSrvSta;
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enHrpdNetworkExist;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode;
    TAF_SDC_REG_STATUS_ENUM_UINT8                           enRegSta;
    TAF_PH_ACCESS_TECH_ENUM_UINT8                           enAct;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8                        enOldRptSrvStatus;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enOldSubMode;

    /* ����״̬��ʱ��ά�ɲ� */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

    pstHrpdSrvStaInd = (MSCC_MMA_HRPD_SERVICE_STATUS_IND_STRU *)pstMsg;
    enSrvSta         = pstHrpdSrvStaInd->enSrvSta;
    enSysMode        = TAF_SDC_SYS_MODE_BUTT;
    enSubMode        = TAF_SDC_SYS_SUBMODE_BUTT;
    pFuncTafSdcSysmodServiceRegStaUpdate = VOS_NULL_PTR;

    /* �����no rf��־����ֱ�Ӳ����� */
    if (VOS_FALSE == TAF_SDC_GetHrpdRfAvailFlag())
    {
        return VOS_TRUE;
    }

    /* report ^mode */
    enHrpdNetworkExist = TAF_MMA_MapHrpdSrvStaToCdmaNetworkExistance(enSrvSta);
    TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(enHrpdNetworkExist, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

    if ( (TAF_SDC_SYS_MODE_SVLTE == enSysMode)
      || (TAF_SDC_SYS_MODE_LTE == enSysMode) )
    {
        return VOS_TRUE;
    }

    if (TAF_SDC_HRPD_NETWORK_EXIST == enHrpdNetworkExist)
    {
        if (VOS_TRUE == pstHrpdSrvStaInd->ucIsEhrpdSupport)
        {
            enSubMode = TAF_SDC_SYS_SUBMODE_EHRPD;
        }
        else
        {
            enSubMode = TAF_MMA_CovertSubMode_EvdoExist(enSysMode, pstHrpdSrvStaInd->enCurrSessionRelType);
        }
    }

    enOldSubMode = TAF_SDC_GetSysSubMode();


    /* notify APS the service status */
    if (MSCC_MMA_HRPD_SERVICE_STATUS_NORMAL_SERVICE == pstHrpdSrvStaInd->enSrvSta)
    {
        TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_RPT_APS_CL_NO_SERVICE);
        TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_RPT_APS_DO_NO_SERVICE);
        TAF_MMA_GetCLNoServiceDelayRptInfo()->enDelayType   = TAF_MMA_DELAY_CL_REPORT_TYPE_BUTT;

        if (VOS_TRUE == pstHrpdSrvStaInd->ucIsEhrpdSupport)
        {
            TAF_MMA_SndTafCLServiceStatusInd(MMA_TAF_CL_STATUS_EHRPD_NORMAL_SERVICE, pstHrpdSrvStaInd->ucIsNewSession);
        }
        else
        {
            TAF_MMA_SndTafCLServiceStatusInd(MMA_TAF_CL_STATUS_HRPD_NORMAL_SERVICE, pstHrpdSrvStaInd->ucIsNewSession);
        }
    }
    if (TAF_SDC_HRPD_NETWORK_EXIST == enHrpdNetworkExist)
    {
        Mma_ModeChgReport(enSysMode, enSubMode);

        /* SysMode�������ڷ���״̬ˢ�� */
        TAF_SDC_SetSysMode(enSysMode);
        TAF_SDC_SetSysSubMode(enSubMode);
    }

    /* report +CGREG */
    /* when acquire, do not update +cgreg, only ^mode, so
      here only process in normal service and no service */
    if (MSCC_MMA_HRPD_SERVICE_STATUS_NORMAL_SERVICE == enSrvSta)
    {
        enRegSta = TAF_SDC_REG_REGISTERED_HOME_NETWORK;
    }
    else
    {
        enRegSta = TAF_SDC_REG_NOT_REGISTERED_SEARCHING;
    }

    TAF_MMA_ConvertSysSubModeToActForAtCmdCgreg(enSubMode, &enAct);

    enOldRptSrvStatus = TAF_SDC_GetServiceStatus();

    /* update srvstatus and domain */
    TAF_MMA_UpdateHrpdServiceStatusAndDomain(enSysMode, enSrvSta);

    TAF_MMA_ReportPsRegStatusInClMode(enRegSta);

    /* ����״̬�и��£��Ž���ú������� */
    if (enOldRptSrvStatus != TAF_SDC_GetServiceStatus())
    {
        TAF_MMA_ReportHrpdAndLteServiceState();
    }
    else
    {
        /* ����PS�������Ϣ */
        if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            TAF_MMA_UpdateAppPsSrvInfoInClMode();
        }
    }

    /* EHRPD���е��ޣ��������������� */
    if ((TAF_SDC_HRPD_NETWORK_NOT_EXIST != enHrpdNetworkExist)
     || (TAF_SDC_SYS_SUBMODE_EHRPD != enOldSubMode))
    {
        TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeHrpd(enHrpdNetworkExist);

        /* ����SubMode���·����� */
        TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());
    }

    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);

    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   TAF_MMA_RcvMsccHrpdOverheadMsgInd_PreProc
Description     :   Receive and process the MSCC hrpd overhead msg ind
Input parameters:   ulEventType-----message ID +pid
                    pstMsg     -----message content
Outout parameters:  None
Return Value    :   VOS_TRUE------------the current event is processed finished


Modify History  :
1)  Date           : 2015-02-04
    Author         : w00208541
    Modify content : Create
1)  Date           : 2015-06-18
    Author         : l00324781
    Modify content : Iteration12 TAF_SYS_SUBMODE_ENUM_UINT8�޸�ΪTAF_SDC_SYS_SUBMODE_ENUM_UINT8

  3.��    ��   : 2015��11��20��
    ��    ��   : Y00213812
    �޸�����   : �յ�DO��ϵͳ��Ϣ�ݲ��ϱ�^MODE����������sessionЭ�̽�������
                 �ϱ�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccHrpdOverheadMsgInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU *pstRcvMsg = VOS_NULL_PTR;
    TAF_SDC_HRPD_SYS_INFO_STRU          *pstHrpdSysInfo = VOS_NULL_PTR;

    pstRcvMsg = (MSCC_MMA_HRPD_OVERHEAD_MSG_IND_STRU *)pstMsg;
    pstHrpdSysInfo = TAF_SDC_GethrpdSysInfo();

    /* �����no rf��־����ֱ�Ӳ����� */
    if (VOS_FALSE == TAF_SDC_GetHrpdRfAvailFlag())
    {
        return VOS_TRUE;
    }

    /* ��sessionЭ�̽�����������������һ���ϱ� */

    /* ����hrpd��Ϣ������*/
    pstHrpdSysInfo->ucColorCode         = pstRcvMsg->ucUATIColorCode;
    pstHrpdSysInfo->ucSubNetMask        = pstRcvMsg->ucSubNetMask;
    pstHrpdSysInfo->ulMcc               = pstRcvMsg->ulMcc;
    pstHrpdSysInfo->usBandClass         = pstRcvMsg->usBandClass;
    pstHrpdSysInfo->usFreq              = pstRcvMsg->usFreq;
    pstHrpdSysInfo->ulSector24          = pstRcvMsg->ulSector24;

    /* ��ά�ɲ� */
    TAF_MMA_SndOmCdmaStatusInfoReportInd();

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMsccHrpdSysAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetPriCdmaSrvMode
 ��������  : ��ȡ��ǰ�����ȼ��ķ���ģʽ
 �������  : TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
 �������  : ��
 �� �� ֵ  : MMA_TAF_RAT_TYPE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��10��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
MMA_TAF_RAT_TYPE_ENUM_UINT32 TAF_MMA_GetPriCdmaSrvMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
)
{
    switch (enSysMode)
    {
        case TAF_SDC_SYS_MODE_CDMA_1X:
            return MMA_TAF_RAT_TYPE_1X;

        case TAF_SDC_SYS_MODE_EVDO:
            return MMA_TAF_RAT_TYPE_HRPD;

        case TAF_SDC_SYS_MODE_HYBRID:
            return MMA_TAF_RAT_TYPE_HRPD;

        default:
            /* do nothing */
            break;
    }

    return MMA_TAF_RAT_TYPE_NULL;
}



VOS_UINT32 TAF_MMA_RcvMscc1xSystemTimeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_1X_SYSTEM_TIME_IND_STRU   *pst1xSystemTimeInd = VOS_NULL_PTR;

    pst1xSystemTimeInd = (MSCC_MMA_1X_SYSTEM_TIME_IND_STRU *)pstMsg;

    TAF_MMA_ProcessCSystemTime(&(pst1xSystemTimeInd->stSysTime));

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMsccCLSysAcqStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    #if 0
    MSCC_MMA_CL_SYSTEM_ACQUIRE_START_IND_STRU              *pstClSysAcqStartInd;

    pstClSysAcqStartInd = (MSCC_MMA_CL_SYSTEM_ACQUIRE_START_IND_STRU *)pstMsg;
    #endif
    /*TODO*/

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMsccCLSysAcqEndInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    #if 0
    MSCC_MMA_CL_SYSTEM_ACQUIRE_END_IND_STRU                *pstClSysAcqEndInd;

    pstClSysAcqEndInd = (MSCC_MMA_CL_SYSTEM_ACQUIRE_END_IND_STRU *)pstMsg;
    #endif

    /*TODO*/

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_Rcv1xChanSetReq_PreProc
 ��������  : MMAԤ�����д���^1XCHAN��������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_Rcv1xChanSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CFREQ_LOCK_SET_REQ_STRU    *pstCFreqLockSetReq     = VOS_NULL_PTR;
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstTafMmaCFreqLockPara = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstCFreqLockSetReq = (TAF_MMA_CFREQ_LOCK_SET_REQ_STRU *)pstMsg;

    /*  ��ȡȫ�ֱ�����ֵ */
    pstTafMmaCFreqLockPara = TAF_MMA_GetCFreqLockSetPara();

    /*  ������ò����仯��дNV��NTF XSD/HSD */
    if (0 != PS_MEM_CMP(pstTafMmaCFreqLockPara,
                        &pstCFreqLockSetReq->stCFreqLockPara,
                        sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU)))
    {
        #ifndef DMT
        /* wirte CFREQLOCK informations into NV */
        ulRslt = NV_Write(en_NV_Item_CFreqLock_CFG,
                          &pstCFreqLockSetReq->stCFreqLockPara,
                          sizeof(TAF_NVIM_CFREQ_LOCK_CFG_STRU));

        if (NV_OK != ulRslt)
        {
            TAF_MMA_Snd1xChanSetCnf(pstCFreqLockSetReq, VOS_ERR);
            return VOS_TRUE;
        }
        #endif

        /* ����MMA�������Ƶȫ�ֱ��� */
        PS_MEM_CPY(pstTafMmaCFreqLockPara,
                   &pstCFreqLockSetReq->stCFreqLockPara,
                   sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU));

        /* ����MMA_MSCC_CFREQ_LOCK_NTF */
        TAF_MMA_SndMsccCFreqLockNtf(pstTafMmaCFreqLockPara);

    }
    /* ����TAF_MMA_1XCHAN_SET_CNF */
    TAF_MMA_Snd1xChanSetCnf(pstCFreqLockSetReq, VOS_OK);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvQuery1xChanReq_PreProc
 ��������  : MMAԤ�����д���^CVER��ѯ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvQuery1xChanReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_1XCHAN_QUERY_REQ_STRU      *pstAppReqMsg;
    TAF_MMA_1XCHAN_QUERY_CNF_STRU      *pst1xChanCnf;

    pstAppReqMsg     = (TAF_MMA_1XCHAN_QUERY_REQ_STRU *)pstMsg;

    pst1xChanCnf = (TAF_MMA_1XCHAN_QUERY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                        sizeof(TAF_MMA_1XCHAN_QUERY_CNF_STRU));
    if (VOS_NULL_PTR == pst1xChanCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvQuery1xChanReq_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pst1xChanCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_1XCHAN_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pst1xChanCnf->ulReceiverPid          = WUEPS_PID_AT;
    pst1xChanCnf->ulMsgName              = ID_TAF_MMA_1XCHAN_QUERY_CNF;
    pst1xChanCnf->stAtAppCtrl.usClientId = pstAppReqMsg->stCtrl.usClientId;
    pst1xChanCnf->stAtAppCtrl.ucOpId     = pstAppReqMsg->stCtrl.ucOpId;

    if (TAF_SDC_SYS_MODE_CDMA_1X == TAF_SDC_GetSysMode())
    {
        pst1xChanCnf->ulRslt             = VOS_OK;

        pst1xChanCnf->usChannel          = TAF_SDC_Get1xChan();
    }
    else
    {
        pst1xChanCnf->ulRslt             = VOS_ERR;
    }

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pst1xChanCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAtQueryCVER_PreProc
 ��������  : MMAԤ�����д���^CVER��ѯ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvQueryCVerReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CVER_QUERY_REQ_STRU        *pstAppReqMsg;
    TAF_MMA_CVER_QUERY_CNF_STRU        *pstCVerCnf;

    pstAppReqMsg     = (TAF_MMA_CVER_QUERY_REQ_STRU *)pstMsg;

    pstCVerCnf = (TAF_MMA_CVER_QUERY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                       sizeof(TAF_MMA_CVER_QUERY_CNF_STRU));
    if (VOS_NULL_PTR == pstCVerCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvQueryCVerReq_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCVerCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CVER_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstCVerCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstCVerCnf->ulMsgName              = ID_TAF_MMA_CVER_QUERY_CNF;
    pstCVerCnf->stAtAppCtrl.usClientId = pstAppReqMsg->stCtrl.usClientId;
    pstCVerCnf->stAtAppCtrl.ucOpId     = pstAppReqMsg->stCtrl.ucOpId;

    if (TAF_SDC_SYS_MODE_CDMA_1X == TAF_SDC_GetSysMode())
    {
        pstCVerCnf->ulRslt             = VOS_OK;

        pstCVerCnf->enPrevInUse        = TAF_SDC_Get1xPrevInUse();
    }
    else
    {
        pstCVerCnf->ulRslt             = VOS_ERR;
    }

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCVerCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvQueryStateReq_PreProc
 ��������  : MMAԤ�����д���^GETST��ѯ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvQueryStateReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_STATE_QUERY_REQ_STRU       *pstStateMsg         = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstStateMsg  = (TAF_MMA_STATE_QUERY_REQ_STRU *)pstMsg;

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndGetStaQryCnf(&(pstStateMsg->stCtrl),
                                VOS_NULL_PTR,
                                TAF_MMA_APP_OPER_RESULT_FAILURE);

        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstStateMsg->stCtrl,
                       TAF_MMA_OPER_GETSTA_QUERY_REQ,
                       ucCtxIndex);

    if (VOS_TRUE != TAF_MMA_SndMsccHandsetInfoQryReq(MMA_MSCC_HANDSET_INFO_TYPE_STATE))
    {
        TAF_MMA_SndGetStaQryCnf(&(pstStateMsg->stCtrl),
                                VOS_NULL_PTR,
                                TAF_MMA_APP_OPER_RESULT_FAILURE);

        TAF_MMA_ClearOperCtx(ucCtxIndex);

        return VOS_TRUE;
    }

    /* ����������ʱ��TI_TAF_MMA_WAIT_MSCC_STATE_QUERY_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_STATE_QUERY_CNF, TI_TAF_MMA_WAIT_MSCC_STATE_QUERY_CNF_LEN);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvQueryHighVerReq_PreProc
 ��������  : MMAԤ�����д���^CHIGHVER��������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvQueryHighVerReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CHIGHVER_QUERY_REQ_STRU    *pstHVerMsg          = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstHVerMsg  = (TAF_MMA_CHIGHVER_QUERY_REQ_STRU *)pstMsg;

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndCHVerQryCnf(&(pstHVerMsg->stCtrl),
                               TAF_MMA_APP_OPER_RESULT_FAILURE,
                               TAF_MMA_1X_CAS_P_REV_ENUM_BUTT);

        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstHVerMsg->stCtrl,
                       TAF_MMA_OPER_CHVER_QUERY_REQ, ucCtxIndex);

    if (VOS_TRUE != TAF_MMA_SndMsccHandsetInfoQryReq(MMA_MSCC_HANDSET_INFO_TYPE_HVERSION))
    {
        TAF_MMA_SndCHVerQryCnf(&(pstHVerMsg->stCtrl),
                               TAF_MMA_APP_OPER_RESULT_FAILURE,
                               TAF_MMA_1X_CAS_P_REV_ENUM_BUTT);

        TAF_MMA_ClearOperCtx(ucCtxIndex);

        return VOS_TRUE;
    }

    /* ����������ʱ��TI_TAF_MMA_WAIT_MSCC_CHVER_QUERY_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_CHVER_QUERY_CNF, TI_TAF_MMA_WAIT_MSCC_CHVER_QUERY_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccHandsetInfoQryCnf_PreProc
 ��������  : ����MSCC�ϱ��ֻ���Ϣ�Ĵ�����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��22��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccHandsetInfoQryCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU   *pstInfoQryCnf          = VOS_NULL_PTR;

    pstInfoQryCnf   = (MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU *)pstMsg;

    if ( MMA_MSCC_HANDSET_INFO_TYPE_STATE == pstInfoQryCnf->enInfoType)
    {
        /* ͣ��ʱ�� */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_STATE_QUERY_CNF);

        TAF_MMA_CasStateQry_Proc(pstInfoQryCnf->ucCasState,pstInfoQryCnf->ucCasSubSta);
    }
    else
    {
        /* ͣ��ʱ�� */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CHVER_QUERY_CNF);

        TAF_MMA_HighVerQry_Proc(pstInfoQryCnf->enHighVer);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CasStateQry_Proc
 ��������  : ����MSCC�ϱ��ֻ�״̬��Ϣ�Ĵ�����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��22��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_CasStateQry_Proc(
    VOS_UINT8                           ucCasState,
    VOS_UINT8                           ucCasSubSta
)
{
    TAF_MMA_OPER_CTX_STRU                                  *pstMmaOperCtx   = VOS_NULL_PTR;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt;
    TAF_MMA_HANDSET_STATE_STRU                              stHandsetInfo;
    VOS_UINT8                                               ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();
    enRslt          = TAF_MMA_APP_OPER_RESULT_SUCCESS;
    ucCtxIndex      = 0;

    PS_MEM_SET(&stHandsetInfo, 0x00, sizeof(TAF_MMA_HANDSET_STATE_STRU));

    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_GETSTA_QUERY_REQ, &ucCtxIndex))
    {
        /* ȷ�ϴ��ж��߼� */
        if ((MSCC_MMA_1X_CAS_STATE_ENUM_BUTT == ucCasState)
         || (MSCC_MMA_CAS_STA_INVALID_SUBSTA == ucCasSubSta))
        {
            enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
        }

        TAF_MMA_CasStateConvert_Proc(ucCasState, ucCasSubSta, &stHandsetInfo);

        TAF_MMA_SndGetStaQryCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                                &stHandsetInfo,
                                enRslt);

        /* ���CTX������  */
        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }
    else
    {
        MMA_ERRORLOG("TAF_MMA_CasStateQry_Proc:ERROR when get SpecOper");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CasStateConvert_Proc
 ��������  : ����״̬ת��
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��22��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_CasStateConvert_Proc(
    VOS_UINT8                           ucCasState,
    VOS_UINT8                           ucCasSubSta,
    TAF_MMA_HANDSET_STATE_STRU         *pstState
)
{
    MSCC_MMA_1X_CAS_STATE_ENUM_UINT8    enCasSta;

    pstState->ucCasState = ucCasState;

    enCasSta = (MSCC_MMA_1X_CAS_STATE_ENUM_UINT8)ucCasState;

    /*
    //INIT substate
    CDMA_SYS_INIT_SYS_DETERM_SUB_STATE   (0)  MSCC_MMA_1X_CAS_INIT_DETERM_SUB_STATE  (0x01)
    CDMA_SYS_PILOT_CH_ACQ_SUB_STATE Pilot(1)  MSCC_MMA_1X_CAS_PILOT_CH_ACQ_SUB_STATE (0x02)
    CDMA_SYS_SYNC_CH_ACQ_SUB_STATE       (2)  MSCC_MMA_1X_CAS_SYNC_CH_ACQ_SUB_STATE  (0x03)
    CDMA_SYS_TIMING_CHNG_SUB_STATE       (3)  MSCC_MMA_1X_CAS_TIMING_CHNG_SUB_STATE  (0x04)

    //IDLE substae
    CDMA_SYS_IDLE_AWAKE_SUB_STATE        (0)  MSCC_MMA_1X_CAS_IDLE_SUB_STATE         (0x10)
    CDMA_SYS_IDLE_SLEEP_SUB_STATE        (1)

    //ACCESS substae
    CDMA_SYS_UPDATE_OVERHEAD_SUB_STATE          (0) MSCC_MMA_1X_CAS_UPDATE_OVERHEAD_SUB_STATE          (0x20)
    CDMA_SYS_MOB_STATION_ORIG_ATTEMPT_SUB_STATE (1) MSCC_MMA_1X_CAS_MOB_STATION_ORIG_ATTEMPT_SUB_STATE (0x21)
    CDMA_SYS_PAG_RESP_SUB_STATE                 (2) MSCC_MMA_1X_CAS_PAG_RESP_SUB_STATE                 (0x22)
    CDMA_SYS_MOB_STATION_ORDR_RESP_SUB_STATE    (3) MSCC_MMA_1X_CAS_MOB_STATION_ORDR_RESP_SUB_STATE    (0x23)
    CDMA_SYS_REG_ACCESS_SUB_STATE               (4) MSCC_MMA_1X_CAS_REG_ACCESS_SUB_STATE               (0x24)
    CDMA_SYS_MOB_STATION_MSG_TRANS_SUB_STATE    (5) MSCC_MMA_1X_CAS_MOB_STATION_MSG_TRANS_SUB_STATE    (0x25)
    CDMA_SYS_PACA_CANCEL_SUB_STATE              (6)

    //TRAFFIC CAS sub state
    CDMA_SYS_TCH_INIT_SUB_STATE Traffic channel    (0)  MSCC_MMA_1X_CAS_TCH_INIT_SUB_STATE      (0x30)
    CDMA_SYS_WAIT_FOR_ORDER_SUB_STATE              (1)  MSCC_MMA_1X_CALL_STATE_WAIT_FOR_ORDER   (0x00)
    CDMA_SYS_WAIT_FOR_MOB_STATION_ANSWER_SUB_STATE (2)  MSCC_MMA_1X_CALL_STATE_WAIT_FOR_ANSWER  (0x01)
    CDMA_SYS_CONVERSATION_SUB_STATE                (3)  MSCC_MMA_1X_CALL_STATE_CONVERSATION     (0x02)
    CDMA_SYS_REL_SUB_STATE                         (4)  MSCC_MMA_1X_CAS_REL_SUB_STATE           (0x31)

    //NO SERVICE
    CDMA_SYS_WAIT_FOR_SERVICE_SUB_STATE   (0)   MSCC_MMA_1X_CAS_WAIT_FOR_SERVICE_SUB_STATE (0x40)
    */

    switch (enCasSta)
    {
        case MSCC_MMA_1X_CAS_INIT_STATE:
            pstState->ucCasSubSta = (ucCasSubSta & 0x0F) - 0x01;
            break;

        case MSCC_MMA_1X_CAS_IDLE_STATE:
        case MSCC_MMA_1X_CAS_ACCESS_STATE:
        case MSCC_MMA_1X_CAS_NO_SERVICE_STATE:
            pstState->ucCasSubSta = (ucCasSubSta & 0x0F);
            break;

        case MSCC_MMA_1X_CAS_TCH_STATE:
            /*cas �ϱ�*/
            if (MSCC_MMA_1X_CAS_TCH_INIT_SUB_STATE == ucCasSubSta)
            {
                pstState->ucCasSubSta = (ucCasSubSta & 0x0F);
            }
            else if (MSCC_MMA_1X_CAS_REL_SUB_STATE == ucCasSubSta)
            {
                pstState->ucCasSubSta = (ucCasSubSta & 0x0F) + 0x03 ;
            }
            /*xcc �ϱ�*/
            else if (MSCC_MMA_CAS_STA_INVALID_SUBSTA != ucCasSubSta)
            {
                pstState->ucCasSubSta = ucCasSubSta + 1;
            }
            else
            {
                pstState->ucCasSubSta = ucCasSubSta;
            }
            break;

        default:
            pstState->ucCasSubSta = ucCasSubSta;
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_HighVerQry_Proc
 ��������  : ����MSCC�ϱ��ֻ��汾��Ϣ�Ĵ�����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��22��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_HighVerQry_Proc(
    MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8    enHighVer
)
{
    TAF_MMA_OPER_CTX_STRU                                  *pstMmaOperCtx   = VOS_NULL_PTR;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt;
    TAF_MMA_1X_CAS_P_REV_ENUM_UINT8                         enHVer;
    VOS_UINT8                                               ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();
    enRslt          = TAF_MMA_APP_OPER_RESULT_SUCCESS;
    ucCtxIndex      = 0;

    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CHVER_QUERY_REQ, &ucCtxIndex))
    {
        enHVer = (TAF_MMA_1X_CAS_P_REV_ENUM_UINT8)enHighVer;

        /* ȷ�ϴ��ж��߼� */
        if (TAF_MMA_1X_CAS_P_REV_ENUM_BUTT == enHVer)
        {
            enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
        }

        TAF_MMA_SndCHVerQryCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                               enHVer,
                               enRslt);

        /* ���CTX������  */
        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }
    else
    {
        MMA_ERRORLOG("TAF_MMA_HighVerQry_Proc:ERROR when get SpecOper");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccStateQryCnfExpired_PreProc
 ��������  : MMAԤ�����д���^GETST��ѯ���ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccStateQryCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_GETSTA_QUERY_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_GETSTA_QUERY_REQ, &ucCtxIndex))
    {
        TAF_MMA_SndGetStaQryCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                                VOS_NULL_PTR,
                                TAF_MMA_APP_OPER_RESULT_FAILURE);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccHVerQryCnfExpired_PreProc
 ��������  : MMAԤ�����д���^CHIGHVER��ѯ���ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccHVerQryCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_CHVER_QUERY_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CHVER_QUERY_REQ, &ucCtxIndex))
    {
        TAF_MMA_SndCHVerQryCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                               TAF_MMA_APP_OPER_RESULT_FAILURE,
                               TAF_MMA_1X_CAS_P_REV_ENUM_BUTT);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvHsmHrpdSysInfoInd_PreProc
 ��������  : MMA�յ�HSM��hrpd��sys info�ϱ��������ڿ�ά�ɲ�
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��4��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvHsmHrpdSysInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SDC_HRPD_SYS_INFO_STRU         *pSdchrpdSysInfo;
    HSM_MMA_HRPD_SYS_INFO_IND_STRU     *pRcvMsg = VOS_NULL_PTR;

    pRcvMsg = (HSM_MMA_HRPD_SYS_INFO_IND_STRU*)pstMsg;


    pSdchrpdSysInfo = TAF_SDC_GethrpdSysInfo();

    pSdchrpdSysInfo->ulSessionSeed = pRcvMsg->ulSessionSeed;
    pSdchrpdSysInfo->ucSessionStatus = TAF_MMA_MapHsmSessionStatus(pRcvMsg->enSessionStatus);
    PS_MEM_CPY(pSdchrpdSysInfo->aucCurUATI, pRcvMsg->aucCurUATI, NAS_OM_MMA_UATI_OCTET_LENGTH);

    TAF_MMA_SndOmCdmaStatusInfoReportInd();
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvHsmHardwareSysInfoInd_PreProc
 ��������  : ����HSM������HARDWARE INFO��SDC
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��6��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_MMA_RcvHsmHardwareSysInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_MMA_HARDWARE_SYS_INFO_IND_STRU *pRcvMsg = VOS_NULL_PTR;

    pRcvMsg = (HSM_MMA_HARDWARE_SYS_INFO_IND_STRU*)pstMsg;

    PS_MEM_CPY(TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.aucMeId, pRcvMsg->aucMeId, NAS_OM_MMA_MEID_OCTET_NUM);
    TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.ulEsn = pRcvMsg->ulEsn;
    TAF_SDC_GetSysInfo()->enModemId = pRcvMsg->enModemId;

    PS_MEM_CPY(TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.aucRuimid, pRcvMsg->aucRuimid, TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT);


    TAF_MMA_SndOmCdmaStatusInfoReportInd();
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvOmCdmaStatusInfoReportReq_PreProc
 ��������  : �յ�OM��cdma��ά�ɲ��ѯ������Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��4��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvOmCdmaStatusInfoReportReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_STRU  *pRcvMsg = VOS_NULL_PTR;
    VOS_UINT32                                    ulRptPeriod;

    pRcvMsg = (OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ_STRU*)pstMsg;

    ulRptPeriod = pRcvMsg->ulRptPeriod;

    if(OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_NOT_REPORT == pRcvMsg->enCmd)
    {
        /* �����־λ����ֹ�����ϱ�,���������ϱ���ʱ����Ϊtrue */
        TAF_SDC_GetSdcCtx()->stCdmaMntn.ulCdmaStatusReportSuport = VOS_FALSE;
        /*Stop timer if the timer is running*/
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_FREQUENCE_OF_QRY_CDMA_SYS_INFO))
        {
            TAF_MMA_StopTimer(TI_TAF_MMA_FREQUENCE_OF_QRY_CDMA_SYS_INFO);
        }

    }
    else if (OM_NAS_MMA_CDMA_STATUS_REPORT_CMD_FOREVER == pRcvMsg->enCmd)
    {
        /* Check the rpt period*/
        if (0 == pRcvMsg->ulRptPeriod)
        {
            ulRptPeriod = TI_TAF_MMA_DEFAULT_FREQUENCE_OF_QRY_CDMA_SYS_INFO_LEN;
        }
        /*start timer,and save rpt period */
        TAF_MMA_StartTimer(TI_TAF_MMA_FREQUENCE_OF_QRY_CDMA_SYS_INFO, ulRptPeriod);
        TAF_SDC_SetCdmaStatusReportPeriod(ulRptPeriod);

        /* �����־λ���޸������ϱ���־λ */
        TAF_SDC_GetSdcCtx()->stCdmaMntn.ulCdmaStatusReportSuport = VOS_TRUE;
    }
    else
    {
        /* �����־λ����ֹ�����ϱ�,���������ϱ���ʱ����Ϊtrue */
        TAF_SDC_GetSdcCtx()->stCdmaMntn.ulCdmaStatusReportSuport = VOS_FALSE;
    }

    TAF_MMA_SndOmCdmaStatusReportCnf(NAS_OM_MMA_CDMA_STATUS_REPORT_RESULT_SUCC, pRcvMsg);
    TAF_MMA_SndOmCdmaStatusInfoReportInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiCdmaSysInfoReport_PreProc
 ��������  : ��ʱ�ϱ�cdma sysinfo��om
 �������  :  VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiCdmaSysInfoReport_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SndOmCdmaStatusInfoReportInd();
    TAF_MMA_StartTimer(TI_TAF_MMA_FREQUENCE_OF_QRY_CDMA_SYS_INFO,
                       TAF_SDC_GetCdmaStatusReportPeriod());

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMscc1XSidNidInd_PreProc
 ��������  : ����mscc��������sid��nid�����ϱ���Ϣ
 �������  :  VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��9��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�
  3.��    ��   : 2015��12��15��
    ��    ��   : l00359089
    �޸�����   : SID�ϱ�������ʱ�ϱ�����, ��SID ��ֵ������ pstSdcCtx->stNetworkInfo.lSid ��
  4.��    ��   : 2015��12��10��
    ��    ��   : l00324781
    �޸�����   : CL_MUTIMODE_OPTIMIZE�޸�

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMscc1XSidNidInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_1X_SID_NID_IND_STRU       *pstRcvMsg =  VOS_NULL_PTR;

    TAF_SDC_CTX_STRU                   *pstSdcCtx = VOS_NULL_PTR;
    VOS_INT32                           lSidTmp;

    pstRcvMsg = (MSCC_MMA_1X_SID_NID_IND_STRU *)pstMsg;
    pstSdcCtx = TAF_SDC_GetSdcCtx();
    lSidTmp   = (0x00000000 | pstRcvMsg->usSid);

    if ((VOS_TRUE == TAF_MMA_IsSidChangeNeedRpt())
     && (lSidTmp  != pstSdcCtx->stNetworkInfo.lSid))
    {
        /* �ϱ�AT���� */
        TAF_MMA_ReportCSid(lSidTmp);
    }

    pstSdcCtx->stNetworkInfo.lSid = lSidTmp;

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvQuitCallBackReq_PreProc
 ��������  : AT QCCB������
 �������  :  VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��9��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvQuitCallBackInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_QUIT_CALLBACK_SET_REQ_STRU *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (TAF_MMA_QUIT_CALLBACK_SET_REQ_STRU *)pstMsg;

    TAF_MMA_SndMsccQuitCallBackNtf();

    /*ֱ�ӻظ�cnf��Ϣ */
    TAF_MMA_SndQuitCallBackCnf(&(pstRcvMsg->stCtrl), TAF_ERR_NO_ERROR);

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMscc1XEmcCallBackNtf_PreProc
 ��������  : xsd call back  ͸���ϱ�
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                 �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMscc1XEmcCallBackNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU *pstRcvMsg =  VOS_NULL_PTR;
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo;

    pstRcvMsg = (MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU *)pstMsg;
    pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    /*���µ�ǰ�Ƿ���callbackģʽ��Ϣ*/
    pstSdc1xSysInfo->ulIsInEmcCallBack = (VOS_UINT32)(pstRcvMsg->enCallBackState);

    TAF_MMA_Report1xEmcCallBack((VOS_UINT32)pstRcvMsg->enCallBackState);

    if (VOS_FALSE == pstSdc1xSysInfo->ulIsInEmcCallBack)
    {
        pstSdc1xSysInfo->ucIsEmcCallExistFlg = VOS_FALSE;
    }

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvSetCSidListReq_PreProc
 ��������  : AT CSIDLIST req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��13��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSetCSidListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SET_CSIDLIST_REQ_STRU     *pstSndMsg = VOS_NULL_PTR;
    TAF_MMA_CSIDLIST_SET_REQ_STRU      *pstRcvMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstRcvMsg = (TAF_MMA_CSIDLIST_SET_REQ_STRU *)pstMsg;

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    if (VOS_TRUE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        /* �����ڴ�  */
        pstSndMsg = (MMA_MSCC_SET_CSIDLIST_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA,
                               sizeof(MMA_MSCC_SET_CSIDLIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);


        if ( VOS_NULL_PTR == pstSndMsg )
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvSetCSidListReq_PreProc:ERROR: Memory Alloc Error for pMsg");
            return VOS_ERR;
        }

        PS_MEM_SET((VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMA_MSCC_SET_CSIDLIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

        TAF_MMA_SetOperCtx(pstRcvMsg->stCtrl,
                       TAF_MMA_OPER_SET_CSIDLIST_REQ, ucCtxIndex);

        pstSndMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
        pstSndMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MSCC;
        pstSndMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
        pstSndMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
        pstSndMsg->stMsgHeader.ulLength         = sizeof(MMA_MSCC_SET_CSIDLIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
        pstSndMsg->stMsgHeader.ulMsgName        = ID_MMA_MSCC_SET_CSIDLIST_REQ;
        PS_MEM_CPY(&pstSndMsg->stSidWhiteList, &pstRcvMsg->stWhiteSidInfo, sizeof(TAF_MMA_OPER_LOCK_WHITE_SID_STRU));
        /* ����VOS����ԭ�� */
        PS_SEND_MSG( WUEPS_PID_MMA, pstSndMsg );

    }
    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    else
    {
        TAF_MMA_SndSetCSidListCnf(&(pstRcvMsg->stCtrl), TAF_ERR_ERROR);
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccSetCSidListCnf
 ��������  : �յ�mscc ����csidlist set�Ľ����Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��13��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccSetCSidListCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_SET_CSIDLIST_CNF_STRU     *pstRcvMsg = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    pstRcvMsg = (MSCC_MMA_SET_CSIDLIST_CNF_STRU *)pstMsg;

    if (VOS_TRUE == pstRcvMsg->ulRslt)
    {
        enErrorCode = TAF_ERR_NO_ERROR;
    }
    else
    {
        enErrorCode = TAF_ERR_ERROR;
    }
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_SET_CSIDLIST_REQ, &ucCtxIndex))
    {
        /*  �ظ�CSIDLIST set cnf*/
        TAF_MMA_SndSetCSidListCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), enErrorCode);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvQryEmcCallBackMode_PreProc
 ��������  : ��ѯ��ǰ�Ƿ��ڽ�����callbackģʽ��
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvQryEmcCallBackMode_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_1X_EMC_CALL_BACK_QRY_REQ_STRU           *pstRcvMsg;
    TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF_STRU           *pstSndMsg;
    TAF_SDC_1X_SYS_INFO_STRU                        *pstSdc1xSysInfo;

    pstRcvMsg       = (TAF_MMA_1X_EMC_CALL_BACK_QRY_REQ_STRU *)pstMsg;
    pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();
    pstSndMsg = (TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                        sizeof(TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        MMA_ERRORLOG("TAF_MMA_RcvQryEmcCallBackMode_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstSndMsg->ulReceiverPid          = WUEPS_PID_AT;
    pstSndMsg->ulMsgName              = ID_TAF_MMA_1X_EMC_CALL_BACK_QRY_CNF;
    PS_MEM_CPY(&pstSndMsg->stCtrl, &pstRcvMsg->stCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->ucIsInCallBackMode     = pstSdc1xSysInfo->ulIsInEmcCallBack;
    pstSndMsg->enErrorCode            = TAF_ERR_NO_ERROR;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvXcc1xCallStateInd_PreProc
 ��������  : XCC 1x call state �ϱ���Ϣ����
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvXcc1xCallStateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_MMA_1X_CALL_STATE_IND_STRU     *pstRcvMsg = VOS_NULL_PTR;
    NAS_OM_1X_CALL_STATE_ENUM_UINT8     enPreXcallState;

    pstRcvMsg = (XCC_MMA_1X_CALL_STATE_IND_STRU *)pstMsg;
    enPreXcallState = TAF_SDC_GetXCallState();

    switch (pstRcvMsg->enCallState)
    {

        case XCC_MMA_1X_CALL_STATE_IDLE:
            TAF_SDC_SetXCaLLState(CDMA_1X_CALL_STATE_IDLE);
            break;
        case XCC_MMA_1X_CALL_STATE_ORIG_CALL:
            TAF_SDC_SetXCaLLState(CDMA_1X_CALL_STATE_ORIGNALING_CALL);
            break;
        case XCC_MMA_1X_CALL_STATE_INCOMMING_CALL:
            TAF_SDC_SetXCaLLState(CDMA_1X_CALL_STATE_INCOMING_CALL);
            break;
        case XCC_MMA_1X_CALL_STATE_CONVERSATION:
            TAF_SDC_SetXCaLLState(CDMA_1X_CALL_STATE_CONVERSATION);
            break;
        default :
            TAF_SDC_SetXCaLLState(CDMA_1X_CALL_STATE_IDLE);
    }

    /* CALL STATE �仯���ϱ�һ��*/
    if (TAF_SDC_GetXCallState() != enPreXcallState)
    {
        TAF_MMA_SndOmCdmaStatusInfoReportInd();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvXsdUeStateInd_PreProc
 ��������  : �յ�XSD STATE IND��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��11��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccUeStateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_UE_STATE_IND_STRU         *pstUeStateInd;

    pstUeStateInd       = (MSCC_MMA_UE_STATE_IND_STRU*)pstMsg;

    /* ����ǰ��UE״̬����SDCȫ�ֱ����� */
    TAF_SDC_SetCdmaCurUeState((TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8)pstUeStateInd->ucUeMainState);

    /* �����п��ܽoTAF�ڲ�PID����STATE IND */

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcHdrCsqSetReq_PreProc
 ��������  : ����TAF�ź�ǿ���ϱ���������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcHdrCsqSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_HDR_CSQ_SET_REQ_STRU       *pstMmaHdrCsqReqMsg  = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx       = VOS_NULL_PTR;
    NAS_MSCC_PIF_HDR_CSQ_SET_PARA_STRU  stHdrCsqSetPara;
    VOS_UINT8                           ucCtxIndex          = 0;

    pstMmaHdrCsqReqMsg  = (TAF_MMA_HDR_CSQ_SET_REQ_STRU*)pstMsg;

    /* ���ƽ̨������֧��DO�����·����ֱ�ӷ���ʧ�� */
    if (VOS_FALSE == TAF_SDC_IsPlatformSupportHrpd())
    {
        TAF_MMA_SndHdrCsqSetCnf(&(pstMmaHdrCsqReqMsg->stCtrl),
                                TAF_MMA_APP_OPER_RESULT_FAILURE);

        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndHdrCsqSetCnf(&(pstMmaHdrCsqReqMsg->stCtrl),
                                TAF_MMA_APP_OPER_RESULT_FAILURE);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstMmaHdrCsqReqMsg->stCtrl,
                       TAF_MMA_OPER_HDR_CSQ_SET_REQ,
                       ucCtxIndex);

    /*�����Ϣ*/
    PS_MEM_SET(&stHdrCsqSetPara, 0, sizeof(NAS_MSCC_PIF_HDR_CSQ_SET_PARA_STRU));
    stHdrCsqSetPara.ucTimeInterval  = pstMmaHdrCsqReqMsg->stHdrCsqSetting.ucTimeInterval;
    stHdrCsqSetPara.ucRssiThreshold = pstMmaHdrCsqReqMsg->stHdrCsqSetting.ucRssiThreshold;
    stHdrCsqSetPara.ucSnrThreshold  = pstMmaHdrCsqReqMsg->stHdrCsqSetting.ucSnrThreshold;
    stHdrCsqSetPara.ucEcioThreshold = pstMmaHdrCsqReqMsg->stHdrCsqSetting.ucEcioThreshold;


    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();
    pstMmaOperCtx[ucCtxIndex].pPara = (TAF_MMA_HDR_CSQ_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_HDR_CSQ_PARA_STRU));

    if (VOS_NULL_PTR == pstMmaOperCtx[ucCtxIndex].pPara)
    {
        TAF_MMA_SndHdrCsqSetCnf(&(pstMmaHdrCsqReqMsg->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
        return VOS_TRUE;
    }

    if (VOS_TRUE != TAF_MMA_SndMsccHdrCsqSetReq(stHdrCsqSetPara))
    {
        TAF_MMA_SndHdrCsqSetCnf(&(pstMmaHdrCsqReqMsg->stCtrl),
                                TAF_MMA_APP_OPER_RESULT_FAILURE);

        PS_MEM_FREE(WUEPS_PID_MMA, pstMmaOperCtx[ucCtxIndex].pPara);
        pstMmaOperCtx[ucCtxIndex].pPara = VOS_NULL_PTR;

        TAF_MMA_ClearOperCtx(ucCtxIndex);

        return VOS_TRUE;
    }

    PS_MEM_CPY(pstMmaOperCtx[ucCtxIndex].pPara, &pstMmaHdrCsqReqMsg->stHdrCsqSetting, sizeof(TAF_MMA_HDR_CSQ_PARA_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccHdrCsqSetCnf_PreProc
 ��������  : ����HSD�ź�ǿ���ϱ����õĴ�����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccHdrCsqSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_HDR_CSQ_SET_CNF_STRU        *pstHdrCsqCnf          = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU                *pstMmaOperCtx          = VOS_NULL_PTR;
    TAF_MMA_HDR_CSQ_PARA_STRU            *pstMmaHdrCsqPara      = VOS_NULL_PTR;
    TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU   *pstSdcHrpdSigQualityInfo = VOS_NULL_PTR;
    VOS_UINT8                             ucCtxIndex;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32   enRslt;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();
    enRslt          = TAF_MMA_APP_OPER_RESULT_SUCCESS;

    pstHdrCsqCnf   = (MSCC_MMA_HDR_CSQ_SET_CNF_STRU *)pstMsg;

    if ( NAS_MSCC_PIF_HDR_CSQ_SET_RESULT_SUCC != pstHdrCsqCnf->enRslt )
    {
        enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
    }

    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_HDR_CSQ_SET_REQ, &ucCtxIndex))
    {
        /* ����HDRCSQ�����ûظ� */
        TAF_MMA_SndHdrCsqSetCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                                enRslt);

        if (TAF_MMA_APP_OPER_RESULT_SUCCESS == enRslt)
        {

            pstMmaHdrCsqPara  = (TAF_MMA_HDR_CSQ_PARA_STRU *)pstMmaOperCtx[ucCtxIndex].pPara;
            /*����SDC��ȫ�ֱ���*/
            pstSdcHrpdSigQualityInfo                        = TAF_SDC_GetHrpdSigQualityInfo();

            pstSdcHrpdSigQualityInfo->enMode                = pstMmaHdrCsqPara->enMode;
            pstSdcHrpdSigQualityInfo->ucRssiThreshold       = pstMmaHdrCsqPara->ucRssiThreshold;
            pstSdcHrpdSigQualityInfo->ucSnrThreshold        = pstMmaHdrCsqPara->ucSnrThreshold;
            pstSdcHrpdSigQualityInfo->ucEcioThreshold       = pstMmaHdrCsqPara->ucEcioThreshold;
            pstSdcHrpdSigQualityInfo->ucTimeInterval        = pstMmaHdrCsqPara->ucTimeInterval;
        }

        /* ���CTX������  */
        TAF_MMA_ClearOperCtx(ucCtxIndex);
        PS_MEM_FREE(WUEPS_PID_MMA, pstMmaHdrCsqPara);
    }
    else
    {
        MMA_ERRORLOG("TAF_MMA_RcvMsccHdrCsqSetCnf_PreProc:ERROR");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccHdrCsqInd_PreProc
 ��������  : �����ϱ��ź�ǿ��
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccHdrCsqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_HDR_CSQ_IND_STRU            *psHdrCsqInd          = VOS_NULL_PTR;
    TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU   *pstSdcHrpdSigQualityInfo = VOS_NULL_PTR;
    TAF_MMA_HDR_CSQ_MODE_ENUM_UINT8       enMode;

    psHdrCsqInd = (MSCC_MMA_HDR_CSQ_IND_STRU *)pstMsg;

    /* �����no rf��־����ֱ�Ӳ����� */
    if (VOS_FALSE == TAF_SDC_GetHrpdRfAvailFlag())
    {
        return VOS_TRUE;
    }

    /* ����ȫ�ֱ��� */
    pstSdcHrpdSigQualityInfo                 = TAF_SDC_GetHrpdSigQualityInfo();
    pstSdcHrpdSigQualityInfo->sHdrRssi       = psHdrCsqInd->sHrpdRssi;
    pstSdcHrpdSigQualityInfo->sHdrSnr        = psHdrCsqInd->sHrpdSnr;
    pstSdcHrpdSigQualityInfo->sHdrEcio       = psHdrCsqInd->sHrpdEcio;

    enMode = pstSdcHrpdSigQualityInfo->enMode;

    enMode = pstSdcHrpdSigQualityInfo->enMode;

    if (TAF_MMA_HDR_CSQ_MODE_ENABLE == enMode)
    {
        /* ����HDR_CSQ�������ϱ�*/

        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            pstSdcHrpdSigQualityInfo->ucIsDelayReportEnable  =  VOS_TRUE;

            /* AT������ʱ�ϱ������� */
            TAF_MMA_LogDelayReportInfo(TAF_MMA_LOG_DELAY_RPT_HDRCSQ);
        }
        else
        {
            TAF_MMA_SndHdrCsqInd( pstSdcHrpdSigQualityInfo->sHdrRssi,
                                  pstSdcHrpdSigQualityInfo->sHdrSnr,
                                  pstSdcHrpdSigQualityInfo->sHdrEcio);
        }

    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvHdrCsqQryReq_PreProc
 ��������  : ��ѯ�ź�ǿ���ϱ�������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvHdrCsqQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU *pstHdrCsqQryCnf           = VOS_NULL_PTR;
    TAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU *pstRcvMsg                 = VOS_NULL_PTR;
    TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU   *pstSdcHrpdSigQualityInfo  = VOS_NULL_PTR;


    pstRcvMsg = (TAF_MMA_HDR_CSQ_QRY_SETTING_REQ_STRU *)pstMsg;

    pstHdrCsqQryCnf = (MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                sizeof(MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU));
    if (VOS_NULL_PTR == pstHdrCsqQryCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvHdrCsqQryReq_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstHdrCsqQryCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_TAF_HDR_CSQ_QRY_SETTING_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstHdrCsqQryCnf->ulReceiverPid          = pstRcvMsg->stCtrl.ulModuleId;
    pstHdrCsqQryCnf->ulMsgName              = ID_MMA_TAF_HDR_CSQ_QRY_SETTING_CNF;

    PS_MEM_CPY(&pstHdrCsqQryCnf->stCtrl, &pstRcvMsg->stCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstSdcHrpdSigQualityInfo                  = TAF_SDC_GetHrpdSigQualityInfo();

    pstHdrCsqQryCnf->stHdrCsq.enMode          = pstSdcHrpdSigQualityInfo->enMode;
    pstHdrCsqQryCnf->stHdrCsq.ucTimeInterval  = pstSdcHrpdSigQualityInfo->ucTimeInterval;
    pstHdrCsqQryCnf->stHdrCsq.ucRssiThreshold = pstSdcHrpdSigQualityInfo->ucRssiThreshold;
    pstHdrCsqQryCnf->stHdrCsq.ucSnrThreshold  = pstSdcHrpdSigQualityInfo->ucSnrThreshold;
    pstHdrCsqQryCnf->stHdrCsq.ucEcioThreshold = pstSdcHrpdSigQualityInfo->ucEcioThreshold;
    pstHdrCsqQryCnf->sHdrRssi                 = pstSdcHrpdSigQualityInfo->sHdrRssi;
    pstHdrCsqQryCnf->sHdrSnr                  = pstSdcHrpdSigQualityInfo->sHdrSnr;
    pstHdrCsqQryCnf->sHdrEcio                 = pstSdcHrpdSigQualityInfo->sHdrEcio;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstHdrCsqQryCnf);

    return VOS_TRUE;
}



/*****************************************************************************
  �� �� ��  : TAF_MMA_RcvTiCLDelayRptCsServiceStatusExpired_PreProc
  ��������  : TI_TAF_MMA_CDMA_CS_SERVICE_STATUS_DELAY_REPORT��ʱ����
  �������  : ulEventType
             pstMsg

  �������  : ��
  �� �� ֵ  : VOS_TRUE
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��9��30��
  ��    ��  : j00354216
  �޸�����  : CDMA Iteration 18 ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiCLDelayRptCsServiceStatusExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enNetCsRegStatus;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enNetSrvSta;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enAppNetSrvSta;

    /* ����״̬��ʱ��ά�ɲ� */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

    /*PS���ӳٶ�ʱ��������ʱ,�����ϱ���������ϱ��ܵķ���״̬��ֻ����CS��������Ϣ*/
    if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
    {
        /*����CS����Ҫ�ϱ�������*/
        TAF_MMA_DelayReportCsReferCmdInClMode();

        /*ע���ϱ��Ƿ��ϱ��Ĵ���*/
        TAF_MMA_SndCsRegStatusInClMode();

        /*����CS���ע��״̬*/
        enNetCsRegStatus    = TAF_SDC_GetCsRegStatus();
        TAF_SDC_SetAppCsRegStatus(enNetCsRegStatus);

        /*����CS����Ϣ*/
        TAF_MMA_UpdateAppCsSrvInfoInClMode();

    }
    else
    {
        /*PS���ӳٶ�ʱ����������ʱ�������ϱ����������CS����Ϣ���ϱ��ķ���״̬*/
        /*����CS����Ҫ�ϱ�������*/
        TAF_MMA_DelayReportCsReferCmdInClMode();

        /* CS��ע���ϱ��Ƿ��ϱ��Ĵ���*/
        TAF_MMA_SndCsRegStatusInClMode();

        /*����CS���ע��״̬*/
        enNetCsRegStatus    = TAF_SDC_GetCsRegStatus();
        TAF_SDC_SetAppCsRegStatus(enNetCsRegStatus);

        /* ����״̬�ϱ����� */
        enNetSrvSta        = TAF_SDC_GetServiceStatus();
        enAppNetSrvSta     = TAF_SDC_GetAppServiceStatus();

        /* ����coverity�澯 */
        if (TAF_SDC_REPORT_SRVSTA_BUTT == enAppNetSrvSta)
        {
            TAF_WARNING_LOG(WUEPS_PID_MMA,
                            "TAF_MMA_RcvTiCLDelayRptCsServiceStatusExpired_PreProc: Service Status is BUTT!");
        }

        TAF_MMA_ProcServiceStatusReport(enNetSrvSta, enAppNetSrvSta);
        /* ���·���״̬ */
        TAF_SDC_SetAppServiceStatus(enNetSrvSta);

        /*����CS����Ϣ*/
        TAF_MMA_UpdateAppCsSrvInfoInClMode();
    }

    TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode1x(TAF_SDC_1X_NETWORK_NOT_EXIST);

    /* ����SubMode���·����� */
    TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());

    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);

    return VOS_TRUE;
}

/*****************************************************************************
  �� �� ��  : TAF_MMA_RcvTiCLDelayRptPsServiceStatusExpired_PreProc
  ��������  : TI_TAF_MMA_CDMA_PS_SERVICE_STATUS_DELAY_REPORT��ʱ����
  �������  : ulEventType
             pstMsg

  �������  : ��
  �� �� ֵ  : VOS_TRUE
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��9��30��
  ��    ��  : j00354216
  �޸�����  : CDMA Iteration 18 ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiCLDelayRptPsServiceStatusExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enNetPsRegStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsSrvStatus;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enNetSrvSta;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enAppNetSrvSta;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8          enSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc    pFuncTafSdcSysmodServiceRegStaUpdate;

    enSysMode                               = TAF_SDC_SYS_MODE_BUTT;
    enSubMode                               = TAF_SDC_GetSysSubMode();
    pFuncTafSdcSysmodServiceRegStaUpdate    = VOS_NULL_PTR;

    /* ����״̬��ʱ��ά�ɲ� */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

    /* EHRPD���յ�Acquire End Ind��ʱ���� */
    if (TAF_SDC_SYS_SUBMODE_EHRPD != enSubMode)
    {
        TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_HRPD_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

        /* SysMode�������ڷ���״̬ˢ�� */
        TAF_SDC_SetSysMode(enSysMode);
        TAF_SDC_SetSysSubMode(enSubMode);

        Mma_ModeChgReport(enSysMode, enSubMode);
    }

    /*CS���ӳٶ�ʱ��������ʱ,�����ϱ���������ϱ��ܵķ���״̬��ֻ����PS��������Ϣ*/
    if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
    {
        TAF_MMA_SndPsRegStatusInClMode();

        enSysMode = TAF_SDC_GetSysMode();

        pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
        pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

        /*LTE�£���Ҫ����plmn��Ϣ���ź�����*/
        if ((TAF_SDC_SYS_MODE_LTE == enSysMode)
         || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
        {
            PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.stServPlmnInfo.stServicePlmnId),
                       &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId),
                       sizeof(TAF_SDC_PLMN_ID_STRU));

            pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
            pstAppNwInfo->stAppSysInfo.stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
            pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
            pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
            pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

            /* �ź��������µ�AppNetworkInfo */
            PS_MEM_CPY(&(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo),
                        &(pstCurNwInfo->stSigQuaInfo.st3GppRssiInfo),
                        sizeof(TAF_SDC_3GPP_RSSI_INFO_STRU));
        }

        /* ϵͳģʽ��ϵͳ��ģʽ���µ�AppNetworkInfo */
        if (TAF_SDC_SYS_SUBMODE_EHRPD != TAF_SDC_GetAppNetworkInfo()->stAppSysInfo.enSysSubMode)
        {
            /* PS��ʱ�ϱ���ʱ����ʱ��CS��ʱ�ϱ���ʱ���������У�APP�д��ģʽֻ������SVLTE����hybird */
            pstAppNwInfo->stAppSysInfo.enSysMode    = TAF_SDC_SYS_MODE_CDMA_1X;
            pstAppNwInfo->stAppSysInfo.enSysSubMode = TAF_SDC_SYS_SUBMODE_CDMA_1X;
         }

        /* ����SubMode���·����� */
        TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());

        /*����PSע��״̬*/
        enNetPsRegStatus    = TAF_SDC_GetPsRegStatus();
        TAF_SDC_SetAppPsRegStatus(enNetPsRegStatus);

        /*����PS�����״̬*/
        enPsSrvStatus = TAF_SDC_GetPsServiceStatus();
        TAF_SDC_SetAppPsServiceStatus(enPsSrvStatus);
    }
    else
    {
        /*PS��ע��״̬���ϱ�����*/
        TAF_MMA_SndPsRegStatusInClMode();
        /*����PSע��״̬*/
        TAF_SDC_SetAppPsRegStatus(TAF_SDC_GetPsRegStatus());

        /* ����״̬�ϱ����� */
        enNetSrvSta        = TAF_SDC_GetServiceStatus();
        enAppNetSrvSta     = TAF_SDC_GetAppServiceStatus();

        /* ����coverity�澯 */
        if (TAF_SDC_REPORT_SRVSTA_BUTT == enAppNetSrvSta)
        {
            TAF_WARNING_LOG(WUEPS_PID_MMA,
                            "TAF_MMA_RcvTiCLDelayRptPsServiceStatusExpired_PreProc: Service Status is BUTT!");
        }

        TAF_MMA_ProcServiceStatusReport(enNetSrvSta, enAppNetSrvSta);

        /* ���·���״̬ */
        TAF_SDC_SetAppServiceStatus(enNetSrvSta);

        /*����PS����Ϣ*/
        TAF_MMA_UpdateAppPsSrvInfoInClMode();

        /* �����ϱ���ϵͳģʽ��ϵͳ��ģʽ */
        TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();

        /* ����SubMode���·����� */
        TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());
    }
    /* HRPD �����ϱ� */
    /* �ж��Ƿ���Ҫ�ϱ�PS״̬ */
    TAF_MMA_DelayReportPsCmdInClMode();

    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvQryCurrSidNid_PreProc
 ��������  : ��ѯ��ǰϵͳפ����sid nid
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvQryCurrSidNid_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CURR_SID_NID_QRY_REQ_STRU  *pstRcvMsg;
    TAF_MMA_CURR_SID_NID_QRY_CNF_STRU  *pstSndMsg;
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo = VOS_NULL_PTR;

    pstRcvMsg       = (TAF_MMA_CURR_SID_NID_QRY_REQ_STRU *)pstMsg;
    pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();
    pstSndMsg       = (TAF_MMA_CURR_SID_NID_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                        sizeof(TAF_MMA_CURR_SID_NID_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        MMA_ERRORLOG("TAF_MMA_RcvQryCurrSidNid_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CURR_SID_NID_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstSndMsg->ulReceiverPid          = WUEPS_PID_AT;
    pstSndMsg->ulMsgName              = ID_TAF_MMA_CURR_SID_NID_QRY_CNF;
    PS_MEM_CPY(&pstSndMsg->stCtrl, &pstRcvMsg->stCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSndMsg->lSid                   = pstSdc1xSysInfo->lSid;
    pstSndMsg->lNid                   = pstSdc1xSysInfo->lNid;
    pstSndMsg->enErrorCode            = TAF_ERR_NO_ERROR;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccDataCallRedialSysAcqInd_PreProc
 ��������  : ����MSCC�ϱ����ݺ����������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccDataCallRedialSysAcqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU             *pstDataCallSysAcqInd;

    pstDataCallSysAcqInd = (MSCC_MMA_DATA_CALL_REDIAL_SYS_ACQ_IND_STRU *)pstMsg;

    TAF_MMA_SndTafHrpdDataCallSysAcqInd(pstDataCallSysAcqInd->enRslt, pstDataCallSysAcqInd->enRatType);

    return VOS_TRUE;
}


#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccSystemAcquireStartInd_PreProc
 ��������  : ����MSCC�ϱ���������ʼ��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2013��10��09��
    ��    ��  : l00208543
    �޸�����  : �����ɺ���,DTS2013100904573
  2.��    ��  : 2015��6��04��
    ��    ��  : w00176964
    �޸�����  : CDMA Iteration 15 Modified

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccSystemAcquireStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU                 *pstSysAcqStartInd    = VOS_NULL_PTR;
    TAF_MMA_PLMN_SELECTION_INFO_STRU                        stTafPlmnSelectInfo;

    pstSysAcqStartInd = (MSCC_MMA_SYSTEM_ACQUIRE_START_IND_STRU *)pstMsg;
    PS_MEM_SET(&stTafPlmnSelectInfo, 0, sizeof(TAF_MMA_PLMN_SELECTION_INFO_STRU));

    /* ����ϱ��¼� */
    stTafPlmnSelectInfo.ulPlmnSelectRlst = TAF_PH_PLMN_SELECTION_RESULT_BUTT;
    stTafPlmnSelectInfo.ulPlmnSelectFlag = TAF_PH_PLMN_SELECTION_START;

    if (MSCC_MMA_ACQ_SYS_TYPE_3GPP == pstSysAcqStartInd->enSysType)
    {
        if (VOS_TRUE == TAF_MMA_IsPlmnSelectInfoNeedRpt())
        {
            TAF_MMA_SndPlmnSelectionInd(&stTafPlmnSelectInfo);
        }
    }

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccSystemAcquireEndInd_PreProc
 ��������  : ���ݲ�ͬ�Ľ��뼼�����õȴ�����ظ���״̬
 �������  : enPlmnSelectionRslt: �������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���
  2.��    ��   : 2012��10��19��
    ��    ��   : s46746
    �޸�����   : DTS2012101902505,���������޷���ʱ����һ��Location status event�¼�
  3.��    ��   : 2013��4��2��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mscc�ӿڵ���
  4.��    ��   : 2012��07��15��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseI��Ŀ�޸�:�޸ĺ��������ͷ���ֵ
  5.��    ��   : 2013��10��9��
    ��    ��   : l00208543
    �޸�����   : DTS2013100904573
  6.��    ��   : 2015��06��04��
    ��    ��   : w00176964
    �޸�����   : CDMA Iteration 15 Modified
  7.��    ��   : 2015��10��10��
    ��    ��   : l00324781
    �޸�����   : CDMA Iteration 18 Modified

  8.��    ��   : 2015��11��21��
    ��    ��   : Y00213812
    �޸�����   : ��������ʧ�ܺ����ģʽ���ϱ�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccSystemAcquireEndInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enNetworkExist;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enOldSysMode;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enOldSubMode;
#endif
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate;

    MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU                   *pstSysAcqEndInd;
    VOS_UINT32                                              ulIsNeedProcSysAcqRlt;

    pstSysAcqEndInd = (MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU*)pstMsg;

    if (MSCC_MMA_ACQ_SYS_TYPE_3GPP == pstSysAcqEndInd->enAcqSysType)
    {
        TAF_MMA_ProcMsccSystemAcquireEndInd3GppType(pstSysAcqEndInd);
    }
    else if (MSCC_MMA_ACQ_SYS_TYPE_1X == pstSysAcqEndInd->enAcqSysType)
    {
        if ((VOS_TRUE                                      == TAF_SDC_Get1xRfAvailFlag())
          &&(MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NORMAL_SERVICE != pstSysAcqEndInd->enResult))
        {
            TAF_MMA_SndTaf1XServiceStatusInd(VOS_FALSE);
        }
    }
    else
    {
        /* Interruptԭ��ֵ������ */
        if (MSCC_MMA_SYSTEM_ACQUIRE_RESULT_INTERRUPT == pstSysAcqEndInd->enResult)
        {
            return VOS_TRUE;
        }

        ulIsNeedProcSysAcqRlt = TAF_MMA_IsNeedProcessSystemAcquireResult(pstSysAcqEndInd->enResult);

        /* ��ǰ�޷����ʱ�������DO����������֪ͨAPS��ǰDO�޷���,�����DO+LTE����������֪ͨAPS��ǰDO+LTEs�޷���  */
        if ((VOS_TRUE                                      == TAF_SDC_GetHrpdRfAvailFlag())
         && (VOS_TRUE                                      == ulIsNeedProcSysAcqRlt))
        {
            /* ����״̬��ʱ��ά�ɲ� */
            TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

            enNetworkExist = TAF_SDC_NETWORK_BUT;

            enOldSysMode = TAF_SDC_GetSysMode();
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            enOldSubMode = TAF_SDC_GetSysSubMode();
#endif

            if (MSCC_MMA_ACQ_SYS_TYPE_DO_LTE == pstSysAcqEndInd->enAcqSysType)
            {
                if (VOS_TRUE == TAF_MMA_IsNeedDelayReportApsNoServiceStatus(TAF_MMA_DELAY_CL_REPORT_TYPE_DO_LTE))
                {
                    return VOS_TRUE;
                }

                TAF_MMA_SndTafCLServiceStatusInd(MMA_TAF_CL_STATUS_DO_LTE_NO_SERVICE, VOS_FALSE);

                if ((TAF_SDC_SYS_MODE_LTE == enOldSysMode)
                 || (TAF_SDC_SYS_MODE_SVLTE == enOldSysMode))
                {
                    enNetworkExist = TAF_SDC_LTE_NETWORK_NOT_EXIST;
                }
                else
                {
                    enNetworkExist = TAF_SDC_HRPD_NETWORK_NOT_EXIST;
                }

            }

            if (MSCC_MMA_ACQ_SYS_TYPE_DO == pstSysAcqEndInd->enAcqSysType)
            {
                if (VOS_TRUE == TAF_MMA_IsNeedDelayReportApsNoServiceStatus(TAF_MMA_DELAY_CL_REPORT_TYPE_DO))
                {
                    return VOS_TRUE;
                }

                TAF_MMA_SndTafCLServiceStatusInd(MMA_TAF_CL_STATUS_DO_NO_SERVICE, VOS_FALSE);

                enNetworkExist = TAF_SDC_HRPD_NETWORK_NOT_EXIST;
            }

            if (TAF_SDC_NETWORK_BUT != enNetworkExist)
            {
                TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(enNetworkExist, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);
                Mma_ModeChgReport(enSysMode, enSubMode);

                TAF_SDC_SetSysMode(enSysMode);
                TAF_SDC_SetSysSubMode(enSubMode);



#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
                if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
                {
                    /* LTE���� */
                    if (TAF_SDC_LTE_NETWORK_NOT_EXIST == enNetworkExist)
                    {
                        TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeLte(enNetworkExist);

                        TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());
                    }

                    /* EHRPD���� */
                    if (TAF_SDC_HRPD_NETWORK_NOT_EXIST == enNetworkExist)
                    {
                        if (TAF_SDC_SYS_SUBMODE_EHRPD == enOldSubMode)
                        {
                            TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeHrpd(enNetworkExist);

                            TAF_MMA_UpdateAppServiceDomainInClMode(TAF_SDC_GetAppSysMode());
                        }
                    }
                }
#endif
            }

            TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);

        }

    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvCopsFormatTypeSetReq_PreProc
 ��������  : MMAģ���յ�ATģ�鷢�͵�cops format type set req
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��3��9��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��EONS�����޸�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvCopsFormatTypeSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU                  *pstCopsFormatTypeReq = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                                    *pRcvMsg = VOS_NULL_PTR;

    pRcvMsg         = (MN_APP_REQ_MSG_STRU*)pstMsg;

    pstCopsFormatTypeReq = (TAF_MMA_COPS_FORMAT_TYPE_SET_REQ_STRU *)pRcvMsg->aucContent;

    TAF_SDC_SetCopsFormatType(pstCopsFormatTypeReq->ucCopsFormatType);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvUsimStubSetReq_PreProc
 ��������  : MMAģ���յ�ATģ�鷢�͵�usim stub set req
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��3��31��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��EONS�����޸�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvUsimStubSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_USIM_STUB_SET_REQ_STRU     *pstUsimStubReq = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pRcvMsg        = VOS_NULL_PTR;
    USIMM_READFILE_CNF_STRU            *pstUsimMsg     = VOS_NULL_PTR;
    VOS_CHAR                           *pucFilePathStr = VOS_NULL_PTR;
    VOS_UINT32                          ulPathLength;
    VOS_UINT32                          ulTotalLen;

    pRcvMsg        = (MN_APP_REQ_MSG_STRU*)pstMsg;
    pstUsimStubReq = (TAF_MMA_USIM_STUB_SET_REQ_STRU *)pRcvMsg->aucContent;

    ulTotalLen = pstUsimStubReq->ucTotalNum * pstUsimStubReq->usEfLen;

    pstUsimMsg = (USIMM_READFILE_CNF_STRU*)VOS_AllocMsg(WUEPS_PID_USIM, (sizeof(USIMM_READFILE_CNF_STRU) - VOS_MSG_HEAD_LENGTH) + ulTotalLen);

    if(VOS_NULL_PTR == pstUsimMsg)
    {
        return VOS_FALSE;
    }

    pstUsimMsg->stCmdResult.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstUsimMsg->stCmdResult.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstUsimMsg->stCmdResult.ulLength          = (sizeof(USIMM_READFILE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    pstUsimMsg->stCmdResult.ulReceiverPid     = WUEPS_PID_MMA;
    pstUsimMsg->stCmdResult.ulSenderPid       = WUEPS_PID_USIM;
    pstUsimMsg->stCmdResult.enMsgName         = USIMM_READFILE_CNF;
    pstUsimMsg->stCmdResult.ulErrorCode       = USIMM_SW_OK;
    pstUsimMsg->stCmdResult.ulResult          = VOS_OK;
    pstUsimMsg->stCmdResult.ulSendPara        = 0;
    pstUsimMsg->stCmdResult.enApptype         = pstUsimStubReq->ulApptype;
    pstUsimMsg->usEfLen                       = pstUsimStubReq->usEfLen;
    pstUsimMsg->ucTotalNum                    = pstUsimStubReq->ucTotalNum;

    /* �ļ�Idת�ļ�·�� */
    if (VOS_OK != USIMM_ChangeDefFileToPath(pstUsimStubReq->usEfId, &pucFilePathStr))
    {
        return VOS_FALSE;
    }

    /* �ļ�·�����ȱ��� */
    ulPathLength = VOS_StrLen(pucFilePathStr);
    if (0 == ulPathLength)
    {
         return VOS_FALSE;
    }

    /* FILE PATH */
    pstUsimMsg->stFilePath.ulPathLen = ulPathLength;
    PS_MEM_CPY(pstUsimMsg->stFilePath.acPath, pucFilePathStr, ulPathLength + 1);

    PS_MEM_CPY(pstUsimMsg->aucEf, pstUsimStubReq->aucEf, ulTotalLen);

    PS_SEND_MSG(WUEPS_PID_USIM, pstUsimMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvRefreshStubSetReq_PreProc
 ��������  : MMAģ���յ�ATģ�鷢�͵�refresh stub set req
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��3��31��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��EONS�����޸�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvRefreshStubSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_REFRESH_STUB_SET_REQ_STRU  *pstRefreshStubReq = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pRcvMsg           = VOS_NULL_PTR;
    USIMM_STKREFRESH_IND_STRU          *pstUsimRefreshInd = VOS_NULL_PTR;
    VOS_UINT32                          ulTotalLen;
    VOS_UINT8                           i;

    pRcvMsg           = (MN_APP_REQ_MSG_STRU*)pstMsg;
    pstRefreshStubReq = (TAF_MMA_REFRESH_STUB_SET_REQ_STRU *)pRcvMsg->aucContent;

    ulTotalLen = 0;

    if (0 != pstRefreshStubReq->ucTotalNum)
    {
        ulTotalLen = sizeof(USIMM_STKREFRESH_IND_STRU) * (pstRefreshStubReq->ucTotalNum - 1);
    }

    pstUsimRefreshInd = (USIMM_STKREFRESH_IND_STRU*)PS_ALLOC_MSG(MAPS_PIH_PID, ((sizeof(USIMM_STKREFRESH_IND_STRU)-VOS_MSG_HEAD_LENGTH) + ulTotalLen));

    if(VOS_NULL_PTR == pstUsimRefreshInd)
    {
        return VOS_TRUE;
    }

    PS_MEM_SET((VOS_INT8*)pstUsimRefreshInd + VOS_MSG_HEAD_LENGTH, 0, ((sizeof(USIMM_STKREFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH) + ulTotalLen));

    pstUsimRefreshInd->stIndHdr.enMsgName       = USIMM_STKREFRESH_IND;
    pstUsimRefreshInd->stIndHdr.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstUsimRefreshInd->stIndHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstUsimRefreshInd->stIndHdr.ulLength        = (sizeof(USIMM_STKREFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    pstUsimRefreshInd->stIndHdr.ulReceiverPid   = pstRefreshStubReq->ulReceivePid;
    pstUsimRefreshInd->stIndHdr.ulSenderPid     = MAPS_PIH_PID;
    pstUsimRefreshInd->enRefreshType            = pstRefreshStubReq->usRefreshFileType;
    pstUsimRefreshInd->usEfNum                  = pstRefreshStubReq->ucTotalNum;

    for (i = 0; i < pstRefreshStubReq->ucTotalNum; i++)
    {
        pstUsimRefreshInd->astEfId[i].usFileId  = pstRefreshStubReq->ausEfId[i];    /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstUsimRefreshInd->astEfId[i].enAppType = USIMM_GUTL_APP;                   /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */

    }

    PS_SEND_MSG(MAPS_PIH_PID, pstUsimRefreshInd);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvCSServiceDisconnExpired_PreProc
 ��������  : �ȴ�cs ҵ������ĳ�ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��15��
    ��    ��   : c00318887
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvCSServiceDisconnExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == TAF_SDC_GetCsEccExistFlg())
    {
        /* ������CS ҵ�������������ʱ���ȴ�CSҵ�������ػ� */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN, TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN_LEN);
    }
    else
    {
        /* �����ڲ��Ŀ�״̬�ı�ָʾ��Ϣ�������ػ� */
        TAF_MMA_SndInterUsimChangeInd();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvWaitReadSimFilesExpired_PreProc
 ��������  : �����ļ�������ʱ����ʱ�Ĵ���
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��15��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvWaitReadSimFilesExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                        *pstMsg
)
{
    TAF_MMA_ClearAllWaitSimFilesCnfFlg();
    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAutoReselStubSetReq_PreProc
 ��������  : MMAģ���յ�ATģ�鷢�͵�refresh stub set req
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��5��30��
    ��    ��   : b00269685
    �޸�����   : new
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAutoReselStubSetReq_PreProc(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                                    *pRcvMsg = VOS_NULL_PTR;
    TAF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU                   *pstRefreshStubReq = VOS_NULL_PTR;

    pRcvMsg           = (MN_APP_REQ_MSG_STRU*)pstMsg;
    pstRefreshStubReq = (TAF_MMA_AUTO_RESEL_STUB_SET_REQ_STRU *)pRcvMsg->aucContent;

    TAF_MMA_SndMsccAutoReselSetReq(pstRefreshStubReq->ucActiveFlg);

    return VOS_TRUE;
}


/* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, Begin */
/*lint -e958 �޸���: j00174725; */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccPsServiceConnStatusInd_PreProc
 ��������  : �յ�MSCCģ��PS�������״̬��Ϣ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��27��
    ��    ��   : s00217060
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccPsServiceConnStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU                *pstPsServiceConnStatusInd = VOS_NULL_PTR;
    TAF_MTC_SRV_CONN_STATE_INFO_STRU                        stMmaMtcConnStInfo;
    TAF_CTRL_STRU                                           stCtrl;
    MSCC_MMC_PS_SIGNALING_TYPE_ENUM_UINT8                   enPsSigType;

    pstPsServiceConnStatusInd = (MSCC_MMA_PS_SERVICE_CONN_STATUS_IND_STRU *)pstMsg;
    PS_MEM_SET(&stMmaMtcConnStInfo, 0, sizeof(TAF_MTC_SRV_CONN_STATE_INFO_STRU));
    PS_MEM_SET(&stCtrl, 0x0, sizeof(stCtrl));

    enPsSigType               = pstPsServiceConnStatusInd->enPsSigType;

    /* ��дCTLͷ */
    TAF_API_CTRL_HEADER(&stCtrl, WUEPS_PID_MMA, 0, 0);

    switch(enPsSigType)
    {
    #if (FEATURE_ON == FEATURE_LTE)
        case MSCC_MMC_PS_SIGNALING_TYPE_LTE:

            TAF_SDC_SetEpsServiceConnStatusFlag(pstPsServiceConnStatusInd->ucPsServiceConnStatusFlag);

            stMmaMtcConnStInfo.bitOpEpsSrv          = VOS_TRUE;
            stMmaMtcConnStInfo.enEpsSrvConnState    = pstPsServiceConnStatusInd->ucPsServiceConnStatusFlag;
            break;
    #endif

        case MSCC_MMC_PS_SIGNALING_TYPE_GU:

            TAF_SDC_SetPsServiceConnStatusFlag(pstPsServiceConnStatusInd->ucPsServiceConnStatusFlag);

            stMmaMtcConnStInfo.bitOpPsSrv           = VOS_TRUE;
            stMmaMtcConnStInfo.enPsSrvConnState     = pstPsServiceConnStatusInd->ucPsServiceConnStatusFlag;
            break;

        default:
            MMA_WARNINGLOG("TAF_MMA_RcvMsccPsServiceConnStatusInd_PreProc():WORNING:sig type is invalid.");

            return VOS_TRUE;
    }

    /* ������״̬����MTC */
    MTC_SetModemServiceConnState(&stCtrl, &stMmaMtcConnStInfo);

    return VOS_TRUE;
}
#endif
/*lint +e958 �޸���: j00174725; */
/* Add by s00217060 for K3V3 ��ģ����������, 2014-06-27, End */



#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafImsSrvInfoNotify_PreProc
 ��������  : �յ�TAF��ID_TAF_MMA_IMS_SRV_INFO_NOTIFY��Ϣ�Ĵ���
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��06��
    ��    ��   : s00217060
    �޸�����   : DTS2014110608091:IMS�绰ʱ������cs���paging ind
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafImsSrvInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_IMS_SRV_INFO_NOTIFY_STRU              *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg   = (TAF_MMA_IMS_SRV_INFO_NOTIFY_STRU *)pstMsg;

    TAF_MMA_SndMsccImsSrvInfoNotify(pstRcvMsg->ucImsCallFlg);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafImsSwitchQryReq_PreProc
 ��������  : �յ�TAF��ID_TAF_MMA_IMS_SWITCH_QRY_REQ��Ϣ�Ĵ���
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafImsSwitchQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_IMS_SWITCH_QRY_REQ_STRU    *pstSetReq = VOS_NULL_PTR;
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8 enImsSwitchState;

    pstSetReq = (TAF_MMA_IMS_SWITCH_QRY_REQ_STRU *)pstMsg;

    if (VOS_TRUE != TAF_SDC_GetImsSupportFlag())
    {
        enImsSwitchState = TAF_SDC_IMS_SWITCH_STATE_OFF;
    }
    else
    {
        enImsSwitchState = TAF_SDC_IMS_SWITCH_STATE_ON;
    }

    TAF_MMA_SndImsSwitchQryCnf(&pstSetReq->stCtrl, (VOS_UINT8)enImsSwitchState);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafVoiceDomainSetReq_PreProc
 ��������  : �յ�TAF��ID_TAF_MMA_VOICE_DOMAIN_SET_REQ��Ϣ�Ĵ���
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafVoiceDomainSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU  *pstSetReq;
    VOS_UINT8                           ucImsVoiceFlag;
    VOS_UINT32                          ulImsSupportFlag;
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain;

    pstSetReq           = (TAF_MMA_VOICE_DOMAIN_SET_REQ_STRU *)pstMsg;
    ucImsVoiceFlag      = TAF_SDC_GetVoiceCallOnImsSupportFlag();
    ulImsSupportFlag    = TAF_SDC_GetImsSupportFlag();
    enVoiceDomain       = TAF_SDC_GetVoiceDomain();

    /* IMS����ҵ���ܹرջ���IMS������֧�ֵ�����£�����������PS_ONLY */
    if ((VOS_FALSE == ucImsVoiceFlag)
     || (VOS_FALSE == ulImsSupportFlag))
    {
        if (TAF_MMA_VOICE_DOMAIN_IMS_PS_ONLY == pstSetReq->enVoiceDomain)
        {
            /* ��APP�ظ�����ʧ�� */
            TAF_MMA_SndVoiceDomainSetCnf(&pstSetReq->stCtrl,
                                         TAF_MMA_APP_OPER_RESULT_REJECT,
                                         TAF_ERR_IMS_NOT_SUPPORT);

            return VOS_TRUE;
        }
    }

    /* IMS����ҵ������У�����������CS_ONLY */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        if (TAF_MMA_VOICE_DOMAIN_CS_ONLY == pstSetReq->enVoiceDomain)
        {
            /* ��APP�ظ�����ʧ�� */
            TAF_MMA_SndVoiceDomainSetCnf(&pstSetReq->stCtrl,
                                         TAF_MMA_APP_OPER_RESULT_REJECT,
                                         TAF_ERR_IMS_SERVICE_EXIST);

            return VOS_TRUE;
        }
    }

    /* ��ѡ�������з����仯����֪ͨMMC */
    if (enVoiceDomain != pstSetReq->enVoiceDomain)
    {
        /* �ڷ���ģʽ���治��MMC����UE������ֻ���������ĺ�NV */
        if (TAF_PH_MODE_FULL == TAF_SDC_GetCurPhoneMode())
        {
            /* ��MSCC����VOICE DOMAIN�仯ָʾ */
            TAF_MMA_SndMsccVoiceDomainChangeInd((NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32)pstSetReq->enVoiceDomain);
        }

        /* ����������ѡ��������ĺ�NV */
        if (VOS_TRUE != TAF_MMA_UpdataVoiceDomain((TAF_SDC_VOICE_DOMAIN_ENUM_UINT32)pstSetReq->enVoiceDomain))
        {
            TAF_MMA_SndVoiceDomainSetCnf(&pstSetReq->stCtrl,
                                         TAF_MMA_APP_OPER_RESULT_FAILURE,
                                         TAF_ERR_UNSPECIFIED_ERROR);
            return VOS_TRUE;
        }

    }

    /* ��APP�ظ����óɹ� */
    TAF_MMA_SndVoiceDomainSetCnf(&pstSetReq->stCtrl,
                                 TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                 TAF_ERR_NO_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafVoiceDomainQryReq_PreProc
 ��������  : �յ�TAF��ID_TAF_MMA_VOICE_DOMAIN_QRY_REQ��Ϣ�Ĵ���
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafVoiceDomainQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU  *pstSetReq;
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain;

    pstSetReq       = (TAF_MMA_VOICE_DOMAIN_QRY_REQ_STRU *)pstMsg;
    enVoiceDomain   = TAF_SDC_GetVoiceDomain();

    TAF_MMA_SndVoiceDomainQryCnf(&pstSetReq->stCtrl,
                                 (TAF_MMA_VOICE_DOMAIN_ENUM_UINT32)enVoiceDomain);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccImsSwitchStateInd_PreProc
 ��������  : �յ�MSCCģ���IMS���ػ�״ָ̬ʾ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��04��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��03��13��
   ��    ��   : l00198894
   �޸�����   : VOLTE Randk1������Ŀ

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccImsSwitchStateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_IMS_SWITCH_STATE_IND_STRU  *pstStateInd = VOS_NULL_PTR;

    pstStateInd = (MSCC_MMA_IMS_SWITCH_STATE_IND_STRU *)pstMsg;

    TAF_SDC_SetCurImsSwitchState((TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8)pstStateInd->enImsSwitch);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ֪ͨMTC IMSA�Ŀ��ػ�״̬ */
    TAF_MMA_SndMtcImsaStateInd((MTC_MODEM_POWER_STATE_ENUM_UINT8)pstStateInd->enImsSwitch);
#endif

    return VOS_TRUE;
}

#endif

/*lint -restore */



#if ( FEATURE_ON == FEATURE_LTE )
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccLmmCellSignReportInd_PreProc
 ��������  : �յ�MMC�ϱ���LMM  ���ź�������Ϣ
 �������  : ID_MMC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND *pMsg MMC�ϴ�����������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��28��
    ��    ��   : w00281933
    �޸�����   : �����ɺ���(����״̬��ʾ�Ż�Phase I)
  2.��    ��   : 2015��4��28��
    ��    ��   : b00269685
    �޸�����   : add rat of rssi
  3.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccLmmCellSignReportInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SDC_CTX_STRU                               *pstSdcCtx     = VOS_NULL_PTR;
    MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU    *pstRcvMsg          = VOS_NULL_PTR;
    TAF_SDC_SYS_MODE_ENUM_UINT8                     enAppSysMode;

    pstRcvMsg        = (MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND_STRU*)pstMsg;
    pstSdcCtx   = TAF_SDC_GetSdcCtx();
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.ucChannalQual = TAF_PH_BER_UNKNOWN;
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRssi = pstRcvMsg->stLteRssi.sRssi;
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsd  = pstRcvMsg->stLteRssi.sRsd;
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsrp = pstRcvMsg->stLteRssi.sRsrp;
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsrq = pstRcvMsg->stLteRssi.sRsrq;
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.lSINR = pstRcvMsg->stLteRssi.lSINR;

    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.usRI      = pstRcvMsg->stLteRssi.stCQI.usRI;
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[0] = pstRcvMsg->stLteRssi.stCQI.ausCQI[0];
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[1] = pstRcvMsg->stLteRssi.stCQI.ausCQI[1];

    TAF_MMA_GetRssiLevelFromLteRssi(pstRcvMsg->stLteRssi.sRssi, &(pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.ucRssiValue));

    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.enRat = TAF_SDC_SYS_MODE_LTE;

    enAppSysMode = TAF_SDC_GetAppSysMode();

    /*RAT �ı��ݲ��ϱ�����ע�������ϱ�*/
    if ((TAF_SDC_SYS_MODE_LTE != enAppSysMode)
     && (TAF_SDC_SYS_MODE_SVLTE != enAppSysMode))
    {
        return VOS_TRUE;
    }

    /* RAT��ͬʱ������APP�е��ź�ǿ�� */
    PS_MEM_CPY(&(pstSdcCtx->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo),
               &(pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo),
               sizeof(TAF_SDC_3GPP_RSSI_INFO_STRU));

    /* RXLEV��Ҫ�ϱ���AT,RXQUALITY����Ҫ�ϱ���AT */
    if (NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV == (pstRcvMsg->unMeasReportType.ucMeasReportType & NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV))
    {
        TAF_MMA_SndAtRssiInd();
    }

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccRssiInd_PreProc
 ��������  : �յ�MSCC�ϱ���MSCC_RSSI_IND��Ϣ
 �������  : MSCC_MMA_RSSI_IND_STRU *pMsg MSCC�ϴ�����������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��9��24��
    ��    ��   : liuyang
    �޸�����   : �����ɺ���
  2.��    ��   : 2006��3��16��
    ��    ��   : liuyang id:48197
    �޸�����   : ���ⵥ�ţ�A32D02382

  3.��    ��   : 2012��5��26��
    ��    ��   : z40661
    �޸�����   : DTS2012050803419,�ж��ź�ǿ�ȹ�Сʱ,��Ҫ���ź�ǿ�ȷ����仯ʱ,�����ϱ�һ�η���״̬

  4.��    ��   : 2012��6��5��
    ��    ��   : z40661
    �޸�����   : DTS2012042602737�����ն˲�Ʒ�ߴ��һ�£�ɾ��AT^sysinfo�ź�
                 ���޵��ж�
  5.��    ��   : 2013��2��4��
    ��    ��   : t00212959
    �޸�����   : DTS2013020600770:at^cerssi?���ӷ��ز���
  6.��    ��   : 2013��4��2��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
  7.��    ��   : 2012��07��15��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseI��Ŀ�޸�:�޸ĺ��������ͷ���ֵ
  8.��    ��   : 2014��06��4��
    ��    ��   : b00269685
    �޸�����   : �����ж��Ƿ���Ҫ�ϱ�
  10.��    ��   : 2014��11��28��
    ��    ��   : w00281933
    �޸�����   : ע��״̬��ʾ�Ż�Phase I
  11.��    ��   : 2015��4��28��
    ��    ��   : b00269685
    �޸�����   : rssi��Ϣ��ҪЯ��rat
  12.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccRssiInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulI;

    /* Added by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, begin */
    MSCC_MMA_RSSI_IND_STRU              *pMsg;
    TAF_SDC_CTX_STRU                   *pstSdcCtx = VOS_NULL_PTR;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enAppSysMode;

#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        return VOS_TRUE;
    }
#endif

    pMsg            = (MSCC_MMA_RSSI_IND_STRU*)pstMsg;
    /* Added by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, end */
    enAppSysMode    = TAF_SDC_GetAppSysMode();
    pstSdcCtx       = TAF_SDC_GetSdcCtx();


    /*CERSSI ��Ϣ��������SDC */
    ulI = 0;
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.ucChannalQual = pMsg->astRssi[ulI].ucBer;

    /* RSCP/ECIO/RSSI�������µĶ�Ӧ��ϵ��RSCP=ECIO+RSSI*/
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.sUeRfPower   = pMsg->sUeRfPower;
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.usCellDlFreq = pMsg->usCellDlFreq;
    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.usCellUlFreq = pMsg->usCellUlFreq;

    if (TAF_SDC_SYS_MODE_GSM == pMsg->enRat)
    {
        MMA_GetRssiLevelFromValue(pMsg->astRssi[ulI].sRssiValue,
                                 &(pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.ucRssiValue));

        pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.u.st2GCellSignInfo.sRssiValue = pMsg->astRssi[ulI].sRssiValue;
    }
    else
    {
        pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sRscpValue = pMsg->astRssi[ulI].sRscpValue;
        pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sEcioValue = pMsg->astRssi[ulI].sRscpValue - pMsg->astRssi[ulI].sRssiValue;

        MMA_GetRssiLevelFromValue(pMsg->astRssi[ulI].sRscpValue,
                             &(pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.ucRssiValue));
    }

    pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo.enRat = pMsg->enRat;

    /* ���RAT��ͬ������Ҫ����APP�е��ź�ǿ�ȣ�Ҳ����Ҫ�ϱ���AT */
    if (enAppSysMode != pMsg->enRat)
    {
        return VOS_TRUE;
    }

    /* RAT��ͬʱ������APP�е��ź�ǿ�� */
    PS_MEM_CPY(&(pstSdcCtx->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo),
                &(pstSdcCtx->stNetworkInfo.stSigQuaInfo.st3GppRssiInfo),
                sizeof(TAF_SDC_3GPP_RSSI_INFO_STRU));

    /* RXLEV��Ҫ�ϱ���AT,RXQUALITY����Ҫ�ϱ���AT */
    if(NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV == (pMsg->unMeasReportType.ucMeasReportType & NAS_MSCC_PIF_SCELL_MEAS_TYPE_RXLEV))
    {
        TAF_MMA_SndAtRssiInd();
    }

    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, begin */
    return VOS_TRUE;
    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-15, end */
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccSrchedPlmnInfoInd_PreProc
 ��������  : �յ�MSCC���������ѵ�PLMN��Ϣ�ϱ���Ϣ
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��15��
    ��    ��   : h00285180
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccSrchedPlmnInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU *pstSrchedPlmnInfoInd = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl       = VOS_NULL_PTR;

    pstSrchedPlmnInfoInd = (MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU *) pstMsg;

    /*  ���ܿ������ϱ� */
    pstCurcRptCtrl = TAF_SDC_GetCurcRptCtrl();
    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                              TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                              TAF_SDC_RPT_CMD_SRCHEDPLMNINFO))
    {
        TAF_MMA_SndSrchedPlmnInfoInd(pstSrchedPlmnInfoInd);
    }

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_MMA_IsAutoSrchNetworkAllowedInCLMode_PreProc
 ��������  : check��CLģʽ�£��Ƿ������Զ���������
 �������  : ��

 �������  : penErrCode -- ���ز���������
 �� �� ֵ  : VOS_TRUE   -- ��������Զ�����, �ó�������Ҫ��ע�����룻
             VOS_FALSE  -- ����������Զ��������ó�����Ҫ���ش�������û���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��26��
    ��    ��   : y00245242
    �޸�����   : �½�
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsAutoSrchNetworkAllowedInCLMode_PreProc(
    TAF_ERROR_CODE_ENUM_UINT32         *penErrCode
)
{
    /* CallBack״̬��,syscfgexֱ�ӻظ�ʧ�� */
    if (VOS_TRUE == TAF_SDC_Get1xSysInfo()->ucIsEmcCallExistFlg)
    {
        *penErrCode = TAF_ERR_CME_OPT_NOT_SUPPORTED;
        return VOS_FALSE;
    }

    if (TAF_SDC_USIM_STATUS_NO_PRESENT == TAF_SDC_GetCsimStatus())
    {
        MMA_WARNINGLOG("TAF_MMA_IsAutoSrchNetworkAllowedInCLMode_PreProc: Csim Status Absent!");
    }

    *penErrCode = TAF_MMA_ConvertCsimCardStatusToTafErrorCode(TAF_SDC_GetCsimStatus());

    /* ���CSIM��״̬, ����޿������쳣�򿨱���������Ҫ���������� */
    if (TAF_ERR_NO_ERROR != *penErrCode)
    {
        return VOS_FALSE;
    }

    if (MMA_SIM_IS_LOCK == g_stMmaMePersonalisationStatus.SimLockStatus)
    {
        *penErrCode = TAF_ERR_SIM_LOCK;

        return VOS_FALSE;
    }

    /* ����������Ҫ�������� */
    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvPlmnAutoReselReq_PreProc
 ��������  : �յ�AT��at+cops=0���õ�Ԥ����
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����

 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ҫ��һ������
             VOS_FALSE:��Ҫ��״̬������

���ú���   :
��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                 �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������

  3.��    ��   : 2015��12��25��
    ��    ��   : y00245242
    �޸�����   : CLģʽ�£����������������Կ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPlmnAutoReselReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) || (FEATURE_ON == FEATURE_DSDS))
    TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU   *pstPlmnReselMsg = VOS_NULL_PTR;
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_ERROR_CODE_ENUM_UINT32          enErrCode;
#endif
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enWaitSrvAcqCnfTimerStatus;
#endif

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) || (FEATURE_ON == FEATURE_DSDS))
    pstPlmnReselMsg = (TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU *)pstMsg;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    enErrCode = TAF_ERR_NO_ERROR;

    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        if (VOS_FALSE == TAF_MMA_IsAutoSrchNetworkAllowedInCLMode_PreProc(&enErrCode))
        {
            /* Cģʽ��ֱ���ϱ���֧��*/
            TAF_MMA_SndPlmnAutoReselCnf(&pstPlmnReselMsg->stCtrl, enErrCode);

            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    enWaitSrvAcqCnfTimerStatus = TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF);

    /* �������ҵ�񴥷���������ֱ�ӻظ�ʧ�� */
    if (TAF_MMA_TIMER_STATUS_RUNING == enWaitSrvAcqCnfTimerStatus)
    {
        /* �ϱ�APP��ǰ״̬�¼� */
        TAF_MMA_SndPlmnAutoReselCnf(&pstPlmnReselMsg->stCtrl, TAF_ERR_NO_RF);

        return VOS_TRUE;
    }
#endif


    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvPlmnSpecialSelReq_PreProc
 ��������  : �յ�AT��at+cops=0���õ�Ԥ����
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����

 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ҫ��һ������
             VOS_FALSE:��Ҫ��״̬������

���ú���   :
��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPlmnSpecialSelReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU  *pstPlmnUserSelMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucError;
    TAF_PLMN_ID_STRU                    stPlmn;
    VOS_UINT32                          ulRet;

#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enWaitSrvAcqCnfTimerStatus;
#endif

    pstPlmnUserSelMsg = (TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* Cģʽ��ֱ���ϱ���֧��*/
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnUserSelMsg->stCtrl, TAF_ERR_CME_OPT_NOT_SUPPORTED);

        return VOS_TRUE;
    }
#endif



#if (FEATURE_ON == FEATURE_DSDS)
    enWaitSrvAcqCnfTimerStatus = TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF);

    /* �������ҵ�񴥷���������ֱ�ӻظ�ʧ�� */
    if (TAF_MMA_TIMER_STATUS_RUNING == enWaitSrvAcqCnfTimerStatus)
    {
        /* �ϱ�APP��ǰ״̬�¼� */
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnUserSelMsg->stCtrl, TAF_ERR_NO_RF);

        return VOS_TRUE;
    }
#endif

    /* ��CLģʽʱ�򣬲�֧��AT����ѡ������,ֱ�ӷ���ERROR */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnUserSelMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* ת���û�����PLMN�ַ�ΪPLMN ID */
    ulRet = MMA_FormatPlmnStr2PlmnId(&stPlmn,
                                      pstPlmnUserSelMsg->stPlmnUserSel.ucFormatType,
                                      pstPlmnUserSelMsg->stPlmnUserSel.usOperNameLen,
                                      pstPlmnUserSelMsg->stPlmnUserSel.ucOperName);
    if( VOS_TRUE == ulRet)
    {
        MMA_PlmnId2NasStyle(&stPlmn);

        /* ͨ��ԭ�е�TAF_PH_EVT_PLMN_SEL_CNF��Ϣ��ָ���ѽ�����͸�AT */

        ucError            = TAF_ERR_NO_ERROR;

        ucError = MMA_CheckUsimStatusForPlmnSel();
        if (TAF_ERR_NO_ERROR != ucError)
        {
            /*������*/
            TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnUserSelMsg->stCtrl, ucError);
            return VOS_TRUE;
        }

        /*����ACCESSMODEѡ��*/
        if (pstPlmnUserSelMsg->stPlmnUserSel.enAccessMode > TAF_MMA_RAT_BUTT)
        {
            /*������*/
            TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnUserSelMsg->stCtrl, TAF_ERR_PARA_ERROR);

            return VOS_TRUE;
        }

        /* ��ڲ����Ϸ��Լ�� */
        if ( Sta_IsInvalidOpId (pstPlmnUserSelMsg->stCtrl.ucOpId))
        {
            MMA_WARNINGLOG("TAF_MMA_RcvPlmnSpecialSelReq_PreProc():WARNING:parameter invalid");
            return VOS_TRUE;
        }

        /* svlte nv��������ػ�״̬����cops */
        if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
        {
            /* Modified by b00269685 for Fortify ����, 2014-7-22, begin */
            (VOS_VOID)TAF_MMA_RcvPlmnSelectionReq_PowerOff(pstPlmnUserSelMsg,
                                                           stPlmn,
                                                           pstPlmnUserSelMsg->stPlmnUserSel.enAccessMode,
                                                           TAF_PLMN_RESELETION_MANUAL);
            return VOS_TRUE;
            /* Modified by b00269685 for Fortify ����, 2014-7-22, end */
        }


        /* PLMN_SEL״̬������������쳣*/
        if (VOS_TRUE != TAF_MMA_IsEnablePlmnSelect())
        {
            /* �������ENABLE״̬�����ش��� */
            if (TAF_MMA_PLMN_MODE_ENUM_DISABLE == TAF_MMA_GetPlmnMode_Refresh())
            {
                ucError = TAF_ERR_NET_SEL_MENU_DISABLE;
            }
            else
            {
                ucError = TAF_ERR_PHONE_MSG_UNMATCH;
            }

            /* �ϱ�APP��ǰ״̬�¼� */
            TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnUserSelMsg->stCtrl, ucError);

            return VOS_TRUE;    /* ���󷵻� */
        }

        /* USIM����ֹGSM���벢����G��ģʱ���������û�ָ����
           SIM��������L��ģʱ��Ҳ�������û�ָ���� */
        if (VOS_FALSE == TAF_MMA_IsExistPlmnRatAllowAccess())
        {
            /* �ϱ�APP��ǰ״̬�¼� */
            TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnUserSelMsg->stCtrl, TAF_ERR_NO_NETWORK_SERVICE);
            return VOS_TRUE;
        }
    }
    else
    {
        /*������*/
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnUserSelMsg->stCtrl, TAF_ERR_PARA_ERROR);
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvLocInfoQryReq_PreProc
 ��������  : ����TAF loc info �ϱ���������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvLocInfoQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_LOCATION_INFO_QRY_REQ_STRU *pstLocInfoQryReqMsg = VOS_NULL_PTR;
    TAF_MMA_LOCATION_INFO_QRY_CNF_STRU  stLocInfoQryCnfMsg;

    pstLocInfoQryReqMsg = (TAF_MMA_LOCATION_INFO_QRY_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stLocInfoQryCnfMsg, 0x00, sizeof(TAF_MMA_LOCATION_INFO_QRY_CNF_STRU));

    /*����MN_PH_QryLocinfo��ѯ������*/
    stLocInfoQryCnfMsg.ulResult = MN_PH_QryLocinfo(&stLocInfoQryCnfMsg.ulMcc,
                                                   &stLocInfoQryCnfMsg.ulMnc,
                                                   &stLocInfoQryCnfMsg.usLac,
                                                   &stLocInfoQryCnfMsg.ucRac,
                                                   &stLocInfoQryCnfMsg.ulCellid);

    TAF_MMA_SndLocInfoQryCnf(&pstLocInfoQryReqMsg->stCtrl, &stLocInfoQryCnfMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvCipherQryReq_PreProc
 ��������  : ����TAF loc info �ϱ���������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvCipherQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CIPHER_QRY_REQ_STRU        *pstCipherQryReqMsg = VOS_NULL_PTR;

    pstCipherQryReqMsg = (TAF_MMA_CIPHER_QRY_REQ_STRU *)pstMsg;

    MMA_QryCipherInfo(pstCipherQryReqMsg->stCtrl.usClientId, pstCipherQryReqMsg->stCtrl.ucOpId);

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvPowerDownReq_PreProc
 ��������  : ����PrefPlmnType �ϱ���������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPowerDownReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_MT_POWER_DOWN_REQ_STRU     *pstPowerDownReqMsg = VOS_NULL_PTR;

    pstPowerDownReqMsg = (TAF_MMA_MT_POWER_DOWN_REQ_STRU *)pstMsg;

#if defined(INSTANCE_1)
    /* RF(G/W) OFF,delay n ms */
    DRV_RF_LDODOWN(RF_ID1);
#elif defined(INSTANCE_2)
    /* RF(G/W) OFF,delay n ms */
    DRV_RF_LDODOWN(RF_ID2);
#else
    /* RF(G/W) OFF,delay n ms */
    DRV_RF_LDODOWN(RF_ID0);
#endif

    /* USIM OFF,delay n ms */
    (VOS_VOID)mdrv_sci_deact();
    /* BBP(G/W) OFF,����Ҫ��ʾ�ر� */

    /*�����¼�ΪMT �µ�Ļظ���Ϣ,*/
    TAF_MMA_SndMtPowrDownCnf(&pstPowerDownReqMsg->stCtrl, TAF_ERR_NO_ERROR);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvPrefPlmnTypeSetReq_PreProc
 ��������  : ����TAF loc info �ϱ���������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPrefPlmnTypeSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU    *pstPrefPlmnSetReqMsg = VOS_NULL_PTR;
    VOS_UINT32                              ulRet;
    TAF_ERROR_CODE_ENUM_UINT32              enErrorCause;

    pstPrefPlmnSetReqMsg = (TAF_MMA_PREF_PLMN_TYPE_SET_REQ_STRU *)pstMsg;

    ulRet = TAF_SetPrefPlmnType(pstPrefPlmnSetReqMsg->enPrefPlmnType);
    if (TAF_PARA_OK != ulRet)
    {
        enErrorCause = TAF_ERR_CME_OPT_NOT_SUPPORTED;
    }
    else
    {
        enErrorCause = TAF_ERR_NO_ERROR;
    }

    TAF_MMA_SndPrefPlmnTypeSetCnf(&pstPrefPlmnSetReqMsg->stCtrl, enErrorCause, pstPrefPlmnSetReqMsg->enPrefPlmnType);
    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvCFPlmnSetReq_PreProc
 ��������  : ����TAF cfplmn �ϱ���������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvCFPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucCtxIndex;
    VOS_UINT8                           ucSimStatus;
    TAF_MMA_CFPLMN_SET_REQ_STRU        *pstCFPlmnReqMsg = VOS_NULL_PTR;

    pstCFPlmnReqMsg = (TAF_MMA_CFPLMN_SET_REQ_STRU *)pstMsg;

    /* ��ȡ��״̬ */
    (VOS_VOID)MMA_PhoneGetUsimStatus(&ucSimStatus);

    /* ���������򷵻ش��� */
    if (MMA_USIM_PRESENT != ucSimStatus)
    {
        MMA_WARNINGLOG("TAF_MMA_RcvCFPlmnSetReq_PreProc:SIM/USIM Not Present!");
        TAF_MMA_SndCFPlmnSetCnf(&pstCFPlmnReqMsg->stCtrl, TAF_MMA_APP_CFPLMN_OPER_RESULT_NO_USIM);
        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndCFPlmnSetCnf(&pstCFPlmnReqMsg->stCtrl, TAF_MMA_APP_CFPLMN_OPER_RESULT_FAILURE);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstCFPlmnReqMsg->stCtrl,
                       TAF_MMA_OPER_CFPLMN_SET_REQ, ucCtxIndex);

    /* PLMN��ʽת�� */
    MMA_PlmnId2NasStyle(&pstCFPlmnReqMsg->stCFPlmnPara.stPlmn);

    /* ��MSCC��cfplmn req��Ϣ */
    TAF_MMA_SndMsccCFPlmnSetReq(&pstCFPlmnReqMsg->stCFPlmnPara);

    /* ����������ʱ��TI_TAF_MMA_WAIT_MSCC_CFPLMN_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF, TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF_LEN);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvCFPlmnQueryReq_PreProc
 ��������  : ����TAF cfplmn �ϱ���������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvCFPlmnQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucCtxIndex;
    VOS_UINT8                           ucSimStatus;
    TAF_MMA_CFPLMN_QUERY_REQ_STRU      *pstCFPlmnReqMsg = VOS_NULL_PTR;

    pstCFPlmnReqMsg = (TAF_MMA_CFPLMN_QUERY_REQ_STRU *)pstMsg;

    /* ��ȡ��״̬ */
    (VOS_VOID)MMA_PhoneGetUsimStatus(&ucSimStatus);

    /* ���������򷵻ش��� */
    if (MMA_USIM_PRESENT != ucSimStatus)
    {
        MMA_WARNINGLOG("TAF_MMA_RcvCFPlmnSetReq_PreProc:SIM/USIM Not Present!");
        TAF_MMA_SndCFPlmnQueryCnf(&pstCFPlmnReqMsg->stCtrl, TAF_MMA_APP_CFPLMN_OPER_RESULT_NO_USIM, VOS_NULL_PTR);
        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndCFPlmnQueryCnf(&pstCFPlmnReqMsg->stCtrl, TAF_MMA_APP_CFPLMN_OPER_RESULT_FAILURE, VOS_NULL_PTR);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstCFPlmnReqMsg->stCtrl,
                       TAF_MMA_OPER_CFPLMN_QRY_REQ, ucCtxIndex);

    /* ��MSCC��cfplmn req��Ϣ */
    TAF_MMA_SndMsccCFPlmnQueryReq();

    /* ����������ʱ��TI_TAF_MMA_WAIT_MSCC_CFPLMN_QUERY_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_CFPLMN_QUERY_CNF, TI_TAF_MMA_WAIT_MSCC_CFPLMN_QUERY_CNF_LEN);
    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccCFPlmnSetCnf_PreProc
 ��������  : �յ�mscc��cfplmn cnf��Ϣ
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCFPlmnSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_CFPLMN_SET_CNF_STRU                           *pstCFPlmnCnf    = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU                                  *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                                               ucCtxIndex;
    TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32              enRslt;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    pstCFPlmnCnf = (MSCC_MMA_CFPLMN_SET_CNF_STRU *)pstMsg;

    if (NAS_MSCC_PIF_CFPLMN_OPER_RESULT_SUCCESS != pstCFPlmnCnf->enResult)
    {
        enRslt = TAF_MMA_APP_CFPLMN_OPER_RESULT_FAILURE;
    }
    else
    {
        enRslt = TAF_MMA_APP_CFPLMN_OPER_RESULT_SUCCESS;
    }

    /* ֹͣ������ʱ�� */
    if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF))
    {
        /* ֹͣ������ʱ�� */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF);

        /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����ID_TAF_MMA_CFPLMN_REQ��Ӧ�ļ�¼�� */
        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CFPLMN_SET_REQ, &ucCtxIndex))
        {
            /*  �ظ�confirm */
            TAF_MMA_SndCFPlmnSetCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                                    enRslt);

            TAF_MMA_ClearOperCtx(ucCtxIndex);
        }
    }
    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccCFPlmnQueryCnf_PreProc
 ��������  : �յ�mscc��cfplmn cnf��Ϣ
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCFPlmnQueryCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_CFPLMN_QUERY_CNF_STRU                         *pstCFPlmnCnf  = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU                                  *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                                               ucCtxIndex;
    TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32              enRslt;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    pstCFPlmnCnf = (MSCC_MMA_CFPLMN_QUERY_CNF_STRU *)pstMsg;
    if (NAS_MSCC_PIF_CFPLMN_OPER_RESULT_SUCCESS != pstCFPlmnCnf->enResult)
    {
        enRslt = TAF_MMA_APP_CFPLMN_OPER_RESULT_FAILURE;
    }
    else
    {
        enRslt = TAF_MMA_APP_CFPLMN_OPER_RESULT_SUCCESS;
    }

    /* ֹͣ������ʱ�� */
    if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_CFPLMN_QUERY_CNF))
    {
        /* ֹͣ������ʱ�� */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CFPLMN_QUERY_CNF);

        /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����ID_TAF_MMA_CFPLMN_QUERY REQ��Ӧ�ļ�¼�� */
        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CFPLMN_QRY_REQ, &ucCtxIndex))
        {
            /*  �ظ�confirm */
            TAF_MMA_SndCFPlmnQueryCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                                      enRslt,
                                      pstCFPlmnCnf);

            TAF_MMA_ClearOperCtx(ucCtxIndex);
        }
    }
    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccCFPlmnSetCnfExpired_PreProc
 ��������  : �ȴ�MSCCģ���FPLMN CNF��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccCFPlmnSetCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_CFPLMN_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CFPLMN_SET_REQ, &ucCtxIndex))
    {
        /*  �ظ�MMA_CFPLMN_CNF */
        TAF_MMA_SndCFPlmnSetCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_MMA_APP_CFPLMN_OPER_RESULT_TIME_OUT);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccCFPlmnQueryCnfExpired_PreProc
 ��������  : �ȴ�MSCCģ���FPLMN CNF��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccCFPlmnQueryCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_CFPLMN_QUERY_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CFPLMN_QRY_REQ, &ucCtxIndex))
    {
        /*  �ظ�MMA_CFPLMN_QUERY_CNF */
        TAF_MMA_SndCFPlmnQueryCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_MMA_APP_CFPLMN_OPER_RESULT_TIME_OUT, VOS_NULL_PTR);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return VOS_TRUE;

}

/**********************************************************
 �� �� ��  : TAF_MMA_RcvMmaPrefPlmnSetReq_PreProc
 ��������  : CPOL���������
 �������  : ulEventType
             pstMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��3��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 ������
*************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaPrefPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PREF_PLMN_SET_REQ_STRU     *pstRcvMsg              = VOS_NULL_PTR;
    TAF_PH_SET_PREFPLMN_STRU           *pstPrefPlmnParam       = VOS_NULL_PTR;
    TAF_PH_PREF_PLMN_OPERATE_STRU       stPrefPlmnOpt;
    TAF_PLMN_ID_STRU                    stPlmnIdFromAt;
    VOS_UINT16                          usRet;
    VOS_UINT8                           ucUsimStatus;
    VOS_UINT8                           ucCtxIndex;

    pstRcvMsg         = (TAF_MMA_PREF_PLMN_SET_REQ_STRU *)pstMsg;
    pstPrefPlmnParam  = (TAF_PH_SET_PREFPLMN_STRU *)(&pstRcvMsg->stPrefPlmn);
    PS_MEM_SET(&stPrefPlmnOpt, 0x00, sizeof(TAF_PH_PREF_PLMN_OPERATE_STRU));
    PS_MEM_SET(&stPlmnIdFromAt, 0x00, sizeof(stPlmnIdFromAt));

    /* ��ȡ��״̬ */
    ucUsimStatus      = MMA_USIM_ABSENT;
    if (MMA_SUCCESS != MMA_GetUsimStatusFromUsim(&ucUsimStatus, VOS_NULL_PTR))
    {
        MMA_WARNINGLOG("TAF_MMA_RcvMmaPrefPlmnSetReq_PreProc():WORNING:Invoke MMA_GetUsimStatusFromUsim fail.");
        TAF_MMA_SndPrefPlmnSetCnf(&(pstRcvMsg->stCtrl), TAF_MMA_APP_PREF_PLMN_OPER_RESULT_USIM_ABSENT);

        return VOS_TRUE;
    }

    if (MMA_USIM_ABSENT == ucUsimStatus)
    {
        TAF_MMA_SndPrefPlmnSetCnf(&(pstRcvMsg->stCtrl), TAF_MMA_APP_PREF_PLMN_OPER_RESULT_USIM_ABSENT);

        return VOS_TRUE;
    }

    usRet = MMA_CheckCpolPara(pstPrefPlmnParam, &stPrefPlmnOpt);
    if (VOS_TRUE != usRet)
    {
        TAF_MMA_SndPrefPlmnSetCnf(&(pstRcvMsg->stCtrl), TAF_MMA_APP_PREF_PLMN_OPER_RESULT_CHECK_PARA_ERR);

        return VOS_TRUE;
    }

    /* �Ƚ�AT������PLMNID����ת�� */
    PS_MEM_CPY(&stPlmnIdFromAt, &stPrefPlmnOpt.stPlmn, sizeof(stPlmnIdFromAt));
    MMA_PlmnId2NasStyle(&stPlmnIdFromAt);


    MMA_PlmnId2Bcd(&stPlmnIdFromAt);
    if (VOS_FALSE == MN_PH_IsPlmnValid(&stPlmnIdFromAt))
    {
        TAF_MMA_SndPrefPlmnSetCnf(&(pstRcvMsg->stCtrl), TAF_MMA_APP_PREF_PLMN_OPER_RESULT_INVALID_PLMN);
        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPrefPlmnSetCnf(&(pstRcvMsg->stCtrl), TAF_MMA_APP_PREF_PLMN_OPER_RESULT_FAILURE);

        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstRcvMsg->stCtrl,
                       TAF_MMA_OPER_PREF_PLMN_SET_REQ,
                       ucCtxIndex);

    stPrefPlmnOpt.enPrefPLMNType = pstPrefPlmnParam->enPrefPlmnType;

    /* ��MSCC����ID_MMA_MSCC_PREF_PLMN_SET_REQ */
    TAF_MMA_SndMsccPrefPlmnSetReq(&(pstRcvMsg->stCtrl), &stPrefPlmnOpt);

    /* ����������ʱ��TI_TAF_MMA_WAIT_MSCC_PREM_CPOL_SET_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_SET_CNF, TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_SET_CNF_LEN);

    return VOS_TRUE;
}
/**********************************************************
 �� �� ��  : TAF_MMA_RcvMmaPrefPlmnTestReq_PreProc
 ��������  : CPOL���������
 �������  : ulEventType
             pstMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��3��
    ��    ��   : y00307564
    �޸�����   : Iteration 8 ������
*************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaPrefPlmnTestReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PREF_PLMN_TEST_REQ_STRU    *pstRcvMsg              = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstRcvMsg = (TAF_MMA_PREF_PLMN_TEST_REQ_STRU *)pstMsg;

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPrefPlmnTestCnf(&(pstRcvMsg->stCtrl), TAF_MMA_APP_PREF_PLMN_OPER_RESULT_FAILURE, VOS_NULL_PTR);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstRcvMsg->stCtrl,
                       TAF_MMA_OPER_PREF_PLMN_TEST_REQ, ucCtxIndex);

    TAF_MMA_SndMsccPrefPlmnTestReq(pstRcvMsg);

    /* ����������ʱ��TI_TAF_MMA_WAIT_MSCC_PREM_CPOL_TEST_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_TEST_CNF, TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_TEST_CNF_LEN);

    return VOS_TRUE;
}

/**********************************************************
 �� �� ��  : TAF_MMA_RcvMmaPrefPlmnQueryReq_PreProc
 ��������  : CPOL��ѯ�����
 �������  : ulEventType
             pstMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��3��
    ��    ��   : y00307564
    �޸�����   : Iteration 8����
*************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaPrefPlmnQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PREF_PLMN_QUERY_REQ_STRU   *pstRcvMsg              = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstRcvMsg = (TAF_MMA_PREF_PLMN_QUERY_REQ_STRU *)pstMsg;

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPrefPlmnQueryCnf(&(pstRcvMsg->stCtrl), TAF_MMA_APP_PREF_PLMN_OPER_RESULT_FAILURE, VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstRcvMsg->stCtrl,
                       TAF_MMA_OPER_PREF_PLMN_QUERY_REQ,
                       ucCtxIndex);

    /* ����ID_MMA_MSCC_PREF_PLMN_QUERY_REQ��MSCC */
    TAF_MMA_SndMsccPrefPlmnQueryReq(pstRcvMsg);

    /* ����������ʱ��TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF, TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF_LEN);

    return VOS_TRUE;
}

/**********************************************************
 �� �� ��  : TAF_MMA_RcvMsccPrefPlmnQueryCnf_PreProc
 ��������  : CPOL��ѯ�����
 �������  : ulEventType
             pstMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00307564
    �޸�����   : Iteration 8����
*************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccPrefPlmnQueryCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU  *pstRcvMsg       = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    pstRcvMsg = (MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU *)pstMsg;

    if (NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_SUCCESS != pstRcvMsg->enRslt)
    {
        enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
    }
    else
    {
        enRslt = TAF_MMA_APP_OPER_RESULT_SUCCESS;
    }

    if (NAS_MSCC_PIF_PREF_PLMN_QUERY == pstRcvMsg->enCmdType)
    {
        /* ͣ��ʱ�� */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF);

        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PREF_PLMN_QUERY_REQ, &ucCtxIndex))
        {
            TAF_MMA_SndPrefPlmnQueryCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), enRslt, pstRcvMsg);

            TAF_MMA_ClearOperCtx(ucCtxIndex);
        }
    }
    else if (NAS_MSCC_PIF_PREF_PLMN_TEST == pstRcvMsg->enCmdType)
    {
        /* ͣ��ʱ�� */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_TEST_CNF);

        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PREF_PLMN_TEST_REQ, &ucCtxIndex))
        {
            TAF_MMA_SndPrefPlmnTestCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), enRslt, pstRcvMsg);

            TAF_MMA_ClearOperCtx(ucCtxIndex);
        }
    }
    else
    {
        MMA_WARNINGLOG("TAF_MMA_RcvMsccPrefPlmnQueryCnf_PreProc: MSG enCmdType is wrong ");
    }

    return VOS_TRUE;
}

/**********************************************************
 �� �� ��  : TAF_MMA_RcvMsccPrefPlmnSetCnf_PreProc
 ��������  : CPOL���������
 �������  : ulEventType
             pstMsg
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00307564
    �޸�����   : Iteration 8����
*************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccPrefPlmnSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_PREF_PLMN_SET_CNF_STRU    *pstRcvMsg           = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx       = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    /* ͣ��ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_SET_CNF);

    pstRcvMsg = (MSCC_MMA_PREF_PLMN_SET_CNF_STRU *)pstMsg;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_PREF_PLMN_SET_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PREF_PLMN_SET_REQ, &ucCtxIndex))
    {
        TAF_MMA_SndPrefPlmnSetCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), pstRcvMsg->enRslt);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccPrefPlmnSetCnfExpired_PreProc
 ��������  : �ȴ�MSCCģ���pref plmn set CNF��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8����
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccPrefPlmnSetCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_PREF_PLMN_SET_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PREF_PLMN_SET_REQ, &ucCtxIndex))
    {
        TAF_MMA_SndPrefPlmnSetCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_MMA_APP_PREF_PLMN_OPER_RESULT_TIMEOUT);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccPrefPlmnQueryCnfExpired_PreProc
 ��������  : �ȴ�MSCCģ���pref plmn query CNF��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8����
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccPrefPlmnQueryCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU                                  *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                                               ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_PREF_PLMN_QUERY_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PREF_PLMN_QUERY_REQ, &ucCtxIndex))
    {
        TAF_MMA_SndPrefPlmnQueryCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                                       TAF_MMA_APP_PREF_PLMN_OPER_RESULT_TIMEOUT,
                                       VOS_NULL_PTR);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccPrefPlmnTestCnfExpired_PreProc
 ��������  : �ȴ�MSCCģ���pref plmn test CNF��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00307564
    �޸�����   : Iteration 8����
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccPrefPlmnTestCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU                                  *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                                               ucCtxIndex;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����TAF_MMA_OPER_PREF_PLMN_TEST_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PREF_PLMN_TEST_REQ, &ucCtxIndex))
    {
        TAF_MMA_SndPrefPlmnTestCnf(&(pstMmaOperCtx->stCtrl),
                                      TAF_MMA_APP_PREF_PLMN_OPER_RESULT_TIMEOUT,
                                      VOS_NULL_PTR);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvCerssiSetReq_PreProc
 ��������  : Mma PreProc Cerssi Set Req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��23��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvCerssiSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CERSSI_SET_REQ_STRU        *pstCerssiSeqReq = VOS_NULL;
    VOS_UINT32                          ulRptCmdStatus;
    VOS_UINT32                          ulRet;

    pstCerssiSeqReq = (TAF_MMA_CERSSI_SET_REQ_STRU *)pstMsg;

    if (0 == pstCerssiSeqReq->ucSignThreshold)
    {
        ulRptCmdStatus = VOS_FALSE;
    }
    else
    {
        ulRptCmdStatus = VOS_TRUE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CERSSI, ulRptCmdStatus);

    if ( (pstCerssiSeqReq->ucActionType > TAF_START_EVENT_INFO_STOP)
       ||(pstCerssiSeqReq->ucRrcMsgType > ( TAF_EVENT_INFO_CELL_BLER
                                           |TAF_EVENT_INFO_CELL_ID
                                           |TAF_EVENT_INFO_CELL_SIGN) ) )
    {
        MMA_WARNINGLOG("TAF_MMA_RcvCerssiSetReq_PreProc():WARNING:Error Para");

        TAF_MMA_SndCerssiSetCnf(&pstCerssiSeqReq->stCtrl, TAF_ERR_PARA_ERROR);

        return VOS_TRUE;
    }
    else
    {
        ulRet = TAF_MMA_SndMsccSignalReportReq(pstCerssiSeqReq->ucActionType, pstCerssiSeqReq->ucRrcMsgType,
                                               pstCerssiSeqReq->ucSignThreshold, pstCerssiSeqReq->ucMinRptTimerInterval);
    }

    if (VOS_OK == ulRet)
    {
        TAF_MMA_SndCerssiSetCnf(&pstCerssiSeqReq->stCtrl, TAF_PARA_OK);
    }
    else
    {
        TAF_MMA_SndCerssiSetCnf(&pstCerssiSeqReq->stCtrl, TAF_ERR_PARA_ERROR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvCerssiQryReq_PreProc
 ��������  : Mma PreProc Cerssi Qry Req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��24��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvCerssiQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CERSSI_INFO_QRY_CNF_STRU   *pstCerssiInfoQryCnf = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNetworkInfo   = VOS_NULL_PTR;
    TAF_MMA_CERSSI_INFO_QRY_REQ_STRU   *pstCerssiQryReq = VOS_NULL;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRatType;

    pstCerssiQryReq = (TAF_MMA_CERSSI_INFO_QRY_REQ_STRU *)pstMsg;

    enRatType           = TAF_SDC_GetAppSysMode();
    pstAppNetworkInfo   = &(TAF_SDC_GetSdcCtx()->stAppNetworkInfo);
    pstCerssiInfoQryCnf = (TAF_MMA_CERSSI_INFO_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                              WUEPS_PID_MMA,
                                                              sizeof(TAF_MMA_CERSSI_INFO_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstCerssiInfoQryCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvCerssiQryReq_PreProc:ERROR: Memory Alloc Error for pMsg");
        return VOS_TRUE;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstCerssiInfoQryCnf + VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(TAF_MMA_CERSSI_INFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣ */
    pstCerssiInfoQryCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstCerssiInfoQryCnf->ulMsgName              = ID_TAF_MMA_CERSSI_QRY_CNF;
    PS_MEM_CPY(&pstCerssiInfoQryCnf->stCtrl, &pstCerssiQryReq->stCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstCerssiInfoQryCnf->stCerssi.ucCurrentUtranMode    = NAS_UTRANCTRL_GetCurrUtranMode();
    pstCerssiInfoQryCnf->enErrorCause                   = TAF_ERR_NO_ERROR;
    pstCerssiInfoQryCnf->stCerssi.ucRssiNum             = 1;
    pstCerssiInfoQryCnf->stCerssi.enRatType             = enRatType;

    pstCerssiInfoQryCnf->stCerssi.aRssi[0].ucRssiValue   = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.ucRssiValue;
    pstCerssiInfoQryCnf->stCerssi.aRssi[0].ucChannalQual = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.ucChannalQual;

    switch (enRatType)
    {
        case TAF_SDC_SYS_MODE_GSM:
        {
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stGCellSignInfo.sRssiValue =  pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st2GCellSignInfo.sRssiValue;
        }
        break;
        case TAF_SDC_SYS_MODE_WCDMA:
        {
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sRscpValue;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sEcioValue = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sEcioValue;
        }
        break;
#if ( FEATURE_ON == FEATURE_LTE )
        case TAF_SDC_SYS_MODE_LTE:
        {
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.lSINR           = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.lSINR;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsd            = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsd;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrp           = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsrp;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrq           = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsrq;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRssi           = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRssi;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.usRI      = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.usRI;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[0] = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[0];
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[1] = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[1];
        }
        break;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TAF_SDC_SYS_MODE_SVLTE:
        {
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.lSINR           = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.lSINR;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsd            = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsd;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrp           = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsrp;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRsrq           = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsrq;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.sRssi           = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRssi;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.usRI      = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.usRI;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[0] = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[0];
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stLCellSignInfo.stCQI.ausCQI[1] = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.stCQI.ausCQI[1];

            pstCerssiInfoQryCnf->stCerssi.enRatType = TAF_SDC_SYS_MODE_LTE;
        }
        break;
#endif

        default:
        /*��δפ���ɹ���������Чֵ*/
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stGCellSignInfo.sRssiValue = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st2GCellSignInfo.sRssiValue;
            pstCerssiInfoQryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue = pstAppNetworkInfo->stAppSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sRscpValue;

            MMA_WARNINGLOG1("TAF_MMA_RcvCerssiQryReq_PreProc():WARNING:TAF_SDC_GetAppSysMode():", enRatType);
         break;
    }


    /* ������Ϣ */
    if( VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstCerssiInfoQryCnf))
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR, "TAF_MMA_RcvCerssiQryReq_PreProc:ERROR: Send Msg Error!");
    }

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_RcvAcInfoQry_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_AC_INFO_QRY_REQ_STRU       *pstRcvMsg       = VOS_NULL_PTR;
    TAF_MMA_AC_INFO_QRY_CNF_STRU       *pstAcInfoQryCnf = VOS_NULL_PTR;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRadioMode;
    TAF_SDC_ACCESS_RESTRICTION_STRU    *pstCsAcRestriction = VOS_NULL_PTR;
    TAF_SDC_ACCESS_RESTRICTION_STRU    *pstPsAcRestriction = VOS_NULL_PTR;

    pstRcvMsg = (TAF_MMA_AC_INFO_QRY_REQ_STRU *)pstMsg;

    pstCsAcRestriction = TAF_SDC_GetCsAcRestriction();
    pstPsAcRestriction = TAF_SDC_GetPsAcRestriction();
    pstAcInfoQryCnf    = (TAF_MMA_AC_INFO_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                         WUEPS_PID_MMA,
                                                         sizeof(TAF_MMA_AC_INFO_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstAcInfoQryCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvAcInfoQry_PreProc:ERROR: Memory Alloc Error");
        return VOS_TRUE;
    }

    /* Set the allocated memory with 0 */
    PS_MEM_SET( (VOS_UINT8 *)pstAcInfoQryCnf + VOS_MSG_HEAD_LENGTH,
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_AC_INFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* Assigning the values to cnf message */
    pstAcInfoQryCnf->ulReceiverPid          = pstRcvMsg->stCtrl.ulModuleId;
    pstAcInfoQryCnf->ulMsgName              = ID_TAF_MMA_AC_INFO_QRY_CNF;
    pstAcInfoQryCnf->stCtrl.usClientId      = MN_GetRealClientId(pstRcvMsg->stCtrl.usClientId, WUEPS_PID_MMA);
    pstAcInfoQryCnf->stCtrl.ucOpId          = pstRcvMsg->stCtrl.ucOpId;
    pstAcInfoQryCnf->stCtrl.ulModuleId      = pstRcvMsg->stCtrl.ulModuleId;

    /* Get RadioAccess Mode */
    enRadioMode = TAF_SDC_GetSysMode();

    if (TAF_SDC_SYS_MODE_LTE == enRadioMode)
    {
        /* Setting result with ERROR and send message */
        pstAcInfoQryCnf->ulRslt = TAF_ERR_ERROR;
    }
    else
    {
        pstAcInfoQryCnf->ulRslt = TAF_ERR_NO_ERROR;

        pstAcInfoQryCnf->stCellCsAcInfo.enSrvDomain           = TAF_MMA_SERVICE_DOMAIN_CS;
        pstAcInfoQryCnf->stCellCsAcInfo.enCellAcType          = pstCsAcRestriction->enCellAcType;
        pstAcInfoQryCnf->stCellCsAcInfo.ucRestrictPagingRsp   = pstCsAcRestriction->ucRestrictPagingRsp;
        pstAcInfoQryCnf->stCellCsAcInfo.ucRestrictRegister    = pstCsAcRestriction->ucRestrictRegister;

        pstAcInfoQryCnf->stCellPsAcInfo.enSrvDomain           = TAF_MMA_SERVICE_DOMAIN_PS;
        pstAcInfoQryCnf->stCellPsAcInfo.enCellAcType          = pstPsAcRestriction->enCellAcType;
        pstAcInfoQryCnf->stCellPsAcInfo.ucRestrictPagingRsp   = pstPsAcRestriction->ucRestrictPagingRsp;
        pstAcInfoQryCnf->stCellPsAcInfo.ucRestrictRegister    = pstPsAcRestriction->ucRestrictRegister;
    }

    /* Sending message */
    PS_SEND_MSG(WUEPS_PID_MMA, pstAcInfoQryCnf);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvCopnInfoQry_PreProc(
             VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
)
{
    TAF_MMA_COPN_INFO_QRY_REQ_STRU     *pstCopnQerReq = VOS_NULL_PTR;
    TAF_MMA_COPN_INFO_QRY_CNF_STRU     *pstCopnQryCnf = VOS_NULL_PTR;
    VOS_UINT16                          usPlmnNum;
    VOS_UINT16                          usRemainPlmnNum;
    VOS_UINT16                          usTotal;
    VOS_UINT32                          ulMsgSize;

    pstCopnQerReq = (TAF_MMA_COPN_INFO_QRY_REQ_STRU*)pstMsg;

    /*
        ���÷��������־�ͷ����ϱ���Ӫ�̸���: �����͵���Ӫ��������һ����Ϣ��
        �����͵���Ӫ�����������ý�����־���������д�������Ӫ����Ϣ��
    */
    usTotal             = TAF_MMA_GetNetWorkNameTblSize();

    if (pstCopnQerReq->usFromIndex > usTotal)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_WARNING,
                "TAF_MMA_RcvCopnInfoQry_PreProc: abnormal request!");
        usPlmnNum = 0;
    }
    else
    {
        usRemainPlmnNum = usTotal - (pstCopnQerReq->usFromIndex);

        if (usRemainPlmnNum < pstCopnQerReq->usPlmnNum)
        {
            usPlmnNum = usRemainPlmnNum;
        }
        else
        {
            usPlmnNum = pstCopnQerReq->usPlmnNum;
        }
    }

    if (0 < usPlmnNum)
    {
        ulMsgSize  = sizeof(TAF_MMA_COPN_INFO_QRY_CNF_STRU) - sizeof(pstCopnQryCnf->aucContent);
        ulMsgSize += usPlmnNum * sizeof(TAF_PH_OPERATOR_NAME_STRU);
    }
    else
    {
        ulMsgSize  = sizeof(TAF_MMA_COPN_INFO_QRY_CNF_STRU);
    }

    /* ��TAF_PH_COPN_PLMN_MAX_NUM����Ӫ��Ϊһ������ϱ���Ӫ����Ϣ */
    pstCopnQryCnf  = (TAF_MMA_COPN_INFO_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                       WUEPS_PID_MMA,
                                                       ulMsgSize);

    if (VOS_NULL_PTR == pstCopnQryCnf)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_RcvCopnInfoQry_PreProc: Memory Alloc Error for pMsg!");
        return VOS_TRUE;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET( (VOS_UINT8 *)pstCopnQryCnf + VOS_MSG_HEAD_LENGTH,
                0x00,
                (VOS_SIZE_T)(ulMsgSize - VOS_MSG_HEAD_LENGTH) );

    /* ��д��Ϣͷ����Ϣ */
    pstCopnQryCnf->ulReceiverPid          = pstCopnQerReq->stCtrl.ulModuleId;
    pstCopnQryCnf->ulMsgName              = ID_TAF_MMA_COPN_INFO_QRY_CNF;
    PS_MEM_CPY(&pstCopnQryCnf->stCtrl, &pstCopnQerReq->stCtrl, sizeof(TAF_MMA_CTRL_STRU));

    /*
    ��ulFromIndex��ʼ��gastNetworkNameTbl����Ӫ����Ϣ��д��
    pstCopnQryCnf->astOperNameList�ṹ���飬
    ��Ӫ�̵ĸ���ΪpstCopnQryCnf->usPlmnNum
    */
    TAF_MMA_FillCopnOperNameList(pstCopnQerReq->usFromIndex, usPlmnNum, pstCopnQryCnf);

    pstCopnQryCnf->usFromIndex = pstCopnQerReq->usFromIndex;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCopnQryCnf);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvSimInsertReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SIM_INSERT_REQ_STRU        *pstSimInsertReq = VOS_NULL_PTR;
    TAF_MMA_SIM_INSERT_CNF_STRU        *pstSimInsertCnf = VOS_NULL_PTR;

    pstSimInsertReq = (TAF_MMA_SIM_INSERT_REQ_STRU*) pstMsg;

    pstSimInsertCnf  = (TAF_MMA_SIM_INSERT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                      WUEPS_PID_MMA,
                                                      sizeof(TAF_MMA_SIM_INSERT_CNF_STRU));

    if (VOS_NULL_PTR == pstSimInsertCnf)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_RcvSimInsertReq_PreProc: Memory Alloc Error for pMsg!");
        return VOS_TRUE;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET( (VOS_UINT8 *)pstSimInsertCnf + VOS_MSG_HEAD_LENGTH,
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_SIM_INSERT_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    /* ��д��Ϣͷ����Ϣ */
    pstSimInsertCnf->ulReceiverPid          = pstSimInsertReq->stCtrl.ulModuleId;
    pstSimInsertCnf->ulMsgName              = ID_TAF_MMA_SIM_INSERT_CNF;
    PS_MEM_CPY(&pstSimInsertCnf->stCtrl, &pstSimInsertReq->stCtrl, sizeof(TAF_MMA_CTRL_STRU));

    if (TAF_SIM_INSERT_STATE_REMOVE == pstSimInsertReq->enSimInsertState)
    {
        if (USIMM_API_SUCCESS == NAS_USIMMAPI_DeactiveCardReq(WUEPS_PID_MMA))
        {
            pstSimInsertCnf->ulResult = VOS_OK;
        }
        else
        {
            pstSimInsertCnf->ulResult = VOS_ERR;
        }
    }
    else
    {
        pstSimInsertCnf->ulResult = VOS_OK;
    }

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstSimInsertCnf);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvEOPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_EOPLMN_SET_REQ_STRU        *pstSetEOPlmnReq = VOS_NULL_PTR;

    pstSetEOPlmnReq = (TAF_MMA_EOPLMN_SET_REQ_STRU *)pstMsg;

    /* ����������*/
    gstMmaValue.stEOPlmnSet.usClientId = pstSetEOPlmnReq->stCtrl.usClientId;
    gstMmaValue.stEOPlmnSet.ucOpId     = pstSetEOPlmnReq->stCtrl.ucOpId;

    /* ��MSCCģ�鷢��ID_MMA_MSCC_EOPLMN_SET_REQ */
    TAF_MMA_SndMsccEOPlmnSetReq(&(pstSetEOPlmnReq->stEOPlmnSetPara));

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvEOPlmnQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulLen;
    TAF_MMA_EOPLMN_QRY_REQ_STRU                            *pstEOPlmnQryReq = VOS_NULL_PTR;
    TAF_MMA_EOPLMN_QRY_CNF_STRU                            *pstEOPlmnQryCnf = VOS_NULL_PTR;
    NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU                *pstNvimCfgOPlmnInfo = VOS_NULL_PTR;

    ulLen           = 0;
    pstEOPlmnQryReq = (TAF_MMA_EOPLMN_QRY_REQ_STRU *)pstMsg;

    pstNvimCfgOPlmnInfo = (NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU*)PS_MEM_ALLOC(
                                                                    WUEPS_PID_MMA,
                                                                    sizeof(NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU));
    if (VOS_NULL_PTR == pstNvimCfgOPlmnInfo)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvEOPlmnQryReq_PreProc():ERROR: Memory Alloc Error");
        return VOS_TRUE;
    }
    PS_MEM_SET(pstNvimCfgOPlmnInfo, 0x00, sizeof(NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU));


    pstEOPlmnQryCnf = (TAF_MMA_EOPLMN_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                     WUEPS_PID_MMA,
                                                     sizeof(TAF_MMA_EOPLMN_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstEOPlmnQryCnf)
    {
        MN_ERR_LOG("TAF_MMA_RcvEOPlmnQryReq_PreProc: Alloc Msg Failed!");
        PS_MEM_FREE(WUEPS_PID_MMA, pstNvimCfgOPlmnInfo);
        return VOS_TRUE;
    }

    PS_MEM_SET( (VOS_INT8 *)pstEOPlmnQryCnf + VOS_MSG_HEAD_LENGTH, 0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_EOPLMN_QRY_CNF_STRU)  - VOS_MSG_HEAD_LENGTH) );

    /* ��NV��en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST��ʧ�ܣ�ֱ�ӷ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST, &ulLen);

    if (NV_OK != NV_Read(en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST,
                         pstNvimCfgOPlmnInfo, ulLen))
    {
        MN_ERR_LOG("TAF_MMA_RcvEOPlmnQryReq_PreProc():WARNING: read en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST Error");
        /* �����Ϣ */
        pstEOPlmnQryCnf->ulResult = TAF_ERR_ERROR;
    }
    else
    {
        /* �����Ϣ */
        pstEOPlmnQryCnf->ulResult = TAF_ERR_NO_ERROR;
    }

    /* �����Ϣͷ */;
    pstEOPlmnQryCnf->ulReceiverPid          = pstEOPlmnQryReq->stCtrl.ulModuleId;
    pstEOPlmnQryCnf->ulMsgName              = ID_TAF_MMA_EOPLMN_QRY_CNF;
    PS_MEM_CPY(&pstEOPlmnQryCnf->stCtrl, &pstEOPlmnQryReq->stCtrl, sizeof(TAF_MMA_CTRL_STRU));

    PS_MEM_CPY(pstEOPlmnQryCnf->aucVersion,
               pstNvimCfgOPlmnInfo->aucVersion,
               NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN * sizeof(VOS_UINT8));

    pstEOPlmnQryCnf->usOPlmnNum = pstNvimCfgOPlmnInfo->usOplmnListNum;

    PS_MEM_CPY(pstEOPlmnQryCnf->aucOPlmnList,
               pstNvimCfgOPlmnInfo->aucOPlmnList,
               NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN * sizeof(VOS_UINT8));

    PS_SEND_MSG(WUEPS_PID_MMA, pstEOPlmnQryCnf);

    PS_MEM_FREE(WUEPS_PID_MMA, pstNvimCfgOPlmnInfo);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvNetScanReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_NET_SCAN_REQ_STRU          *pstNetScanSetPara   = VOS_NULL_PTR;
    TAF_MMA_NET_SCAN_CNF_STRU          *pstNetScanCnf       = VOS_NULL_PTR;

    pstNetScanSetPara = (TAF_MMA_NET_SCAN_REQ_STRU *)pstMsg;

    if ( STA_FSM_ENABLE != g_StatusContext.ulFsmState )
    {

        pstNetScanCnf  = (TAF_MMA_NET_SCAN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                      WUEPS_PID_MMA,
                                                      sizeof(TAF_MMA_NET_SCAN_CNF_STRU));

        if (VOS_NULL_PTR == pstNetScanCnf)
        {
            TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                    "TAF_MMA_RcvNetScanReq_PreProc: Memory Alloc Error for pMsg!");
            return VOS_TRUE;
        }

        PS_MEM_SET( (VOS_UINT8 *)pstNetScanCnf + VOS_MSG_HEAD_LENGTH, 0x00,
                    (VOS_SIZE_T)(sizeof(TAF_MMA_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

        pstNetScanCnf->ulReceiverPid            = pstNetScanSetPara->stCtrl.ulModuleId;
        pstNetScanCnf->ulMsgName                = ID_TAF_MMA_NET_SCAN_CNF;
        pstNetScanCnf->usClientId               = MN_GetRealClientId(pstNetScanSetPara->stCtrl.usClientId, WUEPS_PID_TAF);
        pstNetScanCnf->ucOpId                   = pstNetScanSetPara->stCtrl.ucOpId;
        pstNetScanCnf->enResult                 = TAF_MMA_NET_SCAN_RESULT_FAILURE;
        pstNetScanCnf->enCause                  = TAF_MMA_NET_SCAN_CAUSE_MMA_STATE_DISABLE;

        PS_SEND_MSG(WUEPS_PID_MMA, pstNetScanCnf);

        return VOS_TRUE;
    }

    /* ����^NETSCAN�·���ClientId��OpId */
    gstMmaValue.stNetScan.usClientId = pstNetScanSetPara->stCtrl.usClientId;
    gstMmaValue.stNetScan.ucOpId     = pstNetScanSetPara->stCtrl.ucOpId;

    /* ��MSCCģ�鷢��NETSCAN REQ */
    TAF_MMA_SndMsccNetScanMsgReq(pstNetScanSetPara);

    /* ����STA_TIMER_NET_SCAN 108s��ʱ���������ʱδ�յ�MSCC�Ļظ����MSCC����ABORT NET SCAN REQ */
    TAF_MMA_StartNetScanProtectTimer();

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_RcvAbortNetScanReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_NET_SCAN_ABORT_REQ_STRU    *pstNetScanAbortReq = VOS_NULL_PTR;

    pstNetScanAbortReq  = (TAF_MMA_NET_SCAN_ABORT_REQ_STRU*)pstMsg;

    if ( MMA_TIMER_RUN == g_stNetScanProtectTimer.ucTimerStatus )
    {
        TAF_MMA_StopNetScanProtectTimer();

        /* ����^NETSCAN�·���ClientId��OpId */
        gstMmaValue.stNetScan.usClientId = pstNetScanAbortReq->stCtrl.usClientId;
        gstMmaValue.stNetScan.ucOpId     = pstNetScanAbortReq->stCtrl.ucOpId;

        /* ��MSCCģ�鷢�ʹ��NETSCAN REQ */
        TAF_MMA_SndMsccAbortNetScanMsgReq();

        /* ����TI_TAF_MMA_ABORT_NET_SCAN_TIMER 10s��ʱ�� */
        (VOS_VOID)TAF_MMA_StartAbortNetScanProtectTimer();
    }

    /* MMA������ʱ����ʱ�󣬸�MSCC����ABORT������û���ʱ���·��������
       ������û��·��Ĵ������ */

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvUserSrvStateQry_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_USER_SRV_STATE_QRY_CNF_STRU  *pstUserservstateCnf   = VOS_NULL_PTR;
    TAF_MMA_USER_SRV_STATE_QRY_REQ_STRU  *pstRcvMsg             = VOS_NULL_PTR;
    VOS_UINT8                           ucCsServiceConnStatusFlag;

    pstRcvMsg = (TAF_MMA_USER_SRV_STATE_QRY_REQ_STRU *)pstMsg;

    pstUserservstateCnf  = (TAF_MMA_USER_SRV_STATE_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                  WUEPS_PID_MMA,
                                                                  sizeof(TAF_MMA_USER_SRV_STATE_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstUserservstateCnf)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_RcvUserSrvStateQry_PreProc: Memory Alloc Error for pMsg!");
        return VOS_TRUE;
    }

    PS_MEM_SET( (VOS_UINT8 *)pstUserservstateCnf + VOS_MSG_HEAD_LENGTH,
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_USER_SRV_STATE_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );


    ucCsServiceConnStatusFlag               = TAF_SDC_GetCsServiceConnStatusFlag();
    pstUserservstateCnf->ulCsSrvExistFlg    = VOS_FALSE;

    /* ��ȡ��ǰ�Ƿ���CSҵ�� */
    if ((VOS_TRUE == TAF_SDC_GetCsSrvExistFlg())
     || (VOS_TRUE == ucCsServiceConnStatusFlag))
    {
        pstUserservstateCnf->ulCsSrvExistFlg = VOS_TRUE;
    }
    pstUserservstateCnf->ulReceiverPid          = pstRcvMsg->stCtrl.ulModuleId;
    pstUserservstateCnf->ulMsgName              = ID_TAF_MMA_USER_SRV_STATE_QRY_CNF;
    pstUserservstateCnf->usClientId             = pstRcvMsg->stCtrl.usClientId;
    pstUserservstateCnf->ucOpId                 = pstRcvMsg->stCtrl.ucOpId;

    /* Ŀǰֻ�ṩCSҵ���Ƿ���ڵĲ�ѯ��PSҵ��Ĳ�ѯ���ṩ���̶����0 */
    pstUserservstateCnf->ulPsSrvExistFlg = VOS_FALSE;

    PS_SEND_MSG(WUEPS_PID_MMA, pstUserservstateCnf);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvApPwrOnAndRegTimeQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU             *pstAppwronregCnf = VOS_NULL_PTR;
    TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ_STRU             *pstRcvMsg        = VOS_NULL_PTR;

    pstRcvMsg = (TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ_STRU *)pstMsg;

    pstAppwronregCnf  = (TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                      WUEPS_PID_MMA,
                                                                      sizeof(TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstAppwronregCnf)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_RcvApPwrOnAndRegTimeQryReq_PreProc: Memory Alloc Error for pMsg!");
        return VOS_TRUE;
    }

    PS_MEM_SET( (VOS_UINT8 *)pstAppwronregCnf + VOS_MSG_HEAD_LENGTH,
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstAppwronregCnf->ulReceiverPid             = pstRcvMsg->stCtrl.ulModuleId;
    pstAppwronregCnf->ulMsgName                 = ID_TAF_MMA_POWER_ON_AND_REG_TIME_QRY_CNF;
    pstAppwronregCnf->usClientId                = pstRcvMsg->stCtrl.usClientId;
    pstAppwronregCnf->ucOpId                    = pstRcvMsg->stCtrl.ucOpId;

    pstAppwronregCnf->ulCostTime                = MN_PH_GetRegCostTime();

    PS_SEND_MSG(WUEPS_PID_MMA, pstAppwronregCnf);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvSpnQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SPN_QRY_REQ_STRU           *pstSpnReq          = VOS_NULL_PTR;
    TAF_MMA_SPN_QRY_CNF_STRU           *pstSpnCnf          = VOS_NULL_PTR;
    TAF_SDC_SPN_FILE_INFO_STRU         *pstUsimSpnFileInfo = VOS_NULL_PTR;
    TAF_SDC_SPN_FILE_INFO_STRU         *pstSimSpnFileInfo  = VOS_NULL_PTR;

    pstSpnReq          = (TAF_MMA_SPN_QRY_REQ_STRU *)pstMsg;
    pstUsimSpnFileInfo = TAF_SDC_GetUsimSpnFileInfo();
    pstSimSpnFileInfo  = TAF_SDC_GetSimSpnFileInfo();

    pstSpnCnf  = (TAF_MMA_SPN_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_SPN_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstSpnCnf)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_RcvSpnQryReq_PreProc: Memory Alloc Error for pMsg!");
        return VOS_TRUE;
    }

    PS_MEM_SET( (VOS_UINT8 *)pstSpnCnf + VOS_MSG_HEAD_LENGTH,
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_SPN_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstSpnCnf->ulReceiverPid          = pstSpnReq->stCtrl.ulModuleId;
    pstSpnCnf->ulMsgName              = ID_TAF_MMA_SPN_QRY_CNF;
    pstSpnCnf->usClientId             = pstSpnReq->stCtrl.usClientId;
    pstSpnCnf->ucOpId                 = pstSpnReq->stCtrl.ucOpId;

    /* SIM SPN */
    pstSpnCnf->stMnMmaSpnInfo.stSimSpnInfo.ucCoding        = pstSimSpnFileInfo->stSpnOperName.bitCoding;
    pstSpnCnf->stMnMmaSpnInfo.stSimSpnInfo.ucSpareBit      = pstSimSpnFileInfo->stSpnOperName.bitSpare;
    pstSpnCnf->stMnMmaSpnInfo.stSimSpnInfo.ucLength        = pstSimSpnFileInfo->stSpnOperName.ucLength;
    pstSpnCnf->stMnMmaSpnInfo.stSimSpnInfo.ucDispRplmnMode = pstSimSpnFileInfo->ucDispRplmnMode;
    PS_MEM_CPY(pstSpnCnf->stMnMmaSpnInfo.stSimSpnInfo.aucSpnName, pstSimSpnFileInfo->stSpnOperName.aucOperatorName, TAF_SDC_MAX_OPER_NAME_NUM);

    /* USIM SPN */
    pstSpnCnf->stMnMmaSpnInfo.stUsimSpnInfo.ucCoding        = pstUsimSpnFileInfo->stSpnOperName.bitCoding;
    pstSpnCnf->stMnMmaSpnInfo.stUsimSpnInfo.ucSpareBit      = pstUsimSpnFileInfo->stSpnOperName.bitSpare;
    pstSpnCnf->stMnMmaSpnInfo.stUsimSpnInfo.ucLength        = pstUsimSpnFileInfo->stSpnOperName.ucLength;
    pstSpnCnf->stMnMmaSpnInfo.stUsimSpnInfo.ucDispRplmnMode = pstUsimSpnFileInfo->ucDispRplmnMode;
    PS_MEM_CPY(pstSpnCnf->stMnMmaSpnInfo.stUsimSpnInfo.aucSpnName, pstUsimSpnFileInfo->stSpnOperName.aucOperatorName, TAF_SDC_MAX_OPER_NAME_NUM);

    PS_SEND_MSG(WUEPS_PID_MMA, pstSpnCnf);

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_RcvMMPlmnInfoQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_MMPLMNINFO_QRY_REQ_STRU    *pstMMPlmnInfoReq = VOS_NULL_PTR;
    TAF_MMA_MMPLMNINFO_QRY_CNF_STRU    *pstMMPlmnInfoCnf = VOS_NULL_PTR;
    TAF_PLMN_ID_STRU                   *pstPlmnId        = VOS_NULL_PTR;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;

    TAF_SDC_MM_INFO_STRU               *pstMmInfo = VOS_NULL_PTR;

    pstMmInfo = TAF_SDC_GetMmInfo();

    pstMMPlmnInfoReq = (TAF_MMA_MMPLMNINFO_QRY_REQ_STRU *)pstMsg;

    pstMMPlmnInfoCnf  = (TAF_MMA_MMPLMNINFO_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                           WUEPS_PID_MMA,
                                                           sizeof(TAF_MMA_MMPLMNINFO_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstMMPlmnInfoCnf)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_RcvMMPlmnInfoQryReq_PreProc: Memory Alloc Error for pMsg!");
        return VOS_TRUE;
    }

    PS_MEM_SET( (VOS_CHAR *)pstMMPlmnInfoCnf + VOS_MSG_HEAD_LENGTH,
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_MMPLMNINFO_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstMMPlmnInfoCnf->ulReceiverPid          = pstMMPlmnInfoReq->stCtrl.ulModuleId;
    pstMMPlmnInfoCnf->ulMsgName              = ID_TAF_MMA_MMPLMNINFO_QRY_CNF;
    pstMMPlmnInfoCnf->usClientId             = pstMMPlmnInfoReq->stCtrl.usClientId;
    pstMMPlmnInfoCnf->ucOpId                 = pstMMPlmnInfoReq->stCtrl.ucOpId;

    enCsServiceStatus = TAF_SDC_GetAppCsServiceStatus();
    enPsServiceStatus = TAF_SDC_GetAppPsServiceStatus();

    if ( (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
      || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enPsServiceStatus) )
    {
        pstPlmnId = (TAF_PLMN_ID_STRU*)TAF_SDC_GetAppServicePlmnId();

        if ((pstPlmnId->Mcc == pstMmInfo->stOperatorPlmnId.ulMcc)
        &&  (pstPlmnId->Mnc == pstMmInfo->stOperatorPlmnId.ulMnc))
        {
            pstMMPlmnInfoCnf->stMmPlmnInfo.ucLongNameLen  = TAF_MMA_TranslateOperatorName2UCS2(&pstMmInfo->stOperatorNameLong,
                                                            (VOS_CHAR *)(pstMMPlmnInfoCnf->stMmPlmnInfo.aucLongName),
                                                             NAS_MML_MAX_OPER_LONG_NAME_LEN);

            pstMMPlmnInfoCnf->stMmPlmnInfo.ucShortNameLen = TAF_MMA_TranslateOperatorName2UCS2(&pstMmInfo->stOperatorNameShort,
                                                            (VOS_CHAR *)(pstMMPlmnInfoCnf->stMmPlmnInfo.aucShortName),
                                                            NAS_MML_MAX_OPER_SHORT_NAME_LEN);
        }
    }

    PS_SEND_MSG(WUEPS_PID_MMA, pstMMPlmnInfoCnf);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvPlmnQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_LAST_CAMP_PLMN_QRY_REQ_STRU                    *pstPlmnReq = VOS_NULL_PTR;
    TAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU                    *pstPlmnCnf = VOS_NULL_PTR;
    TAF_SDC_PLMN_ID_STRU                                   *pstCurrCampPlmnId = VOS_NULL_PTR;

    pstPlmnReq = (TAF_MMA_LAST_CAMP_PLMN_QRY_REQ_STRU *)pstMsg;

    pstPlmnCnf  = (TAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                         WUEPS_PID_MMA,
                                                         sizeof(TAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstPlmnCnf)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL_PTR, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_RcvPlmnQryReq_PreProc: Memory Alloc Error for pMsg!");
        return VOS_TRUE;
    }

    PS_MEM_SET( (VOS_CHAR *)pstPlmnCnf + VOS_MSG_HEAD_LENGTH,
                0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_LAST_CAMP_PLMN_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstPlmnCnf->ulReceiverPid          = pstPlmnReq->stCtrl.ulModuleId;
    pstPlmnCnf->ulMsgName              = ID_TAF_MMA_LAST_CAMP_PLMN_QRY_CNF;
    pstPlmnCnf->usClientId             = pstPlmnReq->stCtrl.usClientId;
    pstPlmnCnf->ucOpId                 = pstPlmnReq->stCtrl.ucOpId;

    pstCurrCampPlmnId = TAF_SDC_GetCurrCampPlmnId();

    pstPlmnCnf->stPlmnId.Mcc = pstCurrCampPlmnId->ulMcc;
    pstPlmnCnf->stPlmnId.Mnc = pstCurrCampPlmnId->ulMnc;

    MMA_PlmnId2Bcd(&(pstPlmnCnf->stPlmnId));

    PS_SEND_MSG(WUEPS_PID_MMA, pstPlmnCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaSetCqstReq_PreProc
 ��������  : AT^CQST
 �������  : ulEventType *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��24��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaSetCqstReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_QUICKSTART_SET_REQ_STRU                        *pstRcvMsg;
    TAF_MMA_QUICKSTART_SET_CNF_STRU                        *pstQuickStartSetCnf;
    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU                   stQuickStartFlg;
    VOS_UINT32                                              ulResult;

    pstRcvMsg              = (TAF_MMA_QUICKSTART_SET_REQ_STRU *)pstMsg;

    pstQuickStartSetCnf    = (TAF_MMA_QUICKSTART_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                sizeof(TAF_MMA_QUICKSTART_SET_CNF_STRU));
    if (VOS_NULL_PTR == pstQuickStartSetCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvMmaSetCqstReq_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstQuickStartSetCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_QUICKSTART_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstQuickStartSetCnf->ulReceiverPid          = pstRcvMsg->stCtrl.ulModuleId;
    pstQuickStartSetCnf->ulMsgName              = ID_TAF_MMA_QUICKSTART_SET_CNF;
    pstQuickStartSetCnf->usClientId             = pstRcvMsg->stCtrl.usClientId;
    pstQuickStartSetCnf->ucOpId                 = pstRcvMsg->stCtrl.ucOpId;

    if (0 == pstRcvMsg->ulQuickStartMode)
    {
        stQuickStartFlg.ulQuickStartSta = MMA_QUICK_START_DISABLE;
    }
    else
    {
        stQuickStartFlg.ulQuickStartSta = MMA_QUICK_START_ENABLE;
    }

    ulResult = MMA_WriteValue2Nvim(en_NV_Item_FollowOn_OpenSpeed_Flag,
                                  (VOS_VOID *)(&stQuickStartFlg),
                                   sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU));

    if (MMA_SUCCESS != ulResult)
    {
        pstQuickStartSetCnf->ucResult   = TAF_PARA_WRITE_NVIM_ERROR;

        /* ������Ϣ */
        PS_SEND_MSG(WUEPS_PID_MMA, pstQuickStartSetCnf);
    }
    else
    {
        gstMmaValue.ulQuickStartFlg     = stQuickStartFlg.ulQuickStartSta;

        pstQuickStartSetCnf->ucResult   = TAF_PARA_OK;

        /* ������Ϣ */
        PS_SEND_MSG(WUEPS_PID_MMA, pstQuickStartSetCnf);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaQryQuickStartReq_PreProc
 ��������  : ���ٿ�����ѯ�������Ϣ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��27��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaQryQuickStartReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_QUICKSTART_QRY_REQ_STRU     *pstRcvMsg;
    TAF_MMA_QUICKSTART_QRY_CNF_STRU     *pstQuickStartQryCnf;

    pstRcvMsg  = (TAF_MMA_QUICKSTART_QRY_REQ_STRU *)pstMsg;

    pstQuickStartQryCnf = (TAF_MMA_QUICKSTART_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                             sizeof(TAF_MMA_QUICKSTART_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstQuickStartQryCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvMmaQryQuickStartReq_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstQuickStartQryCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_QUICKSTART_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));


    pstQuickStartQryCnf->ulReceiverPid            = WUEPS_PID_AT;
    pstQuickStartQryCnf->ulMsgName                = ID_TAF_MMA_QUICKSTART_QRY_CNF;
    pstQuickStartQryCnf->usClientId               = pstRcvMsg->stCtrl.usClientId;
    pstQuickStartQryCnf->ucOpId                   = pstRcvMsg->stCtrl.ucOpId;
    pstQuickStartQryCnf->enErrorCause             = TAF_ERR_NO_ERROR;

    if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        pstQuickStartQryCnf->ulQuickStartMode = 1;
    }
    else
    {
        pstQuickStartQryCnf->ulQuickStartMode = 0;
    }

    /* ��Ϣ���� */
    PS_SEND_MSG(WUEPS_PID_MMA, pstQuickStartQryCnf);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaQryCrpnReq_PreProc
 ��������  : AT^CRPN����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��24��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��3��5��
    ��    ��   : b00269685
    �޸�����   : �޸�Ϊ�ֶ��ϱ�

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaQryCrpnReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PH_OPERATOR_NAME_STRU           stOrigOperName;
    VOS_UINT8                           ucMaxMncLen;
    VOS_UINT8                           ucSendNum;
    VOS_UINT8                           ucLeftNum;
    VOS_UINT32                          ulTotalNum;
    TAF_MMA_CRPN_QRY_INFO_STRU         *pstMnMmaCrpnQryCnf;
    TAF_PH_OPERATOR_NAME_STRU          *pstOperName;
    VOS_UINT32                          i;
    TAF_MMA_CRPN_QRY_REQ_STRU          *pstRcvMsg;

    pstRcvMsg = (TAF_MMA_CRPN_QRY_REQ_STRU *)pstMsg;

    /* ������ʼ�� */
    pstMnMmaCrpnQryCnf = VOS_NULL_PTR;
    pstOperName        = VOS_NULL_PTR;
    PS_MEM_SET(&stOrigOperName, 0, sizeof(TAF_PH_OPERATOR_NAME_STRU));

    /* ��ȡ����������PLMN�ܸ��� */
    MMA_CrpnQuery_GetPlmnNum(&stOrigOperName, &pstRcvMsg->stCrpnQryPara, &ucMaxMncLen, &ulTotalNum);

    /* ����Ƿ������磬����MNC�Ƿ�Ϸ� */
    if ((VOS_FALSE == TAF_MMA_IsMncLenVaild(ucMaxMncLen)
      || (0 == ulTotalNum)))
    {
        TAF_MMA_SndCrpnQryCnf(&pstRcvMsg->stCtrl, VOS_NULL_PTR, TAF_ERR_PB_WRONG_INDEX);

        return VOS_TRUE;
    }

    /* ����PLMN INFO�Ĵ洢�ռ� */
    pstOperName = (TAF_PH_OPERATOR_NAME_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                                            sizeof(TAF_PH_OPERATOR_NAME_STRU) * ulTotalNum);

    if (VOS_NULL_PTR == pstOperName)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "MMA_CrpnQuery: Alloc mem fail!");
        return VOS_TRUE;
    }

    /* ��ȡPLMN INFO */
    if (0 == pstRcvMsg->stCrpnQryPara.ucPlmnType)
    {
        MMA_PhoneGetAllOperInfoByLongNameFromOperTbl(&stOrigOperName, pstOperName);

    }
    else if(1 == pstRcvMsg->stCrpnQryPara.ucPlmnType)
    {
        MMA_PhoneGetAllOperInfoByShortNameFromOperTbl(&stOrigOperName, pstOperName);

    }
    else
    {
        /* Mcc */
        if(VOS_ERR == MMA_String2Hex(pstRcvMsg->stCrpnQryPara.aucPlmnName,
                                     3,
                                     &pstOperName->PlmnId.Mcc))
        {
            /* �ͷŶ�̬�ڴ� */
            PS_MEM_FREE(WUEPS_PID_MMA, pstOperName);

            TAF_MMA_SndCrpnQryCnf(&pstRcvMsg->stCtrl, VOS_NULL_PTR, TAF_ERR_PARA_ERROR);

            return VOS_TRUE;
        }
        /* Mnc */
        if(VOS_ERR == MMA_String2Hex(&pstRcvMsg->stCrpnQryPara.aucPlmnName[3],
                                      pstRcvMsg->stCrpnQryPara.usPlmnNameLen - 3,
                                     &pstOperName->PlmnId.Mnc))
        {
            /* �ͷŶ�̬�ڴ� */
            PS_MEM_FREE(WUEPS_PID_MMA, pstOperName);

            TAF_MMA_SndCrpnQryCnf(&pstRcvMsg->stCtrl, VOS_NULL_PTR, TAF_ERR_PARA_ERROR);
            return VOS_TRUE;
        }

        pstOperName->PlmnId.Mcc |= 0xFFFFF000;
        pstOperName->PlmnId.Mnc |= (0xFFFFFFFF << ((pstRcvMsg->stCrpnQryPara.usPlmnNameLen-3)*4));

        if (MMA_SUCCESS != MMA_PhoneFindNtwkNameByPlmnId(pstOperName))
        {
            /* �ͷŶ�̬�ڴ� */
            PS_MEM_FREE(WUEPS_PID_MMA, pstOperName);

            TAF_MMA_SndCrpnQryCnf(&pstRcvMsg->stCtrl, VOS_NULL_PTR, TAF_ERR_PB_WRONG_INDEX);

            return VOS_TRUE;
        }
    }


    /* ������Ϣ�ڴ� */
    pstMnMmaCrpnQryCnf = (TAF_MMA_CRPN_QRY_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                                            sizeof(TAF_MMA_CRPN_QRY_INFO_STRU));
    if (VOS_NULL_PTR == pstMnMmaCrpnQryCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "MMA_CrpnQuery: Alloc mem fail!");

        /* �ͷŶ�̬�ڴ� */
        PS_MEM_FREE(WUEPS_PID_MMA, pstOperName);
        return VOS_TRUE;
    }
    PS_MEM_SET(pstMnMmaCrpnQryCnf, 0, sizeof(TAF_MMA_CRPN_QRY_INFO_STRU));

    /* ������Ϣ��ֵ */
    pstMnMmaCrpnQryCnf->ucMaxMncLen = ucMaxMncLen;

    ucSendNum = pstRcvMsg->stCrpnQryPara.ucQryNum;

    /* ���Ҫ���ȡ��index���ڵ���CRPN������Ŀ����Ϊ�����һ���ϱ����ϱ�һ�����б� */
    if (pstRcvMsg->stCrpnQryPara.ucCurrIndex >= (VOS_UINT8)ulTotalNum)
    {
        pstMnMmaCrpnQryCnf->ucTotalNum = 0;
        ucSendNum = 0;
    }
    else
    {
        ucLeftNum = (VOS_UINT8)ulTotalNum - pstRcvMsg->stCrpnQryPara.ucCurrIndex;

        if (ucSendNum >= ucLeftNum)
        {
            ucSendNum = ucLeftNum;
        }
        pstMnMmaCrpnQryCnf->ucTotalNum  = (VOS_UINT8)ucSendNum;
        pstMnMmaCrpnQryCnf->ucCurrIndex = pstRcvMsg->stCrpnQryPara.ucCurrIndex;
    }

    PS_MEM_CPY(&pstMnMmaCrpnQryCnf->stMnMmaCrpnQry, &pstRcvMsg->stCrpnQryPara, sizeof(TAF_MMA_CRPN_QRY_PARA_STRU));

    for (i = 0; i < ucSendNum; i++)
    {
        PS_MEM_CPY(&pstMnMmaCrpnQryCnf->stOperNameList[i], (pstOperName + i + pstRcvMsg->stCrpnQryPara.ucCurrIndex), sizeof(TAF_PH_OPERATOR_NAME_STRU));
    }

    TAF_MMA_SndCrpnQryCnf(&pstRcvMsg->stCtrl, pstMnMmaCrpnQryCnf, TAF_ERR_NO_ERROR);

    /* �ͷŶ�̬�ڴ� */
    PS_MEM_FREE(WUEPS_PID_MMA, pstOperName);
    PS_MEM_FREE(WUEPS_PID_MMA, pstMnMmaCrpnQryCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaSetCmmReq_PreProc
 ��������  : AT^CMM ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��24��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaSetCmmReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CMM_SET_REQ_STRU           *pstRcvMsg;
    TAF_MMA_CMM_SET_CNF_STRU           *pstMmaSetCnfMsg;

    pstRcvMsg       = (TAF_MMA_CMM_SET_REQ_STRU *)pstMsg;

    /* ������Ϣ�ڴ� */
    pstMmaSetCnfMsg = (TAF_MMA_CMM_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(TAF_MMA_CMM_SET_CNF_STRU));

    if (VOS_NULL_PTR == pstMmaSetCnfMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvMmaSetCmmReq_PreProc:ERROR: Memory Alloc Error for pMsg");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMmaSetCnfMsg + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CMM_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ */
    pstMmaSetCnfMsg->ulReceiverPid          = WUEPS_PID_AT;
    pstMmaSetCnfMsg->ulMsgName              = ID_TAF_MMA_CMM_SET_CNF;
    PS_MEM_CPY(&pstMmaSetCnfMsg->stCtrl, &pstRcvMsg->stCtrl, sizeof(TAF_MMA_CTRL_STRU));

    pstMmaSetCnfMsg->ulResult = Mm_AtTest(&pstRcvMsg->stCmmSetReq, &pstMmaSetCnfMsg->stAtCmdRslt);

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstMmaSetCnfMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaTestSyscfgReq_PreProc
 ��������  : syscfg test req ��ϢԤ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��26��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaTestSyscfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SYSCFG_TEST_REQ_STRU       *pstRcvMsg;
    TAF_MMA_SYSCFG_TEST_CNF_STRU       *pstSysCfgTestCnf;

    pstRcvMsg        = (TAF_MMA_SYSCFG_TEST_REQ_STRU *)pstMsg;
    pstSysCfgTestCnf = (TAF_MMA_SYSCFG_TEST_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                    sizeof(TAF_MMA_SYSCFG_TEST_CNF_STRU));
    if (VOS_NULL_PTR == pstSysCfgTestCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvMmaTestSyscfgReq_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstSysCfgTestCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_SYSCFG_TEST_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstSysCfgTestCnf->ulReceiverPid          = pstRcvMsg->stCtrl.ulModuleId;
    pstSysCfgTestCnf->ulMsgName              = ID_TAF_MMA_SYSCFG_TEST_CNF;
    PS_MEM_CPY(&pstSysCfgTestCnf->stCtrl, &pstRcvMsg->stCtrl, sizeof(TAF_MMA_CTRL_STRU));
    pstSysCfgTestCnf->enErrorCause           = TAF_ERR_NO_ERROR;

    Taf_GetSyscfgBandGroupStr(&pstSysCfgTestCnf->stBandInfo);

    PS_SEND_MSG(WUEPS_PID_MMA, pstSysCfgTestCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaCsnrQryReq_PreProc
 ��������  : CSNR qry ��Ϣ�����ظ�
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��28��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaCsnrQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CSNR_QRY_REQ_STRU          *pstRcvMsg;
    TAF_MMA_CSNR_QRY_CNF_STRU          *pstCsnrQryCnf;
    VOS_UINT32                          ulResult;
    TAF_MMA_CSNR_PARA_STRU              pstCsnrParaStr ;

    pstRcvMsg = (TAF_MMA_CSNR_QRY_REQ_STRU *)pstMsg;

    pstCsnrQryCnf = (TAF_MMA_CSNR_QRY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_CSNR_QRY_CNF_STRU));
    if (VOS_NULL_PTR == pstCsnrQryCnf)
    {
        MMA_ERRORLOG("TAF_MMA_RcvMmaCsnrQryReq_PreProc: ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCsnrQryCnf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CSNR_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstCsnrQryCnf->ulReceiverPid          = pstRcvMsg->stCtrl.ulModuleId;
    pstCsnrQryCnf->ulMsgName              = ID_TAF_MMA_CSNR_QRY_CNF;
    PS_MEM_CPY(&pstCsnrQryCnf->stCtrl, &pstRcvMsg->stCtrl, sizeof(TAF_MMA_CTRL_STRU));

    /* ���� Taf_QueryCSNR ��ȡ�ź�ֵ */
    ulResult = Taf_QueryCSNR(&pstCsnrParaStr.sCpichRscp, &pstCsnrParaStr.sCpichEcNo);

    /* �ϱ�AT^CSNR������ѯ����¼� */
    if (VOS_OK != ulResult)
    {
        pstCsnrQryCnf->enErrorCause = TAF_ERR_ERROR;
    }
    else
    {
        pstCsnrQryCnf->enErrorCause = TAF_ERR_NO_ERROR;
        PS_MEM_CPY(&pstCsnrQryCnf->stCsnrPara, &pstCsnrParaStr, sizeof(TAF_MMA_CSNR_PARA_STRU));
    }

    PS_SEND_MSG(WUEPS_PID_MMA, pstCsnrQryCnf);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaCsqQryReq_PreProc
 ��������  : CSQ QRY��ϢԤ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��28��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaCsqQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CSQ_QRY_REQ_STRU            *pstRcvMsg;
    VOS_UINT32                           ulI;
    TAF_PH_RSSI_STRU                     stMmaRssiTmp;
    TAF_SDC_CTX_STRU                    *pstSdcCtx = VOS_NULL_PTR;

    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    PS_MEM_SET(&stMmaRssiTmp, 0, sizeof(stMmaRssiTmp));

    pstRcvMsg = (TAF_MMA_CSQ_QRY_REQ_STRU *)pstMsg;
    pstSdcCtx = TAF_SDC_GetSdcCtx();
    enSysMode = TAF_SDC_GetAppSysMode();

    ulI = 0;

    /* NO RFʱ�����ϱ��ź���������ѯʱ��ucRssiNum��Ϊ0 */
    if (VOS_TRUE == TAF_SDC_Get3GppRfAvailFlag())
    {
        stMmaRssiTmp.ucRssiNum = 1;
    }
    /* RSSI ��Ϣ��MMA ����SDC ���� */
    switch(enSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:

            MMA_GetRssiLevelFromValue(pstSdcCtx->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st2GCellSignInfo.sRssiValue,
                                      &(stMmaRssiTmp.aRssi[ulI].ucRssiValue));
            break;

        case TAF_SDC_SYS_MODE_WCDMA:

            MMA_GetRssiLevelFromValue(pstSdcCtx->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sRscpValue,
                                      &(stMmaRssiTmp.aRssi[ulI].ucRssiValue));
            break;

#if ( FEATURE_ON == FEATURE_LTE )
        case TAF_SDC_SYS_MODE_LTE:

            /* 4G���㷨��GU��ͬ, ������װ����, ��atSetCsqCnfSameProc������ͬ */
            TAF_MMA_GetRssiLevelFromLteRssi(pstSdcCtx->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRssi,
                                      &(stMmaRssiTmp.aRssi[ulI].ucRssiValue));
            break;
#endif

        default:
            stMmaRssiTmp.ucRssiNum = 0;

            MMA_WARNINGLOG1("MMA_PhModeReport():WARNING:TAF_SDC_GetAppSysMode():", enSysMode);
            break;

    }

    stMmaRssiTmp.aRssi[ulI].ucChannalQual = pstSdcCtx->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.ucChannalQual;

    TAF_MMA_SndCsqQryCnf(&pstRcvMsg->stCtrl, &stMmaRssiTmp);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaCsqLvlQryReq_PreProc
 ��������  : csqlvl qry req��Ϣ����
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��28��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
  3.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaCsqLvlQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CSQLVL_QRY_REQ_STRU        *pstRcvMsg;
    TAF_MMA_CSQLVL_PARA_STRU            stCsqLvlPara;
    TAF_MMA_CSQLVLEXT_PARA_STRU         stCsqLvlExtPara;
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
    VOS_UINT16                          ausCsqLvl[AT_CSQLVL_MAX_NUM]={105,102,97};
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode = TAF_ERR_ERROR;

    pstRcvMsg = (TAF_MMA_CSQLVL_QRY_REQ_STRU *)pstMsg;
    PS_MEM_SET(&stCsqLvlPara, 0, sizeof(TAF_MMA_CSQLVL_PARA_STRU));
    PS_MEM_SET(&stCsqLvlExtPara, 0, sizeof(TAF_MMA_CSQLVLEXT_PARA_STRU));

    sCpichRscp = RRC_NAS_MEASURE_INVALID_VALUE;
    sCpichEcNo = MMA_RSCP_MIN;

    /* ��ȡ Rscp ֵ */
    if (TAF_SUCCESS != Taf_QueryCSNR(&sCpichRscp, &sCpichEcNo))
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_WARNING, "TAF_MMA_RcvMmaCsqLvlQryReq_PreProc: Taf_QueryCSNR fail.");
        TAF_MMA_SndCsqLvlQryCnf(&pstRcvMsg->stCtrl, &stCsqLvlPara, &stCsqLvlExtPara, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* ȡ����ֵ */
    stCsqLvlPara.usRscp = (VOS_UINT16)(-sCpichRscp);

    /* ������ת��Ϊ��Ӧ�ĸ��� */
    if ( stCsqLvlPara.usRscp <= ausCsqLvl[2] )
    {
        stCsqLvlPara.usLevel = AT_CSQLVL_LEVEL_3;
    }
    else if ( stCsqLvlPara.usRscp <= ausCsqLvl[1] )
    {
        stCsqLvlPara.usLevel = AT_CSQLVL_LEVEL_2;
    }
    else if ( stCsqLvlPara.usRscp <= ausCsqLvl[0] )
    {
        stCsqLvlPara.usLevel = AT_CSQLVL_LEVEL_1;
    }
    else
    {
        stCsqLvlPara.usLevel = AT_CSQLVL_LEVEL_0;
    }

    /* �����ź�ǿ�Ȼ�ȡ��CSQLVLEXT������źŸ�����CSQLVLEXT������INDEXΪ0��RSSIֵ */
    if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE != TAF_SDC_GetAppServiceStatus())
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-2, end */
    {
     stCsqLvlExtPara.enRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_0;
    }
    else
    {
     /*��ȡ��ǰRSSI��ֵ,����API*/
     /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-2, begin */
        if (TAF_SDC_SYS_MODE_GSM == TAF_SDC_GetAppSysMode())
        {
            MN_PH_GetRssilvForCsqlvlExt(TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st2GCellSignInfo.sRssiValue,
                                     TAF_SDC_GetAppSysMode(),
                                     &stCsqLvlExtPara.enRssilv);
        }
        else
        {
            MN_PH_GetRssilvForCsqlvlExt(TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st3GCellSignInfo.sRscpValue,
                                     TAF_SDC_GetAppSysMode(),
                                     &stCsqLvlExtPara.enRssilv);
        }
     /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-2, end */
    }
    /* ��ǰ�汾��֧��CSQLVLEXT����ı��������ʰٷֱȲ�ѯ���̶�����99 */
    stCsqLvlExtPara.enBer = MN_PH_CSQLVLEXT_BER_VALUE_99;

    enErrorCode = TAF_ERR_NO_ERROR;

    TAF_MMA_SndCsqLvlQryCnf(&pstRcvMsg->stCtrl, &stCsqLvlPara, &stCsqLvlExtPara, enErrorCode);
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAccessModeQry_PreProc
 ��������  : MMA Pre Process Access Mode Qry Req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��27��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAccessModeQry_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ACCESS_MODE_QRY_REQ_STRU    *pstRcvMsg;
    TAF_MMA_RAT_ORDER_STRU               stRatOrder;
    NAS_MMA_NVIM_ACCESS_MODE_STRU        stAccessMode;
    VOS_UINT32                           ulLength;
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8      enAccessMode;
    TAF_PH_PLMN_PRIO                     ucPlmnPrio;

    pstRcvMsg = (TAF_MMA_ACCESS_MODE_QRY_REQ_STRU *)pstMsg;

    ulLength        = 0;
    PS_MEM_SET(&stRatOrder,   0x00, sizeof(stRatOrder));
    PS_MEM_SET(&stAccessMode, 0x00, sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU));

    TAF_MMA_ReadNvimRatPrioList(&stRatOrder);


    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_AccessMode, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_MMA_AccessMode ,
                        &stAccessMode,
                         ulLength))

    {
        stAccessMode.aucAccessMode[1] = TAF_PLMN_PRIO_AUTO;
    }



    /* CPAM��ѯ�����ȼ���syscfg��ѯ�����ȼ���һ����Ҫ����ת�� */
    if ( TAF_PLMN_GSM_PRIO == stAccessMode.aucAccessMode[1] )
    {
        ucPlmnPrio = MN_MMA_CPAM_RAT_PRIO_GSM;
    }
    else
    {
        ucPlmnPrio = MN_MMA_CPAM_RAT_PRIO_WCDMA;
    }

    /* ��ȡGUģ�������ȼ���Ϣ */
    /* MN_MMA_GetCpamGURatPrio((&pAccessMode->PlmnPrio), &stRatOrder); */

    /* ��ȡGUģ���뼼����Ϣ */
    MN_MMA_GetCpamGUAccessRat(&enAccessMode, &stRatOrder);

    /* Snd access Mode qry cnf */
    TAF_MMA_SndAccessModeQryCnf(&pstRcvMsg->stCtrl, enAccessMode, ucPlmnPrio);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvCopsQry_PreProc
 ��������  : Mma Pre Process Cops Qry Req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��27��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��04��11��
    ��    ��   : w00281933
    �޸�����   : ����״̬�Ż�Phase II
  3.��    ��   : 2016��1��22��
    ��    ��   : h00313353
    �޸�����   : DTS2016012202418
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvCopsQry_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulIndex;
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU               *pstEnhancedOperNameInfo = VOS_NULL_PTR;
    TAF_SDC_PLMN_ID_STRU                                   *pstAppServicePlmnId = VOS_NULL_PTR;
    TAF_PH_NETWORKNAME_STRU                                 stOperatorName;
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                          stMmInfoPlmnName;
    TAF_MMA_COPS_QRY_REQ_STRU                              *pstRcvMsg;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enPsServiceStatus;
    pstRcvMsg = (TAF_MMA_COPS_QRY_REQ_STRU *)pstMsg;

    enCsServiceStatus = TAF_SDC_GetAppCsServiceStatus();
    enPsServiceStatus = TAF_SDC_GetAppPsServiceStatus();

    pstAppServicePlmnId     = TAF_SDC_GetAppServicePlmnId();
    pstEnhancedOperNameInfo = TAF_SDC_GetEnhancedOperatorNameInfo();

    PS_MEM_SET(&stOperatorName, 0, sizeof(stOperatorName));
    PS_MEM_SET(&stMmInfoPlmnName, 0, sizeof(stMmInfoPlmnName));
    stOperatorName.NameFormat                   = TAF_SDC_GetCopsFormatType();
    stOperatorName.RaMode                       = TAF_SDC_GetAppSysMode();
    stOperatorName.PlmnSelMode                  = TAF_MMA_GetPlmnSelectionMode();
    stOperatorName.Name.aucOperatorNameLong[0]  = '\0';
    stOperatorName.Name.aucOperatorNameShort[0] = '\0';
    stOperatorName.Name.PlmnId.Mcc              = 0;
    stOperatorName.Name.PlmnId.Mnc              = 0;

    /* mmc�Բ�ͬ״̬��plmn Id�жϲ�׼ȷ��ʹ����SYS_INFO�ϱ���PLMN ID, ���ϵ�ǰ����״̬���ж� */
    if ( (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
      || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enPsServiceStatus) )
    {
        stOperatorName.Name.PlmnId.Mcc = pstAppServicePlmnId->ulMcc;
        stOperatorName.Name.PlmnId.Mnc = pstAppServicePlmnId->ulMnc;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        if ((TAF_SDC_SYS_SUBMODE_LTE != TAF_SDC_GetAppSysSubMode())
         || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enPsServiceStatus))
        {
            stOperatorName.Name.PlmnId.Mcc  = 0;
            stOperatorName.Name.PlmnId.Mnc  = 0;
        }
        else
        {
            stOperatorName.RaMode = TAF_PH_RA_LTE;
        }
    }
#endif

    if (TAF_SDC_COPS_FORMAT_TYPE_NUMERIC == TAF_SDC_GetCopsFormatType())
    {
        MMA_PlmnId2Bcd(&(stOperatorName.Name.PlmnId));
        TAF_MMA_SndCopsQryCnf(&pstRcvMsg->stCtrl, &stOperatorName);
        return VOS_TRUE;
    }

    for (ulIndex = 0; ulIndex < pstEnhancedOperNameInfo->stOperNameTypePrio.ucOperNamePrioNum; ulIndex++)
    {
        /* ��PNN�л�ȡ��Ӫ������*/
        if (TAF_SDC_OPER_NAME_TYPE_PNN == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ulIndex])
        {
            /* ��PNN�л�ȡ��Ӫ�����Ƴɹ�����ֱ�ӷ���*/
            if (VOS_TRUE == TAF_MMA_GetPnnNetWorkName((TAF_SDC_PLMN_ID_STRU *)&stOperatorName.Name.PlmnId, &stMmInfoPlmnName, TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT))
            {
                PS_MEM_CPY(stOperatorName.Name.aucOperatorNameLong, stMmInfoPlmnName.aucLongName, sizeof(stOperatorName.Name.aucOperatorNameLong));
                PS_MEM_CPY(stOperatorName.Name.aucOperatorNameShort, stMmInfoPlmnName.aucShortName, sizeof(stOperatorName.Name.aucOperatorNameShort));
                MMA_PlmnId2Bcd(&(stOperatorName.Name.PlmnId));
                TAF_MMA_SndCopsQryCnf(&pstRcvMsg->stCtrl, &stOperatorName);

                /* ��COPS RESULT ��ϢLOG���� */
                TAF_MMA_LogCopsRltInfo(&stOperatorName, TAF_SDC_LOG_OPER_NAME_TYPE_PNN);

                return VOS_TRUE;
            }

            /* �����PNN�л�ȡ7bit�������Ӫ������ʧ�ܣ���ȡUCS2�������Ӫ����������ɹ���cops��Ҫ���ؿգ�Ӧ��ͨ��^eonsucs2��ѯ��ȡucs2�������Ӫ������ */
            if (VOS_TRUE == TAF_MMA_GetPnnNetWorkName((TAF_SDC_PLMN_ID_STRU *)&stOperatorName.Name.PlmnId, &stMmInfoPlmnName, TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2))
            {
                MMA_PlmnId2Bcd(&(stOperatorName.Name.PlmnId));
                TAF_MMA_SndCopsQryCnf(&pstRcvMsg->stCtrl, &stOperatorName);

                /* ��COPS RESULT ��ϢLOG���� */
                TAF_MMA_LogCopsRltInfo(&stOperatorName, TAF_SDC_LOG_OPER_NAME_TYPE_PNN);

                return VOS_TRUE;
            }
        }

        /* ��CPHS�л�ȡ��Ӫ������*/
        if (TAF_SDC_OPER_NAME_TYPE_CPHS == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ulIndex])
        {
            /* ��CPHS�л�ȡ��Ӫ�����Ƴɹ�����ֱ�ӷ���*/
            if (VOS_TRUE == TAF_MMA_GetCphsNetWorkName(&stMmInfoPlmnName, TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT))
            {
                PS_MEM_CPY(stOperatorName.Name.aucOperatorNameLong, stMmInfoPlmnName.aucLongName, sizeof(stOperatorName.Name.aucOperatorNameLong));
                PS_MEM_CPY(stOperatorName.Name.aucOperatorNameShort, stMmInfoPlmnName.aucShortName, sizeof(stOperatorName.Name.aucOperatorNameShort));
                MMA_PlmnId2Bcd(&(stOperatorName.Name.PlmnId));
                TAF_MMA_SndCopsQryCnf(&pstRcvMsg->stCtrl, &stOperatorName);

                /* ��COPS RESULT ��ϢLOG���� */
                TAF_MMA_LogCopsRltInfo(&stOperatorName, TAF_SDC_LOG_OPER_NAME_TYPE_CPHS);

                return VOS_TRUE;
            }
        }

        /* ��MM INFO�л�ȡ��Ӫ������*/
        if (TAF_SDC_OPER_NAME_TYPE_MMINFO == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ulIndex])
        {
            /* ��MM INFO�л�ȡ��Ӫ�����Ƴɹ�����ֱ�ӷ���*/
            if (VOS_TRUE == TAF_MMA_GetMmInfoNetWorkName((TAF_SDC_PLMN_ID_STRU *)&stOperatorName.Name.PlmnId, &stMmInfoPlmnName, TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT))
            {
                PS_MEM_CPY(stOperatorName.Name.aucOperatorNameLong, stMmInfoPlmnName.aucLongName, sizeof(stOperatorName.Name.aucOperatorNameLong));
                PS_MEM_CPY(stOperatorName.Name.aucOperatorNameShort, stMmInfoPlmnName.aucShortName, sizeof(stOperatorName.Name.aucOperatorNameShort));
                MMA_PlmnId2Bcd(&(stOperatorName.Name.PlmnId));
                TAF_MMA_SndCopsQryCnf(&pstRcvMsg->stCtrl, &stOperatorName);

                /* ��COPS RESULT ��ϢLOG���� */
                TAF_MMA_LogCopsRltInfo(&stOperatorName, TAF_SDC_LOG_OPER_NAME_TYPE_MMINFO);

                return VOS_TRUE;
            }

            /* �����MM INFO�л�ȡ7bit�������Ӫ������ʧ�ܣ���ȡUCS2�������Ӫ����������ɹ���cops��Ҫ���ؿգ�Ӧ��ͨ��^eonsucs2��ѯ��ȡucs2�������Ӫ������ */
            if (VOS_TRUE == TAF_MMA_GetMmInfoNetWorkName((TAF_SDC_PLMN_ID_STRU *)&stOperatorName.Name.PlmnId, &stMmInfoPlmnName, TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2))
            {
                MMA_PlmnId2Bcd(&(stOperatorName.Name.PlmnId));
                TAF_MMA_SndCopsQryCnf(&pstRcvMsg->stCtrl, &stOperatorName);

                /* ��COPS RESULT ��ϢLOG���� */
                TAF_MMA_LogCopsRltInfo(&stOperatorName, TAF_SDC_LOG_OPER_NAME_TYPE_MMINFO);

                return VOS_TRUE;
            }
        }

        /* ��SPN�л�ȡ��Ӫ������*/
        if (TAF_SDC_OPER_NAME_TYPE_SPN == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ulIndex])
        {
            /* ��SPN�л�ȡ��Ӫ�����Ƴɹ�����ֱ�ӷ���*/
            if (VOS_TRUE == TAF_MMA_GetSpnNetWorkName((TAF_SDC_PLMN_ID_STRU *)&stOperatorName.Name.PlmnId, &stMmInfoPlmnName, TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT))
            {
                PS_MEM_CPY(stOperatorName.Name.aucOperatorNameLong, stMmInfoPlmnName.aucLongName, sizeof(stOperatorName.Name.aucOperatorNameLong));
                PS_MEM_CPY(stOperatorName.Name.aucOperatorNameShort, stMmInfoPlmnName.aucShortName, sizeof(stOperatorName.Name.aucOperatorNameShort));
                MMA_PlmnId2Bcd(&(stOperatorName.Name.PlmnId));
                TAF_MMA_SndCopsQryCnf(&pstRcvMsg->stCtrl, &stOperatorName);

                /* ��COPS RESULT ��ϢLOG���� */
                TAF_MMA_LogCopsRltInfo(&stOperatorName, TAF_SDC_LOG_OPER_NAME_TYPE_SPN);

                return VOS_TRUE;
            }

            /* �����SPN�л�ȡ7bit�������Ӫ������ʧ�ܣ���ȡUCS2�������Ӫ����������ɹ���cops��Ҫ���ؿգ�Ӧ��ͨ��^eonsucs2��ѯ��ȡucs2�������Ӫ������ */
            if (VOS_TRUE == TAF_MMA_GetSpnNetWorkName((TAF_SDC_PLMN_ID_STRU *)&stOperatorName.Name.PlmnId, &stMmInfoPlmnName, TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2))
            {
                MMA_PlmnId2Bcd(&(stOperatorName.Name.PlmnId));
                TAF_MMA_SndCopsQryCnf(&pstRcvMsg->stCtrl, &stOperatorName);

                /* ��COPS RESULT ��ϢLOG���� */
                TAF_MMA_LogCopsRltInfo(&stOperatorName, TAF_SDC_LOG_OPER_NAME_TYPE_SPN);

                return VOS_TRUE;
            }
        }
    }

    if (VOS_TRUE == TAF_MMA_GetNvimNetWorkName(&stOperatorName))
    {
        /* ��nv�л�ȡ��Ӫ�����Ƴɹ�����ֱ�ӷ��� */
        MMA_PlmnId2Bcd(&(stOperatorName.Name.PlmnId));
        TAF_MMA_SndCopsQryCnf(&pstRcvMsg->stCtrl, &stOperatorName);

        /* ��COPS RESULT ��ϢLOG���� */
        TAF_MMA_LogCopsRltInfo(&stOperatorName, TAF_SDC_LOG_OPER_NAME_TYPE_NV);

        return VOS_TRUE;
    }

    /* ��gastNetworkNameTbl�л�ȡ��Ӫ�����ƣ���ֱ�ӷ��� */
    MMA_PlmnId2Bcd(&(stOperatorName.Name.PlmnId));
    if (VOS_TRUE == TAF_MMA_GetStoredInternalNetWorkName(&stOperatorName))
    {
        TAF_MMA_SndCopsQryCnf(&pstRcvMsg->stCtrl, &stOperatorName);

        /* ��COPS RESULT ��ϢLOG���� */
        TAF_MMA_LogCopsRltInfo(&stOperatorName, TAF_SDC_LOG_OPER_NAME_TYPE_TABLE);

        return VOS_TRUE;
    }
    TAF_MMA_SndCopsQryCnf(&pstRcvMsg->stCtrl, &stOperatorName);

    /* ��COPS RESULT ��ϢLOG���� */
    TAF_MMA_LogCopsRltInfo(&stOperatorName, TAF_SDC_OPER_NAME_TYPE_BUTT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvRegStateQryReq_PreProc
 ��������  : Mma PreProc reg state Qry Req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��27��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvRegStateQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_REG_STATE_QRY_REQ_STRU     *pstRcvMsg;
    TAF_PH_REG_STATE_STRU               stRegStatusTmp;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_PLMN_ID_STRU                   *pstPlmnId = VOS_NULL_PTR;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enCsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enPsRegStatus;
#endif

    pstRcvMsg = (TAF_MMA_REG_STATE_QRY_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stRegStatusTmp, 0, sizeof(stRegStatusTmp));

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        enCsRegStatus   = TAF_SDC_GetAppCsRegStatus();
        enPsRegStatus   = TAF_SDC_GetAppPsRegStatus();

        /* AppNetWorkinof�е�enCsRegStatus��enPsRegStatus����ʼ��Ϊ��TAF_SDC_REG_STATUS_BUTT
           ע��״̬�ϱ�ʱ��ֻ���ϱ�0--5 ֵ���������BUTT, ת��ΪBUTT
        */
        if (TAF_SDC_REG_STATUS_BUTT == enCsRegStatus)
        {
            stRegStatusTmp.RegState = TAF_PH_REG_NOT_REGISTERED_NOT_SEARCH;
        }
        else
        {
            stRegStatusTmp.RegState = (TAF_PH_REG_STATE_TYPE)enCsRegStatus;
        }

        if (TAF_SDC_REG_STATUS_BUTT == enPsRegStatus)
        {
            stRegStatusTmp.ucPsRegState = TAF_PH_REG_NOT_REGISTERED_NOT_SEARCH;
        }
        else
        {
            stRegStatusTmp.ucPsRegState = (TAF_PH_REG_STATE_TYPE)enPsRegStatus;
        }

        TAF_MMA_FillActForAtCmdCregInClMode(pstRcvMsg->enQryRegStaType, &stRegStatusTmp.ucAct);

        /* LTEʱ��дС����Ϣ */
        if (TAF_PH_ACCESS_TECH_E_UTRAN == stRegStatusTmp.ucAct)
        {
            /*��ȡ��ǰPLMN*/
            pstPlmnId           = (TAF_PLMN_ID_STRU *)TAF_SDC_GetAppServicePlmnId();
            stRegStatusTmp.Plmn = *pstPlmnId;

            /*��ȡ��ǰCI*/
            stRegStatusTmp.CellId.aulCellId[0] = TAF_SDC_GetAppCampCellId();
            stRegStatusTmp.CellId.ucCellNum    = 1;

            /*��ȡ��ǰLAC*/
            stRegStatusTmp.usLac     = TAF_SDC_GetAppCampLac();

            /*��ȡ��ǰRAC*/
            stRegStatusTmp.ucRac     = TAF_SDC_GetAppCampRac();
        }
    }
    else
#endif
    {
        TAF_MMA_GetRegStateInfo(&stRegStatusTmp);
    }

    /* Mma snd reg state Qry cnf */
    TAF_MMA_SndRegStateQryCnf(&pstRcvMsg->stCtrl, &stRegStatusTmp);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvSysInfoQryReq_PreProc
 ��������  : Mma Pre Proc System Info Qry Req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��28��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
  3.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSysInfoQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SYSINFO_QRY_REQ_STRU       *pstRcvMsg;
    TAF_PH_SYSINFO_STRU                 sys_info;
    VOS_UINT32                          ulPinStatus;


    PS_MEM_SET( (VOS_UINT8 *)&sys_info,
                        0x00,
                        (VOS_SIZE_T)(sizeof(TAF_PH_SYSINFO_STRU)) );

    pstRcvMsg = (TAF_MMA_SYSINFO_QRY_REQ_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        if (VOS_TRUE == pstRcvMsg->ulSysInfoExFlag)
        {
            TAF_MMA_QueryClSysInfo(&sys_info);
        }

        TAF_MMA_SndSystemInfoQryCnf(pstRcvMsg, &sys_info);

        return VOS_TRUE;
    }
    else
#endif
    {
        /* ��ȡ��ǰ�������� */
        MN_PH_GetSysInfoRoamStatus(&sys_info);
        sys_info.ucSrvStatus = TAF_SDC_GetAppServiceStatus();
        sys_info.ucSrvDomain = TAF_SDC_GetAppServiceDomain();

        if (TAF_SDC_USIM_STATUS_NO_PRESENT == TAF_SDC_GetUsimStatus())
        {
            MMA_WARNINGLOG("TAF_MMA_RcvSysInfoQryReq_PreProc: Usim Status Absent!");
        }

        /* ��ȡ��ǰService Status��Ϣ */
        MN_PH_GetSysInfoSrvStatus(&sys_info, TAF_SDC_GetUsimStatus());

        /*�����ǰ��ҪPIN�롢��ҪPUK�����PUK��block��MMA��TAF�ϱ��ķ�����Ӧ��Ϊ0(�޷���)*/
        ulPinStatus = MMA_CheckPin1SatusSimple();

        /* ��ҪPIN��ʱ����״̬��ʾΪδ֪ */
        if (MMA_NONEED_PIN1 != ulPinStatus)
        {
            sys_info.ucSrvDomain = TAF_PH_INFO_NO_DOMAIN;
            sys_info.ucRoamStatus = TAF_PH_INFO_ROAM_UNKNOW;
        }

        /*��ȡ��ǰ������뼼��*/
        MMA_INFOLOG1("g_stTafSdcCtx.stAppNetworkInfo.stAppSysInfo.stServPlmnInfo.enServiceSysMode=", TAF_SDC_GetAppSysMode());
        MMA_INFOLOG1("gstMmaValue.pg_StatusContext->ucDataTranStatus=", gstMmaValue.pg_StatusContext->ucDataTranMode);

        if (VOS_TRUE == pstRcvMsg->ulSysInfoExFlag)
        {
            MN_PH_GetSysInfoSysModeEx(&sys_info);
        }
        else
        {
            MMA_GetSysInfoSysMode(&sys_info);
        }

        /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */

        if ( MMA_SIM_IS_LOCK == MMA_GetMeLockStatus() )
        {
            sys_info.ucSimLockStatus = VOS_TRUE;
        }
        else
        {
            sys_info.ucSimLockStatus = VOS_FALSE;
        }

        if (MMA_PUK1_REMAINS_ZERO == ulPinStatus)
        {
            sys_info.ucSimStatus = TAF_PH_USIM_STATUS_UNAVAIL;
        }
        else
        {
            /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
            sys_info.ucSimStatus = MMA_GetUsimStatus(VOS_FALSE);
            /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */
        }

        TAF_MMA_SndSystemInfoQryCnf(pstRcvMsg, &sys_info);

        return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAntennaInfoQryReq_PreProc
 ��������  : Mma Pre Proc Antenna Info Qry Req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAntennaInfoQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ANTENNA_INFO_QRY_REQ_STRU  *pstRcvMsg;
    MN_MMA_ANQUERY_PARA_STRU            stAnqueryPara;
    VOS_UINT32                          ulResult;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    pstRcvMsg = (TAF_MMA_ANTENNA_INFO_QRY_REQ_STRU *)pstMsg;

    enSysMode = TAF_SDC_GetAppSysMode();

    PS_MEM_SET(&stAnqueryPara, 0x0, sizeof(MN_MMA_ANQUERY_PARA_STRU));

    if ((TAF_SDC_SYS_MODE_GSM == enSysMode)
     || (TAF_SDC_SYS_MODE_WCDMA == enSysMode))
    {
        /*���ú���MN_PH_QryAnQuery��ȡrscp, ecio,rssi,cellid */
        ulResult = MN_PH_QryAnQuery(&stAnqueryPara.u.st2G3GCellSignInfo.sCpichRscp,
                                    &stAnqueryPara.u.st2G3GCellSignInfo.sCpichEcNo,
                                    &stAnqueryPara.u.st2G3GCellSignInfo.ucRssi,
                                    &stAnqueryPara.u.st2G3GCellSignInfo.ulCellId);
         /*ָʾ��Ϊ2G 3G��С���ź� */
         stAnqueryPara.enServiceSysMode = enSysMode;

    /* �ظ�AT^ANQUERY��ѯ���� */
    if (VOS_OK != ulResult)
    {
        TAF_MMA_SndAntennaInfoQryCnf(&pstRcvMsg->stCtrl, TAF_ERR_ERROR, &stAnqueryPara);
    }
    else
    {
        TAF_MMA_SndAntennaInfoQryCnf(&pstRcvMsg->stCtrl, TAF_ERR_NO_ERROR, &stAnqueryPara);
    }
    }
#if ( FEATURE_ON == FEATURE_LTE )
    else if(TAF_SDC_SYS_MODE_LTE == enSysMode )
    /* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */
    {

        /*�� at_CsqInfoProc ��RssiLevel������ͬ */
        stAnqueryPara.u.st4GCellSignInfo.sRssi = TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRssi;
        stAnqueryPara.u.st4GCellSignInfo.sRsrp = TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsrp;
        stAnqueryPara.u.st4GCellSignInfo.sRsrq = TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stAppSigQuaInfo.st3GppRssiInfo.u.st4GCellSignInfo.sRsrq;

        /*ָʾ��Ϊ2G 3G��С���ź� */
        stAnqueryPara.enServiceSysMode = enSysMode;

        TAF_MMA_SndAntennaInfoQryCnf(&pstRcvMsg->stCtrl, TAF_ERR_NO_ERROR, &stAnqueryPara);
    }
#endif
    else
    {
        MMA_WARNINGLOG("TAF_MMA_RcvAntennaInfoQryReq_PreProc():RAT IS INVALID");
    }
/* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvApHplmnQryReq_PreProc
 ��������  : Mma PreProc ApHplmn Qry Req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvApHplmnQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_HOME_PLMN_QRY_REQ_STRU     *pstRcvMsg;
    TAF_ERROR_CODE_ENUM_UINT32          enErrCode;

    pstRcvMsg = (TAF_MMA_HOME_PLMN_QRY_REQ_STRU *)pstMsg;

    enErrCode = MMA_ProcHplmnQryReq(&(pstRcvMsg->stCtrl));

    if (TAF_ERR_NO_ERROR != enErrCode)
    {
        TAF_MMA_SndApHplmnCnf(enErrCode, &(pstRcvMsg->stCtrl), VOS_NULL_PTR);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvDplmnQryReq_PreProc
 ��������  : MMA�յ�TAF���͵�ID_TAF_MMA_DPLMN_QRY_REQ��Ϣ��Ԥ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDplmnQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_DPLMN_QRY_REQ_STRU         *pstRcvMsg = VOS_NULL_PTR;
    NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU   stNvimDplmnNplmnCfg;

    pstRcvMsg = (TAF_MMA_DPLMN_QRY_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stNvimDplmnNplmnCfg, 0x00, sizeof(NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU));

    TAF_MMA_ReadDplmnNplmnCfgNvim(&stNvimDplmnNplmnCfg);

    /* MMA��MSCC����ID_MMA_MSCC_DPLMN_QRY_REQ��Ϣ */
    TAF_MMA_SndDplmnQryCnf(&(pstRcvMsg->stCtrl), stNvimDplmnNplmnCfg.aucVersionId);

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvDplmnSetReq_PreProc
 ��������  : mma �յ�ID_TAF_MMA_DPLMN_SET_REQ��Ϣ�Ĵ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDplmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_DPLMN_SET_REQ_STRU         *pstRcvMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucEhPlmnNum;
    VOS_UINT16                          usDplmnNum;
    VOS_UINT32                          i;

   pstRcvMsg = (TAF_MMA_DPLMN_SET_REQ_STRU *)pstMsg;

   /* �ֲ�������ʼ�� */
   ucEhPlmnNum    = pstRcvMsg->stDplmnInfo.ucEhPlmnNum;
   usDplmnNum     = pstRcvMsg->stDplmnInfo.usDplmnNum;

   /* ת��plmn id��ʽ */
   for ( i = 0; i < ucEhPlmnNum; i++ )
   {
        MMA_PlmnId2NasStyle( &(pstRcvMsg->stDplmnInfo.astEhPlmnInfo[i]));
   }

   for ( i = 0; i < usDplmnNum; i++ )
   {
        MMA_PlmnId2NasStyle( &(pstRcvMsg->stDplmnInfo.astDplmnList[i].stPlmnId));
   }

   /* ����ID_MMA_MSCC_DPLMN_SET_REQ��Ϣ��MSCC */
   TAF_MMA_SndMsccDplmnSetReq(pstRcvMsg);

   return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_RcvBatteryCapacityQry_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_BATTERY_CAPACITY_QRY_REQ_STRU                  *pstRcvMsg = VOS_NULL_PTR;
    TAF_MMA_BATTERYPOWER_STRU                               stBatteryStatus;
    TAF_PMU_STATE_STRU                                      stpmuState;

    pstRcvMsg = (TAF_MMA_BATTERY_CAPACITY_QRY_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stBatteryStatus,0x00,sizeof(TAF_MMA_BATTERYPOWER_STRU));

    PS_MEM_SET(&stpmuState,0x00,sizeof(stpmuState));

    (VOS_VOID)DRV_GET_PMU_STATE(&stpmuState);
    /************************************************************/
    /*�ӵ�Դģ���л�ȡ��ǰ��Ҫ��Ϣ*/
    if(1 == stpmuState.bat_out)
    {
        stBatteryStatus.BatteryPowerStatus = TAF_PH_NOBATTERYFIXED;
    }
    else if(1 == stpmuState.chg_timer_overflow)
    {
        stBatteryStatus.BatteryPowerStatus = TAF_PH_POWERSOURCEERROR;
    }
    else if(1 == stpmuState.chargerstate)
    {
        stBatteryStatus.BatteryPowerStatus = TAF_PH_BATTERYNOSUPPLY;
    }
    else
    {
        stBatteryStatus.BatteryPowerStatus = TAF_PH_BATTERYCHARGING;
    }

    stBatteryStatus.BatteryRemains      = (VOS_UINT8)((stpmuState.bal_Volt * 100) / 900);
    /************************************************************/

    /* Mma snd CBC Qry cnf */
    TAF_MMA_SndBatteryCapacityQryCnf(&pstRcvMsg->stCtrl, &stBatteryStatus);

    return VOS_TRUE;

}


VOS_UINT32 TAF_MMA_RcvHandShakeQry_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_HAND_SHAKE_QRY_REQ_STRU    *pstRcvMsg = VOS_NULL_PTR;
    VOS_UINT8                           aucBuf[AT_HS_PARA_MAX_LENGTH];
    VOS_UINT8                          *pPara = VOS_NULL_PTR;
    VOS_UINT32                          ulId;
    /* Added by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-12, begin */
    VOS_UINT8                           ucPhoneMode;

    pstRcvMsg   = (TAF_MMA_HAND_SHAKE_QRY_REQ_STRU *)pstMsg;

    ucPhoneMode = TAF_SDC_GetCurPhoneMode();
    /* Added by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-12, end */

    ulId        = MMA_HS_ID;
    PS_MEM_CPY(aucBuf, &ulId, sizeof(VOS_UINT32));                              /*id*/

    aucBuf[4]   = MMA_HS_PROTOCOL_APP;                                            /*protocol*/

    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-12, begin */
    if ((TAF_PH_MODE_FULL == ucPhoneMode)                    /*UE CUR CFUN MODE*/
     || (TAF_PH_MODE_FT == ucPhoneMode))
    {
        aucBuf[5] = MMA_HS_ONLINE;
    }
    /* BEGIN: Modified by w00199382, 2012/4/4   ���ⵥ��:DTS2012031906134*/
    else if (TAF_PH_MODE_RFOFF == ucPhoneMode)
    {
        aucBuf[5] = MMA_HS_OFFLINE;
    }
    /* END: Modified by w00199382, 2012/4/4   ���ⵥ��:DTS2012031906134*/
    else
    {
        aucBuf[5] = MMA_HS_LPM;
    }
    /* Modified by w00176964 for VoLTE_PhaseI��Ŀ, 2013-7-12, end */

    aucBuf[6] = MMA_HS_PRODUCT_CLASS_GW;                                        /*product_class*/
    aucBuf[7] = MMA_HS_PRODUCT_ID;                                              /*product id*/
    aucBuf[8] = 0x0;                                                            /*software_id*/
    pPara = (VOS_UINT8 *)aucBuf;

    /* Mma snd HS Qry cnf */
    TAF_MMA_SndHandShakeQryCnf(&pstRcvMsg->stCtrl, pPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccPlmnAutoSelCnfExpired_PreProc
 ��������  : �ȴ�MSCCģ���PLMN AUTO RESEL CNF��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��2��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccPlmnAutoSelCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����ID_TAF_MMA_PLMN_AUTO_RESEL_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ, &ucCtxIndex))
    {
        /*  �ظ�MMA_CFPLMN_CNF */
        TAF_MMA_SndPlmnAutoReselCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_TIME_OUT);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    g_StatusContext.ulFsmState = STA_FSM_ENABLE;
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccAbortSpecPlmnSelCnfExpired_PreProc
 ��������  : �ȴ�MSCCģ���PLMN special RESEL CNF��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��2��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccAbortSpecPlmnSelCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_SPEC_SEL_REQ, &ucCtxIndex))
    {
        TAF_MMA_SndPlmnSpecialSelCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_TIME_OUT);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    /* Ǩ��״̬��ENABLE״̬ */
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccSpecPlmnSelCnfExpired_PreProc
 ��������  : �ȴ�MSCCģ���PLMN special abort CNF��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��2��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��18��
    ��    ��   : z00359541
    �޸�����   : DTS2016011901728: AT���ʱ�����MMA״̬Ϊ�ֶ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccSpecPlmnSelCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucCtxIndex;
    VOS_UINT32                          ulRet;

    /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ��Ӧ�ļ�¼�� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_SPEC_SEL_REQ, &ucCtxIndex))
    {
        /* ��ʱ����ʱ������MMA״̬Ϊ�ֶ�ģʽ */
        NAS_NORMAL_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitMsccSpecPlmnSelCnfExpired_PreProc: Set MMA to Manual Mode");
        TAF_MMA_SetPlmnSelectionMode(TAF_PH_PLMN_SEL_MODE_MANUAL);

        /* MMA��ָ������������ʱ����ʱ��������MSCC����ָֹͣ����������
           �յ�MSCC�Ļظ�������AT�ظ� */
        ulRet = TAF_MMA_SndMsccSpecPlmnSearchAbortReq();

        if (VOS_ERR == ulRet)
        {
            MMA_WARNINGLOG("TAF_MMA_RcvTiWaitMsccSpecPlmnSelCnfExpired_PreProc():ERROR: failed");
        }

        /* ����STA_TIMER_SPEC_PLMN_ABORT 10s��ʱ���������ʱδ�յ�MSCC�Ļظ����ϱ�ATʧ�� */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_ABORT_SPEC_PLMN_SEL_CNF, TI_TAF_MMA_WAIT_MSCC_ABORT_SPEC_PLMN_SEL_CNF_LEN);
    }

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccPlmnListAbortCnfExpired_PreProc
 ��������  : �ȴ�MSCCģ���PLMN list abort CNF��Ϣ��ʱ����
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��2��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccPlmnListAbortCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    if (TAF_MMA_PLMN_LIST_ABORT_BUTT == g_StatusContext.ucPlmnListAbortProc)
    {
        return VOS_TRUE;
    }

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* PLMN LIST ABORTԭ��ֵΪ��ʱ����ʱ */
    if ( TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT == g_StatusContext.ucPlmnListAbortProc )
    {
        /* ��AT�ظ��б��ѳ�ʱ��� */
        g_StatusContext.PhoneError    = TAF_ERR_TIME_OUT;
        g_StatusContext.ucOperateType = STA_OP_PHONEERROR;

        /* �ϱ�AT��ǰ״̬�¼� */
        Sta_EventReport (g_StatusContext.ulCurOpId, TAF_PH_EVT_PLMN_LIST_CNF);
    }
    else
    {
         /* ��AT�ظ��б��ѳ�ʱ��� */
        /* ��ȫ�ֱ���g_stTafMmaCtx.astMmaOperCtx����ID_TAF_MMA_PLMN_LIST_ABORT_REQ��Ӧ�ļ�¼�� */
        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_PLMN_LIST_ABORT_REQ, &ucCtxIndex))
        {
            /*  �ظ�ID_TAF_MMA_PLMN_LIST_ABORT_CNF */
            TAF_MMA_SndPlmnListAbortCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_NO_ERROR);

            TAF_MMA_ClearOperCtx(ucCtxIndex);
        }
    }

    /* Ǩ��״̬��ENABLE״̬ */
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;

    /* ���õ�ǰû�д����û��б��Ѵ�Ϲ��� */
    g_StatusContext.ucPlmnListAbortProc = TAF_MMA_PLMN_LIST_ABORT_BUTT;

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcAutoAttachSetReq_PreProc
 ��������  : ���ݷ���ģʽ����attach����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ProcAutoAttachSetReq_PreProc(VOS_VOID)
{
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8      enAttachType;
    VOS_UINT8                           ucAutoAttachFlg;
    NAS_NVIM_AUTOATTACH_STRU            stAutoattachFlag;
    VOS_UINT32                          ulLength;
    VOS_UINT8                           ucOpID;

    ulLength = 0;
    PS_MEM_SET(&stAutoattachFlag, 0x00, sizeof(NAS_NVIM_AUTOATTACH_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_Autoattach, &ulLength);
    if (NV_OK == NV_Read(en_NV_Item_Autoattach,
                         (VOS_VOID*)(&stAutoattachFlag),
                         ulLength))
    {
        if (1 == stAutoattachFlag.usAutoattachFlag)
        {
            ucAutoAttachFlg = MMA_AUTO_ATTACH_ENABLE;
        }
        else
        {
            ucAutoAttachFlg = MMA_AUTO_ATTACH_DISABLE;
        }
    }
    else
    {
        ucAutoAttachFlg = MMA_AUTO_ATTACH_ENABLE;
    }

    switch (g_StatusContext.ucModeService)
    {
        case TAF_PH_MS_CLASS_A:
            enAttachType = TAF_MMA_ATTACH_TYPE_GPRS_IMSI;
            if (MMA_AUTO_ATTACH_DISABLE == ucAutoAttachFlg)
            {
                enAttachType = TAF_MMA_ATTACH_TYPE_IMSI;
            }
            break;

        case TAF_PH_MS_CLASS_CG:
            enAttachType = TAF_MMA_ATTACH_TYPE_GPRS;
            if (MMA_AUTO_ATTACH_DISABLE == ucAutoAttachFlg)
            {
                return;
            }
            break;

        case TAF_PH_MS_CLASS_CC:
            enAttachType = TAF_MMA_ATTACH_TYPE_IMSI;
            break;

        case TAF_PH_MS_CLASS_NULL:
            g_StatusContext.ulFsmState = STA_FSM_ENABLE;
            return;

        default:
            return;
    }

    ucOpID = TAF_MMA_GetAttachOpId();

    (VOS_VOID)TAF_MMA_SndMsccAttachReq(ucOpID, (NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32)enAttachType, TAF_MMA_ATTACH_REASON_INITIAL);

    TAF_MMA_SetAttachAllowFlg(enAttachType);

    return;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafCsgListSearchReq_PreProc
 ��������  : CSG �б���������Ԥ����
 �������  : ulEventType - �¼�����
             pstMsg     - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��6��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafCsgListSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enWaitSrvAcqCnfTimerStatus;
#endif

    TAF_MMA_CSG_LIST_SEARCH_REQ_STRU   *pstRcvMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulCsSrvExistFlag;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;
    TAF_MMA_PLMN_LIST_CTRL_STRU         stPlmnListCtrl;

    pstRcvMsg        = (TAF_MMA_CSG_LIST_SEARCH_REQ_STRU *)pstMsg;
    ulCsSrvExistFlag = TAF_SDC_GetCsSrvExistFlg();
    enSimType        = TAF_SDC_GetSimType();


    /* ������Ƿֶ��ϱ��е��״β�ѯ����ֱ�ӵ��û����е������ϱ� */
    if (0 < pstRcvMsg->stPlmnListPara.usCurrIndex)
    {
        stPlmnListCtrl.usCurrIndex = pstRcvMsg->stPlmnListPara.usCurrIndex;
        stPlmnListCtrl.usReadNum   = pstRcvMsg->stPlmnListPara.usQryNum;
        TAF_MMA_ReportCsgListSearchResult(&pstRcvMsg->stCtrl, &stPlmnListCtrl);

        return VOS_TRUE;
    }

    /* ���syscfg���ò�֧��LTE��������sim�������ߴ���CSҵ�񣬷���ʧ�� */
    if ((VOS_TRUE != TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_LTE))
     || (VOS_TRUE == ulCsSrvExistFlag)
     || (TAF_SDC_SIM_TYPE_SIM == enSimType))
    {
        /* ֱ�ӻظ�csg plmn listʧ�� */
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_CMD_TYPE_ERROR);

        return VOS_TRUE;
    }

#if (FEATURE_IMS == FEATURE_ON)
    /* ����imsҵ��ֱ�ӻظ�ʧ�� */
    if (VOS_TRUE == TAF_SDC_IsImsSrvExist())
    {
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_CMD_TYPE_ERROR);

        return VOS_TRUE;
    }
#endif

    /* �����C+Lģʽ����ʱ��AT������csg list���� ����ظ�ʧ��,���б���  */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* �޿�����״̬���Դ���pin����puk�룬����ʧ�� */
    enErrorCode = MMA_CheckUsimStatusForPlmnSel();

    if(TAF_ERR_NO_ERROR != enErrorCode)
    {
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), enErrorCode);
        return VOS_TRUE;
    }

    if (VOS_TRUE != TAF_MMA_IsEnablePlmnList())
    {
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_PHONE_MSG_UNMATCH);
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_DSDS)
    enWaitSrvAcqCnfTimerStatus = TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF);

    /* �����ǰno rf״̬�Ҵ���ҵ�񴥷���������ֱ�ӻظ�ʧ�� */
    if (TAF_MMA_TIMER_STATUS_RUNING == enWaitSrvAcqCnfTimerStatus)
    {
        /* ֱ�ӻظ�csg plmn listʧ�� */
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_NO_RF);

        return VOS_TRUE;
    }

#endif

    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccCsgListSearchCnfExpired_PreProc
 ��������  : CSG list������ʱ����ʱ����
 �������  : ulEventType - �¼�����
             pstMsg     - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��8��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccCsgListSearchCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ǰ״̬����CSG LIST״̬��ֱ�ӷ��� */
    if ( STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState )
    {
        MMA_WARNINGLOG("TAF_MMA_RcvTiWaitMsccCsgListSearchCnfExpired_PreProc():WARNING: no csg list searching");
        return VOS_TRUE;
    }

    if (VOS_ERR == TAF_MMA_SndMsccCsgListAbortReq())
    {
        MMA_WARNINGLOG("TAF_MMA_RcvTiWaitMsccCsgListSearchCnfExpired_PreProc():ERROR: failed");
        return VOS_TRUE;
    }

    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF, TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF_LEN);

    /* ���õ�ǰ���ڴ���ʱ����ʱ��CSG�б��Ѵ�Ϲ��� */
    TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitMsccCsgListAbortCnfExpired_PreProc
 ��������  : CSG list abort��ʱ����ʱ����
 �������  : ulEventType - �¼�����
             pstMsg     - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��8��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitMsccCsgListAbortCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    if (TAF_MMA_PLMN_LIST_ABORT_BUTT == TAF_MMA_GetCsgListAbortType())
    {
        return VOS_TRUE;
    }

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /* CSG LIST ABORTԭ��ֵΪ��ʱ����ʱ */
    if ( TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT == TAF_MMA_GetCsgListAbortType())
    {
        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, &ucCtxIndex))
        {
            TAF_MMA_ReportCsgListError(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_ERROR);
        }
    }
    else
    {
         /* ��AT�ظ��б��ѳ�ʱ��� */
        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_ABORT_REQ, &ucCtxIndex))
        {
            /*  �ظ�LIST_ABORT_CNF */
            TAF_MMA_SndCsgListAbortCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_NO_ERROR);

            TAF_MMA_ClearOperCtx(ucCtxIndex);
        }
    }

    TAF_MMA_ClearCsgListSearchOperCtx();

    /* Ǩ��״̬��ENABLE״̬ */
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;

    /* ���õ�ǰû�д����û�CSG�б��Ѵ�Ϲ��� */
    TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_BUTT);

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaSetAutoAttachReq_PreProc
 ��������  : AT^CAATT
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��25��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaSetAutoAttachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_AUTO_ATTACH_SET_REQ_STRU   *pstRcvMsg;

    VOS_UINT32                          ulMsgAutoAttachFlg;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucAutoAttachFlg;
    NAS_NVIM_AUTOATTACH_STRU            stAutoattachFlag;
    VOS_UINT32                          ulLength;

    ulLength    = 0;
    ulResult    = 0;

    PS_MEM_SET(&stAutoattachFlag, 0x00, sizeof(NAS_NVIM_AUTOATTACH_STRU));
    pstRcvMsg = (TAF_MMA_AUTO_ATTACH_SET_REQ_STRU *)pstMsg;

    (VOS_VOID)NV_GetLength(en_NV_Item_Autoattach, &ulLength);
    if (NV_OK == NV_Read(en_NV_Item_Autoattach,
                          (VOS_VOID*)(&stAutoattachFlag),
                          ulLength))
    {
        MMA_INFOLOG1("TAF_MMA_RcvMmaSetAutoAttachReq_PreProc:Read result from NV", (VOS_INT32)stAutoattachFlag.usAutoattachFlag);
        if (1 == stAutoattachFlag.usAutoattachFlag)
        {
            ucAutoAttachFlg = MMA_AUTO_ATTACH_ENABLE;
        }
        else
        {
            ucAutoAttachFlg = MMA_AUTO_ATTACH_DISABLE;
        }
    }
    else
    {
        MMA_WARNINGLOG("TAF_MMA_RcvMmaSetAutoAttachReq_PreProc:WARNING: Read NV Failure!");
        ucAutoAttachFlg = MMA_AUTO_ATTACH_ENABLE;
    }

    if (VOS_FALSE == pstRcvMsg->ulAutoAttachEnable)
    {
        ulMsgAutoAttachFlg = MMA_AUTO_ATTACH_DISABLE;
    }
    else if (VOS_TRUE == pstRcvMsg->ulAutoAttachEnable)
    {
        ulMsgAutoAttachFlg = MMA_AUTO_ATTACH_ENABLE;
    }
    else
    {
        MMA_WARNINGLOG("TAF_MMA_RcvMmaSetAutoAttachReq_PreProc:WARNING: ulSetValue error");

        TAF_MMA_SndAutoAttachSetCnf(&pstRcvMsg->stCtrl, TAF_PARA_SET_ERROR);
        return VOS_TRUE;

    }

    if ( ucAutoAttachFlg == ulMsgAutoAttachFlg )
    {
        /* NV��ֵû�иı䣬�򷵻سɹ�������AT�ڻᱻռ�� */
        TAF_MMA_SndAutoAttachSetCnf(&pstRcvMsg->stCtrl, TAF_PARA_OK);
        return VOS_TRUE;
    }

    /* ֵ��һ������ҪдNV */

    stAutoattachFlag.usAutoattachFlag = (VOS_UINT16)ulMsgAutoAttachFlg;
    ulResult = MMA_WriteValue2Nvim(en_NV_Item_Autoattach, (VOS_VOID *)(&stAutoattachFlag), sizeof(VOS_UINT16));

    if (MMA_SUCCESS != ulResult)
    {
        MMA_WARNINGLOG("TAF_MMA_RcvMmaSetAutoAttachReq_PreProc:WARNING: Write NV Failure!");

        TAF_MMA_SndAutoAttachSetCnf(&pstRcvMsg->stCtrl, TAF_PARA_WRITE_NVIM_ERROR);
        return VOS_TRUE;

    }
    else
    {
        TAF_MMA_SndAutoAttachSetCnf(&pstRcvMsg->stCtrl, TAF_PARA_OK);

        if ((MMA_AUTO_ATTACH_DISABLE  == ucAutoAttachFlg)
            &&(MMA_AUTO_ATTACH_ENABLE == ulMsgAutoAttachFlg))
        {
            /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
            if ( (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != TAF_SDC_GetPsServiceStatus())
              && ( (STA_FSM_NULL     != g_StatusContext.ulFsmState)
                && (STA_FSM_STOP     != g_StatusContext.ulFsmState) )
              && (TAF_PH_MS_CLASS_CC != g_StatusContext.ucModeService)  )
            /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */
            {
                TAF_MMA_ProcAutoAttachSetReq_PreProc();
            }
        }
    }

    return VOS_TRUE;

}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaQryAutoAttachReq_PreProc
 ��������  : Mma Pre Process Qry Auto Attach Info Req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��28��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaQryAutoAttachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_AUTO_ATTACH_QRY_REQ_STRU   *pstRcvMsg;
    NAS_NVIM_AUTOATTACH_STRU            stAutoattachFlag;
    VOS_UINT32                          ulLength;
    VOS_UINT8                           ucAutoAttachFlg;

    pstRcvMsg = (TAF_MMA_AUTO_ATTACH_QRY_REQ_STRU *)pstMsg;

    ulLength        = 0;
    ucAutoAttachFlg = 0;
    PS_MEM_SET(&stAutoattachFlag, 0x00, sizeof(NAS_NVIM_AUTOATTACH_STRU));
    (VOS_VOID)NV_GetLength(en_NV_Item_Autoattach, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_Autoattach,
                        (VOS_VOID*)(&stAutoattachFlag),
                         ulLength))
    {
        MMA_WARNINGLOG("MMA_GetPhAutoAttachStatus:Read Auto Attach Status Failed!");

        /* Mma Snd Auto Attach Qry Cnf */
        TAF_MMA_SndAutoAttachQryCnf(&pstRcvMsg->stCtrl, TAF_ERR_ERROR, ucAutoAttachFlg);
    }
    else
    {
        MMA_INFOLOG1("MMA_GetPhAutoAttachStatus:Read result from NV",(VOS_INT32)(stAutoattachFlag.usAutoattachFlag));

        if (0 == stAutoattachFlag.usAutoattachFlag)
        {
            ucAutoAttachFlg = MMA_AUTO_ATTACH_DISABLE;
        }
        else
        {
            ucAutoAttachFlg = MMA_AUTO_ATTACH_ENABLE;
        }

        /* Mma Snd Auto Attach Qry Cnf */
        TAF_MMA_SndAutoAttachQryCnf(&pstRcvMsg->stCtrl, TAF_ERR_NO_ERROR, ucAutoAttachFlg);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvDetachReq_PreProc
 ��������  : �յ�DetachReq��Ϣ��Ԥ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����Ҫ����״̬��,VOS_FALSE:��Ҫ����״̬������ִ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��13��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDetachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_DETACH_REQ_STRU            *pstDetachReqMsg = VOS_NULL_PTR;

    pstDetachReqMsg = (TAF_MMA_DETACH_REQ_STRU *)pstMsg;

    /* ���DETACH�������ͺϷ��Լ�� */
    if ((pstDetachReqMsg->stDetachPara.enDetachDomain) > TAF_MMA_SERVICE_DOMAIN_CS_PS)
    {
        TAF_MMA_SndDetachCnf(&(pstDetachReqMsg->stCtrl), TAF_MMA_APP_OPER_RESULT_FAILURE, TAF_ERR_PARA_ERROR);

        return VOS_TRUE;
    }

    /* �����C+Lģʽ����ʱ��AT������detach����ظ�ʧ��,���б���  */
    if ((VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
     && (CMMCA_CLIENT_ID != (VOS_UINT32)(pstDetachReqMsg->stCtrl.usClientId)))
    {
        TAF_MMA_SndDetachCnf(&(pstDetachReqMsg->stCtrl), TAF_MMA_APP_OPER_RESULT_FAILURE, TAF_ERR_ERROR);

        return VOS_TRUE;
    }

    /* �����ǰ����C+Lģʽ������CMMCA����DETACH,��ֱ�ӻظ�ʧ�� */
    if ((VOS_FALSE == TAF_MMA_IsPowerOnCLInterWork())
     && (CMMCA_CLIENT_ID == (VOS_UINT32)(pstDetachReqMsg->stCtrl.usClientId)))
    {
        TAF_MMA_SndDetachCnf(&(pstDetachReqMsg->stCtrl), TAF_MMA_APP_OPER_RESULT_FAILURE, TAF_ERR_ERROR);

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* ��ǰ�����CLģʽ���ҽ���detach������CS����CS+PS����ֱ�ӷ���ERROR */
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        if ( (TAF_MMA_SERVICE_DOMAIN_CS == pstDetachReqMsg->stDetachPara.enDetachDomain)
          || (TAF_MMA_SERVICE_DOMAIN_CS_PS == pstDetachReqMsg->stDetachPara.enDetachDomain) )
        {
            TAF_MMA_SndDetachCnf(&(pstDetachReqMsg->stCtrl), TAF_MMA_APP_OPER_RESULT_FAILURE, TAF_ERR_ERROR);

            return VOS_TRUE;
        }
    }
#endif

    /* �����Ϣ��Ч������Main״̬������ */
    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAttachReq_PreProc
 ��������  : �յ�ID_TAF_MMA_ATTACH_REQ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAttachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ATTACH_REQ_STRU                                *pstAttachReqMsg = VOS_NULL_PTR;

    pstAttachReqMsg   = (TAF_MMA_ATTACH_REQ_STRU *)pstMsg;

    /* Added by s00261364 for L-C��������Ŀ, 2014-1-27, begin */
    /* �����C+Lģʽ */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        /*��ʱ��AT������attach����ظ�ʧ��,���б��� */
        TAF_MMA_SndAttachCnf(&(pstAttachReqMsg->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_PHONE_ATTACH_FORBIDDEN);

        return VOS_TRUE;
    }
    /* Added by s00261364 for L-C��������Ŀ, 2014-1-27, end */

    /* ������Ч�Լ�� */
    if (pstAttachReqMsg->enAttachType > TAF_MMA_ATTACH_TYPE_GPRS_IMSI)
    {
        TAF_MMA_SndAttachCnf(&(pstAttachReqMsg->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_PARA_ERROR);

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* ��ǰ�����CLģʽ���ҽ���detach������CS����CS+PS����ֱ�ӷ���ERROR */
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        if ( (TAF_MMA_ATTACH_TYPE_IMSI == pstAttachReqMsg->enAttachType)
          || (TAF_MMA_ATTACH_TYPE_GPRS_IMSI == pstAttachReqMsg->enAttachType) )
        {
            TAF_MMA_SndAttachCnf(&(pstAttachReqMsg->stCtrl), TAF_MMA_APP_OPER_RESULT_FAILURE, TAF_ERR_ERROR);

            return VOS_TRUE;
        }
    }
#endif

    /* �����Ϣ��Ч������Main״̬������ */
    return VOS_FALSE;
}


/**********************************************************
 �� �� ��  : TAF_MMA_RcvAttachStatusQry_PreProc
 ��������  : ��ȡע��״̬
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��15��
    ��    ��   : c00173809
    �޸�����   : AT �ں���Ŀ,����API��ȡ���ע��״̬��
  2.��    ��   : 2012��07��15��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseI��Ŀ�޸�:�޸ĺ��������ͷ���ֵ
  3.��    ��   : 2015��4��17��
    ��    ��   : h00313353
    �޸�����   : SysCfg Reconsitution
*************************************************************/
VOS_UINT32 TAF_MMA_RcvAttachStatusQry_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enCsStatus;
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enPsStatus;

    Taf_GetCurrentAttachStatus(&enCsStatus, &enPsStatus);

    TAF_MMA_SndAttachStatusQryCnf((TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU *)pstMsg,
                                   TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                   TAF_ERR_NO_ERROR,
                                   enCsStatus,
                                   enPsStatus);

    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : TAF_MMA_IsNeedProcUsimStatusIndInFsmPhoneMode
 ��������  : �Ƿ���Ҫ��phone mode״̬���ﴦ��״̬�ϱ�
 �������  : VOS_UINT32                          ulFsmTopState
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��19��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedProcUsimStatusIndInFsmPhoneMode(
    VOS_UINT32                          ulFsmTopState
)
{
    switch(ulFsmTopState)
    {
        /* ������Щ״̬��Ҫ����״̬�ϱ� */
        case TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT:
        case TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_GET_GEO_CNF:
        case TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_START_CNF:
        case TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_POWER_OFF_CNF:
        case TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_STOP_GET_GEO_CNF:
        case TAF_MMA_PHONE_MODE_STA_GET_GEO_CMP_WAIT_USIM_STATUS_IND:

            return VOS_TRUE;

        default:

            return VOS_FALSE;
    }
}


/*****************************************************************************
 Function Name     :  TAF_MMA_RcvTafPsRatTypeNtf_PreProc
 Description       :  ��Ϣ͸��

 Input parameters  :   VOS_UINT32                          ulEventType,
                       struct MsgCB                       *pstMsg
 Outout parameters :
 Return Value      :   VOS_UINT32

 Modify History:
     1)  Date      :   2015-06-01
         Author    :   y00314741
         Modify content :    Create
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafPsRatTypeNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PS_RAT_TYPE_NTF_STRU       *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg   = (TAF_MMA_PS_RAT_TYPE_NTF_STRU *)pstMsg;

    TAF_MMA_SndMsccPsRatTypeNtf(pstRcvMsg->enRatType);

    return VOS_TRUE;
}

#if 0
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccInterSysStartInd_PreProc
 ��������  : �յ�MSCC_MMA_INTERSYS_START_IND_STRU��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE: ��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��1��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccInterSysStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_INTERSYS_START_IND_STRU   *pstInterSysStartInd = VOS_NULL_PTR;

    pstInterSysStartInd = (MSCC_MMA_INTERSYS_START_IND_STRU*)pstMsg;

    /* CLģʽ�£�HRPD��ѡ��LTE�����л������У�ԭ����ģʽΪHRPD,Ŀ�Ľ���ģʽΪLTE
        InterSysCause ΪReselect.��ʱUE��ʱ�����޽���ϵͳ״̬������ҵ�񻺴档���л���lte��
        �ٰѽ������͸���Ϊlte��
    */

    /* �˴���yanzhijiȷ�ϣ�����Ҫ��APS֪ͨ�޷����ɽ����֪ͨ */
    if ((VOS_RATMODE_HRPD == pstInterSysStartInd->enOrignRatMode)
        && (VOS_RATMODE_LTE == pstInterSysStartInd->enDestRatMode)
        && (NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT == pstInterSysStartInd->enInterSysCause))
    {
        /*TAF_MMA_SndTafServiceStatusInd(MMA_TAF_RAT_TYPE_NULL, VOS_FALSE);*/
    }

    return VOS_TRUE;
}

#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


