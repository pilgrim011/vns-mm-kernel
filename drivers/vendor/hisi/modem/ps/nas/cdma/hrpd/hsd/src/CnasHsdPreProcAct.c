/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdPreProcAct.c
  �� �� ��   : ����
  ��    ��   : g00256031
  ��������   : 2014��12��10��
  ��������   : EVDO SDԤ�����¼�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��10��
    ��    ��   : g00256031
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasHsdPreProcAct.h"
#include  "CnasHsdComFunc.h"
#include  "CnasHsdMntn.h"
#include  "CnasHsdSysAcqStrategy.h"
#include  "CnasHsdAvoidStrategy.h"
#include  "CnasHsdSndInternalMsg.h"
#include  "CnasHsdFsmMainTbl.h"
#include  "CnasHsdSndCas.h"
#include  "CnasHsdFsmSysAcqTbl.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"

#include  "CnasHsdSndMscc.h"

#include "CnasHsdSndHsm.h"

#include "CnasHsdSndRrm.h"
#include  "cas_hrpd_routeupdate_nas_pif.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_PRE_PROC_ACT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvSliceReverseProtectTimerExpired_PreProc
 ��������  : �յ�avoid list timer��ʱ����ʱ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��08��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvSliceReverseProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCurSlice;
    VOS_UINT32                          ulRunSliceNum;
    VOS_UINT8                           ucIndex;
    CNAS_HSD_AVOID_FREQ_INFO_STRU      *pstAvoidFreqInfo;

    /* ��ȡ��ǰϵͳ��slice */
    ulCurSlice = CNAS_HSD_GetSystemSlice();

    /* ����avoid�б������е�Ƶ��ĵ���slice */
    for (ucIndex = 0; ucIndex < CNAS_HSD_MAX_AVOID_FREQ_NUM; ucIndex++)
    {
        pstAvoidFreqInfo = CNAS_HSD_GetAvoidItemFromAvoidList(ucIndex);

        if (CNAS_HSD_AVOID_ITEM_UNUSED == pstAvoidFreqInfo->enUsedFlag)
        {
            continue;
        }

        if (ulCurSlice < pstAvoidFreqInfo->ulStartSlice)
        {
            /* ���Ƿ�ת���� */
            ulRunSliceNum = CNAS_HSD_MAX_SLICE_VALUE - pstAvoidFreqInfo->ulStartSlice + ulCurSlice + 1;
        }
        else
        {
            ulRunSliceNum = ulCurSlice - pstAvoidFreqInfo->ulStartSlice;
        }

        /* ����Ѿ����е�slice��Ŀ���ڵ��ڵ��ڵ�slice��Ŀ����avoidƵ���б����޳���Ƶ�� */
        if (ulRunSliceNum >= pstAvoidFreqInfo->ulExpiredSliceNum)
        {
            CNAS_HSD_DeleteItemFromAvoidList(ucIndex);
            CNAS_HSD_DecreaseAvoidFreqUsedNum();
        }
    }

    /* ���avoid list��Ϊ�գ���������slice��ʱ�� */
    if (0 != CNAS_HSD_GetAvoidFreqListUsedNum())
    {
        CNAS_HSD_StartTimer(TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER,
                            TI_CNAS_HSD_SLICE_REVERSE_PROTECT_TIMER_LEN);
    }

    CNAS_HSD_LogAvoidFreqList(CNAS_HSD_GetAvoidFreqListAddr());

    return VOS_TRUE;
}

/* ����Ϣ�ڵ���15������HRUP���ͣ�����Network lostԭ��ֵ�У�������Ҫ����Ӧ�޸� */
#if 0
/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvTchAssignTimeoutInd_PreProc
 ��������  : �յ�ID_CAS_CNAS_HRPD_TCH_ASSIGN_TIMEOUT_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTchAssignTimeoutInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_REACQ_FALG_ENUM_UINT32     enReAcqFlag;

    enReAcqFlag = CNAS_HSD_NOT_NEED_REACQ;

    /* avoidģ�鴦�� */
    CNAS_HSD_ProcAvoidEventInTchAssignTimeoutInd(&enReAcqFlag);

    /* �Ƿ���Ҫ�������� */
    if (CNAS_HSD_NEED_REACQ == enReAcqFlag)
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}
#endif
/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcHrpd1XSysAssn
 ��������  : �������жϴ���
 �������  : enHsdATStatus          - ��ǰϵͳ״̬
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : ��1x�������жϽӿڵ������������pstHrpdSys

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcHrpd1XSysAssn(CNAS_HSD_AT_STATUS_ENUM_UINT32 enHsdATStatus)
{
    CNAS_HSD_AT_STATUS_ENUM_UINT32      enLastStatus;
    CNAS_HSD_ASSN_RLST_ENUM_UINT32      enAssnRlst;
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys;

    enLastStatus = CNAS_HSD_GetATStatus();

    /* ϵͳ�ӷ�IDLE̬��IDLE̬����Ҫ�ж� */
    if ((CNAS_HSD_AT_STATUS_ENUM_IDLE == enLastStatus)
     || (CNAS_HSD_AT_STATUS_ENUM_IDLE != enHsdATStatus))
    {
        return;
    }

    if (CNAS_HSD_HRPD_SYSTEM_AVAILABLE != CNAS_HSD_GetHrpdSysStatus())
    {
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_ProcHrpd1XSysAssn: Current state is incorrect.");

        /* �쳣������ֱ�ӷ��� */
        return ;
    }

    /* ����Ϊ��Ƶ�¾Ͳ����ж� */
    if (VOS_TRUE == CNAS_HSD_GetFreqLockMode())
    {
        return;
    }

    pstHrpdSys = CNAS_HSD_GetCampedHrpdSystemInfo();

    /*  ��ȡ��ǰ1X��HRPD�Ĺ�����ϵ */
    enAssnRlst = CNAS_HSD_CheckHrpdFreqAssnWith1X(pstHrpdSys);

    /* ��ǰû���������Ƶ�� */
    if (CNAS_HSD_NO_ASSN_FREQ == enAssnRlst)
    {
        CNAS_HSD_ClearHrpdSysInfo();

        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

        CNAS_HSD_SndCasOocNtf();

        /* �ϱ�����ʧ��,֪ͨMSCC�л���LTE */
        CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);

        return;
    }

    /* �й���Ƶ�㣬���͵�ǰ��HRPDϵͳ������� */
    if (CNAS_HSD_NO_ASSN_WITH_HRPD == enAssnRlst)
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasStatusInd_PreProc
 ��������  : �յ�ID_HSM_HSD_CAS_STATUS_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_HSD_CAS_STATUS_IND_STRU        *pstCasStatusInd;
    CNAS_HSD_AT_STATUS_ENUM_UINT32      enHsdATStatus;

    pstCasStatusInd = (HSM_HSD_CAS_STATUS_IND_STRU*)pstMsg;

    enHsdATStatus   = CNAS_HSD_TransferCasStatusTypeToHsdFormat(pstCasStatusInd->enCasStatus);

    /* avoidģ�鴦�� */
    CNAS_HSD_ProcAvoidEventInCasStatusInd(enHsdATStatus);

    CNAS_HSD_ProcHrpd1XSysAssn(enHsdATStatus);

    /* ����AT��ǰ״̬ */
    CNAS_HSD_SaveATStatus(enHsdATStatus);


    CNAS_HSD_SndMsccHrpdCasStatusInd((HSD_MSCC_HRPD_CAS_STATUS_ENUM_UINT16)enHsdATStatus);


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvPsStatusInd_PreProc
 ��������  : ��NORF�����½��յ�RRM��״̬��Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��07��16��
    ��    ��   : x00306642
    �޸�����   : ���ƹ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPsStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_RRM_STATUS_IND);

    CNAS_HSD_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_HRPD_NETWORK_SEARCH);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvPsStatusInd_PreProc
 ��������  : ��NORF�����½��յ�RRM��״̬��Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_Rcv1xSysChgInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_1X_SYS_CHANGE_IND_STRU    *pst1xSysIndMsg;
    CNAS_HSD_1X_SYSTEM_INFO_STRU       *pstHsd1xSysInfo;
    CNAS_PRL_1X_SYSTEM_STRU             st1xSrcSys;

    pst1xSysIndMsg = (MSCC_HSD_1X_SYS_CHANGE_IND_STRU *)pstMsg;

    pstHsd1xSysInfo = CNAS_HSD_Get1xSystemInfo();

    /* 1X�����ɹ�֮������ΪAVAILABLE״̬�����浱ǰ��ϵͳ��Ϣ */
    if (VOS_TRUE == pst1xSysIndMsg->ucIs1xAvail)
    {
        if (CNAS_HSD_1X_SYSTEM_AVAILABLE == pstHsd1xSysInfo->enStatus)
        {
            st1xSrcSys.usSid               = pst1xSysIndMsg->st1xSysInfo.usSid;
            st1xSrcSys.usNid               = pst1xSysIndMsg->st1xSysInfo.usNid;
            st1xSrcSys.stFreq.enBandClass  = pst1xSysIndMsg->st1xSysInfo.usBandClass;
            st1xSrcSys.stFreq.usChannel    = pst1xSysIndMsg->st1xSysInfo.usChannel;

            /* �����µ�1X����ϵͳ��֮ǰ��ͬ�򲻽��к������� */
            if (VOS_TRUE == CNAS_PRL_Is1xSysMatched(&st1xSrcSys,
                                                    &(pstHsd1xSysInfo->st1xSys)))
            {
                return VOS_TRUE;
            }
        }

        pstHsd1xSysInfo->enStatus = CNAS_HSD_1X_SYSTEM_AVAILABLE;

        /* �����Ƿ���Ҫ����ǰ��1Xϵͳ��һ�µ���� */
        pstHsd1xSysInfo->st1xSys.stFreq.enBandClass = pst1xSysIndMsg->st1xSysInfo.usBandClass;
        pstHsd1xSysInfo->st1xSys.stFreq.usChannel   = pst1xSysIndMsg->st1xSysInfo.usChannel;

        pstHsd1xSysInfo->st1xSys.usNid              = pst1xSysIndMsg->st1xSysInfo.usNid;
        pstHsd1xSysInfo->st1xSys.usSid              = pst1xSysIndMsg->st1xSysInfo.usSid;
    }
    else if (CNAS_HSD_1X_SYSTEM_AVAILABLE != pstHsd1xSysInfo->enStatus)
    {
        pstHsd1xSysInfo->enStatus = CNAS_HSD_1X_SYSTEM_UNAVAILABLE;

        PS_MEM_SET(pstHsd1xSysInfo, 0, sizeof(CNAS_HSD_1X_SYSTEM_INFO_STRU));
    }
    else
    {
        ;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccQryHrpdSysInfoReq_PreProc
 ��������  : �յ�ID_MSCC_HSD_QRY_HRPD_SYS_INFO_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccQryHrpdSysInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU *pHrpdSysInfo;
    VOS_UINT8                            ucHrpdSysNum;
    MSCC_HSD_HRPD_SYS_INFO_STRU          astHrpdSysInfoList[MSCC_HSD_BG_HRPD_MAX_SYS_NUM];

    PS_MEM_SET(astHrpdSysInfoList,
               0,
               sizeof(MSCC_HSD_HRPD_SYS_INFO_STRU) * MSCC_HSD_BG_HRPD_MAX_SYS_NUM);

    pHrpdSysInfo    =   (MSCC_HSD_QRY_HRPD_SYS_INFO_REQ_STRU *)pstMsg;

    if (MSCC_HSD_SYS_TYPE_CDMA2000_AI == pHrpdSysInfo->enSysType)
    {
        CNAS_HSD_QRY_HrpdSysInfo(pHrpdSysInfo,
                                 &ucHrpdSysNum,
                                 astHrpdSysInfoList,
                                 CNAS_HSD_GetPriClassWithTypeAI);

    }
    else if (MSCC_HSD_SYS_TYPE_CDMA2000_HRPD== pHrpdSysInfo->enSysType)
    {
        CNAS_HSD_QRY_HrpdSysInfo(pHrpdSysInfo,
                                 &ucHrpdSysNum,
                                 astHrpdSysInfoList,
                                 CNAS_HSD_GetPriClassWithTypeHRPD);
    }
    else
    {
        ucHrpdSysNum = 0;
    }

    CNAS_HSD_SndMsccHrpdSysInfoCnf(ucHrpdSysNum, astHrpdSysInfoList);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccDisableLte_PreProc
 ��������  : �յ�ID_MSCC_HSD_DISABLE_LTE_NTF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDisableLteNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* HSD��CAS͸��DISABLE��Ϣ */
    CNAS_HSD_SndCasDisableLteNtf();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccBgSearchReq_PreProc
 ��������  : �յ�ID_MSCC_HSD_BG_SEARCH_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccBgSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_BSR_LTE_CNF_STRU      stBsrLteCnf;
    MSCC_HSD_BG_SEARCH_REQ_STRU        *pstBgSearchReq = VOS_NULL_PTR;

    PS_MEM_SET(&stBsrLteCnf, 0, sizeof(stBsrLteCnf));

    pstBgSearchReq = (MSCC_HSD_BG_SEARCH_REQ_STRU *)pstMsg;

    /* HSD��IDLE̬����enRatModeΪLTEʱ��HSD�Ÿ�CAS͸��bsr lte req��Ϣ */
    if ((CNAS_HSD_AT_STATUS_ENUM_IDLE == CNAS_HSD_GetATStatus()))
    {
        if (VOS_RATMODE_LTE == pstBgSearchReq->enRatMode)
        {
            CNAS_HSD_SndCasBsrLteReq();
        }
        else
        {
            /* ֱ�ӻظ�FAIL */
            stBsrLteCnf.ucRslt  = CNAS_CAS_HRPD_BSR_RSLT_FAIL;
            CNAS_HSD_SndMsccBgSearchCnf(&stBsrLteCnf);
        }
    }
    else
    {
        /* ֱ�ӻظ�abort */
        stBsrLteCnf.ucRslt  = CNAS_CAS_HRPD_BSR_RSLT_ABORT;
        CNAS_HSD_SndMsccBgSearchCnf(&stBsrLteCnf);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccStopBgSearchReq_PreProc
 ��������  : �յ�ID_MSCC_HSD_STOP_BG_SEARCH_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccStopBgSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* HSD��CAS͸��stop bg search��Ϣ */
    CNAS_HSD_SndCasStopBsrLteReq();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasBsrLteCnf_PreProc
 ��������  : �յ�ID_CAS_CNAS_HRPD_BSR_LTE_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasBsrLteCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_BSR_LTE_CNF_STRU      *pstBsrLteCnf;

    pstBsrLteCnf = (CAS_CNAS_HRPD_BSR_LTE_CNF_STRU *)pstMsg;

    CNAS_HSD_SndMsccBgSearchCnf(pstBsrLteCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasFreqListReq_PreProc
 ��������  : �յ�ID_CAS_CNAS_HRPD_FREQ_LIST_QUERY_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��07��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasFreqListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_BSR_FREQ_LIST_QUERY_REQ_STRU             *pstFreqListReq;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          astFreqList[CNAS_CAS_HRPD_MAX_FREQ_NUM];
    VOS_UINT32                                              ulFreqNum;

    PS_MEM_SET(astFreqList, 0, sizeof(astFreqList));

    pstFreqListReq = (CAS_CNAS_HRPD_BSR_FREQ_LIST_QUERY_REQ_STRU *)pstMsg;

    if (PS_TRUE == pstFreqListReq->enFirstQueryFlag)
    {
        /* ���տ�����������Ƶ���б� */
        CNAS_HSD_BuildHrpdScanList_CasReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON);
    }

    ulFreqNum = CNAS_HSD_GetScanListSameLevelFreq(CNAS_CAS_HRPD_MAX_FREQ_NUM, astFreqList);

    if (0 == ulFreqNum)
    {
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvCasFreqListReq_PreProc: ulFreqNum is 0.");
    }

    /* ��CAS����ID_CNAS_CAS_HRPD_FREQ_LIST_QUERY_CNF����ʹ�����Ƶ�����Ϊ0��Ҳ��Ҫ�ظ������� */
    CNAS_HSD_SndCasFreqListCnf(ulFreqNum, astFreqList);

    CNAS_HSD_RefreshScanListIndex((VOS_UINT16)ulFreqNum);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasStopBsrLte_PreProc
 ��������  : �յ�ID_CAS_CNAS_HRPD_STOP_BSR_LTE_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasStopBsrLteCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �յ�CAS�ظ�����Ϣ��ֱ�Ӹ�MSCC�ظ� */
    CNAS_HSD_SndMsccStopBgSearchCnf();

    return VOS_TRUE;
}


VOS_UINT32 CNAS_HSD_RcvCasOhmNotCurrentInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Send indication to HSM */
    CNAS_HSD_SndHsmOhmNotCurrentInd();

    return VOS_TRUE;
}

#ifdef DMT
/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvHsdTestCfgREQ_PreProc
 ��������  : DMT���������õ�ǰslice
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��29��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvHsdTestCfgREQ_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_HSD_TEST_CFG_REQ_STRU     *pstCfgReq = VOS_NULL_PTR;

    pstCfgReq = (CNAS_HSD_HSD_TEST_CFG_REQ_STRU*)pstMsg;

    g_ulHsdCurSlice = pstCfgReq->ulCurSlice;

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccSysCfgSet_PreProc
 ��������  : ͸��MSCC��ϵͳ������Ϣ��CAS
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccSysCfgSet_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_SYS_CFG_REQ_STRU          *pstSysCfgReq = VOS_NULL_PTR;

    pstSysCfgReq = (MSCC_HSD_SYS_CFG_REQ_STRU *)pstMsg;

    CNAS_HSD_SetSysModeType(CNAS_HSD_CheckHybridMode(pstSysCfgReq->ucSuppRatNum, &pstSysCfgReq->aenRatMode[0]));

    /* �����й����Ŷ����¼� */
    CNAS_HSD_ProcessCTCCCustomize();

    CNAS_HSD_SetSysCfgFlag(VOS_TRUE);

    CNAS_HSD_SndCasSysCfgReq(pstSysCfgReq);

    CNAS_HSD_InitOocCtxInfo();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasSysCfgCnf_PreProc
 ��������  : ����CAS��ϵͳ����ȷ����Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasSysCfgCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_SYS_CFG_CNF_STRU     *pstSysCfgCnf = VOS_NULL_PTR;

    pstSysCfgCnf = (CAS_CNAS_HRPD_SYS_CFG_CNF_STRU *)pstMsg;

    CNAS_HSD_SetSysCfgFlag(VOS_FALSE);

    CNAS_HSD_SndMsccSysCfgCnf(pstSysCfgCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasNetworkLostIndProc_PreProc
 ��������  : Ԥ�����ж�ID_CAS_CNAS_HRPD_NETWORK_LOST_IND����avoid����֮���ٽ�״̬������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLostIndProc_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstCasNetworkLostMsg;
    CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU                  *pstNetwkLostSysRec;
    CNAS_HSD_HISTORY_SYS_LIST_STRU                         *pstHistorySys;
    VOS_UINT32                                              ulIsChange;
    CNAS_HSD_SYS_MODE_TYPD_ENUM_UINT32                      enSysMode;

    pstCasNetworkLostMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU*)pstMsg;

    pstHistorySys        = CNAS_HSD_GetHistorySysList();
    pstNetwkLostSysRec   = CNAS_HSD_GetNetwkLostSysRec();
    enSysMode            = CNAS_HSD_GetModeType();

    /* �ǻ��ģʽ�²���signal fade����avoid���� */
    if (CNAS_HSD_SYS_MODE_NONHYBRID == enSysMode)
    {
        return VOS_FALSE;
    }

    /* �ɹ�פ������Ž��д��� */
    if (0 != pstHistorySys->ulTotalNum)
    {
        /* ��no rf��abnormal �ĳ����Ž���avoid���� */
        if ((CAS_CNAS_HRPD_NETWORK_LOST_NO_RF    != pstCasNetworkLostMsg->enNetworkLostReason)
         && (CAS_CNAS_HRPD_NETWORK_LOST_ABNORMAL != pstCasNetworkLostMsg->enNetworkLostReason))
        {
            /* �Ƿ���ͬһϵͳ�϶��� */
            ulIsChange = CNAS_HSD_IsHrpdSysChange(&(pstHistorySys->stCampedHrpdSysInfo[0]),
                                                  &(pstNetwkLostSysRec->stHrpdSys));

            if (VOS_TRUE == ulIsChange)
            {
                PS_MEM_CPY(&(pstNetwkLostSysRec->stHrpdSys),
                       &(pstHistorySys->stCampedHrpdSysInfo[0]),
                       sizeof(CNAS_PRL_HRPD_SYSTEM_STRU));

                pstNetwkLostSysRec->ucNetwkLostCnt = 0x01;

                pstNetwkLostSysRec->ulLastRecSlice = CNAS_HSD_GetSystemSlice();
            }
            else
            {
                CNAS_HSD_AvoidNetwkLostProc(pstNetwkLostSysRec);
            }

        }
    }
    else
    {}

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_AvoidNetwkLostProc
 ��������  : �����������Ƿ���Ҫ����void����
 �������  : pstNetwkLostSysRec         ������¼��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_AvoidNetwkLostProc(
    CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU                  *pstNetwkLostSysRec
)
{
    VOS_UINT32                          ulCurSlice;
    VOS_UINT32                          ulInterSlice;
    VOS_UINT32                          ulMaxInterSlice;

    ulMaxInterSlice     = CNAS_HSD_TIMER_LEN_20_SEC * CNAS_HSD_GetSystemSliceNumOfOneSecond();

    ulCurSlice  = CNAS_HSD_GetSystemSlice();

    if (ulCurSlice < pstNetwkLostSysRec->ulLastRecSlice)
    {
        /* ���Ƿ�ת���� */
        ulInterSlice = CNAS_HSD_MAX_SLICE_VALUE - pstNetwkLostSysRec->ulLastRecSlice + ulCurSlice + 1;
    }
    else
    {
        ulInterSlice = ulCurSlice - pstNetwkLostSysRec->ulLastRecSlice;
    }

    /* ����ʱ�� */
    pstNetwkLostSysRec->ulLastRecSlice = ulCurSlice;

    if (ulInterSlice > ulMaxInterSlice)
    {
        pstNetwkLostSysRec->ucNetwkLostCnt = 0x01;
    }
    else
    {
        pstNetwkLostSysRec->ucNetwkLostCnt++;

        /* ������������3�� */
        if (pstNetwkLostSysRec->ucNetwkLostCnt >= CNAS_HSD_AVOID_NETWORK_LOST_MAX_CNT)
        {
            CNAS_HSD_ProcAvoidEventInNetwkLostInd(&(pstNetwkLostSysRec->stHrpdSys.stFreq));
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccCFreqLockSetNtf_PreProc
 ��������  : �յ�MSCC��������Ƶ����Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccCFreqLockSetNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_CFREQ_LOCK_NTF_STRU       *pstCFreqLockNtf         = VOS_NULL_PTR;
    CNAS_HSD_CFREQ_LOCK_SET_PARA_STRU  *pstCFreqLockSetPara     = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stLockFreq;

    pstCFreqLockNtf = (MSCC_HSD_CFREQ_LOCK_NTF_STRU *)pstMsg;

    /* ���͸�CAS */
    if (VOS_TRUE != CNAS_HSD_SndCasCFreqLockNtf(pstCFreqLockNtf))
    {
        return VOS_TRUE;
    }

    pstCFreqLockSetPara                  = CNAS_HSD_GetFreqLockAddr();

    if (NAS_MSCC_PIF_CFREQ_LOCK_SET_MODE_ENABLE == pstCFreqLockNtf->enFreqLockMode)
    {
        pstCFreqLockSetPara->ucFreqLockMode  = VOS_TRUE;
    }
    else
    {
        pstCFreqLockSetPara->ucFreqLockMode  = VOS_FALSE;
    }
    pstCFreqLockSetPara->usHrpdBandClass = pstCFreqLockNtf->usHrpdBandClass;
    pstCFreqLockSetPara->usHrpdFreq      = pstCFreqLockNtf->usHrpdFreq;
    pstCFreqLockSetPara->usHrpdPn        = pstCFreqLockNtf->usHrpdPn;

    if (VOS_TRUE == pstCFreqLockSetPara->ucFreqLockMode)
    {
        /* ��ǰפ��ϵͳ�Ĳ����뼴����Ƶ������ͬʱ������������ */
        if (CNAS_HSD_HRPD_SYSTEM_AVAILABLE == CNAS_HSD_GetHrpdSysStatus())
        {
            stLockFreq.enBandClass  = pstCFreqLockSetPara->usHrpdBandClass;
            stLockFreq.usChannel    = pstCFreqLockSetPara->usHrpdFreq;

            if (VOS_FALSE == CNAS_PRL_CmpFreqValue(&(CNAS_HSD_GetCampedHrpdSystemInfo()->stFreq), &stLockFreq))
            {
                /* IDLE״̬�´������� */
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

                CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_CFREQ_LOCK, 0, VOS_NULL_PTR);
            }
        }
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvNoRFProtectTimerExpired_PreProc
 ��������  : �յ�NO RF��ʱ����ʱ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��20��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvNoRFProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enScene;

    if (VOS_FALSE == CNAS_HSD_GetHrpdRfAvailFlg())
    {
        enScene = CNAS_HSD_GetNoRfScene();

        if (CNAS_HSD_SYS_ACQ_SCENE_BUTT >= enScene)
        {
            CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_BUTT);

            /* ����L1״̬������INITIAL״̬ */
            CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

            CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
        }
    }

    return VOS_TRUE;
}
#if 0
/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccDataCallStartNtf_PreProc
 ��������  : �յ�MSCC��������ʼ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallStartNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccDataCallEndNtf_PreProc
 ��������  : �յ�MSCC������������Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallEndNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccDataCallSuccNtf_PreProc
 ��������  : �յ�MSCC�������ɹ���Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallSuccNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasSuspendInd_PreProc
 ��������  : �յ�CAS��suspend ind�ı�������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��28��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasSuspendInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_FSM_ID_ENUM_UINT32         enFsmId;
    VOS_UINT32                          ulState;

    enFsmId              = CNAS_HSD_GetCurrFsmId();
    ulState              = CNAS_HSD_GetFsmTopState();

    /* ��SysCfg��Ϣ���͸�CAS��û���ܵ�CAS�Ļظ� */
    if (VOS_TRUE == CNAS_HSD_GetSysCfgFlag())
    {
        CNAS_HSD_SndCasSuspendRsp(CAS_CNAS_HRPD_RSLT_FAIL);

        return VOS_TRUE;
    }
    /* �����ǰ״̬����idle̬���ظ��ɹ�������״̬����������ֻ�ظ�ʧ�ܼ��� */
    if ((CNAS_HSD_FSM_L1_MAIN == enFsmId)
     && (CNAS_HSD_L1_STA_IDLE == ulState))
    {
        CNAS_HSD_SndCasSuspendRsp(CAS_CNAS_HRPD_RSLT_SUCC);

        return VOS_FALSE;
    }
    else
    {
        CNAS_HSD_SndCasSuspendRsp(CAS_CNAS_HRPD_RSLT_FAIL);

        return VOS_TRUE;
    }
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccHdrCsqSetReq_PreProc
 ��������  : �յ�MSCC��HDR CSQ SET REQ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccHdrCsqSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_HDR_CSQ_SET_REQ_STRU      *psrHdrCsqSetReq;

    psrHdrCsqSetReq = (MSCC_HSD_HDR_CSQ_SET_REQ_STRU*)pstMsg;

    /* ��set req ���ͽocas */
    if (VOS_ERR == CNAS_HSD_SndCasHdrCsqSetReq(psrHdrCsqSetReq))
    {

        /* �oMSCC �ظ�SET ʧ�� */
        CNAS_HSD_SndMsccHdrCsqSetCnf(NAS_MSCC_PIF_CDMACSQ_SET_RESULT_FAIL);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasHdrCsqSetCnf_PreProc
 ��������  : �յ�cas��HDR CSQ SET CNF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasHdrCsqSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_SET_SIGNAL_QUALITY_CNF_STRU              *psrHdrCsqSetCnf;

    psrHdrCsqSetCnf = (CAS_CNAS_HRPD_SET_SIGNAL_QUALITY_CNF_STRU*)pstMsg;

    /* �oMSCC �ظ�SET CNF */
    CNAS_HSD_SndMsccHdrCsqSetCnf(psrHdrCsqSetCnf->enRslt);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccHdrCsqQualityInd_PreProc
 ��������  : �յ�cas��HDR CSQ QUAL IND�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccHdrCsqQualityInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_SIGNAL_QUALITY_IND_STRU              *psrHdrCsqInd;

    psrHdrCsqInd = (CAS_CNAS_HRPD_SIGNAL_QUALITY_IND_STRU*)pstMsg;

    /* �oMSCC ����HDR CSQ IND*/
    CNAS_HSD_SndMsccHdrCsqQualityInd(psrHdrCsqInd->sHrpdRssi,
                                     psrHdrCsqInd->sHrpdSinr,
                                     psrHdrCsqInd->sHrpdEcIo);

    return VOS_TRUE;
}


/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



