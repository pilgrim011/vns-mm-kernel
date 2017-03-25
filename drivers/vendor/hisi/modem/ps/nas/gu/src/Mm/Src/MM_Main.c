/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MM_Main.c
  Description  : MM������
  Function List: Mm_Event_Analy
                 Mm_Timer_Event_Analy
                 Mm_Main

  History:
      1.  ��־��   2003.12.20 �°�����
      2.  s46746  2005.10.19  ��ӡȫ�����ݽṹ ���ⵥA32D00636
      3.  s46746  2006.02.28  �������ⵥA32D02234�޸�
      4.  s46746  2006.02.28  �������ⵥA32D02235�޸�

      5.��    ��   : 2006��4��19��
        ��    ��   : liuyang id:48197
        �޸�����   : ���ⵥ�ţ�A32D03208

      6. x51137 2006/5/5 A32D03487
      7. x51137 2006/5/30 A32D04051
      8. s46746 2006-07-25 �������ⵥA32D04901�޸�
      10.x51137 2006/11/3 A32D06821
      11.h44270 2007/01/26 A32D08575
      12.��    ��  : 2007��06��07��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D11534
      13.��    ��  : 2008��08��05��
         ��    ��  : ouyangfei id:00132663
         �޸�����  : ���ⵥ��:AT2D04738
      14.��    ��   : 2009��01��15��
         ��    ��   : l00130025
         �޸�����   : ���ⵥ��:AT2D07018,LAU��RAU������������SYSCFG����,����ײ��ͷ����ӵĲ���
      15.��    ��   : 2009��09��25��
         ��    ��   : x00115505
         �޸�����   : ���ⵥ��:AT2d14773,�ػ�ʱ��SDT�п�ά�ɲ⹦�ܲ�ѯIMSIΪ��
*******************************************************************************/
#include        "MM_Inc.h"
#include        "MmSuspend.h"
#include        "NasComm.h"
#include        "NasMmcSndOm.h"
#include        "NasMmcMain.h"
#if (FEATURE_ON == FEATURE_LTE)
#include        "MmLmmInterface.h"
#include        "NasMmProcLResult.h"
#endif
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
#include        "NasMmEcall.h"
#include        "NasMmPreProc.h"
/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-8, end */

#include        "NasMmSndOm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_MAIN_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


extern MM_TIMER_ST  gstMmTimerSuspend;

VOS_UINT32 WuepsMmcPidInit ( enum VOS_INIT_PHASE_DEFINE ip );
VOS_UINT32 WuepsGmmPidInit ( enum VOS_INIT_PHASE_DEFINE ip );

/*****************************************************************************
 �� �� ��  : NAS_MM_Event_Analy_From_GMM
 ��������  : ����GMM����Ϣ����
 �������  : pMsgHeader:����GMM����Ϣ
 �������  : ��
 �� �� ֵ  : �¼�ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��01��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32   NAS_MM_Event_Analy_From_GMM(MSG_HEADER_STRU* pMsgHeader)
{
    VOS_UINT8 ucEventID = MM_EVENT_ID_INVALID;

    switch ( pMsgHeader->ulMsgName )
    {
        case GMMMM_COMBINED_ATTACH_INITIATION:
            ucEventID   = 6;
            break;
        case GMMMM_COMBINED_ATTACH_ACCEPTED:
            ucEventID   = 7;
            break;
        case GMMMM_COMBINED_ATTACH_REJECTED:
            ucEventID   = 8;
            break;
        case GMMMM_IMSI_DETACH_INITIATION:
            ucEventID   = 9;
            break;
        case GMMMM_IMSI_DETACH_COMPLETED:
            ucEventID   = 10;
            break;
        case GMMMM_GPRS_DETACH_INITIATION:
            ucEventID   = 11;
            break;
        case GMMMM_GPRS_DETACH_COMPLETED:
            ucEventID   = 12;
            break;
        case GMMMM_NETWORK_DETACH_IND:
            ucEventID   = 13;
            break;
        case GMMMM_GMM_ACTION_RESULT_IND:
            ucEventID   = 14;
            break;
        case GMMMM_LU_INITIATION:
            ucEventID   = 15;
            break;
        case GMMMM_AUTHENTICATON_FAILURE_IND:
            ucEventID   = 16;
            break;
        case GMMMM_COMBINED_RAU_INITIATION:
            ucEventID   = 17;
            break;
        case GMMMM_COMBINED_RAU_ACCEPTED:
            ucEventID   = 18;
            break;
        case GMMMM_COMBINED_RAU_REJECTED:
            ucEventID   = 19;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_Event_Analy_From_GMM:WARNING: Msg name from GMM is Error");
            break;
    }

    return ucEventID;

}
#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MM_AnalyzeLmmEvent
 ��������  : ����LMM����Ϣ����
 �������  : pMsgHeader - ����LMM����Ϣͷ
 �������  : ��
 �� �� ֵ  : �¼�ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��11��28��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��2��14��
   ��    ��   : z00161729
   �޸�����   : V7R1C50 ֧��CSFB�����޸�
3. ��    ��   : 2012��9��22��
   ��    ��   : w00176964
   �޸�����   : Volte_phaseII ��Ŀ:����CS��ȫ�����Ļظ��Ĵ���
*****************************************************************************/
VOS_UINT8  NAS_MM_AnalyzeLmmEvent(MSG_HEADER_STRU *pMsgHeader)
{
    VOS_UINT8                           ucEventID = MM_EVENT_ID_INVALID;

    switch ( pMsgHeader->ulMsgName )
    {
        case ID_LMM_MM_COMBINED_START_NOTIFY_REQ:
            ucEventID = NAS_MM_RcvLmmCombinedStartNotifyReq(pMsgHeader);
            break;

        case ID_LMM_MM_CSFB_SERVICE_END_IND:
            ucEventID = NAS_MM_RcvLmmCsfbServiceEndInd(pMsgHeader);
            break;

        case ID_LMM_MM_CSFB_SERVICE_PAGING_IND:
            ucEventID = NAS_MM_RcvLmmCsPagingInd(pMsgHeader);
            break;

        /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-22, begin */
        case ID_LMM_MM_HO_SECU_INFO_CNF:
            ucEventID = NAS_MM_RcvLmmHoSecuInfoCnf((struct MsgCB*)pMsgHeader);
            break;
        /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-22, end */

         default:
             NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_AnalyzeLmmEvent:WARNING: Msg name from LMM is Error");
             break;

    }

    return ucEventID;
}

#endif

/***********************************************************************
 *  MODULE   : Mm_Event_Analy_From_MMC
 *  FUNCTION : Mm_Event_Analy���������Ӷ�: ����MMC����Ϣ����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2. ��    ��   : 2011��10��27��
        ��    ��   : s46746
        �޸�����   : V7R1 PhaseIII,֧��Lģ����ע��

     3. ��    ��   : 2011��11��30��
        ��    ��   : w00176964
        �޸�����   : V7R1 Phase IV����:���Ӷ�L��detach�ظ�����Ĵ���
     4. ��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����

     5. ��    ��   : 2013��4��1��
        ��    ��   : y00176023
        �޸�����   : DSDS GUNAS II��Ŀ:���Ӷ�CSFB������RAT�ı�Ĵ���

     6.��    ��   : 2014��5��21��
       ��    ��   : w00167002
       �޸�����   : DTS2014051602857:��SOR��ʱ�����CSע��ʧ�ܴﵽ4�Σ��������
                ������ʱ����ʱ����LIST�����������ǰ����ԭ�����磬����LAU,����
                ����MM����LAU;���LIST�Ѻ󣬷������������磬�����������������ע�ᡣ
     7. ��    ��   : 2014��04��1��
        ��    ��   : w00176964
        �޸�����   : V3R3C60_eCall��Ŀ:ϵͳ��Ϣ�����Ż�
************************************************************************/
VOS_UINT8   Mm_Event_Analy_From_MMC(MSG_HEADER_STRU* pMsgHeader)
{
    VOS_UINT8 ucEventID = MM_EVENT_ID_INVALID;

    switch ( pMsgHeader->ulMsgName )
    {
    case MMCMM_START_REQ:
        ucEventID   = 1;
        break;
    case MMCMM_ATTACH_REQ:
        ucEventID   = NAS_MM_RcvMmcAttachReq_PreProc((struct MsgCB*)pMsgHeader);
        break;
    case MMCMM_RAT_CHANGE_IND:
        ucEventID   = NAS_MM_RcvMmcRatChangeInd((struct MsgCB*)pMsgHeader);
        break;

#if   (FEATURE_ON == FEATURE_LTE)

    case MMCMM_LTE_SYS_INFO_IND:
        ucEventID   = NAS_MM_RcvLmmSysInfoInd((struct MsgCB*)pMsgHeader);
        break;

    case MMCMM_LMM_ATTACH_IND:
        ucEventID   = NAS_MM_RcvLmmAttachInd((struct MsgCB*)pMsgHeader);
        break;

    case MMCMM_LMM_TAU_RESULT_IND:
        ucEventID   = NAS_MM_RcvLmmTauInd((struct MsgCB*)pMsgHeader);
        break;

    case MMCMM_LMM_MT_DETACH_IND:
        ucEventID   = NAS_MM_RcvLmmMTDetachInd((struct MsgCB*)pMsgHeader);
        break;

    case MMCMM_LMM_SERVICE_RESULT_IND:
        ucEventID   = NAS_MM_RcvLmmServiceRsltInd((struct MsgCB*)pMsgHeader);
        break;

    case MMCMM_LMM_MO_DETACH_IND:
        ucEventID   = NAS_MM_RcvLmmMoDetachInd((struct MsgCB*)pMsgHeader);
        break;

    case MMCMM_LMM_LOCAL_DETACH_IND:
        ucEventID   = MM_EVENT_ID_INVALID;
        break;

    case MMCMM_LMM_TIMER_STATE_NOTIFY:
        ucEventID  = 89;
        break;

#endif

    case MMCMM_PLMN_SEARCH_INITIATED:
        ucEventID   = 3;
        break;

    /* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ�� */

    case MMCMM_SYS_INFO_IND:
    case MMCMM_GSM_SYS_INFO_IND:
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */
        ucEventID   = NAS_MM_RcvMmcMmSysInfoInd_PreProc(pMsgHeader);
        /* Modified by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-1, end */
        break;
    case MMCMM_MODE_CHANGE_REQ:
        ucEventID   = 20;
        break;
    case MMCMM_COVERAGE_LOST_IND:
        ucEventID   = NAS_MM_RcvMmcCoverageLostInd_PreProc(pMsgHeader);
        break;
    case MMCMM_DETACH_REQ:
        ucEventID   = NAS_MM_RcvMmcDetachReq_PreProc((struct MsgCB*)pMsgHeader);
        break;
    case MMCMM_POWER_OFF_REQ:
        ucEventID   = 23;
        break;
    case MMCMM_REL_REQ:
        ucEventID   = 49;
        break;
    case MMCMM_SUSPEND_IND:
        ucEventID   = 84;
        break;
    case MMCMM_RESUME_IND:
        ucEventID   = 85;
        break;
    case MMCMM_W_AC_INFO_CHANGE_IND:
        ucEventID   = 88;
        break;

#if (FEATURE_ON == FEATURE_IMS)
    case MMCMM_SRVCC_INFO_NOTIFY:
        NAS_MM_RcvMmcSrvccInfoNtf((struct MsgCB*)pMsgHeader);
        break;
#endif

    case MMCMM_LAU_REQ:
        NAS_MM_RcvMmcLauReq((struct MsgCB*)pMsgHeader);
        break;


    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Event_Analy_From_MMC:WARNING: Msg name from MMC is Error");
        break;
    }

    return ucEventID;
}

/***********************************************************************
 *  MODULE   : Mm_Event_Analy_From_CC
 *  FUNCTION : Mm_Event_Analy���������Ӷ�: ����CC����Ϣ����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2013��09��22��
       ��    ��   : w00176964
       �޸�����   : VoLTE_PhaseII ��Ŀ:����CCģ��֪ͨ�ĺ�����Ϣ����
     3.��    ��   : 2014��6��13��
       ��    ��   : w00242748
       �޸�����   : DSDS ������
 ************************************************************************/
VOS_UINT8   Mm_Event_Analy_From_CC(MSG_HEADER_STRU* pMsgHeader)
{
    VOS_UINT8 ucEventID = MM_EVENT_ID_INVALID;

    switch ( pMsgHeader->ulMsgName )
    {
    case MMCC_EST_REQ:
        ucEventID   = 24;
        break;
    case MMCC_REL_REQ:
        ucEventID   = 25;
        break;
    case MMCC_ABORT_REQ:
        ucEventID   = 26;
        break;
    case MMCC_DATA_REQ:
        ucEventID   = 27;
        break;
    case MMCC_REEST_REQ:
        ucEventID   = 28;
        break;
    case MMCC_UNIT_DATA_REQ:
        ucEventID   = 29;
        break;
    case MMCC_PROMPT_REJ:
        ucEventID   = 68;
        break;
    case MMCC_START_CC:
        ucEventID   = 87;
        break;

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-23, begin */
#if (FEATURE_ON == FEATURE_IMS)
    case MMCC_SRVCC_CALL_INFO_NOTIFY:
        NAS_MM_RcvCcSrvccCallInfoNtf((MMCC_SRVCC_CALL_INFO_NOTIFY_STRU*)pMsgHeader);
        break;
#endif
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-23, end */

#if (FEATURE_ON == FEATURE_DSDS)
    case MMCC_BEGIN_SESSION_NOTIFY:
        NAS_MM_RcvMmccBeginSessionNotify((MMCC_BEGIN_SESSION_NOTIFY_STRU*)pMsgHeader);
        break;

    case MMCC_END_SESSION_NOTIFY:
        NAS_MM_RcvMmccEndSessionNotify((MMCC_END_SESSION_NOTIFY_STRU*)pMsgHeader);
        break;
#endif

    case MMCC_CALL_STATUS_NTY:
        NAS_MM_RcvMmccCallStatusNty((MMCC_CALL_STATUS_NTF_STRU*)pMsgHeader);
        break;

    /* Added by n00355355 for �����ؽ�, 2015-9-17, begin */
    case MMCC_GET_CALL_INFO_CNF:
        NAS_MM_RcvMmccGetCallInfoCnf((MMCC_GET_CALL_INFO_CNF_STRU*)pMsgHeader);
        break;

    /* Added by n00355355 for �����ؽ�, 2015-9-17, end */

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Event_Analy_From_CC:WARNING: Msg name from CC is Error");
        break;
    }

    return ucEventID;
}

/* Added by f62575 for V9R1 STK����, 2013/07/11, begin */
/*****************************************************************************
 �� �� ��  : NAS_MM_SndSmsNackMsg
 ��������  : ת��GAS��RRMM_NACK_DATA_IND��SMSģ�飬��Ϣ���޸�ΪMMSMS_NACK_DATA_IND
 �������  : RRMM_NACK_DATA_IND_STRU *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��6��26��
   ��    ��   : f62575
   �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_VOID NAS_MM_SndSmsNackMsg(RRMM_NACK_DATA_IND_STRU *pstMsg)
{
    MMSMS_NACK_DATA_IND_STRU           *pstMmSmsNackMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstMmSmsNackMsg = (MMSMS_NACK_DATA_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MM,
                                                pstMsg->MsgHeader.ulLength);

    if (VOS_NULL_PTR == pstMmSmsNackMsg)
    {
        return;
    }

    pstMmSmsNackMsg->MsgHeader.ulMsgName        = MMSMS_NACK_DATA_IND;
    pstMmSmsNackMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_SMS;

    pstMmSmsNackMsg->stNackMsg.ulNasMsgSize = pstMsg->stNackMsg.ulNasMsgSize;
    PS_MEM_CPY(pstMmSmsNackMsg->stNackMsg.aucNasMsg,
               pstMsg->stNackMsg.aucNasMsg,
               pstMsg->stNackMsg.ulNasMsgSize);

    ulRet = PS_SEND_MSG(WUEPS_PID_MM,  pstMmSmsNackMsg);
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_SndSmsNackMsg: Send msg fails");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_RcvNackMsg
 ��������  : ���������ϱ���δ������Ϣ��Ŀǰ��֧��GAS�ϱ��Ķ���δ������Ϣ��͸����SMS����
 �������  : pstMsg GAS�ϱ��Ķ���δ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_VOID NAS_MM_RcvNackMsg(RRMM_NACK_DATA_IND_STRU *pstMsg)
{
    /* �ж�PD                                   */
    if (MM_IE_PD_SMS_MSG == (pstMsg->stNackMsg.aucNasMsg[0] & MM_IE_PD_MASK))
    {
        NAS_MM_SndSmsNackMsg(pstMsg);
    }

    return;
}

/* Added by f62575 for V9R1 STK����, 2013/07/11, end */

/***********************************************************************
 *  MODULE   : Mm_Event_Analy_From_GAS
 *  FUNCTION : Mm_Event_Analy���������Ӷ�: ����GAS����Ϣ����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2013��07��11��
       ��    ��   : f62575
       �޸�����   : V9R1 STK������Ŀ
 ************************************************************************/
VOS_UINT8   Mm_Event_Analy_From_GAS(MSG_HEADER_STRU* pMsgHeader)
{
    VOS_UINT8 ucEventID = MM_EVENT_ID_INVALID;

    switch ( pMsgHeader->ulMsgName )
    {
    case GRRMM_PAGING_IND: /* GAS �ĺ���ָʾ,������WASͳһ */
        ucEventID   = NAS_MM_RcvCspagingInd_PreProc((struct MsgCB*)pMsgHeader);
        break;
    case RRMM_EST_CNF:
        ucEventID   = 32;
        break;
    case GRRMM_EST_SAPI3_CNF: /* ���� SAPI3 �Ļ�Ӧ��Ϣ */
        ucEventID   = 83;
        break;
    case RRMM_REL_IND:
        ucEventID   = 33;
        break;
    case GAS_RR_SYNC_IND: /* GAS �ļ���ָʾ,������WASͳһ */
        ucEventID   = 34;
        break;
    case RRMM_DATA_IND:
        ucEventID   = Mm_ComMsgChkProc((RRMM_DATA_IND_FOR_PCLINT_STRU*)pMsgHeader);
        break;
    case RRMM_AC_INFO_CHANGE_IND:
        ucEventID   = 74;
        break;
    case GAS_RR_CHAN_IND:
        ucEventID   = 86;
        break;
    /* Added by f62575 for V9R1 STK����, 2013/07/11, begin */
    case RRMM_NACK_DATA_IND:
        NAS_MM_RcvNackMsg((RRMM_NACK_DATA_IND_STRU *)pMsgHeader);
        break;
    /* Added by f62575 for V9R1 STK����, 2013/07/11, end */

    /* Added by n00355355 for �����ؽ� , 2015-9-17, begin */
    case RRMM_TRANSACTION_INFO_ENQ:
        NAS_MM_RcvRrMmGetTransactionReq((RRMM_TRANSACTION_INFO_ENQ_STRU*)pMsgHeader);
        break;
    /* Added by n00355355 for �����ؽ�, 2015-9-17, end */

    default:
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Event_Analy_From_GAS:WARNING: Msg name from GAS is Error", (VOS_INT32) pMsgHeader->ulMsgName);
        break;
    }

    return ucEventID;
}

/***********************************************************************
 *  MODULE   : Mm_Event_Analy_From_RRCF
 *  FUNCTION : Mm_Event_Analy���������Ӷ�: ����RRCF����Ϣ����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_UINT8   Mm_Event_Analy_From_RRCF(MSG_HEADER_STRU* pMsgHeader)
{
    VOS_UINT8 ucEventID = MM_EVENT_ID_INVALID;

    switch ( pMsgHeader->ulMsgName )
    {
    case RRMM_PAGING_IND:
        ucEventID   = NAS_MM_RcvCspagingInd_PreProc((struct MsgCB*)pMsgHeader);
        break;
    case RRMM_EST_CNF:
        ucEventID   = 32;
        break;
    case RRMM_REL_IND:
        ucEventID   = 33;
        break;
    case RRMM_SECURITY_IND:
        ucEventID   = 34;
        break;
    case RRMM_SYNC_IND:
        ucEventID   = 35;
        break;
    case RRMM_DATA_IND:
        ucEventID   = Mm_ComMsgChkProc((RRMM_DATA_IND_FOR_PCLINT_STRU*)pMsgHeader);
        break;

    /* Added by n00355355 for �����ؽ� , 2015-9-17, begin */
    case RRMM_TRANSACTION_INFO_ENQ:
        NAS_MM_RcvRrMmGetTransactionReq((RRMM_TRANSACTION_INFO_ENQ_STRU*)pMsgHeader);
        break;
    /* Added by n00355355 for �����ؽ�, 2015-9-17, end */

    default:
        PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Event_Analy_From_RRCF:WARNING: Msg name from RRC is Error", (VOS_INT32)pMsgHeader->ulMsgName);
        break;
    }

    return ucEventID;
}

/***********************************************************************
 *  MODULE   : Mm_Event_Analy_From_USIM
 *  FUNCTION : Mm_Event_Analy���������Ӷ�: ����USIM����Ϣ����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.  hezhijune2015.02.06  USIMM���ӿڵ���
 ************************************************************************/
VOS_UINT8   Mm_Event_Analy_From_USIM(MSG_HEADER_STRU* pMsgHeader)
{
    VOS_UINT8 ucEventID = MM_EVENT_ID_INVALID;

    switch ( pMsgHeader->ulMsgName )
    {
    /* case AGENT_USIM_AUTHENTICATION_CNF: */
    case USIMM_AUTHENTICATION_CNF:
        ucEventID   = 48;
        break;
    case USIMM_UPDATEFILE_CNF:
        ucEventID   = MM_EVENT_ID_INVALID;
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Event_Analy_From_USIM:WARNING: Msg name from USIM is Error");
        break;
    }

    return ucEventID;
}

/***********************************************************************
 *  MODULE   : Mm_Event_Analy_From_SMS
 *  FUNCTION : Mm_Event_Analy���������Ӷ�: ����SMS����Ϣ����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2014��6��25��
       ��    ��   : z00161729
       �޸�����   : DSDS III����

 ************************************************************************/
VOS_UINT8   Mm_Event_Analy_From_SMS(MSG_HEADER_STRU* pMsgHeader)
{
    VOS_UINT8 ucEventID = MM_EVENT_ID_INVALID;

    switch ( pMsgHeader->ulMsgName )
    {
    case MMSMS_EST_REQ:
        ucEventID   = 62;
        break;
    case MMSMS_REL_REQ:
        ucEventID   = 63;
        break;
    case MMSMS_DATA_REQ:
        ucEventID   = 64;
        break;
    case MMSMS_ABORT_REQ:
        ucEventID   = 81;
        break;
#if (FEATURE_ON == FEATURE_DSDS)
    case MMSMS_BEGIN_SESSION_NOTIFY:
        NAS_MM_RcvMmsmsBeginSessionNotify((MMSMS_BEGIN_SESSION_NOTIFY_STRU*)pMsgHeader);
        break;

    case MMSMS_END_SESSION_NOTIFY:
        NAS_MM_RcvMmsmsEndSessionNotify((MMSMS_END_SESSION_NOTIFY_STRU*)pMsgHeader);
        break;
#endif

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Event_Analy_From_SMS:WARNING: Msg name from SMS is Error");
        break;
    }

    return ucEventID;
}

/***********************************************************************
 *  MODULE   : Mm_Event_Analy_From_SS
 *  FUNCTION : Mm_Event_Analy���������Ӷ�: ����SS����Ϣ����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
     2.��    ��   : 2014��6��25��
       ��    ��   : z00161729
       �޸�����   : DSDS III����

 ************************************************************************/
VOS_UINT8   Mm_Event_Analy_From_SS(MSG_HEADER_STRU* pMsgHeader)
{
    VOS_UINT8 ucEventID = MM_EVENT_ID_INVALID;

    switch ( pMsgHeader->ulMsgName )
    {
    case MMSS_EST_REQ:
        ucEventID   = 65;
        break;
    case MMSS_REL_REQ:
        ucEventID   = 66;
        break;
    case MMSS_DATA_REQ:
        ucEventID   = 67;
        break;
    case MMSS_ABORT_REQ:
        ucEventID   = 80;
        break;

#if (FEATURE_ON == FEATURE_DSDS)
    case MMSS_BEGIN_SESSION_NOTIFY:
        NAS_MM_RcvMmssBeginSessionNotify((MMSS_BEGIN_SESSION_NOTIFY_STRU*)pMsgHeader);
        break;

    case MMSS_END_SESSION_NOTIFY:
        NAS_MM_RcvMmssEndSessionNotify((MMSS_END_SESSION_NOTIFY_STRU*)pMsgHeader);
        break;
#endif

    case MMSS_SS_STATUS_NOTIFY:
        NAS_MM_RcvMmssStatusNty((MMSS_STATUS_NTY_STRU*)pMsgHeader);
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Event_Analy_From_SS:WARNING: Msg name from SS is Error");
        break;
    }

    return ucEventID;
}

/***********************************************************************
 *  MODULE   : Mm_Event_Analy_From_TC
 *  FUNCTION : Mm_Event_Analy���������Ӷ�: ����TC����Ϣ����
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_UINT8   Mm_Event_Analy_From_TC(MSG_HEADER_STRU* pMsgHeader)
{
    VOS_UINT8 ucEventID = MM_EVENT_ID_INVALID;

    switch ( pMsgHeader->ulMsgName )
    {
    case TCMM_TEST_REQ:
        ucEventID   = 71;
        break;
    case TCMM_DATA_REQ:
        ucEventID   = 72;
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Event_Analy_From_TC:WARNING: Msg name from TC is Error");
        break;
    }

    return ucEventID;
}


/*******************************************************************************
  Module:   Mm_Event_Analy
  Function: MM �¼�����
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_UINT8,�¼�ID
  History:
      1.  ��־��   2003.12.20 �°�����
      2�� s46746 2005-09-08 �޸�
      3. x51137 2006/5/5 A32D03487
      4. ��    ��   : 2009��01��15��
         ��    ��   : l00130025
         �޸�����   : ���ⵥ��:AT2D07018,LAU��RAU������������SYSCFG����,����ײ��ͷ����ӵĲ���
*******************************************************************************/
VOS_UINT8   Mm_Event_Analy(MSG_HEADER_STRU* pMsgHeader)
{
    VOS_UINT8 ucEventID = MM_EVENT_ID_INVALID;
    switch ( pMsgHeader->ulSenderPid )
    {
    case WUEPS_PID_MMC:
        ucEventID = Mm_Event_Analy_From_MMC(pMsgHeader);
        break;
    case WUEPS_PID_CC:
        ucEventID = Mm_Event_Analy_From_CC(pMsgHeader);
        break;
    case UEPS_PID_GAS: /* GAS ���͵���Ϣ */
        ucEventID = Mm_Event_Analy_From_GAS(pMsgHeader);
        break;
    case WUEPS_PID_WRR:
        ucEventID = Mm_Event_Analy_From_RRCF(pMsgHeader);
        break;
    case WUEPS_PID_USIM:
        ucEventID = Mm_Event_Analy_From_USIM(pMsgHeader);
        break;
    case WUEPS_PID_SMS:
        ucEventID = Mm_Event_Analy_From_SMS(pMsgHeader);
        break;
    case WUEPS_PID_SS:
        ucEventID = Mm_Event_Analy_From_SS(pMsgHeader);
        break;
    case WUEPS_PID_TC:
         ucEventID = Mm_Event_Analy_From_TC(pMsgHeader);
       break;

    case WUEPS_PID_GMM:
        ucEventID = (VOS_UINT8)NAS_MM_Event_Analy_From_GMM(pMsgHeader);
        break;

#if (FEATURE_ON == FEATURE_LTE)
    case PS_PID_MM:
        ucEventID = NAS_MM_AnalyzeLmmEvent(pMsgHeader);
        break;
#endif
    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Event_Analy:WARNING: SrcTskId is Error");
        break;
    }
    return ucEventID;
}

/*****************************************************************************
 Prototype      : MM_DelayLuGsmTimeout
 Description    : G���ӳٷ���LU��ʱ����ʱ�Ĵ���
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2009-03-12
    Author      : o00132663
    Modification: Created function
  2. ��    ��   : 2012��03��23��
     ��    ��   : L65478
     �޸�����   : ���ⵥ��:DTS2012032002585,����ģʽI������5��ATTACHʧ�ܺ�,MMû�з���LU
  3.��    ��   : 2015��6��29��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID MM_DelayLuGsmTimeout()
{
    NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_INFO,
            "MM_DelayLuGsmTimeout: INFO: Timer MM_TIMER_DELAY_LU_GSM expire!");

    Mm_TimerStop(MM_TIMER_DELAY_LU_GSM);

    if ((LOCATION_UPDATING_PENDING    == g_MmGlobalInfo.ucState)
     || (MM_IDLE_ATTEMPTING_TO_UPDATE == g_MmGlobalInfo.ucState)
     || (MM_IDLE_NO_CELL_AVAILABLE == g_MmGlobalInfo.ucState))
    {
        Mm_ComLuOnly();
    }

    return;
}

/*****************************************************************************
 Prototype      : MM_DelayCsServiceGsmTimeout
 Description    : G���ӳٷ���CSҵ��ʱ����ʱ�Ĵ���
 Input          :
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2009-08-8
    Author      : o00132663
    Modification: Created function
*****************************************************************************/
VOS_VOID MM_DelayCsServiceGsmTimeout()
{
    NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_INFO,
            "MM_DelayCsServiceGsmTimeout: INFO: Timer MM_TIMER_DELAY_CS_SERVICE_GSM expire!");

    Mm_TimerStop(MM_TIMER_DELAY_CS_SERVICE_GSM);

    if (MM_IDLE_NORMAL_SERVICE == g_MmGlobalInfo.ucState)
    {
        Mm_ComCheckDelayMmConn( MM_TRUE );
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_WaitConnectRelTimeOut
 ��������  : �ȴ����������ͷŵı�����ʱ����ʱ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
   ��    ��   : s46746
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 3.��    ��   :2014��9��24��
   ��    ��   :s00217060
   �޸�����   :for cs_err_log
*****************************************************************************/
VOS_VOID NAS_MM_WaitConnectRelTimeOut()
{
    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_MM_WaitConnectRelTimeOut:WARNING: Wait connect rel time out.");

    if (MM_IDLE_PLMN_SEARCH == g_MmGlobalInfo.ucState)
    {
        /* �����������Ӳ����� */
        NAS_MML_SetCsSigConnStatusFlg(VOS_FALSE);

        /* ֪ͨMMC���Ӳ����� */
        Mm_SndMmcRrConnInfInd(MMC_MM_RR_CONN_ABSENT);
        NAS_MM_SndGmmCsConnectInd(MMGMM_CS_CONNECT_NOT_EXIST);
        MM_SndMmcRrRelInd(RRC_REL_CAUSE_RR_NORM_EVENT);

        /* �ͷ�����MM����,���ڽ���MM���� */
        Mm_ComRelAllMmConn(NAS_MMCM_REL_CAUSE_RR_REL_NAS_REL_REQ);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_NormalCsfbHoWaitSysinfoTimeOut
 ��������  : CSFB HO�����еȴ�ϵͳ��Ϣ��ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��2��15��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��12��13��
   ��    ��   : s00217060
   �޸�����   : Service_State_Optimize_PhaseI �л������޸�
 3.��    ��   : 2015��5��4��
   ��    ��   : w00167002
   �޸�����   : ����csmt��ʱ�������У�����ҪЯ��csmt��־
 4.��    ��   : 2015��10��16��
   ��    ��   : j00174725
   �޸�����   : DTS2015101603066
*****************************************************************************/
VOS_VOID NAS_MM_NormalCsfbHoWaitSysinfoTimeOut(VOS_VOID)
{

#if (FEATURE_ON == FEATURE_LTE)

    if (NAS_MML_MT_CSFB_PAGING_TIMER_RUNNING == NAS_MML_GetCsfbMtPagingTimerStatus())
    {
        /* ����LAUЯ��CSMT��־ */
        NAS_MM_SetCsfbMtLauFlg(VOS_TRUE);
    }

    /* ����CSFB���̷���LAU���� */
    if ( VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        g_MmGlobalInfo.LuInfo.ucLuType = MM_IE_LUT_NORMAL_LU;
        Mm_ComLuOnly();
    }
#endif

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_MM_EmergencyCallCsfbWaitHoSysInfoTimeOut
 ��������  : ��������CSFB HO�����еȴ�ϵͳ��Ϣ��ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��3��27��
   ��    ��   : w00166186
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��7��25��
   ��    ��   : w00242748
   �޸�����   : DTS2013072200933:vodafone r8����csfb mt��w��cs ps�����ͷź�1.5s����ѡ��l��
                �������2s���һ������·�paging��Ϣ�����ڶ�Ѱ�����д�ͨ���ο����ʵ�֣�
                rau req�д�follow on��־,����ȷЭ������
 3.��    ��   : 2014��6��13��
   ��    ��   : w00242748
   �޸�����   : DSDS ������
*****************************************************************************/
VOS_VOID NAS_MM_EmergencyCallCsfbWaitHoSysInfoTimeOut(VOS_VOID)
{
    /* ���ڽ�����CSFB���̷���������� */
    if ( NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        /* ��ǰ���ڻ����CCҵ�񣬷���CCҵ�� */
        if ( MM_TRUE == g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg )
        {
            /* ��¼delay lau��ʶ�����н������յ�ϵͳ��Ϣ��Ҫ��lau */
            NAS_MML_SetDelayedCsfbLauFlg(VOS_TRUE);
            g_MmGlobalInfo.ucStaOfRcvXXEstReq = g_MmGlobalInfo.ucState; /* ��¼�յ���������ʱ��״̬                 */

            NAS_MM_EstMmConnection(MM_CONN_CTRL_CC);
        }
        else
        {
            /* �޻����CCҵ�񣬽����쳣���� */
            NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_EmergencyCallCsfbWaitHoSysInfoTimeOut:EmergencyCall BUFFER NOT EXIST ");

            NAS_MM_ProcCsfbServiceStatusChange(NAS_MML_GetCsfbServiceStatus(), NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);

            NAS_MML_SetCsfbServiceStatus(NAS_MML_CSFB_SERVICE_STATUS_NOT_EXIST);
        }
    }
    else
    {
        /* �޻����CCҵ�񣬽����쳣���� */
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_EmergencyCallCsfbWaitHoSysInfoTimeOut:EmergencyCall BUFFER NOT EXIST ");
    }

    return;
}
#endif


/*****************************************************************************
 �� �� ��  : NAS_MM_CsHoWaitSysinfoTimeOut
 ��������  : CS HO�����еȴ�ϵͳ��Ϣ��ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��01��04��
   ��    ��   : s00217060
   �޸�����   : Service_State_Optimize_PhaseI �л������޸�

 2.��    ��   : 2016��1��28��
   ��    ��   : w00167002
   �޸�����   : ��IMS�绰��SRVCC��G,û��ϵͳ��Ϣ�����·���TMSI����䣬���µ�ǰ��RAT
                ΪGSM;���ж�RATû�иı䣬û�и�MSCC�ϱ�ϵͳ��Ϣ�����½���һֱ��ʾΪ
                4G.
*****************************************************************************/
VOS_VOID NAS_MM_CsHoWaitSysinfoTimeOut(VOS_VOID)
{
    
    /* ԭ��ֵ��չ:֪ͨMMC NAS_MML_REG_FAIL_CAUSE_NO_SYSINFO_INTER_RAT_CHANGE_SUCC */
    NAS_MM_SndMmcCsRegResultInd(MM_MMC_LU_PROC_FALSE, MM_MMC_LU_RESULT_SUCCESS, NAS_MML_REG_FAIL_CAUSE_HO_WAIT_SYSINFO_TIMEOUT);
    

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_ModeICsPsPowerOffProtectTimeOut
 ��������  : MM�Ĺػ�������ʱ����ʱ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��29��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, �ػ�������ʱ����ʱ�������������·��Ϣ
  2.��    ��   : 2013��05��15��
    ��    ��   : s46746
    �޸�����   : SS FDN&Call Control��Ŀ������CSPSע��״̬

*****************************************************************************/
VOS_VOID NAS_MM_ModeICsPsPowerOffProtectTimeOut(VOS_VOID)
{
    Mm_ComSetMmState(MM_STATE_NULL);

    g_MmGlobalInfo.ucMmServiceState = MM_NO_SERVICE;

    Mm_ComNasInfoSav(MM_STATUS_DETACHED,
                     NAS_MML_GetSimCsSecurityCksn());

    Mm_SndMmcPowerOffCnf();

}


/*******************************************************************************
  Module:   Mm_Timer_Event_Analy
  Function: MM Timer�¼�����
  Input:    VOS_VOID
  Output:
  NOTE:
  Return:   VOS_UINT8,�¼�ID
  History:
      1.  ��־��   2003.12.20 �°�����
      2.  s46746 2005-09-23 �޸�
      3.  s46746 2006-07-25 �������ⵥA32D04901�޸�
      4. ��    ��   : 2011��7��11��
         ��    ��   : sunxibo 46746
         �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
      5. ��    ��   : 2012��2��15��
         ��    ��   : z00161729
         �޸�����   : V7R1C50 ֧��CSFB�����޸�
      6. ��    ��   : 2012��9��07��
         ��    ��   : l00171473
         �޸�����   : DTS2012081701006, ���MM�ػ�������ʱ��
      7.��    ��   : 2013��6��6��
        ��    ��   : w00167002
        �޸�����   : V9R1_SVLTE��Ŀ�޸�
      8. ��    ��   : 2013��06��28��
         ��    ��   : l00167671
         �޸�����   : DCM LOGGER��Ŀ��ʱ���¼��ϱ�
      9. ��    ��   : 2013��09��22��
         ��    ��   : w00176964
         �޸�����   : Volte_phaseII��Ŀ:����CS��ȫ�����Ļ�ȡ��ʱ�Ĵ���
     10. ��    ��   : 2015��5��5��
         ��    ��   : w00167002
         �޸�����   : csmt�޸�
*******************************************************************************/

VOS_UINT8 Mm_Timer_Event_Analy(VOS_UINT32 *aulRcvMsg)
{

    VOS_UINT8   ucEventId = MM_EVENT_ID_INVALID;
    VOS_UINT8   ucTimerId;

    PS_NAS_LOG1(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: TimerExpired: ", (VOS_UINT8)aulRcvMsg[1]);

    if (MM_TIMER_PROTECT_SUSPEND != aulRcvMsg[1])
    {
        ucTimerId = (VOS_UINT8)aulRcvMsg[1];

        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
        if (ucTimerId >= MM_TIMER_MAX)
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Timer_Event_Analy:WARNING: TIMER ID is illegal.");
            return ucEventId;
        }

        if (MM_TIMER_STOP == gstMmTimer[ucTimerId].ucTimerStatus)
        {
            PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Timer_Event_Analy:WARNING: The TIMER has been stopped.");
            if( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_MM, ucTimerId, &gstMmTimer[ucTimerId].hTimer))
            {                                                               /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Timer_Event_Analy:WARNING: TIMER STOP FAILURE!");
            }
            return ucEventId;
        }
        else
        {
            Mm_TimerStop( (VOS_UINT8)aulRcvMsg[1] );
        }
    }

    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
    NAS_TIMER_EventReport(aulRcvMsg[1], WUEPS_PID_MM, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);
    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, end */

    switch ( aulRcvMsg[1] )
    {
    case MM_TIMER_T3210:
        ucEventId = 51;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM T3210 TIME OUT");
        break;
    case MM_TIMER_T3211:
        ucEventId = 52;
        g_T3211Flag = 0;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM T3211 TIME OUT");
        break;
    case MM_TIMER_T3212:
        ucEventId = 53;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM T3212 TIME OUT");
        break;
    case MM_TIMER_T3213:
        ucEventId = 54;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM T3213 TIME OUT");
        break;
    case MM_TIMER_T3214:
        ucEventId = 55;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM T3214 TIME OUT");
        break;
    case MM_TIMER_T3216:
        ucEventId = 56;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM T3216 TIME OUT");
        break;
    case MM_TIMER_T3218:
        ucEventId = 57;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM T3218 TIME OUT");
        break;
    case MM_TIMER_T3220:
        ucEventId = 58;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM T3220 TIME OUT");
        break;
    case MM_TIMER_T3230:
        ucEventId = 59;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM T3230 TIME OUT");
        break;
    case MM_TIMER_T3240:
        ucEventId = 60;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM T3240 TIME OUT");
        break;
    case MM_TIMER_PROTECT_AGENT:
        ucEventId = 75;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM_TIMER_PROTECT_AGENT TIME OUT");
        break;
    case MM_TIMER_PROTECT_DETACH:
        ucEventId = 76;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM_TIMER_PROTECT_DETACH TIME OUT");
        break;
    case MM_TIMER_PROTECT_SIGNALLING:
        ucEventId = 77;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM_TIMER_PROTECT_SIGNALLING TIME OUT");
        break;
    case MM_TIMER_PROTECT_CC:
        ucEventId = 79;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM_TIMER_PROTECT_CC TIME OUT");
        break;
    case MM_TIMER_PROTECT_CCBS:
        ucEventId = 82;
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "Mm_Timer_Event_Analy:INFO: MM_TIMER_PROTECT_CCBS TIME OUT");
        break;
    case MM_TIMER_PROTECT_SUSPEND:
        /* ���ñ�����ʱ���ĳ�ʱ���� */
        MM_SuspendTimeout();
        ucEventId = MM_EVENT_ID_INVALID;
        break;
    case MM_TIMER_DELAY_LU_GSM:
        MM_DelayLuGsmTimeout();
        ucEventId = MM_EVENT_ID_INVALID;
        break;
    case MM_TIMER_DELAY_CS_SERVICE_GSM:
        MM_DelayCsServiceGsmTimeout();
        ucEventId = MM_EVENT_ID_INVALID;
        break;
    case MM_TIMER_WAIT_CONNECT_REL:
        NAS_MM_WaitConnectRelTimeOut();
        ucEventId = MM_EVENT_ID_INVALID;
        break;

    case MM_TIMER_NORMAL_CSFB_HO_WAIT_SYSINFO:
        NAS_MM_NormalCsfbHoWaitSysinfoTimeOut();
        ucEventId = MM_EVENT_ID_INVALID;
        break;

    case MM_TIMER_EMERGENCY_CSFB_HO_WAIT_SYSINFO:
#if (FEATURE_ON == FEATURE_LTE)
        NAS_MM_EmergencyCallCsfbWaitHoSysInfoTimeOut();
#endif
        ucEventId = MM_EVENT_ID_INVALID;
        break;

    case MM_TIMER_CS_HO_WAIT_SYSINFO:
        NAS_MM_CsHoWaitSysinfoTimeOut();
        ucEventId = MM_EVENT_ID_INVALID;
        break;

    case MM_TIMER_MODE_I_CS_PS_POWER_OFF_PROTECT:
        NAS_MM_ModeICsPsPowerOffProtectTimeOut();
        break;

    case MM_TIMER_PROTECT_CS_DETACH:
        NAS_MM_RcvMmTimerProtectCsDetachExpired();
        ucEventId = MM_EVENT_ID_INVALID;
        break;

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-22, begin */
    case MM_TIMER_WAIT_GET_HO_SECU_INFO_CNF:
#if (FEATURE_ON == FEATURE_LTE)
        NAS_MM_RcvMmTimerGetHoSecuInfoCnfExpired();
#endif
        break;
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-22, end */

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    case MM_TIMER_T3242:
        ucEventId = MM_EVENT_ID_T3242_EXPIRED;
        break;

    case MM_TIMER_T3243:
        ucEventId = MM_EVENT_ID_T3243_EXPIRED;
        break;
#endif
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

    case MM_TIMER_PROTECT_MT_CSFB_PAGING_PROCEDURE:
        NAS_MM_RcvProtectingMtCsfbPagingProcedureExpired();
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_Timer_Event_Analy:WARNING: TimerId is Error");
        break;
    }
    return ucEventId;
}

#ifdef __PS_WIN32_RECUR__


/*****************************************************************************
 �� �� ��  : NAS_MM_SetMmSigFunc
 ��������  : ���ݵ�ǰ������ģʽ������MM��MmImportFunc�ĺ���ָ��
 �������  : ��ǰ���������ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��1��
    ��    ��   : l00130025
    �޸�����   : �طŵ����������ָ�����

*****************************************************************************/
VOS_VOID  NAS_MM_SetMmSigFunc(NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enRat)
{
    if (NAS_MML_NET_RAT_TYPE_GSM == enRat)
    {

        /* ����������ĺ���ָ��ָ�� GSM �����µķ��ͺ��� */
        g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc          = MM_GasRrEstReq;
        g_NasMmImportFunc.SigConnCtrl.RrRelReqFunc          = MM_GasRrRelReq;

        /* ���������ݴ���ĺ���ָ��ָ�� GSM �����µķ��ͺ��� */
        g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc     = MM_GasRrDataReq;
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
    {
        g_NasMmImportFunc.SigConnCtrl.RrEstReqFunc          = MM_WasRrEstReq;
        g_NasMmImportFunc.SigConnCtrl.RrRelReqFunc          = As_RrRelReq;

        /* ���������ݴ���ĺ���ָ��ָ�� UMTS �����µķ��ͺ��� */
        g_NasMmImportFunc.SigDataTransfer.RrDataReqFunc     = MM_WasRrDataReq;
    }
    else
    {

    }

}


/*****************************************************************************
 �� �� ��  : NAS_MM_RestoreContextData
 ��������  : �ָ�MMȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��01��04��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��01��04��
    ��    ��   : z00161729
    �޸�����   : pc�ط�ѹ�������޸�
*****************************************************************************/
VOS_UINT32 NAS_MM_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                 *pstRcMsg;
    VOS_UINT32                                               ulExpectCount;
    VOS_UINT32                                               ulCount;
    VOS_UINT32                                               ulItemCount;
    VOS_UINT8                                               *pucDest;
    VOS_UINT8                                               *pucSrc;
    VOS_UINT32                                               ulDestLen;

    ulExpectCount = 0;
    ulCount       = 0;
    ulItemCount   = 0;

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
    ulExpectCount  = sizeof(VOS_UINT8)                     /* gucMmProcessFlg */
                   + sizeof(VOS_UINT8)                     /* g_T3211Flag*/
                   + sizeof(MM_NSD_INFO_ST)                /* g_stMmNsd*/
                   + sizeof(MM_GLOBAL_CTRL_STRU)           /* g_MmGlobalInfo*/
                   + sizeof(MM_TIMER_STRU) * MM_TIMER_MAX; /*gstMmTimer*/
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */

    pstRcMsg = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pMsg;
    pucSrc   = pstRcMsg->aucData;

    /* �����ܳ��� */
    PS_MEM_CPY(&ulCount, pucSrc, sizeof(VOS_UINT32));
    pucSrc += sizeof(VOS_UINT32);

    if( ulExpectCount != ulCount )
    {
        return VOS_FALSE;
    }

    /* gucMmProcessFlgĿ���ַ */
    pucDest     = (VOS_UINT8 *)&gucMmProcessFlg;
    ulDestLen   = sizeof(gucMmProcessFlg);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_T3211FlagĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_T3211Flag;
    ulDestLen   = sizeof(g_T3211Flag);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_stMmNsdĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_stMmNsd;
    ulDestLen   = sizeof(MM_NSD_INFO_ST);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_MmGlobalInfoĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_MmGlobalInfo;
    ulDestLen   = sizeof(MM_GLOBAL_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);


    /* gstMmTimerĿ���ַ */
    pucDest     = (VOS_UINT8 *)gstMmTimer;
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
    ulDestLen   = sizeof(MM_TIMER_STRU) * MM_TIMER_MAX;
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    NAS_MM_SetMmSigFunc(NAS_MML_GetCurrNetRatType());

    PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_MM_RestoreContextData - data is restored.");
    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_MM_SndOutsideContextData
 ��������  : ��MM�ⲿ��������ΪSDT��Ϣ���ͳ�ȥ���Ա��ڻط�ʱͨ��׮������ԭ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��01��03��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��30��
    ��    ��   : z00161729
    �޸�����   : ʵ��pc�ط�ѹ�������޸�
*****************************************************************************/
VOS_VOID NAS_MM_SndOutsideContextData()
{
    VOS_UINT8                                              *pucCompressBuf;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                *pstPcreplayCompressCtx;
    VOS_UINT32                                              ulCompressDataLen;
    VOS_UINT32                                              ulCount;
    VOS_UINT8                                              *pucEndBuf;
    VOS_UINT32                                              ulItemCount;
    VOS_UINT8                                              *pucDest;
    VOS_UINT8                                              *pucSrc;
    VOS_UINT32                                              ulCmLen;


    /*lint -e961*/
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
    ulCount     = sizeof(VOS_UINT8)                     /* gucMmProcessFlg */
                + sizeof(VOS_UINT8)                     /* g_T3211Flag*/
                + sizeof(MM_NSD_INFO_ST)                /* g_stMmNsd*/
                + sizeof(MM_GLOBAL_CTRL_STRU)           /* g_MmGlobalInfo*/
                + sizeof(MM_TIMER_STRU) * MM_TIMER_MAX; /*gstMmTimer*/
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
    /*lint +e961*/

    ulItemCount = 0;

    ulCompressDataLen  = NAS_MML_PC_RECUR_COMPRESS_DATA_LEN;
    pucCompressBuf     = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMC, ulCompressDataLen);

    if(VOS_NULL_PTR == pucCompressBuf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MM,"NAS_MM_SndOutsideContextData: Alloc Fail.");
        return;
    }

    pstPcreplayCompressCtx = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pucCompressBuf;

    /* ��ȡbuf��β��ַ�����ڼ���ʣ��ռ�*/
    pucEndBuf = pucCompressBuf + ulCompressDataLen;
    pucDest   = pstPcreplayCompressCtx->aucData;

    /* ԭʼ���ݴ�С */
    PS_MEM_CPY(pucDest, &ulCount, sizeof(VOS_UINT32));
    pucDest += sizeof(VOS_UINT32);

    /* ѹ��gucMmProcessFlg */
    pucSrc      = (VOS_UINT8 *)&gucMmProcessFlg;
    ulItemCount = sizeof(gucMmProcessFlg);

    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/

    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen , pucSrc , ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_T3211Flag */
    pucSrc      = (VOS_UINT8 *)&g_T3211Flag;
    ulItemCount = sizeof(g_T3211Flag);

    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/

    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_stMmNsd */
    pucSrc      = (VOS_UINT8 *)&g_stMmNsd;
    ulItemCount = sizeof(MM_NSD_INFO_ST);

    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/

    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_MmGlobalInfo */
    pucSrc      = (VOS_UINT8 *)&g_MmGlobalInfo;
    ulItemCount = sizeof(MM_GLOBAL_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��gstMmTimer */
    pucSrc      = (VOS_UINT8 *)gstMmTimer;
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
    ulItemCount = sizeof(MM_TIMER_STRU) * MM_TIMER_MAX;
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/

    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    ulCompressDataLen = (VOS_UINT32)(pucDest - (VOS_UINT8 *)pstPcreplayCompressCtx);

    pstPcreplayCompressCtx->ulReceiverPid      = WUEPS_PID_MM;
    pstPcreplayCompressCtx->ulSenderPid        = WUEPS_PID_MM;
    pstPcreplayCompressCtx->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulLength           = ulCompressDataLen;
    pstPcreplayCompressCtx->ulMsgName          = EVT_NAS_MM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;
    DIAG_TraceReport(pstPcreplayCompressCtx);

    PS_MEM_FREE(WUEPS_PID_MM, pucCompressBuf);
    return;
}

VOS_UINT8 gucMmProcessFlg = WAIT_FOR_MMCMM_START_REQ;    /* MM Task �������̵�flag */

/*******************************************************************************
  Module:   MmMsgProc
  Function: MM������ڣ�������Ϣ����
  Input:    struct MsgCB* pMsg
  Output:
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��      2005-1-25  �½�
      2�� s46746  2005-09-01 �޸�

      3.��    ��   : 2006��4��19��
        ��    ��   : liuyang id:48197
        �޸�����   : ���ⵥ�ţ�A32D03208

      4. x51137 2006/5/5 A32D03487
      5. x51137 2006/5/30 A32D04051
      6. h44270 2007/01/26 A32D08575
      7. ��    ��  : 2007��06��07��
         ��    ��  : luojian id:60022475
         �޸�����  : ���ⵥ��:A32D11534
                     Reject CM Service REQ at Power off State.

      8.��    ��   : 2012��05��21��
        ��    ��   :  z40661
        �޸�����   :  DTS2012052308001:��L��ѡ��G�󷴸�����LAU
      9.��    ��   : 2012��12��11��
        ��    ��   : l00167671
        �޸�����   : DTS2012121802573, TQE����
     10.��    ��  : 2013��03��13��
        ��    ��  : z00214637
        �޸�����  : BodySAR��Ŀ
     11.��    ��   : 2014��3��22��
        ��    ��   : z00234330
        �޸�����   : dts2014032202060���ӿ�ν�ɲ⣬mmû�յ�һ����Ϣ�������Ϣ

*******************************************************************************/
VOS_VOID MmMsgProc (struct MsgCB* pMsg)
{
    VOS_VOID                *pRcvMsg = VOS_NULL_PTR;                            /* ������Ϣʹ�õ�ͷ��ַ����                 */
    MSG_HEADER_STRU         *pMsgHeader;                                        /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT32               aulRcvTimerMsg[4];                                 /* ������Ϣʹ�õ���ʱ�ڴ涨��               */
    REL_TIMER_MSG           *pTimerMsg = VOS_NULL_PTR;
    VOS_UINT8                ucEventId = MM_EVENT_ID_INVALID;
    MM_MSG_MM_STATUS_STRU    Msg;

    if (VOS_NULL_PTR == pMsg)
    {
        MM_WARN_LOG( "\nMM:MmMsgProc:MM Msg is null!");

        return;
    }

    NAS_MM_LogMmStateInfo(g_MmGlobalInfo.ucState);

#ifdef __PS_WIN32_RECUR__
    if ((WUEPS_PID_MM == pMsg->ulSenderPid) && (WUEPS_PID_MM == pMsg->ulReceiverPid))
    {
        NAS_MM_RestoreContextData(pMsg);
    }
#endif

    if (g_NasMmImportFunc.ucFuncEnvironment != NAS_MML_GetCurrNetRatType() )
    {
        MM_SndMsgFuncChg();
    }


    /* �ȴ���Task������MM������Ϣ */
    switch (gucMmProcessFlg)
    {
    case WAIT_FOR_NORMAL_MSG:                                                   /* �ȴ�����������Ϣ:                        */
        pRcvMsg = (VOS_VOID *)pMsg;
        if (PC_PID_TOOL == pMsg->ulSenderPid)
        {
            ucEventId = 78;
        }
        else if (VOS_PID_TIMER == pMsg->ulSenderPid)
        {
            pTimerMsg = (REL_TIMER_MSG *)pMsg;
            aulRcvTimerMsg[1] = pTimerMsg->ulName;
            aulRcvTimerMsg[2] = pTimerMsg->ulPara;


            ucEventId = Mm_Timer_Event_Analy(aulRcvTimerMsg);
        }
        /* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */

        /* Deleted by wx270776 for OM�ں�, 2015-7-16, end */
        else if (WUEPS_PID_ADMIN == pMsg->ulSenderPid)
        {
            pMsgHeader = (MSG_HEADER_STRU *)pMsg;
            if (WUEPS_RESET_REQ == pMsgHeader->ulMsgName)
            {
                Mm_TimerStop(MM_TIMER_STOP_ALL);
                if (MM_TIMER_START == gstMmTimerSuspend.ucTimerStatus)
                {
                    if (VOS_OK !=
                        Mm_StopRelTimer(WUEPS_PID_MM, MM_TIMER_PROTECT_SUSPEND, &(gstMmTimerSuspend.stTimer)))
                    {
                        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "MmMsgProc:WARNING: Mm_StopRelTimer VOS_ERRNO_RELTM_STOP_TIMERINVALID.");
                    }
                    gstMmTimerSuspend.ucTimerStatus = MM_TIMER_STOPPED;
                }
                PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "MmMsgProc:WARNING: ADMIN Reset order.");
                gucMmProcessFlg = WAIT_FOR_WUEPS_START;                         /* �ȴ�ADMIN��������ԭ��                    */
                break;
            }
        }
        else
        {
            pMsgHeader = ( MSG_HEADER_STRU* )pMsg;                              /* �õ���Ϣͷ                               */
            ucEventId = Mm_Event_Analy(pMsgHeader);
        }

        PS_NAS_LOG2(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_INFO, "MmMsgProc:INFO: MM* Receive Msg,EventId,State:",ucEventId,g_MmGlobalInfo.ucState);

        if ( MM_EVENT_ID_STATUS_95 == ucEventId )
        {
            PS_MEM_SET(&g_MmMsgMmInfo, 0, sizeof(MM_MSG_MM_INFO_STRU));

            Msg.MmIeRjctCause.ucRejCause
                = NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG;
            Mm_ComMsgMmStatusSnd(&Msg);
            ucEventId = MM_EVENT_ID_INVALID;
        }
        if ( MM_EVENT_ID_STATUS_96 == ucEventId )
        {
            PS_MEM_SET(&g_MmMsgMmInfo, 0, sizeof(MM_MSG_MM_INFO_STRU));

            Msg.MmIeRjctCause.ucRejCause
                = NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF;
            Mm_ComMsgMmStatusSnd(&Msg);
            ucEventId = MM_EVENT_ID_INVALID;
        }

        g_MmSubLyrShare.MmShare.MmSuspendEvent = ucEventId;

        /*lint -e961*/
        if ( MM_EVENT_ID_INVALID != ucEventId )
        {
            gaMmStateTable[ucEventId - 1][g_MmGlobalInfo.ucState](pRcvMsg);
        }
        /*lint +e961*/

        /* �յ�GUģϵͳ��Ϣ����Ҫ����MM�б����net type */
        if ( 5 ==  ucEventId)
        {
            g_MmGlobalInfo.enPreRatType = NAS_MML_GetCurrNetRatType();
        }

        break;
    case WAIT_FOR_WUEPS_START:                                                  /* �ȴ�WUEPS_START_REQ��Ϣ                  */

        if (VOS_PID_TIMER == pMsg->ulSenderPid)
        {
        }
        else
        {
            pMsgHeader = ( MSG_HEADER_STRU* )pMsg;                              /* �õ���Ϣͷ                               */

            if (( WUEPS_START_REQ == pMsgHeader->ulMsgName) &&
                ( WUEPS_PID_ADMIN == pMsgHeader->ulSenderPid ))
            {                                                                   /* ��WUEPS_START_REQ��Ϣ */
                #ifdef __PS_WIN32_RECUR__
                Mm_ComInit();
                #endif

                gucMmProcessFlg = WAIT_FOR_MMCMM_START_REQ;                      /* ״̬Ǩ�Ƶ�"�ȴ�MMCMM_START_REQ��Ϣ"      */
            }
            else
            {                                                                   /* �޲���;                                  */
            }

        }

        break;
    case WAIT_FOR_MMCMM_START_REQ:                                              /* �ȴ�MMCMM_START_REQ��Ϣ:                 */

        if (VOS_PID_TIMER == pMsg->ulSenderPid)
        {
        }
        else
        {
            pRcvMsg = (VOS_VOID *)pMsg;                                             /* ��ȡ��Ϣ��ַ                             */
            pMsgHeader = ( MSG_HEADER_STRU* )pMsg;                              /* �õ���Ϣͷ                               */

            if (( MMCMM_START_REQ == pMsgHeader->ulMsgName) &&
                 ( WUEPS_PID_MMC == pMsgHeader->ulSenderPid ))
            {                                                                   /* ��MMCGMM_START_REQ��Ϣ */
                Mm_ComInit();
                ucEventId = Mm_Event_Analy(pMsgHeader);

                if ( MM_EVENT_ID_INVALID != ucEventId )
                {
                    /*lint -e961*/
                    gaMmStateTable[ucEventId - 1]
                                    [g_MmGlobalInfo.ucState](pRcvMsg);
                    /*lint +e961*/

                    gucMmProcessFlg = WAIT_FOR_NORMAL_MSG;                       /* ״̬Ǩ�Ƶ�"�ȴ�����������Ϣ"             */

                    #ifndef __PS_WIN32_RECUR__

                    if ( VOS_TRUE == NAS_MML_IsSndOmPcRecurMsgValid() )
                    {
                        NAS_MM_SndOutsideContextData();
                    }

                    #endif
                }

            }
            /*A32D11534==>*/
            else if ((( MMCC_EST_REQ == pMsgHeader->ulMsgName)
                && ( WUEPS_PID_CC == pMsgHeader->ulSenderPid ))
             ||  (( MMSS_EST_REQ == pMsgHeader->ulMsgName)
                && ( WUEPS_PID_SS == pMsgHeader->ulSenderPid ))
             ||  (( MMSMS_EST_REQ == pMsgHeader->ulMsgName)
                &&( WUEPS_PID_SMS == pMsgHeader->ulSenderPid )))
            {
                ucEventId = Mm_Event_Analy(pMsgHeader);
                if ( MM_EVENT_ID_INVALID != ucEventId )
                {
                    /*lint -e961*/
                    gaMmStateTable[ucEventId - 1][MM_STATE_NULL](pRcvMsg);
                    /*lint -e961*/
                }
            }
            /*<==A32D11534*/
            else
            {                                                                   /* �޲���;                                  */
            }

        }

        break;
     default:
        PS_NAS_LOG(WUEPS_PID_MM, VOS_NULL, PS_LOG_LEVEL_WARNING, "MmMsgProc:WARNING: gucMmProcessFlg is Abnormal");
         break;
    }
/*
#ifndef __PS_WIN32_RECUR__
    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif
*/
}

/* add by ��־��    for VOS 2005-1-25 end */

/******************************************************************************
 * �������� �� WuepsMmPidInit
 * �������� �� WUEPS MM PID�ĳ�ʼ������
 * ����˵�� �� ��
 * ��    ע ��
 * �� �� ֵ �� VOS_UINT32 ��ʼ�������
 *             0  : �ɹ�
 *             ��0: ʧ��
 *
 * �����ʷ ��
 *           No.  ����      ���                                    ��   ��
 *           1    ��־��    �½�                                   2005.02.24
 *****************************************************************************/
VOS_UINT32 WuepsMmPidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    /*VOS_UINT32 ulReturnCode = VOS_OK;   A32D00461,zzy,pclint
 */
    switch( ip )
    {
    case VOS_IP_LOAD_CONFIG:
    case VOS_IP_FARMALLOC:
    case VOS_IP_INITIAL:
    case VOS_IP_ENROLLMENT:
    case VOS_IP_LOAD_DATA:
    case VOS_IP_FETCH_DATA:
    case VOS_IP_STARTUP:
    case VOS_IP_RIVAL:
    case VOS_IP_KICKOFF:
    case VOS_IP_STANDBY:
    case VOS_IP_BROADCAST_STATE:
    case VOS_IP_RESTART:
    case VOS_IP_BUTT:
        break;
    default:
        break;
    }

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : Mm_GetState
 ��������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��5��7��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_GetState()
{
    return g_MmGlobalInfo.ucState;
}




/*****************************************************************************
 �� �� ��  : NAS_MM_FillNasMmState
 ��������  : ����MM״̬���OM��ѯ��ϢMM State��Substate��
 �������  : ��
 �������  : pMsg:������MM��ǰ״̬
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��3��4��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��6��16��
   ��    ��   : w00176964
   �޸�����   : DTS2014061006131:MM�����µ�Э��״̬
 3.��    ��   : 2015��7��25��
   ��    ��   : wx270776
   �޸�����   : OM�ں�
 4.��    ��   : 2015��9��17��
   ��    ��   : zwx247453
   �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ
*****************************************************************************/
VOS_VOID NAS_MM_FillNasMmState(
    /* Modified by wx270776 for OM�ں�, 2015-7-25, begin */
    NAS_OM_MM_IND_STRU                  *pMsg
    /* Modified by wx270776 for OM�ں�, 2015-7-25, end */
)
{
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    pMsg->enMmSubState = MM_SUB_STATE_BUTT;
    switch (g_MmGlobalInfo.ucState)
    {
    case MM_STATE_NULL:
        pMsg->enMmState = STATE_MM_NULL;
        break;
    case MM_IDLE_NO_CELL_AVAILABLE:
        pMsg->enMmState = STATE_MM_IDLE;
        pMsg->enMmSubState = NO_CELL_AVAILABLE;
        break;
    case MM_IDLE_PLMN_SEARCH:
        pMsg->enMmState = STATE_MM_IDLE;
        pMsg->enMmSubState = PLMN_SEARCH;
        break;
    case MM_IDLE_NORMAL_SERVICE:
        pMsg->enMmState = STATE_MM_IDLE;
        pMsg->enMmSubState = NORMAL_SERVICE;
        break;
    case MM_IDLE_LIMITED_SERVICE:
        pMsg->enMmState = STATE_MM_IDLE;
        pMsg->enMmSubState = LIMITED_SERVICE;
        break;
    case MM_IDLE_ATTEMPTING_TO_UPDATE:
        pMsg->enMmState = STATE_MM_IDLE;
        pMsg->enMmSubState = ATTEMPTING_TO_UPDATE;
        break;
    case MM_IDLE_LOCATION_UPDATE_NEEDED:
        pMsg->enMmState = STATE_MM_IDLE;
        pMsg->enMmSubState = LOCATION_UPDATE_NEEDED;
        break;
    case MM_IDLE_PLMN_SEARCH_NORMAL_SERVICE:
        pMsg->enMmState = STATE_MM_IDLE;
        pMsg->enMmSubState = PLMN_SEARCH_NORMAL_SERVICE;
        break;
    case MM_IDLE_NO_IMSI:
        pMsg->enMmState = STATE_MM_IDLE;
        pMsg->enMmSubState = NO_IMSI;
        break;
    case WAIT_FOR_OUTGOING_MM_CONNECTION:
        pMsg->enMmState = WAIT_FOR_OUTGOING_MM_CONNECT;
        break;
    case MM_CONNECTION_ACTIVE:
        pMsg->enMmState = MM_CONNECT_ACT;
        break;
    case WAIT_FOR_NETWORK_COMMAND:
        pMsg->enMmState = WAIT_FOR_NET_COMMAND;
        break;
    case WAIT_FOR_RR_CONNECTION_MM_CONNECTION:
        pMsg->enMmState = WAIT_FOR_RR_CONNECT_MM_CONNECT;
        break;
    case WAIT_FOR_REESTABLISH_WAIT_FOR_REEST_REQ:
        pMsg->enMmState = WAIT_FOR_REEST_WAIT_FOR_REEST_REQ;
        break;
    case WAIT_FOR_REESTABLISH_WAIT_FOR_EST_CNF:
        pMsg->enMmState = WAIT_FOR_REEST_WAIT_FOR_EST_CNF;
        break;
    case WAIT_FOR_RR_ACTIVE:
        pMsg->enMmState = WAIT_FOR_RR_ACT;
        break;
    case WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECTION:
        pMsg->enMmState = WAIT_FOR_ADDITIONAL_OUTGOING_MM_CONNECT;
        break;
    case LOCATION_UPDATING_PENDING:
        pMsg->enMmState = LOCATION_UPDATING_PEND;
        break;
    case IMSI_DETACH_PENDING:
        pMsg->enMmState = IMSI_DETACH_PEND;
        break;
    case MM_WAIT_FOR_ATTACH:
        pMsg->enMmState = MM_WAIT_FOR_ATTCH;
        break;
    case WAIT_FOR_RR_CONNECTION_LOCATION_UPDATING:
        pMsg->enMmState = WAIT_FOR_RR_CONNECT_LOCATION_UPDATING;
        break;
    case LOCATION_UPDATING_INITIATED:
        pMsg->enMmState = LU_INITIATED;
        break;
    case LOCATION_UPDATE_REJECTED:
        pMsg->enMmState = LU_REJECTED;
        break;
    case WAIT_FOR_RR_CONNECTION_IMSI_DETACH:
        pMsg->enMmState = WAIT_FOR_RR_CONNECT_IMSI_DETACH;
        break;
    case IMSI_DETACH_INITIATED:
        pMsg->enMmState = IMSI_DETACH_INITIATE;
        break;
    case PROCESS_CM_SERVICE_PROMPT:
        pMsg->enMmState = PROCESS_CM_SERV_PROMPT;
        break;
    case TEST_CONTROL_ACTIVE:
        pMsg->enMmState = TEST_CONTROL_ACT;
        break;
    case MM_INTER_RAT_CHANGE:
        pMsg->enMmState = MM_INTER_RAT_CHG;
        break;
    case MM_IDLE_ECALL_INACTIVE:
        pMsg->enMmState    = STATE_MM_IDLE;
        pMsg->enMmSubState = ECALL_INACTIVE;
        break;
    default:
        pMsg->enMmState = MM_STATE_BUTT;
        NAS_WARNING_LOG(WUEPS_PID_MM, "NAS_MM_FillNasMmState:WARNING: g_MmGlobalInfo.ucState Abnormal");
       break;
    }
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetMmRegStateForInterPLmnList
 ��������  : ��ȡMM��ע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��1��21��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetMmRegStateForInterPLmnList( VOS_VOID )
{
    if ( ( MM_IDLE_ATTEMPTING_TO_UPDATE  == g_MmGlobalInfo.ucState )
      && ( MM_TIMER_RUNNING == gstMmTimer[MM_TIMER_T3212].ucTimerStatus))
    {
        return VOS_OK;
    }

    if ( MM_IDLE_LOCATION_UPDATE_NEEDED == g_MmGlobalInfo.ucState )
    {
        return VOS_OK;
    }

    if ( MM_IDLE_LIMITED_SERVICE == g_MmGlobalInfo.ucState )
    {
        return VOS_OK;
    }

    if ( MM_IDLE_NO_IMSI == g_MmGlobalInfo.ucState )
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

