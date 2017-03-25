/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmComm.c
  Description   : GMM COMMON PROCEDURE������ش�����Դ�ļ�
  Function List :
    01.   Gmm_Attach_Prepare
    02.   Gmm_Au_MacAutnWrong
    03.   Gmm_AuCntFail
    04.   Gmm_AuthenAndCipherFailureMsgMake
    05.   Gmm_AuthenAndCipherResponseMsgMake
    06.   Gmm_Com_RcvAgentUsimAuthenticationCnf
    07.   Gmm_IdentityResponseMsgMake
    08.   Gmm_PagingInd_common
    09.   Gmm_PtmsiReallocationCompleteMsgMake
    10.   Gmm_RcvAgentUsimAuthenticationCnf
    11.   Gmm_RcvAuthenAndCipherRejectMsg
    12.   Gmm_RcvAuthenAndCipherRequestMsg
    13.   Gmm_RcvGmmInformationMsg
    14.   Gmm_RcvIdentityRequestMsg
    15.   Gmm_RcvPtmsiReallocationCommandMsg
    16.   Gmm_RcvRrmmPagingInd
    17.   Gmm_RcvRrmmPagingInd_DeregInit
    18.   Gmm_RcvRrmmPagingInd_RauInit
    19.   Gmm_RcvRrmmPagingInd_RegNmlServ
    20.   Gmm_RcvRrmmPagingInd_ServReqInit
    21.   Gmm_Start_StopedRetransmissionTimer
    22.   Gmm_Stop_RetransmissionTimer
  History       :
    1.  ��־��  2003.12.05  �¹�����
    2.  s46746 2006-03-08 �������ⵥA32D02368�޸�
    3.  l40632 2006-04-11 �������ⵥA32D03039�޸�
    4.  x51137 2006/4/13 A32D03056
    5.  x51137 2006/4/28 A32D02889
    6.  s46746 2006-05-08 �������ⵥA32D03487�޸�
    7.  ��    ��   : 2006��9��13��
        ��    ��   : liurui id:40632
        �޸�����   : �������ⵥ�ţ�A32D05596
    8.  ��    ��   : 2006��10��8��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥ�ţ�A32D06583

    9. x51137 2006/11/2 A32D06628
   10.��    ��  : 2006��11��25��
      ��    ��  : luojian id:60022475
      �޸�����  : ���ⵥ��:A32D06583
   11.��    ��  : 2007��01��13��
      ��    ��  : s46746
      �޸�����  : �������ⵥ�ţ�A32D08326
   12.��    ��   : 2007��01��16��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D08381
   13.��    ��   : 2007��05��11��
      ��    ��   : luojian id:60022475
      �޸�����   : ���ⵥ��:A32D10713
   14.��    ��   : 2007��06��05��
      ��    ��   : s46746
      �޸�����   : ���ⵥ��:A32D11127,�򿨷���Ȩ����ʱ���ж��Ƿ����ڵȴ����ظ���Ȩ��Ӧ������У�
                   ������ȴ���־��Ҳ���򿨷���Ȩ�������û�У����򿨷��ͼ�Ȩ����
   15.��    ��   : 2007��06��16��
      ��    ��   : luojian id:60022475
      �޸�����   : �������ⵥ�ţ�A32D11635,gas�ϱ�GPRS RESUME FAILUREʱ,��Ȼ֪ͨ
                   RABM �ָ��ɹ�,�������PDP����ʱ,����RAU,��������RAU������ϵ
                   ͳ��ϢָʾRAI�����ı�Ͳ��ٷ���RAU.
   16.��    ��   : 2007��07��27��
      ��    ��   : luojian id:60022475
      �޸�����   : ���ⵥ��:A32D12606,support GMM identity type:TMSI
   17.��    ��   : 2007��09��30��
      ��    ��   : s46746
      �޸�����   : ���ⵥ��:A32D12878,��register״̬֧��PTMSI���ط��䴦��
   18.��    ��   : 2007��10��13��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D13060
   19.��    ��   : 2007��10��29��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D13271
   20.��    ��   : 2007��11��22��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D13475,�޸���ϵͳ�ı��ָ�ɵ�old TLLI�Ϳ���������ԿΪȫ0����
   21.��    ��   : 2007��12��14��
      ��    ��   : s46746
      �޸�����   : ���ⵥA32D13638����֤����RAU֮ǰ�������෢���������ݣ�����RAU���ɹ������ָ���2
   22.��    ��   : 2007��12��18��
      ��    ��   : s46746
      �޸�����   : ���ⵥA32D13913��GMM�ڽ��м�Ȩ�����У����rand��ͬ��Ҳ��Ҫָ
                   ʾ��2�����㷨����Կ
   23.��    ��   : 2007��12��28��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D13954,�޸�GMM��2G3�����л�����Ϣ����
   24.��    ��   : 2008��07��18��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�AT2D04481,����������ͬ��Ȩ���󣬲�Ӧ���ж�
   25.��    ��   : 2008��9��23��
      ��    ��   : o00132663
      �޸�����   : �������ⵥ�ţ�AT2D05839,�������ȫ�ֱ��� ucRlsMsgFlg��״̬GMM_REGISTERED_WAIT_FOR_RAU
   26.��    ��   : 2008��10��15��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�AT2D06216,GMM�������յ�������ͬ��Ȩ����ʱ��
                   ���ظ���һ����Ȩ����GMMû�н���Ȩ������ص������
   27.��    ��   : 2009��02��07��
      ��    ��   : x00115505
      �޸�����   : �������ⵥ�ţ�AT2D06771,2G PS���Ȩ��û�еõ����Ļظ�֮ǰ
                   ���յ�����ͬ���ļ�Ȩ��Ϣ��MSֱ�ӻظ���Ȩ��Ӧ��
   28.��    ��   : 2009��5��8��
      ��    ��   : x00115505
      �޸�����   : AT2D11792,ִ��GCF��������8.2.2.50ʱ����GMM����ʱ����Ӧpaging��Ϣ��������ʧ�ܡ�
   29.��    ��   : 2009��6��30��
      ��    ��   : s46746
      �޸�����   : AT2D12561,3G2����GPRS��δ�������ܣ�NASָ�ɲ�2�����㷨�󣬲�2���������ݽ����˼���
   30.��    ��   : 2009��08��24��
      ��    ��   : x00115505
      �޸�����   : AT2D14023,����GCF����44.2.2.1.9ʧ��
   31.��    ��   : 2010��3��2��
      ��    ��   : o00132663
      �޸�����   : NAS R7Э��������Ŀ��������·�ͷ���ǿ���������
*******************************************************************************/

#include "GmmInc.h"

#include "GmmCasGlobal.h"
#include "GmmCasGsm.h"
#include "GmmCasComm.h"
#include "GmmCasSend.h"
#include "GmmCasMain.h"
#include "GmmMmInterface.h"
#include "NasMmlCtx.h"
#include "NasGmmSndOm.h"

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/
#include "NasUsimmApi.h"
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_COMM_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

/*lint -save -e958 */

/*******************************************************************************
  Module   : Gmm_RcvRrmmPagingInd
  Function : ���յ�RRMM_PAGING_INDԭ���Ĵ���
  Input    : VOS_VOID *pMsg    :RRMM_PAGING_INDԭ���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �°�����
    2.��    ��   : 2012��2��15��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmPagingInd(
                          VOS_VOID *pMsg                                            /* RRMM_PAGING_INDԭ���׵�ַ                */
                          )
{
    RRMM_PAGING_IND_STRU  *pPagingInd;                                          /* ָ��RRMM_PAGING_IND_STRU�ṹ��ָ��       */

    pPagingInd = (RRMM_PAGING_IND_STRU *)pMsg;
    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����GMM��ͬ��״̬��������Ӧ�Ĵ���        */
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
       Gmm_RcvRrmmPagingInd_DeregInit( pPagingInd);
       break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
       Gmm_RcvRrmmPagingInd_RauInit(pPagingInd);
       break;
    case GMM_SERVICE_REQUEST_INITIATED:
       Gmm_RcvRrmmPagingInd_ServReqInit(pPagingInd);
       break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_TC_ACTIVE:
    case GMM_REGISTERED_UPDATE_NEEDED:
       Gmm_RcvRrmmPagingInd_RegNmlServ(pPagingInd);
       break;
    default:
       PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
       break;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_PagingInd_common
  Function : ���յ�RRMM_PAGING_INDԭ����һЩ��������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �°�����
    2.��    ��   : 2012��2��15��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Gmm_PagingInd_common(VOS_VOID)
{
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }
    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);         /* ����״̬��ΪGU2                          */
    Gmm_DelPsLocInfoUpdateUsim();

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* ����״̬�Ĺ�������                       */
    Gmm_SndMmcLocalDetachInd(NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);                    /* ����MMCGMM_LOCAL_DETACH_IND()            */

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);
    }
    else
    {
        if (VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
        {
            Gmm_Attach_Prepare();                                                   /* ȫ�ֱ�������������Ϊattach����׼��     */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                 /* ����attach                               */
        }
        else
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            /* ��MMC����PSע���� */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);
        }
    }
}

/*******************************************************************************
  Module   : Gmm_Attach_Prepare
  Function : ȫ�ֱ�������������Ϊattach����׼��
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.  ��־��    2003.12.08  �°�����
*******************************************************************************/
VOS_VOID Gmm_Attach_Prepare(VOS_VOID)
{
    g_GmmGlobalCtrl.ucSpecProc           = GMM_NULL_PROCEDURE;                  /* ���"��ǰ���е�specific����"             */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Attach_Prepare:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucSpecProcHold       = GMM_NULL_PROCEDURE;                  /* ���"������specific����"                 */
    g_GmmGlobalCtrl.ucSpecProcInCsTrans  = GMM_NULL_PROCEDURE;                  /* ���"CSͨ���н��е�specific����"         */
    g_GmmGlobalCtrl.ucFollowOnFlg        = GMM_FALSE;                           /* ���"�����ӳ�ʹ�ñ�־"                   */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk = 0;                                   /* ��buffer                                 */
    Gmm_TimerStop(GMM_TIMER_ALL);
    g_GmmReqCnfMng.ucCnfMask = 0;                                               /* �ȴ�cnf�ı�־��Ϊ0                       */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmPagingInd_DeregInit
  Function : ��GMM-DEREGISTERED-INITIATED״̬�£��յ�RRMM_PAGING_INDԭ
             ���Ĵ���
  Input    : RRMM_PAGING_IND_STRU  *ptr    :RRMM_PAGING_INDԭ���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �°�����
    2.��    ��   : 2006��12��5��
      ��    ��   : luojian 60022475
      �޸�����   : Maps3000�ӿ��޸�
    3.��    ��   : 2012��2��15��
      ��    ��   : w00166186
      �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmPagingInd_DeregInit(
                                    RRMM_PAGING_IND_STRU  *ptr                  /* RRMM_PAGING_INDԭ���׵�ַ                */
                                    )
{
    RRMM_PAGING_IND_STRU    *pMsg;

    if (RRC_IMSI_GSM_MAP == ptr->ulPagingUeId)
    {                                                                           /* Ѱ��������ΪIMSI                         */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* �����������ڽ�����������                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk    |= GMM_MSG_HOLD_FOR_PAGING; /* ����Ϣ������ı�־                       */
            pMsg = (RRMM_PAGING_IND_STRU *)Gmm_MemMalloc(sizeof(RRMM_PAGING_IND_STRU));
            if (VOS_NULL_PTR == pMsg)
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRrmmPagingInd_DeregInit:ERROR: allocate memory error");
                  return;
            }
            Gmm_MemCpy(pMsg, ptr, sizeof(RRMM_PAGING_IND_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsg;      /* ����RRMM_PAGING _IND�׵�ַ               */
        }
        else
        {                                                                       /* �������û�������һ�û������             */
            if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask
                & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
            {                                                                   /* �ȴ���Ȩ��Ӧ                             */
                Gmm_TimerStop(GMM_TIMER_PROTECT);                               /* ͣ������ʱ��                             */
                g_GmmReqCnfMng.ucCnfMask
                    &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                  /* ���ԭ��ȴ���־                         */
            }
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED); /* ����״̬��ΪGU2                          */
            Gmm_DelPsLocInfoUpdateUsim();
            Gmm_SndMmcLocalDetachInd(NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);

            if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                Gmm_RcvDetachAcceptMsg_DeregInit();
            }
            else
            {
                Gmm_RcvDetachAcceptMsg_RegImsiDtchInit();
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

                if (VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
                {
                    Gmm_Attach_Prepare();                                           /* ȫ�ֱ�������������Ϊattach����׼��     */
                    Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
                }
                else
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
                }
            }
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd_DeregInit:WARNING: NOT RRC_IMSI_GSM_MAP");
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmPagingInd_RauInit
  Function : ��GMM-ROUTING-AREA-UPDATING-INITIATED״̬�£��յ�
             RRMM_PAGING_INDԭ���Ĵ���
  Input    : RRMM_PAGING_IND_STRU *ptr    :RRMM_PAGING_INDԭ���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �°�����
    2.  ��    ��   : 2006��12��5��
        ��    ��   : luojian 60022475
        �޸�����   : Maps3000�ӿ��޸�
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmPagingInd_RauInit(
                                  RRMM_PAGING_IND_STRU *ptr                     /* RRMM_PAGING_INDԭ���׵�ַ                */
                                  )
{
    RRMM_PAGING_IND_STRU    *pMsg;

    if (RRC_IMSI_GSM_MAP == ptr->ulPagingUeId)
    {                                                                           /* Ѱ��������ΪIMSI                         */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* �����������ڽ�����������                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk    |= GMM_MSG_HOLD_FOR_PAGING; /* ����Ϣ������ı�־                       */
            pMsg = (RRMM_PAGING_IND_STRU *)Gmm_MemMalloc(sizeof(RRMM_PAGING_IND_STRU));
            if (VOS_NULL_PTR == pMsg)
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRrmmPagingInd_RauInit:ERROR: Allocate memory error");
                  return;
            }
            Gmm_MemCpy(pMsg, ptr, sizeof(RRMM_PAGING_IND_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsg;            /* ����RRMM_PAGING _IND�׵�ַ              */
        }
        else
        {                                                                       /* �������û�������һ�û������             */
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* ͣT3330                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* ֹͣT3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* ֹͣT3320                                */

            Gmm_ComCnfHandle();
            Gmm_PagingInd_common();
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd_RauInit:WARNING: NOT RRC_IMSI_GSM_MAP");
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmPagingInd_ServReqInit
  Function : ��GMM-SERVICE-REQUEST-INITIATED״̬�£��յ�RRMM_PAGING_IND
             ԭ���Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �°�����
    2.  ��    ��   : 2006��12��5��
        ��    ��   : luojian 60022475
        �޸�����   : Maps3000�ӿ��޸�
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmPagingInd_ServReqInit(
                                     RRMM_PAGING_IND_STRU  *ptr
                                     )
{
    RRMM_PAGING_IND_STRU    *pMsg;

    if (RRC_IMSI_GSM_MAP == ptr->ulPagingUeId)
    {                                                                           /* Ѱ��������ΪIMSI(RRC_IMSI_DS41,RRC��֧�� */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* �����������ڽ�����������                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk    |= GMM_MSG_HOLD_FOR_PAGING; /* ����Ϣ������ı�־                       */
            pMsg = (RRMM_PAGING_IND_STRU *)Gmm_MemMalloc(sizeof(RRMM_PAGING_IND_STRU));
            if (VOS_NULL_PTR == pMsg)
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvRrmmPagingInd_ServReqInit:ERROR: Allocate memory error");
                  return;
            }
            Gmm_MemCpy(pMsg, ptr, sizeof(RRMM_PAGING_IND_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsg;           /* ����RRMM_PAGING _IND�׵�ַ               */
        }
        else
        {                                                                       /* �������û�������һ�û������             */
            Gmm_TimerStop(GMM_TIMER_T3317);                                     /* ͣT3317                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* ֹͣT3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* ֹͣT3320                                */

            Gmm_ComCnfHandle();
            Gmm_PagingInd_common();
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd_ServReqInit:WARNING: NOT RRC_IMSI_GSM_MAP");
    }

    return;
}
/*******************************************************************************
  Module   : Gmm_RcvRrmmPagingInd_RegNmlServ
  Function : ��GMM-REGISTERED.NORMAL-SERVICE״̬�£��յ�RRMM_PAGING_IND
             ԭ���Ĵ���
  Input    : RRMM_PAGING_IND_STRU  *ptr    :RRMM_PAGING_INDԭ���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �°�����
    2. ��־��  2005.02.21  MM_MT_BUG_005��Ӧ
    3.  ��    ��   : 2006��12��5��
        ��    ��   : luojian 60022475
        �޸�����   : Maps3000�ӿ��޸�
    4.  ��    ��   : 2010��11��20��
        ��    ��   : w00166186
        �޸�����   : DTS2010111600353
    5.  ��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmPagingInd_RegNmlServ(
                                     RRMM_PAGING_IND_STRU *ptr                  /* RRMM_PAGING_INDԭ���׵�ַ                */
                                     )
{
    NAS_MSG_STRU *ptrNasMsg;                                                    /* ָ��NAS��Ϣ�ṹ��ָ��                    */
    VOS_UINT8 ucEstCause = (VOS_UINT8)ptr->ulPagingCause;                               /* RRC������ԭ��                            */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;

                               /* ��ʼ��ָ��                               */

    if (RRC_IMSI_GSM_MAP == ptr->ulPagingUeId)
    {                                                                           /* Ѱ��������ΪIMSI                         */
        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* ����������                               */
            g_GmmAttachCtrl.ucPagingWithImsiFlg = GMM_TRUE;                     /* ����������IMSIѰ��������ATTACH         */
        }
        Gmm_PagingInd_common();
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
    }
    else
    {                                                                           /* Ѱ��������ΪTMSI/P_TMSI                  */
        /* psѰ������ʱ����ӦPTMSIѰ�� */
        if (VOS_TRUE == NAS_MML_GetPsRestrictPagingFlg())
        {
            return;
        }

        enRatType   = NAS_MML_GetCurrNetRatType();
        if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
         && (gstGmmCasGlobalCtrl.ucLastDataSender != enRatType)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
        )
        {
            GMM_LOG_INFO("Gmm_RcvRrmmPagingInd_RegNmlServ:Inter System change, Exec select RAU.");
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
            return;
        }

        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* ������                                   */
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

            g_GmmGlobalCtrl.ucSpecProc   = GMM_SERVICE_REQUEST_PAGING_RSP;      /* ���õ�ǰ����                             */

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmPagingInd_RegNmlServ:INFO: Service request(paging response) procedure started");

            g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;             /* ����GMM��״̬                            */

            GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmPagingInd_RegNmlServ:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

            g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
            ptrNasMsg = Gmm_ServiceRequestMsgMake();                            /* ����ServiceRequestMsg make����           */

            switch (ucEstCause)
            {                                                                   /* RRMM_PAGING_IND��RRMM_EST_REQ��causeת�� */
            case RRC_PAGE_CAUSE_TERMINAT_CONVERSAT_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_CONVERSAT_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_STREAM_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_STREAM_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_INTERACT_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_INTERACT_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_BACKGROUND_CALL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_BACKGROUND_CALL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL;
                break;
            case RRC_PAGE_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL:
                ucEstCause = RRC_EST_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL;
                break;
            default:
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd_RegNmlServ:WARNING: RRC establish Cause is UNKNOWN");
                ucEstCause = RRC_EST_CAUSE_TERMINAT_CAUSE_UNKNOWN;
                break;
            }

            Gmm_SndRrmmEstReq(ucEstCause, RRC_IDNNS_LOCAL_TMSI, ptrNasMsg);  /* ����RRMM_EST_REQ                         */

            Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_DATA_SERVICE_REQ,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmPagingInd_RegNmlServ:WARNING: STATUS IS GMM_SERVICE_REQUEST_INITIATED");
        }

    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAgentUsimAuthenticationCnf
  Function : �յ�AGENT_USIM_AUTHENTICATION_CNF��Ĵ���
  Input    : VOS_VOID *pMsg :AGENT_USIM_AUTHENTICATION_CNF_STRUԭ���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.��־��  2003.12.08  �°�����
    2.��    ��  : 2011��03��30��
      ��    ��  : ŷ����
      �޸�����  : DTS2011032802556,�����쳣���������ͼ�Ȩ������Ϣ�����¼�Ȩʧ�ܣ�����Ч��
    3.��    ��  : 2013��11��30��
      ��    ��  : l65478
      �޸�����  : DTS2013121919477,�����յ������������Ȩ��Ϣ,����ѵ�һ����Ϣ����Ӧ��Ϊ�ڶ����������Ӧ,���¼�Ȩʧ��
    4.��    ��  : 2013��7��22��
      ��    ��  : y00245242
      �޸�����  : �����µ�USIM�ӿ�

	5.��    ��  :2014��01��09��
      ��    ��  :l65478
      �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
*******************************************************************************/
VOS_VOID Gmm_RcvAgentUsimAuthenticationCnf(
                                       VOS_VOID *pMsg
                                       )
{
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-22, begin */
    USIMM_AUTHENTICATION_CNF_STRU *ptr;
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-22, end */


/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-22, begin */
    ptr = (USIMM_AUTHENTICATION_CNF_STRU *)pMsg;
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-22, end */

    NAS_GMM_LogAuthInfo((VOS_UINT8)ptr->stCmdResult.ulSendPara, g_GmmAuthenCtrl.ucOpId);

    /* ��ǰ���ڵȴ�����Ϣ,���� */
    if ((VOS_UINT8)ptr->stCmdResult.ulSendPara != g_GmmAuthenCtrl.ucOpId)
    {
        return;
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        != (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* ���ȴ���ԭ��                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAgentUsimAuthenticationCnf:WARNING: USIM_Authentication_cnf is not expected");
        return;
    }
    Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* ͣ����Timer                              */
    g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;         /* ��ȴ���־                               */


    Gmm_Com_RcvAgentUsimAuthenticationCnf(ptr);                                 /* ���ø�ԭ��Ĺ�������                     */

    return;
}

/*******************************************************************************
  Module   : Gmm_Com_RcvAgentUsimAuthenticationCnf
  Function : �յ�AGENT_USIM_AUTHENTICATION_CNF�Ĺ�������
  Input    : AGENT_USIM_AUTHENTICATION_CNF_STRU *ptr
            :AGENT_USIM_AUTHENTICATION_CNF_STRUԭ���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.��־��  2003.12.08  �°�����
    2.��־��  2004.10.23  AGENT�ӿڱ����Ӧ
    3.��־��  2005.02.03  ָ������޸�Ϊ�����ʽ
    4.liurui  2006.01.13  ����GSM��Ȩʧ�ܴ���
    5.��    ��  : 2013��11��15��
      ��    ��  : m00217266
      �޸�����  : sim����Ȩʧ��ԭ���ϱ�
    6.��    ��   : 2013��07��22��
      ��    ��   : y00245242
      �޸�����   : Ϊ����VOLTE�������µ�USIM�ӿ�
*******************************************************************************/
VOS_VOID Gmm_Com_RcvAgentUsimAuthenticationCnf(
            USIMM_AUTHENTICATION_CNF_STRU         *ptr                                /* ԭ��ָ��                                 */
                                           )
{
    VOS_UINT8                           ucCause;
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16   enUsimAuthFailVaule;

    ucCause             = NAS_MML_REG_FAIL_CAUSE_NULL;
    enUsimAuthFailVaule = NAS_MML_SIM_AUTH_FAIL_NULL;

    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-22, begin */
    if ((USIMM_3G_AUTH != ptr->enAuthType)
     && (USIMM_2G_AUTH != ptr->enAuthType))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
               "Gmm_Com_RcvAgentUsimAuthenticationCnf:WARNING: authentication is not expected");
        return;
    }
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-22, end */

    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, begin */
    if (USIMM_AUTH_UMTS_SUCCESS == ptr->enResult)
    {/*UMTS��Ȩ�ɹ�*/
        GMM_CasRcvUsimCnfUmtsSucc(&(ptr->uCnfData.stTELECnf));
    }
    else if(USIMM_AUTH_GSM_SUCCESS == ptr->enResult)
    {/*GSM��Ȩ�ɹ�*/
        GMM_CasRcvUsimCnfGsmSucc(&(ptr->uCnfData.stTELECnf));
    }
    else if ((USIMM_AUTH_MAC_FAILURE == ptr->enResult)
             || (USIMM_AUTH_SYNC_FAILURE == ptr->enResult))
    {/*UMTS��Ȩ:SYNCʧ�ܻ���MACʧ��*/
        GMM_CasRcvUsimCnfFailUmts(&(ptr->uCnfData.stTELECnf), ptr->enResult);
    }
    else if (USIMM_AUTH_UMTS_OTHER_FAILURE == ptr->enResult)
    {/*GSM��Ȩʧ��,��������ԭ��*/
        GMM_CasRcvUsimCnfFailGsm(&(ptr->uCnfData.stTELECnf));
    }
    else
    {
        Gmm_AuCntFail();
    }
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, end */

    switch (ptr->enResult)
    {
    case USIMM_AUTH_MAC_FAILURE:
        ucCause = NAS_OM_MM_CAUSE_MAC_FAILURE;
        break;
    case USIMM_AUTH_SYNC_FAILURE:
        ucCause = NAS_OM_MM_CAUSE_SYNCH_FAILURE;
        break;
    case USIMM_AUTH_UMTS_OTHER_FAILURE:
        ucCause = NAS_OM_MM_CAUSE_AUT_UMTS_OTHER_FAILURE;
        break;
    case USIMM_AUTH_GSM_OTHER_FAILURE:
        ucCause = NAS_OM_MM_CAUSE_AUT_GSM_OTHER_FAILURE;
        break;
    default:
        ucCause = NAS_OM_MM_CAUSE_AUT_UMTS_OTHER_FAILURE;
        break;
    }

    if ((USIMM_AUTH_UMTS_SUCCESS == ptr->enResult)
        || (USIMM_AUTH_GSM_SUCCESS == ptr->enResult))
    {
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_AUTH_AND_CIPHER_SUCC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }
    else
    {
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_AUTH_AND_CIPHER_FAIL,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_AUTH_AND_CIPHER_FAIL_LEN);
        enUsimAuthFailVaule = NAS_GMM_ConvertUsimAuthFailInfo(ptr->enResult);
        NAS_GMM_SndMmcSimAuthFailInfo(enUsimAuthFailVaule);

    }
    return;
}

/*lint -e438 -e830*/

/*******************************************************************************
  Module   : Gmm_RcvPtmsiReallocationCommandMsg
  Function : �յ�P_TMSI reallocation��Ϣ��Ĵ���
  Input    : NAS_MSG_STRU *pMsg :P_TMSI reallocation ��Ϣ�׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.09  �°�����
  2. ��־��  2005.04.07  NAS_IT_BUG_049��Ӧ
  3. x51137 2006/4/28 A32D02889
  2.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  3.��    ��   : 2012��3��3��
    ��    ��   : z00161729
    �޸�����   : V7R1 C50 ֧��ISR�޸�,T3312����ֹͣ��ʱ����֪ͨL
  4.��    ��   : 2013��08��23��
    ��    ��   : f00179208
    �޸�����   : ErrLog&FTM��Ŀ,PTMSI�����ı�ʱ�ϱ���OM
  5.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : PCINT����
  6.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*******************************************************************************/
VOS_VOID Gmm_RcvPtmsiReallocationCommandMsg(
                                        NAS_MSG_FOR_PCLINT_STRU *pMsg
                                        )
{
    VOS_UINT8               *pucMsgTemp;                                            /* ��ʱָ�����                             */
    VOS_UINT8               *pucRaiTemp;
    VOS_UINT8               ucPtmsiSigFlg;
    NAS_MSG_STRU        *pNasMsg;                                               /* ����ָ��NAS��Ϣ��ָ��                    */
    GMM_RAI_STRU        RaiTemp;
    NAS_MSG_STRU        *pGmmStatus;

    NAS_MML_RAI_STRU                       *pstLastSuccRai;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();


    /*if (0x20 != (g_GmmGlobalCtrl.ucState & 0xF0))*/
    if ((0x0 != (g_GmmGlobalCtrl.ucState & 0xF0))
     &&  (0x20 != (g_GmmGlobalCtrl.ucState & 0xF0)))
    {                                                                           /* ��REGISTERED״̬                         */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiReallocationCommandMsg:WARNING: P-TMSI reallocation is not expected");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_MSG_TYPE_NOT_COMPATIBLE);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }
    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_P_TMSI_REALLOCATION_COMMAND)
    {                                                                           /* ������нӿ���Ϣ�ĳ��ȷǷ�               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiReallocationCommandMsg:WARNING: The length of P-TMSI REALLOCATION is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    if ( GMM_FALSE == Gmm_RcvPtmsiRelocCmdIEChk(pMsg) )
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiReallocationCommandMsg:WARNING: The check result of P-TMSI REALLOCATION is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(
            NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    ucPtmsiSigFlg = GMM_FALSE;
    pucMsgTemp = pMsg->aucNasMsg;                                               /* �õ����нӿ���Ϣ�׵�ַ                   */
    pucRaiTemp = pucMsgTemp+8;
    /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
    RaiTemp.Lai.PlmnId.aucMccDigit[0] = (VOS_UINT8)((*pucRaiTemp) & 0x0F);
    RaiTemp.Lai.PlmnId.aucMccDigit[1] = (VOS_UINT8)((*pucRaiTemp) >> 4);
    pucRaiTemp++;

    RaiTemp.Lai.PlmnId.aucMccDigit[2] = (VOS_UINT8)((*pucRaiTemp) & 0x0F);
    RaiTemp.Lai.PlmnId.aucMncDigit[2] = (VOS_UINT8)((*pucRaiTemp) >> 4);
    pucRaiTemp++;

    RaiTemp.Lai.PlmnId.aucMncDigit[0] = (VOS_UINT8)((*pucRaiTemp) & 0x0F);
    RaiTemp.Lai.PlmnId.aucMncDigit[1] = (VOS_UINT8)((*pucRaiTemp) >> 4);
    pucRaiTemp++;

    if (0x0F == RaiTemp.Lai.PlmnId.aucMncDigit[2])
    {
        RaiTemp.Lai.PlmnId.ucMncCnt = 2;
    }
    else
    {
        RaiTemp.Lai.PlmnId.ucMncCnt = 3;
    }

    RaiTemp.Lai.aucLac[0] = *(pucRaiTemp);
    pucRaiTemp++;

    RaiTemp.Lai.aucLac[1] = *(pucRaiTemp);
    pucRaiTemp++;

    RaiTemp.ucRac = *pucRaiTemp;

    /* Modified by z00234330 for PCLINT����, 2014-06-24, end */

    if(GMM_MSG_LEN_P_TMSI_REALLOCATION_COMMAND != pMsg->ulNasMsgSize)
    {
        if((GMM_IEI_P_TMSI_SIGNATURE ==
            *(pucMsgTemp+GMM_MSG_LEN_P_TMSI_REALLOCATION_COMMAND))
            && (pMsg->ulNasMsgSize ==
                        (GMM_MSG_LEN_P_TMSI_REALLOCATION_COMMAND + 4)))
        {
            ucPtmsiSigFlg = GMM_TRUE;
        }
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {/* 2Gģʽ���� */
        pucMsgTemp += 2;
        if (GMM_FALSE == GMM_GetPtmsiFromMsgIe(pucMsgTemp))
        {
            GMM_LOG_WARN("Gmm_RcvPtmsiReallocationCommandMsg:WARNING: Cannot get new ptmsi!");
        }
        pucMsgTemp += 6;
    }
    else if ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {/* 3Gģʽ���� */
        pucMsgTemp +=4;
        NAS_MML_SetUeIdPtmsi(pucMsgTemp);
        pucMsgTemp = pucMsgTemp + NAS_MML_MAX_PTMSI_LEN;
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;              /* ����UE ID���ڱ�־                        */

#if (FEATURE_ON == FEATURE_PTM)
        /* ���̲˵��򿪺�PTMSI�����ı���Ҫ�ϱ���OM */
        NAS_GMM_SndAcpuOmChangePtmsi();
#endif
    }
    else
    {

    }


    pstLastSuccRai->ucRac               = RaiTemp.ucRac;
    pstLastSuccRai->stLai.aucLac[0]     = RaiTemp.Lai.aucLac[0];
    pstLastSuccRai->stLai.aucLac[1]     = RaiTemp.Lai.aucLac[1];
    NAS_GMM_ConvertPlmnIdToMmcFormat(&(RaiTemp.Lai.PlmnId),
         &(pstLastSuccRai->stLai.stPlmnId));


    if (GMM_TRUE == ucPtmsiSigFlg )
    {                                                                           /* ��Ϣ����P-TMSI signature                 */
        pucMsgTemp += 8;                                                        /* ָ��ָ��P-TMSI signature��               */
        Gmm_MemCpy(NAS_MML_GetUeIdPtmsiSignature(),
                   pucMsgTemp,
                   NAS_MML_MAX_PTMSI_SIGNATURE_LEN);                            /* P_TMSI signature��ֵ */
        pucMsgTemp += NAS_MML_MAX_PTMSI_SIGNATURE_LEN;
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI_SIGNATURE;    /* ����UE ID���ڱ�־                        */
    }

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
    }
    else
    {
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
    }

    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                        /* ֪ͨRRC NAS����Ϣ�仯                    */

    /* Gmm_SndPmmAgentProcedureInd(GMM_PROCEDURE_PTMSI_RELOC); */

    pNasMsg = Gmm_PtmsiReallocationCompleteMsgMake();                           /* P-TMSI REALLOCATION COMPLETE��Ϣ������   */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);                       /* ���÷���RRMM_DATA_REQ����                */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        if ( GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg )
        {
            gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

            if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
            {
                gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                Gmm_TimerStop(GMM_TIMER_T3314);
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);

                 NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);

            }
        }
    }
    return;
}
/*lint +e438 +e830*/

/*******************************************************************************
  Module   : Gmm_Auth_Request_Option_Ie_Check
  Function : ��Authentication and Ciphering Request��Ϣ�еĿ�ѡ����м��
  Input    : NAS_MSG_STRU *pMsg
             VOS_UINT8     ucIeOffset
  Output   : ��
  NOTE     : ��
  Return   : GMM_SUCCESS   ���ɹ�
             GMM_FAILURE   ���ʧ��
  History  :
    1.��    �� : 2009��06��10��
      ��    �� : x00115505
      �޸����� : Created
*******************************************************************************/
VOS_UINT8 Gmm_Auth_Request_Option_Ie_Check(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                           VOS_UINT8 **ppRand,
                                                           VOS_UINT8 *pucRandFlag,
                                                           VOS_UINT8 **ppCksn,
                                                           VOS_UINT8 *pucCksnFlag,
                                                           VOS_UINT8 **ppAutn,
                                                           VOS_UINT8 *pucAutnFlag)
{
    VOS_UINT8        ucAddOffset = 0;
    VOS_UINT8       *pucMsgTemp;                                                /* ��ʱָ�����                             */
    NAS_MSG_STRU    *pGmmStatus;

    if (VOS_NULL == pMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Auth_Request_Option_Ie_Check:ERROR: Null Pointer");
        return GMM_FAILURE;
    }

    pucMsgTemp = pMsg->aucNasMsg;                                               /* �õ����нӿ���Ϣ�׵�ַ                   */

    for (; pMsg->ulNasMsgSize > (VOS_UINT32)(4 + ucAddOffset); )
    {
        switch (*(pucMsgTemp + 4 + ucAddOffset))
        {
        case GMM_IEI_AUTHENTICATION_PARAMETER_RAND:
            if ((GMM_TRUE == *pucRandFlag)
                || (((ucAddOffset + 4) + 17) > (VOS_UINT8)pMsg->ulNasMsgSize ))
            {
                ucAddOffset += 17;
                break;
            }
            *pucRandFlag = GMM_TRUE;
            *ppRand = pucMsgTemp + 4 + ucAddOffset;
            ucAddOffset += 17;
            break;
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER0:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER1:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER2:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER3:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER4:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER5:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER6:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER7:
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER0|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER1|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER2|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER3|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER4|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER5|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER6|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
        case GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_NUMBER7|(GMM_IEI_GPRS_CIPHERING_KEY_SEQUENCE_SPARE1):
            if (GMM_TRUE == *pucCksnFlag)
            {
                ucAddOffset += 1;
                break;
            }
            *pucCksnFlag = GMM_TRUE;
            *ppCksn = pucMsgTemp + 4 + ucAddOffset;
            ucAddOffset += 1;
            break;
        case GMM_IEI_AUTHENTICATION_PARAMETER_AUTN:
            if ( (VOS_UINT8)pMsg->ulNasMsgSize < (ucAddOffset + 6) )
            {
                ucAddOffset = (VOS_UINT8)pMsg->ulNasMsgSize;
                break;
            }
            if ((GMM_TRUE == *pucAutnFlag)
                || (((ucAddOffset + 4) + 18) > (VOS_UINT8)pMsg->ulNasMsgSize ))
            {
                ucAddOffset += 18;
                break;
            }
            if (16 != (*(pucMsgTemp + 4 + ucAddOffset + 1)))
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: Semantically incorrect message");
                pGmmStatus = Gmm_GmmStatusMsgMake(
                                  NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

                Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
                return GMM_FAILURE;
            }

            *pucAutnFlag = GMM_TRUE;
            *ppAutn = pucMsgTemp + 4 + ucAddOffset;
            ucAddOffset += 18;
            break;
        default :
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: Conditional IE error");
            ucAddOffset = (VOS_UINT8)pMsg->ulNasMsgSize;
            break;
        }
    }

    return GMM_SUCCESS;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_ForceToStandby
  Function : Gmm_RcvAuthenAndCipherRequestMsg�����Ӷ�: ForceToStandby ����
  Input    : VOS_UINT8 ucForceToStandby
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ����  2009.06.11  �°�����
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_ForceToStandby(
                                      VOS_UINT8 ucForceToStandby
                                      )
{
    if (0 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    else if (1 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_TRUE;
    }

    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg_ForceToStandby:WARNING: AUTHENTICATION AND CIPHER REQUEST is semantically incorrect");
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_No_Rand_Handling
  Function : Gmm_RcvAuthenAndCipherRequestMsg�����Ӷ�: Rand �����ڵĴ���
  Input    : VOS_VOID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ����  2009.06.11  �°�����
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_No_Rand_Handling(VOS_VOID)
{
    NAS_MSG_STRU *pNasMsg = VOS_NULL;                                           /* ����ָ��NAS��Ϣ��ָ��                    */

    pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
                                    GMM_AUTH_AND_CIPH_RES_UNNEEDED);            /* ����Gmm_AuthenAndCipherResponseMsgMake   */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);                      /* ����Gmm_SndRrmmDataReq                   */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComGprsCipherHandle();
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_Umts_Auth_Handling
  Function : Gmm_RcvAuthenAndCipherRequestMsg�����Ӷ�: Umts_Auth�Ĵ���
  Input    : VOS_UINT8  ucCksnFlag,
             VOS_UINT8 *pCksn,
             VOS_UINT8 *pAutn
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.ŷ����  2009.06.11  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��  : 2011��03��30��
    ��    ��  : ŷ����
    �޸�����  : DTS2011032802556,�����쳣���������ͼ�Ȩ������Ϣ�����¼�Ȩʧ�ܣ�����Ч��
  4.��    ��  : 2011��05��13��
    ��    ��  : ŷ����
    �޸�����  : DTS2011051304471,RAU ��Ȩ�����У������·���Ȩ������ڿ��ظ���Ȩ���
                  ǰ������W��G��ѡ�ٻ��ˣ�����פ��WС�������������·���Ȩ��Ϣ��GMMδ��
                  �����ͼ�Ȩ���󣬶����ϵļ�Ȩ����ظ����磬���¼�Ȩʧ�ܣ�����Ч��
 5.��    ��   : 2012��12��25��
   ��    ��   : L65478
   �޸�����   : DTS2012122900226,G�¶�ʱ����ʱ����ʧ�ܴ��������Ƿ��ֹ��ǰС��
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_Umts_Auth_Handling(
                                                  VOS_UINT8  ucCksnFlag,
                                                  VOS_UINT8 *pCksn,
                                                  VOS_UINT8 *pAutn)
{
    NAS_MSG_STRU *pNasMsg = VOS_NULL;                                           /* ����ָ��NAS��Ϣ��ָ��                    */

    if (GMM_TRUE == ucCksnFlag)
    {
        g_GmmAuthenCtrl.ucCksnSav = (VOS_UINT8)((*pCksn) & 0x07);               /* �ݴ�CKSN                                 */
    }

    /* 24.008�涨����3�μ�Ȩʧ�ܲ���ΪMS��Ȩ����ʧ��,���Ե��ϴμ�Ȩû��ʧ��ʱ�����Ȩʧ�ܴ��� */
    if ((GMM_TIMER_T3318_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3318_FLG))
     && (GMM_TIMER_T3320_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3320_FLG)))
    {
        g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;
    }

    if (GMM_FALSE == g_GmmAuthenCtrl.ucResStoredFlg)
    {                                                                           /* ��ʧ���ڴ�Ϊ��                           */
        Gmm_SndAgentUsimAuthenticationReq(*(pAutn+1), (pAutn+1));
        Gmm_TimerStart(GMM_TIMER_PROTECT);
    }
    else
    {                                                                           /* ��ʧ���ڴ�ǿ�                           */
        /* �Ƿ���ϴ�RAND��ͬ */
        if (GMM_TRUE == GMM_IsLastRand())
        {
            /* ��Ϣ�е�RAND = ��ʧ���ڴ��е�RAND���������򿨽��м�Ȩ��ֱ�ӻظ����� */
            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY);

            if (GMM_TRUE == GMM_IsCasGsmMode())
            {
                Gmm_ComGprsCipherHandle();
            }

            pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
                                    GMM_AUTH_AND_CIPH_RES_NEEDED);              /* ����Gmm_AuthenAndCipherResponseMsgMake   */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);               /* ����Gmm_SndRrmmDataReq                   */

            Gmm_Start_StopedRetransmissionTimer();                              /* ���ڱ�ֹͣ��retransmission timer�������� */

            g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;                              /* GMM Authentication attempt counter��0    */
        }
        else
        {
            g_GmmAuthenCtrl.ucResStoredFlg = GMM_FALSE;

            /* ��Ϣ�е�RAND ������ ��ʧ���ڴ��е�RAND�������򿨽��м�Ȩ */
            Gmm_SndAgentUsimAuthenticationReq(*(pAutn+1), (pAutn+1));
            Gmm_TimerStart(GMM_TIMER_PROTECT);
        }
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_Gsm_Auth_Handling
  Function : Gmm_RcvAuthenAndCipherRequestMsg�����Ӷ�: Gsm_Auth�Ĵ���
  Input    : VOS_UINT8  ucCksnFlag,
             VOS_UINT8 *pCksn
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ����  2009.06.11  �°�����
    2.��    ��  : 2011��03��30��
      ��    ��  : ŷ����
      �޸�����  : DTS2011032802556,�����쳣���������ͼ�Ȩ������Ϣ�����¼�Ȩʧ�ܣ�����Ч��
    3.��    ��  : 2011��05��13��
      ��    ��  : ŷ����
      �޸�����  : DTS2011051304471,RAU ��Ȩ�����У������·���Ȩ������ڿ��ظ���Ȩ���
                  ǰ������W��G��ѡ�ٻ��ˣ�����פ��WС�������������·���Ȩ��Ϣ��GMMδ��
                  �����ͼ�Ȩ���󣬶����ϵļ�Ȩ����ظ����磬���¼�Ȩʧ�ܣ�����Ч��
    4.��    ��   : 2012��12��25��
      ��    ��   : L65478
      �޸�����   : DTS2012122900226,G�¶�ʱ����ʱ����ʧ�ܴ��������Ƿ��ֹ��ǰС��
    5.��    ��  : 2012��12��26��
      ��    ��  : ���� id:00214637
      �޸�����  : USIM����ӿں�������Ĵ��� ��Client ID �� PID��ת������
    6.��    ��  : 2013��6��4��
      ��    ��  : w00242748
      �޸�����  : NAS_SndUsimmAuthReq�޸�ΪNAS_USIMMAPI_AuthReq�����߻���ݵ�ǰģʽ�Զ�
                  ����
    7.��    ��  : 2013��11��30��
      ��    ��  : l65478
      �޸�����  : DTS2013121919477,�����յ������������Ȩ��Ϣ,����ѵ�һ����Ϣ����Ӧ��Ϊ�ڶ����������Ӧ,���¼�Ȩʧ��

    8.��    ��  : 2014��1��3��
      ��    ��  : s00261364
      �޸�����  : mmģ��Converity�澯����
    9.��    ��   : 2014��2��19��
      ��    ��   : s00217060
      �޸�����   : coverity����
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_Gsm_Auth_Handling(
                                                  VOS_UINT8  ucCksnFlag,
                                                  VOS_UINT8 *pCksn)
{
    NAS_MSG_STRU *pNasMsg    = VOS_NULL;                                           /* ����ָ��NAS��Ϣ��ָ��                    */
    VOS_UINT8     ucTempOpId = 0;

    if (GMM_TRUE == ucCksnFlag)
    {
        g_GmmAuthenCtrl.ucCksnSav = (VOS_UINT8)((*pCksn) & 0x07);               /* �ݴ�CKSN                                 */
    }

    /* 24.008�涨����3�μ�Ȩʧ�ܲ���ΪMS��Ȩ����ʧ��,���Ե��ϴμ�Ȩû��ʧ��ʱ�����Ȩʧ�ܴ��� */
    if ((GMM_TIMER_T3318_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3318_FLG))
     && (GMM_TIMER_T3320_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3320_FLG)))
    {
        g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;
    }

    if (GMM_FALSE == g_GmmAuthenCtrl.ucResStoredFlg)
    {                                                                           /* ��ʧ���ڴ�Ϊ��                           */

        ucTempOpId = g_GmmAuthenCtrl.ucOpId;

        g_GmmAuthenCtrl.ucOpId = (VOS_UINT8)((ucTempOpId) % 255);
        g_GmmAuthenCtrl.ucOpId++;

        NAS_USIMMAPI_AuthReq(WUEPS_PID_GMM,
                      AUTHENTICATION_REQ_GSM_CHALLENGE,
                      g_GmmAuthenCtrl.aucRandSav,
                      VOS_NULL_PTR,
                      g_GmmAuthenCtrl.ucOpId
                      );


        g_GmmReqCnfMng.ucCnfMask |= GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;

        Gmm_TimerStart(GMM_TIMER_PROTECT);
    }
    else
    {
        /* �Ƿ���ϴ�RAND��ͬ */
        if (GMM_TRUE == GMM_IsLastRand())
        {
            /* ��Ϣ�е�RAND = ��ʧ���ڴ��е�RAND        */
            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY);
            if (GMM_TRUE == GMM_IsCasGsmMode())
            {
                Gmm_ComGprsCipherHandle();
            }
            pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
                                    GMM_AUTH_AND_CIPH_RES_NEEDED );
            Gmm_SndRrmmDataReq( RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg );

            Gmm_Start_StopedRetransmissionTimer();
            g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;
        }
        else
        {
            g_GmmAuthenCtrl.ucResStoredFlg = GMM_FALSE;

            /* Modified by s00217060 for coverity����, 2014-02-17, begin */
            g_GmmAuthenCtrl.ucOpId = (VOS_UINT8)((ucTempOpId) % 255);
            g_GmmAuthenCtrl.ucOpId++;
            /* Modified by s00217060 for coverity����, 2014-02-17, end */

            NAS_USIMMAPI_AuthReq( WUEPS_PID_GMM,
                           AUTHENTICATION_REQ_GSM_CHALLENGE,
                           g_GmmAuthenCtrl.aucRandSav,
                           VOS_NULL_PTR,
                           g_GmmAuthenCtrl.ucOpId);

            g_GmmReqCnfMng.ucCnfMask |= GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
            Gmm_TimerStart(GMM_TIMER_PROTECT);
        }
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_Auth_Fail_Handling
  Function : Gmm_RcvAuthenAndCipherRequestMsg�����Ӷ�: Auth Fail�Ĵ���
  Input    : VOS_UINT8 ucGmmAuthType
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ŷ����  2009.06.11  �°�����
  2.  ��    ��  : 2011��03��30��
      ��    ��  : ŷ����
      �޸�����  : DTS2011032802556,�����쳣���������ͼ�Ȩ������Ϣ�����¼�Ȩʧ�ܣ�����Ч��
  3.  ��    ��   : 2012��8��25��
      ��    ��   : m00217266
      �޸�����   : ɾ��GMM_SaveErrCode�����Gmm_Save_Detach_Cause��
                  ���浼��Attachʧ�ܵ�ԭ��ֵ
  4.  ��    ��  :2014��01��09��
      ��    ��  :l65478
      �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_Auth_Fail_Handling(
                                                  VOS_UINT8 ucGmmAuthType)
{
    NAS_MSG_STRU *pNasMsg;                                                      /* ����ָ��NAS��Ϣ��ָ��                    */

    g_GmmAuthenCtrl.ucAuthenAttmptCnt++;                                /* GMM Authentication attempt counter��1    */
    if (GMM_AUTHEN_ATTEMPT_MAX_CNT == g_GmmAuthenCtrl.ucAuthenAttmptCnt)
    {                                                                   /* Authentication attempt counter�ﵽ���   */
        if ( GMM_AUTH_GSM_AUTH_UNACCEPTABLE == ucGmmAuthType )
        {
            pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE, 0, VOS_NULL_PTR);     /* AUTHENTICATION AND CIPHERING FAILURE���� */
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);                   /* ���÷��ͺ���                             */

            Gmm_TimerStop(GMM_TIMER_T3316);                             /* ֹͣT3316                                */

            /* �����Ȩ���ȫ�ֱ��� */
            g_GmmAuthenCtrl.ucResStoredFlg       = GMM_FALSE;
            g_GmmAuthenCtrl.ucRandStoredFlg      = GMM_FALSE;

            /*�����Ȩʧ�ܵĴ�����*/
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_GSM_AUT_UNACCEPTABLE);
        }

        Gmm_AuCntFail();
    }
    else
    {                                                                   /* Auth attempt counterû�дﵽ���         */
        if (GMM_AUTH_GSM_AUTH_UNACCEPTABLE == ucGmmAuthType)
        {
            Gmm_Au_MacAutnWrong(NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE);
        }
    }

    if (GMM_AUTH_GSM_AUTH_UNACCEPTABLE == ucGmmAuthType)
    {
        NAS_GMM_SndMmcSimAuthFailInfo(NAS_MML_SIM_AUTH_FAIL_GSM_AUT_UNACCEPTABLE);
    }

    return;
}


/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_T3314_Handling
  Function : Gmm_RcvAuthenAndCipherRequestMsg�����Ӷ�: T3314�Ĵ���
  Input    : VOS_VOID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ����  2009.06.11  �°�����
    2.��    ��   : 2012��3��3��
      ��    ��   : z00161729
      �޸�����   : V7R1 C50 ֧��ISR�޸�,T3312����ֹͣ��ʱ����֪ͨL
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_T3314_Handling(VOS_VOID)
{
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        if ( GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg )
        {
            gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

            if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
            {
                gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                Gmm_TimerStop(GMM_TIMER_T3314);

#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);
                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
            }
        }
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsPowerOffTriggeredDetach
 ��������  : �ж��Ƿ���POWER OFF������DETACH����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��
             VOS_FALSE - ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��3��
    ��    ��   : z00359541
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsPowerOffTriggeredDetach(VOS_VOID)
{
    if ((GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_IsPowerOffTriggeredDetach: return True");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedIgnoreAuthenAndCipherReq
 ��������  : �ж��Ƿ���Ҫ����GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��3��
    ��    ��   : z00359541
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedIgnoreAuthenAndCipherReq(VOS_VOID)
{
    /* ��ǰΪ��POWER OFF������DETACH״̬����Ҫ�����Ȩ���� */
    if ((VOS_FALSE == NAS_GMM_IsPowerOffTriggeredDetach())
     && (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedIgnoreAuthenAndCipherReq: Not power off triggered detach and GMM_DEREGISTERED_INITIATED, return False");
        return VOS_FALSE;
    }

    /* ��ǰ״̬Ϊȥ�������ڷ���ע��״̬ */
    if ((GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
     && (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedIgnoreAuthenAndCipherReq: GMM_STATUS_DETACHED and GMM_REGISTERED_INITIATED, return False");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg_Preprocess
  Function : Gmm_RcvAuthenAndCipherRequestMsg�����Ӷ�: ��ϢԤ����
  Input    : NAS_MSG_STRU *pMsg :NAS��Ϣ�׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ����  2009.06.11  �°�����
*******************************************************************************/
VOS_UINT8 Gmm_RcvAuthenAndCipherRequestMsg_Preprocess(
                                                NAS_MSG_FOR_PCLINT_STRU *pMsg
                                                )
{
    NAS_MSG_STRU        *pGmmStatus;

    if (GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_REQUEST > pMsg->ulNasMsgSize)
    {                                                                           /* ������нӿ���Ϣ�ĳ��ȹ���               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: The length of AUTHENTICATION AND CIPHER REQUEST is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return GMM_FAILURE;
    }

    if (VOS_TRUE == NAS_GMM_IsNeedIgnoreAuthenAndCipherReq())
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: The check result of P-TMSI REALLOCATION is invalid AUTHENTICATION AND CIPHER REQUEST is not expected");
        return GMM_FAILURE;
    }

    return GMM_SUCCESS;

}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRequestMsg
  Function : Authentication and ciphering request���մ���
  Input    : NAS_MSG_STRU *pMsg :NAS��Ϣ�׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �°�����
    2. ��־��  2005.03.18  NAS_IT_BUG_007��Ӧ
    3. x51137        2006/4/13 A32D03056
    3. x51137  2006/4/28 A32D02889
    4.��    ��  : 2006��11��25��
      ��    ��  : luojian id:60022475
      �޸�����  : ���ⵥ��:A32D06583
    5.��    ��  : 2007��01��13��
      ��    ��  : s46746
      �޸�����  : �������ⵥ�ţ�A32D08326
    6.��    ��  : 2009��03��18��
      ��    ��  : l65478
      �޸�����  : �������ⵥ�ţ�AT2D08671,����״̬�£�W�����������е�G�������ָ�ʧ�ܣ���ΪGMMû������LL�����㷨
    7.��    ��  : 2011��03��30��
      ��    ��  : ŷ����
      �޸�����  : DTS2011032802556,�����쳣���������ͼ�Ȩ������Ϣ�����¼�Ȩʧ�ܣ�����Ч��
    8.��    ��  : 2013��11��30��
      ��    ��  : l65478
      �޸�����  : DTS2013121919477,�����յ������������Ȩ��Ϣ,����ѵ�һ����Ϣ����Ӧ��Ϊ�ڶ����������Ӧ,���¼�Ȩʧ��
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg(
    NAS_MSG_FOR_PCLINT_STRU            *pMsg
)
{
    VOS_UINT8                           i;
    VOS_UINT8                          *pucMsgTemp;
    VOS_UINT8                           ucRandFlag      = GMM_FALSE;
    VOS_UINT8                           ucAutnFlag      = GMM_FALSE;
    VOS_UINT8                          *pRand           = VOS_NULL_PTR;
    VOS_UINT8                          *pCksn           = VOS_NULL_PTR;
    VOS_UINT8                          *pAutn           = VOS_NULL_PTR;
    NAS_MSG_STRU                       *pGmmStatus      = VOS_NULL_PTR;

    VOS_UINT8                           ucCksnFlag      = GMM_FALSE;
    VOS_UINT8                           ucOptionalIeFlg = GMM_TRUE;

    VOS_UINT8                           ucGmmAuthType;
    VOS_UINT8                           ucForceToStandby;
    VOS_UINT8                           ucResult        = GMM_SUCCESS;

    ucResult = Gmm_RcvAuthenAndCipherRequestMsg_Preprocess(pMsg);
    if (GMM_FAILURE == ucResult)
    {
        return;
    }

    /* �ϱ���Ȩ�¼� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_AUTH_AND_CIPHER_REQ,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    /* ForceStandby��־���� */
    ucForceToStandby = (VOS_UINT8)(pMsg->aucNasMsg[3] & 0x0F);
    Gmm_RcvAuthenAndCipherRequestMsg_ForceToStandby(ucForceToStandby);

    /* ����Ƿ��п�ѡIE */
    if (GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_REQUEST < pMsg->ulNasMsgSize)
    {
        ucOptionalIeFlg = GMM_TRUE;
    }
    else
    {
        ucOptionalIeFlg = GMM_FALSE;
    }

    /* ��ѡIE��Ч�Լ�� */
    pucMsgTemp = pMsg->aucNasMsg;
    if (GMM_TRUE == ucOptionalIeFlg)
    {
        ucResult = Gmm_Auth_Request_Option_Ie_Check(pMsg, &pRand, &ucRandFlag, &pCksn, &ucCksnFlag,
                                               &pAutn, &ucAutnFlag);

        if (GMM_FAILURE == ucResult)
        {
            return;
        }
    }

    /* ����A&C reference number */
    g_GmmAuthenCtrl.ucAcRefNum = (VOS_UINT8)((*(pucMsgTemp+3) & 0xf0) >> 4);        /* �� A&C reference number                  */

    /* ����GPRS�����㷨 */
    gstGmmCasGlobalCtrl.ucGprsCipherAlg = (VOS_UINT8)(*(pucMsgTemp+2) & 0x07);

    NAS_GMM_SndMmcCipherInfoInd();

    if (1 == ((*(pucMsgTemp+2)&0x70)>>4))
    {
        g_GmmAuthenCtrl.ucImeisvFlg = GMM_TRUE;
    }
    else
    {
        g_GmmAuthenCtrl.ucImeisvFlg = GMM_FALSE;
    }

    /* ��Ϣ�в���������:GPRS RAND */
    if ((GMM_FALSE == ucRandFlag) || (VOS_NULL_PTR == pRand))
    {                                                                           /* ��Ϣ�в���������:GPRS RAND               */
        Gmm_RcvAuthenAndCipherRequestMsg_No_Rand_Handling();
    }
    else
    {
        /* ������:GPRS RAND */
        if (VOS_NULL_PTR == pCksn)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: cksn in AUTHENTICATION AND CIPHER REQUEST is expected");
            pGmmStatus = Gmm_GmmStatusMsgMake(
                NAS_MML_REG_FAIL_CAUSE_CONDITIONAL_IE_ERROR);
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
            return;
        }

        /* Խ��IEI�����汾��RAND */
        pRand++;
        for (i=0; i<GMM_MAX_SIZE_RAND; i++)
        {
            g_GmmAuthenCtrl.aucRandSav[i] = *(pRand+i);
        }

        /* ����ڼ�Ȩ�����У��ٴ��յ�����ļ�Ȩ��Ϣ���������� */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {
            if (GMM_TRUE == GMM_IsLastRand())
            {
                /* ��ǰ���ڼ�Ȩ�����У������·����µļ�Ȩ������RAND���ϴε���ͬ�����ٸ���
                   �·��µ����󣬼����ȴ����Ļظ� */
                return;
            }
        }

        /* GSM�£����豣��RES */
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG ==
                (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
            {
                g_GmmAuthenCtrl.ucResStoredFlg = GMM_FALSE;
            }
        }

        /* ��ȡ��Ȩ���ͣ������ò�ͬ�������� */
        ucGmmAuthType = GMM_AuthType(ucAutnFlag);
        if ((GMM_AUTH_UMTS == ucGmmAuthType) && (VOS_NULL_PTR != pAutn))
        {
            /*UMTS��Ȩ*/
            Gmm_RcvAuthenAndCipherRequestMsg_Umts_Auth_Handling(ucCksnFlag, pCksn, pAutn);
            
            NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_FALSE);
            
        }
        else if (GMM_AUTH_GSM == ucGmmAuthType)
        {   /*GSM��Ȩ*/
            Gmm_RcvAuthenAndCipherRequestMsg_Gsm_Auth_Handling(ucCksnFlag, pCksn);

            if (VOS_TRUE == NAS_MML_IsNeedSetUsimDoneGsmAuthFlg())
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:SetUsimDoneGsmPsAuthFlg to true");
            
                NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_TRUE);
            }
        }
        else
        {
            Gmm_RcvAuthenAndCipherRequestMsg_Auth_Fail_Handling(ucGmmAuthType);
        }
    }

    /* ����RAND�����´μ�Ȩ���бȽ� */
    for (i=0; i<GMM_MAX_SIZE_RAND; i++)
    {
        g_GmmAuthenCtrl.aucRand[i] = g_GmmAuthenCtrl.aucRandSav[i];
    }

    Gmm_RcvAuthenAndCipherRequestMsg_T3314_Handling();

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvAuthenAndCipherRejectMsg
  Function : ����Authentication and ciphering reject��Ϣ�Ĵ���
  Input    : NAS_MSG_STRU *pMsg :NAS��Ϣ�׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �°�����
    2.��    ��   : 2007��01��16��
      ��    ��   : s46746
      �޸�����   : �������ⵥ�ţ�A32D08381
    3.��    ��   : 2007��05��11��
      ��    ��   : luojian id:60022475
      �޸�����   : ���ⵥ��:A32D10713
    4.��    ��   : 2007��06��16��
      ��    ��   : luojian id:60022475
      �޸�����   : �������ⵥ�ţ�A32D11635
    5.��    ��   : 2009��03��31��
      ��    ��   : L65478
      �޸�����   : �������ⵥ�ţ�AT2D10529���μ�Ȩʧ�ܺ�û���ͷ�RRC����
    6.��    ��   : 2011��07��13��
      ��    ��   : w00166186
      �޸�����   : V7R1 PHASE II ATTACH/DETACH����
    7.��    ��   : 2011��10��8��
      ��    ��   : s46746
      �޸�����   : V7R1 phase II,��EPLMN��RPLMN�Ƶ�MM/GMMά��
    8.��    ��  : 2012��08��24��
      ��    ��  : m00217266
      �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
    9.��    ��   : 2013��10��05��
      ��    ��   : l65478
      �޸�����   : DTS2013092509860:GPRS detach���̱�BG������ֹ��,GMM���Զ�������ע��
	10.��    ��   : 2014��2��18��
      ��    ��   : l00215384
      �޸�����   : DTS2014021006453��ע��ɹ����Ȩ�ܾ���������
  11. ��    ��   : 2016��3��17��
      ��    ��   : z00359541
      �޸�����   : DTS2016022503901: NV9247����ʱ��VPLMN�¼�Ȩ����Ҳ���Դ˾ܾ���Ϣ
*******************************************************************************/
VOS_VOID Gmm_RcvAuthenAndCipherRejectMsg(
                                     NAS_MSG_FOR_PCLINT_STRU *pMsg
                                     )
{
    NAS_MSG_STRU        *pGmmStatus;
    VOS_UINT8            ucCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU      *pstAuthRejInfo = VOS_NULL_PTR;

    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;

    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_REJECT)
    {                                                                           /* ������нӿ���Ϣ�ĳ��ȷǷ�               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRejectMsg:WARNING: The length of AUTHENTICATION AND CIPHER REJECT is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();

    if (pstAuthRejInfo->ucHplmnPsAuthRejCounter < pstAuthRejInfo->ucMaxAuthRejNo)
    {
        if (VOS_TRUE == pstAuthRejInfo->ucIgnoreAuthRejFlg)
        {
           pstAuthRejInfo->ucHplmnPsAuthRejCounter++;
           NAS_NORMAL_LOG1(WUEPS_PID_GMM, "Gmm_RcvAuthenAndCipherRejectMsg: NV 9247 active, ignore AUTH REJ ", pstAuthRejInfo->ucHplmnPsAuthRejCounter);
           return;
        }
    }

    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

    Gmm_TimerStop(GMM_TIMER_ALL);                                               /* ͣ����Timer,(T3316/3318/3320/3310...)    */
    g_GmmReqCnfMng.ucCnfMask = 0;                                               /* ���ԭ��ȴ���־                         */
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                    /* ����״̬�Ĺ�������                       */

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
        NAS_GMM_SndMmcMmDetachInfo();
    }

    NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);      /* ����״̬��ΪGU2                          */

    /* �����ر�־ */
    NAS_GMM_ClearIMSIOfUeID();

    NAS_GMM_DeleteEPlmnList();

    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {                                                                           /* SMS�ڵȴ���Ӧ                            */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ����PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */

        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    ucCause = NAS_OM_MM_CAUSE_AUT_NETWORK_REJECT;

    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_AUTH_AND_CIPHER_REJ,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    switch (g_GmmGlobalCtrl.ucSpecProc)
    {
    case GMM_SERVICE_REQUEST_PAGING_RSP:
    case GMM_SERVICE_REQUEST_DATA_IDLE:
    case GMM_SERVICE_REQUEST_SIGNALLING:

        /* ��MMC����SERVICE REQUEST��� */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                              NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REJ,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_SERVICE_REJ_LEN);
        break;
    case GMM_ATTACH_COMBINED:
    case GMM_ATTACH_WHILE_IMSI_ATTACHED:
    case GMM_ATTACH_NORMAL:
    case GMM_ATTACH_NORMAL_CS_TRANS:

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_ATTACH_FAIL,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_ATTACH_FAIL_LEN);
        break;
    case GMM_RAU_COMBINED:
    case GMM_RAU_WITH_IMSI_ATTACH:
    case GMM_RAU_NORMAL:
    case GMM_RAU_NORMAL_CS_TRANS:
    case GMM_RAU_NORMAL_CS_UPDATED:

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_RAU_FAIL,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_RAU_FAIL_LEN);
        break;
    default:
        break;
    }

    Gmm_DelPsLocInfoUpdateUsim();
    NAS_GMM_SndMmAuthenticationFailureInd();                                       /* ����MMCGMM_AUTHENTICATON_FAILURE_IND     */

    if (0x10 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* ATTACH����                               */
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ��Ҫ�ϱ���SM                             */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_AUTHENTICATION_REJ);    /* ֪ͨSM GMMע��ʧ��                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* ��ucSmCnfFlg��־                         */
        }

        if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
         && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
    }
    else
    {                                                                           /* ��������                                 */
        if ((GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* "Service type"��"data"                   */
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* ֪ͨRABM���                             */
        }
        else if (0x20 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
        {
            if (GMM_TRUE == GMM_IsCasGsmMode())
            {
                /*==>A32D11635*/
                g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_FALSE;
                /*<==A32D11635*/
                /* GMM_SndLlcResumeReq(); */
            }

            if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
            {
                GMM_RauFailureInterSys();
            }
            else
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
            }
        }
        else
        {
        }
    }

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �����ǰ����                             */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvAuthenAndCipherRejectMsg:INFO: specific procedure ended");

    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* �����������                             */
    Gmm_HoldBufferFree();                                                       /* ���������Ϣ                             */
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvIdentityRequestMsg
  Function : ����Identity Request��Ϣ�Ĵ���
  Input    : NAS_MSG_STRU *pMsg :NAS��Ϣ�׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.09  �°�����
  2. x51137 2006/4/28 A32D02889
  3.��    ��   : 2007��07��27��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D12606
  4.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5.��    ��   : 2012��03��03��
    ��    ��   : l65478
    �޸�����   : DTS2012020106640�ж�ID����ʱӦ����PTMSI������TMSI
  6.��    ��   : 2012��3��3��
    ��    ��   : z00161729
    �޸�����   : V7R1 C50 ֧��ISR�޸�,T3312����ֹͣ��ʱ����֪ͨL
*******************************************************************************/
VOS_VOID Gmm_RcvIdentityRequestMsg(
                               NAS_MSG_FOR_PCLINT_STRU *pMsg
                               )
{
    VOS_UINT8           *pucMsgTemp;                                                /* ��ʱָ�����                             */
    NAS_MSG_STRU        *pNasMsg;                                                   /* ����ָ��NAS��Ϣ��ָ��                    */
    VOS_UINT8            ucMsId;
    NAS_MSG_STRU        *pGmmStatus;
    VOS_UINT8       ucForceToStandby;

    if (GMM_MSG_LEN_IDENTITY_REQUEST > pMsg->ulNasMsgSize)
    {                                                                           /* ������нӿ���Ϣ���ȹ���                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvIdentityRequestMsg:WARNING: Invalid mandatory information");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    if ((GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
        && (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvIdentityRequestMsg:WARNING: IDENTITY REQUEST is unexpected");
        return;
    }
	
	/* according to 24007 11.1.4:	
    *11.1.4 Spare parts
    *In some cases the specification is that which message instances can be accepted by a receiver comprise more 
	*that the legal message instances that can be sent. One example of this is the notion of spare bit. A spare bit 
	*has to send as the value indicated in the specification (typically 0), but can be accepted as a 0 or a 1 by the 
	*receiver without error diagnosis. A spare field is a field composed entirely of spare bits.
	*/

    pucMsgTemp = &(pMsg->aucNasMsg[0]);                                         /* �õ����нӿ���Ϣ�׵�ַ                   */

    /* ==>A32D12606 */
    ucForceToStandby = (VOS_UINT8)((*(pucMsgTemp+2) >> 4) & 0x07);
    /* <==A32D12606 */
    if (1 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_TRUE;
    }
    else if (0 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvIdentityRequestMsg:WARNING: Wrong information of [Force to standby]");
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }
    ucMsId = (VOS_UINT8)((*(pucMsgTemp+2)) & 0x07);
    /* ==>A32D12606 */
    if ((GMM_MOBILE_ID_IMSI != ucMsId)
        && (GMM_MOBILE_ID_IMEI != ucMsId)
        && (GMM_MOBILE_ID_IMEISV != ucMsId)
        && (GMM_MOBILE_ID_TMSI_PTMSI!= ucMsId ))
    {
        ucMsId = GMM_MOBILE_ID_IMSI;                                            /* All other values are interpreted as      *
                                                                                 * IMSI by this version of the protocol.    */
    }

    if ((GMM_MOBILE_ID_IMSI == ucMsId)
        && (GMM_UEID_IMSI != (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_IMSI)))
    {
        ucMsId = GMM_MOBILE_ID_NONE;
    }

    if ((VOS_FALSE  == NAS_MML_IsPtmsiValid())
     && (GMM_MOBILE_ID_TMSI_PTMSI == ucMsId))
    {
        ucMsId = GMM_MOBILE_ID_NONE;
    }

    /* <==A32D12606 */
    pNasMsg = Gmm_IdentityResponseMsgMake(ucMsId);                              /* ����Identity response��make����          */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);                      /* ���÷���RRMM_DATA_REQ����                */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        if ( GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg )
        {
            gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

            if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
            {
                gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                Gmm_TimerStop(GMM_TIMER_T3314);
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);
                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
            }
        }
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvGmmInformationMsg
  Function : ����information��Ϣ��Ĵ���
  Input    : NAS_MSG_STRU *pMsg :NAS��Ϣ�׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �°�����
    2.��    ��   : 2011��10��08��
      ��    ��   : s46746
      �޸�����   : V7R1 phase II�����ȼ�״̬��ʵ��
    3.��    ��   : 2013��5��17��
      ��    ��   : l00167671
      �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*******************************************************************************/
VOS_VOID Gmm_RcvGmmInformationMsg(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg
)
{
    NAS_MM_INFO_IND_STRU                                    stMmInfo;
    VOS_UINT32                                              ulIeOffset = GMM_MSG_LEN_GMM_INFORMATION;
    VOS_UINT32                                              ulRst;
    VOS_UINT8                                               ucNetworkNameFlg;
    NAS_MML_OPERATOR_NAME_INFO_STRU                         stOldOperatorName;
    NAS_MML_OPERATOR_NAME_INFO_STRU                        *pstCurrOperatorName = VOS_NULL_PTR;

    /* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
    NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU                    stNvimOperatorName;
    /* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */

    PS_MEM_SET(&stMmInfo, 0, sizeof(NAS_MM_INFO_IND_STRU));

    ulRst = NAS_GMM_CheckGmmInfoMsg(pMsg);
    if (VOS_ERR == ulRst)
    {
        return;
    }

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();
    PS_MEM_CPY(&stOldOperatorName, pstCurrOperatorName, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU));

    ucNetworkNameFlg = VOS_FALSE;
    for (; (ulIeOffset < pMsg->ulNasMsgSize);)
    {                                                                           /* �洢IE��ƫ����С�ڿտ���Ϣ�ĳ���         */
        switch (pMsg->aucNasMsg[ulIeOffset])
        {                                                                       /* IEI                                      */
            case GMM_IEI_FULL_NAME_FOR_NETWORK:                                 /* Full name for network                    */
                ulRst = NAS_GMM_DecodeFullNameforNetworkIE(pMsg, &ulIeOffset);

                ucNetworkNameFlg = VOS_TRUE;
                break;

            case GMM_IEI_SHORT_NAME_FOR_NETWORK:                                /* Short name for network                   */
                ulRst = NAS_GMM_DecodeShortNameforNetworkIE(pMsg, &ulIeOffset);

                ucNetworkNameFlg = VOS_TRUE;
                break;

            case GMM_IEI_LOCAL_TIME_ZONE:                                       /* Local time zone                          */
                ulRst = NAS_GMM_DecodeLocalTimeZoneIE(pMsg, &ulIeOffset, &stMmInfo);
                break;

            case GMM_IEI_UNIVERSAL_TIME_AND_LOCAL_TIME_ZONE:                    /* Universal time and local time zone       */
                ulRst = NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE(pMsg, &ulIeOffset, &stMmInfo);
                break;

            case GMM_IEI_LSA_IDENTITY:                                          /* LSA Identity                             */
                ulRst = NAS_GMM_DecodeLSAIdentityIE(pMsg, &ulIeOffset, &stMmInfo);
                break;

            case GMM_IEI_NETWORK_DAYLIGHT_SAVING_TIME:                          /* Network Daylight Saving Time             */
                ulRst = NAS_GMM_DecodeDaylightSavingTimeIE(pMsg, &ulIeOffset, &stMmInfo);
                break;

            default:
                NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvGmmInformationMsg:WARNING: unknown IE.");
                ulIeOffset += pMsg->aucNasMsg[ulIeOffset + 1] + 2;
                break;
        }

        if (VOS_ERR == ulRst)
        {
            return;
        }

        /* �����Ϣ���������������֮ǰ��������ݲ�ͬ,��ҪдNV */
        if (0 != VOS_MemCmp(pstCurrOperatorName, &stOldOperatorName, sizeof(NAS_MML_OPERATOR_NAME_INFO_STRU)))
        {
            /* Modified by l00167671 for NV�����Ŀ , 2013-05-17, begin */
            PS_MEM_CPY(&stNvimOperatorName, pstCurrOperatorName, sizeof(stNvimOperatorName));

            if (NV_OK != NV_Write(en_NV_Item_Network_Name_From_MM_Info,
                                  &stNvimOperatorName,
                                  sizeof(stNvimOperatorName)))
            {
                NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvGmmInformationMsg:Write NV fail.");
            }
            /* Modified by l00167671 for NV�����Ŀ , 2013-05-17, end */

        }
    }

    /* GMM INFO�а���������Ϣʱ���ϱ���MMC */
    if ( (0 != stMmInfo.ucIeFlg)
      || (VOS_TRUE == ucNetworkNameFlg))
    {
        Gmm_SndMmcInfoInd(&stMmInfo);
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_PtmsiReallocationCompleteMsgMake
  Function : ��P-TMSI reallocation complete���з�װ
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.��־��  2003.12.09  �°�����
*******************************************************************************/
NAS_MSG_STRU *Gmm_PtmsiReallocationCompleteMsgMake(VOS_VOID)
{
    NAS_MSG_STRU * ptrNasMsg;

    ptrNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));            /* �����ڴ�ռ�                             */
    if (VOS_NULL_PTR == ptrNasMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_PtmsiReallocationCompleteMsgMake:Error: Alloc Memory fail.");
        return ptrNasMsg;
    }
    Gmm_MemSet(ptrNasMsg, 0, sizeof(NAS_MSG_STRU));                             /* ��������ڴ�ռ���0                      */

    ptrNasMsg->ulNasMsgSize = GMM_MSG_LEN_P_TMSI_REALLOCATION_COMPLETE;
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_P_TMSI_REALLOCATION_COMPLETE;

    return ptrNasMsg;
}

/*******************************************************************************
Module   : Gmm_AuthenAndCipherResponseMsgMake
Function : ��AUTHENTICATION AND CIPHERING RESPONSE���з�װ
Input    : VOS_UINT8 ucResFlg :0 ʱ����ʾ����ش�res���ǿ�ʱ����ʾ��ش�res
Output   : ��
NOTE     : ��
Return   : ��
History  :
   1.��־��  2003.12.09  �°�����
  2.��    ��   : 2012��05��25��
    ��    ��   : w00166186
    �޸�����   : DTS2012052108400,IMEI��д����
 3.��    ��   : 2014��6��17��
   ��    ��   : z00234330
   �޸�����   : PCINT����
*******************************************************************************/
NAS_MSG_STRU *Gmm_AuthenAndCipherResponseMsgMake(
                                                 VOS_UINT8 ucResFlg                 /* 0:��ʾ����ش�res;1:��ʾ��ش�res        */
                                                 )
{
    NAS_MSG_FOR_PCLINT_STRU *ptrNasMsg;                                         /* ����ָ��NAS��Ϣ�ṹ���ָ��              */
    NAS_MSG_STRU *pNasMsg;                                                      /* ����ָ��NAS��Ϣ�ṹ���ָ��              */
    VOS_UINT8 ucTotalLen;                                                           /* NAS��Ϣ�ܳ�                              */
    VOS_UINT8 ucTempLen;                                                            /* NAS��Ϣ��ʱ����                          */
    VOS_UINT8 j;                                                                    /* ѭ�����Ʊ���                             */
    VOS_UINT8                           *pucImeisv;

    pucImeisv    = NAS_MML_GetImeisv();

    ucTotalLen = GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_RESPONSE;
    if (GMM_AUTH_AND_CIPH_RES_NEEDED == ucResFlg)
    {                                                                           /* ��ش�res                                */
        if (0 == g_GmmAuthenCtrl.ucResExtLen)
        {                                                                       /* ȫ����RES Extension���ȱ�ʶΪ0           */
            ucTotalLen += 5;
        }
        else
        {                                                                       /* ȫ����RES Extension���ȱ�ʶ��Ϊ0         */
            ucTotalLen += (7 + g_GmmAuthenCtrl.ucResExtLen);
        }

    }
    if (GMM_TRUE == g_GmmAuthenCtrl.ucImeisvFlg)
    {                                                                           /* ȫ�ֱ�����ʾRESPONSE��Ϣ����Ҫ��IMEISV   */
        ucTotalLen += 11;
    }

    if (ucTotalLen < 4)
    {
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));          /* �����ڴ�ռ�                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_AuthenAndCipherResponseMsgMake:Error: Alloc Memory fail.");
            return pNasMsg;
        }
        ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(ptrNasMsg, 0, sizeof(NAS_MSG_STRU));                         /* ��������ڴ�ռ���0                      */
    }
    else
    {
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(
                                    (sizeof(NAS_MSG_STRU) + ucTotalLen) - 4);     /* �����ڴ�ռ�                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_AuthenAndCipherResponseMsgMake:Error: Alloc Memory fail.");
            return pNasMsg;
        }
        ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(ptrNasMsg, 0, ((sizeof(NAS_MSG_STRU) + ucTotalLen) - 4));      /* ��������ڴ�ռ���0                      */
    }

    ptrNasMsg->ulNasMsgSize = ucTotalLen;
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_AUTHENTICATION_AND_CIPHERING_RESPONSE;
    ptrNasMsg->aucNasMsg[2] = (VOS_UINT8)(g_GmmAuthenCtrl.ucAcRefNum & 0x0F);

    ucTempLen = 3;                                                              /* ָ��Authentication Response parameter��  */
    if (GMM_AUTH_AND_CIPH_RES_NEEDED == ucResFlg)
    {
        /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
        /*lint -e961*/
        ptrNasMsg->aucNasMsg[ucTempLen++] =
            GMM_IEI_AUTHENTICATION_PARAMETER_RESPONSE;                          /* ��IEI��ֵ                                */
        /*lint +e961*/
        for (j=0; j<4; j++)
        {                                                                       /* ��дRES                                  */
            ptrNasMsg->aucNasMsg[ucTempLen] = g_GmmAuthenCtrl.aucRes[j];
            ucTempLen++;
        }
        #ifdef GSM_GCF_RS_SIM_STUB
        ucTempLen = ucTempLen - 4;
        ptrNasMsg->aucNasMsg[ucTempLen] = 0x11;
        ucTempLen++;
        ptrNasMsg->aucNasMsg[ucTempLen] = 0x10;
        ucTempLen++;
        ptrNasMsg->aucNasMsg[ucTempLen] = 0x13;
        ucTempLen++;
        ptrNasMsg->aucNasMsg[ucTempLen] = 0x12;
        ucTempLen++;
        #endif
    }

    if (GMM_TRUE == g_GmmAuthenCtrl.ucImeisvFlg)
    {                                                                           /* ȫ�ֱ�����ʾRESPONSE��Ϣ����Ҫ��IMEISV   */
        ptrNasMsg->aucNasMsg[ucTempLen] = GMM_IEI_IMEISV;                     /* ��IEI��ֵ                                */
        ucTempLen++;
        ptrNasMsg->aucNasMsg[ucTempLen] = 9;                                  /* ��length��ֵ                           */
        ucTempLen++;
        ptrNasMsg->aucNasMsg[ucTempLen] = (VOS_UINT8)(GMM_MOBILE_ID_IMEISV        /* b2~b0                                    */
                                            | GMM_EVEN_NUM_OF_ID_DIGITS         /* b3                                       */
                                            | (pucImeisv[0] << 4));          /* b7~b4                                    */
        ucTempLen++;
        for (j=0; j<7; j++ )
        {
            ptrNasMsg->aucNasMsg[ucTempLen] =
                (VOS_UINT8)((pucImeisv[1 + (2*j)] & 0x0F)
                | (pucImeisv[2 + (2*j)] << 4));
            ucTempLen++;
        }
        ptrNasMsg->aucNasMsg[ucTempLen] =
            (VOS_UINT8)(pucImeisv[15] | 0xF0);          /* ����ֽڵ�b7~b4:��Ϊ'1111'               */
        ucTempLen++;
    }
    if (GMM_AUTH_AND_CIPH_RES_NEEDED == ucResFlg)
    {
        if (0 != g_GmmAuthenCtrl.ucResExtLen)
        {                                                                       /* ȫ����RES Extension���ȱ�ʶ"��Ϊ0        */
            ptrNasMsg->aucNasMsg[ucTempLen]
                = GMM_IEI_AUTHENTICATION_RESPONSE_PARAMETER;                    /* ��IEI��ֵΪ29                            */
            ucTempLen++;
            ptrNasMsg->aucNasMsg[ucTempLen]
                = g_GmmAuthenCtrl.ucResExtLen;                                  /* ��length��ֵ                           */
            ucTempLen++;
            for (j=0; j<g_GmmAuthenCtrl.ucResExtLen; j++)
            {                                                                   /* ��дRES extension                        */
                ptrNasMsg->aucNasMsg[ucTempLen]= g_GmmAuthenCtrl.aucResExt[j];
                ucTempLen++;
            }
        }
    }
    /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */

    return (NAS_MSG_STRU *)ptrNasMsg;
}

/*******************************************************************************
  Module   : Gmm_AuthenAndCipherFailureMsgMake
  Function : ��Authentication and Ciphering Failure���з�װ
  Input    : VOS_UINT8  GmmCause :ʧ��ԭ��
             VOS_UINT8  ucFailParaLenFailure :  Parameter�ĳ��ȣ���λΪ�ֽ� ��
                                            0����Failure Paramete��Ч
             VOS_UINT8 *pFailPara : Authentication Failure parameter �׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : NAS_MSG_STRU     *ptrNasMsg:    NAS��Ϣ�׵�ַ
  History  :
    1.��־��  2003.12.09  �°�����
*******************************************************************************/
NAS_MSG_STRU *Gmm_AuthenAndCipherFailureMsgMake(
                                                VOS_UINT8  GmmCause,                /* ʧ��ԭ��                                 */
                                                VOS_UINT8  ucFailParaLen,           /* Parameter�ĳ��ȣ���λΪ�ֽ� ��           */
                                                VOS_UINT8 *pFailPara                /* Authentication Failure parameter �׵�ַ  */
                                                )
{
    NAS_MSG_FOR_PCLINT_STRU *ptrNasMsg;
    NAS_MSG_STRU            *pNasMsg;
    VOS_UINT8     ucTotalLen;                                                       /* ���нӿ���Ϣ�ĳ���                       */
    VOS_UINT8 i;                                                                    /* ѭ�����Ʊ���                             */

    ucTotalLen = GMM_MSG_LEN_AUTHENTICATION_AND_CIPHERING_FAILURE;
    if (NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE == GmmCause )
    {                                                                           /* GmmCauseΪSynch failure                  */
        ucTotalLen += 16;
    }
    if(ucTotalLen < 4)
    {                                                                           /* ���Ȳ���4��ʱ                            */
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));        /* �����ڴ�ռ�                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_AuthenAndCipherFailureMsgMake:Error: Alloc Memory fail.");
            return pNasMsg;
        }
        ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(ptrNasMsg, 0, sizeof(NAS_MSG_STRU));                         /* ��������ڴ�ռ���0                      */
    }
    else
    {
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(
                                    (sizeof(NAS_MSG_STRU) + ucTotalLen) - 4);     /* �����ڴ�ռ�                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_AuthenAndCipherFailureMsgMake:Error: Alloc Memory fail.");
            return pNasMsg;
        }
        ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(ptrNasMsg, 0, ((sizeof(NAS_MSG_STRU) + ucTotalLen) - 4));      /* ��������ڴ�ռ���0                      */
    }

    ptrNasMsg->ulNasMsgSize = ucTotalLen;                                       /* ��дԭ�ﳤ����                           */
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_AUTHENTICATION_AND_CIPHERING_FAILURE;
    ptrNasMsg->aucNasMsg[2] = GmmCause;

    if (NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE == GmmCause )
    {                                                                           /* GmmCauseΪSynch failure                  */
        ptrNasMsg->aucNasMsg[3] = GMM_IEI_AUTHENTICATION_FAILURE_PARAMETER;
        ptrNasMsg->aucNasMsg[4] = 14;
        if ( ucFailParaLen > 14 )
        {
            for ( i = 0; i < 14; i++)
            {
                ptrNasMsg->aucNasMsg[5+i] = *(pFailPara + i);
            }
        }
        else
        {
            for ( i = 0; i < ucFailParaLen; i++)
            {
                ptrNasMsg->aucNasMsg[5+i] = *(pFailPara + i);
            }
            if ( ucFailParaLen < 14 )
            {
                for ( ; i < 14; i++)
                {
                    ptrNasMsg->aucNasMsg[5+i] = 0xFF;
                }
            }
        }
    }

    return (NAS_MSG_STRU *)ptrNasMsg;
}

/*******************************************************************************
  Module   : Gmm_IdentityResponseMsgMake
  Function : ��Identity response���з�װ
  Input    : UNCHAR IdType    :bit  3 2 1
                                    001: IMSI ��������15 digits
                                    010: IMEI ��IMEI��15 digits���
                                    011: IMEISV��IMEISV��16 digits���
                                    100: TMSI,8 digits
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �°�����
  2.��    ��   : 2007��07��27��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D12606
  3.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  4.��    ��   : 2012��03��03��
    ��    ��   : l65478
    �޸�����   : DTS2012020106640�ж�ID����ʱӦ����PTMSI������TMSI
  5.��    ��   : 2012��05��17��
    ��    ��   : l65478
    �޸�����   : DTS2012051700882,IMEI����
*******************************************************************************/
NAS_MSG_STRU *Gmm_IdentityResponseMsgMake(
                                          VOS_UINT8 IdType                          /* ��Identity request Ҫ���ID              */
                                          )
{
    NAS_MSG_FOR_PCLINT_STRU            *ptrNasMsg;
    NAS_MSG_STRU                       *pNasMsg;
    MM_CSPS_INFO_ST                     stCsInfo;
    VOS_UINT8                           ucTotalLen;                                                 /* ������ʱ����                             */
    VOS_UINT8                           i;                                                          /* ѭ�����Ʊ���                             */
    VOS_UINT8                          *pucMmlImsi;
    VOS_UINT8                          *pucImeisv;

    pucImeisv    = NAS_MML_GetImeisv();
    ucTotalLen = 2;                                                             /* ��ʼ����ʱ����                           */

    pucMmlImsi = NAS_MML_GetSimImsi();
    if (GMM_MOBILE_ID_IMSI == IdType)
    {                                                                           /* IdTypeΪIMSI                             */
        ucTotalLen += (pucMmlImsi[0] + 1);
    }

    /* ==>A32D12606 */
    else if(GMM_MOBILE_ID_TMSI_PTMSI == IdType)
    {
        ucTotalLen += 6;
    }
    /* <==A32D12606 */
    else if(GMM_MOBILE_ID_IMEI == IdType)
    {                                                                           /* Identication_TypeOfIDΪIMEI              */
        ucTotalLen += 9;
    }
    else if (GMM_MOBILE_ID_NONE == IdType)
    {
        ucTotalLen += 4;
    }
    else
    {                                                                           /* Identication_TypeOfIDΪIMEISV            */
        ucTotalLen += 10;
    }

    pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(
                                (sizeof(NAS_MSG_STRU) + ucTotalLen) - 4);         /* �����ڴ�ռ�                             */
    if (VOS_NULL_PTR == pNasMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_IdentityResponseMsgMake:Error: Alloc Memory fail.");
        return pNasMsg;
    }

    ptrNasMsg = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
    Gmm_MemSet(ptrNasMsg, 0, ((sizeof(NAS_MSG_STRU) + ucTotalLen) - 4));          /* ��������ڴ�ռ���0                      */

    ptrNasMsg->ulNasMsgSize = ucTotalLen;
    ptrNasMsg->aucNasMsg[0] = GMM_PD_GMM;
    ptrNasMsg->aucNasMsg[1] = GMM_MSG_IDENTITY_RESPONSE;

    if (GMM_MOBILE_ID_IMSI == IdType)                                           /* IdTypeΪIMSI                             */
    {
        Gmm_MemCpy(&ptrNasMsg->aucNasMsg[2],
                   pucMmlImsi,
                   pucMmlImsi[0] + 1);
    }


    if (GMM_MOBILE_ID_IMEI == IdType)
    {                                                                           /* IdTypeΪIMEI                             */
        ptrNasMsg->aucNasMsg[2] = 8;                                            /* ��length��ֵ                           */
        ptrNasMsg->aucNasMsg[3] = (VOS_UINT8)(GMM_MOBILE_ID_IMEI                    /* b2~b0                                    */
                                  | GMM_ODD_NUM_OF_ID_DIGITS                    /* b3                                       */
                                  | (pucImeisv[0] << 4));                    /* b7~b4                                    */
        for (i=0; i<7; i++ )
        {
            ptrNasMsg->aucNasMsg[4 + i] =
                (VOS_UINT8)((pucImeisv[1 + (2*i)] & 0x0F)
                | ((pucImeisv[2 + (2*i)]) << 4));
        }
        ptrNasMsg->aucNasMsg[10] &= 0x0F;                                       /* ����ֽڵ�b7~b4:��Ϊ'0000'               */
    }

    if (GMM_MOBILE_ID_IMEISV == IdType)
    {                                                                           /* IdTypeΪIMEISV                           */
        ptrNasMsg->aucNasMsg[2] = 9;                                            /* ��length��ֵ                           */
        ptrNasMsg->aucNasMsg[3] = (VOS_UINT8)(GMM_MOBILE_ID_IMEISV                  /* b2~b0                                    */
                                  | GMM_EVEN_NUM_OF_ID_DIGITS                   /* b3                                       */
                                  | (pucImeisv[0] << 4));                    /* b7~b4                                    */
        for (i=0; i<7; i++)
        {
            ptrNasMsg->aucNasMsg[4 + i] =
                (VOS_UINT8)((pucImeisv[1 + (2*i)] & 0x0F)
                | (pucImeisv[2 + (2*i)] << 4));
        }
        ptrNasMsg->aucNasMsg[11] =
            (VOS_UINT8)(pucImeisv[15] | 0xF0);          /* ����ֽڵ�b7~b4:��Ϊ'1111'               */

    }
    /* ==>A32D12606 */
    if (GMM_MOBILE_ID_TMSI_PTMSI == IdType)
    {
        PS_MEM_SET(&stCsInfo, 0, sizeof(MM_CSPS_INFO_ST));
        GMM_GetSecurityInfo(&stCsInfo);
        /*MM_GetSecurityInfo(&stCsInfo);
 */
        ptrNasMsg->aucNasMsg[2]   = 5;                                                              /* Length of mobile identity contents       */
        ptrNasMsg->aucNasMsg[3]   = 0xF0;                                                           /* ��4bit��"1111"                           */
        ptrNasMsg->aucNasMsg[3]  |= GMM_MOBILE_ID_TMSI_PTMSI;                                       /* Type of identity                         */

        /* ��дTMSI  */
        ptrNasMsg->aucNasMsg[4]   = stCsInfo.aucPTMSI[0];
        ptrNasMsg->aucNasMsg[5]   = stCsInfo.aucPTMSI[1];
        ptrNasMsg->aucNasMsg[6]   = stCsInfo.aucPTMSI[2];
        ptrNasMsg->aucNasMsg[7]   = stCsInfo.aucPTMSI[3];
    }
    if (GMM_MOBILE_ID_NONE == IdType)
    {                                                                           /* IdTypeΪNONE                             */
        ptrNasMsg->aucNasMsg[2] = 3;                                            /* ��length��ֵ                           */
        ptrNasMsg->aucNasMsg[3] = (VOS_UINT8)(GMM_MOBILE_ID_NONE                /* b2~b0                                    */
                                  | GMM_ODD_NUM_OF_ID_DIGITS);                  /* b3                                       */
    }

    /* <==A32D12606 */
    return (NAS_MSG_STRU *)ptrNasMsg;
}

/*******************************************************************************
  Module   : Gmm_Start_StopedRetransmissionTimer
  Function : ������ڱ�ֹͣ��retransmission timer��������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.��־��  2003.12.11  �°�����
*******************************************************************************/
VOS_VOID Gmm_Start_StopedRetransmissionTimer(VOS_VOID)
{
    if (0x10 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* ��ǰ����Ϊattach,��T3310                 */
        if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3310)))
        {                                                                           /* ��timer�Ѿ�����                          */
            Gmm_TimerStart(GMM_TIMER_T3310);
        }
    }
    else if (0x20 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* ��ǰ����ΪRAU,����T3330                  */
        if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3330)))
        {                                                                           /* ��timer�Ѿ�����                          */
            Gmm_TimerStart(GMM_TIMER_T3330);
        }
    }
    else if (0x30 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* ��ǰ����ΪDETACH,����T3321               */
        if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3321)))
        {                                                                           /* ��timer�Ѿ�����                          */
            Gmm_TimerStart(GMM_TIMER_T3321);
        }
    }
    else if (0x40 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* ��ǰ����ΪSERVICE_REQUEST,����T3317      */
        if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3317)))
        {                                                                           /* ��timer�Ѿ�����                          */
            Gmm_TimerStart(GMM_TIMER_T3317);
        }
    }
    else
    {
    }
}

/*******************************************************************************
  Module   : Gmm_Stop_RetransmissionTimer
  Function : ֹͣ�������е�retransmission timer
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.��־��  2003.12.11  �°�����
*******************************************************************************/
VOS_VOID Gmm_Stop_RetransmissionTimer(VOS_VOID)
{
    if (0x10 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* ��ǰ����Ϊattach,ͣT3310                 */
        Gmm_TimerStop(GMM_TIMER_T3310);
    }
    else if (0x20 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* ��ǰ����ΪRAU,ͣT3330                    */
        Gmm_TimerStop(GMM_TIMER_T3330);
    }
    else if (0x30 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* ��ǰ����ΪDETACH,ͣT3321                 */
        Gmm_TimerStop(GMM_TIMER_T3321);
    }
    else if (0x40 == (g_GmmGlobalCtrl.ucSpecProc & 0xF0))
    {                                                                           /* ��ǰ����ΪSERVICE_REQUEST,ͣT3317        */
        Gmm_TimerStop(GMM_TIMER_T3317);
    }
    else
    {
    }
}

/*******************************************************************************
  Module   : Gmm_AuCntFail
  Function : ��GMM Authentication attempt counter����3ʱ�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.��־��  2003.12.11  �°�����
    2.��    ��   : 2009��03��31��
      ��    ��   : L65478
      �޸�����   : �������ⵥ�ţ�AT2D10529���μ�Ȩʧ�ܺ�û���ͷ�RRC����
    3.��    ��   : 2012��4��20��
      ��    ��   : l00130025
      �޸�����   : DTS2012032004389��Netork����3�α�Ms Auth Rej��T3318/T3320��ʱʱ��û��֪ͨGAS Bar����ǰС��
*******************************************************************************/
VOS_VOID Gmm_AuCntFail(VOS_VOID)
{
    g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;                                      /* GMM Authentication attempt counter��0    */
    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ͣT3318                                  */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ͣT3320                                  */

    NAS_GMM_SndGasGprsAuthFailNotifyReq();

    Gmm_SndRrmmRelReq(RRC_CELL_BARRED);

    Gmm_Start_StopedRetransmissionTimer();                                      /* ���ڱ�ֹͣ��retransmission timer�������� */
}

/*******************************************************************************
  Module   : Gmm_Au_MacAutnWrong
  Function : ��MAC�����AUTN������ʱ�Ĵ���
  Input    : VOS_UINT8  ucWrongCause    ������ԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.��־��  2003.12.11  �°�����
    2.��    ��   : 2006��12��5��
      ��    ��   : luojian 60022475
      �޸�����   : Maps3000�ӿ��޸�
    3.��    ��   : 2009��03��31��
      ��    ��   : L65478
      �޸�����   : �������ⵥ�ţ�AT2D10529���μ�Ȩʧ�ܺ�û���ͷ�RRC����
    4.��    ��   : 2012��4��20��
      ��    ��   : l00130025
      �޸�����   : DTS2012032004389��Netork����3�α�Ms Auth Rej��T3318/T3320��ʱʱ��û��֪ͨGAS Bar����ǰС��
    5.��    ��  :2014��01��09��
      ��    ��  :l65478
      �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
*******************************************************************************/
VOS_VOID Gmm_Au_MacAutnWrong(
                         VOS_UINT8  ucWrongCause                                    /* ����ԭ��                                 */
                         )
{
    NAS_MSG_STRU    *pNasMsg = VOS_NULL_PTR;

    if ((GMM_AUTHEN_REJ_CAUSE_MAC_FAIL == g_GmmAuthenCtrl.ucLastFailCause)
        || (GMM_AUTHEN_REJ_CAUSE_GSM_FAIL == g_GmmAuthenCtrl.ucLastFailCause))
     {                                                                          /* T3318������                              */
        pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(ucWrongCause, 0, VOS_NULL_PTR);     /* AUTHENTICATION AND CIPHERING FAILURE���� */

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);                   /* ���÷��ͺ���                             */

        Gmm_TimerStop(GMM_TIMER_T3316);                                         /* ֹͣT3316                                */

        /* �����Ȩ���ȫ�ֱ��� */
        g_GmmAuthenCtrl.ucResStoredFlg       = GMM_FALSE;
        g_GmmAuthenCtrl.ucRandStoredFlg      = GMM_FALSE;

        g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;                                  /* GMM Authentication attempt counter��0    */
        g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;


        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ͣT3318                                  */

        NAS_GMM_SndGasGprsAuthFailNotifyReq();

        Gmm_SndRrmmRelReq(RRC_CELL_BARRED);

        Gmm_Start_StopedRetransmissionTimer();                                  /* ���ڱ�ֹͣ��retransmission timer�������� */
     }
     else
     {                                                                          /* T3318��������                            */
         if(NAS_MML_REG_FAIL_CAUSE_GSM_AUT_UNACCEPTABLE == ucWrongCause)
         {
             g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_GSM_FAIL;
         }
         else
         {
             g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_MAC_FAIL;
         }
         pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(ucWrongCause, 0, VOS_NULL_PTR);    /* AUTHENTICATION AND CIPHERING FAILURE���� */

         Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);                  /* ���÷��ͺ���                             */
         Gmm_TimerStop(GMM_TIMER_T3320);                                        /* ͣT3320(���������)                      */
         Gmm_TimerStart(GMM_TIMER_T3318);                                       /* ��T3318                                  */
         Gmm_Stop_RetransmissionTimer();                                        /* ֹͣ�������е�retransmission timer       */
     }
}

/*******************************************************************************
Module   : Gmm_RcvPtmsiRelocCmdIEChk
Function : �յ�P_TMSI reallocation��Ϣ�е�TE��Ч�Լ��
Input    : NAS_MSG_STRU *pMsg
Output   : ��
NOTE     : ��
Return   : ��
History  :
    1. ��־��     2005.01.27  �°�����
    2. ��־��  2005.03.26  NAS_IT_BUG_033��Ӧ
    3.��    ��   : 2007��07��27��
      ��    ��   : luojian id:60022475
      �޸�����   : ���ⵥ��:A32D12606
*******************************************************************************/
VOS_UINT8 Gmm_RcvPtmsiRelocCmdIEChk(
                                NAS_MSG_FOR_PCLINT_STRU *pMsg
                                )
{
    VOS_UINT8        *pucMsgTemp;                                               /* ��ʱָ�����                             */
    VOS_UINT8         ucForceToStandby;

    pucMsgTemp = pMsg->aucNasMsg;                                               /* �õ����нӿ���Ϣ�׵�ַ                   */

    /*lint -e961*/
    pucMsgTemp +=2;                                                             /* ָ��ָ��Allocated P-TMSI��               */
    if (5 != *(pucMsgTemp++))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiRelocCmdIEChk:WARNING: The length of P-TMSI REALLOCATION is invalid");
        return GMM_FALSE;
    }
    if (GMM_MOBILE_ID_TMSI_PTMSI != ((*pucMsgTemp++) & 0x07))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiRelocCmdIEChk:WARNING: MS ID in P-TMSI REALLOCATION is not P-TMSI");
        return GMM_FALSE;
    }
    /*lint +e961*/

    ucForceToStandby = (VOS_UINT8)(*(pucMsgTemp + 10) & 0x07);
    if (1 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_TRUE;
    }
    else if (0 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }
    else
    {                                                                           /* force to standby                         */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvPtmsiRelocCmdIEChk:WARNING: IE\" Force To Standby\" of P-TMSI REALLOCATION is invalid");
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    return GMM_TRUE;
}

/*****************************************************************************
 Prototype      :  GMM_GetSecurityInfo
 Description    :  ��ѯGMM�İ�ȫ��������Ϣ����
 Input          :
 Output         : ---
 Return Value   : 1     ���سɹ�
                  0     ����ʧ��
 Calls          : ---
 Called By      :

 History        : ---
  1.Date        : ---
    Author      : ---
    Modification: ---

  2.��    ��   : 2011��7��12��
    ��    ��   : zhoujun 40661
    �޸�����   : �޸�SIM�������ݵ��ж�
  3.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
*****************************************************************************/
VOS_VOID GMM_GetSecurityInfo(MM_CSPS_INFO_ST *pPsInfo)
{

    NAS_MML_SIM_STATUS_STRU             *pstSimStatusInfo;
    VOS_UINT8                           *pucMmlImsi;

    pstSimStatusInfo        = NAS_MML_GetSimStatus();
    if (VOS_NULL_PTR == pPsInfo)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                    "GMM_GetSecurityInfo: ERROR: Para check error!");

        return;
    }

    /* ��ȫ�ֽṹ����Ӧ��Ϣ�������ṹ pCsInfo �� */
    /* ��ʼ���ṹ�� InfoMask ���� */
    pPsInfo->ucInfoMask = 0x0;

    if (VOS_FALSE == pstSimStatusInfo->ucSimPresentStatus) /* �������� */
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_GetSecurityInfo: INFO: SIM is not present!");

        return;
    }

    /* ���� Ck��Ik �� Kc */
    pPsInfo->ucInfoMask |= 0x1F;
    PS_MEM_CPY(pPsInfo->aucCk, NAS_MML_GetSimPsSecurityUmtsCk(), 16);

    PS_MEM_CPY(pPsInfo->aucIk, NAS_MML_GetSimPsSecurityUmtsIk(), 16);

    PS_MEM_CPY(pPsInfo->aucKc, NAS_MML_GetSimPsSecurityGsmKc(), 8);

    /* ��ȡ IMSI,cksn */
    pucMmlImsi = NAS_MML_GetSimImsi();
    PS_MEM_CPY(pPsInfo->aucImsi, &(pucMmlImsi[1]), 8);
    pPsInfo->ucCksn = NAS_MML_GetSimPsSecurityCksn();

    if ( GMM_UEID_P_TMSI & g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask )
    {
        pPsInfo->ucInfoMask |= MM_SECURITY_P_TMSI_MASK;

        Gmm_MemCpy(&pPsInfo->aucPTMSI[0],
                   NAS_MML_GetUeIdPtmsi(),
                   NAS_MML_MAX_PTMSI_LEN);                                         /* P_TMSI��ֵ                               */
    }


    return;
}

/*******************************************************************************
Module   : Gmm_GetCurrCipherInfo
Function : ��õ�ǰ�ļ����Ƿ�������Ϣ
Input    : ��
Output   : ��
NOTE     : ��
Return   : 1 : ��������
           0 : ����û������
History  :
  1. l65478  2009.04.09  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_GetCurrCipherInfo(VOS_VOID)
{
    if(VOS_TRUE == gstGmmCasGlobalCtrl.ucGprsCipher)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*****************************************************************************
 �� �� ��  : GMM_GetTlliInfo
 ��������  : ��ȡ��ǰ��TLLIֵ
 �������  : ��
 �������  : pulNewTlli
             pulOldTlli
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��30��
    ��    ��   : j00174725
    �޸�����   : ���ⵥ�޸�
*******************************************************************************/
VOS_VOID GMM_GetTlliInfo(VOS_UINT32 *pulNewTlli, VOS_UINT32 *pulOldTlli)
{
    VOS_UINT8                          *pucPtmsiAddr        = VOS_NULL_PTR;
    NAS_MML_RAI_STRU                   *pstLastSuccRai      = VOS_NULL_PTR;
    NAS_LMM_GUTI_STRU                  *pstGutiInfo         = VOS_NULL_PTR;
    GMM_RAI_STRU                        stGmmRai;
    NAS_LMM_INFO_STRU                   stLmmInfo;
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];
    VOS_UINT32                          ulGutiValid;
    VOS_UINT32                          ulTLLI;
    VOS_UINT32                          ulGetLteInfoRet;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT8                           ucUeIdMask;

    /* ��ʼ�� */
    ulTLLI = 0;
    PS_MEM_SET(aucPtmsi, 0, sizeof(aucPtmsi));

    ucUeIdMask      = NAS_GMM_GetUeIdMask();
#if (FEATURE_ON == FEATURE_LTE)
    ulGutiValid     = NAS_GMM_GetLteGutiValid();
    enTinType       = NAS_MML_GetTinType();
    ulGetLteInfoRet = NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo );
#else
    ulGutiValid     = VOS_FALSE;
    ulGetLteInfoRet = VOS_FALSE;
#endif

    /* ���PTMSI��Ч�����Ǵ�Lӳ������ģ�������Foreign TLLI */
#if (FEATURE_ON == FEATURE_LTE)
    if ( (VOS_TRUE == ulGutiValid)
      && (VOS_TRUE == ulGetLteInfoRet) )
    {
        pstGutiInfo                         = &(stLmmInfo.u.stGuti);
        aucPtmsi[0]                         = (pstGutiInfo->stMTmsi.ucMTmsi & 0x3f) | 0xc0 ;
        aucPtmsi[1]                         = pstGutiInfo->stMmeCode.ucMmeCode;
        aucPtmsi[2]                         = pstGutiInfo->stMTmsi.ucMTmsiCnt2;
        aucPtmsi[3]                         = pstGutiInfo->stMTmsi.ucMTmsiCnt3;

        if ( ( (0 == (ucUeIdMask & GMM_UEID_P_TMSI))
            && (NAS_MML_TIN_TYPE_INVALID == enTinType) )
          || (NAS_MML_TIN_TYPE_GUTI == enTinType) )
        {
            /* �����µ�TLLIֵ */
            GMM_CharToUlong(&ulTLLI, aucPtmsi);
            GMM_CreateNewTlli(&ulTLLI, GMM_FOREIGN_TLLI);

            *pulNewTlli = ulTLLI;
            *pulOldTlli = gstGmmCasGlobalCtrl.ulOldTLLI;

            return;
        }
    }
#endif

    /* ���PTMSI ��Ч�����������TLLI */
    if (0 == (ucUeIdMask & GMM_UEID_P_TMSI))
    {
         GMM_CreateNewTlli(&ulTLLI, GMM_RANDOM_TLLI);

        *pulNewTlli = ulTLLI;
        *pulOldTlli = 0xffffffff;

        return;
    }

    /* ���PTMSI��Ч�Ҳ��Ǵ�Lӳ������ģ��Ƚϵ�ǰפ����RAI��PSע��ɹ���RAI��
    ��ͬ����local TLLI,��ͬ����foreign TLLI */

    /* ȡ�ô洢PTMSI���ݵĵ�ַ */
    pucPtmsiAddr        = NAS_MML_GetUeIdPtmsi();
    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];
    PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    GMM_CharToUlong(&ulTLLI, aucPtmsi);

    if (VOS_TRUE == Gmm_Compare_Rai(&stGmmRai, &g_GmmGlobalCtrl.SysInfo.Rai))
    {

        GMM_CreateNewTlli(&ulTLLI, GMM_LOCAL_TLLI);
    }
    else
    {
        GMM_CreateNewTlli(&ulTLLI, GMM_FOREIGN_TLLI);
    }

    *pulNewTlli = ulTLLI;
    *pulOldTlli = gstGmmCasGlobalCtrl.ulOldTLLI;

    return;
}


/*******************************************************************************
Module   : Gmm_ClearLlcData
Function : GMM��DETACH��ػ�ʱ����Ҫ���LLC����
Input    : ��
Output   : ��
NOTE     : ��
Return   : ��
History  :
  1.��    ��   : 2009��05��14��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��:AT2D06770
  2.��    ��   : 2009��06��30��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��AT2D12655,�������LLC�������͵Ĵ���
*******************************************************************************/
VOS_VOID Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ENUM_UINT8 ucClearDataType)
{
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        Gmm_SndLlcAbortReq(ucClearDataType);
        GMM_FreeSysTlli();
        Gmm_TimerStop(GMM_TIMER_PROTECT_OLD_TLLI);
        gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;
    }
}

/*******************************************************************************
Module   : NAS_GMM_SuspendLlcForInterSys
Function : GMM��פ��W����Ҫ�����2��������פ��GSM��ָ�
Input    : ��
Output   : ��
NOTE     : ��
Return   : ��
History  :
  1.��    ��   : 2010��07��20��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:DTS2010073001405,G2W��ϵͳ��ѡ�󣬲����2����ȥָ�ɶ��ǹ����2
*******************************************************************************/
VOS_VOID NAS_GMM_SuspendLlcForInterSys()
{
    if ((GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
     && (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause))
    {
        GMM_SndLlcSuspendReq();
        gstGmmCasGlobalCtrl.ucSuspendLlcCause |= GMM_SUSPEND_LLC_FOR_INTER_SYS;

        Gmm_TimerStop(GMM_TIMER_PROTECT_OLD_TLLI);
        gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;
    }
}

/*******************************************************************************
Module   : Gmm_ComGprsCipherHandle
Function : GMM��GPRS�¼��ܵĹ�������
Input    : ��
Output   : ��
NOTE     : ��
Return   : ��
History  :
  1.��    ��   : 2009��06��26��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:AT2D12561
*******************************************************************************/
VOS_VOID Gmm_ComGprsCipherHandle()
{
    if (0 != gstGmmCasGlobalCtrl.ucGprsCipherAlg)
    {
        gstGmmCasGlobalCtrl.ucGprsCipher = VOS_TRUE;
    }
    else
    {
        gstGmmCasGlobalCtrl.ucGprsCipher = VOS_FALSE;
    }

    NAS_GMM_SndMmcCipherInfoInd();

    /* ָ��Kc�ͼ����㷨 */
    GMM_AssignGsmKc();
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_UpdateAttemptCounterForSpecialCause
 ��������  : ���ԭ��ֵ�Ƿ���Ҫ����Attemp Counterֵ
 �������  : VOS_UINT8  ucUpdateAttachCounter :
                            VOS_TRUE: Attach����, VOS_FALSE: RAU����
             VOS_UINT32 ulGmmCause : ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��14��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��11��18��
    ��    ��   : zhoujun /40661
    �޸�����   : ���ⵥDTS2010111601893,�յ��ܾ�ԭ��ֵΪ102-110��
                 ����Ӧ�ú�ԭ��ֵ111�Ĵ���һ��

  3.��    ��   : 2011��2��11��
    ��    ��   : w00176964
    �޸�����   : DTS2012021003156:GMMע�ᱻ��ԭ��ֵΪ4ʱ��������Э�鲻һ�£�����
                 ��Чattach��RAU����
*****************************************************************************/
VOS_VOID NAS_GMM_UpdateAttemptCounterForSpecialCause(
    VOS_UINT8                           ucUpdateAttachCounter,
    VOS_UINT32                          ulGmmCause
)
{
    /* 3GPP 24.008, 4.7.3.1.5 Abnormal cases in the MS
       d)ATTACH REJECT, other causes than those treated in subclause 4.7.3.1.4
         Upon reception of the cause codes # 95, # 96, # 97, # 99 and # 111 the
         MS should set the GPRS attach attempt counter to 5.

       Gmm Combined RAU has similiar handling. */

    /*  3GPP 24.008 10.5.5.14 GMM cause
        Any other value received by the mobile station shall be treated as 0110 1111,
        "Protocol error, unspecified". Any other value received by the network shall
        be treated as 0110 1111, "Protocol error, unspecified".*/

#if (PS_UE_REL_VER >= PS_PTL_VER_R6)
    if ((NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG == ulGmmCause)
     || (NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF      == ulGmmCause)
     || (NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE == ulGmmCause)
     || (NAS_MML_REG_FAIL_CAUSE_IE_NONEXIST_NOTIMPLEMENTED == ulGmmCause)
     /* ����24008Э�飬���Ӷ�GMM��©��ԭ��ֵ���� */
     || (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR        == ulGmmCause)
     || (NAS_MML_REG_FAIL_CAUSE_CS_DOMAIN_NOT_AVAILABLE    == ulGmmCause)
     || (NAS_MML_REG_FAIL_CAUSE_ESM_FAILURE                == ulGmmCause)
     || ((ulGmmCause >= NAS_MML_REG_FAIL_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG )
      && (ulGmmCause <= NAS_MML_REG_FAIL_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE))
     || ((ulGmmCause > NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE )
      && (ulGmmCause <= NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR) ))
    {
        if ( VOS_TRUE == ucUpdateAttachCounter )
        {
            g_GmmAttachCtrl.ucAttachAttmptCnt = 4;
        }
        else
        {
            g_GmmRauCtrl.ucRauAttmptCnt = 4;
        }
    }
#endif

    if (VOS_TRUE == NAS_MML_IsRoamingRejectNoRetryFlgActived((VOS_UINT8)ulGmmCause))
    {
        g_GmmAttachCtrl.ucAttachAttmptCnt = 4;
    }


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_CheckCauseToStartT3340
 ��������  : ���ܾ�ԭ��ֵ���ж��Ƿ���Ҫ����T3340
 �������  : VOS_UINT8 ucCause : ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��15��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_CheckCauseToStartT3340(
    VOS_UINT8                           ucCause
)
{
    /*3GPP 24.008
      4.7.1.9 Release of the PS signalling connection (Iu mode only)
      In Iu mode, to allow the network to release the PS signalling connection
      (see 3GPP TS 25.331 [23c] and 3GPP TS 44.118 [110]) the MS shall start
      the timer T3340 in the following cases:

      a)the MS receives any of the reject cause values #11, #12, #13 or #15;
      */

    if (GMM_FALSE == GMM_IsCasGsmMode())
    {
        if (   (NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW  == ucCause)
            || (NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW    == ucCause)
            || (NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW  == ucCause)
            || (NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL == ucCause))
        {
            Gmm_TimerStart(GMM_TIMER_T3340);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_HandleDelayedEvent
 ��������  : ����follow on�¼����߻�����¼�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��16��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_HandleDelayedEvent( VOS_VOID )
{
    if (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
    {
        /* T3340���������У�����·�ͷź��ٴ�������Ϣ */
        return;
    }

    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
    {
        if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            Gmm_RoutingAreaUpdateHandleFollowOn();
        }

        if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
        {
            Gmm_DealWithBuffAfterProc();
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_AsEstReq
 ��������  : ֪ͨ����㷢��Est_Req
 �������  :  ulOpId       - ����ID
              ucCnDomain   - ��ö��
              ulEstCause   - ����ԭ��ֵ
              pIdnnsInfo   - ��ʶ
              pstPlmnId    - ��ǰ�����
              ulSize       - ��Ϣ��С
              pFisrstMsg   - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��21��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_INT32 NAS_GMM_AsEstReq(
    VOS_UINT32                          ulOpId,
    VOS_UINT8                           ucCnDomain,
    VOS_UINT32                          ulEstCause,
    IDNNS_STRU                          *pIdnnsInfo,
    RRC_PLMN_ID_STRU                    *pstPlmnId,
    VOS_UINT32                          ulSize,
    VOS_INT8                            *pFisrstMsg
)
{
    /* PS��ĺ�������ͳһ��дΪOther */
    return As_RrEstReq(ulOpId,ucCnDomain,ulEstCause,RRC_NAS_CALL_TYPE_OTHER,
                       pIdnnsInfo,pstPlmnId,ulSize,pFisrstMsg);
}

 /*****************************************************************************
 �� �� ��  : NAS_GMM_GetAttemptUpdateRaiInfo
 ��������  : ��ȡATTEMPT UPDATEʱ��RAI��Ϣ
 �������  : ��
 �������  : VOS_VOID
 �� �� ֵ  : NAS_MML_RAI_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
NAS_MML_RAI_STRU *NAS_GMM_GetAttemptUpdateRaiInfo(VOS_VOID)
{
    return &(g_GmmGlobalCtrl.stAttemptToUpdateRai);
}

 /*****************************************************************************
  �� �� ��  : NAS_GMM_SetAttemptUpdateRaiInfo
  ��������  : ����ATTEMPT UPDATEʱ��RAI��Ϣ
  �������  : pstRai - rai��Ϣ
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ      :
   1.��    ��   : 2015��1��14��
     ��    ��   : z00161729
     �޸�����   : AT&T ֧��DAM�����޸�
 *****************************************************************************/
 VOS_VOID NAS_GMM_SetAttemptUpdateRaiInfo(
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo
 )
 {
     g_GmmGlobalCtrl.stAttemptToUpdateRai.stLai = pstCampPlmnInfo->stLai;
     g_GmmGlobalCtrl.stAttemptToUpdateRai.ucRac = pstCampPlmnInfo->ucRac;
     return;
 }

 /*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedUseAttemptUpdateRaiInfo
 ��������  : �ж��Ƿ���Ҫʹ��ATTEMPT UPDATEʱ��RAI��Ϣ
 �������  : pSysinfoRai - ��ǰϵͳ��Ϣ��rai��Ϣ
 �������  : VOS_VOID
 �� �� ֵ  : VOS_TRUE  - ��Ҫʹ��
             VOS_FALSE - ����Ҫʹ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
  2.��    ��   : 2015��3��2��
    ��    ��   : z00359541
    �޸�����   : DTS2016022908722: T3302������ʱ��ʹ��AttemptUpdateRai�뵱ǰRAI�����ж��Ƿ�RAI�ı�
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedUseAttemptUpdateRaiInfo(
     GMM_RAI_STRU                       *pstSysinfoRai,
     GMM_RAI_STRU                       *pstAttemptUpdateRai
)
{
    VOS_UINT32                           ulT3302Status;

    ulT3302Status = NAS_GMM_QryTimerStatus(GMM_TIMER_T3302);

    /* U2,GMM״̬Ϊ������GMM_SUSPENDED_WAIT_FOR_SYSINFO״̬����T3302��ʱ�������У�
      ��ʹ���ϴ�ϵͳ��Ϣ��rai�뵱ǰϵͳ��Ϣ��rai�Ƚ��ж�λ�����Ƿ�ı䣬
      ʹ��g_GmmGlobalCtrl.stAttemptToUpdateLai�뵱ǰϵͳ��Ϣ��rai�Ƚ�λ�����Ƿ�ı�,
      �Է�ֹ����rau */
    if ((NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED == NAS_MML_GetPsUpdateStatus())
     && (VOS_TRUE == ulT3302Status)
     && ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
      || (GMM_DEREGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
      || (GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
      || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_InitRaiInfo
 ��������  : ��ʼ��ATTEMPT UPDATEʱ��RAI��Ϣ
 �������  : pstRai - RAI��Ϣ
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID NAS_GMM_InitRaiInfo(
    NAS_MML_RAI_STRU                   *pstRai
)
{
    pstRai->stLai.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    pstRai->stLai.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    pstRai->stLai.aucLac[0]      = NAS_MML_LAC_LOW_BYTE_INVALID;
    pstRai->stLai.aucLac[1]      = NAS_MML_LAC_HIGH_BYTE_INVALID;
    pstRai->ucRac                = NAS_MML_RAC_INVALID;

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_RetryCurrentProcedureCommonCheck
 ��������  : �Ƿ���Ҫ���·���PS����ͨ�ü�麯��
 �������  : NAS_MM_COM_PROCEDURE_ENUM_UINT8     ucCurrentProc
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_GMM_RetryCurrentProcedureCommonCheck(VOS_VOID)
{
    /* �ط����̣�����Ƿ�������������:
       1. Iu ģʽ
       2. ��ǰ�����뱻�쳣�ͷŵ�����һ��
       3. ��ǰ���������Ѵ��ڵ�RRC�����Ϸ���
       4. ��ǰ����û���յ�Security Mode Command���������Ժ������� NAS����Ϣ*/

    if (   (VOS_FALSE == GMM_IsCasGsmMode())
        && (g_GmmGlobalCtrl.ucSpecProc
                == g_GmmGlobalCtrl.stGmmLinkCtrl.ucCurrentProc)
        && (VOS_TRUE == g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedRrcConn)
        && (VOS_FALSE
                == g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RetryAttachProcedureCheck
 ��������  : ����Ƿ���Ҫ���·���Attach����
 �������  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause         - �ͷ�ԭ��ֵ
             RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus    - ��·״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ��Ҫ���·�������
             VOS_FALSE: ����Ҫ���·�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��30��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_GMM_RetryAttachProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
)
{
    /*24.008, 4.7.3.1.5 Abnormal cases in the MS
      b)    Lower layer failure before the ATTACH ACCEPT or ATTACH REJECT mess-
      age is received
      The procedure shall be aborted and. Tthe MS shall proceed as described
      below, except in the following implementation option cases b.1 and
      b.2.
      b.1)  Release of PS signalling connection in Iu mode before the comple-
      tion of the GPRS attach procedure
      If the release of the PS signalling connection occurs before completion
      of the GPRS attach procedure, then the GPRS attach procedure shall
      be initiated again, if the following conditions apply:
      i)    The original GPRS attach procedure was initiated over an existing
      PS signalling connection; and
      ii)   The GPRS attach procedure was not due to timer T3310 expiry; and
      iii)  No SECURITY MODE COMMAND message and no Non-Access Startum (NAS)
      messages relating to the PS signalling connection (e.g. PS authentica-
      tion procedure, see subclause 4.7.7) were received after the ATTACH
      REQUEST message was transmitted.
      b.2)  RR release in Iu mode (i.e. RRC connection release) with, for
      example, cause "Normal", or "User inactivity" (see 3GPP TS 25.331
      [32c] and 3GPP TS 44.118 [111])
      The GPRS attach procedure shall be initiated again, if the following
      conditions apply:
      i)    The original GPRS attach procedure was initiated over an existing
      RRC connection; and
      ii)   The GPRS attach procedure was not due to timer T3310 expiry; and
      iii)  No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection (e.g. PS authentica-
      tion procedure, see subclause 4.7.7) were received after the ATTACH
      REQUEST message was transmitted.
      NOTE:     The RRC connection release cause that triggers the re-initiation
      of the GPRS attach procedure is implementation specific.*/

    VOS_UINT8                               ucRst;

    ucRst = NAS_GMM_RetryCurrentProcedureCommonCheck();

    if (VOS_TRUE == ucRst)
    {
        if (0 == g_GmmAttachCtrl.ucT3310outCnt)
        {
            if (RRC_RRC_CONN_STATUS_ABSENT == ulRrcConnStatus)
            {
                /* �ͷŵ���RRC���� */
                if ( (RRC_REL_CAUSE_RR_NORM_EVENT    == ulRelCause)
                  || (RRC_REL_CAUSE_RR_USER_INACT    == ulRelCause)
                  || (RRC_REL_CAUSE_CELL_UPDATE_FAIL == ulRelCause)
                  || (RRC_REL_CAUSE_T315_EXPIRED     == ulRelCause) )
                {
                    return VOS_TRUE;
                }
            }
            else
            {
                /* �ͷŵ���PS�������� */
                if (VOS_TRUE
                        == g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn)
                {
                    /* �����������Ѵ��ڵ�PS���������Ϸ���� */
                    return VOS_TRUE;
                }
            }
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RetryDetachProcedureCheck
 ��������  : ����Ƿ���Ҫ���·���Detach����
 �������  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause         - �ͷ�ԭ��ֵ
             RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus    - ��·״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ��Ҫ���·�������
             VOS_FALSE: ����Ҫ���·�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��30��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_GMM_RetryDetachProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
)
{
    /*24.008, 4.7.4.1.4
      b.1)  Release of PS signalling connection before the completion of
      the GPRS detach procedure
      The release of the PS signalling connection before completion of the
      GPRS detach procedure shall result in the GPRS detach procedure being
      initiated again, if the following conditions apply:
      i)    The original GPRS detach procedure was initiated over an existing
      PS signalling connection; and
      ii)   No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection (e.g. PS authentica-
      tion procedure, see subclause 4.7.7) were received after the DETACH
      REQUEST message was transmitted.
      b.2)  RR release in Iu mode (i.e. RRC connection release) with cause
      different than "Directed signalling connection re-establishment",
      for example, "Normal", or"User inactivity" (see 3GPP TS 25.331 [32c]
      and 3GPP TS 44.118 [111])
      The GPRS detach procedure shall be initiated again, if the following
      conditions apply:
      i)    The original GPRS detach procedure was initiated over an exisiting
      RRC connection; and
      ii)   No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection (e.g. PS authentica-
      tion procedure, see subclause 4.7.7) were received after the DETACH
      REQUEST message was transmitted.
      NOTE:     The RRC connection release cause different than "Directed sign-
      alling connection re-establishment" that triggers the re-initiation
      of the GPRS detach procedure is implementation specific.
      b.3)  RR release in Iu mode (i.e. RRC connection release) with cause
      "Directed signalling connection re-establishment" (see 3GPP TS 25.331
      [32c] and 3GPP TS 44.118 [111])
      The routing area updating procedure shall be initiated followed by
      completion of the GPRS detach procedure if the following conditions
      apply:
      i)    The original GPRS detach procedure was not due to SIM removal; and
      ii)   The original GPRS detach procedure was not due to a rerun of the
      procedure due to "Directed signalling connection reestablishment".*/


    VOS_UINT8                               ucRst;

    if (   (GMM_DETACH_COMBINED_POWER_OFF
                == g_GmmGlobalCtrl.stGmmLinkCtrl.ucCurrentProc)
        || (GMM_DETACH_NORMAL_POWER_OFF
                == g_GmmGlobalCtrl.stGmmLinkCtrl.ucCurrentProc))
    {
        return VOS_FALSE;
    }

    ucRst = NAS_GMM_RetryCurrentProcedureCommonCheck();

    if (VOS_TRUE == ucRst)
    {
        if (RRC_RRC_CONN_STATUS_ABSENT == ulRrcConnStatus)
        {
            /* �ͷŵ���RRC���� */
            if ( (RRC_REL_CAUSE_RR_NORM_EVENT == ulRelCause)
              || (RRC_REL_CAUSE_RR_USER_INACT == ulRelCause)
              || (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == ulRelCause)
              || (RRC_REL_CAUSE_CELL_UPDATE_FAIL        == ulRelCause)
              || (RRC_REL_CAUSE_T315_EXPIRED            == ulRelCause) )
            {
                return VOS_TRUE;
            }
        }
        else
        {
            /* �ͷŵ���PS�������� */
            if (VOS_TRUE
                    == g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn)
            {
                /* �����������Ѵ��ڵ�PS���������Ϸ���� */
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;


}


/*****************************************************************************
 �� �� ��  : NAS_GMM_RetryRauProcedureCheck
 ��������  : ����Ƿ���Ҫ���·���ǰ���жϵ�RAU����
 �������  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause         - �ͷ�ԭ��ֵ
             RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus    - ��·״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ��Ҫ���·�������
             VOS_FALSE: ����Ҫ���·�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��1��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_GMM_RetryRauProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
)
{
    /*24.008 4.7.5.1.5
      b.1)  Release of PS signalling connection before the completion of
      the routing area updating procedure
      The routing area updating procedure shall be initiated again, if the
      following conditions apply:
      i)    The original routing area update procedure was initiated over an
      existing PS signalling connection; and
      ii)   The routing area update procedure was not due to timer T3330
      expiry; and
      iii)  No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection were (e.g. PS authe-
      ntication procedure, see subclause 4.7.7) received after the ROUTING
      AREA UPDATE REQUEST message was transmitted.
      b.2)  RR release in Iu mode (i.e. RRC connection release) with, for
      example, cause "Normal", or "User inactivity" or "Direct signalling
      connection re-establishment" (see 3GPP TS 25.331 [32c] and 3GPP TS
      44.118 [111])
      The routing area updating procedure shall be initiated again, if the
      following conditions apply:
      i)    The original routing area update procedure was initiated over an
      existing RRC connection; and
      ii)   The routing area update procedure was not due to timer T3330
      expiry; and
      iii)  No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection (e.g. PS authentica-
      tion procedure, see subclause 4.7.7) were received after the ROUTING
      AREA UPDATE REQUEST message was transmitted.
      NOTE:     The RRC connection release cause that triggers the re-initiation
      of the routing area update procedure is implementation specific.

      ע:
      Direct signalling connection re-establishment ԭ��ֵ�Ѿ����⴦���ˣ�
      �˴����ٴ���*/

    VOS_UINT8                               ucRst;

    ucRst = NAS_GMM_RetryCurrentProcedureCommonCheck();

    if (VOS_TRUE == ucRst)
    {
        if (0 == g_GmmRauCtrl.ucT3330outCnt)
        {
            if (RRC_RRC_CONN_STATUS_ABSENT == ulRrcConnStatus)
            {
                /* �ͷŵ���RRC���� */
                if ( (RRC_REL_CAUSE_RR_NORM_EVENT       == ulRelCause)
                  || (RRC_REL_CAUSE_RR_USER_INACT       == ulRelCause)
                  || (RRC_REL_CAUSE_CELL_UPDATE_FAIL    == ulRelCause)
                  || (RRC_REL_CAUSE_T315_EXPIRED        == ulRelCause) )
                {
                    return VOS_TRUE;
                }
            }
            else
            {
                /* �ͷŵ���PS�������� */
                if (VOS_TRUE
                        == g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn)
                {
                    /* �����������Ѵ��ڵ�PS���������Ϸ���� */
                    return VOS_TRUE;
                }
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RetrySrProcedureCheck
 ��������  : ����Ƿ���Ҫ���·���ǰ���жϵ�Service Request����
 �������  : RRC_REL_CAUSE_ENUM_UINT32           ulRelCause         - �ͷ�ԭ��ֵ
             RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus    - ��·״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ��Ҫ���·�������
             VOS_FALSE: ����Ҫ���·�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��1��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_GMM_RetrySrProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
)
{
    /*24.008 4.7.13.5
      b.1)  Release of PS signalling connection in Iu mode (i.e. RRC connect-
      ion release) before the completion of the service request procedure
      The service request procedure shall be initiated again, if the follow-
      ing conditions apply:
      i)    The original service request procedure was initiated over an exist-
      ing PS signalling connection; and
      ii)   No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection were received after
      the SERVICE REQUEST message was transmitted.
      b.2)  RR release in Iu mode (i.e. RRC connection release) with cause
      different than "Directed signalling connection re-establishment",
      for example, "Normal", or "User inactivity" (see 3GPP TS 25.331 [32c]
      and 3GPP TS 44.118 [111])
      The service request procedure shall be initiated again, if the follow-
      ing conditions apply:
      i)    The original service request procedure was initiated over an exist-
      ing RRC connection and,
      ii)   No SECURITY MODE COMMAND message and no Non-Access Stratum (NAS)
      messages relating to the PS signalling connection were received after
      the SERVICE REQUEST messge was transmitted.
      NOTE:     The RRC connection release cause different than "Directed sign-
      alling connection re-establishment" that triggers the re-initiation
      of the service request procedure is implementation specific.
      b.3)  RR release in Iu mode (i.e. RRC connection release) with cause
      "Directed signalling connection re-establishment" (see 3GPP TS 25.331
      [32c] and 3GPP TS 44.118 [111])
      The routing area updating procedure shall be initiated followed by
      a rerun of the service request procedure if the following condition
      applies:
      i)    The service request procedure was not due to a rerun of the proced-
      ure due to "Directed signalling connection re-establishment"*/

    VOS_UINT8                               ucRst;

    ucRst = NAS_GMM_RetryCurrentProcedureCommonCheck();

    if (VOS_TRUE == ucRst)
    {
        if (RRC_RRC_CONN_STATUS_ABSENT == ulRrcConnStatus)
        {
            /* �ͷŵ���RRC���� */
            if ( (RRC_REL_CAUSE_RR_NORM_EVENT           == ulRelCause)
              || (RRC_REL_CAUSE_RR_USER_INACT           == ulRelCause)
              || (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == ulRelCause)
              || (RRC_REL_CAUSE_CELL_UPDATE_FAIL        == ulRelCause)
              || (RRC_REL_CAUSE_T315_EXPIRED            == ulRelCause) )
            {
                return VOS_TRUE;
            }
        }
        else
        {
            /* �ͷŵ���PS�������� */
            if (VOS_TRUE
                    == g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn)
            {
                /* �����������Ѵ��ڵ�PS���������Ϸ���� */
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : NAS_GMM_UpdateGmmLinkCtrlStru
 ��������  : ����GMM�����ͷſ��ƽṹ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��3��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��7��14��
    ��    ��   : zhoujun 40661
    �޸�����   : ʹ��MML_CTX�е�����״̬
*****************************************************************************/
VOS_VOID NAS_GMM_UpdateGmmLinkCtrlStru(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();

    if (VOS_TRUE== GMM_IsCasGsmMode())
    {
        /* GSM������·�ͷ���ǿ���� */
        return;
    }


    g_GmmGlobalCtrl.stGmmLinkCtrl.ucCurrentProc = g_GmmGlobalCtrl.ucSpecProc;
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_FALSE;

    /* ��鵱ǰ�����Ƿ����ѽ�����RRC�����Ϸ��� */
    if (VOS_FALSE == pstConnStatus->ucRrcStatusFlg)
    {
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedRrcConn = VOS_FALSE;
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn = VOS_FALSE;
    }
    else if (VOS_TRUE ==
                        (pstConnStatus->ucPsSigConnStatusFlg))
    {
        /* PS ������·���� */
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedRrcConn = VOS_TRUE;
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn = VOS_TRUE;
    }
    else
    {
        /* RRC���Ӵ��ڣ���PS ������·������ */
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedRrcConn = VOS_TRUE;
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn = VOS_FALSE;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_ClearGmmLinkCtrlStru
 ��������  : ���GMM��·���Ʊ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��9��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_ClearGmmLinkCtrlStru( VOS_VOID )
{
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucCurrentProc = GMM_NULL_PROCEDURE;
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedPsSignallingConn = GMM_NULL_PROCEDURE;
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucExistedRrcConn = VOS_FALSE;
    g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_FALSE;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetDetachTypeFromProcName
 ��������  : ���ݵ�ǰ���������Detach����
 �������  : NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8            ucSpecProc  - ������
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��4��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_GMM_GetDetachTypeFromProcName(
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucSpecProc
)
{
    VOS_UINT8                           ucDetachType;

    switch (ucSpecProc)
    {
        case GMM_DETACH_COMBINED:
            if (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
            {
                ucDetachType = MMC_GMM_PS_CS_DETACH;
            }
            else
            {
                ucDetachType = MMC_GMM_PS_DETACH;
            }
            break;

        case GMM_DETACH_NORMAL:
        case GMM_DETACH_NORMAL_NETMODE_CHANGE:
            ucDetachType = MMC_GMM_PS_DETACH;
            break;

        case GMM_DETACH_WITH_IMSI:
            ucDetachType = MMC_GMM_CS_DETACH;
            break;

        default:
            ucDetachType = GMM_INVALID_DETACH_TYPE;
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "NAS_GMM_GetDetachTypeFromCurrProc: Procedure is not detach related.");
    }

    return ucDetachType;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_SndStatusMsg
 ��������  : ������ظ�STATUS��Ϣ
 �������  : VOS_UINT8 ulCause - ԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��23��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_SndStatusMsg(
    VOS_UINT8                           ucCause
)
{
    NAS_MSG_STRU        *pGmmStatus;

    pGmmStatus = Gmm_GmmStatusMsgMake(ucCause);

    if (VOS_NULL_PTR != pGmmStatus)
    {
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_ClearBufferedSmDataReq
 ��������  : ��������SM DATA REQ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��13��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_ClearBufferedSmDataReq( VOS_VOID )
{
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(): Clear cached SM Data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }


    /* û�ж���ʱ,���follow on��־ */
    if (GMM_FALSE == g_GmmServiceCtrl.ucSmsFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }



    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_CheckGmmInfoMsg
 ��������  : ���Gmm Information��Ϣ
 �������  : pMsg - Gmm Information ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32 - ��Ϣ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��23��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_GMM_CheckGmmInfoMsg(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg
)
{
    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_GMM_INFORMATION)
    {
        /* ��Ϣ�ĳ��ȷǷ� */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvGmmInformationMsg:WARNING: The length of GMM INFORMATION is invalid");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        return VOS_ERR;
    }

    if (GMM_NOT_SUPPORT_INFORMATION_MSG == g_GmmGlobalCtrl.UeInfo.ucSupportInfoFlg)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvGmmInformationMsg:WARNING: GMM INFORMATION is unsupported");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE);

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_DecodeFullNameforNetworkIE
 ��������  : ������Ϣ�е�Full Name for Network IE
 �������  : NAS_MSG_FOR_PCLINT_STRU *pMsg - ��Ϣָ��
             VOS_UINT32 *pulIeOffset       - ��ǰ����ָ���λ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��23��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��01��09��
    ��    ��   : l65478
    �޸�����   : DTS2013010809507���������ϱ�����

*****************************************************************************/
VOS_UINT32 NAS_GMM_DecodeFullNameforNetworkIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset
)
{
    VOS_UINT32                          ulIePos;
    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();
    ulIePos             = *pulIeOffset;

    /* ��Ϣ��ֻ����Tag */
    if ( pMsg->ulNasMsgSize < (ulIePos + 2) )
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeFullNameforNetworkIE:WARNING: FULL NAME for NETWORK is error in GMM INFORMATION");
        return VOS_ERR;
    }

    /* ��IE lenΪ0 */
    if ( 0 == pMsg->aucNasMsg[ulIePos + 1] )
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeFullNameforNetworkIE:WARNING: GMM INFORMATION is semantically incorrect");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    PS_MEM_SET(pstCurrOperatorName->aucOperatorNameLong, 0, NAS_MML_MAX_OPER_LONG_NAME_LEN);
    if (NAS_MML_MAX_OPER_LONG_NAME_LEN >= (pMsg->aucNasMsg[ulIePos + 1] + 1))
    {
        PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameLong, (VOS_UINT8 *)&(pMsg->aucNasMsg[ulIePos + 1]), pMsg->aucNasMsg[ulIePos + 1] + 1);
    }
    else
    {
        PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameLong, (VOS_UINT8 *)&(pMsg->aucNasMsg[ulIePos + 1]), NAS_MML_MAX_OPER_LONG_NAME_LEN);
    }

    *pulIeOffset += pMsg->aucNasMsg[ulIePos + 1] + 2;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_DecodeShortNameforNetworkIE
 ��������  : ������Ϣ�е�Short Name for Network IE
 �������  : NAS_MSG_FOR_PCLINT_STRU *pMsg - ��Ϣָ��
             VOS_UINT32 *pulIeOffset       - ��ǰ����ָ���λ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��23��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��01��09��
    ��    ��   : l65478
    �޸�����   : DTS2013010809507���������ϱ�����

*****************************************************************************/
VOS_UINT32  NAS_GMM_DecodeShortNameforNetworkIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset
)
{
    VOS_UINT32                          ulIePos;

    NAS_MML_OPERATOR_NAME_INFO_STRU    *pstCurrOperatorName = VOS_NULL_PTR;

    pstCurrOperatorName = NAS_MML_GetOperatorNameInfo();
    ulIePos             = *pulIeOffset;

    /* ��Ϣ��ֻ����Tag */
    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ulIePos + 2))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeShortNameforNetworkIE:WARNING: SHORT NAME for NETWORK is error in GMM INFORMATION");
        return VOS_ERR;
    }

    if (0 == pMsg->aucNasMsg[ulIePos + 1])
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeShortNameforNetworkIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    PS_MEM_SET(pstCurrOperatorName->aucOperatorNameShort, 0, NAS_MML_MAX_OPER_SHORT_NAME_LEN);
    if (NAS_MML_MAX_OPER_SHORT_NAME_LEN >= (pMsg->aucNasMsg[ulIePos + 1] + 1))
    {
        PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameShort, (VOS_UINT8 *)&(pMsg->aucNasMsg[ulIePos + 1]), pMsg->aucNasMsg[ulIePos + 1] + 1);
    }
    else
    {
        PS_MEM_CPY(pstCurrOperatorName->aucOperatorNameShort, (VOS_UINT8 *)&(pMsg->aucNasMsg[ulIePos + 1]), NAS_MML_MAX_OPER_SHORT_NAME_LEN);
    }

    *pulIeOffset += pMsg->aucNasMsg[ulIePos + 1] + 2;

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_DecodeLocalTimeZoneIE
 ��������  : ������Ϣ�е�Local Time Zone IE
 �������  : NAS_MSG_FOR_PCLINT_STRU *pMsg - ��Ϣָ��
             VOS_UINT32 *pulIeOffset       - ��ǰ����ָ���λ��
             pstMmInfo                     - ��������õ�IEֵ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��23��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_GMM_DecodeLocalTimeZoneIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
)
{
    VOS_UINT32      ulIePos;
    VOS_INT8        cTimeZone;
    VOS_UINT8       ucDigit;

    ulIePos = *pulIeOffset;

    /* ��Ϣ���Ȳ��� */
    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ulIePos + 2))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeLocalTimeZoneIE:WARNING: IE Len incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    ucDigit = ((pMsg->aucNasMsg[ulIePos + 1]) & 0xF0) >> 4;
    if ( ucDigit > 9 )
    {
        /*ֵ�Ƿ� */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeLocalTimeZoneIE:WARNING: Time Zone value incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    cTimeZone = (VOS_INT8)((((pMsg->aucNasMsg[ulIePos + 1]) & 0x07) * 10) + ucDigit);

    /* �ж�ʱ��������ֵ */
    if ((pMsg->aucNasMsg[ulIePos + 1]) & 0x08)
    {
        pstMmInfo->cLocalTimeZone = - cTimeZone;
    }
    else
    {
        pstMmInfo->cLocalTimeZone = cTimeZone;
    }

    pstMmInfo->ucIeFlg |= NAS_MM_INFO_IE_LTZ;

    *pulIeOffset += 2;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE
 ��������  : ������Ϣ�е�Universal Time and Local Time Zone IE
 �������  : NAS_MSG_FOR_PCLINT_STRU *pMsg - ��Ϣָ��
             VOS_UINT32 *pulIeOffset       - ��ǰ����ָ���λ��
             pstMmInfo                     - ��������õ�IEֵ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��23��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��7��1��
    ��    ��   : ŷ����
    �޸�����   : DTS2010062801177,���Ӷ�IE����Ч�Լ��

  3.��    ��   : 2010��7��20��
    ��    ��   : ŷ����
    �޸�����   : DTS2010072001259����IE���ʧ��ʱ�����Ը���Ϣ�������ٸ�����
                 �ظ�GMM STATUS��Ϣ
*****************************************************************************/
VOS_UINT32  NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
)
{
    VOS_UINT32      ulIePos;
    VOS_INT8        cTimeZone;
    VOS_UINT8       ucDigit;

    ulIePos = *pulIeOffset;

    /* ��Ϣ���Ȳ��� */
    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ulIePos + 8))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    /* ��һ���ֽ�Ϊ Year */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucYear = (((pMsg->aucNasMsg[ulIePos + 1]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 1]) & 0xf0) >> 4);
    if (pstMmInfo->stUniversalTimeandLocalTimeZone.ucYear > 99)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Year Value.");
        return VOS_ERR;
    }


    /* �ڶ����ֽ�Ϊ Month */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucMonth = (((pMsg->aucNasMsg[ulIePos + 2]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 2]) & 0xf0) >> 4);
    if (  (pstMmInfo->stUniversalTimeandLocalTimeZone.ucMonth > 12)
        ||(0 == pstMmInfo->stUniversalTimeandLocalTimeZone.ucMonth) )
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Month Value.");
        return VOS_ERR;
    }

    /* �������ֽ�Ϊ Day */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucDay = (((pMsg->aucNasMsg[ulIePos + 3]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 3]) & 0xf0) >> 4);
    if (  (pstMmInfo->stUniversalTimeandLocalTimeZone.ucDay > 31)
        || (0 == pstMmInfo->stUniversalTimeandLocalTimeZone.ucDay) )
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Day Value.");
        return VOS_ERR;
    }

    /* ���ĸ��ֽ�Ϊ Hour */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucHour = (((pMsg->aucNasMsg[ulIePos + 4]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 4]) & 0xf0) >> 4);
    if (pstMmInfo->stUniversalTimeandLocalTimeZone.ucHour >= 24)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Hour Value.");
        return VOS_ERR;
    }

    /* ������ֽ�Ϊ Minute */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucMinute = (((pMsg->aucNasMsg[ulIePos + 5]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 5]) & 0xf0) >> 4);
    if (pstMmInfo->stUniversalTimeandLocalTimeZone.ucMinute >= 60)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Minute Value.");
        return VOS_ERR;
    }

    /* �������ֽ�Ϊ Second */
    pstMmInfo->stUniversalTimeandLocalTimeZone.ucSecond = (((pMsg->aucNasMsg[ulIePos + 6]) & 0x0f) * 10)
                                                     +(((pMsg->aucNasMsg[ulIePos + 6]) & 0xf0) >> 4);
    if (pstMmInfo->stUniversalTimeandLocalTimeZone.ucSecond >= 60)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Second Value.");
        return VOS_ERR;
    }

    /* ���߸��ֽ�Ϊ TimeZone */
    ucDigit = ((pMsg->aucNasMsg[ulIePos + 7]) & 0xF0) >> 4;
    if (ucDigit > 9)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE:WARNING: Invalid Time Zone Value.");
        return VOS_ERR;
    }
    cTimeZone = (VOS_INT8)((((pMsg->aucNasMsg[ulIePos + 7]) & 0x07) * 10) + ucDigit );

    /* �ж�ʱ��������ֵ */
    if ((pMsg->aucNasMsg[ulIePos + 7]) & 0x08)
    {
        pstMmInfo->stUniversalTimeandLocalTimeZone.cTimeZone = - cTimeZone;
    }
    else
    {
        pstMmInfo->stUniversalTimeandLocalTimeZone.cTimeZone = cTimeZone;
    }

    pstMmInfo->ucIeFlg |= NAS_MM_INFO_IE_UTLTZ;

    *pulIeOffset += 8;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_DecodeLSAIdentityIE
 ��������  : ������Ϣ�е�LSA IDENTITY IE
 �������  : NAS_MSG_FOR_PCLINT_STRU *pMsg - ��Ϣָ��
             VOS_UINT32 *pulIeOffset       - ��ǰ����ָ���λ��
             pstMmInfo                     - ��������õ�IEֵ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��23��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_GMM_DecodeLSAIdentityIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
)
{
    VOS_UINT32      ulIePos;

    ulIePos = *pulIeOffset;

    /* ��Ϣ���Ȳ��� */
    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ulIePos + 2))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeLSAIdentityIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    pstMmInfo->ucIeFlg |= NAS_MM_INFO_IE_LSA;

    /* IE ���ȷǷ� */
    if (3 < pMsg->aucNasMsg[ulIePos + 1])
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeLSAIdentityIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    /* ĿǰLSA ID ��Ϣδʹ��, ������ */


    *pulIeOffset += pMsg->aucNasMsg[ulIePos + 1] + 2;

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_DecodeDaylightSavingTimeIE
 ��������  : ������Ϣ�е�Daylight Saving Time IE
 �������  : NAS_MSG_FOR_PCLINT_STRU *pMsg - ��Ϣָ��
             VOS_UINT32 *pulIeOffset       - ��ǰ����ָ���λ��
             pstMmInfo                     - ��������õ�IEֵ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��23��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_GMM_DecodeDaylightSavingTimeIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
)
{
    VOS_UINT32      ulIePos;

    ulIePos = *pulIeOffset;

    /* ��Ϣ���Ȳ��� */
    if ((VOS_UINT8)(pMsg->ulNasMsgSize) < (ulIePos + 3))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeDaylightSavingTimeIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    /* IE ��Ч�Լ��ʧ�� */
    if ((1 != pMsg->aucNasMsg[ulIePos + 1]) || (pMsg->aucNasMsg[ulIePos + 2] > 3))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeDaylightSavingTimeIE:WARNING: GMM INFORMATION is semantically incorrect.");
        NAS_GMM_SndStatusMsg(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);

        return VOS_ERR;
    }

    pstMmInfo->ucIeFlg |= NAS_MM_INFO_IE_DST;
    pstMmInfo->ucDST = pMsg->aucNasMsg[ulIePos + 2];

    *pulIeOffset += 3;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedStartT3340RegSuccNoFollowOnProceed
 ��������  : attach accept��rau accept����follow on proceed�ж��Ƿ���Ҫ����t3340��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ����T3340
             VOS_FALSE - ����Ҫ����T3340
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : z00161729
    �޸�����   : DTS2015071505434:rau��attach���󲻴�follow on������ظ�attach accept��rau accept��Я��follow on proceed��ʶ��gmm��Ҫ
                 �����ж����ps rab���ڻ����rabm�ؽ���smҵ�������cds���ڻ�������������T3340����������t3340���������������

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedStartT3340RegSuccNoFollowOnProceed(VOS_VOID)
{
    VOS_UINT32                          ulIsPsRabExistFlag;
    VOS_UINT8                           ucPdpExistNotStartT3340Flag;
    VOS_UINT32                          ulUsimMMApiIsTestCard;

    ulUsimMMApiIsTestCard       = NAS_USIMMAPI_IsTestCard();
    ulIsPsRabExistFlag          = NAS_RABM_IsPsRbExist();
    ucPdpExistNotStartT3340Flag = NAS_MML_GetPdpExistNotStartT3340Flag();

    /* 24008 R12 Table 11.3/3GPP TS 24.008��������:
     T3340��ʱ����������: ATTACH ACCEPT or ROUTING AREA UPDATE ACCEPT is
     received with "no follow-on proceed" indication and user plane
     radio access bearers have not been setup. */
    if (VOS_TRUE == ulIsPsRabExistFlag)
    {
        return VOS_FALSE;
    }

    if (VOS_TRUE == ulUsimMMApiIsTestCard)
    {
        return VOS_TRUE;
    }

    if ((VOS_TRUE == NAS_MML_IsPsBearerExist())
     && (VOS_TRUE == ucPdpExistNotStartT3340Flag))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedStartT3340RegSuccWithFollowOnProceed
 ��������  : attach accept��rau accept��follow on proceed�ж��Ƿ���Ҫ����t3340��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ����T3340
             VOS_FALSE - ����Ҫ����T3340
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : z00161729
    �޸�����   : DTS2015071505434:rau��attach���󲻴�follow on������ظ�attach accept��rau accept��Я��follow on proceed��ʶ��gmm��Ҫ
                 �����ж����ps rab���ڻ����rabm�ؽ���smҵ�������cds���ڻ�������������T3340����������t3340���������������

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedStartT3340RegSuccWithFollowOnProceed(VOS_VOID)
{
    VOS_UINT32                          ulDataAvailFlg;
    VOS_UINT32                          ulIsPsRabExistFlag;

    ulIsPsRabExistFlag          = NAS_RABM_IsPsRbExist();

    if (VOS_FALSE == NAS_GMM_IsEnableRelPsSigCon())
    {
        return VOS_FALSE;
    }

    /* 24008 R12 4.7.13�½���������:
       If the network indicates "follow-on proceed" and the MS has no service
       request pending, then no specific action is required from the MS.
       As an implementation option, the MS may start timer T3340 as described
       in subclause 4.7.1.9 if no user plane radio access bearers are set up.
       RAU request��ϢδЯ��follow on,��������������������T3340:
       1����ǰû�������ڽ���
       2����û�л����rabm�ؽ�����
       3��û�л����smҵ������
       4��������ps��rab
       5��2309 nv�����Ҳ��ǲ��Կ� */
    ulDataAvailFlg     = CDS_IsPsDataAvail();

    if ((VOS_TRUE != NAS_GMM_IsFollowOnPend())
     && (PS_TRUE  != ulDataAvailFlg)
     && (VOS_TRUE != ulIsPsRabExistFlag)
     && (GMM_MSG_HOLD_FOR_SERVICE != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
     && (GMM_MSG_HOLD_FOR_SM != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_CheckIfNeedToStartTimerT3340
 ��������  : ���յ�RAU ACCEPT�󣬼���Ƿ���Ҫ����T3340��ʱ�������RRC��·��
             �ͷ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��7��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��3��7��
    ��    ��   : z00161729
    �޸�����   : V7R1 C50 ֧��ISR�޸�
  3.��    ��   : 2014��10��23��
    ��    ��   : z00161729
    �޸�����   : DTS2014102403468:rau accept����û�д�follow on proceed����Ҫ����T3340��T3340�����ڼ�����յ�����pdp modify�����ȥ����������Ҫ�����ظ�
  4.��    �� : 2015-4-1
    ��    �� : wx270776
	�޸����� : DTS2015032608956: ���Ϊ���Կ���������3340��ʱ��
  5.��    ��   : 2015��7��14��
    ��    ��   : z00161729
    �޸�����   : DTS2015071505434:rau��attach���󲻴�follow on������ظ�attach accept��rau accept��Я��follow on proceed��ʶ��gmm��Ҫ
                �����ж����ps rab���ڻ����rabm�ؽ���smҵ�������cds���ڻ�������������T3340����������t3340���������������
*****************************************************************************/
VOS_VOID  NAS_GMM_CheckIfNeedToStartTimerT3340(VOS_VOID)
{
    VOS_INT8                            cVersion;
    VOS_UINT32                          ulT3340TimerStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;


    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

#if (PS_UE_REL_VER >= PS_PTL_VER_R6)
    if (cVersion >= PS_PTL_VER_R6)
    {
        /* R7������T3340��ʱ��������R6������Ҳ���ʵ��Ҳ�Ǻ���ġ� */
        if (   (GMM_FALSE == GMM_IsCasGsmMode())
            && (GMM_FALSE == g_GmmGlobalCtrl.ucFopFlg))
        {
            if (VOS_TRUE == NAS_GMM_IsNeedStartT3340RegSuccNoFollowOnProceed())
            {
                Gmm_TimerStart(GMM_TIMER_T3340);
            }
        }

        /* ����������� */
        ulT3340TimerStatus = NAS_GMM_QryTimerStatus(GMM_TIMER_T3340);
        enRatType          = NAS_MML_GetCurrNetRatType();

        if ((NAS_MML_NET_RAT_TYPE_WCDMA == enRatType)
         && (VOS_FALSE                  == ulT3340TimerStatus)
         && (GMM_TRUE == g_GmmGlobalCtrl.ucFopFlg))
        {
            if (VOS_TRUE == NAS_GMM_IsNeedStartT3340RegSuccWithFollowOnProceed())
            {
                /* ʹ����������������õ�T3340�Ķ�ʱ��ʱ�� */
                g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = NAS_GMM_GetRelPsSigConCfg_T3340TimerLen();
                Gmm_TimerStart(GMM_TIMER_T3340);

                /* �ָ�T3340��Э���׼ʱ�� */
                g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_T3340_VALUE;
            }

        }
    }
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer
 ��������  : �ж��Ƿ���Ҫ������ʱ�� GMM_TIMER_DELAY_PS_SMS_CONN_REL
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��23��
    ��    ��   : c00318887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    /* ȡ�õ�ǰ��������Ϣ */
    pstConnStatus = NAS_MML_GetConnStatus();

    /* �������û���������ǲ��Կ� */
    if (VOS_FALSE == NAS_GMM_IsEnableRelPsSigCon())
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:IsEnableRelPsSigCon is false");
        return VOS_FALSE;
    }

    /* T3340�����У����T3340��ʱ�ͷ����� */
    if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3340))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:T3340 is runing");
        return VOS_FALSE;
    }
    
    /* ��ǰ����W�£�����ҪREL */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:rat isnot WCDMA");
        return VOS_FALSE;
    }
    
    /* sm�ڽ���pdp���ȥ���modify���̣�����false������Ҫ�����ͷ����� */
    if (NAS_MML_SM_PROC_FLAG_START == NAS_MML_GetSmProcFlag())
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:SmProcFlag is start");
        return VOS_FALSE;
    }

    /* pdp�Ѿ��������false������Ҫ�����ͷ����� */
    if (VOS_TRUE == NAS_MML_GetPdpConnStateInfo())
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:PdpConnState is ture");
        return VOS_FALSE;
    }

    /* ����GMM ����ʱ������Ҫ�����ͷ����� */
    if (GMM_NULL_PROCEDURE != g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:g_GmmGlobalCtrl.ucSpecProc != GMM_NULL_PROCEDURE");
        return VOS_FALSE;
    }

    /* ����PS��· */
    if ( (VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
      && (VOS_TRUE == pstConnStatus->ucPsSigConnStatusFlg) )
    {
        return VOS_TRUE;
    }

    NAS_WARNING_LOG2(WUEPS_PID_GMM, "NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer:RrcStatus and PsSigConnStatus are", 
                        pstConnStatus->ucRrcStatusFlg, pstConnStatus->ucPsSigConnStatusFlg);
    
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_TransferSmEstCause2RrcEstCause
 ��������  : ��SM�Ľ�������ԭ��ֵת��ΪRRC����ԭ��ֵ
 �������  : VOS_UINT32     ulSmEstCause    - SM�Ľ�������ԭ��ֵ
 �������  : VOS_UINT32     *pulRrcEstCause - RRC����ԭ��ֵָ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��19��
    ��    ��   : ŷ����
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_TransferSmEstCause2RrcEstCause(
    VOS_UINT32                          ulSmEstCause,
    VOS_UINT32                          *pulRrcEstCause
)
{
    VOS_UINT32  ulRrcEstCause;

    switch (ulSmEstCause)
    {
        case GMM_SM_RRC_EST_CAUSE_ORG_CONV_CALL:
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_STM_CALL:
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_STREAM_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_INTER_CALL:
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_INTERACT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_BG_CALL:
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_BACKGROUND_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_ST_CALL:
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_SUBSCRIB_TRAFFIC_CALL;
            break;
        default:
            NAS_INFO_LOG1(WUEPS_PID_GMM, "NAS_GMM_TransferSmEstCause2RrcEstCause: Rcv SmEstCause:", ulSmEstCause);
            ulRrcEstCause = RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL;
            break;
    }

    *pulRrcEstCause = ulRrcEstCause;

    return;
}

/*******************************************************************************
Module   : NAS_GMM_FreeTlliForPowerOff
Function : �ڹػ�״̬ʱ���ͷ�TLLI�����L2�����ݣ����ָ�L2
Input    : ��
Output   : ��
NOTE     : ��
Return   : ��
History  :
  1.��    ��   : 2010��09��13��
    ��    ��   : l65478
    �޸�����   : �����ɺ���
*******************************************************************************/
VOS_VOID NAS_GMM_FreeTlliForPowerOff(VOS_VOID)
{
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_ALL);
        if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                               /* �ָ�LLC���ݴ��� */
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
        }
        GMM_FreeSysTlli();
        Gmm_TimerStop(GMM_TIMER_PROTECT_OLD_TLLI);
        gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsFollowOnPend
 ��������  : ��RAU��Attach��Ϣ���Ƿ���Ҫ��Follow on�����ж�
 �������  : ��
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��16��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��25��
    ��    ��   : w00242748
    �޸�����   : DTS2013072200933:vodafone r8����csfb mt��w��cs ps�����ͷź�1.5s����ѡ��l��
                 �������2s���һ������·�paging��Ϣ�����ڶ�Ѱ�����д�ͨ���ο����ʵ�֣�
                 rau req�д�follow on��־,����ȷЭ������
  3.��    ��   : 2013��7��25��
    ��    ��   : w00242748
    �޸�����   : DTS2014053105098:CSFB mo�Ƿ���Ҫ��follow on����NV����
*****************************************************************************/
VOS_BOOL NAS_GMM_IsFollowOnPend(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                               ucIsRauNeedFollowOnCsfbMtFlg;
    VOS_UINT8                                               ucDelayedCsfbLauFlg;
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  ucCsfbServiceStatus;
    VOS_UINT8                                               ucIsRauNeedFollowOnCsfbMoFlg;
#endif

    if (NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    ucIsRauNeedFollowOnCsfbMtFlg = NAS_MML_GetIsRauNeedFollowOnCsfbMtFlg();
    ucCsfbServiceStatus          = NAS_MML_GetCsfbServiceStatus();
    ucDelayedCsfbLauFlg          = NAS_MML_GetDelayedCsfbLauFlg();
    ucIsRauNeedFollowOnCsfbMoFlg = NAS_MML_GetIsRauNeedFollowOnCsfbMoFlg();

    /* ���ձ��ʵ�֣�������ȷЭ��涨 */
    if ((VOS_TRUE == ucIsRauNeedFollowOnCsfbMtFlg)
     && (NAS_MML_CSFB_SERVICE_STATUS_MT_EXIST == ucCsfbServiceStatus)
     && (VOS_FALSE == ucDelayedCsfbLauFlg))
    {
        return VOS_TRUE;
    }

    if ( (VOS_TRUE == NAS_MML_IsCsfbMoServiceStatusExist())
      && (VOS_TRUE == ucIsRauNeedFollowOnCsfbMoFlg) )
    {
        return VOS_TRUE;
    }

#endif

    if (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        return VOS_FALSE;
    }

    if (GMM_NULL_PROCEDURE != g_GmmGlobalCtrl.ucSpecProcHold)
    {
        return VOS_TRUE;
    }

    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {
        return VOS_TRUE;
    }

    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        return VOS_TRUE;
    }

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_HandleModeANOIWhenRAInotChange
 ��������  : GMM���յ�ϵͳ��Ϣ����ǰΪA+IģʽʱRAIû�иı�Ĵ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��20��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��04��08��
    ��    ��   : o00132663
    �޸�����   : DTS2011040803612���ֶ�������RAU�ܾ�ԭ��Ϊ#9,#10ʱ���ض�����
                 ����Attach����ǰ�͸��û��ظ�ʧ��
  3.��    ��   : 2013��7��4��
    ��    ��   : w00167002
    �޸�����   : DSVLTE_bbit:DTS2013070302959:w�£�II,��46002��ע��ɹ�,�û�ָ����24005�ϣ�I,PS/CSע��ʧ��
                 ԭ��Ϊ����ʧ��(7)=>
                 1.�յ�ϵͳ��Ϣ��PSע��״̬Ǩ�Ƶ���5(��ΪGMM��MMC�ϱ���ע��ɹ�)��
                    -->GMM֪ͨMMCע��״̬ʧ�ܣ�CAUSE401;
                 2. MMC����������(��Ϊ��ON PLMN״̬��GMM��MMC�ϱ�401ԭ�򣬸�MM�ϱ�
                 ԭ��410��MM��MMC֪ͨ410�󣬴���������)��
                    -->MM�յ�GMM��ǰ����ԭ��410ʱ��ת����401ԭ��֪ͨMMC;
                 3.�����ɹ�����ԭС���յ�ϵͳ��Ϣ��MMC�ظ���������(GMM֪ͨMM��ǰ
                   PS��ǰע��ɹ���CSԭ��16������MM��MMC�ϱ�16ԭ��ֵ������ѭ������)��
                   -->GMM��ATTEMPT TO UPDATE״̬��֪ͨMM����ԭ��410��
                 4. ֪ͨMM PS only�ɹ���ԭ��ֵ��16�޸�Ϊ401��sunxiboһ���߶����յ�
                    ϵͳ��Ϣʱ��ԭ��ֵ������дΪ16������MM֪ͨMMC16��ATTMPT���Դ���
                    Ϊ4�Σ��ᴥ��������
  4.��    ��   : 2014��04��08��
    ��    ��   : s00217060
    �޸�����   : DTS2014040901544:PS��ע�ᱻ��#111,�������T3302��ʱ��ʱ��Ϊ0�������ͷ����յ�ϵͳ��Ϣʱ��UEһֱ����ATTACH

*****************************************************************************/
VOS_VOID NAS_GMM_HandleModeANOIWhenRAInotChange()
{
    VOS_UINT8 ucState;

    ucState = g_GmmGlobalCtrl.ucState;
    if (GMM_REGISTERED_PLMN_SEARCH == ucState)
    {
        ucState = g_GmmGlobalCtrl.ucPlmnSrchPreSta;
    }

    if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
     && (GMM_REGISTERED_NORMAL_SERVICE == ucState))
    {
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
        NAS_GMM_SndMmCombinedRauInitiation();
        NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                       NAS_MML_REG_FAIL_CAUSE_NULL,
                                       VOS_NULL_PTR,
                                       VOS_NULL_PTR);


        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
    }
    else
    {
        /* ����������T3311��T3302��ʱʱû�н���RAU */
        /* �����������T3302��ʱ��ʱ��Ϊ0ʱ������T3302��ʱ��������������һ���жϣ�UE��һֱ����ATTACH */
        if ((GMM_TIMER_T3302_FLG
            != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        && ((GMM_TIMER_T3311_FLG
            != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
        && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
        {                                                                       /* Timer3302��������                        */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
        }
        else
        {
            /* GMMǨ��IDLE̬����T3311��T3302��ʱ���ٷ���RAU */
            if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == ucState)
            {

                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                NAS_GMM_SndMmCombinedRauInitiation();
                NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_PS_ONLY,
                                               NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE,
                                               VOS_NULL_PTR,
                                               VOS_NULL_PTR);


                /* ��MMC����PSע���� */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);

                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM);
            }
            else
            {

                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                /* ��MMC����PSע���� */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);


                NAS_GMM_SndMmCombinedRauInitiation();
                NAS_GMM_SndMmCombinedRauRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);

                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
            }

        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_HandleModeANOIWhenDeregister
 ��������  : GMM���յ�ϵͳ��Ϣ����ǰΪA+Iģʽδע��ʱ �Ĵ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��20��
    ��    ��   : 12
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��11��8��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseII�׶ν���ػ�������
  3.��    ��   : 2012��9��25��
    ��    ��   : h00216089
    �޸�����   : DTS2012090304976:����������Detach(re-attach not required)��MM��ʱ����ʱ����LU��
                  LU�������յ�ϵͳ��ϢGMM�����ٷ���Attach
  4.��    ��   : 2014��04��08��
    ��    ��   : s00217060
    �޸�����   : DTS2014040901544:PS��ע�ᱻ��#111,�������T3302��ʱ��ʱ��Ϊ0�������ͷ����յ�ϵͳ��Ϣʱ��UEһֱ����ATTACH
*****************************************************************************/
VOS_VOID NAS_GMM_HandleModeANOIWhenDeregister()
{
    VOS_UINT8                           ucAttachCnt;

    if ((GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg)
    && (VOS_TRUE == g_GmmGlobalCtrl.ucRcvNetDetachFlg))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                     /* ����״̬�Ĺ�������*/
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);
        return;
    }

    if ((GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg)
    && (GMM_FALSE == gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg)
    && ((GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
     || (GMM_DEREGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)))
    {
        /* �����������T3302��ʱ��ʱ��Ϊ0ʱ������T3302��ʱ��������������һ���жϣ�UE��һֱ����ATTACH */
        if ((GMM_TIMER_T3302_FLG
            != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        && ((GMM_TIMER_T3311_FLG
            != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
        && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
        {
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            {
                ucAttachCnt = g_GmmAttachCtrl.ucAttachAttmptCnt;
                g_GmmAttachCtrl.ucAttachAttmptCnt = 5;
                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                /* ��MMC����PSע����,��PSע��ʧ�ܣ���������Ҫ��MMC�ϱ�ԭ��ֵΪOTHER CAUSE */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                g_GmmAttachCtrl.ucAttachAttmptCnt = ucAttachCnt;
            }

            Gmm_ComStaChg(GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH);
        }
    }
    else
    {
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;

        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_BackToOrgPlmnAfterCoverageLost
 ��������  : �ӳ��������ص�ԭ����PLMN�Ĵ���
 �������  : VOS_VOID                           *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��9��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��19��
    ��    ��   : zhoujun 40661
    �޸�����   : DTS2011111700165,����ģʽI��,GMM�ص�ԭС��,δ��֪ͨMM������������
  3.��    ��   : 2012��1��18��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�DTS2012011601544,����ģʽI ����ע���PS�ɹ�,�������к�CSָʾ��������
  4.��    ��   : 2012��02��23��
    ��    ��   : l65478
    �޸�����   : DTS2012021306419,BVT���ԣ�RAIû�иı�ʱ��������RAU
 5. ��    ��   : 2012��3��28��
    ��    ��   : l65478
    �޸�����   : ���ⵥ�ţ�DTS2012032002585:��W->L->Wʱ���ص�W��û�з���RAU
 6. ��    ��   : 2012��7��17��
    ��    ��   : z00161729
    �޸�����   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR����CS LAI�ı�)-W(LAI1����ģʽI)��Ҫ
                  ��������rau
  7.��    ��   : 2013��9��29��
    ��    ��   : w00242748
    �޸�����   : DTS2013092302598:�ֶ�������L�³ɹ�פ����CSFB��W�£�λ�����仯��LAU/RAU����ʧ��(5��)��
                 ������ԭС����������������RAUʧ�ܣ�MM����LAUʧ�ܣ���ѭ����MM ATTEMPT COUNTER��������
*****************************************************************************/
VOS_UINT32 NAS_GMM_BackToOrgPlmnAfterCoverageLost(
    VOS_VOID                           *pMsg
)
{
    GMM_RAI_STRU                       *pRaiTemp = VOS_NULL_PTR;
    VOS_UINT8                           ucRaiChgFlg;
    VOS_UINT8                           ucLaiChgFlg;
    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    GMM_RAI_STRU                        stGmmRai;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
#endif

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));
    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_RcvMmcSysInfoInd_RegUpdtNeed:ERROR: Alloc mem fail.");
        return VOS_FALSE;
    }
    Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp(pRaiTemp, pMsg);

    Gmm_Get_Location_Change_info(pRaiTemp, &stGmmRai, &ucLaiChgFlg, &ucRaiChgFlg, g_GmmGlobalCtrl.ucNetMod);

    Gmm_MemFree(pRaiTemp);

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
     && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
    {
        return VOS_FALSE;
    }
    /* ����GMM LIMITEDֻ�����漸�����:
       1. �ܾ�ԭ��ֵ#13
       2. �ܾ�ԭ��ֵ#11
       3. ��ǰС����֧��GPRS
       4. ��ǰ�����ֹע��
       ��ǰ�����������״̬����U1,
       �ں�������������ԭ����U1,����RAI���ı��ʱ,����Ҫ����RAU */
#if (FEATURE_ON == FEATURE_LTE)
    enTinType = NAS_MML_GetTinType();
    if ((NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
     && (GMM_FALSE == ucRaiChgFlg)
     && (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
     && (NAS_MML_TIN_TYPE_PTMSI == enTinType))
#else
    if ((NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
     && (GMM_FALSE == ucRaiChgFlg)
     && (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG)))
#endif
    {
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( ( VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;


        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_DeleteEPlmnList
 ��������  : ���EPLMN�б�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��8��
    ��    ��   : s46746
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
*****************************************************************************/
VOS_VOID NAS_GMM_DeleteEPlmnList()
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEPlmnList    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmnId = VOS_NULL_PTR;

    pstEPlmnList = NAS_MML_GetEquPlmnList();


    NAS_MML_InitEquPlmnInfo(pstEPlmnList);

    /* ���NV�б����EPLMN */
    NAS_GMM_WriteEplmnNvim(pstEPlmnList);

    /*����ǰ�������Eplmn�б�*/
    pstCurrPlmnId = NAS_MML_GetCurrCampPlmnId();

    pstEPlmnList->astEquPlmnAddr[0].ulMcc = pstCurrPlmnId->ulMcc;
    pstEPlmnList->astEquPlmnAddr[0].ulMnc = pstCurrPlmnId->ulMnc;

    pstEPlmnList->ucEquPlmnNum = 1;


    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_DecodeEquPlmnInfoIE
 ��������  : ������Ϣ�е�EQUIVALENT PLMN IE
 �������  : GMM_MMC_ACTION_TYPE_ENUM_U32        enActionType,
              GMM_MSG_RESOLVE_STRU               *pstAcceptIe,
              NAS_MSG_FOR_PCLINT_STRU            *pstNasMsg,
 �������  : NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011��10��8��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��6��5��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_VOID NAS_GMM_DecodeEquPlmnInfoIE(
    GMM_MMC_ACTION_TYPE_ENUM_U32        enActionType,
    GMM_MSG_RESOLVE_STRU               *pstAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU            *pstNasMsg,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    VOS_UINT8                          *pucEPlmnlist    = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstPlmnId       = VOS_NULL_PTR;

    /* ����ӵ�ǰפ����plmn��Ϣ��EPlmn�б��� */
    pstPlmnId    = NAS_MML_GetCurrCampPlmnId();
    pstEquPlmnInfo->astEquPlmnAddr[0].ulMcc = pstPlmnId->ulMcc;
    pstEquPlmnInfo->astEquPlmnAddr[0].ulMnc = pstPlmnId->ulMnc;
    pstEquPlmnInfo->ucEquPlmnNum = 1;

    /* ȡ�����෵�ص�EPlmn��Ϣ�������෵�ص�����EPlmn�ĸ���Ϊ15�� */
    if ( (VOS_NULL_PTR != pstAcceptIe)
      && (VOS_NULL_PTR != pstNasMsg) )
    {
        if ((GMM_MMC_ACTION_RAU == enActionType)
         && (GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN_FLG
             == (pstAcceptIe->ulOptionalIeMask
                 & GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN_FLG)))
        {
            pucEPlmnlist = &pstNasMsg->aucNasMsg[pstAcceptIe->
                              aucIeOffset[GMM_RAU_ACCEPT_IE_EQUIVALENT_PLMN]];

            /* ��дPLMN�б���GMM_TRUE */
            if (GMM_TRUE == Gmm_Com_DealOfPlmnList(pucEPlmnlist,
                              (MMCGMM_PLMN_ID_STRU*)&pstEquPlmnInfo->astEquPlmnAddr[1]))
            {
                /* ��ЧPLMN���� */
                pstEquPlmnInfo->ucEquPlmnNum += *((VOS_UINT8 *)pucEPlmnlist + 1) / 3;
            }
        }
        else if ((GMM_MMC_ACTION_ATTACH == enActionType)
              && (GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN_FLG
                  == (pstAcceptIe->ulOptionalIeMask
                    & GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN_FLG)))
        {
            pucEPlmnlist = &pstNasMsg->aucNasMsg[pstAcceptIe->
                              aucIeOffset[GMM_ATTACH_ACCEPT_IE_EQUIVALENT_PLMN]];

            /* ��дPLMN�б���GMM_TRUE */
            if (GMM_TRUE == Gmm_Com_DealOfPlmnList(pucEPlmnlist,
                              (MMCGMM_PLMN_ID_STRU*)&pstEquPlmnInfo->astEquPlmnAddr[1]))
            {
                /* ��ЧPLMN���� */
                pstEquPlmnInfo->ucEquPlmnNum += *((VOS_UINT8 *)pucEPlmnlist + 1) / 3;
            }
        }
        else
        {
        }


        /* ��EPLMN�б���ɾ����Ч ����ֹ�Ͳ��������ε����� */
        pstEquPlmnInfo->ucEquPlmnNum = (VOS_UINT8)NAS_MML_DelInvalidPlmnFromList(
                                          (VOS_UINT32)pstEquPlmnInfo->ucEquPlmnNum,
                                          pstEquPlmnInfo->astEquPlmnAddr);
        pstEquPlmnInfo->ucEquPlmnNum = (VOS_UINT8)NAS_MML_DelForbPlmnInList(
                                          (VOS_UINT32)pstEquPlmnInfo->ucEquPlmnNum,
                                      pstEquPlmnInfo->astEquPlmnAddr);

        return;
    }

    NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_DecodeEquPlmnInfoIE:parameter is null pointer");

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_GMM_WriteRplmnWithRatNvim
 ��������  : дNV: en_NV_Item_RPlmnWithRat
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2011��10��8��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID NAS_GMM_WriteRplmnWithRatNvim(
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo
)
{
    NAS_NVIM_RPLMN_WITH_RAT_STRU        stRplmn;

    stRplmn.ucLastRplmnRat          = pstRplmnCfgInfo->enLastRplmnRat;
    stRplmn.stGRplmn.ulMcc          = pstRplmnCfgInfo->stGRplmnInNV.ulMcc;
    stRplmn.stGRplmn.ulMnc          = pstRplmnCfgInfo->stGRplmnInNV.ulMnc;
    stRplmn.stWRplmn.ulMcc          = pstRplmnCfgInfo->stWRplmnInNV.ulMcc;
    stRplmn.stWRplmn.ulMnc          = pstRplmnCfgInfo->stWRplmnInNV.ulMnc;
    stRplmn.ucLastRplmnRatEnableFlg = pstRplmnCfgInfo->ucLastRplmnRatFlg;

    if (NV_OK != NV_Write(en_NV_Item_RPlmnWithRat, &stRplmn, sizeof(NAS_NVIM_RPLMN_WITH_RAT_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_GMM_WriteRplmnWithRatNvim(): en_NV_Item_RPlmnWithRat Error");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_UpdateGURegRlstRPlmnIdInNV
 ��������  : ע��ɹ���,�ж�Rplmn��Ϣ�Ƿ����˸ı���
 �������  : pstRPlmnId
 �������  : ��
 �� �� ֵ  : VOS_TRUE:rplmn�ı�
             VOS_FALSE:rplmnδ�ı�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��10��08��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsGURplmnChanged(
    NAS_MML_PLMN_ID_STRU               *pstRPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulGRplmnCompareRslt;
    VOS_UINT32                          ulWRplmnCompareRslt;

    /* Ĭ��RPlmn�ȽϽ��δ�����ı� */
    ulGRplmnCompareRslt = VOS_TRUE;
    ulWRplmnCompareRslt = VOS_TRUE;

    /* ���ڻ�ȡRPLMN�Ķ���������Ϣ */
    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* �ж�ȫ�ֱ����е�LastRPLMN�Ľ��뼼���Ƿ����ı� */
    if (enCurrRat != NAS_MML_GetLastRplmnRat())
    {
        /* RPlmn��Ϣ�����˸ı䣬����VOS_TRUE */
        return VOS_TRUE;
    }

    /* �ж�ȫ�ֱ����е�˫RPLMN�Ƿ�֧�� */
    if (VOS_FALSE == pstRplmnCfgInfo->ucMultiRATRplmnFlg)
    {
        ulGRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                 &pstRplmnCfgInfo->stGRplmnInNV);

        ulWRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                 &pstRplmnCfgInfo->stWRplmnInNV);
    }
    else
    {
        /* ֧��˫RPLMN, ��ֻ�ж϶�Ӧ���뼼����RPLMN */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurrRat)
        {
            ulGRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                     &pstRplmnCfgInfo->stGRplmnInNV);
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
        {
            ulWRplmnCompareRslt = NAS_MML_CompareBcchPlmnwithSimPlmn(pstRPlmnId,
                                                     &pstRplmnCfgInfo->stWRplmnInNV);
        }
        else
        {
            ;
        }
    }

    /* RPlmn�ȽϽ����VOS_FALSE��ʾ�����˸ı� */
    if ((VOS_FALSE == ulGRplmnCompareRslt)
     || (VOS_FALSE == ulWRplmnCompareRslt))
    {
        /* RPlmn��Ϣ�����˸ı䣬����VOS_TRUE */
        return VOS_TRUE;
    }

    /* RPlmn��Ϣδ�����ı䣬����VOS_FALSE */
    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertMmlPlmnIdToNvimEquPlmn
 ��������  : ��MML��ʽ��PlmnIDת��ΪNvim��Eplmn
              23002f(MML�ĸ�ʽ Mcc:0x000302,Mnc:0x0f0200)-->2,3,0,0,2,f
 �������  : pstPlmnId: MML��PLMN ID
 �������  : pstNvimPlmnId: NvimEPlmn��ʽ
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2012��03��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
*****************************************************************************/
VOS_VOID NAS_GMM_ConvertMmlPlmnIdToNvimEquPlmn(
    NAS_MML_PLMN_ID_STRU               *pstMmlPlmnId,
    NVIM_PLMN_VALUE_STRU               *pstNvimPlmnId
)
{
    /* ת��MCC */
    pstNvimPlmnId->ucMcc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMcc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMcc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMcc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);

    /* ת��MNC */
    pstNvimPlmnId->ucMnc[0] = (VOS_UINT8)(pstMmlPlmnId->ulMnc & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[1] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 8) & NAS_MML_OCTET_LOW_FOUR_BITS);

    pstNvimPlmnId->ucMnc[2] = (VOS_UINT8)((pstMmlPlmnId->ulMnc >> 16) & NAS_MML_OCTET_LOW_FOUR_BITS);

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertMmlEquListToNvimEquPlmnList
 ��������  : ��MML��ʽ��Eplmn�б�ת��ΪNvim��Eplmn�б�
 �������  : pstMmlEPlmnList: MML��EplmnList
 �������  : pstNvimEPlmnList:Nvim��ʽ��EPlmnList
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2012��03��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
*****************************************************************************/
VOS_VOID NAS_GMM_ConvertMmlEquListToNvimEquPlmnList(
    NAS_MML_EQUPLMN_INFO_STRU          *pstMmlEPlmnList,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList
)
{
    VOS_UINT8                           i;

    pstNvimEPlmnList->ucCount = pstMmlEPlmnList->ucEquPlmnNum;

    if (pstNvimEPlmnList->ucCount > NVIM_MAX_EPLMN_NUM)
    {
        pstNvimEPlmnList->ucCount = NVIM_MAX_EPLMN_NUM;
    }

    for (i = 0; i < pstNvimEPlmnList->ucCount; i++)
    {
        NAS_GMM_ConvertMmlPlmnIdToNvimEquPlmn(&(pstMmlEPlmnList->astEquPlmnAddr[i]),
                                              &(pstNvimEPlmnList->struPlmnList[i]));

    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsInNvEplmnList
 ��������  : �ж�PLMN ID�Ƿ���NV�е�EPLMN LIST�б���
 �������  : pstPlmnId:��Ҫ�жϵ�PLMN ID
             ucPlmnNum:PLMN ID����
             pstPlmnIdList:PLMN ID�б�
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : PLMN ID��NV�е�EPLMN LIST�б���
             VOS_FALSE : PLMN ID����NV�е�EPLMN LIST�б���
 ���ú���  :
 ��������  :
 �޸���ʷ      :
    1.��    ��   : 2012��03��15��
      ��    ��   : l00130025
      �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsInNvEplmnList(
    NVIM_PLMN_VALUE_STRU               *pstPlmnId,
    VOS_UINT8                           ucPlmnNum,
    NVIM_PLMN_VALUE_STRU               *pstPlmnIdList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < ucPlmnNum ; i++ )
    {
        if ( (pstPlmnId->ucMcc[0] == pstPlmnIdList[i].ucMcc[0])
          && (pstPlmnId->ucMcc[1] == pstPlmnIdList[i].ucMcc[1])
          && (pstPlmnId->ucMcc[2] == pstPlmnIdList[i].ucMcc[2])
          && (pstPlmnId->ucMnc[0] == pstPlmnIdList[i].ucMnc[0])
          && (pstPlmnId->ucMnc[1] == pstPlmnIdList[i].ucMnc[1])
          && (pstPlmnId->ucMnc[2] == pstPlmnIdList[i].ucMnc[2]) )
        {
            return VOS_TRUE;
        }
    }
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNvimEPlmnListEqual
 ��������  : �ж�2��NVIM_EQUIVALENT_PLMN_LIST_STRU�Ƿ���ͬ
 �������  : pstNvimEPlmnList1,pstNvimEPlmnList2���Ƚϵ�2��NvimPlmnList
 �������  : ��
 �� �� ֵ  : VOS_TRUE  : 2��EplmnList��ͬ
              VOS_FALSE : 2��EplmnList��ͬ
 ���ú���  :
 ��������  :
 �޸���ʷ      :
    1.��    ��   : 2012��03��15��
      ��    ��   : l00130025
      �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNvimEPlmnListEqual(
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList1,
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNvimEPlmnList2
)
{
    VOS_UINT32                          i;

    if (pstNvimEPlmnList1->ucCount != pstNvimEPlmnList2->ucCount)
    {
        return VOS_FALSE;
    }

    /* Eplmn��������0,��Rplmn��ͬʱ��EplmnList����ͬ */
    if (pstNvimEPlmnList1->ucCount > 0)
    {
        if (VOS_FALSE == NAS_GMM_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[0]),
                                                 1,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        return VOS_TRUE;
    }

    /* ����Eplmnû�н������������ظ����ݣ���Ҫ�Ա�2���б����ȷ����ͬ */
    for ( i = 1 ; i < pstNvimEPlmnList1->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_GMM_IsInNvEplmnList(&(pstNvimEPlmnList1->struPlmnList[i]),
                                                 pstNvimEPlmnList2->ucCount,
                                                 pstNvimEPlmnList2->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    for ( i = 1 ; i < pstNvimEPlmnList2->ucCount ; i++ )
    {
        if (VOS_FALSE == NAS_GMM_IsInNvEplmnList(&(pstNvimEPlmnList2->struPlmnList[i]),
                                                 pstNvimEPlmnList1->ucCount,
                                                 pstNvimEPlmnList1->struPlmnList))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_WriteEplmnNvim
 ��������  : ��Eplmn���µ�NV��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��10��08��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012021407803,Eplmnά���޸ģ������ֶ�������ѡ���ܴ�����ѭ��
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID NAS_GMM_WriteEplmnNvim(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnAddr
)
{
    VOS_UINT32                          ulUpdateNvFlag;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstNewNvEquPlmnList = VOS_NULL_PTR;
    NVIM_EQUIVALENT_PLMN_LIST_STRU     *pstOldNvEquPlmnList = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulUpdateNvFlag  = VOS_FALSE;
    ulLength        = 0;

    pstNewNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                      WUEPS_PID_GMM,
                                                      sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstNewNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_WriteEplmnNvim:ERROR: Memory Alloc Error");
        return;
    }

    pstOldNvEquPlmnList = (NVIM_EQUIVALENT_PLMN_LIST_STRU*)PS_MEM_ALLOC(
                                                        WUEPS_PID_GMM,
                                                        sizeof (NVIM_EQUIVALENT_PLMN_LIST_STRU));

    if (VOS_NULL_PTR == pstOldNvEquPlmnList)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_WriteEplmnNvim:ERROR: Memory Alloc Error");
        PS_MEM_FREE(WUEPS_PID_GMM, pstNewNvEquPlmnList);
        return;
    }

    PS_MEM_SET(pstNewNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));
    PS_MEM_SET(pstOldNvEquPlmnList, 0, sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU));

    NAS_GMM_ConvertMmlEquListToNvimEquPlmnList(pstEplmnAddr,
                                               pstNewNvEquPlmnList);

    (VOS_VOID)NV_GetLength(en_NV_Item_EquivalentPlmn, &ulLength);

    /* ��ȡNV��EPLMN��Ϣ */
    if ( NV_OK == NV_Read(en_NV_Item_EquivalentPlmn,
                         pstOldNvEquPlmnList, ulLength) )
    {
        if (VOS_FALSE == NAS_GMM_IsNvimEPlmnListEqual(pstNewNvEquPlmnList,
                                                      pstOldNvEquPlmnList))
        {
            ulUpdateNvFlag = VOS_TRUE;
        }
    }
    else
    {
        ulUpdateNvFlag = VOS_TRUE;
    }

    if ( VOS_TRUE == ulUpdateNvFlag )
    {
        if (NV_OK != NV_Write(en_NV_Item_EquivalentPlmn,
                              pstNewNvEquPlmnList,
                              sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)))
        {
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_WriteEplmnNvim:WARNING: en_NV_Item_EquivalentPlmn Error");
        }
    }

    PS_MEM_FREE(WUEPS_PID_GMM, pstNewNvEquPlmnList);
    PS_MEM_FREE(WUEPS_PID_GMM, pstOldNvEquPlmnList);



}


/*****************************************************************************
 �� �� ��  : NAS_GMM_NotifyMmUnrealCombinedRauResult
 ��������  : ��PSΪ��������ʱ,֪ͨMMģ������ע����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��10��08��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_NotifyMmUnrealCombinedRauResult()
{
    NAS_GMM_SndMmCombinedRauInitiation();

    if (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
    {
        NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_PS_ONLY,
                                       NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE,
                                       VOS_NULL_PTR,
                                       VOS_NULL_PTR);                              /* ����MMCGMM_COMBINED_RAU_ACCEPTED��MMC    */

    }
    else
    {
        NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                       NAS_MML_REG_FAIL_CAUSE_NULL,
                                       VOS_NULL_PTR,
                                       VOS_NULL_PTR);                              /* ����MMCGMM_COMBINED_RAU_ACCEPTED��MMC    */
    }

    return;
}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_GMM_IsT3412ExpiredNeedRegist
 ��������  : T3412��ʱ����ģʽI�Ƿ���Ҫ����RAU
 �������  : enLteCsServiceCfg - UE֧�ֵ�cs ҵ������
             enTinType         - TIN����
             enT3412Status     - T3412��ʱ��״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ����ע��
             VOS_FALSE - ����Ҫ����ע��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��5��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsT3412ExpiredNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3412Status
)
{
     /* 3GPP 24.008��4.7.5.2.1 Combined routing area updating procedure initiation�½��������£�
        when the MS is configured to use CS fallback and SMS over SGs,
        or SMS over SGs only, the TIN indicates "RAT-related TMSI" and the
        periodic tracking area update timer T3412 expires;
    */
    if ((NAS_MML_TIMER_EXP == enT3412Status)
     && ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsT3423StatusChangeNeedRegist
 ��������  : T3423������ʱ��ʱ����ģʽI�Ƿ���Ҫ����RAU
 �������  : enLteCsServiceCfg - UE֧�ֵ�cs ҵ������
             enTinType         - TIN����
             enT3423Status     - T3423��ʱ��״̬
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ����ע��
             VOS_FALSE - ����Ҫ����ע��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��5��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsT3423StatusChangeNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3423Status
)
{
     /*
        3GPP 24.008��4.7.5.2.1 Combined routing area updating procedure initiation�½��������£�
        when the MS which is configured to use CS fallback and SMS over SGs,
        or SMS over SGs only, enters a GERAN or UTRAN cell, the TIN indicates
        "RAT-related TMSI", and the E-UTRAN deactivate ISR timer T3423 is running.

        when the MS which is configured to use CS fallback and SMS over SGs,
        or SMS over SGs only, enters a GERAN or UTRAN cell and the E-UTRAN deactivate
        ISR timer T3423 has expired.
    */
    if (((NAS_MML_TIMER_START == enT3423Status)
      || (NAS_MML_TIMER_EXP == enT3423Status))
     && ((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == enLteCsServiceCfg)
      || (NAS_MML_LTE_SUPPORT_SMS_OVER_SGS_ONLY == enLteCsServiceCfg))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType))
    {
        /* GMM��ǰ���㷢��RAU���� */
        if (VOS_TRUE == NAS_GMM_IsAbleCombinedRau_TimerStatusChg())
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_WriteTinInfoNvim
 ��������  : ����TIN INFO�����ݵ�NVIM
 �������  : enTinType - TIN����
             pucImsi   - IMSI
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��1��8��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��5��17��
   ��    ��   : l00167671
   �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID  NAS_GMM_WriteTinInfoNvim(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    /* Modified by l00167671 for NV�����Ŀ , 2013-05-17, begin */
    NAS_NVIM_TIN_INFO_STRU              stTinInfo;
    /* Modified by l00167671 for NV�����Ŀ , 2013-05-17, end*/

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /*
        The following EMM parameter shall be stored in a non-volatile memory in the
        ME together with the IMSI from the USIM:
        -   TIN.
        This EMM parameter can only be used if the IMSI from the USIM matches the
        IMSI stored in the non-volatile memory of the ME; else the UE shall delete
        the EMM parameter.
    */

    if (pstRplmnCfgInfo->enTinType != enTinType)
    {
        /* �ȸ���MML�Ĳ��� */
        pstRplmnCfgInfo->enTinType  = enTinType;
        PS_MEM_CPY(pstRplmnCfgInfo->aucLastImsi, pucImsi, sizeof(pstRplmnCfgInfo->aucLastImsi));

        /* �ٸ���NVIM�еĲ��� */
        stTinInfo.ucTinType        = pstRplmnCfgInfo->enTinType;
        PS_MEM_CPY(stTinInfo.aucImsi, pstRplmnCfgInfo->aucLastImsi, sizeof(stTinInfo.aucImsi));
        PS_MEM_SET(stTinInfo.aucReserve, 0, sizeof(stTinInfo.aucReserve));

        /* ������NVIM�� */
        if (NV_OK != NV_Write (en_NV_Item_TIN_INFO,
                               &stTinInfo,
                               sizeof(stTinInfo)))
        {
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_WriteTinInfoNvim:Write NV Failed");
        }

        /* ��ά�ɲ�������Ϣ��ӡ */
        NAS_GMM_LogTinTypeInfo(enTinType);
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedDeactiveIsr_InterSys
 ��������  : L��GU��ϵͳ�任ʱ�ж��Ƿ����ISR����󼤻��ps���أ��������Ҫȥ����ISR
 �������  : ucPreRat        - ����ǰ���뼼��
             enCurrNetType   - ��ǰ���뼼��
             enSuspendCause  - ����ԭ�������������gu�ģ���MMC_SUSPEND_CAUSE_BUTT
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫȥ����ISR
             VOS_FALSE - ����Ҫȥ����ISR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��15��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��6��5��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedDeactiveIsr_InterSys(
    VOS_UINT8                           ucPreRat,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType,
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
)
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType = NAS_MML_GetTinType();

    /* δ������ϵͳֱ�ӷ��ز���ȥ����ISR */
    if (ucPreRat == enCurrNetType)
    {
        return VOS_FALSE;
    }

    /* �������L��GU����ϵͳ�任���߲���L�³���������������GU������ISRδ�����ֱ�ӷ���VOS_FALSE,����Ҫȥ����ISR */
    if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI != enTinType)
     || (NAS_MML_NET_RAT_TYPE_LTE != ucPreRat))
    {
        return VOS_FALSE;
    }

    /* 3GPP 24301 6.1.5 Coordination between ESM and EMM for supporting ISR����:
      This subclause applies to a UE with its TIN set as "RAT related TMSI" for which ISR is activated.
      The UE shall change its TIN to "GUTI" to deactivate ISR:
    -  at the time when the UE changes from S1 mode to A/Gb mode or Iu mode,
       if any EPS bearer context activated after the ISR was activated in the UE exists;*/
    if (VOS_TRUE == NAS_MML_IsPsBearerAfterIsrActExist())
    {
        return VOS_TRUE;
    }

    /* 24008_CR2116R3_(Rel-11)_C1-122223 24008 4.7.5.1�½���������:
    - in A/Gb mode, after intersystem change from S1 mode via cell change order
    procedure not due to CS fallback, if the TIN indicates "RAT-related TMSI";
    in this case the MS shall set the TIN to "GUTI" before initiating
    the routing area updating procedure.*/
    if ((VOS_FALSE == NAS_MML_IsCsfbServiceStatusExist())
     && (MMC_SUSPEND_CAUSE_CELLCHANGE == enSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurrNetType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_LogTinTypeInfo
 ��������  : GMM ����TIN����ʱ��Ҫ����Ϣ������trace��
 �������  : enTinType - TIN����
 �������  : ��
 �� �� ֵ  : VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_LogTinTypeInfo(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
)
{
    NAS_GMM_LOG_TIN_INFO_STRU          *pstTinTypeInfo = VOS_NULL_PTR;

    pstTinTypeInfo = (NAS_GMM_LOG_TIN_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                             sizeof(NAS_GMM_LOG_TIN_INFO_STRU));

    if ( VOS_NULL_PTR == pstTinTypeInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogTinTypeInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstTinTypeInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstTinTypeInfo->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstTinTypeInfo->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstTinTypeInfo->stMsgHeader.ulLength        = sizeof(NAS_GMM_LOG_TIN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;;
    pstTinTypeInfo->stMsgHeader.ulMsgName       = NAS_GMM_LOG_TIN_TYPE_INFO_IND;

    pstTinTypeInfo->enTinType = enTinType;

    DIAG_TraceReport(pstTinTypeInfo);

    PS_MEM_FREE(WUEPS_PID_GMM, pstTinTypeInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedDeactiveISR_RauAccept
 ��������  : ��RAU�����Ƿ���Ҫȥ��� �Ա�����䵽L�¿��Է���TAU
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ���Ҫ�޸�Tin type,���ȥ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��17��
    ��    ��   : f00261443
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_GMM_IsNeedDeactiveISR_RauAccept(VOS_VOID)
{
    VOS_UINT8                                               ucImsVoiceMMEnableFlg;
    VOS_UINT8                                               ucImsVoiceAvailFlg;
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainPreference;
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8                     enGUNwImsVoiceSupport;
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8                     enLNwImsVoiceSupport;

    ucImsVoiceMMEnableFlg   = NAS_MML_GetImsVoiceMMEnableFlg();
    ucImsVoiceAvailFlg      = NAS_MML_GetImsVoiceAvailFlg();
    enVoiceDomainPreference = NAS_MML_GetVoiceDomainPreference();
    enGUNwImsVoiceSupport   = NAS_MML_GetGUNwImsVoiceSupportFlg();
    enLNwImsVoiceSupport    = NAS_MML_GetLteNwImsVoiceSupportFlg();

    /* ISR����ʱ,������������������TINΪPTMSI,��֤��ѡ��LTE����TAU */
    /* 24008 Э�鳡��:
       1)ISRû���� MS֧��L ��Ӧ�ð�TIN��Ϊ"P-TMSI"
       2)ISR���� ����p.5������TINΪ"P-TMSI"
    */
    /* 24008 ��¼P.5����
       ����������������֮һ
       ����1��
       1)MMAָʾIMS VOICE����
       2)UE��IMS �����ն˵��ƶ��Թ���NV���ô�
       3)GU��L��IMS VOICE��һ��֧����������ѡ��ΪCS ONLY
       4)��ǰ��W��
       ����2��
       1)MMAָʾIMS VOICE����
       2)UE��IMS �����ն˵��ƶ��Թ���NV���ô�
       3)W��L��֧��IMS VOICE��GU��L����һ����������ѡ��ΪCS ONLY
    */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA         == NAS_MML_GetCurrNetRatType())
     && (VOS_TRUE                           == ucImsVoiceMMEnableFlg)
     && (VOS_TRUE                           == ucImsVoiceAvailFlg)
     && (NAS_MML_CS_VOICE_ONLY              != enVoiceDomainPreference)
     && ((NAS_MML_NW_IMS_VOICE_SUPPORTED    == enGUNwImsVoiceSupport)
      || (NAS_MML_NW_IMS_VOICE_SUPPORTED    == enLNwImsVoiceSupport)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsISRActived_RauAccept
 ��������  : �ж�Rau���֮���Ƿ��Ѽ���ISR
 �������  : ucUpdateResultValue - Rau accept��Ϣ��Update result information element IE����
 �������  : ��
 �� �� ֵ  : �Ƿ��Ѿ�����ISR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : f00261443
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��6��4��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT8 NAS_GMM_IsISRActived_RauAccept(VOS_UINT8 ucUpdateResultValue)
{

    VOS_UINT32                                              ulPlatformSuppLteFlg;
    VOS_UINT8                                               ucIsrSupport;

    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3412Status;
    VOS_INT8                                                cVersion;

    cVersion      = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);
    enT3412Status = NAS_MML_GetT3412Status();

    ucIsrSupport        = NAS_MML_GetIsrSupportFlg();

    ulPlatformSuppLteFlg = NAS_MML_IsPlatformSupportLte();

    /* 24008_CR1528R2_(Rel-10)_C1-102727-rev-C1-102388 24008 4.7.5.1.3��������:
    If the ROUTING AREA UPDATE ACCEPT message contains
    i)  no indication that ISR is activated, an MS supporting S1 mode shall set the TIN to "P-TMSI"; or
    ii) an indication that ISR is activated, the MS shall regard the available GUTI and
    TAI list as valid and registered with the network. If the TIN currently indicates "GUTI" and
    the periodic tracking area update timer T3412 is running, the MS shall set the
    TIN to "RAT-related TMSI". If the TIN currently indicates "GUTI" and the periodic
    tracking area update timer T3412 has already expired, the MS shall set the TIN
    to "P-TMSI".*/
    if (((GMM_RA_UPDATED_ISR_ACTIVE             == ucUpdateResultValue)
      || (GMM_COMBINED_RALA_UPDATED_ISR_ACTIVE  == ucUpdateResultValue))
     && (VOS_TRUE                               == ulPlatformSuppLteFlg)
     && (VOS_TRUE                               == ucIsrSupport)
     && ((cVersion <= PS_PTL_VER_R9)
      || (NAS_MML_TIMER_EXP != enT3412Status)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_UpdateTinType_RauAccept
 ��������  : GMM�յ�rau accept��Ϣʱ����TIN����
 �������  : enTinType           - TIN����
             pucImsi             - imsi����
             ucUpdateResultValue - Rau accept��Ϣ��Update result information element IE����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��21��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��28��
    ��    ��   : s46746
    �޸�����   : DSDA GUNAS C CORE��Ŀ������ƽ̨�����ж�
  3.��    ��   : 2013��05��23��
    ��    ��   : z00234330
    �޸�����   : DTS2013052301419������IsR�Ƿ�֧�ֵ��ж�
  4.��    ��   : 2013��12��17��
    ��    ��   : f00261443
    �޸�����   : ������ϵͳ�� L �£�ȥ����ISR��RAU�������Tin����
                 ΪP-TMSI�ĳ���
*****************************************************************************/
VOS_VOID NAS_GMM_UpdateTinType_RauAccept(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi,
    VOS_UINT8                           ucUpdateResultValue
)
{


    /* RAU��ɺ��Ƿ񼤻�ISR */
    if (VOS_TRUE == NAS_GMM_IsISRActived_RauAccept(ucUpdateResultValue))
    {
        /* �Ƿ���Ҫȥ����ISR */
        if (VOS_TRUE == NAS_GMM_IsNeedDeactiveISR_RauAccept())
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pucImsi);
            Gmm_TimerStop(GMM_TIMER_T3323);
            /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);

            return;
        }

        /* ISR�Ѿ����� */
        if (NAS_MML_TIN_TYPE_GUTI == enTinType)
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_RAT_RELATED_TMSI, pucImsi);
        }

        return;
    }

    /* û�м���ISR */
    NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pucImsi);
    Gmm_TimerStop(GMM_TIMER_T3323);
    /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
    NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsAbleCombinedRau_TimerStatusChg
 ��������  : GMM�յ�T3412��ʱ����ʱ��T3423�����л�T3423��ʱ�Ƿ��ܷ�������rau
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -  ���㷢��RAU
             VOS_FALSE - �����㷢��RAU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��21��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsAbleCombinedRau_TimerStatusChg(VOS_VOID)
{
    VOS_UINT8                           ucSimCsRegStatus;

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {
         /* �����ǰ��������ģʽI��cs ps mode�����ز����㷢��RAU���� */
         return VOS_FALSE;
    }

    if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
     || (VOS_FALSE == ucSimCsRegStatus)
     || (VOS_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
    {
        /* ���csע�ᱻ����cs����Ч��cs��ͨ�������У����ز����㷢��RAU����  */
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsrActiveRaiNoChgBeforeT3312Exp_InterSys
 ��������  : ISR����·����δ�ı䣬idle̬��L��ϵͳ��GU,T3312δ��ʱ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��3��21��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��08��24��
   ��    ��   : m00217266
   �޸�����   : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
 3.��    ��   : 2013��2��4��
   ��    ��   : w00176964
   �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 4.��    ��   : 2013��11��1��
   ��    ��   : z00161729
   �޸�����   : DTS2013110103529:L�ؽ���gu��ISR����λ����δ�ı䣬gmmδ����rau
 5.��    ��   : 2014��01��10��
   ��    ��   : f00261443
   �޸�����   : VoLTE_PhaseIII��Ŀ
 6.��    ��   : 2014��04��08��
   ��    ��   : s00217060
   �޸�����   : DTS2014040901544:PS��ע�ᱻ��#111,�������T3302��ʱ��ʱ��Ϊ0�������ͷ����յ�ϵͳ��Ϣʱ��UEһֱ����ATTACH
*****************************************************************************/
VOS_VOID NAS_GMM_IsrActiveRaiNoChgBeforeT3312Exp_InterSys(VOS_VOID)
{
    VOS_UINT8                                               ucCsRestrictionFlg;
    VOS_UINT8                                               ucCsAttachAllow;
    VOS_UINT8                                               ucSimCsRegStatus;
    VOS_UINT8                                               ucImsVoiceMMEnableFlg;
	VOS_UINT8                                               ucImsVoiceAvailFlg;
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8                     enImsSupportInLTE;
    NAS_MML_VOICE_DOMAIN_PREFERENCE_ENUM_UINT8              enVoiceDomainPreference;
    VOS_UINT8                                               ucOldSpecProc;

    ucCsAttachAllow    = NAS_MML_GetCsAttachAllowFlg();
    ucSimCsRegStatus   = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictionFlg = NAS_MML_GetCsRestrictRegisterFlg();

    /* 24008 4.7.5��in Iu mode and A/Gb mode after intersystem change from S1 mode,
       and the GMM receives an indication of "RRC connection failure" from lower layers due to
       lower layer failure while in S1 mode;
       ���LTE�ؽ��ɹ����ISR����λ����δ�ı䣬gmm�жϸñ�ʶΪ1��Ҫ����rau */

    /* �����������T3302��ʱ��ʱ��Ϊ0ʱ������T3302��ʱ��������������һ���жϣ�UE��һֱ����ATTACH */
    if ((VOS_TRUE == Nas_GetLrrcConnFailureFlag())
     && (GMM_TIMER_T3302_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
     && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
    {
        /**
          * 24301�ж��ڴ�L��ϵͳ�任��U�£�������RAU�ĳ�����
          * If the TRACKING AREA UPDATE ACCEPT message contains:
          * i)  no indication that ISR is activated, the UE shall set the TIN to "GUTI";
          * ii) an indication that ISR is activated, then:
          * -   if the UE is required to perform routing area updating for IMS voice
          * termination as specified in 3GPP TS 24.008 [13], annex P.5,
          * the UE shall set the TIN to "GUTI";

          * 24008�й涨��
          * ֧��IMS���ն˴�L��䵽G�£���Tin Type Ϊ RAT-related TIN,����Ҫ����RAU,��p.4
          * P.4
          * 1)�豸֧�� IMS Voice
          * 2)L������֧��ImsVoice
          * 3)������ѡ���� CS Only
          * ĿǰGU�²�֧��IMS�������L��ISR����ʱ����Э��L��Ȼȥ����ISR������g��
          ����Ȼ����RAU�����Ŀǰ�������÷�֧,���ں�����չ.
          */
        ucImsVoiceMMEnableFlg = NAS_MML_GetImsVoiceMMEnableFlg();
        ucImsVoiceAvailFlg = NAS_MML_GetImsVoiceAvailFlg();
        enImsSupportInLTE = NAS_MML_GetLteNwImsVoiceSupportFlg();
        enVoiceDomainPreference = NAS_MML_GetVoiceDomainPreference();

        if ( (VOS_TRUE == ucImsVoiceMMEnableFlg)
          && (VOS_TRUE == ucImsVoiceAvailFlg)
          && (NAS_MML_NW_IMS_VOICE_SUPPORTED == enImsSupportInLTE)
          && (NAS_MML_CS_VOICE_ONLY != enVoiceDomainPreference))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

            return;
        }
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)
         || (VOS_TRUE == ucCsRestrictionFlg))
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;

            /* ��MMC����PSע���� */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_NULL);

            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        }
        else
        {
            if (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
            {
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                {                                                       /* ��Ҫ��SM��EST_CNF                        */
                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);    /* ��SM�ؽ����ɹ�����Ӧ                     */
                }

                if (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                {                                                       /* CS������ע��                             */
                    NAS_GMM_SndMmCombinedRauInitiation();
                    NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                                   NAS_MML_REG_FAIL_CAUSE_NULL,
                                                   VOS_NULL_PTR,
                                                   VOS_NULL_PTR);
                }

                /* ��MMC����PSע���� */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                             NAS_MML_REG_FAIL_CAUSE_NULL);

            }
            else
            {
                /* sim��Ч����CS������ע�� */
                if ((VOS_FALSE == ucCsAttachAllow)
                 || (VOS_TRUE != ucSimCsRegStatus))
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                    {                                                   /* ��Ҫ��SM��EST_CNF                        */
                        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                        Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);        /* ��SM�ؽ����ɹ�����Ӧ                     */
                    }
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;

                    /* ��MMC����PSע���� */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }
            }
        }
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;       /* ���������̱�־ */
    }
    else
    {
        if (GMM_TIMER_T3302_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        {
            Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);

            ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
            g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

            /* ��MMC����PSע���� */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                NAS_GMM_NotifyMmUnrealCombinedRauResult();
            }

            g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
            g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        }
        else
        {
            /* PS����״̬����GU1 */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }

    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsrActiveRaiNoChgAfterT3312Exp_InterSys
 ��������  : ISR����·����δ�ı䣬idle̬��L��ϵͳ��GU,T3312��ʱ�Ĵ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��2��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*****************************************************************************/
VOS_VOID NAS_GMM_IsrActiveRaiNoChgAfterT3312Exp_InterSys(VOS_VOID)
{
    /* NMO1��,��ͨ���ֻ�ģʽ�ж��Ƿ���Ҫ��������ע�� */
    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {
        /* ��A+I */
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {
        /* A+I */
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsrActiveRaiNoChg_InterSys
 ��������  : ISR����·����δ�ı䣬idle̬��L��ϵͳ��GU�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��21��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_IsrActiveRaiNoChg_InterSys(VOS_VOID)
{
    if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
    {
        NAS_GMM_IsrActiveRaiNoChgBeforeT3312Exp_InterSys();
        return;
    }

    NAS_GMM_IsrActiveRaiNoChgAfterT3312Exp_InterSys();
    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_IsRegNeedFillVoiceDomainPreferenceAndUeUsageSettingIE
 ��������  : �ж��Ƿ�attach��rauע����Ϣ���Ƿ���Ҫ��װVoice domain preference and UE's usage setting IE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��4��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRegNeedFillVoiceDomainPreferenceAndUeUsageSettingIE(VOS_VOID)
{
    VOS_UINT32                                  ulSupportLteFlg;
    VOS_UINT8                                   ucImsVoiceSupportFlag;

    ucImsVoiceSupportFlag = NAS_MML_IsUeSupportImsVoice();
    ulSupportLteFlg       = NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE);

    /* 24008_CR1678R2_(Rel-10)_C1-105172 rev of  C1-104874 rev of C1-104734 Correcting voice domain prefs IE conditions-Rel-10
    24008 9.4.1.11��9.4.14.16�½���������:
    This IE shall be included:
    -   if the MS supports CS fallback and SMS over SGs, or the MS is configured
        to support IMS voice, or both; and
    -   if the MS is E-UTRAN capable.*/
    if (((NAS_MML_LTE_SUPPORT_CSFB_AND_SMS_OVER_SGS == NAS_MML_GetLteCsServiceCfg())
       || (VOS_TRUE == ucImsVoiceSupportFlag))
     && (VOS_TRUE == ulSupportLteFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_LogGasGmmRadioAccessCapability
 ��������  : ����NAS����GAS�Ľӿ�GASGCOM_GetMsCapability
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��21��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_LogGasGmmRadioAccessCapability(
    VOS_UINT32                          ulRst,
    VOS_UINT8                           ucMsCapType,
    VOS_UINT16                          usSize,
    VOS_UINT8                          *pucData
)
{
    NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU                  *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                                         sizeof(NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogGasGmmRadioAccessCapability:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_GMM_LOG_GAS_RADIO_ACCESS_CAP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = GMMOM_LOG_RADIAO_ACCESS_CAP;

    pstMsg->ulRst                       = ulRst;
    pstMsg->ucMsCapType                 = ucMsCapType;
    pstMsg->usSize                      = usSize;

    PS_MEM_CPY(pstMsg->aucData, pucData, usSize);

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_GMM, pstMsg);

    return;
}


#endif

/*****************************************************************************
 �� �� ��  : NAS_GMM_StopT3311InIuPmmConnMode_T3312Exp
 ��������  : w����pmm connected modeʱ���t3312��ʱ����ʱ�����T3311�����У�ֹͣT3311
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��4��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_GMM_StopT3311InIuPmmConnMode_T3312Exp(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;

    /* ȡ�õ�ǰ�Ľ���ģʽ */
    enCurrRat     = NAS_MML_GetCurrNetRatType();

    /* ȡ�õ�ǰ��������Ϣ */
    pstConnStatus = NAS_MML_GetConnStatus();

    /* 24008_CR1735R3_(Rel-10)_C1-111529 was 1470 was 1012 24008-a10 24008 4.7.5.1.5�½���������:
    If in addition the ROUTING AREA UPDATE REQUEST message indicated "periodic updating",
    -   in Iu mode, the timer T3311 may be stopped when the MS enters PMM-CONNECTED mode;
    -   in A/Gb mode, the timer T3311 may be stopped when the READY timer is started.*/
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat)
     && (VOS_TRUE == pstConnStatus->ucPsSigConnStatusFlg)
     && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_DeleteRandAndResInfoInPmmIdleMode
 ��������  : w��pmm idle mode��Ҫɾ��rand ��res��Ϣ��ֹͣT3316
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��4��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_GMM_DeleteRandAndResInfoInPmmIdleMode(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus = NAS_MML_GetConnStatus();

    /* 24008_CR2084_(Rel-11)_C1-120652 24008 4.7.7.2��������:
    The RAND and RES values stored in the mobile station shall be deleted and
    timer T3316, if running, shall be stopped: -if the mobile station enters
    PMM-IDLE mode (Iu mode only).*/
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (VOS_FALSE == pstConnStatus->ucPsSigConnStatusFlg))
    {
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;
        Gmm_TimerStop(GMM_TIMER_T3316);
    }
    return;
}

#if   (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_GMM_IsRegNeedFillOldLocationAreaIdentificationIE
 ��������  : �ж�ATTCH��rau�����Ƿ���ҪЯ��Old location area identification IE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRegNeedFillOldLocationAreaIdentificationIE(VOS_VOID)
{
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   enSpecProc;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    pstCsSuccLai = NAS_MML_GetCsLastSuccLai();
    enSpecProc   = NAS_GMM_GetSpecProc();
    enMsMode     = NAS_MML_GetMsMode();

    /* 24008_CR1986R5_(Rel-10)_C1-115368 ��24008_CR1987R4_(Rel-11)_C1-115328 24008
    4.7.3.2.1�½���������:
    If the MS has stored a valid LAI and the MS supports EMM combined procedures,
    the MS shall include it in the Old location area identification IE in the ATTACH REQUEST message.
    4.7.5.2.1�½���������:
    If the MS has stored a valid LAI and the MS supports EMM combined procedures,
    the MS shall include it in the Old location area identification IE in the ROUTING AREA UPDATE REQUEST message.*/
    if (PS_PTL_VER_R11 > NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS))
    {
        return VOS_FALSE;
    }

    /* ��֧��EMM Combined procedures capability(֧��LTE��ģʽΪCS_PSʱ��Ϊ֧��),
       ����ҪЯ��Old location area identification IE*/
    if (VOS_FALSE == NAS_MML_IsNetRatSupported(NAS_MML_NET_RAT_TYPE_LTE))
    {
        return VOS_FALSE;
    }

    if (NAS_MML_MS_MODE_PS_CS != enMsMode)
    {
        return VOS_FALSE;
    }

    /* ��������ע�����̣�����ҪЯ��Old location area identification IE */
    if ((GMM_RAU_COMBINED != enSpecProc)
     && (GMM_RAU_WITH_IMSI_ATTACH != enSpecProc)
     && (GMM_ATTACH_COMBINED != enSpecProc)
     && (GMM_ATTACH_WHILE_IMSI_ATTACHED != enSpecProc))
    {
        return VOS_FALSE;
    }

    /* LAI�Ƿ�����ҪЯ��,����ҪЯ��Old location area identification IE */
    if (( NAS_MML_LAC_LOW_BYTE_INVALID == pstCsSuccLai->aucLac[0])
     && ( NAS_MML_LAC_HIGH_BYTE_INVALID == pstCsSuccLai->aucLac[1]))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_FillOldLocationAreaIdentificationIE
 ��������  : ���ATTCH��rau�����Old location area identification��IE����
 �������  : pucAddr - ��װIE��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : ��д��IE�ĳ���ucNumber
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT8 NAS_GMM_FillOldLocationAreaIdentificationIE(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucLen;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;

    pstCsSuccLai = NAS_MML_GetCsLastSuccLai( );
    ucLen        = 0;

    /* ��IE�ṹ�μ�24008 10.5.5.30�½����� */
    pucAddr[ucLen++] = NAS_GMM_IEI_OLD_LOCATION_AREA_IDENTIFICATION;
    pucAddr[ucLen++] = NAS_GMM_IE_OLD_LOCATION_AREA_IDENTIFICATION_LEN;

    pucAddr[ucLen] |= (VOS_UINT8)(0x0000000f & pstCsSuccLai->stPlmnId.ulMcc);

    pucAddr[ucLen++] |= (VOS_UINT8)((0x00000f00 & pstCsSuccLai->stPlmnId.ulMcc) >> NAS_MML_OCTET_MOVE_FOUR_BITS);
    pucAddr[ucLen]   |= (VOS_UINT8)((0x000f0000 & pstCsSuccLai->stPlmnId.ulMcc) >> NAS_MML_OCTET_MOVE_SIXTEEN_BITS);
    pucAddr[ucLen++] |= (VOS_UINT8)((0x000f0000 & pstCsSuccLai->stPlmnId.ulMnc) >> NAS_MML_OCTET_MOVE_TWELVE_BITS);
    pucAddr[ucLen]   |= (VOS_UINT8)(0x0000000f & pstCsSuccLai->stPlmnId.ulMnc );
    pucAddr[ucLen++] |= (VOS_UINT8)((0x00000f00 & pstCsSuccLai->stPlmnId.ulMnc) >> NAS_MML_OCTET_MOVE_FOUR_BITS);

    /* ����LAC��8λ */
    pucAddr[ucLen++] = (VOS_UINT8)(pstCsSuccLai->aucLac[0]);

    /* ����LAC��8λ */
    pucAddr[ucLen++] = (VOS_UINT8)pstCsSuccLai->aucLac[1];

    return ucLen;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_GMM_SaveGprsTimer3Value
 ��������  : ����T3312��ʱ��ʱ��
 �������  : ucTimerName     - ��ʱ������
             ucMsgTimerValue - ��Ϣ�ж�ʱ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_GMM_SaveGprsTimer3Value(
    VOS_UINT8                            ucTimerName,
    VOS_UINT8                            ucMsgTimerValue
)
{
    VOS_UINT8                            ucTimerUnit;                                                   /* ������ʱ�����洢ʱ����λ                 */
    VOS_UINT8                            ucTimerValue;                                                   /* ������ʱ�����洢ʱ��                     */


    ucTimerUnit     = 0;
    ucTimerValue    = 0;
    ucTimerUnit     = (VOS_UINT8)(ucMsgTimerValue >> 5);
    ucTimerValue    = (VOS_UINT8)(ucMsgTimerValue & 0x1F);

    /* 24008 10.5.163a�½���������:
    GPRS Timer 3 value (octet 3)
    Bits 5 to 1 represent the binary coded timer value.
    Bits 6 to 8 defines the timer value unit for the GPRS timer as follows:
    Bits
    8 7 6
    0 0 0 value is incremented in multiples of 10 minutes
    0 0 1 value is incremented in multiples of 1 hour
    0 1 0 value is incremented in multiples of 10 hours
    0 1 1 value is incremented in multiples of 2 seconds
    1 0 0 value is incremented in multiples of 30 seconds
    1 0 1 value is incremented in multiples of 1 minute
    1 1 1 value indicates that the timer is deactivated.

    Other values shall be interpreted as multiples of 1 hour in this version of the protocol.
    */
    switch (ucTimerUnit)
    {
        case 0:
            /* 10���� */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 10 * 60 * 1000;
            break;

        case 1:
            /* 1Сʱ */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 60 * 60 * 1000;
            break;

        case 2:
            /* 10Сʱ */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 10 * 60 * 60 * 1000;
            break;

        case 3:
            /* 2�� */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 2 * 1000;
            break;

        case 4:
            /* 30�� */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 30 * 1000;
            break;

        case 5:
            /* 1���� */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 60 * 1000;
            break;

        case 7:
            /* timer is deactivated */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal = 0;
            break;

        default:
            /* 1Сʱ */
            g_GmmTimerMng.aTimerInf[ucTimerName].ulTimerVal
                = ucTimerValue * 60 * 60 * 1000;
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_IsRegNeedFillTmsiStatusIE
 ��������  : �ж��Ƿ�attach��rauע����Ϣ���Ƿ���Ҫ��װtmsi status IE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��4��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRegNeedFillTmsiStatusIE(VOS_VOID)
{
    /* 24008 9.4.1.3�½���������:
      This IE shall be included if the MS performs a combined GPRS attach and no valid TMSI is available
      24008 9.4.14.4�½���������:
      This IE shall be included if the MS performs a combined routing area update and no valid TMSI is available.*/
    if ((VOS_FALSE  == NAS_MML_IsTmsiValid())
     && ((GMM_ATTACH_WHILE_IMSI_ATTACHED == NAS_GMM_GetSpecProc())
      || (GMM_ATTACH_COMBINED          == NAS_GMM_GetSpecProc())
      || (GMM_RAU_COMBINED         == NAS_GMM_GetSpecProc())
      || (GMM_RAU_WITH_IMSI_ATTACH == NAS_GMM_GetSpecProc())))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_GetAllocT3302ValuePlmnWithRat
 ��������  : ��ȡ�·�t3302��ʱ��ʱ��������Ϣ
 �������  : ��
 �������  : VOS_VOID
 �� �� ֵ  : NAS_MML_PLMN_ID_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��10��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
NAS_MML_PLMN_WITH_RAT_STRU *NAS_GMM_GetAllocT3302ValuePlmnWithRat(VOS_VOID)
{
    return &(g_GmmGlobalCtrl.stAllocT3302ValuePlmnWithRat);
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_SetAllocT3302ValuePlmnWithRat
 ��������  : �����·�t3302��ʱ��ʱ��������Ϣ
 �������  : ��
 �������  : VOS_VOID
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��10��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID NAS_GMM_SetAllocT3302ValuePlmnWithRat(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat
)
{
    g_GmmGlobalCtrl.stAllocT3302ValuePlmnWithRat.stPlmnId.ulMcc = pstPlmnWithRat->stPlmnId.ulMcc;
    g_GmmGlobalCtrl.stAllocT3302ValuePlmnWithRat.stPlmnId.ulMnc = pstPlmnWithRat->stPlmnId.ulMnc;
    g_GmmGlobalCtrl.stAllocT3302ValuePlmnWithRat.enRat = pstPlmnWithRat->enRat;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedUseDefaultT3302ValueRauAttempCntMax
 ��������  : �ж�rau attempt cnt�ﵽ����������t3302��ʱ��ʱ�Ƿ���Ҫʹ��T3302Ĭ��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫʹ��Ĭ��ֵ
             VOS_FALSE - ����Ҫʹ��Ĭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��10��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedUseDefaultT3302ValueRauAttempCntMax(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU         *pstAllocT3302PlmnWithRat = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;

    pstAllocT3302PlmnWithRat = NAS_GMM_GetAllocT3302ValuePlmnWithRat();
    enCurrNetRatType         = NAS_MML_GetCurrNetRatType();

    /* 24008_CR1904R1_(Rel-11)_C1-113602 Handling of timer T3302 24008 4.7.2.x�½���������:
    The MS shall apply this value in the routing area registered by the MS, until a new value is received.
    The default value of this timer is used in the following cases:
    -   ATTACH ACCEPT message, ROUTING AREA UPDATE ACCEPT message, ATTACH REJECT message, or ROUTING AREA UPDATE REJECT message is received without a value specified;
    -   In Iu mode, if the network provides a value in a non-integrity protected Iu mode GMM message and the MS is not attaching for emergency services or not attached for emergency services;
    -   the MS does not have a stored value for this timer; or
    -   a new PLMN which is not in the list of equivalent PLMNs has been entered, the routing area updating fails and the routing area updating attempt counter is equal to 5.
    ע��ʧ�ܴ�5�Σ����ϴ��·�t3302��ʱ��ʱ��������ͬ��ǰפ�����粻ͬ������뼼����ͬ����t3302ʹ��Ĭ��ֵ��*/
    if (VOS_FALSE == NAS_MML_CompareBcchPlmnwithSimPlmn(&pstAllocT3302PlmnWithRat->stPlmnId, NAS_MML_GetCurrCampPlmnId()))
    {
        return VOS_TRUE;
    }

    if (pstAllocT3302PlmnWithRat->enRat != enCurrNetRatType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsRegNeedFillTmsiBasedNRIContainerIE
 ��������  : �ж�ATTCH��rau�����Ƿ���ҪЯ��TMSI based NRI container IE
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRegNeedFillTmsiBasedNRIContainerIE(VOS_VOID)
{
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   enSpecProc;

    enSpecProc   = NAS_GMM_GetSpecProc();

    /* 24008_CR2145R3_(Rel-11)_C1-122517 /24008_CR2183R1_(Rel-11)_C1-123313/24008_CR2246_(Rel-11)_C1-123539
    24008 4.7.3.2.1��������:
    If the MS has stored a valid TMSI, the MS shall include the TMSI based NRI container IE
    in the ATTACH REQUEST message.
    4.7.5.2.1��������:
    If the MS has stored a valid TMSI, the MS shall include the TMSI based NRI container IE
    in the ROUTING AREA UPDATE REQUEST message..*/
    if (PS_PTL_VER_R11 > NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS))
    {
        return VOS_FALSE;
    }

    /* ��������ע�����̣�����ҪЯ��TMSI based NRI container IE */
    if ((GMM_RAU_COMBINED != enSpecProc)
     && (GMM_RAU_WITH_IMSI_ATTACH != enSpecProc)
     && (GMM_ATTACH_COMBINED != enSpecProc)
     && (GMM_ATTACH_WHILE_IMSI_ATTACHED != enSpecProc))
    {
        return VOS_FALSE;
    }

    /* Tmsi�Ƿ�,����ҪЯ��TMSI based NRI container IE */
    if (VOS_FALSE  == NAS_MML_IsTmsiValid())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_FillTmsiBasedNRIContainerIE
 ��������  : ���ATTCH��rau�����TMSI based NRI container IE����
 �������  : pucAddr - ��װIE��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : ��д��IE�ĳ���ucNumber
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT8 NAS_GMM_FillTmsiBasedNRIContainerIE(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBitValue;
    VOS_UINT8                          *pucTmsi = VOS_NULL_PTR;

    pucTmsi = NAS_MML_GetUeIdTmsi();
    ucLen   = 0;

    /* ��IE�ṹ�μ�10.5.5.31�½�����:
    NRI container value (octet 3 and bit 7-8 of octet 4)
    The NRI container value consists of 10 bits which correspond to bits 23 to 14 of the valid TMSI.
    NRI container value shall start with bit 8 of octet 3, which corresponds to bit 23 of TMSI. Bit 7 of octet 4 corresponds to TMSI bit 14.
    Bits 6, 5, 4, 3, 2, and 1 in octet 4 are spare and shall be set to zero.*/
    pucAddr[ucLen++] = NAS_GMM_IEI_TMSI_BASED_NRI_CONTAINER;
    pucAddr[ucLen++] = NAS_GMM_IE_TMSI_BASED_NRI_CONTAINER_LEN;

    /* ȡtmsi�ĵ�16λ(pucTmsi[0]Ϊ��1λ)����ֵ��NRI container value octet 3 bit 1 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 16);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 1, ucBitValue);


    /* ȡtmsi�ĵ�17λ����ֵ��NRI container value octet 3 bit 2 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 17);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 2, ucBitValue);


    /* ȡtmsi�ĵ�18λ����ֵ��NRI container value octet 3 bit 3 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 18);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 3, ucBitValue);

    /* ȡtmsi�ĵ�19λ����ֵ��NRI container value octet 3 bit 4 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 19);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 4, ucBitValue);

    /* ȡtmsi�ĵ�20λ����ֵ��NRI container value octet 3 bit 5 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 20);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 5, ucBitValue);

    /* ȡtmsi�ĵ�21λ����ֵ��NRI container value octet 3 bit 6 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 21);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 6, ucBitValue);

    /* ȡtmsi�ĵ�22λ����ֵ��NRI container value octet 3 bit 7 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 22);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 7, ucBitValue);

    /* ȡtmsi�ĵ�23λ����ֵ��NRI container value octet 3 bit 8 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 23);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 8, ucBitValue);

    ucLen++;

    /* ����ֵ */
    pucAddr[ucLen] = 0;

    /* ȡtmsi�ĵ�14λ����ֵ��NRI container value octet 4 bit 7 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 14);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 7, ucBitValue);

    /* ȡtmsi�ĵ�15λ����ֵ��NRI container value octet 4 bit 8 */
    ucBitValue = NAS_MML_GetBitValueFromBuffer(pucTmsi, 15);
    NAS_MML_SetBitValueToBuffer(&pucAddr[ucLen], 8, ucBitValue);

    ucLen++;

    return ucLen;
}

/*****************************************************************************
 �� �� ��  : NAS_Gmm_FillMsNetworkFeatureSupportIE
 ��������  : ��װms network feature support IE
 �������  : pucAddr
 �������  : pucAddr
 �� �� ֵ  : ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��6��8��
   ��    ��   : z00161729
   �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_UINT8 NAS_GMM_FillMsNetworkFeatureSupportIE(
    VOS_UINT8                          *pucAddr
)
{
    VOS_UINT8                           ucLen;

    ucLen = 0;

    pucAddr[0] = GMM_IE_MS_SUPPORT_EXTEND_PERIODIC_TIMER_IN_THIS_DOMAIN;

    /* ��дIEIΪ C0 */
    pucAddr[0] |= GMM_IEI_MS_NETWORK_FEATURE_SUPPORT;

    ucLen      = GMM_MS_NETWORK_FEATURE_SUPPORT_IE_LEN;

    return ucLen;
}




/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertPdpCtxStatusToNetworkPdpCtxStatus
 ��������  : ��MML��pdp״̬ת��Ϊ���������ʽ
 �������  : pstPsBearerCtx  - MML��pdp״̬��Ϣ
 �������  : pstPdpCtxStatus - ת����pdp״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��15��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��3��15��
    ��    ��   : l65478
    �޸�����   : DTS2013120300990:��PDP��������з���RAU,��һ��PDP����ʧ��
  3.��    ��   : 2014��12��06��
    ��    ��   : A00165503
    �޸�����   : DTS2014120207400: ����ȥ������PDP, ���಻�ͷ�RRC����
*****************************************************************************/
VOS_VOID NAS_GMM_ConvertPdpCtxStatusToNetworkPdpCtxStatus(
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx,
    VOS_UINT32                         *pulPdpCtxStatus
)
{
    VOS_UINT32                          ulPdpCtxStatus;
    VOS_UINT32                          i;

    ulPdpCtxStatus = 0;

    for ( i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        /* refer to 24.008 10.5.7.1
           1	indicates that the SM state of the corresponding PDP context is not PDP-INACTIVE */
        if ((NAS_MML_PS_BEARER_STATE_ACTIVE == pstPsBearerCtx[i].enPsBearerState)
         || (VOS_TRUE == pstPsBearerCtx[i].ucPsActPending)
         || (VOS_TRUE == pstPsBearerCtx[i].ucPsDeactPending))
        {
            /*lint -e701*/
            ulPdpCtxStatus |= 0x00000001 << (i + NAS_MML_NSAPI_OFFSET);
            /*lint +e701*/
        }
    }
    *pulPdpCtxStatus = ulPdpCtxStatus;

}



/*****************************************************************************
 �� �� ��  : NAS_GMM_ConverRrcGmmProcTypeToMml
 ��������  : rrmm��gmm proc type����ת��ΪMML��
 �������  : enRrmmGmmProcType:rrmm��gmm proc type
 �������  : penMmlGmmProcType:MML��gmm proc type
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��28��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_VOID    NAS_GMM_ConverRrcGmmProcTypeToMml(
    RRMM_GMM_PROC_TYPE_ENUM_UINT16      enRrmmGmmProcType,
    NAS_MML_GMM_PROC_TYPE_ENUM_UINT16  *penMmlGmmProcType
)
{
    switch (enRrmmGmmProcType)
    {
        case RRMM_GMM_PROC_TYPE_ATTACH:
            *penMmlGmmProcType = NAS_MML_GMM_PROC_TYPE_ATTACH;
            break;

        case RRMM_GMM_PROC_TYPE_NORMAL_RAU:
            *penMmlGmmProcType = NAS_MML_GMM_PROC_TYPE_NORMAL_RAU;
            break;

        case RRMM_GMM_PROC_TYPE_PERIOD_RAU:
            *penMmlGmmProcType = NAS_MML_GMM_PROC_TYPE_PERIOD_RAU;
            break;


        default:
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_ConverRrcGmmProcTypeToMml: Invalid gmm proc type!");
            *penMmlGmmProcType = NAS_MML_GMM_PROC_TYPE_INVALID;
            break;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_ConverRrcGmmProcFlagToMml
 ��������  : rrmm��gmm proc flag����ת��ΪMML��
 �������  : enRrmmGmmProcFlag:rrmm��gmm proc type
 �������  : penMmlGmmProcFlag:MML��gmm proc type
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��28��
   ��    ��   : z00161729
   �޸�����   : 24301 R11 CR������Ŀ�޸�

*****************************************************************************/
VOS_VOID    NAS_GMM_ConverRrcGmmProcFlagToMml(
    RRMM_GMM_PROC_FLAG_ENUM_UINT16      enRrmmGmmProcFlag,
    NAS_MML_GMM_PROC_FLAG_ENUM_UINT16  *penMmlGmmProcFlag
)
{
    switch (enRrmmGmmProcFlag)
    {
        case RRMM_GMM_PROC_FLAG_START:
            *penMmlGmmProcFlag = NAS_MML_GMM_PROC_FLAG_START;
            break;

        case RRMM_GMM_PROC_FLAG_FINISH:
            *penMmlGmmProcFlag = NAS_MML_GMM_PROC_FLAG_FINISH;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_GMM, "penMmlGmmProcFlag: Invalid gmm proc flag!");
            *penMmlGmmProcFlag = NAS_MML_GMM_PROC_FLAG_INVALID;
            break;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_TransGmmNwCause2GmmSmCause
 ��������  : ��GMM Causeװ����GMM/SM Cause
 �������  : enGmmCause - GMM Cause
 �������  : ��
 �� �� ֵ  : GMM_SM_CAUSE_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��6��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
GMM_SM_CAUSE_ENUM_UINT16 NAS_GMM_TransGmmNwCause2GmmSmCause(
    VOS_UINT8  enGmmCause
)
{
    GMM_SM_CAUSE_ENUM_UINT16            enGmmSmCause;

    if ( (enGmmCause >= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MIN)
      && (enGmmCause <= NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL_MAX) )
    {
        enGmmSmCause = NAS_MML_REG_FAIL_CAUSE_RETRY_UPON_ENTRY_CELL + GMM_SM_CAUSE_GMM_NW_CAUSE_OFFSET;
    }
    else
    {
        enGmmSmCause = enGmmCause + GMM_SM_CAUSE_GMM_NW_CAUSE_OFFSET;
    }

    return enGmmSmCause;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_LogGmmStateInfo
 ��������  : ��GMM��״̬
 �������  : ucGmmState: GMM�ĵ�ǰ״̬
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��08��21��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_GMM_LogGmmStateInfo(
    VOS_UINT8                           ucGmmState
)
{
    NAS_GMM_LOG_STATE_INFO_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_GMM_LOG_STATE_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                                         sizeof(NAS_GMM_LOG_STATE_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogGmmStateInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_GMM_LOG_STATE_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_GMM_LOG_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = GMMOM_LOG_STATE_INFO_IND;
    pstMsg->enGmmState                  = (NAS_GMM_STATE_ID_ENUM_UINT8)ucGmmState;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_GMM, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_LogGmmCtxInfo
 ��������  : ��GMMȫ�ֱ���
 �������  : ��
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��2��12��
    ��    ��   : s00217060
    �޸�����   : VOLTE SWITCH�޸ģ������ϴη�attach/rauʱ��voice domain
  3.��    ��   : 2015��6��15��
    ��    ��   : z00161729
    �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*****************************************************************************/
VOS_VOID  NAS_GMM_LogGmmCtxInfo(VOS_VOID)
{
    GMMOM_LOG_CTX_INFO_STRU            *pstMsg = VOS_NULL_PTR;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstMsg = (GMMOM_LOG_CTX_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                                         sizeof(GMMOM_LOG_CTX_INFO_STRU));

    pstConnStatus = NAS_MML_GetConnStatus();

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogGmmCtxInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(GMMOM_LOG_CTX_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulLength        = sizeof(GMMOM_LOG_CTX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = GMMOM_LOG_CTX_INFO_IND;

    pstMsg->stGmmGasGlobalCtrlInfo.ucLastDataSender  = gstGmmCasGlobalCtrl.ucLastDataSender;
    pstMsg->stGmmGasGlobalCtrlInfo.ucSuspendLlcCause = gstGmmCasGlobalCtrl.ucSuspendLlcCause;
    pstMsg->stGmmGasGlobalCtrlInfo.ucTlliAssignFlg   = gstGmmCasGlobalCtrl.ucTlliAssignFlg;

    pstMsg->stGmmGlobalCtrlInfo.CsInfo_ucCsTransFlg  = g_GmmGlobalCtrl.CsInfo.ucCsTransFlg;
    pstMsg->stGmmGlobalCtrlInfo.SysInfo_Rai          = g_GmmGlobalCtrl.SysInfo.Rai;
    pstMsg->stGmmGlobalCtrlInfo.SysInfo_ucCellChgFlg = g_GmmGlobalCtrl.SysInfo.ucCellChgFlg;
    pstMsg->stGmmGlobalCtrlInfo.SysInfo_ucNetMod     = g_GmmGlobalCtrl.SysInfo.ucNetMod;
    pstMsg->stGmmGlobalCtrlInfo.ucCvrgAreaLostFlg    = g_GmmGlobalCtrl.ucCvrgAreaLostFlg;
    pstMsg->stGmmGlobalCtrlInfo.ucDetachType         = (VOS_UINT8)g_GmmGlobalCtrl.stDetachInfo.enDetachType;
    pstMsg->stGmmGlobalCtrlInfo.ucRaiChgRelFlg       = g_GmmGlobalCtrl.ucRaiChgRelFlg;
    pstMsg->stGmmGlobalCtrlInfo.ucRelCause           = g_GmmGlobalCtrl.ucRelCause;
    pstMsg->stGmmGlobalCtrlInfo.ucSigConFlg          = g_GmmGlobalCtrl.ucSigConFlg;
    pstMsg->stGmmGlobalCtrlInfo.ucPlmnSrchPreSta     = g_GmmGlobalCtrl.ucPlmnSrchPreSta;
    pstMsg->stGmmGlobalCtrlInfo.ucSpecProc           = g_GmmGlobalCtrl.ucSpecProc;
    pstMsg->stGmmGlobalCtrlInfo.ucSpecProcInCsTrans  = g_GmmGlobalCtrl.ucSpecProcInCsTrans;
    pstMsg->stGmmGlobalCtrlInfo.UeInfo_ucMsRadioCapSupportLteFromAs     = g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs;
    pstMsg->stGmmGlobalCtrlInfo.UeInfo_ucMsRadioCapSupportLteFromRegReq = g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq;
    pstMsg->stGmmGlobalCtrlInfo.UeInfo_UeId_ucUeIdMask = g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask;
    PS_MEM_CPY(&pstMsg->stGmmGlobalCtrlInfo.stAttemptToUpdateRai, &g_GmmGlobalCtrl.stAttemptToUpdateRai, sizeof(NAS_MML_RAI_STRU));
    pstMsg->stGmmGlobalCtrlInfo.UeInfo_enVoiceDomainFromRegRq   = g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq;

    PS_MEM_CPY(&pstMsg->stGmmGlobalCtrlInfo.stAllocT3302ValuePlmnWithRat, NAS_GMM_GetAllocT3302ValuePlmnWithRat(),sizeof(pstMsg->stGmmGlobalCtrlInfo.stAllocT3302ValuePlmnWithRat));

    pstMsg->stGmmRauCtrlInfo.ucT3311ExpiredFlg         = g_GmmRauCtrl.ucT3311ExpiredFlg;
    pstMsg->stGmmRauCtrlInfo.ucT3312ExpiredFlg         = g_GmmRauCtrl.ucT3312ExpiredFlg;

    pstMsg->stGmmReqCnfMngInfo.ucCnfMask               = g_GmmReqCnfMng.ucCnfMask;

    pstMsg->stGmmServiceCtrlInfo.ucRetrySrForRelCtrlFlg = g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg;

    pstMsg->stGmmSuspendCtrlInfo.ucNetModeChange        = gstGmmSuspendCtrl.ucNetModeChange;
    pstMsg->stGmmSuspendCtrlInfo.ucPreRat               = gstGmmSuspendCtrl.ucPreRat;
    pstMsg->stGmmSuspendCtrlInfo.ucPreSrvState          = gstGmmSuspendCtrl.ucPreSrvState;
    pstMsg->stGmmSuspendCtrlInfo.ucT3312State           = gstGmmSuspendCtrl.ucT3312State;

    pstMsg->stGmmTimerMngInfo.ulTimerRunMask            = g_GmmTimerMng.ulTimerRunMask;

    pstMsg->stMmlCtxInfo.ucWSysInfoDrxLen               = NAS_MML_GetWSysInfoDrxLen();
    pstMsg->stMmlCtxInfo.ucT3423State                   = NAS_MML_GetT3423Status();
    pstMsg->stMmlCtxInfo.ucPsServiceBufferStatusFlg     = pstConnStatus->ucPsServiceBufferFlg;
    pstMsg->stMmlCtxInfo.ucPsRegStatus                  = NAS_MML_GetSimPsRegStatus();
    pstMsg->stMmlCtxInfo.ucIsTmsiValid                  = (VOS_UINT8)NAS_MML_IsTmsiValid();
    PS_MEM_CPY(&pstMsg->stMmlCtxInfo.stPsLastSuccRai ,NAS_MML_GetPsLastSuccRai(),sizeof(pstMsg->stMmlCtxInfo.stPsLastSuccRai));
    pstMsg->stMmlCtxInfo.enTinType                      = NAS_MML_GetTinType();
    pstMsg->stMmlCtxInfo.enPsUpdateStatus               = NAS_MML_GetPsUpdateStatus();
    pstMsg->stMmlCtxInfo.enMsMode                       = NAS_MML_GetMsMode();
    pstMsg->stMmlCtxInfo.enCurrUtranMode                = NAS_UTRANCTRL_GetCurrUtranMode();
    PS_MEM_CPY(pstMsg->stMmlCtxInfo.astPsBearerContext, NAS_MML_GetPsBearerCtx(), sizeof(pstMsg->stMmlCtxInfo.astPsBearerContext));

    pstMsg->stMmSubLyrShareInfo.GmmShare_ucGsAssociationFlg = g_MmSubLyrShare.GmmShare.ucGsAssociationFlg;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_GMM, pstMsg);

    return;
}


/* Added by t00212959 for DCM�����������������, 2012-8-14, begin */
/*****************************************************************************
 �� �� ��  : NAS_GMM_LogPsRegContainDrxInfo
 ��������  : GMM �����Ƿ�Я��Drx����ʱ��Ҫ����Ϣ������trace��
 �������  : enPsRegContainDrx - Drx����Я������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_LogPsRegContainDrxInfo(
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8    enPsRegContainDrx
)
{
    NAS_GMM_LOG_PS_REG_DRX_INFO_STRU             *pstPsRegContainDrxInfo;

    pstPsRegContainDrxInfo = (NAS_GMM_LOG_PS_REG_DRX_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                             sizeof(NAS_GMM_LOG_PS_REG_DRX_INFO_STRU));

    if ( VOS_NULL_PTR == pstPsRegContainDrxInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogPsRegContainDrxInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstPsRegContainDrxInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstPsRegContainDrxInfo->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstPsRegContainDrxInfo->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstPsRegContainDrxInfo->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstPsRegContainDrxInfo->stMsgHeader.ulLength        = sizeof(NAS_GMM_LOG_PS_REG_DRX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstPsRegContainDrxInfo->stMsgHeader.ulMsgName       = NAS_GMM_LOG_PS_REG_DRX_INFO_IND;

    pstPsRegContainDrxInfo->enPsRegContainDrx = enPsRegContainDrx;

    DIAG_TraceReport(pstPsRegContainDrxInfo);

    PS_MEM_FREE(WUEPS_PID_GMM, pstPsRegContainDrxInfo);

    return;
}
/* Added by t00212959 for DCM�����������������, 2012-8-14, end */

/* Modified by z00161729 for DCM�����������������, 2012-8-20, begin */
/*****************************************************************************
 �� �� ��  : NAS_GMM_IsCsPsModeAndNetworkI
 ��������  : �ж��Ƿ���A+Iģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��cs ps mode������ģʽΪI
             VOS_FALSE - ����A+Iģʽ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��18��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsAModeAndNetworkI(VOS_VOID)
{
    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsCombinedSpecProc
 ��������  : �ж�GMM�ڽ��е�ר�������Ƿ������ϵ�rau������rau with imsi attach
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - GMM��ר������������rau������rau with imsi attach
             VOS_FALSE - GMM��ר�����̲�������rau������rau with imsi attach
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��18��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsCombinedSpecProc(VOS_VOID)
{
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   enSpecProc;

    enSpecProc = NAS_GMM_GetSpecProc();

    if ((GMM_RAU_COMBINED == enSpecProc)
     || (GMM_RAU_WITH_IMSI_ATTACH == enSpecProc))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Modified by z00161729 for DCM�����������������, 2012-8-20, end */

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_GMM_GetLteInfo
 ��������  : ��ȡLTE��Ϣ�����ӿں���
 �������  : ulInfoType
 �������  : pstLmmInfo
 �� �� ֵ  : VOS_TRUE:��ȡ�ɹ�
              VOS_FALSE:��ȡʧ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��12��27��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_GMM_GetLteInfo(
    NAS_LMM_INFO_TYPE_ENUM_UINT32       ulInfoType,
    NAS_LMM_INFO_STRU                  *pstLmmInfo
)
{
    /* ƽ̨��֧��LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* ����LNAS�ṩ�ӿں������ɹ�����VOS_OK */
    if (MMC_LMM_SUCC == Nas_GetLteInfo(ulInfoType, pstLmmInfo))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : NAS_GMM_HandleMsRadioCapLteSupportChanged
 ��������  : MS Radio cap������LTE�Ƿ�֧�ַ����ı�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��05��09��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_GMM_HandleMsRadioCapLteSupportChanged(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    pstConnStatus   = NAS_MML_GetConnStatus();

    /* �������CSҵ����ֱ�ӷ��� */
    if (VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)
    {
        return;
    }

    /* ������ڷ���CSҵ����������ʱ����ҵ����ʧ��������ʱ������RAU��
       ҵ����ɹ���ʱ����ʱʱ��ֱ�ӷ��� */
    if ((VOS_TRUE == NAS_MML_GetCsServiceBufferStatusFlg())
     && (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);

        return;
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU);
    }

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm
 ��������  : GMM��GmmRegisteredAttemptingToUpdateMm״̬�ж��Ƿ���Խ�������ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    - ���Է�������ע��
              VOS_FALSE  - �����Է�������ע��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��18��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
        TS24.008:t3311��ʱ����COMBINED RA/LA updating with imsi attach.�޸�
        ���³�������������ATTACH.

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo         = VOS_NULL_PTR;

    VOS_UINT8                           ucCsRestrictRegister;

    /* ��ȡ��ǰ��CS���ޱ�ʶ */
    ucCsRestrictRegister = NAS_MML_GetCsRestrictRegisterFlg();

    /* ��ȡ��ǰ����ģʽ */
    pstCampInfo          = NAS_MML_GetCurrCampPlmnInfo();

    /* ��ǰ������ģʽI */
    if ( NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode )
    {
        return VOS_FALSE;
    }

    /* ��ǰcs��׼��ע�� */
    if ( VOS_FALSE == NAS_MML_GetCsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* ��ǰע��cs���� */
    if ( VOS_TRUE == ucCsRestrictRegister )
    {
        return VOS_FALSE;
    }

    /* ��ǰCS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimCsRegStatus())
    {
        return VOS_FALSE;
    }

    /* CS��ҵ�� */
    if ( GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_LogAuthInfo
 ��������  : ��MM�������ļ�Ȩ��Ϣ
 �������  : VOS_VOID
 �������  : ucRcvOpId    : ��Ϣ�н��ܵ���OPID
             ucExpectOpId : MM������OPID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��08��21��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_GMM_LogAuthInfo(
    VOS_UINT8                           ucRcvOpId,
    VOS_UINT8                           ucExpectOpId
)
{
    NAS_GMM_LOG_AUTH_INFO_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_GMM_LOG_AUTH_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_GMM,
                                         sizeof(NAS_GMM_LOG_AUTH_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_LogAuthInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_GMM_LOG_AUTH_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_GMM_LOG_AUTH_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = GMMOM_LOG_AUTH_INFO_IND;
    pstMsg->ucExpectOpId                = ucExpectOpId;
    pstMsg->ucRcvOpId                   = ucRcvOpId;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_GMM, pstMsg);

    return;
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : NAS_GMM_NwDetachIndRecord
 ��������  : ��¼����Detachָʾ�¼�
 �������  : VOS_UINT8  ucDetachType
             VOS_UINT8  ucGmmCause
             VOS_UINT8  ucForceToStandby
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_NwDetachIndRecord(
    VOS_UINT8                           ucDetachType,
    VOS_UINT8                           ucGmmCause,
    VOS_UINT8                           ucForceToStandby
)
{
    NAS_ERR_LOG_NW_DETACH_IND_EVENT_STRU                    stNwDetachIndEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_NW_DETACH_IND);
    ulIsLogRecord = NAS_MML_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_NW_DETACH_IND_EVENT_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    PS_MEM_SET(&stNwDetachIndEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stNwDetachIndEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_GMM),
                                      NAS_ERR_LOG_ALM_NW_DETACH_IND,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    NAS_MNTN_OutputPositionInfo(&stNwDetachIndEvent.stPositionInfo);

    stNwDetachIndEvent.ucDetachType         = ucDetachType;
    stNwDetachIndEvent.ucGmmCause           = ucGmmCause;
    stNwDetachIndEvent.ucForceToStandby     = ucForceToStandby;
    stNwDetachIndEvent.ucCurrNetRat         = NAS_MML_GetCurrNetRatType();

    stNwDetachIndEvent.ucOriginalGmmCause = NAS_MML_GetOriginalRejectCause(stNwDetachIndEvent.ucGmmCause);
    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = NAS_MML_PutErrLogRingBuf((VOS_CHAR *)&stNwDetachIndEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_MMC_NwDetachIndRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_NW_DETACH_IND,
                           WUEPS_PID_GMM,
                           (VOS_UINT8 *)&stNwDetachIndEvent,
                           sizeof(stNwDetachIndEvent));

    return;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsEnableRelPsSigCon
 ��������  : gmm �ж��Ƿ����������������
 �������  : ��
 �������  : ��
 �� �� ֵ  :  �Ƿ�������������ܣ�TRUE��ʾ������FALSE:δ����

 �޸���ʷ  :
 1.��    ��   : 2014��11��04��
   ��    ��   : w000281933
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 NAS_GMM_IsEnableRelPsSigCon(VOS_VOID)
{
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_GMM_IsEnableRelPsSigCon(): The sim is Test card!");
        return VOS_FALSE;
    }

    return (NAS_MML_GetRelPsSigConFlg());
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetRelPsSigConCfg_T3340TimerLen
 ��������  : gmm �ڿ�������������ܺ󣬻�ȡ���õ�T3340 ��ֵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :  ���õ�T3340 ��ʱ������λΪ���룻

 �޸���ʷ  :
 1.��    ��   : 2014��11��04��
   ��    ��   : w000281933
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_GetRelPsSigConCfg_T3340TimerLen(VOS_VOID)
{
    VOS_UINT32                          ulTmpT3340timeLen;

    ulTmpT3340timeLen = (NAS_MML_GetRelPsSigConCfg_T3340TimerLen() * NAS_MML_ONE_THOUSAND_MILLISECOND); /* ��λ��Ϊ���� */

    return ulTmpT3340timeLen;
}

/*lint -restore */

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsUeInfoChangeTriggerRau
 ��������  : UE��Ϣ�仯�Ƿ���Ҫ����RAU
 �������  : ��
 �������  : ��
 �� �� ֵ  :  VOS_TRUE:��Ҫ
              VOS_FALSE:����Ҫ

 �޸���ʷ  :
 1.��    ��   : 2014��11��04��
   ��    ��   : w000281933
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��8��13��
   ��    ��   : l00289540
   �޸�����   : User_Exp_Improve�޸�

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsUeInfoChangeTriggerRau(VOS_VOID)
{
    VOS_INT8                            cVersion;

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

#if (FEATURE_ON == FEATURE_LTE)
    /* radio capability����һ��ע��ʱ�Ĳ�ͬ����Ҫ��RAU */
    if (g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs != g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq)
    {
        return VOS_TRUE;
    }

    if (cVersion >= PS_PTL_VER_R9)
    {
        /* voice domain����һ��ע��ʱ�Ĳ�ͬ����Ҫ��RAU */
        if (g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq != NAS_MML_GetVoiceDomainPreference())
        {
            return VOS_TRUE;
        }
    }
#endif

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : Gmm_ComConvertRrcEstCnfCauseToMmlRegCause
 ��������  : Gmm ����ʧ��ԭ��ֵת��ΪMML Reg Fail Cause
 �������  : ulRrcEstResult:RRC �������
 �������  : penMmlRegFailCause:ת��֮���MML Reg fail cause
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��24��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID Gmm_ComConvertRrcEstCnfCauseToMmlRegCause(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulRrcEstResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penMmlRegFailCause
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    *penMmlRegFailCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL;
    enCurrUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();

    if (NAS_MML_NET_RAT_TYPE_WCDMA     == NAS_MML_GetCurrNetRatType())
    {
        if ((NAS_UTRANCTRL_UTRAN_MODE_FDD  == enCurrUtranMode)
         && (RRC_EST_RANDOM_ACCESS_REJECT  == ulRrcEstResult))
        {
            *penMmlRegFailCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL_RANDOM_ACCESS_REJECT;
        }

        if ((NAS_UTRANCTRL_UTRAN_MODE_TDD  == enCurrUtranMode)
         && (RRC_EST_RJ_TIME_OUT           == ulRrcEstResult))
        {
            *penMmlRegFailCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL_RANDOM_ACCESS_REJECT;
        }
    }

    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

