/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcMsgPrioCompare.c
  �� �� ��   : ����
  ��    ��   : zhoujun 40661
  ��������   : 2011��9��27��
  ����޸�   :
  ��������   : NasMmcMsgCompare.h��ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��9��27��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "NasComm.h"
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
/* ɾ��ExtAppMmcInterface.h*/
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */
#include  "MmcMmInterface.h"
#include  "MmcGmmInterface.h"
#include  "NasMmcSndInternalMsg.h"
#include  "UsimPsInterface.h"
#include  "NasMmcMsgPrioCompare.h"
#include  "NasMmcFsmSyscfg.h"
#include  "NasMmcFsmPlmnSelectionTbl.h"
#include  "NasMmcFsmPLmnListTbl.h"
#include  "NasMmcFsmBgPlmnSearchTbl.h"
#include  "NasMmcFsmAnyCellSearchTbl.h"
#include  "NasMmlCtx.h"
#include  "NasMmcCtx.h"
#include  "NasMmlLib.h"
#include  "siappstk.h"

/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

#include "PsRrmInterface.h"

#include "NasMmcComFunc.h"

#include "NasMmcFsmPlmnSelection.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_MSG_PRIO_COMPARE_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithInterSysCcoTbl
 ȫ�ֱ���˵��  : MMC CCO ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/

NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysCcoTbl[] =
{
    /* InterSys Cco�������յ�MMC����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithInterSysCco),
};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithInterSysHoTbl
 ȫ�ֱ���˵��  : MMC HO ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysHoTbl[] =
{

    /* InterSys HO�������յ�MMC����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithInterSysHo),

};

/* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithInterSysCellReselTbl
 ȫ�ֱ���˵��  : MMC cell resel ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
 2.��    ��   : 2012��11��15��
   ��    ��   : s00217060
   �޸�����   : DTS2012082007133:SYSCFG���û�ָ���ѿ��Դ��С����ѡ״̬��
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysCellReselTbl[] =
{
    /* InterSys cellresel�������յ��û�ָ�������������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithInterSysCellResel),


    /* InterSys cellresel�������յ�syscfg�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithInterSysCellResel),

    /* InterSys cellresel�������յ��ػ��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithInterSysCellResel),

    /* InterSys cellresel�������յ�DETACH�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_DETACH_REQ),
                             NAS_MMC_CompareDetachReqPrioWithInterSysCellResel),

    /* InterSys cellresel�������յ�power save�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithInterSysCellResel),


    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_PLMN_SEARCH_IND),
                             NAS_MMC_ComparePlmnSearchIndPrioWithInterSysCellResel),

    /* InterSys cellresel�������յ�MMC����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithInterSysCellResel),
};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithInterSysOosTbl
 ȫ�ֱ���˵��  : MMC OOS ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
 2.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysOosTbl[] =
{

    /* OOS�������յ��ػ��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithInterSysOos),


    /* OOS�������յ��û���ѡ�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithInterSysOos),

    /* OOS�������յ��û�LIST�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithInterSysOos),
#if (FEATURE_ON == FEATURE_CSG)
    /* OOS�������յ��û�CSG �б��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
                             NAS_MMC_CompareUserCsgListPrioWithInterSysOos),


    /* OOS�������յ�TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH��ʱ����ʱ��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH),
                             NAS_MMC_CompareUserCsgListPrioWithInterSysOos),
#endif

    /* OOS�������յ��û�ָ�������������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithInterSysOos),


    /* OOS�������յ�syscfg�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithInterSysOos),


    /* OOS�������յ�TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithInterSysOos),

    /* OOS�������յ�TI_NAS_MMC_AVAILABLE_TIMER�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_AVAILABLE_TIMER),
                             NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
    /* OOS�������յ�TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithInterSysOos),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */


    /* OOS�������յ�TI_NAS_MMC_FORBID_LA_TIMER_LEN�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN),
                             NAS_MMC_CompareTiForbidLaTimerExpiredPrioWithInterSysOos),

    /* OOS�������յ��û�MMCMM_CM_SERVICE_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CM_SERVICE_IND),
                             NAS_MMC_CompareCmServiceIndPrioWithInterSysOos),
};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithPlmnSelectionTbl
 ȫ�ֱ���˵��  : MMC plmn selection ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
 2.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 3.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 4.��    ��   : 2015��5��7��
   ��    ��   : b00269685
   �޸�����   : ���Ӵ��csfb ��������������
 5.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithPlmnSelectionTbl[] =
{

    /* PlmnSelection�������յ��ػ��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithPlmnSelection),

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    /* PlmnSelection�������յ�PowerSave�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithPlmnSelection),
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithPlmnSelection),
#endif

    /* PlmnSelection�������յ�SYSCFG�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection),

    /* PlmnSelection�������յ��û���ѡ�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithPlmnSelection),

    /* PlmnSelection�������յ��û�LIST�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),

    /* PlmnSelection�������յ��û�LIST�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),

#if (FEATURE_ON == FEATURE_CSG)
    /* PlmnSelection�������յ��û�CSG �б��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
                             NAS_MMC_CompareUserCsgListPrioWithPlmnSelection),


    /* PlmnSelection�������յ�TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH��ʱ����ʱ��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH),
                             NAS_MMC_CompareUserCsgListPrioWithPlmnSelection),
#endif

    /* PlmnSelection�������յ��û�ָ�������������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection),

    /* PlmnSelection�������յ��û�MMCMM_CM_SERVICE_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CM_SERVICE_IND),
                             NAS_MMC_CompareCmServiceIndPrioWithPlmnSelection),

    /* Modified by z00161729 for DCM�����������������, 2012-8-13, begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* PlmnSelection�������յ��û�MMCMM_CM_SERVICE_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CSFB_ABORT_IND),
                             NAS_MMC_CompareCsfbAbortIndPrioWithPlmnSelection),

    /* PlmnSelection�������յ�ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SERVICE_RESULT_IND),
                             NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnSelection),

#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-13, end */

    /* PlmnSelection�������յ��û�MMCMM_PLMN_SEARCH_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_PLMN_SEARCH_IND),
                             NAS_MMC_ComparePlmnSearchIndPrioWithPlmnSelection),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, begin */
    /* PlmnSelection�������յ�TI_NAS_MMC_CONTROL_FIRST_SEARCH_PLMN_TIMER��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_ComparePlmnSearchPhaseOneTotalTimePrioWithPlmnSelection),
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, end */

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_DPLMN_SET_REQ),
                             NAS_MMC_CompareDplmnSetReqPrioWithPlmnSelection),

};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithAnyCellTbl
 ȫ�ֱ���˵��  : MMC any cell ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
 2.��    ��   : 2012��5��12��
   ��    ��   : w00176964
   �޸�����   : GUL BG��Ŀ����
 3.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 4.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 5.��    ��   : 2014��7��3��
   ��    ��   : z00161729
   �޸�����   : DSDS III����
 6.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithAnyCellTbl[] =
{
    /* anycell�������յ�SYSCFG�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection),

    /* anycell �������յ��ػ��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithPlmnSelection),

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    /* PlmnSelection�������յ�PowerSave�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithPlmnSelection),
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

    /* anycell�������յ��û���ѡ�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithPlmnSelection),

    /* anycell�������յ��û�LIST�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                            NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),
#if (FEATURE_ON == FEATURE_CSG)
    /* anycell�������յ��û�CSG �б��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
                             NAS_MMC_CompareUserCsgListPrioWithPlmnSelection),


    /* anycell�������յ�TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH��ʱ����ʱ��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH),
                             NAS_MMC_CompareUserCsgListPrioWithPlmnSelection),
#endif

    /* anycell�������յ��û�ָ�������������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection),

    /* Modified by z00161729 for DCM�����������������, 2012-8-13, begin */
    /* anycell�������յ��û�MMCMM_CM_SERVICE_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CM_SERVICE_IND),
                             NAS_MMC_CompareCmServiceIndPrioWithAnyCellSearch),
    /* Modified by z00161729 for DCM�����������������, 2012-8-13, end */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CSFB_ABORT_IND),
                             NAS_MMC_CompareCsfbAbortIndPrioWithAnyCellSearch),
#endif

#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithAnyCellSearch),
#endif

    /* anycell�������յ��û�LIST�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),

    /* anycell�������յ��û�MMCMM_PLMN_SEARCH_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_PLMN_SEARCH_IND),
                             NAS_MMC_ComparePlmnSearchIndPrioWithAnyCellSearch),
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, begin */
    /* PlmnSelection�������յ�TI_NAS_MMC_CONTROL_FIRST_SEARCH_PLMN_TIMER��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimePrioWithAnyCellSearch),
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, end */
};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithSysCfgTbl
 ȫ�ֱ���˵��  : MMC syscfg ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithSysCfgTbl[] =
{

    /* SYSCFG�������յ�MMC����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithSysCfg),

};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithPlmnListTbl
 ȫ�ֱ���˵��  : MMC Plmn List ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
 2.��    ��   : 2012��5��10��
   ��    ��   : w00176964
   �޸�����   : GUL BG������Ŀ����
 3.��    ��   : 2012��6��4��
   ��    ��   : t00212959
   �޸�����   : GUL BG������Ŀ����
 4.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 5.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 6.��    ��   : 2014��7��3��
   ��    ��   : z00161729
   �޸�����   : DSDS III����
 7.��    ��   : 2015��9��8��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithPlmnListTbl[] =
{

    /* �ڲ�list�����ʱ�û�list�����������յ�ID_MSCC_MMC_POWER_OFF_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithPlmnList),

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    /* PlmnSelection�������յ�PowerSave�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithPlmnList),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithPlmnList),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithPlmnList),
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

    /* �ڲ�list�����������յ�ID_MSCC_MMC_SYS_CFG_SET_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithPlmnList),


    /* �ڲ�list�����������յ�MSCC_MMC_PLMN_SPECIAL_REQ_STRU����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithPlmnList),


    /* �ڲ�list�����������յ�ID_MSCC_MMC_PLMN_SPECIAL_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithPlmnList),
#if (FEATURE_ON == FEATURE_CSG)
    /* �ڲ�list�������յ��û�CSG �б��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
                             NAS_MMC_CompareUserCsgListPrioWithPlmnList),
#endif

    /* �ڲ�list�����������յ�ID_MSCC_MMC_PLMN_LIST_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnList),

    /* �ڲ�list�����������յ�ID_MSCC_MMC_DETACH_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_DETACH_REQ),
                             NAS_MMC_CompareUserDetachReqPrioWithPlmnList),

    /* list�����������յ�WAS RRMM_SUSPEND_IND ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithPlmnList),

    /* list�����������յ�GAS RRMM_SUSPEND_IND ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithPlmnList),

#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithPlmnList),
#endif

#if (FEATURE_ON == FEATURE_LTE)

    /* LIST�����������յ�LMM�Ĺ���ָʾ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND ),
                             NAS_MMC_CompareLmmSuspendIndPrioWithPlmnList),

    /* Modified by z00161729 for DCM�����������������, 2012-8-13, begin */
    /* LIST�����������յ�ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SERVICE_RESULT_IND),
                             NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnList),

    /* Modified by z00161729 for DCM�����������������, 2012-8-13, end */

#endif

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_RRM, ID_RRM_PS_STATUS_IND),
                             NAS_MMC_CompareRrmPsStatusIndPrioWithPlmnList),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
    /* OOS�������յ�TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithPlmnList),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */

};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithBgSearchTbl
 ȫ�ֱ���˵��  : MMC Bg search ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�

 2.��    ��   : 2011��11��10��
   ��    ��   : zhoujun 40661
   �޸�����   : ����RRMM_SUSPEND_INDԭ������ȼ��Ƚ�

 3.��    ��   : 2012��4��27��
   ��    ��   : w00176964
   �޸�����   : GUL BG��������:BG�����͸����ȼ�����״̬���ϲ�,����L�µ���Ϣ�Ƚ�
 4.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 5.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 6.��    ��   : 2014��7��3��
   ��    ��   : z00161729
   �޸�����   : DSDS III����
 7.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithBgSearchTbl[] =
{

    /* BG�����������յ�ID_MSCC_MMC_POWER_OFF_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePoweroffPrioWithBgSearch),

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    /* PlmnSelection�������յ�PowerSave�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithBgSearch),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithBgSearch),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithBgSearch),
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

    /* BG�����������յ�ID_MSCC_MMC_PLMN_LIST_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithBgSearch),

    /* BG�����������յ�TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithBgSearch),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
    /* BG�ѹ������յ�TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithBgSearch),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */
#if (FEATURE_ON == FEATURE_CSG)
    /* BG�����������յ��û�CSG �б��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_CSG_LIST_SEARCH_REQ),
                             NAS_MMC_CompareUserCsgListPrioWithBgSearch),


    /* BG�����������յ�TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH��ʱ����ʱ��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH),
                             NAS_MMC_CompareUserCsgListPrioWithBgSearch),
#endif

    /* BG�����������յ�ID_MSCC_MMC_PLMN_SPECIAL_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithBgSearch),


    /* BG�����������յ�ID_MSCC_MMC_SYS_CFG_SET_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithBgSearch),

    /* BG�����������յ�MSCC_MMC_PLMN_SPECIAL_REQ_STRU����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithBgSearch),

    /* BG�����������յ�STK_NAS_STEERING_OF_ROAMING_IND����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(MAPS_STK_PID, STK_NAS_STEERING_OF_ROAMING_IND),
                             NAS_MMC_CompareStkRoamingIndPrioWithBgSearch),

    /* BG�����������յ�PS_USIM_REFRESH_IND����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(MAPS_PIH_PID, USIMM_STKREFRESH_IND),
                             NAS_MMC_CompareUsimRefreshPrioWithBgSearch),


    /* BG�����������յ�ID_MSCC_MMC_UPDATE_UPLMN_NTF����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_UPDATE_UPLMN_NTF),
                             NAS_MMC_CompareMsccUpdateUplmnNtfPrioWithBgSearch),


    /* BG�����������յ��������յ������(WAS)�ϱ���RRMM_SUSPEND_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithBgSearch),


    /* BG�����������յ��������յ������(GAS)�ϱ���RRMM_SUSPEND_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithBgSearch),

    /* �ڲ�list�����������յ�ID_MSCC_MMC_PLMN_LIST_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_DETACH_REQ),
                             NAS_MMC_CompareUserDetachReqPrioWithBgSearch),


#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithBgSearch),
#endif

#if (FEATURE_ON == FEATURE_LTE)

    /* BG�����������յ��������յ�LMM�Ĺ���ָʾ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND ),
                             NAS_MMC_CompareLmmSuspendIndPrioWithBgSearch),

    /* Modified by z00161729 for DCM�����������������, 2012-8-13, begin */
    /* BG�����������յ�ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SERVICE_RESULT_IND),
                             NAS_MMC_CompareLmmServiceResultIndPrioWithBgSearch),

    /* Modified by z00161729 for DCM�����������������, 2012-8-13, end */
#endif

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_NVIM_OPLMN_REFRESH_IND),
                             NAS_MMC_CompareMmcNvimOPlmnRefreshIndPrioWithBgSearch),



};
/* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */


/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithGetGeoTbl
 ȫ�ֱ���˵��  : MMC GET GEO״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2015��05��08��
   ��    ��   : sunjitan 00193151
   �޸�����   : �½�
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithGetGeoTbl[] =
{
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithGetGeo),
};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithPowerOffTbl
 ȫ�ֱ���˵��  : MMC power off ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2015��7��9��
   ��    ��   : w00242748
   �޸�����   : �½�

*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithPowerOffTbl[] =
{

    /* BG�����������յ�ID_MSCC_MMC_POWER_OFF_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_RRM, ID_RRM_PS_STATUS_IND),
                             NAS_MMC_CompareRrmPsStatusIndPrioWithPowerOff)
};



/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioHighPlmnSearchCompareTbl
 ȫ�ֱ���˵��  : MMC״̬���ȽϺ�����
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
NAS_MMC_FSM_MSG_COMPARE_STRU g_astMmcMsgCompareTbl[] =
{
     /* CCO״̬���ȽϺ�����*/
    NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_CCO,
                     g_astMmcMsgPrioCompareWithInterSysCcoTbl),

    /* HO״̬���ȽϺ�����*/
    NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_HO,
                      g_astMmcMsgPrioCompareWithInterSysHoTbl),


     /* cellresel״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_CELLRESEL,
                       g_astMmcMsgPrioCompareWithInterSysCellReselTbl),

     /* OOS״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_OOS,
                       g_astMmcMsgPrioCompareWithInterSysOosTbl),


     /* PLMN Selection״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_PLMN_SELECTION,
                       g_astMmcMsgPrioCompareWithPlmnSelectionTbl),


     /* anycell״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_ANYCELL_SEARCH,
                       g_astMmcMsgPrioCompareWithAnyCellTbl),

     /* SYSCFG״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_SYSCFG,
                       g_astMmcMsgPrioCompareWithSysCfgTbl),


     /* PLMN LIST״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_PLMN_LIST,
                       g_astMmcMsgPrioCompareWithPlmnListTbl),

     /* BG����״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_BG_PLMN_SEARCH,
                       g_astMmcMsgPrioCompareWithBgSearchTbl),

     /* GET GEO״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_GET_GEO,
                       g_astMmcMsgPrioCompareWithGetGeoTbl),

     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_POWER_OFF,
                        g_astMmcMsgPrioCompareWithPowerOffTbl)

};

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsTrigerDisableLte_MoDetach
 ��������  : �ж��û�detach��ʱ���Ƿ���Ҫ����disable LTE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫdisable LTE
             VOS_FALSE:����Ҫdisable LTE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��05��10��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��12��28��
   ��    ��   : s46746
   �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
 3.��    ��   : 2015��4��17��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsTrigerDisableLte_MoDetach(
    MSCC_MMC_DETACH_REQ_STRU           *pstDetachReq
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return VOS_FALSE;
    }

    /* ��ȡLTE������״̬ */
    enLCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLCapabilityStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* �����LTE onlyģʽ����Ҫdisable LTE */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* ��ȡLTE��UEģʽ */
    enLUeMode = NAS_MML_GetLteUeOperationMode();

    /* UEģʽΪCS PS mode1��CS PS mode2��Ҫdisable LTE */
    if ((NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2 == enLUeMode)
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 == enLUeMode))
    {
        /* ���detachΪ�û������������仯�����ģ��Ұ���PS detach���ͣ�����Ҫdisable LTE */
        if (VOS_TRUE == NAS_MMC_IsDetachReqestDisableLte(pstDetachReq->enDetachType,
                                                         pstDetachReq->enDetachReason))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif



/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareMmcMsgPrioWithInterSysCco
 ��������  : ��MMC�յ�����Ϣ��CCO״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysCco(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareMmcMsgPrioWithInterSysHo
 ��������  : ��MMC�յ�����Ϣ��HO״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysHo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnSpecPrioWithInterSysCellResel
 ��������  : ���û�ָ��������Ϣ��cell resel״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��15��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSysCfgSetPrioWithInterSysCellResel
 ��������  : ��SYSCFG��Ϣ��cell resel״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��15��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerOffPrioWithInterSysCellResel
 ��������  : ���ػ�������Ϣ��cell resel״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��19��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerSavePrioWithInterSysCellResel
 ��������  : ��power save������Ϣ��cell resel״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��11��6��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareDetachReqPrioWithInterSysCellResel
 ��������  : ��DetachReq��Ϣ��cell resel״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��11��20��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��27��
   ��    ��   : w00176964
   �޸�����   : PS���detach��Ҫ���״̬��
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareDetachReqPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MSCC_MMC_DETACH_REQ_STRU             *pstTafDetachReq = VOS_NULL_PTR;

    pstTafDetachReq = (MSCC_MMC_DETACH_REQ_STRU *)pstMsg;

    /* ps���detach�ᴥ��disable LTE,��Ҫ��� */
    if ((NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI == pstTafDetachReq->enDetachType)
     || (NAS_MSCC_PIF_DETACH_TYPE_GPRS    == pstTafDetachReq->enDetachType))
    {
        *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    *penAbortType     = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_BUTT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePlmnSearchIndPrioWithInterSysCellResel
 ��������  : MMCMM_PLMN_SEARCH_IND����ϵͳ״̬�������ȼ��Ƚ�
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
             NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnSearchIndPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_PLMN_SEARCH_IND_STRU         *pstPlmnSearchInd    = VOS_NULL_PTR;

    pstPlmnSearchInd          = (MMCMM_PLMN_SEARCH_IND_STRU*)pstMsg;

    /* �����ض���ʧ�ܻ��˵�LTE������ʱ������ */
    if (MM_MMC_PLMN_SEARCH_TYPE_CSFB_BACK_LTE != pstPlmnSearchInd->enPlmnSearchType)
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* �ض���ʧ�ܻ��˵�LTE������ʱ����� */
    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
     return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareMmcMsgPrioWithInterSysCellResel
 ��������  : ��MMC�յ�����Ϣ��cell resel״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerOffPrioWithInterSysOos
 ��������  : ���ػ���Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserReselPrioWithInterSysOos
 ��������  : ���û���ѡ��Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserReselPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserCsgListPrioWithInterSysOos
 ��������  : ���û�CSG LIST������Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnListPrioWithInterSysOos
 ��������  : ���û�LIST������Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnSpecPrioWithInterSysOos
 ��������  : ���û�SPEC������Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSysCfgSetPrioWithInterSysOos
 ��������  : ��SYSCFG������Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos
 ��������  : ��available timer��ʱ��Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithInterSysOos
 ��������  : ��TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER��ʱ��Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��11��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiForbidLaTimerExpiredPrioWithInterSysOos
 ��������  : ��forbid la timer��ʱ��Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiForbidLaTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareCmServiceIndPrioWithInterSysOos
 ��������  : ��CM Service Ind��Ϣ��oos״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��15��
   ��    ��   : z00161729
   �޸�����   : DTS2013062406563:WAS����̬OOS,T305�����ڼ�ֻ���ڱ�ϵͳ���ѵ�Чplmn��
                 ����פ������ϵͳ�������磬Ҳ������ϵͳ�½��������������޷��ܿ�����������ע�ᣬnas����޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_CM_SERVICE_IND_STRU          *pstServiceIndMsg = VOS_NULL_PTR;

    pstServiceIndMsg        = (MMCMM_CM_SERVICE_IND_STRU*)pstMsg;

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* ��������ֱ�Ӷ�������Ϣ,��������������� */
    if (MM_EMERGENCY_CALL_TRUE == pstServiceIndMsg->ulEmcFlg)
    {
        *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerOffPrioWithPlmnSelection
 ��������  : ���ػ���Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerSavePrioWithPlmnSelection
 ��������  : ��Power Save��Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareAcqReqPrioWithPlmnSelection
 ��������  : ����ȡ��Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareRegReqPrioWithPlmnSelection
 ��������  : ��ע����Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareRegReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePlmnSearchPhaseOneTotalTimePrioWithPlmnSelection
 ��������  : ��TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER��ʱ��Ϣ��Plmn selection ״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��8��31��
   ��    ��   : c00318887
   �޸�����   : �½�
  2.��    ��   : 2015��12��22��
    ��    ��   : c00318887
    �޸�����   : DTS2015121106060: phaseI��ʱ����ʱ������û�ָ���ѵȳ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnSearchPhaseOneTotalTimePrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                       enPlmnSearchScene;
    
    enPlmnSearchScene                   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if ((NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED                      == enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH  == enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH == enPlmnSearchScene))
    {
        *penAbortType                   = NAS_MMC_ABORT_FSM_DELAY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;    
    }

    *penAbortType                       = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareDplmnSetReqPrioWithPlmnSelection
 ��������  : AP�·���Ԥ��DPLMNʱ��ѡ��״̬�����ȼ��Ƚ�
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
             NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��13��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareDplmnSetReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          i;
    VOS_INT32                           lVersionCmpRst;
    VOS_UINT32                          ulHplmnCmpRslt;
    VOS_UINT32                          ulCurrState;
    NAS_MML_PLMN_ID_STRU                stHplmnId;
    VOS_UINT8                          *pucImsi              = VOS_NULL_PTR;
    NAS_MMC_INTER_DPLMN_SET_REQ_STRU   *pstDplmnSetReq       = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU  *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList       = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo        = VOS_NULL_PTR;

    /* ��ϵ�ǰ����������:
        1. ��������Ϊ��������
        2. ��ǰ���ڽ�����������������
        3. AP�·���DPLMN�б���version��HPLMN�뵱ǰʹ�õĲ�ͬ
    */

    pstDplmnSetReq          = (NAS_MMC_INTER_DPLMN_SET_REQ_STRU *)pstMsg;
    pstDPlmnNPlmnCfgInfo    = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    pstPrioRatList          = NAS_MML_GetMsPrioRatList();
    ulCurrState             = NAS_MMC_GetFsmTopState();

    /* ����ѡ��״̬������Ҫ��� */
    if (NAS_MMC_FSM_PLMN_SELECTION  != NAS_MMC_GetCurrFsmId())
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* ���ǿ���������������һ��������Ч�����β���� */
    if (NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON != NAS_MMC_GetPlmnSearchScene_PlmnSelection())
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* û�н����������򣬵�ǰ������RPLMN/HPLMN������Ҫ��� */
    if (VOS_FALSE == NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(pstPrioRatList))
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* �����ɹ�֮�����Щ״̬������Ҫ��� */
    if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND       == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND        == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND   == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND   == ulCurrState))
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    pucImsi     = NAS_MML_GetSimImsi();
    stHplmnId   = NAS_MML_GetImsiHomePlmn(pucImsi);

    /* �Ƚ�version�Ƿ���ͬ */
    lVersionCmpRst = PS_MEM_CMP(pstDplmnSetReq->aucVersionId,
                                pstDPlmnNPlmnCfgInfo->aucVersionId,
                                NAS_MCC_INFO_VERSION_LEN);


    /* �汾�Ų�ͬ����Ҫ��ϵ�ǰ���� */
    if (0 != lVersionCmpRst)
    {
        NAS_TRACE_HIGH("version updating abort current plmn selection");

        *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* �Ƚϵ�ǰʹ�õ�hplmn�Ƿ���APԤ�õ�dplmn�б�����Ӧ��ehplmn list */
    ulHplmnCmpRslt = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stHplmnId,
                                                           pstDplmnSetReq->ucEhPlmnNum,
                                                           pstDplmnSetReq->astEhPlmnInfo);


    /* hplmn��APԤ�õ�DPLMN�б��У�����Ҫ��ϵ�ǰ���� */
    if (VOS_TRUE == ulHplmnCmpRslt)
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* �Ƚϵ�ǰ��EHPLMN�б��Ƿ���APԤ�õ����ظ��� */
    pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();

    ulHplmnCmpRslt      = VOS_FALSE;

    for (i = 0; i < pstEHPlmnInfo->ucEhPlmnNum; i++)
    {
        ulHplmnCmpRslt = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId),
                                                               pstDplmnSetReq->ucEhPlmnNum,
                                                               pstDplmnSetReq->astEhPlmnInfo);

        if (VOS_TRUE == ulHplmnCmpRslt)
        {
            *penAbortType = NAS_MMC_ABORT_BUTT;
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
        }
    }

    NAS_TRACE_HIGH("EHPLMN list changed abort current plmn selection");

    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}



/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimePrioWithAnyCellSearch
 ��������  : ��available timer��ʱ��Ϣ��AnyCell״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��11��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimePrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */


#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSrvAcqReqPrioWithPlmnSelection
 ��������  : ��ID_MSCC_MMC_SRV_ACQ_REQ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��23��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MSCC_MMC_SRV_ACQ_REQ_STRU           *pstSrvAcqReq = VOS_NULL_PTR;

    pstSrvAcqReq    = (MSCC_MMC_SRV_ACQ_REQ_STRU*)pstMsg;

    /* ����ǽ���������ֱ�Ӵ�ϣ��ǽ��������򻺴棬������״̬���˳�����
       �������״̬���˳���������������ֱ�ӻظ�ҵ�񴥷������ɹ������
       ������ٴδ���ҵ�񴥷��������������� */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL == pstSrvAcqReq->enSrvType)
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSrvAcqReqPrioWithAnyCellSearch
 ��������  : ��ID_MSCC_MMC_SRV_ACQ_REQ��anycell״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��23��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSrvAcqReqPrioWithPlmnList
 ��������  : ��ID_MSCC_MMC_SRV_ACQ_REQ��list����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��23��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSrvAcqReqPrioWithBgSearch
 ��������  : ��ID_MSCC_MMC_SRV_ACQ_REQ��bg����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��23��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

#endif


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection
 ��������  : ��SYSCFG������Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��07��02��
   ��    ��   : s46746
   �޸�����   : For CS/PS mode 1������EPS�����ͷŵĴ���
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 4.��    ��   : 2014��7��14��
   ��    ��   : w00242748
   �޸�����   : DTS2014063003419:SYSCFG���������ȼ����뼼����������NV���ƣ�ͬʱ
                �������״̬��(�����ȴ�CS/PSע����״̬)
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulNeedPlmnSearch;
    VOS_UINT32                          ulNeedHighPrioRat;

    ulCurrState         = NAS_MMC_GetFsmTopState();

    /* �жϵ�ǰSYSCFG�����Ƿ�ᴥ��SYSCFG���� */
    ulNeedPlmnSearch    = NAS_MMC_IsPlmnSelectionNeeded_SysCfg( (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)pstMsg );

    /* ���NV���ҵ�ǰδפ����������ȼ����뼼����PLMN�ϣ���Ҫ��� */
    ulNeedHighPrioRat   = NAS_MMC_IsRatPrioChangeTriggerPlmnSrch( NAS_MML_GetMsPrioRatList(),
                                    &((MSCC_MMC_SYS_CFG_SET_REQ_STRU *)pstMsg)->stRatPrioList);

    if ( (VOS_TRUE == NAS_MML_GetSyscfgTriHighRatSrchFlg())
      && (VOS_FALSE == ulNeedPlmnSearch)
      && (VOS_TRUE == ulNeedHighPrioRat) )
    {
        *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* �Բ���Ҫ���������������ж� */
    if  ( ( VOS_FALSE == ulNeedPlmnSearch )
       && ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND == ulCurrState )
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND == ulCurrState )))

    {
        /* ֱ����״̬���д��� */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

#if   (FEATURE_ON == FEATURE_LTE)

    /* ���ڲ���Ҫ���������,ֱ����״̬���д��� */
    if ( ( VOS_FALSE == ulNeedPlmnSearch )
      && ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE == ulCurrState )))
    {
        /* ֱ����״̬���д��� */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

#endif

    /* �����������Ҫ��ϵ�ǰ״̬�� */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserReselPrioWithPlmnSelection
 ��������  : ���û���ѡ��Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserReselPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserCsgListPrioWithPlmnSelection
 ��������  : ���û�CSG LIST������Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection
 ��������  : ���û�LIST������Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection
 ��������  : ���û�SPEC������Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
 1.��    ��   : 2012��06��07��
   ��    ��   : s00217060
   �޸�����   : For CS/PS mode 1����������פ��LTE�����״̬�ж�
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU      *pstUserPlmnInfo;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulRlt;

    ulCurrState         = NAS_MMC_GetFsmTopState();
    pstUserPlmnInfo     = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;

    *penAbortType       = NAS_MMC_ABORT_BUTT;

    /* ����Ҫ�ڵȴ�ע�����������ͷ�,��Ҫ����״̬�� */
    if ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND ==  ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND ==  ulCurrState ) )
    {
        /* ��ȡ��ǰפ��������Ϣ,�����յ�ϵͳ��Ϣ��ʱ��ȡ�϶�û������ */
        pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

        ulRlt           = NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCampPlmnInfo->stLai.stPlmnId),
                                               (NAS_MML_PLMN_ID_STRU*)(&(pstUserPlmnInfo->stPlmnId)));

        /* ��Ҫ�ж�PLMN ID�ͽ�������Ƿ���ͬ,��ͬ��ֱ�ӽ���״̬�� */
        if ( ( VOS_TRUE == ulRlt)
          && ( pstCampPlmnInfo->enNetRatType ==  pstUserPlmnInfo->enAccessMode ))
        {
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
        }
    }

    /* ����ڵȴ�ϵͳ��Ϣ����Ҫ���л��� */
    if ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND ==  ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND ==  ulCurrState ))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

#if   (FEATURE_ON == FEATURE_LTE)
    if ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE == ulCurrState ))
    {

        /* ��ȡ��ǰפ��������Ϣ,�����յ�ϵͳ��Ϣ��ʱ��ȡ�϶�û������ */
        pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

        ulRlt           = NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCampPlmnInfo->stLai.stPlmnId),
                                               (NAS_MML_PLMN_ID_STRU*)(&(pstUserPlmnInfo->stPlmnId)));

        /* ��Ҫ�ж�PLMN ID�ͽ�������Ƿ���ͬ,��ͬ��ֱ�ӽ���״̬�� */
        if ( ( VOS_TRUE == ulRlt)
          && ( pstCampPlmnInfo->enNetRatType ==  pstUserPlmnInfo->enAccessMode ))
        {
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
        }
    }

    /* ����ڵȴ�ϵͳ��Ϣ����Ҫ���л��� */
    if ( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND ==  ulCurrState )
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

#endif

    /* �����������Ҫ��� */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareCmServiceIndPrioWithPlmnSelection
 ��������  : ��CM Service Ind��Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 3.��    ��   : 2012��12��27��
   ��    ��   : t00212959
   �޸�����   : DTS2012122607665 L����������ʱ��Ƚϳ���Ӱ�����������Ҫ�������
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;
    MMCMM_CM_SERVICE_IND_STRU          *pstServiceIndMsg;

    pstServiceIndMsg        = (MMCMM_CM_SERVICE_IND_STRU*)pstMsg;
    ulCurrState             = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;
    /* ��������ֱ�Ӷ�������Ϣ */
    if (MM_EMERGENCY_CALL_FALSE == pstServiceIndMsg->ulEmcFlg)
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* �����͹���״̬ʱ��Ҫ��ϵ�ǰ״̬�� */
    if ( ( NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF      ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* Modified by z00161729 for DCM�����������������, 2012-8-13, begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* ��L���������״̬���L����ظ�״̬��Ҫ��ϵ�ǰ״̬�� */
    if ((NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF ==  ulCurrState)
      || (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE == ulCurrState)))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
         return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-13, end */

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareCsfbAbortIndPrioWithPlmnSelection
 ��������  : ��csfb abort ind��Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��7��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareCsfbAbortIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState   = NAS_MMC_GetFsmTopState();
    *penAbortType = NAS_MMC_ABORT_BUTT;

    /* �����͹���״̬ʱ��Ҫ��ϵ�ǰ״̬�� */
    if ( ( NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF      ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* ��L�Ĺ���ظ�״̬��Ҫ��ϵ�ǰ״̬�� */
    if (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF ==  ulCurrState)
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
         return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePlmnSearchIndPrioWithPlmnSelection
 ��������  : ��Plmn Search Ind��Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnSearchIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_PLMN_SEARCH_IND_STRU         *pstPlmnSearchInd;
    VOS_UINT32                          ulCurrState;
    VOS_UINT8                           ucIsLteSearched;

    ulCurrState               = NAS_MMC_GetFsmTopState();
    *penAbortType             = NAS_MMC_ABORT_BUTT;
    pstPlmnSearchInd          = (MMCMM_PLMN_SEARCH_IND_STRU*)pstMsg;
    ucIsLteSearched           = NAS_MMC_IsSpecRatSearched_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

    if ((NAS_MMC_FSM_PLMN_SELECTION       != NAS_MMC_GetCurrFsmId())
     || (MM_MMC_PLMN_SEARCH_TYPE_CSFB_END != pstPlmnSearchInd->enPlmnSearchType))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* ��������LTE�����Ѿ�����LTEʱ����Ҫ��ϵ�ǰ״̬�� */
    if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF == ulCurrState )
     || (VOS_TRUE                                            == ucIsLteSearched ))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* GU�����ɹ��ȴ�ϵͳ��Ϣ���ߵȴ�ע����ʱ���������״̬�� */
    if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND       == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND   == ulCurrState))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
     return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePlmnSearchIndPrioWithAnyCellSearch
 ��������  : anycell�������յ��û�MMCMM_PLMN_SEARCH_IND�������Ϣ���ȼ��Ƚ�
 �������  : ulEventType :��Ϣ����
             pstMsg      :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��25��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnSearchIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_PLMN_SEARCH_IND_STRU         *pstPlmnSearchInd;
    VOS_UINT32                          ulIsUsimStausValid;

    *penAbortType             = NAS_MMC_ABORT_BUTT;

    pstPlmnSearchInd          = (MMCMM_PLMN_SEARCH_IND_STRU*)pstMsg;
    ulIsUsimStausValid        = NAS_MML_IsUsimStausValid();

    if ( (NAS_MMC_FSM_ANYCELL_SEARCH       != NAS_MMC_GetCurrFsmId())
      || (MM_MMC_PLMN_SEARCH_TYPE_CSFB_END != pstPlmnSearchInd->enPlmnSearchType)
      || (VOS_FALSE                        == ulIsUsimStausValid))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
     return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareMmcMsgPrioWithSysCfg
 ��������  : ��MMC�յ�����Ϣ��SYSCFG״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    /* Ĭ�Ϸ�����Ϣ��Ҫ���� */
    *penAbortType = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerOffPrioWithPlmnList
 ��������  : ���ػ���Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerSavePrioWithPlmnList
 ��������  : ��Power Save��Ϣ��LIST״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareAcqReqPrioWithPlmnSelection
 ��������  : ����ȡ��Ϣ��LIST״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareRegReqPrioWithPlmnSelection
 ��������  : ��ע����Ϣ��LIST״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareRegReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSysCfgSetPrioWithPlmnList
 ��������  : ��SYSCFG������Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserReselPrioWithPlmnList
 ��������  : ���û���ѡ��Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserReselPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserCsgListPrioWithPlmnList
 ��������  : ���û�CSG�б�������Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnListWaitGuSearchCnfState
 ��������  : �ж��Ƿ���list������gu�����ظ�״̬
 �������  : ulState - ״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��list����״̬����gu�����ظ�״̬
             VOS_FALSE:����list����״̬����gu�����ظ�״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��22��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnListWaitGuSearchCnfState(
    VOS_UINT32                          ulCurrState
)
{
    if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState)
#if (FEATURE_ON == FEATURE_CSG)
      || (NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_CNF  ==  ulCurrState)
#endif
       ))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnSpecPrioWithPlmnList
 ��������  : ���û�ָ��������Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnListPrioWithPlmnList
 ��������  : ���û�LIST������Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��9��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareUserPlmnListPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserDetachReqPrioWithPlmnList
 ��������  : ���û�detach��Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��10��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2015��4��16��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareUserDetachReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulTrigerDisableLte;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    *penAbortType    = NAS_MMC_ABORT_BUTT;


    enRat = NAS_MML_NET_RAT_TYPE_BUTT;

    /* �жϵ�ǰ�û���detach�Ƿ�ᴥ��disable LTE */
    ulTrigerDisableLte      = NAS_MMC_IsTrigerDisableLte_MoDetach((MSCC_MMC_DETACH_REQ_STRU *)pstMsg);

    ulCurrState             = NAS_MMC_GetFsmTopState();

    if (VOS_TRUE == ulTrigerDisableLte)
    {
        /* ��ǰ��L�µ��ڲ�LIST�����������յ��û�detach��Ϣ,��CS/PS mode2����Ҫdisable
           LTE,��ʱ��Ҫ���L�µ��ڲ�LIST����,�����û���detach���� */
        if (NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF == ulCurrState)
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }

        /* ��ȡ�¸���Ҫ�����Ľ��뼼�� */
        (VOS_VOID)NAS_MMC_GetNextSearchingRat_PlmnList(&enRat);

        /* ��GU���ڲ��б�����ʱ,�������RRMM_NOT_CAMP_ON_IND��Ϣ�Գ�,����GU��L
           ����������û�detach������Ҫdisable LTE,��ʱ���ڼ�����L���ڲ�LIST����
           �˳�LIST����״̬���������detach */
        if (((NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SUSPEND_CNF == ulCurrState)
          || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SUSPEND_CNF == ulCurrState))
         && (NAS_MML_NET_RAT_TYPE_LTE    == enRat))
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }
#endif

    *penAbortType    = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSuspendIndPrioWithPlmnList
 ��������  : ��RRMM_SUSPEND_IND��Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��4��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��8��1��
    ��    ��   : w00167002
    �޸�����   : �ڵ�ϵͳ��Ϣʱ���յ���ϵͳ��Ϣ�����ϵ�ǰ״̬��������ϵͳ������
  3.��    ��   : 2015��9��8��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareSuspendIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    VOS_UINT32                          ulIsPlmnListWaitGuSearchCnfState;

    ulCurrState                      = NAS_MMC_GetFsmTopState();
    ulIsPlmnListWaitGuSearchCnfState = NAS_MMC_IsPlmnListWaitGuSearchCnfState(ulCurrState);

    *penAbortType   = NAS_MMC_ABORT_BUTT;


    /* LIST������������ϵͳָʾ�Գ�,RRC��ظ�List_REJ,Ϊ��֤����������ϵͳָʾ
       MMC�Ȼ��������Ϣ,�յ�List_REJ���˳�״̬��������Ĺ���ָʾ��Ϣ */
    if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
     && ((VOS_TRUE == ulIsPlmnListWaitGuSearchCnfState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_STOP_CNF    ==  ulCurrState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_STOP_CNF    ==  ulCurrState)
#if (FEATURE_ON == FEATURE_CSG)
      || (NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_STOP_CNF  ==  ulCurrState)
      || (NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_STOP_CNF  ==  ulCurrState)
#endif
      ))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* ע��״ֱ̬�ӽ���״̬���д��� */
    if ( ( NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND  ==  ulCurrState )
       || ( NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }


    /* �ڵ�ϵͳ��Ϣʱ��ֱ�Ӵ��LIST����״̬����������������²��ظ�SUSPEDN RSP,GAS��λ */
    if ( ( NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SYS_INFO_IND ==  ulCurrState )
       || ( NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SYS_INFO_IND ==  ulCurrState )))
    {
        *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* �����������ǰ�������һ�� */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareRrmPsStatusIndPrioWithPlmnList
 ��������  : ��ID_RRM_PS_STATUS_IND��list����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��9��8��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareRrmPsStatusIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState     = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;


    /* NO RFʱ����LIST�������ȴ�LIST�����ظ�ʱ,RRM֪ͨ��Դ����,LIST������ɺ�֪ͨ������,���ܴ����ظ�ȥע��Lģ,��Ҫ��
       �ȴ�LIST�����ظ��յ���Դ���ò����� */
    if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState)
#if (FEATURE_ON == FEATURE_LTE)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState)
#endif
#if (FEATURE_ON == FEATURE_CSG)
      || (NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_CNF == ulCurrState)
      || (NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_CNF == ulCurrState)
#endif
      ))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* NO RF�����LIST����״̬��,�������RRM֪ͨ��Դ����,��Ҫ��LIST
       �������̽����󴥷�һ������,��˸���Ϣ��Ҫ����,��LIST����״̬
       ���˳�����һ�� */
    *penAbortType   = NAS_MMC_MSG_COMPARE_PRIO_RSLT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}



/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithPlmnList
 ��������  : ��TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER��ʱ��Ϣ��PLMN LIST״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��11��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */


/* Modified by z00161729 for DCM�����������������, 2012-8-13, begin */

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareCmServiceIndPrioWithAnyCellSearch
 ��������  : ��CM Service Ind��Ϣ��anycell״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��12��28��
   ��    ��   : t00212959
   �޸�����   : DTS2012122607665 L�µ�ϵͳ��Ϣ��Ϻ󣬽������޷�����
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_CM_SERVICE_IND_STRU                              *pstServiceIndMsg;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;
    VOS_UINT32                                              ulCurrState;

    ulCurrState             =  NAS_MMC_GetFsmTopState();
#endif

    pstServiceIndMsg        = (MMCMM_CM_SERVICE_IND_STRU*)pstMsg;
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    /* ��������ֱ�Ӷ�������Ϣ */
    if (MM_EMERGENCY_CALL_FALSE == pstServiceIndMsg->ulEmcFlg)
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ��ȡ�¸�Ҫ������������뼼�� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    /* GU����״̬����һ��Ҫ�����Ľ��뼼��ΪL�һ���δanycell��������GU���뼼��ʱ��Ҫ��ϵ�ǰ״̬�� */
    if ((NAS_MMC_FSM_ANYCELL_SEARCH == NAS_MMC_GetCurrFsmId())
     && (enRat == NAS_MML_NET_RAT_TYPE_LTE)
     && ((NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF  ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SUSPEND_CNF  ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* CSFBʱ��L�����ظ�״̬��Ҫ��ϵ�ǰ״̬�� */
    if ((NAS_MMC_FSM_ANYCELL_SEARCH == NAS_MMC_GetCurrFsmId())
     && (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF == ulCurrState))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
#endif

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/* Modified by z00161729 for DCM�����������������, 2012-8-13, end */


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareCsfbAbortIndPrioWithAnyCellSearch
 ��������  : ��CM Service Ind��Ϣ��anycell״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��11��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareCsfbAbortIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState   = NAS_MMC_GetFsmTopState();
    *penAbortType = NAS_MMC_ABORT_BUTT;

    /* GU����״̬����һ��Ҫ�����Ľ��뼼��ΪL�һ���δanycell��������GU���뼼��ʱ��Ҫ��ϵ�ǰ״̬�� */
    if ((NAS_MMC_FSM_ANYCELL_SEARCH == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* CSFBʱ��L�����ظ�״̬��Ҫ��ϵ�ǰ״̬�� */
    if (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SUSPEND_CNF == ulCurrState)
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareLmmSuspendIndPrioWithPlmnList
 ��������  : List����״̬����ID_LMM_MMC_SUSPEND_IND��Ϣ�����ȼ��Ƚ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��4��
   ��    ��   : t00212959
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��9��8��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareLmmSuspendIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState     = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* LIST������������ϵͳָʾ�Գ�,LMM��ظ�List_REJ,Ϊ��֤����������ϵͳָʾ
       MMC�Ȼ��������Ϣ,�յ�List_REJ���˳�״̬��������Ĺ���ָʾ��Ϣ */
    if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_STOP_CNF    ==  ulCurrState )
#if (FEATURE_ON == FEATURE_CSG)
      || (NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF  ==  ulCurrState)
#endif
      ))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }


    /* ע��״ֱ̬�ӽ���״̬���д��� */
    if (( NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )
       || ( NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* �����������ǰ�������һ�� */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnList
 ��������  : List����״̬����ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ�����ȼ��Ƚ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���


 2.��    ��   : 2015��8��10��
   ��    ��   : w00167002
   �޸�����   : DTS2015080700349:��L���ڲ�LIST��ʱ���յ����У��յ�L��SERVICE
                RESULT��Ϣû�н��д���

 3.��    ��   : 2015��9��6��
   ��    ��   : z00359541
   �޸�����   : DTS2015081407087: �ӿڵ�����ɾ��bitOpReqType��
 4.��    ��   : 2015��9��8��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                                              ulCurrState;

    ulCurrState          = NAS_MMC_GetFsmTopState();
    *penAbortType        = NAS_MMC_ABORT_BUTT;

    /* CSFB������ʱ��L�����ظ�״̬���Lע����״̬��������ͷ�״̬��Ҫ��ϵ�ǰ״̬��  */

    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
          && ((NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState)
           || (NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )
           || (NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
#if (FEATURE_ON == FEATURE_CSG)
           || (NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_CNF  ==  ulCurrState)
#endif
           ))
        {
           *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnSelection
 ��������  : ��ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��12��27��
   ��    ��   : t00212959
   �޸�����   : DTS2012122607665 L�½�����,csps mode1 ��L��vplmn�����ͷ�ʱ��Ҫ��ϵ�ǰ״̬��
 3.��    ��   : 2015��3��20��
   ��    ��   : z00161729
   �޸�����   : DTS2015031709266:l��csfb��gu�������κ�������l��rplmn�ɹ���tau�ɹ�����ims cap indʱ��
               cc�ط���ʱ����ʱ��l�ظ�service result indָʾ��������mmc��ȡ��һ��lte����ע�ᱻ������פ����available��ʱ��lte rplmn�ɻָ�������ʧ��
 4.��    ��   : 2015��9��6��
   ��    ��   : z00359541
   �޸�����   : DTS2015081407087: �ӿڵ�����ɾ��bitOpReqType��
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                                              ulCurrState;

    ulCurrState          = NAS_MMC_GetFsmTopState();
   *penAbortType         = NAS_MMC_ABORT_BUTT;

    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* CSFB������ʱ��Lע�����������ͷ�״̬��csps mode1 ��L��vplmn��Lע�����������ͷ�ʱ��Ҫ��ϵ�ǰ״̬�� */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        if (( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState)
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE == ulCurrState))
        {
           *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }

    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND  ==  ulCurrState)
         || (NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState))
        {
            *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
             return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }


    if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState ))
    {
        /* ֱ����״̬���д��� */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}
/* Modified by z00161729 for DCM�����������������, 2012-8-13, end */

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePoweroffPrioWithBgSearch
 ��������  : ���ػ���Ϣ���û���������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePoweroffPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    /* �ػ���Ϣ�����ӳ��˳� */
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerSavePrioWithBgSearch
 ��������  : ��Power Save��Ϣ��BG״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareAcqReqPrioWithBgSearch
 ��������  : ����ȡ��Ϣ��BG״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareRegReqPrioWithBgSearch
 ��������  : ��ע����Ϣ��BG״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareRegReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSysCfgSetPrioWithBgSearch
 ��������  : ��SYSCFG������Ϣ��BG����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��4��27��
   ��    ��   : w00176964
   �޸�����   : GUL BG��������:����LTEģ���л�״̬��
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulNeedPlmnSearch;

    /* �жϵ�ǰSYSCFG�����Ƿ�ᴥ��SYSCFG���� */
    ulNeedPlmnSearch    = NAS_MMC_IsPlmnSelectionNeeded_SysCfg( (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)pstMsg );

    ulCurrState         = NAS_MMC_GetFsmTopState();

    /* �Բ���Ҫ���������������ж� */
    if  ( ( VOS_FALSE == ulNeedPlmnSearch )
       && ( ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND == ulCurrState )
#if (FEATURE_ON == FEATURE_LTE)
         || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND == ulCurrState )
         || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND == ulCurrState )
#endif
         || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND == ulCurrState )))
    {
        /* ֱ����״̬���д��� */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* �����������Ҫ��ϵ�ǰ״̬�� */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserReselPrioWithBgSearch
 ��������  : ��user resel��ѡ��Ϣ��BG����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��9��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareUserReselPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareStkRoamingIndPrioWithBgSearch
 ��������  : ��stk steer of roaming ind��Ϣ���û������ȼ�����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��8��
   ��    ��   : w00167002
   �޸�����   : �յ�STK_NAS_STEERING_OF_ROAMING_IND,��������ϵ�ǰ����
 3.��    ��   : 2012��5��18��
   ��    ��   : w00176964
   �޸�����   : GUL BG��Ŀ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareStkRoamingIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    /* BG����״̬��������ʱ,����Ϣ�Ȼ���,�˳�״̬������ */
    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUsimRefreshPrioWithBgSearch
 ��������  : ��usim refresh ind��Ϣ��BG����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��07��
   ��    ��   : l00130025
   �޸�����   : ����V3R1�� Usim�ӿ�
 3.��    ��   : 2011��11��8��
   ��    ��   : w00167002
   �޸�����   : HPLMN/UPLMN/OPLMN�ļ��������£���������ϵ�ǰ�ĸ����ȼ�������
                 �����ӳٴ�ϣ��������Գ�ʼ����ǰ�ĸ����ȼ������б�
 4.��    ��   : 2012��5��14��
   ��    ��   : z00161729
   �޸�����   : V7R1C50 GUL BG�����޸�,�������UPLMN��OPLMN����Ϊ0����ʼ�������ȼ������б�
                ʱʹ�õ��ǿ���PLMN Sel�ļ����ó���PLMN Sel�ļ��ı�Ҳ����
 5.��    ��   : 2012��5��18��
   ��    ��   : w00176964
   �޸�����   : GUL BG��Ŀ����
 6.��    ��   : 2012��6��11��
   ��    ��   : w00166186
   �޸�����   : AT&T&DCM��Ŀ
 7.��    ��   : 2013��6��4��
   ��    ��   : z00161729
   �޸�����   : SVLTE ��usim�ӿڵ����޸�
 8.��    ��    : 2013��11��26��
   ��    ��    : s00190137
   �޸�����    : �����֧�����õ�OPLMN��չ��256��
 9.��    ��   : 2015��02��06��
   ��    ��   : h00313353
   �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUsimRefreshPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          i;
    USIMM_STKREFRESH_IND_STRU          *pstUsimRefreshInd = VOS_NULL_PTR;

    NAS_MML_SIM_USERPLMN_INFO_STRU      *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU      *pstOperPlmnList = VOS_NULL_PTR;
    VOS_UINT8                            ucIsUoplmnExist;

    pstUsimRefreshInd = (USIMM_STKREFRESH_IND_STRU *)pstMsg;

    if (USIMM_REFRESH_FILE_LIST != pstUsimRefreshInd->enRefreshType)
    {
        /* refresh��Ϣָʾ�����ļ��������ݲ������� */
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* ��ȡUOPLMN */
    pstUserPlmnList   = NAS_MML_GetSimUserPlmnList();
    pstOperPlmnList   = NAS_MML_GetSimOperPlmnList();
    ucIsUoplmnExist   = VOS_TRUE;

    /* UPLMN������Ϊ0����OPLMN������Ϊ0 */
    if ((0 == pstUserPlmnList->ucUserPlmnNum)
     && (0 == pstOperPlmnList->usOperPlmnNum))
    {
        ucIsUoplmnExist = VOS_FALSE;
    }

    for(i = 0; i < pstUsimRefreshInd->usEfNum; i++ )
    {
        if ((USIMM_USIM_EFHPLMNwACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_GSM_EFHPLMNACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_USIM_EFPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_GSM_EFPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_USIM_EFOPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_GSM_EFOPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
		 || (USIMM_USIM_EFEHPLMN_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_ATTGSM_EFACTINGHPLMN_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_ATTUSIM_EFACTINGHPLMN_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || ((USIMM_GSM_EFPLMNSEL_ID == pstUsimRefreshInd->astEfId[i].usFileId)
          && (VOS_FALSE == ucIsUoplmnExist)))
        {
            /* H��U��O�ļ�ˢ��ʱ,BG����״̬�����ݲ�ˢ��,�˳�BG����״̬����ˢ�� */
            *penAbortType   = NAS_MMC_ABORT_BUTT;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
        }
    }

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareMsccUpdateUplmnNtfPrioWithBgSearch
 ��������  : ��ID_MSCC_MMC_UPDATE_UPLMN_NTF��Ϣ��BG����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��31��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMsccUpdateUplmnNtfPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;

}



#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserCsgListPrioWithBgSearch
 ��������  : ���û�CSG List������Ϣ��BG����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserCsgListPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
#endif
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnListPrioWithBgSearch
 ��������  : ���û�List������Ϣ��BG����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}





/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnSpecPrioWithBgSearch
 ��������  : ���û�SpEC������Ϣ��BG����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    /* �ֶ�ģʽʱ������� */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSuspendIndPrioWithBgSearch
 ��������  : BG����״̬����RRMM_SUSPEND_IND��Ϣ�����ȼ��Ƚ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��7��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��5��24��
   ��    ��   : w00176964
   �޸�����   : GUL BG��Ŀ����:��ϵͳ��BG��������Գ�
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareSuspendIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState             = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* BG������������ϵͳָʾ�Գ�,RRC��ظ�BG ABORT,Ϊ��֤����������ϵͳָʾ
       MMC�Ȼ��������Ϣ,�յ�bg abort���˳�״̬��������Ĺ���ָʾ��Ϣ */
    if ((NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF    ==  ulCurrState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_STOP_CNF    ==  ulCurrState)))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* ע��״ֱ̬�ӽ���״̬���д��� */
    if ( ( NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND  ==  ulCurrState )
       || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* �����������ǰ�������һ�� */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserDetachReqPrioWithBgSearch
 ��������  : BG����״̬����ID_MSCC_MMC_DETACH_REQ��Ϣ�����ȼ��Ƚ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��10��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��4��16��
   ��    ��   : y00245242
   �޸�����   : iteration 13����
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareUserDetachReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulTrigerDisableLte;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstCurHighPrioPlmn = VOS_NULL_PTR;

    *penAbortType               = NAS_MMC_ABORT_BUTT;

    /* ��ȡ��ǰ���ڳ��Եĸ����ȼ��������Ϣ */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* ��ȡ��ǰ״̬����״̬ */
    ulCurrState                 = NAS_MMC_GetFsmTopState();

    /* �жϵ�ǰ�û���detach�Ƿ�ᴥ��disable LTE */
    ulTrigerDisableLte          = NAS_MMC_IsTrigerDisableLte_MoDetach((MSCC_MMC_DETACH_REQ_STRU *)pstMsg);


    if (VOS_TRUE == ulTrigerDisableLte)
    {
        /* ��ǰ��LTE�·ǹ���״̬(detach������Ҫȷ����ǰ�Ľ���ģʽ,����״̬����ģʽΪBUTT),��Ҫdisable LTEʱ,ֱ�Ӵ����
           L1�������detach��Ϣ,disable LTE��ͨ��ָ��������GU�� */
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF != ulCurrState))
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }

        /* ��ǰ��GU������״̬��Ҫ���:
          1)GU��BG����L,��ǰ��Ҫdisable LTE
          2)GU�µȴ�����ظ�ʱ,��ǰ��Ҫ�����ĸ����ȼ�����ΪL,��ǰ��Ҫdisable LTE
          ��ʱ��ϵ�L1�´������detach��Ϣ,�յ�GMM��ע���������L1��CS��additionalֵ
          �����Ƿ���Ҫ����ָ������ */
        if (((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF        == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF        == ulCurrState))
         && (NAS_MML_NET_RAT_TYPE_LTE == pstCurHighPrioPlmn->enRat))
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }
#endif

    /* �����������ǰ�������һ�� */
    *penAbortType               = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareLmmSuspendIndPrioWithBgSearch
 ��������  : BG����״̬����ID_LMM_MMC_SUSPEND_IND��Ϣ�����ȼ��Ƚ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��4��27��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareLmmSuspendIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState             = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* BG������������ϵͳָʾ�Գ�,RRC��ظ�BG ABORT,Ϊ��֤����������ϵͳָʾ
       MMC�Ȼ��������Ϣ,�յ�bg abort���˳�״̬��������Ĺ���ָʾ��Ϣ */
    if ((NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF    ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* ע��״ֱ̬�ӽ���״̬���д��� */
    if ( ( NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
       || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* �����������ǰ�������һ�� */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

/* Modified by z00161729 for DCM�����������������, 2012-8-13, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareLmmServiceResultIndPrioWithBgSearch
 ��������  : BG����״̬����ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ�����ȼ��Ƚ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��9��6��
   ��    ��   : z00359541
   �޸�����   : DTS2015081407087: �ӿڵ�����ɾ��bitOpReqType��
 3.��    ��   : 2015��12��7��
   ��    ��   : z00359541
   �޸�����   : DTS2015113009064: CSFB��Ҫ��ϱ�����
   
*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareLmmServiceResultIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                                              ulCurrState;

    ulCurrState          = NAS_MMC_GetFsmTopState();
    *penAbortType        = NAS_MMC_ABORT_BUTT;

    /* CSFB������ʱ��L BG�����ظ�״̬���Lע����״̬��������ͷ�״̬���L����ָ����״̬
       ���vplmn��L�����ظ�״̬��Ҫ��ϵ�ǰ״̬��  */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        if (( NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
         && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_FAST_SEARCH_CNF ==  ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF_RECAMP_VPLMN  ==  ulCurrState)))
        {
           *penAbortType = NAS_MMC_ABORT_FSM_IMMEDIATELY;
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }

    if ((VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND  ==  ulCurrState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState)))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
         return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    if ((NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
     && (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND == ulCurrState))
    {
        /* ֱ����״̬���д��� */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/* Modified by z00161729 for DCM�����������������, 2012-8-13, end */
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerOffPrioWithGetGeo
 ��������  : ��Power Off��Ϣ��GETGEO״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��08��
   ��    ��   : sunjitan 00193151
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithGetGeo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_FindMsgPrioCompareFun
 ��������  : ������Ϣ�ȽϺ���
 �������  : ulEventType:���������Ϣ����
             pstMsg     :���������Ϣ����
             ulFsmEntryEventType    :״̬���������Ϣ
             enFsmId                :״̬����ID
 �������  : ��
 �� �� ֵ  : ��ǰ��������Ϣ�����ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��29��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/

NAS_MMC_MSG_COMPARE_FUNC  NAS_MMC_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    NAS_MMC_FSM_MSG_COMPARE_STRU       *pstFsmCompareTbl = VOS_NULL_PTR;
    VOS_UINT32                          i;

    for ( i = 0 ; i < (sizeof(g_astMmcMsgCompareTbl)/sizeof(NAS_MMC_FSM_MSG_COMPARE_STRU)) ; i++ )
    {
        if ( enFsmId == g_astMmcMsgCompareTbl[i].enFsmId)
        {
            pstFsmCompareTbl = &g_astMmcMsgCompareTbl[i];
            break;
        }
    }

    /* δ���ҵ���״̬���ıȽϺ�����,ֱ�ӷ��ؿ�ָ�� */
    if ( VOS_NULL_PTR == pstFsmCompareTbl )
    {
        return VOS_NULL_PTR;
    }

    for ( i = 0 ; i < pstFsmCompareTbl->ulSize; i++ )
    {
        /* �����Ҫƥ���κ���Ϣ��ֱ�ӽ���ȽϺ��� */
        if ( NAS_MMC_UNIVERAL_MSG_ID == pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType )
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }

        /* ���Ҳ�ͬ�¼��ıȽϺ��� */
        if ( pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType == ulEventType)
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
    }

    /* δ�ҵ�������ֱ�ӷ��ؿ�ָ�� */
    return VOS_NULL_PTR;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetMsgComparePrio
 ��������  : ��ȡ��Ϣ���ȼ��ȽϺ�Ľ��
 �������  : ulEventType:���������Ϣ����
             pstMsg     :���������Ϣ����
 �������  : pulAbortType:����ֵΪ���ʱ,���صĴ������
 �� �� ֵ  : ��ǰ��������Ϣ�����ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��29��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
NAS_MMC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 NAS_MMC_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    NAS_MMC_MSG_COMPARE_FUNC                    pfCompareFunc;
    NAS_MMC_FSM_ID_ENUM_UINT32                  enCurrFsmId;
    NAS_MMC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32   enRslt;

    /*  ��ȡ��ǰ״̬����ID */
    enCurrFsmId         = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enCurrFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }


    /*  ��ȡ�ȽϺ��� NAS_MMC_FindMsgPrioCompareFun() */
    pfCompareFunc       = NAS_MMC_FindMsgPrioCompareFun(ulEventType, pstMsg, enCurrFsmId);

    /* δ�ҵ�������,��Ĭ����Ϣ���� */
    if ( VOS_NULL_PTR == pfCompareFunc )
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* ���ñȽϺ���,�������ȼ��ʹ������ */
    enRslt = pfCompareFunc(ulEventType, pstMsg, penAbortType);

    return enRslt;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareMmcNvimOPlmnRefreshIndPrioWithBgSearch
 ��������  : ������ڱ��������Ƴ���Ϣ����
 �������  : ulEventType:���������Ϣ����
             pstMsg     :���������Ϣ����
 �������  : pulAbortType:����ֵΪ���ʱ,���صĴ������
 �� �� ֵ  : ��ǰ��������Ϣ�����ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : x65241
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcNvimOPlmnRefreshIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCacheMsgIdx;
    VOS_UINT32                          ulExistFlg;
    VOS_UINT32                          ulCacheEventType;

    ulCacheEventType     = NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_NVIM_OPLMN_REFRESH_IND);
    ulExistFlg           = NAS_MMC_IsExistCacheMsg(ulCacheEventType, &ulCacheMsgIdx);

    /* ����Ѿ���ͬ������Ϣ�ˣ��������һ������*/
    if (VOS_TRUE == ulExistFlg)
    {
        NAS_MMC_ClearCacheMsg(ulCacheEventType);
    }

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos
 ��������  : ��available timer��ʱ��Ϣ��BG ��״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��11��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}
/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareRrmPsStatusIndPrioWithPowerOff
 ��������  : power off״̬��ʱ���յ���Դ������Ϣ�Ĵ���
 �������  : ulEventType:���������Ϣ����
             pstMsg     :���������Ϣ����
 �������  : pulAbortType:����ֵΪ���ʱ,���صĴ������
 �� �� ֵ  : ��ǰ��������Ϣ�����ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��9��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareRrmPsStatusIndPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
