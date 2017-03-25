/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcProcNvim.h
  �� �� ��   : ����
  ��    ��   : z00161729
  ��������   : 2011��7��14��
  ����޸�   :
  ��������   : NasMmcProcNvim.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��7��14��
    ��    ��   : z00161729
    �޸�����   : �����ļ�
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ�ɾ��GMM/MM/MMC����NVIM_EPLMN�����ඨ��
******************************************************************************/
#ifndef _NAS_MMC_PROC_NVIM_H
#define _NAS_MMC_PROC_NVIM_H

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "NasMmlCtx.h"
#include  "NasMmcCtx.h"
#include  "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MMC_NV_ITEM_ACTIVE          (1)                                     /* NV��� */
#define NAS_MMC_NV_ITEM_DEACTIVE        (0)                                     /* NV��δ���� */

/* GPRS GEA �㷨֧�ֺ궨�� */
#define NAS_MMC_GPRS_GEA1_SUPPORT       (0x01)                                  /* ֧��GPRS GEA1�㷨 */
#define NAS_MMC_GPRS_GEA1_VALUE         (0x80)                                  /* ֧��GEA1ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA2_VALUE         (0x40)                                  /* ֧��GEA2ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA3_VALUE         (0x20)                                  /* ֧��GEA3ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA4_VALUE         (0x10)                                  /* ֧��GEA4ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA5_VALUE         (0x08)                                  /* ֧��GEA5ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA6_VALUE         (0x04)                                  /* ֧��GEA6ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA7_VALUE         (0x02)                                  /* ֧��GEA7ʱ����������ֵ */

#define NAS_MMC_GPRS_GEA2_SUPPORT       (0x02)                                  /* ֧��GPRS GEA2�㷨 */
#define NAS_MMC_GPRS_GEA3_SUPPORT       (0x04)                                  /* ֧��GPRS GEA3�㷨 */
#define NAS_MMC_GPRS_GEA4_SUPPORT       (0x08)                                  /* ֧��GPRS GEA4�㷨 */
#define NAS_MMC_GPRS_GEA5_SUPPORT       (0x10)                                  /* ֧��GPRS GEA5�㷨 */
#define NAS_MMC_GPRS_GEA6_SUPPORT       (0x20)                                  /* ֧��GPRS GEA6�㷨 */
#define NAS_MMC_GPRS_GEA7_SUPPORT       (0x40)                                  /* ֧��GPRS GEA7�㷨 */
#define NAS_MMC_NVIM_MAX_EPLMN_NUM      (16)                                    /* en_NV_Item_EquivalentPlmn NV�е�Чplmn���� */
#define NAS_MMC_NVIM_MAX_MCC_SIZE       (3)                                     /* plmn��Mcc��󳤶� */
#define NAS_MMC_NVIM_MAX_MNC_SIZE       (3)                                     /* plmn��Mnc��󳤶� */
#define NAS_MMC_LOW_BYTE_MASK           (0x0f)

#define NAS_MMC_MAX_USER_CFG_IMSI_PLMN_NUM                  (6)                 /* �û����õ�����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MMC_MAX_USER_CFG_EHPLMN_NUM                     (6)                 /* �û����õ�EHplmn�ĸ��� */
#define NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM            (8)                 /* ��ֹ���뼼����PLMN ID�������� */

#define NAS_MMC_CMCC_PLMN_LIST                              (4)
#define NAS_MMC_UNICOM_PLMN_LIST                            (3)
#define NAS_MMC_CT_PLMN_LIST                                (2)

#define NAS_MCC_NVIM_PHASE_ONE_DEFUALT_SLEEP_TIME_LEN               (1)
#define NAS_MCC_NVIM_PHASE_TWO_DEFAULT_SLEEP_TIME_LEN               (40)
#define NAS_MCC_NVIM_PHASE_ONE_DEFAULT_FULL_BAND_NUM                (1)
#define NAS_MCC_NVIM_PHASE_TWO_DEFAULT_FULL_BAND_NUM                (1)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum NAS_MMC_HPLMN_TYPE_ENUM
{
    NAS_MMC_HPLMN_TYPE_CMCC                     = 0,            /*�й��ƶ�*/
    NAS_MMC_HPLMN_TYPE_UNICOM                   = 1,            /* �й���ͨ */
    NAS_MMC_HPLMN_TYPE_CT                       = 2,            /* �й�����*/
    NAS_MMC_HPLMN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_HPLMN_TYPE_ENUM_UINT8;


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
VOS_VOID NAS_MMC_ReadImeisvNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadLauRejTrigPlmnSearchNvim( VOS_VOID );
VOS_VOID NAS_MMC_ReadLauRejNeedNoRetryWhenCmSrvExistNvim( VOS_VOID );
VOS_VOID NAS_MMC_ReadRoamingRejectNoRetryFlgNvim( VOS_VOID );
VOS_VOID NAS_MMC_ReadSupported3GppReleaseNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadClassMark1Nvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadClassMark2Nvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadNetworkCapabilityNvim(VOS_VOID);
VOS_VOID  NAS_MMC_ReadMsModeNvim( VOS_VOID );

VOS_VOID NAS_MMC_UpdateNetworkCapabilityGeaValue(VOS_VOID);

VOS_VOID NAS_MMC_ReadUseSingleRplmnFlagNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadRplmnWithRatNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadNvimLastRplmnRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penNvimLastRplmnRat
);

VOS_VOID NAS_MMC_WriteRplmnWithRatNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadEHPlmnSupportNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadUserSetBandNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSearchHPlmnFlgAutoModeNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadAddEhplmnWhenSrchHplmnNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSearchHPlmnFlgManualModeNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSearchHplmnFlgPowerOnNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadEnhancedHPlmnSearchFlagNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSpecialRoamFlgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadNetworkNameNvim(VOS_VOID);

VOS_VOID NAS_MMC_WriteEplmnNvim(VOS_VOID);


VOS_VOID NAS_MMC_DeleteEPlmnList( VOS_VOID );


VOS_VOID NAS_MMC_ReadHplmnFirstSearchPeriodNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadDefaultHplmnSrchPeriodNvim(VOS_VOID);

/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
VOS_VOID NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim(VOS_VOID);
/* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

VOS_VOID NAS_MMC_ReadSrchHplmnTtimerValueNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadWhiteOpeLockPlmnInfoNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadBlackOperLockPlmnInfoNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadUserCfgExtEhplmnInfoNvim( VOS_VOID );
VOS_VOID NAS_MMC_ReadDisabledRatPlmnInfoNvim( VOS_VOID );



VOS_UINT8 NAS_MMC_IsRatForbiddenListNvimValid(
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU *pstParaValue
);

VOS_VOID NAS_MMC_ReadRatForbiddenListConfigNvim( VOS_VOID );

VOS_UINT32 NAS_MMC_ConvertNvimRatToMmlType(
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8            enNvRatType,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *penMmlRatType
);



VOS_VOID NAS_MMC_ReadStandardSTKSteeringOfRoamingFlgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadCsRejSearchSupportFlagNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadAutoAttachNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadPlmnSelectionModeNvim(VOS_VOID);

VOS_VOID NAS_MMC_WritePlmnSelectionModeNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadEquivalentPlmnNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadMaxForbRoamLaNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadGsmForbidAccessInfoNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadRoamBrokerRegisterFailCntNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadPsLociNvim(VOS_VOID);

VOS_VOID NAS_MMC_WritePsLociNvim(
    NAS_NVIM_PS_LOCI_SIM_FILES_STRU    *pstPsLocInfo
);

VOS_VOID NAS_MMC_WriteCsLociNvim(
    NAS_NVIM_CS_LOCI_SIM_FILES_STRU    *pstCsLocInfo
);


VOS_VOID NAS_MMC_ReadCsLociNvim(VOS_VOID);


VOS_VOID NAS_MMC_ReadRoamCfgInfoNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadDtSingleDomainPlmnSearchNvim(VOS_VOID);

VOS_VOID  NAS_MMC_ReadLastImsiNvim( VOS_VOID );

VOS_VOID NAS_MMC_UpdateLastImsi( VOS_VOID );

#if   (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ReadTinInfoNvim(VOS_VOID);

VOS_VOID  NAS_MMC_WriteTinInfoNvim(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi
);

VOS_VOID NAS_MMC_ReadLteCsServiceConfigNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadHoWaitSysinfoTimeLenNvim(VOS_VOID);

VOS_VOID  NAS_MMC_ReadLNasReleaseNvim(VOS_VOID);

#endif
/* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
VOS_VOID NAS_MMC_ReadCsfbEmgCallLaiChgLauFirstNvim(VOS_VOID);
/* Modified by z00161729 for DCM�����������������, 2012-8-14, end */

VOS_VOID NAS_MMC_ReadLteRoamConfigNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadDailRejectConfigNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReaducWcdmaPriorityGsmNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadPsOnlyCsServiceSupportNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadAPPConfigSupportNvim(VOS_VOID);

/* Modified by z40661 for ̩��AIS���� 2012-05-17, begin */

VOS_VOID NAS_MMC_ReadAisRoamingNvim( VOS_VOID  );

/* Modified by z40661 for ̩��AIS���� 2012-05-17, end */


VOS_VOID NAS_MMC_ReadUserAutoReselCfgNvim(VOS_VOID);


VOS_VOID NAS_MMC_ReadScanCtrlNvim(VOS_VOID);


VOS_VOID NAS_MMC_ReadPrioHplmnActCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadHPlmnSearchRegardLessMccNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadSingleDomainFailActionListNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadRegFailNetWorkFailureCustomFlagNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadActingHPlmnSupportNvim(VOS_VOID);

/* Added by t00212959 for DCM�����������������, 2012-8-13, begin */
VOS_VOID NAS_MMC_ReadPlmnExactlyCompareNvim(VOS_VOID);
/* Added by t00212959 for DCM�����������������, 2012-8-13, end */

VOS_VOID NAS_MMC_ReadCustomizeServiceNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadHplmnRegisterCtrlNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadCellSignReportCfgNvim( VOS_VOID );

VOS_VOID NAS_MMC_WriteCellSignReportCfgNvim(VOS_UINT8 ucSignThreshold, VOS_UINT8 ucMinRptTimerInterval);


VOS_VOID NAS_MMC_ReadPlatformRatCapNvim( VOS_VOID );
VOS_UINT32 NAS_MMC_IsPlatformRatCapNvimValid(
    PLATAFORM_RAT_CAPABILITY_STRU              *pstNvPlatformRatCap
);
VOS_UINT32 NAS_MMC_ConvertNvimTypePlatformRatCapToNasType(
    PLATFORM_RAT_TYPE_ENUM_UINT16                       enNvPlatformRatCap,
    NAS_MML_PLATFORM_RAT_TYPE_ENUM_UINT8               *penNasPlatformRatCap
);

/* Added by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, begin */
VOS_VOID NAS_MMC_ReadUcs2CustomizationNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadCloseSmsCapabilityConfigNvim(VOS_VOID);
/* Added by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, end */

VOS_VOID NAS_MMC_ReadH3gCtrlNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSvlteSupportFlagNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadPsTransferCfgNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadDamCfgNvim(VOS_VOID);

#if  (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_ReadEnableLteTimerLenNvim(VOS_VOID);

/* Added by c00318887 for ��ֲT3402 , 2015-6-17, begin */
VOS_VOID NAS_MMC_ReadDisableLteStartT3402EnableLteCfgNvim(VOS_VOID);
/* Added by c00318887 for ��ֲT3402 , 2015-6-17, end */

VOS_VOID NAS_MMC_ReadCsfbRauFollowOnFlgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadLteCustomMccInfoNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_CSG)
VOS_VOID NAS_MMC_ReadCsgCfgNvim(VOS_VOID);
#endif
#endif
VOS_VOID  NAS_MMC_ReadIsrSupportNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadRefreshRplmnWhenEplmnInvalidCfgNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_MMC_ReadErrlogCtrlInfoNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadErrlogNwSrchRecordcfgNvim(VOS_VOID);
#endif


VOS_VOID NAS_MMC_ReadDsdaPlmnSearchEnhancedCfgNvim(VOS_VOID);


VOS_VOID NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim(VOS_VOID);


VOS_VOID NAS_MMC_ReadNonOosPlmnSearchFeatureSupportCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadOosPlmnSearchStrategyCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadGetGeoCfgInfoNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadUserCfgOPlmnInfoNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadAccBarPlmnSearchNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_MMC_ReadModemRfShareCfgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadDsdsEndSessionDelayNvim(VOS_VOID);
#endif

VOS_VOID NAS_MMC_ReadUmtsCodecTypeNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadMedCodecTypeNvim(VOS_VOID);


VOS_VOID NAS_MMC_ReadWgRfMainBandNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadImsVoiceMMEnableNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadLcCtrlParaNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadLteDisabledUseLteInfoFlagNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadCsOnlyDataServiceSupportNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadIgnoreAuthRejFlgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadHighPrioRatHplmnTimerCfgNvim( VOS_VOID  );
VOS_VOID NAS_MMC_ReadSBMCustomDualIMSIConfigNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadRPLMNConfigNvim(VOS_VOID);
#if  (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_ReadUltraFlashCsfbSupportFlgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadSrvccSupportFlgNvim(VOS_VOID);
#endif

VOS_VOID NAS_MMC_Read3GPP2UplmnNotPrefFlgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSyscfgTriPlmnSrchCfgNvim(VOS_VOID);

VOS_VOID  NAS_MMC_ReadDplmnNplmnInfoNvim(VOS_VOID);
VOS_VOID NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_WriteApPresetAndSelfLearnDplmnNplmnToNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_ReadDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_ReadFirstPresetDplmnNplmnCfgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadSecondPresetDplmnNplmnCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSelfLearnDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                     *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_UpdateDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_UpdateApPresetDplmnToFirstPresetDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_UpdateApPresetDplmnToSecondPresetDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_UpdateSelfLearnDplmnNplmnToSelfLearnDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

extern VOS_VOID  NAS_MMC_ReadChangeNwCauseCfgNvim(VOS_VOID );

extern VOS_VOID NAS_MMC_ReadRelPsSignalConCfgNvim(VOS_VOID);

#if  (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID NAS_MMC_ReadLteRejCause14CfgNvim(VOS_VOID);
#endif

VOS_VOID NAS_MMC_ReadDsdsActiveModemModeNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadCsmoSupportedCfgNvim(VOS_VOID);

#if  (FEATURE_ON == FEATURE_IMS)
VOS_VOID NAS_MMC_ReadImsRatSupportNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadImsCapNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadUssdOnImsNvim(VOS_VOID);
#endif

VOS_VOID NAS_MMC_ReadT3212TimerCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadPsRegFailMaxTimesTrigLauOnceFlgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadKeepSrchHplmnEvenRejByCause13Nvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadEpsRejByCause14InVplmnAllowPsRegFlgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadCarryEplmnWhenSrchRplmnCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadRoamDisplayCfgNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID NAS_MMC_ReadLteOos2GPrefPlmnSelCfgNvim(VOS_VOID);
#endif

VOS_VOID NAS_MMC_ReadProtectMtCsfbPagingProcedureLenNvim(VOS_VOID);

/* added by y00176023 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, begin */
VOS_VOID NAS_MMC_ReadLowPrioAnycellsearchLteCfgNvim(VOS_VOID);
/* added by y00176023 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, end */

VOS_VOID NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadKeepCsForbInfoWhenPsRegSuccCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadClearCksnCfgNvim(VOS_VOID);

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

#endif
