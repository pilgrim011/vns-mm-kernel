/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaMain.c
  �� �� ��   : ����
  ��    ��   : ��־��
  ��������   : 2012��6��27��
  ����޸�   :
  ��������   : MTAģ����Ϣ��������Ӧ����ع���������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��6��27��
    ��    ��   : Y00213812
    �޸�����   : A-GPS��Ŀ����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMtaCtx.h"
#include "TafMtaComm.h"
#include "TafMtaMain.h"
#include "AtMtaInterface.h"
#include "TafMtaTimerMgmt.h"
#include "TafMtaAgps.h"
#include "TcNasinterface.h"
#include "TafMtaSecure.h"
#include "TafMtaMntn.h"
#include "MtaPhyInterface.h"
#include "TafMtaPhy.h"
#include "NasMtaInterface.h"
/* Added by z00161729 for �����ϱ�AT�������������C��, 2013-4-11, begin */
#include "TafMtaUnSolicitedReport.h"
/* Added by z00161729 for �����ϱ�AT�������������C��, 2013-4-11, begin */

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

#include "MtaMtcInterface.h"
#include "TafMtaModemControl.h"

#include "TafMtaMbms.h"

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
#include "nascbtinterface.h"
#endif

#include "TafMtaModemInfoQuery.h"

#include "MtaPhyInterface.h"
#include "AtMtaInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTA_MAIN_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* MTAģ�鴦������AT��Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcAtTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_AT_MTA_CPOS_SET_REQ,                    TAF_MTA_RcvAtCposSetReq},
    {ID_AT_MTA_CGPSCLOCK_SET_REQ,               TAF_MTA_RcvAtCgpsClockSetReq},

    {ID_AT_MTA_APSEC_SET_REQ,                   TAF_MTA_RcvAtApSecSetReq},

    {ID_AT_MTA_SIMLOCKUNLOCK_SET_REQ,           TAF_MTA_RcvAtSimlockUnlockSetReq},

    {ID_AT_MTA_QRY_NMR_REQ,                     TAF_MTA_RcvQryNmrReq},

    {ID_AT_MTA_RESEL_OFFSET_CFG_SET_NTF,        TAF_MTA_RcvReselOffsetCfgSetReq},

    {ID_AT_MTA_WRR_AUTOTEST_QRY_REQ,            TAF_MTA_RcvQryWrrAutotestReq},
    {ID_AT_MTA_WRR_CELLINFO_QRY_REQ,            TAF_MTA_RcvQryWrrCellInfoReq},
    {ID_AT_MTA_WRR_MEANRPT_QRY_REQ,             TAF_MTA_RcvQryWrrMeanrptReq},
    {ID_AT_MTA_WRR_FREQLOCK_SET_REQ,            TAF_MTA_RcvSetWrrFreqlockReq},
    {ID_AT_MTA_WRR_RRC_VERSION_SET_REQ,         TAF_MTA_RcvSetWrrRrcVersionReq},
    {ID_AT_MTA_WRR_CELLSRH_SET_REQ,             TAF_MTA_RcvSetWrrCellsrhReq},
    {ID_AT_MTA_WRR_FREQLOCK_QRY_REQ,            TAF_MTA_RcvQryWrrFreqlockReq},
    {ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ,         TAF_MTA_RcvQryWrrRrcVersionReq},
    {ID_AT_MTA_WRR_CELLSRH_QRY_REQ,             TAF_MTA_RcvQryWrrCellsrhReq},

    {ID_AT_MTA_BODY_SAR_SET_REQ,                TAF_MTA_RcvAtBodySarSetReq},

    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, begin */
    {ID_AT_MTA_CURC_SET_NOTIFY,                 TAF_MTA_RcvAtSetCurcNotify},
    {ID_AT_MTA_CURC_QRY_REQ,                    TAF_MTA_RcvAtQryCurcReq},
    {ID_AT_MTA_UNSOLICITED_RPT_SET_REQ,         TAF_MTA_RcvAtSetUnsolicitedRptReq},
    {ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,         TAF_MTA_RcvAtQryUnsolicitedRptReq},
    {ID_TAFAGENT_MTA_GET_SYSMODE_REQ,           TAF_MTA_RcvTafAgentGetSysModeReq},
    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, end */

    {ID_AT_MTA_IMEI_VERIFY_QRY_REQ,             TAF_MTA_RcvQryImeiVerifyReq},
    {ID_AT_MTA_CGSN_QRY_REQ,                    TAF_MTA_RcvQryCgsnReq},

    {ID_AT_MTA_NCELL_MONITOR_SET_REQ,           TAF_MTA_RcvAtSetNCellMonitorReq},
    {ID_AT_MTA_NCELL_MONITOR_QRY_REQ,           TAF_MTA_RcvAtQryNCellMonitorReq},

    {ID_AT_MTA_REFCLKFREQ_SET_REQ,              TAF_MTA_RcvAtRefclkfreqSetReq},
    {ID_AT_MTA_REFCLKFREQ_QRY_REQ,              TAF_MTA_RcvAtRefclkfreqQryReq},

    {ID_AT_MTA_RFICSSIRD_QRY_REQ,               TAF_MTA_RcvAtRficSsiRdQryReq},

    {ID_TAFAGENT_MTA_GET_ANT_STATE_REQ,         TAF_MTA_RcvTafAgentGetAntStateReq},

    {ID_AT_MTA_HANDLEDECT_SET_REQ,              TAF_MTA_RcvAtSetHandleDectReq},
    {ID_AT_MTA_HANDLEDECT_QRY_REQ,              TAF_MTA_RcvAtQryHandleDectReq},

#if (FEATURE_ON == FEATURE_DSDS)
    { ID_AT_MTA_RRC_PROTECT_PS_REQ,             TAF_MTA_RcvAtPsProtectSetReq},
#endif
    { ID_AT_MTA_PHY_INIT_REQ,                   TAF_MTA_RcvAtPhyInitReq},


    /* Added by l00198894 for ����+ECID����, 2013-12-09, begin */
    {ID_AT_MTA_ECID_SET_REQ,                    TAF_MTA_RcvAtEcidSetReq},
    /* Added by l00198894 for ����+ECID����, 2013-12-09, end */

    {ID_AT_MTA_MIPICLK_QRY_REQ,                TAF_MTA_RcvAtQryMipiClkReq},

    {ID_AT_MTA_SET_DPDTTEST_FLAG_REQ,           TAF_MTA_RcvAtSetDpdtTestFlagReq},
    {ID_AT_MTA_SET_DPDT_VALUE_REQ,              TAF_MTA_RcvAtSetDpdtValueReq},
    {ID_AT_MTA_QRY_DPDT_VALUE_REQ,              TAF_MTA_RcvAtQryDpdtValueReq},

    {ID_AT_MTA_SET_JAM_DETECT_REQ,              TAF_MTA_RcvAtSetJamDetectReq},

    {ID_AT_MTA_SET_FREQ_LOCK_REQ,               TAF_MTA_RcvAtSetFreqLockReq},

    {ID_AT_MTA_SET_GSM_FREQLOCK_REQ,            TAF_MTA_RcvAtSetGFreqLockReq},

    {ID_AT_MTA_SET_FEMCTRL_REQ,                 TAF_MTA_RcvAtSetFemctrlReq},

    {ID_AT_MTA_NVWRSECCTRL_SET_REQ,             TAF_MTA_RcvAtNvwrSecCtrlSetReq},
#if(FEATURE_ON == FEATURE_LTE)
#if(FEATURE_ON == FEATURE_LTE_MBMS)
    {ID_AT_MTA_MBMS_SERVICE_OPTION_SET_REQ,     TAF_MTA_RcvAtMBMSServiceOptionSetReq},
    {ID_AT_MTA_MBMS_SERVICE_STATE_SET_REQ,      TAF_MTA_RcvAtMBMSServiceStateSetReq},
    {ID_AT_MTA_MBMS_PREFERENCE_SET_REQ,         TAF_MTA_RcvAtMBMSPreferenceSetReq},
    {ID_AT_MTA_SIB16_NETWORK_TIME_QRY_REQ,      TAF_MTA_RcvAtSIB16NetworkTimeQryReq},
    {ID_AT_MTA_BSSI_SIGNAL_LEVEL_QRY_REQ,       TAF_MTA_RcvAtBSSISignalLevelQryReq},
    {ID_AT_MTA_NETWORK_INFO_QRY_REQ,            TAF_MTA_RcvAtNetworkInfoQryReq},
    {ID_AT_MTA_EMBMS_STATUS_QRY_REQ,            TAF_MTA_RcvAtEMBMSStatusQryReq},
    {ID_AT_MTA_MBMS_UNSOLICITED_CFG_SET_REQ,    TAF_MTA_RcvAtMBMSUnsolicitedCfgSetReq},
    {ID_AT_MTA_INTEREST_LIST_SET_REQ,           TAF_MTA_RcvAtMBMSInterestListSetReq},
    {ID_AT_MTA_MBMS_AVL_SERVICE_LIST_QRY_REQ,   TAF_MTA_RcvAtMBMSAvlServiceListQryReq},
#endif
    {ID_AT_MTA_LTE_LOW_POWER_SET_REQ,           TAF_MTA_RcvAtLteLowPowerConsumptionSetReq},
    {ID_AT_MTA_LTE_WIFI_COEX_SET_REQ,           TAF_MTA_RcvAtIsmCoexSetReq},
    {ID_AT_MTA_LTE_WIFI_COEX_QRY_REQ,           TAF_MTA_RcvAtIsmCoexQryReq},
#endif
    {ID_AT_MTA_SET_FR_REQ,                      TAF_MTA_RcvAtSetFrReq},

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {ID_AT_MTA_MEID_SET_REQ,                    TAF_MTA_RcvMeidSetReq},
    {ID_AT_MTA_MEID_QRY_REQ,                    TAF_MTA_RcvMeidQryReq},
#endif

    {ID_AT_MTA_TRANSMODE_QRY_REQ,               TAF_MTA_RcvAtTransModeQryReq},

    {ID_AT_MTA_UE_CENTER_SET_REQ,               TAF_MTA_RcvAtUECenterSetReq},
    {ID_AT_MTA_UE_CENTER_QRY_REQ,               TAF_MTA_RcvAtUECenterQryReq},
    {ID_AT_MTA_SET_NETMON_SCELL_REQ,            TAF_MTA_RcvAtSetNetMonSCellReq},
    {ID_AT_MTA_SET_NETMON_NCELL_REQ,            TAF_MTA_RcvAtSetNetMonNCellReq},

    {ID_AT_MTA_QRY_AFC_CLK_FREQ_XOCOEF_REQ,     TAF_MTA_RcvAtQryAfcAndXoInfoReq},

};

/* MTAģ�鴦������PHY APMģ�����Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcApmTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_APM_MTA_BODY_SAR_SET_CNF,               TAF_MTA_RcvPhyBodySarSetCnf},

    {ID_APM_MTA_REFCLOCK_STATUS_IND,            TAF_MTA_RcvPhyRefClockStatusInd},

    {ID_APM_MTA_HANDLE_DETECT_SET_CNF,          TAF_MTA_RcvPhyHandleDectSetCnf},
    {ID_APM_MTA_HANDLE_DETECT_QRY_CNF,          TAF_MTA_RcvPhyHandleDectQryCnf},

#if(FEATURE_ON == FEATURE_PTM)
    {ID_APM_MTA_GET_PHY_CHR_INFO_CNF,           TAF_MTA_RcvPhyChrInfoQryCnf},
#endif
};

/* MTAģ�鴦������TLPHYģ�����Ϣ������Ӧ�� */
const MTA_MSG_PROC_STRU g_astMtaMsgProcRttAgentTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_APM_MTA_REFCLOCK_STATUS_IND,       TAF_MTA_RcvTlPhyAfclockStatusInd},
#if(FEATURE_ON == FEATURE_PTM)
    {ID_TLPHY_MTA_GET_PHY_CHR_INFO_CNF,    TAF_MTA_RcvPhyChrInfoQryCnf},
#endif
};

/* MTAģ�鴦�����Խ����Gģ����Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcGasTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_RRC_MTA_MSG_POSITION_REQ,               TAF_MTA_RcvRrcMsgPositionReq},

    /* Modified by l00198894 for ����+ECID����, 2013-12-10, begin */
    {ID_RRC_MTA_QRY_NMR_CNF,                    TAF_MTA_RcvGUAsEcellInfoQryCnf},
    /* Modified by l00198894 for ����+ECID����, 2013-12-10, end */

    {ID_GRR_MTA_NCELL_MONITOR_SET_CNF,          TAF_MTA_RcvRrcSetNCellMonitorCnf},
    {ID_GRR_MTA_NCELL_MONITOR_QRY_CNF,          TAF_MTA_RcvRrcQryNCellMonitorCnf},
    {ID_GRR_MTA_NCELL_MONITOR_IND,              TAF_MTA_RcvRrcNCellMonitorInd},

    {ID_RRC_MTA_JAM_DETECT_CNF,                 TAF_MTA_RcvRrcJamDetectCnf},
    {ID_RRC_MTA_JAM_DETECT_IND,                 TAF_MTA_RcvRrcJamDetectInd},

    {ID_RRC_MTA_CHECK_FREQ_VALIDITY_CNF,        TAF_MTA_RcvRrcCheckFreqValidityCnf},

    {ID_GRR_MTA_FREQLOCK_SET_CNF,               TAF_MTA_RcvGasSetFreqLockCnf},

#if(FEATURE_ON == FEATURE_PTM)
    {ID_RRC_MTA_PLMN_FREQ_QRY_CNF,              TAF_MTA_RcvGasPlmnFreqQryCnf},
#endif

    {ID_GRR_MTA_NETMON_CELL_QRY_CNF,            TAF_MTA_RcvGasNetMonCellQryCnf},
    {ID_GRR_MTA_NETMON_TA_QRY_CNF,              TAF_MTA_RcvGasNetMonTaQryCnf},

};
/* MTAģ�鴦�����Խ����Wģ����Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcWcomTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_RRC_MTA_MSG_POSITION_REQ,               TAF_MTA_RcvRrcMsgPositionReq},

};


/* MTAģ�鴦�����Խ����Wrrģ����Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcWrrTab[]=
{
    /* Modified by l00198894 for ����+ECID����, 2013-12-10, begin */
    {ID_RRC_MTA_QRY_NMR_CNF,                    TAF_MTA_RcvGUAsEcellInfoQryCnf},
    /* Modified by l00198894 for ����+ECID����, 2013-12-10, end */
    {ID_WRR_MTA_AUTOTEST_QRY_CNF,               TAF_MTA_RcvWrrAutotestQryCnf},
    {ID_WRR_MTA_CELLINFO_QRY_CNF,               TAF_MTA_RcvWrrCellInfoQryCnf},
    {ID_WRR_MTA_MEASRPT_QRY_CNF,                TAF_MTA_RcvWrrMeanrptQryCnf},
    {ID_WRR_MTA_FREQLOCK_SET_CNF,               TAF_MTA_RcvWrrFreqlockSetCnf},
    {ID_WRR_MTA_RRC_VERSION_SET_CNF,            TAF_MTA_RcvWrrVersionSetCnf},
    {ID_WRR_MTA_CELLSRH_SET_CNF,                TAF_MTA_RcvWrrCellsrhSetCnf},
    {ID_WRR_MTA_FREQLOCK_QRY_CNF,               TAF_MTA_RcvWrrFreqlockQryCnf},
    {ID_WRR_MTA_RRC_VERSION_QRY_CNF,            TAF_MTA_RcvWrrVersionQryCnf},
    {ID_WRR_MTA_CELLSRH_QRY_CNF,                TAF_MTA_RcvWrrCellsrhQryCnf},

    {ID_RRC_MTA_CHECK_FREQ_VALIDITY_CNF,        TAF_MTA_RcvRrcCheckFreqValidityCnf},
#if(FEATURE_ON == FEATURE_PTM)
    {ID_RRC_MTA_PLMN_FREQ_QRY_CNF,              TAF_MTA_RcvWrrPlmnFreqQryCnf},
#endif
    {ID_RRC_MTA_NETMON_CELL_QRY_CNF,            TAF_MTA_RcvWrrNetMonCellQryCnf},
};


/* MTAģ�鴦�����������Gģ����Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcGphyTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_GPHY_MTA_SET_GPS_RF_CLOCK_CNF,          TAF_MTA_RcvPhyCgpsClockSetCnf},
    {ID_GUPHY_MTA_QRY_DPDT_VALUE_CNF,           TAF_MTA_RcvGuPhyQryDpdtValueCnf},
    {ID_GPHY_MTA_XPASS_INFO_IND,                TAF_MTA_RcvGphyXpassInfoInd},

};
/* MTAģ�鴦�����������Wģ����Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcWphyTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_WPHY_MTA_SET_GPS_RF_CLOCK_CNF,          TAF_MTA_RcvPhyCgpsClockSetCnf},
    {ID_GUPHY_MTA_QRY_DPDT_VALUE_CNF,           TAF_MTA_RcvGuPhyQryDpdtValueCnf},
    {ID_WPHY_MTA_XPASS_INFO_IND,                TAF_MTA_RcvWphyXpassInfoInd},

};
/* MTAģ�鴦������TC��Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcTcTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {TCMTA_RESET_UE_POS_STORED_INFO_IND,        TAF_MTA_RcvTcResetUePosStoredInfoInd},

};
/* MTAģ�鴦�����Զ�ʱ����Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcTimerTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {TI_TAF_MTA_WAIT_AT_SET_CPOS_CNF,           TAF_MTA_RcvTiCposSetReqExpired},
    {TI_TAF_MTA_WAIT_GPHY_SET_CGPSCLOCK_CNF,    TAF_MTA_RcvTiCgpsClockSetReqExpired},
    {TI_TAF_MTA_WAIT_WPHY_SET_CGPSCLOCK_CNF,    TAF_MTA_RcvTiCgpsClockSetReqExpired},

    {TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF,            TAF_MTA_RcvTiWaitAsQryNmrCnfExpired},

    {TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF,      TAF_MTA_RcvTiReqAutotestQryExpired},
    {TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF,      TAF_MTA_RcvTiReqCellInfoQryExpired},
    {TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF,       TAF_MTA_RcvTiReqMeanrptQryExpired},
    {TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF,      TAF_MTA_RcvTiReqFreqlockSetExpired},
    {TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF,   TAF_MTA_RcvTiReqRrcVersionSetExpired},
    {TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF,       TAF_MTA_RcvTiReqCellsrhSetExpired},
    {TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF,      TAF_MTA_RcvTiReqFreqlockQryExpired},
    {TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF,   TAF_MTA_RcvTiReqRrcVersionQryExpired},
    {TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF,       TAF_MTA_RcvTiReqCellsrhQryExpired},

    {TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF,       TAF_MTA_RcvTiWaitPhySetBodySarExpired},

    {TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF,  TAF_MTA_RcvTiWaitGrrSetNCellMonitorExpired},
    {TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF,  TAF_MTA_RcvTiWaitGrrQryNCellMonitorExpired},

    {TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF,    TAF_MTA_RcvTiWaitPhySetHandleDectExpired},
    {TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF,    TAF_MTA_RcvTiWaitPhyQryHandleDectExpired},

    /* Added by l00198894 for ����+ECID����, 2013-12-10, begin */
    {TI_TAF_MTA_WAIT_AS_ECID_SET_CNF,           TAF_MTA_RcvTiEcidSetExpired},
    /* Added by l00198894 for ����+ECID����, 2013-12-10, end */


    {TI_TAF_MTA_RF_LCD_MIPI_CLK_REPORT,         TAF_MTA_RcvTiMipiClkExpired},

    {TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF,        TAF_MTA_RcvTiReqDpdtValueQryExpired},

    {TI_TAF_MTA_WAIT_DSP_INIT_CNF,              TAF_MTA_RcvTiPhyInitExpired},

    {TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF,        TAF_MTA_RcvTiWaitGrrSetJamDetectExpired},

    {TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF,   TAF_MTA_RcvTiWaitRrcCheckFreqValidityExpired},

    {TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF,      TAF_MTA_RcvTiWaitGasSetGFreqLockExpired},

#if(FEATURE_ON == FEATURE_LTE)
#if(FEATURE_ON == FEATURE_LTE_MBMS)
    {TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF,          TAF_MTA_RcvTiWaitLrrcSetMBMSServiceOption},
    {TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF,           TAF_MTA_RcvTiWaitLrrcSetMBMSServiceState},
    {TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF,              TAF_MTA_RcvTiWaitLrrcSetMBMSPreference},
    {TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF,      TAF_MTA_RcvTiWaitLrrcQrySIB16NetworkTime},
    {TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF,       TAF_MTA_RcvTiWaitLrrcQryBSSISignalLevel},
    {TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF,            TAF_MTA_RcvTiWaitLrrcQryNetworkInfo},
    {TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF,                 TAF_MTA_RcvTiWaitLrrcQryEMBMSStatus},
    {TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF,         TAF_MTA_RcvTiWaitLrrcSetMBMSUnsolicitedCfg},
    {TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF,            TAF_MTA_RcvTiWaitLrrcSetInterestList},
    {TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF,        TAF_MTA_RcvTiWaitLrrcQryAvlServiceList},
#endif
    {TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF,        TAF_MTA_RcvTiWaitLrrcSetLowPowerConsumption},
    {TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF,                     TAF_MTA_RcvTiWaitSetIsmCoexList},
#endif

    {TI_TAF_MTA_WAIT_SET_FR_CNF,                TAF_MTA_RcvTiWaitLrrcSetFrCnfExpired},

    {TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND,       TAF_MTA_RcvTiWaitAgentRefclockIndExpired},
    {TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF,    TAF_MTA_RcvTiWaitAgentQryAfclockExpired},
#if (FEATURE_ON == FEATURE_PTM)
    {TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF,                    TAF_MTA_RcvTiWaitFreqCltQryCnfExpired},
    {TI_TAF_MTA_WAIT_NETWORK_INFO_QRY_CNF,          TAF_MTA_RcvTiWaitNetworkInfoQryCnfExpired},
#endif
    {TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF,         TAF_MTA_RcvTiWaitLrrcTransModeQryExpired},

    {TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF,         TAF_MTA_RcvTiWaitLnasUECenterSetExpired},
    {TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF,         TAF_MTA_RcvTiWaitLnasUECenterQryExpired},
    {TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF,  TAF_MTA_RcvTiWaitRrcNetMonSCellQryExpired},
    {TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF,  TAF_MTA_RcvTiWaitRrcNetMonNCellQryExpired},
    {TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF,     TAF_MTA_RcvTiWaitGrrNetMonTaQryExpired},

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {TI_TAF_MTA_WAIT_UIMID_READ_CNF,            TAF_MTA_RcvTiWaitUIMIDReadExpired},
#endif
    {TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF,  TAF_MTA_RcvTiWaitRcmAfcInfoQryExpired},
};

/* MTAģ�鴦������MMAģ�����Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcNasTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_NAS_MTA_AREA_LOST_IND,                  TAF_MTA_RcvNasAreaLostInd},

    { ID_LNAS_MTA_SET_UE_CENTER_CNF,            TAF_MTA_RcvLnasUECenterSetCnf},
    { ID_LNAS_MTA_QRY_UE_CENTER_CNF,            TAF_MTA_RcvLnasUECenterQryCnf},
#if (FEATURE_ON == FEATURE_PTM)
    { ID_MMC_MTA_GET_NAS_CHR_INFO_CNF,          TAF_MTA_RcvNasGetNasChrInfoCnf},
#endif
};

/* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/* MTAģ�鴦������AT��Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcTafAgentTab[]=
{
    {ID_TAFAGENT_MTA_GET_SYSMODE_REQ,           TAF_MTA_RcvTafAgentGetSysModeReq},

    {ID_TAFAGENT_MTA_GET_ANT_STATE_REQ,         TAF_MTA_RcvTafAgentGetAntStateReq},
};
/* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */


#if (FEATURE_ON == FEATURE_PTM)
/* MTAģ�鴦������Acpu OMģ�����Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcAcpuOmTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_OM_ERR_LOG_CTRL_IND,                    TAF_MTA_RcvAcpuOmErrLogCtrlInd},
    {ID_OM_ERR_LOG_REPORT_REQ,                  TAF_MTA_RcvAcpuOmErrLogRptReq},
    {ID_OM_INFO_CLT_REPORT_REQ,                 TAF_MTA_RcvAcpuOmInfoCltRptReq},
};
#endif

/* MTAģ�鴦������MTCģ�����Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcMtcTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    {ID_MTC_MTA_PS_TRANSFER_IND,                TAF_MTA_RcvMtcPsTransferInd},
#endif
    {ID_MTC_MTA_MIPICLK_INFO_IND,               TAF_MTA_RcvMtcMipiClkInfoInd},
    {ID_MTC_MTA_GSM_CELLINFO_QRY_CNF,           TAF_MTA_RcvMtcGsmCellInfoQryCnf},
};

/* Added by l00198894 for ����+ECID����, 2013-12-10, begin */
#if (FEATURE_ON == FEATURE_LTE)
const MTA_MSG_PROC_STRU g_astMtaMsgProcLrrcTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_LRRC_MTA_CELLINFO_QRY_CNF,              TAF_MTA_RcvLrrcCellinfoQryCnf},

    {ID_TLRRC_MTA_QRY_DPDT_VALUE_CNF,           TAF_MTA_RcvTLrrcDpdtValueQryCnf},

    {ID_RRC_MTA_CHECK_FREQ_VALIDITY_CNF,        TAF_MTA_RcvRrcCheckFreqValidityCnf},

#if(FEATURE_ON == FEATURE_LTE)
#if(FEATURE_ON == FEATURE_LTE_MBMS)
    {ID_LRRC_MTA_MBMS_SERVICE_OPTION_CNF,       TAF_MTA_RcvLrrcMBMSServiceOptionSetCnf},
    {ID_LRRC_MTA_MBMS_SERVICE_STATE_SET_CNF,    TAF_MTA_RcvLrrcMBMSServiceStateSetCnf},
    {ID_LRRC_MTA_MBMS_PREFERENCE_SET_CNF,       TAF_MTA_RcvLrrcMBMSPreferenceSetCnf},
    {ID_LRRC_MTA_SIB16_NETWORK_TIME_QRY_CNF,    TAF_MTA_RcvLrrcMBMSSIB16NetworkTimeQryCnf},
    {ID_LRRC_MTA_BSSI_SIGNAL_LEVEL_QRY_CNF,     TAF_MTA_RcvLrrcMBMSBSSISignalLevelQryCnf},
    {ID_LRRC_MTA_NETWORK_INFO_QRY_CNF,          TAF_MTA_RcvLrrcMBMSNetworkInfoQryCnf},
    {ID_LRRC_MTA_EMBMS_STATUS_QRY_CNF,          TAF_MTA_RcvLrrcEMBMSStatusQryCnf},
    {ID_LRRC_MTA_MBMS_UNSOLICITED_CFG_SET_CNF,  TAF_MTA_RcvLrrcMBMSUnsolicitedCfgSetCnf},
    {ID_LRRC_MTA_MBMS_SERVICE_EVENT_IND,        TAF_MTA_RcvLrrcMBMSServiceEventInd},
    {ID_LRRC_MTA_INTEREST_LIST_SET_CNF,         TAF_MTA_RcvLrrcInterestListSetCnf},
    {ID_LRRC_MTA_MBMS_AVL_SERVICE_LIST_QRY_CNF, TAF_MTA_RcvLrrcMBMSAvlServiceListQryCnf},
#endif
    {ID_LRRC_MTA_LOW_POWER_CONSUMPTION_SET_CNF, TAF_MTA_RcvLrrcLowPowerConsumptionSetCnf},
    {ID_LRRC_MTA_LTE_WIFI_COEX_SET_CNF,         TAF_MTA_RcvLrrcIsmCoexSetCnf},
#endif
    {ID_LRRC_MTA_SET_FR_CNF,                    TAF_MTA_RcvLrrcSetFrCnf},
#if(FEATURE_ON == FEATURE_PTM)
    {ID_RRC_MTA_PLMN_FREQ_QRY_CNF,              TAF_MTA_RcvLrrcPlmnFreqQryCnf},
#endif

    { ID_LRRC_MTA_TRANSMODE_QRY_CNF,            TAF_MTA_RcvLrrcTransModeQryCnf},
    {ID_LRRC_MTA_NETMON_CELL_QRY_CNF,           TAF_MTA_RcvLrrcNetMonCellQryCnf},
};
#endif
/* Added by l00198894 for ����+ECID����, 2013-12-10, end */

/* MTAģ�鴦������������ʼ����Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcDspStartTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_UPHY_MTA_START_UPHY_CNF,          TAF_MTA_RcvPhyInitCnf},

};

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
const MTA_MSG_PROC_STRU g_astMtaMsgProcTdsTab[]=
{
    {ID_RRC_MTA_CHECK_FREQ_VALIDITY_CNF,        TAF_MTA_RcvRrcCheckFreqValidityCnf},
	{ID_TLRRC_MTA_QRY_DPDT_VALUE_CNF,           TAF_MTA_RcvTLrrcDpdtValueQryCnf},
    {ID_RRC_MTA_NETMON_CELL_QRY_CNF,              TAF_MTA_RcvTrrcNetMonCellQryCnf},
};
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/* ��������Ctas����Ϣ */
const MTA_MSG_PROC_STRU g_astMtaMsgProcCtasTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_CTAS_MTA_QRY_DPDT_VALUE_CNF,            TAF_MTA_RcvCtasQryDpdtValueCnf},
};
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/* ��������USIMM����Ϣ */
const MTA_MSG_PROC_STRU g_astMtaMsgProcUsimmTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {USIMM_READFILE_CNF,                        TAF_MTA_RcvRcvUsimGetFileRsp},
};
#endif

#if 0
/* MTAģ�鴦�����������TLPHY�������Ϣ������Ӧ��*/
const MTA_MSG_PROC_STRU g_astMtaMsgProcTLphyAgentTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
#if(FEATURE_ON == FEATURE_LTE)
    {ID_LPHY_MTA_LTE_WIFI_COEX_SET_CNF,         TAF_MTA_RcvLphyIsmCoexSetCnf},
#endif
};
#endif

/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndAtMsg
 ��������  : MTA��AT������Ϣ����
 �������  : AT_APPCTRL_STRU   *pAppCtrl������Ϣ��ID
             VOS_UINT32         ulMsgId ��ϢID
             VOS_UINT32         ulLen   ��Ϣ����
             VOS_UINT8         *pData   ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����

*****************************************************************************/
VOS_VOID TAF_MTA_SndAtMsg(
    AT_APPCTRL_STRU                    *pAppCtrl,
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pData
)
{
    AT_MTA_MSG_STRU                    *pstMtaMsgStr;

    /* �ж�������� */
    if ((VOS_NULL_PTR == pData) || (0 == ulLen))
    {
        MTA_ERROR_LOG("TAF_MTA_SndAtMsg: para is invalid!");
        return;
    }

    /* ��Ϣ�ռ����� */
    pstMtaMsgStr = (AT_MTA_MSG_STRU *)PS_ALLOC_MSG( UEPS_PID_MTA,
                                                    sizeof(AT_APPCTRL_STRU) + sizeof(ulMsgId) + ulLen);
    if (VOS_NULL_PTR == pstMtaMsgStr)
    {
        MTA_ERROR_LOG("TAF_MTA_SndAtMsg: alloc msg fail!");
        return;
    }

    /* ����Ϣ�� */
    pstMtaMsgStr->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMtaMsgStr->ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstMtaMsgStr->ulSenderPid           = UEPS_PID_MTA;
    pstMtaMsgStr->ulReceiverPid         = WUEPS_PID_AT;
    pstMtaMsgStr->ulMsgId               = ulMsgId;
    pstMtaMsgStr->stAppCtrl.usClientId  = MN_GetRealClientId(pAppCtrl->usClientId, UEPS_PID_MTA);
    pstMtaMsgStr->stAppCtrl.ucOpId      = pAppCtrl->ucOpId;
    pstMtaMsgStr->stAppCtrl.aucReserved[0] = 0;
    PS_MEM_CPY(pstMtaMsgStr->aucContent, pData, ulLen);

    /* ������Ϣ��ATģ�� */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaMsgStr))
    {
        MTA_ERROR_LOG("TAF_MTA_SndAtMsg():WARNING:SEND MSG FIAL");
    }
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SearchMsgProcTab
 ��������  : ��������ATģ�����Ϣ
 �������  : ulMsgCnt       ��Ϣ�б�Ĵ�С
             *pstMsg        ������Ϣ
             pstMsgProcTab  ��Ϣ�б�
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32 TAF_MTA_SearchMsgProcTab(
    VOS_UINT32                          ulMsgCnt,
    VOS_VOID                           *pstMsg,
    const MTA_MSG_PROC_STRU            *pstMsgProcTab
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMsgName;

    /* ����Ϣ���л�ȡMSG ID */
    ulMsgName  = ((MSG_HEADER_STRU*)pstMsg)->ulMsgName;

    /* ���������Ϣ�ַ� */
    for (ulLoop = 0; ulLoop < ulMsgCnt; ulLoop++)
    {
        if (pstMsgProcTab[ulLoop].ulMsgType == ulMsgName)
        {
            pstMsgProcTab[ulLoop].pProcMsgFunc(pstMsg);
            break;
        }
    }

    /* û���ҵ�ƥ�����Ϣ */
    if (ulMsgCnt == ulLoop)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtMsg
 ��������  : ��������ATģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcAtTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcAtTab)/sizeof(MTA_MSG_PROC_STRU);

    /*g_astMtaMsgProcAtTab���������Ϣ�ַ�*/
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcAtTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAtMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvApmMsg
 ��������  : ��������PHY APMģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��03��11��
    ��    ��   : z00214637
    �޸�����   : BODYSAR��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvApmMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcApmTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcApmTab)/sizeof(MTA_MSG_PROC_STRU);

    /* g_astMtaMsgProcApmTab���������Ϣ�ַ� */
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcApmTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvApmMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvRttAgentMsg
 ��������  : ��������RTTAGENTģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : zwx247453
    �޸�����   : Refclkfreq��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvRttAgentMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcRttAgentTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcRttAgentTab)/sizeof(MTA_MSG_PROC_STRU);

    /* g_astMtaMsgProcRttAgentTab���������Ϣ�ַ� */
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcRttAgentTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvRttAgentMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvGasMsg
 ��������  : ��������Gģʽ�½�������Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvGasMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcGasTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcGasTab)/sizeof(MTA_MSG_PROC_STRU);

    /* g_astMtaMsgProcGasTab���������Ϣ�ַ� */
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcGasTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvGasMsg: Msg Id is invalid!");
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvWcomMsg
 ��������  : ��������Wģʽ�½�������Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��cerssi��nmr

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWcomMsg(struct MsgCB *pstMsg)

{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcWcomTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcWcomTab)/sizeof(MTA_MSG_PROC_STRU);

    /* g_astMtaMsgProcWasTab���������Ϣ�ַ� */
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcWcomTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvWcomMsg: Msg Id is invalid!");
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvWrrMsg
 ��������  : ��������Wģʽ�½�������Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWrrMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcWrrTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcWrrTab)/sizeof(MTA_MSG_PROC_STRU);

    /* g_astMtaMsgProcWrrTab���������Ϣ�ַ� */
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcWrrTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvWrrMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvGphyMsg
 ��������  : ��������Gģʽ����������Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvGphyMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMsgName;

    /* ��g_astMtaMsgProcGphyTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcGphyTab)/sizeof(MTA_MSG_PROC_STRU);

    /* ����Ϣ���л�ȡMSG ID */
    ulMsgName = (VOS_UINT32)((MTA_PHY_MSG_HEADER_STRU*)pstMsg)->usMsgID;

    /* g_astMtaMsgProcGphyTab���������Ϣ�ַ� */
    for (ulLoop = 0; ulLoop < ulMsgCnt; ulLoop++)
    {
        if (g_astMtaMsgProcGphyTab[ulLoop].ulMsgType == ulMsgName)
        {
            g_astMtaMsgProcGphyTab[ulLoop].pProcMsgFunc(pstMsg);
            break;
        }
    }

    /* û���ҵ�ƥ�����Ϣ */
    if (ulMsgCnt == ulLoop)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvGphyMsg: Msg Id is invalid!");
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvWphyMsg
 ��������  : ��������Wģʽ����������Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWphyMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMsgName;

    /* ��g_astMtaMsgProcWphyTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcWphyTab)/sizeof(MTA_MSG_PROC_STRU);

    /* ����Ϣ���л�ȡMSG ID */
    ulMsgName = (VOS_UINT32)((MTA_PHY_MSG_HEADER_STRU*)pstMsg)->usMsgID;

    /* g_astMtaMsgProcWphyTab���������Ϣ�ַ� */
    for (ulLoop = 0; ulLoop < ulMsgCnt; ulLoop++)
    {
        if (g_astMtaMsgProcWphyTab[ulLoop].ulMsgType == ulMsgName)
        {
            g_astMtaMsgProcWphyTab[ulLoop].pProcMsgFunc(pstMsg);
            break;
        }
    }

    /* û���ҵ�ƥ�����Ϣ */
    if (ulMsgCnt == ulLoop)

    {
        MTA_ERROR_LOG("TAF_MTA_RcvWphyMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTcMsg
 ��������  : ��������Tc����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��07��09��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTcMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcTcTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcTcTab)/sizeof(MTA_MSG_PROC_STRU);

    /* g_astMtaMsgProcTcTab���������Ϣ�ַ� */
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcTcTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvTcMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTimerMsg
 ��������  : ��ʱ����ʱ����
 �������  : VOS_VOID *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTimerMsg(VOS_VOID *pstMsg)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulTimerId;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    /* ��g_astMtaMsgProcTimerTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcTimerTab)/sizeof(MTA_MSG_PROC_STRU);

    /* ��ȡTIMER ID���Ѷ�ʱ��״̬��ΪSTOP */
    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;
    ulTimerId      = pstRcvTimerMsg->ulName;
    TAF_MTA_StopTimer(ulTimerId);

    /* g_astMtaMsgProcTimerTab���������Ϣ�ַ� */
    for (ulLoop = 0; ulLoop < ulMsgCnt; ulLoop++)
    {
        if (g_astMtaMsgProcTimerTab[ulLoop].ulMsgType == ulTimerId)
        {
            g_astMtaMsgProcTimerTab[ulLoop].pProcMsgFunc((VOS_VOID *)pstMsg);
            return;
        }
    }

    /* û���ҵ�ƥ�����Ϣ */
    if (ulMsgCnt == ulLoop)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvTimerMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvNasMsg
 ��������  : ��������ATģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvNasMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcMmaTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcNasTab)/sizeof(MTA_MSG_PROC_STRU);

    /*g_astMtaMsgProcMmaTab���������Ϣ�ַ�*/
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcNasTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvNasMsg: Msg Id is invalid!");
    }

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvCtasMsg
 ��������  : ��������CTASģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : h00313353
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvCtasMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcCtasTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcCtasTab)/sizeof(MTA_MSG_PROC_STRU);

    /* g_astMtaMsgProcCtasTab���������Ϣ�ַ�*/
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcCtasTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvCtasMsg: Msg Id is invalid!");
    }

    return;
}
#endif

/* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTafAgentMsg
 ��������  : ��������TAFAGENTģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��28��
    ��    ��   : y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTafAgentMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcTafAgentTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcTafAgentTab)/sizeof(MTA_MSG_PROC_STRU);

    /*g_astMtaMsgProcTafAgentTab���������Ϣ�ַ�*/
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcTafAgentTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvTafAgentMsg: Msg Id is invalid!");
    }

    return;
}

/* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */


#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAcpuOmMsg
 ��������  : ��������A��OMģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ����ErrLog�ϱ�������ģʽ��չĿ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAcpuOmMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcAcpuOmTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcAcpuOmTab)/sizeof(MTA_MSG_PROC_STRU);

    /*g_astMtaMsgProcAcpuOmTab���������Ϣ�ַ�*/
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcAcpuOmTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAcpuOmMsg: Msg Id is invalid!");
    }

    return;
}
#endif

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvMtcMsg
 ��������  : ��������MTCģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��21��
    ��    ��   : l00198894
    �޸�����   : V9R1C50 SVLTE������ѡ��Ŀ����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvMtcMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcMtcTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcMtcTab)/sizeof(MTA_MSG_PROC_STRU);

    /*g_astMtaMsgProcMtcTab���������Ϣ�ַ�*/
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcMtcTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvMtcMsg: Msg Id is invalid!");
    }

    return;
}
#endif

/* Added by l00198894 for ����+ECID����, 2013-12-10, begin */
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcMsg
 ��������  : ��������LRRCģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : l00198894
    �޸�����   : ����+ECID����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcLrrcTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcLrrcTab)/sizeof(MTA_MSG_PROC_STRU);

    /*g_astMtaMsgProcLrrcTab���������Ϣ�ַ�*/
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcLrrcTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvLrrcMsg: Msg Id is invalid!");
    }

    return;
}
#endif
/* Added by l00198894 for ����+ECID����, 2013-12-10, end */

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvPhyStartMsg
 ��������  : ��������DSP_PID_STARTUPģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

1.��    ��   : 2013��3��26��
  ��    ��   : y00176023
  �޸�����   : DSDS GUNAS II��Ŀ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvDspStartMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;
    MSG_HEADER_STRU                    *pstMsgHeader    = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgHeader->ulMsgName = pstMsgHeader->ulMsgName & 0xffff;

    /* ��g_astMtaMsgProcDspStartTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcDspStartTab)/sizeof(MTA_MSG_PROC_STRU);

    /*g_astMtaMsgProcDspStartTab���������Ϣ�ַ�*/
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcDspStartTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvDspStartMsg: Msg Id is invalid!");
    }

    return;
}


#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTdsMsg
 ��������  : ��������TRRCģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��20��
    ��    ��   : g00261581
    �޸�����   : ����Freq Lock����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTdsMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcTdsTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcTdsTab)/sizeof(MTA_MSG_PROC_STRU);

    /* g_astMtaMsgProcTdsTab���������Ϣ�ַ� */
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcTdsTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvTdsMsg: Msg Id is invalid!");
    }

    return;
}
#endif

#if 0
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTLphyAgentMsg
 ��������  : ��������TLPHY����ģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTLphyAgentMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcTLphyAgentTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcTLphyAgentTab)/sizeof(MTA_MSG_PROC_STRU);

    /*g_astMtaMsgProcTLphyAgentTab���������Ϣ�ַ�*/
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcTLphyAgentTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvLphyMsg: Msg Id is invalid!");
    }

    return;
}
#endif

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvCcbtMsg
 ��������  : ��������CCBTģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��26��
    ��    ��   : w00242748
    �޸�����   : ��̬������Ŀ
*****************************************************************************/
VOS_VOID TAF_MTA_RcvCcbtMsg(struct MsgCB *pstMsg)
{
    CCBT_MTA_MSG_HEADER_STRU           *pstMsgHeader = VOS_NULL_PTR;

    pstMsgHeader = (CCBT_MTA_MSG_HEADER_STRU *)pstMsg;

    switch (pstMsgHeader->enMsgId)
    {
        case ID_CCBT_MTA_LOAD_PS_RRC_REQ :
            TAF_MTA_RcvCcbtLoadPsRrcReq(pstMsg);
            break;

        case ID_CCBT_MTA_QRY_PS_RRC_LOAD_STATUS_REQ :
            TAF_MTA_RcvCcbtQryPsRrcLoadStatusReq(pstMsg);
            break;

        default:
            MTA_ERROR_LOG("TAF_MTA_RcvCcbtMsg: Msg Id is invalid!");
            break;
    }

    return;
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvUsimmMsg
 ��������  : ��������USIMMģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��18��
    ��    ��   : z00316370
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvUsimmMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtaMsgProcCtasTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtaMsgProcUsimmTab)/sizeof(MTA_MSG_PROC_STRU);

    /* g_astMtaMsgProcCtasTab���������Ϣ�ַ�*/
    ulRst = TAF_MTA_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtaMsgProcUsimmTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvUsimmMsg: Msg Id is invalid!");
    }

    return;
}
#endif


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvRcmMsg
 ��������  : ��������RCMģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��25��
    ��    ��   : c00299064
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvRcmMsg(struct MsgCB *pstMsg)
{
    RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU          *pstCnf               = VOS_NULL_PTR;

    pstCnf = (RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU*)pstMsg;


    switch (pstCnf->usMsgID)
    {
        case ID_RCM_MTA_AFC_CLK_INFO_QRY_CNF:

            TAF_MTA_RcvRcmAfcInfoCnf((VOS_VOID*)pstMsg);

            break;

        default:
            MTA_ERROR_LOG("TAF_MTA_RcvRcmMsg: unkown msg id");
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_ProcMsg
 ��������  : �ַ�����ģ�鷢��MTA����Ϣ
 �������  : struct MsgCB * pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ErrLog&FTM��Ŀ
  3.��    ��   : 2013��10��21��
    ��    ��   : l00198894
    �޸�����   : V9R1C50 SVLTE������ѡ��Ŀ����
  4.��    ��   : 2013��4��1��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:���Ӷ�����㷢���ĳ�ʼ����Ϣ�Ĵ���
  5.��    ��   : 2015��6��17��
    ��    ��   : zwx247453
    �޸�����   : Refclkfreq��Ŀ:���Ӷ�����㷢����AFC����״̬��Ϣ�Ĵ���
*****************************************************************************/
VOS_VOID  TAF_MTA_ProcMsg (struct MsgCB *pstMsg)
{
    /* ��ϢΪ�գ�ֱ�ӷ��� */
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_MTA_ProcMsg: PstMsg is NULL!");
        return;
    }

    /* ���ݷ��ͷ�PID���ַ���Ϣ */
    switch (pstMsg->ulSenderPid)
    {
        case WUEPS_PID_AT:
            TAF_MTA_RcvAtMsg(pstMsg);
            break;
        case WUEPS_PID_WCOM:
            TAF_MTA_RcvWcomMsg(pstMsg);
            break;
        case UEPS_PID_GAS:
            TAF_MTA_RcvGasMsg(pstMsg);
            break;
        case DSP_PID_GPHY:
            TAF_MTA_RcvGphyMsg(pstMsg);
            break;
        case DSP_PID_WPHY:
            TAF_MTA_RcvWphyMsg(pstMsg);
            break;
        case WUEPS_PID_TC:
            TAF_MTA_RcvTcMsg(pstMsg);
            break;
        case VOS_PID_TIMER:
            TAF_MTA_RcvTimerMsg(pstMsg);
            break;

        case WUEPS_PID_WRR:
            TAF_MTA_RcvWrrMsg(pstMsg);
            break;

        case DSP_PID_APM:
            TAF_MTA_RcvApmMsg(pstMsg);
            break;

        case WUEPS_PID_MMA:
            TAF_MTA_RcvNasMsg(pstMsg);
            break;
        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        case ACPU_PID_TAFAGENT:
            TAF_MTA_RcvTafAgentMsg(pstMsg);
            break;
        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
#if (FEATURE_ON == FEATURE_PTM)
        case MSP_PID_DIAG_APP_AGENT:
            TAF_MTA_RcvAcpuOmMsg(pstMsg);
            break;
#endif
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
        case UEPS_PID_MTC:
            TAF_MTA_RcvMtcMsg(pstMsg);
            break;
#endif
        /* Added by l00198894 for ����+ECID����, 2013-12-10, begin */
#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_ERRC:
            TAF_MTA_RcvLrrcMsg(pstMsg);
            break;
#endif
        /* Added by l00198894 for ����+ECID����, 2013-12-10, end */

        case DSP_PID_STARTUP:
            TAF_MTA_RcvDspStartMsg(pstMsg);
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        case TPS_PID_RRC:
            TAF_MTA_RcvTdsMsg(pstMsg);
            break;
#endif

#if 0
        case TLPHY_PID_RTTAGENT:
            TAF_MTA_RcvTLphyAgentMsg(pstMsg);
            break;
#endif

        case TLPHY_PID_RTTAGENT:
            TAF_MTA_RcvRttAgentMsg(pstMsg);
            break;

        /* Added by lwx277467 for ����+CEUS����, 2015-09-10, begin */
#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_MM:
            TAF_MTA_RcvNasMsg(pstMsg);
            break;
#endif
        /* Added by lwx277467 for ����+CEUS����, 2015-09-10, end */

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
        case CCPU_PID_CBT:
            TAF_MTA_RcvCcbtMsg(pstMsg);
            break;
#endif
        case WUEPS_PID_MMC:
            TAF_MTA_RcvNasMsg(pstMsg);
            break;
		
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case CPROC_PID_1X_CTAS:
            TAF_MTA_RcvCtasMsg(pstMsg);
            break;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case WUEPS_PID_USIM:
            TAF_MTA_RcvUsimmMsg(pstMsg);
            break;
#endif
        case DSP_PID_RCM:
            TAF_MTA_RcvRcmMsg(pstMsg);
            break;

        default:
            MTA_ERROR_LOG("TAF_MTA_ProcMsg: No opposite MsgPro Function!");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_InitCtx
 ��������  : MTA CTXģ���ʼ��
 �������  : pstMtaCtx:MTA��������Ϣ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
  2.��    ��   : 2013��07��22��
    ��    ��   : l00198894
    �޸�����   : V9R1 AGPS
  3.��    ��   : 2014��11��17��
    ��    ��   : l00198894
    �޸�����   : ECID�����Ʒ�߶�������
*****************************************************************************/
VOS_VOID  TAF_MTA_InitCtx(TAF_MTA_CONTEXT_STRU *pstMtaCtx)
{
    /* ��ʼ������¼XML������Դ�Ľṹ */
    pstMtaCtx->stAgpsCtx.stXmlText.pcBufHead   = VOS_NULL_PTR;
    pstMtaCtx->stAgpsCtx.stXmlText.pcBufCur    = VOS_NULL_PTR;

    /* ��ʼ�������ж�ʱ����Ϣ */
    TAF_MTA_InitAllTimers(pstMtaCtx->astTimerCtx);

    /* ��ʼ��AT�������� */
    TAF_MTA_InitCmdBufferQueue(TAF_MTA_GetCmdBufferQueueAddr());

    /* ��ʼ��GPS�ο�ʱ��״̬��Ϣ */
    TAF_MTA_InitRefClockInfo(&pstMtaCtx->stAgpsCtx.stRefClockInfo);

    /* ��ʼ��RF&Lcd��������ļ� */
    TAF_MTA_InitRfLcdIntrusionCtx(&pstMtaCtx->stMtaRfLcdCtx);

    TAF_MTA_InitEcidCfg(&pstMtaCtx->stAgpsCtx.stEcidCfg);

#if(FEATURE_ON == FEATURE_LTE)
    TAF_MTA_InitIsmCoex(pstMtaCtx->astIsmCoex);
#endif

#if (FEATURE_ON == FEATURE_PTM)
    TAF_MMA_InitInfoCltCtx(&pstMtaCtx->stInfoCltCtx);
#endif

    TAF_MTA_InitNetmonGsmInfo(&pstMtaCtx->stNetmonGsmInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_InitTask
 ��������  : MTA�����ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��06��28��
   ��    ��   : y00213812
   �޸�����   : V7R1C50 A-GPS��Ŀ��������

*****************************************************************************/
VOS_UINT32  TAF_MTA_InitTask( VOS_VOID )
{
    TAF_MTA_CONTEXT_STRU                *pstMtaCtx;

    /* ��ʼ��MTAģ��CTX */
    pstMtaCtx   = TAF_MTA_GetMtaCtxAddr();
    TAF_MTA_InitCtx(pstMtaCtx);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_InitPid
 ��������  : MTA��PID��ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE ip
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��28��
    ��    ��   : y00213812
    �޸�����   : V7R1C50 A-GPS��Ŀ��������
*****************************************************************************/
VOS_UINT32 TAF_MTA_InitPid(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch ( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            {
                /* ����MTAģ���ʼ������ */
                (VOS_VOID)TAF_MTA_InitTask();
            }break;
        default:
            break;
    }

    return VOS_OK;
}









#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
