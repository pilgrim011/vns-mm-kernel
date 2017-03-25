/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmService.c
  Description   : GMM SERVICE REQUEST������ش�����Դ�ļ�
  Function List :
    01.   Gmm_RcvRabmReestablishReq
    02.   Gmm_RcvRrmmSecurityInd
    03.   Gmm_RcvRrmmSecurityInd_RegInit
    04.   Gmm_RcvRrmmSecurityInd_ServReqInit
    05.   Gmm_RcvServiceAcceptMsg
    06.   Gmm_RcvServiceRejectMsg
    07.   Gmm_RcvSmsEstReq
    08.   Gmm_RcvSmsUnitdataReq
    09.   Gmm_ServiceReqRejectCasue10
    10.   Gmm_ServiceReqRejectCasue11
    11.   Gmm_ServiceReqRejectCasue12
    12.   Gmm_ServiceReqRejectCasue13
    13.   Gmm_ServiceReqRejectCasue3
    14.   Gmm_ServiceReqRejectCasue40
    15.   Gmm_ServiceReqRejectCasue7
    16.   Gmm_ServiceReqRejectCasue9
    17.   Gmm_ServiceReqRejectTheOtherCause
    18.   Gmm_ServiceRequestMsgMake
    19.   Gmm_ServiceRequestMsgMake_ForData
  History       :
    1.  ��־��  2003.12.05  �¹�����
    2.  s46746  2006.05.08  �������ⵥA32D03487�޸�
    3.��    ��   : 2006��12��5��
      ��    ��   : luojian 60022475
      �޸�����   : Maps3000�ӿ��޸�
    4.��    ��   : 2007��07��10��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D12268
    5.��    ��   : 2007��10��10��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D12948
    6.��    ��   : 2007��12��15��
      ��    ��   : l00107747
      �޸�����   : ���ⵥ��:A32D13897,Gmm_RcvRabmReestablishReq
                   ������GMM����״̬�Ĵ���
    7.��    ��   : 2008��3��17��
      ��    ��   : s46746
      �޸�����   : ���ⵥ��:AT2D02570,NAS B005�汾�����������
    8.��    ��   : 2008��7��24��
      ��    ��   : luojian 00107747
      �޸�����   : �������ⵥ�ţ�AT2D04627/AT2D04237,
                     ATTEMPT TO UPDATE/ATTACH ״̬��CM������
    9. ��    ��   : 2008��9��18��
       ��    ��   : ouyangfei 00132663
       �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬��GMM���̽����ٷ���
    10.��    ��   : 2008��9��23��
       ��    ��   : o00132663
       �޸�����   : �������ⵥ�ţ�AT2D05839,�������ȫ�ֱ��� ucRlsMsgFlg��״̬GMM_REGISTERED_WAIT_FOR_RAU
    11.��    ��   : 2008��9��26��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D05431
    12.��    ��   : 2009��07��31��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D13413,С����ѡʱ��Ӧ�÷�����ؽ�����ֱ�ӱ�GMM�ܾ���
    13.��    ��   : 2009��8��3��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�AT2D13469������GCF����12.9.7c��PDP����ʱService Req���ܣ�
                    �ϲ�û��������ֹ�ù��̣�֮��פ����������С�����ٴη�����PDP����������Ϣ����������ʧ��
*******************************************************************************/
#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasGsm.h"
#include "GmmCasMain.h"

#include "NasUsimmApi.h"
#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_SERVICE_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvRabmReestablishReq_AttemptToUpdate
 ��������  : ��register attempting to update״̬�յ�GMMRABM_REESTABLISH_REQԭ���Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2015��1��14��
   ��    ��   : z00161729
   �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID NAS_GMM_RcvRabmReestablishReq_AttemptToUpdate(
    GMMRABM_REESTABLISH_REQ_STRU       *pstMsg
)
{
    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        /*
        3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
        reset when the MS is in substate ATTEMPTING-TO-UPDATE and
            - a new routing area is entered;
            - expiry of timer T3302; or
            - at request from registration function.
        */

        /* ֹͣTimer3302 */
        Gmm_TimerStop(GMM_TIMER_T3302);

        /* ֹͣTimer3311*/
        Gmm_TimerStop(GMM_TIMER_T3311);

        /*����RAU����*/
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else
    {
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvRabmRabSetupInd
 ��������  : gmm�յ�rabm��rab set up ind��Ϣ�Ĵ���
 �������  : pstRabSetupIndMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��14��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_RcvRabmRabSetupInd(
    GMMRABM_RAB_SETUP_IND_STRU         *pstRabSetupIndMsg
)
{
    VOS_UINT32                          ulT3340TimerStatus;

    ulT3340TimerStatus = NAS_GMM_QryTimerStatus(GMM_TIMER_T3340);

    /* 2G����ģʽ������ */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        return;
    }

    /* ���t3340��ʱ�������У���ֹͣt3340 */
    if (VOS_TRUE == ulT3340TimerStatus)
    {
        Gmm_TimerStop(GMM_TIMER_T3340);

        if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
        {
            Gmm_DealWithBuffAfterProc();
        }
    }

    return;
}


/*******************************************************************************
  Module   : Gmm_RcvRabmReestablishReq
  Function : �յ�GMMRABM_REESTABLISH_REQԭ���Ĵ���
  Input    : VOS_VOID *pMsg     ԭ���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.��־��  2003.12.10  �°�����

    2.��    ��   : 2010��7��17��
      ��    ��   : ŷ����
      �޸�����   : DTS2010071601574, ���������ʹ�ָ��GMMRABM_REESTABLISH_REQ_-
                   STRU��ָ���ΪusUplinkDataStatus��
    3.��    ��   : 2011��3��2��
      ��    ��   : z00161729
      �޸�����   : DTS2010071601574:RAU��������յ�rau accept��Ҫ�ȴ�RABM��WRR�ظ����ٷ���RAU cmp��Ϣ�ڼ�,
                   ����rabm�ؽ�����.
    3.��    ��   : 2011��3��8��
      ��    ��   : c00173809
      �޸�����   : DTS2011030704202:���û��б��ѹ�����,�������RABM�ؽ�����,���ȴ���RABM����.
    4.��    ��   : 2012��2��15��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ����
    5.��    ��   : 2012��8��25��
      ��    ��   : m00217266
      �޸�����   : �޸�GMM_SndSmServiceRej�����ӿ�
    6.��    ��   : 2012��8��15��
      ��    ��   : z00161729
      �޸�����   : DCM������������������޸�
    7.��    ��   : 2012��12��11��
      ��    ��   : w00176964
      �޸�����   : NAS_MML_GetPsRestrictNormalServiceFlg�޸ĺ�����
    8.��    ��   : 2013��05��30��
      ��    ��   : l65478
      �޸�����   : DTS2013052405902, ������MMSͬʱ���е�ʱ��,MMSʧ��
    9.��    ��   : 2013��07��27��
      ��    ��   : l65478
      �޸�����   : DTS2013071003497, ���ӱ�NAS��ֹ��,GMM�յ�RAB���ؽ������û�����·���RAB�ؽ�����
   10.��    ��   : 2013��08��16��
      ��    ��   : l65478
      �޸�����   : DTS2013091003969,L handover to W���յ���Ȩ��Ϣû�д���
   11.��    ��   : 2015��1��5��
      ��    ��   : z00161729
      �޸�����   : AT&T ֧��DAM�����޸�
*******************************************************************************/
VOS_VOID Gmm_RcvRabmReestablishReq(VOS_VOID *pMsg)
{
    VOS_UINT32                      ulRrcEstCauseTemp;
    NAS_MSG_STRU                    *ptrNasMsg;
    GMMRABM_REESTABLISH_REQ_STRU    *pRabmMsg;
    GMMRABM_REESTABLISH_REQ_STRU    *ptr;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {/* 2G����ģʽ������ */
        return;
    }

    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
    {
        /* Modified by z00161729 for DCM�����������������, 2012-9-10, begin */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
        /* Modified by z00161729 for DCM�����������������, 2012-9-10, end */
        return;
    }

    pRabmMsg = (GMMRABM_REESTABLISH_REQ_STRU *)pMsg;

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    g_GmmGlobalCtrl.usUplinkDataStatus  = pRabmMsg->usUplinkDataStatus;
    #endif

    /* �����ǰ�û������б�����,���û�������б��������� */
    /*if ( VOS_TRUE == NAS_MMC_IsEnableRabmReset())
 */
    /*{
 */
    /*    Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                  ����GMMRABM_REESTABLISH_CNF(fail)        */
    /*    return;
 */
    /*}
 */

    /* ��RabmReestablishReqԭ���е�ԭ��ֵ��Ӧ��RRMM_EST_REQԭ���е�ԭ��ֵ */
    switch (pRabmMsg->ulRrcEstCause)

    {
    case GMM_RABM_RRC_EST_CAUSE_ORG_CONV_CALL:
        ulRrcEstCauseTemp = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
        break;
    case GMM_RABM_RRC_EST_CAUSE_ORG_STM_CALL:
        ulRrcEstCauseTemp = RRC_EST_CAUSE_ORIGIN_STREAM_CALL;
        break;
    case GMM_RABM_RRC_EST_CAUSE_ORG_INTER_CALL:
        ulRrcEstCauseTemp = RRC_EST_CAUSE_ORIGIN_INTERACT_CALL;
        break;
    case GMM_RABM_RRC_EST_CAUSE_ORG_BG_CALL:
        ulRrcEstCauseTemp = RRC_EST_CAUSE_ORIGIN_BACKGROUND_CALL;
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRabmReestablishReq:WARNING: RRC Connection Setup Cause is Abnormal");
        return;
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����GMM��ͬ��״̬��������Ӧ�Ĵ���        */
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ����GMMRABM_REESTABLISH_CNF(fail)        */
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_SERVICE_REQUEST_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        /* ����Ѿ���������Ϣ,���ͷ�ԭ���Ļ��� */
        if (GMM_MSG_HOLD_FOR_SERVICE
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                        GMM_MSG_HOLD_FOR_SERVICE))
        {                                                                       /* ����б�����ServiceRequestԭ��           */
            ptr = (GMMRABM_REESTABLISH_REQ_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;      /* ��ȡServiceRequestԭ���ַ               */
            Gmm_MemFree(ptr);                                                   /* ������buffer�����е���Ϣ�ͷ�             */
        }
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SERVICE;       /* ��дGMM_MSG_HOLD_STRU���͵ı���          */

        ptr = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRabmReestablishReq:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pRabmMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)ptr;               /* ������ԭ��                               */
        break;

    case GMM_REGISTERED_PLMN_SEARCH:
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;

        /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_DATA);
        /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */
        break;

    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        NAS_GMM_RcvRabmReestablishReq_AttemptToUpdate(pRabmMsg);
        break;

    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:

        if ((MM_COM_SRVST_NORMAL_SERVICE != NAS_GMM_GetRegUptNeededPsSrvStatus())
         && (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState))
        {
            return;
        }

        g_GmmGlobalCtrl.ulEstCause = ulRrcEstCauseTemp;

        if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT ==
                                                    g_GmmGlobalCtrl.ucRelCause)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
            return;
        }
        if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
            && (gstGmmCasGlobalCtrl.ucLastDataSender != enCurRat)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
            )
        {
            GMM_LOG_INFO("Gmm_RcvRabmReestablishReq:Inter System change, Exec select RAU.");

            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            return;
        }
        /* �����ǰGMM�ڽ����ӵĹ���������RAI�ı������Ҫ���ͷ����ڽ��������ӣ�
           ��ô�����ڵȴ������������ͷ�ָʾ�Լ������ͷ�ָʾ֮���ϱ���ϵͳ��Ϣ
           �������յ����ϲ�������Ҫ����*/
        if (GMM_TRUE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
        {
            if (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg)
            {
                g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

                g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
            }
            else
            {
                if (GMM_MSG_HOLD_FOR_SERVICE ==
                    (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                        GMM_MSG_HOLD_FOR_SERVICE))
                {                                                               /* ����б�����ServiceRequestԭ��           */
                    ptr = (GMMRABM_REESTABLISH_REQ_STRU *)g_GmmGlobalCtrl.MsgHold.
                                                        ulMsgAddrForService;    /* ��ȡServiceRequestԭ���ַ               */
                    Gmm_MemFree(ptr);                                           /* ������buffer�����е���Ϣ�ͷ�             */
                }
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |=
                                                    GMM_MSG_HOLD_FOR_SERVICE;   /* ��дGMM_MSG_HOLD_STRU���͵ı���          */

                ptr = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));
                if (VOS_NULL_PTR == ptr)
                {
                      PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRabmReestablishReq:ERROR: Memory is not allocated");
                      return;
                }
                Gmm_MemCpy(ptr, pRabmMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)ptr;  /* ������ԭ��                               */
            }

            return;
        }

        if (  (GMM_TIMER_T3319_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3319_FLG))
            || (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
            || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg))
        {                                                                       /* T3319/T3340������                              */
            ptr = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

            if (VOS_NULL_PTR == ptr)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRabmReestablishReq:ERROR: Memory is not allocated");
                return;
            }

            Gmm_MemCpy(ptr, pRabmMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SERVICE;   /* ����Ϣ�����־                           */
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)ptr;      /* ������ԭ��                               */
            return;
        }

        g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;                 /* ����GMM״̬                              */

        GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRabmReestablishReq:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* ������                                   */
            g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_IDLE;         /* ���õ�ǰ���е�specific����               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRabmReestablishReq:INFO: SR(data) procedure started");
            ptrNasMsg = Gmm_ServiceRequestMsgMake_ForData(pRabmMsg->usUplinkDataStatus, pRabmMsg->usPdpContextStatus);                            /* ����make����                             */

            Gmm_SndRrmmEstReq(ulRrcEstCauseTemp,
                              GMM_RRC_IDNNS_UNKNOWN,
                              ptrNasMsg);                                       /* ��RRMM_EST_REQ                           */

            Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_DATA_SERVICE_REQ,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
        }
        else
        {                                                                       /* ������                                   */
            g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_CONN;         /* ���õ�ǰ���е�specific����               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRabmReestablishReq:INFO: SR(data) procedure started");
            ptrNasMsg = Gmm_ServiceRequestMsgMake_ForData(pRabmMsg->usUplinkDataStatus, pRabmMsg->usPdpContextStatus);                            /* ����make����                             */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, ptrNasMsg);            /* ���÷���RRMM_DATA_REQ����                */
            Gmm_TimerStart(GMM_TIMER_T3317);                                    /* ����T3317                                */
        }

        if (0 != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* T3311������                              */
            Gmm_TimerPause(GMM_TIMER_T3311);                                    /* ����T3311                                */
        }
        break;

    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        g_GmmGlobalCtrl.ulEstCause = ulRrcEstCauseTemp;
        if ( (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != enCurRat)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
          )
        {
            GMM_LOG_INFO("Gmm_RcvRabmReestablishReq:Inter System change, Exec select RAU.");

            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            return;
        }

        if (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3319)))
        {                                                                       /* T3319������                              */
            ptr = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

            if (VOS_NULL_PTR == ptr)
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRabmReestablishReq:ERROR: Memory is not allocated");
                return;
            }

            Gmm_MemCpy(ptr, pRabmMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SERVICE;   /* ����Ϣ�����־                           */
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)ptr;      /* ������ԭ��                               */
            return;
        }

        g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;                 /* ����GMM״̬                              */
        GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRabmReestablishReq:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* ������                                   */
            g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_IDLE;         /* ���õ�ǰ���е�specific����               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRabmReestablishReq:INFO: SR(data) procedure started");
            ptrNasMsg = Gmm_ServiceRequestMsgMake_ForData(pRabmMsg->usUplinkDataStatus, pRabmMsg->usPdpContextStatus);                            /* ����make����                             */

            Gmm_SndRrmmEstReq(ulRrcEstCauseTemp,
                              GMM_RRC_IDNNS_UNKNOWN,
                              ptrNasMsg);                                       /* ��RRMM_EST_REQ                           */
            Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_DATA_SERVICE_REQ,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
        }
        else
        {                                                                       /* ������                                   */
            g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_CONN;         /* ���õ�ǰ���е�specific����               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRabmReestablishReq:INFO: SR(data) procedure started");
            ptrNasMsg = Gmm_ServiceRequestMsgMake_ForData(pRabmMsg->usUplinkDataStatus, pRabmMsg->usPdpContextStatus);                            /* ����make����                             */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,ptrNasMsg);             /* ���÷���RRMM_DATA_REQ����                */
            Gmm_TimerStart(GMM_TIMER_T3317);                                    /* ����T3317                                */
        }

        if (0 != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* T3311������                              */
            Gmm_TimerPause(GMM_TIMER_T3311);                                    /* ����T3311                                */
        }
        if (0 != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* T3302������                              */
            Gmm_TimerPause(GMM_TIMER_T3302_FLG);                                /* ����T3302                                */
        }
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        NAS_GMM_RcvRabmEstReq_SuspendWaitForSysinfo(pMsg);
        break;
    default:
        /* ����״̬�ظ�ʧ����Ϣ */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ����GMMRABM_REESTABLISH_CNF(fail)        */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRabmReestablishReq:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmsEstReq_SuspendWaitForSysinfo
 ��������  : ��SUSPEND WAIT FOR SYSINFO״̬���յ�SMS��Ϣ�Ĵ���
 �������  : pMsg        - �յ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��26��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��25��
    ��    ��   : w00167002
    �޸�����   : DTS2014122201960:��SUSPEND WAIT FOR SYSINFOʱ�������ʱ����
                ���У��������ϵͳ��Ϣ��
*****************************************************************************/
VOS_VOID NAS_GMM_RcvRabmEstReq_SuspendWaitForSysinfo(
    VOS_VOID                            *pMsg
)
{
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);;
        return;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);;
        return;
    }

    /* �ڴ�G�л���Wʱ,��Ҫ���ȷ���RAU�ָ�PS,Ȼ�������RABM��Ϣ */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;

        /* �����ϵͳ��Ϣ��ʱ�������У����·�RAU */
        if (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG == (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRabRelInd
  Function : �յ�GMMRABM_RAB_REL_INDԭ���Ĵ���
  Input    : VOS_VOID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
        1.  x00115505     2009.05.11  �°�����
*******************************************************************************/
VOS_VOID Gmm_RcvRabRelInd(VOS_VOID)
{
    VOS_VOID                            *pMsg;
    GMMRABM_REESTABLISH_REQ_STRU        *pRabmReEst;
    Gmm_TimerStop(GMM_TIMER_T3319);

    if (GMM_MSG_HOLD_FOR_SERVICE ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����SRԭ��                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */

        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;

        /*����ַ���Ϣ*/
        pRabmReEst = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        if (VOS_NULL_PTR == pRabmReEst)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        Gmm_MemCpy(pRabmReEst, pMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        /*�ͷű����RAMB��Ϣ*/
        Gmm_MemFree(pMsg);

        /*�ַ������Service��Ϣ*/
        Gmm_MsgDistribute((VOS_VOID *)(pRabmReEst));

        /*�ͷ���������ڴ�*/
        Gmm_MemFree(pRabmReEst);
    }
}
/*******************************************************************************
  Module   : Gmm_RcvRrmmSecurityInd
  Function : �յ�RRMM_SECURITY_INDԭ���Ĵ���
  Input    : VOS_VOID *pMsg     ԭ���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �°�����
    2.��    ��   : 2012��03��2��
      ��    ��   : l00130025
      �޸�����   : DTS2012022906401:L->W Handover SMC��ϵͳ��Ϣǰ�յ�ʱû�д�������RAUʧ��
    3.��    ��   : 2012��09��26��
      ��    ��   : z00161729
      �޸�����   : DTS2012080605232:W������פ������T3312,������L ��HO��W��gmm����pmm_connected״̬δֹͣT3312
    4.��    ��   : 2015��7��2��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmSecurityInd(VOS_VOID *pMsg)
{
    RRMM_SECURITY_IND_STRU             *pstSecurityInd = VOS_NULL_PTR;

    pstSecurityInd = (RRMM_SECURITY_IND_STRU *)pMsg;

    /* �յ��˴���������Security Mode Command ��Ϣ */
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_TRUE;

    if (RRC_SECURITY_PS_SMC_CMPL == pstSecurityInd->ulRptMode)
    {
        /* һ��PS SMC���̽�����Ϊ����PMM_CONNECTED״̬����ҪֹͣT3312 */
        Gmm_TimerStop(GMM_TIMER_T3312);
#if (defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER )
#else
#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
#endif

        /* 24008_CR1735R3_(Rel-10)_C1-111529 was 1470 was 1012 24008-a10 24008 4.7.5.1.5�½���������:
        If in addition the ROUTING AREA UPDATE REQUEST message indicated "periodic updating",
        -   in Iu mode, the timer T3311 may be stopped when the MS enters PMM-CONNECTED mode;
        -   in A/Gb mode, the timer T3311 may be stopped when the READY timer is started.*/
        NAS_GMM_StopT3311InIuPmmConnMode_T3312Exp();

    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����GMM��ͬ��״̬��������Ӧ�Ĵ���        */
    case GMM_REGISTERED_INITIATED:
    case GMM_DEREGISTERED_INITIATED:
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvRrmmSecurityInd_RegInit((RRMM_SECURITY_IND_STRU *)pMsg);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvRrmmSecurityInd_ServReqInit((RRMM_SECURITY_IND_STRU *)pMsg);
        break;

    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        Gmm_RcvRrmmSecurityInd_SuspendWaitSysinfo((RRMM_SECURITY_IND_STRU *)pMsg);
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmSecurityInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
}
/*******************************************************************************
  Module   : Gmm_RcvRrmmSecurityInd_RegInit
  Function : ��GMM-REGISTERED-INITIATED״̬�£��յ�RRMM_SECURITY_INDԭ���Ĵ���
  Input    : RRMM_SECURITY_IND_STRU *ptr     ԭ���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.10  �°�����
  2. ��־��  2004.10.27  CK,IK�洢��ʽ���
  3.��    ��   : 2006��12��5��
    ��    ��   : luojian 60022475
    �޸�����   : Maps3000�ӿ��޸�
  4.��    ��   : 2011��3��3��
    ��    ��   : z00161729
    �޸�����   : DTS2011021201997:PS��CS�����Ա����Ƿ�����GMM��MM�ֿ�ά��,MMC����ά��
  2.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6.��    ��  :2014��01��09��
    ��    ��  :l65478
    �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmSecurityInd_RegInit(
                                    RRMM_SECURITY_IND_STRU *ptr                 /* ԭ���׵�ַ                               */
                                    )
{
    if (RRC_SECURITY_PS_SMC_RCV == ptr->ulRptMode)
    {                                                                           /* ulRptMode=�յ���Ч��PS SMC��Ϣ           */
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                            /* ��"RES���ڱ�־ "��Ϊ0                    */
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                            /* ��"RAND���ڱ�־ "��Ϊ0                   */

        Gmm_TimerStop(GMM_TIMER_T3316);                                         /* ֹͣT3316                                */

        /*A32D12268==>�����Ա�������*/
        g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect   = NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE;
        /*<==A32D12268*/
    }
    else if ((RRC_SECURITY_DEL_CS_PS_KEY == ptr->ulRptMode)
        || (RRC_SECURITY_DEL_PS_KEY == ptr->ulRptMode))
    {                                                                           /* ulRptMode=USIM��(CS+PS)/PS��CK��IK��ɾ�� */

        NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);            /* ɾ��CKSN                                 */
        NAS_MML_InitPsSecurityUmtsCkInvalid();
        NAS_MML_InitPsSecurityUmtsIkInvalid();
    }
    else
    {
    }
}
/*******************************************************************************
  Module   : Gmm_RcvRrmmSecurityInd_ServReqInit
  Function : ��GMM-SERVICE-REQUEST-INITIATED״̬�£��յ�RRMM_SECURITY_INDԭ
             ���Ĵ���
  Input    : RRMM_SECURITY_IND_STRU *ptr     ԭ���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �°�����
  2.��־��  2004.10.27  CK,IK�洢��ʽ���
  3.��    ��   : 2006��12��5��
    ��    ��   : luojian 60022475
    �޸�����   : Maps3000�ӿ��޸�
  4.��    ��   : 2008��9��18��
    ��    ��   : ouyangfei 00132663
    �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬
                  ��GMM���̽����ٷ���
  5.��    ��   : 2011��3��3��
    ��    ��   : z00161729
    �޸�����   : DTS2011021201997:PS��CS�����Ա����Ƿ�����GMM��MM�ֿ�ά��,MMC����ά��
  6.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  7.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  8.��    ��   : 2012��8��1��
    ��    ��   : A00165503
    �޸�����   : DTS2012072705055: GMM��SM֮�������������ӽ���ָʾԭ��, SM��
                 �ݸ�ԭ������T3380, T3381��T3390
  9.��    ��  :2014��01��09��
    ��    ��  :l65478
    �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmSecurityInd_ServReqInit(
                                        RRMM_SECURITY_IND_STRU *ptr             /* ԭ���׵�ַ                               */
                                        )
{
    GMMSM_DATA_REQ_STRU *pSmDataReqMsg;                                         /* ָ��GMMSM_DATA_REQ_STRU�ṹ��ָ��        */


    if (RRC_SECURITY_PS_SMC_CMPL == ptr->ulRptMode)
    {                                                                           /* ulRptMode=һ��SMC���̽���                */
        if (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
        {                                                                       /* service type = data_connected            */
            return;
        }

        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* ����״̬�Ĺ�������                       */
        if (GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
        {
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_SUCCESS);             /* ����GMMRABM_REESTABLISH_CNF��Success��   */
            /* RABM������ Service Request ���̳ɹ������ӻ�л����RABM
               �ؽ���Ϣ����ô����Ҫ�ٴ������෢�ͣ���������ɡ� */
            if (GMM_MSG_HOLD_FOR_SERVICE
                == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
            {                                                                           /* ����б�����SRԭ��                       */
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */
                Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
            }

            Gmm_TimerStart(GMM_TIMER_T3319);                                    /* ����3319                                 */
        }
        if ((GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
            && (GMM_MSG_HOLD_FOR_SM
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM)))
        {                                                                       /* ��ǰ��������SERVICE_REQUEST_SIGNALLING   */
            NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmSecurityInd_ServReqInit(): Process cached SM Data Req");

            pSmDataReqMsg =
                (GMMSM_DATA_REQ_STRU*)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;   /* �õ���������Ϣ                           */

            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                    &pSmDataReqMsg->SmMsg);                     /* ����RRMM_DATA_REQ(CM�Ӳ����Ϣ�׵�ַ)    */

            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;       /* ���������־                             */
            Gmm_MemFree(pSmDataReqMsg);                                         /* �ͷű����SM��Ϣ                         */

            NAS_GMM_SndSmSigConnInd();
        }

        if ( GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
        {                                                                       /* SMS�ڵȴ���Ӧ                            */
            Gmm_SndSmsEstCnf();                                                 /* ����PMMSMS_EST_CNF                       */
            g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
        }

        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);                                     /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


        /* ��MMC����service request��� */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_SUCCESS,
                                              NAS_MML_REG_FAIL_CAUSE_NULL);
        /* �¼��ϱ� */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_ACC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ���е�specific����                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmSecurityInd_ServReqInit:INFO: specific procedure ended");
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
        {
        }

        if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
        {                                                                       /* �б�������Ϣ                             */
            Gmm_DealWithBuffAfterProc();
        }

    }
    else if (RRC_SECURITY_PS_SMC_RCV == ptr->ulRptMode)
    {                                                                           /* ulRptMode=�յ���Ч��PS SMC��Ϣ           */
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                            /* ��"RES���ڱ�־ "��Ϊ0                    */
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                            /* ��"RAND���ڱ�־ "��Ϊ0                   */

        Gmm_TimerStop(GMM_TIMER_T3316);                                         /* ֹͣT3316                                */

        /*A32D12268==>�����Ա�������*/
        g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                        NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE;
        /*<==A32D12268*/
    }
    else if ((RRC_SECURITY_DEL_CS_PS_KEY == ptr->ulRptMode)
        || (RRC_SECURITY_DEL_PS_KEY == ptr->ulRptMode))
    {                                                                           /* ulRptMode=USIM��(CS+PS)/PS��CK��IK��ɾ�� */
        NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);            /* ɾ��CKSN                                 */
        NAS_MML_InitPsSecurityUmtsCkInvalid();
        NAS_MML_InitPsSecurityUmtsIkInvalid();
    }
    else
    {
    }

}
/*****************************************************************************
 �� �� ��  : Gmm_RcvRrmmSecurityInd_SuspendWaitSysinfo
 ��������  : SuspendWaitSysinfo״̬��SecurityInd�Ĵ���
 �������  : RRMM_SECURITY_IND_STRU              *pStSecurityInd
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��1��
    ��    ��   : l00130025
    �޸�����   : DTS2012022906401,L->W handover��Resume���յ�Security_indû�д���
  2.��    ��  :2014��01��09��
    ��    ��  :l65478
    �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
*****************************************************************************/

VOS_VOID Gmm_RcvRrmmSecurityInd_SuspendWaitSysinfo(
    RRMM_SECURITY_IND_STRU              *pStSecurityInd
)
{
    if (RRC_SECURITY_PS_SMC_CMPL == pStSecurityInd->ulRptMode)
    {
        Gmm_TimerStop(GMM_TIMER_T3317);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);

    }
    else if (RRC_SECURITY_PS_SMC_RCV == pStSecurityInd->ulRptMode)
    {
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;

        Gmm_TimerStop(GMM_TIMER_T3316);

        g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                        NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE;

    }
    else if ((RRC_SECURITY_DEL_CS_PS_KEY == pStSecurityInd->ulRptMode)
        || (RRC_SECURITY_DEL_PS_KEY == pStSecurityInd->ulRptMode))
    {
        NAS_MML_SetSimPsSecurityCksn(NAS_MML_CKSN_INVALID);
        NAS_MML_InitPsSecurityUmtsCkInvalid();
        NAS_MML_InitPsSecurityUmtsIkInvalid();
    }
    else
    {
    }

}

/*******************************************************************************
  Module   : Gmm_RcvServiceAcceptMsg
  Function : �յ�service accept��Ϣ��Ĵ���
  Input    : NAS_MSG_STRU *pMsg     NAS��Ϣ�׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �°�����
  2.��    ��   : 2008��9��18��
    ��    ��   : ouyangfei 00132663
    �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬
                  ��GMM���̽����ٷ���
  3.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2012��04��24��
    ��    ��   : L65478
    �޸�����   : DTS2012042407125,û�д���PDP STATUS IE
  5.��    ��   : 2012��08��24��
    ��    ��   : m00217266
    �޸�����   : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ��ɾ��GMM_ClearErrCode
  6.��    ��  :2014��01��09��
    ��    ��  :l65478
    �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ

  6.��    ��   : 2014��5��28��
    ��    ��   : z00234330
    �޸�����   : SMC����,dts2014052907662
  7.��    ��   : 2015��7��2��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvServiceAcceptMsg(
                             NAS_MSG_FOR_PCLINT_STRU *pMsg
                             )
{

    NAS_MSG_STRU        *pGmmStatus;
    VOS_UINT32           ulPDPStatus;

    ulPDPStatus = 0;

    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_SERVICE_ACCEPT)
    {                                                                           /* ���нӿڳ��ȷǷ�                         */

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvServiceAcceptMsg:WARNING: Length of SERVICE ACCEPT is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);

        return;
    }

    if ( (VOS_TRUE == NAS_UTRANCTRL_IsUtranPsSmcNeeded())
      && (GMM_SERVICE_REQUEST_DATA_CONN != g_GmmGlobalCtrl.ucSpecProc))
    {
        return;
    }

    /* 24008_CR1735R3_(Rel-10)_C1-111529 was 1470 was 1012 24008-a10 24008 4.7.5.1.5�½���������:
    If in addition the ROUTING AREA UPDATE REQUEST message indicated "periodic updating",
    -   in Iu mode, the timer T3311 may be stopped when the MS enters PMM-CONNECTED mode;
    -   in A/Gb mode, the timer T3311 may be stopped when the READY timer is started.
    TDS��û��SMC����������service accept�����ж����Ƿ���ҪֹͣT3311��ʱ�� */
    NAS_GMM_StopT3311InIuPmmConnMode_T3312Exp();

    Gmm_TimerStop(GMM_TIMER_T3316);                                             /* ֹͣT3316                                */

    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* ��"RES���ڱ�־ "��Ϊ0                    */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* ��"RAND���ڱ�־ "��Ϊ0                   */

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����GMM��ͬ��״̬��������Ӧ�Ĵ���        */
    case GMM_SERVICE_REQUEST_INITIATED:
        if (pMsg->ulNasMsgSize >= (GMM_MSG_LEN_SERVICE_ACCEPT + NAS_GMM_IE_LEN_PDP_STATUS))
        {
            if (GMM_IEI_PDP_CONTEXT_STATUS == pMsg->aucNasMsg[GMM_SR_ACCEPT_IE_PDP_CONTEXT_STATUS])
            {
                /* PDP status��TLV���͵�IE,����Ҫ�������ͺͳ��Ȼ�ȡPDP status */
                ulPDPStatus = (pMsg->aucNasMsg[GMM_SR_ACCEPT_IE_PDP_CONTEXT_STATUS + 3] << 8) | \
                            pMsg->aucNasMsg[GMM_SR_ACCEPT_IE_PDP_CONTEXT_STATUS + 2];

                Gmm_SndSmPdpStatusInd(ulPDPStatus, GMM_SM_CAUSE_SERVICE_ACCEPT);
            }
        }
        if ( (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
          || (GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc))
        {
          Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_SUCCESS);                 /* ����GMMRABM_REESTABLISH_CNF(success)     */
        }

        /* RABM������ Service Request ���̳ɹ���������л����RABM
           �ؽ���Ϣ����ô����Ҫ�ٴ������෢�ͣ���������ɡ� */
        if (GMM_MSG_HOLD_FOR_SERVICE
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
        {                                                                           /* ����б�����SRԭ��                       */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
        }

        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_TimerStart(GMM_TIMER_T3319);                                        /* ����3319                                 */

        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* ����״̬�Ĺ�������                       */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_SUCCESS,
                                        NAS_MML_REG_FAIL_CAUSE_NULL);                                     /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


        /* ��MMC����service request��� */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_SUCCESS,
                                              NAS_MML_REG_FAIL_CAUSE_NULL);
        /* �¼��ϱ� */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_ACC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ���е�specific����                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvServiceAcceptMsg:INFO: specific procedure ended");
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
        {
        }

        if ( GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
        {                                                                       /* SMS�ڵȴ���Ӧ                            */
            Gmm_SndSmsEstCnf();                                                 /* ����PMMSMS_EST_CNF                       */
            g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
        }

        if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
        {                                                                       /* �б�������Ϣ                             */
            Gmm_DealWithBuffAfterProc();
        }
        g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvServiceAcceptMsg:WARNING: SERVICE ACCEPT is unexpected");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        break;
    }
}

/*****************************************************************************
 �� �� ��  : Gmm_RcvServiceRejectMsg_Cause_Handling
 ��������  : �ַ������봦��
 �������  : ucRejectCause �ܾ���ԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��20��
    ��    ��   : S62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��25��
    ��    ��   : m00217266
    �޸�����   : ɾ��GMM_SaveErrCode�����Gmm_Save_Detach_Cause��
                ���浼��Attachʧ�ܵ�ԭ��ֵ
  3.��    ��   : 2015��6��5��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID  Gmm_RcvServiceRejectMsg_Cause_Handling(VOS_UINT8 ucRejectCause)
{
    /*���汻�ܾ��Ĵ�����*/
    NAS_GMM_SetAttach2DetachErrCode(NAS_GMM_TransGmmNwCause2GmmSmCause(ucRejectCause));

    switch (ucRejectCause)
    {
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:
        Gmm_ServiceReqRejectCasue3(ucRejectCause);
        break;

    /*24008_CR2297R2_(Rel-11)_C1-124967 24008 4.7.13.4��������:
    #8 - The MS shall set the GPRS update status to GU3 ROAMING NOT ALLOWED (and
    shall store it according to subclause 4.1.3.2) and shall delete any P-TMSI,
    P-TMSI signature, RAI and GPRS ciphering key sequence number. The new GMM state
    is GMM-DEREGISTERED.
    The MS shall set the update status to U3 ROAMING NOT ALLOWED, shall delete any TMSI, LAI
    and ciphering key sequence number. If the MS is operating in MS operation mode A and an RR
    connection exists, the MS shall abort the RR connection, unless an emergency call is ongoing.
    The SIM/USIM shall be considered as invalid for GPRS and non-GPRS services until switching off
    or the SIM/USIM is removed. */
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:
        Gmm_ServiceReqRejectCasue3(ucRejectCause);
        break;

    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:
        Gmm_ServiceReqRejectCasue7();
        break;
    case NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED:
        Gmm_ServiceReqRejectCasue9();
        break;
    case NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED:
        Gmm_ServiceReqRejectCasue10();
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:
        Gmm_ServiceReqRejectCasue11();
        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:
        Gmm_ServiceReqRejectCasue12();
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:
        Gmm_ServiceReqRejectCasue13(ucRejectCause);
        break;
    case NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT:
        Gmm_ServiceReqRejectCasue40();
        break;
    default:
        Gmm_ServiceReqRejectTheOtherCause(ucRejectCause);
        break;
    }
    return;

}

/*******************************************************************************
  Module   : Gmm_RcvServiceRejectMsg
  Function : �յ�service reject��Ϣ��Ĵ���
  Input    : NAS_MSG_STRU *pMsg  NAS��Ϣ�׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �°�����
    2. ��    ��   : 2008��9��18��
       ��    ��   : ouyangfei 00132663
       �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬��GMM���̽����ٷ���
    3. ��    ��   : 2010��11��24��
       ��    ��   : ��ë 00166186
       �޸�����   : �������ⵥ��DTS2010112205253,DEFAULT��֧������ԭ��ֵ��д����ȷ
    4. ��    ��   : 2011��7��26��
       ��    ��   : c00173809
       �޸�����   : �������ⵥ��DTS2011072203766,����PDP�����(ԭ��#15)��BALONG������SM����ʧ�ܡ�
    5.��    ��   : 2012��02��16��
      ��    ��   : L65478
      �޸�����   : ���ⵥ��;DTS2012021602026,GCF����ʧ��,PDP�������ܾ������������·�����PDP��������
    6.��    ��   : 2012��3��17��
      ��    ��   : w00176964
      �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:���Ӳ��ű��ܶ���
    7.��    ��   : 2012��3��21��
      ��    ��   : z40661
      �޸�����   : DTS2011112403767:L��ѡ��W��������ܾ�#9��Я����PTMSI����ȷ
    8.��    ��   : 2012��8��25��
      ��    ��   : m00217266
      �޸�����   : �޸ĺ���GMM_SndSmServiceRej�����ԭ��ֵ���
    9.��    ��   : 2013��1��4��
      ��    ��   : w00176964
      �޸�����   : DTS2013010400031:ȫ�ֱ���g_ucGcfInd�滻ΪUSIM�ṩAPI����USIMM_IsTestCard
   10.��    ��   : 2013��6��5��
      ��    ��   : w00242748
      �޸�����   : svlte��usim�ӿڵ���
   11.��    ��  :2014��01��09��
      ��    ��  :l65478
      �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
   12.��    ��  :2014��04��2��
      ��    ��  :w00242748
      �޸�����  :DTS2014040200322:PS����PS����ʱ��������ܾ�ԭ��ֵ#3,#6,#7,#8
                 ����PS����Ч�����������ֳ�����
   13.��    ��   : 2014��10��20��
      ��    ��   : h00285180
      �޸�����   : �ܾ�ԭ��ֵ�Ż�PhaseII DTS2014110307415
*******************************************************************************/
VOS_VOID Gmm_RcvServiceRejectMsg(
                             NAS_MSG_FOR_PCLINT_STRU *pMsg
                             )
{
    VOS_UINT8                           ucRejectCause;                                         /* �ܾ�ԭ��                                 */
    NAS_MSG_STRU                       *pGmmStatus;
    VOS_UINT8                           ucDellRejectEnableFlg;

    /* ��ȡ���ű��ܶ����Ƿ�ʹ�� */
    ucDellRejectEnableFlg = NAS_MML_GetDailRejectCfg();

    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_SERVICE_REJECT)
    {                                                                           /* ���нӿڳ��ȷǷ�                         */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvServiceRejectMsg:WARNING: Length of SERVICE REJECT is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    if (GMM_SERVICE_REQUEST_INITIATED != g_GmmGlobalCtrl.ucState)
    {                                                                           /* GMM״̬= GMM-SERVICE-REQUEST-INITIATED   */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvServiceRejectMsg:WARNING: SERVICE REJECT is unexpected");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    if ((GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
         ||(GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* service request type=data                */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ����GMMRABM_REESTABLISH_CNF(failure)     */
    }
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ͣT3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
    Gmm_TimerStop(GMM_TIMER_T3316);                                             /* ֹͣT3316                                */

    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* ��"RES���ڱ�־ "��Ϊ0                    */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* ��"RAND���ڱ�־ "��Ϊ0                   */
    NAS_GMM_ChangePsSerRejCauseAvoidInvalidSim(&(pMsg->aucNasMsg[2]));

    ucRejectCause = *(pMsg->aucNasMsg + 2);

    /*����ܾ�ԭ��Ϊ15ʱ������SM��ʧ�ܣ�Ҳ�����SM��Ϣ���壬������ע����ٻؽ����*/
    if ((VOS_FALSE == NAS_USIMMAPI_IsTestCard())
     && (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == ucRejectCause)
     && (VOS_FALSE == ucDellRejectEnableFlg))
    {
        g_GmmServiceCtrl.ucRejCauseVaildFlg = GMM_TRUE;  /* reject casue valid*/
        g_GmmServiceCtrl.ucRejCause         = ucRejectCause;

        Gmm_RcvServiceRejectMsg_Cause_Handling(ucRejectCause);
        NAS_GMM_CheckCauseToStartT3340(ucRejectCause);

        g_GmmServiceCtrl.ucRejCauseVaildFlg = GMM_FALSE;    /* ������� */

        return;
    }
    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvServiceRejectMsg(): Service reject, clear msg cached buffer");

    Gmm_HoldBufferFree();                                                       /* ���������Ϣ                             */

    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {                                                                           /* SMS�ڵȴ���Ӧ                            */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
        /* ����Ѿ�������SMS��Ϣ,���ͷ�ԭ���Ļ��� */
        if (GMM_MSG_HOLD_FOR_SMS
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SMS))
        {                                                                       /* ����б�����EST_REQԭ��           */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;      /* ��������־                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);               /* ������buffer�����е���Ϣ�ͷ�             */
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)NULL;
        }
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ����PMMSMS_ERROR_IND                     */
    }

    if ((GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
     && (GMM_TRUE == g_GmmServiceCtrl.ucSmFlg))
    {
        /* ����ܾ�ԭ��Ϊ 9��10������SM���;ܾ���Ϣ����Ҫ���SM��Ϣ���壬��ATTACH��ɺ�������PDP���� */
        if ((NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED != ucRejectCause)
         && (NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED != ucRejectCause))
        {
            /* service reject ����ԭ��ֵ����NV��ʱ������40���ܻظ�ʧ�� */
            if (((NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT != ucRejectCause)
              && (VOS_TRUE == ucDellRejectEnableFlg))
             || (VOS_FALSE == ucDellRejectEnableFlg))
            {
                GMM_SndSmServiceRej(NAS_GMM_TransGmmNwCause2GmmSmCause(ucRejectCause));
            }
        }

        g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
    }

    if (ucRejectCause == NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT)
    {
        Gmm_SndSmPdpStatusInd(0, GMM_SM_CAUSE_NO_PDP_CONTEXT_ACT);
    }

    g_GmmServiceCtrl.ucRejCauseVaildFlg = GMM_TRUE;  /* reject casue valid*/
    g_GmmServiceCtrl.ucRejCause         = ucRejectCause;

    Gmm_RcvServiceRejectMsg_Cause_Handling(ucRejectCause);
    NAS_GMM_CheckCauseToStartT3340(ucRejectCause);

    g_GmmServiceCtrl.ucRejCauseVaildFlg = GMM_FALSE;    /* ������� */
    return;
}

/*******************************************************************************
  Module   : Gmm_ServiceReqRejectCasue3
  Function : �յ�ԭ��ֵΪ3��service reject��Ϣ��Ĵ���
  Input    : VOS_UINT8 ucCause    ʧ��ԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
*******************************************************************************/
VOS_VOID Gmm_ServiceReqRejectCasue3(
                                VOS_UINT8 ucCause                               /* ʧ��ԭ��                                 */
                                )
{
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);      /* update status��ΪGU3                     */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
    Gmm_DelPsLocInfoUpdateUsim();
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                    /* ����״̬�Ĺ�������                       */

    /* �����ر�־ */
    NAS_GMM_ClearIMSIOfUeID();

    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE, ucCause);/* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* ��MMC����service request��� */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          ucCause);
    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)(&ucCause),
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �嵱ǰ����                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue3:INFO: SERVICE REJECT is unexpected");
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* �屣������                               */

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */

}

/*******************************************************************************
  Module   : Gmm_ServiceReqRejectCasue7
  Function : �յ�ԭ��ֵΪ7��service reject��Ϣ��Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
*******************************************************************************/
VOS_VOID Gmm_ServiceReqRejectCasue7(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;

    enCause = NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW;

    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);      /* update status��ΪGU3                     */
    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
    Gmm_DelPsLocInfoUpdateUsim();
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                    /* ����״̬�Ĺ�������                       */

    /* �����ر�־ */
    NAS_GMM_ClearIMSIOfUeID();

    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                 /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* ��MMC����service request��� */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �嵱ǰ����                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue7:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* �屣������                               */

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */

}
/*******************************************************************************
  Module   : Gmm_ServiceReqRejectCasue9
  Function : �յ�ԭ��ֵΪ9��service reject��Ϣ��Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������

  3.��    ��   : 2012��3��21��
    ��    ��   : z40661
    �޸�����   : DTS2011110201060:L��ѡ��W��������ܾ�#9��Я����PTMSI����ȷ

*******************************************************************************/
VOS_VOID Gmm_ServiceReqRejectCasue9(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;

    enCause = NAS_MML_REG_FAIL_CAUSE_MS_ID_NOT_DERIVED;

    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);         /* update status��ΪGU2                     */

    Gmm_DelPsLocInfoUpdateUsim();
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* ����״̬�Ĺ�������                       */
    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */

#if (FEATURE_ON == FEATURE_LTE)

    NAS_GMM_SetLteGutiValid(VOS_FALSE);
#endif

    Gmm_Attach_Prepare();
    Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                     /* ����attach                               */

#if (FEATURE_ON == FEATURE_LTE)
    NAS_GMM_SetLteGutiValid(VOS_TRUE);
#endif
}
/*******************************************************************************
  Module   : Gmm_ServiceReqRejectCasue10
  Function : �յ�ԭ��ֵΪ10��service reject��Ϣ��Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������

*******************************************************************************/
VOS_VOID Gmm_ServiceReqRejectCasue10(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_IMPLICIT_DETACHED;
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* ����״̬�Ĺ�������                       */

    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */

    Gmm_Attach_Prepare();
    Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                     /* ����attach                               */
}
/*******************************************************************************
  Module   : Gmm_ServiceReqRejectCasue11
  Function : �յ�ԭ��ֵΪ11��service reject��Ϣ��Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.10  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
*******************************************************************************/
VOS_VOID Gmm_ServiceReqRejectCasue11(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;

    enCause = NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW;

    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);      /* update status��ΪGU3:PLMN not allowed    */

    g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN;                   /* ���ý�ֹע���б��־                     */
    Gmm_DelPsLocInfoUpdateUsim();

    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                            /* ����״̬�Ĺ�������                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                 /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* ��MMC����service request��� */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �嵱ǰ����                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue11:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* �屣������                               */

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */

}
/*******************************************************************************
  Module   : Gmm_ServiceReqRejectCasue12
  Function : �յ�ԭ��ֵΪ12��service reject��Ϣ��Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.10  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
*******************************************************************************/
VOS_VOID Gmm_ServiceReqRejectCasue12(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16   enCause;

    enCause                             = NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW;
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);      /* update status��ΪGU3                     */
    g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS;    /* ���ý�ֹע���б��־                     */
    Gmm_DelPsLocInfoUpdateUsim();

    g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_TRUE;
    Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                            /* ����״̬�Ĺ�������                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                 /* ����MMCGMM_GMM_ACTION_RESULT_IND         */


    /* ��MMC����service request��� */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �嵱ǰ����                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue12:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* �屣������                               */

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */

}
/*******************************************************************************
  Module   : Gmm_ServiceReqRejectCasue13
  Function : �յ�ԭ��ֵΪ13��service reject��Ϣ��Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
*******************************************************************************/
VOS_VOID Gmm_ServiceReqRejectCasue13(
                             VOS_UINT8 ucCause                                  /* ʧ��ԭ��                                 */
                             )
{
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);      /* update status��ΪGU3                     */
    g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_ROAM;            /* ���ý�ֹע���б��־                     */

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
    }
    else
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
    }

    Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                              /* ����״̬�Ĺ�������                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    ucCause);                                /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* ��MMC����service request��� */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          ucCause);
    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&ucCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �嵱ǰ����                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue13:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* �屣������                               */

    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */

}

/*******************************************************************************
  Module   : Gmm_ServiceReqRejectCasue40
  Function : �յ�ԭ��ֵΪ40��service reject��Ϣ��Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.10  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������

*******************************************************************************/
VOS_VOID Gmm_ServiceReqRejectCasue40(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT;
    Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* ����״̬�Ĺ�������                       */

    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                 /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* ��MMC����service request��� */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �嵱ǰ����                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectCasue40:INFO: specific procedure ended");

    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* ���ڱ������T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* �ָ�T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* ���ڱ������T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* �ָ�T3302                                */
    }
    else
    {
    }
}
/*******************************************************************************
  Module   : Gmm_ServiceReqRejectTheOtherCause
  Function : �յ�ԭ��ֵΪ3��6��7��9��10��11��12��13��15��40֮��ֵ��
             service reject��Ϣ��Ĵ���
  Input    : VOS_UINT8 ucCause  :�ܾ�ԭ��ֵ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��   2003.12.10  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������

*******************************************************************************/
VOS_VOID Gmm_ServiceReqRejectTheOtherCause(
                                       VOS_UINT8 ucCause                        /* �ܾ�ԭ��ֵ                               */
                                       )
{

    Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* ����״̬�Ĺ�������                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    ucCause);                        /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */

    /* ��MMC����service request��� */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          ucCause);
    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID*)&ucCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �嵱ǰ����                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ServiceReqRejectTheOtherCause:INFO: specific procedure ended");
    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* ���ڱ������T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* �ָ�T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* ���ڱ������T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* �ָ�T3302                                */
    }
    else
    {
    }
}
/*******************************************************************************
  Module   : Gmm_ServiceRequestMsgMake
  Function : service request������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : NAS_MSG_STRU *ptrNasMsg    :NAS��Ϣ�׵�ַ
  History  :
  1. ��־��  2003.12.10  �°�����
  2.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  3.��    ��   : 2012��3��7��
    ��    ��   : z00161729
    �޸�����   : V7R1 C50 ֧��ISR�޸�
  4.��    ��   : 2012��3��15��
    ��    ��   : l65478
    �޸�����   : DTS2013120300990:��PDP��������з���RAU,��һ��PDP����ʧ��
  5.��    ��   : 2014��12��06��
    ��    ��   : A00165503
    �޸�����   : DTS2014120207400: ����ȥ������PDP, ���಻�ͷ�RRC����
  6.��    ��   : 2016��1��20��
    ��    ��   : c00318887
    �޸�����   : DTS2015123110917: usim����GSM����2G��Ȩ��csfb��3G�¼�Ȩ����
*******************************************************************************/
NAS_MSG_STRU *Gmm_ServiceRequestMsgMake()
{
    NAS_MSG_FOR_PCLINT_STRU            *ptrNasMsg;
    NAS_MSG_STRU                       *pNasMsg;
    VOS_UINT8                           ucTotalLen = GMM_MSG_LEN_SERVICE_REQUEST;       /* ���нӿ���Ϣ�ĳ���                       */
    VOS_UINT8                           ucServiceType;                                  /* ��ʱ����                                 */
    VOS_UINT8                           i;                                              /* ѭ�����Ʊ���                             */

    VOS_UINT32                          ulPdpCtxStatus;
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    /* �̶�IE: PDP context status IE */
    ucTotalLen += 4;

    pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc((sizeof(NAS_MSG_STRU)
                                              + ucTotalLen) - 4);               /* �����ڴ�ռ�                             */
    if (VOS_NULL_PTR == pNasMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ServiceRequestMsgMake:WARNING: Alloc memory fail.");
        return pNasMsg;
    }

    ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;

    ptrNasMsg->ulNasMsgSize = ucTotalLen;
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;                                       /* GMM_PD_GMMΪ��0x0080                     */
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_SERVICE_REQUEST;                          /* GMM_MSG_SERVICE_REQUESTΪ��12            */

    /* �õ�service ��type */
    if (GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
    {                                                                           /* ��ǰ���е�specific������GMM_SERVICE_REQU *
                                                                                 * EST_SIGNALLING/                          */
        ucServiceType = GMM_SERVICE_TYPE_SIGNALLING;
    }
    else if (GMM_SERVICE_REQUEST_PAGING_RSP == g_GmmGlobalCtrl.ucSpecProc)
    {                                                                           /* ��ǰ���е�specific������GMM_SERVICE_REQU *
                                                                                 * EST_PAGING_RSP                           */
        ucServiceType = GMM_SERVICE_TYPE_PAGING_RSP;
    }
    else
    {                                                                           /* ��ǰ���е�specific������service "data"   */
        ucServiceType = GMM_SERVICE_TYPE_DATA;
    }

    
    if (VOS_TRUE == NAS_MML_IsNeedClearPsCksn_UsimDoneGsmPsAuth())
    {
        NAS_MML_SetSimPsSecurityCksn(MM_CKSN_INVALID);

        NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_FALSE);
    }
    
    ptrNasMsg->aucNasMsg[2] =
        (VOS_UINT8)((NAS_MML_GetSimPsSecurityCksn() & 0x07) |
                                        ((ucServiceType & 0x07) << 4));         /* ��ptrNasMsg->aucNasMsg[2]��ֵ            */
    ptrNasMsg->aucNasMsg[3] = 5;                                                /* ptrNasMsg-> aucNasMsg[3]= P_TMSI�ĳ���   */
    ptrNasMsg->aucNasMsg[4] = GMM_MOBILE_ID_TMSI_PTMSI | 0xF0;                  /* ��ptrNasMsg-> aucNasMsg[4]�������       */

    if (GMM_UEID_P_TMSI
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI))
    {
        PS_MEM_CPY(&ptrNasMsg->aucNasMsg[5],
                   NAS_MML_GetUeIdPtmsi(),
                   NAS_MML_MAX_PTMSI_LEN);                                         /* P_TMSI��ֵ                               */
    }
    else
    {
        for (i=0; i<4; i++)
        {                                                                       /* ��P_TMSI�������                         */
            ptrNasMsg->aucNasMsg[5 + i] = GMM_PTMSI_INVALID;
        }
    }

    ptrNasMsg->aucNasMsg[9]   = GMM_IEI_PDP_CONTEXT_STATUS;
    ptrNasMsg->aucNasMsg[10]  = 2;

    NAS_GMM_ConvertPdpCtxStatusToNetworkPdpCtxStatus(pstPsBearerCtx, &ulPdpCtxStatus);
    ptrNasMsg->aucNasMsg[11] = (VOS_UINT8)(ulPdpCtxStatus & 0xE0);
    ptrNasMsg->aucNasMsg[12] = (VOS_UINT8)(ulPdpCtxStatus >> NAS_MML_OCTET_MOVE_EIGHT_BITS);

    /* ����Service Request���̣�����GMM��·�ͷſ��Ʊ��� */
    NAS_GMM_UpdateGmmLinkCtrlStru();
    g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_FALSE;
    g_GmmServiceCtrl.ucServiceRequestProc = g_GmmGlobalCtrl.ucSpecProc;

    return (NAS_MSG_STRU *)ptrNasMsg;
}

/*****************************************************************************
 �� �� ��  : Gmm_ServiceRequestMsgMake_ForData
 ��������  : service request For Data���͵�����
 �������  : pMsg
 �������  :
 �� �� ֵ  : NAS_MSG_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2010��1��14��
   ��    ��   : Z00163274
   �޸�����   : �����ɺ���

 2.��    ��   : 2010��7��17��
   ��    ��   : ŷ����
   �޸�����   : DTS2010071601574, ���������ʹ�ָ��GMMRABM_REESTABLISH_REQ_-
                STRU��ָ���ΪusUplinkDataStatus��
 3.��    ��   : 2011��7��27��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
 4.��    ��   : 2012��3��7��
   ��    ��   : z00161729
   �޸�����   : V7R1 C50 ֧��ISR�޸�
 5.��    ��   : 2013��05��30��
   ��    ��   : l65478
   �޸�����   : DTS2013052405902, ������MMSͬʱ���е�ʱ��,MMSʧ��
  6.��    ��   : 2016��1��20��
    ��    ��   : c00318887
    �޸�����   : DTS2015123110917: usim����GSM����2G��Ȩ��csfb��3G�¼�Ȩ����
*****************************************************************************/
NAS_MSG_STRU *Gmm_ServiceRequestMsgMake_ForData(
    VOS_UINT16                          usUplinkDataStatus,
    VOS_UINT16                          usPdpContextStatus
)
{
    NAS_MSG_FOR_PCLINT_STRU            *ptrNasMsg;
    NAS_MSG_STRU                       *pNasMsg;
    VOS_UINT8                           ucTotalLen = GMM_MSG_LEN_SERVICE_REQUEST;       /* ���нӿ���Ϣ�ĳ���                       */
    VOS_UINT8                           ucServiceType;                                  /* ��ʱ����                                 */
    VOS_UINT8                           i;                                              /* ѭ�����Ʊ���                             */
    VOS_INT8                            cVersion;

    VOS_UINT32                          ulPdpCtxStatus;
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx;

    pstPsBearerCtx = NAS_MML_GetPsBearerCtx();

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

    /* �̶�IE: PDP context status IE */
    ucTotalLen += 4;

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    if (cVersion >= PS_PTL_VER_R7)
    {
        /* ��ѡIE: Uplink data status IE */
        ucTotalLen += 4;
    }
    #endif
    pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc((sizeof(NAS_MSG_STRU)
                                              + ucTotalLen) - 4);                 /* �����ڴ�ռ�                             */
    if (VOS_NULL_PTR == pNasMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ServiceRequestMsgMake_ForData:WARNING: Alloc memory fail.");
        return pNasMsg;
    }

    ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;

    ptrNasMsg->ulNasMsgSize = ucTotalLen;
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;                                         /* GMM_PD_GMMΪ��0x0080                     */
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_SERVICE_REQUEST;                            /* GMM_MSG_SERVICE_REQUESTΪ��12            */

    /* �õ�service ��type */
    if (GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
    {                                                                             /* ��ǰ���е�specific������GMM_SERVICE_REQU *
                                                                                 * EST_SIGNALLING                           */
        ucServiceType = GMM_SERVICE_TYPE_SIGNALLING;
    }
    else if (GMM_SERVICE_REQUEST_PAGING_RSP == g_GmmGlobalCtrl.ucSpecProc)
    {                                                                             /* ��ǰ���е�specific������GMM_SERVICE_REQU *
                                                                                 * EST_PAGING_RSP                           */
        ucServiceType = GMM_SERVICE_TYPE_PAGING_RSP;
    }
    else
    {                                                                             /* ��ǰ���е�specific������service "data"   */
        ucServiceType = GMM_SERVICE_TYPE_DATA;
    }

    
    if (VOS_TRUE == NAS_MML_IsNeedClearPsCksn_UsimDoneGsmPsAuth())
    {
        NAS_MML_SetSimPsSecurityCksn(MM_CKSN_INVALID);

        NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_FALSE);
    }
        
    ptrNasMsg->aucNasMsg[2] =
        (VOS_UINT8)((NAS_MML_GetSimPsSecurityCksn() & 0x07) |
                                        ((ucServiceType & 0x07) << 4));           /* ��ptrNasMsg->aucNasMsg[2]��ֵ            */
    ptrNasMsg->aucNasMsg[3] = 5;                                                  /* ptrNasMsg-> aucNasMsg[3]= P_TMSI�ĳ���   */
    ptrNasMsg->aucNasMsg[4] = GMM_MOBILE_ID_TMSI_PTMSI | 0xF0;                    /* ��ptrNasMsg-> aucNasMsg[4]�������       */

    if (GMM_UEID_P_TMSI
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI))
    {
        Gmm_MemCpy(&ptrNasMsg->aucNasMsg[5],
                   NAS_MML_GetUeIdPtmsi(),
                   NAS_MML_MAX_PTMSI_LEN);                                         /* P_TMSI��ֵ                               */
    }
    else
    {
        for (i=0; i<4; i++)
        {                                                                         /* ��P_TMSI�������                         */
            ptrNasMsg->aucNasMsg[5 + i] = GMM_PTMSI_INVALID;
        }
    }

    ptrNasMsg->aucNasMsg[9]   = GMM_IEI_PDP_CONTEXT_STATUS;
    ptrNasMsg->aucNasMsg[10]  = 2;

    /* TDDģʽ��,��Ҫ����RABM֪ͨ��PDP STATUS�ϱ����� */
    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_GMM_ConvertPdpCtxStatusToNetworkPdpCtxStatus(pstPsBearerCtx, &ulPdpCtxStatus);
        ptrNasMsg->aucNasMsg[11] = (VOS_UINT8)(ulPdpCtxStatus & 0xE0);
        ptrNasMsg->aucNasMsg[12] = (VOS_UINT8)(ulPdpCtxStatus >> NAS_MML_OCTET_MOVE_EIGHT_BITS);
    }
    else
    {
        ptrNasMsg->aucNasMsg[11] = (VOS_UINT8)(usPdpContextStatus & 0xE0);                           /* b4~b0:00000                              */
        ptrNasMsg->aucNasMsg[12] = (VOS_UINT8)((usPdpContextStatus >> 8) & 0xFF);
    }

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    if (cVersion >= PS_PTL_VER_R7)
    {
        ptrNasMsg->aucNasMsg[13] = GMM_IEI_UPLINK_DATA_STATUS;
        ptrNasMsg->aucNasMsg[14] = 2;
        ptrNasMsg->aucNasMsg[15]
            = (VOS_UINT8)(usUplinkDataStatus & 0xE0);                           /* b4~b0:00000                              */
        ptrNasMsg->aucNasMsg[16] = (VOS_UINT8)((usUplinkDataStatus >> 8) & 0xFF);
    }
    #endif

    /* ����Service Request���̣�����GMM��·�ͷſ��Ʊ��� */
    NAS_GMM_UpdateGmmLinkCtrlStru();
    g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_FALSE;
    g_GmmServiceCtrl.ucServiceRequestProc = g_GmmGlobalCtrl.ucSpecProc;

    return (NAS_MSG_STRU *)ptrNasMsg;
}

/*******************************************************************************
  Module   : Gmm_RcvSmsUnitdataReq
  Function : �յ�ԭ��PMMSMS_UNITDATA_REQ�Ĵ���
  Input    : VOS_VOID       *pMsg   ָ��ԭ���ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.03.11  �¹�����  ���ڸ���_GMM_001_03
    2. ��    ��   : 2007��12��11��
       ��    ��   : l65478
       �޸�����   : A32D13796

*******************************************************************************/
VOS_VOID Gmm_RcvSmsUnitdataReq(
                           VOS_VOID    *pMsg                                    /* ��Ϣָ��                                 */
                           )
{
    PMMSMS_UNITDATA_REQ_STRU *pPmmSmsDataReq;                                   /* PMMSMS_UNITDATA_REQ_STRU����ָ��         */

    pPmmSmsDataReq = (PMMSMS_UNITDATA_REQ_STRU *)pMsg;

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmsUnitdataReq:WARNING: PS signalling connection is invalid");
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ֪ͨSMS�������Ӳ�����                    */
        return;
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* �������Ӵ���                             */
        if ((GMM_NULL_PROCEDURE != g_GmmGlobalCtrl.ucSpecProc)
            && (0x40 != (g_GmmGlobalCtrl.ucSpecProc & 0x40))
            && (0x20 != (g_GmmGlobalCtrl.ucSpecProc & 0x20)))
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);                      /* ֪ͨSMS GMM���ڽ�������                  */
        }
        else
        {
            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_LOW,
                                    &pPmmSmsDataReq->SmsMsg);                   /* ���� RRMM_DATA_REQ                       */
        }
    }
    else
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ֪ͨSMS�������Ӳ�����                    */
    }
}

/*******************************************************************************
  Module   : NAS_GMM_BufferSmsEstReq
  Function : �����յ���ԭ��PMMSMS_EST_REQ
  Input    : VOS_VOID       *pMsg   ָ��ԭ���ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ����  2010.01.07  �¹�����
*******************************************************************************/
VOS_VOID NAS_GMM_BufferSmsEstReq(
    VOS_VOID                            *pMsg
)
{
    PMMSMS_EST_REQ_STRU *ptr;                                           /* ������Ϣָ��              */

    if (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                           /* ��¼��SMS�����־  */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        g_GmmGlobalCtrl.ulEstCause = ((PMMSMS_EST_REQ_STRU *)pMsg)->ulEstCause;
    }
    else
    {
        ptr = (PMMSMS_EST_REQ_STRU *)Gmm_MemMalloc(sizeof(PMMSMS_EST_REQ_STRU));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvSmsEstReq:ERROR: Memory is not allocated");
              return;
        }

        Gmm_MemCpy(ptr, pMsg, sizeof(PMMSMS_EST_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)ptr;      /* ������ԭ��                               */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SMS;   /* ��дGMM_MSG_HOLD_STRU���͵ı���          */
    }

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmsEstReq_RegUptNeededNormalSrv
 ��������  : GMM_REGISTERED_UPDATE_NEEDED״̬���������յ�SMS EST REQ�Ĵ���
 �������  : PMMSMS_EST_REQ_STRU                 pstGmmSmsEstReq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��24��
    ��    ��   : w00166186
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmsEstReq_RegUptNeededNormalSrv(
    PMMSMS_EST_REQ_STRU                *pstGmmSmsEstReq
)
{
    NAS_MSG_STRU                       *pstNasMsg = VOS_NULL_PTR;

    g_GmmGlobalCtrl.ulEstCause = pstGmmSmsEstReq->ulEstCause;

    if ((gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
     && (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause))
    {
        return;
    }

    /* �����ǰGMM�ڽ����ӵĹ���������RAI�ı������Ҫ���ͷ����ڽ��������ӣ�
       ��ô�����ڵȴ������������ͷ�ָʾ�Լ������ͷ�ָʾ֮���ϱ���ϵͳ��Ϣ
       �������յ����ϲ�������Ҫ����
       ����T3340�������У���ǰ�������ڲ��ߣ�����SMS���� */
    if (GMM_TRUE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
    {
        NAS_GMM_BufferSmsEstReq(pstGmmSmsEstReq);
        return;
    }

    g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                                       /* ��¼��־���������ӽ����ɹ����SMS����Ӧ  */

    if (GMM_TIMER_T3302_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* T3302��������                            */
        Gmm_TimerPause(GMM_TIMER_T3302);                                        /* ����T3302                                */
    }

    else if (GMM_TIMER_T3311_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* T3311��������                            */
        Gmm_TimerPause(GMM_TIMER_T3311);                                        /* ����T3311                                */
    }
    else
    {
    }

    /* Ǩ��GMM״̬ */
    g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;
    GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

    g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
    g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_SIGNALLING;                /* �洢��ǰ������                           */

    pstNasMsg = Gmm_ServiceRequestMsgMake();                                    /* ����service request��������              */
    Gmm_SndRrmmEstReq(pstGmmSmsEstReq->ulEstCause,
                      GMM_RRC_IDNNS_UNKNOWN,
                      pstNasMsg);                                               /* ����service request(signalling)          */

    Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REQ,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

}
/*******************************************************************************
  Module   : Gmm_RcvSmsEstReq
  Function : �յ�ԭ��PMMSMS_EST_REQ�Ĵ���
  Input    : VOS_VOID       *pMsg   ָ��ԭ���ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.03.11  �¹�����  ���ڸ���_GMM_001_05
    2. ��    ��   : 2008��7��24��
       ��    ��   : luojian 00107747
       �޸�����   : �������ⵥ�ţ�AT2D04627/AT2D04237
    3. ��    ��   : 2008��9��18��
       ��    ��   : ouyangfei 00132663
       �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬��GMM���̽����ٷ���
    4.��    ��   : 2011��3��2��
      ��    ��   : z00161729
      �޸�����   : DTS2010071601574:RAU��������յ�rau accept��Ҫ�ȴ�RABM��WRR�ظ����ٷ���RAU cmp��Ϣ�ڼ�,
                   ����sms����,��RAU�����ٷ���
    5.��    ��   : 2012��2��15��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ����
    6.��    ��   : 2012��5��7��
      ��    ��   : z00161729
      �޸�����   : V7R1C50 GUL BG�����޸�
    7.��    ��   : 2012��12��11��
      ��    ��   : w00176964
      �޸�����   : NAS_MML_GetPsRestrictNormalServiceFlg�޸ĺ�����
    8.��    ��   : 2013��08��16��
      ��    ��   : l65478
      �޸�����   : DTS2013091003969,L handover to W���յ���Ȩ��Ϣû�д���
*******************************************************************************/
VOS_VOID Gmm_RcvSmsEstReq(
                      VOS_VOID    *pMsg                                         /* ��Ϣָ��                                 */
                      )
{
    NAS_MSG_STRU        *pNasMsg = VOS_NULL_PTR;                                /* ����ָ��                                 */
    PMMSMS_EST_REQ_STRU *pPmmSmsEstReq;                                         /* PMMSMS_EST_REQ_STRU����ָ��              */
    PMMSMS_EST_REQ_STRU *ptr;                                                   /* ������Ϣָ��              */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    pPmmSmsEstReq = (PMMSMS_EST_REQ_STRU *)pMsg;

    if (GMM_MSG_HOLD_FOR_SMS
          == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SMS))
    {
                                                                                /* �Ѿ�������SMS��Ϣ����,���ͷ�ԭ���Ļ��� */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;          /* ��������־                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);                   /* ������buffer�����е���Ϣ�ͷ�             */
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)NULL;
    }

    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, begin */
    if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
    /* Modified by w00176964 for V7R1C50_DCM�����ֹС����Ϣ�ϱ�, 2012-12-11, end */
    {
        /* ֪ͨSMS����ʧ�� */
        Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
        return;
    }

    if ((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        && ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
          ||(GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM ==
                                                g_GmmGlobalCtrl.ucState)))
    {                                                                           /* �������Ӵ���,�Ҳ���GMM������                             */
        if ((GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
         || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg))
        {
            NAS_GMM_BufferSmsEstReq(pMsg);
            return;
        }

        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;                                  /* SMS�����Ѵ��������־  */
        Gmm_SndSmsEstCnf();                                                     /* ���� PMMSMS_EST_CNF                      */
    }
    else
    {
        switch (g_GmmGlobalCtrl.ucState)
        {                                                                       /* GMM״̬                                  */
        case GMM_SERVICE_REQUEST_INITIATED:
            g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                               /* ��¼��SMS�����־  */
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            /* ��ǰ��GMM���̣���SMS��־λ�������ԭ� */
            g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                               /* ��¼��SMS�����־  */

            ptr = (PMMSMS_EST_REQ_STRU *)Gmm_MemMalloc(sizeof(PMMSMS_EST_REQ_STRU));
            if (VOS_NULL_PTR == ptr)
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvSmsEstReq:ERROR: Memory is not allocated");
                  return;
            }
            Gmm_MemCpy(ptr, pMsg, sizeof(PMMSMS_EST_REQ_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)ptr;          /* ������ԭ��                               */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SMS;       /* ��дGMM_MSG_HOLD_STRU���͵ı���          */
            break;

        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
            Gmm_RcvCmServReq_RegAtmpToUpdt(pMsg);
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            Gmm_RcvCmServReq_DeregAtmpToAtch(pMsg);
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            g_GmmGlobalCtrl.ulEstCause = pPmmSmsEstReq->ulEstCause;

            if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
             && (gstGmmCasGlobalCtrl.ucLastDataSender != enCurRat)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
             )
            {
                GMM_LOG_INFO("Gmm_RcvSmsEstReq:Inter System change, Exec select RAU.");

                /*GMM_BufferMsgReceive(pMsg);*/
                g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                           /* ��¼��SMS�����־  */
                g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

                g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;

                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                return;
            }
            /* �����ǰGMM�ڽ����ӵĹ���������RAI�ı������Ҫ���ͷ����ڽ��������ӣ�
               ��ô�����ڵȴ������������ͷ�ָʾ�Լ������ͷ�ָʾ֮���ϱ���ϵͳ��Ϣ
               �������յ����ϲ�������Ҫ����
               ����T3340�������У���ǰ�������ڲ��ߣ�����SMS���� */

            if (GMM_TRUE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
            {
                NAS_GMM_BufferSmsEstReq(pMsg);
                return;
            }

            g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                               /* ��¼��־���������ӽ����ɹ����SMS����Ӧ  */
            if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* T3302��������                            */
                Gmm_TimerPause(GMM_TIMER_T3302);                                /* ����T3302                                */
            }

            else if (GMM_TIMER_T3311_FLG
                == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))

            {                                                                   /* T3311��������                            */
                Gmm_TimerPause(GMM_TIMER_T3311);                                /* ����T3311                                */
            }
            else
            {
            }
            g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

            GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmsEstReq:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

            g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

            g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_SIGNALLING;        /* �洢��ǰ������                           */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmsEstReq:INFO: SR(signaling) procedure started");

            pNasMsg = Gmm_ServiceRequestMsgMake();                              /* ����service request��������              */

            Gmm_SndRrmmEstReq(pPmmSmsEstReq->ulEstCause,
                              GMM_RRC_IDNNS_UNKNOWN,
                              pNasMsg);                                         /* ����service request(signalling)          */

            Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_DATA_SERVICE_REQ,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
            break;
        case GMM_REGISTERED_UPDATE_NEEDED:
            if (MM_COM_SRVST_NORMAL_SERVICE == NAS_GMM_GetRegUptNeededPsSrvStatus())
            {
                /* �������� */
                NAS_GMM_RcvSmsEstReq_RegUptNeededNormalSrv(pPmmSmsEstReq);
            }
            else
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
            }
            break;

        /* ������������ָ�������������û����Ͷ��ţ�GMM�����棬�ظ�error ind������ϣ������������ط������ٴδ�������*/
        case GMM_REGISTERED_PLMN_SEARCH:
            Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
            break;

        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_GMM_RcvSmsEstReq_SuspendWaitForSysinfo(pMsg);
            break;

        default:
            Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmsEstReq:WARNING: Receive SMS Request in a not suitable state");
            break;
        }
    }
    return;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertSmsSessionTypeToRrc
 ��������  : ��gmm��sms�ӿ��е�session typeת��Ϊgmm��gu������session type
 �������  : enGmmSmsSessionType - gmm��sms�ӿ��е�session type
 �������  : pucRrcSessionType   - gmm��gu������session type
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_ConvertSmsSessionTypeToRrc(
    GMMSMS_SESSION_TYPE_ENUM_UINT8      enGmmSmsSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *pucRrcSessionType
)
{
    switch (enGmmSmsSessionType)
    {
        case GMMSMS_SESSION_TYPE_MO_SMS:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_MO_SMS;
            break;

        case GMMSMS_SESSION_TYPE_MT_SMS:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_MT_SMS;
            break;

        default:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }
    return;
}
#endif 

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmsBeginSessionNotify_PreProc
 ��������  : �յ�sms��begin session��Ϣ�Ĵ���
 �������  : pstBeginSessionMsg  - �յ�sms begin session��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��09��23��
    ��    ��   : c00318887
    �޸�����   : DTS2015082604451:�޸�DSDS��أ�ֹͣ�ͷ�PS��SMS���ӵĶ�ʱ��
*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmsBeginSessionNotify_PreProc(
    GMMSMS_BEGIN_SESSION_NOTIFY_STRU   *pstBeginSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSMS_SESSION_TYPE_BUTT != pstBeginSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmsSessionTypeToRrc(pstBeginSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndBeginSessionNotify(enRrcSessionType);
    }
#endif

    Gmm_TimerStop(GMM_TIMER_DELAY_PS_SMS_CONN_REL);                       

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmsEndSessionNotify_PreProc
 ��������  : �յ�sms��end session��Ϣ�Ĵ���
 �������  : pstEndSessionMsg  - �յ�sms end session��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��09��23��
    ��    ��   : c00318887
    �޸�����   : DTS2015082604451:�޸�DSDS��أ������ͷ�PS��SMS���ӵĶ�ʱ��
*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmsEndSessionNotify_PreProc(
    GMMSMS_END_SESSION_NOTIFY_STRU     *pstEndSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSMS_SESSION_TYPE_BUTT != pstEndSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmsSessionTypeToRrc(pstEndSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndEndSessionNotify(enRrcSessionType);
    }
#endif

    if (VOS_TRUE == NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer())
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_PS_SMS_CONN_REL);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvSmsEstReq_SuspendWaitForSysinfo
 ��������  : ��SUSPEND WAIT FOR SYSINFO״̬���յ�SMS��Ϣ�Ĵ���
 �������  : pMsg        - �յ���Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��26��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��12��25��
    ��    ��   : w00167002
    �޸�����   : DTS2014122201960:��SUSPEND WAIT FOR SYSINFOʱ�������ʱ����
                ���У��������ϵͳ��Ϣ
*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmsEstReq_SuspendWaitForSysinfo(
    VOS_VOID                            *pMsg
)
{
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
        return;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SPEC_PROC_ONGOING);
        return;
    }

    /* �ڴ�G�л���Wʱ,��Ҫ���ȷ���RAU�ָ�PS,Ȼ�������SM��Ϣ */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
    {
        g_GmmServiceCtrl.ucSmsFlg = GMM_TRUE;                           /* ��¼��SMS�����־  */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;


        /* �����ϵͳ��Ϣ��ʱ�������У����·�RAU */
        if (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG == (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcMmlProcStatusQryReq
 ��������  : ����RABM�����󣬲鿴��ǰ�Ƿ���CS���PS����ź�PS��ר�й���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��11��
    ��    ��   : M00217266
    �޸�����   : ��Ӻ������
*****************************************************************************/
VOS_VOID NAS_GMM_RcvRabmMmlProcStatusQryReq(
    struct MsgCB                       *pMsg
)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;
    RABM_GMM_MML_PROC_STATUS_STRU       stMmlProcStatus;
    RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU   *pstQryMsg;

    PS_MEM_SET(&stMmlProcStatus, 0, sizeof(stMmlProcStatus));
    pstQryMsg = (RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU *)pMsg;

    stMmlProcStatus.enOptFlag = pstQryMsg->enOptFlag;

    /* ��ȡ��ǰGMM�Ƿ���ר������ */
    stMmlProcStatus.bitOpGmmSpecificProcedure = NAS_GMM_IsInRegisterProcedure();

    /* ȡ�õ�ǰ��������Ϣ */
    pstConnStatus = NAS_MML_GetConnStatus();
    stMmlProcStatus.bitOpCsSignal = pstConnStatus->ucCsSigConnStatusFlg;

    /* ��ȡ�Ƿ�ǰ����PS����� */
    /* ��ǰGMMû��ά����ǰ�Ƿ���PS�������̵Ĵ�����Ҫ��ά������Ҫ����
       ��Ϣ���̣�SMS�޸ĵ�Ƚ�ɢ������ʱ����ȣ�������ʱ����API����*/
    if (VOS_TRUE == NAS_SMS_IsPsDomainIdle())
    {
        stMmlProcStatus.bitOpPsSmsService = VOS_FALSE;
    }

    /* ���ú���NAS_GMM_SndRabmMmlProcStatusQryCnf�ظ���� */
    NAS_GMM_SndRabmMmlProcStatusQryCnf(&stMmlProcStatus);
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ChangePsSerRejCauseAvoidInvalidSim
 ��������  : service request�ܾ�ԭ��ֵ����Ӧ
 �������  : VOS_UINT8 *pucRcvMsg  ָ��ԭʼ�ܾ�ԭ��ֵ��ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : h00285180
    �޸�����   : �ܾ�ԭ��ֵPhaseII DTS2014110307415
*****************************************************************************/
VOS_VOID NAS_GMM_ChangePsSerRejCauseAvoidInvalidSim(VOS_UINT8 *pucRcvMsg)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* ���Ӳ��Կ����������Կ�ʱ���޸ģ�ֱ�ӷ��� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_ChangeDetachCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    NAS_MML_SetOriginalRejectCause(*pucRcvMsg);
    /* ȡ�õ�ǰפ����PLMN ID */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_GMM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_PS_SER_REJ, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_GMM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_PS_SER_REJ, pucRcvMsg);
    }
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

