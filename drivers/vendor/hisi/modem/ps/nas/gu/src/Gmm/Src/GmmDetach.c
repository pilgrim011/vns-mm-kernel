/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmDetach.c
  Description   : GMM DETACH������ش�����Դ�ļ�
  Function List :
    01.   Gmm_RcvMmcDetachReq
    02.   Gmm_SimRemoveDetach
    03.   Gmm_RcvMmcDetachReq_RegNoCell
    04.   Gmm_MsInitNormalDetach
    05.   Gmm_Com_MsInitNormalDetach
    06.   Gmm_RcvMmcPowerOffReq
    07.   Gmm_PowerOffDetach
    08.   Gmm_DetachRequestMsgMake
    09.   Gmm_RcvDetachRequestMsg
    10.   Gmm_RcvDetachRequestMsg_RegInit
    11.   Gmm_RcvDetachRequestMsg_DeregInit
    12.   Gmm_RcvDetachRequestMsg_RauInit
    13.   Gmm_RcvDetachRequestMsg_ServReqInit
    14.   Gmm_RcvDetachRequestMsg_RegNmlServ
    15.   Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm
    16.   Gmm_RcvDetachRequestMsg_RegImsiDtchInit
    17.   Gmm_NetInitNotRequiredDetach
    18.   Gmm_Com_Cause2Detach
    19.   Gmm_Com_CauseDetach
    20.   Gmm_NetInitRequiredDetach
    21.   Gmm_NetInitImsiDetach
    22.   Gmm_DetachAcceptMsgMake
    23.   Gmm_RcvDetachAcceptMsg
    24.   Gmm_RcvDetachAcceptMsg_DeregInit
    25.   Gmm_RcvDetachAcceptMsg_RegImsiDtchInit
  History       :
    1.  ��־��  2003.12.09  �¹�����
    2.  s46746  2006-03-08  �������ⵥA32D02368�޸�
    3.  s46746  2006-03-09  �������ⵥA32D02387�޸�
    4.  l40632  2006-04-17  �������ⵥA32D03132�޸�
    5.  l40632  2006-04-28  �������ⵥA32D03272�޸�
    6. x51137 2006/4/28 A32D02889
    7.  s46746  2006-06-16  �������ⵥA32D03581�޸�
    8. ��    ��   : 2006��9��9��
       ��    ��   : sunxibo id:46746
       �޸�����   : �������ⵥ�ţ�A32D05604
    9.��    ��   : 2006��11��06��
       ��    ��   : s46746
       �޸�����   : ���ⵥ��:A32D05787
    10.��    ��   : 2006��11��9��
       ��    ��   : sunxibo id:46746
       �޸�����   : �������ⵥ�ţ�A32D06822
    11.��    ��   : 2006��11��20��
       ��    ��   : s46746
       �޸�����   : �������������ⵥ�ţ�A32D07433
    12.��    ��   : 2007��01��04��
       ��    ��   : s46746
       �޸�����   : �������������ⵥ�ţ�A32D08235
    13.��    ��   : 2007��12��12��
       ��    ��   : l00107747
       �޸�����   : �������ⵥ�ţ�A32D13861
    14.��    ��   : 2007��12��14��
       ��    ��   : s46746
       �޸�����   : ���ⵥA32D13638����֤����RAU֮ǰ�������෢���������ݣ�����RAU���ɹ������ָ���2
    15.��    ��   : 2007��12��28��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�A32D13954,�޸�GMM��2G3�����л�����Ϣ����
    16.��    ��   : 2008��7��2��
       ��    ��   : l00107747
       �޸�����   : �������ⵥ�ţ�AT2D03900,FOLLOW ON��־����Ų�
    17.��    ��   : 2008��9��23��
       ��    ��   : o00132663
       �޸�����   : �������ⵥ�ţ�AT2D05839,�������ȫ�ֱ��� ucRlsMsgFlg��״̬GMM_REGISTERED_WAIT_FOR_RAU
    18.��    ��   : 2009��01��20��
       ��    ��   : l00130025
       �޸�����   : ���ⵥ��:AT2D08378,��������ı�ʱ,MM/GMMû�ж�UE��mode���иı�;GMM��RAU�������յ�Detach����ʱ,ֱ�ӷ���,û�д���
    19.��    ��   : 2009��05��25��
       ��    ��   : h44270
       �޸�����   : ���ⵥ��:AT2D09923/AT2D12099,����attach����������tlli������
    20.��    ��   : 2009��08��14��
       ��    ��   : l60609
       �޸�����   : ���ⵥ��:AT2D13779,IMSI DETACH�ϱ��¼�������
    21.��    ��   : 2009��08��19��
       ��    ��   : x00115505
       �޸�����   : ���ⵥ��:AT2D13855,Combined Attach������ͨ��SYSCFG���ý�֧��PS������ʧ��
    22.��    ��   : 2009��08��24��
       ��    ��   : x00115505
       �޸�����   : AT2D14023,����GCF����44.2.2.1.9ʧ��
*******************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasSend.h"
#include "GmmCasGsm.h"
#include "NasCommDef.h"
#include "GmmCasSuspend.h"

#include "NasUtranCtrlInterface.h"

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
#define    THIS_FILE_ID        PS_FILE_ID_GMM_DETACH_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

/*lint -save -e958 */


/*****************************************************************************
 �� �� ��  : NAS_GMM_SaveDetachMsg
 ��������  : ����detach��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��10��
    ��    ��   : l65478
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_SaveDetachMsg(VOS_VOID *pMsg)
{
    MMCGMM_DETACH_REQ_STRU      *pDetachMsg = VOS_NULL_PTR;

    /* �Ѿ��л����detach��Ϣʱ,�����һ��detach��ϢΪ׼
       �˴�������detach���Ͳ�ͬ����� */
    if ((VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach)
     && (GMM_MSG_HOLD_FOR_DETACH == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH)))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;
    }

    pDetachMsg = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
    if (VOS_NULL_PTR == pDetachMsg)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_SaveDetachMsg:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
          return;
    }
    Gmm_MemCpy(pDetachMsg, pMsg, sizeof(MMCGMM_DETACH_REQ_STRU));
    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pDetachMsg;
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_DeleteSavedDetachMsg
 ��������  : ɾ�������detach��Ϣ
 �������  : ulDelDetachType        - ɾ����DETACH����
 �������  : ��
 �� �� ֵ  : VOS_TRUE               - ɾ���ɹ�
             VOS_FALSE              - δ����ɾ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��13��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
                 ע:������ģʽI�£�GMM����Ŀ�����CS+PS�������detach��Ϣ��GMM��
                 MMͬʱ����ȥע�ᱣ����ʱ������CS��ʱʱ����PS��1�롣
                 �����ʱCS��ʱ����ôPS����ϢҲ���Ա������
                 �����ʱPS��ʱ����ôCS��PS����Ϣ�����Ա������
*****************************************************************************/
VOS_UINT32 NAS_GMM_DeleteSavedDetachMsg(
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     ulDelDetachType
)
{
    MMCGMM_DETACH_REQ_STRU             *pstMsDetach = VOS_NULL_PTR;
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     ulGmmDetach;

    if ( ( GMM_MSG_HOLD_FOR_DETACH == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH) )
      && ((VOS_NULL_PTR            != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach)) )
    {
         pstMsDetach = (MMCGMM_DETACH_REQ_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;

         /* ��ȡ�����DETACH���� */
         ulGmmDetach = pstMsDetach->enDetachType;

          /* ����������Ҫɾ�����DETACH,����������Detach��Ϣ */
        if ( ulDelDetachType == (ulGmmDetach & ulDelDetachType) )
        {
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;   /* ��������־                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = VOS_NULL_PTR;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcGmmDetachReqMsg_GmmRegisteredInitiated
 ��������  : GMM��GMM_REGISTERED_INITIATED״̬�յ�DETACH REQ�Ĵ���
 �������  : pMsg        - DETACH REQ ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��17��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcGmmDetachReqMsg_GmmRegisteredInitiated(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT32                          ulDetachType;                                  /* ����detach����                           */
    MMCGMM_DETACH_REQ_STRU             *pMsDetach       = VOS_NULL_PTR;                                     /* ����ָ��                                 */

    pMsDetach    = (MMCGMM_DETACH_REQ_STRU *)pMsg;                              /* ��ʼ��ָ��                               */
    ulDetachType = pMsDetach->enDetachType;

    /* ���ڽ��������У��򻺴�ȥע����Ϣ */
    if ( (GMM_FALSE                 == g_GmmGlobalCtrl.ucSigConFlg)
      && (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) )
    {                                                                       /* �����������ڽ�����������                 */
        /* ����DETACH��Ϣʱ����Ҫ�ͷ���ǰ�ѻ����DETACH��Ϣ������ᵼ���ڴ�й¶ */
        NAS_GMM_SaveDetachMsg(pMsg);

        return;                                                       /* ����                                     */
    }

    /* ������ע������У��򻺴���Ϣ,������ע����̽������ٴ��� */
    if ( (GMM_ATTACH_COMBINED            == g_GmmGlobalCtrl.ucSpecProc)
      || (GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc) )
    {
        if (MMC_GMM_PS_CS_DETACH != ulDetachType)
        {
            /* �ڽ�������ע�������,������Ϣ,������ע����̽������ٴ��� */
            NAS_GMM_SaveDetachMsg(pMsg);

            return;
        }
    }

    /* ����ģʽI,�����ǰCS���Ѵ���DETACH״̬�����ҵ�ǰ��CS��PS���DETACH����ֻ����PS ONLY DETACH */
    ulDetachType = NAS_GMM_ConvertDetachType(ulDetachType);

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ͣT3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* ���followon��־                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {                                                                           /* ATTACH��������SM������                   */
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);      /* ֪ͨSM GMMע��ʧ��                       */
        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                                 /* ��ucSmCnfFlg��־                         */
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask
        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }

    if (MMC_GMM_CS_DETACH != ulDetachType)
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );                               /* ���ý�ֹע���־                         */
    }

    Gmm_MsInitNormalDetach(ulDetachType);

    return;

}


/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated
 ��������  : GMM��GmmServiceReqInitiated״̬�յ�DETACH REQ��Ϣ�Ĵ���
 �������  : pMsg        - DETACH REQ ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE               - ����DETACH��Ϣ�Ĵ���
             VOS_FALSE              - δ����DETACH��Ϣ�Ĵ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��17��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT32                          ulDetachType;                                  /* ����detach����                           */
    MMCGMM_DETACH_REQ_STRU             *pMsDetach       = VOS_NULL_PTR;                                     /* ����ָ��                                 */

    pMsDetach    = (MMCGMM_DETACH_REQ_STRU *)pMsg;                              /* ��ʼ��ָ��                               */
    ulDetachType = pMsDetach->enDetachType;

    /* ���ڽ��������У��򻺴�ȥע����Ϣ */
    if ( (GMM_FALSE                 == g_GmmGlobalCtrl.ucSigConFlg)
      && (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) )
    {                                                                       /* �����������ڽ�����������                 */
        /* ����DETACH��Ϣʱ����Ҫ�ͷ���ǰ�ѻ����DETACH��Ϣ������ᵼ���ڴ�й¶ */
        NAS_GMM_SaveDetachMsg(pMsg);

        return;                                                       /* ����                                     */
    }

    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ͣT3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ֹͣT3302                                */
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ֹͣT3311                                */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask
        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }

    if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
        ||(GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* SR����Ϊdata                             */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ��RABM���ͽ��                           */
    }
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ����PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }
    if (GMM_MSG_HOLD_FOR_SM
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(): Clear cached SM Data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }

    /* ����DETACH���͵�ת�� */
    ulDetachType = NAS_GMM_ConvertDetachType(ulDetachType);

    Gmm_MsInitNormalDetach(ulDetachType);                                       /* ����MS������detach����                   */

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_LocalDetach_GmmDeregisteredNoImsi
 ��������  : GMM����GmmDeregisteredNoImsi״̬ʱ��������DETACH����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredNoImsi(VOS_VOID)
{
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );     /* ���ý�ֹע���־                         */

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }

    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_LocalDetach_GmmDeregisteredNormalService
 ��������  : GMM����GmmDeregisteredNormalService״̬ʱ��������DETACH����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��8��7��
    ��    ��   : w00167002
    �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredNormalService(VOS_VOID)
{
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );     /* ���ý�ֹע���־                         */

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach
 ��������  : GMM����GmmDeregisteredAttemptingToAttach״̬ʱ��������DETACH����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach(VOS_VOID)
{
    /* ֪ͨMMģ�� */
    if ((VOS_TRUE      == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod) )
    {
        NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);
    }

    /* GMM���б���DEACH */
    NAS_GMM_GprsLocalDetach();

    /* Ǩ��״̬ */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* ����״̬�Ĺ�������                       */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_LocalDetach_GmmDeregisteredInitiated
 ��������  : GMM����GmmDeregisteredInitiated״̬ʱ��������DETACH����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredInitiated(VOS_VOID)
{
    /* �����ǰPS���Ѿ�ȥע���ˣ����Ҵ���P-TMSI signature,�����P-TMSI signature */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {
            /* Upon completion of an MS initiated detach procedure, the used P-TMSI signature shall be deleted */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
    }

    /* GMM����ȥע�� */
    NAS_GMM_GprsLocalDetach();

    /* Ǩ��״̬ */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_LocalDetach_GmmRauInitiated
 ��������  : GMM����GmmRauInitiated״̬ʱ��������DETACH����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GmmRauInitiated(VOS_VOID)
{
    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauFailureInterSys();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    Gmm_ComCnfHandle();

    /* GMM����ȥע�� */
    NAS_GMM_GprsLocalDetach();

    /* Ǩ��״̬ */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    return;
}




/*****************************************************************************
 �� �� ��  : NAS_GMM_StartDetachProtectingTimer
 ��������  : ����GMM��Detach��Ϣ�ı�����ʱ��
 �������  : MMCGMM_DETACH_REQ_STRU             *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_VOID NAS_GMM_StartDetachProtectingTimer(
    MMCGMM_DETACH_REQ_STRU             *pstMsg
)
{
    /* Detach���̱�����ʱ��ʱ�� */
    VOS_UINT32                          ulDetachTimerVal;

    MMC_GMM_DETACH_TYPE_ENUM_UINT32     enDetachType;

    /* GMM��PS��Detach������ʱ������״̬ */
    VOS_UINT32                          ulPsDetachTimerStatus;

    if (MMC_GMM_DETACH_CAUSE_USER_DETACH == pstMsg->enDetachReason)
    {
        /* �û�������DETACH��ʱ��: 90s */
        ulDetachTimerVal  = GMM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE;
    }
    else
    {
        /* �����ǰ��SYSCFG�������仯������DETACH,�����ñ�����ʱ����ʱ��Ϊ15s */
        ulDetachTimerVal  = GMM_TIMER_PROTECT_DETACH_BY_SYSCFG_VALUE;
    }


    /* ��ȡGMM��Detach������ʱ������״̬ */
    ulPsDetachTimerStatus = NAS_GMM_QryTimerStatus(GMM_TIMER_PROTECT_PS_DETACH);

    /* Ĭ�ϵ�ǰ������PS��DETACH */
    enDetachType         = MMC_GMM_PS_DETACH;

    enDetachType         = pstMsg->enDetachType;

    /* �����ǰ����ҪPS���DETACH����ֱ�ӷ��� */
    if ( MMC_GMM_PS_DETACH != (enDetachType & MMC_GMM_PS_DETACH) )
    {
        return;
    }

    /* �����û�ִ�е���PS��DETACH,���GMM��PS��Detach������ʱ��δ�����У�������PS��Detach������ʱ�� */
    if ( VOS_FALSE         == ulPsDetachTimerStatus )
    {
        /* ����GMM��CS��Detach������ʱ��ʱ�� */
        g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_PS_DETACH].ulTimerVal = ulDetachTimerVal;

        /* ����GMM��PS��detach������ʱ�� */
        Gmm_TimerStart(GMM_TIMER_PROTECT_PS_DETACH);
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_GMM_LocalDetach_GprsSuspension
 ��������  : GMM����GPRS_SUSPENSION״̬ʱ��������DETACH����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 20013��02��19��
    ��    ��   : l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��8��7��
    ��    ��   : w00167002
    �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
  3.��    ��   : 2014��3��12��
    ��    ��   : f00261442
    �޸�����   : DTS2014031103926:�ڱ���DETACH��ʱ��֪ͨSM
*****************************************************************************/
VOS_VOID NAS_GMM_LocalDetach_GprsSuspension(VOS_VOID)
{
    /* ���ý�ֹע���־                         */
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );

    if (GMM_REGISTERED_NO_CELL_AVAILABLE == gstGmmSuspendCtrl.ucPreState)
    {
        gstGmmSuspendCtrl.ucPreState = GMM_DEREGISTERED_NO_CELL_AVAILABLE;
    }
    else if (GMM_DEREGISTERED_NO_IMSI != gstGmmSuspendCtrl.ucPreState)
    {
        gstGmmSuspendCtrl.ucPreState = GMM_DEREGISTERED_NORMAL_SERVICE;
    }
    else
    {

    }

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    NAS_GMM_SndSmStatusInd(GMM_SM_STATUS_DETACHED, GMM_SM_CAUSE_PS_DETACH);

    NAS_GMM_ClearMsgFromBuff(MMCGMM_ATTACH_REQ,WUEPS_PID_MMC,WUEPS_PID_GMM);
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GprsLocalDetachRelCsPsAllConn
 ��������  : GMM������DETACHʱ����������ӵĴ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��21��
    ��    ��   : z00161729
    �޸�����   : DTS2014032105704:����TDS����˲���һ�ԭС��psǨ��modem1���ٻ�Ǩmodem0
*****************************************************************************/
VOS_VOID NAS_GMM_GprsLocalDetachRelCsPsAllConn(VOS_VOID)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType;

    enUtranMode         = NAS_UTRANCTRL_GetCurrUtranMode();
    enCurNetRatType     = NAS_MML_GetCurrNetRatType();

    /* W�´��������֪ͨ�������������ͷ� */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurNetRatType )
     && ((GMM_TRUE                  == g_GmmGlobalCtrl.ucSigConFlg)
      || (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))))

    {
        /* SVLTE����TDDģʽʹ������ԭ��֪ͨtds�����ͷ� */
        if ((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
         && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode))
        {
            NAS_GMM_SndRrmmRelCsPsAllConnReq();
            return;
        }

        /* ��svlte����ʹ��rrmm_rel_req֪ͨ����������ͷ� */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_GprsLocalDetach
 ��������  : GMM������DETACH�Ļ������������������״̬Ǩ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��13��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��8��7��
    ��    ��   : w00167002
    �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
  3.��    ��   : 2014��3��21��
    ��    ��   : z00161729
    �޸�����   : DTS2014032105704:����TDS����˲���һ�ԭС��psǨ��modem1���ٻ�Ǩmodem0
*****************************************************************************/
VOS_VOID NAS_GMM_GprsLocalDetach(VOS_VOID)
{

    NAS_GMM_GprsLocalDetachRelCsPsAllConn();

#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
    }
#endif

    /* GMMֹͣ������ʱ�� */
    Gmm_TimerStop(GMM_TIMER_ALL);

    /* ���ý�ֹע���־ */
    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

    /* �������ķ����־ */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    /* ���followon��־ */
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;

    /* �嵱ǰ���� */
    g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;

    /* G�������2������� */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
    }

    /* ������ڼ�Ȩ��������ȴ���־ */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }

    /* ��������ATTACH��־ */
    NAS_GMM_ClearMsgFromBuff(MMCGMM_ATTACH_REQ, WUEPS_PID_MMC, WUEPS_PID_GMM);

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    /* GPRS Local Detach������Ҫ֪ͨSM��ǰMM����ʧ�� */
    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_GprsLocalDetach: Notify SM EST FAILURE because of PS DETACH");
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);      /* ֪ͨSM GMMע��ʧ��                       */
        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                                 /* ��ucSmCnfFlg��־                         */
    }

    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


    /* �����û��棬��֤���ݲ����·� */
    NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_BUTT,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_FALSE);

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedProcUserCsDetach
 ��������  : �����б��Ƿ���GMM�������û������CS/CS+PS��detach
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE          -- ����ҪGMM���д����û������CS/CS+PS��detach
             VOS_TRUE           -- ��ҪGMM���д����û������CS/CS+PS��detach
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedProcUserCsDetach(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo       = VOS_NULL_PTR;
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo    = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* ��ȡ��ǰ����ģʽ */
    pstCampInfo       = NAS_MML_GetCurrCampPlmnInfo();

    /* ��ȡ��ǰ��������Ϣ */
    pstNetWorkInfo    =  NAS_MML_GetNetworkInfo();

    ulRet             = VOS_FALSE;


    /* ������ģʽI�£�����GMM�����û������detach */
    if ( NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode )
    {
        return VOS_FALSE;
    }

    /* PS��׼��ע�ᣬ����GMM�����û������detach */
    if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        return VOS_FALSE;
    }

    /* PS��ע�����ޣ�����GMM�����û������detach */
    if ( VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg() )
    {
        return VOS_FALSE;
    }

    /* PS ����Ч������GMM�����û������detach */
    if ( VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    /* ��ǰС���Ƿ�֧��GPRS */
    if ( VOS_FALSE == pstNetWorkInfo->stPsDomainInfo.ucPsSupportFlg )
    {
        return VOS_FALSE;
    }

    /* ��ǰС���Ƿ���FORB GPRS PLMN���� */

    ulRet = NAS_MML_IsSimPlmnIdInDestBcchPlmnList( &(pstCampInfo->stLai.stPlmnId),
                                           pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                           pstForbidPlmnInfo->astForbGprsPlmnList );
    if ( VOS_TRUE == ulRet )
    {
        return VOS_FALSE;
    }

    /* MM�Ѵ���ATTACHED״̬������ǰGS�ӿڲ����� */
    if ( (VOS_FALSE          == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
      && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState) )
    {
        return VOS_FALSE;
    }

    /* �����û������CS���DETACH������GMM���д��� */
    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertDetachType
 ��������  : ����ת��ȥע������
 �������  : enDetachType                    -- ת��ǰ��ȥע������
 �������  : ��
 �� �� ֵ  : NAS_GMM_DETACH_TYPE_ENUM_UINT32 -- ת�����ȥע������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��19��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_GMM_DETACH_TYPE_ENUM_UINT32 NAS_GMM_ConvertDetachType(
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     ulDetachType
)
{
    if (MMC_GMM_PS_CS_DETACH == ulDetachType)
    {                                                                           /* ��combined detach                        */
        if ( GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod )
        {                                                                       /* ��ǰ�Ƿ�A+I                              */
            return MMC_GMM_PS_DETACH;
        }

        if ( (MM_STATUS_DETACHED             == g_MmSubLyrShare.MmShare.ucCsAttachState)
          && (GMM_ATTACH_COMBINED            != g_GmmGlobalCtrl.ucSpecProc)
          && (GMM_ATTACH_WHILE_IMSI_ATTACHED != g_GmmGlobalCtrl.ucSpecProc) )
        {
            return MMC_GMM_PS_DETACH;                                           /* GMMִֻ��PS���detach                    */
        }

        return MMC_GMM_PS_CS_DETACH;
    }

    /* ����ȥע�����ͱ��ֲ��� */
    return ulDetachType;

}



/*****************************************************************************
 �� �� ��  : NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit
 ��������  : GMM��GMM_REGISTERED_IMSI_DETACH_INITIATED״̬�յ�MM��
             MMGMM_CS_LOCAL_DETACH_IND��Ϣ�Ĵ���
 �������  : MMCGMM_DETACH_REQ_STRU             *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* ����״̬�Ĺ�������                       */
    g_GmmDetachCtrl.ucT3321OutCnt = 0;                                          /* T3321���������0                         */

    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
        & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            &= ~GMM_UEID_P_TMSI_SIGNATURE;                                      /* ���P_TMSI_SIGNATURE                     */

        NAS_MML_InitUeIdPtmsiSignatureInvalid();
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_CS_DETACH;
    }

    return;                                                                     /* ����                                     */
}


/*****************************************************************************
 �� �� ��  : NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit
 ��������  : GMM��GMM_REGISTERED_IMSI_DETACH_INITIATED״̬�յ�MM��
             MMGMM_CS_LOCAL_DETACH_IND��Ϣ�Ĵ���
 �������  : MMCGMM_DETACH_REQ_STRU             *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
                ����RAU�����У�CS���DETACH��Ϣ�Ǳ�����ģ�������ʱ��CS��
                ��ʱ���Ѿ���ʱ�ˣ���ô���ͷŵ�ǰ������ע�����̣����յ�REL IND��Ϣ
                �󣬵ȶ�ʱ����ʱ�ٴ���RAU:Gmm_RcvRrmmRelInd_RauInit

*****************************************************************************/
VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RegInit(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;                           /* ��ǰ��������뼼�� */

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* ��ǰ��������RAU/attach������ */
    if ( (GMM_ATTACH_COMBINED            != g_GmmGlobalCtrl.ucSpecProc)
      && (GMM_ATTACH_WHILE_IMSI_ATTACHED != g_GmmGlobalCtrl.ucSpecProc) )
    {
        return ;
    }

    /* W�´��������֪ͨ�������������ͷ� */
    if ( ( NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat )
      && ( (GMM_TRUE                  == g_GmmGlobalCtrl.ucSigConFlg)
        || (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) ) )
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);

    }

    return;                                                                     /* ����                                     */
}



/*****************************************************************************
 �� �� ��  : NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit
 ��������  : GMM��GMM_REGISTERED_IMSI_DETACH_INITIATED״̬�յ�MM��
             MMGMM_CS_LOCAL_DETACH_IND��Ϣ�Ĵ���
 �������  : MMCGMM_DETACH_REQ_STRU             *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
                ����RAU�����У�CS���DETACH��Ϣ�Ǳ�����ģ�������ʱ��CS��
                ��ʱ���Ѿ���ʱ�ˣ���ô���ͷŵ�ǰ������ע�����̣����յ�REL IND��Ϣ
                �󣬵ȶ�ʱ����ʱ�ٴ���RAU:Gmm_RcvRrmmRelInd_RauInit

*****************************************************************************/
VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RauInit(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;                           /* ��ǰ��������뼼�� */

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* ��ǰ��������RAU/attach������ */
    if ( (GMM_RAU_COMBINED            != g_GmmGlobalCtrl.ucSpecProc)
      && (GMM_RAU_WITH_IMSI_ATTACH    != g_GmmGlobalCtrl.ucSpecProc) )
    {
        return ;
    }

    /* W�´��������֪ͨ�������������ͷ� */
    if ( ( NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat )
      && ( (GMM_TRUE                  == g_GmmGlobalCtrl.ucSigConFlg)
        || (GMM_RRC_RRMM_EST_CNF_FLG  == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)) )  )
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;                                                                     /* ����                                     */
}


#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : NAS_GMM_GprsLocalDetach_SvltePsTransfer
 ��������  : svlte ps transfer��������detach�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��11��25��
   ��    ��   : z00161729
   �޸�����   : SVLTE�Ż�G-TL ps�л������޸�

*****************************************************************************/
VOS_VOID NAS_GMM_GprsLocalDetach_SvltePsTransfer(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_REGISTERED_INITIATED:
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        case GMM_SERVICE_REQUEST_INITIATED:
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
            NAS_GMM_GprsLocalDetach();
            break;

        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            NAS_GMM_GprsLocalDetach();
            break;

        case GMM_REGISTERED_PLMN_SEARCH:

            /* GMM���б���DEACH */
            NAS_GMM_GprsLocalDetach();
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
            break;

        case GMM_REGISTERED_NO_CELL_AVAILABLE:

            /* GMM���б���DEACH */
            NAS_GMM_GprsLocalDetach();
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
            break;

        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:

            NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach();
            break;

        case GMM_REGISTERED_UPDATE_NEEDED:

            /* GMM���б���DEACH */
            NAS_GMM_GprsLocalDetach();

            /* Ǩ��״̬ */
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            break;

        case GMM_REGISTERED_LIMITED_SERVICE:

            /* GMM���б���DEACH */
            NAS_GMM_GprsLocalDetach();

            /* Ǩ��״̬ */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            break;

        case GMM_DEREGISTERED_NORMAL_SERVICE:
        case GMM_DEREGISTERED_LIMITED_SERVICE:
        case GMM_DEREGISTERED_ATTACH_NEEDED:
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        case GMM_DEREGISTERED_PLMN_SEARCH:

            /* GMM���б���DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNormalService();
            break;

        case GMM_DEREGISTERED_NO_IMSI:

            /* GMM���б���DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNoImsi();
            break;

        case GMM_SUSPENDED_NORMAL_SERVICE:
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:

        /* ��GMM_SUSPENDED_WAIT_FOR_SYSINFO�����ӽ��б���Detach�Ĵ��� */
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_GMM_LocalDetach_GprsSuspension();
            break;

        /* ��Gmm_MsgDistribute_GMM_TC_ACTIVE״̬�Ѿ����� */
        case GMM_TC_ACTIVE:
            break;

        /* ��GMM_DEREGISTERED_INITIATED״̬���յ�PS��detach���򲻴��� */
        case GMM_DEREGISTERED_INITIATED:

            return;

        default:
            NAS_GMM_GprsLocalDetach();

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
            break;
    }


    /* ֪ͨMM��ǰCS�ѱ���ȥע�� */
    if ( (VOS_TRUE             == NAS_GMM_IsNeedProcUserCsDetach())
      && (GMM_WAIT_CS_DETACH   == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH)) )
    {
        NAS_GMM_SndMmcMmDetachInfo();
        return;
    }

    return;
}
#endif



/*******************************************************************************
Module   : Gmm_RcvMmcDetachReq
Function : GMM�յ�MMCGMM_DETACH_REQ�ķַ�����
Input    : VOS_VOID      *pMsg;    ��ǰ�������Ϣ
Output   : ��
NOTE     : ��
Return   : ��
History  :
1. ��־��  2003.12.08  �¹�����

2.��    ��   : 2008��7��2��
  ��    ��   : l00107747
  �޸�����   : �������ⵥ�ţ�AT2D03900

3.��    ��   : 2009��01��20��
  ��    ��   : l00130025
  �޸�����   : ���ⵥ��:AT2D08378,��������ı�ʱ,MM/GMMû�ж�UE��mode���иı�;GMM��RAU�������յ�Detach����ʱ,ֱ�ӷ���,û�д���

4.��    ��   : 2010��1��16��
  ��    ��   : o00132663
  �޸�����   : NAS R7Э����������T3340��������ʱ������ǰ�����������ͷ���·
               �����浱ǰDetach����
5.��    ��   : 2011��3��2��
  ��    ��   : z00161729
  �޸�����   : DTS2010071601574:RAU��������յ�rau accept��Ҫ�ȴ�RABM��WRR�ظ����ٷ���RAU cmp��Ϣ�ڼ�,
               ����detach����,��RAU�����ٷ���
6.��    ��   : 2011��7��14��
  ��    ��   : h44270
  �޸�����   : V7R1 PhaseII�׶ε�����ע������
7.��    ��   : 2011��07��13��
  ��    ��   : w00166186
   �޸�����   : V7R1 PHASE II ATTACH/DETACH����

8. ��    ��   : 2012��1��12��
   ��    ��   : w00166186
   �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                 PLMN״̬������������Ϊ��֧��GMM��Ҫ��������֧����Ϣ֪ͨ��MMC.
9.��    ��   : 2012��01��12��
   ��    ��   : l65478
   �޸�����   : ���ⵥ�ţ�DTS2012010602762:SYSCFG���ó�֧��CS ONLY��
                 PS��Ȼ��ʾ��������
10.��    ��   : 2012��2��15��
   ��    ��   : w00166186
   �޸�����   : CSFB&PPAC&ETWS&ISR ����
11.��    ��  : 2012��08��24��
   ��    ��  : m00217266
   �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
12.��    ��   : 20013��02��19��
   ��    ��   : l00167671
   �޸�����   : DTS2013020607201
13.��    ��   : 2013��1��22��
   ��    ��   : W00176964
   �޸�����   : DTS2013012105162:OOS�����յ�PS��detach��Ҫ���б���detach
14.��    ��   : 2013��6��6��
   ��    ��   : w00167002
   �޸�����   : V9R1_SVLTE��Ŀ�޸�
                ����DETACH��Ϣʱ����Ҫ�ͷ���ǰ�ѻ����DETACH��Ϣ������ᵼ���ڴ�й¶

                2. GMM��ǰ�޷�����CS��DEACH,��֪ͨMM��ǰCS�ѱ���ȥע��
15.��    ��   : 2013��12��8��
   ��    ��   : z00161729
   �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
 16.��    ��   : 2013��12��8��
    ��    ��   : z00161729
    �޸�����   : DTS2014010202583:SVLTE�Ż�G-TL ps�л������޸�
*******************************************************************************/
VOS_VOID Gmm_RcvMmcDetachReq(
                         VOS_VOID       *pMsg                                   /* ��ǰ�������Ϣ                           */
                         )
{
    VOS_UINT32                   ulDetachType;                                  /* ����detach����                           */
    MMCGMM_DETACH_REQ_STRU      *pMsDetach;                                     /* ����ָ��                                 */

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;
    VOS_UINT8                           ucPsLocalDetachFlag;

    enUtranMode         = NAS_UTRANCTRL_GetCurrUtranMode();
    enCurNetRatType     = NAS_MML_GetCurrNetRatType();
    ucPsLocalDetachFlag = NAS_MML_GetPsLocalDetachFlag();
#endif

    pMsDetach    = (MMCGMM_DETACH_REQ_STRU *)pMsg;                              /* ��ʼ��ָ��                               */
    ulDetachType = pMsDetach->enDetachType;                                     /* ��ʼ��detach����                         */


    ulDetachType = NAS_GMM_ConvertDetachType(ulDetachType);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* svlte���Կ�������gmm�յ�mtc��rrc�ٶ�����Ϣ��modem0 psҪǨ�Ƶ�modem1ʱΪ�˼���detach ps
       ʱ�䣬ֱ�ӽ��б���ps detach�������罻�� */
    if ((VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode)
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurNetRatType)
     && (VOS_TRUE == ucPsLocalDetachFlag)
     && (MMC_GMM_PS_DETACH == ulDetachType))
    {
        NAS_GMM_GprsLocalDetach_SvltePsTransfer();


        NAS_MML_SetPsLocalDetachFlag(VOS_FALSE);
        return;
    }
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬���в�ͬ����                 */
    case GMM_REGISTERED_INITIATED:                                              /* GMM-REGISTERED-INITIATED״̬             */

        /* GMM��GMM_REGISTERED_INITIATED״̬�յ�DETACH REQ�Ĵ��� */
        NAS_GMM_RcvMmcGmmDetachReqMsg_GmmRegisteredInitiated(pMsg);
        return;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:

        /* ��RAU�������յ�detach����,�������Ϣ,��RAU��ɺ��ٽ���DETACH���� */
        NAS_GMM_SaveDetachMsg(pMsg);
        return;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:

        /* ��IMSI DETACH�������յ�detach����,����µ�DETACH������IMSI����,
           �������Ϣ,��RAU��ɺ��ٽ���DETACH���� */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_SaveDetachMsg(pMsg);
        }
        return;

    case GMM_SERVICE_REQUEST_INITIATED:                                         /* GMM-SERVICE-REQUEST-INITIATED״̬        */
        NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(pMsg);
        return;

    case GMM_REGISTERED_NORMAL_SERVICE:                                         /* GMM-REGISTERED.NORMAL-SERVIC״̬         */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:                                /* REGISTERED.ATTEMPTING-TO-UPDATE-MM״̬   */
        NAS_GMM_ProcDetachReq_RegNmlServ(pMsDetach, ulDetachType);
        return;

    case GMM_REGISTERED_PLMN_SEARCH:                                            /* GMM-REGISTERED.PLMN-SEARCH״̬           */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM���б���DEACH */
            NAS_GMM_GprsLocalDetach();

            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
        }
        break;

    case GMM_REGISTERED_NO_CELL_AVAILABLE:                                      /* GMM-REGISTERED.NO-CELL-AVAILABLE״̬     */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM���б���DEACH */
            NAS_GMM_GprsLocalDetach();

            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
        }
        break;

    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:                                   /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE״̬  */
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach();
        }
        break;

    case GMM_REGISTERED_UPDATE_NEEDED:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM���б���DEACH */
            NAS_GMM_GprsLocalDetach();

            /* Ǩ��״̬ */
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
        }
        break;

    case GMM_REGISTERED_LIMITED_SERVICE:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM���б���DEACH */
            NAS_GMM_GprsLocalDetach();

            /* Ǩ��״̬ */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
        }
        break;

    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM���б���DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNormalService();
        }

        break;

    case GMM_DEREGISTERED_NO_IMSI:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            /* GMM���б���DEACH */
            NAS_GMM_LocalDetach_GmmDeregisteredNoImsi();
        }

        break;

    case GMM_SUSPENDED_NORMAL_SERVICE:

    case GMM_GPRS_SUSPENSION:
    case GMM_SUSPENDED_GPRS_SUSPENSION:

    /* ��GMM_SUSPENDED_WAIT_FOR_SYSINFO�����ӽ��б���Detach�Ĵ��� */
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:

        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_LocalDetach_GprsSuspension();
        }

        break;

    /* ��Gmm_MsgDistribute_GMM_TC_ACTIVE״̬�Ѿ����� */
    case GMM_TC_ACTIVE:
        break;

    /* ��GMM_DEREGISTERED_INITIATED״̬���յ�PS��detach���򲻴��� */
    case GMM_DEREGISTERED_INITIATED:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            return;
        }

        /* ͳһ����CS��DETACH */
        break;

    default:
        if (MMC_GMM_CS_DETACH != ulDetachType)
        {
            NAS_GMM_GprsLocalDetach();
        }

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcDetachReq:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;
    }


    /* ֪ͨMM��ǰCS�ѱ���ȥע�� */
    if ( (VOS_TRUE             == NAS_GMM_IsNeedProcUserCsDetach())
      && (GMM_WAIT_CS_DETACH   == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH)) )
    {
        NAS_GMM_SndMmcMmDetachInfo();
        return;
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcDetachReq_RegNoCell
  Function : ��GMM_REGISTERED_NO_CELL_AVAILABLE״̬���յ�MMCGMM_DETACH_REQ�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.11  �¹�����
    2.��    ��   : 2009��05��25��
      ��    ��   : h44270
      �޸�����   : ���ⵥ��:AT2D09923/AT2D12099,����attach����������tlli������
    3.��    ��   : 2011��07��13��
      ��    ��   : w00166186
      �޸�����   : V7R1 PHASE II ATTACH/DETACH����
    4. ��    ��   : 2012��1��12��
       ��    ��   : w00166186
       �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                      PLMN״̬������������Ϊ��֧��GMM��Ҫ��������֧����Ϣ֪ͨ��MMC.
*******************************************************************************/
VOS_VOID Gmm_RcvMmcDetachReq_RegNoCell(VOS_VOID)
{
    Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);                          /* ����״̬�Ĺ�������                       */
    NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );              /* ����PS��attach��ֹ��־                   */
    gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_FALSE;

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }


    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);
}

/*******************************************************************************
  Module   : Gmm_MsInitNormalDetach
  Function : MS������detach���̴���
  Input    : VOS_UINT32    ulDetachType    detach����
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.08  �¹�����

  2.��    ��   : 2006��11��06��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D05787

  3.��    ��   : 2009��01��20��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D08378,��������ı�ʱ,MM/GMMû�ж�UE��mode���иı�;
                 GMM��RAU�������յ�Detach����ʱ,ֱ�ӷ���,û�д���
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
  6.��    ��   : 2013��6��8��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:�����߶�:����Чʱ��MMC_GMM_PS_CS_DETACH��
                 GMM_DETACH_NORMAL���͵����̡�
  7.��    ��   : 2014��7��9��
    ��    ��   : w00242748
    �޸�����   : DSDS III������
*******************************************************************************/
VOS_VOID Gmm_MsInitNormalDetach(
    VOS_UINT32                          ulDetachType                   /* detach����                               */
)
{
    VOS_UINT8                           ucSimCsRegStatus;                       /* SIM��CS���ע�������µĿ��Ƿ���ЧVOS_TRUE:CS��Ŀ���Ч,VOS_FALSE:CS��Ŀ���Ч*/

    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();

    switch (ulDetachType)
    {                                                                           /* �ж�detach���ͽ��в�ͬ����               */
    case MMC_GMM_PS_CS_DETACH:                                                  /* combined detach                          */
        if((VOS_FALSE      == NAS_MML_GetCsRestrictRegisterFlg())
        && (VOS_TRUE       == ucSimCsRegStatus)
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod))
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED;                   /* ��ֵ��ǰspesific����                     */
        }
        else
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL;
        }
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsInitNormalDetach:INFO: combined detach procedure started");

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_INITIATED);                    /* ״̬Ǩ�Ƶ�GMM DEREGISTERED INITIATED     */

        NAS_GMM_SndMmGprsDetachInitiation();                                       /* ��MMC����MMCGMM_GPRS_DETACH_INITIATION   */
        Gmm_Com_MsInitNormalDetach();                                           /* ����MS������detach�Ĺ�������             */


        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_MsInitNormalDetach:NORMAL: STATUS IS GMM_DEREGISTERED_INITIATED");

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        break;
    case MMC_GMM_PS_DETACH:                                                     /* GPRS detach                              */
        g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL;                         /* ��ֵ��ǰspesific����                     */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsInitNormalDetach:INFO: normal detach procedure start");

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_INITIATED);                    /* ״̬Ǩ�Ƶ�GMM DEREGISTERED INITIATED     */

        Gmm_Com_MsInitNormalDetach();                                           /* ����MS������detach�Ĺ�������             */


        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_MsInitNormalDetach:NORMAL: STATUS IS GMM_DEREGISTERED_INITIATED");

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        break;
    case MMC_GMM_CS_DETACH:                                                     /* IMSI detach                              */
        if((VOS_FALSE == NAS_MML_GetCsRestrictRegisterFlg())
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod))
        {
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_WITH_IMSI;                      /* ��ֵ��ǰspesific����                     */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsInitNormalDetach:INFO: IMSI detach procedure started");

            GMM_CasFsmStateChangeTo(GMM_REGISTERED_IMSI_DETACH_INITIATED);

            NAS_GMM_SndMmImsiDetachInitiation();                                       /* ��MMC����MMCGMM_IMSI_DETACH_INITIATION   */
            Gmm_Com_MsInitNormalDetach();                                           /* ����MS������detach�Ĺ�������             */


            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_MsInitNormalDetach:NORMAL: STATUS IS GMM_REGISTERED_IMSI_DETACH_INITIATED");

            g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsInitNormalDetach:WARNING: Detach Type is Abnormal");
        break;
    }

    return;                                                                     /* ����                                     */
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_ProcDetachReq_RegNmlServ
 ��������  : ��������״̬����DETACH����
 �������  : VOS_UINT32 ulOpID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��15��
    ��    ��   : ��ë/00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��02��01��
    ��    ��   : l65478
    �޸�����   : DTS2013020104880

*****************************************************************************/
VOS_VOID NAS_GMM_ProcDetachReq_RegNmlServ(
    MMCGMM_DETACH_REQ_STRU             *pstDetachReq,
    VOS_UINT32                          ulDetachType                   /* detach����                               */
)
{
    MMCGMM_DETACH_REQ_STRU              *pstBufDetach = VOS_NULL_PTR;

    if ((GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
     || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg))
    {
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;    /* ��ԭ�ﻺ���־                           */
        pstBufDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
        if (VOS_NULL_PTR == pstBufDetach)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_ProcDetachReq_RegNmlServ:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
              return;
        }

        Gmm_MemCpy(pstBufDetach, pstDetachReq, sizeof(MMCGMM_DETACH_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pstBufDetach;       /* ����ԭ��                                 */
    }
    else if ((gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
          && (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
          )
    {
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;    /* ��ԭ�ﻺ���־                           */
        pstBufDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
        if (VOS_NULL_PTR == pstBufDetach)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_ProcDetachReq_RegNmlServ:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
              return;
        }
        Gmm_MemCpy(pstBufDetach, pstDetachReq, sizeof(MMCGMM_DETACH_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pstBufDetach;       /* ����ԭ��                                 */

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    else
    {
        Gmm_MsInitNormalDetach(ulDetachType);                                   /* ����MS������detach����                   */
    }
}

/*******************************************************************************
  Module   : Gmm_Com_MsInitNormalDetach
  Function : MS������detach���̵Ĺ�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
*******************************************************************************/
VOS_VOID Gmm_Com_MsInitNormalDetach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachRequest;                                            /* ����ָ��                                 */

    pDetachRequest = Gmm_DetachRequestMsgMake();                                /* ����detach request��Ϣ��������           */

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* ��ǰ����������                           */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachRequest);           /* ����detach request��Ϣ                   */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* ����T3321                                */
    }
    else
    {                                                                           /* ��ǰû������������                       */
        Gmm_SndRrmmEstReq(RRC_EST_CAUSE_DETACH,
                          GMM_RRC_IDNNS_UNKNOWN,
                          pDetachRequest);                                      /* ������������                             */
        Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcPowerOffReq
  Function : GMM�յ�MMCGMM_POWER_OFF_REQ�ķַ�����
  Input    : VOS_VOID   *pMsg    ԭ��ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2. ��    ��   : 2009��5��9��
       ��    ��   : l00130025
       �޸�����   : �������ⵥ�ţ�AT2D11645/AT2D11797,�ػ�����detach��EST_REQʧ�ܣ�Gmm�ᷴ������EST_REQ
    3. ��    ��   : 2009��05��23��
       ��    ��   : L65478
       �޸�����   : ���ⵥ��:AT2D06770,RAUʧ�ܣ���ΪGRM������ԭ����DATA��ʵ��Ӧ��������
    4. ��    ��   : 2010��07��26��
       ��    ��   : L65478
       �޸�����   : ���ⵥ��:DTS2010072200479,����ע������У��ػ����ٿ���ʱʧ�ܣ���ΪGMMû�����̴���ػ���Ϣ������MMC������ʱ����ʱ
    5. ��    ��   : 2010��09��13��
       ��    ��   : L65478
       �޸�����   : ���ⵥ��:DTS2010091301310,WCDMA�¹ػ������¿�������GSMģʽ���޷�ע��ɹ�
    6. ��    ��   : 2010��11��11��
       ��    ��   : ŷ����
       �޸�����   : DTS2010111003071��GSM�£�����ģʽII��CS Only��PDP�����ֱ
                    �ӹػ�������MM/GMMͬʱ��������detach����
    7.��    ��   : 2012��1��9��
      ��    ��   : l00130025
      �޸�����   : DTS2011122900476,�ͷŻ����Gsmϵͳ��Ϣ
    8.��    ��   : 2012��8��25��
      ��    ��   : m00217266
      �޸�����   : ɾ��GMM_SaveErrCode�����Gmm_Save_Detach_Cause��
                 ���浼����Attach�л���Detach��ԭ��ֵ

    9.��    ��   : 2012��11��10��
      ��    ��   : w00176964
      �޸�����   : DTS2012110707605:PSδattach��,ֱ�Ӹ�MMC�ظ��ػ����,�ӿ�ػ��ٶ�
   10.��    ��   : 2011��12��28��
      ��    ��   : l00167671
      �޸�����   : �޸����ⵥDTS2012122001075,���ⵥ��������:
                  PS���������з���RA�ı䣬�ó��������CS����ҵ����PS����RAU
                  �ᱻ��ȷ�����Ƴٵ�CS�����ͷ�ʱ�������޸Ĵ˳����еĲ�������:
                  ��CS����ҵ�����WAS����RRMM_REL_REQ������WAS�ͷ����ӣ�
                  ������ϵͳ��Ϣ�����յ�WAS��RRMM_REL_INDʱ�ñ����ϵͳ��Ϣ��RAU
   11.��    ��   : 2013��2��4��
      ��    ��   : w00176964
      �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*******************************************************************************/
VOS_VOID Gmm_RcvMmcPowerOffReq(
                           VOS_VOID *pMsg                                       /* ԭ��ָ��                                 */
                           )
{
    MMCGMM_POWER_OFF_REQ_STRU      *ptr;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PS_DETACH);

    /* �����ػ�������ʱ����*/
    Gmm_TimerStart(GMM_TIMER_1S);

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
        && ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)))
    {                                                                           /* ״̬��GMM-����-INITIATED                 *
                                                                                 * �������������ڽ�����������               */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_POWEROFF;      /* �û����־                               */
        ptr = (MMCGMM_POWER_OFF_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_POWER_OFF_REQ_STRU));
        if (VOS_NULL_PTR == ptr)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcPowerOffReq:WARNING: STATUS IS GMM_REGISTERED_IMSI_DETACH_INITIATED");
            return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_POWER_OFF_REQ_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff = (VOS_UINT32)ptr;         /* ����ԭ��                                 */

        return;                                                                 /* ����                                     */
    }

    /* GMM���ϲ�Ӧ�ûظ�ʧ�� */
    Gmm_ComCnfHandle();
    Gmm_HoldBufferFree();
    /* �ػ����GMM���� */
    GMM_BufferMsgDump();

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    /* PSδattach��,ֱ�Ӹ�MMC�ظ��ػ���� */
    if ((GMM_STATUS_ATTACHED                    != g_MmSubLyrShare.GmmShare.ucAttachSta)
     && (GMM_REGISTERED_INITIATED               != g_GmmGlobalCtrl.ucState)
     && (GMM_ROUTING_AREA_UPDATING_INITIATED    != g_GmmGlobalCtrl.ucState))
    {
        g_GmmReqCnfMng.ucCnfMask = 0;
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;

        Gmm_ComStaChg(GMM_NULL);                                                /* ����״̬�Ĺ�������                       */
        Gmm_SndMmcPowerOffCnf();                                                /* ��MMC����MMCGMM_POWER_CNF               */
        Gmm_ComVariantInit();                                                   /* ���ȫ�ֱ���                             */

        return;
    }

    enCurRat = NAS_MML_GetCurrNetRatType();

    /*G�£���ǰMM��ҵ�����ڽ��У�����ػ����� */
    if ((MMC_MM_SIGNALING_STATUS_PRESENT == MM_GetSignalingStatus())
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        gstGmmSuspendCtrl.ucPowerOff = GMM_POWER_OFF_RCV;

        return;
    }

    /* ���йػ����� */
    Gmm_TimerStop(GMM_TIMER_ALL);

    g_GmmReqCnfMng.ucCnfMask = 0;
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* A+I                                      */
        if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState))

        {                                                                       /* MM��GMM��ע��                            */
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF;         /* �õ�ǰ��specific����                     */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");

        }
        else if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            && (MM_STATUS_DETACHED
            == g_MmSubLyrShare.MmShare.ucCsAttachState))
        {                                                                       /* MMδע��,GMMע��                         */
            if((GMM_RAU_COMBINED == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_RAU_WITH_IMSI_ATTACH == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                   /* ��ǰ������combined                       */
                g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF;     /* �õ�ǰ��specific����                     */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");
            }
            else
            {                                                                   /* ��ǰ���̲���combined                     */
                g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;       /* �õ�ǰ��specific����                     */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
            }
        }
        else
        {                                                                       /* GMMδע��                                */
            if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {                                                                   /* ��ǰ״̬��REGISTERED_INITIATED           */

                if ((GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProc)
                   ||(GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc))
                {                                                               /* ����normal attach                        */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;   /* �õ�ǰ��specific����                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
                }
                else
                {                                                               /* ����combine attach                       */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF; /* �õ�ǰ��specific����                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");
                }
            }
            else if (GMM_ROUTING_AREA_UPDATING_INITIATED
                                            == g_GmmGlobalCtrl.ucState)
            {                                                                   /* ��ǰ״̬��RAU_INITIATED                  */

                if ((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProc)
                    ||(GMM_RAU_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc))
                {                                                               /* ����normal rau                           */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;   /* �õ�ǰ��specific����                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
                }
                else
                {                                                               /* ����combine rau                          */
                    g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_COMBINED_POWER_OFF; /* �õ�ǰ��specific����                     */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: combined detach(power off) procedure started");
                }
            }
            else
            {                                                                   /* ����״̬                                 */
                Gmm_ComStaChg(GMM_NULL);                 /* ����״̬�Ĺ�������                       */
                Gmm_SndMmcPowerOffCnf();                                        /* ��MMC����MMCGMM_DETACH_CNF               */
                Gmm_ComVariantInit();                                           /* ���ȫ�ֱ���                             */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: specific procedure ended");
                return;
            }
        }
    }
    else
    {                                                                           /* A+II��C                                  */
        if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
            || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            || (GMM_ROUTING_AREA_UPDATING_INITIATED
                                             == g_GmmGlobalCtrl.ucState))
        {                                                                       /* GMMע�����
                                                                                 * ��ǰ״̬��REGISTERED_INITIATE            */
            g_GmmGlobalCtrl.ucSpecProc = GMM_DETACH_NORMAL_POWER_OFF;           /* �õ�ǰ��specific����                     */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: normal detach(power off) procedure started");
        }
        else
        {                                                                       /* GMMδע��                                */
            Gmm_ComStaChg(GMM_NULL);                     /* ����״̬�Ĺ�������                       */
            Gmm_SndMmcPowerOffCnf();                                            /* ��MMC����MMCGMM_DETACH_CNF               */
            Gmm_ComVariantInit();                                                   /* ���ȫ�ֱ���                             */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcPowerOffReq:INFO: specific procedure ended");
            return;
        }
    }

    Gmm_PowerOffDetach();                                                       /* ����Power Offʱ��detach����              */

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_PowerOffDetach
  Function : Power Offʱ��detach����
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.08  �¹�����
  2.��    ��   : 2009��5��9��
    ��    ��   : l00130025
    �޸�����   : �������ⵥ�ţ�AT2D11645/AT2D11797,�ػ�����detach��EST_REQʧ�ܣ�Gmm�ᷴ������EST_REQ
  3.��    ��   : 2009��05��23��
    ��    ��   : L65478
    �޸�����   : ���ⵥ��:AT2D06770,RAUʧ�ܣ���ΪGRM������ԭ����DATA��ʵ��Ӧ��������
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��    ��   : 2011��07��13��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  6.��    ��   : 2012��04��20��
    ��    ��   : L65478
    �޸�����   : DTS2012042005349��G�¹ػ�ʱû�й���TTF������TTFһֱ����,IOTʧ��
  7.��    ��   : 2012��10��12��
    ��    ��   : w00176964
    �޸�����   : DTS2012091400694:Gģ�ػ���
  8.��    ��   : 2015��2��6��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���
*******************************************************************************/
VOS_VOID Gmm_PowerOffDetach(VOS_VOID)
{
    NAS_MSG_STRU        *pDetachRequest;                                        /* ����ָ��                                 */

    if ( (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_LIMITED_SERVICE  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_UPDATE_NEEDED  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_PLMN_SEARCH  == g_GmmGlobalCtrl.ucState) )
    {
        if(GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
        }
        if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* ��ǰ������POWER OFF                      */
            if (GMM_UEID_P_TMSI_SIGNATURE
             == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
            {                                                                   /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
                g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                    &= ~GMM_UEID_P_TMSI_SIGNATURE;                              /* ���P_TMSI_SIGNATURE                     */
                NAS_MML_InitUeIdPtmsiSignatureInvalid();
                if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
                }
                else
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
                }
            }

            if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
            {                                                                       /* ��combined����                           */
                NAS_GMM_SndMmGprsDetachInitiation();                                   /* ����ԭ��֪ͨMMC                          */
            }

            Gmm_SndMmcPowerOffCnf();                                            /* ��MMC��POWER OFF����Ӧ                   */

            Gmm_ComStaChg(GMM_NULL);                     /* ����״̬�Ĺ�������                       */

            /*Gmm_TimerDistroy();*/                                                     /* ��������TIMER                            */
            Gmm_ComVariantInit();                                               /* ���ȫ�ֱ���                             */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* �嵱ǰ����                               */
        }
        else if ((GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* ��ǰ������SIM REMOVE                     */
            /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }


            /* ��MMC����PSע���� */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                            /* ����״̬�Ĺ�������                       */

            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* �嵱ǰ����                               */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim5sExpired:INFO: specific procedure ended");

            g_GmmReqCnfMng.ucCnfMask = 0;                                       /* ��ȴ�cnf��־                            */
        }
        else
        {
        }
    }
    else
    {
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            if(GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
                gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_DETACH;
            }
        }

        /* �ڷ���detachʱ���п���ԭ��������LLC���������ڷ���detachǰ����Ҫ�ָ�LLC */
        if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
        {
            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_SIGNAL);
        }

        pDetachRequest = Gmm_DetachRequestMsgMake();                            /* ����detach request��Ϣ��������           */

        if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* ��combined����                           */
            NAS_GMM_SndMmGprsDetachInitiation();                                   /* ����ԭ��֪ͨMMC                          */
        }
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* ��ǰ������������                         */
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachRequest);       /* ����detach request��Ϣ                   */
            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NORMAL_SERVICE);
            Gmm_TimerStart(GMM_TIMER_1S);                                       /* ����1S��ʱ��                             */
        }
        else
        {                                                                       /* ��ǰ��������������                       */
            Gmm_SndRrmmEstReq(RRC_EST_CAUSE_DETACH,
                              GMM_RRC_IDNNS_UNKNOWN,
                              pDetachRequest);                                  /* ������������                             */

            Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ESTING);      /* ֪ͨMMC PS�������������ڽ���             */
            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NORMAL_SERVICE);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_PowerOffDetach:NORMAL: STATUS IS GMM_DEREGISTERED_NORMAL_SERVICE");

            if ((GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                   /* ��ǰ������combined sim remove��power off */
                g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;   /* �ñ�־λ����detach                       */
            }
            Gmm_TimerStart(GMM_TIMER_1S);                                       /* ����5S��ʱ��                             */
        }
        ++ (g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt);

        /* G�¹ػ��ο��������:GMM����5S��ʱ��,����detach������ֻ��Ҫ����5�� */
        Gmm_TimerStart(GMM_TIMER_DETACH_FOR_POWER_OFF);
    }
    return;                                                                     /* ����                                     */
}

/*lint -e438 -e830*/

/*******************************************************************************
  Module   : Gmm_DetachRequestMsgMake
  Function : Detach request��Ϣ����
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : NAS_MSG_STRU *
  History  :
  1. ��־��  2003.12.08  �¹�����
  2. ��    ��   : 2006��11��20��
     ��    ��   : s46746
     �޸�����   : �������������ⵥ�ţ�A32D07433
  3. ��    ��   : 2009��06��17��
     ��    ��   : ouyangfei o00132663
     �޸�����   : �����ն˿����������޸ģ�R99��ǰ�汾�����ɿ�ѡIE
  4. ��    ��   : 2009��08��14��
     ��    ��   : ouyangfei o00132663
     �޸�����   : AT2D13748:��ȡ3GPPЭ��汾��������������Ӧ�ò�ѯPS��汾��
  5.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
*******************************************************************************/
NAS_MSG_STRU* Gmm_DetachRequestMsgMake(VOS_VOID)
{
    NAS_MSG_FOR_PCLINT_STRU    *pDetachRequest;                                 /* ����ָ��                                 */
    NAS_MSG_STRU               *pNasMsg;
    VOS_UINT32                  ulMsgLen;                                       /* ��������洢��Ϣ����                     */
    VOS_UINT8                   ucPtmsiFlg;                                     /* ���������־�Ƿ����P-TMSI               */
    VOS_UINT8                   ucPtmsiSigFlg;                                  /* ���������־�Ƿ����P-TMSI signature     */
    VOS_UINT8                   ucNumber;
    VOS_INT8                    cVersion;

    cVersion = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);

    ulMsgLen        = GMM_MSG_LEN_DETACH_REQUEST;                               /* ��ʼ����ʱ����,��Ϣ�б�ѡ����            */
    ucPtmsiFlg      = GMM_FALSE;                                                /* ��ʼ����ʱ����                           */
    ucPtmsiSigFlg   = GMM_FALSE;                                                /* ��ʼ����ʱ����                           */
    pDetachRequest  = VOS_NULL_PTR;                                             /* ��ʼ����ʱ����                           */

    /* R99��ǰ�汾�޿�ѡIE */
    if(PS_PTL_VER_PRE_R99 != cVersion)
    {
        if (GMM_UEID_P_TMSI == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI))
        {                                                                           /* ����P-TMSI                               */
            ulMsgLen  += 7;                                                         /* ��Ϣ��������                             */
            ucPtmsiFlg = GMM_TRUE;                                                  /* ��־����P-TMSI                           */
        }

        if (  (GMM_TRUE == ucPtmsiFlg)
            &&(GMM_UEID_P_TMSI_SIGNATURE == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE)))
        {                                                                           /* ����P-TMSI signature                     */
            ulMsgLen     += 5;                                                      /* ��Ϣ��������                             */
            ucPtmsiSigFlg = GMM_TRUE;                                               /* ��־����P-TMSI signature                 */
        }
    }

    if (ulMsgLen <= 4)
    {                                                                           /* ��Ϣ����С�ڵ���4                        */
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));          /* �����ڴ�ռ�                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DetachRequestMsgMake:error: Alloc mem fail.");
            return pNasMsg;
        }
        pDetachRequest = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(pDetachRequest, 0, sizeof(NAS_MSG_STRU));                    /* ��������ڴ�ռ���0                      */
    }
    else
    {                                                                           /* ��Ϣ���ȴ���4                            */
        pNasMsg = (NAS_MSG_STRU *)Gmm_MemMalloc(
                                         (sizeof(NAS_MSG_STRU) + ulMsgLen) - 4);  /* �����ڴ�ռ�                             */
        if (VOS_NULL_PTR == pNasMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DetachRequestMsgMake:error: Alloc mem fail.");
            return pNasMsg;
        }
        pDetachRequest = (NAS_MSG_FOR_PCLINT_STRU *)pNasMsg;
        Gmm_MemSet(pDetachRequest, 0, (sizeof(NAS_MSG_STRU) + ulMsgLen) - 4);   /* ��������ڴ�ռ���0                      */
    }

    pDetachRequest->ulNasMsgSize = ulMsgLen;                                    /* ��ֵ��Ϣ����                             */
    pDetachRequest->aucNasMsg[0] = GMM_PD_GMM;                                  /* PD��Skip Indicator                       */
    pDetachRequest->aucNasMsg[1] = GMM_MSG_DETACH_REQUEST;                      /* message type                             */
    switch (g_GmmGlobalCtrl.ucSpecProc)
    {                                                                           /* �ж�detach���ͽ��в�ͬ����               */
    case GMM_DETACH_COMBINED:                                                   /* combined detach                          */
        pDetachRequest->aucNasMsg[2] = GMM_COMBINED_DETACH_NORMAL;              /* detach type                              */
        break;
    case GMM_DETACH_NORMAL:                                                     /* normal detach                            */
    case GMM_DETACH_NORMAL_NETMODE_CHANGE:
        pDetachRequest->aucNasMsg[2] = GMM_GPRS_DETACH_NORMAL;                  /* detach type                              */
        break;
    case GMM_DETACH_WITH_IMSI:                                                  /* IMSI detach                              */
        pDetachRequest->aucNasMsg[2] = GMM_IMSI_DETACH_MS_TO_NET;               /* detach type                              */
        break;
    case GMM_DETACH_COMBINED_POWER_OFF:                                         /* combined detach with power off           */
    case GMM_DETACH_COMBINED_SIM_REMOVE:                                        /* combined detach with sim removing        */
        pDetachRequest->aucNasMsg[2] = GMM_COMBINED_DETACH_POWEROFF;            /* detach type                              */
        break;
    case GMM_DETACH_NORMAL_POWER_OFF:                                           /* GPRS detach with power off               */
    case GMM_DETACH_NORMAL_SIM_REMOVE:                                          /* GPRS detach with sim removing            */
        pDetachRequest->aucNasMsg[2] = GMM_GPRS_DETACH_POWEROFF;                /* detach type                              */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_DetachRequestMsgMake:WARNING: g_GmmGlobalCtrl.ucSpecProc is Abnormal");
        Gmm_MemFree(pDetachRequest);
        return VOS_NULL_PTR;
    }

    /* R99��ǰ�汾�޿�ѡIE */
    if(PS_PTL_VER_PRE_R99 != cVersion)
    {
        ucNumber = 3;
        if (GMM_TRUE == ucPtmsiFlg)
        {                                                                           /* ����P-TMSI                               */
            /*lint -e961*/
            pDetachRequest->aucNasMsg[ucNumber++]
                                        = GMM_IEI_P_TMSI;                           /* IEI                                      */
            pDetachRequest->aucNasMsg[ucNumber++]
                                        = 0x05;                                     /* length                                   */
            pDetachRequest->aucNasMsg[ucNumber++]
                                        = GMM_MOBILE_ID_TMSI_PTMSI | 0xf0;          /* type of id and the 5-8 bit               */
            /*lint +e961*/
            Gmm_MemCpy(&pDetachRequest->aucNasMsg[ucNumber],
                       NAS_MML_GetUeIdPtmsi(),
                       NAS_MML_MAX_PTMSI_LEN);                                         /* P_TMSI��ֵ                               */
            ucNumber = ucNumber + NAS_MML_MAX_PTMSI_LEN;

        }
        if (GMM_TRUE == ucPtmsiSigFlg)
        {                                                                           /* ����P-TMSI signature                     */
            /*lint -e961*/
            pDetachRequest->aucNasMsg[ucNumber++] = GMM_IEI_P_TMSI_SIGNATURE;       /* IEI                                      */
            pDetachRequest->aucNasMsg[ucNumber++] = 0x03;                           /* length                                   */
            /*lint +e961*/
            Gmm_MemCpy(&(pDetachRequest->aucNasMsg[ucNumber]),
                       NAS_MML_GetUeIdPtmsiSignature(),
                       NAS_MML_MAX_PTMSI_SIGNATURE_LEN);                            /* P_TMSI signature��ֵ */
            ucNumber += NAS_MML_MAX_PTMSI_SIGNATURE_LEN;
        }
    }

    /* ����Detach���̣�����GMM��·�ͷſ��Ʊ��� */
    NAS_GMM_UpdateGmmLinkCtrlStru();
    g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg =  VOS_FALSE;
    g_GmmDetachCtrl.ucDetachProc = g_GmmGlobalCtrl.ucSpecProc;

    return (NAS_MSG_STRU *)pDetachRequest;                                                      /* �������ɵ���Ϣ                           */
}
/*lint +e438 +e830*/

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg
  Function : GMM�յ�DETACH_REQUEST�ķַ�����
  Input    : NAS_MSG_STRU   *pMsg  ��ǰ�������Ϣ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.08  �¹�����
  2. x51137 2006/4/28 A32D02889
  3.��    ��   : 2012��1��12��
    ��    ��   : w00166186
    �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                 PLMN״̬������������Ϊ��֧��GMM��Ҫ��������֧����Ϣ֪ͨ��MMC.
  4.��    ��   : 2012��3��3��
    ��    ��   : z00161729
    �޸�����   : V7R1 C50 ֧��ISR�޸�,T3312����ֹͣ��ʱ����֪ͨL
  5.��    ��   : 2012��8��25��
    ��    ��   : m00217266
    �޸�����   : ɾ��GMM_SaveErrCode�����Gmm_Save_Detach_Cause��
                ���浼��Attachʧ�ܵ�ԭ��ֵ

  6.��    ��   : 2013��6��8��
    ��    ��   : w00167002
    �޸�����   : V9R1_SVLTE:�����߶�����:ucDetachType����ά������.
  7.��    ��   : 2014��10��20��
    ��    ��   : h00285180
    �޸�����   : �ܾ�ԭ��ֵ�Ż�PhaseII DTS2014110307415
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg(
                             NAS_MSG_FOR_PCLINT_STRU       *pMsg
                             )
{
    VOS_UINT8               ucDetachType;                                           /* ������ʱ����                             */
    VOS_UINT8               ucGmmCause;                                             /* ������ʱ����                             */
    NAS_MSG_STRU        *pGmmStatus;
    VOS_UINT8           ucForceToStandby;

    ucDetachType = 0;                                                           /* ��ʼ����ʱ����                           */
    ucGmmCause   = NAS_MML_REG_FAIL_CAUSE_NULL;                                 /* ��ʼ����ʱ����                           */

    if (pMsg->ulNasMsgSize < GMM_MSG_LEN_DETACH_REQUEST)
    {                                                                           /* ��Ϣ�б�ѡ��ĳ��Ȳ���                   */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg:WARNING: Length of DETACH REQUEST is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;                                                                 /* ����                                     */
    }

    ucForceToStandby = (VOS_UINT8)((pMsg->aucNasMsg[2]>>4) & 0x0F);
    if (1 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_TRUE;
    }
    else if (0 == ucForceToStandby)
    {
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }
    else
    {                                                                           /* Force to standby                         */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg:WARNING: DETACH REQUEST is semantically incorrect");
        /*pGmmStatus = */
        /*    Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);*/

        /*Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);*/
        /*return;*/
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    ucDetachType = (VOS_UINT8)(pMsg->aucNasMsg[2] & 0x0F);                          /* ����Ϣ��ȡdetach����                     */
    if ((GMM_NET_DETACH_REATTACH_REQUIRED != ucDetachType)
        && (GMM_NET_DETACH_IMSI_DETACH    != ucDetachType))
    {                                                                           /* detach���Ͳ���reattach required
                                                                                 * ����Ҳ����imsi detach                    */
        ucDetachType = GMM_NET_DETACH_REATTACH_NOT_REQUIRED;                    /* ����Ϣ������Ϊreattach not required      */
    }
    /* �����PS��DETACH����Ҫ���津��ԭ�� */
    if (GMM_NET_DETACH_IMSI_DETACH != ucDetachType)
    {
        if (5 == pMsg->ulNasMsgSize)
        {                                                                           /* ��Ϣ���ȵ���5                            */
            if (GMM_IEI_GMM_CAUSE != pMsg->aucNasMsg[3])
            {
                /* ԭ��ֵ��IEI����ȷ */
                NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PROTOCOL_ERROR);
            }
            else
            {
                /* ԭ��ֵ��IEI��ȷ */
                NAS_GMM_ChangeDetachCauseAvoidInvalidSim(&(pMsg->aucNasMsg[4]));

                ucGmmCause = pMsg->aucNasMsg[4];                                    /* ����Ϣ��ȡdetachԭ��                     */
                NAS_GMM_SetAttach2DetachErrCode(NAS_GMM_TransGmmNwCause2GmmSmCause(ucGmmCause));
            }
        }
        else
        {
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PROTOCOL_ERROR);
        }
    }

#if (FEATURE_ON == FEATURE_PTM)
    NAS_GMM_NwDetachIndRecord(ucDetachType, ucGmmCause, ucForceToStandby);
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬���в�ͬ�Ĵ���               */
    case GMM_REGISTERED_INITIATED:                                              /* GMM-REGISTERED-INITIATED                 */
        Gmm_RcvDetachRequestMsg_RegInit(ucDetachType, ucGmmCause);              /* ���ø�״̬�µ�detach����                 */
        break;
    case GMM_DEREGISTERED_INITIATED:                                            /* GMM-DEREGISTERED-INITIATED               */
        Gmm_RcvDetachRequestMsg_DeregInit(ucDetachType, ucGmmCause);                                    /* ���ø�״̬�µ�detach����                 */
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:                                   /* GMM-ROUTING-AREA-UPDATING-INITIATED      */
        Gmm_RcvDetachRequestMsg_RauInit(ucDetachType, ucGmmCause);              /* ���ø�״̬�µ�detach����                 */
        break;
    case GMM_SERVICE_REQUEST_INITIATED:                                         /* GMM-SERVICE-REQUEST-INITIATED            */
        Gmm_RcvDetachRequestMsg_ServReqInit(ucDetachType, ucGmmCause);          /* ���ø�״̬�µ�detach����                 */
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:                                         /* GMM-REGISTERED.NORMAL-SERVICE            */
    case GMM_REGISTERED_LIMITED_SERVICE:                                        /* GMM-REGISTERED.LIMITED-SERVICE           */
        Gmm_RcvDetachRequestMsg_RegNmlServ(ucDetachType, ucGmmCause);           /* ���ø�״̬�µ�detach����                 */
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:                                /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM   */
        Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm(ucDetachType, ucGmmCause);      /* ���ø�״̬�µ�detach����                 */
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:                                  /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */
        Gmm_RcvDetachRequestMsg_RegImsiDtchInit(ucDetachType, ucGmmCause);                              /* ���ø�״̬�µ�detach����                 */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        if ( ucDetachType == GMM_NET_DETACH_IMSI_DETACH )
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
        else/* detach PS */
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;/* default 44s */
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
            NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }

    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RegInit
  Function : ��GMM-REGISTERED-INITIATED״̬���յ�DETACH_REQUEST�Ĵ���
  Input    : VOS_UINT8     ucDetachType     detach����
             VOS_UINT8     ucGmmCause       detachԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
   1. ��־��  2003.12.08  �¹�����
   2.��    ��   : 2008��7��2��
     ��    ��   : l00107747
     �޸�����   : �������ⵥ�ţ�AT2D03900
   3.��    ��  : 2012��08��24��
     ��    ��  : m00217266
     �޸�����  : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
   4.��    ��   : 2015��6��5��
     ��    ��   : z00161729
     �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RegInit(
                                     VOS_UINT8      ucDetachType,                   /* detach����                               */
                                     VOS_UINT8      ucGmmCause                      /* detachԭ��                               */
                                     )
{
    /* 24008_CR2300R1_(Rel-11)_C1-124892 24008 4.7.3.1.5��������:
    If the MS receives a DETACH REQUEST message from the network in state
    GMM-REGISTERED-INITIATED with detach type of detach '"re-attach not required"
    and no cause code, or "re-attach not required"' and the cause code is not #2
    "IMSI unknown in HLR", the GPRS detach procedure shall be progressed and the
    GPRS attach procedure shall be aborted. Otherwise the GPRS attach procedure
    shall be progressed and the DETACH REQUEST message shall be ignored.*/
    if ((GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
     && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != ucGmmCause))
    {                                                                           /* detach������"re-attach not required"     */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        g_GmmReqCnfMng.ucCnfMask   = 0;                                         /* ����ȴ�CNF��־                          */
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH��������SM������                   */
            /* �ú��������ucGmmCause�ɺ���Gmm_RcvDetachRequestMsg���룬��ȡֵ��
             ��ΪNAS_MML_REG_FAIL_CAUSE_NULL����ֵ����GMM/SM���ԭ��ֵ�ڣ��ʴ˴�
             ��g_GmmGlobalCtrl.enGmmCause�����ֵ */

            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, NAS_GMM_GetAttach2DetachErrCode());    /* ֪ͨSM GMMע��ʧ��                       */

            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* ��ucSmCnfFlg��־                         */
        }
        Gmm_NetInitNotRequiredDetach(ucGmmCause);                               /* ����detach�Ĺ�������                     */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ���е�specific����               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachRequestMsg_RegInit:INFO: specific procedure ended");
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_DeregInit
  Function : ��GMM-DEREGISTERED-INITIATED״̬���յ�DETACH_REQUEST�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2. ��    ��   : 2007��12��12��
       ��    ��   : l00107747
       �޸�����   : �������ⵥ�ţ�A32D13861
    3. ��    ��   : 2010��10��16��
       ��    ��   : s46746
       �޸�����   : �������ⵥ�ţ�DTS2010100900274,���յ�����Detach�����û��ָʾSM����Detach״̬
    4. ��    ��   : 2011��07��13��
       ��    ��   : w00166186
       �޸�����   : V7R1 PHASE II ATTACH/DETACH����
    5. ��    ��   : 2012��06��04��
       ��    ��   : l65478
       �޸�����   : DTS2012060402840 MS�����DETACH������ĳ�ͻʱ,û�����ATTACH���б�־
    6.��    ��   : 2013��6��8��
      ��    ��   : w00167002
      �޸�����   : V9R1_SVLTE:�����߶�����:�����ǰ��CS���DETACH���򲻸��·�����.
    7.��    ��   : 2013��8��7��
      ��    ��   : w00167002
      �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
    8.��    ��   : 2013��08��16��
      ��    ��   : l65478
      �޸�����   : DTS2013092202614,G CCO��Wʧ�ܻ��˵�G,��G��֪ͨ��GAS������REDAY̬
    9.��    ��   : 2015��6��5��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_DeregInit(
    VOS_UINT8                           ucDetachType,           /* detach����                               */
    VOS_UINT8                           ucGmmCause              /* detachԭ��                               */
)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* ����ָ��                                 */

    /* 24008_CR2062R2_(Rel-11)_C1-121261 24008 4.7.4.1.4�½���������:
    GPRS detach containing other causes than "power off":
    If the DETACH REQUEST message received by the MS contains detach type "IMSI detach",
    and the MS initiated detach procedure is with detach type "GPRS detach" or
    "combined GPRS/IMSI detach", the MS shall progress both procedures.
    The MS in operation mode A or B in network operation mode I need not re-attach to non-GPRS services.*/
    if ((GMM_NET_DETACH_IMSI_DETACH == ucDetachType)
     && ((GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType)
      || (GMM_WAIT_CS_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType))
      && (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState))
    {
        Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_IMSI, NAS_MML_REG_FAIL_CAUSE_NULL);  /* ����MMCGMM_NETWORK_DETACH_IND            */
        NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_IMSI,
                                      NAS_MML_REG_FAIL_CAUSE_NULL);

        pDetachAccept = Gmm_DetachAcceptMsgMake();
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);
        return;
    }

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* ���ú�������detach accept��Ϣ            */

    Gmm_TimerStop(GMM_TIMER_T3321);
    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* ����RRMM_DATA_REQ(detach accept��Ϣ)     */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_USER);

        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
    }
    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }


    Gmm_SndMmcNetworkDetachInd(ucDetachType, ucGmmCause);  /* ����MMCGMM_NETWORK_DETACH_IND            */

    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RauInit
  Function : GMM-RAU-INITIATED״̬���յ�DETACH_REQUEST�Ĵ���
  Input    : VOS_UINT8     ucDetachType     detach����
             VOS_UINT8     ucGmmCause       detachԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2.��    ��   : 2015��6��4��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RauInit(
                                     VOS_UINT8      ucDetachType,               /* detach����                               */
                                     VOS_UINT8      ucGmmCause                  /* detachԭ��                               */
                                     )
{
    /* 24008_CR1598R2_(Rel-9)_C1-103557 24008 4.7.4.2.4��������:
    If the network receives a ROUTING AREA UPDATE REQUEST message before the network initiated
    GPRS detach procedure has been completed, the detach procedure shall be progressed,
    i.e. the ROUTING AREA UPDATE REQUEST message shall be ignored. If the DETACH REQUEST
    message contains detach type "re-attach not required" and GMM cause  #2 "IMSI unknown in HLR",
    the network will follow the procedure as described below for the detach type "IMSI detach".
    GPRS detach containing detach type "IMSI detach":
     If the network receives a ROUTING AREA UPDATE REQUEST message before the network
     initiated GPRS detach procedure has been completed, the network shall abort the detach procedure,
     shall stop T3322 and shall progress the routing area update procedure.*/
    if (GMM_NET_DETACH_IMSI_DETACH == ucDetachType)
    {
        return;
    }

    if ((GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
     && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR == ucGmmCause))
    {
        return;
    }                                                                          /* detach����Ϊ"re-attach not required"
                                                                             * ��"re-attach required                    */
    Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */

    Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

    Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */

    Gmm_ComCnfHandle();
    g_GmmReqCnfMng.ucCnfMask   = 0;                                         /* ����ȴ�CNF��־                          */
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ���е�specific����               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachRequestMsg_RauInit:INFO: specific procedure ended");

    if (GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
    {                                                                       /* detach����Ϊ"re-attach not required"     */
        Gmm_NetInitNotRequiredDetach(ucGmmCause);                           /* ����"re-attach not required"�Ĺ�������   */
    }
    else
    {                                                                       /* detach����Ϊ"re-attach required"         */
        Gmm_NetInitRequiredDetach();                                        /* ����re-attach required�Ĵ���             */
    }


    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_ServReqInit
  Function : ��GMM-SERVICE-REQUEST-INITIATED״̬���յ�DETACH_REQUEST�Ĵ���
  Input    : VOS_UINT8     ucDetachType     detach����
             VOS_UINT8     ucGmmCause       detachԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2.��    ��   : 2015��6��4��
      ��    ��   : z00161729
      �޸�����   : 24008 23122  R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_ServReqInit(
                                         VOS_UINT8      ucDetachType,           /* detach����                               */
                                         VOS_UINT8      ucGmmCause              /* detachԭ��                               */
                                         )
{
    /* 24008_CR1598R2_(Rel-9)_C1-103557 24008 4.7.4.2.4��������:
    If the GPRS Detach Request message contains detach type "re-attach not required"
    and GMM cause  #2 "IMSI unknown in HLR", the network will follow the procedure as
    described below for the detach type "IMSI detach".
    GPRS detach containing detach type "IMSI detach":
    If the network receives a SERVICE REQUEST message before the network initiated
    GPRS detach procedure has been completed, the network shall progress both
    procedures.*/
    if ((GMM_NET_DETACH_REATTACH_NOT_REQUIRED == ucDetachType)
     && (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR == ucGmmCause))
    {
        ucDetachType = GMM_NET_DETACH_IMSI_DETACH;
    }

    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ͣT3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
    Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* ͣ����Timer                              */

    g_GmmReqCnfMng.ucCnfMask = 0;                                               /* ����ȴ�CNF��־                          */
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �����ǰ���е�specific����               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachRequestMsg_ServReqInit:INFO: specific procedure ended");

    switch (ucDetachType)
    {                                                                           /* �ж�detach���ͽ��в�ͬ����               */
    case GMM_NET_DETACH_REATTACH_NOT_REQUIRED:                                  /* "re-attach not required"                 */
        Gmm_ComCnfHandle();

        Gmm_NetInitNotRequiredDetach(ucGmmCause);                               /* ����"re-attach not required"�Ĺ�������   */
        break;
    case GMM_NET_DETACH_REATTACH_REQUIRED:                                      /* "re-attach required"                     */
        Gmm_ComCnfHandle();

        Gmm_NetInitRequiredDetach();                                            /* ����re-attach required�Ĵ���             */
        break;

    case GMM_NET_DETACH_IMSI_DETACH:                                            /* IMSI detach                              */
        /* Gmm_ComCnfHandle���������sm���棬imsi detach������������rau������sm
           ����rau��follow on rau�ɹ���ɴ����淢��smҵ������ */
        Gmm_NetInitImsiDetach();                                                /* ??IMSI detach???                    */
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg_ServReqInit:WARNING: Detach Type is Abnormal");
        break;
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RegNmlServ
  Function : ��GMM-REGISTERED.NORMAL-SERVICE״̬���յ�DETACH_REQUEST�Ĵ���
  Input    : VOS_UINT8     ucDetachType     detach����
             VOS_UINT8     ucGmmCause       detachԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RegNmlServ(
                                        VOS_UINT8      ucDetachType,                /* detach����                               */
                                        VOS_UINT8      ucGmmCause                   /* detachԭ��                               */
                                        )
{
    switch (ucDetachType)
    {                                                                           /* �ж�detach���ͽ��в�ͬ����               */
    case GMM_NET_DETACH_REATTACH_NOT_REQUIRED:                                  /* "re-attach not required"                 */
        Gmm_NetInitNotRequiredDetach(ucGmmCause);                               /* ����"re-attach not required"�Ĺ�������   */
        break;
    case GMM_NET_DETACH_REATTACH_REQUIRED:                                      /* "re-attach required"                     */
        Gmm_NetInitRequiredDetach();                                            /* ����re-attach required�Ĵ���             */
        break;
    case GMM_NET_DETACH_IMSI_DETACH:                                            /* IMSI detach                              */
        Gmm_NetInitImsiDetach();                                                /* ����IMSI detach�Ĵ���                    */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachRequestMsg_RegNmlServ:WARNING: Detach Type is Abnormal");
        break;
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm
  Function : ��REGISTERED.ATTEMPTING-TO-UPDATE-MM״̬���յ�DETACH_REQUEST�Ĵ���
  Input    : VOS_UINT8     ucDetachType     detach����
             VOS_UINT8     ucGmmCause       detachԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm(
                                             VOS_UINT8      ucDetachType,           /* detach����                               */
                                             VOS_UINT8      ucGmmCause              /* detachԭ��                               */
                                             )
{
    Gmm_RcvDetachRequestMsg_RegNmlServ(ucDetachType, ucGmmCause);
}

/*******************************************************************************
  Module   : Gmm_RcvDetachRequestMsg_RegImsiDtchInit
  Function : ��REGISTERED.IMSI-DETACH-INITIATED״̬���յ�DETACH_REQUEST�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2.��    ��   : 2013��6��8��
      ��    ��   : w00167002
      �޸�����   : V9R1_SVLTE:�����߶�����:
                   ԭ�ȵ��ú���Gmm_RcvDetachRequestMsg_DeregInit(ucDetachType, ucGmmCause);
                   �����ǰ��CS���DETACH��ȴ����PS��׼��ע��.
*******************************************************************************/
VOS_VOID Gmm_RcvDetachRequestMsg_RegImsiDtchInit(
    VOS_UINT8                           ucDetachType,           /* detach����                               */
    VOS_UINT8                           ucGmmCause              /* detachԭ��                               */
)
{



    NAS_MSG_STRU    *pDetachAccept;                                             /* ����ָ��                                 */

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* ���ú�������detach accept��Ϣ            */

    Gmm_TimerStop(GMM_TIMER_T3321);

    switch (ucDetachType)
    {                                                                           /* �ж�detach���ͽ��в�ͬ����               */
        case GMM_NET_DETACH_REATTACH_NOT_REQUIRED:                              /* "re-attach not required"                 */
            Gmm_NetInitNotRequiredDetach(ucGmmCause);                           /* ����"re-attach not required"�Ĺ�������   */
            break;

        case GMM_NET_DETACH_REATTACH_REQUIRED:                                  /* "re-attach required"                     */

            /* ����CS��׼���־���������ᷢ������ATTACH */
            if (GMM_WAIT_CS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH))
            {
                NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            }

            Gmm_NetInitRequiredDetach();                                        /* ����re-attach required�Ĵ���             */
            break;

        case GMM_NET_DETACH_IMSI_DETACH:                                        /* IMSI detach                              */
            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);        /* ����RRMM_DATA_REQ(detach accept��Ϣ)     */
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndMmcNetworkDetachInd(ucDetachType, ucGmmCause);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvDetachRequestMsg_RegImsiDtchInit: INVALID DETACH TYPE!");
            break;
    }
    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }


    return;
}

/*******************************************************************************
  Module   : Gmm_NetInitNotRequiredDetach
  Function : ���෢�������Ϊreattach not required��detach�Ĵ���
  Input    : VOS_UINT8  ucGmmCause        detach��ԭ��ֵ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����
    2. ��    ��   : 2009��06��22��
       ��    ��   : l00130025
       �޸�����   : ���ⵥ��:AT2D12541,��IOT���ԡ������·�Detach(����Ϊ Re-attach not required)��UE�����·���attach����
    3. ��    ��   : 2009��09��07��
       ��    ��   : l65478
       �޸�����   : ���ⵥ��:AT2D13980,����detach�󣬻����PDP�����޷����������
    4.��    ��   : 2012��9��25��
      ��    ��   : h00216089
      �޸�����   : DTS2012090304976:����������Detach(re-attach not required)��MM��ʱ����ʱ����LU��
                   LU�������յ�ϵͳ��ϢGMM�����ٷ���Attach
    5.��    ��   : 2015��6��3��
      ��    ��   : z00161729
      �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
*******************************************************************************/
VOS_VOID Gmm_NetInitNotRequiredDetach(
                                  VOS_UINT8         ucGmmCause                      /* detach��ԭ��ֵ                           */
                                  )
{
    switch (ucGmmCause)
    {                                                                           /* ����ԭ��ֵ��ͬ���в�ͬ����               */
    case NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR:                                      /* ԭ��ֵ2                                  */
        Gmm_Com_Cause2Detach();
        break;
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_MS:                                               /* ԭ��ֵ3                                  */
    case NAS_MML_REG_FAIL_CAUSE_ILLEGAL_ME:                                               /* ԭ��ֵ6                                  */
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW:                    /* ԭ��ֵ8                                  */
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask  &= ~GMM_UEID_IMSI;              /* ���IMSI����MASK                         */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);/* Update status����ΪGU2                   */
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW:                                      /* ԭ��ֵ7                                  */
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask  &= ~GMM_UEID_IMSI;              /* ���IMSI����MASK                         */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);  /* Update status����ΪGU2                  */
        break;
    case NAS_MML_REG_FAIL_CAUSE_PLMN_NOT_ALLOW:                                           /* ԭ��ֵ11                                 */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN;               /* ���ý�ֹע���б��־                     */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status����ΪGU3                   */

        /* 24008_CR1229R1_(Rel-8)_C1-085365 24008 4.7.4.2.2�½���������:#11 The MS shall delete any RAI or LAI,
        P-TMSI, P-TMSI signature and GPRS ciphering key sequence number, shall set
        the GPRS update status to GU3 ROAMING NOT ALLOWED (and shall store it according to subclause 4.1.3.2)
        and shall reset the GPRS attach attempt counter. The new GMM state is GMM-DEREGISTERED.*/
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
        break;
    case NAS_MML_REG_FAIL_CAUSE_LA_NOT_ALLOW:                                             /* ԭ��ֵ12                                 */
        g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_TRUE;
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status����ΪGU3                   */
        g_GmmAttachCtrl.ucAttachAttmptCnt  = 0;                                 /* ATTACH ATTEMPT COUNTER RESET             */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |=
                                        GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS;      /* ���ý�ֹע���б��־                     */
        break;
    case NAS_MML_REG_FAIL_CAUSE_ROAM_NOT_ALLOW:                                           /* ԭ��ֵ13                                 */
    case NAS_MML_REG_FAIL_CAUSE_NO_SUITABL_CELL:                                          /* ԭ��ֵ15                                 */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status����ΪGU3                   */
        g_GmmAttachCtrl.ucAttachAttmptCnt  = 0;                                 /* ATTACH ATTEMPT COUNTER RESET             */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_LA_FOR_ROAM;        /* ���ý�ֹע���б��־                     */
        break;
    case NAS_MML_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN:                              /* ԭ��ֵ14                                 */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED);  /* Update status����ΪGU3                   */
        g_GmmGlobalCtrl.SysInfo.ucForbMask |= GMM_FORBIDDEN_PLMN_FOR_GPRS;      /* ���ý�ֹע���б��־                     */

        /* 24008_CR1229R1_(Rel-8)_C1-085365 24008 4.7.4.2.2�½���������:#14 The MS shall delete any RAI or LAI,
        P-TMSI, P-TMSI signature and GPRS ciphering key sequence number, shall set
        the GPRS update status to GU3 ROAMING NOT ALLOWED (and shall store it according to subclause 4.1.3.2)
        and shall reset the GPRS attach attempt counter. The new GMM state is GMM-DEREGISTERED.*/
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_NetInitNotRequiredDetach:WARNING: GMM Cause is Abnormal");
        ucGmmCause = NAS_MML_REG_FAIL_CAUSE_NULL;                                         /* ��ԭ��ֵ��Ϊ��                           */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.ucRcvNetDetachFlg = VOS_TRUE;
        if (VOS_FALSE == NAS_MML_GetPsAutoAttachFlg())
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
        break;
    }

    if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != ucGmmCause)
    {                                                                           /* ԭ��ֵ������2                            */
        Gmm_Com_CauseDetach(ucGmmCause);                                        /* ����ԭ��ֵ��Ч�Ҳ���2�Ĺ�������          */
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
    }

    return;                                                                     /* ����                                     */
}


/*******************************************************************************
  Module   : Gmm_Com_Cause2Detach
  Function : Reattch not required + #2�Ĵ���
  Input    : VOS_VOID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.08  �¹�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
 3 .��    ��   : 2013��08��16��
    ��    ��   : l65478
    �޸�����   : DTS2013092202614,G CCO��Wʧ�ܻ��˵�G,��G��֪ͨ��GAS������REDAY̬
*******************************************************************************/
VOS_VOID Gmm_Com_Cause2Detach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* ������Ϣָ��                             */

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* ���ú�������detach accept��Ϣ            */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* ����RRMM_DATA_REQ(detach accept��Ϣ)     */
    Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_NOATTACH,
                               NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);               /* ����MMCGMM_NETWORK_DETACH_IND            */
    NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_NOATTACH,
                                  NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR);
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ��ǰ״̬ΪREGISTERED_INITIATED           */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ���½���ATTACH                           */                                                  /* ���½���attach                           */
    }
    else if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ��ǰ״̬ΪRAU_INITIATED                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ���½���RAU                              */
    }
    else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* ����״̬�Ĺ�������                       */
        if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* T3302��������                            */
            Gmm_TimerPause(GMM_TIMER_T3302);                                    /* ����T3302                                */
        }
        else if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* T3311��������                            */
            Gmm_TimerPause(GMM_TIMER_T3311);                                    /* ����T3311                                */
        }
        else
        {
        }
    }
    else
    {
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_Com_CauseDetach
  Function : Reattch not required + ��#2�Ĵ���
  Input    : VOS_UINT8  ucGmmCause        detach��ԭ��ֵ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �¹�����
  2.��    ��   : 2007��01��04��
    ��    ��   : s46746
    �޸�����   : �������������ⵥ�ţ�A32D08235
  3.��    ��   : 2009��09��07��
    ��    ��   : l65478
    �޸�����   : �������ⵥ�ţ�AT2D13980,����detach������attachʧ�ܣ���Ϊtlliû��ȥָ��
  4.��    ��   : 2010��01��03��
    ��    ��   : o00132663
    �޸�����   : ���ⵥ�ţ�xxxx,NAS R7Э��������������PS���������ͷŶ�ʱ��T3340
  5.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  6.��    ��   : 2013��08��16��
    ��    ��   : l65478
    �޸�����   : DTS2013092202614,G CCO��Wʧ�ܻ��˵�G,��G��֪ͨ��GAS������REDAY̬
*******************************************************************************/
VOS_VOID Gmm_Com_CauseDetach(
                         VOS_UINT8  ucGmmCause                                      /* detach��ԭ��ֵ                           */
                         )
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* ������Ϣָ��                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* ��ʼ����Ϣָ��                           */

    Gmm_TimerStop(GMM_TIMER_ALL);                                               /* ֹͣ���е�GMM TIMER                      */

    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* ���ú�������detach accept��Ϣ            */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* ����RRMM_DATA_REQ(detach accept��Ϣ)     */
    Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_NOATTACH, ucGmmCause);         /* ����MMCGMM_NETWORK_DETACH_IND            */
    NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_NOATTACH, ucGmmCause);
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (NAS_MML_REG_FAIL_CAUSE_NULL != ucGmmCause)
    {                                                                           /* ԭ��ֵ��Ч                               */
        Gmm_DelPsLocInfoUpdateUsim();
    }

    NAS_GMM_CheckCauseToStartT3340(ucGmmCause);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        if(GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_USER);
        }
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_NetInitRequiredDetach
  Function : ��������������Ϊreattach required��detach���̴���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �¹�����
  2.��    ��    : 2009��9��03��
    ��    ��    : l65478
    �޸�����    : created AT2D14239,detach��ɺ�,�ٴη���ATTATCH REQʱ,GASʹ�þɵ�TLLI������TBF��������,û�м�ʱʹ���µ�TLLI,����MS��������ά����TLLI��һ��,�Ӷ�����GAS��ΪTLLI��ƥ�䶪���˽�������TBF��ָ������,���յ�������ʧ��
  3.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  4.��    ��   : 2013��08��16��
    ��    ��   : l65478
    �޸�����   : DTS2013092202614,G CCO��Wʧ�ܻ��˵�G,��G��֪ͨ��GAS������REDAY̬
*******************************************************************************/
VOS_VOID Gmm_NetInitRequiredDetach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* ������Ϣָ��                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* ��ʼ����Ϣָ��                           */

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* ����״̬�Ĺ�������                       */
    Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_REATTACH, NAS_MML_REG_FAIL_CAUSE_NULL);  /* ֪ͨMMC GMM���е�detach                  */
    NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_REATTACH,
                                  NAS_MML_REG_FAIL_CAUSE_NULL);
    pDetachAccept = Gmm_DetachAcceptMsgMake();                                  /* ���ú�������detach accept��Ϣ            */

    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);                /* ����RRMM_DATA_REQ(detach accept��Ϣ)     */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);
    Gmm_HoldBufferFree();                                                       /* ���������Ϣ                             */
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_USER);

        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
    }

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
        if(GMM_TRUE == GMM_IsCasGsmMode())
        {
            g_GmmGlobalCtrl.ulGmmAttachFlg = GMM_TRUE;
        }
        else
        {
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_NetInitImsiDetach
  Function : ��������������ΪIMSI detach��detach���̴���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��  2003.12.09  �¹�����
  2.��    ��   : 2007��01��04��
    ��    ��   : s46746
    �޸�����   : �������������ⵥ�ţ�A32D08235
  3.��    ��   : 2009��05��23��
    ��    ��   : L65478
    �޸�����   : ���ⵥ��:AT2D06770,RAUʧ�ܣ���ΪGRM������ԭ����DATA��ʵ��Ӧ��������
  4.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  5.��     ��  : 2011��9��26��
    ��    ��   : c00173809
    �޸�����   : DTS2011092001088,GCF 44.2.2.2.4����ʧ��
  6.��    ��   : 2013��2��4��
    ��    ��   : w00176964
    �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
*******************************************************************************/
VOS_VOID Gmm_NetInitImsiDetach(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* ������Ϣָ��                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* ��ʼ����Ϣָ��                           */

    if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
    {                                                                           /* CS��ע��                                 */
        Gmm_SndMmcNetworkDetachInd(NAS_MMC_GMM_NT_DETACH_IMSI, NAS_MML_REG_FAIL_CAUSE_NULL);  /* ����MMCGMM_NETWORK_DETACH_IND            */
        NAS_GMM_SndMmNetworkDetachInd(GMMMM_NET_DETACH_IMSI,
                                      NAS_MML_REG_FAIL_CAUSE_NULL);
        pDetachAccept = Gmm_DetachAcceptMsgMake();                              /* ���ú�������detach accept��Ϣ            */

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pDetachAccept);            /* ����RRMM_DATA_REQ(detach accept��Ϣ)     */

        g_GmmGlobalCtrl.ucDetachAcceptedFlg = VOS_TRUE;

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH); /* ����RAU����combined RAU with IMSI attach */
        }
        else if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
              && (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_ATTACH_NORMAL;
        }
        else
        {
        }

        g_GmmGlobalCtrl.ucDetachAcceptedFlg = VOS_FALSE;
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_DetachAcceptMsgMake
  Function : Detach accept��Ϣ����
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : NAS_MSG_STRU *
  History  :
    1. ��־��  2003.12.09  �¹�����
*******************************************************************************/
NAS_MSG_STRU* Gmm_DetachAcceptMsgMake(VOS_VOID)
{
    NAS_MSG_STRU    *pDetachAccept;                                             /* ������Ϣָ��                             */

    pDetachAccept = VOS_NULL_PTR;                                                       /* ��ʼ����Ϣָ��                           */

    pDetachAccept = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));        /* �����ڴ�ռ�                             */
    if (VOS_NULL_PTR == pDetachAccept)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_DetachAcceptMsgMake:error: Alloc mem fail.");
        return pDetachAccept;
    }
    Gmm_MemSet(pDetachAccept, 0, sizeof(NAS_MSG_STRU));                         /* ��������ڴ�ռ���0                      */

    pDetachAccept->ulNasMsgSize = GMM_MSG_LEN_DETACH_ACCEPT;                    /* ��Ϣ����                                 */
    pDetachAccept->aucNasMsg[0] = GMM_PD_GMM;                                   /* PD                                       */
    pDetachAccept->aucNasMsg[1] = GMM_MSG_DETACH_ACCEPT;                        /* message type                             */

    return pDetachAccept;                                                       /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachAcceptMsg
  Function : GMM�յ�DETACH_ACCEPT�ķַ�����
  Input    : NAS_MSG_STRU   *pMsg  ��ǰ�������Ϣ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.09  �¹�����
  2. x51137 2006/4/28 A32D02889
  3.��    ��   : 2006��11��9��
    ��    ��   : sunxibo id:46746
    �޸�����   : �������ⵥ�ţ�A32D06822
  4.��    ��   : 2009��05��23��
    ��    ��   : L65478
    �޸�����   : ���ⵥ��:AT2D06770,RAUʧ�ܣ���ΪGRM������ԭ����DATA��ʵ��Ӧ��������
  5.��    ��   : 2010��10��29��
    ��    ��   : l00167671/�޿���
    �޸�����   : ���ⵥ�ţ�DTS2010100802035,���Wģʱ��LLC������
  6.��    ��   : 2010��11��24��
    ��    ��   : ��ë 00166186
    �޸�����   : �������ⵥ��DTS2010112205253,DEFAULT��֧������ԭ��ֵ��д����ȷ
  7.��    ��   : 2010��12��03��
    ��    ��   : w00166186
    �޸�����   : DTS2010112403161 ��������������
  8.��    ��   : 2012��3��3��
    ��    ��   : z00161729
    �޸�����   : V7R1 C50 ֧��ISR�޸�,T3312����ֹͣ��ʱ����֪ͨL
  9.��    ��   : 2012��8��25��
    ��    ��   : m00217266
    �޸�����   : ɾ��GMM_SaveErrCode�����Gmm_Save_Detach_Cause��
                ���浼��Attachʧ�ܵ�ԭ��ֵ
  *******************************************************************************/
VOS_VOID Gmm_RcvDetachAcceptMsg(
                            NAS_MSG_FOR_PCLINT_STRU        *pMsg
                            )
{
    NAS_MSG_STRU                       *pGmmStatus;
    VOS_UINT8                           ucForceToStandby;
    VOS_UINT8                           ucDetachType=0x0;

#if (FEATURE_LTE == FEATURE_ON)
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    if (GMM_MSG_LEN_DETACH_ACCEPT > pMsg->ulNasMsgSize)
    {                                                                           /* ��Ϣ�б�ѡ��ĳ��Ȳ�����                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg:WARNING: Length of DETACH ACCEPT is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;                                                                 /* ����                                     */
    }

    ucForceToStandby = (VOS_UINT8)(pMsg->aucNasMsg[2] & 0x0F);
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
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg:WARNING: DETACH ACCEPT is semantically incorrect");
        /*pGmmStatus = Gmm_GmmStatusMsgMake(*/
        /*    NAS_MML_REG_FAIL_CAUSE_SEMANTICALLY_INCORRECT_MSG);*/

        /*Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);*/
        /*return;*/
        gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬���в�ͬ����                 */
    case GMM_DEREGISTERED_INITIATED:                                            /* GMM-DEREGISTERED-INITIATED               */
        Gmm_RcvDetachAcceptMsg_DeregInit();                                     /* ���ø�״̬�µĴ���                       */
        ucDetachType = GMM_NET_DETACH_REATTACH_NOT_REQUIRED;
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:                                  /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */
        Gmm_RcvDetachAcceptMsg_RegImsiDtchInit();                               /* ���ø�״̬�µĴ���                       */
        ucDetachType = GMM_NET_DETACH_IMSI_DETACH;
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg:WARNING: DETACH ACCEPT is unexpected");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_MSG_NOT_COMPATIBLE);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        break;
    }

    if (ucDetachType != GMM_NET_DETACH_IMSI_DETACH)
    {
        NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_PS_DETACH);
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {

        if ( ucDetachType == GMM_NET_DETACH_IMSI_DETACH )
        {
            if ( GMM_TRUE == gstGmmCasGlobalCtrl.ucFtsFlg )
            {
                gstGmmCasGlobalCtrl.ucFtsFlg = GMM_FALSE;

                if ( 0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue )
                {
                     gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                     Gmm_TimerStop(GMM_TIMER_T3314);
                     Gmm_TimerStart(GMM_TIMER_T3312);
                     NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                }
            }
        }
        else/* detach PS */
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);                                                 /* ȥָ��TLLI���ͷ�LLC������ */
            Gmm_TimerStop(GMM_TIMER_T3314);
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
            gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;/* default 44s */

#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }

            /* detach ps�����ISR�����Ҫȥ����ISR */
            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
            {
                NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
                Gmm_TimerStop(GMM_TIMER_T3323);

                /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
                NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
            NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }

    }
    else
    {
        if (GMM_NET_DETACH_IMSI_DETACH != ucDetachType)
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }

            /* detach ps�����ISR�����Ҫȥ����ISR */
            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
            {
                NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
                Gmm_TimerStop(GMM_TIMER_T3323);

                /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
                NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
        }
    }

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachAcceptMsg_DeregInit
  Function : ��GMM-REGISTERED.IMSI-DETACH-INITIATED���յ�DETACH_ACCEPT�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.09  �¹�����
  2. ��    ��   : 2006��11��20��
     ��    ��   : s46746
     �޸�����   : �������������ⵥ�ţ�A32D07433
  3. ��    ��   : 2011��07��13��
     ��    ��   : w00166186
     �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  4.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  5. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��GMM��Ҫ��������֧����Ϣ֪ͨ��MMC.

  6.��    ��   : 2013��8��7��
    ��    ��   : w00167002
    �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
*******************************************************************************/
VOS_VOID Gmm_RcvDetachAcceptMsg_DeregInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );             /* ��PS���attach��ֹ��־                   */
    }
    /*Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);*/                             /* ����״̬�Ĺ�������                       */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* ���P_TMSI_SIGNATURE                     */
        NAS_MML_InitUeIdPtmsiSignatureInvalid();
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }

        else
        {
            /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
            NAS_GMM_SndMmGprsDetachComplete();
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    }
    else if (VOS_OK != Mm_StartRelTimer(&g_stGmmProtectRrRelTimer,
                                            WUEPS_PID_GMM,
                                            GMM_TIMER_PROTECT_FOR_RR_REL_VALUE,
                                            GMM_TIMER_PROTECT_FOR_RR_REL,
                                            0,
                                            VOS_RELTIMER_NOLOOP))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
            NAS_GMM_SndMmGprsDetachComplete();
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvDetachAcceptMsg_DeregInit:WARNING: Gmm Start Timer fail.");
    }
    else
    {
        g_GmmTimerMng.ulTimerRunMask |= (0x00000001 << GMM_TIMER_PROTECT_FOR_RR_REL);
    }

    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachAcceptMsg_DeregInit:INFO: specific procedure ended");
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvDetachAcceptMsg_RegImsiDtchInit
  Function : ��GMM-DEREGISTERED-INITIATED״̬���յ�DETACH_ACCEPT�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��  2003.12.09  �¹�����
  2. ��    ��   : 2011��07��13��
     ��    ��   : w00166186
     �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  3.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
*******************************************************************************/
VOS_VOID Gmm_RcvDetachAcceptMsg_RegImsiDtchInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* ����״̬�Ĺ�������                       */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* ���P_TMSI_SIGNATURE                     */
        NAS_MML_InitUeIdPtmsiSignatureInvalid();
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }
    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    g_GmmGlobalCtrl.ucSpecProc               = GMM_NULL_PROCEDURE;              /* �����ǰ���е�specific����               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvDetachAcceptMsg_RegImsiDtchInit:INFO: specific procedure ended");
    return;                                                                     /* ����                                     */
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_SetAttach2DetachErrCode
 ��������  : ���浼��GMM��Attach״̬�л���Detach״̬��ԭ��
 �������  : GMM_SM_CAUSE_ENUM_UINT16
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��15��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_ENUM_UINT16 enCause)
{
    g_GmmGlobalCtrl.enAttach2DetachCause = enCause;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_GetAttach2DetachErrCode
 ��������  : ��ȡ����GMM��Attach״̬�л���Detach״̬��ԭ��
 �������  : ��
 �������  : GMM_SM_CAUSE_ENUM_UINT16
 �� �� ֵ  : GMM_SM_CAUSE_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��15��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
GMM_SM_CAUSE_ENUM_UINT16 NAS_GMM_GetAttach2DetachErrCode(VOS_VOID)
{
    return g_GmmGlobalCtrl.enAttach2DetachCause;
}



/*****************************************************************************
 �� �� ��  : NAS_GMM_ChangeDetachCauseAvoidInvalidSim
 ��������  : ����Detach�ܾ�ԭ��ֵ����Ӧ
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
VOS_VOID NAS_GMM_ChangeDetachCauseAvoidInvalidSim(VOS_UINT8 *pucRcvMsg)
{
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId    = VOS_NULL_PTR;
    VOS_UINT32                          bIsRegisteredInHplmn = VOS_FALSE;

    /* ���Ӳ��Կ����������Կ�ʱ���޸ģ�ֱ�ӷ��� */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_ChangeDetachCauseAvoidInvalidSim: The sim is Test card");
        return;
    }

    /* ȡ�õ�ǰפ����PLMN ID */
    pstCurrCampPlmnId    = NAS_MML_GetCurrCampPlmnId();
    bIsRegisteredInHplmn = NAS_MML_ComparePlmnIdWithHplmn(pstCurrCampPlmnId);

    NAS_MML_SetOriginalRejectCause(*pucRcvMsg);
    if (VOS_TRUE == bIsRegisteredInHplmn)
    {
        /* HPLMN */
        NAS_GMM_HandleHplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_DETACH, pucRcvMsg);
    }
    else
    {
        /* VPLMN */
        NAS_GMM_HandleVplmnRejCauseChange(NAS_MML_CHANGE_REJ_TYPE_DETACH, pucRcvMsg);
    }
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

