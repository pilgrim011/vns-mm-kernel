/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccMainCtrl.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��09��13��
  ��������   : 1X CC(call control)���ش�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��13��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "PsCommonDef.h"
#include  "CnasXccMainCtrl.h"
#include  "CnasXccInstanceMgmt.h"
#include  "NasFsm.h"
#include  "xsd_xcc_pif.h"
#include  "CnasXccSndXsd.h"
#include  "CnasXccSndInternalMsg.h"
#include  "CnasXccComFunc.h"
#include  "CnasXccCtx.h"
#include  "CnasCcb.h"
#include  "CnasXccSndXcall.h"
#include  "CnasXccFsmMainTbl.h"
#include  "CnasXccFsmMoCallingTbl.h"
#include  "CnasXccFsmMtCallingTbl.h"
#include  "CnasXccSndCas.h"
#include  "CnasMntn.h"
#include  "xcc_aps_pif.h"
#include  "xcc_sms_pif.h"
#include  "CnasXccSndAps.h"
#include  "CnasXccSndCsms.h"
#include  "CnasXccSndXcall.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "xcc_mma_pif.h"
#include  "CnasXccSndMma.h"
#include "CnasXccSndXpds.h"
#include  "xcc_xpds_pif.h"
#include "CnasXccProcNvim.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_MAIN_CTRL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/* ĿǰXģ�Ĳ��ǵ�������ģ�������ڱ���ʱ������TAF�ֵĴ��� */
extern VOS_UINT8   TAF_SDC_GetCsCallExistFlg(VOS_VOID);

/*****************************************************************************
  2 ���Ͷ���
*****************************************************************************/
typedef VOS_UINT32 (*CNAS_XCC_MAIN_CTRL_PROC_FUNC)(VOS_UINT32                    ulEventType,
                                                   struct MsgCB                 *pstMsg);

typedef struct
{
    VOS_UINT32                          ulMsgEvtType;
    CNAS_XCC_MAIN_CTRL_PROC_FUNC        pfMainCtrlProcFun;
} CNAS_XCC_MAIN_CTRL_PROC_STRU;

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/
CNAS_XCC_MAIN_CTRL_PROC_STRU g_astCnasXccMainCtrlProcTab[] = {
    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_XCC_START_REQ,
                     CNAS_XCC_ProcessXsdStartReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_XCC_POWER_OFF_REQ,
                     CNAS_XCC_ProcessXsdPowerDownReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ORIG_CALL_REQ,
                     CNAS_XCC_ProcessXcallOrigCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_ORIG_DATA_CALL_REQ,
                     CNAS_XCC_ProcessApsOrigDataCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_ORIG_SMS_CALL_REQ,
                     CNAS_XCC_ProcessSmsOrigCallReq_MainCtrl),
    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_ORIG_AGPS_CALL_REQ,
                     CNAS_XCC_ProcessXpdsOrigCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_HANGUP_CALL_REQ,
                     CNAS_XCC_ProcessXcallHangupCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_HANGUP_DATA_CALL_REQ,
                     CNAS_XCC_ProcessApsHangupDataCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_END_SMS_CALL_REQ,
                     CNAS_XCC_ProcessSmsHangupCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_END_AGPS_CALL_REQ,
                     CNAS_XCC_ProcessXpdsHangupCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_ProcessXcallAnswerCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_ANSWER_DATA_CALL_REQ,
                     CNAS_XCC_ProcessApsAnswerDataCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_ProcessSmsAnswerCallReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_ProcessXpdsAnswerCallReq_MainCtrl),
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_PAGING_IND,
                     CNAS_XCC_ProcessCas1xPagingInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_IND,
                     CNAS_XCC_ProcessCas1xDschDataInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_POWEROFF_REL_ORDER_SND_NTF,
                     CNAS_XCC_ProcessCas1xReleaseOrderInd_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_SEND_FLASH_REQ,
                     CNAS_XCC_ProcessXcallSendFlashReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                     CNAS_XCC_ProcessCas1xDschDataCnf_MainCtrl),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK,
                     CNAS_XCC_RcvTiProtectFlashCnfL2Ack_MainCtrl),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK,
                     CNAS_XCC_RcvTiProtectBurstDTMFCnfL2Ack_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_SEND_BURST_DTMF_REQ,
                     CNAS_XCC_ProcessXcallSendBurstDTMFReq_MainCtrl),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK,
                     CNAS_XCC_RcvTiWaitEmergencyCallFlashCnfL2Ack_MainCtrl),


    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_ProcessCas1xCallTerminateInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_REL_IND,
                     CNAS_XCC_ProcessCas1xCallRelInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_ProcessXccPowerDownInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CSCH_DATA_IND,
                     CNAS_XCC_ProcessCas1xCschDataInd_MainCtrl),


    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_NDSS_RECORD_DAILED_DIGITS_IND,
                     CNAS_XCC_ProcessCas1xNdssRecordDialedDigitsInd_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSD,
                     ID_XSD_XCC_NDSS_RESULT_IND,
                     CNAS_XCC_ProcessXsdNdssResultInd_MainCtrl),


    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_PZID_INFO_NTF,
                     CNAS_XCC_ProcessApsPzidInfoNtf_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_CALL_STATE_IND,
                     CNAS_XCC_ProcessXCallStateInd_MainCtrl),

#if 0
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_RESERVE_SR_ID_NTF,
                     CNAS_XCC_ProcessReserveSrIdNtf_MainCtrl),
#endif

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_SEND_CONT_DTMF_REQ,
                     CNAS_XCC_ProcessXcallSendContDTMFReq_MainCtrl),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK,
                     CNAS_XCC_RcvTiProtectContDTMFCnfL2Ack_MainCtrl),

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ECC_SERVICE_REQ,
                     CNAS_XCC_ProcessXcallEccServiceReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_ECC_SERVICE_CNF,
                     CNAS_XCC_ProcessCas1xEccServiceCnf_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_TCH_ASSIGN_CMPL_IND,
                     CNAS_XCC_ProcessCas1xTchAssignCmplInd_MainCtrl),
#endif

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_PRIVACY_MODE_SET_REQ,
                     CNAS_XCC_ProcessXcallPrivacyModeSetReq_MainCtrl),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_PRIVACY_MODE_QRY_REQ,
                     CNAS_XCC_ProcessXcallPrivacyModeQryReq_MainCtrl),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_LONG_CODE_TRANSITION_IND,
                     CNAS_XCC_ProcessXcallLongCodeTransitionInd_MainCtrl),
};

/*****************************************************************************
  4 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XCC_IsSending1xCallRelReqAllowed
 ��������  : check��ǰcall instanceʵ�嵱ǰ״̬��ID��״̬, ȷ���Ƿ���Ҫ����
             1X call release����
 �������  : pstFsmCtx -- FSM������
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ������
             VOS_FALSE -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XCC_IsSending1xCallRelReqAllowed(
    CNAS_XCC_FSM_CTX_STRU               *pstFsmCtx
)
{
    VOS_UINT8                           ulRslt;

    ulRslt = VOS_TRUE;

    switch (pstFsmCtx->enFsmId)
    {
        case CNAS_XCC_FSM_L1_MAIN:
            if (CNAS_XCC_L1_STA_ENDING == pstFsmCtx->ulState)
            {
                /* ��ending״̬������Ҫ����release request */
                ulRslt = VOS_FALSE;
            }
            break;

        case CNAS_XCC_FSM_MO_CALLING:
            if (CNAS_XCC_MO_CALLING_STA_WAIT_APS_SUSPEND_RSP == pstFsmCtx->ulState)
            {
                /* ��ʱ��·δ����������Ҫ����release request */
                ulRslt = VOS_FALSE;
            }
            break;

        case CNAS_XCC_FSM_MT_CALLING:
            if (CNAS_XCC_MT_CALLING_STA_WAIT_APS_SUSPEND_RSP == pstFsmCtx->ulState)
            {
                /* ��ʱ��·δ����������Ҫ����release request */
                ulRslt = VOS_FALSE;
            }
            break;

        default:
            ulRslt = VOS_FALSE;
            break;
    }

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ReturnPaginMsgActionType
 ��������  : ���Ѱ����Ϣ�Ƿ�������
 �������  : pstFsmCtx -- FSM������
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ������
             VOS_FALSE -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XCC_IsPaginMsgAllowed(
    CAS_CNAS_1X_PAGING_IND_STRU        *pstMsg,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;

    /* ֧�ֲ����Ļ���ָʾ����Ҫ��ϣ������� */
    *pucAbortFlag  = VOS_FALSE;
    *pucAbortIndex = 0;

    CNAS_XCC_ConvertSoToServiceType(pstMsg->enSo, &enServiceType);

    /* paging��Ϣ������SO, ����Ƿ���ͬ���͵ĺ����ڷ���������ڣ�����paging */
    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(enServiceType, pucAbortIndex))
    {

        return VOS_FALSE;
    }

    if (VOS_FALSE == CNAS_XCC_IsConcurrentSupported())
    {
        return CNAS_XCC_ProcessPagingCollision(enServiceType, pucAbortIndex, pucAbortFlag);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_IsXcallOrigCallReqAllowed
 ��������  : ������������Ϣ�Ƿ������������ͨ��pucAbortFlag�����Ƿ���ֹ
             ��ǰ�������У�����������ֹ��������
 �������  : pstMsg -- XCALL ORIG CALL REQ��Ϣ��ַ
 �������  : pucAbortIndex -- ������ֹ��������call instance����
             pucAbortFlag  -- �����Ƿ���Ҫ��ֹ��������

 �� �� ֵ  : VOS_TRUE  -- ������
             VOS_FALSE -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x��Ŀ����5�޸�
*****************************************************************************/
TAF_XCC_CAUSE_ENUM_UINT32 CNAS_XCC_IsXcallOrigCallReqAllowed(
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstMsg,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
)
{
    /* ֧�ֲ����Ļ���ָʾ����Ҫ��ϣ������� */
    *pucAbortFlag  = VOS_FALSE;
    *pucAbortIndex = 0;

    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
    {
        if (VOS_FALSE == pstMsg->ucIsEmergencyCall)
        {
            return TAF_XCC_CAUSE_ABORT;
        }

        /* if mt voice call instance exist (mo vocice call exist,uplayer will reject the emergency call request af first),
           check if we could send a emc flash message or not.
           if not, send orig cnf fail with one special cause so that the uplayer could retry this call
        */
        if (VOS_FALSE == CNAS_XCC_IsSendingEmcFlashMsgAllowed_MainCtrl(*pucAbortIndex))
        {
            return TAF_XCC_CAUSE_EMERGENCY_CALL_ABORT;
        }

        return TAF_XCC_CAUSE_SUCCESS;
    }

    if (VOS_FALSE == CNAS_XCC_IsConcurrentSupported())
    {
        /* ��ǰ�������Ϊ���ڻ��ز��Ե�ʱ�򣬲��ܴ������� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_LOOPBACK, pucAbortIndex))
        {
            return TAF_XCC_CAUSE_CALL_NOT_ALLOWED;
        }

        /* �������ݺ������У��յ���������������� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            return TAF_XCC_CAUSE_SUCCESS;
        }

        /* ����SMS�������У��յ���������������� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            return TAF_XCC_CAUSE_SUCCESS;
        }

        /* ��AGPS�������У��յ���������������� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            return TAF_XCC_CAUSE_SUCCESS;
        }
    }

    return TAF_XCC_CAUSE_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_IsApsOrigDataCallReqAllowed
 ��������  : ������ݺ���������Ϣ�Ƿ������������ͨ��pucAbortFlag�����Ƿ���ֹ
             ��ǰ�������У�����������ֹ��������
 �������  : pstMsg -- XCALL ORIG CALL REQ��Ϣ��ַ
 �������  : pucAbortIndex -- ������ֹ��������call instance����
             pucAbortFlag  -- �����Ƿ���Ҫ��ֹ��������

 �� �� ֵ  : TAF_XCC_CAUSE_SUCCESS   -- ������
             ��TAF_XCC_CAUSE_SUCCESS -- ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_XCC_CAUSE_ENUM_UINT32 CNAS_XCC_IsApsOrigDataCallReqAllowed(VOS_VOID)
{
    VOS_UINT8                           ucIndex;

    if (CNAS_CCB_GetPRevInUse() < P_REV_IN_USE_6)
    {
        return TAF_XCC_CAUSE_PROTOTAL_REV_NOT_SUPPORT;
    }

    /* ͬ�����ͺ��г�ͻ��������/���г�ͻ */
    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, &ucIndex))
    {
        /* ���ȱ��У��ɸú��������߻ظ���� */
        return TAF_XCC_CAUSE_ABORT;
    }

    if (VOS_FALSE == CNAS_XCC_IsConcurrentSupported())
    {
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_LOOPBACK, &ucIndex))
        {
            return TAF_XCC_CAUSE_CALL_NOT_ALLOWED;
        }

        /* �������й����У��յ��������ݺ���ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
        {
            return TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* ���ű��й����У��յ��������ݺ���ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, &ucIndex))
        {
            return TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* ��AGPS�������У��յ���������������� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, &ucIndex))
        {
            return TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }
    }

    return TAF_XCC_CAUSE_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_IsCsmsOrigCallReqAllowed
 ��������  : �����ź���������Ϣ�Ƿ������������ͨ��pucAbortFlag�����Ƿ���ֹ
             ��ǰ�������У�����������ֹ��������
 �������  : pstMsg -- XCALL ORIG CALL REQ��Ϣ��ַ
 �������  : pucAbortIndex -- ������ֹ��������call instance����
             pucAbortFlag  -- �����Ƿ���Ҫ��ֹ��������

 �� �� ֵ  : TAF_XCC_CAUSE_SUCCESS   -- ������
             ��TAF_XCC_CAUSE_SUCCESS -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_XCC_CAUSE_ENUM_UINT32 CNAS_XCC_IsCsmsOrigCallReqAllowed(
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU    *pstOrigDataCallReq,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtx = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    /* ֧�ֲ����Ļ���ָʾ����Ҫ��ϣ������� */
    *pucAbortFlag  = VOS_FALSE;
    *pucAbortIndex = 0;

    pstXccCtx = CNAS_XCC_GetCtxAddr();
    enCause   = TAF_XCC_CAUSE_SUCCESS;

    /* ͬ�����ͺ��г�ͻ���� */
    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
    {
        /* ���ȱ��У��ɸú��������߻ظ���� */
        enCause = TAF_XCC_CAUSE_ABORT;
    }

    if (VOS_FALSE == CNAS_XCC_IsConcurrentSupported())
    {
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_LOOPBACK, pucAbortIndex))
        {
            return TAF_XCC_CAUSE_CALL_NOT_ALLOWED;
        }

        /* �������й����У��յ����ж��ţ�ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* ����ҵ�񱻽й����У��յ����ж��ţ�ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* ��AGPS�������У��յ���������������� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }
    }

    /*�����ǰSO�Ѿ�Э����ɣ�����ԭ��ֵ */
    if (TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        if (VOS_TRUE == pstXccCtx->astFsmEntity[*pucAbortIndex].stCallInfoCtx.ucIsSoNegCmplt)
        {
            CNAS_XCC_ConvertSoToServiceType(pstXccCtx->astFsmEntity[*pucAbortIndex].stCallInfoCtx.enCurrentSo, &enServiceType);

            if (CNAS_XCC_SERVICE_TYPE_SMS == enServiceType)
            {
                enCause = TAF_XCC_CAUSE_MT_SMS_IN_TCH;
            }
            else
            {
                enCause = TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH;
            }
        }
    }

    return enCause;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_IsXpdsOrigCallReqAllowed
 ��������  : ���AGPS����������Ϣ�Ƿ������������ͨ��pucAbortFlag�����Ƿ���ֹ
             ��ǰ�������У�����������ֹ��������
 �������  : pstMsg -- XPDS_XCC_ORIG_AGPS_CALL_REQ��Ϣ��ַ
 �������  : pucAbortIndex -- ������ֹ��������call instance����
             pucAbortFlag  -- �����Ƿ���Ҫ��ֹ��������

 �� �� ֵ  : TAF_XCC_CAUSE_SUCCESS   -- ������
             ��TAF_XCC_CAUSE_SUCCESS -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��02��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_XCC_CAUSE_ENUM_UINT32 CNAS_XCC_IsXpdsOrigCallReqAllowed(
    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU   *pstOrigDataCallReq,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtx = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    /* ֧�ֲ����Ļ���ָʾ����Ҫ��ϣ������� */
    *pucAbortFlag  = VOS_FALSE;
    *pucAbortIndex = 0;

    pstXccCtx = CNAS_XCC_GetCtxAddr();
    enCause   = TAF_XCC_CAUSE_SUCCESS;

    /* ͬ�����ͺ��г�ͻ���� */
    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
    {
        /* ���ȱ��У��ɸú��������߻ظ���� */
        enCause = TAF_XCC_CAUSE_ABORT;
    }

    if (VOS_FALSE == CNAS_XCC_IsConcurrentSupported())
    {
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_LOOPBACK, pucAbortIndex))
        {
            return TAF_XCC_CAUSE_CALL_NOT_ALLOWED;
        }

        /* �������й����У��յ�AGPS���У�ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* ����ҵ�񱻽й����У��յ�AGPS���У�ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }

        /* �ڶ��ź������У��յ�AGPS���У���� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
        {
            enCause = TAF_XCC_CAUSE_CCS_NOT_SUPPORT;
        }
    }

    if (TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        if (VOS_TRUE == pstXccCtx->astFsmEntity[*pucAbortIndex].stCallInfoCtx.ucIsSoNegCmplt)
        {
            enCause = TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH;
        }
    }

    return enCause;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_IsPrivacyModeAllowedToSend_MainCtrl
 ��������  : �Ƿ�������privacy mode��CAS

 �������  : enPrivacyMode -- �û�����privacy mode

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ������
             VOS_FALSE -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_IsPrivacyModeAllowedToSend_MainCtrl(
    XCALL_XCC_PRIVACY_MODE_ENUM_UINT8                       enPrivacyMode
)
{
    CNAS_XCC_CTX_STRU                                      *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;

    /* ��鵱ǰ�Ƿ��м����������� */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_FALSE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* �����ǰ״̬������L1 MAIN״̬����conversation״̬����Ҫ����privacy mode */
    if ((CNAS_XCC_FSM_L1_MAIN         != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        return VOS_FALSE;
    }

    /* ����CASԼ����ֻ����SOЭ����ɺ󣬲ſɷ��� */
    if (VOS_FALSE == pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSoNegCmplt)
    {
        return VOS_FALSE;
    }

    /* �����ǰ���û������privacy mode����Э�̺��privacy mode, ����Ҫ���� */
    if (enPrivacyMode == pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.enNegPrivacyMode)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq
 ��������  : ��Send Flash Req�����еȴ�L2 ACK״̬�£�����绰�Ҷ�(�����Ҷϻ�����Ҷ�)
 �������  : ucIndex
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��12��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�

*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait)
    {
        return;
    }

    /* ����ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait = VOS_FALSE;

    /* ֹͣTI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK);

    CNAS_XCC_SndXcallSendFlashCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                  TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq
 ��������  : ��Send Burst DTMF�����еȴ�L2 ACK״̬�£�����绰�Ҷ�(�����Ҷϻ�����Ҷ�)
 �������  : ucIndex
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��12��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�

*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait)
    {
        return;
    }

    /* ����ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait = VOS_FALSE;

    /* ֹͣTI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK);

    CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                      TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE);

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcBufferedMsgWithPowerDown
 ��������  : ���������û�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
   2.��    ��   : 2015��9��8��
     ��    ��   : w00176964
     �޸�����   : CNAS�ڴ�ü�����
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcBufferedMsgUponPowerDown(VOS_VOID)
{
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstXcallOrigReq = VOS_NULL_PTR;
    APS_XCC_ORIG_DATA_CALL_REQ_STRU    *pstApsOrigReq   = VOS_NULL_PTR;
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU    *pstCsmsOrigReq  = VOS_NULL_PTR;
    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU   *pstXpdsOrigReq  = VOS_NULL_PTR;
    VOS_UINT8                           i;
    VOS_UINT8                           ucMsgNum;

    ucMsgNum = CNAS_XCC_GetBufferedMsgNum();

    for (i = 0; i < CNAS_MIN(ucMsgNum, CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM); i++)
    {
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(i);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_XCALL_XCC_ORIG_CALL_REQ) == ulBufferMsgEventType)
        {
            pstXcallOrigReq = (XCALL_XCC_ORIG_CALL_REQ_STRU *)pstBufferMsgHdr;
            CNAS_XCC_SndXcallOrigCallCnf(pstXcallOrigReq->ucCallId,
                                         TAF_XCC_FAIL_LAYER_L3,
                                         TAF_XCC_CAUSE_POWER_DOWN_IND,
                                         TAF_XCC_CALLID_NULL,
                                         0);
        }

        /* �û���������XCC��ͻ���ƣ���ʱ�޸� */
        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_XCC_ORIG_DATA_CALL_REQ) == ulBufferMsgEventType)
        {
            pstApsOrigReq = (APS_XCC_ORIG_DATA_CALL_REQ_STRU *)pstBufferMsgHdr;

            CNAS_XCC_SndApsOrigDataCallCnf(pstApsOrigReq->ucCallId,
                                           TAF_XCC_FAIL_LAYER_L3,
                                           TAF_XCC_CAUSE_POWER_DOWN_IND,
                                           CNAS_XCC_INVALID_CON_REF,
                                           CNAS_XCC_INVAILD_CON_ID,
                                           0);
        }

        if (CNAS_BuildEventType(UEPS_PID_XSMS, ID_CSMS_XCC_ORIG_SMS_CALL_REQ) == ulBufferMsgEventType)
        {
            pstCsmsOrigReq = (CSMS_XCC_ORIG_SMS_CALL_REQ_STRU *)pstBufferMsgHdr;

            CNAS_XCC_SndCsmsOrigCallCnf(pstCsmsOrigReq->ucCallId,
                                        TAF_XCC_FAIL_LAYER_L3,
                                        TAF_XCC_CAUSE_POWER_DOWN_IND);
        }
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */

        if (CNAS_BuildEventType(UEPS_PID_XPDS, ID_XPDS_XCC_ORIG_AGPS_CALL_REQ) == ulBufferMsgEventType)
        {
            pstXpdsOrigReq = (XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU *)pstBufferMsgHdr;

            CNAS_XCC_SndXpdsOrigCallCnf(pstXpdsOrigReq->ucCallId,
                                        TAF_XCC_FAIL_LAYER_L3,
                                        TAF_XCC_CAUSE_POWER_DOWN_IND);
        }
    }

    /* ������л��� */
    CNAS_XCC_FreeAllBufferMsgInQueue();
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXsdStartReq_MainCtrl
 ��������  : ����Xsd start req
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXsdStartReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_InitCtx(CNAS_XCC_INIT_TYPE_POWER_ON);

    /* ����������Ҫ��call control instance��״̬����ֱ�ӷ��ؿ����ɹ� */
    CNAS_XCC_SndXsdStartCnf(XCC_XSD_START_RESULT_SUCC);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXsdPowerDownReq_MainCtrl
 ��������  : ����power down request
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��06��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��8��
    ��    ��   : y00245242
    �޸�����   : ����NDSS ORIG����
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXsdPowerDownReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INSTANCE_LIST_STRU    stCallInstanceList;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucRelReqFlag;
    XSD_XCC_POWER_OFF_REQ_STRU         *pstPowerOffReq = VOS_NULL_PTR;

    NAS_MEM_SET_S(&stCallInstanceList, sizeof(CNAS_XCC_CALL_INSTANCE_LIST_STRU), 0, sizeof(CNAS_XCC_CALL_INSTANCE_LIST_STRU));

    CNAS_XCC_GetAllActiveCallInstanceIndex(&stCallInstanceList);

    pstXccCtxAddr       = CNAS_XCC_GetCtxAddr();

    ucRelReqFlag        = VOS_FALSE;

    pstPowerOffReq = (XSD_XCC_POWER_OFF_REQ_STRU*)pstMsg;

    if (0 == stCallInstanceList.ucInstanceNum)
    {
        /* �����call control instance����ظ��ػ�ȷ�� */
        CNAS_XCC_SndXsdPowerOffCnf(XCC_XSD_POWER_OFF_RESULT_SUCC);

        /* ��ʼ��XCC������ */
        if (XCC_XSD_POWER_OFF_REASON_POWER_OFF == pstPowerOffReq->enPowerOffReason)
        {
            CNAS_XCC_InitCtx(CNAS_XCC_INIT_TYPE_POWER_DOWN);
        }
        else
        {
            CNAS_XCC_InitCtx(CNAS_XCC_INIT_TYPE_POWER_SAVE);
        }

        return VOS_TRUE;
    }

    /* ����м���call instance��ת�����ڲ��ػ��¼��������Ϣ���ڲ������� */
    for (i = 0; i < CNAS_MIN(stCallInstanceList.ucInstanceNum, CNAS_XCC_MAX_FSM_ENTITY_NUM); i++)
    {
        ucIndex = stCallInstanceList.aucInstance[i];

        CNAS_XCC_SndXccPowerDownInd(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId);

        if (VOS_FALSE == ucRelReqFlag)
        {
            ucRelReqFlag =
                CNAS_XCC_IsSending1xCallRelReqAllowed(&(pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm));
        }

    }

    if (VOS_TRUE == ucRelReqFlag)
    {
        if (XCC_XSD_POWER_OFF_REASON_POWER_OFF == pstPowerOffReq->enPowerOffReason)
        {
            /* �����ͷ����� */
            CNAS_XCC_SndCasCallRelReq(CNAS_XCC_INVAILD_CON_ID,
                                      CNAS_XCC_INVALID_CON_REF,
                                      CAS_CNAS_1X_REL_REASON_POWER_DOWN_RELEASE,
                                      VOS_TRUE);
        }
        else
        {
            /* �����ͷ����� */
            CNAS_XCC_SndCasCallRelReq(CNAS_XCC_INVAILD_CON_ID,
                                      CNAS_XCC_INVALID_CON_REF,
                                      CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                                      VOS_TRUE);
        }
    }

    /* ������ܻ���������û�������Ϣ */
    CNAS_XCC_ProcBufferedMsgUponPowerDown();

    /* ����ػ�������Ϣ */
    CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

    CNAS_XCC_ClearAllOrigCallOrderIndex();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallOrigCallReq_MainCtrl
 ��������  : ����ID_XCALL_XCC_ORIG_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��06��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X��Ŀ����5�޸�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallOrigCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucAbortIndex;
    VOS_UINT8                           ucAbortFlag;
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstXcallOrigReq = VOS_NULL_PTR;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    pstXcallOrigReq = (XCALL_XCC_ORIG_CALL_REQ_STRU *)pstMsg;

    if (VOS_FALSE == CNAS_CCB_Get1XRfAvailFlg())
    {
        /* NO RFʱ���ܾ��������� */
        /* NO RF״̬��XSD��������ʱ�յ�ҵ�������·�SessionBegin��Ϣ�ᵼ��Xģ�ڲ�����Դ�������
           ������NO RF״ֱ̬�ӻظ�XCALL,��XCALL�����ز�����֤��ǰפ�������Ϻ��ٴ������ҵ�� */
        CNAS_XCC_SndXcallOrigCallCnf(pstXcallOrigReq->ucCallId,
                                     TAF_XCC_FAIL_LAYER_L3,
                                     TAF_XCC_CAUSE_NO_RF,
                                     TAF_XCC_CALLID_NULL,
                                     0);

        return VOS_TRUE;
    }

    /* check�Ƿ��йػ����� */
    if (VOS_TRUE == CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl())
    {
        /* ����йػ���Ϣ���棬�ܾ��������� */
        CNAS_XCC_SndXcallOrigCallCnf(pstXcallOrigReq->ucCallId,
                                     TAF_XCC_FAIL_LAYER_L3,
                                     TAF_XCC_CAUSE_POWER_DOWN_IND,
                                     TAF_XCC_CALLID_NULL,
                                     0);

        return VOS_TRUE;
    }

    ucAbortIndex = 0;
    ucAbortFlag  = VOS_FALSE;
    enCause = CNAS_XCC_IsXcallOrigCallReqAllowed(pstXcallOrigReq, &ucAbortIndex, &ucAbortFlag);
    if(TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        /* �ܾ��������� */
        CNAS_XCC_SndXcallOrigCallCnf(pstXcallOrigReq->ucCallId,
                                     TAF_XCC_FAIL_LAYER_L3,
                                     enCause,
                                     TAF_XCC_CALLID_NULL,
                                     0);

        return VOS_TRUE;
    }

    if (VOS_TRUE == ucAbortFlag)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

        /* �����Ҫ��ֹ�����������ͣ�ת�����¼�Ϊabort�¼�������ŵ��ڲ������� */
        CNAS_XCC_SndXccAbortReq(pstXccCtxAddr->astFsmEntity[ucAbortIndex].stCallInfoCtx.ucConnectId,
                                ulEventType,
                                TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MO_CALL);

        /* �����û�������Ϣ */
        CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

        return VOS_TRUE;
    }

    /* for emergency call,we should process in advance according the state machine state  */
    if (VOS_TRUE == pstXcallOrigReq->ucIsEmergencyCall)
    {
        if (VOS_TRUE == CNAS_XCC_ProcessXcallEmergencyCallReq_MainCtrl(ulEventType, pstMsg))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallOrigCallReq_MainCtrl
 ��������  : ����ID_APS_XCC_ORIG_DATA_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessApsOrigDataCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_ORIG_DATA_CALL_REQ_STRU                        *pstDataCallReq = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32                               enCause;

    pstDataCallReq = (APS_XCC_ORIG_DATA_CALL_REQ_STRU *)pstMsg;

    /* check�Ƿ��йػ����� */
    if (VOS_TRUE == CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl())
    {
        /* ����йػ���Ϣ���棬֪ͨAPS����ʧ�� */
        CNAS_XCC_SndApsOrigDataCallCnf(pstDataCallReq->ucCallId,
                                       TAF_XCC_FAIL_LAYER_L3,
                                       TAF_XCC_CAUSE_POWER_DOWN_IND,
                                       CNAS_XCC_INVALID_CON_REF,
                                       CNAS_XCC_INVAILD_CON_ID,
                                       0);

        return VOS_TRUE;
    }



    enCause = CNAS_XCC_IsApsOrigDataCallReqAllowed();

    if(TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        /* ֪ͨAPS����ʧ�� */
        CNAS_XCC_SndApsOrigDataCallCnf(pstDataCallReq->ucCallId, TAF_XCC_FAIL_LAYER_L3, enCause, CNAS_XCC_INVALID_CON_REF, CNAS_XCC_INVAILD_CON_ID, 0);

        return VOS_TRUE;
    }

#if 0
    if (VOS_TRUE == ucAbortFlg)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

        /* �����Ҫ��ֹ�����������ͣ�ת�����¼�Ϊabort�¼�������ŵ��ڲ������� */
        CNAS_XCC_SndXccAbortReq(pstXccCtxAddr->astFsmEntity[ucAbortIndex].stCallInfoCtx.ucConnectId, ulEventType);

        /* �����û�������Ϣ */
        CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessSmsOrigCallReq_MainCtrl
 ��������  : ����ID_CSMS_XCC_ORIG_SMS_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessSmsOrigCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU                        *pstOrigCallReq = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32                               enCause;
    VOS_UINT8                                               ucAbortIndex;
    VOS_UINT8                                               ucAbortFlag;

    pstOrigCallReq = (CSMS_XCC_ORIG_SMS_CALL_REQ_STRU *)pstMsg;

    /* check�Ƿ��йػ����� */
    if (VOS_TRUE == CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl())
    {
        /* ����йػ���Ϣ���棬֪ͨSMS����ʧ�� */
        CNAS_XCC_SndCsmsOrigCallCnf(pstOrigCallReq->ucCallId,
                                    TAF_XCC_FAIL_LAYER_L3,
                                    TAF_XCC_CAUSE_POWER_DOWN_IND);

        return VOS_TRUE;
    }

    ucAbortIndex = 0;
    ucAbortFlag  = 0;

    enCause = CNAS_XCC_IsCsmsOrigCallReqAllowed(pstOrigCallReq, &ucAbortIndex, &ucAbortFlag);

    if (TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        /* ֪ͨSMS����ʧ�� */
        CNAS_XCC_SndCsmsOrigCallCnf(pstOrigCallReq->ucCallId, TAF_XCC_FAIL_LAYER_L3, enCause);

        return VOS_TRUE;
    }

#if 0
    if (VOS_TRUE == ucAbortFlag)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

        /* �����Ҫ��ֹ�����������ͣ�ת�����¼�Ϊabort�¼�������ŵ��ڲ������� */
        CNAS_XCC_SndXccAbortReq(pstXccCtxAddr->astFsmEntity[ucAbortIndex].stCallInfoCtx.ucConnectId, ulEventType);

        /* �����û�������Ϣ */
        CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXpdsOrigCallReq_MainCtrl
 ��������  : ����ID_XPDS_XCC_ORIG_AGPS_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXpdsOrigCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU   *pstOrigCallReq = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;
    VOS_UINT8                           ucAbortIndex;
    VOS_UINT8                           ucAbortFlag;


    pstOrigCallReq = (XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU *)pstMsg;

    /* check�Ƿ��йػ����� */
    if (VOS_TRUE == CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl())
    {
        /* ����йػ���Ϣ���棬֪ͨXPDS����ʧ�� */
        CNAS_XCC_SndXpdsOrigCallCnf(pstOrigCallReq->ucCallId,
                                    TAF_XCC_FAIL_LAYER_L3,
                                    TAF_XCC_CAUSE_POWER_DOWN_IND);

        return VOS_TRUE;
    }

    ucAbortIndex = 0;
    ucAbortFlag  = 0;

    enCause = CNAS_XCC_IsXpdsOrigCallReqAllowed(pstOrigCallReq, &ucAbortIndex, &ucAbortFlag);

    if (TAF_XCC_CAUSE_SUCCESS != enCause)
    {
        /* ֪ͨXPDS����ʧ�� */
        CNAS_XCC_SndXpdsOrigCallCnf(pstOrigCallReq->ucCallId, TAF_XCC_FAIL_LAYER_L3, enCause);

        return VOS_TRUE;
    }

#if 0
    if (VOS_TRUE == ucAbortFlag)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

        /* �����Ҫ��ֹ�����������ͣ�ת�����¼�Ϊabort�¼�������ŵ��ڲ������� */
        CNAS_XCC_SndXccAbortReq(pstXccCtxAddr->astFsmEntity[ucAbortIndex].stCallInfoCtx.ucConnectId, ulEventType);

        /* �����û�������Ϣ */
        CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}




/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallAnswerCallReq_MainCtrl
 ��������  : ����ID_XCALL_XCC_ANSWER_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��06��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallAnswerCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCALL_XCC_ANSWER_CALL_REQ_STRU     *pstXcallAnswerReq = VOS_NULL_PTR;

    if (VOS_FALSE == CNAS_XCC_IsVoiceCallInstanceActive())
    {
        pstXcallAnswerReq = (XCALL_XCC_ANSWER_CALL_REQ_STRU *)pstMsg;

        /* �ظ�����ʧ�� */
        CNAS_XCC_SndXcallAnswerCallCnf(pstXcallAnswerReq->ucCallId,
                                       0,
                                       TAF_CDMA_SO_BUTT,
                                       TAF_XCC_FAIL_LAYER_L3,
                                       TAF_XCC_CAUSE_CONNID_NOT_FOUND);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessApsAnswerDataCallReq_MainCtrl
 ��������  : ����ID_APS_XCC_ANSWER_DATA_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessApsAnswerDataCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_ANSWER_DATA_CALL_REQ_STRU  *pstAnsCallReq = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAnsCallReq = (APS_XCC_ANSWER_DATA_CALL_REQ_STRU *)pstMsg;

    ucIndex = 0;

    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, &ucIndex))
    {
        /* ��APS���ͽ���ʧ�� */
        CNAS_XCC_SndApsAnswerDataCallCnf(pstAnsCallReq->ucCallId, TAF_XCC_CAUSE_CONNID_NOT_FOUND);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessSmsAnswerCallReq_MainCtrl
 ��������  : ����ID_CSMS_XCC_ANSWER_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessSmsAnswerCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CSMS_XCC_ANSWER_CALL_REQ_STRU      *pstAnsCallReq = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAnsCallReq = (CSMS_XCC_ANSWER_CALL_REQ_STRU *)pstMsg;

    ucIndex = 0;

    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, &ucIndex))
    {
        /* ��SMS���ͽ���ʧ�� */
        CNAS_XCC_SndCsmsAnswerCallCnf(pstAnsCallReq->ucCallId, TAF_XCC_CAUSE_CONNID_NOT_FOUND);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXpdsAnswerCallReq_MainCtrl
 ��������  : ����ID_CSMS_XCC_ANSWER_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXpdsAnswerCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XPDS_XCC_ANSWER_CALL_REQ_STRU      *pstAnsCallReq = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstAnsCallReq = (XPDS_XCC_ANSWER_CALL_REQ_STRU *)pstMsg;

    ucIndex = 0;

    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, &ucIndex))
    {
        /* ��XPDS���ͽ���ʧ�� */
        CNAS_XCC_SndXpdsAnswerCallCnf(pstAnsCallReq->ucCallId, TAF_XCC_CAUSE_CONNID_NOT_FOUND);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallHangupCallReq_MainCtrl
 ��������  : ����ID_XCALL_XCC_HANGUP_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��06��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X��Ŀ����5�޸�

  3.��    ��   : 2015��1��8��
    ��    ��   : y00245242
    �޸�����   : ����NDSS ORIG����
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallHangupCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           i;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigReq   = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupReq = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    ucMsgNum     = CNAS_XCC_GetBufferedMsgNum();

    pstHangupReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    for (i = 0; i < CNAS_MIN(ucMsgNum, CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM); i++)
    {
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(i);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_XCALL_XCC_ORIG_CALL_REQ) == ulBufferMsgEventType)
        {
            pstOrigReq   = (XCALL_XCC_ORIG_CALL_REQ_STRU *)pstBufferMsgHdr;

            if (pstHangupReq->ucCallId == pstOrigReq->ucCallId)
            {
                /* ����������� */
                CNAS_XCC_SndXcallHangUpCallCnf(pstHangupReq->ucCallId);
                CNAS_XCC_FreeSpecifiedIndexBufferMsg(i);
                return VOS_TRUE;
            }
        }
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
    }

    /* �����voice call instance���ֱ�ӻظ��һ�ȷ�� */
    if (VOS_FALSE == CNAS_XCC_IsVoiceCallInstanceActive())
    {
        CNAS_XCC_SndXcallHangUpCallCnf(pstHangupReq->ucCallId);
        return VOS_TRUE;
    }

    /* Get call control instance of hangUp CallId, if fail,
       hangup the emergency call other than mt call.
    */
    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByCallId(pstHangupReq->ucCallId, &ucIndex))
    {
        /* if fail, ucIndex points to mt call instance,
           but hangup callId points to emergency call.So don't execute the following function.
        */
        /* �ж�ʵ���Ƿ��ڵȴ�FLASH REQ��L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(ucIndex);

        /* �ж�ʵ���Ƿ��ڵȴ�Send Burst DTMF��L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(ucIndex);

        /* �ж�ʵ���Ƿ��ڵȴ�Cont DTMF Tone Order��L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(ucIndex);
    }
    else
    {
        /* if wait emergency FWI/EFWI flag exist,the uplayer may hangup the emergency call while mt
          voice call exist, the we could not match the hangup call ID with the current mt voice call ID
          then we should continue match the hangup call ID with the emergency call ID. */
        if (VOS_FALSE == CNAS_XCC_GetWaitEmcFlashMsgRspFlg())
        {
            return VOS_TRUE;
        }

        /* continue get the instance index using the mt voice call id. */
        if (VOS_FALSE == CNAS_XCC_GetCallInstanceIndexByCallId(CNAS_XCC_GetMtVoiceCallId(), &ucIndex))
        {
            return VOS_TRUE;
        }
    }

    if (VOS_TRUE == CNAS_XCC_ProcessHangupCallReqWhenWaitEmcFlashMsgRsp(ucIndex, pstHangupReq))
    {
        return VOS_TRUE;
    }

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessApsHangupDataCallReq_MainCtrl
 ��������  : ����ID_APS_XCC_HANGUP_DATA_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��8��
    ��    ��   : y00245242
    �޸�����   : ����NDSS ORIG����
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessApsHangupDataCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
    APS_XCC_ORIG_DATA_CALL_REQ_STRU    *pstOrigReq   = VOS_NULL_PTR;
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU  *pstHangupReq = VOS_NULL_PTR;
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;

    ucMsgNum     = CNAS_XCC_GetBufferedMsgNum();

    pstHangupReq = (APS_XCC_HANGUP_DATA_CALL_REQ_STRU *)pstMsg;

    for (i = 0; i < CNAS_MIN(ucMsgNum, CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM); i++)
    {
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(i);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_XCC_ORIG_DATA_CALL_REQ) == ulBufferMsgEventType)
        {
            pstOrigReq   = (APS_XCC_ORIG_DATA_CALL_REQ_STRU *)pstBufferMsgHdr;

            if (pstHangupReq->ucCallId == pstOrigReq->ucCallId)
            {
                /* ��APS���͹Ҷϻظ� */
                CNAS_XCC_SndApsHangupDataCallCnf(pstHangupReq->ucCallId);

                /* ������� */
                CNAS_XCC_FreeSpecifiedIndexBufferMsg(i);

                return VOS_TRUE;
            }
        }
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
    }

    /* �����data call instance���ֱ�ӻظ��һ�ȷ�� */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, &ucIndex))
    {
        /* ��APS���͹Ҷϻظ� */
        CNAS_XCC_SndApsHangupDataCallCnf(pstHangupReq->ucCallId);

        return VOS_TRUE;
    }

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessSmsHangupCallReq_MainCtrl
 ��������  : ����ID_CSMS_XCC_END_SMS_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��8��
    ��    ��   : y00245242
    �޸�����   : ����NDSS ORIG����
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessSmsHangupCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU    *pstOrigReq   = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU     *pstHangupReq = VOS_NULL_PTR;
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;

    ucMsgNum     = CNAS_XCC_GetBufferedMsgNum();

    pstHangupReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;

    for (i = 0; i < CNAS_MIN(ucMsgNum, CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM); i++)
    {
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(i);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(UEPS_PID_XSMS, ID_CSMS_XCC_ORIG_SMS_CALL_REQ) == ulBufferMsgEventType)
        {
            pstOrigReq   = (CSMS_XCC_ORIG_SMS_CALL_REQ_STRU *)pstBufferMsgHdr;

            if (pstHangupReq->ucCallId == pstOrigReq->ucCallId)
            {
                /* ��SMS���͹Ҷϻظ� */
                CNAS_XCC_SndCsmsHangupCallCnf(pstHangupReq->ucCallId);

                /* ������� */
                CNAS_XCC_FreeSpecifiedIndexBufferMsg(i);

                return VOS_TRUE;
            }
        }
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
    }

    /* �����SMS call instance���ֱ�ӻظ��һ�ȷ�� */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, &ucIndex))
    {
        /* ��SMS���͹Ҷϻظ� */
        CNAS_XCC_SndCsmsHangupCallCnf(pstHangupReq->ucCallId);

        return VOS_TRUE;
    }

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXpdsHangupCallReq_MainCtrl
 ��������  : ����ID_XPDS_XCC_END_AGPS_CALL_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXpdsHangupCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
    XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU   *pstOrigReq   = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU    *pstHangupReq = VOS_NULL_PTR;
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;

    ucMsgNum     = CNAS_XCC_GetBufferedMsgNum();

    pstHangupReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;

    for (i = 0; i < CNAS_MIN(ucMsgNum, CNAS_XCC_MAX_BUFFER_MSG_QUEUE_NUM); i++)
    {
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(i);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(UEPS_PID_XPDS, ID_XPDS_XCC_ORIG_AGPS_CALL_REQ) == ulBufferMsgEventType)
        {
            pstOrigReq   = (XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU *)pstBufferMsgHdr;

            if (pstHangupReq->ucCallId == pstOrigReq->ucCallId)
            {
                /* ��Xpds���͹Ҷϻظ� */
                CNAS_XCC_SndXpdsEndCallCnf(pstHangupReq->ucCallId);

                /* ������� */
                CNAS_XCC_FreeSpecifiedIndexBufferMsg(i);

                return VOS_TRUE;
            }
        }
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
    }

    /* �����AGPS call instance���ֱ�ӻظ��һ�ȷ�� */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, &ucIndex))
    {
        /* ��XPDS���͹Ҷϻظ� */
        CNAS_XCC_SndXpdsEndCallCnf(pstHangupReq->ucCallId);

        return VOS_TRUE;
    }

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xPagingInd_MainCtrl
 ��������  : ����ID_CAS_CNAS_1X_PAGING_IND
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��06��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xPagingInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucAbortIndex;
    VOS_UINT8                           ucAbortFlag;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulCurrFsmId;
    VOS_UINT32                          ulCurrFsmState;
    VOS_UINT32                          i;
    CNAS_XCC_FSM_ENTITY_STRU           *pstFsmEntity = VOS_NULL_PTR;

    for ( i = 0 ; i < CNAS_XCC_MAX_FSM_ENTITY_NUM ; i++ )
    {
        /* ��ȡÿ��״̬�� */
        pstFsmEntity = &(CNAS_XCC_GetCtxAddr()->astFsmEntity[i]);

        ulCurrFsmId    = pstFsmEntity->stCurFsm.enFsmId;
        ulCurrFsmState = pstFsmEntity->stCurFsm.ulState;

        /* ��ǰ���ڹػ�״̬������Ѱ�� */
        if ((CNAS_XCC_FSM_L1_MAIN == ulCurrFsmId)
         && (CNAS_XCC_L1_STA_POWER_OFF == ulCurrFsmState))
        {
            /* ����Ѱ�� */
            CNAS_WARNING_LOG(UEPS_PID_XCC,
                             "CNAS_XCC_ProcessCas1xPagingInd_MainCtrl: power off��ignore the page information!");

            return VOS_TRUE;

        }
    }

    if (VOS_TRUE == CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl())
    {
        /* ����Ѱ�� */
        CNAS_WARNING_LOG(UEPS_PID_XCC,
                         "CNAS_XCC_ProcessCas1xPagingInd_MainCtrl: ignore the page information!");

        return VOS_TRUE;

    }

    ucAbortIndex = 0;
    ucAbortFlag  = VOS_FALSE;
    if (VOS_FALSE == CNAS_XCC_IsPaginMsgAllowed((CAS_CNAS_1X_PAGING_IND_STRU *)pstMsg, &ucAbortIndex, &ucAbortFlag))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == ucAbortFlag)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

        /* �����Ҫ��ֹ�����������ͣ�ת�����¼�Ϊabort�¼�������ŵ��ڲ������� */
        CNAS_XCC_SndXccAbortReq(pstXccCtxAddr->astFsmEntity[ucAbortIndex].stCallInfoCtx.ucConnectId,
                                ulEventType,
                                TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MT_CALL);

        /* �����û�������Ϣ */
        CNAS_XCC_BufferMsgInQueue(ulEventType, pstMsg);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessMsgWaitingWithinAWI_MainCtrl
 ��������  : ��AWI��Ϣ�д���MsgWaiting Info record������XSMS����ָʾ
 �������  : pst1xDschDataInd --- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : L00256032
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinAWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    CNAS_XCC_AWIM_STRU                 *pstAWIM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ���AWI�Ľ��� */
    pstAWIM = (CNAS_XCC_AWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_AWIM_STRU));
    if (VOS_NULL_PTR == pstAWIM)
    {
        return;
    }

    NAS_MEM_SET_S(pstAWIM, sizeof(CNAS_XCC_AWIM_STRU), 0, sizeof(CNAS_XCC_AWIM_STRU));

    if (VOS_OK != CNAS_XCC_DecodeAlertWithInformationMsg(pst1xDschDataInd, pstAWIM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
        return;
    }

    /* ���ҽ����Ľ�����Ƿ���message waiting���info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING,
                                                           pstAWIM->ucNumInfoRecs,
                                                           pstAWIM->astInfoRecsData,
                                                           &ucIndex);

    if (VOS_TRUE == ulResult)
    {
        CNAS_XCC_SndCsmsMsgWaitingInd(pstAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stMsgWaiting.ucMsgCnt);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessMsgWaitingWithinFWI_MainCtrl
 ��������  : ��FWI��Ϣ�д���MsgWaiting Info record������XSMS����ָʾ
 �������  : pst1xDschDataInd --- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : L00256032
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinFWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    CNAS_XCC_FWIM_STRU                 *pstFWIM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ���FWI�Ľ��� */
    pstFWIM = (CNAS_XCC_FWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_FWIM_STRU));
    if (VOS_NULL_PTR == pstFWIM)
    {
        return;
    }

    NAS_MEM_SET_S(pstFWIM, sizeof(CNAS_XCC_FWIM_STRU), 0, sizeof(CNAS_XCC_FWIM_STRU));

    if (VOS_OK != CNAS_XCC_DecodeFlashWithInformationMsg(pst1xDschDataInd, pstFWIM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstFWIM);
        return;
    }

    /* ���ҽ����Ľ�����Ƿ���message waiting���info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING,
                                                           pstFWIM->ucNumInfoRecs,
                                                           pstFWIM->astInfoRecsData,
                                                           &ucIndex);

    if (VOS_TRUE == ulResult)
    {
        CNAS_XCC_SndCsmsMsgWaitingInd(pstFWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stMsgWaiting.ucMsgCnt);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstFWIM);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessMsgWaitingWithinEAWI_MainCtrl
 ��������  : ��EAWI��Ϣ�д���MsgWaiting Info record������XSMS����ָʾ
 �������  : pst1xDschDataInd --- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : L00256032
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinEAWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    CNAS_XCC_EAWIM_STRU                *pstEAWIM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ���EAWI�Ľ��� */
    pstEAWIM = (CNAS_XCC_EAWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EAWIM_STRU));
    if (VOS_NULL_PTR == pstEAWIM)
    {
        return;
    }

    NAS_MEM_SET_S(pstEAWIM, sizeof(CNAS_XCC_EAWIM_STRU), 0, sizeof(CNAS_XCC_EAWIM_STRU));

    if (VOS_OK != CNAS_XCC_DecodeExtendedAlertWithInformationMsg(pst1xDschDataInd, pstEAWIM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
        return;
    }

    /* ���ҽ����Ľ�����Ƿ���message waiting���info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING,
                                                           pstEAWIM->ucNumInfoRecs,
                                                           pstEAWIM->astInfoRecsData,
                                                           &ucIndex);

    if (VOS_TRUE == ulResult)
    {
        CNAS_XCC_SndCsmsMsgWaitingInd(pstEAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stMsgWaiting.ucMsgCnt);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessMsgWaitingWithinEFWI_MainCtrl
 ��������  : ��EFWI��Ϣ�д���MsgWaiting Info record������XSMS����ָʾ
 �������  : pst1xDschDataInd --- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : L00256032
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinEFWI_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    CNAS_XCC_EFWIM_STRU                *pstEFWIM  = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ���EFWI�Ľ��� */
    pstEFWIM = (CNAS_XCC_EFWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EFWIM_STRU));
    if (VOS_NULL_PTR == pstEFWIM)
    {
        return;
    }

    NAS_MEM_SET_S(pstEFWIM, sizeof(CNAS_XCC_EFWIM_STRU), 0, sizeof(CNAS_XCC_EFWIM_STRU));

    if (VOS_OK != CNAS_XCC_DecodeExtendedFlashWithInformationMsg(pst1xDschDataInd, pstEFWIM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstEFWIM);
        return;
    }

    /* ���ҽ����Ľ�����Ƿ���message waiting���info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING,
                                                           pstEFWIM->ucNumInfoRecs,
                                                           pstEFWIM->astInfoRecsData,
                                                           &ucIndex);

    if (VOS_TRUE == ulResult)
    {
        CNAS_XCC_SndCsmsMsgWaitingInd(pstEFWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stMsgWaiting.ucMsgCnt);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstEFWIM);

    return;
}

VOS_UINT32 CNAS_XCC_ProcessOrderMsg_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    CNAS_XCC_ORDRM_STRU                 stOrdrm;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucConRef;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucDigit;
    VOS_UINT8                           ucSwitch;
    CNAS_XCC_ORDER_TYPE_ENUM_UINT8      enOrderType;


    NAS_MEM_SET_S(&stOrdrm, sizeof(CNAS_XCC_ORDRM_STRU), 0x00, sizeof(CNAS_XCC_ORDRM_STRU));

    if (VOS_OK != CNAS_XCC_DecodeOrderMsg(pst1xDschDataInd, &stOrdrm))
    {
        /* message structure not acceptable */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stOrdrm.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_STRUCT);
        return VOS_TRUE;
    }

    ulRslt = CNAS_XCC_GetOrderSpecificMsgType(&(stOrdrm.stOrder), &enOrderType);
    if (VOS_OK != ulRslt)
    {
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stOrdrm.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_CODE);
        CNAS_ERROR_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcessOrderMsg_MainCtrl: CNAS_XCC_GetOrderSpecificMsgType FAIL ", ulRslt);
        return VOS_TRUE;
    }

    if (CNAS_XCC_ORDER_TYPE_CONTINUOUS_DTMF_TONE != enOrderType)
    {
        /* Returning VOS_FALSE to process this order in FSM */
        return VOS_FALSE;
    }

    /* if the Protocol Revision is equal to or greater than 7, then the CON_REF must be extracted from the encoded
    ORDM message to get the correct call ID corresponding to this message */
    if (P_REV_IN_USE_7 <= CNAS_CCB_GetPRevInUse())
    {
        /* Get the CON_REF_INCL and CON_REF from the Encoded bit stream */
        CNAS_XCC_DecodeConRefFromFDschOrdmMsg(pst1xDschDataInd->aucMsgData,
                                              pst1xDschDataInd->usMsgDataLen,
                                              &stOrdrm.ucConRefPresent,
                                              &stOrdrm.ucConRef);
    }

    ucConRef = (VOS_TRUE == stOrdrm.ucConRefPresent) ? stOrdrm.ucConRef : CNAS_XCC_INVALID_CON_REF;
    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByCallRef(ucConRef, &ucIndex))
    {
        /* no call control instance present with the specified identifier */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stOrdrm.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_NO_CC_INST);
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if ((CNAS_XCC_FSM_L1_MAIN != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        /* message not accepted in this state  */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stOrdrm.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_STATE);
        return VOS_TRUE;
    }

    ucDigit  = CNAS_XCC_INVALID_DTMF_DIGIT;
    ucSwitch = CNAS_XCC_INVALID_DTMF_SWITCH;

    /* Check the permissible ORDQ */
    ulRslt = CNAS_XCC_GetDigitAndSwitchFromORDQ(stOrdrm.stOrder.ucOrdq, &ucDigit, &ucSwitch);
    if (VOS_OK != ulRslt)
    {
        /* message field not in valid range */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stOrdrm.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_FIELD);
        return VOS_TRUE;
    }

    /* Send ID_XCC_XCALL_CONT_DTMF_IND message to XCALL */
    ucCallId = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId;
    CNAS_XCC_SndXcallContDTMFInd(ucCallId, ucDigit, ucSwitch);

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessMsgWaitingWithinDschDataInd_MainCtrl
 ��������  : ����ID_CAS_CNAS_1X_DSCH_DATA_IND�����ΪFWI/EFWI/AWI/EAWI������Ϣ�д���
             MsgWaiting Info record������XSMS����ָʾ
 �������  : pst1xDschDataInd --- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��02��
    ��    ��   : L00256032
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessMsgWaitingWithinDschDataInd_MainCtrl(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd
)
{
    switch (pst1xDschDataInd->enDschMsgType)
    {
        case CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG:
            CNAS_XCC_ProcessMsgWaitingWithinAWI_MainCtrl(pst1xDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG:
            CNAS_XCC_ProcessMsgWaitingWithinFWI_MainCtrl(pst1xDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG:
            CNAS_XCC_ProcessMsgWaitingWithinEAWI_MainCtrl(pst1xDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG:
            CNAS_XCC_ProcessMsgWaitingWithinEFWI_MainCtrl(pst1xDschDataInd);
            break;

        default:
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xDschDataInd_MainCtrl
 ��������  : ����ID_CAS_CNAS_1X_DSCH_DATA_IND
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��06��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2015-07-24
    ��    ��   : K00902809
    �޸�����   : Added process to handle receiving Continuous DTMF order.

  3.��    ��   : 2015-07-24
    ��    ��   : a00295761
    �޸�����   : Added process to handle receiving Burst DTMF Message.
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xDschDataInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd = VOS_NULL_PTR;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    CNAS_XCC_ORDRM_STRU                 stOrdrm;
    VOS_UINT8                           ucConRef;

    /* �����CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG��Ϣ������״̬�� */
    pst1xDschDataInd =(CAS_CNAS_1X_DSCH_DATA_IND_STRU*)pstMsg;
    if (CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG == pst1xDschDataInd->enDschMsgType)
    {
        CNAS_XCC_ProcessCas1xTchServiceOptionControlMsgInd_MainCtrl(pstMsg);
        return VOS_TRUE;
    }

    if (CAS_CNAS_1X_RX_TCH_ORDER_MSG == pst1xDschDataInd->enDschMsgType)
    {
        /*
        Returns VOS_FALSE: If the received ORDER TYPE is not Continuous DTMF order to process pstMsg is FSM.
        Other wise returns VOS_TRUE because the message is processed in the below function and no need to process in FSM.
        */
        return CNAS_XCC_ProcessOrderMsg_MainCtrl(pst1xDschDataInd);
    }

    if (CAS_CNAS_1X_RX_TCH_SEND_BURST_DTMF_MSG == pst1xDschDataInd->enDschMsgType)
    {
        CNAS_XCC_ProcessCas1xTchSndBurstDtmfMsgInd_MainCtrl(ulEventType, pstMsg);
        return VOS_TRUE;
    }

    pst1xDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;

    CNAS_XCC_GetConRefFromDschDataInd(pst1xDschDataInd, &ucConRef);

    if (VOS_FALSE == CNAS_XCC_IsCallConRefExist(ucConRef))
    {
        /* ���ConRef�����ڣ�����reject order����Ϣ����״̬������ */
        NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

        /* ����REJ ORDER */
        stRejInfo.ucConRef          = ucConRef;
        stRejInfo.enRejRxTchMsgType = pst1xDschDataInd->enDschMsgType;
        stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
        stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_NO_CC_INST;
        stRejInfo.ulL3PduBitLen     = 0;
        stRejInfo.pucPdudata        = aucPduData;

        if (CAS_CNAS_1X_RX_TCH_ORDER_MSG == pst1xDschDataInd->enDschMsgType)
        {
            NAS_MEM_SET_S(&stOrdrm, sizeof(stOrdrm), 0, sizeof(stOrdrm));

            CNAS_XCC_DecodeOrderMsg(pst1xDschDataInd, &stOrdrm);
            stRejInfo.ucRejOrderCode    = stOrdrm.stOrder.ucOrder;
            stRejInfo.ucRejOrdq         = stOrdrm.stOrder.ucOrdq;
        }

        CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

        /* ����ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)��AS */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                   0,
                                   (VOS_UINT16)stRejInfo.ulL3PduBitLen,
                                   stRejInfo.pucPdudata);

        return VOS_TRUE;
    }

    CNAS_XCC_ProcessMsgWaitingWithinDschDataInd_MainCtrl(pst1xDschDataInd);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xReleaseOrderInd_MainCtrl
 ��������  : ����ID_CAS_CNAS_1X_RELEASE_ORDER_IND
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��13��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xReleaseOrderInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ο�Q��ʵ��,as����release orderָʾ��NW��,�ն˲���Ҫ�ٽ��йػ�ȥע��,֪ͨXSDģ��ػ�����Ҫȥע�� */
    CNAS_XCC_SndXsdDeregisterInd(XSD_XCC_DEREGISTER_REASON_POWEROFF);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessMsgInMainCtrl
 ��������  : ����ģ���д��������Ϣ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessMsgInMainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           i;

    ulRslt = VOS_FALSE;

    for (i = 0; i < (sizeof(g_astCnasXccMainCtrlProcTab)/sizeof(CNAS_XCC_MAIN_CTRL_PROC_STRU)); i++)
    {
        if (ulEventType == g_astCnasXccMainCtrlProcTab[i].ulMsgEvtType)
        {
            ulRslt = g_astCnasXccMainCtrlProcTab[i].pfMainCtrlProcFun(ulEventType, pstMsg);
            break;
        }
    }

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessPagingCollision
 ��������  : �����г�ͻ
 �������  : enPagingService -- ���з�������
 �������  : pucAbortIndex -- �������
             pucAbortFlag -- ��ϱ��
 �� �� ֵ  : VOS_TRUE  -- ������
             VOS_FALSE -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XCC_ProcessPagingCollision(
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enPagingService,
    VOS_UINT8                          *pucAbortIndex,
    VOS_UINT8                          *pucAbortFlag
)
{
    VOS_UINT8                           ucRslt;
    CNAS_XCC_CALL_INSTANCE_LIST_STRU    stCallInstanceList;

    ucRslt = VOS_TRUE;

    NAS_MEM_SET_S(&stCallInstanceList, sizeof(stCallInstanceList), 0x0, sizeof(stCallInstanceList));

    /* ��ǰ���ڻ��صı��У����ϵ�ǰ�ĺ��� */
    if (CNAS_XCC_SERVICE_TYPE_LOOPBACK == enPagingService)
    {
        /* ��ǰֻ�в�֧�ֲ���������£��Ż���Ҫ��ϵ�ǰ�ĺ��У����ֻ������һ·���� */
        CNAS_XCC_GetAllActiveCallInstanceIndex(&stCallInstanceList);
        if (0 != stCallInstanceList.ucInstanceNum)
        {
            *pucAbortIndex = stCallInstanceList.aucInstance[0];
            *pucAbortFlag = VOS_TRUE;
            ucRslt = VOS_TRUE;
        }
    }
    else if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enPagingService)
    {
        /* �������ݺ������У��յ���������������� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            ucRslt = VOS_TRUE;
        }

        /* ����SMS�������У��յ���������������� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            ucRslt = VOS_TRUE;
        }

        /* ����AGPS�������У��յ���������������� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
        {
            *pucAbortFlag = VOS_TRUE;

            ucRslt = VOS_TRUE;
        }
    }
    else if (CNAS_XCC_SERVICE_TYPE_DATA_CALL == enPagingService)
    {
        /* �������й����У��յ��������ݺ���ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }

        /* ���ű��й����У��յ��������ݺ���ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }


        /* �������ز����ڶ������ݱ��� */
        if (VOS_TRUE == TAF_SDC_GetCsCallExistFlg())
        {
            ucRslt = VOS_FALSE;
        }
        /* ����AGPS�������У��յ��������ݺ���ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }
    }
    else if (CNAS_XCC_SERVICE_TYPE_SMS == enPagingService)
    {
        /* �������й����У��յ����ж��ţ�ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }

        /* ����ҵ�񱻽й����У��յ����ж��ţ�ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }

        /* ����AGPS�������У��յ����ж��ţ�ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_AGPS_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }
    }
    else if (CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enPagingService)
    {
        /* �����������У��յ�AGPS���У�ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }

        /* ���ݺ������У��յ�AGPS���У�ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_DATA_CALL, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }

         /* ���ź������У��յ�AGPS���У�ֱ�ӷ��� */
        if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_SMS, pucAbortIndex))
        {
            ucRslt = VOS_FALSE;
        }
    }
    else
    {
       ucRslt = VOS_TRUE;
    }

    return ucRslt;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_IsBufferedPowerDownMsgExist
 ��������  : �����г�ͻ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ������
             VOS_FALSE -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��28��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_IsBufferedPowerDownMsgExist_MainCtrl(VOS_VOID)
{
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */

    /* check�Ƿ��йػ����� */
    if (0 != CNAS_XCC_GetBufferedMsgNum())
    {
        /* �ػ������Ƿ���� */
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
        pstBufferMsgHdr         = (MSG_HEADER_STRU *)CNAS_XCC_GetSpecifiedIndexBufferMsg(0);

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            return VOS_FALSE;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(UEPS_PID_XSD, ID_XSD_XCC_POWER_OFF_REQ) == ulBufferMsgEventType)
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
        {
            /* ���ڻ���ػ����򷵻�VOS_TRUE */
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndFWIorEFWIWithFlashReq_MainCtrl
 ��������  : XCC����FWI��EFWI
 �������  : ucIndex           -- voice callʵ������
             *pstXcallFlashReq
 �������  : ��
 �� �� ֵ  : VOS_OK    --  ��Ϣ���ͳɹ�
             VOS_ERR   --  ��Ϣ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�
  2.��    ��   : 2014��12��1��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 5 Modified
*****************************************************************************/
VOS_UINT32 CNAS_XCC_SndFWIorEFWIWithFlashReq_MainCtrl(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_SEND_FLASH_REQ_STRU      *pstXcallFlashReq
)
{
    VOS_UINT8                           ucPRevInUse;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucMsgSeqNum;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    /* ����SEQ NUM */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucSendFlashSeqNum = CNAS_XCC_AllocSeqNum();
    ucMsgSeqNum = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucSendFlashSeqNum;

    /*
        If P_REV_IN_USEs is less than seven, the mobile station shall send a Flash With Information Message .
        If P_REV_IN_USEs is equal to or greater than seven, the mobile station shall perform the following:
          if this Call Control instance is identified by NULL, the mobile station shall send either a Flash
          With Information Message or an Extended Flash With Information Message (with either the CON_REF_INCL
          field of the message set to '0' or the CON_REF_INCL field set to '1' and the CON_REF field set to
          the connection reference of the service option connection corresponding to this call);
          otherwise, the mobile station shall send an  Extended Flash With Information Message, with the
          CON_REF_INCL field of the message set to '1' and the CON_REF field of the message set to the
          connection reference of the service option connection corresponding to this call.
    */

    ucPRevInUse = CNAS_CCB_GetPRevInUse();

    if ( (ucPRevInUse < P_REV_IN_USE_7)
       ||(VOS_TRUE == pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsNullCc))
    {
        /* ��Ҫ����FWI�������FWI�ı��� */
        if (VOS_OK != CNAS_XCC_EncodeFlashWithInformationMsgWithFlashReq(pstXcallFlashReq->ucDigitNum,
                                                             pstXcallFlashReq->aucDigit,
                                                             aucPduData,
                                                             &ulPduDataLen))
        {
            return VOS_ERR;
        }

        /* ����FWI */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_FLASH_WITH_INFORMATION_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_BUTT,
                                   ucMsgSeqNum,
                                   (VOS_UINT16)ulPduDataLen,
                                   aucPduData);

    }
    else
    {
        /* ��Ҫ����EFWI�������EFWI�ı��� */
        if (VOS_OK != CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithFlashReq(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConRef,
                                                                     pstXcallFlashReq->ucDigitNum,
                                                                     pstXcallFlashReq->aucDigit,
                                                                     aucPduData,
                                                                     &ulPduDataLen))
        {
            return VOS_ERR;
        }

        /* ����EFWI */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_EXT_FLASH_WITH_INFORMATION_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_BUTT,
                                   ucMsgSeqNum,
                                   (VOS_UINT16)ulPduDataLen,
                                   aucPduData);
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallSendFlashReq_MainCtrl
 ��������  : ����ID_XCALL_XCC_SEND_FLASH_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallSendFlashReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    XCALL_XCC_SEND_FLASH_REQ_STRU      *pstXcallFlashReq = VOS_NULL_PTR;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucIsEmcCall;
    XCALL_XCC_ORIG_CALL_REQ_STRU        stXcallOrigReq;
    VOS_UINT8                           ucMsgSeqNum;

    pstXcallFlashReq = (XCALL_XCC_SEND_FLASH_REQ_STRU *)pstMsg;

    /* ��ȡvoice call��ʵ��index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        CNAS_XCC_SndXcallSendFlashCnf(pstXcallFlashReq->ucCallId, TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE);

        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* �ж�voice call��ʵ��״̬�Ƿ�ΪConversation��Ŀǰֻ֧����conversation̬����FLASH���� */
    if (  (CNAS_XCC_FSM_L1_MAIN != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
       || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        CNAS_XCC_SndXcallSendFlashCnf(pstXcallFlashReq->ucCallId, TAF_XCC_CAUSE_ABNORMAL_STATE);

        return VOS_TRUE;
    }

    ucIsEmcCall = pstXcallFlashReq->ucIsEmcCall;

    if (VOS_TRUE == ucIsEmcCall)
    {
        NAS_MEM_SET_S(&stXcallOrigReq, sizeof(XCALL_XCC_ORIG_CALL_REQ_STRU), 0x00, sizeof(XCALL_XCC_ORIG_CALL_REQ_STRU));

        NAS_MEM_CPY_S(stXcallOrigReq.stCalledPartyNum.aucDigit,
                      XCC_XCALL_MAX_CALLED_NUMBER_CHARI_OCTET_NUM,
                      pstXcallFlashReq->aucDigit,
                      pstXcallFlashReq->ucDigitNum);

        stXcallOrigReq.stCalledPartyNum.ucDigitNum = pstXcallFlashReq->ucDigitNum;

        ucMsgSeqNum = CNAS_XCC_AllocSeqNum();
        pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucSendFlashSeqNum = ucMsgSeqNum;

        stXcallOrigReq.enDigitMode = XCC_XCALL_DIGIT_MODE_ASCII;

        /* ��AS����ID_CNAS_CAS_1X_DSCH_DATA_REQ(FWI/EFWI) */
        if (VOS_FALSE == CNAS_XCC_SndFWIorEFWIWithEmergencyCallReq_MainCtrl(ucIndex, ucMsgSeqNum, &stXcallOrigReq))
        {
           CNAS_XCC_SndXcallSendFlashCnf(pstXcallFlashReq->ucCallId, TAF_XCC_CAUSE_ENCODE_FAIL);

           return VOS_TRUE;
        }
    }
    else
    {
        /* ��AS����ID_CNAS_CAS_1X_DSCH_DATA_REQ(FWI/EFWI) */
        if (VOS_OK != CNAS_XCC_SndFWIorEFWIWithFlashReq_MainCtrl(ucIndex, pstXcallFlashReq))
        {
            CNAS_XCC_SndXcallSendFlashCnf(pstXcallFlashReq->ucCallId, TAF_XCC_CAUSE_ENCODE_FAIL);

            return VOS_TRUE;
        }
    }

    /* ��λ�ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait = VOS_TRUE;

    /* ����TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK */
    CNAS_XCC_StartTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                        TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK,
                        TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessFlashL2Ack_MainCtrl
 ��������  : ����FLASH��L2 ACK
 �������  : ucIndex           -- ��Ϣ����+PID
             pst1xDschDataCnf  -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��ӦFLASH��L2 ACK
             VOS_FALSE --  ��FLASH��L2 ACK����ǰ�����ڵȴ�FLASH L2 ACK��״̬

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��11��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessFlashL2Ack_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* �ж�voice call��ʵ���Ƿ��ڵȴ�FLASH REQ��L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait)
    {
        return VOS_FALSE;
    }

    /* �ж�seqNum�Ƿ�һ�� */
    if (pst1xDschDataCnf->ucMsgSeqNum != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucSendFlashSeqNum)
    {
        return VOS_FALSE;
    }

    /* ����ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait = VOS_FALSE;

    /* ֹͣTI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK);

    if(CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pst1xDschDataCnf->enRslt)
    {
        enCause = TAF_XCC_CAUSE_SUCCESS;
    }
    else
    {
        enCause = TAF_XCC_CAUSE_L2_ACK_FAIL;
    }
    CNAS_XCC_SndXcallSendFlashCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                  enCause);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xDschDataCnf_MainCtrl
 ��������  : ����ID_CAS_CNAS_1X_DSCH_DATA_CNF
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�

  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X��Ŀ����5�޸�
  3.��    ��   : 2015��7��25��
    ��    ��   : l00324781
    �޸�����   : ����16�޸�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xDschDataCnf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf = VOS_NULL_PTR;

    pst1xDschDataCnf = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU *)pstMsg;

    /* ��ȡvoice call��ʵ��index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_FALSE;
    }

    /* �ж��Ƿ�ΪFWI/EFWI��L2 ACK */
    if (VOS_TRUE == CNAS_XCC_ProcessFlashL2Ack_MainCtrl(ucIndex, pst1xDschDataCnf))
    {
        /* ΪFWI/EFWI��L2 ACK��������ɺ�ֱ���˳�������Ҫ����״̬������ */
        return VOS_TRUE;
    }

    /* �ж��Ƿ�ΪSend Burst DTMF��L2 ACK */
    if (VOS_TRUE == CNAS_XCC_ProcessBurstDTMFL2Ack_MainCtrl(ucIndex, pst1xDschDataCnf))
    {
        /* ΪSend Burst DTMF��L2 ACK��������ɺ�ֱ���˳�������Ҫ����״̬������ */
        return VOS_TRUE;
    }

    /* �ж��Ƿ�ΪCont DTMF Tone Order��L2 ACK */
    if (VOS_TRUE == CNAS_XCC_ProcessContDTMFToneOrderL2Ack_MainCtrl(ucIndex, pst1xDschDataCnf))
    {
        /* ΪCont DTMF Tone Order��L2 ACK��������ɺ�ֱ���˳�������Ҫ����״̬������ */
        return VOS_TRUE;
    }

    if (VOS_TRUE == CNAS_XCC_ProcessEmergencyCallFlashMsgRsp_MainCtrl(ucIndex, pst1xDschDataCnf))
    {
        return VOS_TRUE;
    }


    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiProtectFlashCnfL2Ack_MainCtrl
 ��������  : ����TI_CNAS_XCC_WAIT_FLASH_CNF_L2_ACK��ʱ����ʱ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE --  ��Ϣ������Ҫ��״̬�������ʸú�������ֵ��ΪVOS_TRUE

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiProtectFlashCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    /* ��ȡvoice call��ʵ��index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    /* �ж�voice call��ʵ���Ƿ��ڵȴ�FLASH REQ��L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait)
    {
        return VOS_TRUE;
    }

    /* ����ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsSendFlashAckWait = VOS_FALSE;

    CNAS_XCC_SndXcallSendFlashCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                  TAF_XCC_CAUSE_L2_ACK_TIME_OUT);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiProtectBurstDTMFCnfL2Ack_MainCtrl
 ��������  : ����TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK��ʱ����ʱ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE --  ��Ϣ������Ҫ��״̬�������ʸú�������ֵ��ΪVOS_TRUE

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiProtectBurstDTMFCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;


    /* ��ȡvoice call��ʵ��index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    /* �ж�voice call��ʵ���Ƿ��ڵȴ�Send Burst DTMF��L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait)
    {
        return VOS_TRUE;
    }

    /* ����ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait = VOS_FALSE;

    CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                      TAF_XCC_CAUSE_L2_ACK_TIME_OUT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallSendBurstDTMFReq_MainCtrl
 ��������  : ����ID_XCALL_XCC_BURST_DTMF_REQ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallSendBurstDTMFReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    XCALL_XCC_BURST_DTMF_REQ_STRU      *pstXcallBurstDTMFReq = VOS_NULL_PTR;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXcallBurstDTMFReq = (XCALL_XCC_BURST_DTMF_REQ_STRU *)pstMsg;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByCallId(pstXcallBurstDTMFReq->ucCallId, &ucIndex))
    {
        CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXcallBurstDTMFReq->ucCallId, TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE);

        return VOS_TRUE;
    }

    /* �ж�voice call��ʵ��״̬�Ƿ�ΪConversation��Ŀǰֻ֧����conversation̬����Burst DTMF���� */
    if (  (CNAS_XCC_FSM_L1_MAIN != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
       || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXcallBurstDTMFReq->ucCallId, TAF_XCC_CAUSE_ABNORMAL_STATE);

        return VOS_TRUE;
    }

    /* ��CAS����ID_CNAS_CAS_1X_DSCH_DATA_REQ(Send Burst DTMF) */
    if (VOS_OK != CNAS_XCC_SndBurstDTMF_MainCtrl(ucIndex, pstXcallBurstDTMFReq))
    {
        CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXcallBurstDTMFReq->ucCallId, TAF_XCC_CAUSE_ENCODE_FAIL);

        return VOS_TRUE;
    }

    /* ��λ�ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait = VOS_TRUE;

    /* ����TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK */
    CNAS_XCC_StartTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                        TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK,
                        TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndBurstDTMF_MainCtrl
 ��������  : XCC����Send Burst DTMF
 �������  : ucIndex               -- voice callʵ������
             pstXcallBurstDTMFReq  -- Burst DTMF������Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_OK                --  ��Ϣ���ͳɹ�
             VOS_ERR               --  ��Ϣ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_SndBurstDTMF_MainCtrl(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_BURST_DTMF_REQ_STRU      *pstXcallBurstDTMFReq
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucMsgSeqNum;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    /* ����SEQ NUM */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucBurstDtmfSeqNum = CNAS_XCC_AllocSeqNum();
    ucMsgSeqNum = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucBurstDtmfSeqNum;

    /* ��Ҫ����Send Burst DTMF������ɱ��� */
    if (VOS_OK != CNAS_XCC_EncodeSendBurstDTMFMsg(pstXcallBurstDTMFReq,
                                                  aucPduData,
                                                 &ulPduDataLen))
    {
        return VOS_ERR;
    }

    /* ����Send Burst DTMF */
    CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_SEND_BURST_DTMF_MSG,
                               CNAS_XCC_TX_ORDER_TYPE_BUTT,
                               ucMsgSeqNum,
                               (VOS_UINT16)ulPduDataLen,
                               aucPduData);
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessBurstDTMFL2Ack_MainCtrl
 ��������  : ����Send Burst DTMF��L2 ACK
 �������  : ucIndex           -- ��Ϣ����+PID
             pst1xDschDataCnf  -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��ӦSend Burst DTMF��L2 ACK
             VOS_FALSE --  ��Send Burst DTMF��L2 ACK����ǰ�����ڵȴ�Send Burst DTMFL2 ACK��״̬

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessBurstDTMFL2Ack_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* �ж�voice call��ʵ���Ƿ��ڵȴ�Send Burst DTMF��L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait)
    {
        return VOS_FALSE;
    }

    /* �ж�seqNum�Ƿ�һ�� */
    if (pst1xDschDataCnf->ucMsgSeqNum != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucBurstDtmfSeqNum)
    {
        return VOS_FALSE;
    }

    /* ����ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsBurstDtmfAckWait = VOS_FALSE;

    /* ֹͣTI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_BURST_DTMF_CNF_L2_ACK);

    if(CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pst1xDschDataCnf->enRslt)
    {
        enCause = TAF_XCC_CAUSE_SUCCESS;
    }
    else
    {
        enCause = TAF_XCC_CAUSE_L2_ACK_FAIL;
    }

    CNAS_XCC_SndXcallSendBurstDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId, enCause);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xCallTerminateInd_MainCtrl
 ��������  : ����ID_CAS_CNAS_1X_CALL_TERMINATE_IND
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��13��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�

  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X��Ŀ����5�޸�

  3.��    ��   : 2015��1��8��
    ��    ��   : y00245242
    �޸�����   : ����NDSS ORIG����
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xCallTerminateInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                    *pstCallTerminateInd;
    VOS_UINT8                                               ucIndex;

    pstCallTerminateInd = (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU *)pstMsg;

    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByConnId(pstCallTerminateInd->ucConnectId, &ucIndex))
    {
        return VOS_FALSE;
    }

    /* �ж�ʵ���Ƿ��ڵȴ�FLASH REQ��L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(ucIndex);

    /* �ж�ʵ���Ƿ��ڵȴ�Send Burst DTMF��L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(ucIndex);

    /* �ж�ʵ���Ƿ��ڵȴ�Cont DTMF Tone Order��L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(ucIndex);

    CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp(ucIndex);

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xCallRelInd_MainCtrl
 ��������  : ����ID_CAS_CNAS_1X_CALL_REL_IND
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��13��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�

  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X��Ŀ����5�޸�

  3.��    ��   : 2015��1��8��
    ��    ��   : y00245242
    �޸�����   : ����NDSS ORIG����
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xCallRelInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_CALL_REL_IND_STRU                          *pstCallRelInd;
    VOS_UINT8                                               ucIndex;

    pstCallRelInd = (CAS_CNAS_1X_CALL_REL_IND_STRU *)pstMsg;

    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByConnId(pstCallRelInd->ucConnectId, &ucIndex))
    {
        return VOS_TRUE;
    }

    /* �ж�ʵ���Ƿ��ڵȴ�FLASH REQ��L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(ucIndex);

    /* �ж�ʵ���Ƿ��ڵȴ�Send Burst DTMF��L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(ucIndex);

    /* �ж�ʵ���Ƿ��ڵȴ�Cont DTMF Tone Order��L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(ucIndex);

    CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp(ucIndex);

    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXccPowerDownInd_MainCtrl
 ��������  : ����ID_CNAS_XCC_XCC_POWER_DOWN_IND
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��13��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�

  2.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X��Ŀ����5�޸�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXccPowerDownInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_XCC_POWER_DOWN_IND_STRU                       *pstPowerDownInd;
    VOS_UINT8                                               ucIndex;

    pstPowerDownInd = (CNAS_XCC_XCC_POWER_DOWN_IND_STRU *)pstMsg;

    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByConnId(pstPowerDownInd->ucConnectId, &ucIndex))
    {
        return VOS_TRUE;
    }

    /* �ж�ʵ���Ƿ��ڵȴ�FLASH REQ��L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(ucIndex);

    /* �ж�ʵ���Ƿ��ڵȴ�Send Burst DTMF��L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(ucIndex);

    /* �ж�ʵ���Ƿ��ڵȴ�Cont DTMF Tone Order��L2 ACK */
    CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(ucIndex);

    CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp(ucIndex);

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xCschFeatureNotificationMsgInd_MainCtrl
 ��������  : ����CAS_CNAS_1X_RX_COMMON_FEATURE_NOTIFICATION_MSG
 �������  : pstCschDataInd -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xCschFeatureNotificationMsgInd_MainCtrl(
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstCschDataInd
)
{
    CNAS_XCC_FNM_STRU                  *pstFNM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;


    /* ���FNM�Ľ��� */
    pstFNM = (CNAS_XCC_FNM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_FNM_STRU));
    if (VOS_NULL_PTR == pstFNM)
    {
        return VOS_TRUE;
    }

    if (VOS_OK != CNAS_XCC_DecodeFeatureNotificationMsg(pstCschDataInd, pstFNM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstFNM);
        return VOS_TRUE;
    }

    /* ��������MS ACK�Ĵ���Ŀǰ�Ĵ����Ƕ��ź�XCC��Ҫ�жϹ����ŵ��ϵ���Ϣ�Ƿ���Ҫȷ�ϣ������Ҫ
    ����ȷ�ϣ�����MS ACK������ */
    if ( VOS_TRUE == pstCschDataInd->enAckReqFlag )
    {
        if (VOS_OK == CNAS_XCC_EncodeCschMsAckOrderMsg(aucPduData, &ulPduDataLen))
        {
            CNAS_XCC_SndCasCschDataReq(CAS_CNAS_1X_TX_COMMON_ORDER_MSG,
                                       pstCschDataInd->enAckReqFlag,
                                       pstCschDataInd->aucAckPara,
                                       (VOS_UINT16)ulPduDataLen,
                                       aucPduData);
        }
    }


    if (VOS_TRUE == pstFNM->ucIsRelease)
    {
        /* ֪ͨ�����绰�ͷţ�����REL REQ��CAS */
        CNAS_XCC_SndCasCallRelReq(0, 0, CAS_CNAS_1X_REL_REASON_FNM_RELEASE,VOS_TRUE);
    }


    /* ���ҽ����Ľ�����Ƿ���Message Waiting��еĻ���֪ͨXSMS*/
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_MESSAGE_WAITING,
                                                           pstFNM->ucNumInfoRecs,
                                                           pstFNM->astInfoRecsData,
                                                           &ucIndex);
    if (VOS_TRUE == ulResult)
    {
        CNAS_XCC_SndCsmsMsgWaitingInd(pstFNM->astInfoRecsData[ucIndex].stInfoRecs.u.stMsgWaiting.ucMsgCnt);
    }


    /* ��Ϣͨ��ID_XCC_XCALL_INFO_REC_IND�ϱ���XCALL */
    CNAS_XCC_SndXcallCschInfoRecInd(CNAS_XCC_INVAILD_CALL_ID,
                                    CAS_CNAS_1X_RX_COMMON_FEATURE_NOTIFICATION_MSG,
                                    (VOS_UINT8*)pstFNM);


    PS_MEM_FREE(UEPS_PID_XCC, pstFNM);
    return VOS_TRUE;

}



/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xCschDataInd_L1Main_MainCtrl
 ��������  : ����ID_CAS_CNAS_1X_CSCH_DATA_IND
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xCschDataInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstCschDataInd  = VOS_NULL_PTR;


    pstCschDataInd  = (CAS_CNAS_1X_CSCH_DATA_IND_STRU*)pstMsg;


    switch(pstCschDataInd->enCschMsgType)
    {
        case CAS_CNAS_1X_RX_COMMON_FEATURE_NOTIFICATION_MSG:
            CNAS_XCC_ProcessCas1xCschFeatureNotificationMsgInd_MainCtrl(pstCschDataInd);

            CNAS_MNTN_Log1xCschDataIndMsg(UEPS_PID_XCC,
                                          pstCschDataInd->usMsgDataLen,
                                          pstCschDataInd->enCschMsgType,
                                          pstCschDataInd->aucMsgData);
            break;

        default:
            CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcessCas1xCschDataInd_MainCtrl wrong Msg Type", pstCschDataInd->enCschMsgType);
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xTchServiceOptionControlMsgInd_L1Main_MainCtrl
 ��������  : ����CAS_CNAS_1X_RX_TCH_SERVICE_OPTION_CONTROL_MSG
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xTchServiceOptionControlMsgInd_MainCtrl(
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd  = VOS_NULL_PTR;
    CNAS_XCC_SOCM_STRU                  stSOCM;

    pstDschDataInd  = (CAS_CNAS_1X_DSCH_DATA_IND_STRU*)pstMsg;
    if (VOS_OK != CNAS_XCC_DecodeServiceOptionControlMsg(pstDschDataInd, &stSOCM))
    {
        return VOS_TRUE;
    }

    switch (stSOCM.usSo)
    {
        case CAS_CNAS_1X_SO_3_EVRC:
        case CAS_CNAS_1X_SO_68_EVRC_B:
            CNAS_XCC_ProcessVoiceSoCtrlMsg_MainCtrl(&stSOCM);
            break;

        case CAS_CNAS_1X_SO_33_PPP_PKT_DATA_CDMA2K:
            CNAS_XCC_ProcessDataSoCtrlMsg_MainCtrl(&stSOCM);
            break;

        /* only support data service and voice service */
        default:
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessVoiceSoCtrlMsg_MainCtrl
 ��������  : ����������ҵ���Service Option Control��Ϣ
 �������  : pstSOCM   -- ������Ϣ����
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessVoiceSoCtrlMsg_MainCtrl(
    CNAS_XCC_SOCM_STRU                 *pstSOCM
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;
    VOS_UINT8                           ucOctetLen;

    /* get the voice call entity��if can not find��return */
    if (VOS_FALSE == CNAS_XCC_GetCallInstanceIndexByCallRef(pstSOCM->ucConRef, &ucIndex))
    {
        return;
    }

    /* if para is invalid, return */
    if (VOS_FALSE == CNAS_XCC_VoiceSoCtrlMsgParaCheck(pstSOCM))
    {
        return;
    }

    /* ��ǰ������SOCM��Ϣ������8bit���������������ֱ��ȡ���� */
    ucOctetLen = (VOS_UINT8)(pstSOCM->usBitLen / CNAS_XCC_OCTET_BIT_LEN);

    /*  the USE_TIME field is set to '1', the base station shall set this field
         to the System Time, in units of 80 ms (modulo 64), at which the message
         is to take effect.  If the USE_TIME field set to '0' the base station shall
         set this field to '00000' */
    if (0 == pstSOCM->ucUseTime)
    {
        pstSOCM->ucActionTime = 0;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    pstCallInfo = (CNAS_XCC_CALL_INFO_CTX_STRU*)(&(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx));

    /* Send Mesaage to XCALL */
    CNAS_XCC_SndXcallSoCtrlMsgInd(pstCallInfo,
                                  pstSOCM->aucData,
                                  ucOctetLen,
                                  pstSOCM->ucActionTime);

}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessDataSoCtrlMsg_MainCtrl
 ��������  : ����������ҵ���Service Option Control��Ϣ
 �������  : pstSOCM   -- ������Ϣ����
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessDataSoCtrlMsg_MainCtrl(
    CNAS_XCC_SOCM_STRU                 *pstSOCM
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo;

    /* ��ȡ����ҵ��ĺ���ʵ�壬����Ҳ�����ֱ�ӷ��� */
    if (VOS_FALSE == CNAS_XCC_GetCallInstanceIndexByCallRef(pstSOCM->ucConRef, &ucIndex))
    {
        return;
    }


    if (VOS_FALSE == CNAS_XCC_DataSoCtrlMsgParaCheck(pstSOCM))
    {
        return;
    }

    /*  the USE_TIME field is set to '1', the base station shall set this field
         to the System Time, in units of 80 ms (modulo 64), at which the message
         is to take effect.  If the USE_TIME field set to '0' the base station shall
         set this field to '00000' */
    if (0 == pstSOCM->ucUseTime)
    {
        pstSOCM->ucActionTime = 0;
    }


    /* ��������£�����ID_XCC_APS_SO_CTRL_MSG_IND��APS */
    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    pstCallInfo = (CNAS_XCC_CALL_INFO_CTX_STRU*)(&(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx));
    CNAS_XCC_SndApsSoCtrlMsgInd(pstCallInfo, pstSOCM);

}



/*****************************************************************************
 �� �� ��  : CNAS_XCC_IsSendingEmcFlashMsgAllowed_MainCtrl
 ��������  : check sending emergency call FWI/EFWI message allowed or not
 �������  : ucCurInstanceIndex----current call instance index
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- need send flash msg
             VOS_FALSE -- need not send flash msg

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_IsSendingEmcFlashMsgAllowed_MainCtrl(
    VOS_UINT8                           ucCurInstanceIndex
)
{
    CNAS_XCC_FSM_ID_ENUM_UINT32         enFsmId;
    VOS_UINT32                          ulState;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    ulState       = pstXccCtxAddr->astFsmEntity[ucCurInstanceIndex].stCurFsm.ulState;
    enFsmId       = pstXccCtxAddr->astFsmEntity[ucCurInstanceIndex].stCurFsm.enFsmId;

    /* follow C.S0005 protocol, converstation sate,wait for answer state, wait or order state should
       send a flash with info message while receive a emergency call.But follow Q logic,while in wait
       for order state,the ui did not show "ring",so here easy to process :return orig fail with one
       special cause to uplayer the redial in the next state. */
    if ((CNAS_XCC_FSM_L1_MAIN           == enFsmId)
     && (CNAS_XCC_L1_STA_CONVERSATION   == ulState))
    {
        return VOS_TRUE;
    }

    if (CNAS_XCC_FSM_MT_CALLING == enFsmId)
    {
        switch(ulState)
        {
            case CNAS_XCC_MT_CALLING_STA_WAIT_FOR_ANSWER:
            case CNAS_XCC_MT_CALLING_STA_WAIT_FOR_INCOMING_RSP:

                if (CNAS_CCB_GetPRevInUse() >= P_REV_IN_USE_7)
                {
                    return VOS_TRUE;
                }
                else
                {
                    return VOS_FALSE;
                }

            default:

                return VOS_FALSE;
        }
    }

    /* else for wait for order state, also send back one speical cause to the uplayer
       and wait the uplayer to retry later. */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallEmgencyCallReq_MainCtrl
 ��������  : process emergency call reqest message
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 5 Modified
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallEmergencyCallReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucSeqNum;
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstXcallOrigReq = VOS_NULL_PTR;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;

    pstXcallOrigReq = (XCALL_XCC_ORIG_CALL_REQ_STRU *)pstMsg;

    /* if voice call instance does not exist,continue process in the state machine. */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_FALSE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
    ucCallId      = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId;

    /* send emergency call flash with info message following the C.S0005 protocol */
    /* If the Call Control instance receives an indication that the user has originated
       an  emergency call (see 2.6.4.3), the mobile station shall send a Flash With Information
       Message or an Extended Flash With Information Message in assured mode with a  Global
       Emergency Call Information Record */

    /* allocate new sequence number and save it */
    ucSeqNum = CNAS_XCC_AllocSeqNum();

    if (VOS_FALSE == CNAS_XCC_SndFWIorEFWIWithEmergencyCallReq_MainCtrl(ucIndex, ucSeqNum, pstXcallOrigReq))
    {
        CNAS_XCC_SndXcallOrigCallCnf(pstXcallOrigReq->ucCallId, TAF_XCC_FAIL_LAYER_L3, TAF_XCC_CAUSE_ENCODE_FAIL, TAF_XCC_CALLID_NULL, 0);

        return VOS_TRUE;
    }

    CNAS_XCC_SetWaitEmcFlashMsgRspFlg(VOS_TRUE);

    CNAS_XCC_SaveEmcFlashMsgSeqNum(ucSeqNum);

    CNAS_XCC_SaveEmcCallId(pstXcallOrigReq->ucCallId);
    CNAS_XCC_SaveMtVoiceCallId(ucCallId);

    CNAS_XCC_StartTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                        TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK,
                        TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndFWIorEFWIWithEmergencyCallReq_MainCtrl
 ��������  : XCC send emergency call flash message
 �������  : ucIndex           -- voice callʵ������
             *pstXcallFlashReq
 �������  : ��
 �� �� ֵ  : VOS_OK    --  ��Ϣ���ͳɹ�
             VOS_ERR   --  ��Ϣ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 5 Modified
*****************************************************************************/
VOS_UINT32 CNAS_XCC_SndFWIorEFWIWithEmergencyCallReq_MainCtrl(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucMsgSeqNum,
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigReq
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    /*
        If this Call Control instance is identified by NULL, the mobile station shall send  either
        a Flash With Information Message or an Extended Flash With Information Message (with either
        the CON_REF_INCL field of the message set to '0' or the CON_REF_INCL field set to '1' and
        the CON_REF field set to the connection reference of the service option connection corresponding
        to this call); otherwise,the mobile station shall send an Extended Flash With Information Message,
        with the CON_REF_INCL field of the message set to '1' and the CON_REF field of the  message set to
        the connection reference of the service option connection  corresponding to this call.
    */

    if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsNullCc)
    {
        /* ucIsNullCc = 1ʱ�������Э��汾���Ͳ�ͬType��FWI��Ϣ */
        if (P_REV_IN_USE_7 > CNAS_CCB_GetPRevInUse())
        {
            /* ��Ҫ����FWI�������FWI�ı��� Type = KEYPAD_FACILITY */
            if (VOS_OK != CNAS_XCC_EncodeFlashWithInformationMsgWithFlashReq(pstOrigReq->stCalledPartyNum.ucDigitNum,
                                                                         pstOrigReq->stCalledPartyNum.aucDigit,
                                                                         aucPduData,
                                                                         &ulPduDataLen))
            {
                return VOS_FALSE;
            }
        }
        else
        {
            /* ��Ҫ����FWI�������FWI�ı��룬Type = EMERGENCY_CALL */
            if (VOS_OK != CNAS_XCC_EncodeFlashWithInformationMsgWithEmergencyCallReq(pstOrigReq->enDigitMode,
                                                                               &(pstOrigReq->stCalledPartyNum),
                                                                               aucPduData,
                                                                               &ulPduDataLen))
            {
                return VOS_FALSE;
            }
        }

        /* ����FWI */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_FLASH_WITH_INFORMATION_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_BUTT,
                                   ucMsgSeqNum,
                                   (VOS_UINT16)ulPduDataLen,
                                   aucPduData);

    }
    else
    {
        /* ��Ҫ����EFWI�������EFWI�ı��� */
        if (VOS_OK != CNAS_XCC_EncodeExtendedFlashWithInformationMsgWithEmergencyCallReq(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConRef,
                                                                                   pstOrigReq->enDigitMode,
                                                                                   &(pstOrigReq->stCalledPartyNum),
                                                                                   aucPduData,
                                                                                   &ulPduDataLen))
        {
            return VOS_FALSE;
        }

        /* ����EFWI */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_EXT_FLASH_WITH_INFORMATION_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_BUTT,
                                   ucMsgSeqNum,
                                   (VOS_UINT16)ulPduDataLen,
                                   aucPduData);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessHangupCallReqWhenWaitEmcFlashMsgRsp
 ��������  : process the hang up call request when waiting for the respnose of the emc FWI/EFWI msg
 �������  : ucIndex-------------------current call instance index
             pstHangupReq -------------hangup call request message
 �������  : VOS_VOID
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 5 Modified

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessHangupCallReqWhenWaitEmcFlashMsgRsp(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_HANGUP_CALL_REQ_STRU     *pstHangupReq
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucEmcCallId;
    VOS_UINT8                           ucMtVoiceCallId;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_FALSE == CNAS_XCC_GetWaitEmcFlashMsgRspFlg())
    {
        return VOS_FALSE;
    }

    /* no matter hangup the mt voice call or the emergency call, we should stop the timer and
       clear the emc ctrl info. */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK);

    ucEmcCallId     = CNAS_XCC_GetEmcCallId();
    ucMtVoiceCallId = CNAS_XCC_GetMtVoiceCallId();

    CNAS_XCC_InitEmergencyCallCtrlCtx(&(pstXccCtxAddr->stMainCtrlCtx.stEmcCallCtrl));

    /* if hangup emergency call, we response the hangup cnf to uplayer and this message
       need not process any more. */
    if (ucEmcCallId == pstHangupReq->ucCallId)
    {
        CNAS_XCC_SndXcallHangUpCallCnf(ucEmcCallId);

        return VOS_TRUE;
    }

    /* if hangup mt voice call,we should disconnect the emergency call and this meesage
       should be continue processed in the state machine. */
    if (ucMtVoiceCallId == pstHangupReq->ucCallId)
    {
        CNAS_XCC_SndXcallOrigCallCnf(ucEmcCallId, TAF_XCC_FAIL_LAYER_L3, TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE, TAF_XCC_CALLID_NULL, 0);

        return VOS_FALSE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessEmergencyCallFlashMsgRsp_MainCtrl
 ��������  : process the respnose of the emc FWI/EFWI msg
 �������  : ucIndex-------------------current call instance index
             pst1xDschDataCnf ---------the response of the emc FWI/EFWI msg
 �������  : VOS_VOID
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 5 Modified

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessEmergencyCallFlashMsgRsp_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucEmcSeqNum;
    VOS_UINT8                           ucOrigCallId;

    ucOrigCallId                        = TAF_XCC_CALLID_NULL;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_FALSE == CNAS_XCC_GetWaitEmcFlashMsgRspFlg())
    {
        return VOS_FALSE;
    }

    /* compare the sequence number,if not match, return */
    ucEmcSeqNum = CNAS_XCC_GetEmcFlashMsgSeqNum();

    if (ucEmcSeqNum != pst1xDschDataCnf->ucMsgSeqNum)
    {
        return VOS_FALSE;
    }

    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pst1xDschDataCnf->enRslt)
    {
        ucOrigCallId                    = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId;
    }

    /* stop the timer and clear the emc ctrl info. */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK);

    CNAS_XCC_SndXcallOrigCallCnf(CNAS_XCC_GetEmcCallId(),
                                 TAF_XCC_FAIL_LAYER_L3,
                                 TAF_XCC_CAUSE_EMERGENCY_CALL_FLASHED,
                                 ucOrigCallId,
                                 0);

    CNAS_XCC_InitEmergencyCallCtrlCtx(&(pstXccCtxAddr->stMainCtrlCtx.stEmcCallCtrl));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiWaitEmergencyCallFlashCnfL2Ack_MainCtrl
 ��������  : process the expired of the timer:TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE --  ��Ϣ������Ҫ��״̬�������ʸú�������ֵ��ΪVOS_TRUE

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration Modifed
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiWaitEmergencyCallFlashCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_MAIN_CTRL_CTX_STRU        *pstMainCtrlCtx = VOS_NULL_PTR;

    /* ��ȡvoice call��ʵ��index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    if (VOS_FALSE == CNAS_XCC_GetWaitEmcFlashMsgRspFlg())
    {
        return VOS_TRUE;
    }

    pstMainCtrlCtx = CNAS_XCC_GetMainCtrlCtx();

    CNAS_XCC_SndXcallOrigCallCnf(CNAS_XCC_GetEmcCallId(), TAF_XCC_FAIL_LAYER_L3, TAF_XCC_CAUSE_L2_ACK_TIME_OUT, TAF_XCC_CALLID_NULL, 0);

    CNAS_XCC_InitEmergencyCallCtrlCtx(&(pstMainCtrlCtx->stEmcCallCtrl));

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp
 ��������  : process the release when waiting for the respnose of the emc FWI/EFWI msg
 �������  : ucIndex-------------------current call instance index
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 5 Modified

*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_FALSE == CNAS_XCC_GetWaitEmcFlashMsgRspFlg())
    {
        return;
    }

    ucCallId = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId;

    /* check the mt voice call id matahed or not */
    if (ucCallId != CNAS_XCC_GetMtVoiceCallId())
    {
        return;
    }

    /* stop the timer and clear the emc ctrl info. */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_EMERGENCY_CALL_FLASH_CNF_L2_ACK);

    CNAS_XCC_SndXcallOrigCallCnf(CNAS_XCC_GetEmcCallId(), TAF_XCC_FAIL_LAYER_L3, TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE, TAF_XCC_CALLID_NULL, 0);

    CNAS_XCC_InitEmergencyCallCtrlCtx(&(pstXccCtxAddr->stMainCtrlCtx.stEmcCallCtrl));

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xNdssRecordDialedDigitsInd_MainCtrl
 ��������  : �����ں��й����У��������н��������л������TCH̬�£�����ҵ���ض���
             ���д���
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��06��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xNdssRecordDialedDigitsInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;

    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    CNAS_XCC_FSM_ENTITY_STRU           *pstFsmEntity = VOS_NULL_PTR;

    ucIndex = CNAS_XCC_GetLastCallIndex();

    if (CNAS_XCC_INVAILD_CALL_INDEX == ucIndex)
    {
        return VOS_TRUE;
    }

    pstFsmEntity = &(CNAS_XCC_GetCtxAddr()->astFsmEntity[ucIndex]);

    /* ����ʵ���Ѿ�ȥ����˳����� */
    if (VOS_FALSE == pstFsmEntity->stCallInfoCtx.ucIsEntityActive)
    {
        return VOS_TRUE;
    }

    /* ������ƽ�ʵ����TCH״̬�µ����һ·����������������У� ���Բ���Э�鶨���NDSS�����ز���
       ����������ԭ�е��ز�����.
       */
    /* ��SOת����SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstFsmEntity->stCallInfoCtx.enCurrentSo, &enServiceType);

    if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
    {
        /* �ж�ʵ���Ƿ��ڵȴ�FLASH REQ��L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndFlashReq(ucIndex);

        /* �ж�ʵ���Ƿ��ڵȴ�Send Burst DTMF��L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndBurstDtmfReq(ucIndex);

        /* �ж�ʵ���Ƿ��ڵȴ�Cont DTMF Tone Order��L2 ACK */
        CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(ucIndex);

        CNAS_XCC_ProcessReleaseWhenWaitEmcFlashMsgRsp(ucIndex);

        /* ����XCC�ڲ���Ϣ��֪ͨNDSS redial indication */
        CNAS_XCC_SndXccNdssRedialInd(pstFsmEntity->stCallInfoCtx.ucConnectId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXsdNdssResultInd_MainCtrl
 ��������  : ����XSD���й������ض�����������ֱ��͸����TAF
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��08��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXsdNdssResultInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_XCC_NDSS_RESULT_IND_STRU       *pstNdssResultInd = VOS_NULL_PTR;

    pstNdssResultInd = (XSD_XCC_NDSS_RESULT_IND_STRU *)pstMsg;

    CNAS_XCC_SndXcallNdssResultInd((XCC_XCALL_NDSS_RESULT_ENUM_UINT8)pstNdssResultInd->enNsddResult);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessApsPzidInfoNtf_MainCtrl
 ��������  : ����Aps��Pzid��Ϣ�����͸�����
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��10��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessApsPzidInfoNtf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_PZID_INFO_NTF_STRU         *pstPzidInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;
    VOS_UINT8                           ucConRef;

    pstPzidInfo = (APS_XCC_PZID_INFO_NTF_STRU*)pstMsg;

    ulRslt = CNAS_XCC_GetCallInstanceIndexByConnId(pstPzidInfo->ucConnectId,&ucIndex);

    if (VOS_TRUE == ulRslt)
    {
        pstXccCtxAddr = CNAS_XCC_GetCtxAddr();
        ucConRef = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConRef;
        ulPduDataLen= 0;
        NAS_MEM_SET_S(aucPduData, sizeof(aucPduData), 0, sizeof(aucPduData));
        if (VOS_OK != CNAS_XCC_EncodeServiceOptionCtrlMsg(pstPzidInfo, ucConRef,aucPduData,&ulPduDataLen))
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_ProcessApsPzidInfoNtf_MainCtrl: Encode fail");
            return VOS_TRUE;
        }

        /* ����SERVICE OPTION CONTROL MESSAG */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_SERVICE_OPTION_CONTROL_MSG,
                                   CNAS_XCC_TX_ORDER_TYPE_BUTT,
                                   0,
                                   (VOS_UINT16)ulPduDataLen,
                                   aucPduData);


    }


    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessReserveSrIdNtf_MainCtrl
 ��������  : ����APS֪ͨˢ��SR_ID
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��15��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessReserveSrIdNtf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_XCC_RESERVE_SR_ID_NTF_STRU     *pstSrIdNtf = VOS_NULL_PTR;

    pstSrIdNtf = (APS_XCC_RESERVE_SR_ID_NTF_STRU*)pstMsg;

    CNAS_XCC_UpdateSrIdUsed(pstSrIdNtf->enSo,
                            pstSrIdNtf->ucSrId,
                            CNAS_XCC_INVAILD_CON_ID);


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXCallStateInd_MainCtrl
 ��������  : call state  ״̬��Ϣ�ı�ʱ���ϱ�
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXCallStateInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucVoicceCallState;
    VOS_UINT8                           ucPsCallState;
    VOS_UINT8                           ucSmsCallState;
    VOS_UINT8                           ucCurrCallState;

    ucVoicceCallState = CNAS_CCB_Get1xVoiceCallState();
    ucPsCallState     = CNAS_CCB_Get1xPsCallState();
    ucSmsCallState    = CNAS_CCB_Get1xSmsCallState();

    if ((CNAS_CCB_1X_CALL_STATE_BUTT != ucVoicceCallState)
    && (CNAS_CCB_1X_CALL_STATE_IDLE!= ucVoicceCallState))
    {
        ucCurrCallState = CNAS_XCC_Convert1XcallState(ucVoicceCallState);
    }
    else if ((CNAS_CCB_1X_CALL_STATE_ORIG_CALL == ucPsCallState)
          || (CNAS_CCB_1X_CALL_STATE_ORIG_CALL == ucSmsCallState))
    {
        ucCurrCallState = XCC_MMA_1X_CALL_STATE_ORIG_CALL;
    }
    else if ((CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL == ucPsCallState)
          || (CNAS_CCB_1X_CALL_STATE_INCOMMING_CALL == ucSmsCallState))
    {
        ucCurrCallState = XCC_MMA_1X_CALL_STATE_INCOMMING_CALL;
    }
    else if ((CNAS_CCB_1X_CALL_STATE_CONVERSATION == ucPsCallState)
          || (CNAS_CCB_1X_CALL_STATE_CONVERSATION == ucSmsCallState))
    {
        ucCurrCallState = XCC_MMA_1X_CALL_STATE_CONVERSATION;
    }
    else
    {
        ucCurrCallState = XCC_MMA_1X_CALL_STATE_IDLE;
    }
    CNAS_XCC_SndMma1XCallState(ucCurrCallState);

    return VOS_TRUE;
}




VOS_VOID CNAS_XCC_ProcessCas1xTchSndBurstDtmfMsgInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU                         *pst1xDschDataInd = VOS_NULL_PTR;
    CNAS_XCC_SEND_BURST_DTMF_STRU                           stSndBurstDtmfMsg;
    CNAS_XCC_CTX_STRU                                      *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;
    VOS_UINT8                                               ucCallId;
    CNAS_XCC_DECODE_RESULT_ENUM_UINT8                       enDecodeRslt;
    CNAS_XCC_REV_MS_REJECT_ORDQ_ENUM_UINT8                  enRejOrdq;

    pst1xDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU*)pstMsg;

    NAS_MEM_SET_S(&stSndBurstDtmfMsg, sizeof(CNAS_XCC_SEND_BURST_DTMF_STRU), 0x00, sizeof(CNAS_XCC_SEND_BURST_DTMF_STRU));

    /* Decode the CAS DSCH Data Ind message */
    enDecodeRslt = CNAS_XCC_DecodeSndBurstDtmfMsg(pst1xDschDataInd, &stSndBurstDtmfMsg);

    if (CNAS_XCC_DECODE_RSLT_SUCCESS != enDecodeRslt)
    {
        /* If the decode process is not success, then XCC sends Message Reject Order to CAS */
        if (CNAS_XCC_DECODE_RSLT_INVALID_FIELD == enDecodeRslt)
        {
            enRejOrdq = CNAS_XCC_REV_ORDER_MS_REJECT_FIELD;
        }
        else
        {
            enRejOrdq = CNAS_XCC_REV_ORDER_MS_REJECT_STRUCT;
        }

        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stSndBurstDtmfMsg.ucConRef, enRejOrdq);

        return;
    }

    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByCallRef(stSndBurstDtmfMsg.ucConRef, &ucIndex))
    {
        /* If the Call Instance cannot be found from the input Con_Ref, XCC will send Message Reject Order to CAS */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stSndBurstDtmfMsg.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_NO_CC_INST);

        return;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if ((CNAS_XCC_FSM_L1_MAIN != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        /* If the Current FSM is not L1 Main Or the current FSM state is not Conversation, then XCC sends Message Reject Order
        to CAS */
        CNAS_XCC_SendComDschDataRejectOrder(pst1xDschDataInd, stSndBurstDtmfMsg.ucConRef, CNAS_XCC_REV_ORDER_MS_REJECT_STATE);

        return;
    }

    ucCallId = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId;

    /* XCC sends BURST DTMF Request to XCALL */
    CNAS_XCC_SndXcallBurstDtmfInd(ucCallId, &stSndBurstDtmfMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallSendContDTMFReq_MainCtrl
 ��������  : ����ID_XCALL_XCC_SEND_CONT_DTMF_REQ��Ϣ���򷵻�ʧ�ܣ�����CAS������Ϣ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��25��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallSendContDTMFReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    XCALL_XCC_SEND_CONT_DTMF_REQ_STRU  *pstXcallContDTMFReq = VOS_NULL_PTR;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXcallContDTMFReq = (XCALL_XCC_SEND_CONT_DTMF_REQ_STRU *)pstMsg;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* ��ȡʵ������ȡʧ�ܱ�ʾ�쳣����XCALL��Ӧʧ�� */
    if (VOS_TRUE != CNAS_XCC_GetCallInstanceIndexByCallId(pstXcallContDTMFReq->ucCallId, &ucIndex))
    {
        CNAS_XCC_SndXcallSendContDTMFCnf(pstXcallContDTMFReq->ucCallId, TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE);

        return VOS_TRUE;
    }

    /* �ж�voice call��ʵ��״̬�Ƿ�ΪConversation��Ŀǰֻ֧����conversation̬����Cont DTMF Tone Order */
    if ((CNAS_XCC_FSM_L1_MAIN != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
       || (CNAS_XCC_L1_STA_CONVERSATION != pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        CNAS_XCC_SndXcallSendContDTMFCnf(pstXcallContDTMFReq->ucCallId, TAF_XCC_CAUSE_ABNORMAL_STATE);

        return VOS_TRUE;
    }

    /* ��CAS����ID_CNAS_CAS_1X_DSCH_DATA_REQ(CONT DTMF Tone Order) */
    if (VOS_OK != CNAS_XCC_SndContDTMFToneOrder_MainCtrl(ucIndex, pstXcallContDTMFReq))
    {
        CNAS_XCC_SndXcallSendContDTMFCnf(pstXcallContDTMFReq->ucCallId, TAF_XCC_CAUSE_ENCODE_FAIL);

        return VOS_TRUE;
    }

    /* ��λ�ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait = VOS_TRUE;

    /* ����TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK */
    CNAS_XCC_StartTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                        TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK,
                        TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndContDTMFToneOrder_MainCtrl
 ��������  : XCC����Send Cont DTMF Tone Order
 �������  : ucIndex               -- voice callʵ������
             pstXcallContDTMFReq  --  Cont DTMF������Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_OK                --  ��Ϣ���ͳɹ�
             VOS_ERR               --  ��Ϣ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��24��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_SndContDTMFToneOrder_MainCtrl(
    VOS_UINT8                           ucIndex,
    XCALL_XCC_SEND_CONT_DTMF_REQ_STRU  *pstXcallContDTMFReq
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                           ucContDtmfSeqNum;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    VOS_UINT32                          ulPduDataLen;
    CNAS_XCC_TX_ORDER_TYPE_ENUM_UINT8   enOrderType;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    ulPduDataLen = 0;
    NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

    /* ��Ҫ����Send Cont DTMF Tone Order������ɱ��� */
    if (VOS_OK != CNAS_XCC_EncodeSendContDTMFToneOrder(pstXcallContDTMFReq,
                                                       aucPduData,
                                                       &ulPduDataLen,
                                                       ucIndex))
    {
        return VOS_ERR;
    }

    /* ����SEQ NUM */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucContDtmfSeqNum = CNAS_XCC_AllocSeqNum();
    ucContDtmfSeqNum = pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucContDtmfSeqNum;

    /* Cont DTMF Tone Order ��ΪStart �� Stop */
    if (XCALL_XCC_CONT_DTMF_STOP == pstXcallContDTMFReq->enSwitch)
    {
        enOrderType = CNAS_XCC_TX_ORDER_TYPE_CONTINUOUS_DTMF_TONE_STOP_ORDER;
    }
    else
    {
        enOrderType = CNAS_XCC_TX_ORDER_TYPE_CONTINUOUS_DTMF_TONE_START_ORDER;
    }

    /* ����Send Cont DTMF Tone Order */
    CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, enOrderType,
                               ucContDtmfSeqNum, (VOS_UINT16)ulPduDataLen, aucPduData);

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessContDTMFToneOrderL2Ack_MainCtrl
 ��������  : ����Cont DTMF Tone Order��L2 ACK
 �������  : ucIndex           -- ��Ϣ����+PID
             pst1xDschDataCnf  -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��ӦCont DTMF Tone Order��L2 ACK
             VOS_FALSE --  ��Cont DTMF Tone Order��L2 ACK����ǰ�����ڵȴ�Cont DTMF Tone Order��״̬

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��25��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessContDTMFToneOrderL2Ack_MainCtrl(
    VOS_UINT8                           ucIndex,
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pst1xDschDataCnf
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32           enCause;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* �ж�voice call��ʵ���Ƿ��ڵȴ�Cont DTMF Tone Order��L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait)
    {
        return VOS_FALSE;
    }

    /* �ж�seqNum�Ƿ�һ�� */
    if (pst1xDschDataCnf->ucMsgSeqNum != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucContDtmfSeqNum)
    {
        return VOS_FALSE;
    }

    /* ����ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait = VOS_FALSE;

    /* ֹͣTI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK);

    /* ���L2 Ack���ؽ�� */
    if(CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pst1xDschDataCnf->enRslt)
    {
        enCause = TAF_XCC_CAUSE_SUCCESS;
    }
    else
    {
        enCause = TAF_XCC_CAUSE_L2_ACK_FAIL;
    }

    CNAS_XCC_SndXcallSendContDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId, enCause);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiProtectContDTMFCnfL2Ack_MainCtrl
 ��������  : ����TI_CNAS_XCC_WAIT_Cont_DTMF_CNF_L2_ACK��ʱ����ʱ
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE --  ��Ϣ������Ҫ��״̬�������ʸú�������ֵ��ΪVOS_TRUE

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��25��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiProtectContDTMFCnfL2Ack_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    /* ��ȡvoice call��ʵ��index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* �ж�voice call��ʵ���Ƿ��ڵȴ�Cont DTMF Tone Order��L2 ACK */
    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait)
    {
        return VOS_TRUE;
    }

    /* ����ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait = VOS_FALSE;

    CNAS_XCC_SndXcallSendContDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                      TAF_XCC_CAUSE_L2_ACK_TIME_OUT);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder
 ��������  : ��Send Cont DTMF Tone Order�����еȴ�L2 ACK״̬�£�����绰�Ҷ�(�����Ҷϻ�����Ҷ�)
 �������  : ucIndex
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��27��
    ��    ��   : L00324781
    �޸�����   : Iter 16 ����

*****************************************************************************/
VOS_VOID CNAS_XCC_ProcessReleaseWhenWaitForL2AckDuringSndContDtmfToneOrder(
    VOS_UINT8                           ucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    if (VOS_TRUE != pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait)
    {
        return;
    }

    /* ����ȴ�ACK�ı�� */
    pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucIsContDtmfAckWait = VOS_FALSE;

    /* ֹͣTI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK */
    CNAS_XCC_StopTimer(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucConnectId,
                       TI_CNAS_XCC_WAIT_CONT_DTMF_CNF_L2_ACK);

    CNAS_XCC_SndXcallSendContDTMFCnf(pstXccCtxAddr->astFsmEntity[ucIndex].stCallInfoCtx.ucCallId,
                                      TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE);

    return;
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallEccServiceReq_MainCtrl
 ��������  : Ԥ����ID_XCALL_XCC_ECC_SERVICE_REQ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallEccServiceReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    /* ��ȡvoice call��ʵ��index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        CNAS_XCC_SndXcallEccServiceCnf(XCC_XCALL_ECC_SERVICE_RESULT_FAIL);
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* �ж�voice call��ʵ��״̬ ,������� CNAS_XCC_L1_STA_ENDING״̬, ֱ�Ӹ�XCALL �ظ�ʧ��*/
    if ((CNAS_XCC_FSM_L1_MAIN == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     && (CNAS_XCC_L1_STA_ENDING == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        CNAS_XCC_SndXcallEccServiceCnf(XCC_XCALL_ECC_SERVICE_RESULT_FAIL);
        return VOS_TRUE;
    }

    /*����״̬����CAS �·�ҵ������*/
    CNAS_XCC_SndCasEccServiceReq();
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xEccServiceCnf_MainCtrl
 ��������  : Ԥ����ID_CAS_CNAS_1X_ECC_SERVICE_CNF
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xEccServiceCnf_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucIndex;
    CNAS_XCC_CTX_STRU                                      *pstXccCtxAddr = VOS_NULL_PTR;
    CAS_CNAS_1X_ECC_SERVICE_CNF_STRU                       *pstEccServiceCnf = VOS_NULL_PTR;
    XCC_XCALL_ECC_SERVICE_RESULT_ENUM_UINT8                 enRslt;

    pstEccServiceCnf = (CAS_CNAS_1X_ECC_SERVICE_CNF_STRU *)pstMsg;
    enRslt = XCC_XCALL_ECC_SERVICE_RESULT_SUCC;

    /* ��ȡvoice call��ʵ��index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* �ж�voice call��ʵ��״̬ ,������� CNAS_XCC_L1_STA_ENDING״̬, ���账��*/
    if ((CNAS_XCC_FSM_L1_MAIN == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     && (CNAS_XCC_L1_STA_ENDING == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        return VOS_TRUE;
    }

    /*����״̬����XCALL�ظ�*/
    if (CAS_CNAS_1X_ECC_SERVICE_RESULT_SUCC != pstEccServiceCnf->enRslt)
    {
        enRslt = XCC_XCALL_ECC_SERVICE_RESULT_FAIL;
    }

    CNAS_XCC_SndXcallEccServiceCnf(enRslt);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessCas1xTchAssignCmplInd_MainCtrl
 ��������  : Ԥ����ID_CAS_CNAS_1X_TCH_ASSIGN_CMPL_IND
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --  ��Ϣ����Ҫ��һ������
             VOS_FALSE --  ��Ϣ��Ҫ������һ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessCas1xTchAssignCmplInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    /* ��ȡvoice call��ʵ��index */
    if (VOS_FALSE == CNAS_XCC_GetSpecTypeInstance(CNAS_XCC_SERVICE_TYPE_VOICE_CALL, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* �ж�voice call��ʵ��״̬ ,������� CNAS_XCC_L1_STA_ENDING״̬, ���账��*/
    if ((CNAS_XCC_FSM_L1_MAIN == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.enFsmId)
     && (CNAS_XCC_L1_STA_ENDING == pstXccCtxAddr->astFsmEntity[ucIndex].stCurFsm.ulState))
    {
        return VOS_TRUE;
    }

    /*����״̬����XCALL�ϱ�TCH ������Ϣ*/
    CNAS_XCC_SndXcallTchAssignCmplInd();
    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallPrivacyModeQryReq_MainCtrl
 ��������  : ��ѯ��ǰprivacy mode����

 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ������
             VOS_FALSE -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallPrivacyModeSetReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCALL_XCC_PRIVACY_MODE_SET_REQ_STRU                    *pstPrivacyModeSetReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg       = VOS_NULL_PTR;
    XCC_XCALL_RESULT_ENUM_UINT32                            enResult;

    enResult             = XCC_XCALL_RESULT_SUCC;

    pstPrivacyModeSetReq = (XCALL_XCC_PRIVACY_MODE_SET_REQ_STRU *)pstMsg;

    pstCallNvimCfg = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

    /* ���privacy mode���ͱ������ҪдNV */
    if (pstCallNvimCfg->ucPrivacyMode != (VOS_UINT8)pstPrivacyModeSetReq->enPrivacyMode)
    {
        if (VOS_FALSE == CNAS_XCC_WritePrivacyModeNvim((VOS_UINT8)pstPrivacyModeSetReq->enPrivacyMode))
        {
            /* ���дʧ�ܣ����ز���ʧ�ܣ������±��ص�ȫ�ֱ��� */
            enResult = XCC_XCALL_RESULT_FAIL;
        }
    }

    /* ���дNV�ɹ����Ե�ǰ��voice���н��д�������Ƿ���Ҫ����privacy mode */
    if (XCC_XCALL_RESULT_SUCC == enResult)
    {
        pstCallNvimCfg->ucPrivacyMode = (VOS_UINT8)pstPrivacyModeSetReq->enPrivacyMode;

        /* ����Ƿ���Ҫ֪ͨ����㣬�����ǰ�������е�privacy mode */
        if (VOS_TRUE == CNAS_XCC_IsPrivacyModeAllowedToSend_MainCtrl(pstPrivacyModeSetReq->enPrivacyMode))
        {
            /* ֪ͨCAS privacy mode������� */
            CNAS_XCC_SndCasLongCodeTransitionNtf(pstCallNvimCfg->ucPrivacyMode);
        }
    }

    CNAS_XCC_SndXcallPrivacyModeSetCnf(enResult,
                                       pstPrivacyModeSetReq->ulModuleId,
                                       pstPrivacyModeSetReq->usClientId,
                                       pstPrivacyModeSetReq->usOpId);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallPrivacyModeQryReq_MainCtrl
 ��������  : ��ѯ��ǰprivacy mode����

 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ������
             VOS_FALSE -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallPrivacyModeQryReq_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCALL_XCC_PRIVACY_MODE_QRY_REQ_STRU                    *pstPrivacyModeQryReq = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg       = VOS_NULL_PTR;

    pstPrivacyModeQryReq = (XCALL_XCC_PRIVACY_MODE_QRY_REQ_STRU *)pstMsg;

    pstCallNvimCfg      = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

    CNAS_XCC_SndXcallPrivacyModeQryCnf((XCALL_XCC_PRIVACY_MODE_ENUM_UINT8)pstCallNvimCfg->ucPrivacyMode,
                                       pstPrivacyModeQryReq->ulModuleId,
                                       pstPrivacyModeQryReq->usClientId,
                                       pstPrivacyModeQryReq->usOpId);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessXcallLongCodeTransitionInd_MainCtrl
 ��������  : �յ�CAS�ϱ���privacy modeָʾ

 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ������
             VOS_FALSE -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessXcallLongCodeTransitionInd_MainCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_LONG_CODE_TRANSITION_IND_STRU              *pstLongCodeTransInd = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx      = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg       = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;
    VOS_UINT8                                               ucIndex;

    pstLongCodeTransInd = (CAS_CNAS_1X_LONG_CODE_TRANSITION_IND_STRU *)pstMsg;

    /* ���CONNECT ID��Ч���򲻴������Ϣ */
    if (VOS_FALSE == CNAS_XCC_GetCallInstanceIndexByConnId(pstLongCodeTransInd->ucConnectId, &ucIndex))
    {
        return VOS_TRUE;
    }

    pstCallInfoCtx = &(CNAS_XCC_GetCtxAddr()->astFsmEntity[ucIndex].stCallInfoCtx);

    enServiceType = CNAS_XCC_SERVICE_TYPE_BUTT;
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* ��������������У����������Ϣ */
    if (CNAS_XCC_SERVICE_TYPE_VOICE_CALL != enServiceType)
    {
        return VOS_TRUE;
    }

    /* ���privacy mode�����˱��������º�����Ϣ��Э�̵�privacy mode��ͬʱ֪ͨXCALLģ�� */
    if (pstLongCodeTransInd->enUsePrivateLongCodeFlag != pstCallInfoCtx->enNegPrivacyMode)
    {
        pstCallNvimCfg                   = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

        /* ����Э�̺��privacy mode */
        pstCallInfoCtx->enNegPrivacyMode = pstLongCodeTransInd->enUsePrivateLongCodeFlag;

        CNAS_XCC_SndXcallPrivacyModeInd(pstCallNvimCfg->ucPrivacyMode,
                                        pstCallInfoCtx->enNegPrivacyMode,
                                        pstCallInfoCtx->ucCallId);
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


