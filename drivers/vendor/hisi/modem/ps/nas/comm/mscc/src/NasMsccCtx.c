/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMsccCtx.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2015��01��26��
  ��������   : NAS MSCCȫ�ֱ�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��01��26��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMsccCtx.h"
#include "PsCommonDef.h"
#include "NasMsccFsmSwitchOnTbl.h"
#include "NasMsccFsmPowerOffTbl.h"
#include "NasMsccFsmSysAcqTbl.h"
#include "NasMsccFsmMainTbl.h"
#include "NasNvInterface.h"
#include "NasMsccTimerMgmt.h"
#include "NasMsccMntn.h"
#include "NasMsccProcNvim.h"
#include "xsd_mscc_pif.h"
#include "hsd_mscc_pif.h"

#include "NasMsccFsmBsrTbl.h"

#include "NasMmlCtx.h"

#include "NasMsccComFunc.h"
#include "NasMsccSysAcqStrategy.h"
#include "NasMsccMlplMsplApi.h"
#include "NasMsccFsmSysCfgTbl.h"
#include "NasMsccFsmSysCfg.h"
#include "NasComm.h"

#include "NasMsccFsmCLInterSysTbl.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_CTX_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
NAS_MSCC_CTX_STRU                       g_stNasMsccCtx;




/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetMsccCtxAddr
 ��������  : ��ȡ��ǰMSCC��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰMSCC��CTX��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��26��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_CTX_STRU* NAS_MSCC_GetMsccCtxAddr(VOS_VOID)
{
    return &(g_stNasMsccCtx);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_InitCtx
 ��������  : MSCC������ȫ�ֱ�����ʼ��
 �������  : enInitType - ָʾ�ǿ�����ʼ�����ǹػ���ʼ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��26��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��04��13��
   ��    ��   : y00174758
   �޸�����   : CDMA Iteration 10 Modified
 3. Date      : 2015-04-14
    Author    : a00295761
    Content   : Added Init MS Cfg Info Function
 4. Date      : 2015-04-27
    Author    : y00174758
    Content   : ��ӿ������ػ���ʼ��ָʾ

*****************************************************************************/
VOS_VOID NAS_MSCC_InitCtx(
    NAS_MSCC_INIT_CTX_TYPE_ENUM_UINT8 enInitType
)
{
    NAS_MSCC_CTX_STRU                  *pstMsccCtx = VOS_NULL_PTR;

    pstMsccCtx = NAS_MSCC_GetMsccCtxAddr();

    /* Init the Current FSM context */
    NAS_MSCC_InitCurrFsmCtx(&(pstMsccCtx->stCurFsm));

    /* Init the FSM Stack */
    NAS_MSCC_InitFsmStackCtx(&(pstMsccCtx->stFsmStack));

    /* Init the Cache message queue */
    NAS_MSCC_InitCacheMsgQueue(&(pstMsccCtx->stCacheMsgQueue));

    /* Init the internal message queue */
    NAS_MSCC_InitInternalBuffer(&(pstMsccCtx->stIntMsgQueue));

    /* Init the Timer Context */
    NAS_MSCC_InitTimerCtx(&(pstMsccCtx->astMsccTimerCtx[0]));

    /* INit the Network info Structure. */
    NAS_MSCC_InitNetworkInfo(&(pstMsccCtx->stNwInfo));

    NAS_MSCC_InitMlplMsplInfo(enInitType, &(pstMsccCtx->stMlplMsplInfo));

    NAS_MSCC_InitSimInfo(&(pstMsccCtx->stSimInfo));

    NAS_MSCC_InitMsCfgInfo(&(pstMsccCtx->stMsCfgInfo));

    NAS_MSCC_InitPowerSaveCtrlInfo(&(pstMsccCtx->stPowerSaveCtrl));

    NAS_MSCC_InitSysAcqCtrlInfo(&(pstMsccCtx->stSysAcqCtrl));

    NAS_MSCC_InitMntnInfo(&(pstMsccCtx->stMntnInfo));



    NAS_MSCC_InitNoCardInitSearchLocInfo(&(pstMsccCtx->stSysAcqCtrl.stNoCardInitSearchLoc));
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_InitNetworkInfo
 ��������  : ��ʼ�����������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��26��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��04��11��
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 10 Modified
 3. Date      : 2015-04-14
    Author    : a00295761
    Content   : Added Init Steps
 4. Date      : 2015-09-22
    Author    : y00346957
    Content   : DTS2015070910885 �޸ģ�ɾ����mscc sys pri class����ṹ��

*****************************************************************************/
VOS_VOID NAS_MSCC_InitNetworkInfo(
    NAS_MSCC_NW_INFO_STRU               *pstNwInfo
)
{
    PS_MEM_SET(pstNwInfo, 0, sizeof(NAS_MSCC_NW_INFO_STRU));

    pstNwInfo->stGuNwCapInfo.enLteCsCap    = NAS_MSCC_LTE_CS_CAPBILITY_BUTT;
    pstNwInfo->stGuNwCapInfo.enNwEmcBsCap  = NAS_MSCC_NW_EMC_BS_BUTT;
    pstNwInfo->stGuNwCapInfo.enNwImsVoCap  = NAS_MSCC_NW_IMS_VOICE_BUTT;

    pstNwInfo->stLteNwCapInfo.enLteCsCap   = NAS_MSCC_LTE_CS_CAPBILITY_BUTT;
    pstNwInfo->stLteNwCapInfo.enNwEmcBsCap = NAS_MSCC_NW_EMC_BS_BUTT;
    pstNwInfo->stLteNwCapInfo.enNwImsVoCap = NAS_MSCC_NW_IMS_VOICE_BUTT;

    pstNwInfo->stImsDomainInfo.enPersistentBearerState = NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST;
    pstNwInfo->stImsDomainInfo.enImsVoiceCap           = MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE;

    pstNwInfo->stSysInfo.st3gppSysInfo.enLmmAccessType   = NAS_MSCC_LMM_ACCESS_TYPE_BUTT;
    pstNwInfo->stSysInfo.st3gppSysInfo.enSysMode         = NAS_MSCC_SYS_MODE_BUTT;
    pstNwInfo->stSysInfo.st3gppSysInfo.stPlmnId.ulMcc    = NAS_MSCC_INVALID_MCC;
    pstNwInfo->stSysInfo.st3gppSysInfo.stPlmnId.ulMnc    = NAS_MSCC_INVALID_MNC;
    pstNwInfo->stSysInfo.st3gppSysInfo.ucRac             = NAS_MSCC_INVALID_RAC;
    pstNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag        = VOS_FALSE;
    pstNwInfo->stSysInfo.st3gppSysInfo.ulCellId          = NAS_MSCC_INVALID_CELL_ID;
    pstNwInfo->stSysInfo.st3gppSysInfo.usLac             = NAS_MSCC_INVALID_LAC;
    pstNwInfo->stSysInfo.st3gppSysInfo.enPrioClass       = NAS_MSCC_PIF_PRI_CLASS_ANY;

    /* Init the 1x Sys Info */
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.en1xPrioClass = NAS_MSCC_PIF_PRI_CLASS_ANY;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.enAIPrioClass = NAS_MSCC_PIF_PRI_CLASS_ANY;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.ucCampOnFlg   = VOS_FALSE;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.ulMcc         = NAS_MSCC_INVALID_MCC;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.ulMnc         = NAS_MSCC_INVALID_MNC;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.usSid         = NAS_MSCC_WILDCARD_SID;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.st1xSysInfo.usNid         = NAS_MSCC_WILDCARD_NID;

    /* Init the HRPD Sys Info */
    pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.enAIPrioClass   = NAS_MSCC_PIF_PRI_CLASS_ANY;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.enHrpdPrioClass = NAS_MSCC_PIF_PRI_CLASS_ANY;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.ucCampOnFlg     = VOS_FALSE;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.ulMcc           = NAS_MSCC_INVALID_MCC;
    pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.ucSubNetMask    = 0;
    PS_MEM_SET(pstNwInfo->stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.aucSectorId, 0x00, NAS_MSCC_BYTES_IN_SUBNET);

    /* Init the Service status info */
    pstNwInfo->stServiceStatusInfo.en1xServiceStatus     = NAS_MSCC_SERVICE_STATUS_NO_SERVICE;
    pstNwInfo->stServiceStatusInfo.en3gppPsServiceStatus = NAS_MSCC_SERVICE_STATUS_NO_SERVICE;
    pstNwInfo->stServiceStatusInfo.enHrpdServiceStatus   = NAS_MSCC_SERVICE_STATUS_NO_SERVICE;

    /* Init the Connection status info */
    pstNwInfo->stConnStatusInfo.ucHrpdConnExistFlg   = VOS_FALSE;
    pstNwInfo->stConnStatusInfo.ucLteEpsConnExistFlg = VOS_FALSE;

    pstNwInfo->stSendToImsaInfo.ucRoamFlg            = VOS_FALSE;

    /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
    pstNwInfo->stSendToImsaInfo.enPsRegCnRslt        = NAS_MSCC_PIF_L_REG_PROC_BUTT;
    /* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetGuNwCapInfo
 ��������  : ����GU����������Ϣ
 �������  : pstGuNwCap -- LTE����������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��26��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SetGuNwCapInfo(NAS_MSCC_NETWORK_CAP_INFO_STRU *pstGuNwCap)
{
    NAS_MSCC_NETWORK_CAP_INFO_STRU     *pstGuNwCapInfo = VOS_NULL;

    pstGuNwCapInfo = &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stGuNwCapInfo);

    pstGuNwCapInfo->enLteCsCap   = pstGuNwCap->enLteCsCap;
    pstGuNwCapInfo->enNwEmcBsCap = pstGuNwCap->enNwEmcBsCap;
    pstGuNwCapInfo->enNwImsVoCap = pstGuNwCap->enNwImsVoCap;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetGuNwCapInfo
 ��������  : MSCC������ȫ�ֱ�����ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_NETWORK_CAP_INFO_STRU -- GU����������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��26��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_NETWORK_CAP_INFO_STRU *NAS_MSCC_GetGuNwCapInfo(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stGuNwCapInfo);
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetLteNwCapInfo
 ��������  : ����LTE ����������Ϣ
 �������  : pstLteNwCap -- LTE����������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��26��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SetLteNwCapInfo(NAS_MSCC_NETWORK_CAP_INFO_STRU *pstLteNwCap)
{
    NAS_MSCC_NETWORK_CAP_INFO_STRU     *pstLteNwCapInfo = VOS_NULL;

    pstLteNwCapInfo = &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stLteNwCapInfo);

    pstLteNwCapInfo->enLteCsCap   = pstLteNwCap->enLteCsCap;
    pstLteNwCapInfo->enNwEmcBsCap = pstLteNwCap->enNwEmcBsCap;
    pstLteNwCapInfo->enNwImsVoCap = pstLteNwCap->enNwImsVoCap;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetPersistentBearerState
 ��������  : ���õ�ǰ�Ƿ����persistent eps bearer��ʶ
 �������  : enPersistentBearerState - �Ƿ����persistent eps bearer��ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��12��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_VOID    NAS_MSCC_SetPersistentBearerState(
    NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8             enPersistentBearerState
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stImsDomainInfo.enPersistentBearerState = enPersistentBearerState;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetPersistentBearerState
 ��������  : ��ȡ��ǰ�Ƿ����persistent eps bearer��ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ����persistent eps bearer��ʶ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��12��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8  NAS_MSCC_GetPersistentBearerState(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stImsDomainInfo.enPersistentBearerState;
}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetImsVoiceCapability
 ��������  : ���õ�ǰ��������
 �������  : enImsVoiceCap - IMS��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��8��14��
   ��    ��   : n00269697
   �޸�����   : DTS2015072803051

*****************************************************************************/
VOS_VOID    NAS_MSCC_SetImsVoiceCapability(
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8                      enImsVoiceCap
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stImsDomainInfo.enImsVoiceCap = enImsVoiceCap;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetImsVoiceCapability
 ��������  : ��ȡ��ǰ��������
 �������  : enImsVoiceCap - IMS��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��8��14��
   ��    ��   : n00269697
   �޸�����   : DTS2015072803051

*****************************************************************************/
MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8  NAS_MSCC_GetImsVoiceCapability(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stImsDomainInfo.enImsVoiceCap;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetLteNwCapInfo
 ��������  : MSCC������ȫ�ֱ�����ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_NETWORK_CAP_INFO_STRU -- LTE����������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��26��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_NETWORK_CAP_INFO_STRU *NAS_MSCC_GetLteNwCapInfo(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stLteNwCapInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetCurrSysInfo
 ��������  : ��ȡ��ǰ�����ϵͳ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_SYS_INFO_STRU -- ��ǰ����ϵͳ��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��26��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_SYS_INFO_STRU *NAS_MSCC_GetCurrSysInfo(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetTimerCtxAddr
 ��������  : ��ȡMSCC CTXģ���ж�ʱ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : MSCC CTXģ���ж�ʱ����������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��27��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MSCC_TIMER_CTX_STRU *NAS_MSCC_GetTimerCtxAddr( VOS_VOID )
{
    return &(NAS_MSCC_GetMsccCtxAddr()->astMsccTimerCtx[0]);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetImsCfgInfo
 ��������  : ��ȡMSCCģ����IMS������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : IMS������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��27��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MSCC_IMS_CONFIG_PARA_STRU *NAS_MSCC_GetImsCfgInfo( VOS_VOID )
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stImsCfgInfo);
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetWaitImsVoiceAvailTimerLen
 ��������  : ��ȡ�ȴ�IMS VOICE���õĶ�ʱ��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ȴ�IMS VOICE���õĶ�ʱ��ʱ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetWaitImsVoiceAvailTimerLen(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stImsCfgInfo.ulWaitImsVoiceAvailTimerLen;
}



VOS_VOID  NAS_MSCC_LoadSubFsm(
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId,
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm
)
{
    switch (enFsmId)
    {
        case NAS_MSCC_FSM_SWITCH_ON :
            pstCurFsm->ulState                  = NAS_MSCC_SWITCHON_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetSwitchOnFsmDescAddr();
            break;

        case NAS_MSCC_FSM_POWER_OFF :
            pstCurFsm->ulState                  = NAS_MSCC_POWER_OFF_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetPowerOffFsmDescAddr();
            break;

        case NAS_MSCC_FSM_SYSTEM_CONFIG :
            pstCurFsm->ulState                  = NAS_MSCC_SYSCFG_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetSysCfgFsmDescAddr();
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case NAS_MSCC_FSM_SYS_ACQ :
            pstCurFsm->ulState                  = NAS_MSCC_SYSACQ_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetSysAcqFsmDescAddr();
            break;

        case NAS_MSCC_FSM_CL_INTERSYS:
            pstCurFsm->ulState                  = NAS_MSCC_CL_INTERSYS_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetCLInterSysFsmDescAddr();
            break;

        case NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION :
            pstCurFsm->ulState                  = NAS_MSCC_BSR_STA_INIT;
            pstCurFsm->pstFsmDesc               = NAS_MSCC_GetBsrFsmDescAddr();
            break;
#endif

        default:
            NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_LoadSubFsm:Invalid Fsm Id");
            return;
    }

    /*ִ�г�ʼ��L2״̬���ĺ���*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}




VOS_VOID NAS_MSCC_InitFsmL2(
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId
)
{
    NAS_MSCC_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enParentFsmId;
    VOS_UINT32                          ulParentEventType;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enCurrFsmId;

    enCurrFsmId = NAS_MSCC_GetCurrFsmId();
    if (NAS_MSCC_BUTT == enCurrFsmId)
    {
        /* Sending the Warning Log for this case */
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmL2: NAS_MSCC_GetCurrFsmId return Butt");
    }

    /* The FSM Info is logged in OM */
    NAS_MSCC_MNTN_LogFsmInfo(enCurrFsmId, NAS_MSCC_GetFsmTopState());

    /* Getting the parent FSM ID and the Parent Event Type */
    enParentFsmId     = NAS_MSCC_GetCurrFsmId();
    ulParentEventType = NAS_MSCC_GetCurFsmAddr()->stEntryMsg.ulEventType;

    /* Getting the FSM stack address, Current FSM Context structure. The Current FSM context is pushed to the stack */
    pstFsmStack = NAS_MSCC_GetFsmStackAddr();
    pstCurFsm   = NAS_MSCC_GetCurFsmAddr();
    NAS_MSCC_PushFsm(pstFsmStack, pstCurFsm);

    /* The current FSM context must now contain the ID of the new FSM to be loaded. */
    pstCurFsm->enFsmId = enFsmId;

    /* The current FSM context must contain the init state of the NEW FSM. The initializing function is also called. */
    NAS_MSCC_LoadSubFsm(enFsmId, pstCurFsm);

    /* ��¼�ϲ�״̬�����������Ϣ���� */
    pstCurFsm->enParentFsmId     = enParentFsmId;
    pstCurFsm->ulParentEventType = ulParentEventType;

    enCurrFsmId = NAS_MSCC_GetCurrFsmId();
    if (NAS_MSCC_BUTT == enCurrFsmId)
    {
        /* Log the warning for the error case*/
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmL2: NAS_MSCC_GetCurrFsmId return Butt");
    }

    /* The FSM Info is logged in OM */
    NAS_MSCC_MNTN_LogFsmInfo(enCurrFsmId, NAS_MSCC_GetFsmTopState());
}




VOS_VOID NAS_MSCC_PopFsm( VOS_VOID )
{
    NAS_MSCC_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* Get the FSM Stack Address and the current FSM address */
    pstFsmStack = NAS_MSCC_GetFsmStackAddr();
    pstCurFsm   = NAS_MSCC_GetCurFsmAddr();

    /* If the Stack Depth is empty then return with Error Log */
    if (0 == pstFsmStack->usStackDepth)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_PopFsm: FSM Stack is empty");
        return;
    }

    /* Decrease the Stack depth */
    pstFsmStack->usStackDepth--;

    /* Copy the top Context in FSM stack to the Current FSM Context global structure */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]),
              sizeof(NAS_MSCC_FSM_CTX_STRU));
}




VOS_VOID NAS_MSCC_PushFsm(
    NAS_MSCC_FSM_STACK_STRU             *pstFsmStack,
    NAS_MSCC_FSM_CTX_STRU               *pstNewFsm
)
{
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;

    /* Check if the New FSM stack or the New FSM to be pushed */
    if ((VOS_NULL_PTR == pstFsmStack)
     || (VOS_NULL_PTR == pstNewFsm))
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC,
                       "NAS_MSCC_PushFsm: pstFsmStack or pstNewFsm is null pointer!");

        return;
    }

    /* Check if the Stack Depth is greater than the max FSM stack depth */
    if (pstFsmStack->usStackDepth >= NAS_MSCC_MAX_FSM_STACK_DEPTH)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_PushFsm: Fsm Stack Depth = %d Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    /* Get the address of the top member of the FSM stack and store it in pstCurFsm */
    pstCurFsm = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    /* Copy the New FSM to the address pointed by pstCurFsm */
    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(NAS_MSCC_FSM_CTX_STRU));

    /* Increase the stack depth */
    pstFsmStack->usStackDepth++;

    return;
}




VOS_VOID NAS_MSCC_QuitFsmL2(VOS_VOID)
{

    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enCurrFsmId;

    pstCurFsm = NAS_MSCC_GetCurFsmAddr();

    /* The context specific to the current FSM is re-initialized */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    enCurrFsmId = NAS_MSCC_GetCurrFsmId();
    if (NAS_MSCC_BUTT == enCurrFsmId)
    {
        /* Log Warning if the current FSM ID is abnormal */
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_QuitFsmL2: NAS_MSCC_GetCurrFsmId return Butt");
    }

    /*  Log the Current FSM info to OM */
    NAS_MSCC_MNTN_LogFsmInfo(enCurrFsmId, NAS_MSCC_GetFsmTopState());

    /* Pop the FSM Stack Structure */
    NAS_MSCC_PopFsm();

    enCurrFsmId = NAS_MSCC_GetCurrFsmId();
    if (NAS_MSCC_BUTT == enCurrFsmId)
    {
        /* Log Warning if the current FSM ID is abnormal */
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_QuitFsmL2: NAS_MSCC_GetCurrFsmId return Butt");
    }

    /*  Log the Current FSM info to OM */
    NAS_MSCC_MNTN_LogFsmInfo(enCurrFsmId, NAS_MSCC_GetFsmTopState());

    return;
}




VOS_VOID  NAS_MSCC_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
)
{
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm   = VOS_NULL_PTR;

    /* Get the current FSM address*/
    pstCurFsm                   = NAS_MSCC_GetCurFsmAddr();

    /* Set the current FSM State to the New state */
    pstCurFsm->ulState          = ulCurrState;

    /*  Log the FSM to OM. */
    NAS_MSCC_MNTN_LogFsmInfo(pstCurFsm->enFsmId, ulCurrState);

    return;

}




VOS_UINT32 NAS_MSCC_GetFsmTopState(VOS_VOID)
{
    return (NAS_MSCC_GetCurFsmAddr()->ulState);
}




NAS_MSCC_CACHE_MSG_QUEUE_STRU* NAS_MSCC_GetCacheMsgAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCacheMsgQueue);
}




VOS_UINT32 NAS_MSCC_GetCacheMsgNum(VOS_VOID)
{
    NAS_MSCC_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = NAS_MSCC_GetCacheMsgAddr();

    return pstMsgQueue->ucCacheMsgNum;
}




VOS_UINT32  NAS_MSCC_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* Check if the message size does not exceed the maximum */
    if ((NAS_MSCC_MAX_MSG_BUFFER_LEN - VOS_MSG_HEAD_LENGTH) <= pstMsgHeader->ulLength)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SaveCacheMsg:Len too Long");
        return VOS_FALSE;
    }

    /* If the message does not exceed max size, save in cache message queue.  */
    NAS_MSCC_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return VOS_TRUE;

}




VOS_UINT32 NAS_MSCC_GetNextCachedMsg(
    NAS_MSCC_MSG_STRU                  *pstEntryMsg
)
{
    NAS_MSCC_CACHE_MSG_QUEUE_STRU      *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue = NAS_MSCC_GetCacheMsgAddr();

    /* Check if the Cache is empty */
    if ( 0 == pstMsgQueue->ucCacheMsgNum )
    {
        NAS_INFO_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    /* Copy the first cache message to the pstEntryMsg  */
    PS_MEM_CPY(pstEntryMsg,
               &(pstMsgQueue->astCacheMsg[0]),
               sizeof(NAS_MSCC_MSG_STRU));

    return VOS_TRUE;

}




NAS_MSCC_FSM_CTX_STRU* NAS_MSCC_GetCurFsmAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm);
}




NAS_FSM_DESC_STRU* NAS_MSCC_GetCurFsmDesc(VOS_VOID)
{
    return (NAS_MSCC_GetCurFsmAddr()->pstFsmDesc);
}



NAS_MSCC_FSM_SYS_ACQ_CTX_STRU* NAS_MSCC_GetSysAcqFsmCtxAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSysAcqCtx);
}




NAS_MSCC_FSM_ID_ENUM_UINT32 NAS_MSCC_GetCurrFsmId(VOS_VOID)
{
    return (g_stNasMsccCtx.stCurFsm.enFsmId);
}




NAS_MSCC_MSG_STRU* NAS_MSCC_GetCurrFsmEntryMsgAddr(VOS_VOID)
{
    return &(g_stNasMsccCtx.stCurFsm.stEntryMsg);
}




VOS_UINT8* NAS_MSCC_GetCurrFsmEntryMsgBufferAddr(VOS_VOID)
{
    return (g_stNasMsccCtx.stCurFsm.stEntryMsg.aucMsgBuffer);
}




NAS_MSCC_FSM_STACK_STRU* NAS_MSCC_GetFsmStackAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stFsmStack);
}




VOS_UINT16 NAS_MSCC_GetFsmStackDepth(VOS_VOID)
{
    NAS_MSCC_FSM_STACK_STRU            *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = NAS_MSCC_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}




NAS_MSCC_INT_MSG_QUEUE_STRU* NAS_MSCC_GetIntMsgQueueAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stIntMsgQueue);
}




VOS_VOID NAS_MSCC_InitInternalBuffer(
    NAS_MSCC_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
)
{
    VOS_UINT8                           i;

    for (i = 0; i < NAS_MSCC_MAX_INT_MSG_QUEUE_NUM; i++)
    {
        pstIntMsgQueue->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstIntMsgQueue->ucIntMsgNum = 0;
}




VOS_VOID NAS_MSCC_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
)
{
    VOS_UINT8                           ucIntMsgNum;

    /* Check if the number of internal messages is greater than Max */
    if (NAS_MSCC_MAX_INT_MSG_QUEUE_NUM <= NAS_MSCC_GetIntMsgNum())
    {
        PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);

        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_PutMsgInIntMsgQueue: msg queue is full!" );

        return;
    }

    ucIntMsgNum = NAS_MSCC_GetIntMsgQueueAddr()->ucIntMsgNum;

    /* Insert the message in internal message queue */
    NAS_MSCC_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = pstMsg;

    /* Incrememt the number of internal messages */
    NAS_MSCC_GetIntMsgQueueAddr()->ucIntMsgNum = (ucIntMsgNum + 1);

    return;
}




VOS_UINT8 *NAS_MSCC_GetNextIntMsg(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = NAS_MSCC_GetIntMsgQueueAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* Get the first member in the queue */
        pstIntMsg = NAS_MSCC_GetIntMsgQueueAddr()->pastIntMsg[0];

        /* Decrement the number of internal messages */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* Shift the Queue by one place */
            PS_MEM_MOVE(&(NAS_MSCC_GetIntMsgQueueAddr()->pastIntMsg[0]),
                        &(NAS_MSCC_GetIntMsgQueueAddr()->pastIntMsg[1]),
                        ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* The last member must now point to NULL */
        NAS_MSCC_GetIntMsgQueueAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        NAS_MSCC_GetIntMsgQueueAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
}




VOS_UINT8 NAS_MSCC_GetIntMsgNum(VOS_VOID)
{
    VOS_UINT8                           ucIntMsgNum;

    ucIntMsgNum = NAS_MSCC_GetIntMsgQueueAddr()->ucIntMsgNum;

    return ucIntMsgNum;
}




VOS_VOID NAS_MSCC_ClearCacheMsg(
    VOS_UINT8                           ucIndex
)
{
    NAS_MSCC_CACHE_MSG_QUEUE_STRU       *pstMsgQueue = VOS_NULL_PTR;

    /* IF the index to be cleared is out of bounds, Return */
    if (NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM <= ucIndex)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ClearCacheMsg: Attempted to clear out of bound value!");
        return;
    }

    pstMsgQueue = NAS_MSCC_GetCacheMsgAddr();

    if (0 < pstMsgQueue->ucCacheMsgNum)
    {
        pstMsgQueue->ucCacheMsgNum--;

        if (ucIndex < (NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM - 1))
        {
            /* Shift the Messages from (Index + 1) to (Index). The message at (Index) is deleted */
            PS_MEM_MOVE(&(pstMsgQueue->astCacheMsg[ucIndex]),
                        &(pstMsgQueue->astCacheMsg[ucIndex + 1]),
                        (pstMsgQueue->ucCacheMsgNum - ucIndex) * sizeof(NAS_MSCC_MSG_STRU));
        }

        /* Clear the last member of the queue */
        PS_MEM_SET(&(pstMsgQueue->astCacheMsg[pstMsgQueue->ucCacheMsgNum]),
                   0,
                   sizeof(NAS_MSCC_MSG_STRU));
    }

    NAS_MSCC_MNTN_LogBufferQueueMsg(VOS_FALSE);
}

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))
/*****************************************************************************
Function Name   :   NAS_MSCC_InitFsmCtx_CLInterSys
Description     :   CL��ϵͳ���̵�״̬���ĳ�ʼ������
Input parameters:   None.
Output parameters:  None.
Return Value    :   None.
Modify History:
    1)  Date    :   2015-11-05
        Author  :   w00176964
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_InitFsmCtx_CLInterSys(VOS_VOID)
{
    return;
}

#endif



VOS_VOID NAS_MSCC_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    NAS_MSCC_CACHE_MSG_QUEUE_STRU      *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue  = NAS_MSCC_GetCacheMsgAddr();

    /* Check if the cache message queue is full */
    if (NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM <= pstMsgQueue->ucCacheMsgNum)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SaveCacheMsgInMsgQueue:No Empty buffer");

        return;
    }

    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        /* �������Ѿ�������ͬ�¼�������Ҫ����ӵĶ����� */
        if (pstMsgQueue->astCacheMsg[i].ulEventType == ulEventType)
        {
            return;
        }
    }

    /* Save the message to the end of the cache message queue */
    pstMsgQueue->astCacheMsg[pstMsgQueue->ucCacheMsgNum].ulEventType = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astCacheMsg[pstMsgQueue->ucCacheMsgNum].aucMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    /* Log the Buffer Queue */
    NAS_MSCC_MNTN_LogBufferQueueMsg(VOS_FALSE);

    NAS_INFO_LOG1(UEPS_PID_MSCC, "NAS_MSCC_SaveCacheMsgInMsgQueue: Cache Num = %d", pstMsgQueue->ucCacheMsgNum);
}




VOS_VOID NAS_MSCC_InitCacheMsgQueue(
    NAS_MSCC_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue
)
{
    pstCacheMsgQueue->ucCacheMsgNum = 0;

    PS_MEM_SET(&(pstCacheMsgQueue->astCacheMsg[0]),
               0,
               sizeof(NAS_MSCC_MSG_STRU)*NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM);
}




VOS_VOID NAS_MSCC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSG_STRU                  *pstEntryMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* Get the Current entry message address from the FSM context */
    pstEntryMsg                 = NAS_MSCC_GetCurrFsmEntryMsgAddr();

    ulLen                       = pstMsg->ulLength + VOS_MSG_HEAD_LENGTH;

    /* Save the message received in the entry message address  */
    PS_MEM_CPY( pstEntryMsg->aucMsgBuffer, pstMsg, ulLen );

    /* Save the event type */
    pstEntryMsg->ulEventType    = ulEventType;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetImsSupportFlag
 ��������  : ��ȡ��ǰ�Ƿ�֧��IMS��־,GSM,UTRAN,LTE IMS������һ��֧��IMS����Ϊ֧��IMS
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ�Ƿ�֧��IMS��־
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��27��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetImsSupportFlag(VOS_VOID)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();

    /* ���֧��GSM/UTRAN/LTE IMS, �κ�һ���뼼��֧��IMS������Ϊ֧��IMS */
    if ((VOS_TRUE == pstImsCfgInfo->stImsRatSupport.ucGsmImsSupportFlag)
     || (VOS_TRUE == pstImsCfgInfo->stImsRatSupport.ucUtranImsSupportFlag)
     || (VOS_TRUE == pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag))
    {
        return VOS_TRUE;
    }

    /* �����������Ϊ��ǰ��֧��IMS */
    return VOS_FALSE;
}




NAS_MSCC_FSM_SWITCH_ON_CTX_STRU* NAS_MSCC_GetModuleOrderAddr_SwitchOn(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx);
}




VOS_VOID NAS_MSCC_SetModuleOrder_SwitchOn(VOS_VOID)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU    *pstModuleOrder;

    pstModuleOrder                     = NAS_MSCC_GetModuleOrderAddr_SwitchOn();

    /* Clearing the Module order structure */
    PS_MEM_SET(pstModuleOrder,
               0x00,
               sizeof(NAS_MSCC_FSM_SWITCH_ON_CTX_STRU));

    /* If IMS Feature is ON, Add IMS module ID to the Module order array */
#if (FEATURE_ON == FEATURE_IMS)
    if (VOS_TRUE == NAS_MSCC_GetImsSupportFlag())
    {
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = PS_PID_IMSA;
        pstModuleOrder->usNum ++;
    }
#endif

    /* If CDMA Feature is ON, Add XSD and HSD module ID to the Module order array */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdma1X())
    {
        /* Adding XSD module ID */
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = UEPS_PID_XSD;
        pstModuleOrder->usNum ++;
    }

    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdmaEVDO())
    {
        /* Adding HSD module ID */
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = UEPS_PID_HSD;
        pstModuleOrder->usNum ++;
    }
#endif

    /* If GUL is supported add MMC module ID to the Module order array */
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupport3Gpp())
    {
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = WUEPS_PID_MMC;
        pstModuleOrder->usNum ++;
    }

    /* Reset the module order index */
    pstModuleOrder->usIndex = 0;

    return;
}




VOS_UINT32 NAS_MSCC_GetNextModuleId_SwitchOn(
    VOS_UINT32                          *pulNextModuleId
)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU    *pstModuleOrder;

    pstModuleOrder                      = NAS_MSCC_GetModuleOrderAddr_SwitchOn();

    /* If the index of the Module order array is greater than the Total number of supported Modules, Return FALSE*/
    if (pstModuleOrder->usIndex >= pstModuleOrder->usNum)
    {
        return VOS_FALSE;
    }

    /* Write the next module ID from the module order array at the address pointed by pulNextModuleId */
    *pulNextModuleId = pstModuleOrder->aulModuleID[pstModuleOrder->usIndex];

    /* Increment the index of the module order array */
    pstModuleOrder->usIndex ++;

    return VOS_TRUE;
}




VOS_UINT32 NAS_MSCC_IsModuleOrderValid_SwitchOn(VOS_VOID)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU    *pstModuleOrder;

    pstModuleOrder                   = NAS_MSCC_GetModuleOrderAddr_SwitchOn();

    /* Return FALSE if Number of modules is zero. */
    if (0 == pstModuleOrder->usNum)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_IsModuleOrderValid: Module Number = %d Error!",
                       pstModuleOrder->usNum);
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_IMS)
    /* If IMS feature is enabled, atleast one other module must also be supported. */
    if ((1 == pstModuleOrder->usNum)
     && (PS_PID_IMSA == pstModuleOrder->aulModuleID[0]))
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_IsModuleOrderValid: Module Number = %d Error!",
                       pstModuleOrder->usNum);
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}



NAS_MSCC_FSM_POWER_OFF_CTX_STRU* NAS_MSCC_GetModuleOrderAddr_PowerOff(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stPowerOffCtx);
}


/*****************************************************************************
Function Name   :   NAS_MSCC_SetModuleOrder_PowerOff
Description     :   This function is used to set the module order global structure address. The Power Off order is
                    written in the list by reading the Platform Rat Cap global strucuture in the MSCC global context
Input parameters:   None.
Output parameters:  None.
Return Value    :   None.
Modify History:
    1)  Date    :   2014-02-02
        Author  :   a00295761
        Modify content :    Create

    1)  Date    :   2015-05-08
        Author  :   y00245242
        Modify content : iteration 13����
*****************************************************************************/
VOS_VOID NAS_MSCC_SetModuleOrder_PowerOff(VOS_VOID)
{
    NAS_MSCC_FSM_POWER_OFF_CTX_STRU    *pstModuleOrder;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT16                          usPowerOffHrpdIndex;
    VOS_UINT16                          usPowerOff3GppIndex;

    usPowerOffHrpdIndex                = 0xFFFF;
    usPowerOff3GppIndex                = 0xFFFF;
#endif

    pstModuleOrder                     = NAS_MSCC_GetModuleOrderAddr_PowerOff();

    /* Clearing the Module order structure */
    PS_MEM_SET(pstModuleOrder,
               0x00,
               sizeof(NAS_MSCC_FSM_POWER_OFF_CTX_STRU));

    /* If IMS Feature is ON, Add IMS module ID to the Module order array */
#if (FEATURE_ON == FEATURE_IMS)
    if (VOS_TRUE == NAS_MSCC_GetImsSupportFlag())
    {
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = PS_PID_IMSA;
        pstModuleOrder->usNum ++;
    }
#endif

    /* If CDMA Feature is ON, Add XSD and HSD module ID to the Module order array */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdma1X())
    {
        /* Adding XSD module ID */
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = UEPS_PID_XSD;
        pstModuleOrder->usNum ++;
    }

    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdmaEVDO())
    {
        /* Adding HSD module ID */
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = UEPS_PID_HSD;
        pstModuleOrder->usNum ++;

        usPowerOffHrpdIndex = pstModuleOrder->usNum - 1;
    }
#endif

    /* If GUL is supported add MMC module ID to the Module order array */
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupport3Gpp())
    {
        pstModuleOrder->aulModuleID[pstModuleOrder->usNum] = WUEPS_PID_MMC;
        pstModuleOrder->usNum ++;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        usPowerOff3GppIndex = pstModuleOrder->usNum - 1;
#endif
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* ����HRPD��LTE��֧��ʱ��ȷ����ģ�ȹػ�, ���ｻ��һ������ģpower save˳�� */
    if ((VOS_TRUE == NAS_MSCC_Get3gppActiveFlg())
     && (0xFFFF    != usPowerOffHrpdIndex)
     && (0xFFFF    != usPowerOff3GppIndex))
    {
        pstModuleOrder->aulModuleID[usPowerOffHrpdIndex] = WUEPS_PID_MMC;

        pstModuleOrder->aulModuleID[usPowerOff3GppIndex] = UEPS_PID_HSD;
    }
#endif

    /* Reset the module order index */
    pstModuleOrder->usIndex = 0;

    return;
}




VOS_UINT32 NAS_MSCC_GetNextModuleId_PowerOff(
    VOS_UINT32                          *pulNextModuleId
)
{
    NAS_MSCC_FSM_POWER_OFF_CTX_STRU    *pstModuleOrder;

    pstModuleOrder                      = NAS_MSCC_GetModuleOrderAddr_PowerOff();

    /* If the index of the Module order array is greater than the Total number of supported Modules, Return FALSE*/
    if (pstModuleOrder->usIndex >= pstModuleOrder->usNum)
    {
        return VOS_FALSE;
    }

    /* Write the next module ID from the module order array at the address pointed by pulNextModuleId */
    *pulNextModuleId = pstModuleOrder->aulModuleID[pstModuleOrder->usIndex];

    /* Increment the index of the module order array */
    pstModuleOrder->usIndex ++;

    return VOS_TRUE;
}




VOS_UINT32 NAS_MSCC_IsModuleOrderValid_PowerOff(VOS_VOID)
{
    NAS_MSCC_FSM_POWER_OFF_CTX_STRU    *pstModuleOrder;

    pstModuleOrder                   = NAS_MSCC_GetModuleOrderAddr_PowerOff();

    /* Return FALSE if Number of modules is zero. */
    if (0 == pstModuleOrder->usNum)
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_IsModuleOrderValid: Module Number = %d Error!",
                       pstModuleOrder->usNum);
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_IMS)
    /* If IMS feature is enabled, atleast one other module must also be supported. */
    if ((1 == pstModuleOrder->usNum)
     && (PS_PID_IMSA == pstModuleOrder->aulModuleID[0]))
    {
        NAS_ERROR_LOG1(UEPS_PID_MSCC,
                       "NAS_MSCC_IsModuleOrderValid: Module Number = %d Error!",
                       pstModuleOrder->usNum);
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_IsPlatformSupport3Gpp(VOS_VOID)
{
    VOS_UINT32                                              i;
    VOS_RATMODE_ENUM_UINT32                                 enRatType         = VOS_RATMODE_BUTT;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU                         *pstPlatformRatCap = VOS_NULL_PTR;


    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Check if GSM, WCDMA, TDS or LTE is present in the Platform RAT List */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        enRatType = pstPlatformRatCap->aenRatList[i];

        if ((VOS_RATMODE_GSM             == enRatType)
         || (VOS_RATMODE_WCDMA           == enRatType)
         || (VOS_RATMODE_TDS             == enRatType)
         || (VOS_RATMODE_LTE             == enRatType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_IsPlatformSupport3Gpp2(VOS_VOID)
{
    VOS_UINT32                                              i;
    VOS_RATMODE_ENUM_UINT32                                 enRatType         = VOS_RATMODE_BUTT;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU                         *pstPlatformRatCap = VOS_NULL_PTR;


    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Check if ix or hrpd is present in the Platform RAT List */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        enRatType = pstPlatformRatCap->aenRatList[i];

        if ((VOS_RATMODE_1X     == enRatType)
         || (VOS_RATMODE_HRPD   == enRatType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_IsPlatformSupportLte(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_RATMODE_ENUM_UINT32             enRatType         = VOS_RATMODE_BUTT;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap = VOS_NULL_PTR;


    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Check if LTE is present in the Platform RAT List */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        enRatType = pstPlatformRatCap->aenRatList[i];

        if (VOS_RATMODE_LTE == enRatType)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_IsPlatformSupportCdma1X(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Check if CDMA or EVDO is listed in the plaform RAT LIST */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if ((VOS_RATMODE_1X   == pstPlatformRatCap->aenRatList[i]))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}




VOS_UINT32 NAS_MSCC_IsPlatformSupportCdmaEVDO(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap = VOS_NULL_PTR;

    pstPlatformRatCap = NAS_MSCC_GetPlatformRatCap();

    /* Check if CDMA or EVDO is listed in the plaform RAT LIST */
    for (i = 0 ; i < pstPlatformRatCap->ucRatNum; i++)
    {
        if ((VOS_RATMODE_HRPD   == pstPlatformRatCap->aenRatList[i]))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}




NAS_MSCC_PLATFORM_RAT_CAP_STRU*  NAS_MSCC_GetPlatformRatCap(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stPlatformRatCap);
}




VOS_UINT32 NAS_MSCC_IsPlatformRatCapNvimValid(
    PLATAFORM_RAT_CAPABILITY_STRU      *pstNvPlatformRatCap
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* Return False if the number of the RAT supported is zero */
    if (0 == pstNvPlatformRatCap->usRatNum)
    {
        NAS_TRACE_HIGH("NAS_MSCC_IsPlatformRatCapNvimValid: Number of RATs read from NV Item is zero!");

        return VOS_FALSE;
    }

    for (i = 0; i < pstNvPlatformRatCap->usRatNum; i++)
    {
        /* Check if any duplicate exists in the NVIM data  */
        for (j = i + 1 ; j < pstNvPlatformRatCap->usRatNum; j++)
        {
            if (pstNvPlatformRatCap->aenRatList[i] == pstNvPlatformRatCap->aenRatList[j])
            {
                NAS_TRACE_HIGH("NAS_MSCC_IsPlatformRatCapNvimValid: Duplicates exist in RATs read from NV Item!");

                return VOS_FALSE;
            }
        }

        /* Return False if any undefined value exists */
        if (pstNvPlatformRatCap->aenRatList[i] >= PLATFORM_RAT_BUTT)
        {
            NAS_TRACE_HIGH("NAS_MSCC_IsPlatformRatCapNvimValid: Invalid RAT read from NV Item!");

            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}



VOS_VOID NAS_MSCC_InitCurrFsmCtx(
    NAS_MSCC_FSM_CTX_STRU              *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   NAS_MSCC_FSM_L1_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   NAS_MSCC_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   NAS_MSCC_L1_STA_NULL;
    pstCurrFsmCtx->enParentFsmId            =   NAS_MSCC_BUTT;
    pstCurrFsmCtx->ulParentEventType        =   0;
    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;

    /* Clear the Entry message buffer */
    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucMsgBuffer,
               0x00,
               NAS_MSCC_MAX_MSG_BUFFER_LEN);
}




VOS_VOID NAS_MSCC_InitFsmStackCtx(
    NAS_MSCC_FSM_STACK_STRU            *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;

    for (i = 0 ; i < NAS_MSCC_MAX_FSM_STACK_DEPTH ; i++)
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = NAS_MSCC_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = NAS_MSCC_L1_STA_BUTT;
    }
}




VOS_VOID NAS_MSCC_InitTimerCtx(
    NAS_MSCC_TIMER_CTX_STRU            *pstTimerCtx
)
{
    VOS_UINT32                          i;

    for (i = 0; i < TI_NAS_MSCC_TIMER_BUTT; i++ )
    {
        pstTimerCtx[i].hTimer           = VOS_NULL_PTR;
        pstTimerCtx[i].enTimerId        = TI_NAS_MSCC_TIMER_BUTT;
        pstTimerCtx[i].enTimerStatus    = NAS_MSCC_TIMER_STATUS_STOP;
    }

}




NAS_MSCC_MS_CFG_INFO_STRU* NAS_MSCC_GetMsCfgInfoStruAddr(VOS_VOID)
{
    return (&(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo));
}




VOS_VOID NAS_MSCC_InitFsmCtx_SwitchOn(VOS_VOID)
{
    if (NAS_MSCC_FSM_SWITCH_ON != NAS_MSCC_GetCurrFsmId())
    {
        /* Make Error log is FSM Id is not Switch On */
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmCtx_SwitchOn:ENTERED");

        return;
    }

    NAS_MSCC_InitCardReadInfor(NAS_MSCC_GetCardReadInforAddr());

    /* Create the Switch On Module Order list */
    NAS_MSCC_SetModuleOrder_SwitchOn();
}




VOS_VOID NAS_MSCC_InitFsmCtx_PowerOff(VOS_VOID)
{
    if (NAS_MSCC_FSM_POWER_OFF != NAS_MSCC_GetCurrFsmId())
    {
        /* Make Error log is FSM Id is not Power Off */
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmCtx_PowerOff:ENTERED");

        return;
    }

    /* Create the Power Off Module Order list */
    NAS_MSCC_SetModuleOrder_PowerOff();
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID NAS_MSCC_InitFsmCtx_SysAcq(VOS_VOID)
{

    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU                          *pstSysAcqFsmCtx;

    pstSysAcqFsmCtx     = NAS_MSCC_GetSysAcqFsmCtxAddr();

    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        /* Make Error log is FSM Id is not system acquire */
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmCtx_SysAcq:ENTERED");

        return;
    }

    PS_MEM_SET(pstSysAcqFsmCtx,
               0x00,
               sizeof(NAS_MSCC_FSM_SYS_ACQ_CTX_STRU));

    pstSysAcqFsmCtx->ucNeedReAcqLteFlg               = NAS_MSCC_GetMmssSysAcqCfgInfoAddr()->ucReAcqLteOnHrpdSyncIndFlag;
    pstSysAcqFsmCtx->ucAbortFlg                      = VOS_FALSE;
    pstSysAcqFsmCtx->ucSearchLteFlag                 = VOS_FALSE;
    pstSysAcqFsmCtx->ucSearchHrpdFlag                = VOS_FALSE;
    pstSysAcqFsmCtx->st1xInitLocSta.enLocInfoStatus  = NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_BUTT;
    pstSysAcqFsmCtx->stLteInitLocSta.enLocInfoStatus = NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_BUTT;
}


VOS_VOID NAS_MSCC_InitFsmCtx_BSR(VOS_VOID)
{
    NAS_MSCC_3GPP_SYS_INFO_STRU                            *pst3gppSysInfo = VOS_NULL_PTR;
    NAS_MSCC_HRPD_SYS_INFO_STRU                            *pstHrpdSysInfo = VOS_NULL_PTR;
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                        stOutSysList;
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU                stIn3gppInfo;
    NAS_MSCC_MMSS_MATCH_HRPD_INPUT_INFO_STRU                stInHrpdInfo;
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType;
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enPriClass;
    NAS_MSCC_CTX_STRU                                      *pstMsccCtx = VOS_NULL_PTR;
    VOS_UINT8                                               ucMsplIndex;
    VOS_UINT8                                               ucDefMsplRec;
    NAS_MSCC_MSPL_ID_STRU                                  *pstMatchedMsplTable = VOS_NULL_PTR;

    pstMsccCtx = NAS_MSCC_GetMsccCtxAddr();

    PS_MEM_SET(&(pstMsccCtx->stCurFsm.unFsmCtx.stBsrCtx), 0x00, sizeof(NAS_MSCC_FSM_BSR_CTX_STRU));

    pstMsccCtx->stCurFsm.unFsmCtx.stBsrCtx.stPrefPlmnList.enRat = NAS_MSCC_PIF_NET_RAT_TYPE_LTE;

    if (VOS_TRUE == NAS_MSCC_GetHrpdCampOnFlag())
    {
        pstHrpdSysInfo = NAS_MSCC_GetHrpdSysInfoAddr();

        stInHrpdInfo.enPriClassCdma2000Hrpd = pstHrpdSysInfo->enHrpdPrioClass;
        stInHrpdInfo.enPriClassCdma2000Ai   = pstHrpdSysInfo->enAIPrioClass;
        stInHrpdInfo.ucIsMccValid           = VOS_TRUE;
        stInHrpdInfo.ulMcc                  = pstHrpdSysInfo->ulMcc;
        stInHrpdInfo.ucSubNetMask           = pstHrpdSysInfo->ucSubNetMask;

        PS_MEM_CPY(stInHrpdInfo.aucSectorId,
                   pstHrpdSysInfo->aucSectorId,
                   NAS_MSCC_BYTES_IN_SUBNET);

        PS_MEM_SET(&stOutSysList, 0x00, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

        (VOS_VOID)NAS_MSCC_GetHigherPriMsplSysListThanHrpd(&stInHrpdInfo, &stOutSysList);

        enPriClass = NAS_MSCC_GetDestBsrSysPriClassInSysList(VOS_RATMODE_HRPD, &stOutSysList);
        enSysType  = NAS_MSCC_GetDestBsrSysTypeInSysList(VOS_RATMODE_HRPD, &stOutSysList);
    }
    else
    {
        pst3gppSysInfo         =   NAS_MSCC_Get3gppSysInfoAddr();

        stIn3gppInfo.stPlmnId.ulMcc = pst3gppSysInfo->stPlmnId.ulMcc;
        stIn3gppInfo.stPlmnId.ulMnc = pst3gppSysInfo->stPlmnId.ulMnc;
        stIn3gppInfo.enPriClass     = pst3gppSysInfo->enPrioClass;
        stIn3gppInfo.enSysRat       = VOS_RATMODE_LTE;

        PS_MEM_SET(&stOutSysList, 0x00, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

        pstMatchedMsplTable= NAS_MSCC_GetMatchedMsplTableBy3gppInfo(&stIn3gppInfo);

        if (VOS_NULL_PTR != pstMatchedMsplTable)
        {
            (VOS_VOID)NAS_MSCC_GetHigherPriSysListWithMsplTable(&stIn3gppInfo,
                                                                pstMatchedMsplTable,
                                                                &stOutSysList);
        }

        enSysType  = NAS_MSCC_GetDestBsrSysTypeInSysList(VOS_RATMODE_LTE, &stOutSysList);
        enPriClass = NAS_MSCC_GetDestBsrSysPriClassInSysList(VOS_RATMODE_LTE, &stOutSysList);
    }

    NAS_MSCC_SetDestBsrSysType_BSR(enSysType);
    NAS_MSCC_SetDestBsrSysPriClass_BSR(enPriClass);

    ucMsplIndex = 0;

    ucDefMsplRec = VOS_FALSE;

    NAS_MSCC_SetOrigSysDefMsplRecFlg_BSR(VOS_FALSE);

    if (VOS_TRUE == NAS_MSCC_GetCurrentCampedSysMsplIndex(&ucMsplIndex, &ucDefMsplRec))
    {
        NAS_MSCC_SetOrigSysMsplIndex_BSR(ucMsplIndex);

        NAS_MSCC_SetOrigSysDefMsplRecFlg_BSR(ucDefMsplRec);
    }

    return;
}
#endif

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
/*****************************************************************************
Function Name   :   NAS_MSCC_IsCLCombinedModeWithRatPrio
Description     :   �Ƿ���CL mode
Input parameters:   None.
Output parameters:  None.
Return Value    :

Modify History:
    1)  Date    :   2015-07-13
        Author  :   f00279542
        Modify content :    Create
*****************************************************************************/
VOS_UINT8 NAS_MSCC_IsCLCombinedModeWithRatPrio
(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstUserRatPrio
)
{
    VOS_UINT16                          ulLoop;

    /* ��1X��hrpd rat �ͱ�ʾ��CLģʽ */
    for (ulLoop = 0; ulLoop < pstUserRatPrio->ucRatNum; ulLoop++)
    {
        if ((NAS_MSCC_PIF_NET_RAT_TYPE_1X == pstUserRatPrio->aucRatPrio[ulLoop])
         || (NAS_MSCC_PIF_NET_RAT_TYPE_HRPD == pstUserRatPrio->aucRatPrio[ulLoop]))
        {
            return TRUE;
        }
    }

    return FALSE;
}

#endif



NAS_MSCC_SYSACQ_TIMER_CFG_STRU*         NAS_MSCC_GetSysAcqTimerCfgAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stMmssNvimCfgInfo.stMmssSysAcqCfg.stSysAcqTimerCfg);
}




NAS_MSCC_MMSS_LOCATION_INFO_STRU*       NAS_MSCC_GetMmssLastLocationInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stMmssNvimCfgInfo.stMmssLastLocInfo);
}




NAS_MSCC_MMSS_CFG_INFO_STRU* NAS_MSCC_GetMmssNvimCfgInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stMmssNvimCfgInfo);
}




NAS_MSCC_MMSS_SYSACQ_CFG_STRU* NAS_MSCC_GetMmssSysAcqCfgInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.stMmssNvimCfgInfo.stMmssSysAcqCfg);
}



NAS_MSCC_3GPP_SYS_INFO_STRU* NAS_MSCC_Get3gppSysInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo);
}




NAS_MSCC_1X_SYS_INFO_STRU* NAS_MSCC_Get1xSysInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.st1xSysInfo);
}




NAS_MSCC_HRPD_SYS_INFO_STRU* NAS_MSCC_GetHrpdSysInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.stHrpdSysInfo);
}



VOS_VOID NAS_MSCC_Set1xCampOnFlag(
    VOS_UINT8                           ucFlag
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.st1xSysInfo.ucCampOnFlg = ucFlag;
}



VOS_UINT8 NAS_MSCC_Get1xCampOnFlag(VOS_VOID)
{
   return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.st1xSysInfo.ucCampOnFlg);
}




VOS_VOID NAS_MSCC_SetHrpdCampOnFlag(
    VOS_UINT8                           ucFlag
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.ucCampOnFlg = ucFlag;
}



VOS_UINT8 NAS_MSCC_GetHrpdCampOnFlag(VOS_VOID)
{
   return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.stHrpdSysInfo.ucCampOnFlg);
}



VOS_VOID NAS_MSCC_Set3gppCampOnFlag(
    VOS_UINT8                           ucFlag
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.ucCampOnFlg = ucFlag;
}



NAS_MSCC_SYS_MODE_ENUM_UINT8 NAS_MSCC_Get3gppCurSysMode(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.enSysMode);
}



VOS_UINT8 NAS_MSCC_Get3gppCampOnFlag(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.ucCampOnFlg);
}




VOS_UINT8 NAS_MSCC_GetLteCampOnFlag(VOS_VOID)
{
    if (NAS_MSCC_SYS_MODE_LTE == NAS_MSCC_Get3gppCurSysMode())
    {
        return NAS_MSCC_Get3gppCampOnFlag();
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetCurr3gppRoamingFlg
 ��������  : ���õ�ǰ���������״̬��Ϣ
 �������  : ucRoamingFlg ��ǰ��������״̬��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SetCurr3gppRoamingFlg(
    VOS_UINT8                               ucRoamingFlg
)
{
    (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.ucRoamFlag) = ucRoamingFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetCurr3gppRoamingFlg
 ��������  : ���õ�ǰ���������״̬��Ϣ
 �������  : ucRoamingFlg ��ǰ��������״̬��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetCurr3gppRoamingFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.ucRoamFlag);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_UpdateRoamFlag
 ��������  : ����MSCC�����RoamFlag��ʾ
 �������  : enRegState       --MMC�ϱ���ע��״̬��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID NAS_MSCC_UpdateRoamFlag(
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
)
{
    switch (enRegState)
    {
        case NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK:
            NAS_MSCC_SetCurr3gppRoamingFlg(VOS_FALSE);
            break;

        case NAS_MSCC_PIF_REG_REGISTERED_ROAM:
            NAS_MSCC_SetCurr3gppRoamingFlg(VOS_TRUE);
            break;

        default:
            NAS_NORMAL_LOG1(UEPS_PID_MSCC, "NAS_MSCC_UpdateRoamFlag enRegState", enRegState);
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetCurr3gppPsServiceStatus
 ��������  : ���õ�ǰ�����ҵ��״̬��Ϣ
 �������  : enSrvSt ��ǰ����ҵ��״̬��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��11��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SetCurr3gppPsServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
)
{
    (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.en3gppPsServiceStatus) = enSrvSt;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetCurr3gppPsServiceStatus
 ��������  : ��ȡ��ǰ�����ҵ��״̬��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_SERVICE_STATUS_INFO_STRU -- ��ǰ����ҵ��״̬��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��11��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurr3gppPsServiceStatus(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.en3gppPsServiceStatus);
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetCurr1xServiceStatus
 ��������  : ��ȡ��ǰ�����ҵ��״̬��Ϣ
 �������  : enSrvSt ��ǰ����ҵ��״̬��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��11��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SetCurr1xServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
)
{
    (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.en1xServiceStatus) = enSrvSt;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetCurr1xServiceStatus
 ��������  : ��ȡ��ǰ�����ҵ��״̬��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_SERVICE_STATUS_INFO_STRU -- ��ǰ����ҵ��״̬��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��11��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurr1xServiceStatus(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.en1xServiceStatus);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetCurrHrpdServiceStatus
 ��������  : ��ȡ��ǰ�����ҵ��״̬��Ϣ
 �������  : enSrvSt -- ��ǰ�����ҵ��״̬��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��11��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SetCurrHrpdServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
)
{
    (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.enHrpdServiceStatus) = enSrvSt;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetCurrHrpdServiceStatus
 ��������  : ��ȡ��ǰ�����ҵ��״̬��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_SERVICE_STATUS_INFO_STRU -- ��ǰ����ҵ��״̬��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��11��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurrHrpdServiceStatus(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stServiceStatusInfo.enHrpdServiceStatus);
}




VOS_VOID NAS_MSCC_SetBsrTimerNvimActiveFlag(
    VOS_UINT8                           ucFlag
)
{
    NAS_MSCC_GetMmssNvimCfgInfoAddr()->stMmssSysAcqCfg.stSysAcqTimerCfg.ucIsBsrTimerNvimActiveFlag = ucFlag;
}




VOS_UINT8 NAS_MSCC_GetBsrTimerNvimActiveFlag(VOS_VOID)
{
    return (NAS_MSCC_GetMmssNvimCfgInfoAddr()->stMmssSysAcqCfg.stSysAcqTimerCfg.ucIsBsrTimerNvimActiveFlag);
}

/*****************************************************************************
Function Name   :   NAS_MSCC_InitFsmCtx_L1Main
Description     :   This function is used to init the l1 main fsm ctx
Input parameters:   None.
Output parameters:  None.
Return Value    :   None.
Modify History:
    1)  Date    :   2014-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/

VOS_VOID NAS_MSCC_InitFsmCtx_L1Main(VOS_VOID)
{
    NAS_MSCC_CTX_STRU                  *pstMsccCtx = VOS_NULL_PTR;

    pstMsccCtx = NAS_MSCC_GetMsccCtxAddr();

    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        /* Make Error log is FSM Id is not Power Off */
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_InitFsmCtx_L1Main:ENTERED");

        return;
    }

    pstMsccCtx->stCurFsm.unFsmCtx.stL1MainCtx.stOosAvailableTimerCtx.ulAvailableTimerCount = 0;

    pstMsccCtx->stCurFsm.unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteFullBandSrchCount = 0;
    pstMsccCtx->stCurFsm.unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteHistorySrchCount  = 0;

}


/*****************************************************************************
Function Name   :   NAS_MSCC_GetCurOosAvailableTimerStartCount_L1Main
Description     :   The function is used to get current available timer start count
Input parameters:   None
Output parameters:  None.
Return Value    :   the available timer start count
Modify History:
    1)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_UINT32  NAS_MSCC_GetCurOosAvailableTimerStartCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetCurAvailableTimerStartCount_L1Main,ERROR:FsmId Error");
    }

    return  NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.stOosAvailableTimerCtx.ulAvailableTimerCount;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main
Description     :   The function is used to reset current available timer start count
Input parameters:   None
Output parameters:  None.
Return Value    :   NONE
Modify History:
    1)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-12-12
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_VOID  NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main,ERROR:FsmId Error");

        return;
    }

    NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.stOosAvailableTimerCtx.ulAvailableTimerCount = 0;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_AddCurOosAvailableTimerStartCount_L1Main
Description     :   The function is used to add current available timer start count
Input parameters:   None
Output parameters:  None.
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_VOID  NAS_MSCC_AddCurOosAvailableTimerStartCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_AddCurAvailableTimerStartCount_L1Main,ERROR:FsmId Error");

        return;
    }

    (NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.stOosAvailableTimerCtx.ulAvailableTimerCount)++;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetNextOosAvailableTimerLength_L1Main
Description     :   The function is used to get next start available timer length
Input parameters:   None
Output parameters:  None.
Return Value    :   the next available timer length
Modify History:
    1)  Date    :   2015-04-07
        Author  :   w00176964
        Modify content :    Create
    2)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_UINT32  NAS_MSCC_GetNextOosAvailableTimerLength_L1Main(VOS_VOID)
{
    VOS_UINT32                          ulCount;
    VOS_UINT32                          ulTimerLen;
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU     *pstSysAcqTimerCfg;

    pstSysAcqTimerCfg          = NAS_MSCC_GetSysAcqTimerCfgAddr();

    ulCount                    = NAS_MSCC_GetCurOosAvailableTimerStartCount_L1Main();

    /* �����ǰ�����Ĵ���������available ��ʱ���ĵ�һ�δ���,ʹ�õ�һ��ʱ��,����ʹ�õڶ��ε� */
    if (ulCount <= pstSysAcqTimerCfg->ulAvailableTimerCountFirstSearch)
    {
        ulTimerLen =  (pstSysAcqTimerCfg->ulAvailableTimerLengthFirstSearch);
    }
    else
    {
        ulTimerLen =  (pstSysAcqTimerCfg->ulAvailableTimerLengthDeepSearch);
    }

    return ulTimerLen;
}



VOS_UINT8 NAS_MSCC_GetMlplMsplValidFlag(VOS_VOID)
{
    NAS_MSCC_CTX_STRU                  *pstMsccCtx = VOS_NULL_PTR;

    pstMsccCtx = NAS_MSCC_GetMsccCtxAddr();

    if ((VOS_TRUE == pstMsccCtx->stMlplMsplInfo.ucMlplValid)
     && (VOS_TRUE == pstMsccCtx->stMlplMsplInfo.ucMsplValid))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}



VOS_VOID NAS_MSCC_SetMlplValidFlag(
    VOS_UINT8                           ucValid
)
{
    NAS_MSCC_GetMlplMsplInfoAddr()->ucMlplValid = ucValid;
}



VOS_VOID NAS_MSCC_SetMsplValidFlag(
    VOS_UINT8                           ucValid
)
{
    NAS_MSCC_GetMlplMsplInfoAddr()->ucMsplValid = ucValid;
}



NAS_MSCC_MLPL_MSPL_INFO_STRU* NAS_MSCC_GetMlplMsplInfoAddr(VOS_VOID)
{
    return (&(NAS_MSCC_GetMsccCtxAddr()->stMlplMsplInfo));
}



NAS_MSCC_MLPL_STRU* NAS_MSCC_GetMlplInfoAddr(VOS_VOID)
{
    return (&(NAS_MSCC_GetMsccCtxAddr()->stMlplMsplInfo.stMlplInfo));
}



NAS_MSCC_MSPL_STRU* NAS_MSCC_GetMsplInfoAddr(VOS_VOID)
{
    return (&(NAS_MSCC_GetMsccCtxAddr()->stMlplMsplInfo.stMsplInfo));
}



VOS_UINT32 NAS_MSCC_GetWaitCardReadCnfFlag_SwitchOn(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx.stCardReadInfo.ulWaitCardReadFlag);
}



VOS_VOID NAS_MSCC_SetWaitCardReadCnfFlag_SwitchOn(
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32 enFlag
)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU *pstSwitchOnCtx;

    pstSwitchOnCtx = &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx);

    pstSwitchOnCtx->stCardReadInfo.ulWaitCardReadFlag |= enFlag;
}



VOS_VOID NAS_MSCC_ClearWaitCardReadCnfFlag_SwitchOn(
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32 enFlag
)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU *pstSwitchOnCtx;

    pstSwitchOnCtx = &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx);

    pstSwitchOnCtx->stCardReadInfo.ulWaitCardReadFlag &= ~enFlag;
}


VOS_VOID NAS_MSCC_ResetWaitCardReadCnfFlg_SwitchOn(VOS_VOID)
{
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU *pstSwitchOnCtx;

    pstSwitchOnCtx = &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx);

    pstSwitchOnCtx->stCardReadInfo.ulWaitCardReadFlag = NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_NULL;
}



NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU* NAS_MSCC_GetEhPlmnInfoAddr(VOS_VOID)
{
   return (&(NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimPlmnInfo.stEhPlmnInfo));
}



NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU* NAS_MSCC_GetUserPlmnInfoAddr(VOS_VOID)
{
   return (&(NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimPlmnInfo.stUserPlmnInfo));
}



NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU* NAS_MSCC_GetOperPlmnInfoAddr(VOS_VOID)
{
   return (&(NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimPlmnInfo.stOperPlmnInfo));
}



VOS_VOID NAS_MSCC_InitMlplMsplInfo(
    NAS_MSCC_INIT_CTX_TYPE_ENUM_UINT8                       enInitType,
    NAS_MSCC_MLPL_MSPL_INFO_STRU                           *pstMlplMsplInfo
)
{
    VOS_UINT8                                               ucLoop;

    if (NAS_MSCC_INIT_CTX_STARTUP == enInitType)
    {
        PS_MEM_SET(pstMlplMsplInfo, 0, sizeof(NAS_MSCC_MLPL_MSPL_INFO_STRU));

        return;
    }

    if (NAS_MSCC_INIT_CTX_POWEROFF == enInitType)
    {
        for (ucLoop = 0; ucLoop < NAS_MSCC_MAX_NUM_MLPL_REC; ucLoop++)
        {
            if (VOS_NULL_PTR != pstMlplMsplInfo->stMlplInfo.apstMlplRec[ucLoop])
            {
                PS_MEM_FREE(UEPS_PID_MSCC, pstMlplMsplInfo->stMlplInfo.apstMlplRec[ucLoop]);
            }
        }

        for (ucLoop = 0; ucLoop < NAS_MSCC_MAX_NUM_MSPL_ID; ucLoop++)
        {
            if (VOS_NULL_PTR != pstMlplMsplInfo->stMsplInfo.apstMsplId[ucLoop])
            {
                PS_MEM_FREE(UEPS_PID_MSCC, pstMlplMsplInfo->stMsplInfo.apstMsplId[ucLoop]);
            }
        }

        PS_MEM_SET(pstMlplMsplInfo, 0, sizeof(NAS_MSCC_MLPL_MSPL_INFO_STRU));

        return;
    }
}



VOS_VOID NAS_MSCC_InitSimInfo(
    NAS_MSCC_SIM_INFO_STRU                                 *pstSimInfo
)
{
    PS_MEM_SET(pstSimInfo, 0, sizeof(NAS_MSCC_SIM_INFO_STRU));

    pstSimInfo->stSimStatus.enUsimStatus = NAS_MSCC_PIF_CARD_STATUS_BUTT;
    pstSimInfo->stSimStatus.enCsimStatus = NAS_MSCC_PIF_CARD_STATUS_BUTT;

    /* ����Ĭ��CS��PS��SIM��ע��״̬Ϊ����Ч */
    pstSimInfo->stSimStatus.ucSimCsRegStatus = VOS_TRUE;
    pstSimInfo->stSimStatus.ucSimPsRegStatus = VOS_TRUE;

    NAS_MSCC_InitSimUserPlmnInfo(&(pstSimInfo->stSimPlmnInfo.stUserPlmnInfo));
    NAS_MSCC_InitSimOperPlmnInfo(&(pstSimInfo->stSimPlmnInfo.stOperPlmnInfo));

    pstSimInfo->ucIsCardChanged             = VOS_TRUE;
}



VOS_VOID NAS_MSCC_InitCardReadInfor(
    NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU             *pstCardReadInfo
)
{
    PS_MEM_SET(pstCardReadInfo, 0, sizeof(NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU));
}



NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU* NAS_MSCC_GetCardReadInforAddr(VOS_VOID)
{
    return (&(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSwitchOnCtx.stCardReadInfo));
}



VOS_VOID NAS_MSCC_InitSimUserPlmnInfo(
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU                    *pstUserPlmnInfo
)
{
    VOS_UINT32                                              i;

    pstUserPlmnInfo->ucUserPlmnNum = 0;

    for ( i = 0 ; i < NAS_MSCC_PIF_MAX_USERPLMN_NUM ; i++ )
    {
        pstUserPlmnInfo->astUserPlmnInfo[i].stPlmnId.ulMcc = NAS_MSCC_INVALID_MCC;
        pstUserPlmnInfo->astUserPlmnInfo[i].stPlmnId.ulMnc = NAS_MSCC_INVALID_MNC;
    }
}



VOS_VOID NAS_MSCC_InitSimOperPlmnInfo(
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU                    *pstOperPlmnInfo
)
{
    VOS_UINT32                                              i;

    pstOperPlmnInfo->usOperPlmnNum = 0;

    for ( i = 0 ; i < NAS_MSCC_PIF_MAX_OPERPLMN_NUM ; i++ )
    {
        pstOperPlmnInfo->astOperPlmnInfo[i].stPlmnId.ulMcc   = NAS_MSCC_INVALID_MCC;
        pstOperPlmnInfo->astOperPlmnInfo[i].stPlmnId.ulMnc   = NAS_MSCC_INVALID_MNC;
    }
}




VOS_UINT32 NAS_MSCC_GetAbortFlag_SysAcq(VOS_VOID)
{
    /* �����ǰ״̬������CL system acquire */
    if (NAS_MSCC_FSM_SYS_ACQ!= NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MSCC_GetAbortFlag_SysAcq,ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMsccCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg);
}


VOS_VOID NAS_MSCC_SetAbortFlag_SysAcq(
    VOS_UINT8                           ucAbortFlg
)
{
    /* �����ǰ״̬������CL system acquire */
    if (NAS_MSCC_FSM_SYS_ACQ!= NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MSCC_SetAbortFlag_SysAcq,ERROR:FsmId Error");
    }

    g_stNasMsccCtx.stCurFsm.unFsmCtx.stSysAcqCtx.ucAbortFlg = ucAbortFlg;
}



VOS_UINT8 NAS_MSCC_GetLteInitialAcqFinishFlg_SysAcq(VOS_VOID)
{
    /* �����ǰ״̬������CL system acquire */
    if (NAS_MSCC_FSM_SYS_ACQ!= NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetLteInitialAcqFinishFlg_SysAcq,ERROR:FsmId Error");
    }

    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->stLteInitLocSta.ucAcqFinishFlg);
}




VOS_UINT8 NAS_MSCC_Get1xInitialAcqFinishFlg_SysAcq(VOS_VOID)
{
    /* �����ǰ״̬������CL system acquire */
    if (NAS_MSCC_FSM_SYS_ACQ!= NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_Get1xInitialAcqFinishFlg_SysAcq,ERROR:FsmId Error");
    }

    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->st1xInitLocSta.ucAcqFinishFlg);
}



VOS_VOID NAS_MSCC_SetLteInitialAcqLocInfoStatus_SysAcq(
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enStatus
)
{
    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SetLteInitialAcqLocInfoStatus_SysAcq,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetSysAcqFsmCtxAddr()->stLteInitLocSta.enLocInfoStatus) = enStatus;
}



VOS_VOID NAS_MSCC_Set1xInitialAcqLocInfoStatus_SysAcq(
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enStatus
)
{
    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_Set1xInitialAcqLocInfoStatus_SysAcq,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetSysAcqFsmCtxAddr()->st1xInitLocSta.enLocInfoStatus) = enStatus;
}


NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8 NAS_MSCC_GetLteInitialAcqLocInfoStatus_SysAcq(VOS_VOID)
{
    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetLteInitialAcqLocInfoStatus_SysAcq,ERROR:FsmId Error");
    }

    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->stLteInitLocSta.enLocInfoStatus);
}



NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8 NAS_MSCC_Get1xInitialAcqLocInfoStatus_SysAcq(VOS_VOID)
{
    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_Get1xInitialAcqLocInfoStatus_SysAcq,ERROR:FsmId Error");
    }

    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->st1xInitLocSta.enLocInfoStatus);
}


VOS_UINT8 NAS_MSCC_GetInterSysSearchLteFlag_SysAcq(VOS_VOID)
{
    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->ucSearchLteFlag);
}


VOS_VOID NAS_MSCC_SetInterSysSearchLteFlag_SysAcq(
    VOS_UINT8                               ucSearchLteFLag
)
{
    (NAS_MSCC_GetSysAcqFsmCtxAddr()->ucSearchLteFlag) = ucSearchLteFLag;

    return;
}


VOS_UINT8 NAS_MSCC_GetInterSysSearchHrpdFlag_SysAcq(VOS_VOID)
{
    return (NAS_MSCC_GetSysAcqFsmCtxAddr()->ucSearchHrpdFlag);
}


VOS_VOID NAS_MSCC_SetInterSysSearchHrpdFlag_SysAcq(
    VOS_UINT8                           ucSearchHrpdFLag
)
{
    (NAS_MSCC_GetSysAcqFsmCtxAddr()->ucSearchHrpdFlag) = ucSearchHrpdFLag;

    return;
}


VOS_UINT32 NAS_MSCC_GetScanTimerLength(VOS_VOID)
{
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU     *pstSysAcqTimerCfg;

    pstSysAcqTimerCfg          = NAS_MSCC_GetSysAcqTimerCfgAddr();

    return pstSysAcqTimerCfg->ulScanTimerLen;
}


VOS_UINT32 NAS_MSCC_GetSleepTimerLength(VOS_VOID)
{
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU     *pstSysAcqTimerCfg;

    pstSysAcqTimerCfg          = NAS_MSCC_GetSysAcqTimerCfgAddr();

    return pstSysAcqTimerCfg->ulSleepTimerLen;
}



VOS_UINT8  NAS_MSCC_GetHrpdConnExistFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stConnStatusInfo.ucHrpdConnExistFlg);
}


VOS_VOID  NAS_MSCC_SetHrpdConnExistFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stConnStatusInfo.ucHrpdConnExistFlg = ucFlg;
}


VOS_UINT8  NAS_MSCC_GetLteEpsConnExistFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stConnStatusInfo.ucLteEpsConnExistFlg);
}


VOS_VOID  NAS_MSCC_SetLteEpsConnExistFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stConnStatusInfo.ucLteEpsConnExistFlg= ucFlg;
}



NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8  NAS_MSCC_GetLtePriClass(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gppSysInfo.enPrioClass);
}


NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8  NAS_MSCC_Get1xPriClass(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.st1xSysInfo.en1xPrioClass);
}


NAS_MSCC_PIF_PRI_CLASS_ENUM_UINT8  NAS_MSCC_Get1xAIPriClass(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSysInfo.st3gpp2SysInfo.st1xSysInfo.enAIPrioClass);
}


VOS_VOID  NAS_MSCC_Set1xActiveFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.uc1xActiveFlg = ucFlg;
}


VOS_UINT8  NAS_MSCC_Get1xActiveFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.uc1xActiveFlg);
}


VOS_VOID  NAS_MSCC_SetPowerSaveReplyFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.ucPowerSaveReplyFlg = ucFlg;
}


VOS_UINT8  NAS_MSCC_GetPowerSaveReplyFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.ucPowerSaveReplyFlg);
}


VOS_VOID  NAS_MSCC_SetHrpdActiveFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.ucHrpdActiveFlg = ucFlg;
}


VOS_UINT8  NAS_MSCC_GetHrpdActiveFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.ucHrpdActiveFlg);
}



VOS_VOID  NAS_MSCC_Set3gppActiveFlg(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.uc3gppActiveFlg = ucFlg;
}


VOS_UINT8  NAS_MSCC_Get3gppActiveFlg(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stPowerSaveCtrl.uc3gppActiveFlg);
}





NAS_MSCC_PREF_ORDER_MODULE_LIST* NAS_MSCC_GetPowerSaveModuleOrderAddr_SysCfg(VOS_VOID)
{
    /* If the current FSM is not System config print log */
    if (NAS_MSCC_FSM_SYSTEM_CONFIG != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetPowerSaveModuleOrderAddr_SysCfg : Wrong State entered..!");
    }

    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.stPowerSaveModuleOrder);
}




NAS_MSCC_PREF_ORDER_MODULE_LIST* NAS_MSCC_GetSysCfgModuleOrderAddr_SysCfg(VOS_VOID)
{
    /* If the current FSM is not System config print log */
    if (NAS_MSCC_FSM_SYSTEM_CONFIG != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetSysCfgModuleOrderAddr_SysCfg : Wrong State entered..!");
    }

    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.stSysCfgModuleOrder);
}





VOS_UINT32 NAS_MSCC_GetAbortFlag_BSR(VOS_VOID)
{
    /* �����ǰ״̬������BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetAbortFlag_BSR ERROR:FsmId Error");
    }

    return (VOS_UINT32)(g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucAbortFlag);
}


VOS_VOID NAS_MSCC_SetAbortFlag_BSR(
    VOS_UINT8                           ucAbortFlg
)
{
    /* �����ǰ״̬������BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SetAbortFlag_BSR ERROR:FsmId Error");
    }

    g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucAbortFlag = ucAbortFlg;

    return;
}


VOS_VOID NAS_MSCC_SetDestBsrSysPriClass_BSR(
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enSysPriClass
)
{
    /* �����ǰ״̬������BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetDestBsrSysPriClass_BSR ERROR:FsmId Error");
    }

    g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.enDestBsrSysPriClass = enSysPriClass;
}


NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8 NAS_MSCC_GetDestBsrSysPriClass_BSR(VOS_VOID)
{
    /* �����ǰ״̬������BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetDestBsrSysPriClass_BSR ERROR:FsmId Error");
    }

    return (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.enDestBsrSysPriClass);
}


VOS_VOID NAS_MSCC_SetDestBsrSysType_BSR(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType
)
{
    /* �����ǰ״̬������BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetDestBsrSysType_BSR ERROR:FsmId Error");
    }

    (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.enDestBsrSysType) = enSysType;
}



VOS_VOID NAS_MSCC_SetOrigSysMsplIndex_BSR(
    VOS_UINT8                           ucOrigSysMsplIndex
)
{
    /* �����ǰ״̬������BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SetOrigSysMsplIndex_BSR ERROR:FsmId Error");
    }

    (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucOrigSysMsplIndex) = ucOrigSysMsplIndex;
}


VOS_UINT8 NAS_MSCC_GetOrigSysMsplIndex_BSR(VOS_VOID)
{
    /* �����ǰ״̬������BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SetOrigSysMsplIndex_BSR ERROR:FsmId Error");
    }

    return (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucOrigSysMsplIndex);
}


/*****************************************************************************
Function Name   :   NAS_MSCC_SetOrigSysDefMsplRecFlg_BSR
Description     :   ����ԭʼϵͳ�Ƿ���default mspl�еı��
Input parameters:   ԭʼϵͳ��default mspl�еı��
Output parameters:  None.
Return Value    :   None
Modify History:
    1)  Date    :   2016-01-08
        Author  :   w00176964
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MSCC_SetOrigSysDefMsplRecFlg_BSR(
    VOS_UINT8                           ucOrigSysUseDefMsplRec
)
{
    /* �����ǰ״̬������BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SetOrigSysDefMsplRecFlg_BSR ERROR:FsmId Error");
    }

    (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucOrigSysUseDefMsplRec) = ucOrigSysUseDefMsplRec;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetOrigSysDefMsplRecFlg_BSR
Description     :   ��ȡԭʼϵͳ�Ƿ���default mspl�еı��
Input parameters:   None.
Output parameters:  None.
Return Value    :   ԭʼϵͳ�Ƿ���default mspl�еı��
Modify History:
    1)  Date    :   2016-01-08
        Author  :   w00176964
        Modify content :    Create
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetOrigSysDefMsplRecFlg_BSR(VOS_VOID)
{
    /* �����ǰ״̬������BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetOrigSysDefMsplRecFlg_BSR ERROR:FsmId Error");
    }

    return (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.ucOrigSysUseDefMsplRec);
}





NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8 NAS_MSCC_GetDestBsrSysType_BSR(VOS_VOID)
{
    /* �����ǰ״̬������BSR */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetDestBsrSysType_BSR ERROR:FsmId Error");
    }

    return (g_stNasMsccCtx.stCurFsm.unFsmCtx.stBsrCtx.enDestBsrSysType);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetHrpdHighPrioSysInfo_BSR
 ��������  : ��ȡ�����ȼ�subnet�б�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��07��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU *NAS_MSCC_GetHrpdHighPrioSysInfo_BSR(VOS_VOID)
{
    return &(NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stBsrCtx.stHighPriSysInfo);
}


NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU* NAS_MSCC_GetLtePrefPlmnListInfo_BSR(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stCurFsm.unFsmCtx.stBsrCtx.stPrefPlmnList);
}


VOS_VOID NAS_MSCC_SaveCardStatus(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enCsimStatus
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.enUsimStatus = enUsimStatus;
    NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.enCsimStatus = enCsimStatus;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SaveIsCardChanged
 ��������  : ���濨ICCID�Ƿ����ı�ı�ʶ
 �������  : VOS_UINT8          ��ICCID�Ƿ����ı�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��26��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SaveIsCardChangedFlg(
    VOS_UINT8                           ucIsCardChanged
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSimInfo.ucIsCardChanged    = ucIsCardChanged;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetIsCardChanged
 ��������  : ��ȡ��ICCID�Ƿ����ı�ı�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8          ��ICCID�Ƿ����ı�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��08��26��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetIsCardChangedFlg( VOS_VOID )
{
    return (NAS_MSCC_GetMsccCtxAddr()->stSimInfo.ucIsCardChanged);
}



VOS_VOID  NAS_MSCC_SetSimCsRegStatus(
    VOS_UINT8                           ucSimCsRegStatus
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.ucSimCsRegStatus = ucSimCsRegStatus;
}


VOS_VOID  NAS_MSCC_SetSimPsRegStatus(
    VOS_UINT8                           ucSimPsRegStatus
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.ucSimPsRegStatus = ucSimPsRegStatus;
}


VOS_UINT8  NAS_MSCC_GetSimCsRegStatus(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.ucSimCsRegStatus);
}


VOS_UINT8  NAS_MSCC_GetSimPsRegStatus(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.ucSimPsRegStatus);
}


VOS_VOID NAS_MSCC_SavePrioRatList(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrio
)
{
    VOS_UINT8                           i;

    VOS_UINT8                           ucMinRatNum;

    ucMinRatNum = NAS_COMM_MIN(pstRatPrio->ucRatNum, NAS_MSCC_PIF_MAX_RAT_NUM);

    for (i = 0; i < ucMinRatNum; i++)
    {
        NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stMsSysCfgInfo.stRatPrio.aucRatPrio[i]
             = pstRatPrio->aucRatPrio[i];
    }

    NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stMsSysCfgInfo.stRatPrio.ucRatNum = ucMinRatNum;
}



NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetUsimCardStatus(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.enUsimStatus;
}


NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetCsimCardStatus(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stSimInfo.stSimStatus.enCsimStatus;
}


NAS_MSCC_PIF_RAT_PRIO_STRU* NAS_MSCC_GetRatPrioList(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stMsSysCfgInfo.stRatPrio);
}


VOS_UINT32 NAS_MSCC_IsSpecRatSupported(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat
)
{
    VOS_UINT8                           i;
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrioList;

    pstRatPrioList = NAS_MSCC_GetRatPrioList();

    for (i = 0; i < pstRatPrioList->ucRatNum; i++)
    {
        if (enRat == pstRatPrioList->aucRatPrio[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MSCC_IsUserSysCfgRatCapSupport3Gpp(VOS_VOID)
{
    VOS_UINT32                                              i;
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRatType;
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstRatPrioList = VOS_NULL_PTR;


    pstRatPrioList = NAS_MSCC_GetRatPrioList();

    /* Check if GSM, WCDMA, TDS or LTE is present in the RAT List */
    for (i = 0; i < pstRatPrioList->ucRatNum; i++)
    {
        enRatType = pstRatPrioList->aucRatPrio[i];

        if ((NAS_MSCC_PIF_NET_RAT_TYPE_GSM   == enRatType)
         || (NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA == enRatType)
         || (NAS_MSCC_PIF_NET_RAT_TYPE_LTE   == enRatType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU* NAS_MSCC_GetSysAcqCtrlInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl);
}


VOS_VOID NAS_MSCC_SetCurrBsrTimerLen(
    VOS_UINT32                          ulBsrTimerLen
)
{
    NAS_MSCC_GetSysAcqCtrlInfoAddr()->ulCurrBsrTimerLen = ulBsrTimerLen;
    return;
}


VOS_UINT32 NAS_MSCC_GetCurrBsrTimerLen(VOS_VOID)
{
    return NAS_MSCC_GetSysAcqCtrlInfoAddr()->ulCurrBsrTimerLen;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetEmcCallExistFlag
 ��������  : ���ý���������Ƿ����
 �������  : VOS_UINT8                           ucIsEmcCallExistFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SetEmcCallExistFlag(
    VOS_UINT8                           ucIsEmcCallExistFlg
)
{
    NAS_MSCC_GetSysAcqCtrlInfoAddr()->ucIsEmcCallExist = ucIsEmcCallExistFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetEmcCallExistFlag
 ��������  : ��ȡ����������Ƿ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetEmcCallExistFlag(VOS_VOID)
{
    return NAS_MSCC_GetSysAcqCtrlInfoAddr()->ucIsEmcCallExist;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetCallBackEnableFlag
 ��������  : ���ý������غ����ܱ���Ƿ����
 �������  : VOS_UINT32                          ulCallBackEnableFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SetEmcCallBackEnableFlag(
    VOS_UINT32                          ulCallBackEnableFlg
)
{
    NAS_MSCC_GetSysAcqCtrlInfoAddr()->ulCallBackEnableFlg = ulCallBackEnableFlg;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetCallBackEnableFlag
 ��������  : ��ȡ�������غ������Ƿ�ʹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��6��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetEmcCallBackEnableFlag(VOS_VOID)
{
    return NAS_MSCC_GetSysAcqCtrlInfoAddr()->ulCallBackEnableFlg;
}





VOS_VOID NAS_MSCC_SetOrigBsrTimerStartRat(VOS_VOID)
{
    if (VOS_TRUE == NAS_MSCC_GetHrpdCampOnFlag())
    {
        NAS_MSCC_GetSysAcqCtrlInfoAddr()->enOrigBsrTimerStartRat = VOS_RATMODE_HRPD;
    }
    else if (VOS_TRUE == NAS_MSCC_Get3gppCampOnFlag())
    {
        NAS_MSCC_GetSysAcqCtrlInfoAddr()->enOrigBsrTimerStartRat = VOS_RATMODE_LTE;
    }
    else
    {
    }

    return;
}


VOS_RATMODE_ENUM_UINT32 NAS_MSCC_GetOrigBsrTimerStartRat(VOS_VOID)
{
    return NAS_MSCC_GetSysAcqCtrlInfoAddr()->enOrigBsrTimerStartRat;
}



VOS_VOID NAS_MSCC_InitMsCfgInfo(
    NAS_MSCC_MS_CFG_INFO_STRU          *pstMsCfgInfo
)
{
    /* Init the Custom Cfg Info */
    NAS_MSCC_InitCustomCfgInfo(&(pstMsCfgInfo->stCustomCfgInfo));

    /* Init the Ms Sys Cfg Info */
    NAS_MSCC_InitMsSysCfgInfo(&(pstMsCfgInfo->stMsSysCfgInfo));

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_InitCustomCfgInfo
Description     :   The function is used to init the Custom Cfg Info
Input parameters:   Pointer to Custom Cfg Info global variable.
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   a00295761
        Modify content :    Create
    2)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/

VOS_VOID NAS_MSCC_InitCustomCfgInfo(
    NAS_MSCC_CUSTOM_CONFIG_STRU        *pstCustomCfgInfo
)
{
    /* Init the platform RAT Capability structure */
    NAS_MSCC_InitPlatformRatCapInfo(&(pstCustomCfgInfo->stPlatformRatCap));

    /* Init the IMS Cfg Info */
    NAS_MSCC_InitImsCfgInfo(&(pstCustomCfgInfo->stImsCfgInfo));

    /* Init the MMSS Cfg Info */
    NAS_MSCC_InitMmssCfgInfo(&(pstCustomCfgInfo->stMmssNvimCfgInfo));

    NAS_MSCC_Init1xServiceClSysAcqStrategyInfo(&pstCustomCfgInfo->st1xSrvClSysAcqStrategy);

    return;
}




VOS_VOID NAS_MSCC_InitMsSysCfgInfo(
    NAS_MSCC_MS_SYS_CFG_INFO_STRU      *pstMsSysCfgInfo
)
{
    VOS_UINT32                          i;

    PS_MEM_SET(&(pstMsSysCfgInfo->stRatPrio), 0x00, sizeof(NAS_MSCC_PIF_RAT_PRIO_STRU));

    /* Initializing the Rat Mode List to VOS_RATMODE_BUTT */
    for (i = 0; i < NAS_MSCC_PIF_MAX_RAT_NUM; i++ )
    {
        pstMsSysCfgInfo->stRatPrio.aucRatPrio[i] = NAS_MSCC_PIF_NET_RAT_TYPE_BUTT;

    }

    return;
}




VOS_VOID NAS_MSCC_InitPlatformRatCapInfo(
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap
)
{
    VOS_UINT32                          i;

    PS_MEM_SET(pstPlatformRatCap, 0x00, sizeof(NAS_MSCC_PLATFORM_RAT_CAP_STRU));

    /* Initializing the Rat Mode List to VOS_RATMODE_BUTT */
    for (i = 0; i < NAS_MSCC_PLATFORM_MAX_RAT_NUM; i++ )
    {
        pstPlatformRatCap->aenRatList[i] = VOS_RATMODE_BUTT;

    }

    return;
}




VOS_VOID NAS_MSCC_InitImsCfgInfo(
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo
)
{
    /* Init the IMS RAT Support */
    PS_MEM_SET(&(pstImsCfgInfo->stImsRatSupport), 0, sizeof(NAS_MSCC_IMS_RAT_SUPPORT_STRU));

    pstImsCfgInfo->stImsRatSupport.ucGsmImsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucUtranImsSupportFlag = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucGsmEmsSupportFlag   = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucUtranEmsSupportFlag = VOS_FALSE;
    pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag   = VOS_FALSE;

    /* Init the IMS VOICE Domain */
    pstImsCfgInfo->enVoiceDomain = NAS_MSCC_VOICE_DOMAIN_CS_ONLY;

    /* Init the IMS Voice Avail TImer length to default value */
    pstImsCfgInfo->ulWaitImsVoiceAvailTimerLen = TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_AVAIL_IND_LEN;

    return;
}




VOS_VOID NAS_MSCC_InitMmssCfgInfo(
    NAS_MSCC_MMSS_CFG_INFO_STRU        *pstMmssCfgInfo
)
{
    PS_MEM_SET(pstMmssCfgInfo, 0x00, sizeof(NAS_MSCC_MMSS_CFG_INFO_STRU));

    /* Initialize the control flag of MSCC Reacquire LTE after receiving HSD Sync Ind to FALSE */
    pstMmssCfgInfo->stMmssSysAcqCfg.ucReAcqLteOnHrpdSyncIndFlag = VOS_FALSE;

    /* Initialize the CDMA 1x Location Info as preferred */
    pstMmssCfgInfo->stMmssSysAcqCfg.ucIs1xLocInfoPrefThanLte = VOS_TRUE;

    /* INit the System Acquire Timer Config */
    NAS_MSCC_InitSysAcqTimerCfgInfo(&(pstMmssCfgInfo->stMmssSysAcqCfg.stSysAcqTimerCfg));

    /* Init the Last Location Info */
    NAS_MSCC_InitMmssLastLocationInfo(&(pstMmssCfgInfo->stMmssLastLocInfo));

    return;
}




VOS_VOID NAS_MSCC_InitMmssLastLocationInfo(
    NAS_MSCC_MMSS_LOCATION_INFO_STRU   *pstMmssLastLocationInfo
)
{
    /* Initialize the Location info used in Switch On flag to FALSE and Sys Acq mode as GUL */
    pstMmssLastLocationInfo->ucIsLocInfoUsedInSwitchOn = VOS_FALSE;
    pstMmssLastLocationInfo->enSysAcqMode              = NAS_MSCC_LC_RAT_COMBINED_GUL;

    /* Initialize the Location Info Global variable */
    pstMmssLastLocationInfo->ucCdma1xActiveFlag     = VOS_FALSE;
    pstMmssLastLocationInfo->ucLteActiveFlag        = VOS_FALSE;

    /* Initialize the 1x Location Info */
    pstMmssLastLocationInfo->st1xLocationInfo.ulMcc = NAS_MSCC_INVALID_MCC;
    pstMmssLastLocationInfo->st1xLocationInfo.ulMnc = NAS_MSCC_INVALID_MNC;
    pstMmssLastLocationInfo->st1xLocationInfo.usSid = NAS_MSCC_WILDCARD_SID;
    pstMmssLastLocationInfo->st1xLocationInfo.usNid = NAS_MSCC_WILDCARD_NID;

    /* Initialize the LTE location info */
    pstMmssLastLocationInfo->stLteLocationInfo.ulMcc = NAS_MSCC_INVALID_MCC;
    pstMmssLastLocationInfo->stLteLocationInfo.ulMnc = NAS_MSCC_INVALID_MNC;

    return;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_InitSysAcqTimerCfgInfo
Description     :   The function is used to init the Sys Acq Timer cfg global variable.
Input parameters:   Pointer to Sys Acq Timer cfg  global variable.
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-14
        Author  :   a00295761
        Modify content :    Create

    2) Date     : 2016-01-14
       Author   : W00176964
       Modify   : DTS2016011505496:���Ӷ�ԭʼϵͳ����MSPL�����BSR����,��ʱ��ʱ����NV����

    3)  Date    :   2016-1-14
        Author  :   w00176964
        Modify content : DTS2016010704615:CCF05006����(1����dormant̬,��Ҫ��BSR��ʱ����ʱ����ѡ��
                         LTE��)��ͨ��,��Ҫ�޸�NV2015��BSR��Ĭ��ֵ����ͨ������
*****************************************************************************/

VOS_VOID NAS_MSCC_InitSysAcqTimerCfgInfo(
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU     *pstSysAcqTimerCfg
)
{
    /* �ο��������,BSR��ʱ��Ĭ��ȡNV�е�,���ӿ���ȡ,��֤CCF(11102��11101��05006)����ͨ�� */
    pstSysAcqTimerCfg->ucIsBsrTimerNvimActiveFlag            = VOS_TRUE;

    /* Initialize the Timer Length Structure with default values */
    pstSysAcqTimerCfg->ulAvailableTimerCountFirstSearch     = TI_NAS_MSCC_AVAILABLE_TIMER_COUNT_FIRST_SEARCH;
    pstSysAcqTimerCfg->ulAvailableTimerLengthFirstSearch    = TI_NAS_MSCC_AVAILABLE_TIMER_FIRST_SEARCH_LEN;
    pstSysAcqTimerCfg->ulAvailableTimerLengthDeepSearch     = TI_NAS_MSCC_AVAILABLE_TIMER_DEEP_SEARCH_LEN;
    pstSysAcqTimerCfg->ulBsrTimerLen                        = TI_NAS_MSCC_BSR_TIMER_LEN;
    pstSysAcqTimerCfg->ulScanTimerLen                       = TI_NAS_MSCC_SCAN_TIMER_LEN;
    pstSysAcqTimerCfg->ulSleepTimerLen                      = TI_NAS_MSCC_SLEEP_TIMER_LEN;

    pstSysAcqTimerCfg->ulBsrTimerLenWithNoMatchedMsplRec    = TI_NAS_MSCC_DEFAULT_BSR_TIMER_LEN_WITH_UNMATCHED_MSPL_REC;

    return;
}




VOS_VOID NAS_MSCC_InitPowerSaveCtrlInfo(
    NAS_MSCC_POWER_SAVE_CTRL_CTX_STRU  *pstPowerSaveCtrlInfo
)
{
    PS_MEM_SET(pstPowerSaveCtrlInfo, 0x00, sizeof(NAS_MSCC_POWER_SAVE_CTRL_CTX_STRU));

    pstPowerSaveCtrlInfo->uc1xActiveFlg         = VOS_FALSE;
    pstPowerSaveCtrlInfo->ucHrpdActiveFlg       = VOS_FALSE;
    pstPowerSaveCtrlInfo->uc3gppActiveFlg       = VOS_FALSE;
    pstPowerSaveCtrlInfo->ucPowerSaveReplyFlg   = VOS_FALSE;

    return;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_InitSysAcqCtrlInfo
Description     :   The function is used to init the System Acquire Context global variable
Input parameters:   Pointer to Sys Acq Ctrl Info  global variable.
Output parameters:  None
Return Value    :   None

Modify History:
    1)  Date    :   2015-4-28
        Author  :   t00323010
        Modify content :    Create
    2)  Date    :   2015-9-19
        Author  :   y00346957
        Modify content :    add for DTS2015070910885
      3.��    ��   : 2016��1��6��
        ��    ��   : w00242748
        �޸�����   : DTS2015072705348:����������غ�ģʽ�󣬹���HRPD��LTE���˳�������
                     �غ�ģʽ���ٽ����������������غ�ģʽ�£������������κ���ʽ������
*****************************************************************************/

VOS_VOID NAS_MSCC_InitSysAcqCtrlInfo(
    NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU     *pstSysAcqCtrlInfo
)
{
    pstSysAcqCtrlInfo->enOrigBsrTimerStartRat   = VOS_RATMODE_BUTT;
    pstSysAcqCtrlInfo->ulCurrBsrTimerLen        = 0;

    pstSysAcqCtrlInfo->ucSysAcqMoCallFlag = VOS_FALSE;
    pstSysAcqCtrlInfo->enCur1xServiceSysAcqPhaseNum  = NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE;

    /* Ĭ��LTE��������,���յ�1Xλ����Ϣ����� */
    pstSysAcqCtrlInfo->ucAllowSrchLteFlg        = VOS_TRUE;

    pstSysAcqCtrlInfo->ucIsEmcCallExist         = VOS_FALSE;
    pstSysAcqCtrlInfo->ulCallBackEnableFlg      = VOS_FALSE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_Set1xSysAcqMoCallFlag
Description     :   The function is used to set ucSysAcqMoCallFlag
Input parameters: VOS_UINT8                           ucFlg
Output parameters:  None.
Return Value    :   None
Modify History:
    1)  Date    :   2015-07-09
        Author  :   y00314741
        Modify content :    Create
    2)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_VOID  NAS_MSCC_Set1xSysAcqMoCallFlag(
    VOS_UINT8                           ucFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.ucSysAcqMoCallFlag = ucFlg;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_Get1xSysAcqMoCallFlags
Description     :   The function is used to get ucSysAcqMoCallFlag
Input parameters:   None
Output parameters:  None.
Return Value    :
Modify History:
    1)  Date    :   2015-07-09
        Author  :   y00314741
        Modify content :    Create
    2)  Date    :   2015-12-10
        Author  :   w00176964
        Modify content :CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_UINT8  NAS_MSCC_Get1xSysAcqMoCallFlag(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.ucSysAcqMoCallFlag;
}

VOS_UINT8  NAS_MSCC_GetAllowSrchLteFlg(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.ucAllowSrchLteFlg;
}


VOS_VOID NAS_MSCC_SetAllowSrchLteFlg(
    VOS_UINT8                           ucAllowSrchLteFlg
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.ucAllowSrchLteFlg = ucAllowSrchLteFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_InitMntnInfo
 ��������  : The function is used to init the mntn Context global variableS
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_InitMntnInfo(
    NAS_MSCC_MNTN_CTX_STRU            *pstMntnInfo
)
{
    PS_MEM_SET(pstMntnInfo, 0x00, sizeof(NAS_MSCC_MNTN_CTX_STRU));
    return;
}



/*****************************************************************************
�� �� ��  : NAS_MSCC_AddLogMsgState
��������  : ����stLogMsgState
�������  : usSendPid, usMsgName,usReceivePid
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��7��2��
  ��    ��   : y00322978
  �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_AddLogMsgState(
    VOS_UINT32                          ulSendPid,
    VOS_UINT32                          ulReceivePid,
    VOS_UINT16                          usMsgName
)
{
    NAS_MSCC_LOG_MSG_STATUS_STRU       *pstLogMsgState;
    VOS_UINT8                           ucIndex;

    pstLogMsgState = &(NAS_MSCC_GetMsccCtxAddr()->stMntnInfo.stLogMsgState);

    pstLogMsgState->ucLatestIndex = (pstLogMsgState->ucLatestIndex + 1) % NAS_MSCC_MAX_LOG_MSG_STATE_NUM;

    ucIndex                       = pstLogMsgState->ucLatestIndex;

    PS_MEM_SET(&(pstLogMsgState->stMsgState[ucIndex]), 0, sizeof(NAS_MSCC_MSG_STATE_STRU));

    pstLogMsgState->stMsgState[ucIndex].ulReceiveTime = VOS_GetTick();
    pstLogMsgState->stMsgState[ucIndex].usSendPid     = (VOS_UINT16)ulSendPid;
    pstLogMsgState->stMsgState[ucIndex].usReceivePid  = (VOS_UINT16)ulReceivePid;
    pstLogMsgState->stMsgState[ucIndex].ucMsccFsmId   = (VOS_UINT8)NAS_MSCC_GetCurrFsmId();
    pstLogMsgState->stMsgState[ucIndex].ucMsccState   = (VOS_UINT8)NAS_MSCC_GetFsmTopState();
    pstLogMsgState->stMsgState[ucIndex].usMsgName     = usMsgName;

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MSCC_UpdateExitTime
 ��������  : ������Ϣ�˳���ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_UpdateMsgExitTime( VOS_VOID )
{
    NAS_MSCC_LOG_MSG_STATUS_STRU       *pstLogMsgState;
    VOS_UINT8                           ucIndex;

    pstLogMsgState = &(NAS_MSCC_GetMsccCtxAddr()->stMntnInfo.stLogMsgState);
    ucIndex = pstLogMsgState->ucLatestIndex;

    pstLogMsgState->stMsgState[ucIndex].ulExitTime = VOS_GetTick();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_LogMsgInfo
 ��������  : �ж���Ϣ�Ƿ��Ƕ�ʱ�������ģ�����Ǿʹ�ӡ��ʱ����Ϣ�������ӡ��
             Ϣ��Ϣ
 �������  : MSG_HEADER_STRU
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��01��23��
    ��    ��   : l00324781
    �޸�����   : LOG_MSG_OPTIMIZE �޸�
*****************************************************************************/
VOS_VOID NAS_MSCC_LogMsgInfo(
    MSG_HEADER_STRU                    *pstMsgHeader
)
{
    VOS_UINT32                          ulSenderPid;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulRet;

    /* ��MSCCģ���յ�����Ϣ���ж��Ƿ��ں����б��У�����ڣ������м�¼ */
    ulRet = NAS_MSCC_MNTN_IsNeedDiscardForRcvMsg(pstMsgHeader->ulSenderPid,
                                                 pstMsgHeader->ulReceiverPid,
                                                 pstMsgHeader->ulMsgName);
    if (VOS_TRUE == ulRet)
    {
        return;
    }
    /* ��MSCCģ�鷢�͵���Ϣ���ж��Ƿ��ں����б��У�����ڣ������м�¼ */
    ulRet = NAS_MSCC_MNTN_IsNeedDiscardForSndMsg(pstMsgHeader->ulSenderPid,
                                                 pstMsgHeader->ulReceiverPid,
                                                 pstMsgHeader->ulMsgName);
    if (VOS_TRUE == ulRet)
    {
        return;
    }

    /* �жϷ���id�Ƿ��Ƕ�ʱ�� */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        ulSenderPid      =    ((REL_TIMER_MSG*)pstMsgHeader)->ulSenderPid;
        ulReceiverPid    =    ((REL_TIMER_MSG*)pstMsgHeader)->ulReceiverPid;
        ulMsgName        =    ((REL_TIMER_MSG*)pstMsgHeader)->ulName;
    }
    else
    {
        ulSenderPid      =    pstMsgHeader->ulSenderPid;
        ulReceiverPid    =    pstMsgHeader->ulReceiverPid;
        ulMsgName        =    pstMsgHeader->ulMsgName;
    }

    /* ��ӡ��Ϣ */
    NAS_MSCC_AddLogMsgState(ulSenderPid, ulReceiverPid, (VOS_UINT16)ulMsgName);

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_IsCLModeSupportedInRatList
 ��������  : �ж�Ŀ����뼼���Ƿ�֧��CLģʽ
 �������  : NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrioList
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE  ��ʾ֧��
             VOS_FASLE ��ʾ��֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��21��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsCLModeSupportedInRatList(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrioList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < (VOS_UINT32)pstRatPrioList->ucRatNum; i++ )
    {
        if ( (NAS_MSCC_PIF_NET_RAT_TYPE_1X == pstRatPrioList->aucRatPrio[i])
          || (NAS_MSCC_PIF_NET_RAT_TYPE_HRPD == pstRatPrioList->aucRatPrio[i]) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_Init1xServiceClSysAcqStrategyInfo
 ��������  : ��ʼ��1x�з���ʱCLϵͳ�������NV��Ϣ
 �������  : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_STRU
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��14��
    ��    ��   : w00176964
    �޸�����   : DTS2016010704615:�޸�NVĬ��ֵ��֤CCF����ͨ��
*****************************************************************************/
VOS_VOID NAS_MSCC_Init1xServiceClSysAcqStrategyInfo(
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_STRATEGY_STRU    *pstSysAcqStrategy
)
{
    pstSysAcqStrategy->stPhaseOnePatternCfg.ucLteFullBandSrchNum = NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_ONE_FULL_BAND_SRCH_NUM;
    pstSysAcqStrategy->stPhaseOnePatternCfg.ucLteHistorySrchNum  = NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_ONE_HISTORY_SRCH_NUM;
    pstSysAcqStrategy->stPhaseOnePatternCfg.usSleepTimeLen       = TI_NAS_MSCC_DEFAULT_1X_SERVICE_AVAILABLE_TIMER_PHASE_ONE_SLEEP_TIMER_LEN;
    pstSysAcqStrategy->stPhaseOnePatternCfg.usTotalTimeLen       = TI_NAS_MSCC_DEFAULT_1X_SERVICE_AVAILABLE_TIMER_PHASE_ONE_TOTAL_TIMER_LEN;

    pstSysAcqStrategy->stPhaseTwoPatternCfg.ucLteFullBandSrchNum = NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_TWO_FULL_BAND_SRCH_NUM;
    pstSysAcqStrategy->stPhaseTwoPatternCfg.ucLteHistorySrchNum  = NAS_MSCC_DEFAULT_1X_SERVICE_PHASE_TWO_HISTORY_SRCH_NUM;
    pstSysAcqStrategy->stPhaseTwoPatternCfg.usSleepTimeLen       = TI_NAS_MSCC_DEFAULT_1X_SERVICE_AVAILABLE_TIMER_PHASE_TWO_SLEEP_TIMER_LEN;
    pstSysAcqStrategy->stPhaseTwoPatternCfg.usTotalTimeLen       = 0;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_Get1xServiceClSysAcqPatternONeCfgAddr
 ��������  : ��ȡ1x�з���ʱCLϵͳ������Խ׶�1NV��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU* NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.st1xSrvClSysAcqStrategy.stPhaseOnePatternCfg);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr
 ��������  : ��ȡ1x�з���ʱCLϵͳ������Խ׶�2NV��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PATTERN_CFG_STRU* NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stMsCfgInfo.stCustomCfgInfo.st1xSrvClSysAcqStrategy.stPhaseTwoPatternCfg);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetCur1xServiceSysAcqPhaseNum
 ��������  : ��ȡ1x�з���ʱCLϵͳ����ǰ�����ĸ��׶�
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8 NAS_MSCC_GetCur1xServiceSysAcqPhaseNum(VOS_VOID)
{
    return (NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.enCur1xServiceSysAcqPhaseNum);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetCur1xServiceSysAcqPhaseNum
 ��������  : ����1x�з���ʱCLϵͳ����ǰ�����ĸ��׶�
 �������  : NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SetCur1xServiceSysAcqPhaseNum(
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8  enPhase
)
{
    (NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.enCur1xServiceSysAcqPhaseNum) = enPhase;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_ResetCur1xServiceSysAcqPhaseNum
 ��������  : RESET 1x�з���ʱCLϵͳ����׶�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_ResetCur1xServiceSysAcqPhaseNum(VOS_VOID)
{
    (NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.enCur1xServiceSysAcqPhaseNum) = NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_AddCur1xServiceSysAcqPhaseNum
 ��������  : add 1x�з���ʱCLϵͳ����׶�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_AddCur1xServiceSysAcqPhaseNum(VOS_VOID)
{
    (NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.enCur1xServiceSysAcqPhaseNum)++;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main
 ��������  : ��ȡ��ǰ1x�з���ʱavailable��ʱ����ʱ������LTEȫƵ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main,ERROR:FsmId Error");
    }

    return NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteFullBandSrchCount;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main
 ��������  : reset��ǰ1x�з���ʱavailable��ʱ����ʱ������lteȫƵ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteFullBandSrchCount) = 0;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_AddCur1xServiceLteFullBandSrchCount_L1Main
 ��������  : ������ǰ1x�з���ʱavailable��ʱ����ʱ������ȫƵ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_AddCur1xServiceLteFullBandSrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_AddCur1xServiceLteFullBandSrchCount_L1Main,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteFullBandSrchCount)++;
}




/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main
 ��������  : ��ȡ��ǰ1x�з���ʱavailable��ʱ����ʱ��������ʷƵ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main,ERROR:FsmId Error");
    }

    return NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteHistorySrchCount;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main
 ��������  : reset��ǰ1x�з���ʱavailable��ʱ����ʱ��������ʷƵ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteHistorySrchCount) = 0;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_AddCur1xServiceLteHistorySrchCount_L1Main
 ��������  : ������ǰ1x�з���ʱavailable��ʱ����ʱ��������ʷƵ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_AddCur1xServiceLteHistorySrchCount_L1Main(VOS_VOID)
{
    if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_AddCur1xServiceLteHistorySrchCount_L1Main,ERROR:FsmId Error");
    }

    (NAS_MSCC_GetCurFsmAddr()->unFsmCtx.stL1MainCtx.st1xServiceAvailableTimerCtx.ucCurLteHistorySrchCount)++;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetNext1xServiceAvailableTimerLength_L1Main
 ��������  : ��ȡ�´�1x�з���ʱavailable��ʱ��������ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32  NAS_MSCC_GetNext1xServiceAvailableTimerLength_L1Main(
    NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ENUM_UINT8  enPhaseNum
)
{
    VOS_UINT32                          ulTimerLen;

    /* �¸��׶�Ϊ1�׶�,ȡһ�׶ε�sleepʱ��������ȡ2�׶�,��ΪĿǰֻ���������׶� */
    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE == enPhaseNum)
    {
        ulTimerLen =  (NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->usSleepTimeLen) * NAS_MSCC_THOUSAND_MILLISECOND_UNIT;
    }
    else
    {
        ulTimerLen =  (NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->usSleepTimeLen) * NAS_MSCC_THOUSAND_MILLISECOND_UNIT;
    }

    return ulTimerLen;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_IsNeedPerfromLteFullBandSrchWith1xServiceExist_L1Main
 ��������  : �Ƿ���Ҫִ��LteȫƵ����1x�������ʱ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫִ��LteȫƵ����1x�������ʱ
             VOS_FALSE:����Ҫִ��LteȫƵ����1x�������ʱ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��14��
    ��    ��   : w00176964
    �޸�����   : DTS2016011505664:�������Խ��е���,ȫƵ��L������ʷ��L
*****************************************************************************/

VOS_UINT32  NAS_MSCC_IsNeedPerfromLteFullBandSrchWith1xServiceExist_L1Main(VOS_VOID)
{
    VOS_UINT8                           ucFullBandSrchNum;
    VOS_UINT8                           ucCurFullBandSrchCount;
    VOS_UINT8                           ucCurHistorySrchCount;
    VOS_UINT8                           ucHistorySrchNum;

    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
    {
        ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteHistorySrchNum;

        ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteFullBandSrchNum;
    }
    else
    {
        ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteHistorySrchNum;

        ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteFullBandSrchNum;
    }

    /* ��ʷ�Ѵ���Ϊ0��ȫƵ�Ѵ�����Ϊ0,һֱ����ȫƵ�� */
    if ((0 == ucHistorySrchNum)
     && (0 != ucFullBandSrchNum))
    {
        return VOS_TRUE;
    }

    ucCurFullBandSrchCount = NAS_MSCC_GetCur1xServiceLteFullBandSrchCount_L1Main();
    ucCurHistorySrchCount  = NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main();

    /* ��ǰ����ȫƵ�δ���С��NV�����õ����ֵ����ʷ�Ѵ����ﵽ���ֵʱ,��Ҫ����ȫƵ������ */
    if ((ucCurFullBandSrchCount < ucFullBandSrchNum)
     && (ucCurHistorySrchCount  == ucHistorySrchNum))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_IsNeedPerfromLteHistorySrchWith1xServiceExist_L1Main
 ��������  : �Ƿ���Ҫִ��Lte��ʷƵ��������1x�������ʱ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫִ��Lte��ʷƵ��������1x�������ʱ
             VOS_FALSE:����Ҫִ��Lte��ʷƵ��������1x�������ʱ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32  NAS_MSCC_IsNeedPerfromLteHistorySrchWith1xServiceExist_L1Main(VOS_VOID)
{
    VOS_UINT8                           ucHistorySrchNum;
    VOS_UINT8                           ucCurHistorySrchCount;
    VOS_UINT8                           ucFullBandSrchNum;

    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE == NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
    {
        ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteHistorySrchNum;

        ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->ucLteFullBandSrchNum;
    }
    else
    {
        ucHistorySrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteHistorySrchNum;

        ucFullBandSrchNum = NAS_MSCC_Get1xServiceClSysAcqPatternTwoCfgAddr()->ucLteFullBandSrchNum;
    }

    /* ��ʷ�Ѵ�����Ϊ0��ȫƵ�Ѵ���Ϊ0,һֱ������ʷ�� */
    if ((0 == ucFullBandSrchNum)
     && (0 != ucHistorySrchNum))
    {
        return VOS_TRUE;
    }

    ucCurHistorySrchCount = NAS_MSCC_GetCur1xServiceLteHistorySrchCount_L1Main();

    /* ��ǰ������ʷƵ�����С��NV�����õ����ֵ,��Ҫ������ʷƵ������ */
    if (ucCurHistorySrchCount < ucHistorySrchNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetNextAvailableTimerLength_L1Main
 ��������  : ��ȡ�´�available��ʱ��������ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32  NAS_MSCC_GetNextAvailableTimerLength_L1Main(VOS_VOID)
{
    if (VOS_TRUE == NAS_MSCC_Is1xNormalService())
    {
        return NAS_MSCC_GetNext1xServiceAvailableTimerLength_L1Main(NAS_MSCC_GetCur1xServiceSysAcqPhaseNum());
    }

    return NAS_MSCC_GetNextOosAvailableTimerLength_L1Main();
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main
 ��������  : ����1x�з���ʱCLϵͳ����׶�1������ʱ����ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID  NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main(VOS_VOID)
{
    VOS_UINT16                          usPhaseOneTotalTimerLen;
    VOS_UINT16                          usPhaseOneSleepTimerLen;

    /* �Ѿ������ڽ׶�1,����Ҫ���� */
    if (NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE != NAS_MSCC_GetCur1xServiceSysAcqPhaseNum())
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main: not in phase one");

        return;
    }

    usPhaseOneTotalTimerLen = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->usTotalTimeLen;
    usPhaseOneSleepTimerLen = NAS_MSCC_Get1xServiceClSysAcqPatternOneCfgAddr()->usSleepTimeLen;

    /* NV��������ʱ��Ϊ0������ */
    if (0 == usPhaseOneTotalTimerLen)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main: total timer len is zero");

        return;
    }

    /* NV��������ʱ��С��sleepʱ��,������ */
    if (usPhaseOneTotalTimerLen < usPhaseOneSleepTimerLen)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_Start1xServiceClSysAcqPhaseOneTotalTimer_L1Main: total timer len less than sleep timer len");

        return;
    }

    (VOS_VOID)NAS_MSCC_StartTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER, usPhaseOneTotalTimerLen * NAS_MSCC_THOUSAND_MILLISECOND_UNIT );

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_Reset1xServiceClSysAcqRelatedInfo_L1Main
 ��������  : reset 1x�з���ʱCLϵͳ���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��15��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_VOID  NAS_MSCC_Reset1xServiceClSysAcqRelatedInfo_L1Main(VOS_VOID)
{
    NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

    NAS_MSCC_StopTimer(TI_NAS_MSCC_1X_SERVICE_CL_SYSTEM_ACQUIRE_PHASE_ONE_TOTAL_TIMER);

    NAS_MSCC_ResetCur1xServiceLteHistorySrchCount_L1Main();

    NAS_MSCC_ResetCur1xServiceLteFullBandSrchCount_L1Main();

    NAS_MSCC_ResetCur1xServiceSysAcqPhaseNum();

    NAS_MSCC_ResetCurOosAvailableTimerStartCount_L1Main();

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MSCC_InitNoCardInitSearchLocInfo
 ��������  : �޿�����λ����Ϣ���ݳ�ʼ��
 �������  : NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU         *pstNoCardInitSearchLocInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_InitNoCardInitSearchLocInfo(
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo
)
{
    pstNoCardInitSearchLocInfo->stInitSearchGulLoc.ulMcc  = NAS_MSCC_INVALID_MCC;
    pstNoCardInitSearchLocInfo->stInitSearchGulLoc.ulMnc  = NAS_MSCC_INVALID_MNC;
    pstNoCardInitSearchLocInfo->stInitSearchCdmaLoc.lSid  = NAS_MSCC_INVALID_SID;
    pstNoCardInitSearchLocInfo->stInitSearchCdmaLoc.lNid  = NAS_MSCC_INVALID_NID;
    pstNoCardInitSearchLocInfo->stInitSearchCdmaLoc.ulMcc = NAS_MSCC_INVALID_MCC;
    pstNoCardInitSearchLocInfo->enInitSearchWaitType      = NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_BUTT;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetNoCardInitSearchLocInfoAddr
 ��������  : ��ȡ�޿�����λ����Ϣ���ݵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU *NAS_MSCC_GetNoCardInitSearchLocInfoAddr(VOS_VOID)
{
    return &(NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc);
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_Update1xNoCardInitSearchLocInfo
 ��������  : ����1x�޿�����λ����Ϣ����
 �������  : VOS_INT32 lSid
             VOS_INT32 lNid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_Update1xNoCardInitSearchLocInfo(
    VOS_INT32                           lSid,
    VOS_INT32                           lNid
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.stInitSearchCdmaLoc.lSid = lSid;
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.stInitSearchCdmaLoc.lNid = lNid;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_Update1xNoCardInitSearchLocMcc
 ��������  : ����1x�޿�����λ����Ϣ��MCCֵ
 �������  : VOS_UINT32    ulMcc
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_Update1xNoCardInitSearchLocMcc(
    VOS_UINT32                          ulMcc
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.stInitSearchCdmaLoc.ulMcc = ulMcc;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_UpdateGulNoCardInitSearchLocInfo
 ��������  : ����Gul�޿�����λ����Ϣ����
 �������  : VOS_UINT32 ulMcc
             VOS_UINT32 ulMcc
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_UpdateGulNoCardInitSearchLocInfo(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.stInitSearchGulLoc.ulMcc = ulMcc;
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.stInitSearchGulLoc.ulMnc = ulMnc;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetNoCardInitSearchWaitType
 ��������  : �����޿����ѵ�ǰ�ȴ��ĳ�������
 �������  : NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32  enNoCardInitSearchWaitType
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_SetNoCardInitSearchWaitType(
    NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32      enNoCardInitSearchWaitType
)
{
    NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.enInitSearchWaitType = enNoCardInitSearchWaitType;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetNoCardInitSearchWaitType
 ��������  : ��ȡ�޿����ѵ�ǰ�ȴ��ĳ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32  enNoCardInitSearchWaitType
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_NO_CARD_INIT_SEARCH_WAIT_TYPE_ENUM_UINT32 NAS_MSCC_GetNoCardInitSearchWaitType(VOS_VOID)
{
    return NAS_MSCC_GetMsccCtxAddr()->stSysAcqCtrl.stNoCardInitSearchLoc.enInitSearchWaitType;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_ResetNoCardInitSearchInfo
 ��������  : �����޿����ѵ�ǰ�ȴ��ĳ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : j00354216
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MSCC_ResetNoCardInitSearchInfo(VOS_VOID)
{
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo = VOS_NULL_PTR;

    pstNoCardInitSearchLocInfo = NAS_MSCC_GetNoCardInitSearchLocInfoAddr();

    NAS_MSCC_Update1xNoCardInitSearchLocMcc(NAS_MSCC_INVALID_MCC);

    NAS_MSCC_Update1xNoCardInitSearchLocInfo(NAS_MSCC_INVALID_SID,
                                             NAS_MSCC_INVALID_NID);

    NAS_MSCC_UpdateGulNoCardInitSearchLocInfo(NAS_MSCC_INVALID_MCC,
                                              NAS_MSCC_INVALID_MNC);
    /* ����λ����Ϣ��ʹ�ù����ñ�־λΪTRUE */
    pstNoCardInitSearchLocInfo->ucIsLocInfoUsed = VOS_TRUE;

    return;
}

/* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
/*****************************************************************************
 �� �� ��  : NAS_MSCC_SetPsRegSuccProcType
 ��������  : ���õ�ǰע��ɹ���������
 �������  : enPsRegCnRslt
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��5��
    ��    ��   : z00359541
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_SetPsRegSuccProcType(
    NAS_MSCC_PIF_PS_REG_PROC_ENUM_UINT32                     enPsRegCnRslt
)
{
    NAS_NORMAL_LOG1(UEPS_PID_MSCC, "NAS_MSCC_SetPsRegSuccProcType: enPsRegCnRslt", enPsRegCnRslt);
    NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSendToImsaInfo.enPsRegCnRslt = enPsRegCnRslt;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetPsRegSuccProcType
 ��������  : ��ȡ��ǰע��ɹ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰע��ɹ���������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��5��
    ��    ��   : z00359541
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MSCC_GetPsRegSuccProcType(VOS_VOID)
{
    NAS_NORMAL_LOG1(UEPS_PID_MSCC, "NAS_MSCC_GetPsRegSuccProcType: enPsRegCnRslt", (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSendToImsaInfo.enPsRegCnRslt));
    return (NAS_MSCC_GetMsccCtxAddr()->stNwInfo.stSendToImsaInfo.enPsRegCnRslt);
}
/* Added by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



