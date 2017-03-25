/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcPlmnSelectionStrategy.c
  �� �� ��   : ����
  ��    ��   : sunxibo /46746
  ��������   : 2011��07��04��
  ����޸�   :
  ��������   : NAS ��״̬��PlmnSelection�����������ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��07��04��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 phase II

******************************************************************************/


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "stdlib.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcFsmPlmnSelection.h"
#include "NasMmlLib.h"
#include "NasComm.h"
#include "NasMmcCtx.h"
#include "NasMmcSndOm.h"
#include "NasMmcComFunc.h"
#include "NasMmcProcNvim.h"
#include "NasMmcFsmBgPlmnSearchTbl.h"

#include "MmaAppLocal.h"
#include "TafMmaNetworkNameTbl.h"
#include "NasMmcSndLmm.h"

#include "NasMmcFsmMainTbl.h"
#include "NasUsimmApi.h"

#include "NasMmlCtx.h"
/* Added by c00318887 for ��ֲT3402 , 2015-6-24, begin */
#include "NasMmcFsmBgPlmnSearch.h"
/* Added by c00318887 for ��ֲT3402 , 2015-6-24, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_PLMN_SELECTION_STRATEGY_C

/* ��������������Ӧ�������б��ʼ��������������״̬����ʼ��ʱʹ�� */
NAS_MMC_PLMN_SELECTION_LIST_INIT_TBL_STRU         g_astNasMmcPlmnSearchInitTbl[] =
{
    {NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON,                   NAS_MMC_InitPlmnSelectionList_SwitchOn},
    {NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST,                   NAS_MMC_InitPlmnSelectionList_AreaLost},
    {NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET,                  NAS_MMC_InitPlmnSelectionList_SyscfgSet},
    {NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED,     NAS_MMC_InitPlmnSelectionList_AvailTimerExpire},
    {NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST,                   NAS_MMC_InitPlmnSelectionList_UserList},
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_PLMN_SEARCH,         NAS_MMC_InitPlmnSelectionList_RegRejPlmnSearch},
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_CURRENT_PLMN_SEARCH, NAS_MMC_InitPlmnSelectionList_RegRejCurPlmnSearch},
    {NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,       NAS_MMC_InitPlmnSelectionList_UserSpecPlmnSearch},
    {NAS_MMC_PLMN_SEARCH_SCENE_MANUAL_CHANGE_AUTO_MODE,     NAS_MMC_InitPlmnSelectionList_ManualChangeAutoMode},
    {NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,       NAS_MMC_InitPlmnSelectionList_HighPrioPlmnSearch},
    {NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE,                 NAS_MMC_InitPlmnSelectionList_DisableLte},
    {NAS_MMC_PLMN_SEARCH_SCENE_INTER_SYS_OOS,               NAS_MMC_InitPlmnSelectionList_InterSysOos},
#if (FEATURE_ON == FEATURE_LTE)
    {NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ,       NAS_MMC_InitPlmnSelectionListCsfbServiceRej},
#endif
    {NAS_MMC_PLMN_SEARCH_SCENE_USER_AUTO_RESEL,             NAS_MMC_InitPlmnSelectionList_UserAutoResel},

    {NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH, NAS_MMC_InitPlmnSelectionList_AvailTimerExpireNcellSearch},

    {NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE,                   NAS_MMC_InitPlmnSelectionListRfEnable},

    {NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_RAT_HPLMN_SEARCH,  NAS_MMC_InitPlmnSelectionList_HighPrioRatHplmnSearch},
    /* Added by s00246516 for L-C��������Ŀ, 2014-02-11, Begin */
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL,                   NAS_MMC_InitPlmnSelectionList_RegNCell},
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN,                   NAS_MMC_InitPlmnSelectionList_RegHPlmn},
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN,               NAS_MMC_InitPlmnSelectionList_RegPrefPlmn},
    {NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN,                NAS_MMC_InitPlmnSelectionList_AvailTimerExpire},
    /* Added by s00246516 for L-C��������Ŀ, 2014-02-11, End */


    {NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG,       NAS_MMC_InitPlmnSelectionList_Roaming_AreaLost},

    {NAS_MMC_PLMN_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH,        NAS_MMC_InitPlmnSelectionListRfEnable},

#if (FEATURE_ON == FEATURE_LTE)
    {NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH,      NAS_MMC_InitPlmnSelectionList_EnableLte},
    {NAS_MMC_PLMN_SEARCH_SCENE_CSFB_ABORT,                  NAS_MMC_InitPlmnSelectionList_CsfbAbort},
#endif

#if (FEATURE_ON == FEATURE_LTE)
    {NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH,      NAS_MMC_InitPlmnSelectionList_HighPrioLtePlmnSearch},
#endif

    {NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH,     NAS_MMC_InitPlmnSelectionList_AvailTimerExpire},

    {NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH,    NAS_MMC_InitPlmnSelectionList_AvailTimerExpire},

    {NAS_MMC_PLMN_SEARCH_SCENE_CSFB_END,   NAS_MMC_InitPlmnSelectionList_CsfbEnd},

    {NAS_MMC_PLMN_SEARCH_SCENE_DPLMN_SET,  NAS_MMC_InitPlmnSelectionList_DplmnSet},
};

/* ��Ҫ�Ƚ���history�������������� */
VOS_UINT32 g_aulNasMmcNeedHistorySearchSceneTbl[] =
{
    NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST,
    NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED,
    NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_PLMN_SEARCH,
    NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ,
    NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE,
    NAS_MMC_PLMN_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH,
    NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH,
    NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH,
    NAS_MMC_PLMN_SEARCH_SCENE_CSFB_END,
};


/* ��Ҫ�Ƚ���pref band�������������� */
VOS_UINT32 g_aulNasMmcNeedPrefBandSearchSceneTbl[] =
{
    NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST,
    NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH,
};


/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNeedHistorySearchSceneTblSize
 ��������  : ��ȡ��Ҫ����history���������������б����
 �������  : ��
 �������  : ��
 �� �� ֵ  : g_astNasMmcNeedHistorySearchSceneTbl����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��8��11��
    ��    ��   : z00161729
    �޸�����   : DTS2015061609419��L�±������������Ż�����history����ȫƵ��
*****************************************************************************/
VOS_UINT16 NAS_MMC_GetNeedHistorySearchSceneTblSize(VOS_VOID)
{
    VOS_UINT16                          usTblSize;

    usTblSize = sizeof(g_aulNasMmcNeedHistorySearchSceneTbl) / sizeof(g_aulNasMmcNeedHistorySearchSceneTbl[0]);

    return usTblSize;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNeedHistorySearchSceneTblAddr
 ��������  : ��ȡ��Ҫ����history���������������б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : g_astNasMmcNeedHistorySearchSceneTbl��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��8��11��
    ��    ��   : z00161729
    �޸�����   : DTS2015061609419��L�±������������Ż�����history����ȫƵ��
*****************************************************************************/
VOS_UINT32 *NAS_MMC_GetNeedHistorySearchSceneTblAddr(VOS_VOID)
{
    return g_aulNasMmcNeedHistorySearchSceneTbl;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSpecSearchSceneInNeedHistorySearchSceneTbl
 ��������  : �ж�ָ�����������Ƿ���Ҫ��history��
 �������  : enSearchScene - ��������
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ָ����������������Ҫ��history���������б���
             VOS_FALSE - ָ������������������Ҫ��history���������б���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��8��11��
    ��    ��   : z00161729
    �޸�����   : DTS2015061609419��L�±������������Ż�����history����ȫƵ��
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsSpecSearchSceneInNeedHistorySearchSceneTbl(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enSearchScene
)
{
    VOS_UINT16                          usTblSize;
    VOS_UINT32                          ulIndex;

    usTblSize = NAS_MMC_GetNeedHistorySearchSceneTblSize();

    for (ulIndex = 0; ulIndex < usTblSize; ulIndex++)
    {
        if (enSearchScene == g_aulNasMmcNeedHistorySearchSceneTbl[ulIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetMsccTriggerPlmnSrchTypeInClMode_PlmnSelection
 ��������  : ��ȡCLģʽ�µ���������
 �������  : VOS_VOID
 �������  : NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32---CLģʽ�µ���������
 �� �� ֵ  : VOS_TRUE----��ȡ�ɹ�
             VOS_FALSE---��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��12��29��
    ��    ��   : w00176964
    �޸�����   : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetMsccTriggerPlmnSrchTypeInClMode_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                   *penSrchType
)
{
    NAS_MMC_ENTRY_MSG_STRU                                 *pstEntryMsg           = VOS_NULL_PTR;
    MSCC_MMC_PLMN_SEARCH_REQ_STRU                          *pstMsccPlmnSrchReq    = VOS_NULL_PTR;

    /* ��ȡ״̬���������Ϣ��Ϣ */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    *penSrchType = NAS_MMC_PLMN_SEARCH_TYPE_SPEC;

    if (VOS_FALSE == NAS_MML_IsGULModeConfigured())
    {
        if (pstEntryMsg->ulEventType == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ))
        {
            pstMsccPlmnSrchReq = (MSCC_MMC_PLMN_SEARCH_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

            if (NAS_MSCC_PIF_PLMN_SEARCH_HISTORY == pstMsccPlmnSrchReq->enSrchType)
            {
                *penSrchType = NAS_MMC_PLMN_SEARCH_TYPE_HISTORY;
            }
            else if (NAS_MSCC_PIF_PLMN_SEARCH_PERF_BAND == pstMsccPlmnSrchReq->enSrchType)
            {
                *penSrchType = NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND;
            }
            else
            {
                *penSrchType = NAS_MMC_PLMN_SEARCH_TYPE_SPEC;
            }

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNeedPrefBandSearchSceneTblSize
 ��������  : ��ȡ��Ҫ����pref band���������������б����
 �������  : ��
 �������  : ��
 �� �� ֵ  : g_astNasMmcNeedPrefBandSearchSceneTbl����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��10��13��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16 NAS_MMC_GetNeedPrefBandSearchSceneTblSize(VOS_VOID)
{
    VOS_UINT16                          usTblSize;

    usTblSize = sizeof(g_aulNasMmcNeedPrefBandSearchSceneTbl) / sizeof(g_aulNasMmcNeedPrefBandSearchSceneTbl[0]);

    return usTblSize;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNeedPrefBandSearchSceneTblAddr
 ��������  : ��ȡ��Ҫ����pref band���������������б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : g_astNasMmcNeedPrefBandSearchSceneTbl��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��10��13��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 *NAS_MMC_GetNeedPrefBandSearchSceneTblAddr(VOS_VOID)
{
    return g_aulNasMmcNeedPrefBandSearchSceneTbl;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSpecSearchSceneInNeedPrefBandSearchSceneTbl
 ��������  : �ж�ָ�����������Ƿ���Ҫ��pref band��
 �������  : enSearchScene - ��������
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ָ����������������Ҫ��pref band���������б���
             VOS_FALSE - ָ������������������Ҫ��pref band���������б���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��10��13��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsSpecSearchSceneInNeedPrefBandSearchSceneTbl(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enSearchScene
)
{
    VOS_UINT16                          usTblSize;
    VOS_UINT32                          ulIndex;

    usTblSize = NAS_MMC_GetNeedPrefBandSearchSceneTblSize();

    for (ulIndex = 0; ulIndex < usTblSize; ulIndex++)
    {
        if (enSearchScene == g_aulNasMmcNeedPrefBandSearchSceneTbl[ulIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildRatPrioList_AreaLost
 ��������  : ����֮����������������������ø��½��뼼��˳��
 �������  : NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
 �������  : ��
 �� �� ֵ  : NAS_MML_PLMN_RAT_PRIO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_BuildRatPrioList_AreaLost(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstDestRatRrioList
)
{
    VOS_UINT32                                              i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurRatType;                                                  /* ����Ľ��뼼�� */
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstNonOosCfg  = VOS_NULL_PTR;

    pstNonOosCfg   = NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg();
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    enCurRatType   = NAS_MML_GetCurrNetRatType();

    PS_MEM_CPY(pstDestRatRrioList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* �������PlmnList��Ϣ����ԭ�еĴ���һ�£��ѵ�ǰģ��������� */
    if (VOS_NULL_PTR == pstSearchedPlmnListInfo)
    {
        NAS_MML_SortSpecRatPrioLowest(enCurRatType, pstDestRatRrioList);
        return;
    }

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (pstSearchedPlmnListInfo[i].enRatType != enCurRatType)
        {
            continue;
        }

        /* ���������ϱ�����ʱ�Ѿ����й�spec�ѻ�pref band�ѣ�����NV���ò��ѵ�ǰģ��ѵ�ǰģ��������� */
        if ((VOS_TRUE == pstSearchedPlmnListInfo[i].stSearchedType.ucPrefBandSearchedFlg)
         || (VOS_TRUE == pstSearchedPlmnListInfo[i].stSearchedType.ucSpecSearchedFlg))
        {
            /* NV����������ǰģ��spec�ѻ�pref band��ʱ���ѵ�ǰģ���б���ɾ�� */
            if (NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_NONE == pstNonOosCfg->enSearchTypeAfterHistoryInAreaLostScene)
            {
                NAS_MML_DelSpecRatInPrioRatList(enCurRatType, pstDestRatRrioList);
            }
            /* NV���ò�������ǰģ��spec�ѻ�pref band��ʱ���ѵ�ǰģ��������� */
            else
            {
                NAS_MML_SortSpecRatPrioLowest(enCurRatType, pstDestRatRrioList);
            }

            return;
        }

        /* ��������δ�����κ����������ϱ�������Ҫ�����ѵ�ǰģ��
           ���������ϱ�����ʱֻ���й�history�ѣ���ǰģ�ȷ�����ǰ�棬���б�־��¼��ǰģ�ѽ��й�history��history��ʱ������
        */
        NAS_MML_SortSpecRatPrioHighest(enCurRatType, pstDestRatRrioList);
        break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PlmnSearchListInit
 ��������  : ����״̬������ʱ�������б��ʼ��
 �������  : enPlmnSearchScene    ��������
 �������  : pstPlmnSelectionList �����б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��28��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
 3.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : PCINT����
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;
    pNasMmcPlmnSelectionListInitFunc    pfunPlmnSearchInit;

    pfunPlmnSearchInit = VOS_NULL_PTR;

    /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
    /* ���ݳ�����g_astNasMmcPlmnSearchInitTbl���������б��ʼ������ */
    for (i = 0; i < (sizeof(g_astNasMmcPlmnSearchInitTbl)/sizeof(NAS_MMC_PLMN_SELECTION_LIST_INIT_TBL_STRU)); i++)
    /* Modified by z00234330 for PCLINT����, 2014-06-24, end */
    {
        if (enPlmnSearchScene == g_astNasMmcPlmnSearchInitTbl[i].enPlmnSearchScene)
        {
            pfunPlmnSearchInit = g_astNasMmcPlmnSearchInitTbl[i].pfunPlmnSearchInit;
            break;
        }
    }

    /* ���ҳɹ�ʱ���ó�ʼ���������г�ʼ�� */
    if (VOS_NULL_PTR != pfunPlmnSearchInit)
    {
        PS_MEM_SET(pstPlmnSelectionListInfo, 0x0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

        pfunPlmnSearchInit(pstPlmnSelectionListInfo, pstSearchedPlmnListInfo);
    }

    /* �û��б�����ʱ,��ʼ����Ϻ���Ҫ�����������б���и���,
       ��˴˴��ݲ�Log��Ϣ,��������Ϻ�Log */
    if (NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST != enPlmnSearchScene)
    {
        /* ��ά�ɲ⣬���ѡ���б���Ϣ */
        NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_SwitchOn
 ��������  : ���������б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��28��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������

 3.��    ��   : 2012��5��17��
   ��    ��   : zhoujun 40661
   �޸�����   : ̩��AIS����

 4.��    ��   : 2014��10��8��
   ��    ��   : w00167002
   �޸�����   : DTS2014090401463:�ڻ���ʱ�򣬿����Ὣ8275nv�е�LAST RPLMN RAT����Ϊ
                BUTT�������ڿ���ʱ����������ˣ�����LAST RPLMN RAT����Ч����
                ���ƶ�����4gע��ɹ�������ͨ��(��4G��ע��ɹ�),���ڵ�ǰû��6f7E
                �ļ�����ȡL��RPLMNʧ�ܣ�����ʱ���ȡW��RPLMN.���Կ���ʱ�򣬰���W
                LG˳���������޸ĺ��ڻ����󣬻ᰴ��LWG˳��������
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_SwitchOn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_HPLMN_CFG_INFO_STRU        *pstHPlmnCfg     = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg     = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstGeoPlmn      = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRPlmn;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enNvimLastRplmnRat;             /* NVIM�б�����ϴιػ�ǰRPLMN�Ľ��뼼�� */

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    PS_MEM_SET(&stRPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    /* ��ȡ��ǰ֧�ֵĽ��뼼���������ȼ� */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* ��ȡHPLMN��������Ϣ */
    pstHPlmnCfg    = NAS_MML_GetHplmnCfg();

    /* ��ȡRPLMN��������Ϣ */
    pstRPlmnCfg    = NAS_MML_GetRplmnCfg();

    enNvimLastRplmnRat = pstRPlmnCfg->enLastRplmnRat;
    NAS_MMC_ReadNvimLastRplmnRat(&enNvimLastRplmnRat);

    pstGeoPlmn  = NAS_MMC_GetGeoPlmn();

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* Modified by z40661 for ̩��AIS���� 2012-05-17, begin */
        if ( VOS_TRUE == NAS_MMC_IsAisRoamingEffect())
        {
            /* ��ѡ���б�����������Ҫ��������������*/
            NAS_MMC_AddAisRoamPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }

        /* Modified by z40661 for ̩��AIS���� 2012-05-17, end */

        /* ֧����Ӫ��P4�Ŀ�������Hplmn����֧����������Hplmn */
        if ((VOS_TRUE == NAS_MMC_IsHPlmnPrioSearch())
         || (VOS_TRUE == pstHPlmnCfg->ucHplmnSearchPowerOn))
        {
            /* ��ѡ���б�������HPLMN��EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������UPLMN��OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }

        else if ( (VOS_TRUE                     == pstRPlmnCfg->ucLastRplmnRatFlg)
               && (NAS_MML_NET_RAT_TYPE_BUTT    != enNvimLastRplmnRat) ) /* last Rplmn rat���� */
        {
            /* ��ѡ���б�������RPLMN,��last Rplmn rat������ǰ�� */
            NAS_MML_SortSpecRatPrioHighest(pstRPlmnCfg->enLastRplmnRat, &stPrioRatList);
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������HPLMN��EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������UPLMN��OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������HPLMN��EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������UPLMN��OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
    }
    else
    {
        /* ��ȡ�û�ָ������ */
        pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

        /* last Rplmn rat����,��û�л������ڻ���ʱ��LastRplmnRatΪBUTTֵ */
        if ( (VOS_TRUE                  == pstRPlmnCfg->ucLastRplmnRatFlg)
          && (NAS_MML_NET_RAT_TYPE_BUTT != enNvimLastRplmnRat) )
        {
            /* ��ѡ���б��������û�ָ��PLMN,ֻ����last Rplmn ratָʾ�Ľ��뼼�� */
            stPrioRatList.ucRatNum      = 1;
            stPrioRatList.aucRatPrio[0] = pstRPlmnCfg->enLastRplmnRat;
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }

        /* ��ѡ���б��������û�ָ��PLMN */
        NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        (VOS_VOID)NAS_MMC_GetRPlmn_PlmnSelectionStrategy(pstRPlmnCfg->enLastRplmnRat, &stRPlmn);

        /* �û�ָ��������RPLMN��ͬʱ��Ҫ��EPLMN��ӵ�ѡ���б� */
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stRPlmn,
                                                           &(pstUserSpecPlmn->stPlmnId)))
        {
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);
        }

        /* ֧��R7��������Hplmn */
        if (VOS_TRUE == pstHPlmnCfg->ucManualSearchHplmnFlg)
        {
            /* ��ѡ���б�������HPLMN��EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
    }

    /* �����Ƿ����RPLMN��HPLMN��־ */
    NAS_MMC_UpdateExistRplmnOrHplmnFlag_InitPlmnSelectionList(pstGeoPlmn);

    /* �������� NV�򿪲���MCC��RPLMN/HPLMN��ͬʱ�����������������б��ǰ�� */
    if (VOS_TRUE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON,
                                                                                  pstGeoPlmn))
    {
        /* ��ѡ���б�������� */
        NAS_MMC_SortRoamPlmnSelectionList_InitPlmnSelectionList(pstGeoPlmn, pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_AreaLost
 ��������  : �������������б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��28��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
 3.��    ��   : 2012��11��09��
   ��    ��   : l65478
   �޸�����   : DTS2012103005174, PS�ɹ�,CSʧ���ֶ�ģʽ����ʱ���ܼ�RPLMN
 4.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_AreaLost(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;
    VOS_UINT32                          ulIsRoam;
    VOS_UINT32                          ulIsSortPlmnSearchList;
    VOS_UINT32                          ulIsLTESearched;
#endif

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* ��ȡ��ǰ֧�ֵĽ��뼼���������ȼ� */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

#if (FEATURE_ON == FEATURE_LTE)
    ulIsSortPlmnSearchList      = VOS_FALSE;
    enNetRatType                = NAS_MML_GetCurrNetRatType();
    ulIsRoam                    = NAS_MML_IsLastCampedPlmnIdRoam();
    ulIsLTESearched             = NAS_MML_IsLteSearched_AreaLost(pstSearchedPlmnListInfo);

    if ((VOS_TRUE == NAS_MML_IsNeedSortRatPrioForLteOos2GPrefPlmnSel(&stPrioRatList))
     && (NAS_MML_NET_RAT_TYPE_LTE == enNetRatType)
     && (VOS_FALSE == ulIsRoam))
    {
        ulIsSortPlmnSearchList = VOS_TRUE;
    }
#endif

    /* ����NV���õ��������Ե���������˳�� */
    NAS_MMC_BuildRatPrioList_AreaLost(pstSearchedPlmnListInfo, &stPrioRatList);

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ֧����������Hplmn */
        if (VOS_TRUE == NAS_MMC_IsHPlmnPrioSearch())
        {
            /* ��ѡ���б�������HPLMN��EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* ���뼼��˳��ĵ�������ǰ�� */

            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);


        }
        else
        {
            /* ���뼼��˳��ĵ�������ǰ�� */

            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������HPLMN��EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        if(VOS_TRUE == ulIsSortPlmnSearchList)
        {
            NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                    pstPlmnSelectionListInfo);
            if (VOS_TRUE == ulIsLTESearched)
            {
                NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE,
                                                        pstPlmnSelectionListInfo);
            }
        }
        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {

            /* ���뼼��˳��ĵ�������ǰ�� */

            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ȡ�û�ָ������ */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* ���뼼��˳��ĵ�������ǰ�� */

            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }
        if(VOS_TRUE == ulIsSortPlmnSearchList)
        {
            NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                    pstPlmnSelectionListInfo);
            if (VOS_TRUE == ulIsLTESearched)
			{
                NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE,
                                                        pstPlmnSelectionListInfo);
            }
        }
    }

    /* ������������ʱ�������ǰ����CSFBҵ���־��ѡ���б������֮����Ҫ��LTE�����������ȼ�����GSM��WCDMA֮�� */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_Roaming_AreaLost
 ��������  : OOS���������������б��ʼ��
 �������  : pstPlmnListSearched, ������ϱ����б�
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��02��18��
   ��    ��   : t00173447
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_Roaming_AreaLost(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;

    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* ��ȡ��ǰ֧�ֵĽ��뼼���������ȼ� */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /*���ѵ�ǰ���뼼��*/
        PS_MEM_SET(&stPrioRatList, 0x0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
        stPrioRatList.ucRatNum = 1;
        stPrioRatList.aucRatPrio[0] = NAS_MML_GetCurrNetRatType();
        /* ��ѡ���б�������RPLMN,���ѵ�ǰ���뼼�� */
        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* ��ѡ���б�������EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������HPLMN��EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* ��ѡ���б�������RPLMN,��ǰ���뼼��������� */
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ȡ�û�ָ������ */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* ��ѡ���б��������û�ָ��PLMN,��ǰ���뼼��������� */
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }

    }
    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_OosAreaLost
 ��������  : OOS���������������б��ʼ��
 �������  : pstPlmnListSearched, ������ϱ����б�
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��11��26��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
 3.��    ��   : 2012��11��09��
   ��    ��   : l65478
   �޸�����   : DTS2012103005174, PS�ɹ�,CSʧ���ֶ�ģʽ����ʱ���ܼ�RPLMN
 4.��    ��   : 2015��8��25��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve �޸�
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_InterSysOos(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* ��ȡ��ǰ֧�ֵĽ��뼼���������ȼ� */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* ��OOS���̽����������ϱ���PLMN���������б� */
    NAS_MMC_AddSearchedPlmnListInfoInPlmnSelectionList(pstPlmnSelectionListInfo, pstSearchedPlmnListInfo);

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ��ѡ���б�������RPLMN,��ǰ���뼼��������� */
        NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* ��ѡ���б�������EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������HPLMN��EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* ��ѡ���б�������RPLMN,��ǰ���뼼��������� */
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ȡ�û�ָ������ */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* ��ѡ���б��������û�ָ��PLMN,��ǰ���뼼��������� */
            NAS_MML_SortSpecRatPrioLowest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }

    }


    /* �����ǰ����CSFBҵ���־��ѡ���б������֮����Ҫ��LTE�����������ȼ�����GSM��WCDMA֮�� */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    /* ��ά�ɲ⣬���ѡ���б���Ϣ */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_UserAutoResel
 ��������  : �û���ѡʱ,�����б��ʼ������Ts23.122 ch4.4.3.2.1����ǰPlmn�������λ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2012��5��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton����֧��

  2.��    ��   : 2014��9��3��
    ��    ��   : w00167002
    �޸�����   : DTS2014090204636:��HOME PLMN��פ��ʱ��������ѡ���ѵ�ǰ��HOMPE PLMN
                ��ɾ���ˡ��ڵ�ģʱ�������HPLMN,����ܴ�����FFFFF���磬��������ʱ�䡣
 *****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_UserAutoResel(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    /* ��ѡ���б�������HPLMN��EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    /* ��ѡ���б�������UPLMN��OPLMN */
    NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);


    /* פ���ڷ�EHPLMNʱ���򽫵�ǰ����������� */
    if (VOS_TRUE == NAS_MMC_IsRoam())
    {
        /* ɾ����ǰפ�������� */
        NAS_MMC_DelSpecPlmnWithRatInPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                             NAS_MML_GetCurrNetRatType(),
                                             pstPlmnSelectionListInfo);
    }

    /* ��ά�ɲ⣬���ѡ���б���Ϣ */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPrioRat_SyscfgSet
 ��������  : Syscfg���ô�������ʱ�����б��ʼ��ʱ����ȡ��ǰ������ȼ��Ľ��뼼��
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8 ������ȼ��Ľ��뼼��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��11��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��7��17��
   ��    ��   : w00242748
   �޸�����   : DTS2014063003419:SYSCFG���������ȼ����뼼����������NV����

*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetPrioRat_SyscfgSet(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg     = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;

    enRatType        = NAS_MML_NET_RAT_TYPE_BUTT;
    pstRPlmnCfg      = NAS_MML_GetRplmnCfg();
    enCurrNetRatType = NAS_MML_GetCurrNetRatType();
    pstPrioRatList   = NAS_MML_GetMsPrioRatList();

    /* SVLTE���Կ��Ļ�����ǰפ���Ľ��뼼������ */
    if ( (VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
      && (NAS_MML_NET_RAT_TYPE_BUTT != enCurrNetRatType))
    {
        enRatType = enCurrNetRatType;
    }
    else
    {
        /* SVLTE���Թرգ���ԭ���߼����� */
        if ( VOS_TRUE == NAS_MML_GetSyscfgTriHighRatSrchFlg() )
        {
            enRatType = pstPrioRatList->aucRatPrio[0];
        }
        else if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
        {
            enRatType = pstRPlmnCfg->enLastRplmnRat;
        }
        else
        {
            ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

            if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
             && (VOS_TRUE == ulEplmnValidFlg))
            {
                enRatType = pstRPlmnCfg->enLastRplmnRat;
            }
            else
            {
                pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();
                enRatType       = pstUserSpecPlmn->enRat;
            }
        }
    }

    return enRatType;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_SyscfgSet
 ��������  : Syscfg���ô�������ʱ�����б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��28��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
 3.��    ��   : 2012��11��09��
   ��    ��   : l65478
   �޸�����   : DTS2012103005174, PS�ɹ�,CSʧ���ֶ�ģʽ����ʱ���ܼ�RPLMN
 4.��    ��   : 2015��8��25��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve �޸�
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_SyscfgSet(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr      = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstGeoPlmn      = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstGeoPlmn  = NAS_MMC_GetGeoPlmn();

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));


    enRatType = NAS_MMC_GetPrioRat_SyscfgSet();

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ��ѡ���б�������RPLMN,��last Rplmn rat������ǰ�� */
        NAS_MML_SortSpecRatPrioHighest(enRatType, &stPrioRatList);
        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* ��ѡ���б�������EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������HPLMN��EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* ��ѡ���б�������RPLMN,��last Rplmn rat������ǰ�� */
            NAS_MML_SortSpecRatPrioHighest(enRatType, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ȡ�û�ָ������ */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* ��ѡ���б��������û�ָ��PLMN,���û�ָ����rat������ǰ�� */
            NAS_MML_SortSpecRatPrioHighest(enRatType, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }
    }


    /* �����Ƿ����RPLMN��HPLMN��־ */
    NAS_MMC_UpdateExistRplmnOrHplmnFlag_InitPlmnSelectionList(pstGeoPlmn);

    /* �������� NV�򿪲���MCC��RPLMN/HPLMN��ͬʱ�����������������б��ǰ�� */
    if (VOS_TRUE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET,
                                                                                  pstGeoPlmn))
    {
        /* ��ѡ���б�������� */
        NAS_MMC_SortRoamPlmnSelectionList_InitPlmnSelectionList(pstGeoPlmn, pstPlmnSelectionListInfo);
    }


    /* �����ǰ����CSFBҵ���־��ѡ���б������֮����Ҫ��LTE�����������ȼ�����GSM��WCDMA֮�� */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildNcellPlmnSelectionPlmnList
 ��������  : ����NCELL ѡ���б�
 �������  : enPlmnType:��������
             ucChangePrioRatOrder :�Ƿ���PrioRat ˳��

 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��5��27��
   ��    ��   :  x00203213
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_BuildNcellPlmnSelectionPlmnList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    VOS_UINT8                                               ucChangePrioRatOrder,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT8                                               ucRatNum;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList = VOS_NULL_PTR;
    VOS_UINT32                                              ulRatCnt;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRatType;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;

    PS_MEM_CPY(&(stPlmnInfo.stPlmnId), pstPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
    stPlmnInfo.enPlmnType = enPlmnType;

    /* ��ȡ���ȼ��б� */
    pstRatPrioList     = NAS_MML_GetMsPrioRatList();

    for (ulRatCnt =0; ulRatCnt< pstRatPrioList->ucRatNum; ulRatCnt++)
    {
        ucRatNum                = 0x0;
        /* ��ʼ���ϱ��Ľ��뼼���б� */
        if (VOS_FALSE == ucChangePrioRatOrder)
        {
            enRatType        = pstRatPrioList->aucRatPrio[ulRatCnt];
        }

        /*���򹹽������б�*/
        else
        {
            enRatType        = pstRatPrioList->aucRatPrio[pstRatPrioList->ucRatNum -1 - ulRatCnt];
        }


        if (NAS_MML_NET_RAT_TYPE_LTE == enRatType)
        {
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_LTE;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
            ucRatNum++;
        }

        if (NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
        {
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_WCDMA;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
            ucRatNum++;
        }
        stPlmnInfo.ucRatNum = ucRatNum;

        /* ����ʣ��λ�ø�ֵΪ��Чֵ */
        for (; ucRatNum < NAS_MML_MAX_RAT_NUM; ucRatNum++)
        {
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_BUTT;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_BUTT;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_BUTT;
            stPlmnInfo.astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        }

        /* ��ӵ������б� */
        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);

    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_AvailTimerExpireNcellSearch
 ��������  : Available Timer��ʱ����NCELL ����ʱ�����б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��28��
    ��    ��   : x00203213
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_AvailTimerExpireNcellSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU        *pstEHPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          *pstUserSpecPlmn   = VOS_NULL_PTR;
    VOS_UINT8                            ucNeedChangeRatOrder;

    /* �ж��Ƿ���Ҫ����˳��*/
    ucNeedChangeRatOrder = NAS_MMC_IsNeedChangeNcellSearchRatOrder();

    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();
    pstEHPlmnInfo   = NAS_MML_GetSimEhplmnList();


    /* �Զ�����ģʽ ��� HPLMN ���б���*/
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_MMC_BuildNcellPlmnSelectionPlmnList(NAS_MMC_PLMN_TYPE_HPLMN,
                                       ucNeedChangeRatOrder,
                                       &(pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId),
                                       pstPlmnSelectionListInfo);

    }

    else
    {
        NAS_MMC_BuildNcellPlmnSelectionPlmnList(NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                       ucNeedChangeRatOrder,
                                       &(pstUserSpecPlmn->stPlmnId),
                                       pstPlmnSelectionListInfo);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_AvailTimerExpire
 ��������  : Available Timer��ʱ��������ʱ�����б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��28��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��31��
    ��    ��   : w00166186
    �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
  3.��    ��   : 2012��11��09��
    ��    ��   : l65478
    �޸�����   : DTS2012103005174, PS�ɹ�,CSʧ���ֶ�ģʽ����ʱ���ܼ�RPLMN
  4.��    ��   : 2015��8��25��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve �޸�
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_AvailTimerExpire(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ֧����������Hplmn */
        if (VOS_TRUE == NAS_MMC_IsHPlmnPrioSearch())
        {
            /* ��ѡ���б�������HPLMN��EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(pstPrioRatList, pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������UPLMN��OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(pstPrioRatList, pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������HPLMN��EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������UPLMN��OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
    }
    else
    {
        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       pstPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }

    }

    /* �����ǰ����CSFBҵ���־��ѡ���б������֮����Ҫ��LTE�����������ȼ�����GSM��WCDMA֮�� */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_UserList
 ��������  : �û��б����������󴥷�����ʱ�����б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��28��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��20��
   ��    ��   : w00167002
   �޸�����   : �û��б��Ѱ�����һ��RPlmn����˳���������
 3.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
 4.��    ��   : 2012��6��4��
   ��    ��   : z00161729
   �޸�����   : V7R1C50 GUL BG�����޸�
 5.��    ��   : 2012��11��09��
   ��    ��   : l65478
   �޸�����   : DTS2012103005174, PS�ɹ�,CSʧ���ֶ�ģʽ����ʱ���ܼ�RPLMN
 6.��    ��   : 2014��2��20��
   ��    ��   : z00161729
   �޸�����   : DTS2014022100125:����פ��g�����磬��˫����tl����������פ��g�����磬
               available��ʱ��list�������������б��last rplmn rat������ǰ��
               ����g���ڵ�һ���޷���l��tds������
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_UserList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg     = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;

    VOS_UINT8                           ucPsAttachAllowFlg;
    VOS_UINT8                           ucCsAttachAllowFlg;

    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstRPlmnCfg    = NAS_MML_GetRplmnCfg();

    /* ��ѡ���б�������RPLMN,��last Rplmn rat������ǰ�� */
    NAS_MML_SortSpecRatPrioHighest(pstRPlmnCfg->enLastRplmnRat, &stPrioRatList);

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ֧����������Hplmn */
        if (VOS_TRUE == NAS_MMC_IsHPlmnPrioSearch())
        {
            /* ��ѡ���б�������HPLMN��EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(pstPrioRatList, pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������UPLMN��OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {

            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������HPLMN��EHPLMN */
            NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

            /* ��ѡ���б�������UPLMN��OPLMN */
            NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
    }
    else
    {
        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {

            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }

    }

    /* �������б��������svlte ˫��ģʽ��g�Ľ��뼼���ŵ��б����,��������Ҳ���t��l��������� */
    ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();
    ucCsAttachAllowFlg = NAS_MML_GetCsAttachAllowFlg();

    if ((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
     && (VOS_FALSE == ucPsAttachAllowFlg)
     && (VOS_FALSE == ucCsAttachAllowFlg))
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_GSM,
                                                pstPlmnSelectionListInfo);
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_RegRejPlmnSearch
 ��������  : ע�ᱻ�ܴ�������ʱ�����б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��28��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : W00166186
   �޸�����   : DTS2011082902017,ON PLMNע�ᱻ�ܣ�����״̬���ظ�����
 3.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_RegRejPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU            stPrioRatList;
    VOS_UINT8                             ucKeepSrchHplmnFlg;
    NAS_MML_PLMN_RAT_PRIO_STRU           *pstPrioRatList = VOS_NULL_PTR;

    ucKeepSrchHplmnFlg = NAS_MMC_IsNeedSrchCurrCampHpmnRejByCause13();

    NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_InitPlmnSelectionList_RegRejPlmnSearch: ucKeepSrchHplmnFlg =", ucKeepSrchHplmnFlg);

    if (VOS_TRUE == ucKeepSrchHplmnFlg)
    {
        PS_MEM_SET(&stPrioRatList, 0x00, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
        stPrioRatList.ucRatNum = 1;
        stPrioRatList.aucRatPrio[0] = NAS_MML_GetCurrNetRatType();

        NAS_MMC_AddSpecPlmnInPlmnSelectionList(NAS_MML_GetCurrCampPlmnId(),
                                            NAS_MMC_PLMN_TYPE_HPLMN,
                                            &stPrioRatList,
                                            pstPlmnSelectionListInfo);
    }

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
        
        /* ��ȡ��ǰ֧�ֵĽ��뼼���������ȼ� */
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

        /* ��ѡ���б�������RPLMN */
        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);
        
        /* ��ѡ���б�������EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������HPLMN��EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        if (VOS_FALSE == ucKeepSrchHplmnFlg)
        {
            /* ɾ����ǰע�ᱻ�ܵ����� */
            NAS_MMC_DelSpecPlmnWithRatInPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                                 NAS_MML_GetCurrNetRatType(),
                                                 pstPlmnSelectionListInfo);
        }
    }
    else
    {
        /* ��ѡ���б��������û�ָ������ */
        NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    /* �����ǰ����CSFBҵ���־��ѡ���б������֮����Ҫ��LTE�����������ȼ�����GSM��WCDMA֮�� */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_InitPlmnSelectionList_RegRejPlmnSearch: CSFB exists, Move L RAT to the end of PLMN Selection List");
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_DisableLte
 ��������  : Disable LTE��������ʱ�����б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��11��1��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��1��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003930, Disable Lteʱ��Ҫ��RPLMN
  3.��    ��   : 2012��11��09��
    ��    ��   : l65478
    �޸�����   : DTS2012103005174, PS�ɹ�,CSʧ���ֶ�ģʽ����ʱ���ܼ�RPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_DisableLte(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU                              *pEplmnAddr  = VOS_NULL_PTR;

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {

        /* ��ѡ���б������� RPLMN */
        NAS_MMC_AddRPlmnInPlmnSelectionList(pstPrioRatList, pstPlmnSelectionListInfo);

        /* ��ѡ���б������� EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);


        /* ��ѡ���б�������HPLMN��EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {

        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* ��ѡ���б������� RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       pstPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* ��ѡ���б������� EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);
        }


        /* ��ѡ���б��������û�ָ������ */
        NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_RegRejCurPlmnSearch
 ��������  : ע�ᱻ�ܴ����ѵ�ǰ����ʱ�����б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��28��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:���ıȽϵ��Ⱥ�˳����Ϊ��ǰפ������������
                ΪBCCH�ġ�
 3.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
 4.��    ��   : 2012��11��09��
   ��    ��   : l65478
   �޸�����   : DTS2012103005174, PS�ɹ�,CSʧ���ֶ�ģʽ����ʱ���ܼ�RPLMN
 5.��    ��   : 2015��8��25��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve �޸�
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_RegRejCurPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enPlmnType;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnList = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstPlmnId      = NAS_MML_GetCurrCampPlmnId();
    pstEquPlmnList = NAS_MML_GetEquPlmnList();

    /* ��ӵ�Plmn������Ĭ��ΪAvailPlmn */
    enPlmnType = NAS_MMC_PLMN_TYPE_AVAIL_PLMN;


    /* Rplmn�� EplmnList[0]��ͬʱ�����ΪRplmn���� */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &(pstEquPlmnList->astEquPlmnAddr[0]) ))
    {
        enPlmnType = NAS_MMC_PLMN_TYPE_RPLMN;
    }


    /* ��ѡ���б������ӵ�ǰ����,��ǰ���뼼��������ǰ�� */
    NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);

    NAS_MMC_AddSpecPlmnInPlmnSelectionList(pstPlmnId,
                                           enPlmnType,
                                           &stPrioRatList,
                                           pstPlmnSelectionListInfo);

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ��ѡ���б�������EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������HPLMN��EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);
        }

        /* ��ѡ���б��������û�ָ������ */
        NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    /* �����ǰ����CSFBҵ���־��ѡ���б������֮����Ҫ��LTE�����������ȼ�����GSM��WCDMA֮�� */
    if (VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE, pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_UserSpecPlmnSearch
 ��������  : �û�ָ������ʱ�б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��28��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_UserSpecPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRPlmn;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg     = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    PS_MEM_SET(&stRPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

    /* ��ȡRPLMN��������Ϣ */
    pstRPlmnCfg    = NAS_MML_GetRplmnCfg();

    /* ��ѡ���б��������û�ָ������,�û�ָ�����뼼��������ǰ�� */
    NAS_MML_SortSpecRatPrioHighest(pstUserSpecPlmn->enRat, &stPrioRatList);
    NAS_MMC_AddSpecPlmnInPlmnSelectionList(&pstUserSpecPlmn->stPlmnId,
                                           NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                           &stPrioRatList,
                                           pstPlmnSelectionListInfo);

    (VOS_VOID)NAS_MMC_GetRPlmn_PlmnSelectionStrategy(pstRPlmnCfg->enLastRplmnRat, &stRPlmn);

    /* �û�ָ��������RPLMN��ͬʱ��Ҫ��EPLMN��ӵ�ѡ���б� */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stRPlmn,
                                                       &(pstUserSpecPlmn->stPlmnId)))
    {
        NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_ManualChangeAutoMode
 ��������  : �ֶ�����ģʽ�޸�Ϊ�Զ�ģʽ��������ʱ�����б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��28��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_ManualChangeAutoMode(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserReselPlmn = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* �Զ��޸�Ϊ�ֶ�ʱ�ṩ������������� */
    pstUserReselPlmn = NAS_MMC_GetUserReselPlmnId();

    /* �Զ��޸�Ϊ�ֶ�ʱ������ṩ������������Ľ��뼼��������ǰ�� */
    NAS_MML_SortSpecRatPrioHighest(pstUserReselPlmn->enRat, &stPrioRatList);
    NAS_MMC_AddSpecPlmnInPlmnSelectionList(&pstUserReselPlmn->stPlmnId,
                                           NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                           &stPrioRatList,
                                           pstPlmnSelectionListInfo);

    /* ��ѡ���б�������EPLMN */
    NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

    /* ��ѡ���б�������HPLMN��EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    /* ��ѡ���б�������UPLMN��OPLMN */
    NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_CSFB_SERVICE_REJ
 ��������  : CSFB����������б��ʼ��
 �������  : pstPlmnListSearched, ������ϱ����б�
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��2��15��
   ��    ��   : h00202780
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��09��
   ��    ��   : l65478
   �޸�����   : DTS2012103005174, PS�ɹ�,CSʧ���ֶ�ģʽ����ʱ���ܼ�RPLMN
 3.��    ��   : 2014��4��8��
   ��    ��   : z00161729
   �޸�����   : DTS2014040809442:csfbʧ��lmm �ظ�service result indָʾ��Ҫ����������tds���������ƣ����utranmodeΪtdd��
                ���������б�ʱ��Ҫ��tds����ŵ�g�ĺ��棬���Ӻ��гɹ���
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionListCsfbServiceRej(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* ��ȡ��ǰ֧�ֵĽ��뼼���������ȼ� */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ��ѡ���б�������RPLMN */
        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* ��ѡ���б�������EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������HPLMN��EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* ��ѡ���б�������RPLMN  */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ȡ�û�ָ������ */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }

    }

    if (VOS_TRUE == NAS_MMC_IsNetRatSupportedTdscdma())
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                pstPlmnSelectionListInfo);
    }

    /* �������б�������򣬽�L���뼼���ŵ��б����*/
    NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE,
                                                pstPlmnSelectionListInfo);
    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_EnableLte
 ��������  : enable lte�����б��ʼ��
 �������  : pstPlmnSelectionListInfo, ������ϱ����б�
 �������  : pstSearchedPlmnListInfo,�б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_EnableLte(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* ��ȡ��ǰ֧�ֵĽ��뼼���������ȼ� */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ��ѡ���б�������RPLMN,LTE���뼼��������ǰ */
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);

        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* ��ѡ���б�������EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������HPLMN��EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    }
    else
    {
        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* ��ѡ���б�������RPLMN,LTE���뼼��������ǰ */
            NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ȡ�û�ָ������ */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* ��ѡ���б��������û�ָ��PLMN,LTE���뼼��������ǰ */
            NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }
    }
    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_CsfbAbort
 ��������  : enable lte�����б��ʼ��
 �������  : pstPlmnSelectionListInfo, ������ϱ����б�
 �������  : pstSearchedPlmnListInfo,�б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��5��7��
    ��    ��   : b00269685
    �޸�����   : csfb���������йҵ绰����������
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_CsfbAbort(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* ��ȡ��ǰ֧�ֵĽ��뼼���������ȼ� */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ��ѡ���б�������RPLMN,LTE���뼼��������ǰ */
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);

        NAS_MMC_AddRPlmnInPlmnSelectionList(&stPrioRatList, pstPlmnSelectionListInfo);

        /* ��ѡ���б�������EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������HPLMN��EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    }
    else
    {
        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* ��ѡ���б�������RPLMN,LTE���뼼��������ǰ */
            NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       &stPrioRatList,
                                       pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ȡ�û�ָ������ */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* ��ѡ���б��������û�ָ��PLMN,LTE���뼼��������ǰ */
            NAS_MML_SortSpecRatPrioHighest(NAS_MML_NET_RAT_TYPE_LTE, &stPrioRatList);
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_CsfbEnd
 ��������  : CSFB�������յ�Area lost�����������̺��յ��Ҷ�ҵ��֪ͨ������������
 �������  : pstPlmnSelectionListInfo, ������ϱ����б�
 �������  : pstSearchedPlmnListInfo,�б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : �½�
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_CsfbEnd(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    VOS_UINT32                          ulEplmnValidFlg;
    NAS_MML_EQUPLMN_INFO_STRU          *pEplmnAddr  = VOS_NULL_PTR;

    pEplmnAddr = NAS_MML_GetEquPlmnList();

    /* �Զ�����ģʽ */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_MMC_AddRPlmnInPlmnSelectionList(NAS_MML_GetMsPrioRatList(), pstPlmnSelectionListInfo);

        /* ��ѡ���б�������EPLMN */
        NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������HPLMN��EHPLMN */
        NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    }
    else
    {
        /* �û�ָ������ע��ɹ���,��������RPLMN��EPLMN */
        ulEplmnValidFlg = NAS_MML_GetEplmnValidFlg();

        if ((VOS_TRUE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
         && (VOS_TRUE == ulEplmnValidFlg))
        {
            /* ��ѡ���б�������RPLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pEplmnAddr->astEquPlmnAddr[0]),
                                       NAS_MMC_PLMN_TYPE_RPLMN,
                                       NAS_MML_GetMsPrioRatList(),
                                       pstPlmnSelectionListInfo);

            /* ��ѡ���б�������EPLMN */
            NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(pstPlmnSelectionListInfo);

            /* ��ѡ���б��������û�ָ������ */
            NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ��ȡ�û�ָ������ */
            pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

            /* ��ѡ���б��������û�ָ��PLMN */
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstUserSpecPlmn->stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                   NAS_MML_GetMsPrioRatList(),
                                                   pstPlmnSelectionListInfo);
        }
    }

    return;
}

#endif



/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionListRfEnable
 ��������  : ֪ͨRF����ʱ�򣬽���ѡ���б���
 �������  : pstPlmnListSearched, ������ϱ����б�
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��22��
   ��    ��   : w00167002
   �޸�����   : SVLTE��������Ŀ��
            ����������ʧ��NO RF������MMC��Ҫ�޸��������ֳ�����������
            ��1�� MMC���յ�RRM���͵�ID_RRM_PS_STATUS_IND��Ϣʱ�������ǰ����NO RF�����Ϣ�����败��ѡ����
            ��2�� MMC���յ�Available��ʱ����ʱ��Ϣʱ�������ǰ����NO RF�����Ϣ�����败��ѡ����

            MMC��ѡ���б������Ϊ:
            ����1�� NO RF����ʧ��ʱ��ѡ���б���Ч����������յ�ʱ��ѡ���б�������������򰴹���2����ѡ���б��졣
            ����2��������������ʱ����ʱ��������ѡ���б������յ�NO RFʧ��ʱ�Ľ��뼼����Ϊ��һ��PLMN�������ȼ����뼼����
                   ����W������ʧ�ܣ�����ѡ���б��е�һλ��������W��������뼼����
 2.��    ��   : 2013��4��4��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:����NO RF ��ر�������
 3.��    ��   : 2013��6��30��
   ��    ��   : w00176964
   �޸�����   : DSDS GUNAS III��Ŀ:NO RF������,���³�ʼ�������ȼ������б�
 4.��    ��   : 2015��5��21��
   ��    ��   : l00305157
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionListRfEnable(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stDestFirstPlmnRatInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNoRfPlmnRat;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT8                                               ucExistNoRFRat;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList      = VOS_NULL_PTR;
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstRatSearcchInfo   = VOS_NULL_PTR;

    pstRatSearcchInfo   = NAS_MMC_GetSearchRatInfo_PlmnSelection();

    /* ������ʼ�� */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    enNoRfPlmnRat  = NAS_MML_GetNoRfRatType();

    ucExistNoRFRat = VOS_FALSE;
    PS_MEM_SET(&stDestFirstPlmnRatInfo, 0X00, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

    /* �����ǰMMC�б�����ѡ���б���ָ����뱸�ݵ�ѡ���б� */
    if ( NAS_MMC_BACKUP_PLMN_SELECTION_LIST == NAS_MMC_GetPlmnSelectionListType() )
    {
        PS_MEM_CPY(pstPlmnSelectionListInfo, NAS_MMC_GetHighPrioPlmnList(), sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

        /* �ָ�NO RF ��Դ���ú�,���������Դ�Ļָ� */
        NAS_MMC_RestoreNoRfHistorySearchedRatInfo_PlmnSelection(pstRatSearcchInfo);

        /* NO RF������,�����ǰ�Ǳ���ѡ���б���Ϣ�������³�ʼ��Ϊ�����ȼ��б���Ϣ */
        if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
        {
            NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                          VOS_NULL_PTR,
                                          NAS_MMC_GetHighPrioPlmnList());
        }

        return;
    }

    /* ����������������ʱ����ʱ���������б�����NO RFʱ��Ľ��뼼������Ϊ��һ���ȼ� */
    NAS_MMC_InitPlmnSelectionList_AvailTimerExpire(pstPlmnSelectionListInfo, pstSearchedPlmnListInfo);

    /* �쳣�����������ǰĿ����뼼��ΪBUTT,�򲻽��е��� */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == enNoRfPlmnRat )
    {
        return;
    }

    /* �쳣�����������ǰ���������ˣ��򲻽��й��� */
    if ( NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST == pstPlmnSelectionListInfo->usSearchPlmnNum )
    {
        return;
    }

    /* ��ǰ�Ľ��뼼������Ϊ1��������Ҫ���������б� */
    if ( 1 == pstPrioRatList->ucRatNum)
    {
        return;
    }

    /* ������ѡ���б��в���Ŀ����뼼����������Ϣ */
    for ( i = 0 ; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++ )
    {
        for (j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; j++)
        {
            /* �ҵ�Ŀ������뼼����������ڵ�һλ���ܸ�������Ҫ���� */
            if ( enNoRfPlmnRat == pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType )
            {
                PS_MEM_CPY(&stDestFirstPlmnRatInfo,
                           &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                           sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

                /* ��Ŀ������Ľ��뼼������Ϊ����һ�� */
                stDestFirstPlmnRatInfo.ucRatNum = 1;
                PS_MEM_CPY(&(stDestFirstPlmnRatInfo.astPlmnRatInfo[0]),
                           &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j]),
                           sizeof(NAS_MMC_PLMN_RAT_INFO_STRU) );

                ucExistNoRFRat = VOS_TRUE;

                break;
            }
        }

        /* �ҵ���Ŀ����뼼������ֱ������ */
        if ( VOS_TRUE == ucExistNoRFRat )
        {
            break;
        }
    }

    /* û�ҵ�Ŀ����뼼��������һ����Ӧ�Ľ��뼼�� */
    if ( VOS_FALSE == ucExistNoRFRat )
    {
        /* ����Ҳ�����Ӧ�Ľ��뼼��������Ϣ������������һ��Ŀ����뼼������ */
        PS_MEM_CPY(&stDestFirstPlmnRatInfo,
                   &(pstPlmnSelectionListInfo->astPlmnSelectionList[0]),
                   sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

        stDestFirstPlmnRatInfo.ucRatNum = 1;
        stDestFirstPlmnRatInfo.astPlmnRatInfo[0].enRatType      = enNoRfPlmnRat;
        stDestFirstPlmnRatInfo.astPlmnRatInfo[0].enNetStatus    = NAS_MMC_NET_STATUS_BUTT;
        stDestFirstPlmnRatInfo.astPlmnRatInfo[0].enQuality      = NAS_MMC_NET_QUALITY_BUTT;
        stDestFirstPlmnRatInfo.astPlmnRatInfo[0].ucReserve      = 0;
        stDestFirstPlmnRatInfo.astPlmnRatInfo[0].lRscp          = NAS_MML_UTRA_RSCP_UNVALID;
    }

    /* ����ǰѡ���б����һλ�󣬽�Ŀ����뼼���������ѡ���б� */
    (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[1]),
                &(pstPlmnSelectionListInfo->astPlmnSelectionList[0]),
                (pstPlmnSelectionListInfo->usSearchPlmnNum) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));


    PS_MEM_CPY(&(pstPlmnSelectionListInfo->astPlmnSelectionList[0]),
               &stDestFirstPlmnRatInfo,
               sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

    pstPlmnSelectionListInfo->usSearchPlmnNum++;

    return;
}


/* Added by s00246516 for L-C��������Ŀ, 2014-02-11, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_RegNCell
 ��������  : ����NCellע��ʱ�����б��ʼ��
 �������  : pstSearchedPlmnListInfo,����������������Ϣ
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��11��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_RegNCell(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MMC_NCELL_SEARCH_INFO_STRU     *pstMmcNcellSearchInfo = VOS_NULL_PTR;

    pstMmcNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();

    /* ĿǰNCELL��֧��LTE���뼼�� */
    stPrioRatList.ucRatNum      = 1;
    stPrioRatList.aucRatPrio[0] = NAS_MML_NET_RAT_TYPE_LTE;

    /* ��ѡ���б�������NCELL��Ϣ�е�PLMN ID */
    for (i = 0; i < pstMmcNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum; i ++)
    {
        NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstMmcNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr[0]),
                                   NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                   &stPrioRatList,
                                   pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_RegHPlmn
 ��������  : ����Home Plmnע��ʱ�����б��ʼ��
 �������  : pstSearchedPlmnListInfo,����������������Ϣ
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��11��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_RegHPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    /* ��ѡ���б�������HPLMN��EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_RegPrefPlmn
 ��������  : ������ѡPLMNע��ʱ�����б��ʼ��
 �������  : pstSearchedPlmnListInfo,����������������Ϣ
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��11��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��6��13��
   ��    ��   : b00269685
   �޸�����   : ����3gpp2,Pref���粻����UPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_RegPrefPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    /* ��ѡ���б�������HPLMN��EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    if (VOS_FALSE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
    {
        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* ��ѡ���б�������OPLMN */
        NAS_MMC_AddOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    return;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-02-11, End */

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_HighPrioLtePlmnSearch
 ��������  : �����ȼ���LTE�������б��ʼ��
 �������  : pstPlmnListSearched, MSCC�·���ת�����PLMN�б�
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��4��3��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_HighPrioLtePlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU                stTmpPlmnId;

    VOS_UINT32                                              ulHighPlmnIndex;
    VOS_UINT32                                              ulLowPlmnIndex;
    VOS_UINT8                                               ucRatIndex;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRatType;

    /* ��ѡ���б�������HPLMN��EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);

    if (VOS_FALSE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
    {
        /* ��ѡ���б�������UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }
    else
    {
        /* ��ѡ���б�������OPLMN */
        NAS_MMC_AddOPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
    }

    /* ������ѡ��LTE��PLMN�Ѿ�������һ�飬���������Ҫʹ���ѵ�����ѡ
       PLMN�б�ˢ����PLMN״̬�����ڲ����ڵ�PLMN�ڸ����ȼ�����ʱ
       ֱ���������������Ч��; */

    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        stTmpPlmnId = pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId;

        if (VOS_FALSE == NAS_MMC_IsPlmnIdInSearchedPlmnList(&stTmpPlmnId, pstSearchedPlmnListInfo))
        {
            /* δ���ҵ���ͬ����ѡPLMN,������ͬ���뼼����PLMN(Ŀǰ��������뼼����ȻΪLTE),����״
               ̬��Ҫ����Ϊ�ѹ�������,��֤����ʱ����������PLMN */
            NAS_MMC_UpdateRatNetStatusInPlmnRatInfo(pstSearchedPlmnListInfo->enRatType,
                                                    NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,
                                                    &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]));
        }
    }



    /* ��bsrʱhsd�������ѵ���plmn׷�ӵ�plmnѡ���б���(�ظ��Ĳ���) */

    PS_MEM_SET(&stPlmnInfo, 0x00, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    for (ucRatIndex = 0; ucRatIndex < NAS_MML_MAX_RAT_NUM; ucRatIndex++)
    {
        enRatType = pstSearchedPlmnListInfo[ucRatIndex].enRatType;

        if (NAS_MML_NET_RAT_TYPE_BUTT == enRatType)
        {
            continue;
        }

        /* �Ը��ź��������� */
        for (ulHighPlmnIndex = 0; ulHighPlmnIndex < pstSearchedPlmnListInfo[ucRatIndex].ulHighPlmnNum; ulHighPlmnIndex++)
        {
            stPlmnInfo.stPlmnId.ulMcc = pstSearchedPlmnListInfo[ucRatIndex].astHighPlmnList[ulHighPlmnIndex].ulMcc;
            stPlmnInfo.stPlmnId.ulMnc = pstSearchedPlmnListInfo[ucRatIndex].astHighPlmnList[ulHighPlmnIndex].ulMnc;

            /* �ѵ���plmn�������еĹ����������б��У�Ҫ׷�� */
            if (VOS_FALSE == NAS_MMC_IsPlmnInSearchList(stPlmnInfo, pstPlmnSelectionListInfo))
            {
                NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_InitPlmnSelectionList_HighPrioLtePlmnSearch, high srched plmn is not in plmn selectionlist:",
                                    stPlmnInfo.stPlmnId.ulMcc, stPlmnInfo.stPlmnId.ulMnc);

                stPrioRatList.ucRatNum      = 1;
                stPrioRatList.aucRatPrio[0] = pstSearchedPlmnListInfo[ucRatIndex].enRatType;

                NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(stPlmnInfo.stPlmnId),
                                                        NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                        &stPrioRatList,
                                                        pstPlmnSelectionListInfo);


            }
        }

        /* �Ե��ź��������� */
        for (ulLowPlmnIndex = 0; ulLowPlmnIndex < pstSearchedPlmnListInfo[ucRatIndex].ulLowPlmnNum; ulLowPlmnIndex++)
        {
            stPlmnInfo.stPlmnId.ulMcc = pstSearchedPlmnListInfo[ucRatIndex].astLowPlmnList[ulLowPlmnIndex].stPlmnId.ulMcc;
            stPlmnInfo.stPlmnId.ulMnc = pstSearchedPlmnListInfo[ucRatIndex].astLowPlmnList[ulLowPlmnIndex].stPlmnId.ulMnc;

            /* �ѵ���plmn�������еĹ����������б��У�Ҫ׷�� */
            if (VOS_FALSE == NAS_MMC_IsPlmnInSearchList(stPlmnInfo, pstPlmnSelectionListInfo))
            {
                NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_InitPlmnSelectionList_HighPrioLtePlmnSearch, low srched plmn is not in plmn selectionlist:",
                                    stPlmnInfo.stPlmnId.ulMcc, stPlmnInfo.stPlmnId.ulMnc);

                stPrioRatList.ucRatNum      = 1;
                stPrioRatList.aucRatPrio[0] = pstSearchedPlmnListInfo[ucRatIndex].enRatType;

                NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(stPlmnInfo.stPlmnId),
                                                        NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                        &stPrioRatList,
                                                        pstPlmnSelectionListInfo);
            }
        }
    }

    /* ��ά�ɲ⣬���ѡ���б���Ϣ */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_DplmnSet
 ��������  : ��������ΪNAS_MMC_PLMN_SEARCH_SCENE_DPLMN_SETʱ����ʼ��ѡ���б�
 �������  : NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
             NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_DplmnSet(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    /* ͬ������������GEO��Ϣʱ��ʹ��AP�����������µ�DPLMN�б��������б�
       ������GEO��Ϣ����RPLMN/HPLMNʱ������㱨PLMN_INFO_IND��Ҫ��ϣ���ʱ�յ�DPLMN SET�ĳ���
       ��Ҫ��RPLMN/HPLMN��ʼ�ѣ����յ�PLMN_INFO_IND��Ҫ��ϣ���ʱ��ʹ��AP�����������µ�DPLMN�б� */

    NAS_MMC_InitPlmnSelectionList_SwitchOn(pstPlmnSelectionListInfo, pstSearchedPlmnListInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildPlmnSelectionPlmnInfo
 ��������  : ����ѡ���б��е���PLMN��Ϣ
 �������  : enPlmnType:��������
             usSimRat:֧�ֵĽ��뼼��,��SIM���洢�ĸ�ʽ
             pstPlmnId:PLMN ID
 �������  : pstPlmnInfo,֧�ֵĽ��뼼������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��27��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_BuildPlmnSelectionPlmnInfo(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    VOS_UINT16                                              usSimRat,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo
)
{
    VOS_UINT8                           ucRatNum;

    ucRatNum                = 0x0;

    PS_MEM_CPY(&pstPlmnInfo->stPlmnId, pstPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
    pstPlmnInfo->enPlmnType = enPlmnType;

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_SIM_RAT_E_UTRN == (NAS_MML_SIM_RAT_E_UTRN & usSimRat))
    {
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_LTE;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        ucRatNum++;
    }
#endif

    if (NAS_MML_SIM_RAT_UTRN == (NAS_MML_SIM_RAT_UTRN & usSimRat))
    {
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_WCDMA;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        ucRatNum++;
    }

    if (NAS_MML_SIM_RAT_GSM == (NAS_MML_SIM_RAT_GSM & usSimRat))
    {
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_GSM;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        ucRatNum++;
    }

    pstPlmnInfo->ucRatNum = ucRatNum;

    /* ����ʣ��λ�ø�ֵΪ��Чֵ */
    for (; ucRatNum < NAS_MML_MAX_RAT_NUM; ucRatNum++)
    {
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_AddEHPlmnInPlmnSelectionList
 ��������  : �������б��м���EHPLMN��HPLMN
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddEHPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;

    /* ��ȡEHPLMN */
    pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();

    for (i = 0; i< pstEHPlmnInfo->ucEhPlmnNum; i++)
    {
        /* ����SIM���Ľ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
        NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_HPLMN,
                                           pstEHPlmnInfo->astEhPlmnInfo[i].usSimRat,
                                           &(pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId),
                                           &stPlmnInfo);

        /* ��ӵ������б� */
        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddEHPlmnInDestPlmn
 ��������  : ��Ŀ�ĵ������б��м���EHPLMN��HPLMN
 �������  : pstEHPlmnInfo        EHPLMN �б�
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��3��19��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��6��17��
   ��    ��   : z00234330
   �޸�����   : PCINT����
 3.��    ��   : 2015��9��30��
   ��    ��   : c00318887
   �޸�����   : DTS2015091700173
*****************************************************************************/
VOS_VOID NAS_MMC_AddEHPlmnInDestPlmnList(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo
)
{
    VOS_UINT32                                              i;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndexOfPlmnList;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnIdWithRat;
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg   = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stTempPlmn;

    if ( 0 == pstDestPlmnList->ulPlmnNum )
    {
        return;
    }

    /* ��ȡ��ֹ���뼼����PLMN��Ϣ */
    pstDisabledRatPlmnCfg = NAS_MML_GetDisabledRatPlmnInfo();

    /* ���б�ĵ�0λΪRPLMN */
    pstPlmnWithRat = &pstDestPlmnList->astPlmnId[0];


    PS_MEM_SET(&stTempPlmn, 0x00, sizeof(stTempPlmn));

    /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
    for (i = 0, (ulIndexOfPlmnList = 1); i< NAS_MML_MIN(pstEHPlmnInfo->ucEhPlmnNum, NAS_MML_MAX_EHPLMN_NUM); i++)
    /* Modified by z00234330 for PCLINT����, 2014-06-24, end */
    {
        /* ����SIM���Ľ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
        PS_MEM_SET(&stPlmnId, 0x00, sizeof(stPlmnId));
        PS_MEM_SET(&stPlmnIdWithRat, 0x00, sizeof(stPlmnIdWithRat));
        PS_MEM_CPY(&stPlmnId, &(pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId), sizeof(stPlmnId));
        PS_MEM_CPY(&stPlmnIdWithRat.stPlmnId, &stPlmnId, sizeof(stPlmnIdWithRat.stPlmnId));

        stPlmnIdWithRat.enRat = pstPlmnWithRat->enRat;

        if ( VOS_TRUE == NAS_MML_IsBcchPlmnIdWithRatInDestPlmnWithRatList(&stPlmnIdWithRat, pstDestPlmnList->ulPlmnNum, pstDestPlmnList->astPlmnId) )
        {
            continue;
        }

        /* �жϸ�PLMN�Ƿ��ںڰ������� */
        if ( VOS_TRUE == NAS_MML_IsPlmnIdForbiddenByWhiteBlackList(&stPlmnId) )
        {
            continue;
        }

        /* ��װstTempPlmn�������ж��Ƿ񱻽����뼼�� */
        stTempPlmn.enPlmnType                  = NAS_MMC_PLMN_TYPE_HPLMN;
        stTempPlmn.ucRatNum                    = 1;
        stTempPlmn.astPlmnRatInfo[0].enRatType = pstPlmnWithRat->enRat;
        PS_MEM_CPY(&stTempPlmn.stPlmnId, &stPlmnId, sizeof(stTempPlmn.stPlmnId));

        /* ɾ���ڽ�ֹ���뼼��������Ľ��뼼�� */
        NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList(&stTempPlmn,
                                                  pstDisabledRatPlmnCfg->ulDisabledRatPlmnNum,
                                                  pstDisabledRatPlmnCfg->astDisabledRatPlmnId);

        /* ɾ���ڽ�ֹ���뼼���б��еĽ��뼼�� */
        NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo(&stTempPlmn);

        /* ���������Ľ��뼼������Ϊ�㣬����� */
        if (0 == stTempPlmn.ucRatNum)
        {
            continue;
        }

        if ( NAS_MML_MAX_EHPLMN_NUM <= pstDestPlmnList->ulPlmnNum )
        {
            break;
        }

        pstDestPlmnList->astPlmnId[ulIndexOfPlmnList].enRat          = pstPlmnWithRat->enRat;

        PS_MEM_CPY(&(pstDestPlmnList->astPlmnId[ulIndexOfPlmnList].stPlmnId), &stPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
        pstDestPlmnList->ulPlmnNum++;
        ulIndexOfPlmnList++;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_AddEPlmnInDestPlmnList
 ��������  : ��Ŀ�ĵ������б��м���EPLMN
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��9��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddEPlmnInDestPlmnList(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIndexOfPlmnList;
    VOS_UINT32                                              ulCurPlmnNum;
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnIdWithRat;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    PS_MEM_SET(&stPlmnIdWithRat, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    ulCurPlmnNum = pstDestPlmnList->ulPlmnNum;

    if ( 0 == ulCurPlmnNum )
    {
        return;
    }

    pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
    PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
    NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);

    for (i = 0, (ulIndexOfPlmnList = ulCurPlmnNum); i< NAS_MML_MIN(stSndEquPlmnInfo.ucEquPlmnNum, NAS_MML_MAX_EHPLMN_NUM); i++)
    {
        stPlmnIdWithRat.stPlmnId.ulMcc = stSndEquPlmnInfo.astEquPlmnAddr[i].ulMcc;
        stPlmnIdWithRat.stPlmnId.ulMnc = stSndEquPlmnInfo.astEquPlmnAddr[i].ulMnc;
        stPlmnIdWithRat.enRat          = pstDestPlmnList->astPlmnId[0].enRat;

        /* ��Ҫ�����eplmn�Ѿ����б��������� */
        if ( VOS_TRUE == NAS_MML_IsBcchPlmnIdWithRatInDestPlmnWithRatList(&stPlmnIdWithRat, pstDestPlmnList->ulPlmnNum, pstDestPlmnList->astPlmnId) )
        {
            continue;
        }

        pstDestPlmnList->astPlmnId[ulIndexOfPlmnList].enRat = stPlmnIdWithRat.enRat;
        PS_MEM_CPY(&(pstDestPlmnList->astPlmnId[ulIndexOfPlmnList].stPlmnId), &stPlmnIdWithRat.stPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
        pstDestPlmnList->ulPlmnNum++;
        ulIndexOfPlmnList++;

        if (ulIndexOfPlmnList >= NAS_MML_MAX_EHPLMN_NUM)
        {
            return;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddDplmnOfSameCountryInDestPlmnList
 ��������  : ��Ŀ�ĵ������б��м���DPLMN
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��24��
   ��    ��   : l00289540
   �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��30��
    ��    ��   : c00318887
    �޸�����   : DTS2015120807529����Ҫ���ӵ�dplmn��fplmn���Ӧ����
*****************************************************************************/
VOS_VOID NAS_MMC_AddDplmnInDestPlmnList(
    NAS_MML_PLMN_WITH_RAT_STRU          *pstDestPlmn,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     *pstDestPlmnList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIsSameCountryAsDestPlmn;
    NAS_MML_MCC_DESC_STRU                                  *pstEquMccList           = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDplmnNplmnCfgInfo    = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList    = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stTempPlmn;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ��ȡ��ЧMCC�б� */
    pstEquMccList                       = NAS_MML_GetEquivalentMccList(pstDestPlmn->stPlmnId.ulMcc);

    /* ��ȡѡ���б� */
    pstPlmnSelectionList                = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    pstForbidPlmnInfo                   = NAS_MML_GetForbidPlmnInfo();
    PS_MEM_SET(&stTempPlmn, 0x00, sizeof(stTempPlmn));

    if ((0 == pstDestPlmnList->ulPlmnNum)
     || (VOS_NULL_PTR == pstEquMccList))
    {
        return;
    }

    pstDplmnNplmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* ��DPLMN List��ȡ������ͬ���ҵĵ�DPLMN��������뵽Ŀ���б��� */
    for (i = 0; i < pstDplmnNplmnCfgInfo->usDplmnListNum; i++)
    {
        /* ��ǰDPLMN��֧�ֵ�ǰ���뼼�� */
        if (VOS_FALSE == NAS_MMC_IsNetRatContainedInSimRat(pstDestPlmn->enRat, pstDplmnNplmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.usSimRat))
        {
            continue;
        }

        stPlmnWithRat.stPlmnId.ulMcc = pstDplmnNplmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMcc;
        stPlmnWithRat.stPlmnId.ulMnc = pstDplmnNplmnCfgInfo->astDPlmnList[i].stSimPlmnWithRat.stPlmnId.ulMnc;
        stPlmnWithRat.enRat = pstDestPlmn->enRat;

        ulIsSameCountryAsDestPlmn = NAS_MML_IsSpecMccInEquMccList(stPlmnWithRat.stPlmnId.ulMcc, pstEquMccList);
        enNetStatus = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&stPlmnWithRat, pstPlmnSelectionList);

        if ((VOS_TRUE == ulIsSameCountryAsDestPlmn)
         && (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != enNetStatus))
        {
            /* ��Ҫ�����Dplmn�Ѿ����б��������� */
            if ( VOS_TRUE == NAS_MML_IsBcchPlmnIdWithRatInDestPlmnWithRatList(&stPlmnWithRat, pstDestPlmnList->ulPlmnNum, pstDestPlmnList->astPlmnId) )
            {
                continue;
            }

            /* ��Ҫ�����Dplmn��forbid plmn�б��������� */
            if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(stPlmnWithRat.stPlmnId),
                                                  pstForbidPlmnInfo->ucForbPlmnNum,
                                                  pstForbidPlmnInfo->astForbPlmnIdList))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: dplmn in forbPlmnIdList");
                continue;
            }   
            
            /* �жϸ�PLMN�Ƿ��ںڰ������� */
            if ( VOS_TRUE == NAS_MML_IsPlmnIdForbiddenByWhiteBlackList(&(stPlmnWithRat.stPlmnId)) )
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: dplmn in WhiteBlackList");
                continue;
            }
            
            /* ��PLMN ID�Ƿ�������������PLMN �б��� */
            if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInLockPlmnList(&(stPlmnWithRat.stPlmnId)))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: dplmn in LockPlmnList");
                continue;
            }
            
            /* ����������ʱ */
            if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(&(stPlmnWithRat.stPlmnId)))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: dplmn RoamingAllowed is false");
                continue;
            } 
            /* ��ǰplmn��MCC�ڽ�ֹLTE�������ε�MCC�б���,PLMN��������ע�� */
            if (VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(stPlmnWithRat.stPlmnId.ulMcc))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList:  dplmn IsNeedDisableLteRoam is true");
                continue;
            }            
            
            /* �жϵ�ǰPLMN�Ƿ��ڽ�ֹRAT��PLMN�б���ͬʱ��ǰ���뼼������ֹ,����Ϊ��ǰPLMNΪ��ֹ���� */
            if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList return true");
                continue;
            }
            
            /* �ж�PLMN��RAT�ڽ�ֹ���뼼���б��У�����Ϊ��ǰRAT��Ӧ����Ϊ��ֹ���� */
            if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(stPlmnWithRat.enRat))
            {
                NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_AddDplmnInDestPlmnList: NAS_MML_IsRatInForbiddenList return true");
                continue;
            }

            /* Ŀ���б����������˳��˺��� */
            if ( NAS_MML_MAX_EHPLMN_NUM <= pstDestPlmnList->ulPlmnNum )
            {
                return;
            }

            pstDestPlmnList->astPlmnId[pstDestPlmnList->ulPlmnNum].enRat = stPlmnWithRat.enRat;
            PS_MEM_CPY(&(pstDestPlmnList->astPlmnId[pstDestPlmnList->ulPlmnNum].stPlmnId), &stPlmnWithRat.stPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
            pstDestPlmnList->ulPlmnNum++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddUOPlmnInPlmnSelectionList
 ��������  : �������б��м���UPLMN��OPLMN,������в������������ļ�,���PlmnSel
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��    : 2013��11��26��
   ��    ��    : s00190137
   �޸�����    : �����֧�����õ�OPLMN��չ��256��
 3.��    ��   : 2014��6��13��
   ��    ��   : b00269685
   �޸�����   : ����3gpp2,Pref���粻����UPLMN

*****************************************************************************/
VOS_VOID NAS_MMC_AddUOPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_SIM_USERPLMN_INFO_STRU                         *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU                         *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU                          *pstSelPlmnList  = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;
    VOS_UINT16                                              usSimRat;

    /* ��ȡUOPLMN */
    pstUserPlmnList = NAS_MML_GetSimUserPlmnList();

    pstOperPlmnList = NAS_MML_GetSimOperPlmnList();

    /* UPLMN������Ϊ0����OPLMN������Ϊ0 */
    if ((pstUserPlmnList->ucUserPlmnNum > 0)
     || (pstOperPlmnList->usOperPlmnNum > 0))
    {
        for (i = 0; i< pstUserPlmnList->ucUserPlmnNum; i++)
        {

            /* UPLMN����Plmn��Ч����usSimRatΪ0ʱ��Ĭ�϶�֧�� */
            usSimRat = pstUserPlmnList->astUserPlmnInfo[i].usSimRat;

            if (0 == usSimRat)
            {
                usSimRat = NAS_MML_SIM_RAT_ALL_SUPPORT;
            }

            /* ����SIM���Ľ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_UPLMN,
                                               usSimRat,
                                               &(pstUserPlmnList->astUserPlmnInfo[i].stPlmnId),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
        }

        for (i = 0; i< pstOperPlmnList->usOperPlmnNum; i++)
        {
            /* OPLMN����Plmn��Ч����usSimRatΪ0ʱ��Ĭ�϶�֧�� */
            usSimRat = pstOperPlmnList->astOperPlmnInfo[i].usSimRat;

            if (0 == usSimRat)
            {
                usSimRat = NAS_MML_SIM_RAT_ALL_SUPPORT;
            }

            /* ����SIM���Ľ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_OPLMN,
                                               usSimRat,
                                               &(pstOperPlmnList->astOperPlmnInfo[i].stPlmnId),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
        }
    }
    else /* ��ʾ(U)SIM���в�����UPLMN��OPLMN�������PLMN Sel�ļ� */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        for (i = 0; i< pstSelPlmnList->ucSelPlmnNum; i++)
        {
            /* ����SIM���Ľ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_OPLMN,
                                               NAS_MML_SIM_RAT_ALL_SUPPORT,
                                               &(pstSelPlmnList->astPlmnId[i]),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddOPlmnInPlmnSelectionList
 ��������  : �������б��м���OPLMN,������в������������ļ�,���PlmnSel
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��5��15��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddOPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_SIM_USERPLMN_INFO_STRU                         *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU                         *pstOperPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_SELPLMN_INFO_STRU                          *pstSelPlmnList  = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;
    VOS_UINT16                                              usSimRat;

    /* ��ȡUOPLMN */
    pstUserPlmnList = NAS_MML_GetSimUserPlmnList();

    pstOperPlmnList = NAS_MML_GetSimOperPlmnList();

    /* UPLMN������Ϊ0����OPLMN������Ϊ0 */
    if ((pstUserPlmnList->ucUserPlmnNum > 0)
     || (pstOperPlmnList->usOperPlmnNum > 0))
    {
        for (i = 0; i< pstOperPlmnList->usOperPlmnNum; i++)
        {
            /* OPLMN����Plmn��Ч����usSimRatΪ0ʱ��Ĭ�϶�֧�� */
            usSimRat = pstOperPlmnList->astOperPlmnInfo[i].usSimRat;

            if (0 == usSimRat)
            {
                usSimRat = NAS_MML_SIM_RAT_ALL_SUPPORT;
            }

            /* ����SIM���Ľ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_OPLMN,
                                               usSimRat,
                                               &(pstOperPlmnList->astOperPlmnInfo[i].stPlmnId),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
        }
    }
    else /* ��ʾ(U)SIM���в�����UPLMN��OPLMN�������PLMN Sel�ļ� */
    {
        pstSelPlmnList = NAS_MML_GetSimSelPlmnList();

        for (i = 0; i< pstSelPlmnList->ucSelPlmnNum; i++)
        {
            /* ����SIM���Ľ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_OPLMN,
                                               NAS_MML_SIM_RAT_ALL_SUPPORT,
                                               &(pstSelPlmnList->astPlmnId[i]),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode
 ��������  : �ֶ�����ģʽ���������б��м���EPLMN
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:���ıȽϵ��Ⱥ�˳����Ϊ��ǰפ������������
                ΪBCCH�ġ�

*****************************************************************************/
VOS_VOID NAS_MMC_AddEPlmnInPlmnSelectionListInAutoMode(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnList = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;

    /* ��ǰRplmn������ʱ�������Eplmn */
    if (VOS_FALSE == NAS_MML_GetRPlmn(NAS_MML_GetLastRplmnRat(), &stPlmnId))
    {
        return;
    }

    pstEquPlmnList = NAS_MML_GetEquPlmnList();


    /* Rplmn�� EplmnList[0]����ͬʱ������Ҫ��� */
    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId, &(pstEquPlmnList->astEquPlmnAddr[0])))
    {
        return;
    }

    for (i = 1; i < pstEquPlmnList->ucEquPlmnNum; i++)
    {
        /* ����SIM���Ľ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
        NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_EPLMN,
                                           NAS_MML_SIM_RAT_ALL_SUPPORT,
                                           &(pstEquPlmnList->astEquPlmnAddr[i]),
                                           &stPlmnInfo);

        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode
 ��������  : �������б��м���EPLMN
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:���ıȽϵ��Ⱥ�˳����Ϊ��ǰפ������������
                ΪBCCH�ġ�

*****************************************************************************/
VOS_VOID NAS_MMC_AddEPlmnInPlmnSelectionListInMannulMode(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnList = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;


    pstEquPlmnList = NAS_MML_GetEquPlmnList();


    for (i = 1; i < pstEquPlmnList->ucEquPlmnNum; i++)
    {
        /* ����SIM���Ľ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
        NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_EPLMN,
                                           NAS_MML_SIM_RAT_ALL_SUPPORT,
                                           &(pstEquPlmnList->astEquPlmnAddr[i]),
                                           &stPlmnInfo);

        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddRPlmnInPlmnSelectionList
 ��������  : �������б��а��ض����뼼������˳�����RPLMN
 �������  : pstPrioRatList
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddRPlmnInPlmnSelectionList(
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;
    NAS_MML_PLMN_ID_STRU                                    stRPlmn;
    NAS_MML_RPLMN_CFG_INFO_STRU                            *pstRPlmnCfg  = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRPlmnRat;

    /* ��ȡRPLMN������Ϣ */
    pstRPlmnCfg = NAS_MML_GetRplmnCfg();

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        enRPlmnRat = pstPrioRatList->aucRatPrio[i];

        /* �����RPLMN����δ����,��ʹ�����ע��ɹ���RPLMN��Ϊ���н��뼼����RPLMN
           ���ߵ�ǰΪ�ֶ�ѡ��ģʽ,Ҳֻ�����ע��ɹ���RPLMNΪָ�������EPLMN,����RPLMN�������� */
        if ((NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
         || (VOS_FALSE == pstRPlmnCfg->ucMultiRATRplmnFlg))
        {
            enRPlmnRat = pstRPlmnCfg->enLastRplmnRat;
        }

        /* RPLMN��ȡʧ�� */
        if (VOS_FALSE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(enRPlmnRat,
                                                               &stRPlmn))
        {
            continue;
        }

        switch (pstPrioRatList->aucRatPrio[i])
        {
#if   (FEATURE_ON == FEATURE_LTE)
            case NAS_MML_NET_RAT_TYPE_LTE:

                /* ���ݵ�ǰ���뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_RPLMN,
                                                   NAS_MML_SIM_RAT_E_UTRN,
                                                   &stRPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;
#endif

            case NAS_MML_NET_RAT_TYPE_WCDMA:

                /* ���ݵ�ǰ���뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_RPLMN,
                                                   NAS_MML_SIM_RAT_UTRN,
                                                   &stRPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;

            case NAS_MML_NET_RAT_TYPE_GSM:

                /* ���ݵ�ǰ���뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_RPLMN,
                                                   NAS_MML_SIM_RAT_GSM,
                                                   &stRPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;

            default:
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_AddRPlmnInPlmnSelectionList: Rat not support.");
                break;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList
 ��������  : �������б��м����û�ָ������PLMN
 �������  : ��
 �������  : pstPlmnSelectionListInfo,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��27��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddUserSpecSearchPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;

    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

    /* ���ݽ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
    NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                       NAS_MML_SIM_RAT_ALL_SUPPORT,
                                       &(pstUserSpecPlmn->stPlmnId),
                                       &stPlmnInfo);

    NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);

    return;
}

/* Modified by z40661 for ̩��AIS���� 2012-05-17, begin */

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddAisRoamPlmnInPlmnSelectionList
 ��������  : �������б��м���AIS��������PLMN
 �������  : ��
 �������  : pstPlmnSelectionListInfo,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��5��17��
   ��    ��   : z40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddAisRoamPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_AIS_ROAMING_CFG_STRU           *pstRoamingCfg   = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU   stPlmnInfo;
    VOS_UINT16                              usSimRat;

    pstRoamingCfg  = NAS_MML_GetAisRoamingCfg();



#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == pstRoamingCfg->enHighPrioRatType )
    {
        usSimRat = NAS_MML_SIM_RAT_E_UTRN;
    }
#endif
    if ( NAS_MML_NET_RAT_TYPE_WCDMA == pstRoamingCfg->enHighPrioRatType )
    {
        usSimRat = NAS_MML_SIM_RAT_UTRN;
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == pstRoamingCfg->enHighPrioRatType )
    {
        usSimRat = NAS_MML_SIM_RAT_GSM;
    }
    else
    {
        usSimRat = NAS_MML_SIM_NO_RAT;
    }

    /* ���ݽ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
    NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_HPLMN,
                                       usSimRat,
                                       &(pstRoamingCfg->stHighPrioPlmnId),
                                       &stPlmnInfo);

    NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);

}


/* Modified by z40661 for ̩��AIS���� 2012-05-17, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddSpecPlmnInPlmnSelectionList
 ��������  : �������б��а��ض����뼼������˳�����ָ������
 �������  : pstPlmn
             enPlmnType
             pstPrioRatList
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddSpecPlmnInPlmnSelectionList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmn,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        switch (pstPrioRatList->aucRatPrio[i])
        {
#if   (FEATURE_ON == FEATURE_LTE)
            case NAS_MML_NET_RAT_TYPE_LTE:

                /* ���ݵ�ǰ���뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_E_UTRN,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;
#endif

            case NAS_MML_NET_RAT_TYPE_WCDMA:

                /* ���ݵ�ǰ���뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_UTRN,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;

            case NAS_MML_NET_RAT_TYPE_GSM:

                /* ���ݵ�ǰ���뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_GSM,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSelectionListInfo);
                break;

            default:
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_AddSpecPlmnInPlmnSelectionList: Rat not support.");
                break;
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_AppendPlmnInPlmnSelectionList
 ��������  : �������б��м���ָ��PLMN
 �������  : pstPlmn
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
                ����ΪNAS_MML_IsSimPlmnIdInDestBcchPlmnList,��ȷ����ıȽ����ͣ�
                ������ܵ��±Ƚϳ���
 3.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ:ɾ��NAS_FEATURE_BLACK_WHITE_PLMN��
 4.��    ��   : 2012��8��15��
   ��    ��   : w00176964
   �޸�����   : V7R1C50_GUTL_PhaseII:����ǰPLMN�еĽ�ֹ���뼼��ɾ��

  5.��    ��   : 2012��9��24��
    ��    ��   : w00167002
    �޸�����   : DTS2012092405740:ɾ����ֹ������뼼��ʱ�����ı䴫�ݽ�����������Ϣ��
                 ԭ�е������������:�û��·��б��ѣ���ǰ����46001W,23001W,46001G,
                 ����46001WΪ��ֹ���磬�б�ֻ�ϱ���46001G,û���ϱ�23001W.
  6.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
*****************************************************************************/
VOS_VOID NAS_MMC_AppendPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT16                                              usSearchPlmnNum;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stTempPlmn;

    NAS_MML_PLMN_LOCK_CFG_INFO_STRU                        *pstPlmnLockCfg          = VOS_NULL_PTR;
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg   = VOS_NULL_PTR;

    PS_MEM_SET(&stTempPlmn, 0, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

    /* ��ȡ��ֹ���뼼����PLMN��Ϣ */
    pstDisabledRatPlmnCfg = NAS_MML_GetDisabledRatPlmnInfo();

    /* ���ڻ�ȡ�ڰ����� */
    pstPlmnLockCfg = NAS_MML_GetPlmnLockCfg();

    /* ��������������pstPlmn����ʱ�ֲ�������ȥ����֤pstPlmn���ݲ��ᱻ��ǰ�����޸� */
    PS_MEM_CPY(&stTempPlmn, pstPlmn, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU) );

    /* ��PLMN��Ч */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&(stTempPlmn.stPlmnId)))
    {
        return;
    }

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    /* �жϵ�ǰ�������Ƿ��ں������б��У�������ֱ�ӷ���VOS_FALSE */
    if ( VOS_TRUE == NAS_MMC_IsSpecTypePlmnIdInDestPlmnList(&(stTempPlmn.stPlmnId),
                                           stTempPlmn.enPlmnType,
                                           pstPlmnLockCfg->ucBlackPlmnLockNum,
                                           pstPlmnLockCfg->astBlackPlmnId) )     /* ��PLMN�ں������б��� */
    {
        return;
    }

    if (pstPlmnLockCfg->ucWhitePlmnLockNum != 0)
    {
        /* �жϵ�ǰ�������Ƿ��ڰ������б��У���������ֱ�ӷ���VOS_FALSE */
        if (VOS_FALSE == NAS_MMC_IsSpecTypePlmnIdInDestPlmnList(&(stTempPlmn.stPlmnId),
                                               stTempPlmn.enPlmnType,
                                               pstPlmnLockCfg->ucWhitePlmnLockNum,
                                               pstPlmnLockCfg->astWhitePlmnId))     /* ��PLMN���ڰ������б��� */
        {
            return;
        }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(&(stTempPlmn.stPlmnId))) /* ��PLMN�������������б��� */
    {
        return;
    }

    /* ɾ���ڽ�ֹ���뼼��������Ľ��뼼�� */
    NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList(&stTempPlmn,
                                              pstDisabledRatPlmnCfg->ulDisabledRatPlmnNum,
                                              pstDisabledRatPlmnCfg->astDisabledRatPlmnId);

    /* ɾ���ڽ�ֹ���뼼���б��еĽ��뼼�� */
    NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo(&stTempPlmn);

    /* ���������Ľ��뼼������Ϊ�㣬����� */
    if (0 == stTempPlmn.ucRatNum)
    {
        return;
    }

    usSearchPlmnNum = pstPlmnSelectionListInfo->usSearchPlmnNum;

    if (usSearchPlmnNum >= NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_AppendPlmnInPlmnSelectionList: list full.");

        return;
    }

    /*����PLMN�洢���б�β��,PLMN������1*/
    PS_MEM_CPY(&(pstPlmnSelectionListInfo->astPlmnSelectionList[usSearchPlmnNum]),
               &stTempPlmn, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
    pstPlmnSelectionListInfo->usSearchPlmnNum++;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AppendPlmnInRoamPlmnSelectionList
 ��������  : �������б��м���ָ��PLMN
 �������  : pstPlmn - ָ��plmn��Ϣ
 �������  : pstSearchedPlmnListInfo - �б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��30��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
 2.��    ��   : 2016��1��4��
   ��    ��   : s00217060
   �޸�����   : DTS2015120406613:�ѵ����ε����粻����

*****************************************************************************/
VOS_VOID NAS_MMC_AppendPlmnInRoamPlmnSelectionList(
    NAS_MMC_ROAM_PLMN_INFO_STRU                            *pstPlmn,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedPlmnListInfo
)
{
    VOS_UINT16                                              usSearchPlmnNum;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stTempPlmn;
    NAS_MML_LAI_STRU                                        stLai;
    VOS_UINT8                                               ucAllBandSearch;
    VOS_UINT32                                              i;

    PS_MEM_SET(&stTempPlmn, 0, sizeof(stTempPlmn));
    PS_MEM_SET(&stLai, 0, sizeof(stLai));
    i               = 0;
    usSearchPlmnNum = 0;

    /* ��������������pstPlmn����ʱ�ֲ�������ȥ����֤pstPlmn���ݲ��ᱻ��ǰ�����޸� */
    PS_MEM_CPY(&stTempPlmn, pstPlmn, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU) );

    /* plmn��Ч������roam�����б� */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&stTempPlmn.stPlmnWithRat.stPlmnId))
    {
        return;
    }

    ucAllBandSearch = NAS_MMC_GetAllBandSearch_PlmnSelection(stTempPlmn.stPlmnWithRat.enRat);

    /* ����ý��뼼��֮ǰ�Ѿ��յ���searched plmn info ind���Ź�һ����,���Ѿ����й�һ��ȫƵ��������
       ����Ӹý��뼼��plmn��roam�����б� */
    if (VOS_TRUE == NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(stTempPlmn.stPlmnWithRat.enRat))
    {
        return;
    }

    /* ���ĳ��ģ�Ǵ�ģ�����Ҹ�ģ���Ѿ����й�һ��ȫƵ����������������ʱֻ�ŵ�ǰ��ģ�����������ģ�������� */
    if ((pstPlmn->stPlmnWithRat.enRat != NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE == ucAllBandSearch))
    {
        return;
    }

    usSearchPlmnNum = pstSearchedPlmnListInfo->usSearchPlmnNum;

    if (usSearchPlmnNum >= NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_AppendPlmnInRoamPlmnSelectionList: list full.");

        return;
    }

    /* ����Ѿ���roam�����б��У���������� */
    for (i = 0; i < pstSearchedPlmnListInfo->usSearchPlmnNum; i++)
    {
        if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stTempPlmn.stPlmnWithRat.stPlmnId, &pstSearchedPlmnListInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId))
         && (stTempPlmn.stPlmnWithRat.enRat == pstSearchedPlmnListInfo->astPlmnSelectionList[i].stPlmnWithRat.enRat))
        {
            return;
        }
    }

    stLai.stPlmnId         = stTempPlmn.stPlmnWithRat.stPlmnId;
    stLai.enCampPlmnNetRat = stTempPlmn.stPlmnWithRat.enRat;
    stLai.aucLac[0]        = stTempPlmn.aucLac[0];
    stLai.aucLac[1]        = stTempPlmn.aucLac[1];
    stLai.ucRac            = NAS_MML_RAC_INVALID;

    /* ��ȡ�����ֹ���ͣ�����ǽ�ֹ�����򲻼���roam�����б� */
    if (NAS_MML_PLMN_FORBID_NULL != NAS_MML_GetLaiForbType(&stLai))
    {
        return;
    }

    /*����PLMN�洢���б�β��,PLMN������1*/
    PS_MEM_CPY(&(pstSearchedPlmnListInfo->astPlmnSelectionList[usSearchPlmnNum]),
               &stTempPlmn, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));

    pstSearchedPlmnListInfo->usSearchPlmnNum++;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InsertPlmnInPlmnSelectionList
 ��������  : �������б��в���ָ��PLMN
 �������  : pstPlmn:��Ҫ�����PLMN��Ϣ
             ulPos:��Ҫ�����λ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_UINT32 VOS_TRUE :����ɹ�
                        VOS_FALSE:����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
2. ��    ��   : 2013��8��26��
   ��    ��   : w00242748
   �޸�����   : DTS2013071808373,����澯����
*****************************************************************************/
VOS_UINT32 NAS_MMC_InsertPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulPos
)
{
    VOS_UINT16                          usSearchPlmnNum;

    usSearchPlmnNum = pstPlmnSelectionListInfo->usSearchPlmnNum;

    if ((usSearchPlmnNum >= NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST)
     || (ulPos >= NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_InsertPlmnInPlmnSelectionList: list full.");

        return VOS_FALSE;
    }

    if ((NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - 1) != ulPos)
    {
        /* ����ulPosλ�ÿճ� */
        /*lint -e961*/
        (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[ulPos+1]),
                    &(pstPlmnSelectionListInfo->astPlmnSelectionList[ulPos]),
                    (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST-ulPos-1)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
        /*lint +e961*/
    }

    /* ����PLMN���뵽�����б��ulPosλ�� */
    PS_MEM_CPY(&(pstPlmnSelectionListInfo->astPlmnSelectionList[ulPos]),
               pstPlmn, sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
    pstPlmnSelectionListInfo->usSearchPlmnNum++;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InsertPlmnToPlmnSelectionListHead
 ��������  : ��ѡ���б�ǰ�水���뼼������˳�����ָ��PLMN
 �������  : pstPlmn:��Ҫ�����PLMN
             enPlmnType
             pstPrioRatList,����Ľ��뼼�����ȼ�˳��
             ulPos:��Ҫ�����λ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_InsertPlmnToPlmnSelectionListHead(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmn,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulPos;

    ulRet                               = VOS_FALSE;
    ulPos                               = 0;

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        switch (pstPrioRatList->aucRatPrio[i])
        {
#if   (FEATURE_ON == FEATURE_LTE)
            case NAS_MML_NET_RAT_TYPE_LTE:

                /* ���ݵ�ǰ���뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_E_UTRN,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                ulRet = NAS_MMC_InsertPlmnInPlmnSelectionList(&stPlmnInfo,
                                                              pstPlmnSelectionListInfo,
                                                              ulPos);
                break;
#endif

            case NAS_MML_NET_RAT_TYPE_WCDMA:

                /* ���ݵ�ǰ���뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_UTRN,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                ulRet = NAS_MMC_InsertPlmnInPlmnSelectionList(&stPlmnInfo,
                                                              pstPlmnSelectionListInfo,
                                                              ulPos);
                break;

            case NAS_MML_NET_RAT_TYPE_GSM:

                /* ���ݵ�ǰ���뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
                NAS_MMC_BuildPlmnSelectionPlmnInfo(enPlmnType,
                                                   NAS_MML_SIM_RAT_GSM,
                                                   pstPlmn,
                                                   &stPlmnInfo);

                ulRet = NAS_MMC_InsertPlmnInPlmnSelectionList(&stPlmnInfo,
                                                              pstPlmnSelectionListInfo,
                                                              ulPos);
                break;

            default:
                NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_InsertSpecPlmnInPlmnSelectionList: Rat not support.");
                break;
        }

        if (VOS_TRUE == ulRet)
        {
            ulPos++;
            ulRet = VOS_FALSE;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateRatNetStatusInPlmnRatInfo
 ��������  : ����ָ��PLMN�Ķ�Ӧ���뼼��������״̬��Ϣ
 �������  : pstSrcPlmn
 �������  : pstDstPlmn,
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��19��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateRatNetStatusInPlmnRatInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstDstPlmn
)
{
    VOS_UINT32                             i;

    /* ��ԭPLMN��ÿһ��֧�ֵĽ��뼼����Ŀ��PLMN��ÿһ��֧�ֵĽ��뼼�����бȽ� */
    for (i = 0; i < pstDstPlmn->ucRatNum; i++)
    {
        /* �����ͬ�������Ŀ��PLMN��Ϣ�е�״̬��Ϣ */
        if (pstDstPlmn->astPlmnRatInfo[i].enRatType == enRat)
        {
            pstDstPlmn->astPlmnRatInfo[i].enNetStatus = enNetStatus;

            return;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList
 ��������  : ��ȡ�����б���ָ�����뼼�����������������
 �������  : pstPlmnWithRat
             pstPlmnSelectionList,�б���Ϣ
 �������  : ��
 �� �� ֵ  : NAS_MMC_PLMN_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
NAS_MMC_PLMN_TYPE_ENUM_UINT8 NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;

    enPlmnType = NAS_MMC_GetPlmnTypeInPlmnSelectionList(pstPlmnWithRat, pstPlmnSelectionListInfo);

    if (NAS_MMC_PLMN_TYPE_BUTT == enPlmnType)
    {
        enPlmnType = NAS_MMC_PLMN_TYPE_AVAIL_PLMN;
    }

    /* ���������б���plmn���ظ����������п��ܼ���rplmn����uplmn����Ҫ���ж������Ƿ���UPLMN */
    if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithUplmn(pstPlmnWithRat))
    {
        enPlmnType = NAS_MMC_PLMN_TYPE_UPLMN;
        return enPlmnType;
    }

    /* ���������б���plmn���ظ����������п��ܼ���rplmn����uplmn����Ҫ���ж������Ƿ���OPLMN */
    if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithOplmn(pstPlmnWithRat))
    {
        enPlmnType = NAS_MMC_PLMN_TYPE_OPLMN;
        return enPlmnType;
    }

    return enPlmnType;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList
 ��������  : ��ȡ�����б���ָ������ĵ������뼼���������״̬
 �������  : pstPlmnWithRat
             pstPlmnSelectionList,�б���Ϣ
 �������  : ��
 �� �� ֵ  : NAS_MMC_NET_STATUS_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

 2.��    ��   : 2015��10��6��
   ��    ��   : c00318887
   �޸�����   : �޸ĺ�������
*****************************************************************************/
NAS_MMC_NET_STATUS_ENUM_UINT8 NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;
    NAS_MMC_NET_STATUS_ENUM_UINT8                           aucNetStatus[NAS_MML_MAX_RAT_NUM];
    VOS_UINT8                                               i;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(stPrioRatList));

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        aucNetStatus[i] = NAS_MMC_NET_STATUS_BUTT;
    }

    stPrioRatList.ucRatNum      = 1;
    stPrioRatList.aucRatPrio[0] = pstPlmnWithRat->enRat;
    NAS_MMC_GetSpecPlmnNetStatusInPlmnSelectionList(&pstPlmnWithRat->stPlmnId,
                                                    &stPrioRatList,
                                                    aucNetStatus,
                                                    pstPlmnSelectionListInfo);

    return  aucNetStatus[0];
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList
 ��������  : �����������б��м�������
 �������  : pstRoamPlmnInfo - ����������Ϣ
 �������  : pstNewRoamPlmnSelectionList - �����б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��28��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�

*****************************************************************************/
VOS_VOID NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList(
    NAS_MMC_ROAM_PLMN_INFO_STRU                            *pstRoamPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stRoamPlmnInfo;
    VOS_UINT16                                              usSimRat;

    /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    enPlmnType      = NAS_MMC_PLMN_TYPE_BUTT;
    i               = 0;

    PS_MEM_SET(&stPlmnInfo, 0, sizeof(stPlmnInfo));
    PS_MEM_SET(&stRoamPlmnInfo, 0, sizeof(stRoamPlmnInfo));
    PS_MEM_SET(&stPrioRatList, 0, sizeof(stPrioRatList));

    /* ��ȡ�洢DPLMN��NPLMN��ָ�� */
    pstDPlmnNPlmnCfgInfo = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* ��ȡ��ǰ֧�ֵĽ��뼼���������ȼ� */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* ��ѡ���б������ӽ���㱨���������磬��ǰ�������뼼������ */
    NAS_MML_SortSpecRatPrioHighest(pstRoamPlmnInfo->stPlmnWithRat.enRat, &stPrioRatList);


    /* ��������������NPLMN�У�����ӵ�roam�����б���,��������б���û������������б������ */
    if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&pstRoamPlmnInfo->stPlmnWithRat,
                    pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList))
    {
        if (VOS_FALSE == NAS_MMC_IsPlmnWithRatInPlmnList(&pstRoamPlmnInfo->stPlmnWithRat.stPlmnId,
                                                         pstRoamPlmnInfo->stPlmnWithRat.enRat,
                                                         pstPlmnSrchList,
                                                         pstPlmnSrchList->usSearchPlmnNum))
        {
            usSimRat = NAS_MMC_ConvertNetRatToSimRat(pstRoamPlmnInfo->stPlmnWithRat.enRat);

            NAS_MMC_BuildPlmnSelectionPlmnInfo(pstRoamPlmnInfo->enPlmnType,
                                               usSimRat,
                                               &(pstRoamPlmnInfo->stPlmnWithRat.stPlmnId),
                                               &stPlmnInfo);

            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSrchList);
        }
    }
    else
    {
        NAS_MMC_AppendPlmnInRoamPlmnSelectionList(pstRoamPlmnInfo, pstNewRoamPlmnSelectionList);
    }

    /* �����������뼼��plmn��roam�����б� */
    for (i = 1; i < stPrioRatList.ucRatNum; i++)
    {
        stRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = pstRoamPlmnInfo->stPlmnWithRat.stPlmnId.ulMcc;
        stRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = pstRoamPlmnInfo->stPlmnWithRat.stPlmnId.ulMnc;
        stRoamPlmnInfo.stPlmnWithRat.enRat = stPrioRatList.aucRatPrio[i];

        enPlmnType                 = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stRoamPlmnInfo.stPlmnWithRat, pstPlmnSrchList);
        stRoamPlmnInfo.enPlmnType  = enPlmnType;
        stRoamPlmnInfo.enNetStatus = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&stRoamPlmnInfo.stPlmnWithRat, pstPlmnSrchList);

        if (NAS_MMC_NET_STATUS_BUTT == stRoamPlmnInfo.enNetStatus)
        {
            stRoamPlmnInfo.enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
        }

        /* �����������NPLMN������Ӹ����絽roam�����б�,��������б��в����ڣ�����������б������ */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&stRoamPlmnInfo.stPlmnWithRat,
                        pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList))
        {
            if (VOS_FALSE == NAS_MMC_IsPlmnWithRatInPlmnList(&stRoamPlmnInfo.stPlmnWithRat.stPlmnId,
                                                         stRoamPlmnInfo.stPlmnWithRat.enRat,
                                                         pstPlmnSrchList,
                                                         pstPlmnSrchList->usSearchPlmnNum))
            {
                usSimRat = NAS_MMC_ConvertNetRatToSimRat(stRoamPlmnInfo.stPlmnWithRat.enRat);

                NAS_MMC_BuildPlmnSelectionPlmnInfo(stRoamPlmnInfo.enPlmnType,
                                                   usSimRat,
                                                   &(stRoamPlmnInfo.stPlmnWithRat.stPlmnId),
                                                   &stPlmnInfo);

                NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstPlmnSrchList);
            }

            continue;
        }

        NAS_MMC_AppendPlmnInRoamPlmnSelectionList(&stRoamPlmnInfo, pstNewRoamPlmnSelectionList);

    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRoamPlmnType
 ��������  : ��ȡ������������
 �������  : pstPlmnInfo - ������Ϣ
 �������  : ��
 �� �� ֵ  : ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��13��
    ��    ��   : l00289540
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
*****************************************************************************/
NAS_MMC_ROAM_PLMN_TYPE_ENUM_UINT8 NAS_MMC_GetRoamPlmnType(
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstPlmnInfo
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MML_LAI_STRU                                        stLai;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));
    PS_MEM_SET(&stLai, 0, sizeof(stLai));

    /* ��ȡ�洢DPLMN��NPLMN��ָ�� */
    pstDPlmnNPlmnCfgInfo   = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    stLai.stPlmnId         = pstPlmnInfo->stPlmnWithRat.stPlmnId;
    stLai.enCampPlmnNetRat = pstPlmnInfo->stPlmnWithRat.enRat;
    stLai.aucLac[0]        = pstPlmnInfo->aucLac[0];
    stLai.aucLac[1]        = pstPlmnInfo->aucLac[1];
    stLai.ucRac            = NAS_MML_RAC_INVALID;

    /* �ж������Ƿ�Ϊ��ֹ���� */
    if (NAS_MML_PLMN_FORBID_NULL != NAS_MML_GetLaiForbType(&stLai))
    {
        return NAS_MMC_ROAM_PLMN_TYPE_FORBIDDEN;
    }

    /* �ж������Ƿ���NPLMN�б��� */
    if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&pstPlmnInfo->stPlmnWithRat,
                      pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList))
    {
        return NAS_MMC_ROAM_PLMN_TYPE_NPLMN;
    }

    if (VOS_TRUE == NAS_MMC_GetSrchUOplmnPriorToDplmnFlg())
    {
        /* �ж������Ƿ���UPLMN */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithUplmn(&pstPlmnInfo->stPlmnWithRat))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_UPLMN;
        }

        /* �ж������Ƿ���OPLMN */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithOplmn(&pstPlmnInfo->stPlmnWithRat))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_OPLMN;
        }

        /* �ж������Ƿ���DPLMN�� */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&pstPlmnInfo->stPlmnWithRat,
                               pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_DPLMN;
        }
    }
    else
    {
        /* �ж������Ƿ���DPLMN�� */
        if (VOS_TRUE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(&pstPlmnInfo->stPlmnWithRat,
                               pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_DPLMN;
        }

        /* �ж������Ƿ���UPLMN */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithUplmn(&pstPlmnInfo->stPlmnWithRat))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_UPLMN;
        }

        /* �ж������Ƿ���OPLMN */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithOplmn(&pstPlmnInfo->stPlmnWithRat))
        {
            return NAS_MMC_ROAM_PLMN_TYPE_OPLMN;
        }
    }

    return NAS_MMC_ROAM_PLMN_TYPE_AVAIL_PLMN;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRoamPlmnPrio
 ��������  : ��ȡ����PLMN�����ȼ���Ϣ
 �������  : NAS_MMC_ROAM_PLMN_INFO_STRU        *pstRoamPlmnInfo������PLMN
 �������  : ��
 �� �� ֵ  : VOS_UINT32�����ȼ���Ӧ����ֵ��ȡֵ��ΧΪ[0,5]��ֵԽ�����ȼ�Խ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��9��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_GetRoamPlmnPrio(
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstRoamPlmnInfo
)
{
    NAS_MMC_ROAM_PLMN_TYPE_ENUM_UINT8             enRoamPlmnType;
    NAS_MMC_ROAM_PLMN_PRIO_ENUM_UINT8             enRoamPlmnPrio;

    enRoamPlmnType      = NAS_MMC_GetRoamPlmnType(pstRoamPlmnInfo);

    if (VOS_FALSE == NAS_MMC_GetSrchUOplmnPriorToDplmnFlg())
    {
        return enRoamPlmnType;
    }

    switch(enRoamPlmnType)
    {
        case NAS_MMC_ROAM_PLMN_TYPE_UPLMN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_UPLMN;
            break;

        case NAS_MMC_ROAM_PLMN_TYPE_OPLMN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_OPLMN;
            break;

        case NAS_MMC_ROAM_PLMN_TYPE_DPLMN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_DPLMN;
            break;

        case NAS_MMC_ROAM_PLMN_TYPE_AVAIL_PLMN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_AVAIL_PLMN;
            break;

        case NAS_MMC_ROAM_PLMN_TYPE_NPLMN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_NPLMN;
            break;

        case NAS_MMC_ROAM_PLMN_TYPE_FORBIDDEN:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_FORBIDDEN;
            break;

        default:
            enRoamPlmnPrio = NAS_MMC_ROAM_PLMN_PRIO_FORBIDDEN;
            break;
    }

    return enRoamPlmnPrio;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareRoamPlmnPrio
 ��������  : �Ƚ�����plmn���ȼ�
 �������  : pPlmn1Info - ��һ��plmn��Ϣ
             pPlmn2Info - �ڶ���plmn��Ϣ
 �������  : ��
 �� �� ֵ  : 1 - ��һ��plmn���ȼ����ڵڶ���plmn
             0 - ��һ��plmn���ȼ����ڵڶ���plmn
            -1 - ��һ��plmn���ȼ����ڵڶ���plmn
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��9��
    ��    ��   : l00289540
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
*****************************************************************************/
VOS_INT32  NAS_MMC_CompareRoamPlmnPrio(
    const VOS_VOID                  *pPlmn1Info,
    const VOS_VOID                  *pPlmn2Info,
    NAS_MML_PLMN_RAT_PRIO_STRU      *pstPrioRatList
)
{
    NAS_MMC_ROAM_PLMN_INFO_STRU                            *pstFirstPlmnInfo;
    NAS_MMC_ROAM_PLMN_INFO_STRU                            *pstSecondPlmnInfo;
    VOS_UINT8                                               ucFirstRoamPlmnPrio;
    VOS_UINT8                                               ucSecondRoamPlmnPrio;
    VOS_UINT8                                               i;
    VOS_UINT8                                               ucFirstPlmnRatIndex;
    VOS_UINT8                                               ucSecondPlmnRatIndex;

    pstFirstPlmnInfo         = (NAS_MMC_ROAM_PLMN_INFO_STRU *)pPlmn1Info;
    pstSecondPlmnInfo        = (NAS_MMC_ROAM_PLMN_INFO_STRU *)pPlmn2Info;
    ucFirstRoamPlmnPrio      = NAS_MMC_GetRoamPlmnPrio(pstFirstPlmnInfo);
    ucSecondRoamPlmnPrio     = NAS_MMC_GetRoamPlmnPrio(pstSecondPlmnInfo);
    ucFirstPlmnRatIndex      = 0;
    ucSecondPlmnRatIndex     = 0;

    /* �Ƚ�����plmn�����ȼ���plmn typeԽ�����ȼ�Խ�� */
    if (ucFirstRoamPlmnPrio > ucSecondRoamPlmnPrio)
    {
        return 1;
    }

    if (ucFirstRoamPlmnPrio < ucSecondRoamPlmnPrio)
    {
        return -1;
    }

    /* �������plmn���ȼ���ͬ���ٱȽ�����״̬�����ڵ��������ȼ���,
       ��������״̬����Ϊ���ȼ��Ƚ����� */
    if ((NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstFirstPlmnInfo->enNetStatus)
     && (NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstSecondPlmnInfo->enNetStatus))
    {
        return 0;
    }

    if (NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstFirstPlmnInfo->enNetStatus)
    {
        return 1;
    }

    if (NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstSecondPlmnInfo->enNetStatus)
    {
        return -1;
    }

    /* ��һ��plmn�͵ڶ���plmn��ͬʱ�ſ��ǽ��뼼�����ȼ�*/
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstFirstPlmnInfo->stPlmnWithRat.stPlmnId, &pstSecondPlmnInfo->stPlmnWithRat.stPlmnId))
    {
        for (i = 0; i < pstPrioRatList->ucRatNum; i++)
        {
            if (pstFirstPlmnInfo->stPlmnWithRat.enRat == pstPrioRatList->aucRatPrio[i])
            {
                ucFirstPlmnRatIndex = i;
            }

            if (pstSecondPlmnInfo->stPlmnWithRat.enRat == pstPrioRatList->aucRatPrio[i])
            {
                ucSecondPlmnRatIndex = i;
            }
        }

        /* ��һ��plmn���뼼�����ȣ��������ȼ��� */
        if (ucFirstPlmnRatIndex < ucSecondPlmnRatIndex)
        {
            return 1;
        }

        if (ucSecondPlmnRatIndex < ucFirstPlmnRatIndex)
        {
            return -1;
        }
    }

    return 0;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList
 ��������  : ������õ�roam�����б���������б�
 �������  : pstNewRoamPlmnSelectionList - ��Ҫ���������б���Ϣ
 �������  : pstPlmnSrchList - �����б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��29��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��7��9��
   ��    ��   : z00161729
   �޸�����   : DTS2015071001632:�������������������������������ȫ���ǽ�ֹ�����ȫ��nplmn�У�
               ����ڹ�������������б�Ϊ0����0��1�����ȫF�Ĵ���������ѭ�������帴λ

*****************************************************************************/
VOS_VOID NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stInsertPlmnInfo;
    VOS_UINT16                                              usSimRat;
    VOS_INT32                                               i;

    PS_MEM_SET(&stInsertPlmnInfo, 0, sizeof(stInsertPlmnInfo));
    i = 0;

    if (0 == pstNewRoamPlmnSelectionList->usSearchPlmnNum)
    {
        return;
    }

    /* ������˳��ӵ͵��߲��������б�ͷ�� */
    for (i = pstNewRoamPlmnSelectionList->usSearchPlmnNum - 1; i >= 0 ; i--)
    {
        usSimRat = NAS_MMC_ConvertNetRatToSimRat(pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].stPlmnWithRat.enRat);

        NAS_MMC_BuildPlmnSelectionPlmnInfo(
              pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].enPlmnType,
              usSimRat,
              &pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId,
              &stInsertPlmnInfo);

        (VOS_VOID)NAS_MMC_InsertPlmnInPlmnSelectionList(&stInsertPlmnInfo,
                 pstPlmnSrchList, 0);

        /* ���roam�����б�������״̬�ǲ�Ϊno searched����Ҫ�������������б�������״̬���������б��Ӧ����״̬��
           Ĭ��NAS_MMC_BuildPlmnSelectionPlmnInfo����������״̬��δ����״̬ */
        if (NAS_MMC_NET_STATUS_NO_SEARCHED != pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].enNetStatus)
        {
            NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].stPlmnWithRat,
                                               pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].enNetStatus,
                                               pstPlmnSrchList);
        }
    }

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail
 ��������  : ��rrc search cnfʧ����Ϣ�л�ȡ���ڵ�����������Ϣ
 �������  : enRat         - ���뼼��
             pstPlmnIdList - rrc search cnfʧ����Ϣ�д�������������Ϣ
 �������  : pstSearchedExistPlmnInfo - ���������б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��1��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnIdList,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo
)
{
    VOS_UINT32                                             i;
    VOS_UINT32                                             ulPlmnNum;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                           enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                 *pstPlmnSrchList   = VOS_NULL_PTR;

     /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* �������������*/
    for (i = 0; i < pstPlmnIdList->ulHighPlmnNum; i++)
    {
        ulPlmnNum = pstSearchedExistPlmnInfo->usSearchPlmnNum;

        if (ulPlmnNum >= NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST)
        {
            return;
        }

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.stPlmnId = pstPlmnIdList->astHighPlmnList[i];
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.enRat    = enRat;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[0]              = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[1]              = NAS_MML_LAC_HIGH_BYTE_INVALID;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus            = NAS_MMC_NET_STATUS_SEARCHED_EXIST;

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus  =  NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus)
        {
            pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        }

        enPlmnType = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enPlmnType  = enPlmnType;
        pstSearchedExistPlmnInfo->usSearchPlmnNum++;
    }

    /* ����ѵ���������*/
    for (i = 0; i < pstPlmnIdList->ulLowPlmnNum; i++)
    {
        ulPlmnNum = pstSearchedExistPlmnInfo->usSearchPlmnNum;

        if (ulPlmnNum >= NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST)
        {
            return;
        }

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.stPlmnId = pstPlmnIdList->astLowPlmnList[i].stPlmnId;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.enRat    = enRat;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[0]              = NAS_MML_LAC_LOW_BYTE_INVALID;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[1]              = NAS_MML_LAC_HIGH_BYTE_INVALID;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus            = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        enPlmnType = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enPlmnType  = enPlmnType;
        pstSearchedExistPlmnInfo->usSearchPlmnNum++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildSearchedPlmnInfoByLteSearchedPlmnInfoInd
 ��������  : ����lte��searched plmn info ind��Ϣ�д�������������ȡ
             NAS_MMC_ROAM_PLMN_LIST_INFO_STRU�ṹ���͵����������б�
 �������  : pstLteSearchedPlmnInfo - lte��searched plmn info ind��Ϣ����
 �������  : pstSearchedExistPlmnInfo - �����б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��1��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_BuildSearchedPlmnInfoByLteSearchedPlmnInfoInd(
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU                    *pstLteSearchedPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo
)
{
    VOS_UINT32                                             i;
    VOS_UINT32                                             ulPlmnNum;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                           enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                 *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   stGuNasPlmn;

    /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulPlmnNum       = 0;
    i               = 0;
    enPlmnType      = NAS_MMC_PLMN_TYPE_BUTT;
    PS_MEM_SET(&stGuNasPlmn, 0, sizeof(stGuNasPlmn));


    /*  �����ڵ��������roam�����б� */
    for (i = 0; i < pstLteSearchedPlmnInfo->ulTaiNum; i++)
    {
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&pstLteSearchedPlmnInfo->stTaiList[i].stPlmnId,
                                            &stGuNasPlmn);

        ulPlmnNum = pstSearchedExistPlmnInfo->usSearchPlmnNum;

        if (ulPlmnNum >= NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST)
        {
            return;
        }

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.stPlmnId = stGuNasPlmn;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[0]              = pstLteSearchedPlmnInfo->stTaiList[i].stTac.ucTac;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[1]              = pstLteSearchedPlmnInfo->stTaiList[i].stTac.ucTacCnt;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus  =  NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus)
        {
            pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        }

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.enRat    = NAS_MML_NET_RAT_TYPE_LTE;

        enPlmnType = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enPlmnType  = enPlmnType;
        pstSearchedExistPlmnInfo->usSearchPlmnNum++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildSearchedPlmnInfoByRrcSearchedPlmnInfoInd
 ��������  : ��RRMM_SEARCHED_PLMN_INFO_IND��Ϣ�д����������簴
             NAS_MMC_ROAM_PLMN_INFO_STRU�ṹ��ȡ��NAS_MMC_ROAM_PLMN_LIST_INFO_STRU�б���
 �������  : pstSearchedPlmnInfoMsg   - rrmm searched plmn info ind��Ϣ����
 �������  : pstSearchedExistPlmnInfo - �������������б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��1��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_BuildSearchedPlmnInfoByRrcSearchedPlmnInfoInd(
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU   *pstSearchedExistPlmnInfo
)
{
    VOS_UINT32                                             i;
    VOS_UINT32                                             ulPlmnNum;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                           enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                 *pstPlmnSrchList   = VOS_NULL_PTR;
    RRC_NAS_RAT_TYPE_ENUM_UINT32                           enRrcRatType;
    NAS_MMC_NET_STATUS_ENUM_UINT8                          enNetStatus;

    enPlmnType   = NAS_MMC_PLMN_TYPE_BUTT;
    ulPlmnNum    = 0;
    enRrcRatType = RRC_NAS_RAT_TYPE_BUTT;
    i            = 0;

    /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    for (i = 0; i < pstSearchedPlmnInfoMsg->ulAvailPlmnNum; i++)
    {
        ulPlmnNum = pstSearchedExistPlmnInfo->usSearchPlmnNum;

        if (ulPlmnNum >= NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST)
        {
            return;
        }

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.stPlmnId.ulMcc = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].stPlmnId.ulMcc;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.stPlmnId.ulMnc = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].stPlmnId.ulMnc;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[0]              = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].usLac & 0x00FF;
        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].aucLac[1]              = (pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].usLac & 0xFF00) >> 8;

        enRrcRatType = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].ulRat;
        NAS_MMC_ConvertRrcRatToNasFormat(enRrcRatType, &pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat.enRat);

        /* ������״̬��Ҫ���ܵ������б����Ȳ�ѯ�£����״̬�Ѿ���register��
           ���²���ʱ��Ҫʹ�������б���״̬������Ĭ�ϸ���Ϊsearched exist����ᵼ�¶������*/
        enNetStatus = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED == enNetStatus)
        {
            pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_REGISTERED;
        }
        else
        {
            pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        }

        enPlmnType = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].stPlmnWithRat, pstPlmnSrchList);

        pstSearchedExistPlmnInfo->astPlmnSelectionList[ulPlmnNum].enPlmnType  = enPlmnType;
        pstSearchedExistPlmnInfo->usSearchPlmnNum++;
    }

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnExistInRoamPlmnList
 ��������  : �ж�plmn�Ƿ������������б���
 �������  : pstPlmnId            - ������Ϣ
             pstNewRoamPlmnSelectionList - ���������б�
 �� �� ֵ  : ��
 ���ú���  : VOS_TRUE  - ����
             VOS_FALSE - ������
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��1��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnExistInRoamPlmnList(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnId,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU   *pstNewRoamPlmnSelectionList
)
{
    VOS_UINT32                          i;

    for (i = 0; i < pstNewRoamPlmnSelectionList->usSearchPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstPlmnId->stPlmnId,
                      &pstNewRoamPlmnSelectionList->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildRoamPlmnSelectionPlmnInfo
 ��������  : ��������ѡ���б��е�������PLMN��Ϣ
 �������  : pstPlmnWithRat - ������Ϣ
 �������  : pstRoamPlmnInfo - ����plmn��Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_VOID NAS_MMC_BuildRoamPlmnSelectionPlmnInfo(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat,
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstPlmnInfo
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stRoamPlmnInfo;
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus;

    PS_MEM_SET(&stRoamPlmnInfo, 0, sizeof(stRoamPlmnInfo));

    pstPlmnSelectionList                        = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    stRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    stRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;
    stRoamPlmnInfo.stPlmnWithRat.enRat          = pstPlmnWithRat->enRat;

    /* ������״̬��Ҫ���ܵ������б����Ȳ�ѯ�£����״̬�Ѿ���searched no exist��register
       ��exist�����²���ʱ��Ҫʹ�������б���״̬������Ĭ�ϸ���Ϊno searched����ᵼ�¶������*/
    enNetStatus = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&stRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);

    if (NAS_MMC_NET_STATUS_BUTT != enNetStatus)
    {
        stRoamPlmnInfo.enNetStatus = enNetStatus;
    }
    else
    {
        stRoamPlmnInfo.enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
    }

    stRoamPlmnInfo.enPlmnType = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);
    stRoamPlmnInfo.aucLac[0]  = NAS_MML_LAC_LOW_BYTE_INVALID;
    stRoamPlmnInfo.aucLac[1]  = NAS_MML_LAC_HIGH_BYTE_INVALID;

    PS_MEM_CPY(pstPlmnInfo, &stRoamPlmnInfo, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SortRoamPlmnSelectionList
 ��������  : �����������б�����
 �������  : pstPrioRatList       - �������ȼ�
             ulRoamPlmnListNum    - �����б��������
 �������  : pstRoamPlmnList      - ���������б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��1��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��7��9��
   ��    ��   : z00161729
   �޸�����   : DTS2015071001632:�������������������������������ȫ���ǽ�ֹ�����ȫ��nplmn�У�
                ����ڹ�������������б�Ϊ0����0��1�����ȫF�Ĵ���������ѭ�������帴λ
*****************************************************************************/
VOS_VOID NAS_MMC_SortRoamPlmnSelectionList(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList,
    VOS_UINT32                          ulRoamPlmnListNum,
    NAS_MMC_ROAM_PLMN_INFO_STRU        *pstRoamPlmnList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT32                          ulHighPrioRoamPlmnIndex;
    NAS_MMC_ROAM_PLMN_INFO_STRU         stHighPrioRoamPlmnInfo;

    PS_MEM_SET(&stHighPrioRoamPlmnInfo, 0, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));

    if (0 == ulRoamPlmnListNum)
    {
        return;
    }

    for (i = 0; i < ulRoamPlmnListNum - 1; ++i)
    {
        ulHighPrioRoamPlmnIndex = i;

        for (j = i + 1; j < ulRoamPlmnListNum; ++j)
        {
            /* �޸ĺ����� */
            if (1 == NAS_MMC_CompareRoamPlmnPrio(&pstRoamPlmnList[j],&pstRoamPlmnList[ulHighPrioRoamPlmnIndex],pstPrioRatList))
            {
                ulHighPrioRoamPlmnIndex = j;
            }
        }

        PS_MEM_CPY(&stHighPrioRoamPlmnInfo, &pstRoamPlmnList[ulHighPrioRoamPlmnIndex],sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));
        PS_MEM_CPY(&pstRoamPlmnList[ulHighPrioRoamPlmnIndex], &pstRoamPlmnList[i],sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));
        PS_MEM_CPY(&pstRoamPlmnList[i], &stHighPrioRoamPlmnInfo, sizeof(NAS_MMC_ROAM_PLMN_INFO_STRU));
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddDplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo
 ��������  : ���ݽ����������Ĵ������磬��DPLMN List����SearchedExistPlmnͬ��һ�����ҵ�PLMN���뵽���������б�
 �������  : pstSearchedExistPlmnInfo    - ����������Ϣ
 �������  : pstNewRoamPlmnSelectionList - ���������б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��10��
   ��    ��   : l00289540
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddDplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stRoamPlmnInfo;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;

    pstDPlmnNPlmnCfgInfo     = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    i                        = 0;
    j                        = 0;

    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));
    PS_MEM_SET(&stRoamPlmnInfo, 0, sizeof(stRoamPlmnInfo));

    /* ���TAF_MMA_GetNetworkNameTblAddr����Ϣ��ȫ��DPLMN�е����粻��
       TAF_MMA_GetNetworkNameTblAddr�У�����DPLMNû�м��������б���������ȼ���DPLMN������*/
    for (i = 0; i < pstSearchedExistPlmnInfo->usSearchPlmnNum; i++)
    {
        for (j = 0; j < pstDPlmnNPlmnCfgInfo->usDplmnListNum; j++)
        {
            stPlmnWithRat.stPlmnId.ulMcc = pstDPlmnNPlmnCfgInfo->astDPlmnList[j].stSimPlmnWithRat.stPlmnId.ulMcc;
            stPlmnWithRat.stPlmnId.ulMnc = pstDPlmnNPlmnCfgInfo->astDPlmnList[j].stSimPlmnWithRat.stPlmnId.ulMnc;
            stPlmnWithRat.enRat = NAS_MMC_ConvertSimRatToNetRat(pstDPlmnNPlmnCfgInfo->astDPlmnList[j].stSimPlmnWithRat.usSimRat);

            if (VOS_TRUE == NAS_MML_IsPlmnMccBelongToTheSameCountry(stPlmnWithRat.stPlmnId.ulMcc,
                                                pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId.ulMcc))
            {
                if (VOS_TRUE == NAS_MMC_IsPlmnExistInRoamPlmnList(&stPlmnWithRat, pstNewRoamPlmnSelectionList))
                {
                    continue;
                }

                if (NAS_MML_NET_RAT_TYPE_BUTT != stPlmnWithRat.enRat)
                {
                    NAS_MMC_BuildRoamPlmnSelectionPlmnInfo(&stPlmnWithRat, &stRoamPlmnInfo);
                    NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList(&stRoamPlmnInfo, pstNewRoamPlmnSelectionList);
                }
            }
        }
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddUOplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo
 ��������  : ���ݽ����������Ĵ������磬��UPLMN/OPLMN L List����SearchedExistPlmnͬ��һ�����ҵ�PLMN���뵽���������б�
 �������  : pstSearchedExistPlmnInfo    - ����������Ϣ
 �������  : pstNewRoamPlmnSelectionList - ���������б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��10��
   ��    ��   : l00289540
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddUOplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stRoamPlmnInfo;
    VOS_UINT32                                              i = 0;
    VOS_UINT32                                              j = 0;
    VOS_UINT32                                              k = 0;

    pstPlmnSelectionList     = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));
    PS_MEM_SET(&stRoamPlmnInfo, 0, sizeof(stRoamPlmnInfo));

    /* ���TAF_MMA_GetNetworkNameTblAddr����Ϣ��ȫ��UPLMN/OPLMN�е����粻��
     * TAF_MMA_GetNetworkNameTblAddr�У�����UPLMN/OPLMNû�м��������б���������ȼ���UPLMN/OPLMN������*/
    for (i = 0; i < pstSearchedExistPlmnInfo->usSearchPlmnNum; i++)
    {
        for (j = 0; j < pstPlmnSelectionList->usSearchPlmnNum; j++)
        {
            if ((NAS_MMC_PLMN_TYPE_UPLMN == pstPlmnSelectionList->astPlmnSelectionList[j].enPlmnType)
             || (NAS_MMC_PLMN_TYPE_OPLMN == pstPlmnSelectionList->astPlmnSelectionList[j].enPlmnType))
            {
                stPlmnWithRat.stPlmnId.ulMcc = pstPlmnSelectionList->astPlmnSelectionList[j].stPlmnId.ulMcc;
                stPlmnWithRat.stPlmnId.ulMnc = pstPlmnSelectionList->astPlmnSelectionList[j].stPlmnId.ulMnc;

                if (VOS_TRUE == NAS_MML_IsPlmnMccBelongToTheSameCountry(stPlmnWithRat.stPlmnId.ulMcc,
                                                pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId.ulMcc))
                {
                    if (VOS_TRUE == NAS_MMC_IsPlmnExistInRoamPlmnList(&stPlmnWithRat, pstNewRoamPlmnSelectionList))
                    {
                        continue;
                    }

                    for(k = 0; k< pstPlmnSelectionList->astPlmnSelectionList[j].ucRatNum; k++)
                    {
                        stPlmnWithRat.enRat          = pstPlmnSelectionList->astPlmnSelectionList[j].astPlmnRatInfo[k].enRatType;

                        if (NAS_MML_NET_RAT_TYPE_BUTT != stPlmnWithRat.enRat)
                        {
                            NAS_MMC_BuildRoamPlmnSelectionPlmnInfo(&stPlmnWithRat, &stRoamPlmnInfo);
                            NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList(&stRoamPlmnInfo, pstNewRoamPlmnSelectionList);
                        }
                    }
                }
            }
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddOtherPlmnToRoamPlmnSelectionListBySearchedExistPlmnInfo
 ��������  : ���ݽ����������Ĵ������磬��TAF_MMA_GetNetworkNameTblAddr����SearchedExistPlmn
             ͬ��һ��������δ�����������б��ڵ�PLMN���뵽�б���
 �������  : pstSearchedExistPlmnInfo    - ����������Ϣ
 �������  : pstNewRoamPlmnSelectionList - ���������б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��10��
   ��    ��   : l00289540
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddOtherPlmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
)
{
    TAF_PH_OPERATOR_NAME_TBL_STRU                          *pstNetworkNameTbl = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stRoamPlmnInfo;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    VOS_UINT16                                              usTotalNtwkNum;
    VOS_UINT8                                               ucPlmnMncNum;
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;

    usTotalNtwkNum           = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl        = TAF_MMA_GetNetworkNameTblAddr();
    i                        = 0;
    j                        = 0;
    ucPlmnMncNum             = 0;
    PS_MEM_SET(&stPlmnWithRat, 0, sizeof(stPlmnWithRat));
    PS_MEM_SET(&stRoamPlmnInfo, 0, sizeof(stRoamPlmnInfo));

    /* ���Һʹ���������ͬ�����������plmn������roam�����б��������������б� */
    for (i = 0; i < pstSearchedExistPlmnInfo->usSearchPlmnNum; i++)
    {
        for (j = 0; j < usTotalNtwkNum; j++)
        {
            stPlmnWithRat.stPlmnId.ulMcc = pstNetworkNameTbl[j].PlmnId.Mcc;
            stPlmnWithRat.stPlmnId.ulMnc = pstNetworkNameTbl[j].PlmnId.Mnc;
            stPlmnWithRat.enRat          = pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.enRat;

            ucPlmnMncNum = pstNetworkNameTbl[j].ucMncLength;
            NAS_MMC_ConvertPlmnId2NasFormat(&stPlmnWithRat.stPlmnId,ucPlmnMncNum);

            if (VOS_TRUE == NAS_MML_IsPlmnMccBelongToTheSameCountry(stPlmnWithRat.stPlmnId.ulMcc,
                                            pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId.ulMcc))
            {
                if (VOS_TRUE == NAS_MMC_IsPlmnExistInRoamPlmnList(&stPlmnWithRat, pstNewRoamPlmnSelectionList))
                {
                    continue;
                }

                NAS_MMC_BuildRoamPlmnSelectionPlmnInfo(&stPlmnWithRat, &stRoamPlmnInfo);
                NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList(&stRoamPlmnInfo, pstNewRoamPlmnSelectionList);
            }
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo
 ��������  : ���ݽ����������Ĵ������繹�����������б�
 �������  : enRat                       - ���뼼��
             pstSearchedExistPlmnInfo    - ����������Ϣ
 �������  : pstNewRoamPlmnSelectionList - ���������б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��1��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��10��9��
   ��    ��   : l00289540
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0 �޸�
 3.��    ��   : 2016��1��5��
   ��    ��   : s00217060
   �޸�����   : DTS2015120406613:����ʱֻ��ϲ�����

*****************************************************************************/
VOS_VOID NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstNewRoamPlmnSelectionList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    i                        = 0;
    PS_MEM_SET(&stPrioRatList, 0, sizeof(stPrioRatList));

    /*  �����ڵ��������roam�����б���ǰ�� */
    for (i = 0; i < pstSearchedExistPlmnInfo->usSearchPlmnNum; i++)
    {
        NAS_MMC_AddSearchedPlmnInRoamPlmnSelectionList(&pstSearchedExistPlmnInfo->astPlmnSelectionList[i], pstNewRoamPlmnSelectionList);
    }

    if (VOS_TRUE == NAS_MMC_GetSrchUOplmnPriorToDplmnFlg())
    {
        NAS_MMC_AddUOplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);

        NAS_MMC_AddDplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);

        NAS_MMC_AddOtherPlmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);
    }
    else
    {
        NAS_MMC_AddDplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);

        NAS_MMC_AddUOplmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);

        NAS_MMC_AddOtherPlmnToRoamPlmnSelectionListBySearchedExistPlmnInfo(pstSearchedExistPlmnInfo, pstNewRoamPlmnSelectionList);
    }

    /* ����ʱ�����б���������������DPLMNǰ������UPLMN/OPLMN���Դ򿪣�������ԭ��Ϊ:DPLMN->UPLMN->OPLMN->AVAILABLE
     * ��������ԭ��Ϊ:UPLMN->OPLMN->DPLMN->AVAILABLE
     */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* ��ѡ���б������ӽ���㱨���������磬��ǰ�������뼼������ */
    NAS_MML_SortSpecRatPrioHighest(enRat, &stPrioRatList);

    NAS_MMC_SortRoamPlmnSelectionList(&stPrioRatList, pstNewRoamPlmnSelectionList->usSearchPlmnNum,
                  pstNewRoamPlmnSelectionList->astPlmnSelectionList);

    /* ����֮�����Ϊ0ʱ�����쳣��ӡ */
    if (0 == pstNewRoamPlmnSelectionList->usSearchPlmnNum)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo: usSearchPlmnNum is 0");
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList
 ��������  : ���������б���ָ��PLMN������״̬��Ϣ
 �������  : pstPlmn
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmn,
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                             i;

    /* ����PLMN������뼼���������б���ÿ��PLMN������뼼���Ƚ� */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        /* �Ƚ�pstPlmn->stPlmnId,��pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId */
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmn->stPlmnId),
                                                           &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId)))
        {
            /* �����ͬ�����������б���PLMN��Ӧ���뼼������Ϣ */
            NAS_MMC_UpdateRatNetStatusInPlmnRatInfo(pstPlmn->enRat,
                                                    enNetStatus,
                                                    &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]));
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSpecQualAvailPlmnInPlmnSelectionList
 ��������  : ��ȡ�����б�������Ϊavailable�Ķ�Ӧ��������
 �������  : pstPlmnSelectionList,�б���Ϣ
             enPlmnQuality,Ҫ��ȡ���������
 �������  : pstPlmnSelectionList,�б���Ϣ
             pstAvailPlmnList,��ȡ��洢���б�
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��19��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��8��28��
   ��    ��   : z00161729
   �޸�����   : available������������ڴ治�㣬�ᵼ�¿���Խ�絥�帴λ
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetSpecQualAvailPlmnInPlmnSelectionList(
    VOS_UINT32                                              ulAvailPlmnListNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstAvailPlmnList,
    NAS_MMC_NET_QUALITY_ENUM_UINT8                          enPlmnQuality,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulPlmnNum;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnSelectionPlmnInfo = VOS_NULL_PTR;

    ulPlmnNum = 0x0;

    /* �������б�������ΪAVAIL�ź�����ΪenPlmnQuality�������ҳ� */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        pstPlmnSelectionPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);

        if (NAS_MMC_PLMN_TYPE_AVAIL_PLMN == pstPlmnSelectionPlmnInfo->enPlmnType)
        {
            /* ѭ���������еĽ��뼼�����ҳ���Ӧ���뼼������ΪenPlmnQuality������ */
            for (j = 0; j < pstPlmnSelectionPlmnInfo->ucRatNum; j++)
            {
                if (enPlmnQuality == pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enQuality)
                {
                    /* ��ʼ��ѡ����Ϣ */
                    NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                       NAS_MML_INVALID_SIM_RAT,
                                                       &(pstPlmnSelectionPlmnInfo->stPlmnId),
                                                       &(pstAvailPlmnList[ulPlmnNum]));

                    /* ��ȡ��PLMN�����Ϣ */
                    PS_MEM_CPY(&pstAvailPlmnList[ulPlmnNum].astPlmnRatInfo[0],
                               &(pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j]),
                               sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));

                    pstAvailPlmnList[ulPlmnNum].ucRatNum++;

                    ulPlmnNum ++;

                    if (ulPlmnNum >= ulAvailPlmnListNum)
                    {
                       return ulPlmnNum;
                    }
                }
            }
        }
    }

    return ulPlmnNum;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SortRatPrioSpecRat
 ��������  : ����һ������ָ�����뼼�������ڵڶ���֮ǰ
 �������  : enPrioRat
             enRat
 �������  : pstPrioRatList,���뼼������˳��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��19��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SortRatPrioSpecRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enPrioRat,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulPrioRatIndex;
    VOS_UINT32                          ulRatIndex;
    VOS_UINT32                          ulFoundPrioRatFlg;
    VOS_UINT32                          ulFoundRatFlg;

    ulPrioRatIndex    = 0x0;
    ulRatIndex        = 0x0;

    ulFoundPrioRatFlg = VOS_FALSE;
    ulFoundRatFlg     = VOS_FALSE;

    /* �ҳ����Ƚ��뼼���ͷ����Ƚ��뼼����λ�� */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        if (enPrioRat == pstPrioRatList->aucRatPrio[i])
        {
            ulPrioRatIndex    = i;
            ulFoundPrioRatFlg = VOS_TRUE;
        }

        if (enRat == pstPrioRatList->aucRatPrio[i])
        {
            ulRatIndex        = i;
            ulFoundRatFlg     = VOS_TRUE;
        }
    }

    /* �����ǰ��֧�����Ƚ��뼼��,����Ҫ���� */
    if ((VOS_FALSE == ulFoundPrioRatFlg)
     || (VOS_FALSE == ulFoundRatFlg))
    {
        return;
    }

    /* ���ǰ�����ȼ��ͣ���Ҫ�����������ȵ��Ƶ�ǰ�� */
    if (ulPrioRatIndex > ulRatIndex)
    {
        (VOS_VOID)PS_MEM_MOVE(&(pstPrioRatList->aucRatPrio[ulRatIndex+1]),
                    &(pstPrioRatList->aucRatPrio[ulRatIndex]),
                    (ulPrioRatIndex-ulRatIndex)*sizeof(NAS_MML_NET_RAT_TYPE_ENUM_UINT8));

        pstPrioRatList->aucRatPrio[ulRatIndex] = enPrioRat;
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SortPlmnListRandom
 ��������  : �������б���PLMN�����������
 �������  : pstPlmnSelectionList,�б���Ϣ
             ulPlmnNum,PLMN����
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��19��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��5��20��
   ��    ��   : s00217060
   �޸�����   : coverity��foritfy�޸�

*****************************************************************************/
VOS_VOID NAS_MMC_SortPlmnListRandom(
    VOS_UINT32                                              ulPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnList
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU  stTempPlmnInfo;
    VOS_UINT32                             ulPlmnListNum;
    VOS_UINT32                             ulRand;

    ulPlmnListNum = ulPlmnNum;

    /* Modified by s00217060 for coverity��foritfy�޸� , 2013-05-20, begin */
    /* ������� */
    VOS_SetSeed(VOS_GetTick());

    for (; ulPlmnListNum > 1; ulPlmnListNum--)
    {
        /* ��ȡ����� */
        ulRand = VOS_Rand(ulPlmnListNum);
        if (ulRand >  (ulPlmnListNum - 1))
        {
            continue;
        }

        stTempPlmnInfo               = pstPlmnList[ulRand];
        pstPlmnList[ulRand]          = pstPlmnList[ulPlmnListNum-1];
        pstPlmnList[ulPlmnListNum-1] = stTempPlmnInfo;
    }
    /* Modified by s00217060 for coverity��foritfy�޸� , 2013-05-20, end */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SortPlmnListPrioRat
 ��������  : �������б���PLMN�����뼼������˳������
 �������  : pstPlmnSelectionList,�б���Ϣ
             *pulPlmnNum,PLMN����
             pstPrioRatList,ָ���Ľ��뼼������˳��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��19��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SortPlmnListPrioRat(
    VOS_UINT32                                             *pulPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnList,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulTmpPlmnNum;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstTmpPlmnList = VOS_NULL_PTR;

    /* PlmnNum����Ϊ0ʱ���������� */
    if (0 == (*pulPlmnNum))
    {
        return;
    }

    pstTmpPlmnList = (NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   ((*pulPlmnNum)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU)));

    if (VOS_NULL_PTR == pstTmpPlmnList)
    {
        /* ��ӡ�쳣 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SortPlmnListPrioRat: Mem alloc fail.");

        return;
    }

    ulTmpPlmnNum = 0x0;

    /*���򷽷���,ѭ�����еĽ��뼼��,��������ȼ��Ľ��뼼������ŵ����һ����ѭ����֤�����
      �ȼ����뼼�������綼����ǰ�棬���Ŷ����������������ͬ��ʽ���� */
    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        for (j = 0; j < (*pulPlmnNum); j++)
        {
            if (pstPrioRatList->aucRatPrio[i] == pstPlmnList[j].astPlmnRatInfo[0].enRatType)
            {
                PS_MEM_CPY(&pstTmpPlmnList[ulTmpPlmnNum], &pstPlmnList[j], sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
                ulTmpPlmnNum++;
            }
        }
    }

    *pulPlmnNum = ulTmpPlmnNum;

    PS_MEM_CPY(pstPlmnList, pstTmpPlmnList, (ulTmpPlmnNum*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU)));

    PS_MEM_FREE(WUEPS_PID_MMC, pstTmpPlmnList);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SortPlmnListSignalDecrease
 ��������  : �������б���PLMN���źŵݼ�����
 �������  : pstPlmnSelectionList,�б���Ϣ
             ulPlmnNum,PLMN����
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��19��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SortPlmnListSignalDecrease(
    VOS_UINT32                                              ulPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnList
)
{
    /* ��ͬ���뼼����������׼��һ�£���δȷ�����򷽷� */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SortAvailPlmnInPlmnSelectionList
 ��������  : �������б��иߵ�������available plmn��������
 �������  : pstPlmnSelectionList,�б���Ϣ
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ:ʹ��NV�滻NAS_FEATURE_SUPPORT_H3G_REQ��
 3.��    ��   : 2013��12��13��
   ��    ��   : z00161729
   �޸�����   : DTS2013121206933:�Ǹ����ȼ����øߵ����������簴syscfg���ý��뼼�����ȼ�����9055 nv�����

*****************************************************************************/
VOS_VOID NAS_MMC_SortAvailPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstHighQualityAvailPlmnList  = VOS_NULL_PTR;
    VOS_UINT32                             ulHighQualityAvailPlmnNum;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstLowQualityAvailPlmnList   = VOS_NULL_PTR;
    VOS_UINT32                             ulLowQualityAvailPlmnNum;
    NAS_MML_PLMN_RAT_PRIO_STRU             stPrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU            *pstPrioRatList;

    VOS_UINT32                             ulAvailPlmnListNum;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU   *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    ulAvailPlmnListNum = NAS_MML_MAX_RAT_NUM * RRC_MAX_HIGH_PLMN_NUM;

    pstHighQualityAvailPlmnList = (NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   (NAS_MML_MAX_RAT_NUM*RRC_MAX_HIGH_PLMN_NUM)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstHighQualityAvailPlmnList)
    {
        /* ��ӡ�쳣 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SortAvailPlmnInPlmnSelectionList: Mem alloc fail.");

        return;
    }

    pstLowQualityAvailPlmnList  = (NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   (NAS_MML_MAX_RAT_NUM*RRC_MAX_HIGH_PLMN_NUM)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

    if (VOS_NULL_PTR == pstLowQualityAvailPlmnList)
    {
        /* ��ӡ�쳣 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SortAvailPlmnInPlmnSelectionList: Mem alloc fail.");

        PS_MEM_FREE(WUEPS_PID_MMC, pstHighQualityAvailPlmnList);

        return;
    }

    /* �������б�������ΪAvailabe����Ϊ�ߵ�PLMNȡ�� */
    ulHighQualityAvailPlmnNum = NAS_MMC_GetSpecQualAvailPlmnInPlmnSelectionList(ulAvailPlmnListNum,
                                                                            pstHighQualityAvailPlmnList,
                                                                            NAS_MMC_NET_HIGH_QUALITY,
                                                                            pstPlmnSelectionListInfo);

    /* �������б�������ΪAvailabe����Ϊ�͵�PLMNȡ�� */
    ulLowQualityAvailPlmnNum = NAS_MMC_GetSpecQualAvailPlmnInPlmnSelectionList(ulAvailPlmnListNum,
                                                                            pstLowQualityAvailPlmnList,
                                                                            NAS_MMC_NET_LOW_QUALITY,
                                                                            pstPlmnSelectionListInfo);


    /* �������б�������ΪAvailabe����Ϊ�ߵ�PLMNɾ�� */
    NAS_MMC_DeleteSpecQualAvailPlmnInPlmnSelectionList(NAS_MMC_NET_HIGH_QUALITY, pstPlmnSelectionListInfo);

    /* �������б�������ΪAvailabe����Ϊ�͵�PLMNɾ�� */
    NAS_MMC_DeleteSpecQualAvailPlmnInPlmnSelectionList(NAS_MMC_NET_LOW_QUALITY, pstPlmnSelectionListInfo);

    /* �Ը�����PLMN����������� */
    NAS_MMC_SortPlmnListRandom(ulHighQualityAvailPlmnNum, pstHighQualityAvailPlmnList);

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucWcdmaPriorityGsmFlg)
    {
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        stPrioRatList  = *pstPrioRatList;

        /* �� W�Ľ��뼼���ƶ��� G��ǰ�� */
        NAS_MMC_SortRatPrioSpecRat(NAS_MML_NET_RAT_TYPE_WCDMA,
                                   NAS_MML_NET_RAT_TYPE_GSM,
                                  &stPrioRatList);

        NAS_MMC_SortPlmnListPrioRat(&ulHighQualityAvailPlmnNum,
                                        pstHighQualityAvailPlmnList,
                                        &stPrioRatList);
    }
    else if (NAS_MMC_NV_ITEM_ACTIVE == pstMiscellaneousCfgInfo->ucSortAvailalePlmnListRatPrioFlg)
    {
        pstPrioRatList = NAS_MML_GetMsPrioRatList();
        stPrioRatList  = *pstPrioRatList;

        /* ���������簴syscfg�������ȼ����� */
        NAS_MMC_SortPlmnListPrioRat(&ulHighQualityAvailPlmnNum,
                                     pstHighQualityAvailPlmnList,
                                    &stPrioRatList);

        /* ���������簴syscfg�������ȼ����� */
        NAS_MMC_SortPlmnListPrioRat(&ulLowQualityAvailPlmnNum,
                                     pstLowQualityAvailPlmnList,
                                    &stPrioRatList);
    }
    else
    {
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    /* �Ե�����PLMN���а��źŵݼ����� */
    NAS_MMC_SortPlmnListSignalDecrease(ulLowQualityAvailPlmnNum, pstLowQualityAvailPlmnList);



    /* ��������PLMN�ٷŻ�ѡ���б� */
    NAS_MMC_SaveAvailablePlmnInPlmnSelectionList(ulHighQualityAvailPlmnNum,
                                                 pstHighQualityAvailPlmnList,
                                                 pstPlmnSelectionListInfo);

    /* ��������PLMN�ڷŻ������б� */
    NAS_MMC_SaveAvailablePlmnInPlmnSelectionList(ulLowQualityAvailPlmnNum,
                                                 pstLowQualityAvailPlmnList,
                                                 pstPlmnSelectionListInfo);

    PS_MEM_FREE(WUEPS_PID_MMC, pstHighQualityAvailPlmnList);

    PS_MEM_FREE(WUEPS_PID_MMC, pstLowQualityAvailPlmnList);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_DeleteEPlmnInPlmnSelectionList
 ��������  : �������б�������ΪenPlmnType������ɾ��
 �������  : enPlmnType
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                             i;

    i = 0;

    /* �������б�������ΪenPlmnType������ɾ�� */
    while (i < pstPlmnSelectionListInfo->usSearchPlmnNum)
    {
        if (enPlmnType == pstPlmnSelectionListInfo->astPlmnSelectionList[i].enPlmnType)
        {
            pstPlmnSelectionListInfo->usSearchPlmnNum--;

            (VOS_VOID)PS_MEM_MOVE(&pstPlmnSelectionListInfo->astPlmnSelectionList[i],
                        &pstPlmnSelectionListInfo->astPlmnSelectionList[i+1],
                        (pstPlmnSelectionListInfo->usSearchPlmnNum-i)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

            continue;
        }

        i++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_DeleteSpecQualAvailPlmnInPlmnSelectionList
 ��������  : ɾ��ָ��������Available����
 �������  : enNetQuality
 �������  : pstPlmnSelectionListInfo,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��28��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��8��26��
   ��    ��   : w00242748
   �޸�����   : DTS2013071808373����澯����
*****************************************************************************/
VOS_VOID NAS_MMC_DeleteSpecQualAvailPlmnInPlmnSelectionList(
    NAS_MMC_NET_QUALITY_ENUM_UINT8                          enNetQuality,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo = VOS_NULL_PTR;

    i = 0;

    /* �������б�������ΪAVAIL�ź�����ΪenNetQuality�������ҳ� */
    while (i < pstPlmnSelectionListInfo->usSearchPlmnNum)
    {
        pstPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);
        if (NAS_MMC_PLMN_TYPE_AVAIL_PLMN == pstPlmnInfo->enPlmnType)
        {
            j = 0;

            /* ѭ���������еĽ��뼼�����ҳ���Ӧ���뼼������ΪenPlmnQuality������ */
            while (j < pstPlmnInfo->ucRatNum)
            {
                if (enNetQuality == pstPlmnInfo->astPlmnRatInfo[j].enQuality)
                {
                    /* �������б��н���PLMN��Ӧ�Ľ��뼼����Ϣ��� */
                    pstPlmnInfo->ucRatNum --;

                    if (j < (NAS_MML_MAX_RAT_NUM - 1))
                    {
                        (VOS_VOID)PS_MEM_MOVE(&pstPlmnInfo->astPlmnRatInfo[j],
                                    &pstPlmnInfo->astPlmnRatInfo[j+1],
                                    (pstPlmnInfo->ucRatNum - j)*sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                    }

                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enRatType     = NAS_MML_NET_RAT_TYPE_BUTT;
                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enQuality     = NAS_MMC_NET_QUALITY_BUTT;
                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enNetStatus   = NAS_MMC_NET_STATUS_BUTT;

                    continue;
                }
                j++;
            }

            /* ɾ���������Ӧ���뼼����Ϣ������䲻֧���κν��뼼��������б���ɾ�������� */
            if (0 == pstPlmnInfo->ucRatNum)
            {
                pstPlmnSelectionListInfo->usSearchPlmnNum--;

                if (i < (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - 1))
                {
                    (VOS_VOID)PS_MEM_MOVE(&pstPlmnSelectionListInfo->astPlmnSelectionList[i],
                                &pstPlmnSelectionListInfo->astPlmnSelectionList[i+1],
                                (pstPlmnSelectionListInfo->usSearchPlmnNum - i)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
                }
                continue;
            }
        }

        i++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_DeleteSpecNetStatusAvailPlmnInPlmnSelectionList
 ��������  : ɾ��ָ������״̬������
 �������  : enNetStatus
 �������  : pstPlmnSelectionListInfo,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��5��22��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���:��������RPLMN:23002�ɹ���ע��ʧ��CS����17�ﵽ4�κ�,��ˢ��EPLMNʱ�򣬰����е�
                RPLMN��Ϣ������ˣ��������ѵ�23002���ַ���������
*****************************************************************************/
VOS_VOID NAS_MMC_DeleteSpecNetStatusAvailPlmnInPlmnSelectionList(
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo = VOS_NULL_PTR;

    i = 0;

    /* �������б�������ΪAVAIL,����״̬ΪNO SEARCHED�������ҳ� */
    while (i < pstPlmnSelectionListInfo->usSearchPlmnNum)
    {
        pstPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);
        if (NAS_MMC_PLMN_TYPE_AVAIL_PLMN == pstPlmnInfo->enPlmnType)
        {
            j = 0;

            /* ѭ���������еĽ��뼼�����ҳ�����״̬ΪNO SEARCHED�������ҳ� */
            while (j < pstPlmnInfo->ucRatNum)
            {
                if (enNetStatus == pstPlmnInfo->astPlmnRatInfo[j].enNetStatus)
                {
                    /* �������б��н���PLMN��Ӧ�Ľ��뼼����Ϣ��� */
                    pstPlmnInfo->ucRatNum --;

                    if (j < (NAS_MML_MAX_RAT_NUM - 1))
                    {
                        (VOS_VOID)PS_MEM_MOVE(&pstPlmnInfo->astPlmnRatInfo[j],
                                    &pstPlmnInfo->astPlmnRatInfo[j+1],
                                    (pstPlmnInfo->ucRatNum - j)*sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                    }

                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enRatType     = NAS_MML_NET_RAT_TYPE_BUTT;
                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enQuality     = NAS_MMC_NET_QUALITY_BUTT;
                    pstPlmnInfo->astPlmnRatInfo[pstPlmnInfo->ucRatNum].enNetStatus   = NAS_MMC_NET_STATUS_BUTT;

                    continue;
                }
                j++;
            }

            /* ɾ���������Ӧ���뼼����Ϣ������䲻֧���κν��뼼��������б���ɾ�������� */
            if (0 == pstPlmnInfo->ucRatNum)
            {
                pstPlmnSelectionListInfo->usSearchPlmnNum--;

                if (i < (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST - 1))
                {
                    (VOS_VOID)PS_MEM_MOVE(&pstPlmnSelectionListInfo->astPlmnSelectionList[i],
                                &pstPlmnSelectionListInfo->astPlmnSelectionList[i+1],
                                (pstPlmnSelectionListInfo->usSearchPlmnNum - i)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
                }

                continue;
            }
        }

        i++;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_DelSpecNetStatusRat
 ��������  : ��stPrioRatList��ɾ������״̬ΪenNetStatus�Ľ��뼼��
 �������  : enNetStatus  : ָ��Ҫɾ��������״̬����
              pstNetStatus : PLMNID������״̬
 �������  : stPrioRatList : ���뼼�����ȼ��б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��13��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_DelSpecNetStatusRat(
    NAS_MMC_NET_STATUS_ENUM_UINT8       enNetStatus,
    NAS_MMC_NET_STATUS_ENUM_UINT8      *pstNetStatus,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT32                          i;

    i = 0;

    /* �쳣���� */
    if (0x0 == pstPrioRatList->ucRatNum)
    {
        return;

    }

    /* �������״̬ΪenNetStatus���Ѹ�״̬�Ľ��뼼����stPrioRatList��ɾ�� */
    while (i < (VOS_UINT32)(pstPrioRatList->ucRatNum-1))
    {
        if (enNetStatus == pstNetStatus[i])
        {
            pstPrioRatList->aucRatPrio[i] = NAS_MML_NET_RAT_TYPE_BUTT;
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPrioRatList->aucRatPrio[i]),
                        &(pstPrioRatList->aucRatPrio[i+1]),
                        (NAS_MML_MAX_RAT_NUM-i-1));

            (VOS_VOID)PS_MEM_MOVE(&(pstNetStatus[i]),
                        &(pstNetStatus[i+1]),
                        (NAS_MML_MAX_RAT_NUM-i-1));
            /*lint +e961*/
            (pstPrioRatList->ucRatNum)--;

            continue;
        }
        i++;
    }

    /* ���һ���Ĵ��� */
    if ((pstPrioRatList->ucRatNum > 0)
     && (enNetStatus == pstNetStatus[i]))
    {
        pstPrioRatList->aucRatPrio[i] = NAS_MML_NET_RAT_TYPE_BUTT;

        (pstPrioRatList->ucRatNum)--;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ModifyPlmnTypeInPlmnSelectionList
 ��������  : ���������б�������ΪenSrcPlmnType�����磬�޸�������ΪenDestPlmnType
 �������  : enSrcPlmnType
             enDestPlmnType
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��6��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enSrcPlmnType,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enDestPlmnType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                             i;

    /* �������б�������ΪenSrcPlmnType������,�޸�������ΪenDestPlmnType */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        if (enSrcPlmnType == pstPlmnSelectionListInfo->astPlmnSelectionList[i].enPlmnType)
        {
            pstPlmnSelectionListInfo->astPlmnSelectionList[i].enPlmnType = enDestPlmnType;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextSearchPlmn
 ��������  : ��ȡ�����б���������ǰ��Ŀ�������������
 �������  : pstPlmnSelectionList,�б���Ϣ
             pstPrioRatList,���ȼ�˳��
             ulUserSpecPlmnSearch,�Ƿ��û�ָ������
 �������  : pstDestPlmn
 �� �� ֵ  : VOS_UINT32 VOS_TRUE :��ȡ�ɹ�
                        VOS_FALSE:��ȡʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextSearchPlmn(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstDestPlmn,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    VOS_UINT32                                              ulUserSpecPlmnSearch,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    VOS_UINT32                                              ulIsPlmnSearchingAllowed;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnSelectionPlmnInfo = VOS_NULL_PTR;

    /* ���β��������б��е�ÿһ������ */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        pstPlmnSelectionPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);

        /* ��SYSCFG���õĽ��뼼�����ȼ����β��� */
        for (k = 0; k < pstPrioRatList->ucRatNum; k++)
        {
            /* ���β���һ�����������֧�ֵĽ��뼼�� */
            for (j = 0; j < pstPlmnSelectionPlmnInfo->ucRatNum; j++)
            {
                /* ������ȵĽ��뼼���뵱ǰ���ҵ�����֧�ֵĽ��뼼����ͬ */
                if (pstPrioRatList->aucRatPrio[k] == pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType)
                {
                    ulIsPlmnSearchingAllowed = NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy(&(pstPlmnSelectionPlmnInfo->stPlmnId),
                                                                                         pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType,
                                                                                         pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enNetStatus,
                                                                                         ulUserSpecPlmnSearch);
                    if (VOS_FALSE == ulIsPlmnSearchingAllowed)
                    {
                        /* �洢�Ľ��뼼���������ظ� */
                        break;
                    }

                    pstDestPlmn->stPlmnId = pstPlmnSelectionPlmnInfo->stPlmnId;
                    pstDestPlmn->enRat    = pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType;

                    return VOS_TRUE;
                }
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdatePlmnIdWithBCCHMnc
 ��������  : ���� BCCH��Mncȷ��Sim���ж�ӦPlmn��Mnc�ĳ��� ��������list�����ϱ�ʱ����
             ���ú�����Ҫ��֤,ulBcchMnc��Ӧ���� ��pstDestPlmnInfo��Ӧ��������ͬ��
 �������  : ulBcchMnc
 �������  : pstDestPlmnId
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��27��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdatePlmnIdWithBCCHMnc(
    VOS_UINT32                          ulBcchMnc,
    NAS_MML_PLMN_ID_STRU               *pstDestPlmnId
)
{
    VOS_UINT8                           ucBcchMnc3;

    ucBcchMnc3 = (VOS_UINT8)((ulBcchMnc & 0x00ff0000) >> 16);

    if (0x0F == ucBcchMnc3)
    {
        pstDestPlmnId->ulMnc |= 0x0F0000;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdatePlmnRatInfoInSearchList
 ��������  : ����PLMN ID�ͽ��뼼��,�������б��и�������״̬������Ϣ
 �������  : pstPlmnSearchInfo    ���������б���Ϣ
 �������  : pstPlmnSelectionInfo,ѡ���б���ĳ������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_UpdatePlmnRatInfoInSearchList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnSelectionInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    VOS_UINT8                                               ucIsAllBandSearch

)
{
    VOS_UINT32                               i;
    VOS_UINT32                               j;

    for (i = 0; i < pstPlmnSelectionInfo->ucRatNum; i++)
    {
        if (pstPlmnSearchInfo->enRatType == pstPlmnSelectionInfo->astPlmnRatInfo[i].enRatType)
        {
            break;
        }
    }

    if (i == pstPlmnSelectionInfo->ucRatNum)
    {
        return VOS_FALSE;
    }

    /* pstPlmnSelectionInfo->stPlmnId�Ƿ��ڸ������б��� */
    for (j = 0; j < pstPlmnSearchInfo->ulHighPlmnNum; j++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnSearchInfo->astHighPlmnList[j]),
                                                           &(pstPlmnSelectionInfo->stPlmnId)))
        {
            /* �����ǰ���統ǰ���뼼��״̬Ϊinitial��not exist�������״̬Ϊ���ڣ�����Ϊ������ */
            if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != pstPlmnSelectionInfo->astPlmnRatInfo[i].enNetStatus)
            {
                pstPlmnSelectionInfo->astPlmnRatInfo[i].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
            }
            pstPlmnSelectionInfo->astPlmnRatInfo[i].enQuality   = NAS_MMC_NET_HIGH_QUALITY;
            pstPlmnSelectionInfo->astPlmnRatInfo[i].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;

            /* BCCH���ϱ���Mnc�п��ܳ��Ⱥ�SIM���д洢��Mnc��һ����ͳһ��ΪBCCH�е�Mnc */
            pstPlmnSelectionInfo->stPlmnId.ulMnc = pstPlmnSearchInfo->astHighPlmnList[j].ulMnc;
            return VOS_TRUE;
        }
    }

    for (j = 0; j < pstPlmnSearchInfo->ulLowPlmnNum; j++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn((NAS_MML_PLMN_ID_STRU*)&(pstPlmnSearchInfo->astLowPlmnList[j].stPlmnId),
                                                           &(pstPlmnSelectionInfo->stPlmnId)))
        {
            /* �����ǰ���統ǰ���뼼��״̬Ϊinitial��not exist�������״̬Ϊ���ڣ�����Ϊ����������¼��������ֵ */
            if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != pstPlmnSelectionInfo->astPlmnRatInfo[i].enNetStatus)
            {
                pstPlmnSelectionInfo->astPlmnRatInfo[i].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
            }
            pstPlmnSelectionInfo->astPlmnRatInfo[i].enQuality   = NAS_MMC_NET_LOW_QUALITY;
            pstPlmnSelectionInfo->astPlmnRatInfo[i].lRscp       = pstPlmnSearchInfo->astLowPlmnList[j].lRscp;

            /* BCCH���ϱ���Mnc�п��ܳ��Ⱥ�SIM���д洢��Mnc��һ����ͳһ��ΪBCCH�е�Mnc */
            pstPlmnSelectionInfo->stPlmnId.ulMnc = pstPlmnSearchInfo->astLowPlmnList[j].stPlmnId.ulMnc;
            return VOS_TRUE;
        }
    }


    /* ��ȫƵ������ʱ�򣬲��ܽ�δ�������ĸ���Ϊ�����ڣ�����ʷƵ���ѣ��������ѵȷ�ȫƵ����ʱ��ֻ�ܸ��´��ڵ� */
    if (VOS_TRUE == ucIsAllBandSearch )
    {
        /* �����ǰ���統ǰ���뼼��״̬Ϊinitial��exist��exist seached�������״̬Ϊ������ */
        pstPlmnSelectionInfo->astPlmnRatInfo[i].enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST;
        pstPlmnSelectionInfo->astPlmnRatInfo[i].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_DelPlmnInSearchList
 ��������  : �������б���ɾ��ָ��������
 �������  : pstPlmn    ��Ҫɾ��������
 �������  : pstPlmnSearchInfo,�����б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_DelPlmnInSearchList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmn,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo
)
{
    VOS_UINT32                           i;

    /* �Ӹ������б���ɾ�������� */
    for (i = 0; i < pstPlmnSearchInfo->ulHighPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnSearchInfo->astHighPlmnList[i]),
                                                           pstPlmn))
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSearchInfo->astHighPlmnList[i]),
                        &(pstPlmnSearchInfo->astHighPlmnList[i+1]),
                        (pstPlmnSearchInfo->ulHighPlmnNum-i-1)*sizeof(NAS_MML_PLMN_ID_STRU));
            /*lint +e961*/
            (pstPlmnSearchInfo->ulHighPlmnNum)--;

            return;
        }
    }

    /* �ӵ������б���ɾ�������� */
    for (i = 0; i < pstPlmnSearchInfo->ulLowPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn((NAS_MML_PLMN_ID_STRU*)&(pstPlmnSearchInfo->astLowPlmnList[i].stPlmnId),
                                                           pstPlmn))
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSearchInfo->astLowPlmnList[i]),
                        &(pstPlmnSearchInfo->astLowPlmnList[i+1]),
                        (pstPlmnSearchInfo->ulLowPlmnNum-i-1)*sizeof(NAS_MMC_LOW_PLMN_INFO_STRU));
            /*lint +e961*/
            (pstPlmnSearchInfo->ulLowPlmnNum)--;

            return;
        }
    }

    return;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSpecPlmnTypeIndexInPlmnSelectionList
 ��������  : ��ȡ�����б���ָ���������͵�����ֵ
 �������  : enSpecPlmnType      - ��������
             pstPlmnSelectionList- �б���Ϣ
 �������  : ��
 �� �� ֵ  : ����ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_UINT16 NAS_MMC_GetSpecPlmnTypeIndexInPlmnSelectionList(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enSpecPlmnType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{

    VOS_UINT16                                              i;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo = VOS_NULL_PTR;

    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        pstPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);

        if (enSpecPlmnType == pstPlmnInfo->enPlmnType)
        {
            return i;
        }
    }

    /* ������ָ�����͵����磬������Чֵ0xffff */
    return NAS_MMC_PLMN_SELECTION_LIST_INVALID_INDEX;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_InsertRoamPlmnListInPlmnSelectionList
 ��������  : �������������б���Ϣ���»򲹳�ѡ���б�
 �������  : pastPlmnSearchInfo,�������б���Ϣ
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��18��
   ��    ��   : c00188733
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_VOID NAS_MMC_InsertRoamPlmnListInPlmnSelectionList(
    VOS_UINT32                                              ulPlmnSearchNum,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnIdList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT16                                              usIndex;
    VOS_UINT16                                              usSimRat;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;

    /* ѭ��������������ÿ������,�ж��Ƿ��������б����Ѵ��ڣ�����������ҹ�������rplmn��hplmn��ͬ��
       ����������б��rplmn��hplmnǰ */
    for (i = 0; i < ulPlmnSearchNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_IsPlmnWithRatInPlmnList(&(pstPlmnIdList[i]),
                                                          enRat,
                                                          pstPlmnSelectionListInfo,
                                                          pstPlmnSelectionListInfo->usSearchPlmnNum))
        {
            continue;
        }


        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstPlmnIdList[i].ulMcc))
        {
            continue;
        }

        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstPlmnIdList[i].ulMcc))
        {
            continue;
        }

        usSimRat = NAS_MMC_ConvertNetRatToSimRat(enRat);

        /* ��ȡrplmn�������б��е�index�����rplmn�����ڣ����ȡhplmn�������б��е�index,���������б�indexλ�� */
        usIndex = NAS_MMC_GetSpecPlmnTypeIndexInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN, pstPlmnSelectionListInfo);

        if (NAS_MMC_PLMN_SELECTION_LIST_INVALID_INDEX != usIndex)
        {

            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                               usSimRat,
                                               &pstPlmnIdList[i],
                                               &stPlmnInfo);

            (VOS_VOID)NAS_MMC_InsertPlmnInPlmnSelectionList(&stPlmnInfo,
                                                   pstPlmnSelectionListInfo,
                                                   usIndex);
        }
        else
        {
            usIndex = NAS_MMC_GetSpecPlmnTypeIndexInPlmnSelectionList(NAS_MMC_PLMN_TYPE_HPLMN, pstPlmnSelectionListInfo);

            NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                               usSimRat,
                                               &pstPlmnIdList[i],
                                               &stPlmnInfo);

            (VOS_VOID)NAS_MMC_InsertPlmnInPlmnSelectionList(&stPlmnInfo,
                                                   pstPlmnSelectionListInfo,
                                                   usIndex);
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateRoamPlmnListInPlmnSelectionList
 ��������  : �������������б���Ϣ���»򲹳�ѡ���б�
 �������  : pastPlmnSearchInfo,�������б���Ϣ
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateRoamPlmnListInPlmnSelectionList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulAppendFlg,
    VOS_UINT8                                                ucIsAllBandSearch

)
{
    VOS_UINT32                                              i;
    NAS_MML_PLMN_ID_STRU                                    astLowPlmnInfo[NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM];

    /*���������PLMN*/
    NAS_MMC_InsertRoamPlmnListInPlmnSelectionList(pstPlmnSearchInfo->ulHighPlmnNum,pstPlmnSearchInfo->enRatType,pstPlmnSearchInfo->astHighPlmnList,pstPlmnSelectionListInfo);

    /*���������PLMN*/
    PS_MEM_SET(astLowPlmnInfo, 0xFF, sizeof(astLowPlmnInfo));
    for (i = 0; i < pstPlmnSearchInfo->ulLowPlmnNum; i++)
    {
        astLowPlmnInfo[i].ulMcc = pstPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMcc;
        astLowPlmnInfo[i].ulMnc = pstPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMnc;
    }
    NAS_MMC_InsertRoamPlmnListInPlmnSelectionList(pstPlmnSearchInfo->ulLowPlmnNum,pstPlmnSearchInfo->enRatType,astLowPlmnInfo,pstPlmnSelectionListInfo);

    /* ������Ͻ�ʣ�����粹�䵽ѡ���б� */
    NAS_MMC_UpdatePlmnListInPlmnSelectionList(pstPlmnSearchInfo,
                                              pstPlmnSelectionListInfo,
                                              ulAppendFlg,
                                              ucIsAllBandSearch);

    return;
}





/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdatePlmnListInPlmnSelectionList
 ��������  : �������������б���Ϣ���»򲹳�ѡ���б�
 �������  : pastPlmnSearchInfo,�������б���Ϣ
             ulAppendFlg,�Ƿ���Ҫ�����º���б���Ϣ���浽ѡ���б�
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnListInPlmnSelectionList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulAppendFlg,
    VOS_UINT8                                                ucIsAllBandSearch

)
{
    VOS_UINT32                                              i;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstTmpPlmnSearchInfo = VOS_NULL_PTR;


    pstTmpPlmnSearchInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU));

    if (VOS_NULL_PTR == pstTmpPlmnSearchInfo)
    {
        /* ��ӡ�쳣 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_UpdatePlmnListInPlmnSelectionList: Mem alloc fail.");

        return;
    }

    PS_MEM_CPY(pstTmpPlmnSearchInfo, pstPlmnSearchInfo, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU));

    /* ѭ��ѡ���б���ÿһ������ */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {

        /* ����һ�����뼼����������Ϣ���������б��е�һ�����磬������³ɹ�����Ҫ��������Ϣ�ж�Ӧ����ɾ�� */
        if (VOS_TRUE == NAS_MMC_UpdatePlmnRatInfoInSearchList(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                                               pstPlmnSearchInfo, ucIsAllBandSearch))
        {
            NAS_MMC_DelPlmnInSearchList(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId), pstTmpPlmnSearchInfo);
        }
    }

    /* �����Ҫ�����������б���ϢpastPlmnSearchInfo�е�ʣ�����粹�䵽�����б��� */
    if (VOS_TRUE == ulAppendFlg)
    {
        NAS_MMC_SavePlmnListInPlmnSelectionList(pstTmpPlmnSearchInfo, pstPlmnSelectionListInfo);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstTmpPlmnSearchInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnTypeInPlmnSelectionList
 ��������  : ��ȡ�����б���ָ�����뼼�������������
 �������  : pstPlmnWithRat
             pstPlmnSelectionList,�б���Ϣ
 �������  : ��
 �� �� ֵ  : NAS_MMC_PLMN_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
NAS_MMC_PLMN_TYPE_ENUM_UINT8 NAS_MMC_GetPlmnTypeInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{

    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo = VOS_NULL_PTR;

    /* ����PLMN������뼼���������б���ÿ��PLMN������뼼���Ƚ� */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        pstPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);

        /* �Ƚ�pstPlmn->stPlmnId,��pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId */
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstPlmnWithRat->stPlmnId),
                                                           &(pstPlmnInfo->stPlmnId)))
        {
            /* �����ͬ���ȽϽ��뼼�� */
            for (j = 0; j < pstPlmnInfo->ucRatNum; j++)
            {
                if (pstPlmnWithRat->enRat == pstPlmnInfo->astPlmnRatInfo[j].enRatType)
                {
                    return pstPlmnInfo->enPlmnType;
                }
            }
        }
    }

    return NAS_MMC_PLMN_TYPE_BUTT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSpecPlmnNetStatusInPlmnSelectionList
 ��������  : ��ȡ�����б���ָ������ĸ����뼼��������״̬
 �������  : pstPlmnWithRat
             pstPrioRatList
             pstPlmnSelectionList,�б���Ϣ
 �������  : paucNetStatus
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_GetSpecPlmnNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmn,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList,
    NAS_MMC_NET_STATUS_ENUM_UINT8                          *paucNetStatus,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo = VOS_NULL_PTR;

    /* ����PLMN������뼼���������б���ÿ��PLMN������뼼���Ƚ� */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++)
    {
        pstPlmnInfo = &(pstPlmnSelectionListInfo->astPlmnSelectionList[i]);

        /* �Ƚ�pstPlmn->stPlmnId,��pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId */
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmn,
                                                           &(pstPlmnInfo->stPlmnId)))
        {
            /* �����ͬ���ȽϽ��뼼�� */
            for (j = 0; j < pstPrioRatList->ucRatNum; j++)
            {
                for (k = 0; k < pstPlmnInfo->ucRatNum; k++)
                {
                    if (pstPrioRatList->aucRatPrio[j] == pstPlmnInfo->astPlmnRatInfo[k].enRatType)
                    {
                        paucNetStatus[j] = pstPlmnInfo->astPlmnRatInfo[k].enNetStatus;
                        break;
                    }
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetRPlmn_PlmnSelectionStrategy
 ��������  : ����RPLMN�������Ի�ȡRPLMN
 �������  : enRat
 �������  : pstPlmnId
 �� �� ֵ  : VOS_TRUE,��ȡ�ɹ�
             VOS_FALSE,��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��  : s46746
   �޸�����  : �����ɺ���
 2.��    ��   : 2016��5��2��
   ��    ��   : z00359541
   �޸�����   : ���Ȼ�ȡָ�����뼼����Rplmn�����ʧ�ܣ����ȡ�������뼼����-
                Rplmn
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetRPlmn_PlmnSelectionStrategy(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRPlmnCfg  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRPlmn;

    /* ��ʼ��Ϊ��ЧPLMN */
    pstPlmnId->ulMcc = NAS_MML_INVALID_MCC;
    pstPlmnId->ulMnc = NAS_MML_INVALID_MNC;

    /* ��ȡRPLMN������Ϣ */
    pstRPlmnCfg = NAS_MML_GetRplmnCfg();

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        /* ��ȡLTE��RPLMN */
        return NAS_MML_GetPrefRPlmn(enRat, pstPlmnId);
    }
#endif

    /* ��ȡGU��RPLMN */
    if (VOS_FALSE == NAS_MML_GetPrefRPlmn(enRat, pstPlmnId))
    {
        return VOS_FALSE;
    }

    /* �����֧�ֶ���뼼��RPLMN,����Ҫ��ȡ���Խ��뼼���±�����NV�е�RPLMN */
    if (VOS_FALSE == pstRPlmnCfg->ucMultiRATRplmnFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRPlmn_PlmnSelectionStrategy: ucMultiRATRplmnFlg is FALSE");
        return VOS_TRUE;
    }

    if (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
    {
        stRPlmn = pstRPlmnCfg->stWRplmnInNV;
    }
    else
    {
        stRPlmn = pstRPlmnCfg->stGRplmnInNV;
    }

    /* ��NV�б����RPLMN��Ч�Ҳ��ڽ�ֹ�����У�����NV�д洢������,���򷵻�֮ǰ��SIM���л�ȡ������ */
    if (VOS_TRUE == NAS_MML_IsPlmnIdValid(&stRPlmn))
    {
        if (VOS_FALSE == NAS_MML_IsPlmnIdInForbidPlmnList(&stRPlmn))
        {
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_GetRPlmn_PlmnSelectionStrategy: RPLMN not in FPLMN list");
           *pstPlmnId = stRPlmn;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy
 ��������  : �ж�PLMN ID�Ƿ��ڽ�ֹ�б���
 �������  : pstPlmnId:��Ҫ�жϵ�PLMN ID
             enRat:������뼼��
             enNetStatus:�������״̬
             ulUserSpecPlmnSearch:�Ƿ��û�ָ������
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : PLMN ID��������
             VOS_FALSE : PLMN ID����������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011��08��3��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��10��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 phaseII�����ȼ�����LLD��������޸ĺ������Ͳ���
 3.��    ��   : 2011��10��26��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase III����:����ע���޸�
 4.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
                ����ΪNAS_MML_IsSimPlmnIdInDestBcchPlmnList,��ȷ����ıȽ����ͣ�
                ������ܵ��±Ƚϳ���
 4.��    ��   : 2011��10��26��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase III����:����ע���޸�
 5.��    ��   : 2012��3��17��
   ��    ��   : w00176964
   �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:����LTE�������ι��ܶ���

 6.��    ��   : 2012��10��20��
   ��    ��   : w00167002
   �޸�����   : DTS2012101903646:GUTL��ģ���ư汾��UE��L��ע�ᱻ�ܺ󣬸�����
                ���б�ʱ��û�й��˽�ֹ���뼼������,���³����ѽ�ֹ���뼼�������磬
                ����Ʋ����ϡ�
 7.��    ��   : 2012��12��27��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:���USIM��GSM��ֹ���룬��ѡ��GSM����
 8.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 9.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
 10.��    ��   : 2015��4��23��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MMC_NET_STATUS_ENUM_UINT8       enNetStatus,
    VOS_UINT32                          ulUserSpecPlmnSearch
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulAllowed;
#endif
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRatId;


    /* ��ʼ��PLMN WITH RAT��Ϣ */
    stPlmnWithRatId.stPlmnId.ulMcc      = pstPlmnId->ulMcc;
    stPlmnWithRatId.stPlmnId.ulMnc      = pstPlmnId->ulMnc;
    stPlmnWithRatId.enRat               = enRat;

#if (FEATURE_ON == FEATURE_LTE)
    ulAllowed = VOS_TRUE;

    /* ��ǰ����ΪLTEʱ */
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        /* �ж��Ƿ�����LTE������������� */
        ulAllowed   = NAS_MMC_IsLtePlmnSearchingAllowed_PlmnSelectionStrategy(pstPlmnId);
    }

    if (VOS_FALSE == ulAllowed)
    {
        return VOS_FALSE;
    }

#endif

    /* ���USIM��GSM��ֹ���룬��ѡ��GSM���� */
    if ( (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
      && (NAS_MML_NET_RAT_TYPE_GSM == enRat) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy GsmForbidFlg");        
        
        return VOS_FALSE;
    }

    /* �����ǰ���������������ڽ�ֹ���뼼�������б���,��׼������ */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRatId))
    {
       return VOS_FALSE;
    }

    /* �����ǰ���ԵĽ��뼼���ڽ�ֹ���뼼���б��У���׼������ */
    if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(stPlmnWithRatId.enRat))
    {
        return VOS_FALSE;
    }


    /* ����״̬��Ϊδ����������������,���������������� */
    if ((NAS_MMC_NET_STATUS_NO_SEARCHED != enNetStatus)
     && (NAS_MMC_NET_STATUS_SEARCHED_EXIST != enNetStatus))
    {
        return VOS_FALSE;
    }

    /* �ֶ�ģʽ����Ҫ���ж��Ƿ��ڽ�ֹ�����б��� */
    if (VOS_TRUE == ulUserSpecPlmnSearch)
    {
        return VOS_TRUE;
    }

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();


    /* ��ֹ���磬��Ϊ�϶���BCCH�������磬��forbid plmn�б��� */
    if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstPlmnId,
                                          pstForbidPlmnInfo->ucForbPlmnNum,
                                          pstForbidPlmnInfo->astForbPlmnIdList))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy auto in astForbPlmnIdList");        
        
        return VOS_FALSE;
    }

    /* ����forbid plmn for gprs�б��� */
    if (VOS_FALSE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstPlmnId,
                                          pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                          pstForbidPlmnInfo->astForbGprsPlmnList))
    {
        return VOS_TRUE;
    }

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy auto in astForbGprsPlmnList");        

#if (FEATURE_ON == FEATURE_LTE)

    /* LTE��֧��EPS,������PS����,��ʾ�����粻������ */
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        return VOS_FALSE;
    }
#endif

    /* ����ΪPS ONLYʱ,��������ֹGPRS�б��е����� */
    if (NAS_MML_MS_MODE_PS_ONLY == NAS_MML_GetMsMode())
    {
        return VOS_FALSE;
    }

    /* CS����Чʱ */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MML_GetSimCsRegStatus is false");        
        
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveAvailablePlmnInPlmnSelectionList
 ��������  : ��Available���籣���ѡ���б�
 �������  : ulAvailPlmnNum
             pstAvailPlmnList
 �������  : pstPlmnSelectionListInfo
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2011��08��3��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
*****************************************************************************/
/*lint -e429*/
VOS_VOID NAS_MMC_SaveAvailablePlmnInPlmnSelectionList(
    VOS_UINT32                                              ulAvailPlmnNum,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstAvailPlmnList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    /* �ж�����������Ƿ�ᵼ��ѡ���б���� */
    if ((pstPlmnSelectionListInfo->usSearchPlmnNum + ulAvailPlmnNum) < NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST)
    {
        PS_MEM_CPY(&pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum],
                   pstAvailPlmnList,
                   ulAvailPlmnNum*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
        pstPlmnSelectionListInfo->usSearchPlmnNum += (VOS_UINT16)ulAvailPlmnNum;
    }
    else
    {
        PS_MEM_CPY(&pstPlmnSelectionListInfo->astPlmnSelectionList[pstPlmnSelectionListInfo->usSearchPlmnNum],
                   pstAvailPlmnList,
                   (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST-pstPlmnSelectionListInfo->usSearchPlmnNum)*sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
        pstPlmnSelectionListInfo->usSearchPlmnNum = NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST;

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SaveAvailablePlmnInPlmnSelectionList: Plmn selection list full.");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SavePlmnListInPlmnSelectionList
 ��������  : ������º�ʣ��������б���Ϣ��ѡ���б�
 �������  : pastPlmnSearchInfo,ʣ��������б���Ϣ
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SavePlmnListInPlmnSelectionList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{

    VOS_UINT32                                              i;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmn;

    /* ��ʼ��ѡ����Ϣ */
    NAS_MMC_BuildPlmnSelectionPlmnInfo(NAS_MMC_PLMN_TYPE_AVAIL_PLMN, NAS_MML_INVALID_SIM_RAT,
                                       &(stPlmn.stPlmnId), &stPlmn);

    stPlmn.ucRatNum++;
    stPlmn.astPlmnRatInfo[0].enRatType     = pstPlmnSearchInfo->enRatType;
    stPlmn.astPlmnRatInfo[0].enNetStatus   = NAS_MMC_NET_STATUS_SEARCHED_EXIST;

    /* ѭ���������б��л����ڵĸ��������� */
    for (i = 0; i < pstPlmnSearchInfo->ulHighPlmnNum; i++)
    {
        stPlmn.stPlmnId                        = pstPlmnSearchInfo->astHighPlmnList[i];

        stPlmn.astPlmnRatInfo[0].enQuality     = NAS_MMC_NET_HIGH_QUALITY;

        /* ���뵽ѡ���б��� */
        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmn, pstPlmnSelectionListInfo);
    }

    /* ѭ���������б��л����ڵĵ��������� */
    for (i = 0; i < pstPlmnSearchInfo->ulLowPlmnNum; i++)
    {
        stPlmn.stPlmnId.ulMcc                  = pstPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMcc;
        stPlmn.stPlmnId.ulMnc                  = pstPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMnc;

        stPlmn.astPlmnRatInfo[0].enQuality     = NAS_MMC_NET_LOW_QUALITY;
        stPlmn.astPlmnRatInfo[0].lRscp         = pstPlmnSearchInfo->astLowPlmnList[i].lRscp;

        /* ���뵽ѡ���б��� */
        NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmn, pstPlmnSelectionListInfo);
    }

    return;
}
/*lint +e429*/
/*****************************************************************************
 �� �� ��  : NAS_MMC_InitNetStatusInRatSearchInfo
 ��������  : ���ݽ��뼼���Ƿ���й�ȫƵ��������ʼ������Ĵ���״̬
 �������  : pstPrioRatList : ���뼼�����ȼ��б�
              pstSearchRatInfo ����ͬ���뼼����������Ϣ�б�
 �������  : paucNetStatus�����뼼����Ӧ������״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��22��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_InitNetStatusInRatSearchInfo(
    NAS_MMC_NET_STATUS_ENUM_UINT8      *paucNetStatus,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList,
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT8                           ucSearchAllBandFlg;

    for (i = 0; i < pstPrioRatList->ucRatNum; i++)
    {
        ucSearchAllBandFlg = VOS_FALSE;

        for (j = 0; j < NAS_MML_MAX_RAT_NUM; j++)
        {
            if (pstPrioRatList->aucRatPrio[i] == pstSearchRatInfo[j].enRatType)
            {
                ucSearchAllBandFlg = pstSearchRatInfo[j].ucSearchAllBand;
                break;
            }
        }

        if (VOS_TRUE == ucSearchAllBandFlg)
        {
            paucNetStatus[i] = NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST;
        }
        else
        {
            paucNetStatus[i] = NAS_MMC_NET_STATUS_NO_SEARCHED;
        }
    }
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RefreshPlmnSelectionList_DisableLte_CsPsMode1RegSuccess
 ��������  : ˢ��ѡ���б���֤��ǰ�����GU���뼼����������
 �������  : ��
 �������  : pstPlmnSelectionList
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��1��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��10��10��
   ��    ��   : t00212959
   �޸�����   : For DTS2012083005474��EPLMN�ĵ�һ����RPLMN,��ԭ�����б��RPLMN �� EPLMNȥ��
 3.��    ��   : 2012��12��12��
   ��    ��   : t00212959
   �޸�����   : For DTS2012121104779��������ΪCSPS mode 1���µ�disable L,�类#7�ܾ�����Ӧ�ð���CSPS Mode1����

 4.��    ��   : 2014��5��28��
   ��    ��   : z00234330
   �޸�����   : covertity�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_RefreshPlmnSelectionList_DisableLte_CsPsMode1RegSuccess(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList,
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEPlmnList    = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MMC_NET_STATUS_ENUM_UINT8       aucNetStatus[NAS_MML_MAX_RAT_NUM];
    VOS_UINT32                          i;

    /* modified by z00234330 for coverity�޸� 2014-05-28 begin */
    PS_MEM_SET(aucNetStatus, 0x00, sizeof(aucNetStatus));
    PS_MEM_SET(&stPrioRatList, 0x00, sizeof(stPrioRatList));
    /* modified by z00234330 for coverity�޸� 2014-05-28 end */

    /* NAS_MML_GetEquPlmnList ��ȡ��ǰ�����EPLMN */
    pstEPlmnList   = NAS_MML_GetEquPlmnList();
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* ��ԭ�������б��EPLMNȥ��*/
    /* �ֶ�ѡ��ģʽɾ��RPLMN��EPLMN,�û�ָ�����粻ɾ��,Ŀ�������������뼼���ϼ��������û�ָ������ */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ��ѡ���б��н��û�ָ��PLMN�޸�ΪAvail plmn,��֤������ȡ��һ����������ʱ,
           ����䴦�ڽ�ֹ�б���,�������������� */
        NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                  NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                  pstPlmnSelectionList);

        /* ��ѡ���б���ɾ��RPLMN */
        NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN,
                                                      pstPlmnSelectionList);

        /* ��ѡ���б���ɾ��EPLMN */
        NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN,
                                                      pstPlmnSelectionList);
    }
    else
    {
        /* ��ѡ���б��н�RPLMN�޸�ΪAvail plmn */
        NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN,
                                                  NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                  pstPlmnSelectionList);

        /* ��ѡ���б��н�EPLMN�޸�ΪAvail plmn */
        NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN,
                                                  NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                  pstPlmnSelectionList);

        /* ��ѡ���б���ɾ������ΪUNKNOW��Avail plmn */
        NAS_MMC_DeleteSpecQualAvailPlmnInPlmnSelectionList(NAS_MMC_NET_QUALITY_UNKNOWN,
                                                           pstPlmnSelectionList);

        /* ��������available plmn */
        NAS_MMC_SortAvailPlmnInPlmnSelectionList(pstPlmnSelectionList);
    }

    /* ��EPLMN�Ӻ���ǰ��ӵ�ѡ���б� */
    for ( i = pstEPlmnList->ucEquPlmnNum; i > 0; i-- )
    {
        NAS_MMC_InitNetStatusInRatSearchInfo(aucNetStatus, pstPrioRatList, pstSearchRatInfo);

        NAS_MMC_GetSpecPlmnNetStatusInPlmnSelectionList(&(pstEPlmnList->astEquPlmnAddr[i-1]),
                                                          pstPrioRatList,
                                                          aucNetStatus,
                                                          pstPlmnSelectionList);

        PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(stPrioRatList));

        /* ����״̬ΪNAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,NAS_MMC_NET_STATUS_SEARCHED_REGISTERED�Ľ��뼼��,
           ��ʾ����û��Ҫ�ڽ���������,��˴�stPrioRatList��ɾ�� */
        NAS_MMC_DelSpecNetStatusRat(NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST, aucNetStatus, &stPrioRatList);

        NAS_MMC_DelSpecNetStatusRat(NAS_MMC_NET_STATUS_SEARCHED_REGISTERED, aucNetStatus, &stPrioRatList);

        if (i==1)
        {
            /* ��RPLMN������뵽ѡ���б���ǰ�� */
            NAS_MMC_InsertPlmnToPlmnSelectionListHead(&(pstEPlmnList->astEquPlmnAddr[i-1]),
                                                        NAS_MMC_PLMN_TYPE_RPLMN,
                                                       &stPrioRatList,
                                                        pstPlmnSelectionList);
        }
        else
        {
            /* ��EPLMN������뵽ѡ���б���ǰ�� */
            NAS_MMC_InsertPlmnToPlmnSelectionListHead(&(pstEPlmnList->astEquPlmnAddr[i-1]),
                                                        NAS_MMC_PLMN_TYPE_EPLMN,
                                                       &stPrioRatList,
                                                        pstPlmnSelectionList);
        }

    }

    return;
}

#endif


/*****************************************************************************
 �� �� ��  : NAS_MMC_RefreshEPlmnInPlmnSelectionList
 ��������  : ��ע��ʧ����Ҫ����PLMN SELECTIONʱ��ѡ���б�ĵ���
 �������  : ��
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���
 2. ��    ��   : 2011��1��15��
    ��    ��  : l00171473
    �޸�����   : For DTS2011111003965, �ֶ��������û�ָ�����类ԭ��ֵ13�ܵ��󣬲�Ӧ��EPLMN
  3.��    ��   : 2012��10��26��
    ��    ��   : W00176964
    �޸�����   : DTS2012090303157:ʹ��EPLMN��Ч������ж��Ƿ���Ҫ��ѡ���б���ɾ��EPLMN
  4.��    ��   : 2014��5��21��
    ��    ��   : w00167002
    �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ
                ɾ��EPLMNʱ�򣬲��ܽ��Ѿ�ע���������ɾ����
*****************************************************************************/
VOS_VOID NAS_MMC_RefreshEPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList
)
{
    /* EPLMN��Чֱ�ӷ���,ֻ����EPLMN��Ч������²Ÿ���ѡ���б� */
    if (VOS_TRUE == NAS_MML_GetEplmnValidFlg())
    {
        return;
    }


    /* �ֶ�ѡ��ģʽɾ��RPLMN��EPLMN,�û�ָ�����粻ɾ��,Ŀ�������������뼼���ϼ��������û�ָ������ */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        /* ��ѡ���б��н��û�ָ��PLMN�޸�ΪAvail plmn,��֤������ȡ��һ����������ʱ,
           ����䴦�ڽ�ֹ�б���,�������������� */
        NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,
                                                  NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                  pstPlmnSelectionList);


        if (VOS_TRUE == NAS_MML_GetDeleteRplmnWhenEplmnInvalidFlg())
        {
            /* ��ѡ���б���ɾ��RPLMN */
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN,
                                                          pstPlmnSelectionList);
        }

        /* ��ѡ���б���ɾ��EPLMN */
        NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN,
                                                      pstPlmnSelectionList);

        return;
    }

    if (VOS_TRUE == NAS_MML_GetDeleteRplmnWhenEplmnInvalidFlg())
    {
        /* ��ѡ���б��н�RPLMN�޸�ΪAvail plmn */
        NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN,
                                                  NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                  pstPlmnSelectionList);
    }

    /* ��ѡ���б��н�EPLMN�޸�ΪAvail plmn */
    NAS_MMC_ModifyPlmnTypeInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN,
                                              NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                              pstPlmnSelectionList);


    /* ��ѡ���б���ɾ������״̬Ϊδ���������� */
    NAS_MMC_DeleteSpecNetStatusAvailPlmnInPlmnSelectionList(NAS_MMC_NET_STATUS_NO_SEARCHED,
                                               pstPlmnSelectionList);


    /* ��������available plmn */
    NAS_MMC_SortAvailPlmnInPlmnSelectionList(pstPlmnSelectionList);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsR7SptSrchHplmn_AutoMode
 ��������  : �Զ�ģʽ�Ƿ�֧��R7�������� Hplmn
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��8��12��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��12��
   ��    ��   : w00167002
   �޸�����   : DTS2011111200182:��¼�Ƿ�֧��Э��Ҫ������Զ�ģʽ����
                 ����������Hplmn������,VOS_FALSE:��֧��,VOS_TRUE:֧��
 3.��    ��   : 2014��3��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014031200137:��NV���Դ�ʱ���Զ�������������ʱ������״�����RPLMN�Ļ���
                ��Ҫ��HPLMN/EHPLMN��������㡣
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsHPlmnPrioSearch( VOS_VOID )
{
    NAS_MML_HPLMN_CFG_INFO_STRU        *pstHplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo   = VOS_NULL_PTR;

    /* ��ȡHPLMN��������Ϣ */
    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    /* ��ȡSim����Ehplmn��ص���Ϣ */
    pstEHPlmnInfo  = NAS_MML_GetSimEhplmnList();

    /* �Զ�����ģʽ ֧�ֿ�����������Hplmn */
    if ((NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
     && ( ( (NAS_MML_AUTO_SRCH_FLG_TYPE_PLMN_SEL_IND == pstHplmnCfgInfo->enAutoSearchHplmnFlg)
       && (NAS_MML_LAST_RPLMN_SEL_IND_HPLMN == pstEHPlmnInfo->enPLMNSelInd))
     || (NAS_MML_AUTO_SRCH_FLG_TYPE_HPLMN_FIRST == pstHplmnCfgInfo->enAutoSearchHplmnFlg) ))
    {
        return VOS_TRUE;
    }
    else
    {
       return VOS_FALSE;
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsRPlmnFirstSearchWithHPlmn
 ��������  : ����RPLMNʱ���Ƿ���Ҫ��HPLMN�ı�ʶ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014031200137:��NV���Դ�ʱ���Զ�������������ʱ������״�����RPLMN�Ļ���
                ��Ҫ��HPLMN/EHPLMN��������㡣
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsRPlmnFirstSearchWithHPlmn(VOS_VOID)
{
    NAS_MML_HPLMN_CFG_INFO_STRU        *pstHplmnCfgInfo = VOS_NULL_PTR;

    /* ��ȡHPLMN��������Ϣ */
    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();


    /* �Զ�����ģʽ ֧�ֿ�����������Hplmn */
    if ((NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
     && (NAS_MML_AUTO_SRCH_FLG_TYPE_RPLMN_WITH_HPLMN_FIRST == pstHplmnCfgInfo->enAutoSearchHplmnFlg))
    {
        return VOS_TRUE;
    }
    else
    {
       return VOS_FALSE;
    }
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RefreshCurPlmnInPlmnSelectionList
 ��������  : ��ע��ʧ����Ҫ���е�ǰ��������ʱ��ѡ���б�ĵ���
 �������  : enPlmnType
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���
 2.��    ��   : 2012��7��1��
    ��    ��  : s00217060
    �޸�����  : For V7R1 CS/PS mode 1, ����������ѡ���б��ʼ��
 3.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
 3.��    ��   : 2013��8��26��
   ��    ��   : w00242748
   �޸�����   : DTS2013071808373, ����澯����
*****************************************************************************/
VOS_VOID NAS_MMC_RefreshCurPlmnInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList,
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList       = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MMC_NET_STATUS_ENUM_UINT8       aucNetStatus[NAS_MML_MAX_RAT_NUM];
    VOS_UINT32                          i;

    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    PS_MEM_SET(aucNetStatus, 0x00, sizeof(aucNetStatus));

    pstPrioRatList = NAS_MML_GetMsPrioRatList();
    PS_MEM_CPY(&stPrioRatList, pstPrioRatList, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    /* ��ѡ���б��л�ȡ��ǰ���������״̬ */
    NAS_MMC_InitNetStatusInRatSearchInfo(aucNetStatus, pstPrioRatList, pstSearchRatInfo);

    NAS_MMC_GetSpecPlmnNetStatusInPlmnSelectionList(NAS_MML_GetCurrCampPlmnId(),
                                                    pstPrioRatList,
                                                    aucNetStatus,
                                                    pstPlmnSelectionList);

    i = 0;

    /* ����״̬ΪNAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,NAS_MMC_NET_STATUS_SEARCHED_REGISTERED�Ľ��뼼��,
       ��ʾ����û��Ҫ�ڽ���������,��˴�stPrioRatList��ɾ�� */
    while (i < stPrioRatList.ucRatNum)
    {
        if ((NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST == aucNetStatus[i])
         || (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED == aucNetStatus[i]))
        {
            stPrioRatList.aucRatPrio[i] = NAS_MML_NET_RAT_TYPE_BUTT;

            if (i < (NAS_MML_MAX_RAT_NUM - 1))
            {
                /*lint -e961*/
                (VOS_VOID)PS_MEM_MOVE(&(stPrioRatList.aucRatPrio[i]),
                            &(stPrioRatList.aucRatPrio[i+1]),
                            (NAS_MML_MAX_RAT_NUM-i-1));

                (VOS_VOID)PS_MEM_MOVE(&(aucNetStatus[i]),
                            &(aucNetStatus[i+1]),
                            (NAS_MML_MAX_RAT_NUM-i-1));
                /*lint +e961*/
            }
            stPrioRatList.ucRatNum--;

            continue;
        }
        i++;
    }

    /* �����������ΪButt,��ʾѡ���б���δ�ҵ��˽��뼼������,���������;�Ϊavail����,
       ��ʱֻ��Ҫ����ǰ���뼼��������ǰ�漴�� */
    if (NAS_MMC_PLMN_TYPE_BUTT == enPlmnType)
    {
        enPlmnType = NAS_MMC_PLMN_TYPE_AVAIL_PLMN;
        NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), &stPrioRatList);
    }
    else
    {
        /* ����ǰ���뼼�����뵽��ǰ�� */
        (VOS_VOID)PS_MEM_MOVE(&(stPrioRatList.aucRatPrio[1]),
                    &(stPrioRatList.aucRatPrio[0]),
                    (stPrioRatList.ucRatNum*sizeof(NAS_MML_NET_RAT_TYPE_ENUM_UINT8)));

        stPrioRatList.aucRatPrio[0] = NAS_MML_GetCurrNetRatType();

        stPrioRatList.ucRatNum++;
    }

    /* ����ǰ������뵽ѡ���б���ǰ�� */
    NAS_MMC_InsertPlmnToPlmnSelectionListHead(NAS_MML_GetCurrCampPlmnId(),
                                              enPlmnType,
                                              &stPrioRatList,
                                              pstPlmnSelectionList);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_LogPlmnSelectionList
 ��������  : ��ѡ���б��͵�OM
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��29��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_LogPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* ��ѡ���б���Ϣ���͵�OM��� */
    NAS_MMC_SndOmPlmnSelectionList(pstPlmnSelectionList, pstPrioRatList);

    NAS_MMC_LogRplmnRelatedInfo();
    NAS_MMC_LogForbiddenPlmnRelatedInfo();


    /* ��ȡѡ��״̬����������Ϣ���������ⶨλ */
    if (NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
    {
        NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo(NAS_MMC_GetPlmnSelectionCtx_PlmnSelection());
    }


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_LogAsPlmnList
 ��������  : ��������ϱ������б��͵�OM
 �������  : pstSrchedPlmn - ������ϱ��������б�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��9��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��29��
    ��    ��   : w00167002
    �޸�����   : DTS2014122600652:���Ȳ���ȷ���¸�λ
*****************************************************************************/
VOS_VOID NAS_MMC_LogAsPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstSrchedPlmn
)
{
    NAS_MMC_LOG_AS_PLMN_LIST_MSG_STRU                      *pstMsg  = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_AS_PLMN_LIST_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_AS_PLMN_LIST_MSG_STRU)));
    if (TAF_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogAsPlmnList:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_AS_PLMN_SELECTION_LIST;

    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_AS_PLMN_LIST_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY(&pstMsg->stSrchedPlmn, pstSrchedPlmn,sizeof(pstMsg->stSrchedPlmn));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_LogDplmnNplmnList
 ��������  : ��DPLMN, NPLMN���͵�OM
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��11��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��16��
    ��    ��   : s00217060
    �޸�����   : DTS2015120701561:����DPLMN��Ӧ�汾�ź�EHPLMN�б�Ŀ�ά�ɲ�

*****************************************************************************/
VOS_VOID NAS_MMC_LogDplmnNplmnList(VOS_VOID)
{
    NAS_MMC_LOG_DPLMN_LIST_STRU                            *pstLogDplmnMsg       = VOS_NULL_PTR;
    NAS_MMC_LOG_NPLMN_LIST_STRU                            *pstLogNplmnMsg       = VOS_NULL_PTR;
    NAS_MMC_LOG_DPLMN_NPLMN_CFG_STRU                       *pstLogDplmnNplmnCfg  = VOS_NULL_PTR;
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT16                                              i;

    pstDPlmnNPlmnCfgInfo     = NAS_MMC_GetDPlmnNPlmnCfgInfo();


    /* ========================== DPLMN-NPLMN-CFG��ʼ ========================== */
    pstLogDplmnNplmnCfg = (NAS_MMC_LOG_DPLMN_NPLMN_CFG_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_DPLMN_NPLMN_CFG_STRU)));

    if (VOS_NULL_PTR == pstLogDplmnNplmnCfg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogDplmnNplmnList:ERROR:Alloc Mem Fail.");
        return;
    }

    pstLogDplmnNplmnCfg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLogDplmnNplmnCfg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstLogDplmnNplmnCfg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstLogDplmnNplmnCfg->stMsgHeader.ulMsgName       = MMCOM_LOG_DPLMN_NPLMN_CFG;
    pstLogDplmnNplmnCfg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_DPLMN_NPLMN_CFG_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �汾�� */
    PS_MEM_CPY(pstLogDplmnNplmnCfg->aucVersionId, pstDPlmnNPlmnCfgInfo->aucVersionId, NAS_MCC_INFO_VERSION_LEN);

    /* EHPLMN���� */
    pstLogDplmnNplmnCfg->ucEHplmnNum    = pstDPlmnNPlmnCfgInfo->ucEHplmnNum;

    /* EHPLMN�б� */
    PS_MEM_CPY(pstLogDplmnNplmnCfg->astEHplmnList, pstDPlmnNPlmnCfgInfo->astEHplmnList, sizeof(pstDPlmnNPlmnCfgInfo->astEHplmnList));

    DIAG_TraceReport(pstLogDplmnNplmnCfg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstLogDplmnNplmnCfg);

    /* ========================== DPLMN-NPLMN-CFG���� ========================== */


    /* ========================== DPLMN LIST��ʼ ========================== */


    pstLogDplmnMsg = (NAS_MMC_LOG_DPLMN_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_DPLMN_LIST_STRU)));

    if (VOS_NULL_PTR == pstLogDplmnMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogDplmnNplmnList:ERROR:Alloc Mem Fail.");
        return;
    }

    pstLogDplmnMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLogDplmnMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstLogDplmnMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstLogDplmnMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_DPLMN_LIST;

    for (i = 0; i < pstDPlmnNPlmnCfgInfo->usDplmnListNum; i++)
    {
        PS_MEM_CPY(&pstLogDplmnMsg->astDPlmnList[i], &pstDPlmnNPlmnCfgInfo->astDPlmnList[i], sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));
    }

    pstLogDplmnMsg->usDplmnListNum = pstDPlmnNPlmnCfgInfo->usDplmnListNum;

    pstLogDplmnMsg->stMsgHeader.ulLength = sizeof(pstLogDplmnMsg->stMsgHeader.ulMsgName)
                                      + sizeof(pstLogDplmnMsg->usDplmnListNum)
                                      + (pstLogDplmnMsg->usDplmnListNum * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));

    DIAG_TraceReport(pstLogDplmnMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstLogDplmnMsg);

    /* ========================== DPLMN LIST���� ========================== */



    /* ========================== NPLMN LIST��ʼ ========================== */

    pstLogNplmnMsg = (NAS_MMC_LOG_NPLMN_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_NPLMN_LIST_STRU)));

    if (VOS_NULL_PTR == pstLogNplmnMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogDplmnNplmnList:ERROR:Alloc Mem Fail.");
        return;
    }

    pstLogNplmnMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLogNplmnMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstLogNplmnMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstLogNplmnMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_NPLMN_LIST;

    for (i = 0; i < pstDPlmnNPlmnCfgInfo->usNplmnListNum; i++)
    {
        PS_MEM_CPY(&pstLogNplmnMsg->astNPlmnList[i], &pstDPlmnNPlmnCfgInfo->astNPlmnList[i], sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));
    }

    pstLogNplmnMsg->usNplmnListNum = pstDPlmnNPlmnCfgInfo->usNplmnListNum;

    pstLogNplmnMsg->stMsgHeader.ulLength = sizeof(pstLogNplmnMsg->stMsgHeader.ulMsgName)
                                      + sizeof(pstLogNplmnMsg->usNplmnListNum)
                                      + (pstLogNplmnMsg->usNplmnListNum * sizeof(NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU));

    DIAG_TraceReport(pstLogNplmnMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstLogNplmnMsg);
    /* ========================== NPLMN LIST���� ========================== */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_HighPrioPlmnSearch
 ��������  : �����ȼ�����״̬������ʱ�������б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList - �����ȼ������б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��9��9��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������

 3.��    ��   : 2012��5��17��
   ��    ��   : zhoujun 40661
   �޸�����   : ̩��AIS����

 4.��    ��   : 2014��1��22��
   ��    ��   : w00167002
   �޸�����   : SVLTE������:MMC�������е�ѡ���б�������ڸ����ȼ�����ʹ�ã�
                 Ҳ�������ڴ洢ѡ��״̬���е������б���Ϣ��
                �����ʼ��Ϊ�����ȼ�����������Ҫ��ʾָʾ��ǰ��ѡ�����͡�
 5.��    ��   : 2014��6��13��
   ��    ��   : b00269685
   �޸�����   : ����3gpp2,��ѡ���粻����UPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_HighPrioPlmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT8                           uc3GPPUplmnNotPrefFlg;

    uc3GPPUplmnNotPrefFlg = NAS_MML_Get3GPP2UplmnNotPrefFlg();

    NAS_MMC_SetPlmnSelectionListType(NAS_MMC_STORE_HIGH_PRIO_PLMN_SELECTION_LIST);

    /* Modified by z40661 for ̩��AIS���� 2012-05-17, begin */
    if ( VOS_TRUE == NAS_MMC_IsAisRoamingEffect())
    {
        /* ��ѡ���б�����������Ҫ��������������*/
        NAS_MMC_AddAisRoamPlmnInPlmnSelectionList(pstHighPrioPlmnSearchListInfo);
    }
    /* Modified by z40661 for ̩��AIS���� 2012-05-17, end */

    /* ���EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstHighPrioPlmnSearchListInfo);

    if ((NAS_MMC_REG_CONTROL_BY_3GPP_MMC == NAS_MMC_GetRegCtrl())
     || (VOS_FALSE == uc3GPPUplmnNotPrefFlg))
    {
        /* ���UPLMN��OPLMN */
        NAS_MMC_AddUOPlmnInPlmnSelectionList(pstHighPrioPlmnSearchListInfo);
    }
    else
    {
        /* ���OPLMN */
        NAS_MMC_AddOPlmnInPlmnSelectionList(pstHighPrioPlmnSearchListInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnRatSupported
 ��������  : �ж�PLMN�ĸ����뼼����ǰ�Ƿ�֧��(�Ƿ���syscfg����֧�ֵ�)
 �������  : NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU   *pstPlmnInfo
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��֧��
             VOS_FALSE:֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��23��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnRatSupported(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo
)
{
    VOS_UINT32                         i;

    for (i = 0; i < pstPlmnInfo->ucRatNum; i++)
    {
        if (VOS_TRUE == NAS_MML_IsNetRatSupported(pstPlmnInfo->astPlmnRatInfo[i].enRatType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsHighPrioPlmnSameCountry
 ��������  : ��ȡ�ø����ȼ������Ƿ���������
 �������  : pstHighPrioPlmnInfo: �����ȼ�PLMN
             pstVPlmnId: VPLMN��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��������
             VOS_FALSE:����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��9��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��11��
   ��    ��   : w00166186
   �޸�����   : AT&T&DCM��Ŀ

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsHighPrioPlmnSameCountry(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstHighPrioPlmnInfo,
    NAS_MML_PLMN_ID_STRU                                   *pstVPlmnId
)
{
    VOS_UINT32                                      ulIsSameCountryFlg;
    NAS_MML_BG_SEARCH_CFG_INFO_STRU                 *pstBgSearchCfg = VOS_NULL_PTR;

    NAS_MMC_HPLMN_SEARCH_REGARDLESS_MCC_CTX_STRU    *pstBgSearchRegardlessMccCtx = VOS_NULL_PTR;

    pstBgSearchCfg              = NAS_MML_GetBgSearchCfg();

    pstBgSearchRegardlessMccCtx = NAS_MML_GetBgSearchRegardlessMccCtx();


    ulIsSameCountryFlg  = NAS_MML_ComparePlmnMcc(pstVPlmnId->ulMcc, pstHighPrioPlmnInfo->stPlmnId.ulMcc);

    /* ucSpecialRoamFlg�ر�ʱ,��������벻ͬ,����VOS_FALSE��
       ����ucSpecialRoamFlg��ʱ,plmn����Ϊplmn����ΪUPLMN��OPLMN,���������
       ��ͬ����VOS_FALSE,EHPLMN�޴�����*/

    if ((VOS_TRUE == pstBgSearchCfg->ucSpecialRoamFlg)
     && (NAS_MMC_PLMN_TYPE_HPLMN == pstHighPrioPlmnInfo->enPlmnType))
    {
        return VOS_TRUE;
    }

    /* ��ǰ�������ڶ��Ƶ�BG�Ѳ����ǹ�������б��� */
    if (VOS_TRUE == NAS_MML_IsMccInDestMccList(pstVPlmnId->ulMcc, pstBgSearchRegardlessMccCtx->ucCustomMccNum, pstBgSearchRegardlessMccCtx->aulCostumMccList))
    {
        return VOS_TRUE;
    }

    return ulIsSameCountryFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareVPlmnPrioWithHighPrioPlmn
 ��������  : �Ƚ�VPLMN�͸����ȼ�������������ȼ��Ƿ���ͬ
 �������  : pstVPlmn:�����ȼ�����֮ǰפ����VPLMN��Ϣ
             enRat:VPLMN�Ľ��뼼��
             pstEplmnList:�����ȼ�����֮ǰפ��VPLMN�ĵ�ЧPLMN��Ϣ
             pstHighPrioPlmnInfo: �����ȼ�PLMN
 �������  : ��
 �� �� ֵ  : VOS_TRUE:VPLMN�͸����ȼ��������ȼ���ͬ
             VOS_FALSE:VPLMN�͸����ȼ��������ȼ���ͬ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��9��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��11��24��
   ��    ��   : w00167002
   �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
               ����ΪNAS_MML_IsSimPlmnIdInDestBcchPlmnList,��ȷ����ıȽ����ͣ�
               ������ܵ��±Ƚϳ���
  3.��    ��   : 2012��5��24��
    ��    ��   : l00171473
    �޸�����   : DTS2012052404408,פ��HPLMNʱ,������BG��
 3.��    ��   : 2012��5��26��
   ��    ��   : z00161729
   �޸�����   : V7R1C50 GUL�������޸�
 4.��    ��   : 2014��6��17��
   ��    ��   : z00234330
   �޸�����   : PCINT����
*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareVPlmnPrioWithHighPrioPlmn(
    NAS_MML_PLMN_ID_STRU                                   *pstVPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnList,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstHighPrioPlmnInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIsPlmnInEplmnList;
    VOS_UINT32                          ulIsPlmnRatSupported;
    VOS_UINT32                          ulIsEPlmnListValid;

    ulIsPlmnInEplmnList = VOS_FALSE;

    ulIsEPlmnListValid  = VOS_FALSE;

    /* �ж�EPLMN�б��Ƿ�ΪVPLMN�ĵ�ЧPLMN�б�,����֮ǰע��ɹ�,��ѡ�������ֹ����,��ʱEPLMN�б�Ϊ��ǰ�����EPLMN�б� */
    if (pstEplmnList->ucEquPlmnNum != 0)
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstVPlmnId, &(pstEplmnList->astEquPlmnAddr[0])))
        {
            ulIsEPlmnListValid = VOS_TRUE;
        }
    }

    /* �жϸ����ȼ�����Ľ��뼼���Ƿ�֧��,��������ȼ�������EPLMN���ҽ��뼼��
       ��ǰ֧�֣��򷵻�VOS_TRUE,��ģʱEPLMN���ֽ��뼼�� */
    ulIsPlmnRatSupported = NAS_MMC_IsPlmnRatSupported(pstHighPrioPlmnInfo);

    /* ����23.122 4.4.3.3:In the case
    that the mobile has a stored "Equivalent PLMNs" list the mobile shall
    only select a PLMN if it is of a higher priority than those of the same
    country as the current serving PLMN which are stored in the "Equivalent
    PLMNs" list,��ʱ����Ҫ����,������ȼ��������Ѿ���EPLMN�б��з���VOS_TRUE,
    EPLMN�Ǵ������±�1��ʼ��ŵģ������±�0��ŵ���RPLMN */
    if (VOS_TRUE == ulIsEPlmnListValid)
    {
        ulIsPlmnInEplmnList = NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&(pstHighPrioPlmnInfo->stPlmnId),
                                                         pstEplmnList->ucEquPlmnNum - 1,
                                                         &pstEplmnList->astEquPlmnAddr[1]);
    }

    if ((VOS_TRUE == ulIsPlmnInEplmnList)
     && (VOS_TRUE == ulIsPlmnRatSupported))
    {
        return VOS_TRUE;
    }

    /* h) If the PLMN of the highest priority PLMN/access technology combination
    available is the current VPLMN,or one of the PLMNs in the ""Equivalent PLMNs""
    list,the MS shall remain on the current PLMN/access technology combination. */
    /* ��ǰפ��������PLMN ID��������ȼ�������һ��,
       �Ҹø����ȼ�����֧�ֵĽ��뼼����ǰ֧�ַ���VOS_TRUE */
    if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstVPlmnId, &(pstHighPrioPlmnInfo->stPlmnId)))
    {
        /* ���VPLMN��HPLMN, ��ʹ��ǰ�Ľ��뼼����������ȼ���ͬҲ��Ϊ����������ȼ� */
        if (VOS_TRUE == NAS_MMC_IsCampOnHPlmn())
        {
            return VOS_TRUE;
        }

        for (i = 0; i < pstHighPrioPlmnInfo->ucRatNum; i++)
        {
            if (pstHighPrioPlmnInfo->astPlmnRatInfo[i].enRatType == enRat)
            {
                return VOS_TRUE;
            }
        }

        /* If the PLMN of the highest priority PLMN/access technology combination
          available is the current VPLMN,or one of the PLMNs in the ""Equivalent PLMNs"" list,
          the MS shall remain on the current PLMN/access technology combination.
          ��VPLMN��ͬ�������������ȼ���������ڵ�ǰ���绷���д��ڣ���VPLMN��������ȼ�������
          ��PLMN��ͬ�������磺VPLMNΪG��23002��USIM����������ȼ�����ΪW��23002��״̬
          ΪSEARCHED_EXIST������Ϊ��פ����������ȼ�������*/
        for (i = 0; i < pstHighPrioPlmnInfo->ucRatNum; i++)
        {
            /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
            if ((VOS_TRUE ==  NAS_MML_IsNetRatSupported(pstHighPrioPlmnInfo->astPlmnRatInfo[i].enRatType))
             && (NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstHighPrioPlmnInfo->astPlmnRatInfo[i].enNetStatus))
            /* Modified by z00234330 for PCLINT����, 2014-06-24, end */
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextSearchHighPrioPlmn
 ��������  : ��ȡ��һ����Ҫ�����ĸ����ȼ�����
 �������  : pstHighPrioPlmnSearchListInfo:��Ҫ�����ĸ����ȼ��б�
             pstVPlmn:�����ȼ�����֮ǰפ����VPLMN��Ϣ
             pstEplmnList:�����ȼ�����֮ǰפ��VPLMN�ĵ�ЧPLMN��Ϣ
 �������  : pstHighPrioPlmnInfo: �����ȼ�PLMN
 �� �� ֵ  : VOS_TRUE:��ȡ�ɹ�
             VOS_FALSE:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��9��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��2��22��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search����:פ��VPLMNΪHPLMNʱ���Ƚ����ȼ�
 3.��    ��   : 2014��4��10��
   ��    ��   : w00242748
   �޸�����   : DTS2014040905679:���뼼��˳��030201����ǰפ����GSM�ϣ�
                �����ȼ����뼼��HPLMN����Lʧ�ܣ�����W�ɹ����ɹ�ע����ٴ�
                ���������ȼ����뼼��HPLMNʱ����ʱ��ʱ������ȷ��
 4.��    ��   : 2015��2��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
 5.��    ��   : 2015��11��23��
   ��    ��   : z00359541
   �޸�����   : DTS2015111706562:TAU������#17�ܾ�5��DISABLE LTE������������
                ��ENABLE LTE�����ֻᷢ��TAU������#17�ܾ���TAU�ڼ��ղ�������Ѱ��
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextSearchHighPrioPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchListInfo,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstHighPrioPlmnInfo,
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstVPlmn,
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsPlmnSearchingAllowed;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnSelectionPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulCampHplmnFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulIsPlmnSupportDam;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
    /* Added by c00318887 for ��ֲT3402 , 2015-6-23, begin */
    VOS_UINT8                                               ucHighRatBgProc;
    /* Added by c00318887 for ��ֲT3402 , 2015-6-23, end*/
    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();
#endif


    ulCampHplmnFlg              = NAS_MML_ComparePlmnIdWithHplmn(&pstVPlmn->stPlmnId);

    /* ��ȡ��ǰ���뼼�����ȼ���Ϣ */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    for ( i = 0 ; i < pstHighPrioPlmnSearchListInfo->usSearchPlmnNum; i++ )
    {
        pstPlmnSelectionPlmnInfo = &(pstHighPrioPlmnSearchListInfo->astPlmnSelectionList[i]);

        /* ��PLMN��VPLMN�������Ƿ���ͬ,�������ͬ,�򲻽������� */
        if ( VOS_FALSE == NAS_MMC_IsHighPrioPlmnSameCountry(pstPlmnSelectionPlmnInfo,
                                                                 &pstVPlmn->stPlmnId))
        {
            continue;
        }

        /* ��ǰVPLMN��HPLMN,HPLMN��BG�ѱȽ�����,��Ҫ���⴦�� */
        if (VOS_TRUE == ulCampHplmnFlg)
        {
            /* ��ȡ���ĸ����ȼ�PLMN����HPLMN������ */
            if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(&pstPlmnSelectionPlmnInfo->stPlmnId))
            {
                continue;
            }
        }
        else
        {
            /* �Ǹ����ȼ�RAT��HPLMN����ʱ,�Ƚ�VPLMN�͸����ȼ��������ȼ��Ƿ���ͬ�������ͬ����VOS_FALSE */
            if (VOS_TRUE == NAS_MMC_CompareVPlmnPrioWithHighPrioPlmn(&pstVPlmn->stPlmnId,
                                                                      pstVPlmn->enRat, pstEplmnList, pstPlmnSelectionPlmnInfo))
            {
                return VOS_FALSE;
            }
        }


        /* ��SYSCFG���õĽ��뼼�����ȼ����β���,����Ҫ�����ĵ�ǰ�ĸ����ȼ�PLMNʱ���˳� */
        for (k = 0; k < pstPrioRatList->ucRatNum; k++)
        {
            /* ����SYSCFG���ú͸�Plmn֧�ֵĽ��뼼����ȡ��plmn Id�ͽ��뼼���Լ�����״̬ */
            for (j = 0; j < pstPlmnSelectionPlmnInfo->ucRatNum; j++)
            {
                /* ������뼼��֧����״̬��Ϊδ�����������Ѵ��� */
                if (pstPrioRatList->aucRatPrio[k] == pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType)
                {
                    ulIsPlmnSearchingAllowed = NAS_MMC_IsPlmnSearchingAllowed_PlmnSelectionStrategy(&(pstPlmnSelectionPlmnInfo->stPlmnId),
                                                                                         pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType,
                                                                                         pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enNetStatus,
                                                                                         VOS_FALSE);
                    if (VOS_FALSE == ulIsPlmnSearchingAllowed)
                    {
                        /* �洢�Ľ��뼼���������ظ� */
                        break;
                    }

#if (FEATURE_ON == FEATURE_LTE)
                    /* �Ѿ�Disable L,�Ҹ����ȼ�������lte�ģ���DAM������Ч��bg��lte�����磬��enable lte */
                    if (((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == NAS_MML_GetLteCapabilityStatus())
                      || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus))
                      && (NAS_MML_NET_RAT_TYPE_LTE == pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType))
                    {
                        /* ���֮ǰdisable lte��������֧��DAM�����磬�ҽ�ֹ���뼼�������б�����9014 nvδ������
                          ������enable lte,AT&T LTE-BTR-1-1840����Ҫ��ֻ��ֹ310410 lte���磬����lte������ã�
                          �������ɾ���������������Ҫ���ԣ�����DAM nv����в��� */
                        ulIsPlmnSupportDam = NAS_MML_IsPlmnSupportDam(NAS_MMC_GetDisabledLtePlmnId());

                        if ((VOS_FALSE == NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag())
                          && (VOS_TRUE == ulIsPlmnSupportDam))
                        {
                            continue;
                        }
                        
                        /* Added by c00318887 for ��ֲT3402 , 2015-6-23, begin */
                        ucHighRatBgProc = NAS_MMC_IsHighPrioRatHplmnSearch_BgPlmnSearch();
                        /* �����ȼ�RAT��ENABLE LTE������Ч��bg��lte�����磬��enable lte */
                        if ( (NAS_MML_HIGH_PRIO_RAT_BG_SEARCH_PROC_LTE_NOT_ENABLE_LTE == NAS_MML_GetHighPrioRatBgEnableLteFlag())
                          && (VOS_TRUE == ucHighRatBgProc))
                        {
                            continue;
                        }    
                        /* Added by c00318887 for ��ֲT3402 , 2015-6-23, end */
                        if  (VOS_TRUE == ulCampHplmnFlg)
                        {
                            continue;
                        }
                    }
#endif

                    /* פ��HPLMN���һ�ȡ���ĸ����ȼ�RAT��VPLMN��RATһ����������ȡ�����ȼ������б��е��¸�������PLMN */
                    /* ֱ���ڹ��������б�ʱ���� */

                    pstHighPrioPlmnInfo->stPlmnId                      = pstHighPrioPlmnSearchListInfo->astPlmnSelectionList[i].stPlmnId;
                    pstHighPrioPlmnInfo->ucRatNum                      = 1;
                    pstHighPrioPlmnInfo->astPlmnRatInfo[0].enRatType   = pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enRatType;
                    pstHighPrioPlmnInfo->astPlmnRatInfo[0].enNetStatus = pstPlmnSelectionPlmnInfo->astPlmnRatInfo[j].enNetStatus;

                    /* ��ȡ�ɹ�����VOS_TRUE */
                    return VOS_TRUE;

                }
            }
        }

    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetHighestPrioPlmnFromHighPrioPlmnList
 ��������  : �Ӹ����ȼ��б��еõ�������ȼ�������
 �������  : pstPlmnSelectionListInfo:��Ҫ�����ĸ����ȼ��б�
 �������  : pstHighPrioPlmnInfo: ������ȼ�PLMN
 �� �� ֵ  : VOS_TRUE:��ȡ�ɹ�
             VOS_FALSE:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��24��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetHighestPrioPlmnInHighPrioPlmnList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstHighPrioPlmnInfo
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId = VOS_NULL_PTR;

    /* ȡ�õ�ǰפ����PLMN ID */
    pstCurrCampPlmnId = NAS_MML_GetCurrCampPlmnId();

    for ( i = 0 ; i < pstPlmnSelectionListInfo->usSearchPlmnNum; i++ )
    {
        /* ֻȡ��������ͬ��PLMN */
        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrCampPlmnId->ulMcc, pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId.ulMcc))
        {
            continue;
        }

        /* ���������ȼ�������뼼����֧��,����ȡ��һ�� */
        if (VOS_FALSE == NAS_MMC_IsPlmnRatSupported(&pstPlmnSelectionListInfo->astPlmnSelectionList[i]))
        {
            continue;
        }

        PS_MEM_CPY(pstHighPrioPlmnInfo, &pstPlmnSelectionListInfo->astPlmnSelectionList[i], sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));

        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_DelSpecPlmnWithRatInPlmnList
 ��������  : ���б���ɾ��ָ����PLMN
 �������  :
             NAS_MML_PLMN_ID_STRU                   *pstPlmnId,
             NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enRat,
             NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstPlmnSelectionListInfo
 �������  : pstPlmnSelectionListInfo
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : ��ë/00166186
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_DelSpecPlmnWithRatInPlmnList (
    NAS_MML_PLMN_ID_STRU                   *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* ɾ���ظ���PLMN */
    for (i = 0; i < pstPlmnSelectionListInfo->usSearchPlmnNum; )
    {
        for (j = 0; j < pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum; )
        {
            if ((VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId,
                                                               &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].stPlmnId)))
             && (enRat == pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType))
            {
                /*lint -e961*/
                /* ɾ����Ӧ��RAT */
                (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j]),
                            &(pstPlmnSelectionListInfo->astPlmnSelectionList[i].astPlmnRatInfo[j + 1]),
                            ((pstPlmnSelectionListInfo->astPlmnSelectionList[i]).ucRatNum - j - 1) * sizeof(NAS_MMC_PLMN_RAT_INFO_STRU));
                /*lint +e961*/
                pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum--;

            }
            else
            {
                j++;
            }
        }

        /* ���뼼������Ϊ0ʱ��ɾ����Ӧ��PLMN ID */
        if (0 == pstPlmnSelectionListInfo->astPlmnSelectionList[i].ucRatNum)
        {
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstPlmnSelectionListInfo->astPlmnSelectionList[i]),
                        &(pstPlmnSelectionListInfo->astPlmnSelectionList[i + 1]),
                        (pstPlmnSelectionListInfo->usSearchPlmnNum - i - 1) * sizeof(NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU));
            /*lint +e961*/
            pstPlmnSelectionListInfo->usSearchPlmnNum--;
        }
        else
        {
            i++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddEHPlmnInPlmnSelectionList
 ��������  : �������б��м���EHPLMN��HPLMN
 �������  : pstSearchedPlmnListInfo,���������б�
 �������  : pstPlmnSelectionList,�б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��01��02��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_AddSearchedPlmnListInfoInPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;

    if (VOS_NULL_PTR == pstSearchedPlmnListInfo)
    {
        return;
    }

    /* ���������AREA_LOST��Ϣ���ϱ�������ģ���������ѡ���б� */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (NAS_MML_NET_RAT_TYPE_BUTT == pstSearchedPlmnListInfo[i].enRatType)
        {
            continue;
        }

        stPrioRatList.ucRatNum      = 1;
        stPrioRatList.aucRatPrio[0] = pstSearchedPlmnListInfo[i].enRatType;

        /* ���������������ѡ���б� */
        for (j = 0; j < pstSearchedPlmnListInfo[i].ulHighPlmnNum; j++)
        {
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstSearchedPlmnListInfo[i].astHighPlmnList[j]),
                                                   NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }

        /* ���������������ѡ���б� */
        for (j = 0; j < pstSearchedPlmnListInfo[i].ulLowPlmnNum; j++)
        {
            NAS_MMC_AddSpecPlmnInPlmnSelectionList(&(pstSearchedPlmnListInfo[i].astLowPlmnList[j].stPlmnId),
                                                   NAS_MMC_PLMN_TYPE_AVAIL_PLMN,
                                                   &stPrioRatList,
                                                   pstPlmnSelectionListInfo);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSpecRatCoverageTypeInSearchedPlmnList
 ��������  : �������б��л�ȡָ��RAT�ĸ�������
 �������  : pstSearchedPlmnListInfo,���������б�
             enRatType;ָ���Ľ��뼼������
 �������  : penCoverType,���뼼����������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��11��06��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_GetSpecRatCoverageTypeInSearchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRatType,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8                       *penCoverType
)
{
    VOS_UINT32                                              i;

    /* ���������AREA_LOST��Ϣ���ϱ�������ģ���������ѡ���б� */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRatType == pstSearchedPlmnListInfo[i].enRatType)
        {
            *penCoverType = pstSearchedPlmnListInfo[i].enCoverType;
            break;
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList
 ��������  : �������б��л�ȡָ��RAT�ĸ�������
 �������  : pstSearchRatInfo,��������RAT�б�
             enRatType;ָ���Ľ��뼼������
 �������  : penCoverType,���뼼����������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��11��06��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MMC_COVERAGE_TYPE_ENUM_UINT8 NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRatType
)
{
    VOS_UINT32                                              i;

    /* ���������AREA_LOST��Ϣ���ϱ�������ģ���������ѡ���б� */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (enRatType == pstSearchRatInfo[i].enRatType)
        {
            return pstSearchRatInfo[i].enCoverageType;
        }
    }

    return NAS_MMC_COVERAGE_TYPE_BUTT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedNcellSearch
 ��������  : �ж��Ƿ���Ҫ����ncell����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����ncell������VOS_FALSE:����Ҫ����ncell����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 2.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL������
*****************************************************************************/
VOS_UINT8  NAS_MMC_IsNeedNcellSearch(VOS_VOID)
{
    VOS_UINT32                          ulCurNcellSearchTimerCount;
    VOS_UINT32                          ulTotalNcellSearchTimerCount;
    VOS_UINT8                           ucNcellSearchFlag;


    VOS_UINT8                           ucNcellSearchTimerLen;

    VOS_UINT8                           ucPsAttachAllowFlag;
    VOS_UINT8                           ucCsAttachAllowFlag;

    ulCurNcellSearchTimerCount   = NAS_MMC_GetCurNcellSearchTimerCount_OnPlmn();
    ucNcellSearchFlag            = NAS_MMC_GetNcellSearchFlag();
    ulTotalNcellSearchTimerCount = 0;
    ucPsAttachAllowFlag          = NAS_MML_GetPsAttachAllowFlg();
    ucCsAttachAllowFlag          = NAS_MML_GetCsAttachAllowFlg();

    /* �����ǰ�����Ĵ���������available ��ʱ���ĵ�һ�δ���,ʹ�õ�һ��ʱ��,����ʹ�õڶ��ε� */
    if (NAS_MMC_OOS_PHASE_ONE == NAS_MMC_GetOosPhaseNum())
    {
        ucNcellSearchTimerLen        = NAS_MMC_GetNcellSearchFirstTimerLen();

        if (0 != ucNcellSearchTimerLen)
        {
            ulTotalNcellSearchTimerCount = ((NAS_MMC_GetPhaseOnePeriodicSleepTimerLen()) / ucNcellSearchTimerLen);
        }
    }
    else
    {
        ucNcellSearchTimerLen        = NAS_MMC_GetNcellSearchSecondTimerLen();

        if (0 != ucNcellSearchTimerLen)
        {
            ulTotalNcellSearchTimerCount = ((NAS_MMC_GetPhaseTwoPeriodicSleepTimerLen()) / ucNcellSearchTimerLen);
        }
    }

    /* 1��svlte ���Կ���
       2��֧��ncell��������nv����
       3��modem1 gas�ϱ�����t��l������Ƶ����Ϣ����������Ϊ0ʱҲ������ncell�Ѷ�ʱ��
       4����ǰΪPS attach not allow/cs attach not allow,��ֹ������������ù���
       5��ncell��������δ�ﵽn(��M�׶ε��������ʱ��/ NcellQuickSearchTimer)��
          ��available��ʱ��ʱ������Ϊncell����ʱ�� */
    if ((VOS_TRUE == ucNcellSearchFlag)
     && (ulCurNcellSearchTimerCount < ulTotalNcellSearchTimerCount)
     && (VOS_FALSE == ucPsAttachAllowFlag)
     && (VOS_FALSE == ucCsAttachAllowFlag))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedChangeNcellSearchRatOrder
 ��������  : �ж�ncell����ʱ���Ƿ���ҪT L����˳���򣬷�ֹʼ������ͬһ��RAT��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����VOS_FALSE:����Ҫ���з���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��5��28��
   ��    ��   : x00203213
   �޸�����   : SVLTE֧��NCELL����˳��ת
 *****************************************************************************/

VOS_UINT8 NAS_MMC_IsNeedChangeNcellSearchRatOrder(VOS_VOID)
{
    VOS_UINT8                                               ucCampOnHighRatFlag;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstRatPrioList        = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCampOnRatType;
    VOS_UINT8                                               ucSvlteSupportFlag;
    VOS_UINT8                                               ucPsTransferOffAreaModeFlag;
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 enSpecPlmnSearchState;

    ucCampOnHighRatFlag             = VOS_FALSE;
    ucSvlteSupportFlag                  = NAS_MML_GetSvlteSupportFlag();
    ucPsTransferOffAreaModeFlag	= NAS_MML_GetPsTransferOffAreaModeFlag();
    enSpecPlmnSearchState          = NAS_MMC_GetSpecPlmnSearchState();

    /* ��ȡ���ȼ��б� */
    pstRatPrioList     = NAS_MML_GetMsPrioRatList();

    /*��ǰ֧��һ��RAT������Ҫ��ת*/
    if (2 > pstRatPrioList->ucRatNum)
    {
         return VOS_FALSE;
    }


    /* ��ȡפ��RAT */
    enCampOnRatType = NAS_MML_GetCurrNetRatType();

    /*פ���ڷ�������ȼ������ϲ�����Ҫ��ת*/
    if ((pstRatPrioList->aucRatPrio[pstRatPrioList->ucRatNum -1] != enCampOnRatType )
    &&  ( NAS_MML_NET_RAT_TYPE_BUTT != enCampOnRatType ))
    {
         ucCampOnHighRatFlag = VOS_TRUE;
    }

    /*��������������Ҫ����:
          1��svlte ���Կ���
          2��֧����������NV ����
          3����ǰ�ڸ����ȼ���RAT ��פ��
          4 ����ǰ�Ѿ����פ��
    */
    if ((VOS_TRUE == ucSvlteSupportFlag)
          && (VOS_TRUE == ucPsTransferOffAreaModeFlag)
          && (VOS_TRUE == ucCampOnHighRatFlag)
          && (NAS_MMC_SPEC_PLMN_SEARCH_STOP == enSpecPlmnSearchState))
    {
        return VOS_TRUE;
    }

   return VOS_FALSE;

}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsLtePlmnSearchingAllowed_PlmnSelectionStrategy
 ��������  : �ж�LTE��PLMN ID�Ƿ���������
 �������  : pstPlmnId:��Ҫ�жϵ�PLMN ID
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : PLMN ID��������
             VOS_FALSE : PLMN ID����������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2012��03��8��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��8��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559 ������SIM��ʱ���ó�LTE only����ȥ��Lģ������ʱ����ʱ����Lģ
 3.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search���Ե���:BG��ʱ����disable L�����������L������
 4.��    ��   : 2015��9��19��
   ��    ��   : y00346957
   �޸�����   : add for DTS2015070910885
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsLtePlmnSearchingAllowed_PlmnSelectionStrategy(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;
    VOS_UINT32                                              ulEnableRoaming;
    VOS_UINT32                                              aulComparedMccList[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER];
    VOS_UINT32                                              ulState;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;

    enSimType = NAS_MML_GetSimType();

    ulEnableRoaming   = VOS_TRUE;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* �жϵ�ǰѡ���PLMN�Ƿ��������ȼ�Ҫ�� */
    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(pstPlmnId))
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_IsLtePlmnSearchingAllowed_PlmnSelectionStrategy:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                             pstPlmnId->ulMcc, pstPlmnId->ulMnc);
        return VOS_FALSE;
    }
#endif

    /* ��ֹLTE��������ʱ */
    if (VOS_FALSE == NAS_MML_GetLteRoamAllowedFlg())
    {
        NAS_MML_GetRoamEnabledMccList(aulComparedMccList);

        /* �жϸ�PLMN ID��MCC�Ƿ�������פ����MCC�б��� */
        ulEnableRoaming = NAS_MML_IsMccInDestMccList(pstPlmnId->ulMcc, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMccList);
    }

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    /* ������������,����Ҫ����LTE������:
        1)��ǰ����Ľ��뼼��ΪL�ҵ�ǰPS����Ч
        2)��ǰ����Ľ��뼼��ΪL�ҵ�ǰDISABLE LTE
        3)LTE��ֹ��������
        4)������ΪSIM��:��Ӧ�ĳ���Ϊ:SIM��ʱ���ó�LTE only����ȥ��Lģ������ʱ����ʱ����Lģ
    */
    if ((VOS_FALSE                             == NAS_MML_GetSimPsRegStatus())
     || (VOS_FALSE == ulEnableRoaming)
     || (NAS_MML_SIM_TYPE_SIM == enSimType))
    {
        NAS_NORMAL_LOG2(WUEPS_PID_MMC, "NAS_MMC_IsLtePlmnSearchingAllowed_PlmnSelectionStrategy ulEnableRoaming,enSimType",ulEnableRoaming,enSimType);        
        
        return VOS_FALSE;
    }

    ulState = NAS_MMC_GetFsmTopState();

    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLCapabilityStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLCapabilityStatus))
    {
        /* BG���������л�ȡ�¸������ȼ�����ʱ������disable Lģ������ */
        if ((NAS_MMC_FSM_BG_PLMN_SEARCH                             == NAS_MMC_GetCurrFsmId())
         && ((NAS_MMC_BG_PLMN_SEARCH_STA_INIT                        == ulState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF == ulState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF == ulState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF == ulState)))
        {
            /* PS��������ע��,����Ҫ���� Enable L */
            if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
            {
                return VOS_FALSE;
            }

            /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
            if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
            {
                return VOS_FALSE;
            }

            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#endif


/*****************************************************************************
 �� �� ��  : NAS_MMC_InitPlmnSelectionList_HighPrioPlmnSearch
 ��������  : �����ȼ�����״̬������ʱ�������б��ʼ��
 �������  : ��
 �������  : pstPlmnSelectionList - �����ȼ������б���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��20��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_InitPlmnSelectionList_HighPrioRatHplmnSearch(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchListInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo;

    NAS_MMC_SetPlmnSelectionListType(NAS_MMC_STORE_HIGH_PRIO_PLMN_SELECTION_LIST);

    /* Added by w00176964 for coverity����, 2014-3-10, begin */
    PS_MEM_SET(&stPlmnInfo, 0x0, sizeof(stPlmnInfo));
    /* Added by w00176964 for coverity����, 2014-3-10, end */

    /* ��ȡEHPLMN */
    pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();


    for (i = 0; i< pstEHPlmnInfo->ucEhPlmnNum; i++)
    {
        /* ����SIM���Ľ��뼼����Ϣ������ID���������͹���ѡ���б���PLMN ID��Ϣ */
        NAS_MMC_BuildPlmnSelectionPlmnInfo_ForHighPrioRatHplmnSearch(NAS_MMC_PLMN_TYPE_HPLMN,
                                           &(pstEHPlmnInfo->astEhPlmnInfo[i].stPlmnId),
                                           &stPlmnInfo);

        /* ��ӵ������б� */
        if (VOS_FALSE == NAS_MMC_IsPlmnInSearchList(stPlmnInfo, pstHighPrioPlmnSearchListInfo))
        {
            NAS_MMC_AppendPlmnInPlmnSelectionList(&stPlmnInfo, pstHighPrioPlmnSearchListInfo);
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnInSearchList
 ��������  : ���ָ����Plmn�Ƿ��ڹ���������б���
 �������  : stPlmnId:PLMN ID
            pstHighPrioPlmnSearchListInfo: ����������б�
 �������  : pstPlmnInfo,֧�ֵĽ��뼼������
 �� �� ֵ  : VOS_TRUE: �Ѿ�����
            VOS_FALSE: ������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��27��
   ��    ��   : f00261443
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��9��29��
   ��    ��   : b00269685
   �޸�����   : DTS2014092900118�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnInSearchList(
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                   stPlmnInfo,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstHighPrioPlmnSearchListInfo
)
{
    VOS_UINT32                          ulPlmnNum;
    NAS_MML_PLMN_ID_STRU                stPlmnId;

    PS_MEM_SET(&stPlmnId, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    for (ulPlmnNum = 0; ulPlmnNum < pstHighPrioPlmnSearchListInfo->usSearchPlmnNum; ulPlmnNum++)
    {
        PS_MEM_CPY(&stPlmnId, &(pstHighPrioPlmnSearchListInfo->astPlmnSelectionList[ulPlmnNum].stPlmnId), sizeof(stPlmnId));
        if ((stPlmnId.ulMcc == stPlmnInfo.stPlmnId.ulMcc)
         && (stPlmnId.ulMnc == stPlmnInfo.stPlmnId.ulMnc))
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildPlmnSelectionPlmnInfo_ForHighPrioRatHplmnSearch
 ��������  : ����ѡ���б��е���PLMN��Ϣ
 �������  : enPlmnType:��������
            pstPlmnId:PLMN ID
 �������  : pstPlmnInfo,֧�ֵĽ��뼼������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��2��27��
   ��    ��   : f00261443
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��4��10��
   ��    ��   : w00242748
   �޸�����   : DTS2014040905679:���뼼��˳��030201����ǰפ����GSM�ϣ�
                �����ȼ����뼼��HPLMN����Lʧ�ܣ�����W�ɹ����ɹ�ע����ٴ�
                ���������ȼ����뼼��HPLMNʱ����ʱ��ʱ������ȷ��

*****************************************************************************/
VOS_VOID NAS_MMC_BuildPlmnSelectionPlmnInfo_ForHighPrioRatHplmnSearch(
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType,
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnInfo
)
{
    VOS_UINT8                           ucRatNum;
    VOS_UINT8                           i;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPlmnRatPrio = VOS_NULL_PTR;

    ucRatNum                = 0x0;
    pstPlmnRatPrio = NAS_MML_GetMsPrioRatList();

    PS_MEM_CPY(&pstPlmnInfo->stPlmnId, pstPlmnId, sizeof(NAS_MML_PLMN_ID_STRU));
    pstPlmnInfo->enPlmnType = enPlmnType;

    for (i = 0; i < pstPlmnRatPrio->ucRatNum; i++)
    {
        /* ��������ȼ����뼼��HPLMN�б�ʱ��ֱ�ӽ����ȼ��ȵ�ǰ���뼼���͵Ľ��뼼�����˵� */
        if ( pstPlmnRatPrio->aucRatPrio[i] == NAS_MML_GetCurrNetRatType() )
        {
            break;
        }

        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = pstPlmnRatPrio->aucRatPrio[i];
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_UNKNOWN;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
        ucRatNum++;

    }

    pstPlmnInfo->ucRatNum = ucRatNum;
    /* ����ʣ��λ�ø�ֵΪ��Чֵ */
    for (; ucRatNum < NAS_MML_MAX_RAT_NUM; ucRatNum++)
    {
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enRatType   = NAS_MML_NET_RAT_TYPE_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enNetStatus = NAS_MMC_NET_STATUS_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].enQuality   = NAS_MMC_NET_QUALITY_BUTT;
        pstPlmnInfo->astPlmnRatInfo[ucRatNum].lRscp       = NAS_MML_UTRA_RSCP_UNVALID;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsPlmnIdInSearchedPlmnList
 ��������  : ���ָ����Plmn�Ƿ��ڹ���������б���
 �������  : stPlmnId:PLMN ID
             pstSearchedPlmnListInfo: ����������б�
 �������  : pstPlmnInfo,֧�ֵĽ��뼼������
 �� �� ֵ  :VOS_TRUE: �Ѿ�����
            VOS_FALSE: ������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��4��4��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsPlmnIdInSearchedPlmnList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
)
{
    VOS_UINT32                          ulHighPlmnIndex;
    VOS_UINT32                          ulLowPlmnIndex;
    VOS_UINT8                           ucRatIndex;

    if (VOS_NULL_PTR == pstSearchedPlmnListInfo)
    {
        return VOS_FALSE;
    }

    for (ucRatIndex = 0; ucRatIndex < NAS_MML_MAX_RAT_NUM; ucRatIndex++)
    {
        if (NAS_MML_NET_RAT_TYPE_BUTT == pstSearchedPlmnListInfo[ucRatIndex].enRatType)
        {
            continue;
        }

        for (ulHighPlmnIndex = 0; ulHighPlmnIndex < pstSearchedPlmnListInfo[ucRatIndex].ulHighPlmnNum; ulHighPlmnIndex++)
        {
            if ((pstPlmnId->ulMcc == pstSearchedPlmnListInfo[ucRatIndex].astHighPlmnList[ulHighPlmnIndex].ulMcc)
             && (pstPlmnId->ulMnc == pstSearchedPlmnListInfo[ucRatIndex].astHighPlmnList[ulHighPlmnIndex].ulMnc))
            {
                return VOS_TRUE;
            }
        }

        for (ulLowPlmnIndex = 0; ulLowPlmnIndex < pstSearchedPlmnListInfo[ucRatIndex].ulLowPlmnNum; ulLowPlmnIndex++)
        {
            if ((pstPlmnId->ulMcc == pstSearchedPlmnListInfo[ucRatIndex].astLowPlmnList[ulLowPlmnIndex].stPlmnId.ulMcc)
             && (pstPlmnId->ulMnc == pstSearchedPlmnListInfo[ucRatIndex].astLowPlmnList[ulLowPlmnIndex].stPlmnId.ulMnc))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}


/*lint -restore */


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateExistRplmnOrHplmnFlag_InitPlmnSelectionList
 ��������  : ��ʼ���б�ʱ�����Ƿ����RPLMN��HPLMN��־
 �������  : NAS_MML_PLMN_WITH_RAT_STRU                             *pstSearchedPlmn
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��22��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateExistRplmnOrHplmnFlag_InitPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSearchedPlmn
)
{
    /* PLMN��Чʱ�������±�־ */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&(pstSearchedPlmn->stPlmnId)))
    {
        return;
    }

    /* ��ȡ����λ����Ϣʱ��PLMN��Ӧ�Ĺ�������rplmn��ͬ */
    if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstSearchedPlmn->stPlmnId.ulMcc))
    {
        NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
        return;
    }

    /* ��ȡ����λ����Ϣʱ��PLMN��Ӧ�Ĺ�������hplmn��ͬ */
    if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstSearchedPlmn->stPlmnId.ulMcc))
    {
        NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection
 ��������  : �жϳ�ʼ��ѡ���б�ʱ�Ƿ���Ҫ�������б��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ��������
             VOS_FALSE - ����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��11��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene,
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSearchedPlmn
)
{
    /* ���Կ� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList: Test SIM, No need sort");
        return VOS_FALSE;
    }

    /* ���������Ż������ƹرղ����� */
    if (VOS_FALSE == NAS_MMC_GetRoamPlmnSelectionSortActiveFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList: NV not active, No need sort");
        return VOS_FALSE;
    }

    /* �ֶ�����ģʽ���������Ϣ */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList: Manual Selection Mode, No need sort");
        return VOS_FALSE;
    }

    /* PLMN��Чʱ������DPLMN/UPLMN/OPLMN/AVAILABLE PLMN ���� */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(&(pstSearchedPlmn->stPlmnId)))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList: Invalid PLMN, No need sort");
        return VOS_FALSE;
    }

    /* ��ȡ����λ����Ϣʱ��PLMN��Ӧ�Ĺ������Ƿ��rplmn��hplmn��ͬ */
    if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstSearchedPlmn->stPlmnId.ulMcc))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList: MCC same with RPLMN, No need sort");
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstSearchedPlmn->stPlmnId.ulMcc))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList: MCC same with HPLMN, No need sort");
        return VOS_FALSE;
    }

    /* �����������ƿ�����Ŀǰֻ�п���ѡ����SYSCFG������ѡ�����Ż��ڳ�ʼ���б�ʱ������������
       ������������������ڳ�ʼ���б�ʱ��Ҫ��������� */
    if ((NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON    != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET   != enPlmnSearchScene))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList: Not SwitchON or SYSCFG PLMN Srch Scene, No need sort");
        return VOS_FALSE;
    }

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_InitPlmnSelectionList: return TRUE");

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SortRoamPlmnSelectionList_InitPlmnSelectionList
 ��������  : ��ʼ���б�ʱ�����������������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��11��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SortRoamPlmnSelectionList_InitPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSearchedPlmn,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList  = VOS_NULL_PTR;


    /* �������γ�����syscfg���������������������б�����ԭ������:
     1����������MMA������������������������б�ǰ��,��NPLMN�е����粻��ӣ�
        ֧�ֵ����н��뼼������ӣ���ǰ�����Ľ��뼼������
     2����gastNetworkNameTbl���ҳ�����ǰ����������ͬ�������plmn�������������б�
        ��NPLMN�е����粻��ӣ�֧�ֵ����н��뼼������ӣ���ǰ�����Ľ��뼼������
     3������DPLMN->UPLMN->OPLMN->AVAILABLE PLMN˳������������б��������
    */

    pstPrioRatList  = NAS_MML_GetMsPrioRatList();

    /* ����pstSearchedPlmn����stSearchedExistPlmnInfo */
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));

    enPlmnType  = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(pstSearchedPlmn, pstPlmnSelectionListInfo);

    enNetStatus = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(pstSearchedPlmn, pstPlmnSelectionListInfo);

    if (NAS_MMC_NET_STATUS_BUTT == enNetStatus)
    {
        enNetStatus = NAS_MMC_NET_STATUS_NO_SEARCHED;
    }

    stSearchedExistPlmnInfo.usSearchPlmnNum = 1;
    stSearchedExistPlmnInfo.astPlmnSelectionList[0].stPlmnWithRat.enRat             = pstPrioRatList->aucRatPrio[0];
    stSearchedExistPlmnInfo.astPlmnSelectionList[0].stPlmnWithRat.stPlmnId.ulMcc    = pstSearchedPlmn->stPlmnId.ulMcc;
    stSearchedExistPlmnInfo.astPlmnSelectionList[0].stPlmnWithRat.stPlmnId.ulMnc    = pstSearchedPlmn->stPlmnId.ulMnc;
    stSearchedExistPlmnInfo.astPlmnSelectionList[0].enPlmnType                      = enPlmnType;
    stSearchedExistPlmnInfo.astPlmnSelectionList[0].enNetStatus                     = enNetStatus;


    /* ��DPLMN/UPLMN/OPLMN/AVAILABLE PLMN���ҳ�MCC��ͬ�����磬���������б� */
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    /* ��ʼ���б�����ʱ���õ�ǰsyscfg���õ�������ȼ��Ľ��뼼���������������LTE���ȼ�ʱ�����ܻ�������WCDMA */
    NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(pstPrioRatList->aucRatPrio[0],
                                                              &stSearchedExistPlmnInfo,
                                                              &stNewRoamPlmnSelectionList);

    /* ���Ź����roam�����б���������б�ǰ�� */
    NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSelectionListInfo);

    /* ���øý��뼼�����й�һ������ */
    NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[0], VOS_TRUE);

    /* ��ά�ɲ�,��ѡ���б���� */
    NAS_MMC_LogDplmnNplmnList();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSrchCurrCampHpmnRejByCause13
 ��������  : HPLMN��ע�ᱻ#13��֮���Ƿ���Ҫ����������ǰPLMN WITH RAT
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����������ǰע�ᱻ#13�ܾ���HPLMN
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��9��
    ��    ��   : s00217060
    �޸�����   : DTS2015120709483:ѭ����������MSCC��Ϣ������

*****************************************************************************/
VOS_UINT8  NAS_MMC_IsNeedSrchCurrCampHpmnRejByCause13(VOS_VOID)
{
    VOS_UINT8                           ucKeepSrchHplmnEvenRejByCause13Flg;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegRejCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegRejCause;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbPlmnInfo = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstCurrLai      = VOS_NULL_PTR;

    /* ���û�ָ����������ȫ�ֱ����л�ȡFORBIDEN ROAMING LAS��Ϣ */
    pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();

    enCsRegRejCause = NAS_MML_REG_FAIL_CAUSE_BUTT;
    enPsRegRejCause = NAS_MML_REG_FAIL_CAUSE_BUTT;

    ucKeepSrchHplmnEvenRejByCause13Flg  = NAS_MML_GetKeepSrchHplmnEvenRejByCause13Flg();

    /* �Ż����ԶԲ��Կ�����Ч */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* �Ż�����δ��ʱ�������ѵ�ǰHPLMN */
    if (VOS_FALSE   == ucKeepSrchHplmnEvenRejByCause13Flg)
    {
        return VOS_FALSE;
    }

    /* δפ��HPLMN�򲻼���������ǰPLMN */
    if (VOS_FALSE   == NAS_MMC_IsCampOnHPlmn())
    {
        return VOS_FALSE;
    }

    /* ��ȡ�ڸ�PLMN�ϵ�ע�ᱻ��ԭ��ֵ */
    NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                            NAS_MML_GetCurrNetRatType(),
                                            &enCsRegRejCause,
                                            &enPsRegRejCause);


    /* ��һ����#11�ܾ��򲻼���������ǰHPLMN */
    if ((NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == enCsRegRejCause)
     || (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW == enPsRegRejCause))
    {
        return VOS_FALSE;
    }

    /* ��ȡ��ǰפ����LAI */
    pstCurrLai          = NAS_MML_GetCurrCampLai();

    /* ��ǰפ����PLMN��forb LA�Ƿ���ͬ����ͬʱ��ζ����α��վ��#13�ܾ�����Ҫ������HPLMN;���򲻼����� */
    if ( VOS_TRUE == NAS_MML_IsLaiInDestLaiList(pstCurrLai, pstForbPlmnInfo->ucForbRoamLaNum, pstForbPlmnInfo->astForbRomLaList) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateRegFinishedPlmnNetStatusInPlmnSelectionList
 ��������  : ע�����֮�󣬸��µ�ǰ����״̬�������б���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_UpdateRegFinishedPlmnNetStatusInPlmnSelectionList(
    NAS_MML_PLMN_WITH_RAT_STRU                   *pstPlmnIdWithRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU        *pstPlmnSelectionListInfo
)
{

    /* ѡ��״̬���£�HPLMNע�ᱻ#13�ܾ������Ҫ���ѵ�ǰHPLMN���򲻸��µ�ǰ���������״̬ */
    if (VOS_TRUE == NAS_MMC_IsNeedSrchCurrCampHpmnRejByCause13())
    {
        /* ���µ�ǰ���������״̬Ϊ���������Ҵ��ڣ��ڴ��ָ����ȼ������У��������Ѵ����� */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstPlmnIdWithRat,
                                                NAS_MMC_NET_STATUS_SEARCHED_EXIST,
                                                pstPlmnSelectionListInfo);
    }
    else
    {
        /* ���µ�ǰ���������״̬Ϊ��ע������ڴ��ָ����ȼ������У��������Ѵ����� */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(pstPlmnIdWithRat,
                                                NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                pstPlmnSelectionListInfo);
    }

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


