/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccFsmMain.c
  �� �� ��   : ����
  ��    ��   : y00213812
  ��������   : 2014��07��03��
  ��������   : XCC L1��״̬��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��07��03��
    ��    ��   : y00213812
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasXccFsmMain.h"
#include "CnasXccFsmMainTbl.h"
#include "CnasXccSndInternalMsg.h"
#include "CnasMntn.h"
#include "cas_1x_control_main_nas_pif.h"
#include "cas_1x_trchctrl_proc_nas_pif.h"
#include "CnasXccComFunc.h"
#include "CnasXccCtx.h"
#include "CnasXccSndAps.h"
#include "CnasXccSndCas.h"
#include "CnasXccSndXcall.h"
#include "CnasTimerMgmt.h"
#include "CnasXccSndCsms.h"
#include "CnasCcb.h"
#include "xcc_aps_pif.h"
#include "xcc_sms_pif.h"
#include "CnasXccSndXpds.h"
#include  "xcc_xpds_pif.h"
#include "Nas_Mem.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvOrigCallReq_L1Main
 ��������  : �յ�ID_XCALL_XCC_ORIG_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��10��22��
   ��    ��   : h00313353
   �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucIsEntityActive = VOS_TRUE;

    /* ����Session���� */
    CNAS_XCC_SndSessionBeginNtf((CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16)(((XCALL_XCC_ORIG_CALL_REQ_STRU *)pstMsg)->stSoInfo.enSo));

    /* ״̬Ǩ��MO CALLING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MO_CALLING);

    /* ����L2 MO CALLING״̬�� */
    CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MO_CALLING);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvOrigDataCallReq_L1Main_Idle
 ��������  : �յ�ID_APS_XCC_ORIG_DATA_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��22��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigDataCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucIsEntityActive = VOS_TRUE;

    /* ����Session���� */
    CNAS_XCC_SndSessionBeginNtf((CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16)(((APS_XCC_ORIG_DATA_CALL_REQ_STRU *)pstMsg)->enSo));

    /* ״̬Ǩ��MO CALLING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MO_CALLING);

    /* ����L2 MO CALLING״̬�� */
    CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MO_CALLING);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvOrigCsmsCallReq_L1Main_Idle
 ��������  : �յ�ID_CSMS_XCC_ORIG_SMS_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��22��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigCsmsCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucIsEntityActive = VOS_TRUE;

    /* ����Session���� */
    CNAS_XCC_SndSessionBeginNtf((CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16)(((CSMS_XCC_ORIG_SMS_CALL_REQ_STRU *)pstMsg)->enSo));

    /* ״̬Ǩ��MO CALLING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MO_CALLING);

    /* ����L2 MO CALLING״̬�� */
    CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MO_CALLING);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvOrigAgpsCallReq_L1Main_Idle
 ��������  : �յ�ID_XPDS_XCC_ORIG_AGPS_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��31��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��22��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvOrigAgpsCallReq_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucIsEntityActive = VOS_TRUE;

    /* ����Session���� */
    CNAS_XCC_SndSessionBeginNtf((CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16)(((XPDS_XCC_ORIG_AGPS_CALL_REQ_STRU *)pstMsg)->enSo));

    /* ״̬Ǩ��MO CALLING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MO_CALLING);

    /* ����L2 MO CALLING״̬�� */
    CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MO_CALLING);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvPagingInd_Idle
 ��������  : �յ�ID_XCALL_XCC_ORIG_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��22��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvPagingInd_L1Main_Idle(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo     = VOS_NULL_PTR;

    /* ����Session Begin��Ϣ */
    CNAS_XCC_SndSessionBeginNtf(((CAS_CNAS_1X_PAGING_IND_STRU *)pstMsg)->enSo);

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstCallInfo->ucIsEntityActive = VOS_TRUE;

    /* ״̬Ǩ��MT CALLING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

    /* ����L2 MT CALLING״̬�� */
    CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvMoCallingRsltCnf_L1Main_MoCalling
 ��������  : �յ�ID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��22��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS

  3.��    ��   : 2015��12��24��
    ��    ��   : y00245242
    �޸�����   : privacy mode���Կ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvMoCallingRsltCnf_L1Main_MoCalling(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU                  *pstMoCallingRsltCnf = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo         = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg      = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;

    pstCallInfo         = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstMoCallingRsltCnf = (CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU *)pstMsg;

    /*
     ״̬������ΪCNAS_XCC_MO_CALLING_RESULT_SUCCESSʱ��˵���绰��ͨ
     ״̬������ΪCNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDEDʱ��˵���绰�Ѿ�����
     ״̬������ΪCNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDINGʱ��˵���绰���ڹҶϵĹ�����
     */
    if ( CNAS_XCC_MO_CALLING_RESULT_SUCCESS == pstMoCallingRsltCnf->enRslt )
    {
        /* ״̬Ǩ�� */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_CONVERSATION);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_CONVERSATION,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

        /* ��SOת����SERVICE TYPE */
        CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

        /* privacy mode������Ϊvoice call�ҵ�ǰsoЭ���Ѿ���� */
        if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
         && (VOS_TRUE                         == pstCallInfo->ucIsSoNegCmplt))
        {
            pstCallNvimCfg = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

             /* �����ǰNV����ģʽ�����ں��������privacy mode����Ҫ֪ͨCAS privacy mode������� */
            if (((VOS_UINT8)pstCallInfo->enReqPrivacyMode) != pstCallNvimCfg->ucPrivacyMode)
            {
                pstCallInfo->enReqPrivacyMode = pstCallNvimCfg->ucPrivacyMode;

                /* ֪ͨCAS privacy mode������� */
                CNAS_XCC_SndCasLongCodeTransitionNtf(pstCallNvimCfg->ucPrivacyMode);
            }
        }
    }
    else if ( CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDED == pstMoCallingRsltCnf->enRslt )
    {
        pstCallInfo->ucIsEntityActive = VOS_FALSE;

        /* ȥ��Session���� */
        CNAS_XCC_SndSessionEndNtf(pstCallInfo->enInitSo);

        CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfo->ucConnectId);

        CNAS_XCC_InitCallInfoCtx(pstCallInfo, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

        /* ״̬Ǩ�� */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);
    }
    else if ( CNAS_XCC_MO_CALLING_RESULT_FAIL_CALL_ENDING == pstMoCallingRsltCnf->enRslt )
    {
        CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfo->ucConnectId);

        CNAS_XCC_InitCallInfoCtx(pstCallInfo, CNAS_XCC_INIT_CALLINFO_SCENE_ENDING);

        /* ״̬Ǩ�� */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

        if (CNAS_XCC_MO_CALLING_END_REASON_POWER_DOWN_END == pstMoCallingRsltCnf->enEndReason)
        {
            CNAS_XCC_StartTimer(pstCallInfo->ucConnectId,
                                TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                                TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING_LEN);
        }
    }
    else
    {
        /* enRslt is wrong */
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_RcvMoCallingRsltCnf_L1Main_MoCalling: Wrong Rslt",
                          pstMoCallingRsltCnf->enRslt);
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvMtCallingRsltCnf_L1Main_MtCalling
 ��������  : �յ�ID_CNAS_XCC_XCC_MT_CALLING_RSLT_CNF��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��22��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS

  3.��    ��   : 2015��12��24��
    ��    ��   : y00245242
    �޸�����   : privacy mode���Կ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvMtCallingRsltCnf_L1Main_MtCalling(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU                  *pstMtCallingRsltCnf = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo         = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                            *pstCallNvimCfg      = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;

    pstCallInfo         = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstMtCallingRsltCnf = (CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU *)pstMsg;

    if ( CNAS_XCC_MT_CALLING_RESULT_SUCCESS == pstMtCallingRsltCnf->enRslt )
    {
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_CONVERSATION);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_CONVERSATION,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

        /* ��SOת����SERVICE TYPE */
        CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

        /* privacy mode������Ϊvoice call�ҵ�ǰsoЭ���Ѿ���� */
        if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
         && (VOS_TRUE                         == pstCallInfo->ucIsSoNegCmplt))
        {
            pstCallNvimCfg = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

            /* �����ǰNV����ģʽ�����ں��������privacy mode����Ҫ֪ͨCAS privacy mode������� */
            if (((VOS_UINT8)pstCallInfo->enReqPrivacyMode) != pstCallNvimCfg->ucPrivacyMode)
            {
                pstCallInfo->enReqPrivacyMode = pstCallNvimCfg->ucPrivacyMode;

                /* ֪ͨCAS privacy mode������� */
                CNAS_XCC_SndCasLongCodeTransitionNtf(pstCallNvimCfg->ucPrivacyMode);
            }
        }
    }
    else if ( CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDED == pstMtCallingRsltCnf->enRslt )
    {
        pstCallInfo->ucIsEntityActive = VOS_FALSE;

        /* ȥ��Session���� */
        CNAS_XCC_SndSessionEndNtf(pstCallInfo->enInitSo);

        CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfo->ucConnectId);

        CNAS_XCC_InitCallInfoCtx(pstCallInfo, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();
    }
    else if ( CNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING == pstMtCallingRsltCnf->enRslt )
    {
        CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfo->ucConnectId);

        CNAS_XCC_InitCallInfoCtx(pstCallInfo, CNAS_XCC_INIT_CALLINFO_SCENE_ENDING);

        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

        if (CNAS_XCC_MT_CALLING_END_REASON_POWER_DOWN_END == pstMtCallingRsltCnf->enEndReason)
        {
            CNAS_XCC_StartTimer(pstCallInfo->ucConnectId,
                                TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                                TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING_LEN);
        }

        CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                                CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
        CNAS_XCC_SndXcc1xCallStateUpdateInd();

    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_RcvMtCallingRsltCnf_L1Main_MtCalling: Wrong Rslt",
                          pstMtCallingRsltCnf->enRslt);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallTerminateInd_L1Main_Conversation
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_TERMINATE_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��22��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU        *pstCallTerminateInd = VOS_NULL_PTR;

    pstCallTerminateInd = (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU *)pstMsg;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* Session���� */
    CNAS_XCC_SndSessionEndNtf(pstCallInfoCtx->enInitSo);

    CNAS_XCC_NotifyTafCallDisc_L1Main(pstCallInfoCtx,
                                      CNAS_XCC_ConvertTerminateReasonToTafCause(pstCallTerminateInd->enTerminateReason),
                                      VOS_TRUE);

    /* ���ñ���ó�VOS_FALSE��������ʵ���Ѳ����� */
    pstCallInfoCtx->ucIsEntityActive = VOS_FALSE;

    CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfoCtx->ucConnectId);

    CNAS_XCC_InitCallInfoCtx(pstCallInfoCtx, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

    /* ״̬Ǩ�Ƶ�IDLE */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallRelInd_L1Main_Conversation
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_REL_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallRelInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;
    TAF_XCC_CAUSE_ENUM_UINT32                   enCause;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* causeֵ����ΪTAF_XCC_CAUSE_NORMAL_RELEASE���������ӿ�������causeֵ��ʹ����Ϣ�е�ԭ��ֵ */
    enCause = TAF_XCC_CAUSE_MS_NORMAL_RELEASE;

    CNAS_XCC_NotifyTafCallDisc_L1Main(pstCallInfoCtx, enCause, VOS_FALSE);

    /* ״̬Ǩ�Ƶ�ENDING*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXcallHandupCallReq_L1Main_Conversation
 ��������  : �յ�ID_XCALL_XCC_HANGUP_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXcallHandupCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;
    XCALL_XCC_HANGUP_CALL_REQ_STRU             *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8           enRelReason;

    pstCallInfoCtx   = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XCALL_XCC_HANGUP_CALL_REQ_STRU *)pstMsg;

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* ��AS����REL REQ��ָʾ���н��� */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ֪ͨXCALL�������� */
    if ( VOS_TRUE == pstCallInfoCtx->ucIsCodecOpen )
    {
        CNAS_XCC_SndXcallCodecCloseInd();

        pstCallInfoCtx->ucIsCodecOpen = VOS_FALSE;
    }

    /* ��XCALLģ�鷢��ID_XCC_XCALL_HANGUP_CALL_CNF */
    CNAS_XCC_SndXcallHangUpCallCnf(pstCallInfoCtx->ucCallId);


    /* ״̬Ǩ�Ƶ�ENDING*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvApsHangupDataCallReq_L1Main_Conversation
 ��������  : �յ�ID_APS_XCC_HANGUP_DATA_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvApsHangupDataCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;
    APS_XCC_HANGUP_DATA_CALL_REQ_STRU          *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8           enRelReason;

    pstCallInfoCtx   = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (APS_XCC_HANGUP_DATA_CALL_REQ_STRU *)pstMsg;

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* ��AS����REL REQ��ָʾ���н��� */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��XCALLģ�鷢��ID_XCC_APS_HANGUP_DATA_CALL_CNF */
    CNAS_XCC_SndApsHangupDataCallCnf(pstCallInfoCtx->ucCallId);


    /* ״̬Ǩ�Ƶ�ENDING*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvCsmsEndSmsCallReq_L1Main_Conversation
 ��������  : �յ�ID_CSMS_XCC_END_SMS_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvCsmsEndSmsCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;
    CSMS_XCC_END_SMS_CALL_REQ_STRU             *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8           enRelReason;

    pstCallInfoCtx   = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)pstMsg;

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* ��AS����REL REQ��ָʾ���н��� */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��XCALLģ�鷢��ID_XCC_APS_HANGUP_DATA_CALL_CNF */
    CNAS_XCC_SndCsmsHangupCallCnf(pstCallInfoCtx->ucCallId);


    /* ״̬Ǩ�Ƶ�ENDING*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXpdsEndAgpsCallReq_L1Main_Conversation
 ��������  : �յ�ID_XPDS_XCC_END_AGPS_CALL_REQ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��01��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXpdsEndAgpsCallReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfo      = VOS_NULL_PTR;
    XPDS_XCC_END_AGPS_CALL_REQ_STRU            *pstHangupCallReq = VOS_NULL_PTR;
    CAS_CNAS_1X_REL_REASON_ENUM_UINT8           enRelReason;

    pstCallInfo      = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstHangupCallReq = (XPDS_XCC_END_AGPS_CALL_REQ_STRU *)pstMsg;

    CNAS_XCC_ConvertTafHangupReasonToCas(pstHangupCallReq->enEndReason, &enRelReason);

    /* ��AS����REL REQ��ָʾ���н��� */
    CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                              pstCallInfo->ucConRef,
                              enRelReason,
                              VOS_FALSE);

    /* ��XPDSģ�鷢��ID_XCC_XPDS_END_AGPS_CALL_CNF */
    CNAS_XCC_SndXpdsEndCallCnf(pstCallInfo->ucCallId);

    /* ״̬Ǩ�Ƶ�ENDING*/
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAWI_L1Main_Conversation
 ��������  : �յ�AWI��Ϣ�Ĵ���
 �������  : pstDschDataInd
 �������  : ��
 �� �� ֵ  : VOS_TRUE   -- ����ɹ�
             VOS_FALSE  -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2014��11��12��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_AWIM_STRU                 *pstAWIM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ���AWI�Ľ��� */
    pstAWIM = (CNAS_XCC_AWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_AWIM_STRU));
    if (VOS_NULL_PTR == pstAWIM)
    {
        return VOS_FALSE;
    }

    if (VOS_OK != CNAS_XCC_DecodeAlertWithInformationMsg(pstDschDataInd, pstAWIM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);
        return VOS_FALSE;
    }

    /* ���ҽ����Ľ�����Ƿ���signal���info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_SIGNAL,
                                                           pstAWIM->ucNumInfoRecs,
                                                           pstAWIM->astInfoRecsData,
                                                           &ucIndex);


    /* ���SIGNAL�����ڣ�״̬��ҪǨ�Ƶ�WAIT FOR ANSWER */
    if (VOS_TRUE != ulResult)
    {
        /* ״̬Ǩ��MT CALLING */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

        /* ����L2 MT CALLING״̬�� */
        CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);

        PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);

        return VOS_TRUE;
    }

    /* ��� SIGNAL TYPE Ϊ01 OR 10��״̬��ҪǨ�Ƶ�WAIT FOR ANSWER */
    if ( (CNAS_XCC_SIGNAL_TYPE_ISDN_ALERTING == pstAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stSignal.ucSignalType)
      || (CNAS_XCC_SIGNAL_TYPE_IS_54B_ALERTING == pstAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stSignal.ucSignalType))
    {
        /* ״̬Ǩ��MT CALLING */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

        /* ����L2 MT CALLING״̬�� */
        CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);

        PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);

        return VOS_TRUE;
    }

    /* ��Ϣͨ��rec ind�ϱ� */
    CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG,
                                (VOS_UINT8 *)pstAWIM);

    PS_MEM_FREE(UEPS_PID_XCC, pstAWIM);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvEAWI_L1Main_Conversation
 ��������  : �յ�EAWI��Ϣ�Ĵ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2014��11��12��
    ��    ��   : L00256032
    �޸�����   : 1X SS Project�޸�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvEAWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_EAWIM_STRU                *pstEAWIM = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ���EAWI�Ľ��� */
    pstEAWIM = (CNAS_XCC_EAWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EAWIM_STRU));
    if (VOS_NULL_PTR == pstEAWIM)
    {
        return VOS_FALSE;
    }

    if (VOS_OK != CNAS_XCC_DecodeExtendedAlertWithInformationMsg(pstDschDataInd, pstEAWIM))
    {
        PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);
        return VOS_FALSE;
    }

    /* ���ҽ����Ľ�����Ƿ���singal���info record */
    ulResult = CNAS_XCC_FindSpecInfoRecoTypeInInfoRecoList(CNAS_XCC_F_DSCH_INFO_RECORD_TYPE_SIGNAL,
                                                           pstEAWIM->ucNumInfoRecs,
                                                           pstEAWIM->astInfoRecsData,
                                                           &ucIndex);


    /* ���SIGNAL�����ڣ�״̬��ҪǨ�Ƶ�WAIT FOR ANSWER */
    if (VOS_TRUE != ulResult)
    {
        /* ״̬Ǩ��MT CALLING */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

        /* ����L2 MT CALLING״̬�� */
        CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);

        PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);

        return VOS_TRUE;
    }

    /* ��� SIGNAL TYPE Ϊ01 OR 10��״̬��ҪǨ�Ƶ�WAIT FOR ANSWER */
    if ( (CNAS_XCC_SIGNAL_TYPE_ISDN_ALERTING == pstEAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stSignal.ucSignalType)
      || (CNAS_XCC_SIGNAL_TYPE_IS_54B_ALERTING == pstEAWIM->astInfoRecsData[ucIndex].stInfoRecs.u.stSignal.ucSignalType))
    {
        /* ״̬Ǩ��MT CALLING */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

        /* ����L2 MT CALLING״̬�� */
        CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);

        PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);

        return VOS_TRUE;
    }

    /* ��Ϣͨ��rec ind�ϱ� */
    CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG,
                                (VOS_UINT8 *)pstEAWIM);

    PS_MEM_FREE(UEPS_PID_XCC, pstEAWIM);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsDschDataInd_L1Main_Conversation
 ��������  : �յ�ID_CAS_CNAS_1X_DSCH_DATA_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��11��10��
   ��    ��   : y00307564
   �޸�����   : 1X SS Project�޸�
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd = VOS_NULL_PTR;


    pstDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;

    /*
    If the Call Control instance receives a message from the layer 3Layer 3 which is
    included in the following list and every message field value is within its permissible
    range, the Call Control instance shall process the message as described below and
    in accordance with the message action time (see 2.6.4.1.5).
        1. Alert With Information Message: If the message contains a Signal information
        record with the SIGNAL_TYPE field set to '01' or '10', or if the message does not
        contain a Signal information record, the Call Control instance shall enter the
        Waiting For Mobile Station Answer Substate. The mobile station should alert the
        user in accordance with the Signal information record. If this message does not
        contain a Signal information record, the mobile station should use standard
        alert as defined in 3.7.5.5.
        2. Continuous DTMF Tone Order
        3. Extended Alert With Information Message: If the message contains a Signal
        information record with the SIGNAL_TYPE field set to '01' or '10' or if the
        message does not contain a Signal information record, the Call Control instance
        shall enter the Waiting For Mobile Station Answer Substate. The mobile station
        should alert the user in accordance with the Signal information record. If this
        message does not contain a Signal information record, the mobile station should
        use standard alert as defined in 3.7.5.5.
        4. Flash With Information Message
        5. Extended Flash With Information Message
        6. Maintenance Order: The Call Control instance shall enter the Waiting for Mobile
        Station Answer Substate.
        7. Send Burst DTMF Message:
    If the Call Control instance receives a message that is not included in the above list,
    cannot be processed, or requires a capability which is not supported, the Call
    Control instance shall discard the message and send a message rejected indicationto the layer 3Layer 3, with the reject reason indicated.
    */
    switch (pstDschDataInd->enDschMsgType)
    {
        case CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG:
            CNAS_XCC_RcvAWI_L1Main_Conversation(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG:
            CNAS_XCC_RcvEAWI_L1Main_Conversation(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG:
            CNAS_XCC_RcvFWI_L1Main_Conversation(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG:
            CNAS_XCC_RcvEFWI_L1Main_Conversation(pstDschDataInd);
            break;

        case CAS_CNAS_1X_RX_TCH_ORDER_MSG:
            CNAS_XCC_ProcOrderMsg_L1Main_Conversation(pstDschDataInd);
            break;

        default:
            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_RcvAsDschDataInd_L1Main_Conversation: Wrong order msg");
            break;

    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsUpdateCallInfoInd_L1Main_Conversation
 ��������  : �յ�ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

 2.��    ��   : 2015��12��24��
   ��    ��   : y00245242
   �޸�����   : privacy mode���Կ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsUpdateCallInfoInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx       = VOS_NULL_PTR;
    CAS_CNAS_1X_UPDATE_CALL_INFO_IND_STRU      *pstUpdateCallInfoInd = VOS_NULL_PTR;
    CNAS_XCC_CALL_NVIM_CFG_STRU                *pstCallNvimCfg       = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32           enServiceType;

    pstUpdateCallInfoInd = (CAS_CNAS_1X_UPDATE_CALL_INFO_IND_STRU *)pstMsg;
    pstCallInfoCtx       = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ����CALL��CON_REF��Ϣ */
    pstCallInfoCtx->ucConRef     = pstUpdateCallInfoInd->ucConRef;
    pstCallInfoCtx->ucIsNullCc   = pstUpdateCallInfoInd->enIsNullCcFlag;
    pstCallInfoCtx->enCurrentSo  = pstUpdateCallInfoInd->enSo;
    CNAS_XCC_UpdateSrIdUsed(pstUpdateCallInfoInd->enSo,
                            pstUpdateCallInfoInd->ucSrId,
                            pstUpdateCallInfoInd->ucConnectId);
    pstCallInfoCtx->ucSrId       = pstUpdateCallInfoInd->ucSrId;

    if ( VOS_TRUE == pstUpdateCallInfoInd->ucQosParaFlag )
    {
        pstCallInfoCtx->bitOpQosInfo       = VOS_TRUE;
        pstCallInfoCtx->ucQosInfoLen       = pstUpdateCallInfoInd->ucQosInfoLen;
        NAS_MEM_CPY_S(pstCallInfoCtx->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo), pstUpdateCallInfoInd->aucQosInfo, sizeof(pstCallInfoCtx->aucQosInfo));
    }

    /* ��SOת����SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    /* ���ݲ�ͬSO������ͬģ�鷢��SOЭ����� */
    if ( CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType )
    {
        /* ֪ͨXCALL����CALL��Ϣ */
        if (VOS_FALSE == pstCallInfoCtx->ucIsCodecOpen)
        {
            CNAS_XCC_SndXcallCodecOpenInd(pstCallInfoCtx);
            pstCallInfoCtx->ucIsCodecOpen = VOS_TRUE;
        }
        else
        {
            CNAS_XCC_SndXcallCodecChangedInd(pstCallInfoCtx);
        }

        pstCallNvimCfg = &(CNAS_XCC_GetCtxAddr()->stCallNvimCfg);

        /* �����ǰNV����ģʽ�����ں��������privacy mode����Ҫ֪ͨCAS privacy mode������� */
       if (((VOS_UINT8)pstCallInfoCtx->enReqPrivacyMode) != pstCallNvimCfg->ucPrivacyMode)
       {
           pstCallInfoCtx->enReqPrivacyMode = pstCallNvimCfg->ucPrivacyMode;

           /* ֪ͨCAS privacy mode������� */
           CNAS_XCC_SndCasLongCodeTransitionNtf(pstCallNvimCfg->ucPrivacyMode);
       }
    }

    if ( CNAS_XCC_SERVICE_TYPE_DATA_CALL == enServiceType )
    {
        /* ��ǰ��Ҫ����SR_ID��ά����������ɺ������������ƣ��Ѿ�֪ͨAPS����ҵ���������
             �£���������һ��ˢ�µ�֪ͨ */
        if (VOS_FALSE == pstCallInfoCtx->ucIsDataSrvConn)
        {
            CNAS_XCC_SndApsDataServiceConnectInd(pstCallInfoCtx);
            pstCallInfoCtx->ucIsDataSrvConn= VOS_TRUE;
        }
        else
        {
            CNAS_XCC_SndApsUpdateDataCallInfoInd(pstCallInfoCtx);
        }
    }

    if ( CNAS_XCC_SERVICE_TYPE_SMS == enServiceType )
    {
        CNAS_XCC_SndCsmsServiceConnectInd(pstCallInfoCtx);
    }

    if ( CNAS_XCC_SERVICE_TYPE_AGPS_CALL == enServiceType )
    {
        CNAS_XCC_SndXpdsServiceConnectInd(pstCallInfoCtx);
    }

    /* ��ǰ��Ϊ������ϱ�ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND��ʱ�򣬽�����Ѿ�SOЭ����ɣ����
        ��ʱSO��Э����ɱ���ó�VOS_TRUE����������������һ�� */
    pstCallInfoCtx->ucIsSoNegCmplt = VOS_TRUE;

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccPowerDownInd_L1Main_Conversation
 ��������  : �յ�ID_CNAS_XCC_XCC_POWER_DOWN_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��16��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /*
        ��ǰ�ػ���ʱ����·�ͷ�����main control���洦��ģ���˲���Ҫ�����㽻����ֻ��Ҫ״̬Ǩ�ƣ�
        ͬʱTAF��Ӧ��Ϣ�Ĵ���
     */

    /* ֪ͨTAFͨ������ */
    CNAS_XCC_NotifyTafCallDisc_L1Main(pstCallInfo, TAF_XCC_CAUSE_POWER_DOWN_IND, VOS_FALSE);

    /* ״̬Ǩ��ΪCNAS_XCC_MT_CALLING_RESULT_FAIL_CALL_ENDING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfo->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();


    /* �����ػ��ı�����ʱ�� */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId,
                        TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                        TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccAbortReq_L1Main_Conversation
 ��������  : ID_CNAS_XCC_XCC_ABORT_REQ������ʱ����ʱ
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��15��
    ��    ��   : y00245242
    �޸�����   : �޸�ԭ��ֵ�ϱ�

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccAbortReq_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfoCtx = VOS_NULL_PTR;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstAbortReq    = VOS_NULL_PTR;

    pstAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ����service type ��TAF����ҵ����ָֹʾ */
    CNAS_XCC_NotifyTafCallDisc_L1Main(pstCallInfoCtx, pstAbortReq->enAbortCause, VOS_FALSE);

    /* ֪ͨAS REL_REQ */
    CNAS_XCC_SndCasCallRelReq(pstCallInfoCtx->ucConnectId,
                              pstCallInfoCtx->ucConRef,
                              CAS_CNAS_1X_REL_REASON_NORMAL_RELEASE,
                              VOS_FALSE);

    /* ֱ�ӽ�״̬��Ǩ��CNAS_XCC_L1_STA_ENDING */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_ENDING);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvXccNdssRedialInd_L1Main_Conversation
 ��������  : ��ͨ�������У��յ�NDSS�ز�ָʾ����
 �������  : VOS_UINT32                          ulEventType,
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��5��
    ��    ��   : y00245242
    �޸�����   : �޸�ԭ��ֵ�ϱ�

  3.��    ��   : 2015��10��22��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccNdssRedialInd_L1Main_Conversation(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ȥ��Session���� */
    CNAS_XCC_SndSessionEndNtf(pstCallInfoCtx->enInitSo);

    /* ֪ͨXCALL�����ز�ָʾ, ������� */
    CNAS_XCC_NotifyTafCallDisc_L1Main(pstCallInfoCtx, TAF_XCC_CAUSE_NDSS_REDIAL_IND, VOS_TRUE);

    /* ���ñ���ó�VOS_FALSE��������ʵ���Ѳ����� */
    pstCallInfoCtx->ucIsEntityActive = VOS_FALSE;

    CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfoCtx->ucConnectId);

    CNAS_XCC_InitCallInfoCtx(pstCallInfoCtx, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

    /* ״̬Ǩ�Ƶ�IDLE */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsCallTerminateInd_L1Main_Ending
 ��������  : �յ�ID_CAS_CNAS_1X_CALL_TERMINATE_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��22��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsCallTerminateInd_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32           enServiceType;
    CNAS_XCC_CALL_INFO_CTX_STRU                *pstCallInfoCtx = VOS_NULL_PTR;

    pstCallInfoCtx = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ȥ��Session���� */
    CNAS_XCC_SndSessionEndNtf(pstCallInfoCtx->enInitSo);

    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_XCC,
                                                                  TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                                                                  pstCallInfoCtx->ucConnectId))
    {
        CNAS_XCC_StopTimer(pstCallInfoCtx->ucConnectId, TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING);
    }

    /* ������������еĻ�������Ҫ֪ͨAPS resume */
    enServiceType = CNAS_XCC_SERVICE_TYPE_BUTT;

    CNAS_XCC_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo, &enServiceType);

    if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType))
    {
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfoCtx->ucConnectId, enServiceType);
    }

    pstCallInfoCtx->ucIsEntityActive = VOS_FALSE;

    CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfoCtx->ucConnectId);

    CNAS_XCC_InitCallInfoCtx(pstCallInfoCtx, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE,
                            CNAS_CCB_ConvertSoToServiceType(pstCallInfoCtx->enCurrentSo));
    CNAS_XCC_SndXcc1xCallStateUpdateInd();

    /* ״̬Ǩ�Ƶ�IDLE */
    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvAsDschDataInd_L1Main_Ending
 ��������  : �յ�ID_CAS_CNAS_1X_DSCH_DATA_IND��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvAsDschDataInd_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd = VOS_NULL_PTR;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    CNAS_XCC_ORDRM_STRU                 stOrdrm;

    pstCallInfo         = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
    pstDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;

    /*
        2.6.10.3 Call Release Substate
    In this substate, the Call Control instance waits for the call to be released.
    While in the Call Release Substate, the Call Control instance shall perform the following:
    If the Call Control instance receives a message from the layer 3Layer 3 which is
    included in the following list and every message field value is within its permissible
    range, the Call Control instance shall process the message as described below and
    in accordance with the message action time (see 2.6.4.1.5).
         1. Alert With Information Message: The Call Control instance shall send an enter
         traffic channel substate indication?to the layer 3Layer 3 and shall enter the
         Waiting for Mobile Station Answer Substate. If this message does not contain a
         Signal information record, the mobile station should use standard alert as
         defined in 3.7.5.5.
         2. Extended Alert With Information Message: The Call Control instance shall send a
         enter traffic channel substate indication?to layer 3Layer 3 and shall enter the
         Waiting for Mobile Station Answer Substate. If this message does not contain a
         Signal information record, the mobile station should use standard alert as
         defined in 3.7.5.5.
    If the Call Control instance receives a message that is not included in the above list,
    cannot be processed, or requires a capability which is not supported, the Call
    Control instance shall discard the message and send a message rejected indicationto the layer 3Layer 3, with the reject reason indicated.
    */

    /* ��ǰ��Ϊ����׶β��ٴ���տ���Ϣ�������ʱ���пտ���Ϣ����ֱ�ӷ���REL REQ��CAS */
    if (CNAS_TIMER_STATUS_RUNNING == CNAS_GetSpecifiedTimerStatus(UEPS_PID_XCC,TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING, pstCallInfo->ucConnectId))
    {
        CNAS_XCC_SndCasCallRelReq(pstCallInfo->ucConnectId,
                                  pstCallInfo->ucConRef,
                                  CAS_CNAS_1X_REL_REASON_POWER_DOWN_RELEASE,
                                  VOS_FALSE);

        return VOS_TRUE;
    }

    if ( (CAS_CNAS_1X_RX_TCH_ALERT_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType)
      || (CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType) )
    {
        /* ���͸�AS enter traffic channel substate indication */
        CNAS_XCC_NotifyCasEnterTchSubstate();

        /* ״̬Ǩ��MT CALLING */
        CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

        /* ����L2 MT CALLING״̬�� */
        CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);
    }
    else if ((CAS_CNAS_1X_RX_TCH_FLASH_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType)
          || (CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG == pstDschDataInd->enDschMsgType)
          || (CAS_CNAS_1X_RX_TCH_ORDER_MSG == pstDschDataInd->enDschMsgType)
          || (CAS_CNAS_1X_RX_TCH_SEND_BURST_DTMF_MSG == pstDschDataInd->enDschMsgType))
    {
        NAS_MEM_SET_S(&aucPduData[0], sizeof(aucPduData), 0, sizeof(aucPduData));

        /* ����REJ ORDER */
        if (CAS_CNAS_1X_RX_TCH_ORDER_MSG == pstDschDataInd->enDschMsgType)
        {
            CNAS_XCC_DecodeOrderMsg(pstDschDataInd, &stOrdrm);
            stRejInfo.ucRejOrderCode    = stOrdrm.stOrder.ucOrder;
            stRejInfo.ucRejOrdq         = stOrdrm.stOrder.ucOrdq;
        }
        pstCallInfo                 = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
        stRejInfo.ucConRef          = pstCallInfo->ucConRef;
        stRejInfo.enRejRxTchMsgType = pstDschDataInd->enDschMsgType;
        stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
        stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_STATE;
        stRejInfo.ulL3PduBitLen     = 0;
        stRejInfo.pucPdudata        = aucPduData;
        CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

        /* ����ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)��AS */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                                0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, aucPduData);
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_RcvAsDschDataInd_L1Main_Ending: msgtype", pstDschDataInd->enDschMsgType);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiProtectPowerDown_L1Main_Ending
 ��������  : �յ�TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING��ʱ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��10��22��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvTiProtectPowerDown_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU                            *pstCallInfo   = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32                       enServiceType;

    pstCallInfo         = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* ȥ��Session���� */
    CNAS_XCC_SndSessionEndNtf(pstCallInfo->enInitSo);

    /* ������������еĻ�������Ҫ֪ͨAPS resume */
    enServiceType = CNAS_XCC_SERVICE_TYPE_BUTT;

    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    if ((CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_SMS        == enServiceType)
     || (CNAS_XCC_SERVICE_TYPE_AGPS_CALL  == enServiceType))
    {
        CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, enServiceType);
    }

    CNAS_XCC_ClearSpecificedSrIdByConnectId(pstCallInfo->ucConnectId);

    CNAS_XCC_InitCallInfoCtx(pstCallInfo, CNAS_XCC_INIT_CALLINFO_SCENE_ENDED);

    CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_IDLE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvTiProtectPowerDown_L1Main_Ending
 ��������  : �յ�TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING��ʱ��Ϣ�Ĵ���
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��9��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvXccPowerDownInd_L1Main_Ending(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo   = VOS_NULL_PTR;

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    /* �����ػ��ı�����ʱ�� */
    CNAS_XCC_StartTimer(pstCallInfo->ucConnectId,
                        TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                        TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_NotifyTafCallDisc_L1Main
 ��������  : ֪ͨTAF��ģ�飬���н���
 �������  : pstCallInfo -- ״̬���ĺ�����Ϣ
             enCause     -- ����ԭ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��15��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_NotifyTafCallDisc_L1Main(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_UINT32                          ulIsNeedToResumeAps
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    /* ��SOת����SERVICE TYPE */
    CNAS_XCC_ConvertSoToServiceType(pstCallInfo->enCurrentSo, &enServiceType);

    switch (enServiceType)
    {
        case CNAS_XCC_SERVICE_TYPE_VOICE_CALL:
            /* ֪ͨXCALL�������� */
            if (VOS_TRUE == pstCallInfo->ucIsCodecOpen)
            {
                CNAS_XCC_SndXcallCodecCloseInd();

                pstCallInfo->ucIsCodecOpen = VOS_FALSE;
            }

            /* ֪ͨXCALL���н��� */
            CNAS_XCC_SndXcallCallDiscInd(pstCallInfo->ucCallId,pstCallInfo->ucConnectId, enCause);

            if (VOS_TRUE == ulIsNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId,CNAS_XCC_SERVICE_TYPE_VOICE_CALL);
            }

            break;

        case CNAS_XCC_SERVICE_TYPE_DATA_CALL:
            /* ֪ͨAPS���н��� */
            CNAS_XCC_SndApsDataCallDiscInd(pstCallInfo, enCause);
            break;

        case CNAS_XCC_SERVICE_TYPE_SMS:
            /* ����ط�ò��ȱ��SMS�ӿڣ������ֱ��֪ͨSMS�绰���� */
            if (VOS_TRUE == ulIsNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId,CNAS_XCC_SERVICE_TYPE_SMS);
            }
            break;
        case CNAS_XCC_SERVICE_TYPE_AGPS_CALL:
            if (VOS_TRUE == ulIsNeedToResumeAps)
            {
                CNAS_XCC_SndApsDataCallResumeInd(pstCallInfo->ucConnectId, CNAS_XCC_SERVICE_TYPE_AGPS_CALL);
            }
            break;

        case CNAS_XCC_SERVICE_TYPE_LOOPBACK:
            if (VOS_TRUE == pstCallInfo->ucIsMoCall)
            {
                CNAS_XCC_SndXcallCallDiscInd(pstCallInfo->ucCallId,pstCallInfo->ucConnectId, enCause);
            }

            break;

        default:
            CNAS_XCC_SndXcallCallDiscInd(pstCallInfo->ucCallId,pstCallInfo->ucConnectId, enCause);

            CNAS_WARNING_LOG(UEPS_PID_XCC, "CNAS_XCC_NotifyTafCallDisc_L1Main: Wrong Service Type");
            break;
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcOrderMsg_L1Main_Conversation
 ��������  : ����տڵ�Order��Ϣ
 �������  : ulEventType -- �¼�����
             pstMsg      -- ��Ϣָ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��25��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcOrderMsg_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_ORDRM_STRU                 stOrdrm;
    VOS_UINT32                          ulRslt;
    CNAS_XCC_ORDER_TYPE_ENUM_UINT8      enOrderType;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;

    if (VOS_OK != CNAS_XCC_DecodeOrderMsg(pstDschDataInd, &stOrdrm))
    {
        CNAS_ERROR_LOG(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation: Decode FAIL ");
        return;
    }

    /* ��ȡ�����order��Ϣ���� */
    ulRslt = CNAS_XCC_GetOrderSpecificMsgType(&(stOrdrm.stOrder), &enOrderType);
    if (VOS_OK != ulRslt)
    {
        CNAS_ERROR_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation: CAS_1X_MAIN_GetOrderSpecificMsgType FAIL ", ulRslt);

        return ;
    }

    switch(enOrderType)
    {
        case CNAS_XCC_ORDER_TYPE_MAINTENANCE:
            /* Ǩ״̬��WAIT FOR ANSWER */
            /* ״̬Ǩ��MT CALLING */
            CNAS_XCC_SetCurrFsmState(CNAS_XCC_L1_STA_MT_CALLING);

            /* ����L2 MT CALLING״̬�� */
            CNAS_XCC_InitFsmL2(CNAS_XCC_FSM_MT_CALLING);
            break;

        case CNAS_XCC_ORDER_TYPE_SERVICE_OPTION_CONTROL:
            pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();
            CNAS_XCC_SndXcallSoCtrlOrderInd(pstCallInfo, (VOS_UINT8)stOrdrm.stOrder.ucOrdq);
            break;

        default:
            CNAS_ERROR_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcOrderMsg_L1Main_Conversation Wrong enOrderType", enOrderType);
            break;
    }

    return;

}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvFWI_L1Main_Conversation
 ��������  : �յ�FWI��Ϣ�Ĵ���
 �������  : CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��12��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvFWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_FWIM_STRU                 *pstFWIM  = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstFWIM = (CNAS_XCC_FWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_FWIM_STRU));
    if (VOS_NULL_PTR == pstFWIM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "ALLOC FWIM Wrong");

        return VOS_FALSE;
    }
    NAS_MEM_SET_S(pstFWIM, sizeof(CNAS_XCC_FWIM_STRU), 0, sizeof(CNAS_XCC_FWIM_STRU));

    if ((VOS_OK == CNAS_XCC_DecodeFlashWithInformationMsg(pstDschDataInd, pstFWIM))
      && (1 <= pstFWIM->ucNumInfoRecs))
    {
         /* ��XCALL����ID_XCC_XCALL_INFO_REC_IND */
         CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                     pstDschDataInd->enDschMsgType,
                                    (VOS_UINT8 *)pstFWIM);
    }
    else
    {
        NAS_MEM_SET_S(&stRejInfo, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU), 0x0, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU));

        /* ����REJ ORDER */
        stRejInfo.ucConRef          = pstCallInfo->ucConRef;
        stRejInfo.enRejRxTchMsgType = pstDschDataInd->enDschMsgType;
        stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
        stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_STRUCT;
        stRejInfo.ulL3PduBitLen     = 0;
        stRejInfo.pucPdudata        = aucPduData;
        CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

        /* ����ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)��AS */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                   0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, aucPduData);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstFWIM);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_RcvEFWI_L1Main_Conversation
 ��������  : �յ�EFWI��Ϣ�Ĵ���
 �������  : CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��12��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RcvEFWI_L1Main_Conversation(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd
)
{
    CNAS_XCC_EFWIM_STRU                *pstEFWIM  = VOS_NULL_PTR;
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo = VOS_NULL_PTR;
    CNAS_XCC_REJ_ORDER_INFO_STRU        stRejInfo;
    VOS_UINT8                           aucPduData[CNAS_XCC_MAX_DATA_SDU_OCTET_NUM];

    pstCallInfo = CNAS_XCC_GetCurrFsmEntityCallInfoCtx();

    pstEFWIM = (CNAS_XCC_EFWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EFWIM_STRU));
    if (VOS_NULL_PTR == pstEFWIM)
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC, "ALLOC EFWIM Wrong");

        return VOS_FALSE;
    }
    NAS_MEM_SET_S(pstEFWIM, sizeof(CNAS_XCC_EFWIM_STRU), 0, sizeof(CNAS_XCC_EFWIM_STRU));

    if ((VOS_OK == CNAS_XCC_DecodeExtendedFlashWithInformationMsg(pstDschDataInd, pstEFWIM))
       && (pstEFWIM->ucRecNum == pstEFWIM->ucNumInfoRecs))
    {
        /* ��XCALL����ID_XCC_XCALL_INFO_REC_IND */
        CNAS_XCC_SndXcallInfoRecInd(pstCallInfo->ucCallId,
                                    pstDschDataInd->enDschMsgType,
                                    (VOS_UINT8 *)pstEFWIM);
    }
    else
    {
        NAS_MEM_SET_S(&stRejInfo, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU), 0x0, sizeof(CNAS_XCC_REJ_ORDER_INFO_STRU));

        /* ����REJ ORDER */
        stRejInfo.ucConRef          = pstCallInfo->ucConRef;
        stRejInfo.enRejRxTchMsgType = pstDschDataInd->enDschMsgType;
        stRejInfo.enRevOrderCode    = CNAS_XCC_REV_ORDER_CODE_MS_REJECT;
        stRejInfo.enRevOrdq         = CNAS_XCC_REV_ORDER_MS_REJECT_STRUCT;
        stRejInfo.ulL3PduBitLen     = 0;
        stRejInfo.pucPdudata        = aucPduData;
        CNAS_XCC_EncodeTxTchMSRejectOrderMsg(&stRejInfo);

        /* ����ID_CNAS_CAS_1X_DSCH_DATA_REQ(REJ ORDER)��AS */
        CNAS_XCC_SndCasDschDataReq(CAS_CNAS_1X_TX_TCH_ORDER_MSG, CNAS_XCC_TX_ORDER_TYPE_MS_REJECT_ORDER,
                                   0, (VOS_UINT16)stRejInfo.ulL3PduBitLen, aucPduData);
    }

    PS_MEM_FREE(UEPS_PID_XCC, pstEFWIM);

    return VOS_TRUE;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





