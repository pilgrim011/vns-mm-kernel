/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaServiceManagement.c
  Description     : ��C�ļ�ʵ�ַ������ģ��ĳ�ʼ�����ڲ���Ϣ�Ĵ���ͷ���
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaServiceManagement.h"
#include "ImsaEntity.h"
#include "ImsaPublic.h"
#include "ImsaInterface.h"
#include "ImsaProcMsccMsg.h"
#include "ImsaCallManagement.h"
#include "ImsaProcAtMsg.h"
#include "ImsaProcSpmMsg.h"
#include "ImsaProcSmsMsg.h"
#include "ImsaProcUssdMsg.h"
#include "ImsaImsAdaption.h"

#include "ImsaLmmInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_IMSASERVICEMANAGEMENT_C
#define    THIS_NAS_FILE_ID      NAS_FILE_ID_IMSASERVICEMANAGEMENT_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
IMSA_SUBSCRIPTION_INFO_LIST_STRU    g_stSubcriptionInfoList = {0};              /**< ������Ϣ�б� */

extern VOS_VOID IMSA_CONTROL_InitConfigPara( VOS_VOID );
extern VOS_VOID IMSA_CONTROL_InitNetworkInfo( VOS_VOID );
extern VOS_VOID IMSA_SRV_RatFormatTransform
(
    IMSA_CAMPED_RAT_TYPE_ENUM_UINT8    *penImsaRat,
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enMmaRat
);
extern VOS_UINT32 IMSA_SRV_IsCurRatSupportEms( VOS_VOID );
extern VOS_UINT32 IMSA_SRV_IsNrmSrvIsimParaSatisfied( VOS_VOID );
extern IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32 IMSA_SRV_IsNrmSrvConditonSatisfied( VOS_VOID );
extern VOS_UINT32 IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied( VOS_VOID );
extern VOS_UINT32 IMSA_SRV_IsEmcSrvConditonSatisfied( VOS_VOID );
/*extern VOS_VOID IMSA_CMCCDeregProc();*/
extern IMSA_NORMAL_REG_STATUS_ENUM_UINT32 IMSA_SRV_GetRegStatusFromSrvStatus
(
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
);
extern VOS_UINT32 IMSA_SRV_IsSrvStatusEqual
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatus
);
extern VOS_VOID IMSA_SRV_SndConnSetupReq
(
    VOS_UINT32                          ulReEstablishFlag,
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
);

extern VOS_VOID IMSA_SRV_SndRegRegReq
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
);

extern VOS_VOID IMSA_SRV_SndNrmRegStatusNotify
(
    const IMSA_SUBSCRIPTION_INFO_STRU  *pstSubsciptionInfo,
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNormalRegStatus
);
extern VOS_VOID IMSA_SRV_NrmRegStatusNotify
(
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNrmRegStatus
);

extern VOS_VOID IMSA_SRV_ProcConnSetupIndSucc
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
);
extern VOS_VOID IMSA_SRV_ProcConnSetupIndFail
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
);
extern VOS_VOID IMSA_SRV_ProcRegRegIndSucc
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
);
extern VOS_VOID IMSA_SRV_ProcRegRegIndFail
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
);
extern VOS_VOID IMSA_SRV_ProcEmcConnRelIndMsg
(
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
);
extern VOS_VOID IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg( VOS_VOID );
extern VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg
(
    const IMSA_CONN_MODIFY_IND_STRU    *pstConnModifyIndMsg
);
extern VOS_VOID IMSA_SRV_ProcTransToNotSupportEms( VOS_VOID );
extern VOS_VOID IMSA_SRV_UpdateRat
(
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enRat,
    VOS_UINT32                         *pulIsNotfiyNrmNoSrv,
    VOS_UINT32                         *pulIsNotfiyEmcNoSrv
);
extern VOS_VOID IMSA_SRV_UpdateImsVoPsStatus
(
    MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8      enImsVoPsInd
);
extern VOS_VOID IMSA_SRV_UpdateEmsStatus
(
    MSCC_IMSA_EMS_INDICATOR_ENUM_UINT8           enEmsInd
);
extern VOS_UINT32 IMSA_IsImsVoiceContidionSatisfied( VOS_VOID );

extern VOS_VOID IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo
(
    IMSA_IMS_INPUT_SERVICE_REASON_ENUM_UINT32   enInputServeReason
);

extern VOS_VOID IMSA_SRV_RegConningStateProcRegDeregIndMsg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);

extern VOS_UINT32 IMSA_SRV_GetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8 *penImsVoiceCap);

extern VOS_VOID IMSA_SRV_SetImsRegForbidden
(
    IMSA_REG_TYPE_ENUM_UINT8       enRegType,
    IMSA_REG_RESULT_ENUM_UINT32    enResult
);

extern VOS_VOID IMSA_StartTempForbTimer(VOS_VOID);
extern VOS_UINT32 IMSA_IsTempForbTimerRunning(VOS_VOID);

/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e961*/
/*****************************************************************************
 Function Name  : IMSA_CONTROL_InitConfigPara
 Description    : IMSA �ܿ�ģ���ʼ��������Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONTROL_InitConfigPara( VOS_VOID )
{
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara = VOS_NULL_PTR;

    pstImsaConfigPara = IMSA_GetConfigParaAddress();

    pstImsaConfigPara->ucGsmImsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucUtranImsSupportFlag        = VOS_FALSE;
    pstImsaConfigPara->ucLteImsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucGsmEmsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucUtranEmsSupportFlag        = VOS_FALSE;
    pstImsaConfigPara->ucLteEmsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucVoiceCallOnImsSupportFlag  = VOS_TRUE;
    pstImsaConfigPara->ucSmsOnImsSupportFlag        = VOS_TRUE;
    pstImsaConfigPara->ucNoCardEmcCallSupportFlag   = VOS_FALSE;
    pstImsaConfigPara->ucUeRelMediaPdpFLag          = VOS_FALSE;
    pstImsaConfigPara->ucImsLocDeregSigPdpRelFlag   = VOS_TRUE;
    pstImsaConfigPara->enVoiceDomain                = IMSA_VOICE_DOMAIN_IMS_PS_PREFERRED;
    pstImsaConfigPara->stCMCCCustomReq.ucCMCCCustomDeregFlag        = VOS_FALSE;
    pstImsaConfigPara->stCMCCCustomReq.ucCMCCCustomTcallFlag        = VOS_FALSE;
    pstImsaConfigPara->stCMCCCustomReq.ucCMCCCustomTqosFlag         = VOS_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CONTROL_InitConfigPara
 Description    : IMSA �ܿ�ģ���ʼ��������Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONTROL_InitNetworkInfo( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNetworkInfo = VOS_NULL_PTR;

    pstImsaNetworkInfo = IMSA_GetNetInfoAddress();

    pstImsaNetworkInfo->enImsaCampedRatType   = IMSA_CAMPED_RAT_TYPE_NULL;
    pstImsaNetworkInfo->enImsaImsVoPsStatus   = IMSA_IMS_VOPS_STATUS_BUTT;
    pstImsaNetworkInfo->enImsaEmsStatus       = IMSA_EMS_STAUTS_BUTT;
    pstImsaNetworkInfo->enImsaPsServiceStatus = IMSA_PS_SERVICE_STATUS_NO_SERVICE;
    pstImsaNetworkInfo->ucImsaRoamingFlg      = VOS_FALSE;
}


/*****************************************************************************
 Function Name  : IMSA_CONTROL_Init
 Description    : IMSA �ܿ�ģ��ĳ�ʼ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONTROL_Init( VOS_VOID )
{
    IMSA_CONTROL_MANAGER_STRU          *pstImsaControlManager   = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();
    pstImsaControlManager   = IMSA_GetControlManagerAddress();

    IMSA_MEM_SET_S( pstImsaControlManager,
                    sizeof(IMSA_CONTROL_MANAGER_STRU),
                    0x0,
                    sizeof(IMSA_CONTROL_MANAGER_STRU));

    pstImsaControlManager->enImsaStatus                 = IMSA_STATUS_NULL;
    pstImsaControlManager->enImsaIsimStatus             = IMSA_ISIM_STATUS_ABSENT;

    /* ��ʼ��������ʱ�� */
    pstImsaControlManager->stProtectTimer.phTimer       = VOS_NULL_PTR;
    pstImsaControlManager->stProtectTimer.ucMode        = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stProtectTimer.usName        = TI_IMSA_START_OR_STOP;
    pstImsaControlManager->stProtectTimer.ulTimerLen    = TI_IMSA_START_OR_STOP_TIMER_LEN;

    /* ��ʼ��������Ϣ */
    IMSA_CONTROL_InitConfigPara();

    /* ��ʼ��������Ϣ */
    IMSA_CONTROL_InitNetworkInfo();

    pstImsaControlManager->bitRegSuccProcTypeValid     = IMSA_OP_FALSE;
    pstImsaControlManager->enRegSuccProcType           = IMSA_MSCC_REG_PROC_BUTT;

    /* ��ʼ�������Գ���IMS����ʱ�� */
    pstImsaControlManager->stPeriodImsSrvTryTimer.phTimer   = VOS_NULL_PTR;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usName    = TI_IMSA_PERIOD_TRY_IMS_SRV;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ucMode    = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ulTimerLen= TI_IMSA_PERIOD_IMS_SRV_TRY_TIMER_LEN;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usPara    = (VOS_UINT16)IMSA_SRV_TYPE_NORMAL;

    pstImsaControlManager->stTempForbiddenTimer.phTimer     = VOS_NULL_PTR;
    pstImsaControlManager->stTempForbiddenTimer.usName      = TI_IMSA_TEMP_FORBIDDEN_TIMER;
    pstImsaControlManager->stTempForbiddenTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stTempForbiddenTimer.ulTimerLen  = LMM_Get3402TimerLen();
    pstImsaControlManager->stTempForbiddenTimer.usPara      = (VOS_UINT16)IMSA_SRV_TYPE_NORMAL;

    /* delete PeriodImsEmcSrvTryTimer */

    pstImsaControlManager->enNrmSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;
    pstImsaControlManager->enEmcSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;

    pstImsaControlManager->enDeregCause     = IMSA_SRV_DEREG_CAUSE_BUTT;
    pstImsaControlManager->ucIsImsRegForbidden = IMSA_FALSE;
    /* ��ʼ���ϴ���ͨע��״̬ */
    pstSubcriptionInfoList->enLastNrmRegStatus  = IMSA_NORMAL_REG_STATUS_DEREG;

    /* ��ʼ���ϴ���ͨATע��״̬ */
    pstSubcriptionInfoList->enLastNrmAtRegStatus  = IMSA_NORMAL_AT_REG_STATUS_DEREG;

    pstImsaControlManager->stGetSerProtectTimer.phTimer         = VOS_NULL_PTR;
    pstImsaControlManager->stGetSerProtectTimer.ucMode          = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stGetSerProtectTimer.usName          = TI_IMSA_GET_SERVICE_PROTECT_TIMER;
    pstImsaControlManager->stGetSerProtectTimer.ulTimerLen      = TI_IMSA_GET_SERVICE_PROTECT_TIMER_LEN;

    pstImsaControlManager->stDeregSerProtectTimer.phTimer       = VOS_NULL_PTR;
    pstImsaControlManager->stDeregSerProtectTimer.ucMode        = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stDeregSerProtectTimer.usName        = TI_IMSA_DEREG_SERVICE_PROTECT_TIMER;
    pstImsaControlManager->stDeregSerProtectTimer.ulTimerLen    = TI_IMSA_DEREG_SERVICE_PROTECT_TIMER_LEN;
    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CONTROL_ClearResource
 Description    : IMSA �ܿ�ģ��������Դ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CONTROL_ClearResource( VOS_VOID )
{
    IMSA_CONTROL_MANAGER_STRU          *pstImsaControlManager   = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();
    pstImsaControlManager   = IMSA_GetControlManagerAddress();

    /* ���ע��״̬�����������Ҫ�ϱ��ϲ�ע��״̬ */
    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

    pstImsaControlManager->enImsaStatus                 = IMSA_STATUS_NULL;
    pstImsaControlManager->enIsImsSrvExist              = IMSA_SRV_CONN_STATUS_ISNOT_EXIST;
    pstImsaControlManager->enStopType                   = MSCC_IMSA_STOP_TYPE_BUTT;
    /* ֹͣ������ʱ�� */
    IMSA_StopTimer(&pstImsaControlManager->stProtectTimer);
    pstImsaControlManager->stProtectTimer.phTimer       = VOS_NULL_PTR;
    pstImsaControlManager->stProtectTimer.ucMode        = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stProtectTimer.usName        = TI_IMSA_START_OR_STOP;
    pstImsaControlManager->stProtectTimer.ulTimerLen    = TI_IMSA_START_OR_STOP_TIMER_LEN;

    /* ��ʼ��������Ϣ */
    IMSA_CONTROL_InitNetworkInfo();

    /* ֹͣ�����Գ���IMS����ʱ�� */
    IMSA_StopTimer(&pstImsaControlManager->stPeriodImsSrvTryTimer);
    pstImsaControlManager->stPeriodImsSrvTryTimer.phTimer   = VOS_NULL_PTR;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usName    = TI_IMSA_PERIOD_TRY_IMS_SRV;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ucMode    = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ulTimerLen= TI_IMSA_PERIOD_IMS_SRV_TRY_TIMER_LEN;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usPara    = (VOS_UINT16)IMSA_SRV_TYPE_NORMAL;

    IMSA_StopTimer(&pstImsaControlManager->stTempForbiddenTimer);
    pstImsaControlManager->stTempForbiddenTimer.phTimer     = VOS_NULL_PTR;
    pstImsaControlManager->stTempForbiddenTimer.usName      = TI_IMSA_TEMP_FORBIDDEN_TIMER;
    pstImsaControlManager->stTempForbiddenTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stTempForbiddenTimer.ulTimerLen  = LMM_Get3402TimerLen();
    pstImsaControlManager->stTempForbiddenTimer.usPara      = (VOS_UINT16)IMSA_SRV_TYPE_NORMAL;

    /* delete PeriodImsEmcSrvTryTimer */
    pstImsaControlManager->bitRegSuccProcTypeValid     = IMSA_OP_FALSE;
    pstImsaControlManager->enRegSuccProcType           = IMSA_MSCC_REG_PROC_BUTT;

    pstImsaControlManager->enNrmSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;
    pstImsaControlManager->enEmcSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;

    pstImsaControlManager->enDeregCause     = IMSA_SRV_DEREG_CAUSE_BUTT;

    pstImsaControlManager->ucIsImsRegForbidden = IMSA_FALSE;

    IMSA_MEM_SET_S( &pstImsaControlManager->stImsaIntraMsgQueue,
                    sizeof(IMSA_INTRA_MSG_QUEUE_STRU),
                    0x0,
                    sizeof(IMSA_INTRA_MSG_QUEUE_STRU));

    /* ��ʼ���ϴ���ͨע��״̬ */
    pstSubcriptionInfoList->enLastNrmRegStatus  = IMSA_NORMAL_REG_STATUS_DEREG;

    /* ��ʼ���ϴ���ͨATע��״̬ */
    pstSubcriptionInfoList->enLastNrmAtRegStatus  = IMSA_NORMAL_AT_REG_STATUS_DEREG;

    pstImsaControlManager->stImsaCommonInfo.stImsaUeId.bitOpImpi = IMSA_OP_FALSE;

    IMSA_MEM_SET_S( &pstImsaControlManager->stImsaCommonInfo.stImsaUeId.stImpi,
                    sizeof(IMSA_IMPI_STRU),
                    0,
                    IMSA_MAX_IMPI_LEN +1);


    pstImsaControlManager->stImsaCommonInfo.stImsaUeId.bitOpTImpu = IMSA_OP_FALSE;

    IMSA_MEM_SET_S( &pstImsaControlManager->stImsaCommonInfo.stImsaUeId.stTImpu,
                    sizeof(IMSA_TIMPU_STRU),
                    0,
                    IMSA_MAX_TIMPU_LEN+1);

    pstImsaControlManager->stImsaCommonInfo.bitOpHomeNetDomainName = IMSA_OP_FALSE;

    IMSA_MEM_SET_S( &pstImsaControlManager->stImsaCommonInfo.stHomeNetDomainName,
                    sizeof(IMSA_HOME_NET_DOMAIN_NAME_STRU),
                    0,
                    IMSA_MAX_HOME_NET_DOMAIN_NAME_LEN +1);


    pstImsaControlManager->ucIsCardLocked = IMSA_FALSE;

    return ;
}


/*****************************************************************************
 Function Name  : IMSA_SRV_RatFormatTransform
 Description    : ���뼼����ʽת��
 Input          : penImsaRat------------IMSA���뼼��ָ��
                  enMmaRat--------------MMA���뼼��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_RatFormatTransform
(
    IMSA_CAMPED_RAT_TYPE_ENUM_UINT8    *penImsaRat,
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enMmaRat
)
{
    if (MSCC_IMSA_RAT_TYPE_GSM == enMmaRat)
    {
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_GSM;
    }
    else if (MSCC_IMSA_RAT_TYPE_UTRAN == enMmaRat)
    {
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_UTRAN;
    }
    else if (MSCC_IMSA_RAT_TYPE_LTE == enMmaRat)
    {
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_EUTRAN;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_SRV_RatFormatTransform:illegal rat type");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_RatFormatTransform_ENUM, LNAS_PARAM_INVALID);
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_NULL;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsCurRatSupportIms
 Description    : ��ǰ���뼼���Ƿ�֧��IMS����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsCurRatSupportIms( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara   = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();
    pstImsaConfigPara   = IMSA_GetConfigParaAddress();

    if ((IMSA_CAMPED_RAT_TYPE_GSM == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucGsmImsSupportFlag)
        && (MSCC_IMSA_ACCESS_TYPE_GERAN == pstImsaNwInfo->enAccessType))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:GSM support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportIms_ENUM, 1);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_UTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucUtranImsSupportFlag)
    /* ���ƶ���TDD�²�֧��IMS�����Բ���Ҫ�ж�UTRAN_TDD */
        && (MSCC_IMSA_ACCESS_TYPE_UTRAN_FDD == pstImsaNwInfo->enAccessType))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:UNTRAN support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportIms_ENUM, 2);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_EUTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucLteImsSupportFlag)
        && ((MSCC_IMSA_ACCESS_TYPE_EUTRAN_TDD == pstImsaNwInfo->enAccessType)
        || (MSCC_IMSA_ACCESS_TYPE_EUTRAN_FDD == pstImsaNwInfo->enAccessType)))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:LTE support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportIms_ENUM, 3);
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsCurRatSupportEms
 Description    : ��ǰ���뼼���Ƿ�֧��EMS����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsCurRatSupportEms( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara   = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();
    pstImsaConfigPara   = IMSA_GetConfigParaAddress();

    if ((IMSA_CAMPED_RAT_TYPE_GSM == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucGsmEmsSupportFlag)
        && (MSCC_IMSA_ACCESS_TYPE_GERAN == pstImsaNwInfo->enAccessType))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportEms:GSM support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportEms_ENUM, 1);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_UTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucUtranEmsSupportFlag)
    /* ���ƶ���TDD�²�֧��IMS�����Բ���Ҫ�ж�UTRAN_TDD */
        && (MSCC_IMSA_ACCESS_TYPE_UTRAN_FDD == pstImsaNwInfo->enAccessType))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:UNTRAN support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportEms_ENUM, 2);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_EUTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucLteEmsSupportFlag)
        && ((MSCC_IMSA_ACCESS_TYPE_EUTRAN_TDD == pstImsaNwInfo->enAccessType)
        || (MSCC_IMSA_ACCESS_TYPE_EUTRAN_FDD == pstImsaNwInfo->enAccessType)))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:LTE support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportEms_ENUM, 3);
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsNrmSrvIsimParaSatisfied
 Description    : ��ȡIMS��ͨ�����ISIM�����Ƿ�߱�
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsNrmSrvIsimParaSatisfied( VOS_VOID )
{
    IMSA_COMMON_INFO_STRU              *pstImsaCommonInfo = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    /* �ж�USIM��״̬�Ƿ����� */
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    if (IMSA_PS_SIMM_INVALID == pstControlMagnaer->ucImsaUsimStatus)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:USIM not available!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 1);
        return IMSA_FALSE;
    }

    if (IMSA_ISIM_STATUS_AVAILABLE != IMSA_GetIsimStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:ISIM not available!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 2);
        return IMSA_FALSE;
    }

    pstImsaCommonInfo = IMSA_GetCommonInfoAddress();
    if (IMSA_OP_TRUE != pstImsaCommonInfo->bitOpHomeNetDomainName)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:No home network domain name!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 3);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NotInitRegEventReport(IMSA_ERR_LOG_NOT_INIT_IMS_REG_REASON_DOMAIN_INVALIED);
        #endif
        return IMSA_FALSE;
    }

    if (IMSA_OP_TRUE != pstImsaCommonInfo->stImsaUeId.bitOpImpi)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:No impi!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 4);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NotInitRegEventReport(IMSA_ERR_LOG_NOT_INIT_IMS_REG_REASON_IMPI_INVALIED);
        #endif
        return IMSA_FALSE;
    }

    if (IMSA_OP_TRUE != pstImsaCommonInfo->stImsaUeId.bitOpTImpu)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:No temporary IMPU!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 5);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NotInitRegEventReport(IMSA_ERR_LOG_NOT_INIT_IMS_REG_REASON_IMPU_INVALIED);
        #endif
        return IMSA_FALSE;
    }

    if (IMSA_TRUE == pstControlMagnaer->ucIsCardLocked)
    {
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 6);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NotInitRegEventReport(IMSA_ERR_LOG_NOT_INIT_IMS_REG_REASON_USIM_LOCK);
        #endif
        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsNrmSrvConditonSatisfied
 Description    : ��ȡIMS��ͨ����������Ƿ�߱�
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
      2.wangchen 00209181    2015-06-23  Modify:volte
*****************************************************************************/
IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32 IMSA_SRV_IsNrmSrvConditonSatisfied( VOS_VOID )
{
    /* ��ǰ���뼼��֧��IMS���� */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportIms())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:cur rat not support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 1);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_RAT_NOT_SUPPORT;
    }

    if (IMSA_VOICE_DOMAIN_CS_ONLY == IMSA_GetVoiceDomain())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:voice not support!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 2);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NotInitRegEventReport(IMSA_ERR_LOG_NOT_INIT_IMS_REG_REASON_VOICE_DAOMAIN_CS_ONLY);
        #endif

        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_VOICE_NOT_SUPPORT;
    }

    if (VOS_FALSE == IMSA_GetUeImsVoiceCap())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:voice not support!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 8);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NotInitRegEventReport(IMSA_ERR_LOG_NOT_INIT_IMS_REG_REASON_UE_NOT_SUPPORT_IMS_VOICE);
        #endif

        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_VOICE_NOT_SUPPORT;
    }

    if (IMSA_IMS_VOPS_STATUS_NOT_SUPPORT == IMSA_GetNwImsVoiceCap())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:voice not support!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 8);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NotInitRegEventReport(IMSA_ERR_LOG_NOT_INIT_IMS_REG_REASON_NW_NOT_SUPPORT_VOPS);
        #endif

        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_VOICE_NOT_SUPPORT;
    }
    #if 0
    /* IMS������֧�֣��򷵻����������� */
    if ((IMSA_VOICE_DOMAIN_CS_ONLY == IMSA_GetVoiceDomain())
            || (VOS_FALSE == IMSA_GetUeImsVoiceCap())
            || (IMSA_IMS_VOPS_STATUS_NOT_SUPPORT == IMSA_GetNwImsVoiceCap()))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:voice not support!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 2);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_VOICE_NOT_SUPPORT;
    }
    #endif

    /* PS�����״̬Ϊ�������� */
    if (IMSA_PS_SERVICE_STATUS_NORMAL_SERVICE != IMSA_GetPsServiceStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:Ps service not normal!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 3);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_OTHERS;
    }


    /* ����������������£���UE����Ϊ��֧�����������µ�ע�ᣬ��ֱ���˳�������֪ͨMMA VOICE������ */
    if ((VOS_TRUE == IMSA_GetNetInfoAddress()->ucImsaRoamingFlg) &&
        (VOS_TRUE == IMSA_GetConfigParaAddress()->ucRoamingImsNotSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:Roaming and not support !");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 4);

        /* ���������²�֧�ַ���IMSע��ʱ������CHR�������ϱ� */
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NotInitRegEventReport(IMSA_ERR_LOG_NOT_INIT_IMS_REG_REASON_NOT_SUPPORT_ROAMING_REG);
        #endif

        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_ROAM_NOT_SUPPORT;
    }


    /* ��״̬Ϊ��Ч���ã���IMPI��IMPU��DOMAIN������Ч */
    if (IMSA_TRUE != IMSA_SRV_IsNrmSrvIsimParaSatisfied())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:ISIM PARA not satisfied!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 5);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_USIM_NOT_SUPPORT;
    }

    /* IMSע�ᱻ��ֹ */
    if (IMSA_TRUE == IMSA_GetIsImsRegForbidden())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:IMS reg forbidden!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 6);

        /* UE����ʱ������CHR�������ϱ� */
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NotInitRegEventReport(IMSA_ERR_LOG_NOT_INIT_IMS_REG_REASON_REG_FORBIDEN);
        #endif

        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_REG_FORBIDDEN;
    }

    /* Pnd��ʱ���ܳͷ���ʱ������ʱ����ע�ᱻ�� */
    if (VOS_TRUE == IMSA_IsTempForbTimerRunning())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:Forb Timer Running!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 7);

        /* UE����ʱ������CHR�������ϱ� */
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NotInitRegEventReport(IMSA_ERR_LOG_NOT_INIT_IMS_REG_REASON_TEMP_FORBIDEN_TIMER_RUNNING);
        #endif

        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_REG_FORBIDDEN;
    }

    return IMSA_NRM_SRV_CON_SAT_STATUE_SUCC;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied
 Description    : ��NORMAL SERVICE����������������Ƿ�߱�
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();

    /* �Ƿ���HPLMN�� */
    if (VOS_TRUE == pstImsaNwInfo->ucImsaRoamingFlg)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied:NOT HPLMN!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied_ENUM, 1);
        return IMSA_FALSE;
    }

    /* ���������Ƿ���ע��ɹ� */
    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied:normal service not reg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied_ENUM, 2);
        return IMSA_FALSE;
    }

    /* �����˽���������������֧�ֽ��������� */
    if ((IMSA_TRUE == IMSA_CONN_IsEmcPdpDefined())
        && (IMSA_EMS_STAUTS_SUPPORT == pstImsaNwInfo->enImsaEmsStatus))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied:defined emc pdp and nw support emc bearer!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied_ENUM, 3);

        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_IsEmcSrvConditonSatisfied
 Description    : ��ȡIMS��������������Ƿ�߱�
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsEmcSrvConditonSatisfied( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara   = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();
    pstImsaConfigPara   = IMSA_GetConfigParaAddress();

    /* ��ǰ���뼼��֧��IMS���� */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportIms())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:cur rat not support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 1);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CUR_RAT_NOT_SUPPORT_IMS,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* ��ǰ���뼼��֧��EMS���� */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportEms())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:cur rat not support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 2);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CUR_RAT_NOT_SUPPORT_EMC_IMS,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* UE�Ƿ�֧������ */
    if (VOS_FALSE == IMSA_GetUeImsVoiceCap())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:ue not support voice!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 3);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VOICE_CALL,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* �ܷ������������´������ */
    if (IMSA_TRUE == IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:can make emc call in normal service!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 4);
        return IMSA_TRUE;
    }

    /* �ܷ���޿������� */
    if ((IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
        && (VOS_FALSE == pstImsaConfigPara->ucNoCardEmcCallSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:not support anonymous emc call!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 5);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CANNOT_MAKE_NOCAR_EMC_CALL,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* �����Ƿ�֧�ֽ��������� */
    if (IMSA_EMS_STAUTS_NOT_SUPPORT == pstImsaNwInfo->enImsaEmsStatus)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:nw not support emc bearer!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 6);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NW_NOT_SUPPORT_EMC_BEAR,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif

        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_GetRegStatusFromSrvStatus
 Description    : ���ݷ���״̬����ȡ����ע��״̬
 Input          : enSrvStatus-----------����״̬
 Output         : VOS_VOID
 Return Value   : IMSA_NORMAL_REG_STATUS_ENUM_UINT32

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
IMSA_NORMAL_REG_STATUS_ENUM_UINT32 IMSA_SRV_GetRegStatusFromSrvStatus
(
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
)
{
    switch (enSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
        /* case IMSA_SRV_STATUS_CONNING_DEREG: */
        case IMSA_SRV_STATUS_RELEASING_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:

            return IMSA_NORMAL_REG_STATUS_DEREG;

        case IMSA_SRV_STATUS_CONN_DEREGING:

            return IMSA_NORMAL_REG_STATUS_DEREGING;

        case IMSA_SRV_STATUS_CONN_REGING:
        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONNING_REG:
            return IMSA_NORMAL_REG_STATUS_REGING;

        default:

            return IMSA_NORMAL_REG_STATUS_REG;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_GetAtRegStatusFromSrvStatus
 Description    : ���ݷ���״̬����ȡ����ATע��״̬
 Input          : enSrvStatus-----------����״̬
 Output         : VOS_VOID
 Return Value   : IMSA_NORMAL_REG_STATUS_ENUM_UINT32

 History        :
      1.leili 00132387      2013-10-14  Draft Enact
*****************************************************************************/
IMSA_NORMAL_AT_REG_STATUS_ENUM_UINT32 IMSA_SRV_GetAtRegStatusFromSrvStatus
(
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
)
{
    switch (enSrvStatus)
    {
        case IMSA_SRV_STATUS_CONNING_REG:
        case IMSA_SRV_STATUS_CONN_REG:

            return IMSA_NORMAL_AT_REG_STATUS_REG;

        default:

            return IMSA_NORMAL_AT_REG_STATUS_DEREG;
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_IsSrvStatusEqual
 Description    : �жϷ���״̬�Ƿ��������ͬ
 Input          : enConnType-------------��������
                  enTimerId--------------��ʱ������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsSrvStatusEqual
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatus
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatusTmp = IMSA_SRV_STATUS_BUTT;

    if (IMSA_SRV_TYPE_NORMAL == enSrvType)
    {
        enImsaSrvStatusTmp = IMSA_SRV_GetNormalSrvStatus();
    }
    else
    {
        enImsaSrvStatusTmp = IMSA_SRV_GetEmcSrvStatus();
    }

    if (enImsaSrvStatus == enImsaSrvStatusTmp)
    {
        return IMSA_TRUE;
    }
    else
    {
        return IMSA_FALSE;
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_SndConnSetupReq
 Description    : �����ڲ���ϢID_IMSA_CONN_SETUP_REQ
 Input          : enConnType----------------��������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndConnSetupReq
(
    VOS_UINT32                          ulReEstablishFlag,
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_CONN_SETUP_REQ_STRU           *pstConnSetupReq     = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndConnSetupReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndConnSetupReq_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstConnSetupReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_SETUP_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstConnSetupReq)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndConnSetupReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndConnSetupReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    pstControlMagnaer  = IMSA_GetControlManagerAddress();
    /* ���Ҫ����������ͨ���ӣ���ֹͣ�����Գ���IMS��ͨ����ʱ�� */
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        IMSA_StopTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
    }

    /* delete PeriodImsEmcSrvTryTimer */


    /*���*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstConnSetupReq),
                    IMSA_GET_MSG_LENGTH(pstConnSetupReq),
                    0,
                    IMSA_GET_MSG_LENGTH(pstConnSetupReq));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnSetupReq,
                                ID_IMSA_CONN_SETUP_REQ,
                                sizeof(IMSA_CONN_SETUP_REQ_STRU));

    /*��д��Ϣ����*/
    pstConnSetupReq->ulReEstablishFlag  = ulReEstablishFlag;
    pstConnSetupReq->enConnType     = enConnType;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstConnSetupReq);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SndConnRelReq
 Description    : �����ڲ���ϢID_IMSA_CONN_REL_REQ
 Input          : enConnType----------------��������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndConnRelReq
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
)
{
    IMSA_CONN_REL_REQ_STRU             *pstConnRelReq       = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndConnRelReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndConnRelReq_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstConnRelReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_REL_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstConnRelReq)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndConnSetupReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndConnRelReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstConnRelReq),
                    IMSA_GET_MSG_LENGTH(pstConnRelReq),
                    0,
                    IMSA_GET_MSG_LENGTH(pstConnRelReq));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnRelReq,
                                ID_IMSA_CONN_REL_REQ,
                                sizeof(IMSA_CONN_REL_REQ_STRU));

    /*��д��Ϣ����*/
    pstConnRelReq->enConnType       = enConnType;
    pstConnRelReq->enSipPdpType     = enSipPdpType;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstConnRelReq);
}


/*****************************************************************************
 Function Name  : IMSA_SRV_SndRegRegReq
 Description    : �����ڲ���ϢID_IMSA_REG_REG_REQ
 Input          : enRegType-----------------ע������
                  enAddrType----------------ʹ�õĵ�ַ������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndRegRegReq
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
)
{
    IMSA_REG_REG_REQ_STRU              *pstRegRegReq        = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndRegRegReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndRegRegReq_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstRegRegReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_REG_REG_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstRegRegReq)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndRegRegReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndRegRegReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /* �ر������Գ���IMS����ʱ�� */
    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        IMSA_StopTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
    }

    /* delete PeriodImsEmcSrvTryTimer */

    /*���*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstRegRegReq),
                    IMSA_GET_MSG_LENGTH(pstRegRegReq),
                    0,
                    IMSA_GET_MSG_LENGTH(pstRegRegReq));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstRegRegReq,
                                ID_IMSA_REG_REG_REQ,
                                sizeof(IMSA_REG_REG_REQ_STRU));

    /*��д��Ϣ����*/
    pstRegRegReq->enRegType     = enRegType;
    pstRegRegReq->enAddrType    = enAddrType;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstRegRegReq);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SndNrmCallSrvStatusInd
 Description    : �����ڲ���ϢID_IMSA_NRM_CALL_SRV_STATUS_IND
 Input          : enServiceStatus-----------------֪ͨCALLģ�����ͨ����״̬
                  enNoSrvCause--------------------�޷���ʱָʾԭ��ֵ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndNrmCallSrvStatusInd
(
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32       enCallSrvStatus,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32         enNoSrvCause
)
{
    IMSA_NRM_CALL_SRV_STATUS_IND_STRU    *pstNrmCallSrvStatusInd = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndNrmCallSrvStatusInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndNrmCallSrvStatusInd_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstNrmCallSrvStatusInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_NRM_CALL_SRV_STATUS_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstNrmCallSrvStatusInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndNrmCallSrvStatusInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndNrmCallSrvStatusInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstNrmCallSrvStatusInd),
                    IMSA_GET_MSG_LENGTH(pstNrmCallSrvStatusInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstNrmCallSrvStatusInd));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstNrmCallSrvStatusInd,
                                ID_IMSA_NRM_CALL_SRV_STATUS_IND,
                                sizeof(IMSA_NRM_CALL_SRV_STATUS_IND_STRU));

    /*��д��Ϣ����*/
    pstNrmCallSrvStatusInd->enCallSrvStatus = enCallSrvStatus;
    pstNrmCallSrvStatusInd->enNoSrvCause    = enNoSrvCause;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstNrmCallSrvStatusInd);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SndEmcCallSrvStatusInd
 Description    : �����ڲ���ϢID_IMSA_EMC_CALL_SRV_STATUS_IND
 Input          : enServiceStatus-----------------֪ͨCALLģ��Ľ�������״̬
                  enNoSrvCause--------------------�޷���ʱָʾԭ��ֵ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndEmcCallSrvStatusInd
(
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32       enCallSrvStatus,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32         enNoSrvCause
)
{
    IMSA_EMC_CALL_SRV_STATUS_IND_STRU     *pstEmcCallSrvStatusInd = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndEmcCallSrvStatusInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndEmcCallSrvStatusInd_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstEmcCallSrvStatusInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_EMC_CALL_SRV_STATUS_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstEmcCallSrvStatusInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndEmcCallSrvStatusInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndEmcCallSrvStatusInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstEmcCallSrvStatusInd),
                    IMSA_GET_MSG_LENGTH(pstEmcCallSrvStatusInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstEmcCallSrvStatusInd));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstEmcCallSrvStatusInd,
                                ID_IMSA_EMC_CALL_SRV_STATUS_IND,
                                sizeof(IMSA_EMC_CALL_SRV_STATUS_IND_STRU));

    /*��д��Ϣ����*/
    pstEmcCallSrvStatusInd->enCallSrvStatus = enCallSrvStatus;
    pstEmcCallSrvStatusInd->enNoSrvCause    = enNoSrvCause;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstEmcCallSrvStatusInd);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SndRegDeregReq
 Description    : �����ڲ���ϢID_IMSA_REG_DEREG_REQ
 Input          : enDeRegType-----------------ȥע������
                  ulLocalFlag-----------------����ȥע���ʶ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndRegDeregReq
(
    IMSA_REG_TYPE_ENUM_UINT8            enDeRegType,
    VOS_UINT32                          ulLocalFlag
)
{
    IMSA_REG_DEREG_REQ_STRU            *pstRegDeregReq  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndRegDeregReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndRegDeregReq_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstRegDeregReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_REG_DEREG_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstRegDeregReq)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndRegRegReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndRegDeregReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstRegDeregReq),
                    IMSA_GET_MSG_LENGTH(pstRegDeregReq),
                    0,
                    IMSA_GET_MSG_LENGTH(pstRegDeregReq));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstRegDeregReq,
                                ID_IMSA_REG_DEREG_REQ,
                                sizeof(IMSA_REG_DEREG_REQ_STRU));

    /*��д��Ϣ����*/
    pstRegDeregReq->enDeRegType   = enDeRegType;
    pstRegDeregReq->ulLocalFlag   = ulLocalFlag;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstRegDeregReq);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SndNrmRegStatusNotify
 Description    : �����ڲ���ϢID_IMSA_NORMAL_REG_STATUS_NOTIFY
 Input          : pstSubsciptionInfo-----------------������Ϣָ��
                  enNormalRegStatus------------------��ͨע��״̬
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SndNrmRegStatusNotify
(
    const IMSA_SUBSCRIPTION_INFO_STRU  *pstSubsciptionInfo,
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNormalRegStatus
)
{
    IMSA_NORMAL_REG_STATUS_NOTIFY_STRU     *pstNrmRegStatusNotify = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndNrmRegStatusNotify is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndNrmRegStatusNotify_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstNrmRegStatusNotify = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NORMAL_REG_STATUS_NOTIFY_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstNrmRegStatusNotify)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndNrmRegStatusNotify:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndNrmRegStatusNotify_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstNrmRegStatusNotify),
                    IMSA_GET_MSG_LENGTH(pstNrmRegStatusNotify),
                    0,
                    IMSA_GET_MSG_LENGTH(pstNrmRegStatusNotify));

    /*��д��Ϣͷ*/
    pstNrmRegStatusNotify->ulMsgId          = ID_IMSA_NORMAL_REG_STATUS_NOTIFY;
    pstNrmRegStatusNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNrmRegStatusNotify->ulSenderPid      = PS_PID_IMSA;
    pstNrmRegStatusNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNrmRegStatusNotify->ulReceiverPid    = pstSubsciptionInfo->ulPid;

    /* ��д��Ϣ���� */
    pstNrmRegStatusNotify->enNormalRegStatus= enNormalRegStatus;
    pstNrmRegStatusNotify->ulPara           = pstSubsciptionInfo->ulPara;
    pstNrmRegStatusNotify->ulSubscriptionId = pstSubsciptionInfo->ulSubscriptionId;

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstNrmRegStatusNotify);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_NrmRegStatusNotify
 Description    : �����µ���ͨע��״̬֪ͨ����ģ��
 Input          : enNrmRegStatus-------------��ͨע��״̬
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_NrmRegStatusNotify
(
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNrmRegStatus
)
{
    VOS_UINT32                          i                       = IMSA_NULL;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_STRU        *pstSubcriptionInfo      = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_NrmRegStatusNotify is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_NrmRegStatusNotify_ENUM, LNAS_ENTRY);

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();

    for (i = 0; i < pstSubcriptionInfoList->ulSubscriptionNum; i++)
    {
        pstSubcriptionInfo = &pstSubcriptionInfoList->astSubcriptionInfoArray[i];
        if (IMSA_SUBCRIBE_TYPE_NORMAL_REG == pstSubcriptionInfo->enType)
        {
            IMSA_SRV_SndNrmRegStatusNotify(pstSubcriptionInfo, enNrmRegStatus);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_GetImsVoiceCapability
 Description    : ȡ��IMS VOICE�������û򲻿���
 Input          : penImsVoiceCap-------------IMS VOICE����
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-04-13  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_GetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8 *penImsVoiceCap)
{
    VOS_UINT32                    ulResult           = IMSA_FALSE;
    IMSA_CONTROL_MANAGER_STRU     *pstControlMagnaer = VOS_NULL_PTR;

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
            if (VOS_FALSE == IMSA_IsTimerRunning(&pstControlMagnaer->stPeriodImsSrvTryTimer))
            {
                *penImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE;
                ulResult = IMSA_TRUE;
            }
            break;
        case IMSA_SRV_STATUS_CONN_REG:
            if (IMSA_TRUE == IMSA_IsImsVoiceContidionSatisfied())
            {
                *penImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE;
            }
            else
            {
                *penImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE;
            }
            ulResult = IMSA_TRUE;
            break;
        case IMSA_SRV_STATUS_CONN_DEREG:
            *penImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE;
            ulResult = IMSA_TRUE;
            break;

        default:
            break;
    }

    return ulResult;
}


/*****************************************************************************
 Function Name  : IMSA_SRV_SetServcieStatus
 Description    : ���÷���״̬
 Input          : enSrvType-------------��������
                  enSrvStatus-----------����״̬
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SetServcieStatus
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
)
{
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNrmRegStatus = IMSA_NORMAL_REG_STATUS_BUTT;
    IMSA_NORMAL_AT_REG_STATUS_ENUM_UINT32 enNrmAtRegStatus = IMSA_NORMAL_AT_REG_STATUS_BUTT;
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8  enImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_BUTT;

    /* ��ȡ����ԭ״̬ */

    /* ��ӡ�������� */

    /* ��ӡ����״̬�������Ϣ */

    if (IMSA_SRV_TYPE_EMC == enSrvType)
    {
        IMSA_SRV_GetEmcSrvStatus() = enSrvStatus;

        /* ���ȡ��IMS VOICE���������ϱ�IMS VOICE���� */
        if (IMSA_TRUE == IMSA_SRV_GetImsVoiceCapability(&enImsVoiceCap))
        {
            IMSA_SndMsccMsgImsVoiceCapNotify(enImsVoiceCap, IMSA_CONN_IsExitPersistentBearer());
        }
        return ;
    }

    /* ���ݷ���״̬����ȡ��ͨע��״̬ */
    enNrmRegStatus = IMSA_SRV_GetRegStatusFromSrvStatus(enSrvStatus);

    /* �����ͨע��״̬�����������֪ͨǩԼ��ģ�����µ���ͨע��״̬ */
    if (enNrmRegStatus != IMSA_GetLastNrmRegStatus())
    {
        IMSA_SRV_NrmRegStatusNotify(enNrmRegStatus);

        IMSA_SetLastNrmRegStatus(enNrmRegStatus);
    }

    /* ���ݷ���״̬����ȡ��ͨATע��״̬ */
    enNrmAtRegStatus = IMSA_SRV_GetAtRegStatusFromSrvStatus(enSrvStatus);

    IMSA_INFO_LOG2("IMSA_SRV_SetServcieStatus:enNrmAtRegStatus = ,IMSA_GetLastNrmAtRegStatus()=",
                   enNrmAtRegStatus,IMSA_GetLastNrmAtRegStatus());
    TLPS_PRINT2LAYER_INFO2(IMSA_SRV_SetServcieStatus_ENUM, 1, enNrmAtRegStatus, IMSA_GetLastNrmAtRegStatus());

    /* �����ͨATע��״̬�����������֪ͨAT���µ���ͨATע��״̬ */
    if (enNrmAtRegStatus != IMSA_GetLastNrmAtRegStatus())
    {
        IMSA_SndMsgAtCireguInd(enNrmAtRegStatus);

        IMSA_SetLastNrmAtRegStatus(enNrmAtRegStatus);
    }

    IMSA_SRV_GetNormalSrvStatus() = enSrvStatus;

    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        /* SRVCC�쳣(����ػ���DEREG REQ��״̬Ǩ��CONN+REG)���建�� */
        IMSA_SrvccAbormalClearBuff(IMSA_SRVCC_ABNORMAL_STATUS_CHANGE);

        IMSA_SMS_ClearResource();

        IMSA_USSD_ClearResource();
    }

    /* ���ȡ��IMS VOICE���������ϱ�IMS VOICE���� */
    if (IMSA_TRUE == IMSA_SRV_GetImsVoiceCapability(&enImsVoiceCap))
    {
        IMSA_SndMsccMsgImsVoiceCapNotify(enImsVoiceCap, IMSA_CONN_IsExitPersistentBearer());
    }

}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnSetupIndSucc
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_SETUP_IND�����������ӽ����ɹ�
 Input          : pstConnSetupIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:emc dedicated
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcConnSetupIndSucc
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
)
{
    IMSA_CONTROL_MANAGER_STRU              *pstImsaControlManager   = VOS_NULL_PTR;
    VOS_CHAR                                acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                                acPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    IMSA_INFO_LOG("IMSA_SRV_ProcConnSetupIndSucc is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnSetupIndSucc_ENUM, LNAS_ENTRY);

    pstImsaControlManager = IMSA_GetControlManagerAddress();

    /* ��CALL�ķ���״̬���������֪ͨCALL;�����ǰ���뼼����֧��IMS�������޷���
       ��ǰ���뼼��֧��IMSʱ�������������ж�:
       CONN REG�з���CONN DEREG���Ƿ����޿�
    ������޿������з��񣬷������޷������������޷���,CALLģ���յ��޷�����Ҫ�ͷ�
    CALL��*/

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnSetupIndMsg->enSipPdpType)
    {
        /* ֪ͨCALLģ������Ѿ��߱� */
        IMSA_ProcCallResourceIsReady(pstConnSetupIndMsg->enConnType, pstConnSetupIndMsg->enMediaPdpType);
        return ;
    }

    if (IMSA_CONN_TYPE_NORMAL == pstConnSetupIndMsg->enConnType)
    {
        IMSA_UtilStrNCpy(acUeAddr, pstImsaControlManager->stNrmRegParaInfo.acUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
        IMSA_UtilStrNCpy(acPcscfAddr, pstImsaControlManager->stNrmRegParaInfo.acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);
    }
    else
    {
        IMSA_UtilStrNCpy(acUeAddr, pstImsaControlManager->stEmcRegParaInfo.acUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
        IMSA_UtilStrNCpy(acPcscfAddr, pstImsaControlManager->stEmcRegParaInfo.acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);
    }
    /* �����ǰ����REG+CONNING״̬ */
    if (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                    IMSA_SRV_STATUS_CONNING_REG))
    {
        /* CRˢ�� Issue A+Issue B+Issue C+Issue D: When the PDP context used for SIP signalling (EPS bearer context
           used for SIP signalling) is deactivated by procedures not triggered by UE and either the network requests
           reactivation or the UE desires or is required to be registered, then the UE performs the same procedures
           as at initially ensuring the PDP context used for SIP signalling (EPS bearer context used for SIP signalling).
           If the operation is successful, then the UE performs a new initial registration. */
        /* ������ݵ�ע�������Ч����ʹ�õ�ǰ��ַע�� */
        if (IMSA_TRUE == IMSA_IsRegParaAvailable((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                  acUeAddr,
                                                  acPcscfAddr))
        {
            /* Current��ַ����ȥ�����������ʱ�Ѿ������, ���Դ�ʱ��Ҫ�������� */
            (VOS_VOID)IMSA_SetCurrentPara(pstConnSetupIndMsg->enConnType, acUeAddr, acPcscfAddr);

            IMSA_SRV_SetServcieStatus((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegDeregReq((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_REG_ADDR_PARAM_SAME);
        }
        else
        /* ������ݵ�ע�������Ч���򽫱���ȥע�ᣬ����֪ͨREGģ�����·���ע�� */
        {
            IMSA_SRV_SetServcieStatus((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegDeregReq((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_REG_ADDR_PARAM_NEW);


        }

        /* ����CONNING+REG̬ʱ��IMSA��Ҫ֪ͨIMS������ */
        if (IMSA_CONN_TYPE_NORMAL == pstConnSetupIndMsg->enConnType)
        {
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_SRV_InitDeregEventReport(IMSA_ERR_LOG_INIT_DEREG_REASON_PDN_LOST);

            /* ��¼����ע���ʱ�� */
            ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStopConnTimerAddr()->ul32KTStampHighBit),
                                                &(IMSA_GetErrlogStopConnTimerAddr()->ul32KTStampLowBit));

            /* ��¼UE����ע���ʱ�� */
            ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampHighBit),
                                                &(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampLowBit));

            /* ���ؽ���ʱ��������ֵ�жϼ��ϱ� */
            IMSA_PdnConnTimerExpireEventReport();
            #endif
        }
        else
        {
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV);
        }

        return;
    }

    /* ������ؼ���ɹ���֧ */

    /* �������CONNING&DEREG̬����ֱ���˳� */
    if (IMSA_TRUE != IMSA_SRV_IsSrvStatusEqual( (IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                IMSA_SRV_STATUS_CONNING_DEREG))
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcConnSetupIndSucc:SRV status is not conningdereg!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcConnSetupIndSucc_ENUM, IMSA_STATE_ERROR);
        return ;
    }

    if (IMSA_CONN_TYPE_EMC == pstConnSetupIndMsg->enConnType)
    {
        /* ������޿�����������ת��CONN&DEREG̬�����ٷ���ע�ᣬ֪ͨCALL����
           ����߱�;����ת��CONN&REGING̬������REGģ�鷢�����ע�� */
        if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
        {
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREG);

            /* �޿��������������ע�ᣬ���֪ͨCALLģ��������з���߱� */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_BUTT);
        }
        else
        {
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegRegReq(IMSA_REG_TYPE_EMC, IMSA_REG_ADDR_PARAM_NEW);
        }
    }
    else
    {
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REGING);

        IMSA_SRV_SndRegRegReq(IMSA_REG_TYPE_NORMAL, IMSA_REG_ADDR_PARAM_NEW);
            /* ��¼UE�����ɹ���ʱ�� */
            #if (FEATURE_ON == FEATURE_PTM)
            ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStopConnTimerAddr()->ul32KTStampHighBit),
                                                &(IMSA_GetErrlogStopConnTimerAddr()->ul32KTStampLowBit));

            /* ��¼UE����ע���ʱ�� */
            ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampHighBit),
                                                &(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampLowBit));

            /* ���ؽ���ʱ��������ֵ�жϼ��ϱ� */
            IMSA_PdnConnTimerExpireEventReport();
            #endif
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnSetupIndFail
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_SETUP_IND�����������ӽ���ʧ��
 Input          : pstConnSetupIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcConnSetupIndFail
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcConnSetupIndFail is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnSetupIndFail_ENUM, LNAS_ENTRY);

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnSetupIndMsg->enSipPdpType)
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcConnSetupIndFail:can not happen when nw initiate pdp activation!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcConnSetupIndFail_ENUM, 2);
        return ;
    }

    /* ������ؼ���ʧ�ܷ�֧ */
    /* �ؽ������̴���REG+CONNING״̬ */
    if ((IMSA_CONN_TYPE_NORMAL == pstConnSetupIndMsg->enConnType)
        && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_NORMAL,
                                                   IMSA_SRV_STATUS_CONNING_REG)))
    {
        /* ����ȥע�� */
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        if (IMSA_CONN_RESULT_FAIL_PERM_FORBIDDEN == pstConnSetupIndMsg->enResult)
        {
            /* ���ñ��ܱ�־���� */
            IMSA_SetIsImsRegForbidden(IMSA_TRUE);
        }
        else if (IMSA_CONN_RESULT_FAIL_TEMP_FORBIDDEN == pstConnSetupIndMsg->enResult)
        {
            /* ������ʱ���ܳͷ���ʱ�� */
            IMSA_StartTempForbTimer();
        }
        else
        {
            /* ���������Գ��Զ�ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
        }

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif
        return;
    }

    if ((IMSA_CONN_TYPE_EMC == pstConnSetupIndMsg->enConnType)
        && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_EMC,
                                                   IMSA_SRV_STATUS_CONNING_REG)))
    {
        /* ����ȥע�� */
        IMSA_SRV_SndRegDeregReq(IMSA_SRV_TYPE_EMC, IMSA_DEREG_LOCAL);
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

        return;
    }

    /* �������CONNING&DEREG̬����ֱ���˳� */
    if (IMSA_TRUE != IMSA_SRV_IsSrvStatusEqual( (IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                IMSA_SRV_STATUS_CONNING_DEREG))
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcConnSetupIndFail:SRV status is not conningdereg!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcConnSetupIndFail_ENUM, IMSA_STATE_ERROR);
        return ;
    }

    if (IMSA_CONN_TYPE_EMC == pstConnSetupIndMsg->enConnType)
    {
        /* ״̬ת��IDLE&DEREG̬��֪ͨCALL�������񲻾߱� */
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

        /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);
    }
    else
    {
        if ((IMSA_CONN_RESULT_FAIL_TIMER_EXP == pstConnSetupIndMsg->enResult)
            || (IMSA_CONN_RESULT_FAIL_CONN_RELEASING == pstConnSetupIndMsg->enResult)
            || (IMSA_CONN_RESULT_FAIL_SAME_APN_OPERATING == pstConnSetupIndMsg->enResult))
        {
            /* ���������Գ���IMS����ʱ�� */
            IMSA_INFO_LOG("IMSA_SRV_ProcConnSetupIndFail:start period ims service tyr timer!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnSetupIndFail_ENUM, 4);
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
        }

        if (IMSA_CONN_RESULT_FAIL_PERM_FORBIDDEN == pstConnSetupIndMsg->enResult)
        {
            /* ���ñ��ܱ�־���� */
            IMSA_SetIsImsRegForbidden(IMSA_TRUE);
        }

        if (IMSA_CONN_RESULT_FAIL_TEMP_FORBIDDEN == pstConnSetupIndMsg->enResult)
        {
            /* ������ʱ���ܳͷ���ʱ�� */
            IMSA_StartTempForbTimer();
        }

        /* ״̬ת��IDLE&DEREG̬��֪ͨCALL�������񲻾߱�������IMSA_SRV_SetServcieStatus
           �л��õ������Գ���IMS����ʱ��������������ҵ�ǰ����ע������У�
           ������Ҫ��������ʱ����ת״̬ */
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegRegIndSucc
 Description    : IMSA�ڲ���ϢID_IMSA_REG_REG_IND��������ע��ɹ�
 Input          : pstRegRegIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
      2.wangchen 00209181    2015-11-20  Modify:dsds
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegRegIndSucc
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU              *pstImsaControlManager   = IMSA_GetControlManagerAddress();
    #endif

    IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndSucc is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndSucc_ENUM, LNAS_ENTRY);

    /* ���������������״̬ת��CONN&REG̬��֪ͨCALLģ����������߱� */
    if (IMSA_REG_TYPE_NORMAL == pstRegRegIndMsg->enRegType)
    {
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REG);

        /* ֪ͨCALLģ����ͨ���з�������з���״̬ */
        IMSA_SRV_SndNrmCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_BUTT);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstImsaControlManager->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif

        /* ��¼UEע��ɹ���ʱ�� */
        #if (FEATURE_ON == FEATURE_PTM)
        ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStopRegTimerAddr()->ul32KTStampHighBit),
                                            &(IMSA_GetErrlogStopRegTimerAddr()->ul32KTStampLowBit));

        /* ע��ʱ��������ֵ�жϼ��ϱ� */
        IMSA_RegTimerExpireEventReport();

        /* ע��ɹ��¼��ϱ� */
        IMSA_SRV_RegSuccEventReport();
        #endif
    }
    else
    {
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_REG);

        /* ֪ͨCALLģ��������з�������з���״̬ */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_BUTT);
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_SetImsRegForbidden
 Description    : ����IMSע���ֹ��ʶ
 Input          : enRegType--------------ע������
                  enResult---------------ע����
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-11-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_SetImsRegForbidden
(
    IMSA_REG_TYPE_ENUM_UINT8       enRegType,
    IMSA_REG_RESULT_ENUM_UINT32    enResult
)
{
    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        if (IMSA_REG_RESULT_FAIL_FORBIDDEN == enResult)
        {
            IMSA_SetIsImsRegForbidden(IMSA_TRUE);
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegRegIndFail
 Description    : IMSA�ڲ���ϢID_IMSA_REG_REG_IND��������ע��ʧ��
 Input          : pstRegRegIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-08  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegRegIndFail
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU              *pstImsaControlManager   = IMSA_GetControlManagerAddress();
    #endif

    IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndFail is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndFail_ENUM, LNAS_ENTRY);

    switch (pstRegRegIndMsg->enResultAction)
    {
        case IMSA_RESULT_ACTION_NULL:

            IMSA_SRV_SetImsRegForbidden(pstRegRegIndMsg->enRegType,pstRegRegIndMsg->enResult);

            if (IMSA_REG_TYPE_EMC == pstRegRegIndMsg->enRegType)
            {
                /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
                IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                                IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
            }
            else
            {
                /* ֻ����ͨ���͵���Ҫ������Դȥע�ᣬ�����Ĳ���Ҫ��Ҳ����Ҫ�޸���Դ���� */
                /* ʹ��ע�����Դ */
                #if (FEATURE_ON == FEATURE_DSDS)
                if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
                {
                    IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG, RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

                    /* �޸���Դ�Ĵ���Ŀ��*/
                    IMSA_StopTimer(&pstImsaControlManager->stGetSerProtectTimer);
                    IMSA_StartTimer(&pstImsaControlManager->stDeregSerProtectTimer);
                }
                #endif
            }

            IMSA_SRV_SndConnRelReq((IMSA_CONN_TYPE_ENUM_UINT32)pstRegRegIndMsg->enRegType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            /* ��������ע�ᣬ���ͷ����ӣ�״̬ת��RELEASING&DEREG̬ */
            IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                        IMSA_SRV_STATUS_RELEASING_DEREG);
            break;
        case IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR:

            IMSA_SRV_SndRegRegReq(pstRegRegIndMsg->enRegType, IMSA_REG_ADDR_PARAM_NEW);
            break;
        case IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR:

            IMSA_SRV_SndRegRegReq(pstRegRegIndMsg->enRegType, IMSA_REG_ADDR_PARAM_SAME);
            break;
        case IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR:

            IMSA_SRV_SndRegRegReq(pstRegRegIndMsg->enRegType, IMSA_REG_ADDR_PARAM_NEXT);
            break;
        case IMSA_RESULT_ACTION_REG_LOCAL_DEREG:
            IMSA_SRV_SetServcieStatus((IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                       IMSA_SRV_STATUS_CONN_DEREG);

            /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
            IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                          IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                          IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

            if (IMSA_REG_TYPE_NORMAL == pstRegRegIndMsg->enRegType)
            {
                #if (FEATURE_ON == FEATURE_DSDS)
                if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
                {
                    IMSA_StopTimer(&pstImsaControlManager->stGetSerProtectTimer);
                    IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
                }
                #endif
            }

            break;
        /* ֻ����ͨ���͵�ע��ʧ�ܣ��Ż����÷�֧��ע��ʧ�ܣ�retry after��ʱ��������Դʧ��*/
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESULT_ACTION_REG_NORF:
            IMSA_SRV_SetServcieStatus((IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                       IMSA_SRV_STATUS_CONN_DEREG);

            /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
            IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                          IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                          IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

            IMSA_StopTimer(&pstImsaControlManager->stGetSerProtectTimer);

            /* ֪ͨRRMģ�飬��ע������ҵ�RRM������ */
            IMSA_DsdsProcResourceRegisterInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                             IMSA_RF_RES_APPLY_TRIGER_SRC_REG_RETRY_EXP,
                                             IMSA_REG_ADDR_PARAM_SAME);
            break;
        #endif
        default:

            IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndFail:illegal result action!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndFail_ENUM, LNAS_PARAM_INVALID);

            if (IMSA_REG_TYPE_EMC == pstRegRegIndMsg->enRegType)
            {
                /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
                IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                                IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
            }
            else
            {
                #if (FEATURE_ON == FEATURE_DSDS)
                if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
                {
                    IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG, RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

                    /* �޸���Դ�Ĵ���Ŀ��*/
                    IMSA_StopTimer(&pstImsaControlManager->stGetSerProtectTimer);
                    IMSA_StartTimer(&pstImsaControlManager->stDeregSerProtectTimer);
                }
                #endif
            }

            /* ��������ע�ᣬ���ͷ����ӣ�״̬ת��RELEASING&DEREG̬ */
            IMSA_SRV_SndConnRelReq((IMSA_CONN_TYPE_ENUM_UINT32)pstRegRegIndMsg->enRegType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                        IMSA_SRV_STATUS_RELEASING_DEREG);
            break;
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegRegIndMsg
 Description    : IMSA�ڲ���ϢID_IMSA_REG_REG_IND������
 Input          : pstRegRegIndMsg------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegRegIndMsg
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndMsg_ENUM, LNAS_ENTRY);

    /* �������CONN&REGING̬����ֱ���˳� */
    if (IMSA_TRUE != IMSA_SRV_IsSrvStatusEqual(     (IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                                    IMSA_SRV_STATUS_CONN_REGING))
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcRegRegIndMsg:Not conn&reging state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcRegRegIndMsg_ENUM, IMSA_STATE_ERROR);

        return ;
    }

    if (IMSA_REG_RESULT_SUCCESS == pstRegRegIndMsg->enResult)
    {
        IMSA_SRV_ProcRegRegIndSucc(pstRegRegIndMsg);
    }
    else
    {
        IMSA_SRV_ProcRegRegIndFail(pstRegRegIndMsg);
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_RegConningStateProcRegDeregIndMsg
 Description    : REG+CONNING״̬�£�IMSA�ڲ���ϢID_IMSA_REG_DEREG_IND������
 Input          : enRegType--------------ע������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2014-3-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_RegConningStateProcRegDeregIndMsg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstImsaControlManager   = VOS_NULL_PTR;

    pstImsaControlManager   = IMSA_GetControlManagerAddress();

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        /* �������Գ��Զ�ʱ����ʱ */
        if (VOS_TRUE == IMSA_IsTimerRunning(&pstImsaControlManager->stPeriodImsSrvTryTimer))
        {
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_IDLE_DEREG);
        }
        else
        {
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
        }
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

        return;
    }
    /* ����ע�� */
    if (IMSA_REG_TYPE_EMC == enRegType)
    {
        /* delete PeriodImsEmcSrvTryTimer */
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                    IMSA_SRV_STATUS_CONNING_DEREG);

        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV);

        return;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegDeregIndWithNextAddr
 Description    : IMSA�ڲ���ϢID_IMSA_REG_DEREG_IND������
 Input          : pstRegDeregIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegDeregIndWithAddr
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    VOS_UINT32                          ulPara
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    IMSA_SRV_SetServcieStatus(  enSrvType,
                                IMSA_SRV_STATUS_CONN_REGING);

    /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
    IMSA_SRV_SndCallSrvStatusInd( enSrvType,
                                  IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                  IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            /* ���г�ʼע�ᣬʹ�õ�һ����ַ�ԣ�״̬ת��CONN&REGING̬ */
            IMSA_SRV_SndRegRegReq(      enSrvType,
                                        ulPara);

            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_WAIT_STATUS_IND:
            /* �ϱ�voice������ */
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());
            break;

        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_REREGISTER_FAIL,
                                          ulPara,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_REREGISTER_FAIL,
                                          ulPara,
                                          IMSA_FALSE);

            IMSA_SRV_SndRegRegReq(  enSrvType,
                                    ulPara);

            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }

            break;

        case IMSA_RESOURCE_STATUS_APPLYING:
            break;
        #endif
        default:
            /* ���г�ʼע�ᣬʹ�õ�һ����ַ�ԣ�״̬ת��CONN&REGING̬ */
            IMSA_SRV_SndRegRegReq(      enSrvType,
                                        ulPara);

            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
    }
    #if (FEATURE_ON == FEATURE_PTM)
    /* ��¼UE����ע���ʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampHighBit),
                                        &(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampLowBit));

    #endif
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegDeregIndWithNextAddr
 Description    : IMSA�ڲ���ϢID_IMSA_REG_DEREG_IND������
 Input          : pstRegDeregIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegDeregIndActionNull
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    IMSA_SRV_SetServcieStatus(  enSrvType,
                                IMSA_SRV_STATUS_RELEASING_DEREG);

    /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
    IMSA_SRV_SndCallSrvStatusInd( enSrvType,
                                  IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                  IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

    if (IMSA_SRV_TYPE_EMC == enSrvType)
    {
        /* GCF 19.5.10�������������Ҷϣ�IMS����ע�ᳬʱ���ϱ������û�ע����
           IMSA�յ����������ͷŽ���PDN���ӣ�״̬Ǩ����CONN+DEREG */
        /* IMSA_SRV_SndConnRelReq(enSrvType,
                                IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        IMSA_SRV_SetServcieStatus(  enSrvType,
                                    IMSA_SRV_STATUS_IDLE_DEREG); */
        IMSA_SRV_SetServcieStatus(  enSrvType,
                                    IMSA_SRV_STATUS_CONN_DEREG);
        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            IMSA_SRV_SndConnRelReq(enSrvType,
                                   IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);

            IMSA_SRV_SndConnRelReq(enSrvType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;

        case IMSA_RESOURCE_STATUS_APPLYING:
            /* �޸�ԭ��ֵ */
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            break;
        #endif
        default:
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            IMSA_SRV_SndConnRelReq(enSrvType,
                                   IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            break;
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegDeregIndWithNextAddr
 Description    : IMSA�ڲ���ϢID_IMSA_REG_DEREG_IND������
 Input          : pstRegDeregIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegDeregIndConnDereging
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    IMSA_SRV_SetServcieStatus(enSrvType,
                              IMSA_SRV_STATUS_RELEASING_DEREG);

    IMSA_SRV_SndCallSrvStatusInd(enSrvType,
                                IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

    /* ����ǽ������ͣ���ֱ��֪ͨ����ģ���ͷų��� */
    if (IMSA_SRV_TYPE_EMC == enSrvType)
    {
        IMSA_SRV_SndConnRelReq(enSrvType,
                                IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
         case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndConnRelReq(enSrvType,
                                   IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            /* ��ʱ�����и�ԭ��ֵ */
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);

            IMSA_SRV_SndConnRelReq(enSrvType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;

        case IMSA_RESOURCE_STATUS_APPLYING:
            /* �޸�ԭ��ֵ */
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            break;
        #endif
        default:
            IMSA_SRV_SndConnRelReq(enSrvType,
                                   IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcRegDeregIndMsg
 Description    : IMSA�ڲ���ϢID_IMSA_REG_DEREG_IND������
 Input          : pstRegDeregIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
      2.wangchen 00209181    2015-11-30  Modify:volte dsds
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcRegDeregIndMsg
(
    const IMSA_REG_DEREG_IND_STRU      *pstRegDeregIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcRegDeregIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegDeregIndMsg_ENUM, LNAS_ENTRY);

    /* �����CONN&DEREGING״̬���������ͷ����ӣ�״̬ת��RELEASING&DEREG̬ */
    if (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual((    IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                                    IMSA_SRV_STATUS_CONN_DEREGING))
    {
        /* Ŀǰֻ��MMA DEREG REG���µ�ȥע�����ͣ������������������͵�ȥע�ᣬ
           �˴���Ҫ���ӿ��� */
        IMSA_SRV_ProcRegDeregIndConnDereging((    IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType);

        return ;
    }

    /* �����CONNING&REG״̬���򱾵�ȥע�ᣬ״̬�޸�ΪCONNING&DEREG״̬ */
    if (((IMSA_REG_TYPE_NORMAL == pstRegDeregIndMsg->enRegType)
            && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_NORMAL,IMSA_SRV_STATUS_CONNING_REG)))
        ||((IMSA_REG_TYPE_EMC == pstRegDeregIndMsg->enRegType)
            && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_EMC,IMSA_SRV_STATUS_CONNING_REG))))
    {
        IMSA_SRV_RegConningStateProcRegDeregIndMsg(pstRegDeregIndMsg->enRegType);

        return;
    }

    if (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual((    IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                                    IMSA_SRV_STATUS_CONN_REG))
    {
        switch (pstRegDeregIndMsg->enResultAction)
        {
            case IMSA_RESULT_ACTION_NULL:


                IMSA_SRV_SetImsRegForbidden(pstRegDeregIndMsg->enRegType, pstRegDeregIndMsg->enResult);
                IMSA_SRV_ProcRegDeregIndActionNull((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType);
                break;
            case IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR:

                IMSA_SRV_ProcRegDeregIndWithAddr((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType, IMSA_REG_ADDR_PARAM_NEW);

                break;
            case IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR:

                IMSA_SRV_ProcRegDeregIndWithAddr((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                                   IMSA_REG_ADDR_PARAM_SAME);

                break;
            case IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR:

                IMSA_SRV_ProcRegDeregIndWithAddr((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                                   IMSA_REG_ADDR_PARAM_NEXT);

                break;
            case IMSA_RESULT_ACTION_REG_LOCAL_DEREG:
                IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                            IMSA_SRV_STATUS_CONN_DEREG);

                /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
                IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                              IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                              IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

                break;
            case IMSA_RESULT_ACTION_WAIT_RETRY_TIME_OUT:

                IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                            IMSA_SRV_STATUS_CONN_REGING);

                /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
                IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                              IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                              IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
                break;
            default:

                IMSA_INFO_LOG("IMSA_SRV_ProcRegDeregIndMsg:illegal result action!");
                TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegDeregIndMsg_ENUM, LNAS_PARAM_INVALID);

                IMSA_SRV_ProcRegDeregIndActionNull((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType);

                break;
        }
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnSetupIndMsg
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_SETUP_IND������
 Input          : pstConnSetupIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcConnSetupIndMsg
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
)
{
    if (IMSA_CONN_RESULT_SUCCESS == pstConnSetupIndMsg->enResult)
    {
        IMSA_SRV_ProcConnSetupIndSucc(pstConnSetupIndMsg);
    }
    else
    {
        IMSA_SRV_ProcConnSetupIndFail(pstConnSetupIndMsg);
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcEmcConnRelIndMsg
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_REL_IND������,��������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:Emc dedicated
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcEmcConnRelIndMsg
(
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;

    pstControlManager = IMSA_GetControlManagerAddress();

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == enSipPdpType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcEmcConnRelIndMsg:emc dedicated release!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcEmcConnRelIndMsg_ENUM, 1);

        /* ֪ͨCALLģ��ý������ͷ� */
        IMSA_ProcCallResourceIsNotReady(IMSA_CONN_TYPE_EMC);

        /* ����IR92�����������ͷų��غ�Ӧ��������ȥ�Ҷϵ绰�����ǿ������������쳣������UEδ
        �յ�����ĹҶ���Ϣ�������ڶ�ʱ����ʱ����UE�����Ҷϵ绰 */
        if ((IMSA_FALSE == pstControlManager->ucMediaLostNotRelCallFlag) &&
            (IMSA_FALSE == IMSA_CONN_HasEmcActiveVoicePdp()))
        {
            /* ���ֻ����Ƶ���ر��ͷţ�����Ҫ֪ͨCALLģ�飻��������������ش��ڣ�Ҳ����Ҫ֪ͨCALL
            ģ�� */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE);
        }
        return ;
    }

    IMSA_INFO_LOG("IMSA_SRV_ProcEmcConnRelIndMsg:emc default release!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcEmcConnRelIndMsg_ENUM, 2);

    /* ����ע��״̬���յ����෢�͵��ͷ�SIP�������غ�Ĵ��� */
    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        /* delete PeriodImsEmcSrvTryTimer */
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

        /* ֪ͨIMSA����ȥע�� */
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

        return;
    }
    if (IMSA_SRV_STATUS_CONNING_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        /* ����CONNING+REG̬ʱ��IMSA��Ҫ֪ͨIMS������ */
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

        /* ֪ͨIMSA����ȥע�� */
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        return;
    }

    /* �������������״̬����֪ͨREGģ�鱾��ȥע�� */
    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* ��Ҫ֪ͨCALLģ��������з�������޷���״̬����ʹ���ͷŻ���Ľ����� */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);
    }

    if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* �����Ѿ����б���ȥע�ᣬ����֪ͨCALLģ����з���״̬�����޷���
           ���򱾵�ȥע�����̺��ͷ�CALL����ͬʱ���У����׳����� */
    }

    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnRelIndMsg
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_REL_IND������
 Input          : pstConnRelIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg( VOS_VOID )
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, LNAS_ENTRY);

    /* ����DETACHED̬�������ͷ�(����DETACH����MT DETACH���µ�)��IMSA��Ӧ���ؽ���·��
       ������ATTACHED̬�������ͷţ�IMSAӦ���ؽ���·��IMSAͨ��PS�����״̬�Ƿ���
       �������������֣���Ϊ�˱���ϵͳ��ʱ������(��APS֪ͨ�����ͷ���ǰ��MMA֪ͨ
       PS�����״̬�ں�)��������IMSA�ж�����IMSA�������ж�PS�����״̬��������
       �����Գ���IMS����ʱ��������ʱ����ʱ�����ж��������ӵ������Ƿ�߱� */
    pstControlMagnaer  = IMSA_GetControlManagerAddress();
    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&reg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_REGISTERED);

        /* SIP��������ͷź󣬲��ٱ���ȥע�ᣬIP��ַ�����������IMS������ע�ᶨʱ����ʱ��
        ���·���IMSע�� */
        /* ��Ҫ֪ͨIMS�������� */
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_NRM_SRV);

        /*IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);*/
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONNING_REG);

        /* ���������Գ���IMS����ʱ�� */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

        /* ֪ͨCALLģ����ͨ���з�������޷���״̬ */
        IMSA_SRV_SndNrmCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

        return ;
    }

    if (IMSA_SRV_STATUS_CONNING_REG == IMSA_SRV_GetNormalSrvStatus())
    {
        /* �����ʱ��û�������У���ת��IDLE+DEREG״̬������ȥע�� */
        if (IMSA_TRUE != IMSA_IsTimerRunning(&pstControlMagnaer->stPeriodImsSrvTryTimer))
        {
            /* ����CONNING+REG̬ʱ��IMSA��Ҫ֪ͨIMS������ */
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            /* ���������Գ���IMS����ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

            /* ��Ҫ�ͷ���Դ */
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            }
            #endif
        }
        return;
    }

    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&reging!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_REGISTERING);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

        /* ���������Գ���IMS����ʱ�� */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

        /* ״̬ת��IDLE&DEREG̬������IMSA_SRV_SetServcieStatus�л��õ�������
           ����IMS����ʱ��������������ҵ�ǰ��ע������У�������Ҫ��������ʱ����ת״̬ */
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        /* �����Ѿ����б���ȥע�ᣬ����֪ͨCALLģ����з���״̬�����޷���
           ���򱾵�ȥע�����̺��ͷ�CALL����ͬʱ���У����׳����� */

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_RegFailEventReport(IMSA_ERR_LOG_REG_FAIL_REASON_SIP_PDP_RELEASE,
                                IMSA_FALSE,
                                IMSA_FALSE,
                                IMSA_FALSE);
        #endif
        return ;
    }

    if (IMSA_SRV_STATUS_CONN_DEREG == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&dereg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_NOT_REGISTER);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        /* ���������Գ���IMS����ʱ�� */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif

        return ;
    }

    if ((IMSA_SRV_STATUS_RELEASING_DEREG == IMSA_SRV_GetNormalSrvStatus())
        || (IMSA_SRV_STATUS_CONNING_DEREG == IMSA_SRV_GetNormalSrvStatus()))
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:releasing&dereg or conning&dereg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_RELEASING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONNECTING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_NOT_REGISTER);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif

        return ;
    }

    if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&dereging!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_DEREGISTERING);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
        }
        #endif

        return ;
    }

    return ;
}


/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnRelIndMsg
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_REL_IND������
 Input          : pstConnRelIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
      2.lihong 00150010      2013-12-06  Modify:Emc dedicated
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcConnRelIndMsg
(
    const IMSA_CONN_REL_IND_STRU       *pstConnRelIndMsg
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcConnRelIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnRelIndMsg_ENUM, LNAS_ENTRY);

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    if (IMSA_CONN_TYPE_EMC == pstConnRelIndMsg->enConnType)
    {
        IMSA_SRV_ProcEmcConnRelIndMsg(pstConnRelIndMsg->enSipPdpType);

        return ;
    }

    /* ��ͨ���ӷ�֧ */

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnRelIndMsg->enSipPdpType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcConnRelIndMsg:normal media pdp release!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnRelIndMsg_ENUM, 2);

        /* ֪ͨCALLģ��ý������ͷ� */
        IMSA_ProcCallResourceIsNotReady(IMSA_CONN_TYPE_NORMAL);

        /* ֪ͨMSCC����ǰ����״̬ */
        if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus())
        {
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE,IMSA_CONN_IsExitPersistentBearer());
        }

        /* ��IDLE+DEREG״̬�²����յ�ý����ص��ͷ���Ϣ�����Բ���Ҫ�ж� */
            /* ����IR92�����������ͷų��غ�Ӧ��������ȥ�Ҷϵ绰�����ǿ������������쳣������UEδ
            �յ�����ĹҶ���Ϣ�������ڶ�ʱ����ʱ����UE�����Ҷϵ绰 */
            if ((IMSA_FALSE == pstControlMagnaer->ucMediaLostNotRelCallFlag) &&
                (IMSA_FALSE == IMSA_CONN_HasActiveVoicePdp()))
            {
                /* ���ֻ����Ƶ���ر��ͷţ�����Ҫ֪ͨCALLģ�飻��������������ش��ڣ�Ҳ����Ҫ֪ͨCALL
                ģ�� */
                IMSA_SRV_SndNrmCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                                IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE);
            }

        /* ý����ر��ͷţ����粻֧��IMS VOICE,���뼼����֧��IMSʱ������������Ƿ�
        �Ҷϵ绰��ɾ��UE�����Ҷϵ绰�Ĺ��� */

    }
    else
    {
        IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg();
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnReging
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_MODIFY_IND������
 Input          : pstConnModifyIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnReging
(
    VOS_VOID
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();

    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&reging!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_REGISTERING);

    /* �����DSDS���̣�����Ҫ��������Դ */
    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif

            /* ���������Գ���IMS����ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLYING:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

            break;

        /* ��������״̬Ӧ�ö������� */
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_WAIT_STATUS_IND:

            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            break;
        #endif
        default:
            break;
    }

    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_RegFailEventReport(IMSA_ERR_LOG_REG_FAIL_REASON_SIP_PDP_RELEASE,
                            IMSA_FALSE,
                            IMSA_FALSE,
                            IMSA_FALSE);
    #endif
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereg
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_MODIFY_IND������
 Input          : pstConnModifyIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereg
(
    VOS_VOID
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();

    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&reging!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_REGISTERING);

    /* �����DSDS���̣�����Ҫ��������Դ */
    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            /* ���������Գ���IMS����ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif

            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLYING:

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

            /* ���������Գ���IMS����ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

            break;

        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_WAIT_STATUS_IND:
            /* �п��ܴ��ڸ�״̬���ȴ���Ϣ�����·�ע�� */
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            IMSA_DsdsSndRrmDeRegisterInd(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);

            /* ���������Գ���IMS����ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            break;
        #endif
        default:
            break;
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereging
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_MODIFY_IND������
 Input          : pstConnModifyIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereging
(
    VOS_VOID
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&reging!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_REGISTERING);

    /* �����DSDS���̣�����Ҫ��������Դ */
    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLYING:

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            break;
        /* ��������״̬��Ӧ���� */
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_WAIT_STATUS_IND:
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            break;
        #endif
        default:
            break;
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereging
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_MODIFY_IND������
 Input          : pstConnModifyIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyPcscfInvalid
(
    VOS_VOID
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    #if (FEATURE_ON == FEATURE_PTM)
    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_RegFailEventReport(IMSA_ERR_LOG_REG_FAIL_REASON_SIP_PDP_RELEASE,
                                IMSA_FALSE,
                                IMSA_FALSE,
                                IMSA_FALSE);
    }
    else
    {
        IMSA_SRV_InitDeregEventReport(IMSA_ERR_LOG_INIT_DEREG_REASON_PDN_LOST);

        /* ��¼UE����ע���ʱ�� */
        ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampHighBit),
                                            &(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampLowBit));
    }
    #endif

    if ((IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus()) ||
        (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus()))
    {
        switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
        {
            case IMSA_RESOURCE_STATUS_ACTIVE:

                IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REGING);
                IMSA_SRV_SndRegDeregReq(IMSA_SRV_TYPE_NORMAL, IMSA_DEREG_LOCAL);
                IMSA_SRV_SndRegRegReq(IMSA_SRV_TYPE_NORMAL, IMSA_REG_ADDR_PARAM_NEW);

                #if (FEATURE_ON == FEATURE_DSDS)
                if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
                {
                    IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
                }
                #endif
                break;
            #if (FEATURE_ON == FEATURE_DSDS)
            case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

                IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                              IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                              VOS_FALSE,
                                              VOS_FALSE);

                IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REGING);
                IMSA_SRV_SndRegDeregReq(IMSA_SRV_TYPE_NORMAL, IMSA_DEREG_LOCAL);
                IMSA_SRV_SndRegRegReq(IMSA_SRV_TYPE_NORMAL, IMSA_REG_ADDR_PARAM_NEW);

                if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
                {
                    IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
                }
                break;

            case  IMSA_RESOURCE_STATUS_NULL:

                IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                              IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                              IMSA_REG_ADDR_PARAM_NEW,
                                              VOS_FALSE);

                IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REGING);
                IMSA_SRV_SndRegDeregReq(IMSA_SRV_TYPE_NORMAL, IMSA_DEREG_LOCAL);
                break;
            #endif
            default:
                #if (FEATURE_ON == FEATURE_DSDS)
                IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                                 RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
                #endif
                break;

        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereging
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_MODIFY_IND������
 Input          : pstConnModifyIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyRegParaInvalid
(
    VOS_VOID
)
{

    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();

    /* �����CONN&REGIN����GCONN&REG̬��������REGģ�鱾��ȥע�ᣬ
       ����CONNģ���ͷ����ӣ�״̬ת��RELEASING&DEREG̬�����������Գ���IMS
       ����ʱ�� */
    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnReging();
        return ;
    }

    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&reg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_REGISTERED);

        /* ��Ҫ֪ͨIMS�������� */
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_NRM_SRV);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONNING_REG);

        /* ���������Գ���IMS����ʱ�� */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

        return;
    }

    /* �����CONN&DEREGING̬��������REGģ�鱾��ȥע�ᣬ����CONNģ���ͷ����ӣ�
       ״̬ת��RELEASING&DEREG̬ */
    if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&dereging!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_DEREGISTERING);

        IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereging();
        return ;
    }

    /* �����CONN&DEREG̬��������CONNģ���ͷ����ӣ�״̬ת��RELEASING&DEREG̬,
       ���������Գ���IMS����ʱ�� */
    if (IMSA_SRV_STATUS_CONN_DEREG == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&dereg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_NOT_REGISTER);

        IMSA_SRV_ProcNormalConnSignalBearerModifyIndConnDereg();
        return ;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnModifyIndMsg
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_MODIFY_IND������
 Input          : pstConnModifyIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg
(
    const IMSA_CONN_MODIFY_IND_STRU    *pstConnModifyIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, LNAS_ENTRY);

    /* �������ע�������Ч����ֱ���˳� */
    if (IMSA_OP_TRUE != pstConnModifyIndMsg->bitOpModifyType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:normal,not reg para invalid!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, 2);

        return ;
    }

    /* ����������ӣ���ע��P-CSCF��ַʧЧ�������·���ע�᣻����ֱ���˳�  */
    if (IMSA_CONN_TYPE_EMC == pstConnModifyIndMsg->enConnType)
    {
        if (IMSA_CONN_MODIFY_TYPE_PCSCF_INVALID == pstConnModifyIndMsg->enModifyType)
        {
            /* ��Ҫ�ж�ע��״̬ */
            if ((IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus()) ||
                (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus()))
            {
                IMSA_SRV_SetServcieStatus(IMSA_REG_TYPE_EMC, IMSA_SRV_STATUS_CONN_REGING);
                IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);
                IMSA_SRV_SndRegRegReq(IMSA_REG_TYPE_EMC, IMSA_REG_ADDR_PARAM_NEW);
            }
        }
        return ;
    }

    /* ע�����ʧЧ */
    if (IMSA_CONN_MODIFY_TYPE_REG_PARA_INVALID == pstConnModifyIndMsg->enModifyType)
    {
        IMSA_SRV_ProcNormalConnSignalBearerModifyRegParaInvalid();

    }
    else /* P-CSCF��ַʧЧ */
    {
        IMSA_SRV_ProcNormalConnSignalBearerModifyPcscfInvalid();
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_ProcConnModifyIndMsg
 Description    : IMSA�ڲ���ϢID_IMSA_CONN_MODIFY_IND������
 Input          : pstConnModifyIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
      2.lihong 00150010      2013-12-06  Modify
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcConnModifyIndMsg
(
    const IMSA_CONN_MODIFY_IND_STRU    *pstConnModifyIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcConnModifyIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnModifyIndMsg_ENUM, LNAS_ENTRY);

    /* �����ý������޸ģ���ͨ��CALLģ����Դ�߱� */
    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnModifyIndMsg->enSipPdpType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcConnModifyIndMsg:no need notify CallModule!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnModifyIndMsg_ENUM, LNAS_ENTRY);
    }
    else
    {
        IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg(pstConnModifyIndMsg);
    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCallRsltWithFirstAddr
 Description    : IMSA�ڲ���ϢID_IMSA_CALL_RESULT_ACTION_IND������
 Input          : pstCallRsltActionIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCallRsltWithFirstAddr
(
    const IMSA_CALL_RESULT_ACTION_IND_STRU *pstCallRsltActionIndMsg
)
{
    if (IMSA_CALL_TYPE_EMC != pstCallRsltActionIndMsg->enCallType)
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:normal srv,first addr pair can not happen!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_PARAM_INVALID, 1);
        return ;
    }

    if (IMSA_SRV_STATUS_IDLE_DEREG != IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:first addr pair,emc status is not IDLE&DEREG!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, IMSA_STATE_ERROR, 1);
        return ;
    }

    if (IMSA_RESOURCE_STATUS_ACTIVE == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL))
    {
        IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                    IMSA_CONN_TYPE_EMC);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                    IMSA_SRV_STATUS_CONNING_DEREG);
    }
    #if (FEATURE_ON == FEATURE_DSDS)
    else if (IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL))
    {
        IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL,
                                      IMSA_RF_RES_APPLY_TRIGER_SRC_EMC_CALL,
                                      VOS_FALSE,
                                      VOS_FALSE);

        IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                    IMSA_CONN_TYPE_EMC);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                    IMSA_SRV_STATUS_CONNING_DEREG);
    }
    else
    {
        IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL,
                                      IMSA_RF_RES_APPLY_TRIGER_SRC_EMC_CALL,
                                      VOS_FALSE,
                                      VOS_FALSE);
    }
    #endif
    return;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCallRsltWithNextAddr
 Description    : IMSA�ڲ���ϢID_IMSA_CALL_RESULT_ACTION_IND������
 Input          : pstCallRsltActionIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCallRsltWithNextAddr
(
    const IMSA_CALL_RESULT_ACTION_IND_STRU *pstCallRsltActionIndMsg
)
{
    if (IMSA_CALL_TYPE_EMC != pstCallRsltActionIndMsg->enCallType)
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:normal srv,next addr pair can not happen!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_PARAM_INVALID, 2);
        return ;
    }

    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:next addr pair,emc status is not CONN&REG!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, IMSA_STATE_ERROR, 2);
        return ;
    }

    /* �ȱ���ȥע�ᣬ�ڷ���ע������״̬ת��CONN&REGING */
    IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_EMC,
                                IMSA_DEREG_LOCAL);

    IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_EMC,
                                IMSA_REG_ADDR_PARAM_NEXT);

    IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                IMSA_SRV_STATUS_CONN_REGING);

    /* ����CALLģ���ǻ������Ž���������˲���֪ͨCALLģ���޷��񣬷����
       ����CALLģ���������Ľ����� */
    return;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCallRsltWithNextAddr
 Description    : IMSA�ڲ���ϢID_IMSA_CALL_RESULT_ACTION_IND������
 Input          : pstCallRsltActionIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCallRsltRestoration
(
    const IMSA_CALL_RESULT_ACTION_IND_STRU *pstCallRsltActionIndMsg
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    if (IMSA_CALL_TYPE_EMC == pstCallRsltActionIndMsg->enCallType)
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:emc srv,restoration can not happen!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_PARAM_INVALID, 3);
        return ;
    }

    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:restoration,normal status is not CONN&REG!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, IMSA_STATE_ERROR, 3);
        return ;
    }

    if (IMSA_RESOURCE_STATUS_ACTIVE == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                IMSA_DEREG_LOCAL);

        IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                    IMSA_REG_ADDR_PARAM_RESTORATION);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                    IMSA_SRV_STATUS_CONN_REGING);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
        }
        #endif
    }
    #if (FEATURE_ON == FEATURE_DSDS)
    else if (IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                     IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                     IMSA_REG_ADDR_PARAM_RESTORATION,
                                     IMSA_FALSE);

        IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                IMSA_DEREG_LOCAL);

        IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                    IMSA_REG_ADDR_PARAM_RESTORATION);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                    IMSA_SRV_STATUS_CONN_REGING);

        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
        }
    }
    else
    {
        IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                      IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                      IMSA_REG_ADDR_PARAM_RESTORATION,
                                      IMSA_FALSE);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL,
                                IMSA_DEREG_LOCAL);

        /* IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                    IMSA_SRV_STATUS_CONN_REGING); */
        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                    IMSA_SRV_STATUS_CONN_DEREG);
    }
    #endif
    /* �����Ѿ�֪ͨע��ģ����б���ȥע�ᣬ�������֪ͨCALLģ���޷���
       ���򱾵�ȥע�����̺��ͷ�CALL����ͬʱ���У����׳����� */

    /* ��¼UE����ȥע���¼���������ע���ʱ�� */
    #if (FEATURE_ON == FEATURE_PTM)
    /* ��¼UE����ע���ʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampHighBit),
                                        &(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampLowBit));
    #endif

    return;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCallRsltActionIndMsg
 Description    : IMSA�ڲ���ϢID_IMSA_CALL_RESULT_ACTION_IND������
 Input          : pstCallRsltActionIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-06-24  Draft Enact
      2.wangchen 00209181    2014-06-19  Modify vtlte
      3.wangchen 00209181   2015-11-28   Modify:volte dsds
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCallRsltActionIndMsg
(
    const IMSA_CALL_RESULT_ACTION_IND_STRU *pstCallRsltActionIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcCallRsltActionIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_ENTRY);

    switch (pstCallRsltActionIndMsg->enResultAction)
    {
        case IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR:

            IMSA_SRV_ProcCallRsltWithFirstAddr(pstCallRsltActionIndMsg);
            break;
        case IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR:

            IMSA_SRV_ProcCallRsltWithNextAddr(pstCallRsltActionIndMsg);
            break;
        case IMSA_RESULT_ACTION_REG_RESTORATION:

            IMSA_SRV_ProcCallRsltRestoration(pstCallRsltActionIndMsg);
            break;

        default:

            IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:illegal result action!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_ERROR);

            break;
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCallRsltActionIndMsg
 Description    : IMSA�ڲ���ϢID_IMSA_CALL_SRVCC_SUCC_IND������
 Input          : IMSA_SRV_ProcCallSrvccSuccIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719      2015-12-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCallSrvccSuccIndMsg
(
    const IMSA_CALL_SRVCC_SUCC_IND_STRU *pstCallSrvccSuccIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcCallSrvccSuccIndMsg is entered!");

    (VOS_VOID)pstCallSrvccSuccIndMsg;

    /* �յ�CALLģ�鷢����SRVCC�ɹ���Ϣ��֪ͨTAF��ǰIMS����δע��״̬,
       TAF�Ͳ�������ѡ��IMS��
       �绰�ҶϺ󣬻ص�LTE�ᷢTAU��MSCC��֪ͨSERVICE_CHANGE_IND����ʱ
       IMSA�ж�֮ǰ֪ͨ��δע��״̬������֪ͨTAF��ǰΪ��ע��״̬��
       ֮��Ϳ���������ѡ��IMS�� */
    IMSA_SRV_NrmRegStatusNotify(IMSA_NORMAL_REG_STATUS_DEREG);

    IMSA_SetLastNrmRegStatus(IMSA_NORMAL_REG_STATUS_DEREG);
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcTransToNotSupportEms
 Description    : EMSתΪ��֧��ʱ�Ĵ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-10-11  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcTransToNotSupportEms( VOS_VOID )
{
    switch (IMSA_SRV_GetEmcSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_REG:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conn&reg!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_REGISTERED);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        case IMSA_SRV_STATUS_CONNING_DEREG:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conning&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conn&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        case IMSA_SRV_STATUS_CONN_REGING:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conn&reging!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_REGISTERING);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        default:
            break;
    }
}


/*****************************************************************************
 Function Name  : IMSA_SRV_UpdateRat
 Description    : ���½��뼼��
 Input          : enRat------------------���뼼��
 Output         : pulIsNotfiyNrmNoSrv----�Ƿ�֪ͨ���������޷���
                  pulIsNotfiyEmcNoSrv----�Ƿ�֪ͨ���������޷���
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-10-11  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_UpdateRat
(
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enRat,
    VOS_UINT32                         *pulIsNotfiyNrmNoSrv,
    VOS_UINT32                         *pulIsNotfiyEmcNoSrv
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;
    IMSA_CAMPED_RAT_TYPE_ENUM_UINT8     enCampedRatTypeTmp  = IMSA_CAMPED_RAT_TYPE_BUTT;
    IMSA_CALL_MANAGER_STRU              *pstImsaCallCtx   = VOS_NULL_PTR;

    pstImsaCallCtx   = IMSA_CallCtxGet();
    pstNwInfo = IMSA_GetNetInfoAddress();

    *pulIsNotfiyNrmNoSrv = IMSA_FALSE;
    *pulIsNotfiyEmcNoSrv = IMSA_FALSE;

    IMSA_SRV_RatFormatTransform(    &enCampedRatTypeTmp,
                                    enRat);

    /* �������δ�������ֱ�ӷ��� */
    if (pstNwInfo->enImsaCampedRatType == enCampedRatTypeTmp)
    {
        return ;
    }

    /* ��GU�任��L���ҵ�ǰ�к��д��ڣ���֪ͨLRRC����HIFIͬ�� */
    if ((enCampedRatTypeTmp == IMSA_CAMPED_RAT_TYPE_EUTRAN)
        && (VOS_TRUE == IMSA_IsCallConnExist()))
    {
        IMSA_SndLRrcHifiSyncSwtichInd(IMSA_TRUE);
    }

    pstNwInfo->enImsaCampedRatType = enCampedRatTypeTmp;

    /*��ϵͳ�任����ҪֹͣBACK-OFF��ʱ��*/
    IMSA_StopTimer(&pstImsaCallCtx->stBackOffTxTimer);
    IMSA_StopTimer(&pstImsaCallCtx->stBackOffTyTimer);

    /* ������뼼�������������Ŀ�Ľ��벻֧��IMS����SRVCC��ʶΪFALSE����ָʾ
       IMSA CALL��ģ���޷���ԭ��ֵ��Ϊ��SRVCC��ϵͳ */
    if ((IMSA_FALSE == IMSA_SRV_IsCurRatSupportIms())
        && (IMSA_FALSE == IMSA_CallGetSrvccFlag()))
    {
        *pulIsNotfiyNrmNoSrv = IMSA_TRUE;

    }

    /* ������뼼�������������Ŀ�Ľ��벻֧��EMS����ָʾIMSA REG��ģ�鱾�ؽ���
       ȥע�ᣨ�������IMS����ע�ᣩ����֪ͨIMSA CONN��ģ���ͷŽ������ӣ�
       ���ֻ����IMS�������ӣ�������IMS����ע�ᣩ */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportEms())
    {
        *pulIsNotfiyEmcNoSrv = IMSA_TRUE;


    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_UpdateImsVoPsStatus
 Description    : ���������Ƿ�֧��IMS VOICE��ʶ
 Input          : enImsVoPsInd------------------IMS VOICE��ʶ
                  ulIsNotfiyNrmNoSrv------------�Ƿ�֪ͨ���������޷���
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-10-11  Draft Enact
      2.wangchen 00209181    2013-10-12  Modify
*****************************************************************************/
VOS_VOID IMSA_SRV_UpdateImsVoPsStatus
(
    MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8      enImsVoPsInd
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;

    pstNwInfo = IMSA_GetNetInfoAddress();

    if (pstNwInfo->enImsaImsVoPsStatus != enImsVoPsInd)
    {
        pstNwInfo->enImsaImsVoPsStatus          = enImsVoPsInd;

        IMSA_SndMsgAtCirepiInd(enImsVoPsInd);

    }
    IMSA_ConfigNetCapInfo2Ims();

}

/*****************************************************************************
 Function Name  : IMSA_SRV_UpdateEmsStatus
 Description    : ���������Ƿ�֧��EMS��ʶ
 Input          : enEmsInd----------------------EMS��ʶ
                  ulIsNotfiyEmcNoSrv------------�Ƿ�֪ͨ���������޷���
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-10-11  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_UpdateEmsStatus
(
    MSCC_IMSA_EMS_INDICATOR_ENUM_UINT8           enEmsInd
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;

    pstNwInfo = IMSA_GetNetInfoAddress();

    pstNwInfo->enImsaEmsStatus = enEmsInd;

}


/*****************************************************************************
 Function Name  : IMSA_SRV_ProcWhenRoamNotSatisfiedConnReging
 Description    : ������������ȥע�����̵ĺ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcWhenRoamNotSatisfiedConnReging(VOS_VOID)
{
    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            break;

        case IMSA_RESOURCE_STATUS_NULL:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            //IMSA_DsdsSaveMoSmsMsg(pstRpDataReq);
            break;
        #endif
        default:
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            break;

    }
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcWhenRoamNotSatisfiedConnReging
 Description    : ������������ȥע�����̵ĺ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcWhenRoamNotSatisfiedConningDeReg(VOS_VOID)
{

    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            break;

        case  IMSA_RESOURCE_STATUS_NULL:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            //IMSA_DsdsSaveMoSmsMsg(pstRpDataReq);
            break;
        #endif
        default:
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            break;

    }

}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcWhenRoamNotSatisfiedConnReg
 Description    : ������������ȥע�����̵ĺ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcWhenRoamNotSatisfiedConnReg(VOS_VOID)
{

    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            break;

        case  IMSA_RESOURCE_STATUS_NULL:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            //IMSA_DsdsSaveMoSmsMsg(pstRpDataReq);
            break;
        #endif
        default:
            /* */
            break;

    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcWhenRoamNotSatisfied
 Description    : ������������ȥע�����̵ĺ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-07-02  Draft Enact
      2.zhaochen 00308719   2015-08-25  Modify for VoLTE
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcWhenRoamNotSatisfied(VOS_VOID)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus      = IMSA_SRV_STATUS_BUTT;

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();

    /* �����ǰ��IMSҵ����ڣ�����Ҫ��ҵ������󣬲��ܷ���ȥע�� */
    if (VOS_TRUE == IMSA_IsImsExist())
    {
        return;
    }
    /* �����ǰ��ͨ����֧�����Σ��򲻴��� */
    if (IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_ROAM_NOT_SUPPORT != IMSA_SRV_IsNrmSrvConditonSatisfied())
    {
        return;
    }

    /* ���ݵ�ǰ����״̬���в�ͬ���� */
    switch (enNrmSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
            /* ֪ͨMMA IMS VOICE  ������ */
            /* �������ֳ���������IMSע������ʱ��MMA�Լ��ܹ�ʶ��ֱ����ΪIMS voice�����ã� ����ҪIMSA
            ֪ͨ���������������£��Ҳ�֧��IMSע�ᣬMMA���޷�ʶ��ģ�������ҪIMSA����֪ͨһ�� */
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());

            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
            #endif
            break;
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_SRV_ProcWhenRoamNotSatisfiedConnReging();
            #if (FEATURE_ON == FEATURE_PTM)
            if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus())
            {
                IMSA_RegFailEventReport(IMSA_ERR_LOG_REG_FAIL_REASON_ROAMING_NOT_SUPPORT_REG,
                                        IMSA_FALSE,
                                        IMSA_FALSE,
                                        IMSA_FALSE);
            }
            #endif
            break;

        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:
            IMSA_SRV_ProcWhenRoamNotSatisfiedConningDeReg();
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_SRV_InitDeregEventReport(IMSA_ERR_LOG_INIT_DEREG_REASON_ROAMING_NOT_SUPPORT_REG);
            #endif
            break;

        case IMSA_SRV_STATUS_CONNING_REG:
            /* ��Ҫ֪ͨIMS�����䷢����֪ͨ���𱾵�ע�� */
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            /*�ͷ���Դ */
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_SRV_InitDeregEventReport(IMSA_ERR_LOG_INIT_DEREG_REASON_ROAMING_NOT_SUPPORT_REG);
            #endif
            break;

        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_SRV_ProcWhenRoamNotSatisfiedConnReg();

            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_SRV_InitDeregEventReport(IMSA_ERR_LOG_INIT_DEREG_REASON_ROAMING_NOT_SUPPORT_REG);
            #endif
            break;

        default:
            /* �ͷ���Դ */
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            break;
    }

}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcNrmSrvConditionSatisfiedResult
 Description    : MMA��������Ϣ������
 Input          : pstServiceChangeInd-----------SERVICE CHANGE IND��Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-30  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_PreProcNrmSrvConSatStatus
(
    IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32    enImsaSrvStatue
)
{
    switch(enImsaSrvStatue)
    {
        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_RAT_NOT_SUPPORT:
            /* �����ǰ���뼼����֧�֣����CALLģ���ϱ��޷��� */
            if ((MSCC_IMSA_IMS_VOPS_NOT_SUPPORT == IMSA_GetNetInfoAddress()->enImsaImsVoPsStatus)&&
                (IMSA_FALSE == IMSA_GetControlManagerAddress()->ucNonSrvccNotRelCallFlag))
            {
                IMSA_SRV_SndNrmCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE);
                IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE);
            }
            IMSA_CMCCDeregProc();
            break;

        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_USIM_NOT_SUPPORT:
            /* �������ֳ���������IMSע������ʱ��MMA�Լ��ܹ�ʶ��ֱ����ΪIMS voice�����ã� ����ҪIMSA
            ֪ͨ�����ǿ���Ч�ĳ�����MMA���޷�ʶ��ģ�������ҪIMSA����֪ͨһ�� */
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());
        #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
        #endif
            break;

        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_ROAM_NOT_SUPPORT:
            /* ��Ҫ���ݵ�ǰ�ķ���״̬���ж���ֱ��֪ͨVOICE�����ã����Ƿ���ȥע�� */
            IMSA_CommonDeregProc();
            break;

        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_VOICE_NOT_SUPPORT:
            /* ���ƶ������������IMS������֧�֣�����ȥע�� */
            IMSA_CMCCDeregProc();
            break;

        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_OTHERS:
            /* IMS������֧�ֻ���PS�����״̬��ΪNORMAL SERVICEʱ�������⴦�� */
        #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
        #endif
            break;
        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_REG_FORBIDDEN:
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
            #endif
            break;

        default:
            return IMSA_TRUE;
    }

    return IMSA_FALSE;
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcServiceChangeIndIdleDereg
 Description    : MMA��������Ϣ������
 Input          : pstServiceChangeInd-----------SERVICE CHANGE IND��Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181    2015-12-07  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcServiceChangeIndIdleDereg
(
    VOS_VOID
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    switch(IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_FALSE,
                                          IMSA_FALSE);

            /* ��������ģ�齨�����ӣ���״̬ת��IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;
        #endif
        case IMSA_RESOURCE_STATUS_ACTIVE:

            /* ��������ģ�齨�����ӣ���״̬ת��IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);

            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        default:
            break;
    }
    /* ��¼UE��������ʱ�� */
    #if (FEATURE_ON == FEATURE_PTM)
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStartConnTimerAddr()->ul32KTStampHighBit),
                                        &(IMSA_GetErrlogStartConnTimerAddr()->ul32KTStampLowBit));
    #endif
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcServiceChangeIndIdleDereg
 Description    : MMA��������Ϣ������
 Input          : pstServiceChangeInd-----------SERVICE CHANGE IND��Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181    2015-12-07  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcServiceChangeIndConnDereging
(
    VOS_VOID
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    switch(IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_FALSE,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_FALSE,
                                          IMSA_FALSE);

            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());

            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                        IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEW);

            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            break;
        case IMSA_RESOURCE_STATUS_APPLYING:
            /* �޸Ĵ���ԴΪ��ȡ���� */
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            break;
        #endif
        case IMSA_RESOURCE_STATUS_ACTIVE:

            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());

            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                        IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEW);

            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                /* �޸Ĵ���ԴΪ��ȡ���� */
                IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                                 RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);

                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StopTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;

        default:
            break;
    }
    #if (FEATURE_ON == FEATURE_PTM)

    /* ��¼UE����ע���ʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampHighBit),
                                        &(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampLowBit));
    #endif
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcServiceChangeIndIdleDereg
 Description    : MMA��������Ϣ������
 Input          : pstServiceChangeInd-----------SERVICE CHANGE IND��Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181    2015-12-07  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcServiceChangeIndConnDereg
(
    VOS_VOID
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    switch(IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_REG_ADDR_PARAM_NEW,
                                          IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                          IMSA_REG_ADDR_PARAM_NEW,
                                          IMSA_FALSE);

            /* ����ע��ģ�鷢��ע�ᣬ��״̬ת��IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEW);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;
        #endif
        case IMSA_RESOURCE_STATUS_ACTIVE:

            /* ����ע��ģ�鷢��ע�ᣬ��״̬ת��IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEW);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        default:
            break;
    }
    #if (FEATURE_ON == FEATURE_PTM)
    /* ��¼UE����ע���ʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampHighBit),
                                        &(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampLowBit));
    #endif
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcServiceChangeInd
 Description    : MMA��������Ϣ������
 Input          : pstServiceChangeInd-----------SERVICE CHANGE IND��Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-04  Draft Enact
      2.wangchen 00209181    2015-11-18  Modify:volte dsds
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcServiceChangeInd
(
    const MSCC_IMSA_SERVICE_CHANGE_IND_STRU     *pstServiceChangeInd
)
{
    IMSA_NETWORK_INFO_STRU                     *pstNwInfo           = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;
    IMSA_SRV_STATUS_ENUM_UINT8                  enNrmSrvStatus      = IMSA_SRV_STATUS_BUTT;
    VOS_UINT32                                  ulIsNotfiyNrmNoSrv  = IMSA_FALSE;
    VOS_UINT32                                  ulIsNotfiyEmcNoSrv  = IMSA_FALSE;
    IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32    enImsaSrvStatue     = IMSA_NRM_SRV_CON_SAT_STATUE_BUTT;
    IMSA_MSCC_REG_SUCC_PROC_ENUM_UINT32         enRegSuccProcType   = IMSA_MSCC_REG_PROC_BUTT;

    IMSA_INFO_LOG("IMSA_SRV_ProcServiceChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcServiceChangeInd_ENUM, LNAS_ENTRY);

    /* �洢SERVICE CHANGE IND��Ϣ��Я���Ĳ��� */
    pstNwInfo                               = IMSA_GetNetInfoAddress();
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    pstNwInfo->enImsaPsServiceStatus        = pstServiceChangeInd->enPsServiceStatus;
    /* ֮ǰ�����α����ͨ��CAMP_INFO_CHANGE_IND�������ģ����ǲ���׼ȷ����ҪSERVICE_CHANGE_IND��֪ͨ��IMSA
       ����һ������λbitRoamingValid�����ñ���λΪ1ʱ���������α�־��Ч����ʱIMSA���±���ά��������״̬��*/
    if (VOS_TRUE == pstServiceChangeInd->bitRoamingValid)
    {
        pstNwInfo->ucImsaRoamingFlg             = pstServiceChangeInd->ucRoamingFlg;
    }

    pstControlMagnaer->ucImsaUsimStatus     = pstServiceChangeInd->ucPsSimValid;

    /* ���뼼������ */
    IMSA_SRV_UpdateRat(pstServiceChangeInd->enRat, &ulIsNotfiyNrmNoSrv, &ulIsNotfiyEmcNoSrv);

    /* ֻ������������ʱ���Ÿ�������֧��IMS��EMSָʾ */
    if (MSCC_IMSA_NORMAL_SERVICE == pstServiceChangeInd->enPsServiceStatus)
    {
        IMSA_SRV_UpdateImsVoPsStatus(pstServiceChangeInd->enImsVoPsInd);
        IMSA_SRV_UpdateEmsStatus(pstServiceChangeInd->enEmsInd);

        if(pstServiceChangeInd->bitRegSuccProcTypeValid != pstControlMagnaer->bitRegSuccProcTypeValid)
        {
            pstControlMagnaer->bitRegSuccProcTypeValid = pstServiceChangeInd->bitRegSuccProcTypeValid;
        }
        if(pstServiceChangeInd->enRegSuccProcType != IMSA_GetRegSuccProcType())
        {
            enRegSuccProcType = pstServiceChangeInd->enRegSuccProcType;
            IMSA_SetRegSuccProcType(enRegSuccProcType);
        }
    }

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();

    /* ����˷�֧��˵���ϴθ�TAF����ע��״̬��δע�ᣬĿǰֻ����SRVCC���ٹҶϳ����л������������� */
    if ((IMSA_SRV_STATUS_CONN_REG == enNrmSrvStatus) && (IMSA_NORMAL_REG_STATUS_REG != IMSA_GetLastNrmRegStatus()))
    {
        IMSA_SRV_NrmRegStatusNotify(IMSA_NORMAL_REG_STATUS_REG);

        IMSA_SetLastNrmRegStatus(IMSA_NORMAL_REG_STATUS_REG);
    }

    enImsaSrvStatue = IMSA_SRV_IsNrmSrvConditonSatisfied();

    if (VOS_FALSE== IMSA_SRV_PreProcNrmSrvConSatStatus(enImsaSrvStatue))
    {
        return;
    }

    /*�����ǰservice change ind��Ϣ�д��ı�־��ǰע��ɹ�������Ч�ı�־λΪtrue,
     ���ݵ�ǰע�����ͽ��д���*/
    if(VOS_TRUE == pstServiceChangeInd->bitRegSuccProcTypeValid)
    {
        /*����Ĵ��������:�����L��ע������Ϊ�ٵ�TAU��Ϊ��Чֵ,ֱ�Ӷ���,���ٴ���IMSע��*/
        if((IMSA_MSCC_TAU_UNREAL_PROC == pstServiceChangeInd->enRegSuccProcType)
            ||(IMSA_MSCC_REG_PROC_BUTT == pstServiceChangeInd->enRegSuccProcType))
        {
            return;
        }
    }


    /* ���ݵ�ǰ����״̬���в�ͬ���� */
    switch (enNrmSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* ��������ģ�齨�����ӣ���״̬ת��IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_ProcServiceChangeIndIdleDereg();
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            /* ���������Գ���IMS����ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;

        case IMSA_SRV_STATUS_CONN_DEREGING:

            IMSA_SRV_ProcServiceChangeIndConnDereging();

            break;

        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_SRV_ProcServiceChangeIndConnDereg();
            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONN_REGING:
        case IMSA_SRV_STATUS_CONNING_REG:
            /*������״̬��ע����ɺ��ϱ�IMS voice����*/
            break;
        default:
            /*IMSA������ע�ᣬ���ϱ�IMS voice����*/
            if (IMSA_TRUE == IMSA_IsImsVoiceContidionSatisfied())
            {
                IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE,IMSA_CONN_IsExitPersistentBearer());
            }
            else
            {
                IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());
            }

            break;
    }
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcCampInfoChangeInd
 Description    : MMA������Ϣ�����Ϣ������
 Input          : pstRoamingChangeInd-----------ROAMING CHANGE IND��Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-27  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcCampInfoChangeInd
(
    const MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU     *pstCampInfoChangeInd
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcCampInfoChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcCampInfoChangeInd_ENUM, LNAS_ENTRY);

    /* �洢SERVICE CHANGE IND��Ϣ��Я���Ĳ��� */
    pstNwInfo                       = IMSA_GetNetInfoAddress();

    pstNwInfo->enAccessType         = pstCampInfoChangeInd->enAccessType;
    pstNwInfo->usLac                = pstCampInfoChangeInd->usLac;
    pstNwInfo->usTac                = pstCampInfoChangeInd->usTac;
    IMSA_MEM_CPY_S(                 &pstNwInfo->stPlmnId,
                                    sizeof(MSCC_IMSA_PLMN_ID_STRU),
                                    &pstCampInfoChangeInd->stPlmnId,
                                    sizeof(MSCC_IMSA_PLMN_ID_STRU));
    pstNwInfo->ulCellId             = pstCampInfoChangeInd->ulCellId;

    /* ����CGI��Ϣ��IMS */
    IMSA_ConfigCgi2Ims();
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcVoiceDomainChangeInd
 Description    : MMA VOICE DOMAIN��Ϣ�����Ϣ������
 Input          : pstVoiceDomainChangeInd-----------VOICE DOMAIN CHANGE IND��Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-02-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcVoiceDomainChangeInd
(
    const MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU     *pstVoiceDomainChangeInd
)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;

    IMSA_INFO_LOG("IMSA_SRV_ProcVoiceDomainChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcVoiceDomainChangeInd_ENUM, LNAS_ENTRY);

    pstControlManager = IMSA_GetControlManagerAddress();

    /* �洢VOICE DOMAIN CHANGE IND��Ϣ��Я���Ĳ��� */
    pstControlManager->stImsaConfigPara.enVoiceDomain = (IMSA_VOICE_DOMAIN_ENUM_UINT32)pstVoiceDomainChangeInd->enVoiceDomain;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcDeregReq()
 Description    : IMSA SERVICEģ�鴦��DEREG����
 Input          : enDeregCause----------ȥע������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcDeregReq
(
    IMSA_SRV_DEREG_CAUSE_ENUM_UINT32    enDeregCause
)
{
    /* ����ȥע��ԭ��ֵ */
    IMSA_SetDeregCause(enDeregCause);

    /* �������������ע��ɹ���������ע�ᣬ��֪ͨע��ģ����б���ȥע�� */
    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:emc,conn&reging!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_EMERGENCY);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERING);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREG);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
    }

    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:emc,conn&reg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_EMERGENCY);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERED);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREG);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* �����Ѿ����б���ȥע�ᣬ������֪ͨCALLģ��������н����޷���״̬��
           ���򱾵�ȥע�����̺�CALL�ͷ�����ͬʱ���У����׳����� */
    }

    if (IMSA_SRV_STATUS_CONNING_DEREG == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:emc,conning&dereg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_EMERGENCY);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONNECTING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_NOT_REGISTER);

        /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);
    }

    /* �����ͨ������ע��ɹ���������ע�ᣬ��֪ͨע��ģ�����ȥע�� */
    if ((IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus())
        || (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus()))
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:dereg normal service!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_NORMAL);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERED);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);

        /* �����Ѿ�����ȥע�ᣬ������֪ͨCALLģ����ͨ���н����޷���״̬��
           ����ȥע�����̺�CALL�ͷ�����ͬʱ���У����׳����� */
        return ;
    }

    if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:wait for dereg result!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, 1);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_DEREGISTERING);
        return ;
    }

    IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:already dereg!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_NOT_REGISTER);

    IMSA_SndMsccMsgDeregCnf();
    return ;
}

/*****************************************************************************
 Function Name  : IMSA_SRV_ProcReceivedUsimReadfileCnf()
 Description    : USIM�ļ���ȡ���,�����ʼע��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719   2016-01-25  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcReceivedUsimReadfileCnf(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    /* ���״̬����IDLE_DEREG���ڲ����㷢��ע����������򷵻� */
    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != IMSA_SRV_IsNrmSrvConditonSatisfied()
     || IMSA_SRV_STATUS_IDLE_DEREG != IMSA_SRV_GetNormalSrvStatus())
    {
        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_NOT_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

           IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);

            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                    IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);

            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;
        #endif
        default:
            break;
    }
    return;
}

/*****************************************************************************
 Function Name  : IMSA_StartImsNormalService
 Description    : ���ƹ���ģ���ṩ������ģ���API, Callģ���ڴ���ͨ�绰ʱ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32
                  ���ؽ����0����ʾControl�����ṩ��������Call����ֱ�Ӵ�绰
                  ���ؽ����1����ʾ�����ṩ�������񣬴������绰ʧ��

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
      2.wangchen 00209181   2015-08-17 Modify:CHR
*****************************************************************************/
VOS_UINT32 IMSA_StartImsNormalService
(
    IMSA_CALL_TYPE_ENUM_UINT8               enCallType
)
{
    /* �����ǰ�Ѿ���һ·�绰��˵��������������Ѿ��жϹ�һ���ˡ�
       ���ڷ���״̬���漰NV�ı�־�����к���ʱ�ǲ����ܸı�ģ�
       ���������״̬�����ڵ�ǰ�Ѿ���һ·�绰����ʹ�������������ı䣬
       IMSAҲ���ᷢ��ȥע�����̣��ʽ�����ʾ��Ȼ��VoLTE���á�
       ��ֻ��Ҫ�Ժ������ͽ����жϣ��������������ж� */
    if ((IMSA_CALL_TYPE_VOICE == enCallType)
        && (VOS_FALSE == IMSA_GetUeImsVoiceCap()))
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VOICE_CALL,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if ((IMSA_CALL_TYPE_VIDEO == enCallType)
        && (VOS_FALSE == IMSA_GetUeImsVideoCap()))
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VIDEO_CALL,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if (VOS_TRUE == IMSA_IsCallConnExist())
    {
        return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
    }

    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NORM_SER_NOT_CONN_REG,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if (IMSA_VOICE_DOMAIN_CS_ONLY == IMSA_GetVoiceDomain())
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_VOICE_DOMAIN_CS_ONLY,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if (IMSA_IMS_VOPS_STATUS_NOT_SUPPORT == IMSA_GetNwImsVoiceCap())
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_IMS_VOPS_STATUS_NOT_SUPPORT,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
}

/*****************************************************************************
 Function Name  : IMSA_StartImsNormalService
 Description    : ���ƹ���ģ���ṩ������ģ���API, Callģ���ڴ�����绰ʱ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32
                  ���ؽ����0����ʾControl�����ṩ��������Call����ֱ�Ӵ�绰
                  ���ؽ����1����ʾ�����ṩ�������񣬴�����绰ʧ��
                  ���ؽ����2����ʾ��ʱ�����ṩ�����������ڽ�����������Callģ����Ҫ����绰

 History        :
      1.wangchen 00209181    2015-11-28  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_StartImsEmergServiceAbilityCheck
(
    IMSA_EMC_CALL_TYPE_ENUM_UINT32     *penEmcCallType
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enEmcSrvStatus      = IMSA_SRV_STATUS_BUTT;

    IMSA_INFO_LOG("IMSA_StartImsEmergService is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, LNAS_ENTRY);


    /* �жϻ�ȡ����IMS����������Ƿ�߱���������߱����򷵻ز��ܴ������ */
    if (IMSA_TRUE != IMSA_SRV_IsEmcSrvConditonSatisfied())
    {
        IMSA_INFO_LOG("IMSA_StartImsEmergService:EMC service condition not satisfied!");
        TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, 1);
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    /* ������������������Ϸ������������ֱ�ӷ����ܴ������ */
    if (IMSA_TRUE == IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied())
    {
        IMSA_INFO_LOG("IMSA_StartImsEmergService:can make emc call in normal service!");
        TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, 2);
        *penEmcCallType = IMSA_EMC_CALL_TYPE_IN_NORMAL_SRV;
        return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
    }

    enEmcSrvStatus      = IMSA_SRV_GetEmcSrvStatus();

    /* ���ݵ�ǰ����״̬���в�ͬ���� */
    switch (enEmcSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;

        case IMSA_SRV_STATUS_CONN_DEREG:

            /*  ������޿�����������ֱ�ӷ����ܴ������ */
            if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
            {
                IMSA_INFO_LOG("IMSA_StartImsEmergService:can make anonymous emc call in conn dereg!");
                TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_CONN);
                TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_NOT_REGISTER);
                *penEmcCallType = IMSA_EMC_CALL_TYPE_NO_CARD;
                return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
            }

            break;

        case IMSA_SRV_STATUS_CONN_REG:

            *penEmcCallType = IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG;
            return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;

        default:
            break;
    }


    if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
    {
        *penEmcCallType = IMSA_EMC_CALL_TYPE_NO_CARD;
    }
    else
    {
        *penEmcCallType = IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG;
    }


    return IMSA_START_SRV_RESULT_BUFFER_CALL_WAIT_INDICATION;
}
/*****************************************************************************
 Function Name  : IMSA_StartImsNormalService
 Description    : ���ƹ���ģ���ṩ������ģ���API, Callģ���ڴ�����绰ʱ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32
                  ���ؽ����0����ʾControl�����ṩ��������Call����ֱ�Ӵ�绰
                  ���ؽ����1����ʾ�����ṩ�������񣬴�����绰ʧ��
                  ���ؽ����2����ʾ��ʱ�����ṩ�����������ڽ�����������Callģ����Ҫ����绰

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
      2.wangchen 00209181    2015-11-23  Modify:volte dsds
*****************************************************************************/
VOS_VOID IMSA_StartImsEmcService
(
    VOS_VOID
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enEmcSrvStatus      = IMSA_SRV_STATUS_BUTT;

    enEmcSrvStatus      = IMSA_SRV_GetEmcSrvStatus();

    /* ���ݵ�ǰ����״̬���в�ͬ���� */
    switch (enEmcSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* ��������ģ�齨�����ӣ���״̬ת��IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_EMC);
            IMSA_SRV_SetServcieStatus(  IMSA_CONN_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            break;

        case IMSA_SRV_STATUS_CONN_DEREG:

            /* ����ע��ģ�鷢��ע�ᣬ��״̬ת��IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_CONN_TYPE_EMC,
                                        IMSA_REG_ADDR_PARAM_NEW);
            IMSA_SRV_SetServcieStatus(  IMSA_CONN_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONN_REGING);
            break;


        default:
            break;
    }

    return;
}


/*****************************************************************************
 Function Name  : IMSA_StartImsNormalService
 Description    : ���ƹ���ģ���ṩ������ģ���API, Callģ���ڴ�����绰ʱ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32
                  ���ؽ����0����ʾControl�����ṩ��������Call����ֱ�Ӵ�绰
                  ���ؽ����1����ʾ�����ṩ�������񣬴�����绰ʧ��
                  ���ؽ����2����ʾ��ʱ�����ṩ�����������ڽ�����������Callģ����Ҫ����绰

 History        :
      1.lihong 00150010      2013-07-05  Draft Enact
      2.wangchen 00209181    2015-11-23  Modify:volte dsds
*****************************************************************************/
VOS_UINT32 IMSA_StartImsEmergService
(
    IMSA_EMC_CALL_TYPE_ENUM_UINT32     *penEmcCallType
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enEmcSrvStatus      = IMSA_SRV_STATUS_BUTT;

    IMSA_INFO_LOG("IMSA_StartImsEmergService is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, LNAS_ENTRY);

    /* �жϻ�ȡ����IMS����������Ƿ�߱���������߱����򷵻ز��ܴ������ */
    if (IMSA_TRUE != IMSA_SRV_IsEmcSrvConditonSatisfied())
    {
        IMSA_INFO_LOG("IMSA_StartImsEmergService:EMC service condition not satisfied!");
        TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, 1);
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    /* ������������������Ϸ������������ֱ�ӷ����ܴ������ */
    if (IMSA_TRUE == IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied())
    {
        IMSA_INFO_LOG("IMSA_StartImsEmergService:can make emc call in normal service!");
        TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, 2);
        *penEmcCallType = IMSA_EMC_CALL_TYPE_IN_NORMAL_SRV;
        return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
    }

    enEmcSrvStatus      = IMSA_SRV_GetEmcSrvStatus();

    /* ���ݵ�ǰ����״̬���в�ͬ���� */
    switch (enEmcSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* ��������ģ�齨�����ӣ���״̬ת��IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_EMC);
            IMSA_SRV_SetServcieStatus(  IMSA_CONN_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            /* ��ʱ��ʵ�ֳɲ���������������CS���ԣ��������Ը����û��������Ϊ
               ������ʱ������·�ͷ����֮���ٽ����������� */
            IMSA_INFO_LOG("IMSA_StartImsEmergService:can not make emc call as in releasing&dereg state!");
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_NOT_REGISTER);

            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_EmcCallErrRecord(  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_EMC_REG_FAIL,
                                    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SERVICE_STATUS_ERROR,
                                    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                    VOS_FALSE,
                                    VOS_FALSE,
                                    IMSA_ERR_LOG_CALL_STATUS_IDLE);
            #endif

            return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;

        case IMSA_SRV_STATUS_CONN_DEREG:

            /*  ������޿�����������ֱ�ӷ����ܴ������ */
            if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
            {
                IMSA_INFO_LOG("IMSA_StartImsEmergService:can make anonymous emc call in conn dereg!");
                TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_CONN);
                TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_NOT_REGISTER);
                *penEmcCallType = IMSA_EMC_CALL_TYPE_NO_CARD;
                return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
            }

            /* ����ע��ģ�鷢��ע�ᣬ��״̬ת��IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_CONN_TYPE_EMC,
                                        IMSA_REG_ADDR_PARAM_NEW);
            IMSA_SRV_SetServcieStatus(  IMSA_CONN_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONN_REGING);
            break;

        case IMSA_SRV_STATUS_CONN_REG:

            IMSA_INFO_LOG("IMSA_StartImsEmergService:can make emc call in conn reg!");
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_REGISTERED);
            *penEmcCallType = IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG;
            return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;

        default:
            break;
    }


    if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
    {
        *penEmcCallType = IMSA_EMC_CALL_TYPE_NO_CARD;
    }
    else
    {
        *penEmcCallType = IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG;
    }


    return IMSA_START_SRV_RESULT_BUFFER_CALL_WAIT_INDICATION;
}
/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgPeriodTryImsSrvExpIdleDereg()
 Description    : �����Գ���IMS����ʱ����ʱ,�����ʼע��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgPeriodTryImsSrvExpIdleDereg(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != IMSA_SRV_IsNrmSrvConditonSatisfied())
    {
        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_NOT_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

           IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);

            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                    IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);

            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;
        #endif
        default:
            break;
    }
    return;
}

/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgPeriodTryImsSrvExpConnDereg()
 Description    : �����Գ���IMS����ʱ����ʱ,�����ʼע��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgPeriodTryImsSrvExpConnDereg(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    #endif
    IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32    enSrvRst    = IMSA_NRM_SRV_CON_SAT_STATUE_BUTT;

    #if (FEATURE_ON == FEATURE_DSDS)
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif
    enSrvRst                                = IMSA_SRV_IsNrmSrvConditonSatisfied();

    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != enSrvRst)
    {
        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                    IMSA_REG_ADDR_PARAM_NEXT);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_REG_ADDR_PARAM_NEXT,
                                       IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

           IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_REG_ADDR_PARAM_NEXT,
                                       IMSA_FALSE);

            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEXT);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;
        #endif
        default:
            break;
    }

}
/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgPeriodTryImsSrvExpConnDereg()
 Description    : �����Գ���IMS����ʱ����ʱ,�����ʼע��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgPeriodTryImsSrvExpConningReg(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    #endif
    IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32    enSrvStatus = IMSA_NRM_SRV_CON_SAT_STATUE_BUTT;

    #if (FEATURE_ON == FEATURE_DSDS)
    pstControlMagnaer                   = IMSA_GetControlManagerAddress();
    #endif
    enSrvStatus                         = IMSA_SRV_IsNrmSrvConditonSatisfied();


    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != enSrvStatus)
    {
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_SRV_InitDeregEventReport(IMSA_ERR_LOG_INIT_DEREG_REASON_PDN_LOST);
        #endif
        return;
    }

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndConnSetupReq(   IMSA_TRUE,
                                        IMSA_CONN_TYPE_NORMAL);

            /* ����ע��ʱ��������ʱ�� */
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_NULL:
            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

           IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                       IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                       IMSA_FALSE,
                                       IMSA_FALSE);

            IMSA_SRV_SndConnSetupReq(   IMSA_TRUE,
                                        IMSA_CONN_TYPE_NORMAL);

            /* ����ע��ʱ��������ʱ�� */
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            break;
        #endif
        default:
            break;
    }
    /* ��¼UE��������ʱ�� */
    #if (FEATURE_ON == FEATURE_PTM)
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStartConnTimerAddr()->ul32KTStampHighBit),
                                        &(IMSA_GetErrlogStartConnTimerAddr()->ul32KTStampLowBit));
    #endif
}

/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgPeriodTryImsSrvExp()
 Description    : �����Գ���IMS����ʱ����ʱ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-07-09  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgPeriodTryImsSrvExp(const VOS_VOID *pRcvMsg )
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    (void)pRcvMsg;

    IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, LNAS_ENTRY);

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    switch (IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONNING_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:conning&dereg or conn&reging!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_StopTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:releasing&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;

        case IMSA_SRV_STATUS_IDLE_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:idle&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_IDLE);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_ProcTimerMsgPeriodTryImsSrvExpIdleDereg();

            break;
        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:conn&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_ProcTimerMsgPeriodTryImsSrvExpConnDereg();

            break;
        case IMSA_SRV_STATUS_CONNING_REG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:conning&reg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_REGISTERED);
            IMSA_ProcTimerMsgPeriodTryImsSrvExpConningReg();

            break;
        default:
            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:other states!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, 1);
            break;
    }
}

/* delete PeriodImsEmcSrvTryTimer */

/*****************************************************************************
 Function Name  : IMSA_AddSubscription()
 Description    : IMSA�����ṩ��ע�ᶩ�Ľӿ�
 Input          : ulPid---------------�����ߵ�PID
                  enType--------------������������
                  ulPara--------------�������ݸ�����Ϣ��Я���Ĳ���
 Output         : pulSubscriptionId---����IDָ��
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-10  Draft Enact
*****************************************************************************/
VOS_UINT32  IMSA_AddSubscription
(
    VOS_UINT32                          ulPid,
    IMSA_SUBCRIBE_TYPE_ENUM_UINT8       enType,
    VOS_UINT32                          ulPara,
    VOS_UINT32                         *pulSubscriptionId
)
{
    IMSA_SUBSCRIPTION_INFO_STRU        *pstSubcriptionInfo      = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_AddSubscription is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, LNAS_ENTRY);

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();

    /* �ж��Ƿ��Ѿ�����������ǣ��򷵻�ʧ�� */
    if (pstSubcriptionInfoList->ulSubscriptionNum >= IMSA_MAX_SUBSCRIPTION_NUM)
    {
        IMSA_WARN_LOG("IMSA_AddSubscription:can not save more!");
        TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, 1);
        return IMSA_FAIL;
    }

    /* ���������Ƿ�Ϸ� */
    if (enType >= IMSA_SUBCRIBE_TYPE_BUTT)
    {
        IMSA_WARN_LOG("IMSA_AddSubscription:type illegal!");
        TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, LNAS_PARAM_INVALID);
        return IMSA_FAIL;
    }

    /* �ж�����ָ���Ƿ�Ϸ� */
    if (pulSubscriptionId == VOS_NULL_PTR)
    {
        IMSA_WARN_LOG("IMSA_AddSubscription:null pointer!");
        TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, LNAS_NULL_PTR);
        return IMSA_FAIL;
    }

    /* �洢ǩԼ��Ϣ */
    pstSubcriptionInfo = &pstSubcriptionInfoList->astSubcriptionInfoArray[pstSubcriptionInfoList->ulSubscriptionNum];
    pstSubcriptionInfo->ulPid               = ulPid;
    pstSubcriptionInfo->enType              = enType;
    pstSubcriptionInfo->ulPara              = ulPara;
    pstSubcriptionInfo->ulSubscriptionId    = pstSubcriptionInfoList->ulMaxSubscriptionId;
    *pulSubscriptionId                      = pstSubcriptionInfoList->ulMaxSubscriptionId;
    pstSubcriptionInfoList->ulMaxSubscriptionId++;
    pstSubcriptionInfoList->ulSubscriptionNum++;

    return IMSA_SUCC;
}

/*****************************************************************************
 Function Name  : IMSA_DeleteSubscription()
 Description    : IMSA�����ṩ��ȡ�����Ľӿ�
 Input          : ulSubscriberId---------------����ID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-07-10  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_DeleteSubscription
(
    VOS_UINT32                  ulSubscriptionId
)
{
    VOS_UINT32                          i                       = IMSA_NULL;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_DeleteSubscription is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_DeleteSubscription_ENUM, LNAS_ENTRY);

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();

    for (i = 0; i < pstSubcriptionInfoList->ulSubscriptionNum; i++)
    {
        if (ulSubscriptionId == pstSubcriptionInfoList->astSubcriptionInfoArray[i].ulSubscriptionId)
        {
            IMSA_MEM_CPY_S( &pstSubcriptionInfoList->astSubcriptionInfoArray[i],
                            sizeof(IMSA_SUBSCRIPTION_INFO_STRU)*((pstSubcriptionInfoList->ulSubscriptionNum - 1) - i),
                            &pstSubcriptionInfoList->astSubcriptionInfoArray[i+1],
                            sizeof(IMSA_SUBSCRIPTION_INFO_STRU)*((pstSubcriptionInfoList->ulSubscriptionNum - 1) - i));

            pstSubcriptionInfoList->ulSubscriptionNum--;
            return IMSA_SUCC;
        }
    }

    return IMSA_SUCC;
}


VOS_VOID IMSA_SRV_PrintNrmSrvState( VOS_VOID )
{
    switch (IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: IDLE+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_IDLE);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: CONNING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_REG:
            IMSA_INFO_LOG("Current Normal Service State: CONNING+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        case IMSA_SRV_STATUS_RELEASING_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: RELEASING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: CONN+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_INFO_LOG("Current Normal Service State: CONN+REGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_REGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_DEREGING:
            IMSA_INFO_LOG("Current Normal Service State: CONN+DEREGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_DEREGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_INFO_LOG("Current Normal Service State: CONN+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        default:
            IMSA_INFO_LOG("Current Normal Service State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}


VOS_VOID IMSA_SRV_PrintEmcSrvState( VOS_VOID )
{
    switch (IMSA_SRV_GetEmcSrvStatus())
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: IDLE+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_IDLE);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: CONNING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_REG:
            IMSA_INFO_LOG("Current Emc Service State: CONNING+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        case IMSA_SRV_STATUS_RELEASING_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: RELEASING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: CONN+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_INFO_LOG("Current Emc Service State: CONN+REGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_REGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_DEREGING:
            IMSA_INFO_LOG("Current Emc Service State: CONN+DEREGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_DEREGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_INFO_LOG("Current Emc Service State: CONN+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        default:
            IMSA_INFO_LOG("Current Emc Service State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}

/*****************************************************************************
 Function Name   : IMSA_SRV_IsConningRegState
 Description     :
 Input           : ucIsEmc---------1:������ 0:��ͨ
 Output          : None
 Return          : VOS_INT32

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsConningRegState(VOS_UINT8 ucIsEmc)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatus = IMSA_SRV_STATUS_BUTT;

    if (1 == ucIsEmc)
    {
        enImsaSrvStatus = IMSA_SRV_GetEmcSrvStatus();
    }
    else
    {
        enImsaSrvStatus = IMSA_SRV_GetNormalSrvStatus();
    }

    if (IMSA_SRV_STATUS_CONNING_REG != enImsaSrvStatus)
    {
        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}
/*****************************************************************************
 Function Name   : IMSA_CMCCDeregProcConnRegOrReging
 Description     : �й��ƶ�����������������ʱ����IMSȥע��
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181    2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CMCCDeregProcConnRegOrReging(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);

    /* ����ж�ʱ�������У��Ƿ���Ҫֹͣ��ʱ��? */
    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);

            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            break;

        case  IMSA_RESOURCE_STATUS_NULL:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            //IMSA_DsdsSaveMoSmsMsg(pstRpDataReq);
            break;
        #endif
        default:
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            break;

    }


}
/*****************************************************************************
 Function Name   : IMSA_CMCCDeregProcConnRegOrReging
 Description     : �й��ƶ�����������������ʱ����IMSȥע��
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181    2015-12-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CMCCDeregProcConnOrConningDereg(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        case IMSA_RESOURCE_STATUS_ACTIVE:
            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            #endif
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
                IMSA_StartTimer(&pstControlMagnaer->stDeregSerProtectTimer);
            }
            break;

        case  IMSA_RESOURCE_STATUS_NULL:

            IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                          IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                          VOS_FALSE,
                                          VOS_FALSE);

            //IMSA_DsdsSaveMoSmsMsg(pstRpDataReq);
            break;
        #endif
        default:
            #if (FEATURE_ON == FEATURE_DSDS)
            IMSA_DsdsModifyTaskSrcByTaskType(IMSA_RF_RES_APPLY_TRIGER_SRC_DEREG,
                                             RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            #endif
            break;

    }

}

/*****************************************************************************
 Function Name   : IMSA_CMCCDeregProc
 Description     : �й��ƶ�����������������ʱ����IMSȥע��
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.mengchao 00277840    2014-08-20  Draft Enact
    2.wangchen 00209181    2015-06-23  Modify:CONNING_REG
    3.wangchen 00209181    2016-04-01  Modify:CHR REPORT
*****************************************************************************/
VOS_VOID IMSA_CMCCDeregProc(VOS_VOID)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    #endif

    if (VOS_FALSE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
    {
        IMSA_INFO_LOG("CMCC Custom Dereg Flag is false.");
        TLPS_PRINT2LAYER_INFO(IMSA_CMCCDeregProc_ENUM, 1);
        return;
    }

    if (MSCC_IMSA_IMS_VOPS_SUPPORT == IMSA_GetNetInfoAddress()->enImsaImsVoPsStatus)
    {
        IMSA_INFO_LOG("VoPS support.");
        TLPS_PRINT2LAYER_INFO(IMSA_CMCCDeregProc_ENUM, 2);
        return;
    }

    /* �������ƶ���������VOLTEͨ���������ƶ���GU�£�RAU�ɹ�����Ҫ��������ȥע������;
    ����ͨ���������ƶ�����֧��VOLTE��LС������Ҫ�ȵ绰���� */
    if (((MSCC_IMSA_ACCESS_TYPE_EUTRAN_TDD == IMSA_GetNetInfoAddress()->enAccessType) ||
          (MSCC_IMSA_ACCESS_TYPE_EUTRAN_FDD == IMSA_GetNetInfoAddress()->enAccessType)) &&
         (VOS_TRUE == IMSA_IsImsExist()))
    {
        IMSA_INFO_LOG("IMS call/sms/ss running. will dereg later.");
        TLPS_PRINT2LAYER_INFO(IMSA_CMCCDeregProc_ENUM, 3);
        return;
    }




    IMSA_INFO_LOG1("IMSA_CMCCDeregProc: Service status: ", IMSA_SRV_GetNormalSrvStatus());
    TLPS_PRINT2LAYER_INFO1(IMSA_CMCCDeregProc_ENUM, 4, IMSA_SRV_GetNormalSrvStatus());
    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_CMCCDeregProcConnRegOrReging();
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_RegFailEventReport(IMSA_ERR_LOG_REG_FAIL_REASON_MOVE_TO_NOT_SUP_IMS_RAT,
                                    IMSA_FALSE,
                                    IMSA_FALSE,
                                    IMSA_FALSE);
            #endif
            break;

        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_CMCCDeregProcConnRegOrReging();
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_SRV_InitDeregEventReport(IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT);
            #endif
            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_CMCCDeregProcConnOrConningDereg();
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_SRV_InitDeregEventReport(IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT);
            #endif
            break;

        case IMSA_SRV_STATUS_CONNING_REG:
            /* ��Ҫ֪ͨIMS�����䷢����֪ͨ���𱾵�ע�� */
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            /* �ͷ���Դ */
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
                IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            }
            #endif
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_SRV_InitDeregEventReport(IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT);
            #endif
            break;
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* �����״̬�£���������ע����Դ����ԭ��ֵΪ��ȡ��ͨ�������ͷ���Դ */
            #if (FEATURE_ON == FEATURE_DSDS)
            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            }
            #endif
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
            #endif
            break;
        default:
            break;
    }
}
/*****************************************************************************
 Function Name   : IMSA_CommonDeregProc
 Description     : ���κ����ƶ���������ͨ��ȥע������
 Input           : VOS_VOID
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
    1.zhaochen 00308719    2015-08-26  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CommonDeregProc(VOS_VOID)
{

    IMSA_CMCCDeregProc();
    IMSA_SRV_ProcWhenRoamNotSatisfied();

    return;
}

/*****************************************************************************
 Function Name  : IMSA_IsStopImsEmcService
 Description    : ���ݽ�������״̬���ж��Ƿ�ֹͣ��������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.xiongxianghui 00253310      2015-09-01  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_IsImsEmcServiceEstablishSucc(VOS_VOID)
{
    VOS_UINT32    ulResult = IMSA_FALSE;

    IMSA_INFO_LOG("IMSA_IsStopImsEmcService is enter!");

    if ((IMSA_SRV_STATUS_CONNING_DEREG == IMSA_SRV_GetEmcSrvStatus()) ||
        (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus()))
    {
        ulResult = IMSA_FALSE;
    }
    else if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        ulResult = IMSA_TRUE;
    }
    else
    {
        IMSA_INFO_LOG("IMSA_IsStopImsEmcService:other status!");
    }


    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_StopImsEmcService
 Description    : CONNING+DEREG��CONN+REGINGֹͣ��������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-09-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_StopImsEmcService(VOS_VOID)
{
    IMSA_INFO_LOG("IMSA_StopImsEmcService is enter!");

    switch(IMSA_SRV_GetEmcSrvStatus())
    {
        case IMSA_SRV_STATUS_CONNING_DEREG:
            IMSA_INFO_LOG("IMSA_SRV_ProcEmcTcallTimerExp:CONNING_DEREG!");

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_EMC,
                                   IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            /* ״̬ת��RELEASE+DEREG̬��֪ͨCALL�������񲻾߱� */
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC,
                                      IMSA_SRV_STATUS_RELEASING_DEREG);

            /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

            break;
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_INFO_LOG("IMSA_SRV_ProcEmcTcallTimerExp:CONN_REGING!");

            /* ��Ҫ����ȥע�� */
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREGING);
            break;
        default:
            IMSA_INFO_LOG("IMSA_StopImsEmcService:other status!");
            break;
    }

}
#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcVoiceDomainChangeInd
 Description    : MMA VOICE DOMAIN��Ϣ�����Ϣ������
 Input          : pstVoiceDomainChangeInd-----------VOICE DOMAIN CHANGE IND��Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-02-26  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsNotNeedNwDereg
(
    VOS_VOID
)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;

    IMSA_INFO_LOG("IMSA_SRV_ProcVoiceDomainChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcVoiceDomainChangeInd_ENUM, LNAS_ENTRY);

    pstControlManager = IMSA_GetControlManagerAddress();

    if (IMSA_SRV_STATUS_IDLE_DEREG == IMSA_SRV_GetNormalSrvStatus())
    {
        return IMSA_TRUE;
    }

    if (IMSA_SRV_STATUS_CONNING_REG == IMSA_SRV_GetNormalSrvStatus())
    {
        /* ��Ҫ֪ͨIMS ��������Ȼ�󱾵�ȥע�� */
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

        IMSA_StopTimer(&pstControlManager->stPeriodImsSrvTryTimer);

        IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                    IMSA_DEREG_LOCAL);

        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcVoiceDomainChangeInd
 Description    : MMA VOICE DOMAIN��Ϣ�����Ϣ������
 Input          : pstVoiceDomainChangeInd-----------VOICE DOMAIN CHANGE IND��Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-02-26  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcStopMsgWhenNoRf
(
    VOS_VOID
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcVoiceDomainChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcVoiceDomainChangeInd_ENUM, LNAS_ENTRY);

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        /* ����Ҫ֪ͨIMS����ȥע�ἴ�ɣ������Ƿ���Ҫɾ��,���յ�IMS�ػ���Ӧ�󣬸��ݹػ�
        ���;����Ƿ�Ҫ֪ͨAPSɾ�� */
        case IMSA_SRV_STATUS_CONN_REGING:
        case IMSA_SRV_STATUS_CONN_DEREGING:
        case IMSA_SRV_STATUS_CONN_REG:

            IMSA_RegNotifyImsLocalDereg();
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : IMSA_SRV_ProcRegResourceApplyCnf
 ��������  : DSDS����ע����Դ�ɹ���Ĵ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 IMSA_SRV_ProcGetNormSevResourceApplyCnf
(
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus      = IMSA_SRV_STATUS_BUTT;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();
    pstControlMagnaer = IMSA_GetControlManagerAddress();

    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != IMSA_SRV_IsNrmSrvConditonSatisfied())
    {
        return IMSA_FALSE;
    }

    /* ���ݵ�ǰ����״̬���в�ͬ���� */
    switch (enNrmSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* ��������ģ�齨�����ӣ���״̬ת��IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);

            /* ����ע��ʱ��������ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);

            break;

        case IMSA_SRV_STATUS_CONN_DEREG:
            /* �����ǰ״̬ΪACTIVE����ֱ�ӷ���ע�� */
            /* ����ע��ģ�鷢��ע�ᣬ��״̬ת��IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        enAddrType);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            /* ����ע��ʱ��������ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;

        case IMSA_SRV_STATUS_CONNING_REG:
            /* ��������ģ�齨������ */
            IMSA_SRV_SndConnSetupReq(   IMSA_TRUE,
                                        IMSA_CONN_TYPE_NORMAL);

            /* ����ע��ʱ��������ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;

        default:
            /* ��ӡ״̬ */
            return IMSA_FALSE;
    }
    return IMSA_TRUE;
}
/*****************************************************************************
 �� �� ��  : IMSA_SRV_ProcRegResourceApplyCnf
 ��������  : DSDS����ע����Դ�ɹ���Ĵ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 IMSA_SRV_ProcPeriodRegResourceApplyCnf
(
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus      = IMSA_SRV_STATUS_BUTT;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();
    pstControlMagnaer = IMSA_GetControlManagerAddress();

    if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC != IMSA_SRV_IsNrmSrvConditonSatisfied())
    {
        return IMSA_FALSE;
    }

    /* ���ݵ�ǰ����״̬���в�ͬ���� */
    switch (enNrmSrvStatus)
    {
        case IMSA_SRV_STATUS_CONN_REGING:
            /* �����ǰ״̬ΪACTIVE����ֱ�ӷ���ע�� */
            /* ����ע��ģ�鷢��ע�ᣬ��״̬ת��IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        enAddrType);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            /* ����ע��ʱ��������ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;

        default:
            /* ��ӡ״̬ */
            return IMSA_FALSE;
    }
    return IMSA_TRUE;
}

/*****************************************************************************
 �� �� ��  : IMSA_SRV_ProcRegResourceApplyCnf
 ��������  : DSDS����ע����Դ�ɹ���Ĵ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  IMSA_SRV_ProcGetNorServiceResourceApplyExp
(
    VOS_VOID
)
{
    switch (IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE, IMSA_CONN_IsExitPersistentBearer());
            break;
        case IMSA_SRV_STATUS_CONNING_REG:

            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
            break;

        case IMSA_SRV_STATUS_CONN_REGING:

            //IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE, IMSA_CONN_IsExitPersistentBearer());
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREG);
            break;

        default:
            break;
    }
}


VOS_UINT32 IMSA_SRV_ProcPeriodRegResourceApplyExp
(
    VOS_VOID
)
{
    switch (IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_DEREG);

            break;

        case IMSA_SRV_STATUS_CONNING_REG:

            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            break;

        default:
            /* ��ӡ״̬ */
            return IMSA_FALSE;
    }
    return IMSA_TRUE;
}

/*****************************************************************************
 �� �� ��  : IMSA_SRV_ProcRegResourceApplyCnf
 ��������  : DSDS����ע����Դ�ɹ���Ĵ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 IMSA_SRV_ProcDeRegResourceApplyCnf
(
    VOS_VOID
)
{
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_DEREGING:
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            //IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:
            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;

        default:
            return IMSA_FALSE;
    }
    return IMSA_TRUE;
}
/*****************************************************************************
 �� �� ��  : IMSA_SRV_ProcRegResourceApplyCnf
 ��������  : DSDS����ע����Դ�ɹ���Ĵ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 IMSA_SRV_ProcDeRegResourceApplyTimerExp
(
    VOS_VOID
)
{
    IMSA_CONTROL_MANAGER_STRU                  *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_DEREGING:
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            return IMSA_TRUE;

        case IMSA_SRV_STATUS_RELEASING_DEREG:


            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);
            break;

        default:
            break;
    }
    return IMSA_FALSE;
}


/*****************************************************************************
 �� �� ��  : IMSA_SRV_ProcRegResourceApplyTimerExp
 ��������  : DSDS����ע����Դ��ʱ����ʱ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcGetSrvTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcGetSrvTimerExp:enter!");

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_REGING:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREG);

            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);

            /* �������ڳ��Զ�ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

            break;

        case IMSA_SRV_STATUS_CONNING_DEREG:
            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);

            /* �������ڳ��Զ�ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

            break;

        default:
            break;
    }
    if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
    {
        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
    }
    return;

}

/*****************************************************************************
 �� �� ��  : IMSA_SRV_ProcRegResourceApplyTimerExp
 ��������  : DSDS����ע����Դ��ʱ����ʱ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcDeregSrvTimerExp
(
    const VOS_VOID                     *pMsg
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcDeregSrvTimerExp:enter!");

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_DEREGING:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);

            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            }
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

            IMSA_StopTimer(&pstControlMagnaer->stGetSerProtectTimer);

            if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
            {
                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER);
            }
            break;

        default:
            break;
    }
    return;

}

#endif

/*****************************************************************************
 Function Name  : IMSA_StartTempForbTimer
 Description    : ����TI_IMSA_TEMP_FORBIDDEN_TIMER��ʱ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_StartTempForbTimer(VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    /* �޸Ķ�ʱ��ʱ�� */
    pstControlMagnaer->stTempForbiddenTimer.ulTimerLen = LMM_Get3402TimerLen();

    /* ������ʱ�� */
    IMSA_StartTimer(&pstControlMagnaer->stTempForbiddenTimer);
}

/*****************************************************************************
 Function Name  : IMSA_IsTempForbTimerRunning
 Description    : �ж�TI_IMSA_TEMP_FORBIDDEN_TIMER��ʱ���Ƿ�����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_FALSE--------��ʱ��δ����
                  VOS_TRUE---------��ʱ����������

 History        :
      1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_IsTempForbTimerRunning(VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = VOS_FALSE;

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    ulRslt = IMSA_IsTimerRunning(&pstControlMagnaer->stTempForbiddenTimer);

    return ulRslt;
}

/*****************************************************************************
 Function Name  : IMSA_ProcTimerMsgTempForbTimerExp
 Description    : TI_IMSA_TEMP_FORBIDDEN_TIMER��ʱ����ʱ����
 Input          : pRcvMsg----------��ʱ����ʱ��Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641      2015-12-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTimerMsgTempForbTimerExp(const VOS_VOID *pRcvMsg )
{
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus;

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();

    /* �ö�ʱ����ʱʱ, ����ǰ����IMSA_SRV_STATUS_IDLE_DEREG̬, ����CONN�������� */
    if (IMSA_SRV_STATUS_IDLE_DEREG == enNrmSrvStatus)
    {
        IMSA_ProcTimerMsgPeriodTryImsSrvExpIdleDereg();
    }

    return;
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 Function Name   :IMSA_SRV_GetTimeDiffByStampWithMillSecondUnit
 Description     : ��������32Kʱ��������ֵ�����ص�λ����Ϊ����
 Input           :
 Output          : None
 Return          :

 History         :
    1.wangchen 00209181     2016-03-31  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_SRV_GetTimeDiffByStampWithMillSecondUnit(const LPS_32K_TIMESTAMP *pstOldTStamp,const LPS_32K_TIMESTAMP *pstNewTStamp)
{
    VOS_UINT32   ulHighDiff = pstNewTStamp->ul32KTStampHighBit - pstOldTStamp->ul32KTStampHighBit;
    VOS_UINT32   ulowDiff;
    VOS_UINT32   ulHighInterval;
    VOS_UINT32   ulLowDiffRight15Bit;
    VOS_UINT32   ulLowDiffLeft17Bit;

    if(pstNewTStamp->ul32KTStampHighBit < pstOldTStamp->ul32KTStampHighBit)
    {
        LPS_OM_INFO_LOG2( "IMSA_SRV_GetTimeDiffByStampWithMillSecondUnit return 0 !oldhi=,newhi=",
                           pstOldTStamp->ul32KTStampHighBit,
                           pstNewTStamp->ul32KTStampHighBit);
        return 0;
    }

    if ((ulHighDiff == 0) && ( pstNewTStamp->ul32KTStampLowBit < pstOldTStamp->ul32KTStampLowBit))
    {
        LPS_OM_INFO_LOG2( "IMSA_SRV_GetTimeDiffByStampWithMillSecondUnit return 0 ! oldlo=,newlow=",
                           pstOldTStamp->ul32KTStampLowBit,pstNewTStamp->ul32KTStampLowBit);
        return 0;
    }

    /*��λ��ֵ�ﵽ���ֱ�ӷ������ʱ����ֹ���*/
    if (ulHighDiff >= TLPS_32TSTAMP_MAX_HIGH_VAL_MILL_SECOND)
    {
        LPS_OM_INFO_LOG2( "IMSA_SRV_GetTimeDiffByStampWithMillSecondUnit hiout",
                           pstOldTStamp->ul32KTStampHighBit,
                           pstNewTStamp->ul32KTStampHighBit);
        return PS_NULL_UINT32;
    }

    if (pstNewTStamp->ul32KTStampLowBit < pstOldTStamp->ul32KTStampLowBit)
    {
       ulHighInterval = (ulHighDiff-1) << TLPS_32TSTAMP_HIGHBIT_MOVE_BIT_IN_SECOND;
       ulowDiff       = (VOS_UINT32)(0xFFFFFFFFUL  - pstOldTStamp->ul32KTStampLowBit + pstNewTStamp->ul32KTStampLowBit + 1);
    }
    else
    {
       ulHighInterval = ulHighDiff << TLPS_32TSTAMP_HIGHBIT_MOVE_BIT_IN_SECOND;
       ulowDiff       = (VOS_UINT32)(pstNewTStamp->ul32KTStampLowBit  - pstOldTStamp->ul32KTStampLowBit);
    }

    ulLowDiffRight15Bit = ((ulowDiff & 0x00007FFF) * 1000) >> TLPS_32TSTAMP_ACCURACY_MOVE_BIT_IN_SECOND ;
    ulLowDiffLeft17Bit  = (ulowDiff & 0xFFFF8000) >> TLPS_32TSTAMP_ACCURACY_MOVE_BIT_IN_SECOND ;

    return ulHighInterval*1000 + ulLowDiffLeft17Bit*1000 + ulLowDiffRight15Bit;
}

/*****************************************************************************
 �� �� ��  : IMSA_NotInitRegEventReport
 ��������  : ��¼IMSA������ע���ԭ��ֵ,�����ϱ�
 �������  : enRegFailReason  ע��ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��06��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_NotInitRegEventReport
(
    IMSA_ERR_LOG_NOT_INIT_IMS_REG_REASON_ENUM_UINT16    enNotInitRegReason
)
{
    IMSA_ERR_LOG_ALM_IMS_REG_FAIL_EVENT_REPORT_STRU stImsNotInitRegEvent;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usLevel;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();

    TLPS_PRINT2LAYER_INFO(IMSA_NotInitRegEventReport_ENUM, LNAS_ENTRY);

    /* SERVICE ״̬ΪIDLE+DEREGʱ���Ž����ϱ� */
    if (IMSA_SRV_STATUS_IDLE_DEREG != IMSA_SRV_GetNormalSrvStatus())
    {
        TLPS_PRINT2LAYER_WARNING(IMSA_NotInitRegEventReport_ENUM, IMSA_STATE_ERROR);
        return;
    }

    /* ��TAU������SERVICE CHANG IND��Ϣ�����ϱ�CHR */
    if(IMSA_OP_TRUE == pstControlMagnaer->bitRegSuccProcTypeValid)
    {
        /*����Ĵ��������:����TAU���̵ĸ���Ϣֱ�Ӷ��������ٴ���CHR�ϱ�*/
        if((IMSA_MSCC_TAU_UNREAL_PROC == IMSA_GetRegSuccProcType())
            ||(IMSA_MSCC_REG_PROC_BUTT == IMSA_GetRegSuccProcType()))
        {
               return;
        }
    }

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel             = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_IMS_REG_FAIL_EVENT_REPORT);
    ulIsLogRecord       = IMSA_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_ALM_IMS_REG_FAIL_EVENT_REPORT_STRU);

    IMSA_MEM_SET_S(&stImsNotInitRegEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsNotInitRegEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_IMS_REG_FAIL_EVENT_REPORT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsNotInitRegEvent.enImsRegFailReason =  IMSA_OM_IMS_REG_FAIL_REASON_NOT_INIT_IMS_REG;
    stImsNotInitRegEvent.stNotInitRegReason.enNotInitRegReason = enNotInitRegReason;

    IMSA_SndAcpuOmFaultErrLogInd(   &stImsNotInitRegEvent,
                                    ulLength,
                                    IMSA_ERR_LOG_ALM_IMS_REG_FAIL_EVENT_REPORT);

    return;
}
/*****************************************************************************
 �� �� ��  : IMSA_PdnConnTimerExpireEventReport
 ��������  : IMS���ؽ���ʱ�䳬ʱ�¼��ϱ�
 �������  : enRegFailReason  ע��ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-03-31
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_PdnConnTimerExpireEventReport
(
    VOS_VOID
)
{
    IMSA_ERR_LOG_ALM_IMS_REG_TIMER_EXPIRE_EVENT_REPORT_STRU stImsTimerExpireEvent;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usLevel;
    IMSA_ERRORLOG_MANAGER_STRU         *pstImsaErrorlogManager   = VOS_NULL_PTR;
    VOS_UINT32                          ulMillSecondDiff;

    TLPS_PRINT2LAYER_INFO(IMSA_PdnConnTimerExpireEventReport_ENUM, LNAS_ENTRY);

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel                 = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_IMS_REG_TIMER_EXPIRE_EVENT_REPORT);
    ulIsLogRecord           = IMSA_IsErrLogNeedRecord(usLevel);
    pstImsaErrorlogManager  = IMSA_GetErrorlogManagerAddress();

    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    /* ������ؽ���ʱ��û�г�����ֵ����ֱ���˳� */
    ulMillSecondDiff = IMSA_SRV_GetTimeDiffByStampWithMillSecondUnit(&pstImsaErrorlogManager->stStartConnTStamp,
                                                                     &pstImsaErrorlogManager->stStopConnTStamp);

    TLPS_PRINT2LAYER_INFO1(IMSA_PdnConnTimerExpireEventReport_ENUM, IMSA_Conn_Meas_Time_Interval,
                            ulMillSecondDiff);

    if (pstImsaErrorlogManager->ulPdnConnTimeThreshold > ulMillSecondDiff)
    {
        return;
    }
    ulLength = sizeof(IMSA_ERR_LOG_ALM_IMS_REG_TIMER_EXPIRE_EVENT_REPORT_STRU);

    IMSA_MEM_SET_S(&stImsTimerExpireEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsTimerExpireEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_IMS_REG_TIMER_EXPIRE_EVENT_REPORT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsTimerExpireEvent.enTimeExpireReason    = IMSA_OM_IMS_TIMER_EXPIRE_REASON_PDN_CONN;
    stImsTimerExpireEvent.ulPdnConnTimerLen     = ulMillSecondDiff;

    IMSA_SndAcpuOmFaultErrLogInd(   &stImsTimerExpireEvent,
                                    ulLength,
                                    IMSA_ERR_LOG_ALM_IMS_REG_TIMER_EXPIRE_EVENT_REPORT);

    return;
}
/*****************************************************************************
 �� �� ��  : IMSA_RegTimerExpireEventReport
 ��������  : IMSע��ʱ�䳬ʱ�¼��ϱ�
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-03-31
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_RegTimerExpireEventReport
(
    VOS_VOID
)
{
    IMSA_ERR_LOG_ALM_IMS_REG_TIMER_EXPIRE_EVENT_REPORT_STRU stImsTimerExpireEvent;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usLevel;
    IMSA_ERRORLOG_MANAGER_STRU         *pstImsaErrorlogManager   = VOS_NULL_PTR;
    VOS_UINT32                          ulMillSecondDiff;

    TLPS_PRINT2LAYER_INFO(IMSA_RegTimerExpireEventReport_ENUM, LNAS_ENTRY);

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel                 = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_IMS_REG_TIMER_EXPIRE_EVENT_REPORT);
    ulIsLogRecord           = IMSA_IsErrLogNeedRecord(usLevel);
    pstImsaErrorlogManager  = IMSA_GetErrorlogManagerAddress();

    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    /* ������ؽ���ʱ��û�г�����ֵ����ֱ���˳� */
    ulMillSecondDiff = IMSA_SRV_GetTimeDiffByStampWithMillSecondUnit(&pstImsaErrorlogManager->stStartRegTStamp,
                                                                     &pstImsaErrorlogManager->stStopRegTStamp);

    TLPS_PRINT2LAYER_INFO1(IMSA_RegTimerExpireEventReport_ENUM, IMSA_Reg_Meas_Time_Interval,
                            ulMillSecondDiff);

    if (pstImsaErrorlogManager->ulRegTimeThreshold > ulMillSecondDiff)
    {
        return;
    }
    ulLength = sizeof(IMSA_ERR_LOG_ALM_IMS_REG_TIMER_EXPIRE_EVENT_REPORT_STRU);

    IMSA_MEM_SET_S(&stImsTimerExpireEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsTimerExpireEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_IMS_REG_TIMER_EXPIRE_EVENT_REPORT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsTimerExpireEvent.enTimeExpireReason    = IMSA_OM_IMS_TIMER_EXPIRE_REASON_REG;
    stImsTimerExpireEvent.ulImsRegTimerLen      = ulMillSecondDiff;

    IMSA_SndAcpuOmFaultErrLogInd(   &stImsTimerExpireEvent,
                                    ulLength,
                                    IMSA_ERR_LOG_ALM_IMS_REG_TIMER_EXPIRE_EVENT_REPORT);

    return;
}
/*****************************************************************************
 �� �� ��  : IMSA_SRV_RegSuccEventReport
 ��������  : IMSע��ɹ��¼��ϱ�
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-03-31
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_SRV_RegSuccEventReport
(
    VOS_VOID
)
{
    IMSA_ERR_LOG_ALM_IMS_REG_SUCC_EVENT_REPORT_STRU stImsRegSuccEvent;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usLevel;
    IMSA_ERRORLOG_MANAGER_STRU         *pstImsaErrorlogManager   = VOS_NULL_PTR;
    VOS_UINT32                          ulConnMillSecondDiff;
    VOS_UINT32                          ulRegMillSecondDiff;

    TLPS_PRINT2LAYER_INFO(IMSA_SRV_RegSuccEventReport_ENUM, LNAS_ENTRY);

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel                 = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_IMS_REG_SUCC_EVENT_REPORT);
    ulIsLogRecord           = IMSA_IsErrLogNeedRecord(usLevel);
    pstImsaErrorlogManager  = IMSA_GetErrorlogManagerAddress();

    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    /* ������ؽ���ʱ��û�г�����ֵ����ֱ���˳� */
    ulConnMillSecondDiff = IMSA_SRV_GetTimeDiffByStampWithMillSecondUnit(&pstImsaErrorlogManager->stStartConnTStamp,
                                                                         &pstImsaErrorlogManager->stStopConnTStamp);

    ulRegMillSecondDiff = IMSA_SRV_GetTimeDiffByStampWithMillSecondUnit(&pstImsaErrorlogManager->stStartRegTStamp,
                                                                        &pstImsaErrorlogManager->stStopRegTStamp);

    ulLength = sizeof(IMSA_ERR_LOG_ALM_IMS_REG_SUCC_EVENT_REPORT_STRU);

    IMSA_MEM_SET_S(&stImsRegSuccEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsRegSuccEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_IMS_REG_SUCC_EVENT_REPORT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsRegSuccEvent.ulPdnConnTimerLen = ulConnMillSecondDiff;
    stImsRegSuccEvent.ulImsRegTimerLen  = ulRegMillSecondDiff;

    IMSA_SndAcpuOmFaultErrLogInd(   &stImsRegSuccEvent,
                                    ulLength,
                                    IMSA_ERR_LOG_ALM_IMS_REG_SUCC_EVENT_REPORT);

    return;
}

/*****************************************************************************
 �� �� ��  : IMSA_SRV_InitDeregEventReport
 ��������  : UE����������ȥ�����¼��ϱ�
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016-03-31
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_SRV_InitDeregEventReport
(
    IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM_UINT32  enInitDeregCause
)
{
    IMSA_ERR_LOG_ALM_IMS_INIT_DEREG_EVENT_REPORT_STRU stImsInitDeregEvent;
    VOS_UINT32                          ulIsLogRecord;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel                 = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_IMS_INIT_DEREG_EVENT_REPORT);
    ulIsLogRecord           = IMSA_IsErrLogNeedRecord(usLevel);

    TLPS_PRINT2LAYER_INFO(IMSA_SRV_InitDeregEventReport_ENUM, LNAS_ENTRY);

    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    /* ������ؽ���ʱ��û�г�����ֵ����ֱ���˳� */
    ulLength = sizeof(IMSA_ERR_LOG_ALM_IMS_INIT_DEREG_EVENT_REPORT_STRU);

    IMSA_MEM_SET_S(&stImsInitDeregEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsInitDeregEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_IMS_INIT_DEREG_EVENT_REPORT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsInitDeregEvent.enInitDeregCause = enInitDeregCause;

    IMSA_SndAcpuOmFaultErrLogInd(   &stImsInitDeregEvent,
                                    ulLength,
                                    IMSA_ERR_LOG_ALM_IMS_INIT_DEREG_EVENT_REPORT);

    return;
}

#endif
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcSmsRsltRestoration
 Description    : IMSA�ڲ���ϢID_IMSA_CALL_RESULT_ACTION_IND������
 Input          : pstCallRsltActionIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641   2016-05-213  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcSmsRsltRestoration
(
    const IMSA_SMS_RESULT_ACTION_IND_STRU *pstSmsRsltActionIndMsg
)
{
    #if (FEATURE_ON == FEATURE_DSDS)
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = IMSA_GetControlManagerAddress();
    #endif

    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcSmsRsltRestoration:restoration,normal status is not CONN&REG!");
        TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcSmsRsltRestoration_ENUM, IMSA_STATE_ERROR, 3);
        return ;
    }

    if (IMSA_RESOURCE_STATUS_ACTIVE == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                    IMSA_DEREG_LOCAL);

        IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                    IMSA_REG_ADDR_PARAM_RESTORATION);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                    IMSA_SRV_STATUS_CONN_REGING);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
        }
        #endif
    }
    #if (FEATURE_ON == FEATURE_DSDS)
    else if (IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF == IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER))
    {
        IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                     IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                     IMSA_REG_ADDR_PARAM_RESTORATION,
                                     IMSA_FALSE);

        IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                IMSA_DEREG_LOCAL);

        IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                    IMSA_REG_ADDR_PARAM_RESTORATION);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                    IMSA_SRV_STATUS_CONN_REGING);

        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            IMSA_StartTimer(&pstControlMagnaer->stGetSerProtectTimer);
        }
    }
    else
    {
        IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_REGISTER,
                                      IMSA_RF_RES_APPLY_TRIGER_SRC_GET_NOR_SRV,
                                      IMSA_REG_ADDR_PARAM_RESTORATION,
                                      IMSA_FALSE);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL,
                                IMSA_DEREG_LOCAL);

        IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                    IMSA_SRV_STATUS_CONN_REGING);
    }
    #endif
    /* �����Ѿ�֪ͨע��ģ����б���ȥע�ᣬ�������֪ͨCALLģ���޷���
       ���򱾵�ȥע�����̺��ͷ�CALL����ͬʱ���У����׳����� */

    /* ��¼UE����ȥע���¼���������ע���ʱ�� */
    #if (FEATURE_ON == FEATURE_PTM)
    /* ��¼UE����ע���ʱ�� */
    ( VOS_VOID )LPS_OM_GET32K_TIMESTAMP(&(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampHighBit),
                                        &(IMSA_GetErrlogStartRegTimerAddr()->ul32KTStampLowBit));
    #endif

    return;
}
/*****************************************************************************
 Function Name  : IMSA_SRV_ProcSmsRsltActionIndMsg
 Description    : IMSA�ڲ���ϢID_IMSA_SMS_RESULT_ACTION_IND������
 Input          : pstCallRsltActionIndMsg--------------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2016-04-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SRV_ProcSmsRsltActionIndMsg
(
    const IMSA_SMS_RESULT_ACTION_IND_STRU *pstSmsRsltActionIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcSmsRsltActionIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcSmsRsltActionIndMsg_ENUM, LNAS_ENTRY);

    switch (pstSmsRsltActionIndMsg->enResultAction)
    {
        case IMSA_RESULT_ACTION_REG_RESTORATION:
            IMSA_SRV_ProcSmsRsltRestoration(pstSmsRsltActionIndMsg);
            break;

        default:

            IMSA_WARN_LOG("IMSA_SRV_ProcSmsRsltActionIndMsg:illegal result action!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcSmsRsltActionIndMsg_ENUM, LNAS_ERROR);

            break;
    }
}
/*lint +e961*/

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaServiceManagement.c */



