/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregFsmMain.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��07��03��
  ��������   : 1X reg L1��״̬�����յ����¼�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��03��
    ��    ��   : l60609
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXregCtx.h"
#include  "CnasXregFsmMain.h"
#include  "CnasXregFsmMainTbl.h"
#include  "CnasXregSndXsd.h"
#include  "CnasMntn.h"
#include  "CnasXregProcess.h"
#include  "CnasXregSndInternalMsg.h"
#include  "NVIM_Interface.h"
#include  "CnasXregListProc.h"
#include  "CnasCcb.h"
#include  "CnasXregSndCas.h"
#include  "CnasXregTimer.h"
#include  "CnasTimerMgmt.h"
#include  "CnasXregMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvStartReq_Null
 ��������  : ��null״̬�յ���������ID_XSD_XREG_START_REQ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��08��
   ��    ��   : l60609
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvStartReq_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_ClearGlobal();

    /* ����L2״̬�� */
    CNAS_XREG_InitFsmL2(CNAS_XREG_FSM_SWITCH_ON);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvSwitchOnRslt_Null
 ��������  : ��null״̬�յ���������ID_XSD_XREG_START_REQ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��07��08��
   ��    ��   : l60609
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvSwitchOnRslt_Null(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֱ�ӻظ�Start Cnf(Succ) */
    CNAS_XREG_SndXsdStartCnf(XREG_XSD_START_RESULT_SUCC);

    /* �е�����δע��״̬ */
    CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_UNREG);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvStartReq_UnReg
 ��������  : ��UnReg״̬�յ��ػ�����ID_XSD_XREG_START_REQ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��23��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvStartReq_UnReg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ѿ�����ֱ�ӻظ�Start Cnf(Succ) */
    CNAS_XREG_SndXsdStartCnf(XREG_XSD_START_RESULT_SUCC);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvAccessInd_L1Main
 ��������  : CAS���͵�ע����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : ����
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvAccessInd_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_MSG_ACCESS_RSLT_IND_STRU    *pstMsgData;

    pstMsgData = (CAS_CNAS_1X_MSG_ACCESS_RSLT_IND_STRU *)pstMsg;

    /* ��¼ע����,CAS_CNAS_1X_REGISTRATION_TYPE_BUTT�Ѿ������Traffic Channel Registered. */
    CNAS_XREG_RecordRegRslt((CAS_CNAS_1X_REGISTRATION_TYPE_BUTT + 1) + pstMsgData->enMsgAccessInfo, VOS_OK);

    /* ע��ɹ� */
    if (VOS_TRUE == pstMsgData->ucAcsSuccFlag)
    {
        if ((CAS_CNAS_1X_SUCC_ACCESS_ORIG == pstMsgData->enMsgAccessInfo)
         || (CAS_CNAS_1X_SUCC_ACCESS_PAGING_RSP == pstMsgData->enMsgAccessInfo))
        {
            CNAS_XREG_GetRegStateAddr()->enRegTypeMntn = NAS_OM_CDMA_IMPLICIT_REGISTRATION;

            CNAS_XREG_SndOmRegTypeReportInd(NAS_OM_CDMA_IMPLICIT_REGISTRATION);

            CNAS_XREG_RegSuccProc();

            /* �е���ע��״̬ */
            CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_REGED);

            return VOS_TRUE;
        }

        /* ��ע��ɹ���Ϣ���͸�XSD */
        if (CAS_CNAS_1X_SUCC_ACCESS_REG == pstMsgData->enMsgAccessInfo)
        {
            CNAS_XREG_SndXsdRegSuccessInd();

            return VOS_TRUE;
        }
    }

    if ((VOS_FALSE == pstMsgData->ucAcsSuccFlag)
     || (CAS_CNAS_1X_SUCC_ACCESS_OTHER_MSG == pstMsgData->enMsgAccessInfo))
    {
        CNAS_XREG_RegFailProc();
    }
    else
    {
        ;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvRegedDataInd_L1Main
 ��������  : CAS���͵���ע��DSCH������Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : ף�
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvRegedDataInd_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschData;

    pstDschData = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;

    if (CAS_CNAS_1X_RX_TCH_REGISTRATION_MSG != pstDschData->enDschMsgType)
    {
        return VOS_TRUE;
    }

    if (VOS_OK != CNAS_XREG_DSCHDataTrans(pstDschData))
    {
        return VOS_TRUE;
    }

    /* �е���ע��״̬ */
    CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_REGED);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvRegReq_L1Main
 ��������  : �ڲ���Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : ����
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvRegReq_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_REQ_STRU                *pstRegReq;
    CAS_CNAS_1X_REGISTRATION_TYPE_ENUM_UINT8    enRegType;
    VOS_UINT8                                   ucPowerOffDeregFlg;
    VOS_UINT8                                   ucNoCardMode;

    pstRegReq = (CNAS_XREG_XREG_REG_REQ_STRU*)pstMsg;

    ucPowerOffDeregFlg = CNAS_XREG_GetPowerOffDeregFlg();

    /* �ж��Ƿ�����ػ�ע������ */
    if (CAS_CNAS_1X_POWER_DOWN_REGISTRATION == pstRegReq->enRegType)
    {
        if ((VOS_FALSE == CNAS_XREG_PowerDownCheck())
         || (VOS_TRUE  == ucPowerOffDeregFlg))
        {
            CNAS_XREG_ProcPowerOffReq();

            return VOS_TRUE;
        }
    }
    else if (CAS_CNAS_1X_REGISTRATION_TYPE_BUTT == pstRegReq->enRegType)
    {
        /* �ж��Ƿ�����ע������ */
        enRegType = CNAS_XREG_IdleRegCheck();

        if (CAS_CNAS_1X_REGISTRATION_TYPE_BUTT == enRegType)
        {
            return VOS_TRUE;
        }

        /* ��ע�����ͱ��浽��Ϣ������ */
        pstRegReq->enRegType = enRegType;
    }
    else
    {
        /* For pclint */;
    }

    ucNoCardMode = CNAS_XREG_GetNoCardMode();

    /* �п�������޿�ģʽ����ʱ��ע�� */
    if ((CNAS_CCB_CARD_STATUS_ABSENT != CNAS_CCB_GetCsimCardStatus())
     || (VOS_TRUE == ucNoCardMode))
    {
        /* ֪ͨ�����Ự��ʼ */
        CNAS_XREG_SndCasBeginSessionNtf();

        /* ����L2 REGING״̬�� */
        CNAS_XREG_InitFsmL2(CNAS_XREG_FSM_REGING);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvRegCnf_L1Main
 ��������  : �ڲ���Ϣ�ظ�
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvRegCnf_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_XREG_REG_CNF_STRU        *pstReqCnf;
    CNAS_XREG_REGSTATE_STRU            *pstRegState;
    NAS_OM_CDMA_REG_TYPE_ENUM_UINT32    enRegTypeMntn;

    pstReqCnf = (CNAS_XREG_XREG_REG_CNF_STRU*)pstMsg;

    pstRegState = CNAS_XREG_GetRegStateAddr();

    /* ֪ͨ�����Ự���� */
    CNAS_XREG_SndCasEndSessionNtf();

    /* ���沢�ϱ���ά�ɲ��ע������ */
    enRegTypeMntn = CNAS_XREG_TransferRegType(pstReqCnf->enRegType);
    pstRegState->enRegTypeMntn = enRegTypeMntn;
    CNAS_XREG_SndOmRegTypeReportInd(enRegTypeMntn);

    /* ������NORF���д��� */
    if (CNAS_XREG_REG_RESULT_NORF == pstReqCnf->enRegResult)
    {
        /* ���浱ǰ��ע������ */
        pstRegState->enCurRegType = pstReqCnf->enRegType;

        /* ע��RF��Դ���� */
        CNAS_XREG_SndRrmRegisterInd(RRM_PS_TASK_TYPE_1X_REGISTER);

        /* �е�Registered״̬ */
        CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_UNREG);

        return VOS_TRUE;
    }

    /* �ػ�������ʱ����ʱ + ��ǰΪ�ػ�ע����Ҫ�������� */
    if ((CAS_CNAS_1X_POWER_DOWN_REGISTRATION == pstReqCnf->enRegType)
     || (CNAS_XREG_REG_RESULT_PWROFF == pstReqCnf->enRegResult))
    {
        CNAS_XREG_ProcPowerOffReq();

        return VOS_TRUE;
    }

    /* ȥע��RF��Դ���� */
    CNAS_XREG_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_1X_REGISTER);

    if (CNAS_XREG_REG_RESULT_SUCCESS == pstReqCnf->enRegResult)
    {
        /* �е�Registered״̬ */
        CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_REGED);
    }
    else
    {
        /* �е� UN REG ״̬ */
        CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_UNREG);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_WriteNvimInfo_PowerOff
 ��������  : ����״̬�¶�ȡNV������.
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��05��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_WriteNvimInfo_PowerOff(VOS_VOID)
{
    VOS_UINT32                          ulLastSci;

    ulLastSci = (VOS_UINT32)CNAS_XREG_GetLastSciValue();

    if (NV_OK != NV_Write(en_NV_Item_1X_LAST_SCI, &ulLastSci, sizeof(ulLastSci)))
    {
        CNAS_ERROR_LOG(UEPS_PID_XREG, "CNAS_XREG_WriteNvimInfo_PowerOff:NV_Write Failed");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ProcPowerOffReq
 ��������  : �ػ����̴���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XREG_ProcPowerOffReq(VOS_VOID)
{
    /* �ػ�ʱ�رձ�����ʱ�� */
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_PWROFF_ESTCNF_PT, 0);
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ESTCNF_PT, 0);
    CNAS_StopTimer(UEPS_PID_XREG, TI_CNAS_XREG_TIMER_ABORTCNF_PT, 0);

    /* ȥע����� */
    CNAS_XREG_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_1X_REGISTER);

    /* ����NV��Ϣ */
    CNAS_XREG_WriteNvimInfo_PowerOff();

    /* �ظ�POWEROFF��Ϣ */
    CNAS_XREG_SndXsdPowerOffCnf();

    /* ���ȫ�ֱ��� */
    CNAS_XREG_ClearGlobal();

    /* �е�NULL״̬ */
    CNAS_XREG_SetCurrFsmState(CNAS_XREG_L1_STA_NULL);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RcvPwrOffTimeOut_L1Main
 ��������  : �ػ���ʱ��ʱ������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : ganlan
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RcvPwrOffTimeOut_L1Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XREG_ProcPowerOffReq();

    return VOS_TRUE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



