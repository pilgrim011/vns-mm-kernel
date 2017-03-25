/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcFsmSyscfg.c
  �� �� ��   : ����
  ��    ��   : z00161729
  ��������   : 2011��07��2��
  ����޸�   :
  ��������   : SYSCFG״̬������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��07��2��
    ��    ��   : z00161729
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "v_typdef.h"
#include "NasComm.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
#include "NasMmcCtx.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndLmm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcFsmSyscfg.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcFsmSyscfgTbl.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndInternalMsg.h"
#include "NasComm.h"
#include "NasUtranCtrlInterface.h"

#include "MmaMsccInterface.h"

#include "NasMmcComFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_SYSCFG_C
/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMsccSysCnfSetReq_SYSCFG_Init
 ��������  : ��NAS_MMC_SYSCFG_STA_INIT״̬�յ�MSCC��ID_MSCC_MMC_SYS_CFG_SET_REQ��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - �յ�MSCC��ID_MSCC_MMC_SYS_CFG_SET_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ɹ�
             VOS_FALSE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��15��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��

 4.��    ��   : 2013��7��15��
   ��    ��   : z00234330
   �޸�����   : DTS2013070500039

 5.��    ��   : 2013��9��11��
   ��    ��   : z00234330
   �޸�����   : dmt���Է������⣬gwģ��
                ����rrc����ʱ����ȴ���1�������ͷ�,DTS2013052300940
 6.��    ��   : 2015��2��26��
   ��    ��   : w00167002
   �޸�����   : DTS2015021604972:��SYSCFG�������MMA����ATTACH���̡�MMC�Ѿ��˳�
                 SYSCFG״̬����������������������ʱ�����PS��׼��ATTACH��������LTE��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMsccSysCfgSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg        = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    VOS_UINT32                          ulRrcConnExistFlag;
    VOS_UINT32                          ulNeedSyscfgPlmnSrch;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;
    VOS_UINT32                          ulFlg;
    VOS_UINT32                          ulUsimStausFlg;
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8 enPlmnSelectionMode;
    VOS_UINT8                           ucPreRatNum;
    VOS_UINT8                           ucCurRatNum;
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList;
    NAS_MML_PLMN_RAT_PRIO_STRU          stSyscfgPrioRatList;

    PS_MEM_SET(&stSyscfgPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

    pstPrePrioRatList = NAS_MML_GetMsPrioRatList();
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    /* ȡ�õ�ǰ��SYSCFG��Ϣ */
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg         = (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)pstMsg;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/


    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_SYSCFG);

    /* ���û����õ�SYSCFG��Ϣֻ���������Ըı䣬����Ҫ֪ͨ����� */
    if ( VOS_TRUE == pstSysCfgMsg->ucOnlyRoamParaChanged )
    {
        /* ��MSCC�ظ�SYSCFG���óɹ�ԭ�� */
        NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS);

        /* Ĭ���������ò���Ҫ�������� */
        ulNeedSyscfgPlmnSrch = VOS_FALSE;

        /* �ж�SYSCFG��ROAM���Ե������Ƿ���Ҫ�������� */
        ulUsimStausFlg = NAS_MML_IsUsimStausValid();
        ulFlg          = NAS_MMC_CheckRoamSettingPlmnSelection_SysCfg(pstSysCfgMsg);
        if ( (VOS_TRUE == ulUsimStausFlg)
          && (VOS_TRUE == ulFlg) )
        {
            ulNeedSyscfgPlmnSrch = VOS_TRUE;
            /*�ֶ�ģʽʱ,syscfg��Ҫ��������ʱ,��Ҫ����ǰ���������plmn�ͽ��뼼������һ����Ϊ�û���ѡ��plmn id�ͽ��뼼�� */
            enPlmnSelectionMode = NAS_MMC_GetPlmnSelectionMode();
            if ( NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enPlmnSelectionMode)
            {
                /* ����ָ������ǰפ����PlmnID�����뼼�� */
                NAS_MMC_SaveUserReselPlmnInfo();
            }
        }

        /* �����û����õ�������Ϣ */
        NAS_MML_SetRoamCapability(pstSysCfgMsg->enRoamCapability);


        /* ֪ͨ�ϲ�״̬��SYSCFG״̬�����н����syscfg���óɹ� */
        NAS_MMC_SndSysCfgRslt(VOS_TRUE, ulNeedSyscfgPlmnSrch, NAS_MMC_IsNeedAttachPs_SysCfg(), pstPrePrioRatList);


        /* �˳�SYSCFG״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }



    /* ���ݵ�ǰģ��Ϣ������������·�SYSCFG˳��������  */
    NAS_MMC_SetSysCfgSendingOrder_SysCfg( pstSysCfgMsg );

    /* �ж�SYSCFG�����Ƿ���Ҫ�������� */
    ulNeedSyscfgPlmnSrch = NAS_MMC_IsPlmnSelectionNeeded_SysCfg(pstSysCfgMsg);

    /* ����������Ϣ��״̬���������� */
    NAS_MMC_SetPlmnSearchFlag_SysCfg(ulNeedSyscfgPlmnSrch);

    /*�ֶ�ģʽʱ,syscfg��Ҫ��������ʱ,��Ҫ����ǰ���������plmn�ͽ��뼼������һ����Ϊ�û���ѡ��plmn id�ͽ��뼼�� */
    enPlmnSelectionMode = NAS_MMC_GetPlmnSelectionMode();
    if ( ( NAS_MMC_PLMN_SELECTION_MODE_MANUAL == enPlmnSelectionMode)
      && (VOS_TRUE == ulNeedSyscfgPlmnSrch) )
    {
        /* ����ָ������ǰפ����PlmnID�����뼼�� */
        NAS_MMC_SaveUserReselPlmnInfo();
    }

    ucPreRatNum = pstPrePrioRatList->ucRatNum;

    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    /* ����syscfg����ǰ�Ľ��뼼�������ȼ� */
    NAS_MMC_SetPrePrioRatList_SysCfg(pstPrePrioRatList);

    /* ��ֵ�û����õĽ��뼼�����ȼ� */
    PS_MEM_CPY(&stSyscfgPrioRatList,
               &(pstSysCfgMsg->stRatPrioList),
               sizeof(NAS_MML_PLMN_RAT_PRIO_STRU) );

    NAS_MML_SetMsSysCfgPrioRatList(&stSyscfgPrioRatList);
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    ucCurRatNum = NAS_MML_GetMsPrioRatList()->ucRatNum;

    /* ��ȡ��ǰģ���������Ӵ�����Ϣ */
    ulRrcConnExistFlag   = NAS_MML_IsRrcConnExist();

    /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-05-10, begin */
    if ( (VOS_TRUE == ulNeedSyscfgPlmnSrch)
      && (VOS_FALSE == ulRrcConnExistFlag)
      && (0 != ucPreRatNum)
      && (0 != ucCurRatNum) )
    {
        /* ��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();

        /* ��MM��������ָʾ */
        NAS_MMC_SndMmPlmnSchInit();
    }
    /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-05-10, end */

    /* ��ǰ����Ҫ�����򲻴����������� */
    if ( (VOS_FALSE == ulNeedSyscfgPlmnSrch)
      || (VOS_FALSE == ulRrcConnExistFlag) )
    {
        /* ��ȡ��Ҫ����SYSCFG�Ľ��뼼�� */
        enCurrRat             = NAS_MMC_GetNextSettingRat_SysCfg();
        NAS_MMC_SetRatModeSysCfgReq_SysCfg(enCurrRat, pstSysCfgMsg);

        return VOS_TRUE;
    }

    /* ��ǰSYSCFG���������Ҫ�������ҵ�ǰ���������Ӵ��ڣ�������������� */
#if (FEATURE_ON == FEATURE_LTE)

    /* ȡ�õ�ǰ�Ľ���ģʽ */
    enCurrRat            = NAS_MML_GetCurrNetRatType();
    if ( NAS_MML_NET_RAT_TYPE_LTE == enCurrRat )
    {
        /* ��ǰΪLģ����lmm�·������ͷ�����  */
        NAS_MMC_SndLmmRelReq();

        NAS_MMC_SetRelRequestFlag_SysCfg(VOS_TRUE);

        /* ����SYSCFG״̬������״̬��Ǩ��:Ǩ�Ƶ��ȴ������ͷ���״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_SYSCFG_STA_WAIT_EPS_CONN_REL_IND);

        /* �����ȴ�Lģ�ظ���ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);

        return VOS_TRUE;
    }
#endif

    /* ��ǰ��GUģ�£����������ͷ����� */
    NAS_MMC_SndMmRelReq();
    NAS_MMC_SndGmmRelReq();

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetRelRequestFlag_SysCfg(VOS_TRUE);

    /* ����SYSCFG״̬������״̬��Ǩ��:Ǩ�Ƶ��ȴ������ͷ���״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_SYSCFG_STA_WAIT_RRC_CONN_REL_IND);

    /* �����ȴ��ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasSysCfgCnf_SysCfg_WaitGasSysCfgCnf
 ��������  : ��NAS_MMC_SYSCFG_STA_WAIT_GAS_SYSCFG_CNF״̬�յ�GAS��RRMM_SYS_CFG_CNF��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - �յ�GAS��RRMM_SYS_CFG_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ɹ�
             VOS_FALSE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 4.��    ��   : 2015��2��26��
   ��    ��   : w00167002
   �޸�����   : DTS2015021604972:��SYSCFG�������MMA����ATTACH���̡�MMC�Ѿ��˳�
                 SYSCFG״̬����������������������ʱ�����PS��׼��ATTACH��������LTE��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasSysCfgCnf_SysCfg_WaitGasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstSysCfgMsg          = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg           = VOS_NULL_PTR;
    RRMM_SYS_CFG_CNF_STRU              *pstSysCfgCnf          = VOS_NULL_PTR;
    VOS_UINT32                          ulNeedSyscfgPlmnSrch;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRat;

    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList;
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    /* ֹͣ�ȴ�GAS��SYSCFG�ظ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF);

    /* ��syscfg����ʧ�ܣ����д����ӡ���˳�SYSCFG״̬�� */
    pstSysCfgCnf          = (RRMM_SYS_CFG_CNF_STRU *)pstMsg;
    if ( RRMM_SYS_CFG_RESULT_FAILURE == pstSysCfgCnf->ulResult)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvGasSysCfgCnf_SysCfg_WaitGasSysCfgCnf:ERROR:SYSCFG SET FAIL!");

        /* ��MSCC�ظ�SYSCFG����ʧ����Ϣ */
        NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER);

        /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
        /* syscfg����ʧ����Ҫ�ָ�֮ǰ�Ľ��뼼�������ȼ� */
        pstPrePrioRatList = NAS_MMC_GetPrePrioRatList_SysCfg();

        NAS_MML_SetMsSysCfgPrioRatList(pstPrePrioRatList);
        /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */


        /* ֪ͨ�ϲ�״̬��SYSCFG״̬�����н����syscfg����ʧ�ܣ�����Ҫ���� */
        NAS_MMC_SndSysCfgRslt(VOS_FALSE, VOS_FALSE, NAS_MMC_IsNeedAttachPs_SysCfg(), pstPrePrioRatList);


        /* �˳�SYSCFG״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��ȡsyscfg״̬�������Ϣ��Ϣ */
    pstEntryMsg           = NAS_MMC_GetCurrEntryMsg();

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg          = (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* δ���SYSCFG������ģʽ���ã������ģ����SYSCFG�������� */
    enNextRat             = NAS_MMC_GetNextSettingRat_SysCfg();
    if (NAS_MML_NET_RAT_TYPE_BUTT != enNextRat)
    {
        NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);
        return VOS_TRUE;
    }

    /* ���������ģʽ��SYSCFG����,����SYSCFG����������Ϣ */
    NAS_MMC_SaveUserSyscfgInfo_SysCfg(pstSysCfgMsg);

    /* SYSCFG������ɺ󣬽���С����Ϣ�ĸ��� */
    NAS_MMC_UpdateCellInfo_SysCfg();

    /* ��MSCC�ظ�SYSCFG���óɹ�ԭ�� */
    NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS);

    /* ����Ҫ����������������SYSCFG������ڲ�������Ϣ */
    ulNeedSyscfgPlmnSrch  = NAS_MMC_GetPlmnSearchFlag_SysCfg();


    pstPrePrioRatList = NAS_MMC_GetPrePrioRatList_SysCfg();

    /* ֪ͨ�ϲ�״̬��SYSCFG״̬�����н����syscfg���óɹ� */
    NAS_MMC_SndSysCfgRslt(VOS_TRUE, ulNeedSyscfgPlmnSrch, NAS_MMC_IsNeedAttachPs_SysCfg(), pstPrePrioRatList);


    /* �˳�SYSCFG״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



/*****************************************************************************
�� �� ��  : NAS_MMC_RcvGasSuspendInd_SysCfg_WaitGasSysCfgCnf
��������  : ��NAS_MMC_SYSCFG_STA_WAIT_GAS_SYSCFG_CNF״̬�յ�GAS��
             RRMM_SUSPEND_IND��Ϣ�Ĵ���
�������  : ulEventType - ��Ϣ����
            pstMsg      - �յ�RRMM_SUSPEND_IND��Ϣ���׵�ַ
�������  : ��
�� �� ֵ  : VOS_TRUE  - �ɹ�
            VOS_FALSE - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��7��11��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasSuspendInd_SysCfg_WaitGasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������ظ�����ʧ�� */
    NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, UEPS_PID_GAS);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasSysCfgCnfExpired_SysCfg_WaitGasSysCfgCnf
 ��������  : ��NAS_MMC_SYSCFG_STA_WAIT_GAS_SYSCFG_CNF״̬�յ�������ʱ��
             TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF��ʱ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - �յ�TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF��ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ɹ�
             VOS_FALSE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��21��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasSysCfgCnfExpired_SysCfg_WaitGasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList;
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    /* ��ӡ��ʱ����ʱ�쳣LOG */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvGasSysCfgCnfExpired_SysCfg_WaitGasSysCfgCnf():TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF timeout");

    /* ��MSCC�ظ�SYSCFG����ʧ�� */
    NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER);


    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    /* syscfg����ʧ����Ҫ�ָ�֮ǰ�Ľ��뼼�������ȼ� */
    pstPrePrioRatList = NAS_MMC_GetPrePrioRatList_SysCfg();

    NAS_MML_SetMsSysCfgPrioRatList(pstPrePrioRatList);
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */


    /* ֪ͨ�ϲ�״̬��SYSCFG״̬�����н��,syscfg����ʧ�� */
    NAS_MMC_SndSysCfgRslt(VOS_FALSE, VOS_FALSE, NAS_MMC_IsNeedAttachPs_SysCfg(), pstPrePrioRatList);

    /* �˳�SYSCFG״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasSysCfgCnf_SYSCFG_WaitWasSysCfgCnf
 ��������  : ��NAS_MMC_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF״̬�յ�WAS��RRMM_SYS_CFG_CNF��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - �յ�WAS��RRMM_SYS_CFG_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ɹ�
             VOS_FALSE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 4.��    ��   : 2015��2��26��
   ��    ��   : w00167002
   �޸�����   : DTS2015021604972:��SYSCFG�������MMA����ATTACH���̡�MMC�Ѿ��˳�
                 SYSCFG״̬����������������������ʱ�����PS��׼��ATTACH��������LTE��
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvWasSysCfgCnf_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstSysCfgMsg          = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg           = VOS_NULL_PTR;
    RRMM_SYS_CFG_CNF_STRU              *pstSysCfgCnf          = VOS_NULL_PTR;
    VOS_UINT32                          ulNeedSyscfgPlmnSrch;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRat;

    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList;
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    /* ֹͣ�ȴ�WAS��SYSCFG�ظ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF);

    /* ��syscfg����ʧ�ܣ����д����ӡ���˳�SYSCFG״̬�� */
    pstSysCfgCnf          = (RRMM_SYS_CFG_CNF_STRU *)pstMsg;
    if ( RRMM_SYS_CFG_RESULT_FAILURE == pstSysCfgCnf->ulResult)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvWasSysCfgCnf_SysCfg_WaitWasSysCfgCnf:ERROR:SYSCFG SET FAIL!");

        /* ��MSCC�ظ�SYSCFG����ʧ����Ϣ */
        NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER);

        /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
        /* syscfg����ʧ����Ҫ�ָ�֮ǰ�Ľ��뼼�������ȼ� */
        pstPrePrioRatList = NAS_MMC_GetPrePrioRatList_SysCfg();

        NAS_MML_SetMsSysCfgPrioRatList(pstPrePrioRatList);
        /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */



        /* ֪ͨ�ϲ�״̬��SYSCFG״̬�����н����syscfg����ʧ�ܣ�����Ҫ���� */
        NAS_MMC_SndSysCfgRslt(VOS_FALSE, VOS_FALSE, NAS_MMC_IsNeedAttachPs_SysCfg(), pstPrePrioRatList);

        /* �˳�SYSCFG״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��ȡsyscfg״̬�������Ϣ��Ϣ */
    pstEntryMsg           = NAS_MMC_GetCurrEntryMsg();

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg          = (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* ��ȡ��Ҫ����SYSCFG����һ������ģ */
    enNextRat             = NAS_MMC_GetNextSettingRat_SysCfg();
    if (NAS_MML_NET_RAT_TYPE_BUTT != enNextRat)
    {
        NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);
        return VOS_TRUE;
    }

    /* ���������ģʽ��SYSCFG����,����SYSCFG����������Ϣ */
    NAS_MMC_SaveUserSyscfgInfo_SysCfg(pstSysCfgMsg);

    /* SYSCFG������ɺ󣬽���С����Ϣ�ĸ��� */
    NAS_MMC_UpdateCellInfo_SysCfg();

    /* ��MSCC�ظ�SYSCFG���óɹ�ԭ�� */
    NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS);

    /* ����Ҫ����������������SYSCFG������ڲ�������Ϣ */
    ulNeedSyscfgPlmnSrch = NAS_MMC_GetPlmnSearchFlag_SysCfg();


    pstPrePrioRatList = NAS_MMC_GetPrePrioRatList_SysCfg();

    /* ֪ͨ�ϲ�״̬��SYSCFG״̬�����н����syscfg���óɹ� */
    NAS_MMC_SndSysCfgRslt(VOS_TRUE, ulNeedSyscfgPlmnSrch, NAS_MMC_IsNeedAttachPs_SysCfg(), pstPrePrioRatList);

    /* �˳�SYSCFG״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_RcvGasSuspendInd_SysCfg_WaitGasSysCfgCnf
��������  : ��NAS_MMC_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF״̬�յ�WAS��
             RRMM_SUSPEND_IND��Ϣ�Ĵ���
�������  : ulEventType - ��Ϣ����
            pstMsg      - �յ�RRMM_SUSPEND_IND��Ϣ���׵�ַ
�������  : ��
�� �� ֵ  : VOS_TRUE  - �ɹ�
            VOS_FALSE - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��7��11��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSuspendInd_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������ظ�����ʧ�� */
    NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasSysCfgCnfExpired_SYSCFG_WaitWasSysCfgCnf
 ��������  : ��NAS_MMC_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF״̬�յ�������ʱ��
             TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF��ʱ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - �յ�TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF��ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ɹ�
             VOS_FALSE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��15��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSysCfgCnfExpired_SysCfg_WaitWasSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList;
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    /* ��ӡ��ʱ����ʱ�쳣LOG */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvWasSysCfgCnfExpired_SysCfg_WaitWasSysCfgCnf():TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF timeout");

    /* ��MSCC�ظ�SYSCFG����ʧ�� */
    NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER);

    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    /* syscfg����ʧ����Ҫ�ָ�֮ǰ�Ľ��뼼�������ȼ� */
    pstPrePrioRatList = NAS_MMC_GetPrePrioRatList_SysCfg();

    NAS_MML_SetMsSysCfgPrioRatList(pstPrePrioRatList);
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */


    /* ֪ͨ�ϲ�״̬��SYSCFG״̬�����н��,syscfg����ʧ�� */
    NAS_MMC_SndSysCfgRslt(VOS_FALSE, VOS_FALSE, NAS_MMC_IsNeedAttachPs_SysCfg(), pstPrePrioRatList);

    /* �˳�SYSCFG״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmSignalingStatusInd_SysCfg_WaitRrcConnRelInd
 ��������  : ��NAS_MMC_SYSCFG_STA_WAIT_RRC_CONN_REL_IND״̬�յ�
             MMCGMM_SIGNALING_STATUS_IND��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - �յ�MMCGMM_SIGNALING_STATUS_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ɹ�
             VOS_FALSE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��30��
   ��    ��   : w00167002
   �޸�����   : DTS2011113001438:���Ӳ����ڣ�ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG����
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmSignalingStatusInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg    = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRat;
    VOS_UINT32                          ulRrcConnExistFlag;

    /* ��ȡSYSCFG״̬���������Ϣ��Ϣ */
    pstEntryMsg         = NAS_MMC_GetCurrEntryMsg();

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg        = (MSCC_MMC_SYS_CFG_SET_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* ������������ͷ�,ͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);


    /* ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG���� */
    enNextRat           = NAS_MMC_GetNextSettingRat_SysCfg();
    NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);

    return VOS_TRUE;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_RcvMmConnInfoInd_SysCfg_WaitRrcConnRelInd
��������  : ��NAS_MMC_SYSCFG_STA_WAIT_RRC_CONN_REL_IND״̬�յ�
            MMCMM_RR_CONN_INFO_IND��Ϣ�Ĵ���
�������  : ulEventType - ��Ϣ����
            pstMsg      - �յ�MMCMM_RR_CONN_INFO_IND��Ϣ���׵�ַ
�������  : ��
�� �� ֵ  : VOS_TRUE  - �ɹ�
            VOS_FALSE - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��7��11��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���

2.��    ��   : 2011��11��30��
  ��    ��   : w00167002
  �޸�����   : DTS2011113001438:���Ӳ����ڣ�ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG����
3.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmConnInfoInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRat;
    VOS_UINT32                          ulRrcConnExistFlag;

    /* ��ȡSYSCFG״̬���������Ϣ��Ϣ */
    pstEntryMsg         = NAS_MMC_GetCurrEntryMsg();

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg        = (MSCC_MMC_SYS_CFG_SET_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* ������������ͷ�,ͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);


    /* ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG���� */
    enNextRat           = NAS_MMC_GetNextSettingRat_SysCfg();
    NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);

    return VOS_TRUE;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_RcvMmcMmRelInd_SysCfg_WaitRrcConnRelInd
��������  : ��NAS_MMC_SYSCFG_STA_WAIT_RRC_CONN_REL_IND״̬�յ�
            MMCMM_RR_REL_IND��Ϣ�Ĵ���
�������  : ulEventType - ��Ϣ����
            pstMsg      - �յ�MMCMM_RR_REL_IND��Ϣ���׵�ַ
�������  : ��
�� �� ֵ  : VOS_TRUE  - �ɹ�
            VOS_FALSE - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��7��11��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���

2.��    ��   : 2011��11��30��
  ��    ��   : w00167002
  �޸�����   : DTS2011113001438:���Ӳ����ڣ�ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG����
3.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmcMmRelInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRat;
    VOS_UINT32                          ulRrcConnExistFlag;

    /* ��ȡSYSCFG״̬���������Ϣ��Ϣ */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg = (MSCC_MMC_SYS_CFG_SET_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* ������������ͷ�,ͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);


    /* ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG���� */
    enNextRat           = NAS_MMC_GetNextSettingRat_SysCfg();
    NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);

    return VOS_TRUE;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_RcvRrMmRelInd_SysCfg_WaitRrcConnRelInd
��������  : ��NAS_MMC_SYSCFG_STA_WAIT_RRC_CONN_REL_IND״̬�յ�
            RRMM_REL_IND��Ϣ�Ĵ���
�������  : ulEventType - ��Ϣ����
            pstMsg      - �յ�RRMM_REL_IND��Ϣ���׵�ַ
�������  : ��
�� �� ֵ  : VOS_TRUE  - �ɹ�
            VOS_FALSE - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��7��11��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���

2.��    ��   : 2011��11��30��
  ��    ��   : w00167002
  �޸�����   : DTS2011113001438:���Ӳ����ڣ�ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG����
3.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvRrMmRelInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRat;
    VOS_UINT32                          ulRrcConnExistFlag;

    /* ��ȡSYSCFG״̬���������Ϣ��Ϣ */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg = (MSCC_MMC_SYS_CFG_SET_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag  = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* ������������ͷ�,ͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);


    /* ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG���� */
    enNextRat           = NAS_MMC_GetNextSettingRat_SysCfg();
    NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);

    return VOS_TRUE;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_RcvGmmTbfRelInd_SysCfg_WaitRrcConnRelInd
��������  : ��NAS_MMC_SYSCFG_STA_WAIT_RRC_CONN_REL_IND״̬�յ�
            MMCGMM_TBF_REL_IND��Ϣ�Ĵ���
�������  : ulEventType - ��Ϣ����
            pstMsg      - �յ�MMCGMM_TBF_REL_IND��Ϣ���׵�ַ
�������  : ��
�� �� ֵ  : VOS_TRUE  - �ɹ�
            VOS_FALSE - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��7��11��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���

2.��    ��   : 2011��11��30��
  ��    ��   : w00167002
  �޸�����   : DTS2011113001438:���Ӳ����ڣ�ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG����
3.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmTbfRelInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRat;
    VOS_UINT32                          ulRrcConnExistFlag;

    /* ��ȡSYSCFG״̬���������Ϣ��Ϣ */
    pstEntryMsg        = NAS_MMC_GetCurrEntryMsg();

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg       = (MSCC_MMC_SYS_CFG_SET_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    /* �ж����������Ƿ��Ѿ�����ͷ� */
    ulRrcConnExistFlag = NAS_MML_IsRrcConnExist();

    if ( VOS_TRUE == ulRrcConnExistFlag )
    {
        /* ��������δ�ͷ���ɣ������ȴ����������ͷ���Ϣ */
        return VOS_TRUE;
    }

    /* ������������ͷ�,ͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);


    /* ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG���� */
    enNextRat           = NAS_MMC_GetNextSettingRat_SysCfg();
    NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);


    return VOS_TRUE;
}


/*****************************************************************************
�� �� ��  : NAS_MMC_RcvWasSuspendInd_SysCfg_WaitRrcConnRelInd
��������  : ��NAS_MMC_SYSCFG_STA_WAIT_RRC_CONN_REL_IND״̬�յ�WAS��
            RRMM_SUSPEND_IND��Ϣ�Ĵ���
�������  : ulEventType - ��Ϣ����
            pstMsg      - �յ�RRMM_SUSPEND_IND��Ϣ���׵�ַ
�������  : ��
�� �� ֵ  : VOS_TRUE  - �ɹ�
            VOS_FALSE - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��7��11��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasSuspendInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������ظ�����ʧ�� */
    NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);

    return VOS_TRUE;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_RcvGasSuspendInd_SysCfg_WaitRrcConnRelInd
��������  : ��NAS_MMC_SYSCFG_STA_WAIT_RRC_CONN_REL_IND״̬�յ�GAS��
            RRMM_SUSPEND_IND��Ϣ�Ĵ���
�������  : ulEventType - ��Ϣ����
            pstMsg      - �յ�RRMM_SUSPEND_IND��Ϣ���׵�ַ
�������  : ��
�� �� ֵ  : VOS_TRUE  - �ɹ�
            VOS_FALSE - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��7��11��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasSuspendInd_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������ظ�����ʧ�� */
    NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, UEPS_PID_GAS);

    return VOS_TRUE;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_RcvTiWaitRrcConnRelExpired_SysCfg_WaitRrcConnRelInd
��������  : ��NAS_MMC_SYSCFG_STA_WAIT_RRC_CONN_REL_IND״̬�յ�������ʱ��
            TI_NAS_MMC_WAIT_RRC_CONN_REL��ʱ��Ϣ�Ĵ���
�������  : ulEventType - ��Ϣ����
            pstMsg      - �յ�TI_NAS_MMC_WAIT_RRC_CONN_REL��ʱ��Ϣ���׵�ַ
�������  : ��
�� �� ֵ  : VOS_TRUE  - �ɹ�
            VOS_FALSE - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��7��11��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���

2.��    ��   : 2011��11��30��
  ��    ��   : w00167002
  �޸�����   : DTS2011113001438:���Ӳ����ڣ�ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG����
3.��    ��   : 2011��12��1��
  ��    ��   : w00176964
  �޸�����   : GUNAS V7R1 PhaseIV �׶ε���
4.��    ��   : 2013��3��30��
  ��    ��   : l00167671
  �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitRrcConnRelExpired_SysCfg_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRat;

    /* ��ӡ�쳣��Ϣ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitRrcConnRelExpired_SysCfg_WaitRrcConnRelInd:TI_NAS_MMC_WAIT_RRC_CONN_REL timeout");

    /* ��ȡSYSCFG״̬���������Ϣ��Ϣ */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg = (MSCC_MMC_SYS_CFG_SET_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    enNextRat    = NAS_MML_NET_RAT_TYPE_BUTT;

    /* ����������Ӵ���, �����������ͷ�����,������������� */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_SysCfg())
    {
        NAS_MMC_SetRelRequestFlag_SysCfg(VOS_FALSE);

        /* ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG���� */
        enNextRat  = NAS_MMC_GetNextSettingRat_SysCfg();

        /* ��ǰ����ģʽ����SYSCFG���� */
        NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);

        /* ��MM��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        return VOS_TRUE;
    }

    /* ���������ͷ�����MM��GMM�����������ȴ������ͷŶ�ʱ�� */
    NAS_MMC_SetRelRequestFlag_SysCfg(VOS_TRUE);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
    NAS_MMC_SndMmRelReq();
    NAS_MMC_SndGmmRelReq();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSysCfgCnf_SYSCFG_WaitLmmSysCfgCnf
 ��������  : ��NAS_MMC_SYSCFG_STA_WAIT_LMM_SYSCFG_CNF״̬�յ�LMM��MMC_LMM_SYS_CFG_CNF��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - �յ�LMM��ID_LMM_MMC_SYS_CFG_CNF��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ɹ�
             VOS_FALSE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��30��
   ��    ��   : w00167002
   �޸�����   : DTS2011113001438:Lģ�п��������һ��ģ����Ϊ���һ��ģ����
                 ����SYSCFG�������Ĵ�������
 3.��    ��   : 2012��8��13��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 4.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
 5.��    ��   : 2015��2��26��
   ��    ��   : w00167002
   �޸�����   : DTS2015021604972:��SYSCFG�������MMA����ATTACH���̡�MMC�Ѿ��˳�
                 SYSCFG״̬����������������������ʱ�����PS��׼��ATTACH��������LTE��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysCfgCnf_SysCfg_WaitLmmSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstSysCfgMsg          = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg           = VOS_NULL_PTR;
    LMM_MMC_SYS_CFG_CNF_STRU           *pstSysCfgCnf          = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRat;
    VOS_UINT32                          ulNeedSyscfgPlmnSrch;

    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList;
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    /* ֹͣ�ȴ�LMM��SYSCFG�ظ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYSCFG_CNF);

    /* ��syscfg����ʧ�ܣ����д����ӡ���˳�SYSCFG״̬�� */
    pstSysCfgCnf          = (LMM_MMC_SYS_CFG_CNF_STRU *)pstMsg;
    if ( MMC_LMM_FAIL == pstSysCfgCnf->ulRst)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSysCfgCnf_SysCfg_WaitLmmSysCfgCnf:ERROR:SYSCFG SET FAIL!");

        /* ��MSCC�ظ�SYSCFG����ʧ����Ϣ */
        NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER);

        /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
        /* syscfg����ʧ����Ҫ�ָ�֮ǰ�Ľ��뼼�������ȼ� */
        pstPrePrioRatList = NAS_MMC_GetPrePrioRatList_SysCfg();

        NAS_MML_SetMsSysCfgPrioRatList(pstPrePrioRatList);
        /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */



        /* ֪ͨ�ϲ�״̬��SYSCFG״̬�����н����syscfg����ʧ�ܣ�����Ҫ���� */
        NAS_MMC_SndSysCfgRslt(VOS_FALSE, VOS_FALSE, NAS_MMC_IsNeedAttachPs_SysCfg(), pstPrePrioRatList);

        /* �˳�SYSCFG״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��ȡsyscfg״̬�������Ϣ��Ϣ */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg = (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/


    /* δ���SYSCFG������ģʽ���ã������ģ����SYSCFG�������� */
    enNextRat             = NAS_MMC_GetNextSettingRat_SysCfg();
    if (NAS_MML_NET_RAT_TYPE_BUTT != enNextRat)
    {
        NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);

        return VOS_TRUE;
    }

    /* ���������ģʽ��SYSCFG����,����SYSCFG����������Ϣ */
    NAS_MMC_SaveUserSyscfgInfo_SysCfg(pstSysCfgMsg);

    /* SYSCFG������ɺ󣬽���С����Ϣ�ĸ��� */
    NAS_MMC_UpdateCellInfo_SysCfg();

    /* ��MSCC�ظ�SYSCFG���óɹ�ԭ�� */
    NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS);

    /* ����Ҫ����������������SYSCFG������ڲ�������Ϣ */
    ulNeedSyscfgPlmnSrch  = NAS_MMC_GetPlmnSearchFlag_SysCfg();

    pstPrePrioRatList = NAS_MMC_GetPrePrioRatList_SysCfg();

    /* ֪ͨ�ϲ�״̬��SYSCFG״̬�����н����syscfg���óɹ� */
    NAS_MMC_SndSysCfgRslt(VOS_TRUE, ulNeedSyscfgPlmnSrch, NAS_MMC_IsNeedAttachPs_SysCfg(), pstPrePrioRatList);

    /* �˳�SYSCFG״̬�� */
    NAS_MMC_FSM_QuitFsmL2();


    return VOS_TRUE;
}

/*****************************************************************************
�� �� ��  : NAS_MMC_RcvLmmSuspendInd_SysCfg_WaitLmmSysCfgCnf
��������  : ��NAS_MMC_SYSCFG_STA_WAIT_LMM_SYSCFG_CNF״̬�յ�LMM��
             ID_LMM_MMC_SUSPEND_IND��Ϣ�Ĵ���
�������  : ulEventType - ��Ϣ����
            pstMsg      - �յ�ID_LMM_MMC_SUSPEND_IND��Ϣ���׵�ַ
�������  : ��
�� �� ֵ  : VOS_TRUE  - �ɹ�
            VOS_FALSE - ʧ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2011��7��11��
  ��    ��   : w00167002
  �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_SysCfg_WaitLmmSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��LMM�ظ�����ʧ�� */
    NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSysCfgCnfExpired_SYSCFG_WaitLmmSysCfgCnf
 ��������  : ��NAS_MMC_SYSCFG_STA_WAIT_LMM_SYSCFG_CNF״̬�յ�������ʱ��
             TI_NAS_MMC_WAIT_LMM_SYSCFG_CNF��ʱ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - �յ�TI_NAS_MMC_WAIT_LMM_SYSCFG_CNF��ʱ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ɹ�
             VOS_FALSE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��8��15��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSysCfgCnfExpired_SysCfg_WaitLmmSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrePrioRatList;
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    /* ��ӡ��ʱ����ʱ�쳣LOG */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSysCfgCnfExpired_SysCfg_WaitLmmSysCfgCnf():TI_NAS_MMC_WAIT_LMM_SYSCFG_CNF timeout");

    /* ��MSCC�ظ�SYSCFG����ʧ�� */
    NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_OTHER);

    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    /* syscfg����ʧ����Ҫ�ָ�֮ǰ�Ľ��뼼�������ȼ� */
    pstPrePrioRatList = NAS_MMC_GetPrePrioRatList_SysCfg();

    NAS_MML_SetMsSysCfgPrioRatList(pstPrePrioRatList);
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */


    /* ֪ͨ�ϲ�״̬��SYSCFG״̬�����н��,syscfg����ʧ�� */
    NAS_MMC_SndSysCfgRslt(VOS_FALSE, VOS_FALSE, NAS_MMC_IsNeedAttachPs_SysCfg(), pstPrePrioRatList);

    /* �˳�SYSCFG״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmMmcStatusInd_SYSCFG_WaitEpsConnRelInd
 ��������  : ��NAS_MMC_SYSCFG_STA_WAIT_EPS_CONN_REL_IND״̬�յ�
             L ��ID_LMM_MMC_STATUS_IND�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - �յ�ID_LMM_MMC_STATUS_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ɹ�
             VOS_FALSE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��30��
   ��    ��   : w00167002
   �޸�����   : DTS2011113001438: ���Ӳ����ڣ�ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG����
 3.��    ��   : 2012��5��16��
   ��    ��   : z00161729
   �޸�����   : V7R1C50 GUL BG�����޸�,������״̬�����ñ���һ�£�
                �յ�MMC_LMM_CONNECTED_DATAָʾֻ����ҵ����ڲ������������Ӵ���
 4.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmMmcStatusInd_SysCfg_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg       = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg        = VOS_NULL_PTR;
    LMM_MMC_STATUS_IND_STRU            *pstLmmStatusIndMsg = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRat;

    pstLmmStatusIndMsg = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    /* ��ȡSYSCFG״̬���������Ϣ��Ϣ */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg = (MSCC_MMC_SYS_CFG_SET_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    if ( VOS_FALSE == pstLmmStatusIndMsg->bitOpConnState)
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_SysCfg_WaitEpsConnRelInd:bitOpConnState IS VOS_FALSE");
        return VOS_TRUE;
    }

    /* ����LMM������״̬ */
    switch (pstLmmStatusIndMsg->ulConnState)
    {
        case MMC_LMM_CONN_ESTING:
        case MMC_LMM_CONNECTED_SIG:
            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
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

    /* ��������������ӣ�������ȴ� */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ������ͷŶ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);


    /* ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG���� */
    enNextRat           = NAS_MMC_GetNextSettingRat_SysCfg();
    NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitEpsConnRelIndExpired_SYSCFG_WaitEpsConnRelInd
 ��������  : ��NAS_MMC_SYSCFG_STA_WAIT_EPS_CONN_REL_IND״̬�յ�������ʱ��
             TI_NAS_MMC_WAIT_EPS_CONN_REL_IND��ʱ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - �յ�TI_NAS_MMC_WAIT_EPS_CONN_REL_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ɹ�
             VOS_FALSE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��11��30��
   ��    ��   : w00167002
   �޸�����   : DTS2011113001438:���Ӳ����ڣ�ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG����
 3.��    ��   : 2011��12��1��
   ��    ��   : w00176964
   �޸�����   : GUNAS V7R1 PhaseIV �׶ε���
 4.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitEpsConnRelIndExpired_SysCfg_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg = VOS_NULL_PTR;
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNextRat;

    /* ��ӡ�쳣��Ϣ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitEpsConnRelIndExpired_SysCfg_WaitEpsConnRelInd:TI_NAS_MMC_WAIT_EPS_CONN_REL_IND timeout");

    /* ��ȡSYSCFG״̬���������Ϣ��Ϣ */
    pstEntryMsg  = NAS_MMC_GetCurrEntryMsg();

    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    pstSysCfgMsg = (MSCC_MMC_SYS_CFG_SET_REQ_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
    enNextRat    = NAS_MML_NET_RAT_TYPE_BUTT;

    /* ����������Ӵ���, �����������ͷ�����,������������� */
    if (VOS_TRUE == NAS_MMC_GetRelRequestFlag_SysCfg())
    {
        NAS_MMC_SetRelRequestFlag_SysCfg(VOS_FALSE);


        /* ȡ��Ŀ��ģ�Ľ��뼼����������SYSCFG���� */
        enNextRat           = NAS_MMC_GetNextSettingRat_SysCfg();
        NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);

       /* ��ǰ����ģʽ����SYSCFG���� */
       NAS_MMC_SetRatModeSysCfgReq_SysCfg(enNextRat, pstSysCfgMsg);

       /* ��MM��GMM��������ָʾ */
       NAS_MMC_SndGmmPlmnSchInit();
       NAS_MMC_SndMmPlmnSchInit();

       return VOS_TRUE;
    }

    /* ���������ͷ�����LMM�����������ȴ������ͷŶ�ʱ�� */
    NAS_MMC_SetRelRequestFlag_SysCfg(VOS_TRUE);
    NAS_MMC_SndLmmRelReq();
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);


    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmSuspendInd_SYSCFG_WaitEpsConnRelInd
 ��������  : ��NAS_MMC_SYSCFG_STA_WAIT_EPS_CONN_REL_IND״̬�յ�ID_LMM_MMC_SUSPEND_IND
             ��Ϣ�Ĵ���
 �������  : ulEventType - ��Ϣ����
             pstMsg      - �յ�ID_LMM_MMC_SUSPEND_IND��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �ɹ�
             VOS_FALSE - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��11��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_SysCfg_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��LMM�ظ�����ʧ�� */
    NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);

    return VOS_TRUE;
}

#endif



/*****************************************************************************
 �� �� ��  : NAS_MMC_SysCfg_IsPlmnSelectionNeeded
 ��������  : �ж�SYSCFG�����Ƿ���Ҫ��������
 �������  : pstSysCfgSetParm:�û����õ�SYSCFG����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:SYSCFG������Ҫ����
              VOS_FALSE:SYSCFG���ò���Ҫ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��2��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsPlmnSelectionNeeded_SysCfg(
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
)
{
    VOS_UINT32                          ulFlg;

    /* �ж�SYSCFG�Խ������ȼ��������Ƿ���Ҫ��������:
       ����ǰ�Ľ��뼼��������Ϊ��Ч������Ҫ���� */
    ulFlg           = NAS_MMC_IsCurrentRatSetted_SysCfg(pstSysCfgSetParm);
    if ( VOS_FALSE  == ulFlg )
    {
        return VOS_TRUE;
    }

    /* �ж�SYSCFG�Խ�BAND�������Ƿ���Ҫ�������� */
    ulFlg           = NAS_MMC_IsCurrentBandSetted_SysCfg(pstSysCfgSetParm);
    if ( VOS_FALSE  == ulFlg )
    {
        return VOS_TRUE;
    }

    /* �ж�SYSCFG��ROAM���Ե������Ƿ���Ҫ�������� */
    ulFlg           = NAS_MMC_CheckRoamSettingPlmnSelection_SysCfg(pstSysCfgSetParm);
    if ( VOS_TRUE  == ulFlg )
    {
        return VOS_TRUE;
    }

    /* SYSCFG���ò���Ҫ�������� */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_BandSetNeedPlmnSearch
 ��������  : �ж�SYSCFG��Ƶ�������Ƿ��·�������
 �������  : pstUserSetBand:�û�����֧�ֵ�Ƶ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��ǰƵ����Ч
             VOS_FALSE:��ǰƵ����Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��2��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��3��7��
   ��    ��   : w00176964
   �޸�����   : DTS201212345678:����BAND6��BAND19��֧��

 3.��    ��   : 2012��8��6��
   ��    ��   : w00167002
   �޸�����   : V7R1C50_GUTL_PhaseII:��פ����TDģʽ�£�����Ƶ����Ϣ�϶��Ǳ�֧�ֵģ�ֱ�ӷ���VOS_-
                 TRUE
 4.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsCurrentBandSetted_SysCfg(
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
)
{
    NAS_MML_MS_BAND_INFO_STRU          *pstBandInfo         = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_LTE)
    LTE_BAND_STRU                       stCurrentLteBand;
    LTE_BAND_STRU                       stSetLteBand;
#endif
    VOS_UINT32                          ulCurrentWcdmaBand;
    VOS_UINT32                          ulSetWcdmaBand;
    VOS_UINT32                          ulCurrentGsmBand;
    VOS_UINT32                          ulSetGsmBand;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;

    /* ȡ�õ�ǰ�Ľ��뼼������ */
    enCurrNetRatType                    = NAS_MML_GetCurrNetRatType();

    /* ��ȡ��ǰ��Ƶ����Ϣ */
    pstBandInfo                         = NAS_MML_GetCurrBandInfo();
#if (FEATURE_ON == FEATURE_LTE)

    PS_MEM_SET(&stCurrentLteBand, 0, sizeof(LTE_BAND_STRU));
    PS_MEM_SET(&stSetLteBand, 0, sizeof(LTE_BAND_STRU));

    /* ��ȡ��ǰ��LTE��Ƶ�� */
    PS_MEM_CPY( &(stCurrentLteBand),
                &(pstBandInfo->stLteBand),
                sizeof(LTE_BAND_STRU) );

#endif

    /* ��ȡ��ǰ��WCDMA��Ƶ�� */
    ulCurrentWcdmaBand                  = pstBandInfo->unWcdmaBand.ulBand;

    /* ��ȡ��ǰ��GSM��Ƶ�� */
    ulCurrentGsmBand                    = pstBandInfo->unGsmBand.ulBand;

#if (FEATURE_ON == FEATURE_LTE)

    /* ��ȡ��ǰ�û�SYSCFG���õ�LTE��Ƶ�� */
    PS_MEM_CPY( &(stSetLteBand),
                &(pstSysCfgSetParm->stBand.stLteBand),
                sizeof(LTE_BAND_STRU) );
#endif

    /* ��ȡ��ǰ�û�SYSCFG���õ�WCDMA��Ƶ�� */
    ulSetWcdmaBand                      = pstSysCfgSetParm->stBand.unWcdmaBand.ulBand;

    /* ��ȡ��ǰ�û�SYSCFG���õ�GSM��Ƶ�� */
    ulSetGsmBand                        = pstSysCfgSetParm->stBand.unGsmBand.ulBand;

#if (FEATURE_ON == FEATURE_LTE)

    /* ��ǰLTE��Ƶ�����û�����Ƶ���� */
    if ( (0 != (stCurrentLteBand.aulLteBand[0] & stSetLteBand.aulLteBand[0]))
      || (0 != (stCurrentLteBand.aulLteBand[1] & stSetLteBand.aulLteBand[1])) )
    {
        /* ��ǰLTEƵ�����û����õ���ӦƵ���У�������ǰƵ����Ч */
        return VOS_TRUE;
    }
#endif


    /* ��פ����TDģʽ�£�����Ƶ����Ϣ�϶��Ǳ�֧�ֵģ�ֱ�ӷ���VOS_TRUE */
    if ( (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurrNetRatType) )
    {
        return VOS_TRUE;
    }


    /* ��ǰGUƵ�����û�����Ƶ���� */
    if ( (0 != (ulCurrentGsmBand & ulSetGsmBand))
      || (0 != (ulCurrentWcdmaBand & ulSetWcdmaBand)) )
    {
        /* ��ǰGUƵ�����û����õ���ӦƵ���У�������ǰƵ����Ч */
        return VOS_TRUE;
    }

    /* ��ǰƵ���ڲ��û����õ���ӦƵ���У�������ǰƵ����Ч */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CheckCurrentRatValidity
 ��������  : �ж�SYSCFG���뼼�����ȼ��ĸı��Ƿ���Ҫ��������
 �������  : pstPlmnRatPrio:�û����õĽ��뼼�����ȼ�
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��ǰ����ģʽ���û�SYSCFG��������
             VOS_FALSE:��ǰ����ģʽ�����û�SYSCFG��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��2��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsCurrentRatSetted_SysCfg(
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
)
{
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8     *pstRatPrio = VOS_NULL_PTR;              /* �������ȼ����б� index��ʾ���ȼ�����,0��ߣ�2��� */
    VOS_UINT8                           ucRatNum;                               /* ��ǰ֧�ֵĽ��뼼������  */
    VOS_UINT32                          i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;

    /* ȡ�õ�ǰ�Ľ���ģʽ */
    enCurrRat       = NAS_MML_GetCurrNetRatType();

    /* ȡ���û���ǰ���õĽ������ȸ��� */
    ucRatNum        = pstSysCfgSetParm->stRatPrioList.ucRatNum;

    /* ȡ���û���ǰ���õĽ������ȼ��б� */
    pstRatPrio      = pstSysCfgSetParm->stRatPrioList.aucRatPrio;

    /* �����ǰģ���û����õĽ������ȼ��б������TRUE,���򷵻�FALSE */
    for ( i = 0 ; i < ucRatNum; i++ )
    {
        if ( enCurrRat == pstRatPrio[i] )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CheckRoamSettingPlmnSelection_SysCfg��
 ��������  : �ж�SYSCFG�������õĸı��Ƿ���Ҫ��������
 �������  : pstPlmnRatPrio:�û����õĽ��뼼�����ȼ�
 �������  : ��
 �� �� ֵ  : VOS_TRUE:SYSCFG������������Ҫ����
             VOS_FALSE:SYSCFG���������ò���Ҫ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��8��2��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32  NAS_MMC_CheckRoamSettingPlmnSelection_SysCfg(
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
)
{
    NAS_MML_ROAM_CFG_INFO_STRU         *pstRoamCfg          = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo      = VOS_NULL_PTR;
    NAS_MSCC_PIF_ROAM_CAPABILITY_ENUM_UINT8   enSysCfgSetRoamCapability;

    /* ȡ���û���ǰSYSCFG���õ�����������Ϣ */
    enSysCfgSetRoamCapability = pstSysCfgSetParm->enRoamCapability;

    /* ��ȡ��ǰ������������Ϣ */
    pstRoamCfg                = NAS_MML_GetRoamCfg();

    /* ��������û�д�ʱ������Ҫ���� */
    if (VOS_FALSE == pstRoamCfg->ucRoamFeatureFlg)
    {
        return VOS_FALSE;
    }

    /* ����ȡֵû�иı���߸ı䵫��Ӱ�������б�Χ������Ҫ���� */
    if ( (pstRoamCfg->enRoamCapability == enSysCfgSetRoamCapability)
      || (NAS_MSCC_PIF_ROAM_UNCHANGE         == enSysCfgSetRoamCapability) )
    {
        return VOS_FALSE;
    }

    /* �������ιرգ��������εĸı䲻��Ҫ���� */
    if ( ( (NAS_MML_ROAM_NATION_OFF_INTERNATION_ON  == pstRoamCfg->enRoamCapability)
        && (NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_OFF  == enSysCfgSetRoamCapability) )
      || ( (NAS_MML_ROAM_NATION_OFF_INTERNATION_OFF == pstRoamCfg->enRoamCapability)
        && (NAS_MSCC_PIF_ROAM_NATION_OFF_INTERNATION_ON   == enSysCfgSetRoamCapability) ) )
    {
        return VOS_FALSE;
    }

    /* ����ǰ���粻�������Σ�����Ҫ����������Ҫ��EPLMN�в��������ε���������� */
    if ( VOS_FALSE == NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg(pstSysCfgSetParm) )
    {
        /* ȡ�õ�ǰ��EPLMN��ַ��Ϣ */
        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();

        /* ��EPLMN�еĲ�׼�����ε�����ȥ�� */
        NAS_MML_RemoveRoamPlmnInSrchList( &pstEquPlmnInfo->ucEquPlmnNum,
                                           pstEquPlmnInfo->astEquPlmnAddr );
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_Save3Gpp2RatPrio_Syscfg
 ��������  : �����û�SYSCFG���õ�3GPP2�б�
 �������  : pstPrioRatList---�û�SYSCFG���õ�RAT PRIO LIST
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��29��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_Save3Gpp2RatPrio_Syscfg(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
)
{
    VOS_UINT8                           ucRatNum;
    VOS_UINT32                          i;
    NAS_MML_3GPP2_RAT_PRIO_STRU        *pst3Gpp2RatPrioList = VOS_NULL_PTR;

    pst3Gpp2RatPrioList     = NAS_MML_GetMs3Gpp2PrioRatList();
    ucRatNum                = 0;

    PS_MEM_SET(NAS_MML_GetMs3Gpp2PrioRatList()->aucRatPrio,
               NAS_MML_3GPP2_RAT_TYPE_BUTT,
               sizeof(NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8) * NAS_MML_MAX_3GPP2_RAT_NUM);

    for (i = 0; i < NAS_MML_MIN(NAS_MSCC_PIF_MAX_RAT_NUM,pstPrioRatList->ucRatNum); i++)
    {
        if (VOS_TRUE == NAS_MML_Is3Gpp2Rat(pstPrioRatList->aucRatPrio[i]))
        {
            /* ��MSCC���ݹ�����3GPP2����ת��ΪMML��ʽ */
            NAS_MMC_ConvertMsccRatTypeToMml3GPP2RatType(pstPrioRatList->aucRatPrio[i],
                                                       &(pst3Gpp2RatPrioList->aucRatPrio[ucRatNum]));


            ucRatNum ++;
        }
    }

    NAS_MML_GetMmlCtx()->stMsCfgInfo.stMsSysCfgInfo.st3Gpp2RatList.ucRatNum = ucRatNum;

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveUserSyscfgInfo
 ��������  : �����û����õ�SYSCFG��Ϣ
 �������  : MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg:�û����õ�SYSCFG��Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��10��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_VOID  NAS_MMC_SaveUserSyscfgInfo_SysCfg(
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
)
{
    NAS_MML_MS_BAND_INFO_STRU           stMsBand;
    NAS_MML_PLMN_RAT_PRIO_STRU          stPrioRatList;

    PS_MEM_SET(&stMsBand, 0, sizeof(NAS_MML_MS_BAND_INFO_STRU));
    PS_MEM_SET(&stPrioRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    /* ��ֵ�û����õ�������Ϣ */
    NAS_MML_SetRoamCapability(pstSysCfgMsg->enRoamCapability);

    /* ��ֵ�û����õ�Ƶ����Ϣ */
    PS_MEM_CPY( &(stMsBand.stLteBand),
                &(pstSysCfgMsg->stBand.stLteBand),
                sizeof(LTE_BAND_STRU) );
    stMsBand.unWcdmaBand.ulBand = pstSysCfgMsg->stBand.unWcdmaBand.ulBand;
    stMsBand.unGsmBand.ulBand   = pstSysCfgMsg->stBand.unGsmBand.ulBand;
    NAS_MML_SetMsSysCfgBand( &stMsBand );

    /* ��ֵ�û����õĽ��뼼�����ȼ� */
    PS_MEM_CPY( &stPrioRatList,
                &(pstSysCfgMsg->stRatPrioList),
                sizeof(NAS_MML_PLMN_RAT_PRIO_STRU) );
    NAS_MML_SetMsSysCfgPrioRatList(&stPrioRatList);

    /* save 3gpp2 rat prio list */
    NAS_MMC_Save3Gpp2RatPrio_Syscfg(&stPrioRatList);

    return ;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateCellInfo_SysCfg
 ��������  : SYSCFG������ɺ����CELL INFO��Ϣ�ĸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��10��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_UpdateCellInfo_SysCfg(VOS_VOID)
{
    NAS_MML_MS_CFG_INFO_STRU           *pstMsCfgInfo        = VOS_NULL_PTR;
    NAS_MML_MS_SYS_CFG_INFO_STRU       *pstCurrMsSysCfgInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_CELL_INFO_STRU        *pstCampCellInfo     = VOS_NULL_PTR;
    VOS_UINT32                          ulGsmOnly;
    VOS_UINT32                          ulWcdmaOnly;


    /* ��ȡ��ǰ��SYSCFG������Ϣ */
    pstMsCfgInfo                        = NAS_MML_GetMsCfgInfo();
    pstCurrMsSysCfgInfo                 = &(pstMsCfgInfo->stMsSysCfgInfo);

    /* ����SYSCFG����Ϊ��ģʱ,MSCCģ�����µ�ǰϵͳģʽ�������Ǵ�MMC�ϱ�SYSTEMINFOʱ���£����
       ����Ϊ��ģ��Ҫ���MMCά����С����Ϣ���Է�ֹ�ٴ�����Ϊ˫ģʱMMC���ϱ�SYSTEMINFO */
    ulGsmOnly       = NAS_MML_IsGsmOnlyMode( &(pstCurrMsSysCfgInfo->stPrioRatList) );
    ulWcdmaOnly     = NAS_MML_IsWcdmaOnlyMode( &(pstCurrMsSysCfgInfo->stPrioRatList) );
    if ( (VOS_TRUE == ulGsmOnly)
      || (VOS_TRUE == ulWcdmaOnly) )
    {
        pstCampCellInfo = NAS_MML_GetCampCellInfo();
        pstCampCellInfo->ucCellNum = 0;
    }

    return ;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SetRatModeSysCfgReq_SysCfg
 ��������  : ���ݽ���ģʽ�ж�Ӧ���ĸ�ģ����syscfg��������syscfg״̬����״̬Ǩ��
 �������  : enCurrRat    - ����ģʽ
             pstSysCfgMsg - syscfg��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��20��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SetRatModeSysCfgReq_SysCfg(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat,
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgMsg
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
)
{
    /* ���ݽ���ģʽ������SYSCFG������ */
    switch ( enCurrRat )
    {

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ��Lģ�·�SYSCFG�������� */
            NAS_MMC_SndLmmSyscfgReq(pstSysCfgMsg);
            NAS_MMC_AddSysCfgIndex_SysCfg();

            /* ����SYSCFG״̬������״̬��Ǩ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_SYSCFG_STA_WAIT_LMM_SYSCFG_CNF);

            /* �����ȴ��ظ���ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYSCFG_CNF, TI_NAS_MMC_WAIT_LMM_SYSCFG_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ��Wģ�·�SYSCFG�������� */
            NAS_MMC_SndAsSyscfgReq(pstSysCfgMsg, WUEPS_PID_WRR);
            NAS_MMC_AddSysCfgIndex_SysCfg();

            /* ����SYSCFG״̬������״̬��Ǩ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF);

            /* �����ȴ��ظ���ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF, TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ��Gģ�·�SYSCFG�������� */
            NAS_MMC_SndAsSyscfgReq(pstSysCfgMsg, UEPS_PID_GAS);
            NAS_MMC_AddSysCfgIndex_SysCfg();

            /* ����SYSCFG״̬������״̬��Ǩ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_SYSCFG_STA_WAIT_GAS_SYSCFG_CNF);

            /* �����ȴ��ظ���ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF, TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF_LEN);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SetRatModeSysCfgReq_SysCfg():Invalid net rat type");
            break;
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetDestModeRat_SysCfg
 ��������  : �ж�SYSCFG�����Ƿ���Ҫ��������
 �������  : pstSysCfgSetParm:�û����õ�SYSCFG����
 �������  : ��
 �� �� ֵ  : NAS_MML_NET_RAT_TYPE_ENUM_UINT8:SYSCFG���õ�Ŀ��ģ�Ľ��뼼��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��30��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetDestModeRat_SysCfg(
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
)
{
    VOS_UINT32                          ulFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestModeRat;

    /* ����ǰ�Ľ��뼼��������Ϊ��Ч����Ŀ��ģΪSYSCFG���õ����ȵĽ��뼼�� */
    ulFlg             = NAS_MMC_IsCurrentRatSetted_SysCfg(pstSysCfgSetParm);
    if ( VOS_FALSE    == ulFlg )
    {
        /* �����뼼���ĸı䵼��������Ŀ��ģΪSYSCFG���õ����ȵĽ��뼼�� */
        enDestModeRat = pstSysCfgSetParm->stRatPrioList.aucRatPrio[0];

        return enDestModeRat;
    }

    /* ����Ŀ��ģΪ��ǰ�Ľ��뼼�����ͣ�����ǰ�Ľ��뼼��ΪBUTT���ͣ�
       ��SYSCFG���õ��Ⱥ�˳��ΪL->W->G */
    enDestModeRat     = NAS_MML_GetCurrNetRatType();

    return enDestModeRat;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedAttachPs_SysCfg
 ��������  : �ж�SYSCFG����MMA�Ƿ���Ҫ����ATTACH
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ����ATTACH
             VOS_FALSE:����Ҫ����ATTACH
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��27��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedAttachPs_SysCfg(VOS_VOID)
{
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstSysCfgMsg    = VOS_NULL_PTR;
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;

    /* ��ȡSYSCFG״̬���������Ϣ��Ϣ */
    pstEntryMsg        = NAS_MMC_GetCurrEntryMsg();
    pstSysCfgMsg       = (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

    if (VOS_TRUE == pstSysCfgMsg->ucIsNeedAttachPs)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


