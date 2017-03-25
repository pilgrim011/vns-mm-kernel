/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcFsmPlmnSelection.c
  �� �� ��   : ����
  ��    ��   : zhoujun /40661
  ��������   : 2011��03��14��
  ����޸�   :
  ��������   : PlmnSelection״̬�������ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��03��14��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ļ�
  2.��    ��   : 2011��7��04��
    ��    ��   : s46746
    �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasMmcFsmPlmnSelectionTbl.h"
#include "NasMmcCtx.h"
#include "NasMmcFsmPlmnSelection.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcTimerMgmt.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmlCtx.h"
#include "NasMmlMsgProc.h"
#include "NasMmcSndMscc.h"
#include "NasMmcProcUsim.h"
#include "NasMmcProcSuspend.h"
#include "NasMmcSndOm.h"
#include "NasMmcProcNvim.h"
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
/* ɾ��ExtAppMmcInterface.h*/
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */
#include "MmcMmInterface.h"
#include "MmcGmmInterface.h"
#include "NasMmcComFunc.h"

/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */
#include "NasUtranCtrlInterface.h"
#include "NasUtranCtrlCtx.h"
#include "NasUsimmApi.h"
#include "NasMmcSndCss.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_PLMN_SELECTION_C

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccPlmnSearchReq_PlmnSelection_Init
 ��������  : PLMNѡ��״̬����ʼ״̬���յ�������������
 �������  : pMsg:ID_MSCC_MMC_PLMN_SEARCH_REQ��Ϣ
             ulEventType
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��22��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������

 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��3��17��
   ��    ��   : l65478
   �޸�����   : DTS2012031907930 �û�ָ������ע��ʧ��#11���¿�����û�з�������
 6.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559 ��������ʱ�����ݿ����͸���Lte�������������SIM������ҪDisable Lte
 7.��    ��   : 2012��12��28��
   ��    ��   : s46746
   �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�Ƿ�֧��LTE�ж�
 8.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 9.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
10.��    ��   : 2013��10��09��
   ��    ��   : l00208543
   �޸�����   : DTS2013100904573
11.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
12.��    ��   : 2014��1��22��
   ��    ��   : w00167002
   �޸�����   : SVLTE������:MMC�ִ�������һ�ֵ������������NO RF�����Ϣ��
13.��    ��   : 2014��2��13��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
14.��    ��   : 2014��4��14��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����ʱ���·���״̬
15.��    ��   : 2015��4��3��
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 10 Modified
16.��    ��   : 2015��5��30��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
17.��    ��   : 2015��6��12��
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 12 Modified
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccPlmnSearchReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    MSCC_MMC_PLMN_SEARCH_REQ_STRU                          *pstMsccPlmnSrchReq = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo    = VOS_NULL_PTR;

    pstMsccPlmnSrchReq = (MSCC_MMC_PLMN_SEARCH_REQ_STRU *)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* �ϱ�AT������ʼ */
    NAS_MMC_SndMsccPlmnSelectStartInd();

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ����MMA��������PLMN */
    NAS_MMC_SaveGeoPlmn_PlmnSelection(pstMsccPlmnSrchReq);

    if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstMsccPlmnSrchReq->enAcqReason)
    {
        /* ���ݳ�����ʼ�������б���Ϣ */
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON,
                                      VOS_NULL_PTR,
                                      pstPlmnSelectionListInfo);
    }
    else if (NAS_MSCC_PIF_ACQ_REASON_OTHER == pstMsccPlmnSrchReq->enAcqReason)
    {
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST,
                                      VOS_NULL_PTR,
                                      pstPlmnSelectionListInfo);
    }
    else if (NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY == pstMsccPlmnSrchReq->enAcqReason)
    {
        pstPlmnListInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                 sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);

        if (VOS_NULL_PTR != pstPlmnListInfo)
        {
            NAS_MMC_InitSearchedPlmnListInfo(pstPlmnListInfo);

            NAS_MMC_ConvertMsccHighPrioPlmnListToMmcPlmnListInfo(&pstMsccPlmnSrchReq->stHighPrioPlmnList,
                                                                pstPlmnListInfo);

            NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH,
                                          pstPlmnListInfo,
                                          pstPlmnSelectionListInfo);

            PS_MEM_FREE(WUEPS_PID_MMC, pstPlmnListInfo);

            /* hsd��������ɺ󣬼�lte�Ѿ������һ��ȫƵ�� */
            NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccPlmnSearchReq_PlmnSelection_Init: invalid acquire reason.");
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* ��ȡ��Ҫ���������缰����뼼�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* ��MM��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

        NAS_MMC_UpdateRegStateSpecPlmnSearch();

        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, begin */
        NAS_MMC_UpdateServiceStateSpecPlmnSearch();
        /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, end */

        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);

#if   (FEATURE_ON == FEATURE_LTE)
        /* ��������ʱ�����ݿ����͸���Lte�������������SIM������ҪDisable Lte */
        /* Modified by s00246516 for L-C��������Ŀ, 2014-02-13, Begin */
        NAS_MMC_DisableLteForSimReason_PlmnSelection();
        /* Modified by s00246516 for L-C��������Ŀ, 2014-02-13, End */
#endif

    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccPlmnSearchReq_PlmnSelection_Init: Get Next Search Plmn fail at switch on.");

        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_Init
 ��������  : PLMNѡ��״̬����ʼ״̬���յ��û�ָ����������
 �������  : pMsg:ID_MSCC_MMC_PLMN_SPECIAL_REQ��Ϣ
             ulEventType
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��7��
   ��    ��   : sunxibo 46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������

 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 4.��    ��   : 2012��06��02��
   ��    ��   : s00217060
   �޸�����   : for CS/PS mode 1, �Ѿ�Disable L, PS����Ч������ע��, Enable L
 5.��    ��   : 2012��6��13��
   ��    ��   : w00176964
   �޸�����   : DTS2012061202962:�ֶ�ģʽ,ָ������ӵ���ֹ�б��,anycell����פ��
                ����,available��ʱ���������κ�������
 6.��    ��   : 2012��10��31��
   ��    ��   : t00212959
   �޸�����   : DTS2012103100827:syscfg ֮���µ���������������ʱ���ϱ�refresh
 7.��    ��   : 2013��01��23��
   ��    ��   : s00217060
   �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
 8.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 9.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
10.��    ��   : 2013��10��09��
   ��    ��   : l00208543
   �޸�����   : DTS2013100904573
11.��    ��   : 2014��1��22��
   ��    ��   : w00167002
   �޸�����   : SVLTE������:MMC�ִ�������һ�ֵ������������NO RF�����Ϣ��

12.��    ��   : 2014��3��1��
   ��    ��   : z00234330
   �޸�����   : DTS2014022805826,ָ������ʱ����״̬�ϱ�����ȷ
13.��    ��   : 2014��4��2��
   ��    ��   : B00269685
   �޸�����   : CS,PS��������ʹ��COPS�ı����磬���������У�����δ����ע��״̬��
                ���������������У�AT+CREG?��ѯ�����Ϊ����״̬���޸�Ϊ����ʱͬ������ע��״̬��

14.��    ��   : 2014��4��11��
   ��    ��   : B00269685
   �޸�����   : CS,PS��������ʹ��COPS�ı����磬���������У�����δ����ע��״̬��
                ���������������У�AT+CREG?��ѯ�����Ϊ��������
                �޸�Ϊ����ʱͬ������ע��״̬��
15.��    ��   : 2014��5��21��
   ��    ��   : w00167002
   �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷�������������.ָ�������ϱ����������
                ѡ�����ͣ���������ѡ������һ�¡�
16.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;
#endif

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* �ϱ�AT������ʼ */
    NAS_MMC_SndMsccPlmnSelectStartInd();

    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

#if (FEATURE_ON == FEATURE_LTE)
    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_SPEC_SRCH);

    /* �����ֶ�������Ϣ */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                       pstUserSelReqMsg->enAccessMode);

    /* ���ݳ�����ʼ�������б���Ϣ */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSelectionListInfo);



    if ( VOS_TRUE == NAS_MMC_IsNormalServiceStatus() )
    {
        /* SYSCFG���ú���Ҫ����������Ϊ���Ʒ���״̬���ϱ� */
        NAS_MMC_SetCsServiceStatus(NAS_MMC_LIMITED_SERVICE);
        NAS_MMC_SetPsServiceStatus(NAS_MMC_LIMITED_SERVICE);

        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING, NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

        NAS_MMC_UpdateRegStateSpecPlmnSearch();
    }


    /* ��ǰδפ��,��������ʱ�������������,����״̬���˳����anycell���� */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON  == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    /* ��ȡ��ǰ���뼼�� */
    enNetRatType = NAS_MML_GetCurrNetRatType();

#if (FEATURE_ON == FEATURE_LTE)
    if ( VOS_TRUE == NAS_MMC_IsNeedEnableLte_PlmnSelection(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH) )
    {
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }
#endif

    /* �������Ӵ��� */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* ���ݵ�ǰ��ͬ�Ľ��뼼��,�����ͷ�����,Ǩ�Ƶ���ͬ�ĵȴ������ͷŵ�L2״̬��������������ʱ�� */
        NAS_MMC_SndRelReq_PlmnSelection(enNetRatType);

        return VOS_TRUE;
    }

    /* ��ȡ�¸�����ʧ�ܣ����˳�״̬�� */
    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* ��ӡ�쳣 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_Init: Get Next Search Plmn fail at user spec search.");

        /* ��MMA��ָ������ʧ�� */
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/


        /*���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬��*/
        NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* �˳����״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��MM��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */


    /* �ж���Ҫ����������뼼���뵱ǰ���뼼���Ƿ���ͬ,���ߵ�ǰ���뼼��ΪButt,
       ��Ӧ�ĳ�����ѡ��״̬����������״̬���յ�Abort��Ϣ,�����ظ�SUSPNED CNF
       ��Ὣ��ǰ����ģʽ����ΪButt���˳�,��ʾ�������κν��뼼��ֱ�ӷ������� */
    if ((enNetRatType == stDestPlmn.enRat)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enNetRatType))
    {
        /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    else
    {
        /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_PlmnSelection(enNetRatType);
    }

    NAS_MMC_UpdateRegStateSpecPlmnSearch();


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcMmcInterPlmnSearchReq_PlmnSelection_Init
 ��������  : PLMNѡ��״̬����ʼ״̬���յ��ڲ�������������ʼ�������б��������
 �������  : pMsg:����������Ϣ
             ulEventType
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��22��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��11��29��
   ��    ��   : w00166186
   �޸�����   : DTS2011101802330,OOS����������Ĵ���
 4.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ������,��ǰ���类�ظ�����

 5.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 6.��    ��   : 2011��6��9��
   ��    ��   : z00161729
   �޸�����   : V7R1C50 GUL�������޸ģ�list����������������֮ǰ���ܵ�����
 7.��    ��   : 2012��06��27��
   ��    ��   : s00217060
   �޸�����   : for CS/PS mode 1, ����:����������ѡ���б�
 8.��    ��   : 2012��6��13��
   ��    ��   : w00176964
   �޸�����   : DTS2012061202962:�ֶ�ģʽ,ָ������ӵ���ֹ�б��,anycell����פ��
                ����,available��ʱ���������κ�������
 9.��    ��   : 2012��10��16��
   ��    ��   : z00161729
   �޸�����   : DTS2012081604223:�Ѿ�פ����L�����ṩ��������CS/PS mode 1�ػ�LTE����Ҫ��������GU����ʱ������µ�ǰפ������Ϊ��ע��
10.��    ��   : 2012��12��15��
   ��    ��   : l65478
   �޸�����   : DTS2012120508936:�ڷ����������ʱ��Ҫdisable LTE
11.��    ��   : 2013��01��23��
   ��    ��   : s00217060
   �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
12.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
13.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
14.��    ��   : 2013��10��09��
   ��    ��   : l00208543
   �޸�����   : DTS2013100904573
15.��    ��   : 2013��10��17��
   ��    ��   : l65478
   �޸�����   : DTS2013102103487:DT����:�ڵ���ʧ��ʱҲ��Ҫ��������
16.��    ��   : 2013��11��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
17.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
18.��    ��   : 2014��1��22��
   ��    ��   : w00167002
   �޸�����   : SVLTE������:MMC�ִ�������һ�ֵ������������NO RF�����Ϣ��
19.��    ��   : 2014��4��14��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����ʱ���·���״̬
20.��    ��   : 2014��5��21��
   ��    ��   : w00167002
   �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ
21.��    ��   : 2014��6��30��
   ��    ��   : w00176964
   �޸�����   : DSDS III����:�޸ĺ������Լ����NO RF��ǳ����޸�Ϊѡ��������
22.��    ��   : 2014��6��30��
   ��    ��   : z00161729
   �޸�����   : DSDS III����
23.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
24.��    ��   : 2015��1��5��
   ��    ��   : h00285180
   �޸�����   : LTE #14�ܾ��Ż�:DTS2015010401946
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcInterPlmnSearchReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstPlmnSearchReq = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;

    VOS_UINT32                                              ulIsNormalService;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCampPlmnNetRat;
    NAS_MML_LAI_STRU                                       *pstLai;
    VOS_UINT32                                              ucSpecPlmnSearchFlg;
    VOS_UINT32                                              ulSingleDomainPlmnListFlg;
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason;



    VOS_UINT8                                               ucCsAttachAllowFlg;
    VOS_UINT8                                               ucPsAttachAllowFlg;


#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    VOS_UINT32                                              ulIsCsPsMode1NeedPeriodSearchGU;

    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    VOS_UINT8                                               ucEmcFlg;
    NAS_MMC_TIMER_STATUS_ENUM_U8                            enTimerStatus;

    /* ��ȡ��ǰפ����������Ϣ */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;
    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    ucCsAttachAllowFlg = NAS_MML_GetCsAttachAllowFlg();
    ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();

    /* �µ�����:����ע��ʧ�ܷ����������Դ�ʱ,���ע��ʧ��ԭ��ֵ��#17,��Ҫ�������� */
    ulSingleDomainPlmnListFlg = NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS);
    ulSingleDomainPlmnListFlg |= NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS);

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* �ϱ�AT������ʼ */
    NAS_MMC_SndMsccPlmnSelectStartInd();

    ucSpecPlmnSearchFlg = NAS_MMC_GetSpecPlmnSearchState();
    pstLai              = NAS_MML_GetCurrCampLai();
    enCampPlmnNetRat    = pstLai->enCampPlmnNetRat;

    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* �ڲ�����������  */
    pstPlmnSearchReq = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)pstMsg;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��������ʱҵ�񴥷�ʱ��Ҫ����ȫ�ֱ�����״̬��ʱ���ڷ���end session*/
    if (NAS_MMC_PLMN_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH == pstPlmnSearchReq->enPlmnSearchScene)
    {
        NAS_MMC_SetSrvTrigPlmnSearchFlag_PlmnSelection(VOS_TRUE);
    }

    /* ���ݳ�����ʼ�������б���Ϣ */
    NAS_MMC_InitPlmnSelectionList(pstPlmnSearchReq->enPlmnSearchScene,
                                  &(pstPlmnSearchReq->astInterPlmnSearchInfo[0]),
                                  pstPlmnSelectionListInfo);



    /* ��������������ͳһ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchInfo_PlmnSelection(pstPlmnSearchReq, pstPlmnSelectionListInfo);
#if (FEATURE_ON == FEATURE_LTE)
    /* ����CSFB��EMC���߻����EMC������ENABLE LTE��ʱ�������ڼ�,��ENABLE LTE */
    ucEmcFlg           = NAS_MML_GetCsEmergencyServiceFlg();
    enTimerStatus      = NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
    enDisableLteReason = NAS_MML_GetDisableLteReason();
    if (( (MMC_LMM_DISABLE_LTE_REASON_EMERGENCY_CALL   == enDisableLteReason)
       || (MMC_LMM_DISABLE_LTE_REASON_LTE_REJ_CAUSE_14 == enDisableLteReason)
       || (VOS_TRUE == ucEmcFlg))
     && (NAS_MMC_TIMER_STATUS_RUNING == enTimerStatus))
    {
        enPlmnSearchScene = NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE;
    }
    else
    {
        enPlmnSearchScene = pstPlmnSearchReq->enPlmnSearchScene;
    }
    if ( VOS_TRUE == NAS_MMC_IsNeedEnableLte_PlmnSelection(enPlmnSearchScene) )
    {
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /*�жϵ�ǰ�Ƿ��Ѿ�פ����L�����ṩ��������
      ��Ӧ�ĳ�����CS/PS mode 1�ػ�LTE����������GU����*/
    ulIsCsPsMode1NeedPeriodSearchGU = NAS_MMC_IsCsPsMode1NeedPeriodSearchGU();

    if ((VOS_TRUE == NAS_MMC_IsCampLteNormalService())
     && (VOS_TRUE == ulIsCsPsMode1NeedPeriodSearchGU))
    {
        /* ���浱ǰ���絽״̬�������� */
        NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(NAS_MML_GetCurrCampPlmnId());

        /* ����ѡ���б��е�ǰ����״̬Ϊ��ע�� */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                                       NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                       pstPlmnSelectionListInfo);
    }
#endif

    /* list����״̬���˳���������������NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST��NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE*/
    if ((NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST == pstPlmnSearchReq->enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE == pstPlmnSearchReq->enPlmnSearchScene))
    {
        /* ���cs��ps�������Ʒ���list����������е�ǰ���磬�����ظ�������ǰ����*/
        ulIsNormalService = NAS_MMC_IsNormalServiceStatus();

        if (((VOS_FALSE == ulIsNormalService)
          || (VOS_TRUE  == ulSingleDomainPlmnListFlg))
         && (NAS_MMC_SPEC_PLMN_SEARCH_STOP == ucSpecPlmnSearchFlg))
        {
            /* svlte modem0 psǨ�Ƶ�modem1��g������פ����available��ʱ����ʱ��g���ڲ��б��Ѵ�����l�������g��ǰפ��
               ���磬�û��б��ѳ�����������ɾ����ǰפ��g�����磬��Ϊ�������ָ����l������ʧ�ܣ���Ҫ���»ص�g */
            if (!((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
              && (VOS_FALSE == ucCsAttachAllowFlg)
              && (VOS_FALSE == ucPsAttachAllowFlg)))
            {
                /* ɾ����ǰע�ᱻ�ܵ����� */
                NAS_MMC_DelSpecPlmnWithRatInPlmnList(NAS_MML_GetCurrCampPlmnId(),
                                                    enCampPlmnNetRat,
                                                    pstPlmnSelectionListInfo);
            }

        }

    }

    /* ��ǰδפ��,��������ʱ�������������,����״̬���˳����anycell���� */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON  == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }
    /* ��ȡ�¸�����ʧ�ܣ����˳�״̬�� */
    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* ��ӡ�쳣 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcInterPlmnSearchReq_PlmnSelection_Init: Get Next Search Plmn fail at inter search.");

        NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

        if ( (VOS_TRUE == NAS_MMC_IsSorTriggerAdditionalLau())
          && (NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST == pstPlmnSearchReq->enPlmnSearchScene) )
        {
            /* ���additional lau��Ϣ */
            NAS_MML_InitSorAdditionalLauCtx();

            /* LIST�ѽ�����֪ͨMM���ʹ���SOR��LAU */
            NAS_MMC_SndMmLauReq(MMC_MM_LAU_REQ_REASON_SOR);
        }
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    /* ��ȡ��ǰ���뼼�� */
    enNetRatType = NAS_MML_GetCurrNetRatType();

    /*�������Ӵ���*/
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* ���ݵ�ǰ��ͬ�Ľ��뼼��,�����ͷ�����,Ǩ�Ƶ���ͬ�ĵȴ������ͷŵ�L2״̬��������������ʱ�� */
        NAS_MMC_SndRelReq_PlmnSelection(enNetRatType);

        return VOS_TRUE;
    }

    /* ��MM��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

    /* �ж���Ҫ����������뼼���뵱ǰ���뼼���Ƿ���ͬ,���ߵ�ǰ���뼼��ΪButt,
       ��Ӧ�ĳ�����ѡ��״̬����������״̬���յ�Abort��Ϣ,�����ظ�SUSPNED CNF
       ��Ὣ��ǰ����ģʽ����ΪButt���˳�,��ʾ�������κν��뼼��ֱ�ӷ������� */
    if ((enNetRatType == stDestPlmn.enRat)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enNetRatType))
    {
        /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    /*��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ��*/
    else
    {
        /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_PlmnSelection(enNetRatType);
    }

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, begin */
    NAS_MMC_UpdateServiceStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, end */

    return VOS_TRUE;

}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccAcqReq_PlmnSelection_Init
 ��������  : PLMNѡ��״̬����ʼ״̬���յ���ȡ���紦��
 �������  : pMsg:ID_MSCC_MMC_ACQ_REQ��Ϣ
             ulEventType
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��27��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��4��14��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����ʱ���·���״̬
 3.��    ��   : 2014��7��1��
   ��    ��   : W00176964
   �޸�����   : DSDS III:����ѡ�������NO RF���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccAcqReq_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    MSCC_MMC_ACQ_REQ_STRU                                   *pstAcqReq = VOS_NULL_PTR;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* �ϱ�AT������ʼ */
    NAS_MMC_SndMsccPlmnSelectStartInd();

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstAcqReq = (MSCC_MMC_ACQ_REQ_STRU*)pstMsg;

    /* ���ݻ�ȡԭ����������б��ʼ�� */
    if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstAcqReq->enAcqReason)
    {
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON,
                                      VOS_NULL_PTR,
                                      pstPlmnSelectionListInfo);
    }
    else if (NAS_MSCC_PIF_ACQ_REASON_OTHER == pstAcqReq->enAcqReason)
    {
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED,
                                      VOS_NULL_PTR,
                                      pstPlmnSelectionListInfo);
    }
    else
    {
        NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                      VOS_NULL_PTR,
                                      pstPlmnSelectionListInfo);
    }



    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* ��ӡ�쳣 */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccAcqReq_PlmnSelection_Init: Get Next Search Plmn fail at inter search.");

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    /* ��ȡ��ǰ���뼼�� */
    enNetRatType = NAS_MML_GetCurrNetRatType();

    /*�������Ӵ���*/
    if ((VOS_TRUE == NAS_MML_IsRrcConnExist())
     && (NAS_MML_NET_RAT_TYPE_BUTT != enNetRatType))
    {
        /* ���ݵ�ǰ��ͬ�Ľ��뼼��,�����ͷ�����,Ǩ�Ƶ���ͬ�ĵȴ������ͷŵ�L2״̬��������������ʱ�� */
        NAS_MMC_SndRelReq_PlmnSelection(enNetRatType);

        return VOS_TRUE;
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* ��MM��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

    /* �ж���Ҫ����������뼼���뵱ǰ���뼼���Ƿ���ͬ,���ߵ�ǰ���뼼��ΪButt,
       ��Ӧ�ĳ�����ѡ��״̬����������״̬���յ�Abort��Ϣ,�����ظ�SUSPNED CNF
       ��Ὣ��ǰ����ģʽ����ΪButt���˳�,��ʾ�������κν��뼼��ֱ�ӷ������� */
    if ((enNetRatType == stDestPlmn.enRat)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enNetRatType))
    {
        /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    /*��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ��*/
    else
    {
        /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_PlmnSelection(enNetRatType);
    }

#if   (FEATURE_ON == FEATURE_LTE)
    /* ���������ȡ����Ҫ�ж�SIM������Disable Lte���� */
    if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstAcqReq->enAcqReason)
    {
        NAS_MMC_DisableLteForSimReason_PlmnSelection();
    }
#endif

    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, begin */
    NAS_MMC_UpdateServiceStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, end */


    return VOS_TRUE;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS�����ظ��������յ�״̬���˳���Ϣ�Ĵ���
 �������  : pMsg:MMCMMC_ABORT_FSM_REQ
             ulEventType
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2014��2��18��
   ��    ��   : s00217060
   �޸�����   : DTS2014021203453:���ô�ϱ�־����������յ�stop_cnf֮��������

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /* ֪ͨASָֹͣ������ */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

    /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������ͬ������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcUtranCtrlPlmnSelectionAbortFinishIndMsg_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS�����ظ��������յ�MMC���UTRANCTRL���������Ϣ�Ĵ���
 �������  : pMsg:MMCMMC_INTER_UTRAN_CTRL_PLMN_SELECTION_ABORT_FINISH_IND
             ulEventType
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��12��17��
   ��    ��   : w00167002
   �޸�����   : ��W������ʧ�ܣ���UTRANCTRLѡ��TD����ʱ���յ���һ�׶ζ�
                ʱ����ʱ����Ϣ���������ѡ��״̬������ǰMMCѡ��״̬����W��STOP REQ���󣬶�����
                ��TD��STOP������������MMC����������Lte,����˫��ģ�쳣��λ. ����Ϣ���ѡ��״̬��ʱ��
                ��Ҫ���˳�UTRANCTRLѡ�����̣��ٴ��MMCѡ��״̬������ʱMMC�յ�ѡ��״̬����MMC���͵�
                abort��Ϣ��ϣ�����˳�ѡ��״̬����

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcUtranCtrlAbortFinishIndMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcUtranCtrlAbortFinishIndMsg_PlmnSelection_WaitWasPlmnSearchCnf");

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS�����ظ��������յ�RRMM_REL_IND��Ϣ�Ĵ���
 �������  : pMsg        - RRMM_REL_IND��Ϣ�׵�ַ
             ulEventType - �¼�����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��11��28��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 3.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 4.��    ��   : 2012��6��18��
   ��    ��   : l00171473
   �޸�����   : DTS2012051104124, WAS:���յ�RRMM_PLMN_SEARCH_REQʱ�������ϱ�����ԭ���rel ind��
                ֻ���쳣ԭ���rel ind. �յ�rel indʱ��Ϊ��������
 5.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity

 6.��    ��   : 2014��6��17��
   ��    ��   : w00167002
   �޸�����   : DSDS III:�յ�WAS��NO RF�쳣�ͷţ������OOC

 7.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* �����ж�ԭ��ֵ */

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnSearchCnf: ENTERED");

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);


    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    /* �����ǰ��HISTORY�ѣ�������UTRAN�Ѿ����HISTORY�������� */
    if (NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection())
    {
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ��ȡ��һ��Ҫ����������,����ȡʧ�ܣ�����ϲ�״̬���ϱ�����ʧ�ܣ��˳�
       ����ȡ�ɹ������ж���һ��Ҫ�����������Ƿ��뵱ǰפ��������ͬ��
       ����ͬ���ڵ�ǰģʽ�����������������ǰ���� */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /*  ��ȡ�¸�����ʧ�ܣ�����г����������� */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }


    /*��һ��Ҫ�����������Ƿ��뵱ǰפ�����粻ͬ,��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ�� */
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    else
    {
        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasPlmnSearchCnf
 ��������  : �ȴ�GAS�����ظ��������յ�״̬���˳���Ϣ�Ĵ���
 �������  : pMsg:MMCMMC_ABORT_FSM_REQ
             ulEventType
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2014��2��18��
   ��    ��   : s00217060
   �޸�����   : DTS2014021203453:���ô�ϱ�־����������յ�stop_cnf֮��������

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /* ֪ͨASָֹͣ������ */
    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection
 ��������  : �жϽ��������ʧ�ܽ���Ƿ���Ҫ������������
 �������  : pstInterPlmnSearchInfo - ����ʧ�ܴ��������ڵ�������Ϣ
             enRat                  - ���뼼��
 �������  : ��
 �� �� ֵ  : VOS_TRUE - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��1��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstInterPlmnSearchInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat
)
{
    VOS_UINT32                          i;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstCurrSearchingPlmn = VOS_NULL_PTR;
    VOS_UINT8                           ucSearchedPlmnAllSameWithCurrSearchingPlmn;

    pstCurrSearchingPlmn                       = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    ucSearchedPlmnAllSameWithCurrSearchingPlmn = VOS_TRUE;

    if (VOS_FALSE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection(enRat))
    {
        return VOS_FALSE;
    }

    /* �������ʧ�ܴ��������ڵĸ�����������������������һ��������
       ��rplmn��hplmn��ͬ���򷵻�false */
    for (i = 0; i < pstInterPlmnSearchInfo->ulHighPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstInterPlmnSearchInfo->astHighPlmnList[i].ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return VOS_FALSE;
        }

        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstInterPlmnSearchInfo->astHighPlmnList[i].ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return VOS_FALSE;
        }

        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrSearchingPlmn->stPlmnId.ulMcc, pstInterPlmnSearchInfo->astHighPlmnList[i].ulMcc))
        {
            ucSearchedPlmnAllSameWithCurrSearchingPlmn = VOS_FALSE;
        }
    }

    for (i = 0; i < pstInterPlmnSearchInfo->ulLowPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstInterPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return VOS_FALSE;
        }

        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstInterPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return VOS_FALSE;
        }

        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrSearchingPlmn->stPlmnId.ulMcc, pstInterPlmnSearchInfo->astLowPlmnList[i].stPlmnId.ulMcc))
        {
            ucSearchedPlmnAllSameWithCurrSearchingPlmn = VOS_FALSE;
        }
    }

    /* ����ʧ�ܴ��������ڵ����綼������������ͬһ�����룬�����¹������������б� */
    if (VOS_TRUE == ucSearchedPlmnAllSameWithCurrSearchingPlmn)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �յ�WASȫƵ��ָ������CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:rrmm_plmn_SEARCH_cnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��25��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������

 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 6.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 7.��    ��   : 2014��1��21��
   ��    ��   : w00167002
   �޸�����   : SVLTE��������Ŀ:��W������ʧ��ΪNO RF����ʾ��ǰ������Դ�����ã�
                ��ǰ����������
 8.��    ��   : 2013��3��29��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:NO RF�������RRM����ע�ᣬֻ����GU������LTE����������NO RF
 9.��    ��   : 2014��6��21��
   ��    ��   : w00167002
   �޸�����   : DSDS GUNAS III��Ŀ
10.��    ��   : 2014��11��1��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
11.��    ��   : 2015��5��21��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�,�û�ȫƵ��ָ���ѵĴ����߼�
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* ��ȡѡ���б� */
    pstPlmnSrchList                = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList       = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ���µ�ǰģʽ�����縲����Ϣ */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_SPEC == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* ���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);

        return;
    }


    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }


    /* ��������Ϣ��Я����������Ϣת��Ϊ�ڲ���Ϣ��������Ϣ */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ֪ͨCSS��ǰMCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* �������ʧ�ܽ���д�����������û��һ����rplmn��hplmn
       ͬһ��������֮ǰδ�Ź�����Ҫ�������������б����ԭ�����б�ͷ��*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_WCDMA);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* �Ѹߵ�����������ȡ����roam�����б� */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_WCDMA, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                     &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);


        /* ������Ϣ��Я����������Ϣ���������б� */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);

        /* ��ά�ɲ�,��ѡ���б���� */

        NAS_MMC_LogDplmnNplmnList();

    }


    /* ���µ�ǰ���뼼��������ȫƵ����,�����ǰ�����������������޷��������������б����Թ��������������б���ٸ��½��й�ȫƵ����*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* ��W����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��W����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �յ�WAS pref band����CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:rrmm_plmn_SEARCH_cnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��12��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* ��ȡѡ���б� */
    pstPlmnSrchList                = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList       = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ���µ�ǰģʽ�����縲����Ϣ */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* ���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }

    /* ��������Ϣ��Я����������Ϣת��Ϊ�ڲ���Ϣ��������Ϣ */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ֪ͨCSS��ǰMCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* �������ʧ�ܽ���д�����������û��һ����rplmn��hplmn
       ͬһ��������֮ǰδ�Ź�����Ҫ�������������б����ԭ�����б�ͷ��*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_WCDMA);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* �Ѹߵ�����������ȡ����roam�����б� */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_WCDMA, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                     &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);


        /* ������Ϣ��Я����������Ϣ���������б� */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);

        /* ��ά�ɲ�,��ѡ���б���� */
        NAS_MMC_LogDplmnNplmnList();

    }

    /* ���µ�ǰ���뼼��������ȫƵ����,�����ǰ�����������������޷��������������б����Թ��������������б���ٸ��½��й�ȫƵ����*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* ��W����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��W����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmHistoryPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �յ�WAS ��ʷƵ������CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:rrmm_plmn_SEARCH_cnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��21��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�,history�ѵĴ����߼�
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmHistoryPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;
    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* ��ȡѡ���б� */
    pstPlmnSrchList                = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList       = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ����HISTORY�����ĸ������� */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* ����UTRAN�Ѿ����HISTORY�������� */
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* ���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }

    /* ����UTRAN�Ѿ����HISTORY�������� */
    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);


    /* ��������Ϣ��Я����������Ϣת��Ϊ�ڲ���Ϣ��������Ϣ */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* ������Ϣ��Я����������Ϣ���������б�--- û�н���ȫƵ������������ֻ�ܸ��´��ڵ����� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_FALSE);

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ֪ͨCSS��ǰMCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* �������ʧ�ܽ���д�����������û��һ����rplmn��hplmn
       ͬһ��������֮ǰδ�Ź�����Ҫ�������������б����ԭ�����б�ͷ��*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_WCDMA);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* �Ѹߵ�����������ȡ����roam�����б� */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_WCDMA, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
                     &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);


        /* ������Ϣ��Я����������Ϣ���������б� */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_FALSE);                  /* û�н���ȫBAND�� */

        /* ��ά�ɲ�,��ѡ���б���� */
        NAS_MMC_LogDplmnNplmnList();

    }

    /* -------------ע:HISTORY����ʧ�ܣ���������ALL BAND����------------- */

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* ��W����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��W����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �յ�WAS����CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:rrmm_plmn_SEARCH_cnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��25��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������

 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 6.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 7.��    ��   : 2014��1��21��
   ��    ��   : w00167002
   �޸�����   : SVLTE��������Ŀ:��W������ʧ��ΪNO RF����ʾ��ǰ������Դ�����ã�
                ��ǰ����������
 8.��    ��   : 2013��3��29��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:NO RF�������RRM����ע�ᣬֻ����GU������LTE����������NO RF
 9.��    ��   : 2014��6��21��
   ��    ��   : w00167002
   �޸�����   : DSDS GUNAS III��Ŀ
10.��    ��   : 2014��11��1��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
11.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�,�ֱ���ָ���Ѻ���ʷƵ����
12.��    ��   : 2015��10��12��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0�޸ģ�����pref band�������
                 �Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    switch ( pstSrchCnfMsg->ulSearchRlt )
    {
        /* ȫƵ��ָ���ѽ���Ĵ��� */
        case RRC_PLMN_SEARCH_RLT_SPEC:
        case RRC_PLMN_SEARCH_RLT_SPEC_NO_RF:
        case RRC_PLMN_SEARCH_RLT_SPEC_FAIL:
            NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        /* ��ʷƵ��ָ���ѽ���Ĵ��� */
        case RRC_PLMN_SEARCH_RLT_HISTORY_SUCC:
        case RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF:
        case RRC_PLMN_SEARCH_RLT_HISTORY_FAIL:
            NAS_MMC_RcvRrMmHistoryPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        /* pref band�ѽ���Ĵ��� */
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL:
            NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf:UNEXPECTED SEARCH RSLT!!!");

            /* �쳣��������ָ����ʧ�ܴ��� */
            NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �յ�was RRMM_SEARCHED_PLMN_INFO_IND�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��28��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateExistRplmnOrHplmnFlag_PlmnSelection(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU   *pstSearchedExistPlmnInfo
)
{
    VOS_UINT32                          ulIndex;


    for (ulIndex = 0; ulIndex < pstSearchedExistPlmnInfo->usSearchPlmnNum; ulIndex++)
    {
        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithRplmn(pstSearchedExistPlmnInfo->astPlmnSelectionList[ulIndex].stPlmnWithRat.stPlmnId.ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return;
        }

        if (VOS_TRUE == NAS_MMC_IsPlmnMccSameWithHplmn(pstSearchedExistPlmnInfo->astPlmnSelectionList[ulIndex].stPlmnWithRat.stPlmnId.ulMcc))
        {
            NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(VOS_TRUE);
            return;
        }
    }

    return;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �յ�was RRMM_SEARCHED_PLMN_INFO_IND�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��28��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��5��22��
   ��    ��   : b00269685
   �޸�����   : ����������W����
 3.��    ��   : 2015��10��9��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SEARCHED_PLMN_INFO_IND_STRU                       *pstSearchedPlmnInfoMsg = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    VOS_UINT32                                              ulIsNeedStopPlmnSearch;

    pstSearchedPlmnInfoMsg        = (RRMM_SEARCHED_PLMN_INFO_IND_STRU *)pstMsg;
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));

    NAS_MMC_SndMsccSrchedGuPlmnInfo(NAS_MSCC_PIF_NET_RAT_TYPE_WCDMA, pstSearchedPlmnInfoMsg);


    /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    if (pstSearchedPlmnInfoMsg->ulAvailPlmnNum > NAS_RRC_MAX_AVAILPLMN_NUM)
    {
        pstSearchedPlmnInfoMsg->ulAvailPlmnNum = NAS_RRC_MAX_AVAILPLMN_NUM;
    }
    NAS_MMC_BuildSearchedPlmnInfoByRrcSearchedPlmnInfoInd(pstSearchedPlmnInfoMsg, &stSearchedExistPlmnInfo);

    NAS_MMC_UpdateExistRplmnOrHplmnFlag_PlmnSelection(&stSearchedExistPlmnInfo);

    /* ֪ͨCSS��ǰMCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnInfoInd_PlmnSelection(&stSearchedExistPlmnInfo, VOS_TRUE);

    ulIsNeedStopPlmnSearch = NAS_MMC_IsNeedStopPlmnSearchRcvRrcSearchedPlmnInfoInd_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA,pstSearchedPlmnInfoMsg);

    if ((VOS_TRUE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA))
     && (VOS_TRUE == ulIsNeedStopPlmnSearch))
    {
        /* �������γ��������������б�����ԭ������:
         1��������ϱ����ڵ�����������������б�ǰ��,��NPLMN�е����粻��ӣ�
            ֧�ֵ����н��뼼������ӣ���ǰ�����Ľ��뼼������
         2����gastNetworkNameTbl���ҳ�����ǰ����������ͬ�������plmn�������������б�
            ��NPLMN�е����粻��ӣ�֧�ֵ����н��뼼������ӣ���ǰ�����Ľ��뼼������
         3������DPLMN->UPLMN->OPLMN->AVAILABLE PLMN˳������������б��������
        */
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_WCDMA,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ��ά�ɲ�,��ѡ���б���� */
        NAS_MMC_LogPlmnSelectionList(pstPlmnSrchList);
        NAS_MMC_LogDplmnNplmnList();

        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

        /* �����ǰ��HISTORY�ѣ�������UTRAN�Ѿ����HISTORY�������� */
        if (NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);
        }
        /* ֪ͨutran ctrlģ���ϵ�ǰ����������utran ctrl modeΪfdd */
        NAS_MMC_SndInterAbortUtranCtrlPlmnSearchReqMsg();

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSkipFddRcvRrcSearchedPlmnInfoInd_PlmnSelection(pstSearchedPlmnInfoMsg))
    {
        NAS_MMC_SndInterSkipSearchWIndMsg();

        return VOS_TRUE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvInterAbortUtranCtrlPlmnSearchCnf_WaitWasPlmnSearchCnf
 ��������  : �յ�mmc�ڲ���Ϣinter abort utran ctrl plmn search cnf�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��28��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvInterAbortUtranCtrlPlmnSearchCnf_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     /* ֹͣ������ʱ�� */
     NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);


     /* ֪ͨASָֹͣ������ */
     NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

     /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������ͬ������ʱ��*/
     NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

     (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

     return VOS_TRUE;

}




/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitGasPlmnSearchCnf
 ��������  : �յ�GAS RRMM_SEARCHED_PLMN_INFO_IND�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��28��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
 2.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
 3.��    ��   : 2015��10��9��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SEARCHED_PLMN_INFO_IND_STRU                       *pstSearchedPlmnInfoMsg = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;

    pstSearchedPlmnInfoMsg        = (RRMM_SEARCHED_PLMN_INFO_IND_STRU *)pstMsg;
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));

    NAS_MMC_SndMsccSrchedGuPlmnInfo(NAS_MSCC_PIF_NET_RAT_TYPE_GSM, pstSearchedPlmnInfoMsg);

    /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    if (pstSearchedPlmnInfoMsg->ulAvailPlmnNum > NAS_RRC_MAX_AVAILPLMN_NUM)
    {
        pstSearchedPlmnInfoMsg->ulAvailPlmnNum = NAS_RRC_MAX_AVAILPLMN_NUM;
    }

    NAS_MMC_BuildSearchedPlmnInfoByRrcSearchedPlmnInfoInd(pstSearchedPlmnInfoMsg, &stSearchedExistPlmnInfo);

    NAS_MMC_UpdateExistRplmnOrHplmnFlag_PlmnSelection(&stSearchedExistPlmnInfo);

    /* ֪ͨCSS��ǰMCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnInfoInd_PlmnSelection(&stSearchedExistPlmnInfo, VOS_TRUE);

    if (VOS_FALSE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStopPlmnSearchRcvRrcSearchedPlmnInfoInd_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, pstSearchedPlmnInfoMsg))
    {
        /* �������γ��������������б�����ԭ������:
         1��������ϱ����ڵ�����������������б�ǰ��,��NPLMN�е����粻��ӣ�
            ֧�ֵ����н��뼼������ӣ���ǰ�����Ľ��뼼������
         2����gastNetworkNameTbl���ҳ�����ǰ����������ͬ�������plmn�������������б�
            ��NPLMN�е����粻��ӣ�֧�ֵ����н��뼼������ӣ���ǰ�����Ľ��뼼������
         3������DPLMN->UPLMN->OPLMN->AVAILABLE PLMN˳������������б��������
        */
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_GSM,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ��ά�ɲ�,��ѡ���б���� */
        NAS_MMC_LogPlmnSelectionList(pstPlmnSrchList);
        NAS_MMC_LogDplmnNplmnList();

        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

        /* �����ǰ��HISTORY�ѣ�������G���Ѿ����HISTORY�������� */
        if (NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);
        }

        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

        /* ֪ͨ�����ֹͣ��ǰ���� */
        NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf
 ��������  : �յ�GAS����CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:rrmm_plmn_SEARCH_cnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��25��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��11��22��
   ��    ��   : w00166186
   �޸�����   : DTS2011111603440,����ʧ�ܣ��ϱ������ɹ�
 4.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 5.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 6.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 7.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 8.��    ��   : 2013��3��29��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:NO RF�������RRM����ע�ᣬֻ����GU������LTE����������NO RF
 9.��    ��   : 2014��6��21��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ
10.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
11.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* ��ȡѡ���б� */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* ���õ�ǰģʽ�Ƿ����ȫƵ�������Ƿ�������縲�� */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_SPEC == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* ���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

        return;
    }


    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }


    /* ��������Ϣ��Я����������Ϣת��Ϊ�ڲ���Ϣ��������Ϣ */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_GSM,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ֪ͨCSS��ǰMCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* �������ʧ�ܽ���д�����������û��һ����rplmn��hplmn
       ͬһ��������֮ǰδ�Ź�����Ҫ�������������б����ԭ����ͷ��*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_GSM);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* �Ѹߵ�����������ȡ����roam�����б� */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_GSM, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_GSM,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

        /* ������Ϣ��Я����������Ϣ���������б� */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);

        /* ��ά�ɲ�,��ѡ���б���� */
        NAS_MMC_LogDplmnNplmnList();

    }


    /* ���µ�ǰ���뼼��������ȫƵ����,�����ǰ�����������������޷��������������б����Թ��������������б���ٸ��½��й�ȫƵ����*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);



    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* ��G����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��G����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf
 ��������  : �յ�GAS HISTORY����CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:rrmm_plmn_SEARCH_cnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��25��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmHistoryPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;
    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* ��ȡѡ���б� */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* ����HISTORY�����ĸ������� */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* ���µ�ǰGAS�����HISTORY���� */
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* ���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }

    /* ���µ�ǰGAS�����HISTORY���� */
    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

    /* ��������Ϣ��Я����������Ϣת��Ϊ�ڲ���Ϣ��������Ϣ */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_GSM,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_FALSE);

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ֪ͨCSS��ǰMCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* �������ʧ�ܽ���д�����������û��һ����rplmn��hplmn
       ͬһ��������֮ǰδ�Ź�����Ҫ�������������б����ԭ����ͷ��*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_GSM);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* �Ѹߵ�����������ȡ����roam�����б� */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_GSM, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_GSM,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

        /* ������Ϣ��Я����������Ϣ���������б� */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_FALSE);
        /* ��ά�ɲ�,��ѡ���б���� */
        NAS_MMC_LogDplmnNplmnList();

    }


    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* ��G����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��G����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf
 ��������  : ��GAS���������ʱ�յ�pref band��������Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* ��ȡѡ���б� */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* ���õ�ǰģʽ�Ƿ����ȫƵ�������Ƿ�������縲�� */
    NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(pstSrchCnfMsg);

    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /* ���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

        return;
    }


    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }


    /* ��������Ϣ��Я����������Ϣת��Ϊ�ڲ���Ϣ��������Ϣ */
    NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(NAS_MML_NET_RAT_TYPE_GSM,
                                                     &pstSrchCnfMsg->PlmnIdList,
                                                     &stPlmnSearchInfo);

    /* ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ֪ͨCSS��ǰMCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* �������ʧ�ܽ���д�����������û��һ����rplmn��hplmn
       ͬһ��������֮ǰδ�Ź�����Ҫ�������������б����ԭ����ͷ��*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_GSM);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* �Ѹߵ�����������ȡ����roam�����б� */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_GSM, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_GSM,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

        /* ������Ϣ��Я����������Ϣ���������б� */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);

        /* ��ά�ɲ�,��ѡ���б���� */
        NAS_MMC_LogDplmnNplmnList();

    }

    /* ���µ�ǰ���뼼��������ȫƵ����,�����ǰ�����������������޷��������������б����Թ��������������б���ٸ��½��й�ȫƵ����*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* ��G����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��G����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf
 ��������  : �յ�GAS����CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:rrmm_plmn_SEARCH_cnf��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��25��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��11��22��
   ��    ��   : w00166186
   �޸�����   : DTS2011111603440,����ʧ�ܣ��ϱ������ɹ�
 4.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 5.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 6.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 7.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 8.��    ��   : 2013��3��29��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:NO RF�������RRM����ע�ᣬֻ����GU������LTE����������NO RF
 9.��    ��   : 2014��6��21��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ
10.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
11.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
12.��    ��   : 2015��10��12��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:����pref band�ѽ���Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    switch ( pstSrchCnfMsg->ulSearchRlt )
    {
        /* ȫƵ��ָ���ѽ���Ĵ��� */
        case RRC_PLMN_SEARCH_RLT_SPEC:
        case RRC_PLMN_SEARCH_RLT_SPEC_NO_RF:
        case RRC_PLMN_SEARCH_RLT_SPEC_FAIL:
            NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        /* ��ʷƵ��ָ���ѽ���Ĵ��� */
        case RRC_PLMN_SEARCH_RLT_HISTORY_SUCC:
        case RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF:
        case RRC_PLMN_SEARCH_RLT_HISTORY_FAIL:
            NAS_MMC_RcvRrMmHistoryPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF:
            NAS_MMC_RcvRrMmPrefBandPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf:UNEXPECTED SEARCH RSLT!!!");

            /* �쳣�������� */
            NAS_MMC_RcvRrMmSpecPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasSpecPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WASȫƵ��ָ�������ظ�������������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 6.��    ��   : 2012��8��10��
   ��    ��   : L00171473
   �޸�����   : DTS2012082204471, TQE����
 7.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:�������縲������
 8.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 9.��    ��   : 2014��6��6��
   ��    ��   : b00269685
   �޸�����   : ��ʱ����ʱ����֪ͨWASֹͣ����
 10.��    ��   : 2014��11��8��
    ��    ��   : z00161729
    �޸�����   : ���������Ż���Ŀ�޸�
 11.��    ��   : 2015��5��26��
    ��    ��   : w00167002
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�

*****************************************************************************/

VOS_VOID NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;


    PS_MEM_SET(&stPlmnSearchInfo, 0x00, sizeof(stPlmnSearchInfo));


    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf: Timer Expired");

    /* ���õ�ǰ�����Ѿ�����ȫƵ���� */
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

    /* ���õ�ǰ�����޸��� */
    NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, NAS_MMC_COVERAGE_TYPE_NONE);

    /* ���õ�ǰ���뼼��û���������κ����� */
    stPlmnSearchInfo.ulHighPlmnNum = 0x0;
    stPlmnSearchInfo.ulLowPlmnNum  = 0x0;
    stPlmnSearchInfo.enRatType     = NAS_MML_NET_RAT_TYPE_WCDMA;

    /* ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* ֪ͨASָֹͣ������ */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

    /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������ͬ������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasHistoryPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS HISTORY�����ظ�������������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�

*****************************************************************************/
VOS_VOID NAS_MMC_RcvTiWaitHistoryPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasHistoryPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf: Timer Expired");

    /* ���µ�ǰUTRAN�����HISTORY���� */
    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA, VOS_TRUE);

    /* ֪ͨASָֹͣ������ */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

    /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������ͬ������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf
 ��������  : �ȴ�WAS�����ظ�������������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 6.��    ��   : 2012��8��10��
   ��    ��   : L00171473
   �޸�����   : DTS2012082204471, TQE����
 7.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:�������縲������
 8.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 9.��    ��   : 2014��6��6��
   ��    ��   : b00269685
   �޸�����   : ��ʱ����ʱ����֪ͨWASֹͣ����
 10.��    ��   : 2014��11��8��
    ��    ��   : z00161729
    �޸�����   : ���������Ż���Ŀ�޸�
 11.��    ��   : 2015��5��26��
    ��    ��   : w00167002
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�,����HISTORY�ѵĴ���
 12.��    ��   : 2015��10��28��
    ��    ��   : s00217060
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:����pref band�ѵĴ���

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enCurrSearchingPlmnType;                /* ��������ָ���ѣ�history�� */

    enCurrSearchingPlmnType = NAS_MMC_GetCurrSearchingType_PlmnSelection();

    switch (enCurrSearchingPlmnType)
    {
        case NAS_MMC_PLMN_SEARCH_TYPE_SPEC:
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_HISTORY:
            NAS_MMC_RcvTiWaitHistoryPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND:
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf UNEXPECTED SEARCH TYPE!!!");

            /* �쳣���� */
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasSpecPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf
 ��������  : �ȴ�GAS�����ظ�������������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 6.��    ��   : 2012��8��10��
   ��    ��   : L00171473
   �޸�����   : DTS2012082204471, TQE����
 7.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:�������縲������
 8.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 9.��    ��   : 2014��6��6��
   ��    ��   : b00269685
   �޸�����   : ��ʱ����ʱ����֪ͨGASֹͣ����
 10.��    ��   : 2014��11��8��
    ��    ��   : z00161729
    �޸�����   : ���������Ż���Ŀ�޸�
 11.��    ��   : 2015��5��26��
    ��    ��   : w00167002
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/

VOS_VOID NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;


    PS_MEM_SET(&stPlmnSearchInfo, 0x00, sizeof(stPlmnSearchInfo));


    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf: Timer Expired");

    /* ���õ�ǰ�����Ѿ�����ȫƵ���� */
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

    /* ���õ�ǰ�����޸��� */
    NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, NAS_MMC_COVERAGE_TYPE_NONE);

    /* ���õ�ǰ���뼼��û���������κ����� */
    stPlmnSearchInfo.ulHighPlmnNum = 0x0;
    stPlmnSearchInfo.ulLowPlmnNum  = 0x0;
    stPlmnSearchInfo.enRatType     = NAS_MML_NET_RAT_TYPE_GSM;

    /* ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasHistoryPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf
 ��������  : �ȴ�GAS��ʷƵ�������ظ�������������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_RcvTiWaitHistoryPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasHistoryPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf: Timer Expired");

    /* ���µ�ǰUTRAN�����HISTORY���� */
    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM, VOS_TRUE);

    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf
 ��������  : �ȴ�GAS�����ظ�������������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 6.��    ��   : 2012��8��10��
   ��    ��   : L00171473
   �޸�����   : DTS2012082204471, TQE����
 7.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:�������縲������
 8.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 9.��    ��   : 2014��6��6��
   ��    ��   : b00269685
   �޸�����   : ��ʱ����ʱ����֪ͨGASֹͣ����
 10.��    ��   : 2014��11��8��
    ��    ��   : z00161729
    �޸�����   : ���������Ż���Ŀ�޸�
 11.��    ��   : 2015��5��26��
    ��    ��   : w00167002
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�,���Ӷ�HISTORY�����Ĵ���
 12.��    ��   : 2015��10��28��
    ��    ��   : s00217060
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:����pref band�ѵĴ���
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enCurrSearchingPlmnType;                /* ��������ָ���ѣ�history�� */

    enCurrSearchingPlmnType = NAS_MMC_GetCurrSearchingType_PlmnSelection();

    switch (enCurrSearchingPlmnType)
    {
        case NAS_MMC_PLMN_SEARCH_TYPE_SPEC:
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_HISTORY:
            NAS_MMC_RcvTiWaitHistoryPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND:
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf UNEXPECTED SEARCH TYPE!!!");
            NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnf
 ��������  : suspend CNF�����е�ǰ״̬���˳�
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��

****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnf
 ��������  : �յ�AS��suspend cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : w00167002
   �޸�����   : DTS2011120702166:MMC��λ���޸�λ��Ϣ,��MMLģ���װ��λ��Ϣ��
                  �Թ�MM����ã�������λ��
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 6.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 7.��    ��   : 2014��2��18��
   ��    ��  :  w00242748
   �޸�����  :  DTS2014021803515:��λʱ��ȷ���յ��ĸ����뼼�����쳣��Ϣ���µġ�
 8.��    ��   : 2014��6��23��
   ��    ��  :  b00269685
   �޸�����  :  DSDS III����
 9.��    ��   : 2015��3��11��
   ��    ��   : wx270776
   �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* ���ɻָ�����,���õ���ӿ�RESET */

        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        /* ���õ�ǰ���뼼��ΪBUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* �ظ�Plmn Selectionִ�н�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ��ȡ��Ҫ���������缰����뼼�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    else
    {
        /* Error�����ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnf: Get next search plmn fail.");

        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnf
 ��������  : �յ�GAS��suspend cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : w00167002
   �޸�����   : DTS2011120702166:MMC��λ���޸�λ��Ϣ,��MMLģ���װ��λ��Ϣ��
                 �Թ�MM����ã�������λ��
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 6.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 7.��    ��   : 2014��6��23��
   ��    ��  :  b00269685
   �޸�����  :  DSDS III����
 8.��    ��   : 2015��3��11��
   ��    ��   : wx270776
   �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* ���ɻָ�����,���õ���ӿ�RESET */

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        /* ���õ�ǰ���뼼��ΪBUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* �����������,ԭ��Ϊ�˳�״̬�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ��ȡ��Ҫ���������缰����뼼�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    else
    {
        /* Error�����ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnf: Get next search plmn fail.");

        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnf
 ��������  : suspend CNF�����б�����ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��12��15��
   ��    ��   : w00167002
   �޸�����   : DTS2011120702166:MMC��λ���޸�λ��Ϣ,��MMLģ���װ��λ��Ϣ��
                 �Թ�MM����ã�������λ��
 3.��    ��   : 2014��2��18��
   ��    ��  :  w00242748
   �޸�����  :  DTS2014021803515:��λʱ��ȷ���յ��ĸ����뼼�����쳣��Ϣ���µġ�

 4.��    ��   : 2015��3��11��
   ��    ��   : wx270776
   �޸�����   : DTS2015011212939:���Ӹ�λ����
****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* ���ɻָ����ϣ���λ */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �յ�WAS��plmn search stop cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 4.��    ��   : 2014��6��6��
   ��    ��   : b00269685
   �޸�����   : ������Ϊ������ʱ����ʱ�����͵�stop request������Ҫ��������
 5.��    ��   : 2014��6��21��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* ��W����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��W����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �յ�WAS��RRMM_REL_IND��Ϣ�Ĵ���
 �������  : pMsg        - RRMM_REL_IND��Ϣ�׵�ַ
             ulEventType - �¼�����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��11��28��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 3.��    ��   : 2012��6��18��
   ��    ��   : l00171473
   �޸�����   : DTS2012051104124,WAS:���յ�RRMM_PLMN_SEARCH_STOP_REQʱ��
                ���ܷ������쳣ԭ���rel ind����RRMM_PLMN_SEARCH_STOP_CNF.
                �յ�rel ind��Ϊֹͣ��������
 4.��    ��   : 2014��6��23��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ж�ԭ��ֵ */

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnStopCnf: ENTERED");

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitGasPlmnStopCnf
 ��������  : �յ�GAS��plmn search stop cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 4.��    ��   : 2014��6��6��
   ��    ��   : b00269685
   �޸�����   : ������Ϊ������ʱ����ʱ�����͵�stop request������Ҫ��������
 5.��    ��   : 2014��6��23��
   ��    ��   : y00245242
   �޸�����   : dts2014061701038�޸�
 6.��    ��   : 2014��6��21��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF );

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* ��G����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��G����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : Was��plmn search stop CNF�����б�����ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 4.��    ��   : 2014��6��6��
   ��    ��   : b00269685
   �޸�����   : ������Ϊ������ʱ����ʱ�����͵�stop request������Ҫ��������
 5.��    ��   : 2014��6��21��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ

****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf: Timer Expired");

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* ��W����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��W����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnSelection_WaitGasPlmnStopCnf
 ��������  : Gas��plmn search stop CNF�����б�����ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 4.��    ��   : 2014��6��6��
   ��    ��   : b00269685
   �޸�����   : ������Ϊ������ʱ����ʱ�����͵�stop request������Ҫ��������
 5.��    ��   : 2014��6��23��
   ��    ��   : y00245242
   �޸�����   : dts2014061701038�޸�
 6.��    ��   : 2014��6��21��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ
****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnSelection_WaitGasPlmnStopCnf: Timer Expired");

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* ��G����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��G����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �յ�WAS��spec plmn search cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��6��03��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/

VOS_VOID NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* ��W����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��W����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �յ�WAS��history plmn search cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��6��03��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/

VOS_VOID NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* ��W����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��W����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �յ�WAS��pref band plmn search cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��12��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);

        return;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_WCDMA == stDestPlmn.enRat)
        {
            /* ��W����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��W����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf
 ��������  : �յ�WAS��plmn search cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��6��25��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ����

 2.��    ��   : 2015��6��3��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    switch ( pstSrchCnfMsg->ulSearchRlt )
    {
        /* ȫƵ��ָ���ѽ���Ĵ��� */
        case RRC_PLMN_SEARCH_RLT_SPEC:
        case RRC_PLMN_SEARCH_RLT_SPEC_NO_RF:
        case RRC_PLMN_SEARCH_RLT_SPEC_FAIL:
            NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(ulEventType, pstMsg);
            break;

        /* ��ʷƵ��ָ���ѽ���Ĵ��� */
        case RRC_PLMN_SEARCH_RLT_HISTORY_SUCC:
        case RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF:
        case RRC_PLMN_SEARCH_RLT_HISTORY_FAIL:
            NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(ulEventType, pstMsg);
            break;

         /* pref band�ѽ���Ĵ��� */
         case RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC:
         case RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF:
         case RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL:
             NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(ulEventType, pstMsg);
             break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf:UNEXPECTED SEARCH RSLT!!!");
            NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf
 ��������  : �յ�GAS��spec plmn search cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��6��3��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�

*****************************************************************************/

VOS_VOID NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF );

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* ��G����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��G����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf
 ��������  : �յ�GAS��history plmn search cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��6��3��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�

*****************************************************************************/

VOS_VOID NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF );

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* ��G����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��G����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf
 ��������  : �յ�GAS��pref band plmn search cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��6��3��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�

*****************************************************************************/
VOS_VOID NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF );

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);

        return;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_GSM == stDestPlmn.enRat)
        {
            /* ��G����㷢����������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* ��G����㷢�͹�������Ǩ�Ƶ���Ӧ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_GSM);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf
 ��������  : �յ�GAS��plmn search cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��6��25��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ����

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    switch ( pstSrchCnfMsg->ulSearchRlt )
    {
        /* ȫƵ��ָ���ѽ���Ĵ��� */
        case RRC_PLMN_SEARCH_RLT_SPEC:
        case RRC_PLMN_SEARCH_RLT_SPEC_NO_RF:
        case RRC_PLMN_SEARCH_RLT_SPEC_FAIL:
            NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(ulEventType, pstMsg);
            break;

        /* ��ʷƵ��ָ���ѽ���Ĵ��� */
        case RRC_PLMN_SEARCH_RLT_HISTORY_SUCC:
        case RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF:
        case RRC_PLMN_SEARCH_RLT_HISTORY_FAIL:
            NAS_MMC_RcvRrMmHistoryPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(ulEventType, pstMsg);
            break;

        /* pref band�ѽ���Ĵ��� */
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF:
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL:
            NAS_MMC_RcvRrMmPrefBandPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf:UNEXPECTED SEARCH RSLT!!!");
            NAS_MMC_RcvRrMmSpecPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}

/************************ ע�Ჿ��*************************************/

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasSysInfoInd
 ��������  : MMC����QUIT��ϵͳ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:QUIT��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE ��Ϣ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��12��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasSysInfoInd
 ��������  : MMC����QUIT��ϵͳ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE ��Ϣ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��12��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitWasSysInfoInd
 ��������  : ����WASϵͳ��Ϣ,
             1)��¼MML��ȫ������ 2)��MM/GMMת��ϵͳ��Ϣ֪ͨ 3)���µ�ǰ���������״̬
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:״̬������ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : z40661 / 40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��11��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�
  3.��    ��   : 2011��10��6��
    ��    ��   : w00167002
    �޸�����   : PhaseII�޸�:ɾ�����ĵ�ǰ�������ע��״̬ΪREGISTERED��
                  ͳһ��ע�����󣬲Ÿ���ΪREGISTERED
  4.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  5.��    ��   : 2012��3��17��
    ��    ��   : w00176964
    �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:����LTE�������ι��ܶ���
  6.��    ��   : 2012��6��16��
    ��    ��   : l00171473
    �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
  7.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : for CS/PS mode 1,��Disable LTEԭ��ֵ
  8 .��    ��   : 2012��8��13��
     ��    ��   : z00161729
     �޸�����   : DCM������������������޸�
  9.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMMA
  10.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
 11.��    ��   : 2013��9��14��
    ��    ��   : w00167002
    �޸�����   : DTS2013090908249:�����û�ָ������24003��CSע�ᱻ��15��MM��LIMIT
                 ״̬����ѡ��״̬���յ�ͬһС����SYSINFO��֪ͨMM��ǰû��FORB FLG,
                 ����MM����ѭ��ע�᣻
                 ��NAS_MMC_SndMmGsmSysInfoInd�����У�������û�ָ����������FORBFLG����Ϊnull��
                 �������ȥ����
                 ��ѡ��״̬��ʶ����Ƿ����û�ָ����������������ȷ��ulForbiddenFlg��־��

12.��    ��   : 2014��1��18��
   ��    ��   : z00234330
   �޸�����   : dts2014011801513,������ϱ���ϵͳ��Ϣ�����п���û��Я��plmnid,
               �˴��жϲ�û���ж�plmnid�Ƿ���Ч
 13.��    ��   : 2014��1��23��
    ��    ��   : z00161729
    �޸�����   : DTS2014012305088:svlte����tds��l��ϵͳ��Ϣ��pstransfer:1��ע���������ʧ�ܣ�psǨ��
                ��modem1��tds��l�ٴ�פ��mmc�յ�ϵͳ��Ϣ�ж�פ����Ϣδ�ı䲻���mma����ϵͳ��Ϣ����
                mtc�޷��ϱ�pstransfer:1,��Ҫ������״̬���˳����mma�ٷ���ϵͳ��Ϣ

 14.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo           = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ֹͣ�ȴ�ϵͳ��Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�Plmn Selectionִ�н�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* פ��С���仯����������ʱ���ϱ�ϵͳ��Ϣ */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    }

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMMAģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ����CSPS��AdditionalAction */
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* ����CSPS��RegCause */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    if ( VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType) )
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM,������ǰϵͳ��Ϣ�� Forbidden ����Я����ȥ */
        NAS_MMC_SndMmWasSysInfoInd(NAS_MML_GetLaiForbType(&(pstCurCampInfo->stLai)),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MML_GetLaiForbType(&(pstCurCampInfo->stLai)),
                                   VOS_FALSE,
                                   pstMsg);
    }

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    /* �յ�ϵͳ��Ϣ��Ǩ�Ƶ��ȴ�CS+PS���ע������������ʱ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitGasSysInfoInd
 ��������  : ����GASϵͳ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:״̬������ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : z40661 / 40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��10��6��
    ��    ��   : w00167002
    �޸�����   : PhaseII�޸�:ɾ�����ĵ�ǰ�������ע��״̬ΪREGISTERED��
                  ͳһ��ע�����󣬲Ÿ���ΪREGISTERED
  4.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  5.��    ��   : 2012��6��16��
    ��    ��   : l00171473
    �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
  6.��    ��   : 2012��8��13��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������:����LTE�������ι��ܶ���
  7.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMMA
  8.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  9.��    ��   : 2013��9��14��
    ��    ��   : w00167002
    �޸�����   : DTS2013090908249:�����û�ָ������24003��CSע�ᱻ��15��MM��LIMIT
                 ״̬����ѡ��״̬���յ�ͬһС����SYSINFO��֪ͨMM��ǰû��FORB FLG,
                 ����MM����ѭ��ע�᣻
                 ��NAS_MMC_SndMmGsmSysInfoInd�����У�������û�ָ����������FORBFLG����Ϊnull��
                 �������ȥ����
                 ��ѡ��״̬��ʶ����Ƿ����û�ָ����������������ȷ��ulForbiddenFlg��־��
 10.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 11.��    ��   : 2014��1��23��
    ��    ��   : z00161729
    �޸�����   : DTS2014012305088:svlte����tds��l��ϵͳ��Ϣ��pstransfer:1��ע���������ʧ�ܣ�psǨ��
                ��modem1��tds��l�ٴ�פ��mmc�յ�ϵͳ��Ϣ�ж�פ����Ϣδ�ı䲻���mma����ϵͳ��Ϣ����
                mtc�޷��ϱ�pstransfer:1,��Ҫ������״̬���˳����mma�ٷ���ϵͳ��Ϣ

 12.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
    /* Added by t00212959 for DCM�����������������, 2012-8-13, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-13, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ֹͣ�ȴ�ϵͳ��Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM�����������������, 2012-8-13, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-13, end */

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* פ��С���仯����������ʱ���ϱ�ϵͳ��Ϣ */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMMAģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ����CSPS��AdditionalAction */
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* ����CSPS��RegCause */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();


    /* ���û�ָ������ʱ������ҪЯ��FORB���� */
    if ( VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType) )
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM,������ǰϵͳ��Ϣ�� Forbidden ����Я����ȥ */
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MML_GetLaiForbType(&(pstCurCampInfo->stLai)),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MML_GetLaiForbType(&(pstCurCampInfo->stLai)),
                                   VOS_FALSE,
                                   pstMsg);

    }

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    /* �յ�ϵͳ��Ϣ��Ǩ�Ƶ��ȴ�CS+PS���ע������������ʱ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitWasSysInfoInd
 ��������  : �ȴ�Wϵͳ��Ϣ��ʱ��ͬ�����Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:״̬������ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��25��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��12��15��
    ��    ��   : W00166186
    �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
  4.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  5.��    ��   : 2012��06��02��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2013��8��27��
    ��    ��   : l00208543
    �޸�����   : Coverity
  8.��    ��   : 2014��4��14��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����ʱ���·���״̬
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    VOS_UINT32                          ulResult;

	/* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitWasSysInfoInd: Timer Expired");

    /*�����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

       /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /*��ȡ��һ��Ҫ����������,����ȡʧ�ܣ�����ϲ�״̬���ϱ�����ʧ�ܣ��˳�
      ����ȡ�ɹ������ж���һ��Ҫ�����������Ƿ��뵱ǰפ��������ͬ��
      ����ͬ���ڵ�ǰģʽ�����������������ǰ����
     */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /*  ��ȡ�¸�����ʧ�ܣ�����г����������� */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    /* ��MM��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, end */

    /*��һ��Ҫ�����������Ƿ��뵱ǰפ�����粻ͬ,��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ�� */
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    else
    {
        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitGasSysInfoInd
 ��������  : �ȴ�gϵͳ��Ϣ��ʱ��ͬ�����Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:״̬������ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��25��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��21��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��12��15��
    ��    ��   : W00166186
    �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
  4.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  5.��    ��   : 2012��06��02��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  6.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  7.��    ��   : 2013��8��27��
    ��    ��   : l00208543
    �޸�����   : Coverity
  8.��    ��   : 2014��4��14��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����ʱ���·���״̬
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    VOS_UINT32                          ulResult;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitGasSysInfoInd: Timer Expired");

    /*�����ǰ��Ҫ�˳�״̬��*/
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /*��ȡ��һ��Ҫ����������,����ȡʧ�ܣ�����ϲ�״̬���ϱ�����ʧ�ܣ��˳�
      ����ȡ�ɹ������ж���һ��Ҫ�����������Ƿ��뵱ǰפ��������ͬ��
      ����ͬ���ڵ�ǰģʽ�����������������ǰ����
     */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /*  ��ȡ�¸�����ʧ�ܣ�����г�����������*/
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    /* ��MM��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, end */

    /*��һ��Ҫ�����������Ƿ��뵱ǰפ�����粻ͬ,��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ��*/
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    else
    {
        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : �ڵȴ�CS+PS�ϱ�ע������ʱ���յ�QUIT��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��11��8��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseII�׶ν���ػ�������

  4.��    ��   : 2011��11��29��
    ��    ��   : w00167002
    �޸�����   : DTS2011112301233:���Ӵ���¼�ID��״̬������֪����ʲô�¼�
                ����Լ��ġ�
                �޸�ԭ��:�û��·��ػ�����󣬵�ǰ�����ڵ�ע���������ڵ�����
                �ͷţ�������Ҫ�ȽϾõ�ʱ����ܴ���ػ����ͨ�����Ӵ���¼���
                ��鵱ǰ�ڵ�ע�������ߵ������ͷ�״̬�����յ��ػ������ֱ��
                �˳���ǰ״̬���������û��Ĺػ����
  5.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegFlag;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* ������������û�����Ĺػ�����ֱ���˳���ע����״̬�� */
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    ucWaitRegFlag = NAS_MMC_GetWaitRegRsltFlag_PlmnSelection();

    /* ��ǰû�����ӿ���ֱ���˳�����Ҫָcs/psע�ᱻ�ܣ���cause17,��Ҫ�����ȴ�ע��������� */
    if (( VOS_FALSE == NAS_MML_IsRrcConnExist())
     || (NAS_MMC_WAIT_REG_RESULT_IND_NULL == ucWaitRegFlag))
    {

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����Abort��־ */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /* �����Ҫ�����˳� */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);
        NAS_MMC_SndRelReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : WAIT_CS_PS״̬��PS��ע�ᡢRAU����Ĵ�����ں���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��12��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��14��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:�û�ָ�����֪꣬ͨ�����RRC_NAS_FORBLA_CHANGE
                 ��Ϣ
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  5.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    enCurrentFsmId      = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType  = NAS_MMC_GetCurrFsmEventType();

    pstPsRegRslt        = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* ���CCOʧ�ܻ��˹������յ�����ϵͳ��ע����������Ҫ���� */
    if (pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����ȴ�PSע����mask */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ����ע��������Ӧ����: ���÷���״̬����¼Causeֵ��������һ���������ͣ�֪ͨ��Ӧ��� */
    NAS_MMC_ProcPsRegRslt_PlmnSelection(pstPsRegRslt);

    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /* ���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬�� */
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

            /* �û�ָ������ɺ���Ҫ��MMLȫ�ֱ����еĽ�ֹ����LA��Ϣ֪ͨ�����*/
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ���ϲ�״̬������������� ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
        {
            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* ��LMM�����û���������֪ͨ */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif
        }

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : WAIT_CS_PS״̬��LU���(�ɹ���ʧ��)����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : luokaihui / l00167671
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��14��
   ��    ��   : l00130025
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������
 3.��    ��   : 2011��11��14��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:�û�ָ�����֪꣬ͨ�����RRC_NAS_FORBLA_CHANGE
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
                 ��Ϣ
 5.��    ��   : 2014��7��17��
   ��    ��   : w00167002
   �޸�����   : DTS2014070304051:��GSM:A������CSע��ɹ���PSע��ʧ��14����B������
                CS/PS��ע��ɹ�������ָ���ѻص�A�����ϣ�����CSע��ɹ�������A�����PS������FORB GPRS�У�
                �����ʱû�з���PSע�ᣬ���ܽ���PDP���
                �Աȱ�˿�����A�����Ϸ���ע�ᡣ
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* ���CCOʧ�ܻ��˹������յ�����ϵͳ��ע����������Ҫ���� */
    if (pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����ȴ�CSע����mask */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);

    /* ����ע��������Ӧ����: ���÷���״̬����¼Causeֵ��������һ���������ͣ�֪ͨ��Ӧ��� */
    NAS_MMC_ProcCsRegRslt_PlmnSelection(pstCsRegRslt);

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {

            /* ��GSM�£����CSע��ɹ���PSδע�ᣬ��ɾ��FORB GPRS��Ϣ */
            NAS_MMC_ProcUserSpecPlmnSrchForbGprsInfo_PlmnSelection();

            /*���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬��*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

            /* �û�ָ������ɺ���Ҫ��MMLȫ�ֱ����еĽ�ֹ����LA��Ϣ֪ͨ�����*/
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /*�����ǰ��Ҫ�˳�״̬��*/
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : �ȴ�������ע�����RAU���ʱ��ʱ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : luokaihui / l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��12��15��
    ��    ��   : W00166186
    �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
  4.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  5.��    ��   : 2011��2��11��
    ��    ��   : w00176964
    �޸�����   : DTS2012012002472:GU�µȴ�ע����ʱ��CS����ҵ�����ʱ���ȴ�ע��
                 �����ʱ����ʱ��RRC�����ͷź�MMC�쳣����������
  6.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAdditionalAction;
    NAS_MMC_FSM_ID_ENUM_UINT32           enCurrentFsmId;
    VOS_UINT32                           ulCurrentEventType;

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnSelection_WaitCsPsRegRsltInd: Timer Expired");

    /* �����ǰ�ȴ�ע��ı�ʶ */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

        /* ���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬�� */
        NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

#if   (FEATURE_ON == FEATURE_LTE)
        /* ��LMM�����û���������֪ͨ */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif

    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ���ϲ�״̬������������� ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();

    /* �ȴ�CS PS��ע����ʱ���п���һ������ע�������˺����Լ��������е�ҵ��
      (����G�½���CS����к��У�PS���޷�����ע��),����MMCһ�µȲ�������һ�����
      ע��������ʱMMCֱ��ͨ��additional��������������MMC��ʱ���ݵ�ǰ�յ���ע
      �������µ�additionalֵ�������Ƿ�ɹ��˳�����״̬������ʧ���˳�����״̬����
      ��L1״̬����������״̬�����˳���������Ƿ�����������ѡ����ʱ�����Ǽ����ȴ�
      ҵ������Լ�CSPS��ע���� */

    enAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* ���Ӳ���Ϊפ����ǰ���� */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enAdditionalAction))
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);
    }
    else
    {
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : �ȴ�ע����ʱ,�յ����緢���Detach����,
             attach �����е�detach ��Ҫ�ȷ�attach������ٷ�detach���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��7��
   ��    ��   : sunxibo / 46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��14��
   ��    ��   : l00130025
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������
 3.��    ��   : 2011��11��14��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:�û�ָ�����֪꣬ͨ�����RRC_NAS_FORBLA_CHANGE
 4.��    ��   : 2011��11��14��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:��ǰ��Ϊѡ��״̬��������ӽ�ֹ������Ϣ
                ��ѡ��״̬���Ľ�ֹ����LA������ȥ
 5.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
 6.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 7.��    ��   : 2012��2��13��
   ��    ��   : w00167002
   �޸�����   : DTS2011122704039:additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  8.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    MMCGMM_NETWORK_DETACH_IND_STRU     *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;
    NAS_MMC_FSM_ID_ENUM_UINT32           enCurrentFsmId;
    VOS_UINT32                           ulCurrentEventType;

    pstDetachMsg = (MMCGMM_NETWORK_DETACH_IND_STRU*)pstMsg;

    /* ���ݵ�ǰ��Detach���ͣ� �����´��� */
    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* ��¼Ps ��ע���� */
    NAS_MMC_SetPsRegCause_PlmnSelection((NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);


    /* ������ԭ��ֵΪ#15, ����ӽ�ֹ������Ϣ��ѡ��״̬���Ľ�ֹ����LA������ȥ,
       ���û�ָ������ʱ������Ҫ�ѽ�ֹLA��������� */
    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
      && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstDetachMsg->ulDetachCause) )
    {
        NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                               NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
    }

    /* ��Ҫ����ע��ʱ������Ҫִ�к����Ķ��� */
    if (NAS_MMC_GMM_NT_DETACH_REATTACH == pstDetachMsg->ulDetachType)
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

#if   (FEATURE_ON == FEATURE_LTE)
    /* ��LMM����detach�����Ϣ */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
        (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /* ���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬�� */
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

            /* �û�ָ������ɺ���Ҫ��MMLȫ�ֱ����еĽ�ֹ����LA��Ϣ֪ͨ�����*/
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ��ϲ�״̬��������� ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : ��ServiceRequest����Ĳ�������
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������;
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��14��
   ��    ��   : l00130025
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������

 2.��    ��   : 2011��11��14��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:�û�ָ�����֪꣬ͨ�����RRC_NAS_FORBLA_CHANGE
                 ��Ϣ
 3.��    ��   : 2011��11��14��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:��ǰ��Ϊѡ��״̬��������ӽ�ֹ������Ϣ
                ��ѡ��״̬���Ľ�ֹ����LA������ȥ
 4.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
 5.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 6.��    ��   : 2012��2��13��
   ��    ��   : w00167002
   �޸�����   : DTS2011122704039:additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  7.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

    pstServiceRsltInd = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* ����Service Reqest Result ��������ͬ���� */
    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstServiceRsltInd->enActionResult)
    {
        /* ���·���״̬ */
        NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_NULL);

        /* ����PS��AdditionalAction */
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
        /* ��LMM����Service requestResult�����Ϣ����*/
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);

#endif

    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcPsServiceRegFail(pstServiceRsltInd);

        NAS_MMC_SetPsRegCause_PlmnSelection(pstServiceRsltInd->enRegFailCause);


        /* ������ԭ��ֵΪ#15, ����ӽ�ֹ������Ϣ��ѡ��״̬���Ľ�ֹ����LA������ȥ,
           ���û�ָ������ʱ������Ҫ�ѽ�ֹLA��������� */
        if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
          && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstServiceRsltInd->enRegFailCause) )
        {
            NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                                   NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
        }

        /* AdditionalAction��Ч������PS����һ���Ķ������� */
        if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
        {
            NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
        }

#if (FEATURE_ON == FEATURE_LTE)
        /* ��LMM����Service requestResult�����Ϣ���� */
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = pstServiceRsltInd->enRegFailCause;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    }

    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause, enPsRegCause))
        {
            /* ���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬�� */
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

            /* �û�ָ������ɺ���Ҫ��MMLȫ�ֱ����еĽ�ֹ����LA��Ϣ֪ͨ�����*/
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }


    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : �ȴ������ͷ�״̬ʱ�յ�CSҵ���¿���Ч����Ϣ(MMCMM_CM_SERVICE_REJECT_IND)
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��13��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��14��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:�û�ָ�����֪꣬ͨ�����RRC_NAS_FORBLA_CHANGE
                 ��Ϣ
 3.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    MMCMM_CM_SERVICE_REJECT_IND_STRU   *pstRcvMsg = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
#endif
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    pstRcvMsg = (MMCMM_CM_SERVICE_REJECT_IND_STRU*)pstMsg;

#if (FEATURE_ON == FEATURE_LTE)
    stActionRslt.enProcType     = NAS_MML_PROC_CM_SER;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstRcvMsg->ulCause;
    stActionRslt.ulAttemptCount = 0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);

#endif

    /*CmService Rejֻ�� #4��#6����ʱ���ᷢ�͸�MMC */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstRcvMsg->ulCause)
    {
        /* ���CS��ĵȴ���־ */
        NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);

        /* �����µ�enCsAdditioalActionΪAnycell */
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }


    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /*���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬��*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

            /* �û�ָ������ɺ���Ҫ��MMLȫ�ֱ����еĽ�ֹ����LA��Ϣ֪ͨ�����*/
            NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }


    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : WAS�ϱ���SUSPEND_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : VOS_TRUE:���ش���ɹ�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : W00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��14��
   ��    ��   : l00130025
   �޸�����   : PhaseII�޸�����״̬��
 3.��    ��   : 2013��8��5��
   ��    ��   : w00167002
   �޸�����   : DTS2013073106748:�����ֶ�ģʽG����24003 CS��ע��ɹ���PS��
                ע��ʧ��17����ѡ��״̬�����û�����绰���л���W�µ�46002�����ϡ�
                �绰�ҶϺ�W�ϱ�����,ѡ��״̬����ANYCELL������û����ԭ�е�24003���硣
                �޸�Ϊѡ��״̬����ע����ʱ������յ�HO�л��ɹ������˳�
                ѡ��״̬��,���绰����������L1 MAIN����ѡ��״̬����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstSuspendMsg = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    enRat         = NAS_MML_GetCurrNetRatType();

    /* ���ΪOOS���߲�������ȷ, �����������ϵͳ��ѡ */
    if ((MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendMsg->ucSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= pstSuspendMsg->ucSuspendCause))
    {
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);
    }
    else
    {
        NAS_MMC_SetInterSysSuspendRat_PlmnSelection(enRat);

        NAS_MMC_LoadInterSysFsm_PlmnSelection(pstSuspendMsg->ucSuspendCause);
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : GAS�ϱ���SUSPEND_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : VOS_TRUE:���ش���ɹ�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�����״̬��
  3.��    ��   : 2013��8��5��
    ��    ��   : w00167002
    �޸�����   : DTS2013073106748:�����ֶ�ģʽG����24003 CS��ע��ɹ���PS��
                ע��ʧ��17����ѡ��״̬�����û�����绰���л���W�µ�46002�����ϡ�
                �绰�ҶϺ�W�ϱ�����,ѡ��״̬����ANYCELL������û����ԭ�е�24003���硣
                �޸�Ϊѡ��״̬����ע����ʱ������յ�HO�л��ɹ������˳�
                ѡ��״̬��,���绰����������L1 MAIN����ѡ��״̬����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRMM_SUSPEND_IND_ST                *pstSuspendMsg = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    enRat         = NAS_MML_GetCurrNetRatType();

    /* ���ΪOOS���߲�������ȷ, �����������ϵͳ��ѡ */
    if ((MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendMsg->ucSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= pstSuspendMsg->ucSuspendCause))
    {
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, UEPS_PID_GAS);
    }
    else
    {
        NAS_MMC_SetInterSysSuspendRat_PlmnSelection(enRat);

        NAS_MMC_LoadInterSysFsm_PlmnSelection(pstSuspendMsg->ucSuspendCause);
    }


    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSuspendFailCauseArealost_WaitCsPsRegRsltInd
 ��������  : ����״̬�����յ�MmcMmcSuspendRslt�Ľ��Ϊʧ����ԭ��ֵΪarea lost
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��27��
    ��    ��   : l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  3.��    ��   : 2013��8��27��
    ��    ��   : l00208543
    �޸�����   : Coverity
  4.��    ��   : 2014��4��14��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����ʱ���·���״̬
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvSuspendFailCauseArealost_WaitCsPsRegRsltInd(VOS_VOID
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    VOS_UINT32                          ulResult;

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

	/* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ֹͣ�ȴ�ע������Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* ��ȡ�����ȼ������б� */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /* ��ȡ�¸�����ʧ�� */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        return VOS_TRUE;
    }

    /* ��ȡ��ǰפ����������Ϣ */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = stDestPlmn.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* ���µ�ǰ���������״̬Ϊ��ע������ڴ��ָ����ȼ������У��������Ѵ����� */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                            pstPlmnSelectionListInfo);
    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /*��ȡ��һ��Ҫ����������,����ȡʧ�ܣ�����ϲ�״̬���ϱ�����ʧ�ܣ��˳�
      ����ȡ�ɹ������ж���һ��Ҫ�����������Ƿ��뵱ǰפ��������ͬ��
      ����ͬ���ڵ�ǰģʽ�����������������ǰ����
     */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /* ��ȡ�¸�����ʧ�ܣ�����г����������� */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    /* ��MM��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, end */

    /*��һ��Ҫ�����������Ƿ��뵱ǰפ�����粻ͬ,��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ��*/
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    /* ����ҪSuspend */
    else
    {
        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvSuspendRsltHoSucc_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : ����״̬�����յ�MmcMmcSuspendRslt�Ľ��Ϊ�л��ɹ��Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg     :��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��6��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_RcvSuspendRsltHoSucc_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CONN_STATUS_INFO_STRU                          *pstConnStatus       = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         ucInterSysSuspendRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         ucCurrRat;

    enCurrentFsmId       = NAS_MMC_GetCurrFsmId();
    pstConnStatus        = NAS_MML_GetConnStatus();
    ucInterSysSuspendRat = NAS_MMC_GetInterSysSuspendRat_PlmnSelection();
    ucCurrRat            = NAS_MML_GetCurrNetRatType();

#if (FEATURE_LTE == FEATURE_ON)

    /* Ǩ�Ƶ���ͬ�Ľ��뼼��ʱ����ҪǨ�Ƶ���ͬ�Ĵ���ע����״̬ */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* ֹͣ��ǰ�ȴ�CS/PSע������״̬ */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

#endif

    /* ��ע����ʱ�������ǰ��CSҵ������ʱ��������ϵͳ�л�������״̬����L1 */
    if ( (VOS_TRUE  == pstConnStatus->ucCsServiceConnStatusFlg)
      && (ucCurrRat != ucInterSysSuspendRat) )
    {
        /* ֹͣ��ǰ�ȴ�CS/PSע������״̬ */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* ��ǰ�û��������ָ������,��ظ�ע�����ɹ� */
        ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

        if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
        {
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);

            /* ���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬�� */
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

#if   (FEATURE_ON == FEATURE_LTE)
            /* ��LMM�����û���������֪ͨ */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif
        }

        enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
        enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();

        /* �ȴ�CS PS��ע����ʱ���п���һ������ע�������˺����Լ��������е�ҵ��,
           ������G<->W֮�����ϵͳ���л�(����G�½���CS����к��У�PS���޷�����ע��),
           �绰����������ǰ����绰������״̬������ΪREGISTERED,�����ѡ��״̬��������
           ȥѡ����ǰ���Ե����硣MMC��ʱ���ݵ�ǰ�յ���ע�������µ�additionalֵ������
           �Ƿ�ɹ��˳�����״̬������ʧ���˳�����״̬��,��L1״̬����������״̬�����˳�
           ��������Ƿ�����������ѡ����ʱ�����Ǽ����ȴ�ҵ������Լ�CSPS��ע���� */

        enAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

        /* ���Ӳ���Ϊפ����ǰ���� */
        if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON  == enAdditionalAction)
         || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION  == enAdditionalAction)
         || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
         || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED   == enAdditionalAction))
        {
            /* �ظ�״̬���˳��ɹ� */
            NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);
        }
        else
        {
            NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
        }

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : ����SUSPEND״̬��������ɵĺ���
 �������  : ulEventType:��Ϣ����
             pstMsg:NAS_MM_LAYER_MMCMMC_SUSPEND_RSLT��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��10��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  3.��    ��   : 2011��12��30��
    ��    ��   : l65478
    �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                 ���ݾ����ԭ��ֵ������
  4.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  5.��    ��   : 2013��02��27��
    ��    ��   : l00167671
    �޸�����   : DTS2013022608712����������������ɹ��ȴ�ע��ʱ�ض���ʧ�������յ�������Ϣ
  6.��    ��   : 2013��8��5��
    ��    ��   : w00167002
    �޸�����   : DTS2013073106748:�����ֶ�ģʽG����24003 CS��ע��ɹ���PS��
                ע��ʧ��17����ѡ��״̬�����û�����绰���л���W�µ�46002�����ϡ�
                �绰�ҶϺ�W�ϱ�����,ѡ��״̬����ANYCELL������û����ԭ�е�24003���硣
                �޸�Ϊѡ��״̬����ע����ʱ������յ�HO�л��ɹ������˳�
                ѡ��״̬��,���绰����������L1 MAIN����ѡ��״̬��
  7.��    ��   : 2013��2��7��
    ��    ��   : W00176964
    �޸�����   : Volte_phase3��Ŀ����:����IMS������ʱdisable Lģ���߼��޸�
  8.��    ��   : 2013��4��9��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬��������ʧ��Ǩ�Ƶ�ooc
  9.��    ��   : 2014��6��30��
    ��    ��   : b00269685
    �޸�����   : DSDS GUNAS III��Ŀ:�޸ĺ�������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRsltMsg = VOS_NULL_PTR;

    pstSuspendRsltMsg = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    if (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST != pstSuspendRsltMsg->enFailCause)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitCsPsRegRsltInd(): snd Mode change");
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());
    }


    /* HO�ɹ��Ĵ��� */
    if ( (MMC_SUSPEND_CAUSE_HANDOVER == pstSuspendRsltMsg->enSuspendCause)
      && (NAS_MMC_SUSPEND_SUCCESS    == pstSuspendRsltMsg->enRslt) )
    {
        NAS_MMC_RcvSuspendRsltHoSucc_PlmnSelection_WaitCsPsRegRsltInd(ulEventType, pstMsg);

        return VOS_TRUE;
    }

    /* �����ѡ���Ϊʧ��,ԭ��Ϊ��������,����ע������г����������� */
    if ((NAS_MMC_SUSPEND_FAIL == pstSuspendRsltMsg->enRslt)
     && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST == pstSuspendRsltMsg->enFailCause))
    {
        if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

            /* ״̬���˳����Ϊʧ�ܣ�Ǩ�Ƶ�OOC */
            NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_GetCurrNetRatType());

            return VOS_TRUE;
        }

        /*�����ǰ��Ҫ�˳�״̬��*/
        if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

            /* �ظ�״̬���˳��ɹ� */
            NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

            /* ֱ���˳���ǰ״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }
        else
        {
            return NAS_MMC_RcvSuspendFailCauseArealost_WaitCsPsRegRsltInd();
        }
    }

#if (FEATURE_LTE == FEATURE_ON)

    /* Ǩ�Ƶ���ͬ�Ľ��뼼��ʱ����ҪǨ�Ƶ���ͬ�Ĵ���ע����״̬ */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* ֹͣ��ǰ�ȴ�CS/PSע������״̬ */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);


        /* HO�ɹ��Ĵ����װ��NAS_MMC_RcvSuspendRsltHoSucc_PlmnSelection_WaitCsPsRegRsltInd */

        /* ���µ�ǰ�ȴ�EPS��ע���� */
        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_IMS)
        /* ���ӵȴ�IMS�Ƿ���ý��FLG,MMA��֤�յ�PSע�����ϱ�IMS�Ƿ����ָʾ��MMC */
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, end */

        /* ����CS��ע��Cause��AdditionalAction */
        NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* Ǩ�Ƶ��ȴ�ע������״̬PLMN_SRCH:NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }

#endif

     /* ��Intersys״̬������ϴ���������
     switch (pstSuspendRsltMsg->enRslt)
     {
         case NAS_MMC_SUSPEND_SUCCESS:
         break;

         case NAS_MMC_SUSPEND_FAIL :
         case NAS_MMC_SUSPEND_QUIT :

         break;

         case NAS_MMC_SUSPEND_AREA_LOST :
         break;

         default:

         break;
     }
     */


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : �ȴ�������ע����ʱ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��7��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��11��9��
    ��    ��   : w00167002
    �޸�����   : ��ע��������յ�����ָʾ������µ�ǰ�������ע��״̬Ϊ
                  NAS_MMC_NET_STATUS_SEARCHED_REGISTERED��
  4.��    ��   : 2011��12��15��
    ��    ��   : W00166186
    �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
  5.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  6.��    ��   : 2012��06��02��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  7.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  8.��    ��   : 2013��8��27��
    ��    ��   : l00208543
    �޸�����   : Coverity
  9.��    ��   : 2013��4��9��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬��������ʧ��Ǩ�Ƶ�ooc
 10.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
 11.��    ��   : 2014��4��14��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:����ʱ���·���״̬
 12.��    ��   : 2014��6��30��
    ��    ��   : b00269685
    �޸�����   : �޸ĺ�������
 13.��    ��   : 2014��10��13��
    ��    ��   : w00167002
    �޸�����   : DTS2014102005694:G�£�CSע��ɹ���PS��δע��ɹ�ʱ����
               ����绰ҵ���ڵ绰ҵ����ʱ������MMû���ͷ����MMCû�з���ANY
               CELL������
 14.��    ��   : 2015��1��8��
    ��    ��   : w00167002
    �޸�����   : DTS2015010601540:��CSע��ɹ���PSע��ʧ��ʱ���ڼ����ȴ�ע���
                  ���У�������ռ��Դ����NO RF�������ڵȴ���Դ���ú����´���������ǰ
                  ���硣
 15.��    ��   : 2015��10��22��
    ��    ��   : s00217060
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND��Ϣ�ӿڱ��
 16.��    ��   : 2016��03��17��
    ��    ��   : j00174725
    �޸�����   : DTS2016031602848(eara lost ʱ����������û���չ�, ��Ҫ����ǰPLMN����һ��)
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    VOS_UINT32                          ulResult;

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo    = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo              = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    RRMM_AREA_LOST_IND_STRU                                *pstAreaLost                 = VOS_NULL_PTR;

    NAS_MML_PLMN_WITH_CNT_AND_RAT_STRU                     *pstLastAreaLostPlmnInfo     = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsRrcSearchPlmn;

    pstAreaLost     = (RRMM_AREA_LOST_IND_STRU*)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ֹͣ�ȴ�ע������Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);


    /* ��ȡ��ǰפ����������Ϣ */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */


    /* ��ȡ�����ȼ������б� */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();


    ulIsRrcSearchPlmn       = NAS_MMC_IsGuRrcSearchedAreaLostPlmn(pstAreaLost);
    pstLastAreaLostPlmnInfo = NAS_MMC_GetLastAreaLostPLmnInfoCtx_PlmnSelection();

    NAS_MMC_UpdateLastAreaLostPlmnWIthRatAndCnt(pstLastAreaLostPlmnInfo, &stCurPlmn.stPlmnId, stCurPlmn.enRat);

    /* �ڵȴ�ע����ʱ�������NO RF���������򲻸��µ�ǰΪREGISTER״̬���ȴ���Դ
       ����ʱ�򣬿��Լ����������ڴ������Ͻ���ע�� */
    if (RRC_NAS_NO_RF_AREA_LOST != pstAreaLost->ulRptMode)
    {
        /* ���µ�ǰ���������״̬Ϊ��ע������ڴ��ָ����ȼ������У��������Ѵ����� */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                            pstPlmnSelectionListInfo);

        /* �����Ƿ���й�history��־,���й�pref band�ѻ�spec��ʱ��Ҳ��Ϊ�Ѿ����й�history���� */
        if (VOS_TRUE == ulIsRrcSearchPlmn)
        {
            NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_GetCurrNetRatType(), VOS_TRUE);
        }

    }
    else
    {
        /* ���µ�ǰ���������״̬Ϊ���ڣ���NO RF��Դ�ָ������������ǰ���� */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_EXIST,
                                            pstPlmnSelectionListInfo);
    }

    NAS_WARNING_LOG2(WUEPS_PID_MMC,"NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd: ulIsRrcSearchPlmn = %d , %d",
                                            ulIsRrcSearchPlmn, NAS_MML_GetLastAreaLostPlmnCnt(pstLastAreaLostPlmnInfo));

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());


    /* ֪ͨMM/GMM���붪��,MM���ͷ�CSҵ�� */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    if (RRC_NAS_NO_RF_AREA_LOST == pstAreaLost->ulRptMode)
    {
        /* �ظ�״̬��ʧ�� */
        NAS_MMC_ProcNoRfAreaLost_PlmnSelection(NAS_MML_GetCurrNetRatType());

        return VOS_TRUE;
    }

    /*�����ǰ��Ҫ�˳�״̬��*/
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd: abort");
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    if ( (NAS_MML_GetLastAreaLostPlmnCnt(pstLastAreaLostPlmnInfo) >= NAS_MMC_AREA_LOST_SEARCH_MAX_NUM)
      || (VOS_TRUE == ulIsRrcSearchPlmn) )
    {
        /*��ȡ��һ��Ҫ����������,����ȡʧ�ܣ�����ϲ�״̬���ϱ�����ʧ�ܣ��˳�
          ����ȡ�ɹ������ж���һ��Ҫ�����������Ƿ��뵱ǰפ��������ͬ��
          ����ͬ���ڵ�ǰģʽ�����������������ǰ����
         */
        ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

        /* ��ȡ�¸�����ʧ�ܣ�����г����������� */
        if (VOS_TRUE != ulResult)
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd: NAS_MMC_GetNextSearchPlmn_PlmnSelection false");
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

            return VOS_TRUE;
        }
        
    }
    else
    {
        stDestPlmn.stPlmnId.ulMcc   = stCurPlmn.stPlmnId.ulMcc;
        stDestPlmn.stPlmnId.ulMnc   = stCurPlmn.stPlmnId.ulMnc;
        stDestPlmn.enRat            = stCurPlmn.enRat;
    }

    /* ��MM��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, end */

    /*��һ��Ҫ�����������Ƿ��뵱ǰפ�����粻ͬ,��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ��*/
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    /* ����ҪSuspend */
    else
    {
        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : �ڵȴ�CS+PSע��������յ�Wģʽϵͳ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��14��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��10��6��
    ��    ��   : w00167002
    �޸�����   : PhaseII�޸�:ɾ�����ĵ�ǰ�������ע��״̬ΪREGISTERED��
                  ͳһ��ע�����󣬲Ÿ���ΪREGISTERED
  4.��    ��   : 2011��11��28��
    ��    ��   : w00167002
    �޸�����   : DTS2011112406707:ɾ������ǰ��Additional Action���г�ʼ���Ĵ���.
                �޸�ԭ��:��ROAMING BROKERʱ������1��ʧ��,ע��ʧ��1�κ�
                MMC��Ҫ����������MMC����Ҫ��������Ľ��(����ѡ��״̬��)��
                ���յ�ϵͳ��Ϣ��ʱ�򣬼����̻����MMC��AdditionalAction��ֵ,
                ����ROMING BROKER����ʧЧ��
  5.��    ��   : 2012��5��10��
    ��    ��   : l65478
    �޸�����   : DTS2012050500988:NMO Iʱ,PSע��ʧ��#11,�յ�ϵͳ��Ϣ���ַ�����ע��
  6.��    ��   : 2012��6��16��
    ��    ��   : l00171473
    �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
  7.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
  8.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMMA
  9.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����

 10.��    ��   : 2013��9��14��
    ��    ��   : w00167002
    �޸�����   : DTS2013090908249:�����û�ָ������24003��CSע�ᱻ��15��MM��LIMIT
                 ״̬����ѡ��״̬���յ�ͬһС����SYSINFO��֪ͨMM��ǰû��FORB FLG,
                 ����MM����ѭ��ע�᣻
                 ��NAS_MMC_SndMmGsmSysInfoInd�����У�������û�ָ����������FORBFLG����Ϊnull��
                 �������ȥ����
                 ��ѡ��״̬��ʶ����Ƿ����û�ָ����������������ȷ��ulForbiddenFlg��־��
 11.��    ��   : 2014��1��18��
    ��    ��   : z00234330
    �޸�����   : dts2014011801513,������ϱ���ϵͳ��Ϣ�����п���û��Я��plmnid,
               �˴��жϲ�û���ж�plmnid�Ƿ���Ч

 12.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */
   /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* פ��С���仯ʱ���ϱ�ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    }

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMMAģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ����CSPS��RegCause */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);



    /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM,������ǰϵͳ��Ϣ�� Forbidden ����Я����ȥ */

    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);
    }


#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : �ڵȴ�CS+PSע��������յ�Gģʽϵͳ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��14��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��10��6��
    ��    ��   : w00167002
    �޸�����   : PhaseII�޸�:ɾ�����ĵ�ǰ�������ע��״̬ΪREGISTERED��
                  ͳһ��ע�����󣬲Ÿ���ΪREGISTERED
  4.��    ��   : 2011��11��28��
    ��    ��   : w00167002
    �޸�����   : DTS2011112406707:ɾ������ǰ��Additional Action���г�ʼ���Ĵ���.
                �޸�ԭ��:��ROAMING BROKERʱ������1��ʧ��,ע��ʧ��1�κ�
                MMC��Ҫ����������MMC����Ҫ��������Ľ��(����ѡ��״̬��)��
                ���յ�ϵͳ��Ϣ��ʱ�򣬼����̻����MMC��AdditionalAction��ֵ,
                ����ROMING BROKER����ʧЧ��
  5.��    ��   : 2012��5��10��
    ��    ��   : l65478
    �޸�����   : DTS2012050500988:NMO Iʱ,PSע��ʧ��#11,�յ�ϵͳ��Ϣ���ַ�����ע��
  6.��    ��   : 2012��6��16��
    ��    ��   : l00171473
    �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
  7.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
  8.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMMA
  9.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
 10.��    ��   : 2013��9��14��
    ��    ��   : w00167002
    �޸�����   : DTS2013090908249:�����û�ָ������24003��CSע�ᱻ��15��MM��LIMIT
                 ״̬����ѡ��״̬���յ�ͬһС����SYSINFO��֪ͨMM��ǰû��FORB FLG,
                 ����MM����ѭ��ע�᣻
                 ��NAS_MMC_SndMmGsmSysInfoInd�����У�������û�ָ����������FORBFLG����Ϊnull��
                 �������ȥ����
                 ��ѡ��״̬��ʶ����Ƿ����û�ָ����������������ȷ��ulForbiddenFlg��־��
 11.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ

 12.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* פ��С���仯ʱ���ϱ�ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    }

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMMAģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ����CSPS��RegCause */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);


    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);
    }

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : MMC����MSCC�����SYSCFG������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:SYSCFG������Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: �������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��04��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֱ�ӵ���syscfg���״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : MMC����MSCC�����ָ��������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��04��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��12��31��
    ��    ��   : w00166186
    �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;

    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �����ֶ�������Ϣ */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                       pstUserSelReqMsg->enAccessMode);

    /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* �����û�ָ�������������³�ʼ��ѡ���б�, Ŀǰֻ�е�ǰע��������ָ������������ͬʱ���Ż��ߵ���һ�� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* ���û�ָ�����뼼��������(Ҳ�ǵ�ǰ����)����Ϊ������ע������ظ�ע�� */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause, enPsRegCause))
    {
        return VOS_TRUE;
    }

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : ����SYSCFG״̬�����صĽ��
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : ����MM�� Abort ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��12��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stGuActionRslt;
#endif

    pstMmAbortInd = (MMMMC_ABORT_IND_STRU*)pstMsg;

    /* ���ԭ��ֵ��Ϊ#6���Ҳ�Ϊ#17��ֱ�ӷ��� */
    if ((NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME != (pstMmAbortInd->enAbortCause))
     && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != (pstMmAbortInd->enAbortCause)))
    {
        return VOS_TRUE;
    }

    /* ���ԭ��ֵ#6������CS AdditionΪAnycellפ�� */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstMmAbortInd->enAbortCause)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* ��LMM����ID_MMC_LMM_ACTION_RESULT_REQ */
    /* ����ActionRslt��Ϣ�����ΪCN_Rej,������Ϊ����NAS_MML_PROC_MM_ABORT����
       ����ͽ������CS��ԭ��ֵΪAbort����ԭ��ֵ */
    stGuActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stGuActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stGuActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stGuActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stGuActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stGuActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stGuActionRslt);
#endif

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : ����MSCC��IMS VOICE�����õ���Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��8��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* GU���յ�IMS VOICE�Ƿ����Ŀǰ�ݲ�����
       ������ϵͳ�������յ���IMS VOICE�Ƿ���õĳ������ڿ�������ϵͳ���µ�IMS VOICE
       ������,��ʱ��������disable Lģ��׼ȷ,�ݲ����Ǹó��� */

    return VOS_TRUE;
}
/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, end */


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitRrcConnRelInd
 ��������  : �ڵȴ������ͷŵ�ʱ���յ�QUIT��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : z40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��29��
   ��    ��   : w00167002
   �޸�����   : DTS2011112301233:���Ӵ���¼�ID��״̬������֪����ʲô�¼�
                ����Լ��ġ�
                �޸�ԭ��:�û��·��ػ�����󣬵�ǰ�����ڵ�ע���������ڵ�����
                �ͷţ�������Ҫ�ȽϾõ�ʱ����ܴ���ػ����ͨ�����Ӵ���¼���
                ��鵱ǰ�ڵ�ע�������ߵ������ͷ�״̬�����յ��ػ������ֱ��
                �˳���ǰ״̬���������û��Ĺػ����
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* ������������û�����Ĺػ�����ֱ���˳��������ͷŽ��״̬�� */
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��¼ Abort��־ */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmSignalingStatusInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : MMCGMM_SIGNALING_STATUS_IND������Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : luokaihui / l00167671
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��22��
   ��    ��   : L00171473
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmSignalingStatusInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* ���ϲ�״̬��ָʾѡ��ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����������Ӳ����ڶ��Ҳ��������ͷ���������и��Ӳ��� */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : �ȴ������ͷŹ������յ������detach��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��24��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : lijun 00171473
   �޸�����   : ���ú����޸� for V7R1 phase II
 3.��    ��   : 2011��11��14��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:��ǰ��Ϊѡ��״̬��������ӽ�ֹ������Ϣ
                ��ѡ��״̬���Ľ�ֹ����LA������ȥ
 4.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
 5.��    ��   : 2012��2��13��
   ��    ��   : w00167002
   �޸�����   : DTS2011122704039:additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
 6.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU     *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;

    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

    pstDetachMsg = (MMCGMM_NETWORK_DETACH_IND_STRU *)pstMsg;

    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* ��¼Ps ��ע���� */
    NAS_MMC_SetPsRegCause_PlmnSelection((NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);


    /* ������ԭ��ֵΪ#15, ����ӽ�ֹ������Ϣ��ѡ��״̬���Ľ�ֹ����LA������ȥ,
       ���û�ָ������ʱ������Ҫ�ѽ�ֹLA��������� */
    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
   ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
      && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstDetachMsg->ulDetachCause) )
    {
        NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                               NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
    }


#if   (FEATURE_ON == FEATURE_LTE)
    /* ��LMM����detach�����Ϣ */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
        (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : �ȴ������ͷŹ������յ�ServiceRequestResultInd�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��15��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��14��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:��ǰ��Ϊѡ��״̬��������ӽ�ֹ������Ϣ
                ��ѡ��״̬���Ľ�ֹ����LA������ȥ
 3.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ

 4.��    ��   : 2012��2��13��
   ��    ��   : w00167002
   �޸�����   : DTS2011122704039:additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
 5.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif

    pstServiceRsltInd = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    /* ����Service Reqest Result ��������ͬ���� */
    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstServiceRsltInd->enActionResult)
    {
        /* ���·���״̬ */
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
        NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_NULL);

#if (FEATURE_ON == FEATURE_LTE)
        /* ��LMM����Service requestResult�����Ϣ���� */
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
        stActionRslt.ulAttemptCount = 0;

        NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif


    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcPsServiceRegFail(pstServiceRsltInd);

        NAS_MMC_SetPsRegCause_PlmnSelection(pstServiceRsltInd->enRegFailCause);


        /* ������ԭ��ֵΪ#15, ����ӽ�ֹ������Ϣ��ѡ��״̬���Ľ�ֹ����LA������ȥ,
           ���û�ָ������ʱ������Ҫ�ѽ�ֹLA��������� */
        enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
        if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
        }
        ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
        if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
          && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstServiceRsltInd->enRegFailCause) )
        {
            NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                                   NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
        }

#if (FEATURE_ON == FEATURE_LTE)

        /* ��LMM����Service requestResult�����Ϣ���� */
        stActionRslt.enProcType     = NAS_MML_PROC_SER;
        stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
        stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_PS;
        stActionRslt.enCnCause      = pstServiceRsltInd->enRegFailCause;
        stActionRslt.ulAttemptCount = 0;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    }

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    return VOS_TRUE;
}

/*************************************?****************************************
 �� �� ��  : NAS_MMC_RcvMmConnInfoInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : MMCMM_RR_CONN_INFO_IND������Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : luokaihui / l00167671
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��22��
   ��    ��   : L00171473
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmConnInfoInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����������Ӳ����ڶ��Ҳ��������ͷ���������и��Ӳ��� */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmRrRelInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : MMCMM_RR_CONN_INFO_IND������Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��24��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��22��
   ��    ��   : L00171473
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrRelInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* ���ϲ�״̬��ָʾѡ��ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����������Ӳ����ڶ��Ҳ��������ͷ���������и��Ӳ��� */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : RRMM_REL_IND����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : luokaihui / l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��22��
    ��    ��   : L00171473
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelIndMsg = VOS_NULL_PTR;

    pstRelIndMsg = ( RRMM_REL_IND_STRU * )pstMsg;


    /* ������Ӵ��ڱ�־ */
    if (RRC_RRC_CONN_STATUS_ABSENT == pstRelIndMsg->ulRrcConnStatus)
    {
        NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);
    }

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* ���ϲ�״̬��ָʾѡ��ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����������Ӳ����ڶ��Ҳ��������ͷ���������и��Ӳ��� */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmTbfRelInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : ����TBF������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : luokaihui / l00167671
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��22��
   ��    ��   : L00171473
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmTbfRelInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ������ͷŶ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* ���ϲ�״̬��ָʾѡ��ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����������Ӳ����ڶ��Ҳ��������ͷ���������и��Ӳ��� */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : WAS�ϱ���SUSPEND_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : W00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : L00171473
   �޸�����   : ���ݲ�ͬ�Ĺ���ԭ������ͬ��״̬��

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRMM_SUSPEND_IND_ST                *pstSuspendMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRelRequestFlg;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    ulRelRequestFlg = NAS_MMC_GetRelRequestFlag_PlmnSelection();

    /* ����������ͷŻ����Ѿ����յ�Abort��Ϣ,�����������ϵͳ��ѡ */
    if ((VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
     || (VOS_TRUE == ulRelRequestFlg)
     || (MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendMsg->ucSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= pstSuspendMsg->ucSuspendCause))
    {
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);
    }
    else
    {
        NAS_MMC_LoadInterSysFsm_PlmnSelection(pstSuspendMsg->ucSuspendCause);
    }


    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : GAS�ϱ���SUSPEND_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : W00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : L00171473
   �޸�����   : ���ݲ�ͬ�Ĺ���ԭ������ͬ��״̬��

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRMM_SUSPEND_IND_ST                *pstSuspendMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRelRequestFlg;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    ulRelRequestFlg = NAS_MMC_GetRelRequestFlag_PlmnSelection();

    /* ����������ͷŻ����Ѿ����յ�Abort��Ϣ,�����������ϵͳ��ѡ */
    if ((VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
     || (VOS_TRUE == ulRelRequestFlg)
     || (MMC_SUSPEND_CAUSE_PLMNSEARCH == pstSuspendMsg->ucSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= pstSuspendMsg->ucSuspendCause))

    {
        NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, UEPS_PID_GAS);
    }
    else
    {
        NAS_MMC_LoadInterSysFsm_PlmnSelection(pstSuspendMsg->ucSuspendCause);
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitRrcConnRelInd
 ��������  : ����״̬���������
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��04��
   ��    ��   : sunxibo / 46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��22��
   ��    ��   : L00171473
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������
 3.��    ��   : 2011��12��30��
   ��    ��   : l65478
   �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                ���ݾ����ԭ��ֵ������

 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2013��2��7��
   ��    ��   : W00176964
   �޸�����   : Volte_phase3��Ŀ����:����IMS������ʱdisable Lģ���߼��޸�
 6.��    ��   : 2013��4��9��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬��������ʧ��Ǩ�Ƶ�ooc
 7.��    ��   : 2014��6��30��
   ��    ��   : b00269685
   �޸�����   : DSDS GUNAS III��Ŀ:�޸ĺ�������

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_LTE == FEATURE_ON)

    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRsltMsg = VOS_NULL_PTR;

    pstSuspendRsltMsg = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

     if (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST != pstSuspendRsltMsg->enFailCause)
     {
         NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitRrcConnRelInd(): snd Mode change");
         NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                  NAS_MML_GetSimPsRegStatus());
     }

     /* Ǩ�Ƶ���ͬ�Ľ��뼼��ʱ����ҪǨ�Ƶ���ͬ�Ĵ���ע����״̬ */

    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* ֹͣ��ǰ�ȴ�CS/PS�����ͷŵ�״̬ */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        /* GU handover �� L �ɹ��󣬿��ܺܳ�ʱ���޷��յ�ϵͳ��Ϣ��ת��L1����  */
        if ((NAS_MMC_SUSPEND_SUCCESS == pstSuspendRsltMsg->enRslt)
         && (MMC_SUSPEND_CAUSE_HANDOVER == pstSuspendRsltMsg->enSuspendCause))
        {
            /* �ظ�״̬���˳��ɹ� */
            NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

            /* ֱ���˳���ǰ״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        /* ���µ�ǰ�ȴ�EPS��ע���� */
        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_IMS)
        /* ���ӵȴ�IMS�Ƿ���ý��FLG,MMA��֤�յ�PSע�����ϱ�IMS�Ƿ����ָʾ��MMC */
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, end */

        /* ����CS��ע��Cause��AdditionalAction */
        NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* Ǩ�Ƶ��ȴ�ע������״̬PLMN_SRCH:NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }

#endif

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ״̬���˳����Ϊʧ�ܣ�Ǩ�Ƶ�OOC */
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_GetCurrNetRatType());

        return VOS_TRUE;
    }

    /* ����ѡ֮ǰ�Ѿ��ж�,��ʱ�����ܴ���Abort���������ͷ�,����������Ӳ����ڿ��ܷ������� */
    NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();

   /* ��Intersys״̬������ϴ���������
    switch (pstSuspendRsltMsg->enRslt)
    {
        case NAS_MMC_SUSPEND_SUCCESS:
        break;

        case NAS_MMC_SUSPEND_FAIL :
        case NAS_MMC_SUSPEND_QUIT :

        break;

        case NAS_MMC_SUSPEND_AREA_LOST :
        break;

        default:

        break;
    }
    */




    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : �ȴ������ͷ�״̬�յ�Wϵͳ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��15��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��16��
   ��    ��   : l00171473
   �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
 3.��    ��   : 2012��8��21��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 4.��    ��   : 2012��12��11��
   ��    ��   : w00176964
   �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMMA

 5.��    ��   : 2014��1��18��
   ��    ��   : z00234330
   �޸�����   : dts2014011801513,������ϱ���ϵͳ��Ϣ�����п���û��Я��plmnid,
                 �˴��жϲ�û���ж�plmnid�Ƿ���Ч

 6.��    ��   : 2014��5��4��
   ��    ��   : t00173447
   �޸�����   : DTS2014042105390,������������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU         stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

   /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ��������������ͷ�,������Ҫ������������,ϵͳ��Ϣ������ */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* Added by t00212959 for DCM�����������������, 2012-8-25, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-25, end */

    /* פ��С���仯ʱ���ϱ�ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    }

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMMAģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM,������ǰϵͳ��Ϣ�� Forbidden ����Я����ȥ */
    NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : �ȴ������ͷ�״̬�յ�Gϵͳ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��15��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��16��
   ��    ��   : l00171473
   �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
 3.��    ��   : 2012��8��21��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 4.��    ��   : 2012��12��11��
   ��    ��   : w00176964
   �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMMA
 5.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ

 6.��    ��   : 2014��5��4��
   ��    ��   : t00173447
   �޸�����   : DTS2014042105390,������������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ��������������ͷ�,������Ҫ������������,ϵͳ��Ϣ������ */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, begin */
    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-12, end */

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* Added by t00212959 for DCM�����������������, 2012-8-25, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-25, end */

    /* פ��С���仯ʱ���ϱ�ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    }

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMMAģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM,������ǰϵͳ��Ϣ�� Forbidden ����Я����ȥ */
    NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitRrcConnRelExpired_PlmnSelection_WaitRrcConnRelInd
 ��������  : �����ͷ�״̬��ʱ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : luokaihui / l00167671
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��22��
   ��    ��   : L00171473
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������
 3.��    ��   : 2011��11��25��
   ��    ��   : w00166186
   �޸�����   : DTS2011112308343,G��pdp����󣬶�����Wע��PS�ɹ���CS13�ܾ���PS��·���ͷ�
                �����ͷź�û��������
 4.��    ��   : 2011��12��1��
   ��    ��   : w00176964
   �޸�����   : GUNAS V7R1 PhaseIV �׶ε���
 5.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 6.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 7.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitRrcConnRelExpired_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCsServiceStatusFlg;
    VOS_UINT32                          ulCsEmergencyServiceFlg;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitRrcConnRelExpired_PlmnSelection_WaitRrcConnRelInd ENTERED");

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));


    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* ���ϲ�״̬��ָʾѡ��ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����������Ӵ���, �����������ͷ�����,������������� */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();

        return VOS_TRUE;
    }

    /*
    Connrel �����ͷţ�
    �ж��Ƿ���ҵ���У����˳� (�������񣬷��سɹ������޷��񣬷���ʧ��)
    ���򣬻�ȡ��һ������ɹ����������ͷţ��ñ�־λ��ʧ�����˳�
    */
    ulCsServiceStatusFlg    = NAS_MML_GetCsServiceExistFlg();
    ulCsEmergencyServiceFlg = NAS_MML_GetCsEmergencyServiceFlg();
    if ( (VOS_TRUE == ulCsServiceStatusFlg)
      && (VOS_TRUE == ulCsEmergencyServiceFlg))
    {
        /* �ظ�״̬������ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }
    else
    {
        /* ��ȡ�¸����磬����ɹ��������ͷţ������˳� */
        if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
        {
            /* ���ݵ�ǰ��ͬ�Ľ��뼼��,�����ͷ�����,Ǩ�Ƶ���ͬ�ĵȴ������ͷŵ�L2״̬��������������ʱ�� */
            NAS_MMC_SndRelReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
        }
        else
        {
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        }
    }


    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitRrcConnRelInd
 ��������  : MMC����MSCC�����SYSCFG������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:SYSCFG������Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��04��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֱ�ӵ���syscfg���״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitRrcConnRelInd
 ��������  : ����MSCC���͵��û�ָ��������,�û�ָ����PlmnId��RAT�͵�ǰפ����PlmnId
             ��RAT��ͬ���Ż����ô���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsCause;

    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/


    /* �����ֶ�������Ϣ */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                       pstUserSelReqMsg->enAccessMode);

    /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* �����û�ָ�������������³�ʼ��ѡ���б� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* ���û�ָ�����뼼��������(Ҳ�ǵ�ǰ����)����Ϊ������ע������ظ�ע�� */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    enCsCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    /* ���ݱ����CS/PSע�����ж�ָ�����������Ƿ��ѽ��� */
    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsCause, enPsCause))
    {
        return VOS_TRUE;
    }

    /* ��ΪĿǰ״̬������Ϊ�ֶ���������,��Ҫ���������Ϣ , ĿǰӦ���ò���*/
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitRrcConnRelInd
 ��������  : �ȴ������ͷ�״̬����SYSCFG״̬�����صĽ��
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitRrcConnRelInd: ENTERED. ");
    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : �ȴ������ͷ�״̬ʱ�յ�CSҵ���¿���Ч����Ϣ(MMCMM_CM_SERVICE_REJECT_IND)
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��13��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_CM_SERVICE_REJECT_IND_STRU   *pstRcvMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
#endif

    pstRcvMsg = (MMCMM_CM_SERVICE_REJECT_IND_STRU*)pstMsg;

#if (FEATURE_ON == FEATURE_LTE)
    stActionRslt.enProcType     = NAS_MML_PROC_CM_SER;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstRcvMsg->ulCause;
    stActionRslt.ulAttemptCount = 0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);

#endif

    /* ��#6�����⴦��ʱ */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstRcvMsg->ulCause)
    {
        /* �����µ�enCsAdditioalAction��*/
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : �ȴ������ͷ�״̬��PS��ע�ᡢRAU����Ĵ�����ں���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��12��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* ���CCOʧ�ܻ��˹������յ�����ϵͳ��ע����������Ҫ���� */
    if (pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����ע��������Ӧ����: ���÷���״̬����¼Causeֵ��������һ���������ͣ�֪ͨ��Ӧ��� */
    NAS_MMC_ProcPsRegRslt_PlmnSelection(pstPsRegRslt);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : �ȴ������ͷ�״̬��LU���(�ɹ���ʧ��)����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : luokaihui / l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* ���CCOʧ�ܻ��˹������յ�����ϵͳ��ע����������Ҫ���� */
    if (pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����ע��������Ӧ����: ���÷���״̬����¼Causeֵ��������һ���������ͣ�֪ͨ��Ӧ��� */
    NAS_MMC_ProcCsRegRslt_PlmnSelection(pstCsRegRslt);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : �ȴ�RRC�����ͷŹ������յ�MM Abort��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��7��12��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stGuActionRslt;
#endif

    pstMmAbortInd = (MMMMC_ABORT_IND_STRU*)pstMsg;

    /* ���ԭ��ֵ��Ϊ#6���Ҳ�Ϊ#17��ֱ�ӷ��� */
    if ((NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME != pstMmAbortInd->enAbortCause)
     && (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstMmAbortInd->enAbortCause))
    {
        return VOS_TRUE;
    }

    /* ���ԭ��ֵ#6������CS AdditionΪAnycellפ�� */
    if (NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME == pstMmAbortInd->enAbortCause)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* ��LMM����ID_MMC_LMM_ACTION_RESULT_REQ */
    /* ����ActionRslt��Ϣ�����ΪCN_Rej,������Ϊ����NAS_MML_PROC_MM_ABORT����
       ����ͽ������CS��ԭ��ֵΪAbort����ԭ��ֵ */
    stGuActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stGuActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stGuActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stGuActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stGuActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stGuActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stGuActionRslt);
#endif

    return VOS_TRUE;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccRegReq_PlmnSelection_WaitMsccRegReq
 ��������  : �ȴ�MSCCע������������յ�ID_MSCC_MMC_REG_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��8��1��
   ��    ��   : s00217060
   �޸�����   : DTS2014072800477:VIA��EHRPD���ѵ�����balong����ID_CMMCA_MMC_RAT_NO_SERVICE_REQʱ��
                balong�պ��ѵ�LTE���磬�ȴ�VIA����REG_REQ�Գ峡���Ĵ���
 3.��    ��   : 2015��4��22��
   ��    ��   : wx270776
   �޸�����   : DTS2015031602665:��MSCC����Reg CNF��Ϣʱ����CL ATTACHע��״̬
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccRegReq_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    MSCC_MMC_PLMN_ID_STRU                                    stPlmnId;
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstInterPlmnSrchMsg = VOS_NULL_PTR;
    MSCC_MMC_REG_REQ_STRU                                   *pstRegReq = VOS_NULL_PTR;

    stPlmnId.ulMcc     = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc     = NAS_MML_INVALID_MNC;

    /* ֹͣ������ʱ��TI_NAS_MMC_WAIT_MSCC_REG_REQ */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_REG_REQ);

    /* �����ABORT��־��ֱ���˳� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ��û�д��ʱ���Żṹ���ڲ�������Ϣ��������������ΪREG_NCELL/REG_HPLMN/...
           �����д��ʱ��NAS_MMC_IsMsccRegReq_PlmnSelection����ΪVOS_TRUE
           ��Ҫ�������֧���reg_cnf */
        if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_SndMsccRegCnf(MMC_LMM_CL_REG_STATUS_BUTT, NAS_MSCC_PIF_REG_RESULT_SUCCESS, NAS_MML_GetCurrCampPlmnId(),
                                 NAS_MML_GetCurrCampArfcn());
        }
        else
        {
            if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING != NAS_MMC_GetSpecPlmnSearchState())
            {
                NAS_MMC_SndMsccRegCnf(NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection(), NAS_MSCC_PIF_REG_RESULT_REG_FAILURE, NAS_MML_GetCurrCampPlmnId(),
                                 NAS_MML_GetCurrCampArfcn());
            }
            else
            {
                NAS_MMC_SndMsccRegCnf(NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection(), NAS_MSCC_PIF_REG_RESULT_ACQ_FAILURE, &stPlmnId, 0x0);
            }
        }

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    pstRegReq = (MSCC_MMC_REG_REQ_STRU*)pstMsg;

    /* �����־ */
    NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(MMC_LMM_CL_REG_STATUS_BUTT);

    /* ����NCELL��Ϣ */
    if (VOS_TRUE == pstRegReq->bitOpCellInfo)
    {
        NAS_MMC_SaveRegReqNCellInfo(&(pstRegReq->stCellInfo));
    }

    enPlmnSearchScene = NAS_MMC_GetPlmnSearchSceneMsccRegReq(pstRegReq);

    /* ��״̬�������Ϣ�滻Ϊ������ڲ�������Ϣ�������ѵ���������ֱ�ӷ���ע�� */
    pstInterPlmnSrchMsg = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU));
    if (VOS_NULL_PTR == pstInterPlmnSrchMsg)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccRegReq_PlmnSelection_WaitMsccRegReq Alloc mem fail");

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_BulidInterPlmnSearchReqMsg(enPlmnSearchScene, VOS_NULL_PTR, 0, pstInterPlmnSrchMsg);
    NAS_MMC_SaveCurEntryMsg(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),
                            (struct MsgCB*)pstInterPlmnSrchMsg);
    PS_MEM_FREE(WUEPS_PID_MMC, pstInterPlmnSrchMsg);

    /* ����enPlmnSearchScene����ˢ��ѡ���б�ɾ�����������ȼ�Ҫ������� */
    NAS_MMC_RefreshPlmnSelectionListRcvMsccRegReq_PlmnSelection(enPlmnSearchScene);

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ��ȡ��ǰ���뼼�� */
    enNetRatType = NAS_MML_GetCurrNetRatType();

    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    if (enNetRatType == stDestPlmn.enRat)
    {
        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    /*��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ��*/
    else
    {
        /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_PlmnSelection(enNetRatType);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitMsccRegReq
 ��������  : �ȴ�MSCCע������������յ�MMCMMC_ABORT_FSM_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��8��1��
   ��    ��   : s00217060
   �޸�����   : DTS2014072800477:VIA��EHRPD���ѵ�����balong����ID_CMMCA_MMC_RAT_NO_SERVICE_REQʱ��
                balong�պ��ѵ�LTE���磬�ȴ�VIA����REG_REQ�Գ峡���Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by s00261364 for L-C��������Ŀ, 2014-2-11, begin */
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* ������������û�����Ĺػ�����ֱ���˳���ע������״̬�� */
    /* �����������ID_MSCC_MMC_POWER_SAVE_REQ��Ҳ��Ҫֱ���˳�״̬�� */
    if ( (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
      || (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ) == pstAbortMsg->ulEventType)
      || (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ)        == pstAbortMsg->ulEventType))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_REG_REQ);

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    /* Added by s00261364 for L-C��������Ŀ, 2014-2-11, end */

    /* ��¼��ϱ�־ */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitMsccRegReqExpired_PlmnSelection_WaitMsccRegReq
 ��������  : �ȴ�MSCCע������ʱ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��6��13��
   ��    ��   : b00269685
   �޸�����   : ����abort��־����ظ�abort
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMsccRegReqExpired_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMsccRegReqExpired_PlmnSelection_WaitMsccRegReq ENTERED");

    /* ����abort��־��ظ�abort������ظ�ʧ�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  : �ȴ�LTE�����ظ��������յ�״̬���˳���Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2014��2��18��
   ��    ��   : s00217060
   �޸�����   : DTS2014021203453:���ô�ϱ�־����������յ�stop_cnf֮��������

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ֪ͨLMMָֹͣ������ */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������ͬ������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedStopPlmnSearchRcvLteSearchedPlmnInfoInd_PlmnSelection
 ��������  : �յ�lte SEARCHED_PLMN_INFO_IND�ж��Ƿ���Ҫ��ϵ�ǰ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ��ϵ�ǰ����
             VOS_TRUE:��Ҫ��ϵ�ǰ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��28��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedStopPlmnSearchRcvLteSearchedPlmnInfoInd_PlmnSelection(
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU                    *pstSearchedPlmnInfoInd
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurrSearchingPlmn;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnIdWithRat;
    VOS_UINT32                                              ulIsExistDiffMccWithCurrSearchingMcc;
    VOS_UINT8                                               ucIsExistSearchedPlmnPrioCurrSearchingPlmn;
    NAS_MML_PLMN_ID_STRU                                    stGUNasPlmnId;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stCurrSearchRoamPlmnInfo;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stSearchedExistRoamPlmnInfo;
    VOS_UINT8                                               ucIsAllSearchedPlmnDisableLteRoam;
    VOS_UINT8                                               ucAllSearchedPlmnForbiddenPlmnFlag;
    NAS_MMC_ROAM_PLMN_TYPE_ENUM_UINT8                       enRoamPlmnType;

    PS_MEM_SET(&stCurrSearchRoamPlmnInfo, 0, sizeof(stCurrSearchRoamPlmnInfo));
    PS_MEM_SET(&stSearchedExistRoamPlmnInfo, 0, sizeof(stSearchedExistRoamPlmnInfo));
    PS_MEM_SET(&stPlmnIdWithRat, 0, sizeof(stPlmnIdWithRat));
    PS_MEM_SET(&stGUNasPlmnId, 0, sizeof(stGUNasPlmnId));

    pstCurrSearchingPlmn                       = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    pstPlmnSelectionList                       = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsExistDiffMccWithCurrSearchingMcc       = VOS_FALSE;
    ucIsExistSearchedPlmnPrioCurrSearchingPlmn = VOS_FALSE;
    ucIsAllSearchedPlmnDisableLteRoam          = VOS_TRUE;
    ucAllSearchedPlmnForbiddenPlmnFlag         = VOS_TRUE;
    enRoamPlmnType                             = NAS_MMC_ROAM_PLMN_TYPE_BUTT;

    stCurrSearchRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = pstCurrSearchingPlmn->stPlmnId.ulMcc;
    stCurrSearchRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = pstCurrSearchingPlmn->stPlmnId.ulMnc;
    stCurrSearchRoamPlmnInfo.stPlmnWithRat.enRat          = pstCurrSearchingPlmn->enRat;
    stCurrSearchRoamPlmnInfo.enNetStatus                  = NAS_MMC_NET_STATUS_NO_SEARCHED;
    stCurrSearchRoamPlmnInfo.enPlmnType                   = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stCurrSearchRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);
    stCurrSearchRoamPlmnInfo.aucLac[0]                    = NAS_MML_LAC_LOW_BYTE_INVALID;
    stCurrSearchRoamPlmnInfo.aucLac[1]                    = NAS_MML_LAC_HIGH_BYTE_INVALID;


    /* �����ָʾ���ڵ������rplmn��hplmn��ͬһ����������γ����򲻴������Ϣ*/
    for (ulIndex = 0; ulIndex < pstSearchedPlmnInfoInd->ulTaiNum; ulIndex++)
    {
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&pstSearchedPlmnInfoInd->stTaiList[ulIndex].stPlmnId,
                                            &stGUNasPlmnId);



        /* �����ǰ�����������searched plmn info ind��Ϣ�е�plmn��ͬ�򲻴���
            �Ƚ�����search cnf success��Ϣ*/
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstCurrSearchingPlmn->stPlmnId, &stGUNasPlmnId))
        {
            return VOS_FALSE;
        }

        /* �жϴ������������Ƿ񶼽�ֹlte ���Σ������ֹlte������Ҫ��ϵ�ǰl����*/
        if (VOS_FALSE == NAS_MMC_IsNeedDisableLteRoam(stGUNasPlmnId.ulMcc))
        {
            ucIsAllSearchedPlmnDisableLteRoam = VOS_FALSE;
        }

        /* �ж�searched plmn info ind�д������������Ƿ����������������ͬMCC,
           ���������ͬMCC,�������ϵ�ǰ������������ڲ�ͬMCC���������ϵ�ǰ���� */

        stSearchedExistRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = stGUNasPlmnId.ulMcc;
        stSearchedExistRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = stGUNasPlmnId.ulMnc;
        stSearchedExistRoamPlmnInfo.stPlmnWithRat.enRat          = NAS_MML_NET_RAT_TYPE_LTE;

        stSearchedExistRoamPlmnInfo.enNetStatus =  NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&stSearchedExistRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);

        if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != stSearchedExistRoamPlmnInfo.enNetStatus)
        {
            stSearchedExistRoamPlmnInfo.enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        }

        stSearchedExistRoamPlmnInfo.enPlmnType  = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stSearchedExistRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);
        stSearchedExistRoamPlmnInfo.aucLac[0]   = pstSearchedPlmnInfoInd->stTaiList[ulIndex].stTac.ucTac;
        stSearchedExistRoamPlmnInfo.aucLac[1]   = pstSearchedPlmnInfoInd->stTaiList[ulIndex].stTac.ucTacCnt;

        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrSearchingPlmn->stPlmnId.ulMcc, stGUNasPlmnId.ulMcc))
        {
            ulIsExistDiffMccWithCurrSearchingMcc = VOS_TRUE;

            /* ��������������綼��nplmn��forbidden plmn����ͬmccҲ�Ȳ���� */
            enRoamPlmnType = NAS_MMC_GetRoamPlmnType(&stSearchedExistRoamPlmnInfo);

            if ((NAS_MMC_ROAM_PLMN_TYPE_FORBIDDEN != enRoamPlmnType)
             && (NAS_MMC_ROAM_PLMN_TYPE_NPLMN != enRoamPlmnType))
            {
                ucAllSearchedPlmnForbiddenPlmnFlag = VOS_FALSE;
            }
        }
        else
        {
            /* �޸ĺ����� */
            /* ���������������ȼ����ڵ�ǰ���������磬����Ҫ��ϵ�ǰ���� */
            if (-1 == NAS_MMC_CompareRoamPlmnPrio(&stCurrSearchRoamPlmnInfo, &stSearchedExistRoamPlmnInfo, NAS_MML_GetMsPrioRatList()))
            {
                ucIsExistSearchedPlmnPrioCurrSearchingPlmn = VOS_TRUE;
            }
        }
    }

    if (VOS_TRUE == ucIsAllSearchedPlmnDisableLteRoam)
    {
        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);
        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_ROAMING_NOT_ALLOWED);
        return VOS_TRUE;
    }

    /* searched plmn info ind��Ϣ�д���������������뵱ǰ�ѵ����粻ͬ����������磬
       �Ҳ�����nplmn��forbidden plmn���ϵ�ǰ����*/
    if ((VOS_TRUE == ulIsExistDiffMccWithCurrSearchingMcc)
     && (VOS_FALSE == ucAllSearchedPlmnForbiddenPlmnFlag))
    {
        return VOS_TRUE;
    }

    /* searched plmn info ind ��Ϣ�д������������뵱ǰ�ѵ�����ͬ�����룬
       �����ȼ����ڻ���ڵ�ǰ�������������ϵ�ǰ����*/
    if (VOS_TRUE == ucIsExistSearchedPlmnPrioCurrSearchingPlmn)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSearchedPlmnInfoInd_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  : �յ�LTE searched plmn info ind��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��31��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��10��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSearchedPlmnInfoInd_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU                    *pstSearchedPlmnInfoInd = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stExistRoamPlmnSelectionList;
    NAS_MML_PLMN_ID_STRU                                    stGUNasPlmnId;

    pstSearchedPlmnInfoInd   = (LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU*)pstMsg;
    PS_MEM_SET(&stExistRoamPlmnSelectionList, 0, sizeof(stExistRoamPlmnSelectionList));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));
    PS_MEM_SET(&stGUNasPlmnId, 0, sizeof(stGUNasPlmnId));

    NAS_MMC_SndMsccSrchedLtePlmnInfo(pstSearchedPlmnInfoInd);

    /* ��ȡѡ���б� */
    pstPlmnSrchList       = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();


    NAS_MMC_BuildSearchedPlmnInfoByLteSearchedPlmnInfoInd(pstSearchedPlmnInfoInd, &stExistRoamPlmnSelectionList);

    NAS_MMC_UpdateExistRplmnOrHplmnFlag_PlmnSelection(&stExistRoamPlmnSelectionList);

    /* ֪ͨCSS��ǰMCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnInfoInd_PlmnSelection(&stExistRoamPlmnSelectionList, VOS_TRUE);

    if (VOS_FALSE == NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE))
    {
        return VOS_TRUE;
    }

    /* ��Ϣ��ulAvailPlmnNum��������NAS_RRC_MAX_AVAILPLMN_NUM����Ϊ�Ƿ������¸�ֵ*/
    if (pstSearchedPlmnInfoInd->ulTaiNum > LMM_MMC_MAX_SEARCHED_TAI_NUM)
    {
        pstSearchedPlmnInfoInd->ulTaiNum = LMM_MMC_MAX_SEARCHED_TAI_NUM;
    }

    if (VOS_TRUE == NAS_MMC_IsNeedStopPlmnSearchRcvLteSearchedPlmnInfoInd_PlmnSelection(pstSearchedPlmnInfoInd))
    {
        /* �������γ��������������б�����ԭ������:
         1��������ϱ����ڵ�����������������б�ǰ��,��NPLMN�е����粻��ӣ�
            ֧�ֵ����н��뼼������ӣ���ǰ�����Ľ��뼼������
         2����gastNetworkNameTbl���ҳ�����ǰ����������ͬ�������plmn�������������б�
            ��NPLMN�е����粻��ӣ�֧�ֵ����н��뼼������ӣ���ǰ�����Ľ��뼼������
         3������DPLMN->UPLMN->OPLMN->AVAILABLE PLMN˳������������б��������
        */
        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_LTE,
            &stExistRoamPlmnSelectionList, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ��ά�ɲ�,��ѡ���б���� */
        NAS_MMC_LogPlmnSelectionList(pstPlmnSrchList);
        NAS_MMC_LogDplmnNplmnList();


        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

        if (NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);
        }

        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

        /* ֪ͨLMMָֹͣ������ */
        NAS_MMC_SndLmmPlmnSrchStopReq();

        /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������ͬ������ʱ��*/
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    }

    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  : �յ�LTE����CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:rrmm_plmn_SEARCH_cnf��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��25��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��7��16��
   ��    ��   : s00217060
   �޸�����   : for DTS2012071604442 ����:�յ�LMM����ʧ��,���һ�ȡ��һ������ʧ����Ҫ����פ��LTE
 6.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 7.��    ��   : 2014��6��10��
   ��    ��   : w00167002
   �޸�����   : DSDS III:L������NO RF��������
 8.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
 9.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸ģ���װL��ȫƵ��ָ�������ظ��Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* ��ȡѡ���б� */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ���õ�ǰģʽ�Ƿ����ȫƵ�������Ƿ�������縲�� */
    NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(pstLmmSrchCnfMsg);

    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

        return VOS_TRUE;
    }


    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }


    /* ��������Ϣ��Я����������Ϣת��Ϊ�ڲ���Ϣ��������Ϣ */
    NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(&(pstLmmSrchCnfMsg->stPlmnIdList),
                                                     &stPlmnSearchInfo);


    /* ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ֪ͨCSS��ǰMCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* �������ʧ�ܽ���д�����������û��һ����rplmn��hplmn
       ͬһ��������֮ǰδ�Ź�����Ҫ�������������б����ԭ����ͷ��*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_LTE);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* �Ѹߵ�����������ȡ����roam�����б� */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_LTE, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);

        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_LTE,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

        /* ������Ϣ��Я����������Ϣ���������б� */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);


        /* ��ά�ɲ�,��ѡ���б���� */
        NAS_MMC_LogDplmnNplmnList();
    }


    /* ���µ�ǰ���뼼��������ȫƵ����,�����ǰ�����������������޷��������������б����Թ��������������б���ٸ��½��й�ȫƵ����*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }


    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmHistoryPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  : �յ�LTE history����CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:rrmm_plmn_SEARCH_cnf��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ����:L��HISTORY�ѽ���Ĵ���
*****************************************************************************/
VOS_VOID NAS_MMC_RcvLmmHistoryPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* ��ȡѡ���б� */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* �����õ�ǰģʽ������ȫƵ�������������縲�� */
    NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(pstLmmSrchCnfMsg);

    if (MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return;
    }

    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

    /* ��������Ϣ��Я����������Ϣת��Ϊ�ڲ���Ϣ��������Ϣ */
    NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(&(pstLmmSrchCnfMsg->stPlmnIdList),
                                                     &stPlmnSearchInfo);


    /* ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_FALSE);

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* �������ʧ�ܽ���д�����������û��һ����rplmn��hplmn
       ͬһ��������֮ǰδ�Ź�����Ҫ�������������б����ԭ����ͷ��*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_LTE);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* �Ѹߵ�����������ȡ����roam�����б� */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_LTE, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);

        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_LTE,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

        /* ������Ϣ��Я����������Ϣ���������б� */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_FALSE);

        /* ��ά�ɲ�,��ѡ���б���� */
        NAS_MMC_LogDplmnNplmnList();
    }

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  : �յ�LTE pref band����CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:rrmm_plmn_SEARCH_cnf��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��13��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    VOS_UINT32                                              ulIsNeedSortRoamPlmnList;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stSearchedExistPlmnInfo;
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                        stNewRoamPlmnSelectionList;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;

    /* ��ȡѡ���б� */
    pstPlmnSrchList                  = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ulIsNeedSortRoamPlmnList         = VOS_FALSE;
    PS_MEM_SET(&stSearchedExistPlmnInfo, 0, sizeof(stSearchedExistPlmnInfo));
    PS_MEM_SET(&stNewRoamPlmnSelectionList, 0, sizeof(stNewRoamPlmnSelectionList));

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ���õ�ǰģʽ�Ƿ����ȫƵ�������Ƿ�������縲�� */
    NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(pstLmmSrchCnfMsg);

    if (MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_SUCC == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection();

        /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

        return VOS_TRUE;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }

    /* ��������Ϣ��Я����������Ϣת��Ϊ�ڲ���Ϣ��������Ϣ */
    NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(&(pstLmmSrchCnfMsg->stPlmnIdList),
                                                     &stPlmnSearchInfo);


    /* ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ֪ͨCSS��ǰMCC */
    NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, VOS_TRUE);

    /* �������ʧ�ܽ���д�����������û��һ����rplmn��hplmn
       ͬһ��������֮ǰδ�Ź�����Ҫ�������������б����ԭ����ͷ��*/
    ulIsNeedSortRoamPlmnList = NAS_MMC_IsNeedSortPlmnListRcvRrcPlmnSearchCnfFail_PlmnSelection(&stPlmnSearchInfo, NAS_MML_NET_RAT_TYPE_LTE);

    if (VOS_TRUE == ulIsNeedSortRoamPlmnList)
    {
        /* �Ѹߵ�����������ȡ����roam�����б� */
        NAS_MMC_BuildSearchedPlmnListInfoByRrcSearchCnfFail(NAS_MML_NET_RAT_TYPE_LTE, &stPlmnSearchInfo, &stSearchedExistPlmnInfo);

        NAS_MMC_BuildRoamPlmnSelectionListBySearchedExistPlmnInfo(NAS_MML_NET_RAT_TYPE_LTE,
            &stSearchedExistPlmnInfo, &stNewRoamPlmnSelectionList);

        /* ���Ź����roam�����б���������б�ǰ�� */
        NAS_MMC_AddRoamPlmnSelectionListInPlmnSelectionList(&stNewRoamPlmnSelectionList, pstPlmnSrchList);

        /* ���øý��뼼���Ѿ��յ��������searched plmn info ind���й�һ������ */
        NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

        /* ������Ϣ��Я����������Ϣ���������б� */
        NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                                   NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                                   VOS_TRUE);


        /* ��ά�ɲ�,��ѡ���б���� */
        NAS_MMC_LogDplmnNplmnList();
    }


    /* ���µ�ǰ���뼼��������ȫƵ����,�����ǰ�����������������޷��������������б����Թ��������������б���ٸ��½��й�ȫƵ����*/
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }


    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  : �յ�LTE����CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:rrmm_plmn_SEARCH_cnf��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��25��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��7��16��
   ��    ��   : s00217060
   �޸�����   : for DTS2012071604442 ����:�յ�LMM����ʧ��,���һ�ȡ��һ������ʧ����Ҫ����פ��LTE
 6.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 7.��    ��   : 2014��6��10��
   ��    ��   : w00167002
   �޸�����   : DSDS III:L������NO RF��������
 8.��    ��   : 2014��11��3��
   ��    ��   : z00161729
   �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    switch (pstLmmSrchCnfMsg->enRlst)
    {
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_FAIL:

            /* L��ָ�������Ĵ��� */
            (VOS_VOID)NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_FAIL:

            /* L��HISTORYָ�������Ĵ��� */
            NAS_MMC_RcvLmmHistoryPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        /* L��pref band�����Ĵ��� */
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_FAIL:

            (VOS_VOID)NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnf: UNEXPECTED RSLT TYPE!!!");
            (VOS_VOID)NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  : �յ�ID_LMM_MMC_ATTACH_CNF�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_ATTACH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��9��3��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ǰLTE������״̬��ΪDISABLE ״̬���򲻴������Ϣ */
    if ( NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnf: unexpect message received");

        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ֪ͨLMMָֹͣ������ */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������ͬ������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  : �յ�ID_LMM_MMC_DETACH_CNF�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_DETACH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��01��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ǰLTE������״̬��ΪDISABLE ״̬���򲻴������Ϣ */
    if ( NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnf: unexpect message received");

        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ֪ͨLMMָֹͣ������ */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������ͬ������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  : �ȴ�LTEȫƵ��ָ�������ظ�������������ʱ����ʱ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��7��16��
   ��    ��   : s00217060
   �޸�����   : for DTS2012071604442
                ����:LMM������ʱ����ʱ,���һ�ȡ��һ������ʧ����Ҫ����פ��LTE
 6.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:�������縲������
 7.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 8.��    ��   : 2014��6��6��
   ��    ��   : b00269685
   �޸�����   : ��֪ͨLMMֹͣ����
 9.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�
 7.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    stPlmnSearchInfo;

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf: Timer Expired");

    /* ���õ�ǰ�����Ѿ�����ȫƵ���� */
    NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

    /* ���õ�ǰ�����޸��� */
    NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, NAS_MMC_COVERAGE_TYPE_NONE);

    /* ���õ�ǰ���뼼��û���������κ����� */
    stPlmnSearchInfo.ulHighPlmnNum = 0x0;
    stPlmnSearchInfo.ulLowPlmnNum  = 0x0;
    stPlmnSearchInfo.enRatType     = NAS_MML_NET_RAT_TYPE_LTE;

    /* ������Ϣ��Я����������Ϣ���������б� */
    NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&stPlmnSearchInfo,
                                               NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(),
                                               VOS_TRUE);


    /* ֪ͨLMMָֹͣ������ */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������ͬ������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  : �ȴ�LTE��ʷƵ�������ظ�������������ʱ����ʱ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_RcvTiWaitHistoryPlmnSrchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitHistoryPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf: Timer Expired");

    /* ���õ�ǰ�����޸��� */
    NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, NAS_MMC_COVERAGE_TYPE_NONE);

    NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);

    /* ֪ͨLMMָֹͣ������ */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*���ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������ͬ������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  : �ȴ�LTE�����ظ�������������ʱ����ʱ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2012��7��16��
   ��    ��   : s00217060
   �޸�����   : for DTS2012071604442
                ����:LMM������ʱ����ʱ,���һ�ȡ��һ������ʧ����Ҫ����פ��LTE
 6.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:�������縲������
 7.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 8.��    ��   : 2014��6��6��
   ��    ��   : b00269685
   �޸�����   : ��֪ͨLMMֹͣ����
 9.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�
10.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸� ���Ӷ�HISTORY�����Ĵ���
11.��    ��   : 2015��10��28��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:����pref band�ѵĴ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enCurrSearchingPlmnType;                /* ��������ָ���ѣ�history�� */

    enCurrSearchingPlmnType = NAS_MMC_GetCurrSearchingType_PlmnSelection();

    switch (enCurrSearchingPlmnType)
    {
        case NAS_MMC_PLMN_SEARCH_TYPE_SPEC:
            (VOS_VOID)NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_HISTORY:
            NAS_MMC_RcvTiWaitHistoryPlmnSrchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        case NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND:
            (VOS_VOID)NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf UNEXPECTED SEARCH TYPE!!!");
            (VOS_VOID)NAS_MMC_RcvTiWaitSpecPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendCnf_PlmnSelection_WaitLmmSuspendCnf
 ��������  : �յ�LTE��suspend cnf��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��

 3.��    ��   : 2011��12��15��
   ��    ��   : w00167002
   �޸�����   : DTS2011120702166:MMC��λ���޸�λ��Ϣ,��MMLģ���װ��λ��Ϣ��
                 �Թ�MM����ã�������λ��
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2013��6��7��
   ��    ��   : w00176964
   �޸�����   : SS FDN&Call Control��Ŀ:����PS��ע��״̬
 6.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 7.��    ��   : 2014��3��10��
   ��    ��   : f00261443
   �޸�����   : ����PS��ע��״̬,����һ����NAS_MML_REG_NOT_REGISTERED_SEARCHING
 8.��    ��   : 2014��2��13��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 9.��    ��   : 2014��6��23��
   ��    ��  :  b00269685
   �޸�����  :  DSDS III����
10.��    ��   : 2015��3��11��
   ��    ��   : wx270776
   �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmSuspendCnf_PlmnSelection_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstGuSuspendCnf = VOS_NULL_PTR;
    LMM_MMC_SUSPEND_CNF_STRU           *pstLmmSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    pstGuSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* Lģʱ�������¸�ʽת�� */
    pstLmmSuspendCnf = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    pstGuSuspendCnf->ucResult = (VOS_UINT8)(pstLmmSuspendCnf->ulRst);

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstGuSuspendCnf->ucResult)
    {
        /* ���ɻָ�����,���õ���ӿ�RESET */

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);

        return VOS_TRUE;
    }


    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        /* ���õ�ǰ���뼼��ΪBUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* �����������,ԭ��Ϊ�˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* ��ȡ��Ҫ���������缰����뼼�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
        NAS_MML_SetCurrNetRatType(stDestPlmn.enRat);

        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);

        /* ��֤����L�ص�GUʱPS��ע��״̬ʼ��Ϊ2,�˴�����һ�θ���(����LʱL�����ϱ���ע��״̬��Ϊ2) */
        NAS_MMC_UpdateRegStateSpecPlmnSearch();
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendCnf_PlmnSelection_WaitLmmSuspendCnf,WARNING:CAN'T FIND THE NEXT PLMN");

        /* ���õ�ǰ���뼼��ΪBUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* Modified by s00246516 for L-C��������Ŀ, 2014-02-13, Begin */
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        /* Modified by s00246516 for L-C��������Ŀ, 2014-02-13, End */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPlmnSearchStopCnf_PlmnSelection_WaitLmmPlmnStopCnf
 ��������  : �յ�LTE��plmn search stop cnf��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��

 3.��    ��   : 2011��11��30��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase IV����:disable/enable �����Լ�detach����
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 6.��    ��   : 2014��2��17��
   ��    ��   : s00217060
   �޸�����   : DTS2014021203453:�յ�LmmStopCnfʱ����Ѿ�Enable Lte����Ҫ����ȥLTE������
 7.��    ��   : 2014��2��13��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 8.��    ��   : 2014��6��21��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchStopCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* �޴��ʱ:�����ǰLTE������״̬Ϊdisable LTE���������¸���LTE������
        �����ǰLTE������״̬ΪEnable LTE,�������¸����õ�LTE����
        Enable LTE��Ӧ�ĳ���Ϊ:��LMM���������ʱ�յ�LmmDetachCnf����ҪDisable LTE,Ǩ����LmmStopCnf״̬
        �ڵȴ�LmmStopCnfʱ���յ�LmmAttachCnf������ҪEnable LTE,��ʱ���յ�LmmStopCnf��Ҫ����ȥLTE������ */

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* ��LMM������������Ǩ��״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            /* Modified by s00246516 for L-C��������Ŀ, 2014-02-13, Begin */
            NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
            /* Modified by s00246516 for L-C��������Ŀ, 2014-02-13, End */
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf
 ��������  : �յ�LTE��spec plmn search cnf��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��6��25��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ����
 2.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* �޴��ʱ:�����ǰLTE������״̬Ϊdisable LTE���������¸���LTE������
        �����ǰLTE������״̬ΪEnable LTE,�������¸����õ�LTE����
        Enable LTE��Ӧ�ĳ���Ϊ:��LMM���������ʱ�յ�LmmDetachCnf����ҪDisable LTE,Ǩ����LmmStopCnf״̬
        �ڵȴ�LmmStopCnfʱ���յ�LmmAttachCnf������ҪEnable LTE,��ʱ���յ�LmmStopCnf��Ҫ����ȥLTE������ */

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* ��LMM������������Ǩ��״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf
 ��������  : �յ�LTE��history plmn search cnf��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_RcvLmmHistoryPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* �޴��ʱ:�����ǰLTE������״̬Ϊdisable LTE���������¸���LTE������
        �����ǰLTE������״̬ΪEnable LTE,�������¸����õ�LTE����
        Enable LTE��Ӧ�ĳ���Ϊ:��LMM���������ʱ�յ�LmmDetachCnf����ҪDisable LTE,Ǩ����LmmStopCnf״̬
        �ڵȴ�LmmStopCnfʱ���յ�LmmAttachCnf������ҪEnable LTE,��ʱ���յ�LmmStopCnf��Ҫ����ȥLTE������ */

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* ��LMM������������Ǩ��״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf
 ��������  : �յ�LTE��pref band plmn search cnf��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��13��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* �����ǰΪNO RF����ֱ����״̬�� */
    if (MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

        return;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* �޴��ʱ:�����ǰLTE������״̬Ϊdisable LTE���������¸���LTE������
        �����ǰLTE������״̬ΪEnable LTE,�������¸����õ�LTE����
        Enable LTE��Ӧ�ĳ���Ϊ:��LMM���������ʱ�յ�LmmDetachCnf����ҪDisable LTE,Ǩ����LmmStopCnf״̬
        �ڵȴ�LmmStopCnfʱ���յ�LmmAttachCnf������ҪEnable LTE,��ʱ���յ�LmmStopCnf��Ҫ����ȥLTE������ */

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* ��LMM������������Ǩ��״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf
 ��������  : �յ�LTE��plmn search cnf��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��6��25��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ����
 2.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg = VOS_NULL_PTR;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    switch (pstLmmSrchCnfMsg->enRlst)
    {
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_FAIL:

            /* L��ָ�������Ĵ��� */
            NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(ulEventType, pstMsg);
            break;

        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_FAIL:

            /* L��HISTORYָ�������Ĵ��� */
            NAS_MMC_RcvLmmHistoryPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(ulEventType, pstMsg);
            break;

        /* L��pref band�����Ĵ��� */
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_SUCC:
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF:
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_FAIL:

            NAS_MMC_RcvLmmPrefBandPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(ulEventType, pstMsg);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf: UNEXPECTED RSLT TYPE!!!");
            NAS_MMC_RcvLmmSpecPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf(ulEventType, pstMsg);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnf
 ��������  : LTE��plmn search stop CNF�����б�����ʱ����ʱ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��11��
   ��    ��   : sunxibo 46746
   �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��

 3.��    ��   : 2011��11��30��
   ��    ��   : w00176964
   �޸�����   : V7R1 Phase IV����:disable/enable ����
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 5.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 6.��    ��   : 2014��2��17��
   ��    ��   : s00217060
   �޸�����   : DTS2014021203453:�յ�LmmStopCnfʱ����Ѿ�Enable Lte����Ҫ����ȥLTE������
 7.��    ��   : 2014��2��13��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 8.��    ��   : 2014��6��21��
   ��    ��   : b00269685
   �޸�����   : DSDS III��Ŀ
****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnf: Timer Expired");

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection();

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ʧ�ܺ����RF���ñ�� */
    NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection();

    /* �޴��ʱ:�����ǰLTE������״̬Ϊdisable LTE���������¸���LTE������
        �����ǰLTE������״̬ΪEnable LTE,�������¸����õ�LTE����
        Enable LTE��Ӧ�ĳ���Ϊ:��LMM���������ʱ�յ�LmmDetachCnf����ҪDisable LTE,Ǩ����LmmStopCnf״̬
        �ڵȴ�LmmStopCnfʱ���յ�LmmAttachCnf������ҪEnable LTE,��ʱ���յ�LmmStopCnf��Ҫ����ȥLTE������ */

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_LTE == stDestPlmn.enRat)
        {
            /* ��LMM������������Ǩ��״̬��������������ʱ�� */
            NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
        }
        else
        {
            /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
            NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);
        }
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* Modified by s00246516 for L-C��������Ŀ, 2014-02-13, Begin */
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        /* Modified by s00246516 for L-C��������Ŀ, 2014-02-13, End */
    }

    return VOS_TRUE;


}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmSysInfoInd
 ��������  : MMC����Aort��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:Abort��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��12��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoInd
 ��������  : MMC����LMM�ϱ���ϵͳ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:LMM�ϱ���ϵͳ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��10��6��
    ��    ��   : w00167002
    �޸�����   : PhaseII�޸�:ɾ�����ĵ�ǰ�������ע��״̬ΪREGISTERED��
                 ͳһ��ע�����󣬲Ÿ���ΪREGISTERED
  4.��    ��   : 2011��12��30��
    ��    ��   : l65478
    �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                 ���ݾ����ԭ��ֵ������

  5.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  6.��    ��   : 2012��4��18��
    ��    ��   : l00130025
    �޸�����   : DTS2012040200480,����ά��EPSע��״̬,����ѯ���ϱ�ʹ��
  7.��    ��   : 2012��4��28��
    ��    ��   : W00166186
    �޸�����   : DTS2012042602593,MMû�б��浱ǰפ����PLMN�����º����жϳ���
  8.��    ��   : 2012��6��11��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1
  9.��    ��   : 2012��11��29��
    ��    ��   : w00176964
    �޸�����   : DTS2012042804167:֪ͨCBAģ�鵱ǰ����ģʽΪLTE
 10.��    ��   : 2012��12��20��
    ��    ��   : w00176964
    �޸�����   : DTS2012121906946:�յ�L��ϵͳ��Ϣת����LMM
 11.��    ��   : 2013��1��19��
    ��    ��   : t00212959
    �޸�����   : DTS2012122900189:EPSע��״̬��ȫ��L�ϱ�
 12.��    ��   : 2013��2��7��
    ��    ��   : W00176964
    �޸�����   : Volte_phase3��Ŀ����:����IMS������ʱdisable Lģ���߼��޸�
 13.��    ��   : 2014��1��28��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 14.��    ��   : 2014��6��13��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ: ����״̬�������Ϣ
 15.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 �����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    MSCC_MMC_PLMN_ID_STRU                stPlmnId;
    VOS_UINT32                          ulCurrentEventType;
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg    = VOS_NULL_PTR;
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stPlmnId, 0, sizeof(MSCC_MMC_PLMN_ID_STRU));

    /* ֹͣ�ȴ�ϵͳ��Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    if (VOS_FALSE == NAS_MMC_IsAllowedRegAfterAcqSucc_PlmnSelection())
    {
        /* �������ǻ�ȡ������MSCC�ظ���ȡ�ɹ��������ϱ���ȡָʾ */
        pstLmmSysInfoMsg  = (LMM_MMC_SYS_INFO_IND_STRU*)pstMsg;
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&(pstLmmSysInfoMsg->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]), &stPlmnId);

        if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ) == ulCurrentEventType)
        {
            NAS_MMC_SndMsccAcqCnf(NAS_MSCC_PIF_ACQ_RESULT_SUCCESS, &stPlmnId, pstLmmSysInfoMsg->stLteSysInfo.ulArfcn);

            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();
        }
        else
        {
            NAS_MMC_SndMsccAcqInd(NAS_MSCC_PIF_ACQ_RESULT_SUCCESS, &stPlmnId, pstLmmSysInfoMsg->stLteSysInfo.ulArfcn);
        }

        /* ״̬Ǩ�Ƶ�NAS_MMC_PLMN_SELECTION_STA_WAIT_MSCC_REG_REQ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_MSCC_REG_REQ);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MSCC_REG_REQ, TI_NAS_MMC_WAIT_MSCC_REG_REQ_LEN);

        return VOS_TRUE;
    }
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);





    /* ���µ�ǰ�ȴ�EPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_IMS)
    /* ���ӵȴ�IMS�Ƿ���ý��FLG,MMA��֤�յ�PSע�����ϱ�IMS�Ƿ����ָʾ��MMC */
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, end */

    /* ����CS��ע��Cause��AdditionalAction */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */
    /*�����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC*/
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccSysInfo();
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* ת��GMMϵͳ��Ϣ,��rabmʹ�� */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    /* Ǩ�Ƶ��ȴ�ע������״̬PLMN_SRCH:NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitLSysInfoInd
 ��������  : �ȴ�ϵͳ��Ϣ��ʱ����ʱ��ʱ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_SYS_INFO��ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��12��15��
    ��    ��   : W00166186
    �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
  4.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  5.��    ��   : 2012��7��16��
    ��    ��   : s00217060
    �޸�����   : for DTS2012071604442
                 ����:LMMϵͳ��Ϣ��ʱ����ʱ,���һ�ȡ��һ������ʧ����Ҫ����פ��LTE
  6.��    ��   : 2012��09��27��
    ��    ��   : z00161729
    �޸�����   : DTS2012090303562:����״̬����Lע�����յ�������Ϣ��ȡ��һ������ʧ����״̬�����ַ���Ƿ������������
  7.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  8.��    ��   : 2013��8��27��
    ��    ��   : l00208543
    �޸�����   : Coverity
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    VOS_UINT32                          ulResult;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoInd: Timer Expired");

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /*�����ǰ��Ҫ�˳�״̬��*/
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /*��ȡ��һ��Ҫ����������,����ȡʧ�ܣ�����ϲ�״̬���ϱ�����ʧ�ܣ��˳�
      ����ȡ�ɹ������ж���һ��Ҫ�����������Ƿ��뵱ǰפ��������ͬ��
      ����ͬ���ڵ�ǰģʽ�����������������ǰ����
     */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /*  ��ȡ�¸�����ʧ�ܣ�����г�����������*/
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        return VOS_TRUE;
    }

    /* ��MM��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /*��һ��Ҫ�����������Ƿ��뵱ǰפ�����粻ͬ,��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ��*/
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    /* ����ҪSuspend */
    else
    {
        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }


    return VOS_TRUE;

}




/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSrch_WaitEpsRegRsltInd
 ��������  : �ڵȴ�EPS�ϱ�ע������ʱ���յ�QUIT��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg: Abort��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2011��11��29��
    ��    ��   : w00167002
    �޸�����   : DTS2011112301233:���Ӵ���¼�ID��״̬������֪����ʲô�¼�
                ����Լ��ġ�
                �޸�ԭ��:�û��·��ػ�����󣬵�ǰ�����ڵ�ע���������ڵ�����
                �ͷţ�������Ҫ�ȽϾõ�ʱ����ܴ���ػ����ͨ�����Ӵ���¼���
                ��鵱ǰ�ڵ�ע�������ߵ������ͷ�״̬�����յ��ػ������ֱ��
                �˳���ǰ״̬���������û��Ĺػ����
  4.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;


    /* ������������û�����Ĺػ�����ֱ���˳���ע����״̬�� */
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��ǰû�����ӿ���ֱ���˳� */
    if ( VOS_FALSE == NAS_MML_IsRrcConnExist())
    {
        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����Abort��־ */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /* �����Ҫ�����˳� */
    if (NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
    {
        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ���������ͷ����� */
        NAS_MMC_SndLmmRelReq();

        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsConnRelInd
 ��������  : �ڵȴ�EPS��·�ͷŵ�ʱ������detach�ĵĴ���
 �������  : ulEventType:��Ϣ����
             pstMsg: ID_LMM_MMC_DETACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��1��11��
    ��    ��   : w00176964
    �޸�����   : DTS2013010706662:��������EPLMN�߼�����λ��
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* ����DETACH��Ϣ��������һ������ */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    /*����EPS����һ���Ķ�������*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /*����CS����һ���Ķ�������*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        NAS_MMC_SndOmEquPlmn();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsConnRelInd
 ��������  : �ڵȴ�EPS��·�ͷŵ�ʱ���û�detach CNF�ĵĴ���
 �������  : ulEventType:��Ϣ����
             pstMsg: ID_LMM_MMC_DETACH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_CNF_STRU                                *pstDetachCnfMsg = VOS_NULL_PTR;

    pstDetachCnfMsg        = (LMM_MMC_DETACH_CNF_STRU*)pstMsg;

    /* ����detach������Ǽ�Ȩ���ܣ�����Ҫ��״̬����Ԥ�����оͿ��Դ��� */
    if ( MMC_LMM_DETACH_RSLT_AUTH_REJ != pstDetachCnfMsg->ulDetachRslt)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsConnRelInd: Unexpected detach result!");

        return VOS_TRUE;
    }

    /*����EPS����һ���Ķ�������*/
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);

    /*����CS����һ���Ķ�������*/
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltInd
 ��������  : LMM�ϱ���CONN Status Ind��Ϣ������
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_STATUS_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�,PlmnSelection״̬������
  3.��    ��   : 2015��9��17��
    ��    ��   : y00346957
    �޸�����   : DTS2015070910885 ���ӵ�ǰ������plmn�Ƿ������ѵ��ж�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat     = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
#endif

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    if ( VOS_FALSE == pstLmmStatusIndMsg->bitOpConnState)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltInd:bitOpConnState IS VOS_FALSE");
        return VOS_TRUE;
    }

    /* ����LMM������״̬ */
    switch (pstLmmStatusIndMsg->ulConnState)
    {
        case MMC_LMM_CONN_ESTING:
        case MMC_LMM_CONNECTED_SIG:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
            break;

        case MMC_LMM_CONNECTED_DATA:
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);
            break;

        case MMC_LMM_CONN_IDLE:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        default:
            break;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    pstPlmnWithRat      = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    stPlmnId.ulMcc      = pstPlmnWithRat->stPlmnId.ulMcc;
    stPlmnId.ulMnc      = pstPlmnWithRat->stPlmnId.ulMnc;

    /* �ж�lte plmn�Ƿ��������� */
    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltInd:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                             stPlmnId.ulMcc, stPlmnId.ulMnc);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ���¸�plmn */
        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }
#endif
    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltInd
 ��������  : WaitEpsRegRsltIndʱ��LMM�ϱ���ID_LMM_MMC_ATTACH_IND��Ϣ������
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��22��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�
  3.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : PhaseIII֧������ע���޸�
  4.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  5.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 Phase IV����
  6.��    ��   : 2012��6��2��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1, �����ǰ�Ѿ�������ҪDisable L,����ע��ɹ���
                  ���浱ǰL���絽״̬����������
7.��    ��   : 2012��12��07��
   ��    ��   : t00212959
   �޸�����   : DTS2012120608079:Lattach֮ǰ�·��б��ѣ���ҪdisableLʱ���˳�״̬�����޷���ȡCS����
8.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����
 9.��    ��   : 2015��4��22��
   ��    ��   : wx270776
   �޸�����   : DTS2015031602665:��CL ATTACHע��״̬����ȫ�ֱ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode;

    enUeOperationMode   =  NAS_MML_GetLteUeOperationMode();
    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    if ( VOS_TRUE == NAS_MMC_IsNeedUpdateLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus) )
    {
        NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus);
    }

    /* LMM������δ�ظ�search cnfʱ�յ��û�detach ps����󣬺���������ע���mmc�ظ�attach result
       ΪMMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW���������������MMC_LMM_ATT_TYPE_BUTT��
       MMC��Ҫ���ݵ�ǰue operation mode�������������¸�ֵ */
    if ((MMC_LMM_ATT_TYPE_BUTT == pstLmmAttachIndMsg->ulReqType)
     && (MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW == pstLmmAttachIndMsg->ulAttachRslt))
    {
        pstLmmAttachIndMsg->ulReqType = NAS_MMC_ConvertLmmAttachReqType(enUeOperationMode);
    }

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_PlmnSelection(pstLmmAttachIndMsg);

    /* �Ѿ�Disable L����ע��ɹ�,��Ҫ����ǰ���籣����״̬����������,���ں���
       GU����ʧ�����»ظ������ṩPSҵ��*/
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus())
      && (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt))
    {
        /* ���浱ǰ������״̬���������� */
        NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(NAS_MML_GetCurrCampPlmnId());
    }

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /*���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬��*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {

        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

            return VOS_TRUE;
        }


        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltInd
 ��������  : ��PLMN SRCHʱ���յ�ID_LMM_MMC_TAU_RESULT_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��22��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�
  3.��    ��   : 2011��10��26��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע���޸�
  4.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  5.��    ��   : 2012��6��2��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1, ����Ѿ�Disable L, ����TAU�ɹ���
                  ���浱ǰ���絽״̬����������
  6.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnSelection(pstLmmTauIndMsg);

    /* �Ѿ�Disable L����ע��ɹ�,��Ҫ����ǰ���籣����״̬����������,���ں���
       GU����ʧ�����»ظ������ṩPSҵ��*/
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus())
      && (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst))
    {
        /* ���浱ǰ������״̬���������� */
        NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(NAS_MML_GetCurrCampPlmnId());
    }

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /*���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬��*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();
        }
    }

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltInd
 ��������  : �ڵȴ�EPSע������ʱ������detach�ĵĴ���
 �������  : ulEventType:��Ϣ����
             pstMsg: ID_LMM_MMC_DETACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��19��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��1��11��
    ��    ��   : w00176964
    �޸�����   : DTS2013010706662:��������EPLMN�߼�����λ��
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* ����DETACH��Ϣ��������һ������ */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    /*����EPS����һ���Ķ�������*/
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /*����CS����һ���Ķ�������*/
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        NAS_MMC_SndOmEquPlmn();
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltInd
 ��������  : �ڵȴ�LTEע����ʱ���յ�ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ�Ĵ���,
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��26��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��16��
    ��    ��   : b00269685
    �޸�����   : ������CSFB��־����Ҫ�������޸������ϢΪCSFB����������

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU                        *pstSerRsltMsg       = VOS_NULL_PTR;
    /* Added by b00269685 for ����FR�Ż�, 2014-10-16, begin */
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstInterPlmnSrchMsg = VOS_NULL_PTR;
    /* Added by b00269685 for ����FR�Ż�, 2014-10-16, end */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstSerRsltMsg     = (LMM_MMC_SERVICE_RESULT_IND_STRU*)pstMsg;

    /* ����LMM��service result���������һ�������� */
    enAdditionalAction = NAS_MMC_ProcLmmServiceRsltInd(pstSerRsltMsg);

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* Added by b00269685 for ����FR�Ż�, 2014-10-16, begin */
    if ((VOS_TRUE                                 == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION == enAdditionalAction))
    {
        pstInterPlmnSrchMsg = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU));
        if (VOS_NULL_PTR != pstInterPlmnSrchMsg)
        {
            /* �޸������ϢΪCSFB���������� */
            NAS_MMC_BulidInterPlmnSearchReqMsg(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ, VOS_NULL_PTR, 0, pstInterPlmnSrchMsg);
            NAS_MMC_SaveCurEntryMsg(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),
                                    (struct MsgCB*)pstInterPlmnSrchMsg);
            PS_MEM_FREE(WUEPS_PID_MMC, pstInterPlmnSrchMsg);
        }
        else
        {
            /* �쳣��ӡ */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltInd Alloc mem fail");
        }
    }
    /* Added by b00269685 for ����FR�Ż�, 2014-10-16, end */

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltInd
 ��������  : LMM�ϱ���SUSPEND_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��14��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg = VOS_NULL_PTR;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* Lģ�£�����ԭ������GU�²�ͬ��ת��һ�¹���ԭ���� */
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLSuspendMsg->ulSysChngType, &enSuspendCause);

    /* ���ΪOOS���߲�������ȷ, �����������ϵͳ��ѡ */
    if ((MMC_SUSPEND_CAUSE_PLMNSEARCH == enSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= enSuspendCause))
    {
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
    }
    else
    {
        /* ����SUSPEND��Ϣ�еĲ�ͬ��������Ӧ��״̬�� */
        NAS_MMC_LoadInterSysFsm_PlmnSelection(enSuspendCause);
    }


    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcSuspendRsltAreaLost_PlmnSelection_WaitEpsRegRsltInd
 ��������  : ����״̬���������
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_ProcSuspendRsltAreaLost_PlmnSelection_WaitEpsRegRsltInd()
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    VOS_UINT32                                              ulResult;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ��ȡ�����ȼ������б� */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* ���µ�ǰ���������״̬Ϊ��ע������ڴ��������У��������Ѵ����� */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetCurrSearchingPlmn_PlmnSelection(),
                                            NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                            pstPlmnSelectionListInfo);

    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ֹͣ�ȴ�Epsע������Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��յȴ�ע������־ */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();

    /* �����NCELL����������Ҫ���������������ˣ��˳�״̬�� */
    if (NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL == NAS_MMC_GetPlmnSearchScene_PlmnSelection())
    {
        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ��һ��Ҫ����������,����ȡʧ�ܣ�����ϲ�״̬���ϱ�����ʧ�ܣ��˳�
      ����ȡ�ɹ������ж���һ��Ҫ�����������Ƿ��뵱ǰפ��������ͬ��
      ����ͬ���ڵ�ǰģʽ�����������������ǰ���� */
    ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

    /*  ��ȡ�¸�����ʧ�ܣ�����г����������� */
    if (VOS_TRUE != ulResult)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
        return;

    }

    /* ��MM��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* ��һ��Ҫ�����������Ƿ��뵱ǰפ�����粻ͬ,��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ�� */
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    else
    {
        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltInd
 ��������  : ����״̬���������
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��04��
    ��    ��   : sunxibo / 46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��4��9��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬��������ʧ��Ǩ�Ƶ�ooc
  3.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
  4.��    ��   : 2014��6��30��
    ��    ��   : b00269685
    �޸�����   : DSDS GUNAS III��Ŀ:�޸ĺ�������
  5.��    ��   : 2014��6��30��
    ��    ��   : b00269685
    �޸�����   : DTS2015051900500�޸�
  6.��    ��   : 2014��08��25��
    ��    ��   : m00312079
    �޸�����   : DTS2015082004682:L2C�ɹ����˳�����״̬��
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRslt = VOS_NULL_PTR;
     /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

     /* Ǩ�Ƶ���ͬ�Ľ��뼼��ʱ����ҪǨ�Ƶ���ͬ�Ĵ���ע����״̬ */

    enRatType = NAS_MML_GetCurrNetRatType();

    pstSuspendRslt  = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    if (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST != pstSuspendRslt->enFailCause)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltInd(): snd Mode change");
        NAS_MMC_NotifyModeChange(enRatType,
                                 NAS_MML_GetSimPsRegStatus());
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ֹͣ��ǰ�ȴ�EPSע�����Ķ�ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ״̬���˳����Ϊʧ�ܣ�Ǩ�Ƶ�OOC */
        NAS_MMC_ProcNoRf_PlmnSelection(enRatType);

        return VOS_TRUE;
    }

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
     || (NAS_MML_NET_RAT_TYPE_GSM == enRatType))
    {
        /* ֹͣ��ǰ�ȴ�EPSע�����Ķ�ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ���µ�ǰ�ȴ�CSPS��ע���� */
        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* ����CSPS��AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* ����CSPS��RegCause */
        NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
        NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);


        /* �յ�ϵͳ��Ϣ��Ǩ�Ƶ��ȴ�CS+PS���ע������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);


        return VOS_TRUE;
    }


    if (NAS_MML_NET_RAT_TYPE_LTE == enRatType)
    {
        if ((NAS_MMC_SUSPEND_FAIL                 == pstSuspendRslt->enRslt)
         && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST == pstSuspendRslt->enFailCause))
        {
            NAS_MMC_ProcSuspendRsltAreaLost_PlmnSelection_WaitEpsRegRsltInd();

            return VOS_TRUE;
        }
    }

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
#if ((FEATURE_ON == FEATURE_CL_INTERWORK) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))

    /* ��ѡ��HRPD��,�˳�ѡ��״̬�� */
    if ((NAS_MML_NET_RAT_TYPE_BUTT == enRatType)
     && (NAS_MMC_SUSPEND_SUCCESS == pstSuspendRslt->enRslt))
    {
        /* ֹͣ��ǰ�ȴ�EPSע�����Ķ�ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ���ϲ�״̬������������� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_INTER_SYS_HRPD);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
#endif
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltInd:ENTERED");
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltInd
 ��������  : �ȴ�EPS��REG CNF��ʱ����ʱ
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_EPS_REG_IND_TIMER��ʱ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��15��
    ��    ��   : W00166186
    �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
  3.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  4.��    ��   : 2012��5��24��
    ��    ��   : w00166186
    �޸�����   : DTS2012052203028,L�³����������������������ע��5�κ󣬵ȴ�ע������ʱ����ʱ��λ
  5.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  6.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_FSM_ID_ENUM_UINT32              enCurrentFsmId;
    VOS_UINT32                              ulCurrentEventType;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8    enPsAdditionalAction;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltInd: Timer Expired");

    /* ���·���״̬ */

	/* ֪ͨTAF��ǰ�ķ���״̬ */

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();

    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

        /*���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬��*/
        NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

        /* ��LMM�����û���������֪ͨ */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();

    /* �ȴ�CS PS��ע����ʱ���п���һ������ע�������˺����Լ��������е�ҵ��
      (����G�½���CS����к��У�PS���޷�����ע��),����MMCһ�µȲ�������һ�����
      ע��������ʱMMCֱ��ͨ��additional��������������MMC��ʱ���ݵ�ǰ�յ���ע
      �������µ�additionalֵ�������Ƿ�ɹ��˳�����״̬������ʧ���˳�����״̬����
      ��L1״̬����������״̬�����˳���������Ƿ�����������ѡ����ʱ�����Ǽ����ȴ�
      ҵ������Լ�CSPS��ע���� */

    enAdditionalAction = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* ���Ӳ���Ϊפ����ǰ���� */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enAdditionalAction))
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);
    }
    else
    {
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltInd
 ��������  : �ڵȴ�EPS�ϱ�ע������ʱ���յ�����ָʾ�������ӣ�ֱ�ӹ���������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_AREA_LOST_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��9��
    ��    ��   : w00167002
    �޸�����   : ��ע��������յ�����ָʾ������µ�ǰ�������ע��״̬Ϊ
                  NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,���������һ��������ȻΪ
                  �Ѿ����������硣
  3.��    ��   : 2011��12��15��
    ��    ��   : W00166186
    �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
  4.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
  5.��    ��   : 2012��06��13��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1���������������פ����־,��֤�˳�״̬��ʱ���������פ��
  6.��    ��   : 2012��7��16��
    ��    ��   : s00217060
    �޸�����   : for DTS2012071604442
                 ����:����,���һ�ȡ��һ������ʧ����Ҫ����פ��LTE
  7.��    ��   : 2012��09��27��
    ��    ��   : z00161729
    �޸�����   : DTS2012090303562:����״̬����Lע�����յ�������Ϣ��ȡ��һ������ʧ����״̬�����ַ���Ƿ������������
  8.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  9.��    ��   : 2013��8��27��
    ��    ��   : l00208543
    �޸�����   : Coverity
 10.��    ��   : 2014��1��28��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 11.��    ��   : 2014��6��12��
    ��    ��   : w00167002
    �޸�����   : DSDS III:L��NO RF������Ĵ���
 12.��    ��   : 2015��1��8��
    ��    ��   : w00167002
    �޸�����   : DTS2015010601540:��CSע��ɹ���PSע��ʧ��ʱ���ڼ����ȴ�ע���
                 ���У�������ռ��Դ����NO RF�������ڵȴ���Դ���ú����´���������ǰ
                 ���硣
 13.��    ��   : 2015��10��22��
    ��    ��   : s00217060
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND��Ϣ�ӿڱ��
 15.��    ��   : 2016��03��17��
    ��    ��   : j00174725
    �޸�����   : DTS2016031602848(eara lost ʱ����������û���չ�, ��Ҫ����ǰPLMN����һ��)
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    VOS_UINT32                                              ulResult;

    LMM_MMC_AREA_LOST_IND_STRU                             *pstLmmAreaLostMsg           = VOS_NULL_PTR;

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo    = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo              = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_CNT_AND_RAT_STRU                     *pstLastAreaLostPlmnInfo     = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsRrcSearchPlmn;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    pstLmmAreaLostMsg   =  (LMM_MMC_AREA_LOST_IND_STRU *)pstMsg;

    /* ��ȡ��ǰפ����������Ϣ */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* ��ȡ�����ȼ������б� */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    ulIsRrcSearchPlmn       = NAS_MMC_IsLmmSearchedAreaLostPlmn(pstLmmAreaLostMsg);
    pstLastAreaLostPlmnInfo = NAS_MMC_GetLastAreaLostPLmnInfoCtx_PlmnSelection();

    NAS_MMC_UpdateLastAreaLostPlmnWIthRatAndCnt(pstLastAreaLostPlmnInfo, &stCurPlmn.stPlmnId, stCurPlmn.enRat);



    /* ֹͣ�ȴ�Epsע������Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    if (MMC_LMM_AREA_LOST_REASON_NO_RF == pstLmmAreaLostMsg->enAreaLostReason)
    {
        /* ���µ�ǰ����״̬ΪEXIT,��Դ�ָ������� */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                        NAS_MMC_NET_STATUS_SEARCHED_EXIST,
                                        pstPlmnSelectionListInfo);

        /* �ظ�״̬��ʧ�� */
        NAS_MMC_ProcNoRfAreaLost_PlmnSelection(NAS_MML_GetCurrNetRatType());

        return VOS_TRUE;
    }

    /* �ڵȴ�ע����ʱ�������NO RF���������򲻸��µ�ǰΪREGISTER״̬���ȴ���Դ
       ����ʱ�򣬿��Լ����������ڴ������Ͻ���ע�� */
    /* ���µ�ǰ���������״̬Ϊ��ע������ڴ��������У��������Ѵ����� */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                        NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                        pstPlmnSelectionListInfo);

    /* �����Ƿ���й�history�� */
    if (VOS_TRUE == ulIsRrcSearchPlmn)
    {
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltInd: abort");
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��յȴ�ע������־ */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    /* �����NCELL����������Ҫ���������������ˣ��˳�״̬�� */
    if (NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL == NAS_MMC_GetPlmnSearchScene_PlmnSelection())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltInd: NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL");
        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

    if ( (NAS_MML_GetLastAreaLostPlmnCnt(pstLastAreaLostPlmnInfo) >= NAS_MMC_AREA_LOST_SEARCH_MAX_NUM)
      || (VOS_TRUE == ulIsRrcSearchPlmn) )
    {
        /* ��ȡ��һ��Ҫ����������,����ȡʧ�ܣ�����ϲ�״̬���ϱ�����ʧ�ܣ��˳�
          ����ȡ�ɹ������ж���һ��Ҫ�����������Ƿ��뵱ǰפ��������ͬ��
          ����ͬ���ڵ�ǰģʽ�����������������ǰ���� */
        ulResult = NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn);

        /*  ��ȡ�¸�����ʧ�ܣ�����г����������� */
        if (VOS_TRUE != ulResult)
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltInd: NAS_MMC_GetNextSearchPlmn_PlmnSelection false");
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();
            return VOS_TRUE;
        }
    }
    else
    {
        stDestPlmn.stPlmnId.ulMcc   = stCurPlmn.stPlmnId.ulMcc;
        stDestPlmn.stPlmnId.ulMnc   = stCurPlmn.stPlmnId.ulMnc;
        stDestPlmn.enRat            = stCurPlmn.enRat;
    }

    /* ��MM��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* ��һ��Ҫ�����������Ƿ��뵱ǰפ�����粻ͬ,��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ�� */
    if (stDestPlmn.enRat != NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }
    else
    {
        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltInd
 ��������  : MMC����LMM�ϱ���ϵͳ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:LMM�ϱ���ϵͳ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��6��
    ��    ��   : w00167002
    �޸�����   : PhaseII�޸�:ɾ�����ĵ�ǰ�������ע��״̬ΪREGISTERED��
                 ͳһ��ע�����󣬲Ÿ���ΪREGISTERED
  3.��    ��   : 2012��4��18��
    ��    ��   : l00130025
    �޸�����   : DTS2012040200480,����ά��EPSע��״̬,����ѯ���ϱ�ʹ��
  4.��    ��   : 2012��4��28��
    ��    ��   : W00166186
    �޸�����   : DTS2012042602593,MMû�б��浱ǰפ����PLMN�����º����жϳ���
  5.��    ��   : 2012��11��29��
    ��    ��   : w00176964
    �޸�����   : DTS2012042804167:֪ͨCBAģ�鵱ǰ����ģʽΪLTE
  6.��    ��   : 2012��12��20��
    ��    ��   : w00176964
    �޸�����   : DTS2012121906946:�յ�L��ϵͳ��Ϣת����LMM
  7.��    ��   : 2013��1��19��
    ��    ��   : t00212959
    �޸�����   : DTS2012122900189:EPSע��״̬��ȫ��L�ϱ�
  8.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 �����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);



    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */
    /*�����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC*/
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        NAS_MMC_SndMsccSysInfo();

    }

    /* ת��GMMϵͳ��Ϣ,��rabmʹ�� */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltInd
 ��������  : MMC����MMA�����ָ��������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��04��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;

    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �����û�ָ��������Ϣ�����µ�ǰ����������Ϊ�ֶ�ģʽ */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                        pstUserSelReqMsg->enAccessMode);

    /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* �����û�ָ�������������³�ʼ��ѡ���б� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* ���û�ָ�����뼼��������(Ҳ�ǵ�ǰ����)����Ϊ������ע������ظ�ע�� */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause, enPsRegCause))
    {
        return VOS_TRUE;
    }

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltInd
 ��������  : MMC����MSCC�����SYSCFG������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��04��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֱ�ӵ���syscfg���״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltInd
 ��������  : ����SYSCFG״̬�����صĽ��
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, begin */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltInd
 ��������  : ����MSCC��IMS VOICE�Ƿ������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
             VOS_FALSE:����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��2��7��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *pstImsVoiceNtf = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnSelection();
    pstImsVoiceNtf      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;
    /* ����ڵȴ�PS��ע����������ȴ�PSע���� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_PS == (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_PS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceNtf->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);

            /* �Ѿ�Disable L����ע��ɹ�,��Ҫ����ǰ���籣����״̬����������,���ں���
               GU����ʧ�����»ظ������ṩPSҵ��*/
            NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(NAS_MML_GetCurrCampPlmnId());
        }
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

            return VOS_TRUE;
        }

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, end */


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSrch_WaitEpsConnRelInd
 ��������  : �ȴ�L�����ͷŵĹ������յ��˳�״̬��������
 �������  : ulEventType:��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��26��
   ��    ��   : W00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��29��
   ��    ��   : w00167002
   �޸�����   : DTS2011112301233:���Ӵ���¼�ID��״̬������֪����ʲô�¼�
                ����Լ��ġ�
                �޸�ԭ��:�û��·��ػ�����󣬵�ǰ�����ڵ�ע���������ڵ�����
                �ͷţ�������Ҫ�ȽϾõ�ʱ����ܴ���ػ����ͨ�����Ӵ���¼���
                ��鵱ǰ�ڵ�ע�������ߵ������ͷ�״̬�����յ��ػ������ֱ��
                �˳���ǰ״̬���������û��Ĺػ����

 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* ������������û�����Ĺػ�����ֱ���˳��������ͷŽ��״̬�� */
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����Abort��־, �������ͷź����quit */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsConnRelInd
 ��������  : ����SYSCFG״̬�����صĽ��
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsConnRelInd
 ��������  : MMC�յ�LMM�ϱ���Status Ind��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��21��
   ��    ��   : W00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��12��
   ��    ��   : L00171473
   �޸�����   : �޸ĵ��ú��� for V7R1 phase II
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 4.��    ��   : 2014��2��8��
   ��    ��   : w00176964
   �޸�����   : VOLTE_Phase3����:���������ͷ�ʱҲ��Ҫ����additionֵˢ��ѡ���б�

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, begin */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, end */

    pstLmmStatusIndMsg  = ( LMM_MMC_STATUS_IND_STRU* )pstMsg;


    /* ����EPS������Ӵ���״̬ */
    if ( (MMC_LMM_CONN_ESTING == pstLmmStatusIndMsg->ulConnState)
      || (MMC_LMM_CONNECTED_SIG == pstLmmStatusIndMsg->ulConnState) )
    {
        /* ���ô���EPS�������� */
        NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
    }
    else if (MMC_LMM_CONNECTED_DATA == pstLmmStatusIndMsg->ulConnState)
    {
        /* ���ô���EPSҵ������ */
        NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);
    }
    else if (MMC_LMM_CONN_IDLE == pstLmmStatusIndMsg->ulConnState)
    {
        /* ���ò�����EPS�������� */
        NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
        NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
    }
    else
    {
        ;
    }

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* �Ƿ���Ҫ Abort״̬�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* ���ϲ�״̬��ָʾѡ��ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����������Ӳ����ڶ��Ҳ��������ͷ���������и��Ӳ��� */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, begin */
        /* �����ͷ�����ʱ,����additionҲ���ܵ�������,ǰ���յ�ע����δˢ��ѡ���б�,�˴���Ҫ��ˢ��һ�� */
        enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                              NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

        NAS_MMC_RefreshPlmnSelectionListAfterRegFail_PlmnSelection(enAdditionalAction);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, end */

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnSelection_WaitEpsConnRelInd
 ��������  : �ȴ������ͷŶ�ʱ����ʱ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��21��
   ��    ��   : W00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��22��
   ��    ��   : L00171473
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������
 3.��    ��   : 2011��12��1��
   ��    ��   : w00176964
   �޸�����   : GUNAS V7R1 PhaseIV �׶ε���
 4.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnSelection_WaitEpsConnRelInd ENTERED");


    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����������Ӳ����ڶ��Ҳ��������ͷ���������и��Ӳ��� */
    if (VOS_FALSE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        /* ���������ͷ�����MM��GMM�����������ȴ������ͷŶ�ʱ�� */
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_TRUE);

        NAS_MMC_SndLmmRelReq();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
    }
    else
    {
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_FALSE);

        NAS_MMC_SearchNextPlmn_PlmnSelection();
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsConnRelInd
 ��������  : MMC����LMM�ϱ���ϵͳ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:LMM�ϱ���ϵͳ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : W00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��26��
   ��    ��   : L00171473
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������
 3.��    ��   : 2012��4��18��
   ��    ��   : l00130025
   �޸�����   : DTS2012040200480,����ά��EPSע��״̬,����ѯ���ϱ�ʹ��
 4.��    ��   : 2012��4��28��
   ��    ��   : W00166186
   �޸�����   : DTS2012042602593,MMû�б��浱ǰפ����PLMN�����º����жϳ���
 5.��    ��   : 2012��11��29��
   ��    ��   : w00176964
   �޸�����   : DTS2012042804167:֪ͨCBAģ�鵱ǰ����ģʽΪLTE
 6.��    ��   : 2012��12��20��
   ��    ��   : w00176964
   �޸�����   : DTS2012121906946:�յ�L��ϵͳ��Ϣת����LMM
 7.��    ��   : 2013��1��19��
   ��    ��   : t00212959
   �޸�����   : DTS2012122900189:EPSע��״̬��ȫ��L�ϱ�
 8.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 �����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU         stOldCampInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* ��������������ͷ�,������Ҫ������������,ϵͳ��Ϣ������ */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);



    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    /*�����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC*/
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        NAS_MMC_SndMsccSysInfo();

    }

    /* ת��GMMϵͳ��Ϣ,��rabmʹ�� */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsConnRelInd
 ��������  : MMC����MSCC�����SYSCFG������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:SYSCFG������Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��04��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֱ�ӵ���syscfg���״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsConnRelInd
 ��������  : LMM�ϱ���SUSPEND_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��20��
   ��    ��   : W00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��12��
   ��    ��   : L00171473
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg = VOS_NULL_PTR;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
    VOS_UINT32                          ulRelRequestFlg;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    ulRelRequestFlg = NAS_MMC_GetRelRequestFlag_PlmnSelection();

    /* Lģ�£�����ԭ������GU�²�ͬ��ת��һ�¹���ԭ���� */
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLSuspendMsg->ulSysChngType, &enSuspendCause);

    /* ����������ͷŻ����Ѿ����յ�Abort��Ϣ,�����������ϵͳ��ѡ */
    if ((VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
     || (VOS_TRUE == ulRelRequestFlg)
     || (MMC_SUSPEND_CAUSE_PLMNSEARCH == enSuspendCause)
     || (MMC_SUSPEND_CAUSE_BUTT <= enSuspendCause))
    {
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
    }
    else
    {
        /* ����SUSPEND��Ϣ�еĲ�ͬ��������Ӧ��״̬�� */
        NAS_MMC_LoadInterSysFsm_PlmnSelection(enSuspendCause);
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitEpsConnRelInd
 ��������  : ����״̬���������
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��04��
   ��    ��   : sunxibo / 46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��22��
   ��    ��   : L00171473
   �޸�����   : PhaseII�޸�,PlmnSelection״̬������
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 4.��    ��   : 2013��4��4��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬��������ʧ�ܣ�Ǩ�Ƶ�OOC
 5.��    ��   : 2014��1��27��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
 6.��    ��   : 2014��6��30��
   ��    ��   : b00269685
   �޸�����   : DSDS GUNAS III��Ŀ:�޸ĺ�������

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRsltMsg = VOS_NULL_PTR;

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRslt = VOS_NULL_PTR;
#endif
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

    /* Ǩ�Ƶ���ͬ�Ľ��뼼��ʱ����ҪǨ�Ƶ���ͬ�Ĵ���ע����״̬ */
    enRatType = NAS_MML_GetCurrNetRatType();

    pstSuspendRsltMsg = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    if (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST != pstSuspendRsltMsg->enFailCause)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitEpsConnRelInd(): snd Mode change");
        NAS_MMC_NotifyModeChange(enRatType,
                                 NAS_MML_GetSimPsRegStatus());
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ֹͣ��ǰ�ȴ�eps�����ͷŶ�ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* ״̬���˳����Ϊʧ�ܣ�Ǩ�Ƶ�OOC */
        NAS_MMC_ProcNoRf_PlmnSelection(enRatType);

        return VOS_TRUE;
    }

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
     || (NAS_MML_NET_RAT_TYPE_GSM == enRatType))
    {
        /* ֹͣ��ǰ�ȴ�eps�����ͷŶ�ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* ���µ�ǰ�ȴ�CSPS��ע���� */
        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_CS);
        NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* ����CSPS��AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* ����CSPS��RegCause */
        NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
        NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);


        /* �յ�ϵͳ��Ϣ��Ǩ�Ƶ��ȴ�CS+PS���ע������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);


        return VOS_TRUE;
    }

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    pstSuspendRslt  = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    /* ��ѡ��HRPD��,�˳�ѡ��״̬�� */
    if ((NAS_MML_NET_RAT_TYPE_BUTT == enRatType)
     && (NAS_MMC_SUSPEND_SUCCESS == pstSuspendRslt->enRslt))
    {
        /* ֹͣ��ǰ�ȴ�eps�����ͷŶ�ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* ���ϲ�״̬�����͸����ȼ�����ʧ�ܣ���Ҫ���� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_INTER_SYS_HRPD);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
#endif
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����������Ӳ����ڿ��ܷ������� */
    NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection();


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsConnRelInd
 ��������  : ����MSCC���͵��û�ָ��������,�û�ָ����PlmnId��RAT�͵�ǰפ����PlmnId
             ��RAT��ͬ���Ż����ô���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��12��
   ��    ��   : lijun 00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��31��
   ��    ��   : w00166186
   �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsCause;

    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �����ֶ�������Ϣ */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                       pstUserSelReqMsg->enAccessMode);

    /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* �����û�ָ�������������³�ʼ��ѡ���б� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* ���û�ָ�����뼼��������(Ҳ�ǵ�ǰ����)����Ϊ������ע������ظ�ע�� */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    /* �����û�ָ����PlmnId��RAT�͵�ǰפ����PlmnId��RAT��ͬ��ֱ�ӷ���ָ��������� */
    enCsCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsCause, enPsCause))
    {
        return VOS_TRUE;
    }

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsConnRelInd
 ��������  : �ڵȴ�LTE�����ͷ�ʱ���յ�ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ�Ĵ���,
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��22��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��16��
    ��    ��   : b00269685
    �޸�����   : ������CSFB��־����Ҫ�������޸������ϢΪCSFB����������

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU                        *pstSerRsltMsg       = VOS_NULL_PTR;
    /* Added by b00269685 for ����FR�Ż�, 2014-10-16, begin */
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstInterPlmnSrchMsg = VOS_NULL_PTR;
    /* Added by b00269685 for ����FR�Ż�, 2014-10-16, end */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstSerRsltMsg     = (LMM_MMC_SERVICE_RESULT_IND_STRU*)pstMsg;

    /* ����LMM��service result���������һ�������� */
    enAdditionalAction = NAS_MMC_ProcLmmServiceRsltInd(pstSerRsltMsg);

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* Added by b00269685 for ����FR�Ż�, 2014-10-16, begin */
    if ((VOS_TRUE                                 == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION == enAdditionalAction))
    {
        pstInterPlmnSrchMsg = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU));
        if (VOS_NULL_PTR != pstInterPlmnSrchMsg)
        {
            /* �޸������ϢΪCSFB���������� */
            NAS_MMC_BulidInterPlmnSearchReqMsg(NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ, VOS_NULL_PTR, 0, pstInterPlmnSrchMsg);
            NAS_MMC_SaveCurEntryMsg(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),
                                    (struct MsgCB*)pstInterPlmnSrchMsg);
            PS_MEM_FREE(WUEPS_PID_MMC, pstInterPlmnSrchMsg);
        }
        else
        {
            /* �쳣��ӡ */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsConnRelInd Alloc mem fail");
        }
    }
    /* Added by b00269685 for ����FR�Ż�, 2014-10-16, end */

    NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģsuspend CNF�����н��յ�Abort��Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��01��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�յ�WAS��suspend cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��01��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��2��18��
   ��    ��  :  w00242748
   �޸�����  :  DTS2014021803515:��λʱ��ȷ���յ��ĸ����뼼�����쳣��Ϣ���µġ�
 3.��    ��   : 2014��3��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014031200137:��NV���Դ�ʱ���Զ�������������ʱ������״�����RPLMN�Ļ���
                ��Ҫ��HPLMN/EHPLMN��������㡣
 4.��    ��   : 2015��3��11��
   ��    ��   : wx270776
   �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stReCampLtePlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     stDestPlmnList;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    PS_MEM_SET(&stReCampLtePlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    PS_MEM_SET(&stDestPlmnList, 0, sizeof(NAS_MML_PLMN_LIST_WITH_RAT_STRU));

    pstSuspendCnf            = (RRMM_SUSPEND_CNF_ST*)pstMsg;
    stReCampLtePlmn.enRat    = NAS_MML_NET_RAT_TYPE_LTE;

    PS_MEM_CPY(&(stReCampLtePlmn.stPlmnId),
               NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection(),
               sizeof(stReCampLtePlmn.stPlmnId));

    enCurRat      = NAS_MML_GetCurrNetRatType();

    enPlmnSearchScene  = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* ���ɻָ�����,���õ���ӿ�RESET */
        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ���õ�ǰ���뼼��ΪBUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* �ظ�Plmn Selectionִ�н�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ������Ҫ���»�LTE�����磬
       ���ڹ�������п��ܽ��յ��û�Detach PS�������˴���Ҫ���ж������Ƿ���Ч */
    if (VOS_TRUE == NAS_MMC_IsReCampLtePlmnValid_PlmnSelection())
    {
        /* ���õ�ǰ���뼼��ΪLTE */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

        /* ��LMM����ָ������ */
        PS_MEM_SET(&stDestPlmnList, 0x0, sizeof(stDestPlmnList));

        stDestPlmnList.ulPlmnNum = 1;
        PS_MEM_CPY(&stDestPlmnList.astPlmnId[0], &stReCampLtePlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

        NAS_MMC_SndLmmSpecPlmnSearchReq(&stDestPlmnList, VOS_FALSE, enPlmnSearchScene);

        /* ״̬Ǩ��NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE);

        /* ����������ʱ��TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
    }
    else
    {
        /* ���õ�ǰ���뼼��ΪBUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* �ظ�Plmn Selectionִ�н�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�յ�GAS��suspend cnf��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��01��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��3��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014031200137:��NV���Դ�ʱ���Զ�������������ʱ������״�����RPLMN�Ļ���
                ��Ҫ��HPLMN/EHPLMN��������㡣
 3.��    ��   : 2015��3��11��
   ��    ��   : wx270776
   �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stReCampLtePlmn;
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     stDestPlmnList;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    PS_MEM_SET(&stReCampLtePlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    PS_MEM_SET(&stDestPlmnList, 0, sizeof(NAS_MML_PLMN_LIST_WITH_RAT_STRU));

    pstSuspendCnf            = (RRMM_SUSPEND_CNF_ST*)pstMsg;
    stReCampLtePlmn.enRat    = NAS_MML_NET_RAT_TYPE_LTE;

    PS_MEM_CPY(&(stReCampLtePlmn.stPlmnId),
               NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection(),
               sizeof(stReCampLtePlmn.stPlmnId));

    enPlmnSearchScene  = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* ���ɻָ�����,���õ���ӿ�RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ���õ�ǰ���뼼��ΪBUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* �ظ�Plmn Selectionִ�н�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ������Ҫ���»�LTE�����磬
       ���ڹ�������п��ܽ��յ��û�Detach PS�������˴���Ҫ���ж������Ƿ���Ч */
    if (VOS_TRUE == NAS_MMC_IsReCampLtePlmnValid_PlmnSelection())
    {
        /* ���õ�ǰ���뼼��ΪLTE */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

        /* ��LMM����ָ������ */
        PS_MEM_SET(&stDestPlmnList, 0x0, sizeof(stDestPlmnList));

        stDestPlmnList.ulPlmnNum = 1;
        PS_MEM_CPY(&stDestPlmnList.astPlmnId[0], &stReCampLtePlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

        NAS_MMC_SndLmmSpecPlmnSearchReq(&stDestPlmnList, VOS_FALSE, enPlmnSearchScene);

        /* ״̬Ǩ��NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE);

        /* ����������ʱ��TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
    }
    else
    {
        /* ���õ�ǰ���뼼��ΪBUTT */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* �ظ�Plmn Selectionִ�н�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģsuspend CNF�����б�����ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��01��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��2��18��
   ��    ��  :  w00242748
   �޸�����  :  DTS2014021803515:��λʱ��ȷ���յ��ĸ����뼼�����쳣��Ϣ���µġ�
 3.��    ��   : 2015��3��11��
   ��    ��   : wx270776
   �޸�����   : DTS2015011212939:���Ӹ�λ����
****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* ���ɻָ����ϣ���λ */
    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��LTE�ȴ�LTE�����ظ��������յ�״̬���˳���Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��01��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    /* ֪ͨLMMָֹͣ������ */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*Ǩ�Ƶ��ȴ�ֹͣ����ȷ��״̬������������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�յ�LTE����CNF��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_PLMN_SRCH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��01��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��27��
    ��    ��   : z40661
    �޸�����   : DTS2012091205098,L��������ʱ,δ����ȫƵ������
  3.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
  4.��    ��   : 2014��6��12��
    ��    ��   : w00167002
    �޸�����   : DSDS III:��NO RF���OOC״̬
  5.��    ��   : 2015��4��23��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;

    NAS_MML_PLMN_WITH_RAT_STRU                              stReCampLtePlmn;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ���õ�ǰģʽ�Ƿ����ȫƵ�������Ƿ�������縲�� */
    NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(pstLmmSrchCnfMsg);

    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC == pstLmmSrchCnfMsg->enRlst)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* disable lteԭ����MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOWʱ��
           ����������ڽ�ֹ���뼼����������ɾ�� */
        if (MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW != NAS_MML_GetDisableLteReason())
        {
            stReCampLtePlmn.enRat    = NAS_MML_NET_RAT_TYPE_LTE;
            PS_MEM_CPY(&(stReCampLtePlmn.stPlmnId),
               NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection(),
               sizeof(stReCampLtePlmn.stPlmnId));
            NAS_MML_DeleteSpecDisabledPlmnWithValidPeriodInPlmnList(&stReCampLtePlmn);
        }

        /*Ǩ��״̬������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);
    }
    else
    {

        /* �����ǰΪNO RF����ֱ����״̬�� */
        if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstLmmSrchCnfMsg->enRlst)
        {
            NAS_MMC_ProcNoRf_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

            return VOS_TRUE;
        }

        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* ��ע������������CS/PS����״̬��δ�ϱ�����ʱ��Ҫ���� */



        /* ���µ�ǰ���뼼��������ȫƵ���� */
        NAS_MMC_SetAllBandSearch_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);


        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* �˳����״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�յ�ID_LMM_MMC_ATTACH_CNF�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_ATTACH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��9��3��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ǰLTE������״̬��ΪDISABLE״̬���򲻴������Ϣ */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte: unexpect message received");

        return VOS_TRUE;
    }

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ֪ͨLMMָֹͣ������ */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*Ǩ��״̬������������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�յ�ID_LMM_MMC_DETACH_CNF�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_DETACH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��5��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ǰLTE������״̬��ΪDISABLE״̬���򲻴������Ϣ */
    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte: unexpect message received");

        return VOS_TRUE;
    }

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ֪ͨLMMָֹͣ������ */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /*Ǩ��״̬������������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�LTE�����ظ�������������ʱ����ʱ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��5��29��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��5��5��
   ��    ��   : w00242748
   �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                ע��״̬���ϱ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte ENTERED");

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* ��ע������������CS/PS����״̬��δ�ϱ�����ʱ��Ҫ���� */


    /* ���ϲ�״̬��ָʾѡ��ʧ�� */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    /* �˳����״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPlmnStopCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�յ�LTE��plmn search stop cnf��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmPlmnStopCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* �ж��Ƿ���ڴ�ϱ�־ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ���ϲ�״̬��ָʾѡ������� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* �˳����״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�LTE��plmn search stop CNF�����б�����ʱ����ʱ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

****************************************************************************/

VOS_UINT32 NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte: Timer Expired");

    /* �ж��Ƿ���ڴ�ϱ�־ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ���ϲ�״̬��ָʾѡ������� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* �˳����״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�Lmm�����ظ�״̬�յ�LTE��plmn search cnf��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU          *pstLmmSrchCnfMsg = VOS_NULL_PTR;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    /* ���õ�ǰģʽ�Ƿ����ȫƵ�������Ƿ�������縲�� */
    NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(pstLmmSrchCnfMsg);

    /* �ж��Ƿ���ڴ�ϱ�־ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ���ϲ�״̬��ָʾѡ����ֹ */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* �˳����״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�ϵͳ��ϢMMC����Aort��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:Abort��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��2��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����Abort��־ */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��LteģMMC����LMM�ϱ���ϵͳ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:LMM�ϱ���ϵͳ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��29��
   ��    ��   : w00176964
   �޸�����   : DTS2012042804167:֪ͨCBAģ�鵱ǰ����ģʽΪLTE
 3.��    ��   : 2012��12��20��
   ��    ��   : w00176964
   �޸�����   : DTS2012121906946:�յ�L��ϵͳ��Ϣת����LMM
 4.��    ��   : 2013��1��19��
   ��    ��   : t00212959
   �޸�����   : DTS2012122900189:EPSע��״̬��ȫ��L�ϱ�
 5.��    ��   : 2013��2��7��
   ��    ��   : W00176964
   �޸�����   : Volte_phase3��Ŀ����:����IMS������ʱdisable Lģ���߼��޸�
 6.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 �����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ֹͣ�ȴ�ϵͳ��Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE  == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬������� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);



    /* ���µ�ǰ����״̬���� */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* ���µ�ǰ�ȴ�EPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection();
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, begin */
#if (FEATURE_ON == FEATURE_IMS)
    /* ���ӵȴ�IMS�Ƿ���ý��FLG,MMA��֤�յ�PSע�����ϱ�IMS�Ƿ����ָʾ��MMC */
    NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, end */

    /* ����CS/PS��ע��Cause��AdditionalAction */
    NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);
    NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_BUTT);

    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    /*�����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC*/
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        NAS_MMC_SndMsccSysInfo();

    }


    /* ת��GMMϵͳ��Ϣ */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    /* Ǩ�Ƶ��ȴ�ע������״̬PLMN_SRCH:NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��LTE�ȴ�ϵͳ��Ϣ��ʱ����ʱ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_SYS_INFO��ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte: Timer Expired");

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /*�����ǰ��Ҫ�˳�״̬��*/
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬������� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* �˳����״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ڵȴ�EPS�ϱ�ע������ʱ���յ�QUIT��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg: Abort��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* ������������û�����Ĺػ���������ϻ�ǰû�����ӿ���ֱ���˳� */
    if ((VOS_FALSE == NAS_MML_IsRrcConnExist())
     || (NAS_MMC_ABORT_FSM_IMMEDIATELY == pstAbortMsg->enAbortFsmType)
     /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
     || (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType))
     /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    {
        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* �ظ�״̬������� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����Abort��־ */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��LteģLMM�ϱ���CONN Status Ind��Ϣ������
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_STATUS_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    /* ����LMM������״̬ */
    NAS_MML_UpdateEpsConnectionStatus(pstLmmStatusIndMsg->ulConnState);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��LteģWaitEpsRegRsltIndʱ��LMM�ϱ���ID_LMM_MMC_ATTACH_IND��Ϣ������
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��2��7��
   ��    ��   : W00176964
   �޸�����   : Volte_phase3��Ŀ����:����IMS������ʱdisable Lģ���߼��޸�
 3.��    ��   : 2015��4��22��
   ��    ��   : wx270776
   �޸�����   : DTS2015031602665:��CL ATTACHע��״̬����ȫ�ֱ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* ����ȴ�PS��־ */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    if ( VOS_TRUE == NAS_MMC_IsNeedUpdateLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus) )
    {
        NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus);
    }

    /* LMM������δ�ظ�search cnfʱ�յ��û�detach ps����󣬺���������ע���mmc�ظ�attach result
       ΪMMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW���������������MMC_LMM_ATT_TYPE_BUTT��
       MMC��Ҫ���ݵ�ǰue operation mode�������������¸�ֵ */
    if ((MMC_LMM_ATT_TYPE_BUTT == pstLmmAttachIndMsg->ulReqType)
     && (MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW == pstLmmAttachIndMsg->ulAttachRslt))
    {
        pstLmmAttachIndMsg->ulReqType = NAS_MMC_ConvertLmmAttachReqType(NAS_MML_GetLteUeOperationMode());
    }

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_PlmnSelection(pstLmmAttachIndMsg);

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ״̬���˳����ΪAbort */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                          NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, begin */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* ͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, end */

    /* ���Ӳ���Ϊפ����ǰ���� */
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*  ��������������ӣ�Ǩ�Ƶ��ȴ������ͷ�״̬  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ����פ��LTEʱ������״̬�ϱ� */
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �ظ�״̬���˳�ʧ�� */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
    {
        /* ���Disable Lȫ�ֱ�����־ */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ڵȴ�LTEע����ʱ��
              �յ�ID_LMM_MMC_TAU_RESULT_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��2��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��2��7��
    ��    ��   : W00176964
    �޸�����   : Volte_phase3��Ŀ����:����IMS������ʱdisable Lģ���߼��޸�

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* ����ȴ�PS��־ */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ��GMM��MMת��TAU�����Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����TAU��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnSelection(pstLmmTauIndMsg);

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ״̬���˳����ΪAbort */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                          NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, begin */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnSelection())
    {
        return VOS_TRUE;
    }

    /* ͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, end */

    /* ���Ӳ���Ϊפ����ǰ���� */
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*  ��������������ӣ�Ǩ�Ƶ��ȴ������ͷ�״̬  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ����פ��LTEʱ������״̬�ϱ� */
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �ظ�״̬���˳�ʧ�� */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
    {
        /* ���Disable Lȫ�ֱ�����־ */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ڵȴ�LTEע����ʱ��
              �յ�ID_LMM_MMC_DETACH_IND��Ϣ�Ĵ���,��LMMȷ�ϣ��ó�����ֻ��������Detach PS����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��9��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��1��11��
    ��    ��   : w00176964
    �޸�����   : DTS2013010706662:��������EPLMN�߼�����λ��

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* ����DETACH��Ϣ�������һ������ */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    /*����EPS����һ���Ķ�������*/
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /*����CS����һ���Ķ�������*/
    if (NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        NAS_MMC_SndOmEquPlmn();
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ״̬���˳����ΪAbort */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                              NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

    /* ѡ������AdditionalActionΪ��Ҫ�����ȴ�ע���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        /*���ؼ����ȴ�ע����*/
        return VOS_TRUE;
    }

    /* ͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* ���Ӳ���Ϊפ����ǰ���� */
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*  ��������������ӣ�Ǩ�Ƶ��ȴ������ͷ�״̬  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
    }
    else
    {
        /* �ظ�״̬���˳�ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ڵȴ�LTEע����ʱ��
              �յ�ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ�Ĵ���,
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��26��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU                        *pstSerRsltMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstSerRsltMsg     = (LMM_MMC_SERVICE_RESULT_IND_STRU*)pstMsg;

    /* ��LMM�ķ��������д���������ɺ󷵻���Ҫ���е�ѡ������ */
    enAdditionalAction = NAS_MMC_ProcLmmServiceRsltInd(pstSerRsltMsg);

    /* ѡ������AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* ״̬���˳����ΪAbort */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                              NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

    /* ѡ������AdditionalActionΪ��Ҫ�����ȴ�ע���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        /*���ؼ����ȴ�ע����*/
        return VOS_TRUE;
    }

    /* ͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* ���Ӳ���Ϊפ����ǰ���� */
    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*  ��������������ӣ�Ǩ�Ƶ��ȴ������ͷ�״̬  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* �ظ�״̬���˳�ʧ�� */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�ע����ʱLMM�ϱ���SUSPEND_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��2��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg = VOS_NULL_PTR;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* Lģ�£�����ԭ������GU�²�ͬ��ת��һ�¹���ԭ���� */
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLSuspendMsg->ulSysChngType, &enSuspendCause);

    /* ���ΪOOS���߲�������ȷ, �����������ϵͳ��ѡ */
    if (MMC_SUSPEND_CAUSE_BUTT <= enSuspendCause)
    {
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
    }
    else
    {
        /* ����SUSPEND��Ϣ�еĲ�ͬ��������Ӧ��״̬�� */
        NAS_MMC_LoadInterSysFsm_PlmnSelection(enSuspendCause);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�ע����ʱ����״̬���������
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��2��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��4��9��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬��������ʧ��Ǩ�Ƶ�ooc
  3.��    ��   : 2014��1��27��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���
  4.��    ��   : 2014��6��30��
    ��    ��   : b00269685
    �޸�����   : DSDS GUNAS III��Ŀ:�޸ĺ�������
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRsltMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    pstSuspendRsltMsg = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    if (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST != pstSuspendRsltMsg->enFailCause)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(): snd Mode change");
        NAS_MMC_NotifyModeChange(enRatType,
                                 NAS_MML_GetSimPsRegStatus());
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ״̬���˳����Ϊʧ�ܣ�Ǩ�Ƶ�OOC */
        NAS_MMC_ProcNoRf_PlmnSelection(enRatType);

        return VOS_TRUE;
    }

    /* �����ǰ��ϵͳ�ı䵽GU,ֱ���˳�״̬�� */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
     || (NAS_MML_NET_RAT_TYPE_GSM == enRatType))
    {
        /* ״̬���˳����Ϊ�ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }


    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, Begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* ��ѡ��HRPD��,�˳�ѡ��״̬�� */
    if (NAS_MML_NET_RAT_TYPE_BUTT == enRatType)
    {
        /* ֹͣ�ȴ�epsע������Ϣ�Ķ�ʱ��  */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ���ϲ�״̬�����͸����ȼ�����ʧ�ܣ���Ҫ���� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_INTER_SYS_HRPD);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
#endif
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-27, End */

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�ע����ʱ��ʱ����ʱ
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_EPS_REG_IND_TIMER��ʱ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��2��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte: Timer Expired");

    /* ����NAS_MMC_SetPsServiceStatus����EPS����״̬NAS_MMC_LIMITED_SERVICE */

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        /* �ظ�״̬������� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);
    }
    else
    {
        /* ����״̬���˳������Ϣ�����Ϊʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);
    }

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ڵȴ�EPS�ϱ�ע������ʱ���յ�����ָʾ��
              �����ӣ�ֱ�ӹ���������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_AREA_LOST_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��5��5��
   ��    ��   : w00242748
   �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                ע��״̬���ϱ���
 3.��    ��   : 2014��6��12��
   ��    ��   : w00167002
   �޸�����   : DSDS III:L��NO RF������Ĵ���
 4.��    ��   : 2015��10��22��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:RRMM_AREA_LOST_IND��Ϣ�ӿڱ��
 5.��    ��   : 2016��3��22��
   ��    ��   : j00174725
   �޸�����   : DTS2016031602848
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_AREA_LOST_IND_STRU          *pstLmmAreaLostMsg  = VOS_NULL_PTR;


    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo    = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo              = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_CNT_AND_RAT_STRU                     *pstLastAreaLostPlmnInfo     = VOS_NULL_PTR;
    VOS_UINT32                                              ulIsRrcSearchPlmn;
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                         stDestPlmnList;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    pstLmmAreaLostMsg   =  (LMM_MMC_AREA_LOST_IND_STRU *)pstMsg;


    /* ��ȡ�����ȼ������б� */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    
    PS_MEM_SET(&stDestPlmnList, 0, sizeof(NAS_MML_PLMN_LIST_WITH_RAT_STRU));
    enPlmnSearchScene                   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    /* ��ȡ��ǰפ����������Ϣ */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* ֹͣ�ȴ�Epsע������Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    ulIsRrcSearchPlmn       = NAS_MMC_IsLmmSearchedAreaLostPlmn(pstLmmAreaLostMsg);
    pstLastAreaLostPlmnInfo = NAS_MMC_GetLastAreaLostPLmnInfoCtx_PlmnSelection();

    NAS_MMC_UpdateLastAreaLostPlmnWIthRatAndCnt(pstLastAreaLostPlmnInfo, &stCurPlmn.stPlmnId, stCurPlmn.enRat);

    /* �����Ƿ���й�history�� */
    if (VOS_TRUE == ulIsRrcSearchPlmn)
    {
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);
    }

    /* �ڵȴ�ע����ʱ�������NO RF���������򲻸��µ�ǰΪREGISTER״̬���ȴ���Դ
       ����ʱ�򣬿��Լ����������ڴ������Ͻ���ע�� */
    /* ���µ�ǰ���������״̬Ϊ��ע������ڴ��������У��������Ѵ����� */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                        NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                        pstPlmnSelectionListInfo);

    if (MMC_LMM_AREA_LOST_REASON_NO_RF == pstLmmAreaLostMsg->enAreaLostReason)
    {
        /* ���µ�ǰ����״̬ΪEXIT,��Դ�ָ������� */
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                        NAS_MMC_NET_STATUS_SEARCHED_EXIST,
                                        pstPlmnSelectionListInfo);

        /* �ظ�״̬��ʧ�� */
        NAS_MMC_ProcNoRfAreaLost_PlmnSelection(NAS_MML_GetCurrNetRatType());

        return VOS_TRUE;
    }

    /* ���·���״̬ */

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte,abort");
        /* �ظ�״̬��ѡ������� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        return VOS_TRUE;
    }

    if ( (NAS_MMC_AREA_LOST_SEARCH_MAX_NUM > NAS_MML_GetLastAreaLostPlmnCnt(pstLastAreaLostPlmnInfo))
      && (VOS_TRUE != ulIsRrcSearchPlmn) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte < 2");

        /* ��MM��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();
        NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
        NAS_MMC_UpdateRegStateSpecPlmnSearch();

        /* ��LMM����ָ������ */
        stDestPlmnList.ulPlmnNum = 1;
        stDestPlmnList.astPlmnId[0].enRat = stCurPlmn.enRat;
        stDestPlmnList.astPlmnId[0].stPlmnId.ulMcc  = stCurPlmn.stPlmnId.ulMcc;
        stDestPlmnList.astPlmnId[0].stPlmnId.ulMnc  = stCurPlmn.stPlmnId.ulMnc;

        NAS_MMC_SndLmmSpecPlmnSearchReq(&stDestPlmnList, VOS_FALSE, enPlmnSearchScene);

        /* ״̬��Ǩ�Ƶ�recamp״̬�� */
        /* ״̬Ǩ��NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE);

        /* ����������ʱ��TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte > 2");
        /* ����״̬���˳������Ϣ�����Ϊʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�ע����ʱMMC����LMM�ϱ���ϵͳ��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:LMM�ϱ���ϵͳ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��2��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��11��29��
    ��    ��   : w00176964
    �޸�����   : DTS2012042804167:֪ͨCBAģ�鵱ǰ����ģʽΪLTE
  3.��    ��   : 2012��12��20��
    ��    ��   : w00176964
    �޸�����   : DTS2012121906946:�յ�L��ϵͳ��Ϣת����LMM
 4. ��    ��   : 2013��1��19��
    ��    ��   : t00212959
    �޸�����   : DTS2012122900189:EPSע��״̬��ȫ��L�ϱ�
  5.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 �����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);



    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    /*�����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC*/
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        NAS_MMC_SndMsccSysInfo();

    }

    /* ת��MM/GMMϵͳ��Ϣ */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�ע����ʱMMC����MSCC�����ָ��������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;

    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �����û�ָ��������Ϣ�����µ�ǰ����������Ϊ�ֶ�ģʽ */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                        pstUserSelReqMsg->enAccessMode);

    /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* �����û�ָ�������������³�ʼ��ѡ���б� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* ���û�ָ�����뼼��������(Ҳ�ǵ�ǰ����)����Ϊ������ע������ظ�ע�� */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause, enPsRegCause))
    {
        return VOS_TRUE;
    }

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ״̬Ǩ�Ƶ�NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�ע����ʱMMC����MSCC�����SYSCFG������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֱ�ӵ���syscfg���״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�ע����ʱ����SYSCFG״̬�����صĽ��
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ״̬���в���Ҫ��SYSCFG״̬��������д���ֱ�ӷ��� */
    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�ע����ʱ����MSCC��IMS VOICE�����õ���Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��7��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��4��23��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU                     *pstImsVoiceNtf = VOS_NULL_PTR;
    VOS_UINT8                                               ucWaitRegRsltFlag;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_PLMN_WITH_RAT_STRU                              stReCampLtePlmn;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnSelection();
    pstImsVoiceNtf      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ����ڵȴ�PS��ע����������ȴ�PSע���� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_PS == (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_PS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceNtf->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    /* L��Aע��eps only�ɹ�����#16����disable lte����gu�����κ�����,��A����ע�ᱻ��#16��һ�ξ���״̬�����Ϊ�ɹ���
      ���º����յ�5�α�����disable lte��gu����������˷�������Ҫ�ж����additionalActionΪreg attemptֱ��return*/
    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(),
                                                          NAS_MMC_GetPsRegAdditionalAction_PlmnSelection());

    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* ͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* disable lteԭ����MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOWʱ��
       ����������ڽ�ֹ���뼼����������ɾ�� */
    if (MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW != NAS_MML_GetDisableLteReason())
    {
        stReCampLtePlmn.enRat    = NAS_MML_NET_RAT_TYPE_LTE;
        PS_MEM_CPY(&(stReCampLtePlmn.stPlmnId),
               NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection(),
               sizeof(stReCampLtePlmn.stPlmnId));
        NAS_MML_DeleteSpecDisabledPlmnWithValidPeriodInPlmnList(&stReCampLtePlmn);
    }

    if (VOS_FALSE == NAS_MMC_IsAdditionalActionTrigerPlmnSrch(enAdditionalAction))
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /*  ��������������ӣ�Ǩ�Ƶ��ȴ������ͷ�״̬  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ����פ��LTEʱ������״̬�ϱ� */
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));

    /* �ظ�״̬���˳�ʧ�� */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
    {
        /* ���Disable Lȫ�ֱ�����־ */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�L�����ͷŵĹ������յ��˳�״̬��������
 �������  : ulEventType:��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU             *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* ������������û�����Ĺػ�����ֱ���˳��������ͷŽ��״̬�� */
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ) == pstAbortMsg->ulEventType)
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����Abort��־, �������ͷź����quit */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�L�����ͷŵĹ������յ�LMM�ϱ���Status Ind��Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    /* ����LMM������״̬ */
    NAS_MML_UpdateEpsConnectionStatus(pstLmmStatusIndMsg->ulConnState);

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* �Ƿ���Ҫ Abort״̬�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* ���ϲ�״̬��ָʾѡ��ABORT */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����פ��LTEʱ������״̬�ϱ� */
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �ظ�״̬���˳�ʧ�� */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
    {
        /* ���Disable Lȫ�ֱ�����־ */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitEpsRelIndExpired_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�L�����ͷŵĹ����еȴ������ͷŶ�ʱ����ʱ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitEpsRelIndExpired_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsRelIndExpired_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte ENTERED");

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection() )
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����פ��LTEʱ������״̬�ϱ� */
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
    NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �ظ�״̬���˳�ʧ�� */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
    {
        /* ���Disable Lȫ�ֱ�����־ */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);
    }

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�L�����ͷŵĹ�����MMC����MSCC�����ָ��������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU                          *pstUserSelReqMsg  = VOS_NULL_PTR;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSrchList   = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;

    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstUserSelReqMsg    = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �����û�ָ��������Ϣ�����µ�ǰ����������Ϊ�ֶ�ģʽ */
    NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection((NAS_MML_PLMN_ID_STRU*)(&pstUserSelReqMsg->stPlmnId),
                                                        pstUserSelReqMsg->enAccessMode);

    /* ��ȡѡ���б� */
    pstPlmnSrchList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* �����û�ָ�������������³�ʼ��ѡ���б� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  pstPlmnSrchList);

    /* ���û�ָ�����뼼��������(Ҳ�ǵ�ǰ����)����Ϊ������ע������ظ�ע�� */
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(NAS_MMC_GetUserSpecPlmnId(),
                                                   NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                                   pstPlmnSrchList);

    enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

    if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause, enPsRegCause))
    {
        return VOS_TRUE;
    }

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ״̬Ǩ�Ƶ�NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�L�����ͷŵĹ�����MMC����MSCC�����SYSCFG������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֱ�ӵ���syscfg���״̬�� */
    NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_SYSCFG);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�L�����ͷŵĹ����д���SYSCFG״̬�����صĽ��
 �������  : ulEventType:��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ״̬���в���Ҫ��SYSCFG״̬��������д���ֱ�ӷ��� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�L�����ͷŵĹ���������detach�ĵĴ���
 �������  : ulEventType:��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��1��11��
   ��    ��   : w00176964
   �޸�����   : DTS2013010706662:��������EPLMN�߼�����λ��

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_IND_STRU                                *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));
    pstDetachMsg        = (LMM_MMC_DETACH_IND_STRU*)pstMsg;

    /* ����DETACH��Ϣ��������һ������ */
    NAS_MMC_ProcLmmDetachInd(pstDetachMsg, &enCsAdditionalAction, &enPsAdditionalAction);

    /*����EPS����һ���Ķ�������*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /*����CS����һ���Ķ�������*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        NAS_MMC_SndOmEquPlmn();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte
 ��������  : CS/PS mode 1����פ��Lteģ�ȴ�L�����ͷŵĹ������û�detach CNF�ĵĴ���
 �������  : ulEventType:��Ϣ����
             pstMsg: ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣδ���
             VOS_TRUE:������Ϣ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_DETACH_CNF_STRU            *pstDetachCnfMsg = VOS_NULL_PTR;

    pstDetachCnfMsg        = (LMM_MMC_DETACH_CNF_STRU*)pstMsg;

    /* ���detach������Ǽ�Ȩ���ܣ�����Ҫ��״̬����Ԥ�����оͿ��Դ��� */
    if ( MMC_LMM_DETACH_RSLT_AUTH_REJ != pstDetachCnfMsg->ulDetachRslt)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsConnRelInd: Unexpected detach result!");

        return VOS_TRUE;
    }

    /*����EPS����һ���Ķ�������*/
    NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);

    /*����CS����һ���Ķ�������*/
    NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL);

    return VOS_TRUE;
}


/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitMsccRegReq
 ��������  : �ȴ�MSCCע������������յ�ID_LMM_MMC_SYS_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnId;
    LMM_MMC_SYS_INFO_IND_STRU                              *pstLmmSysInfoMsg    = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo    = VOS_NULL_PTR;

    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* ����ϵͳ��Ϣ��PLMNID������ѡ���б��и�����״̬Ϊ���� */
    pstLmmSysInfoMsg  = (LMM_MMC_SYS_INFO_IND_STRU*)pstMsg;
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(&(pstLmmSysInfoMsg->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]), &(stPlmnId.stPlmnId));

    stPlmnId.enRat           = NAS_MML_NET_RAT_TYPE_LTE;
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stPlmnId, NAS_MMC_NET_STATUS_SEARCHED_EXIST, pstPlmnSelectionListInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitMsccRegReq
 ��������  : �ȴ�MSCCע������������յ�ID_LMM_MMC_SUSPEND_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��״̬�����������ϵͳ��ѡ���ظ�LMM����ʧ�� */
    NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitMsccRegReq
 ��������  : �ȴ�MSCCע������������յ�ID_LMM_MMC_AREA_LOST_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���ý����פ��״̬Ϊδפ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    return VOS_TRUE;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitLmmPlmnSearchCnf
 ��������  :�ȴ�Lģ�ϱ�����������յ�ID_MSCC_MMC_CL_ASSOCIATED_INFO_NTF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������

 �޸���ʷ     :
 1.��    ��   : 2015��9��11��
   ��    ��   : y00346957
   �޸�����   : DTS2015070910885 ���ӵ�ǰ������plmn�Ƿ������ѵ��ж�
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat;

    pstPlmnWithRat = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;

    if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
        NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitLmmPlmnSearchCnf:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                             stPlmnId.ulMcc, stPlmnId.ulMnc);

        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

        /* ֪ͨLMMֹͣ���� */
        NAS_MMC_SndLmmPlmnSrchStopReq();

        /*Ǩ�Ƶ��ȴ�ֹͣ����ȷ��״̬������������ʱ��*/
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF);

        NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccLteSysPriClassInfoInd_PlmnSelection_WaitEpsRegRsltInd
 ��������  :�ȴ�Lģ�ϱ�ע�������յ�ID_MSCC_MMC_MSPL_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������

 �޸���ʷ     :
 1.��    ��   : 2015��9��11��
   ��    ��   : y00346957
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitEpsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat;

    pstPlmnWithRat = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;

    if (VOS_TRUE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
    {
        return VOS_TRUE;
    }

    NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_RcvMsccCLAssociatedInfoNtf_PlmnSelection_WaitEpsRegRsltInd:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                         stPlmnId.ulMcc, stPlmnId.ulMnc);

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
         /* ���������ͷű�־ */
        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_TRUE);

        /* ���������ͷ����� */
        NAS_MMC_SndLmmRelReq();

        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ���¸�plmn */
    NAS_MMC_SearchNextPlmn_PlmnSelection();

    return VOS_TRUE;
}
#endif


#endif  /* (FEATURE_ON == FEATURE_LTE) */

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextSearchPlmn_PlmnSelection
 ��������  : ��ȡҪѡ������缰����뼼��
 �������  : ��
 �������  : pstDestPlmn
 �� �� ֵ  : VOS_UINT32 VOS_TRUE :��ȡ�ɹ�
                        VOS_FALSE:��ȡʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��09��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559:SIM��ʱ���ó�LTE only����ȥ��Lģ������ʱ����ʱ����Lģ
 3.��    ��   : 2012��12��27��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:���USIM��GSM��ֹ���룬��ѡ��GSM����
 4.��    ��   :2013��8��21��
   ��    ��   :z00161729
   �޸�����   :DTS2013081607507:�������������к�̨����·�at+cops=0��mmc�жϷ���������ͣ��ϵ�ǰ���������������¿����ٶ���
 5.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 6.��    ��   : 2014��2��13��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 7.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�   ���Ӷ�HISTORY�����Ĵ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{

    /* ========================== HISTORY��������ʼ ========================== */
    if (VOS_TRUE == NAS_MMC_IsNeedHistoryPlmnSearch_PlmnSelection())
    {
        /* ����HISTORY�ѵ�����,�ҵ��������HISTORY�� */
        if (VOS_TRUE == NAS_MMC_GetNextHistorySearchPlmn_PlmnSelection(pstDestPlmn))
        {
            return VOS_TRUE;
        }
    }
    /* ========================== HISTORY����������� ========================== */


    /* ========================== Pref Band��������ʼ ========================== */
    if (VOS_TRUE == NAS_MMC_IsNeedPrefBandPlmnSearch_PlmnSelection())
    {
        /* ����Pref Band�ѵ�����,�ҵ��������Pref Band�� */
        if (VOS_TRUE == NAS_MMC_GetNextPrefBandSearchPlmn_PlmnSelection(pstDestPlmn))
        {
            return VOS_TRUE;
        }
    }

    /* ========================== Pref Band����������� ========================== */

    if (VOS_TRUE == NAS_MMC_IsNeedSpecPlmnSearch_PlmnSelection())
    {
        /* ����������Ҫ����ȫBAND����������  */
        if (VOS_TRUE == NAS_MMC_GetNextSpecSearchPlmn_PlmnSelection(pstDestPlmn))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextSearchPlmnFail_PlmnSelection
 ��������  : ��ȡ��һ��Ҫѡ�������ʧ�ܴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����
 3.��    ��   : 2014��5��21��
   ��    ��   : w00167002
   �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷�������������.ָ�������ϱ����������
                ѡ�����ͣ���������ѡ������һ�¡�
*****************************************************************************/
VOS_VOID NAS_MMC_GetNextSearchPlmnFail_PlmnSelection(VOS_VOID)
{
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* ������û�ָ�����������ϲ�ظ�����ʧ�� */
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/


        /*���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬��*/
         NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

#if   (FEATURE_ON == FEATURE_LTE)
        /* ��LMM�����û���������֪ͨ */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {

            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif
    }

#if   (FEATURE_ON == FEATURE_LTE)
    /* �ж��Ƿ���Ҫ����פ��LTE���� */
    if (VOS_TRUE == NAS_MMC_IsReCampLtePlmnValid_PlmnSelection())
    {
        NAS_MMC_ReCampLte_PlmnSelection();
    }
    else
#endif
    {
        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* �˳����״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextHistorySearchPlmn_PlmnSelection
 ��������  : ��ȡҪѡ���HISTORY���������缰����뼼��
 �������  : ��
 �������  : pstDestPlmn
 �� �� ֵ  : VOS_UINT32 VOS_TRUE :��ȡ�ɹ�
                        VOS_FALSE:��ȡʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ����
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextHistorySearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stPrioRatList;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulUserSpecPlmnSearch;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

    enCurrentFsmId       = NAS_MMC_GetCurrFsmId();

    if (enCurrentFsmId >= NAS_FSM_BUTT )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    ulCurrentEventType   = NAS_MMC_GetCurrFsmEventType();

    /* ��ȡ�Ƿ��û�ָ������ */
    ulUserSpecPlmnSearch = NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType);

    /* ��ȡ��ǰ���뼼�����ȼ���Ϣ */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();


    /* HISTORY��������Ҫɾ����ǰ��HISTORY�������Ľ��뼼�� */
    PS_MEM_SET(&stPrioRatList, 0X00, sizeof(stPrioRatList));

    for (i = 0 ; i < pstPrioRatList->ucRatNum; i++)
    {
        if (VOS_FALSE == NAS_MMC_GetHistorySearchedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]))
        {
            stPrioRatList.aucRatPrio[stPrioRatList.ucRatNum] = pstPrioRatList->aucRatPrio[i];
            stPrioRatList.ucRatNum ++;
        }
    }

    /* ��ȡѡ���б���������ǰ���״̬Ϊδ�����������������ڵ����� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn(pstDestPlmn, &stPrioRatList,
                                              ulUserSpecPlmnSearch, pstPlmnSelectionList))
    {
        NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(pstDestPlmn);
        NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_HISTORY);

        /* ��ά�ɲ� */
        NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo(NAS_MMC_GetPlmnSelectionCtx_PlmnSelection());

        return VOS_TRUE;
    }

    /* û�ҵ���һ��HISTORY�ѵ����磬����VOS_FALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextPrefBandSearchPlmn_PlmnSelection
 ��������  : ��ȡ��һ����Ҫpref band�ѵ�����
 �������  : NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��2��23��
    ��    ��   : z00359541
    �޸�����   : DTS2016020503116:����ȫƵ����ʱ������ǰפ��С���Ĺ�������������
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextPrefBandSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulUserSpecPlmnSearch;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;
#endif


    enCurrentFsmId       = NAS_MMC_GetCurrFsmId();
    if (enCurrentFsmId >= NAS_FSM_BUTT )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType   = NAS_MMC_GetCurrFsmEventType();

    /* ��ȡ�Ƿ��û�ָ������ */
    ulUserSpecPlmnSearch = NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType);

    /* ��ȡ��ǰ���뼼�����ȼ���Ϣ */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* ��ȡѡ���б���������ǰ���״̬Ϊδ�����������������ڵ����� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn(pstDestPlmn, pstPrioRatList,
                                              ulUserSpecPlmnSearch, pstPlmnSelectionList))
    {
        NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(pstDestPlmn);

        NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND);

        return VOS_TRUE;
    }

    /* �����ǰΪ�Զ�ѡ�� */
    if (VOS_TRUE == NAS_MMC_IsNeedSearchAvailPlmn_PlmnSelection())
    {
        /* ��SYSCFG���õĽ��뼼�����ȼ��ж��Ƿ���ĳ�����뼼��δ����ȫƵ������
           ����У�����VOS_TRUE,����ý��뼼����ȫF��Ч����,ָʾ���������,
           ���������ʧ��ʱ�����һ��ȫƵ���� */
        for (i = 0; i < pstPrioRatList->ucRatNum; i++)
        {
            /* �����жϣ����RAT����ֹ�Ļ�������Ҫ��RAT */
            if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(pstPrioRatList->aucRatPrio[i]))
            {
                continue;
            }

#if (FEATURE_ON == FEATURE_LTE)
            enSimType = NAS_MML_GetSimType();

            /* ��ȡLTE����״̬ */
            enLCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

            /* ������������,����Ҫ����LTE������:
                1)��ǰ����Ľ��뼼��ΪL�ҵ�ǰPS����Ч
                2)��ǰ����Ľ��뼼��ΪL�ҵ�ǰDISABLE LTE
                3)������ΪSIM��:��Ӧ�ĳ���Ϊ:SIM��ʱ���ó�LTE only����ȥ��Lģ������ʱ����ʱ����Lģ
            */
            if (((VOS_FALSE                             == NAS_MML_GetSimPsRegStatus())
              || ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLCapabilityStatus)
               || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLCapabilityStatus))
              ||(NAS_MML_SIM_TYPE_SIM == enSimType))
             && (NAS_MML_NET_RAT_TYPE_LTE == pstPrioRatList->aucRatPrio[i]))
            {
                continue;
            }
#endif
            /* ���USIM��GSM��ֹ���룬��ѡ��GSM���� */
            if ( (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
              && (NAS_MML_NET_RAT_TYPE_GSM == pstPrioRatList->aucRatPrio[i]) )
            {
                continue;
            }

            /* ���β�������֧�ֵĽ��뼼�� */
            if (VOS_FALSE == NAS_MMC_GetAllBandSearch_PlmnSelection(pstPrioRatList->aucRatPrio[i]))
            {
                /* ��ȡ��ǰפ��С���Ĺ������������� */
                pstDestPlmn->stPlmnId.ulMcc = NAS_MMC_GetCountryCode_PlmnSelection();
                pstDestPlmn->stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
                pstDestPlmn->enRat          = pstPrioRatList->aucRatPrio[i];

                NAS_NORMAL_LOG3(WUEPS_PID_MMC, "NAS_MMC_GetNextPrefBandSearchPlmn_PlmnSelection: Dest PLMN MCC,MNC,RAT",
                    pstDestPlmn->stPlmnId.ulMcc,
                    pstDestPlmn->stPlmnId.ulMnc,
                    pstDestPlmn->enRat);
                
                NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(pstDestPlmn);

                NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND);

                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNextSpecSearchPlmn_PlmnSelection
 ��������  : ��ȡҪѡ���ȫƵ��ָ���ѵ����缰����뼼��
 �������  : ��
 �������  : pstDestPlmn
 �� �� ֵ  : VOS_UINT32 VOS_TRUE :��ȡ�ɹ�
                        VOS_FALSE:��ȡʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��09��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559:SIM��ʱ���ó�LTE only����ȥ��Lģ������ʱ����ʱ����Lģ
 3.��    ��   : 2012��12��27��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:���USIM��GSM��ֹ���룬��ѡ��GSM����
 4.��    ��   :2013��8��21��
   ��    ��   :z00161729
   �޸�����   :DTS2013081607507:�������������к�̨����·�at+cops=0��mmc�жϷ���������ͣ��ϵ�ǰ���������������¿����ٶ���
 5.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 6.��    ��   : 2014��2��13��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 7.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸ģ���װ��ȡҪ������ȫBANDָ��������Ĵ���
 8.��    ��   : 2016��2��23��
   ��    ��   : z00359541
   �޸�����   : DTS2016020503116:����ȫƵ����ʱ������ǰפ��С���Ĺ�������������
*****************************************************************************/
VOS_UINT32 NAS_MMC_GetNextSpecSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulUserSpecPlmnSearch;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;
#endif


    NAS_MML_PLMN_ID_STRU                                    stPlmnId;

    PS_MEM_SET(&stPlmnId, 0x00, sizeof(NAS_MML_PLMN_ID_STRU));

    enCurrentFsmId       = NAS_MMC_GetCurrFsmId();
    if (enCurrentFsmId >= NAS_FSM_BUTT )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType   = NAS_MMC_GetCurrFsmEventType();

    /* ��ȡ�Ƿ��û�ָ������ */
    ulUserSpecPlmnSearch = NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType);

    /* ��ȡ��ǰ���뼼�����ȼ���Ϣ */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* ��ȡѡ���б���������ǰ���״̬Ϊδ�����������������ڵ����� */
    if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn(pstDestPlmn, pstPrioRatList,
                                              ulUserSpecPlmnSearch, pstPlmnSelectionList))
    {
        NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(pstDestPlmn);

        NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_SPEC);

        return VOS_TRUE;
    }

    /* �����ǰΪ�Զ�ѡ�� */
    /* Modified by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    if (VOS_TRUE == NAS_MMC_IsNeedSearchAvailPlmn_PlmnSelection())
    /* Modified by s00246516 for L-C��������Ŀ, 2014-01-28, End */
    {
        /* ��SYSCFG���õĽ��뼼�����ȼ��ж��Ƿ���ĳ�����뼼��δ����ȫƵ������
           ����У�����VOS_TRUE,����ý��뼼����ȫF��Ч����,ָʾ���������,
           ���������ʧ��ʱ�����һ��ȫƵ���� */
        for (i = 0; i < pstPrioRatList->ucRatNum; i++)
        {
            /* �����жϣ����RAT����ֹ�Ļ�������Ҫ��RAT */
            if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(pstPrioRatList->aucRatPrio[i]))
            {
                continue;
            }

#if (FEATURE_ON == FEATURE_LTE)
            enSimType = NAS_MML_GetSimType();

            /* ��ȡLTE����״̬ */
            enLCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

            /* ������������,����Ҫ����LTE������:
                1)��ǰ����Ľ��뼼��ΪL�ҵ�ǰPS����Ч
                2)��ǰ����Ľ��뼼��ΪL�ҵ�ǰDISABLE LTE
                3)������ΪSIM��:��Ӧ�ĳ���Ϊ:SIM��ʱ���ó�LTE only����ȥ��Lģ������ʱ����ʱ����Lģ
            */
            if (((VOS_FALSE                             == NAS_MML_GetSimPsRegStatus())
              || ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLCapabilityStatus)
               || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLCapabilityStatus))
              ||(NAS_MML_SIM_TYPE_SIM == enSimType))
             && (NAS_MML_NET_RAT_TYPE_LTE == pstPrioRatList->aucRatPrio[i]))
            {
                continue;
            }
#endif
            /* ���USIM��GSM��ֹ���룬��ѡ��GSM���� */
            if ( (VOS_TRUE == NAS_MML_GetGsmForbidFlg())
              && (NAS_MML_NET_RAT_TYPE_GSM == pstPrioRatList->aucRatPrio[i]) )
            {
                continue;
            }

            /* ���β�������֧�ֵĽ��뼼�� */
            if (VOS_FALSE == NAS_MMC_GetAllBandSearch_PlmnSelection(pstPrioRatList->aucRatPrio[i]))
            {
                /* ��ȡ��ǰפ��С���Ĺ������������� */
                pstDestPlmn->stPlmnId.ulMcc = NAS_MMC_GetCountryCode_PlmnSelection();
                pstDestPlmn->stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
                pstDestPlmn->enRat          = pstPrioRatList->aucRatPrio[i];

                stPlmnId.ulMcc  = pstDestPlmn->stPlmnId.ulMcc;
                stPlmnId.ulMnc  = pstDestPlmn->stPlmnId.ulMnc;

                /* ȫƵ��ȫf��lte����ʱ����clģʽ�£�����cl������Ϣ�����lte���粻����������ֱ�ӷ��� */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
                if (VOS_FALSE == NAS_MMC_IsCurrLtePlmnAllowSrchInCLMode(&stPlmnId))
                {
                    NAS_WARNING_LOG2(WUEPS_PID_MMC, "NAS_MMC_GetNextSpecSearchPlmn_PlmnSelection:WARNING: Current Lte Plmn is not Allowed Srch In CL Mode,ulMcc and ulMnc are",
                                                         pstDestPlmn->stPlmnId.ulMcc, pstDestPlmn->stPlmnId.ulMnc);

                    return VOS_FALSE;
                }
#endif

                NAS_NORMAL_LOG3(WUEPS_PID_MMC, "NAS_MMC_GetNextSpecSearchPlmn_PlmnSelection: Dest PLMN MCC,MNC,RAT",
                    pstDestPlmn->stPlmnId.ulMcc,
                    pstDestPlmn->stPlmnId.ulMnc,
                    pstDestPlmn->enRat);

                NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(pstDestPlmn);


                NAS_MMC_SetCurrSearchingType_PlmnSelection(NAS_MMC_PLMN_SEARCH_TYPE_SPEC);

                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcNoRf_PlmnSelection
 ��������  : ����ʧ��ԭ��ΪNO RF
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��22��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
                ��ѡ��״̬���£������ǰ����ʧ��ԭ��ΪNO RF,���˳�ѡ��״̬��������
                �����������д���

 2.��    ��   : 2013��3��29��
   ��    ��   : y00176023
   �޸�����   : DSDS GUNAS II��Ŀ:NO RF�������RRM����ע�ᣬֻ����GU������LTE����������NO RF

 3.��    ��   : 2014��5��21��
   ��    ��   : w00167002
   �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷�������������.ָ�������ϱ����������
                ѡ�����ͣ���������ѡ������һ�¡�

 4.��    ��   : 2014��6��28��
   ��    ��   : b00269685
   �޸�����   : DSDS GUNAS III��Ŀ�޸�
 5.��    ��   : 2015��05��26��
   ��    ��   : l00305157
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0
*****************************************************************************/
VOS_VOID NAS_MMC_ProcNoRf_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList     = VOS_NULL_PTR;

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* NO RFʧ�ܣ��豣�浱ǰ��ѡ��״̬���б���Ϣ */
    NAS_MMC_SetPlmnSelectionListType(NAS_MMC_BACKUP_PLMN_SELECTION_LIST);
    PS_MEM_CPY(NAS_MMC_GetHighPrioPlmnList(), pstPlmnSelectionList, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));


    /* ���Ӵ洢��ģʽ��HISTORY��������Ϣ���Ա���RF ��Դ���ú󣬼�������HISTORY���� */
    NAS_MMC_BackupNoRfHistorySearchedInfo_PlmnSelection();

    /* ��ά�ɲ⣬���ѡ���б���Ϣ */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionList);

    /* ����NO RF���ڱ����Ϣ */
    NAS_MML_SetCurrRatRfAvailFlg(enNasRat, VOS_FALSE);

    /* ��RRM����ע����Ϣ �˴������ظ�֪ͨRRMMͬһ��RAT��NO RF,RRM��֤�ܴ��� */
    NAS_MMC_RegisterRrmResourceNtf(enNasRat, RRM_PS_TASK_TYPE_NAS_SEARCH);

    /* ��MSCC֪ͨ��ǰNO RF��Ϣ */
    NAS_MMC_SndMsccRfAvailInd(VOS_FALSE);

    /* ���ϲ�״̬��ָʾѡ��ʧ��,���ն�������:����AVAILABLE��ʱ�� */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    /* �˳����״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcNoRfAreaLost_PlmnSelection
 ��������  : ѡ��״̬�����յ�area lost NO RF
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��7��4��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ProcNoRfAreaLost_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList     = VOS_NULL_PTR;

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    /* NO RFʧ�ܣ��豣�浱ǰ��ѡ��״̬���б���Ϣ */
    NAS_MMC_SetPlmnSelectionListType(NAS_MMC_BACKUP_PLMN_SELECTION_LIST);
    PS_MEM_CPY(NAS_MMC_GetHighPrioPlmnList(), pstPlmnSelectionList, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

    /* ��ά�ɲ⣬���ѡ���б���Ϣ */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionList);

    /* ���ϲ�״̬��ָʾѡ��ʧ��,���ն�������:����AVAILABLE��ʱ�� */
    NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

    /* �˳����״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_SndLmmSpecPlmnSearchReq_PlmnSelection
 ��������  : ��LMM��������������Ϣ
 �������  : pstDestPlmn    - ����plmn id
             ulUserSpecFlag - �û�ָ��������ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 2.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�ͨ����ʷƵ��֧��NCELL������
 3.��    ��   : 2014��3��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014031200137:��NV���Դ�ʱ���Զ�������������ʱ������״�����RPLMN�Ļ���
                ��Ҫ��HPLMN/EHPLMN��������㡣
 4.��    ��   : 2014��2��14��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 5.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸� ���Ӷ�HISTORY�ѵĴ���
 6.��    ��   : 2015��10��28��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:����pref band�ѵĴ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmSpecPlmnSearchReq_PlmnSelection(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag
)
{
    NAS_MMC_NCELL_SEARCH_INFO_STRU                         *pstNcellSearchInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstDestPlmn = VOS_NULL_PTR;

    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(stSndEquPlmnInfo));

    pstNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();
    enPlmnSearchScene  = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    pstDestPlmn = &(pstDestPlmnList->astPlmnId[0]);

    /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
    /* ncell�������� */
    if ((VOS_TRUE == NAS_MMC_IsInterPlmnSearch_PlmnSelection())
     && ((NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH == enPlmnSearchScene)
      || (NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL == enPlmnSearchScene)))
    {
        if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH == enPlmnSearchScene)
        {
            /* ����ncell������Чplmn����Ϊmodem1�ĵ�Чplmn+modem0��ЧEHPLMN+modem0��RPLMN */
            NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection(&stSndEquPlmnInfo, pstDestPlmn->enRat);
        }
        else
        {
            stSndEquPlmnInfo.ucEquPlmnNum = NAS_MML_MIN(NAS_MML_MAX_EQUPLMN_NUM, pstNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum);
            PS_MEM_CPY(stSndEquPlmnInfo.astEquPlmnAddr, pstNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr,
                       (stSndEquPlmnInfo.ucEquPlmnNum*sizeof(NAS_MML_PLMN_ID_STRU)));
        }

        /* ɾ����ֹ���� */
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmNcellSpecPlmnSearchReq(&pstNcellSearchInfo->stLteNcellInfo,
                                     &stSndEquPlmnInfo);

    }
    /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, End */
    else if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection())
    {
        /* ֪ͨL������ʷƵ��ָ���� */
        NAS_MMC_SndLmmHistoryPlmnSearchReq(pstDestPlmnList);
    }
    else if ( NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND == NAS_MMC_GetCurrSearchingType_PlmnSelection())
    {
        /* ֪ͨL����pref band�� */
        NAS_MMC_SndLmmPrefBandPlmnSearchReq(pstDestPlmnList, ulUserSpecFlag);
    }
    else
    {
        NAS_MMC_SndLmmSpecPlmnSearchReq(pstDestPlmnList, ulUserSpecFlag, enPlmnSearchScene);
    }

}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection
 ��������  : ����ncell����ʱ֪ͨ�����ĵ�Чplmn��Ϣ
 �������  : pstOutEplmnInfo - ��Чplmn��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�
                ͨ����ʷƵ��֧��NCELL����,ncell����ʱ����eplmnΪmodem1��Чplmn+modem0��ЧEHPLMN+modem0��RPLMN
 2.��    ��   : 2014��2��19��
   ��    ��   : s00217060
   �޸�����   : coverity����
 3.��    ��   : 2014��03��05��
   ��    ��   : z00161729
   �޸�����   : DTS2014030304758��ncell����Я���ĵ�Чplmn��Ϣ˳���Ż���modem0 rplmn����ehplmnǰ�棬��ֹehplmn�������µ�Чplmn ����������16ʹrplmn�޷�����
*****************************************************************************/
VOS_VOID NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection(
    NAS_MML_EQUPLMN_INFO_STRU          *pstOutEplmnInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    MSCC_MMC_PLMN_ID_STRU                astEquPlmnAddr[NAS_MSCC_PIF_MAX_EQUPLMN_NUM];
    NAS_MMC_NCELL_SEARCH_INFO_STRU     *pstNcellSearchInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucSndEplmnNum;
    NAS_MML_PLMN_ID_STRU                stRPlmnId;
    VOS_UINT32                          ulRplmnExistFlg;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstSimEHPlmnInfo = VOS_NULL_PTR;

    PS_MEM_SET(astEquPlmnAddr, 0, sizeof(astEquPlmnAddr));
    PS_MEM_SET(&stRPlmnId, 0, sizeof(stRPlmnId));
    ucSndEplmnNum      = 0;
    ulIndex            = 0;
    pstSimEHPlmnInfo   = NAS_MML_GetSimEhplmnList();
    ulRplmnExistFlg    = VOS_FALSE;
    pstNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();

    /* Modified by s00217060 for coverity����, 2014-02-19, begin */
    if (NAS_MML_MAX_EQUPLMN_NUM < pstNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum)
    {
        pstNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum  = NAS_MML_MAX_EQUPLMN_NUM;

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection:other modem eplmn num incorrect!");

    }

    /* ��Чplmn��Ϣ�м���modem1�ĵ�Чplmn��Ϣ */
    for (ulIndex = 0; ulIndex < pstNcellSearchInfo->stOtherModemEplmnInfo.ucEquPlmnNum; ulIndex++)
    {


        astEquPlmnAddr[ucSndEplmnNum].ulMcc = pstNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr[ulIndex].ulMcc;
        astEquPlmnAddr[ucSndEplmnNum].ulMnc = pstNcellSearchInfo->stOtherModemEplmnInfo.astEquPlmnAddr[ulIndex].ulMnc;
        ucSndEplmnNum++;
    }

    /* ��Чplmn��Ϣ�м���modem0��RPLMN��Ϣ */
#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == enRatType)
    {
        ulRplmnExistFlg = NAS_MML_GetLteRPlmn(&stRPlmnId);
    }
    else
#endif
    {
        ulRplmnExistFlg = NAS_MML_GetGURPlmn(&stRPlmnId);
    }

    if ((VOS_TRUE == ulRplmnExistFlg)
     && (ucSndEplmnNum < NAS_MSCC_PIF_MAX_EQUPLMN_NUM))
    {
        astEquPlmnAddr[ucSndEplmnNum].ulMcc = stRPlmnId.ulMcc;
        astEquPlmnAddr[ucSndEplmnNum].ulMnc = stRPlmnId.ulMnc;
        ucSndEplmnNum++;
    }

    if (NAS_MML_MAX_EHPLMN_NUM < pstSimEHPlmnInfo->ucEhPlmnNum)
    {
        pstSimEHPlmnInfo->ucEhPlmnNum   = NAS_MML_MAX_EHPLMN_NUM;

        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection:other modem ehplmn num incorrect!");
    }
    /* Modified by s00217060 for coverity����, 2014-02-19, end */

    /* ��Чplmn��Ϣ�м���modem0��EHPLMN��Ϣ */
    for (ulIndex = 0; ulIndex < pstSimEHPlmnInfo->ucEhPlmnNum; ulIndex++)
    {
        if (ucSndEplmnNum >= NAS_MSCC_PIF_MAX_EQUPLMN_NUM)
        {
            pstOutEplmnInfo->ucEquPlmnNum = ucSndEplmnNum;
            PS_MEM_CPY(pstOutEplmnInfo->astEquPlmnAddr, astEquPlmnAddr, sizeof(pstOutEplmnInfo->astEquPlmnAddr));
            return;
        }

        astEquPlmnAddr[ucSndEplmnNum].ulMcc = pstSimEHPlmnInfo->astEhPlmnInfo[ulIndex].stPlmnId.ulMcc;
        astEquPlmnAddr[ucSndEplmnNum].ulMnc = pstSimEHPlmnInfo->astEhPlmnInfo[ulIndex].stPlmnId.ulMnc;
        ucSndEplmnNum++;
    }

    pstOutEplmnInfo->ucEquPlmnNum = ucSndEplmnNum;
    PS_MEM_CPY(pstOutEplmnInfo->astEquPlmnAddr, astEquPlmnAddr, sizeof(pstOutEplmnInfo->astEquPlmnAddr));

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndAsSpecPlmnSearchReq_PlmnSelection
 ��������  : ��AS��������������Ϣ
 �������  : pstDestPlmn    - ����plmn id
             ulUserSpecFlag - �û�ָ��������ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
 2.��    ��   : 2014��1��26��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088��֧����ǿNCELL���������Modem1���ݹ�����������Ϣ�����ڵ�����£�
                ͨ����ʷƵ��֧��NCELL����,ncell����ʱ����eplmnΪmodem1��Чplmn+modem0��ЧEHPLMN+modem0��RPLMN
 3.��    ��   : 2014��3��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014031200137:��NV���Դ�ʱ���Զ�������������ʱ������״�����RPLMN�Ļ���
                ��Ҫ��HPLMN/EHPLMN��������㡣
 4.��    ��   : 2015��10��28��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:����pref band�ѵĴ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsSpecPlmnSearchReq_PlmnSelection(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
)
{
    NAS_MMC_NCELL_SEARCH_INFO_STRU                         *pstNcellSearchInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstDestPlmn = VOS_NULL_PTR;

    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(stSndEquPlmnInfo));

    pstNcellSearchInfo = NAS_MMC_GetNcellSearchInfo();
    enPlmnSearchScene  = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    pstDestPlmn        = &(pstDestPlmnList->astPlmnId[0]);

    if ((VOS_TRUE == NAS_MMC_IsInterPlmnSearch_PlmnSelection())
     && (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH == enPlmnSearchScene))
    {
        /* ����ncell������Чplmn����Ϊmodem1�ĵ�Чplmn+modem0��ЧEHPLMN+modem0��RPLMN */
        NAS_MMC_BuildNcellPlmnSearchEquPlmnInfo_PlmnSelection(&stSndEquPlmnInfo, pstDestPlmn->enRat);

        /* ɾ����ֹ���� */
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndAsNcellSpecPlmnSearchReq(&pstNcellSearchInfo->stTdsNcellInfo,
                                            &stSndEquPlmnInfo);
    }
    /* �жϵ�ǰ��Ҫ����HISTORY��������֪ͨ��������HISTORY�� */
    else if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection() )
    {
        NAS_MMC_SndAsHistoryPlmnSearchReq(pstDestPlmnList, pstForbRoamLaInfo);
    }
    else if ( NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND == NAS_MMC_GetCurrSearchingType_PlmnSelection() )
    {
        NAS_MMC_SndAsPrefBandPlmnSearchReq(pstDestPlmnList, pstForbRoamLaInfo);
    }
    else
    {
        NAS_MMC_SndAsSpecPlmnSearchReq(pstDestPlmnList, pstForbRoamLaInfo);
    }


}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAddEplmnInDestPlmnList_PlmnSelection
 ��������  : �ж��Ƿ���Ҫ��EHPLMN/HPLMN����Ŀ�������б�
 �������  : pstDestPlmn    - ����plmn id

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��3��21��
   ��    ��   : w00242748
   �޸�����   : �½�����
 2.��    ��   : 2014��11��19��
   ��    ��   : s00217060
   �޸�����   : DTS2014111002343:available timer��ʱ��������ʱ��EHPLMN/HPLMN
 3.��    ��   : 2/4/2015
   ��    ��   : W00176964
   �޸�����   : CDMA Iteration 10 Modfied
 4.��    ��   : 2015��6��5��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddEhplmnWhenSearchRplmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    VOS_UINT32                                              ulEventType;
    VOS_UINT8                                               ucSearchRplmnAndHplmnFlg;
    NAS_MMC_ENTRY_MSG_STRU                                 *pstEntryMsg    = VOS_NULL_PTR;
    MSCC_MMC_PLMN_SEARCH_REQ_STRU                          *pstMsccPlmnSearchReq = VOS_NULL_PTR;

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg              = NAS_MMC_GetCurrFsmMsgAddr();
    pstMsccPlmnSearchReq     = (MSCC_MMC_PLMN_SEARCH_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    enPlmnSearchScene                = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    pstPlmnSelectionList             = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    enPlmnType                       = NAS_MMC_GetPlmnTypeInPlmnSelectionList(pstDestPlmn, pstPlmnSelectionList);
    ulEventType                      = NAS_MMC_GetCurrFsmEventType();
    ucSearchRplmnAndHplmnFlg         = NAS_MMC_GetSearchRplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat);

    /* �ֶ�����ģʽ��8464 NV���Թر�ʱ������EHPLMN/HPLMN */
    if (VOS_FALSE == NAS_MMC_IsRPlmnFirstSearchWithHPlmn())
    {
        return VOS_FALSE;
    }

    /* Ŀ�����粻��RPLMNʱ������EHPLMN/HPLMN */
    if (NAS_MMC_PLMN_TYPE_RPLMN != enPlmnType)
    {
        return VOS_FALSE;
    }

    /* �ý��뼼������RPLMNʱ�Ѿ�����EHPLMN/HPLMN����״̬��ǰ�´���ȥ�ý��뼼�����ѵ�ʱ�򲻴�EHPLMN/HPLMN */
    if (VOS_TRUE == ucSearchRplmnAndHplmnFlg)
    {
        return VOS_FALSE;
    }

    /* �ϵ��һ�ο�������ʱ��EHPLMN/HPLMN */
    if ((ulEventType                      == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ))
     && (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstMsccPlmnSearchReq->enAcqReason))
    {
        return VOS_TRUE;
    }

    /* ����֮�󴥷�����ʱ��EHPLMN/HPLMN */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST == enPlmnSearchScene)
    {
        return VOS_TRUE;
    }

    /* available timer��ʱ��������ʱ��EHPLMN/HPLMN */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED == enPlmnSearchScene)
    {
        return VOS_TRUE;
    }

    /* available timer��ʱ����history����ʱ��EHPLMN/HPLMN */
    if ((NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH == enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH == enPlmnSearchScene))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedAddEhplmnWhenSearchRplmn_PlmnSelection: AV Timer triggered History or Prefband Srch, Add EHPLMN when searching");
        return VOS_TRUE;
    }


    return VOS_FALSE;
}




/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection
 ��������  : �ж��Ƿ���Ҫ��EHPLMN/HPLMN����Ŀ�������б�
 �������  : pstDestPlmn    - ����plmn id

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��9��30��
    ��    ��   : c00318887
    �޸�����   : �½�����

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MML_HPLMN_CFG_INFO_STRU                            *pstHplmnCfgInfo      = VOS_NULL_PTR;
    VOS_UINT8                                               ucSearchRplmnAndHplmnFlg;


    pstHplmnCfgInfo                     = NAS_MML_GetHplmnCfg();
    pstPlmnSelectionList                = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    enPlmnType                          = NAS_MMC_GetPlmnTypeInPlmnSelectionList(pstDestPlmn, pstPlmnSelectionList);
    ucSearchRplmnAndHplmnFlg            = NAS_MMC_GetSearchRplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat);

    /* NV���Թر�ʱ������EHPLMN/HPLMN */
    if (VOS_FALSE == pstHplmnCfgInfo->ucAddEhplmnWhenSrchHplmnFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(): ucAddEhplmnWhenSrchHplmnFlg is false");
        return VOS_FALSE;
    }

    /* �ý��뼼������RPLMNʱ�Ѿ�����EHPLMN/HPLMN������EHPLMN/HPLMN */
    if (VOS_TRUE == ucSearchRplmnAndHplmnFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(): ucSearchRplmnAndHplmnFlg is true");

        return VOS_FALSE;
    }

    /* ���Կ�ʱ������EHPLMN/HPLMN */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(): is test card");
        return VOS_FALSE;
    }

    /* Ŀ�����粻��HPLMNʱ������EHPLMN/HPLMN */
    if (NAS_MMC_PLMN_TYPE_HPLMN != enPlmnType)
    {
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(): PlmnType isnot home:", enPlmnType);
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetNoSearchedEhplmn_PlmnSelection
 ��������  : ��ȡ����״̬��û��������EHPLMN �б�
 �������  :
 �������  : pstDestEHPlmnInfo    - û��������EHPLMN �б�
 �� �� ֵ  : VOS_VOID

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��9��30��
   ��    ��   : c00318887
   �޸�����   : �½����� : DTS2015091700173

*****************************************************************************/
VOS_VOID NAS_MMC_GetNoSearchedEhplmn_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat,
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstDestEHPlmnInfo
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstEHPlmnInfo        = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MMC_NET_STATUS_ENUM_UINT8                           enNetStatus;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    VOS_UINT16                                              usConvertedSimRat;
    VOS_UINT8                                               ucLoop;
    VOS_UINT8                                               ucIndex             = 0;

    /* ��ȡEHPLMN */
    pstEHPlmnInfo                                           = NAS_MML_GetSimEhplmnList();
    pstPlmnSelectionList                                    = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    usConvertedSimRat                                       = NAS_MMC_ConvertNetRatToSimRat(enCurRat);

    pstDestEHPlmnInfo->enPLMNSelInd                         = pstEHPlmnInfo->enPLMNSelInd;
    pstDestEHPlmnInfo->enEHplmnPresentInd                   = pstEHPlmnInfo->enEHplmnPresentInd;
    pstDestEHPlmnInfo->enHplmnType                          = pstEHPlmnInfo->enHplmnType;

    PS_MEM_SET(&stPlmnWithRat, 0x0, sizeof(stPlmnWithRat));

    for (ucLoop = 0; ucLoop < NAS_MML_MIN(pstEHPlmnInfo->ucEhPlmnNum, NAS_MML_MAX_EHPLMN_NUM); ucLoop++)
    {
        /* Ehplmn�Ľ��뼼����֧�ֵ�ǰ���뼼�� */
        if (usConvertedSimRat != (usConvertedSimRat & pstEHPlmnInfo->astEhPlmnInfo[ucLoop].usSimRat))
        {
            continue;
        }

        stPlmnWithRat.stPlmnId.ulMcc    = pstEHPlmnInfo->astEhPlmnInfo[ucLoop].stPlmnId.ulMcc;
        stPlmnWithRat.stPlmnId.ulMnc    = pstEHPlmnInfo->astEhPlmnInfo[ucLoop].stPlmnId.ulMnc;
        stPlmnWithRat.enRat             = enCurRat;

        enNetStatus                     = NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(
                                                            &stPlmnWithRat,
                                                            pstPlmnSelectionList);

        if ( (NAS_MMC_NET_STATUS_NO_SEARCHED    == enNetStatus)
          || (NAS_MMC_NET_STATUS_SEARCHED_EXIST == enNetStatus) )
        {
            PS_MEM_CPY(&pstDestEHPlmnInfo->astEhPlmnInfo[ucIndex++],
                            &pstEHPlmnInfo->astEhPlmnInfo[ucLoop],
                            sizeof(NAS_MML_SIM_PLMN_WITH_RAT_STRU));
        }

    }
    pstDestEHPlmnInfo->ucEhPlmnNum          = ucIndex;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetSpecSceneSrchRplmnCarryEplmnFlag
 ��������  : ��ȡָ��������RPLMN�Ƿ���ҪЯ��EPLMN�ı�־
 �������  : enPlmnSearchScene��������
             bIsRoam �Ƿ�����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetSpecSceneSrchRplmnCarryEplmnFlag_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 enPlmnSearchScene,
    VOS_UINT8                             ucIsRoam
)
{
    NAS_MML_CARRY_EPLMN_WHEN_SRCH_RPLMN_CFG_STRU *pstCarryEplmnWhenSrchRplmnCfg;
    VOS_UINT8                                     ucRetVal;

    pstCarryEplmnWhenSrchRplmnCfg = NAS_MML_GetCarryEplmnWhenSrchRplmnCfg();

    /* ���Կ����� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        return VOS_FALSE;
    }

    /* ���Ż����عرյĳ��� */
    if (NAS_MML_CARRY_EPLMN_SWITCH_OFF == pstCarryEplmnWhenSrchRplmnCfg->enSwitchFlag)
    {
        return VOS_FALSE;
    }

    /* ���Ż�ֻ�����γ�������Ч������ʱ���ڷ����γ����� */
    if ((NAS_MML_CARRY_EPLMN_SWITCH_ON_FOR_ROAM == pstCarryEplmnWhenSrchRplmnCfg->enSwitchFlag)
     && (VOS_FALSE == ucIsRoam))
    {
        return VOS_FALSE;
    }

    /* �Ż������δ򿪲��Ҵ�ʱ�����γ����������Ż������η����ζ��򿪣�����ݳ���������ȷ���Ƿ���Ż� */
    switch(enPlmnSearchScene)
    {
    case NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSwitchOn;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAreaLost;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneSysCfgSet;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED:
    case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH:
    case NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneAvailableTimerExpired;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneDisableLte;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneCSFBServiceRej;
        break;

    case NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH:
        ucRetVal = pstCarryEplmnWhenSrchRplmnCfg->ucCarryEplmnSceneEnableLte;
        break;

    default:
        ucRetVal = VOS_FALSE;
        break;
    }

    return ucRetVal;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAddEplmnWhenSearchRplmn_PlmnSelection
 ��������  : �ж��Ƿ���Ҫ��EPLMN����Ŀ�������б�
 �������  : pstDestPlmn    - ����plmn id
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ��EPLMN����Ŀ�������б�
             VOS_FALSE:����Ҫ��EPLMN����Ŀ�������б�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��9��
   ��    ��   : z00161729
   �޸�����   : �½�����
 2.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve�޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddEplmnWhenSearchRplmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    VOS_UINT8                                               ucSearchRplmnAndEplmnFlg;
    VOS_UINT8                                               ucIsRoam;

    enPlmnSearchScene                = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    pstPlmnSelectionList             = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    enPlmnType                       = NAS_MMC_GetPlmnTypeInPlmnSelectionList(pstDestPlmn, pstPlmnSelectionList);
    ucSearchRplmnAndEplmnFlg         = NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection(pstDestPlmn->enRat);

    ucIsRoam = VOS_FALSE;

    if (VOS_FALSE == NAS_MML_ComparePlmnIdWithHplmn(&pstDestPlmn->stPlmnId))
    {
        ucIsRoam = VOS_TRUE;
    }

    /* csfb������gu��������rplmnʱ��ҪЯ��eplmn��Ϣ���������ٶ� */
    if ( (NAS_MMC_PLMN_TYPE_RPLMN == enPlmnType)
      && (VOS_FALSE == ucSearchRplmnAndEplmnFlg))
    {
        if  ((NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ == enPlmnSearchScene)
          && (NAS_MML_NET_RAT_TYPE_LTE != pstDestPlmn->enRat))
        {
            return VOS_TRUE;
        }

        if (VOS_TRUE == NAS_MMC_GetSpecSceneSrchRplmnCarryEplmnFlag_PlmnSelection(enPlmnSearchScene, ucIsRoam))
        {
            return VOS_TRUE;
        }

    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAddDplmnOfSameCountryWhenSearchDPlmn_PlmnSelection
 ��������  : �ж��Ƿ���Ҫ��DPLMN����Ŀ�������б�
 �������  : pstDestPlmn    - ����plmn id
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ��DPLMN����Ŀ�������б�
             VOS_FALSE:����Ҫ��DPLMN����Ŀ�������б�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��24��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedAddDplmnOfSameCountryWhenSearchDPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU            *pstDplmnNplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                   *pstPrioRatList       = VOS_NULL_PTR;

    /* ��ȡ��ǰ���뼼�����ȼ���Ϣ */
    pstPrioRatList                      = NAS_MML_GetMsPrioRatList();
    pstDplmnNplmnCfgInfo                = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    /* ���������Ż����ƹرղ����� */
    if (VOS_FALSE == NAS_MMC_GetRoamPlmnSelectionSortActiveFlg())
    {
        return VOS_FALSE;
    }

    /* �ֶ�ģʽ�������� */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return VOS_FALSE;
    }

    /* ��ǰû�н������������򲻴��� */
    if (VOS_FALSE == NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(pstPrioRatList))
    {
        return VOS_FALSE;
    }

    /* Ŀ�����粻��DPLMNʱ�������� */
    if (VOS_FALSE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(pstDestPlmn,
                           pstDplmnNplmnCfgInfo->usDplmnListNum, pstDplmnNplmnCfgInfo->astDPlmnList))
    {
        return VOS_FALSE;
    }

    /* ������������UPLMN->OPLMN->DPLMN->AVAILABLE��˳��ִ�е����Դ� */
    if (VOS_TRUE == NAS_MMC_GetSrchUOplmnPriorToDplmnFlg())
    {
        /* Ŀ��������UPLMNʱ�������� */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithUplmn(pstDestPlmn))
        {
            return VOS_FALSE;
        }

        /* Ŀ��������OPLMNʱ�������� */
        if (VOS_TRUE == NAS_MMC_ComparePlmnIdWithRatWithOplmn(pstDestPlmn))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedHistoryPlmnSearch_PlmnSelection
 ��������  : �ж��Ƿ���Ҫ����HISTROY����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����HISTORY����
            VOS_FALSE:����Ҫ����HISTORY����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : �½�����
 2.��    ��   : 2015��5��21��
   ��    ��   : l00305157
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0
 3.��    ��   : 2015��8��11��
   ��    ��   : z00161729
   �޸�����   : DTS2015061609419��L�±������������Ż�����history����ȫƵ��
 4.��    ��   : 2015��12��11��
   ��    ��   : w00176964
   �޸�����   : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedHistoryPlmnSearch_PlmnSelection(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    VOS_UINT8                                               ucIsOosPLmnSearchScene;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enSrchType;

    enSrchType = NAS_MMC_PLMN_SEARCH_TYPE_SPEC;

    if (VOS_TRUE == NAS_MMC_GetMsccTriggerPlmnSrchTypeInClMode_PlmnSelection(&enSrchType))
    {
        if (NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == enSrchType)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
#endif

    /* ��ȡ��ǰ���뼼�����ȼ���Ϣ */
    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    enPlmnSearchScene                   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if (NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE == enPlmnSearchScene)
    {
        enPlmnSearchScene               = NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection();
    }

    if (VOS_FALSE == NAS_MMC_IsSpecSearchSceneInNeedHistorySearchSceneTbl(enPlmnSearchScene))
    {
        return VOS_FALSE;
    }

    ucIsOosPLmnSearchScene  = NAS_MMC_IsOosPlmnSearchScene(enPlmnSearchScene);

    /* ��OOS��������ʱ�����history�����Ƿ�� */
    if ((VOS_FALSE == NAS_MMC_GetNonOosSceneHistorySearchActiveFlg())
     && (VOS_FALSE == ucIsOosPLmnSearchScene))
    {
        return VOS_FALSE;
    }

    /* OOS�������ý׶�history����Ϊ0����history�� */
    if ((VOS_FALSE == NAS_MMC_IsHistorySearchSupportInCurrPhase())
     && (VOS_TRUE  == ucIsOosPLmnSearchScene))
    {
        return VOS_FALSE;
    }

    /* �����NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ������������history��L */
    if ((VOS_TRUE == NAS_MML_GetCmServiceSetupFlg())
     || (NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ == enPlmnSearchScene))
    {
        NAS_MMC_SetHistorySearchedFlag_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, VOS_TRUE);
    }

    /* ��ǰ�����뼼���¶���HISTORY������������ҪHISTORY���� */
    if (VOS_TRUE == NAS_MMC_IsSpecRatListAllHistorySearched_PlmnSelection(pstPrioRatList))
    {
        return VOS_FALSE;
    }

    /* ��ǰ�����˳��������������������������Ĺ������磬����HISTORY���� */
    if (VOS_TRUE == NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(pstPrioRatList) )
    {
        return VOS_FALSE;
    }

    /* ��Ҫ����HISTORY���� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedPrefBandPlmnSearch_PlmnSelection
 ��������  : �ж��Ƿ���Ҫ����pref band����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����pref band����
            VOS_FALSE:����Ҫ����pref band����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��10��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��12��11��
   ��    ��   : w00176964
   �޸�����   : CL_MUTIMODE_OPTIMIZE����
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedPrefBandPlmnSearch_PlmnSelection(VOS_VOID)
{
    VOS_UINT8                                               ucIsOosPLmnSearchScene;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstNonOosCfg  = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enSrchType;

    enSrchType = NAS_MMC_PLMN_SEARCH_TYPE_SPEC;

    if (VOS_TRUE == NAS_MMC_GetMsccTriggerPlmnSrchTypeInClMode_PlmnSelection(&enSrchType))
    {
        if (NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND == enSrchType)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
#endif

    pstNonOosCfg        = NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg();
    enPlmnSearchScene   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if (NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE == enPlmnSearchScene)
    {
        enPlmnSearchScene               = NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection();
    }

    /* �Ƿ�Ϊpref band�������� */
    if (VOS_FALSE == NAS_MMC_IsSpecSearchSceneInNeedPrefBandSearchSceneTbl(enPlmnSearchScene))
    {
        return VOS_FALSE;
    }

    ucIsOosPLmnSearchScene  = NAS_MMC_IsOosPlmnSearchScene(enPlmnSearchScene);

    /* ��OOS��������ʱ�����prefband�����Ƿ�� */
    if ((VOS_FALSE == pstNonOosCfg->ucPrefBandActiveFlg)
     && (VOS_FALSE == ucIsOosPLmnSearchScene))
    {
        return VOS_FALSE;
    }

    /* area lostʱ��Ҫ����NV�ж���Ҫpref band�ѻ���spec�� */
    if ((NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST == enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_PREF_BAND != pstNonOosCfg->enSearchTypeAfterHistoryInAreaLostScene))
    {
        return VOS_FALSE;
    }

    /* ��Ҫ����pref band���� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSpecPlmnSearch_PlmnSelection
 ��������  : �Ƿ����spec����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��28��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��11��
    ��    ��   : w00176964
    �޸�����   : CL_MUTIMODE_OPTIMIZE����

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSpecPlmnSearch_PlmnSelection(VOS_VOID)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstNonOosCfg  = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MMC_PLMN_SEARCH_TYPE_ENUM_UINT32                    enSrchType;

    enSrchType = NAS_MMC_PLMN_SEARCH_TYPE_SPEC;

    if (VOS_TRUE == NAS_MMC_GetMsccTriggerPlmnSrchTypeInClMode_PlmnSelection(&enSrchType))
    {
        if (NAS_MMC_PLMN_SEARCH_TYPE_SPEC == enSrchType)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
#endif

    pstNonOosCfg        = NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg();
    enPlmnSearchScene   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if (NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE == enPlmnSearchScene)
    {
        enPlmnSearchScene               = NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection();
    }

    /* �Ҳ���HISTORY���磬���ֻ��Ҫ����HISTORY�ѣ�����Ҫ����һ������ */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH == enPlmnSearchScene)
    {
        return VOS_FALSE;
    }

    /* available��ʱ֮�������������ֻ��Ҫ����Pref Band�ѣ�����Ҫ����һ������ */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_PREFBAND_PLMN_SEARCH == enPlmnSearchScene)
    {
        return VOS_FALSE;
    }

    /* area lostʱ��Ҫ����NV�ж���Ҫpref band�ѻ���spec�� */
    if ((NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST == enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_SPEC != pstNonOosCfg->enSearchTypeAfterHistoryInAreaLostScene))
    {
        return VOS_FALSE;
    }

    /* ��Ҫ����spec���� */
    return VOS_TRUE;
}


/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAddHplmnWhenSeachDplmn_PlmnSelection
 ��������  : �ж��Ƿ���Ҫ��EPLMN����Ŀ�������б�
 �������  : pstDestPlmn    - ����plmn id
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ��EPLMN����Ŀ�������б�
             VOS_FALSE:����Ҫ��EPLMN����Ŀ�������б�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��18��
   ��    ��   : c00318887
   �޸�����   : �½�����
 2.��    ��   : 2015��7��30��
   ��    ��   : c00318887
   �޸�����   : ����ROAM_PLMN_SELECTION_OPTIMIZE_2.0 ����

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAddEhplmnWhenSeachDplmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDplmnNplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucSearchDplmnAndHplmnFlg;

    /* Modified by  for c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-7-30, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList       = VOS_NULL_PTR;

    /* ��ȡ��ǰ���뼼�����ȼ���Ϣ */
    pstPrioRatList                      = NAS_MML_GetMsPrioRatList();
    pstDplmnNplmnCfgInfo                = NAS_MMC_GetDPlmnNPlmnCfgInfo();
    ucSearchDplmnAndHplmnFlg            = NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat);

    /* ���������Ż����ƹرղ����� */
    if (VOS_FALSE == NAS_MMC_GetRoamPlmnSelectionSortActiveFlg())
    {
        return VOS_FALSE;
    }



    /* ��ǰû�н������������򲻴��� */
    if (VOS_FALSE == NAS_MMC_IsSpecRatListRoamSorted_PlmnSelection(pstPrioRatList) )
    {
        return VOS_FALSE;
    }


    /* Ŀ�����粻��DPLMNʱ������EHPLMN/HPLMN */
    if (VOS_FALSE == NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(pstDestPlmn,
                           pstDplmnNplmnCfgInfo->usDplmnListNum, pstDplmnNplmnCfgInfo->astDPlmnList))
    {
        return VOS_FALSE;
    }


    /* �Զ�ģʽ��Я��HPLMN */
    if ( (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
      && (VOS_FALSE == ucSearchDplmnAndHplmnFlg))
    {
        return VOS_TRUE;
    }
    /* Modified by  for c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-7-30, end */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAddHplmnWhenSeachDplmn_PlmnSelection
 ��������  : ������Ҫ��EPLMN/hplmn����Ŀ�������б�
 �������  : pstDestPlmn    - ����plmn id
 �������  : pstDestPlmnList --���� EPLMN/hplmn ��������б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��7��30��
   ��    ��   : c00318887
   �޸�����   : �½�����
 2.��    ��   : 2015��9��30��
   ��    ��   : c00318887
   �޸�����   : DTS2015091700173
*****************************************************************************/
VOS_VOID NAS_MMC_BuildDestPlmnListWhenSearchPlmn_PlmnSelection(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     *pstDestPlmnList,
    NAS_MML_PLMN_WITH_RAT_STRU          *pstDestPlmn
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU        stEHPlmnInfo;

    if ( VOS_TRUE == NAS_MMC_IsNeedAddEhplmnWhenSearchRplmn_PlmnSelection(pstDestPlmn) )
    {
        NAS_MMC_AddEHPlmnInDestPlmnList(pstDestPlmnList, NAS_MML_GetSimEhplmnList());


        /* ��HISTORYʱ���������������������Լ���ȫƵ��ָ���� */
        if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY != NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetSearchRplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat, VOS_TRUE);
        }
    }
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, begin */
    else if (VOS_TRUE == NAS_MMC_IsNeedAddEhplmnWhenSeachDplmn_PlmnSelection(pstDestPlmn))
    {
        NAS_MMC_AddEHPlmnInDestPlmnList(pstDestPlmnList, NAS_MML_GetSimEhplmnList());

        if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY != NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat, VOS_TRUE);
        }
    }
    else if ( VOS_TRUE == NAS_MMC_IsNeedAddEhplmnWhenSearchHplmn_PlmnSelection(pstDestPlmn) )
    {
        PS_MEM_SET(&stEHPlmnInfo, 0x0, sizeof(NAS_MML_SIM_EHPLMN_INFO_STRU));

        NAS_MMC_GetNoSearchedEhplmn_PlmnSelection(pstDestPlmn->enRat, &stEHPlmnInfo);

        NAS_MMC_AddEHPlmnInDestPlmnList(pstDestPlmnList, &stEHPlmnInfo);

        if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY != NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetSearchRplmnAndHplmnFlg_PlmnSelection(pstDestPlmn->enRat, VOS_TRUE);
        }

    }
    else
    {
    }
    /* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */


    if (VOS_TRUE == NAS_MMC_IsNeedAddEplmnWhenSearchRplmn_PlmnSelection(pstDestPlmn))
    {
        NAS_MMC_AddEPlmnInDestPlmnList(pstDestPlmnList);

        if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY != NAS_MMC_GetCurrSearchingType_PlmnSelection())
        {
            NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection(pstDestPlmn->enRat, VOS_TRUE);
        }
    }

    if (VOS_TRUE == NAS_MMC_IsNeedAddDplmnOfSameCountryWhenSearchDPlmn_PlmnSelection(pstDestPlmn))
    {
        NAS_MMC_AddDplmnInDestPlmnList(pstDestPlmn, pstDestPlmnList);
    }
}

/* Modified by c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-5-18, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection
 ��������  : ���������LMM��������������Ϣ
 �������  : stDestPlmn
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��11��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:����ֹ����λ������Ϣ��Ϊ�������ݽ�������
                ����㷢�ʹ�FORB ROAM LAS����
 3.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 4.��    ��   : 2012��3��17��
   ��    ��   : w00176964
   �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:����LTE�������ι��ܶ���
 5.��    ��   : 2012��12��11��
   ��    ��   : l00167671
   �޸�����   : DTS2012121802573, TQE����
 6.��    ��   : 2013��1��15��
   ��    ��   : s00217060
   �޸�����   : for DSDA GUNAS C CORE:�ȴ�WAS�������ظ���ʱ�����ȷ�װ�ɺ���
 7.��    ��   : 2013��01��23��
   ��    ��   : s00217060
   �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
 8.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 9.��    ��   : 2013��12��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
10.��    ��   : 2014��3��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014031200137:��NV���Դ�ʱ���Զ�������������ʱ������״�����RPLMN�Ļ���
                ��Ҫ��HPLMN/EHPLMN��������㡣
11.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
12.��    ��   : 2014��9��9��
   ��    ��   : z00161729
   �޸�����   : DTS2014082807343:csfb������gu��mmc�����������rplmn+eplmn���������������T303��ʱ����ʧ�ܳ���
13.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�

13.��    ��   : 2015��02��11��
   ��    ��   : w00167002
   �޸�����   : DTS2015021000324:��ǰ��DSDS˫���У�GSM���������ܲ���NAS ����NO RF,��ô
                NAS������ʱ����ʱ�����ϱ��޷����ˡ��޸�Ϊ�ӳ�NAS��ʱ��ʱ����
14.��    ��   : 2015��6��17��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0,��HISTORY����ʱ�򣬲�����������
                HPLMN/EPLMN.
15.��    ��   : 2015-5-18
   ��    ��   : c00318887
   �޸�����   : DPlmn���ݺ����Ƚ���HPLMN
16.��    ��   : 2015��10��28��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0:����Pref band�ѵĴ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{

    VOS_UINT32                                              ulUserSpecPlmnSearch;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU                stForbRoamLaInfo;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                        *pstForbPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulWaitWasPlmnSrchCnfTimerLen;
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                         stDestPlmnList;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    NAS_MML_RAT_CAPABILITY_STATUS_ENUM_UINT8                enLteForbiddenStatus;

    enLteForbiddenStatus = NAS_MML_GetLteForbiddenStatusFlg();

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    ulWaitWasPlmnSrchCnfTimerLen = NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen();
    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* ��ȡ�Ƿ��û�ָ������ */
    ulUserSpecPlmnSearch = NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType);
    if ( VOS_TRUE == ulUserSpecPlmnSearch )
    {
        /* ���û�ָ���������ӵ�ǰѡ��״̬���л�ȡFORBIDEN ROAMING LAS��Ϣ */
        PS_MEM_CPY( &stForbRoamLaInfo,
                    NAS_MMC_GetForbRoamLaInfo_PlmnSelection(),
                    sizeof(stForbRoamLaInfo) );
    }
    else
    {
        /* ���û�ָ����������ȫ�ֱ����л�ȡFORBIDEN ROAMING LAS��Ϣ */
        pstForbPlmnInfo                  = NAS_MML_GetForbidPlmnInfo();
        stForbRoamLaInfo.ucForbRoamLaNum = pstForbPlmnInfo->ucForbRoamLaNum;
        PS_MEM_CPY( stForbRoamLaInfo.astForbRomLaList,
                    pstForbPlmnInfo->astForbRomLaList,
                    sizeof(pstForbPlmnInfo->astForbRomLaList) );

        NAS_MML_AddCustomizedForbLaToDestLaList(&(stForbRoamLaInfo.ucForbRoamLaNum),
                                                 stForbRoamLaInfo.astForbRomLaList);
    }



    /* ״̬����Ϊ��ǰδפ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

#if (FEATURE_ON == FEATURE_LTE)
    /* �����ǰ�Ѿ�֪ͨLTE disable,��ʱ����LTE�Ĺ���������Ҫenable LTE */

    if ((VOS_TRUE == NAS_MML_GetDisableLteRoamFlg())
     && (NAS_MML_NET_RAT_TYPE_LTE == pstDestPlmn->enRat)
     && (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != enLteForbiddenStatus))
    {
        /* ��ǰLTE�����ָ����û���ΪĬ��ֵ */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_BUTT == enLCapabilityStatus)
         || (NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS == enLCapabilityStatus))
        {
            NAS_MMC_SndEnableLteNotify();
            NAS_MMC_ClearDisabledLtePlmnId();
            NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }


        /* ����disable LTE������� */
        NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);
    }
#endif

    PS_MEM_SET(&stDestPlmnList, 0x0, sizeof(stDestPlmnList));
    stDestPlmnList.ulPlmnNum = 1;
    PS_MEM_CPY(&stDestPlmnList.astPlmnId[0], pstDestPlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* Modified by  for c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-7-30, begin */
    NAS_MMC_BuildDestPlmnListWhenSearchPlmn_PlmnSelection(&stDestPlmnList, pstDestPlmn);
    /* Modified by  for c00318887 for DPlmn���ݺ����Ƚ���HPLMN, 2015-7-30, end */


    /* ���ݲ�ͬ�Ľ��뼼�������������� */
    switch (pstDestPlmn->enRat)
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSpecPlmnSearchReq_PlmnSelection(&stDestPlmnList, ulUserSpecPlmnSearch);

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSpecPlmnSearchReq_PlmnSelection(&stDestPlmnList, &stForbRoamLaInfo);

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF, ulWaitWasPlmnSrchCnfTimerLen);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            if ( NAS_MMC_PLMN_SEARCH_TYPE_HISTORY == NAS_MMC_GetCurrSearchingType_PlmnSelection() )
            {
                NAS_MMC_SndAsHistoryPlmnSearchReq(&stDestPlmnList, &stForbRoamLaInfo);
            }
            else if ( NAS_MMC_PLMN_SEARCH_TYPE_PREFBAND == NAS_MMC_GetCurrSearchingType_PlmnSelection() )
            {
                NAS_MMC_SndAsPrefBandPlmnSearchReq(&stDestPlmnList, &stForbRoamLaInfo);
            }
            else
            {
                NAS_MMC_SndAsSpecPlmnSearchReq(&stDestPlmnList, &stForbRoamLaInfo);
            }

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF, NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen(ulUserSpecPlmnSearch));

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection: Rat not support.");
            break;
    }


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndSuspendReq_PlmnSelection
 ��������  : ���ݲ�ͬ�Ľ��뼼�����������LMM���͹�������
 �������  : enRat
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndSuspendReq_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* ״̬����Ϊ��ǰδפ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

    /* ���ݲ�ͬ�Ľ��뼼�����õȴ������ظ���״̬ */
    switch (enRat)
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendReq_PlmnSelection: Rat not support.");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndRelReq_PlmnSelection
 ��������  : ���ݲ�ͬ�Ľ��뼼����MM/GMM��EPS�����ͷ����󣬲�Ǩ��״̬����������ʱ��
 �������  : enRat
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndRelReq_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* ���ݲ�ͬ�Ľ��뼼���ֱ��� */
    switch (enRat)
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ��EMM�����ͷ����� */
            NAS_MMC_SndLmmRelReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
            NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_TRUE);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ��MM/GMM�����ͷ����� */
            NAS_MMC_SndMmRelReq();
            NAS_MMC_SndGmmRelReq();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
            NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_TRUE);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRelReq_PlmnSelection: Rat not support.");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateGUSearchInfo
 ��������  : �����������������Ӧ���뼼�������縲����Ϣ
 �������  : pstSrchCnfMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:�������縲������
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateGUCoverageFlg_PlmnSelection(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enCoverType;

    if (WUEPS_PID_WRR == pstSrchCnfMsg->MsgHeader.ulSenderPid)
    {
        enRat = NAS_MML_NET_RAT_TYPE_WCDMA;
    }
    else
    {
        enRat = NAS_MML_NET_RAT_TYPE_GSM;
    }

    switch  (pstSrchCnfMsg->ulSearchRlt)
    {
        /* ָ����ʧ�ܵĸ�������ת�� */
        case RRC_PLMN_SEARCH_RLT_SPEC_FAIL:

            /* ��RRC�ĸ�������ת��ΪNAS��ʽ�ĸ������� */
            NAS_MMC_ConvertRrcCoverTypeToNasFormat(pstSrchCnfMsg->enCoverageType, &enCoverType);

            /* ����RRC�ĵ�ǰ���뼼��������Ϣ���� */
            NAS_MMC_SetRatCoverage_PlmnSelection(enRat, enCoverType);
            break;

        /* ָ���ѳɹ����µ�ǰ���뼼�����ڵĸ��� */
        case RRC_PLMN_SEARCH_RLT_SPEC:

            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), enRat))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(enRat, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        /* ָ����NO RF�򲻸��� */
        case RRC_PLMN_SEARCH_RLT_SPEC_NO_RF:
            break;

        /* HISTORY����ʧ�� */
        case RRC_PLMN_SEARCH_RLT_HISTORY_FAIL:

            /* ��RRC�ĸ�������ת��ΪNAS��ʽ�ĸ������� */
            NAS_MMC_ConvertRrcCoverTypeToNasFormat(pstSrchCnfMsg->enCoverageType, &enCoverType);

            /* ����RRC�ĵ�ǰ���뼼��������Ϣ���� */
            NAS_MMC_SetRatCoverage_PlmnSelection(enRat, enCoverType);
            break;

        /* HISTORY�����ɹ�����֪�������ͣ������� */
        case RRC_PLMN_SEARCH_RLT_HISTORY_SUCC:

            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), enRat))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(enRat, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        /* HISTORY����NO RF�����¸��� */
        case RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF:
            break;

        /* pref bandʧ�ܵĸ�������ת�� */
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_FAIL:

            /* ��RRC�ĸ�������ת��ΪNAS��ʽ�ĸ������� */
            NAS_MMC_ConvertRrcCoverTypeToNasFormat(pstSrchCnfMsg->enCoverageType, &enCoverType);

            /* ����RRC�ĵ�ǰ���뼼��������Ϣ���� */
            NAS_MMC_SetRatCoverage_PlmnSelection(enRat, enCoverType);
            break;

        /* pref band�ɹ����µ�ǰ���뼼�����ڵĸ��� */
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_SUCC:

            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), enRat))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(enRat, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        /* pref band NO RF�򲻸��� */
        case RRC_PLMN_SEARCH_RLT_PREF_BAND_NO_RF:
            break;

        default:
            break;
    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateLmmSearchInfo
 ��������  : ���������������LTE��������Ϣ
 �������  : enRat
             pstLmmSrchCnfMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:�������縲������
 3.��    ��   : 2015��6��9��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateLmmCoverageFlg_PlmnSelection(
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg
)
{
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enCoverType;

    switch(pstLmmSrchCnfMsg->enRlst)
    {
        /* ָ����ʧ�ܵĸ�������ת�� */
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_FAIL:

            /* ��RRC�ĸ�������ת��ΪNAS��ʽ�ĸ������� */
            NAS_MMC_ConvertLmmCoverTypeToNasFormat(pstLmmSrchCnfMsg->enCoverageType, &enCoverType);

            /* ����RRC�ĵ�ǰ���뼼��������Ϣ���� */
            NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, enCoverType);

            break;

        /* ָ���ѳɹ��ĸ�������ת�� */
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC:

            /* ���µ�ǰ���뼼�����ڸ��� */
            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        /* ָ����NO RF�򲻸��� */
        case MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF:
            break;

        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_FAIL:

            /* ��RRC�ĸ�������ת��ΪNAS��ʽ�ĸ������� */
            NAS_MMC_ConvertLmmCoverTypeToNasFormat(pstLmmSrchCnfMsg->enCoverageType, &enCoverType);

            NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, enCoverType);

            break;

        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC:

            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        case MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF:
            break;

        /* pref band��ʧ�ܵĸ�������ת�� */
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_FAIL:

            /* ��RRC�ĸ�������ת��ΪNAS��ʽ�ĸ������� */
            NAS_MMC_ConvertLmmCoverTypeToNasFormat(pstLmmSrchCnfMsg->enCoverageType, &enCoverType);

            /* ����RRC�ĵ�ǰ���뼼��������Ϣ���� */
            NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, enCoverType);

            break;

        /* pref band�ѳɹ��ĸ�������ת�� */
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_SUCC:

            /* ���µ�ǰ���뼼�����ڸ��� */
            if (NAS_MMC_COVERAGE_TYPE_BUTT == NAS_MMC_GetSpecRatCoverageTypeInRatSearchInfoList(
                                              NAS_MMC_GetSearchRatInfo_PlmnSelection(), NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SetRatCoverage_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE, NAS_MMC_COVERAGE_TYPE_LOW);
            }
            break;

        /* pref band��NO RF�򲻸��� */
        case MMC_LMM_PLMN_SRCH_RLT_PREF_BAND_NO_RF:
            break;

        default:
            break;

    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsReCampLtePlmnValid_PlmnSelection
 ��������  : �ж��Ƿ���Ҫ����פ����LTE����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ч
             VOS_FALSE:��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 3.��    ��   : 2015��1��26��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsReCampLtePlmnValid_PlmnSelection(VOS_VOID)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstReCampLtePlmn  = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8                  enPlmnSelectionMode;

    VOS_UINT32                                              ulIsPlmnSupportDam;

    pstReCampLtePlmn          = NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection();
    pstForbidPlmnInfo         = NAS_MML_GetForbidPlmnInfo();
    enPlmnSelectionMode       = NAS_MMC_GetPlmnSelectionMode();

    /* ��ǰ��֧��Lʱ,���»�LTE��������Ч */
    if ( VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE) )
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(NAS_MML_NET_RAT_TYPE_LTE))
    {
        return VOS_FALSE;
    }

    /* ״̬���������л�LTE������Ч */
    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(pstReCampLtePlmn))
    {
        return VOS_FALSE;
    }

    /* PS����Ч */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus() )
    {
        return VOS_FALSE;
    }

    /* PS��������ע�� */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* ��LTE�����ڽ�ֹ�б���,��Ӧ�ĳ����Ǹ�������GUע��ʱ��ԭ��ֵ#11�ܾ�*/
    if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstReCampLtePlmn,
                                          pstForbidPlmnInfo->ucForbPlmnNum,
                                          pstForbidPlmnInfo->astForbPlmnIdList))
    {
        return VOS_FALSE;
    }

    /* ��LTE�����ڽ�ֹGPRS�б���,��Ӧ�ĳ����Ǹ�������GUע��ʱ��ԭ��ֵ#14�ܾ� */
    if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstReCampLtePlmn,
                                          pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                          pstForbidPlmnInfo->astForbGprsPlmnList))
    {
        return VOS_FALSE;
    }

    /* ���֮ǰdisable lte��������֧��DAM�����磬�ҽ�ֹ���뼼�������б�����9014 nvδ������
       ������enable lte,AT&T LTE-BTR-1-1840����Ҫ��ֻ��ֹ310410 lte���磬����lte������ã�
       �������ɾ���������������Ҫ���ԣ����Կ���DAM nv����в��� */
    ulIsPlmnSupportDam = NAS_MML_IsPlmnSupportDam(NAS_MMC_GetDisabledLtePlmnId());

    if (VOS_TRUE == ulIsPlmnSupportDam)
    {
        return VOS_FALSE;
    }

    /* �Զ�ѡ��ģʽ��������Ч */
    if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == enPlmnSelectionMode)
    {
        return VOS_TRUE;
    }

    /* �ֶ�ѡ��ģʽʱ�ػ�LTE�����Ƿ����� */
    if (VOS_TRUE == NAS_MMC_IsPlmnAllowedInManualMode(pstReCampLtePlmn))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReCampLte_PlmnSelection
 ��������  : ����פ��LTE����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��2��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��7��16��
   ��    ��   : s00217060
   �޸�����   : ���֮ǰ�Ѿ�Enable LTE,����פ����LTEʱ����Ҫ֪ͨ�����
 3.��    ��   : 2012��09��27��
   ��    ��   : z00161729
   �޸�����   : DTS2012090303562:����״̬����Lע�����յ�������Ϣ��ȡ��һ������ʧ����״̬�����ַ���Ƿ������������
 4.��    ��   : 2013��01��23��
   ��    ��   : s00217060
   �޸�����   : ���ⵥ: DTS2013012106172,Enable Lteʱֹͣ��ʱ��TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER
 5.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 6.��    ��   : 2014��3��19��
   ��    ��   : w00242748
   �޸�����   : DTS2014031200137:��NV���Դ�ʱ���Զ�������������ʱ������״�����RPLMN�Ļ���
                ��Ҫ��HPLMN/EHPLMN��������㡣
 7.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�

*****************************************************************************/
VOS_VOID NAS_MMC_ReCampLte_PlmnSelection(VOS_VOID)
{
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8   enSpecPlmnSearchFlg;
    VOS_UINT32                                  ulEqual;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enRat;
    NAS_MML_PLMN_WITH_RAT_STRU                  stReCampLtePlmn;
    NAS_MML_PLMN_LIST_WITH_RAT_STRU     stDestPlmnList;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32   enLteCapabilityStatus;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32       enPlmnSearchScene;

    PS_MEM_SET(&stReCampLtePlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    PS_MEM_SET(&stDestPlmnList, 0, sizeof(NAS_MML_PLMN_LIST_WITH_RAT_STRU));

    enLteCapabilityStatus               = NAS_MML_GetLteCapabilityStatus();

    stReCampLtePlmn.enRat               = NAS_MML_NET_RAT_TYPE_LTE;
    enSpecPlmnSearchFlg                 = NAS_MMC_GetSpecPlmnSearchState();
    enRat                               = NAS_MML_GetCurrNetRatType();

    enPlmnSearchScene                   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    PS_MEM_CPY(&(stReCampLtePlmn.stPlmnId),
               NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection(),
               sizeof(stReCampLtePlmn.stPlmnId));

    ulEqual = NAS_MML_CompareBcchPlmnwithSimPlmn(&(stReCampLtePlmn.stPlmnId),
                                                  NAS_MML_GetCurrCampPlmnId());

    if (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus)
    {
        NAS_MMC_SndEnableLteNotify();
        NAS_MMC_ClearDisabledLtePlmnId();
        NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
    }

    /* ����disable LTE������� */
    NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS);

    /* ��ǰ�Ѿ�פ��LTE����,�Ҹ���������Ҫ����פ��������ͬ */
    if ( (NAS_MML_NET_RAT_TYPE_LTE == enRat)
      && (NAS_MMC_SPEC_PLMN_SEARCH_STOP == enSpecPlmnSearchFlg)
      && (VOS_TRUE == ulEqual) )
    {
        /* ����פ��LTEʱ������״̬�ϱ� */
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_CS));
        NAS_MMC_SndMsccServiceStatusInd(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_GetServiceStatusForMscc(NAS_MSCC_PIF_SRVDOMAIN_PS));
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* �˳����״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ״̬����Ϊ��ǰδפ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);


    switch (enRat)
    {
        /* suspend������detach PS�ˣ����»�ȡ��һ������ʧ�� */
        case NAS_MML_NET_RAT_TYPE_BUTT:
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ��MM��GMM��������ָʾ */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

            NAS_MMC_UpdateRegStateSpecPlmnSearch();

            /* ��LMM����ָ������ */
            PS_MEM_SET(&stDestPlmnList, 0x0, sizeof(stDestPlmnList));

            stDestPlmnList.ulPlmnNum = 1;
            PS_MEM_CPY(&stDestPlmnList.astPlmnId[0], &stReCampLtePlmn, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

            NAS_MMC_SndLmmSpecPlmnSearchReq(&stDestPlmnList, VOS_FALSE, enPlmnSearchScene);

            /* ״̬Ǩ��NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE);

            /* ����������ʱ��TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:


            /* ��MM��GMM��������ָʾ */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

            NAS_MMC_UpdateRegStateSpecPlmnSearch();

            /* ��WRR���͹������� */
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);

            /* ״̬Ǩ��NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE);

            /* ����������ʱ��TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:


            /* ��MM��GMM��������ָʾ */
            NAS_MMC_SndGmmPlmnSchInit();
            NAS_MMC_SndMmPlmnSchInit();

            /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
            NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
            /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

            NAS_MMC_UpdateRegStateSpecPlmnSearch();

            /* ��Gas���͹������� */
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);

            /* ״̬Ǩ��NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE);

            /* ����������ʱ��TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);

            break;

        default:

            /* �쳣��ӡ */
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReCampLte_PlmnSelection,ERROR:Rat Error");

            break;
    }

    return;
}

#endif  /* (FEATURE_ON == FEATURE_LTE) */


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateUserPlmnList_PlmnSelection
 ��������  : �����û��б��������������Ӧ���뼼������Ϣ
 �������  : pstPlmnSearchReq
 �������  : pstPlmnSelectionListInfo
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��8��3��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��10��12��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
 3.��    ��   : 2012��11��05��
   ��    ��   : w00176964
   �޸�����   : DTS2011082405001:�������縲������
 4.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
 5.��    ��   : 2015��10��22��
   ��    ��   : s00217060
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnSearchInfo_PlmnSelection(
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstPlmnSearchReq,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    VOS_UINT32                          i;

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        /* ���뼼����Ч������ */
        if (NAS_MML_NET_RAT_TYPE_BUTT == pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType)
        {
            continue;
        }

        /* ���뼼����Ч��δ���й�pref band��/spec�ѣ�����Ҫ���� */
        if (VOS_TRUE == NAS_MMC_IsNeedUpdateSpecRatPlmnSearchInfo_PlmnSelection(&(pstPlmnSearchReq->astInterPlmnSearchInfo[i])))
        {
            /* ���õ�ǰ���뼼��������ȫƵ���� */
            NAS_MMC_SetAllBandSearch_PlmnSelection(pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType, VOS_TRUE);

            /* ���µ�ǰ���뼼�������縲������ */
            NAS_MMC_SetRatCoverage_PlmnSelection(pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType,
                                                 pstPlmnSearchReq->astInterPlmnSearchInfo[i].enCoverType);
        }


        /* �Զ����� */
        if (NAS_MMC_PLMN_SELECTION_MODE_AUTO == NAS_MMC_GetPlmnSelectionMode())
        {
            /* ���������Ҫ��ʣ�����粹�䵽ѡ���б� */
            NAS_MMC_UpdatePlmnListInPlmnSelectionList(&(pstPlmnSearchReq->astInterPlmnSearchInfo[i]),
                                                      pstPlmnSelectionListInfo,
                                                      VOS_TRUE,
                                                      NAS_MMC_GetAllBandSearch_PlmnSelection(pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType));

            /*���¶Ը����������������*/
            NAS_MMC_SortAvailPlmnInPlmnSelectionList(pstPlmnSelectionListInfo);
        }
        else
        {
            /* ������ϲ���Ҫ��ʣ�����粹�䵽ѡ���б� */
            NAS_MMC_UpdatePlmnListInPlmnSelectionList(&(pstPlmnSearchReq->astInterPlmnSearchInfo[i]),
                                                      pstPlmnSelectionListInfo,
                                                      VOS_FALSE,
                                                      NAS_MMC_GetAllBandSearch_PlmnSelection(pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType));
        }
    }

    /* �����Ƿ���й�history�ѱ�־ */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST == pstPlmnSearchReq->enPlmnSearchScene)
    {
        for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
        {
            if (pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType == NAS_MML_GetCurrNetRatType())
            {
                /* �����Ƿ���й�history�� */
                NAS_MMC_SetHistorySearchedFlag_PlmnSelection(pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType,
                                                             pstPlmnSearchReq->astInterPlmnSearchInfo[i].stSearchedType.ucHistorySearchedFlg);
                break;
            }
        }
    }


    /* ��ά�ɲ⣬���ѡ���б���Ϣ */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdatePlmnSearchList_PlmnSelection
 ��������  : �����������б����״̬���������������б���Ϣ
 �������  : ucRatNum
             pstIntraPlmnSearchInfo
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��2��13��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���

 3.��    ��   : 2014��11��15��
   ��    ��   : w00167002
   �޸�����   : DTS2014111201728:CSFB����GU,Я��AVAILABLE���磬û�н�GU��������
                ǰ�档
 4.��    ��   : 2014��11��8��
   ��    ��   : z00161729
   �޸�����   : �������������Ż���Ŀ�޸�
 5.��    ��   : 2015��5��26��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�,����HISTORY���������ܸ���δ�ҵ�������
   ״̬Ϊ�����ڡ�
*****************************************************************************/
VOS_VOID NAS_MMC_UpdatePlmnSearchList_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstInterPlmnSearchInfo,
    VOS_UINT32                                               ulIsNeedSortAvailPlmnList,
    VOS_UINT8                                                ucIsAllBandSearch
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;

    VOS_UINT32                                              ulIsCsfbExist;

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    ulIsCsfbExist        = NAS_MML_IsCsfbServiceStatusExist();

    /* Modified by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    /* �Զ�����������������ΪREG_HPLMN,Ҳ��ΪREG_PREF_PLMN,�����������������������������Ѿ�����ѡ���б����� */
    if (VOS_TRUE == NAS_MMC_IsNeedSearchAvailPlmn_PlmnSelection())
    /* Modified by s00246516 for L-C��������Ŀ, 2014-01-28, End */
    {
        if (VOS_TRUE == ulIsNeedSortAvailPlmnList)
        {
            /* ���������Ҫ��ʣ�����粹�䵽ѡ���б� */
            NAS_MMC_UpdatePlmnListInPlmnSelectionList(pstInterPlmnSearchInfo,
                                                     pstPlmnSelectionList,
                                                     VOS_TRUE,
                                                     ucIsAllBandSearch);


            /*���¶Ը����������������*/
            NAS_MMC_SortAvailPlmnInPlmnSelectionList(pstPlmnSelectionList);
        }
        else
        {
            /* �ж�search cnf fail�������������Ƿ��������б��У������������rplmn��hplmn mcc
               ��ͬ�����rplmnǰ�棬���rplmn�����������hplmnǰ�� */
            NAS_MMC_UpdateRoamPlmnListInPlmnSelectionList(pstInterPlmnSearchInfo,
                                                          pstPlmnSelectionList,
                                                          VOS_TRUE,
                                                          ucIsAllBandSearch);
        }
    }
    else
    {

        /* ������Ͻ�ʣ�����粹�䵽ѡ���б� */
        NAS_MMC_UpdatePlmnListInPlmnSelectionList(pstInterPlmnSearchInfo,
                                                  pstPlmnSelectionList,
                                                  VOS_FALSE,
                                                  ucIsAllBandSearch);
    }


    /* �����ǰ��CSFB��������������L���������򵽺��� */
    if ( (NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ == NAS_MMC_GetPlmnSearchScene_PlmnSelection())
      && (VOS_TRUE                                   == ulIsCsfbExist) )
    {
        NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(NAS_MML_NET_RAT_TYPE_LTE,
                                                pstPlmnSelectionList);
    }

    /* ��ά�ɲ⣬���ѡ���б���Ϣ */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionList);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RefreshPlmnSelectionListAfterRegFail_PlmnSelection
 ��������  : ����ע�ᱻ�ܽ������ѡ���б�
 �������  : enAdditionalAction
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
2. ��    ��   : 2011��1��15��
   ��    ��  : l00171473
   �޸�����   : For DTS2011111003965, �ֶ��������û�ָ�����类ԭ��ֵ13�ܵ��󣬲�Ӧ��EPLMN
 3.��    ��   : 2012��06��01��
   ��    ��   : s00217060
   �޸�����   : For CS/PS mode 1, ���AdditionΪPLMN SELECTION�������Ѿ�Disable L,
                 ˢ��ѡ���б��ѵ�ǰ�����GU���뼼�������б����ǰ��
 4.��    ��   : 2012��12��12��
   ��    ��   : t00212959
   �޸�����   : For DTS2012121104779��������ΪCSPS mode 1���µ�disable L,�类#7�ܾ�����Ӧ�ð���CSPS Mode1����
 5.��    ��   : 2014��11��25��
   ��    ��   : z00161729
   �޸�����   : ���������Ż���Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_RefreshPlmnSelectionListAfterRegFail_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MMC_RAT_SEARCH_INFO_STRU                           *pstSearchRatInfo     = VOS_NULL_PTR;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8                            enPlmnType;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurrPlmnWithRat;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                                              ulDisableLteByCsPsModeOne;


    VOS_UINT32                                              ulIsNeedSortAvailablePlmnSelectionList;

    ulIsNeedSortAvailablePlmnSelectionList = NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection();


    ulDisableLteByCsPsModeOne = NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn();
#endif


    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    pstSearchRatInfo     = NAS_MMC_GetSearchRatInfo_PlmnSelection();

    stCurrPlmnWithRat.stPlmnId = (*NAS_MML_GetCurrCampPlmnId());
    stCurrPlmnWithRat.enRat    = NAS_MML_GetCurrNetRatType();

    /* ��ѡ���б��л�ȡ��ǰ��������� */
    enPlmnType = NAS_MMC_GetPlmnTypeInPlmnSelectionList(&stCurrPlmnWithRat, pstPlmnSelectionList);

    if ((NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION == enAdditionalAction))
    {
#if (FEATURE_ON == FEATURE_LTE)
        if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == NAS_MML_GetLteCapabilityStatus())
         && (VOS_TRUE == ulDisableLteByCsPsModeOne)
         && (VOS_TRUE == ulIsNeedSortAvailablePlmnSelectionList))
        {
            NAS_MMC_RefreshPlmnSelectionList_DisableLte_CsPsMode1RegSuccess(pstPlmnSelectionList, pstSearchRatInfo);
        }
        /* ��ǰ����������������ΪRplmn����Eplmnʱ����Ҫ��ѡ���б���EPLMN���е��� */
        else if ((NAS_MMC_PLMN_TYPE_RPLMN == enPlmnType)
         || (NAS_MMC_PLMN_TYPE_EPLMN == enPlmnType)
         || (NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN == enPlmnType))
        {
            /* ��Ҫ����PLMN SELECTIONʱ,�Զ�ѡ��ģʽ��������Ӧ����������EHPLMN,
               �ֶ�ѡ��ģʽֻ�������û�ָ������ */
            NAS_MMC_RefreshEPlmnInPlmnSelectionList(pstPlmnSelectionList);
        }
        else
        {
        }
#else
        if ((NAS_MMC_PLMN_TYPE_RPLMN == enPlmnType)
         || (NAS_MMC_PLMN_TYPE_EPLMN == enPlmnType)
         || (NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN == enPlmnType))
        {
            /* ��Ҫ����PLMN SELECTIONʱ,�Զ�ѡ��ģʽ��������Ӧ����������EHPLMN,
               �ֶ�ѡ��ģʽֻ�������û�ָ������ */
            NAS_MMC_RefreshEPlmnInPlmnSelectionList(pstPlmnSelectionList);
        }
#endif
    }
    else if (NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN == enAdditionalAction)
    {
        /* ��Ҫ������ǰ��������λ����ʱ,��Ҫ����ǰ��������δ����ע��Ľ��뼼��
           ����ѡ���б���ǰ��,��ǰ���뼼�������������뼼��ǰ�� */

        NAS_MMC_RefreshCurPlmnInPlmnSelectionList(pstPlmnSelectionList, pstSearchRatInfo, enPlmnType);
    }
    else
    {
    }

    /* ��ά�ɲ⣬���ѡ���б���Ϣ */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionList);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SearchNextPlmn_PlmnSelection
 ��������  : ���������Ӳ�����ʱִ��ѡ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���

 3.��    ��   : 2012��2��1��
   ��    ��   : l00130025
   �޸�����   : DTS2012011905274��ָ������Lע��ʧ�ܺ�������û������û���ϱ�ָ���������
 4.��    ��   : 2012��06��02��
   ��    ��   : sunxibo /46746
   �޸�����   : Added for V7R1 C50 CS/PS mode 1
 5.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 6.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
 7.��    ��   : 2014��4��14��
   ��    ��   : s00261364
   �޸�����   : V3R360_eCall��Ŀ:����ʱ���·���״̬

*****************************************************************************/
VOS_VOID NAS_MMC_SearchNextPlmn_PlmnSelection(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /*  ��ȡ�¸�����ʧ�ܣ�����г����������� */
    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return;
    }

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-12, end */

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, begin */
    NAS_MMC_UpdateServiceStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-14, end */

    /* ��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ�� */
    if (stDestPlmn.enRat == NAS_MML_GetCurrNetRatType())
    {
        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    else
    {
        /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_PlmnSelection(NAS_MML_GetCurrNetRatType());
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection
 ��������  : �ڵȴ�ע��״̬���յ�����ע��������ݱ����CS��PS��Addition Action ����״̬����һ����Ϊ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��10��6��
   ��    ��   : w00167002
   �޸�����   : PhaseII�޸�:ɾ�����ĵ�ǰ�������ע��״̬ΪREGISTERED��
                 ͳһ��ע�����󣬲Ÿ���ΪREGISTERED
 3.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���
 4.��    ��   : 2011��12��22��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:Ǩ��״̬���ȴ�EPS��·�ͷ�ʱ������ʱ������
 5.��    ��   : 2012��11��22��
   ��    ��   : t00212959
   �޸�����   : DTS2012112006974:L��ֻ��PSע��ɹ�#18����Ҫdisable LTE��Ҫ��L�����ͷ���������
 6.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
 7.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_PerformAdditionalActionRegFinished_PlmnSelection()
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo           = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU                              stCurPlmn;

    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurrSearchingPlmn = VOS_NULL_PTR;

    enPlmnSearchScene     = NAS_MMC_GetPlmnSearchScene_PlmnSelection();
    pstCurrSearchingPlmn  = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();

    /* ��ȡ��ǰפ����������Ϣ */
    pstCurCampInfo     = NAS_MML_GetCurrCampPlmnInfo();
    stCurPlmn.stPlmnId = pstCurCampInfo->stLai.stPlmnId;
    stCurPlmn.enRat    = pstCurCampInfo->enNetRatType;

    /* ��ȡ�����ȼ������б� */
    pstPlmnSelectionListInfo = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    NAS_MMC_UpdateRegFinishedPlmnNetStatusInPlmnSelectionList(
                                            &stCurPlmn,
                                            pstPlmnSelectionListInfo);

    /* ncell��������,ϵͳ��Ϣ�ϱ������粻һ����ncell�ѵ����磬����ˢ�������б�ʱӦ��ˢ��֮ǰ������plmn */
    if ((VOS_TRUE == NAS_MMC_IsInterPlmnSearch_PlmnSelection())
     && (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH == enPlmnSearchScene))
    {
        stCurPlmn.stPlmnId = pstCurrSearchingPlmn->stPlmnId;
        stCurPlmn.enRat    = pstCurrSearchingPlmn->enRat;
        NAS_MMC_UpdatePlmnNetStatusInPlmnSelectionList(&stCurPlmn,
                                            NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,
                                            pstPlmnSelectionListInfo);
    }

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return;
    }

    /* ����L��GU��ע�������������ô˺�������������ʱ����ͣһ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* ���Ӳ���Ϊפ����ǰ���� */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enAdditionalAction))
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    /* �����NCELL����������Ҫ���������������ˣ��˳�״̬�� */
    if (NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL == NAS_MMC_GetPlmnSearchScene_PlmnSelection())
    {
        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

    /* �������Ӵ��ڣ��ҵ�ǰ��Ҫ��������Ǩ�Ƶ��ȴ������ͷŵ�״̬ */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            if (VOS_FALSE == NAS_MMC_IsDisableLteNeedWaitEpsConnRel_PlmnSelection())
            {
                return;
            }

            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
        }
        else
#endif
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);
        }

        return;
    }

    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL == enAdditionalAction))
    {
        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��enRegAdditionalActionΪ��������������͸����б� */
    NAS_MMC_RefreshPlmnSelectionListAfterRegFail_PlmnSelection(enAdditionalAction);

    NAS_MMC_SearchNextPlmn_PlmnSelection();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_PerformAdditionalAction_PlmnSelection
 ��������  : �ڵȴ������ͷ�״̬���յ����������ͷź���ݱ����CS��PS��Addition Action ����״̬����һ����Ϊ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���

*****************************************************************************/
VOS_VOID NAS_MMC_PerformAdditionalActionConnRel_PlmnSelection(VOS_VOID)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAdditionalAction;

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* ������Ӳ���Ϊ�����ȴ�,��ʾ�ȴ����ӹ������ֽ��յ���ע����,��ʱ��״̬Ǩ�ص��ȴ�ע���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);
        }
        else
#endif
        {
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);
        }

        return;
    }

    /* ���Ӳ���Ϊפ����ǰ���� */
    if ((NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED == enAdditionalAction))
    {
        /* �ظ�״̬���˳��ɹ� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_SUCC);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    if ((NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL == enAdditionalAction)
     || (NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL == enAdditionalAction))
    {
        /* ���ϲ�״̬��ָʾѡ��ʧ�� */
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��enRegAdditionalActionΪ��������������͸����б� */
    NAS_MMC_RefreshPlmnSelectionListAfterRegFail_PlmnSelection(enAdditionalAction);

    NAS_MMC_SearchNextPlmn_PlmnSelection();

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcUserSearchCsRegRslt_PlmnSelection
 ��������  : �����û�ָ��������CS���ע����
 �������  : enCause: CSע��ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ָ�������������(�����û��ؽ��)
             VOS_FASLE: ָ����������δ����(δ���û��ؽ��)
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��28��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 3.��    ��   : 2012��6��4��
   ��    ��   : l00171473
   �޸�����   : DTS2012053003921
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcUserSearchCsRegRslt_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause
)
{
    VOS_UINT32                          ulRlst;

    ulRlst = VOS_FALSE;

    /* ֻҪ��һ����ע��ɹ�����MSCC�����û�ָ�������ɹ� */
    if (NAS_MML_REG_FAIL_CAUSE_NULL == enCsCause)
    {

        /* ���õ�ǰע��״̬Ϊ�ɹ� */
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
        /* ��LMM�����û���������֪ͨ */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif

        return VOS_TRUE;
    }

    /*
       ע��ʧ��ʱ
       1��CS������ע��ʧ�ܣ�ԭ��ֵ��#2,#3,#6������PSע����֪ͨTAF�������
       2��ĳһ������ע��ʧ��ԭ��ֵ��#11,#12,#13��֪ͨTAF����ʧ��
       3��CS Other Cause�������ȴ�PS��ע����
    */

    switch(enCsCause)
    {
        /* ע��ʧ��ԭ��ֵ��#11,#12,#13��֪ͨTAFָ������ʧ�� */
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_AUTH_REJ:

            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* ��LMM�����û���������֪ͨ */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif

            ulRlst = VOS_TRUE;
            break;

        /* ����ԭ��ֵ���ݲ���MMA�����û�ָ����������������ȴ�PS���ע���� */
        default:
            break;
    }
    return ulRlst;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcUserSearchPsRegRslt_PlmnSelection
 ��������  : �����û�ָ��������PS���ע����
 �������  : enCause: PSע��ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ָ�������������(�����û��ؽ��)
             VOS_FASLE: ָ����������δ����(δ���û��ؽ��)
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��28��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��15��
    ��    ��   : W00166186
    �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
  3.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcUserSearchPsRegRslt_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{
    VOS_UINT32                          ulRlst;

    ulRlst = VOS_FALSE;

    /* ֻҪ��һ����ע��ɹ���֪ͨ�û������ɹ�, CAUSE_NULL��ʾע��ɹ� */
    if (NAS_MML_REG_FAIL_CAUSE_NULL == enPsCause)
    {

        /* ���õ�ǰע��״̬Ϊ�ɹ� */
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* �ϱ��ɹ������µ�ǰ��������Ϊ�ֶ����� */
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
        /* ��LMM�����û���������֪ͨ */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif

        return VOS_TRUE;
    }

    /*  ע��ʧ��ʱ
        1��PS��ע��ʧ�ܣ�ԭ��ֵ��#3,#6�������޿�״̬��֪ͨTAF����ʧ��
        2��ĳһ������ע��ʧ��ԭ��ֵ��#11,#12,#13��֪ͨTAF����ʧ��
        3��PSע��ʧ��#8��֪ͨTAF����ʧ��
        4��PS����ע��ʧ��#7�������ȴ�CS��ע����
        5��PS����ע��ʧ��#7�������ȴ�CS��ע����
        6��ע������#9,#10�����ȴ�PSע����;���PSע�����ɹ������سɹ������PSע��ʧ�ܣ���������ʧ��
    */

    switch(enPsCause)
    {
        /* ԭ��ֵ#3,#6,#8�Ĵ��� */
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:

            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* ��LMM�����û���������֪ͨ */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif

            ulRlst = VOS_TRUE;
            break;

        /* ע��ʧ��ԭ��ֵ��#11,#12,#13��֪ͨTAFָ������ʧ�� */
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_AUTH_REJ:

            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* ��LMM�����û���������֪ͨ */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif

            ulRlst = VOS_TRUE;
            break;

        /* PSע��ʧ��ԭ��ֵ#7,#9,#10,#14�����ȴ�CSע���� */
        case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
        case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:
            break;

        /* ����ԭ��ֵ�Ĵ��� ,�ȴ�CS�Ĵ����� */
        default:
            break;
    }

    return ulRlst;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcUserSearchRegCause15_PlmnSelection
 ��������  : CS��PSע��15��ԭ��ֵʱ,�����û�ָ��������ע����
 �������  : enCsCause: CS��ע����
             enPsCause: PS��ע����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ָ�������������(�����û��ؽ��)
             VOS_FASLE: ָ����������δ����(δ���û��ؽ��)
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��8��
   ��    ��   : s46746
   �޸�����   : ͬ�����ⵥDTS2011080101138
 2.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcUserSearchRegCause15_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{
    VOS_UINT32                          ulRlst;

    ulRlst = VOS_FALSE;

    /*  PSע��15��ԭ��ֵʱ
        1��CSע��ʧ��ԭ��ֵ��#11,#12,#13��֪ͨTAF����ʧ��
        2��CSע��ʧ������ԭ��ֵ��������ע��

        CSע��15��ԭ��ֵʱ
        1��PS��ע��ʧ�ܣ�ԭ��ֵ��#3,#6�������޿�״̬��֪ͨTAF����ʧ��
        2��PSע��ʧ��ԭ��ֵ��#11,#12,#13��֪ͨTAF����ʧ��
        3��PSע��ʧ��#8��֪ͨTAF����ʧ��
        4��PSע��ʧ������ԭ��ֵ��������ע��
    */

    switch (enCsCause)
    {
        /* ע��ʧ��ԭ��ֵ��#11,#12,#13��֪ͨTAFָ������ʧ�� */
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_AUTH_REJ:

            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* ��LMM�����û���������֪ͨ */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif

            ulRlst = VOS_TRUE;
            break;

        /* ����ԭ��ֵ���ݲ���MMA�����û�ָ����������������´�����ע�� */
        default:
            break;
    }

    switch (enPsCause)
    {
        /* ԭ��ֵ#3,#6,#8�Ĵ��� */
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
        case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:

            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
#if   (FEATURE_ON == FEATURE_LTE)
            /* ��LMM�����û���������֪ͨ */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif
            ulRlst = VOS_TRUE;
            break;

        /* ע��ʧ��ԭ��ֵ��#11,#12,#13��֪ͨTAFָ������ʧ�� */
        case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
        case NAS_MML_REG_FAIL_CAUSE_AUTH_REJ:

            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
            NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
            /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
            /* ��LMM�����û���������֪ͨ */
            if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
            {
                NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
            }
#endif

            ulRlst = VOS_TRUE;
            break;

        /* ����ԭ��ֵ���ݲ���MSCC�����û�ָ����������������´�����ע�� */
        default:
            break;
    }

    return ulRlst;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcUserSearchRegOtherCause_PlmnSelection
 ��������  : CS��PSע��other causeԭ��ֵʱ,�����û�ָ��������ע����
 �������  : enCsCause: CS��ע����
             enPsCause: PS��ע����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ָ�������������(�����û��ؽ��)
             VOS_FASLE: ָ����������δ����(δ���û��ؽ��)
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��8��
   ��    ��   : s46746
   �޸�����   : ͬ�����ⵥDTS2011042803224
 2.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 3.��    ��   : 2012��6��4��
   ��    ��   : l00171473
   �޸�����   : DTS2012053003921
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcUserSearchRegOtherCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{

    /* ֻҪ��һ����ע��ɹ���֪ͨ�û������ɹ�, CAUSE_NULL��ʾע��ɹ� */
    if ((NAS_MML_REG_FAIL_CAUSE_NULL == enCsCause)
     || (NAS_MML_REG_FAIL_CAUSE_NULL == enPsCause))
    {

        /* ���õ�ǰע��״̬Ϊ�ɹ� */
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* �ϱ��ɹ������µ�ǰ��������Ϊ�ֶ����� */
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
        /* ��LMM�����û���������֪ͨ */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif

        return VOS_TRUE;
    }

    /* �������ΪCS ONLY����PS ONLY,��һ����ǰС����֧��ʱ,��Ҫ�����б�����һ
       �������ظ�ָ��������� */
    if ((NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT == enCsCause)
     && (NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT == enPsCause))
    {
        return VOS_FALSE;
    }

    if ((NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT == enCsCause)
     && (NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT == enPsCause))
    {
        return VOS_FALSE;
    }

    /* PSע��ʧ��ԭ��ֵ#9,#10�����ȴ�PSע���� */
    if ((NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED == enPsCause)
     || (NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED == enPsCause))
    {
        return VOS_FALSE;
    }

    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
    /* ��LMM�����û���������֪ͨ */
    if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
    {
        NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
    }
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcUserSearchRegRslt_PlmnSelection
 ��������  : �����û�ָ��������ע����
 �������  : enCsCause: CS��ע����
             enPsCause: PS��ע����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ָ�������������(�����û��ؽ��)
             VOS_FASLE: ָ����������δ����(δ���û��ؽ��)
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��6��29��
   ��    ��   : ��� l00171473
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��8��7��
   ��    ��   : l00130025
   �޸�����   : �����ϱ�˳��
 3.��    ��   : 2011��9��8��
   ��    ��   : s46746
   �޸�����   : ͬ��V3R1�汾���ⵥDTS2011080101138��DTS2011042803224
 4.��    ��   : 2011��11��09��
   ��    ��   : w00166186
   �޸�����   : ���ⵥDTS201110705494,�ֶ�������PS����ԭ��ֵ14��CS�ɹ����ϱ�����ʧ��
 5.��    ��   : 2011��12��15��
   ��    ��   : W00166186
   �޸�����   : dts2011111502641,L��PLMN�����ֹTA��������
 6.��    ��   : 2012��6��4��
   ��    ��   : l00171473
   �޸�����   : DTS2012053003921
 7.��    ��   : 2013��9��14��
   ��    ��   : w00167002
   �޸�����   : DTS2013090908249:�����û�ָ������24003��CSע�ᱻ��15��MM��LIMIT
                 ״̬����ѡ��״̬���յ�ͬһС����SYSINFO��֪ͨMM��ǰû��FORB FLG,
                 ����MM����ѭ��ע�᣻
                 CSע�ᱻ��15���ϱ�ϵͳ��Ϣ������MM/GMM�ϱ�405����ʱҲ����ֱ��
                 �ϱ�ע��������Ҫ��������С����
*****************************************************************************/
VOS_UINT32 NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
)
{
    /* CauseֵΪ NAS_MML_REG_FAIL_CAUSE_NULL ��ʾ����ע��ɹ���
       CauseֵΪ NAS_MML_REG_FAIL_CAUSE_BUTT ��ʾ����δ�յ�ע���� */

    /* ��δ��ȡ��ע����,�����ȴ�ע���� */
    if ((NAS_MML_REG_FAIL_CAUSE_BUTT == enPsCause)
     && (NAS_MML_REG_FAIL_CAUSE_BUTT == enCsCause))
    {
        return VOS_FALSE;
    }

    /* ��δ��ȡ��PSע��������ǰ��ȡ��CSע����, ����CS��ע��ԭ��ֵ */
    if ( (NAS_MML_REG_FAIL_CAUSE_BUTT == enPsCause)
      && (NAS_MML_REG_FAIL_CAUSE_BUTT != enCsCause) )
    {
        return NAS_MMC_ProcUserSearchCsRegRslt_PlmnSelection(enCsCause);
    }

    /* ��δ��ȡ��CSע��������ǰ��ȡ��PSע����������PS��ע��ԭ��ֵ */
    if ( (NAS_MML_REG_FAIL_CAUSE_BUTT == enCsCause)
      && (NAS_MML_REG_FAIL_CAUSE_BUTT != enPsCause) )
    {
        return NAS_MMC_ProcUserSearchPsRegRslt_PlmnSelection(enPsCause);
    }


    /* �������ע��������ȡ,CS��PSע��15��ԭ��ֵʱ,��ע�������� */
    if ( (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL       == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL       == enPsCause)
      || (NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM == enCsCause)
      || (NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM == enPsCause))
    {
        return NAS_MMC_ProcUserSearchRegCause15_PlmnSelection(enCsCause, enPsCause);
    }

    /* �������ע��������ȡ,CS��PSע��15��ԭ��ֵʱ,��ע�������� */
    if ((NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE <= enCsCause)
     || (NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE <= enPsCause))
    {
        return NAS_MMC_ProcUserSearchRegOtherCause_PlmnSelection(enCsCause, enPsCause);
    }

    /* ֻҪ��һ����ע��ɹ�����MMA�����û�ָ�������ɹ� */
    if ((NAS_MML_REG_FAIL_CAUSE_NULL == enCsCause)
     || (NAS_MML_REG_FAIL_CAUSE_NULL == enPsCause))
    {

        /* ���õ�ǰע��״̬Ϊ�ɹ� */
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_SUCCESS);
        /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
        /* ��LMM�����û���������֪ͨ */
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
#endif

        return VOS_TRUE;
    }

    /* �ѻ�ȡ��CS��PS��ע������������ȷԭ��ֵ����other cause��15,�ϱ�ʧ�� */
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);
    /* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

#if   (FEATURE_ON == FEATURE_LTE)
    /* ��LMM�����û���������֪ͨ */
    if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
    {
        NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
    }
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_LoadInterSysFsm_PlmnSelection
 ��������  : ����SUSPEND��ԭ��ֵ��ͬ��״̬��
 �������  : MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��22��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_LoadInterSysFsm_PlmnSelection(
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
)
{
    switch ( enSuspendCause )
    {
        /* ����HANDOVER״̬�� */
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_LoadInterSysFsm_PlmnSelection():MMC_SUSPEND_CAUSE_HANDOVER, snd Mode change");
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            break;

        /* ���� CCO״̬�� */
        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_LoadInterSysFsm_PlmnSelection():MMC_SUSPEND_CAUSE_CELLCHANGE, snd Mode change");
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            break;

        /* ���� С����ѡ ״̬�� */
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_LoadInterSysFsm_PlmnSelection():MMC_SUSPEND_CAUSE_CELLRESELECT or REDIRECTION, snd Mode change");
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            break;

        /* ���� ϵͳ������������ ״̬�� */
        case MMC_SUSPEND_CAUSE_PLMNSEARCH:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_OOS);
            break;

        default:
            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_LoadInterSysFsm_PlmnSelection():default case");
            break;
    }

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcUserSpecPlmnSrchForbGprsInfo_PlmnSelection
 ��������  : ѡ��״̬���д���FORB GPRS��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��16��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ProcUserSpecPlmnSrchForbGprsInfo_PlmnSelection( VOS_VOID )
{
    NAS_MML_LAI_STRU                   *pstLai          = VOS_NULL_PTR;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;

    pstLai              = NAS_MML_GetCurrCampLai();
    enCsRegCause        = NAS_MMC_GetCsRegCause_PlmnSelection();
    enPsRegCause        = NAS_MMC_GetPsRegCause_PlmnSelection();

    /* ��GSM�£����CSע��ɹ���PSδע�ᣬ��ɾ��FORB GPRS��Ϣ */
    if ( (NAS_MML_NET_RAT_TYPE_GSM          == NAS_MML_GetCurrNetRatType())
      && (NAS_MML_REG_FAIL_CAUSE_NULL       == enCsRegCause)
      && (NAS_MML_REG_FAIL_CAUSE_BUTT       == enPsRegCause) )
    {
        NAS_MML_DelForbGprsPlmn(&(pstLai->stPlmnId));
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection
 ��������  : ָ�����������󣬸��µ�ǰ״̬���������ϢΪ��ͨ���������Ա�������ϴ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��22��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��13��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 10 Modified

*****************************************************************************/
VOS_VOID NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection( VOS_VOID )
{
    MSCC_MMC_PLMN_SEARCH_REQ_STRU       stPlmnSrhReg;
    VOS_UINT32                          ulBuildEventType;

    PS_MEM_SET(&stPlmnSrhReg, 0x0, sizeof(MSCC_MMC_PLMN_SEARCH_REQ_STRU));
    stPlmnSrhReg.enAcqReason = NAS_MSCC_PIF_ACQ_REASON_POWER_UP;

    stPlmnSrhReg.MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stPlmnSrhReg.MsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    stPlmnSrhReg.MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stPlmnSrhReg.MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    stPlmnSrhReg.MsgHeader.ulLength          = sizeof(MSCC_MMC_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    stPlmnSrhReg.MsgHeader.ulMsgName         = ID_MSCC_MMC_PLMN_SEARCH_REQ;

    ulBuildEventType  = NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ);

    /*���õ�ǰ�����ϢΪ��������*/
    NAS_MMC_SaveCurEntryMsg(ulBuildEventType, (struct MsgCB*)&stPlmnSrhReg);

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection
 ��������  : �����û�ָ�������Ĳ���
 �������  : pstPlmnId: �û�ָ����PLMN
             ucAccessMode: �û�ָ���Ľ���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��01��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��10��25��
   ��    ��   : w00167002
   �޸�����   : DTS2011102405359:����ָ����ʱ����Ҫֹͣ�������еĸ����ȼ�/bg����

 3.��    ��   : 2011��11��11��
   ��    ��   : w00167002
   �޸�����   : ��ǰΪָ���ѣ����ʼ��ѡ��״̬���Ľ�ֹ����LA��Ϣ����
 4.��    ��   : 2011��11��24��
   ��    ��   : W00166186
   �޸�����   : DT2011112308459,ָ��PLMNû��ע��ɹ���,available��ʱ����ʱ������RPLMN

 5.��    ��   : 2012��5��10��
   ��    ��   : l65478
   �޸�����   : DTS2012050500988:NMO Iʱ,PSע��ʧ��#11,�յ�ϵͳ��Ϣ���ַ�����ע��
 6.��    ��   : 2013��4��16��
   ��    ��   : z00161729
   �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
 7.��    ��   : 2013��6��4��
   ��    ��   : z00161729
   �޸�����  : SVLTE ��usim�ӿڵ����޸�
                  �����һ�TL������Ӧ������������һء�
 8.��    ��   : 2014��2��24��
   ��    ��   : w00176964
   �޸�����   : High_Rat_Hplmn_Search���Ե���
 9.��    ��   : 2014��10��25��
   ��    ��   : b00269685
   �޸�����   : TD��High_Rat_Hplmn_Search���Ե���

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateUserSpecPlmnSearchInfo_PlmnSelection(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                           ucAccessMode
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stUserSpecPlmn;

    /* �����û�ָ����PlmnID������뼼�� */
    stUserSpecPlmn.stPlmnId.ulMcc = pstPlmnId->ulMcc;
    stUserSpecPlmn.stPlmnId.ulMnc = pstPlmnId->ulMnc;

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-16, begin */
    stUserSpecPlmn.enRat = ucAccessMode;
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-16, end */

    NAS_MMC_SetUserSpecPlmnId(&stUserSpecPlmn);

    /* ����ָ������ǰפ����PlmnID�����뼼�� */
    NAS_MMC_SaveUserReselPlmnInfo();


    /* ��ǰΪָ���ѣ����ʼ��ѡ��״̬���Ľ�ֹ����LA��Ϣ���� */
    PS_MEM_SET( NAS_MMC_GetForbRoamLaInfo_PlmnSelection(),
                0X0, sizeof(NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU) );

    PS_MEM_SET(NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection(),
               0X0, sizeof(NAS_MML_PLMN_ID_STRU));

    /* ���õ�ǰע��״̬δע�� */
    NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_FALSE);

    /* ��ǰģʽ����MANUAL���򲻸���NV */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        return;
    }

    /* ���õ�ǰ����ģʽΪ�ֶ�ģʽ */
    NAS_MMC_SetPlmnSelectionMode(NAS_MMC_PLMN_SELECTION_MODE_MANUAL);


    /* ��������ȼ�������ʱ�������й����У���ֹͣ�ö�ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HPLMN_TIMER))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_HPLMN_TIMER);

        /* HPLMN TIMER ֹͣ�¼��ϱ� */
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_HPLMN_TIMER_STOP,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }

    /* ������ڸ����ȼ�������ʱ�������й����У���ֹͣ�ö�ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH);
    }

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER);

        NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main();
        NAS_MMC_InitTdHighRatSearchCount();
    }

    /* ����ǰ����ģʽд��NVIM�� */
    NAS_MMC_WritePlmnSelectionModeNvim();

    /* ����ģʽ�仯�ϱ�USIM */
    if (VOS_TRUE == NAS_MMC_IsNeedSndStkSearchModeChgEvt())
    {
        NAS_MMC_SndStkSearchModeChgEvt(NAS_MMC_PLMN_SELECTION_MODE_MANUAL);
    }

}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegRslt_PlmnSelection
 ��������  : ��Csע�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��23��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��14��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:��ǰ��Ϊѡ��״̬��������ӽ�ֹ������Ϣ
                ��ѡ��״̬���Ľ�ֹ����LA������ȥ
 3.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
4.��    ��   : 2011��11��28��
   ��    ��   : w00167002
   �޸�����   : DTS2011112406707:����ǰΪ�������ҵ�ǰ��AdditionalAction��Ϊ
                ��ʼ��Чֵ���򲻸��µ�ǰ��AdditionalAction��ֵ����������ǰΪ
                �����̻�ǰΪ��������AdditionalActionΪ��ʼ��Чֵ�������
                ��ǰ��AdditionalAction��ֵ.
                �޸�ԭ��:��ROAMING BROKERʱ������1��ʧ��,ע��ʧ��1�κ�
                MMC��Ҫ����������MMC����Ҫ��������Ľ��(����ѡ��״̬��)��
                ���յ�ϵͳ��Ϣ��ʱ�򣬼����̻����MMC��AdditionalAction��ֵ,
                ����ROMING BROKER����ʧЧ��
 5.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ

 6.��    ��   : 2012��1��3��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������
                ͳһ����ע��ADDITIONAL ACTION��ֵ�������û��Զ����ԭ��ֵ(>=256)����
                ������ע����������ǰ֧��Lģ����ע��ԭ��ֵС��260ʱ֪ͨLMM.

 7.��    ��   : 2012��1��20��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:��ע��ʧ�ܵ���Ϣ֪ͨ������ע����������
                  �ܽ��и��õ���չ.
 8.��    ��   : 2012��3��1��
   ��    ��   : w00176964
   �޸�����   : DTS2012022407450:����ATTACHʱ,MM����֪ͨLMM��ʱCS��ע������������TAU�����Ͳ���ȷ

 9.��    ��   : 2012��5��10��
   ��    ��   : l65478
   �޸�����   : DTS2012050500988:CSע��ɹ�ʱ,����ɾ��forbid PLMN for GPRS��Ϣ
10.��    ��   : 2012��6��4��
   ��    ��   : l00171473
   �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
11.��    ��   : 2012��08��20��
   ��    ��   : l65478
   �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
12.��    ��   : 2012��8��13��
   ��    ��   : L65478
   �޸�����   : DTS2012080301606:ע��ʧ�ܺ����ֶ�����ʧ��
13.��    ��   : 2012��12��6��
   ��    ��   : s00217060
   �޸�����   : DTS2012120410842:������ָ������ע��ɹ����������ע��ɹ�ʱ��Ҳ��Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
14.��    ��   : 2013��1��11��
   ��    ��   : w00176964
   �޸�����   : DTS2013010706662:��������EPLMN�߼��жϺ���
15.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
16.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
17.��    ��   : 2014��01��10��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseIII��Ŀ
18.��    ��   : 2014��05��4��
   ��    ��   : w00176964
   �޸�����   : V3R3C60_eCall��Ŀ����
19.��    ��   : 2014��11��3��
  ��    ��   : z00161729
  �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCsRegRslt_PlmnSelection(
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
#endif

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo = VOS_NULL_PTR;
    pstDPlmnNPlmnCfgInfo  = NAS_MMC_GetDPlmnNPlmnCfgInfo();

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    if (MM_MMC_LU_RESULT_SUCCESS == pstCsRegRsltInd->enLuResult)
    {
        NAS_MMC_SetCsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_NULL);

        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /* ����DPLMN NPLMN�б� */
        if (VOS_TRUE == NAS_MMC_IsRoam())
        {
            NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_DPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
            NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
            NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);
            NAS_MMC_LogDplmnNplmnList();
        }

        /* ע��ɹ�ʱ�����GEO PLMN���´�������ʱ������ֱ����RPLMN */
        NAS_MMC_InitGeoPlmn();

        /* ��Hplmn��Rej Lai��Ϣ����� */
        NAS_MMC_ClearHplmnRejDomainInfo(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS);

        /* ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_GuRegRsltSucc(NAS_MMC_REG_DOMAIN_CS);

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_UpdateCsRegStateCsRegSucc();

        /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NORMAL_SERVICE);
        /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

#if   (FEATURE_ON == FEATURE_LTE)

        /* ����ע��ʱ��֪ͨLMM��ʱLU�Ľ�� */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRsltInd->enRegFailCause))
         && (VOS_FALSE == pstCsRegRsltInd->ucIsComBined))
        {
            stActionRslt.enProcType     = NAS_MML_PROC_LAU;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
            stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
            stActionRslt.ulAttemptCount = 0;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS, VOS_TRUE, pstCsRegRsltInd->enRegFailCause);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcCsRegFail(MM_MMC_CS_REG_RESULT_IND, pstCsRegRsltInd);


        /* ������ԭ��ֵΪ#15, ����ӽ�ֹ������Ϣ��ѡ��״̬���Ľ�ֹ����LA������ȥ,
           ���û�ָ������ʱ������Ҫ�ѽ�ֹLA��������� */
        enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
        if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
        }
        ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
        if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
          && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstCsRegRsltInd->enRegFailCause) )
        {
            NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                                   NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
        }

        /* �������Ҫ�ȴ���һ��ע����,�򲻸���ע��ԭ��ֵ,�ȴ�conut�ﵽ�������,
           �Ա����û�ָ�������ظ���� */
        if ((NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enAdditionalAction)
         && (NAS_MMC_ADDITIONAL_ACTION_BUTT             != enAdditionalAction))
        {
            NAS_MMC_SetCsRegCause_PlmnSelection(pstCsRegRsltInd->enRegFailCause);
        }

        if ( VOS_TRUE == NAS_MML_IsNetworkRegFailCause(pstCsRegRsltInd->enRegFailCause) )
        {
            /* ֻ�ڸ�������ʵ����������ʱ��Ÿ���ע����Ϣ�� */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_CS, pstCsRegRsltInd->enRegFailCause);

            /* ����DPLMN NPLMN�б� */
            if (VOS_TRUE == NAS_MMC_IsRoam())
            {
                NAS_MMC_UpdateDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, NAS_MMC_MAX_CFG_NPLMN_NUM, &pstDPlmnNPlmnCfgInfo->usNplmnListNum, pstDPlmnNPlmnCfgInfo->astNPlmnList);
                NAS_MMC_DeleteDPlmnNPlmnList(NAS_MML_GetCurrCampLai(), NAS_MMC_REG_DOMAIN_CS, &pstDPlmnNPlmnCfgInfo->usDplmnListNum, pstDPlmnNPlmnCfgInfo->astDPlmnList);
                NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(pstDPlmnNPlmnCfgInfo);
                NAS_MMC_LogDplmnNplmnList();
            }
        }

        /* PSע��ɹ�, CSע��ʧ��, ԭ��Ϊ11 12 13 15�����, ��Ҫ����ñ�־.
           ��Ϊ��ʱCS�� RPLMNû�и���Ϊ�û�ָ����PLMN, �˺����ȴ���������������
           RPLMN����EPLMN, ����Ҫ����ñ�־. */

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(pstCsRegRsltInd->enRegFailCause);


#if   (FEATURE_ON == FEATURE_LTE)

        /* С�� NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE�ľܾ�ԭ����UE���Է���ע���ԭ��ֵ����Ҫ֪ͨLMM */
        /* ����ע��ʱ��֪ͨLMM��ʱLU�Ľ�� */
        if ((VOS_TRUE  == NAS_MML_IsRegFailCauseNotifyLmm(pstCsRegRsltInd->enRegFailCause))
         && (VOS_FALSE == pstCsRegRsltInd->ucIsComBined))
        {
            /* ��ǰSYSCFG��L����ʱ����Ҫ��LMM֪ͨ */
            stActionRslt.enProcType     = NAS_MML_PROC_LAU;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
            stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
            stActionRslt.enCnCause      = pstCsRegRsltInd->enRegFailCause;
            stActionRslt.ulAttemptCount = pstCsRegRsltInd->ulLuAttemptCnt;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif
    }


    /* AdditionalAction��Ч������CS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();
        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegRslt_PlmnSelection
 ��������  : ��Psע�����Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��23��
   ��    ��   : l00130025
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��14��
   ��    ��   : w00167002
   �޸�����   : DTS2011110907180:��ǰ��Ϊѡ��״̬��������ӽ�ֹ������Ϣ
                ��ѡ��״̬���Ľ�ֹ����LA������ȥ
 3.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
 4.��    ��   : 2011��11��28��
   ��    ��   : w00167002
   �޸�����   : DTS2011112406707:����ǰΪ�������ҵ�ǰ��AdditionalAction��Ϊ
                ��ʼ��Чֵ���򲻸��µ�ǰ��AdditionalAction��ֵ����������ǰΪ
                �����̻�ǰΪ��������AdditionalActionΪ��ʼ��Чֵ�������
                ��ǰ��AdditionalAction��ֵ.
                �޸�ԭ��:��ROAMING BROKERʱ������1��ʧ��,ע��ʧ��1�κ�
                MMC��Ҫ����������MMC����Ҫ��������Ľ��(����ѡ��״̬��)��
                ���յ�ϵͳ��Ϣ��ʱ�򣬼����̻����MMC��AdditionalAction��ֵ,
                ����ROMING BROKER����ʧЧ��
 5.��    ��   : 2011��12��5��
   ��    ��   : z00161729
   �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ

 6.��    ��   : 2012��1��3��
   ��    ��   : w00167002
   �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������
                ͳһ����ע��ADDITIONAL ACTION��ֵ�������û��Զ����ԭ��ֵ(>=256)����
                ������ע����������ǰ֧��Lģ����ע��ԭ��ֵС��260ʱ֪ͨLMM��ǰ��ע����.
 7.��    ��   : 2012��3��1��
   ��    ��   : w00176964
   �޸�����   : DTS2012022407450:����GMM������RAU/ATTACH���ͣ�MMCת����LMM
 8.��    ��   : 2012��03��30��
   ��    ��   : l00130025
   �޸�����   : DTS2012032307791,����LMMע����,CombineRegʱ��Ҫ���ֽ����
 9.��    ��   : 2012��5��10��
   ��    ��   : l65478
   �޸�����   : DTS2012050500988:CSע��ɹ�ʱ,����ɾ��forbid PLMN for GPRS��Ϣ
10.��    ��   : 2012��6��4��
   ��    ��   : l00171473
   �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
11.��    ��   : 2012��6��8��
   ��    ��   : l00130025
   �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨAPS/CDS��Ϣ���޷�����
12.��    ��   : 2012��08��20��
   ��    ��   : l65478
   �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
13.��    ��   : 2012��8��13��
   ��    ��   : L65478
   �޸�����   : DTS2012080301606:ע��ʧ�ܺ����ֶ�����ʧ��
14.��    ��   : 2012��12��6��
   ��    ��   : s00217060
   �޸�����   : DTS2012120410842:������ָ������ע��ɹ����������ע��ɹ�ʱ��Ҳ��Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
15.��    ��   : 2013��1��11��
   ��    ��   : w00176964
   �޸�����   : DTS2013010706662:��������EPLMN�߼��жϺ���
16.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
17.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����
18.��    ��   : 2014��01��10��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseIII��Ŀ
19.��    ��   : 2014��05��4��
   ��    ��   : w00176964
   �޸�����   : V3R3C60_eCall��Ŀ����

*****************************************************************************/
VOS_VOID NAS_MMC_ProcPsRegRslt_PlmnSelection(
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
)
{
    NAS_MML_LAI_STRU                                       *pstLai         = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;


    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;

    NAS_MML_PLMN_ID_STRU                                   *pstForbPlmnForGprs = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstCurrCampOnPlmn = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
    NAS_MML_PROC_TYPE_ENUM_U32                              enProcType;

    /* ת�����͸�L��proctype */
    enProcType = NAS_MML_PROC_BUTT;

    NAS_MMC_ConverGmmActionTypeToMml(pstPsRegRsltInd->enGmmActionType, &enProcType);


    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enReqDomain, &stActionRslt.enReqDomain);

    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enRsltDomain, &stActionRslt.enRstDomain);



#endif
    pstLai              = NAS_MML_GetCurrCampLai();

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstPsRegRsltInd->enActionResult)
    {
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-10, begin */
        /* ����ע������Ϣ */
        NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_REG_RESULT_IND, pstPsRegRsltInd);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-10, end */

        NAS_MMC_SetPsRegCause_PlmnSelection(NAS_MML_REG_FAIL_CAUSE_NULL);
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS, NAS_MML_REG_FAIL_CAUSE_NULL);
        NAS_MMC_ClearHplmnRejDomainInfo(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS);

        if (VOS_TRUE == NAS_MML_GetKeepCsForbInfoCfg())
        {
            /* ֻɾ��Forb GPRS PLMN��Ϣ��CS���FORB��Ϣ��Ȼ���� */
            NAS_MML_DelForbGprsPlmn(&(pstLai->stPlmnId));
        }
        else
        {  
            /* ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ */
            NAS_MMC_DelForbInfo_GuRegRsltSucc(NAS_MMC_REG_DOMAIN_PS);
        }

        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());


        /* ע��ɹ�ʱ�����GEO PLMN���´�������ʱ������ֱ����RPLMN */
        NAS_MMC_InitGeoPlmn();

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_UpdatePsRegStatePsRegSucc();

        /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
        /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

#if   (FEATURE_ON == FEATURE_LTE)

        /* �����̲�֪ͨ��LMM */
        if ( VOS_TRUE == NAS_MML_IsRegFailCauseNotifyLmm(pstPsRegRsltInd->enRegFailCause) )
        {
            stActionRslt.enProcType     = enProcType;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_SUCCESS;
            stActionRslt.enCnCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
            stActionRslt.ulAttemptCount = 0;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }

#endif

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, pstPsRegRsltInd->enRegFailCause);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcPsRegFail(GMM_MMC_PS_REG_RESULT_IND,
                                                   pstPsRegRsltInd);


        /* ������ԭ��ֵΪ#15, ����ӽ�ֹ������Ϣ��ѡ��״̬���Ľ�ֹ����LA������ȥ,
           ���û�ָ������ʱ������Ҫ�ѽ�ֹLA��������� */
        enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
        if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
        }
        ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
        if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
          && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == pstPsRegRsltInd->enRegFailCause) )
        {
            NAS_MML_AddForbRoamLa( NAS_MML_GetCurrCampLai(),
                                   NAS_MMC_GetForbRoamLaInfo_PlmnSelection() );
        }

        if ( (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
          && (NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN == pstPsRegRsltInd->enRegFailCause) )
        {
            pstForbPlmnForGprs = NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection();
            pstCurrCampOnPlmn  = NAS_MML_GetCurrCampPlmnId();

            *pstForbPlmnForGprs = *pstCurrCampOnPlmn;
        }

        /* �������Ҫ�ȴ���һ��ע����,�򲻸���ע��ԭ��ֵ,�ȴ�conut�ﵽ�������,
           �Ա����û�ָ�������ظ���� */
        if ((NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enAdditionalAction)
         && (NAS_MMC_ADDITIONAL_ACTION_BUTT             != enAdditionalAction))
        {
            NAS_MMC_SetPsRegCause_PlmnSelection(pstPsRegRsltInd->enRegFailCause);
        }

        if ( VOS_TRUE == NAS_MML_IsNetworkRegFailCause(pstPsRegRsltInd->enRegFailCause) )
        {
            /* ֻ�ڸ�������ʵ����������ʱ��Ÿ���ע����Ϣ�� */
            NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_PS, pstPsRegRsltInd->enRegFailCause);
        }

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(pstPsRegRsltInd->enRegFailCause);

#if   (FEATURE_ON == FEATURE_LTE)

        /* С�� NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE�ľܾ�ԭ����UE���Է���ע���ԭ��ֵ����Ҫ֪ͨLMM */
        if ( VOS_TRUE == NAS_MML_IsRegFailCauseNotifyLmm(pstPsRegRsltInd->enRegFailCause) )
        {
            stActionRslt.enProcType     = enProcType;
            stActionRslt.enRegRst       = NAS_MML_REG_RESULT_FAILURE;
            stActionRslt.enCnCause      = pstPsRegRsltInd->enRegFailCause;
            stActionRslt.ulAttemptCount = pstPsRegRsltInd->ulRegCounter;

            NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
        }
#endif
    }

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();
        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);
    }

    return;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMsccSrvAcqCnfAccordingPlmnSearchRslt
 ��������  : ����ѡ�������mscc����ҵ�񴥷��������
 �������  : enPlmnSelectionRslt - �������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��2��
   ��    ��   : z00161729
   �޸�����   : DSDS III����
*****************************************************************************/
VOS_VOID  NAS_MMC_SndMsccSrvAcqCnfAccordingPlmnSearchRslt(
    NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32               enPlmnSelectionRslt
)
{
    /* ��������ɹ����������������ϱ�mma�������Ϊ�ɹ� */
    if ((VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
     && (NAS_MMC_PLMN_SELECTION_SUCC == enPlmnSelectionRslt))
    {
        NAS_MMC_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS);
    }
    else
    {
        NAS_MMC_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);
    }

    return;
}

#endif


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCoverageRatNum_PlmnSelection
 ��������  : ��ȡ��ǰ���ڸ��ǵĽ��뼼������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��27��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetCoverageRatNum_PlmnSelection(VOS_VOID)
{
    NAS_MMC_RAT_SEARCH_INFO_STRU       *pstSearchRatInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList   = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRatNum;

    pstSearchRatInfo    = NAS_MMC_GetSearchRatInfo_PlmnSelection();
    pstPrioRatList      = NAS_MML_GetMsPrioRatList();
    ulRatNum            = pstPrioRatList->ucRatNum;

    /* ��HISTORY������������ȡ��ǰ���ڵĸ�������ģʽ */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH == NAS_MMC_GetPlmnSearchScene_PlmnSelection())
    {
        for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
        {
            /* ���й�ȫƵ�����ҵ�ǰû�и��� */
            if ((VOS_TRUE == NAS_MML_IsNetRatSupported(pstSearchRatInfo[i].enRatType))
             && (VOS_TRUE == pstSearchRatInfo[i].ucHistorySearchedFlag)
             && (NAS_MMC_COVERAGE_TYPE_NONE == pstSearchRatInfo[i].enCoverageType))
            {
                ulRatNum--;
            }

            /* �����쳣���� */
            if (0 == ulRatNum)
            {
                break;
            }
        }

        return ulRatNum;

    }


    /* ȫƵ��������������ȡ��ǰ���ڸ��ǵ�����ģʽ */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        /* ���й�ȫƵ�����ҵ�ǰû�и��� */
        if ((VOS_TRUE == NAS_MML_IsNetRatSupported(pstSearchRatInfo[i].enRatType))
         && (VOS_TRUE == pstSearchRatInfo[i].ucSearchAllBand)
         && (NAS_MMC_COVERAGE_TYPE_NONE == pstSearchRatInfo[i].enCoverageType))
        {
            ulRatNum--;
        }

        /* �����쳣���� */
        if (0 == ulRatNum)
        {
            break;
        }
    }

    return ulRatNum;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndRslt_PlmnSelection
 ��������  : ѡ��״̬���з���PlmnSelection�������Ľ��
 �������  : enPlmnSelectionRslt
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��12��14��
   ��    ��   : w00176964
   �޸�����   : V7R1 phaseIV ����:פ�����ͨ���µ��������������Ĵ���

 3.��    ��   : 2014��1��22��
   ��    ��   : w00167002
   �޸�����   : ��������������ǰȫƵ�������Ҵ��ڸ��ǵ��߼���NAS_MMC_SndPlmnSelectionRslt
                �ƶ�����ǰ��������չNAS_MMC_SndPlmnSelectionRslt�����ĸ����ԡ�
 4.��    ��   : 2014��1��27��
   ��    ��   : s00246516
   �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���

 5.��    ��   : 2014��5��28��
   ��    ��   : w00167002
   �޸�����   : DTS2014051602857:sor���ƴ򿪣��û�ָ����23002��CSע�ᱻ��17��psע��
                ����17���ﵽ���������ƶ�����ʧ�ܡ������û���ָ����23002��CSʧ��
                4�κ�PS�ظ�ʧ��401��MMC���ظ�ָ�����������
 6.��    ��   : 2014��6��17��
   ��    ��   : z00234330
   �޸�����   : TQE����
 7.��    ��   : 2014��6��23��
   ��    ��   : z00161729
   �޸�����   : DSDS III����
 8.��    ��   : 2015��6��6��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
 9.��    ��   : 2015��4��22��
   ��    ��   : wx270776
   �޸�����   : DTS2015031602665:��MMA����Reg CNF��Ϣʱ����CL ATTACHע��״̬
*****************************************************************************/
VOS_VOID  NAS_MMC_SndRslt_PlmnSelection(
    NAS_MMC_PLMN_SELECTION_RESULT_ENUM_UINT32               enPlmnSelectionRslt
)
{

    NAS_MMC_RAT_SEARCH_INFO_STRU           *pstSearchRatInfo = VOS_NULL_PTR;
    VOS_UINT32                              ulCampFlg;
    VOS_UINT32                              ulRatNum;

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    MSCC_MMC_PLMN_ID_STRU                   stPlmnId;
    VOS_UINT32                              ulCurrentEventType;
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

    NAS_MMC_FSM_ID_ENUM_UINT32              enCurrentFsmId;

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-2, begin */
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32   ulPlmnSearchScene;
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-2, end */

    pstSearchRatInfo    = NAS_MMC_GetSearchRatInfo_PlmnSelection();

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();

    NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo(NAS_MMC_GetPlmnSelectionCtx_PlmnSelection());

    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        ulCampFlg = VOS_FALSE;
    }
    else
    {
        ulCampFlg = VOS_TRUE;
    }

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    stPlmnId.ulMcc     = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc     = NAS_MML_INVALID_MNC;
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    /* ����ǻ�ȡ������������ͻ�ȡ����ʧ�ܻظ���Ϣ */
    if (NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ) == ulCurrentEventType)
    {
        NAS_MMC_SndMsccAcqCnf(NAS_MSCC_PIF_ACQ_RESULT_FAILURE, &stPlmnId, 0);
    }

    /* Modified by z00234330 for coverity����, 2014-06-16, begin */
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    /* Modified by z00234330 for coverity����, 2014-06-16, end */


#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_TRUE == NAS_MMC_GetSrvTrigPlmnSearchFlag_PlmnSelection())
    {
        NAS_MMC_SndMsccSrvAcqCnfAccordingPlmnSearchRslt(enPlmnSelectionRslt);
    }
#endif

    /* �����ֶ������쳣����ֱ�ӻظ�����ʧ�� */
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType))
    {
        NAS_MMC_SndMsccUserSpecPlmnSearchCnf(NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL);

        /*���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬��*/
        NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

    #if (FEATURE_ON == FEATURE_LTE)
        if ( VOS_TRUE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
        {
            NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
        }
    #endif

        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_FORBLA_CHANGE);
    }

    /* �����ע�����������ע��ظ���Ϣ */
    if (VOS_TRUE == NAS_MMC_IsMsccRegReq_PlmnSelection())
    {
        if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            NAS_MMC_SndMsccRegCnf(NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection(), NAS_MSCC_PIF_REG_RESULT_SUCCESS, NAS_MML_GetCurrCampPlmnId(),
                                 NAS_MML_GetCurrCampArfcn());
        }
        else
        {
            if (VOS_TRUE == ulCampFlg)
            {
                NAS_MMC_SndMsccRegCnf(NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection(), NAS_MSCC_PIF_REG_RESULT_REG_FAILURE, NAS_MML_GetCurrCampPlmnId(),
                                 NAS_MML_GetCurrCampArfcn());
            }
            else
            {
                NAS_MMC_SndMsccRegCnf(NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection(), NAS_MSCC_PIF_REG_RESULT_ACQ_FAILURE, &stPlmnId, 0x0);
            }
        }
    }

    /* �����־ */
    NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(MMC_LMM_ATT_RSLT_BUTT);
    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

    ulRatNum = NAS_MMC_GetCoverageRatNum_PlmnSelection();

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-2, begin */
    ulPlmnSearchScene = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    NAS_MMC_SndPlmnSelectionRslt(enPlmnSelectionRslt, ulCampFlg, pstSearchRatInfo, ulRatNum, ulPlmnSearchScene);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-2, end */


    return;
}

#if   (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc_PlmnSelection
 ��������  : Lmm combined attach EPS��CS�ɹ�ע��Ĵ�����
 �������  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
             enCsRegRsltCause -  cs�򱻾�ԭ��ֵ
 �������  : penCsAddition    - CS��ĺ�������
             penPsAddition    - PS��ĺ�������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��7��
    ��    ��   : w00166186
    �޸�����   : DTS20120050302236:�ֶ�����ָ���������ڽ�ֹ�б��У�ע��ɹ���
                 û����LMM���͵�ЧPLMN
  3.��    ��   : 2012��5��10��
    ��    ��   : l65478
    �޸�����   : DTS2012050500988:CSע��ɹ�ʱ,����ɾ��forbid PLMN for GPRS��Ϣ
  4.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
  5.��    ��   : 2012��6��8��
    ��    ��   : l00130025
    �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨAPS/CDS��Ϣ���޷�����
  6.��    ��   : 2012��6��11��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1,����TAU�ɹ�ʱ����ҪDisable L
  7.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  8.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  9.��    ��   : 2013��12��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
 10.��    ��   : 2015��05��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
 11.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc_PlmnSelection(
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    if (VOS_TRUE == pstLmmAttachIndMsg->bitOpCnRslt)
    {
        if (MMC_LMM_ATT_CN_RSLT_COMBINED_EPS_IMSI == pstLmmAttachIndMsg->ulCnRslt)
        {
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltCsEpsSucc(pstLmmAttachIndMsg,
                          penCsAddition, penPsAddition);
        }
        else if (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == pstLmmAttachIndMsg->ulCnRslt)
        {
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(pstLmmAttachIndMsg,enCsRegRsltCause,
                          penCsAddition, penPsAddition);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc_PlmnSelection:Unexpected cn result!");
        }
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc_PlmnSelection: Unexpected Proc, ATTACH SUCC but bitOpCnRslt set to FALSE");
        /* ���õ�ǰע��״̬Ϊ�ɹ� */
        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* ������ע��ɹ��ϱ��������񷵻� */
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, begin */
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, end */

        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc_PlmnSelection: Update Reg state and Service state");
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);
        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */



        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }


    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());


    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedAttachInd_PlmnSelection
 ��������  : Lmm combined attach����Ĵ�����
 �������  : pstLmmAttachIndMsg - ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��8��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV ����
  3.��    ��   : 2011��12��13��
    ��    ��   : z00161729
    �޸�����   : DTS2011121302231:attach����#9/#10��Э��Ӧ�ð�other cause����
  4.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
                  additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                  �򲻸��µ�ǰ��additional action
  5.��    ��   : 2012��5��7��
    ��    ��   : w00166186
    �޸�����   : DTS20120050302236:�ֶ�����ָ���������ڽ�ֹ�б��У�ע��ɹ���
                 û����LMM���͵�ЧPLMN
  6.��    ��   : 2012��5��10��
    ��    ��   : l65478
    �޸�����   : DTS2012050500988:CSע��ɹ�ʱ,����ɾ��forbid PLMN for GPRS��Ϣ
  7.��    ��   : 2012��06��01��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  8.��    ��   : 2012��6��30��
    ��    ��   : w00176964
    �޸�����   : DTS2012063003332:����ע�ᵥ��ɹ�,ԭ��ֵ����Э��涨���б���,LNAS
                 ���Ľ��ΪCN_REJ,��ʱ��Ӧ��ɾ����ֹ�б�
  9.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
  10.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�DTS2012090401249
  11.��    ��   : 2013��1��11��
    ��    ��   : w00176964
    �޸�����   : DTS2013010706662:��������EPLMN�߼��жϺ���
 12.��    ��   : 2014��5��5��
  ��    ��   : w00242748
  �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
               ע��״̬���ϱ���
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_PlmnSelection(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    NAS_MMC_ConverLmmCombinedAttachRsltToMMLCause(pstLmmAttachIndMsg,&enPsRegRsltCause, &enCsRegRsltCause);

    switch (pstLmmAttachIndMsg->ulAttachRslt)
    {
        case MMC_LMM_ATT_RSLT_SUCCESS:
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc_PlmnSelection(pstLmmAttachIndMsg,
                       enCsRegRsltCause, &enCsAdditionalAction, &enPsAdditionalAction);

            break;

        case MMC_LMM_ATT_RSLT_FAILURE:
            if (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt)
            {
                enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
                enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

                /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
                NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
                /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
            }
            else
            {
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg,
                                      &enPsAdditionalAction, &enCsAdditionalAction);
            }
            break;

        case MMC_LMM_ATT_RSLT_ESM_FAILURE:
        case MMC_LMM_ATT_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_ATT_RSLT_T3402_RUNNING:
        case MMC_LMM_ATT_RSLT_TIMER_EXP:
        case MMC_LMM_ATT_RSLT_ACCESS_BAR:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_ATT_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_ATT_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_ATT_RSLT_AUTH_REJ:
        case MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW:
            NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg,
                                  &enPsAdditionalAction, &enCsAdditionalAction);
            break;

        case MMC_LMM_ATT_RSLT_CN_REJ:
            if ((VOS_TRUE == pstLmmAttachIndMsg->bitOpCnRslt)
             && (MMC_LMM_ATT_CN_RSLT_EPS_ONLY == pstLmmAttachIndMsg->ulCnRslt))
            {
                /* ��ATTACH��������Ϊ���ϣ�������Ӧ��ATTACH�������ΪEPS ONLY��
                   ��ԭ��ֵ��ΪЭ��24301 5.5.1.3.4.3�½����л���û��Я��ԭ��ֵ��
                   ��LMMͨ��ATTACH�����MMC_LMM_ATT_RSLT_CN_REJ֪ͨMMC��
                   ��Я����Ӧ��ATTACH�������͡�������Ӧ��ATTCH������͡�ԭ��ֵ��
                   ��Я�������ԭ����attach attempt counterֵ */
                NAS_MMC_ProcLmmCombinedAttachInd_AttRsltEpsOnlySucc(pstLmmAttachIndMsg,enCsRegRsltCause,
                                  &enCsAdditionalAction, &enPsAdditionalAction);

            }
            else
            {
                NAS_MMC_ProcCombinedAttachEpsRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg,
                                      &enPsAdditionalAction, &enCsAdditionalAction);
            }
            break;

        default:
            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_PlmnSelection:Unexpected attach result!");
            enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();
            enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
            break;
    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /* AdditionalAction��Ч������CS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

    /* �������Ҫ�ȴ���һ��ע����,�򲻸���ע��ԭ��ֵ,�ȴ�conut�ﵽ�������,
       �Ա����û�ָ�������ظ���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegCause_PlmnSelection(enPsRegRsltCause);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndOmEquPlmn();
    }


    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmMmcEpsOnlyAttachInd_PlmnSelection
 ��������  : Lmm attach����Ĵ�����
 �������  : ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��24��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�
  3.��    ��   : 2011��10��30��
    ��    ��   : z00161729
    �޸�����   : PhaseIII�޸ĺ�����
  4.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  5.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  6.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����
                  ����������NAS_MMC_ProcEpsRegFail����ΪNAS_MMC_ProcEpsAttachRegFail
                  ����ATTACH��ע��ԭ��ֵ����д���
  7.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  8.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
                  additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  9.��    ��   : 2012��5��7��
    ��    ��   : w00166186
    �޸�����   : DTS20120050302236:�ֶ�����ָ���������ڽ�ֹ�б��У�ע��ɹ���
                 û����LMM���͵�ЧPLMN
 10.��    ��   : 2012��5��10��
    ��    ��   : l65478
    �޸�����   : DTS2012050500988:CSע��ɹ�ʱ,����ɾ��forbid PLMN for GPRS��Ϣ
 11.��    ��   : 2012��06��01��
    ��    ��   : s46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
 12.��    ��   : 2012��06��01��
    ��    ��   : s00217060
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
 13.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
 14.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
 15.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
 16.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�DTS2012090401249
 17.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:������ָ������ע��ɹ����������ע��ɹ�ʱ��Ҳ��Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
18.��    ��   : 2013��1��11��
   ��    ��   : w00176964
   �޸�����   : DTS2013010706662:��������EPLMN�߼��жϺ���
19.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
20.��    ��   : 2013��12��10��
   ��    ��   : w00176964
   �޸�����   : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
21.��    ��   : 2014��5��6��
   ��    ��   : z00161729
   �޸�����   : DTS2014050602850:l������ע��eps�ɹ���csע�ᱻ#18�ܾ���disable lte��gu������ע��ɹ�����ָ����l csע�ᱻ#18�ܾ������磬l����eps����ע��ɹ���mmcû��disable lte
22.��    ��   : 2014��5��5��
   ��    ��   : w00242748
   �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                ע��״̬���ϱ���
23.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע����ATTACH (EPS ONLY)�ɹ����ϱ�ע��״̬
24.��    ��   : 2015��06��09��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע�������ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�
 25.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmMmcEpsOnlyAttachInd_PlmnSelection(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */
    VOS_UINT8                           ucSimCsRegStatus;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverLmmAttachRsltToMMLCause(pstLmmAttachIndMsg, &enRegRsltCause);

    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */
        /* ����EPLMN */
        if (VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

            /* ��LMM��PLMN ID��ʽת��ΪGU�ĸ�ʽ */
            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnInfo.astEquPlmnAddr);

            NAS_MMC_WriteEplmnNvim();
        }

        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmMmcEpsOnlyAttachInd_PlmnSelection: Update Reg state and Service state");
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

        /* EPS����ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, NAS_MMC_IsEpsEmergencyAttachType(pstLmmAttachIndMsg->ulReqType));

        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }
        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */

        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();


        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Added by w00176964 for APS����״̬֪ͨ����, 2014-4-7, begin */
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                  NAS_MML_GetSimPsRegStatus());
        /* Added by w00176964 for APS����״̬֪ͨ����, 2014-4-7, end */
    }
    else if ((MMC_LMM_ATT_RSLT_FAILURE == pstLmmAttachIndMsg->ulAttachRslt)
          && (VOS_FALSE == pstLmmAttachIndMsg->bitOpAtmpCnt))
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }
    else
    {
        enAdditionalAction= NAS_MMC_ProcEpsAttachRegFail(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enRegRsltCause);
    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    /* �������Ҫ�ȴ���һ��ע����,�򲻸���ע��ԭ��ֵ,�ȴ�conut�ﵽ�������,
       �Ա����û�ָ�������ظ���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enAdditionalAction)
    {
        NAS_MMC_SetPsRegCause_PlmnSelection(enRegRsltCause);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */
        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndOmEquPlmn();
    }

    return ;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmAttachInd_PlmnSelection
 ��������  : ����lmm��attach�������ʹ���attach_ind��Ϣ
 �������  : pstLmmAttachIndMsg - lmm attach ind��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��28��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmAttachInd_PlmnSelection(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    switch (pstLmmAttachIndMsg->ulReqType)
    {
        case MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI:

            /* ����lmm������attach��� */
            NAS_MMC_ProcLmmCombinedAttachInd_PlmnSelection(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_ONLY:

            /* ����lmm�ķ�����attach��EPS onlyע��Ľ�� */
            NAS_MMC_ProcLmmMmcEpsOnlyAttachInd_PlmnSelection(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_EMERGENCY:

            /* �ݲ�֧��δʵ�� */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_PlmnSelection:Unsupported attach req type!");
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_PlmnSelection:Unexpected attach req type!");
            break;

    }
    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnSelection
 ��������  : Lmm TAU����Ĵ�����
 �������  : ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��20��
    ��    ��   : W00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��24��
    ��    ��   : l00130025
    �޸�����   : PhaseII�޸�
  3.��    ��   : 2011��10��30��
    ��    ��   : z00161729
    �޸�����   : PhaseIII�޸ĺ�����
  4.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  5.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����
                  ����������NAS_MMC_ProcEpsRegFail����ΪNAS_MMC_ProcEpsTauRegFail
                  ����TAU��ע��ԭ��ֵ����д���
  6.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  7.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ�������.
                  additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  8.��    ��   : 2012��5��7��
    ��    ��   : w00166186
    �޸�����   : DTS20120050302236:�ֶ�����ָ���������ڽ�ֹ�б��У�ע��ɹ���
                 û����LMM���͵�ЧPLMN
  9.��    ��   : 2012��5��10��
    ��    ��   : l65478
    �޸�����   : DTS2012050500988:CSע��ɹ�ʱ,����ɾ��forbid PLMN for GPRS��Ϣ
 10.��    ��   : 2012��06��01��
    ��    ��   : s46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
 11.��    ��   : 2012��06��01��
    ��    ��   : s00217060
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
 12.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
 13.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
 14.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
 15.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�DTS2012090401249
 16.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:������ָ������ע��ɹ����������ע��ɹ�ʱ��Ҳ��Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
 17.��    ��   : 2013��1��11��
    ��    ��   : w00176964
    �޸�����   : DTS2013010706662:��������EPLMN�߼�����λ��
 18.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 19.��    ��   : 2013��12��10��
     ��    ��  : w00176964
     �޸�����  : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
 20.��    ��   : 2014��5��6��
    ��    ��   : z00161729
    �޸�����   : DTS2014050602850:l������ע��eps�ɹ���csע�ᱻ#18�ܾ���disable lte��gu������ע��ɹ�����ָ����l csע�ᱻ#18�ܾ������磬l����eps����ע��ɹ���mmcû��disable lte
 21.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
 22.��    ��   : 2014��5��14��
    ��    ��   : w00242748
    �޸�����   : DTS2014051206381:ö��ֵʹ�ò���
 23.��    ��   : 2015��4��18��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
 24.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע����(EPS ONLY)�ɹ����ϱ�ע��״̬
 25.��    ��   : 2015��06��09��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע�������ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�
 26.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnSelection(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    VOS_UINT32                          ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU               *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stLEplmnAddr;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enAdditionalAction;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU           stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */
    VOS_UINT8                           ucSimCsRegStatus;

    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8          enCsRegAdditionalAction;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverTauResultToMMLCause(pstLmmTauIndMsg, &enRegRsltCause);

    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* ����ע������Ϣ */
        NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

        /* ����ע��������ע����Ϣ�� */
        NAS_MMC_UpdatePlmnRegInfoList(NAS_MML_GetCurrCampPlmnId(), NAS_MMC_REG_DOMAIN_EPS, NAS_MML_REG_FAIL_CAUSE_NULL);

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */
        /* ����EPLMN */
        if (VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

            /* ��LMM��PLMN ID��ʽת��ΪMMC�ĸ�ʽ */
            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnAddr.astEquPlmnAddr));

            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, stLEplmnAddr.astEquPlmnAddr);

            NAS_MMC_WriteEplmnNvim();
        }

        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
        NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnSelection: Update Reg state and Service state");
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

        /* EPS����ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, VOS_FALSE);

        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        /* �˴�����CS additionԭ��������TAU��EPS�ɹ�ʱ,LMM����T3411�ٴγ���TAU������,
           �û�Detach CS,LMM��ֱ�ӱ�TAU�ɹ�,���ٳ�������TAU */
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON);

        /* ���CS����ע�����CS����Ч�����CSע��״̬ΪNAS_MML_REG_NOT_REGISTERED_NOT_SEARCH */
        ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (VOS_TRUE == ucSimCsRegStatus))
        {
            NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_EPS_ONLY_ATTACH);

            NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
        }

        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */

        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Added by w00176964 for APS����״̬֪ͨ����, 2014-4-7, begin */
        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                  NAS_MML_GetSimPsRegStatus());
        /* Added by w00176964 for APS����״̬֪ͨ����, 2014-4-7, end */
    }
    else if ((MMC_LMM_TAU_RSLT_FAILURE == pstLmmTauIndMsg->ulTauRst)
          && (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt))
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }
    else if (MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC == pstLmmTauIndMsg->ulTauRst)
    {
        NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          &enAdditionalAction, &enCsRegAdditionalAction);
    }
    else
    {
        enAdditionalAction = NAS_MMC_ProcEpsTauRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);

        NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(enRegRsltCause);
    }

    /* �������Ҫ�ȴ���һ��ע����,�򲻸���ע��ԭ��ֵ,�ȴ�conut�ﵽ�������,
       �Ա����û�ָ�������ظ���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enAdditionalAction)
    {
        NAS_MMC_SetPsRegCause_PlmnSelection(enRegRsltCause);
    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */
        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndOmEquPlmn();
    }

    return ;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc_PlmnSelection
 ��������  : Lmm TAU result���ΪMMC_LMM_TAU_RSLT_SUCCESS�Ĵ�����
 �������  : ID_LMM_MMC_TAU_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��07��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��7��
    ��    ��   : w00166186
    �޸�����   : DTS20120050302236:�ֶ�����ָ���������ڽ�ֹ�б��У�ע��ɹ���
                 û����LMM���͵�ЧPLMN
  3.��    ��   : 2012��5��10��
    ��    ��   : l65478
    �޸�����   : DTS2012050500988:CSע��ɹ�ʱ,����ɾ��forbid PLMN for GPRS��Ϣ
  4.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
  5.��    ��   : 2012��6��8��
    ��    ��   : l00130025
    �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨAPS/CDS��Ϣ���޷�����
  6.��    ��   : 2012��6��11��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1,����TAU�ɹ�ʱ����ҪDisable L
  7.��    ��   : 2012��7��27��
    ��    ��   : s00217060
    �޸�����   : For CS/PS mode 1,��Disable LTEԭ��ֵ
  8.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:������ָ������ע��ɹ����������ע��ɹ�ʱ��Ҳ��Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
  9.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 10.��    ��   : 2013��3��30��
    ��    ��   : w00176964
    �޸�����   : DTS2013030802929,������RAU��Ҫ֪ͨLMM
 11.��    ��   : 2013��12��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
 12.��    ��   : 2015��05��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
 13.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc_PlmnSelection(
    LMM_MMC_TAU_RESULT_IND_STRU                            *pstLmmTauIndMsg,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penCsAddition,
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                   *penPsAddition
)
{
    if (VOS_TRUE == pstLmmTauIndMsg->bitOpCnRst)
    {
        /* CS+PS��������TAUʱ,�����Ƿ�Я��CS CAUSEֵ,����Ϊ����ע��ɹ� */
        if ((MMC_LMM_COMBINED_TA_LA_UPDATED == pstLmmTauIndMsg->ulCnRst)
         || (MMC_LMM_COMBINED_TA_LA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst)
         || (MMC_LMM_CS_PS_PERIODIC_UPDATING == pstLmmTauIndMsg->ulReqType))
        {
            /* �����ཻ��EPS��CS��ע��ɹ� */
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltCsEpsSucc(pstLmmTauIndMsg,
                          penCsAddition, penPsAddition);

        }
        else if ((MMC_LMM_TA_UPDATED == pstLmmTauIndMsg->ulCnRst)
              || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst))
        {
            /* �����ཻ��EPS�ɹ�CSʧ�ܣ���ԭ��ֵΪЭ��24301 5.5.3.3.4.3�½����� */
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc(pstLmmTauIndMsg,enCsRegRsltCause,
                          penCsAddition, penPsAddition);

        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc_PlmnSelection:Unexpected cn result!");
        }
    }
    else
    {
        /* ������ע��ɹ��ϱ��������񷵻� */
        *penPsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, begin */
        *penCsAddition = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;
        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, end */

        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, begin */
        /* LTE TAU�����̣��ñ�־λ */
        NAS_MMC_SetLteUnrealRegProcFlg(VOS_TRUE);
        NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc_PlmnSelection: Update Reg state and Service state");
        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NORMAL_SERVICE);
        /* Modified by z00359541 for MSCC_IMSA_SERVICE_CHANGE_IND �ӿڵ���, 2016-4-5, end */

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    }

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedTauResultInd_PlmnSelection
 ��������  : Lmm TAU����Ĵ�����
 �������  : ID_LMM_MMC_TAU_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��27��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��8��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV ����
  3.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  4.��    ��   : 2011��12��13��
    ��    ��   : z00161729
    �޸�����   : DTS2011121302231:attach����#9/#10��Э��Ӧ�ð�other cause����
  5.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
                   additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  6.��    ��   : 2012��5��7��
    ��    ��   : w00166186
    �޸�����   : DTS20120050302236:�ֶ�����ָ���������ڽ�ֹ�б��У�ע��ɹ���
                 û����LMM���͵�ЧPLMN
  7.��    ��   : 2012��5��10��
    ��    ��   : l65478
    �޸�����   : DTS2012050500988:CSע��ɹ�ʱ,����ɾ��forbid PLMN for GPRS��Ϣ
  8.��    ��   : 2012��05��28��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  9.��    ��   : 2012��6��30��
    ��    ��   : w00176964
    �޸�����   : DTS2012063003332:����ע�ᵥ��ɹ�,ԭ��ֵ����Э��涨���б���,LNAS
                 ���Ľ��ΪCN_REJ,��ʱ��Ӧ��ɾ����ֹ�б�
 10.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
  11.��    ��   : 2012��8��21��
     ��    ��   : z00161729
     �޸�����   : DCM������������������޸�DTS2012090401249
  12.��    ��   : 2013��1��11��
     ��    ��   : w00176964
     �޸�����   : DTS2013010706662:��������EPLMN�߼�����λ��
  13.��    ��   : 2014��5��5��
     ��    ��   : w00242748
     �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                  ע��״̬���ϱ���
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_PlmnSelection(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegRsltCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;

     /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
     NAS_MML_EQUPLMN_INFO_STRU                              stSndEquPlmnInfo;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;
    enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_BUTT;

    NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(pstLmmTauIndMsg, &enPsRegRsltCause, &enCsRegRsltCause);

    switch (pstLmmTauIndMsg->ulTauRst)
    {
        case MMC_LMM_TAU_RSLT_SUCCESS:
            NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltSucc_PlmnSelection(pstLmmTauIndMsg,
                       enCsRegRsltCause, &enCsAdditionalAction, &enPsAdditionalAction);

            break;

        case MMC_LMM_TAU_RSLT_FAILURE:
            if (VOS_FALSE == pstLmmTauIndMsg->bitOpAtmpCnt)
            {
                enPsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;
                enCsAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON;

                /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
                NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, VOS_FALSE, NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
                /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
            }
            else
            {
                /* EPS��CSע���ʧ�� */
                NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                              &enPsAdditionalAction, &enCsAdditionalAction);
            }
            break;

        case MMC_LMM_TAU_RSLT_MO_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_MT_DETACH_FAILURE:
        case MMC_LMM_TAU_RSLT_T3402_RUNNING:
        case MMC_LMM_TAU_RSLT_TIMER_EXP:
        case MMC_LMM_TAU_RSLT_ACCESS_BARED:
        case MMC_LMM_TAU_RSLT_FORBID_PLMN:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_RPOS:
        case MMC_LMM_TAU_RSLT_FORBID_PLMN_FOR_GPRS:
        case MMC_LMM_TAU_RSLT_FORBID_TA_FOR_ROAMING:
        case MMC_LMM_TAU_RSLT_AUTH_REJ:
            /* EPS��CSע���ʧ�� */
            NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                          &enPsAdditionalAction, &enCsAdditionalAction);
            break;

        case MMC_LMM_TAU_RSLT_CN_REJ:
            if ((VOS_TRUE == pstLmmTauIndMsg->bitOpCnRst)
             && ((MMC_LMM_TA_UPDATED == pstLmmTauIndMsg->ulCnRst)
              || (MMC_LMM_TA_UPDATED_ISR_ACTIVATED == pstLmmTauIndMsg->ulCnRst)))
            {
                /* ��TAU��������Ϊ���ϣ�������Ӧ��TAU�������ΪTA UPDATED��
                   ��ԭ��ֵ��ΪЭ��24301 5.5.3.3.4.3�½����л���û��Я��ԭ��ֵ��
                   ��LMMͨ��TAU�����MMC_LMM_TAU_RSLT_CN_REJ֪ͨMMC����Я����Ӧ
                   ��TAU�������͡�������Ӧ��TAU������͡�ԭ��ֵ����Я�������ԭ
                   ����tau attempt counterֵ */
                NAS_MMC_ProcLmmCombinedTauResultInd_TauRsltEpsOnlySucc(pstLmmTauIndMsg,enCsRegRsltCause,
                                  &enCsAdditionalAction, &enPsAdditionalAction);
            }
            else
            {
                /* EPS��CSע���ʧ�� */
                NAS_MMC_ProcCombinedTauEpsRegFail(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                              &enPsAdditionalAction, &enCsAdditionalAction);

            }
            break;

        case MMC_LMM_TAU_RSLT_T3402_RUNNING_EPS_ONLY_SUCC:
            NAS_MMC_ProcCombinedEpsRegFailCauseT3402RunningEpsOnlySucc(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg,
                                              &enPsAdditionalAction, &enCsAdditionalAction);
            break;

        default:
            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedTauResultInd_PlmnSelection:Unexpected attach result!");
            enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnSelection();
            enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnSelection();
            break;

    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(enPsAdditionalAction);
    }

    /* AdditionalAction��Ч������CS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(enCsAdditionalAction);
    }

     /* �������Ҫ�ȴ���һ��ע����,�򲻸���ע��ԭ��ֵ,�ȴ�conut�ﵽ�������,
    �Ա����û�ָ�������ظ���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT != enPsAdditionalAction)
    {
        NAS_MMC_SetPsRegCause_PlmnSelection(enPsRegRsltCause);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn_PlmnSelection())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */
        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);

        NAS_MMC_SndOmEquPlmn();
    }


    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmTauResultInd_PlmnSelection
 ��������  : Lmm TAU����Ĵ�����
 �������  : ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV����:������tau��������Ϻͷ�����
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmTauResultInd_PlmnSelection(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    switch (pstLmmTauIndMsg->ulReqType)
    {
        case MMC_LMM_COMBINED_TA_LA_UPDATING:
        case MMC_LMM_COMBINED_TA_LA_WITH_IMSI:
        case MMC_LMM_CS_PS_PERIODIC_UPDATING:

            /* ����lmm������tau��� */
            NAS_MMC_ProcLmmCombinedTauResultInd_PlmnSelection(pstLmmTauIndMsg);
            break;

        case MMC_LMM_TA_UPDATING:
        case MMC_LMM_PS_PERIODIC_UPDATING:

            /* ����lmm�ķ�����tau��EPS onlyע��Ľ�� */
            NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnSelection(pstLmmTauIndMsg);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmTauResultInd_PlmnSelection:Unexpected tau req type!");
            break;

    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsConnRelInd
 ��������  : �ڵȴ�EPS��·�ͷŵ�ʱ���յ�ID_LMM_MMC_TAU_RESULT_IND�ĵĴ���
 �������  : ulEventType:��Ϣ����
             pstMsg: ID_LMM_MMC_TAU_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��12��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32          enCurrentFsmId;
    VOS_UINT32                          ulCurrentEventType;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����ע������� ,�û�����syscfg��Ҫ����������MMC�������ͷ����ӣ�
       �ڵȴ������ͷ�״̬��L���ܻ���ע��������Ҫ���� */
    NAS_MMC_ProcLmmTauResultInd_PlmnSelection(pstLmmTauIndMsg);

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /*���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬��*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsConnRelInd
 ��������  : �ڵȴ�EPS��·�ͷŵ�ʱ���յ�ID_LMM_MMC_ATTACH_IND�ĵĴ���
 �������  : ulEventType:��Ϣ����
             pstMsg: ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��12��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2015��4��22��
    ��    ��   : wx270776
    �޸�����   : DTS2015031602665:��CL ATTACHע��״̬����ȫ�ֱ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    VOS_UINT32                                              ulCurrentEventType;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode;

    enUeOperationMode   =  NAS_MML_GetLteUeOperationMode();
    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    if ( VOS_TRUE == NAS_MMC_IsNeedUpdateLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus) )
    {
        NAS_MMC_SetLmmAttachClRegStatus_PlmnSelection(pstLmmAttachIndMsg->enClAttRegStatus);
    }

    /* LMM������δ�ظ�search cnfʱ�յ��û�detach ps����󣬺���������ע���mmc�ظ�attach result
       ΪMMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW���������������MMC_LMM_ATT_TYPE_BUTT��
       MMC��Ҫ���ݵ�ǰue operation mode�������������¸�ֵ */
    if ((MMC_LMM_ATT_TYPE_BUTT == pstLmmAttachIndMsg->ulReqType)
     && (MMC_LMM_ATT_RSLT_PS_ATT_NOT_ALLOW == pstLmmAttachIndMsg->ulAttachRslt))
    {
        pstLmmAttachIndMsg->ulReqType = NAS_MMC_ConvertLmmAttachReqType(enUeOperationMode);
    }

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����ע������� ,�û�����syscfg��Ҫ����������MMC�������ͷ����ӣ�
      �ڵȴ������ͷ�״̬��L���ܻ���ע��������Ҫ���� */
    NAS_MMC_ProcLmmAttachInd_PlmnSelection(pstLmmAttachIndMsg);

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    if (NAS_MMC_FSM_PLMN_SELECTION != enCurrentFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();
    if (VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId,ulCurrentEventType))
    {
        enCsRegCause = NAS_MMC_GetCsRegCause_PlmnSelection();
        enPsRegCause = NAS_MMC_GetPsRegCause_PlmnSelection();

        if (VOS_TRUE == NAS_MMC_ProcUserSearchRegRslt_PlmnSelection(enCsRegCause,enPsRegCause))
        {
            /*���������ϢΪ��ͨ���������󣬺������µ��û�����ʱ�����Դ�ϸ�״̬��*/
            NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedEnableLte_PlmnSelection
 ��������  : ���ݲ�ͬ�����������ж��Ƿ���Ҫ Enable L
 �������  : enPlmnSearchScene

 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ Enable L
              VOS_TRUE: ��Ҫ Enable L
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��06��02��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��09��12��
   ��    ��   : z00161729
   �޸�����   : DTS2012082702662��disable��enable lte�����жϵ�ǰsyscfg�Ƿ�֧��L
 3.��    ��   : 2012��11��10��
   ��    ��   : s00217060
   �޸�����   : DTS2012102902559��USIM��ʱ������ҪEnable Lte;SIM��ʱ����Ҫ
 4.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 5.��    ��   : 2015��1��5��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedEnableLte_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    VOS_UINT32                                              ulIsPlmnSupportDam;


    enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }

    /* �����SIM��������ҪEnable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* PS����Ч, ����Ҫ���� Enable L */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus() )
    {
        return VOS_FALSE;
    }

    /* PS��������ע��,����Ҫ���� Enable L */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* ����������NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE,����Ҫ���� Enable L */
    if ( NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE == enPlmnSearchScene )
    {
        return VOS_FALSE;
    }

    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* ���֮ǰdisable lte��������֧��DAM�����磬�ҽ�ֹ���뼼�������б�����9014 nvδ������
       ������enable lte,AT&T LTE-BTR-1-1840����Ҫ��ֻ��ֹ310410 lte���磬����lte������ã�
       �������ɾ���������������Ҫ���ԣ����Կ���DAM nv����в��� */
    ulIsPlmnSupportDam = NAS_MML_IsPlmnSupportDam(NAS_MMC_GetDisabledLtePlmnId());

    if ((VOS_FALSE == NAS_MML_GetAddDamPlmnInDisablePlmnWithRatListFlag())
      && (VOS_TRUE == ulIsPlmnSupportDam))
    {
        return VOS_FALSE;
    }

    /* �Ѿ�Disable L,��Ҫ���� Enable L */
    if ( (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapabilityStatus)
      || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapabilityStatus) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNotLastPlmnNeedRelEpsConn_PlmnSelection
 ��������  : �ж��Ƿ���Ҫ�ͷ�EPS����
 �������  : ��

 �������  : ��
 �� �� ֵ  : VOS_FALSE:�����һ�����磬�����ͷ�����
              VOS_TRUE: �������һ�����磬��Ҫ�ͷ�EPS����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��11��22��
   ��    ��   : t00212959
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��8��27��
   ��    ��   : l00208543
   �޸�����   : Coverity
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsDisableLteNeedWaitEpsConnRel_PlmnSelection(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;

	/* ����汾Coverity���� */
	PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
    {
        /* ���һ������*/
        if (VOS_FALSE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
        {
            /* �ظ�״̬���˳��ɹ� */
            NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

            /* ֱ���˳���ǰ״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_FALSE;
        }

        NAS_MMC_SetRelRequestFlag_PlmnSelection(VOS_TRUE);

        NAS_MMC_SndLmmRelReq();
    }

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection
 ��������  : �յ�ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ��ʱ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection(
     VOS_UINT32                         ulEventType,
     struct MsgCB                      *pstMsg
)
{
    /* ��������״̬�������ϢΪ��ͨ���� */
    NAS_MMC_SaveCommonPlmnSrchEntryMsg_PlmnSelection();

#if (FEATURE_ON == FEATURE_LTE)
    /* ֪֪ͨͨLMM��ǰ�ڷ��û�ָ������ģʽ */
    NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify();
#endif

    /* �ظ�TAFMMC_SPEC_PLMN_SEARCH_ABORT_CNF��MMA */
    NAS_MMC_SndMsccSpecPlmnSearchAbortCnf();
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitCsPsRegRsltInd
 ��������  : ������ע����ʱ����OOS RRMM_LIMIT_SERVICE_CAMP_IND��Ϣ�Ĵ���
 �������  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND��Ϣ
             ulEventType - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
             VOS_FALSE:���ش���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��15��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection(ulEventType, pstMsg);

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitRrcConnRelInd
 ��������  : �����������ͷ�ʱ����OOS RRMM_LIMIT_SERVICE_CAMP_IND��Ϣ�Ĵ���
 �������  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND��Ϣ
             ulEventType - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
             VOS_FALSE:���ش���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��15��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection(ulEventType, pstMsg);

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection
 ��������  : ����ʱ����OOS��Ϣ�Ĵ���
 �������  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND��Ϣ
             ulEventType - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:���ش���ɹ�
             VOS_FALSE:���ش���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��27��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��5��28��
    ��    ��   : z00234330
    �޸�����   : covertity�޸�
  3.��    ��   : 2014��11��8��
    ��    ��   : z00161729
    �޸�����   : ���������Ż���Ŀ�޸�
  4.��    ��   : 2015��10��21��
    ��    ��   : s00217060
    �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_3.0�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_LIMIT_SERVICE_CAMP_IND_STRU        *pstRrmmLimitCampOnMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU               stDestPlmn;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pastIntraPlmnSrchInfo = VOS_NULL_PTR;
    VOS_UINT32                               ulIndex;

    pstRrmmLimitCampOnMsg = (RRMM_LIMIT_SERVICE_CAMP_IND_STRU *)pstMsg;

    pastIntraPlmnSrchInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                             sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);
    /* �����ڴ�ʧ�� */
    if (VOS_NULL_PTR == pastIntraPlmnSrchInfo)
    {
        return VOS_TRUE;
    }

    /* modified by z00234330 for coverity�޸� 2014-05-28 begin */
    PS_MEM_SET(&stDestPlmn, 0x00, sizeof(stDestPlmn));
    /* modified by z00234330 for coverity�޸� 2014-05-28 end */

    NAS_MMC_InitSearchedPlmnListInfo(pastIntraPlmnSrchInfo);

    /* ת��W�µ������ʽ */
    NAS_MMC_UpdateSearchedPlmnListInfo(VOS_NULL_PTR, &(pstRrmmLimitCampOnMsg->stPlmnIdList), pastIntraPlmnSrchInfo);

    /* ɾ���б��н�ֹ��PLMN */
    NAS_MMC_DelForbPlmnFromAsSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* �ֶ�����ģʽ��ɾ�����û�ָ����PLMN */
    NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* ��ά�ɲ���Ϣ���� */
    NAS_MMC_LogAsPlmnList(pastIntraPlmnSrchInfo);

    if (VOS_TRUE == NAS_MMC_IsExistAvailPlmnInSearchedPlmnList(pastIntraPlmnSrchInfo))
    {
        for (ulIndex = 0; ulIndex < NAS_MML_MAX_RAT_NUM; ulIndex++)
        {
            NAS_MMC_UpdatePlmnSearchList_PlmnSelection(&(pastIntraPlmnSrchInfo[ulIndex]),
                                                       VOS_TRUE,
                                                       VOS_TRUE);
        }

        /* ����������һ����Ҫ����������ʱ�������������������򣬼����ȴ� */
        if (VOS_TRUE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
        {
            /* ��ǰӦ�ÿ϶�������������,�������������,���ô��� */
            if (VOS_TRUE == NAS_MML_IsRrcConnExist())
            {
                /* ���ݵ�ǰ��ͬ�Ľ��뼼��,�����ͷ�����,Ǩ�Ƶ���ͬ�ĵȴ������ͷŵ�L2״̬��������������ʱ�� */
                NAS_MMC_SndRelReq_PlmnSelection(NAS_MML_NET_RAT_TYPE_WCDMA);
            }
        }
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateOosAreaLostPlmnSearchInfo_PlmnSelection
 ��������  : ���ݽ�����ϱ��������OOS������������б�
 �������  : pstPlmnSearchReq
 �������  : pstPlmnSelectionListInfo
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��11��28��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateOosAreaLostPlmnSearchInfo_PlmnSelection(
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstPlmnSearchReq,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enPlmnType;
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    enPlmnType = NAS_MMC_PLMN_TYPE_AVAIL_PLMN;

    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        if (NAS_MML_NET_RAT_TYPE_BUTT == pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType)
        {
            continue;
        }

        stPrioRatList.aucRatPrio[0] = pstPlmnSearchReq->astInterPlmnSearchInfo[i].enRatType;
        stPrioRatList.ucRatNum      = 1;

        for (j = 0; j < pstPlmnSearchReq->astInterPlmnSearchInfo[i].ulHighPlmnNum; j++)
        {
            NAS_MMC_InsertPlmnToPlmnSelectionListHead(&pstPlmnSearchReq->astInterPlmnSearchInfo[i].astHighPlmnList[j],
                                                      enPlmnType,
                                                      &stPrioRatList,
                                                      pstPlmnSelectionListInfo);
        }

        for (j = 0; j < pstPlmnSearchReq->astInterPlmnSearchInfo[i].ulLowPlmnNum; j++)
        {
            NAS_MMC_InsertPlmnToPlmnSelectionListHead(&pstPlmnSearchReq->astInterPlmnSearchInfo[i].astLowPlmnList[j].stPlmnId,
                                                      enPlmnType,
                                                      &stPrioRatList,
                                                      pstPlmnSelectionListInfo);
        }
    }

    /* ��ά�ɲ⣬���ѡ���б���Ϣ */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionListInfo);

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection
 ��������  : ����״̬���б����
 �������  : ulEventType:�¼�
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 1.��    ��   : 2012��11��6��
   ��    ��   : z40661
   �޸�����   : DTS2012110501311
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     /* ��¼��Ҫ�˳���ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnSelection(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnSearchScene_PlmnSelection
 ��������  : ״̬�������ϢΪ�ڲ�����ʱ����ȡ��ǰ����״̬������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��12��24��
   ��    ��   : z00161729
   �޸�����   : SVLTE֧��NCELL����

 2.��    ��   : 2015��6��3��
   ��    ��   : w00167002
   �޸�����   : ���ӿ���ѡ�����û�ָ��ѡ�������Ľ�����

 3.��    ��   : 2015��12��12��
   ��    ��   : n00355355
   �޸�����   : CL��������MSCCģ���plmn search������Ϣ�л����������
*****************************************************************************/
NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetPlmnSearchScene_PlmnSelection(VOS_VOID)
{
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU *pstInterPlmnSearchReq = VOS_NULL_PTR;
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg           = VOS_NULL_PTR;
    MSCC_MMC_ACQ_REQ_STRU              *pstAcqReq             = VOS_NULL_PTR;

    /* ��ȡ״̬���������Ϣ��Ϣ */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    if (VOS_TRUE == NAS_MMC_IsInterPlmnSearch_PlmnSelection())
    {
        pstInterPlmnSearchReq = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
        return pstInterPlmnSearchReq->enPlmnSearchScene;
    }

    /* ����ѡ������ */
    if (pstEntryMsg->ulEventType == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SEARCH_REQ))
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON;
    }

    /* �û�ָ������������ */
    if ( pstEntryMsg->ulEventType == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ) )
    {
        return NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH;
    }

    /* CL��������MSCCģ���plmn search������Ϣ�л���������� */
    if (pstEntryMsg->ulEventType == NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ))
    {
        pstAcqReq = (MSCC_MMC_ACQ_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

        if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstAcqReq->enAcqReason)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON;
        }

        if (NAS_MSCC_PIF_ACQ_REASON_HIGH_PRIORITY == pstAcqReq->enAcqReason)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH;
        }

        if (NAS_MSCC_PIF_ACQ_REASON_OTHER == pstAcqReq->enAcqReason)
        {
            return NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST;
        }

        return NAS_MMC_PLMN_SEARCH_SCENE_BUTT;

    }

    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetPlmnSearchScene_PlmnSelection, UNKNOWN SCENE!");

    /* �����쳣�򷵻���Ч���������� */
    return NAS_MMC_PLMN_SEARCH_SCENE_BUTT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsInterPlmnSearch_PlmnSelection
 ��������  : �жϵ�ǰ����״̬�������Ϣ�Ƿ����ڲ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ڲ�������Ϣ
             VOS_FALSE - �����ڲ�������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsInterPlmnSearch_PlmnSelection(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;

   /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if (MMCMMC_INTER_PLMN_SEARCH_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection
 ��������  : �ж��Ƿ���Ҫ�������б���available���������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��8��
    ��    ��   : z00161729
    �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedSortAvailablePlmnSelectionList_PlmnSelection(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstPrioRatList       = NAS_MML_GetMsPrioRatList();

    if (VOS_FALSE == NAS_MMC_GetRoamPlmnSelectionSortActiveFlg())
    {
        return VOS_TRUE;
    }


    for (i = 0 ; i < pstPrioRatList->ucRatNum; i++)
    {
        if (VOS_TRUE == NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(pstPrioRatList->aucRatPrio[i]))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection
 ��������  : �ж��Ƿ����㿪�����������Ƿ���Ҫ�������б��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ��������
             VOS_FALSE - ����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��8��
    ��    ��   : z00161729
    �޸�����   : ���������Ż���Ŀ�޸�

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    enPlmnSearchScene                   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if (NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE == enPlmnSearchScene)

    {
        enPlmnSearchScene               = NAS_MMC_GetBackUpNoRfPlmnSearchScene_PlmnSelection();
    }

    /* ���Կ� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection: Test SIM, No need sort");
        return VOS_FALSE;
    }

    /* ���������Ż����ƹرղ����� */
    if (VOS_FALSE == NAS_MMC_GetRoamPlmnSelectionSortActiveFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection: NV not active, No need sort");
        return VOS_FALSE;
    }

    /* �ֶ�����ģʽ���������Ϣ */
    if (NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection: Manual Selection mode, No need sort");
        return VOS_FALSE;
    }

    /* ��ģʽ���Ź�һ��������Ҫ�ŵڶ��� */
    if (VOS_TRUE == NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(enRat))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection: Already Sorted, No need sort again");
        return VOS_FALSE;
    }

    /* ֮ǰ������ϱ���searched plmn info ind��search cnf��
       ���ں�rplmn��hplmn��ͬ����������磬����Ϊ��������ԭ�����̣�����ϵ�ǰ���� */
    if (VOS_TRUE == NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection: report RPLMN or HPLMN, No need sort again");
        return VOS_FALSE;
    }


    /* �����������ƿ��������ڿ���ѡ��������������ѡ����SYSCFG������ѡ���������������� */
    if ((NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_HISTORY_PLMN_SEARCH != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET != enPlmnSearchScene))
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection: PlMN Srch Scene incorrect, No need sort again");
        return VOS_FALSE;
    }

    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsNeedSortRoamPlmnSelectionList_PlmnSelection: return TRUE");

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedStopPlmnSearchRcvRrcSearchedPlmnInfoInd_PlmnSelection
 ��������  : �յ�RRMM_SEARCHED_PLMN_INFO_IND�ж��Ƿ���Ҫ��ϵ�ǰ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ��ϵ�ǰ����
             VOS_TRUE:��Ҫ��ϵ�ǰ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��10��28��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��08��
   ��    ��   : zwx247453
   �޸�����   : ���Coverity�澯
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedStopPlmnSearchRcvRrcSearchedPlmnInfoInd_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg
)
{
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstCurrSearchingPlmn = VOS_NULL_PTR;
    VOS_UINT32                                              ulIndex;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnIdWithRat;
    VOS_UINT32                                              ulIsExistDiffMccWithCurrSearchingMcc;
    VOS_UINT8                                               ucIsExistSearchedPlmnPrioCurrSearchingPlmn;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stCurrSearchRoamPlmnInfo;
    NAS_MMC_ROAM_PLMN_INFO_STRU                             stSearchedExistRoamPlmnInfo;
    RRMM_SEARCHED_PLMN_INFO_IND_STRU                        stSearchedPlmnInfoMsg;
    VOS_UINT8                                               ucAllSearchedPlmnForbiddenPlmnFlag;
    NAS_MMC_ROAM_PLMN_TYPE_ENUM_UINT8                       enRoamPlmnType;

    PS_MEM_SET(&stCurrSearchRoamPlmnInfo, 0, sizeof(stCurrSearchRoamPlmnInfo));
    PS_MEM_SET(&stSearchedExistRoamPlmnInfo, 0, sizeof(stSearchedExistRoamPlmnInfo));
    PS_MEM_SET(&stPlmnIdWithRat, 0, sizeof(stPlmnIdWithRat));
    PS_MEM_SET(&stSearchedPlmnInfoMsg, 0, sizeof(stSearchedPlmnInfoMsg));
    PS_MEM_CPY(&stSearchedPlmnInfoMsg, pstSearchedPlmnInfoMsg, sizeof(stSearchedPlmnInfoMsg));

    pstCurrSearchingPlmn                       = NAS_MMC_GetCurrSearchingPlmn_PlmnSelection();
    ulIsExistDiffMccWithCurrSearchingMcc       = VOS_FALSE;
    ucIsExistSearchedPlmnPrioCurrSearchingPlmn = VOS_FALSE;
    pstPlmnSelectionList                       = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();
    ucAllSearchedPlmnForbiddenPlmnFlag         = VOS_TRUE;
    enRoamPlmnType                             = NAS_MMC_ROAM_PLMN_TYPE_BUTT;

    stCurrSearchRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = pstCurrSearchingPlmn->stPlmnId.ulMcc;
    stCurrSearchRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = pstCurrSearchingPlmn->stPlmnId.ulMnc;
    stCurrSearchRoamPlmnInfo.stPlmnWithRat.enRat          = pstCurrSearchingPlmn->enRat;
    stCurrSearchRoamPlmnInfo.enNetStatus                  = NAS_MMC_NET_STATUS_NO_SEARCHED;
    stCurrSearchRoamPlmnInfo.enPlmnType                   = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stCurrSearchRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);
    stCurrSearchRoamPlmnInfo.aucLac[0]                    = NAS_MML_LAC_LOW_BYTE_INVALID;
    stCurrSearchRoamPlmnInfo.aucLac[1]                    = NAS_MML_LAC_HIGH_BYTE_INVALID;


    /* �����ָʾ���ڵ������rplmn��hplmn��ͬһ����������γ����򲻴������Ϣ*/
    for (ulIndex = 0; ulIndex < stSearchedPlmnInfoMsg.ulAvailPlmnNum; ulIndex++)
    {


        /* �����ǰ�����������searched plmn info ind��Ϣ�е�plmn��ͬ�򲻴���
           �Ƚ�����search cnf success��Ϣ*/
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstCurrSearchingPlmn->stPlmnId, (NAS_MML_PLMN_ID_STRU *)&stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].stPlmnId))
        {
            return VOS_FALSE;
        }

        /* �ж�searched plmn info ind�д������������Ƿ����������������ͬMCC,
           ���������ͬMCC,�Ҵ��������ڵ����粻�ǽ�ֹ���粻��NPLMN�����ȼ����ڵ�ǰ����������,
           ���뵱ǰ�������������ȼ���ͬ�������ϵ�ǰ������
           ������ڲ�ͬMCC�������Ҳ�ȫ��nplmn��forbidden plmn���ϵ�ǰ���� */

        stSearchedExistRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMcc = stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].stPlmnId.ulMcc;
        stSearchedExistRoamPlmnInfo.stPlmnWithRat.stPlmnId.ulMnc = stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].stPlmnId.ulMnc;
        stSearchedExistRoamPlmnInfo.stPlmnWithRat.enRat          = enRat;
        stSearchedExistRoamPlmnInfo.enNetStatus =  NAS_MMC_GetSpecPlmnWithRatNetStatusInPlmnSelectionList(&stSearchedExistRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);

        if (NAS_MMC_NET_STATUS_SEARCHED_REGISTERED != stSearchedExistRoamPlmnInfo.enNetStatus)
        {
            stSearchedExistRoamPlmnInfo.enNetStatus = NAS_MMC_NET_STATUS_SEARCHED_EXIST;
        }

        stSearchedExistRoamPlmnInfo.enPlmnType  = NAS_MMC_GetRoamPlmnTypeInPlmnSelectionList(&stSearchedExistRoamPlmnInfo.stPlmnWithRat, pstPlmnSelectionList);
        stSearchedExistRoamPlmnInfo.aucLac[0]   = (stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].usLac & 0xFF00) >> 8;
        stSearchedExistRoamPlmnInfo.aucLac[1]   = (stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].usLac & 0x00FF);

        if (VOS_FALSE == NAS_MML_ComparePlmnMcc(pstCurrSearchingPlmn->stPlmnId.ulMcc, stSearchedPlmnInfoMsg.astPlmnWithLacList[ulIndex].stPlmnId.ulMcc))
        {
            ulIsExistDiffMccWithCurrSearchingMcc  = VOS_TRUE;

            /* ��������������綼��nplmn��forbidden plmn����ͬmccҲ�Ȳ���� */
            enRoamPlmnType = NAS_MMC_GetRoamPlmnType(&stSearchedExistRoamPlmnInfo);

            if ((NAS_MMC_ROAM_PLMN_TYPE_FORBIDDEN != enRoamPlmnType)
             && (NAS_MMC_ROAM_PLMN_TYPE_NPLMN != enRoamPlmnType))
            {
                ucAllSearchedPlmnForbiddenPlmnFlag = VOS_FALSE;
            }
        }
        else
        {
            /* �޸ĺ����� */
            if (-1 == NAS_MMC_CompareRoamPlmnPrio(&stCurrSearchRoamPlmnInfo, &stSearchedExistRoamPlmnInfo, NAS_MML_GetMsPrioRatList()))
            {
                ucIsExistSearchedPlmnPrioCurrSearchingPlmn = VOS_TRUE;
            }
        }

    }


     /* searched plmn info ind��Ϣ�д���������������뵱ǰ�ѵ����粻ͬ����������磬
       �Ҳ�����nplmn��forbidden plmn���ϵ�ǰ����*/
    if ((VOS_TRUE == ulIsExistDiffMccWithCurrSearchingMcc)
     && (VOS_FALSE == ucAllSearchedPlmnForbiddenPlmnFlag))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == ucIsExistSearchedPlmnPrioCurrSearchingPlmn)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSkipFddRcvRrcSearchedPlmnInfoInd_PlmnSelection
 ��������  : �յ�RRMM_SEARCHED_PLMN_INFO_IND�ж��Ƿ���Ҫ��ϵ�ǰ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ��ϵ�ǰ����
             VOS_TRUE:��Ҫ��ϵ�ǰ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��5��22��
   ��    ��   : b00269685
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSkipFddRcvRrcSearchedPlmnInfoInd_PlmnSelection(
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg
)
{
    VOS_UINT32                          i;

    /* ��ǰ�����Զ��л�ģʽ������Ҫskip */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    /* �ϱ���plmn info ind�д���td list�еĹ����룬��Ҫskip */
    for (i = 0; i < pstSearchedPlmnInfoMsg->ulAvailPlmnNum; i++)
    {
        if (VOS_TRUE == NAS_MML_IsMccInDestMccList(pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].stPlmnId.ulMcc,
                                   NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                   NAS_UTRANCTRL_GetSpecTdMccList()))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnInfoInd_PlmnSelection
 ��������  : �յ�������PLMN INFO INDʱ֪ͨCSS��ǰMCC
 �������  : NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo
             VOS_UINT8                                               ucIsPowerOn
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnInfoInd_PlmnSelection(
    NAS_MMC_ROAM_PLMN_LIST_INFO_STRU                       *pstSearchedExistPlmnInfo,
    VOS_UINT8                                               ucIsPowerOn
)
{
    NAS_MML_PLMN_ID_STRU                                    astGeoPlmn[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                                              ulPlmnNum;
    VOS_UINT32                                              i;

    /* plmn����Ϊ0ʱ����Ҫ֪ͨ */
    if (0 == pstSearchedExistPlmnInfo->usSearchPlmnNum)
    {
        return;
    }

    /* ����ʱ����(RRC_MAX_EQUPLMN_NUM)16��plmn������б��и�������16��ֻȡ�б��е�ǰ16�� */

    ulPlmnNum   = pstSearchedExistPlmnInfo->usSearchPlmnNum;

    if (CSS_MAX_PLMN_ID_NUM < pstSearchedExistPlmnInfo->usSearchPlmnNum)
    {
        ulPlmnNum   = CSS_MAX_PLMN_ID_NUM;
    }

    for (i = 0; i < ulPlmnNum; i++)
    {
        astGeoPlmn[i].ulMcc = pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId.ulMcc;
        astGeoPlmn[i].ulMnc = pstSearchedExistPlmnInfo->astPlmnSelectionList[i].stPlmnWithRat.stPlmnId.ulMnc;
    }

    NAS_MMC_SndCssCurrGeoInd(ucIsPowerOn, ulPlmnNum, astGeoPlmn);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection
 ��������  : �յ�����������ʧ����Ϣʱ֪ͨCSS��ǰMCC
 �������  : NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedExistPlmnInfo
             VOS_UINT8                                               ucIsPowerOn
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��12��
    ��    ��   : s00217060
    �޸�����   : DTS2015120901555�޸ģ�NAS_MML_MIN���������ñ��ʽ

*****************************************************************************/
VOS_VOID NAS_MMC_SndCssCurrGeoIndAfterRcvPlmnSearchCnfFail_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedExistPlmnInfo,
    VOS_UINT8                                               ucIsPowerOn
)
{
    NAS_MML_PLMN_ID_STRU                                    astGeoPlmn[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                                              ulHighPlmnNum;
    VOS_UINT32                                              ulLowPlmnNum;
    VOS_UINT32                                              ulPlmnNum;
    VOS_UINT32                                              ulTotalNum;
    VOS_UINT32                                              i;

    ulHighPlmnNum   = pstSearchedExistPlmnInfo->ulHighPlmnNum;
    ulLowPlmnNum    = pstSearchedExistPlmnInfo->ulLowPlmnNum;

    /* high plmn��low plmn����Ϊ0ʱ����Ҫ֪ͨ */
    if ((0 == ulHighPlmnNum)
     && (0 == ulLowPlmnNum))
    {
        return;
    }

    /* ����ʱ����(RRC_MAX_EQUPLMN_NUM)16��plmn������б��и�������16��ֻȡ�б��е�ǰ16�� */
    ulPlmnNum   = ulHighPlmnNum;

    /* �ȼӸ�������plmn */
    for (i = 0; i < ulPlmnNum; i++)
    {
        astGeoPlmn[i].ulMcc = pstSearchedExistPlmnInfo->astHighPlmnList[i].ulMcc;
        astGeoPlmn[i].ulMnc = pstSearchedExistPlmnInfo->astHighPlmnList[i].ulMnc;
    }

    ulTotalNum  = ulHighPlmnNum + ulLowPlmnNum;

    /* �ټӵ�������plmn */
    for (i = ulPlmnNum; i < NAS_MML_MIN(CSS_MAX_PLMN_ID_NUM, ulTotalNum); i++)
    {
        astGeoPlmn[i].ulMcc = pstSearchedExistPlmnInfo->astLowPlmnList[i - ulPlmnNum].stPlmnId.ulMcc;
        astGeoPlmn[i].ulMnc = pstSearchedExistPlmnInfo->astLowPlmnList[i - ulPlmnNum].stPlmnId.ulMnc;
    }

    /* ����ܵ�plmn���� */
    ulPlmnNum = i;

    NAS_MMC_SndCssCurrGeoInd(ucIsPowerOn, ulPlmnNum, astGeoPlmn);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSndEplmn_PlmnSelection
 ��������  : ��ǰ�Ƿ���Ҫ���͵�ЧPlmn
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��1��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
 3.��    ��   : 2015��4��23��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSndEplmn_PlmnSelection( VOS_VOID )
{
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEplmnInfo  = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                   *pstCurPlmnId = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enCurrentFsmId;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurRat;
    VOS_UINT32                                              ulCurrentEventType;
    VOS_UINT32                                              ulIsPlmnForbid;
    VOS_UINT32                                              ulIsUserSpecSrch;

    ulIsPlmnForbid  = VOS_FALSE;

    /* �޿�ʱ�����뷢�͵�Ч Plmn */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return VOS_FALSE;
    }

    /*  ��ǰפ�����磬��Rplmnʱ�������� Eplmn������㣬�������㶪�� */
    pstEplmnInfo = NAS_MML_GetEquPlmnList();

    /* ��ǰ��EPlmn��֪ͨ�����,����RAU��������ATTACH,LAUʱ����Ҫɾ��Eplmn��24008:4.7.3.2.5
    if the attach attempt counter is smaller than 5 and, additionally,
    the update status is different from U1 UPDATED or the stored LAI is different
    from the one of the current serving cell, then the mobile station shall delete
    any LAI, TMSI, ciphering key sequence number stored in the SIM/USIM
    and list of equivalent PLMNs */
    if ( 0 == pstEplmnInfo->ucEquPlmnNum)
    {
        /* û��EPlmnʱ����֪ͨ����㵱ǰפ�������� */
        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(NAS_MML_GetCurrCampPlmnId(), &(pstEplmnInfo->astEquPlmnAddr[0])))
    {
        return VOS_FALSE;
    }

    pstCurPlmnId        = NAS_MML_GetCurrCampPlmnId();
    enCurRat            = NAS_MML_GetCurrNetRatType();

#if   (FEATURE_ON == FEATURE_LTE)
    /* ��������LTE��������ʱ */
    if ((VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(pstCurPlmnId->ulMcc))
     && (NAS_MML_NET_RAT_TYPE_LTE == enCurRat))
    {
        ulIsPlmnForbid = VOS_TRUE;
    }
#endif

    /* ��������뼼����PLMN ID */
    stPlmnWithRat.enRat          = NAS_MML_GetCurrNetRatType();
    stPlmnWithRat.stPlmnId.ulMcc = pstCurPlmnId->ulMcc;
    stPlmnWithRat.stPlmnId.ulMnc = pstCurPlmnId->ulMnc;

    /* �жϵ�ЧPLMN�Ƿ��ڽ�ֹ���뼼����PLMN�б���,������򲻽���PLMN ID����RRC */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
    {
        ulIsPlmnForbid = VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MML_IsPlmnIdInForbidPlmnList(pstCurPlmnId))
    {
        ulIsPlmnForbid = VOS_TRUE;
    }

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* ����LTE��ֻҪ��forbidden plmn for gprs����Ϊ��ֹ */
    if ((VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(pstCurPlmnId, pstForbidPlmnInfo->ucForbGprsPlmnNum, pstForbidPlmnInfo->astForbGprsPlmnList))
     && (NAS_MML_NET_RAT_TYPE_LTE == enCurRat))
    {
        ulIsPlmnForbid = VOS_TRUE;
    }

    enCurrentFsmId     = NAS_MMC_GetCurrFsmId();
    ulCurrentEventType = NAS_MMC_GetCurrFsmEventType();

    ulIsUserSpecSrch    = NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enCurrentFsmId, ulCurrentEventType);

    /* �û�ָ�����������,EPLMN��Чʱ,��ǰפ��PLMN�ڽ�ֹ�б��ﲻӦ��֪ͨRRC��
       ����RRC����פ�� */
    if ((VOS_TRUE == ulIsUserSpecSrch)
     && (VOS_TRUE == ulIsPlmnForbid))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_DisableLteForSimReason_PlmnSelection
 ��������  : ��������ʱ,���SIM����ҪDisable LTE
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_DisableLteForSimReason_PlmnSelection(VOS_VOID)
{
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;
    VOS_UINT32                                              ulLteOnly;

    ulLteOnly = NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList());

    enSimType           = NAS_MML_GetSimType();
    enLCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    if ((VOS_TRUE == NAS_MML_IsPlatformSupportLte())
     && (NAS_MML_SIM_TYPE_SIM == enSimType)
     && (VOS_FALSE            == ulLteOnly)
      )
    {
        if ((VOS_FALSE == NAS_MML_GetDisableLteRoamFlg())
         && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLCapabilityStatus))
        {
            if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != NAS_MML_GetLteForbiddenStatusFlg())
            {
                NAS_MMC_SndDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_SIM_CARD_SWITCH_ON);
            }
        }

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);
    }

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_RefreshPlmnSelectionListRcvMsccRegReq_PlmnSelection
 ��������  : ����ע�������������������ˢ�������б�
 �������  : enPlmnSearchScene
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��6��13��
   ��    ��   : b00269685
   �޸�����   : Pref���粻����UPLMN
*****************************************************************************/
VOS_VOID NAS_MMC_RefreshPlmnSelectionListRcvMsccRegReq_PlmnSelection(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList = VOS_NULL_PTR;

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    switch (enPlmnSearchScene)
    {
        case NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL:

            /* ���°�NCELL��ʼ��ѡ���б� */
            PS_MEM_SET(pstPlmnSelectionList, 0x0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));
            NAS_MMC_InitPlmnSelectionList_RegNCell(pstPlmnSelectionList, VOS_NULL_PTR);
            break;

        case NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN:

            /* ɾ����HPLMN */
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN, pstPlmnSelectionList);
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_UPLMN, pstPlmnSelectionList);
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_OPLMN, pstPlmnSelectionList);
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN, pstPlmnSelectionList);
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_AVAIL_PLMN, pstPlmnSelectionList);
            break;

        case NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN:

            /* ɾ����HPLMN+UOPLMN */
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_RPLMN, pstPlmnSelectionList);
            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_EPLMN, pstPlmnSelectionList);

            if (VOS_TRUE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
            {
                NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_UPLMN, pstPlmnSelectionList);
            }

            NAS_MMC_DeleteSpecTypePlmnInPlmnSelectionList(NAS_MMC_PLMN_TYPE_AVAIL_PLMN, pstPlmnSelectionList);
            break;

        default:

            /* ������������Ҫˢ��ѡ���б� */
            break;
    }

    /* ��ά�ɲ⣬���ѡ���б���Ϣ */
    NAS_MMC_LogPlmnSelectionList(pstPlmnSelectionList);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsAllowedRegAfterAcqSucc_PlmnSelection
 ��������  : ������������Ƿ�������������ע��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��4��24��
   ��    ��   : w00176964
   �޸�����   : CDMA 1x Iteration 10 Modified
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsAllowedRegAfterAcqSucc_PlmnSelection(VOS_VOID)
{
    MSCC_MMC_ACQ_REQ_STRU              *pstMsccMmcAcqReq      = VOS_NULL_PTR;
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg           = VOS_NULL_PTR;

    /* ��ȡ״̬���������Ϣ��Ϣ */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    /* �����ǰע������3GPP MMC���Ʒ���VOS_TRUE */
    if (NAS_MMC_REG_CONTROL_BY_3GPP_MMC == NAS_MMC_GetRegCtrl())
    {
        /* ���������Ϣ�ж��Ƿ���Ҫ����ע�� */
         if (ID_MSCC_MMC_ACQ_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
         {
             pstMsccMmcAcqReq = (MSCC_MMC_ACQ_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

             if (VOS_TRUE == pstMsccMmcAcqReq->ucNotRegAfterAcqSucc)
             {
                 return VOS_FALSE;
             }
         }

        return VOS_TRUE;
    }

    /* �����ǰע������3GPP2 CBP���ƶ�����MMA������ע�᷵��VOS_TRUE */
    if (VOS_TRUE == NAS_MMC_IsMsccRegReq_PlmnSelection())
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsMsccRegReq_PlmnSelection
 ��������  : ��ǰ�Ƿ���MSCC��ע�����󴥷�����ע��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsMsccRegReq_PlmnSelection(VOS_VOID)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    enPlmnSearchScene = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if ((NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL == enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN == enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN == enPlmnSearchScene)
     || (NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN == enPlmnSearchScene))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSearchAvailPlmn_PlmnSelection
 ��������  : �Ƿ���Ҫ����ѡ���б��ʼ��֮��Ŀ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��1��28��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��5��26��
   ��    ��   : s00246516
   �޸�����   : eHRPD��LTE��ѡ������NCELL����ʱ��PLMN��������Ч�ģ������Ҫ��������Ч������
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedSearchAvailPlmn_PlmnSelection(VOS_VOID)
{
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    enPlmnSearchScene = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    if ((NAS_MMC_PLMN_SELECTION_MODE_AUTO         == NAS_MMC_GetPlmnSelectionMode())
     && (NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN      != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN  != enPlmnSearchScene)
     && (NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_LTE_PLMN_SEARCH != enPlmnSearchScene))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection
 ��������  : ����ʧ�ܺ����MSCC��RF���ñ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��25��
   ��    ��   : w00176964
   �޸�����   : DSDS III�����ɺ���
 2.��    ��   : 2015��5��21��
   ��    ��   : w00167002
   �޸�����   : ROAM_PLMN_SELECTION_OPTIMIZE_2.0��Ŀ�޸�
 3.��    ��   : 2016��1��4��
   ��    ��   : n00355355
   �޸�����   : DTS2016010300936�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateRfAvailFlgPlmnSrchFail_PlmnSelection(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enPlmnType;

    PS_MEM_SET(&stDestPlmn, 0x0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* RF��Դ����,����Ҫ֪ͨMMA��ǰRF��Դ�Ƿ���� */
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return;
    }

    /* ����������һ����Ҫ����������ʱ�������������������򣬽�������פ�� */

    if (VOS_FALSE == NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        /* �����ǰNO RF,������ʧ�ܺ���Ҫ֪ͨMMA��ǰRF��Դ���� */
        NAS_MML_SetCurrRatRfAvailFlg(NAS_MML_NET_RAT_TYPE_BUTT, VOS_TRUE);

        /* ��MMA֪ͨ��ǰNO RF��Ϣ */
        NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

        /* �ϱ�MMA֮ǰ��Ϊno rf��û���ϱ���״̬ */
        NAS_MMC_SndMsccCurrServiceRelatedInfo();

        return;
    }

    enPlmnType = NAS_MMC_GetPlmnTypeInPlmnSelectionList(&stDestPlmn, NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection());

    /* �ж��¸�������PLMN�Ƿ�ΪR+E,��������ݲ�֪ͨMMA��ǰRF����,�ȴ�R+E���������������Ƿ���Ҫ֪ͨMMA;
       ��������֪ͨMMA */
    if ((NAS_MMC_PLMN_TYPE_RPLMN == enPlmnType)
     || (NAS_MMC_PLMN_TYPE_EPLMN == enPlmnType))
    {
        return;
    }

    NAS_MML_SetCurrRatRfAvailFlg(NAS_MML_NET_RAT_TYPE_BUTT, VOS_TRUE);

    /* ��MMA֪ͨ��ǰNO RF��Ϣ */
    NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

    /* �ϱ�MMA֮ǰ��Ϊno rf��û���ϱ���״̬ */
    NAS_MMC_SndMsccCurrServiceRelatedInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection
 ��������  : ��������Ϻ����MMA��RF���ñ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��25��
   ��    ��   : w00176964
   �޸�����   : DSDS III�����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateRfAvailFlgPlmnSrchAborted_PlmnSelection(VOS_VOID)
{
    /* RF��Դ����,����Ҫ֪ͨMMA��ǰRF��Դ�Ƿ���� */
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return;
    }

    NAS_MML_SetCurrRatRfAvailFlg(NAS_MML_NET_RAT_TYPE_BUTT, VOS_TRUE);

    /* ��MMA֪ͨ��ǰNO RF��Ϣ */
    NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

    /* �ϱ�MMA֮ǰ��Ϊno rf��û���ϱ���״̬ */
    NAS_MMC_SndMsccCurrServiceRelatedInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection
 ��������  : �����ɹ������MMA��RF���ñ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��6��25��
   ��    ��   : w00176964
   �޸�����   : DSDS III�����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateRfAvailFlgPlmnSrchSucc_PlmnSelection(VOS_VOID)
{
    /* RF��Դ����,����Ҫ֪ͨMMA��ǰRF��Դ�Ƿ���� */
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return;
    }

    NAS_MML_SetCurrRatRfAvailFlg(NAS_MML_NET_RAT_TYPE_BUTT, VOS_TRUE);

    /* ��MMA֪ͨ��ǰNO RF��Ϣ */
    NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccPlmnSrchReq_PlmnSelection_WaitMsccRegReq
 ��������  : �ȴ�MSCC��reg request�������յ�MSCC������������Ϣ�Ĵ���
 �������  : pMsg        - RRMM_REL_IND��Ϣ�׵�ַ
             ulEventType - �¼�����
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��4��14��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccPlmnSrchReq_PlmnSelection_WaitMsccRegReq(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;
    NAS_MML_PLMN_WITH_RAT_STRU                              stDestPlmn;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstInterPlmnSrchMsg = VOS_NULL_PTR;
    MSCC_MMC_PLMN_SEARCH_REQ_STRU                          *pstPlmnSrchReq      = VOS_NULL_PTR;

    /* ֹͣ������ʱ��TI_NAS_MMC_WAIT_MSCC_REG_REQ */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_REG_REQ);

    /* �����ABORT��־��ֱ���˳� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnSelection())
    {
        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_ABORTED);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    pstPlmnSrchReq = (MSCC_MMC_PLMN_SEARCH_REQ_STRU*)pstMsg;

    enPlmnSearchScene = NAS_MMC_GetPlmnSearchSceneMsccPlmnSrchReq(pstPlmnSrchReq);

    /* ��״̬�������Ϣ�滻Ϊ������ڲ�������Ϣ�������ѵ���������ֱ�ӷ���ע�� */
    pstInterPlmnSrchMsg = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, sizeof(NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU));
    if (VOS_NULL_PTR == pstInterPlmnSrchMsg)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMsccPlmnSrchReq_PlmnSelection_WaitMsccRegReq Alloc mem fail");

        NAS_MMC_SndRslt_PlmnSelection(NAS_MMC_PLMN_SELECTION_FAIL);

        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    NAS_MMC_BulidInterPlmnSearchReqMsg(enPlmnSearchScene, VOS_NULL_PTR, 0, pstInterPlmnSrchMsg);
    NAS_MMC_SaveCurEntryMsg(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_PLMN_SEARCH_REQ),
                            (struct MsgCB*)pstInterPlmnSrchMsg);
    PS_MEM_FREE(WUEPS_PID_MMC, pstInterPlmnSrchMsg);

    /* ����enPlmnSearchScene����ˢ��ѡ���б�ɾ�����������ȼ�Ҫ������� */
    NAS_MMC_RefreshPlmnSelectionListRcvMsccRegReq_PlmnSelection(enPlmnSearchScene);

    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ��ȡ��ǰ���뼼�� */
    enNetRatType = NAS_MML_GetCurrNetRatType();

    if (VOS_TRUE != NAS_MMC_GetNextSearchPlmn_PlmnSelection(&stDestPlmn))
    {
        NAS_MMC_GetNextSearchPlmnFail_PlmnSelection();

        return VOS_TRUE;
    }

    if (enNetRatType == stDestPlmn.enRat)
    {
        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSpecPlmnSearchReq_PlmnSelection(&stDestPlmn);
    }
    /*��Ҫ����ǰģʽ���л����ȴ�����״̬������������ʱ��*/
    else
    {
        /* �������LMM���͹������󣬸��ݵ�ǰ��ͬ�Ľ��뼼����Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_PlmnSelection(enNetRatType);
    }

    return VOS_TRUE;

}




/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveGeoPlmn_PlmnSelection
 ��������  : ����MSCC�ڿ�������ʱ��������PLMN
 �������  : MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstPlmnSearchReq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SaveGeoPlmn_PlmnSelection(
    MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstPlmnSearchReq
)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stGeoPlmn;

    /* ���ǿ���������PLMN��Ч */
    if ((VOS_FALSE == NAS_MML_IsPlmnIdValid(&(pstPlmnSearchReq->stInitAcqPlmnInfo.stInitAcqPlmnId)))
     || (NAS_MSCC_PIF_ACQ_REASON_POWER_UP != pstPlmnSearchReq->enAcqReason))
    {
        return;
    }

    PS_MEM_SET(&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ����MSCC��������PLMN */
    stGeoPlmn.enRat             = pstPlmnSearchReq->stInitAcqPlmnInfo.enRat;
    stGeoPlmn.stPlmnId.ulMcc    = pstPlmnSearchReq->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMcc;
    stGeoPlmn.stPlmnId.ulMnc    = pstPlmnSearchReq->stInitAcqPlmnInfo.stInitAcqPlmnId.ulMnc;

    NAS_MMC_SetGeoPlmn(&stGeoPlmn);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMsccSrchedGuPlmnInfo
 ��������  : ��MSCC����Searched GU PLMN INFO
 �������  : pstInterPlmnSearchInfo - ����ʧ�ܴ��������ڵ�������Ϣ
             enRat                  - ���뼼��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��15��
   ��    ��   : h00285180
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccSrchedGuPlmnInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_SEARCHED_PLMN_INFO_IND_STRU   *pstSearchedPlmnInfoMsg
)
{
    MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU stMmcSrchedPlmnINfo;
    VOS_UINT32                         i;

    PS_MEM_SET(&stMmcSrchedPlmnINfo, 0, sizeof(stMmcSrchedPlmnINfo));

    if (NAS_RRC_MAX_AVAILPLMN_NUM < pstSearchedPlmnInfoMsg->ulAvailPlmnNum)
    {
        pstSearchedPlmnInfoMsg->ulAvailPlmnNum = NAS_RRC_MAX_AVAILPLMN_NUM;
    }
    stMmcSrchedPlmnINfo.ulLaiNum = pstSearchedPlmnInfoMsg->ulAvailPlmnNum;
    if (NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM < stMmcSrchedPlmnINfo.ulLaiNum)
    {
        stMmcSrchedPlmnINfo.ulLaiNum = NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM;
    }

    stMmcSrchedPlmnINfo.enRat = enRat;

    for (i = 0; i < stMmcSrchedPlmnINfo.ulLaiNum; i++)
    {
        stMmcSrchedPlmnINfo.astLai[i].stPlmnId.ulMcc = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].stPlmnId.ulMcc;
        stMmcSrchedPlmnINfo.astLai[i].stPlmnId.ulMnc = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].stPlmnId.ulMnc;
        stMmcSrchedPlmnINfo.astLai[i].usLac          = pstSearchedPlmnInfoMsg->astPlmnWithLacList[i].usLac;
    }

    NAS_MMC_SndMsccSrchedPlmnInfo(&stMmcSrchedPlmnINfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMsccSrchedLtePlmnInfo
 ��������  : ��MSCC����Searched LTE PLMN INFO
 �������  : pstSearchedPlmnInfoInd - ����ʧ�ܴ��������ڵ�������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��15��
   ��    ��   : h00285180
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccSrchedLtePlmnInfo(
    LMM_MMC_SEARCHED_PLMN_INFO_IND_STRU                    *pstSearchedPlmnInfoInd
)
{
    MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU stMmcSrchedPlmnINfo;
    VOS_UINT32                         i;
    MSCC_MMC_PLMN_ID_STRU              stGuNasPlmn;

    PS_MEM_SET(&stMmcSrchedPlmnINfo, 0, sizeof(stMmcSrchedPlmnINfo));

    if (LMM_MMC_MAX_SEARCHED_TAI_NUM < pstSearchedPlmnInfoInd->ulTaiNum)
    {
        pstSearchedPlmnInfoInd->ulTaiNum = LMM_MMC_MAX_SEARCHED_TAI_NUM;
    }
    stMmcSrchedPlmnINfo.ulLaiNum = pstSearchedPlmnInfoInd->ulTaiNum;
    if (NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM < pstSearchedPlmnInfoInd->ulTaiNum)
    {
        stMmcSrchedPlmnINfo.ulLaiNum = NAS_MSCC_PIF_MAX_SRCHED_LAI_NUM;
    }

    stMmcSrchedPlmnINfo.enRat = NAS_MSCC_PIF_NET_RAT_TYPE_LTE;

    for (i = 0; i < stMmcSrchedPlmnINfo.ulLaiNum; i++)
    {

        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&pstSearchedPlmnInfoInd->stTaiList[i].stPlmnId,
                                            &stGuNasPlmn);

        stMmcSrchedPlmnINfo.astLai[i].stPlmnId = stGuNasPlmn;
        stMmcSrchedPlmnINfo.astLai[i].usLac    = (pstSearchedPlmnInfoInd->stTaiList[i].stTac.ucTac << 8) | (pstSearchedPlmnInfoInd->stTaiList[i].stTac.ucTacCnt);
    }

    NAS_MMC_SndMsccSrchedPlmnInfo(&stMmcSrchedPlmnINfo);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedUpdateSpecRatPlmnSearchInfo_PlmnSelection
 ��������  : �յ��ڲ�������Ϣʱ�Ƿ���Ҫ����ָ��rat�����������Ϣ
 �������  : NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsNeedUpdateSpecRatPlmnSearchInfo_PlmnSelection(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnListInfo
)
{
    NAS_MMC_NON_OOS_PLMN_SEARCH_FEATURE_SUPPORT_CFG_STRU   *pstOosCfg   = VOS_NULL_PTR;
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene;

    pstOosCfg           = NAS_MMC_GetNonOosPlmnSearchFeatureSupportCfg();
    enPlmnSearchScene   = NAS_MMC_GetPlmnSearchScene_PlmnSelection();

    /* ��t00173447ȷ�ϣ����������������󣬹��ⶪ������RPLMN������RPLMNֻ�ѵ�ǰģ��
       ����̬ʱ�����W��RPLMN�Ѿ�ȫƵ������������ʱ�������Ϊ�����ڣ��ٶ���һ��W��RPLMNҲû������ */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG == enPlmnSearchScene)
    {
        return VOS_FALSE;
    }

    /* ���������Ż�3.0ֻ���area lost���������޸ģ�������������ԭ���Ĵ��� */
    if (NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST != enPlmnSearchScene)
    {
        return VOS_TRUE;
    }

    /* û�н��й�pref band������spec������������ */
    if ((VOS_FALSE == pstPlmnListInfo->stSearchedType.ucPrefBandSearchedFlg)
     || (VOS_FALSE == pstPlmnListInfo->stSearchedType.ucSpecSearchedFlg))
    {
        return VOS_FALSE;
    }

    /* NV����area lost����history֮����Ҫ����spec�ѻ�pref band�ѣ�������  */
    if (NAS_MMC_PLMN_SEARCH_TYPE_AFTER_HISTORY_NONE != pstOosCfg->enSearchTypeAfterHistoryInAreaLostScene)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSpecRatSearched_PlmnSelection
 ��������  : ָ�����뼼���Ƿ��Ѿ���������
 �������  : enSpecRat
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��������; VOS_FALSE:δ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_MMC_IsSpecRatSearched_PlmnSelection(NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enSpecRat)
{
    VOS_UINT8                            ucSearchAllBand;
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8     enCoverageType;

    ucSearchAllBand           = NAS_MMC_GetAllBandSearch_PlmnSelection(enSpecRat);
    enCoverageType            = NAS_MMC_GetRatCoverage_PlmnSelection(enSpecRat);

    if ( (NAS_MMC_COVERAGE_TYPE_LOW     == enCoverageType)
       ||(NAS_MMC_COVERAGE_TYPE_HIGH    == enCoverageType)
       ||(VOS_TRUE                      == ucSearchAllBand))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedSetLmmAttachClReqStatus_PlmnSelection
 ��������  : �ж��Ƿ���Ҫ����cl attachע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : wx270776
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedUpdateLmmAttachClRegStatus_PlmnSelection(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachClRegStatusFromLmm
)
{
    VOS_UINT32                          ulOldAttachRegStatusPriority;
    VOS_UINT32                          ulNewAttachRegStatusPriority;
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enOldLmmAttachRegStatus;

    enOldLmmAttachRegStatus = NAS_MMC_GetLmmAttachClRegStatus_PlmnSelection();

    /* ��ȡ�¾�ע��״̬���ȼ� */
    ulOldAttachRegStatusPriority = NAS_MMC_GetLmmAttaClRegStatPrioValue(enOldLmmAttachRegStatus);
    ulNewAttachRegStatusPriority = NAS_MMC_GetLmmAttaClRegStatPrioValue(enLmmAttachClRegStatusFromLmm);

    /* ȨֵԽ�����ȼ�Խ�� */
    if (ulNewAttachRegStatusPriority > ulOldAttachRegStatusPriority)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}
/*lint -restore */

#ifdef  __cplusplus
#if  __cplusplus
  }
#endif
#endif
