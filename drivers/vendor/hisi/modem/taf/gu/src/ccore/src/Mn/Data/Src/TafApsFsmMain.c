/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsFsmMain.c
  �� �� ��   : ����
  ��    ��   : h44270
  ��������   : 2011��12��16��
  ����޸�   :
  ��������   : ��״̬��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��12��16��
    ��    ��   : h44270
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "MmcApsInterface.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "TafApsFsmMain.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsFsmMsActivatingTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsFsmNwActivatingTbl.h"
#include "TafApsFsmMsDeactivating.h"
#include "TafApsProcIpFilter.h"
#include "TafApsSndAt.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsSndRabm.h"
#include "TafApsSndSm.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "MnApsMultiMode.h"
#include "ApsL4aInterface.h"
#include "TafApsSndL4a.h"
#endif
#include "ApsNdInterface.h"
#include "TafApsSndNd.h"
#include "TafApsComFunc.h"

#include "TafApsFsmCdataEstingTbl.h"
#include "TafApsFsmCdataDiscingTbl.h"
#include "TafMmaInterface.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "xcc_aps_pif.h"
#include "hsm_aps_pif.h"
#include "TafApsFsmCdataHandOff.h"
#endif
#include "TafApsSndCds.h"
#include "TafApsSndPpp.h"
#include "taf_aps_ppp_pif.h"
#include "TafApsSndXcc.h"
#include "TafApsFsmCdataHandOffTbl.h"
#include "TafApsSndNd.h"
#include "TafApsSndEhsm.h"
#include "TafApsSndDhcp.h"
#include "cnas_cttf_hrpd_pa_pif.h"

#include "TafApsProcEpdszid.h"
#include "TafSdcLib.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MAIN_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_Inactive
 ��������  : �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
              VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg            = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* PDP����������� */
    if (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        /*-------------------------------------------------------
           ����TAF_APS_STA_MS_ACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_ACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_ACTIVATING_SUBSTA_INIT��״̬�д���
           ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
        -------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_ACTIVATING,
                           TAF_APS_GetMsActivatingFsmDescAddr(),
                           TAF_APS_MS_ACTIVATING_SUBSTA_INIT);
    }
    else
    {
        /* ָ��ȥ�����CID����δ����״̬, ��Ԥ�������Ѿ�����, ���ﲻ�ٴ��� */
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvAtSetPdpContextStateReq_Inactive: Wrong operation");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsPppDialOrigReq_Inactive
 ��������  : INACTIVE��״̬���յ�ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /*-------------------------------------------------------
       ƽ̨����֧��CDMA���ҵ�ǰפ��ģʽ���Ϊ3GPP2��NULL,
       ��ѡ��3GPP2���̣�����ѡ��3GPP����

       NULL״̬���յ�MMA�ϱ��ķ���״̬��Ϣ��
       ���ΪLTEģʽ���˳�TAF_APS_FSM_CDATA_ESTING״̬����
       ���¼���TAF_APS_STA_MS_ACTIVATING״̬��

       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/

    if (VOS_TRUE == TAF_APS_IsEnterCdataEsting())
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                           TAF_APS_GetCdataEstingFsmDescAddr(),
                           TAF_APS_CDATA_ESTING_SUBSTA_INIT);
    }
    else
#endif
        /*-------------------------------------------------------
           ����TAF_APS_STA_MS_ACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_ACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_ACTIVATING_SUBSTA_INIT��״̬�д���
           ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ
        -------------------------------------------------------*/
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_ACTIVATING,
                           TAF_APS_GetMsActivatingFsmDescAddr(),
                           TAF_APS_MS_ACTIVATING_SUBSTA_INIT);
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_Inactive
 ��������  : INACTIVE��״̬���յ�ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /*-------------------------------------------------------
       ƽ̨����֧��CDMA���ҵ�ǰפ��ģʽ���Ϊ3GPP2��NULL,
       ��ѡ��3GPP2���̣�����ѡ��3GPP����

       NULL״̬���յ�MMA�ϱ��ķ���״̬��Ϣ��
       ���ΪLTEģʽ���˳�TAF_APS_FSM_CDATA_ESTING״̬����
       ���¼���TAF_APS_STA_MS_ACTIVATING״̬��

       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/

    if (VOS_TRUE == TAF_APS_IsEnterCdataEsting())
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                           TAF_APS_GetCdataEstingFsmDescAddr(),
                           TAF_APS_CDATA_ESTING_SUBSTA_INIT);
    }
    else
#endif
    /*-------------------------------------------------------
       ����TAF_APS_STA_MS_ACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_ACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_ACTIVATING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_ACTIVATING,
                           TAF_APS_GetMsActivatingFsmDescAddr(),
                           TAF_APS_MS_ACTIVATING_SUBSTA_INIT);
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpActivateInd_Inactive
 ��������  : INACTIVE��״̬���յ�D_PMC_SMREG_PDP_ACT_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpActivateInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* ��ȡ��ǰ����ģʽ*/
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* ��鵱ǰģ�Ƿ�ΪGU, �������, ��������Ϣ */
    if ( (TAF_APS_RAT_TYPE_GSM   != enCurrRatType)
      && (TAF_APS_RAT_TYPE_WCDMA != enCurrRatType) )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSmPdpActivateInd_Inactive: Current RAT is not GSM/WCDMA!");
        return VOS_TRUE;
    }

     /* Ǩ�Ƶ���״̬TAF_APS_NW_ACTIVATING_SUBSTA_INIT,����״̬
        TAF_APS_NW_ACTIVATING_SUBSTA_INIT�д��� ID_SMREG_PDP_ACTIVATE_IND
        ��Ϣ
     */
    TAF_APS_InitSubFsm(TAF_APS_FSM_NW_ACTIVATING,
                       TAF_APS_GetNwActivatingFsmDescAddr(),
                       TAF_APS_NW_ACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpManageInd_Inactive
 ��������  : INACTIVE��״̬���յ�ID_APP_ESM_PDP_MANAGER_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpManageInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* ��ȡ��ǰ����ģʽ*/
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* ��鵱ǰģ�Ƿ�ΪLTE, �������, ��������Ϣ */
    if (TAF_APS_RAT_TYPE_LTE != enCurrRatType)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvEsmPdpManageInd_Inactive: Current RAT is not LTE!");
        return VOS_TRUE;
    }

    /* Ǩ�Ƶ���״̬TAF_APS_NW_ACTIVATING_SUBSTA_INIT,����״̬
       TAF_APS_NW_ACTIVATING_SUBSTA_INIT�д��� ID_APP_ESM_PDP_MANAGER_IND
       ��Ϣ
    */
    TAF_APS_InitSubFsm(TAF_APS_FSM_NW_ACTIVATING,
                       TAF_APS_GetNwActivatingFsmDescAddr(),
                       TAF_APS_NW_ACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive
 ��������  : INACTIVE��״̬���յ�ID_ESM_SM_EPS_BEARER_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��07��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��01��21��
    ��    ��   : A00165503
    �޸�����   : DTS2013011803709: ����ND Client���ӽ��뼼���ж�, ��ֹ��NULL
                 ״̬�¼���ND Client����RS��������

  3.��    ��   : 2013��4��23��
    ��    ��   : A00165503
    �޸�����   : DTS2013041204937: ר�ó��ؼ���ʱ����Ҫ����ND Client

  4.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ����IMSר�г��صĴ���

  5.��    ��   : 2014��2��20��
    ��    ��   : A00165503
    �޸�����   : DTS2013022201185: PS����н��������Ż�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataSerMode;
#endif
    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;

    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ����EPS���صĲ�������(Activate, Deactivate, Modify),
       ������Ӧ�Ĵ����� */
    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptActivate(pstPdpEntity, pstBearerInfo);

        if (TAF_APS_DEFAULT_CID == TAF_APS_GetCidFromLteBitCid(pstBearerInfo->ulBitCid))
        {
            TAF_APS_SndInterAttachBearerActivateInd();
        }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

        enDataSerMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

        if ((TAF_APS_RAT_TYPE_1X   != enDataSerMode)
         && (TAF_APS_RAT_TYPE_HRPD != enDataSerMode))
        {
            /* ��¼��ǰ��PS�������ڵ�ģʽ */
            TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

            /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
            TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_LTE);
        }

#endif
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive: Wrong option.");
    }

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    return VOS_TRUE;
}
#endif


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_Active
 ��������  : �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
              pstMsg     : ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
              VOS_TRUE:������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : S62952
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��30��
    ��    ��   : A00165503
    �޸�����   : DTS2012062900707: IPv6���ųɹ�, Ӧ�û�ȡIPv6��ַǰ׺�쳣

  3.��    ��   : 2014��2��20��
    ��    ��   : A00165503
    �޸�����   : DTS2013022201185: PS����н��������Ż�

  4.��    ��   : 2014��12��8��
    ��    ��   : A00165503
    �޸�����   : DTS2014111302668: ƥ��ȱʡPDN������, CID��Ӧ��ʣ��ʱ��δ��
                 ��, ����ʹ����ͬCID�ٴβ��ź�, ��ƥ��ȱʡPDN������δ�ϱ���
                 Ӧ�¼�, ���������쳣
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;
#if (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
    VOS_UINT32                          ulBearerActivateFlg;
    VOS_UINT8                           ucCidValue;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq                = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���ü����� */
    ulBearerActivateFlg = (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState) ? VOS_TRUE : VOS_FALSE;

    /* ��ǰ�Ȳ�֧��һ���Լ�����PDP�ĳ�����һ�μ���һ��������ҵ�һ��Ҫ����� CID */
    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstSetPdpCtxStateReq->stCidListStateInfo.aucCid);

    /* PDP����������� */
    if (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        /* ���CID��Ӧ��ʣ�ඨʱ��ʱ��Ϊ0, ��Ҫ�ϱ���Ӧ�¼� */
        if (0 == TAF_APS_GetCallRemainTmrLen(ucCidValue))
        {
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpCtxStateReq->stCtrl),
                                         TAF_PS_CAUSE_SUCCESS);
        }

        TAF_APS_SetCallRemainTmrLen(ucCidValue, 0);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCidValue);

#if (FEATURE_ON == FEATURE_IPV6)
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
        if (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo)
        {
            /* �ϱ�ID_EVT_TAF_PS_IPV6_INFO_IND�¼� */
            TAF_APS_SndIpv6RaInfoNotifyInd(&(pstSetPdpCtxStateReq->stCtrl),
                                           ucCidValue,
                                           pstPdpEntity->ucNsapi,
                                           (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
        }
#endif

        /* ����ɹ�����������ͳ�� */
        TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
    else
    {
        /*------------------------------------------------------------------
           ��״̬Ǩ����TAF_APS_STA_MS_DEACTIVATING
           ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsPppDialOrigReq_Active
 ��������  : ACTIVE��״̬���յ�ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��30��
    ��    ��   : A00165503
    �޸�����   : DTS2012062900707: IPv6���ųɹ�, Ӧ�û�ȡIPv6��ַǰ׺�쳣

  3.��    ��   : 2014��2��20��
    ��    ��   : A00165503
    �޸�����   : DTS2013022201185: PS����н��������Ż�

  4.��    ��   : 2014��12��8��
    ��    ��   : A00165503
    �޸�����   : DTS2014111302668: ƥ��ȱʡPDN������, CID��Ӧ��ʣ��ʱ��δ��
                 ��, ����ʹ����ͬCID�ٴβ��ź�, ��ƥ��ȱʡPDN������δ�ϱ���
                 Ӧ�¼�, ���������쳣
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
#if (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���CID��Ӧ��ʣ�ඨʱ��ʱ��Ϊ0, ��Ҫ�ϱ���Ӧ�¼� */
    if (0 == TAF_APS_GetCallRemainTmrLen(pstPppDialOrigReq->stPppDialParaInfo.ucCid))
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                  TAF_PS_CAUSE_SUCCESS);
    }

    TAF_APS_SetCallRemainTmrLen(pstPppDialOrigReq->stPppDialParaInfo.ucCid, 0);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
    TAF_APS_SndPdpActivateCnf(ucPdpId, pstPppDialOrigReq->stPppDialParaInfo.ucCid);

#if (FEATURE_ON == FEATURE_IPV6)
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    if (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo)
    {
        /* �ϱ�ID_EVT_TAF_PS_IPV6_INFO_IND�¼� */
        TAF_APS_SndIpv6RaInfoNotifyInd(&(pstPppDialOrigReq->stCtrl),
                                       pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                       pstPdpEntity->ucNsapi,
                                       (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_APS_RAT_TYPE_LTE != TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);
    }
#endif
    /* ����ɹ�����������ͳ�� */
    TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_Active
 ��������  : INACTIVE��״̬���յ�ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��28��
    ��    ��   : A00165503
    �޸�����   : DTS2012062802394: �ϱ�IPv6��RA��Ϣʱ, û�м���û�����Ĳ�
                 �������Ƿ�ΪIPv6

  3.��    ��   : 2012��6��30��
    ��    ��   : A00165503
    �޸�����   : DTS2012062900707: IPv6���ųɹ�, Ӧ�û�ȡIPv6��ַǰ׺�쳣

  4.��    ��   : 2014��5��22��
    ��    ��   : A00165503
    �޸�����   : DTS2013022201185: ���н��������Ż�

  5.��    ��   : 2014��5��16��
    ��    ��   : A00165503
    �޸�����   : DTS2014050703206: IP���ʹӲ��Ų����л�ȡ

  6.��    ��   : 2014��12��8��
    ��    ��   : A00165503
    �޸�����   : DTS2014111302668: ƥ��ȱʡPDN������, CID��Ӧ��ʣ��ʱ��δ��
                 ��, ����ʹ����ͬCID�ٴβ��ź�, ��ƥ��ȱʡPDN������δ�ϱ���
                 Ӧ�¼�, ���������쳣
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#if (FEATURE_ON == FEATURE_IPV6)
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
#endif


    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ���CID��Ӧ��ʣ�ඨʱ��ʱ��Ϊ0, ��Ҫ�ϱ���Ӧ�¼� */
    if (0 == TAF_APS_GetCallRemainTmrLen(pstCallOrigReq->stDialParaInfo.ucCid))
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                               pstCallOrigReq->stDialParaInfo.ucCid,
                               TAF_PS_CAUSE_SUCCESS);
    }

    TAF_APS_SetCallRemainTmrLen(pstCallOrigReq->stDialParaInfo.ucCid, 0);

    /* ��ehrpd�£���ǰ�Ѿ����initial attach������Ĭ�ϳ���cid=0��
        ����dhcpЭ�̿��ܻ�û��Э�����,��ʱ���ϱ���Э�̽����ϱ� */
    if (VOS_FALSE == pstPdpEntity->ucNeedGetDnsFlg)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
        TAF_APS_SndPdpActivateCnf(ucPdpId, pstCallOrigReq->stDialParaInfo.ucCid);
    }

#if (FEATURE_ON == FEATURE_IPV6)
    enPdpType    = pstCallOrigReq->stDialParaInfo.enPdpType;

    if ( ((TAF_PDP_IPV6 == enPdpType) || (TAF_PDP_IPV4V6 == enPdpType))
      && (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo) )
    {
        /* �ϱ�ID_EVT_TAF_PS_IPV6_INFO_IND�¼� */
        TAF_APS_SndIpv6RaInfoNotifyInd(&(pstCallOrigReq->stCtrl),
                                       pstCallOrigReq->stDialParaInfo.ucCid,
                                       pstPdpEntity->ucNsapi,
                                       (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
    }
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_APS_RAT_TYPE_LTE != TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);
    }
#endif
    /* ����ɹ�����������ͳ�� */
    TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_Active
 ��������  : �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE  :������Ϣʧ��
             VOS_TRUE   :������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /*-------------------------------------------------------
       ƽ̨����֧��CDMA���ҵ�ǰפ��ģʽ���Ϊ3GPP2,
       ��ѡ��3GPP2���̣�����ѡ��3GPP����

       ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
       ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

       ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
    -------------------------------------------------------*/
    if (VOS_TRUE == TAF_APS_IsEnterCdataDiscing())
    {
	    /* �ϱ�PS���йҶ���Ӧ�¼� */
        TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

        /* ����TAF_APS_FSM_CDATA_DISCING״̬�� */
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);
    }
    else
#endif
    {
        /*------------------------------------------------------------------
           ��״̬Ǩ����TAF_APS_STA_MS_DEACTIVATING
           ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_Active
 ��������  : �յ�ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE :������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_MODIFYING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_MODIFYING_SUBSTA_INIT

       ��TAF_APS_MS_MODIFYING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_MODIFYING,
                       TAF_APS_GetMsModifyingFsmDescAddr(),
                       TAF_APS_MS_MODIFYING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_Active
 ��������  : ACTIVE��״̬���յ�ID_MSG_TAF_PS_CALL_ANSWER_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_Active
 ��������  : ACTIVE��״̬���յ�ID_MSG_TAF_PS_CALL_HANGUP_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl),
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpModifyInd_Active
 ��������  : �յ�ID_PMC_SMREG_PDP_MODIFY_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_PMC_SMREG_PDP_MODIFY_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE  :������Ϣʧ��
             VOS_TRUE   :������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    APS_MDFIND_PARA_ST                  stParam;
    SMREG_PDP_MODIFY_IND_STRU          *pstSmPdpModifyInd;
#if (FEATURE_ON == FEATURE_LTE)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif

    /* ��ȡ��Ϣ���� */
    pstSmPdpModifyInd = (SMREG_PDP_MODIFY_IND_STRU *)pstMsg;
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType     = TAF_APS_GetCurrPdpEntityRatType();
#if (FEATURE_ON == FEATURE_LTE)
    pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
#endif

    ulResult = Aps_PdpMdfIndParaCheck(pstSmPdpModifyInd, &stParam);
    if (APS_PARA_INVALID  == ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSmPdpModifyInd_Active: Check para failed! ");

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* ���QOS�Ƿ�����MIN */
    if (APS_PARA_VALID == Aps_CheckQosSatisify(ucPdpId, &stParam.NewQos))
    {
        /* ����MINQOS */
        Aps_PdpMdfIndQosSatisfy(ucPdpId, &stParam, pstSmPdpModifyInd);

#if (FEATURE_ON == FEATURE_LTE)
        /* ͬ��PDP��Ϣ��ESM */
        MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_MODIFY);
#endif

        /* �����ǰģΪGSM, Ǩ��״̬ */
        if (TAF_APS_RAT_TYPE_GSM == enCurrRatType)
        {
            /*------------------------------------------------------------------
               ����TAF_APS_STA_MS_MODIFYING״̬��
               ���غ���״̬�л�ΪTAF_APS_MS_MODIFYING_SUBSTA_INIT

               ��TAF_APS_MS_MODIFYING_SUBSTA_INIT��״̬��
               ����D_PMC_SMREG_PDP_MODIFY_IND��Ϣ
            ------------------------------------------------------------------*/
            TAF_APS_InitSubFsm(TAF_APS_FSM_MS_MODIFYING,
                               TAF_APS_GetMsModifyingFsmDescAddr(),
                               TAF_APS_MS_MODIFYING_SUBSTA_INIT);
        }
    }
    else
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmPdpDeactivateInd_Active
 ��������  : �յ� ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_PMC_SMREG_PDP_DEACTIV_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE  :������Ϣʧ��
             VOS_TRUE   :������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmPdpDeactivateInd               = (SMREG_PDP_DEACTIVATE_IND_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* ͬ��PDP״̬����Ϣ��ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ���SNDCP�Ѿ�����, �ͷ�SNDCP��Դ */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpModifyInd_Active
 ��������  : �յ� ID_APP_ESM_PDP_MODIFY_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_APP_ESM_PDP_MODIFY_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE  :������Ϣʧ��
             VOS_TRUE   :������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ����¼LTE�ϱ���EPSQOS
  3.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APP_ESM_PDP_MODIFY_IND_STRU        *pstPdpModify;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpModify = (APP_ESM_PDP_MODIFY_IND_STRU*)pstMsg;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* �������Ĭ�ϳ��أ����ϱ���Ĭ�ϳ��ز��ϱ� */
    if (TAF_APS_DEFAULT_CID != pstPdpModify->ulCid)
    {
        if (VOS_TRUE == pstPdpModify->bitOpSdfQos)
        {
            pstPdpEntity->bitOpEpsQos   = VOS_TRUE;
            PS_MEM_CPY((VOS_UINT8 *)&pstPdpEntity->stEpsQos,
                       (VOS_UINT8 *)&pstPdpModify->stSdfQosInfo,
                       sizeof(TAF_EPS_QOS_STRU));
        }

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFIED_IND�¼� */
        TAF_APS_SndPdpModifyInd(ucPdpId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpDeactivateInd_Active
 ��������  : �յ� ID_L4A_APS_PDP_DEACTIVATE_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_L4A_APS_STA_DEACTIVATE_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE  :������Ϣʧ��
             VOS_TRUE   :������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��8��21��
    ��    ��   : A00165503
    �޸�����   : DTS2014081803666: ����SNDCP����״̬�ж�, ���SNDCP���ڼ���
                 ״̬, �轫��ȥ����

  3.��    ��  : 2015��5��29��
    ��    ��  : a00165503
    �޸�����  :  MODIFY for DTS2015051204781

  4.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpDeactivateInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APP_ESM_PDP_RELEASE_IND_STRU       *pstEsmPdpDeactivateInd;

    /* ��ȡ��Ϣ���� */
    pstEsmPdpDeactivateInd = (APP_ESM_PDP_RELEASE_IND_STRU*)pstMsg;

    /* ��ȡ��ǰ״̬����APS���� */
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��������APSʵ�����ݵ�ַ */
    pstPdpEntity           = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* �������Ĭ�ϳ��أ����ϱ���Ĭ�ϳ��ز��ϱ� */
    if (TAF_APS_DEFAULT_CID != pstPdpEntity->stClientInfo.ucCid)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼��ϱ� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapEsmCause(pstEsmPdpDeactivateInd->ulRslt));
    }
    else
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
#endif
    }

    /* ���SNDCP�Ѿ�����, �ͷ�SNDCP��Դ */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpSetupInd_Active
 ��������  : �յ�ID_APP_ESM_PDP_SETUP_IND��Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����
             pstMsg     : ID_APP_ESM_PDP_SETUP_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE  : ������Ϣʧ��
             VOS_TRUE   : ������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��19��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project

  3.��    ��   : 2015��01��28��
    ��    ��   : w00316404
    �޸�����   : send pdp activate inf to ND Client

  4.��    ��   : 2016��03��03��
    ��    ��   : w00316404
    �޸�����   : ���뼼����ΪNULL�ŷ���pdp activate ind��ND Client
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpSetupInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_IMS) || (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;

    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();

    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
#endif

#if (FEATURE_ON == FEATURE_IMS)
    /* ����IMSר�г��� */
    TAF_APS_ProcImsDedicateBearer(pstPdpEntity);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_RAT_TYPE_NULL != enCurrRatType)
      && (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                               pstPdpEntity->PdpAddr.aucIpV6Addr);

        pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmSmEpsBearerInfoInd_Active
 ��������  : ACTIVE��״̬���յ�ID_ESM_SM_EPS_BEARER_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��07��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


    /* ����EPS���صĲ�������(Activate, Deactivate, Modify),
       ������Ӧ�Ĵ����� */
    if (SM_ESM_PDP_OPT_MODIFY == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptModify(pstPdpEntity, pstBearerInfo);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            /* �����ڲ���Ϣ���������ڼ�������е�״̬������Ҫ�������Ϣ */
            TAF_APS_SndInterAttachBearerActivateInd();
            /* ��¼��ǰ��PS�������ڵ�ģʽ */
            TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);
            /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
            TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_LTE);

            TAF_APS_SET_CDATA_MTU(0);
        }



#endif
    }
    else if (SM_ESM_PDP_OPT_DEACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptDeactivate(pstPdpEntity, pstBearerInfo);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive: Wrong option.");
    }

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpActivateRsp_Active
 ��������  : TAF_APS_STA_ACTIVE״̬���յ�APS_SN_DEACT_RSP_MSG_TYPE��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��6��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APS_SNDCP_ACTIVATE_RSP_ST          *pstSnActivateRsp;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ulResult         = VOS_OK;
    pstSnActivateRsp = &((APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg)->ApsSnActRsp;
    ucPdpId          = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity     = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* �����Ϣ���� */
    ulResult = Aps_SnMsgModSnActRspParaCheck(pstSnActivateRsp);
    if (APS_PARA_VALID != ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSndcpActivateRsp_Active: Check para failed!");

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* �յ�SN_ACT_RSP���޸�APSʵ�����, ����XID����, TRANSMODE */
    Aps_SnActRspChngEntity(pstSnActivateRsp, ucPdpId);

    /* ����RABM�Ĵ���ģʽ */
    TAF_APS_SndRabmSetTransModeMsg(pstSnActivateRsp->ucNsapi,
                                   pstPdpEntity->GprsPara.TransMode);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpDeactivateRsp_Active
 ��������  : TAF_APS_STA_ACTIVE״̬���յ�APS_SN_DEACT_RSP_MSG_TYPE��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��2��6��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpDeactivateRsp_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��TAF_APS_STA_ACTIVE״̬��, Ŀǰ����Ҫ����APS_SN_DEACT_RSP_MSG_TYPE */

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpDeactivateRsp_Active
 ��������  : TAF_APS_STA_ACTIVE״̬���յ�APS_SN_STATUS_REQ_MSG_TYPE��Ϣ�Ĵ���
 �������  : ulEventType    - ��ϢID
             pstMsg         - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE       - ��Ϣ����ɹ�
             VOS_FALSE      - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��20��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq;

    pstSnStatusReq = &((APS_SNDCP_STATUS_REQ_MSG*)pstMsg)->ApsSnStatusReq;
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    ulRslt = TAF_APS_ValidatePdpForSnStatusReq(ucPdpId, pstSnStatusReq);
    if (VOS_TRUE == ulRslt)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvRabmSysChgToGprs_Active
 ��������  : �յ� ID_RABM_APS_SYS_CHG_TO_GPRS��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_RABM_MN_SYS_LTE_CHG_TO_GPRS��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE  :������Ϣʧ��
             VOS_TRUE   :������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvRabmSysChgToGprs_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���SNDCP�����ʶ, ����SNDCP */
    if (APS_SNDCP_INACT == TAF_APS_GetPdpEntSndcpActFlg(ucPdpId))
    {
        Aps_RabmMsgActSndcp(ucPdpId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvRabmLocalPdpDeactivateReq_Active
 ��������  : �յ� RABM_APS_LOCAL_PDP_DEACT_REQ_MSG��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_RABM_APS_LOCAL_PDP_DEACT_REQ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE  :������Ϣʧ��
             VOS_TRUE   :������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvRabmLocalPdpDeactivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* ��ȡ��ǰ״̬���Ľ��뼼�� */
    enCurrRatType = TAF_APS_GetCurrPdpEntityRatType();

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��GUģ�´������Ϣ, LTEģֱ�Ӷ��� */
    if (TAF_APS_RAT_TYPE_WCDMA == enCurrRatType)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_RAB_SETUP_FAILURE);

        /* �����ڲ���Ϣ, ȥ����PDP */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvApsInternalPdpDeactivateReq_Active
 ��������  : ACTIVE��״̬���յ�ID_APS_APS_INTER_PDP_DEACTIVATE_REQ��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ��Ϣ����ɹ�
             VOS_FALSE                  - ��Ϣ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsInternalPdpDeactivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /*-------------------------------------------------------
       ƽ̨����֧��CDMA���ҵ�ǰפ��ģʽ���Ϊ3GPP2,
       ��ѡ��3GPP2���̣�����ѡ��3GPP����

       ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
       ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

       ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
    -------------------------------------------------------*/
    if (VOS_TRUE == TAF_APS_IsEnterCdataDiscing())
    {
        /* �����ڲ���ϢID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_INTER_DEACTIVE,
                                       TAF_APS_INTER_END_CALL_REASON_USER_END,
                                       TAF_APS_GetCurrFsmEntityPdpId(),
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }
    else
#endif
    {
        /*------------------------------------------------------------------
           ����TAF_APS_STA_MS_DEACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬�д���
           ID_APS_APS_INTER_PDP_DEACTIVATE_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvApsLocalPdpDeactivateReq_Active
 ��������  : �յ� TAF_APS_RcvApsLocalPdpDeactivateInd_Active��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_APS_APS_LOCAL_PDP_DEACTIVATE_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE  :������Ϣʧ��
             VOS_TRUE   :������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��05��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��12��2��
    ��    ��   : A00165503
    �޸�����   : DTS2014111805277: ȱʡ���ر���ȥ����ʱ, ��Ҫȥ�����������
                 ��ר�ó���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                               ucPdpId;
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstLocalMsg                         = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;
    ucPdpId                             = pstLocalMsg->ucPdpId;
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* ͬ��PDP״̬����Ϣ��ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* ֪ͨEHSM���LTEͬ����PDN��Ϣ */
        TAF_APS_SndEhsmLocDeactNtf(ucPdpId);
    }

#endif

    /* ��SM���ͱ���ȥ�������� */
    if (VOS_TRUE == pstPdpEntity->bitOpTransId)
    {
        TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);
    }

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ���SNDCP�Ѿ�����, �ͷ�SNDCP��Դ */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInterServiceStatusChangeInd_Active
 ��������  : �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType:��Ϣ����
             pstMsg     : ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:������Ϣʧ��
             VOS_TRUE :������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : s62952
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��01��21��
    ��    ��   : A00165503
    �޸�����   : DTS2013011803709: ����ND Client���ӽ��뼼���ж�, ��ֹ��NULL
                 ״̬�¼���ND Client����RS��������

  3.��    ��   : 2013��4��23��
    ��    ��   : A00165503
    �޸�����   : DTS2013041204937: ר�ó��ؼ���ʱ����Ҫ����ND Client

  4.��    ��   : 2015��5��25��
    ��    ��   : g00261581
    �޸�����   : �޸������Ϣ

  5.��    ��   : 2015��7��22��
    ��    ��   : Y00213812
    �޸�����   : �޸ĺ�����������L->1X���л�����

  6.��    ��   : 2016��03��03��
    ��    ��   : w00316404
    �޸�����   : ���뼼����ΪNULL����pdp activate ind��ND Client
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterServiceStatusChangeInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstServStaChangeInd  = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();

#if (FEATURE_ON == FEATURE_IPV6)
    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity           = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* �����ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_RAT_TYPE_NULL != pstServStaChangeInd->enRatType)
      && (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        if (VOS_TRUE != pstPdpEntity->ulNdClientActiveFlg)
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;
        }
    }
#endif

    switch (pstServStaChangeInd->enRatType)
    {
        /* ��ǰģΪGSMʱ, ����������Ϣ����SNDCP */
        case TAF_APS_RAT_TYPE_GSM:
            break;

        /* ��ǰģΪWCDMA/LTEʱ, ��Ҫȥ����SNDCP */
        case TAF_APS_RAT_TYPE_WCDMA:
        case TAF_APS_RAT_TYPE_LTE:
            if (APS_SNDCP_ACT == TAF_APS_GetPdpEntSndcpActFlg(ucPdpId))
            {
                Aps_RabmMsgDeActSndcp(ucPdpId);
            }

        /* ���֮ǰ���ؽ�����1X�ϵģ���AP��ȥ���� */

            break;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TAF_APS_RAT_TYPE_1X:
            /* TO DO: ԭ����LTE������޸� */
            /* ͬ��PDP��Ϣ��ESM */
#if (FEATURE_ON == FEATURE_LTE)
            if (TAF_APS_RAT_TYPE_LTE == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId), SM_ESM_PDP_OPT_DEACTIVATE);

                /* ֪ͨEHSM���LTEͬ����PDN��Ϣ */
                TAF_APS_SndEhsmLocDeactNtf(ucPdpId);


                /* ֹͣ����ͳ�� */
                TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

                /* �ϱ�ȥ������¼� */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
                /* ����ȥ���� */
                TAF_APS_LocalReleaseProc(ucPdpId);
            }
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {

                /* ֹͣ����ͳ�� */
                TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

                /* �ϱ�ȥ������¼� */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

                /* ����ȥ���� */
                TAF_APS_LocalReleaseProc(ucPdpId);
            }
#endif
            break;
#endif
        case TAF_APS_RAT_TYPE_NULL:
        default:
            break;
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccDiscInd_Active
 ��������  : ACTIVE��״̬���յ�ID_XCC_APS_DATA_CALL_DISC_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��7��
    ��    ��   : g00261581
    �޸�����   : �жϽ���Dormant���Ƿ�����Dormant TI
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd   = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    /* ����ʵ�屣���ԭ��ֵ */
    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    if (TAF_PS_CAUSE_XCC_AS_SO_REJ == pstPdpEntity->enCause)
    {
        /******************************************************************************/
        /*               SO Rej ԭ��ֵ��Ҫ���⴦������ȥ����                        */
        /******************************************************************************/

        if (TAF_APS_CDATA_PPP_STATE_INACTIVE != TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* �յ������SO_REJ���ϱ�ȥ������¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, pstPdpEntity->enCause);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        return VOS_TRUE;
    }
    else
    {
        TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_NO_LINK);

        /* ֪ͨPPP��ǰ��·������ */
        TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_NOT_EXISTED);

        /* ������ԭ��ֵ��ΪSo rej, TAF APS����Dormant״̬ */
        TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_TRUE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallEnterDormantInd_Active
 ��������  : ACTIVE��״̬���յ�ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallEnterDormantInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataServiceMode;

    enDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

    if (TAF_APS_RAT_TYPE_EHRPD == enDataServiceMode)
    {
        /* EHRPDģʽ��ֻ֪ͨEHSM����DORMANT״̬��APS��״̬���ı� */
        TAF_APS_SndEhsmDiscNtf();
    }
    else if ((TAF_APS_RAT_TYPE_1X   == enDataServiceMode)
          || (TAF_APS_RAT_TYPE_HRPD == enDataServiceMode))
    {
        /*------------------------------------------------------------------
           ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
           ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

           ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);
    }
    else
    {
        /* Do nothing */
        TAF_WARNING_LOG1(WUEPS_PID_TAF,"TAF_APS_RcvPsCallEnterDormantInd_Active not cdma mode", enDataServiceMode);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallInterEpdszidReOrig_Active
 ��������  : In Active State, After Rcv Epdszid ReOrig Req, Only add Current EPDSZID into zone List
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��30��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInterEpdszidReOrig_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_CDATA_EPDSZID_STRU         *pstCurrEpdszid;

    pstCurrEpdszid = TAF_APS_GetCurrEpdszidInfo();

    /* Add EPDSZID into Packet Zone List */
    TAF_APS_AddEpdszidToZoneList(pstCurrEpdszid);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccUpdateDataCallInfoInd_Active
 ��������  : Processing message:ID_XCC_APS_UPDATE_DATA_CALL_INFO_IND, This Message is only
             processed in Active, other state is discarded.
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccUpdateDataCallInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU     *pstDataCallInof = VOS_NULL_PTR;
    VOS_UINT8                                   ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDataCallInof = (XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU *)pstMsg;

    /* Only Update SR_ID Now */
    if (pstDataCallInof->ucSrId != TAF_APS_GetPdpEntSrId(ucPdpId))
    {
        TAF_APS_SetPdpEntSrId(ucPdpId, pstDataCallInof->ucSrId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvCdsServiceInd_Active
 ��������  : ACTIVE��״̬���յ�ID_CDS_APS_SERVICE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvCdsServiceInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode;

    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrCdataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

    if (TAF_APS_RAT_TYPE_EHRPD == enCurrCdataServiceMode)
    {
        TAF_APS_SndEhsmReconnReq(ucPdpId);
    }
    else
    {
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmDiscInd_Active
 ��������  : ACTIVE��״̬���յ�ID_HSM_APS_DISC_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��11��9��
    ��    ��   : g00261581
    �޸�����   : �ȴ�PPPЭ�̵Ĺ��̴�Active״̬��Ų��ȥ����״̬�¿���ֱ��Ǩ��-
                 Dormant

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    HSM_APS_DISC_IND_STRU              *pstDiscInd = VOS_NULL_PTR;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd      = (HSM_APS_DISC_IND_STRU *)pstMsg;

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_NO_LINK);

    /* ֪ͨPPP��ǰ��·������ */
    TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_NOT_EXISTED);

    TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    if (HSM_APS_CAUSE_HRPD_HANDOFF_TO_1X == pstDiscInd->enCause)
    {
        TAF_APS_SetIsHrpdDisabledFlag(VOS_TRUE);
        TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_1X);

        /* �����ڲ�HRPD��1X�л�������Ϣ */
        TAF_APS_SndInterHrpdTo1XHandOffReq(ucPdpId);
    }
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactInd_Active
 ��������  : ACTIVE��״̬���յ�ID_PPP_APS_DEACT_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ����ԭ��ֵ */
    pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_NW_DISC;

    /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_ACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /*------------------------------------------------------------------
       ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
       ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

       ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
       ����ID_PPP_APS_DEACT_IND��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppModifyInd_Active
 ��������  : ACTIVE��״̬���յ�ID_PPP_APS_MODIFY_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��27��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    PPP_APS_MODIFY_IND_STRU            *pstModifyInd;
    TAF_PDP_TYPE_ENUM_UINT8             enPdnType;
    VOS_INT32                           lCmpRst;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    lCmpRst        = VOS_ERROR;
    pstModifyInd   = (PPP_APS_MODIFY_IND_STRU*)pstMsg;
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    enPdnType      = TAF_APS_MapPppPdnTypeToAps(pstModifyInd->enPdnType);

    if (APS_ADDR_INVALID == enPdnType)
    {
        return VOS_TRUE;
    }

    if (pstPdpEntity->PdpAddr.ucPdpTypeNum != enPdnType)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                       TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;

        return VOS_TRUE;
    }

    /* �ж�PPP������ */
    switch (pstModifyInd->enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:

            lCmpRst = PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpAddr,
                                 pstModifyInd->aucIpv4Addr,
                                 TAF_APS_PPP_IPV4_ADDR_LEN);
            break;

        case TAF_APS_PPP_ADDR_TYPE_IPV6:

            lCmpRst =  PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpV6Addr,
                                  pstModifyInd->aucIpv6Addr,
                                  TAF_APS_PPP_IPV6_ADDR_LEN);

            break;

        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:

            lCmpRst = PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpV6Addr,
                                 pstModifyInd->aucIpv6Addr,
                                 TAF_APS_PPP_IPV6_ADDR_LEN);

            if ((0 != PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpAddr,
                                 pstModifyInd->aucIpv4Addr,
                                 TAF_APS_PPP_IPV4_ADDR_LEN))
             || (0 != lCmpRst))
            {
                lCmpRst = VOS_ERROR;

            }

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvPppModifyInd_Active:Wrong Msg Entry");
            break;
    }

    if (0 != lCmpRst)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                       TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;
        return VOS_TRUE;
    }

    if (pstModifyInd->usMtu != TAF_APS_GET_CDATA_MTU())
    {
        TAF_APS_SET_CDATA_MTU(pstModifyInd->usMtu);


    }
    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnInfoChgInd_Active
 ��������  : ����ehsm��pdn�仯��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��6��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnInfoChgInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_INFO_CHANGE_IND_STRU  *pstPdnChgInd;
    VOS_UINT8                           ucPdpId;
    VOS_INT32                           lCmpIpv4AddrRst;
    VOS_INT32                           lCmpIpv6AddrRst;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpType;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstPdnChgInd    = (EHSM_APS_PDN_INFO_CHANGE_IND_STRU*)pstMsg;
    ucPdpId         = TAF_APS_GetPdpIdByCid(pstPdnChgInd->ucCid);
    lCmpIpv4AddrRst = 0;
    lCmpIpv6AddrRst = 0;
    ucPdpType       = TAF_APS_MapEhsmPdnTypeToAps(pstPdnChgInd->stPdnChgInfo.stPdnAddr.enPdnType);

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (APS_ADDR_INVALID == ucPdpType)
    {
        return VOS_TRUE;
    }

    if (pstPdpEntity->PdpAddr.ucPdpTypeNum != ucPdpType)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                       TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;

        return VOS_TRUE;
    }

    switch (pstPdnChgInd->stPdnChgInfo.stPdnAddr.enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
            lCmpIpv4AddrRst                     = PS_MEM_CMP(pstPdnChgInd->stPdnChgInfo.stPdnAddr.aucIpv4Addr,
                                                             pstPdpEntity->PdpAddr.aucIpAddr,
                                                             TAF_IPV4_ADDR_LEN);
            break;

        case TAF_APS_PPP_ADDR_TYPE_IPV6:
            lCmpIpv6AddrRst                     = PS_MEM_CMP(pstPdnChgInd->stPdnChgInfo.stPdnAddr.aucIpv6Addr,
                                                             pstPdpEntity->PdpAddr.aucIpV6Addr,
                                                             TAF_IPV6_PREFIX_LEN);

            break;

        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            lCmpIpv4AddrRst                     = PS_MEM_CMP(pstPdnChgInd->stPdnChgInfo.stPdnAddr.aucIpv4Addr,
                                                             pstPdpEntity->PdpAddr.aucIpAddr,
                                                             TAF_IPV4_ADDR_LEN);

            lCmpIpv6AddrRst                     = PS_MEM_CMP(pstPdnChgInd->stPdnChgInfo.stPdnAddr.aucIpv6Addr,
                                                             pstPdpEntity->PdpAddr.aucIpV6Addr,
                                                             TAF_IPV6_PREFIX_LEN);

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnInfoChgInd_Active:Wrong Msg Entry");
            break;
    }

    /* ��EHSM����ȥ������Ϣ */
    if ((0 != lCmpIpv4AddrRst)
     || (0 != lCmpIpv6AddrRst))
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                       TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;
        return VOS_TRUE;
    }

    if (pstPdnChgInd->stPdnChgInfo.usMtu != TAF_APS_GET_CDATA_MTU())
    {
        TAF_APS_SET_CDATA_MTU(pstPdnChgInd->stPdnChgInfo.usMtu);


    }
    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterEndCdmaCallReq_Active
 ��������  : ��״̬���յ�ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��11��10��
    ��    ��   : g00261581
    �޸�����   : ACTIVE״̬���յ��ڲ�ȥ���ֱ�Ӽ���ȥ����״̬��
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
   /*------------------------------------------------------------------
       ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
       ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

       ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_INTERNAL_DISC_SO_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}




/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInterServiceStatusChangeReq_Dormant
 ��������  : DORMANT״̬���յ�TAF�ķ���״̬��Ϣ
             ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND֪ͨ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��18��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��03��24��
    ��    ��   : y00314741
    �޸�����   : Iteration 11
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterServiceStatusChangeReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                     ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32                  enCurrCdataServiceMode;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU *pstServStaChange = VOS_NULL_PTR;

    /* ��ȡPDP ID */
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��Ϣ���� */
    pstServStaChange  = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /*��ȡ��ǰ�������ݷ����ģʽ*/
    enCurrCdataServiceMode  = TAF_APS_GetCurrPdpEntityDataServiceMode();

    /* ���ݴ�����뼼���ֱ��� */
    if (TAF_APS_RAT_TYPE_HRPD == pstServStaChange->enRatType)
    {
         /* ��1X�л���HRPD */
        if (TAF_APS_RAT_TYPE_1X == enCurrCdataServiceMode)
        {
            TAF_APS_Proc1xToHrpdHandOff(ucPdpId, pstServStaChange->ucIsNewSession);
        }
    }
    else if (TAF_APS_RAT_TYPE_1X == pstServStaChange->enRatType)
    {
        /* ��HRPD�л���1X */
        if (TAF_APS_RAT_TYPE_HRPD == enCurrCdataServiceMode)
        {
            /* �����ڲ�HRPD��1X�л�������Ϣ */
            TAF_APS_SndInterHrpdTo1XHandOffReq(ucPdpId);
        }
    }
    else if (TAF_APS_RAT_TYPE_LTE   == pstServStaChange->enRatType)
    {
        if (TAF_APS_RAT_TYPE_1X == enCurrCdataServiceMode)
        {
            /* ����1X dormant̬ȥ���� */
            TAF_APS_SndInterEnd1xServiceInDormantInd(ucPdpId);
        }

        if (TAF_APS_RAT_TYPE_HRPD == enCurrCdataServiceMode)
        {
            /* �ϱ�ȥ������¼� */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
            /* ����ȥ���� */
            TAF_APS_LocalReleaseProc(ucPdpId);

            /* ֪ͨ�ⲿģ��PSģʽ�л� */
            TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);
        }
    }
    else if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChange->enRatType)
    {
        /* �ϱ�ȥ������¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
        /* ����ȥ���� */
        TAF_APS_LocalReleaseProc(ucPdpId);
        /* ֪ͨ�ⲿģ��PSģʽ�л� */
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);
    }
    else
    {
        ;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvCdsServiceInd_Dormant
 ��������  : DORMANT��״̬���յ�ID_CDS_APS_SERVICE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT32 TAF_APS_RcvCdsServiceInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if ((TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
     || (TAF_APS_CDMA_TC_SUSPENDED == TAF_APS_GET_CDATA_SUSPEND_STATUS()))
    {
        /* ��CDS����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ */
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

        return VOS_TRUE;
    }

    /*-------------------------------------------------------
       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppReConnInd_Dormant
 ��������  : Dormant״̬���յ���ϢID_PPP_APS_RECONN_IND�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppReConnInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if ((TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
     || (TAF_APS_CDMA_TC_SUSPENDED == TAF_APS_GET_CDATA_SUSPEND_STATUS()))
    {
        TAF_APS_SndPppLinkStatusNotify(ucPdpId, TAF_APS_PPP_LINK_NOT_EXISTED);

        return VOS_TRUE;
    }

    /*-------------------------------------------------------
       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactInd_Dormant
 ��������  : Dormant״̬���յ���ϢID_PPP_APS_DEACT_NTF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��12��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�����ȥ�����¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_PPP_NW_DISC);

    /* ֹͣDormant ��ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP���� */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccIncomingCallInd_Dormant
 ��������  : DORMANT��״̬���յ�ID_XCC_APS_INCOMING_CALL_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        /* ֹͣDormant ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);
    }

    /*-------------------------------------------------------
       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallOrigReq_Dormant
 ��������  : DORMANT��״̬���յ�ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallOrigReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�����ɹ� */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                           pstCallOrigReq->stDialParaInfo.ucCid,
                           TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsPppDialOrigReq_Dormant
 ��������  : DORMANT��״̬���յ�ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��06��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsPppDialOrigReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�����ɹ� */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                              TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallEndReq_Dormant
 ��������  : DORMANT��״̬���յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��11��11��
    ��    ��   : g00261581
    �޸�����   : �ع�Dormant״̬�µ�ȥ��������
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallEndReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡPPP״̬ */
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /****************************************************************************************************/
    /*             1. Dormant timer�����ڼ䣬���ٷ��������󣬲���Ҫ����ȥ����״̬��                   */
    /*             2. PPP״̬ΪInactive(�м�ģʽ), ����Ҫȥ����Э�̣�����Ҫ�������ʲ�����ȥ����״̬��   */
    /****************************************************************************************************/
    if ((TAF_APS_TIMER_STATUS_RUNING      == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
     || (TAF_APS_CDATA_PPP_STATE_INACTIVE == enPppState))
    {
        /* ֹͣDormant ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

        /* �����ǰ��PPP״̬�Ǽ���� */
        if (TAF_APS_CDATA_PPP_STATE_ACTIVE == enPppState)
        {
            /* ��PPP����deact ind */
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* �ϱ�ȥ������¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        return VOS_TRUE;
    }

    /*----------------------------------------------------------------------------
       DORMANT״̬��ȥ�������ȥ����״̬�����Ƚ���������PPPȥ����Э�̣��ٶ���
    ----------------------------------------------------------------------------*/
    /* ����TAF_APS_FSM_CDATA_DISCING״̬�� */
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallInterEpdszidReOrig_Dormant
 ��������  : When In Dormant State,Rcv Epdszid Re-Orig Req Msg
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInterEpdszidReOrig_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* Get PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* If Dormant Timer is running ,Set Epdszid ReOrig Flag */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        /* Don't start Re-Orig right now , Only Set the Epdszid Re-Orig scene After Dormant Ti expired */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_REORIG_AFTER_DORMANT_TI_EXPIRED);
    }
    else
    {
        /* Start Re-Orig */
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                           TAF_APS_GetCdataEstingFsmDescAddr(),
                           TAF_APS_CDATA_ESTING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiDormantTimerExpired_Dormant
 ��������  : In Dormant State, Dormant Timer is Expried ,Process Re-Orig
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��31��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���
 �޸���ʷ      :
  2.��    ��   : 2015��03��27��
    ��    ��   : y00314741
    �޸�����   : Iteration 11

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiDormantTimerExpired_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* If Re-Orig Pending Status is TRUE, After Dormant Timer Expired, Start Re-Orig Again */
    if (TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG != TAF_APS_GetEpdszidChgReOrigScene())
    {
        /* Snd Inter Msg To Re-Orig */
        TAF_APS_SndInterEpdszidReOrigReq();

        /* Esting Fsm is started, Set Re-Orig Secne BuTT */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
    }
    else
    {
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccResumeInd_Dormant
 ��������  : When in Dormant state, rcv Resume Ind msg ,start re_orig
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccResumeInd_Dormant(

    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* Get PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        return VOS_TRUE;
    }

    /* If Re-Orig Pending Status is TRUE, After Traffic channel exist Expired, Start Re-Orig Again */
    if (TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG != TAF_APS_GetEpdszidChgReOrigScene())
    {
        /* Snd Inter Msg to Re-Orig */
        TAF_APS_SndInterEpdszidReOrigReq();

        /* Esting Fsm is started, Set Re-Orig Secne BuTT */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
    }
    else
    {
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmCalConnectInd_Dormant
 ��������  : In Dormant State, Receive CONNECT_IND,
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmCalConnectInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    TAF_APS_SetCdmaAirLinkStatus(ucPdpId, TAF_APS_CDATA_AIR_LINK_CONNECTED);

    /* ���������ϱ���ʱ�� */
    TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);


    /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_HRPD);

    TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallInter1XToHrpdHandOff_Dormant
 ��������  : �յ��ڲ�1X��HRPD�л���Ϣ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��01��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInter1XToHrpdHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*-------------------------------------------------------
     ����TAF_APS_FSM_CDATA_HANDOFF״̬��
     ���غ���״̬�л�ΪTAF_APS_CDATA_HANDOFF_SUBSTA_INIT

     ��TAF_APS_CDATA_HANDOFF_SUBSTA_INIT��״̬�д���
     ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ��Ϣ
     -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_HANDOFF,
                       TAF_APS_GetCdataHandOffFsmDescAddr(),
                       TAF_APS_CDATA_HANDOFF_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallInterHrpdTo1XHandOff_Dormant
 ��������  : �յ��ڲ�HRPD��1X�л���Ϣ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��01��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInterHrpdTo1XHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*-------------------------------------------------------
     ����TAF_APS_FSM_CDATA_ESTING״̬��
     ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

     ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
     ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ��Ϣ
     -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEHsmPdnDeactInd_Active
 ��������  : ACTIVE��״̬���յ�ID_EHSM_APS_PDN_DEACTIVATE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEHsmPdnDeactInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    EHSM_APS_PDN_DEACTIVATE_IND_STRU   *pstEhsmPdnDeactInd;

    /* ��ȡ��Ϣ���� */
    pstEhsmPdnDeactInd    = (EHSM_APS_PDN_DEACTIVATE_IND_STRU *)pstMsg;
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
    ucCid                 = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstPdpEntity          = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ��¼ʧ��ԭ��ֵ */
    pstPdpEntity->enCause = TAF_APS_MapEhsmCause(pstEhsmPdnDeactInd->enCause);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    /* �������Ĭ�ϳ��أ����ϱ���Ĭ�ϳ��ز��ϱ� */
    if (TAF_APS_DEFAULT_CID != ucCid)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼��ϱ� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, pstPdpEntity->enCause);
    }
    else
    {
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
    }

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP���� */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmLteHandoverToEhrpdInd_Active
 ��������  : ACTIVE��״̬���յ�ID_EHSM_APS_PDN_MODIFY_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��19��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmLteHandoverToEhrpdInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU                *pstLteHandoverInd;
    VOS_UINT8                                               ucPdpId;

    VOS_UINT32                                              ulIsNeedDeactPdn;
    VOS_UINT8                                               aucIpv6Prefix[TAF_IPV6_PREFIX_LEN];
    APS_PDP_CONTEXT_ENTITY_ST                              *pstPdpEntity;

    pstLteHandoverInd = (EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU *)pstMsg;
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    ulIsNeedDeactPdn  = VOS_FALSE;

    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    if (EHSM_APS_PDN_OPTION_MODIFIED == pstLteHandoverInd->enPdnOption)
    {
        TAF_APS_ProcPdnInfoChg_LteHandoverToEhrpdScene(ucPdpId, pstLteHandoverInd, &ulIsNeedDeactPdn);

        if (VOS_TRUE == ulIsNeedDeactPdn)
        {
            TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                           TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                           ucPdpId,
                                           TI_TAF_APS_CDATA_DISCING_LEN);
            return VOS_TRUE;
        }

        PS_MEM_SET(aucIpv6Prefix, 0, TAF_IPV6_PREFIX_LEN);

        if ((EHSM_APS_PDN_TYPE_IPV6   == pstLteHandoverInd->stPdnAddr.enPdnType)
         || (EHSM_APS_PDN_TYPE_IPV4V6 == pstLteHandoverInd->stPdnAddr.enPdnType))
        {
            if ((0 != PS_MEM_CMP(pstLteHandoverInd->stPdnAddr.aucIpv6Addr, aucIpv6Prefix, TAF_IPV6_PREFIX_LEN))
             && (VOS_TRUE != pstPdpEntity->ulNdClientActiveFlg))
            {
                TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                       pstPdpEntity->PdpAddr.aucIpV6Addr);

                pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;

                /* �ڲ���dhcpЭ�̣�����IPV6�ĵ�ַ��Ȼ��ҪЭ�̣���IPV6��ַЭ�̳ɹ�����Ҫ�ϱ�����ˢ�´α��� */
                pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

            }
        }

        TAF_APS_ProcModifyReq_LteHandoverToEhrpdScene(ucPdpId, pstLteHandoverInd);

        if (pstLteHandoverInd->usMtu != TAF_APS_GET_CDATA_MTU())
        {
            TAF_APS_SET_CDATA_MTU(pstLteHandoverInd->usMtu);


        }

         /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

    }
    else if (EHSM_APS_PDN_OPTION_DEACTIVED == pstLteHandoverInd->enPdnOption)
    {
        TAF_APS_ProcLocDeactBear_MsDeactivating_LteMode();
    }
    else
    {
        ;
    }

    /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_EHRPD);

    /* �����ڲ���Ϣ���������ڼ�������е�״̬����Ҫ�������Ϣ */
    TAF_APS_SndInterAttachBearerActivateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnActInd_Inactive
 ��������  : ACTIVE��״̬���յ�ID_EHSM_APS_PDN_ACTIVATE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��19��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_IND_STRU     *pstPdnActInd;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;
    MN_APS_PDP_IPV6_DNS_STRU           *pstPdpIpv6Dns;

    pstPdnActInd = (EHSM_APS_PDN_ACTIVATE_IND_STRU *)pstMsg;

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ����PdnId, APN, PdnAdrr */
    pstPdpEntity->ucNsapi       = pstPdnActInd->ucRabId;
    pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
    pstPdpEntity->ActType       = APS_PDP_ACT_PRI;

    TAF_APS_SetPdpEntCdataPdnId(ucPdpId, pstPdnActInd->ucPdnId);

    TAF_APS_UpdateCdataEhsmPdnInfo(  pstPdpEntity,
                                   &(pstPdnActInd->stPdnAddr),
                                   &(pstPdnActInd->stApn),
                                   &(pstPdnActInd->stIpv4Dns));

    if (TAF_APS_DEFAULT_CID == pstPdnActInd->ucCid)
    {
        TAF_APS_SndInterAttachBearerActivateInd();
    }

    /* ��¼��ǰ��PS�������ڵ�ģʽ */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_EHRPD);

    TAF_APS_SET_CDATA_MTU(pstPdnActInd->usMtu);



    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    TAF_APS_IpfConfigUlFilter(ucPdpId);


    /* ����Ҫ��ȡIpv4 DNS */
    if (((VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4SecDNS))
      && (EHSM_APS_PDN_TYPE_IPV4   == pstPdnActInd->stPdnAddr.enPdnType))
    {

        return VOS_TRUE;
    }
    else if (((VOS_TRUE == pstPdnActInd->stIpv6Dns.bitOpIpv6PrimDNS) || (VOS_TRUE == pstPdnActInd->stIpv6Dns.bitOpIpv6SecDNS))
            && (EHSM_APS_PDN_TYPE_IPV6 == pstPdnActInd->stPdnAddr.enPdnType))
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);
                                   
        pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;                           

        pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstPdnActInd->stIpv6Dns;

        TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);

        pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

        return VOS_TRUE;
    }
    else if (((VOS_TRUE == pstPdnActInd->stIpv6Dns.bitOpIpv6PrimDNS) || (VOS_TRUE == pstPdnActInd->stIpv6Dns.bitOpIpv6SecDNS))
           && ((VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4SecDNS))
           && (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActInd->stPdnAddr.enPdnType))
    {
        TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);
                                   
        pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;                           

        pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstPdnActInd->stIpv6Dns;

        TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);

        pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

        return VOS_TRUE;
    }
    else
    {
        /* ��Ҫ��ȡIpv4 DNS */
        if (((EHSM_APS_PDN_TYPE_IPV4   == pstPdnActInd->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActInd->stPdnAddr.enPdnType))
         && (((VOS_TRUE != pstPdnActInd->stIpv4Dns.bitOpIpv4PrimDNS) && (VOS_TRUE != pstPdnActInd->stIpv4Dns.bitOpIpv4SecDNS))))
        {
            TAF_APS_SndDhcpDnsIpv4Req(ucPdpId);
            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;
        }

        /* ��Ҫ��ȡIpv6 DNS��Ipv4,Ipv4v6���� */
        if (((EHSM_APS_PDN_TYPE_IPV6   == pstPdnActInd->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActInd->stPdnAddr.enPdnType))
         && ((VOS_TRUE != pstPdnActInd->stIpv6Dns.bitOpIpv6PrimDNS) && (VOS_TRUE != pstPdnActInd->stIpv6Dns.bitOpIpv6SecDNS)))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);
                                   
            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;                       

            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);
            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;
        }
    }

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInterEnd1xService_Dormant
 ��������  : DORMANT��״̬���յ�ID_MSG_TAF_PS_INTER_END_1X_SERVICE_IN_DORMANT_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterEnd1xService_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId    = TAF_APS_GetCurrFsmEntityPdpId();
    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* ���Dormant Timer�����л���PPP״̬ΪInactive, ����Ҫ�ٽ���������ȥ���� */
    if ((TAF_APS_TIMER_STATUS_RUNING      == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
     || (TAF_APS_CDATA_PPP_STATE_INACTIVE == enPppState))
    {
        /* ֹͣDormant ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

        /* �ϱ�ȥ������¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* ����ȥ���� */
        TAF_APS_LocalReleaseProc(ucPdpId);

        /* ֪ͨ�ⲿģ��PSģʽ�л� */
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

        return VOS_TRUE;
    }

    /*-------------------------------------------------------
       DORMANT״̬�£���Ҫ�����½������ӣ�Ȼ���ٶϿ���

       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}



#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

