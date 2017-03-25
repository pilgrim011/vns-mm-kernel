/*******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdFsmPowerOff.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��07��03��
  ��������   : 1X SD L2�ػ�״̬���¼�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��03��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXsdFsmPowerOff.h"
#include  "CnasXsdFsmPowerOffTbl.h"
#include  "CnasXsdProcCard.h"
#include  "CnasXsdSndXcc.h"
#include  "CnasXsdSndXreg.h"
#include  "CnasXsdSndMscc.h"
#include  "CnasXsdSndCas.h"
#include  "CnasMntn.h"
#include  "CnasXsdCtx.h"
#include  "CnasXsdComFunc.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "xsd_xcc_pif.h"
#include  "xsd_xreg_pif.h"
#include  "CnasCcb.h"
#include  "NasMntn.h"
#include "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_FSM_POWER_OFF_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvMsccPowerOffReq_PowerOff_Init
 ��������  : POWER_OFF״̬����ʼ��״̬�յ�ID_MSCC_XSD_POWER_OFF_REQ��Ϣ�Ĵ���?
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��3��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : DSDS NO RF RRMȥע��
*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvMsccPowerOffReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���������Ϣ */
    CNAS_XSD_SaveCurEntryMsg(ulEventType, pstMsg);

    /* CAS����TCH̬,��Ҫ�ȴ�CAS�ϱ�call release ָʾ����פ�������ػ�ȥע�� */
    if (CNAS_CCB_1X_CAS_TCH_STATE == CNAS_CCB_GetCasState())
    {
        CNAS_XSD_SetCampOnNeedFlg_PowerOff(VOS_TRUE);
    }

    /* ��RRM����ע��,RF���ú�RRM��֪ͨXSD */
    CNAS_XSD_DeRegisterRrmResourceNtf(RRM_PS_TASK_TYPE_1X_NETWORK_SEARCH);

    /* ֪ͨXCC�ػ� */
    CNAS_XSD_SndXccPowerOffReq(XCC_XSD_POWER_OFF_REASON_POWER_OFF);

    /* Ǩ�Ƶ� CNAS_XSD_POWER_OFF_STA_WAIT_XCC_POWEROFF_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XCC_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF_LEN);


    return VOS_TRUE;

}



VOS_UINT32 CNAS_XSD_RcvMsccPowerSaveReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the current FSM Entry message to the FSM Context */
    CNAS_XSD_SaveCurEntryMsg(ulEventType, pstMsg);

    CNAS_XSD_SndXccPowerOffReq(XCC_XSD_POWER_OFF_REASON_POWER_SAVE);

    /* Ǩ�Ƶ� CNAS_XSD_POWER_OFF_STA_WAIT_XCC_POWEROFF_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XCC_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXccPowerOffCnf_PowerOff_WaitXccPowerOffCnf
 ��������  : XSD��WAIT_XCC_POWER_OFF_CNF״̬�£��յ�XCC�Ĺػ�ȷ�ϻظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32��VOS_TRUE,VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��3��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvXccPowerOffCnf_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq = VOS_NULL_PTR;
    VOS_UINT8                           ucCampOnNeedFlg;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    XCC_XSD_POWER_OFF_CNF_STRU         *pstPowerOffCnf = VOS_NULL_PTR;

    /* ֹͣXSD��Ӧ��״̬������ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_XCC_POWEROFF_CNF);

    pstMsgHeader = (MSG_HEADER_STRU*)(CNAS_XSD_GetCurrFsmEntryMsgAddr()->aucMsgBuffer);

    if ((ID_MSCC_XSD_POWER_OFF_REQ == pstMsgHeader->ulMsgName)
      &&(UEPS_PID_MSCC == pstMsgHeader->ulSenderPid))
    {
        /* �˴�ʹ��NV����(�ݲ����,������NVĿ¼������������),Ĭ�ϴ�,�ر�ʱ����ԭ�������� */
        ucCampOnNeedFlg = CNAS_XSD_GetCampOnNeedFlg_PowerOff();
        if ((VOS_TRUE == CNAS_CCB_GetPowerOffCampOnCtrlFlg())
         && (VOS_TRUE == ucCampOnNeedFlg))
        {
            /* ������ڻ���ĺ����ͷ�ָʾ,ֱ�ӷ����ڲ���Ϣ����ϵͳ����״̬�� */
            if (VOS_TRUE == CNAS_XSD_GetBufCallRelIndFlg_PowerOff())
            {
                pstFreq = CNAS_XSD_GetBufCallRelFreqInfo_PowerOff();

                CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED, 1, pstFreq);

                /* ����ע����Ҫ��Ǩ��״̬;����������״̬����ǰ״̬����ѹջ */
                /* Ǩ��״̬���ȴ�XSD��ϵͳ����ظ�״̬ */
                CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XSD_SYSTEM_ACQUIRE_RSLT_CNF);

                return VOS_TRUE;
            }

            /* Ǩ��״̬���ȴ�CAS��SDָʾCNAS_XSD_POWER_OFF_STA_WAIT_CAS_SYS_DETERMIN_IND */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SYS_DETERMIN_IND);

            /* ����������ʱ��TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND, TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND_LEN);
        }
        else
        {
            /* ֪ͨXREG�ػ� */
            CNAS_XSD_SndXregPowerOffReq();

            /* Ǩ�Ƶ� CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF);
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN);
        }
    }
    else if ((ID_MSCC_XSD_POWER_SAVE_REQ == pstMsgHeader->ulMsgName)
          && (UEPS_PID_MSCC == pstMsgHeader->ulSenderPid))
    {
        pstPowerOffCnf = (XCC_XSD_POWER_OFF_CNF_STRU*)pstMsg;
        if (XCC_XSD_POWER_OFF_RESULT_SUCC == pstPowerOffCnf->enRslt)
        {
            /* Send Suspend Request to CAS */
            CNAS_XSD_SndCasSuspendReq();

            /* Set Next State to Wait CAS Suspend Cnf */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SUSPEND_CNF);

            /* Start the Wait CAS Suspend Cnf protect timer */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF, TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF_LEN);
        }
        else
        {
            CNAS_XSD_SndPowerOffRslt(CNAS_XSD_POWEROFF_REASON_POWER_SAVE, CNAS_XSD_POWEROFF_RSLT_FAIL);

            /* Quit the FSM */
            CNAS_XSD_QuitFsmL2();
        }
    }
    else
    {
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiWaitXccPowerOffCnfExpired_PowerOff_WaitXccPowerOffCnf
 ��������  : �ȴ�XCC�ػ�ȷ�ϻظ���Ϣ��ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiWaitXccPowerOffCnfExpired_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq = VOS_NULL_PTR;
    VOS_UINT8                           ucCampOnNeedFlg;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;

    /* �쳣��ӡ */
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitXccPowerOffCnfExpired_PowerOff_WaitXccPowerOffCnf:wait xcc power off expired");


    /* �˴�ʹ��NV����(�ݲ����,������NVĿ¼������������),Ĭ�ϴ�,�ر�ʱ����ԭ�������� */
    pstMsgHeader = (MSG_HEADER_STRU*)CNAS_XSD_GetCurrFsmEntryMsgAddr();

    if ((ID_MSCC_XSD_POWER_OFF_REQ == pstMsgHeader->ulMsgName)
      &&(UEPS_PID_MSCC == pstMsgHeader->ulSenderPid))
    {
        ucCampOnNeedFlg = CNAS_XSD_GetCampOnNeedFlg_PowerOff();
        if ((VOS_TRUE == CNAS_CCB_GetPowerOffCampOnCtrlFlg())
         && (VOS_TRUE == ucCampOnNeedFlg))
        {
            /* ������ڻ���ĺ����ͷ�ָʾ,ֱ�ӷ����ڲ���Ϣ����ϵͳ����״̬�� */
            if (VOS_TRUE == CNAS_XSD_GetBufCallRelIndFlg_PowerOff())
            {
                pstFreq = CNAS_XSD_GetBufCallRelFreqInfo_PowerOff();

                CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED, 1, pstFreq);

                /* ����ע����Ҫ��Ǩ��״̬;����������״̬����ǰ״̬����ѹջ */
                /* Ǩ��״̬���ȴ�XSD��ϵͳ����ظ�״̬ */
                CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XSD_SYSTEM_ACQUIRE_RSLT_CNF);

                return VOS_TRUE;
            }

            /* Ǩ��״̬���ȴ�CAS��SDָʾCNAS_XSD_POWER_OFF_STA_WAIT_CAS_SYS_DETERMIN_IND */
            CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SYS_DETERMIN_IND);

            /* ����������ʱ��TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND */
            CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND, TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND_LEN);

            return VOS_TRUE;
        }

        /* ֪ͨXREG�ػ� */
        CNAS_XSD_SndXregPowerOffReq();

        /* Ǩ�Ƶ� CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF);
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN);
    }
    else if ((ID_MSCC_XSD_POWER_SAVE_REQ == pstMsgHeader->ulMsgName)
          &&(UEPS_PID_MSCC == pstMsgHeader->ulSenderPid))
    {
        /* Send Suspend Request to CAS */
        CNAS_XSD_SndCasSuspendReq();

        /* Set Next State to Wait CAS Suspend Cnf */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_SUSPEND_CNF);

        /* Start the Wait CAS Suspend Cnf protect timer */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF, TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF_LEN);
    }
    else
    {
    }


    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXregPowerOffCnf_PowerOff_WaitXregPowerOffCnf
 ��������  : XSD��WAIT_XREG_POWEROFF_CNF״̬�£��յ�ע��ģ��ĵĹػ�ȷ�ϻظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��3��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXregPowerOffCnf_PowerOff_WaitXregPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣXSD��Ӧ��״̬������ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF);

    /* ֪ͨCAS�ػ� */
    CNAS_XSD_SndCasPowerOffReq();

    /* Ǩ�Ƶ� CNAS_XSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF, TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiWaitXregPowerOffCnfExpired_PowerOff_WaitXregPowerOffCnf
 ��������  : �ȴ�XREGģ��Ĺػ�ȷ����Ϣ����ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  :
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiWaitXregPowerOffCnfExpired_PowerOff_WaitXregPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitXregPowerOffCnfExpired_PowerOff_WaitXregPowerOffCnf:wait xreg power off expired");

    /* ֪ͨCAS�ػ� */
    CNAS_XSD_SndCasPowerOffReq();

    /* Ǩ�Ƶ� CNAS_XSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_CAS_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF, TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasPowerOffCnf_PowerOff_WaitCasPowerOffCnf
 ��������  : XSD��WAIT_Cas_POWER_OFF_CNF״̬�£��յ�Cas�Ĺػ�ȷ�ϻظ���Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32��VOS_TRUE,VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��3��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2. Date      : 2015-04-11
     Author    : a00295761
     Content   : Modified the send internal power off result function

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvCasPowerOffCnf_PowerOff_WaitCasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Receive Msg!");

    /* ֹͣXSD��Ӧ��״̬������ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_POWEROFF_CNF);

    /* ֪ͨMSCC�ػ���� */
    CNAS_XSD_SndMsccPowerOffCnf();

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_XSD_SndPowerOffRslt(CNAS_XSD_POWEROFF_RSLT_SUCCESS,CNAS_XSD_POWEROFF_REASON_POWER_OFF);

    /* �ػ���ɣ��˳����״̬��*/
    CNAS_XSD_QuitFsmL2();

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf
 ��������  : �ȴ������Ĺػ�ȷ����Ϣʱ����ʱ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2. Date      : 2015-04-11
     Author    : a00295761
     Content   : Modified the send internal power off result function


*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasPowerOffCnfExpired_PowerOff_WaitCasPowerOffCnf:wait cas power off expired");

    /* ֪ͨMSCC�ػ���� */
    CNAS_XSD_SndMsccPowerOffCnf();

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    CNAS_XSD_SndPowerOffRslt(CNAS_XSD_POWEROFF_RSLT_SUCCESS,CNAS_XSD_POWEROFF_REASON_POWER_OFF);

    /* �ػ���ɣ��˳����״̬��*/
    CNAS_XSD_QuitFsmL2();

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitCasSysDeterminInd
 ��������  : �ȴ�CAS��system determinָʾ״̬�յ�CAS��system determin��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  :
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitCasSysDeterminInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDeterminInd = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq;

    pstSysDeterminInd = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    /* ֹͣ��ʱ�� TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SYSTEM_DETERMIN_IND);

    /* �����ͷ� */
    if (CAS_CNAS_1X_SD_RELEASE_IND == pstSysDeterminInd->enSdReason)
    {
        /* ��determin ind��Ϣ�����system id */
        stFreq.enBandClass = pstSysDeterminInd->stCurChannelInfo.usBandClass;
        stFreq.usChannel   = pstSysDeterminInd->stCurChannelInfo.usChannel;

        CNAS_XSD_SndInternalSysAcqReq(CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED, 1, &stFreq);

        /* ����ע����Ҫ��Ǩ��״̬;����������״̬����ǰ״̬����ѹջ */
        /* Ǩ��״̬���ȴ�XSD��ϵͳ����ظ�״̬ */
        CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XSD_SYSTEM_ACQUIRE_RSLT_CNF);

        return VOS_TRUE;
    }

    /* ֪ͨXREG�ػ� */
    CNAS_XSD_SndXregPowerOffReq();

    /* Ǩ�Ƶ� CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvTiWaitCasSysDeterminIndExpired_PowerOff_WaitCasSysDeterminInd
 ��������  : �ȴ�CAS��system determinָʾ�ı�����ʱ����ʱ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  :
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvTiWaitCasSysDeterminIndExpired_PowerOff_WaitCasSysDeterminInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    CNAS_WARNING_LOG(UEPS_PID_XSD, "CNAS_XSD_RcvTiWaitCasSysDeterminIndExpired_PowerOff_WaitCasSysDeterminInd:wait cas system determin ind expired");

    /* ֪ͨXREG�ػ� */
    CNAS_XSD_SndXregPowerOffReq();

    /* Ǩ�Ƶ� CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXsdSystemAcquiredRsltCnf_PowerOff_WaitXsdSystemAcquireRsltCnf
 ��������  : �ȴ�XSD��ϵͳ������״̬�յ�XSD��ϵͳ�������Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  :
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XSD_RcvXsdSystemAcquiredRsltCnf_PowerOff_WaitXsdSystemAcquireRsltCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER);

    /* ֪ͨXREG�ػ� */
    CNAS_XSD_SndXregPowerOffReq();

    /* Ǩ�Ƶ� CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF״̬,������������ʱ��TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF */
    CNAS_XSD_SetCurrFsmState(CNAS_XSD_POWER_OFF_STA_WAIT_XREG_POWEROFF_CNF);
    CNAS_XSD_StartTimer(TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF, TI_CNAS_XSD_WAIT_XREG_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvInterXsdSystemAcquiredReq_PowerOff_WaitXsdSystemAcquireRsltCnf
 ��������  : �ȴ�XSD��ϵͳ������״̬�յ�XSD��ϵͳ��������״̬��
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  :
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��01��13��
    ��    ��   : m00312079
    �޸�����   : ֻ����Call Release�����½���״̬��

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvInterXsdSystemAcquiredReq_PowerOff_WaitXsdSystemAcquireRsltCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU         *pSysAcqReq;

    pSysAcqReq = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU *)pstMsg;

    /* IDLE״̬��Ƶ�����˺��������ǲ����CNAS_XSD_FSM_SYS_ACQ״̬����ֻ����Call
       Release�»����CNAS_XSD_FSM_SYS_ACQ״̬�� */
    if (CNAS_XSD_SYS_ACQ_SCENE_CALL_RELEASED == pSysAcqReq->enSysAcqScene)
    {
        /* ������Ƶ��Դ */
        CNAS_XSD_SndCasBeginSessionNotify(CNAS_CAS_1X_SESSION_TYPE_NETWORK_SEARCH);

        CNAS_XSD_InitFsmL2(CNAS_XSD_FSM_SYS_ACQ);

        /* ֹͣ������ʱ�� */
        CNAS_XSD_StartTimer(TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER,
                            TI_CNAS_XSD_POWEROFF_CAMP_ON_PROTECT_TIMER_LEN);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvXccDeregisterInd_PowerOff_WaitXccPowerOffCnf
 ��������  : �ȴ�XCC�Ĺػ��ظ�״̬�յ�XCC�Ĺػ�ȥע��ָʾ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��14��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvXccDeregisterInd_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_XSD_DEREGISTER_IND_STRU        *pstDeregInd = VOS_NULL_PTR;

    pstDeregInd = (XCC_XSD_DEREGISTER_IND_STRU *)pstMsg;

    if (XSD_XCC_DEREGISTER_REASON_POWEROFF == pstDeregInd->enCause)
    {
        /* �յ�XCC�Ĺػ�ȥע��ָʾ��,XSD����Ҫ�ڹػ�ʱפ��,������ */
        CNAS_XSD_SetCampOnNeedFlg_PowerOff(VOS_FALSE);

        CNAS_XSD_SndXregDeregisterInd(XSD_XREG_DEREGISTER_REASON_POWEROFF);
    }

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitXccPowerOffCnf
 ��������  : �ȴ�XCC�Ĺػ��ظ�״̬�յ�CAS��system determine ind�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��21��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvCasSysDeterminInd_PowerOff_WaitXccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Ϊ��������CAS�ϱ�������ָֹʾ��system determine��ʱ��,�˴�Ҳ����
       �յ�����Ϣ�Ĵ���,���Դ浽��������
    */
    CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU                   *pstSysDetermin = VOS_NULL_PTR;
    CNAS_PRL_FREQENCY_CHANNEL_STRU                          stFreq;

    pstSysDetermin = (CAS_CNAS_1X_SYSTEM_DETERMIN_IND_STRU *)pstMsg;

    if (CAS_CNAS_1X_SD_RELEASE_IND != pstSysDetermin->enSdReason)
    {
        return VOS_TRUE;
    }

    CNAS_XSD_SetBufCallRelIndFlg_PowerOff(VOS_TRUE);

    stFreq.enBandClass = pstSysDetermin->stCurChannelInfo.usBandClass;
    stFreq.usChannel   = pstSysDetermin->stCurChannelInfo.usChannel;

    CNAS_XSD_SaveBufCallRelFreqInfo_PowerOff(&stFreq);

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvCasSuspendCnf_PowerOff_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* Stop the Wait CAS Suspend Cnf protect timer */
    CNAS_XSD_StopTimer(TI_CNAS_XSD_WAIT_CAS_SUSPEND_CNF);

    /* Send Internal Power Sav CNf message */
    CNAS_XSD_SndPowerOffRslt(CNAS_XSD_POWEROFF_RSLT_SUCCESS, CNAS_XSD_POWEROFF_REASON_POWER_SAVE);

    /* Quit the FSM */
    CNAS_XSD_QuitFsmL2();

    return VOS_TRUE;
}




VOS_UINT32 CNAS_XSD_RcvTiWaitCasSuspendCnfExpired_PowerOff_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_REBOOT_INFO_STRU               stCnasRebootInfo;

    /* Construct the Soft Reboot Info */
    NAS_MEM_SET_S(&stCnasRebootInfo, sizeof(stCnasRebootInfo), 0x0, sizeof(CNAS_REBOOT_INFO_STRU));
    stCnasRebootInfo.enRebootScene = CNAS_REBOOT_SCENE_TI_XSD_WAIT_CAS_SUSPEND_CNF_EXPIRED;
    stCnasRebootInfo.ulPid         = UEPS_PID_XSD;
    stCnasRebootInfo.ulFsmId       = CNAS_XSD_GetCurrFsmId();
    stCnasRebootInfo.ulFsmState    = CNAS_XSD_GetFsmTopState();

    /* XSD performs soft reboot */
    CNAS_SoftReboot(stCnasRebootInfo);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_RcvRpmStatusInd_PowerOff_WaitCasSuspendCnf
 ��������  : �յ�ID_RRM_PS_STATUS_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��10��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XSD_RcvRrmStatusInd_PowerOff_WaitCasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����Ϣ�����ڻ����ڴ���� */
    CNAS_XSD_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    return VOS_TRUE;

}


/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



