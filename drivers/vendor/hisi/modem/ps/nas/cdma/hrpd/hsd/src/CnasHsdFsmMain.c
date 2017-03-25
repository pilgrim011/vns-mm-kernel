/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdFsmMain.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��12��12��
  ��������   : HRPD L1��״̬�����յ����¼�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasHsdFsmMain.h"
#include  "CnasHsdFsmMainTbl.h"
#include  "CnasHsdCtx.h"
#include  "CnasMntn.h"
#include  "CnasHsdComFunc.h"
#include  "CnasHsdSndMscc.h"
#include  "CnasHsdSndCas.h"
#include  "CnasPrlApi.h"
#include  "CnasCcb.h"
#include  "CnasHsdFsmSysAcq.h"
#include  "CnasTimerMgmt.h"
#include  "CnasHsdSysAcqStrategy.h"
#include  "CnasHsdAvoidStrategy.h"
#include  "cas_hrpd_overheadmsg_nas_pif.h"
#include  "CnasHsdSndHsm.h"
#include  "CnasHsdSndInternalMsg.h"

#include  "CnasHsdSndRrm.h"

#include  "NasOmInterface.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                        PS_FILE_ID_CNAS_HSD_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvStartReq_Null
 ��������  : ������null״̬�յ����������¼�
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��03��
   ��    ��   : h00300778
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvStartReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����L2����״̬�� */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_SWITCH_ON);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvSwitchOnRsltCnf_Null
 ��������  : �յ�������������ɹ�Ǩ�Ƶ�CNAS_HSD_L1_STA_INACTIVE״̬��
             ʧ�ܱ���CNAS_HSD_L1_STA_NULL״̬
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��12��
   ��    ��   : h00300778
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvSwitchOnRsltCnf_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU                    *pstSwitchOnMsg;

    pstSwitchOnMsg = (CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU *)pstMsg;

    /* �յ�������������ɹ�Ǩ�Ƶ�CNAS_HSD_L1_STA_INACTIVE״̬ */
    if (CNAS_HSD_SWITCH_ON_RESULT_SUCCESS == pstSwitchOnMsg->enRslt)
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

        /* ֪ͨMSCC�����ɹ� */
        CNAS_HSD_SndMsccStartCnf(HSD_MSCC_START_RESULT_SUCC);
    }
    /* ʧ�ܱ���CNAS_HSD_L1_STA_NULL״̬���յ��ػ�����ʱ��ȻҪ��HSM/HLU/CAS���ػ� */
    else
    {
        /* ֪ͨMSCC����ʧ�� */
        CNAS_HSD_SndMsccStartCnf(HSD_MSCC_START_RESULT_FAIL);

        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvSwitchOnRsltCnf_Deactive:switch on fail");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvPowerOffReq_Null
 ��������  : ������null״̬�յ��ػ������¼�
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��12��
   ��    ��   : h00300778
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��06��23��
   ��    ��   : z00316370
   �޸�����   : ����˳��������NULL״̬Ҳ��Ҫ��ػ�״̬��

*****************************************************************************/
VOS_UINT32  CNAS_HSD_RcvPowerOffReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����L2�ػ�״̬�� */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_POWER_OFF);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvPowerOffReq_L1Main
 ��������  : �յ�ID_MMA_HSD_POWER_OFF_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPowerOffReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����L2�ػ�״̬�� */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_POWER_OFF);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvPowerOffReq_Initial
 ��������  : ������IDLE��OCC״̬�յ�L2 power off�ػ�ȷ���¼�
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
   1.��    ��   : 2014��12��03��
     ��    ��   : h00300778
     �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPowerOffRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣHSD���ж�ʱ�� */
    CNAS_StopAllTimerWithSpecifiedPid(UEPS_PID_HSD);

    /* ����ʱ�ж��Ƿ����ʼ��PRL */

    /* ֪ͨMSCC�ػ���� */
    CNAS_HSD_SndMsccPowerOffCnf();

    /* ��ʼ��HSDģ��CTX */
    CNAS_HSD_InitCtx(CNAS_HSD_INIT_CTX_POWEROFF);

    /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_NULL */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_NULL);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvSysAcqReq_Inactive
 ��������  : INACTIVE״̬�յ�ID_MSCC_HSD_SYSTEM_ACQUIRE_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��04��07��
    ��    ��   : z00316370
    �޸�����   : �������������ж�

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvSysAcqReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU   *pstSysAcqReq;
    CNAS_HSD_HIGHPRIORITY_STRU         *pstHighPri;

    /* �޿������޿�ģʽ�ر���ֱ�ӷ�������ʧ�� */
    if (CNAS_CCB_CARD_STATUS_ABSENT == CNAS_CCB_GetCsimCardStatus())
    {
        if (VOS_FALSE == (CNAS_HSD_GetTestConfig()->ucNoCardModeCfgFlg))
        {
            CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);

            return VOS_TRUE;
        }
    }

    pstSysAcqReq    = (MSCC_HSD_SYSTEM_ACQUIRE_REQ_STRU *)pstMsg;

    if (MSCC_HSD_ACQUIRE_REASON_POWER_UP == pstSysAcqReq->enReason)
    {
        CNAS_HSD_StartSysAcq_Inactive(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON);
    }
    else if (MSCC_HSD_ACQUIRE_REASON_HIGH_PRIORITY == pstSysAcqReq->enReason)
    {
        pstHighPri = CNAS_HSD_GetHighPriorityFreqAddr();

        /* ��ʼ�������ȼ�����Ƶ����Ϣ */
        CNAS_HSD_InitHighPriorityFreq(pstHighPri);

        /* �������ȼ�Ƶ����Ϣ���浽�������� */
        pstHighPri->ucFreqNum = CNAS_MIN(pstSysAcqReq->ucFreqNum, CNAS_HSD_MAX_PREF_SUBNET_NUM);

        PS_MEM_CPY(pstHighPri->astFreqInfo,
                   pstSysAcqReq->astFreqInfo,
                   pstHighPri->ucFreqNum * sizeof(CNAS_HSD_SYSTEM_ACQUIRE_FREQ_INFO_STRU));

        /* ��ʼ�����ȼ����� */
        CNAS_HSD_StartSysAcq_Inactive(CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY);
    }
    else if (MSCC_HSD_ACQUIRE_REASON_OTHER == pstSysAcqReq->enReason)
    {
        /* MSCC�����OTHER��HSD����LOST���� */
        CNAS_HSD_StartSysAcq_Inactive(CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER);
    }
    else
    {
        ;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvInternalSysAcqReq_Initial
 ��������  : INACTIVE״̬�յ�ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvInternalSysAcqReq_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SndCasBeginSessionNotify();

    /* ����L2 System Acquire״̬�� */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_SYS_ACQ);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvSysAcqRsltCnf_Initial_Succ
 ��������  : initial״̬�յ�ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF��Ϣ�Ĵ���
 �������  : pstSysAcqRslt

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��20��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_Succ(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
)
{
    /* �����pilot search�����������֪ͨ��CAS,�����л�inactive̬�󷵻� */
    if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndCasPilotSearchSuccNtf();

        /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_INACTIVE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

        return;
    }

    /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_IDLE */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_IDLE);

    /* �������������ɹ� */
    if ((CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON     == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER    == pstSysAcqRslt->enCurAcqScene))
    {
        CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);
    }

    /* �����DATA CALL����������������MSCC�ظ����������ɹ���Ϣ */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);
    }

    /* �ϱ������ɹ� */
    CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

    /* ��ʼ��OOC��������Ϣ */
    CNAS_HSD_InitOocCtxInfo();

    /* ֹͣ����OOC�¶�ʱ��,��Ҫֹͣ��?*/
    CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_TIMER);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvSysAcqRsltCnf_Initial_Aborted
 ��������  : initial״̬�յ�ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF��Ϣ�Ĵ���
 �������  : pstSysAcqRslt

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��20��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_Aborted(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
)
{
    /* ������������ */
    if ((CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON     == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER    == pstSysAcqRslt->enCurAcqScene))
    {
        CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    /* �����pilot search�����������֪ͨ��CAS,�����л�inactive̬�󷵻� */
    if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndCasPilotSearchFailNtf();

        CNAS_HSD_SndHsmPilotSearchFailNtf();

        /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_INACTIVE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

        return;
    }

    /* �����DATA CALL����������������MSCC�ظ���Ϣ */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_OOC */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

    /* ������Ҫ���������������ϱ���MSCC�޷��� */
    if (CNAS_HSD_SYS_ACQ_FAIL_ACT_ACQ_IMMEDIATE != pstSysAcqRslt->enImmediateSysAcq)
    {
        /* �ϱ�������� */
        CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_ABORTED);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvSysAcqRsltCnf_Initial_NoRF
 ��������  : initial״̬�յ�ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF��Ϣ�Ĵ���
 �������  : pstSysAcqRslt

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��20��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_NoRF(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
)
{
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8    enCur1xState;
    /* ����NORF�ĳ��� */
    CNAS_HSD_SetNoRfScene(pstSysAcqRslt->enCurAcqScene);

    /* ��RRM����ע��,RF���ú�RRM��֪ͨXSD */
    /* ��Ҫ�ж�������� ������ڵȴ�RRM��status ind ����Ҫ������Ϣ��������ʱ�� */
    CNAS_HSD_SndRrmRegisterInd(RRM_PS_TASK_TYPE_HRPD_NETWORK_SEARCH);

    /* ����������ʱ�� */
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_RRM_STATUS_IND, TI_CNAS_HSD_WAIT_RRM_STATUS_IND_LEN);

    /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_OOC */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

    /* �����ʱ��INIT ̬ ˵��1X����������RF available֮���տ������� */
    enCur1xState = CNAS_CCB_GetCasState();

    CNAS_HSD_SetNoRf1XUeStatus(enCur1xState);


    if (VOS_TRUE == CNAS_HSD_GetHrpdRfAvailFlg())
    {
        /* �ϱ�MSCC NO RF��Ϣ */
        CNAS_HSD_SndMsccRfAvailInd(VOS_FALSE);

        /* ���õ�ǰRF���ñ��Ϊ:RF������ */
        CNAS_HSD_SetHrpdRfAvailFlg(VOS_FALSE);
    }

    /* ������������ʧ�� */
    if ((CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON     == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER    == pstSysAcqRslt->enCurAcqScene))
    {
        CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);
    }

    /* �����pilot search�����������֪ͨ��CAS,�����л�inactive̬�󷵻� */
    if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndCasPilotSearchFailNtf();

        CNAS_HSD_SndHsmPilotSearchFailNtf();

        /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_INACTIVE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

        return;
    }

    /* ������ض��򳡾�����ӵ�ǰפ��Ƶ�㵽AvoidƵ���� */
    if (CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION == pstSysAcqRslt->enCurAcqScene)
    {
        /* �ó���NORF���ն������� */
        CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST);
    }

    /* �����DATA CALL����������������MSCC�ظ�ʧ����Ϣ */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == pstSysAcqRslt->enCurAcqScene)
    {
        /* �ó���NORF���ն������� */
        CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST);

        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_NO_RF);
    }

    /* �ϱ�����ʧ�� */
    CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_NO_RF);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvSysAcqRsltCnf_Initial_Fail
 ��������  : initial״̬�յ�ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF��Ϣ�Ĵ���
 �������  : pstSysAcqRslt

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��20��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_Fail(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
)
{
    /* ������������ʧ�� */
    if ((CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON     == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == pstSysAcqRslt->enCurAcqScene)
     || (CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER    == pstSysAcqRslt->enCurAcqScene))
    {
        CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);
    }

    /* ������ض��򳡾�����ӵ�ǰפ��Ƶ�㵽AvoidƵ���� */
    if (CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_ProcAvoidEventInRedirection(&(CNAS_HSD_GetHsdCtxAddr()->stSysAcqCtrl.stSyncFreq));

        /* �ض���ʧ�ܣ��������� */
        pstSysAcqRslt->enImmediateSysAcq = CNAS_HSD_SYS_ACQ_FAIL_ACT_ACQ_IMMEDIATE;
    }

    /* �����DATA CALL ����������������MSCC�ظ�ʧ����Ϣ */
    if (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);
    }

    /* �����pilot search�����������֪ͨ��CAS,�����л�inactive̬�󷵻� */
    if (CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH == pstSysAcqRslt->enCurAcqScene)
    {
        CNAS_HSD_SndCasPilotSearchFailNtf();

        CNAS_HSD_SndHsmPilotSearchFailNtf();

        /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_INACTIVE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

        return;
    }

    if (CNAS_HSD_SYS_ACQ_FAIL_ACT_ACQ_IMMEDIATE == pstSysAcqRslt->enImmediateSysAcq)
    {
        /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_INITIAL */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);
    }
    else
    {
        /* �ϱ�����ʧ�� */
        CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL);

        /* �����ǰ�����ǻָ������µĶ������޳ɳ���Ϊ�������� */
        if (CNAS_HSD_SYS_ACQ_SCENE_NO_RF_RESUME == pstSysAcqRslt->enCurAcqScene)
        {
            pstSysAcqRslt->enCurAcqScene = CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST;
        }
        /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_OOC */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

        CNAS_HSD_SetOocSearchScene(pstSysAcqRslt->enCurAcqScene);
        CNAS_HSD_ProcOocSchedule(pstSysAcqRslt->enCurAcqScene);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvSysAcqRsltCnfProc_Initial
 ��������  : initial״̬�յ�ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvSysAcqRsltCnfProc_Initial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt;

    pstSysAcqRslt = (CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU *)pstMsg;

    CNAS_HSD_SndCasEndSessionNotify();

    /* ���abnormal��־ */
    CNAS_HSD_SetAbnormalLostFlag(VOS_FALSE);

    switch(pstSysAcqRslt->enRslt)
    {
        case CNAS_HSD_SYSTEM_ACQUIRED_RESULT_SUCCESS:
        {
            CNAS_HSD_RcvSysAcqRsltCnf_Initial_Succ(pstSysAcqRslt);

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_ACQUIRE_SUCCESS, UEPS_PID_HSD);
            break;
        }

        case CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ABORTED:
        {
            CNAS_HSD_RcvSysAcqRsltCnf_Initial_Aborted(pstSysAcqRslt);

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_LOST, UEPS_PID_HSD);

            break;
        }

        case CNAS_HSD_SYSTEM_ACQUIRED_RESULT_NORF:
        {
            CNAS_HSD_RcvSysAcqRsltCnf_Initial_NoRF(pstSysAcqRslt);

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_LOST, UEPS_PID_HSD);
            break;
        }

        case CNAS_HSD_SYSTEM_ACQUIRED_RESULT_FAILURE:
        {
            CNAS_HSD_RcvSysAcqRsltCnf_Initial_Fail(pstSysAcqRslt);

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_LOST, UEPS_PID_HSD);
            break;
        }

        case CNAS_HSD_SYSTEM_ACQUIRED_RESULT_REDIRECTION:
        {
            CNAS_HSD_RcvSysAcqRsltCnf_Initial_ReDir(pstSysAcqRslt);

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_LOST, UEPS_PID_HSD);

            break;
        }

        default:
            CNAS_ERROR_LOG(UEPS_PID_HSD, "Acq Scene error.");

            CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_SYS_LOST, UEPS_PID_HSD);
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvTiAvailTimerExpired_Ooc
 ��������  : OOC״̬��available��ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiAvailTimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_GetOocSearchScene(),
                                  0,
                                  VOS_NULL_PTR);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvPilotSearch_Inactive
 ��������  : INACTIVE״̬���յ�����㵼Ƶ������Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPilotSearch_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����L1״̬����������״̬ */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_PILOT_SEARCH, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvStartReq_Inactive
 ��������  : INACTIVE״̬���յ�������Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvStartReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���������쳣�ĳ�����MSCC��Ӧ����INACTIVE̬��������������յ��˻��ǻظ����������MSCC,֪ͨMSCC�����ɹ� */
    CNAS_HSD_SndMsccStartCnf(HSD_MSCC_START_RESULT_SUCC);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_Rcv1xSysAcqInd_Inactive
 ��������  : L1״̬�����յ�XSD��1X�������ɹ���Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��04��13��
    ��    ��   : Z00316370
    �޸�����   : �޸�1xϵͳ�Ľӿ�
*****************************************************************************/
VOS_UINT32 CNAS_HSD_Rcv1xSysChgInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SYS_ACQ_STATUS_ENUM_UINT32 enSysAcqStatus;
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene;

    enSysAcqStatus = CNAS_HSD_GetSysAcqStatus();

    if ((enSysAcqStatus & CNAS_HSD_SYS_ACQ_1X_SYS_ACQ_RCV) == CNAS_HSD_SYS_ACQ_1X_SYS_ACQ_RCV)
    {
        return VOS_TRUE;
    }

    enSysAcqScene = CNAS_HSD_GetAcqSceneBySysAcqStatus();

    /* MSCC��������1X�����������˾Ϳ�ʼ���� */
    if (CNAS_HSD_SYS_ACQ_SCENE_BUTT != enSysAcqScene)
    {
        /* ����L1״̬������INITIAL״̬ */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(enSysAcqScene, 0, VOS_NULL_PTR);
    }

    CNAS_HSD_SetSysAcqStatusByBit(CNAS_HSD_SYS_ACQ_1X_SYS_ACQ);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_Rcv1xSysAcqInd_Idle
 ��������  : L1״̬�����յ�XSD��1X�������ɹ���Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��04��11��
    ��    ��   : z00316370
    �޸�����   : 1x��Ϣ����MSCC���ͣ��޸���Ӧ��Ϣ�ӿ�
  3.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �жϺ�1x�����Խӿ��޸�

*****************************************************************************/
VOS_UINT32 CNAS_HSD_Rcv1xSysChgInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_1X_SYS_CHANGE_IND_STRU    *pst1xSysIndMsg;
    CNAS_HSD_ASSN_RLST_ENUM_UINT32      enAssnRlst;
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys;

    pst1xSysIndMsg = (MSCC_HSD_1X_SYS_CHANGE_IND_STRU *)pstMsg;

    /* 1X�������Ϊʧ�����ý����ж� */
    if (VOS_TRUE != pst1xSysIndMsg->ucIs1xAvail)
    {
        return VOS_TRUE;
    }

    /* ��Ҫ������̬�½���������ж� */
    if (CNAS_HSD_AT_STATUS_ENUM_IDLE != CNAS_HSD_GetATStatus())
    {
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_GetATStatus: Current state isn't idle.");

        return VOS_TRUE;
    }

    if (CNAS_HSD_HRPD_SYSTEM_AVAILABLE != CNAS_HSD_GetHrpdSysStatus())
    {
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_Rcv1xSysChgInd_Idle: Current state is incorrect.");

        /* �쳣����������CNAS_HSD_ASSN_SUCC������������������������� */
        return VOS_TRUE;
    }

    /* ����Ϊ��Ƶ�¾Ͳ����ж� */
    if (VOS_TRUE == CNAS_HSD_GetFreqLockMode())
    {
        return VOS_TRUE;
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

        return VOS_TRUE;
    }

    /* �й���Ƶ�㣬���͵�ǰ��HRPDϵͳ������� */
    if (CNAS_HSD_NO_ASSN_WITH_HRPD == enAssnRlst)
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_Rcv1xSysAcqInd_Ooc
 ��������  : L1״̬�����յ�XSD��1X�������ɹ���Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��22��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��04��11��
    ��    ��   : z00316370
    �޸�����   : 1x��Ϣ����MSCC���ͣ��޸���Ӧ��Ϣ�ӿ�
*****************************************************************************/
VOS_UINT32 CNAS_HSD_Rcv1xSysChgInd_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_1X_SYS_CHANGE_IND_STRU    *pst1xSysIndMsg;

    pst1xSysIndMsg = (MSCC_HSD_1X_SYS_CHANGE_IND_STRU *)pstMsg;

    /* 1X�������Ϊʧ�����ý����ж� */
    if (VOS_TRUE != pst1xSysIndMsg->ucIs1xAvail)
    {
        return VOS_TRUE;
    }

    /* ֹͣavailable��ʱ�� */
    CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_TIMER);
    CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_MRU0_TIMER);

    /* �����ǰ��NO_RF״̬����Ӧ�������������� */
    if (VOS_FALSE != CNAS_HSD_GetHrpdRfAvailFlg())
    {
        /* ����L1״̬������INITIAL״̬ */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);
        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasOhmInd_Idle
 ��������  : idle״̬�յ�ID_CAS_CNAS_1X_OHM_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��2��11��
    ��    ��   : w00208541
    �޸�����   : CDMA Iteration 8 ����Ohm�ϱ���mscc
  3.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �жϺ�1x�����Խӿ��޸�
  4.��    ��   : 2015��07��37��
    ��    ��   : x00306642
    �޸�����   : MCC��Ƥ���ж�
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasOhmInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU    *pstOhmMsg;
    CNAS_PRL_HRPD_SYSTEM_STRU               stHrpdSys;
    CNAS_HSD_ASSN_RLST_ENUM_UINT32          enAssnRlst;
    VOS_UINT32                              ulMccFlg;

    pstOhmMsg = (CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU*)pstMsg;

    stHrpdSys.stFreq.enBandClass = pstOhmMsg->usBandClass;
    stHrpdSys.stFreq.usChannel   = pstOhmMsg->usFreq;
    stHrpdSys.ucSubnetMask       = pstOhmMsg->ucSubNetMask;

    PS_MEM_CPY(stHrpdSys.aucSubnet, pstOhmMsg->aucSectorId, CNAS_PRL_BYTES_IN_SUBNET);

    /* avoidģ�鴦�� */
    CNAS_HSD_ProcAvoidEventInSubnetIdChange(&stHrpdSys);

    /* ����history list */
    CNAS_HSD_UpdateHistorySysList(&stHrpdSys);

    /* ����Hrpdפ����Ϣ */
    CNAS_HSD_UpdateHrpdSysInfo(&stHrpdSys);

    if (VOS_TRUE == CNAS_HSD_GetFreqLockMode())
    {
        /* Idle�л��ɹ��Ĵ���Ҫ�����汣��һ�� */
        /* HSD�յ�CAS��overhead��Ϣʱ��Ҫ��HSM�Լ�MSCCת��overhead��Ϣ */
        CNAS_HSD_SndHsmOverheadMsgInd(pstOhmMsg);
        CNAS_HSD_SndMsccOverheadMsgInd(pstOhmMsg,&stHrpdSys);

        /* ��פ�������籣�浽MRU */
        CNAS_HSD_UpdateMru0(&stHrpdSys);

        return VOS_TRUE;
    }

    enAssnRlst = CNAS_HSD_CheckHrpdFreqAssnWith1X(&stHrpdSys);

    ulMccFlg = CNAS_HSD_IsMccInOperLockWhiteSidList(pstOhmMsg->usCountryCode);

    /* ��ǰϵͳ������� */
    if ((CNAS_HSD_NO_ASSN_WITH_HRPD == enAssnRlst)
     || (VOS_FALSE == ulMccFlg))
    {
        /* IDLE̬�²Ž����������� */
        if (CNAS_HSD_AT_STATUS_ENUM_IDLE == CNAS_HSD_GetATStatus())
        {
            CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

            CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
        }
    }
    else if (CNAS_HSD_ASSN_SUCC == enAssnRlst)
    {
        /* Idle�л��ɹ��Ĵ���Ҫ�����汣��һ�� */
        /* HSD�յ�CAS��overhead��Ϣʱ��Ҫ��HSM�Լ�MSCCת��overhead��Ϣ */
        CNAS_HSD_SndHsmOverheadMsgInd(pstOhmMsg);
        CNAS_HSD_SndMsccOverheadMsgInd(pstOhmMsg,&stHrpdSys);

        /* ��פ�������籣�浽MRU */
        CNAS_HSD_UpdateMru0(&stHrpdSys);
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_HSD, "CNAS_HSD_RcvCasOhmInd_Idle: enAssnRlst is incorrect.");;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasNetworkLostIndProc_Idle
 ��������  : IDLE״̬���յ�������ϱ�������Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLostIndProc_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstCasNetworkLostMsg;
    VOS_UINT32                                              ulResult;

    pstCasNetworkLostMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU*)pstMsg;

    if (CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT == pstCasNetworkLostMsg->enNetworkLostReason)
    {
        /* �ض�����Ϣָʾ */
        ulResult = CNAS_HSD_RcvCasRedirectionInd_Idle(ulEventType, pstMsg);
    }
    else if (CAS_CNAS_HRPD_NETWORK_LOST_NO_RF == pstCasNetworkLostMsg->enNetworkLostReason)
    {
        ulResult = CNAS_HSD_RcvCasNoRFInd_Idle(ulEventType, pstMsg);
    }
    else
    {
        ulResult = CNAS_HSD_RcvCasNetworkLostInd_Idle(ulEventType, pstMsg);
    }

    CNAS_HSD_SndMsccHrpdNoSrvInd();

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasRedirectionInd_Idle
 ��������  : idle״̬�յ�ID_CAS_CNAS_HRPD_REDIRECTION_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��5��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasRedirectionInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstCasRedirMsg;
    CNAS_HSD_REDIRECTION_STRU                              *pstRedirection;

    pstRedirection = CNAS_HSD_GetRedirectionFreqAddr();

    pstCasRedirMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU*)pstMsg;

    if (0 == pstCasRedirMsg->ucChanNum)
    {
        /* ��Я��Ƶ����Ϣ���ض�����Ϣ������ͨ���������� */
        /* ����L1״̬����������״̬ */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        /* �������� */
        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);

        return VOS_TRUE;
    }

    /* �յ���Ƶ�����ȫ�ֱ��������ڹ��������� */
    pstRedirection->ucChanNum = pstCasRedirMsg->ucChanNum;

    PS_MEM_CPY(pstRedirection->aulChannel,
               pstCasRedirMsg->aulChannel,
               sizeof(CAS_CNAS_HRPD_DERECTION_CHANNEL_STRU) * pstCasRedirMsg->ucChanNum);

    /* ��ӡ�յ���Ƶ����Ϣ */
    CNAS_HSD_LogRedirectionFreqList(pstRedirection);

    /* ����L1״̬����������״̬ */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    /* �������� */
    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasNetworkLostInd_Idle
 ��������  : IDLE״̬���յ�������ϱ�������Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNetworkLostInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU                    *pstLostMsg;

    pstLostMsg = (CAS_CNAS_HRPD_NETWORK_LOST_IND_STRU *)pstMsg;

    /* ����L1״̬������INITIAL״̬ */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    if (CAS_CNAS_HRPD_NETWORK_LOST_ABNORMAL == pstLostMsg->enNetworkLostReason)
    {
        CNAS_HSD_SetAbnormalLostFlag(VOS_TRUE);
    }

    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST, VOS_NULL, VOS_NULL_PTR);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Idle
 ��������  : IDLE״̬���յ���ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��5��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �Ѿ�פ�����ֱ�ӻظ��ɹ� */
    CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvTiAvailMru0TimerExpired_Ooc
 ��������  : OOC״̬��available��ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ  :
  1.��    ��   : 2015��1��14��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvTiAvailMru0TimerExpired_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    /* ����MRU0 */
    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_OOC_MRU0, 0, VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_UpdateOocSearchPhaseAndCurrentTimes
 ��������  : ���µ�����������Ϣ
 �������  : CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��13��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_UpdateOocSearchPhaseAndCurrentTimes(
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
)
{
    VOS_UINT8                           ucOocSchPhaseNum;
    VOS_UINT16                          usOocSchPhaseTimes;

    /* ���ݵ�ǰOOC�׶λ�ȡ�´�����OOC����ʱ�� */
    ucOocSchPhaseNum    = pstOocScheduleInfo->stOocCtxInfo.ucCurrentPhase;
    usOocSchPhaseTimes  = pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[ucOocSchPhaseNum].usTimes;

    /* ˢ�µ�ǰ�����Ľ׶κʹ��� */
    if ((pstOocScheduleInfo->stConfigInfo.ucPhaseNum - 1) == ucOocSchPhaseNum)
    {
        /* �����ǰ�Ѿ�����ĩβ�Ľ׶Σ������Ѿ�û�����壬����ʼ�����ó�255 */
        pstOocScheduleInfo->stOocCtxInfo.usCurrentTimes = CNAS_HSD_ATTEMP_UNLIMITED_TIMES;
    }
    else
    {
        /* ������ĩλ�Ľ׶Σ�������ۼӣ������ǰ�Ĵ����Ѿ����˸ý׶ε�����������׶����ӣ�
             ���Ѵ�����0 */
        pstOocScheduleInfo->stOocCtxInfo.usCurrentTimes++;
        if (pstOocScheduleInfo->stOocCtxInfo.usCurrentTimes >= usOocSchPhaseTimes)
        {
            pstOocScheduleInfo->stOocCtxInfo.ucCurrentPhase++;
            pstOocScheduleInfo->stOocCtxInfo.usCurrentTimes = 0;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetNextOocScheduleTimerLen
 ��������  : ��ȡ��һ�ε���ʱ��
 �������  : CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��13��
    ��    ��   : Z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 CNAS_HSD_GetNextOocScheduleTimerLen(
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo
)
{
    VOS_UINT16                          usNextTimerLen;
    VOS_UINT8                           ucOocSchPhaseNum;

    usNextTimerLen = 0;

    /* ���ݵ�ǰOOC�׶λ�ȡ�´�����OOC����ʱ�� */
    ucOocSchPhaseNum    = pstOocScheduleInfo->stOocCtxInfo.ucCurrentPhase;
    usNextTimerLen      = pstOocScheduleInfo->stConfigInfo.astOocTimerInfo[ucOocSchPhaseNum].usTimerLen;

    return usNextTimerLen;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcOocSchedule
 ��������  : ����OOC����
 �������  : CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��13��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcOocSchedule(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene
)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;
    VOS_UINT16                          usNextAcqTimerLen;
    VOS_UINT8                           ucMru0SearchTimerLen;
    VOS_UINT32                          ulRemainTimerLen;

    pstOocScheduleInfo = CNAS_HSD_GetOocScheduleInfo();

    ucMru0SearchTimerLen = pstOocScheduleInfo->stConfigInfo.ucMru0SearchTimerLen;

    /* �еȴ�OOC������,��MRU0����ʱ���OOC��ʱ����ʱ������OOC��������,
       ��MRU0����ʧ�ܻ᷵�ص���ʱ��ֱ������OOC����*/
    if (VOS_TRUE == CNAS_HSD_GetOocWaitSearchFlag())
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene, 0, VOS_NULL_PTR);

        /* ������ */
        CNAS_HSD_SetOocWaitSearchFlag(VOS_FALSE);

        return;
    }

    /* ����MRU0ʧ�ܣ��ٴ�check MRU0��ʱ���Ƿ�������� */
    if (CNAS_HSD_SYS_ACQ_SCENE_OOC_MRU0 == enAcqScene)
    {
        /* MRU0����������Ϊ0ʱ�����Գ���MRU0 */
        if (ucMru0SearchTimerLen != 0)
        {
            /* ��ȡavailableʣ��ʱ�� */
            ulRemainTimerLen = CNAS_GetSpecifiedTimerRemainLen(UEPS_PID_HSD, TI_CNAS_HSD_AVAILABLE_TIMER, 0);

            /* ���ʣ��ʱ����Ȼ����2��MRU0ʱ�������Գ���MRU0, ����MRU0��ʱ�� */
            if ((VOS_UINT32)(ucMru0SearchTimerLen * 2000) < ulRemainTimerLen)
            {
                CNAS_HSD_StartTimer(TI_CNAS_HSD_AVAILABLE_MRU0_TIMER, (ucMru0SearchTimerLen * TI_CNAS_HSD_AVAILABLE_RATIO));
            }
        }

        return;
    }

    /* ����ǰ LOG OOC������Ϣ */
    CNAS_HSD_LogOocCtxInfo(&(pstOocScheduleInfo->stOocCtxInfo));

    usNextAcqTimerLen = CNAS_HSD_GetNextOocScheduleTimerLen(pstOocScheduleInfo);

    /* ���OOC����ʱ��Ϊ0�������������� */
    if (0 == usNextAcqTimerLen)
    {
        /* ����L1 main״̬Ϊinitial״̬ */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        /* ����OOC������ϵͳ���� */
        CNAS_HSD_SndInternalSysAcqReq(pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene, 0, VOS_NULL_PTR);
    }
    else
    {
        /* ����OOC available��ʱ�� */
        CNAS_HSD_StartTimer(TI_CNAS_HSD_AVAILABLE_TIMER, (usNextAcqTimerLen * TI_CNAS_HSD_AVAILABLE_RATIO));

        /* �����OOC������������MRU0�Ķ�ʱ���Ȳ�Ϊ0������Ƿ���Ҫ����MRU0���� */
        if ((CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST == pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene)
         && (ucMru0SearchTimerLen != 0))
        {
            /* 2��MRU0����ʱ���Ƿ�С�ڵ�ǰOOC sleepʱ��������ǣ�����MRU0 available��ʱ�� */
            if ((VOS_UINT32)(ucMru0SearchTimerLen * 2000) < usNextAcqTimerLen)
            {
                CNAS_HSD_StartTimer(TI_CNAS_HSD_AVAILABLE_MRU0_TIMER, (ucMru0SearchTimerLen * TI_CNAS_HSD_AVAILABLE_RATIO));
            }
        }
    }

    /* ����OOC�����׶μ���ǰ�׶��������� */
    CNAS_HSD_UpdateOocSearchPhaseAndCurrentTimes(pstOocScheduleInfo);

    /* ���º� LOG OOC������Ϣ */
    CNAS_HSD_LogOocCtxInfo(&(pstOocScheduleInfo->stOocCtxInfo));

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetOocSearchScene
 ��������  : ����OOC��������
 �������  : enAcqScene -- ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��13��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SetOocSearchScene(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enAcqScene
)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;

    pstOocScheduleInfo = CNAS_HSD_GetOocScheduleInfo();

    /* ������������ */
    if (VOS_FALSE == pstOocScheduleInfo->stOocCtxInfo.ucSceneSetFlag)
    {
        if (CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON != enAcqScene)
        {
            /* ������ǿ�������ʧ�ܣ���ͳһ����ΪOOC���� */
            pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene = CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST;
        }
        else
        {
            pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene = CNAS_HSD_SYS_ACQ_SCENE_OOC_SWITCH_ON;
        }

        pstOocScheduleInfo->stOocCtxInfo.ucSceneSetFlag       = VOS_TRUE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetOocSearchScene
 ��������  : ��ȡOOC��������
 �������  : enAcqScene -- ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��09��04��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetOocSearchScene(VOS_VOID)
{
    CNAS_HSD_OOC_SCHEDULE_INFO_STRU    *pstOocScheduleInfo = VOS_NULL_PTR;

    pstOocScheduleInfo = CNAS_HSD_GetOocScheduleInfo();

    return (pstOocScheduleInfo->stOocCtxInfo.enOocSearchScene);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Ooc
 ��������  : OOC״̬���յ���ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��5��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU  *pstDataCallRedialReq;

    pstDataCallRedialReq = (MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU*)pstMsg;

    if (NAS_MSCC_PIF_CDMA_CALL_CAUSE_NO_SERVICE == pstDataCallRedialReq->enCause)
    {
        /* ����L1״̬����������״̬ */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        /* �������� */
        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvPowerSaveReq_L1Main
 ��������  : �յ�ID_MSCC_HSD_POWER_SAVE_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPowerSaveReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����L2 POWER_SAVE״̬�� */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_POWER_SAVE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvPowerSaveReq_Inactive
 ��������  : inactive״̬���յ�ID_MSCC_HSD_POWER_SAVE_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��06��30��
    ��    ��   : z00316370
    �޸�����   : INACTIVE״̬��Ҳ��POWER SAVE ״̬��
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPowerSaveReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���HRPD����״̬ */
    CNAS_HSD_ClearHrpdSysAcqStatusBits();

    /* inactive״̬�£�ֱ�ӻظ�MSCC POWER SAVE��� */
    CNAS_HSD_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvPowerSaveRsltCnf_L1Main
 ��������  : ������IDLE��OCC״̬�յ�L2 power saveȷ���¼�
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
   1.��    ��   : 2015��04��03��
     ��    ��   : z00316370
     �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvPowerSaveRsltCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ֹͣHSD���ж�ʱ�� */
    //CNAS_StopAllTimerWithSpecifiedPid(UEPS_PID_HSD);
    CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_TIMER);
    CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_MRU0_TIMER);
    CNAS_HSD_StopTimer(TI_CNAS_HSD_WAIT_RRM_STATUS_IND);

    /* ֪ͨMSCC POWER SAVE��� */
    CNAS_HSD_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

    /* ���HRPD����״̬ */
    CNAS_HSD_ClearHrpdSysAcqStatusBits();

    /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_INACTIVE */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);

    CNAS_MNTN_LogKeyEvent(NAS_OM_EVENT_HRPD_POWER_SAVE, UEPS_PID_HSD);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_StartSysAcq_Inactive
 ��������  : ��INACTIVE״̬�յ�sys acq������������
 �������  : CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
   1.��    ��   : 2015��04��07��
     ��    ��   : z00316370
     �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_StartSysAcq_Inactive(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
)
{
    CNAS_HSD_SYS_ACQ_STATUS_ENUM_UINT32 enSysAcqStatus;

    /* �ǻ��ģʽ���յ�MSCC����������֮��Ϳ�ʼ���� */
    if (CNAS_HSD_SYS_MODE_NONHYBRID == CNAS_HSD_GetModeType())
    {
        /* ����L1״̬������INITIAL״̬ */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(enSysAcqScene, 0, VOS_NULL_PTR);
    }
    else
    {
        CNAS_HSD_SetSysAcqStatusByAcqScene(enSysAcqScene);

        enSysAcqStatus = CNAS_HSD_GetSysAcqStatus();

        /* 1X�������յ��Ϳ�ʼ���� */
        if ((enSysAcqStatus & CNAS_HSD_SYS_ACQ_1X_SYS_ACQ_RCV) == CNAS_HSD_SYS_ACQ_1X_SYS_ACQ_RCV)
        {
            /* ����L1״̬������INITIAL״̬ */
            CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

            CNAS_HSD_SndInternalSysAcqReq(enSysAcqScene, 0, VOS_NULL_PTR);
        }
    }
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasSubnetIdChkReq_Inactive
 ��������  : ����ID_CAS_CNAS_HRPD_SUBNET_ID_CHECK_REQ������Ϣ
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
   1.��    ��   : 2015��06��02��
     ��    ��   : z00316370
     �޸�����   : �����ɺ���
   2.��    ��   : 2015��08��10��
     ��    ��   : x00306642
     �޸�����   : ���Ӱ�Ƥ����ж�
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasSubnetIdChkReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_HRPD_SUBNET_ID_CHECK_REQ_STRU                 *pstSubnetChk;
    CNAS_PRL_HRPD_SYSTEM_STRU                               stHrpdSys;
    VOS_UINT32                                              ulRslt;
    VOS_UINT32                                              ulMccFlg;

    pstSubnetChk = (CAS_CNAS_HRPD_SUBNET_ID_CHECK_REQ_STRU *)pstMsg;

    stHrpdSys.stFreq.enBandClass    = pstSubnetChk->usBandClass;
    stHrpdSys.stFreq.usChannel      = pstSubnetChk->usFreq;
    stHrpdSys.ucSubnetMask          = pstSubnetChk->ucSubNetMask;
    PS_MEM_CPY(stHrpdSys.aucSubnet, pstSubnetChk->aucSectorId, CNAS_PRL_BYTES_IN_SUBNET);

    /* ���HRPDϵͳ����Ч�� */
    ulRslt = CNAS_HSD_HrpdSubnetIdChkProc(&stHrpdSys);

    ulMccFlg = CNAS_HSD_IsMccInOperLockWhiteSidList(pstSubnetChk->usCountryCode);

    if ((VOS_TRUE == ulRslt) && (VOS_TRUE == ulMccFlg))
    {
        /* �ظ���Ч */
        CNAS_HSD_SndCasSubnetIdChkCnf(PS_TRUE);
    }
    else
    {
        /* �ظ���Ч */
        CNAS_HSD_SndCasSubnetIdChkCnf(PS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasIratFromLteNtf_Inactive
 ��������  : ����ID_CAS_CNAS_HRPD_IRAT_FROM_LTE_NTF������Ϣ
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
   1.��    ��   : 2015��06��02��
     ��    ��   : z00316370
     �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasIratFromLteNtf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SndHsmIratFromLteInd();

    /* ��Լ���˴���BUTT��MSCC���������Ǵ�LTE��ѡ���ǻ���HRPD */
    CNAS_HSD_SndMsccInterSysEndInd(VOS_RATMODE_BUTT);

    /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_IDLE */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_IDLE);
    /* Inactive������L2 ��ϵͳ��״̬�� */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_INTER_SYS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvHrpdInterSysRsltCnf_Proc
 ��������  : CL�л���HRPD��ʽ�µĽ������
 �������  : ucRslt                     -- C-L���
             enNetworkLostReason        -- lostԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
   1.��    ��   : 2015��09��18��
     ��    ��   : z00316370
     �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    CNAS_HSD_RcvHrpdInterSysRsltCnf_Proc(
    VOS_UINT8                                               ucRslt,
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason
)
{
    CNAS_HSD_REDIRECTION_STRU                              *pstRedirection;

    pstRedirection = CNAS_HSD_GetRedirectionFreqAddr();

    if (VOS_TRUE == ucRslt)
    {
        /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_IDLE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_IDLE);

        /* ��ʼ��OOC��������Ϣ */
        CNAS_HSD_InitOocCtxInfo();

        /* ֹͣOOC��������ʱ�� */
        CNAS_HSD_StopTimer(TI_CNAS_HSD_AVAILABLE_TIMER);
    }
    else
    {
        switch (enNetworkLostReason)
        {
            case CAS_CNAS_HRPD_NETWORK_LOST_REDIRECT:
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);
                if (0 == pstRedirection->ucChanNum)
                {
                    /* �������� */
                    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);
                }
                else
                {
                    /* �������� */
                    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION, 0, VOS_NULL_PTR);
                }
                break;
            case CAS_CNAS_HRPD_NETWORK_LOST_NORMAL_ACS:
            case CAS_CNAS_HRPD_NETWORK_LOST_NORMAL_OTHER:
            case CAS_CNAS_HRPD_NETWORK_LOST_ABNORMAL:
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);
                CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST, 0, VOS_NULL_PTR);
                break;
            /* NO RF ���� */
            case CAS_CNAS_HRPD_NETWORK_LOST_NO_RF:
                CNAS_HSD_RcvCasNoRFInd_Proc();
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);
                break;
            default:
                /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_OOC */
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

                CNAS_HSD_SetOocSearchScene(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST);
                CNAS_HSD_ProcOocSchedule(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST);
                break;
        }
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvInterSysRsltCnf_Inactive
 ��������  : ����ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF������Ϣ
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
   1.��    ��   : 2015��06��02��
     ��    ��   : z00316370
     �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvInterSysRsltCnf_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU                   *pstRsltMsg;

    pstRsltMsg  = (CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU *)pstMsg;

    if (VOS_RATMODE_HRPD == pstRsltMsg->enCampedRatMode)
    {
        CNAS_HSD_RcvHrpdInterSysRsltCnf_Proc(pstRsltMsg->ucRslt,
                                            pstRsltMsg->enNetworkLostReason);

    }
    /* LTE��ģ��HRPDΪINACTIVE̬ */
    else
    {}

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvInterSysRsltCnf_Idle
 ��������  : IDLE̬����ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF������Ϣ
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
   1.��    ��   : 2015��07��01��
     ��    ��   : z00316370
     �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvInterSysRsltCnf_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU                   *pstRsltMsg;

    pstRsltMsg  = (CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU *)pstMsg;

    if (VOS_RATMODE_HRPD == pstRsltMsg->enCampedRatMode)
    {
        CNAS_HSD_RcvHrpdInterSysRsltCnf_Proc(pstRsltMsg->ucRslt,
                                            pstRsltMsg->enNetworkLostReason);
    }
    /* LTE��ģ��HRPDΪINACTIVE̬ */
    else
    {
        /* ���HRPD����״̬ */
        CNAS_HSD_ClearHrpdSysAcqStatusBits();

        /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_IDLE */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INACTIVE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasSuspendInd_Idle
 ��������  : ����ID_CAS_CNAS_HRPD_SUSPEND_IND������Ϣ
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
   1.��    ��   : 2015��06��02��
     ��    ��   : z00316370
     �޸�����   : �����ɺ���
   1.��    ��   : 2015��11��13��
     ��    ��   : y00346957
     �޸�����   : DTS2015070910837�޸ģ�intersys cause ö��ͳһ��mscc pif�е�
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasSuspendInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_HSD_SndHsmSuspendInd();

    CNAS_HSD_SndMsccInterSysStartInd(VOS_RATMODE_HRPD,
                                     VOS_RATMODE_LTE,
                                     NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT);

    /* Inactive������L2 ��ϵͳ��״̬�� */
    CNAS_HSD_InitFsmL2(CNAS_HSD_FSM_INTER_SYS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SubnetIdChkProc
 ��������  : ��ϵͳ�л���HRPDʱ����Ч���ж�
 �������  : pstHrpdSys         HRPDϵͳ��Ϣ
 �������  : VOS_VOID

 �� �� ֵ  : VOS_TRUE           - �����
             VOS_FALSE          - �������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��08��
    ��    ��   : z00316370
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 CNAS_HSD_HrpdSubnetIdChkProc(
    CNAS_PRL_HRPD_SYSTEM_STRU          *pstHrpdSys
)
{
    CNAS_HSD_ASSN_RLST_ENUM_UINT32      enAssnRlst;

    /* �й�����HRPDϵͳ��������HRPDϵͳ��û��Ƶ�㣬���ж��߼��Ƿ���CNAS_HSD_NO_ASSN_FREQ
        ���ض���HRPDϵͳʱ���������ж��߼��Ƿ����???
        ���ض����Ƶ�����ڵ�HRPDϵͳ�ǹ����ģ����ǲ���PRL���У����ڵ��ж��߼���ʧ�ܣ��Ƿ����??? */
    enAssnRlst = CNAS_HSD_CheckHrpdSysAssnWith1X(pstHrpdSys);

    if (CNAS_HSD_ASSN_SUCC != enAssnRlst)
    {
        return VOS_FALSE;
    }

    /* �������������ж��Ƿ�avoid��Ƶ�� */
    CNAS_HSD_CheckExpiredFreqFromAvoidList();

    if (VOS_TRUE == CNAS_HSD_IsCurFreqAvoided(&(pstHrpdSys->stFreq)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Inactive
 ��������  : ����ID_MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ������Ϣ
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
   1.��    ��   : 2015��06��25��
     ��    ��   : z00316370
     �޸�����   : �����ɺ���
   2.��    ��   : 2015��12��18��
     ��    ��   : z00316370
     �޸�����   : INACTIVE��Ҳ֧�ֿ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvMsccDataCallRedialSysAcqReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU  *pstDataCallRedialReq;

    pstDataCallRedialReq = (MSCC_HSD_DATA_CALL_REDIAL_SYS_ACQ_REQ_STRU*)pstMsg;

    if (NAS_MSCC_PIF_CDMA_CALL_CAUSE_NO_SERVICE == pstDataCallRedialReq->enCause)
    {
        /* ����L1״̬����������״̬ */
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        /* �������� */
        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasNoRF_Idle
 ��������  : �յ�RRM NO RF״ָ̬ʾ��ʱ�������ǰ����NO RF,����MSCC͸��Status Ind��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE(����ɹ�)
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��15��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvCasNoRFInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����NO RF */
    CNAS_HSD_RcvCasNoRFInd_Proc();

    /* ��IDLE ״̬ʱ�յ�NO_RF�����ٽ��лָ��������������½������Խ��������ó�BUTT */
    CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_BUTT);

    /* ״̬Ǩ�Ƶ�CNAS_HSD_L1_STA_OOC */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_OOC);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvCasNoRFInd_Proc
 ��������  : IDLE̬�յ�RRM NO RF״ָ̬ʾ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��18��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvCasNoRFInd_Proc(VOS_VOID)
{
    /* ����NORF�ĳ��� */
    CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_SYSTEM_LOST);

    /* ��RRM����ע��,RF���ú�RRM��֪ͨHSD */
    CNAS_HSD_SndRrmRegisterInd(RRM_PS_TASK_TYPE_HRPD_NETWORK_SEARCH);

    /* ����������ʱ�� */
    CNAS_HSD_StartTimer(TI_CNAS_HSD_WAIT_RRM_STATUS_IND, TI_CNAS_HSD_WAIT_RRM_STATUS_IND_LEN);

    if (VOS_TRUE == CNAS_HSD_GetHrpdRfAvailFlg())
    {
        /* �ϱ�MSCC NO RF��Ϣ */
        CNAS_HSD_SndMsccRfAvailInd(VOS_FALSE);

        /* ���õ�ǰRF���ñ��Ϊ:RF������ */
        CNAS_HSD_SetHrpdRfAvailFlg(VOS_FALSE);
    }

    /* �oMSCC ����END ��Ϣ����MSCC ȥ��LTE WENXIAO Ҫ������������Ϣ*/
    CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_NO_RF);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvRrmStatusInd_Deactive
 ��������  : �յ�RRM NO RF״ָ̬ʾ��ʱ�������ǰ����NO RF,����MSCC͸��Status Ind��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE(����ɹ�)
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��15��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvRrmStatusInd_Deactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ж�RF���ñ�� */
    if (VOS_FALSE == CNAS_HSD_GetHrpdRfAvailFlg())
    {
        /* ��ǰ����NO RF ��MSCC͸����Ϣ,���������� */
        CNAS_HSD_SndMsccRfAvailInd(VOS_TRUE);

        /* ���õ�ǰRF���ñ��Ϊ:RF���� */
        CNAS_HSD_SetHrpdRfAvailFlg(VOS_TRUE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvRrmStatusInd_Ooc
 ��������  : �յ�RRM NO RF״ָ̬ʾ��ʱ�򣬷�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE(����ɹ�)
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��15��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvRrmStatusInd_Ooc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enScene;
    CNAS_HSD_1X_SYSTEM_INFO_STRU       *pstNew1xSystem;
    CNAS_HSD_1X_SYSTEM_INFO_STRU       *pstScanList1xSystem;
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8    enNoRfUeStatus;
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8    enCur1xUeStatus;
    VOS_UINT32                          ulIs1XSysMatched    = VOS_FALSE;
    VOS_UINT32                          ulIs1XNoChanged     = VOS_FALSE;

    pstNew1xSystem      = CNAS_HSD_Get1xSystemInfo();
    pstScanList1xSystem = CNAS_HSD_GetScanListMatched1xSystemInfo();
    enCur1xUeStatus     = CNAS_CCB_GetCasState();

    /* �����ǰ����NO RF״̬���򴥷����� */
    if (VOS_FALSE == CNAS_HSD_GetHrpdRfAvailFlg())
    {
        enScene = CNAS_HSD_GetNoRfScene();

        if (CNAS_HSD_SYS_ACQ_SCENE_BUTT >= enScene)
        {

            CNAS_HSD_SetNoRfScene(CNAS_HSD_SYS_ACQ_SCENE_BUTT);
            enNoRfUeStatus      = CNAS_HSD_GetNoRf1XUeStatus();

            ulIs1XSysMatched    = CNAS_HSD_Is1xSysStillMatchHrpdSearchList(&pstScanList1xSystem->st1xSys,&pstNew1xSystem->st1xSys);

            /* NO_RFǰ���Ƕ�����Ϊû�б仯 */
            if (((CNAS_CCB_1X_CAS_INIT_STATE == enNoRfUeStatus) || (CNAS_CCB_1X_CAS_NO_SERVICE_STATE == enNoRfUeStatus))
            && ((CNAS_CCB_1X_CAS_INIT_STATE == enCur1xUeStatus) || (CNAS_CCB_1X_CAS_NO_SERVICE_STATE == enCur1xUeStatus)))
            {
                ulIs1XNoChanged = VOS_TRUE;
            }
            else if (((CNAS_CCB_1X_CAS_INIT_STATE != enNoRfUeStatus) && (CNAS_CCB_1X_CAS_NO_SERVICE_STATE != enNoRfUeStatus))
                   &&((CNAS_CCB_1X_CAS_INIT_STATE != enCur1xUeStatus) && (CNAS_CCB_1X_CAS_NO_SERVICE_STATE != enCur1xUeStatus))
                   &&( VOS_TRUE == ulIs1XSysMatched ))
            {
                /* ���NO_RFǰ��������������1xû�б仯������Ҫ���½��� */
                ulIs1XNoChanged = VOS_TRUE;
            }
            else
            {

                ulIs1XNoChanged = VOS_FALSE;
            }

            /* ��� 1Xû�б��(NO_RFǰ���ǲ����ڣ����߶����ڻ���ƥ��)�����ǿ����� ����IDLE̬��NO_RF,�Ž��лָ����� */
            if ((VOS_TRUE == ulIs1XNoChanged)
            &&  (CNAS_HSD_SYS_ACQ_SCENE_DATA_CALL_QUICK != enScene)
            &&  (CNAS_HSD_SYS_ACQ_SCENE_BUTT            != enScene))
            {
                /* ����L1״̬������INITIAL״̬ */
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

                CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_NO_RF_RESUME, 0, VOS_NULL_PTR);

            }
            else
            {
                /* 1x ��� ��Ҫ�������� */
                /* ����L1״̬������INITIAL״̬ */
                CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

                CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
            }


        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvSysAcqRsltCnf_Initial_ReDir
 ��������  : initial״̬�յ�ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF��Ϣ�Ĵ���
 �������  : pstSysAcqRslt

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��15��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_RcvSysAcqRsltCnf_Initial_ReDir(
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstSysAcqRslt
)
{
    /* ����L1״̬����������״̬ */
    CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

    /* �������� */
    CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_REDIRECTION, 0, VOS_NULL_PTR);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_CovertSessionType_PreProc
 ��������  : ��HSM_HSD֮���session typeת��ΪHSD_MSCC֮���session type
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��10��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���
*****************************************************************************/
HSD_MSCC_SESSION_RELEASE_TYPE_ENUM_UINT32 CNAS_HSD_CovertSessionType_Proc(
    HSM_HSD_SESSION_RELEASE_TYPE_ENUM_UINT8                 enSessionRelType
)
{
    HSD_MSCC_SESSION_RELEASE_TYPE_ENUM_UINT32               enCurrSessionRelType;

    enCurrSessionRelType = HSD_MSCC_SESSION_RELEASE_TYPE_BUTT;

    if (HSM_HSD_SESSION_RELEASE_TYPE_0 == enSessionRelType)
    {
        enCurrSessionRelType = HSD_MSCC_SESSION_RELEASE_TYPE_0;
    }
    else if (HSM_HSD_SESSION_RELEASE_TYPE_A == enSessionRelType)
    {
        enCurrSessionRelType = HSD_MSCC_SESSION_RELEASE_TYPE_A;
    }
    else
    {
        enCurrSessionRelType = HSD_MSCC_SESSION_RELEASE_TYPE_BUTT;
    }

    return enCurrSessionRelType;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvHsmSessionNegResultInd_PreProc
 ��������  : idle״̬�յ�ID_HSM_HSD_SESSION_NEG_RESULT_IND��Ϣ�Ĵ���
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
  2.��    ��   : 2015��2��11��
    ��    ��   : w00208541
    �޸�����   : CDMA Iteration 8 ����Э�̽���ϱ���MSCC
  3.��    ��   : 2015��04��06��
    ��    ��   : z00316370
    �޸�����   : CDMA Iteration 10 ���ӵ�ǰ״̬�ж�
  4.��    ��   : 2015��06��03��
    ��    ��   : l00324781
    �޸�����   : CDMA Iteration 12 CNAS_HSD_SndMsccSessionNegRsltInd ���Ӳ���
  5.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvHsmSessionNegResultInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_HSD_SESSION_NEG_RESULT_IND_STRU                    *pstSessionNegRlstInd;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq;
    CNAS_HSD_REACQ_FALG_ENUM_UINT32                         enReAcqFlag;
    HSD_MSCC_SESSION_RELEASE_TYPE_ENUM_UINT32               enCurrSessionRelType;

    pstSessionNegRlstInd = (HSM_HSD_SESSION_NEG_RESULT_IND_STRU*)pstMsg;
    stFreq.enBandClass   = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.enBandClass;
    stFreq.usChannel     = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.usChannel;
    enReAcqFlag          = CNAS_HSD_NOT_NEED_REACQ;

    /* avoidģ�鴦�� */
    CNAS_HSD_ProcAvoidEventInSessionNegRlstInd(pstSessionNegRlstInd, &stFreq, &enReAcqFlag);

    /* �Ƿ���Ҫ�������� */
    if (CNAS_HSD_NEED_REACQ == enReAcqFlag)
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);

        CNAS_HSD_SndMsccHrpdNoSrvInd();

    }
    /* �ɹ���MSCC�ϰ�session��� */
    else if (HSM_HSD_SESSION_NEG_RSLT_SESSION_CLOSE != pstSessionNegRlstInd->enNegResult)
    {
        enCurrSessionRelType = CNAS_HSD_CovertSessionType_Proc(pstSessionNegRlstInd->enSessionRelType);

        CNAS_HSD_SndMsccSessionNegRsltInd(pstSessionNegRlstInd->enNegResult,
                                          pstSessionNegRlstInd->ucIsNewSession,
                                          enCurrSessionRelType,
                                          pstSessionNegRlstInd->ucIsEhrpdSupport);
    }
    else
    {}

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_GetSysAcqStatusByAcqScene
 ��������  : ���������������ص�ǰ��������λ״̬
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��01��09��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32 CNAS_HSD_GetAcqSceneBySysAcqStatus(VOS_VOID)
{
    CNAS_HSD_SYS_ACQ_STATUS_ENUM_UINT32 enSysAcqStatus;

    enSysAcqStatus = CNAS_HSD_GetSysAcqStatus();

    if ( CNAS_HSD_SYS_ACQ_POWER_ON_RCV == enSysAcqStatus)
    {
        return CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON;
    }
    else if(CNAS_HSD_SYS_ACQ_HIGH_PRI_RCV == enSysAcqStatus)
    {
        return CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY;
    }
    else if ( CNAS_HSD_SYS_ACQ_OTHER_RCV == enSysAcqStatus)
    {
        return CNAS_HSD_SYS_ACQ_SCENE_MSCC_OTHER;
    }
    else
    {
        return CNAS_HSD_SYS_ACQ_SCENE_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SetSysAcqStatusByAcqScene
 ��������  : ���������������õ�ǰ��������λ״̬
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��01��09��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_SetSysAcqStatusByAcqScene(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
)
{
    if (CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON == enSysAcqScene)
    {
        CNAS_HSD_SetSysAcqStatusByBit(CNAS_HSD_POWER_ON_SYS_ACQ);
    }
    else if(CNAS_HSD_SYS_ACQ_SCENE_HIGH_PRIORITY == enSysAcqScene)
    {
        CNAS_HSD_SetSysAcqStatusByBit(CNAS_HSD_HIGH_PRI_SYS_ACQ);
    }
    else
    {
        CNAS_HSD_SetSysAcqStatusByBit(CNAS_HSD_OTHER_SYS_ACQ);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RcvHsmConnOpenInd_Idle
 ��������  : �յ�CAS_CNAS_HRPD_ACCESS_RLST_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��06��
    ��    ��   : z00316370
    �޸�����   : ����

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RcvHsmConnOpenInd_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_HSD_CONN_OPEN_IND_STRU         *pstOpenInd;
    CNAS_PRL_FREQENCY_CHANNEL_STRU      stFreq;
    CNAS_HSD_REACQ_FALG_ENUM_UINT32     enReAcqFlag;

    pstOpenInd              = (HSM_HSD_CONN_OPEN_IND_STRU *)pstMsg;
    stFreq.enBandClass      = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.enBandClass;
    stFreq.usChannel        = CNAS_HSD_GetHistorySysList()->stCampedHrpdSysInfo[0].stFreq.usChannel;
    enReAcqFlag             = CNAS_HSD_NOT_NEED_REACQ;

    /* avoidģ�鴦�� */
    CNAS_HSD_ProcAvoidEventInAccessRlstInd(pstOpenInd, &stFreq, &enReAcqFlag);

    /* �Ƿ���Ҫ�������� */
    if (CNAS_HSD_NEED_REACQ == enReAcqFlag)
    {
        CNAS_HSD_SetCurrFsmState(CNAS_HSD_L1_STA_INITIAL);

        CNAS_HSD_SndInternalSysAcqReq(CNAS_HSD_SYS_ACQ_SCENE_SWITCH_ON, 0, VOS_NULL_PTR);
    }

    return VOS_TRUE;
}
/*lint -restore*/

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



