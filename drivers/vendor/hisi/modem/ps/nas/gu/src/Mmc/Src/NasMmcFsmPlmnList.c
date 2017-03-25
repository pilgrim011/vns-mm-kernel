/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcFsmPlmnList.c
  �� �� ��   : ����
  ��    ��   : W00176964
  ��������   : 2011��07��02��
  ����޸�   :
  ��������   : plmn listʱ״̬��״̬����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��07��02��
    ��    ��   : W00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcCtx.h"
#include "NasMmlLib.h"
#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcProcRegRslt.h"
#include "NasMmcProcNvim.h"
#include "NasMmcComFunc.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmlMsgProc.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcFsmPlmnList.h"
#include "NasMmcFsmPLmnListTbl.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndOm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcProcSuspend.h"
#include "NasMmlMsgProc.h"
#include "NasUtranCtrlInterface.h"

/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */
#include "NasMmcSndCss.h"

#include "NasUsimmApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_PLMN_LIST_C
/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/


/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListReq_PlmnList_Init
 ��������  : ��list������INIT״̬,�յ�TAF��LIST������Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II����
  3.��    ��   : 2012��5��9��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  4.��    ��   : 2014��1��22��
    ��    ��   : w00167002
    �޸�����   : SVLTE������:�����б��ѣ������NO RF��ǣ������NO RF�����Ϣ��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    /* ��ȡLTE����״̬ */
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);


    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_LIST_SRCH);



#if (FEATURE_ON == FEATURE_LTE)
    /* ����disable L�ı�� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* �ж��Ƿ���Ҫanycell����,��Ҫ������anycell ������� */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* �����û�LIST�������� */
    NAS_MMC_ProcUserPlmnListReq_PlmnList();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvInterPlmnListReq_PlmnList_Init
 ��������  : ��list������INIT״̬,�յ�MMC���ڲ�LIST������Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_INTER_PLMN_LIST_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��6��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��24��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2012��5��9��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  4.��    ��   : 2012��9��11��
    ��    ��   : w00176964
    �޸�����   : V7R1_GUTL��Ŀ����:TD��ģ��פ��̬����Ҫ֪ͨMM/GMM��������״̬
  5.��    ��   : 2014��1��22��
    ��    ��   : w00167002
    �޸�����   : SVLTE������:�����б��ѣ������NO RF��ǣ������NO RF�����Ϣ��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvInterPlmnListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus      = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);




#if (FEATURE_ON == FEATURE_LTE)
    /* ����disable L��� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݲ�ͬ����ģʽ,����LIST��������Ǩ���ȴ��������״̬������������ʱ��*/
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_PlmnList_Init
 ��������  : ��list������INIT״̬,�յ�TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST��ʱ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��6��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2012��5��9��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  4.��    ��   : 2014��1��22��
    ��    ��   : w00167002
    �޸�����   : SVLTE������:�����б��ѣ������NO RF��ǣ������NO RF�����Ϣ��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserPlmnListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);




#if (FEATURE_ON == FEATURE_LTE)
    /* ����disable L��� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* �ж��Ƿ���Ҫanycell����,��Ҫ������anycell ������� */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* �����û�LIST�������� */
    NAS_MMC_ProcUserPlmnListReq_PlmnList();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_PlmnList_Init
 ��������  : ��list������INIT״̬,�յ�TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST��ʱ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��6��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2012��5��9��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  4.��    ��   : 2012��9��11��
    ��    ��   : w00176964
    �޸�����   : V7R1_GUTL��Ŀ����:TD��ģ��פ��̬����Ҫ֪ͨMM/GMM��������״̬
  5.��    ��   : 2014��1��22��
    ��    ��   : w00167002
    �޸�����   : SVLTE������:�����б��ѣ������NO RF��ǣ������NO RF�����Ϣ��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingInterPlmnListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);




#if (FEATURE_ON == FEATURE_LTE)

    /* ����disable L��� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݲ�ͬ����ģʽ,����LIST��������Ǩ���ȴ��������״̬������������ʱ��*/
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListReq_PlmnList_NonInit
 ��������  : ��list�����ĸ���״̬,�յ�ID_MSCC_MMC_PLMN_LIST_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListReq_PlmnList_NonInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �õ�ǰ��Ϣ���µ�ǰ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndRslt_PlmnList
 ��������  : ����PLMN LIST״̬����ɽ����Ϣ
 �������  : enRslt:״̬���˳����
             ulNeedPlmnSearch:�Ƿ���Ҫ����
             pstListInfo:�������������б���Ϣ
             pstRegRsltInfo:ע������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_OK: ����������Ϣ�ɹ�
             VOS_ERR: ����������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��5��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndRslt_PlmnList(
    NAS_MMC_PLMN_LIST_RESULT_ENUM_UINT32                    enRslt,
    VOS_UINT8                                               ucNeedPlmnSearch,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo,
    NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU                   *pstRegRsltInfo
)
{

    NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8               enPlmnListSearchScene;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    enLteCapStatus        = NAS_MML_GetLteCapabilityStatus();
#endif

    enPlmnListSearchScene = NAS_MMC_PLMN_LIST_SEARCH_SCENE_BUTT;

    /* �����Ҫ����������Ҫ��������������Ŀǰֻ��USERLIST��disable lte������������ */
    if (VOS_TRUE == ucNeedPlmnSearch)
    {
        /* List��֮ǰLte û��disable����List��״̬���﷢��disable lte������������Ϊdisable lte */
#if (FEATURE_ON == FEATURE_LTE)
        if ((VOS_FALSE == NAS_MMC_GetPreLteDisableFlg_PlmnList())
         && ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
          || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus)))
        {
            enPlmnListSearchScene = NAS_MMC_PLMN_LIST_SEARCH_SCENE_DISABLE_LTE;
        }
        else
#endif
        {
            enPlmnListSearchScene = NAS_MMC_PLMN_LIST_SEARCH_SCENE_USER_LIST;
        }
    }

    NAS_MMC_SndPlmnListRslt(enRslt,ucNeedPlmnSearch,enPlmnListSearchScene,
                                pstListInfo,pstRegRsltInfo);
    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��30��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*�˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* δ��ʼ�������û���LIST������ʱ����ʱ����ʱ�����б�Ϊ��
       ��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN���յ���·�ͷź�
       ����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmSignalingStatusInd_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�MMCGMM_SIGNALING_STATUS_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCGMM_SIGNALING_STATUS_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmSignalingStatusInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����GMM�ϱ�����������ָʾ */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmRrConnInfoInd_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�MMCMM_RR_CONN_INFO_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMM_RR_CONN_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrConnInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����MM�ϱ���RR�����ͷ�ָʾ */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmRrRelInd_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�MMCMM_RR_REL_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMM_RR_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmRrRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����MM�ϱ���MM�����ͷ�ָʾ */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�RRMM_REL_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����RRC��·�ͷ����� */
    NAS_MMC_ProcRrcConnRelInd_PlmnList();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmTbfRelInd_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�MMCGMM_TBF_REL_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCGMM_TBF_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmTbfRelInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ж�RRC�����Ƿ���� */
    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* ���ؼ����ȴ� */
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�RRC��·�ͷŶ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ��GAS����LIST��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    /* ��פ��̬֪ͨMM/GMM������ʼ */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();

        /* ���ý�������״̬ */
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�MMCGMM_NETWORK_DETACH_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCGMM_NETWORK_DETACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
  3.��    ��   : 2012��2��13��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                  �򲻸��µ�ǰ��additional action
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU                         *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    pstDetachMsg        = (MMCGMM_NETWORK_DETACH_IND_STRU *)pstMsg;

    /* ����Detach��� */
    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

#if   (FEATURE_ON == FEATURE_LTE)
        /* ��LMM����detach�����Ϣ */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
                                             (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�MMMMC_CS_REG_RESULT_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMMMC_CS_REG_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�GMMMMC_PS_REG_RESULT_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:GMMMMC_PS_REG_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmAbortInd_PlmnList_WaitRrcConnRelInd
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
VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
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
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* ��LMM����ID_MMC_LMM_ACTION_RESULT_REQ */
    /* ����ActionRslt��Ϣ�����ΪCN_Rej,������Ϊ����NAS_MML_PROC_MM_ABORT����
       ����ͽ������CS��ԭ��ֵΪAbort����ԭ��ֵ */
    stActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�RRMM_SYS_INFO_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SYS_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����WASϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�GRRMM_SYS_INFO_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:GRRMM_SYS_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����GASϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�RRMM_SUSPEND_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SUSPEND_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : ������ϵͳ״̬��ʱ����Ϊ��ǰ�����磬��ʱAPS����
  3.��    ��   : 2014��04��18��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST             *pstSuspendMsg = VOS_NULL_PTR;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ��������ͬ��״̬�� */
    switch (pstSuspendMsg->ucSuspendCause)
    {
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_PLMNSEARCH:
            /* ��WAS���͹���ʧ�� */
            NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, pstSuspendMsg->MsgHeader.ulSenderPid);

            /* ���·���״̬ */
            /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, begin */

            /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, end */

            /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, begin */
            NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
            /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, end */

            /* ��Ҫ�����ͷ���· */
            NAS_MMC_SndMmRelReq();

            NAS_MMC_SndGmmRelReq();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            break;
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitRrcConnRelInd:Unexpected suspend type!");
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�MMCMMC_CELLRESELECT_RSLT_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_CELLRESELECT_RSLT_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2011��12��30��
    ��    ��   : l65478
    �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                 ���ݾ����ԭ��ֵ������
  4.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : �˳���ϵͳ״̬��ʱ��֪ͨAPS��ǰ��������

  5.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : GUL BG��Ŀ����
  6.��    ��   : 2012��9��11��
    ��    ��   : w00176964
    �޸�����   : V7R1_GUTL��Ŀ����:TD��ģ��פ��̬����Ҫ֪ͨMM/GMM��������״̬
  7.��    ��   : 2013��2��7��
    ��    ��   : W00176964
    �޸�����   : Volte_phase3��Ŀ����:����IMS������ʱdisable Lģ���߼��޸�
  8.��    ��   : 2013��4��9��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬��,����ʧ����ϢǨ�Ƶ�OOC
  9.��    ��   : 2015��9��25��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMCMMC_SUSPEND_RSLT_STRU       *pstSuspendRslt = VOS_NULL_PTR;

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    pstSuspendRslt  = (NAS_MMCMMC_SUSPEND_RSLT_STRU*)pstMsg;

    /* suspend ��ϵͳ��ѡ��� */
    NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd:SUSPEND COMPLETE!");

    /* ����״̬���˳���� ������Ӧ�Ĵ��� */
    if ( (NAS_MMC_SUSPEND_FAIL == pstSuspendRslt->enRslt)
      && (NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST != pstSuspendRslt->enFailCause))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitRrcConnRelInd:SUSPEND FAIL!");

        return VOS_TRUE;
    }

    /* ��ѡ��ǰ���뼼���Ѿ��ı䣬��Ҫ��ѡ��ʼ�������Ľ��뼼�����ȼ� */
 #if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
 #endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* �жϵ�ǰ����ģʽ */
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* ��ǰ����RRC����,��GU��ϵͳ��LTE��,LTE��ʱ������������,
           MMC��ʱ��Ҫ�ȴ�L�µ�ע���� */

        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        /* ����CSPS��AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, begin */
#if (FEATURE_ON == FEATURE_IMS)
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, end */

        /* Ǩ��״̬���ȴ�EPSע���� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }
#endif

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ��ǰ���뼼������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    /* ��פ��̬֪ͨMM/GMM������ʼ */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();

        /* ���ý�������״̬ */
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd
 ��������  : ��list�����ĵȴ�RRC��·�ͷ�״̬,�յ�TI_NAS_MMC_WAIT_RRC_CONN_REL_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_RRC_CONN_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��25��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2012��6��5��
    ��    ��   : w00176964
    �޸�����   : V7R1 C50 GUL BG��Ŀ����:PSҵ������5S��ʱ����֤LIST�����л��ᷢ��
  4.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd Enter!");

    /* ����ҵ�񣬻ظ��б���ʧ�� */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();
    }
    else
    {
        NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();
    }


    /* ����δ��ʼ�������������������б�Ϊ�գ���Ҫ�����Գ��ԣ��˳�״̬������Ҫ�������� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());


    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSysInfoInd
 ��������  : ��list�����ĵȴ�WASϵͳ��Ϣʱ,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��30��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��8��1��
    ��    ��   : w00167002
    �޸�����   : �ڵ�ϵͳ��Ϣʱ���յ���ϵͳ��Ϣ�����ϵ�ǰ״̬��������ϵͳ������
  3.��    ��   : 2015��9��25��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU                *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);


    /* ����ڵ�ϵͳ��Ϣʱ��,�յ�SUSPEND IND��Ϣ�����ϵ�ǰ״̬����������ϵͳ���� */
    if ( NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND) == pstAbortMsg->ulEventType )
    {
        /* ֹͣ�ȴ�WASϵͳ��Ϣ�ı�����ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

        /* ����5S�����Գ��Զ�ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
             /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* ����LIST REJ��MSCC */
                NAS_Mmc_SndMsccPlmnListRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
            }
        }
#if (FEATURE_ON == FEATURE_CSG)
        else if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* ����LIST REJ��MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
            }
        }
#endif
        else
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
        }

        /* ����״̬��ʧ�ܵ��˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSysInfoInd
 ��������  : ��list�����ĵȴ�WASϵͳ��Ϣʱ,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��¼֪ͨMSCC������ */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSysInfoInd
 ��������  : ��list�����ĵȴ�WASϵͳ��Ϣʱ,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��8��1��
    ��    ��   : w00167002
    �޸�����   : �ڵ�ϵͳ��Ϣʱ���յ���ϵͳ��Ϣ�����ϵ�ǰ״̬��������ϵͳ������
  3.��    ��   : 2015��9��25��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ABORT_FSM_STRU                *pstAbortMsg = VOS_NULL_PTR;

    pstAbortMsg = (NAS_MMC_ABORT_FSM_STRU*)pstMsg;

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);


    /* ����ڵ�ϵͳ��Ϣʱ��,�յ�SUSPEND IND��Ϣ�����ϵ�ǰ״̬����������ϵͳ���� */
    if ( NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND) == pstAbortMsg->ulEventType )
    {
        /* ֹͣ�ȴ�WASϵͳ��Ϣ�ı�����ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

        /* ����5S�����Գ��Զ�ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
             /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* ����LIST REJ��MSCC */
                NAS_Mmc_SndMsccPlmnListRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
            }
        }
#if (FEATURE_ON == FEATURE_CSG)
        else if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* ����LIST REJ��MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
            }
        }
#endif
        else
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
        }

        /* ����״̬��ʧ�ܵ��˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSysInfoInd
 ��������  : ��list�����ĵȴ�WASϵͳ��Ϣʱ,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��¼֪ͨMSCC������ */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasSysInfoInd
 ��������  : ��list�����ĵȴ�WAS sys info,�յ�RRMM_SYS_INFO_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SYS_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�WASϵͳ��Ϣ�ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* ����WASϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* Ǩ�Ƶ��ȴ�ע����״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

    /* ����������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasSysInfoInd
 ��������  : ��list�����ĵȴ�GAS SYS INFO,�յ�GRRMM_SYS_INFO_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:GRRMM_SYS_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
  3.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ֹͣ�ȴ�GASϵͳ��Ϣ�ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* ����GASϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* Ǩ�Ƶ��ȴ�ע����״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

    /* ����������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitWasSysInfoInd
 ��������  : ��list�����ĵȴ�WASϵͳ��Ϣʱ,�յ�RRMM_AREA_LOST_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_AREA_LOST_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II LIST����
  3.��    ��   : 2013��4��4��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬��,����ʧ����Ϣ��Ǩ�Ƶ�OOC
  4.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
  4.��    ��   : 2014��04��9��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:���ӷ���״̬�ϱ�����
  5.��    ��   : 2015��9��25��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */


    /* ���פ��PLMN RAI LAC��Ϣ*/
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, end */
    /* �ϱ���Ӧ��CS/PS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��WAS����LIST��������Ǩ��״̬���ȴ�WAS LIST�����ظ�״̬ ������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitGasSysInfoInd
 ��������  : ��list�����ĵȴ�GASϵͳ��Ϣʱ,�յ�RRMM_AREA_LOST_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_AREA_LOST_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II LIST����
  3.��    ��   : 2013��4��9��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬��������ʧ��Ǩ�Ƶ�ooc
  4.��    ��   : 2014��04��9��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:���ӷ���״̬�ϱ�����
  5.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */


    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, begin */

    /* Deleted by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, end */
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
    /* �ϱ���Ӧ��CS/PS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��GAS����LIST��������,Ǩ��״̬���ȴ�GAS LIST�����ظ�״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasSysInfoIndExpired_PlmnList_WaitWasSysInfoInd
 ��������  : ��list�����ĵȴ�WAS ϵͳ��Ϣʱ,�յ�TI_NAS_MMC_WAIT_WAS_SYS_INFO��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_WAS_SYS_INFO��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2014��04��18��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ
  4.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasSysInfoIndExpired_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSysInfoIndExpired_PlmnList_WaitWasSysInfoInd Enter!");

    /* ���פ��PLMN RAI LAC��Ϣ*/
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /* ���·���״̬ */
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, end */

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��WAS����LIST��������,Ǩ��״̬���ȴ�WAS LIST�����ظ�״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasSysInfoIndExpired_PlmnList_WaitGasSysInfoInd
 ��������  : ��list�����ĵȴ�GAS ϵͳ��Ϣʱ,�յ�TI_NAS_MMC_WAIT_GAS_SYS_INFO��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_GAS_SYS_INFO��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2014��04��18��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ
  4.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasSysInfoIndExpired_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasSysInfoIndExpired_PlmnList_WaitGasSysInfoInd Enter!");

    /* ���פ��PLMN RAI LAC��Ϣ*/
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /* ���·���״̬ */
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, begin */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-18, end */

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        NAS_MMC_ProcFsmAbort_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��GAS����LIST��������,Ǩ��״̬���ȴ�GAS LIST�����ظ�״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsPsRegRsltInd
 ��������  : ��list�����ĵȴ�CS/PS��ע����ʱ,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��30��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitCsPsRegRsltInd
 ��������  : ��list�����ĵȴ�CS/PS��ע����ʱ,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitCsPsRegRsltInd
 ��������  : ��list�����ĵȴ�CS/PS��ע����ʱ,�յ�GMMMMC_PS_REG_RESULT_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:GMMMMC_PS_REG_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2012��9��11��
    ��    ��   : w00176964
    �޸�����   : V7R1_GUTL��Ŀ����:TD��ģ��פ��̬����Ҫ֪ͨMM/GMM��������״̬
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    GMMMMC_PS_REG_RESULT_IND_STRU                          *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* �����ǰ�ȴ�PS��ע���� */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* �Ƿ��Ѿ�����CS/PS��ע���� */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* ���CS/PS��Ҫ��������ע�ᣬ��Ҫ�ڴ�״̬�����ȴ�ע���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitCsPsRegRsltInd
 ��������  : ��list�����ĵȴ�CS/PS��ע����ʱ,�յ�MMMMC_CS_REG_RESULT_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMMMC_CS_REG_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��11��
    ��    ��   : w00176964
    �޸�����   : V7R1_GUTL��Ŀ����:TD��ģ��פ��̬����Ҫ֪ͨMM/GMM��������״̬
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;
    MMMMC_CS_REG_RESULT_IND_STRU                           *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* �����ǰ�ȴ�CS��ע���� */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);

    /* �Ƿ��Ѿ�����CS/PS��ע���� */
    if ( NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList() )
    {
        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* ���CS/PS��Ҫ��������ע�ᣬ��Ҫ�ڴ�״̬�����ȴ�ע���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmAbortInd_PlmnList_WaitCsPsRegRsltInd
 ��������  : �ȴ�CS PSע��������յ� MM Abort��Ϣ�Ĵ���
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
VOS_UINT32 NAS_MMC_RcvMmAbortInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_ABORT_IND_STRU               *pstMmAbortInd   = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU    stActionRslt;
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
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL);
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* ��LMM����ID_MMC_LMM_ACTION_RESULT_REQ */
    /* ����ActionRslt��Ϣ�����ΪCN_Rej,������Ϊ����NAS_MML_PROC_MM_ABORT����
       ����ͽ������CS��ԭ��ֵΪAbort����ԭ��ֵ */
    stActionRslt.enProcType     = NAS_MML_PROC_MM_ABORT;
    stActionRslt.enRegRst       = NAS_MML_REG_RESULT_CN_REJ;
    stActionRslt.enReqDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enRstDomain    = NAS_MMC_REG_DOMAIN_CS;
    stActionRslt.enCnCause      = pstMmAbortInd->enAbortCause;
    stActionRslt.ulAttemptCount = 0x0;

    NAS_MMC_SndLmmRegActionResultReq(&stActionRslt);
#endif

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitCsPsRegRsltInd
 ��������  : ��list�����ĵȴ�CS/PS��ע����ʱ,�յ�MMCGMM_NETWORK_DETACH_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCGMM_NETWORK_DETACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��30��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
  3.��    ��   : 2012��2��13��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  4.��    ��   : 2012��9��11��
    ��    ��   : w00176964
    �޸�����   : V7R1_GUTL��Ŀ����:TD��ģ��פ��̬����Ҫ֪ͨMM/GMM��������״̬
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmNetworkDetachInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_NETWORK_DETACH_IND_STRU                         *pstDetachMsg = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    pstDetachMsg        = (MMCGMM_NETWORK_DETACH_IND_STRU *)pstMsg;

    /* ����Detach��� */
    enAdditionalAction = NAS_MMC_ProcGmmNetworkDetachInd(pstDetachMsg);

    /* AdditionalAction��Ч������PS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

    /* ���PS��ĵȴ���־ */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

#if   (FEATURE_ON == FEATURE_LTE)
    /* ��LMM����detach�����Ϣ */
    NAS_MMC_SndLmmMtDetachIndActionResultReq(pstDetachMsg->ulDetachType,
                                           (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)pstDetachMsg->ulDetachCause);
#endif

    /* ��Ҫ����ע��ʱ������Ҫִ�к����Ķ��� */
    if (NAS_MMC_GMM_NT_DETACH_REATTACH == pstDetachMsg->ulDetachType)
    {
        return VOS_TRUE;
    }

    /* δ����CS/PS�Ľ���������ȴ�ע���� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* ���CS/PS��Ҫ��������ע�ᣬ��Ҫ�ڴ�״̬�����ȴ�ע���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmServiceRequestResultInd_PlmnList_WaitCsPsRegRsltInd
 ��������  : ��list�����ĵȴ�CS/PS��ע����ʱ,�յ�GMMMMC_SERVICE_REQUEST_RESULT_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:GMMMMC_SERVICE_REQUEST_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��30��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��13��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  3.��    ��   : 2012��9��11��
    ��    ��   : w00176964
    �޸�����   : V7R1_GUTL��Ŀ����:TD��ģ��פ��̬����Ҫ֪ͨMM/GMM��������״̬
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmServiceRequestResultInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU                 *pstServiceRsltInd = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsAdditionalAction;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsAdditionalAction;

    pstServiceRsltInd = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)pstMsg;

    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstServiceRsltInd->ulServiceSts)
    {
        /* ����PS��AdditionalAction */
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON);
    }
    else
    {
        /* �������ʧ�ܣ�����ͬ�ܾ�ԭ��ֵ������PS additional Action */
        enAdditionalAction = NAS_MMC_ProcPsServiceRegFail(pstServiceRsltInd);

        /* AdditionalAction��Ч������PS����һ���Ķ������� */
        if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
        {
            NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
        }
    }

    /* ���PS��ĵȴ���־ */
    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ���ע������δ���룬�˳�����, �����ȴ� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* �������ȼ��Ƚϱ��ó�CS/PS�Ĵ������ȼ�����ת��Ϊ״̬����һ����Ϊ */
    enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
    enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
    enAdditionalAction   = NAS_MMC_GetPrioAddtionalAction(enCsAdditionalAction, enPsAdditionalAction);

    /* ���CS/PS��Ҫ��������ע�ᣬ��Ҫ�ڴ�״̬�����ȴ�ע���� */
    if (NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT == enAdditionalAction)
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvAreaLostInd_PlmnList_WaitCsPsRegRsltInd
 ��������  : �ȴ�������ע����ʱ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��4��4��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬��������list����ʧ����Ϣ
  3.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
  4.��    ��   : 2014��04��9��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:���ӷ���״̬�ϱ�����
  5.��    ��   : 2014��10��13��
    ��    ��   : w00167002
    �޸�����   : DTS2014102005694:G�£�CSע��ɹ���PS��δע��ɹ�ʱ����
               ����绰ҵ���ڵ绰ҵ����ʱ������MMû���ͷ����MMCû�з���ANY
               CELL������
  6.��    ��   : 2015��9��25��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvAreaLostInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�ע������Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */


    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, begin */
    /* �ϱ���Ӧ��CS/PS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-8, end */

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());


    /* ֪ͨMM/GMM���붪��,MM���ͷ�CSҵ�� */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����list����ʧ����Ϣ */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());
        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��WAS/GAS����LIST��������,Ǩ��״̬���ȴ�WAS/GAS LIST�����ظ�״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd
 ��������  : �ڵȴ�CS+PSע��������յ�Wģʽϵͳ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
   /* ����WASϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd
 ��������  : �ڵȴ�CS+PSע��������յ�Gģʽϵͳ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����GASϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    /* ���µ�ǰ�ȴ�CSPS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitCsPsRegRsltInd
 ��������  : ��list�����ĵȴ�CS/PS��ע����ʱ,�յ�RRMM_SUSPEND_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SUSPEND_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : ������ϵͳ״̬��ʱ����Ϊ��ǰ�����磬��ʱAPS����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST             *pstSuspendMsg = VOS_NULL_PTR;

    pstSuspendMsg = (RRMM_SUSPEND_IND_ST*)pstMsg;

    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ��������ͬ��״̬�� */
    switch (pstSuspendMsg->ucSuspendCause)
    {
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_PLMNSEARCH:

            /* �����㷢�͹���ʧ�� */
            NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, pstSuspendMsg->MsgHeader.ulSenderPid);

            /* ���·���״̬ */
            NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);

            NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

            /* ��Ҫ�����ͷ���· */
            NAS_MMC_SndMmRelReq();

            NAS_MMC_SndGmmRelReq();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            /* Ǩ��״̬���ȴ�RRC��·�ͷ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

            break;
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmSuspendInd_PlmnList_WaitCsPsRegRsltInd:Unexpected suspend type!");
            break;
    }

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitCsPsRegRsltInd
 ��������  : ��list�����ĵȴ�CS/PS��ע����ʱ,�յ�MMCMMC_SUSPEND_RSLT_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_SUSPEND_RSLT_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : �˳���ϵͳ״̬��ʱ��֪ͨAPS��ǰ��������
  4.��    ��   : 2012��04��26��
    ��    ��   : w00176964
    �޸�����   : GUL BG��Ŀ����
  5.��    ��   : 2013��2��7��
    ��    ��   : W00176964
    �޸�����   : Volte_phase3��Ŀ����:����IMS������ʱdisable Lģ���߼��޸�
  6.��    ��   : 2013��4��4��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬��������ʧ����Ϣ��Ǩ�Ƶ�OOC
  7.��    ��   : 2015��9��25��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ѡ��ǰ���뼼���Ѿ��ı䣬��Ҫ���³�ʼ�������Ľ��뼼�����ȼ� */
#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
#endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }


    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* �жϵ�ǰ����ģʽ */
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

        /* IDLE̬�´�GU��ϵͳ��LTE��,LTE�¿��ܷ���ע��򲻷���ע��
           �����MMC�ϱ�ע���� */
        /* ����CSPS��AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        /* ���µ�ǰ�ȴ�EPS��ע���� */
        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, begin */
#if (FEATURE_ON == FEATURE_IMS)
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, end */

        /* Ǩ��״̬���ȴ�L�µ�EPSע���� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_REG_IND, TI_NAS_MMC_WAIT_EPS_REG_IND_LEN);

        return VOS_TRUE;
    }
#endif

    /* �����ȴ�ע���� */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnList_WaitCsPsRegRsltInd
 ��������  : ��list�����ĵȴ�CS/PS��ע����ʱ,�յ�TI_NAS_MMC_WAIT_CSPS_REG_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_CSPS_REG_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��02��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��11��
    ��    ��   : w00176964
    �޸�����   : V7R1_GUTL��Ŀ����:TD��ģ��פ��̬����Ҫ֪ͨMM/GMM��������״̬
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnList_WaitCsPsRegRsltInd Enter");

    /* ����ȴ�ע������� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* ������������ �����ȴ�RRC�����ͷ� */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        return VOS_TRUE;
    }

    /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
    if (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitRrcConnRelInd
 ��������  : �б������������ͷ�״̬����OOS��ϢRRMM_LIMIT_SERVICE_CAMP_IND�Ĵ���
 �������  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND��Ϣ
             ulEventType - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��15��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitRrcConnRelInd(
        VOS_UINT32                          ulEventType,
        struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList(ulEventType, pstMsg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitCsPsRegRsltInd
 ��������  : �б�������ע����״̬����OOS��ϢRRMM_LIMIT_SERVICE_CAMP_IND�Ĵ���
 �������  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND��Ϣ
             ulEventType - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��15��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList_WaitCsPsRegRsltInd(
        VOS_UINT32                          ulEventType,
        struct MsgCB                       *pstMsg
)
{
    return NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList(ulEventType, pstMsg);
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitCsPsRegRsltInd
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
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitCsPsRegRsltInd(
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
 �� �� ��  : NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList
 ��������  : �б�����ʱ����OOS��Ϣ�Ĵ���
 �������  : pstMsg        - RRMM_LIMIT_SERVICE_CAMP_IND��Ϣ
             ulEventType - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��27��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_LIMIT_SERVICE_CAMP_IND_STRU        *pstRrmmLimitCampOnMsg = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pastIntraPlmnSrchInfo = VOS_NULL_PTR;
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU      *pstSearchRatInfo   = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU              *pstRatPrioList     = VOS_NULL_PTR;
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU    *pstListInfo        = VOS_NULL_PTR;
    VOS_UINT8                                ucRatCnt;

    pstRrmmLimitCampOnMsg = (RRMM_LIMIT_SERVICE_CAMP_IND_STRU *)pstMsg;

    pstSearchRatInfo = NAS_MMC_GetSearchCtrlInfo_PlmnList();
    pstRatPrioList   = NAS_MML_GetMsPrioRatList();
    pstListInfo      = NAS_MMC_GetSearchedPlmnListInfo_PlmnList();

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    pastIntraPlmnSrchInfo = (NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                             sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);
    /* memory alloc fail */
    if (VOS_NULL_PTR == pastIntraPlmnSrchInfo)
    {
        return VOS_TRUE;
    }

    /* �����е�RAT������Ϊ�Ѿ����� */
    for (ucRatCnt = 0; ucRatCnt < pstRatPrioList->ucRatNum; ucRatCnt++)
    {
        pstListInfo[ucRatCnt].enRatType = pstSearchRatInfo[ucRatCnt].enRat;

        pstSearchRatInfo[ucRatCnt].ucSearchedFlag = VOS_TRUE;
    }

    /* ���������б� */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstRrmmLimitCampOnMsg->stPlmnIdList));

    /* ��ת�����PLMN��Ϣ���浽���ر����� */
    PS_MEM_CPY(pastIntraPlmnSrchInfo, pstListInfo, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU) * NAS_MML_MAX_RAT_NUM);


    /* ɾ���б��н�ֹ��PLMN */
    NAS_MMC_DelForbPlmnFromAsSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* �ֶ�����ģʽ��ɾ�����û�ָ����PLMN */
    NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList(pastIntraPlmnSrchInfo);

    /* ��ά�ɲ���Ϣ���� */
    NAS_MMC_LogAsPlmnList(pastIntraPlmnSrchInfo);

    /* �û�LIST���� */
    if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* �����������������������ϱ���MSCC */
        NAS_MMC_SndMsccPlmnListCnf_PlmnList();


        /* �˳�״̬�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                VOS_TRUE,
                                pastIntraPlmnSrchInfo,
                                NAS_MMC_GetRegRsltInfo_PlmnList());
        NAS_MMC_FSM_QuitFsmL2();

        PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* �����������������������ϱ���MSCC */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* �˳�״̬�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                VOS_TRUE,
                                pastIntraPlmnSrchInfo,
                                NAS_MMC_GetRegRsltInfo_PlmnList());
        NAS_MMC_FSM_QuitFsmL2();

        PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);
        return VOS_TRUE;
    }
#endif


    /* ��Ҫ�������� */
    if (VOS_TRUE == NAS_MMC_IsExistAvailPlmnInSearchedPlmnList(pastIntraPlmnSrchInfo))
    {
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                VOS_TRUE,
                                pastIntraPlmnSrchInfo,
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pastIntraPlmnSrchInfo);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchCnf
 ��������  : �ڵȴ�WAS��LIST�����ظ�״̬,�յ��˳���Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�WAS��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��WAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasPlmnSearchCnf
 ��������  : �ڵȴ�WAS��LIST�����ظ�״̬,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�WAS��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��WAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchCnf
 ��������  : �ڵȴ�WAS��LIST�����ظ�״̬,�յ�RRMM_PLMN_SEARCH_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_PLMN_SEARCH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSearchcnf = VOS_NULL_PTR;

    pstPlmnSearchcnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* ֹͣ�ȴ�WAS�����ظ��ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    /* ����PLMN LIST�Ľ�� */
    NAS_MMC_ProcRrmmSearchCnf_PlmnList(pstPlmnSearchcnf);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchCnf
 ��������  : �ڵȴ�WAS��LIST�����ظ�״̬,�յ�RRMM_REL_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��18��
    ��    ��   : l00171473
    �޸�����   : DTS2012051104124, �����ж�REL INDԭ��ֵ.
                 WAS:���յ�RRMM_PLMN_SEARCH_REQʱ�������ϱ�����ԭ���rel ind��
                 ֻ���쳣ԭ���rel ind

  3.��    ��   : 2014��6��30��
    ��    ��   : w00176964
    �޸�����   : DSDS III:  WAS�쳣NO RF�ͷţ������OOC���д���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchCnf Enter!");

    /* �����ж�ԭ��ֵ */

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF);

    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    /* ����״̬���˳���� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

        /* ����5S�����Գ���LIST������ʱ�� */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
        }
        else
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
        }

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();


    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchCnf
 ��������  : �ڵȴ�WAS��LIST�����ظ�״̬,�յ�RRMM_SYS_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SYS_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitWasPlmnSearchCnf
 ��������  : ��list�����ĵȴ������ظ���Ϣʱ,�յ�RRMM_AREA_LOST_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_AREA_LOST_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��4��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
  3.��    ��   : 2014��04��9��
    ��    ��   : s00261364
    �޸�����   : V3R360_eCall��Ŀ:���ӷ���״̬�ϱ�����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitAsPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */


     /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, begin */
    /* �ϱ���Ӧ��CS/PS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-30, end */

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasPlmnSearchCnf
 ��������  : ��list�����ĵȴ������ظ���Ϣʱ,�յ�MMMMC_CS_REG_RESULT_IND��Ϣ��Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasPlmnSearchCnf
 ��������  : ��list�����ĵȴ������ظ���Ϣʱ,�յ�GMMMMC_PS_REG_RESULT_IND��Ϣ��Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasPlmnListCnfExpired_PlmnList_WaitWasPlmnSearchCnf
 ��������  : �ڵȴ�WAS��LIST�����ظ�״̬,�յ�TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��27��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasPlmnListCnfExpired_PlmnList_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{


    /* LIST���������У����������ϱ�RRMM_NOT_CAMP_ON����ʱ��Ҫ���ݵ�ǰפ��״̬����RAT��������� */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ������ģRAT��������� */

#if (FEATURE_ON == FEATURE_LTE)

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

#endif

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        /* ���µ�ǰRAT��������� */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);
    }

    /* ��WAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchCnf
 ��������  : �ڵȴ�GAS��LIST�����ظ�״̬,�յ��˳���Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�GAS��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasPlmnSearchCnf
 ��������  : �ڵȴ�GAS��LIST�����ظ�״̬,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�GAS��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchCnf
 ��������  : �ڵȴ�GAS��LIST�����ظ�״̬,�յ�RRMM_PLMN_SEARCH_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_PLMN_SEARCH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchcnf = VOS_NULL_PTR;

    pstPlmnSrchcnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* ֹͣ�ȴ�GAS�����ظ��ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF);

    /* ����PLMN LIST�Ľ�� */
    NAS_MMC_ProcRrmmSearchCnf_PlmnList(pstPlmnSrchcnf);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchCnf
 ��������  : �ڵȴ�GAS��LIST�����ظ�״̬,�յ�GRRMM_SYS_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:GRRMM_SYS_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasPlmnSearchCnf
 ��������  : ��list�����ĵȴ������ظ���Ϣʱ,�յ�MMMMC_CS_REG_RESULT_IND��Ϣ��Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasPlmnSearchCnf
 ��������  : ��list�����ĵȴ������ظ���Ϣʱ,�յ�GMMMMC_PS_REG_RESULT_IND��Ϣ��Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasPlmnListCnfExpired_PlmnList_WaitGasPlmnSearchCnf
 ��������  : �ڵȴ�GAS��LIST�����ظ�״̬,�յ�TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��27��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasPlmnListCnfExpired_PlmnList_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* LIST���������У����������ϱ�RRMM_NOT_CAMP_ON����ʱ��Ҫ���ݵ�ǰפ��״̬����RAT��������� */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ������ģRAT��������� */

#if (FEATURE_ON == FEATURE_LTE)

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

#endif

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        /* ���µ�ǰRAT��������� */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSuspendCnf
 ��������  : �ڵȴ�WAS��suspend�ظ�״̬,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSuspendCnf
 ��������  : �ڵȴ�WAS��suspend�ظ�״̬,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitWasSuspendCnf
 ��������  : �ڵȴ�WAS��suspend�ظ�״̬,�յ�RRMM_SUSPEND_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SUSPEND_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    /* �������ظ���� */
    NAS_MMC_ProcRrmmSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitWasSuspendCnf
 ��������  : �ڵȴ�WAS��suspend�ظ�״̬,�յ�TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
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
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitWasSuspendCnf: Timer Expired");

    /* ���ɻָ����ϣ���λ */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSuspendCnf
 ��������  : �ڵȴ�GAS��suspend�ظ�״̬,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSuspendCnf
 ��������  : �ڵȴ�GAS��suspend�ظ�״̬,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitGasSuspendCnf
 ��������  : �ڵȴ�GAS��suspend�ظ�״̬,�յ�RRMM_SUSPEND_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SUSPEND_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    /* �������ظ���� */
    NAS_MMC_ProcRrmmSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitGasSuspendCnf
 ��������  : �ڵȴ�GAS��suspend�ظ�״̬,�յ�TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011120702166:MMC��λ���޸�λ��Ϣ,��MMLģ���װ��λ��Ϣ��
                  �Թ�MM����ã�������λ��

  3.��    ��   : 2015��3��11��
    ��    ��   : wx270776
    �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitGasSuspendCnf: Timer Expired");

    /* ���ɻָ����ϣ���λ */

    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasPlmnSearchStopCnf
 ��������  : �ڵȴ�WAS��ֹͣ�����ظ�״̬,�յ�RRMM_PLMN_SEARCH_STOP_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_PLMN_SEARCH_STOP_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchStopCnf
 ��������  : �ڵȴ�WAS��ֹͣ�����ظ�״̬,�յ�RRMM_SYS_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_SYS_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��8��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf
 ��������  : �ڵȴ�WAS��ֹͣ�����ظ�״̬,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��28��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf
 ��������  : �ڵȴ�WAS��ֹͣ�����ظ�״̬,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchStopCnf
 ��������  : ��list�����ĵȴ�Was��ֹͣ�����ظ�ʱ,�յ�RRMM_PLMN_SEARCH_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_PLMN_SEARCH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��28��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��28��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 GUL�������޸�
  3.��    ��   : 2012��6��25��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 DTS2012062105468:MMC��stop plmn cnf��L��search cnf�Գ壬MMC���ӱ�����Ϊ�յ�WAS
                 ��stop plmn cnf���˳�״̬��
  4.��    ��   : 2014��7��9��
    ��    ��   : w00176964
    �޸�����   : DSDS III��Ŀ:����LIST NO RF�Գ�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT32                          ulIndex;

    pstPlmnSrchCnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
    if (RRC_PLMN_SEARCH_RLT_LIST_NO_RF == pstPlmnSrchCnf->ulSearchRlt)
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

     /*ֻ���������ɹ�ʱ�Ž��д��� */
    if (RRC_PLMN_SEARCH_RLT_LIST != pstPlmnSrchCnf->ulSearchRlt)
    {
        return VOS_TRUE;
    }

    /* LIST����������,��Ҫ���ݵ�ǰ�����Я�����Ѿ��������Ľ��뼼����Ϣ����RAT��������� */
    for ( ulIndex = 0; ulIndex < NAS_RRC_MAX_RAT_NUM; ulIndex++)
    {
        if ( RRC_NAS_RAT_LIST_SEARCH_CMPL == pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            /*��RRC�Ľ��뼼��ת����MML����ĸ�ʽ��Ȼ����� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat, &enRat);
            NAS_MMC_SetSearchedFlag_PlmnList(enRat);
        }
    }

    /* ���������б� */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstPlmnSrchCnf->PlmnIdList));

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchStopCnf
 ��������  : �ڵȴ�WAS��ֹͣ�����ظ�״̬,�յ�RRMM_REL_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��12��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��18��
    ��    ��   : l00171473
    �޸�����   : DTS2012051104124, WAS:���յ�RRMM_PLMN_SEARCH_STOP_REQʱ��
                 ���ܷ������쳣ԭ���rel ind����RRMM_PLMN_SEARCH_STOP_CNF,
                 �յ�rel indʱ��Ϊֹͣ�б���������.
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasPlmnSearchStopCnf: ENTERED");

    /* �����ж�ԭ��ֵ */

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* ��ǰ�û��б����� */
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
            {
                /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            }
            else
            {
                /* ��MSCC�ظ�LIST������� */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����״̬���˳���� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* ����5S�����Գ���LIST������ʱ�� */
    if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
    }
    else
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
    }

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasPlmnSearchStopCnf
 ��������  : �ڵȴ�WAS��ֹͣ�����ظ�״̬,�յ�TI_NAS_MMC_WAIT_WAS_STOP_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_WAS_STOP_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasPlmnSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf
 ��������  : �ڵȴ�WAS��ֹͣ�����ظ�״̬,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��28��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasPlmnSearchStopCnf
 ��������  : �ڵȴ�GAS��ֹͣ�����ظ�״̬,�յ�RRMM_PLMN_SEARCH_STOP_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_PLMN_SEARCH_STOP_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchStopCnf
 ��������  : �ڵȴ�GAS��ֹͣ�����ظ�״̬,�յ�GRRMM_SYS_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:GRRMM_SYS_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��8��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf
 ��������  : �ڵȴ�GAS��ֹͣ�����ظ�״̬,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchStopCnf
 ��������  : ��list�����ĵȴ�Gas��ֹͣ�����ظ�ʱ,�յ�RRMM_PLMN_SEARCH_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:RRMM_PLMN_SEARCH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��28��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��28��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 GUL���������޸�
  3.��    ��   : 2012��6��25��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 DTS2012062105468:MMC��stop plmn cnf��L��search cnf�Գ壬MMC���ӱ�����Ϊ�յ�L
                 ��stop plmn cnf���˳�״̬��
  4.��    ��   : 2014��7��9��
    ��    ��   : w00176964
    �޸�����   : DSDS III��Ŀ:����LIST NO RF�Գ�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT32                          ulIndex;

    pstPlmnSrchCnf = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

     /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
     if (RRC_PLMN_SEARCH_RLT_LIST_NO_RF == pstPlmnSrchCnf->ulSearchRlt)
     {
         /* ֹͣ������ʱ�� */
         NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

         NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

         return VOS_TRUE;
     }

     /*ֻ���������ɹ�ʱ�Ž��д��� */
    if (RRC_PLMN_SEARCH_RLT_LIST != pstPlmnSrchCnf->ulSearchRlt)
    {
        return VOS_TRUE;
    }

    /* LIST����������,��Ҫ���ݵ�ǰ�����Я�����Ѿ��������Ľ��뼼����Ϣ����RAT��������� */
    for ( ulIndex = 0; ulIndex < NAS_RRC_MAX_RAT_NUM; ulIndex++)
    {
        if ( RRC_NAS_RAT_LIST_SEARCH_CMPL == pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            /*��RRC�Ľ��뼼��ת����MML����ĸ�ʽ��Ȼ����� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat, &enRat);
            NAS_MMC_SetSearchedFlag_PlmnList(enRat);
        }
    }

    /* ���������б� */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstPlmnSrchCnf->PlmnIdList));

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasPlmnSearchStopCnf
 ��������  : �ڵȴ�GAS��ֹͣ�����ظ�״̬,�յ�TI_NAS_MMC_WAIT_GAS_STOP_CNF��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_GAS_STOP_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasPlmnSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsConnRelInd
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��30��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*�˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsConnRelInd
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*�˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsConnRelInd
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�ID_LMM_MMC_SUSPEND_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_SUSPEND_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ,������ͬ��״̬�� */
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg  = VOS_NULL_PTR;

    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ��������ͬ��״̬�� */
    switch (pstLSuspendMsg->ulSysChngType)
    {
        case MMC_LMM_SUS_TYPE_RSL:
        case MMC_LMM_SUS_TYPE_REDIR:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            break;

        case MMC_LMM_SUS_TYPE_HO:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            break;

        case MMC_LMM_SUS_TYPE_CCO:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsConnRelInd:Unexpected Suspend Type!");
            break;
    }

    if ( (MMC_LMM_SUS_TYPE_BUTT != pstLSuspendMsg->ulSysChngType)
      && (MMC_LMM_SUS_TYPE_CCO_REVERSE != pstLSuspendMsg->ulSysChngType))
    {
        NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                 NAS_MML_GetSimPsRegStatus());
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsConnRelInd
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�ID_LMM_MMC_STATUS_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_STATUS_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2012��04��26��
    ��    ��   : W00176964
    �޸�����   : GUL BG��Ŀ����
  4.��    ��   : 2014��02��8��
    ��    ��   : W00176964
    �޸�����   : VOLTE_Phase3��Ŀ����:�ȴ�EPS�����ͷ�ʱ�յ�L��ע��������Ҫ��һ���ȴ�IMSע����
  5.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg  = ( LMM_MMC_STATUS_IND_STRU* )pstMsg;

    /* ����LMM������״̬ */
    switch (pstLmmStatusIndMsg->ulConnState)
    {
        case MMC_LMM_CONN_ESTING:
        case MMC_LMM_CONNECTED_SIG:

            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
            break;

        case MMC_LMM_CONNECTED_DATA:

            NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);

            /* ֹͣ�ȴ�EPS��·�ͷŶ�ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

            NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();

            /* ��ҵ��ʱ��δ����LIST�������ѵ��������б�Ϊ��,����״̬��ʧ�ܵ��˳���� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                     VOS_FALSE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;

        case MMC_LMM_CONN_IDLE:

            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        default:

            break;
    }

    /* �ж�RRC�����Ƿ���� */
    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* ���ؼ����ȴ� */
        return VOS_TRUE;
    }

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, begin */
    /* �ȴ�IMS��ע���� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, end */

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* ��LMM����LIST��������,����פ��״̬Ϊ��פ��,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��פ��̬֪ͨMM/GMM������ʼ */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpscConnRelInd
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�ID_LMM_MMC_SYS_INFO_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_SYS_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��30��
    ��    ��   : l65478
    �޸�����   : ��Ǩ��Lģʱ,�����̰�CS���óɿ�ѡ����,���ǵȴ�PSע����ʱ
                 ���ݾ����ԭ��ֵ������
  3.��    ��   : 2012��4��18��
    ��    ��   : l00130025
    �޸�����   : DTS2012040200480,����ά��EPSע��״̬,��Lģ��CEREG/CGREG��ѯ���ϱ�ʹ��
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
  1.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 �����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC
  9.��    ��   : 2015��10��24��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);


    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpscConnRelInd
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�ID_LMM_MMC_ATTACH_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��25��
    ��    ��   : z00161729
    �޸�����   : V7R1 phase III����ע���޸�
  3.��    ��   : 2014��2��8��
    ��    ��   : w00176964
    �޸�����   : VOLTE_Phase3��Ŀ�޸�:����IMS֧��ʱdisable Lģ���߼�

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, begin */
    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, end */

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpscConnRelInd
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�ID_LMM_MMC_TAU_RESULT_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_TAU_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��26��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע���޸�
  3.��    ��   : 2014��2��8��
    ��    ��   : w00176964
    �޸�����   : VOLTE_Phase3��Ŀ�޸�:����IMS֧��ʱdisable Lģ���߼�

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, begin */
    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif
    /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-8, end */

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmDetachInd_PlmnList_WaitEpscConnRelInd
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�ID_LMM_MMC_DETACH_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_DETACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��26��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase III����:����ע���޸�

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmDetachInd_PlmnList_WaitEpsConnRelInd(
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
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enPsAdditionalAction);
    }

    /*����CS����һ���Ķ�������*/
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction)
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpscConnRelInd
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�MMCMMC_SUSPEND_RSLT_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_SUSPEND_RSLT_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2011��12��20��
    ��    ��   : h44270
    �޸�����   : �˳���ϵͳ״̬��ʱ��֪ͨAPS��ǰ��������
  4.��    ��   : 2012��5��3��
    ��    ��   : w00176964
    �޸�����   : GUL BG��Ŀ����
  7.��    ��   : 2013��4��4��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬����Ǩ�Ƶ�OOC
  8.��    ��   : 2015��9��25��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    /* ��ѡ��ǰ���뼼���Ѿ��ı䣬��Ҫ���³�ʼ�������Ľ��뼼�����ȼ� */
 #if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
 #endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());


        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �жϵ�ǰ����ģʽ */
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        /* �жϵ�ǰ���������Ƿ���� */
        if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
        {
            /* ���ؼ����ȴ� */
            return VOS_TRUE;
        }

        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

        /* ��L����LIST��������,״̬Ǩ�Ƶ�,����������ʱ�� */
        NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        /* ��פ��̬֪ͨMM/GMM������ʼ */
        if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
        {
            /* ��GMM��������ָʾ */
            NAS_MMC_SndGmmPlmnSchInit();

            /* ��MM��������ָʾ */
            NAS_MMC_SndMmPlmnSchInit();

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
        }

        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* ����CSPS��AdditionalAction */
    NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
    NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

    /* Ǩ��״̬���ȵ�CS/PSע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* Ǩ�Ƶ��ȴ�ע����״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

    /* ����������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnList_WaitEpsConnRelInd
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�TI_NAS_MMC_WAIT_EPS_CONN_REL_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_EPS_CONN_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��25��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  3.��    ��   : 2012��6��5��
    ��    ��   : w00176964
    �޸�����   : V7R1 C50 GUL BG��Ŀ����:PSҵ������5S��ʱ����֤LIST�����л��ᷢ��
  4.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitRrcConnRelIndExpired_PlmnList_WaitRrcConnRelInd Enter!");

    /* ����ҵ�񣬻ظ��б���ʧ�� */
    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();
    }
    else
    {
        NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();
    }

    /* ����δ��ʼ�������������������б�Ϊ�գ���Ҫ�����Գ��ԣ��˳�״̬������Ҫ�������� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());


    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsConnRelInd
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
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU     *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ����ڵȴ�IMS��ע�����Ŵ��� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* ��LMM����LIST��������,����פ��״̬Ϊ��פ��,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��פ��̬֪ͨMM/GMM������ʼ */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();

        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, end */


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsRegInd
 ��������  : ��list�����ĵȴ�EPSע����״̬,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��8��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  3.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsRegInd
 ��������  : ��list�����ĵȴ�EPSע����״̬,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��8��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortReq_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsRegInd
 ��������  : ��list�����ĵȴ�EPSע����״̬,�յ�ID_LMM_MMC_SUSPEND_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_SUSPEND_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��8��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg = VOS_NULL_PTR;
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
    pstLSuspendMsg = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* Lģ�£�����ԭ������GU�²�ͬ��ת��һ�¹���ԭ���� */
    NAS_MMC_ConvertLmmSysChngTypeToMmcType(pstLSuspendMsg->ulSysChngType, &enSuspendCause);

    /* ���Ϊ��������ȷ, �����������ϵͳ��ѡ */
    if (MMC_SUSPEND_CAUSE_BUTT <= enSuspendCause)
    {
        NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);
        return VOS_TRUE;
    }

    /* ���ݲ�ͬ�Ĺ���ԭ��ֵ��������ͬ��״̬�� */
    switch (enSuspendCause)
    {
        /* ���� С����ѡ ״̬�� */
        case MMC_SUSPEND_CAUSE_CELLRESELECT:
        case MMC_SUSPEND_CAUSE_REDIRECTION:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CELLRESEL);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        /* ����HANDOVER״̬�� */
        case MMC_SUSPEND_CAUSE_HANDOVER:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_HO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());

            break;

        /* ���� CCO״̬�� */
        case MMC_SUSPEND_CAUSE_CELLCHANGE:
            NAS_MMC_FSM_InitFsmL2(NAS_MMC_FSM_INTER_SYS_CCO);
            NAS_MMC_NotifyModeChange(NAS_MML_NET_RAT_TYPE_BUTT,
                                     NAS_MML_GetSimPsRegStatus());
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendInd_PlmnList_WaitEpsRegInd:Unexpected suspend type!");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpsRegInd
 ��������  : ��list�����ĵȴ�EPSע����״̬,�յ�ID_LMM_MMC_SYS_INFO_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_SYS_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��18��
    ��    ��   : l00130025
    �޸�����   : DTS2012040200480,����ά��EPSע��״̬,����ѯ���ϱ�ʹ��
  3.��    ��   : 2012��4��28��
    ��    ��   : W00166186
    �޸�����   : DTS2012042602593,MMû�б��浱ǰפ����PLMN�����º����жϳ���
  4.��    ��   : 2012��5��8��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
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
  9.��    ��   : 2015��10��24��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpsRegInd
 ��������  : ��list�����ĵȴ�EPSע����״̬,�յ�ID_LMM_MMC_ATTACH_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��3��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��14��
    ��    ��   : z00161729
    �޸�����   : GUL�������޸�
  3.��    ��   : 2012��11��22��
    ��    ��   : t00212959
    �޸�����   : DTS2012112006974
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enUeOperationMode;

    enUeOperationMode   =  NAS_MML_GetLteUeOperationMode();
    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

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
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* Ǩ��״̬���ȴ�EPS����·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpsRegInd
 ��������  : ��list�����ĵȴ�EPSע����״̬,�յ�ID_LMM_MMC_TAU_RESULT_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_TAU_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��3��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��14��
    ��    ��   : z00161729
    �޸�����   : GUL�������޸�
  3.��    ��   : 2012��11��22��
    ��    ��   : t00212959
    �޸�����   : DTS2012112006974
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg = VOS_NULL_PTR;

    pstLmmTauIndMsg = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    if (NAS_MMC_WAIT_REG_RESULT_IND_NULL != NAS_MMC_GetWaitRegRsltFlag_PlmnList())
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if ( VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /*��SMS ONLY,disable LTE,��#18�б��У�ע��ɹ�����L�����ͷ�����*/
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* Ǩ��״̬���ȴ�EPS����·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd
 ��������  : ��list�����ĵȴ�EPSע����״̬,�յ�ID_LMM_MMC_STATUS_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_STATUS_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��8��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  3.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    if ( VOS_FALSE == pstLmmStatusIndMsg->bitOpConnState)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd:bitOpConnState IS VOS_FALSE");
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

            /* ֹͣ������ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

            NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList();

            /* ����״̬��ʧ���˳��Ľ�� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;

        case MMC_LMM_CONN_IDLE:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_PlmnList_WaitEpsRegInd:Unexpected connection status!");

            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitEpsRegInd
 ��������  : ��list�����ĵȴ�EPSע����״̬,�յ�ID_LMM_MMC_AREA_LOST_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_AREA_LOST_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��8��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�ע������Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ���·���״̬ �ϱ��޷���*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    /* �����㷢��LIST��������,Ǩ��״̬���ȴ� LIST�����ظ�״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    /* ���ý�������״̬ */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmPlmnSearchCnf
 ��������  : ��list�����ĵȴ�LMM�������ظ����״̬,�յ�ID_LMM_MMC_AREA_LOST_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_AREA_LOST_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��4��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ���·���״̬ �ϱ��޷���*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmPlmnSearchCnf
 ��������  : ��list�����ĵȴ�LMM�������״̬,�յ�ID_LMM_MMC_SYS_INFO_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_SYS_INFO_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��6��
    ��    ��   : z00161729
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
  5.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                 �����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC
  6.��    ��   : 2015��10��24��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmPlmnSearchCnf
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�ID_LMM_MMC_ATTACH_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_ATTACH_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmPlmnSearchCnf
 ��������  : ��list�����ĵȴ�EPS��·�ͷ�״̬,�յ�ID_LMM_MMC_TAU_RESULT_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_TAU_RESULT_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmPlmnSearchCnf
 ��������  : ����MSCC��IMS VOICE�Ƿ������Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�������
             VOS_FALSE:����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
1.��    ��   : 2015��7��22��
  ��    ��   : s00217060
  �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ����ڵȴ�IMS��ע�����Ŵ��� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpsRegInd
 ��������  : ��list�����ĵȴ�EPSע����״̬,�յ�MMCMMC_SUSPEND_RSLT_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_SUSPEND_RSLT_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��8��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  3.��    ��   : 2013��4��4��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:�յ�NO RF ��״̬����Ǩ�Ƶ�OOC״̬
  4.��    ��   : 2015��9��25��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmcSuspendRslt_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ѡ��ǰ���뼼���Ѿ��ı䣬��Ҫ���³�ʼ�������Ľ��뼼�����ȼ� */
 #if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        NAS_MMC_InitCsgListSearchRatInfo_PlmnList();
    }
    else
 #endif
    {
        NAS_MMC_InitSearchRatInfo_PlmnList();
    }

    NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                             NAS_MML_GetSimPsRegStatus());

    if (VOS_FALSE == NAS_MML_GetRfAvailFlg())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ����δ����LIST�������������������б�Ϊ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �жϵ�ǰ����ģʽ */
    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

        /* ����CSPS��AdditionalAction */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_BUTT);

        NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_CS);
        NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_PS);

        /* Ǩ�Ƶ��ȴ�ע����״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND, TI_NAS_MMC_WAIT_CSPS_REG_IND_LEN);

        return VOS_TRUE;
    }

    /* �����ȴ�ע���� */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitEpsRegIndExpired_PlmnList_WaitEpsRegInd
 ��������  : ��list�����ĵȴ�EPSע����״̬,�յ�TI_NAS_MMC_WAIT_EPS_REG_IND��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_EPS_REG_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��8��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitEpsRegIndExpired_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsRegIndExpired_PlmnList_WaitEpsRegInd Enter");

    /* ����ȴ�ע������� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* ������������ �����ȴ�EPS�����ͷ� */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* Ǩ��״̬���ȴ�EPS��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;

}


/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsRegInd
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
VOS_UINT32 NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU     *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ����ڵȴ�PS��ע����������ȴ�PSע���� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_PS == (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_PS))
    {
        return VOS_TRUE;
    }

    /* ����ȴ�ע������� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    /* ֹͣ�ȴ�ע�����ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        if (VOS_TRUE == NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn())
        {
            NAS_MMC_SndLmmRelReq();
        }

        /* Ǩ��״̬���ȴ�EPS����·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }

    /* ���ݵ�ǰ�Ľ���ģʽ������LIST��������,Ǩ��״̬������������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-7, end */


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchCnf
 ��������  : ��list�����ĵȴ�LMM�������ظ�ʱ,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��30��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�LMM��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��LMM����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcTafPlmnListAbortReq_PlmnList_WaitLmmPlmnSearchCnf
 ��������  : ��list�����ĵȴ�LMM�������ظ�ʱ,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcTafPlmnListAbortReq_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�LMM��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��LMM����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchCnf
 ��������  : ���list�����ĵȴ�LMM�������ظ�ʱ,�յ�ID_LMM_MMC_PLMN_SRCH_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_PLMN_SRCH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchcnf = VOS_NULL_PTR;

    pstLmmPlmnSrchcnf = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* �ж�LIST������� */
    NAS_MMC_ProcLmmSearchCnf_PlmnList(pstLmmPlmnSrchcnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmPlmnListCnfExpired_PlmnList_WaitLmmPlmnSearchCnf
 ��������  : ��list�����ĵȴ�LMM�������ظ�ʱ,�յ�TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
   3.��    ��   : 2012��4��27��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitLmmPlmnListCnfExpired_PlmnList_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* LIST���������У����������ϱ�RRMM_NOT_CAMP_ON����ʱ��Ҫ���ݵ�ǰפ��״̬����RAT��������� */
    if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ������ģRAT��������� */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        /* ���µ�ǰRAT��������� */
        NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
    }

    /* ��LMM����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmSuspendCnf
 ��������  : ��list�����ĵȴ�LMM�Ĺ���ظ�ʱ,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��30��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmSuspendCnf
 ��������  : ��list�����ĵȴ�LMM�Ĺ���ظ�ʱ,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendCnf_PlmnList_WaitLmmSuspendCnf
 ��������  : ��list�����ĵȴ�LMM�Ĺ���ظ�ʱ,�յ�ID_LMM_MMC_SUSPEND_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_SUSPEND_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II

  3.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011120702166:MMC��λ���޸�λ��Ϣ,��MMLģ���װ��λ��Ϣ��
                  �Թ�MM����ã�������λ��
  4.��    ��   : 2012��10��7��
    ��    ��   : s46746
    �޸�����   : for V7R1C50_At_Abort����פ���б����������У������û��б�������֮�����û��б�������
                 ����û���ٴγ�������

  5.��    ��   : 2015��3��11��
    ��    ��   : wx270776
    �޸�����   : DTS2015011212939:���Ӹ�λ����
  6.��    ��   : 2015��11��04��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendCnf_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_CNF_STRU           *pstLmmSuspendCnf = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    VOS_UINT32                          ulNeedPlmnSearch;

    pstLmmSuspendCnf  = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    if ( MMC_LMM_FAIL  == pstLmmSuspendCnf->ulRst )
    {
        /* ���帴λ */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    /* �ж�״̬���˳�����Ƿ�Ϊ�棬���Ϊ��*/
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        ulNeedPlmnSearch = VOS_FALSE;

        /*֪ͨMSCC�ظ����Ϊ��*/
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            }

            ulNeedPlmnSearch = VOS_TRUE;
        }
        else
        {
            if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* ��MSCC�ظ�LIST������� */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* ����״̬��ABORT���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��ȡ������һ�����뼼�� */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmSuspendCnf_PlmnList: Get next search rat fail.");

        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* �ϱ�LIST������� */
        NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

        /* ����״̬���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                          (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                          NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                          NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
    NAS_MML_SetCurrNetRatType(enRat);

    /* ���¸�����ģʽ����LIST��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(enRat);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PlmnList_WaitLmmSuspendCnf
 ��������  : ��list�����ĵȴ�LMM�Ĺ���ظ�ʱ,�յ�TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011120702166:MMC��λ���޸�λ��Ϣ,��MMLģ���װ��λ��Ϣ��
                  �Թ�MM����ã�������λ��

  3.��    ��   : 2015��3��11��
    ��    ��   : wx270776
    �޸�����   : DTS2015011212939:���Ӹ�λ����
* ****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PlmnList_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PlmnList_WaitLmmSuspendCnf: Timer Expired");

    /* ���ɻָ����ϣ���λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmPlmnSearchStopCnf
 ��������  : ��list�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�ID_LMM_MMC_STOP_PLMN_SRCH_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_STOP_PLMN_SRCH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II

  3.��    ��   : 2012��9��27��
    ��    ��   : z40661
    �޸�����   : DTS2012083102377,��ʱ��ID��д����
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);


    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf
 ��������  : ��list�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��30��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ABORT��־λ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf
 ��������  : ��list�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTafPlmnListAbortFsmMsg_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ABORT��־λ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC����ı�� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchStopCnf
 ��������  : ��list�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�ID_MSCC_MMC_PLMN_LIST_ABORT_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ID_LMM_MMC_PLMN_SRCH_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��28��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��28��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 GUL�������޸�
  3.��    ��   : 2012��6��25��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 DTS2012062105468:MMC��stop plmn cnf��L��search cnf�Գ壬MMC���ӱ�����Ϊ�յ�L
                 ��stop plmn cnf���˳�״̬��
  4.��    ��   : 2012��9��27��
    ��    ��   : z40661
    �޸�����   : DTS2012083102377,��ʱ��ID��д����
  5.��    ��   : 2014��7��9��
    ��    ��   : w00176964
    �޸�����   : DSDS III��Ŀ:LIST�����Գ��յ�NO RF�Ĵ���
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchCnf = VOS_NULL_PTR;
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList;
    VOS_UINT32                          ulIndex;


    pstLmmPlmnSrchCnf = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;
    pstGuPlmnIdList   = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmPlmnSrchCnf_PlmnList_WaitLmmPlmnSearchStopCnf:ERROR: Memory Alloc Error");
        return VOS_TRUE;
    }

    /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
    if (MMC_LMM_PLMN_SRCH_RLT_LIST_NO_RF == pstLmmPlmnSrchCnf->enRlst)
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);
        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }

    /*ֻ���������ɹ�ʱ�Ž��д��� */
    if (MMC_LMM_PLMN_SRCH_RLT_LIST_SUCC != pstLmmPlmnSrchCnf->enRlst)
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);
        return VOS_TRUE;
    }

    /* ���µ�RAT������� */
    for ( ulIndex = 0; ulIndex < MMC_LMM_MAX_RAT_NUM; ulIndex++)
    {
        if ( MMC_LMM_RAT_LIST_SEARCH_CMPL == pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            NAS_MMC_SetSearchedFlag_PlmnList((MMC_LMM_RAT_TYPE_ENUM_UINT8)(pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat));
        }
    }

    /*ת��L��ʽ�������б��ΪGU��ʽ��*/
    NAS_MMC_ConvertLmmPlmnIdListToGUFormat(&(pstLmmPlmnSrchCnf->stPlmnIdList), pstGuPlmnIdList);

    /*���������б�*/
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(pstGuPlmnIdList);

    PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);


    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);


    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmPlmnSearchStopCnf
 ��������  : ��list�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmPlmnSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmPlmnSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList();

    return VOS_TRUE;
}


#endif

/*********************************************************************************/
/*************************PLMN LIST��������***************************************/
/*********************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_IsUserPlmnList_PlmnList
 ��������  : �жϵ�ǰ�Ƿ����û�LIST����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  �û�LIST����
             VOS_FALSE �ڲ�LIST����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��01��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsUserPlmnList_PlmnList(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;

   /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if ( (ID_MSCC_MMC_PLMN_LIST_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
      || (TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcFsmAbort_PlmnList
 ��������  : list�������ڲ�abort�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcFsmAbort_PlmnList(VOS_VOID)
{
    /* ��Ҫ��MSCC�ظ���� */
    if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
    {
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            return;
        }

#if (FEATURE_ON == FEATURE_CSG)
        if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();
        }
#endif
    }
    else
    {
        NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMsccListSearchCnfMsg_PlmnList
 ��������  : ��MSCC����LIST���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccListSearchCnfMsg_PlmnList(VOS_VOID)
{
    if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* ������ͨLIST������� */
        NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        return;
    }

#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* ����CSG LIST������� */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
    }
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList
 ��������  : ���������Գ���list������ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_StartPeriodTryingUserListSrchTimer_PlmnList(VOS_VOID)
{

    if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* ����5S�����Գ���LIST������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
        return;
    }


#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* ����5S�����Գ���CSG LIST������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
    }
#endif

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMsccPlmnListRejMsg_PlmnList
 ��������  : ��MSCC����LIST rej��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPlmnListRejMsg_PlmnList(VOS_VOID)
{
    if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
    {
        /* ����LIST REJ��MSCC */
        NAS_Mmc_SndMsccPlmnListRej();
        return;
    }

#if (FEATURE_ON == FEATURE_CSG)
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        /* ����CSG LIST REJ��MSCC */
        NAS_MMC_SndMsccCsgListSearchRej();
    }
#endif
    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAnyCellSrch_PlmnList
 ��������  : �жϵ�ǰ�Ƿ���Ҫanycell����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��Ҫanycell����
             VOS_FALSE ����Ҫanycel����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��31��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedAnyCellSrch_PlmnList(VOS_VOID)
{
    /* ����Ч�������Ҫ�ж���L1�Ƿ��Ѿ����й�anycell����
       ����Ѿ����й�anycell������LIST�����˳�����Ҫ�ظ�
       ����anycell����;����LIST���˳�����Ҫ����һ��anycell
       ���� */
    if (VOS_FALSE == NAS_MML_IsUsimStausValid())
    {
        /* RRC���Ӵ���˵��δ����������LIST����״̬����ȴ�RRC�����ͷ�
           RRC���Ӳ������ҽ�������״̬˵���Ѿ����й�������δ��� */
        if (VOS_TRUE == NAS_MML_IsRrcConnExist())
        {
            return VOS_TRUE;
        }

        if(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcCsRegRslt_PlmnList
 ��������  : ����CS��ע����
 �������  : pstCsRegRsltInd  CSע������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��28��
    ��    ��   : w00167002
    �޸�����   : DTS2011112406707:����ǰΪ�������ҵ�ǰ��AdditionalAction��Ϊ
                ��ʼ��Чֵ���򲻸��µ�ǰ��AdditionalAction��ֵ����������ǰΪ
                �����̻�ǰΪ��������AdditionalActionΪ��ʼ��Чֵ�������
                ��ǰ��AdditionalAction��ֵ.
                �޸�ԭ��:��ROAMING BROKERʱ������1��ʧ��,ע��ʧ��1�κ�
                MMC��Ҫ����������MMC����Ҫ��������Ľ��(����ѡ��״̬��)��
                ���յ�ϵͳ��Ϣ��ʱ�򣬼����̻����MMC��AdditionalAction��ֵ,
                ����ROMING BROKER����ʧЧ��
   3.��    ��   : 2011��12��5��
     ��    ��   : z00161729
     �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
   4.��    ��   : 2011��12��20��
     ��    ��   : w00176964
     �޸�����   : V7R1 PhaseIV ����:UT�޸ģNNAS_MMC_SetUserSpecPlmnRegisterStatus
                 ֻ������״̬����ON PLMN�½�������
  5.��    ��   : 2012��1��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������
                  ͳһ����ע��ADDITIONAL ACTION��ֵ�������û��Զ����ԭ��ֵ(>=256)����
                  ������ע����������ǰ֧��Lģ����ע��ԭ��ֵС��260ʱ֪ͨLMM.
                  ���������̣�MMC����Ҫ֪��MM/GMM�ϱ����Ƿ���������̡�
  6.��    ��   : 2012��1��20��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:��ע��ʧ�ܵ���Ϣ֪ͨ������ע����������
                  �ܽ��и��õ���չ.
  7.��    ��   : 2012��3��1��
    ��    ��   : w00176964
    �޸�����   : DTS2012022407450:����ATTACHʱ,MM����֪ͨLMM��ʱCS��ע������������TAU�����Ͳ���ȷ
  8.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
  9.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
 10.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
 11.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 12.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
 13.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
 14.��    ��   : 2014��05��4��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ����
 15.��    ��   : 2014��11��3��
    ��    ��   : z00161729
    �޸�����   : ��������������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcCsRegRslt_PlmnList(
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRsltInd
)
{
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
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

        /* ��ǰSYSCFG��L����ʱ����Ҫ��LMM֪ͨ */
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
        enAdditionalAction = NAS_MMC_ProcCsRegFail(MM_MMC_CS_REG_RESULT_IND,
                                                   pstCsRegRsltInd);

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
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPsRegRslt_PlmnList
 ��������  : ��Psע�����Ĵ���
 �������  : pstPsRegRsltInd PSע������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��28��
    ��    ��   : w00167002
    �޸�����   : DTS2011112406707:����ǰΪ�������ҵ�ǰ��AdditionalAction��Ϊ
                ��ʼ��Чֵ���򲻸��µ�ǰ��AdditionalAction��ֵ����������ǰΪ
                �����̻�ǰΪ��������AdditionalActionΪ��ʼ��Чֵ�������
                ��ǰ��AdditionalAction��ֵ.
                �޸�ԭ��:��ROAMING BROKERʱ������1��ʧ��,ע��ʧ��1�κ�
                MMC��Ҫ����������MMC����Ҫ��������Ľ��(����ѡ��״̬��)��
                ���յ�ϵͳ��Ϣ��ʱ�򣬼����̻����MMC��AdditionalAction��ֵ,
                ����ROMING BROKER����ʧЧ��
  3.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 Phase IV����,��ǰSYSCFG��L����ʱ��Ҳ��Ҫ��LMM֪ͨID_MMC_LMM_ACTION_RESULT_REQ
  4.��    ��   : 2011��12��20��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV ����:UT�޸ģNNAS_MMC_SetUserSpecPlmnRegisterStatus
                 ֻ������״̬����ON PLMN�½�������
  5.��    ��   : 2012��1��3��
    ��    ��   : w00167002
    �޸�����   : DTS2011122006209:g��PS ONLYע��ɹ�_����ΪCS��ע��ʧ��4�κ�δ��������
                ͳһ����ע��ADDITIONAL ACTION��ֵ�������û��Զ����ԭ��ֵ(>=256)����
                ������ע����������ǰ֧��Lģ����ע��ԭ��ֵС��260ʱ֪ͨLMM��ǰ��ע����.
                ���������̣�MMC����Ҫ֪��MM/GMM�ϱ����Ƿ���������̡�
  6.��    ��   : 2012��3��1��
    ��    ��   : w00176964
    �޸�����   : DTS2012022407450:����GMM������RAU/ATTACH���ͣ�MMCת����LMM
  7.��    ��   : 2012��03��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012032307791,����LMMע����,CombineRegʱ��Ҫ���ֽ����
  8.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
  9.��    ��   : 2012��6��8��
    ��    ��   : l00130025
    �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨAPS/CDS��Ϣ���޷�����
 10.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
 11.��    ��   : 2012��12��6��
    ��    ��   : s00217060
    �޸�����   : DTS2012120410842:ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbLa,ForbGprs����Ϣ
 12.��    ��   : 2013��05��08��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
 13.��    ��   : 2013��12��24��
    ��    ��   : z00161729
    �޸�����   : SVLTE֧��NCELL����
 14.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
 15.��    ��   : 2014��05��4��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ����
*****************************************************************************/
VOS_VOID NAS_MMC_ProcPsRegRslt_PlmnList(
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRsltInd
)
{
    NAS_MML_LAI_STRU                                       *pstLai         = VOS_NULL_PTR;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU                        stActionRslt;
    NAS_MML_PROC_TYPE_ENUM_U32                              enProcType;

    /* ת�����͸�L��proctype */
    enProcType = NAS_MML_PROC_BUTT;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverGmmActionTypeToMml(pstPsRegRsltInd->enGmmActionType, &enProcType);


    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enReqDomain, &stActionRslt.enReqDomain);

    NAS_MMC_ConvertGmmRegDomainToMmcDomain(pstPsRegRsltInd->enRsltDomain, &stActionRslt.enRstDomain);



#endif
    pstLai              = NAS_MML_GetCurrCampLai();

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */

    /* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

    if (GMM_MMC_ACTION_RESULT_SUCCESS == pstPsRegRsltInd->enActionResult)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-10, begin */
        /* ����ע������Ϣ */
        NAS_MMC_SaveRegRsltCtx(GMM_MMC_PS_REG_RESULT_IND, pstPsRegRsltInd);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-10, end */

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


        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        NAS_MMC_UpdatePsRegStatePsRegSucc();

        /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
        /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */

#if   (FEATURE_ON == FEATURE_LTE)

            /* ��ǰSYSCFG��L����ʱ����Ҫ��LMM֪ͨ */
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
            /* ��ǰSYSCFG��L����ʱ����Ҫ��LMM֪ͨ */
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
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedPlmnSearch_PlmnList
 ��������  : �Ƿ���Ҫ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��Ҫ���� VOS_TRUE
             ����Ҫ���� VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��8��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  3.��    ��   : 2012��6��8��
    ��    ��   : s46746
    �޸�����   : for CS/PS mode 1���б�������ɺ������Ҫ����������GU��������Ҫ����
  4.��    ��   : 2013��10��17��
    ��    ��   : l65478
    �޸�����   : DTS2013102103487:DT����:�ڵ���ʧ��ʱҲ��Ҫ��������
  5.��    ��   : 2014��01��10��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII��Ŀ
  6.��    ��   : 2015��1��14��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  7.��    ��   : 2015��4��20��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
  8.��    ��   : 2015��6��19��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsNeedPlmnSearch_PlmnList(VOS_VOID)
{
    VOS_UINT32                                              ulIsNormalService;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdateRslt;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause;

    enPsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
    enCsRegCause            = NAS_MML_REG_FAIL_CAUSE_NULL;
#endif

    ulIsNormalService = NAS_MMC_IsNormalServiceStatus();

    /* ��ǰ����Ч��Ϊ���Ʒ��� */
    if ((VOS_TRUE == NAS_MML_IsUsimStausValid())
     && (VOS_FALSE == ulIsNormalService))
    {
        return VOS_TRUE;
    }

    /* ��ǰNAS��������δפ������ */
    if (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == NAS_MMC_GetSpecPlmnSearchState())
    {
        return VOS_TRUE;
    }

    /* �����Ҫanycell����,�򷵻�true */
    if (VOS_TRUE == NAS_MMC_GetAnyCellSrchFlg_PlmnList())
    {
        return VOS_TRUE;
    }

    /* ����ע�����Դ�ʱ,��PS����CSע��ʧ��#17,��Ҫ�������� */
    if (VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_CS))
    {
        return VOS_TRUE;
    }
    if (VOS_TRUE == NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(NAS_MSCC_PIF_SRVDOMAIN_PS))
    {
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    enLUeMode            = NAS_MML_GetLteUeOperationMode();
    enAdditionUpdateRslt = NAS_MML_GetAdditionUpdateRslt();

    /* ��ǰ��ģL */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* ��ǰ���뼼����ΪLTE */
    if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
    /* ����CS/PS mode 1��IMS VOICE���� */
    if ((VOS_TRUE                              == NAS_MML_GetImsVoiceAvailFlg())
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 != enLUeMode))

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
    {
        return VOS_FALSE;
    }

    /* addition update ieΪ"SMS ONLY"��"CSFB not preferred" */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableL_CombinedRegSuccAdditionUpdateRslt(enAdditionUpdateRslt))
    {
        return VOS_TRUE;
    }

    /* ��ǰפ��������ԭ��ֵ#18�б��� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    /* NAS_MMC_GetRegRsltAttemptCounterΪ5 */
    if (NAS_MML_MAX_PS_REG_FAIL_CNT == NAS_MMC_GetRegRsltAttemptCounter(NAS_MMC_GetRegRsltType()))
    {
        /* ��ȡ֮ǰע��ʧ�ܵ�ԭ��ֵ */
       NAS_MMC_GetDomainRegStatusInRegInfoList(NAS_MML_GetCurrCampPlmnId(),
                                               NAS_MML_NET_RAT_TYPE_LTE,
                                               &enCsRegCause,
                                               &enPsRegCause);

        if (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause22AttmptCntMaxTimes();
        }

        /* 24301_CR1884R4_(Rel-11)_C1-140658-C1-140643-C1-140393-C1-140368-C1-140004-24301-b90-TA-IMSVoPS-EPS-only
          TAU ACCEPT��EPS ONLY�ɹ�������ԭ��ֵΪ16,17��CS/PS1��DIABLE LTE����������
          persistent EPS bearer�Ƿ���ڣ���Ӧ24301 5.5.3.3.4.3�½�:
              #16 and #17:a UE operating in CS/PS mode 1 of operation with "IMS voice not available"
          and with a persistent EPS bearer context shall wait until the radio bearer
          associated with the persistent EPS bearer context has been released. When
          the radio bearer associated with the persistent EPS bearer context has been
          released and the UE is registered for EPS services only, operating in CS/PS
          mode 1 of operation with "IMS voice not available", then the UE shall attempt
          to select GERAN or UTRAN radio access technology and proceed with appropriate
          MM or GMM specific procedures and disable the E-UTRA capability (see subclause 4.5).
          ��CR��Э��汾���� */
        if (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause16AttmptCntMaxTimes();
        }

        if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == enCsRegCause)
        {
            return NAS_MMC_IsNeedDisableL_RegFailCause17AttmptCntMaxTimes();
        }

        return VOS_TRUE;
    }

#endif


    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SortSearchedPlmnList_PlmnList
 ��������  : �����������б��������
 �������  : pstPlmnSearchList �ѵ����б�
 �������  : pstReportList     �������ϱ��б�
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��20��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    NAS_MMC_SortSearchedPlmnList_PlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnSearchList,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstReportList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulRatNum;

    /* ��ʼ���б� */
    PS_MEM_SET(pstReportList, 0x0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));

    /* ��ѡ���б�������HPLMN��EHPLMN */
    NAS_MMC_AddEHPlmnInPlmnSelectionList(pstReportList);

    /* ��ѡ���б�������UPLMN��OPLMN */
    NAS_MMC_AddUOPlmnInPlmnSelectionList(pstReportList);

    ulRatNum = NAS_MML_GetMsPrioRatList()->ucRatNum;

    /* ���¸����ȼ����б�״̬������ʣ�µĸߵ��������� */
    for(i = 0; i < ulRatNum; i++)
    {
        /* ���������Ҫ��ʣ�����粹�䵽�б� */

        NAS_MMC_UpdatePlmnListInPlmnSelectionList((&pstPlmnSearchList[i]),
                                                  pstReportList,
                                                  VOS_TRUE,
                                                  VOS_TRUE);
    }

    /*���¶Ըߵ����������������*/
    NAS_MMC_SortAvailPlmnInPlmnSelectionList(pstReportList);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnStatus_PlmnList
 ��������  : ��ȡ�б���ÿ��PLMN ID��״̬
 �������  : pstPlmnId                 �ϱ��б��е�ÿ��PLMN ID
             usRaMode                  ÿ��PLMN ID��Ӧ�Ľ���ģʽ
 �������  : pucStatus  PLMN ID��״̬
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��09��21��
    ��    ��   : W00166186
    �޸�����   : V7R1 PHASE II
  3.��    ��   : 2011��11��24��
    ��    ��   : w00167002
    �޸�����   : DTS2011112405567:ԭ�еĺ�����NAS_MML_IsPlmnIdInDestPlmnList
                 ����ΪNAS_MML_IsBcchPlmnIdInDestSimPlmnList,������ȷ�ж�
                 ��������ͣ���������ȽϿ��ܻ����
*****************************************************************************/
VOS_VOID NAS_MMC_GetPlmnStatus_PlmnList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                          *pucStatus,
    VOS_UINT16                          usRaMode
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enOrigNetType;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo;
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId = VOS_NULL_PTR;

    /* ��ǰ�ڷ�פ��״̬�£�˫ģʱ���л�����һ��ģʽ�·����б�������
       ����פ��״̬�£��ڵ�ǰģʽ�¾Ϳ��԰�����ģʽ�µ�PLMN���������ϱ�������
       ����Ҫ������������ֱ��ȡRPLMN��RAT */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_GetOrigenSearchRat_PlmnList(&enOrigNetType);
    }
    else
    {
        enOrigNetType = NAS_MML_GetCurrNetRatType();
    }

    /* ��ȡ��ֹ������Ϣ */
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();


    /* ��forbid plmn�б��� */
    if(VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                  pstForbidPlmnInfo->ucForbPlmnNum,
                                                  pstForbidPlmnInfo->astForbPlmnIdList))
    {
        *pucStatus              = NAS_MSCC_PIF_PLMN_STATUS_FORBIDDEN;
    }
    else
    {
        *pucStatus              = NAS_MSCC_PIF_PLMN_STATUS_AVAILIBLE;
    }

    /*��PLMN���ڵ�ǰLAI��PLMNʱ,����Ϊ��״̬Ϊ��ǰ*/
    if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
    {
        pstCurPlmnId = NAS_MML_GetCurrCampPlmnId();

        if ( (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstCurPlmnId, pstPlmnId))
            &&( usRaMode == enOrigNetType))
        {
            if (NAS_MSCC_PIF_PLMN_STATUS_FORBIDDEN != *pucStatus)
            {
                *pucStatus = NAS_MSCC_PIF_PLMN_STATUS_CURRENT;
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuidTafMmcPlmnListInd_PlmnList
 ��������  : ������ϢID_MMC_MSCC_PLMN_LIST_CNF
 �������  : ��
 �������  : pstSndTafMsg
 �� �� ֵ  : VOS_TRUE ����ɹ�
             VOS_FALSE ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��23��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ:ɾ��NAS_FEATURE_BLACK_WHITE_PLMN��
  3.��    ��   : 2012��07��25��
    ��    ��   : t00212959
    �޸�����   : DTS2011110807051:ֻ����������ȼ���EHPLMN
  4.��    ��   : 2012��08��20��
    ��    ��   : w00176964
    �޸�����   : GUTL PhaseII����:�ϱ��б���ɾ����ֹRAT��PLMN
  5.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
  6.��    ��   : 2015��1��15��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_UINT32    NAS_MMC_BuildTafMmcPlmnListIndMsg_PlmnList(
    MMC_MSCC_PLMN_LIST_CNF_STRU          *pstSndTafMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstReportList = VOS_NULL_PTR;
    VOS_UINT32                              i;
    VOS_UINT32                              j;

    NAS_MML_HPLMN_CFG_INFO_STRU            *pstHplmnCfgInfo = VOS_NULL_PTR;

    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg   = VOS_NULL_PTR;

    /* ��ȡ��ֹ���뼼����PLMN��Ϣ */
    pstDisabledRatPlmnCfg = NAS_MML_GetDisabledRatPlmnInfo();

    pstHplmnCfgInfo = NAS_MML_GetHplmnCfg();

    pstReportList   = (NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                                           sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));
    if (VOS_NULL_PTR == pstReportList)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnListCnf_PlmnList: ALLOC MEM FAIL!");
        return VOS_FALSE;
    }

    PS_MEM_SET(pstSndTafMsg, 0, sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU));
    pstSndTafMsg->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndTafMsg->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_LIST_CNF;
    pstSndTafMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndTafMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndTafMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSndTafMsg->ulCnt                       = 0;

    /* ���������б�������� */
    NAS_MMC_SortSearchedPlmnList_PlmnList(NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                          pstReportList);

    /* ɾ���ظ���PLMN */
    NAS_MMC_DelDuplicatedPlmnWithRatInPlmnList(pstReportList);

    if (VOS_TRUE == pstHplmnCfgInfo->ucEhplmnSupportFlg)
    {
        if (NAS_MML_EHPLMN_PRESENT_IND_HIGHEST == NAS_MML_GetEHplmnPresentInd())
        {
            /* ���������ȼ���ߵ�EHPLMN,������EHPLMN��ɾ�� */
            NAS_MMC_DelLowPrioEHPlmn(pstReportList);
        }
    }

    /* ���ź�����б��е����������Ϣ�ṹ�� */
    for ( i = 0 ; i < pstReportList->usSearchPlmnNum; i++ )
    {
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
        /* �ж�PLMN�ں��������߲��ڰ����������ϱ� */
        if (VOS_TRUE == NAS_MML_IsPlmnIdForbiddenByWhiteBlackList(&(pstReportList->astPlmnSelectionList[i].stPlmnId)))
        {
            continue;
        }
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

        /* ɾ���ڽ�ֹ���뼼��������Ľ��뼼�� */
        NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList(&(pstReportList->astPlmnSelectionList[i]),
                                                  pstDisabledRatPlmnCfg->ulDisabledRatPlmnNum,
                                                  pstDisabledRatPlmnCfg->astDisabledRatPlmnId);

        /* ɾ���ڽ�ֹRAT�б��еĽ��뼼�� */
        NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo(&(pstReportList->astPlmnSelectionList[i]));

        /* ���������Ľ��뼼������Ϊ�㣬����� */
        if ( 0 == pstReportList->astPlmnSelectionList[i].ucRatNum )
        {
            continue;
        }

        /* ���ź������������PLMN�����ϱ���Ϣ�ṹ�� */
        for ( j = 0; j < pstReportList->astPlmnSelectionList[i].ucRatNum; j++)
        {
            if (( NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus)
                && (pstSndTafMsg->ulCnt < NAS_MSCC_PIF_MAX_PLMN_CNT))
            {
                /* �Ѵ�PLMN���뵽�ϱ��б��� */
                pstSndTafMsg->aPlmnList[pstSndTafMsg->ulCnt].ulMcc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMcc;

                pstSndTafMsg->aPlmnList[pstSndTafMsg->ulCnt].ulMnc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMnc;

                pstSndTafMsg->aucRaMode[pstSndTafMsg->ulCnt]
                                        = pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType;

                /* ��ȡ�б���ÿ��PLMN��״̬ */
                NAS_MMC_GetPlmnStatus_PlmnList((NAS_MML_PLMN_ID_STRU *)&(pstSndTafMsg->aPlmnList[pstSndTafMsg->ulCnt]),
                                               &(pstSndTafMsg->aucPlmnStatus[pstSndTafMsg->ulCnt]),
                                               pstSndTafMsg->aucRaMode[pstSndTafMsg->ulCnt]);

                pstSndTafMsg->ulCnt++;
            }
        }
    }

    /* �ڴ��ͷ� */
    PS_MEM_FREE(WUEPS_PID_MMC, pstReportList);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildTafMmcPlmnListAbortCnfMsg_PlmnList
 ��������  : ������ϢID_MMC_MSCC_PLMN_LIST_ABORT_CNF
 �������  : ��
 �������  : pstSndTafMsg
 �� �� ֵ  : VOS_TRUE ����ɹ�
             VOS_FALSE ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��6��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ:ɾ��NAS_FEATURE_BLACK_WHITE_PLMN��
  3.��    ��   : 2013��4��15��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2013��8��27��
    ��    ��   : w00242748
    �޸�����   : DTS2013071808373����澯����
*****************************************************************************/
VOS_UINT32    NAS_MMC_BuildTafMmcPlmnListAbortCnfMsg_PlmnList(
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU    *pstSndMsccMsg
)
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstReportList = VOS_NULL_PTR;
    VOS_UINT32                              i;
    VOS_UINT32                              j;

    pstReportList   = (NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                                           sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU));
    if (VOS_NULL_PTR == pstReportList)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_BuildTafMmcPlmnListAbortCnfMsg_PlmnList: ALLOC MEM FAIL!");
        return VOS_FALSE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstReportList) + VOS_MSG_HEAD_LENGTH, 0, sizeof(NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU) - VOS_MSG_HEAD_LENGTH);
    pstSndMsccMsg->MsgHeader.ulLength          = sizeof(MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU);
    pstSndMsccMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsccMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsccMsg->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstSndMsccMsg->MsgHeader.ulMsgName         = ID_MMC_MSCC_PLMN_LIST_ABORT_CNF;
    pstSndMsccMsg->ulCnt                       = 0;

    /* ���������б�������� */
    NAS_MMC_SortSearchedPlmnList_PlmnList(NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                          pstReportList);

    /* ɾ���ظ���PLMN */
    NAS_MMC_DelDuplicatedPlmnWithRatInPlmnList(pstReportList);

    /* ���ź�����б��е����������Ϣ�ṹ�� */
    for ( i = 0 ; i < pstReportList->usSearchPlmnNum; i++ )
    {
        /* �ж�PLMN�ں��������߲��ڰ����������ϱ� */
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
         if (VOS_TRUE == NAS_MML_IsPlmnIdForbiddenByWhiteBlackList(&(pstReportList->astPlmnSelectionList[i].stPlmnId)))
         {
             continue;
         }
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

        /* ���ź������������PLMN�����ϱ���Ϣ�ṹ�� */
        for ( j = 0; j < pstReportList->astPlmnSelectionList[i].ucRatNum; j++)
        {
            if (( NAS_MMC_NET_STATUS_SEARCHED_EXIST == pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus)
                && (pstSndMsccMsg->ulCnt < NAS_MSCC_PIF_MAX_PLMN_CNT))
            {
                /* �Ѵ�PLMN���뵽�ϱ��б��� */
                pstSndMsccMsg->aPlmnList[pstSndMsccMsg->ulCnt].ulMcc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMcc;

                pstSndMsccMsg->aPlmnList[pstSndMsccMsg->ulCnt].ulMnc
                                        = pstReportList->astPlmnSelectionList[i].stPlmnId.ulMnc;

                pstSndMsccMsg->aucRaMode[pstSndMsccMsg->ulCnt]
                                        = pstReportList->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType;

                /* ��ȡ�б���ÿ��PLMN��״̬ */
                NAS_MMC_GetPlmnStatus_PlmnList((NAS_MML_PLMN_ID_STRU *)&(pstSndMsccMsg->aPlmnList[pstSndMsccMsg->ulCnt]),
                                               &(pstSndMsccMsg->aucPlmnStatus[pstSndMsccMsg->ulCnt]),
                                               pstSndMsccMsg->aucRaMode[pstSndMsccMsg->ulCnt]);

                pstSndMsccMsg->ulCnt++;
            }
        }
    }

    /* �ڴ��ͷ� */
    PS_MEM_FREE(WUEPS_PID_MMC, pstReportList);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMsccPlmnListCnf_PlmnList
 ��������  : ��MSCC����LIST�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��20��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPlmnListCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_PLMN_LIST_CNF_STRU          *pstSndMsccMsg = VOS_NULL_PTR;

    pstSndMsccMsg   = (MMC_MSCC_PLMN_LIST_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                              sizeof(MMC_MSCC_PLMN_LIST_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsccMsg)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnListCnf_PlmnList: ALLOC MEM FAIL!");
        return;
    }

    /* �����ϱ���Ϣ */
    if (VOS_TRUE != NAS_MMC_BuildTafMmcPlmnListIndMsg_PlmnList(pstSndMsccMsg))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);
        return;
    }

    /* ��MSCC�����б��ѽ�� */
    NAS_MMC_SndMsccPlmnListInd(pstSndMsccMsg);

    /* OM �¼��ϱ� */
    if ( 0 == pstSndMsccMsg->ulCnt)
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList
 ��������  : ��MSCC����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��20��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU  *pstSndMsccMsg = VOS_NULL_PTR;

    /* ��ȡ�����ȼ�����ĸ��� */
    pstSndMsccMsg   = (MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                              sizeof(MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU));
    if (VOS_NULL_PTR == pstSndMsccMsg)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList: ALLOC MEM FAIL!");
        return;
    }

    /* �����ϱ���Ϣ */
    if (VOS_TRUE != NAS_MMC_BuildTafMmcPlmnListAbortCnfMsg_PlmnList(pstSndMsccMsg))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);
        return;
    }

    /* ��MSCC�����б��ѽ�� */
    NAS_MMC_SndMsccPlmnListAbortCnf(pstSndMsccMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstSndMsccMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndSpecRatPlmnListReq_PlmnList
 ��������  : ��ָ���Ľ��뼼������LIST��������
 �������  : enRat ָ���Ľ��뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : V7R1C50_GUL_BG ��Ŀ����
  3.��    ��   : 2015��10��15��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatPlmnListReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
#if (FEATURE_ON == FEATURE_CSG)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* �����CSG�б������������csg�б����������� */
    if (VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
    {
        if ((NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
         || (NAS_MML_NET_RAT_TYPE_LTE == enRatType))
        {
            NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList(enRatType);
            return;
        }

        /* gu�·�פ��̬��Ҫ����gu��lte������ */
        NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(enRatType);
        return;
    }
#endif

    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            NAS_MMC_SndLmmPlmnListReq();

            /* ĿǰL֧��פ��̬LIST����,�˴�������ʾ���µ�ǰ��פ��״̬,��
               ������Ϣ�ӿ�ID_LMM_MMC_NOT_CAMP_ON_INDָʾ */

            /* Ǩ��״̬���ȴ�LMM��LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF);

            /* ����������ʱ�� */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_LMM_PLMN_LIST_CNF_LEN);
            }

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            NAS_MMC_SndAsPlmnListReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WAS��LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF);

            /* ����������ʱ�� */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_WAS_PLMN_LIST_CNF_LEN);
            }

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            NAS_MMC_SndAsPlmnListReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS��LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF);

            /* ����������ʱ�� */
            if (NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF, TI_NAS_MMC_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_LIST_CNF, TI_NAS_MMC_NOT_CAMP_ON_WAIT_GAS_PLMN_LIST_CNF_LEN);
            }

            break;
        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatPlmnListReq_PlmnList Unexpected Rat type!");

            break;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList
 ��������  : ��ָ���Ľ��뼼������ֹͣ��������
 �������  : enRat ָ���Ľ��뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ��LMM����ֹͣ�������� */
            NAS_MMC_SndLmmPlmnSrchStopReq();

            /* Ǩ��״̬���ȴ�LMM��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ��WAS����ֹͣ�������� */
            NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WAS��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ��GAS����ֹͣ�������� */
            NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatPlmnSearchStopReq_PlmnList Unexpected Rat type!");

            break;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SndSpecRatSuspendReq_PlmnList
 ��������  : ��ָ���Ľ��뼼�����͹�������
 �������  : enRat ָ���Ľ��뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��1��28��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ:���ӻ�ȡ��ע������Ĵ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatSuspendReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ����פ��״̬ */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
            /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

            /* ��LMM���͹������� */
            NAS_MMC_SndLmmSuspendReq();

            /* Ǩ��״̬���ȴ�LMM�Ĺ���ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_LMM_SUSPEND_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ����פ��״̬ */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
            /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

            /* ��WAS���͹������� */
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WAS�Ĺ���ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SUSPEND_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ����פ��״̬ */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);
            /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

            /* ��GAS���͹������� */
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS�Ĺ���ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SUSPEND_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatSuspendReq_PlmnList Unexpected Rat type!");

            break;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcRrmmSearchCnf_PlmnList
 ��������  : ����PLMN LIST�Ľ��
 �������  : pstPlmnSrchCnf PLMN LIST�Ľ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��5��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 GUL���������޸�
  3.��    ��   : 2012��10��17��
    ��    ��   : z00161729
    �޸�����    : DTS2012052107863:W����psҵ����Է���list�ѣ�g��l��֧��
  4.��    ��   : 2014��2��7��
    ��    ��   : w00167002
    �޸�����   : SVLTE��������Ŀ:פ���ɹ����LIST����,����פ���ɹ��󣬵�ǰҪô�ǹ��ڣ�
                 Ҫô�ǹ��⡣������LTģʽ��TD�²�����NO RF��������GUL����ģʽ��������NO RF��
                 ��ǰ��������Ŀ�����ǵĳ���Ϊ:��˫��ģʽ��W�º�G���ڹ����ߡ�
  5.��    ��   : 2013��3��29��
    ��    ��   : y00176023
    �޸�����   : DSDS GUNAS II��Ŀ:NO RF�������RRM����ע�ᣬֻ����GU������LTE����������NO RF
  6.��    ��   : 2014��5��15��
    ��    ��   : w00167002
    �޸�����   : DTS2014051501018:DSDS��MODEM����绰����MODEM����ʧ������AVAILABLE
                 ��ʱ�����û������б��ѣ����б��ѹ����У�����������ʱ����ʱ���б���
                 ������MMCû����������������ʱ����
                 �޸�Ϊ:���б���NO RF�󣬶�����AVAILABLE��ʱ������AVAILABLE��ʱ��
                 ��ʱ�����������ǰ����#12����������ǰACCESS BAR��������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmSearchCnf_PlmnList(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
)
{
    /* �ж�LIST������� */
    switch (pstPlmnSrchCnf->ulSearchRlt)
    {
        case RRC_PLMN_SEARCH_RLT_LIST_REJ:

            /* ����5S�����Գ��Զ�ʱ�� */
            if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                 /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                    ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
                if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
                {
                    /* ����LIST REJ��MSCC */
                    NAS_Mmc_SndMsccPlmnListRej();
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
                }
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
            }

            /* ����״̬��ʧ�ܵ��˳���� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            break;

       case RRC_PLMN_SEARCH_RLT_LIST:

            /* ����PLMN LIST�����ɹ��Ľ�� */
            NAS_MMC_ProcPlmnListSucc_PlmnList(pstPlmnSrchCnf);

            break;

       case RRC_PLMN_SEARCH_RLT_LIST_FAIL:
            if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* ����LIST REJ��MSCC */
                NAS_Mmc_SndMsccPlmnListRej();
            }

            /* ����״̬��ʧ�ܵ��˳���� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();
            break;

       case RRC_PLMN_SEARCH_RLT_LIST_NO_RF:

            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_GetCurrNetRatType());

            break;

       default:

            /*�쳣��ӡ*/
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmSearchCnf_PlmnList Unexpected List Result!");

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcPlmnListSucc_PlmnList
 ��������  : ����PLMN LIST�ĳɹ��Ľ��
 �������  : pstPlmnSrchCnf PLMN LIST�Ľ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��26��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����

*****************************************************************************/
VOS_VOID NAS_MMC_ProcPlmnListSucc_PlmnList(
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    VOS_UINT32                          ulIndex;

    /* LIST����������,��Ҫ���ݵ�ǰ�����Я�����Ѿ�����
       ���Ľ��뼼����Ϣ����RAT��������� */
    for ( ulIndex = 0; ulIndex < NAS_RRC_MAX_RAT_NUM; ulIndex++)
    {
        if ( RRC_NAS_RAT_LIST_SEARCH_CMPL == pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            /*��RRC�Ľ��뼼��ת����MML����ĸ�ʽ��Ȼ����� */
            NAS_MMC_ConvertRrcRatToNasFormat(pstPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat, &enRat);
            NAS_MMC_SetSearchedFlag_PlmnList(enRat);
        }
    }

    /* ���������б� */
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(&(pstPlmnSrchCnf->PlmnIdList));

    /* LIST����������,RRC���ܳ�������,��ʱ��Ҫ��������״̬,�����˳�LIST�������ָ��
       ���� */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }

    /* ��ȡ������һ��δ�����Ľ���ģʽ */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
       /* ������û�LIST����,��MSCC�ϱ���� */
       if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
       {
           /* �����������������������ϱ���MSCC */
           NAS_MMC_SndMsccPlmnListCnf_PlmnList();
       }

       /* ����״̬���ɹ��˳��Ľ�� */
       NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                               (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                               NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                               NAS_MMC_GetRegRsltInfo_PlmnList());

       /* �˳�״̬�� */
       NAS_MMC_FSM_QuitFsmL2();

       return;
    }

    /* ��ǰ���뼼�����͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_GetCurrNetRatType());

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcRrmmSuspendCnf_PlmnList
 ��������  : ��������Ĺ���ظ��Ľ��
 �������  : pstRrmmSuspendCnf �����Ĺ���ظ��Ľ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011120702166:MMC��λ���޸�λ��Ϣ,��MMLģ���װ��λ��Ϣ��
                  �Թ�MM����ã�������λ��
  3.��    ��   : 2012��10��7��
    ��    ��   : s46746
    �޸�����   : for V7R1C50_At_Abort����פ���б����������У������û��б�������֮�����û��б�������
                 ����û���ٴγ�������
  4.��    ��   : 2014��2��18��
    ��    ��  :  w00242748
    �޸�����  :  DTS2014021803515:��λʱ��ȷ���յ��ĸ����뼼�����쳣��Ϣ���µġ�

  5.��    ��   : 2015��3��11��
    ��    ��   : wx270776
    �޸�����   : DTS2015011212939:���Ӹ�λ����
*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmSuspendCnf_PlmnList(
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT32                          ulNeedPlmnSearch;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    if ( MMC_AS_SUSPEND_FAILURE  == pstRrmmSuspendCnf->ucResult )
    {
        /* ���帴λ */

        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return;
    }

    /* �ж�״̬���˳�����Ƿ�Ϊ�棬���Ϊ��*/
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        ulNeedPlmnSearch = VOS_FALSE;

        /* ��ǰ�û��б����� */
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
            {
                /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

                ulNeedPlmnSearch = VOS_TRUE;
            }
            else
            {
                /* ��MSCC�ظ�LIST������� */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* ����״̬��ABORT���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ�����뼼�� */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmSuspendCnf_PlmnList: Get next search rat fail.");

        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* ��ǰΪ�û�LIST���� */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_CNF */
            NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        }

        /* ����״̬���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
    NAS_MML_SetCurrNetRatType(enRat);

    /* ���¸�����ģʽ����LIST��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(enRat);

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcRrcConnRelInd_PlmnList
 ��������  : ����RRC�����ͷ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��5��
    ��    ��   : w00176964
    �޸�����   : GUL BG��Ŀ����:��PSҵ�����,��������5S��ʱ������
  3.��    ��   : 2014��1��28��
    ��    ��   : w00242748
    �޸�����   : DTS2014012605086:MMC��ON PLMN״̬��ʱ�յ��б������󣬵�ǰCS����
                 ���Ӳ�����ʱ���������㷢���б��������������㴦���ˣ�
                 ��ֱ���ɽ���㴦��ظ���
  4.��    ��   : 2015��9��26��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrcConnRelInd_PlmnList(VOS_VOID)
{
    VOS_UINT32                          ulCsServiceStatusFlg;

    ulCsServiceStatusFlg = NAS_MML_GetCsServiceExistFlg();

    /* һ������·�ͷź󣬵ȴ�����һ������ͷ�ָʾʱ���п����ͷŵ����Ϸ���ҵ��
       �˴���Ҫ�ж��Ƿ���ҵ����� */
    if ( VOS_TRUE == ulCsServiceStatusFlg )
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();

        /* ��ҵ��ʱ��δ����LIST�������ѵ��������б�Ϊ��,����״̬��ʧ�ܵ��˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }
    else if ( VOS_TRUE == NAS_MML_IsRrcConnExist() )
    {
        /* ��������������ӣ�������ȴ����ȴ���ʱ֮���ټ������Է����б��� */
    }
    else
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

        switch (NAS_MML_GetCurrNetRatType())
        {
            case NAS_MML_NET_RAT_TYPE_WCDMA:

                /* Ǩ��״̬���ȴ�was�����ϵͳ��Ϣ */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SYS_INFO_IND);

                /* ����������ʱ�� */
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);

                break;
            case NAS_MML_NET_RAT_TYPE_GSM:

                /* Ǩ��״̬���ȴ�Gas�����ϵͳ��Ϣ */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SYS_INFO_IND);

                /* ����������ʱ�� */
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

                break;

            default:

            /*�쳣��ӡ*/
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrcConnel_PlmnList Unexpected Rat Type!");
            break;
        }
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList
 ��������  : �������������ֹͣ�ظ��Ľ��
 �������  : enRatType ��ǰ���뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��2��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  3.��    ��   : 2012��10��7��
    ��    ��   : s46746
    �޸�����   : for V7R1C50_At_Abort����פ���б����������У������û��б�������֮�����û��б�������
                 ����û���ٴγ�������
  4.��    ��   : 2015��11��04��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmPlmnSearchStopCnf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;

    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        /* ��ǰ�û��б����� */
        if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
            {
                /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();

                ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
            }
            else
            {
                /* ��MSCC�ظ�LIST������� */
                NAS_MMC_SndMsccPlmnListCnf_PlmnList();
            }
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ��δ�����Ľ���ģʽ */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* �û�LIST���� */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            /* �����������������������ϱ���MSCC */
            NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        }

        /* ����״̬��ʧ���˳��Ľ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ǰ���뼼�����͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(enRatType);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList
 ��������  : ����LMM������ֹͣ�ظ��Ľ��
 �������  : enRatType ��ǰ���뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��06��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��2��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  3.��    ��   : 2012��10��7��
    ��    ��   : s46746
    �޸�����   : for V7R1C50_At_Abort����פ���б����������У������û��б�������֮�����û��б�������
                 ����û���ٴγ�������
  4.��    ��   : 2015��11��4��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmPlmnSearchStopCnf_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;

    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        /* ֪ͨMSCC�ظ����Ϊ�� */
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            if (VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
            {
                /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
                NAS_MMC_SndMsccPlmnListAbortCnf_PlmnList();
            }

            ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
        }
        else
        {
            /* ��MSCC�ظ�LIST������� */
            NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ��δ�����Ľ���ģʽ */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* ��MSCC�ظ�LIST������� */
        NAS_MMC_SndMsccListSearchCnfMsg_PlmnList();

        /* ����״̬���ɹ��˳��Ľ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                 (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                 NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                 NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ǰ���뼼�����͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLteSysInfo_PlmnList
 ��������  : ����LTE��ϵͳ��Ϣ
 �������  : pstLSysInfoInd - LTE��ϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��10��24��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_VOID NAS_MMC_ProcLteSysInfo_PlmnList(
    struct MsgCB                       *pstLSysInfoInd
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8               enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstLSysInfoInd);

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*�����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC*/
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();
    }


    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* ת��GMMϵͳ��Ϣ,��rabmʹ�� */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstLSysInfoInd);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstLSysInfoInd);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstLSysInfoInd);

    return;
}


#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedWaitRrcRel_PlmnList
 ��������  : �жϵ�ǰ�Ƿ�ȴ�RRC�����ͷ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : ��Ҫ�ȴ�RRC�����ͷ�
             VOS_FALSE : ����Ҫ�ȴ�RRC�����ͷ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��6��5��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��12��11��
   ��    ��   : z00161729
   �޸�����   : DTS2013121102199:g��lau�����У�sm����pdp���������gmm��
                gmm��������ps����ҵ����ڱ�ʶΪtrue���û�����list����δ�������ͷ�ֱ�ӷ�����list��
 3.��    ��   : 2014��1��28��
   ��    ��   : w00242748
   �޸�����   : DTS2014012605086:MMC��ON PLMN״̬��ʱ�յ��б������󣬵�ǰCS����
                ���Ӳ�����ʱ���������㷢���б��������������㴦���ˣ�
                ��ֱ���ɽ���㴦��ظ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedWaitRrcRel_PlmnList( VOS_VOID )
{
    VOS_UINT8                           ucCsSigConnStatusFlg;

    ucCsSigConnStatusFlg = NAS_MML_GetCsSigConnStatusFlg();

    /* ��ǰRRC���Ӳ����ڿ���ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MML_IsRrcConnExist())
    {
        return VOS_FALSE;
    }

    /* ��ǰ����PSҵ��򻺴��psҵ�񵫲�����cs��������������RRC */
    if (VOS_FALSE == ucCsSigConnStatusFlg)
    {
        return VOS_FALSE;
    }

    /* ���������Ϊ������������,�����ȴ�RRC�ͷ��������� */
    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcUserPlmnListReq_PlmnList
 ��������  : �����û�LIST��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��25��
    ��    ��   : w00176964
    �޸�����   : V7R1_GUL_BG ��Ŀ����
  3.��    ��   : 2012��6��5��
    ��    ��   : w00176964
    �޸�����   : V7R1_GUL_BG ��Ŀ����:PSҵ�����ֱ�ӷ���RRC����LIST����
  4.��    ��   : 2012��9��11��
    ��    ��   : w00176964
    �޸�����   : V7R1_GUTL��Ŀ����:TD��ģ��פ��̬����Ҫ֪ͨMM/GMM��������״̬
  5.��    ��   : 2012��10��7��
    ��    ��   : s46746
    �޸�����   : for V7R1C50_At_Abort����פ���б����������У������û��б�������֮�����û��б�������
                 ����û���ٴγ�������
  6.��    ��   : 2012��11��10��
    ��    ��   : t00212959
    �޸�����   : DTS2012111002172 P̬�б���
  7.��    ��   : 2014��05��6��
    ��    ��   : w00176964
    �޸�����   : V3R3C60_eCall��Ŀ����ע�����״̬�ϱ�
  8.��    ��   : 2014��5��12��
    ��    ��   : w00242748
    �޸�����   : DTS2014050807056:TD���б���֮��PDPȥ����ˡ�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcUserPlmnListReq_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    enRatType     = NAS_MML_GetCurrNetRatType();
    pstConnStatus = NAS_MML_GetConnStatus();

    /* ����״̬�±���ϣ���ǰ���뼼��ΪBUTT */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == NAS_MML_GetCurrNetRatType())
    {
       NAS_MMC_GetOrigenSearchRat_PlmnList(&enRatType);

       NAS_MML_SetCurrNetRatType(enRatType);
    }

    /* �ж��Ƿ���Ҫ�ȴ������ͷ� */
    if ( VOS_FALSE == NAS_MMC_IsNeedWaitRrcRel_PlmnList() )
    {
       /* ���ݲ�ͬ����ģʽ,����LIST��������Ǩ���ȴ��������״̬������������ʱ��*/
       NAS_MMC_SndSpecRatPlmnListReq_PlmnList(NAS_MML_GetCurrNetRatType());

       /* ��פ��̬֪ͨMM/GMM������ʼ */
       if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
       {
            /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-6, begin */
            NAS_MMC_UpdateServiceStateSpecPlmnSearch();
            NAS_MMC_UpdateRegStateSpecPlmnSearch();
            /* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-6, end */

            if ((NAS_MML_NET_RAT_TYPE_WCDMA != enRatType)
             || (VOS_FALSE == pstConnStatus->ucRrcStatusFlg))
            {
                /* ��GMM��������ָʾ */
                NAS_MMC_SndGmmPlmnSchInit();

                /* ��MM��������ָʾ */
                NAS_MMC_SndMmPlmnSchInit();

                /* ���ý�������״̬ */
                NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

                return;
            }
       }

       /* פ��̬��GTLģʽTDΪ��ģʱ��Ҫ֪ͨMM/GMM��������״̬ */
       if ( (VOS_TRUE == NAS_MMC_IsCurrentTdscdmaMode())
         && (VOS_FALSE == pstConnStatus->ucRrcStatusFlg) )
       {
            /* ��GMM��������ָʾ */
            NAS_MMC_SndGmmPlmnSchInit();

            /* ��MM��������ָʾ */
            NAS_MMC_SndMmPlmnSchInit();

            /* ��ģ����������GUNAS���� */
            if (VOS_FALSE == NAS_MML_IsWcdmaOnlyMode(NAS_MML_GetMsPrioRatList()))
            {
                /* ���ý�������״̬ */
                NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
            }
       }

       return;
    }

    /* ��Ҫ�ȴ������ͷ� */
    switch (NAS_MML_GetCurrNetRatType())
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

        /* L����EPS�������ӱ����ȴ�LMM�ͷ���·,
           ������GU��ʵ��һ�� */

        /* Ǩ��״̬���ȴ�LMM��EPS��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        break;
#endif

    case NAS_MML_NET_RAT_TYPE_WCDMA:
    case NAS_MML_NET_RAT_TYPE_GSM:

        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        break;

    default:
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcUserPlmnListReq_PlmnList Unexpected Rat type!");

        break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcGasSysInfo_PlmnList
 ��������  : ����GAS��ϵͳ��Ϣ
 �������  : pstGSysInfoInd GAS��ϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��16��
    ��    ��   : l00171473
    �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
  3.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������,��ֹLTE����
  4.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMSCC
  5.��    ��   : 2014��1��23��
   ��    ��   : z00161729
   �޸�����   : DTS2014012305088:svlte����tds��l��ϵͳ��Ϣ��pstransfer:1��ע���������ʧ�ܣ�psǨ��
                ��modem1��tds��l�ٴ�פ��mmc�յ�ϵͳ��Ϣ�ж�פ����Ϣδ�ı䲻���mma����ϵͳ��Ϣ����
                mtc�޷��ϱ�pstransfer:1,��Ҫ������״̬���˳����mma�ٷ���ϵͳ��Ϣ

  6.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������

*****************************************************************************/
VOS_VOID NAS_MMC_ProcGasSysInfo_PlmnList(
    struct MsgCB                       *pstGSysInfoInd
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

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
    /* Added by t00212959 for DCM�����������������, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-15, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM�����������������, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstGSysInfoInd, enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-15, end */

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
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstGSysInfoInd);

    /* פ��С���仯����������ʱ���ϱ�ϵͳ��Ϣ */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMSCCģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
    NAS_MMC_SndMmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstGSysInfoInd);
    NAS_MMC_SndGmmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstGSysInfoInd);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstGSysInfoInd);
#endif

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcWasSysInfo_PlmnList
 ��������  : ����WAS��ϵͳ��Ϣ
 �������  : pstWSysInfoInd WAS��ϵͳ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��16��
    ��    ��   : l00171473
    �޸�����   : DTS2012061409086, �յ�W��G��ϵͳ��Ϣʱ֪ͨLģ
  3.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������,��ֹLTE����
  4.��    ��   : 2012��12��11��
    ��    ��   : w00176964
    �޸�����   : �յ�ϵͳ��Ϣ�����ֹ��Ϣ�仯��֪ͨMSCC

  5.��    ��   : 2014��1��18��
    ��    ��   : z00234330
    �޸�����   : dts2014011801513,������ϱ���ϵͳ��Ϣ�����п���û��Я��plmnid,
                 �˴��жϲ�û���ж�plmnid�Ƿ���Ч
  6.��    ��   : 2014��1��23��
    ��    ��   : z00161729
    �޸�����    : DTS2014012305088:svlte����tds��l��ϵͳ��Ϣ��pstransfer:1��ע���������ʧ�ܣ�psǨ��
                ��modem1��tds��l�ٴ�פ��mmc�յ�ϵͳ��Ϣ�ж�פ����Ϣδ�ı䲻���mma����ϵͳ��Ϣ����
                mtc�޷��ϱ�pstransfer:1,��Ҫ������״̬���˳����mma�ٷ���ϵͳ��Ϣ

  7.��    ��   : 2014��5��4��
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcWasSysInfo_PlmnList(
    struct MsgCB                       *pstWSysInfoInd
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

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    /* Added by t00212959 for DCM�����������������, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-15, end */

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* Added by t00212959 for DCM�����������������, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstWSysInfoInd,enLCapabilityStatus);
#endif
    /* Added by t00212959 for DCM�����������������, 2012-8-15, end */

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
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstWSysInfoInd);

    /* פ��С���仯����������ʱ���ϱ�ϵͳ��Ϣ */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMSCCģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }
    /* Added by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, begin */
    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-11-18, end */

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
    NAS_MMC_SndMmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstWSysInfoInd);
    NAS_MMC_SndGmmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstWSysInfoInd);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstWSysInfoInd);
#endif

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmSearchCnf_PlmnList
 ��������  : ����LMM�µ�PLMN LIST�Ľ��
 �������  : pstLmmPlmnSrchCnf PLMN LIST�Ľ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��27��
    ��    ��   : t00212959
    �޸�����   : GUL BG��Ŀ����
  3.��    ��   : 2012��6��10��
    ��    ��   : z00161729
    �޸�����   : GUL BG��Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmSearchCnf_PlmnList(
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmPlmnSrchCnf
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList;
    VOS_UINT32                          ulIndex;

    /* �ж�LIST������� */

    if ( (MMC_LMM_PLMN_SRCH_RLT_LIST_SUCC   != pstLmmPlmnSrchCnf->enRlst)
      && (MMC_LMM_PLMN_SRCH_RLT_LIST_REJ    != pstLmmPlmnSrchCnf->enRlst)
      && (MMC_LMM_PLMN_SRCH_RLT_LIST_NO_RF  != pstLmmPlmnSrchCnf->enRlst) )
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmSearchCnf_PlmnList: Unexpected List Search Result!");

        return;
    }

    /* ֹͣ�ȴ�LMM�����ظ��ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_LIST_CNF);


    if (MMC_LMM_PLMN_SRCH_RLT_LIST_NO_RF == pstLmmPlmnSrchCnf->enRlst)
    {
        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        return;
    }



    if (MMC_LMM_PLMN_SRCH_RLT_LIST_REJ == pstLmmPlmnSrchCnf->enRlst)
    {
        /* ����5S�����Գ��Զ�ʱ��*/
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն���
                L���޷�֪����csҵ���Ƕ��ţ�ֻ�ܸ����Ƿ�ucEpsServiceConnStatusFlg���ж� */

            /* L����������̬���Ի����б�������������CSҵ��ʱ��Ҫ�����ظ��б�����ʧ�� */
            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
            {
                /* ����LIST REJ��MSCC */
                NAS_Mmc_SndMsccPlmnListRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
            }

         }
        else
        {
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST, TI_NAS_MMC_PERIOD_TRYING_INTER_PLMN_LIST_LEN);
        }

        /* ����״̬��ʧ���˳��Ľ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ���µ�RAT������� */
    for ( ulIndex = 0; ulIndex < MMC_LMM_MAX_RAT_NUM; ulIndex++)
    {
        if ( MMC_LMM_RAT_LIST_SEARCH_CMPL == pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enListSearchRlt)
        {
            NAS_MMC_SetSearchedFlag_PlmnList((MMC_LMM_RAT_TYPE_ENUM_UINT8)(pstLmmPlmnSrchCnf->astSearchRatInfo[ulIndex].enRat));
        }

    }

    pstGuPlmnIdList   = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                   sizeof(RRC_PLMN_ID_LIST_STRU));

    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmSearchCnf_PlmnList:ERROR: Memory Alloc Error");
        return;
    }

    /*ת��L��ʽ�������б��ΪGU��ʽ��*/
    NAS_MMC_ConvertLmmPlmnIdListToGUFormat(&(pstLmmPlmnSrchCnf->stPlmnIdList), pstGuPlmnIdList);

    /*���������б�*/
    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(pstGuPlmnIdList);
    PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

    if (VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* �ڲ��б��Ѳ��ϱ� */
        if ( VOS_TRUE == NAS_MMC_IsUserPlmnList_PlmnList())
        {
            /* �����������������������ϱ���MSCC */
            NAS_MMC_SndMsccPlmnListCnf_PlmnList();
        }

        /* ����״̬���ɹ��˳��Ľ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��LMM���͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnList
 ��������  : Lmm TAU����Ĵ�����
 �������  : pstLmmTauIndMsg L��TAU��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  3.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����
                  ����������NAS_MMC_ProcEpsRegFail����ΪNAS_MMC_ProcEpsTauRegFail
                  ����TAU��ע��ԭ��ֵ����д���
  4.��    ��   : 2011��12��20��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV ����:UT�޸ģNNAS_MMC_SetUserSpecPlmnRegisterStatus
                 ֻ������״̬����ON PLMN�½�������
  5.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  6.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
                  additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  7.��    ��   : 2012��06��01��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  8.��    ��   : 2012��6��8��
    ��    ��   : l00130025
    �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨAPS/CDS��Ϣ���޷�����
  9.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
  10.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�DTS2012090401249
  11.��    ��   : 2012��09��12��
     ��    ��   : z00161729
     �޸�����  : DTS2012082904888��cs ps mode1��on plmn��plmn list��bg plmn search״̬����eps onlyע��ɹ�δ����NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc�ж��Ƿ���Ҫdisable lte
  12.��    ��   : 2012��12��6��
     ��    ��   : s00217060
     �޸�����   : DTS2012120410842:ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ
  13.��    ��   : 2013��05��08��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  14.��    ��   : 2013��12��10��
      ��    ��  : w00176964
      �޸�����  : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
  15.��    ��   : 2014��5��6��
     ��    ��   : z00161729
     �޸�����   : DTS2014050602850:l������ע��eps�ɹ���csע�ᱻ#18�ܾ���disable lte��gu������ע��ɹ�����ָ����l csע�ᱻ#18�ܾ������磬l����eps����ע��ɹ���mmcû��disable lte
  16.��    ��   : 2014��5��5��
     ��    ��   : w00242748
     �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                  ע��״̬���ϱ���
  17.��    ��   : 2014��5��14��
     ��    ��   : w00242748
     �޸�����   : DTS2014051206381:ö��ֵʹ�ò���
  18.��    ��   : 2015��4��18��
     ��    ��   : z00161729
     �޸�����   : 24301 R11 CR������Ŀ�޸�
  19.��    ��   : 2015��02��11��
     ��    ��   : l00305157
     �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע����(EPS ONLY)�ɹ����ϱ�ע��״̬
  20.��    ��   : 2015��06��09��
     ��    ��   : l00305157
     �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע�������ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�
 21.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnList(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */
    VOS_UINT8                                               ucSimCsRegStatus;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsRegAdditionalAction;
    
    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverTauResultToMMLCause(pstLmmTauIndMsg,&enRegRsltCause);

    if (MMC_LMM_TAU_RSLT_SUCCESS == pstLmmTauIndMsg->ulTauRst)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_TAU_RESULT_IND, pstLmmTauIndMsg);


        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */
        /* ����EPLMN */
        if (VOS_TRUE == pstLmmTauIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmTauIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmTauIndMsg->stEplmnList.astEplmnList;

            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, stLEplmnInfo.astEquPlmnAddr);

            /* ��EPLMN��Ϣ�������ڴ��� */
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, (stLEplmnInfo.astEquPlmnAddr));

            NAS_MMC_WriteEplmnNvim();
        }

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);
        
        /* EPS����ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ */
        NAS_MMC_DelForbInfo_LmmAttRsltSucc(VOS_NULL_PTR, VOS_FALSE);

        /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        /* �˴�����CS additionԭ��������TAU��EPS�ɹ�ʱ,LMM����T3411�ٴγ���TAU������,
           �û�Detach CS,LMM��ֱ�ӱ�TAU�ɹ�,���ٳ�������TAU */
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON);

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


        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());

        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
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

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }
    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmTauResultInd_PlmnList
 ��������  : Lmm TAU����Ĵ�����
 �������  : pstLmmTauIndMsg L��TAU��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��28��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸�������tau����
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmTauResultInd_PlmnList(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
)
{
    switch (pstLmmTauIndMsg->ulReqType)
    {
        case MMC_LMM_COMBINED_TA_LA_UPDATING:
        case MMC_LMM_COMBINED_TA_LA_WITH_IMSI:
        case MMC_LMM_CS_PS_PERIODIC_UPDATING:

            /* ����lmm������tau��� */
            NAS_MMC_ProcLmmCombinedTauResultInd_PlmnList(pstLmmTauIndMsg);
            break;

        case MMC_LMM_TA_UPDATING:
        case MMC_LMM_PS_PERIODIC_UPDATING:

            /* ����lmm�ķ�����tau��EPS onlyע��Ľ�� */
            NAS_MMC_ProcLmmEpsOnlyTauResultInd_PlmnList(pstLmmTauIndMsg);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmTauResultInd_PlmnList:Unexpected tau req type!");
            break;

    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedAttachInd_PlmnList
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
  3.��    ��   : 2011��12��5��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸ĺϲ�ԭNAS_MMC_HPLMN_REG_REJ_STRU��NAS_MMC_PLMN_REG_INFO_STRU
  4.��    ��   : 2011��12��13��
    ��    ��   : z00161729
    �޸�����   : DTS2011121302231:attach����#9/#10��Э��Ӧ�ð�other cause����
  5.��    ��   : 2011��12��20��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV ����:UT�޸ģNNAS_MMC_SetUserSpecPlmnRegisterStatus
                 ֻ������״̬����ON PLMN�½�������
  6.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
                  additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                  �򲻸��µ�ǰ��additional action
  7.��    ��   : 2012��06��01��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  8.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
  9.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�DTS2012090401249
 10.��    ��   : 2014��5��5��
    ��    ��   : w00242748
    �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                 ע��״̬���ϱ���
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedAttachInd_PlmnList(
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
            NAS_MMC_ProcLmmCombinedAttachInd_AttRsltSucc(pstLmmAttachIndMsg,
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
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCombinedAttachInd_PlmnList:Unexpected attach result!");
            enPsAdditionalAction = NAS_MMC_GetPsRegAdditionalAction_PlmnList();
            enCsAdditionalAction = NAS_MMC_GetCsRegAdditionalAction_PlmnList();
            break;

    }

    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enPsAdditionalAction);
    }

    /* AdditionalAction��Ч������CS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo       = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }


    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCombinedTauResultInd_PlmnList
 ��������  : Lmm ������TAU����Ĵ�����
 �������  : pstLmmTauIndMsg L��TAU��Ϣ
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
  6.��    ��   : 2012��06��01��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  7.��    ��   : 2012��6��4��
    ��    ��   : z00161729
    �޸�����   : V7R1C50 GUL BG������Ȧ���Ӷ�
  8.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
  9.��    ��   : 2012��8��21��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�DTS2012090401249
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmCombinedTauResultInd_PlmnList(
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg
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

    NAS_MMC_ConverLmmCombinedTauRsltToMMLCause(pstLmmTauIndMsg, &enPsRegRsltCause, &enCsRegRsltCause);

    NAS_MMC_ProcLmmCombinedTauResult(pstLmmTauIndMsg, enCsRegRsltCause,
                                    &enPsAdditionalAction, &enCsAdditionalAction);


    /* AdditionalAction��Ч������EPS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enPsAdditionalAction )
    {
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enPsAdditionalAction);
    }

    /* AdditionalAction��Ч������CS����һ���Ķ������� */
    if ( NAS_MMC_ADDITIONAL_ACTION_BUTT != enCsAdditionalAction )
    {
        NAS_MMC_SetCsRegAdditionalAction_PlmnList(enCsAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }


    NAS_MMC_UpdateUserSpecPlmnRegisterStatus(enPsRegRsltCause);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmEpsOnlyAttachResultInd_PlmnList
 ��������  : Lmm TAU����Ĵ�����
 �������  : pstLmmTauIndMsg L��attach��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��14��
    ��    ��   : w00176964
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  3.��    ��   : 2011��12��15��
    ��    ��   : w00167002
    �޸�����   : DTS2011121307570: MMCû��ά��LMM��EPLMN��Ϣ������ͳһ����
                  ATTACH/TAU/DETACH/SERVICE�б���ʱEPLMN��ά����
                  ����������NAS_MMC_ProcEpsRegFail����ΪNAS_MMC_ProcEpsAttachRegFail
                  ����ATTACH��ע��ԭ��ֵ����д���
  4.��    ��   : 2011��12��20��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseIV ����:UT�޸ģNNAS_MMC_SetUserSpecPlmnRegisterStatus
                 ֻ������״̬����ON PLMN�½�������
  5.��    ��   : 2012��1��8��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV����:EPS����ע������̵���
  6.��    ��   : 2012��2��4��
    ��    ��   : w00167002
    �޸�����   : DTS2011122704039:��ע���������Լ�ע����Ϣ���ݸ�����ע����
                  ��������չע���������Ĵ���������
                  additional actionֵ��Ϊ��ЧֵNAS_MMC_ADDITIONAL_ACTION_BUTT
                 �򲻸��µ�ǰ��additional action
  7.��    ��   : 2012��06��01��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 C50 CS/PS mode 1
  8.��    ��   : 2012��6��4��
    ��    ��   : l00171473
    �޸�����   : DTS2012053003921, �û��ֶ�ָ�������ע��״̬��־����
  9.��    ��   : 2012��6��8��
    ��    ��   : l00130025
    �޸�����   : DTS2012060702423:Anycellפ����ע��ɹ�ʱ��û��֪֪ͨͨAPS/CDS��Ϣ���޷�����
 10.��    ��   : 2012��08��20��
    ��    ��   : l65478
    �޸�����   : DTS2012081703289���ֶ�����ʧ�ܺ�ػ������¿���ע��ɹ�
                   �����������פ��EPLMN��
  11.��    ��   : 2012��8��21��
     ��    ��   : z00161729
     �޸�����   : DCM������������������޸�DTS2012090401249

  12.��    ��   : 2012��09��12��
     ��    ��   : z00161729
     �޸�����   : DTS2012082904888��cs ps mode1��on plmn��plmn list��bg plmn search״̬����eps onlyע��ɹ�δ����NAS_MMC_IsNeedDisableL_EpsOnlyRegSucc�ж��Ƿ���Ҫdisable lte
  13.��    ��   : 2012��12��6��
     ��    ��   : s00217060
     �޸�����   : DTS2012120410842:ע��ɹ�ʱ����Ҫɾ��ForbPlmn,ForbGprs����Ϣ
  14.��    ��   : 2013��05��08��
     ��    ��   : s46746
     �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬
  15.��    ��   : 2013��12��10��
     ��    ��   : w00176964
     �޸�����   : VoLTE_PhaseIII ��Ŀ:�޸�Disable Lģ���߼�
  16.��    ��   : 2014��5��6��
     ��    ��   : z00161729
     �޸�����   : DTS2014050602850:l������ע��eps�ɹ���csע�ᱻ#18�ܾ���disable lte��gu������ע��ɹ�����ָ����l csע�ᱻ#18�ܾ������磬l����eps����ע��ɹ���mmcû��disable lte
  17.��    ��   : 2014��5��5��
     ��    ��   : w00242748
     �޸�����   : DTS2014043000311:ע��״̬����״̬��һ�£���MMC�б�����״̬�ĳ���������
                  ע��״̬���ϱ���
  18.��    ��   : 2015��4��18��
     ��    ��   : z00161729
     �޸�����   : 24301 R11 CR������Ŀ�޸�
  19.��    ��   : 2015��02��11��
     ��    ��   : l00305157
     �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע����ATTACH (EPS ONLY)�ɹ����ϱ�ע��״̬
  20.��    ��   : 2015��06��09��
     ��    ��   : l00305157
     �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
                    MMC���յ�LMMģ��ע�������ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�
 21.��    ��   : 2015��10��14��
    ��    ��   : c00318887
    �޸�����   : DTS2015082002854: ���α�ǲ�׼
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmEpsOnlyAttachResultInd_PlmnList(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    VOS_UINT32                                              ulEquPlmnNum;
    MMC_LMM_PLMN_ID_STRU                                   *pstLmmEquPlmnList = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stLEplmnInfo;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegRsltCause;
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enAdditionalAction;

    /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;
    /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

    VOS_UINT8                                               ucSimCsRegStatus;

    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    NAS_MMC_ConverLmmAttachRsltToMMLCause(pstLmmAttachIndMsg, &enRegRsltCause);

    if (MMC_LMM_ATT_RSLT_SUCCESS == pstLmmAttachIndMsg->ulAttachRslt)
    {
        enAdditionalAction = NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON;

        NAS_MMC_SaveRegRsltCtx(LMM_MMC_ATTACH_IND, pstLmmAttachIndMsg);

        /*ע��: ��Ҫ�ȸ���EPLMN LIST���ڴ���ע��״̬���ϱ�,��ΪNAS_MMC_UpdatePsRegStatePsRegSucc()�����л����EPLMN LIST�ϱ�ע��״̬ */
        /* ����EPLMN */
        if ( VOS_TRUE == pstLmmAttachIndMsg->bitOpEplmn)
        {
            ulEquPlmnNum        = pstLmmAttachIndMsg->stEplmnList.ulPlmnNum;
            pstLmmEquPlmnList   = pstLmmAttachIndMsg->stEplmnList.astEplmnList;

            /* LMM PLMN ID��ʽת��ΪMMC��PLMN ID�ĸ�ʽ  */
            NAS_MMC_ConvertLmmPlmnToGUNasPlmn(ulEquPlmnNum, pstLmmEquPlmnList, (stLEplmnInfo.astEquPlmnAddr));

            /* ��EPLMN��Ϣ�������ڴ��� */
            NAS_MML_SaveEquPlmnList(ulEquPlmnNum, (stLEplmnInfo.astEquPlmnAddr));

            NAS_MMC_WriteEplmnNvim();
        }

        NAS_MMC_UpdateServiceState_RegSucc(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NORMAL_SERVICE);

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


        NAS_MMC_UpdateGURegRlstRPlmnIdInNV();


        NAS_MMC_NotifyModeChange(NAS_MML_GetCurrNetRatType(),
                                 NAS_MML_GetSimPsRegStatus());



        NAS_MMC_SetUserSpecPlmnRegisterStatus(VOS_TRUE);

        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, begin */
        NAS_MMC_SndMsccRegResultInd(NAS_MSCC_PIF_SRVDOMAIN_PS, VOS_TRUE, NAS_MML_REG_FAIL_CAUSE_NULL);
        /* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-13, end */
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
        NAS_MMC_SetPsRegAdditionalAction_PlmnList(enAdditionalAction);
    }

    if (VOS_TRUE == NAS_MMC_IsNeedSndEplmn())
    {
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, begin */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        /* Modified by z00161729 for DCM�����������������, 2012-8-21, end */

        NAS_MMC_SndOmEquPlmn();

        /* ֪ͨCSS GEO��Ϣ */
        NAS_MMC_SndCssCurrGeoInd(VOS_TRUE, stSndEquPlmnInfo.ucEquPlmnNum, stSndEquPlmnInfo.astEquPlmnAddr);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmAttachInd_PlmnList
 ��������  : Lmm TAU����Ĵ�����
 �������  : pstLmmTauIndMsg L��attach��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_ProcLmmAttachInd_PlmnList(
    LMM_MMC_ATTACH_IND_STRU            *pstLmmAttachIndMsg
)
{
    switch (pstLmmAttachIndMsg->ulReqType)
    {
        case MMC_LMM_ATT_TYPE_COMBINED_EPS_IMSI:

            /* ����lmm������attach��� */
            NAS_MMC_ProcLmmCombinedAttachInd_PlmnList(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_ONLY:

            /* ����lmm�ķ�����attach��EPS onlyע��Ľ�� */
            NAS_MMC_ProcLmmEpsOnlyAttachResultInd_PlmnList(pstLmmAttachIndMsg);
            break;

        case MMC_LMM_ATT_TYPE_EPS_EMERGENCY:

            /* �ݲ�֧��δʵ�� */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_PlmnList:Unsupported attach req type!");
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmAttachInd_PlmnList:Unexpected attach req type!");
            break;

    }

    return;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcNoRf_PlmnList
 ��������  : ����NO RF�ĳ���
 �������  : enCurRat------��ǰ���뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��24��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��18��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcNoRf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat
)
{
    /* פ��̬ʱ,RRC֪ͨNAS��ǰLIST �������ΪNO RFʱ,����RRC������פ��̬,
       ����������;��פ��̬���� */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        /* ��¼NO RF */
        NAS_MML_SetCurrRatRfAvailFlg(enCurRat, VOS_FALSE);

        /* ��MSCC֪ͨ��ǰNO RF��Ϣ  */
        NAS_MMC_SndMsccRfAvailInd(VOS_FALSE);

        /* ��RRM����ע�� */
        NAS_MMC_RegisterRrmResourceNtf(enCurRat, RRM_PS_TASK_TYPE_NAS_SEARCH);
    }

    NAS_MMC_SndMsccPlmnListRejMsg_PlmnList();


    /* ����״̬��ʧ�ܵ��˳���� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_NO_RF_FAIL,
                             VOS_FALSE,
                             NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                             NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}


#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListReq_PlmnList_Init
 ��������  : ��list������INIT״̬,�յ�MSCC��CSG LIST������Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:CSG list������Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��15��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListReq_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    /* ��ȡLTE����״̬ */
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
        /* ����disable L�ı�� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* �ж��Ƿ���Ҫanycell����,��Ҫ������anycell ������� */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* �����û�LIST�������� */
    NAS_MMC_ProcUserCsgListReq_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_PlmnList_Init
 ��������  : ��list������INIT״̬,�յ�MSCC�������Գ���CSG LIST������ʱ����ʱ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:CSG LIST������ʱ����ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��15��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiPeriodTryingUserCsgListExpired_PlmnList_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus;

    /* ��ȡLTE����״̬ */
    enLteCapStatus = NAS_MML_GetLteCapabilityStatus();
#endif

    /* ���浱ǰ��ϢΪ״̬�������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
        /* ����disable L�ı�� */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLteCapStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLteCapStatus))
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_TRUE);
    }
    else
    {
        NAS_MMC_SetPreLteDisableFlg_PlmnList(VOS_FALSE);
    }
#endif

    /* �ж��Ƿ���Ҫanycell����,��Ҫ������anycell ������� */
    if (VOS_TRUE == NAS_MMC_IsNeedAnyCellSrch_PlmnList())
    {
        NAS_MMC_SetAnyCellSrchFlg_PlmnList(VOS_TRUE);
    }

    /* �����û�LIST�������� */
    NAS_MMC_ProcUserCsgListReq_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsPsRegRsltInd
 ��������  : ��CSG list�����ĵȴ�CS/PS��ע����ʱ,�յ�LIST ABORT REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:LIST ABORT REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsPsRegRsltInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSPS_REG_IND);

    /* ����csg LIST ABORT CNF */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasSysInfoInd
 ��������  : ��CSG list�����ĵȴ�WASϵͳ��Ϣʱ,�յ�LIST ABORT REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:LIST ABORT REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��¼֪ͨMSCC������ */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasSysInfoInd
 ��������  : ��CSG list�����ĵȴ�WASϵͳ��Ϣʱ,�յ�LIST ABORT REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:LIST ABORT REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��¼֪ͨMSCC������ */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitRrcConnRelInd
 ��������  : ��CSG list�����ĵȴ�RRC��·�ͷ�״̬,�յ�CSG LIST ABORT��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:CSG LIST ABORT��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ����csg list abort cnf */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* δ��ʼ�������û���LIST������ʱ����ʱ����ʱ�����б�Ϊ��
       ��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN���յ���·�ͷź�
       ����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildReportCsgIdList_PlmnList
 ��������  : �����ϱ�MSCC��CSG ID�б�
 �������  : ��
 �������  : ������Ҫ�ϱ��б��������
 �� �� ֵ  : VOS_VOID
 ���ú���  : ���ú�����֤���ָ�벻��Ϊ��
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : s00193151
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_BuildReportCsgIdList_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                          ulServiceRslt;

    ulServiceRslt = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OP_CGS);

    /* ����LTE-BTR-1-0770�������AT&T������EF Operator List����(Service n90����)��
    ֻ�ϱ�Operator List�е�CSG ID�����������EF Operator List(��������ڣ�����
    ��Ϊ�ղ���)������EFAD��ֵȷ���Ƿ��ϱ����е�CSG ID */
    if ((VOS_TRUE == NAS_MML_GetOnlyReportOperatorCsgListFlag())
      &&(PS_USIM_SERVICE_AVAILIABLE == ulServiceRslt))
    {
        NAS_MMC_BuildReportCsgIdListInOperatorCsgList_PlmnList(pstCsgIdInfoList);
        return;
    }

    /* ��׼Э��ʵ�� */
    NAS_MMC_BuildReportCsgIdListAccordingCsgDisplayIndicator_PlmnList(pstCsgIdInfoList);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildReportCsgIdListInOperatorCsgList_PlmnList
 ��������  : ����AT&T����������Ҫ�ϱ�MSCC��CSG ID�б�
 �������  : ��
 �������  : ������Ҫ�ϱ��б��������
 �� �� ֵ  : VOS_VOID
 ���ú���  : ���ú�����֤���ָ�벻��Ϊ��
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : s00193151
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_BuildReportCsgIdListInOperatorCsgList_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                                              i;
    NAS_MML_PLMN_ID_STRU                                    stPlmnId;
    NAS_MML_PLMN_WITH_CSG_ID_STRU                           stPlmnCsgId;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          aenCsgIdType[NAS_MML_MAX_PLMN_CSG_ID_NUM]; /* ���ڰ��򱣴���Ӧ��CSG���� */

    /* �ֲ�������ʼ�� */
    stPlmnId.ulMcc             = NAS_MML_INVALID_MCC;
    stPlmnId.ulMnc             = NAS_MML_INVALID_MNC;
    stPlmnCsgId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnCsgId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stPlmnCsgId.ulCsgId        = 0;
    PS_MEM_SET(aenCsgIdType,   NAS_MML_CSG_ID_TYPE_BUTT, NAS_MML_MAX_PLMN_CSG_ID_NUM);

    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    /* �����ϱ��б��ԭ��Ϊ����Operator list��(�ǽ�ֹ)�����ϱ�˳��ΪRPLMN->HPLMN->OTHER PLMN��
    ��˳�򲢲����ǵ�ǰPLMN�Ǹ��������ǵ�������Ҳ����ȫ�������մ�˳��ԭ������ţ��п��ܵ�������
    ���ڸ�������ǰ�棬�����б�ʱ���ÿ���Խ����������Ϊ����״̬�������ı����������Ϊ35��������Խ�� */

    /* ��һ��ѭ���ȷ�RPLMN��CSG ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* ȡ��iλ�õ�PLMN CSG ID����Ϊ��ȡCSG ID TYPE����� */
        stPlmnCsgId.stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
        stPlmnCsgId.stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;
        stPlmnCsgId.ulCsgId        = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId;

        /* ��������ѭ�������е�CSG ID������ʶ��������´�ѭ��ʱ�Ϳ�ֱ��ʹ�ñ��α���Ľ�� */
        aenCsgIdType[i] = NAS_MMC_GetCsgIdType_PlmnList(&stPlmnCsgId);

        /* �����Operator List�е�����RPLMN��ӵ��ϱ���MSCC���б���(��ֹ���Ȳ��ϱ�) */
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            stPlmnId.ulMcc = stPlmnCsgId.stPlmnId.ulMcc;
            stPlmnId.ulMnc = stPlmnCsgId.stPlmnId.ulMnc;

            if (VOS_TRUE == NAS_MMC_IsPlmnSameWithRplmn(&stPlmnId))
            {
                /* �����ϱ����CNF�б��� */
                NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

                /* �´�ѭ�����ٴ����λ�õ�CSG ID */
                aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
            }
        }
    }

    /* �ڶ���ѭ����HPLMN��CSG ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* �����Operator List������HPLMN����ӵ��ϱ���MSCC���б���(��ֹ���Ȳ��ϱ�) */
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
            stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

            if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(&stPlmnId))
            {
                /* �����ϱ����CNF�б��� */
                NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

                /* �´�ѭ�����ٴ����λ�õ�CSG ID */
                aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
            }
        }
    }

    /* ������ѭ��������PLMN��CSG ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* �����Operator List�е���ӵ��ϱ���MSCC���б���(��ֹ���Ȳ��ϱ�) */
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            /* �����ϱ����CNF�б��� */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* �´�ѭ�����ٴ����λ�õ�CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    /* ��������operator list�Ĳ��ϱ� */
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildReportCsgIdListAccordingCsgDisplayIndicator_PlmnList
 ��������  : ������׼Э��Ҫ����Ҫ�ϱ�MSCC��CSG ID�б�
 �������  : ��
 �������  : ������Ҫ�ϱ��б��������
 �� �� ֵ  : VOS_VOID
 ���ú���  : ���ú�����֤���ָ�벻��Ϊ��
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : s00193151
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_BuildReportCsgIdListAccordingCsgDisplayIndicator_PlmnList(
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                                              i;
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          enCsgIdType;
    NAS_MML_PLMN_WITH_CSG_ID_STRU                           stPlmnCsgId;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          aenCsgIdType[NAS_MML_MAX_PLMN_CSG_ID_NUM]; /* ���ڰ��򱣴���Ӧ��CSG���� */

    /* �ֲ�������ʼ�� */
    enCsgIdType                = NAS_MML_CSG_ID_TYPE_BUTT;
    stPlmnCsgId.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnCsgId.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stPlmnCsgId.ulCsgId        = 0;
    PS_MEM_SET(aenCsgIdType,   NAS_MML_CSG_ID_TYPE_BUTT, NAS_MML_MAX_PLMN_CSG_ID_NUM);

    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    /* �����ϱ��б��ԭ��Ϊ������ָʾ������ʾ���ϱ�˳��ΪALLOWED LIST->OPERATOR LIST->AVAILABLE LIST��
    ��˳�򲢲����ǵ�ǰPLMN�Ǹ��������ǵ�������Ҳ����ȫ�������մ�˳��ԭ������ţ��п��ܵ�������
    ���ڸ�������ǰ�棬�����б�ʱ���ÿ���Խ����������Ϊ����״̬�������ı����������Ϊ35��������Խ�� */

    /* ����PLMN LIST״̬���������б������������CSG PLMN ID */
    for (i = 0; i < NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum, RRC_NAS_MAX_PLMN_CSG_ID_NUM); i++)
    {
        /* ��ʼ����ʱ����PLMN+CSG ID��ֵΪ��ǰ���ж�Ӧ���ֵ */
        stPlmnCsgId.stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
        stPlmnCsgId.stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;
        stPlmnCsgId.ulCsgId        = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId;

        /* ��ȡCSG ID���� */
        enCsgIdType  = NAS_MMC_GetCsgIdType_PlmnList(&stPlmnCsgId);

        /* �������ָʾ�����ϱ���ֱ��������CSG ID */
        if (VOS_TRUE != NAS_MMC_IsSpecCsgIdDisplayIndicatorNeedReport_PlmnList(&stPlmnCsgId, enCsgIdType))
        {
            /* ��Ӧ���鵥ԪaenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT��Ҳ����û������ */
            continue;
        }

        /* ����ָʾ�����ϱ�������CSG ID���� */
        if (NAS_MML_MAX_PLMN_CSG_ID_NUM > i)
        {
            aenCsgIdType[i] = enCsgIdType;
        }
    }

    /* �������ϱ�MSCC���б������Allowed List */
    for (i = 0; i < NAS_MML_MAX_PLMN_CSG_ID_NUM; i++)
    {
        if ((NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i]))
        {
            /* �����ϱ����CNF�б��� */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* �´�ѭ�����ٴ����λ�õ�CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    /* �������ϱ�MSCC���б������Operator List */
    for (i = 0; i < NAS_MML_MAX_PLMN_CSG_ID_NUM; i++)
    {
        if ((NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN == aenCsgIdType[i])
          ||(NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN == aenCsgIdType[i]))
        {
            /* �����ϱ����CNF�б��� */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* �´�ѭ�����ٴ����λ�õ�CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    /* �������ϱ�MSCC���б������Available List */
    for (i = 0; i < NAS_MML_MAX_PLMN_CSG_ID_NUM; i++)
    {
        if (NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST == aenCsgIdType[i])
        {
            /* �����ϱ����CNF�б��� */
            NAS_MMC_AddCsgIdToListCnf_PlmnList(i, aenCsgIdType[i], pstCsgIdInfoList);

            /* �´�ѭ�����ٴ����λ�õ�CSG ID */
            aenCsgIdType[i] = NAS_MML_CSG_ID_TYPE_BUTT;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�WAS�������ظ�ʱ,�յ������Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�WAS csg list��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�WAS�������ظ�ʱ,�յ�csg list abort��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�WAS csg list��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��WAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�WAS�������ظ�ʱ,�յ�csg list�����Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_CSG_LIST_SEARCH_CNF_STRU      *pstPlmnSearchcnf = VOS_NULL_PTR;

    pstPlmnSearchcnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* ֹͣ�ȴ�WAS csg list�����ظ��ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    /* ����CSG LIST�Ľ�� */
    NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList(pstPlmnSearchcnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�WAS�������ظ�ʱ,�յ�rel ind��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchCnf Enter!");

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF);

    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    /* ����״̬���˳���� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* ����5S�����Գ���CSG LIST������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�WAS�������ظ�ʱ,�յ�ϵͳ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasPlmnListCnfExpired_PlmnList_WaitWasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�WAS�������ظ�ʱ,�������ظ���ʱ����ʱ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasCsgListCnfExpired_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
#endif

    /* ��WAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitAsCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�WAS�������ظ�ʱ,�յ�������Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmAreaLostInd_PlmnList_WaitAsCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* �ϱ���Ӧ��CS/PS����״̬MSCC_MMC_SERVICE_STATUS_NO_SERVICE */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);
    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�WAS�������ظ�ʱ,�յ�csע������Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�WAS�������ظ�ʱ,�յ�psע������Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitWasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�GAS�������ظ�ʱ,�յ�abort��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�GAS csg list��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�GAS�������ظ�ʱ,�յ�csg list abort��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�GAS csg list��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�GAS�������ظ�ʱ,�յ����������Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_CSG_LIST_SEARCH_CNF_STRU      *pstPlmnSrchcnf = VOS_NULL_PTR;

    pstPlmnSrchcnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* ֹͣ�ȴ�GAS csg list�����ظ��ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF);

    /* ����CSG LIST�Ľ�� */
    NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList(pstPlmnSrchcnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�GAS�������ظ�ʱ,�յ�ϵͳ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasCsgListCnfExpired_PlmnList_WaitGasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�GAS�������ظ�ʱ,�������ظ���ʱ����ʱ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasCsgListCnfExpired_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
#endif

    /* ��GAS����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�GAS�������ظ�ʱ,�յ�csע������Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmCsRegResultInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMMMC_CS_REG_RESULT_IND_STRU       *pstCsRegRslt = VOS_NULL_PTR;

    pstCsRegRslt = (MMMMC_CS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstCsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����CS��ע���� */
    NAS_MMC_ProcCsRegRslt_PlmnList(pstCsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�GAS�������ظ�ʱ,�յ�psע������Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmPsRegResultInd_PlmnList_WaitGasCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstPsRegRslt = VOS_NULL_PTR;

    pstPsRegRslt = (GMMMMC_PS_REG_RESULT_IND_STRU*)pstMsg;

    /* �ȴ�RRC��·�ͷ�ʱ���������ѡ���л��Լ�CCO����������ᷢ���ı䣬
       ״̬���˳����յ������ע������Ϣ����Ҫ�жϵ�ǰ������
       �����ı䣬�����ı�������ǰע���� */
    if ( pstPsRegRslt->enNetType != NAS_MML_GetCurrNetRatType())
    {
        return VOS_TRUE;
    }

    /* ����PS��ע����*/
    NAS_MMC_ProcPsRegRslt_PlmnList(pstPsRegRslt);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListWasSuspendCnf
 ��������  : ��CSG List�����ĵȴ�WAS����ظ�ʱ���յ�abort��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListWasSuspendCnf
 ��������  : ��CSG List�����ĵȴ�WAS����ظ�ʱ���յ�csg list abort��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListWasSuspendCnf
 ��������  : ��CSG List�����ĵȴ�WAS����ظ�ʱ���յ�����ظ���Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    /* �������ظ���� */
    NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitCsgListWasSuspendCnf
 ��������  : ��CSG List�����ĵȴ�WAS����ظ�ʱ���ȹ���ظ���ʱ����ʱ��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitCsgListWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSuspendCnfExpired_PlmnList_WaitCsgListWasSuspendCnf: Timer Expired");

    /* ���ɻָ����ϣ���λ */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListGasSuspendCnf
 ��������  : ��CSG List�����ĵȴ�GAS����ظ�ʱ���յ�abort��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListGasSuspendCnf
 ��������  : ��CSG List�����ĵȴ�GAS����ظ�ʱ���յ�csg list abort��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListGasSuspendCnf
 ��������  : ��CSG List�����ĵȴ�GAS����ظ�ʱ���յ�����ظ���Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    /* �������ظ���� */
    NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList(pstRrmmSuspendCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitCsgListGasSuspendCnf
 ��������  : ��CSG List�����ĵȴ�GAS����ظ�ʱ���ȹ���ظ���ʱ����ʱ��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitCsgListGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasSuspendCnfExpired_PlmnList_WaitCsgListGasSuspendCnf: Timer Expired");

    /* ���ɻָ����ϣ���λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�GASֹͣ�����ظ�ʱ���յ�abort��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�GASֹͣ�����ظ�ʱ���յ�ֹͣ�����ظ���Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�GASֹͣ�����ظ�ʱ���յ�ϵͳ��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGrrMmSysInfoInd_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcGasSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�GASֹͣ�����ظ�ʱ���յ�csg list abort��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�GASֹͣ�����ظ�ʱ���յ�csg list�����Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;
    RRMM_CSG_LIST_SEARCH_CNF_STRU                          *pstPlmnSrchCnf = VOS_NULL_PTR;

    pstPlmnSrchCnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
    if (RRC_NAS_CSG_SEARCH_RLT_NO_RF == pstPlmnSrchCnf->enSearchRlt)
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

        return VOS_TRUE;
    }

     /*ֻ���������ɹ�ʱ�Ž��д��� */
    if (RRC_NAS_CSG_SEARCH_RLT_SUCC != pstPlmnSrchCnf->enSearchRlt)
    {
        return VOS_TRUE;
    }

    /* ����GU AS�ϱ����б��ѽ����״̬���������� */
    NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(pstPlmnSrchCnf);

    /* ����L�ѱ������� */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(MMC_LMM_RAT_LTE);
#endif

    /* ����CSG���������ս��ˢ��״̬���������еĸߵ����������б� */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�GASֹͣ�����ظ�ʱ����ֹͣ�����ظ���ʱ����ʱ��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnList_WaitGasCsgListSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�WASֹͣ�����ظ�ʱ���յ�abort��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�WASֹͣ�����ظ�ʱ���յ�ֹͣ�����ظ���Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ��Ǩ��״̬ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�WASֹͣ�����ظ�ʱ���յ�ϵͳ��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmSysInfoInd_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����פ����Ϣ����ת��ϵͳ��Ϣ */
    NAS_MMC_ProcWasSysInfo_PlmnList(pstMsg);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCsgListAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�WASֹͣ�����ظ�ʱ���յ�csg list abort��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCsgListAbortFsmMsg_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ��ֹ��ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�WASֹͣ�����ظ�ʱ���յ�csg list���������Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmCsgListSrchCnf_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;
    RRMM_CSG_LIST_SEARCH_CNF_STRU                          *pstPlmnSrchCnf = VOS_NULL_PTR;

    pstPlmnSrchCnf = (RRMM_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
    if (RRC_NAS_CSG_SEARCH_RLT_NO_RF == pstPlmnSrchCnf->enSearchRlt)
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

     /*ֻ���������ɹ�ʱ�Ž��д��� */
    if (RRC_NAS_CSG_SEARCH_RLT_SUCC != pstPlmnSrchCnf->enSearchRlt)
    {
        return VOS_TRUE;
    }

    /* ����GU AS�ϱ����б��ѽ����״̬���������� */
    NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(pstPlmnSrchCnf);

    /* ����L�ѱ������� */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(MMC_LMM_RAT_LTE);
#endif

    /* ����CSG���������ս��ˢ��״̬���������еĸߵ����������б� */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�WASֹͣ�����ظ�ʱ���յ�rel ind��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_PlmnList_WaitWasCsgListSearchStopCnf: ENTERED");

    /* �����ж�ԭ��ֵ */

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ״̬���˳����Ϊ�� */
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* ��ǰ��csg�б����� */
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* ��MSCC�ظ�csg LIST ABORT CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();
        }
        else
        {
            /* ��MSCC�ظ�csg LIST������� */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                VOS_FALSE,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����״̬���˳���� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* ����5S�����Գ���csg LIST������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasCsgListSearchStopCnf
 ��������  : ��CSG List�����ĵȴ�WASֹͣ�����ظ�ʱ����wasֹͣ������ʱ����ʱ��Ϣ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnList_WaitWasCsgListSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsCsgList_PlmnList
 ��������  : �жϵ�ǰ�Ƿ����û�CSG LIST����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  �û�CSG LIST����
             VOS_FALSE ��CSG LIST����
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_IsCsgList_PlmnList(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if ( (ID_MSCC_MMC_CSG_LIST_SEARCH_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
      || (TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMsccCsgListSearchCnf_PlmnList
 ��������  : ��MSCC����CSG LIST�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCsgListSearchCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU  *pstCsgListSrchCnf = VOS_NULL_PTR;

    /* �����ϱ�������ڴ�ռ� */
    pstCsgListSrchCnf = (MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                    sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU));

    if (VOS_NULL_PTR == pstCsgListSrchCnf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCsgListSearchCnf_PlmnList:ERROR,Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCsgListSrchCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstCsgListSrchCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCsgListSrchCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCsgListSrchCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCsgListSrchCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCsgListSrchCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCsgListSrchCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_CSG_LIST_SEARCH_CNF;

    /* ���������ϱ�������CSG ID�������ϱ���CSG ID�б� */
    NAS_MMC_BuildReportCsgIdList_PlmnList(&(pstCsgListSrchCnf->stCsgIdInfo));

    /* ��MSCC����LIST CNF��Ϣ */
    NAS_MMC_SndMsccUserCsgListSearchCnf(pstCsgListSrchCnf);

    PS_MEM_FREE(WUEPS_PID_MMC, pstCsgListSrchCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndMsccCsgListAbortCnf_PlmnList
 ��������  : ��MSCC����CSG LIST abort���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_SndMsccCsgListAbortCnf_PlmnList(VOS_VOID)
{
    MMC_MSCC_CSG_LIST_ABORT_CNF_STRU                      *pstCsgListAbortCnf = VOS_NULL_PTR;

    /* �����ϱ�������ڴ�ռ� */
    pstCsgListAbortCnf = (MMC_MSCC_CSG_LIST_ABORT_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                    sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU));

    if (VOS_NULL_PTR == pstCsgListAbortCnf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndMsccCsgListAbortCnf_PlmnList:ERROR,Memory Alloc Error");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstCsgListAbortCnf) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstCsgListAbortCnf->MsgHeader.ulLength          = sizeof(MMC_MSCC_CSG_LIST_ABORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCsgListAbortCnf->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstCsgListAbortCnf->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstCsgListAbortCnf->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstCsgListAbortCnf->MsgHeader.ulReceiverPid     = UEPS_PID_MSCC;
    pstCsgListAbortCnf->MsgHeader.ulMsgName         = ID_MMC_MSCC_CSG_LIST_ABORT_CNF;

    /* ���������ϱ�������CSG ID�������ϱ���CSG ID�б� */
    NAS_MMC_BuildReportCsgIdList_PlmnList(&(pstCsgListAbortCnf->stCsgIdInfo));

    /* ��MSCC����LIST ABORT CNF��Ϣ */
    NAS_MMC_SndMsccUserCsgListAbortCnf(pstCsgListAbortCnf);

    PS_MEM_FREE(WUEPS_PID_MMC, pstCsgListAbortCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList
 ��������  : ��ָ���Ľ��뼼������CSG LIST��������
 �������  : enRat ָ���Ľ��뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��15��
    ��    ��   : y00358807
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            NAS_MMC_SndLmmCsgListSearchReq();

            /* Ǩ��״̬���ȴ�LMM��LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsCsgListSearchReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WRR��CSG LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF, TI_NAS_MMC_WAIT_WAS_CSG_LIST_SEARCH_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsCsgListSearchReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS��CSG LIST�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF, TI_NAS_MMC_WAIT_GAS_CSG_LIST_SEARCH_CNF_LEN);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList Unexpected Rat type!");

            break;
    }

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcUserCsgListReq_PlmnList
 ��������  : �����û�CSG LIST��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��15��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcUserCsgListReq_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType     = NAS_MML_GetCurrNetRatType();

#if (FEATURE_LTE == FEATURE_ON)
    /* ����״̬�±���ϣ���ǰ���뼼��ΪBUTT */
    if( NAS_MML_NET_RAT_TYPE_BUTT == NAS_MML_GetCurrNetRatType())
    {
       enRatType = NAS_MML_NET_RAT_TYPE_LTE;
       NAS_MML_SetCurrNetRatType(enRatType);
    }
#endif

    /* ���³�ʼ��NAS_MMC_GetSearchCtrlInfo_PlmnList��ֻ��LTE���뼼�� */
    NAS_MMC_InitCsgListSearchRatInfo_PlmnList();

    /* �ж��Ƿ���Ҫ�ȴ������ͷ� */
    if ( VOS_FALSE == NAS_MMC_IsNeedWaitRrcRel_PlmnList() )
    {
        /* ���ݲ�ͬ����ģʽ,����LIST��������Ǩ���ȴ��������״̬������������ʱ��*/
        if ((NAS_MMC_AS_CELL_CAMP_ON == NAS_MMC_GetAsCellCampOn())
         || (NAS_MML_NET_RAT_TYPE_LTE == enRatType))
        {
            NAS_MMC_SndSpecRatCsgListSearchReq_PlmnList(enRatType);
            return;
        }

        /* gu�·�פ��̬��Ҫ����gu��lte������ */
        NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(enRatType);

        return;
    }

    /* ��Ҫ�ȴ������ͷ� */
    switch (NAS_MML_GetCurrNetRatType())
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

        /* L����EPS�������ӱ����ȴ�LMM�ͷ���·,
           ������GU��ʵ��һ�� */

        /* Ǩ��״̬���ȴ�LMM��EPS��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        break;
#endif

    case NAS_MML_NET_RAT_TYPE_WCDMA:
    case NAS_MML_NET_RAT_TYPE_GSM:

        /* Ǩ��״̬���ȴ�GU��RRC��·�ͷ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND);

        /* ����������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

        break;

    default:
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcUserPlmnListReq_PlmnList Unexpected Rat type!");

        break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList
 ��������  : ��ָ���Ľ��뼼�����͹�������
 �������  : enRat - ָ���Ľ��뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* Ŀǰֻ֧��LTE CSG,�����ڹ���lte�ĳ��� */
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ����פ��״̬ */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

            /* ��WAS���͹������� */
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WAS�Ĺ���ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_WAS_SUSPEND_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ����פ��״̬ */
            NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

            NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

            /* ��GAS���͹������� */
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS�Ĺ���ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_GAS_SUSPEND_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList Unexpected Rat type!");

            break;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList
 ��������  : ��ָ���Ľ��뼼������ֹͣCSG List��������
 �������  : enRat ָ���Ľ��뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
#if (FEATURE_LTE == FEATURE_ON)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ��LMM����ֹͣ�������� */
            NAS_MMC_SndLmmPlmnSrchStopReq();

            /* Ǩ��״̬���ȴ�LMM��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ��WAS����ֹͣ�������� */
            NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WAS��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_WAS_CSG_LIST_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ��GAS����ֹͣ�������� */
            NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS��ֹͣ�����ظ� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_CSG_LIST_STA_WAIT_GAS_CSG_LIST_SEARCH_STOP_CNF);

            /* ����������ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList Unexpected Rat type!");

            break;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcRrmmCsgListSearchSucc_PlmnList
 ��������  : ����CSG PLMN LIST�ĳɹ��Ľ��
 �������  : pstPlmnSrchCnf PLMN LIST�Ľ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmCsgListSearchSucc_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU      *pstPlmnSrchCnf
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    /* ����GU AS�ϱ����б��ѽ����״̬���������� */
    NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(pstPlmnSrchCnf);

    /* ����L�ѱ������� */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SetSearchedFlag_PlmnList(MMC_LMM_RAT_LTE);
#endif

    /* ����CSG���������ս��ˢ��״̬���������еĸߵ����������б� */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

    NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

    /* CSG LIST����������,RRC���ܳ�������,��ʱ��Ҫ��������״̬,�����˳�LIST�������ָ������ */
    if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
    {
        NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    }


    /* ����״̬���˳��Ľ�� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                            (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                             NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                             NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList
 ��������  : ��������Ĺ���ظ��Ľ��
 �������  : pstRrmmSuspendCnf - �����Ĺ���ظ��Ľ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList(
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;
    VOS_UINT32                          ulNeedPlmnSearch;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    if ( MMC_AS_SUSPEND_FAILURE  == pstRrmmSuspendCnf->ucResult )
    {
        /* ���帴λ */

        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);
        }
        else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return;
    }

    /* �ж�״̬���˳�����Ƿ�Ϊ�棬���Ϊ��*/
    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        ulNeedPlmnSearch = VOS_FALSE;

        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* ��MSCC�ظ�ABORT_CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

            ulNeedPlmnSearch = VOS_TRUE;
        }
        else
        {
            /* ��MSCC�ظ�csg LIST������� */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* ����״̬��ABORT���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ�����뼼�� */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enRat))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmCsgListSuspendCnf_PlmnList: Get next search rat fail.");

        /* ���뼼������ΪBUTT����������ֱ��������ģ������������ */
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* ��ǰΪ�û�LIST���� */
        if ( VOS_TRUE == NAS_MMC_IsCsgList_PlmnList())
        {
            /* ��MSCC�ظ�ID_MMC_MSCC_CSG_LIST_SEARCH_CNF */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* ����״̬���˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ���ݻ�ȡ�Ľ��뼼�����õ�ǰ���뼼�� */
    NAS_MML_SetCurrNetRatType(enRat);

    /* ���¸�����ģʽ����LIST��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatPlmnListReq_PlmnList(enRat);

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList
 ��������  : ����CSG LIST�Ľ��
 �������  : pstPlmnSrchCnf - CSG LIST�Ľ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU       *pstPlmnSrchCnf
)
{
    /* �ж�CSG LIST������� */
    switch (pstPlmnSrchCnf->enSearchRlt)
    {
        case RRC_NAS_CSG_SEARCH_RLT_REJ:

            /* ����5S�����Գ��Զ�ʱ�� */
            /* CSҵ�����绰���������Ľ����list rej��Ҫ��ֹlist�ѣ�
                ��Ӧҵ�����AT�ڱ�list����ռ�ã��û��޷���������绰���ն��� */
            if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
            {
                /* ����LIST REJ��MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH_LEN);
            }

            /* ����״̬��ʧ�ܵ��˳���� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            break;

       case RRC_NAS_CSG_SEARCH_RLT_SUCC:

            /* ����CSG LIST�����ɹ��Ľ�� */
            NAS_MMC_ProcRrmmCsgListSearchSucc_PlmnList(pstPlmnSrchCnf);

            break;

       /* ���������̬�»ظ��ý����mmc��������5s�����Գ���csg list�Ѷ�ʱ����ֱ���ϱ�ʧ�� */
       case RRC_NAS_CSG_SEARCH_RLT_FAIL:

            /* ����LIST REJ��MSCC */
            NAS_MMC_SndMsccCsgListSearchRej();

            /* ����״̬��ʧ�ܵ��˳���� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                    VOS_FALSE,
                                    NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                    NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();
            break;

       case RRC_NAS_CSG_SEARCH_RLT_NO_RF:
            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_GetCurrNetRatType());
            break;

       default:

            /*�쳣��ӡ*/
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcRrmmCsgListSearchCnf_PlmnList Unexpected List Result!");

            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList
 ��������  : �������������ֹͣ�ظ��Ľ��
 �������  : enRatType - ��ǰ���뼼��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcRrmmCsgListSearchStopCnf_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;
    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* ��MSCC�ظ�ABORT_CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

            ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
        }
        else
        {
            /* ��MSCC�ظ�csg LIST������� */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ��δ�����Ľ���ģʽ */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* �����������������������ϱ���MSCC */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* ����״̬��ʧ���˳��Ľ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ǰ���뼼�����͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSuspendReq_PlmnList(enRatType);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList
 ��������  : ����RRMM CSG PLMN LIST�ĳɹ��Ľ����PLMN LIST״̬����������
 �������  : pstPlmnSrchCnf CSG LIST�Ľ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  : ���ú�����֤���ָ�벻��Ϊ��
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : s00193151
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_SaveRrmmCsgListSearchResult_PlmnList(
    RRMM_CSG_LIST_SEARCH_CNF_STRU       *pstPlmnSrchCnf
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;

    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();

    /* �������ͱ������� */
    pstCsgPlmnIdList->ulTotalPlmnNum = NAS_MML_MIN(RRC_NAS_MAX_PLMN_CSG_ID_NUM,
                                        pstPlmnSrchCnf->stCsgListSearchedResult.ulTotalPlmnNum);

    pstCsgPlmnIdList->ulHighPlmnNum = NAS_MML_MIN(pstCsgPlmnIdList->ulTotalPlmnNum,
                                        pstPlmnSrchCnf->stCsgListSearchedResult.ulHighPlmnNum);

    /* ���������б� */
    PS_MEM_CPY(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList,
                    pstPlmnSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList,
                    (pstCsgPlmnIdList->ulTotalPlmnNum) * sizeof(RRMM_CSG_LIST_SEARCHED_PLMN_INFO_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsgIdType_PlmnList
 ��������  : ��ȡ��PLMN CSG ID�����ͣ������ĸ�����
 �������  : RRMM_PLMN_CSG_ID_WITH_RAT_STRU   CSG ID+PLMN
 �������  : ��
 �� �� ֵ  : NAS_MML_CSG_ID_TYPE_ENUM_UINT8   ����
 ���ú���  : ���ú�����֤���ָ�벻��Ϊ��
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : s00193151
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
NAS_MML_CSG_ID_TYPE_ENUM_UINT8 NAS_MMC_GetCsgIdType_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId
)
{
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU *pstAllowedList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU *pstOperatorList = VOS_NULL_PTR;

    pstOperatorList                     = NAS_MML_GetOperatorCsgList();
    pstAllowedList                      = NAS_MML_GetAllowedCsgList();

    /* ����Ǻ�С�����򲻴���CSG ID���ͣ�����BUTT */
    if (NAS_MML_INVALID_CSG_ID_VALUE == pstPlmnCsgId->ulCsgId)
    {
        return NAS_MML_CSG_ID_TYPE_BUTT;
    }

    /* �����Allowed List�� */
    if (VOS_TRUE == NAS_MMC_IsPlmnWithCsgIdInDestCsgIdWithHomeNodeBNameList(pstPlmnCsgId,
                                        pstAllowedList->ulPlmnWithCsgIdListNum,
                                        pstAllowedList->astPlmnWithCsgIdInfo))
    {
        /* �����Operator List�� */
        if (VOS_TRUE == NAS_MMC_IsPlmnWithCsgIdInDestCsgIdWithHomeNodeBNameList(pstPlmnCsgId,
                                        pstOperatorList->ulPlmnWithCsgIdListNum,
                                        pstOperatorList->astPlmnWithCsgIdInfo))
        {
            return NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST;

        }

        return NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST;
    }

    /* ����Allowed List�У�������Operator List�� */
    if (VOS_TRUE == NAS_MMC_IsPlmnWithCsgIdInDestCsgIdWithHomeNodeBNameList(pstPlmnCsgId,
                                        pstOperatorList->ulPlmnWithCsgIdListNum,
                                        pstOperatorList->astPlmnWithCsgIdInfo))
    {
        /* �����ǰ���ڽ�ֹ״̬ */
        if (VOS_TRUE == NAS_MMC_IsPlmnCsgIdInForbiddenCsgList(pstPlmnCsgId))
        {
            return NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN;
        }

        return NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN;
    }

    /* �����κ�һ���б��� */
    return NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSpecCsgIdDisplayIndicatorNeedReport_PlmnList
 ��������  : ���ݿ��ļ��жԴ�CSG ID��Display Indicator�ж�ָ��csg id�Ƿ���Ҫ�ϱ�
 �������  : RRMM_PLMN_CSG_ID_WITH_RAT_STRU   CSG ID+PLMN
             NAS_MML_CSG_ID_TYPE_ENUM_UINT8   CSG ID����
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE �ϱ��� VOS_FAULSE ���ϱ���
 ���ú���  : ���ú�����֤���ָ�벻��Ϊ��
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : s00193151
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsSpecCsgIdDisplayIndicatorNeedReport_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId,
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8      enCsgIdType
)
{
    NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_ENUM_UINT8        ucCsgDisplayIndicator;

    ucCsgDisplayIndicator = NAS_MML_CSG_ID_DISPLAY_IND_BUTT;

    /* CSG ID�����쳣�ģ�˵���Ǻ�С�����߳����������쳣��Ĭ��Ϊ���ϱ� */
    if ((NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST > enCsgIdType)
      ||(NAS_MML_CSG_ID_TYPE_BUTT <= enCsgIdType))
    {
        return VOS_FALSE;
    }

    /* ���SERVICE n92�����ã���Ĭ��Ϊ�����ϱ� */
    if (PS_USIM_SERVICE_AVAILIABLE != NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_CSG_CTRL))
    {
        return VOS_TRUE;
    }

    /* SERVICE n92���ã����ݶ�Ӧ��CSG ID���ͣ����в�ͬ�Ĵ��� */
    switch (enCsgIdType)
    {
        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST:
        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN:
        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN:

                /* �����Operator List�У����������ϱ� */
                return VOS_TRUE;

        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST:
        case    NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST:

                ucCsgDisplayIndicator = NAS_MMC_GetCsgDisplayIndicatorNotInOperatorCsgList_PlmnList(pstPlmnCsgId);

                if ((NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ALL_AVAILABLE_CSG_ID == ucCsgDisplayIndicator)
                  ||(NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_NOT_EXIST == ucCsgDisplayIndicator))
                {
                    /* �����ϱ��򲻴��ڶ��ϱ������������Ĭ�ϲ��ϱ� */
                    return VOS_TRUE;
                }

                break;

        default:
                break;

    }

    /* CSG ID�����쳣��Ĭ��Ϊ���ϱ� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetCsgDisplayIndicatorNotInOperatorCsgList_PlmnList
 ��������  : ��ȡ����OperatorList��CSG ID���ļ��жԴ�CSG ID��Display Indicator
 �������  : NAS_MML_PLMN_WITH_CSG_ID_STRU*   CSG ID+PLMN
 �������  : ��
 �� �� ֵ  : VOS_UINT8: 0 �ϱ��� 1 ���ϱ���2 �ϱ���
 ���ú���  : ���ú�����֤���ָ�벻��Ϊ��
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : s00193151
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT8 NAS_MMC_GetCsgDisplayIndicatorNotInOperatorCsgList_PlmnList(
    NAS_MML_PLMN_WITH_CSG_ID_STRU      *pstPlmnCsgId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucCsgDisplayIndicator;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_PLMN_ID_STRU                stOperatorPlmnId;
    VOS_UINT8                           ucEfadIndicator;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU *pstOperatorCsgIdList = VOS_NULL_PTR;

    /* �ֲ�������ʼ�� */
    ulIndex                = 0;
    ucCsgDisplayIndicator  = 0;
    stPlmnId.ulMcc         = pstPlmnCsgId->stPlmnId.ulMcc;
    stPlmnId.ulMnc         = pstPlmnCsgId->stPlmnId.ulMnc;
    stOperatorPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stOperatorPlmnId.ulMnc = NAS_MML_INVALID_MNC;

    ucEfadIndicator        = NAS_MML_GetCsgDisplayCtrlFlag();

    pstOperatorCsgIdList   = NAS_MML_GetOperatorCsgList();

    /* ��������CSG ID�Ƿ��������Ǻ�С����ֱ���ж�Ϊ���ϱ���
    ����ֻ�ϱ�Operator List�еģ�������Ȼ�����ϱ����� */
    if (NAS_MML_INVALID_CSG_ID_VALUE == pstPlmnCsgId->ulCsgId)
    {
        return NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ONLY_OPERATOR_CSG_ID;
    }

    /* ����Operator list��CSG ID������ʾָʾ�Ĵ���ԭ��:
    ���жϴ�CSG ID��PLMN�Ƿ���Operator list������ڣ�����PLMN���Ƿ��ж�Ӧ����ʾָʾ��
    �оͰ���ָʾ�ķ��أ�û�оͰ�EFAD���ļ�ָʾ���з��أ��������Operator list��ֱ�Ӱ�
    EFAD���ļ�ָʾ���з��أ�EFAD���ļ���������ڣ����ⲿӦ�ý�ulEfadIndicatorĬ�ϳ�ʼ��Ϊ�ϱ� */

    /* ��Operator List�в��ҵ�ǰPLMN */
    for (i = 0; i < pstOperatorCsgIdList->ulPlmnWithCsgIdListNum; i++)
    {
        stOperatorPlmnId.ulMcc = pstOperatorCsgIdList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.stPlmnId.ulMcc;
        stOperatorPlmnId.ulMnc = pstOperatorCsgIdList->astPlmnWithCsgIdInfo[i].stPlmnWithCsgId.stPlmnId.ulMnc;

        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmnId,&stOperatorPlmnId))
        {
            ulIndex = i;
            break;
        }
    }

    /* PLMN����Operator List�У�ֱ�Ӱ�EFAD���ļ�ָʾ��Display Indicatorָʾ���з��� */
    if (i >= pstOperatorCsgIdList->ulPlmnWithCsgIdListNum)
    {
        return ucEfadIndicator;
    }

    /* ���PLMN��Operator List�У����ҵ���Ӧ��PLMN��λ��ulIndex��ȡ����Ӧ��indicator */
    ucCsgDisplayIndicator = pstOperatorCsgIdList->astPlmnWithCsgIdInfo[ulIndex].enCsgDisplayIndicator;

    /* ����Display Indicator */
    if ((NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ALL_AVAILABLE_CSG_ID == ucCsgDisplayIndicator)
      ||(NAS_MML_CSG_ID_DISPLAY_INDICATOR_TYPE_DISPLAY_ONLY_OPERATOR_CSG_ID == ucCsgDisplayIndicator))
    {
        /* ����Display Indicatorָʾ���з��� */
        return ucCsgDisplayIndicator;
    }

    /* ��������ڣ���EFAD���ļ�ָʾ��Display Indicatorָʾ���з��� */
    return ucEfadIndicator;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_AddCsgIdToListCnf_PlmnList
 ��������  : ��״̬���������б����ָ��λ�õ�CSG ID��Ϣ��ӵ���MSCC�ϱ���LIST CNF���б���
 �������  : VOS_UINT32                                ����ӵ�״̬���������б����CSG ID��λ��
             NAS_MML_CSG_ID_TYPE_ENUM_UINT8            CSG ID����
             NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU*  �ϱ���MSCC����Ϣ�б�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  : ���ú�����֤���ָ�벻��Ϊ��
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : s00193151
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_AddCsgIdToListCnf_PlmnList(
    VOS_UINT32                                              ulIndex,
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8                          enCsgIdType,
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_INFO_STRU                *pstCsgIdInfoList
)
{
    VOS_UINT32                                              ulReportListIndex;
    NAS_MML_PLMN_WITH_CSG_ID_STRU                           stPlmnWithCsgId;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU                     *pstOperatorList  = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_CSG_ID_LIST_STRU                     *pstAllowedCsgList  = VOS_NULL_PTR;
    VOS_UINT32                                              ulCsgIdInCsgListIndex;

    /* �ҵ���ǰ�ѱ���λ�õ���һ��λ�� */
    ulReportListIndex              = pstCsgIdInfoList->ulPlmnWithCsgIdNum;

    /* ��ʼ����ʱ����PLMN ID�����ں����Ƚ�Operator listʹ�� */
    pstCsgPlmnIdList               = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    stPlmnWithCsgId.stPlmnId.ulMcc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
    stPlmnWithCsgId.stPlmnId.ulMnc = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;
    stPlmnWithCsgId.ulCsgId        = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.ulCsgId;

    /* ���ݺ������ulIndex���ҵ���Ӧ״̬���������б���Ĵ�CSG ID��������뵽��MSCC�ϱ���
    CSG ID LIST�У������λ��Ϊ����ǰ��MSCC�ϱ���CSG ID LIST���Ѵ��ڵ����һ��CSG ID����һ��λ�� */

    /* �б��Ѿ�����ֱ�ӷ��� */
    if (ulReportListIndex >= NAS_MSCC_PIF_MAX_PLMN_CSG_ID_NUM)
    {
        return;
    }

    /* ����PLMN */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].stPlmnId.ulMcc
                    = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc;
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].stPlmnId.ulMnc
                    = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc;

    /* ����CSG ID */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ulCsgId
                    = pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.ulCsgId;

    /* ������뼼�� */
    NAS_MMC_ConvertRrcRatToNasFormat(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat,
                    &pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].enRatType);

    /* ����CSG ID TYPE */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].enPlmnWithCsgIdType
                    = NAS_MMC_ConvertMmlCsgIdTypeToMsccCsgIdType_PlmnList(enCsgIdType);

    /* ����HNB Name */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucHomeNodeBNameLen
                    = NAS_MML_MIN(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stHomeNodeBName.ucHomeNodeBNameLen, NAS_MML_MAX_HOME_NODEB_NAME_LEN);
    PS_MEM_CPY(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucHomeNodeBName,
                    pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stHomeNodeBName.aucHomeNodeBName,
                    pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[ulIndex].stHomeNodeBName.ucHomeNodeBNameLen);

    pstOperatorList       = NAS_MML_GetOperatorCsgList();
    ulCsgIdInCsgListIndex = NAS_MMC_GetCsgIdIndexInDestCsgIdList(&stPlmnWithCsgId, pstOperatorList->ulPlmnWithCsgIdListNum, pstOperatorList->astPlmnWithCsgIdInfo);

    /* ������Operator list�е������ֱ������CSG TYPEΪ0 */
    pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucCsgTypeLen = 0;
    PS_MEM_SET(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucCsgType,
                                    0, NAS_MSCC_PIF_CSG_TYPE_LEN);

    /* Operator list���ҵ���Ӧ���λ������д��Ӧ��csg type */
    if (pstOperatorList->ulPlmnWithCsgIdListNum > ulCsgIdInCsgListIndex)
    {
        pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucCsgTypeLen
                      = NAS_MML_MIN(pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen, NAS_MML_MAX_CSG_TYPE_LEN);

        PS_MEM_CPY(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucCsgType,
                                pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.aucCsgType,
                                pstOperatorList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen);

        pstCsgIdInfoList->ulPlmnWithCsgIdNum++;
        return;
    }

    /* ����operator csg list������allowed csg list�в��Ҷ�Ӧ���λ����д��Ӧ��csg type */
    pstAllowedCsgList     = NAS_MML_GetAllowedCsgList();
    ulCsgIdInCsgListIndex = NAS_MMC_GetCsgIdIndexInDestCsgIdList(&stPlmnWithCsgId, pstAllowedCsgList->ulPlmnWithCsgIdListNum, pstAllowedCsgList->astPlmnWithCsgIdInfo);

    if (pstAllowedCsgList->ulPlmnWithCsgIdListNum > ulCsgIdInCsgListIndex)
    {
        pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].ucCsgTypeLen
                      = NAS_MML_MIN(pstAllowedCsgList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen, NAS_MML_MAX_CSG_TYPE_LEN);

        PS_MEM_CPY(pstCsgIdInfoList->astPlmnWithCsgIdList[ulReportListIndex].aucCsgType,
                                pstAllowedCsgList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.aucCsgType,
                                pstAllowedCsgList->astPlmnWithCsgIdInfo[ulCsgIdInCsgListIndex].stCsgType.ucCsgTypeLen);
    }

    pstCsgIdInfoList->ulPlmnWithCsgIdNum++;
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertAsCsgIdTypeToMsccCsgIdType_PlmnList
 ��������  : ��MML���͵�CSG ID TYPEת��ΪMSCCʹ�õ�����
 �������  : NAS_MML_CSG_ID_TYPE_ENUM_UINT8
 �������  : ��
 �� �� ֵ  : NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : s00193151
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8 NAS_MMC_ConvertMmlCsgIdTypeToMsccCsgIdType_PlmnList(
    NAS_MML_CSG_ID_TYPE_ENUM_UINT8      enCsgIdType
)
{
    NAS_MSCC_PIF_PLMN_WITH_CSG_ID_TYPE_ENUM_UINT8    enMsccCsgIdType;

    switch(enCsgIdType)
    {
        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST:
        case    NAS_MML_CSG_ID_TYPE_IN_ALLOWED_AND_OPERATOR_CSG_LIST:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_IN_ALLOWED_CSG_LIST;
                break;

        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_NOT_FOBIDDEN;
                break;

        case    NAS_MML_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_IN_OPERATOR_CSG_LIST_FOBIDDEN;
                break;

        case    NAS_MML_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_NOT_IN_ALLOWED_AND_OPERATOR_CSG_LIST;
                break;
        default:

                enMsccCsgIdType = NAS_MSCC_PIF_CSG_ID_TYPE_BUTT;
                break;

    }

    return enMsccCsgIdType;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsRegInd
 ��������  : ��CSG list�����ĵȴ�EPSע����״̬,�յ�LIST ABORT REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:LIST ABORT REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsRegInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_REG_IND);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsConnRelInd
 ��������  : ��CSG list�����ĵȴ�EPS��·�ͷ�״̬,�յ�LIST ABORT REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:LIST ABORT REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvCsgListAbortReq_PlmnList_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* ����ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
    NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

    /* δ��ʼ��������ʱ�����б�Ϊ��,��¼��ǰע�ᵼ�µĺ���additionֵ��L1 MAIN��
       �յ���·�ͷź����additionֵ�����Ƿ񴥷����� */
    NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                            VOS_FALSE,
                            NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                            NAS_MMC_GetRegRsltInfo_PlmnList());

    /*�˳�״̬��*/
     NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchCnf
 ��������  : ��CSG list�����ĵȴ�LMM�������ظ�ʱ,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�LMM��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ��LMM����ֹͣ��������,Ǩ��NAS_MMC_PLMN_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitLmmCsgListSearchCnf
 ��������  : ��csg list�����ĵȴ�LMM�������ظ�ʱ,�յ�csg list abort��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:csg list abort��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��10��16��
   ��    ��   : y00358807
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortReq_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ�LMM��������ı�����ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

    /* ��¼״̬���˳���� */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    /* ��LMM����ֹͣ��������,Ǩ��NAS_MMC_PLMN_LIST_STA_WAIT_LMM_CSG_LIST_SEARCH_STOP_CNF״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�LMM�������ظ�ʱ,�յ�CSG list �����ظ���Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:CSG list���������Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSearchCnf = VOS_NULL_PTR;

    pstLmmCsgListSearchCnf = (LMM_MMC_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* ����CSG LIST������� */
    NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList(pstLmmCsgListSearchCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList
 ��������  : ����LMM�µ�CSG PLMN LIST�Ľ��
 �������  : pstLmmCsgListSrchCnf - CSG list�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��18��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
)
{

    /* �ж�CSG LIST������� */
    switch (pstLmmCsgListSrchCnf->enRlst)
    {
        case MMC_LMM_CSG_LIST_SRCH_RLT_NO_RF:

            /* ֹͣ�ȴ�LMM�����ظ��ı�����ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);
            return;

        case MMC_LMM_CSG_LIST_SRCH_RLT_REJ:

            /* ֹͣ�ȴ�LMM�����ظ��ı�����ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
            {
                /* ����LIST REJ��MSCC */
                NAS_MMC_SndMsccCsgListSearchRej();
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_PERIOD_TRYING_USER_CSG_LIST_SEARCH, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST_LEN);
            }

            /* ����״̬��ʧ���˳��Ľ�� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                     VOS_FALSE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();
            return;

        case MMC_LMM_CSG_LIST_SRCH_RLT_FAIL:

            /* ֹͣ�ȴ�LMM�����ظ��ı�����ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

            /* ����LIST REJ��MSCC */
            NAS_MMC_SndMsccCsgListSearchRej();

            /* ����״̬��ʧ���˳��Ľ�� */
            NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                     VOS_FALSE,
                                     NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                     NAS_MMC_GetRegRsltInfo_PlmnList());

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();
            return;

        case MMC_LMM_CSG_LIST_SRCH_RLT_SUCC:

            /* �����б���������������ϱ� */
            NAS_MMC_ProcLmmCsgListSearchSucc_PlmnList(pstLmmCsgListSrchCnf);
            return;

        default:

            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ProcLmmCsgListSearchCnf_PlmnList: Unexpected Csg List Search Result!");
            break;

    }

    /* һ�׶�ֻ֧����LTE����˲������ж�����ģ��ֱ���˳�״̬�� */
    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCsgListSearchSucc_PlmnList
 ��������  : ����LMM CSG PLMN LIST�ĳɹ��Ľ��
 �������  : pstPlmnSrchCnf CSG LIST�Ľ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  : ���ú�����֤���ָ�벻��Ϊ��
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : s00193151
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCsgListSearchSucc_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
)
{
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    /* ����LMM�ϱ����б��ѽ����״̬���������� */
    NAS_MMC_SaveLmmCsgListSearchResult_PlmnList(pstLmmCsgListSrchCnf);

    /* �ϱ���������ʱ��˵��LMM�Ѿ��ϱ�������������� */
    if (VOS_TRUE == pstLmmCsgListSrchCnf->ucCsgListResultCompleteFlag)
    {
        /* ֹͣ�ȴ�LMM�����ظ��ı�����ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_CSG_LIST_SEARCH_CNF);

        /* ����L�ѱ������� */
        NAS_MMC_SetSearchedFlag_PlmnList(MMC_LMM_RAT_LTE);

        /* ����CSG���������ս��ˢ��״̬���������еĸߵ����������б� */
        pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
        NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* CSG LIST����������,RRC���ܳ�������,��ʱ��Ҫ��������״̬,�����˳�LIST�������ָ������ */
        if (NAS_MMC_AS_CELL_NOT_CAMP_ON == NAS_MMC_GetAsCellCampOn())
        {
            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
        }

        /* ����״̬���˳��Ľ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_SUCC,
                                 (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                 NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                 NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveLmmCsgListSearchResult_PlmnList
 ��������  : ����LMM CSG PLMN LIST�ĳɹ��Ľ����PLMN LIST״̬����������
 �������  : pstPlmnSrchCnf CSG LIST�Ľ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  : ���ú�����֤���ָ�벻��Ϊ��
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : s00193151
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_VOID NAS_MMC_SaveLmmCsgListSearchResult_PlmnList(
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListSrchCnf
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulSavePlmnNum;   /* ���ο��Ա����PLMN���� */
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                                    stGUNasPlmn;
    MMC_LMM_PLMN_ID_STRU                                    stLMMPlmn;
    VOS_UINT32                                              ulTotalPlmnNum;

    /* LMM���ܻ������ϱ���ֹ1����Ϣ����˴˴������ۼӷ�ʽ���� */
    pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
    ulTotalPlmnNum   = pstCsgPlmnIdList->ulTotalPlmnNum;


    /* �����������������ֻ��ʣ���λ�ý��б���(��ֹѭ������Խ��)��������Ͱ�LMMʵ���ϱ��������б���
    ����: ����35���Ѿ�������30�������LMM���ϱ���10�����Ǿ�ֻ����ǰ��5����ʣ�µĶ���*/
    if (NAS_MML_MAX_PLMN_CSG_ID_NUM < pstCsgPlmnIdList->ulTotalPlmnNum + pstLmmCsgListSrchCnf->stCsgListSearchedResult.ulTotalPlmnNum)
    {
        ulSavePlmnNum = NAS_MML_MAX_PLMN_CSG_ID_NUM - pstCsgPlmnIdList->ulTotalPlmnNum;
    }
    else
    {
        ulSavePlmnNum = pstLmmCsgListSrchCnf->stCsgListSearchedResult.ulTotalPlmnNum;
    }

    /* ��LMM�ϱ���CSG�б��ѽ�����棬ͬʱ��PLMNת����GU�ĸ�ʽ��ע�����ۼӱ��棬���α���Ҫ��������������һ��λ�ÿ�ʼ */
    for (i = pstCsgPlmnIdList->ulTotalPlmnNum; i < pstCsgPlmnIdList->ulTotalPlmnNum + ulSavePlmnNum; i++)
    {
        /* ������뼼�� */
        NAS_MMC_ConvertLmmRatToRrcFormat(pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stPlmnCsgIdWithRat.stPlmnWithRat.enPlmnRat,
              &pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.ulRat);

        /* ����CSG ID */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.ulCsgId
                    = pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stPlmnCsgIdWithRat.ulCsgId;

        /* ����HNB Name */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stHomeNodeBName.ucHomeNodeBNameLen
                    = NAS_MML_MIN(pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stHomeNodeBName.ucHomeNodeBNameLen, NAS_MML_MAX_HOME_NODEB_NAME_LEN);

        PS_MEM_CPY(pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stHomeNodeBName.aucHomeNodeBName,
                    pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stHomeNodeBName.aucHomeNodeBName,
                    pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stHomeNodeBName.ucHomeNodeBNameLen);

        /* ����lRscp */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].lRscp
                    = pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].lRscp;

        /* ת��������PLMN */

        /* ��ʼ����ʱ���� */
        PS_MEM_SET(&stGUNasPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));
        PS_MEM_SET(&stLMMPlmn,   0, sizeof(MMC_LMM_PLMN_ID_STRU));

        /* ȡ��LMM��PLMN����ʱ���� */
        PS_MEM_CPY(stLMMPlmn.aucPlmnId,
                    pstLmmCsgListSrchCnf->stCsgListSearchedResult.astCsgListSearchedPlmnInfoList[i-ulTotalPlmnNum].stPlmnCsgIdWithRat.stPlmnWithRat.aucPlmnId,
                    MMC_LMM_PLMN_ID_LEN);

        /* ת��L��PLMN��GU�ĸ�ʽ */
        NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLMMPlmn, &stGUNasPlmn);

        /* ����PLMN */
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMcc = stGUNasPlmn.ulMcc;
        pstCsgPlmnIdList->astCsgListSearchedPlmnInfoList[i].stPlmnCsgIdWithRat.stPlmnWithRat.stPlmnId.ulMnc = stGUNasPlmn.ulMnc;

    }

    /* ����PLMN���� */
    pstCsgPlmnIdList->ulTotalPlmnNum += ulSavePlmnNum;

    /* ��������ȼ�PLMN������ע�����LMM�ϱ���PLMNû��ȫ�����棬��ֻ����ʵ�ʱ���ĸ��� */
    pstCsgPlmnIdList->ulHighPlmnNum  += NAS_MML_MIN(pstLmmCsgListSrchCnf->stCsgListSearchedResult.ulHighPlmnNum, ulSavePlmnNum);

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmCsgListSrchCnfExpired_PlmnList_WaitLmmCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�LMM�������ظ�ʱ,�յ�������ʱ����ʱ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��CSG list�������������ʱ����ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitLmmCsgListSrchCnfExpired_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���µ�ǰRAT��������� */
    NAS_MMC_SetSearchedFlag_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��LMM����ֹͣ��������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatCsgListSearchStopReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�LMM�������ظ�ʱ,�յ�������Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:������Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��9��7��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ���·���״̬ �ϱ��޷���*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�LMM�������ظ�ʱ,�յ�ϵͳ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ϵͳ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�LMM�������ظ�ʱ,�յ�attach��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:attach��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�LMM�������ظ�ʱ,�յ�tau��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:tau��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchCnf
 ��������  : ��CSG List�����ĵȴ�LMM�������ظ�ʱ,�յ�ims voice cap ind��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ims voice cap ind��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ����ڵȴ�IMS��ע�����Ŵ��� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf
 ��������  : ��csg list�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�MMCMMC_ABORT_FSM_REQ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:MMCMMC_ABORT_FSM_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ABORT��־λ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf
 ��������  : ��csg list�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�csg list abort��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:CSG list abort��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��9��7��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccCsgListAbortFsmMsg_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ABORT��־λ */
    NAS_MMC_SetAbortFlag_PlmnList(VOS_TRUE);

    /* ����֪ͨMSCC����ı�� */
    NAS_MMC_SetNotifyMsccFlag_PlmnList(VOS_TRUE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchStopCnf
 ��������  : ��csg list�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�csg list�����Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:CSG list�����Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��10��21��
   ��    ��   : y00358807
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmCsgListSrchCnf_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_CSG_LIST_SEARCH_CNF_STRU   *pstLmmCsgListsearchCnf = VOS_NULL_PTR;
    NAS_MMC_CSG_SEARCHED_PLMN_LIST_INFO_STRU               *pstCsgPlmnIdList  = VOS_NULL_PTR;

    pstLmmCsgListsearchCnf = (LMM_MMC_CSG_LIST_SEARCH_CNF_STRU*)pstMsg;

    /* LIST�����ظ���ֹͣ�����Գ�,NO RFʱֱ���˳�LIST�������� */
    if (MMC_LMM_CSG_LIST_SRCH_RLT_NO_RF == pstLmmCsgListsearchCnf->enRlst)
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        NAS_MMC_ProcNoRf_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }

    /*ֻ���������ɹ�ʱ�Ž��д��� */
    if (MMC_LMM_CSG_LIST_SRCH_RLT_SUCC != pstLmmCsgListsearchCnf->enRlst)
    {
        return VOS_TRUE;
    }

    /* ����LMM�ϱ����б��ѽ����״̬���������� */
    NAS_MMC_SaveLmmCsgListSearchResult_PlmnList(pstLmmCsgListsearchCnf);

    /* �ϱ���������ʱ��˵��LMM�Ѿ��ϱ�������������� */
    if (VOS_TRUE == pstLmmCsgListsearchCnf->ucCsgListResultCompleteFlag)
    {
        /* ֹͣ������ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        /* ����L�ѱ������� */
        NAS_MMC_SetSearchedFlag_PlmnList(MMC_LMM_RAT_LTE);

        /* ����CSG���������ս��ˢ��״̬���������еĸߵ����������б� */
        pstCsgPlmnIdList = NAS_MMC_GetCsgSearchedPlmnListInfo_PlmnList();
        NAS_MMC_UpdateSearchedPlmnListInfoFromCsgSearchResult_PlmnList(pstCsgPlmnIdList);

        /* ��������ֹͣ�ظ���� */
        NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList();
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmCsgListSearchStopCnf
 ��������  : ��csg list�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�ֹͣ�����ظ���Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ֹͣ�����ظ���Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��10��16��
   ��    ��   : y00358807
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchStopCnf_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmCsgListSearchStopCnf
 ��������  : ��csg list�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ���ֹͣ�����ظ���ʱ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:��ֹͣ�����ظ���ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��10��16��
   ��    ��   : y00358007
   �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnList_WaitLmmCsgListSearchStopCnf: Timer Expired");

    /* ��������ֹͣ�ظ���� */
    NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchStopCnf
 ��������  : ��ֹͣCSG List�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�������Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:������Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/

VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ���·���״̬ �ϱ��޷���*/
    NAS_MMC_SetCsServiceStatus(NAS_MMC_NO_SERVICE);
    NAS_MMC_SetPsServiceStatus(NAS_MMC_NO_SERVICE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchCnf
 ��������  : ��ֹͣCSG List�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�ϵͳ��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ϵͳ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysInfoInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_ProcLteSysInfo_PlmnList(pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchCnf
 ��������  : ��ֹͣCSG List�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�attach��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:attach��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmAttachInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_ATTACH_IND_STRU                                *pstLmmAttachIndMsg = VOS_NULL_PTR;

    pstLmmAttachIndMsg  = (LMM_MMC_ATTACH_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmAttachInd(pstLmmAttachIndMsg);
    NAS_MMC_SndGmmLmmAttachInd(pstLmmAttachIndMsg);

    /* ����attach��� */
    NAS_MMC_ProcLmmAttachInd_PlmnList(pstLmmAttachIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchStopCnf
 ��������  : ��ֹͣCSG List�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�tau��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:tau��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmTauResultInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_TAU_RESULT_IND_STRU        *pstLmmTauIndMsg;

    pstLmmTauIndMsg  = (LMM_MMC_TAU_RESULT_IND_STRU*)pstMsg;

    /* ��GMM��MMת��ע������Ϣ */
    NAS_MMC_SndMmLmmTauResultInd(pstLmmTauIndMsg);
    NAS_MMC_SndGmmLmmTauResultInd(pstLmmTauIndMsg);

    /* ����tau��� */
    NAS_MMC_ProcLmmTauResultInd_PlmnList(pstLmmTauIndMsg);

    /* L��ע����ɺ�IMSʱ֧��ʱ�ᷢ��IMSע��,��Ҫ����IMSע�����������Ƿ���Ҫ
       disable Lģ,��ʱ��Ҫ��һ���ȴ�IMS��ע���� */
    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList();

#if (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_SetWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchStopCnf
 ��������  : ��ͣCSG List�����ĵȴ�LMM��ֹͣ�����ظ�ʱ,�յ�ims voice cap ind��Ϣ��Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg:ims voice cap ind��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : y00358807
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccImsVoiceCapInd_PlmnList_WaitLmmCsgListSearchStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *pstImsVoiceInd = VOS_NULL_PTR;
    VOS_UINT8                           ucWaitRegRsltFlag;

    ucWaitRegRsltFlag   = NAS_MMC_GetWaitRegRsltFlag_PlmnList();
    pstImsVoiceInd      = (MSCC_MMC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;

    /* ����ڵȴ�IMS��ע�����Ŵ��� */
    if (NAS_MMC_WAIT_REG_RESULT_IND_IMS != (ucWaitRegRsltFlag & NAS_MMC_WAIT_REG_RESULT_IND_IMS))
    {
        return VOS_TRUE;
    }

    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(NAS_MMC_WAIT_REG_RESULT_IND_IMS);

    /* IMS������ʱ�ж��Ƿ���Ҫdisable LTE */
    if (VOS_FALSE  == pstImsVoiceInd->ucAvail)
    {
        if (VOS_TRUE == NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail())
        {
            NAS_MMC_SetCsRegAdditionalAction_PlmnList(NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION);

            NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS);

            NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_LTE_VOICE_NOT_AVAILABLE);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList
 ��������  : ����LMM��CSG����ֹͣ�ظ��Ľ��
 �������  : enRatType ��ǰ���뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��06��
    ��    ��   : y00358807
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_ProcLmmCsgListSearchStopCnf_PlmnList(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRatType;

    VOS_UINT32                          ulNeedPlmnSearch;

    if ( VOS_TRUE == NAS_MMC_GetAbortFlag_PlmnList())
    {
        ulNeedPlmnSearch = VOS_FALSE;

        /* ֪ͨMSCC�ظ����Ϊ�� */
        if ( VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_PlmnList())
        {
            /* ��MSCC�ظ�ID_MMC_MSCC_PLMN_LIST_ABORT_CNF */
            NAS_MMC_SndMsccCsgListAbortCnf_PlmnList();

            ulNeedPlmnSearch = NAS_MMC_IsNeedPlmnSearch_PlmnList();
        }
        else
        {
            /* ��MSCC�ظ�LIST������� */
            NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();
        }

        /* ����״̬��ABORT�˳���� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_ABORTED,
                                (VOS_UINT8)ulNeedPlmnSearch,
                                NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ȡ������һ��δ�����Ľ���ģʽ */
    if ( VOS_FALSE == NAS_MMC_GetNextSearchingRat_PlmnList(&enNextRatType))
    {
        /* �����������������������ϱ���MSCC */
        NAS_MMC_SndMsccCsgListSearchCnf_PlmnList();

        /* ����״̬���ɹ��˳��Ľ�� */
        NAS_MMC_SndRslt_PlmnList(NAS_MMC_PLMN_LIST_FAIL,
                                 (VOS_UINT8)NAS_MMC_IsNeedPlmnSearch_PlmnList(),
                                 NAS_MMC_GetSearchedPlmnListInfo_PlmnList(),
                                 NAS_MMC_GetRegRsltInfo_PlmnList());

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return;
    }

    /* ��ǰ���뼼�����͹�������,Ǩ��״̬,����������ʱ�� */
    NAS_MMC_SndSpecRatSuspendReq_PlmnList(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    return;
}
#endif
#endif

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




